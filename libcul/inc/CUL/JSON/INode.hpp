#pragma once

#include "CUL/STL_IMPORTS/STD_memory.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/String/StringWrapper.hpp"


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
    explicit INode( const StringWr& name, INode* val );
    explicit INode( const StringWr& name, const ChildrenNodes& value );
    explicit INode( const StringWr& name, bool value );
    explicit INode( const StringWr& name, double value );
    explicit INode( const StringWr& name, float value );
    explicit INode( const StringWr& name, int value );
    explicit INode( const StringWr& name, long int value );
    explicit INode( const StringWr& name, const char* value );
    explicit INode( const StringWr& name, const StringWr& value );

    const StringWr& getName() const;
    void setName( const StringWr& name );
    bool operator==( const INode& rhv ) const;
    bool operator==( const StringWr& rhv ) const;

    void setValue( INode* val );
    void setValue( const ChildrenNodes& value );
    void setValue( bool value );
    void setValue( double value );
    void setValue( float value );
    void setValue( int value );
    void setValue( long int value );
    void setValue( const char* value );
    void setValue( const StringWr& value );

    ElementType getType() const;
    const INode* getObject() const;
    const ChildrenNodes& getArray() const;
    ChildrenNodes& getArray();
    bool getBool() const;
    double getDouble() const;
    float getFloat() const;
    int getInt() const;
    int64_t getInt64() const;
    const StringWr& getString() const;

    INode* findChild( const StringWr& name );

    ~INode();
protected:
private:
    // I am ready for being laugh at to use this, erm, data structure.
    StringWr m_name;
    ElementType m_type = ElementType::NONE;
    INode* m_node = nullptr;
    ChildrenNodes m_array;
    bool m_bool = false;
    double m_double = 0.0;
    float m_float = 0.0f;
    int m_int = 0;
    int64_t m_int64 = 1;
    StringWr m_string;

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
