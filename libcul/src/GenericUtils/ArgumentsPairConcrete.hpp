#pragma once

#include "CUL/GenericUtils/IArgumentsPair.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/MyString.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( GUTILS )

enum class ArgsDefs: char
{
    PROGRAM_NAME = 0
};
#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4820 )
#endif
class ArgumentsPairConcrete final:
    public IArgumentsPair
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

    std::vector<MyString> m_argumentsPtrs;
    char* m_valBegining = nullptr;
    char** m_valBeginingTable = nullptr;
    int m_argc = 0;
    bool m_argumentsAreDummy = false;

};
#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( GUTILS )
NAMESPACE_END( CUL )