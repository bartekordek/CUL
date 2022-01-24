#include "CUL/Graphics/IImageLoader.hpp"
#include "Graphics/ImageLoaderConcrete.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

IImageLoader::IImageLoader( CULInterface* culInterface ) : m_culInterface( culInterface )
{
}

IImageLoader* IImageLoader::createConcrete( CUL::GUTILS::IConfigFile* config, CULInterface* culInterface )
{
    return new ImageLoaderConcrete( config, culInterface );
}

IImage* loadImage( const FS::Path& , bool )
{
    return nullptr;
}

IImage* IImageLoader::loadImage( DataType*, unsigned, unsigned )
{
    return nullptr;
}

IImage* IImageLoader::loadImage(const FS::Path&, bool)
{
    return nullptr;
}

CULInterface* IImageLoader::getInterface()
{
    return m_culInterface;
}

IImageLoader::~IImageLoader()
{
}

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )