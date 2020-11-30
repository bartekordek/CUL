#include "CUL/CULInterface.hpp"
#include "CUL/Log/ILogContainer.hpp"
#include "GenericUtils/IConfigFileConcrete.hpp"
#include "CUL/Graphics/IImageLoader.hpp"
#include "CUL/Filesystem/FileFactory.hpp"
#include "CUL/Filesystem/FS.hpp"

using namespace CUL;

CULInterface* CULInterface::createInstance( const FS::Path& configFile )
{
    auto instance = new CULInterface( configFile );
    instance->initialize();
    return instance;
}

CULInterface::CULInterface( const FS::Path& configFilePath ):
    m_configFilePath( configFilePath )
{
   
}

void CULInterface::initialize()
{
    m_fileFactory = new FS::FileFactory( this );
    m_fsApi = new FS::FSApi( m_fileFactory.get(), this );

    m_configFile = loadConfigFile( m_configFilePath );
    m_imageLoader.reset( Graphics::IImageLoader::createConcrete( m_configFile ) );

    m_logger = LOG::LOG_CONTAINER::getLogger();
    m_logger->log( "Initialized logger." );



    m_sysFonts = OSUtils::ISystemFonts::createConcrete( m_fsApi, m_logger );
}

CUL::LOG::ILogger* CULInterface::getLogger()
{
    return m_logger;
}

FS::FSApi* CULInterface::getFS()
{
    return m_fsApi;
}

OSUtils::ISystemFonts* CULInterface::getSystemFonts()
{
    return m_sysFonts;
}

FS::FileFactory* CULInterface::getFF()
{
    return m_fileFactory;
}

Graphics::IImageLoader* CULInterface::getImageLoader()
{
    return m_imageLoader.get();
}

GUTILS::IConfigFile* CULInterface::loadConfigFile( const FS::Path& path )
{
    return new GUTILS::IConfigFileConcrete( path, this );
}

CULInterface::~CULInterface()
{
    LOG::LOG_CONTAINER::destroyLogger();
    m_logger = nullptr;
}