#include "CUL/Graphics/IImageLoader.hpp"
#include "Graphics/ImageLoaderConcrete.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

IImageLoader::IImageLoader()
{
}

IImageLoader* IImageLoader::createConcrete( CUL::GUTILS::IConfigFile* config )
{
    return new ImageLoaderConcrete( config );
}

IImageLoader::~IImageLoader()
{
}

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )