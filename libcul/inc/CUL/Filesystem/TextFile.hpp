#pragma once

#include "CUL/Filesystem/IFile.hpp"

NAMESPACE_BEGIN( CUL )
class CULInterface;
NAMESPACE_BEGIN( FS )

class CULLib_API TextFile final: public IFile
{
public:
    TextFile( const StringWr& fPath, CULInterface* inInterface );
    ~TextFile();
protected:
private:
    void changePath( const Path& newPath ) override;

    const Path& getPath() const override;

    void reload( bool keepLineEndingCharacter ) override;
    void reload() override;
    void unload() override;

    const StringWr& firstLine() const override;
    const StringWr& lastLine() const override;


    const StringWr& getAsOneString() const override;
    const char** getContent() const override;

    unsigned getLinesCount() const override;
    FileType getType() const override;

    Path m_path;
    StringWr m_values;


    TextFile( const TextFile& file ) = delete;
    TextFile( TextFile&& file ) = delete;
    TextFile& operator=( const StringWr& rPath ) = delete;
    TextFile& operator=( const TextFile& file ) = delete;
    TextFile& operator=( TextFile&& file ) = delete;
};

NAMESPACE_END( FS )
NAMESPACE_END( CUL )
