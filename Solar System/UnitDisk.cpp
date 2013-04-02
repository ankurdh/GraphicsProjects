/**
\file UnitDisk.cpp
\author Zachary Wartell

\brief Implements UnitDisk

Copyright 2007, All Rights Reserved: Zachary Wartell, University of North Carolina at Charlotte

TO DO LIST:
\todo 

BUG LIST:
\bug This file probably has a bug. 

FOOTNOTES:
- [F1] This is an example footnote.

REFERENCES:
- [R1] Donald Hearn and M. Pauline Baker.  Computer Graphics with OpenGL: Third Edition.

\internal
*/

/*******************************************************************************
    Includes	
*******************************************************************************/
#ifdef WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include "UnitDisk.h"
#include "CoordinateSystem.h"

/*******************************************************************************
    File Scope Macros 
*******************************************************************************/
/* NONE */
/*******************************************************************************
    File Scope Function Prototypes 
*******************************************************************************/
/* NONE */
/*******************************************************************************
    File Scope Data Types 
*******************************************************************************/
/* NONE */

/*******************************************************************************
    File Scope Global Declarations 
*******************************************************************************/
/* NONE */

/*******************************************************************************
    Library Scope Global Declarations 
*******************************************************************************/
/* NONE */

/*******************************************************************************
    Exported Scope Global Declarations 
*******************************************************************************/
/* NONE */

/*******************************************************************************
    Exported Scope Functions & Class Member Functions 
*******************************************************************************/
/* NONE */
/*******************************************************************************
    Library Scope Functions & Class Member Functions 
*******************************************************************************/
using namespace ITCS4120;

UnitDisk::UnitDisk()
    {
    }

UnitDisk::UnitDisk(int colorIndex, std::string planetName, CoordinateSystem *cs) : Shape(cs)
    {

    this->planetName = planetName;

    switch(colorIndex)
	{
    case 1: 
	color[0] = 1.0f;
	color[1] = 0.5f;
	color[2] = 0.0f;
	break;

    case 2:
	color[0] = 0.2f;
	color[1] = 0.5f;
	color[2] = 0.9f;
	break;

    case 3:
	color[0] = 0.9f;
	color[1] = 0.3f;
	color[2] = 0.7f;
	break;

    case 4:
	color[0] = 0.1f;
	color[1] = 0.1f;
	color[2] = 0.4f;
	break;

    case 5:
	color[0] = 1.0f;
	color[1] = 0.3f;
	color[2] = 1.0f;
	break;

    case 6:
	color[0] = 0.0f;
	color[1] = 0.3f;
	color[2] = 1.0f;
	break;

    case 7:
	color[0] = 1.0f;
	color[1] = 0.1f;
	color[2] = 0.1f;
	break;

    default:
	color[0] = 0.6f;
	color[1] = 0.8f;
	color[2] = 0.6f;

	}
    }

/**
\author Zachary Wartell
\brief Draw a unit disc with respect to current OGL modelview transform.

Note, the unit disc is always a disc centered at 0,0 with a radius of 1
as measured with respect to the parent coordinate system.

To render an ellipse with different x/y sizes, orientation and position,
students must manipulate the parent CoordinateSystem pose attributes.
*/
void UnitDisk::render()
    {
    // \todo replace this rendering of a unit square with code to render a prettier unit disc.
    glBegin( GL_POLYGON );
	
        for( float i = 0; i <= 2 * 3.1426 + 0.2 ; i += 0.1 )
        {
	    glColor3f(color[0]/(color[0] + i + 0.3f), color[1]/(color[1] + 0.1f + i), color[2]/(color[2] + i + 0.1f));
            glVertex2f( sin( i ), cos( i ));
        }
    glEnd();
    }

bool UnitDisk::contains (Point2 target_WCS)
    {
    Point2 target_LCS; // target point in local coordinates

    /* transform target_WCS into the local coordinates of this UnitDisk's 
       parent CoordinateSystem.
    */
    // \todo replace this with code to do the above...
    const CoordinateSystem * parent = Shape::parent();
    if(parent != NULL)
	{
	Matrix3x3 localFromWorld = parent->local_from_world();

	target_LCS = localFromWorld * target_WCS;
	Point2 parentOrigin = parent->origin;
	Point2 parentOriginInLocal = parent->local_from_parent() * parentOrigin;
	/* 
	test whether target_LCS is inside the unit circle 
	*/
	Vector2 v = parentOriginInLocal - target_LCS;
	Scalar length = v.length();
	return ( abs(length) <= 1);
	}
    return false;
    }

/*******************************************************************************
    File Scope Functions & Class Member Functions 
*******************************************************************************/
/* NONE */
