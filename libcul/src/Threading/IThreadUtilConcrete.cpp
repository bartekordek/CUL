#include "Threading/IThreadUtilConcrete.hpp"

#ifdef _MSC_VER
#include "ThreadUtilityWindows.hpp"
#endif

using namespace CUL;

ThreadUtilConcrete::ThreadUtilConcrete()
{
}

std::vector<String> ThreadUtilConcrete::getThreadNames() const
{
    std::vector<String> result;

    for( const auto& thread : m_threads )
    {
        result.push_back( thread.second );
    }
    return result;
}

std::optional<String> ThreadUtilConcrete::getCurrentThreadName() const
{
    std::thread::id currentThreadId = std::this_thread::get_id();
    auto it = m_threads.find( currentThreadId );
    if( it == m_threads.end() )
    {
        return {};
    }

    return it->second;
}

void ThreadUtilConcrete::setCurrentThreadName( const String& name )
{
    std::thread::id currentThreadId = std::this_thread::get_id();
    m_threads.insert( { currentThreadId, name } );

#ifdef _MSC_VER
    setCurrentThreadNameWin( name );
#endif
}

ThreadUtilConcrete::~ThreadUtilConcrete()
{
}