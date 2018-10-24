#pragma once

#if _MSC_VER
#pragma warning( push, 0 )
#pragma warning( disable: 4365 )
#pragma warning( disable: 4514 )
#pragma warning( disable: 4571 )
#pragma warning( disable: 4625 )
#pragma warning( disable: 4626 )
#pragma warning( disable: 4710 )
#pragma warning( disable: 4820 )
#pragma warning( disable: 5026 )
#pragma warning( disable: 5027 )
#pragma warning( disable: 5045 )
#endif

#define BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>

#ifdef _MSC_VER
#pragma warning( pop )
#endif