#pragma once

#include "CUL/GenericUtils/IConfigFile.hpp"
#include "CUL/GenericUtils/DumbPtr.hpp"
#include "CUL/STL_IMPORTS/STD_map.hpp"

NAMESPACE_BEGIN( CUL )
class FS::IFile;
class CULInterface;
NAMESPACE_BEGIN( GUTILS )

class IConfigFileConcrete final:
    public IConfigFile
{
public:
    IConfigFileConcrete( const FS::Path& path, CULInterface* culInterface );

    void addValue( const String& valueName, const String& value );
    void reload() override;

    ~IConfigFileConcrete();

protected:
private:
    const String& getValue( const String& valueFieldName ) const override;
    TimeConcrete getModificationTime() override;
    void loadPath();
    void clear();

    CULInterface* m_culInterface = nullptr;
    GUTILS::DumbPtr<FS::IFile> m_file;
    FS::Path m_path;
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