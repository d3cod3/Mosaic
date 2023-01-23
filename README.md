![Mosaic logo](https://github.com/d3cod3/Mosaic/raw/master/process/logo/logo_150.png)

# [MOSAIC](https://mosaic.d3cod3.org) - an openFrameworks based Visual Patching Creative-Coding Platform

![Mosaic](https://github.com/d3cod3/Mosaic/raw/master/process/img/28_transparent_machines04.jpg)

[![Mosaic Forum](https://img.shields.io/badge/forum-Mosaic%20Forum-2000ff)](https://mosaicforum.cryptoriot.art/)

[![Discord Mosaic Visual Programming](https://img.shields.io/badge/discord-Mosaic%20Visual%20Programming-2000ff)](https://discord.com/invite/sPJr6EEpyG)

__

Table of Contents
=================

   * [INSTALL](#install)
   * [OF_COMPATIBLE_RELEASE](#of_compatible_release)
   * [DEPENDENCIES](#dependencies)
   * [DESCRIPTION](#description)
   * [SPECIFICATIONS](#specifications)
   * [CONTRIBUTING](#contributing)
   * [SCREENSHOTS](#screenshots)
   * [LICENSE](#license)
   * [CREDITS](#credits)


# INSTALL

## LINUX

Check the Mosaic installer here: https://github.com/d3cod3/Mosaic-Installer

## MACOS

Get Mosaic last release here: https://github.com/d3cod3/Mosaic/releases
Just unzip the downloaded release and copy Mosaic app in your Application folder, that's it!

## WINDOWS

Get Mosaic last release here: https://github.com/d3cod3/Mosaic/releases
Just unzip the downloaded release and run it!


# OF COMPATIBLE RELEASE

## 0.11.2 STABLE (official download from [OF site](https://openframeworks.cc/))
> Compiled/tested with QTCreator on osx/linux/windows
> Compiled on native VisualStudio on Windows

If you want to build Mosaic, just download OF0.11.2 for your OS (osx, linux, windows) and follow the correspondent setup guide.

# DESCRIPTION

![Mosaic-Data-Flow-Diagram](https://github.com/d3cod3/Mosaic/raw/master/process/img/10_Mosaic-Data-Flow-Diagram.jpg)

~~A very commonly used quote from Albert Einstein goes like this: « If I can't picture it, I can't understand it. »~~. A very commonly used quote from Henri Bergson goes like this: « The Eyes See Only What The Mind Is Prepared To Comprehend. » Following that thought, we'll eventually enter the realm of visual thinking, or better yet, the imagination realm, where complex ideas can be communicated in a simple way, or just the opposite.

Mosaic is a visual thinking toolkit made by artists, for artists.

[Emanuele Mazza](https://github.com/d3cod3) started the Mosaic project in 2018, in strict relation with the work of ART+TECHNOLOGY research group Laboluz from the Fine Art faculty of the Universidad Politécnica de Valéncia (Spain). From the very beginning, the source code was released on the Github development platform with a focus on making the code modular and simple to read, in order to encourage potentially interested coders in participating and collaborating on the project. Recently in 2020, digital artist [Daan de Lange](https://github.com/Daandelange) became a contributor of Mosaic code, participating in code development and restructuring.

Mosaic is a multi-platform livecoding programming/patching environment for creating real-time audio-visual compositions. It's principally designed for live needs, as can be teaching in class, live performing in an algorave, or running a generative audio-visual installation in a museum.
It aims to empower artists, creative coders, scenographers and other creative technologists in their creative workflow.
It's a FLOSS, Free/Libre and Open Source Software with multi-platform support, and it's written in C++, offering high performance.

Mosaic is shipped with an internal code editor, non-blocking system dialogs, a programmable non-linear interactive timeline, an included patch video exporter with subtitler for easy tutorial creation, lua/glsl/bash live-coding and pure data live-patching capability, a good selection of audio synthesis modules, multiple fullscreen output windows capabilities ( as many as your system can have ) with an independent warping for each window, a map-map style integrated mapping module, and an easy to use osc sending/receiving objects/nodes for network communication.

The idea behind Mosaic is to facilitate human-machine communication, to amplify imagination and to speed up the creative workflow, without sacrificing the spectrum of possibilities. To achieve this, it bundles together various creative-coding tools, acting as an interactive bridge between them.
It includes a collection of audio-visual objects that can be easily connected together using a nodal-based graphical interface, defining a custom dataflow.

Mosaic is mainly based on two frameworks : OpenFrameworks and ImGui. OpenFrameworks is an open source C++ toolkit for creative coding.
Dear ImGui is a bloat-free graphical user interface for C++ with minimal dependencies.
Together with the latter ones, Mosaic bundles comes with other 3rd party libraries such as [libpd](https://github.com/libpd/libpd) and numerous ofxAddons.
It also embeds various programming languages for live-coding purposes : Lua with OF-bindings scripting interpreter, live compiling of GLSL shaders and editing/execute Bash scripts (macOS & linux) capabilities.

Mosaic is extendable : you can easily [add custom objects](https://github.com/d3cod3/ofxMosaicPlugin).
While this involves writing and compiling code, requiring some C++ knowledge, we aim to make this process as easy as possible. Thus, Mosaic is flexible and devoted to grow over time.
For example, any Openframeworks project can be easily ported to Mosaic Objects, exposing them to the live-patching environment. This way, working with OF becomes way more modular, and you can make run-time adjustments. Possibilities are endless.
Once created, plugins can either be statically compiled into Mosaic, or if you wish, there's also support for dynamically loading them, making it easy to share and distribute your objects with others.


#### KEYWORDS
Mosaic, ofxVisualProgramming, openframeworks, linux, macOS, windows, creative-coding, live-coding, physical, visual, scripting, transmedia, programming, visual-programming

# DEPENDENCIES


#### [ofxAudioFile](https://github.com/npisanti/ofxAudioFile)

#### [ofxBTrack](https://github.com/d3cod3/ofxBTrack) -- Fork

#### [ofxChromaKeyShader](https://github.com/d3cod3/ofxChromaKeyShader) -- Fork

#### [ofxCv](https://github.com/kylemcdonald/ofxCv)

#### [ofxEasing](https://github.com/arturoc/ofxEasing)

#### [ofxFFmpegRecorder](https://github.com/d3cod3/ofxFFmpegRecorder) -- Fork

#### [ofxFft](https://github.com/kylemcdonald/ofxFft)

#### [ofxJSON](https://github.com/jeffcrouse/ofxJSON)

#### [ofxImGui](https://github.com/d3cod3/ofxImGui) -- Fork

#### [ofxInfiniteCanvas](https://github.com/d3cod3/ofxInfiniteCanvas) -- Fork

#### [ofxLua](https://github.com/danomatika/ofxLua)

#### [ofxMidi](https://github.com/danomatika/ofxMidi)

#### [ofxMtlMapping2D](https://github.com/d3cod3/ofxMtlMapping2D) -- Fork

#### [ofxNDI](https://github.com/d3cod3/ofxNDI) -- Fork

#### [ofxPd](https://github.com/danomatika/ofxPd)

#### [ofxPDSP](https://github.com/d3cod3/ofxPDSP) -- Fork

#### [ofxSyphon](https://github.com/d3cod3/ofxSyphon) -- Fork

#### [ofxTimeline](https://github.com/d3cod3/ofxTimeline) -- Fork

#### [ofxVisualProgramming](https://github.com/d3cod3/ofxVisualProgramming)

#### [ofxWarp](https://github.com/d3cod3/ofxWarp) -- Fork

Some addons are forks of the original, due to some mods, compatibility with OF0.11 and the intention of cross-platform compiling (osx,linux,win)


# SPECIFICATIONS

  - [FLOSS](https://www.gnu.org/philosophy/floss-and-foss.en.html), Free/Libre and Open Source Software
  - cross-platform (Linux, macOS, Windows)
  - plugin injection capable, see [ofxMosaicPlugin](https://github.com/d3cod3/ofxMosaicPlugin)
  - multi-threaded
  - ImGui based GUI interface
  - included automatic window video exporter with subtitler for easy tutorial creation
  - non-blocking system dialogs
  - internal code editor
  - lua/glsl/bash live-coding
  - pure data live-patching
  - non-linear interactive timeline
  - good selection of audio synthesis modules
  - warping integrated on output window object
  - mapmap style projection mapping module


# OFXADDONS

Clone all the required addons listed:

```bash
cd <your_openframeworks_release_folder>/addons

git clone https://github.com/npisanti/ofxAudioFile
git clone https://github.com/d3cod3/ofxBTrack
git clone https://github.com/d3cod3/ofxChromaKeyShader
git clone https://github.com/kylemcdonald/ofxCv
git clone https://github.com/arturoc/ofxEasing
git clone https://github.com/d3cod3/ofxFFmpegRecorder
git clone https://github.com/kylemcdonald/ofxFft
git clone https://github.com/jeffcrouse/ofxJSON
git clone https://github.com/d3cod3/ofxImGui
git clone https://github.com/d3cod3/ofxInfiniteCanvas
git clone https://github.com/danomatika/ofxLua
git clone https://github.com/danomatika/ofxMidi
git clone https://github.com/d3cod3/ofxMtlMapping2D
git clone https://github.com/d3cod3/ofxNDI
git clone https://github.com/danomatika/ofxPd
git clone https://github.com/d3cod3/ofxPDSP
git clone https://github.com/d3cod3/ofxSyphon
git clone https://github.com/d3cod3/ofxTimeline
git clone https://github.com/d3cod3/ofxVisualProgramming
git clone https://github.com/d3cod3/ofxWarp

```

Some addons use specific branches and remotes (usually in order to provide easy multiplatform support). Specially if you have already worked with OpenFrameworks, your current addons folder might be incompatible with Mosaic. To verify compatibility, it can be useful to `cd path/to/mosaic && cd scripts/ofxAddonTool && ./ofxAddonTool.sh` to get an oversight of ofxAddons compatibility.

Then clone Mosaic project as an openFrameworks example:

```bash
cd <your_openframeworks_release_folder>/apps/myApps

git clone --recursive https://github.com/d3cod3/Mosaic
```

Now you're ready to compile Mosaic! Load the .qbs project in QTCreator and compile it. Or just enter in Mosaic folder and run a make Release.

# CONTRIBUTING

Contributing to the project adding new objects is relatively easy, as ofxVisualProgramming is at the core of [Mosaic](https://github.com/d3cod3/Mosaic) software, it has been implemented a plugin mechanism based on [Pugg](http://pugg.sourceforge.net/), in order to facilitate the extension and the creation of new objects/nodes to add at the ofxVisualProgramming/Mosaic default objects/nodes library. (see objects/nodes list below)

You can find the repo of the plugin template here: [ofxMosaicPlugin](https://github.com/d3cod3/ofxMosaicPlugin), with some generic objects templates and more detailed info in the readme.

If you're curious, please try out Mosaic and don't hesitate to get in touch.
Mosaic is open to anybody, contributions of any kind are welcome.

# SCREENSHOTS

![Mosaic 0.6.4_beta](https://github.com/d3cod3/Mosaic/raw/master/process/img/30_mosaicWireless.jpg)

![Mosaic 0.4.3_beta](https://github.com/d3cod3/Mosaic/raw/master/process/img/29_1979.jpg)

![Mosaic 0.4.0_beta](https://github.com/d3cod3/Mosaic/raw/master/process/img/25_transparent_machines.jpg)

![Mosaic pre_0.2.0](https://github.com/d3cod3/Mosaic/raw/master/process/img/23_helloSonogram.jpg)

![Mosaic pre_0.2.0](https://github.com/d3cod3/Mosaic/raw/master/process/img/22_Ry_ofLoffler.jpg)

![Mosaic 0.1.7](https://github.com/d3cod3/Mosaic/raw/master/process/img/21_mappingBebop.jpg)

![Mosaic 0.1.7](https://github.com/d3cod3/Mosaic/raw/master/process/img/20_jupiterBlues.jpg)

![Mosaic pre_0.1.7](https://github.com/d3cod3/Mosaic/raw/master/process/img/19_rememberPD.jpg)

![Mosaic pre_0.1.6](https://github.com/d3cod3/Mosaic/raw/master/process/img/18_pre0.1.6.jpg)

![Mosaic pre_alpha_0.1.0](https://github.com/d3cod3/Mosaic/raw/master/process/img/09_we_are_near_alpha_station.png)

![Mosaic pre_alpha_0.1.0](https://github.com/d3cod3/Mosaic/raw/master/process/img/08_life_is_full_of_possibilities.png)

![Mosaic on linux](https://github.com/d3cod3/Mosaic/raw/master/process/img/03_Mosaic_linux_cinnamon_screenshot.png)

![Mosaic on windows](https://github.com/d3cod3/Mosaic/raw/master/process/img/04_Mosaic_windows_screenshot.png)

# LICENSE

[![license](https://img.shields.io/github/license/mashape/apistatus.svg)](LICENSE)

All contributions are made under the [MIT License](https://opensource.org/licenses/MIT). See [LICENSE](https://github.com/d3cod3/Mosaic/blob/master/LICENSE.md).

# CREDITS

Mosaic is a [FLOSS](https://www.gnu.org/philosophy/floss-and-foss.en.html), Free/Libre and Open Source Software.

Mosaic is almost completely based on [ofxVisualProgramming](https://github.com/d3cod3/ofxVisualProgramming) ofxaddon, if you like this software and are giving it a star, please consider giving another one at [ofxVisualProgramming](https://github.com/d3cod3/ofxVisualProgramming) repo.

The Mosaic team is composed by [Emanuele Mazza](https://github.com/d3cod3) [<img src="https://avatars0.githubusercontent.com/u/141075?v=4" height=50 width=50>](https://github.com/d3cod3), [Daan de Lange](https://github.com/Daandelange) [<img src="https://avatars0.githubusercontent.com/u/1329784?v=4" height=50 width=50>](https://github.com/Daandelange) and Maria José Martínez de Pisón.

Mosaic uses [ImGui](https://github.com/ocornut/imgui), [kiss_fft](https://github.com/mborgerding/kissfft), [libsamplerate](https://github.com/erikd/libsamplerate), [dr_libs](https://github.com/mackron/dr_libs), [hap](https://github.com/Vidvox/hap), [snappy](https://github.com/google/snappy), [ffmpeg](https://github.com/FFmpeg/FFmpeg)  and code from openframeworks and all the included ofxAddons.
