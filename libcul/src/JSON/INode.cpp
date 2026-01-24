#include "CUL/JSON/INode.hpp"
#include "CUL/STL_IMPORTS/STD_algorithm.hpp"

using namespace CUL;
using namespace JSON;

INode::INode()
{
}

//INode::INode( const INode& arg ):
//    m_name( arg.m_name ),
//    m_type( arg.m_type )
//{
//    if( ElementType::OBJECT == m_type )
//    {
//        m_node = arg.m_node;
//    }
//    else if( ElementType::ARRAY == m_type )
//    {
//        m_array = arg.m_array;
//    }
//    else if( ElementType::BOOL == m_type )
//    {
//        m_bool = arg.m_bool;
//    }
//    else if( ElementType::DOUBLE == m_type )
//    {
//        m_double = arg.m_double;
//    }
//    else if( ElementType::FLOAT == m_type )
//    {
//        m_float = arg.m_float;
//    }
//    else if( ElementType::INT == m_type )
//    {
//        m_int = arg.m_int;
//    }
//    else if( ElementType::INT64 == m_type )
//    {
//        m_int64 = arg.m_int64;
//    }
//    else if( ElementType::STRING == m_type )
//    {
//        m_string = arg.m_string;
//    }
//}
//
//INode::INode( INode&& arg ):
//    m_name( std::move( arg.m_name ) ),
//    m_type( arg.m_type )
//{
//    if( ElementType::OBJECT == m_type )
//    {
//        m_node = std::move( arg.m_node );
//    }
//    else if( ElementType::ARRAY == m_type )
//    {
//        m_array = std::move( arg.m_array );
//    }
//    else if( ElementType::BOOL == m_type )
//    {
//        m_bool = arg.m_bool;
//    }
//    else if( ElementType::DOUBLE == m_type )
//    {
//        m_double = arg.m_double;
//    }
//    else if( ElementType::FLOAT == m_type )
//    {
//        m_float = arg.m_float;
//    }
//    else if( ElementType::INT == m_type )
//    {
//        m_int = arg.m_int;
//    }
//    else if( ElementType::INT64 == m_type )
//    {
//        m_int64 = arg.m_int64;
//    }
//    else if( ElementType::STRING == m_type )
//    {
//        m_string = std::move( arg.m_string );
//    }
//}
//
//INode& INode::operator=(
//    const INode& rhv
//    )
//{
//    if( this != &rhv )
//    {
//        m_type = rhv.m_type;
//        m_name = rhv.m_name;
//        if( ElementType::OBJECT == m_type )
//        {
//            m_node = rhv.m_node;
//        }
//        else if( ElementType::ARRAY == m_type )
//        {
//            m_array = rhv.m_array;
//        }
//        else if( ElementType::BOOL == m_type )
//        {
//            m_bool = rhv.m_bool;
//        }
//        else if( ElementType::DOUBLE == m_type )
//        {
//            m_double = rhv.m_double;
//        }
//        else if( ElementType::FLOAT == m_type )
//        {
//            m_float = rhv.m_float;
//        }
//        else if( ElementType::INT == m_type )
//        {
//            m_int = rhv.m_int;
//        }
//        else if( ElementType::INT64 == m_type )
//        {
//            m_int64 = rhv.m_int64;
//        }
//        else if( ElementType::STRING == m_type )
//        {
//            m_string = rhv.m_string;
//        }
//    }
//    return *this;
//}
//
//INode& INode::operator=( INode&& rhv )
//{
//    if( this != &rhv )
//    {
//        m_type = rhv.m_type;
//        m_name = std::move( rhv.m_name);
//        if( ElementType::OBJECT == m_type )
//        {
//            m_node = std::move( rhv.m_node );
//        }
//        else if( ElementType::ARRAY == m_type )
//        {
//            m_array = std::move( rhv.m_array );
//        }
//        else if( ElementType::BOOL == m_type )
//        {
//            m_bool = rhv.m_bool;
//        }
//        else if( ElementType::DOUBLE == m_type )
//        {
//            m_double = rhv.m_double;
//        }
//        else if( ElementType::FLOAT == m_type )
//        {
//            m_float = rhv.m_float;
//        }
//        else if( ElementType::INT == m_type )
//        {
//            m_int = rhv.m_int;
//        }
//        else if( ElementType::INT64 == m_type )
//        {
//            m_int64 = rhv.m_int64;
//        }
//        else if( ElementType::STRING == m_type )
//        {
//            m_string = std::move( rhv.m_string );
//        }
//    }
//    return *this;
//}

INode::INode( const String& name, INode* value ):
    m_name( name )
{
    setValue( value );
}

INode::INode( const String& name, const ChildrenNodes& value ):
    m_name( name )
{
    setValue( value );
}

INode::INode( const String& name, bool value ):
    m_name( name )
{
    setValue( value );
}

INode::INode( const String& name, double value ):
    m_name( name )
{
    setValue( value );
}

INode::INode( const String& name, float value ):
    m_name( name )
{
    setValue( value );
}

INode::INode( const String& name, int value ):
    m_name( name )
{
    setValue( value );
}

INode::INode( const String& name, long int value ):
    m_name( name )
{
    setValue( value );
}

INode::INode( const String& name, const char* value ):
    m_name( name )
{
    setValue( value );
}

INode::INode( const String& name, const String& value ):
    m_name( name )
{
    setValue( value );
}

const String& INode::getName() const
{
    return m_name;
}

void INode::setName( const String& name )
{
    m_name = name;
}

bool INode::operator==( const INode& rhv ) const
{
    if( this != &rhv )
    {
        if( !m_name.equals( rhv.m_name.getString() ) )
        {
            return false;
        }
    }
    return true;
}

bool INode::operator==( const String& rhv ) const
{
    if( m_name.equals( rhv.getString() ) )
    {
        return true;
    }
    return false;
}

void INode::setValue( INode* val )
{
    m_node = val;
    m_type = ElementType::OBJECT;
}

void INode::setValue( const ChildrenNodes& value )
{
    m_array = value;
    m_type = ElementType::ARRAY;
}

void INode::setValue( bool value )
{
    m_bool = value;
    m_type = ElementType::BOOL;
}

void INode::setValue( double value )
{
    m_double = value;
    m_type = ElementType::DOUBLE;
}

void INode::setValue( float value )
{
    m_float = value;
    m_type = ElementType::FLOAT;
}

void INode::setValue( int value )
{
    m_int = value;
    m_type = ElementType::INT;
}

void INode::setValue( long int value )
{
    m_int64 = value;
    m_type = ElementType::INT64;
}

void INode::setValue( const char* value )
{
    m_string = value;
    m_type = ElementType::STRING;
}

void INode::setValue( const String& value )
{
    m_string = value;
    m_type = ElementType::STRING;
}

ElementType INode::getType() const
{
    return m_type;
}

const INode* INode::getObject() const
{
    return m_node;
}

const ChildrenNodes& INode::getArray() const
{
    return m_array;
}

ChildrenNodes& INode::getArray()
{
    return m_array;
}

bool operator==( INode* lhv, const String& rhv )
{
    return lhv->operator==( rhv );
}

bool INode::getBool() const
{
    return m_bool;
}

double INode::getDouble() const
{
    return m_double;
}

float INode::getFloat() const
{
    return m_float;
}

int INode::getInt() const
{
    return m_int;
}

int64_t INode::getInt64() const
{
    return m_int64;
}

const String& INode::getString() const
{
    return m_string;
}

INode* INode::findChild( const String& name )
{
    if( ElementType::ARRAY == m_type )
    {
        auto it = std::find_if( m_array.begin(), m_array.end(),
                                [name]( INode* node )
                                {
                                    return node->getName().equals( name.getString() );
                                } );
        if( it != m_array.end() )
        {
            return *it;
        }
    }
    return nullptr;
}

INode::~INode()
{
    if( ElementType::OBJECT == m_type )
    {
        delete m_node;
        m_node = nullptr;
    }
    else if( ElementType::ARRAY == m_type )
    {
        for( const auto& child: m_array )
        {
            delete child;
        }
        m_array.clear();
    }
}
