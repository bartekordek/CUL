set( FREEGLUT_HOME ${CUL_DEPS_PATH}/freeglut-3.2.1 )

set( freeglut_INCLUDE_DIR ${FREEGLUT_HOME}/include )
set( ENV{freeglut_INCLUDE_DIR} ${freeglut_INCLUDE_DIR} )

set( freeglut_LIBRARY_TEMP freeglut )
set( freeglut_LIBRARY freeglut} )
set( freeglut_DIR $ENV{CUL_ROOT_DIR} )

set( freeglut_FOUND true )