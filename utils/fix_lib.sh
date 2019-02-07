#!/bin/bash

echo "Copy"
sudo cp $HOME/cocos/coc*/extern*/linux-specific/fmod/prebuilt/64-bit/libfmod.so /usr/lib
sudo cp $HOME/cocos/coc*/extern*/linux-specific/fmod/prebuilt/64-bit/libfmodL.so /usr/lib

echo "Create link"
ln -s libfmod.so libfmod.so.6

echo "Install deps"
cd $HOME/cocos/coc*/build
./install-deps-linux.sh
