#pragma once

#include <CUL/String/StringWrapper.hpp>
#include <CUL/GenericUtils/NonCopyable.hpp>
#include <CUL/STL_IMPORTS/STD_memory.hpp>
#include <CUL/STL_IMPORTS/STD_optional.hpp>

namespace CUL
{
struct FileMeta
{
    StringWr Path;
    StringWr MD5;
    std::uint64_t Size;
};

class IFileDb
{
public:
    IFileDb() = default;

    CUL_NONCOPYABLE( IFileDb );

    static std::unique_ptr<IFileDb> createJsonImpl();

    virtual void load(const StringWr& inDbPath ) = 0;
    virtual void addFile( const FileMeta& meta ) = 0;
    virtual std::optional<FileMeta> getFile( const StringWr& path ) = 0;
    virtual ~IFileDb() = default;

protected:
private:
};
}  // namespace CUL