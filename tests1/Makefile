CC = g++
CC_LINK = g++
COMPILER_FLAGS = -pedantic -Wall -std=c++11 -D MogeLib_EXPORT="1" -Wno-ignored-attributes
DEBUG_FLAGS = -ggdb
RELEASE_FLAGS = -Ofast
PROJECT_NAME = Tetris
BINARY_NAME = $(PROJECT_NAME).exe 
OUTPUT_DIR_DEBUG = ../Build/Debug
OUTPUT_DIR_RELEASE = ../Build/Release
HEADER_INC = -I ../MogeLib/inc/ -I inc/
OUTPUT_DEBUG = $(OUTPUT_DIR_DEBUG)/$(BINARY_NAME)
OUTPUT_RELEASE = $(OUTPUT_DIR_RELEASE)/$(BINARY_NAME)

IMP_DIRS_D = -L$(OUTPUT_DIR_DEBUG) 
IMP_DIRS_R = -L$(OUTPUT_DIR_RELEASE)

LINK2 = -lmoge

CPP_FILES := $(wildcard */*.cpp)
CPP_FILES += main.cpp

OBJ_DEBUG_DIR := obj/debug/
OBJ_DEBUG_FILES := $(addprefix $(OBJ_DEBUG_DIR),$(CPP_FILES:.cpp=.o))

OBJ_RELEASE_DIR := obj/release/
OBJ_RELEASE_FILES := $(addprefix $(OBJ_RELEASE_DIR),$(CPP_FILES:.cpp=.o))
	
ifeq ($(OS),Windows_NT)
    DYN_LIB_EXT = .dll
else
    DYN_LIB_EXT = .so
endif

debug: run_debug_deps $(OUTPUT_DEBUG)
release: run_release_deps $(OUTPUT_RELEASE)

run_debug:
	make debug
	cd $(OUTPUT_DIR_DEBUG);./$(BINARY_NAME)

run_release:
	make release
	cd $(OUTPUT_DIR_RELEASE);./$(BINARY_NAME)

$(OUTPUT_DEBUG): $(OBJ_DEBUG_FILES)
	$(CC_LINK) -o $(OUTPUT_DEBUG) $(DEBUG_FLAGS) $(OBJ_DEBUG_FILES) $(IMP_DIRS_D) $(LINK2) 

$(OUTPUT_RELEASE): $(OBJ_RELEASE_FILES)
	$(CC_LINK) -o $(OUTPUT_RELEASE) $(RELEASE_FLAGS) $(OBJ_RELEASE_FILES) $(IMP_DIRS_R) $(LINK2)

$(OBJ_DEBUG_DIR)%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(HEADER_INC) $(COMPILER_FLAGS) $(DEBUG_FLAGS) -c -o $@ $<

$(OBJ_RELEASE_DIR)%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(HEADER_INC) $(COMPILER_FLAGS) $(RELEASE_FLAGS) -c -o $@ $<

run_debug_deps:
	make -C ../MogeLib debug

run_release_deps:
	make -C ../MogeLib release

first_run:
	mkdir -p $(dir $(OBJ_DEBUG_FILES)) 
	mkdir -p $(dir $(OUTPUT_DEBUG))
	mkdir -p $(dir $(OBJ_RELEASE_FILES)) 
	mkdir -p $(dir $(OUTPUT_RELEASE))

clean:
	make -C ../MogeLib clean
	rm -f $(OBJ_DEBUG_FILES)
	rm -f $(OBJ_RELEASE_FILES)
	rm -f $(OUTPUT_DEBUG)
	rm -f $(OUTPUT_RELEASE)
	find .. -name '*.o' | xargs rm -fv

test:
	@echo "All .o files: $(OBJ_DEBUG_FILES)"
	@echo "All .cpp files: $(CPP_FILES)" 
	@echo "SDL2: $(HOME_SDL2_CYGWIN)/"

help:
	echo "If run first time, please run \"make first_run\" it will create necessary dirs."
