#cmake -DCMAKE_BUILD_TYPE=Debug
cmake_minimum_required(VERSION 3.0.0)

project(cul LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(EXEC AdditionalDeps)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

message( "[cul deps] Setting CUL_OUTPUT_DIR to: ${CUL_OUTPUT_DIR}" )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CUL_OUTPUT_DIR} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CUL_OUTPUT_DIR} )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CUL_OUTPUT_DIR} )

add_library(AdditionalDeps STATIC
    stb/deprecated/stb_image.c
    stb/stb_vorbis.c
    tiny-image/src/tinyimage.cpp
)

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
)

if (MSVC)
    target_link_libraries( ${EXEC} )
else()
    target_link_libraries( ${EXEC} stdc++fs )
endif()

target_include_directories(${EXEC} PUBLIC stb tiny-image/src/)
target_include_directories(${EXEC} PRIVATE src)

if ( CMAKE_COMPILER_IS_GNUCC )
    target_compile_options(${EXEC} PRIVATE "-w")
endif()

if ( MSVC )
    target_compile_options(${EXEC} PRIVATE "/W3")
endif()