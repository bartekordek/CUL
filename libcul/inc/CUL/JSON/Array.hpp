#pragma once

#include "CUL/JSON/DataPair.hpp"
#include "CUL/STL_IMPORTS/STD_map.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( JSON )

class CULLib_API Array final:
    public INode
{
public:
    Array();
    Array( CsStr& name );
    ~Array();

    const ElementType getType() const override;
    void addValue( INode* node );
    INode* getValue( CsStr& valName );
    const ChildrenNodes& getAllValues() const;

protected:
private:
};

NAMESPACE_END( JSON )
NAMESPACE_END( CUL )