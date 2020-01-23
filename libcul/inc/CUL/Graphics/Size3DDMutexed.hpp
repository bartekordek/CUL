#pragma once

#include "CUL/Graphics/ISize3DD.hpp"
#include "CUL/Math/Vector3D.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

class Size3DDMutexedImpl;
class CULLib_API Size3DDMutexed:
    public ISize3DD
{
public:
    Size3DDMutexed();
    Size3DDMutexed( CDbl x, CDbl y, CDbl z );
    Size3DDMutexed( const Size3DDMutexed& val );
    virtual ~Size3DDMutexed();

    Size3DDMutexed& operator=( const Size3DDMutexed& val );
    Size3DDMutexed& operator=( const Math::Vector3Dd& vec );

    void setWidth( CDbl val ) override;
    void setHeight( CDbl val ) override;
    void setDepth( CDbl val ) override;

    void setWidthHeightDepth( CDbl x, CDbl y, CDbl z ) override;

    CDbl getWidth() const override;
    CDbl getHeight() const override;
    CDbl getDepth() const override;

    Size3DDMutexed& operator+=( const Size3DDMutexed& val );
    Size3DDMutexed operator+( const Size3DDMutexed& val );

    Size3DDMutexed& operator-=( const Size3DDMutexed& val );
    Size3DDMutexed operator-( const Size3DDMutexed& val );

    Size3DDMutexed& operator*=( const Size3DDMutexed& val );
    Size3DDMutexed operator*( const Size3DDMutexed& val );

    Size3DDMutexed& operator/=( const Size3DDMutexed& val );
    Size3DDMutexed operator/( const Size3DDMutexed& val );

    Size3DDMutexed& operator+=( CDbl val );
    Size3DDMutexed operator+( CDbl val );

    Size3DDMutexed& operator-=( CDbl val );
    Size3DDMutexed operator-( CDbl val );

protected:
private:
    Size3DDMutexedImpl* m_impl = nullptr;
};

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )