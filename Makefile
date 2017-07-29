CC = g++

CPP_FILES := $(shell cat sourcesList)
HEADERS_DIRS := $(shell cat headerDirs)

debug: $(OUTPUT_DEBUG)
release: $(OUTPUT_RELEASE)

ifeq ($(OS),Windows_NT)
    DYN_LIB_EXT = .dll
else
    DYN_LIB_EXT = .so
endif

ifeq ($(BUILD_TYPE),dynamic)

else

endif
