#include "CUL/CULInterface.hpp"
#include "CUL/Log/ILogContainer.hpp"

using namespace CUL;

UniquePtr<CULInterface> CULInterface::createInstance()
{
    return UniquePtr<CULInterface>( new CULInterface() );
}

CULInterface::CULInterface()
{
    m_logger = LOG::LOG_CONTAINER::getLogger();
    m_logger->log( "Initialized logger." );
}

LOG::ILogger* CULInterface::getLogger()
{
    return m_logger;
}


CULInterface::~CULInterface()
{
    LOG::LOG_CONTAINER::destroyLogger();
    m_logger = nullptr;
}