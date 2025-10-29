#pragma once

#include "CUL/CUL.hpp"
#include "CUL/STL_IMPORTS/STD_string.hpp"
#include "CUL/STL_IMPORTS/STD_map.hpp"
#include "CUL/STL_IMPORTS/STD_memory.hpp"
#include "CUL/STL_IMPORTS/STD_variant.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"

namespace CUL
{
enum class EParserType: std::uint8_t
{
    Jsonxx,
    Rapidjson
};

enum class EVarType : std::uint8_t
{
    None = 0u,
    String,
    Float,
    Double,
    Int32,
    Int64
};

struct CULLib_API ConfigNode
{
    std::string Name;
    std::variant<std::string, float, double, std::int32_t, std::int64_t> Value;
    EVarType Type{ EVarType::None };
    std::map<std::string, ConfigNode> Children;

    //auto getType(EVarType inType) const
    //{
    //    else if( inType == EVarType::Float )
    //    {
    //        return std::get<float>( Value );
    //    }
    //    else if( inType == EVarType::Int32 )
    //    {
    //        return std::get<std::int32_t>( Value );
    //    }
    //    else 
    //    {
    //        return std::get<td::int64_t>( Value );
    //    }
    //}
};

class CULLib_API ConfigFile
{
public:
    static std::unique_ptr<ConfigFile> createFile( EParserType inParserType );


    ConfigFile();
    virtual void loadFile( const std::string& inFileName ) = 0;
    virtual void saveFile( const std::string& inFileName ) = 0;
    virtual const ConfigNode* getValue( const std::vector<std::string>& path ) const = 0;
    virtual bool addOverwriteValue( const ConfigNode& inValue, const std::vector<std::string>& inPath ) = 0;

    ConfigFile( const ConfigFile& arg ) = delete;
    ConfigFile( ConfigFile&& arg ) noexcept = delete;

    ConfigFile& operator=( const ConfigFile& arg ) = delete;
    ConfigFile& operator=( ConfigFile&& arg ) noexcept = delete;
    virtual ~ConfigFile();

protected:

    

private:

};
}  // namespace CUL