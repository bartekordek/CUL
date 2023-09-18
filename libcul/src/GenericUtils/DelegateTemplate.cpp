#include "CUL/GenericUtils/DelegateTemplate.hpp"

using namespace CUL;
using namespace GUTILS;

void DelegateTemplateZeroParam::addDelegate( DelegateTemplateZeroParam::DelegateInput delegate )
{
    m_delegates.push_back( delegate );
}

void DelegateTemplateZeroParam::execute()
{
    const size_t size = m_delegates.size();
    for( size_t i = 0; i < size; ++i )
    {
        m_delegates[i]();
    }
}