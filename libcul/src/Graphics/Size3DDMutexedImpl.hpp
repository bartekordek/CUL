#pragma once

#include "CUL/Graphics/Position3DDMutexed.hpp"
#include "CUL/STL_IMPORTS/STD_mutex.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

class Size3DDMutexedImpl
{
public:
    Size3DDMutexedImpl();
    Size3DDMutexedImpl( CDbl x, CDbl y, CDbl z );
    Size3DDMutexedImpl( const Size3DDMutexedImpl& val );
    virtual ~Size3DDMutexedImpl();
    Size3DDMutexedImpl& operator=( const Size3DDMutexedImpl& val );

    void setWidth( CDbl val );
    void setHeight( CDbl val );
    void setDepth( CDbl val );

    void setWidthHeightDepth( CDbl x, CDbl y, CDbl z );

    CDbl getWidth() const;
    CDbl getHeight() const;
    CDbl getDepth() const;

    Size3DDMutexedImpl& operator+=( const Size3DDMutexedImpl& val );
    Size3DDMutexedImpl operator+( const Size3DDMutexedImpl& val );

    Size3DDMutexedImpl& operator-=( const Size3DDMutexedImpl& val );
    Size3DDMutexedImpl operator-( const Size3DDMutexedImpl& val );

    Size3DDMutexedImpl& operator*=( const Size3DDMutexedImpl& val );
    Size3DDMutexedImpl operator*( const Size3DDMutexedImpl& val );

    Size3DDMutexedImpl& operator/=( const Size3DDMutexedImpl& val );
    Size3DDMutexedImpl operator/( const Size3DDMutexedImpl& val );

    Size3DDMutexedImpl& operator+=( CDbl val );
    Size3DDMutexedImpl operator+( CDbl val );

    Size3DDMutexedImpl& operator-=( CDbl val );
    Size3DDMutexedImpl operator-( CDbl val );

protected:
private:
    mutable std::mutex m_valMtx;
    double m_width = 0.0;
    double m_height = 0.0;
    double m_depth = 0.0;
};

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )