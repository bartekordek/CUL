#pragma once

#include "CUL/CUL.hpp"
#include "CUL/IMPORT_GLM.hpp"

NAMESPACE_BEGIN(CUL)

NAMESPACE_BEGIN(MATH)

class Utils final
{
public:
    CULLib_API static const glm::vec3 sphericalToVector( float xAngle, float zAngle, float r );
    CULLib_API static bool equals( float val1, float val2, float epsilon );
    CULLib_API static bool equals( double val1, double val2, double epsilon );
    CULLib_API static float floatModulo( float inValue, float moduloVal ); 
    CULLib_API static double floatModulo( double inValue, double moduloVal ); 

protected:
private:
};

template<typename T>
class Constants final
{
public:
    static T Pi;

protected:
private:
};

template <class T>
T Constants<T>::Pi = static_cast<T>( 3.14159265358979323846264338327950288 );



template <typename T>
class Converter final
{
public:
    static T Val180;

    static T toDeg( T inValue )
    {
        return inValue * Val180 / Constants<T>::Pi;
    }

    static T toRad( T inValue )
    {
        return inValue * Constants<T>::Pi / Val180;
    }

protected:
private:
};

template <class T>
T Converter<T>::Val180 = static_cast<T>( 180 );


NAMESPACE_END(MATH)

NAMESPACE_END(CUL)