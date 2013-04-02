#ifndef Shape_H
#define Shape_H
/**
\file Shape.h
\author Zachary Wartell
\brief This file implements the Shape and related classes

Copyright 2007, All Rights Reserved: Zachary Wartell, University of North Carolina at Charlotte

Dr. Wartell gives students the .h files with the C++ class already designed. Students in his
courses are responsible for implementing the class member functions and adding additional
ones as needed.
*/

/*******************************************************************************
    Includes	
*******************************************************************************/
#include <Math2D/Matrix3x3.h>
#include "CoordinateSystem.h"

/*******************************************************************************
    Macros
*******************************************************************************/
/* NONE */

/*******************************************************************************
    Data Types 
*******************************************************************************/
namespace ITCS4120
{

/**
\author Zachary Wartell
\brief Shape is a object whose state is a 2D geometric shape. Shape sub-classes
added geometric attributes (points,vectors, distances) that describe the shape
instance. All attributes are measured with respect to the Shape's parent CoordinateSystem.
*/
class Shape
    {
    public:   
    Shape ();
    Shape (CoordinateSystem *c);

    /**
    Render this shape.
    */
    virtual void render()=0;      

    /**
    Return whether this Shape contains a target point, P.  P's coordinates measured in 
    world coordinates are 'target_WCS'.
    */
    virtual bool contains (Point2 target_WCS)=0;

    private:
    CoordinateSystem* parent_;
    public:
    // parent read accessor
    const CoordinateSystem* parent() const { return parent_; }

    friend void CoordinateSystem::addShape(Shape& s);
    };
}  

/*******************************************************************************
    C Exported Function Prototypes
*******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/* NONE */
#ifdef __cplusplus
}
#endif

/*******************************************************************************
    Global Variables
*******************************************************************************/
/* NONE */
#endif
