#pragma once

#include "CUL/UselessMacros.hpp"
#include "CUL/STL_IMPORTS/STD_filesystem.hpp"
#include "CUL/MyString.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( FS )

#ifdef FILESYSTEM_IS_EXPERIMENTAL
using FsPath = std::experimental::filesystem::path;
using DirectoryIterator = std::experimental::filesystem::directory_iterator;
#else
using FsPath = std::filesystem::path;
using DirectoryIterator = std::filesystem::directory_iterator;
#endif

CUL::MyString ws2s( const std::wstring& wstr );

NAMESPACE_END( FS )
NAMESPACE_END( CUL )