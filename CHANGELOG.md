# Mosaic CHANGELOG

### 0.4.9
- **bug fixing** : fixed file delete error form patch data folder when loading new patch
- **bug fixing** : _osc sender_ throw out of range on reloading patch [68bc8a42](https://github.com/d3cod3/ofxVisualProgramming/commit/68bc8a42602374ee4fe8325b39a08493bc4550e2)
- **feature** : added rescan devices button to MIDI send/receive objects [dae4f6d](https://github.com/d3cod3/ofxVisualProgramming/commit/dae4f6de2eca90ed1f06fa8efbee4c684ce445be)
- **enhancement** : added [tracy profiler](https://github.com/wolfpld/tracy) for solid debug and profiling, as submodule
- **serialization** : added app release reference in patch files

### 0.4.8
- better retina screen detection
- upgraded openGL to 4.1
- glsl shaders languages availables from 150 to 410
- included example shaders updated
- updated ofxAddonsTool to last commit
- removed ofxFontStash dependency
- fixed flatpak sandbox issue
- switched subtitler to text paragraph


### 0.4.7
- small fixes

### 0.4.6
- added windows docking
- fixed/enhanced internal text editor
- added text editor find&replace
- added GUI asset manager
- optimized patch/resources interaction saving mechanism
- updated ofxAddonTool
- bug fixes

### 0.4.4
- fixed main window recording on external monitors
- added fullscreen shortcut for main window
- added ofxAddonTool as submodule
- added patch autoload-on-startup mechanism
- updated python to 3.8 on linux
- fixed compile on windows
- cleaned audio process code
- bug fixes
- code cleaning

### 0.4.3
- Added patch autoload-on-startup mechanism
- Properly adjusted clear timings and global std::map objects reference on reloading patches
- General graphic fixes
- Removed unused files

### 0.4.2
- Added an utility for ofxAddon compatibility verifications.
- Added string category with a bunch of basic string manipulation objects
- Added multiple objects selection and delete/duplicate over selected objects
- Optimized code for high performance rendering
- Updated examples
- Various bugs fixes

### 0.4.1

- Changed "bash script" object to non-blocking with ofThread
- Various bugs fixes
