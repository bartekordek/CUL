#include "CUL/ISerializable.hpp"

using namespace CUL;

CounterType ISerializable::s_spacesInTab = 4;

ISerializable::ISerializable()
{
}

String ISerializable::serialize( CounterType tabsSize, const bool separator ) const
{
    String tabs = getTab( tabsSize );
    String result = tabs + "{\n";

    result += getSerializationContent( tabsSize + 1, separator );

    if( separator )
    {
        result = result + tabs + "},\n";
    }
    else
    {
        result = result + tabs + "}\n";
    }

    return result;
}

String ISerializable::getTab( CounterType tabSize )
{
    String tabs;

    const CounterType spacesToAdd = s_spacesInTab * tabSize;
    for( CounterType i = 1; i <= spacesToAdd; ++i )
    {
        tabs += String( " " );
    }

    return tabs;
}

ISerializable::~ISerializable()
{
}