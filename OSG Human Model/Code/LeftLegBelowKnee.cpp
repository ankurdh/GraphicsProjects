#include "LeftLegBelowKnee.h"


LeftLegBelowKnee::LeftLegBelowKnee(ref_ptr<MatrixTransform> transform) : MyBodyPart(transform)
    {
    shape->setShape(new Capsule(Vec3(0.0f, 0.0f, -1.0f), 0.40f, 2.0f));
    rotationAngle = 0.0f;
    rotationVector = Vec3(1.0f, 0.0f, 0.0f);
    }

bool LeftLegBelowKnee::handle(const GUIEventAdapter & ea, GUIActionAdapter & aa)
    {
    Matrix m;
    switch ( ea.getEventType() )
	{

    case osgGA::GUIEventAdapter::KEYDOWN:
	switch ( ea.getKey() )
	    {
	case GUIEventAdapter::KEY_Up:
	    if(isSelected)
		{
		if(rotationAngle < DegreesToRadians(80.0))
		    {
		    rotationAngle += PI/180;
		    m = Matrix::rotate(PI/180, rotationVector);
		    transform->setMatrix(m*transform->getMatrix());
		    }
		}
	    break;

	case GUIEventAdapter::KEY_Down:
	    if(isSelected)
		{
		if(rotationAngle > DegreesToRadians(0.0f))
		    {
		    rotationAngle -= PI/180;
		    m = Matrix::rotate(-PI/180, rotationVector);
		    transform->setMatrix(m*transform->getMatrix());
		    }
		}
	    break;

	case '8':
	    shape->setColor(Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	    isSelected = true;
	    break;
	case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '9':
	case '0': 
	    shape->setColor(Vec4(1.0f, 1.0f, 1.0f, 1.0f));
	    isSelected = false;
	    break;

	    }
	}
    return false;
    }

LeftLegBelowKnee::~LeftLegBelowKnee(void)
    {
    }
