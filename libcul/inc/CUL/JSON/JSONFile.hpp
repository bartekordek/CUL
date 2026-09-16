#pragma once

#include "CUL/Filesystem/IFile.hpp"
#include "CUL/JSON/INode.hpp"
#include "CUL/GenericUtils/NonCopyable.hpp"


namespace CUL::JSON
{

class JSONFile_impl;
class CULLib_API JSONFile: public FS::IFile
{
public:
    JSONFile( const StringWr& path, CULInterface* inInterface );

    INode* getRoot() const;
    INode* getChild( const StringWr& inPath );

    CUL_NONCOPYABLE( JSONFile );

    ~JSONFile();

protected:
private:
    void parse();

    FS::FileType getType() const;

    void changePath( const FS::Path& newPath );

    void reload( bool keepLineEndingCharacter );
    void reload();
    void load( bool keepLineEndingCharacter, bool removeBottomEmptyLines );
    void unload();

    std::unique_ptr<JSONFile_impl> m_impl;
    INode* m_root = nullptr;
    bool m_keepLineEndingCharacter = false;
    std::vector<char> m_fileContents;
};

}  // namespace CUL::JSON