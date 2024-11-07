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
#include "ofxVisualProgramming.h"

//--------------------------------------------------------------
void SplashScreen::setup(){
    ofSetEscapeQuitsApp(false);
    ofSetVerticalSync(true);

    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    glfwGetMonitorContentScale(primaryMonitor, &xScreenContentScale, &yScreenContentScale);

    // testing retina screens and GUI scaling
    //xScreenContentScale = 2;
    //yScreenContentScale = 2;

    float ww = 428*xScreenContentScale;
    float wh = 280*yScreenContentScale;

    ofSetWindowShape(ww,wh);
    ofSetWindowPosition(ofGetScreenWidth()/2 - (ww/2),ofGetScreenHeight()/2 - (wh/2));
    font.load(ofToDataPath("fonts/IBMPlexMono-Medium.ttf"),80*yScreenContentScale,true,true,true);
    fontSmall.load(ofToDataPath("fonts/IBMPlexMono-Medium.ttf"),24*yScreenContentScale,true,true,true);

    startTime = ofGetElapsedTimeMillis();

    // load logo
    logo.load("images/logo_1024_bw.png");

    // load background
    background.load("videos/splash_background.mp4");

    background.setLoopState(OF_LOOP_NONE);
    background.setVolume(0.0f);
    background.play();

}

//--------------------------------------------------------------
void SplashScreen::update(){
    background.update();

    if(ofGetElapsedTimeMillis()-startTime > 200 && ofGetElapsedTimeMillis()-startTime < 500){
        glfwFocusWindow(splashWindow->getGLFWWindow());
    }

    if(ofGetElapsedTimeMillis()-startTime > 4800){
        //splashWindow->setWindowShouldClose();
        glfwHideWindow(splashWindow->getGLFWWindow());
    }
}

//--------------------------------------------------------------
void SplashScreen::draw(){
    ofBackground(0);
    ofEnableAlphaBlending();

    // draw background
    ofSetColor(255);
    background.draw(-80*xScreenContentScale,-60*yScreenContentScale,splashWindow->getWidth()+(160*xScreenContentScale),splashWindow->getHeight()+(120*yScreenContentScale));

    // draw logo
    ofSetColor(255,255,255,216);
    logo.draw(20,10,128*xScreenContentScale,128*yScreenContentScale);

    // draw info
    ofSetColor(20,20,20,229);
    font.drawStringAsShapes(VERSION_GRAPHIC,226*xScreenContentScale,91*yScreenContentScale);
    fontSmall.drawStringAsShapes("BETA",splashWindow->getWidth()-(180*xScreenContentScale),splashWindow->getHeight()-(100*yScreenContentScale));

}

//--------------------------------------------------------------
void SplashScreen::mousePressed(int x, int y, int button){
    unusedArgs(x,y,button);

    //splashWindow->setWindowShouldClose();
    glfwHideWindow(splashWindow->getGLFWWindow());
}
