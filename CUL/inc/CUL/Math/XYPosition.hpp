#pragma once
namespace CUL
{
    template <typename Type>
    struct Position2D
    {
        Position2D( 
            const Type x = static_cast<Type>( 0 ), 
            const Type y = static_cast<Type>( 0 ) ):
            x( x ),
            y( y )
        {

        }

        Type x = static_cast<Type>( 0 );
        Type y = static_cast<Type>( 0 );
    };

    using Position2DI = Position2D<int>;
    using Position2DU = Position2D<unsigned>;
    using Position2DD = Position2D<double>;
}