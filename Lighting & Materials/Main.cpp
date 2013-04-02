/**
Copyright 2007, All Rights Reserved: Zachary Wartell, University of North Carolina at Charlotte
\file Main.cpp
\author Zachary Wartell
\brief Main.cpp is a example of GLUT and OpenGL plus a few ITCS4120::OpenGLTrainer
calls to help setup for simply 2D drawing.

TO DO LIST:
\todo

BUG LIST:
\bug

FOOTNOTES:
- [F1] This is an example footnote.

REFERENCES:
- [R1] Donald Hearn and M. Pauline Baker.  Computer Graphics with OpenGL: Third Edition.
*/

/*******************************************************************************
    Includes	
*******************************************************************************/
#ifdef _WIN32
#include <windows.h>
#endif

#include <assert.h>
#include <time.h>
#include <iostream>

#include <GL/glew.h>   

#include <GL/glut.h>

#include <OpenGLTrainer/OpenGLTrainer.h>

#include <Cube.h>
#include "SphereHelper.h"
using namespace std;

/*******************************************************************************
    File Scope Macros
*******************************************************************************/
/**
\brief enable debugging output to trace primary GLUT callbacks.
*/
//#define TRACE_CALLBACKS

/*******************************************************************************
    File Scope (static) Globals
*******************************************************************************/
//NONE

/*******************************************************************************
    File Scope (static) Functions - To be replaced by Student
*******************************************************************************/
/**
\brief All code in ZJW namespace should be completely replaced by the student to implement
their assignment.
*/
namespace ZJW
    {

    //make all the lighting parameters global, static and const.
    static const GLfloat zero_values [] = {0.0f, 0.0f, 0.0f, 0.0f};
    static const GLfloat ambient_values[] = {0.2, 0.2f, 0.2f, 1.0f};
    static const GLfloat light0_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0};
    static const GLfloat light0_position[] = {10.0, 10.0, 10.0, 0.0};  /* Infinite light location. */

    static const GLfloat light1_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0};
    static const GLfloat light1_position[] = {-10.0, -10.0, 10.0, 0.0};  /* Infinite light location. */

    static const GLfloat light2_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0};
    static const GLfloat light2_position[] = {-10.0, 10.0, -10.0, 0.0};  /* Infinite light location. */

    static const GLfloat light3_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0};
    static const GLfloat light3_position[] = {10.0, -10.0, -10.0, 0.0};  /* Infinite light location. */

    //string variable to hold the light on/off status of lights
    static std::string lightStatus;

    //have parameters for light using which we could turn on/off lights
    static bool light1On = true, //lights are all on by default
	light2On = true,
	light3On = true,
	light4On = true;

    static GLint fogMode;

    //below parameters are required to simulate the motion of the camera in an 
    // 'ARC BALL' fashion.
    static GLfloat cameraSphereRadius = 6.0f;
    static GLfloat u = 0.0f, v = 0.0f;

    //required for camera motion with mouse.
    static GLint mouseX, mouseY;
    static bool mouseLeftDown = false, mouseRightDown = false;

#define PI 3.142

    //get the cameraX location
    static 
	GLfloat getCameraX()
	{
	return cameraSphereRadius * -sinf(u * PI/180) * cosf(v*(PI/180));
	}

    //get the cameraY location
    static
	GLfloat getCameraY()
	{
	return  cameraSphereRadius * -sinf(v*(PI/180));
	}

    //get the cameraZ location
    static
	GLfloat getCameraZ()
	{
	return cameraSphereRadius * cosf(u*(PI/180)) * cosf(v*(PI/180));
	}

    /**
    \brief Print message for showing mouse position
    */
    static void respondMouseMotion(int x, int y)
	{
	//cout << "Mouse: " << x << " " << y << endl;   

	if(ZJW::mouseLeftDown)
	    {
	    ZJW::u += (x - mouseX) * 0.7f;
	    ZJW::v += (y - mouseY) * 0.7f;

	    mouseX = x;
	    mouseY = y;
	    }

	if(ZJW::mouseRightDown)
	    {
	    ZJW::cameraSphereRadius += (y - mouseY) * 0.02f;
	    mouseY = y;
	    }

	glutPostRedisplay();
	}

    /**
    \brief Set basic 3D view for a default fixed camera pose and frustum
    */
    static void setupview()
	{
	/* Setup the view. */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( /* field of view in degree */ 40.0,
	    /* aspect ratio */ 1.0,
	    /* Z near */ 1.0, /* Z far */ 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(getCameraX(), getCameraY(), getCameraZ(),  /* eye is at (0,0,5) */
	    0.0, 0.0, 0.0,      /* center is at (0,0,0) */
	    0.0, 1.0, 0.0);      /* up is in positive Y direction */

	//setup lights in is function so that the light positions remain constant
	//when the camera is moved. Without this, the lights moved along with camera!
	glLightfv(GL_LIGHT0, GL_DIFFUSE, ZJW::light0_diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ZJW::ambient_values);
	glLightfv(GL_LIGHT0, GL_SPECULAR, ZJW::light0_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, ZJW::light0_position);
	
	glLightfv(GL_LIGHT1, GL_DIFFUSE, ZJW::light1_diffuse);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ZJW::ambient_values);
	glLightfv(GL_LIGHT1, GL_SPECULAR, ZJW::light1_diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, ZJW::light1_position);
	
	glLightfv(GL_LIGHT2, GL_DIFFUSE, ZJW::light2_diffuse);
	glLightfv(GL_LIGHT2, GL_AMBIENT, ZJW::ambient_values);
	glLightfv(GL_LIGHT2, GL_SPECULAR, ZJW::light2_diffuse);
	glLightfv(GL_LIGHT2, GL_POSITION, ZJW::light2_position);
	
	glLightfv(GL_LIGHT3, GL_DIFFUSE, ZJW::light3_diffuse);
	glLightfv(GL_LIGHT3, GL_AMBIENT, ZJW::ambient_values);
	glLightfv(GL_LIGHT3, GL_SPECULAR, ZJW::light3_diffuse);
	glLightfv(GL_LIGHT3, GL_POSITION, ZJW::light3_position);

	}

    static Cube cube;

    // \brief draw some random stuff
    static void draw_frame()
	{	
	//cube.draw();
	}

    } // namespace
/*******************************************************************************
    File Scope (static) Functions
*******************************************************************************/

/**
\brief Simulate next time step in animation
*/
static void simulateNextTimeStep(void)
    {
    static clock_t lastTime = 0;

    /** update any animated objects' state */
    clock_t now;

    /* compute current time and time since last frame */
    now = clock ();

    if (lastTime)
	{// lastTime is initialize, so compute delta time
	float seconds=(float)(now - lastTime)/CLK_TCK;

	/* update all Animatible's data members based on time based since last frame */		
	//ZJW::cube.animate(seconds);
	}

    /* record current time */
    lastTime=now;
    }

/**
\brief initialize some default OGL settings
*/
static
void initOpenGL (void)
    {
    
    SphereHelper::createDisplayLists();

    //set clear color to white
    glClearColor(0.0f,0.0f,0.0f,0.0f);     

    //Enable lighting and all the four lights.
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);

    // enable depth buffering
    glEnable(GL_DEPTH_TEST);

    //Enable face culling
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_NORMALIZE);

    /*glEnable(GL_FOG);
    {
    GLfloat fogColor[4] = {0.5, 0.5, 0.5, 1.0};

    ZJW::fogMode = GL_EXP;
    glFogi (GL_FOG_MODE, ZJW::fogMode);
    glFogfv (GL_FOG_COLOR, fogColor);
    glFogf (GL_FOG_DENSITY, 0.35);
    glHint (GL_FOG_HINT, GL_DONT_CARE);
    glFogf (GL_FOG_START, 1.0);
    glFogf (GL_FOG_END, 5.0);
    }
    glClearColor(0.5, 0.5, 0.5, 1.0);*/  

    glShadeModel(GL_SMOOTH);
    }

/**
\brief 'motionFunc' is the GLUT motionFunc callback function
*/
static
void motionFunc 
	(
	int gx,  // 'glutX' - mouse X in GLUT coordinates
	int gy   // 'glutY' - mouse Y in GLUT coordinates
	)
    {
    /* convert from GLUT coordinate system to the 2D drawing coordinate system
       established by ITCS4120::OpenGLTrainer::matchWorldCoordinatesToPixelCoordinates 
     */
    const int WIDTH = glutGet(GLUT_WINDOW_WIDTH);
    const int HEIGHT = glutGet(GLUT_WINDOW_HEIGHT);

    int sx,sy; // 'screenX', 'screenY'  mouse coordinate in our 2D screen coordinates
    sx = gx;
    sy = HEIGHT-gy;

    /* do something with mouse motion */
    ZJW::respondMouseMotion(sx,sy);
    }

void drawSpheres()
    {
    SphereHelper::renderSpheres();
    }

static
void printLightsStatus()
    {
    
    ZJW::lightStatus.clear();
    if(ZJW::light1On)
	ZJW::lightStatus.append("Light 1: ON; ");
    else ZJW::lightStatus.append("Light 1: OFF; ");

    if(ZJW::light2On)
	ZJW::lightStatus.append("Light 2: ON; ");
    else ZJW::lightStatus.append("Light 2: OFF; ");

    if(ZJW::light3On)
	ZJW::lightStatus.append("Light 3: ON; ");
    else ZJW::lightStatus.append("Light 3: OFF; ");

    if(ZJW::light4On)
	ZJW::lightStatus.append("Light 4: ON; ");
    else ZJW::lightStatus.append("Light 4: OFF; ");

    std::cout<<ZJW::lightStatus.c_str()<<std::endl;
    }

/**
\brief 'display' is the GLUT display callback function (see [F2])

FOOTNOTES:
[F1] Note, OGL calls are only legal during execution of a GLUT display callback.  Below 
	is a standard method to make any OpenGL calls that we wish to make only the first
	time the GLUT display callback is executed.
[F2] DESIGN CHOICE: simulation of next time step is put in 'idle' callback and separated from
'display' callback.  This allows simulation to keep running even if the window is minimized
(in which case the display callback stops being called).  Other designs are of course possible.
To understand this design enable TRACE_CALLBACKS and toggle the window between it's minimized 
and non-minimized state and observe the console output. 
*/
static
void display(void)
    {      
    /**
	perform any 'one time' setup OGL calls (see [F1])
     **/
    static boolean doOnce=true;
    if (doOnce)
	{
	initOpenGL();
	doOnce = false;
	}

    /**
	setup frame
     **/   
    // clear screen
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // setup view
    ZJW::setupview();

    /**
	draw frame
     **/
    ZJW::draw_frame();

    /*GLfloat dimRed[] = {0.5f, 0.0f, 0.0f, 1.0f};
    GLfloat white [] = {1.0f, 1.0f, 1.0f, 1.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, dimRed);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 48);
    glutSolidSphere(1.0f, 100, 100);*/

    drawSpheres();

    /**
	end frame
     **/		
    ITCS4120::OpenGLTrainer::showFrameRate();		
    assert(glGetError()==GL_NO_ERROR);
    glutSwapBuffers();

   #ifdef TRACE_CALLBACKS
	cout << "display" << endl;
   #endif
    }

/**
\brief 'idle' is the GLUT idle callback function (see [F2])
*/
static
void idle(void)
    {	
    /** simulate next time step (in current approach simulation will keep running even if  
	    window is minimize)
	 **/
	simulateNextTimeStep();
	
    /** trigger display callback to redraw scene based on object's updated state (see [F2]) */
    glutPostRedisplay();

   #ifdef TRACE_CALLBACKS
	cout << "idle" << endl;
   #endif
    }

/**
\brief 'reshape' is the GLUT idle callback function
*/
static
void reshape(int width, int height)
    {    
    /* use the entire Window area for OpenGL drawing */
    glViewport( 0, 0,(GLsizei)width,(GLsizei)height);

    /* Setup the view. */
    ZJW::setupview();

    /** trigger display callback to redraw scene based on new window size */
    glutPostRedisplay();
    }

static
    void keyHandler(unsigned char c, int x, int y)
    {
    switch(c)
	{
    case 49:
	{
	if(ZJW::light1On)
	    {
	    glDisable(GL_LIGHT0);
	    ZJW::light1On = false;
	    }
	else
	    {
	    glEnable(GL_LIGHT0);
	    ZJW::light1On = true;
	    }
	break;
	}

    case 50:
	{
	if(ZJW::light2On)
	    {
	    glDisable(GL_LIGHT1);
	    ZJW::light2On = false;
	    }
	else
	    {
	    glEnable(GL_LIGHT1);
	    ZJW::light2On = true;
	    }
	break;
	}
    case 51:
	{
	if(ZJW::light3On)
	    {
	    glDisable(GL_LIGHT2);
	    ZJW::light3On = false;
	    }
	else
	    {
	    glEnable(GL_LIGHT2);
	    ZJW::light3On = true;
	    }
	break;
	}
    case 52:
	{
	if(ZJW::light4On)
	    {
	    glDisable(GL_LIGHT3);
	    ZJW::light4On = false;
	    }
	else
	    {
	    glEnable(GL_LIGHT3);
	    ZJW::light4On = true;
	    }
	break;
	}

	}

    printLightsStatus();

    if(c == 'w')
	ZJW::v -= 0.3f;

    if(c == 's')
	ZJW::v += 0.3f;

    if(c == 'a')
	ZJW::u -= 0.3f;

    if(c == 'd')
	ZJW::u += 0.3f;

    glutPostRedisplay();
    }

static
    void mouseHandler(int button, int state, int x, int y)
    {
    ZJW::mouseX = x;
    ZJW::mouseY = y;

    if(state == GLUT_DOWN)
	{
	if(button == GLUT_LEFT_BUTTON)
	    ZJW::mouseLeftDown = true;
	else 
	    ZJW::mouseRightDown = true;
	}

    if(state == GLUT_UP)
	{
	if(button == GLUT_LEFT_BUTTON)
	    ZJW::mouseLeftDown = false;
	else 
	    ZJW::mouseRightDown = false;
	}
    }

/**
\brief 'main' is the standard C/C++ main function where execution starts
*/
int main (int argc, char** argv)
    {       
    /* Initialize GLUT library */
    glutInit(&argc, argv);

    /* create window */    
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
    glutCreateWindow("Cube Skeleton I");
    
    /** init ITCS4120::OpenGLTrainer classes */
    ITCS4120::OpenGLTrainer::init(&argc,argv);    

    /* set glut callbacks */
    glutDisplayFunc (display);
    glutIdleFunc (idle);
    glutMouseFunc (mouseHandler);
    glutMotionFunc (motionFunc);     
    glutReshapeFunc (reshape);
    glutKeyboardFunc (keyHandler);

    /* start GLUT main loop */
    glutMainLoop();
    return 0;
    }