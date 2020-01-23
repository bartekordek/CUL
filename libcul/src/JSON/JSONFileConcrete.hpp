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
    JSONFileConcrete();
    ~JSONFileConcrete();

protected:
private:
    void parse();
    INode* parse(
        const JValue& parentValue );
    const FS::Path& getPath() const override;

    CBool exists() const override;
    CBool isBinary() const override;

    void changePath( const FS::Path& newPath ) override;

    void reload( CBool keepLineEndingCharacter = false ) override;
    void load( CBool keepLineEndingCharacter = false ) override;
    void unload() override;

    CsStr& firstLine() const override;
    CsStr& lastLine() const override;

    CsStr& getAsOneString() const override;
    const char** getContent() const override;

    Cunt getLinesCount() const override;

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