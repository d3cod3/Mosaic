/*==============================================================================

    Mosaic: OF Visual Patching Developer Platform

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
    ofSetDrawBitmapMode(OF_BITMAPMODE_SIMPLE);
    ofSetLogLevel("Mosaic",OF_LOG_NOTICE);

#ifdef TARGET_OSX
    initDataFolderFromBundle();
#endif

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
    isInited = false;
    isWindowResized = false;
    loggerBounds = new ofRectangle();
    screenLoggerChannel = shared_ptr<ofxScreenLoggerChannel>(new ofxScreenLoggerChannel());
    ofSetLoggerChannel(screenLoggerChannel);
    screenLoggerChannel->setBackgroundColor(ofColor(0,0,0,200));
    screenLoggerChannel->setTextColor(ofColor(203,224,254));
    // MORE RETINA FIX
    if(ofGetScreenWidth() >= RETINA_MIN_WIDTH && ofGetScreenHeight() >= RETINA_MIN_HEIGHT){
        screenLoggerChannel->setup(MAIN_FONT,26);
        screenLoggerChannel->setIsRetina();
    }else{
        screenLoggerChannel->setup(MAIN_FONT,14);
    }
    screenLoggerChannel->setPrefixTimestamp(true);
    screenLoggerChannel->setMaxBufferCount(512);

    ofLog(OF_LOG_NOTICE,"%s | %s",WINDOW_TITLE,DESCRIPTION);
    ofLog(OF_LOG_NOTICE," ");
    ofLog(OF_LOG_NOTICE,"This project deals with the idea of integrate/amplify human-machine communication, offering a real-time flowchart based visual interface for high level creative coding. As live-coding scripting languages offer a high level coding environment, ofxVisualProgramming and the Mosaic Project as his parent layer container, aim at a high level visual-programming environment, with embedded multi scripting languages availability (Lua, Python, GLSL and BASH).");

    // Visual Programming Environment Load
    visualProgramming = new ofxVisualProgramming();
    visualProgramming->setup();

    // GUI
    mosaicLogo = new ofImage("images/logo_1024_bw.png");

    guiThemeRetina = new ofxDatGuiThemeRetina();
    mainMenu = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
    mainMenu->setAutoDraw(false);
    mainMenu->addHeader("Mosaic",false);
    mainMenu->addBreak();
    mainMenu->addBreak();
    mainMenu->addLabel("PATCH");
    mainMenu->addButton("  new");
    mainMenu->addButton("  open");
    mainMenu->addButton("  save as");
    mainMenu->addBreak();
    mainMenu->addBreak();
    ofxDatGuiFolder* audioFolder = mainMenu->addFolder("SOUND CONFIG");
    audioFolder->addBreak();
    audioFolder->addLabel("  INPUT DEVICE");
    audioINputDevices = new ofxDatGuiDropdown("Select audio input device",visualProgramming->audioDevicesStringIN);
    audioINputDevices->onDropdownEvent(this, &ofApp::onDropdownEvent);
    audioFolder->attachItem(audioINputDevices);
    audioINputDevices->select(visualProgramming->audioINDev);
    audioFolder->addBreak();
    audioFolder->addLabel("  OUTPUT DEVICE");
    audioOUTputDevices = new ofxDatGuiDropdown("Select audio output device",visualProgramming->audioDevicesStringOUT);
    audioOUTputDevices->onDropdownEvent(this, &ofApp::onDropdownEvent);
    audioFolder->attachItem(audioOUTputDevices);
    audioOUTputDevices->select(visualProgramming->audioOUTDev);
    mainMenu->addBreak();
    mainMenu->addBreak();
    mainMenu->addLabel("SYSTEM");
    mainMenu->addBreak();
    dspONOFF = mainMenu->addToggle("  DSP",visualProgramming->dspON);
    mainMenu->addBreak();
    mainMenu->addToggle("  PROFILER");
    mainMenu->addBreak();
    mainMenu->addBreak();
    mainMenu->addBreak();
    mainMenu->addButton("quit");
    mainMenu->addBreak();

    ofxDatGuiFooter* footer = mainMenu->addFooter();
    footer->setLabelWhenExpanded("collapse");
    footer->setLabelWhenCollapsed("MOSAIC");

    // RETINA FIX
    if(ofGetScreenWidth() >= RETINA_MIN_WIDTH && ofGetScreenHeight() >= RETINA_MIN_HEIGHT){ // RETINA SCREEN
        mainMenu->setTheme(guiThemeRetina);
    }

    mainMenu->onButtonEvent(this, &ofApp::onButtonEvent);
    mainMenu->onToggleEvent(this, &ofApp::onToggleEvent);
    mainMenu->onDropdownEvent(this, &ofApp::onDropdownEvent);

    // MODALS
    confirm.setup();
    modalMessage.setup();

    // NET
    ofxSimpleHttp::createSslContext();
    http.addCustomHttpHeader("Accept", "application/zip");
    ofAddListener(http.httpResponse, this, &ofApp::newResponse);

    // Check for updates
    confirm.addListener(this, &ofApp::onModalEvent);

    if(checkInternetReachability()){
        checkForUpdates();
    }

}

//--------------------------------------------------------------
void ofApp::update(){

    windowTitle = visualProgramming->currentPatchFile+" - "+WINDOW_TITLE;
    ofSetWindowTitle(windowTitle);

    visualProgramming->update();
    if(visualProgramming->dspON){
        dspONOFF->setLabelColor(ofColor::fromHex(0xFFD00B));
        dspONOFF->setChecked(true);
    }else{
        dspONOFF->setLabelColor(ofColor::fromHex(0xEEEEEE));
        dspONOFF->setChecked(false);
    }

    if(!visualProgramming->draggingObject){
        mainMenu->update();
    }

    if(isWindowResized){
        isWindowResized = false;
        loggerBounds->width = ofGetWindowWidth();
        loggerBounds->y = ofGetWindowHeight() - (240*visualProgramming->scaleFactor);
        screenLoggerChannel->setDrawBounds(*loggerBounds);

        if(visualProgramming->gui->getHeight() > ofGetWindowHeight()-(240*visualProgramming->scaleFactor)){
            visualProgramming->gui->collapse();
        }else{
            visualProgramming->gui->expand();
        }
    }

    if(!isInited){
        isInited = true;
        // set logger dimensions
        loggerBounds->set(0,ofGetWindowHeight()-(240*visualProgramming->scaleFactor),ofGetWindowWidth(),240*visualProgramming->scaleFactor);
        screenLoggerChannel->setDrawBounds(*loggerBounds);
    }

    http.update();

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(20);

    // BACKGROUND GUI
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
    mainMenu->draw();

    // LOGGER
    screenLoggerChannel->draw();

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
        if (file.exists()){
            string fileExtension = ofToUpper(file.getExtension());
            if(fileExtension == "XML") {
                visualProgramming->openPatch(file.getAbsolutePath());
                for(size_t i=0;i<visualProgramming->audioDevicesID_IN.size();i++){
                    if(visualProgramming->audioDevicesID_IN.at(i) == visualProgramming->audioINDev){
                        audioINputDevices->select(i);
                        break;
                    }
                }
                for(size_t i=0;i<visualProgramming->audioDevicesID_OUT.size();i++){
                    if(visualProgramming->audioDevicesID_OUT.at(i) == visualProgramming->audioOUTDev){
                        audioOUTputDevices->select(i);
                        break;
                    }
                }
            }
        }
    }

}

//--------------------------------------------------------------
void ofApp::onButtonEvent(ofxDatGuiButtonEvent e){
    //cout << "onButtonEvent: " << e.target->getLabel() << endl;
    if(e.target->getLabel() == "  new"){
        visualProgramming->newPatch();
    }else if(e.target->getLabel() == "  open"){
        ofFileDialogResult openFileResult= ofSystemLoadDialog("Open a mosaic");
        if (openFileResult.bSuccess){
            ofFile file (openFileResult.getPath());
            if (file.exists()){
                string fileExtension = ofToUpper(file.getExtension());
                if(fileExtension == "XML") {
                    visualProgramming->openPatch(file.getAbsolutePath());
                    for(size_t i=0;i<visualProgramming->audioDevicesID_IN.size();i++){
                        if(visualProgramming->audioDevicesID_IN.at(i) == visualProgramming->audioINDev){
                            audioINputDevices->select(i);
                            break;
                        }
                    }
                    for(size_t i=0;i<visualProgramming->audioDevicesID_OUT.size();i++){
                        if(visualProgramming->audioDevicesID_OUT.at(i) == visualProgramming->audioOUTDev){
                            audioOUTputDevices->select(i);
                            break;
                        }
                    }
                }
            }
        }
    }else if(e.target->getLabel() == "  save as"){
        ofFileDialogResult saveFileResult = ofSystemSaveDialog("mosaicPatch.xml","Save mosaic as");
        if (saveFileResult.bSuccess){
            ofFile file (saveFileResult.getPath());
            visualProgramming->savePatchAs(file.getAbsolutePath());
        }
    }else if(e.target->getLabel() == "quit"){
        quitMosaic();
    }
}

//--------------------------------------------------------------
void ofApp::onToggleEvent(ofxDatGuiToggleEvent e){
    //cout << "onToggleEvent: " << e.target->getLabel() << endl;
    if(e.target->getLabel() == "  PROFILER"){
        visualProgramming->profilerActive = e.checked;
        TIME_SAMPLE_SET_ENABLED(visualProgramming->profilerActive);
    }else if(e.target->getLabel() == "  DSP"){
        if(e.checked){
            visualProgramming->activateDSP();
        }else{
            visualProgramming->deactivateDSP();
        }

    }
}

//--------------------------------------------------------------
void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e){
    //cout << "the option at index # " << e.child << " was selected " << endl;
    if(e.target == audioINputDevices){
        visualProgramming->setAudioInDevice(e.child);
    }else if(e.target == audioOUTputDevices){
        visualProgramming->setAudioOutDevice(e.child);
    }
    e.target->expand();
}

//--------------------------------------------------------------
void ofApp::onModalEvent(ofxModalEvent e){
    if (e.type == ofxModalEvent::CONFIRM){
        // Download Mosaic Last release
        ofHttpResponse resp = ofLoadURL("https://raw.githubusercontent.com/d3cod3/Mosaic/master/RELEASE.md");
        string lastRelease = resp.data.getText();
        mosaicURL = "";

        if(VERSION != lastRelease){
            string fileName;

#ifdef TARGET_LINUX
            fileName = "Mosaic_v"+lastRelease+"_linux64_release.tar.gz";
            mosaicURL = "https://mosaic.d3cod3.org/downloads/v"+lastRelease+"/"+fileName;
#elif defined(TARGET_OSX)
            fileName = "Mosaic_v"+lastRelease+"_osx_release.zip";
            mosaicURL = "https://mosaic.d3cod3.org/downloads/v"+lastRelease+"/"+fileName;
#elif defined(TARGET_WIN32)
            fileName = "Mosaic_v"+lastRelease+"_windows_release.zip";
            mosaicURL = "https://mosaic.d3cod3.org/downloads/v"+lastRelease+"/"+fileName;
#endif

            if(mosaicURL != ""){
                http.setUserAgent("Mozilla/5.0 (Macintosh; Intel Mac OS X 10.12; rv:62.0) Gecko/20100101 Firefox/62.0");
                http.fetchURLToDisk(mosaicURL,true,userHome+"/Downloads");
            }else{
                ofLog(OF_LOG_ERROR,"There was an error trying to download Mosaic update, please retry next time!");
            }

        }
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
void ofApp::quitMosaic(){
    ofxSimpleHttp::destroySslContext();
    ofExit(0);
}

//--------------------------------------------------------------
void ofApp::initDataFolderFromBundle(){
    string _bundleDataPath;

#ifdef TARGET_OSX
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
#elif defined(TARGET_WIN32) || defined(TARGET_LINUX)
    _bundleDataPath = ofToDataPath("",true);
#endif

    const char *homeDir = getenv("HOME");

#ifdef TARGET_WIN32

#elif defined(TARGET_OSX) || defined(TARGET_LINUX)
    if(!homeDir){
        struct passwd* pwd;
        pwd = getpwuid(getuid());
        if (pwd){
            homeDir = pwd->pw_dir;
        }
    }
#endif

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
#elif defined(TARGET_WIN32)
    cmd = "ping -n 1 www.github.com > null && echo okk || echo err";
    execFile = _popen(cmd.c_str(), "r");
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
#elif defined(TARGET_WIN32)
        _pclose(execFile);
#endif

        if(output == "okk"){
            ofLog(OF_LOG_NOTICE,"[verbose] INTERNET IS AVAILABLE!");
            return true;
        }else if(output == "err"){
            ofLog(OF_LOG_ERROR,"INTERNET IS NOT AVAILABLE!");
            return false;
        }
    }

    return false;

}

//--------------------------------------------------------------
void ofApp::checkForUpdates(){
    ofLog(OF_LOG_NOTICE," ");
    ofLog(OF_LOG_NOTICE,"CHECKING FOR MOSAIC UPDATES...");

    ofHttpResponse resp = ofLoadURL("https://raw.githubusercontent.com/d3cod3/Mosaic/master/RELEASE.md");

    string lastRelease = resp.data.getText();

    if(VERSION != lastRelease && resp.status != 404){
        ofLog(OF_LOG_NOTICE,"[verbose]NEW MOSAIC "+lastRelease+" UPDATE AVAILABLE!");
        confirm.setTitle("Mosaic Update");
        confirm.setMessage("Mosaic release "+lastRelease+" available, would you like to update?");
        confirm.setButtonLabel("ok");
        confirm.show();
    }else if(VERSION == lastRelease){
        ofLog(OF_LOG_NOTICE,"NO NEW MOSAIC UPDATE AVAILABLE!");
    }

}
