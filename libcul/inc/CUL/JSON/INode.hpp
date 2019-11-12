#pragma once

#include "CUL/JSON/IParent.hpp"
#include "CUL/UselessMacros.hpp"
#include "CUL/STL_IMPORTS/STD_memory.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( JSON )

enum class ElementType: short
{
    NULLVAL = 0,
    OBJECT,
    ARRAY,
    VALUE
};

class CULLib_API INode:
    public IParent
{
public:
    INode( void ) = default;
    INode( CnstMyStr& name );
    virtual ~INode( void ) = default;

    CnstMyStr& getName() const;
    void setName( CnstMyStr& name );
    const bool operator==( const INode& rhv ) const;
    const bool operator==( CnstMyStr& rhv ) const;

    virtual const ElementType getType()const = 0;

    const ChildrenNodes& getChildren()const override;
    const INode* getChild( CnstMyStr& childName ) const override;
    void addChild( INode* node ) override;

protected:
private:
    MyString m_name;
    ChildrenNodes m_children;

};

NAMESPACE_END( JSON )
NAMESPACE_END( CUL )