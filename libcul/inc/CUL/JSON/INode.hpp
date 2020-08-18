#pragma once

#include "CUL/STL_IMPORTS/STD_memory.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/String.hpp"
//#include "CUL/JSON/DataValue.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( JSON )
//
enum class ElementType: short
{
    NONE = 0,
    OBJECT,
    ARRAY,
    BOOL,
    DOUBLE,
    FLOAT,
    INT,
    INT64,
    STRING
};

class CULLib_API INode;
using NodePtr = std::unique_ptr<INode>;
using ChildrenNodes = std::vector<INode*>;

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4820 )
#endif

class INodeImpl;
class CULLib_API INode final
{
public:
    INode();
    explicit INode( const String& name, INode* val );
    explicit INode( const String& name, const ChildrenNodes& value );
    explicit INode( const String& name, Cbool value );
    explicit INode( const String& name, Cdouble value );
    explicit INode( const String& name, Cfloat value );
    explicit INode( const String& name, Cint value );
    explicit INode( const String& name, Cint64 value );
    explicit INode( const String& name, const char* value );
    explicit INode( const String& name, CsStr& value );

    CsStr& getName() const;
    void setName( CsStr& name );
    Cbool operator==( const INode& rhv ) const;
    Cbool operator==( CsStr& rhv ) const;

    void setValue( INode* val );
    void setValue( const ChildrenNodes& value );
    void setValue( Cbool value );
    void setValue( Cdouble value );
    void setValue( Cfloat value );
    void setValue( Cint value );
    void setValue( Cint64 value );
    void setValue( const char* value );
    void setValue( CsStr& value );

    const ElementType getType() const;
    const INode* getObject() const;
    const ChildrenNodes& getArray() const;
    ChildrenNodes& getArray();
    Cbool getBool() const;
    Cdouble getDouble() const;
    Cfloat getFloat() const;
    Cint getInt() const;
    Cint64 getInt64() const;
    CsStr& getString() const;

    INode* findChild( const String& name );

    ~INode();
protected:
private:
    // I am ready for being laugh at to use this, erm, data structure.
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

    INode( const INode& arg ) = delete;
    INode( INode&& arg ) = delete;

    INode& operator=( const INode& rhv ) = delete;
    INode& operator=( INode&& node ) = delete;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( JSON )
NAMESPACE_END( CUL )
