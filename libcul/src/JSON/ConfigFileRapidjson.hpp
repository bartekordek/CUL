#pragma once

#include "CUL/Filesystem/ConfigFile.hpp"
#include "JSON/ImportRapidJSON.hpp"

namespace CUL
{
class ConfigFileRapidJson: public ConfigFile
{
public:
    ConfigFileRapidJson();
    void loadFile( const std::string& inFileName ) override;
    const ConfigNode* getValue( const std::vector<std::string>& path ) const override;

    ConfigFileRapidJson( const ConfigFileRapidJson& arg ) = delete;
    ConfigFileRapidJson( ConfigFileRapidJson&& arg ) noexcept = delete;
    ConfigFileRapidJson& operator=( const ConfigFileRapidJson& arg ) = delete;
    ConfigFileRapidJson& operator=( ConfigFileRapidJson&& arg ) noexcept = delete;

    ~ConfigFileRapidJson();

protected:
private:
    void saveFile( const std::string& inFileName ) override;
    bool addOverwriteValue( const ConfigNode& inValue, const std::vector<std::string>& inPath ) override;

    void fetchObject( const rapidjson::Value::Object& inObject, ConfigNode& inOutNode );
    const ConfigNode* getValueImpl( const std::string& childName, const ConfigNode& node ) const;
    void fetchObject( const std::string& inName, const rapidjson::Value& inObject, ConfigNode& inOutNode );

    rapidjson::Document m_document;
    ConfigNode m_root;
};
}  // namespace CUL