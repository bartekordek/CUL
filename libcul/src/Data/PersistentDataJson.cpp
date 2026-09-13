#include <CUL/Data/PersistentDataJson.hpp>
#include <CUL/Filesystem/Path.hpp>
#include <nlohmann/json.hpp>
#include <CUL/STL_IMPORTS/STD_fstream.hpp>

namespace CUL
{

std::vector<StringWr> splitPath( const StringWr& inPath )
{
    return inPath.split( CUL_CHAR( '/' ) );
}

class PersistentDataJson_impl
{
public:
    PersistentDataJson_impl() = default;

    void init( const StringWr& inDataPath )
    {
        FS::Path path( inDataPath );
        if( !path.getExtension().equals( CUL_STR( "json" ) ) )
        {
            path += CUL_STR( ".json" );
        }
        m_path = path.getPath();
    }

    void addNode( const StringWr& inPath, const DataNode& node )
    {
        const std::vector<StringWr> path = splitPath( inPath );

        nlohmann::json* current = &m_document;
        for( const StringWr& currentPathPart : path )
        {
            current = &( *current )[currentPathPart.getUtfChar()];
        }

        const auto memberName = node.Name.getUtfChar();

        if( std::holds_alternative<bool>( node.Value ) )
        {
            ( *current )[memberName] = std::get<bool>( node.Value );
        }
        else if( std::holds_alternative<std::int64_t>( node.Value ) )
        {
            ( *current )[memberName] = std::get<std::int64_t>( node.Value );
        }
        else if( std::holds_alternative<std::uint64_t>( node.Value ) )
        {
            ( *current )[memberName] = std::get<std::uint64_t>( node.Value );
        }
        else if( std::holds_alternative<float>( node.Value ) )
        {
            ( *current )[memberName] = std::get<float>( node.Value );
        }
        else if( std::holds_alternative<StringWr>( node.Value ) )
        {
            ( *current )[memberName] = std::get<StringWr>( node.Value ).getUtfChar();
        }
        else
        {
            ( *current )[memberName] = nlohmann::json::object();
        }
    }

    void writeToFile()
    {
        std::ofstream file( m_path.getUtfChar() );
        if( !file )
        {
            return;
        }
        file << m_document.dump( 4 );
    }

    ~PersistentDataJson_impl() = default;

protected:
private:
    nlohmann::json m_document;
    StringWr m_path;
};

PersistentDataJson::PersistentDataJson()
    : m_impl( std::make_unique<PersistentDataJson_impl>() )
{

}

void PersistentDataJson::init( const StringWr& inDataPath )
{
    m_impl->init( inDataPath );
}

void PersistentDataJson::addNode( const StringWr& inPath, const DataNode& node )
{
    m_impl->addNode( inPath, node );
}

void PersistentDataJson::writeToFile()
{
    m_impl->writeToFile();
}

PersistentDataJson::~PersistentDataJson()
{
}
}  // namespace CUL