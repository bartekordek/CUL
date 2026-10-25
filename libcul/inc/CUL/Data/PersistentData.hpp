#pragma once

#include <CUL/String/StringWrapper.hpp>
#include <CUL/GenericUtils/NonCopyable.hpp>
#include <CUL/STL_IMPORTS/STD_memory.hpp>
#include <CUL/STL_IMPORTS/STD_type_traits.hpp>
#include <CUL/STL_IMPORTS/STD_variant.hpp>
#include <CUL/STL_IMPORTS/STD_vector.hpp>

namespace CUL
{

struct DataNode;
using TypeContainer_old = std::variant<StringWr,
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
     CUL_NONCOPYABLE_MOVABLE( Variant )

     template <typename T>
     Variant( T&& value ) : m_value( std::forward<T>( value ) )
     {
         m_set = true;
     }

     bool isSet() const
     {
         return m_set;
     }

     template <typename T>
     void set( const T& inValue )
     {
         m_value = inValue;
         m_set = true;
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
         return std::holds_alternative<OtherType>( m_value );
     }

     template <typename OtherType>
     OtherType getValue() const
     {
         return std::get<OtherType>( m_value );
     }

 private:
     std::variant<Types...> m_value;
     bool m_set{ false };
 };

 using TypeContainer = Variant<StringWr,
                               std::uint64_t,
                               std::int64_t,
                               float,
                               bool,
                               std::unique_ptr<DataNode>,
                               std::vector<std::unique_ptr<DataNode>>>;

struct DataNode
{
    StringWr Name;
    TypeContainer Value;
    bool IsEmpty{ true };

    DataNode() = default;
    CUL_NONCOPYABLE_MOVABLE( DataNode )

    template <typename T>
    DataNode( StringWr inName, T&& inValue )
        : Name( std::move( inName ) ),
          Value( std::forward<T>( inValue ) ),
          IsEmpty( false )
    {
    }

    template <typename T>
    void add( const StringWr& inPath, const T& inValue )
    {
        const std::vector<StringWr> pathParts = inPath.split( CUL_CHAR( '/' ) );
        if( pathParts.empty() )
        {
            return;
        }

        DataNode* current = this;
        const std::size_t lastIndex = pathParts.size() - 1u;
        for( std::size_t i = 0u; i < lastIndex; ++i )
        {
            current = current->getOrCreateChild( pathParts[i] );
        }

        DataNode* leaf = current->getOrCreateChild( pathParts[lastIndex] );
        leaf->Value = storeValue( inValue );
        leaf->IsEmpty = false;
    }

    const DataNode* findChild( const StringWr& inName ) const;

    DataNode* findChild( const StringWr& inName );

private:
    DataNode* getOrCreateChild( const StringWr& inName )
    {
        auto* children = Value.getIf<std::vector<std::unique_ptr<DataNode>>>();
        if( !children )
        {
            Value = TypeContainer( std::vector<std::unique_ptr<DataNode>>() );
            children = Value.getIf<std::vector<std::unique_ptr<DataNode>>>();
        }

        for( const std::unique_ptr<DataNode>& child : *children )
        {
            if( child->Name == inName )
            {
                return child.get();
            }
        }

        auto child = std::make_unique<DataNode>();
        child->Name = inName;
        DataNode* raw = child.get();
        children->push_back( std::move( child ) );
        IsEmpty = false;
        return raw;
    }

    template <typename T>
    static TypeContainer storeValue( const T& inValue )
    {
        using Decayed = std::decay_t<T>;
        if constexpr( std::is_same_v<Decayed, bool> )
        {
            return TypeContainer( inValue );
        }
        else if constexpr( std::is_floating_point_v<Decayed> )
        {
            return TypeContainer( static_cast<float>( inValue ) );
        }
        else if constexpr( std::is_integral_v<Decayed> )
        {
            if constexpr( std::is_unsigned_v<Decayed> )
            {
                return TypeContainer( static_cast<std::uint64_t>( inValue ) );
            }
            else
            {
                return TypeContainer( static_cast<std::int64_t>( inValue ) );
            }
        }
        else
        {
            return TypeContainer( StringWr( inValue ) );
        }
    }
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