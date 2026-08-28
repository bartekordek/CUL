#include "CUL/JSON/JSONFile.hpp"
#include "CUL/JSON/ImportRapidJSON.hpp"
#include "CUL/STL_IMPORTS/STD_fstream.hpp"
#include "CUL/STL_IMPORTS/STD_algorithm.hpp"

namespace CUL::JSON
{

JSONFile::JSONFile( const StringWr& path, CULInterface* inInterface )
    : IFile( path, inInterface )
{
    m_document = std::make_unique<rapidjson::Document>();
    load( true, true );
}

INode* JSONFile::getChild( const StringWr& inPath )
{
    return m_root->findChild(inPath.getValue());
}

FS::FileType JSONFile::getType() const
{
    return FS::FileType::TXT;
}

void JSONFile::changePath( const FS::Path& /*newPath*/ )
{
    //m_fileContents->changePath( newPath );
    //IFile::setPath( newPath );
}

void JSONFile::reload( bool /*keepLineEndingCharacter*/ )
{
    //m_keepLineEndingCharacter = keepLineEndingCharacter;
    //m_fileContents->reload( keepLineEndingCharacter );
    //parse();
}

void JSONFile::reload()
{
    //m_fileContents->reload( m_keepLineEndingCharacter );
    //parse();
}

void JSONFile::load( bool keepLineEndingCharacter, bool removeBottomEmptyLines )
{
    m_keepLineEndingCharacter = keepLineEndingCharacter;
    m_removeBottomEmptyLines = removeBottomEmptyLines;

    m_fileContents.clear();
    std::ifstream infile;
    infile.open( getPath().getPath().getValue(), std::ios::in | std::ios::binary );
    if( infile )
    {
        infile.seekg( 0, std::ios::end );
        const std::streamoff length = infile.tellg();
        infile.seekg( 0, std::ios::beg );

        if( length > 0 )
        {
            m_fileContents.resize( static_cast<size_t>( length ) + 1 );
            infile.read( m_fileContents.data(), length );
            m_fileContents[static_cast<size_t>( length )] = '\0';
        }
        else
        {
            m_fileContents.resize( 1 );
            m_fileContents[0] = '\0';
        }
    }
    infile.close();

    parse();
}

void JSONFile::unload()
{
    m_fileContents.clear();
    m_document.reset();
    delete m_root;
    m_root = nullptr;
}

INode* JSONFile::getRoot() const
{
    return m_root;
}

void JSONFile::parse()
{
    const auto v = m_fileContents.data();
    // auto documentContents = m_fileContents->getAsOneString().getUtfChar();
    m_document->Parse( v );
    const auto errorCode = m_document->GetParseError();
    if( rapidjson::ParseErrorCode::kParseErrorNone != errorCode )
    {
        const auto message = rapidjson::GetParseError_En( errorCode );
        CUL::Assert::simple( false, message );
    }

    m_root = parse( *m_document );
    m_root->setName( "root" );
}

INode* JSONFile::parse( const rapidjson::Value& value )
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
        for( auto& element : value.GetArray() )
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

JSONFile::~JSONFile()
{
    {
        delete m_root;
        m_root = nullptr;
        m_fileContents.clear();
        m_document.reset();
    }
}
}  // namespace CUL::JSON