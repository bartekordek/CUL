#pragma once

#include "CUL/GenericUtils/IArgumentsList.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/String.hpp"

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
    public IArgumentsList
{
public:
    ArgumentsPairConcrete();
    ~ArgumentsPairConcrete();

protected:
private:
    void pushArg( const String& name, const String& value ) override;
    void setArgs( const int argc, char** argv ) override;
    int* getArgCount() override;
    char** getArgsVal() override;
    void createDummyArgs() override;
    void clearArgs();
    const String& getFlagValue( const String& flagName ) const override;

    ArgumentsVec m_argumentsPtrs;
    std::vector<NameValue> m_values;
    char* m_valBegining = nullptr;
    char** m_valBeginingTable = nullptr;
    int m_argc = 0;
    bool m_argumentsAreDummy = false;

private: // Deleted.
    ArgumentsPairConcrete( ArgumentsPairConcrete&& arg ) = delete;
    ArgumentsPairConcrete( const ArgumentsPairConcrete& value ) = delete;
    ArgumentsPairConcrete& operator=( const ArgumentsPairConcrete& rhv ) = delete;
    ArgumentsPairConcrete& operator=( ArgumentsPairConcrete&& rhv ) = delete;
};
#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( GUTILS )
NAMESPACE_END( CUL )
