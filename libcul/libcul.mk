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

DEP_DEBUG := $(patsubst %.o,%.d,$(OBJ_DEBUG_FILES))
DEP_RELEASE := $(patsubst %.o,%.d,$(OBJ_RELEASE_FILES))

PROG_DEBUG := $(patsubst %.cpp,%,$(CPP_FILES))

debug: $(DEP_DEBUG)
	@echo "Rule for: $@."
	@echo "Dependencies1: $@"
	@echo "Dependencies1: $(DEP_DEBUG)"
	$(MAKE) $(PROG_DEBUG)

%.d:
	@echo "Rule for: $@."
	@echo "COOOO? $<"
	@echo "ELO: `echo "$@" | sed 's/.*src/src/' | sed 's/\.d/\.cpp/'`"
	@mkdir -p $(dir $@)
	$(CC)`echo "$@" | sed 's/.*src/src/' | sed 's/\.d/\.cpp/'` -MM  $(HEADER_INC)  $(CC_FLAGS)  > $@

%: %.d
	echo "Compiling $@"

test:
	echo "DEP_DEBUG = $(DEP_DEBUG)"
	echo "\n\n\n\n"
	echo "OBJ_DEBUG_FILES = $(OBJ_DEBUG_FILES)"
	echo "\n\n\n\n"
	echo "PROG_DEBUG = $(PROG_DEBUG)"

clean:
	rm -rfv $(OUTPUT_DIR)