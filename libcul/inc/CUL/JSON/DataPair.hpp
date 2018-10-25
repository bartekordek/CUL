#pragma once

#include "CUL/JSON/INode.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( JSON )

class CULLib_API DataPair final:
    public INode
{
public:
    DataPair( void );
    DataPair( CnstMyStr& name, CnstMyStr& value );
    ~DataPair( void );

    CnstMyStr& getVal()const;
    void setVal( CnstMyStr& val );

    //INode
    const ElementType getType()const override;
    //INode

protected:
private:
    MyString m_value;

};

NAMESPACE_END( JSON )
NAMESPACE_END( CUL )