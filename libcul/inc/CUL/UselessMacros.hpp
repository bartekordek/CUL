#pragma once

#define NAMESPACE_BEGIN( name ) namespace name {
#define NAMESPACE_END( name ) }// name


#define CUL_NONCOPYABLE( TypeName ) \
public: \
TypeName( TypeName&& ) = delete;                 \
TypeName( const TypeName& ) = delete;            \
TypeName& operator=( const TypeName& ) = delete; \
TypeName& operator=( TypeName&& ) = delete;
