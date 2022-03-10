#pragma once
#include "CUL/Filesystem/FileFactory.hpp"
#include "CUL/GenericUtils/DumbPtr.hpp"
#include "CUL/IThreadUtil.hpp"
#include "CUL/Log/ILogger.hpp"
#include "CUL/OSUtils/ISystemFonts.hpp"
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

NAMESPACE_BEGIN( Graphics )
class IImageLoader;
NAMESPACE_END( Graphics )

class CULLib_API CULInterface final
{
public:
    static CULInterface* createInstance( const FS::Path& configFile = "" );

    OSUtils::ISystemFonts* getSystemFonts();

    LOG::ILogger* getLogger();
    FS::FSApi* getFS();
    FS::FileFactory* getFF();
    Graphics::IImageLoader* getImageLoader();
    IThreadUtil* getThreadUtil();

    GUTILS::IConfigFile* loadConfigFile( const FS::Path& path );

    ~CULInterface();

protected:
private:
    explicit CULInterface( const FS::Path& configFile = "" );
    void initialize();
    explicit CULInterface( const CULInterface& arg ) = delete;
    explicit CULInterface( CULInterface&& arg ) = delete;
    CULInterface& operator=( const CULInterface& arg ) = delete;
    CULInterface& operator=( CULInterface&& arg ) = delete;

    FS::Path m_configFilePath;
    CUL::GUTILS::IConfigFile* m_configFile = nullptr;
    CUL::LOG::ILogger* m_logger = nullptr;
    GUTILS::DumbPtr<FS::FileFactory> m_fileFactory;
    std::unique_ptr<FS::FSApi> m_fsApi;
    GUTILS::DumbPtr<OSUtils::ISystemFonts> m_sysFonts;
    // GUTILS::DumbPtr<Graphics::IImageLoader> m_imageLoader;
    std::unique_ptr<Graphics::IImageLoader> m_imageLoader;
    GUTILS::DumbPtr<IThreadUtil> m_threadUtil;
};

NAMESPACE_END( CUL )
