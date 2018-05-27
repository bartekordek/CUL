#include "CUL/IArgumentsPair.hpp"
#include "ArgumentsPairConcrete.hpp"

using namespace CUL;

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
