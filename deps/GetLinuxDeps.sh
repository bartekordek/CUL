#!/bin/bash

sudo apt-get install libpng-dev -y

GTEST_BUILD_PATH=Build-Linux
cd googletest;
mkdir -p $GTEST_BUILD_PATH;
cd $GTEST_BUILD_PATH
cmake .. -G "Unix Makefiles"
make -j 8
cd ../..
