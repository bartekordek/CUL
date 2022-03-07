#pragma once

#include "CUL/Filesystem/IFile.hpp"
#include "CUL/Filesystem/Path.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/STL_IMPORTS/STD_memory.hpp"
#include "CUL/UselessMacros.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( FS )

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4820 )
#endif

class FileRegularImpl final:
    public IFile
{
public:
    FileRegularImpl( const String& path, CULInterface* interface );

    ~FileRegularImpl();

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
    void cacheFile();
    FileType getType() const override;
    void loadFromString( const String& stringContent ) override;
    void addLine( const String& line ) override;
    void saveFile() override;

    Path m_path;
    std::vector<String> rows;
    std::vector<char*> m_rowsAsChars;
    String m_cached;
    bool m_keepLineEndingCharacter = false;

private: // Deleted:
    FileRegularImpl( const FileRegularImpl& file ) = delete;
    FileRegularImpl( FileRegularImpl&& file ) = delete;
    FileRegularImpl( const Path& path ) = delete;
    FileRegularImpl& operator=( const FileRegularImpl& rhv ) = delete;
    FileRegularImpl& operator=( FileRegularImpl&& rhv ) = delete;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( FS )
NAMESPACE_END( CUL )