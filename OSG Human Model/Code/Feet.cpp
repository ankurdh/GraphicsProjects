#include "Feet.h"


Feet::Feet(ref_ptr<MatrixTransform> transform) : MyBodyPart(transform)
    {
    shape->setShape(new Box(Vec3(0.0f, -0.2f, 0.0f), 0.8f, 1.2f, 0.5f));
    }

bool Feet::handle( const GUIEventAdapter & ea, GUIActionAdapter & aa )
    {
    return false;
    }

Feet::~Feet(void)
    {
    }
