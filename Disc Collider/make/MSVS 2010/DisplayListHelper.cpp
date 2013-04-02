#include "DisplyaListHelper.h"

#pragma region CREATE DISPLAY LISTS REGION

DisplayListHelper::DisplayListHelper(const int height, const int width, Grid & grid) : g(grid)
    {
    HEIGHT = height;
    WIDTH = width;
    
    cout<<"Creating Vertical Line Display List"<<endl;
    createVerticalLineDL();
    cout<<"Creating Horizontal Line Display List"<<endl;
    createHorizontalLineDL();
    cout<<"Creating the individial discs display list"<<endl;
    createIndividialDiscDL();
    cout<<"Creating the discs display list"<<endl;
    createDiscDL();
    cout<<"Creating the grid display list"<<endl;
    createGridDL();

    }

void DisplayListHelper::createIndividialDiscDL()
    {
    int segments = 100;
    double M_PI = 3.14;
    int r = Disk::radius;

    glNewList(INDIVIDUAL_DISC_DL_ID, GL_COMPILE);

    glBegin(GL_LINE_LOOP);
    for( int n = 0; n <= segments; ++n ) {
	float const t = 2*M_PI*(float)n/(float)segments;
	glVertex2f(cos(t)*r, sin(t)*r);
	}
    glEnd();

    glEndList();
    }

void DisplayListHelper::createDiscDL()
    {
    glNewList(DISC_DL_ID, GL_COMPILE);

    Disk * d = g.getDisks();
    glColor3ub(0,255,0);
    for(int i = 0 ; i < NO_OF_DISCS ; i ++)
	{
	if(d[i].getCenterX() != -1 && d[i].getCenterY() != -1)
	    {
	    glPushMatrix();
	    glTranslatef(d[i].getCenterX(), d[i].getCenterY(), 0);
	    glCallList(INDIVIDUAL_DISC_DL_ID);
	    glPopMatrix();
	    }
	}

    glEndList();
    }

void DisplayListHelper::createHorizontalLineDL()
    {
    glNewList(HORIZONTAL_GRID_LINE_DL_ID, GL_COMPILE);

    glBegin(GL_LINES);

    glVertex2d(0, 1000);
    glVertex2d(WIDTH, 1000);

    glEnd();

    glEndList();
    }

void DisplayListHelper::createVerticalLineDL()
    {
    glNewList(VERTICAL_GRID_LINE_DL_ID, GL_COMPILE);

    glBegin(GL_LINES);

    glVertex2d(1000, 0);
    glVertex2d(1000, HEIGHT);

    glEnd();

    glEndList();
    }

void DisplayListHelper::createGridDL()
    {
    glNewList(GRID_DL_ID, GL_COMPILE);

    //Draw lines in black
    glColor3f(0.20f, 0.3f, 0.70f);
    //draw all the vertical lines first
    for(long int i = 0, incr = 0 ; i < 1000 ; i ++, incr += 1000)
	{
	glPushMatrix();
	glTranslatef(incr, 0,0);
	glCallList(VERTICAL_GRID_LINE_DL_ID);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, incr, 0);
	glCallList(HORIZONTAL_GRID_LINE_DL_ID);
	glPopMatrix();
	}

    glEndList();

    }

void DisplayListHelper::refreshDiscDL()
    {
    glDeleteLists(DISC_DL_ID,1);
    createDiscDL();
    }

#pragma endregion 