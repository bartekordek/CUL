ifeq ($(OS),Windows_NT)
DYN_LIB_EXT := .dll
BUILD_ROOT := Build-Cygwin
else
DYN_LIB_EXT := .so
BUILD_ROOT := Build-Linux
endif

DIAG_FLAG := -fdiagnostics-color=always
COMPILER := g++ #clang++-6.0
CPP_VERSION := --std=c++17
CC := $(COMPILER) 
CC_FLAGS := $(CPP_VERSION) $(DIAG_FLAG) \
-fPIC -pedantic -Wall -Werror
CC_LINK := $(COMPILER) $(DIAG_FLAG) -shared -fPIC

DEBUG_FLAGS = -ggdb3
RELEASE_FLAGS = -Ofast
PROJECT_NAME = libcul
IMP_LIB_NAME = $(PROJECT_NAME).a
OUTPUT_DIR := ../$(BUILD_ROOT)
OUTPUT_DIR_DEBUG = $(OUTPUT_DIR)/Debug
OUTPUT_DIR_RELEASE = $(OUTPUT_DIR)/Release

#DEPS
HOME_DEPS := ../deps

#BOOST ROOT
BOOST_ROOT := $(HOME_DEPS)/boost
BOOST_ASSERT := $(BOOST_ROOT)/assert
BOOST_CIRCULAR_BUFFER := $(BOOST_ROOT)/circular_buffer
BOOST_CONFIG := $(BOOST_ROOT)/config
BOOST_CONTAINER_HASH := $(BOOST_ROOT)/container_hash
BOOST_CONCEPT_CHECK := $(BOOST_ROOT)/concept_check
BOOST_CORE := $(BOOST_ROOT)/core
BOOST_MOVE := $(BOOST_ROOT)/move
BOOST_PREPROCESSOR := $(BOOST_ROOT)/preprocessor
BOOST_STATIC_ASSERT := $(BOOST_ROOT)/static_assert
BOOST_THROW_EXCEPTION := $(BOOST_ROOT)/throw_exception
BOOST_TYPE_INDEX := $(BOOST_ROOT)/type_index
BOOST_TYPE_TRAITS := $(BOOST_ROOT)/type_traits
BOOST_TYPE_VARIANT := $(BOOST_ROOT)/variant

RAPIDJSON_INCLUDE := $(HOME_DEPS)/rapidjson/include

# SPDLOG
SPDLOG_HOME := $(HOME_DEPS)/spdlog
SPDLOG_INCLUDE := $(SPDLOG_HOME)/include

HEADER_INC := -I inc
HEADER_INC += -I $(BOOST_ASSERT)/include
HEADER_INC += -I $(BOOST_CIRCULAR_BUFFER)/include
HEADER_INC += -I $(BOOST_CONFIG)/include
HEADER_INC += -I $(BOOST_CONCEPT_CHECK)/include
HEADER_INC += -I $(BOOST_CONTAINER_HASH)/include
HEADER_INC += -I $(BOOST_CORE)/include
HEADER_INC += -I $(BOOST_MOVE)/include
HEADER_INC += -I $(BOOST_PREPROCESSOR)/include
HEADER_INC += -I $(BOOST_STATIC_ASSERT)/include
HEADER_INC += -I $(BOOST_THROW_EXCEPTION)/include
HEADER_INC += -I $(BOOST_TYPE_INDEX)/include
HEADER_INC += -I $(BOOST_TYPE_TRAITS)/include
HEADER_INC += -I $(BOOST_TYPE_VARIANT)/include
HEADER_INC += -I $(RAPIDJSON_INCLUDE)
HEADER_INC += -I $(SPDLOG_INCLUDE)
HEADER_INC += -I src

OUTPUT_DEBUG = $(OUTPUT_DIR_DEBUG)/$(DLL_NAME)
OUTPUT_RELEASE = $(OUTPUT_DIR_RELEASE)/$(DLL_NAME)
IMP_LIB_DEBUG = $(OUTPUT_DIR_DEBUG)/$(IMP_LIB_NAME)
IMP_LIB_RELEASE = $(OUTPUT_DIR_RELEASE)/$(IMP_LIB_NAME)

IMP_LIBS := $(shell pkg-config --libs libpng)
IMP_LIBS += $(shell pkg-config --libs IL)
IMP_LIBS += $(shell pkg-config --libs ILU)
IMP_LIBS += $(shell pkg-config --libs ILUT)
IMP_LIBS += -lstdc++fs

CPP_FILES := $(wildcard src/*.cpp)
CPP_FILES += $(wildcard src/*/*.cpp)

# OBJ:
OBJ_DEBUG_DIR := $(OUTPUT_DIR_DEBUG)/obj/debug/
OBJ_RELEASE_DIR := $(OUTPUT_DIR_DEBUG)/obj/release/
OBJ_DEBUG_FILES := $(addprefix $(OBJ_DEBUG_DIR),$(CPP_FILES:.cpp=.o))
OBJ_RELEASE_FILES := $(addprefix $(OBJ_RELEASE_DIR),$(CPP_FILES:.cpp=.o))

DEP := $(patsubst %.cpp,%.d,$(CPP_FILES))

DLL_NAME = $(PROJECT_NAME)$(DYN_LIB_EXT)

debug: $(OUTPUT_DEBUG)
release: $(OUTPUT_RELEASE)

$(OUTPUT_DEBUG): $(OBJ_DEBUG_FILES)
	@mkdir -p $(@D)
	$(CC_LINK) -o $(OUTPUT_DEBUG) $(OBJ_DEBUG_FILES) $(IMP_LIBS) $(IMPORT_LIBS_DEBUG)

$(OUTPUT_RELEASE): $(OBJ_RELEASE_FILES)
	@mkdir -p $(@D)
	$(CC_LINK) -o $(OUTPUT_RELEASE) $(OBJ_RELEASE_FILES) $(IMP_LIBS) $(RELEASE_FLAGS) $(IMPORT_LIBS_RELEASE)

#depend: .depend

# Replace $< (first dependency) with $^ (all dependencies).

$(OBJ_DEBUG_DIR)%.o: %.cpp
	@mkdir -p $(dir $@)
	rm -f ./.depend
	#$(CC) $(CC_FLAGS) $(HEADER_INC) -MM $^ > ./.depend;
	$(CC) $(CC_FLAGS) $(HEADER_INC) $(DEBUG_FLAGS) -c -o $@ $<

$(OBJ_RELEASE_DIR)%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) $(HEADER_INC) $(RELEASE_FLAGS) -c -o $@ $^

clean:
	rm -rf $(OUTPUT_DIR)

test:
	@echo "DEP = $(DEP)"

#include .depend
