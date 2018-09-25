#include "CUL/JSON/IJSONFile.hpp"
#include "CUL/JSON/Object.hpp"
#include "RapidJSON.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( JSON )

class FS::IFile;

using JValue = rapidjson::Value;

class JSONFileConcrete:
    public IJSONFile
{
public:
    JSONFileConcrete( void );
    JSONFileConcrete( const JSONFileConcrete& rhv ) = delete;
    ~JSONFileConcrete( void );

    JSONFileConcrete& operator=( const JSONFileConcrete& rhv ) = delete;

    const FS::Path& getPath()const override;

    CBool exists()const override;
    CBool isBinary()const override;

    void changePath( const FS::Path& newPath ) override;

    void reload( CBool keepLineEndingCharacter = false ) override;
    void load( CBool keepLineEndingCharacter = false ) override;
    void unload() override;

    CnstMyStr& firstLine()const override;
    CnstMyStr& lastLine()const override;

    CnstMyStr& getAsOneString()const override;
    const char** getContent()const override;

    cunt getLinesCount()const override;

    INode* getRoot()const override;

protected:
private:
    void parse();
    void parse( CnstMyStr& valueName, const JValue& parentValue, INode* parentNode = nullptr );

    rapidjson::Document m_document;
    INode* m_root = nullptr;
    FS::IFile* m_fileContents = nullptr;

};

NAMESPACE_END( JSON )
NAMESPACE_END( CUL )