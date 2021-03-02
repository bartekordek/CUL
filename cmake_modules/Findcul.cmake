message("[Findcul.cmake] begin")

# Check if paths are set.
#if(NOT DEFINED ${VAR_NAME})

message("[Findcul.cmake] CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message("[Findcul.cmake] ENV{CUL_ROOT_DIR}: $ENV{CUL_ROOT_DIR}")
message("[Findcul.cmake] CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

if( NOT DEFINED ENV{CUL_ROOT_DIR} )
    message(FATAL_ERROR "[Findcul.cmake] ENV{CUL_ROOT_DIR} is not set.")
endif( NOT DEFINED ENV{CUL_ROOT_DIR} )

set( cul_INCLUDE_DIR $ENV{CUL_ROOT_DIR}/libcul/inc )
set( ENV{cul_INCLUDE_DIR} ${cul_INCLUDE_DIR} )
message("[Findcul.cmake] cul_INCLUDE_DIR: ${cul_INCLUDE_DIR}")

list( APPEND CUL_LIB_PATHS $ENV{CUL_OUTPUT_DIR} )
list( APPEND CUL_LIB_PATHS $ENV{CUL_OUTPUT_DIR}/${CMAKE_BUILD_TYPE} )
list( APPEND CUL_LIB_PATHS $ENV{CUL_ROOT_DIR} )

message("[Findcul.cmake] find_library cul in:")
foreach(dir_path IN LISTS CUL_LIB_PATHS)
    message("[Findcul.cmake] ${dir_path}")
endforeach()

#find_library( cul_LIBRARY_TEMP
#    NAMES cul
#    HINTS ${CUL_LIB_PATHS}
#)
#message("[Findcul.cmake] cul_LIBRARY_TEMP: ${cul_LIBRARY_TEMP}")
set( cul_LIBRARY_TEMP $ENV{CUL_OUTPUT_DIR}/${CMAKE_BUILD_TYPE}/cul.lib )
set( cul_LIBRARY ${cul_LIBRARY_TEMP} )
set( cul_BINARY $ENV{CUL_OUTPUT_DIR}/${CMAKE_BUILD_TYPE}/cul.dll )
set( cul_SYMBOLS $ENV{CUL_OUTPUT_DIR}/${CMAKE_BUILD_TYPE}/cul.pdb )
set( ENV{cul_LIBRARY} ${cul_LIBRARY} )
set( cul_DIR $ENV{CUL_ROOT_DIR} )

set( cul_FOUND true )
message("[Findcul.cmake] end")