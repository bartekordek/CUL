#pragma once

#include "CUL/Graphics/IImage.hpp"

namespace CUL
{
    class CULLib_API ImageUtility final
    {
    public:
        ImageUtility() = delete;
        ImageUtility( const ImageUtility& value ) = delete;
        ImageUtility& operator=( const ImageUtility& rhv ) = delete;
        ~ImageUtility() = delete;

        static IImage* createImage( const FS::Path& path );

    protected:
    private:
    };
}