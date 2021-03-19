
set( OPENGL_INCLUDE_DIR ${freeglut_INCLUDE_DIR} )
set( OPENGL_opengl_LIBRARY ${freeglut_LIBRARY} )
set( OPENGL_glx_LIBRARY ${freeglut_LIBRARY} )
set( OpenGL_FOUND true )

message( "OPENGL_INCLUDE_DIR: ${OPENGL_INCLUDE_DIR}" )
message( "OPENGL_opengl_LIBRARY: ${OPENGL_opengl_LIBRARY}" )

mark_as_advanced( OpenGL_FOUND OPENGL_INCLUDE_DIR OPENGL_opengl_LIBRARY OPENGL_glx_LIBRARY )