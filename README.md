![Mosaic logo](https://github.com/d3cod3/Mosaic/raw/master/process/logo/logo_150.png) [MOSAIC](https://mosaic.d3cod3.org)
========

### Mosaic is an [OF](http://openframeworks.cc/) Visual Patching Developer Platform, builded with at the core the [ofxVisualProgramming](https://github.com/d3cod3/ofxVisualProgramming) addon

Table of Contents
=================

   * [OF_COMPATIBLE_RELEASE](#of_compatible_release)
   * [DEPENDENCIES](#dependencies)
   * [COMPILING](#compiling)
   * [SCREENSHOTS](#screenshots)


# OF COMPATIBLE RELEASE

#### 0.10.0
Compiled/tested with QTCreator on osx/linux/windows


# DEPENDENCIES

#### [ofxVisualProgramming](https://github.com/d3cod3/ofxVisualProgramming)

#### [ofxAudioAnalyzer](https://github.com/d3cod3/ofxAudioAnalyzer)

#### [ofxBPMDetector](https://github.com/d3cod3/ofxBPMDetector)

#### [ofxDatGui](https://github.com/d3cod3/ofxDatGui)

#### [ofxFontStash](https://github.com/armadillu/ofxFontStash)

#### [ofxGLError](https://github.com/armadillu/ofxGLError)

#### [ofxHistoryPlot](https://github.com/armadillu/ofxHistoryPlot)

#### [ofxInfiniteCanvas](https://github.com/d3cod3/ofxInfiniteCanvas)

#### [ofxLoggerChannel](https://github.com/d3cod3/ofxLoggerChannel)

#### [ofxLua](https://github.com/d3cod3/ofxLua)

#### [ofxTimeMeasurements](https://github.com/armadillu/ofxTimeMeasurements)

#### ofxXmlSettings --> Core OF Addon

Some addons are forks of the original, due to some mods, compatibility with OF0.10 and the intention of cross-platform compiling (osx,linux,win)


# COMPILING


Clone all the required addons listed:

```bash
cd <your_openframeworks_release_folder>/addons

git clone https://github.com/d3cod3/ofxAudioAnalyzer
git clone https://github.com/d3cod3/ofxBPMDetector
git clone https://github.com/d3cod3/ofxDatGui
git clone https://github.com/armadillu/ofxFontStash
git clone https://github.com/armadillu/ofxGLError
git clone https://github.com/armadillu/ofxHistoryPlot
git clone https://github.com/d3cod3/ofxInfiniteCanvas
git clone https://github.com/d3cod3/ofxLoggerChannel
git clone https://github.com/armadillu/ofxTimeMeasurements
git clone https://github.com/d3cod3/ofxVisualProgramming
```

Then, if on Linux/osx:

```bash
cd <your_openframeworks_release_folder>/addons

git clone --branch=of-0.10.0 https://github.com/d3cod3/ofxLua
```

or windows:

```bash
cd <your_openframeworks_release_folder>/addons

git clone --branch=windows https://github.com/d3cod3/ofxLua
```


# SCREENSHOTS

![Mosaic pre_alpha_0.1.0](https://github.com/d3cod3/Mosaic/blob/master/process/img/01_Mosaic_pre_alpha_0.1.0.jpg)

![Mosaic on linux](https://github.com/d3cod3/Mosaic/raw/master/process/img/03_Mosaic_linux_cinnamon_screenshot.png)

![Mosaic on windows](https://github.com/d3cod3/Mosaic/raw/master/process/img/04_Mosaic_windows_screenshot.png)
