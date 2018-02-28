ARCH := $(shell getconf LONG_BIT)
ifeq ($(OS),Windows_NT)
DYN_LIB_EXT := .dll
BUILD_ROOT := Build-Cygwin
else
DYN_LIB_EXT := .so
BUILD_ROOT := Build-Linux
endif

ifeq ($(ARCH),64)
ARCH_FLAG := -m64
else
ARCH_FLAG := -m32
endif

DIAG_FLAG := -fdiagnostics-color=always
CC := g++ $(ARCH_FLAG) $(DIAG_FLAG) -fPIC
CC_LINK := g++ $(ARCH_FLAG) $(DIAG_FLAG)
CUL_PREPROCESOR_FLAGS := -D CULLib_EXPORT -D CUL_LINUX
COMPILER_FLAGS = -pedantic -Wall -std=gnu++11 $(CUL_PREPROCESOR_FLAGS) -Wno-ignored-attributes
DEBUG_FLAGS = -ggdb
RELEASE_FLAGS = -Ofast
PROJECT_NAME = Tests
BINARY_NAME = $(PROJECT_NAME).exe
OUTPUT_DIR := ../build
OUTPUT_DIR_DEBUG = $(OUTPUT_DIR)/Debug
OUTPUT_DIR_RELEASE = $(OUTPUT_DIR)/Release
RUN_DIR := ../runTestsDir

DEPS_ROOT := ../deps
GTEST_ROOT := $(DEPS_ROOT)/gtest
GTEST_INCLUDE := $(GTEST_ROOT)/googletest/include
GTEST_LIBRARY_DIR := $(GTEST_ROOT)/$(BUILD_ROOT)
ROOT_LIBCUL := ../libcul
LIBCUL_IMPORT_LIB := libcul.a

HEADER_INC := -I . -isystem $(GTEST_INCLUDE) -I $(ROOT_LIBCUL)/inc
IMPORT_LIBS_DEBUG := -L$(OUTPUT_DIR_DEBUG) -L$(GTEST_LIBRARY_DIR)
IMPORT_LIBS_RELEASE := -L$(OUTPUT_DIR_RELEASE) -L$(GTEST_LIBRARY_DIR)
IMPORT_LIBS_FILES := -lgtest -lgtest_main -lcul -pthread

CPP_FILES := $(wildcard */*.cpp)
CPP_FILES += $(wildcard *.cpp)

# $(@D) <- dir of target

# OBJ:
OBJ_DEBUG_DIR := $(OUTPUT_DIR_DEBUG)/intermediate_$(PROJECT_NAME)/debug/
OBJ_RELEASE_DIR := $(OUTPUT_DIR_RELEASE)/intermediate_$(PROJECT_NAME)/release/
OBJ_DEBUG_FILES := $(addprefix $(OBJ_DEBUG_DIR),$(CPP_FILES:.cpp=.o))
OBJ_RELEASE_FILES := $(addprefix $(OBJ_RELEASE_DIR),$(CPP_FILES:.cpp=.o))

debug: $(OUTPUT_DIR_DEBUG)/$(BINARY_NAME)
release: $(OUTPUT_DIR_RELEASE)/$(BINARY_NAME)

run_debug: $(OUTPUT_DIR_DEBUG)/$(BINARY_NAME)
	cd $(RUN_DIR);LD_LIBRARY_PATH=$(OUTPUT_DIR_DEBUG) ./$<

run_release: $(OUTPUT_DIR_RELEASE)/$(BINARY_NAME)
	cd $(RUN_DIR);LD_LIBRARY_PATH=$(OUTPUT_DIR_RELEASE) ./$<

$(OUTPUT_DIR_DEBUG)/$(BINARY_NAME): $(OBJ_DEBUG_FILES)
	@make deps_debug
	@mkdir -p $(@D)
	$(CC_LINK) -o $@ $(OBJ_DEBUG_FILES) $(IMPORT_LIBS_DEBUG) $(IMPORT_LIBS_FILES)

$(OUTPUT_DIR_RELEASE)/$(BINARY_NAME): $(OBJ_RELEASE_FILES)
	@make deps_release
	@mkdir -p $(@D)
	$(CC_LINK) -o $@ $(OBJ_RELEASE_FILES) $(IMPORT_LIBS_RELEASE) $(IMPORT_LIBS_FILES)

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
	make -C $(ROOT_LIBCUL) clean
	rm -f $(OBJ_DEBUG_FILES)
	rm -f $(OBJ_RELEASE_FILES)
	rm -f $(OUTPUT_DEBUG)
	rm -f $(OUTPUT_RELEASE)

deps_debug:
	make -C $(ROOT_LIBCUL) debug

deps_release:
	make -C $(ROOT_LIBCUL) release

clear_all:
	find . -name '*.o' | xargs rm

test:
	@echo "All .o files: $(OBJ_DEBUG_FILES)"
	@echo "All .cpp files: $(CPP_FILES)"
	@echo "ARCH: $(ARCH)"