#include "CUL/Memory/MemoryPool.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/Log/ILogger.hpp"


#include "CUL/STL_IMPORTS/STD_algorithm.hpp"
#include "CUL/STL_IMPORTS/STD_cstring.hpp"
#include "CUL/STL_IMPORTS/STD_iostream.hpp"
#include "CUL/STL_IMPORTS/STD_cassert.hpp"

#define assertm(exp, msg) assert(((void)msg, exp))

using namespace CUL;
using namespace Memory;