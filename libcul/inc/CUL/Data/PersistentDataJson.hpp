#pragma once

#include <CUL/Data/PersistentData.hpp>
#include <CUL/STL_IMPORTS/STD_memory.hpp>

namespace CUL
{
class PersistentDataJson_impl;
class PersistentDataJson: public IPersistendData
{
public:
    CULLib_API PersistentDataJson();
    CULLib_API void init( const StringWr& inDataPath );

    CULLib_API void setValue( const StringWr& inPath, const TypeContainer& inValue );
    CULLib_API TypeContainer getValue( const StringWr& inPath ) const;

    CULLib_API void addNode( const StringWr& inPath, const DataNode& node );
    CULLib_API void writeToFile();
    CULLib_API ~PersistentDataJson();

protected:
private:
    std::unique_ptr<PersistentDataJson_impl> m_impl;
};
}  // namespace CUL