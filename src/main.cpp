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

#include "ofMain.h"
#include "ofApp.h"
#include "LoggerApp.h"
#include "ofAppGLFWWindow.h"
#include "ofxTimeMeasurements.h"

//========================================================================
int main(int argc, char *argv[]){

    vector<string> options;

    if(argc > 1){
        for(int i = 0; i < argc; i++){
            options.push_back(argv[i]);
        }
    }

    ofGLFWWindowSettings settings;
    int major = 0, minor = -1; // momentarily deactivated -- TODO
    if(major > 0 && major < 5 && minor > -1 && minor < 6) {
        settings.setGLVersion(major, minor);
    }
    settings.stencilBits = 0;
    settings.setSize(1280, 720);
    settings.setPosition(ofVec2f(0,0));
    settings.resizable = true;

    // Mosaic main visual-programming window
    shared_ptr<ofAppBaseWindow> mosaicWindow = ofCreateWindow(settings);
    shared_ptr<ofApp> mosaicApp(new ofApp);

    TIME_SAMPLE_SET_FRAMERATE(30);

    mosaicApp->arguments = options;

    settings.setSize(854, 240);
    settings.setPosition(ofVec2f(0,780));
    settings.resizable = true;
    settings.shareContextWith = mosaicWindow;

    // Logger
    shared_ptr<ofAppBaseWindow> loggerWindow = ofCreateWindow(settings);
    shared_ptr<LoggerApp> loggerApp(new LoggerApp);

    mosaicApp->loggerApp = loggerApp;

    ofRunApp(loggerWindow, loggerApp);
    ofRunApp(mosaicWindow, mosaicApp);
    ofRunMainLoop();

    // done
    return EXIT_SUCCESS;

}
