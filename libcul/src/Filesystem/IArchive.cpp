#include "CUL/Filesystem/IArchive.hpp"
#include "CUL/STL_IMPORTS/STD_fstream.hpp"

namespace CUL
{
void SFile::setFile( const std::string& inPath )
{
    m_path = inPath;

    std::ifstream stream( inPath, std::ios::binary | std::ios::ate );
    m_content.resize( static_cast<std::uint64_t>( stream.tellg() ) );
    stream.seekg( 0, std::ios::beg );
    stream.read( reinterpret_cast<char*>( m_content.data() ),
                 static_cast<std::streamsize>( m_content.size() ) );
}

const std::string& SFile::getPath() const
{
    return m_path;
}

std::uint64_t SFile::getPathSize() const
{
    return m_path.size() * sizeof( char );
}

const std::vector<std::byte>& SFile::getContent() const
{
    return m_content;
}

std::vector<std::byte>& SFile::getContent()
{
    return m_content;
}

void SFile::setPath( const std::string& inPath )
{
    m_path = inPath;
}

IArchive::~IArchive()
{
}
}  // namespace CUL