/*==============================================================================

    Mosaic: Live Visual Patching Creative-Coding Platform

    Copyright (c) 2018 Emanuele Mazza aka n3m3da <emanuelemazza@d3cod3.org>

    Mosaic is distributed under the MIT License. This gives everyone the
    freedoms to use Mosaic in any context: commercial or non-commercial,
    public or private, open or closed source.

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
    OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.

    See https://github.com/d3cod3/Mosaic for documentation

==============================================================================*/

#include "ofApp.h"

#ifdef MOSAIC_ENABLE_PROFILING
#include "Tracy.hpp"
#endif

//--------------------------------------------------------------
void ofApp::setup(){

    #ifdef MOSAIC_ENABLE_PROFILING
    ZoneScopedN("ofApp::Setup()");
    #endif

    ///////////////////////////////////////////
    // OF Stuff
    ofSetEscapeQuitsApp(false);
    ofSetVerticalSync(true);
    ofEnableAntiAliasing();
    ofSetLogLevel(PACKAGE,OF_LOG_NOTICE);
    ofRegisterURLNotification(this);

    initDataFolderFromBundle();
    ///////////////////////////////////////////

    // TIMING
    mosaicFPS = 60;
    mosaicTiming.setFramerate(mosaicFPS);
    mosaicBPM = 120;

    // Screen data

    //int count;
    //GLFWmonitor** monitors = glfwGetMonitors(&count);

    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();

    const GLFWvidmode * mode = glfwGetVideoMode(primaryMonitor); // for monitor resolution
    wRes = mode->width;
    hRes = mode->height;
    glfwGetMonitorContentScale(primaryMonitor, &xScreenContentScale, &yScreenContentScale);
    glfwGetMonitorPhysicalSize(primaryMonitor, &wScreenMM, &hScreenMM);

    pixelsxMM = mode->height/hScreenMM;

    suggestedFontSize = static_cast<int>(ofMap(yScreenContentScale,1,8,10,56));

    //std::cout << pixelsxMM << ":" << suggestedFontSize << std::endl;

    // RETINA FIX
    fontScaling = 1;
    retinaScale = yScreenContentScale;
    isRetina = false;
    if(retinaScale > 1){
        isRetina = true;
    }
    pixelScreenScale = retinaScale*fontScaling;

    // LOGGER
    isInited        = false;
    isWindowResized = false;
    isLoggerON      = false;
    mosaicLoggerChannel = shared_ptr<MosaicLoggerChannel>(new MosaicLoggerChannel());
    ofSetLoggerChannel(mosaicLoggerChannel);

    std::string tmp_msg = "";
    ofLog(OF_LOG_NOTICE,"%s | %s <%s>",WINDOW_TITLE,DESCRIPTION,MOSAIC_WWW);
    tmp_msg = " an open project by Emanuele Mazza aka n3m3da";
    ofLog(OF_LOG_NOTICE,"%s",tmp_msg.c_str());
    ofLog(OF_LOG_NOTICE,"Developers: %s",MOSAIC_DEVELOPERS);
    tmp_msg = "This project deals with the idea of integrate/amplify human-machine communication, offering a real-time flowchart based visual interface for high level creative coding.";
    ofLog(OF_LOG_NOTICE,"%s",tmp_msg.c_str());
    tmp_msg = "As live-coding scripting languages offer a high level coding environment, ofxVisualProgramming and the Mosaic Project as his parent layer container,";
    ofLog(OF_LOG_NOTICE,"%s",tmp_msg.c_str());
    tmp_msg = "aim at a high level visual-programming environment, with embedded multi scripting languages availability (Lua, GLSL and BASH).\n";
    ofLog(OF_LOG_NOTICE,"%s",tmp_msg.c_str());

    // Visual Programming Environment Load

    // ImGui
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.MouseDrawCursor = false;

    // window config ini file
    ofFile guiIniFile(ofToDataPath("imgui.ini"));
    iniFilePath = guiIniFile.getAbsolutePath();
    io.IniFilename = iniFilePath.c_str();

    // double font oversampling (default 3) for canvas zoom
    ImFontConfig font_config;
    font_config.OversampleH = 6;
    font_config.OversampleV = 6;

    ofFile fileToRead1(ofToDataPath(MAIN_FONT));
    string absPath1 = fileToRead1.getAbsolutePath();
    ofFile fileToRead2(ofToDataPath(LIVECODING_FONT));
    string absPath2 = fileToRead2.getAbsolutePath();

    // TO CHECK IN DIFFERENT MONITORS - FIX FONT SIZE FOR DIFFERENTS SCREEN RESOLUTION/PIXEl DEPTH
    io.Fonts->AddFontFromFileTTF(absPath2.c_str(),suggestedFontSize+(4*retinaScale),&font_config); // code editor font
    io.Fonts->AddFontFromFileTTF(absPath1.c_str(),suggestedFontSize+(4*retinaScale),&font_config); // GUI font

    // merge in icons from Font Awesome
    static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
    ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;
    if(isRetina){
        io.Fonts->AddFontFromFileTTF( FONT_ICON_FILE_NAME_FAS, suggestedFontSize+(6*retinaScale), &icons_config, icons_ranges );
    }else{
        io.Fonts->AddFontFromFileTTF( FONT_ICON_FILE_NAME_FAS, suggestedFontSize+2.0f, &icons_config, icons_ranges );
    }

    ImFont* defaultfont = io.Fonts->Fonts[io.Fonts->Fonts.Size - 1];
    io.FontDefault = defaultfont;

    mainTheme = new MosaicTheme();
    if(isRetina){
        mainTheme->fixForRetinaScreen();
    }
    mainMenu.setup(mainTheme,false);

    visualProgramming   = new ofxVisualProgramming();
    visualProgramming->setRetina(isRetina,retinaScale);
    visualProgramming->setup(&mainMenu, ofToString(VERSION_GRAPHIC) );
    visualProgramming->canvasViewport.set(glm::vec2(0,20*retinaScale), glm::vec2(ofGetWidth(), ofGetHeight()-(20*retinaScale)));

    patchToLoad                 = "";
    loadNewPatch                = false;
    isAutoloadedPatch           = false;

    showRightClickMenu          = false;
    createSearchedObject        = false;
    showAboutWindow             = false;

    // LOGO
    mosaicLogo = new ofImage("images/logo_1024_bw.png");
    mosaicLogoID = mainMenu.loadImage(*mosaicLogo);

    // CODE EDITOR
    luaLang = TextEditor::LanguageDefinition::Lua();
    glslLang = TextEditor::LanguageDefinition::GLSL();
    bashLang = TextEditor::LanguageDefinition::Bash();

    initScriptLanguages();

    actualCodeEditor                = 0;
    actualEditedFilePath            = "";
    actualEditedFileName            = "";
    scriptToRemoveFromCodeEditor    = "";
    isCodeEditorON                  = false;
    isOverCodeEditor                = false;

    // DHT CHATROOM
    chat_message                    = "";
    initChatModal                   = false;
    isChatroomON                    = false;
    isOverChatroom                  = false;
    setFocusOnMessageInput          = false;

    // ASSET LIBRARY
    assetWatcher.start();
    selectedFile                    = "";
    isAssetFolderInited             = false;
    isAssetLibraryON                = false;
    isOverAssetLibrary              = false;
    isDeleteModalON                 = false;

    // NET
    isInternetAvailable = false;
    isCheckingRelease = false;

    // Check for updates
    lastRelease = VERSION;

    isInternetAvailable = checkInternetReachability();

#ifdef TARGET_LINUX
    shortcutFunc = "CTRL";
#elif defined(TARGET_OSX)
    shortcutFunc = "CMD";
#elif defined(TARGET_WIN32)
    shortcutFunc = "CTRL";
#endif

    // INIT Mosaic DHT Chatroom
    if(isInternetAvailable){
        setupDHTNode();
    }

    saveNewScreenshot       = false;
    lastScreenshot          = "";
    waitForScreenshotTime   = 200;
    resetScreenshotTime     = ofGetElapsedTimeMillis();


    // AUTOLOAD PATCH ( if configured )
    checkAutoloadConfig();

    // Load imgui window config
    ImGui::LoadIniSettingsFromDisk(iniFilePath.c_str());

    #ifdef MOSAIC_ENABLE_PROFILING
    TracyAppInfo(WINDOW_TITLE, sizeof(WINDOW_TITLE));
    #endif

}

//--------------------------------------------------------------
void ofApp::update(){

    #ifdef MOSAIC_ENABLE_PROFILING
    ZoneScopedN("ofApp::Update()");
    #endif

    windowTitle = visualProgramming->currentPatchFile+" | "+visualProgramming->currentSubpatch+" - "+WINDOW_TITLE;
    ofSetWindowTitle(windowTitle);

    pixelScreenScale = retinaScale*fontScaling;

    // Visual Programming Environment
    if(mosaicTiming.tick()){
        visualProgramming->update();
        visualProgramming->canvasViewport.set(glm::vec2(0,20*retinaScale), glm::vec2(ofGetWidth(), ofGetHeight()-(20*retinaScale)));
        refreshScriptTabs();
    }

    // init start empty patch or load selected patch
    if(loadNewPatch){
        loadNewPatch = false;
        if(patchToLoad != ""){
            // load patch
            visualProgramming->preloadPatch(patchToLoad);
            mosaicBPM = visualProgramming->bpm;
            // reset asset library
            ofFile temp(patchToLoad);
            assetFolder.reset();
            assetFolder.listDir(temp.getEnclosingDirectory()+"data/");
            assetFolder.sort();
            assetWatcher.removeAllPaths();
            assetWatcher.addPath(temp.getEnclosingDirectory()+"data/");
            // load patch gui windows config
            ofxXmlSettings XML;
#if OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR < 12
            if (XML.loadFile(patchToLoad)){
#else
            if (XML.load(patchToLoad)){
#endif
                if (XML.pushTag("settings")){
                    isAssetLibraryON = static_cast<bool>(XML.getValue("AssetManager",0));
                    isCodeEditorON = static_cast<bool>(XML.getValue("CodeEditor",0));
                    visualProgramming->inspectorActive = static_cast<bool>(XML.getValue("Inspector",0));
                    isLoggerON = static_cast<bool>(XML.getValue("Logger",0));
                    visualProgramming->navigationActive = static_cast<bool>(XML.getValue("PatchNavigator",0));
                    visualProgramming->profilerActive = static_cast<bool>(XML.getValue("Profiler",0));

                    XML.popTag();
                }

            }
        }
    }

    // autoload patch on startup
    if(autoloadPatchFile != "" && isAutoloadedPatch){
        if(ofGetElapsedTimeMillis() - autoloadStartTime > waitForAutoload){
            isAutoloadedPatch = false;
            visualProgramming->preloadPatch(autoloadPatchFile);
            mosaicBPM = visualProgramming->bpm;
            ofFile temp(autoloadPatchFile);
            assetFolder.listDir(temp.getEnclosingDirectory()+"data/");
            assetFolder.sort();
            assetWatcher.removeAllPaths();
            assetWatcher.addPath(temp.getEnclosingDirectory()+"data/");
        }
    }

    // listen for editing scripts external changes
    if(codeWatchers.size() > 0){
        for(map<string,PathWatcher*>::iterator it = codeWatchers.begin(); it != codeWatchers.end(); it++ ){
            while(it->second->waitingEvents()) {
                pathChanged(it->second->nextEvent());
            }
        }
    }

    // listen for asset folder changes
    while(assetWatcher.waitingEvents()) {
        pathChanged(assetWatcher.nextEvent());
    }

    if(isWindowResized){
        isWindowResized = false;
        visualProgramming->updateCanvasViewport();
    }

    if(!isInited){
        isInited = true;

        // RETINA FIX
        ofSetWindowShape(ofGetScreenWidth()-(4*retinaScale),ofGetScreenHeight());

        if(isRetina){
            mainTheme->fixForRetinaScreen();
        }
        fileDialog.setIsRetina(isRetina);
    }

    if(ofGetElapsedTimeMillis() > 3000 && !isAssetFolderInited){
        isAssetFolderInited = true;
        assetFolder.reset();

        assetFolder.listDir(ofToDataPath("temp/data/",true));
        assetFolder.sort();
        assetWatcher.addPath(ofToDataPath("temp/data/",true));
    }

    // NET
    if(isInternetAvailable && !isCheckingRelease){
        isCheckingRelease = true;
        lastReleaseResp = ofLoadURLAsync("https://raw.githubusercontent.com/d3cod3/Mosaic/master/RELEASE.md","check_release_async");
    }

    // Mosaic Chatroom
    if(dht.dhtNode.isRunning()){
        updateDHTChat();
    }

    // Screenshot
    if(saveNewScreenshot){
        if(ofGetElapsedTimeMillis()-resetScreenshotTime > waitForScreenshotTime){ // avoid imgui filebrowser
            saveNewScreenshot = false;
            if(lastScreenshot != ""){
                ofFile file(lastScreenshot);
                // force .jpg file extension
                string finalPath = file.getAbsolutePath();
                if(ofToUpper(file.getExtension()) != "JPG"){
                    finalPath += ".jpg";
                }
                ofImage tempScreenshot;
                tempScreenshot.grabScreen(ofGetWindowRect().x,ofGetWindowRect().y,ofGetWindowWidth(),ofGetWindowHeight());
                tempScreenshot.getPixels().swapRgb();
                tempScreenshot.save(finalPath);
            }
        }
    }

    // Testing
    //ofLog(OF_LOG_NOTICE,"Editor: %i - Asset Manager: %i - Chatroom: %i",isOverCodeEditor,isOverAssetLibrary,isOverChatroom);

    #ifdef MOSAIC_ENABLE_PROFILING
    TracyPlotConfig("MosaicFPS", tracy::PlotFormatType::Number);
    TracyPlot("MosaicFPS", ofGetFrameRate());
    #endif

}

//--------------------------------------------------------------
void ofApp::draw(){

    #ifdef MOSAIC_ENABLE_PROFILING
    ZoneScopedN("ofApp::Draw()");
    #endif

    ofBackground(20);
    ofFill();
    ofSetLineWidth(1);

    // BACKGROUND GUI

    // canvas grid (TouchDesigner style)
    ofSetColor(255,255,255,6);
    ofSetLineWidth(1);
    for(int i=0;i<60;i++){
        ofDrawLine(ofGetWindowWidth()/30 * i,0,ofGetWindowWidth()/30 * i,ofGetWindowHeight());
        ofDrawLine(0,ofGetWindowWidth()/30 * i,ofGetWindowWidth(),ofGetWindowWidth()/30 * i);
    }

    // Logo
    ofSetColor(255,255,255,16);
    mosaicLogo->draw(ofGetWindowWidth()/2 - (128*retinaScale),(ofGetWindowHeight()- (240*retinaScale))/2 - (128*retinaScale),256*retinaScale,256*retinaScale);

    // Mosaic Visual Programming
    ofSetColor(255,255,255);
    if(!visualProgramming->bLoadingNewPatch){

        // Draw to vp Gui
        visualProgramming->draw();

        // draw main GUI interface
        drawImGuiInterface();

        visualProgramming->closeDrawMainMenu();

    }

    // Bottom INFO BAR --------------------------------------------------------------------------------------

    // DSP flag
    if(visualProgramming->dspON){
        ofSetColor(ofColor::fromHex(0xFFD00B));
        visualProgramming->font->drawString("DSP ON",10*retinaScale,ofGetHeight() - (6*retinaScale));
    }else{
        ofSetColor(ofColor::fromHex(0x777777));
        visualProgramming->font->drawString("DSP OFF",10*retinaScale,ofGetHeight() - (6*retinaScale));
    }

    // Last LOG on bottom bar
    string tmpMsg = mosaicLoggerChannel->GetLastLog();
    if(tmpMsg.find("[warning") != std::string::npos) {
        ofSetColor(255, 127, 0);
    }else if(tmpMsg.find("[ error") != std::string::npos || tmpMsg.find("[ fatal") != std::string::npos) {
        ofSetColor(255, 45, 45);
    }else{
        ofSetColor(220,220,220);
    }

    // FORCE CUSTOM VERBOSE
    if(tmpMsg.find("[verbose]") != std::string::npos){
        ofSetColor(60, 255, 60);
    }
    visualProgramming->font->drawString(tmpMsg,100*retinaScale,ofGetHeight() - (6*retinaScale));
    // ------------------------------------------------------------------------------------------------------

    #ifdef MOSAIC_ENABLE_PROFILING
    FrameMark; // Tracy end of frame
    #endif

}

//--------------------------------------------------------------
void ofApp::drawImGuiInterface(){

    //mainMenu.begin();

    {

        // Fullscreen transparent DockSpace
        static bool showDockspace = true;
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBackground;
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(ImVec2(viewport->WorkSize.x,viewport->WorkSize.y-(20*retinaScale)));
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;

        ImGui::Begin("DockSpace", &showDockspace, window_flags);
        ImGui::PopStyleVar(3);

        ImGui::SetNextWindowBgAlpha(0.0f);
        ImGui::DockSpace(ImGui::GetID("MosaicDockSpace"), ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None|ImGuiDockNodeFlags_PassthruCentralNode);

        ImGui::BeginMainMenuBar();

        {

            openPatch           = false;
            savePatchAs         = false;
            openAutoloadPatch   = false;
            takeScreenshot      = false;

            if(ImGui::BeginMenu( "File")){
                if(ImGui::MenuItem( "New patch",ofToString(shortcutFunc+"+N").c_str())){
                    visualProgramming->newPatch(ofToString(VERSION_GRAPHIC));
                    ofFile temp(visualProgramming->currentPatchFile);
                    assetFolder.reset();
                    assetFolder.listDir(temp.getEnclosingDirectory()+"data/");
                    assetFolder.sort();
                    assetWatcher.removeAllPaths();
                    assetWatcher.addPath(temp.getEnclosingDirectory()+"data/");
                }
                ImGui::Separator();
                if(ImGui::MenuItem( "Open patch" )){
                    openPatch = true;
                }
                ImGui::Separator();
                if(ImGui::MenuItem( "Save patch As.." )){
                    savePatchAs = true;
                }
                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Separator();
                ImGui::Spacing();

                if(ImGui::BeginMenu( "Autoload")){

                    if(ImGui::MenuItem( "Set autoload patch" )){
                        openAutoloadPatch = true;
                    }
                    ImGui::Separator();
                    if(ImGui::MenuItem( "Remove autoload patch" )){
                        autoloadPatchFile = "";
                        autoloadDelaySeconds = 1;
                        setAutoloadConfig();
                    }
                    ImGui::Spacing();
                    ImGui::Spacing();
                    if(ImGui::DragInt("Delay ( Seconds )",&autoloadDelaySeconds)){
                        if(autoloadDelaySeconds < 1){
                            autoloadDelaySeconds = 1;
                        }
                    }
                    ImGui::Spacing();
                    ImGui::Spacing();
                    if(autoloadPatchFile == ""){
                        ImGui::Text("no patch in autoload mode");
                    }else{
                        ImGui::Text("%s",_apf.getFileName().c_str());
                        if (ImGui::IsItemHovered()) ImGui::SetTooltip("%s",_apf.getAbsolutePath().c_str());
                    }
                    ImGui::Spacing();
                    ImGui::Spacing();
                    if(ImGui::Button("APPLY",ImVec2(-1,26*retinaScale))){
                        setAutoloadConfig();
                    }

                    ImGui::EndMenu();
                }

                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Separator();
                ImGui::Spacing();
                if(ImGui::MenuItem( "Quit",ofToString(shortcutFunc+"+Q").c_str())){
                    quitMosaic();
                }
                ImGui::EndMenu();
            }

            if(ImGui::BeginMenu( "Objects")){
                ofxVPObjects::factory::objectCategories& objectsMatrix = ofxVPObjects::factory::getCategories();
                for(ofxVPObjects::factory::objectCategories::iterator it = objectsMatrix.begin(); it != objectsMatrix.end(); ++it ){
                    if(ImGui::BeginMenu(it->first.c_str())){
                        std::sort(it->second.begin(), it->second.end());
                        for(int j=0;j<static_cast<int>(it->second.size());j++){
                            if(it->second.at(j) != "audio device"){
                                if(ImGui::MenuItem(it->second.at(j).c_str())){
                                    visualProgramming->addObject(it->second.at(j),ofVec2f(visualProgramming->canvas.getMovingPoint().x + 200,visualProgramming->canvas.getMovingPoint().y + 200));
                                }
                            }
                        }
                        ImGui::EndMenu();
                    }
                }
                // MOST WANTED
                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Spacing();
                ImGui::Spacing();
                if(ImGui::MenuItem("bang",ofToString(shortcutFunc+"+1").c_str())){
                    visualProgramming->addObject("bang",ofVec2f(visualProgramming->canvas.getMovingPoint().x + 200,visualProgramming->canvas.getMovingPoint().y + 200));
                }
                if(ImGui::MenuItem("trigger",ofToString(shortcutFunc+"+2").c_str())){
                    visualProgramming->addObject("trigger",ofVec2f(visualProgramming->canvas.getMovingPoint().x + 200,visualProgramming->canvas.getMovingPoint().y + 200));
                }
                if(ImGui::MenuItem("number",ofToString(shortcutFunc+"+3").c_str())){
                    visualProgramming->addObject("number",ofVec2f(visualProgramming->canvas.getMovingPoint().x + 200,visualProgramming->canvas.getMovingPoint().y + 200));
                }
                if(ImGui::MenuItem("metronome",ofToString(shortcutFunc+"+4").c_str())){
                    visualProgramming->addObject("metronome",ofVec2f(visualProgramming->canvas.getMovingPoint().x + 200,visualProgramming->canvas.getMovingPoint().y + 200));
                }
                if(ImGui::MenuItem("video viewer",ofToString(shortcutFunc+"+5").c_str())){
                    visualProgramming->addObject("video viewer",ofVec2f(visualProgramming->canvas.getMovingPoint().x + 200,visualProgramming->canvas.getMovingPoint().y + 200));
                }
                if(ImGui::MenuItem("signal viewer",ofToString(shortcutFunc+"+6").c_str())){
                    visualProgramming->addObject("signal viewer",ofVec2f(visualProgramming->canvas.getMovingPoint().x + 200,visualProgramming->canvas.getMovingPoint().y + 200));
                }
                if(ImGui::MenuItem("audio analyzer",ofToString(shortcutFunc+"+7").c_str())){
                    visualProgramming->addObject("audio analyzer",ofVec2f(visualProgramming->canvas.getMovingPoint().x + 200,visualProgramming->canvas.getMovingPoint().y + 200));
                }
                if(ImGui::MenuItem("lua script",ofToString(shortcutFunc+"+8").c_str())){
                    visualProgramming->addObject("lua script",ofVec2f(visualProgramming->canvas.getMovingPoint().x + 200,visualProgramming->canvas.getMovingPoint().y + 200));
                }
                if(ImGui::MenuItem("output window",ofToString(shortcutFunc+"+9").c_str())){
                    visualProgramming->addObject("output window",ofVec2f(visualProgramming->canvas.getMovingPoint().x + 200,visualProgramming->canvas.getMovingPoint().y + 200));
                }
                ImGui::EndMenu();
            }

            if(ImGui::BeginMenu( "Examples")){
                #if defined(TARGET_OSX)
                examplesRoot.listDir(mosaicExamplesPath.string());
                #else
                examplesRoot.listDir(ofToDataPath("../examples"));
                #endif
                examplesRoot.sort();
                for(size_t i=0;i<examplesRoot.getFiles().size();i++){
                    createDirectoryNode(examplesRoot.getFiles().at(i));
                }

                ImGui::EndMenu();
            }


            if(ImGui::BeginMenu( "Sound")){
                if(ImGui::Checkbox("DSP",&visualProgramming->dspON)){
                    if(visualProgramming->dspON){
                        visualProgramming->activateDSP();
                    }else{
                        visualProgramming->deactivateDSP();
                    }
                }
                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Separator();
                ImGui::Spacing();
                if(ImGui::DragInt("TEMPO (BPM)",&mosaicBPM,1.0f,1)){
                    visualProgramming->bpm = mosaicBPM;
                    visualProgramming->engine->sequencer.setTempo(mosaicBPM);
                    visualProgramming->setPatchVariable("bpm",mosaicBPM);
                }
                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Separator();
                ImGui::Spacing();

                if(visualProgramming->audioDevicesStringIN.size() > 0){
                    static int inDev = visualProgramming->audioGUIINIndex;
                    if(ofxImGui::VectorCombo("Input Device", &inDev,visualProgramming->audioDevicesStringIN)){
                        visualProgramming->audioGUIINIndex = inDev;
                    }
                }else{
                    static vector<string> emptyInputDevice = {"  No audio input device available"};
                    static int inDev = 0;
                    if(ofxImGui::VectorCombo("Input Device", &inDev,emptyInputDevice)){}
                }

                if(visualProgramming->audioDevicesStringOUT.size() > 0){
                    static int outDev = visualProgramming->audioGUIOUTIndex;
                    if(ofxImGui::VectorCombo("Output Device", &outDev,visualProgramming->audioDevicesStringOUT)){
                        visualProgramming->audioGUIOUTIndex = outDev;
                    }
                }else{
                    static vector<string> emptyOutputDevice = {"  No audio output device available"};
                    static int outDev = 0;
                    if(ofxImGui::VectorCombo("Output Device", &outDev,emptyOutputDevice)){}
                }

                if(visualProgramming->audioDevicesSR.size() > 0){
                    static int adSR = visualProgramming->audioGUISRIndex;
                    if(ofxImGui::VectorCombo("Sample Rate", &adSR,visualProgramming->audioDevicesSR)){
                        visualProgramming->audioGUISRIndex = adSR;
                    }
                }

                if(visualProgramming->audioDevicesBS.size() > 0){
                    static int adBS= visualProgramming->audioGUIBSIndex;
                    if(ofxImGui::VectorCombo("Buffer Size", &adBS,visualProgramming->audioDevicesBS)){
                        visualProgramming->audioGUIBSIndex = adBS;
                    }
                }

                ImGui::Spacing();ImGui::Spacing();ImGui::Spacing();
                if(ImGui::Button("APPLY",ImVec2(224,26*retinaScale))){
                    visualProgramming->setAudioSampleRate(visualProgramming->audioGUISRIndex);
                    visualProgramming->setAudioBufferSize(visualProgramming->audioGUIBSIndex);
                    if(visualProgramming->audioDevicesStringIN.size() > 0){
                        visualProgramming->setAudioInDevice(visualProgramming->audioGUIINIndex);
                    }
                    if(visualProgramming->audioDevicesStringOUT.size() > 0){
                        visualProgramming->setAudioOutDevice(visualProgramming->audioGUIOUTIndex);
                    }
                    visualProgramming->reloadPatch();
                    ImGui::CloseCurrentPopup();
                }

                ImGui::EndMenu();
            }

            if(ImGui::BeginMenu("System")){
                if(ImGui::DragInt("FPS",&mosaicFPS,1.0f,1)){
                    setMosaicFrameRate(mosaicFPS);
                }

                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Separator();
                ImGui::Spacing();
                if(ImGui::Button("Screenshot", ImVec2(-1,26*retinaScale))){
                    takeScreenshot = true;
                }
                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Separator();
                ImGui::Spacing();
                if(ImGui::Button("Reset Canvas", ImVec2(-1,26*retinaScale))){
                    visualProgramming->resetCanvas();
                }
                ImGui::EndMenu();
            }

            if(ImGui::BeginMenu( "View")){
                if(ImGui::MenuItem("Asset Manager",ofToString(shortcutFunc+"+M").c_str())){
                    isAssetLibraryON = !isAssetLibraryON;
                    visualProgramming->setPatchVariable("AssetManager",static_cast<int>(isAssetLibraryON));
                }
                if(ImGui::MenuItem("Code Editor",ofToString(shortcutFunc+"+E").c_str())){
                    isCodeEditorON = !isCodeEditorON;
                    visualProgramming->setPatchVariable("CodeEditor",static_cast<int>(isCodeEditorON));
                }
                if(ImGui::MenuItem("Inspector",ofToString(shortcutFunc+"+I").c_str())){
                    visualProgramming->inspectorActive = !visualProgramming->inspectorActive;
                    visualProgramming->setPatchVariable("Inspector",static_cast<int>(visualProgramming->inspectorActive));
                }
                if(ImGui::MenuItem("Patch Navigator",ofToString(shortcutFunc+"+T").c_str())){
                    visualProgramming->navigationActive = !visualProgramming->navigationActive;
                    visualProgramming->setPatchVariable("PatchNavigator",static_cast<int>(visualProgramming->navigationActive));
                }
                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Spacing();
                if(ImGui::MenuItem("Logger",ofToString(shortcutFunc+"+L").c_str())){
                    isLoggerON = !isLoggerON;
                    visualProgramming->setPatchVariable("Logger",static_cast<int>(isLoggerON));
                }
                if(ImGui::MenuItem("Profiler",ofToString(shortcutFunc+"+P").c_str())){
                    visualProgramming->profilerActive = !visualProgramming->profilerActive;
                    visualProgramming->setPatchVariable("Profiler",static_cast<int>(visualProgramming->profilerActive));
                }
                if(ImGui::MenuItem("Object Selector",ofToString(shortcutFunc+"+O").c_str())){
                    showRightClickMenu = !showRightClickMenu;
                }
                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Spacing();
                if(ImGui::MenuItem("Chatroom",ofToString(shortcutFunc+"+D").c_str())){
                    isChatroomON = !isChatroomON;
                }
                ImGui::EndMenu();
            }

            if(ImGui::BeginMenu( "Help")){
                if(ImGui::MenuItem("Mosaic Github")){
                    ofLaunchBrowser("https://github.com/d3cod3/Mosaic");
                }
                if(ImGui::MenuItem("Mosaic WIKI")){
                    ofLaunchBrowser("https://github.com/d3cod3/Mosaic/wiki");
                }
                if(ImGui::MenuItem("Mosaic Manual")){
                    ofLaunchBrowser("https://mosaic.d3cod3.org/manual/");
                }
                if(ImGui::MenuItem("Mosaic Reference")){
                    ofLaunchBrowser("https://mosaic.d3cod3.org/#reference");
                }
                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Separator();
                ImGui::Spacing();
                if(ImGui::MenuItem("OF Reference")){
                    ofLaunchBrowser("https://openframeworks.cc/documentation/");
                }
                if(ImGui::MenuItem("ofxAddons")){
                    ofLaunchBrowser("http://ofxaddons.com/categories");
                }
                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Separator();
                ImGui::Spacing();
                if(ImGui::MenuItem("About Mosaic")){
                    showAboutWindow = !showAboutWindow;
                }
                ImGui::EndMenu();
            }

            // File dialogs
            if(openPatch) ImGui::OpenPopup("Open patch");
            if(savePatchAs) ImGui::OpenPopup("Save patch");
            if(openAutoloadPatch) ImGui::OpenPopup("Set autoload patch");
            if(takeScreenshot) ImGui::OpenPopup("Take screenshot");

            // open patch
            if( fileDialog.showFileDialog("Open patch", imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(FILE_DIALOG_WIDTH*retinaScale, FILE_DIALOG_HEIGHT*retinaScale), ".xml") ){
                ofFile file(fileDialog.selected_path);
                if (file.exists()){
                    string fileExtension = ofToUpper(file.getExtension());
                    if(fileExtension == "XML") {
                        ofxXmlSettings XML;
#if OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR < 12
                        if (XML.loadFile(file.getAbsolutePath())){
#else
                        if (XML.load(file.getAbsolutePath())){
#endif

                            if (XML.getValue("www","") == "https://mosaic.d3cod3.org"){
                                patchToLoad = file.getAbsolutePath();
                                loadNewPatch = true;
                            }else{
                                ofLog(OF_LOG_ERROR, "The opened file: %s, is not a Mosaic patch!",file.getAbsolutePath().c_str());
                            }
                        }
                    }
                }
            }

            // set autoload patch
            if( fileDialog.showFileDialog("Set autoload patch", imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(FILE_DIALOG_WIDTH*retinaScale, FILE_DIALOG_HEIGHT*retinaScale), ".xml") ){
                ofFile file(fileDialog.selected_path);
                if (file.exists()){
                    string fileExtension = ofToUpper(file.getExtension());
                    if(fileExtension == "XML") {
                        ofxXmlSettings XML;
#if OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR < 12
                        if (XML.loadFile(file.getAbsolutePath())){
#else
                        if (XML.load(file.getAbsolutePath())){
#endif
                            if (XML.getValue("www","") == "https://mosaic.d3cod3.org"){
                                autoloadPatchFile = file.getAbsolutePath();
                                _apf.open(autoloadPatchFile);
                            }else{
                                ofLog(OF_LOG_ERROR, "The opened file: %s, is not a Mosaic patch!",file.getAbsolutePath().c_str());
                            }
                        }
                    }
                }
            }

            // save patch
            string newFileName = "mosaicPatch_"+ofGetTimestampString("%y%m%d")+".xml";
            if( fileDialog.showFileDialog("Save patch", imgui_addons::ImGuiFileBrowser::DialogMode::SAVE, ImVec2(FILE_DIALOG_WIDTH*retinaScale, FILE_DIALOG_HEIGHT*retinaScale), ".xml", newFileName) ){
                ofFile file(fileDialog.selected_path);
                visualProgramming->savePatchAs(file.getAbsolutePath());
                assetFolder.reset();
                assetFolder.listDir(visualProgramming->currentPatchFolderPath+"/data/");
                assetFolder.sort();
                assetWatcher.removeAllPaths();
                assetWatcher.addPath(visualProgramming->currentPatchFolderPath+"/data/");
            }

            // take patch screenshot
            string newShotName = "mosaicScreenshot_"+ofGetTimestampString("%y%m%d")+".jpg";
            if( fileDialog.showFileDialog("Take screenshot", imgui_addons::ImGuiFileBrowser::DialogMode::SAVE, ImVec2(FILE_DIALOG_WIDTH*retinaScale, FILE_DIALOG_HEIGHT*retinaScale), ".jpg", newShotName) ){
                ofFile file(fileDialog.selected_path);
                lastScreenshot = file.getAbsolutePath();
                saveNewScreenshot = true;
                resetScreenshotTime = ofGetElapsedTimeMillis();
            }

        }

        ImGui::EndMainMenuBar();

        // About window
        if(showAboutWindow){

            //ImGui::SetNextWindowPos(ImVec2((ofGetWidth()-(400*retinaScale))*.5f,(ofGetHeight()-(400*retinaScale))*.5f), ImGuiCond_Appearing );
            //ImGui::SetNextWindowSize(ImVec2(400*retinaScale,400*retinaScale), ImGuiCond_Appearing );

            if( ImGui::Begin("About Mosaic", &showAboutWindow, ImGuiWindowFlags_NoCollapse ) ){

                if(mosaicLogo && mosaicLogo->isAllocated() && mosaicLogoID && mosaicLogo->getWidth()!=0 ){
                    float ratio = (150.f*retinaScale) / mosaicLogo->getWidth();
                    ImGui::Image(GetImTextureID(mosaicLogoID), ImVec2(mosaicLogo->getWidth()*ratio, mosaicLogo->getHeight()*ratio));
                }
                ImGui::Text( "%s", PACKAGE);
                ImGui::Text( "Version %s (%s)", VERSION, VERSION_GRAPHIC );
                ImGui::Spacing();
                ImGui::TextWrapped( DESCRIPTION );
                ImGui::TextWrapped( "an open project by Emanuele Mazza aka n3m3da" );
                ImGui::TextWrapped( MOSAIC_WWW );
                ImGui::TextWrapped( "Developers: %s", MOSAIC_DEVELOPERS );
                ImGui::Spacing();
                ImGui::Text(" ");
                ImGui::Spacing();

                if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None)){

                    if (ImGui::BeginTabItem("Build Info")){

                        ImGui::TextWrapped("Feel free to include the following information in bug reports.");
                        bool copy_to_clipboard = ImGui::Button("Copy to clipboard");

                        ImGui::Spacing();
                        ImGui::BeginChild(ImGui::GetID("Build Configuration"), ImVec2(0, ImGui::GetTextLineHeightWithSpacing() * (18*retinaScale)), ImGuiWindowFlags_NoMove);
                        if (copy_to_clipboard){
                            ImGui::LogToClipboard();
                        }
#ifdef DEBUG
#define BUILDVARIANT "Debug"
#else
#define BUILDVARIANT "Release"
#endif
                        ImGui::Text( "%s version %s (%s) (%s build)", PACKAGE, VERSION, VERSION_GRAPHIC , BUILDVARIANT );
                        ImGui::Separator();
#ifdef _WIN32
                        ImGui::Text("define: _WIN32");
#endif
#ifdef _WIN64
                        ImGui::Text("define: _WIN64");
#endif
#ifdef __linux__
                        ImGui::Text("define: __linux__");
#endif
#ifdef __APPLE__
                        ImGui::Text("define: __APPLE__");
#endif
#ifdef _MSC_VER
                        ImGui::Text("define: _MSC_VER=%d", _MSC_VER);
#endif
#ifdef __MINGW32__
                        ImGui::Text("define: __MINGW32__");
#endif
#ifdef __MINGW64__
                        ImGui::Text("define: __MINGW64__");
#endif
#ifdef __GNUC__
                        ImGui::Text("define: __GNUC__=%d", (int)__GNUC__);
#endif
                        ImGui::Text("define: __cplusplus=%d", (int)__cplusplus);

                        ImGui::Separator();

                        // GPU information
                        ImGui::Text("GPU Information:");
                        static bool isProgrammable = ofIsGLProgrammableRenderer();

                        static int minor; static int major;

                        //glfwGetVersion(&minor, &major, nullptr); // Old way, seems to return maximal version (tested with GLFW 3.4)
                        major = ofGetGLRenderer()->getGLVersionMajor();
                        minor = ofGetGLRenderer()->getGLVersionMinor();
#ifdef TARGET_OPENGLES
                        ImGui::Text("GL ES %d.%d (fixed pipeline)", major, minor);
#else
                        ImGui::Text("GL SL %d.%d (programmable)", major, minor);
#endif

                        // Note: ofGLSLVersionFromGL is very outdated... we do it manually here.
                        const char* glsl_name = "Unknown";
                        const char* glsl_version = "Unknown";
                        // ofGLSLVersionFromGL is very outdated... we do it manually here.
                        // See imgui_impl_opengl3.cpp
                        //----------------------------------------
                        // OpenGL    GLSL      GLSL
                        // version   version   string
                        //----------------------------------------
                        //  2.0       110       "#version 110"
                        //  2.1       120       "#version 120"
                        //  3.0       130       "#version 130"
                        //  3.1       140       "#version 140"
                        //  3.2       150       "#version 150"
                        //  3.3       330       "#version 330 core"
                        //  4.0       400       "#version 400 core"
                        //  4.1       410       "#version 410 core"
                        //  4.2       420       "#version 410 core"
                        //  4.3       430       "#version 430 core"
                        //  ES 2.0    100       "#version 100"      = WebGL 1.0
                        //  ES 3.0    300       "#version 300 es"   = WebGL 2.0
                        //----------------------------------------


#ifdef TARGET_OPENGLES
                        if( isProgrammable ){
                            if( major==2 ){
                                glsl_version = "#version 100";
                                glsl_name = "GL ES 2";
                            }
                            else if( major==3 ){ // Note: not yet available in oF !!!
                                glsl_version = "#version 300 es";
                                glsl_name = "GL ES 3";
                            }
                        }
                        else {
                            glsl_name = "GL ES 1";
                            glsl_version = "none";
                        }
#else
                        if( isProgrammable ){
                            if( major==3 ){
                                glsl_name = "GLSL 3";

                                if( minor==0 )      glsl_version="#version 130";
                                else if( minor==1 ) glsl_version="#version 140";
                                else if( minor==2 ) glsl_version="#version 150";
                                else if( minor==3 ) glsl_version="#version 330 core";
                            }
                            else if( major==4 ){
                                glsl_name = "GLSL 4";
                                if( minor==0 )      glsl_version="#version 400 core";
                                else if( minor==1 ) glsl_version="#version 410 core";
                                else if( minor==2 ) glsl_version="#version 420 core";
                                else if( minor==3 ) glsl_version="#version 430 core";
                            }
                        }
                        else {
                            glsl_name = "GL 2";
                            glsl_version = "none";
                        }
#endif
                        ImGui::Text("Shaders: %s (%s)", glsl_name, glsl_version);

                        // Some info is double, but needs to be tested what works best in multiple environments
                        ImGui::Text( "Vendor : %s", glGetString(GL_VENDOR) );
                        ImGui::Text( "GPU : %s", glGetString(GL_RENDERER) );
                        ImGui::Text( "OpenGL ver. %s", glGetString(GL_VERSION) ); // alt: glGetString(GL_MAJOR_VERSION), glGetString(GL_MINOR_VERSION)
                        ImGui::Text( "GLSL ver. %s / %s", glGetString(GL_SHADING_LANGUAGE_VERSION), ofGLSLVersionFromGL(major, minor).c_str() );
                        static int numExtensions = 0;
                        std::string extensions = "";
                        glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
                        for(int i = 0; i<numExtensions; ++i){
                            if(i!=0) extensions.append(", ");
                            extensions.append( (char*)glGetStringi(GL_EXTENSIONS, i) );
                        }
                        ImGui::TextWrapped( "GL Extensions (%d) :\n%s", numExtensions, extensions.c_str());//, glGetString(GL_EXTENSIONS) );
                        ImGui::Separator();
                        ImGui::Separator();

                        // Installed objects

                        ofxVPObjects::factory::objectCategories& objectsMatrix = ofxVPObjects::factory::getCategories();
                        for(ofxVPObjects::factory::objectCategories::iterator it = objectsMatrix.begin(); it != objectsMatrix.end(); ++it ){
                            if(it->second.size()<1) continue;

                            for(auto objIt=it->second.begin(); objIt!=it->second.end(); ++objIt){
                                ImGui::Text("object/%s: %s", it->first.c_str(), (*objIt).c_str() );
                            }
                        }

                        ImGui::Spacing();

                        // End
                        if (copy_to_clipboard){
                            ImGui::LogFinish();
                        }
                        ImGui::EndChild();

                        ImGui::EndTabItem();
                    }

                    if(ImGui::BeginTabItem("Monitor")){
                        // Monitor information
                        ImGui::Spacing();
                        ImGui::Text("Primary Monitor:");
                        ImGui::Spacing();
                        ImGui::Text("Resolution: %sx%s", ofToString(wRes).c_str(),ofToString(hRes).c_str());
                        ImGui::Text("Physical Dimensions: %sx%s mm", ofToString(wScreenMM).c_str(),ofToString(hScreenMM).c_str());
                        ImGui::Text("Retina Scale ( Retina Screens ): %s",ofToString(retinaScale).c_str());
                        ImGui::Text("Screen Content Scale ( OS managed, accessibility ): %s",ofToString(xScreenContentScale).c_str());
                        ImGui::Text("Pixel density ( Resolution over Physical Size): %s",ofToString(pixelsxMM).c_str());
                        ImGui::Text("Suggested font size: %s",ofToString(suggestedFontSize+(4*retinaScale)).c_str());

                        ImGui::EndTabItem();
                    }

                    if (ImGui::BeginTabItem("Objects")){
                        ImGui::TextWrapped("This version of Mosaic has been built with the following objects :" );
                        ImGui::Spacing();

                        ofxVPObjects::factory::objectCategories& objectsMatrix = ofxVPObjects::factory::getCategories();
                        if (objectsMatrix.size()>0){

                            ofxVPObjects::factory::objectCategories& objectsMatrix = ofxVPObjects::factory::getCategories();
                            for(ofxVPObjects::factory::objectCategories::iterator it = objectsMatrix.begin(); it != objectsMatrix.end(); ++it ){
                                if (ImGui::TreeNodeEx( it->first.c_str(), ImGuiTreeNodeFlags_DefaultOpen )){
                                    ImGui::Indent(10);
                                    for(auto objIt=it->second.begin(); objIt!=it->second.end(); ++objIt){
                                        ImGui::Text("%s", (*objIt).c_str());
                                    }
                                    ImGui::Unindent(10);
                                    ImGui::TreePop();
                                }
                            }
                        }
                        else {
                            ImGui::Text("There are no objects.");
                        }

                        ImGui::EndTabItem();
                    }

                    ImGui::EndTabBar();
                }
            }
            ImGui::End(); // end showAboutWindow
        }

        // code editor
        if(isCodeEditorON){
            ImGui::SetNextWindowSize(ImVec2(640*retinaScale,640*retinaScale), ImGuiCond_Appearing);

            if( ImGui::Begin(ICON_FA_CODE "  Code Editor", &isCodeEditorON, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse) ){

                isOverCodeEditor = ImGui::IsWindowHovered(ImGuiHoveredFlags_RootWindow) || ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows);

                if(codeEditors.size() > 0){

                    auto cpos = codeEditors[editedFilesNames[actualCodeEditor]].GetCursorPosition();

                    if (ImGui::BeginMenuBar()){
                        if (ImGui::BeginMenu("File")){
                            if (ImGui::MenuItem("Save/Reload",ofToString(shortcutFunc+"+R").c_str())){
                                filesystem::path tempPath(editedFilesPaths[actualCodeEditor].c_str());

                                ofBuffer buff;
                                buff.set(codeEditors[editedFilesNames[actualCodeEditor]].GetText());

                                ofBufferToFile(tempPath,buff,false);
                            }
                            ImGui::EndMenu();
                        }
                        if (ImGui::BeginMenu("Edit")){
                            if (ImGui::MenuItem("Undo", ofToString(shortcutFunc+"+Z").c_str(), nullptr, codeEditors[editedFilesNames[actualCodeEditor]].CanUndo()))
                                codeEditors[editedFilesNames[actualCodeEditor]].Undo();
                            if (ImGui::MenuItem("Redo", ofToString(shortcutFunc+"+Y").c_str(), nullptr, codeEditors[editedFilesNames[actualCodeEditor]].CanRedo()))
                                codeEditors[editedFilesNames[actualCodeEditor]].Redo();

                            ImGui::Separator();

                            if (ImGui::MenuItem("Copy", ofToString(shortcutFunc+"+C").c_str(), nullptr, codeEditors[editedFilesNames[actualCodeEditor]].HasSelection()))
                                codeEditors[editedFilesNames[actualCodeEditor]].Copy();
                            if (ImGui::MenuItem("Cut", ofToString(shortcutFunc+"+X").c_str(), nullptr, codeEditors[editedFilesNames[actualCodeEditor]].HasSelection()))
                                codeEditors[editedFilesNames[actualCodeEditor]].Cut();
                            if (ImGui::MenuItem("Paste", ofToString(shortcutFunc+"+V").c_str(), nullptr, ImGui::GetClipboardText() != nullptr))
                                codeEditors[editedFilesNames[actualCodeEditor]].Paste();

                            ImGui::Separator();

                            if (ImGui::MenuItem("Select all", ofToString(shortcutFunc+"+A").c_str()))
                                codeEditors[editedFilesNames[actualCodeEditor]].SetSelection(TextEditor::Coordinates(), TextEditor::Coordinates(codeEditors[editedFilesNames[actualCodeEditor]].GetTotalLines(), 0));

                            ImGui::EndMenu();
                        }

                        if (ImGui::BeginMenu("Find")){
                            if (ImGui::MenuItem("Find and Replace")){
                                codeEditors[editedFilesNames[actualCodeEditor]].Find();
                            }

                            ImGui::EndMenu();
                        }

                        ImGui::EndMenuBar();
                    }

                    ImGui::Text("%6d/%-6d %6d lines | %s | %s", cpos.mLine + 1, cpos.mColumn + 1, codeEditors[editedFilesNames[actualCodeEditor]].GetTotalLines(), codeEditors[editedFilesNames[actualCodeEditor]].GetLanguageDefinition().mName.c_str(), editedFilesPaths[actualCodeEditor].c_str());

                    ImFont* tempfont = ImGui::GetIO().Fonts->Fonts[ImGui::GetIO().Fonts->Fonts.Size - 2];

                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Spacing();

                    ImGui::SliderFloat("Font scale", &tempfont->Scale, 1.0f, 2.0f);

                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Spacing();

                    if (ImGui::BeginTabBar("TabBar", ImGuiTabBarFlags_Reorderable | ImGuiTabBarFlags_AutoSelectNewTabs | ImGuiTabBarFlags_NoCloseWithMiddleMouseButton)){
                        for(int i=0;i<static_cast<int>(editedFilesNames.size());i++){
                            if (ImGui::BeginTabItem(editedFilesNames[i].c_str(), nullptr)){

                                if(ImGui::IsItemClicked() || ImGui::IsItemActive()){
                                    actualCodeEditor = i;
                                    actualEditedFilePath = editedFilesPaths[i];
                                    actualEditedFileName = editedFilesNames[i];
                                }

                                ImGui::PushFont(tempfont);

                                codeEditors[editedFilesNames[i]].Render("TextEditor");

                                ImGui::PopFont();

                                ImGui::EndTabItem();
                            }
                        }
                        ImGui::EndTabBar();
                    }

                }

            }
            ImGui::End(); // End code editor
        }else{
            isOverCodeEditor = false;
        }

        // asset manager window
        if(isAssetLibraryON){
            ImGui::SetNextWindowSize(ImVec2(640*retinaScale,320*retinaScale), ImGuiCond_Appearing);

            if( ImGui::Begin(ICON_FA_FOLDER "  Asset Manager", &isAssetLibraryON, ImGuiWindowFlags_NoCollapse) ){

                isOverAssetLibrary = ImGui::IsWindowHovered(ImGuiHoveredFlags_RootWindow) || ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows);

                static int selected = -1;
                static int node_clicked = -1;

                // button bar

                importAsset         = false;
                confirmAssetDelete  = false;
                assetWarning        = false;

                ImGui::Dummy(ImVec2(1,6*retinaScale));

                ImGui::Dummy(ImVec2(6*retinaScale,1)); ImGui::SameLine();
                if (ImGui::Button(ICON_FA_UPLOAD "  Add to patch") && selectedFile != ""){
                    ofFile tmpf(selectedFile);
                    if(tmpf.isFile()){
                        glm::vec3 temp = visualProgramming->canvas.screenToWorld(glm::vec3(ofGetWindowWidth()/2,ofGetWindowHeight()/2 + 100,0));
                        createObjectFromFile(tmpf,true,static_cast<int>(temp.x),static_cast<int>(temp.y));
                    }
                }
                isAddToPatchOver = ImGui::IsItemHovered();

                /*ImGui::SameLine(); ImGui::Dummy(ImVec2(6*retinaScale,1)); ImGui::SameLine();
                if (ImGui::Button(ICON_FA_FOLDER_PLUS "  Add folder")){
                    newDirName = "";
                    ImGui::OpenPopup("Add folder");
                }

                if(ImGui::BeginPopup("Add folder")){

                    if(ImGui::InputText("##NewDirNameInput", &newDirName,ImGuiInputTextFlags_EnterReturnsTrue)){
                        if(newDirName != ""){
                            // create directory
                            ofDirectory::createDirectory(assetFolder.getAbsolutePath()+"/"+newDirName,false,false);
                        }
                        ImGui::CloseCurrentPopup();
                    }
                    ImGui::SameLine();
                    if(ImGui::Button("Cancel")){
                        ImGui::CloseCurrentPopup();
                    }
                    ImGui::SameLine();
                    if(ImGui::Button("Create")){
                        if(newDirName != ""){
                            // create directory
                            ofDirectory::createDirectory(assetFolder.getAbsolutePath()+"/"+newDirName,false,false);
                        }
                        ImGui::CloseCurrentPopup();
                    }
                    ImGui::EndPopup();

                }*/

                ImGui::SameLine(); ImGui::Dummy(ImVec2(6*retinaScale,1)); ImGui::SameLine();

                if (ImGui::Button(ICON_FA_FILE_IMPORT "  Import asset")){
                    importAsset = true;
                }

                ImGui::SameLine(); ImGui::Dummy(ImVec2(6*retinaScale,1)); ImGui::SameLine();

                if (ImGui::Button(ICON_FA_TRASH_ALT "  Remove selected") && selectedFile != ""){
                    // file not used in patch, can be deleted
                    if(!checkFileUsedInPatch(selectedFile)){
                        confirmAssetDelete = true;
                    }else{ // file used in patch, show warning/info message
                        assetWarning = true;
                    }

                }

                // END button bar

                if(ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !ImGui::IsItemHovered() && !isAddToPatchOver && !isDeleteModalON){
                    selected = -1;
                    node_clicked = -1;
                    selectedFile = "";
                }

                if(confirmAssetDelete){
                    ImGui::OpenPopup("Confirm Delete");
                    isDeleteModalON = true;
                }

                if(assetWarning){
                    ImGui::OpenPopup("Warning! Asset In-Use");
                    isDeleteModalON = true;
                }

                if (ImGui::BeginPopupModal("Confirm Delete", NULL, ImGuiWindowFlags_NoDocking|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_AlwaysAutoResize)){
                    ofFile tmpf(selectedFile);
                    if(tmpf.isDirectory()){
                        ImGui::Text("Are you sure you want to delete\n%s\nfolder with all his content?\n\nThis operation cannot be undone!\n\n",selectedFile.c_str());
                    }else{
                        ImGui::Text("Are you sure you want to delete\n%s ?\n\nThis operation cannot be undone!\n\n",selectedFile.c_str());
                    }
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Separator();
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Spacing();

                    ImGui::SetCursorPosX(ImGui::GetWindowSize().x - (ImGui::CalcTextSize("Cancel Delete").x + (ImGui::GetStyle().FramePadding.x*4.0)) - ImGui::GetStyle().ItemSpacing.x - ImGui::GetStyle().WindowPadding.x);

                    if (ImGui::Button("Cancel")) {
                        isDeleteModalON = false;
                        ImGui::CloseCurrentPopup();
                    }
                    ImGui::SetItemDefaultFocus();
                    ImGui::SameLine();
                    ImGui::PushStyleColor(ImGuiCol_Button, VHS_RED);
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, VHS_RED_OVER);
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, VHS_RED_OVER);
                    if (ImGui::Button("Delete")) {
                        if(selectedFile != ""){
                            ofFile tmpr(selectedFile);
                            if(tmpr.isDirectory()){
                                tmpr.remove(true);
                            }else if(tmpr.isFile()){
                                tmpr.remove();
                            }
                            selected = -1;
                            node_clicked = -1;
                            selectedFile = "";
                        }
                        isDeleteModalON = false;

                        ImGui::CloseCurrentPopup();
                    }
                    ImGui::PopStyleColor(3);
                    ImGui::EndPopup();
                }

                if (ImGui::BeginPopupModal("Warning! Asset In-Use", NULL, ImGuiWindowFlags_NoDocking|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_AlwaysAutoResize)){

                    ImGui::Text("The selected file for removal:\n%s\n\nis currently used inside the patch!\n\nIf you want to remove this file, first disable/remove the related object from the patch.",selectedFile.c_str());

                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Separator();
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Spacing();

                    ImGui::SetCursorPosX(ImGui::GetWindowSize().x - (ImGui::CalcTextSize("Understood").x + (ImGui::GetStyle().FramePadding.x*2.0)) - ImGui::GetStyle().ItemSpacing.x - ImGui::GetStyle().WindowPadding.x);

                    if (ImGui::Button("Understood")) {
                        isDeleteModalON = false;
                        ImGui::CloseCurrentPopup();
                    }

                    ImGui::EndPopup();
                }

                // File dialog
                if(importAsset) ImGui::OpenPopup("Import asset");

                // import asset
                if( fileDialog.showFileDialog("Import asset", imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(FILE_DIALOG_WIDTH*retinaScale, FILE_DIALOG_HEIGHT*retinaScale), "*.*") ){
                    ofFile file(fileDialog.selected_path);
                    if (file.exists()){
#if defined (TARGET_WIN32)
                        copyFileToPatchFolder(assetFolder.getAbsolutePath()+"\\",file.getAbsolutePath());
#else
                        copyFileToPatchFolder(assetFolder.getAbsolutePath()+"/",file.getAbsolutePath());
#endif
                    }
                }

                ImGui::Dummy(ImVec2(1,16*retinaScale));

                if(assetFolder.size() == 0){
                    ImGui::Text("No assets loaded");
                }

                int listPos = 0;
                for(int i=0;i<static_cast<int>(assetFolder.size());i++){
                    if(assetFolder.getFile(i).isDirectory()){
                        string tmps = "\uf07b "+assetFolder.getName(i);
                        ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
                        if (node_clicked == i) node_flags |= ImGuiTreeNodeFlags_Selected;
                        bool node_open = ImGui::TreeNodeEx(tmps.c_str(), node_flags);
                        if (ImGui::IsItemClicked()){
                            node_clicked = i;
                            selected = -1;
                            selectedFile = assetFolder.getFile(i).getAbsolutePath();
                        }
                        if (node_open){
                            // list folder
                            ofDirectory tmp;
                            tmp.listDir(assetFolder.getFile(i).getAbsolutePath());
                            for(size_t t=0;t<tmp.size();t++){
                                ImGui::Dummy(ImVec2(1,2*retinaScale));
                                ImGui::Dummy(ImVec2(30*retinaScale,1)); ImGui::SameLine();
                                char buf[32];
                                sprintf_s(buf, "\uf15b %s", tmp.getName(t).c_str());
                                if (ImGui::Selectable(buf, selected == listPos)){
                                    selected = listPos;
                                    node_clicked = -1;
                                    selectedFile = tmp.getFile(t).getAbsolutePath();
                                }

                                listPos++;
                            }
                            ImGui::TreePop();
                        }

                        ImGui::Dummy(ImVec2(1,2*retinaScale));
                    }else{
                        char buf[32];
                        sprintf_s(buf, "\uf15b %s", assetFolder.getName(i).c_str());
                        ImGui::Dummy(ImVec2(14*retinaScale,1)); ImGui::SameLine();
                        if (ImGui::Selectable(buf, selected == listPos)){
                            selected = listPos;
                            node_clicked = -1;
                            selectedFile = assetFolder.getFile(i).getAbsolutePath();
                        }

                        ImGui::Dummy(ImVec2(1,2*retinaScale));
                    }

                    listPos++;

                }
            }

            ImGui::End(); // End Asset Manager window
        }

        // floating logger window
        if(isLoggerON){
            ImGui::SetNextWindowSize(ImVec2(640*retinaScale,320*retinaScale), ImGuiCond_Appearing);
            mosaicLoggerChannel->Draw(ICON_FA_TERMINAL "  Logger", &isLoggerON);
        }

        // Mosaic DHT Chatroom
        if(isChatroomON){
            ImGui::SetNextWindowSize(ImVec2(640*retinaScale,320*retinaScale), ImGuiCond_Appearing);

            if (ImGui::Begin("Chatroom",NULL,ImGuiWindowFlags_NoScrollbar)){

                isOverChatroom = ImGui::IsWindowHovered(ImGuiHoveredFlags_RootWindow) || ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows);

                // startup modal for choosing session username
                if(!initChatModal){
                    initChatModal = true;
                    ImGui::OpenPopup("Set user AKA for this chatroom session");
                }

                bool open = true;
                ImGui::SetNextWindowPos(ImVec2(ofGetWindowWidth()/2 - 150*retinaScale,ofGetWindowHeight()/2 - 50*retinaScale), ImGuiCond_Appearing);
                ImGui::SetNextWindowSize(ImVec2(300*retinaScale,100*retinaScale), ImGuiCond_Always);

                if (ImGui::BeginPopupModal("Set user AKA for this chatroom session", &open,ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoScrollbar|ImGuiWindowFlags_NoSavedSettings|ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_Modal)){

                    ImGui::TextColored(ImVec4(1,1,1,1),"Set user AKA for this chatroom session");
                    ImGui::Spacing();

                    ImGui::PushItemWidth(-1);
                    if(ImGui::InputTextWithHint("###aka","Leave empty if you want a random aka",&aka,ImGuiInputTextFlags_EnterReturnsTrue)){
                        if(aka != "" && checkAKAIsValid(aka)){ // if aka is not empty and is not already taken
                            participants[userID] = aka;
                        }else{
                            participants[userID] = userID;
                            aka = userID;
                        }
                        ImGui::CloseCurrentPopup();
                    }
                    ImGui::PopItemWidth();

                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Spacing();

                    ImGui::PushStyleColor(ImGuiCol_Button, VHS_DGRAY);
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, VHS_DGRAY_OVER);
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, VHS_DGRAY_OVER);
                    if (ImGui::Button("Join",ImVec2(80*retinaScale,-1))){
                        if(aka != "" && checkAKAIsValid(aka)){ // if aka is not empty and is not already taken
                            participants[userID] = aka;
                        }else{
                            participants[userID] = userID;
                            aka = userID;
                        }
                        ImGui::CloseCurrentPopup();
                    }
                    ImGui::PopStyleColor(3);
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::EndPopup();
                }

                // main GUI
                static int selected = 0;
                int counter = 0;
                ImGui::BeginChild("participants", ImVec2((640*retinaScale)/5, 0),ImGuiChildFlags_ResizeX);
                for(std::map<std::string,std::string>::iterator it = participants.begin(); it != participants.end(); it++ ){
                    if (ImGui::Selectable(it->second.c_str(), selected == counter)){
                        selected = counter;
                    }
                    if (ImGui::BeginPopupContextItem()){
                        ImGui::Text("%s",it->first.c_str());
                        ImGui::Spacing();
                        ImGui::Text("%s",it->second.c_str());
                        if(activeChats.find(it->first) == activeChats.end() && it->first != userID){
                            ImGui::Spacing();
                            ImGui::Separator();
                            ImGui::Spacing();
                            if(ImGui::Button("New Private Chat",ImVec2(200*retinaScale,26*retinaScale))){
                                TextEditor newPrivateChat;
                                newPrivateChat.SetShowWhitespaces(false);
                                newPrivateChat.SetText("");
                                newPrivateChat.SetReadOnly(true);
                                newPrivateChat.SetShowLineNumbers(false);
                                newPrivateChat.SetPalette(TextEditor::GetMosaicPalette());
                                newPrivateChat.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());

                                activeChats.insert( pair<string,TextEditor>(it->first,newPrivateChat) );
                                ImGui::CloseCurrentPopup();
                            }
                        }

                        ImGui::EndPopup();
                    }
                    counter++;
                }
                ImGui::EndChild();

                ImGui::SameLine();

                ImGui::BeginChild("chat view", ImVec2(0,0));
                if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_Reorderable|ImGuiTabBarFlags_AutoSelectNewTabs|ImGuiTabBarFlags_TabListPopupButton)){

                    //static bool opened[4] = { true, true, true, true }; // Persistent user state

                    if (ImGui::BeginPopupContextWindow()){
                        if (ImGui::MenuItem("Paste", nullptr, nullptr, ImGui::GetClipboardText() != nullptr)){
                            chat_message = ImGui::GetClipboardText();
                            setFocusOnMessageInput = true;
                        }
                        ImGui::EndPopup();
                    }

                    for(std::map<std::string,TextEditor>::iterator it = activeChats.begin(); it != activeChats.end(); it++ ){
                        string tabName = "";
                        if(it->first == chatname.c_str()){
                            tabName = it->first;
                        }else{
                            tabName = participants[it->first];
                        }

                        if (ImGui::BeginTabItem(tabName.c_str())){
                            string tempLabel = "###chat_"+it->first;

                            //ImGui::InputTextMultiline(tempLabel.c_str(),&it->second,ImVec2(-1.0, -36*retinaScale),ImGuiInputTextFlags_ReadOnly);
                            activeChats[it->first].Render(tempLabel.c_str(),ImVec2(-1.0, -36*retinaScale));

                            if(!activeChats[it->first].IsWindowFocused()){
                                activeChats[it->first].SetCursorPosition(TextEditor::Coordinates((int)activeChats[it->first].GetTotalLines(), 0));
                            }

                            ImGui::Spacing();
                            ImGui::Separator();
                            ImGui::Spacing();

                            ImGui::PushItemWidth(-80*retinaScale);
                            if(setFocusOnMessageInput){
                                setFocusOnMessageInput = false;
                                ImGui::SetKeyboardFocusHere();
                            }
                            if(ImGui::InputTextWithHint("###message","Write a message...",&chat_message,ImGuiInputTextFlags_EnterReturnsTrue)){

                                if(chat_message != ""){
                                    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

                                    if(it->first == chatname.c_str()){
                                        activeChats[it->first].InsertText("["+ofGetTimestampString("%H-%M-%S")+"] <" + aka + ">\t" + chat_message + "\n");

                                        dht.dhtNode.putSigned(room, dht::ImMessage(rand_id(rd), std::move("<"+aka+"> "+chat_message), now));
                                    }else{
                                        activeChats[it->first].InsertText("["+ofGetTimestampString("%H-%M-%S")+"]\t" + chat_message + "\n");

                                        dht.dhtNode.putEncrypted(room, dht::InfoHash(it->first), dht::ImMessage(rand_id(rd), std::move("<"+aka+"> "+chat_message), now));
                                    }
                                }
                                // clear previuos message
                                chat_message = "";
                            }

                            ImGui::PopItemWidth();

                            ImGui::SameLine();

                            ImGui::PushStyleColor(ImGuiCol_Button, VHS_DGRAY);
                            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, VHS_DGRAY_OVER);
                            ImGui::PushStyleColor(ImGuiCol_ButtonActive, VHS_DGRAY_OVER);
                            if(ImGui::Button("SEND",ImVec2(70*retinaScale,-1))){
                                if(chat_message != ""){
                                    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

                                    if(it->first == chatname.c_str()){
                                        activeChats[it->first].InsertText("["+ofGetTimestampString("%H-%M-%S")+"] <" + aka + ">\t" + chat_message + "\n");

                                        dht.dhtNode.putSigned(room, dht::ImMessage(rand_id(rd), std::move("<"+aka+"> "+chat_message), now));
                                    }else{
                                        activeChats[it->first].InsertText("["+ofGetTimestampString("%H-%M-%S")+"]\t" + chat_message + "\n");

                                        dht.dhtNode.putEncrypted(room, dht::InfoHash(it->first), dht::ImMessage(rand_id(rd), std::move("<"+aka+"> "+chat_message), now));
                                    }
                                }
                                // clear previuos message
                                chat_message = "";
                            }
                            ImGui::PopStyleColor(3);

                            ImGui::EndTabItem();
                        }
                    }
                    ImGui::EndTabBar();
                }
                ImGui::EndChild();
            }
            ImGui::End();
        }else{
            isOverChatroom = false;
            chat_message = "";
        }

        // right click menu
        if(showRightClickMenu){
            ImGui::SetNextWindowSize(ImVec2(200*retinaScale,280*retinaScale), ImGuiCond_Appearing);
            ImGui::SetNextWindowPos(ImVec2(ofGetMouseX(),ofGetMouseY()), ImGuiCond_Appearing);

            if(ImGui::Begin("Objects", &showRightClickMenu,ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse) ){

                static ImGuiTextFilter filter;
                filter.Draw("Search");
                bool bIsFiltering = filter.IsActive();

                bool bApplyFilter = false;
                if( createSearchedObject ){
                    createSearchedObject = false;
                    bApplyFilter = true;
                    bIsFiltering = true;
                }
                bool bDidSelectObject = false;

                string tempFilter = filter.InputBuf;
                if(tempFilter == ""){
                    bApplyFilter = false;
                    bIsFiltering = false;
                }

                ofxVPObjects::factory::objectCategories& objectsMatrix = ofxVPObjects::factory::getCategories();
                for(ofxVPObjects::factory::objectCategories::iterator it = objectsMatrix.begin(); it != objectsMatrix.end(); ++it ){
                    if(!bIsFiltering){
                        if(ImGui::BeginMenu(it->first.c_str())){
                            std::set<std::string> tempSecond; // for alphabetical sort
                            for(int j=0;j<static_cast<int>(it->second.size());j++){
                                tempSecond.emplace(it->second.at(j));
                            }
                            for(auto const &on : tempSecond){
                                // show items
                                if(on != "audio device"){
                                    if(ImGui::MenuItem(on.c_str())){
                                        visualProgramming->addObject(on,ofVec2f(visualProgramming->canvas.getMovingPoint().x + 200,visualProgramming->canvas.getMovingPoint().y + 200));
                                        //showRightClickMenu = false;
                                    }
                                }
                            }
                            ImGui::EndMenu();
                        }
                    }
                    else {
                        bool bCatPrinted = false;
                        for(int j=0;j<static_cast<int>(it->second.size());j++){
                            // filter items
                            if (!filter.PassFilter(it->second.at(j).c_str()))
                                continue;

                            // show sub cat
                            if( !bCatPrinted ){
                                bCatPrinted = ImGui::TreeNodeEx(it->first.c_str(), ImGuiTreeNodeFlags_DefaultOpen );
                            }
                            // show items
                            ImGuiTreeNodeFlags tmpFlags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
                            if(!bDidSelectObject) tmpFlags |= ImGuiTreeNodeFlags_Selected;
                            if(it->second.at(j) != "audio device"){
                                if(ImGui::TreeNodeEx(it->second.at(j).c_str(), tmpFlags)){
                                    // choose by click or pick first one
                                    if (ImGui::IsItemClicked() || bApplyFilter){
                                        visualProgramming->addObject(it->second.at(j),ofVec2f(visualProgramming->canvas.getMovingPoint().x + (200*retinaScale),visualProgramming->canvas.getMovingPoint().y + (200*retinaScale)));
                                        //showRightClickMenu = false;
                                        bApplyFilter = false;
                                        filter.Clear();
                                        break;
                                    }
                                }
                            }
                            bDidSelectObject = true;


                        }
                        if(bCatPrinted){
                            ImGui::TreePop();
                        }
                    }
                }

                // at this point, if apply filter is true, there was no match, reset search.
                if(bApplyFilter){
                    filter.Clear();
                }

            }

            ImGui::End(); // End  "Objects"

        }

        // PROFILER
        if(visualProgramming->profilerActive){
            visualProgramming->profiler.Render(&visualProgramming->profilerActive);
        }

        // INSPECTOR
        if(visualProgramming->inspectorActive){
            if(visualProgramming->isCanvasVisible){
                visualProgramming->drawInspector();
            }
        }

        // PATCH NAVIGATOR
        if(visualProgramming->navigationActive){
            if(visualProgramming->isCanvasVisible){
                visualProgramming->drawSubpatchNavigation();
            }
        }

        ImGui::End(); // End "DockSpace"

    }

    //mainMenu.end();
}

//--------------------------------------------------------------
void ofApp::exit() {

    visualProgramming->setPatchVariable("AssetManager",static_cast<int>(isAssetLibraryON));
    visualProgramming->setPatchVariable("CodeEditor",static_cast<int>(isCodeEditorON));
    visualProgramming->setPatchVariable("Inspector",static_cast<int>(visualProgramming->inspectorActive));
    visualProgramming->setPatchVariable("Logger",static_cast<int>(isLoggerON));
    visualProgramming->setPatchVariable("Profiler",static_cast<int>(visualProgramming->profilerActive));
    visualProgramming->setPatchVariable("PatchNavigator",static_cast<int>(visualProgramming->navigationActive));

    ImGui::SaveIniSettingsToDisk(iniFilePath.c_str());

    for(map<string,PathWatcher*>::iterator it = codeWatchers.begin(); it != codeWatchers.end(); it++ ){
        it->second->removeAllPaths();
        it->second->stop();
    }

    closeDHTNode();

    codeEditors.clear();
    codeWatchers.clear();

    visualProgramming->exit();
}

//--------------------------------------------------------------
void ofApp::keyPressed(ofKeyEventArgs &e){

    // new patch ( MOD_KEY-n )
    if(e.hasModifier(MOD_KEY) && e.keycode == 78) {
        visualProgramming->newPatch(ofToString(VERSION_GRAPHIC));

    }
    // code-editor SAVE/RELOAD ( MOD_KEY-r )
    else if(e.hasModifier(MOD_KEY) && e.keycode == 82 && isCodeEditorON && isOverCodeEditor && !codeEditors.empty()){
        filesystem::path tempPath(editedFilesPaths[actualCodeEditor].c_str());
        ofBuffer buff;
        buff.set(codeEditors[editedFilesNames[actualCodeEditor]].GetText());
        ofBufferToFile(tempPath,buff,false);
    }
    // code-editor UNDO ( MOD_KEY-z )
    else if(e.hasModifier(MOD_KEY) && e.keycode == 90 && isCodeEditorON && isOverCodeEditor){
        if(codeEditors[editedFilesNames[actualCodeEditor]].CanUndo()){
            codeEditors[editedFilesNames[actualCodeEditor]].Undo();
        }
    }
    // code-editor REDO ( MOD_KEY-y )
    else if(e.hasModifier(MOD_KEY) && e.keycode == 89 && isCodeEditorON && isOverCodeEditor){
        if(codeEditors[editedFilesNames[actualCodeEditor]].CanRedo()){
            codeEditors[editedFilesNames[actualCodeEditor]].Redo();
        }
    }
    // code-editor COPY ( MOD_KEY-c )
    else if(e.hasModifier(MOD_KEY) && e.keycode == 67 && isCodeEditorON && isOverCodeEditor){
        if(codeEditors[editedFilesNames[actualCodeEditor]].HasSelection()){
            codeEditors[editedFilesNames[actualCodeEditor]].Copy();
        }
    }
    // code-editor CUT ( MOD_KEY-x )
    else if(e.hasModifier(MOD_KEY) && e.keycode == 88 && isCodeEditorON && isOverCodeEditor){
        if(codeEditors[editedFilesNames[actualCodeEditor]].HasSelection()){
            codeEditors[editedFilesNames[actualCodeEditor]].Cut();
        }
    }
    // code-editor PASTE ( MOD_KEY-v )
    else if(e.hasModifier(MOD_KEY) && e.keycode == 86 && isCodeEditorON && isOverCodeEditor){
        if(ImGui::GetClipboardText() != nullptr){
            codeEditors[editedFilesNames[actualCodeEditor]].Paste();
        }
    }
    // code-editor SELECT ALL ( MOD_KEY-a )
    else if(e.hasModifier(MOD_KEY) && e.keycode == 65 && isCodeEditorON && isOverCodeEditor){
        codeEditors[editedFilesNames[actualCodeEditor]].SetSelection(TextEditor::Coordinates(), TextEditor::Coordinates(codeEditors[editedFilesNames[actualCodeEditor]].GetTotalLines(), 0));
    }

    #if defined(TARGET_LINUX) || defined(TARGET_WIN32)
    if(e.hasModifier(MOD_KEY) && e.keycode == 81){
        quitMosaic();
    }
    #endif

    //ofLog(OF_LOG_NOTICE,"%i",e.keycode);

}

//--------------------------------------------------------------
void ofApp::keyReleased(ofKeyEventArgs &e){
    // OSX: CMD-F, WIN/LINUX: CTRL-F    (FULLSCREEN)
    if(e.hasModifier(MOD_KEY) && e.keycode == 70){
        ofToggleFullscreen();
    // add object from right click menu with enter
    }else if(e.keycode == 257){
        createSearchedObject = true;
    // most useful objects shortcuts
    }else if(e.hasModifier(MOD_KEY) && e.keycode == 49){ // MOD_KEY 1
        visualProgramming->addObject("bang",ofVec2f(visualProgramming->canvas.getMovingPoint().x + 100,visualProgramming->canvas.getMovingPoint().y + 100));
    }else if(e.hasModifier(MOD_KEY) && e.keycode == 50){ // MOD_KEY 2
        visualProgramming->addObject("trigger",ofVec2f(visualProgramming->canvas.getMovingPoint().x + 100,visualProgramming->canvas.getMovingPoint().y + 100));
    }else if(e.hasModifier(MOD_KEY) && e.keycode == 51){ // MOD_KEY 3
        visualProgramming->addObject("number",ofVec2f(visualProgramming->canvas.getMovingPoint().x + 100,visualProgramming->canvas.getMovingPoint().y + 100));
    }else if(e.hasModifier(MOD_KEY) && e.keycode == 52){ // MOD_KEY 4
        visualProgramming->addObject("metronome",ofVec2f(visualProgramming->canvas.getMovingPoint().x + 100,visualProgramming->canvas.getMovingPoint().y + 100));
    }else if(e.hasModifier(MOD_KEY) && e.keycode == 53){ // MOD_KEY 5
        visualProgramming->addObject("video viewer",ofVec2f(visualProgramming->canvas.getMovingPoint().x + 100,visualProgramming->canvas.getMovingPoint().y + 100));
    }else if(e.hasModifier(MOD_KEY) && e.keycode == 54){ // MOD_KEY 6
        visualProgramming->addObject("signal viewer",ofVec2f(visualProgramming->canvas.getMovingPoint().x + 100,visualProgramming->canvas.getMovingPoint().y + 100));
    }else if(e.hasModifier(MOD_KEY) && e.keycode == 55){ // MOD_KEY 7
        visualProgramming->addObject("audio analyzer",ofVec2f(visualProgramming->canvas.getMovingPoint().x + 100,visualProgramming->canvas.getMovingPoint().y + 100));
    }else if(e.hasModifier(MOD_KEY) && e.keycode == 56){ // MOD_KEY 8
        visualProgramming->addObject("lua script",ofVec2f(visualProgramming->canvas.getMovingPoint().x + 100,visualProgramming->canvas.getMovingPoint().y + 100));
    }else if(e.hasModifier(MOD_KEY) && e.keycode == 57){ // MOD_KEY 9
        visualProgramming->addObject("output window",ofVec2f(visualProgramming->canvas.getMovingPoint().x + 100,visualProgramming->canvas.getMovingPoint().y + 100));
    }
    // open/close Asset Manager ( MOD_KEY-m )
    else if(e.hasModifier(MOD_KEY) && e.keycode == 77){
        isAssetLibraryON = !isAssetLibraryON;
    }
    // open/close Code Editor ( MOD_KEY-e )
    else if(e.hasModifier(MOD_KEY) && e.keycode == 69){
        isCodeEditorON = !isCodeEditorON;
    }
    // open/close Inspector ( MOD_KEY-i )
    else if(e.hasModifier(MOD_KEY) && e.keycode == 73){
        visualProgramming->inspectorActive = !visualProgramming->inspectorActive;
    }
    // open/close Logger ( MOD_KEY-l )
    else if(e.hasModifier(MOD_KEY) && e.keycode == 76){
        isLoggerON = !isLoggerON;
    }
    // open/close Profiler ( MOD_KEY-p )
    else if(e.hasModifier(MOD_KEY) && e.keycode == 80){
        visualProgramming->profilerActive = !visualProgramming->profilerActive;
    }
    // open/close Patch Navigator ( MOD_KEY-t )
    else if(e.hasModifier(MOD_KEY) && e.keycode == 84){
        visualProgramming->navigationActive = !visualProgramming->navigationActive;
    }
    // open/close Chatroom ( MOD_KEY-d )
    else if(e.hasModifier(MOD_KEY) && e.keycode == 68){
        isChatroomON = !isChatroomON;
    }
    // open/close Objects Menu ( MOD_KEY-o )
    else if(e.hasModifier(MOD_KEY) && e.keycode == 79){
        showRightClickMenu = !showRightClickMenu;
    }

    //ofLog(OF_LOG_NOTICE,"%i",e.keycode);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    unusedArgs(x,y);

    /*if(button == 2 && !isOverCodeEditor && !isOverAssetLibrary){ // right click
        showRightClickMenu = true;
    }*/

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    unusedArgs(x,y,button);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    unusedArgs(w,h);

    if(isInited && ofGetElapsedTimeMillis() > 1000){
        isWindowResized = true;
    }
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    if( dragInfo.files.size() == 1 ){
        ofFile file (dragInfo.files[0]);
        createObjectFromFile(file,false);
    }
}

//--------------------------------------------------------------
void ofApp::urlResponse(ofHttpResponse & response) {
    if (response.status==200 && response.request.name == "check_release_async") {
        // check for updates
        lastRelease = response.data.getText();
        checkForUpdates();
    }
}

//--------------------------------------------------------------
void ofApp::pathChanged(const PathWatcher::Event &event) {

    ofFile tempfile(event.path);

    if(tempfile.isFile()){
        ofBuffer tempcontent = ofBufferFromFile(tempfile.getAbsolutePath());

        switch(event.change) {
            case PathWatcher::CREATED:
                //ofLogVerbose(PACKAGE) << "path created " << event.path;
                break;
            case PathWatcher::MODIFIED:
                //ofLogVerbose(PACKAGE) << "path modified " << event.path;
                codeEditors[tempfile.getFileName()].SetText(tempcontent.getText(),false);
                break;
            case PathWatcher::DELETED:
                //ofLogVerbose(PACKAGE) << "path deleted " << event.path;
                return;
            default: // NONE
                return;
        }
    }else if(tempfile.isDirectory()){
        if(event.change == PathWatcher::MODIFIED){
            assetFolder.listDir(assetFolder.getAbsolutePath());
            assetFolder.sort();
        }
    }



}

//--------------------------------------------------------------
void ofApp::quitMosaic(){
    ofExit(0);
}

//--------------------------------------------------------------
void ofApp::refreshScriptTabs(){
    // load new script files in code editor
    if(visualProgramming->scriptsObjectsFilesPaths.size() > 0){
        for(map<string,string>::iterator it = visualProgramming->scriptsObjectsFilesPaths.begin(); it != visualProgramming->scriptsObjectsFilesPaths.end(); it++ ){
            ofFile tempsofp(it->second);

            map<string,TextEditor>::iterator sofpIT = codeEditors.find(tempsofp.getFileName());
            if (sofpIT == codeEditors.end()){
                // script not found in code editor, insert it
                initNewCodeEditor(tempsofp);
            }
        }
    }

    // remove deleted script files from code editor
    if(codeEditors.size() > 0){
        for(map<string,TextEditor>::iterator it = codeEditors.begin(); it != codeEditors.end(); it++ ){
            map<string,string>::iterator sofpVP = visualProgramming->scriptsObjectsFilesPaths.find(it->first);
            if (sofpVP == visualProgramming->scriptsObjectsFilesPaths.end()){
                // script not found in main map, remove it from code editor
                scriptToRemoveFromCodeEditor = it->first;
            }
        }
    }

    if(scriptToRemoveFromCodeEditor != ""){
       removeScriptFromCodeEditor(scriptToRemoveFromCodeEditor);
    }


}

//--------------------------------------------------------------
void ofApp::setMosaicFrameRate(float fps){
    mosaicTiming.setFramerate(fps);
}

//--------------------------------------------------------------
void ofApp::initDataFolderFromBundle(){

    string _bundleDataPath;
    string _bundleExamplesPath;
    string _bundlePluginsPath;

    #ifdef TARGET_OSX

    CFURLRef appUrl = CFBundleCopyBundleURL(CFBundleGetMainBundle());
    CFStringRef appPath = CFURLCopyFileSystemPath(appUrl, kCFURLPOSIXPathStyle);

    const CFIndex kCStringSize = 128;
    char temporaryCString[kCStringSize];
    bzero(temporaryCString,kCStringSize);
    CFStringGetCString(appPath, temporaryCString, kCStringSize, kCFStringEncodingUTF8);
    std::string *appPathStr = new std::string(temporaryCString);
    CFRelease(appUrl);
    CFRelease(appPath);

    CFURLRef resourceUrl = CFBundleCopyResourcesDirectoryURL(CFBundleGetMainBundle());
    CFStringRef resourcePath = CFURLCopyFileSystemPath(resourceUrl, kCFURLPOSIXPathStyle);

    bzero(temporaryCString,kCStringSize);
    CFStringGetCString(resourcePath, temporaryCString, kCStringSize, kCFStringEncodingUTF8);
    std::string *resourcePathStr = new std::string(temporaryCString);
    CFRelease(resourcePath);
    CFRelease(resourceUrl);

    // GIT CLONE CUSTOM BUILD ?
    // Fallback on MosaicRepo/bin/data if Mosaic.app/Contents/Ressources has not been copied for deployment (custom GIT compilers on Qt-creator)
    // This part could be removed when the deployment scripts are ready.
    if(
        // No ressources folder (only distributed builds have these)
        !ofDirectory::doesDirectoryExist(*appPathStr + "/" + *resourcePathStr + "/") &&
        // App is in a "bin" folder and there's a "data" folder
        // (MosaicGit/bin/data and MosaicGit/bin/Mosaic_xxx.app/Contents/MacOs/mosaicBinary)
        ofDirectory::doesDirectoryExist(*appPathStr + "/../../bin/data/")
    ){
        std::string gitBinPath = ofDirectory(*appPathStr + "/../../bin/").getAbsolutePath();
        ofLog(OF_LOG_VERBOSE, "%s","Mosaic Build: Detected a custom git build application, setting application paths accordingly.");
        _bundleDataPath = gitBinPath + "/../../bin/data/"; // the absolute path to the resources folder
        _bundleExamplesPath = gitBinPath + "/examples/";
        _bundlePluginsPath = gitBinPath + "/plugins/";
    }
    // DISTRIBUTED RELEASE BINARY
    else {
        ofLog(OF_LOG_VERBOSE, "%s","Mosaic Build: Detected a distributed release application.");
        _bundleDataPath = *appPathStr + "/" + *resourcePathStr + "/"; // the absolute path to the resources folder
        _bundleExamplesPath = *appPathStr + "/Contents/examples/";
        _bundlePluginsPath = *appPathStr + "/Contents/plugins/";
    }
    ofLog(OF_LOG_VERBOSE, "Mosaic binary data path:     %s", _bundleDataPath.c_str());
    ofLog(OF_LOG_VERBOSE, "Mosaic binary examples path: %s", _bundleExamplesPath.c_str());
    ofLog(OF_LOG_VERBOSE, "Mosaic binary plugins path:  %s", _bundlePluginsPath.c_str());

    const char *homeDir = getenv("HOME");

    if(!homeDir){
        struct passwd* pwd;
        pwd = getpwuid(getuid());
        if (pwd){
            homeDir = pwd->pw_dir;
        }
    }

    string _MosaicDataPath(homeDir);
    string _MosaicExamplesPath(homeDir);
    string _MosaicPluginsPath(homeDir);
    userHome = _MosaicDataPath;

    _MosaicDataPath += "/Documents/Mosaic/data";
    _MosaicExamplesPath += "/Documents/Mosaic/examples";
    _MosaicPluginsPath += "/Documents/Mosaic/plugins";

    std::filesystem::path tempPath(_MosaicDataPath.c_str());
    std::filesystem::path examplesPath(_MosaicExamplesPath.c_str());
    std::filesystem::path pluginsPath(_MosaicPluginsPath.c_str());

    mosaicPath = tempPath;
    mosaicExamplesPath = examplesPath;
    mosaicPluginsPath = pluginsPath;

    ofDirectory mosaicDir;

    // examples directory
    if(!ofDirectory::doesDirectoryExist(mosaicExamplesPath)){
        ofDirectory::createDirectory(mosaicExamplesPath,true,true);

        std::filesystem::path dataPath(_bundleExamplesPath.c_str());

        ofDirectory dataDir(dataPath);
        dataDir.copyTo(mosaicExamplesPath,true,true);
    }else{
        string relfilepath = _MosaicDataPath+"/release.txt";
        std::filesystem::path releasePath(relfilepath.c_str());
        ofFile relFile(releasePath);

        if(relFile.exists()){
            string actualRel = relFile.readToBuffer().getLines().begin().asString();

            if(VERSION != actualRel){
                std::filesystem::path dataPath(_bundleExamplesPath.c_str());

                // remove previous release examples folder
                ofDirectory::removeDirectory(mosaicExamplesPath,true);
                ofDirectory::createDirectory(mosaicExamplesPath,true,true);

                ofDirectory dataDir(dataPath);
                dataDir.copyTo(mosaicExamplesPath,true,true);
            }
        }

    }

    // Create data directory
    if(!ofDirectory::doesDirectoryExist(mosaicPath)){
        ofDirectory::createDirectory(mosaicPath,true,true);

        std::filesystem::path dataPath(_bundleDataPath.c_str());

        ofDirectory dataDir(dataPath);
        dataDir.copyTo(mosaicPath,true,true);
    // Or Check data directory
    }else{
        string relfilepath = _MosaicDataPath+"/release.txt";
        std::filesystem::path releasePath(relfilepath.c_str());
        ofFile relFile(releasePath);

        string actualRel = "";
        if(relFile.exists()){
            actualRel = relFile.readToBuffer().getLines().begin().asString();
            ofLog(OF_LOG_VERBOSE, "Mosaic user data path: %s (saved with version %s, Mosaic is %s)", _MosaicDataPath.c_str(), actualRel.c_str(), VERSION);
        }else{
            ofLog(OF_LOG_WARNING, "%s","release.txt was not found, Mosaic could not verify compatibility with your data folder.");
            actualRel = "unknown"; // Note: setting this will trigger a data folder update
        }

        // If versions differ, copy data folder again (use a fresh one)
        if(VERSION != actualRel){
            ofLog(OF_LOG_NOTICE, "%s","Mosaic was updated since you last used it. Copying the new data folder structure to your user workspace to ensure full compatibility.");
            std::filesystem::path dataPath(_bundleDataPath.c_str());

            // Remove previous release data folder
            ofDirectory::removeDirectory(mosaicPath,true);
            ofDirectory::createDirectory(mosaicPath,true,true);

            // Copy the new one from app bundle
            ofDirectory dataDir(dataPath);

            // Copy files if originals exists
            if( dataDir.exists() ){
                ofLog(OF_LOG_NOTICE, "Copying data folder from  %s to %s.", dataDir.getAbsolutePath().c_str(), mosaicPath.c_str());
                dataDir.copyTo(mosaicPath,true,true);
            }else {
                ofLog(OF_LOG_ERROR,"%s", "Mosaic could not find a clean data folder to work with and will thus be unable to initialize correctly !");
                exit();
            }
        }

    }

    // plugins directory
    if(!ofDirectory::doesDirectoryExist(mosaicPluginsPath)){
        ofDirectory::createDirectory(mosaicPluginsPath,true,true);

        std::filesystem::path dataPath(_bundlePluginsPath.c_str());

        ofDirectory dataDir(dataPath);
        dataDir.copyTo(mosaicPluginsPath,true,true);
    }


    ofSetDataPathRoot(mosaicPath); // tell OF to look for resources here

    examplesRoot.listDir(mosaicExamplesPath.string());

    #elif defined(TARGET_LINUX)

    _bundleDataPath = ofToDataPath("../data");
    _bundleExamplesPath = ofToDataPath("../examples");
    _bundlePluginsPath = ofToDataPath("../plugins");

    string prevCMD = execCmd("cat ~/.config/user-dirs.dirs | grep XDG_DOCUMENTS_DIR | sed 's/XDG_DOCUMENTS_DIR=//g' | tr -d '\"' ");
    string finalCMD = "echo "+prevCMD;
    string homeDir = execCmd(finalCMD.c_str());
    if(homeDir[homeDir.length()-1] < 97 || homeDir[homeDir.length()-1] > 122){
        homeDir.pop_back();
    }

    string _MosaicDataPath(homeDir);
    string _MosaicExamplesPath(homeDir);
    string _MosaicPluginsPath(homeDir);
    userHome = _MosaicDataPath;

    _MosaicDataPath += "/Mosaic/data";
    _MosaicExamplesPath += "/Mosaic/examples";
    _MosaicPluginsPath += "/Mosaic/plugins";

    std::filesystem::path tempPath(_MosaicDataPath.c_str());
    std::filesystem::path examplesPath(_MosaicExamplesPath.c_str());
    std::filesystem::path pluginsPath(_MosaicPluginsPath.c_str());

    mosaicPath = tempPath;
    mosaicExamplesPath = examplesPath;
    mosaicPluginsPath = pluginsPath;

    ofDirectory mosaicDir;

    // examples directory
    if(!mosaicDir.doesDirectoryExist(mosaicExamplesPath)){
        mosaicDir.createDirectory(mosaicExamplesPath,true,true);

        std::filesystem::path dataPath(_bundleExamplesPath.c_str());

        ofDirectory dataDir(dataPath);
        dataDir.copyTo(mosaicExamplesPath,true,true);
    }else{
        string relfilepath = _MosaicDataPath+"/release.txt";
        std::filesystem::path releasePath(relfilepath.c_str());
        ofFile relFile(releasePath);

        if(relFile.exists()){
            string actualRel = relFile.readToBuffer().getText();

            if(VERSION != actualRel){
                std::filesystem::path dataPath(_bundleExamplesPath.c_str());

                // remove previous release examples folder
                mosaicDir.removeDirectory(mosaicExamplesPath,true);
                mosaicDir.createDirectory(mosaicExamplesPath,true,true);

                ofDirectory dataDir(dataPath);
                dataDir.copyTo(mosaicExamplesPath,true,true);
            }
        }

    }

    // data directory
    if(!mosaicDir.doesDirectoryExist(mosaicPath)){
        mosaicDir.createDirectory(mosaicPath,true,true);

        std::filesystem::path dataPath(_bundleDataPath.c_str());

        ofDirectory dataDir(dataPath);
        dataDir.copyTo(mosaicPath,true,true);
    }else{
        /*string relfilepath = _MosaicDataPath+"/release.txt";
        std::filesystem::path releasePath(relfilepath.c_str());
        ofFile relFile(releasePath);

        if(relFile.exists()){
            string actualRel = relFile.readToBuffer().getText();

            if(VERSION != actualRel){
                std::filesystem::path dataPath(_bundleDataPath.c_str());

                // remove previous release data folder
                mosaicDir.removeDirectory(mosaicPath,true);
                mosaicDir.createDirectory(mosaicPath,true,true);

                // copy the new one
                ofDirectory dataDir(dataPath);
                dataDir.copyTo(mosaicPath,true,true);
            }
        }*/
    }

    // plugins directory
    if(!mosaicDir.doesDirectoryExist(mosaicPluginsPath)){
        mosaicDir.createDirectory(mosaicPluginsPath,true,true);

        std::filesystem::path dataPath(_bundlePluginsPath.c_str());

        ofDirectory dataDir(dataPath);
        dataDir.copyTo(mosaicPluginsPath,true,true);
    }


    ofSetDataPathRoot(mosaicPath); // tell OF to look for resources here

    examplesRoot.listDir(mosaicExamplesPath.string());

    #elif defined(TARGET_WIN32)

    examplesRoot.listDir(ofToDataPath("../examples"));

    #endif

    examplesRoot.sort();

}

//--------------------------------------------------------------
bool ofApp::checkInternetReachability(){

    ofHttpResponse tempResp = ofLoadURL("https://raw.githubusercontent.com/d3cod3/Mosaic/master/RELEASE.md");

    if(tempResp.status == 200){
        string tmpstr = "[verbose] INTERNET IS AVAILABLE!";
        ofLog(OF_LOG_NOTICE,"%s",tmpstr.c_str());
        return true;
    }else{
        string tmpstr = "INTERNET IS NOT AVAILABLE!";
        ofLog(OF_LOG_ERROR,"%s",tmpstr.c_str());
        return false;
    }

}

//--------------------------------------------------------------
void ofApp::checkForUpdates(){
    string tmpstr = "CHECKING FOR MOSAIC UPDATES...";
    ofLog(OF_LOG_NOTICE,"%s",tmpstr.c_str());

    string actualVersion = VERSION;
    if(ofToInt(string(1,actualVersion.at(0))) < ofToInt(string(1,lastRelease.at(0))) || ( ofToInt(string(1,actualVersion.at(0))) == ofToInt(string(1,lastRelease.at(0))) && ofToInt(string(1,actualVersion.at(2))) < ofToInt(string(1,lastRelease.at(2))) ) || ( ofToInt(string(1,actualVersion.at(0))) == ofToInt(string(1,lastRelease.at(0))) && ofToInt(string(1,actualVersion.at(2))) == ofToInt(string(1,lastRelease.at(2))) && ofToInt(string(1,actualVersion.at(4))) < ofToInt(string(1,lastRelease.at(4))) )){
        ofLog(OF_LOG_NOTICE,"[verbose]NEW MOSAIC %s UPDATE AVAILABLE!",lastRelease.c_str());
    }else{
        tmpstr = "NO NEW MOSAIC UPDATE AVAILABLE!";
        ofLog(OF_LOG_NOTICE,"%s",tmpstr.c_str());
    }

}

//--------------------------------------------------------------
void ofApp::checkAutoloadConfig(){
    string autoloadfilepath = ofToDataPath("autoload.txt",true);
    ofFile autoloadFile(autoloadfilepath);

    autoloadPatchFile       = "";
    autoloadDelaySeconds    = 1;
    waitForAutoload         = autoloadDelaySeconds*1000;
    isAutoloadedPatch       = false;

    if(autoloadFile.exists()){
        ofBuffer fileBuffer = ofBufferFromFile(autoloadfilepath);

        // extract autoload data ( fixed txt file with two lines, line one: filepath, line two: delay seconds to load )
        if(fileBuffer.size()) {
            int counter = 0;
            for (ofBuffer::Line it = fileBuffer.getLines().begin(), end = fileBuffer.getLines().end(); it != end; ++it) {
                string line = *it;

                if(counter == 0){
                    autoloadPatchFile       = line;
                }else if(counter == 1){
                    autoloadDelaySeconds    = ofToInt(line);
                    waitForAutoload         = autoloadDelaySeconds*1000;
                    isAutoloadedPatch       = true;
                }

                counter++;
            }
        }
    }

    //ofLog(OF_LOG_NOTICE,"AUTOLOAD Data: %s --> Delay %i",autoloadPatchFile.c_str(),autoloadDelaySeconds);

    autoloadStartTime = ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------
void ofApp::setAutoloadConfig(){
    //std::ofstream file;
    string autoloadfilepath = ofToDataPath("autoload.txt",true);

    std::ofstream file(autoloadfilepath, std::ofstream::trunc);

    //file.open(autoloadfilepath, std::ios::out | std::ios::app);

    file << autoloadPatchFile << std::endl;
    file << ofToString(autoloadDelaySeconds) << std::endl;
    file.close();
}

//--------------------------------------------------------------
void ofApp::createDirectoryNode(ofFile file){
    if(file.isDirectory()){
        if(ImGui::BeginMenu(file.getBaseName().c_str())){
            ofDirectory temp;
            temp.listDir(file.getAbsolutePath());
            temp.sort();
            for(size_t i=0;i<temp.getFiles().size();i++){
                createDirectoryNode(temp.getFiles().at(i));
            }
            ImGui::EndMenu();
        }
    }else{
        if(file.getBaseName() != "LICENSE" && file.getBaseName() != "README"){
            string fileExtension = ofToUpper(file.getExtension());
            if(fileExtension == "LUA" || fileExtension == "FRAG" || fileExtension == "SH" || fileExtension == "PD" || fileExtension == "XML" || fileExtension == "PNG" || fileExtension == "GIF" || fileExtension == "JPG" || fileExtension == "JPEG" || fileExtension == "TIF" || fileExtension == "TIFF" || fileExtension == "WAV" || fileExtension == "OGG" || fileExtension == "MP3" || fileExtension == "FLAC" || fileExtension == "MOV" || fileExtension == "MP4" || fileExtension == "MPEG" || fileExtension == "MPG" || fileExtension == "AVI"){
                if(fileExtension == "LUA"){
#if defined(TARGET_WIN32)
                    string tempstr = file.getEnclosingDirectory().substr(0,file.getEnclosingDirectory().find_last_of('\\'));
                    if(file.getEnclosingDirectory().substr(tempstr.find_last_of('\\')+1,file.getEnclosingDirectory().find_last_of('\\')-tempstr.find_last_of('\\')-1) == file.getFileName().substr(0,file.getFileName().find_last_of('.'))){
#else
                    string tempstr = file.getEnclosingDirectory().substr(0,file.getEnclosingDirectory().find_last_of('/'));
                    if(file.getEnclosingDirectory().substr(tempstr.find_last_of('/')+1,file.getEnclosingDirectory().find_last_of('/')-tempstr.find_last_of('/')-1) == file.getFileName().substr(0,file.getFileName().find_last_of('.'))){
#endif
                        string menuName = file.getBaseName()+"."+file.getExtension();
                        if(ImGui::MenuItem(menuName.c_str())){
                            createObjectFromFile(file,true);
                        }
                    }
                }else{
                    string menuName = file.getBaseName()+"."+file.getExtension();
                    if(ImGui::MenuItem(menuName.c_str())){
                        createObjectFromFile(file,true);
                    }
                }

            }
        }

    }
}

//--------------------------------------------------------------
void ofApp::createObjectFromFile(ofFile file,bool temp,int px, int py){

    ofVec2f objPos;

    if(px == -1 && py == -1){
        objPos.set(visualProgramming->canvas.getMovingPoint().x + 20,visualProgramming->canvas.getMovingPoint().y + 20);
    }else{
        objPos.set(px,py);
    }

    if (file.exists()){
        //string tempstr = file.getEnclosingDirectory().substr(0,file.getEnclosingDirectory().find_last_of('/'));
        //ofLog(OF_LOG_NOTICE,"%s : %s",file.getEnclosingDirectory().substr(tempstr.find_last_of('/')+1,file.getEnclosingDirectory().find_last_of('/')-tempstr.find_last_of('/')-1).c_str(), file.getFileName().substr(0,file.getFileName().find_last_of('.')).c_str());
        string fileExtension = ofToUpper(file.getExtension());
        if(fileExtension == "XML") {
            ofxXmlSettings XML;

#if OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR < 12
            if (XML.loadFile(file.getAbsolutePath())){
#else
            if (XML.load(file.getAbsolutePath())){
#endif
                if (XML.getValue("www","") == "https://mosaic.d3cod3.org"){
                    if(temp){
                        visualProgramming->newTempPatchFromFile(file.getAbsolutePath());
                        ofFile temp(visualProgramming->currentPatchFile);
                        assetFolder.reset();
                        assetFolder.listDir(temp.getEnclosingDirectory()+"data/");
                        assetFolder.sort();
                        assetWatcher.removeAllPaths();
                        assetWatcher.addPath(temp.getEnclosingDirectory()+"data/");
                    }else{
                        patchToLoad = file.getAbsolutePath();
                        loadNewPatch = true;
                        //visualProgramming->preloadPatch(file.getAbsolutePath());
                    }
                }else{
                    ofLog(OF_LOG_ERROR, "The opened file: %s, is not a Mosaic patch!",file.getAbsolutePath().c_str());
                }
            }
        }else if(fileExtension == "MOV" || fileExtension == "MP4" || fileExtension == "MPEG" || fileExtension == "MPG" || fileExtension == "AVI"){
            visualProgramming->addObject("video player",objPos);
            if(visualProgramming->getLastAddedObject() != nullptr){
                visualProgramming->getLastAddedObject()->autoloadFile(file.getAbsolutePath());
            }
        }else if(fileExtension == "WAV" || fileExtension == "OGG" || fileExtension == "MP3" || fileExtension == "FLAC") {
            visualProgramming->addObject("soundfile player",objPos);
            if(visualProgramming->getLastAddedObject() != nullptr){
                visualProgramming->getLastAddedObject()->autoloadFile(file.getAbsolutePath());
            }
        }else if(fileExtension == "PNG" || fileExtension == "GIF" || fileExtension == "JPG" || fileExtension == "JPEG" || fileExtension == "TIF" || fileExtension == "TIFF") {
            visualProgramming->addObject("image loader",objPos);
            if(visualProgramming->getLastAddedObject() != nullptr){
                visualProgramming->getLastAddedObject()->autoloadFile(file.getAbsolutePath());
            }
        }else if(fileExtension == "LUA") {
            visualProgramming->addObject("lua script",objPos);
            if(visualProgramming->getLastAddedObject() != nullptr){
                visualProgramming->getLastAddedObject()->autoloadFile(file.getAbsolutePath());
            }
        }else if(fileExtension == "FRAG" || fileExtension == "VERT") {
            visualProgramming->addObject("glsl shader",objPos);
            if(visualProgramming->getLastAddedObject() != nullptr){
                visualProgramming->getLastAddedObject()->autoloadFile(file.getAbsolutePath());
            }
        }else if(fileExtension == "SH") {
            visualProgramming->addObject("bash script",objPos);
            if(visualProgramming->getLastAddedObject() != nullptr){
                visualProgramming->getLastAddedObject()->autoloadFile(file.getAbsolutePath());
            }
        }else if(fileExtension == "PD") {
            visualProgramming->addObject("pd patch",objPos);
            if(visualProgramming->getLastAddedObject() != nullptr){
                visualProgramming->getLastAddedObject()->autoloadFile(file.getAbsolutePath());
            }
        }

    }
}

//--------------------------------------------------------------
bool ofApp::checkFileUsedInPatch(string filepath){
    for(map<int,shared_ptr<PatchObject>>::iterator it = visualProgramming->patchObjects.begin(); it != visualProgramming->patchObjects.end(); it++ ){
        if(it->second->getFilepath() == filepath){
            return true;
        }
    }
    return false;
}

//--------------------------------------------------------------
void ofApp::initScriptLanguages(){
    // ------------------------------------------- LUA
    static const char* const lua_mosaic_keywords[] = {
        "USING_DATA_INLET", "OUTPUT_WIDTH", "OUTPUT_HEIGHT", "_mosaic_data_inlet", "_mosaic_data_outlet", "SCRIPT_PATH", "mouseX", "mouseY" };

    for (size_t i = 0; i < sizeof(lua_mosaic_keywords) / sizeof(lua_mosaic_keywords[0]); ++i){
        TextEditor::Identifier id;
        //id.mDeclaration = lua_mosaic_keywords_decl[i];
        id.mDeclaration = "";
        luaLang.mPreprocIdentifiers.insert(std::make_pair(std::string(lua_mosaic_keywords[i]), id));
    }

    ofxXmlSettings XML;


#if OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR < 12
    if (XML.loadFile("livecoding/lua_mosaic_language.xml")){
#else
    if (XML.load("livecoding/lua_mosaic_language.xml")){
#endif
        int totalMethods = XML.getNumTags("method");

        // Load all the lua_of_mosaic methods
        for(int i=0;i<totalMethods;i++){
            if(XML.pushTag("method", i)){
                string methname = XML.getValue("name","");
                string methdesc = XML.getValue("desc","");

                TextEditor::Identifier id;
                //id.mDeclaration = fix_newlines(methdesc).c_str();
                id.mDeclaration = "";
                luaLang.mIdentifiers.insert(std::make_pair(std::string(methname.c_str()), id));

                XML.popTag();
            }
        }

    }

}

//--------------------------------------------------------------
void ofApp::initNewCodeEditor(ofFile file){
    actualEditedFilePath = file.getAbsolutePath();
    actualEditedFileName = file.getFileName();
    editedFilesPaths.push_back(actualEditedFilePath);
    editedFilesNames.push_back(actualEditedFileName);

    ofBuffer tempcontent = ofBufferFromFile(actualEditedFilePath);

    string fileExtension = ofToUpper(file.getExtension());

    TextEditor codeEditor;
    if(fileExtension == "LUA"){
        codeEditor.SetLanguageDefinition(luaLang);
    }else if(fileExtension == "SH"){
        codeEditor.SetLanguageDefinition(bashLang);
    }else if(fileExtension == "FRAG" || fileExtension == "VERT"){
        codeEditor.SetLanguageDefinition(glslLang);
    }

    codeEditor.SetPalette(TextEditor::GetMosaicPalette());
    codeEditor.SetShowWhitespaces(false);
    codeEditor.SetText(tempcontent.getText());

    codeEditors.insert( pair<string,TextEditor>(actualEditedFileName,codeEditor) );

    codeWatchers.insert( pair<string,PathWatcher*>(actualEditedFileName,new PathWatcher()) );
    codeWatchers[actualEditedFileName]->start();
    codeWatchers[actualEditedFileName]->removeAllPaths();
    codeWatchers[actualEditedFileName]->addPath(actualEditedFilePath);

}

//--------------------------------------------------------------
void ofApp::removeScriptFromCodeEditor(string filename){

    for(size_t i=0;i<editedFilesNames.size();i++){
        if(editedFilesNames[i] == filename){
            editedFilesPaths.erase(editedFilesPaths.begin()+i);
            editedFilesNames.erase(editedFilesNames.begin()+i);
        }
    }

    if(editedFilesPaths.size() == 0){
        actualEditedFilePath = "";
        actualEditedFileName = "";
    }else{
        actualEditedFilePath = editedFilesPaths[editedFilesPaths.size()-1];
        actualEditedFileName = editedFilesNames[editedFilesNames.size()-1];
    }

    codeEditors.erase(filename);
    codeWatchers.erase(filename);

    if(codeEditors.size() == 0){
        actualCodeEditor = 0;
    }else{
        actualCodeEditor = codeEditors.size()-1;
    }

    scriptToRemoveFromCodeEditor = "";

}

//--------------------------------------------------------------
void ofApp::setupDHTNode(){

    dht.setupDHTNode(DHT_NETWORK,DHT_PORT,DHT_BOOTSTRAP_NODE);

    myChatid = dht.dhtNode.getId();

    userID = myChatid.toString();
    aka = "";

    chatname = "Mosaic chatroom";

    room = dht::InfoHash::get(chatname);

    welcome_message = "\n\n";
    welcome_message +=" _________________\n";
    welcome_message +="< MOSAIC CHATROOM >\n";
    welcome_message +=" -----------------\n";
    welcome_message +="        \\   ^__^\n";
    welcome_message +="         \\  (OO)\\_______\n";
    welcome_message +="             (__)\\            )\\/\\\n";
    welcome_message +="                    ||----w  |\n";
    welcome_message +="                    ||        ||\n\n\n";

    welcome_message +="Welcome to the internal Mosaic Chatroom! This space is intended for Mosaic users to share knowledge and communicate.\n";
    welcome_message +="This chat is implemented with opendht library, so it works over a distributed network, it is anonymous, and persistent until\n";
    welcome_message +="the last Mosaic instance is closed, so if even only one user let Mosaic running, the chat history will persist.\n";
    welcome_message +="You can communicate here in the public chatroom, or you can open a new private chat with a specific user from the list on the left,\n";
    welcome_message +="so many as you want.\n";
    welcome_message +="This space is not regulated, moderated or supervised, you can change your aka every time you open the software, and absolutely no user data is\n";
    welcome_message +="stored nowhere, as the concept behind the term, this space is free, so use and enjoy it at your own pace.\n\n\n";

    //std::cout << welcome_message << std::endl;

    TextEditor newChat;
    newChat.SetShowWhitespaces(false);
    newChat.SetText(welcome_message);
    newChat.SetReadOnly(true);
    newChat.SetShowLineNumbers(false);
    newChat.SetPalette(TextEditor::GetMosaicPalette());
    newChat.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());

    activeChats.insert( pair<string,TextEditor>(chatname,newChat) );


    if(NDEBUG) std::cout << "Joining h(" << chatname << ") = " << room << std::endl;

    // node running thread
    token = dht.dhtNode.listen<dht::ImMessage>(room, [&](dht::ImMessage&& msg) {
            if (msg.from != myChatid){

                // store current session participants list
                std::map<string,string>::iterator it = participants.find(msg.from.toString());
                if (it == participants.end()){
                    unsigned first = msg.msg.find("<");
                    unsigned last = msg.msg.find_last_of(">");
                    string newAka = msg.msg.substr(first+1,last-first-1);
                    participants[msg.from.toString()] = newAka;
                }

                // debug log
                if(NDEBUG){
                    std::cout << msg.from.toString() << " at " << dht.printTime(msg.date)
                              << " (took " << dht::print_dt(std::chrono::system_clock::now() - std::chrono::system_clock::from_time_t(msg.date))
                              << "s) " << ": " << msg.id << " - " << msg.msg << std::endl;
                }

                // update chatrooms messages
                if(msg.to == myChatid){ // encrypted ( private message )
                    activeChats[msg.from.toString()].InsertText("["+ofGetTimestampString("%H-%M-%S")+"] " + msg.msg + "\n");
                }else{
                    activeChats[chatname].InsertText("["+ofGetTimestampString("%H-%M-%S")+"] " + msg.msg + "\n");
                }

            }
            return true;
    });

}

//--------------------------------------------------------------
void ofApp::updateDHTChat(){
    participantsList = "";
    for(std::map<std::string,std::string>::iterator it = participants.begin(); it != participants.end(); it++ ){
        participantsList += it->second;
        participantsList += "\n";
    }
}

//--------------------------------------------------------------
bool ofApp::checkAKAIsValid(std::string aka){
     for(std::map<std::string,std::string>::iterator it = participants.begin(); it != participants.end(); it++ ){
         if(it->second == aka){
             return false;
         }
     }
     return true;
}

//--------------------------------------------------------------
void ofApp::closeDHTNode(){
    if(dht.dhtNode.isRunning()){
        dht.dhtNode.cancelListen(room, std::move(token));
        dht.stopDHTNode();
    }
}
