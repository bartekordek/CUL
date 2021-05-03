#pragma once

#include "CUL/Math/Vector3D.hpp"
#include "CUL/CUL.hpp"
#include "CUL/Math/IPivotObserver.hpp"
#include "CUL/Graphics/Position3DDMutexed.hpp"

#ifdef _MSC_VER
// For now, I let this as TODO, since i don't know
// How to fix this.
// TODO
#pragma warning( push )
#pragma warning( disable: 4574 )
#endif
#ifdef ABSOLUTE
#undef ABSOLUTE
#endif
#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( MATH )

using Position3DDMutexed = CUL::Graphics::Position3DDMutexed;

class CULLib_API IPivot
{
public:
    enum class CULLib_API PivotType: short
    {
        ABSOLUTE,
        NORMALIZED
    };

    IPivot();
    virtual ~IPivot();

    virtual void setPivot(
        double px,
        double py,
        double pz,
        const PivotType type = PivotType::NORMALIZED ) = 0;
    virtual void setPivotX(
        double val,
        const PivotType type = PivotType::NORMALIZED ) = 0;
    virtual void setPivotY(
        double val,
        const PivotType type = PivotType::NORMALIZED ) = 0;
    virtual void setPivotZ(
        double val,
        const PivotType type = PivotType::NORMALIZED ) = 0;

    virtual const Position3DDMutexed& getPivot(
        const PivotType type = PivotType::NORMALIZED ) const = 0;

protected:
private:
};

NAMESPACE_END( MATH )
NAMESPACE_END( CUL )