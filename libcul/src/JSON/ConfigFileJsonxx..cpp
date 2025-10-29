#include "JSON/ConfigFileJsonxx.hpp"
#include "CUL/Filesystem/FileFactory.hpp"
#include "CUL/Filesystem/RegularFile.hpp"
#include "CUL/CULInterface.hpp"

namespace CUL
{
ConfigFileJsonxx::ConfigFileJsonxx()
{
}

void ConfigFileJsonxx::saveFile( const std::string& inFileName )
{
    CUL::String newJson = m_root.write( jsonxx::Format::JSON );
    while( newJson.contains( "\t" ) )
    {
        newJson.replace( "\t", "    " );
    }

    CULInterface* culInterface = CULInterface::getInstance();
    FS::RegularFile* rf = culInterface->getFF()->createRegularFileRawPtr( inFileName );
    std::unique_ptr<FS::RegularFile> file( rf );
    rf->overwriteContents( newJson );
    rf->saveFile();
}

bool ConfigFileJsonxx::addOverwriteValue( const ConfigNode& inValue, const std::vector<std::string>& inPath )
{
    jsonxx::Object* currObj = &m_root;
    jsonxx::Array* currArr{ nullptr };
    jsonxx::Value* currValue{ nullptr };

    const std::size_t pathSize = inPath.size();
    for( std::size_t i = 0u; i < pathSize; ++i )
    {
        const std::string& currentObjName = inPath[i];
        if( currObj )
        {
            if( currObj->has<jsonxx::Boolean>( currentObjName ) )
            {
                currObj->get<jsonxx::Boolean>( currentObjName );
            }
            else if( currObj->has<jsonxx::Number>( currentObjName ) )
            {
                currObj->get<jsonxx::Number>( currentObjName );
            }
            else if( currObj->has<jsonxx::String>( currentObjName ) )
            {
                currObj->get<jsonxx::String>( currentObjName );
            }
            else if( currObj->has<jsonxx::Array>( currentObjName ) )
            {
                currArr = &currObj->get<jsonxx::Array>( currentObjName );
                jsonxx::Value currVal;

                if( inValue.Type == EVarType::String )
                {
                    currVal = std::get<std::string>( inValue.Value );
                }
                else if( inValue.Type == EVarType::Float )
                {
                    currVal = std::get<float>( inValue.Value );
                }
                else if( inValue.Type == EVarType::Double )
                {
                    currVal = std::get<double>( inValue.Value );
                }
                else if( inValue.Type == EVarType::Int32 )
                {
                    currVal = std::get<std::int32_t>( inValue.Value );
                }
                else if( inValue.Type == EVarType::Int64 )
                {
                    currVal = std::get<std::int64_t>( inValue.Value );
                }
                else
                {
                    Assert::check( false, "ConfigFileJsonxx::addOverwriteValue: Unkown value." );
                }
                currArr->append( currVal );
                return true;
            }
        }
        else if( currArr )
        {
            if( i == pathSize - 1u )
            {
                jsonxx::Value currVal;
                currVal = inValue.Value;
                currArr->append( currVal );
                return true;
            }
        }
        else if( currValue )
        {
        }
        else
        {
            Assert::check( false, "NO VALUE!" );
        }
    }

    return false;
}

void ConfigFileJsonxx::loadFile( const std::string& inFileName )
{
    CULInterface* culInterface =  CULInterface::getInstance();
    std::unique_ptr<FS::IFile> file( culInterface->getFF()->createRegularFileRawPtr( inFileName ) );
    file->load( true, false );
    m_root.parse( file->getAsOneString().cStr() );

    m_configRoot.Name = "root";
}

const ConfigNode* ConfigFileJsonxx::getValue( const std::vector<std::string>& path ) const
{
    const std::size_t pathSize = path.size();
    const jsonxx::Object& currentobj = m_root;

    return getValueImpl( m_configRoot, m_root, path, 0u );
}

bool IsNumber(const std::string& inString)
{
    for( const char currChar: inString )
    {
        if( std::isdigit( currChar ) == false )
        {
            return false;
        }
    }

    return true;
}

const ConfigNode* ConfigFileJsonxx::getValueImpl( ConfigNode& parent, const jsonxx::Object& inObj, const std::vector<std::string>& path,
                                                  std::size_t currIndx ) const
{
    const std::size_t pathSize = path.size();
    if( currIndx >= pathSize )
    {
        return nullptr;
    }

    const ConfigNode* result{ nullptr };
    const jsonxx::Object* currObj = &inObj;
    const jsonxx::Array* currArr{ nullptr };
    const jsonxx::Value* currValue{ nullptr };

    for( std::size_t i = 0u; i < pathSize; ++i )
    {
        const std::string& currentObjName = path[i];

        std::optional<NodeResult> childNode;
        if( currObj )
        {
            childNode = jsonNodeToConfigNode( *currObj, currentObjName );
        }
        else if( currArr )
        {
            childNode = jsonArrayToConfigNode( *currArr, currentObjName );
        }
        else if( currValue )
        {
            childNode = jsonValueToConfigNode( *currValue, currentObjName );
        }

        if( childNode.has_value() )
        {
            parent.Children[currentObjName] = childNode->Node;
            if( childNode->Object )
            {
                currObj = childNode->Object;
                currArr = nullptr;
                currValue = nullptr;
            }
            else if( childNode->Array )
            {
                currObj = nullptr;
                currArr = childNode->Array;
                currValue = nullptr;
            }
            else if( childNode->Value )
            {
                currObj = nullptr;
                currArr = nullptr;
                currValue = childNode->Value;
            }

            if( i == ( pathSize - 1u ) )
            {
                result = &parent.Children[currentObjName];
            }
        }
    }

    //const std::string& currentName = path[currIndx];

    //ConfigNode node;
    //node.Name = currentName;
    //if( inObj.has<jsonxx::Boolean>( currentName ) )
    //{
    //    node.Value = inObj.get<jsonxx::Boolean>( currentName );
    //}
    //else if( inObj.has<jsonxx::Number>( currentName ) )
    //{
    //    node.Value = static_cast<double>( inObj.get<jsonxx::Number>( currentName ) );
    //}
    //else if( inObj.has<jsonxx::String>( currentName ) )
    //{
    //    node.Value = inObj.get<jsonxx::String>( currentName );
    //}
    //else if( inObj.has<jsonxx::Array>( currentName ) )
    //{
    //    const jsonxx::Array arrayOut = inObj.get<jsonxx::Array>( currentName );
    //    const std::vector<jsonxx::Value*>& arrayValues = arrayOut.values();
    //    std::int32_t index{ -1 };
    //    if( IsNumber( currentName ) )
    //    {
    //        index = std::stoi( currentName );
    //        const std::size_t valuesCount = arrayValues.size();
    //        if( index >= valuesCount )
    //        {
    //            return nullptr;
    //        }
    //        const jsonxx::Value* targetVal = arrayValues[index];
    //        //const ConfigNode* childNode = getValueImpl( parent, , path, currIndx + 1 );
    //    }
    //    else
    //    {
    //        const std::string subobjectName = path[currIndx + 1u];
    //        if( IsNumber( currentName ) )
    //        {
    //            index = std::stoi( subobjectName );
    //            if( arrayValues.size() < index )
    //            {
    //                jsonxx::Value* subOjb = arrayValues[index];
    //                ConfigNode subNode;
    //                subNode.Name = subobjectName;
    //                subNode
    //                node.Children[subobjectName] = 
    //            }
    //            else
    //            {
    //            }
    //        }
    //        else
    //        {
    //        }
    //        for( const jsonxx::Value* value : arrayValues )
    //        {
    //            const jsonxx::Object& valueObject = value->get<jsonxx::Object>();
    //            const ConfigNode* currNode = getValueImpl( node, valueObject, path, currIndx + 1u );
    //            if( currNode )
    //            {
    //                break;
    //            }
    //            // const ConfigNode* childNode = getValueImpl( parent, , path, currIndx + 1 );
    //        }
    //    }
    //}
    //else if( inObj.has<jsonxx::Object>( currentName ) )
    //{
    //    auto z = 0;
    //}
    //else
    //{
    //    
    //}
    //parent.Children[currentName] = node;
    //const ConfigNode* result = &parent.Children[currentName];
    return result;
}

std::optional<ConfigFileJsonxx::NodeResult> ConfigFileJsonxx::jsonNodeToConfigNode( const jsonxx::Object& inParentNode,
                                                                                  const std::string& childName ) const
{
    ConfigFileJsonxx::NodeResult resultNode;
    resultNode.Node.Name = childName;

    if( inParentNode.has<jsonxx::Boolean>( childName ) )
    {
        resultNode.Node.Value = inParentNode.get<jsonxx::Boolean>( childName );
    }
    else if( inParentNode.has<jsonxx::Number>( childName ) )
    {
        resultNode.Node.Value = static_cast<double>( inParentNode.get<jsonxx::Number>( childName ) );
    }
    else if( inParentNode.has<jsonxx::String>( childName ) )
    {
        resultNode.Node.Value = inParentNode.get<jsonxx::String>( childName );
    }
    else if( inParentNode.has<jsonxx::Array>( childName ) )
    {
        resultNode.Array = &inParentNode.get<jsonxx::Array>( childName );
        const auto arraySize = resultNode.Array->size();

        for( std::size_t i = 0u; i < arraySize; ++i )
        {
        }
    }
    else if( inParentNode.has<jsonxx::Object>( childName ) )
    {
        auto z = 0;
    }
    else
    {
    }

    return resultNode;
}

std::optional<ConfigFileJsonxx::NodeResult> ConfigFileJsonxx::jsonArrayToConfigNode( const jsonxx::Array& inArray,
                                                                                    const std::string& childName ) const
{
    ConfigFileJsonxx::NodeResult resultNode;
    resultNode.Node.Name = childName;
    const std::vector<jsonxx::Value*>& arrayValues = inArray.values();
    if( IsNumber( childName ) )
    {
        const std::int32_t index = std::stoi( childName );
        const jsonxx::Value* currVal = arrayValues[index];
        resultNode.Value = currVal;
    }
    else
    {
        Assert::check( false, "ConfigFileJsonxx::jsonArrayToConfigNode, %s is not a number.", childName.c_str() );
    }


    return resultNode;
}

std::optional<ConfigFileJsonxx::NodeResult> ConfigFileJsonxx::jsonValueToConfigNode( const jsonxx::Value& inValue,
                                                                                     const std::string& childName ) const
{
    ConfigFileJsonxx::NodeResult resultNode;
    resultNode.Node.Name = childName;
    resultNode.Value = &inValue;

    if( inValue.is<jsonxx::Boolean>() )
    {
        resultNode.Node.Value = inValue.get<jsonxx::Boolean>();
    }
    else if( inValue.is<jsonxx::Number>() )
    {
        resultNode.Node.Value = static_cast<double>( inValue.get<jsonxx::Number>() );
    }
    else if( inValue.is<jsonxx::String>() )
    {
        resultNode.Node.Value = inValue.get<jsonxx::String>();
    }
    else if( inValue.is<jsonxx::Object>() )
    {
        resultNode.Object = &inValue.get<jsonxx::Object>();
        std::optional<NodeResult> nodeValue = jsonNodeToConfigNode( *resultNode.Object, childName );
        if( nodeValue )
        {
            resultNode.Node.Value = nodeValue->Node.Value;
        }
    }
    else
    {
        Assert::check( false, "Wrong type of value." );
    }

    return resultNode;
}

bool* ConfigFileJsonxx::objectToBool( const jsonxx::Object& inObj ) const
{

    return nullptr;
}

double* ConfigFileJsonxx::objectToNumber( const jsonxx::Object& inObj ) const
{
    return nullptr;
}

std::string* ConfigFileJsonxx::objectToString( const jsonxx::Object& inObj ) const
{
    return nullptr;
}

ConfigFileJsonxx::~ConfigFileJsonxx()
{
}
}