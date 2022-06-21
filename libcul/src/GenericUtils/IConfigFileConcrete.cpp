#include "GenericUtils/IConfigFileConcrete.hpp"
#include "CUL/Filesystem/IFile.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/Filesystem/FileFactory.hpp"

#include "CUL/STL_IMPORTS/STD_fstream.hpp"
#include "CUL/STL_IMPORTS/STD_iosfwd.hpp"
#include "CUL/STL_IMPORTS/STD_sstream.hpp"

using namespace CUL;
using namespace GUTILS;

IConfigFileConcrete::IConfigFileConcrete( const FS::Path& path, CULInterface* culInterface ):
    m_culInterface( culInterface ),
    m_path( path )
{
    Assert::simple( nullptr != culInterface, "CUL Is not initialized!" );
    loadPath();
    m_file = culInterface->getFF()->createFileFromPath( path );
}

void IConfigFileConcrete::addValue( const String& valueName, const String& value )
{
    m_values[valueName] = value;
}

const String& IConfigFileConcrete::getValue( const String& valueFieldName ) const
{
    const auto it = m_values.find( valueFieldName );
    if( it != m_values.end() )
    {
        return m_values.at( valueFieldName );
    }

    return m_empty;
}

TimeConcrete IConfigFileConcrete::getModificationTime()
{
    return m_file->getLastModificationTime();
}

void IConfigFileConcrete::reload()
{
    clear();
    loadPath();
}

void IConfigFileConcrete::loadPath()
{
    std::ifstream fileStream( m_path.getPath().cStr() );
    std::string line;
    char delim = ' ';
    while( std::getline( fileStream, line ) )
    {
        std::istringstream iss( line );
        std::string item;
        int i = 0;
        std::string valueName;
        while( std::getline( iss, item, delim ) )
        {
            if( i == 0 )
            {
                valueName = item;
            }
            else if( i == 1 )
            {
                addValue( valueName, item );
            }
            ++i;
        }
    }
}

IConfigFileConcrete::~IConfigFileConcrete()
{
    clear();
}

void IConfigFileConcrete::clear()
{
    m_values.clear();
}