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
            'ofxVisualProgramming',
        ]

        // additional flags for the project. the of module sets some
        // flags by default to add the core libraries, search paths...
        // this flags can be augmented through the following properties:
        of.pkgConfigs: []       // list of additional system pkgs to include
        of.includePaths: ['profiler/tracy']     // include search paths
        of.cFlags: []           // flags passed to the c compiler

        // flags passed to the c++ compiler
        of.cxxFlags: {
            var flags = [];
            if(qbs.configurationName.contains('Debug')){
                flags = flags.concat(['-g']);
            }else{
                flags = flag.concat(['-O2']);
            }
            return flags;
        }

        // flags passed to the linker
        of.linkerFlags: []

        // defines are passed as -D to the compiler
        of.defines: {
            var defs = [];
            //defs = defs.concat(['IMGUI_DISABLE_OBSOLETE_FUNCTIONS']); // Uncomment to check for depreciated imgui usage
            //defs = defs.concat(['OFXIMGUI_DEBUG']);  // Uncomment to debug ofxImGui
            if(qbs.configurationName.contains('Debug')){
                defs = defs.concat([]);
            }else if(qbs.configurationName.contains('Release')){
                defs = defs.concat([]);
            }else if(qbs.configurationName.contains('Profiling')){
                defs = defs.concat(['TRACY_ENABLE','TRACY_ONLY_IPV4','MOSAIC_ENABLE_PROFILING']);
            }
            return defs;
        }
        // and can be checked with #ifdef or #if in the code

        // osx only, additional frameworks to link with the project
        of.frameworks: ['/System/Library/Frameworks/CoreMIDI.framework']

        of.staticLibraries: []  // static libraries
        of.dynamicLibraries: [] // dynamic libraries

        // other flags can be set through the cpp module: http://doc.qt.io/qbs/cpp-module.html
        // eg: this will enable ccache when compiling
        //
        // cpp.compilerWrapper: 'ccache'

        // add CoreMIDI for osx
        /*Properties {
            condition: qbs.hostOS.contains("osx")
            of.frameworks: outer.concat(['CoreMIDI']);
        }*/

        // add QTKit support on osx 10.12
        Properties {
            condition: qbs.hostOS.contains("osx") && qbs.hostOS.contains("10.12")
            of.frameworks: outer.concat(['QTKit']);
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
