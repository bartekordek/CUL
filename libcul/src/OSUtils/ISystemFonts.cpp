#include "CUL/OSUtils/ISystemFonts.hpp"
#if _WIN32
#include "OSUtils/SystemFontsWindows.hpp"
#endif

using namespace CUL;

using ISystemFonts = OSUtils::ISystemFonts;

ISystemFonts* OSUtils::getUtil()
{
#if _WIN32
    using SystemFontsWindows = OSUtils::SystemFontsWindows;
    return new SystemFontsWindows();
#else
    return nullptr; //TODO
#endif
}