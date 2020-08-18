#pragma once

/*
 * As the vector itself, this container for some reason do not work with bool.
 * Please see:
 * http://stackoverflow.com/questions/8399417/why-vectorboolreference-doesnt-return-reference-to-bool
 * Workaround: define your own bool type:
    using myBool = unsigned char;
    static const myBool False = 0;
    static const myBool True = 1;
 */

#include "CUL/STL_IMPORTS/STD_iostream.hpp"
#include "CUL/STL_IMPORTS/STD_iomanip.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"

namespace CUL
{
namespace MATH
{
enum class Directions: char
{
    L, R, U, D
};

inline std::pair<int, int> direction2RowCol( const Directions direction )
{
    if( Directions::U == direction )
    {
        return std::pair<int, int>( 1, 0 );
    }

    if( Directions::D == direction )
    {
        return std::pair<int, int>( -1, 0 );
    }

    if( Directions::R == direction )
    {
        return std::pair<int, int>( 0, 1 );
    }

    if( Directions::L == direction )
    {
        return std::pair<int, int>( 0, -1 );
    }

    return std::pair<int, int>( 0, 0 );
}

template <typename Type>
class Matrix2D
{
public:
    Matrix2D()
    {
    }

    Matrix2D( const unsigned rowsCount, const unsigned columnsCount )
    {
        createMatrixOfSize( rowsCount, columnsCount );
    }

    Matrix2D( const Matrix2D& matrix ): values( matrix.values )
    {
    }

    virtual ~Matrix2D()
    {
    }

    Matrix2D& operator=( const Matrix2D& matrix )
    {
        if( &matrix != this )
        {
            values = matrix.values;
        }
        return *this;
    }

    Type& operator()( const unsigned rowIndex, const unsigned colIndex )
    {
        return getValue( rowIndex, colIndex );
    }

    const Type& operator()( const unsigned rowIndex, const unsigned colIndex ) const
    {
        return getValue( rowIndex, colIndex );
    }

    Type& operator()( const unsigned int elementIndex )
    {
        const unsigned int colIndex = elementIndex % getColumnCount();
        const unsigned int rowIndex = elementIndex / getRowsCount();
        return getValue( rowIndex, colIndex );
    }

    void set( const unsigned rowIndex, const unsigned colIndex, const Type& value )
    {
        getValue( rowIndex, colIndex ) = value;
    }

    const unsigned int getColumnCount() const
    {
        if( 0 == values.size() )
        {
            return 0;
        }
        return static_cast<unsigned int>( values[0].size() );
    }

    const unsigned int getRowsCount() const
    {
        return static_cast<unsigned int>( values.size() );
    }

    void moveElementsUntillNoEmptyLine( const Directions direction )
    {
        const unsigned int rowsCount = static_cast<unsigned int>( values.size() );
        if( true == isZero() || 0 == rowsCount )
        {
            return;
        }
        const unsigned int columnsCount = static_cast<unsigned int>( values[0].size() );

        if( Directions::U == direction )
        {
            while( rowIsEmpty( 0 ) )
            {
                moveElements( direction );
            }
        }
        else if( Directions::D == direction )
        {
            while( rowIsEmpty( rowsCount - 1 ) )
            {
                moveElements( direction );
            }
        }
        else if( Directions::R == direction )
        {
            while( columnIsEmpty( columnsCount - 1 ) )
            {
                moveElements( direction );
            }
        }
        else if( Directions::L == direction )
        {
            while( columnIsEmpty( 0 ) )
            {
                moveElements( direction );
            }
        }
    }

    void moveElements( const Directions direction )
    {
        std::pair<int, int> offset = direction2RowCol( direction );
        const unsigned int rowsCount = static_cast<unsigned int>( values.size() );
        if( 0 == rowsCount )
        {
            return;
        }

        const unsigned int columnsCount = static_cast<unsigned int>( values[0].size() );

        for(
            int rowIndex =
            Directions::D == direction ? rowsCount - 1 : 0;
            Directions::D == direction ? rowIndex >= 0 : rowIndex < static_cast<int>( rowsCount );
            Directions::D == direction ? --rowIndex : ++rowIndex )
        {
            for(
                int columnIndex =
                Directions::R == direction ? columnsCount - 1 : 0;
                Directions::R == direction ? columnIndex >= 0 : columnIndex < static_cast<int> ( columnsCount );
                Directions::R == direction ? --columnIndex : ++columnIndex )
            {
                const unsigned int targetXumnIndex = columnIndex - offset.second;
                if( elementExist( rowIndex + offset.first, targetXumnIndex ) )
                {
                    values[rowIndex][columnIndex] = values[rowIndex + offset.first][targetXumnIndex];
                }
                else
                {
                    values[rowIndex][columnIndex] = static_cast<Type>( 0 );
                }
            }
        }
    }

    const bool elementExist( const unsigned row, const unsigned col ) const
    {
        if( getRowsCount() <= row || getColumnCount() <= col )
        {
            return false;
        }
        return true;
    }

    const bool isZero() const
    {
        const Type zeroValue = static_cast<Type>( 0 );

        for( const std::vector<Type>& row : values )
        {
            for( const Type& value : row )
            {
                if( zeroValue != value )
                {
                    return false;
                }
            }
        }
        return true;
    }

    void print() const
    {
        for( const std::vector<Type>& row : values )
        {
            for( const Type& value : row )
            {
                std::cout << std::setw( 3 ) << value;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

    void setMatrix( std::vector<std::vector<Type>>& matrix )
    {
        values = matrix;
    }

protected:
    const bool columnIsEmpty( const unsigned int columnIndex ) const
    {
        if( getRowsCount() == 0 && columnIndex >= getColumnCount() )
        {
            return false;
        }
        const unsigned int rowsCount = getRowsCount();
        for( unsigned int i = 0; i < rowsCount; ++i )
        {
            if( values[i][columnIndex] != static_cast<Type>( 0 ) )
            {
                return false;
            }
        }
        return true;
    }

    const bool rowIsEmpty( const unsigned int rowIndex ) const
    {
        if( rowIndex >= getRowsCount() )
        {
            return false;
        }

        const std::vector<Type>& row = values[rowIndex];
        for( const Type& value : row )
        {
            if( static_cast<Type>( 0 ) != value )
            {
                return false;
            }
        }
        return true;
    }

    std::vector< std::vector<Type> > copyValues() const
    {
        std::vector< std::vector<Type> > result;
        result = values;
        return result;
    }

private:
    void createMatrixOfSize( const unsigned rowsCount, const unsigned columnsCount )
    {
        allocateValues( rowsCount, columnsCount );
        applyValue( static_cast<Type>( 0 ) );
    }

    void allocateValues( const unsigned int rowsCount, const unsigned int columnsCount )
    {
        values.resize( rowsCount );
        for( std::vector<Type>& row : values )
        {
            row.resize( columnsCount );
        }
    }

    void applyValue( const Type& value )
    {
        for( std::vector<Type>& row : values )
        {
            const unsigned int columnsCount = static_cast<unsigned int>( row.size() );
            for( unsigned int columnIndex = 0; columnIndex < columnsCount; ++columnIndex )
            {
                row[columnIndex] = value;
            }
        }
    }

    Type& getValue( const unsigned int rowIndex, const unsigned int columnIndex )
    {
        return values[rowIndex][columnIndex];
    }

    const Type& getValue( const unsigned int rowIndex, const unsigned int columnIndex ) const
    {
        return values[rowIndex][columnIndex];
    }

    std::vector< std::vector<Type> > values;
};
}
}
