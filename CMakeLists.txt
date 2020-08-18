cmake_minimum_required(VERSION 3.0.0)

project(culTests LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(EXEC culTests)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libcul)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libcul/inc)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/googletest)
include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/deps/googletest/googletest/include)


if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    #add_compile_options(-Wall -Wextra -pedantic -Werror)
    add_compile_options(-Wall -Wextra -pedantic -Werror)
    add_definitions(-Wfatal-errors)
endif()

include_directories(libculTests/src)
file( GLOB SOURCES libculTests/src/*.cpp )

add_executable(${EXEC} ${SOURCES})

#target_link_libraries(${EXEC} -L/home/user/libs/somelibpath/)
target_link_libraries(${EXEC} cul gtest gmock )

target_include_directories(culTests PRIVATE inc)
target_include_directories(culTests PRIVATE src)
