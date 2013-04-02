#include "Torso.h"


Torso::Torso(ref_ptr<MatrixTransform> transform) : MyBodyPart(transform)
    {
    shape->setShape(new Capsule(Vec3(0.0f, 0.0f, 0.0f), 1.0f, 2.0f));
    }

Torso::~Torso(void)
    {
    }

bool Torso::handle( const GUIEventAdapter & ea, GUIActionAdapter & aa )
    {
    Matrix m;
    switch ( ea.getEventType() )
	{
	
    case osgGA::GUIEventAdapter::KEYDOWN:
	switch ( ea.getKey() )
	    {
	    
	case 'a':
	    m = Matrix::translate(-0.1f, 0.0f, 0.0f);
	    transform->setMatrix(m*transform->getMatrix());
	    break;
	case 'd':
	     m = Matrix::translate(0.1f, 0.0f, 0.0f);
	    transform->setMatrix(m*transform->getMatrix());
	    break;
	case 'w':
	     m = Matrix::translate(0.0f, 0.1f, 0.0f);
	    transform->setMatrix(m*transform->getMatrix());
	    break;
	case 's':
	     m = Matrix::translate(0.0f, -0.10f, 0.f);
	    transform->setMatrix(m*transform->getMatrix());
	    break;
	case '0':
	    shape->setColor(Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	    break;
	case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8':
	case '9': 
	    shape->setColor(Vec4(1.0f, 1.0f, 1.0f, 1.0f));
	    break;
	    }
	}
    return false;
    }