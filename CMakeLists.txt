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

message( "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}" )
message( "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}" )
file( RELATIVE_PATH CUL_RENEGATE_DIR ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR} )
message( "CUL_RENEGATE_DIR: ${CUL_RENEGATE_DIR}" )

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
list( APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules" )

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CUL_OUTPUT_DIR} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CUL_OUTPUT_DIR} )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CUL_OUTPUT_DIR} )

set( CUL_DEPS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/deps )
# Add sub directories
add_subdirectory( ${CUL_DEPS_PATH} )
add_subdirectory( ${CUL_DEPS_PATH}/boost/array )
add_subdirectory( ${CUL_DEPS_PATH}/boost/assert )
add_subdirectory( ${CUL_DEPS_PATH}/boost/circular_buffer )
add_subdirectory( ${CUL_DEPS_PATH}/boost/concept_check )
add_subdirectory( ${CUL_DEPS_PATH}/boost/config )
add_subdirectory( ${CUL_DEPS_PATH}/boost/container_hash )
add_subdirectory( ${CUL_DEPS_PATH}/boost/core )
add_subdirectory( ${CUL_DEPS_PATH}/boost/detail )
add_subdirectory( ${CUL_DEPS_PATH}/boost/integer )
add_subdirectory( ${CUL_DEPS_PATH}/boost/move )
add_subdirectory( ${CUL_DEPS_PATH}/boost/predef )
add_subdirectory( ${CUL_DEPS_PATH}/boost/preprocessor )
add_subdirectory( ${CUL_DEPS_PATH}/boost/stacktrace )
add_subdirectory( ${CUL_DEPS_PATH}/boost/static_assert )
add_subdirectory( ${CUL_DEPS_PATH}/boost/throw_exception )
add_subdirectory( ${CUL_DEPS_PATH}/boost/type_index )
add_subdirectory( ${CUL_DEPS_PATH}/boost/type_traits )
add_subdirectory( ${CUL_DEPS_PATH}/boost/variant )
add_subdirectory( ${CUL_DEPS_PATH}/boost/winapi )

set(OPTION_BUILD_TESTS OFF CACHE BOOL "Disable testing" FORCE)
set(cppfs_BINARY_DIR ${CUL_OUTPUT_DIR})
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(OPTION_SELF_CONTAINED ON CACHE BOOL "" FORCE)
set(OPTION_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory( ${CUL_DEPS_PATH}/cppfs )

# TODO!
#add_subdirectory( ${CUL_DEPS_PATH}/cppcheck )

add_subdirectory( ${CUL_DEPS_PATH}/glm )

set( gtest_force_shared_crt ON CACHE BOOL "" FORCE )
add_subdirectory( ${CUL_DEPS_PATH}/googletest )

option( RAPIDJSON_BUILD_TESTS "Enable testing." OFF )
option( RAPIDJSON_BUILD_EXAMPLES "Build examples." OFF )
add_subdirectory( ${CUL_DEPS_PATH}/rapidjson )

add_subdirectory( ${CUL_DEPS_PATH}/spdlog )

set(BUILD_EXAMPLE OFF CACHE BOOL "DISABLE EXAMPLE" FORCE)
set(BUILD_TOOL OFF CACHE BOOL "DISABLE TOOL" FORCE)
set(BUILD_TEST OFF CACHE BOOL "DISABLE TEST" FORCE)
add_subdirectory( ${CUL_DEPS_PATH}/udp-discovery-cpp )
add_subdirectory( ${CUL_DEPS_PATH}/zlib )
set( PNG_TESTS OFF )
add_subdirectory( ${CUL_DEPS_PATH}/libpng )
find_package( PNG REQUIRED )

set(TRACY_CALLSTACK ON CACHE BOOL "[tracy ]Enable callstack." FORCE)
set(TRACY_ON_DEMAND ON CACHE BOOL "[tracy ]Enable on demand." FORCE)
add_subdirectory( ${CUL_DEPS_PATH}/tracy )

add_subdirectory( libcul )
add_subdirectory( libculTests )
