#!/bin/bash

find . -name '*.hpp' | sed 's/\.\///g' > HPP_FILES.txt
find . -name '*.cpp' | sed 's/\.\///g' > CPP_FILES.txt