#include "CUL/Filesystem/Archiver.hpp"
#include "Filesystem/Archive.hpp"

namespace CUL
{
Archiver& Archiver::getInstance()
{
    static Archiver staticInstance;
    return staticInstance;
}

IArchive& Archiver::createArchive( const SFArchiveMetadata& inMeta, EAccesMode inAccessMode )
{
    std::unique_ptr<Archive> archive( new Archive( inMeta, inAccessMode ) );
    m_archives.push_back( std::move( archive ) );
    return *m_archives.back();
}

IArchive& Archiver::readArchive( const StringWr& inPath )
{
    std::unique_ptr<Archive> archive( new Archive( inPath ) );
    m_archives.push_back( std::move( archive ) );
    return *m_archives.back();
}

Archiver::Archiver()
{
}

Archiver::~Archiver()
{
}
}  // namespace CUL