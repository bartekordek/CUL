#include "CUL/JSON/Array.hpp"

using namespace CUL;
using namespace JSON;

Array::Array( void )
{
}

Array::Array( CnstMyStr& name ):
    INode( name )
{
}

Array::~Array( void )
{
}

const ElementType Array::getType() const
{
    return ElementType::ARRAY;
}

void Array::addValue( INode* node )
{
    INode::addChild( node );
}

INode* Array::getValue( CnstMyStr& valName )
{
    for( auto& val: INode::getChildren() )
    {
        if( val->getName() == valName )
        {
            return val;
        }
    }
    return nullptr;
}

const ChildrenNodes& Array::getAllValues()const
{
    return INode::getChildren();
}
