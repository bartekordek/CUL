#pragma once
#include "CUL/Filesystem/ConfigFile.hpp"
#include "JSON/ImportJsonXX.hpp"
#include  "CUL/STL_IMPORTS/STD_optional.hpp"

namespace CUL
{
class ConfigFileJsonxx: public ConfigFile
{
public:
    ConfigFileJsonxx();

    ConfigFileJsonxx( const ConfigFileJsonxx& arg ) = delete;
    ConfigFileJsonxx( ConfigFileJsonxx&& arg ) noexcept = delete;
    ConfigFileJsonxx& operator=( const ConfigFileJsonxx& arg ) = delete;
    ConfigFileJsonxx& operator=( ConfigFileJsonxx&& arg ) noexcept = delete;

     ~ConfigFileJsonxx();

protected:
private:
    struct NodeResult
    {
        ConfigNode Node;
        const jsonxx::Object* Object{ nullptr };
        const jsonxx::Value* Value{ nullptr };
        const jsonxx::Array* Array{ nullptr };
    };

    void saveFile( const std::string& inFileName ) override;
    bool addOverwriteValue( const ConfigNode& inValue, const std::vector<std::string>& inPath ) override;
    
    void loadFile( const std::string& inFileName ) override;
    const ConfigNode* getValue( const std::vector<std::string>& path ) const override;
    const ConfigNode* getValueImpl( ConfigNode& parent,
        const jsonxx::Object& inObj,
        const std::vector<std::string>& path,
        std::size_t currIndx ) const;
    std::optional<NodeResult> jsonNodeToConfigNode( const jsonxx::Object& inParentNode, const std::string& childName ) const;
    std::optional<NodeResult> jsonArrayToConfigNode( const jsonxx::Array& inParentNode, const std::string& childName ) const;
    std::optional<NodeResult> jsonValueToConfigNode( const jsonxx::Value& inParentNode, const std::string& childName ) const;

    bool* objectToBool( const jsonxx::Object& inObj ) const;
    double* objectToNumber( const jsonxx::Object& inObj ) const;
    std::string* objectToString( const jsonxx::Object& inObj ) const;

    jsonxx::Object m_root;
    mutable ConfigNode m_configRoot;
};

}