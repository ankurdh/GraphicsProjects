#pragma once
#include "mybodypart.h"
class RightHandBelowElbow :
    public MyBodyPart
    {
    public:
	RightHandBelowElbow(ref_ptr<MatrixTransform> transform);
	virtual bool handle( const GUIEventAdapter & ea, GUIActionAdapter & aa );
	~RightHandBelowElbow(void);

    private:
	float rotationAngle;
	Vec3 rotationVector;
    };

