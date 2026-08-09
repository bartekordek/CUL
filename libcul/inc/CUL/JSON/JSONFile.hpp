#pragma once

#include "CUL/Filesystem/IFile.hpp"
#include "CUL/JSON/INode.hpp"
#include "CUL/GenericUtils/NonCopyable.hpp"

namespace rapidjson
{

template <typename CharType>
struct UTF8;
template <typename CharType>
struct UTF16;
template <typename CharType>
struct UTF16BE;
template <typename CharType>
struct UTF16LE;
template <typename CharType>
struct UTF32;
template <typename CharType>
struct UTF32BE;
template <typename CharType>
struct UTF32LE;
template <typename CharType>
struct ASCII;
template <typename CharType>
struct AutoUTF;

template <typename SourceEncoding, typename TargetEncoding>
struct Transcoder;

// allocators.h

class CrtAllocator;

template <typename BaseAllocator>
class MemoryPoolAllocator;

// stream.h

template <typename Encoding>
struct GenericStringStream;

typedef GenericStringStream<UTF8<char> > StringStream;

template <typename Encoding>
struct GenericInsituStringStream;

typedef GenericInsituStringStream<UTF8<char> > InsituStringStream;

// stringbuffer.h

template <typename Encoding, typename Allocator>
class GenericStringBuffer;

typedef GenericStringBuffer<UTF8<char>, CrtAllocator> StringBuffer;

// filereadstream.h

class FileReadStream;

// filewritestream.h

class FileWriteStream;

// memorybuffer.h

template <typename Allocator>
struct GenericMemoryBuffer;

typedef GenericMemoryBuffer<CrtAllocator> MemoryBuffer;

// memorystream.h

struct MemoryStream;

// reader.h

template <typename Encoding, typename Derived>
struct BaseReaderHandler;

template <typename SourceEncoding, typename TargetEncoding, typename StackAllocator>
class GenericReader;

typedef GenericReader<UTF8<char>, UTF8<char>, CrtAllocator> Reader;

// writer.h

template <typename OutputStream,
          typename SourceEncoding,
          typename TargetEncoding,
          typename StackAllocator,
          unsigned writeFlags>
class Writer;

// prettywriter.h

template <typename OutputStream,
          typename SourceEncoding,
          typename TargetEncoding,
          typename StackAllocator,
          unsigned writeFlags>
class PrettyWriter;

// document.h

template <typename Encoding, typename Allocator>
class GenericMember;

template <bool Const, typename Encoding, typename Allocator>
class GenericMemberIterator;

template <typename CharType>
struct GenericStringRef;

template <typename Encoding, typename Allocator>
class GenericValue;

typedef GenericValue<UTF8<char>, MemoryPoolAllocator<CrtAllocator> > Value;

template <typename Encoding, typename Allocator, typename StackAllocator>
class GenericDocument;

typedef GenericDocument<UTF8<char>, MemoryPoolAllocator<CrtAllocator>, CrtAllocator>
    Document;
}

namespace CUL::JSON
{
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
    INode* parse( const rapidjson::Value& parentValue );

    FS::FileType getType() const;

    void changePath( const FS::Path& newPath );

    void reload( bool keepLineEndingCharacter );
    void reload();
    void load( bool keepLineEndingCharacter, bool removeBottomEmptyLines );
    void unload();

    std::unique_ptr<rapidjson::Document> m_document;
    INode* m_root = nullptr;
    bool m_keepLineEndingCharacter = false;
    std::vector<char> m_fileContents;
};

}  // namespace CUL::JSON