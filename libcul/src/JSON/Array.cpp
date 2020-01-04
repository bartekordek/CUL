#include "CUL/JSON/Array.hpp"

using namespace CUL;
using namespace JSON;

Array::Array()
{
}

Array::Array( CsStr& name ):
    INode( name )
{
}

Array::~Array()
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

INode* Array::getValue( CsStr& valName )
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

const ChildrenNodes& Array::getAllValues() const
{
    return INode::getChildren();
}