#pragma once

#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/String/String.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( GUTILS )

struct NameValue
{
    String name;
    String value;
};

class CULLib_API IArgumentsList
{
public:
    using ArgumentsVec = std::vector<String>;

    IArgumentsList();
    virtual ~IArgumentsList();

    virtual int* getArgCount() = 0;
    virtual char** getArgsVal() = 0;
    virtual void setArgs( const int argc, char** argv ) = 0;
    virtual void createDummyArgs() = 0;
    virtual const String& getFlagValue( const String& flagName ) const = 0;
    virtual void pushArg( const String& name, const String& value ) = 0;

    static IArgumentsList* getConcrete();

protected:
private:
};

NAMESPACE_END( GUTILS )
NAMESPACE_END( CUL )