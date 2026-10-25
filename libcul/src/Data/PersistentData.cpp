#include <CUL/Data/PersistentData.hpp>

namespace CUL
{
const DataNode* DataNode::findChild( const StringWr& inName ) const
{
    const auto* children = Value.getIf<std::vector<std::unique_ptr<DataNode>>>();
    if( !children )
    {
        return nullptr;
    }

    for( const std::unique_ptr<DataNode>& child : *children )
    {
        if( child && child->Name == inName )
        {
            return child.get();
        }
    }

    return nullptr;
}

DataNode* DataNode::findChild( const StringWr& inName )
{
    return const_cast<DataNode*>( static_cast<const DataNode*>( this )->findChild( inName ) );
}
}  // namespace CUL