#pragma once
#include "CUL.hpp"
namespace CUL
{
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
}