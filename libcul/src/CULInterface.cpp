#include "CUL/CULInterface.hpp"

#include "CUL/Memory/MemoryPool.hpp"
#include "CUL/Threading/ThreadUtil.hpp"
#include "CUL/Filesystem/FSApi.hpp"
#include "CUL/Filesystem/FileFactory.hpp"
#include "CUL/Filesystem/Path.hpp"
#include "CUL/Graphics/IImageLoader.hpp"
#include "GenericUtils/IConfigFileConcrete.hpp"
#include "CUL/GenericUtils/ConsoleUtilities.hpp"
#include "CUL/GenericUtils/Singleton.hpp"
#include "CUL/IMPORT_tracy.hpp"

#include "CUL/STL_IMPORTS/STD_iostream.hpp"
#include "CUL/STL_IMPORTS/STD_new.hpp"
#include "CUL/STL_IMPORTS/STD_memory_resource.hpp"

static std::array<std::byte, 8192> g_bufferBlocks;
static std::pmr::monotonic_buffer_resource g_buffer_src( &g_bufferBlocks, sizeof( g_bufferBlocks ) );
static std::pmr::vector<void*> g_allocatedBlocks( &g_buffer_src );

static CUL::LOG::ILogger* g_logger = nullptr;

using namespace CUL;

#if CUL_GLOBAL_MEMORY_POOL

#endif  // #if CUL_GLOBAL_MEMORY_POOL

CULInterface* CULInterface::s_instance = nullptr;

CULInterface* CULInterface::createInstance( const FS::Path& configFile )
{
    if( s_instance == nullptr )
    {
        auto instance = new CULInterface( configFile );
        instance->initialize();
    }

    return s_instance;
}

CULInterface* CULInterface::getInstance()
{
    return s_instance;
}

CULInterface::CULInterface( const FS::Path& configFilePath ) : m_configFilePath( configFilePath )
{
    CUL::Assert::simple( s_instance == nullptr, "Propably DLL Hell. There is already a instance of CUL Interface." );

    s_instance = this;
}

void CULInterface::initialize()
{
    m_fileFactory = new FS::FileFactory( this );
    m_fsApi = std::make_unique<FS::FSApi>( this, m_fileFactory );

    m_logger = &LOG::ILogger::getInstance();

    if( !m_configFilePath.getPath().empty() )
    {
        m_configFile = loadConfigFile( m_configFilePath );
    }

    m_imageLoader.reset( Graphics::IImageLoader::createConcrete( m_configFile, this ) );

    m_logger->log( "Initialized logger." );
    if( !g_logger )
    {
        g_logger = m_logger;
    }

#if CUL_GLOBAL_MEMORY_POOL
    CUL::Memory::MemoryPool::s_logger = m_logger;
#endif  // #if CUL_GLOBAL_MEMORY_POOL

    // m_sysFonts = OSUtils::ISystemFonts::createConcrete( m_fsApi.get(), m_logger );

    m_args.reset( new GUTILS::ConsoleUtilities() );

    m_threadUtils = &ThreadUtil::getInstance();


    constexpr std::size_t sizeOfStdString{ sizeof( std::string ) };
    constexpr std::size_t sizeOfString{ sizeof( String ) };
    constexpr std::size_t sizeOfFSPath{ sizeof( FS::Path ) };

    m_logger->logVariable( LOG::Severity::Warn, "Size of std::string: %d B", sizeOfStdString );
    m_logger->logVariable( LOG::Severity::Warn, "Size of String:      %d B", sizeOfString );
    m_logger->logVariable( LOG::Severity::Warn, "Size of FS::Path:    %d B", sizeOfFSPath );
}

GUTILS::IConfigFile* CULInterface::getConfig() const
{
    return m_configFile;
}

CUL::LOG::ILogger* CULInterface::getLogger()
{
    return m_logger;
}

FS::FSApi* CULInterface::getFS()
{
    return m_fsApi.get();
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

GUTILS::ConsoleUtilities* CULInterface::getConsoleUtils()
{
    return m_args.get();
}

ThreadUtil& CULInterface::getThreadUtils()
{
    return *m_threadUtils;
}

GUTILS::IConfigFile* CULInterface::loadConfigFile( const FS::Path& path )
{
    return new GUTILS::IConfigFileConcrete( path, this );
}

CULInterface::~CULInterface()
{
    delete m_sysFonts;
    m_sysFonts = nullptr;

#if CUL_GLOBAL_MEMORY_POOL
    Memory::MemoryPool::s_logger = m_logger;
#endif  // #if CUL_GLOBAL_MEMORY_POOL
    g_logger = nullptr;
    m_logger = nullptr;
    s_instance = nullptr;
}
