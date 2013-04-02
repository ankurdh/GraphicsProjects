#ifndef CoordinateSystem_H
#define CoordinateSystem_H
/**
\file CoordinateSystem.h
\author Zachary Wartell
\brief This file implements the CoordinateSystem and related classes

Copyright 2007, All Rights Reserved: Zachary Wartell, University of North Carolina at Charlotte

Dr. Wartell gives students the .h files with the C++ class already designed. Students in his
courses are responsible for implementing the class member functions and adding additional
ones as needed.
*/

/*******************************************************************************
    Includes	
*******************************************************************************/
#include <Math2D/Matrix3x3.h>
#include <vector>

/*******************************************************************************
    Macros
*******************************************************************************/
/* NONE */

/*******************************************************************************
    Data Types 
*******************************************************************************/
namespace ITCS4120
{
class Shape; 
/**
\author Zachary Wartell
\brief CoordinateSystem is a object whose state is a 2D recti-linear coordinate system.
The coordinate system is defined by three attributes: an origin, an orientation angle and
a differential scale. The latter two attributes determine the x and y basis vectors.
Collectively, the three attributes are refered to as the 'pose' of the coordinate system.

CoordinateSystem instances are arranged in a tree data structure. The tree structure is
created by parent-child links between CoordinateSystem instances. Each CoordinateSystem may have one 
parent CoordinateSystem and may have multiple child CoordinateSystems. 

Conceptually, all CoordinateSystems exist in a common world coordinate space.
However, a CoordinateSystem's pose attributes are measured relative to its parent CoordinateSystem.
An exception occurs when a CoordinateSystem has no parent; in that case, it's pose attributes are 
measured relative to the world coordinate system.

The fact that a CoordinateSystem's pose is measured relative to its parent implies that moving a 
parent CoordinateSystem also moves all it's children, and more generally all its descendents.

A CoordinateSystem has methods to compute the matrix that maps a coordinate from the
local coordinate system to the parent coordinate system and visa-versa. 

A CoordinateSystem has also methods to compute the matrix that maps a coordinate from the
local coordinate system to the world coordinate system and visa-versa.

Finally, CoordinateSystem's by themselves have no visual appearance. Hence a CoordinateSystem
also has a list of Shape instances. Shape subclasses describes various shape types using 
coordinate descriptions particular to the subclass. Importantly, the coordinate descriptions of a
Shape are always measured with respect to a Shape's parent CoordinateSystem's local coordinates.
*/
class CoordinateSystem 
    {
    public:   
    CoordinateSystem ();

    /****
     Change of Coordinate Member Functions:

     The next set of methods compute a matrix for converting between various coordinate systems.

     For example, the parent_from_local() method, returns the matrix that transforms this
     CoordinateSystem's local coordinates to it's parent CoordinateSystem's coordinates. More
     precisely, the returns matrix is defined as follows:

     M			=	 M                       * M                          * M
      parent<-local		  Translate(this.origin)    Rotate(this.orientation)     Scale(this.scale)

     \todo ITCS4120: Using your knowledge of composing matrices and computing inverses you should
     be able to derive the matrix sequences need to compute the returned results for the remaining
     methods.
     ****/

    /**
    \brief Return the matrix that maps local coordiates to parent coordinates, i.e.:
	    M
	     parent<-local
    */
    Matrix3x3 parent_from_local() const;
    /**
    \brief Return the matrix that maps parent coordiates to local coordinates, i.e.:
	    M
	     local<-parent
    */
    Matrix3x3 local_from_parent() const;

    /**
    \brief Return the matrix that maps local coordiates to world coordinates, i.e.:
	    M
	     world<-local
    */
    Matrix3x3 world_from_local() const;
    /**
    \brief Return the matrix that maps world coordiates to local coordinates, i.e.:
	    M
	     local<-world
    */
    Matrix3x3 local_from_world() const;

    /****
	pose data members 
     ****/	
    public:
    /**
    origin of this CoordinateSystem measured in its parent CoordinateSystem
    */
    Point2 origin;
    /**
    orientation angle of this CoordinateSystem measured in its parent CoordinateSystem
    */
    float orientation;
    /**
    Differential scale factors of this CoordinateSystem measured in its parent CoordinateSystem
    */
    float scale[2];

    /****
	other data members 
     ****/
    private:
    /**
    parent_ is parent CoordinateSystem to which this CoordinateSystem is attached.
    parent_ may be NULL which means this CoordinateSystem is measured relatived to the world coordinate space.
    */
    CoordinateSystem* parent_;

    /**
    children_ are the child CoordinateSystem's which are attached to this CoordinateSystem
    */
    // students may use an STL vector or any other structure as along as it can store multiple children
    std::vector<CoordinateSystem*> children_;

    /**
    shapes_ are the Shape's that are attached to this CoordinateSystem.
    */
    // students may use an STL vector or any other structure as along as it can store multiple shapes
    private:
    std::vector<Shape*> shapes_;

    public:
    /**
    Add Shape 's' to this CoordinateSystem's shapes.	
    */
    void addShape (Shape& s);

    /**
    Add CoordinateSystem 'cs' as an additional child of this CoordinateSystem.
    */
    void addCoordinateSystem(CoordinateSystem& cs);

    /**
    Render all this CoordinateSystem's shapes and all descendent CoordinateSystem's
    and all their attached shapes.
    */
    void render();

    //method to register the parent co-ordinate system.
    void setParent(CoordinateSystem *cs){ parent_ = cs; }

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
