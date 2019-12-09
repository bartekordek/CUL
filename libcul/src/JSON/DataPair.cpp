#include "CUL/JSON/DataPair.hpp"

using namespace CUL;
using namespace JSON;

DataPair::DataPair( void )
{

}

DataPair::DataPair( CsStr& name, CsStr& value ):
    INode( name ),
    m_value( value )
{
}

DataPair::~DataPair()
{
}

CsStr& DataPair::getVal() const
{
    return m_value;
}

void DataPair::setVal( CsStr& val )
{
    m_value = val;
}

const ElementType DataPair::getType() const
{
    return ElementType::VALUE;
}