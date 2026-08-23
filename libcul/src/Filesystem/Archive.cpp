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

using FileSizeType = std::uint64_t;
constexpr std::size_t sizeOfChar = sizeof( char );

template <typename T>
requires std::is_trivial_v<T>
T readValue( std::fstream& inStream )
{
    T result;
    inStream.read( reinterpret_cast<char*>( &result ), sizeof( T ) );
    return result;
}

template <typename T>
requires std::is_trivial_v<T>
void writeValue( std::fstream& inStream, T inValue )
{
    constexpr std::size_t bufferSize{ 512u };
    char buffer[bufferSize];
    const std::size_t sizeofT = sizeof( T );
    const auto charNormalizedSize = static_cast<std::streamsize>( sizeofT / sizeOfChar );
    inStream.write( reinterpret_cast<const char*>( &inValue ), charNormalizedSize );
}

void writeData( std::fstream& inOutStream, const std::vector<std::byte>& inData )
{
    const std::uint64_t dataSize = static_cast<std::uint64_t>( inData.size() );
    writeValue( inOutStream, dataSize );
    inOutStream.write( reinterpret_cast<const char*>( inData.data() ),
                       static_cast<std::streamsize>( dataSize ) );
}

void readData( std::fstream& inOutStream, std::vector<std::byte>& inOutData )
{
    const std::uint64_t dataSize = readValue<std::uint64_t>( inOutStream );
    inOutData.resize( dataSize );
    inOutStream.read( reinterpret_cast<char*>( inOutData.data() ),
                      static_cast<std::streamsize>( dataSize ) );
}

StringWr readString( std::fstream& inStream )
{
    // Read string length.
    std::uint32_t lengthOfStringInBytes{ 0u };
    inStream.read( reinterpret_cast<char*>( &lengthOfStringInBytes ),
                   sizeof( decltype( lengthOfStringInBytes ) ) );

    std::vector<char> stringBuffer( lengthOfStringInBytes );

    // ReadString
    inStream.read( stringBuffer.data(), lengthOfStringInBytes );
    return StringWr( stringBuffer.data() );
}

void writeString( std::fstream& inStream, const StringWr& inString )
{
    const std::uint32_t lengthOfStringInBytes =
        static_cast<std::uint32_t>( StringUtil::strSize( inString.getUtfChar() ) );
    // Write string length.
    inStream.write( reinterpret_cast<const char*>( &lengthOfStringInBytes ),
                    sizeof( decltype( lengthOfStringInBytes ) ) );
    // Write string content.
    inStream.write( inString.getUtfChar(), lengthOfStringInBytes );
}

Archive::Archive( const StringWr& inPath )
{
    m_metadata.Path = inPath;
    read();
}

Archive::Archive( const SFArchiveMetadata& inMetaCpy, EAccesMode /*inAccessMode*/ )
{
    m_metadata = inMetaCpy;
    write();
}

void Archive::write()
{
    m_stream.open( m_metadata.Path.getValue(), std::ios::out | std::ios::binary );

    writeString( m_stream, ARCHIVE_META_MARKER_START );
    writeValue( m_stream, m_metadata.Version );
    writeValue( m_stream, m_metadata.FilesCount );
    writeString( m_stream, ARCHIVE_META_MARKER_END );

    for( const SFile& file : m_metadata.Files )
    {
        writeString( m_stream, ARCHIVE_FILE_CONTENT_START );
        writeString( m_stream, file.getPath() );
        writeData( m_stream, file.getContent() );
        writeString( m_stream, ARCHIVE_FILE_CONTENT_END );
    }
    m_stream.close();
}
void Archive::read()
{
    m_stream.open( m_metadata.Path.getValue(), std::ios::in | std::ios::binary );
    const auto markerStart = readString(m_stream);
    CUL::Assert::simple( markerStart.equals( ARCHIVE_META_MARKER_START ),
                         "Cannot read ARCHIVE_META_MARKER_START tag." );

    m_metadata.Version = readValue<decltype( m_metadata.Version )>( m_stream );
    m_metadata.FilesCount = readValue<decltype( m_metadata.FilesCount )>( m_stream );

    const auto markerEnd = readString( m_stream );
    CUL::Assert::simple( markerEnd.equals( ARCHIVE_META_MARKER_END ),
                         "Cannot read ARCHIVE_META_MARKER_END tag." );

    for( std::uint64_t i = 0u; i < m_metadata.FilesCount; ++i )
    {
        SFile file;
        const auto contentStart = readString( m_stream );
        contentStart.equals( ARCHIVE_FILE_CONTENT_START );
        CUL::Assert::simple( contentStart.equals( ARCHIVE_FILE_CONTENT_START ), "Cannot read ARCHIVE_FILE_CONTENT_START tag." );
        file.setPath( readString( m_stream ).getSTDString() );
        std::vector<std::byte>& content = file.getContent();
        readData( m_stream, content );

        const auto contentEnd = readString( m_stream );
        contentEnd.equals( ARCHIVE_FILE_CONTENT_END );
        m_metadata.Files.push_back( file );
    }
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
        if( inPath.equals( file.getPath() ) )
        {
            return &file;
        }
    }
    return nullptr;
}

}  // namespace CUL