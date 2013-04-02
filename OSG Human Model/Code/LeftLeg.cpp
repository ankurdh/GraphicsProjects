#include "LeftLeg.h"


LeftLeg::LeftLeg(ref_ptr<MatrixTransform> transform) : MyBodyPart(transform)
    {
    shape->setShape(new Capsule(Vec3(0.0f, 0.0f, -0.8f), 0.5f, 1.8f));
    rotationAngleX = rotationAngleY = rotationAngleZ = 0.0f;
    rotationVectorX = Vec3(-1.0f, 0.0f, 0.0f);
    rotationVectorY = Vec3(0.0f, 1.0f, 0.0f);
    rotationVectorZ = Vec3(0.0f, 0.0f, -1.0f);
    isShiftKeyPressed = false;
    }

bool LeftLeg::handle(const GUIEventAdapter & ea, GUIActionAdapter & aa)
    {

    Matrix matX, matY, matZ;
    switch ( ea.getEventType() )
	{

    case osgGA::GUIEventAdapter::KEYDOWN:
	switch ( ea.getKey() )
	    {

	case GUIEventAdapter::KEY_Shift_L:case GUIEventAdapter::KEY_Shift_R:
	    isShiftKeyPressed = true;
	    break;

	case GUIEventAdapter::KEY_Left:
	    if(isSelected && !isShiftKeyPressed)
		{
		if(rotationAngleY < DegreesToRadians(45.0)){
		    rotationAngleY += PI/180;
		    matY = Matrix::rotate(PI/180, rotationVectorY);
		    transform->setMatrix(matY*transform->getMatrix());
		    }
		}

	    if(isSelected && isShiftKeyPressed)
		{
		if(rotationAngleZ < DegreesToRadians(10.0f)){
		    rotationAngleZ += PI/180;
		    matZ = Matrix::rotate(PI/180, rotationVectorZ);
		    transform->setMatrix(matZ*transform->getMatrix());
		    }
		}

	    break;

	case GUIEventAdapter::KEY_Right:
	    if(isSelected && !isShiftKeyPressed)
		{
		if(rotationAngleY > DegreesToRadians(0.0f)){
		    rotationAngleY -= PI/180;
		    matY = Matrix::rotate(-PI/180, rotationVectorY);
		    transform->setMatrix(matY*transform->getMatrix());
		    }
		}

	    if(isSelected && isShiftKeyPressed)
		{
		if(rotationAngleZ > DegreesToRadians(0.0f)){
		    rotationAngleZ -= PI/180;
		    matZ = Matrix::rotate(-PI/180, rotationVectorZ);
		    transform->setMatrix(matZ*transform->getMatrix());
		    }
		}
	    break;
	case GUIEventAdapter::KEY_Up:
	    if(isSelected)
		{
		if(rotationAngleX < DegreesToRadians(90.0))
		    {
		    rotationAngleX += PI/180;
		    matX = Matrix::rotate(PI/180, rotationVectorX);
		    transform->setMatrix(matX*transform->getMatrix());
		    }
		}
	    break;

	case GUIEventAdapter::KEY_Down:
	    if(isSelected)
		{
		if(rotationAngleX > DegreesToRadians(0.0f))
		    {
		    rotationAngleX -= PI/180;
		    matX = Matrix::rotate(-PI/180, rotationVectorX);
		    transform->setMatrix(matX*transform->getMatrix());
		    }
		}
	    break;

	case '6':
	    shape->setColor(Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	    isSelected = true;
	    break;
	case '1': case '2': case '3': case '4':
	case '5': case '9': case '7': case '8':
	case '0': 
	    shape->setColor(Vec4(1.0f, 1.0f, 1.0f, 1.0f));
	    isSelected = false;
	    break;

	    }
	break;
    case GUIEventAdapter::KEYUP:
	if(ea.getKey() == GUIEventAdapter::KEY_Shift_L)
	    isShiftKeyPressed = false;
	break;
	}
    return false;
    }

LeftLeg::~LeftLeg(void)
    {
    }
