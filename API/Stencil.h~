#ifndef STENCIL_H
#define STENCIL_H

#include <GL/glut.h>

int GLOBAL_STENCIL_MODE = 0;
int GLOBAL_STENCIL_WRITE_VALUE = 0;

namespace Stencil
{
    
enum
{
    DISABLED=0,
    SET_PICK_ID
};

    void setMode(int i)
    {
	if(GLOBAL_STENCIL_MODE != i )
	{
	    switch(i)
	    {
		case 0:
		    glDisable( GL_STENCIL_TEST );
		    break;
		case SET_PICK_ID:
		    glEnable( GL_STENCIL_TEST );
		    glStencilOp( GL_KEEP , GL_KEEP , GL_REPLACE );
		    glClearStencil(0);
	    }
	    GLOBAL_STENCIL_MODE = i;
	}
    }
    inline void disable()
    { setMode(DISABLED); }
    
    void setWriteValue( int a )
    {
	glStencilFunc( GL_ALWAYS , a , -1 );
    }
};

#endif