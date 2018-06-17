#pragma once
#include "CUL/Math/Epsilon.hpp"
#include "CUL/CUL.hpp"
namespace CUL
{
    namespace Math
    {
#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4514 )
#pragma warning( disable: 4820 )
#endif
        template <typename Type>
        class Vector3D:
            public Epsilon<Type>
        {
        public:
            enum class Axis: short
            {
                X,
                Y,
                Z
            };

            Vector3D() = default;
            Vector3D( 
                const Type xVal,
                const Type yVal,
                const Type zVal ):
                    x( xVal ),
                    y( yVal ),
                    z( zVal )
            {
            }

            Vector3D( const Vector3D<Type>& vector ) = default;

            template <class someOtherClass>
            Vector3D( const Vector3D<someOtherClass>& right ):
                x( static_cast<Type>( right.getX() ) ),
                y( static_cast<Type>( right.getY() ) ),
                z( static_cast<Type>( right.getZ() ) )
            {
            }

            virtual ~Vector3D() = default;

            const Type getX()const
            {
                return this->x;
            }

            const Type getY()const
            {
                return this->y;
            }

            const Type getZ()const
            {
                return this->z;
            }

            void setX( const Type xValue )
            {
                this->x = xValue;
            }

            void setY( const Type yValue )
            {
                this->y = yValue;
            }

            void setZ( const Type zValue )
            {
                this->z = zValue;
            }

            void setXYZ(
                const Type xVal,
                const Type yVal,
                const Type zVal )
            {
                this->x = xVal;
                this->y = yVal;
                this->z = zVal;
            }

            void setXYZ( const Vector3D& object )
            {
                this->x = object.x;
                this->y = object.y;
                this->z = object.z;
            }

            const bool operator!=( Vector3D& r ) const
            {
                return !this->operator==( r );
            }

            const bool operator==( const Vector3D& ivector )const
            {
                if( 
                    Epsilon<Type>::equals( this->x, ivector.x ) &&
                    Epsilon<Type>::equals( this->y, ivector.y ) &&
                    Epsilon<Type>::equals( this->z, ivector.z ) )
                {
                    return true;
                }
                return false;
            }

            Vector3D<Type> operator*( const Vector3D<Type>& t )const
            {
                Vector3D<Type> result;
                result.x = this->x * t.x;
                result.y = this->y * t.y;
                result.z = this->z * t.z;
                return result;
            }

            Vector3D<Type> operator-( const Vector3D<Type>& t )const
            {
                Vector3D<Type> result;
                result.x = this->x - t.x;
                result.y = this->y - t.y;
                result.z = this->z - t.z;
                return result;
            }

            Vector3D<Type>& operator*=( const Vector3D<Type>& t )
            {
                this->x = this->x * t.x;
                this->y = this->y * t.y;
                this->z = this->z * t.z;
                return *this;
            }

            Vector3D<Type> operator*( const Type& t )const
            {
                Vector3D<Type> result;
                result.x = this->x * t;
                result.y = this->y * t;
                result.z = this->z * t;
                return result;
            }

            Vector3D<Type>& operator*=( const Type& t )
            {
                this->x = this->x * t;
                this->y = this->y * t;
                this->z = this->z * t;
                return *this;
            }

            Vector3D<Type> operator+( const Vector3D<Type>& right )
            {
                Vector3D<Type> result( *this );
                result += right;
                return result;
            }

            Vector3D<Type>& operator+=( const Vector3D<Type>& right )
            {
                this->x += right.x;
                this->y += right.y;
                this->z += right.z;
                return *this;
            }

            Vector3D<Type> operator-( const Vector3D<Type>& right )
            {
                Vector3D<Type> result( *this );
                result -= right;
                return result;
            }

            Vector3D<Type>& operator-=( const Vector3D<Type>& right )
            {
                this->x -= right.x;
                this->y -= right.y;
                this->z -= right.z;
                return *this;
            }

            Vector3D<Type>& operator=( const Vector3D<Type>& right )
            {
                if( this != &right )
                {
                    this->x = right.x;
                    this->y = right.y;
                    this->z = right.z;
                }
                return *this;
            }

            Vector3D<Type> operator/( const Vector3D<Type>& t )const
            {
                Vector3D<Type> result;
                result.x = this->x / t.x;
                result.y = this->y / t.y;
                result.z = this->z / t.z;
                return result;
            }

            Vector3D<Type>& operator/=( const Vector3D<Type>& t )
            {
                this->x = this->x / t.x;
                this->y = this->y / t.y;
                this->z = this->z / t.z;
                return *this;
            }

            Vector3D<Type> operator/( const Type& t )const
            {
                Vector3D<Type> result;
                result.x = this->x / t;
                result.y = this->y / t;
                result.z = this->z / t;
                return result;
            }

            Vector3D<Type>& operator/=( const Type& t )
            {
                this->x = this->x / t;
                this->y = this->y / t;
                this->z = this->z / t;
                return *this;
            }

            const Type dotProdcut( const Vector3D<Type>& right )const
            {
                const Type xx = this->x * right.x;
                const Type yy = this->y * right.y;
                const Type zz = this->z * right.z;
                return xx * yy * zz;
            }

            const Vector3D<Type> crossProducti( const Vector3D<Type>& right )const
            {
                const auto& v1 = *this;
                const auto& v2 = right;

                const Type cx = v1.y * v2.z - v1.z * v2.y;
                const Type cy = v1.z * v2.x - v1.x * v2.z;
                const Type cz = v1.x * v2.y - v1.y * v2.x;
                return Vector3D<Type>( cx, cy, cz );
            }

            const Type getAxis( const Axis axis )const
            {
                if( Axis::X == axis )
                {
                    return this->x;
                }
                else if( Axis::Y == axis )
                {
                    return this->y;
                }
                else if( Axis::Z == axis )
                {
                    return this->z;
                }
                return static_cast<Type>(0);
            }

            template <class someOtherClass>
            Vector3D<Type>& operator=( const Vector3D<someOtherClass>& right )
            {
                this->x = static_cast<Type>( right.getX() );
                this->y = static_cast<Type>( right.getY() );
                this->z = static_cast<Type>( right.getZ() );
                return *this;
            }

        protected:
        private:
            Type x = static_cast<Type>( 0 );
            Type y = static_cast<Type>( 0 );
            Type z = static_cast<Type>( 0 );
        };
#ifdef _MSC_VER
#pragma warning( pop )
#endif
        using Vector3Dd = Vector3D<double> ;
        using Vector3Di = Vector3D<int>;
        using Vector3Du = Vector3D<unsigned>;
    }
}