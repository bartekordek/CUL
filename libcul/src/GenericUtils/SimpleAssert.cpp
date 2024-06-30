#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/STL_IMPORTS/STD_iostream.hpp"
#include "CUL/Log/ILogger.hpp"

#include "CUL/STL_IMPORTS/STD_fstream.hpp"

#include "IMPORT_boost_assert.hpp"
#include "IMPORT_boost_stacktrace.hpp"

using namespace CUL;
#undef ERROR

void Assert::simple( bool val, const String& msg, LOG::ILogger* loggerIn, bool generateStackTrace )
{
    if( val == true )
    {
        return;
    }

    if( loggerIn )
    {
        loggerIn->log( msg, LOG::Severity::ERROR );
    }
    else
    {
        LOG::ILogger::getInstance().log( msg, LOG::Severity::ERROR );
    }

    if( generateStackTrace )
    {
        std::ofstream stackDumpFile( "dump.log" );

        auto stackTrace = boost::stacktrace::stacktrace();
        size_t stackTraceSize = stackTrace.size();
        for( size_t i = 0; i < stackTraceSize; ++i )
        {
            stackDumpFile << stackTrace[i] << "\n";
        }

        stackDumpFile.close();

        std::cerr << stackTrace;
    }

    std::cerr << msg.string() << "\n";
    BOOST_ASSERT_MSG( val, msg.cStr() );
}