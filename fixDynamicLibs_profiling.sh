#!/bin/bash

SCRIPTPATH="$( cd "$(dirname "$0")" ; pwd -P )"
APPNAME="Mosaic_profiling"

# to check binary dependencies: otool -L $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME

install_name_tool -change @rpath/libndi.3.dylib @executable_path/libndi.3.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
install_name_tool -change @rpath/ffmpeg/lib/osx/libavcodec.58.dylib @executable_path/libavcodec.58.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
install_name_tool -change @rpath/ffmpeg/lib/osx/libavformat.58.dylib @executable_path/libavformat.58.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
install_name_tool -change @rpath/ffmpeg/lib/osx/libavutil.56.dylib @executable_path/libavutil.56.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
install_name_tool -change @rpath/ffmpeg/lib/osx/libswresample.3.dylib @executable_path/libswresample.3.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
install_name_tool -change @rpath/ffmpeg/lib/osx/libavcodec.57.dylib @executable_path/libavcodec.57.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
install_name_tool -change @rpath/ffmpeg/lib/osx/libavformat.57.dylib @executable_path/libavformat.57.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
install_name_tool -change @rpath/ffmpeg/lib/osx/libavutil.55.dylib @executable_path/libavutil.55.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
install_name_tool -change @rpath/ffmpeg/lib/osx/libswresample.2.dylib @executable_path/libswresample.2.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
install_name_tool -change @rpath/snappy/lib/osx/libsnappy.1.dylib @executable_path/libsnappy.1.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
