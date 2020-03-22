#!/bin/bash

sudo apt install libpng-dev -y
sudo apt install libdevil-dev -y
sudo apt install googletest* -y

GTEST_BUILD_PATH=Build-Linux
cd googletest;
mkdir -p $GTEST_BUILD_PATH;
cd $GTEST_BUILD_PATH
cmake .. -G "Unix Makefiles"
make -j 8
sudo make install
cd ../..
