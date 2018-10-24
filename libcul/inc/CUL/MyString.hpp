#pragma once

#include "CUL/CUL.hpp"
#include "CUL/STD_string.hpp"
#include "CUL/UselessMacros.hpp"

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
    explicit MyString( const std::string& inputString );
    virtual ~MyString();

    MyString& operator=( const char* someString );
    MyString& operator=( const MyString& someString );

    const bool Contains( const MyString& inputString )const;
    const bool Contains( const char* inputString )const;

    MyString& Replace( const MyString& inWhat, const MyString& inFor );
    CnstStr toLower()const;
    static void toLowerS( std::string& inOutString );
    static void toUpperS( std::string& inOutString );
    CnstStr string()const;

protected:
private:
};

MyString CULLib_API  operator+( const MyString& string1, const MyString& string2 );

NAMESPACE_END( CUL )