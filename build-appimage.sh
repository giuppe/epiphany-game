#!/usr/bin/env bash
VERSION=0.9.1
make distclean
./configure --prefix=/usr
make DESTDIR=$PWD/AppDir install
# download linuxdeploy from github
# https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage
./linuxdeploy-x86_64.AppImage  --appdir AppDir --desktop-file appdir-src/epiphany.desktop --icon-file appdir-src/epiphany.png --output appimage
mv Epiphany-x86_64.AppImage ./build/Epiphany-$VERSION-x86_64.AppImage 
