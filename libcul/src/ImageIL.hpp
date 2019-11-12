#pragma once

#include "CUL/Graphics/IImage.hpp"

#if _MSC_VER
#pragma warning( push, 0 )
#pragma warning( disable: 4710 )
#endif
#include "IL/ilu.h"
#ifdef _MSC_VER
#pragma warning( pop )
#endif

namespace CUL
{
    class ImageIL final:
        public IImage
    {
    public:
        ImageIL( void );
        ImageIL( const ImageIL& val );
        ~ImageIL( void );
        ImageIL& operator=( const ImageIL& rhv );
        ImageIL& operator=( const FS::Path& path );

        const DataType* getData()const;
        const FS::Path& getPath()const;

    protected:
    private:
        void loadImageFrom( const FS::Path& path );

        ILubyte* m_data = nullptr;
        FS::Path m_path;

    };
}