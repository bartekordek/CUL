#pragma once

#include "CUL/JSON/INode.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( JSON )

class CULLib_API DataPair final:
    public INode
{
public:
    DataPair( void );
    DataPair( CsStr& name, CsStr& value );
    ~DataPair( void );

    CsStr& getVal() const;
    void setVal( CsStr& val );

    //INode
    const ElementType getType() const override;
    //INode

protected:
private:
    String m_value;

};

NAMESPACE_END( JSON )
NAMESPACE_END( CUL )