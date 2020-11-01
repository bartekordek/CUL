#include "CUL/CULInterface.hpp"
#include "CUL/Log/ILogContainer.hpp"
#include "CUL/Filesystem/FileFactory.hpp"
#include "CUL/Filesystem/FS.hpp"

using namespace CUL;

CULInterface* CULInterface::createInstance()
{
    return new CULInterface();
}

CULInterface::CULInterface()
{
    m_fileFactory = new FS::FileFactory();

    m_logger = LOG::LOG_CONTAINER::getLogger();
    m_logger->log( "Initialized logger." );

    m_fsApi = new FS::FSApi( m_fileFactory.get() );

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


CULInterface::~CULInterface()
{
    LOG::LOG_CONTAINER::destroyLogger();
    m_logger = nullptr;
}