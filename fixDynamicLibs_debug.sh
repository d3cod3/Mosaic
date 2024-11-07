#!/bin/bash

SCRIPTPATH="$( cd "$(dirname "$0")" ; pwd -P )"
APPNAME="Mosaic_debug"

# to check binary dependencies: otool -L $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME

install_name_tool -change @rpath/libndi.3.dylib @executable_path/libndi.3.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
install_name_tool -change @rpath/libopendht.2.dylib @executable_path/libopendht.2.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
install_name_tool -change @rpath/libgnutls.30.dylib @executable_path/libgnutls.30.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
install_name_tool -change @rpath/libnettle.8.dylib @executable_path/libnettle.8.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
install_name_tool -change @rpath/libfmt.11.dylib @executable_path/libfmt.11.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
#install_name_tool -change /usr/local/opt/gnutls/lib/libgnutls.30.dylib @executable_path/libgnutls.30.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/libopendht.2.dylib
#install_name_tool -change /usr/local/opt/nettle/lib/libnettle.8.dylib @executable_path/libnettle.8.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/libopendht.2.dylib
#install_name_tool -change @rpath/libintl.8.dylib @loader_path/libintl.8.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/libgnutls.30.dylib
#install_name_tool -change @rpath/libp11-kit.0.dylib @loader_path/libp11-kit.0.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/libgnutls.30.dylib
#install_name_tool -change @rpath/libidn2.0.dylib @loader_path/libidn2.0.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/libgnutls.30.dylib
#install_name_tool -change @rpath/libunistring.5.dylib @loader_path/libunistring.5.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/libgnutls.30.dylib
#install_name_tool -change @rpath/libtasn1.6.dylib @loader_path/libtasn1.6.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/libgnutls.30.dylib
#install_name_tool -change @rpath/libnettle.8.dylib @loader_path/libnettle.8.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/libgnutls.30.dylib
#install_name_tool -change @rpath/libhogweed.6.dylib @loader_path/libhogweed.6.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/libgnutls.30.dylib
#install_name_tool -change @rpath/libgmp.10.dylib @loader_path/libgmp.10.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/libgnutls.30.dylib
#install_name_tool -change @rpath/libffi.8.dylib @loader_path/libffi.8.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/libp11-kit.0.dylib
#install_name_tool -change @rpath/libintl.8.dylib @loader_path/libintl.8.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/libp11-kit.0.dylib
#install_name_tool -change @rpath/libunistring.5.dylib @loader_path/libunistring.5.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/libidn2.0.dylib
#install_name_tool -change @rpath/libintl.8.dylib @loader_path/libintl.8.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/libidn2.0.dylib
#install_name_tool -change @rpath/libnettle.8.dylib @loader_path/libnettle.8.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/libhogweed.6.dylib
#install_name_tool -change @rpath/libgmp.10.dylib @loader_path/libgmp.10.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/libhogweed.6.dylib
install_name_tool -change @rpath/ffmpeg/lib/osx/libavcodec.58.dylib @executable_path/libavcodec.58.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
install_name_tool -change @rpath/ffmpeg/lib/osx/libavformat.58.dylib @executable_path/libavformat.58.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
install_name_tool -change @rpath/ffmpeg/lib/osx/libavutil.56.dylib @executable_path/libavutil.56.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
install_name_tool -change @rpath/ffmpeg/lib/osx/libswresample.3.dylib @executable_path/libswresample.3.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
install_name_tool -change @rpath/snappy/lib/osx/libsnappy.1.dylib @executable_path/libsnappy.1.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
