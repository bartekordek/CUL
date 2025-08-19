#pragma once

#if defined(_MSC_VER)
#define CUL_MSVC_SKIP_DEFAULT_WARNING_BEGIN __pragma( warning( push, 0 ) )\
__pragma( warning( disable: 1404 ) )\
__pragma( warning( disable: 3909 ) )\
__pragma( warning( disable: 4005 ) )\
__pragma( warning( disable: 4100 ) )\
__pragma( warning( disable: 4146 ) )\
__pragma( warning( disable: 4242 ) )\
__pragma( warning( disable: 4251 ) )\
__pragma( warning( disable: 4267 ) )\
__pragma( warning( disable: 4312 ) )\
__pragma( warning( disable: 4355 ) )\
__pragma( warning( disable: 4365 ) )\
__pragma( warning( disable: 4371 ) )\
__pragma( warning( disable: 4464 ) )\
__pragma( warning( disable: 4505 ) )\
__pragma( warning( disable: 4514 ) )\
__pragma( warning( disable: 4571 ) )\
__pragma( warning( disable: 4623 ) )\
__pragma( warning( disable: 4625 ) )\
__pragma( warning( disable: 4626 ) )\
__pragma( warning( disable: 4668 ) )\
__pragma( warning( disable: 4710 ) )\
__pragma( warning( disable: 4711 ) )\
__pragma( warning( disable: 4715 ) )\
__pragma( warning( disable: 4774 ) )\
__pragma( warning( disable: 4800 ) )\
__pragma( warning( disable: 4820 ) )\
__pragma( warning( disable: 4996 ) )\
__pragma( warning( disable: 5026 ) )\
__pragma( warning( disable: 5027 ) )\
__pragma( warning( disable: 5039 ) )\
__pragma( warning( disable: 5045 ) )\
__pragma( warning( disable: 5204 ) )\
__pragma( warning( disable: 5262 ) )\
__pragma( warning( disable: 5264 ) )\
__pragma( warning( disable: 5266 ) )\
__pragma( warning( disable: 6011 ) )\
__pragma( warning( disable: 6262 ) )\
__pragma( warning( disable: 6308 ) )\
__pragma( warning( disable: 26409 ) )\
__pragma( warning( disable: 26429 ) )\
__pragma( warning( disable: 26432 ) )\
__pragma( warning( disable: 26433 ) )\
__pragma( warning( disable: 26434 ) )\
__pragma( warning( disable: 26436 ) )\
__pragma( warning( disable: 26447 ) )\
__pragma( warning( disable: 26451 ) )\
__pragma( warning( disable: 26462 ) )\
__pragma( warning( disable: 26472 ) )\
__pragma( warning( disable: 26477 ) )\
__pragma( warning( disable: 26481 ) )\
__pragma( warning( disable: 26486 ) )\
__pragma( warning( disable: 26494 ) )\
__pragma( warning( disable: 26495 ) )\
__pragma( warning( disable: 26496 ) )\
__pragma( warning( disable: 26812 ) )\
__pragma( warning( disable: 26819 ) )\
__pragma( warning( disable: 28182 ) )\
__pragma( warning( disable: 33010 ) )
#define CUL_MSVC_SKIP_DEFAULT_WARNING_END __pragma( warning( pop ) )

#else
#define CUL_MSVC_SKIP_DEFAULT_WARNING_BEGIN
#define CUL_MSVC_SKIP_DEFAULT_WARNING_END
#endif
