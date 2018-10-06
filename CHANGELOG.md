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
  ___   _  _  _   
 / _ \ / || || |  
| | | || || || |_ 
| |_| || ||__   _|
 \___(_)_(_) |_|  
                                 
```

# v0.1.4

### general
    + Added DSP ON/OFF control
    / Fixed audio input/output devices lists
    + Added GUI objects collision detection, better user interaction interface
    + Added check for updates & automatic download
    + Added [ofxModal](https://github.com/braitsch/ofxModal)
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
