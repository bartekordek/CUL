#pragma once

#include "CUL/IArgumentsPair.hpp"
#include <string>
#include <vector>

namespace CUL
{
    enum class ArgsDefs: char
    {
        PROGRAM_NAME = 0
    };

    class ArgumentsPairConcrete final: public IArgumentsPair
    {
    public:
        ArgumentsPairConcrete();
        ~ArgumentsPairConcrete();

        void setArgs( const int argc, char** argv ) override;
        int* getArgCount() override;
        char** getArgsVal() override;
        void createDummyArgs() override;

    protected:
    private:
        void clearArgs();

        std::vector<char*> m_argumentsPtrs;
        bool m_argumentsAreDummy = false;
        int m_argc = 0;
    };
}