#pragma once
#include "mybodypart.h"
class RightLegBelowKnee :
    public MyBodyPart
    {
    public:
	RightLegBelowKnee(ref_ptr<MatrixTransform> transform);
	virtual bool handle( const GUIEventAdapter & ea, GUIActionAdapter & aa );
	~RightLegBelowKnee(void);

    private:
	float rotationAngle;
	Vec3 rotationVector;
    };

