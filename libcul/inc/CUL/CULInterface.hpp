#pragma once

#include "CUL/GenericUtils/DumbPtr.hpp"
#include "CUL/Log/ILogger.hpp"
#include "CUL/OSUtils/ISystemFonts.hpp"

#include "CUL/STL_IMPORTS/STD_memory.hpp"

NAMESPACE_BEGIN( CUL )

template <typename Type>
using UniquePtr = std::unique_ptr<Type>;

NAMESPACE_BEGIN( FS )
class FSApi;
class FileFactory;
NAMESPACE_END( FS )

NAMESPACE_BEGIN( GUTILS )
class IConfigFile;
NAMESPACE_END( GUTILS )

NAMESPACE_BEGIN( Graphics )
class IImageLoader;
NAMESPACE_END( Graphics )

NAMESPACE_BEGIN( GUTILS )
class ConsoleUtilities;
NAMESPACE_END( GUTILS )

class ThreadUtils;

class CULLib_API CULInterface final
{
public:
    static CULInterface* getInstance( const FS::Path& configFile = "" );



    OSUtils::ISystemFonts* getSystemFonts();

    LOG::ILogger* getLogger();
    FS::FSApi* getFS();
    FS::FileFactory* getFF();
    Graphics::IImageLoader* getImageLoader();
    GUTILS::ConsoleUtilities* getConsoleUtils();
    ThreadUtils& getThreadUtils();

    GUTILS::IConfigFile* loadConfigFile( const FS::Path& path );
    GUTILS::IConfigFile* getConfig() const;

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
    GUTILS::IConfigFile* m_configFile = nullptr;
    CUL::LOG::ILogger* m_logger = nullptr;
    FS::FileFactory* m_fileFactory = nullptr;
    std::unique_ptr<FS::FSApi> m_fsApi;
    OSUtils::ISystemFonts* m_sysFonts = nullptr;
    // GUTILS::DumbPtr<Graphics::IImageLoader> m_imageLoader;
    std::unique_ptr<Graphics::IImageLoader> m_imageLoader;
    std::unique_ptr<GUTILS::ConsoleUtilities> m_args;
    ThreadUtils* m_threadUtils = nullptr;

    static CULInterface* s_instance;
};

NAMESPACE_END( CUL )