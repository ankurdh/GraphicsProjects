#pragma once
#include "mybodypart.h"
class LeftLeg :
    public MyBodyPart
    {
    public:
	LeftLeg(ref_ptr<MatrixTransform> transform);
	virtual bool handle(const GUIEventAdapter & ea, GUIActionAdapter & aa);
	~LeftLeg(void);

    private:
	float rotationAngleX, rotationAngleY, rotationAngleZ;
	Vec3 rotationVectorX, rotationVectorY, rotationVectorZ;
	bool isShiftKeyPressed;
    };

