#cmake -DCMAKE_BUILD_TYPE=Debug
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

cmake_policy(SET CMP0069 NEW)

project(cul_main)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

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
set(CUL_OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

set( ENV{CUL_OUTPUT_DIR} ${CUL_OUTPUT_DIR} )
list( APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" )

message(STATUS "Binary dir: ${CMAKE_BINARY_DIR}")


include(cmake/ISPC.cmake)
setup_ispc(VERSION 1.25.3)

set( CUL_DEPS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/deps )
# Add sub directories
add_subdirectory( ${CUL_DEPS_PATH} )

add_subdirectory( ${CUL_DEPS_PATH}/boost/assert )
set_property(TARGET boost_assert PROPERTY FOLDER "deps/boost")

add_subdirectory( ${CUL_DEPS_PATH}/boost/circular_buffer )
set_property(TARGET boost_circular_buffer PROPERTY FOLDER "deps/boost")

add_subdirectory( ${CUL_DEPS_PATH}/boost/concept_check )
set_property(TARGET boost_concept_check PROPERTY FOLDER "deps/boost")

add_subdirectory( ${CUL_DEPS_PATH}/boost/config )
set_property(TARGET boost_config PROPERTY FOLDER "deps/boost")

add_subdirectory( ${CUL_DEPS_PATH}/boost/container_hash )
set_property(TARGET boost_container_hash PROPERTY FOLDER "deps/boost")

add_subdirectory( ${CUL_DEPS_PATH}/boost/core )
set_property(TARGET boost_core PROPERTY FOLDER "deps/boost")

add_subdirectory( ${CUL_DEPS_PATH}/boost/describe )
set_property(TARGET boost_describe PROPERTY FOLDER "deps/boost")

add_subdirectory( ${CUL_DEPS_PATH}/boost/move )
set_property(TARGET boost_move PROPERTY FOLDER "deps/boost")

add_subdirectory( ${CUL_DEPS_PATH}/boost/mp11 )
set_property(TARGET boost_mp11 PROPERTY FOLDER "deps/boost")

add_subdirectory( ${CUL_DEPS_PATH}/boost/predef )
set_property(TARGET boost_predef PROPERTY FOLDER "deps/boost")

add_subdirectory( ${CUL_DEPS_PATH}/boost/preprocessor )
set_property(TARGET boost_preprocessor PROPERTY FOLDER "deps/boost")

add_subdirectory( ${CUL_DEPS_PATH}/boost/stacktrace )
set_property(TARGET boost_stacktrace PROPERTY FOLDER "deps/boost")
set_property(TARGET boost_stacktrace_basic PROPERTY FOLDER "deps/boost")

add_subdirectory( ${CUL_DEPS_PATH}/boost/static_assert )
set_property(TARGET boost_static_assert PROPERTY FOLDER "deps/boost")

add_subdirectory( ${CUL_DEPS_PATH}/boost/throw_exception )
set_property(TARGET boost_throw_exception PROPERTY FOLDER "deps/boost")

add_subdirectory( ${CUL_DEPS_PATH}/boost/type_traits )
set_property(TARGET boost_type_traits PROPERTY FOLDER "deps/boost")

add_subdirectory( ${CUL_DEPS_PATH}/boost/winapi )
set_property(TARGET boost_winapi PROPERTY FOLDER "deps/boost")

set_property(TARGET boost_stacktrace_basic PROPERTY FOLDER "deps/boost")
set_property(TARGET boost_stacktrace_from_exception PROPERTY FOLDER "deps/boost")
set_property(TARGET boost_stacktrace_noop PROPERTY FOLDER "deps/boost")

if (MSVC)
    set_property(TARGET boost_stacktrace_windbg PROPERTY FOLDER "deps/boost")
    set_property(TARGET boost_stacktrace_windbg_cached PROPERTY FOLDER "deps/boost")
endif()

set(PATH_TO_APPLICATION_ICON ${CUL_DEPS_PATH}/CPP-DateTime-library/product.ico CACHE STRING "necessary value" FORCE)
# BUILD_SHARED_LIBS
set(BUILD_SHARED_LIBS FALSE CACHE BOOL "necessary value" FORCE)
# Disable unnecessary targets
set(BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory( ${CUL_DEPS_PATH}/CPP-DateTime-library )
set_property(TARGET datetime PROPERTY FOLDER "deps/DateTime")
set_property(TARGET uninstall PROPERTY FOLDER "deps/DateTime")

set(OPTION_BUILD_TESTS OFF CACHE BOOL "Disable testing" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(OPTION_SELF_CONTAINED ON CACHE BOOL "" FORCE)
set(OPTION_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# TODO!
#add_subdirectory( ${CUL_DEPS_PATH}/cppcheck )

set(GLM_TEST_ENABLE OFF CACHE BOOL "" FORCE)
set(GLM_ENABLE_EXPERIMENTAL OFF CACHE BOOL "" FORCE) # optional
add_subdirectory( ${CUL_DEPS_PATH}/glm )
set_property(TARGET glm PROPERTY FOLDER "deps")

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(gtest_build_samples OFF CACHE BOOL "" FORCE)
set(gtest_build_tests OFF CACHE BOOL "" FORCE)
add_subdirectory( ${CUL_DEPS_PATH}/googletest )
set_property(TARGET gmock PROPERTY FOLDER "deps/googletest")
set_property(TARGET gmock_main PROPERTY FOLDER "deps/googletest")
set_property(TARGET gtest PROPERTY FOLDER "deps/googletest")
set_property(TARGET gtest_main PROPERTY FOLDER "deps/googletest")

add_subdirectory( ${CUL_DEPS_PATH}/nativefiledialog-extended )
set_property(TARGET nfd PROPERTY FOLDER "deps")

set(RAPIDJSON_BUILD_DOC OFF CACHE BOOL "Enable testing." FORCE)
set(RAPIDJSON_BUILD_EXAMPLES OFF CACHE BOOL "Enable examples." FORCE)
set(RAPIDJSON_BUILD_TESTS OFF CACHE BOOL "Enable doc." FORCE)
add_subdirectory( ${CUL_DEPS_PATH}/rapidjson )
set_property(TARGET travis_doc PROPERTY FOLDER "deps/rapidjson")

if (MSVC)
    set(SPDLOG_WCHAR_SUPPORT ON CACHE BOOL "" FORCE)
    set(SPDLOG_WCHAR_FILENAMES ON CACHE BOOL "" FORCE)
endif()
set(SPDLOG_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_BENCH OFF CACHE BOOL "" FORCE)
set(SPDLOG_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory( ${CUL_DEPS_PATH}/spdlog )
set_property(TARGET spdlog PROPERTY FOLDER "deps")

set(BUILD_TOOL OFF CACHE BOOL "DISABLE TOOL" FORCE)
set(BUILD_TEST OFF CACHE BOOL "DISABLE TEST" FORCE)
add_subdirectory( ${CUL_DEPS_PATH}/udp-discovery-cpp )
set_property(TARGET udp-discovery PROPERTY FOLDER "deps")

set(BUILD_EXAMPLE OFF CACHE BOOL "DISABLE EXAMPLE" FORCE)
add_subdirectory( ${CUL_DEPS_PATH}/zlib )
set_property(TARGET example PROPERTY FOLDER "deps/zlib")
set_property(TARGET minigzip PROPERTY FOLDER "deps/zlib")
set_property(TARGET zlib PROPERTY FOLDER "deps/zlib")
set_property(TARGET zlibstatic PROPERTY FOLDER "deps/zlib")

set(PNG_TESTS OFF CACHE BOOL "Disable libpng tests" FORCE)
add_subdirectory( ${CUL_DEPS_PATH}/libpng )
set_property(TARGET png PROPERTY FOLDER "deps")
find_package( PNG REQUIRED )

option(ENABLE_TRACY "Enable Tracy profiler" OFF)
message(STATUS "ENABLE_TRACY=${ENABLE_TRACY}")
if(ENABLE_TRACY)
    add_subdirectory(${CUL_DEPS_PATH}/tracy)
endif()

add_subdirectory( libcul )
add_subdirectory( libculTests )
