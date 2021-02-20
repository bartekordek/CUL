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

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CUL_OUTPUT_DIR} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CUL_OUTPUT_DIR} )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CUL_OUTPUT_DIR} )

message( "[cul test] CMAKE_ARCHIVE_OUTPUT_DIRECTORY: ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}" )
message( "[cul test] CMAKE_LIBRARY_OUTPUT_DIRECTORY: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}" )
message( "[cul test] CMAKE_RUNTIME_OUTPUT_DIRECTORY: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}" )

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

if (MSVC)
    CmakeToWindow( ${CUL_OUTPUT_DIR} CUL_OUTPUT_DIR_WINDOWS )
    CmakeToWindow( ${CUL_DEPS_PATH} CUL_DEPS_PATH_WINDOWS )
    CmakeToWindow( ${CUL_TESTS_RUN_DIR} CUL_TESTS_RUN_DIR_WINDOWS )
    CmakeToWindow( ${CMAKE_SOURCE_DIR}/${BUILD_ROOT_POSTFIX} OUTER_BUILD_ROOT )
    #message( "OUTER_BUILD_ROOT = ${OUTER_BUILD_ROOT}" )

    set( CopyCommand ${CUL_DEPS_PATH_WINDOWS}\\helpers\\CopyLibraryBinaryAndSymbolsRecursive.bat )
    add_custom_command(TARGET ${EXEC} POST_BUILD
        COMMAND ${CopyCommand} ${CUL_OUTPUT_DIR} ${CUL_TESTS_RUN_DIR_WINDOWS}
        COMMAND ${CopyCommand} ${CUL_DEPS_PATH}  ${CUL_TESTS_RUN_DIR_WINDOWS}
        COMMAND ${CopyCommand} ${OUTER_BUILD_ROOT} ${CUL_TESTS_RUN_DIR_WINDOWS}
    )
endif()