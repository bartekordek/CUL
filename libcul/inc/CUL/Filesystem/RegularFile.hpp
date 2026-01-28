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
    RegularFile( const StringWr& path, CULInterface* inInterface );
    const Path& getPath() const override;
    const StringWr& getAsOneString() const override;
    void overwriteContents( const CUL::StringWr& value );
    void saveFile() override;
    void addLine( const StringWr& line ) override;

    // Getters
    std::string getLineUtf( std::int32_t inLineNum ) const override;
    std::wstring getLineW( std::int32_t inLineNum ) const override;

    ~RegularFile();

protected:
private:
    void loadFromString( const StringWr& contents, bool keepLineEndingCharacter = false ) override;
    void loadFromStringNoEmptyLines( const StringWr& contents, bool keepLineEndingCharacter = false ) override;
    void changePath( const Path& newPath ) override;

    void reload( bool keepLineEndingCharacter ) override;
    void reload() override;
    void load( bool keepLineEndingCharacter, bool removeBottomEmptyLines ) override;
    void unload() override;
    const StringWr& firstLine() const override;
    const StringWr& lastLine() const override;
    const char** getContent() const override;
    const char* getUtfChar() const override;
    unsigned getLinesCount() const override;
    void cacheFile();
    FileType getType() const override;
    void initializeRowsChar();

    Path m_path;
    std::vector<StringWr> m_rows;
    std::string m_asOne;
    StringWr m_cached;

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
