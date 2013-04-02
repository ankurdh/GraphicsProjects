/**
Copyright 2007, All Rights Reserved: Zachary Wartell, University of North Carolina at Charlotte
\file Main.cpp
\author Zachary Wartell
\brief Main.cpp illustrates how to use the PanZoomWindow class.  The pan and zoom user interface is
documented in \ref PanZoomWindow_USER_INTERFACE and quoted below:

    "Left-click + CTRL : mouse movements pans the contents of the pan-zoom window.
     Left-click + CTRL + SHIFT: vertical mouse movement zooms in and out.
     mouse wheel : zooms in and out
     (mouse wheel support available only with compatible GLUT libraries)"

Additionally, Left-click and drag moves a dot around on the screen.

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
#include <iostream>

#if 0
#include <GL/gl.h>
#else
// replacement for GL/gl.h incase an advanced student wants to use OGL extensions, OGL 2.1, etc.
#include <GL/glew.h>   
#endif

#include <GL/glut.h>

#include <OpenGLTrainer/OpenGLTrainer.h>
#include <OpenGLTrainer/PanZoomWindow.h>
#include <OpenGLTrainer/Framebuffer.h>

//#include<vld.h>

#include "SpaceBarHelper.h"

using namespace std;

/*******************************************************************************
    File Scope (static) Globals
*******************************************************************************/
/** lowerLeft and upperRight corner of axis aligned rectangle in world coordinates
    where we will draw all our stuff */
static const float PLAY_FIELD[2][2] = {{0,0},{1e6,1e6}};

//Declare the Grid variable.
int WIDTH = PLAY_FIELD[1][0]-PLAY_FIELD[0][0];
int HEIGHT = PLAY_FIELD[1][1]-PLAY_FIELD[0][1];

Grid grid(HEIGHT, WIDTH);
SpaceBarHelper spaceBarHelper(grid);
/*******************************************************************************
    File Scope (static) Functions
*******************************************************************************/
using namespace ITCS4120::OpenGLTrainer;

class MyPanZoomWindow : public PanZoomWindow
    {
    public:
    MyPanZoomWindow (const float viewLowerLeft[2], const float viewUpperRight[2]);
    
    /** Overridden callback member functions.

	Each of these is automatically called whenever the similarly name GLUT callback function
	is called for the GLUT window created by this PanZoomWindow.
     */
    virtual void display(void);
    virtual void motion (int x, int y);
    virtual void passiveMotion (int x, int y);
    virtual void keyboard (unsigned char key, int x, int y);
    virtual void mouse (int button, int state, int x, int y);

    /** non-virtual functions */
    void resetOpenGL(void);
    bool firstDisplay;
    
    /** All the following functions and data members must be replaced by the student!

    They implement simple drawing and interaction above and beyond the standard
    functionality of PanZoomWindow.  They are provided just to illustrate proper usage of 
    a PanZoomWindow derived class.
    */
    inline void ZJW_mouse (int button, int state, int x, int y);
    inline void ZJW_passiveMotion (int x, int y);    
    inline void ZJW_motion(int gx, int gy);
    inline void ZJW_draw_frame();
    bool ZJW_drag;
    struct Point
	{
	int x;
	int y;
	} ZJW_point;    
    } panZoomWindow (PLAY_FIELD[0],PLAY_FIELD[1]);

/*******************************************************************************
    File Scope (static) Functions
*******************************************************************************/
using namespace ITCS4120::OpenGLTrainer;

/**
\brief Construct a PanZoomWindow whose view window is initially bounded by 'viewLowerLeft' and
'viewUpperRight'.
*/
MyPanZoomWindow::MyPanZoomWindow (const float viewLowerLeft[2], const float viewUpperRight[2]) : 
	PanZoomWindow (viewLowerLeft,viewUpperRight)
    {
    firstDisplay = true;
    }

/**
\brief initialize some default OGL settings
*/
void MyPanZoomWindow::resetOpenGL (void)
    {
    //set clear color to black
    glClearColor(0.0f,0.0f,0.0f,1.0f);    
    }

/**
\brief 'motion' handle mouse motions.
*/
void MyPanZoomWindow::motion
	(
	int gx,  // 'glutX' - mouse X in GLUT coordinates
	int gy   // 'glutY' - mouse Y in GLUT coordinates
	)
    {
    /* perform standard PanZoomWindow motion event processing */
    PanZoomWindow::motion(gx,gy);

    /* do something with mouse motion */
    ZJW_motion(gx,gy);
    }

/**
\brief 'mouse' handles mouse button presses.
*/
void MyPanZoomWindow::mouse(int button, int state, int x, int y)
    {
    /* perform standard PanZoomWindow mouse event processing */
    PanZoomWindow::mouse(button,state,x,y);

    /* perform additional mouse event processing */    
    ZJW_mouse(button, state, x, y);
    }

/**
\brief 'passiveMotion' handles passiveMotion.
*/
void MyPanZoomWindow::passiveMotion(int x, int y)
    {
    /* perform standard PanZoomWindow passiveMotion event processing */
    PanZoomWindow::passiveMotion(x,y);

    /* perform additional passiveMotion event processing */
    // \todo do stuff...
    }

/**
\brief 'keyboard' handles keypresses.
*/
void MyPanZoomWindow::keyboard (unsigned char key, int x, int y)
    {

    /* perform additional keyboard event processing */
    switch (key)
	{
    case 27:     
	glDeleteLists(1, 2);
	break;

    case ' ':
	grid.registerSpaceBar();
	spaceBarHelper.triggerDLRefresh();
	glutPostRedisplay();
	break;
	}

    /* perform standard PanZoomWindow keyboard event processing */
    PanZoomWindow::keyboard(key,x,y);
    }

/**
\brief 'display' is called whenever the GLUT display callback function for this object's
GLUT window is called.
*/
void MyPanZoomWindow::display(void)
    {      
    /**
	perform any 'one time' setup OGL calls.

	Note, OGL calls are only legal during execution of a GLUT display callback.  Below 
	is a standard method to make any OpenGL calls that we wish to make only the first
	time the GLUT display callback is executed.
     **/    
    if (firstDisplay)
	{
	resetOpenGL();
	firstDisplay = false;
	}

    /**
	setup frame
     **/   
    // clear screen
    glClear(GL_COLOR_BUFFER_BIT);
    setOpenGLView();

    /**
	draw frame
     **/
    ZJW_draw_frame();
    
 
    /**
	end frame
     **/    
    ITCS4120::OpenGLTrainer::showFrameRate();
    assert(glGetError()==GL_NO_ERROR);
    glutSwapBuffers();
    }

void shadeCell(int x, int y)
    {
    glBegin(GL_POLYGON);
    glVertex2d(x + 10, y+ 10);
    glVertex2d(x + 10, y+ 1000 - 10);
    glVertex2d(x + 1000 - 10, y+ 1000 - 10);
    glVertex2d(x + 1000 - 10, y + 10);
    glEnd();
    }


// \brief draw some random stuff
void MyPanZoomWindow::ZJW_draw_frame()
    {
    const int WIDTH = PLAY_FIELD[1][0]-PLAY_FIELD[0][0];
    const int HEIGHT = PLAY_FIELD[1][1]-PLAY_FIELD[0][1];
    const int CENTER_X = WIDTH/2;
    const int CENTER_Y = HEIGHT/2;

    /* draw play field */
    //have the background in a light color. So that the green discs can be easily distinguished
    glColor3ub(50,50,50);
    glBegin(GL_QUADS);
	glVertex2fv(PLAY_FIELD[0]);
	glVertex2f (PLAY_FIELD[1][0],PLAY_FIELD[0][0]);
	glVertex2fv(PLAY_FIELD[1]);
	glVertex2f (PLAY_FIELD[0][0],PLAY_FIELD[1][0]);
    glEnd();

#ifdef GRID_DL_ID
    glCallList(GRID_DL_ID);
#endif
#ifdef DISC_DL_ID
    glCallList(DISC_DL_ID);
#endif

    if(grid.getFirstRightClickCell().x != -1 && grid.getFirstRightClickCell().y != -1)
	{
	MyPoint p = grid.getFirstRightClickCell();

	glColor3d(1, 0, 1);
	shadeCell(p.x, p.y);

	}
	if(grid.getSecondRightClickCell().x != -1 && grid.getSecondRightClickCell().y != -1)
	    {
	    MyPoint p = grid.getSecondRightClickCell();

	    glColor3d(1, 0, 1);
	    shadeCell(p.x, p.y);
	    }

	if(grid.getLineIntersectedCellCount() > 0)
	    {
	    //draw in red.
	    glColor3f(0.5f, 0.10f, 0.10f);
	    MyPoint * intersectedCells = grid.getIntersectedGridCells();

	    for(int i = 0 ; i < grid.getLineIntersectedCellCount() ; i++)
		{
		shadeCell((*intersectedCells).x, (*intersectedCells).y);
		intersectedCells++;
		}
	    }

	if(grid.getOtherLineIntersectedCellCount() > 0)
	    {
	    //draw in blue
	    glColor3f(0.10f, 0.10f, 0.5f);
	    MyPoint * intersectedCells = grid.getOtherLineIntersectedGridCells();

	    for(int i = 0 ; i < grid.getOtherLineIntersectedCellCount() ; i++)
		{
		shadeCell((*intersectedCells).x, (*intersectedCells).y);
		intersectedCells++;
		}
	    }

	//draw the parallelogram
	if(grid.rightClickedTwice())
	    {
	    //draw the parallelogram
	    glColor3d(1, 1, 0);
	    MyPoint * parallelogramVertices = grid.getParallelogramVertices();
	    glBegin(GL_LINE_LOOP);
	    glVertex2d(parallelogramVertices[0].x, parallelogramVertices[0].y);
	    glVertex2d(parallelogramVertices[1].x, parallelogramVertices[1].y);
	    glVertex2d(parallelogramVertices[2].x, parallelogramVertices[2].y);
	    glVertex2d(parallelogramVertices[3].x, parallelogramVertices[3].y);
	    glEnd();
	    }

	/* draw dot */
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	glColor3ub(255,0,255);
	glVertex2i(ZJW_point.x,ZJW_point.y);
	glEnd();

	//check if a disc has to be highlighted, if yes, highlight it.
	if(grid.highlightCells())
	    {
	    //draw in green.
	    glColor3f(0.0f, 1.0f, 0.0f);
	    MyPoint * discsToHighlight = grid.getCellsToHighlight();

	    for(int i = 0 ; i < grid.getHighlightingDiscsCount(); i++)
		{
		if(discsToHighlight[i].x != -1 && discsToHighlight[i].y != 0)
		    {
		    glPushMatrix();
		    glTranslatef(discsToHighlight[i].x, discsToHighlight[i].y, 0);
		    glBegin(GL_POLYGON);
		    for( int n = 0; n <= 300; ++n ) {
			float const t = 2*3.142*(float)n/100.0;
			glVertex2f(cos(t)*Disk::radius, sin(t)*Disk::radius);
			}
		    glEnd();
		    glPopMatrix();
		    }
		}
	    }
    }

    /**
    \brief Drag the dot around.
    */
    void MyPanZoomWindow::ZJW_mouse(int button, int state, int x, int y)
	{

	switch (button)
	    {
	case GLUT_LEFT_BUTTON:
	    if (glutGetModifiers()==0)
		ZJW_drag = state == GLUT_DOWN;
	    else
		ZJW_drag = false;
	    break;

	case GLUT_RIGHT_BUTTON:
	    if(state == GLUT_DOWN)
		{
		int mouse[2] = {x, y};
		float mouseW[2];
		mouseCoordinatesToWorldCoordinatesPoint(mouse, mouseW);
		cout<<"X: "<<mouseW[0]<<" Y: "<<mouseW[1]<<endl;

		grid.registerRightClick(mouseW[0], mouseW[1]);
		}

	    break;
	    }

	}

/**
\brief Drag the dot around.
*/
void MyPanZoomWindow::ZJW_motion(int gx, int gy)
    {
    int mouse[2]={gx,gy};
    float mouseW[2];
    mouseCoordinatesToWorldCoordinatesPoint(mouse,mouseW);
   #if 0
    cout << "mouseW: " << mouseW[0] << " " << mouseW[1] << endl;
    cout << "Mouse: " << gx << " " << gy << endl;
   #endif

    if (ZJW_drag)
	{
	ZJW_point.x = mouseW[0];
	ZJW_point.y = mouseW[1];
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

    /* create window */    
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    ::panZoomWindow.glutCreateWindow("PanZoom Window");

    /** init ITCS4120::OpenGLTrainer classes */
    ITCS4120::OpenGLTrainer::Framebuffer::init();        

	DisplayListHelper dlHelper(HEIGHT, WIDTH, grid);
	spaceBarHelper.setDLHelper(&dlHelper);

	/* start GLUT main loop */
	glutMainLoop();
	return 0;
	}
