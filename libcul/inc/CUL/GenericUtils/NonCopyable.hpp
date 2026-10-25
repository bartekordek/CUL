#pragma once

#define CUL_NONCOPYABLE( TypeName )                  \
public:                                              \
    TypeName( TypeName&& ) = delete;                 \
    TypeName( const TypeName& ) = delete;            \
    TypeName& operator=( const TypeName& ) = delete; \
    TypeName& operator=( TypeName&& ) = delete;

// Copy-deleted, move-enabled (e.g. types that own unique_ptr / variant payloads).
#define CUL_NONCOPYABLE_MOVABLE( TypeName )          \
public:                                              \
    TypeName( const TypeName& ) = delete;            \
    TypeName& operator=( const TypeName& ) = delete; \
    TypeName( TypeName&& ) = default;                \
    TypeName& operator=( TypeName&& ) = default;
