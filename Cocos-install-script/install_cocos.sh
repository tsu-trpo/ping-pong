#!/bin/bash
set -e

echo "Start installing cocos..."

echo "Creating cocos folder..."
mkdir $HOME/cocos

echo "Downloading cocos archive..."
wget -P $HOME/cocos http://cdn.cocos2d-x.org/cocos2d-x-3.15.1.zip

echo "Unzipping cocos archive..."
unzip $HOME/cocos/cocos2d-x-3.15.1.zip -d $HOME/cocos

echo "Delete archive..."
rm -f $HOME/cocos/cocos2d-x-3.15.1.zip

echo "Installing deps..."
cd $HOME/cocos/cocos*/build
./install-deps-linux.sh

echo "Installing glfw package..."
cd $HOME/cocos/cocos*/tools/travis-scr*/
./install_glfw.sh

echo "Run setup..."
cd $HOME/cocos/cocos*/
./setup.py

echo "Reload .bashrc"
source ~/.bashrc

echo "Make cmake..."
cd $HOME/cocos/cocos*/build
mkdir linux-build
cd linux-build
cmake ../..

	#echo "Test application run..."
	# Very long operation
	#make
	#cd bin/cpp-tests/
	#./cpp-tests

echo "Done"
echo "If libfmod.so.6 error, run ./lib_fix script"