#cmake -DCMAKE_BUILD_TYPE=Debug
cmake_minimum_required(VERSION 3.0.0)

set( CMAKE_CXX_STANDARD 23 )

set( PROJECT_NAME_DYNAMIC cul_dynamic )
set( PROJECT_NAME_STATIC_IMPL cul-static-impl )
set( PROJECT_NAME_STATIC cul_static )

project(${PROJECT_NAME_DYNAMIC} LANGUAGES CXX)
project(${PROJECT_NAME_STATIC} LANGUAGES CXX)

set( CMAKE_ENABLE_EXPORTS true )
cmake_policy(SET CMP0069 NEW)

include_directories( SYSTEM ${CUL_ROOT_DIR}/deps/CPP-DateTime-library/src )
include_directories( SYSTEM ${CUL_ROOT_DIR}/deps/hash-library )
include_directories( SYSTEM ${CUL_ROOT_DIR}/deps/nativefiledialog-extended/src/include)
include_directories( SYSTEM ${CUL_ROOT_DIR}/deps/rapidjson/include )
include_directories( SYSTEM ${CUL_ROOT_DIR}/deps/sqlite-amalgamation-3340000 )
include_directories( SYSTEM ${CUL_ROOT_DIR}/deps/stb )
include_directories( SYSTEM ${CUL_ROOT_DIR}/deps/tiny-image/src )
include_directories( SYSTEM ${CUL_ROOT_DIR}/deps/tracy/public )

set_option(CUL_PROFILER_PIX "Enable profiling" 0)

if( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC" )
    message(STATUS "WARNING: building msvc version.")
    # warning level 4 and all warnings as errors
    add_compile_options( /Wall )
    #add_compile_options( /WX ) # error on warning.
    add_compile_options( /MP )
    add_compile_options( "/wd4266" )
    add_compile_options( "/wd4820" )
    add_compile_options( "/wd4710" )
    add_compile_options( "/wd4774" )
    add_compile_options( "/wd4996" ) # 'sprintf': This function or variable may be unsafe. Consider using sprintf_s instead. 
    add_compile_options( "/wd5045" )

    add_compile_options("$<$<CONFIG:RelWithDebInfo>:/Ot>")
    add_compile_options("$<$<CONFIG:RelWithDebInfo>:/Oi>")

    add_compile_options("$<$<CONFIG:Release>:/Ot>")
    add_compile_options("$<$<CONFIG:Release>:/Oi>")

    find_package( RapidJSON REQUIRED )
    if( RapidJSON_FOUND )
        include_directories( SYSTEM ${RapidJSON_INCLUDE_DIRS} )
    endif( RapidJSON_FOUND )
else()
    if(CMAKE_CXX_SIMULATE_ID MATCHES "MSVC")
        message(STATUS "WARNING: building clang-cl version.")
    else()
        message(STATUS "WARNING: building regular version.")
        # lots of warnings and all warnings as errors
        add_compile_options( -Wall -Wextra -Werror -Wno-unused-parameter )
        # -Wno-sized-deallocation
        add_compile_options( -Wno-unused-variable )
        add_definitions( -Wfatal-errors )
    endif()
endif()

find_package( glm REQUIRED )

set( ENV{GLM_INCLUDE_DIR} ${CUL_ROOT_DIR}/deps/glm )
set( ENV{GLM_INCLUDE_DIRS} ${CUL_ROOT_DIR}/deps/glm )
###################################################################

file( GLOB_RECURSE SOURCES inc/*.hpp src/*.hpp src/*.cpp )

source_group( TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES} )

add_library( ${PROJECT_NAME_DYNAMIC} SHARED ${SOURCES} )
add_library( ${PROJECT_NAME_STATIC} STATIC ${SOURCES} )

set( DEPENDENCIES
PUBLIC AdditionalDeps
PUBLIC boost_assert
PUBLIC boost_circular_buffer
PUBLIC boost_core
PUBLIC glm
PRIVATE spdlog
PRIVATE udp-discovery
PUBLIC zlibstatic
PUBLIC TracyClient
PRIVATE nfd
PUBLIC datetime
)

if (MSVC)
list(APPEND DEPENDENCIES PRIVATE boost_stacktrace_windbg_cached)
else()
list(APPEND DEPENDENCIES PRIVATE boost_stacktrace_basic)
endif()

set_property( TARGET ${PROJECT_NAME_DYNAMIC} PROPERTY "LINK_LIBRARY_DEPENDENCIES" true )
set_property( TARGET ${PROJECT_NAME_STATIC} PROPERTY "LINK_LIBRARY_DEPENDENCIES" true )

set_property( TARGET ${PROJECT_NAME_DYNAMIC} PROPERTY INTERPROCEDURAL_OPTIMIZATION_DEBUG false )
set_property( TARGET ${PROJECT_NAME_DYNAMIC} PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELWITHDEBINFO false )
set_property( TARGET ${PROJECT_NAME_DYNAMIC} PROPERTY INTERPROCEDURAL_OPTIMIZATION_MINSIZEREL true )
set_property( TARGET ${PROJECT_NAME_DYNAMIC} PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE true )
set_property( TARGET ${PROJECT_NAME_STATIC} PROPERTY INTERPROCEDURAL_OPTIMIZATION_DEBUG false )
set_property( TARGET ${PROJECT_NAME_STATIC} PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELWITHDEBINFO false )
set_property( TARGET ${PROJECT_NAME_STATIC} PROPERTY INTERPROCEDURAL_OPTIMIZATION_MINSIZEREL true )
set_property( TARGET ${PROJECT_NAME_STATIC} PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE true )

set_target_properties(${PROJECT_NAME_STATIC} PROPERTIES COMPILE_DEFINITIONS "")
target_compile_definitions(${PROJECT_NAME_STATIC} PRIVATE CUL_STATIC=1 )

if (MSVC)
    list(APPEND LIBS msvcmrtd )
    target_link_options(${PROJECT_NAME_DYNAMIC} PUBLIC "/INCREMENTAL:NO")
    target_link_options(${PROJECT_NAME_STATIC} PUBLIC "/INCREMENTAL:NO")
    target_link_libraries( ${PROJECT_NAME_DYNAMIC} ${DEPENDENCIES} )
    target_link_libraries( ${PROJECT_NAME_STATIC} ${DEPENDENCIES} )
else()
    target_link_libraries( ${PROJECT_NAME_DYNAMIC} ${DEPENDENCIES} stdc++fs )
    target_link_libraries( ${PROJECT_NAME_STATIC} ${DEPENDENCIES} stdc++fs )
endif()

if( MSVC )
else()
    if( NOT APPLE )
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    endif()
endif()

target_include_directories(${PROJECT_NAME_DYNAMIC} SYSTEM PUBLIC zlibstatic)
target_include_directories(${PROJECT_NAME_STATIC} SYSTEM PUBLIC zlibstatic)

target_include_directories(${PROJECT_NAME_DYNAMIC} PUBLIC inc)
target_include_directories(${PROJECT_NAME_DYNAMIC} PRIVATE src)

target_include_directories(${PROJECT_NAME_STATIC} PUBLIC inc)
target_include_directories(${PROJECT_NAME_STATIC} PRIVATE src)
