#include "CUL/JSON/JSONFile.hpp"
#include <nlohmann/json.hpp>
#include "CUL/STL_IMPORTS/STD_fstream.hpp"
#include "CUL/STL_IMPORTS/STD_algorithm.hpp"

namespace CUL::JSON
{
class JSONFile_impl
{
public:
    JSONFile_impl( const StringWr& inPath )
    {
    }

    CUL_NONCOPYABLE( JSONFile_impl );

    INode* parse( const StringWr& inContents )
    {
        m_document = nlohmann::json::parse( inContents.getUtfChar() );
        return parse( m_document );
    }

    INode* parse( const nlohmann::json& value )
    {
        if( value.is_object() )
        {
            ChildrenNodes nodes;
            for( auto it = value.begin(); it != value.end(); ++it )
            {
                const auto& childValue = it.value();
                auto child = parse( childValue );
                child->setName( CUL::StringWr( it.key() ) );
                nodes.push_back( child );
            }

            return new INode( "", nodes );
        }

        if( value.is_array() )
        {
            ChildrenNodes nodes;

            for( std::size_t i = 0; i < value.size(); ++i )
            {
                const auto& element = value[i];
                auto child = parse( element );
                child->setName( "ID_" + std::to_string( i ) );
                nodes.push_back( child );
            }

            return new INode( "", nodes );
        }

        if( value.is_number_integer() )
        {
            return new INode( "", static_cast<int>( value.get<int64_t>() ) );
        }

        if( value.is_number_unsigned() )
        {
            return new INode( "", static_cast<int>( value.get<uint64_t>() ) );
        }

        if( value.is_number_float() )
        {
            return new INode( "", value.get<double>() );
        }

        if( value.is_string() )
        {
            return new INode( "", value.get<std::string>().c_str() );
        }

        if( value.is_boolean() )
        {
            return new INode( "", value.get<bool>() );
        }

        if( value.is_null() )
        {
            return new INode( "", CUL::StringWr( "" ) );
        }

        return nullptr;
    }

    void reset()
    {
        m_document.clear();
    }

    ~JSONFile_impl()
    {
    }

protected:
private:
    nlohmann::json m_document;
};

JSONFile::JSONFile( const StringWr& path, CULInterface* inInterface )
    : IFile( path, inInterface )
{
    m_impl = std::make_unique<JSONFile_impl>( path );
    load( true, true );
}

INode* JSONFile::getChild( const StringWr& inPath )
{
    return m_root->findChild( inPath.getValue() );
}

FS::FileType JSONFile::getType() const
{
    return FS::FileType::TXT;
}

void JSONFile::changePath( const FS::Path& /*newPath*/ )
{
    // m_fileContents->changePath( newPath );
    // IFile::setPath( newPath );
}

void JSONFile::reload( bool /*keepLineEndingCharacter*/ )
{
    // m_keepLineEndingCharacter = keepLineEndingCharacter;
    // m_fileContents->reload( keepLineEndingCharacter );
    // parse();
}

void JSONFile::reload()
{
    // m_fileContents->reload( m_keepLineEndingCharacter );
    // parse();
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
    m_impl->reset();
    delete m_root;
    m_root = nullptr;
}

INode* JSONFile::getRoot() const
{
    return m_root;
}

void JSONFile::parse()
{
    const auto fileContents =
        std::string( m_fileContents.data() ? m_fileContents.data() : "" );
    if( fileContents.empty() )
    {
        m_root = new INode( "", ChildrenNodes() );
        m_root->setName( "root" );
        return;
    }

    m_root = m_impl->parse( StringWr( fileContents ) );

    m_root->setName( "root" );
}

JSONFile::~JSONFile()
{
    delete m_root;
    m_root = nullptr;
    m_fileContents.clear();
}
}  // namespace CUL::JSON