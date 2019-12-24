#include "CUL/Graphics/IObject.hpp"

using IObject = CUL::Graphics::IObject;

const bool IObject::operator==( const IObject& right ) const
{
    return this == &right;
}