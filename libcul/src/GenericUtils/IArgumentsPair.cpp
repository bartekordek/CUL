#include "CUL/GenericUtils/IArgumentsList.hpp"
#include "ArgumentsPairConcrete.hpp"

using namespace CUL;
using namespace GUTILS;

IArgumentsList* IArgumentsList::getConcrete()
{
    return new ArgumentsPairConcrete();
}

IArgumentsList::IArgumentsList()
{
}

IArgumentsList::~IArgumentsList()
{
}