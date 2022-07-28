#include "CUL/GenericUtils/SimpleDelegate.hpp"

using namespace CUL;
using namespace GUTILS;

SimpleDelegate::SimpleDelegate() noexcept
{

}

void SimpleDelegate::addDelegate(std::function<void(void)> delegate)
{
    m_delegates.push_back( delegate );
}

void SimpleDelegate::execute()
{
    const size_t size = m_delegates.size();
    for( size_t i = 0; i < size; ++i )
    {
        m_delegates[i]();
    }
}

SimpleDelegate::~SimpleDelegate()
{

}