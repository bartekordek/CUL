#pragma once

#include "CUL/UselessMacros.hpp"
#include "CUL/CUL.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/MyString.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( JSON )

class CULLib_API INode;
using NodePtr = INode * ;//std::unique_ptr<INode>;
using ChildrenNodes = std::vector<NodePtr>;

class CULLib_API IParent
{
public:
    IParent( void ) = default;
    virtual ~IParent( void ) = default;

    virtual const ChildrenNodes& getChildren() const = 0;
    virtual const INode* getChild( CnstMyStr& childName ) const = 0;
    virtual void addChild( INode* node ) = 0;

protected:
private:
};

NAMESPACE_END( JSON )
NAMESPACE_END( CUL )