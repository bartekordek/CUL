#include "CUL/ObjectRegistry.hpp"

using namespace CUL;

ObjectRegistry::ObjectRegistry()
{
}

std::uint64_t ObjectRegistry::getFirstFreeIndex()
{
    std::uint64_t result = 0u;
    std::lock_guard<std::mutex> locker( m_listMtx );

    for( std::uint64_t i = 0; i < std::numeric_limits<std::uint64_t>::max(); ++i )
    {
        const auto it = m_list.find( i );
        if( it == m_list.end() )
        {
            result = i;
            m_list.insert( i );
            break;
        }
    }

    return result;
}

void ObjectRegistry::removeIndex( std::uint64_t index )
{
    std::lock_guard<std::mutex> locker( m_listMtx );
    const auto it = m_list.find( index );
    if( it != m_list.end() )
    {
        m_list.erase( it );
    }
}

ObjectRegistry::~ObjectRegistry()
{
}
