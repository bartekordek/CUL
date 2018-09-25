#include "JSONFileConcrete.hpp"
#include "CUL/FileFactory.hpp"
#include "CUL/SimpleAssert.hpp"
#include "CUL/JSON/Array.hpp"
#include "CUL/JSON/DataPair.hpp"

using namespace CUL;
using namespace JSON;

JSONFileConcrete::JSONFileConcrete( void ):
    m_fileContents( FS::FileFactory::createRegularFile() )
{
}

JSONFileConcrete::~JSONFileConcrete( void )
{
    delete this->m_root;
    this->m_root = nullptr;

    delete this->m_fileContents;
    this->m_fileContents = nullptr;
}

const FS::Path& JSONFileConcrete::getPath() const
{
    return this->m_fileContents->getPath();
}

CBool JSONFileConcrete::exists() const
{
    return this->m_fileContents->exists();
}

CBool JSONFileConcrete::isBinary() const
{
    return this->m_fileContents->isBinary();
}

void JSONFileConcrete::changePath( const FS::Path& newPath )
{
    this->m_fileContents->changePath( newPath );
}

void JSONFileConcrete::reload( CBool keepLineEndingCharacter )
{
    this->m_fileContents->reload( keepLineEndingCharacter );
    parse();
}

void JSONFileConcrete::load( CBool keepLineEndingCharacter )
{
    this->m_fileContents->load( keepLineEndingCharacter );
    parse();
}

void JSONFileConcrete::unload()
{
    this->m_fileContents->unload();
    delete this->m_root;
    this->m_root = nullptr;
}

CnstMyStr& JSONFileConcrete::firstLine() const
{
    return this->m_fileContents->firstLine();
}

CnstMyStr& JSONFileConcrete::lastLine() const
{
    return this->m_fileContents->lastLine();
}

CnstMyStr& JSONFileConcrete::getAsOneString() const
{
    return this->m_fileContents->getAsOneString();
}

const char** JSONFileConcrete::getContent() const
{
    return this->m_fileContents->getContent();
}

cunt JSONFileConcrete::getLinesCount() const
{
    return this->m_fileContents->getLinesCount();
}

INode* JSONFileConcrete::getRoot() const
{
    return this->m_root;
}

void JSONFileConcrete::parse()
{
    auto documentContents = this->m_fileContents->getAsOneString().c_str();
    m_document.Parse( documentContents );
    auto errorCode = m_document.GetParseError();
    if( rapidjson::ParseErrorCode::kParseErrorNone != errorCode )
    {
        auto message = rapidjson::GetParseError_En( errorCode );
        CUL::Assert::simple( false, message );
    }

    parse( "root", m_document );
}

void JSONFileConcrete::parse( CnstMyStr& valueName, const JValue& parentValue, INode* parentNode )
{
    INode* obj = nullptr;
    if( parentValue.IsObject() )
    {
        obj = new Object( valueName );
        for( auto& member : parentValue.GetObject() )
        {
            const rapidjson::Value& childValue = member.value;
            CnstMyStr memberName = member.name.GetString();
            parse( memberName, childValue, obj );
        }
    }
    else if( parentValue.IsArray() )
    {
        auto array = new Array();
        for( auto& element : parentValue.GetArray() )
        {
            parse( "", element, array );
        }
        obj = array;
    }
    else if( parentValue.IsBool() )
    {
        auto valIntermediate = parentValue.GetBool();
        auto val = std::to_string( valIntermediate );
        obj = new DataPair( valueName, val );
    }
    else if( parentValue.IsDouble() )
    {
        auto valIntermediate = parentValue.GetDouble();
        auto val = std::to_string( valIntermediate );
        obj = new DataPair( valueName, val );
    }
    else if( parentValue.IsFloat() )
    {
        auto valIntermediate = parentValue.GetFloat();
        auto val = std::to_string( valIntermediate );
        obj = new DataPair( valueName, val );
    }
    else if( parentValue.IsInt() )
    {
        auto valIntermediate = parentValue.GetInt();
        auto val = std::to_string( valIntermediate );
        obj = new DataPair( valueName, val );
    }
    else if( parentValue.IsInt64() )
    {
        auto valIntermediate = parentValue.GetInt64();
        auto val = std::to_string( valIntermediate );
        obj = new DataPair( valueName, val );
    }
    else if( parentValue.IsString() )
    {
        auto val = parentValue.GetString();
        obj = new DataPair( valueName, val );
    }

    if( nullptr == parentNode )
    {
        this->m_root = obj;
    }
    else
    {
        parentNode->addChild( obj );
    }
}