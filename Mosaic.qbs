import qbs
import qbs.Process
import qbs.File
import qbs.FileInfo
import qbs.TextFile
import "../../../libs/openFrameworksCompiled/project/qtcreator/ofApp.qbs" as ofApp

Project{
    property string of_root: '../../..'

    ofApp {
        name: { return FileInfo.baseName(sourceDirectory) }
        cpp.minimumMacosVersion: '10.15'
        cpp.cxxLanguageVersion: 'c++17'

        files: [
            "profiler/tracy/TracyClient.cpp",
            "src/MosaicTheme.cpp",
            "src/MosaicTheme.h",
            "src/SplashScreen.cpp",
            "src/SplashScreen.h",
            "src/TextEditor.cpp",
            "src/TextEditor.h",
            "src/SynchTimer.h",
            "src/config.h",
            "src/includes.h",
            'src/main.cpp',
            'src/ofApp.cpp',
            'src/ofApp.h',
        ]

        of.addons: [
            'ofxInfiniteCanvas','ofxVisualProgramming'
        ]

        // additional flags for the project. the of module sets some
        // flags by default to add the core libraries, search paths...
        // this flags can be augmented through the following properties:
        of.pkgConfigs: {
            var configs = [];
            if(qbs.hostOS.contains("osx") || qbs.targetOS.contains("macos")){
                configs = configs.concat([]);
            }else if(qbs.hostOS.contains("windows")){
                configs = configs.concat([]);
            }else if(qbs.hostOS.contains("linux")){
                configs = configs.concat(["/usr/local/lib/pkgconfig/opendht.pc"]);
            }

            return configs;
        }

        of.includePaths: {
            var paths = ['profiler/tracy'];
            if(qbs.hostOS.contains("osx") || qbs.targetOS.contains("macos")){
                paths = paths.concat([of_root+'/addons/ofxFft/src']);
            }else if(qbs.hostOS.contains("windows")){
                paths = paths.concat([]);
            }else if(qbs.hostOS.contains("linux")){
                paths = paths.concat([]);
            }
            return paths;
        }
        of.cFlags: []           // flags passed to the c compiler


        // flags passed to the c++ compiler
        of.cxxFlags: {
            var flags = []; // Enter global flags here
            if(qbs.configurationName.contains('Debug')){
                flags = flags.concat(['-g']);
            }else if(qbs.configurationName.contains('Release')){
                flags = flags.concat(['-O2']);
            }else if(qbs.configurationName.contains('Profiling')){
                flags = flags.concat(['-g', '-O2']); // Optimize to have release performance, but with exporting symbols for the profiler.
            }

            return flags;
        }

        // flags passed to the linker
        of.linkerFlags: {
            var lFlags = [];
            if(qbs.hostOS.contains("osx") || qbs.targetOS.contains("macos")){
                lFlags = lFlags.concat([
                                           '-L'+of_root+'/addons/ofxFFt/libs/fftw/lib',  // for ofxFft
                                       ]);
            }else if(qbs.hostOS.contains("windows")){
                lFlags = lFlags.concat([]);
            }else if(qbs.hostOS.contains("linux")){
                lFlags = lFlags.concat([]);
            }
            return lFlags;
        }

        // defines are passed as -D to the compiler, and can be checked with #ifdef or #if in the code
        of.defines: {
            var defs = []; // Enter global flags here
            // defs = defs.concat(['OFXIMGUI_DEBUG']);  // Uncomment to debug ofxImGui
            defs = defs.concat([]);
            if(qbs.configurationName.contains('Debug')){
                defs = defs.concat(['MOSAIC_DEBUG','OFXVP_DEBUG']);
            }else if(qbs.configurationName.contains('Release')){
                defs = defs.concat([]);
            }else if(qbs.configurationName.contains('Profiling')){
                defs = defs.concat(['TRACY_ENABLE','TRACY_ONLY_IPV4','MOSAIC_ENABLE_PROFILING']);
            }
            return defs;
        }

        // osx only, additional frameworks to link with the project
        of.frameworks: []

        // static libraries
        of.staticLibraries: {
            var libs = [];
            if(qbs.hostOS.contains("osx") || qbs.targetOS.contains("macos")){
                libs = libs.concat([]);
            }else if(qbs.hostOS.contains("windows")){
                libs = libs.concat([]);
            }else if(qbs.hostOS.contains("linux")){
                libs = libs.concat([]);
            }

            return libs;
        }

        // dynamic libraries
        of.dynamicLibraries: {
            var libs = [];
            if(qbs.hostOS.contains("osx") || qbs.targetOS.contains("macos")){
                libs = libs.concat([]);
            }else if(qbs.hostOS.contains("windows")){
                libs = libs.concat(['openal','mpg123','libsndfile','pd']);
            }else if(qbs.hostOS.contains("linux")){
                libs = libs.concat([]);
            }

            return libs;
        }

        // other flags can be set through the cpp module: http://doc.qt.io/qbs/cpp-module.html
        // eg: this will enable ccache when compiling
        //
        // cpp.compilerWrapper: 'ccache'

        // add CoreMIDI for osx before big sur
        Properties {
            condition: qbs.hostOS.contains("10.15")
            of.frameworks: outer.concat(['/System/Library/Frameworks/CoreMIDI.framework']);
        }

        // Include ofxSyphon on osx
        Properties {
            // osx only, additional frameworks to link with the project
            condition: qbs.targetOS.contains("osx") || qbs.targetOS.contains("macos")
            of.addons: outer.concat(['ofxSyphon'])
            of.frameworks: outer.concat(['Syphon'])
            cpp.frameworkPaths: [of_root+'/addons/ofxSyphon/libs/Syphon/lib/osx/']
            // dirty fix for compiling .mm files (not auto-detected on qt)
            files: outer.concat([
                                    of_root + '/addons/ofxSyphon/src/ofxSyphonClient.mm',
                                    of_root + '/addons/ofxSyphon/src/ofxSyphonServer.mm',
                                    of_root + '/addons/ofxSyphon/src/ofxSyphonServerDirectory.mm',
                                    of_root + '/addons/ofxSyphon/libs/Syphon/src/SyphonNameboundClient.m',
                                ])
        }

        // OSX + openDHT support
        Properties {
            condition: qbs.targetOS.contains("osx") || qbs.targetOS.contains("macos")
            of.dynamicLibraries: outer.concat(['opendht'])
            cpp.systemIncludePaths: outer.concat(['/usr/local/include/'])
        }

        Depends{
            name: "cpp"
        }

        // common rules that parse the include search paths, core libraries...
        Depends{
            name: "of"
        }

        // dependency with the OF library
        Depends{
            name: "openFrameworks"
        }
    }

    property bool makeOF: true  // use makfiles to compile the OF library
    // will compile OF only once for all your projects
    // otherwise compiled per project with qbs


    property bool precompileOfMain: false  // precompile ofMain.h
    // faster to recompile when including ofMain.h
    // but might use a lot of space per project

    references: [FileInfo.joinPaths(of_root, "/libs/openFrameworksCompiled/project/qtcreator/openFrameworks.qbs")]
}
