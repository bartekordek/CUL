#pragma once

#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/Log/ILogger.hpp"
#include "CUL/STL_IMPORTS/STD_cstdint.hpp"

NAMESPACE_BEGIN( CUL )

template<std::uint16_t Capacity>
class StringStatic
{
public:
    StringStatic()
    {

    }

    StringStatic( const StringStatic& arg )
    {
    }

    StringStatic( StringStatic&& arg )
    {
    }

    StringStatic& operator=( const StringStatic& arg )
    {
        if( this != &arg )
        {
            std::strcpy(m_value, arg.m_value);
            m_size = arg.m_size;
        }
        return *this;
    }

    StringStatic& operator=( StringStatic&& arg )
    {
        if( this != &arg )
        {
            std::strcpy( m_value, arg.m_value );
            m_size = arg.m_size;

            arg.m_size = 0u;
        }
        return *this;
    }

    void append(const char* inStr)
    {
        const std::uint16_t stringLength = std::strlen( inStr );
        append(inStr, stringLength);
    }

    void append( const char* inStr, std::uint16_t inSize )
    {
        if( m_size + inSize + 1u >= Capacity )
        {
            Assert::simple( false, "NOT ENOUGHT PLACE FOR THIS STRING!" );
            return;
        }

        std::strncpy( m_value + m_size, inStr, inSize);
        m_size += inSize;
        m_value[m_size] = '\n';
        m_value[m_size+1] = '\0';
        m_size += 1;
    }

    void print()const
    {
        LOG::ILogger::getInstance().logVariable( LOG::Severity::INFO, "\nCurrent string value:\n%s", m_value );
    }

    const char* c_str() const
    {
        return m_value;
    }

    ~StringStatic()
    {

    }

protected:
private:
    char m_value[Capacity]{};
    std::uint16_t m_size{ 0u };
};

NAMESPACE_END( CUL )