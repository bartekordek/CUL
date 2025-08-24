#cmake -DCMAKE_BUILD_TYPE=Debug

get_filename_component( basename ${CMAKE_CURRENT_SOURCE_DIR} NAME )

project( ${basename} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(EXEC_DYNAMIC ${PROJECT_NAME}_dynamic)
set(EXEC_STATIC ${PROJECT_NAME}_static)

message( "[cul test] Compiler: ${CMAKE_CXX_COMPILER_ID}" )
message( "[cul test] Simulate: ${CMAKE_CXX_SIMULATE_ID}" )

if (MSVC)
    add_compile_options()
    add_compile_options( /MP )
else()
    if(CMAKE_CXX_SIMULATE_ID MATCHES "MSVC")
    else()
        add_compile_options(-Wall -Wextra -pedantic)
    endif()
endif()

include_directories(src)
include_directories("${CUL_ROOT_DIR}/libcul/src")
file( GLOB_RECURSE SOURCES inc/*.hpp src/*.hpp src/*.cpp )
source_group( TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES} )

add_executable(${EXEC_DYNAMIC} ${SOURCES})
add_executable(${EXEC_STATIC} ${SOURCES})

if (MSVC)
    set_target_properties(
        ${EXEC_DYNAMIC}
        PROPERTIES
            OUTPUT_NAME ${EXEC_DYNAMIC}
            SUFFIX ".exe"
    )
    set_target_properties(
        ${EXEC_STATIC}
        PROPERTIES
            OUTPUT_NAME ${EXEC_STATIC}
            SUFFIX ".exe"
    )
else()
    set_target_properties(
        ${EXEC_DYNAMIC}
        PROPERTIES
            OUTPUT_NAME ${EXEC_DYNAMIC}
            SUFFIX ".bin"
    )
    set_target_properties(
        ${EXEC_STATIC}
        PROPERTIES
            OUTPUT_NAME ${EXEC_STATIC}
            SUFFIX ".bin"
    )
endif()

target_link_libraries(${EXEC_DYNAMIC} cul_dynamic gtest gmock )
target_link_libraries(${EXEC_STATIC} cul_static gtest gmock )

target_include_directories(${EXEC_DYNAMIC} PRIVATE inc)
target_include_directories(${EXEC_DYNAMIC} PRIVATE src)

target_include_directories(${EXEC_STATIC} PRIVATE inc)
target_include_directories(${EXEC_STATIC} PRIVATE src)

if (MSVC)
    set_target_properties( ${EXEC_DYNAMIC} PROPERTIES LINK_FLAGS "/INCREMENTAL:NO" )
    set_target_properties( ${EXEC_STATIC} PROPERTIES LINK_FLAGS "/INCREMENTAL:NO" )


    message( "[cul test] Setting cul tests run dir to: ${CUL_TESTS_RUN_DIR}" )
    set_target_properties( ${EXEC_DYNAMIC} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CUL_TESTS_RUN_DIR}" )
    set_target_properties( ${EXEC_STATIC} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CUL_TESTS_RUN_DIR}" )
    set_target_properties( ${EXEC_DYNAMIC} PROPERTIES VS_DEBUGGER_COMMAND_ARGUMENTS  "--gtest_break_on_failure" )
    set_target_properties( ${EXEC_STATIC} PROPERTIES VS_DEBUGGER_COMMAND_ARGUMENTS  "--gtest_break_on_failure" )

    if( ${CMAKE_BUILD_TYPE} MATCHES "Debug" )
        set( GTEST_BIN gtestd )
        set( GMOCK_BIN gmockd )
    else()
        set( GTEST_BIN gtest )
        set( GMOCK_BIN gmock )
    endif()

    set( GTEST_OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/bin/${CMAKE_BUILD_TYPE} )
endif()