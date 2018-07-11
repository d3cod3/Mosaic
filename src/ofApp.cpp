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
    ofSetVerticalSync(false);
    ofSetDrawBitmapMode(OF_BITMAPMODE_SIMPLE);
    ofSetLogLevel(OF_LOG_NOTICE);
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
    ofLog(OF_LOG_NOTICE,"%s | %s",WINDOW_TITLE,DESCRIPTION);

    // Visual Programming Environment Load
    visualProgramming = new ofxVisualProgramming();
    visualProgramming->setup();

    // GUI
    mosaicLogo = new ofImage("images/logo_1024_bw.png");

    mainMenu = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
    mainMenu->addHeader("Mosaic",false);
    mainMenu->addBreak();
    mainMenu->addBreak();
    mainMenu->addLabel("PATCH");
    mainMenu->addButton("  new");
    mainMenu->addButton("  open");
    mainMenu->addButton("  save as");
    mainMenu->addBreak();
    ofxDatGuiFolder* audioFolder = mainMenu->addFolder("SOUND CONFIG");
    audioFolder->addBreak();
    audioFolder->addLabel("  INPUT DEVICE");
    audioINputDevices = new ofxDatGuiDropdown("Select audio input device",visualProgramming->audioDevicesString);
    audioINputDevices->onDropdownEvent(this, &ofApp::onDropdownEvent);
    audioFolder->attachItem(audioINputDevices);
    audioINputDevices->select(visualProgramming->audioINDev);
    audioFolder->addBreak();
    audioFolder->addLabel("  OUTPUT DEVICE");
    audioOUTputDevices = new ofxDatGuiDropdown("Select audio output device",visualProgramming->audioDevicesString);
    audioOUTputDevices->onDropdownEvent(this, &ofApp::onDropdownEvent);
    audioFolder->attachItem(audioOUTputDevices);
    audioOUTputDevices->select(visualProgramming->audioOUTDev);
    mainMenu->addBreak();
    mainMenu->addLabel("SYSTEM");
    mainMenu->addToggle("  PROFILER");
    mainMenu->addBreak();
    mainMenu->addBreak();
    mainMenu->addBreak();
    mainMenu->addButton("quit");
    mainMenu->addBreak();

    ofxDatGuiFooter* footer = mainMenu->addFooter();
    footer->setLabelWhenExpanded("collapse");
    footer->setLabelWhenCollapsed("MOSAIC");


    mainMenu->onButtonEvent(this, &ofApp::onButtonEvent);
    mainMenu->onToggleEvent(this, &ofApp::onToggleEvent);
    mainMenu->onDropdownEvent(this, &ofApp::onDropdownEvent);

}

//--------------------------------------------------------------
void ofApp::update(){

    windowTitle = visualProgramming->currentPatchFile+" - "+WINDOW_TITLE;
    ofSetWindowTitle(windowTitle);

    visualProgramming->update();

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

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(20);

    // BACKGROUND GUI
    ofSetColor(255,255,255,16);
    mosaicLogo->draw(ofGetWindowWidth()/2 - (128*visualProgramming->scaleFactor),(ofGetWindowHeight()- (240*visualProgramming->scaleFactor))/2 - (128*visualProgramming->scaleFactor),256*visualProgramming->scaleFactor,256*visualProgramming->scaleFactor);

    // Mosaic Visual Programming
    ofSetColor(255,255,255);
    visualProgramming->draw();

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
                audioINputDevices->select(visualProgramming->audioINDev);
                audioOUTputDevices->select(visualProgramming->audioOUTDev);
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
                    audioINputDevices->select(visualProgramming->audioINDev);
                    audioOUTputDevices->select(visualProgramming->audioOUTDev);
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
void ofApp::quitMosaic(){
    ofExit(0);
}
