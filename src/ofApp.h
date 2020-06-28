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

    void drawImGuiInterface();

    // Keyboard Events
    void keyPressed(ofKeyEventArgs &e);
    void keyReleased(ofKeyEventArgs &e);

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

    // NET Events
    void urlResponse(ofHttpResponse & response);

    // Filepath watcher Events
    void pathChanged(const PathWatcher::Event &event);

    void quitMosaic();

    // TIMING
    void            setMosaicFrameRate(float fps);

    // UTILS
    void            initDataFolderFromBundle();
    bool            checkInternetReachability();
    void            checkForUpdates();
    void            createDirectoryNode(ofFile file);
    void            createObjectFromFile(ofFile file,bool temp);

    // Code Editor
    void            initScriptLanguages();
    void            initNewCodeEditor(ofFile file);
    void            removeScriptFromCodeEditor(string filename);

    // Command line arguments
    vector<string>              arguments;

    // CORE
    ofDirectory                 examplesRoot;
    std::filesystem::path       mosaicPath;
    std::filesystem::path       mosaicExamplesPath;
    string                      mosaicURL;
    string                      userHome;

    // GUI
    ofxImGui::Gui                   mainMenu;
    imgui_addons::ImGuiFileBrowser  fileDialog;

    ofImage                         *mosaicLogo;
    GLuint                          mosaicLogoID;
    string                          shortcutFunc;
    bool                            createSearchedObject;
    bool                            showConsoleWindow;
    bool                            showCodeEditor;
    bool                            showAboutWindow;
    bool                            showRightClickMenu;
    bool                            isHoverMenu;
    bool                            openPatch;
    bool                            savePatchAs;

    // CODE EDITOR
    TextEditor::LanguageDefinition  bashLang;
    TextEditor::LanguageDefinition  luaLang;
    TextEditor::LanguageDefinition  pythonLang;
    TextEditor::LanguageDefinition  javaProcessingLang;
    TextEditor::LanguageDefinition  glslLang;
    ofRectangle                     codeEditorRect;
    ofImage                         editorFullscreenButtonSource;
    GLuint                          editorFullscreenButtonID;
    map<string,TextEditor>          codeEditors;
    map<string,PathWatcher*>         codeWatchers;
    vector<string>                  editedFilesPaths;
    vector<string>                  editedFilesNames;
    string                          actualEditedFilePath;
    string                          actualEditedFileName;
    string                          scriptToRemoveFromCodeEditor;
    int                             actualCodeEditor;
    bool                            isCodeEditorON;
    bool                            isHoverCodeEditor;
    bool                            isCodeEditorFullWindow;

    // LOGGER
    bool                        isInited;
    bool                        isWindowResized;
    bool                        isLoggerON;
    ofRectangle                 loggerRect;
    bool                        isHoverLogger;

    // Core visual programming
    ofxVisualProgramming        *visualProgramming;
    SynchTimer                  mosaicTiming;
    int                         mosaicFPS;
    string                      windowTitle;
    string                      patchToLoad;
    bool                        loadNewPatch;
    bool                        autoinitDSP;
    size_t                      resetInitDSP;

    // NET
    int                         lastReleaseResp;
    bool                        isInternetAvailable;
    bool                        isCheckingRelease;
    string                      lastRelease;


private:
    shared_ptr<MosaicLoggerChannel>     mosaicLoggerChannel;

    string                              lastScreenshot;
    bool                                takeScreenshot;
    bool                                saveNewScreenshot;

protected:


};
