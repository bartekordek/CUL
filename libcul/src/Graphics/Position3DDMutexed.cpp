#include "CUL/Graphics/Position3DDMutexed.hpp"
#include "Graphics/Position3DDMutexedImpl.hpp"

using namespace CUL;
using namespace Graphics;

Position3DDMutexed::Position3DDMutexed():
    m_impl( new Position3DDMutexedImpl() )
{

}

Position3DDMutexed::Position3DDMutexed( CDbl x, CDbl y, CDbl z ):
    m_impl( new Position3DDMutexedImpl( x, y , z ) )
{
}

Position3DDMutexed::Position3DDMutexed( const Position3DDMutexed& val ):
    m_impl( new Position3DDMutexedImpl( *val.m_impl ) )
{

}

Position3DDMutexed::~Position3DDMutexed()
{
    delete this->m_impl;
    this->m_impl = nullptr;
}

Position3DDMutexed& Position3DDMutexed::operator=( const Position3DDMutexed& val )
{
    if( this != &val )
    {
        *this->m_impl = *val.m_impl;
    }
    return *this;
}

Position3DDMutexed& Position3DDMutexed::operator=( const Math::Vector3Dd& vec )
{
    this->m_impl->setXYZ( vec.getX(), vec.getY(), vec.getZ() );
    return *this;
}

void Position3DDMutexed::setX( CDbl val )
{
    this->m_impl->setX( val );
}

void Position3DDMutexed::setY( CDbl val )
{
    this->m_impl->setY( val );
}

void Position3DDMutexed::setZ( CDbl val )
{
    this->m_impl->setZ( val );
}

void Position3DDMutexed::setXYZ( CDbl x, CDbl y, CDbl z )
{
    this->m_impl->setXYZ( x, y, z );
}

CDbl Position3DDMutexed::getX() const
{
    return this->m_impl->getX();
}

CDbl Position3DDMutexed::getY() const
{
    return this->m_impl->getY();
}

CDbl Position3DDMutexed::getZ() const
{
    return this->m_impl->getZ();
}

Position3DDMutexed& Position3DDMutexed::operator+=( const Position3DDMutexed& val )
{
    *this->m_impl += *val.m_impl;
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
    *this->m_impl -= *val.m_impl;
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
    *this->m_impl *= *val.m_impl;
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
    *this->m_impl /= *val.m_impl;
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
    *this->m_impl -= val;
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
    *this->m_impl -= val;
    return *this;
}

Position3DDMutexed Position3DDMutexed::operator-( CDbl val )
{
    Position3DDMutexed result( *this );
    result -= val;
    return result;
}