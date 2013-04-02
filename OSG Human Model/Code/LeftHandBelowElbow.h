#pragma once
#include "mybodypart.h"
class LeftHandBelowElbow :
    public MyBodyPart
    {
    public:
	LeftHandBelowElbow(ref_ptr<MatrixTransform> transform);
	virtual bool handle( const GUIEventAdapter & ea, GUIActionAdapter & aa );
	~LeftHandBelowElbow(void);

    private:
	float rotationAngle;
	Vec3 rotationVector;
    };

