#pragma once

#include "CUL/GenericUtils/Types.hpp"

#include "CUL/STL_IMPORTS/STD_stddef.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/STL_IMPORTS/STD_cstdint.hpp"
#include "CUL/STL_IMPORTS/STD_string.hpp"

NAMESPACE_BEGIN( CUL )

class DataWrapper final
{
public:
    CULLib_API DataWrapper();
    CULLib_API DataWrapper( const DataWrapper& dw );
    CULLib_API DataWrapper( DataWrapper&& dw );
    CULLib_API DataWrapper& operator=( const DataWrapper& dw );
    CULLib_API DataWrapper& operator=( DataWrapper&& dw );

    CULLib_API void load( const void* data, std::size_t size, ETypes inType );
    CULLib_API void* getData();
    CULLib_API const void* getData() const;
    CULLib_API std::size_t getSize() const;
    CULLib_API std::size_t getElementCount() const;

    CULLib_API void createFrom( const std::vector<float>& inData );
    CULLib_API void createFrom( const float* inData, std::size_t inDataSize );

    CULLib_API void createFrom( const std::vector<std::uint32_t>& inData );
    CULLib_API void createFrom( const std::vector<std::int32_t>& inData );

    CULLib_API void setType( ETypes inType );
    CULLib_API ETypes getType() const;

    CULLib_API bool getIsEmpty() const;

    CULLib_API ~DataWrapper();

protected:
private:
    void release();
    std::vector<std::uint8_t> m_value;
    ETypes m_type{ ETypes::Unkown };
};

NAMESPACE_END( CUL )
