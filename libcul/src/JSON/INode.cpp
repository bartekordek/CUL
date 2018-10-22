#include "CUL/JSON/INode.hpp"
#include "CUL/STD_algorithm.hpp"

using namespace CUL;
using namespace JSON;

INode::INode( CnstMyStr& name ):
    m_name( name )
{
}

CnstMyStr& INode::getName() const
{
    return this->m_name;
}

void INode::setName( CnstMyStr& name )
{
    this->m_name = name;
}

const bool INode::operator==( const INode& rhv ) const
{
    if( this != &rhv )
    {
        if( this->m_name != rhv.m_name )
        {
            return false;
        }
    }
    return true;
}

const bool INode::operator==( CnstMyStr& rhv ) const
{
    if( this->m_name == rhv )
    {
        return true;
    }
    return false;
}

const bool operator==( INode* lhv, CnstMyStr& rhv )
{
    return lhv->operator==( rhv );
}

struct isChild
{
    MyString m_value;
    isChild( CnstMyStr& val ): m_value( val ) {}

    const bool operator()( const NodePtr& nodePtr )const
    {
        return nodePtr->operator==( m_value );
    }
};


const INode* INode::getChild( CnstMyStr& childName ) const
{
    auto it = std::find_if(
        this->m_children.begin(),
        this->m_children.end(),
        isChild( childName ) );
    if( it != this->m_children.end() )
    {
        return *it;
    }

    return nullptr;
}

void INode::addChild( INode* node )
{
    this->m_children.push_back( node );
}


const ChildrenNodes& INode::getChildren() const
{
    return this->m_children;
}


