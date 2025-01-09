#pragma once

#include "CUL/CUL.hpp"

#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/STL_IMPORTS/STD_mutex.hpp"

NAMESPACE_BEGIN(CUL::Containers)

template <class Type>
class TSVector
{
public:
protected:
private:
    mutable std::mutex m_mutex;
    std::vector<Type> m_vector;
};

NAMESPACE_END(CUL::Containers)