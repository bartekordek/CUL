#pragma once

#include "CUL/Graphics/IRawImage.hpp"
#include "CUL/String.hpp"
#include "Graphics/IMPORT_Devil.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

class RawImageConcrete final:
    public IRawImage
{
public:
    RawImageConcrete( void );
    ~RawImageConcrete( void );

    void loadFromFile( CUL::CsStr& path );

    cunt getID()const override;
    const Math::Vector3Du& getSize()const override;
    RawDataPtr getData()const override;

protected:
private:
    Math::Vector3Du m_size;
    RawDataPtr m_data = nullptr;
    unsigned int m_fileId = 0;
    ILuint m_iluId = 0;

    static bool s_ilInitialized;

};

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )