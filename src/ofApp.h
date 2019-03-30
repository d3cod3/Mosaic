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

#pragma once

#include "ofMain.h"

#if !defined(TARGET_WIN32)
#include <pwd.h>
#endif

#include <unistd.h>

#include "config.h"
#include "includes.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void exit();

    void drawMainMenu();

    // Keyboard Events
    void keyPressed(int key);
    void keyReleased(int key);

    // Mouse Events
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);

    // Misc Events
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    // GUI Events
    void onModalEvent(ofxModalEvent e);
    void onFileDialogResponse(ofxThreadedFileDialogResponse &response);

    // NET Events
    void newResponse(ofxSimpleHttpResponse &response);
    void urlResponse(ofHttpResponse & response);

    void quitMosaic();

    // UTILS
    void            initDataFolderFromBundle();
    bool            checkInternetReachability();
    void            checkForUpdates();

    // Command line arguments
    vector<string>              arguments;

    // CORE
    std::filesystem::path       mosaicPath;
    string                      mosaicURL;
    string                      userHome;
    bool                        setupLoaded;

    // GUI
    ofxImGui::Gui               mainMenu;
    ofxModalConfirm             confirm;
    ofxModalAlert               modalMessage;
    shared_ptr<ofxModalTheme>   modalTheme;
    bool                        showRightClickMenu;
    bool                        isHoverMenu;

    // LOGGER
    ofRectangle                 *loggerBounds;
    bool                        isInited;
    bool                        isWindowResized;
    bool                        isLoggerON;

    // Core visual programming
    ofxVisualProgramming        *visualProgramming;
    string                      windowTitle;
    string                      patchToLoad;
    bool                        loadNewPatch;

    // GUI
    ofImage                     *mosaicLogo;

    // NET
    ofxSimpleHttp               http;
    int                         lastReleaseResp;
    bool                        isInternetAvailable;
    bool                        isCheckingRelease;
    string                      lastRelease;


private:
    shared_ptr<ofxScreenLoggerChannel>  screenLoggerChannel;
    string                              lastScreenshot;
    bool                                takeScreenshot;
    bool                                saveNewScreenshot;

protected:


};
