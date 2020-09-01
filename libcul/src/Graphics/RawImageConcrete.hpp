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
    RawImageConcrete();
    ~RawImageConcrete();

    void loadFromFile( CUL::CsStr& path );

    unsigned getID() const override;
    const MATH::Vector3Du& getSize() const override;
    RawDataPtr getData() const override;

protected:
private:
    const FS::Path& getPath() const override;
    void changePath( const FS::Path& newPath ) override;
    void reload( Cbool keepLineEndingCharacter = false ) override;
    void load( Cbool keepLineEndingCharacter = false ) override;
    void unload() override;

    CsStr& firstLine() const override;
    CsStr& lastLine() const override;

    CsStr& getAsOneString() const override;
    const char** getContent() const override;

    unsigned getLinesCount() const override;
    FS::FileType getType() const override;

    CUL::FS::Path m_path;
    CUL::String m_value;
    MATH::Vector3Du m_size;
    RawDataPtr m_data = nullptr;
    unsigned int m_fileId = 0;
    unsigned int m_iluId = 0;

    static bool s_ilInitialized;

    // Deleted:
    RawImageConcrete( const RawImageConcrete& arg ) = delete;
    RawImageConcrete( RawImageConcrete&& arg ) = delete;
    RawImageConcrete& operator=( const RawImageConcrete& arg ) = delete;
    RawImageConcrete& operator=( RawImageConcrete&& arg ) = delete;
};

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )
