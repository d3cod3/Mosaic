![Mosaic logo](https://github.com/d3cod3/Mosaic/raw/master/process/logo/logo_150.png)

# [MOSAIC](https://mosaic.d3cod3.org) - an openFrameworks based Visual Patching Creative-Coding Platform

Operating system | Status
---------------- | ----------
Ubuntu and macOS | [![TravisCI](https://travis-ci.org/d3cod3/ofxVisualProgramming.svg?branch=master)](https://travis-ci.org/d3cod3/ofxVisualProgramming)
Windows          | [![AppVeyor](https://ci.appveyor.com/api/projects/status/65sk40q6y8bqfunw/branch/master?svg=true)](https://ci.appveyor.com/project/d3cod3/ofxvisualprogramming/branch/master)

Table of Contents
=================

   * [DOWNLOAD](#download)
   * [OF_COMPATIBLE_RELEASE](#of_compatible_release)
   * [DEPENDENCIES](#dependencies)
   * [DESCRIPTION](#description)
   * [COMPILING](#compiling)
   * [SCREENSHOTS](#screenshots)
   * [LICENSE](#license)


# DOWNLOAD

Get Mosaic last release here: https://github.com/d3cod3/Mosaic/releases

# OF COMPATIBLE RELEASE

## 0.10.0 STABLE (official download from [OF site](https://openframeworks.cc/))
> Compiled/tested with QTCreator on osx/linux/windows

If you want to build Mosaic, just download OF0.10.0 for your OS (osx, linux, windows) and follow the setup guide for [qtcreator](https://www.qt.io/) IDE.

# DESCRIPTION

![Mosaic-Data-Flow-Diagram](https://github.com/d3cod3/Mosaic/raw/master/process/img/10_Mosaic-Data-Flow-Diagram.jpg)

Mosaic is an open source multi-platform (osx, linux, windows) live coding and visual programming application, based on openFrameworks.

This project deals with the idea of integrate/amplify man-machine communication, offering a real-time flowchart based visual interface for high level creative coding. As live-coding scripting languages offer a high level coding environment, ofxVisualProgramming and the Mosaic Project as his parent layer container, aim at a high level visual-programming environment, with embedded multi scripting languages availability (Lua, GLSL, Python and BASH(macOS & linux) ).

As this project is based on openFrameworks, one of the goals is to offer as more objects as possible, using the pre-defined OF classes for trans-media manipulation (audio, text, image, video, electronics, computer vision), plus all the gigantic ofxaddons ecosystem actually available (machine learning, protocols, web, hardware interface, among a lot more).

While the described characteristics could potentially offer an extremely high complex result (OF and OFXADDONS ecosystem is really huge, and the possibility of multiple scripting languages could lead every unexperienced user to confusion), the idea behind the interface design aim at avoiding the "high complex" situation, embodying a direct and natural drag&drop connect/disconnet interface (mouse/trackpad) on the most basic level of interaction, adding text editing (keyboard) on a intermediate level of interaction (script editing), following most advanced level of interaction for experienced users (external devices communication, automated interaction, etc...)


#### KEYWORDS
Mosaic, ofxVisualProgramming, openframeworks, linux, macOS, windows, creative-coding, live-coding, physical, visual, scripting, transmedia, programming, visual-programming

# DEPENDENCIES

#### [ofxAudioAnalyzer](https://github.com/d3cod3/ofxAudioAnalyzer) -- Fork

#### [ofxAudioFile](https://github.com/npisanti/ofxAudioFile)

#### [ofxBTrack](https://github.com/d3cod3/ofxBTrack) -- Fork

#### [ofxChromaKeyShader](https://github.com/d3cod3/ofxChromaKeyShader) -- Fork

#### [ofxCv](https://github.com/kylemcdonald/ofxCv)

#### [ofxDatGui](https://github.com/d3cod3/ofxDatGui) -- Fork

#### [ofxFontStash](https://github.com/d3cod3/ofxFontStash) -- Fork

#### [ofxGLError](https://github.com/d3cod3/ofxGLEditor) -- Fork

#### [ofxGLError](https://github.com/armadillu/ofxGLError)

#### [ofxHistoryPlot](https://github.com/armadillu/ofxHistoryPlot)

#### [ofxInfiniteCanvas](https://github.com/d3cod3/ofxInfiniteCanvas) -- Fork

#### [ofxLoggerChannel](https://github.com/d3cod3/ofxLoggerChannel) -- Fork

#### [ofxLua](https://github.com/d3cod3/ofxLua) -- Fork

#### [ofxMidi](https://github.com/d3cod3/ofxMidi) -- Fork

#### [ofxModal](https://github.com/braitsch/ofxModal)

#### [ofxParagraph](https://github.com/d3cod3/ofxParagraph) -- Fork

#### [ofxPDSP](https://github.com/npisanti/ofxPDSP)

#### [ofxPython](https://github.com/d3cod3/ofxPython) -- Fork

#### [ofxSIMDFloats](https://github.com/npisanti/ofxSIMDFloats)

#### [ofxSimpleHttp](https://github.com/armadillu/ofxSimpleHttp)

#### [ofxTimeMeasurements](https://github.com/armadillu/ofxTimeMeasurements)

#### [ofxVisualProgramming](https://github.com/d3cod3/ofxVisualProgramming)

Some addons are forks of the original, due to some mods, compatibility with OF0.10 and the intention of cross-platform compiling (osx,linux,win)


# COMPILING

**MACOS/LINUX/WINDOWS Compiling with qtcreator4.6.1**

Clone all the required addons listed:

```bash
cd <your_openframeworks_release_folder>/addons

git clone https://github.com/d3cod3/ofxAudioAnalyzer
git clone https://github.com/npisanti/ofxAudioFile
git clone https://github.com/d3cod3/ofxBTrack
git clone https://github.com/d3cod3/ofxChromaKeyShader
git clone https://github.com/kylemcdonald/ofxCv
git clone https://github.com/d3cod3/ofxDatGui
git clone https://github.com/d3cod3/ofxFontStash
git clone https://github.com/d3cod3/ofxGLEditor
git clone https://github.com/armadillu/ofxGLError
git clone https://github.com/armadillu/ofxHistoryPlot
git clone https://github.com/d3cod3/ofxInfiniteCanvas
git clone https://github.com/d3cod3/ofxLoggerChannel
git clone --branch=of-0.10.0 https://github.com/d3cod3/ofxLua
git clone https://github.com/d3cod3/ofxMidi
git clone https://github.com/braitsch/ofxModal
git clone --branch=OF0.9.8 https://github.com/d3cod3/ofxPython
git clone https://github.com/d3cod3/ofxParagraph
git clone https://github.com/npisanti/ofxPDSP
git clone https://github.com/npisanti/ofxSIMDFloats
git clone https://github.com/armadillu/ofxSimpleHttp
git clone https://github.com/armadillu/ofxTimeMeasurements
git clone https://github.com/d3cod3/ofxVisualProgramming

```

# SCREENSHOTS

![Mosaic pre_alpha_0.1.0](https://github.com/d3cod3/Mosaic/raw/master/process/img/09_we_are_near_alpha_station.png)

![Mosaic pre_alpha_0.1.0](https://github.com/d3cod3/Mosaic/raw/master/process/img/08_life_is_full_of_possibilities.png)

![Mosaic on linux](https://github.com/d3cod3/Mosaic/raw/master/process/img/03_Mosaic_linux_cinnamon_screenshot.png)

![Mosaic on windows](https://github.com/d3cod3/Mosaic/raw/master/process/img/04_Mosaic_windows_screenshot.png)

# LICENSE

[![license](https://img.shields.io/github/license/mashape/apistatus.svg)](LICENSE)

All contributions are made under the [MIT License](https://opensource.org/licenses/MIT). See [LICENSE](https://github.com/d3cod3/Mosaic/blob/master/LICENSE.md).
