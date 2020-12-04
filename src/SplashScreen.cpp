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

#include "SplashScreen.h"

//--------------------------------------------------------------
void SplashScreen::setup(){
    ofSetEscapeQuitsApp(false);
    ofSetVerticalSync(true);

    if(ofGetScreenWidth() >= 2560 && ofGetScreenHeight() >= 1600){ // RETINA SCREEN
        ofSetWindowShape(854,560);
        ofSetWindowPosition(ofGetScreenWidth()/2 - 427,ofGetScreenHeight()/2 - 280);
        font.load(ofToDataPath("fonts/IBMPlexMono-Medium.ttf"),160);
        fontSmall.load(ofToDataPath("fonts/IBMPlexMono-Medium.ttf"),48);
    }else{
        font.load(ofToDataPath("fonts/IBMPlexMono-Medium.ttf"),80);
        fontSmall.load(ofToDataPath("fonts/IBMPlexMono-Medium.ttf"),24);
    }

    startTime = ofGetElapsedTimeMillis();

    // load background
#ifdef TARGET_LINUX
    background.load("videos/splash_background.mp4");
#elif defined(TARGET_OSX)
    background.load("videos/splash_background.mp4");
#elif defined(TARGET_WIN32)
    background.load("videos/splash_background.avi");
#endif

    background.setLoopState(OF_LOOP_NORMAL);
    background.play();

    splashWindow->makeCurrent();
}

//--------------------------------------------------------------
void SplashScreen::update(){
    background.update();

    if(ofGetElapsedTimeMillis()-startTime > 6000){
        splashWindow->setWindowShouldClose();
    }
}

//--------------------------------------------------------------
void SplashScreen::draw(){
    ofBackground(0);
    ofEnableAlphaBlending();

    ofSetColor(255);
    // draw background
    background.draw(-40,0,splashWindow->getWidth()+80,splashWindow->getHeight());

    ofSetColor(0,255,255,66);
    if(ofGetScreenWidth() >= 2560 && ofGetScreenHeight() >= 1600){ // RETINA SCREEN
        font.drawString(VERSION_GRAPHIC,452,182);
        fontSmall.drawString("BETA",splashWindow->getWidth()-360,splashWindow->getHeight()-200);
    }else{
        font.drawString(VERSION_GRAPHIC,226,91);
        fontSmall.drawString("BETA",splashWindow->getWidth()-180,splashWindow->getHeight()-100);
    }

}

//--------------------------------------------------------------
void SplashScreen::mousePressed(int x, int y, int button){
    splashWindow->setWindowShouldClose();
}
