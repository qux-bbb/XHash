#!/bin/sh

linuxdeploy=~/Downloads/linuxdeploy-x86_64.AppImage

if [ -e linux_build ]
then
    rm linux_build -rf
fi

mkdir linux_build
cd linux_build
qmake ../src
make -j$(nproc)
make install INSTALL_ROOT=AppDir
$linuxdeploy -d ../xhash.desktop -i ../src/xhash.png --appdir AppDir --output appimage --plugin qt
