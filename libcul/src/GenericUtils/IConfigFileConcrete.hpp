#pragma once

#include "CUL/GenericUtils/IConfigFile.hpp"
#include "CUL/GenericUtils/DumbPtr.hpp"
#include "CUL/STL_IMPORTS/STD_map.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( FS )
class IFile;
NAMESPACE_END( FS )
class CULInterface;
NAMESPACE_BEGIN( GUTILS )

class IConfigFileConcrete final:
    public IConfigFile
{
public:
    IConfigFileConcrete( const FS::Path& path, CULInterface* culInterface );

    void addValue( const StringWr& valueName, const StringWr& value );
    void reload() override;

    ~IConfigFileConcrete();

protected:
private:
    const StringWr getValue( const StringWr& valueFieldName ) const override;
    void getModificationTime( Time& out ) override;
    void loadPath();
    void clear();

    CULInterface* m_culInterface = nullptr;
    GUTILS::DumbPtr<FS::IFile> m_file;
    FS::Path m_path;
    std::map<std::string, std::string> m_values;
    StringWr m_empty;


    // Deleted:
    IConfigFileConcrete( const IConfigFileConcrete& val ) = delete;
    IConfigFileConcrete( IConfigFileConcrete&& val ) = delete;
    IConfigFileConcrete& operator=( const IConfigFileConcrete& rhv ) = delete;
    IConfigFileConcrete& operator=( IConfigFileConcrete&& rhv ) = delete;
};

NAMESPACE_END( GUTILS )
NAMESPACE_END( CUL )