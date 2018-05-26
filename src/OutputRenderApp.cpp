#include "OutputRenderApp.h"

//--------------------------------------------------------------
void OutputRenderApp::setup(){

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
