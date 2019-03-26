```bash
        _   _         _            _            _                    _           _      
       /\_\/\_\ _    /\ \         / /\         / /\                 /\ \       /\ \     
      / / / / //\_\ /  \ \       / /  \       / /  \                \ \ \     /  \ \    
     /\ \/ \ \/ / // /\ \ \     / / /\ \__   / / /\ \               /\ \_\   / /\ \ \   
    /  \____\__/ // / /\ \ \   / / /\ \___\ / / /\ \ \             / /\/_/  / / /\ \ \  
   / /\/________// / /  \ \_\  \ \ \ \/___// / /  \ \ \           / / /    / / /  \ \_\
  / / /\/_// / // / /   / / /   \ \ \     / / /___/ /\ \         / / /    / / /    \/_/
 / / /    / / // / /   / / /_    \ \ \   / / /_____/ /\ \       / / /    / / /          
/ / /    / / // / /___/ / //_/ __/ / /  / /_________/\ \ \  ___/ / /__  / / /________   
\/_/    / / // / /____\/ / \ \/___/ /  / / /_       __\  _\/ __\/_/___\/ / /_________\  
        \/_/ \/_________/    _____\/    _ ___\     /____/_/\/_________/\/____________/  

```

```bash
  ___   _   ___  
 / _ \ / | ( _ )
| | | || | / _ \
| |_| || || (_) |
 \___(_)_(_)___/

```

# v0.1.8

### general
    / Various retina fixes
    / General bug fixes
    + Added first bunch of sound objects using ofxPDSP engine
    / Fixed Windows release dlls
    + Added Linux Ubuntu/Debian automatic install/update scripts

//////////////////////////////////

# v0.1.7

### general
    + Added splashscreen
    + Integrated threaded non-blocking system dialogs (notifications, load/save file, messages)
    + Added "pd patch" object, live pd patching integrated inside Mosaic
    + Added some logic objects: inverter, select, spigot, gate, ==, !=, >, <
    / Switched menus from ofxDatGui to ofxImGui

### ofxaddons
    + Added ofxThreadedFileDialog <https://github.com/d3cod3/ofxThreadedFileDialog>
    + Added ofxJSON <https://github.com/jeffcrouse/ofxJSON>
    + Added ofxImGui <https://github.com/jvcleave/ofxImGui>
    + Added ofxThreadedYouTubeVideo <https://github.com/pierrep/ofxThreadedYouTubeVideo>
    + Added a forked version of ofxWarp <https://github.com/d3cod3/ofxWarp>

//////////////////////////////////

# v0.1.6

### general
    + Added timeline object from a modded version of ofxTimeline
    + Added Live Patching Mode (render over patch with transparency) through live patching object
    + Added framerate control selector
    + Added logger hide/show button
    + Added "take patch screenshot" button for easy patch documentation

### ofxaddons
    + added a forked version of ofxTimeline <https://github.com/d3cod3/ofxTimeline>
    + added ofxPd <https://github.com/danomatika/ofxPd>

//////////////////////////////////

# v0.1.5

### general
    + Added all computer vision objects
    + Added Mosaic examples folder
    + Added haarcascades files from opencv source
    / Simplified .qbs project file
    / Fixed some issues/bugs
    / Better objects user interface

//////////////////////////////////

# v0.1.4

### general
    / Fixed sound streaming/sample rate issues
    + Added all audio analysis objects
    / Better general objects logic
    + Added DSP ON/OFF control
    / Fixed audio input/output devices lists
    + Added GUI objects collision detection, better mouse control, better user interaction interface
    + Added check for updates & automatic download

### ofxaddons
    + Added a forked version of [ofxModal](https://github.com/d3cod3/ofxModal)
    + Added [ofxSimpleHttp](https://github.com/armadillu/ofxSimpleHttp)

//////////////////////////////////

# v0.1.3

### general
    / Fixed macOS Sierra & High Sierra Gatekeeper Path Randomization Anti-Malware Feature Issue

//////////////////////////////////

# v0.1.2

### general
    + added a forked version of ofxGLEditor <https://github.com/d3cod3/ofxGLEditor>
    + added live-coding (ofxGLEditor) in lua script and python script objects
    / Fixed bugs in lua script and python script objects
    + added luafilesystem (https://keplerproject.github.io/luafilesystem/) library to lua embedded scripting interpreter

//////////////////////////////////

# v0.1.1

### general
    + retina fixes
    + added NEW button to scripting objects
    / general code cleaning

//////////////////////////////////

# v0.1.0

### general
    / builded with OF 0.10.0, QT Creator 4.6.1
    / multi-platform osx/win/linux
    + added MIT License
    + added process/ folder for documentation

### core
    / the core code of Mosaic is the ofxVisualProgramming addon

### opengl
    / using opengl 2.1

### gui
    / using a forked ofxDatGui working with ofxFontStash <https://github.com/d3cod3/ofxDatGui>
    + added Audio Analyzer Panel for audio analyzer object

### ofxaddons
    + added a forked version of ofxAudioAnalyzer <https://github.com/d3cod3/ofxAudioAnalyzer>
    + added ofxAudioFile
    + added a forked version of ofxBTrack <https://github.com/d3cod3/ofxBTrack>
    + added a forked version of ofxChromaKeyShader <https://github.com/d3cod3/ofxChromaKeyShader>
    + added ofxCv
    + added a forked version of ofxDatGui <https://github.com/d3cod3/ofxDatGui>
    + added ofxFontStash
    + added ofxGLError
    + added ofxHistoryPlot
    + added a forked version ofofxInfiniteCanvas <https://github.com/d3cod3/ofxInfiniteCanvas>
    + added a forked version of ofxLoggerChannel <https://github.com/d3cod3/ofxLoggerChannel>
    + added a forked version of ofxLua with OF 0.10.0 bindings
    <https://github.com/d3cod3/ofxLua>
    + added a forked version of ofxMidi
    <https://github.com/d3cod3/ofxMidi>
    + added a forked version of ofxParagraph
    <https://github.com/d3cod3/ofxParagraph>
    + added ofxPDSP
    + added a forked version of ofxPython with OF 0.10.0 bindings
    <https://github.com/d3cod3/ofxPython>
    + added ofxSIMDFloats
    + added ofxTimeMeasurements
    + added ofxVisualProgramming <https://github.com/d3cod3/ofxVisualProgramming>

### libs
    + fftw3 static lib, included with ofxAudioAnalyzer
    + essentia 2.1-beta3 source code (for multi-platform compat.), included with ofxAudioAnalyzer
    + kiff_fft, libsamplerate, included with ofxBTrack
    + dr_wav, dr_mp3, dr_flac, stb_vorbis, included in ofxAudioFile
    + AudioFFT wrapper is used in ofxPDSP, Copyright (c) 2013 HiFi-LoFi.


### examples


PLATFORM SPECIFIC
-----------------

### linux
    / QTCreator project only

### macos
    / QTCreator project only
    / Based on Qt 5.10.1 (Clang 8.0 (Apple), 64 bit)

### win
    / QTCreator project only
