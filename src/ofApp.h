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
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);

    // Misc Events
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);

    // NET Events
    void urlResponse(ofHttpResponse & response);

    // Filepath watcher Events
    void pathChanged(const PathWatcher::Event &event);

    void quitMosaic();

    // VISUAL PROGRAMMING
    void            refreshScriptTabs();

    // TIMING
    void            setMosaicFrameRate(float fps);

    // UTILS
    void            initDataFolderFromBundle();
    bool            checkInternetReachability();
    void            checkForUpdates();
    void            checkAutoloadConfig();
    void            setAutoloadConfig();
    void            createDirectoryNode(ofFile file);
    void            createObjectFromFile(ofFile file,bool temp,int px=-1, int py=-1);
    bool            checkFileUsedInPatch(string filepath);

    // Code Editor
    void            initScriptLanguages();
    void            initNewCodeEditor(ofFile file);
    void            removeScriptFromCodeEditor(string filename);

    // DHT Chatroom
    void            setupDHTNode();
    void            updateDHTChat();
    bool            checkAKAIsValid(std::string aka);
    void            closeDHTNode();

    // Command line arguments
    vector<string>                  arguments;

    // CORE
    ofDirectory                     examplesRoot;
    std::filesystem::path           mosaicPath;
    std::filesystem::path           mosaicExamplesPath;
    std::filesystem::path           mosaicPluginsPath;
    string                          mosaicURL;
    string                          userHome;

    // GUI
    ofxImGui::Gui                   mainMenu;
    MosaicTheme                     *mainTheme;
    imgui_addons::ImGuiFileBrowser  fileDialog;
    ImFontConfig                    font_config;
    ImFont*                         font1;
    int                             suggestedFontSize;
    string                          iniFilePath;

    bool                            isRetina;
    int                             retinaScale;
    int                             pixelScreenScale;
    float                           xScreenContentScale, yScreenContentScale;
    int                             wScreenMM, hScreenMM;
    int                             wRes,hRes;
    float                           monitorContentScale;
    float                           pixelsxMM;
    float                           fontScaling;

    ofImage                         *mosaicLogo;
    GLuint                          mosaicLogoID;
    string                          shortcutFunc;
    bool                            createSearchedObject;
    bool                            showAboutWindow;
    bool                            showRightClickMenu;
    bool                            openPatch;
    bool                            openAutoloadPatch;
    bool                            savePatchAs;

    // ASSET Manager
    ofDirectory                     assetFolder;
    PathWatcher                     assetWatcher;
    string                          newDirName;
    string                          selectedFile;
    bool                            importAsset;
    bool                            confirmAssetDelete;
    bool                            assetWarning;
    bool                            isDeleteModalON;
    bool                            isAssetLibraryON;
    bool                            isOverAssetLibrary;
    bool                            isAddToPatchOver;
    bool                            isAssetFolderInited;

    // CODE EDITOR
    TextEditor::LanguageDefinition  bashLang;
    TextEditor::LanguageDefinition  luaLang;
    TextEditor::LanguageDefinition  glslLang;
    map<string,TextEditor>          codeEditors;
    map<string,PathWatcher*>        codeWatchers;
    vector<string>                  editedFilesPaths;
    vector<string>                  editedFilesNames;
    string                          actualEditedFilePath;
    string                          actualEditedFileName;
    string                          scriptToRemoveFromCodeEditor;
    int                             actualCodeEditor;
    bool                            isCodeEditorON;
    bool                            isOverCodeEditor;

    // LOGGER
    bool                            isInited;
    bool                            isWindowResized;
    bool                            isLoggerON;

    // DHT Mosaic Chatroom
    ofxOpenDHT                          dht;

    dht::InfoHash                       room;
    std::future<size_t>                 token;
    dht::InfoHash                       myChatid;
    std::string                         chatname;

    std::map<std::string,TextEditor>    activeChats;
    std::map<std::string,std::string>   participants;

    std::string                         userID;
    std::string                         aka;

    std::string                         participantsList;
    std::string                         chat_message;
    std::string                         welcome_message;

    bool                                initChatModal;
    bool                                isChatroomON;
    bool                                isOverChatroom;
    bool                                setFocusOnMessageInput;

    // Core visual programming
    ofxVisualProgramming            *visualProgramming;
    SynchTimer                      mosaicTiming;
    int                             mosaicFPS;
    int                             mosaicBPM;
    string                          windowTitle;
    string                          patchToLoad;
    bool                            loadNewPatch;

    // Autoload
    ofFile                          _apf;
    string                          autoloadPatchFile;
    int                             autoloadDelaySeconds;
    size_t                          autoloadStartTime;
    size_t                          waitForAutoload;
    bool                            isAutoloadedPatch;

    // NET
    int                             lastReleaseResp;
    bool                            isInternetAvailable;
    bool                            isCheckingRelease;
    string                          lastRelease;


private:
    shared_ptr<MosaicLoggerChannel>     mosaicLoggerChannel;

    string                              lastScreenshot;
    bool                                takeScreenshot;
    bool                                saveNewScreenshot;
    size_t                              waitForScreenshotTime;
    size_t                              resetScreenshotTime;

protected:


};
