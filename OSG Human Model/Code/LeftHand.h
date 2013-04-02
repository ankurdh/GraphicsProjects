#pragma once
#include "mybodypart.h"

class LeftHand : public MyBodyPart
    {
    public:
	LeftHand(ref_ptr<MatrixTransform> transform);
	virtual bool handle(const GUIEventAdapter & ea, GUIActionAdapter & aa);
	~LeftHand(void);

    private:
	float rotationAngleX, rotationAngleY;
	Vec3 rotationAxisX, rotationAxisY;
    };

