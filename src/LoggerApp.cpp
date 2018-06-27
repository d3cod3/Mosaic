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

#include "LoggerApp.h"

//--------------------------------------------------------------
void LoggerApp::setup(){

    ofSetWindowTitle("Console");
    ofSetFrameRate(30);
    ofEnableAlphaBlending();
    ofSetBackgroundAuto(true);

    isInited = false;

    // RETINA FIX
    if(ofGetScreenWidth() >= RETINA_MIN_WIDTH && ofGetScreenHeight() >= RETINA_MIN_HEIGHT){
        ofSetWindowShape(CONSOLE_WINDOW_START_WIDTH*2, CONSOLE_WINDOW_START_HEIGHT*2);
        ofSetWindowPosition(0,(WINDOW_START_HEIGHT*2)+140);
    }

    screenLoggerChannel = shared_ptr<ofxScreenLoggerChannel>(new ofxScreenLoggerChannel());
    ofSetLoggerChannel(screenLoggerChannel);
    screenLoggerChannel->setBackgroundColor(ofColor(0,0,0,20));
    screenLoggerChannel->setTextColor(ofColor(203,224,254));
    // MORE RETINA FIX
    if(ofGetScreenWidth() >= RETINA_MIN_WIDTH && ofGetScreenHeight() >= RETINA_MIN_HEIGHT){
        screenLoggerChannel->setup(MAIN_FONT,26);
        screenLoggerChannel->setIsRetina();
    }else{
        screenLoggerChannel->setup(MAIN_FONT,14);
    }
    screenLoggerChannel->setPrefixTimestamp(true);

    bounds = screenLoggerChannel->getDrawBounds();
    bounds.width = ofGetWindowWidth();
    bounds.height = ofGetWindowHeight();
    screenLoggerChannel->setDrawBounds(bounds);

    ofLogNotice("setup", "Starting Mosaic!");

}

//--------------------------------------------------------------
void LoggerApp::update(){
    if(!isInited){
        isInited = true;
    }
}

//--------------------------------------------------------------
void LoggerApp::draw(){
    ofBackground(20,20,20);
    screenLoggerChannel->draw();
}

//--------------------------------------------------------------
void LoggerApp::keyPressed(int key){
    //ofLogNotice("keyPressed", "TESTING");
}

//--------------------------------------------------------------
void LoggerApp::windowResized(int w, int h){
    if(isInited){
        bounds = screenLoggerChannel->getDrawBounds();
        bounds.width = ofGetWindowWidth();
        bounds.height = ofGetWindowHeight();
        screenLoggerChannel->setDrawBounds(bounds);
    }
}
