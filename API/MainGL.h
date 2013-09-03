#include <GL/glut.h>
#include <string>

void handleKeyPress( unsigned char key, int x, int y );
void handleKeyUp( unsigned char key , int x , int y );
void handleSpecialPress( int key, int x, int y );

void handleMousePress( int button, int state, int x, int y );
void handleMouseMotion(int x, int y);
void handleMousePassiveMotion( int x, int y );

void handleScreenResize(int width, int height);

void handleGameInitialize();	// REQUIRED
void handleGameDisplay();	// REQUIRED
void handleGameIdle();		// REQUIRED

float GLOBAL_WINDOW_WIDTH = 800;
float GLOBAL_WINDOW_HEIGHT = 600;

float GLOBAL_WINDOW_POS_X = 10;
float GLOBAL_WINDOW_POS_Y = 10;

float GLOBAL_CLEAR_COLOR_R = 0.7;
float GLOBAL_CLEAR_COLOR_G = 0.7;
float GLOBAL_CLEAR_COLOR_B = 0.7;
float GLOBAL_CLEAR_COLOR_A = 0.7;

std::string GLOBAL_TITLE = "Default Project Title";

void inline run2D(int numArguments , char** arguments)
{
    glutInit(&numArguments, arguments);
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH );
 
    glutInitWindowSize( GLOBAL_WINDOW_WIDTH, GLOBAL_WINDOW_HEIGHT );
    glutInitWindowPosition( GLOBAL_WINDOW_POS_X,GLOBAL_WINDOW_POS_Y);
    glutCreateWindow( GLOBAL_TITLE.c_str() );
    
    handleGameInitialize();
    glClearColor( GLOBAL_CLEAR_COLOR_R,
		  GLOBAL_CLEAR_COLOR_G,
		  GLOBAL_CLEAR_COLOR_B,
		  GLOBAL_CLEAR_COLOR_A );
	
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );
    
    glutWarpPointer( GLOBAL_WINDOW_WIDTH / 2 , GLOBAL_WINDOW_HEIGHT / 2 );
    gluOrtho2D(0, 1, 0, 1);

    
    glutDisplayFunc(handleGameDisplay);
    glutIdleFunc(handleGameIdle);
    
    glutKeyboardFunc(handleKeyPress);
    glutKeyboardUpFunc(handleKeyUp);
    glutSpecialFunc(handleSpecialPress);
    glutMouseFunc(handleMousePress);
    glutPassiveMotionFunc(handleMousePassiveMotion);
    glutMotionFunc(handleMouseMotion);
    glutReshapeFunc(handleScreenResize);
    // glutMouseWheelFunc(handleMouseWheel);
    
    glutMainLoop();
}