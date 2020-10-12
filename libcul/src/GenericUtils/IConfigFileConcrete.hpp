#pragma once

#include "CUL/GenericUtils/IConfigFile.hpp"
#include "CUL/STL_IMPORTS/STD_map.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( GUTILS )

class IConfigFileConcrete final:
    public IConfigFile
{
public:
    IConfigFileConcrete();

    void addValue( const String& valueName, const String& value );



    ~IConfigFileConcrete();

protected:
private:
    const String& getValue( const String& valueFieldName ) const override;

    std::map<String, String> m_values;
    String m_empty = "";


    // Deleted:
    IConfigFileConcrete( const IConfigFileConcrete& val ) = delete;
    IConfigFileConcrete( IConfigFileConcrete&& val ) = delete;
    IConfigFileConcrete& operator=( const IConfigFileConcrete& rhv ) = delete;
    IConfigFileConcrete& operator=( IConfigFileConcrete&& rhv ) = delete;
};

NAMESPACE_END( GUTILS )
NAMESPACE_END( CUL )