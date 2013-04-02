#include "Shape.h"
#include "CoordinateSystem.h"

using namespace ITCS4120;

Shape::Shape()
    {
    parent_ = NULL;
    }

Shape::Shape(CoordinateSystem *c)
    { 
    parent_ = c; 
    }