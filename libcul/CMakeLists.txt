cmake_minimum_required(VERSION 3.6)
project(libcul VERSION 1.0.1 DESCRIPTION "Common utility library.")

add_library(libcul SHARED
    src/*.cpp
)
target_include_directories(libcul PRIVATE inc)

set_target_properties(libcul PROPERTIES VERSION ${PROJECT_VERSION})