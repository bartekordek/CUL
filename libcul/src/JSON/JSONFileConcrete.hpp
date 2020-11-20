#pragma once

#include "CUL/Filesystem/IFile.hpp"
#include "CUL/JSON/IJSONFile.hpp"
#include "ImportRapidJSON.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( JSON )

using JValue = rapidjson::Value;

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4820 )
#endif
class JSONFileConcrete final:
    public IJSONFile
{
public:
    JSONFileConcrete( const String& path, FS::IFile* fileContent, CULInterface* interface );
    ~JSONFileConcrete();

protected:
private:
    void parse();
    INode* parse(
        const JValue& parentValue );
    const FS::Path& getPath() const override;

    FS::FileType getType() const override;

    void changePath( const FS::Path& newPath ) override;

    void reload( Cbool keepLineEndingCharacter = false ) override;
    void load( Cbool keepLineEndingCharacter = false ) override;
    void unload() override;

    const String& firstLine() const override;
    const String& lastLine() const override;

    const String& getAsOneString() const override;
    const char** getContent() const override;

    unsigned getLinesCount() const override;

    INode* getRoot() const override;

    rapidjson::Document m_document;
    INode* m_root = nullptr;
    FS::IFile* m_fileContents = nullptr;

private: // Deleted
    JSONFileConcrete( const JSONFileConcrete& rhv ) = delete;
    JSONFileConcrete& operator=( const JSONFileConcrete& rhv ) = delete;
};
#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( JSON )
NAMESPACE_END( CUL )
