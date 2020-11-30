#cmake -DCMAKE_BUILD_TYPE=Debug
cmake_minimum_required(VERSION 3.0.0)

project(cul_main)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Add sub directories
add_subdirectory( deps )
add_subdirectory( deps/boost/assert )
add_subdirectory( deps/boost/circular_buffer )
add_subdirectory( deps/boost/concept_check )
add_subdirectory( deps/boost/config )
add_subdirectory( deps/boost/container_hash )
add_subdirectory( deps/boost/core )
add_subdirectory( deps/boost/move )
add_subdirectory( deps/boost/preprocessor )
add_subdirectory( deps/boost/static_assert )
add_subdirectory( deps/boost/throw_exception )
add_subdirectory( deps/boost/type_index )
add_subdirectory( deps/boost/type_traits )
add_subdirectory( deps/boost/variant )
add_subdirectory( deps/googletest )


option(RAPIDJSON_BUILD_TESTS "Enable testing" OFF)
add_subdirectory( deps/rapidjson )

#add_library(lib1 lib1.cpp)
#set_property(TARGET lib1 PROPERTY POSITION_INDEPENDENT_CODE ON)
add_subdirectory( deps/spdlog )

add_subdirectory( libcul )
add_subdirectory( libculTests )
