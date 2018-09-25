#pragma once

#include "CUL/Path.hpp"

namespace CUL
{
    using DataType = unsigned char;
    class CULLib_API IImage
    {
    public:
        IImage() = default;
        IImage( const IImage& value ) = delete;
        virtual ~IImage() = default;
        IImage& operator=( const IImage& rhv ) = delete;

        virtual const DataType* getData()const = 0;
        virtual const FS::Path& getPath()const = 0;

    protected:
    private:
    };
}