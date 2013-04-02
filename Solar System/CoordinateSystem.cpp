/**
\file CoordinateSystem.cpp
\author Zachary Wartell
\brief This file implements the CoordinateSystem and related classes.

Copyright 2007, All Rights Reserved: Zachary Wartell, University of North Carolina at Charlotte.

Dr. Wartell gives students the .h files with the C++ class already designed. Students in his
courses are responsible for implementing the class member functions and adding additional
ones as needed.

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
#include <math.h>
#include <time.h>
#include <assert.h>
#include <iostream>

#include "CoordinateSystem.h"
#include "Shape.h"

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
/**
\author Zachary Wartell 
\brief 'CoordinateSystem' constructs and initializes this CoordinateSystem

FOOTNOTES:
*/
CoordinateSystem::CoordinateSystem()
    {
    parent_ = NULL;
    // \todo initialize pose attributes too...
    origin = Point2(0.0f, 0.0f);
    orientation = 0.0f;
    scale[0] = scale[1] = 1.0f;
    }

/**
\author Zachary Wartell 
\brief Render all this CoordinateSystem's shapes and all descendent CoordinateSystem's
and all their shapes.

FOOTNOTES:
*/
// \todo This method must be implement as recursive tree traversal.
void CoordinateSystem::render()
    {
    // push and post multiply the OpenGL modelview matrix by a transformation that
    // maps this coordinate system's local space into its parent space.
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    GLfloat mVMat[16];
    glGetFloatv (GL_MODELVIEW_MATRIX, mVMat);

    Matrix3x3 currentMVMat(mVMat[0], mVMat[1], mVMat[3],
	mVMat[4], mVMat[5], mVMat[7], 
	mVMat[12], mVMat[13], mVMat[15]);

    Matrix3x3 parentFromLocal = parent_from_local();
    parentFromLocal.assignTranspose();

    currentMVMat.postMultiply(parentFromLocal);

    GLfloat mat[16] = { 
	parentFromLocal[0][0], parentFromLocal[0][1], 0.0f, parentFromLocal[0][2],
	parentFromLocal[1][0], parentFromLocal[1][1], 0.0f, parentFromLocal[1][2],
	0.0f, 0.0f, 1.0f, 0.0f,
	parentFromLocal[2][0], parentFromLocal[2][1], 0.0f, parentFromLocal[2][2],
	};

    glMultMatrixf(mat);

    /*glTranslatef(origin[0], origin[1], 0.0f);
    glRotatef(orientation, 0.0f, 0.0f, 1.0f);
    glScalef(scale[0], scale[1], 1.0f);*/

    // render all this CoordinateSystem's Shapes 
    for(std::vector<Shape *>::iterator i = shapes_.begin(); i != shapes_.end(); i++)
	(*i)->render();

    // recursively render this CoordinateSystem's children...
    for(std::vector<CoordinateSystem *>::iterator i = children_.begin(); i != children_.end(); i++)
	(*i)->render();

    // pop OpenGL matrix
    glPopMatrix();
    }

Matrix3x3 CoordinateSystem::parent_from_local() const
    {
    Matrix3x3 parentFromLocal(Matrix3x3::IDENTITY_MATRIX);
    
    parentFromLocal.postTranslate(origin[0], origin[1]);
    parentFromLocal.postRotate(orientation);
    parentFromLocal.postScale(scale[0], scale[1]);

    return parentFromLocal;
    }

Matrix3x3 CoordinateSystem::local_from_parent() const
    {
    Matrix3x3 localFromParent(Matrix3x3::IDENTITY_MATRIX);

    localFromParent.assignInverse(parent_from_local());

    return localFromParent;
    }

Matrix3x3 CoordinateSystem::local_from_world() const
    {
    Matrix3x3 localFromWorld = world_from_local();
    localFromWorld.assignInverse();
    return localFromWorld;
    }

Matrix3x3 CoordinateSystem::world_from_local() const
    {
    
    Matrix3x3 worldFromLocal(Matrix3x3::IDENTITY_MATRIX);
    if(parent_ != NULL)
	{
	worldFromLocal.postMultiply(parent_->world_from_local()); 
	}
    worldFromLocal.postMultiply(parent_from_local());
    return worldFromLocal;
    }

void CoordinateSystem::addShape(Shape& s)
    {
    shapes_.push_back(&s);
    }	

void CoordinateSystem::addCoordinateSystem(CoordinateSystem& cs)
    {
    children_.push_back(&cs);
    cs.setParent(this);
    }

/*******************************************************************************
    File Scope Functions & Class Member Functions 
*******************************************************************************/
/* NONE */
