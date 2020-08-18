#pragma once

#include "CUL/JSON/INode.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( JSON )

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4820 )
#endif


class INodeImpl final
{
public:
    INodeImpl();

    CsStr& getName() const;
    void setName( CsStr& name );

    void setValue( INode* val );
    void setValue( const ChildrenNodes& value );
    void setValue( Cbool value );
    void setValue( Cdouble value );
    void setValue( Cfloat value );
    void setValue( Cint value );
    void setValue( Cint64 value );
    void setValue( const String& value );

    ElementType getType() const;
    const INode* getObject() const;
    const ChildrenNodes& getArray() const;
    ChildrenNodes& getArray();
    bool getBool() const;
    double getDouble() const;
    float getFloat() const;
    int getInt() const;
    unsigned int long getInt64() const;
    const String& getString() const;

    ~INodeImpl();
protected:
private:
    // I am ready for being laught at to use this, erm, data structure.
    String m_name;
    ElementType m_type = ElementType::NONE;
    INode* m_node = nullptr;
    ChildrenNodes m_array;
    bool m_bool = false;
    double m_double = 0.0;
    float m_float = 0.0f;
    int m_int = 0;
    int64_t m_int64 = 1;
    String m_string;

// Deleted:
    INodeImpl( const INodeImpl& rhv ) = delete;
    INodeImpl( INodeImpl&& rhv ) = delete;
    INodeImpl& operator=( const INodeImpl& rhv ) = delete;
    INodeImpl& operator=( INodeImpl&& rhv ) = delete;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( JSON )
NAMESPACE_END( CUL )