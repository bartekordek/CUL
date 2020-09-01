#include "JSON/INodeImpl.hpp"
#include "CUL/STL_IMPORTS/STD_typeinfo.hpp"

using namespace CUL;
using namespace JSON;

INodeImpl::INodeImpl()
{
}

CsStr& INodeImpl::getName() const
{
    return m_name;
}

void INodeImpl::setName( CsStr& name )
{
    m_name = name;
}

void INodeImpl::setValue( INode* val )
{
    m_node = val;
    m_type = ElementType::OBJECT;
}

void INodeImpl::setValue( const ChildrenNodes& value )
{
    m_array = value;
    m_type = ElementType::ARRAY;
}

void INodeImpl::setValue( Cbool value )
{
    m_bool = value;
    m_type = ElementType::BOOL;
}

void INodeImpl::setValue( Cdouble value )
{
    m_double = value;
    m_type = ElementType::DOUBLE;
}

void INodeImpl::setValue( Cfloat value )
{
    m_float = value;
    m_type = ElementType::FLOAT;
}

void INodeImpl::setValue( Cint value )
{
    m_int = value;
    m_type = ElementType::INT;
}

void INodeImpl::setValue( Cint64 value )
{
    m_int64 = value;
    m_type = ElementType::INT64;
}

void INodeImpl::setValue( const String& value )
{
    m_string = value;
    m_type = ElementType::STRING;
}

ElementType INodeImpl::getType() const
{
    return m_type;
}

const INode* INodeImpl::getObject() const
{
    return nullptr;
}

const ChildrenNodes& INodeImpl::getArray() const
{
    return m_array;
}

ChildrenNodes& INodeImpl::getArray()
{
    return m_array;
}

bool INodeImpl::getBool() const
{
    return m_bool;
}

double INodeImpl::getDouble() const
{
    return m_double;
}

float INodeImpl::getFloat() const
{
    return m_float;
}

int INodeImpl::getInt() const
{
    return m_int;
}

int64_t INodeImpl::getInt64() const
{
    return m_int64;
}

const String& INodeImpl::getString() const
{
    return m_string;
}

INodeImpl::~INodeImpl()
{
}