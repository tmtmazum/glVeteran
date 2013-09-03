#include <iostream>
#include <GL/glut.h>
#include "API/all.h"

CameraCEU Cam;
Lighting Lights;

MouseAB Mouse;
PosXY MouseDiff;

PosXYZ npScale(1,1,1);
float scale = 1;
PosXYZ translate(0,0,0);
PosXYZ rotates(0,0);

PosXY getMouseDiff( PosXY Current , PosXY Old )
{
    
    PosXY MouseDiff( -(Old.X - Current.X), -(Old.Y -Current.Y) );
    
    if(abs(MouseDiff.X) > abs(MouseDiff.Y)) MouseDiff = PosXY( MouseDiff.X, 0 );
    else MouseDiff = PosXY( 0, MouseDiff.Y );
    
    return PosXY( MouseDiff.X/GLOBAL_WINDOW_WIDTH, MouseDiff.Y/GLOBAL_WINDOW_HEIGHT );
}
void handleKeyPress( unsigned char key, int x, int y )
{
    switch( key )
    {
	case '1':
	    npScale.X += 0.04;
	    break;
	case '2':
	    npScale.X = 1;
	    break;
	case '3':
	    npScale.X -= 0.04;
	    break;
	    
	case '4':
	    npScale.Y += 0.04;
	    break;
	case '5':
	    npScale.Y = 1;
	    break;
	case '6':
	    npScale.Y -= 0.04;
	    break;
	    
	case '7':
	    npScale.Z += 0.04;
	    break;
	case '8':
	    npScale.Z = 1;
	    break;
	case '9':
	    npScale.Z -= 0.04;
	    break;

	case '<':
	    scale -= 0.04;
	    break;
	case '>':
	    scale += 0.04;
	    break;
	    
	case 'j':
	    translate.X -= 0.04;
	    break;
	case 'l':
	    translate.X += 0.04;
	    break;
	case 'k':
	    translate.Y -= 0.04;
	    break;
	case 'i':
	    translate.Y += 0.04;
	    break;
	    
	case 'u':
	    translate.Z -= 0.04;
	    break;
	case 'o':
	    translate.Z += 0.04;
	    break;
	    
	    
	case 'f':
	    rotates.X -= 0.04;
	    break;
	case 'h':
	    rotates.X += 0.04;
	    break;
	case 'g':
	    rotates.Y -= 0.04;
	    break;
	case 't':
	    rotates.Y += 0.04;
	    break;
    }
    
}
void handleKeyUp( unsigned char key , int x , int y ){}
void handleSpecialPress( int key, int x, int y ){}

void handleMousePress( int button, int state, int x, int y )
{
        Mouse.toggleButton( button , state );
    Mouse.setPosition( x, y );
    //if( state == GLUT_DOWN )
    //{
    if(state == GLUT_DOWN) Mouse.savePos();
}
void handleMouseMotion(int x, int y)
{
    Mouse.setPosition( x , y );
    MouseDiff = getMouseDiff( Mouse.At , Mouse.loadPos() );
}
void handleMousePassiveMotion( int x, int y ){}

void handleScreenResize(int width, int height){}

void handleGameInitialize()
{
    Cam.init();
}	// REQUIRED
void handleGameDisplay()
{
    
    if(Mouse.buttonsPressed & MouseAB::MMB) { Cam.translateXYZ( MouseDiff ); }
    if(Mouse.buttonsPressed & MouseAB::LMB) { Cam.rotateXYZ( MouseDiff ); }
    if(Mouse.buttonsPressed & MouseAB::RMB) { Cam.scaleXYZ( MouseDiff ); }
	
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    
    WO line_1;
    line_1.setGeometry( GO::LINE , 0.4 , 0.4 , 0.0 , END_F );
    line_1.set( WO::POSITION , 0.0 , 0.0 , 0.0 , END_F );
    draw3D( line_1 );
	    
    Cam.update();
    Lights.setCenter( Cam.Center );
    Lights.setMode();
    
    glColor4f( 0.1 , 1.0 , 0.1 , 0.95 );
    
    WO single;
    single.setGeometry( GO::FACE , 13.0 , END_F );
    single.set( WO::POSITION , translate.X , translate.Y , translate.Z , END_F );
    single.set( WO::NP_SCALE , npScale.X , npScale.Y , npScale.Z , END_F );
    single.set( WO::ROTATION , rotates.X*PI*10 , rotates.Y*PI*10 , END_F );
    // single.set( WO::ROTATION , 0.0 , PI/2 , END_F );
    single.set( WO::SCALE , scale );
    single.set( WO::COLOR , 1.0 , 1.0 , 1.0 , END_F );
    /*
	    glEnable( GL_LINE_STIPPLE );
	    unsigned short pattern = 43690;
	    glLineStipple(5 , pattern);
    */
    glPolygonMode( GL_FRONT_AND_BACK , GL_FILL );
    
    TextureIF* T1;
    T1 = new TextureIF( "image/Qtiles.bmp" );
    T1->enable();
    draw3D( single );
    T1->disable();
    
    single.setGeometry( GO::CUBE , END_F );
    single.set( WO::SCALE , 0.04 , END_F );
    draw3D( single );
    // draw3D_pure( single , true );
    	//    glDisable( GL_LINE_STIPPLE );

    glutSwapBuffers();

}	// REQUIRED
void handleGameIdle()
{
    handleGameDisplay();
    
}		// REQUIRED

int main(int nArgs , char** args)
{
    GLOBAL_WINDOW_WIDTH = 1000;
    GLOBAL_WINDOW_HEIGHT = 800;
    // GLOBAL_TITLE = "Nada";
    run2D( nArgs , args );
}