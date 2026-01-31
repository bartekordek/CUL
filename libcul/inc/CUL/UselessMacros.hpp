#pragma once

#define CUL_CONCAT_IMPL( a, b ) a##b
#define CUL_CONCAT( a, b ) CUL_CONCAT_IMPL(a, b)

#define CUL_UNIQUE_VAR( base ) CUL_CONCAT( base, __LINE__ )

#define MacroArgumentToStringLiteral( x ) #x
#define StringLiteralToVariableName( name ) var_##name

#define NAMESPACE_BEGIN( name ) namespace name {
#define NAMESPACE_END( name ) }// name

