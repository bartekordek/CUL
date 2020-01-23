#pragma once

#include "CUL/CUL.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( GUTILS )

class CULLib_API IArgumentsPair
{
public:
    IArgumentsPair();
    virtual ~IArgumentsPair();

    virtual int* getArgCount() = 0;
    virtual char** getArgsVal() = 0;
    virtual void setArgs( const int argc, char** argv ) = 0;
    virtual void createDummyArgs() = 0;

    static IArgumentsPair* getConcrete();

protected:
private:
};

NAMESPACE_END( GUTILS )
NAMESPACE_END( CUL )