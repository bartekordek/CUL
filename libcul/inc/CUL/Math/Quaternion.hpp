#pragma once

#include "CUL/STL_IMPORTS/STD_cmath.hpp"

namespace CUL
{
    namespace Math
    {
        template <typename Type>
        class Quaternion
        {
        public:
            Quaternion()
            {
            }

            Quaternion( const Quaternion& quaternion ): s( quaternion.s ), x( quaternion.x ), y( quaternion.y ), z( quaternion.z )
            {
            }

            virtual ~Quaternion()
            {
            }

            void normalize()
            {
                //const double normalizeCoefficient = 
            }

            Quaternion inverse() const
            {
                return conjugate() * 1 / squareNorm();
            }

            const Type squareNorm() const
            {
                return norm * norm;
            }

            Quaternion& operator=( const Quaternion& quaternion )
            {
                if( this != &quaternion )
                {
                    s = quaternion.s;
                    x = quaternion.x;
                    y = quaternion.y;
                    z = quaternion.z;
                }
                return *this;
            }

            Quaternion operator+( const Quaternion& quaternion )
            {
                Quaternion result;
                result.s = s + quaternion.s;
                result.x = x + quaternion.x;
                result.y = y + quaternion.y;
                result.z = z + quaternion.z;
                return result;
            }

            Quaternion operator-( const Quaternion& quaternion )
            {
                Quaternion result;
                result.s = s - quaternion.s;
                result.x = x - quaternion.x;
                result.y = y - quaternion.y;
                result.z = z - quaternion.z;
                return result;
            }

            Quaternion operator*( const Quaternion& qb )
            {
                Quaternion result;
                Quaternion& qa = *this;
                Type sa = qa.s;
                Type sb = qb.s;
                Type xa = qa.x;
                Type xb = qb.x;
                Type ya = qa.y;
                Type yb = qb.y;
                Type za = qa.z;
                Type zb = qb.z;

                result.s = sa * sb - xa * xb - ya * yb - za * zb;
                result.x = sa * xb + sb * xa + ya * zb - yb * za;
                result.y = sa * yb + sb * ya + za * xb - zb * xa;
                result.z = sa * zb + sb * za + xa * yb - xb * ya;

                return result;
            }

            Quaternion operator*( const Type scalar )
            {
                Quaternion result;
                //result.a = a * scalar;
                //result.x = x * scalar;
                //result.y = y * scalar;
                //result.z = z * scalar;
                return result;
            }


            const bool operator==( const Quaternion& qb )
            {
                Quaternion& qa = *this;
                return ( ( qa.s == qb.s ) && ( qa.x == qb.x ) && ( qa.y == qb.y ) && ( qa.z == qb.z ) );
            }

            Quaternion conjugate() const
            {
                Quaternion result;
                result.s = s;
                result.x = -x;
                result.y = -y;
                result.z = -z;
                return result;
            }

            void set( const Type s, const Type x, const Type y, const Type z )
            {
                s = s;
                x = x;
                y = y;
                z = z;
                calculateNorm();
            }

            void setS( const Type s )
            {
                s = s;
                calculateNorm();
            }

            void setX( const Type x )
            {
                x = x;
                calculateNorm();
            }

            void setY( const Type y )
            {
                y = y;
                calculateNorm();
            }

            void setZ( const Type z )
            {
                z = z;
                calculateNorm();
            }

            const Type GetS() const
            {
                return s;
            }

            const Type GetX() const
            {
                return x;
            }

            const Type GetY() const
            {
                return y;
            }

            const Type GetZ() const
            {
                return z;
            }

        protected:
        private:
            Quaternion& operator/( const Quaternion& quaternion )
            {
                return Quaternion();
            }

            void calculateNorm()
            {
                norm = sqrt( s*s + x*x + y*y + z*z );
            }

            Type s = 0;
            Type x = 0;
            Type y = 0;
            Type z = 0;
            Type norm = 0;
        };
    }
}