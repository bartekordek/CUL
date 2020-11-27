#!/bin/bash

#find . -name '*.hpp' -o -name '*.h' | sed 's/\.\///g'
#find . -name '*.cpp' -o -name '*.c' | sed 's/\.\///g'

find . -name '*.hpp' -o -name '*.h' | sed 's/\.\///g' > HEADER_FILES_LIST.txt
find . -name '*.cpp' -o -name '*.c' | sed 's/\.\///g' > CPP_FILES_LIST.txt
