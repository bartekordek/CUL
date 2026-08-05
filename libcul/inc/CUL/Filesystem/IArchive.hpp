#pragma once

#include "CUL/CUL.hpp"
#include "CUL/GenericUtils/NonCopyable.hpp"
#include "CUL/STL_IMPORTS/STD_cstdint.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/String/StringWrapper.hpp"

namespace CUL
{
struct SFile
{
    void* Content{ nullptr };
    std::uint64_t Size{ 0u };
};

class IArchive
{
public:
    CULLib_API IArchive();

    CULLib_API virtual std::vector<SFile> getFileList() const = 0;
    CULLib_API virtual SFile* getFile( const String& inPath ) = 0;
    CULLib_API virtual void addFile( const SFile& inFile ) = 0;

    CUL_NONCOPYABLE( IArchive );

    CULLib_API virtual ~IArchive();

protected:
private:
};
}  // namespace CUL