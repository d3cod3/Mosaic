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

#include "ofMain.h"

#include "ofApp.h"
#include "SplashScreen.h"

#include "ofAppGLFWWindow.h"

#include "config.h"

#ifdef MOSAIC_ENABLE_PROFILING
#include "Tracy.hpp"
#include <memory>

// Overload global new and delete for memory inspection
void* operator new(std::size_t n)
{
    void* ptr = malloc(n);
    TracyAlloc(ptr, n);
    return ptr;
}
void operator delete(void* ptr) noexcept
{
    TracyFree(ptr);
    free(ptr);
}
#endif

//========================================================================
int main(int argc, char *argv[]){

    #ifdef MOSAIC_ENABLE_PROFILING
    ZoneScopedN("main()");
    #endif

    vector<string> options;
    if(argc > 1){
        for(int i = 0; i < argc; i++){
            options.push_back(argv[i]);
        }
    }

    float splashWinW = 428;
    float splashWinH = 280;

    ofGLFWWindowSettings settings;
#if defined(OFXVP_GL_VERSION_MAJOR) && defined(OFXVP_GL_VERSION_MINOR)
    settings.setGLVersion(OFXVP_GL_VERSION_MAJOR,OFXVP_GL_VERSION_MINOR);
#else
    settings.setGLVersion(3,2);
#endif

    settings.stencilBits = 0;
    settings.setSize(WINDOW_START_WIDTH, WINDOW_START_HEIGHT);
#ifdef TARGET_LINUX
    settings.setPosition(ofVec2f(0,0));
#elif defined(TARGET_OSX)
    settings.setPosition(ofVec2f(0,0));
#elif defined(TARGET_WIN32)
    settings.setPosition(ofVec2f(6,30));
#endif
    settings.resizable = true;
    settings.decorated = true;

    // Mosaic main visual-programming window
    shared_ptr<ofAppGLFWWindow> mosaicWindow = dynamic_pointer_cast<ofAppGLFWWindow>(ofCreateWindow(settings));
    #ifdef TARGET_LINUX
    mosaicWindow->setWindowIcon("images/logo_128.png");
    #endif
    shared_ptr<ofApp> mosaicApp(new ofApp);

    // Splash Screen Window
    ofGLFWWindowSettings splashSettings;
    splashSettings.setSize(splashWinW,splashWinH);
    splashSettings.setPosition(ofVec2f(ofGetScreenWidth()/2 - splashWinW/2,ofGetScreenHeight()/2 - splashWinH/2));
    splashSettings.resizable = false;
    splashSettings.decorated = false;

    shared_ptr<ofAppGLFWWindow> splashWindow = dynamic_pointer_cast<ofAppGLFWWindow>(ofCreateWindow(splashSettings));
    #ifdef TARGET_LINUX
    mosaicWindow->setWindowIcon("images/logo_128.png");
    #endif
    shared_ptr<SplashScreen> splashApp(new SplashScreen);
    splashApp->splashWindow = splashWindow;

    mosaicApp->arguments = options;

    ofRunApp(mosaicWindow, mosaicApp);
    ofRunApp(splashWindow, splashApp);
    ofRunMainLoop();

    // done
    return EXIT_SUCCESS;

}
