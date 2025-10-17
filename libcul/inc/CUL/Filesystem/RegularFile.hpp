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

class CULLib_API RegularFile final: public IFile
{
public:
    RegularFile( const String& path, CULInterface* inInterface );
    const Path& getPath() const override;
    const String& getAsOneString() const override;
    void overwriteContents( const CUL::String& value );
    void saveFile() override;
    ~RegularFile();

protected:
private:
    void loadFromString( const String& contents, bool keepLineEndingCharacter = false ) override;
    void loadFromStringNoEmptyLines( const String& contents, bool keepLineEndingCharacter = false ) override;
    void changePath( const Path& newPath ) override;

    void reload( bool keepLineEndingCharacter ) override;
    void reload() override;
    void load( bool keepLineEndingCharacter, bool removeBottomEmptyLines ) override;
    void unload() override;
    const String& firstLine() const override;
    const String& lastLine() const override;
    const char** getContent() const override;
    unsigned getLinesCount() const override;
    void cacheFile();
    FileType getType() const override;
    void addLine( const String& line ) override;
    void initializeRowsChar();

    Path m_path;
    std::vector<String> m_rows;
    std::vector<const char*> m_rowsAsChars;
    String m_cached;

private:  // Deleted:
    RegularFile( const RegularFile& file ) = delete;
    RegularFile( RegularFile&& file ) = delete;
    RegularFile( const Path& path ) = delete;
    RegularFile& operator=( const RegularFile& rhv ) = delete;
    RegularFile& operator=( RegularFile&& rhv ) = delete;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( FS )
NAMESPACE_END( CUL )
