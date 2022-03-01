#pragma once

#include "CUL/Filesystem/IFile.hpp"

NAMESPACE_BEGIN( CUL )
class CULInterface;
NAMESPACE_BEGIN( FS )

class CULLib_API TextFile final: public IFile
{
public:
    TextFile( const String& fPath, CULInterface* interface );
    ~TextFile();
protected:
private:
    void changePath( const Path& newPath ) override;

    const Path& getPath() const override;

    void reload( bool keepLineEndingCharacter = false ) override;
    void load( bool keepLineEndingCharacter = false ) override;
    void unload() override;

    const String& firstLine() const override;
    const String& lastLine() const override;


    const String& getAsOneString() const override;
    const char** getContent() const override;

    unsigned getLinesCount() const override;

    Path m_path;
    String m_values;


    TextFile( const TextFile& file ) = delete;
    TextFile( TextFile&& file ) = delete;
    TextFile& operator=( const String& rPath ) = delete;
    TextFile& operator=( const TextFile& file ) = delete;
    TextFile& operator=( TextFile&& file ) = delete;
};

NAMESPACE_END( FS )
NAMESPACE_END( CUL )