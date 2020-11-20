#pragma once
#include "CUL/OSUtils/ISystemFonts.hpp"
#include "CUL/Filesystem/FileFactory.hpp"
#include "CUL/GenericUtils/DumbPtr.hpp"
#include "CUL/Log/ILogger.hpp"

#include "CUL/STL_IMPORTS/STD_memory.hpp"


NAMESPACE_BEGIN( CUL )

template <typename Type>
using UniquePtr = std::unique_ptr<Type>;


NAMESPACE_BEGIN( FS )
class FSApi;
NAMESPACE_END( FS )

NAMESPACE_BEGIN( GUTILS )
class IConfigFile;
NAMESPACE_END( GUTILS )

class CULLib_API CULInterface final
{
public:

    static CULInterface* createInstance();
    LOG::ILogger* getLogger();
    FS::FSApi* getFS();
    OSUtils::ISystemFonts* getSystemFonts();
    FS::FileFactory* getFF();
    GUTILS::IConfigFile* createConfigFile( const FS::Path& path );

    ~CULInterface();
protected:
private:
    explicit CULInterface();
    explicit CULInterface( const CULInterface& arg ) = delete;
    explicit CULInterface( CULInterface&& arg ) = delete;
    CULInterface& operator=( const CULInterface& arg ) = delete;
    CULInterface& operator=( CULInterface&& arg ) = delete;

    CUL::LOG::ILogger* m_logger = nullptr;
    GUTILS::DumbPtr<FS::FileFactory> m_fileFactory;
    GUTILS::DumbPtr<FS::FSApi> m_fsApi;
    GUTILS::DumbPtr<OSUtils::ISystemFonts> m_sysFonts;
};

NAMESPACE_END( CUL )