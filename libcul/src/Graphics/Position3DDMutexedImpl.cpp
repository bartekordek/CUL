#include "Graphics/Position3DDMutexedImpl.hpp"

using namespace CUL;
using namespace Graphics;

Position3DDMutexedImpl::Position3DDMutexedImpl()
{
}

Position3DDMutexedImpl::Position3DDMutexedImpl( CDbl x, CDbl y, CDbl z ):
    m_x( x ),
    m_y( y ),
    m_z( z )
{
}

Position3DDMutexedImpl::Position3DDMutexedImpl( const Position3DDMutexedImpl& val )
{
    std::lock_guard<std::mutex> lock( m_valMtx );
    m_x = val.m_x;
    m_y = val.m_y;
    m_z = val.m_z;
}

Position3DDMutexedImpl::~Position3DDMutexedImpl()
{
}

Position3DDMutexedImpl& Position3DDMutexedImpl::operator=( const Position3DDMutexedImpl& val )
{
    if( this != &val )
    {
        std::lock_guard<std::mutex> lock( m_valMtx );
        m_x = val.m_x;
        m_y = val.m_y;
        m_z = val.m_z;
    }
    return *this;
}

void Position3DDMutexedImpl::setX( CDbl val )
{
    std::lock_guard<std::mutex> lock( m_valMtx );
    m_x = val;
}

void Position3DDMutexedImpl::setY( CDbl val )
{
    std::lock_guard<std::mutex> lock( m_valMtx );
    m_y = val;
}

void Position3DDMutexedImpl::setZ( CDbl val )
{
    std::lock_guard<std::mutex> lock( m_valMtx );
    m_z = val;
}

void Position3DDMutexedImpl::setXYZ( CDbl x, CDbl y, CDbl z )
{
    std::lock_guard<std::mutex> lock( m_valMtx );
    m_x = x;
    m_y = y;
    m_z = z;
}

double Position3DDMutexedImpl::getX() const
{
    std::lock_guard<std::mutex> lock( m_valMtx );
    return m_x;
}

double Position3DDMutexedImpl::getY() const
{
    std::lock_guard<std::mutex> lock( m_valMtx );
    return m_y;
}

double Position3DDMutexedImpl::getZ() const
{
    std::lock_guard<std::mutex> lock( m_valMtx );
    return m_z;
}

Position3DDMutexedImpl& Position3DDMutexedImpl::operator+=( const Position3DDMutexedImpl& val )
{
    std::lock_guard<std::mutex> lock( m_valMtx );
    m_x += val.m_x;
    m_y += val.m_y;
    m_z += val.m_z;
    return *this;
}

Position3DDMutexedImpl Position3DDMutexedImpl::operator+( const Position3DDMutexedImpl& val )
{
    Position3DDMutexedImpl result;
    result += val;
    return result;
}

Position3DDMutexedImpl& Position3DDMutexedImpl::operator-=( const Position3DDMutexedImpl& val )
{
    std::lock_guard<std::mutex> lock( m_valMtx );
    m_x -= val.m_x;
    m_y -= val.m_y;
    m_z -= val.m_z;
    return *this;
}

Position3DDMutexedImpl Position3DDMutexedImpl::operator-( const Position3DDMutexedImpl & val )
{
    Position3DDMutexedImpl result;
    result -= val;
    return result;
}

Position3DDMutexedImpl & Position3DDMutexedImpl::operator*=( const Position3DDMutexedImpl & val )
{
    std::lock_guard<std::mutex> lock( m_valMtx );
    m_x *= val.m_x;
    m_y *= val.m_y;
    m_z *= val.m_z;
    return *this;
}

Position3DDMutexedImpl Position3DDMutexedImpl::operator*( const Position3DDMutexedImpl & val )
{
    Position3DDMutexedImpl result;
    result *= val;
    return result;
}

Position3DDMutexedImpl& Position3DDMutexedImpl::operator/=( const Position3DDMutexedImpl & val )
{
    std::lock_guard<std::mutex> lock( m_valMtx );
    m_x /= val.m_x;
    m_y /= val.m_y;
    m_z /= val.m_z;
    return *this;
}

Position3DDMutexedImpl Position3DDMutexedImpl::operator/( const Position3DDMutexedImpl & val )
{
    Position3DDMutexedImpl result;
    result /= val;
    return result;
}

Position3DDMutexedImpl& Position3DDMutexedImpl::operator+=( CDbl val )
{
    std::lock_guard<std::mutex> lock( m_valMtx );
    m_x += val;
    m_y += val;
    m_z += val;
    return *this;
}

Position3DDMutexedImpl Position3DDMutexedImpl::operator+( CDbl val )
{
    Position3DDMutexedImpl result;
    result += val;
    return result;
}

Position3DDMutexedImpl& Position3DDMutexedImpl::operator-=( CDbl val )
{
    std::lock_guard<std::mutex> lock( m_valMtx );
    m_x -= val;
    m_y -= val;
    m_z -= val;
    return *this;
}

Position3DDMutexedImpl Position3DDMutexedImpl::operator-( CDbl val )
{
    Position3DDMutexedImpl result;
    result -= val;
    return result;
}