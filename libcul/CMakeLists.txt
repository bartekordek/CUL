#cmake -DCMAKE_BUILD_TYPE=Debug
cmake_minimum_required(VERSION 3.0.0)

project(cul LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(EXEC cul)

include_directories( SYSTEM "../deps/spdlog/include" )
include_directories( SYSTEM "../deps/boost/assert/include" )
include_directories( SYSTEM "../deps/boost/circular_buffer/include" )
include_directories( SYSTEM "../deps/boost/concept_check/include" )
include_directories( SYSTEM "../deps/boost/config/include" )
include_directories( SYSTEM "../deps/boost/container_hash/include" )
include_directories( SYSTEM "../deps/boost/core/include" )
include_directories( SYSTEM "../deps/boost/move/include" )
include_directories( SYSTEM "../deps/boost/preprocessor/include" )
include_directories( SYSTEM "../deps/boost/static_assert/include" )
include_directories( SYSTEM "../deps/boost/throw_exception/include" )
include_directories( SYSTEM "../deps/boost/type_index/include" )
include_directories( SYSTEM "../deps/boost/type_traits/include" )
include_directories( SYSTEM "../deps/boost/variant/include" )
include_directories( SYSTEM "../deps/tiny-image/src" )
include_directories( SYSTEM "../deps/stb" )

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../deps ${CMAKE_CURRENT_BINARY_DIR}/../deps)

if( MSVC )
    # warning level 4 and all warnings as errors
    add_compile_options( /W4 /WX )
else()
    # lots of warnings and all warnings as errors
    #add_compile_options(-Wall -Wextra -pedantic -Werror)
    add_compile_options( -Wall -Wextra -pedantic -Werror )
    add_definitions( -Wfatal-errors )
endif()

add_library( cul SHARED
    src/Color.cpp
    src/CSVFile.cpp
    src/FileCompileTest.cpp
    src/Filesystem/Directory.cpp
    src/Filesystem/FileFactory.cpp
    src/Filesystem/FileRegularImpl.cpp
    src/Filesystem/FS.cpp
    src/Filesystem/FSUtils.cpp
    src/Filesystem/IFile.cpp
    src/Filesystem/Path.cpp
    src/GenericUtils/ArgumentsPairConcrete.cpp
    src/GenericUtils/ConsoleUtilities.cpp
    src/GenericUtils/IArgumentsPair.cpp
    src/GenericUtils/IConfigFile.cpp
    src/GenericUtils/IConfigFileConcrete.cpp
    src/Graphics/IImage.cpp
    src/Graphics/IImageLoader.cpp
    src/Graphics/ImageConcrete.cpp
    src/Graphics/ImageLoaderBMP.cpp
    src/Graphics/ImageLoaderConcrete.cpp
    src/Graphics/ImageLoaderSTB.cpp
    src/Graphics/ImageLoaderTiny.cpp
    src/Graphics/IObject.cpp
    src/Graphics/IPosition3DD.cpp
    src/Graphics/ITexture.cpp
    src/Graphics/Position3DDMutexed.cpp
    src/Graphics/Position3DDMutexedImpl.cpp
    src/Graphics/Size3DDMutexed.cpp
    src/Graphics/Size3DDMutexedImpl.cpp
    src/ICSVFile.cpp
    src/IHttpRequest.cpp
    src/IName.cpp
    src/IPivot.cpp
    src/ITime.cpp
    src/ITimer.cpp
    src/JSON/DataValue.cpp
    src/JSON/INode.cpp
    src/JSON/INodeImpl.cpp
    src/JSON/JSONFileConcrete.cpp
    src/Log/ILogContainer.cpp
    src/Log/ILogger.cpp
    src/Log/LoggerSimpleStandardOutput.cpp
    src/Math/Axis.cpp
    src/Math/IAngle.cpp
    src/Math/Math.cpp
    src/Math/TriangleRectangularSimple2D.cpp
    src/Named.cpp
    src/OSUtils/ISystemFonts.cpp
    src/OSUtils/SystemFontsWindows.cpp
    src/Quaternion.cpp
    src/SimpleAssert.cpp
    src/String/String.cpp
    src/String/StringImpl.cpp
    src/ThreadUtilityDummy.cpp
    src/ThreadUtilityWindows.cpp
    src/ThreadUtils.cpp
    src/TimeConcrete.cpp
    src/TimerChrono.cpp
    src/Video/FPSCounterConcrete.cpp
    src/Video/IFPSCounter.cpp
    src/Video/IFPSObservable.cpp
)

#set_target_properties(cul PROPERTIES PUBLIC_HEADER
set( HEADERS_PUBLIC
    inc/CUL/CUL.hpp
    inc/CUL/Filesystem/Directory.hpp
    inc/CUL/Filesystem/FileFactory.hpp
    inc/CUL/Filesystem/FS.hpp
    inc/CUL/Filesystem/IFile.hpp
    inc/CUL/Filesystem/Path.hpp
    inc/CUL/GenericUtils/ConsoleUtilities.hpp
    inc/CUL/GenericUtils/Conversion.hpp
    inc/CUL/GenericUtils/DisableErros.hpp
    inc/CUL/GenericUtils/DumbPtr.hpp
    inc/CUL/GenericUtils/IArgumentsList.hpp
    inc/CUL/GenericUtils/IConfigFile.hpp
    inc/CUL/GenericUtils/ITask.hpp
    inc/CUL/GenericUtils/LckPrim.hpp
    inc/CUL/GenericUtils/SimpleAssert.hpp
    inc/CUL/Graphics/Color.hpp
    inc/CUL/Graphics/IImage.hpp
    inc/CUL/Graphics/IImageLoader.hpp
    inc/CUL/Graphics/IObject.hpp
    inc/CUL/Graphics/IObjectRegister.hpp
    inc/CUL/Graphics/IPosition3DD.hpp
    inc/CUL/Graphics/IRawImage.hpp
    inc/CUL/Graphics/ISize3DD.hpp
    inc/CUL/Graphics/ITexture.hpp
    inc/CUL/Graphics/Pos2D.hpp
    inc/CUL/Graphics/Pos3D.hpp
    inc/CUL/Graphics/Position3DDMutexed.hpp
    inc/CUL/Graphics/Rect2D.hpp
    inc/CUL/Graphics/SimplePos3D.hpp
    inc/CUL/Graphics/SimpleSize2D.hpp
    inc/CUL/Graphics/SimpleSize3D.hpp
    inc/CUL/Graphics/Size2D.hpp
    inc/CUL/Graphics/Size3DDMutexed.hpp
    inc/CUL/ICSVFile.hpp
    inc/CUL/IName.hpp
    inc/CUL/Iterator.hpp
    inc/CUL/ITime.hpp
    inc/CUL/ITimer.hpp
    inc/CUL/JSON/DataValue.hpp
    inc/CUL/JSON/IJSON.hpp
    inc/CUL/JSON/IJSONFile.hpp
    inc/CUL/JSON/INode.hpp
    inc/CUL/List/IList.hpp
    inc/CUL/Log/ILogContainer.hpp
    inc/CUL/Log/ILogger.hpp
    inc/CUL/Math/Angle.hpp
    inc/CUL/Math/Axis.hpp
    inc/CUL/Math/Epsilon.hpp
    inc/CUL/Math/IPivot.hpp
    inc/CUL/Math/IPivotObserver.hpp
    inc/CUL/Math/Math.hpp
    inc/CUL/Math/Matrix2D.hpp
    inc/CUL/Math/MultiPoint.hpp
    inc/CUL/Math/Point.hpp
    inc/CUL/Math/PosTable.hpp
    inc/CUL/Math/Quaternion.hpp
    inc/CUL/Math/RotationType.hpp
    inc/CUL/Math/SquareMatrix2D.hpp
    inc/CUL/Math/Triangle.hpp
    inc/CUL/Math/TriangleRectangularSimple2D.hpp
    inc/CUL/Math/Vector3D.hpp
    inc/CUL/Named.hpp
    inc/CUL/Network/IHttpRequest.hpp
    inc/CUL/OSUtils/ISystemFonts.hpp
    inc/CUL/STL_IMPORTS/STD_algorithm.hpp
    inc/CUL/STL_IMPORTS/STD_array.hpp
    inc/CUL/STL_IMPORTS/STD_atomic.hpp
    inc/CUL/STL_IMPORTS/STD_clocale.hpp
    inc/CUL/STL_IMPORTS/STD_cmath.hpp
    inc/CUL/STL_IMPORTS/STD_cstdint.hpp
    inc/CUL/STL_IMPORTS/STD_cstdlib.hpp
    inc/CUL/STL_IMPORTS/STD_cstring.hpp
    inc/CUL/STL_IMPORTS/STD_filesystem.hpp
    inc/CUL/STL_IMPORTS/STD_fstream.hpp
    inc/CUL/STL_IMPORTS/STD_functional.hpp
    inc/CUL/STL_IMPORTS/STD_iomanip.hpp
    inc/CUL/STL_IMPORTS/STD_iosfwd.hpp
    inc/CUL/STL_IMPORTS/STD_iostream.hpp
    inc/CUL/STL_IMPORTS/STD_map.hpp
    inc/CUL/STL_IMPORTS/STD_memory.hpp
    inc/CUL/STL_IMPORTS/STD_mutex.hpp
    inc/CUL/STL_IMPORTS/STD_queue.hpp
    inc/CUL/STL_IMPORTS/STD_set.hpp
    inc/CUL/STL_IMPORTS/STD_sstream.hpp
    inc/CUL/STL_IMPORTS/STD_stack.hpp
    inc/CUL/STL_IMPORTS/STD_stddef.hpp
    inc/CUL/STL_IMPORTS/STD_string.hpp
    inc/CUL/STL_IMPORTS/STD_thread.hpp
    inc/CUL/STL_IMPORTS/STD_typeinfo.hpp
    inc/CUL/STL_IMPORTS/STD_type_traits.hpp
    inc/CUL/STL_IMPORTS/STD_utility.hpp
    inc/CUL/STL_IMPORTS/STD_variant.hpp
    inc/CUL/STL_IMPORTS/STD_vector.hpp
    inc/CUL/String.hpp
    inc/CUL/ThreadUtils.hpp
    inc/CUL/ThreadWrap.hpp
    inc/CUL/UselessMacros.hpp
    inc/CUL/Video/IFPSCounter.hpp
    inc/CUL/Video/IFPSObservable.hpp
    inc/CUL/Windows/INCLUDE_dwrite.hpp
)

if( MSVC )
else()
endif()
target_link_libraries( ${EXEC} stdc++fs )

target_include_directories(${EXEC} PUBLIC inc)
target_include_directories(${EXEC} PRIVATE src)