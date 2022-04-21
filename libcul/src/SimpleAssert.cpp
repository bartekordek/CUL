#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/STL_IMPORTS/STD_iostream.hpp"
#include "CUL/Log/ILogger.hpp"

#include "IMPORT_boost_assert.hpp"

using namespace CUL;

void Assert::simple( bool val, const String& msg, LOG::ILogger* loggerIn )
{
    if( !val )
    {
        if(loggerIn)
        {
            loggerIn->log(msg, LOG::Severity::ERROR);
        }
        std::cerr << msg.string() << "\n";
        BOOST_ASSERT_MSG( val, msg.cStr() );
    }
}