ARCH := $(shell getconf LONG_BIT)
ifeq ($(OS),Windows_NT)
DYN_LIB_EXT := .dll
BUILD_ROOT := Build-Cygwin
else
DYN_LIB_EXT := .so
BUILD_ROOT := Build-Linux
endif

DIAG_FLAG := -fdiagnostics-color=always
COMPILER := g++
#COMPILER := clang++-6.0
CC := $(COMPILER) $(DIAG_FLAG) -fPIC
CC_LINK := $(COMPILER) $(DIAG_FLAG) -lstdc++fs
CPP_VERSION := -std=gnu++17
COMPILER_FLAGS = -pedantic -Wall $(CPP_VERSION) -Werror

DEBUG_FLAGS = -ggdb
RELEASE_FLAGS = -Ofast
PROJECT_NAME = Tests
BINARY_NAME = $(PROJECT_NAME).exe
OUTPUT_DIR := ../$(BUILD_ROOT)
OUTPUT_DIR_DEBUG = $(OUTPUT_DIR)/Debug
OUTPUT_DIR_RELEASE = $(OUTPUT_DIR)/Release
RUN_DIR := ../runDir

#DEPS
DEPS_ROOT := ../deps
GTEST_ROOT := $(DEPS_ROOT)/googletest
GTEST_INCLUDE := $(GTEST_ROOT)/googletest/include
GTEST_LIBRARY_DIR := $(GTEST_ROOT)/$(BUILD_ROOT)/lib

#DEPS::CUL
LIBCUL_ROOT := ../libcul
LIBCUL_INC := $(LIBCUL_ROOT)/inc
LIBCUL_LIB_DIR := ../$(BUILD_ROOT)
LIBCUL_LIB_NAME := libcul.so
LIBCUL_LIB_FILE_DEBUG := $(LIBCUL_LIB_DIR)/Debug/$(LIBCUL_LIB_NAME)
LIBCUL_LIB_FILE_RELEASE := $(LIBCUL_LIB_DIR)/Release/$(LIBCUL_LIB_NAME)

HEADER_INC := -I . -isystem $(GTEST_INCLUDE)
HEADER_INC += -I $(LIBCUL_INC)
IMPORT_LIBS_DEBUG := -L$(OUTPUT_DIR_DEBUG) -L$(GTEST_LIBRARY_DIR)
IMPORT_LIBS_RELEASE := -L$(OUTPUT_DIR_RELEASE) -L$(GTEST_LIBRARY_DIR)
IMPORT_LIBS_FILES := -lgtest -lgtest_main
IMPORT_LIBS_FILES += -pthread
IMPORT_LIBS_FILES += $(shell pkg-config --libs libpng)
IMPORT_LIBS_FILES_DEBUG := $(IMPORT_LIBS_FILES) $(LIBCUL_LIB_FILE_DEBUG)
IMPORT_LIBS_FILES_RELEASE := $(IMPORT_LIBS_FILES) $(LIBCUL_LIB_FILE_RELEASE)

CPP_FILES += $(wildcard *.cpp)

# $(@D) <- dir of target

# OBJ:
OBJ_DEBUG_DIR := obj/debug/
OBJ_RELEASE_DIR := obj/release/
OBJ_DEBUG_FILES := $(addprefix $(OBJ_DEBUG_DIR),$(CPP_FILES:.cpp=.o))
OBJ_RELEASE_FILES := $(addprefix $(OBJ_RELEASE_DIR),$(CPP_FILES:.cpp=.o))

debug: $(LIBCUL_LIB_FILE_DEBUG)
	@make $(OUTPUT_DIR_DEBUG)/$(BINARY_NAME)

release: $(IMPORT_LIBS_RELEASE)
	@make $(OUTPUT_DIR_RELEASE)/$(BINARY_NAME)

$(LIBCUL_LIB_FILE_DEBUG):
	make -C $(LIBCUL_ROOT) debug

$(IMPORT_LIBS_RELEASE):
	make -C $(LIBCUL_ROOT) release

run_debug: $(OUTPUT_DIR_DEBUG)/$(BINARY_NAME)
	cd $(RUN_DIR);LD_LIBRARY_PATH=$(OUTPUT_DIR_DEBUG) ./$< --gtest_break_on_failure

run_release: $(OUTPUT_DIR_RELEASE)/$(BINARY_NAME)
	cd $(RUN_DIR);LD_LIBRARY_PATH=$(OUTPUT_DIR_RELEASE) ./$< --gtest_break_on_failure

$(OUTPUT_DIR_DEBUG)/$(BINARY_NAME): $(OBJ_DEBUG_FILES)
	@mkdir -p $(@D)
	$(CC_LINK) -o $@ $(OBJ_DEBUG_FILES) $(IMPORT_LIBS_DEBUG) $(IMPORT_LIBS_FILES_DEBUG)

$(OUTPUT_DIR_RELEASE)/$(BINARY_NAME): $(OBJ_RELEASE_FILES)
	@mkdir -p $(@D)
	$(CC_LINK) -o $@ $(OBJ_RELEASE_FILES) $(IMPORT_LIBS_RELEASE) $(IMPORT_LIBS_FILES_RELEASE)

$(OUTPUT_DIR_DEBUG)/$(LIBCUL_IMPORT_LIB):
	@echo "HALO"

$(OUTPUT_DIR_RELEASE)/$(LIBCUL_IMPORT_LIB):
	@echo "HALO"

$(OBJ_DEBUG_DIR)%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(HEADER_INC) $(COMPILER_FLAGS) $(DEBUG_FLAGS) -c -o $@ $<

$(OBJ_RELEASE_DIR)%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(HEADER_INC) $(COMPILER_FLAGS) $(RELEASE_FLAGS) -c -o $@ $<

clean:
	make -C $(LIBCUL_ROOT) clean
	rm -f $(OBJ_DEBUG_FILES)
	rm -f $(OBJ_RELEASE_FILES)
	rm -f $(OUTPUT_DEBUG)
	rm -f $(OUTPUT_RELEASE)

clear_all:
	find . -name '*.o' | xargs rm

test:
	@echo "All .o files: $(OBJ_DEBUG_FILES)"
	@echo "All .cpp files: $(CPP_FILES)"
	@echo "ARCH: $(ARCH)"
