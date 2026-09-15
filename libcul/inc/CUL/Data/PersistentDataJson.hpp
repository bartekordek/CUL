#pragma once

#include <CUL/Data/PersistentData.hpp>
#include <CUL/STL_IMPORTS/STD_memory.hpp>

namespace CUL
{
class PersistentDataJson_impl;
class PersistentDataJson: public IPersistendData
{
public:
    PersistentDataJson();
    void init( const StringWr& inDataPath );

    void setValue( const StringWr& inPath, const TypeContainer& inValue );
    TypeContainer getValue( const StringWr& inPath ) const;

    void addNode( const StringWr& inPath, const DataNode& node );
    void writeToFile();
    ~PersistentDataJson();

protected:
private:
    std::unique_ptr<PersistentDataJson_impl> m_impl;
    
};
}  // namespace CUL