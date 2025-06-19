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
void CommandlineParser::passVariables( HINSTANCE /*inInst*/, PSTR cmd )
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
        const char* argument = splitedStr[i].cStr();
        const String argStr = argument;

        Argument arg;
        arg.Name = argStr;
        arg.Name.removeFromStart( "--" );
        arg.Index = static_cast<decltype( arg.Index )>( i );
        if( i + 1 < argsCount )
        {
            const String argValue = splitedStr[i + 1];
            if( argValue.startsWith( "--" ) == false )
            {
                arg.Value = argValue;
            }
        }
        m_values[arg.Name.string()] = arg;
    }
}
#endif  // #if defined(CUL_WINDOWS)

void CommandlineParser::passVariables( const std::int32_t argc, const char** argv )
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
            arg.Value = argStr;
            m_values["ExecPath"] = arg;

            FS::Path execPath = argStr;
            arg.Name = "ExecutableName";
            arg.Value = execPath.getBaseName() + "." + execPath.getExtension();
            m_values["ExecutableName"] = arg;

            arg.Name = "Directory";
            arg.Value = execPath.getDir();
            m_values["Directory"] = arg;
        }
        else
        {
            Argument arg;
            arg.Name = argStr;
            arg.Name.removeFromStart( "--" );
            arg.Index = static_cast<decltype( arg.Index )>( i );
            if( i + 1 < argCount )
            {
                const String argValue = argv[i + 1];
                if( argValue.startsWith( "--" ) == false )
                {
                    arg.Value = argValue;
                }
            }
            m_values[arg.Name.string()] = arg;
        }
    }
}

const String CommandlineParser::getArgument( std::size_t /*inArg*/ ) const
{
    return {};
}

const String& CommandlineParser::getExecutablePath() const
{
    static String appPath;

    const auto it = m_values.find( "ExecPath" );
    if( it != m_values.end() )
    {
        return it->second.Value;
    }

    return appPath;
}

const String& CommandlineParser::getAppName() const
{
    static String appName;

    const auto it = m_values.find( "ExecutableName" );
    if( it != m_values.end() )
    {
        return it->second.Value;
    }

    return appName;
}

const String CommandlineParser::getFlagValue( const String& /*inFlagName*/ ) const
{
    return {};
}

CommandlineParser::~CommandlineParser()
{
}
}  // namespace CUL