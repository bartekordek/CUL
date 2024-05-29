#pragma once

#include "CUL/UselessMacros.hpp"
#include "CUL/STL_IMPORTS/STD_filesystem.hpp"
#include "CUL/String.hpp"

#ifdef CUL_WINDOWS
#include "CUL/IMPORT_stringapiset.hpp"
#endif

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( FS )

namespace FSCpp = std::filesystem;
using FsPath = std::filesystem::path;
using DirectoryIterator = std::filesystem::directory_iterator;

std::string ws2s( const std::wstring& wstr );
#ifdef CUL_WINDOWS
std::wstring s2ws( const std::string& str, unsigned int codePage = CP_ACP );
#else
std::wstring s2ws( const std::string& str, unsigned int codePage = 65001 );
#endif

NAMESPACE_END( FS )
NAMESPACE_END( CUL )