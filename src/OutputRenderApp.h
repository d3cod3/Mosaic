#pragma once

#include "ofMain.h"

#include "config.h"
#include "includes.h"

class OutputRenderApp: public ofBaseApp, ofxLuaListener {

public:

    void setup();
    void update();
    void draw();
    void exit();

    // Keyboard Events
    void keyPressed(int key);

    // Mouse Events
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);

    // ofxLua error callback
    void errorReceived(std::string& msg);

    // Scripting
    ofxLua          lua;
    string          testingScript;


private:


protected:


};
