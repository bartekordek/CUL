#cmake -DCMAKE_BUILD_TYPE=Debug
cmake_minimum_required(VERSION 3.0.0)

set( CMAKE_CXX_STANDARD 17 )
set( EXEC cul )

project(${EXEC} LANGUAGES CXX)

if( MSVC )
    string(REPLACE "/INCREMENTAL" "" tempFlag ${CMAKE_EXE_LINKER_FLAGS_DEBUG})
    set( CMAKE_EXE_LINKER_FLAGS_DEBUG ${tempFlag} )
endif()


set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CUL_OUTPUT_DIR} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CUL_OUTPUT_DIR} )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CUL_OUTPUT_DIR} )
set( CMAKE_ENABLE_EXPORTS true )

include_directories( SYSTEM "../deps/stb" )
include_directories( SYSTEM "../deps/tiny-image/src" )

if( MSVC )
    # warning level 4 and all warnings as errors
    add_compile_options( /W4 /WX )
    add_compile_options( /MP )

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

add_library( ${EXEC}-static STATIC ${SOURCES} )
add_library( ${EXEC} SHARED ${SOURCES} )

set( DEPENDENCIES
AdditionalDeps
boost_assert
boost_circular_buffer
boost_core
spdlog
)


set_property( TARGET ${EXEC} PROPERTY "LINK_LIBRARY_DEPENDENCIES" true )
if (MSVC)
    list(APPEND LIBS msvcmrtd )
    target_link_libraries( ${EXEC}-static ${DEPENDENCIES} )
    target_link_libraries( ${EXEC} ${DEPENDENCIES} )
else()
    target_link_libraries( ${EXEC} ${DEPENDENCIES} stdc++fs )
    target_link_libraries( ${EXEC}-static ${DEPENDENCIES} )
endif()

add_dependencies( ${EXEC} ${DEPENDENCIES} )

IF(NOT APPLE AND NOT MSVC)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
ENDIF()

target_include_directories(${EXEC} PUBLIC inc)
target_include_directories(${EXEC} PRIVATE src)

# TODO: Do I need to copy it?
#if (MSVC)
#    set_target_properties(${EXEC} PROPERTIES LINK_FLAGS "/INCREMENTAL:NO")
#    CmakeToWindow( ${CUL_OUTPUT_DIR} CUL_OUTPUT_DIR_WINDOWS )
#    CmakeToWindow( ${CUL_DEPS_PATH} CUL_DEPS_PATH_WINDOWS )
#    CmakeToWindow( ${CUL_TESTS_RUN_DIR} CUL_TESTS_RUN_DIR_WINDOWS )
#    CmakeToWindow( ${CMAKE_SOURCE_DIR}/${BUILD_ROOT_POSTFIX} OUTER_BUILD_ROOT )
#    #message( "OUTER_BUILD_ROOT = ${OUTER_BUILD_ROOT}" )
#
#    set( CopyCommand ${CUL_DEPS_PATH_WINDOWS}\\helpers\\CopyLibraryBinaryAndSymbolsRecursive.bat )
#    add_custom_command(TARGET ${EXEC} POST_BUILD
#        COMMAND ${CopyCommand} ${CUL_OUTPUT_DIR} ${CUL_TESTS_RUN_DIR_WINDOWS}
#        COMMAND ${CopyCommand} ${CUL_DEPS_PATH}  ${CUL_TESTS_RUN_DIR_WINDOWS}
#        COMMAND ${CopyCommand} ${OUTER_BUILD_ROOT} ${CUL_TESTS_RUN_DIR_WINDOWS}
#    )
#endif()
