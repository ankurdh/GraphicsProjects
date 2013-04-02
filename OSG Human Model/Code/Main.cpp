#include "MyBodyPart.h"
#include "BodyHelper.h"

#include<iostream>

using namespace osg;
using namespace osgDB;
using namespace osgUtil;
using namespace osgViewer;
using namespace osgGA;

void registerEventHandlers(Viewer &v, BodyHelper &bodyHelper)
    {
    
    v.addEventHandler(bodyHelper.getTorso());
    v.addEventHandler(bodyHelper.getHead());
    v.addEventHandler(bodyHelper.getLeftHand());
    v.addEventHandler(bodyHelper.getLeftHandBelowElbow());
    v.addEventHandler(bodyHelper.getRightHand());
    v.addEventHandler(bodyHelper.getRightHandBelowElbow());
    v.addEventHandler(bodyHelper.getRightLeg());
    v.addEventHandler(bodyHelper.getRightLegBelowKnee());
    v.addEventHandler(bodyHelper.getLeftLeg());
    v.addEventHandler(bodyHelper.getLeftLegBelowKnee());

    }

int main()
    {
    BodyHelper bodyHelper;
    ref_ptr<Group> body = bodyHelper.getBody();

    Viewer v;

    registerEventHandlers(v, bodyHelper);
    v.setSceneData(body);
    
    return v.run();

    }
