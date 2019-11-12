#include "CUL/Graphics/Size3DDMutexed.hpp"
#include "Graphics/Size3DDMutexedImpl.hpp"

using namespace CUL;
using namespace Graphics;

Size3DDMutexed::Size3DDMutexed():
    m_impl( new Size3DDMutexedImpl() )
{

}

Size3DDMutexed::Size3DDMutexed( CDbl x, CDbl y, CDbl z ):
    m_impl( new Size3DDMutexedImpl( x, y , z ) )
{
}

Size3DDMutexed::Size3DDMutexed( const Size3DDMutexed& val ):
    m_impl( new Size3DDMutexedImpl( *val.m_impl ) )
{

}

Size3DDMutexed::~Size3DDMutexed()
{
    delete this->m_impl;
    this->m_impl = nullptr;
}

Size3DDMutexed& Size3DDMutexed::operator=( const Size3DDMutexed& val )
{
    if( this != &val )
    {
        *this->m_impl = *val.m_impl;
    }
    return *this;
}

Size3DDMutexed& Size3DDMutexed::operator=( const Math::Vector3Dd& vec )
{
    this->m_impl->setWidthHeightDepth( vec.getX(), vec.getY(), vec.getZ() );
    return *this;
}

void Size3DDMutexed::setWidth( CDbl val )
{
    this->m_impl->setWidth( val );
}

void Size3DDMutexed::setHeight( CDbl val )
{
    this->m_impl->setHeight( val );
}

void Size3DDMutexed::setDepth( CDbl val )
{
    this->m_impl->setDepth( val );
}

void Size3DDMutexed::setWidthHeightDepth( CDbl width, CDbl height, CDbl depth )
{
    this->m_impl->setWidthHeightDepth( width, height, depth );
}

CDbl Size3DDMutexed::getWidth() const
{
    return this->m_impl->getWidth();
}

CDbl Size3DDMutexed::getHeight() const
{
    return this->m_impl->getHeight();
}

CDbl Size3DDMutexed::getDepth() const
{
    return this->m_impl->getDepth();
}

Size3DDMutexed& Size3DDMutexed::operator+=( const Size3DDMutexed& val )
{
    *this->m_impl += *val.m_impl;
    return *this;
}

Size3DDMutexed Size3DDMutexed::operator+( const Size3DDMutexed& val )
{
    Size3DDMutexed result( *this );
    result += val;
    return result;
}

Size3DDMutexed& Size3DDMutexed::operator-=( const Size3DDMutexed& val )
{
    *this->m_impl -= *val.m_impl;
    return *this;
}

Size3DDMutexed Size3DDMutexed::operator-( const Size3DDMutexed& val )
{
    Size3DDMutexed result( *this );
    result -= val;
    return result;
}

Size3DDMutexed& Size3DDMutexed::operator*=( const Size3DDMutexed & val )
{
    *this->m_impl *= *val.m_impl;
    return *this;
}

Size3DDMutexed Size3DDMutexed::operator*( const Size3DDMutexed & val )
{
    Size3DDMutexed result( *this );
    result *= val;
    return result;
}

Size3DDMutexed& Size3DDMutexed::operator/=( const Size3DDMutexed & val )
{
    *this->m_impl /= *val.m_impl;
    return *this;
}

Size3DDMutexed Size3DDMutexed::operator/( const Size3DDMutexed & val )
{
    Size3DDMutexed result( *this );
    result /= val;
    return result;
}

Size3DDMutexed& Size3DDMutexed::operator+=( CDbl val )
{
    *this->m_impl -= val;
    return *this;
}

Size3DDMutexed Size3DDMutexed::operator+( CDbl val )
{
    Size3DDMutexed result( *this );
    result += val;
    return result;
}

Size3DDMutexed& Size3DDMutexed::operator-=( CDbl val )
{
    *this->m_impl -= val;
    return *this;
}

Size3DDMutexed Size3DDMutexed::operator-( CDbl val )
{
    Size3DDMutexed result( *this );
    result -= val;
    return result;
}