#include "CUL/Named.hpp"

using namespace CUL;

Name::Name( const String& name ):
    mName( name )
{
}

Name::Name( const Name& name ):
    mName( name.mName )
{
}

Name::~Name()
{
}

void Name::setName( const String& name )
{
    mName = name;
}

const String& Name::GetName()const
{
    return mName;
}

Name& Name::operator=( const Name& name )
{
    if( this != &name )
    {
        mName = name.mName;
    }
    return *this;
}