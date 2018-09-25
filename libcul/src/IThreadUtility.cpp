#include "CUL/IThreadUtility.hpp"


#ifdef _MSC_VER
#include "ThreadUtilityWindows.hpp"
#else
#include "ThreadUtilityDummy.hpp"
#endif

using namespace CUL;

std::shared_ptr<IThreadUtility> IThreadUtilityFactory::getConcrete()
{
    std::shared_ptr<IThreadUtility> result;
#ifdef _MSC_VER
    result.reset( new ThreadUtilityWindows() );
#else
    result.reset( new ThreadUtilityDummy() );
#endif
    return result;
}