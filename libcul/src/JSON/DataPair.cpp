#include "CUL/JSON/DataPair.hpp"

using namespace CUL;
using namespace JSON;

DataPair::DataPair( void )
{

}

DataPair::DataPair( CnstMyStr& name, CnstMyStr& value ):
    INode( name ),
    m_value( value )
{
}

DataPair::~DataPair( void )
{

}

CnstMyStr& DataPair::getVal() const
{
    return this->m_value;
}

void DataPair::setVal( CnstMyStr& val )
{
    this->m_value = val;
}

const ElementType DataPair::getType() const
{
    return ElementType::VALUE;
}