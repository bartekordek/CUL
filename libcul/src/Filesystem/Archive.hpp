#pragma once
#include "CUL/Filesystem/IArchive.hpp"
#include "CUL/STL_IMPORTS/STD_fstream.hpp"

namespace CUL
{
class Archive: public IArchive
{
public:
    Archive( const StringWr& inPath );
    Archive( const SFArchiveMetadata& inMeta, EAccesMode inAccessMode );

    void loadFile( const StringWr& inPath );
    std::vector<SFile> getFileList() const override;
    SFile* getFile( const StringWr& inPath ) override;

    CUL_NONCOPYABLE( Archive );
protected:
private:
    void read();
    void write();


    SFArchiveMetadata m_metadata;
    std::fstream m_stream;
};
}  // namespace CUL