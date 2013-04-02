#pragma once
#include "mybodypart.h"
class RightLeg :
    public MyBodyPart
    {
    public:
	RightLeg(ref_ptr<MatrixTransform> transform);
	virtual bool handle(const GUIEventAdapter & ea, GUIActionAdapter & aa);
	~RightLeg(void);

    private:
	float rotationAngleX, rotationAngleY, rotationAngleZ;
	Vec3 rotationVectorX, rotationVectorY, rotationVectorZ;
	bool isShiftKeyPressed;
    };

