#include "JSON/ConfigFileRapidjson.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/STL_IMPORTS/STD_fstream.hpp"

namespace CUL
{
ConfigFileRapidJson::ConfigFileRapidJson()
{
}

void ConfigFileRapidJson::loadFile( const std::string& inFileName )
{
    std::ifstream t( inFileName );
    std::string str( ( std::istreambuf_iterator<char>( t ) ), std::istreambuf_iterator<char>() );
    m_document.Parse( str.c_str() );

    // m_root
    rapidjson::Value::Object documentRootObj = m_document.GetObject();
    m_root.Name = "root";
    fetchObject( documentRootObj, m_root );
}

void ConfigFileRapidJson::saveFile( const std::string& inFileName )
{
}

bool ConfigFileRapidJson::addOverwriteValue( const ConfigNode& inValue, const std::vector<std::string>& inPath )
{
    return false;
}

void ConfigFileRapidJson::fetchObject( const rapidjson::Value::Object& inObject, ConfigNode& inOutNode )
{
    for( const auto& documentChildren : inObject )
    {
        fetchObject( documentChildren.name.GetString(), documentChildren.value, inOutNode );
    }
}

void ConfigFileRapidJson::fetchObject( const std::string& inName, const rapidjson::Value& inObject, ConfigNode& inOutNode )
{
    ConfigNode childNode;
    childNode.Name = inName;
    if( inObject.IsInt() )
    {
        childNode.Value = inObject.GetInt();
    }
    else if( inObject.IsString() )
    {
        childNode.Value = inObject.GetString();
        if( inName.empty() )
        {
            childNode.Name = inObject.GetString();
        }
    }
    else if( inObject.IsArray() )
    {
        const auto objArray = inObject.GetArray();
        std::size_t arrayIndex = 0u;
        for( const auto& arrayElement : objArray )
        {
            fetchObject( std::to_string( arrayIndex++ ), arrayElement, childNode );
        }
    }
    else if( inObject.IsObject() )
    {
        const auto obj = inObject.GetObject();
        for( const auto& child : obj )
        {
            fetchObject( child.name.GetString(), child.value, childNode );
        }
    }
    else
    {
        Assert::check( false, "Value of type %d is not implemented.", static_cast<std::int32_t>( inObject.GetType() ) );
    }
    inOutNode.Children[childNode.Name] = childNode;
}

const ConfigNode* ConfigFileRapidJson::getValue( const std::vector<std::string>& paths ) const
{
    const ConfigNode* result{ &m_root };

    for( const std::string& pathPart : paths )
    {
        if( const ConfigNode* currentValue = getValueImpl( pathPart, *result ) )
        {
            result = currentValue;
        }
        else
        {
            result = nullptr;
            break;
        }
    }

    return result;
}

const ConfigNode* ConfigFileRapidJson::getValueImpl( const std::string& childName, const ConfigNode& node ) const
{
    if( node.Children.contains( childName ) )
    {
        const ConfigNode& result = node.Children.at( childName );
        return &result;
    }
    return nullptr;
}

ConfigFileRapidJson::~ConfigFileRapidJson()
{
}
}  // namespace CUL
