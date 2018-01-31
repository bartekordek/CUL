CC = g++ -fdiagnostics-color=always
CC_LINK = g++ -fdiagnostics-color=always -shared
COMPILER_FLAGS = -pedantic -Wall -std=c++11 -DCULLib_EXPORT -DCUL_DYNAMIC -Wno-ignored-attributes
LINKER_ENABLE_IMPORT := -Wl,--export-all-symbols -Wl,--enable-auto-import
DEBUG_FLAGS = -ggdb
RELEASE_FLAGS = -Ofast
PROJECT_NAME = libcul
IMP_LIB_NAME = $(PROJECT_NAME).a
OUTPUT_DIR := ../build
OUTPUT_DIR_DEBUG = $(OUTPUT_DIR)/Debug
OUTPUT_DIR_RELEASE = $(OUTPUT_DIR)/Release

HOME_BOOST := ../deps/boost_1_64_0
ifeq ($(OS),Windows_NT)
BOOST_LIB_DIR := $(HOME_BOOST)/Build-Cygwin
else
BOOST_LIB_DIR := $(HOME_BOOST)/Build-Linux
endif
BOOST_FS_LIB_PATH := $(BOOST_LIB_DIR)/libboost_filesystem-mt.a
BOOST_SYS_LIB_PATH := $(BOOST_LIB_DIR)/libboost_system-mt.a

HEADER_INC = -I inc -I $(HOME_BOOST)
IMPORT_LIBS_DEBUG = $(BOOST_FS_LIB_PATH) $(BOOST_SYS_LIB_PATH)
IMPORT_LIBS_RELEASE = $(BOOST_FS_LIB_PATH) $(BOOST_SYS_LIB_PATH)
OUTPUT_DEBUG = $(OUTPUT_DIR_DEBUG)/$(DLL_NAME)
OUTPUT_RELEASE = $(OUTPUT_DIR_RELEASE)/$(DLL_NAME)
IMP_LIB_DEBUG = $(OUTPUT_DIR_DEBUG)/$(IMP_LIB_NAME)
IMP_LIB_RELEASE = $(OUTPUT_DIR_RELEASE)/$(IMP_LIB_NAME)

CPP_FILES := $(wildcard src/*.cpp)

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
	@mkdir -p $(@D)
	$(CC_LINK) -o $(OUTPUT_DEBUG) $(OBJ_DEBUG_FILES) $(DEBUG_FLAGS) $(IMPORT_LIBS_DEBUG) -Wl,--out-implib,$(OUTPUT_DIR_DEBUG)/$(IMP_LIB_NAME) $(LINKER_ENABLE_IMPORT)
	cp -fv $(HOME_SDL2_LINUX)/Build-Linux/build/.libs/*$(DYN_LIB_EXT) $(OUTPUT_DIR_DEBUG)

$(OUTPUT_RELEASE): $(OBJ_RELEASE_FILES)
	@mkdir -p $(@D)
	$(CC_LINK) -o $(OUTPUT_RELEASE) $(OBJ_RELEASE_FILES) $(RELEASE_FLAGS) $(IMPORT_LIBS_RELEASE) -Wl,--out-implib,$(OUTPUT_DIR_RELEASE)/$(IMP_LIB_NAME) $(LINKER_ENABLE_IMPORT)
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
