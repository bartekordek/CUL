#pragma once

#include <CUL/String/StringWrapper.hpp>
#include <CUL/GenericUtils/NonCopyable.hpp>
#include <CUL/STL_IMPORTS/STD_memory.hpp>

namespace CUL
{


struct DataNode
{
    StringWr Name;
    std::variant<StringWr,
                 std::uint64_t,
                 std::int64_t,
                 float,
                 bool,
                 std::unique_ptr<DataNode>>
        Value;
};

class IPersistendData
{
public:
    IPersistendData() = default;
    CUL_NONCOPYABLE( IPersistendData );

    virtual ~IPersistendData() = default;

protected:
private:
};
}  // namespace CUL