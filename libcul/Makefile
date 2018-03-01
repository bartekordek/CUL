ARCH := $(shell getconf LONG_BIT)
ifeq ($(OS),Windows_NT)
DYN_LIB_EXT := .dll
BUILD_ROOT := Build-Cygwin
else
DYN_LIB_EXT := .so
BUILD_ROOT := Build-Linux
endif

#ifeq ($(ARCH),64)
#ARCH_FLAG := -m64
#else
#ARCH_FLAG := -m32
#endif

DIAG_FLAG := -fdiagnostics-color=always
CC := g++ $(ARCH_FLAG) $(DIAG_FLAG) -fPIC
CC_LINK := g++ $(ARCH_FLAG) $(DIAG_FLAG) -shared -fPIC
COMPILER_FLAGS = -pedantic -Wall -std=c++11 -D CUL_EXPORT -D CUL_LINUX -Wno-ignored-attributes
DEBUG_FLAGS = -ggdb
RELEASE_FLAGS = -Ofast
PROJECT_NAME = libcul
IMP_LIB_NAME = $(PROJECT_NAME).a
OUTPUT_DIR := ../build
OUTPUT_DIR_DEBUG = $(OUTPUT_DIR)/Debug
OUTPUT_DIR_RELEASE = $(OUTPUT_DIR)/Release

#DEPS
HOME_DEPS := ../deps
HOME_BOOST := $(HOME_DEPS)/boost_1_66_0
BOOST_LIB := $(HOME_BOOST)/$(BUILD_ROOT)
BOOST_IMP_LIB := $(BOOST_LIB)/libboost_filesystem-gcc54-mt-x64-1_66.a $(BOOST_LIB)/libboost_system-gcc54-mt-x64-1_66.a

HEADER_INC = -I inc -I $(HOME_BOOST)
IMPORT_LIBS_DEBUG = $(BOOST_IMP_LIB)
IMPORT_LIBS_RELEASE = $(BOOST_IMP_LIB)
OUTPUT_DEBUG = $(OUTPUT_DIR_DEBUG)/$(DLL_NAME)
OUTPUT_RELEASE = $(OUTPUT_DIR_RELEASE)/$(DLL_NAME)
IMP_LIB_DEBUG = $(OUTPUT_DIR_DEBUG)/$(IMP_LIB_NAME)
IMP_LIB_RELEASE = $(OUTPUT_DIR_RELEASE)/$(IMP_LIB_NAME)

CPP_FILES := $(wildcard src/*.cpp)

OBJ_DEBUG_DIR := obj/debug/
OBJ_RELEASE_DIR := obj/release/
OBJ_DEBUG_FILES := $(addprefix $(OBJ_DEBUG_DIR),$(CPP_FILES:.cpp=.o))
OBJ_RELEASE_FILES := $(addprefix $(OBJ_RELEASE_DIR),$(CPP_FILES:.cpp=.o))

DLL_NAME = $(PROJECT_NAME)$(DYN_LIB_EXT)

debug: $(OUTPUT_DEBUG)
release: $(OUTPUT_RELEASE)

$(OUTPUT_DEBUG): $(OBJ_DEBUG_FILES)
	@mkdir -p $(@D)
	$(CC_LINK) -o $(OUTPUT_DEBUG) $(OBJ_DEBUG_FILES) $(DEBUG_FLAGS) $(IMPORT_LIBS_DEBUG)

$(OUTPUT_RELEASE): $(OBJ_RELEASE_FILES)
	@mkdir -p $(@D)
	$(CC_LINK) -o $(OUTPUT_RELEASE) $(OBJ_RELEASE_FILES) $(RELEASE_FLAGS) $(IMPORT_LIBS_RELEASE)

$(OBJ_DEBUG_DIR)%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(HEADER_INC) $(COMPILER_FLAGS) $(DEBUG_FLAGS) -c -o $@ $<

$(OBJ_RELEASE_DIR)%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(HEADER_INC) $(COMPILER_FLAGS) $(RELEASE_FLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ_DEBUG_FILES)
	rm -f $(OBJ_RELEASE_FILES)
	rm -f $(OUTPUT_DEBUG)
	rm -f $(OUTPUT_RELEASE)
	find . -name '*.o' | xargs rm -fv
