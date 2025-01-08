#pragma once

#include "CUL/GenericUtils/Types.hpp"

#include "CUL/STL_IMPORTS/STD_stddef.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/STL_IMPORTS/STD_cstdint.hpp"
#include "CUL/STL_IMPORTS/STD_string.hpp"

NAMESPACE_BEGIN( CUL )

class CULLib_API DataWrapper final
{
public:
    DataWrapper();
    DataWrapper( const DataWrapper& dw );
    DataWrapper( DataWrapper&& dw );
    DataWrapper& operator=( const DataWrapper& dw );
    DataWrapper& operator=( DataWrapper&& dw );

    void load( const void* data, std::size_t size, ETypes inType );
    void* getData();
    const void* getData() const;
    std::size_t getSize() const;
    std::size_t getElementCount() const;

    void createFrom( const std::vector<float>& inData );
    void createFrom( const std::vector<std::uint32_t>& inData );

    void setType( ETypes inType );
    ETypes getType() const;

    bool getIsEmpty() const;

    ~DataWrapper();

protected:
private:
    void release();
    std::vector<std::uint8_t> m_value;
    ETypes m_type{ ETypes::Unkown };
};

NAMESPACE_END( CUL )
