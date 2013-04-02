#ifndef UnitDisk_H
#define UnitDisk_H
/**
\file UnitDisk.h
\author Zachary Wartell
\brief This file implements the UnitDisk and related classes

Copyright 2007, All Rights Reserved: Zachary Wartell, University of North Carolina at Charlotte
*/

/*******************************************************************************
    Includes	
*******************************************************************************/
#include "Shape.h"


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
\brief UnitDisk is a object whose state is a 2D geometric unit disc, a filled circle
with a diameter of 1.  UnitDisk is centered at the origin it's parent coordinate system.
*/
class UnitDisk : public Shape
    {
    public:   
    UnitDisk();
    UnitDisk(int colorIndex, std::string planetName, CoordinateSystem *cs);

    /**
    Render this UnitDisk.
    */
    virtual void render();      

    /**
    Return whether this UnitDisk contains a point whose coordinates as measured in 
    world coordinates are 'target_WCS'.
    */
    virtual bool contains (Point2 target_WCS);

    float * getColor() { return color; }

    std::string getName() { return planetName; }

    private:
	float color[3];
	std::string planetName;
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
