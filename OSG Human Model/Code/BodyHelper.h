#include "MyBodyPart.h"
#include "Torso.h"
#include "Head.h"
#include "RightHand.h"
#include "LeftHand.h"
#include "LeftLeg.h"
#include "RightLeg.h"
#include "LeftHandBelowElbow.h"
#include "RightHandBelowElbow.h"
#include "LeftLegBelowKnee.h"
#include "RightLegBelowKnee.h"
#include "Feet.h"

class BodyHelper {
public:
    ref_ptr<Group> getBody();

    ref_ptr<Torso> getTorso()
	{
	return torso;
	}
    ref_ptr<Head> getHead()
	{
	return head;
	}

    ref_ptr<LeftHand> getLeftHand()
	{
	return leftHand;
	}

    ref_ptr<RightHand> getRightHand()
	{
	return rightHand;
	}

    ref_ptr<LeftHandBelowElbow> getLeftHandBelowElbow()
	{
	return leftHandBelowElbow;
	}

    ref_ptr<RightHandBelowElbow> getRightHandBelowElbow()
	{
	return rightHandBelowElbow;
	}

    ref_ptr<LeftLeg> getLeftLeg()
	{
	return leftLeg;
	}

    ref_ptr<RightLeg> getRightLeg()
	{
	return rightLeg;
	}

    ref_ptr<LeftLegBelowKnee> getLeftLegBelowKnee()
	{
	return leftLegBelowKnee;
	}

    ref_ptr<RightLegBelowKnee> getRightLegBelowKnee()
	{
	return rightLegBelowKnee;
	}

private:
    ref_ptr<Torso> torso;
    ref_ptr<Head> head;
    ref_ptr<RightHand> rightHand;
    ref_ptr<LeftHand> leftHand;
    ref_ptr<RightLeg> rightLeg;
    ref_ptr<LeftLeg> leftLeg;
    ref_ptr<LeftHandBelowElbow> leftHandBelowElbow;
    ref_ptr<RightHandBelowElbow> rightHandBelowElbow;
    ref_ptr<LeftLegBelowKnee> leftLegBelowKnee;
    ref_ptr<RightLegBelowKnee> rightLegBelowKnee;
    ref_ptr<Feet> rightFoot;
    ref_ptr<Feet> leftFoot;
    };