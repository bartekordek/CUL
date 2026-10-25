#include <CUL/Data/PersistentDataJson.hpp>
#include <CUL/Filesystem/Path.hpp>
#include <CUL/GenericUtils/SimpleAssert.hpp>
#include <nlohmann/json.hpp>
#include <CUL/STL_IMPORTS/STD_fstream.hpp>
#include <CUL/STL_IMPORTS/STD_shared_mutex.hpp>

namespace CUL
{

std::vector<StringWr> splitPath( const StringWr& inPath )
{
    // Logical JSON paths always use '/', independent of the OS directory separator.
    return inPath.split( CUL_CHAR( '/' ) );
}

class PersistentDataJson_impl
{
public:
    PersistentDataJson_impl() = default;
    CUL_NONCOPYABLE( PersistentDataJson_impl )

    void init( const StringWr& inDataPath )
    {
        FS::Path path( inDataPath );
        if( !path.getExtension().equals( CUL_STR( "json" ) ) )
        {
            path.setExtension( CUL_STR( ".json" ) );
        }
        m_path = path.getPath();

        std::ifstream file( m_path.getSTDString() );
        if( file )
        {
            try
            {
                file >> m_document;
                if( !m_document.is_object() )
                {
                    m_document = nlohmann::json::object();
                }
            }
            catch( const nlohmann::json::exception& )
            {
                m_document = nlohmann::json::object();
            }
        }
        else
        {
            m_document = nlohmann::json::object();
        }
    }

    void setValue( const StringWr& inPath, const TypeContainer& inValue )
    {
        std::unique_lock writeLock( m_mutex );
        nlohmann::json* current = navigateOrCreate( inPath );
        *current = typeContainerToJson( inValue );
    }

    const TypeContainer getValue( const StringWr& inPath ) const
    {
        TypeContainer result;

        std::shared_lock readLock( m_mutex );
        const nlohmann::json* current = navigate( inPath );
        if( !current )
        {
            return result;
        }

        if( current->is_null() )
        {
            return result;
        }
        else if( current->is_boolean() )
        {
            result = TypeContainer( current->get<bool>() );
        }
        else if( current->is_number_float() )
        {
            result = TypeContainer( current->get<float>() );
        }
        else if( current->is_number_unsigned() )
        {
            result = TypeContainer( current->get<std::uint64_t>() );
        }
        else if( current->is_number_integer() )
        {
            result = TypeContainer( current->get<std::int64_t>() );
        }
        else if( current->is_string() )
        {
            result = TypeContainer( StringWr( current->get<std::string>() ) );
        }
        else if( current->is_object() )
        {
            result = TypeContainer( jsonToDataNode( *current, inPath ) );
        }
        else if( current->is_array() )
        {
            Assert::check( false, "JSON arrays are not supported." );
        }
        else if( current->is_binary() )
        {
            Assert::check( false, "JSON binary values are not supported." );
        }
        else
        {
            Assert::check( false, "Unsupported JSON value type." );
        }

        return result;
    }

    void addNode( const StringWr& inPath, const DataNode& node )
    {
        std::unique_lock writeLock( m_mutex );
        nlohmann::json* parent = navigateOrCreate( inPath );
        if( !parent->is_object() )
        {
            *parent = nlohmann::json::object();
        }

        const std::string key = toUtf8( node.Name );
        parent->erase( key );
        parent->emplace( key, typeContainerToJson( node.Value ) );
    }

    void writeToFile()
    {
        std::shared_lock readLock( m_mutex );
        std::ofstream file( m_path.getSTDString(), std::ios::binary );
        if( !file )
        {
            return;
        }

        try
        {
            // Filenames on disk can contain characters that were stored via a non-UTF8
            // conversion; never crash the app on dump.
            file << m_document.dump( 4, ' ', false, nlohmann::json::error_handler_t::replace );
        }
        catch( const nlohmann::json::exception& )
        {
        }
    }

    ~PersistentDataJson_impl() = default;

protected:
private:
    static std::string toUtf8( const StringWr& inValue )
    {
        // getSTDString() converts wchar → UTF-8 on Windows.
        // getUtfChar() uses CP_ACP and produces invalid UTF-8 for many filenames.
        return inValue.getSTDString();
    }

    nlohmann::json* navigateOrCreate( const StringWr& inPath )
    {
        nlohmann::json* current = &m_document;
        for( const StringWr& currentPathPart : splitPath( inPath ) )
        {
            const std::string key = toUtf8( currentPathPart );
            if( !current->contains( key ) )
            {
                current->emplace( key, nullptr );
            }
            current = &current->at( key );
        }
        return current;
    }

    const nlohmann::json* navigate( const StringWr& inPath ) const
    {
        const nlohmann::json* current = &m_document;
        for( const StringWr& currentPathPart : splitPath( inPath ) )
        {
            const auto it = current->find( toUtf8( currentPathPart ) );
            if( it == current->end() )
            {
                return nullptr;
            }
            current = &it.value();
        }
        return current;
    }

    static nlohmann::json typeContainerToJson( const TypeContainer& value )
    {
        if( !value.isSet() )
        {
            return nullptr;
        }

        if( value.holdsAlternative<bool>() )
        {
            return value.get<bool>();
        }
        if( value.holdsAlternative<std::int64_t>() )
        {
            return value.get<std::int64_t>();
        }
        if( value.holdsAlternative<std::uint64_t>() )
        {
            return value.get<std::uint64_t>();
        }
        if( value.holdsAlternative<float>() )
        {
            return value.get<float>();
        }
        if( value.holdsAlternative<StringWr>() )
        {
            return toUtf8( value.get<StringWr>() );
        }
        if( value.holdsAlternative<std::unique_ptr<DataNode>>() )
        {
            const auto& child = value.get<std::unique_ptr<DataNode>>();
            if( !child )
            {
                return nullptr;
            }
            return dataNodeToJson( *child );
        }
        if( value.holdsAlternative<std::vector<std::unique_ptr<DataNode>>>() )
        {
            nlohmann::json object = nlohmann::json::object();
            for( const std::unique_ptr<DataNode>& child : value.get<std::vector<std::unique_ptr<DataNode>>>() )
            {
                if( !child )
                {
                    continue;
                }
                const std::string key = toUtf8( child->Name );
                object.erase( key );
                object.emplace( key, dataNodeToJson( *child ) );
            }
            return object;
        }

        return nullptr;
    }

    static nlohmann::json dataNodeToJson( const DataNode& node )
    {
        if( !node.Value.isSet() )
        {
            return nlohmann::json::object();
        }
        return typeContainerToJson( node.Value );
    }

    static std::unique_ptr<DataNode> jsonToDataNode( const nlohmann::json& json, const StringWr& name )
    {
        auto node = std::make_unique<DataNode>();
        node->Name = name;

        if( json.is_object() )
        {
            std::vector<std::unique_ptr<DataNode>> children;
            children.reserve( json.size() );
            for( auto it = json.begin(); it != json.end(); ++it )
            {
                children.push_back( jsonToDataNode( it.value(), StringWr( it.key() ) ) );
            }
            node->Value = TypeContainer( std::move( children ) );
            node->IsEmpty = false;
        }
        else if( json.is_boolean() )
        {
            node->Value = TypeContainer( json.get<bool>() );
            node->IsEmpty = false;
        }
        else if( json.is_number_float() )
        {
            node->Value = TypeContainer( json.get<float>() );
            node->IsEmpty = false;
        }
        else if( json.is_number_unsigned() )
        {
            node->Value = TypeContainer( json.get<std::uint64_t>() );
            node->IsEmpty = false;
        }
        else if( json.is_number_integer() )
        {
            node->Value = TypeContainer( json.get<std::int64_t>() );
            node->IsEmpty = false;
        }
        else if( json.is_string() )
        {
            node->Value = TypeContainer( StringWr( json.get<std::string>() ) );
            node->IsEmpty = false;
        }

        return node;
    }

    mutable std::shared_mutex m_mutex;
    nlohmann::json m_document = nlohmann::json::object();
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

void PersistentDataJson::setValue( const StringWr& inPath, const TypeContainer& inValue )
{
    m_impl->setValue( inPath, inValue );
}

TypeContainer PersistentDataJson::getValue( const StringWr& inPath ) const
{
    return m_impl->getValue( inPath );
}

PersistentDataJson::~PersistentDataJson()
{
}
}  // namespace CUL
