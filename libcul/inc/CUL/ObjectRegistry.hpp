#pragma once

#include "CUL/GenericUtils/Singleton.hpp"
#include "CUL/STL_IMPORTS/STD_mutex.hpp"
#include "CUL/STL_IMPORTS/STD_unordered_map.hpp"
#include "CUL/STL_IMPORTS/STD_unordered_set.hpp"

NAMESPACE_BEGIN( CUL )

class IObject;

class CULLib_API ObjectRegistry final: public CUL::Singleton<ObjectRegistry>
{
public:
    friend class CUL::Singleton<ObjectRegistry>;
    ObjectRegistry( const ObjectRegistry& ) = delete;
    ObjectRegistry( ObjectRegistry&& ) = delete;
    ObjectRegistry& operator=( const ObjectRegistry& ) = delete;
    ObjectRegistry& operator=( ObjectRegistry&& ) = delete;

    std::uint64_t getFirstFreeIndex();

    void removeIndex( std::uint64_t index );

protected:
private:
    ObjectRegistry();

    ~ObjectRegistry();

    std::mutex m_listMtx;
    std::unordered_set<std::uint64_t> m_list;
};

NAMESPACE_END(CUL)