#pragma once

#include "CUL/Math/RotationType.hpp"
#include "CUL/Math/Vector3D.hpp"
#include "CUL/Math/IPivot.hpp"
#include "CUL/Math/Angle.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

using RT = CUL::MATH::RotationType;
using CRT = const RT;

class CULLib_API IObject:
    public CUL::MATH::IPivot
{
public:
    IObject() = default;
    IObject( const IObject& ) = delete;
    IObject( IObject&& ) = delete;
    IObject& operator=( const IObject& ) = delete;
    IObject& operator=( IObject&& ) = delete;
    virtual ~IObject() = default;
    
    enum class Type
    {
        SPRITE = 0,
        PRIMITIVE
    };

    virtual void setPosition( const Position3DDMutexed& newPosition ) = 0;
    virtual void setX( CDbl val ) = 0;
    virtual void setY( CDbl val ) = 0;
    virtual void setZ( CDbl val ) = 0;
    virtual void move( const Position3DDMutexed& moveVect ) = 0;

    virtual const Position3DDMutexed& getScale() const = 0;
    virtual void setScale( const CUL::MATH::Vector3Dd& scale ) = 0;

    virtual const Position3DDMutexed& getPosition() const = 0;
    virtual const Position3DDMutexed& getRenderPosition() const = 0;
    virtual const Position3DDMutexed& getSizeReal() const = 0;
    virtual const Position3DDMutexed& getSizeAbs() const = 0;

    virtual Type getType() const = 0;
    virtual bool operator==( const IObject& right ) const;

    virtual void rotate(
        const MATH::Angle& angle,
        CRT = RT::YAW ) = 0;
    virtual const MATH::Angle& getAngle(
        CRT = RT::YAW ) const = 0;

protected:
private:
};

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )