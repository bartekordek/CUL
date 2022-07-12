#include "CUL/CULInterface.hpp"

#include "CUL/Memory/MemoryPool.hpp"
#include "CUL/Threading/ThreadUtils.hpp"
#include "CUL/Filesystem/FSApi.hpp"
#include "CUL/Filesystem/FileFactory.hpp"
#include "CUL/Graphics/IImageLoader.hpp"
#include "CUL/Log/ILogContainer.hpp"
#include "GenericUtils/IConfigFileConcrete.hpp"
#include "CUL/GenericUtils/ConsoleUtilities.hpp"
#include "Threading/IThreadUtilConcrete.hpp"

#include "CUL/STL_IMPORTS/STD_iostream.hpp"
#include "CUL/STL_IMPORTS/STD_new.hpp"

#if CUL_MEMORY_POOL
CUL::Memory::MemoryPool g_mainMemoryPool;
#endif  // #ifdef CUL_MEMORY_POOL

static CUL::LOG::ILogger* g_logger = nullptr;

using namespace CUL;

CULInterface* CULInterface::createInstance( const FS::Path& configFile )
{
    auto instance = new CULInterface( configFile );
    instance->initialize();
    return instance;
}

CULInterface::CULInterface( const FS::Path& configFilePath ) : m_configFilePath( configFilePath )
{
}

void CULInterface::initialize()
{
    m_fileFactory = new FS::FileFactory( this );
    m_fsApi.reset( FS::FSApi::crateInstance( "FSApiFS", m_fileFactory, this ) );

    if( !m_configFilePath.getPath().empty() )
    {
        m_configFile = loadConfigFile( m_configFilePath );
    }

    m_imageLoader.reset( Graphics::IImageLoader::createConcrete( m_configFile, this ) );

    m_logger = LOG::LOG_CONTAINER::getLogger();
    m_logger->log( "Initialized logger." );
    if( !g_logger )
    {
        g_logger = m_logger;
    }

#if CUL_MEMORY_POOL
    CUL::Memory::MemoryPool::s_logger = m_logger;
#endif  // #if CUL_MEMORY_POOL

    m_sysFonts = OSUtils::ISystemFonts::createConcrete( m_fsApi.get(), m_logger );

    m_args.reset( new GUTILS::ConsoleUtilities() );

    m_threadUtils = new ThreadUtils();
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

ThreadUtils& CULInterface::getThreadUtils()
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

    delete m_threadUtils;
    m_threadUtils = nullptr;
    LOG::LOG_CONTAINER::destroyLogger();

#if CUL_MEMORY_POOL
    Memory::MemoryPool::s_logger = m_logger;
#endif  // #if CUL_MEMORY_POOL
    g_logger = nullptr;
    m_logger = nullptr;
}

#if CUL_MEMORY_POOL

void* operator new( std::size_t size )
{
    void* stackPool = g_mainMemoryPool.getMemory( size );
    if( stackPool )
    {
        return stackPool;
    }

    //if( g_logger )
    //{
    //    g_logger->log( CUL::String( "Stack pool is full, creating on heap" ) );
    //}

    void* p = std::malloc( size );
    return p;
}

// void operator delete( void* p, std::size_t targetSize ) throw()
// {
//     if( !g_mainMemoryPool.release( p ) )
//     {
//         std::free( p );
//     }
// }

void operator delete( void* p ) throw()
{
    if( !g_mainMemoryPool.release( p ) )
    {
        std::free( p );
    }
}

void* operator new[]( std::size_t size )
{
    void* stackPool = g_mainMemoryPool.getMemory( size );
    if( stackPool )
    {
        return stackPool;
    }

    //if( g_logger )
    //{
    //    g_logger->log( CUL::String( "Stack pool is full, creating on heap" ) );
    //}

    void* p = std::malloc( size );
    return p;
}

void operator delete[]( void* p ) throw()
{
    if( !g_mainMemoryPool.release( p ) )
    {
        std::free( p );
    }
}

// void operator delete[]( void* p, std::size_t targetSize ) throw()
// {
//     if( !g_mainMemoryPool.release( p ) )
//     {
//         std::free( p );
//     }
// }

#endif  // #ifdef CUL_MEMORY_POOL