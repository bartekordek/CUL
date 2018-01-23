#include "CUL/IPivot.hpp"

using namespace CUL;

IPivot::IPivot()
{
}

IPivot::~IPivot()
{
}

void IPivot::setPivot( 
    const IPivot::PivotType type, 
    const double px, const double py, const double pz )
{
    if( IPivot::PivotType::NORMALIZED == type )
    {
        this->m_pNorm.setXYZ( px, py, pz );
        recalculatePivotAbs();
    }
    else
    {
        this->m_pAbs.setXYZ( px, py, pz );
        recalculatePivotNorm();
    }
}

void IPivot::setPivotX( 
    const PivotType type, 
    const double val )
{
    if( IPivot::PivotType::NORMALIZED == type )
    {
        this->m_pNorm.setX( val );
        this->m_pAbs.setX( this->m_sizeAbs.getX() * this->m_pNorm.getX() );
    }
    else
    {
        this->m_pAbs.setX( val );
        this->m_pNorm.setX( this->m_pAbs.getX() / this->m_sizeAbs.getX() );
    }
}

void IPivot::setPivotY( 
    const PivotType type, 
    const double val )
{
    if( IPivot::PivotType::NORMALIZED == type )
    {
        this->m_pNorm.setY( val );
        this->m_pAbs.setY( this->m_sizeAbs.getY() * this->m_pNorm.getY() );
    }
    else
    {
        this->m_pAbs.setY( val );
        this->m_pNorm.setY( this->m_pAbs.getY() / this->m_sizeAbs.getY() );
    }
}

void IPivot::setPivotZ( const PivotType type, const double val )
{
    if( IPivot::PivotType::NORMALIZED == type )
    {
        this->m_pNorm.setZ( val );
        this->m_pAbs.setZ( this->m_sizeAbs.getZ() * this->m_pNorm.getZ() );
    }
    else
    {
        this->m_pAbs.setZ( val );
        this->m_pNorm.setZ( this->m_pAbs.getZ() / this->m_sizeAbs.getZ() );
    }
}

void IPivot::setRealSize( const CUL::Math::Vector3Dd& val )
{
    this->m_sizeAbs = val;
    recalculatePivotAbs();
}

void IPivot::setRealSize( const double width, const double height, const double depth )
{
    this->m_sizeAbs.setXYZ( width, height, depth );
    recalculatePivotAbs();
}

void IPivot::setWidth( const double val )
{
    this->m_sizeAbs.setX( val );
    this->m_pAbs.setX( this->m_sizeAbs.getX() * this->m_pNorm.getX() );
}

void IPivot::setHeight( const double val )
{
    this->m_sizeAbs.setY( val );
    this->m_pAbs.setY( this->m_sizeAbs.getY() * this->m_pNorm.getY() );
}

void IPivot::setDepth( const double val )
{
    this->m_sizeAbs.setZ( val );
    this->m_pAbs.setZ( this->m_sizeAbs.getZ() * this->m_pNorm.getZ() );
}

const CUL::Math::Vector3Dd& IPivot::getPivot( const PivotType type )const
{
    if( IPivot::PivotType::NORMALIZED == type )
    {
        return this->m_pNorm;
    }
    return this->m_pAbs;
}

void IPivot::recalculatePivotAbs()
{
    this->m_pAbs = this->m_sizeAbs * this->m_pNorm;
}

void IPivot::recalculatePivotNorm()
{
    this->m_pNorm = this->m_pAbs / this->m_sizeAbs;
}