#!/bin/bash

rm -rf *
clear
cmake -DCMAKE_BUILD_TYPE=Debug -G  "Unix Makefiles" $1
make -j12