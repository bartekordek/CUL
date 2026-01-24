#include "CUL/ISerializable.hpp"

using namespace CUL;

CounterType ISerializable::s_spacesInTab = 4;

ISerializable::ISerializable()
{
}

StringWr ISerializable::serialize( CounterType tabsSize, const bool separator ) const
{
    StringWr tabs = getTab( tabsSize );
    StringWr result = tabs;
    result.append( "{\n" );
    const StringWr serialized = getSerializationContent( tabsSize + 1, separator );
    result.append( serialized.getValue() );

    if( separator )
    {
        result.append( tabs.getValue() );
        result.append( "},\n" );
    }
    else
    {
        result.append( tabs.getValue() );
        result.append( "}\n" );
    }

    return result;
}

StringWr ISerializable::getTab( CounterType tabSize )
{
    StringWr tabs;

    const CounterType spacesToAdd = s_spacesInTab * tabSize;
    for( CounterType i = 1; i <= spacesToAdd; ++i )
    {
        tabs += StringWr( " " );
    }

    return tabs;
}

ISerializable::~ISerializable()
{
}