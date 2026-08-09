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

class SFile
{
public:
    CULLib_API void setFile( const std::string& inPath );
    CULLib_API const std::string& getPath() const;
    CULLib_API std::uint64_t getPathSize() const;

    CULLib_API const std::vector<std::byte>& getContent() const;
    CULLib_API std::vector<std::byte>& getContent();
    CULLib_API void setPath( const std::string& inPath );


protected:
private:
    std::string m_path;
    std::vector<std::byte> m_content;
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