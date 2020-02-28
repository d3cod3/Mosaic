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

#if defined(TARGET_LINUX) || defined(TARGET_OSX)
const char* ofxVP_objectsArray[] = {"audio analyzer","beat extractor","bpm extractor","centroid extractor","dissonance extractor","fft extractor","hfc extractor","hpcp extractor","inharmonicity extractor","mel bands extractor","mfcc extractor","onset extractor","pitch extractor","power extractor","rms extractor","rolloff extractor","tristimulus extractor",
                                    "arduino serial","key pressed","key released","midi key","midi knob","midi pad","midi receiver","midi score","midi sender","osc receiver","osc sender",
                                    "background subtraction","chroma key","color tracking","contour tracking","face tracker","haar tracking","motion detection","optical flow",
                                    "bang multiplexer","bang to float","data to file","data to texture","file to data","floats to vector","texture to data","vector at","vector concat","vector gate","vector multiply",
                                    "image exporter","image loader",
                                    "2d pad","bang","comment","message","player controls","signal viewer","slider","sonogram","timeline","trigger","video viewer","vu meter",
                                    "&&","||","==","!=",">","<","counter","delay bang","delay float","gate","inverter","loadbang","select","spigot","timed semaphore",
                                    "add","clamp","constant","divide","map","metronome","modulus","multiply","range","simple noise","simple random","smooth","subtract",
                                    "bash script","lua script","processing script","python script","shader object",
                                    "ADSR envelope","AHR envelope","amp","audio exporter","audio gate","bit cruncher","bit noise","chorus","comb filter","compressor","crossfader","data oscillator","decimator","delay","ducker","hi pass","lfo","low pass","mixer","note to frequency","panner","pd patch","pulse","quad panner","resonant 2pole filter","reverb","saw","signal trigger","sine","soundfile player","triangle","white noise",
                                    "kinect grabber","video crop","video feedback","video exporter","video gate","video grabber","video player","video receiver","video sender","video streaming","video timedelay","video transform",
                                    "live patching","output window","projection mapping"};
#elif defined(TARGET_WIN32)
const char* ofxVP_objectsArray[] = {"audio analyzer","beat extractor","bpm extractor","centroid extractor","dissonance extractor","fft extractor","hfc extractor","hpcp extractor","inharmonicity extractor","mel bands extractor","mfcc extractor","onset extractor","pitch extractor","power extractor","rms extractor","rolloff extractor","tristimulus extractor",
                                    "arduino serial","key pressed","key released","midi key","midi knob","midi pad","midi receiver","midi score","midi sender","osc receiver","osc sender",
                                    "background subtraction","chroma key","color tracking","contour tracking","haar tracking","motion detection","optical flow",
                                    "bang multiplexer","bang to float","data to file","data to texture","file to data","floats to vector","texture to data","vector at","vector concat","vector gate","vector multiply",
                                    "image exporter","image loader",
                                    "2d pad","bang","comment","message","player controls","signal viewer","slider","sonogram","timeline","trigger","video viewer","vu meter",
                                    "&&","||","==","!=",">","<","counter","delay bang","delay float","gate","inverter","loadbang","select","spigot","timed semaphore",
                                    "add","clamp","constant","divide","map","metronome","modulus","multiply","range","simple noise","simple random","smooth","subtract",
                                    "lua script","processing script","python script","shader object",
                                    "ADSR envelope","AHR envelope","amp","audio exporter","audio gate","bit cruncher","bit noise","chorus","comb filter","compressor","crossfader","data oscillator","decimator","delay","ducker","hi pass","lfo","low pass","mixer","note to frequency","panner","pd patch","pulse","quad panner","resonant 2pole filter","reverb","saw","signal trigger","sine","soundfile player","triangle","white noise",
                                    "kinect grabber","video crop","video feedback","video exporter","video gate","video grabber","video player","video streaming","video timedelay","video transform",
                                    "live patching","output window","projection mapping"};
#endif

//--------------------------------------------------------------
void ofApp::setup(){

    ///////////////////////////////////////////
    // OF Stuff
    ofSetEscapeQuitsApp(false);
    ofSetVerticalSync(true);
    ofSetFrameRate(30);
    ofEnableAntiAliasing();
    ofSetLogLevel("Mosaic",OF_LOG_NOTICE);
    ofRegisterURLNotification(this);

    initDataFolderFromBundle();
    ///////////////////////////////////////////

    // RETINA FIX
    if(ofGetScreenWidth() >= RETINA_MIN_WIDTH && ofGetScreenHeight() >= RETINA_MIN_HEIGHT){ // RETINA SCREEN
        ofSetWindowShape(ofGetScreenWidth()-8,ofGetScreenHeight());
    }else if(ofGetScreenWidth() >= 1920){ // DUAL HEAD, TRIPLE HEAD
        ofSetWindowShape(1920-4,ofGetScreenHeight());
    }else{ // STANDARD SCREEN
        ofSetWindowShape(ofGetScreenWidth()-4,ofGetScreenHeight());
    }

    // LOGGER
    isInited        = false;
    isWindowResized = false;
    isLoggerON      = false;
    mosaicLoggerChannel = shared_ptr<MosaicLoggerChannel>(new MosaicLoggerChannel());
    ofSetLoggerChannel(mosaicLoggerChannel);

    ofLog(OF_LOG_NOTICE,"%s | %s <%s>",WINDOW_TITLE,DESCRIPTION,MOSAIC_WWW);
    ofLog(OF_LOG_NOTICE," an open project by Emanuele Mazza aka n3m3da");
    ofLog(OF_LOG_NOTICE,"This project deals with the idea of integrate/amplify human-machine communication, offering a real-time flowchart based visual interface for high level creative coding.\nAs live-coding scripting languages offer a high level coding environment, ofxVisualProgramming and the Mosaic Project as his parent layer container,\naim at a high level visual-programming environment, with embedded multi scripting languages availability (Processing/Java, Lua, Python, GLSL and BASH).\n");

    // Visual Programming Environment Load
    visualProgramming   = new ofxVisualProgramming();
    visualProgramming->setup();
    patchToLoad                 = "";
    loadNewPatch                = false;
    autoinitDSP                 = false;
    resetInitDSP                = ofGetElapsedTimeMillis();

    // GUI
    mosaicLogo = new ofImage("images/logo_1024_bw.png");
    editorFullscreenButtonSource.load("images/fullscreen-icon.png");
    editorFullscreenButtonID = mainMenu.loadImage(editorFullscreenButtonSource);

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ofFile fileToRead1(ofToDataPath(MAIN_FONT));
    string absPath1 = fileToRead1.getAbsolutePath();
    ofFile fileToRead2(ofToDataPath("fonts/IBMPlexMono-Medium.ttf"));
    string absPath2 = fileToRead2.getAbsolutePath();
    if(ofGetScreenWidth() >= RETINA_MIN_WIDTH && ofGetScreenHeight() >= RETINA_MIN_HEIGHT){
        io.Fonts->AddFontFromFileTTF(absPath1.c_str(),26.0f);
        io.Fonts->AddFontFromFileTTF(absPath2.c_str(),30.0f);
    }else{
        io.Fonts->AddFontFromFileTTF(absPath1.c_str(),14.0f);
        io.Fonts->AddFontFromFileTTF(absPath2.c_str(),18.0f);
    }

    ImFont* defaultfont = io.Fonts->Fonts[io.Fonts->Fonts.Size - 2];
    io.FontDefault = defaultfont;

    // CODE EDITOR
    luaLang = TextEditor::LanguageDefinition::Lua();
    glslLang = TextEditor::LanguageDefinition::GLSL();
    javaProcessingLang = TextEditor::LanguageDefinition::JAVAProcessing();
    pythonLang= TextEditor::LanguageDefinition::Python();
    bashLang = TextEditor::LanguageDefinition::Bash();

    initScriptLanguages();

    actualCodeEditor                = 0;
    actualEditedFilePath            = "";
    actualEditedFileName            = "";
    scriptToRemoveFromCodeEditor    = "";
    codeEditorRect.set(ofGetWindowWidth()/3*2, 20,ofGetWindowWidth()/3, ofGetWindowHeight()-40);
    isCodeEditorON = false;
    isCodeEditorFullWindow = false;

    loggerRect.set(0,ofGetWindowHeight()-(258*visualProgramming->scaleFactor),ofGetWindowWidth()/3*2,240*visualProgramming->scaleFactor);

#ifdef TARGET_LINUX
    shortcutFunc = "CTRL";
#elif defined(TARGET_OSX)
    shortcutFunc = "CMD";
#elif defined(TARGET_WIN32)
    shortcutFunc = "CTRL";
#endif

    // Main Menu Bar
    mainMenu.setup();
    mainMenu.setTheme(new MosaicTheme());
    showRightClickMenu      = false;
    showConsoleWindow       = false;
    showCodeEditor          = false;
    isHoverMenu             = false;
    isHoverLogger           = false;
    isHoverCodeEditor       = false;

    ofAddListener(visualProgramming->fileDialog.fileDialogEvent, this, &ofApp::onFileDialogResponse);

    // NET
    isInternetAvailable = false;
    isCheckingRelease = false;

    // Check for updates
    lastRelease = VERSION;

    isInternetAvailable = checkInternetReachability();

    takeScreenshot      = false;
    saveNewScreenshot   = false;
    lastScreenshot      = "";

    setupLoaded         = true;

}

//--------------------------------------------------------------
void ofApp::update(){

    windowTitle = visualProgramming->currentPatchFile+" - "+WINDOW_TITLE;
    ofSetWindowTitle(windowTitle);

    // Visual Programming Environment
    visualProgramming->update();
    visualProgramming->setIsHoverMenu(isHoverMenu);
    visualProgramming->setIsHoverLogger(isHoverLogger);
    visualProgramming->setIsHoverCodeEditor(isHoverCodeEditor);
    if(loadNewPatch){
        loadNewPatch = false;
        if(patchToLoad != ""){
            visualProgramming->openPatch(patchToLoad);
            resetInitDSP = ofGetElapsedTimeMillis();
            autoinitDSP = true;
        }
    }
    if(autoinitDSP){
        if(ofGetElapsedTimeMillis() - resetInitDSP > 1000){
            autoinitDSP = false;
            //visualProgramming->activateDSP();
            // reset code editor position and dimension
            codeEditorRect.set(ofGetWindowWidth()/3*2, 20,ofGetWindowWidth()/3, ofGetWindowHeight()-40);
        }
    }

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

    // listen for editing scripts external changes
    if(codeWatchers.size() > 0){
        for(map<string,PathWatcher*>::iterator it = codeWatchers.begin(); it != codeWatchers.end(); it++ ){
            while(it->second->waitingEvents()) {
                pathChanged(it->second->nextEvent());
            }
        }
    }

    if(scriptToRemoveFromCodeEditor != ""){
       removeScriptFromCodeEditor(scriptToRemoveFromCodeEditor);
    }

    if(isWindowResized){
        isWindowResized = false;
        visualProgramming->updateCanvasViewport();
    }

    if(!isInited){
        isInited = true;
        // reinit DSP
        resetInitDSP = ofGetElapsedTimeMillis();
        autoinitDSP = true;
    }

    // NET
    if(isInternetAvailable && !isCheckingRelease){
        isCheckingRelease = true;
        lastReleaseResp = ofLoadURLAsync("https://raw.githubusercontent.com/d3cod3/Mosaic/master/RELEASE.md","check_release_async");
    }

    // Screenshot
    if(takeScreenshot){
        takeScreenshot = false;
        string newFileName = "mosaicScreenshot_"+ofGetTimestampString("%y%m%d")+".jpg";
        visualProgramming->fileDialog.saveFile("screenshot","Save Mosaic screenshot as",newFileName);
    }
    if(saveNewScreenshot){
       saveNewScreenshot = false;
       if(lastScreenshot != ""){
           ofFile file(lastScreenshot);
           ofImage tempScreenshot;
           tempScreenshot.grabScreen(ofGetWindowRect().x,ofGetWindowRect().y,ofGetWindowWidth(),ofGetWindowHeight());
           tempScreenshot.getPixels().swapRgb();
           tempScreenshot.save(file.getAbsolutePath());
       }
    }

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(20);

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
    mosaicLogo->draw(ofGetWindowWidth()/2 - (128*visualProgramming->scaleFactor),(ofGetWindowHeight()- (240*visualProgramming->scaleFactor))/2 - (128*visualProgramming->scaleFactor),256*visualProgramming->scaleFactor,256*visualProgramming->scaleFactor);

    // Mosaic Visual Programming
    ofSetColor(255,255,255);
    visualProgramming->draw();

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
    visualProgramming->font->draw(tmpMsg,visualProgramming->fontSize,100*visualProgramming->scaleFactor,ofGetHeight() - (6*visualProgramming->scaleFactor));

    // IMGUI interface
    ofSetColor(255,255,255);
    drawImGuiInterface();

    // startup notification popup
    if(setupLoaded && ofGetElapsedTimeMillis() > 1000){
        setupLoaded = false;
        visualProgramming->fileDialog.notificationPopup(WINDOW_TITLE, "Live Visual Patching Creative-Coding Platform\nhttps://mosaic.d3cod3.org/");
    }

}

//--------------------------------------------------------------
void ofApp::drawImGuiInterface(){
    mainMenu.begin();

    {
        ImGui::BeginMainMenuBar();

        {
            if(ImGui::BeginMenu("File")){
                if(ImGui::MenuItem("New patch",ofToString(shortcutFunc+"+N").c_str())){
                    visualProgramming->newPatch();
                    resetInitDSP = ofGetElapsedTimeMillis();
                    autoinitDSP = true;
                }
                ImGui::Separator();
                if(ImGui::MenuItem("Open patch",ofToString(shortcutFunc+"+O").c_str())){
                    visualProgramming->fileDialog.openFile("open patch","Open a Mosaic patch");
                }
                if(ImGui::MenuItem("Open patch source",ofToString(shortcutFunc+"+SHIFT+O").c_str())){
                    visualProgramming->fileDialog.openFile("open patch source","Open a Mosaic patch as source code");
                }
                ImGui::Separator();
                if(ImGui::MenuItem("Save patch As..",ofToString(shortcutFunc+"+S").c_str())){
                    string newFileName = "mosaicPatch_"+ofGetTimestampString("%y%m%d")+".xml";
                    visualProgramming->fileDialog.saveFile("save patch","Save Mosaic patch as",newFileName);
                }
                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Separator();
                ImGui::Spacing();
                if(ImGui::MenuItem("Quit",ofToString(shortcutFunc+"+Q").c_str())){
                    quitMosaic();
                }
                ImGui::EndMenu();
            }

            if(ImGui::BeginMenu("Objects")){
                for(map<string,vector<string>>::iterator it = visualProgramming->objectsMatrix.begin(); it != visualProgramming->objectsMatrix.end(); it++ ){
                    if(ImGui::BeginMenu(it->first.c_str())){
                        for(int j=0;j<static_cast<int>(it->second.size());j++){
                            if(ImGui::MenuItem(it->second.at(j).c_str())){
                                visualProgramming->addObject(it->second.at(j),ofVec2f(visualProgramming->canvas.getMovingPoint().x + 200,visualProgramming->canvas.getMovingPoint().y + 200));
                            }
                        }
                        ImGui::EndMenu();
                    }
                }
                ImGui::EndMenu();
            }

            if(ImGui::BeginMenu("Examples")){
                #if defined(TARGET_OSX)
                examplesRoot.listDir(mosaicExamplesPath.string());
                #else
                examplesRoot.listDir(ofToDataPath("../examples"));
                #endif
                examplesRoot.sort();
                for(int i=0;i<examplesRoot.getFiles().size();i++){
                    createDirectoryNode(examplesRoot.getFiles().at(i));
                }

                ImGui::EndMenu();
            }


            if(ImGui::BeginMenu("Sound")){
                if(ImGui::MenuItem("DSP ON",ofToString(shortcutFunc+"+D").c_str())){
                    visualProgramming->activateDSP();
                }
                #if defined(TARGET_LINUX) || defined(TARGET_OSX)
                if(ImGui::MenuItem("DSP OFF",ofToString(shortcutFunc+"+SHIFT+D").c_str())){
                    visualProgramming->deactivateDSP();
                }
                #endif
                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Separator();
                ImGui::Spacing();
                static int inDev = visualProgramming->audioGUIINIndex;
                if(ImGui::BeginMenu("Input Device")){
                    if(ofxImGui::VectorCombo("Input Device", &inDev,visualProgramming->audioDevicesStringIN)){
                        visualProgramming->setAudioInDevice(inDev);
                    }
                    ImGui::EndMenu();
                }
                static int outDev = visualProgramming->audioGUIOUTIndex;
                if(ImGui::BeginMenu("Output Device")){
                    if(ofxImGui::VectorCombo("Output Device", &outDev,visualProgramming->audioDevicesStringOUT)){
                        visualProgramming->setAudioOutDevice(outDev);
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndMenu();
            }

            if(ImGui::BeginMenu("System")){
                static int fpsn = 2;
                if(ImGui::BeginMenu("FPS")){
                    vector<string> fpss {"24","25","30","60","120"};
                    if(ofxImGui::VectorCombo("FPS", &fpsn,fpss)){
                        if(fpsn == 0){
                            ofSetFrameRate(24);
                        }else if(fpsn == 1){
                            ofSetFrameRate(25);
                        }else if(fpsn == 2){
                            ofSetFrameRate(30);
                        }else if(fpsn == 3){
                            ofSetFrameRate(60);
                        }else if(fpsn == 4){
                            ofSetFrameRate(120);
                        }
                    }
                    ImGui::EndMenu();
                }
                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Separator();
                ImGui::Spacing();
                if(ImGui::MenuItem("Screenshot",ofToString(shortcutFunc+"+T").c_str())){
                    takeScreenshot = true;
                }
                ImGui::EndMenu();
            }

            if(ImGui::BeginMenu("View")){
                if(ImGui::Checkbox("Code Editor",&isCodeEditorON)){
                    showCodeEditor          = isCodeEditorON;
                }
                if(ImGui::Checkbox("Profiler",&visualProgramming->profilerActive)){
                    TIME_SAMPLE_SET_ENABLED(visualProgramming->profilerActive);
                }
                if(ImGui::Checkbox("Logger",&isLoggerON)){
                    showConsoleWindow       = isLoggerON;
                }
                ImGui::EndMenu();
            }

            if(ImGui::BeginMenu("Help")){
                if(ImGui::MenuItem("Mosaic Github")){
                    ofLaunchBrowser("https://github.com/d3cod3/Mosaic");
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
                ImGui::EndMenu();
            }


        }

        ImGui::EndMainMenuBar();

        // code editor
        if(showCodeEditor){
            ImGui::Begin("Code Editor", nullptr, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse);

            ImGui::SetWindowPos(ImVec2(codeEditorRect.x,codeEditorRect.y), ImGuiCond_Always);
            ImGui::SetWindowSize(ImVec2(codeEditorRect.width, codeEditorRect.height), ImGuiCond_Always);

            //isHoverCodeEditor = ImGui::IsAnyWindowHovered() || ImGui::IsAnyItemHovered();
            isHoverCodeEditor = codeEditorRect.inside(ofGetMouseX(),ofGetMouseY());

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

                    ImGui::EndMenuBar();
                }

                ImGui::Text("%6d/%-6d %6d lines | %s | %s", cpos.mLine + 1, cpos.mColumn + 1, codeEditors[editedFilesNames[actualCodeEditor]].GetTotalLines(), codeEditors[editedFilesNames[actualCodeEditor]].GetLanguageDefinition().mName.c_str(), editedFilesPaths[actualCodeEditor].c_str());

                //ImGuiIO& io = ImGui::GetIO();
                //ImFontAtlas* atlas = ImGui::GetIO().Fonts;
                ImFont* tempfont = ImGui::GetIO().Fonts->Fonts[ImGui::GetIO().Fonts->Fonts.Size - 1];

                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Spacing();

                ImGui::SliderFloat("Font scale", &tempfont->Scale, 1.0f, 2.0f);
                ImGui::SameLine();
                ImGui::Spacing();
                ImGui::SameLine();
                ImGui::Spacing();
                ImGui::SameLine();
                ImGui::Spacing();
                ImGui::SameLine();
                if(ImGui::ImageButton(GetImTextureID(editorFullscreenButtonID), ImVec2(24,24))){
                    isCodeEditorFullWindow = !isCodeEditorFullWindow;
                    if(isCodeEditorFullWindow){
                        codeEditorRect.set(0, 20,ofGetWindowWidth(), ofGetWindowHeight()-40);
                    }else{
                        codeEditorRect.set(ofGetWindowWidth()/3*2, 20,ofGetWindowWidth()/3, ofGetWindowHeight()-40);
                    }
                }

                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Spacing();

                if (ImGui::BeginTabBar("TabBar", ImGuiTabBarFlags_Reorderable | ImGuiTabBarFlags_AutoSelectNewTabs | ImGuiTabBarFlags_NoCloseWithMiddleMouseButton)){
                    for(int i=0;i<editedFilesNames.size();i++){
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

                ImGui::End();

            }

            ImGui::End();

        }

        // floating logger window
        if(showConsoleWindow){
            ImGui::SetNextWindowSize(ImVec2(loggerRect.width,loggerRect.height), ImGuiCond_Always);
            ImGui::SetNextWindowPos(ImVec2(loggerRect.x,loggerRect.y), ImGuiCond_Always);
            mosaicLoggerChannel->Draw("Logger");

            isHoverLogger = loggerRect.inside(ofGetMouseX(),ofGetMouseY());
        }else{
            isHoverLogger = false;
        }

        // right click menu
        if(showRightClickMenu){
            ImGui::SetNextWindowSize(ImVec2(200*visualProgramming->scaleFactor,280*visualProgramming->scaleFactor), ImGuiCond_Always);
            ImGui::SetNextWindowPos(ImVec2(ofGetMouseX(),ofGetMouseY()), ImGuiSetCond_Appearing);

            if(ImGui::Begin("Objects", &showRightClickMenu,ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse) ){

                MosaicTheme::TextInputComboBox("Objects", searchedObject, 30, ofxVP_objectsArray, IM_ARRAYSIZE(ofxVP_objectsArray));

                isHoverMenu = ImGui::IsAnyWindowHovered() || ImGui::IsAnyItemHovered();

                for(map<string,vector<string>>::iterator it = visualProgramming->objectsMatrix.begin(); it != visualProgramming->objectsMatrix.end(); it++ ){
                    if(ImGui::BeginMenu(it->first.c_str())){
                        for(int j=0;j<static_cast<int>(it->second.size());j++){
                            if(ImGui::MenuItem(it->second.at(j).c_str())){
                                visualProgramming->addObject(it->second.at(j),ofVec2f(visualProgramming->canvas.getMovingPoint().x + 200,visualProgramming->canvas.getMovingPoint().y + 200));
                                showRightClickMenu = false;
                            }
                        }
                        ImGui::EndMenu();
                    }
                }

                ImGui::End();
            }

        }else{
            isHoverMenu = false;
        }

    }

    mainMenu.end();
}

//--------------------------------------------------------------
void ofApp::exit() {
    visualProgramming->exit();
}

//--------------------------------------------------------------
void ofApp::keyPressed(ofKeyEventArgs &e){

    //ofLog(OF_LOG_NOTICE,"%i",e.keycode);

    if(e.hasModifier(MOD_KEY) && e.keycode == 78) {
        visualProgramming->newPatch();
        resetInitDSP = ofGetElapsedTimeMillis();
        autoinitDSP = true;
    }else if(e.hasModifier(MOD_KEY) && e.hasModifier(OF_KEY_SHIFT) && e.keycode == 79){
        visualProgramming->fileDialog.openFile("open patch source","Open a Mosaic patch as source code");
    }else if(e.hasModifier(MOD_KEY) && !e.hasModifier(OF_KEY_SHIFT) && e.keycode == 79){
        visualProgramming->fileDialog.openFile("open patch","Open a Mosaic patch");
    }else if(e.hasModifier(MOD_KEY) && e.keycode == 76){
        visualProgramming->openLastPatch();
    }else if(e.hasModifier(MOD_KEY) && e.keycode == 83){
        visualProgramming->fileDialog.saveFile("save patch","Save Mosaic patch as","mosaicPatch_"+ofGetTimestampString("%y%m%d")+".xml");
    }else if(e.hasModifier(MOD_KEY) && e.keycode == 82){
        filesystem::path tempPath(editedFilesPaths[actualCodeEditor].c_str());
        ofBuffer buff;
        buff.set(codeEditors[editedFilesNames[actualCodeEditor]].GetText());
        ofBufferToFile(tempPath,buff,false);
    }else if(e.hasModifier(MOD_KEY) && e.keycode == 84){
        takeScreenshot = true;
    }else if(e.hasModifier(MOD_KEY) && !e.hasModifier(OF_KEY_SHIFT) && e.keycode == 68){
        visualProgramming->activateDSP();
    }else if(e.hasModifier(MOD_KEY) && e.hasModifier(OF_KEY_SHIFT) && e.keycode == 68){
        #if defined(TARGET_LINUX) || defined(TARGET_OSX)
        visualProgramming->deactivateDSP();
        #endif
    }else if(e.keycode == 259){
        //visualProgramming->deleteSelectedObject();
    }else if(e.keycode == 257){
        if(searchedObject != ""){
            visualProgramming->addObject(searchedObject,ofVec2f(visualProgramming->canvas.getMovingPoint().x + 300,visualProgramming->canvas.getMovingPoint().y + 200));
            searchedObject = "";
        }

    }

    #if defined(TARGET_LINUX) || defined(TARGET_WIN32)
    if(e.hasModifier(MOD_KEY) && e.keycode == 81){
        quitMosaic();
    }
    #endif

}

//--------------------------------------------------------------
void ofApp::keyReleased(ofKeyEventArgs &e){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if(button == 2){ // right click
        showRightClickMenu = !showRightClickMenu;
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    if(isInited){
        isWindowResized = true;
    }

    if(isInited){
        loggerRect.set(0,ofGetWindowHeight()-(260*visualProgramming->scaleFactor),ofGetWindowWidth()/3*2,240*visualProgramming->scaleFactor);

        if(isCodeEditorFullWindow){
            codeEditorRect.set(0, 20,ofGetWindowWidth(), ofGetWindowHeight()-40);
        }else{
            codeEditorRect.set(ofGetWindowWidth()/3*2, 20,ofGetWindowWidth()/3, ofGetWindowHeight()-40);
        }
    }
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    if( dragInfo.files.size() == 1 ){
        ofFile file (dragInfo.files[0]);
        createObjectFromFile(file,false);
    }
}

//--------------------------------------------------------------
void ofApp::onFileDialogResponse(ofxThreadedFileDialogResponse &response){
    if(response.id == "open patch"){
        ofFile file(response.filepath);
        if (file.exists()){
            string fileExtension = ofToUpper(file.getExtension());
            if(fileExtension == "XML") {
                ofxXmlSettings XML;

                if (XML.loadFile(file.getAbsolutePath())){
                    if (XML.getValue("www","") == "https://mosaic.d3cod3.org"){
                        patchToLoad = file.getAbsolutePath();
                        loadNewPatch = true;
                    }else{
                        ofLog(OF_LOG_ERROR, "The opened file: %s, is not a Mosaic patch!",file.getAbsolutePath().c_str());
                    }
                }
            }
        }
    }else if(response.id == "open patch source"){
        ofFile file(response.filepath);
        if (file.exists()){
            string fileExtension = ofToUpper(file.getExtension());
            if(fileExtension == "XML") {
                ofxXmlSettings XML;

                if (XML.loadFile(file.getAbsolutePath())){
                    if (XML.getValue("www","") == "https://mosaic.d3cod3.org"){
                        string cmd = "";
        #ifdef TARGET_LINUX
                        cmd = "atom "+file.getAbsolutePath();
        #elif defined(TARGET_OSX)
                        cmd = "open -a /Applications/Atom.app "+file.getAbsolutePath();
        #elif defined(TARGET_WIN32)
                        cmd = "atom "+file.getAbsolutePath();
        #endif
                        system(cmd.c_str());
                    }else{
                        ofLog(OF_LOG_ERROR, "The opened file: %s, is not a Mosaic patch!",file.getAbsolutePath().c_str());
                    }
                }

            }
        }
    }else if(response.id == "save patch"){
        ofFile file(response.filepath);
        visualProgramming->savePatchAs(file.getAbsolutePath());
    }else if(response.id == "screenshot"){
        ofFile file(response.filepath);
        lastScreenshot = file.getAbsolutePath();
        saveNewScreenshot = true;
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

}

//--------------------------------------------------------------
void ofApp::quitMosaic(){
    ofExit(0);
}

//--------------------------------------------------------------
void ofApp::initDataFolderFromBundle(){

    #ifdef TARGET_OSX

    string _bundleDataPath;
    string _bundleExamplesPath;

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

    _bundleDataPath = *appPathStr + "/" + *resourcePathStr + "/"; // the absolute path to the resources folder
    _bundleExamplesPath = *appPathStr + "/Contents/examples/";

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
    userHome = _MosaicDataPath;

    _MosaicDataPath += "/Documents/Mosaic/data";
    _MosaicExamplesPath += "/Documents/Mosaic/examples";

    std::filesystem::path tempPath(_MosaicDataPath.c_str());
    std::filesystem::path examplesPath(_MosaicExamplesPath.c_str());

    mosaicPath = tempPath;
    mosaicExamplesPath = examplesPath;

    ofDirectory mosaicDir;

    // data directory
    if(!mosaicDir.doesDirectoryExist(mosaicPath)){
        mosaicDir.createDirectory(mosaicPath,true,true);

        std::filesystem::path dataPath(_bundleDataPath.c_str());

        ofDirectory dataDir(dataPath);
        dataDir.copyTo(mosaicPath,true,true);
    }else{
        string relfilepath = _MosaicDataPath+"/release.txt";
        std::filesystem::path releasePath(relfilepath.c_str());
        ofFile relFile(releasePath);

        if(relFile.exists()){
            string actualRel = relFile.readToBuffer().getText();

            if(VERSION != actualRel){
                std::filesystem::path dataPath(_bundleDataPath.c_str());

                ofDirectory dataDir(dataPath);
                dataDir.copyTo(mosaicPath,true,true);
            }
        }
    }

    // examples directory
    if(!mosaicDir.doesDirectoryExist(examplesPath)){
        mosaicDir.createDirectory(examplesPath,true,true);

        std::filesystem::path dataPath(_bundleExamplesPath.c_str());

        ofDirectory dataDir(dataPath);
        dataDir.copyTo(examplesPath,true,true);
    }else{
        string relfilepath = _MosaicDataPath+"/release.txt";
        std::filesystem::path releasePath(relfilepath.c_str());
        ofFile relFile(releasePath);

        if(relFile.exists()){
            string actualRel = relFile.readToBuffer().getText();

            if(VERSION != actualRel){
                std::filesystem::path dataPath(_bundleExamplesPath.c_str());

                ofDirectory dataDir(dataPath);
                dataDir.copyTo(examplesPath,true,true);
            }
        }

    }

    ofSetDataPathRoot(mosaicPath); // tell OF to look for resources here

    examplesRoot.listDir(mosaicExamplesPath.string());

    #else

    examplesRoot.listDir(ofToDataPath("../examples"));

    #endif

    examplesRoot.sort();

}

//--------------------------------------------------------------
bool ofApp::checkInternetReachability(){

    string cmd = "";
    FILE *execFile;
    string output = "";
#ifdef TARGET_LINUX
    cmd = "ping -q -c1 www.github.com > /dev/null && echo okk || echo err";
    execFile = popen(cmd.c_str(), "r");
#elif defined(TARGET_OSX)
    cmd = "ping -q -c1 www.github.com > /dev/null && echo okk || echo err";
    execFile = popen(cmd.c_str(), "r");
#endif

    if (execFile){
        ofLog(OF_LOG_NOTICE,"CHECKING INTERNET CONNECTIVITY...");

        char buffer[128];
        if(fgets(buffer, sizeof(buffer), execFile) != nullptr){
            char *s = buffer;
            std::string tempstr(s);
            output = tempstr;
        }

        output.pop_back();

#ifdef TARGET_LINUX
        pclose(execFile);
#elif defined(TARGET_OSX)
        pclose(execFile);
#endif

        if(output == "okk"){
            ofLog(OF_LOG_NOTICE,"[verbose] INTERNET IS AVAILABLE!");
            return true;
        }else if(output == "err"){
            ofLog(OF_LOG_ERROR,"INTERNET IS NOT AVAILABLE!");
            return false;
        }
    }

#ifdef TARGET_WIN32
    ofHttpResponse tempResp = ofLoadURL("https://raw.githubusercontent.com/d3cod3/Mosaic/master/RELEASE.md");

    if(tempResp.status == 200){
        ofLog(OF_LOG_NOTICE,"[verbose] INTERNET IS AVAILABLE!");
        return true;
    }else{
        ofLog(OF_LOG_ERROR,"INTERNET IS NOT AVAILABLE!");
        return false;
    }
#else
      return false;
#endif

}

//--------------------------------------------------------------
void ofApp::checkForUpdates(){
    ofLog(OF_LOG_NOTICE,"CHECKING FOR MOSAIC UPDATES...");

    string actualVersion = VERSION;
    if(ofToInt(string(1,actualVersion.at(0))) < ofToInt(string(1,lastRelease.at(0))) || ( ofToInt(string(1,actualVersion.at(0))) == ofToInt(string(1,lastRelease.at(0))) && ofToInt(string(1,actualVersion.at(2))) < ofToInt(string(1,lastRelease.at(2))) ) || ( ofToInt(string(1,actualVersion.at(0))) == ofToInt(string(1,lastRelease.at(0))) && ofToInt(string(1,actualVersion.at(2))) == ofToInt(string(1,lastRelease.at(2))) && ofToInt(string(1,actualVersion.at(4))) < ofToInt(string(1,lastRelease.at(4))) )){
        ofLog(OF_LOG_NOTICE,"[verbose]NEW MOSAIC "+lastRelease+" UPDATE AVAILABLE!");
    }else{
        ofLog(OF_LOG_NOTICE,"NO NEW MOSAIC UPDATE AVAILABLE!");
    }

}

//--------------------------------------------------------------
void ofApp::createDirectoryNode(ofFile file){
    if(file.isDirectory()){
        if(ImGui::BeginMenu(file.getBaseName().c_str())){
            ofDirectory temp;
            temp.listDir(file.getAbsolutePath());
            temp.sort();
            for(int i=0;i<temp.getFiles().size();i++){
                createDirectoryNode(temp.getFiles().at(i));
            }
            ImGui::EndMenu();
        }
    }else{
        if(file.getBaseName() != "LICENSE" && file.getBaseName() != "README"){
            string fileExtension = ofToUpper(file.getExtension());
            if(fileExtension == "LUA" || fileExtension == "PY" || fileExtension == "FRAG" || fileExtension == "SH" || fileExtension == "PD" || fileExtension == "JAVA" || fileExtension == "XML" || fileExtension == "PNG" || fileExtension == "GIF" || fileExtension == "JPG" || fileExtension == "JPEG" || fileExtension == "TIF" || fileExtension == "TIFF" || fileExtension == "WAV" || fileExtension == "OGG" || fileExtension == "MP3" || fileExtension == "FLAC" || fileExtension == "MOV" || fileExtension == "MP4" || fileExtension == "MPEG" || fileExtension == "MPG" || fileExtension == "AVI"){
                if(fileExtension == "LUA"){
                    string tempstr = file.getEnclosingDirectory().substr(0,file.getEnclosingDirectory().find_last_of('/'));
                    if(file.getEnclosingDirectory().substr(tempstr.find_last_of('/')+1,file.getEnclosingDirectory().find_last_of('/')-tempstr.find_last_of('/')-1) == file.getFileName().substr(0,file.getFileName().find_last_of('.'))){
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
void ofApp::createObjectFromFile(ofFile file,bool temp){
    if (file.exists()){
        //string tempstr = file.getEnclosingDirectory().substr(0,file.getEnclosingDirectory().find_last_of('/'));
        //ofLog(OF_LOG_NOTICE,"%s : %s",file.getEnclosingDirectory().substr(tempstr.find_last_of('/')+1,file.getEnclosingDirectory().find_last_of('/')-tempstr.find_last_of('/')-1).c_str(), file.getFileName().substr(0,file.getFileName().find_last_of('.')).c_str());
        string fileExtension = ofToUpper(file.getExtension());
        if(fileExtension == "XML") {
            ofxXmlSettings XML;

            if (XML.loadFile(file.getAbsolutePath())){
                if (XML.getValue("www","") == "https://mosaic.d3cod3.org"){
                    if(temp){
                        visualProgramming->newTempPatchFromFile(file.getAbsolutePath());
                    }else{
                        visualProgramming->openPatch(file.getAbsolutePath());
                    }
                    // reinit DSP
                    resetInitDSP = ofGetElapsedTimeMillis();
                    autoinitDSP = true;
                }else{
                    ofLog(OF_LOG_ERROR, "The opened file: %s, is not a Mosaic patch!",file.getAbsolutePath().c_str());
                }
            }
        }else if(fileExtension == "MOV" || fileExtension == "MP4" || fileExtension == "MPEG" || fileExtension == "MPG" || fileExtension == "AVI"){
            visualProgramming->addObject("video player",ofVec2f(visualProgramming->canvas.getMovingPoint().x + 20,visualProgramming->canvas.getMovingPoint().y + 20));
            if(visualProgramming->getLastAddedObject() != nullptr){
                visualProgramming->getLastAddedObject()->autoloadFile(file.getAbsolutePath());
            }
        }else if(fileExtension == "WAV" || fileExtension == "OGG" || fileExtension == "MP3" || fileExtension == "FLAC") {
            visualProgramming->addObject("soundfile player",ofVec2f(visualProgramming->canvas.getMovingPoint().x + 20,visualProgramming->canvas.getMovingPoint().y + 20));
            if(visualProgramming->getLastAddedObject() != nullptr){
                visualProgramming->getLastAddedObject()->autoloadFile(file.getAbsolutePath());
            }
        }else if(fileExtension == "PNG" || fileExtension == "GIF" || fileExtension == "JPG" || fileExtension == "JPEG" || fileExtension == "TIF" || fileExtension == "TIFF") {
            visualProgramming->addObject("image loader",ofVec2f(visualProgramming->canvas.getMovingPoint().x + 20,visualProgramming->canvas.getMovingPoint().y + 20));
            if(visualProgramming->getLastAddedObject() != nullptr){
                visualProgramming->getLastAddedObject()->autoloadFile(file.getAbsolutePath());
            }
        }else if(fileExtension == "LUA") {
            visualProgramming->addObject("lua script",ofVec2f(visualProgramming->canvas.getMovingPoint().x + 20,visualProgramming->canvas.getMovingPoint().y + 20));
            if(visualProgramming->getLastAddedObject() != nullptr){
                visualProgramming->getLastAddedObject()->autoloadFile(file.getAbsolutePath());
            }
        }else if(fileExtension == "PY") {
            visualProgramming->addObject("python script",ofVec2f(visualProgramming->canvas.getMovingPoint().x + 20,visualProgramming->canvas.getMovingPoint().y + 20));
            if(visualProgramming->getLastAddedObject() != nullptr){
                visualProgramming->getLastAddedObject()->autoloadFile(file.getAbsolutePath());
            }
        }else if(fileExtension == "FRAG" || fileExtension == "VERT") {
            visualProgramming->addObject("shader object",ofVec2f(visualProgramming->canvas.getMovingPoint().x + 20,visualProgramming->canvas.getMovingPoint().y + 20));
            if(visualProgramming->getLastAddedObject() != nullptr){
                visualProgramming->getLastAddedObject()->autoloadFile(file.getAbsolutePath());
            }
        }else if(fileExtension == "SH") {
            visualProgramming->addObject("bash script",ofVec2f(visualProgramming->canvas.getMovingPoint().x + 20,visualProgramming->canvas.getMovingPoint().y + 20));
            if(visualProgramming->getLastAddedObject() != nullptr){
                visualProgramming->getLastAddedObject()->autoloadFile(file.getAbsolutePath());
            }
        }else if(fileExtension == "PD") {
            visualProgramming->addObject("pd patch",ofVec2f(visualProgramming->canvas.getMovingPoint().x + 20,visualProgramming->canvas.getMovingPoint().y + 20));
            if(visualProgramming->getLastAddedObject() != nullptr){
                visualProgramming->getLastAddedObject()->autoloadFile(file.getAbsolutePath());
            }
        }else if(fileExtension == "JAVA"){
            visualProgramming->addObject("processing script",ofVec2f(visualProgramming->canvas.getMovingPoint().x + 20,visualProgramming->canvas.getMovingPoint().y + 20));
            if(visualProgramming->getLastAddedObject() != nullptr){
                visualProgramming->getLastAddedObject()->autoloadFile(file.getAbsolutePath());
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::initScriptLanguages(){
    // ------------------------------------------- LUA
    static const char* const lua_mosaic_keywords[] = {
        "USING_DATA_INLET", "OUTPUT_WIDTH", "OUTPUT_HEIGHT", "_mosaic_data_inlet", "_mosaic_data_outlet", "SCRIPT_PATH", "mouseX", "mouseY" };

    static const char* const lua_mosaic_keywords_decl[] = {
        "", "The current width of the output window", "The current height of the output window",
        "_mosaic_data_inlet is the name of the lua table storing data incoming from a Mosaic patch.\n A vector<float> is automatically converted to a lua table, where the index starts from 1, NOT 0!\n So the first position of your table will be accessed like this: _mosaic_data_inlet[1]",
        "_mosaic_data_outlet is the name of the lua table storing data outgoing to a Mosaic patch.\n A lua table is automatically converted to a vector<float>. Remember that lua tables index starts from 1, NOT 0!\n So the first position of your table will be accessed like this: _mosaic_data_outlet[1]",
        "Mosaic system variable for loading external resources (files). It returns the absolute path to the script file folder container.",
        "The mouse over output window X (horizontal) coordinate", "The mouse over output window Y (vertical) coordinate"
    };

    for (int i = 0; i < sizeof(lua_mosaic_keywords) / sizeof(lua_mosaic_keywords[0]); ++i){
        TextEditor::Identifier id;
        id.mDeclaration = lua_mosaic_keywords_decl[i];
        luaLang.mPreprocIdentifiers.insert(std::make_pair(std::string(lua_mosaic_keywords[i]), id));
    }



    ofxXmlSettings XML;

    if (XML.loadFile("livecoding/lua_mosaic_language.xml")){
        int totalMethods = XML.getNumTags("method");

        // Load all the lua_of_mosaic methods
        for(int i=0;i<totalMethods;i++){
            if(XML.pushTag("method", i)){
                string methname = XML.getValue("name","");
                string methdesc = XML.getValue("desc","");

                TextEditor::Identifier id;
                id.mDeclaration = fix_newlines(methdesc).c_str();
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
    }else if(fileExtension == "PY"){
        codeEditor.SetLanguageDefinition(pythonLang);
    }else if(fileExtension == "JAVA"){
        codeEditor.SetLanguageDefinition(javaProcessingLang);
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

    actualCodeEditor = codeEditors.size()-1;
}

//--------------------------------------------------------------
void ofApp::removeScriptFromCodeEditor(string filename){

    for(int i=0;i<editedFilesNames.size();i++){
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
