#cmake -DCMAKE_BUILD_TYPE=Debug
cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 17)
set(EXEC culTests)
project(${EXEC} LANGUAGES CXX)

if (MSVC)
    add_compile_options(/W4 /WX)
    add_compile_options( /MP )
    set( gtest_force_shared_crt ON CACHE BOOL "" FORCE )
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
    add_definitions(-Wfatal-errors)
endif()

message( "[cul test] OUTPUT LIB PATH: ${CUL_OUTPUT_DIR}" )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CUL_OUTPUT_DIR} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CUL_OUTPUT_DIR} )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CUL_OUTPUT_DIR} )

message( "[cul test] Searchng for cul..." )
find_package( cul REQUIRED )
if( cul_FOUND )
    message( "[cul test] cul found:" )
    message( "[cul test] inc: ${cul_INCLUDE_DIR}" )
    message( "[cul test] lib: ${cul_LIBRARY}" )
endif( cul_FOUND )

message( "[cul test] Searchng for cul... done." )

include_directories(src)
file( GLOB SOURCES src/*.cpp )

add_executable(${EXEC} ${SOURCES})

if (MSVC)
    set_target_properties(
        ${EXEC}
        PROPERTIES
            OUTPUT_NAME ${EXEC}
            SUFFIX ".exe"
    )
else()
    set_target_properties(
        ${EXEC}
        PROPERTIES
            OUTPUT_NAME ${EXEC}
            SUFFIX ".bin"
    )
endif()

target_link_libraries(${EXEC} cul gtest gmock AdditionalDeps )

target_include_directories(${EXEC} PRIVATE inc)
target_include_directories(${EXEC} PRIVATE src)

if (MSVC)
    set_target_properties( ${EXEC} PROPERTIES LINK_FLAGS "/INCREMENTAL:NO" )
    message( "[cul test] Setting cul tests run dir to: ${CUL_TESTS_RUN_DIR}" )
    set_target_properties( ${EXEC} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CUL_TESTS_RUN_DIR}" )
    set_target_properties( ${EXEC} PROPERTIES VS_DEBUGGER_COMMAND_ARGUMENTS  "--gtest_break_on_failure" )
endif()