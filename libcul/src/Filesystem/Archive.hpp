#include "CUL/Filesystem/IArchive.hpp"

namespace CUL
{
class Archive: public IArchive
{
public:
    CUL_NONCOPYABLE( Archive );

protected:
private:
    std::vector<SFile> getFileList() const override;
    SFile* getFile( const String& inPath ) override;
    virtual void addFile( const SFile& inFile ) override;
};
}  // namespace CUL