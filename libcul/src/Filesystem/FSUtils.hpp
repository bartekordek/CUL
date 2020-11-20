#pragma once

#include "CUL/UselessMacros.hpp"
#include "CUL/STL_IMPORTS/STD_filesystem.hpp"
#include "CUL/String.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( FS )

#ifdef FILESYSTEM_IS_EXPERIMENTAL
namespace FSCpp = std::experimental::filesystem;
using FSCpp = std::experimental::filesystem;
using FsPath = std::experimental::filesystem::path;
using DirectoryIterator = std::experimental::filesystem::directory_iterator;
#else
namespace FSCpp = std::filesystem;
using FsPath = std::filesystem::path;
using DirectoryIterator = std::filesystem::directory_iterator;
#endif

CUL::String ws2s( const std::wstring& wstr );

NAMESPACE_END( FS )
NAMESPACE_END( CUL )