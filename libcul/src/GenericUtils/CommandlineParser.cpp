#include "CUL/GenericUtils/CommandlineParser.hpp"
#include "CUL/Filesystem/Path.hpp"

namespace CUL
{

CommandlineParser& CommandlineParser::getInstance()
{
    static CommandlineParser instance;
    return instance;
}

CommandlineParser::CommandlineParser()
{
}

#if defined( CUL_WINDOWS )
void CommandlineParser::passWindowsVariables( HINSTANCE /*inInst*/, PSTR cmd )
{
    TCHAR szFileName[MAX_PATH];

    GetModuleFileName( NULL, szFileName, MAX_PATH );

    {
        Argument arg;
        arg.Index = 0;
        arg.Name = "ExecPath";
        arg.Value = szFileName;
        m_values["ExecPath"] = arg;
    }

    String cmdStr = cmd;
    const std::vector<String> splitedStr = cmdStr.split( " " );
    const std::size_t argsCount = splitedStr.size();
    for( std::size_t i = 0u; i < argsCount; ++i )
    {
        const char* argument = splitedStr[i].getUtfChar();
        const String argStr = argument;

        Argument arg;
        arg.Name = argStr.getString();
        arg.Name.removeFromStart( "--" );
        arg.Index = static_cast<decltype( arg.Index )>( i );
        if( i + 1 < argsCount )
        {
            const String argValue = splitedStr[i + 1];
            if( argValue.startsWith( "--" ) == false )
            {
                arg.Value = argValue.getString();
            }
        }
        m_values[arg.Name.getSTDString()] = arg;
    }
}
#endif  // #if defined(CUL_WINDOWS)

void CommandlineParser::passVariables( const std::int32_t argc, char** argv )
{
    const std::size_t argCount = static_cast<std::size_t>( argc );
    for( std::size_t i = 0u; i < argCount; ++i )
    {
        const char* argument = argv[i];
        const String argStr = argument;

        if( i == 0u )  // Path
        {
            Argument arg;
            arg.Index = 0;
            arg.Name = "ExecPath";
            arg.Value = argStr.getString();
            m_values["ExecPath"] = arg;

            FS::Path execPath = argStr;
            arg.Name = "ExecutableName";
            arg.Value.createFromPrintf( "%s.%s", execPath.getBaseName().getSTDString().c_str(),
                                        execPath.getExtension().getSTDString().c_str() );
            m_values["ExecutableName"] = arg;

            arg.Name = "Directory";
            arg.Value = execPath.getDir();
            m_values["Directory"] = arg;
        }
        else
        {
            Argument arg;
            arg.Name = argStr.getString();
            arg.Name.removeFromStart( "--" );
            arg.Index = static_cast<decltype( arg.Index )>( i );
            if( i + 1 < argCount )
            {
                const String argValue = argv[i + 1];
                if( argValue.startsWith( "--" ) == false )
                {
                    arg.Value = argValue.getString();
                }
            }
            m_values[arg.Name.getSTDString()] = arg;
        }
    }
}

const STDStringWrapper CommandlineParser::getArgument( std::size_t /*inArg*/ ) const
{
    return {};
}

const STDStringWrapper& CommandlineParser::getExecutablePath() const
{
    static STDStringWrapper appPath;

    const auto it = m_values.find( "ExecPath" );
    if( it != m_values.end() )
    {
        return it->second.Value;
    }

    return appPath;
}

const STDStringWrapper& CommandlineParser::getAppName() const
{
    static STDStringWrapper appName;

    const auto it = m_values.find( "ExecutableName" );
    if( it != m_values.end() )
    {
        return it->second.Value;
    }

    return appName;
}

const STDStringWrapper CommandlineParser::getFlagValue( const STDStringWrapper& /*inFlagName*/ ) const
{
    return {};
}

CommandlineParser::~CommandlineParser()
{
}
}  // namespace CUL