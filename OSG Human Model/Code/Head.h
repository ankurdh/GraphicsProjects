#pragma once
#include "mybodypart.h"

class Head : public MyBodyPart
    {
    public:
	Head(ref_ptr<MatrixTransform> transform);
	virtual bool handle( const GUIEventAdapter & ea, GUIActionAdapter & aa );
	~Head(void);
    };

