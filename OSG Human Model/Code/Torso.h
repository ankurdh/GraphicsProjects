#pragma once
#include "MyBodyPart.h"

class Torso : public MyBodyPart
    {
    public:
	Torso(ref_ptr<MatrixTransform> transform);
	virtual bool handle( const GUIEventAdapter & ea, GUIActionAdapter & aa );
	~Torso(void);
    };

