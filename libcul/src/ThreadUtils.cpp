#include "CUL/ThreadUtils.hpp"
#ifdef _MSC_VER
#include "ThreadUtilityWindows.hpp"
#else
#include "ThreadUtilityDummy.hpp"
#endif

using namespace CUL;

ThreadUtils::ThreadUtils()
{

}

void ThreadUtils::setCurrentThreadName( const String& name )
{
#ifdef _MSC_VER
    setCurrentThreadNameWin( name );
#else
    setCurrentThreadNameDummy( name );
#endif

    const std::thread::id thread_id = std::this_thread::get_id();
    m_threadMaps[name] = thread_id;
}

bool ThreadUtils::getIsCurrentThreadNameEqualTo( const String& name )
{
    const auto& currentThreadName = getCurrentThreadName();
    return currentThreadName == name;
}

const String& ThreadUtils::getCurrentThreadName()
{
    const std::thread::id thread_id = std::this_thread::get_id();
    auto foundThread =
        std::find_if( m_threadMaps.begin(), m_threadMaps.end(), [&thread_id]( const std::pair<const CUL::String, std::thread::id>& val ) {
            if( val.second == thread_id )
            {
                return true;
            }
            return false;
    });
    if( foundThread == m_threadMaps.end() )
    {
        return m_emptyname;
    }
    else
    {
        return foundThread->first;
    }
}

ThreadUtils::~ThreadUtils()
{

}