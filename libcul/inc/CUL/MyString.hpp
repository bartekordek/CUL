#pragma once

#include "CUL/UselessMacros.hpp"
#include "CUL/CUL.hpp"
#include "CUL/STD_string.hpp"

#if _MSC_VER
#pragma warning( disable: 4244 )
#pragma warning( disable: 4251 )
#endif

NAMESPACE_BEGIN( CUL )
class CULLib_API MyString:
    public std::string
{
public:
    MyString();
    MyString( const char* inputString );
    MyString( const MyString& inputString );
    MyString( const std::string& inputString );
    virtual ~MyString();

    MyString& operator=( const char* someString );
    MyString& operator=( const std::string& someString );
    MyString& operator=( const MyString& someString );

    MyString& operator+=( const char* someString );
    MyString& operator+=( const std::string& someString );

    const bool contains( const MyString& inputString )const;
    const bool contains( const char* inputString )const;

    MyString& replace( const MyString& inWhat, const MyString& inFor );
    CnstStr toLower()const;
    static void toLowerS( std::string& inOutString );
    static void toUpperS( std::string& inOutString );
    CnstStr string()const;

protected:
private:
};

using CnstMyStr = const MyString;

NAMESPACE_END( CUL )

//CUL::MyString operator+( CUL::CnstMyStr& lhv, CUL::CnstMyStr& rhv );
//CUL::MyString operator+( const char* lhv, CUL::CnstMyStr& rhv );
//CUL::MyString operator+( const std::string& lhv, CUL::CnstMyStr& rhv );