#pragma once

#include "CUL/Filesystem/IFile.hpp"
#include "CUL/Math/Vector3D.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

using Cunt = const unsigned int;
using RawDataPtr = unsigned char*;

class CULLib_API IRawImage:
    public FS::IFile
{
public:
    IRawImage()
    {
    }

    virtual Cunt getID() const = 0;
    virtual const MATH::Vector3Du& getSize() const = 0;
    virtual RawDataPtr getData() const = 0;

    virtual ~IRawImage()
    {
    }

protected:
private:
    IRawImage( const IRawImage& arg ) = delete;
    IRawImage( IRawImage&& arg ) = delete;
    IRawImage& operator=( const IRawImage& arg ) = delete;
    IRawImage& operator=( IRawImage&& arg ) = delete;

};

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )