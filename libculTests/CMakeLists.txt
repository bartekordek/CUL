#cmake -DCMAKE_BUILD_TYPE=Debug
cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 17)
set(EXEC culTests)
project(${EXEC} LANGUAGES CXX)

if (MSVC)
    add_compile_options(/W4 /WX)
    add_compile_options( /MP )
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
    add_definitions(-Wfatal-errors)
endif()

find_package( cul REQUIRED )

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

    if( ${CMAKE_BUILD_TYPE} MATCHES "Debug" )
        set( GTEST_BIN gtestd )
        set( GMOCK_BIN gmockd )
    else()
        set( GTEST_BIN gtest )
        set( GMOCK_BIN gmock )
    endif()

    set( GTEST_OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/bin/${CMAKE_BUILD_TYPE} )

    add_custom_command(TARGET ${EXEC}
        POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${GTEST_OUTPUT_DIR}/${GTEST_BIN}.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${GTEST_OUTPUT_DIR}/${GTEST_BIN}.pdb ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}

            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${GTEST_OUTPUT_DIR}/${GMOCK_BIN}.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${GTEST_OUTPUT_DIR}/${GMOCK_BIN}.pdb ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}
            )

endif()