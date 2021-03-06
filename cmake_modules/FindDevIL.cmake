set( IL_INCLUDE_DIR ${CUL_DEPS_PATH}/DevIL/DevIL/include  )
set( ENV{IL_INCLUDE_DIR} ${IL_INCLUDE_DIR} )

set( IL_LIBRARIES "1" )
set( ILU_LIBRARIES "1" )

if( MSVC )
    message( "RENEGATE_DIR: ${RENEGATE_DIR}, PLATFORM: ${CMAKE_VS_PLATFORM_NAME}" )
    set( DevIL_BINARIES "" )
    set( DEVIL_OUTPUT_ROOT ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CUL_RENEGATE_DIR}/deps/DevIL/DevIL/lib/${CMAKE_VS_PLATFORM_NAME}/${CMAKE_BUILD_TYPE} )
    list( APPEND DevIL_BINARIES ${DEVIL_OUTPUT_ROOT}/DevIL.dll )
    list( APPEND DevIL_BINARIES ${DEVIL_OUTPUT_ROOT}/ILU.dll )

    message( "DevIL_BINARIES: ${DevIL_BINARIES}" )

    set( DevIL_MSVC_BUILD_PATH )
endif()

set( DevIL_FOUND true )