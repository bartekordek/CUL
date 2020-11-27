#include "CUL/OSUtils/ISystemFonts.hpp"
#if _WIN32
#include "OSUtils/SystemFontsWindows.hpp"
#endif

using namespace CUL;

using ISystemFonts = OSUtils::ISystemFonts;

void unused( CUL::FS::FSApi*, LOG::ILogger* )
{

}

ISystemFonts* ISystemFonts::createConcrete( CUL::FS::FSApi* fsApis, LOG::ILogger* logger )
{
#if _WIN32
    using SystemFontsWindows = OSUtils::SystemFontsWindows;
    return new SystemFontsWindows( fsApis, logger );
#else
    unused( fsApis, logger );
    return nullptr; //TODO
#endif
}