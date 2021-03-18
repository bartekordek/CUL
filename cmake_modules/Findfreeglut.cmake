set( FREEGLUT_HOME {CMAKE_CURRENT_SOURCE_DIR}/../freeglut-3.2.1 )

set( freeglut_INCLUDE_DIR ${FREEGLUT_HOME}/include )

set( freeglut_LIBRARY_TEMP $ENV{CUL_OUTPUT_DIR}/${CMAKE_BUILD_TYPE}/freeglut.lib )
set( freeglut_LIBRARY ${freeglut_LIBRARY_TEMP} )
set( freeglut_DIR $ENV{CUL_ROOT_DIR} )

set( freeglut_FOUND true )