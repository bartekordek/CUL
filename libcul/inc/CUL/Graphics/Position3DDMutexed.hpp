#pragma once

#include "CUL/Graphics/IPosition3DD.hpp"
#include "CUL/Math/Vector3D.hpp"
#include "CUL/STL_IMPORTS/STD_memory.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

class Position3DDMutexedImpl;
class CULLib_API Position3DDMutexed:
    public IPosition3DD
{
public:
    Position3DDMutexed();
    Position3DDMutexed( CDbl x, CDbl y, CDbl z );
    Position3DDMutexed( const Position3DDMutexed& val );
    virtual ~Position3DDMutexed();

    Position3DDMutexed& operator=( const Position3DDMutexed& val );
    Position3DDMutexed& operator=( const MATH::Vector3Dd& vec );

    void setX( CDbl val ) override;
    void setY( CDbl val ) override;
    void setZ( CDbl val ) override;

    void setXYZ( CDbl x, CDbl y, CDbl z ) override;

    CDbl getX() const override;
    CDbl getY() const override;
    CDbl getZ() const override;

    Position3DDMutexed& operator+=( const Position3DDMutexed& val );
    Position3DDMutexed operator+( const Position3DDMutexed& val );

    Position3DDMutexed& operator-=( const Position3DDMutexed& val );
    Position3DDMutexed operator-( const Position3DDMutexed& val );

    Position3DDMutexed& operator*=( const Position3DDMutexed& val );
    Position3DDMutexed operator*( const Position3DDMutexed& val );

    Position3DDMutexed& operator/=( const Position3DDMutexed& val );
    Position3DDMutexed operator/( const Position3DDMutexed& val );

    Position3DDMutexed& operator+=( CDbl val );
    Position3DDMutexed operator+( CDbl val );

    Position3DDMutexed& operator-=( CDbl val );
    Position3DDMutexed operator-( CDbl val );

protected:
private:
    std::unique_ptr<Position3DDMutexedImpl> m_impl;
};

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )
