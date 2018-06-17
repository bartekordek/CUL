#pragma once

#include "CUL/IArgumentsPair.hpp"
#include "CUL/STD_vector.hpp"

namespace CUL
{
    enum class ArgsDefs: char
    {
        PROGRAM_NAME = 0
    };
#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4820 )
#endif
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
        int m_argc = 0;
        bool m_argumentsAreDummy = false;

    };
#ifdef _MSC_VER
#pragma warning( pop )
#endif
}
