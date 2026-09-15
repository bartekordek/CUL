#pragma once

#include <CUL/String/StringWrapper.hpp>
#include <CUL/GenericUtils/NonCopyable.hpp>
#include <CUL/STL_IMPORTS/STD_memory.hpp>
#include <CUL/STL_IMPORTS/STD_variant.hpp>

namespace CUL
{

struct DataNode;
using TypeContainer = std::variant<StringWr,
                                   std::uint64_t,
                                   std::int64_t,
                                   float,
                                   bool,
                                   std::unique_ptr<DataNode>>;

template <typename... Types>
class Variant
{
public:
    Variant() = default;

    template <typename T>
    Variant( T&& value ) : m_value( std::forward<T>( value ) )
    {
    }

    template <typename T>
    bool holdsAlternative() const
    {
        return std::holds_alternative<T>( m_value );
    }

    template <typename T>
    T& get()
    {
        return std::get<T>( m_value );
    }

    template <typename T>
    const T& get() const
    {
        return std::get<T>( m_value );
    }

    template <typename T>
    T* getIf()
    {
        return std::get_if<T>( &m_value );
    }

    template <typename T>
    const T* getIf() const
    {
        return std::get_if<T>( &m_value );
    }

    template <typename Visitor>
    decltype( auto ) visit( Visitor&& visitor )
    {
        return std::visit( std::forward<Visitor>( visitor ), m_value );
    }

    template <typename Visitor>
    decltype( auto ) visit( Visitor&& visitor ) const
    {
        return std::visit( std::forward<Visitor>( visitor ), m_value );
    }

    template<typename OtherType>
    bool isOfType() const
    {
        return std::holds_alternative<OtherType>();
    }

    template <typename OtherType>
    OtherType getValue() const
    {
        return std::get<OtherType>( node.Value );
    }

private:
    std::variant<Types...> m_value;
};

struct DataNode
{
    StringWr Name;
    TypeContainer Value;
    bool IsEmpty{ true };
};

class IPersistendData
{
public:
    IPersistendData() = default;

    virtual void setValue( const StringWr& inPath, const TypeContainer& inValue ) = 0;
    virtual TypeContainer getValue( const StringWr& inPath ) const = 0;

    CUL_NONCOPYABLE( IPersistendData );
    virtual ~IPersistendData() = default;

protected:
private:
};
}  // namespace CUL