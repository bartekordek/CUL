#include "CUL/GenericUtils/IArgumentsPair.hpp"
#include "ArgumentsPairConcrete.hpp"

using namespace CUL;
using namespace GUTILS;

IArgumentsPair* IArgumentsPair::getConcrete()
{
    return new ArgumentsPairConcrete();
}

IArgumentsPair::IArgumentsPair()
{
}

IArgumentsPair::~IArgumentsPair()
{
}