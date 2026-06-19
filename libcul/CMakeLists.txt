cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

cmake_policy(SET CMP0069 NEW)

set(CMAKE_CXX_STANDARD 23)

set(PROJECT_NAME_DYNAMIC cul_dynamic)
set(PROJECT_NAME_STATIC_IMPL cul-static-impl)
set(PROJECT_NAME_STATIC cul_static)

project(cul LANGUAGES CXX)

set(CMAKE_ENABLE_EXPORTS true)

include_directories(SYSTEM ${CUL_ROOT_DIR}/deps/CPP-DateTime-library/src)
include_directories(SYSTEM ${CUL_ROOT_DIR}/deps/hash-library)
include_directories(SYSTEM ${CUL_ROOT_DIR}/deps/nativefiledialog-extended/src/include)
include_directories(SYSTEM ${CUL_ROOT_DIR}/deps/rapidjson/include)
include_directories(SYSTEM ${CUL_ROOT_DIR}/deps/sqlite-amalgamation-3340000)
include_directories(SYSTEM ${CUL_ROOT_DIR}/deps/stb)
include_directories(SYSTEM ${CUL_ROOT_DIR}/deps/tiny-image/src)

if(ENABLE_TRACY)
    message("TRACY ENABLED.")
    include_directories(SYSTEM ${CUL_ROOT_DIR}/deps/tracy/public)
else()
    message("TRACY DISABLED.")
endif()

option(CUL_PROFILER_PIX "Enable profiling" 0)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    message(STATUS "WARNING: building msvc version.")

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

    find_package(RapidJSON REQUIRED)
    if(RapidJSON_FOUND)
        include_directories(SYSTEM ${RapidJSON_INCLUDE_DIRS})
    endif()
else()

    if(CMAKE_CXX_SIMULATE_ID MATCHES "MSVC")
        message(STATUS "WARNING: building clang-cl version.")
    else()
        message(STATUS "WARNING: building regular version.")

        add_compile_options(-Wall -Wextra -Werror -Wno-unused-parameter)
        add_compile_options(-Wno-unused-variable)
        add_definitions(-Wfatal-errors)

    endif()

endif()

find_package(glm REQUIRED)

set(ENV{GLM_INCLUDE_DIR} ${CUL_ROOT_DIR}/deps/glm)
set(ENV{GLM_INCLUDE_DIRS} ${CUL_ROOT_DIR}/deps/glm)

###################################################################

# SOURCES
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS inc/*.hpp src/*.hpp src/*.cpp)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

# ISPC SOURCES
file(GLOB_RECURSE SOURCES_ISPC CONFIGURE_DEPENDS src/*.ispc)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES_ISPC})

message("Found ISPC files: ${SOURCES_ISPC}")
message("ISPC compiler: ${ISPC_EXECUTABLE}")

###################################################################
# BUILD LIBS FIRST (IMPORTANT FIX)
###################################################################

add_library(${PROJECT_NAME_DYNAMIC} SHARED ${SOURCES})
add_library(${PROJECT_NAME_STATIC} STATIC ${SOURCES})

###################################################################
# ISPC injection AFTER targets exist (FIX #1)
###################################################################

set(ISPC_TARGETS ${PROJECT_NAME_DYNAMIC} ${PROJECT_NAME_STATIC})

foreach(TGT IN LISTS ISPC_TARGETS)
    add_ispc_sources(${TGT} SOURCES ${SOURCES_ISPC})

    # FIX #2: ensure generated headers are visible
    target_include_directories(${TGT} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
endforeach()

###################################################################

set(DEPENDENCIES
    PUBLIC AdditionalDeps
    PUBLIC boost_assert
    PUBLIC boost_circular_buffer
    PUBLIC boost_core
    PUBLIC glm
    PRIVATE spdlog
    PRIVATE udp-discovery
    PUBLIC zlibstatic
    PRIVATE nfd
    PUBLIC datetime
)

if(MSVC)
    list(APPEND DEPENDENCIES PRIVATE boost_stacktrace_windbg_cached)
else()
    list(APPEND DEPENDENCIES PRIVATE boost_stacktrace_basic)
endif()

set_property(TARGET ${PROJECT_NAME_DYNAMIC} PROPERTY LINK_LIBRARY_DEPENDENCIES true)
set_property(TARGET ${PROJECT_NAME_STATIC} PROPERTY LINK_LIBRARY_DEPENDENCIES true)

set_property( TARGET ${PROJECT_NAME_DYNAMIC} PROPERTY INTERPROCEDURAL_OPTIMIZATION_DEBUG false )
set_property( TARGET ${PROJECT_NAME_DYNAMIC} PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELWITHDEBINFO true )
set_property( TARGET ${PROJECT_NAME_DYNAMIC} PROPERTY INTERPROCEDURAL_OPTIMIZATION_MINSIZEREL true )
set_property( TARGET ${PROJECT_NAME_DYNAMIC} PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE true )
set_property( TARGET ${PROJECT_NAME_STATIC} PROPERTY INTERPROCEDURAL_OPTIMIZATION_DEBUG false )
set_property( TARGET ${PROJECT_NAME_STATIC} PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELWITHDEBINFO true )
set_property( TARGET ${PROJECT_NAME_STATIC} PROPERTY INTERPROCEDURAL_OPTIMIZATION_MINSIZEREL true )
set_property( TARGET ${PROJECT_NAME_STATIC} PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE true )


set_target_properties(${PROJECT_NAME_STATIC} PROPERTIES COMPILE_DEFINITIONS "")
target_compile_definitions(${PROJECT_NAME_STATIC} PRIVATE CUL_STATIC=1)
target_compile_definitions(${PROJECT_NAME_STATIC} PUBLIC GLM_ENABLE_EXPERIMENTAL=1)
target_compile_definitions(${PROJECT_NAME_DYNAMIC} PUBLIC GLM_ENABLE_EXPERIMENTAL=1)

if(ENABLE_TRACY)
    target_compile_definitions(
        ${PROJECT_NAME_DYNAMIC}
        PUBLIC
        TRACY_ENABLE
    )

    target_compile_definitions(
        ${PROJECT_NAME_STATIC}
        PUBLIC
        TRACY_ENABLE
    )
endif()

###################################################################
# LINKING
###################################################################

if(MSVC)
    target_link_options(${PROJECT_NAME_DYNAMIC} PUBLIC "/INCREMENTAL:NO")
    target_link_options(${PROJECT_NAME_STATIC} PUBLIC "/INCREMENTAL:NO")

    target_link_libraries(${PROJECT_NAME_DYNAMIC} ${DEPENDENCIES})
    target_link_libraries(${PROJECT_NAME_STATIC} ${DEPENDENCIES})
else()
    target_link_libraries(${PROJECT_NAME_DYNAMIC} ${DEPENDENCIES} stdc++fs)
    target_link_libraries(${PROJECT_NAME_STATIC} ${DEPENDENCIES} stdc++fs)
endif()

if(NOT MSVC AND NOT APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

if(ENABLE_TRACY)
    target_link_libraries(${PROJECT_NAME_DYNAMIC} PUBLIC TracyClient)
    target_link_libraries(${PROJECT_NAME_STATIC} PUBLIC TracyClient)
endif()

###################################################################

target_include_directories(${PROJECT_NAME_DYNAMIC} SYSTEM PUBLIC zlibstatic)
target_include_directories(${PROJECT_NAME_STATIC} SYSTEM PUBLIC zlibstatic)

target_include_directories(${PROJECT_NAME_DYNAMIC} PUBLIC inc)
target_include_directories(${PROJECT_NAME_DYNAMIC} PRIVATE src)

target_include_directories(${PROJECT_NAME_STATIC} PUBLIC inc)
target_include_directories(${PROJECT_NAME_STATIC} PRIVATE src)
