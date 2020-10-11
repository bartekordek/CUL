#include "JSONFileConcrete.hpp"
#include "CUL/Filesystem/FileFactory.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"

using namespace CUL;
using namespace JSON;

JSONFileConcrete::JSONFileConcrete( const String& path ):
    IJSONFile( path ),
    m_fileContents( FS::FileFactory::createRegularFileRawPtr( path ) )
{
}

const FS::Path& JSONFileConcrete::getPath() const
{
    return m_fileContents->getPath();
}

FS::FileType JSONFileConcrete::getType() const
{
    return FS::FileType::TXT;
}

void JSONFileConcrete::changePath( const FS::Path& newPath )
{
    m_fileContents->changePath( newPath );
    IFile::setPath( newPath );
}

void JSONFileConcrete::reload( Cbool keepLineEndingCharacter )
{
    m_fileContents->reload( keepLineEndingCharacter );
    parse();
}

void JSONFileConcrete::load( Cbool keepLineEndingCharacter )
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

const String& JSONFileConcrete::firstLine() const
{
    return m_fileContents->firstLine();
}

const String& JSONFileConcrete::lastLine() const
{
    return m_fileContents->lastLine();
}

const String& JSONFileConcrete::getAsOneString() const
{
    return m_fileContents->getAsOneString();
}

const char** JSONFileConcrete::getContent() const
{
    return m_fileContents->getContent();
}

unsigned JSONFileConcrete::getLinesCount() const
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
    const auto errorCode = m_document.GetParseError();
    if( rapidjson::ParseErrorCode::kParseErrorNone != errorCode )
    {
        const auto message = rapidjson::GetParseError_En( errorCode );
        CUL::Assert::simple( false, message );
    }

    m_root = parse( m_document );
    m_root->setName( "root" );
}

INode* JSONFileConcrete::parse(
    const JValue& value )
{
    if( value.IsObject() )
    {
        ChildrenNodes nodes;
        for( auto& member : value.GetObject() )
        {
            const rapidjson::Value& childValue = member.value;
            auto child = parse( childValue );
            child->setName( member.name.GetString() );
            nodes.push_back( child );
        }

        return new INode( "", nodes );
    }

    else if( value.IsArray() )
    {
        ChildrenNodes nodes;

        unsigned int i = 0;
        for( auto& element: value.GetArray() )
        {
            auto child = parse( element );
            child->setName( "ID_" + std::to_string( i++ ) );
            nodes.push_back( child );
        }

        return new INode( "", nodes );
    }
    else if( value.IsInt() || value.IsInt64() )
    {
        return new INode( "", value.GetInt() );
    }
    else if( value.IsString() )
    {
        return new INode( "", value.GetString() );
    }
    else if( value.IsBool() )
    {
        return new INode( "", value.GetBool() );
    }
    else if( value.IsDouble() )
    {
        return new INode( "", value.GetDouble() );
    }
    else if( value.IsFloat() )
    {
        return new INode( "", value.GetFloat() );
    }

    return nullptr;
}

JSONFileConcrete::~JSONFileConcrete()
{
    delete m_root;
    m_root = nullptr;

    delete m_fileContents;
    m_fileContents = nullptr;
}