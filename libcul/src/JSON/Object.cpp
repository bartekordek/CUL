#include "CUL/JSON/Object.hpp"

using namespace CUL;
using namespace JSON;

Object::Object()
{
}

Object::Object( CsStr& name ):
    INode( name )
{
}

Object::~Object()
{
}

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4100 )
#endif

#ifdef _MSC_VER
#pragma warning( pop )
#endif
const ElementType Object::getType() const
{
    return ElementType::OBJECT;
}