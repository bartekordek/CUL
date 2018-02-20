#include "CUL/Math/IPivot.hpp"

using namespace CUL;
using namespace Math;

IPivot::IPivot( IPivotObserver* pivotObserver ):
    m_pivotObserver( pivotObserver )
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
    notifyPivotObserver();
}

void IPivot::setPivotX( 
    const PivotType type, 
    const double val )
{
    if( IPivot::PivotType::NORMALIZED == type )
    {
        this->m_pNorm.setX( val );
        this->m_pAbs.setX( this->m_sizeReal.getX() * this->m_pNorm.getX() );
    }
    else
    {
        this->m_pAbs.setX( val );
        this->m_pNorm.setX( this->m_pAbs.getX() / this->m_sizeReal.getX() );
    }
    notifyPivotObserver();
}

void IPivot::setPivotY( 
    const PivotType type, 
    const double val )
{
    if( IPivot::PivotType::NORMALIZED == type )
    {
        this->m_pNorm.setY( val );
        this->m_pAbs.setY( this->m_sizeReal.getY() * this->m_pNorm.getY() );
    }
    else
    {
        this->m_pAbs.setY( val );
        this->m_pNorm.setY( this->m_pAbs.getY() / this->m_sizeReal.getY() );
    }
    notifyPivotObserver();
}

void IPivot::setPivotZ( const PivotType type, const double val )
{
    if( IPivot::PivotType::NORMALIZED == type )
    {
        this->m_pNorm.setZ( val );
        this->m_pAbs.setZ( this->m_sizeReal.getZ() * this->m_pNorm.getZ() );
    }
    else
    {
        this->m_pAbs.setZ( val );
        this->m_pNorm.setZ( this->m_pAbs.getZ() / this->m_sizeReal.getZ() );
    }
    notifyPivotObserver();
}

void IPivot::setSizeReal( const CUL::Math::Vector3Dd& val )
{
    this->m_sizeReal = val;
    recalculatePivotAbs();
    notifyPivotObserver();
}

void IPivot::setSizeReal( const double width, const double height, const double depth )
{
    this->m_sizeReal.setXYZ( width, height, depth );
    recalculatePivotAbs();
    notifyPivotObserver();
}

void IPivot::setWidth( const double val )
{
    this->m_sizeReal.setX( val );
    this->m_pAbs.setX( this->m_sizeReal.getX() * this->m_pNorm.getX() );
    notifyPivotObserver();
}

void IPivot::setHeight( const double val )
{
    this->m_sizeReal.setY( val );
    this->m_pAbs.setY( this->m_sizeReal.getY() * this->m_pNorm.getY() );
    notifyPivotObserver();
}

void IPivot::setDepth( const double val )
{
    this->m_sizeReal.setZ( val );
    this->m_pAbs.setZ( this->m_sizeReal.getZ() * this->m_pNorm.getZ() );
    notifyPivotObserver();
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
    this->m_pAbs = this->m_sizeReal * this->m_pNorm;
}

void IPivot::recalculatePivotNorm()
{
    this->m_pNorm = this->m_pAbs / this->m_sizeReal;
}

void IPivot::notifyPivotObserver()
{
    if( m_pivotObserver )
    {
        m_pivotObserver->pivotHasBeenChanged();
    }
}