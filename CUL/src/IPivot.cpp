#include "CUL/IPivot.hpp"

using namespace CUL;

IPivot::IPivot()
{
}

IPivot::~IPivot()
{
}

void IPivot::setPivotNorm( const double px, const double py, const double pz )
{
    calculateAbsPivot();
}

void IPivot::setPivotNormX( const double val )
{
    calculateAbsPivot();
}

void IPivot::setPivotNormY( const double val )
{
    calculateAbsPivot();
}

void IPivot::setPivotNormZ( const double val )
{
    calculateAbsPivot();
}

const CUL::Math::Vector3Du& IPivot::getPivotNormalized()const
{
    return this->m_pNorm;
}