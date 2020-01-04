#pragma once

#include "CUL/JSON/INode.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( JSON )

class CULLib_API DataPair final:
    public INode
{
public:
    DataPair();
    DataPair( CsStr& name, CsStr& value );
    ~DataPair();

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