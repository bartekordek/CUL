#pragma once

#include "CUL/CUL.hpp"
#include "CUL/GenericUtils/NonCopyable.hpp"
#include "CUL/STL_IMPORTS/STD_cstdint.hpp"
#include "CUL/STL_IMPORTS/STD_memory.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"

namespace CUL
{
class IArchive;
class STDStringWrapper;
using StringWr = STDStringWrapper;
enum class EAccesMode : std::uint8_t;
struct SFArchiveMetadata;

class Archiver
{
public:
    CULLib_API static Archiver& getInstance();
    IArchive& createArchive( const SFArchiveMetadata& inMeta, EAccesMode inAccessMode );
    IArchive& readArchive( const StringWr& inPath );

    CUL_NONCOPYABLE( Archiver );

protected:
private:
    Archiver();
    ~Archiver();
    std::vector<std::unique_ptr<IArchive>> m_archives;

};
}  // namespace CUL