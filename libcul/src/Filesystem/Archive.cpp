#include "Filesystem/Archive.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/STL_IMPORTS/STD_string.hpp"
#include "CUL/STL_IMPORTS/STD_cstdint.hpp"

namespace CUL
{
constexpr const char* ARCHIVE_META_MARKER_START = "ARCHIVE_META_START";
constexpr const char* ARCHIVE_FILE_NAME_START = "FILE_NAME_START";
constexpr const char* ARCHIVE_FILE_NAME_END = "FILE_NAME_END";
constexpr const char* ARCHIVE_META_MARKER_END = "ARCHIVE_META_END";
constexpr const char* ARCHIVE_FILE_CONTENT_START = "FILE_CONTENT_START";
constexpr const char* ARCHIVE_FILE_CONTENT_END = "FILE_CONTENT_END";

template <typename T>
constexpr std::size_t getSize( const T& )
{
    return sizeof( T );
}

template <size_t N>
constexpr size_t getSize( const char ( & )[N] )
{
    return N * sizeof( char );  // includes the null terminator
}

inline size_t getSize( const char* str )
{
    return (std::strlen( str ) + 1u) * sizeof( char );  // excludes the null terminator
}

std::size_t sizeOfString( const char* inStr )
{
    return ( std::strlen( inStr ) + 1u ) * sizeof( char );
}

Archive::Archive( const StringWr& inPath )
{
    m_metadata.Path = inPath;

    m_stream.open( inPath.getValue(), std::ios::in | std::ios::binary );
    constexpr std::size_t buffSize{ 1024 };
    char buff[buffSize];

    m_stream.read( buff, sizeOfString( ARCHIVE_META_MARKER_START ) );
    CUL::Assert::simple( std::strcmp( buff, ARCHIVE_META_MARKER_START ) == 0, "Cannot read ARCHIVE_META_MARKER_START tag." );

    m_stream.read( buff, getSize( m_metadata.Version ) );
    std::memcpy( &m_metadata.Version, buff, getSize( m_metadata.Version ) );

    m_stream.read( buff, getSize( m_metadata.FilesCount ) );
    std::memcpy( &m_metadata.FilesCount, buff, getSize( m_metadata.FilesCount ) );

    m_stream.read( buff, sizeOfString( ARCHIVE_META_MARKER_END ) );
    CUL::Assert::simple( std::strcmp( buff, ARCHIVE_META_MARKER_END ) == 0, "Cannot read ARCHIVE_META_MARKER_END tag." );

    for( std::uint64_t i = 0u; i < m_metadata.FilesCount; ++i )
    {
        SFile file;

        m_stream.read( buff, sizeOfString( ARCHIVE_FILE_CONTENT_START ) );
        CUL::Assert::simple( std::strcmp( buff, ARCHIVE_FILE_CONTENT_START ) == 0, "Cannot read ARCHIVE_FILE_CONTENT_START tag." );

        const std::size_t pathVarSize = getSize( file.PathSize );
        m_stream.read( buff, pathVarSize );
        std::memcpy( &file.PathSize, buff, getSize( file.PathSize ) );

        m_stream.read( buff, file.PathSize );
        file.Path = StringWr( buff );

        m_stream.read( buff, getSize( file.FileSize ) );
        std::memcpy( &file.FileSize, buff, getSize( file.FileSize ) );

        auto* content = new char[file.FileSize];
        m_stream.read( content, file.FileSize );

        file.Content = content;

        m_stream.read( buff, sizeOfString( ARCHIVE_FILE_CONTENT_END ) );
        CUL::Assert::simple( std::strcmp( buff, ARCHIVE_FILE_CONTENT_END ) == 0, "Cannot read ARCHIVE_FILE_CONTENT_END tag." );

        m_metadata.Files.push_back( file );
    }
}

Archive::Archive( const SFArchiveMetadata& inMetaCpy, EAccesMode inAccessMode )
{
    SFArchiveMetadata inMeta = inMetaCpy;

    m_stream.open( inMeta.Path.getValue(), std::ios::out | std::ios::binary );
    m_metadata = inMeta;
    m_stream.write( ARCHIVE_META_MARKER_START, sizeOfString( ARCHIVE_META_MARKER_START ) );
    m_stream.write( reinterpret_cast<const char*>( &m_metadata.Version ), getSize( m_metadata.Version ) );
    m_stream.write( reinterpret_cast<const char*>( &m_metadata.FilesCount ), getSize( m_metadata.FilesCount ) );
    m_stream.write( ARCHIVE_META_MARKER_END, sizeOfString( ARCHIVE_META_MARKER_END ) );
    for( SFile& file : m_metadata.Files )
    {
        const char* path = file.Path.getUtfChar();
        m_stream.write( ARCHIVE_FILE_CONTENT_START, getSize( ARCHIVE_FILE_CONTENT_START ) );
        file.PathSize = getSize( path );
        m_stream.write( reinterpret_cast<const char*>( &file.PathSize ), getSize( file.PathSize ) );
        m_stream.write( path, file.PathSize );
        m_stream.write( reinterpret_cast<const char*>( &file.FileSize ), getSize( file.FileSize ) );
        m_stream.write( reinterpret_cast<const char*>( file.Content ), file.FileSize );

        m_stream.write( ARCHIVE_FILE_CONTENT_END, sizeOfString( ARCHIVE_FILE_CONTENT_END ) );
    }
    m_stream.close();
}

void Archive::loadFile( const StringWr& inPath )
{
    m_stream.open( inPath.getValue(), std::ios::in | std::ios::binary );
}

std::vector<SFile> Archive::getFileList() const
{
    std::vector<SFile> result;

    return result;
}

SFile* Archive::getFile( const StringWr& inPath )
{
    for( SFile& file : m_metadata.Files )
    {
        if( file.Path == inPath )
        {
            return &file;
        }
    }
    return nullptr;
}

}  // namespace CUL