#pragma once
#include "mybodypart.h"
class Feet :
    public MyBodyPart
    {
    public:
	Feet(ref_ptr<MatrixTransform> transform);
        virtual bool handle( const GUIEventAdapter & ea, GUIActionAdapter & aa );
	~Feet(void);
    };

