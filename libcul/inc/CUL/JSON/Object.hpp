#pragma once

#include "CUL/JSON/INode.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( JSON )

class CULLib_API Object final:
    public INode
{
public:
    Object( void );
    Object( CsStr& name );
    ~Object( void );

    //INode
    const ElementType getType()const override;
    //INode

protected:
private:

};

NAMESPACE_END( JSON )
NAMESPACE_END( CUL )
