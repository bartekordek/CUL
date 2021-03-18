set( GLUT_INCLUDE_DIR ${FREEGLUT_HOME}/include )

if( MSVC )
set( GLUT_glut_LIBRARY "" )
else()
endif()

set( GLUT_FOUND true )