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
    FileRegularImpl();
    ~FileRegularImpl();

protected:
private:
    void changePath( const Path& newPath ) override;
    const Path& getPath() const override;
    CBool exists() const override;
    CBool isBinary() const override;
    void reload( CBool keepLineEndingCharacter = false ) override;
    void load( CBool keepLineEndingCharacter = false ) override;
    void unload() override;
    CsStr& firstLine() const override;
    CsStr& lastLine() const override;
    CsStr& getAsOneString() const override;
    const char** getContent() const override;
    Cunt getLinesCount() const override;
    void cacheFile();

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