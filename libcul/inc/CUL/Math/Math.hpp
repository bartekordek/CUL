#pragma once
namespace CUL
{
    namespace Math
    {
        namespace Util
        {
            template<typename Type>
            Type abs( const Type arg )
            {
                if( arg < 0 )
                {
                    return 0 - arg;
                }
                return arg;
            }
        }

        namespace Constants
        {
            const double PI = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481;
        }
    }
}