#pragma once

#include "CUL/Graphics/Position3DDMutexed.hpp"
#include "CUL/STL_IMPORTS/STD_mutex.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

class Position3DDMutexedImpl final
{
public:
    Position3DDMutexedImpl();
    Position3DDMutexedImpl( CDbl x, CDbl y, CDbl z );
    Position3DDMutexedImpl( const Position3DDMutexedImpl& val );
    ~Position3DDMutexedImpl();
    Position3DDMutexedImpl& operator=( const Position3DDMutexedImpl& val );

    void setX( CDbl val );
    void setY( CDbl val );
    void setZ( CDbl val );

    void setXYZ( CDbl x, CDbl y, CDbl z );

    CDbl getX() const;
    CDbl getY() const;
    CDbl getZ() const;

    Position3DDMutexedImpl& operator+=( const Position3DDMutexedImpl& val );
    Position3DDMutexedImpl operator+( const Position3DDMutexedImpl& val );

    Position3DDMutexedImpl& operator-=( const Position3DDMutexedImpl& val );
    Position3DDMutexedImpl operator-( const Position3DDMutexedImpl& val );

    Position3DDMutexedImpl& operator*=( const Position3DDMutexedImpl& val );
    Position3DDMutexedImpl operator*( const Position3DDMutexedImpl& val );

    Position3DDMutexedImpl& operator/=( const Position3DDMutexedImpl& val );
    Position3DDMutexedImpl operator/( const Position3DDMutexedImpl& val );

    Position3DDMutexedImpl& operator+=( CDbl val );
    Position3DDMutexedImpl operator+( CDbl val );

    Position3DDMutexedImpl& operator-=( CDbl val );
    Position3DDMutexedImpl operator-( CDbl val );

protected:
private:
    mutable std::mutex m_valMtx;
    double m_x = 0.0;
    double m_y = 0.0;
    double m_z = 0.0;

};


NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )