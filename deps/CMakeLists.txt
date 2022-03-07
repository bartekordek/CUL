#cmake -DCMAKE_BUILD_TYPE=Debug
cmake_minimum_required(VERSION 3.0.0)

project(cul LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(EXEC AdditionalDeps)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CUL_OUTPUT_DIR} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CUL_OUTPUT_DIR} )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CUL_OUTPUT_DIR} )

set( SQLITE3_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/sqlite-amalgamation-3340000 )

file(GLOB SQLITE_SOURCES ${SQLITE3_ROOT}/*.c)
file(GLOB SQLITE_HEADERS ${SQLITE3_ROOT}/*.h)

file(GLOB HASH_LIBRARY_SOURCES "hash-library/*.cpp")
file(GLOB HASH_LIBRARY_INCLUDES "hash-library/*.h")
file(GLOB STB_SOURCES "stb/*.h" "stb/*.c" "stb/deprecated/*.h" "stb/deprecated/*.c")
file(GLOB TINY_IMAGE_SOURCES "tiny-image/src/*.cpp" "tiny-image/src/*.h" )

set(SOURCES_ALL
${SQLITE_SOURCES}
${SQLITE_HEADERS}
${STB_SOURCES}
${TINY_IMAGE_SOURCES}
${HASH_LIBRARY_INCLUDES}
${HASH_LIBRARY_SOURCES})


message( "[Additional deps] SQLITE_HEADERS: ${SQLITE_HEADERS}" )

source_group( TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES_ALL} )

add_library(AdditionalDeps STATIC ${SOURCES_ALL})

set(INCLUDE_PATHS
${CMAKE_CURRENT_SOURCE_DIR}/stb
${CMAKE_CURRENT_SOURCE_DIR}/tiny-image/src/
${CMAKE_CURRENT_SOURCE_DIR}/sqlite-amalgamation-3340000/src
)

message( "[Additional deps] INCLUDE_PATHS: ${INCLUDE_PATHS}" )

set(HEADERS_PUBLIC
    stb/deprecated/rrsprintf.h
    stb/stb.h
    stb/stb_connected_components.h
    stb/stb_c_lexer.h
    stb/stb_divide.h
    stb/stb_ds.h
    stb/stb_dxt.h
    stb/stb_easy_font.h
    stb/stb_herringbone_wang_tile.h
    stb/stb_image.h
    stb/stb_image_resize.h
    stb/stb_image_write.h
    stb/stb_include.h
    stb/stb_leakcheck.h
    stb/stb_perlin.h
    stb/stb_rect_pack.h
    stb/stb_sprintf.h
    stb/stb_textedit.h
    stb/stb_tilemap_editor.h
    stb/stb_truetype.h
    stb/stb_voxel_render.h
    stb/stretchy_buffer.h
    tiny-image/src/tinyimage.h
    ${HASH_LIBRARY_INCLUDES}
    ${SQLITE_HEADERS}
)

if (MSVC)
    target_link_libraries( ${EXEC} )
else()
    target_link_libraries( ${EXEC} stdc++fs )
endif()

target_include_directories(${EXEC} PUBLIC ${INCLUDE_PATHS})
target_include_directories(${EXEC} PRIVATE src)

# Code is not my own, i don't wish to see external warnings.
if ( MSVC )
    target_compile_options(${EXEC} PRIVATE "/W0")
else()
    target_compile_options(${EXEC} PRIVATE "-w")
endif()