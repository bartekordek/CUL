#include "CUL/Graphics/Position3DDMutexed.hpp"
#include "Graphics/Position3DDMutexedImpl.hpp"

using namespace CUL;
using namespace Graphics;

Position3DDMutexed::Position3DDMutexed():
    m_impl( std::make_unique< Position3DDMutexedImpl>( Position3DDMutexedImpl() ) )
{
}

Position3DDMutexed::Position3DDMutexed( CDbl x, CDbl y, CDbl z ):
    m_impl(
    std::make_unique< Position3DDMutexedImpl>(
    Position3DDMutexedImpl( x, y, z ) ) )
{
}

Position3DDMutexed::Position3DDMutexed( const Position3DDMutexed& val ):
    m_impl(
    std::make_unique< Position3DDMutexedImpl>(
    Position3DDMutexedImpl( *val.m_impl ) ) )
{
}

Position3DDMutexed::~Position3DDMutexed()
{
}

Position3DDMutexed& Position3DDMutexed::operator=( const Position3DDMutexed& val )
{
    if( this != &val )
    {
        *m_impl = *val.m_impl;
    }
    return *this;
}

Position3DDMutexed& Position3DDMutexed::operator=( const Math::Vector3Dd& vec )
{
    m_impl->setXYZ( vec.getX(), vec.getY(), vec.getZ() );
    return *this;
}

void Position3DDMutexed::setX( CDbl val )
{
    m_impl->setX( val );
}

void Position3DDMutexed::setY( CDbl val )
{
    m_impl->setY( val );
}

void Position3DDMutexed::setZ( CDbl val )
{
    m_impl->setZ( val );
}

void Position3DDMutexed::setXYZ( CDbl x, CDbl y, CDbl z )
{
    m_impl->setXYZ( x, y, z );
}

CDbl Position3DDMutexed::getX() const
{
    return m_impl->getX();
}

CDbl Position3DDMutexed::getY() const
{
    return m_impl->getY();
}

CDbl Position3DDMutexed::getZ() const
{
    return m_impl->getZ();
}

Position3DDMutexed& Position3DDMutexed::operator+=( const Position3DDMutexed& val )
{
    *m_impl += *val.m_impl;
    return *this;
}

Position3DDMutexed Position3DDMutexed::operator+( const Position3DDMutexed& val )
{
    Position3DDMutexed result( *this );
    result += val;
    return result;
}

Position3DDMutexed& Position3DDMutexed::operator-=( const Position3DDMutexed& val )
{
    *m_impl -= *val.m_impl;
    return *this;
}

Position3DDMutexed Position3DDMutexed::operator-( const Position3DDMutexed& val )
{
    Position3DDMutexed result( *this );
    result -= val;
    return result;
}

Position3DDMutexed& Position3DDMutexed::operator*=( const Position3DDMutexed & val )
{
    *m_impl *= *val.m_impl;
    return *this;
}

Position3DDMutexed Position3DDMutexed::operator*( const Position3DDMutexed & val )
{
    Position3DDMutexed result( *this );
    result *= val;
    return result;
}

Position3DDMutexed& Position3DDMutexed::operator/=( const Position3DDMutexed & val )
{
    *m_impl /= *val.m_impl;
    return *this;
}

Position3DDMutexed Position3DDMutexed::operator/( const Position3DDMutexed & val )
{
    Position3DDMutexed result( *this );
    result /= val;
    return result;
}

Position3DDMutexed& Position3DDMutexed::operator+=( CDbl val )
{
    *m_impl -= val;
    return *this;
}

Position3DDMutexed Position3DDMutexed::operator+( CDbl val )
{
    Position3DDMutexed result( *this );
    result += val;
    return result;
}

Position3DDMutexed& Position3DDMutexed::operator-=( CDbl val )
{
    *m_impl -= val;
    return *this;
}

Position3DDMutexed Position3DDMutexed::operator-( CDbl val )
{
    Position3DDMutexed result( *this );
    result -= val;
    return result;
}