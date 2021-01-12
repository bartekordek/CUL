#cmake -DCMAKE_BUILD_TYPE=Debug
cmake_minimum_required(VERSION 3.0.0)

project(cul_main)

macro(CmakeToWindow InputPath OutputPath)
    string(REGEX REPLACE "/" "\\\\" ${OutputPath} "${InputPath}")
endmacro()

message( "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}" )
set( CMAKE_POSITION_INDEPENDENT_CODE ON )
set( CUL_TESTS_RUN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/runDir" )

if( MSVC )
    set( CUL_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Build-Windows )
else()
    set( CUL_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Build-Linux )
endif()

# Add sub directories
add_subdirectory( deps )
add_subdirectory( deps/boost/assert )
add_subdirectory( deps/boost/circular_buffer )
add_subdirectory( deps/boost/concept_check )
add_subdirectory( deps/boost/config )
add_subdirectory( deps/boost/container_hash )
add_subdirectory( deps/boost/core )
add_subdirectory( deps/boost/move )
add_subdirectory( deps/boost/preprocessor )
add_subdirectory( deps/boost/static_assert )
add_subdirectory( deps/boost/throw_exception )
add_subdirectory( deps/boost/type_index )
add_subdirectory( deps/boost/type_traits )
add_subdirectory( deps/boost/variant )

message( "00 CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}" )
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/deps" )
message( "01 CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}" )

add_subdirectory( deps/glm )

add_subdirectory( deps/googletest )


option(RAPIDJSON_BUILD_TESTS "Enable testing" OFF)
add_subdirectory( deps/rapidjson )

#add_library(lib1 lib1.cpp)
#set_property(TARGET lib1 PROPERTY POSITION_INDEPENDENT_CODE ON)
add_subdirectory( deps/spdlog )

add_subdirectory( libcul )
add_subdirectory( libculTests )