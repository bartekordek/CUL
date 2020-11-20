#pragma once

#include "CUL/Filesystem/IFile.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( FS )

class CULLib_API ICSVFile:
    public IFile
{
public:
    ICSVFile( const String& path, CULInterface* interface );

    virtual ~ICSVFile();

    virtual bool checkIfFileIsAllRight() const = 0;
    virtual unsigned rowsCount() const = 0;
    virtual unsigned colsCount() const = 0;
    virtual const String& getVal( Cunt row, Cunt col ) const = 0;
    virtual void setVal( const String& val, Cunt row, Cunt col ) = 0;
    virtual void setDelimeter( const String& delimeter ) = 0;
    virtual void fileContainsQuotationMarks( Cbool containsQuotationMarks ) = 0;

protected:
private:

private: // Deleted:
    ICSVFile( const ICSVFile& rhv ) = delete;
    ICSVFile( ICSVFile&& rhv ) = delete;
    ICSVFile& operator=( const ICSVFile& rhv ) = delete;
    ICSVFile& operator=( ICSVFile&& rhv ) = delete;
};

NAMESPACE_END( FS )
NAMESPACE_END( CUL )