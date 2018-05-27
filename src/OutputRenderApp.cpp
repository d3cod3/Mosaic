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

#include "OutputRenderApp.h"

//--------------------------------------------------------------
void OutputRenderApp::setup(){

    ofSetWindowTitle("Main Projector");
    ofSetLogLevel("ofxLua", OF_LOG_VERBOSE);

    ///////////////////////////////////////////
    // Scripting -- TESTING
    testingScript = "scripts/00_Mosaic_ofxLua_testing.lua";

    lua.init(true);
    lua.addListener(this);
    lua.doScript(testingScript, true);
    ///////////////////////////////////////////

    ///////////////////////////////////////////
    // LUA SETUP
    lua.scriptSetup();
    ///////////////////////////////////////////

}

//--------------------------------------------------------------
void OutputRenderApp::update(){
    ///////////////////////////////////////////
    // LUA UPDATE
    lua.scriptUpdate();
    ///////////////////////////////////////////
}

//--------------------------------------------------------------
void OutputRenderApp::draw(){
    ///////////////////////////////////////////
    // LUA DRAW
    lua.scriptDraw();
    ///////////////////////////////////////////
}

//--------------------------------------------------------------
void OutputRenderApp::exit() {
    ///////////////////////////////////////////
    // LUA EXIT
    lua.scriptExit();
    lua.clear();
    ///////////////////////////////////////////
}

//--------------------------------------------------------------
void OutputRenderApp::keyPressed(int key){
    ///////////////////////////////////////////
    // LUA keyPressed
    lua.scriptKeyPressed(key);
    ///////////////////////////////////////////
}

//--------------------------------------------------------------
void OutputRenderApp::mouseMoved(int x, int y ){
    ///////////////////////////////////////////
    // LUA mouseMoved
    lua.scriptMouseMoved(x, y);
    ///////////////////////////////////////////
}

//--------------------------------------------------------------
void OutputRenderApp::mouseDragged(int x, int y, int button){
    ///////////////////////////////////////////
    // LUA mouseDragged
    lua.scriptMouseDragged(x, y, button);
    ///////////////////////////////////////////
}

//--------------------------------------------------------------
void OutputRenderApp::mousePressed(int x, int y, int button){
    ///////////////////////////////////////////
    // LUA mousePressed
    lua.scriptMousePressed(x, y, button);
    ///////////////////////////////////////////
}

//--------------------------------------------------------------
void OutputRenderApp::mouseReleased(int x, int y, int button){
    ///////////////////////////////////////////
    // LUA mouseReleased
    lua.scriptMouseReleased(x, y, button);
    ///////////////////////////////////////////
}

//--------------------------------------------------------------
void OutputRenderApp::errorReceived(std::string& msg) {
    ofLogNotice() << "got a script error: " << msg;
}
