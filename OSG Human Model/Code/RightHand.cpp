#include "RightHand.h"


RightHand::RightHand(ref_ptr<MatrixTransform> transform) : MyBodyPart(transform)
    {
    shape->setShape(new Capsule(Vec3(0.0f, 0.0f, -0.7f), 0.5f, 1.4f));
    rotationAngleX = rotationAngleY = 0.0f;
    rotationAxisY = Vec3(0.0f, -1.0f, 0.0f);
    rotationAxisX = Vec3(-1.0f, 0.0f, 0.0f);
    }

RightHand::~RightHand(void)
    {
    }

bool RightHand::handle(const GUIEventAdapter & ea, GUIActionAdapter & aa)
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
		if(rotationAngleX < DegreesToRadians(90.0))
		    {
		    rotationAngleX += PI/180;
		    m = Matrix::rotate(PI/180, rotationAxisX);
		    transform->setMatrix(m*transform->getMatrix());
		    }
		}
	    break;

	case GUIEventAdapter::KEY_Down:
	    if(isSelected)
		{
		if(rotationAngleX > DegreesToRadians(0.0f))
		    {
		    rotationAngleX -= PI/180;
		    m = Matrix::rotate(-PI/180, rotationAxisX);
		    transform->setMatrix(m*transform->getMatrix());
		    }
		}
	    break;

	case GUIEventAdapter::KEY_Right:
	    if(isSelected)
		{
		if(rotationAngleY < DegreesToRadians(45.0))
		    {
		    rotationAngleY += PI/180;
		    m = Matrix::rotate(PI/180, rotationAxisY);
		    transform->setMatrix(m*transform->getMatrix());
		    }
		}
	    break;

	case GUIEventAdapter::KEY_Left:
	    if(isSelected)
		{
		if(rotationAngleY > DegreesToRadians(0.0) && rotationAngleX > DegreesToRadians(0.0f))
		    {
		    rotationAngleY -= PI/180;
		    m = Matrix::rotate(-PI/180, rotationAxisY);
		    transform->setMatrix(m*transform->getMatrix());
		    }
		}
	    break;

	case '3':
	    shape->setColor(Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	    isSelected = true;
	    break;
	case '1': case '2': case '9': case '4':
	case '5': case '6': case '7': case '8':
	case '0': 
	    shape->setColor(Vec4(1.0f, 1.0f, 1.0f, 1.0f));
	    isSelected = false;
	    break;

	    }
	}
    return false;
    }
