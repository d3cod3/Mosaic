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
    loggerBounds = new ofRectangle();
    screenLoggerChannel = shared_ptr<ofxScreenLoggerChannel>(new ofxScreenLoggerChannel());
    ofSetLoggerChannel(screenLoggerChannel);
    screenLoggerChannel->setBackgroundColor(ofColor(0,0,0,200));
    screenLoggerChannel->setTextColor(ofColor(203,224,254));
    // RETINA FIX
    if(ofGetScreenWidth() >= RETINA_MIN_WIDTH && ofGetScreenHeight() >= RETINA_MIN_HEIGHT){
        screenLoggerChannel->setup(MAIN_FONT,26);
        screenLoggerChannel->setIsRetina();
    }else{
        screenLoggerChannel->setup(MAIN_FONT,14);
    }
    screenLoggerChannel->setPrefixTimestamp(true);
    screenLoggerChannel->setMaxBufferCount(512);

    ofLog(OF_LOG_NOTICE," ");
    ofLog(OF_LOG_NOTICE,"%s | %s <%s>",WINDOW_TITLE,DESCRIPTION,MOSAIC_WWW);
    ofLog(OF_LOG_NOTICE," ");
    ofLog(OF_LOG_NOTICE," an open project by Emanuele Mazza aka n3m3da");
    ofLog(OF_LOG_NOTICE," ");
    ofLog(OF_LOG_NOTICE,"This project deals with the idea of integrate/amplify human-machine communication, offering a real-time flowchart based visual interface for high level creative coding. As live-coding scripting languages offer a high level coding environment, ofxVisualProgramming and the Mosaic Project as his parent layer container, aim at a high level visual-programming environment, with embedded multi scripting languages availability (Lua, Python, GLSL and BASH).");

    // Visual Programming Environment Load
    visualProgramming   = new ofxVisualProgramming();
    visualProgramming->setup();
    patchToLoad         = "";
    loadNewPatch        = false;
    autoinitDSP         = false;
    resetInitDSP        = ofGetElapsedTimeMillis();

    // GUI
    mosaicLogo = new ofImage("images/logo_1024_bw.png");

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ofFile fileToRead(ofToDataPath(MAIN_FONT));
    string absPath = fileToRead.getAbsolutePath();
    if(ofGetScreenWidth() >= RETINA_MIN_WIDTH && ofGetScreenHeight() >= RETINA_MIN_HEIGHT){
        io.Fonts->AddFontFromFileTTF(absPath.c_str(),26.0f);
    }else{
        io.Fonts->AddFontFromFileTTF(absPath.c_str(),14.0f);
    }

    // Main Menu Bar
    mainMenu.setup();
    mainMenu.setTheme(new MosaicTheme());
    showRightClickMenu = false;
    isHoverMenu        = false;

    initExamplesMenu();

    // MODALS
    modalTheme = make_shared<ofxModalTheme>();
    confirm.setup();
    confirm.setTheme(modalTheme);
    modalMessage.setup();
    modalMessage.setTheme(modalTheme);

    ofAddListener(visualProgramming->fileDialog.fileDialogEvent, this, &ofApp::onFileDialogResponse);

    // NET
    isInternetAvailable = false;
    isCheckingRelease = false;

#if !defined(TARGET_WIN32)
    ofxSimpleHttp::createSslContext();
#endif

    http.addCustomHttpHeader("Accept", "application/zip");
    ofAddListener(http.httpResponse, this, &ofApp::newResponse);

    // Check for updates
    confirm.addListener(this, &ofApp::onModalEvent);
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
            visualProgramming->activateDSP();
        }
    }

    if(isWindowResized){
        isWindowResized = false;
        loggerBounds->width = ofGetWindowWidth();
        loggerBounds->y = ofGetWindowHeight() - (258*visualProgramming->scaleFactor);
        screenLoggerChannel->setDrawBounds(*loggerBounds);
    }

    if(!isInited){
        isInited = true;
        // set logger dimensions
        loggerBounds->set(0,ofGetWindowHeight()-(258*visualProgramming->scaleFactor),ofGetWindowWidth(),240*visualProgramming->scaleFactor);
        screenLoggerChannel->setDrawBounds(*loggerBounds);
        // reinit DSP
        resetInitDSP = ofGetElapsedTimeMillis();
        autoinitDSP = true;
    }

    http.update();

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

    // Updates Downloading Progress
    if(http.getPendingDownloads() > 0){
        ofSetColor(64,128,255,100);
        ofDrawRectRounded((ofGetWindowWidth()-(333*visualProgramming->scaleFactor))/2,(ofGetWindowHeight()-(33*visualProgramming->scaleFactor))/2,(333*visualProgramming->scaleFactor)*http.getCurrentDownloadProgress(),(33*visualProgramming->scaleFactor),3);
        ofSetColor(255);
        visualProgramming->font->draw(ofToString(static_cast<int>(http.getCurrentDownloadProgress()*100))+"%",visualProgramming->fontSize,(ofGetWindowWidth()-(333*visualProgramming->scaleFactor))/2 + ((333*visualProgramming->scaleFactor)*http.getCurrentDownloadProgress()/2),ofGetWindowHeight()/2 + 6*visualProgramming->scaleFactor);
    }

    // Mosaic Visual Programming
    ofSetColor(255,255,255);
    visualProgramming->draw();

    // MAIN MENU
    ofSetColor(255,255,255);
    drawMainMenu();

    // LOGGER
    if(isLoggerON){
        screenLoggerChannel->draw();
    }

    if(setupLoaded && ofGetElapsedTimeMillis() > 1000){
        setupLoaded = false;
        visualProgramming->fileDialog.notificationPopup(WINDOW_TITLE, "Live Visual Patching Creative-Coding Platform\nhttps://mosaic.d3cod3.org/");
    }

}

//--------------------------------------------------------------
void ofApp::drawMainMenu(){
    mainMenu.begin();

    {
        ImGui::BeginMainMenuBar();

        {
            if(ImGui::BeginMenu("File")){
                if(ImGui::MenuItem("New")){
                    visualProgramming->newPatch();
                }
                if(ImGui::MenuItem("Open")){
                    visualProgramming->fileDialog.openFile("open patch","Open a Mosaic patch");
                }
                if(ImGui::MenuItem("Save As...")){
                    string newFileName = "mosaicPatch_"+ofGetTimestampString("%y%m%d")+".xml";
                    visualProgramming->fileDialog.saveFile("save patch","Save Mosaic patch as",newFileName);
                }
                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Separator();
                ImGui::Spacing();
                if(ImGui::MenuItem("Quit")){
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
                for(map<string,vector<string>>::iterator it = exampleMenuMatrix.begin(); it != exampleMenuMatrix.end(); it++ ){
                    if(ImGui::BeginMenu(it->first.c_str())){
                        for(int j=0;j<static_cast<int>(it->second.size());j++){
                            if(ImGui::MenuItem(it->second.at(j).c_str())){
                                createObjectFromFile(getFileFromExampleFilename(it->second.at(j)),true);
                            }
                        }
                        ImGui::EndMenu();
                    }
                }
                ImGui::EndMenu();
            }


            if(ImGui::BeginMenu("Sound")){
                if(ImGui::MenuItem("DSP ON")){
                    visualProgramming->activateDSP();
                }
                if(ImGui::MenuItem("DSP OFF")){
                    visualProgramming->deactivateDSP();
                }
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
                if(ImGui::Checkbox("Profiler",&visualProgramming->profilerActive)){
                    TIME_SAMPLE_SET_ENABLED(visualProgramming->profilerActive);
                }
                if(ImGui::Checkbox("Logger",&isLoggerON)){

                }
                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Separator();
                ImGui::Spacing();
                if(ImGui::MenuItem("Screenshot")){
                    takeScreenshot = true;
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

        if(showRightClickMenu){
            ImGui::SetNextWindowSize(ofVec2f(200*visualProgramming->scaleFactor,340*visualProgramming->scaleFactor), ImGuiSetCond_FirstUseEver);
            ImGui::SetNextWindowPos(ofVec2f(ofGetMouseX(),ofGetMouseY()), ImGuiSetCond_Appearing);
            ImGui::Begin("Objects", &showRightClickMenu,ImGuiWindowFlags_NoSavedSettings);
            isHoverMenu = ImGui::IsWindowHovered();
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
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
void ofApp::onModalEvent(ofxModalEvent e){
    if (e.type == ofxModalEvent::CONFIRM){
        // Download Mosaic Last release
        mosaicURL = "";

        if(VERSION != lastRelease){
            string fileName;

#ifdef TARGET_OSX
            fileName = "Mosaic_v"+lastRelease+"_osx_release.zip";
            mosaicURL = "https://github.com/d3cod3/Mosaic/releases/download/"+lastRelease+"/"+fileName;
#elif defined(TARGET_WIN32)
            fileName = "Mosaic_v"+lastRelease+"_windows_release.zip";
            mosaicURL = "https://github.com/d3cod3/Mosaic/releases/download/"+lastRelease+"/"+fileName;
#endif

            #ifdef TARGET_LINUX
            ofLaunchBrowser("https://gist.github.com/d3cod3/2704377f0e7b9e844d775ae0151cd688#file-update_mosaic-sh");
            #else
            if(mosaicURL != ""){
                http.setUserAgent(USER_AGENT);
                http.fetchURLToDisk(mosaicURL,true,userHome+"/Downloads");
            }else{
                ofLog(OF_LOG_ERROR,"There was an error trying to download Mosaic update, please retry next time!");
            }
            #endif

        }
    }
}

//--------------------------------------------------------------
void ofApp::onFileDialogResponse(ofxThreadedFileDialogResponse &response){
    if(response.id == "open patch"){
        ofFile file(response.filepath);
        if (file.exists()){
            string fileExtension = ofToUpper(file.getExtension());
            if(fileExtension == "XML") {
                patchToLoad = file.getAbsolutePath();
                loadNewPatch = true;
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
void ofApp::newResponse(ofxSimpleHttpResponse &r){
    if(r.url == mosaicURL){
        modalMessage.setTitle("Mosaic Update");
        modalMessage.alert("Mosaic last release downloaded! Just unzip it and overwrite your previous version.");
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
void ofApp::quitMosaic(){
#if !defined(TARGET_WIN32)
    ofxSimpleHttp::destroySslContext();
#endif
    ofExit(0);
}

//--------------------------------------------------------------
void ofApp::initExamplesMenu(){
    vector<string> vecInit = {};

    vecInit = {};
    for(map<string,ofFile>::iterator it = exampleFiles.begin(); it != exampleFiles.end(); it++ ){
        if(it->second.getExtension() == "xml"){
            //ofLog(OF_LOG_NOTICE,"%s",it->second.getBaseName().c_str());
            vecInit.push_back(it->second.getFileName());
        }
    }
    exampleMenuMatrix["mosaic"] = vecInit;

    vecInit = {};
    for(map<string,ofFile>::iterator it = exampleFiles.begin(); it != exampleFiles.end(); it++ ){
        if(it->second.getExtension() == "sh"){
            vecInit.push_back(it->second.getFileName());
        }
    }
    exampleMenuMatrix["bash"] = vecInit;

    vecInit = {};
    for(map<string,ofFile>::iterator it = exampleFiles.begin(); it != exampleFiles.end(); it++ ){
        if(it->second.getExtension() == "frag"){
            vecInit.push_back(it->second.getFileName());
        }
    }
    exampleMenuMatrix["glsl"] = vecInit;

    vecInit = {};
    for(map<string,ofFile>::iterator it = exampleFiles.begin(); it != exampleFiles.end(); it++ ){
        if(it->second.getExtension() == "lua"){
            vecInit.push_back(it->second.getFileName());
        }
    }
    exampleMenuMatrix["lua"] = vecInit;

    vecInit = {};
    for(map<string,ofFile>::iterator it = exampleFiles.begin(); it != exampleFiles.end(); it++ ){
        if(it->second.getExtension() == "java"){
            vecInit.push_back(it->second.getFileName());
        }
    }
    exampleMenuMatrix["processing"] = vecInit;

    vecInit = {};
    for(map<string,ofFile>::iterator it = exampleFiles.begin(); it != exampleFiles.end(); it++ ){
        if(it->second.getExtension() == "pd"){
            vecInit.push_back(it->second.getFileName());
        }
    }
    exampleMenuMatrix["pure data"] = vecInit;

    vecInit = {};
    for(map<string,ofFile>::iterator it = exampleFiles.begin(); it != exampleFiles.end(); it++ ){
        if(it->second.getExtension() == "py"){
            vecInit.push_back(it->second.getFileName());
        }
    }
    exampleMenuMatrix["python"] = vecInit;
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

    #endif

    ofDirectory examplesDir;
    examplesDir.listDir(ofToDataPath("../examples"));
    recursiveScanDirectory(examplesDir);

}

//--------------------------------------------------------------
void ofApp::recursiveScanDirectory(ofDirectory dir){
    size_t size = dir.listDir();
    dir.sort();

    for (size_t i = 0; i < size; i++){
        if (dir.getFile(i).isDirectory()==1){
            ofDirectory newDir;
            newDir.listDir(dir.getFile(i).getAbsolutePath());
            recursiveScanDirectory( newDir );
        }else{
            ofFile tempFile(dir.getPath(i));
            exampleFiles[tempFile.getFileName()] = tempFile;
        }
    }
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
        ofLog(OF_LOG_NOTICE," ");
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
    ofLog(OF_LOG_NOTICE," ");
    ofLog(OF_LOG_NOTICE,"CHECKING FOR MOSAIC UPDATES...");

    string actualVersion = VERSION;
    if(ofToInt(string(1,actualVersion.at(0))) < ofToInt(string(1,lastRelease.at(0))) || ( ofToInt(string(1,actualVersion.at(0))) == ofToInt(string(1,lastRelease.at(0))) && ofToInt(string(1,actualVersion.at(2))) < ofToInt(string(1,lastRelease.at(2))) ) || ( ofToInt(string(1,actualVersion.at(0))) == ofToInt(string(1,lastRelease.at(0))) && ofToInt(string(1,actualVersion.at(2))) == ofToInt(string(1,lastRelease.at(2))) && ofToInt(string(1,actualVersion.at(4))) < ofToInt(string(1,lastRelease.at(4))) )){
        ofLog(OF_LOG_NOTICE,"[verbose]NEW MOSAIC "+lastRelease+" UPDATE AVAILABLE!");
        confirm.setTitle("Mosaic Update");
        confirm.setMessage("Mosaic "+lastRelease+" release available, would you like to update?");
        confirm.setButtonLabel("ok");
        confirm.show();
    }else{
        ofLog(OF_LOG_NOTICE,"NO NEW MOSAIC UPDATE AVAILABLE!");
    }

}

//--------------------------------------------------------------
void ofApp::createObjectFromFile(ofFile file,bool temp){
    if (file.exists()){
        string fileExtension = ofToUpper(file.getExtension());
        if(fileExtension == "XML") {
            if(temp){
                visualProgramming->newTempPatchFromFile(file.getAbsolutePath());
            }else{
                visualProgramming->openPatch(file.getAbsolutePath());
            }
            // reinit DSP
            resetInitDSP = ofGetElapsedTimeMillis();
            autoinitDSP = true;
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
ofFile ofApp::getFileFromExampleFilename(string filename){
    for(map<string,ofFile>::iterator it = exampleFiles.begin(); it != exampleFiles.end(); it++ ){
        if(filename == it->first){
            return it->second;
        }
    }

    ofFile n(ofToDataPath("release.txt"));
    return n;
}
