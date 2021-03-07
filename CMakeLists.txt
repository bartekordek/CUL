#cmake -DCMAKE_BUILD_TYPE=Debug
cmake_minimum_required(VERSION 3.0.0)

project(cul_main)

set(default_build_type "Debug")
if(NOT CMAKE_BUILD_TYPE )
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
        STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

message( "CMAKE BUILD TYPE: ${CMAKE_BUILD_TYPE}" )

macro(CmakeToWindow InputPath OutputPath)
    string(REGEX REPLACE "/" "\\\\" ${OutputPath} "${InputPath}")
endmacro()

macro( add_sources_group SUBDIRS_LIST )
    foreach( dir ${SUBDIRS_LIST} )
        file( GLOB SOURCES ${dir}/*.h ${dir}/*.hpp ${dir}/*.c ${dir}/*.cpp )
        message( "Source group ${dir} for ${SOURCES}" )
        source_group( ${dir} FILES ${SOURCES} )
        list( APPEND SOURCE_FILES ${SOURCES} )
    endforeach( dir ${SUBDIRS_LIST} )
endmacro()

set( CMAKE_POSITION_INDEPENDENT_CODE ON )
set( CUL_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
set( CUL_TESTS_RUN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/runDir" )

set( ENV{CUL_ROOT_DIR} ${CUL_ROOT_DIR} )
set( ENV{CUL_DLL} ${CUL_TESTS_RUN_DIR} )

set( CUL_BUILD_ROOT ${CMAKE_SOURCE_DIR} )
message( "CUL_BUILD_ROOT: ${CUL_BUILD_ROOT}" )
if( MSVC )
    set( CUL_OUTPUT_DIR ${CUL_BUILD_ROOT}/Build-Windows )
else()
    set( CUL_OUTPUT_DIR ${CUL_BUILD_ROOT}/Build-Linux )
endif()

set( ENV{CUL_OUTPUT_DIR} ${CUL_OUTPUT_DIR} )
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules" )

set( CUL_DEPS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/deps )
# Add sub directories
add_subdirectory( ${CUL_DEPS_PATH} )
add_subdirectory( ${CUL_DEPS_PATH}/boost/assert )
add_subdirectory( ${CUL_DEPS_PATH}/boost/circular_buffer )
add_subdirectory( ${CUL_DEPS_PATH}/boost/concept_check )
add_subdirectory( ${CUL_DEPS_PATH}/boost/config )
add_subdirectory( ${CUL_DEPS_PATH}/boost/container_hash )
add_subdirectory( ${CUL_DEPS_PATH}/boost/core )
add_subdirectory( ${CUL_DEPS_PATH}/boost/move )
add_subdirectory( ${CUL_DEPS_PATH}/boost/preprocessor )
add_subdirectory( ${CUL_DEPS_PATH}/boost/static_assert )
add_subdirectory( ${CUL_DEPS_PATH}/boost/throw_exception )
add_subdirectory( ${CUL_DEPS_PATH}/boost/type_index )
add_subdirectory( ${CUL_DEPS_PATH}/boost/type_traits )
add_subdirectory( ${CUL_DEPS_PATH}/boost/variant )

#option( BUILD_TESTS "Disable testing" OFF )
#option( BUILD_JAVA "Disable java" OFF )
#option( BUILD_PERF_TESTS "Disable tests" OFF )
#option( BUILD_opencv_python2 "" OFF )
#option( BUILD_opencv_python3 "" OFF )
#option( BUILD_EXAMPLES "Disable examples" OFF )
#add_subdirectory( ${CUL_DEPS_PATH}/opencv )

add_subdirectory( ${CUL_DEPS_PATH}/glm )

set( gtest_force_shared_crt ON CACHE BOOL "" FORCE )
add_subdirectory( ${CUL_DEPS_PATH}/googletest )

option( RAPIDJSON_BUILD_TESTS "Enable testing." OFF )
option( RAPIDJSON_BUILD_EXAMPLES "Build examples." OFF )
add_subdirectory( ${CUL_DEPS_PATH}/rapidjson )

add_subdirectory( ${CUL_DEPS_PATH}/spdlog )
add_subdirectory( libcul )
add_subdirectory( libculTests )