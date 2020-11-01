#pragma once

#include "CUL/Filesystem/FileFactory.hpp"
#include "CUL/String.hpp"


#include "CUL/STL_IMPORTS/STD_set.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( FS )


class CULLib_API FSApi
{
public:
    FSApi( FileFactory* ff );
    
    String getCurrentDir();
    IFile* getDirectory( const Path& directory );

    virtual ~FSApi();
protected:
private:
    FileFactory* m_fileFactory = nullptr;

};

NAMESPACE_END( FS )
NAMESPACE_END( CUL )