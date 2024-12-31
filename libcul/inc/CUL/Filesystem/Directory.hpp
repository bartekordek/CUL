#pragma once

#include "CUL/Filesystem/IFile.hpp"
#include "CUL/CUL.hpp"

NAMESPACE_BEGIN( CUL )
class CULInterface;
NAMESPACE_BEGIN( FS )

class CULLib_API Directory final:
    public IFile
{
public:
    Directory( const String& path, CULInterface* interfaceIn );

    const Path& getPath() const override;
    void changePath( const Path& newPath ) override;
    void reload( bool keepLineEndingCharacter ) override;
    void reload() override;
    void unload() override;
    const String& firstLine() const override;
    const String& lastLine() const override;
    const String& getAsOneString() const override;
    const char** getContent() const override;
    unsigned int getLinesCount() const override;
    FileType getType() const override;

    ~Directory();
protected:
private:
    Path m_path;
    String m_value;

    // Deleted
    Directory( const Directory& directory ) = delete;
    Directory( Directory&& directory ) = delete;

    Directory& operator=( const Directory& directory ) = delete;
    Directory& operator=( Directory&& directory ) = delete;
};

NAMESPACE_END( FS )
NAMESPACE_END( CUL )
