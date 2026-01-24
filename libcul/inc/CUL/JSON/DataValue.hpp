//#pragma once
//
//#include "CUL/STL_IMPORTS/STD_memory.hpp"
//#include "CUL/STL_IMPORTS/STD_vector.hpp"
//#include "CUL/String/String.hpp"
//
//NAMESPACE_BEGIN( CUL )
//NAMESPACE_BEGIN( JSON )
//
//enum class ElementType: short
//{
//    NONE = 0,
//    OBJECT,
//    ARRAY,
//    BOOL,
//    DOUBLE,
//    FLOAT,
//    INT,
//    INT64,
//    STRING
//};
//
//class CULLib_API INode;
//using NodePtr = std::unique_ptr<INode>;
//using ChildrenNodes = std::vector<NodePtr>;
//
//class CULLib_API DataValue final
//{
//public:
//    DataValue();
//    DataValue( const DataValue& arg );
//    DataValue( DataValue&& arg );
//
//    DataValue& operator=( const DataValue& rhv );
//    DataValue& operator=( DataValue&& rhv );
//
//    auto getValue() const;
//    ElementType getType()const;
//
//    void setValue( INode* node );
//    void setValue( const ChildrenNodes& node );
//    void setValue( const bool value );
//    void setValue( const double value );
//    void setValue( const float value );
//    void setValue( const int value );
//    void setValue( const int64_t value );
//    void setValue( const String& value );
//
//    ~DataValue();
//private:
//    union CULLib_API DataUnion
//    {
//        INode* u_object = nullptr;
//        ChildrenNodes u_array;
//        bool u_bool;
//        double u_double;
//        float u_float;
//        int u_int;
//        int64_t u_int64;
//        String u_string;
//    };
//    DataUnion m_union;
//};
//
//
//NAMESPACE_END( JSON )
//NAMESPACE_END( CUL )