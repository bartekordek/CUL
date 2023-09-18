#pragma once

#include "CUL/CUL.hpp"

#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/STL_IMPORTS/STD_functional.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( GUTILS )

class CULLib_API DelegateTemplate
{
public:
    DelegateTemplate() = default;
    virtual ~DelegateTemplate() = default;
protected:
private:
};

class CULLib_API DelegateTemplateZeroParam final: public DelegateTemplate
{
public:

    DelegateTemplateZeroParam() = default;

    using DelegateInput = std::function < void() >;
    void addDelegate( DelegateInput delegate );

    void execute();

protected:
private:
    std::vector<DelegateInput> m_delegates;

private:
    DelegateTemplateZeroParam( const DelegateTemplateZeroParam& arg ) = delete;
    DelegateTemplateZeroParam( DelegateTemplateZeroParam&& arg ) = delete;
    DelegateTemplateZeroParam& operator=( const DelegateTemplateZeroParam& arg ) = delete;
    DelegateTemplateZeroParam& operator=( DelegateTemplateZeroParam&& arg ) = delete;
};

template <typename T>
class DelegateTemplateOneParam final: public DelegateTemplate
{
public:
    DelegateTemplateOneParam() = default;
    using DelegateInput = std::function < void( T ) >;
    void addDelegate( DelegateInput delegate )
    {
        m_delegates.push_back( delegate );
    }

    void execute( T value )
    {
        const size_t size = m_delegates.size();
        for( size_t i = 0; i < size; ++i )
        {
            m_delegates[i]( value );
        }
    }

protected:
private:
    std::vector<DelegateInput> m_delegates;

private:
    DelegateTemplateOneParam( const DelegateTemplateOneParam& arg );
    DelegateTemplateOneParam( DelegateTemplateOneParam&& arg );
    DelegateTemplateOneParam& operator=( const DelegateTemplateOneParam& arg ) = delete;
    DelegateTemplateOneParam& operator=( DelegateTemplateOneParam&& arg ) = delete;
};

template <typename Type1, typename Type2>
class DelegateTemplateTwoParam final: public DelegateTemplate
{
public:
    using DelegateInput = std::function < void( Type1, Type2 )>;
    void addDelegate( DelegateInput delegate )
    {
        m_delegates.push_back( delegate );
    }

    void execute( Type1 value1, Type2 value2 )
    {
        const size_t size = m_delegates.size();
        for( size_t i = 0; i < size; ++i )
        {
            m_delegates[i]( value1, value2 );
        }
    }

protected:
private:
    std::vector<DelegateInput> m_delegates;

private:
    DelegateTemplateTwoParam( const DelegateTemplateTwoParam& arg );
    DelegateTemplateTwoParam( DelegateTemplateTwoParam&& arg );
    DelegateTemplateTwoParam& operator=( const DelegateTemplateTwoParam& arg ) = delete;
    DelegateTemplateTwoParam& operator=( DelegateTemplateTwoParam&& arg ) = delete;
};

NAMESPACE_END( GUTILS )
NAMESPACE_END( CUL )
