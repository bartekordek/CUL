CC = g++
CC_LINK = g++ -shared
CUL_PREPROCESOR_FLAGS := -D CULLib_EXPORT -D CUL_DYNAMIC
COMPILER_FLAGS = -pedantic -Wall -std=c++11 $(CUL_PREPROCESOR_FLAGS) -Wno-ignored-attributes
DEBUG_FLAGS = -ggdb
RELEASE_FLAGS = -Ofast
PROJECT_NAME = libcul
IMP_LIB_NAME = $(PROJECT_NAME).a
OUTPUT_DIR := ../build
OUTPUT_DIR_DEBUG = $(OUTPUT_DIR)/Debug
OUTPUT_DIR_RELEASE = $(OUTPUT_DEBUG)/Release

HEADER_INC = -I .. -I $(HOME_BOOST_LINUX)
IMPORT_LIBS_DEBUG = $(HOME_BOOST_LINUX)/Build-Linux/lib/libboost_filesystem-mt.a $(HOME_BOOST_LINUX)/Build-Linux/lib/libboost_system-mt.a
IMPORT_LIBS_RELEASE = $(HOME_BOOST_LINUX)/Build-Linux/lib/libboost_filesystem-mt.a $(HOME_BOOST_LINUX)/Build-Linux/lib/libboost_system-mt.a
OUTPUT_DEBUG = $(OUTPUT_DIR_DEBUG)/$(DLL_NAME)
OUTPUT_RELEASE = $(OUTPUT_DIR_RELEASE)/$(DLL_NAME)
IMP_LIB_DEBUG = $(OUTPUT_DIR_DEBUG)/$(IMP_LIB_NAME)
IMP_LIB_RELEASE = $(OUTPUT_DIR_RELEASE)/$(IMP_LIB_NAME)

CPP_FILES := $(wildcard */*.cpp)

OBJ_DEBUG_DIR := obj/debug/
OBJ_DEBUG_FILES := $(addprefix $(OBJ_DEBUG_DIR),$(CPP_FILES:.cpp=.o))

OBJ_RELEASE_DIR := obj/release/
OBJ_RELEASE_FILES := $(addprefix $(OBJ_RELEASE_DIR),$(CPP_FILES:.cpp=.o))
	
ifeq ($(OS),Windows_NT)
    DYN_LIB_EXT = .dll
else
    DYN_LIB_EXT = .so
endif

DLL_NAME = $(PROJECT_NAME)$(DYN_LIB_EXT)

debug: $(OUTPUT_DEBUG)
release: $(OUTPUT_RELEASE)

$(OUTPUT_DEBUG): $(OBJ_DEBUG_FILES)
	$(CC_LINK) -o $(OUTPUT_DEBUG) $(OBJ_DEBUG_FILES) $(DEBUG_FLAGS) $(IMPORT_LIBS_DEBUG) -Wl,--out-implib,$(OUTPUT_DIR_DEBUG)/$(IMP_LIB_NAME) -Wl,--export-all-symbols -Wl,--enable-auto-import
	cp -fv $(HOME_SDL2_LINUX)/Build-Linux/build/.libs/*$(DYN_LIB_EXT) $(OUTPUT_DIR_DEBUG)

$(OUTPUT_RELEASE): $(OBJ_RELEASE_FILES)
	$(CC_LINK) -o $(OUTPUT_RELEASE) $(OBJ_RELEASE_FILES) $(RELEASE_FLAGS) $(IMPORT_LIBS_RELEASE) -Wl,--out-implib,$(OUTPUT_DIR_RELEASE)/$(IMP_LIB_NAME) -Wl,--export-all-symbols -Wl,--enable-auto-import
	cp -fv $(HOME_SDL2_LINUX)/Build-Linux/build/.libs/*$(DYN_LIB_EXT) $(OUTPUT_DIR_RELEASE)

$(OBJ_DEBUG_DIR)%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(HEADER_INC) $(COMPILER_FLAGS) $(DEBUG_FLAGS) -c -o $@ $<

$(OBJ_RELEASE_DIR)%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(HEADER_INC) $(COMPILER_FLAGS) $(RELEASE_FLAGS) -c -o $@ $<

first_run:
	mkdir -p $(dir $(OBJ_DEBUG_FILES))
	mkdir -p $(dir $(OUTPUT_DEBUG))
	mkdir -p $(dir $(OBJ_RELEASE_FILES))
	mkdir -p $(dir $(OUTPUT_RELEASE))

clean:
	rm -f $(OBJ_DEBUG_FILES)
	rm -f $(OBJ_RELEASE_FILES)
	rm -f $(OUTPUT_DEBUG)
	rm -f $(OUTPUT_RELEASE)
	find . -name '*.o' | xargs rm -fv
	
test:
	@echo "All .o files: $(OBJ_DEBUG_FILES)"
	@echo "All .cpp files: $(CPP_FILES)"
	@echo "SDL2: $(HOME_SDL2_LINUX)/"

help:
	echo "If run first time, please run \"make first_run\" it will create necessary dirs."
