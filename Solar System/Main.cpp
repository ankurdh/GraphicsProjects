/**
Copyright 2007, All Rights Reserved: Zachary Wartell, University of North Carolina at Charlotte
\file Main.cpp
\author Zachary Wartell
\brief Main.cpp file

Dr. Wartell gives students the .h files with the C++ class already designed. Students in his
courses are responsible for implementing the class member functions and adding additional
ones as needed.
*/
#ifdef _WIN32
// MS Windows graphical apps require this as the first line in each .cpp file
#include <windows.h>
#endif
#include <iostream>
#include <sstream>
using namespace std;

#include <OpenGLTrainer/OpenGLTrainer.h>

#include <GL/gl.h>
#include <GL/glut.h>
#include <time.h>

#include <cmath>

#include "CoordinateSystem.h"
#include "UnitDisk.h"

/*******************************************************************************
    File Scope (static) Globals
*******************************************************************************/
using namespace ITCS4120;

// 'timer' records time elapsed when we displayed our last frame
static OpenGLTrainer::Timer timer;
// 'root' is the root CoordinateSystem in our CoordinateSystem tree.
static CoordinateSystem rootCS;

// 
static UnitDisk disc;
// local coordinate system for 'disc'
static CoordinateSystem discCS;
// coordinate system of orbit of 'disc'
static CoordinateSystem discOrbitCS;

static UnitDisk planets[8];

static Point2 winMaxXY(650, 650);

/*
    Ankur: These are the co-ordinate system heirarchy objects.
*/
static CoordinateSystem earthOrbitCS;
static CoordinateSystem moonOrbitCS;
static CoordinateSystem saturnOrbitCS;
static CoordinateSystem saturnMoonOrbitCS;
static CoordinateSystem saturnMoonDebrisOrbitCS;
static CoordinateSystem uranusOrbitCS;

static CoordinateSystem earthCS;
static CoordinateSystem moonCS;
static CoordinateSystem saturnCS;
static CoordinateSystem saturnMoonCS;
static CoordinateSystem saturnMoonDebrisCS;
static CoordinateSystem uranusCS;

/**
ViewWindow stores the coordinates of rectangular window in world space
that is mapped to the GUI window. Hence it determines the transformation
between world coordinates and GUI window coordinates.
*/

//Declare a string object to hold the name of the planet clicked on.
string tmp;
string lightInfo = "'l': Lights On/Off", speedInfo = "Up/Down Keys for speed";

//Declare a variable to control the speed of revolution/rotation of the planets.
float multFactor = 1.0f;

class ViewWindow
    {
    public:
    ViewWindow();
    // coordinate of lower left corner
    Point2 lowerLeft;
    // coordinate of upper right corner
    Point2 upperRight;
    // \todo might be useful to add methods to compute the windows width and height 
    };

// viewWindow is the applications global View Window
const ViewWindow viewWindow;

/**
Stores GUI window info.
*/
class GUIWindow
    {
    public:
    GUIWindow(float width, float height)
	{
	this->width = width;
	this->height = height;
	}
    float width;
    float height;
    };
GUIWindow guiWindow(650, 650);

/*******************************************************************************
    File Scope (static) Functions
*******************************************************************************/

/**
\brief Construct this ViewWindow

FOOTNOTES:
- [F2] We assume world coordinate (-1000,-1000) maps to the lower-left of the window,
(1000,1000) maps to the upper-right.  Implicitly, then (0,0) is at the window center,
with x-axis to the right and y-axis pointing up.
*/
ViewWindow::ViewWindow()
    {
    lowerLeft = Point2 (-1000,-1000);
    upperRight = Point2 (1000,1000);
    }

/**
\brief Initialize default OGL settings. 

Here we initialize any OGL settings that we do not expect to change during the
execution of our program. All OGL calls must be made from the context of the
display callback to guarantee the executing thread currently has access to the 
OpenGL pipeline; hence initial OGL setup is done in 'initOpenGLDefaults'.
*/
static
void initOpenGLDefaults (void)
    {
    glClearColor(0.0f,0.0f,0.0f,1.0f);

    //tell openGL that no depth test is required.
    glDisable(GL_DEPTH_TEST);

    //enable lighting.
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //Tell OpenGL that the colors assigned to the planets should be visible.
    glEnable(GL_COLOR_MATERIAL);

    //tell OpenGL that all the objects are rendered on XY plane
    glNormal3d(0, 0, 1);

    GLfloat light1Location[] = {0.0f, 0.0f, 1.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light1Location);

    //Not specifying any light components explicitly. Let openGL use the default values.

    }

/*
\brief Init application data structures, etc.

*/
static void init()
    {   

    planets[0] = UnitDisk(1, "Sun",  &rootCS);	//say planet0 is the sun
    planets[1] = UnitDisk(2, "Earth", &earthCS); //say planet1 is earth
    planets[2] = UnitDisk(3, "Moon", &moonCS); //say planet2 is moon

    planets[3] = UnitDisk(4, "Saturn", &saturnCS); //saturn
    planets[4] = UnitDisk(5, "Saturn Moon", &saturnMoonCS); //saturn first moon
    planets[5] = UnitDisk(6, "Saturn Moon Debris", &saturnMoonDebrisCS); //saturn moon debris 
    
    planets[6] = UnitDisk(7, "Uranus", &uranusCS);

    /** build our coordinate system hierarchy */
    
    rootCS.origin = Point2(0.0f, 0.0f);
    rootCS.orientation = 0.0f;
    rootCS.scale[0] = rootCS.scale[1] = 100.0f;
    rootCS.addCoordinateSystem(earthOrbitCS);
    rootCS.addCoordinateSystem(saturnOrbitCS);
    rootCS.addCoordinateSystem(uranusOrbitCS);
    rootCS.addShape(planets[0]);

    earthOrbitCS.origin = Point2(0.0f, 0.0f);
    earthOrbitCS.scale[0] = earthOrbitCS.scale[1] = 1.0f;
    earthOrbitCS.addCoordinateSystem(earthCS);
    earthOrbitCS.addCoordinateSystem(moonOrbitCS);

    saturnOrbitCS.origin = Point2(0.0f, 0.0f);
    saturnOrbitCS.scale[0] = saturnOrbitCS.scale[1] = 1.0f;
    saturnOrbitCS.addCoordinateSystem(saturnCS);
    saturnOrbitCS.addCoordinateSystem(saturnMoonOrbitCS);

    uranusOrbitCS.origin = Point2(0.0f, 0.0f);
    uranusOrbitCS.scale[0] = uranusOrbitCS.scale[1] = 1.0f;
    uranusOrbitCS.addCoordinateSystem(uranusCS);

    earthCS.origin = Point2(2.0f, -2.0f);
    earthCS.scale[0] = 0.5f, earthCS.scale[1] = 0.5f;
    earthCS.addShape(planets[1]);

    moonOrbitCS.origin = Point2(2.0f, -2.0f);
    moonOrbitCS.scale[0] = 1.0f, moonOrbitCS.scale[1] = 1.0f;
    moonOrbitCS.addCoordinateSystem(moonCS);

    moonCS.origin = Point2(0.70f, 0.70f);
    moonCS.scale[0] = 0.2f, moonCS.scale[1] = 0.13f;
    moonCS.addShape(planets[2]);

    saturnCS.scale[0] = 0.8f, saturnCS.scale[1] = 0.8f;
    saturnCS.origin = Point2(5.0f, 5.0f);
    saturnCS.addShape(planets[3]);

    saturnMoonOrbitCS.origin = Point2(5.0f, 5.0f);
    saturnMoonOrbitCS.scale[0] = saturnMoonOrbitCS.scale[1] = 0.50f;
    saturnMoonOrbitCS.addCoordinateSystem(saturnMoonCS);
    saturnMoonOrbitCS.addCoordinateSystem(saturnMoonDebrisOrbitCS);

    saturnMoonCS.origin = Point2(2.3f, 2.3f);
    saturnMoonCS.scale[0] = saturnMoonCS.scale[1] = 0.6f;
    saturnMoonCS.addShape(planets[4]);

    saturnMoonDebrisOrbitCS.origin = Point2(2.3f, 2.3f);
    saturnMoonDebrisOrbitCS.scale[0] = saturnMoonDebrisOrbitCS.scale[1] = 0.60f;
    saturnMoonDebrisOrbitCS.addCoordinateSystem(saturnMoonDebrisCS);

    saturnMoonDebrisCS.origin = Point2(1.20f, 1.20f);
    saturnMoonDebrisCS.scale[0] = 0.5f, saturnMoonDebrisCS.scale[1] = 0.3f;
    saturnMoonDebrisCS.addShape(planets[5]);

    uranusCS.origin = Point2(3.0f, -3.3f);
    uranusCS.scale[0] = 0.8f, uranusCS.scale[1] = 0.4f;
    uranusCS.addShape(planets[6]);

    }

/* updateSimulation executes one time step in our simulation code which
updates all our 2D object's for the next time step. 
*/
static void simulateNextFrame()
    {
    const float ROTATIONAL_VELOCITY = 25.0; // degrees per second
    const float SATURN_ROTATIONAL_VELOCITY = 7.0f;
    const float MOON_ROTATIONAL_VELOCITY = 500.0f;
    const float LEVEL1_ORBIT_VELOCITY = 8.0; // degrees per second
    const float LEVEL2_ORBIT_VELOCITY = 90.0f;

    const float SATURN_MOON_ORBIT_VELOCITY = 25.0f;
    const float SATURN_MOON_ROTATIONAL_VELOCITY = 35.0f;

    const float SATURN_MOON_DEBRIS_ORBIT_VELOCITY = 35.0f;
    const float SATURN_MOON_DEBRIS_ROT_VELOCITY = 300.0f;
        
    /** 
	compute how much time past since last simulation step 
     **/
    ::timer.lap();
    const float delta = ::timer.lastLapInterval();    
    
    /**
	update our simulation
     **/
    
    earthOrbitCS.orientation += LEVEL1_ORBIT_VELOCITY * 2 * delta * multFactor;
    earthOrbitCS.orientation = fmod(earthOrbitCS.orientation, 360.0f);

    moonOrbitCS.orientation += LEVEL2_ORBIT_VELOCITY * delta * multFactor;
    moonOrbitCS.orientation = fmod(moonOrbitCS.orientation, 360.0f);

    earthCS.orientation += ROTATIONAL_VELOCITY * delta * multFactor;
    earthCS.orientation = fmod(earthCS.orientation, 360.0f);

    moonCS.orientation += MOON_ROTATIONAL_VELOCITY * delta * multFactor;
    moonCS.orientation = fmod(moonCS.orientation, 360.0f);

    saturnOrbitCS.orientation += LEVEL1_ORBIT_VELOCITY * delta * multFactor;
    saturnOrbitCS.orientation = fmod(saturnOrbitCS.orientation, 360.0f);

    saturnCS.orientation += SATURN_ROTATIONAL_VELOCITY * delta * multFactor;
    saturnCS.orientation = fmod(saturnCS.orientation, 360.0f);

    saturnMoonOrbitCS.orientation += SATURN_MOON_ORBIT_VELOCITY * delta * multFactor;
    saturnMoonOrbitCS.orientation = fmod(saturnMoonOrbitCS.orientation, 360.0f);

    saturnMoonCS.orientation += SATURN_MOON_ROTATIONAL_VELOCITY * delta * multFactor;
    saturnMoonCS.orientation = fmod(saturnMoonCS.orientation, 360.0f);

    saturnMoonDebrisOrbitCS.orientation += SATURN_MOON_DEBRIS_ORBIT_VELOCITY * delta * multFactor;
    saturnMoonDebrisOrbitCS.orientation = fmod(saturnMoonDebrisOrbitCS.orientation, 360.0f);

    saturnMoonDebrisCS.orientation += SATURN_MOON_DEBRIS_ROT_VELOCITY * delta * multFactor;
    saturnMoonDebrisCS.orientation = fmod(saturnMoonDebrisCS.orientation, 360.0f);

    uranusOrbitCS.orientation += LEVEL1_ORBIT_VELOCITY * 4 * delta * multFactor;
    uranusOrbitCS.orientation = fmod(uranusOrbitCS.orientation, 360.0f);

    uranusCS.orientation += ROTATIONAL_VELOCITY * 6 * delta * multFactor;
    uranusCS.orientation = fmod(uranusCS.orientation , 360.0f);

    }


/**
\brief Mouse callback function

FOOTNOTES:
- [F1] - mouse coordinates are measured in a coordinate system with the origin at the top-left of screen,
x-axis points to the right, y-axis points _down_. Measurement is in pixels.
*/
static
void mouse(int button, int state, int x, int y)
    {
    Point2 cursor(x,y);
    
    // transform cursor from mouse coordinate system (see [F1]) to world coordinate system (see [F2])
    Matrix3x3 world_from_mouse(Matrix3x3::IDENTITY_MATRIX);
    // \todo compute world_from_mouse and use it to transform 'cursor' to world space 
    // (see textbook, Chapter 6 on view port mapping transform)

    GLfloat xwMin = 0.0f, xwMax = guiWindow.width;
    GLfloat ywMin = guiWindow.height, ywMax = 0.0f;
    GLfloat xvMin = viewWindow.lowerLeft[0], xvMax = viewWindow.upperRight[0];
    GLfloat yvMin = viewWindow.lowerLeft[1], yvMax = viewWindow.upperRight[1];

    //assign the transformation from normal square to viewport
    world_from_mouse.assign( (xvMax - xvMin)/2, 0.0f, (xvMax + xvMin)/2,
	0.0f, (yvMax - yvMin)/2 , (yvMax + yvMin)/2, 
	0.0f, 0.0f, 1.0f);

    //post multiply the transformation from window to normal square.
    world_from_mouse.postMultiply(Matrix3x3(2/(xwMax - xwMin), 0.0f, -(xwMax + xwMin)/(xwMax - xwMin),
	0.0f, 2/(ywMax - ywMin), -(ywMax + ywMin)/(ywMax - ywMin),
	0.0f, 0.0f, 1.0f));

    Point2 clickInWorld = world_from_mouse * Point2(x, y);

    tmp.clear();

    // handle button press events
    for(int i = 0 ; i < 8 ; i ++)
	if(planets[i].contains(clickInWorld))
	    {
	    std::ostringstream planet;
	    planet << "Celestial Object clicked on: " << planets[i].getName();
	    tmp += planet.str();
	    break;
	    }

    }

/**
\brief 'display' is the GLUT display callback function
*/
static
void display(void)
    {   

    /**
	update our simulation for next time step
     **/  
    simulateNextFrame();

    /**
	start frame
     **/ 
    static bool inited=false;
    if (!inited)
	{
	initOpenGLDefaults();
	inited = true;
	}

    glClear(GL_COLOR_BUFFER_BIT);

    /** recursively render all objects in our coordinate system hierarchy */
    rootCS.render();

    glColor3ub(255,130,10);
    glRasterPos2i(viewWindow.lowerLeft[0], viewWindow.upperRight[1] - 50);

    for( size_t i = 0; i < tmp.size(); ++i )
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, tmp[i]);
    }

    glColor3ub(255,255,0);
    glRasterPos2i(viewWindow.lowerLeft[0] + 1200, viewWindow.upperRight[1] - 1900);
    for( size_t i = 0; i < lightInfo.size(); ++i )
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, lightInfo[i]);
    }

    glRasterPos2i(viewWindow.lowerLeft[0] + 1200, viewWindow.upperRight[1] - 1980);
    for( size_t i = 0; i < speedInfo.size(); ++i )
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, speedInfo[i]);
    }

    /**
	end frame
     **/
    OpenGLTrainer::showFrameRate();
    glutSwapBuffers();
    glutPostRedisplay();
    }

/**
\brief Set GL view transformation so that the lower left corner of our view window 
'viewWindow' maps to the lower left of the GUI window and the upper right corner
of 'viewWindow' maps to the upper right of the GUI window.
*/
void reshape(int width, int height)
    {
    /* use the entire GUI window area for OpenGL drawing */
    guiWindow.width = width;
    guiWindow.height = height;
    glViewport( 0, 0,guiWindow.width, guiWindow.height);

    /* */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(viewWindow.lowerLeft[0],viewWindow.upperRight[0],viewWindow.lowerLeft[1],viewWindow.upperRight[1]);
    }

/**
\brief 'idle' is the GLUT idle callback function
*/
static
void idle(void)
    {
    }

static 
void keyHandler(int key, int x, int y)
    {
    if(key == GLUT_KEY_UP)
	multFactor *= 1.2f;
    else if(key == GLUT_KEY_DOWN)
	multFactor /= 1.2f;

    glutPostRedisplay();
    }

static
void keyboardHandler(unsigned char key, int x, int y)
    {
    static bool lightsOn = true;

    if(key == 'l')
	{
	if(lightsOn)
	    {
	    glDisable(GL_LIGHTING);
	    lightsOn = false;
	    }
	else
	    {
	    glEnable(GL_LIGHTING);
	    lightsOn = true;
	    }
	}

    glutPostRedisplay();
    }

/**
\brief 'main' is the standard C/C++ main function where execution starts
*/
int main (int argc, char** argv)
    {
    /* Initialize GLUT library */
    glutInit(&argc, argv);

    /* setup default window display mode */
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);

    /* create window */
    glutInitWindowSize(guiWindow.width, guiWindow.height);
    glutCreateWindow(argv[0]);

    /** init ITCS4120::OpenGLTrainer classes */
    OpenGLTrainer::init(&argc,argv);

    /* set glut callbacks */
    glutDisplayFunc (display);
    glutIdleFunc (idle);
    glutMouseFunc (mouse); 
    glutSpecialFunc (keyHandler);
    glutReshapeFunc (reshape);
    glutKeyboardFunc(keyboardHandler);

    /* initialize application */
    init();

    /* start GLUT main loop */
    glutMainLoop();
    return 0;
    }
