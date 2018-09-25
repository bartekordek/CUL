#include "CUL/JSON/Object.hpp"

using namespace CUL;
using namespace JSON;

Object::Object( void )
{
}

Object::Object( CnstMyStr& name ):
    INode( name )
{
}

Object::~Object( void )
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