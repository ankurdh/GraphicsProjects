#include "Head.h"


Head::Head(ref_ptr<MatrixTransform> transform) : MyBodyPart(transform)
    {
    shape->setShape(new Capsule(Vec3(0.0f, 0.0f, 0.4f), 0.60f, 0.50f));
    }


Head::~Head(void)
    {

    }

bool Head::handle( const GUIEventAdapter & ea, GUIActionAdapter & aa )
    {

    switch ( ea.getEventType() )
	{
	
    case osgGA::GUIEventAdapter::KEYDOWN:
	switch ( ea.getKey() )
	    {
	case '1':
	    shape->setColor(Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	    break;
	case '0': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8':
	case '9': 
	    shape->setColor(Vec4(1.0f, 1.0f, 1.0f, 1.0f));
	    break;

	    }
	}

    return false;
    }