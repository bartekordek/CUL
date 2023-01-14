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
#include "CUL/GenericUtils/Singleton.hpp"

#include "CUL/STL_IMPORTS/STD_iostream.hpp"
#include "CUL/STL_IMPORTS/STD_new.hpp"
#include "CUL/STL_IMPORTS/STD_memory_resource.hpp"

static std::array<std::byte, 8192> g_bufferBlocks;
static std::pmr::monotonic_buffer_resource g_buffer_src( &g_bufferBlocks, sizeof( g_bufferBlocks ) );
static std::pmr::vector<void*> g_allocatedBlocks( &g_buffer_src );

static CUL::LOG::ILogger* g_logger = nullptr;

using namespace CUL;
#if CUL_GLOBAL_MEMORY_POOL
    
#endif // #if CUL_GLOBAL_MEMORY_POOL

CULInterface* CULInterface::s_instance = nullptr;

CULInterface* CULInterface::createInstance( const FS::Path& configFile )
{
    auto instance = new CULInterface( configFile );
    instance->initialize();
    s_instance = instance;
    return instance;
}

CULInterface* CULInterface::getInstance()
{
    return s_instance;
}

CULInterface::CULInterface( const FS::Path& configFilePath ) : m_configFilePath( configFilePath )
{
    s_instance = this;
}

void CULInterface::initialize()
{
    m_fileFactory = new FS::FileFactory( this );
    m_fsApi.reset( FS::FSApi::crateInstance( "FSApiFS", m_fileFactory, this ) );

    m_logger = LOG::LOG_CONTAINER::getLogger();

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

    m_sysFonts = OSUtils::ISystemFonts::createConcrete( m_fsApi.get(), m_logger );

    m_args.reset( new GUTILS::ConsoleUtilities() );

    m_threadUtils = new ThreadUtils();
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

#if CUL_GLOBAL_MEMORY_POOL
    Memory::MemoryPool::s_logger = m_logger;
#endif  // #if CUL_GLOBAL_MEMORY_POOL
    g_logger = nullptr;
    m_logger = nullptr;
}

#if CUL_GLOBAL_MEMORY_POOL

void* operator new( std::size_t size )
{
    if( Singleton<Memory::MemoryPool>::getInstance().isInitialized() )
    {
        void* result = Singleton<Memory::MemoryPool>::getInstance().getMemory( size );
        if( result )
        {
            //addMe( result );
            return result;
        }
        else
        {
            return std::malloc( size );
        }
    }
    else
    {
        void* p = std::malloc( size );
        return p;
    }
}

void* operator new[]( std::size_t size )
{
    if( Singleton<Memory::MemoryPool>::getInstance().isInitialized() )
    {
        void* result = Singleton<Memory::MemoryPool>::getInstance().getMemory( size );
        if( result )
        {
            //addMe( result );
            return result;
        }
        else
        {
            return std::malloc( size );
        }
    }
    else
    {
        void* p = std::malloc( size );
        return p;
    }
}

void operator delete( void* p ) throw()
{
    if( Singleton<Memory::MemoryPool>::getInstance().isInitialized() && Singleton<Memory::MemoryPool>::getInstance().exist( p ) )
    {
        Singleton<Memory::MemoryPool>::getInstance().release( p );
    }
    else
    {
        //if( findMe( p ) )
        //{
        //    std::cerr << "Trying to release old stack ptr.\n";
        //}
        std::free( p );
    }
}

void operator delete( void* p, std::size_t targetSize ) throw()
{
    if( Singleton<Memory::MemoryPool>::getInstance().isInitialized() && Singleton<Memory::MemoryPool>::getInstance().exist( p ) )
    {
        Singleton<Memory::MemoryPool>::getInstance().release( p, targetSize );
    }
    else
    {
        //if( findMe(p) )
        //{
        //    std::cerr << "Trying to release old stack ptr.\n";
        //}
        std::free( p );
    }
}

void operator delete[]( void* p ) throw()
{
    if( Singleton<Memory::MemoryPool>::getInstance().isInitialized() && Singleton<Memory::MemoryPool>::getInstance().exist( p ) )
    {
        Singleton<Memory::MemoryPool>::getInstance().release( p );
    }
    else
    {
        //if( findMe( p ) )
        //{
        //    std::cerr << "Trying to release old stack ptr.\n";
        //}
        std::free( p );
    }
}

void operator delete[]( void* p, std::size_t /* targetSize */ ) throw()
{
    if( Singleton<Memory::MemoryPool>::getInstance().isInitialized() && Singleton<Memory::MemoryPool>::getInstance().exist( p ) )
    {
        Singleton<Memory::MemoryPool>::getInstance().release( p );
    }
    else
    {
        //if( findMe( p ) )
        //{
        //    std::cerr << "Trying to release old stack ptr.\n";
        //}
        std::free( p );
    }
}

#endif  // #ifdef CUL_GLOBAL_MEMORY_POOL