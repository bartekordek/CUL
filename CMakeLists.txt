#cmake -DCMAKE_BUILD_TYPE=Debug
cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 17)
set(EXEC culTests)
project(${EXEC} LANGUAGES CXX)

add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/libcul )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/libcul/inc)

add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/deps/googletest )
include_directories( SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/deps/googletest/googletest/include )
# --gtest_break_on_failure?

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
    add_compile_options( /MP )
    set( gtest_force_shared_crt ON CACHE BOOL "" FORCE )

    set( OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../Build-Windows )
    message( "Setting CMAKE_ARCHIVE_OUTPUT_DIRECTORY to: ${OUTPUT_DIR}" )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR} )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR} )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR} )

else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
    add_definitions(-Wfatal-errors)
endif()

include_directories(libculTests/src)
file( GLOB SOURCES libculTests/src/*.cpp )

add_executable(${EXEC} ${SOURCES})

#target_link_libraries(${EXEC} -L/home/user/libs/somelibpath/)
target_link_libraries(${EXEC} cul gtest gmock AdditionalDeps )

target_include_directories(${EXEC} PRIVATE inc)
target_include_directories(${EXEC} PRIVATE src)

set_target_properties( ${EXEC} PROPERTIES LINK_FLAGS "/INCREMENTAL:NO" )
set_target_properties( ${EXEC} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(ProjectDir)..\\runDir" )
set_target_properties( ${EXEC} PROPERTIES VS_DEBUGGER_COMMAND_ARGUMENTS  "--gtest_break_on_failure" )