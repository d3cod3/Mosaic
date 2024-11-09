#!/bin/bash

SCRIPTPATH="$( cd "$(dirname "$0")" ; pwd -P )"
APPNAME="Mosaic_profiling"

# to check binary dependencies: otool -L $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME

install_name_tool -change @rpath/libndi.3.dylib @executable_path/libndi.3.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
install_name_tool -change @rpath/libopendht.2.dylib @executable_path/libopendht.2.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
install_name_tool -change @rpath/libgnutls.30.dylib @executable_path/libgnutls.30.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
install_name_tool -change @rpath/libnettle.8.dylib @executable_path/libnettle.8.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
install_name_tool -change @rpath/libfmt.11.dylib @executable_path/libfmt.11.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
install_name_tool -change /usr/local/lib/libgnutls.30.dylib @executable_path/libgnutls.30.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
install_name_tool -change /usr/local/opt/nettle/lib/libnettle.8.dylib @executable_path/libnettle.8.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
install_name_tool -change /usr/local/opt/fmt/lib/libfmt.11.dylib @executable_path/libfmt.11.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
install_name_tool -change @rpath/ffmpeg/lib/osx/libavcodec.58.dylib @executable_path/libavcodec.58.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
install_name_tool -change @rpath/ffmpeg/lib/osx/libavformat.58.dylib @executable_path/libavformat.58.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
install_name_tool -change @rpath/ffmpeg/lib/osx/libavutil.56.dylib @executable_path/libavutil.56.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
install_name_tool -change @rpath/ffmpeg/lib/osx/libswresample.3.dylib @executable_path/libswresample.3.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
install_name_tool -change @rpath/snappy/lib/osx/libsnappy.1.dylib @executable_path/libsnappy.1.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
