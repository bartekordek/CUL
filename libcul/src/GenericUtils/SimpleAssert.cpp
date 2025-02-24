#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/STL_IMPORTS/STD_iostream.hpp"
#include "CUL/Log/ILogger.hpp"

#include "CUL/STL_IMPORTS/STD_fstream.hpp"
#include "CUL/STL_IMPORTS/STD_cstdarg.hpp"
#include "CUL/STL_IMPORTS/STD_cstdio.hpp"

#include "IMPORT_boost_assert.hpp"
#include "IMPORT_boost_stacktrace.hpp"

using namespace CUL;
#undef ERROR

bool generateStackTrace = true;

void Assert::simple( bool val, const String& msg, LOG::ILogger* loggerIn )
{
    simple( val, msg.cStr(), loggerIn );
}

void Assert::check( bool value, const char* msg... )
{
    if( value )
    {
        return;
    }

    va_list args;
    va_start( args, msg );
    constexpr std::size_t bufferSize{ 512 };
    char buffer[bufferSize];
    snprintf( buffer, bufferSize, msg, args );

    va_end( args );

    BOOST_ASSERT_MSG( value, buffer );

    if( generateStackTrace )
    {
        dumpStackTrace();
    }
}

void Assert::simple( bool val, const char* msg, LOG::ILogger* loggerIn )
{
    if( val == true )
    {
        return;
    }

    if( loggerIn )
    {
        loggerIn->log( msg, LOG::Severity::Error );
    }
    else
    {
        LOG::ILogger::getInstance().logVariable( LOG::Severity::Error, msg );
    }

    if( generateStackTrace )
    {
        dumpStackTrace();
    }

    std::cerr << msg << "\n";
    BOOST_ASSERT_MSG( val, msg );
}

void Assert::dumpStackTrace()
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