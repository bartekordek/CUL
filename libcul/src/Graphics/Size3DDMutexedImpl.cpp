#include "Graphics/Size3DDMutexedImpl.hpp"

using namespace CUL;
using namespace Graphics;

Size3DDMutexedImpl::Size3DDMutexedImpl()
{
}

Size3DDMutexedImpl::Size3DDMutexedImpl( CDbl width, CDbl height, CDbl depth ):
    m_width( width ),
    m_height( height ),
    m_depth( depth )
{
}

Size3DDMutexedImpl::Size3DDMutexedImpl( const Size3DDMutexedImpl& val )
{
    std::lock_guard<std::mutex> lock( this->m_valMtx );
    this->m_width = val.m_width;
    this->m_height = val.m_height;
    this->m_depth = val.m_depth;
}

Size3DDMutexedImpl::~Size3DDMutexedImpl()
{
}

Size3DDMutexedImpl& Size3DDMutexedImpl::operator=( const Size3DDMutexedImpl& val )
{
    if( this != &val )
    {
        std::lock_guard<std::mutex> lock( this->m_valMtx );
        this->m_width = val.m_width;
        this->m_height = val.m_height;
        this->m_depth = val.m_depth;
    }
    return *this;
}

void Size3DDMutexedImpl::setWidth( CDbl val )
{
    std::lock_guard<std::mutex> lock( this->m_valMtx );
    this->m_width = val;
}

void Size3DDMutexedImpl::setHeight( CDbl val )
{
    std::lock_guard<std::mutex> lock( this->m_valMtx );
    this->m_height = val;
}

void Size3DDMutexedImpl::setDepth( CDbl val )
{
    std::lock_guard<std::mutex> lock( this->m_valMtx );
    this->m_depth = val;
}

void Size3DDMutexedImpl::setWidthHeightDepth( CDbl width, CDbl height, CDbl depth )
{
    std::lock_guard<std::mutex> lock( this->m_valMtx );
    this->m_width = width;
    this->m_height = height;
    this->m_depth = depth;
}

double Size3DDMutexedImpl::getWidth() const
{
    std::lock_guard<std::mutex> lock( this->m_valMtx );
    return m_width;
}

double Size3DDMutexedImpl::getHeight() const
{
    std::lock_guard<std::mutex> lock( this->m_valMtx );
    return m_height;
}

double Size3DDMutexedImpl::getDepth() const
{
    std::lock_guard<std::mutex> lock( this->m_valMtx );
    return m_depth;
}

Size3DDMutexedImpl& Size3DDMutexedImpl::operator+=( const Size3DDMutexedImpl& val )
{
    std::lock_guard<std::mutex> lock( this->m_valMtx );
    this->m_width += val.m_width;
    this->m_height += val.m_height;
    this->m_depth += val.m_depth;
    return *this;
}

Size3DDMutexedImpl Size3DDMutexedImpl::operator+( const Size3DDMutexedImpl& val )
{
    Size3DDMutexedImpl result;
    result += val;
    return result;
}

Size3DDMutexedImpl& Size3DDMutexedImpl::operator-=( const Size3DDMutexedImpl& val )
{
    std::lock_guard<std::mutex> lock( this->m_valMtx );
    this->m_width -= val.m_width;
    this->m_height -= val.m_height;
    this->m_depth -= val.m_depth;
    return *this;
}

Size3DDMutexedImpl Size3DDMutexedImpl::operator-( const Size3DDMutexedImpl & val )
{
    Size3DDMutexedImpl result;
    result -= val;
    return result;
}

Size3DDMutexedImpl & Size3DDMutexedImpl::operator*=( const Size3DDMutexedImpl & val )
{
    std::lock_guard<std::mutex> lock( this->m_valMtx );
    this->m_width *= val.m_width;
    this->m_height *= val.m_height;
    this->m_depth *= val.m_depth;
    return *this;
}

Size3DDMutexedImpl Size3DDMutexedImpl::operator*( const Size3DDMutexedImpl & val )
{
    Size3DDMutexedImpl result;
    result *= val;
    return result;
}

Size3DDMutexedImpl& Size3DDMutexedImpl::operator/=( const Size3DDMutexedImpl & val )
{
    std::lock_guard<std::mutex> lock( this->m_valMtx );
    this->m_width /= val.m_width;
    this->m_height /= val.m_height;
    this->m_depth /= val.m_depth;
    return *this;
}

Size3DDMutexedImpl Size3DDMutexedImpl::operator/( const Size3DDMutexedImpl & val )
{
    Size3DDMutexedImpl result;
    result /= val;
    return result;
}

Size3DDMutexedImpl& Size3DDMutexedImpl::operator+=( CDbl val )
{
    std::lock_guard<std::mutex> lock( this->m_valMtx );
    this->m_width += val;
    this->m_height += val;
    this->m_depth += val;
    return *this;
}

Size3DDMutexedImpl Size3DDMutexedImpl::operator+( CDbl val )
{
    Size3DDMutexedImpl result;
    result += val;
    return result;
}

Size3DDMutexedImpl& Size3DDMutexedImpl::operator-=( CDbl val )
{
    std::lock_guard<std::mutex> lock( this->m_valMtx );
    this->m_width -= val;
    this->m_height -= val;
    this->m_depth -= val;
    return *this;
}

Size3DDMutexedImpl Size3DDMutexedImpl::operator-( CDbl val )
{
    Size3DDMutexedImpl result;
    result -= val;
    return result;
}