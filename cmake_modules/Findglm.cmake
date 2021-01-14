message("[Findglm.cmake] begin")

message("[Findglm.cmake] CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message("[Findglm.cmake] ENV{CUL_ROOT_DIR}: $ENV{CUL_ROOT_DIR}")
message("[Findglm.cmake] CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

if( NOT DEFINED ENV{CUL_ROOT_DIR} )
    message(FATAL_ERROR "[Findglm.cmake] ENV{CUL_ROOT_DIR} is not set.")
endif( NOT DEFINED ENV{CUL_ROOT_DIR} )

set( glm_ROOT_DIR $ENV{CUL_ROOT_DIR}/deps/glm )
set( glm_INCLUDE_DIR ${glm_ROOT_DIR} )

message("[Findglm.cmake] glm_INCLUDE_DIR: ${glm_INCLUDE_DIR}")



set( glm_FOUND true )
message("[Findglm.cmake] end")