#include "JSONFileConcrete.hpp"
#include "CUL/Filesystem/FileFactory.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/JSON/Array.hpp"
#include "CUL/JSON/DataPair.hpp"

using namespace CUL;
using namespace JSON;

JSONFileConcrete::JSONFileConcrete():
    m_fileContents( FS::FileFactory::createRegularFileRawPtr() )
{
}

JSONFileConcrete::~JSONFileConcrete()
{
    delete m_root;
    m_root = nullptr;

    delete m_fileContents;
    m_fileContents = nullptr;
}

const FS::Path& JSONFileConcrete::getPath() const
{
    return m_fileContents->getPath();
}

CBool JSONFileConcrete::exists() const
{
    return m_fileContents->exists();
}

CBool JSONFileConcrete::isBinary() const
{
    return m_fileContents->isBinary();
}

void JSONFileConcrete::changePath( const FS::Path& newPath )
{
    m_fileContents->changePath( newPath );
}

void JSONFileConcrete::reload( CBool keepLineEndingCharacter )
{
    m_fileContents->reload( keepLineEndingCharacter );
    parse();
}

void JSONFileConcrete::load( CBool keepLineEndingCharacter )
{
    m_fileContents->load( keepLineEndingCharacter );
    parse();
}

void JSONFileConcrete::unload()
{
    m_fileContents->unload();
    delete m_root;
    m_root = nullptr;
}

CsStr& JSONFileConcrete::firstLine() const
{
    return m_fileContents->firstLine();
}

CsStr& JSONFileConcrete::lastLine() const
{
    return m_fileContents->lastLine();
}

CsStr& JSONFileConcrete::getAsOneString() const
{
    return m_fileContents->getAsOneString();
}

const char** JSONFileConcrete::getContent() const
{
    return m_fileContents->getContent();
}

cunt JSONFileConcrete::getLinesCount() const
{
    return m_fileContents->getLinesCount();
}

INode* JSONFileConcrete::getRoot() const
{
    return m_root;
}

void JSONFileConcrete::parse()
{
    auto documentContents = m_fileContents->getAsOneString().cStr();
    m_document.Parse( documentContents );
    auto errorCode = m_document.GetParseError();
    if( rapidjson::ParseErrorCode::kParseErrorNone != errorCode )
    {
        auto message = rapidjson::GetParseError_En( errorCode );
        CUL::Assert::simple( false, message );
    }

    parse( "root", m_document );
}

void JSONFileConcrete::parse(
    CsStr& valueName,
    const JValue& parentValue,
    INode* parentNode )
{
    INode* obj = nullptr;
    if( parentValue.IsObject() )
    {
        obj = new Object( valueName );
        for( auto& member : parentValue.GetObject() )
        {
            const rapidjson::Value& childValue = member.value;
            CsStr memberName = member.name.GetString();
            parse( memberName, childValue, obj );
        }
    }
    else if( parentValue.IsArray() )
    {
        auto array = new Array( valueName );
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
        m_root = obj;
    }
    else
    {
        parentNode->addChild( obj );
    }
}