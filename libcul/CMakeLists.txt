#cmake -DCMAKE_BUILD_TYPE=Debug
cmake_minimum_required(VERSION 3.0.0)

set( CMAKE_CXX_STANDARD 17 )
set( EXEC cul )

project(${EXEC} LANGUAGES CXX)

if( MSVC )
    string(REPLACE "/INCREMENTAL" "" tempFlag ${CMAKE_EXE_LINKER_FLAGS_DEBUG})
    set( CMAKE_EXE_LINKER_FLAGS_DEBUG ${tempFlag} )
endif()


set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CUL_OUTPUT_DIR} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CUL_OUTPUT_DIR} )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CUL_OUTPUT_DIR} )

include_directories( SYSTEM "../deps/stb" )
include_directories( SYSTEM "../deps/tiny-image/src" )

if( MSVC )
    # warning level 4 and all warnings as errors
    add_compile_options( /W4 /WX )
    add_compile_options( /MP )
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")

    find_package( RapidJSON REQUIRED )
    if( RapidJSON_FOUND )
        include_directories( SYSTEM ${RapidJSON_INCLUDE_DIRS} )
    endif( RapidJSON_FOUND )
else()
    # lots of warnings and all warnings as errors
    add_compile_options( -Wall -Wextra -pedantic -Werror )
    add_definitions( -Wfatal-errors )
endif()

find_package( glm REQUIRED )

set( ENV{GLM_INCLUDE_DIR} ${CUL_ROOT_DIR}/deps/glm )
set( ENV{GLM_INCLUDE_DIRS} ${CUL_ROOT_DIR}/deps/glm )
###################################################################

file( GLOB HEADERS_PUBLIC inc/*.hpp )
message( "[cul lib] HEADERS_PUBLIC: ${HEADERS_PUBLIC}" )
file( GLOB HEADERS_PUBLIC inc/*/*.hpp )
message( "[cul lib] HEADERS_PUBLIC: ${HEADERS_PUBLIC}" )
file( GLOB HEADERS_PUBLIC inc/*/*/*.hpp )
message( "[cul lib] HEADERS_PUBLIC: ${HEADERS_PUBLIC}" )

add_library( ${EXEC} SHARED
${HEADERS_PUBLIC}
src/ThreadUtilityDummy.cpp
src/CSVFile.cpp
src/GenericUtils/IConfigFileConcrete.cpp
src/GenericUtils/IOnChange.cpp
src/GenericUtils/IConfigFile.cpp
src/GenericUtils/ArgumentsPairConcrete.cpp
src/GenericUtils/IArgumentsPair.cpp
src/GenericUtils/ConsoleUtilities.cpp
src/Named.cpp
src/IHttpRequest.cpp
src/JSON/INode.cpp
src/JSON/DataValue.cpp
src/JSON/JSONFileConcrete.cpp
src/JSON/INodeImpl.cpp
src/JSON/IJSONFile.cpp
src/Video/IFPSObservable.cpp
src/Video/IFPSCounter.cpp
src/Video/FPSCounterConcrete.cpp
src/ThreadUtils.cpp
src/String/String.cpp
src/Quaternion.cpp
src/Log/LoggerSimpleStandardOutput.cpp
src/Log/ILogContainer.cpp
src/Log/ILogger.cpp
src/IPivot.cpp
src/Math/Axis.cpp
src/Math/Angle.cpp
src/Math/TriangleRectangularSimple2D.cpp
src/Math/Math.cpp
src/CULInterface.cpp
src/Graphics/ImageLoaderSTB.cpp
src/Graphics/ImageLoaderBMP.cpp
src/Graphics/ITexture.cpp
src/Graphics/Position3DDMutexedImpl.cpp
src/Graphics/ImageLoaderTiny.cpp
src/Graphics/Size3DDMutexed.cpp
src/Graphics/IImageLoader.cpp
src/Graphics/ImageConcrete.cpp
src/Graphics/IImage.cpp
src/Graphics/Position3DDMutexed.cpp
src/Graphics/IObject.cpp
src/Graphics/ImageLoaderConcrete.cpp
src/Graphics/Size3DDMutexedImpl.cpp
src/Graphics/IPosition3DD.cpp
src/ThreadUtilityWindows.cpp
src/ITimer.cpp
src/TimeConcrete.cpp
src/ITime.cpp
src/ICSVFile.cpp
src/Color.cpp
src/FileCompileTest.cpp
src/ISerializable.cpp
src/OSUtils/ISystemFonts.cpp
src/OSUtils/SystemFontsWindows.cpp
src/IName.cpp
src/SimpleAssert.cpp
src/TimerChrono.cpp
src/Filesystem/FileRegularImpl.cpp
src/Filesystem/FSUtils.cpp
src/Filesystem/Path.cpp
src/Filesystem/IFile.cpp
src/Filesystem/FS.cpp
src/Filesystem/Directory.cpp
src/Filesystem/FileFactory.cpp
)

set( DEPENDENCIES
AdditionalDeps
boost_assert
boost_circular_buffer
boost_core
spdlog
)


if (MSVC)
    target_link_libraries( ${EXEC} ${DEPENDENCIES} )
else()
    target_link_libraries( ${EXEC} ${DEPENDENCIES} stdc++fs )
endif()

target_include_directories(${EXEC} PUBLIC inc)
target_include_directories(${EXEC} PRIVATE src)

if (MSVC)
    set_target_properties(${EXEC} PROPERTIES LINK_FLAGS "/INCREMENTAL:NO")
endif()

if (MSVC)
    CmakeToWindow( "${CUL_TESTS_RUN_DIR}" CUL_TESTS_RUN_DIR_WINDOWS )
    CmakeToWindow( "${CUL_OUTPUT_DIR}/${CMAKE_BUILD_TYPE}/*.dll" CUL_DLLS )
    CmakeToWindow( "${CUL_OUTPUT_DIR}/${CMAKE_BUILD_TYPE}/*.pdb" CUL_PDBS )

    add_custom_command(TARGET ${EXEC} POST_BUILD
        COMMAND "xcopy" "${CUL_DLLS}" "${CUL_TESTS_RUN_DIR_WINDOWS}" "/y" "/s" "/f"
        COMMAND "xcopy" "${CUL_PDBS}" "${CUL_TESTS_RUN_DIR_WINDOWS}" "/y" "/s" "/f" )
endif()