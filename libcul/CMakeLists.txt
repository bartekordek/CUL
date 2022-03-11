#cmake -DCMAKE_BUILD_TYPE=Debug
cmake_minimum_required(VERSION 3.0.0)

set( CMAKE_CXX_STANDARD 17 )
set( EXEC cul )

project(${EXEC} LANGUAGES CXX)

if( MSVC )
endif()

set( CMAKE_ENABLE_EXPORTS true )

include_directories( SYSTEM "../deps/stb" )
include_directories( SYSTEM "../deps/tiny-image/src" )
include_directories( SYSTEM "../deps/rapidjson/include" )
include_directories( SYSTEM "../deps/hash-library" )
include_directories( SYSTEM "../deps/DevIL/DevIL/include" )

if( MSVC )
    # warning level 4 and all warnings as errors
    add_compile_options( /Wall )
    #add_compile_options( /WX ) # error on warning.
    add_compile_options( /MP )
    add_compile_options( "/wd4266" )
    add_compile_options( "/wd4820" )
    add_compile_options( "/wd5045" )

    find_package( RapidJSON REQUIRED )
    if( RapidJSON_FOUND )
        include_directories( SYSTEM ${RapidJSON_INCLUDE_DIRS} )
    endif( RapidJSON_FOUND )
else()
    # lots of warnings and all warnings as errors
    add_compile_options( -Wall -Wextra -pedantic -Werror )
    add_definitions( -Wfatal-errors )
endif()

find_package( glm REQUIRED )

set( ENV{GLM_INCLUDE_DIR} ${CUL_ROOT_DIR}/deps/glm )
set( ENV{GLM_INCLUDE_DIRS} ${CUL_ROOT_DIR}/deps/glm )
###################################################################

file( GLOB_RECURSE SOURCES inc/*.hpp src/*.hpp src/*.cpp )

source_group( TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES} )

add_library( ${EXEC} SHARED ${SOURCES} )

set( DEPENDENCIES
AdditionalDeps
boost_assert
boost_circular_buffer
boost_core
cppfs
glm
spdlog
IL
ILU
)

set_property( TARGET ${EXEC} PROPERTY "LINK_LIBRARY_DEPENDENCIES" true )
if (MSVC)
    list(APPEND LIBS msvcmrtd )
    target_link_options(${EXEC} PUBLIC "/INCREMENTAL:NO")
    target_link_libraries( ${EXEC} ${DEPENDENCIES} )
else()
    target_link_libraries( ${EXEC} ${DEPENDENCIES} stdc++fs )
endif()

if( MSVC )
    foreach(DevIL_BINARY ${DevIL_BINARIES})
        message( "DevIL_BINARY: ${DevIL_BINARY}" )
        add_custom_command(TARGET ${EXEC} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${DevIL_BINARY} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE} )
    endforeach(DevIL_BINARY)
#CUL_OUTPUT_DIR

    set( CPPFSSOURCE ${CUL_OUTPUT_DIR}/deps/CUL/deps/cppfs/${CMAKE_BUILD_TYPE}/*.dll )
    set( CPPFSTARGET ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}/ )

    file(TO_NATIVE_PATH ${CPPFSSOURCE} CPPFSSOURCE)
    file(TO_NATIVE_PATH ${CPPFSTARGET} CPPFSTARGET)

    add_custom_command(TARGET ${EXEC} POST_BUILD COMMAND xcopy /Y ${CPPFSSOURCE} ${CPPFSTARGET} )
else()
    if( NOT APPLE )
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    endif()
endif()

target_include_directories(${EXEC} PUBLIC inc)
target_include_directories(${EXEC} PRIVATE src)