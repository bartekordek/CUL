#include "CUL/JSON/INode.hpp"
#include "CUL/STL_IMPORTS/STD_algorithm.hpp"

using namespace CUL;
using namespace JSON;

INode::INode( CsStr& name ):
    m_name( name )
{
}

CsStr& INode::getName() const
{
    return m_name;
}

void INode::setName( CsStr& name )
{
    m_name = name;
}

const bool INode::operator==( const INode& rhv ) const
{
    if( this != &rhv )
    {
        if( m_name != rhv.m_name )
        {
            return false;
        }
    }
    return true;
}

const bool INode::operator==( CsStr& rhv ) const
{
    if( m_name == rhv )
    {
        return true;
    }
    return false;
}

const bool operator==( INode* lhv, CsStr& rhv )
{
    return lhv->operator==( rhv );
}

struct isChild
{
    String m_value;
    isChild( CsStr& val ): m_value( val ) {}

    const bool operator()( const NodePtr& nodePtr ) const
    {
        return nodePtr->operator==( m_value );
    }
};


const INode* INode::getChild( CsStr& childName ) const
{
    auto it = std::find_if(
        m_children.begin(),
        m_children.end(),
        isChild( childName ) );
    if( it != m_children.end() )
    {
        return *it;
    }

    return nullptr;
}

void INode::addChild( INode* node )
{
    m_children.push_back( node );
}


const ChildrenNodes& INode::getChildren() const
{
    return m_children;
}


