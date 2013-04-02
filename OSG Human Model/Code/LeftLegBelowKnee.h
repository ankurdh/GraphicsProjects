#pragma once
#include "mybodypart.h"
class LeftLegBelowKnee :
    public MyBodyPart
    {
    public:
	LeftLegBelowKnee(ref_ptr<MatrixTransform> transform);
	virtual bool handle( const GUIEventAdapter & ea, GUIActionAdapter & aa );
	~LeftLegBelowKnee(void);

    private:
	float rotationAngle;
	Vec3 rotationVector;
    };

