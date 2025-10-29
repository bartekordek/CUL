#cmake -DCMAKE_BUILD_TYPE=Debug
cmake_minimum_required(VERSION 3.0.0)

project(cul LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(EXEC AdditionalDeps)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CUL_OUTPUT_DIR} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CUL_OUTPUT_DIR} )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CUL_OUTPUT_DIR} )

set( SQLITE3_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/sqlite-amalgamation-3340000 )

file(GLOB SQLITE_SOURCES ${SQLITE3_ROOT}/*.c)
file(GLOB SQLITE_HEADERS ${SQLITE3_ROOT}/*.h)

file(GLOB HASH_LIBRARY_SOURCES "hash-library/*.cpp")
# bartlomiej.kordek: Remove digest.cpp since this is a application source.
list(FILTER HASH_LIBRARY_SOURCES EXCLUDE REGEX ".*digest\\.cpp$")
file(GLOB HASH_LIBRARY_INCLUDES "hash-library/*.h")
file(GLOB STB_SOURCES "stb/*.h" "stb/*.c" "stb/deprecated/*.h" )
file(GLOB TINY_IMAGE_SOURCES "tiny-image/src/*.cpp" "tiny-image/src/*.h" )

list(APPEND JSONXX jsonxx/jsonxx.h)
list(APPEND JSONXX jsonxx/jsonxx.cc)

set(SOURCES_ALL
${SQLITE_SOURCES}
${SQLITE_HEADERS}
${STB_SOURCES}
${TINY_IMAGE_SOURCES}
${HASH_LIBRARY_INCLUDES}
${HASH_LIBRARY_SOURCES}
${JSONXX}
)

include_directories( SYSTEM ${CUL_ROOT_DIR}/deps/tracy/public )
message("DUPA: ${CUL_ROOT_DIR}")

source_group( TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES_ALL} )
add_library(AdditionalDeps STATIC ${SOURCES_ALL})

set(INCLUDE_PATHS
${CMAKE_CURRENT_SOURCE_DIR}/stb
${CMAKE_CURRENT_SOURCE_DIR}/tiny-image/src/
${CMAKE_CURRENT_SOURCE_DIR}/sqlite-amalgamation-3340000/src
${CMAKE_CURRENT_SOURCE_DIR}/jsonxx
)

message( "[Additional deps] INCLUDE_PATHS: ${INCLUDE_PATHS}" )

set(HEADERS_PUBLIC
    tiny-image/src/tinyimage.h
    ${HASH_LIBRARY_INCLUDES}
    ${SQLITE_HEADERS}
)

set(DEPENDENCIES PUBLIC TracyClient)

if (MSVC)
    target_link_libraries( ${EXEC} ${DEPENDENCIES} Ws2_32.Lib )
else()
    target_link_libraries( ${EXEC} ${DEPENDENCIES} stdc++fs dl)
endif()

target_include_directories(${EXEC} PUBLIC ${INCLUDE_PATHS})
target_include_directories(${EXEC} PRIVATE src)

# Code is not my own, i don't wish to see external warnings.
if ( MSVC )
    target_compile_options(${EXEC} PRIVATE "/W0")
else()
    target_compile_options(${EXEC} PRIVATE "-w")
endif()


#SQLITE_DEFAULT_CACHE_SIZE
#the default value is -2000, which translates into a maximum of
#  2048000 (  1.953125 MB) bytes per cache.
#268435456 (256.000000 MB)
target_compile_definitions(${EXEC} PUBLIC SQLITE_DEFAULT_CACHE_SIZE=-268435456 SQLITE_THREADSAFE=1)