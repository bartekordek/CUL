#include "CUL/Graphics/IImageLoader.hpp"
#include "Graphics/DevilImageLoader.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

IImageLoader::IImageLoader()
{
}

IImageLoader* IImageLoader::createConcrete()
{
    IImageLoader* result = nullptr;
    // TODO
    result = new DevilImageLoader();
    return result;
}

IImageLoader::~IImageLoader()
{
}

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )