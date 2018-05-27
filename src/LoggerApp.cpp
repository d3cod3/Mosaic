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

    ofSetWindowTitle("Logger");
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    ofSetBackgroundAuto(true);

    screenLoggerChannel = shared_ptr<ofxScreenLoggerChannel>(new ofxScreenLoggerChannel());
    ofSetLoggerChannel(screenLoggerChannel);
    screenLoggerChannel->setBackgroundColor(ofColor(0,0,0,20));
    screenLoggerChannel->setTextColor(ofColor(203,224,254));
    screenLoggerChannel->setPrefixTimestamp(true);

    ofRectangle bounds = screenLoggerChannel->getDrawBounds();
    bounds.width = ofGetWindowWidth();
    bounds.height = ofGetWindowHeight();
    screenLoggerChannel->setDrawBounds(bounds);

    ofLogNotice("setup", "Start the show!");

}

//--------------------------------------------------------------
void LoggerApp::update(){

}

//--------------------------------------------------------------
void LoggerApp::draw(){
    ofBackground(20,20,20);
    screenLoggerChannel->draw();
}

//--------------------------------------------------------------
void LoggerApp::keyPressed(int key){
    ofLogNotice("keyPressed", "TESTING");
}

//--------------------------------------------------------------
void LoggerApp::windowResized(int w, int h){
    ofRectangle bounds = screenLoggerChannel->getDrawBounds();
    bounds.width = ofGetWindowWidth();
    bounds.height = ofGetWindowHeight();
    screenLoggerChannel->setDrawBounds(bounds);
}
