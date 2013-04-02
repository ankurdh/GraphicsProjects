#pragma once

#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osg/fog>
#include <osgUtil/SmoothingVisitor>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/PositionAttitudeTransform>
#include <osgGA/TrackballManipulator>
#include <osg/MatrixTransform>
#include <osgGA/GUIEventHandler>

using namespace osg;
using namespace osgDB;
using namespace osgUtil;
using namespace osgViewer;
using namespace osgGA;

class MyBodyPart : public GUIEventHandler
    {

    public:
	MyBodyPart(ref_ptr<MatrixTransform> transform) : transform(transform), isSelected(false)
	    {
	    ref_ptr<ShapeDrawable> shape = new ShapeDrawable();
	    shape->setShape(new Capsule(Vec3(0.0f, 0.0f, 0.0f), 0.60f, 1.3f));
	    shape->setColor(Vec4(1.0f, 1.0f, 1.0f, 1.0f));

	    this->shape = shape;
	    
	    bodyPartGeode = new Geode();
	    bodyPartGeode->addDrawable(shape);

	    transform->addChild(bodyPartGeode);
	    
	    }
	virtual bool handle( const GUIEventAdapter & ea, GUIActionAdapter & aa) = 0;

	virtual void setColor(Vec4 color)
	    {
	    shape->setColor(color);
	    }

	virtual void addDrawable(ref_ptr<ShapeDrawable> drawable) 
	    {
	    
	    }

	virtual void createGeode()
	    {
	    }

	virtual ref_ptr<Geode> getGeode()
	    {
	    return bodyPartGeode;
	    }

	virtual void addChildBodyPart(ref_ptr<MatrixTransform> partTransform)
	    {
	    transform->addChild(partTransform.get());
	    }

	virtual ref_ptr<MatrixTransform> getTransform()
	    {
	    return transform;
	    }

	virtual void setGeodeToTransform()
	    {
	    }

    protected:
	ref_ptr<ShapeDrawable> shape;
	ref_ptr<MatrixTransform> transform;
	ref_ptr<Geode> bodyPartGeode;
	bool isSelected;

    };