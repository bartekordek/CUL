#include "CUL/Filesystem/ConfigFile.hpp"
#include "JSON/ConfigFileJsonxx.hpp"
#include "JSON/ConfigFileRapidjson.hpp"

namespace CUL
{
std::unique_ptr<ConfigFile> ConfigFile::createFile( EParserType inParserType )
{
    std::unique_ptr<ConfigFile> result;
    if(inParserType == EParserType::Jsonxx)
    {
        result.reset( new ConfigFileJsonxx() );
    }
    else if(inParserType == EParserType::Rapidjson)
    {
        result.reset( new ConfigFileRapidJson );
    }

    return result;
}

ConfigFile::ConfigFile()
{
}

ConfigFile::~ConfigFile()
{
}
}  // namespace CUL
// namespace CUL