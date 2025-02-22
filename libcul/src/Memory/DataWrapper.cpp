#include "CUL/Memory/DataWrapper.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/CULInterface.hpp"
#include "CUL/Threading/ThreadUtil.hpp"

#include "CUL/STL_IMPORTS/STD_memory.hpp"
#include "CUL/STL_IMPORTS/STD_cstring.hpp"

using namespace CUL;

DataWrapper::DataWrapper()
{

}

DataWrapper::DataWrapper( const DataWrapper& dw ):
    m_value( dw.m_value ),
    m_type( dw.m_type )
{
}

DataWrapper::DataWrapper( DataWrapper&& dw ):
    m_value( dw.m_value ),
    m_type( dw.m_type )
{
    dw.m_value.clear();
    dw.m_type = ETypes::Unkown;
}

DataWrapper& DataWrapper::operator=( const DataWrapper& dw )
{
    if( this != &dw )
    {
        m_value = dw.m_value;
        m_type = dw.m_type;
    }
    return *this;
}

DataWrapper& DataWrapper::operator=( DataWrapper&& dw )
{
    if( this != &dw )
    {
        m_value = dw.m_value;
        m_type = dw.m_type;
        dw.m_value.clear();
        dw.m_type = ETypes::Unkown;
    }
    return *this;
}

void DataWrapper::createFrom( const std::vector<float>& inData )
{
    const std::uint64_t dataSize = sizeof( float ) * inData.size();
    load( static_cast<const void*>( inData.data() ), dataSize, CUL::ETypes::Float );
}

void DataWrapper::createFrom( const float* inData, std::size_t inDataSize )
{
    const std::uint64_t dataSize = sizeof( float ) * inDataSize;
    load( static_cast<const void*>( inData ), dataSize, CUL::ETypes::Float );
}

void DataWrapper::createFrom( const std::vector<std::uint32_t>& inData )
{
    const std::uint64_t dataSize = sizeof( std::uint32_t ) * inData.size();
    load( static_cast<const void*>( inData.data() ), dataSize, CUL::ETypes::Uint32 );
}

void DataWrapper::setType( ETypes inType )
{
    m_type = inType;
}

ETypes DataWrapper::getType() const
{
    return m_type;
}

void DataWrapper::load( const void* data, std::size_t size, ETypes inType )
{
    release();
    m_value.resize( size );
    std::memcpy( m_value.data(), data, size );
    m_type = inType;
    CUL::Assert::simple( m_type != ETypes::Unkown, "NOT IN THE RENDER THREAD." );
}

bool DataWrapper::getIsEmpty() const
{
    return m_value.empty();
}

void* DataWrapper::getData()
{
    return m_value.data();
}

const void* DataWrapper::getData() const
{
    return m_value.data();
}

std::size_t DataWrapper::getSize() const
{
    return m_value.size();
}

std::size_t DataWrapper::getElementCount() const
{
    if( m_type == ETypes::Float || m_type == ETypes::Uint32 )
    {
        return m_value.size() / 4u;
    }

    return 0u;
}

DataWrapper::~DataWrapper()
{
    release();
}

void DataWrapper::release()
{
    m_value.clear();
}
