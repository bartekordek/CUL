#include "Filesystem/Archive.hpp"
#include "CUL/String/StringUtil.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/STL_IMPORTS/STD_string.hpp"
#include "CUL/STL_IMPORTS/STD_cstring.hpp"
#include "CUL/STL_IMPORTS/STD_cstdint.hpp"

namespace CUL
{
constexpr const char* ARCHIVE_META_MARKER_START = "ARCHIVE_META_START";
constexpr const char* ARCHIVE_FILE_NAME_START = "FILE_NAME_START";
constexpr const char* ARCHIVE_FILE_NAME_END = "FILE_NAME_END";
constexpr const char* ARCHIVE_META_MARKER_END = "ARCHIVE_META_END";
constexpr const char* ARCHIVE_FILE_CONTENT_START = "FILE_CONTENT_START";
constexpr const char* ARCHIVE_FILE_CONTENT_END = "FILE_CONTENT_END";

Archive::Archive( const StringWr& inPath )
{
    m_metadata.Path = inPath;

    m_stream.open( inPath.getValue(), std::ios::in | std::ios::binary );
    constexpr std::size_t buffSize{ 1024 };
    char buff[buffSize];

    m_stream.read( buff, StringUtil::strSize( ARCHIVE_META_MARKER_START ) );
    
    CUL::Assert::simple( StringUtil::equals( buff, ARCHIVE_META_MARKER_START ),
                         "Cannot read ARCHIVE_META_MARKER_START tag." );

    m_stream.read( buff, sizeof( m_metadata.Version ) );
    std::memcpy( &m_metadata.Version, buff, sizeof( m_metadata.Version ) );

    m_stream.read( buff, sizeof( m_metadata.FilesCount ) );
    std::memcpy( &m_metadata.FilesCount, buff, sizeof( m_metadata.FilesCount ) );

    m_stream.read( buff, StringUtil::strSize( ARCHIVE_META_MARKER_END ) );
    CUL::Assert::simple( StringUtil::equals( buff, ARCHIVE_META_MARKER_END ),
                         "Cannot read ARCHIVE_META_MARKER_END tag." );

    for( std::uint64_t i = 0u; i < m_metadata.FilesCount; ++i )
    {
        SFile file;

        m_stream.read( buff, StringUtil::strSize( ARCHIVE_FILE_CONTENT_START ) );
        CUL::Assert::simple( StringUtil::equals( buff, ARCHIVE_FILE_CONTENT_START ),
                             "Cannot read ARCHIVE_FILE_CONTENT_START tag." );

        const std::size_t pathVarSize = sizeof( file.PathSize );
        m_stream.read( buff, pathVarSize );
        std::memcpy( &file.PathSize, buff, sizeof( file.PathSize ) );

        m_stream.read( buff, file.PathSize );
        file.Path = StringWr( buff );

        m_stream.read( buff, sizeof( file.FileSize ) );
        std::memcpy( &file.FileSize, buff, sizeof( file.FileSize ) );

        file.Content = static_cast<char*>( std::malloc( file.FileSize ) );
        m_stream.read( static_cast<char*>( file.Content ), file.FileSize );

        m_stream.read( buff, StringUtil::strSize( ARCHIVE_FILE_CONTENT_END ) );
        CUL::Assert::simple( StringUtil::equals( buff, ARCHIVE_FILE_CONTENT_END ),
                             "Cannot read ARCHIVE_FILE_CONTENT_END tag." );

        m_metadata.Files.push_back( file );
    }
}

Archive::Archive( const SFArchiveMetadata& inMetaCpy, EAccesMode inAccessMode )
{
    SFArchiveMetadata inMeta = inMetaCpy;

    m_stream.open( inMeta.Path.getValue(), std::ios::out | std::ios::binary );
    m_metadata = inMeta;
    m_stream.write( ARCHIVE_META_MARKER_START, StringUtil::strSize( ARCHIVE_META_MARKER_START ) );
    m_stream.write( reinterpret_cast<const char*>( &m_metadata.Version ), sizeof( m_metadata.Version ) );
    m_stream.write( reinterpret_cast<const char*>( &m_metadata.FilesCount ), sizeof( m_metadata.FilesCount ) );
    m_stream.write( ARCHIVE_META_MARKER_END, StringUtil::strSize( ARCHIVE_META_MARKER_END ) );
    for( SFile& file : m_metadata.Files )
    {
        const char* path = file.Path.getUtfChar();
        m_stream.write( ARCHIVE_FILE_CONTENT_START, StringUtil::strSize( ARCHIVE_FILE_CONTENT_START ) );
        file.PathSize = StringUtil::strSize( path );
        m_stream.write( reinterpret_cast<const char*>( &file.PathSize ), sizeof( file.PathSize ) );
        m_stream.write( path, file.PathSize );
        m_stream.write( reinterpret_cast<const char*>( &file.FileSize ), sizeof( file.FileSize ) );
        m_stream.write( reinterpret_cast<const char*>( file.Content ), file.FileSize );

        m_stream.write( ARCHIVE_FILE_CONTENT_END, StringUtil::strSize( ARCHIVE_FILE_CONTENT_END ) );
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