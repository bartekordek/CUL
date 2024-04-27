#pragma once

#include "CUL/String.hpp"
#include "STL_IMPORTS/STD_cstdint.hpp"
#include "STL_IMPORTS/STD_string.hpp"

NAMESPACE_BEGIN( CUL )

class StringUTF final
{
public:
    CULLib_API explicit StringUTF();

    CULLib_API explicit StringUTF( const char* input );
    CULLib_API explicit StringUTF( const wchar_t* input );
    CULLib_API explicit StringUTF( const float input );
    CULLib_API explicit StringUTF( const std::uint32_t input );
    CULLib_API explicit StringUTF( const std::int32_t input );
    CULLib_API explicit StringUTF( const std::uint64_t input );
    CULLib_API explicit StringUTF( const std::int64_t input );
    CULLib_API explicit StringUTF( const String& input );

    CULLib_API StringUTF& operator=( const char* input );
    CULLib_API StringUTF& operator=( const wchar_t* input );
    CULLib_API StringUTF& operator=( const float input );
    CULLib_API StringUTF& operator=( const std::uint32_t input );
    CULLib_API StringUTF& operator=( const std::int32_t input );
    CULLib_API StringUTF& operator=( const std::uint64_t input );
    CULLib_API StringUTF& operator=( const std::int64_t input );
    CULLib_API StringUTF& operator=( const String& input );

    CULLib_API bool operator==( const StringUTF& rhv ) const;
    CULLib_API bool operator!=( const StringUTF& rhv ) const;

    CULLib_API StringUTF& operator+=( const StringUTF& rhv );
    CULLib_API StringUTF operator+( const StringUTF& rhv );

    CULLib_API void convertToHexData();
    CULLib_API void convertFromHexToString();
    CULLib_API void toLower();
    CULLib_API void toUpper();
    CULLib_API bool contains( const char* ) const;
    CULLib_API const char* cStr() const;

    CULLib_API ~StringUTF();

protected:
private:
    std::u32string m_value;
};

NAMESPACE_END( CUL )