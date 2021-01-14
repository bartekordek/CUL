#cmake -DCMAKE_BUILD_TYPE=Debug
cmake_minimum_required(VERSION 3.0.0)

project(cul_main)

macro(CmakeToWindow InputPath OutputPath)
    string(REGEX REPLACE "/" "\\\\" ${OutputPath} "${InputPath}")
endmacro()

message( "[cul] CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}" )
message( "[cul] CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}" )
set( CMAKE_POSITION_INDEPENDENT_CODE ON )
set( CUL_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
set( CUL_TESTS_RUN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/runDir" )

set( ENV{CUL_ROOT_DIR} ${CUL_ROOT_DIR} )
set( ENV{CUL_DLL} ${CUL_TESTS_RUN_DIR} )

message( "[cul] CUL_ROOT_DIR: ${CUL_ROOT_DIR}" )
message( "[cul] CUL_TESTS_RUN_DIR: ${CUL_TESTS_RUN_DIR}" )

if( MSVC )
    set( CUL_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Build-Windows )
else()
    set( CUL_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Build-Linux )
endif()

set( ENV{CUL_OUTPUT_DIR} ${CUL_OUTPUT_DIR} )

message( "[cul] CMAKE_MODULE_PATH: [Before] ${CMAKE_MODULE_PATH}" )
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules" )
message( "[cul] CMAKE_MODULE_PATH: [After] ${CMAKE_MODULE_PATH}" )
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



add_subdirectory( deps/glm )
add_subdirectory( deps/googletest )


option(RAPIDJSON_BUILD_TESTS "Enable testing" OFF)
add_subdirectory( deps/rapidjson )

#add_library(lib1 lib1.cpp)
#set_property(TARGET lib1 PROPERTY POSITION_INDEPENDENT_CODE ON)
add_subdirectory( deps/spdlog )
add_subdirectory( libcul )
add_subdirectory( libculTests )