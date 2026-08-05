#pragma once

#include "CUL/CUL.hpp"
#include "CUL/GenericUtils/NonCopyable.hpp"
#include "CUL/STL_IMPORTS/STD_cstdint.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/String/StringWrapper.hpp"

namespace CUL
{
enum class EAccesMode : std::uint8_t
{
    Read = 0u,
    Write
};

struct SFile
{
    std::uint64_t PathSize{ 0u };
    StringWr Path;
    std::uint64_t FileSize{ 0u };
    void* Content{ nullptr };
};

struct SFArchiveMetadata
{
    StringWr Path;
    std::uint32_t Version{ 0u };
    std::uint32_t FilesCount{ 0u };
    std::vector<SFile> Files;
};

class IArchive
{
public:
    CULLib_API IArchive() = default;
    CULLib_API virtual std::vector<SFile> getFileList() const = 0;
    CULLib_API virtual SFile* getFile( const StringWr& inPath ) = 0;

    CUL_NONCOPYABLE( IArchive );

    CULLib_API virtual ~IArchive();

protected:
private:
};
}  // namespace CUL