#include <CUL/Data/IFileDb.hpp>
#include <CUL/Data/PersistentDataJson.hpp>
#include <CUL/STL_IMPORTS/STD_shared_mutex.hpp>
#include <CUL/STL_IMPORTS/STD_unordered_map.hpp>

namespace CUL
{
class FileDBJson: public IFileDb
{
public:
    FileDBJson()
    {
    }

    CUL_NONCOPYABLE( FileDBJson );

    void load( const StringWr& inDbPath )
    {
        m_data.init( inDbPath );

        const TypeContainer fileListNode = m_data.getValue( "FileList" );
        if( fileListNode.holdsAlternative<std::vector<std::unique_ptr<DataNode>>>() )
        {
            const std::vector<std::unique_ptr<DataNode>> list = fileListNode
                .get<std::vector<std::unique_ptr<DataNode>>>();
        }
    }

    void addFile( const FileMeta& meta )
    {
        std::unique_lock writeLock( m_filesLock );

        const StringWr keySize = StringWr::createFromPrintf( CUL_STR( "%s/%s" ), meta.Path.getCharVal(), CUL_STR( "size" ) );

        m_data.setValue( keySize, meta.Size );

        const StringWr keyMd5 = StringWr::createFromPrintf( CUL_STR( "%s/%s" ), meta.Path.getCharVal(), CUL_STR( "md5" ) );
        m_data.setValue( keyMd5, meta.MD5 );
    }

    std::optional<FileMeta> getFile( const StringWr& path )
    {
        std::optional<FileMeta> result;

        const StringWr keySize = StringWr::createFromPrintf( CUL_STR( "%s/%s" ), path.getCharVal(), CUL_STR( "size" ) );
        const StringWr keyMd5 = StringWr::createFromPrintf( CUL_STR( "%s/%s" ), path.getCharVal(), CUL_STR( "md5" ) );

        const auto sizeWr = m_data.getValue( keySize );

        if( sizeWr. )
        {
        }

        {
            std::shared_lock readLock( m_filesLock );
        }

        return result;
    }

    ~FileDBJson()
    {
    }

protected:
private:
    PersistentDataJson m_data;

    std::unordered_map<StringWr, FileMeta> m_files;
    std::shared_mutex m_filesLock;
};

std::unique_ptr<IFileDb> IFileDb::createJsonImpl()
{
    return std::make_unique<FileDBJson>();
}
}  // namespace CUL