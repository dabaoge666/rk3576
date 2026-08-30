#!/bin/bash -e

SCRIPTS_PATH=$(dirname "$0")
SDK_PATH_=${SCRIPTS_PATH}/../../..

ENV_PATH=${SDK_PATH_}/buildroot/output/rockchip_rk3576/host/environment-setup
sudo sed -i '69,$d' $ENV_PATH

echo '_SDK_PATH=$(dirname "${BASH_SOURCE[0]}")' | sudo tee -a $ENV_PATH
echo 'export _SDK_PATH="$(cd "$_SDK_PATH" && pwd)"' | sudo tee -a $ENV_PATH
echo 'export SDK_QMAKE_SYSROOT=$_SDK_PATH/aarch64-buildroot-linux-gnu/sysroot' | sudo tee -a $ENV_PATH
echo 'export QT_HOST_PREFIX=$_SDK_PATH' | sudo tee -a $ENV_PATH
echo 'export PATH=$_SDK_PATH/bin:$PATH' | sudo tee -a $ENV_PATH

echo "----------set environment success-----------"

# Modify qt.conf, qdevice.pri, qconfig.pri and qmake.conf so that user can use sysroots in any path
sudo sed -i 's/QMAKE_CFLAGS    += --sysroot=$$\[QT_SYSROOT\]/QMAKE_CFLAGS    += --sysroot=$$(SDK_QMAKE_SYSROOT)/g' $SDK_PATH_/buildroot/output/rockchip_rk3576/host/mkspecs/qconfig.pri
sudo sed -i 's/QMAKE_CXXFLAGS  += --sysroot=$$\[QT_SYSROOT\]/QMAKE_CXXFLAGS  += --sysroot=$$(SDK_QMAKE_SYSROOT)/g' $SDK_PATH_/buildroot/output/rockchip_rk3576/host/mkspecs/qconfig.pri
sudo sed -i 's/QMAKE_LFLAGS    += --sysroot=$$\[QT_SYSROOT\]/QMAKE_LFLAGS    += --sysroot=$$(SDK_QMAKE_SYSROOT)/g' $SDK_PATH_/buildroot/output/rockchip_rk3576/host/mkspecs/qconfig.pri
sudo sed -i '17,18d' $SDK_PATH_/buildroot/output/rockchip_rk3576/host/mkspecs/qconfig.pri
sudo sed -i '17i\
PKG_CONFIG_SYSROOT_DIR = $$(SDK_QMAKE_SYSROOT)\
PKG_CONFIG_LIBDIR = $$(SDK_QMAKE_SYSROOT)/usr/lib/pkgconfig:$$(SDK_QMAKE_SYSROOT)/usr/share/pkgconfig:$$(SDK_QMAKE_SYSROOT)/usr/lib/aarch64-linux-gnu/pkgconfig' $SDK_PATH_/buildroot/output/rockchip_rk3576/host/mkspecs/qconfig.pri
sudo sed -i 's/QMAKE_LINK              = $$(SDK_QMAKE_CXX)/QMAKE_LINK              = $$(SDK_QMAKE_CXX) -L $$(SDK_QMAKE_SYSROOT)\/usr\/lib\/aarch64-linux-gnu/g' $SDK_PATH_/buildroot/output/rockchip_rk3576/host/mkspecs/linux-aarch64-gnu-g++/qmake.conf

sudo sed -i 's/^HostPrefix=.*$/HostPrefix=$(QT_HOST_PREFIX)/' "$SDK_PATH_/buildroot/output/rockchip_rk3576/host/bin/qt.conf"
sudo sed -i 's/^Sysroot=.*$/Sysroot=$(SDK_QMAKE_SYSROOT)/' "$SDK_PATH_/buildroot/output/rockchip_rk3576/host/bin/qt.conf"

sudo sed -i "s|^CROSS_COMPILE = .*$|CROSS_COMPILE = \$\{_SDK_PATH\}/bin/aarch64-buildroot-linux-gnu-|" "$SDK_PATH_/buildroot/output/rockchip_rk3576/host/mkspecs/qdevice.pri"  

# Replace absolute paths with relative paths in sysroot
HOST_PATH=$SDK_PATH_/buildroot/output/rockchip_rk3576/host/

cd $HOST_PATH
HOST_PATH=$(pwd)

find . -type f -name "*.pri" -exec sed -i "s|${HOST_PATH}|\${QT_HOST_PREFIX}|g" {} +  

cd ..

