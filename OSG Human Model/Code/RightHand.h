#pragma once
#include "MyBodyPart.h"

class RightHand : public MyBodyPart
    {
    public:
	RightHand(ref_ptr<MatrixTransform> transform);
	virtual bool handle( const GUIEventAdapter & ea, GUIActionAdapter & aa);
	~RightHand(void);

    private:
	float rotationAngleX, rotationAngleY;
	Vec3 rotationAxisX, rotationAxisY;
    };
