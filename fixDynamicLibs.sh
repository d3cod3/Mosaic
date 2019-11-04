#!/bin/bash

SCRIPTPATH="$( cd "$(dirname "$0")" ; pwd -P )"
APPNAME="Mosaic"

install_name_tool -change @rpath/libndi.3.dylib @executable_path/libndi.3.dylib $SCRIPTPATH/bin/$APPNAME.app/Contents/MacOS/$APPNAME
