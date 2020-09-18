#include "GenericUtils/IConfigFileConcrete.hpp"

using namespace CUL;
using namespace GUTILS;

IConfigFileConcrete::IConfigFileConcrete()
{

}

void IConfigFileConcrete::addValue( const String& valueName, const String& value )
{
    m_values[valueName] = value;
}

const String& IConfigFileConcrete::getValue( const String& valueFieldName ) const
{
    const auto it = m_values.find( valueFieldName );
    if( it != m_values.end() )
    {
        return m_values.at( valueFieldName );
    }

    return m_empty;
}

IConfigFileConcrete::~IConfigFileConcrete()
{

}