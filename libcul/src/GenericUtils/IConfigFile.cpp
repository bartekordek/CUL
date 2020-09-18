#include "CUL/GenericUtils/IConfigFile.hpp"
#include "GenericUtils/IConfigFileConcrete.hpp"
#include "CUL/STL_IMPORTS/STD_fstream.hpp"
#include "CUL/STL_IMPORTS/STD_iosfwd.hpp"
#include "CUL/STL_IMPORTS/STD_sstream.hpp"

using namespace CUL;
using namespace GUTILS;


IConfigFile* IConfigFile::createFile( const FS::Path& path )
{
    auto configFile = new IConfigFileConcrete();

    std::ifstream fileStream( path.getPath().cStr() );
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
                configFile->addValue( valueName, item );
            }
            ++i;
        }
    }

    return configFile;
}