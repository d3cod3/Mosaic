# Mosaic CHANGELOG

### 0.7.0

- **gui** : Drag and drop objects to subpatch on subpatches list to move them
- **gui** : Save canvas displacement position in patch, to always restore last view
- **gui** : Modified actual logger for passing commands, add selectable text and copy/paste
- **addition** : Added multi-slider object with variable number of sliders and multi toggle object with variable number of toggles
- **update** : Modified number object, include internal trigger to on/off data flow ( from internal menu )
- **update** : Modified number and slider object, to set and save variable name, for usability
- **examples** : Added some new visual programming patches examples



### 0.6.9

- **OS** : develop discontinued on windows, last available release 0.6.6
- **update** : Updated core to OF 0.12.0
- **feature** : added internal DHT distributed chatroom, based on [OpenDHT](https://github.com/savoirfairelinux/opendht)
- **feature** : Add main monitor information section in "About Mosaic"
- **feature** : Added sub-patch system
- **update** : Added canvas reset button in menu ( system -> reset canvas )
- **update** : Added some lua random/noise examples
- **update** : Updated to imgui 1.91
- **update** : Updated NDI to libndi5 and enhanced video sender/video release ndi based objects (macOS only)
- **enhancement** : Automatic GUI font size and GUI scale from main monitor data for retina screens
- **code cleaning** : Serious code cleanup
- **bug fixing** : Various fixes

### 0.6.5

- **update** : removed Mosaic window video exporter due to cross-compatibility issues
- **bug fixing** : fixed video exporter object
- **update** : switched from ofxHapPlayer to native OF video player due to some incompatibility issues with of0.11.2
- **update** : added keyboard shortcut for most used objects
- **bug fixing** : Fixed runtime errors when access on empty vectors
- **code cleaning** : Lots of warning removal

### 0.6.4

- **enhancement** : added sender and receiver objects, wireless data transport implemented
- **bug fixing** : Various fixes

### 0.6.3

- **update** : Now same identical basecode and functionalities on all supported OSs (various Linux distros, macOS starting from 10.11 and Windows starting from W10)
- **update** : updated libs for cross-compile
- **update** : disable object creation via keyboard from floating menu for better usability
- **enhancement** : audio devices managing and setting refactored, removed lots of runtime crash situations
- **update** : Now minimum macOS required is 10.11 ( El Capitan )
- **update** : removed ofxPDExternal addon for cross-compile compatibility
- **bug fixing** : Various windows fixes
- **update** : switched ofxAudioAnalyzer for ofxFft due to windows native compiling issues with essentia lib (removed)
- **feature** : added terminal instructions for fixing camera and microphone permissions on osx
- **update** : switched to original maintained ofxLua addon by @danomatika
- **feature** : Add GPU information section in "About Mosaic" from @Daandelange
- **bug fixing** : internal code editor cleaned up and lots of fixes
- **bug fixing** : Various fixes for Monterrey and later macOS
- **update** : Updated core to OF 0.11.2

### 0.5.1

- **cleanup** Removed ofxGLEditor addon and lua scripting onscreen live-coding, due to fontstash incompatibility with opengl4

### 0.5.0

- **addition** : added texture mixer object to mix up to 32 texture using alpha
- **update** : Updated ofxAddonsTool to last commit
- **addition** : Added ofxHapPlayer addon ( forked with some minor tweaks ) for using now in Mosaic the HAP codec as the standard for the video player object
- **addition** : Added ofxSyphon addon ( retro compatibility fork ) and syphon sender + syphon receiver objects ( osx only, obviously )
- **bug fixing** : Various imgui node editor gui fixings from @Daandelange

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
