#pragma once

#include "CUL/CUL.hpp"
#include "CUL/String.hpp"

NAMESPACE_BEGIN( CUL )

class CULLib_API Name
{
public:
    explicit Name( const CUL::String& name = CUL::String("") );
    explicit Name( const Name& name );
    virtual ~Name();

    void setName( const CUL::String& name );
    const CUL::String& GetName()const;

    Name& operator=( const Name& name );

protected:
private:
    String mName;

};

NAMESPACE_END( CUL )