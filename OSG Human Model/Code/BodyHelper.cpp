#include "BodyHelper.h"

ref_ptr<Group> BodyHelper::getBody()
    {

    ref_ptr<MatrixTransform> torsoTransform = new MatrixTransform();
    torso = new Torso(torsoTransform.get());

    ref_ptr<MatrixTransform> headTransform = new MatrixTransform();
    headTransform->setMatrix(Matrix::translate(0.0f, 0.0f, 1.8f));
    head = new Head(headTransform.get());

    ref_ptr<MatrixTransform> rightHandTransform = new MatrixTransform();
    rightHandTransform->setMatrix(Matrix::translate(1.7f, 0.0f, 1.0f));
    rightHand = new RightHand(rightHandTransform.get());

    ref_ptr<MatrixTransform> leftHandTransform = new MatrixTransform();
    leftHandTransform->setMatrix(Matrix::translate(-1.7f, 0.0f, 1.0f));
    leftHand = new LeftHand(leftHandTransform.get());

    ref_ptr<MatrixTransform> rightLegTransform = new MatrixTransform();
    rightLegTransform->setMatrix(Matrix::translate(0.7f, 0.0f, -2.5f));
    rightLeg = new RightLeg(rightLegTransform.get());

    ref_ptr<MatrixTransform> leftLegTransform = new MatrixTransform();
    leftLegTransform->setMatrix(Matrix::translate(-0.7f, 0.0f, -2.5f));
    leftLeg = new LeftLeg(leftLegTransform.get());

    ref_ptr<MatrixTransform> rightHandBelowElbowTransform = new MatrixTransform();
    rightHandBelowElbowTransform->setMatrix(Matrix::translate(0.0f, 0.0f, -2.0f));
    rightHandBelowElbow = new RightHandBelowElbow(rightHandBelowElbowTransform.get());

    ref_ptr<MatrixTransform> leftHandBelowElbowTransform = new MatrixTransform();
    leftHandBelowElbowTransform->setMatrix(Matrix::translate(0.0f, 0.0f, -2.0f));
    leftHandBelowElbow = new LeftHandBelowElbow(leftHandBelowElbowTransform.get());

    ref_ptr<MatrixTransform> leftLegBelowKneeTransform = new MatrixTransform();
    leftLegBelowKneeTransform->setMatrix(Matrix::translate(0.0f, 0.0f, -2.0f));
    leftLegBelowKnee = new LeftLegBelowKnee(leftLegBelowKneeTransform.get());

    ref_ptr<MatrixTransform> rightLegBelowKneeTransform = new MatrixTransform();
    rightLegBelowKneeTransform->setMatrix(Matrix::translate(0.0f, 0.0f, -2.0f));
    rightLegBelowKnee = new RightLegBelowKnee(rightLegBelowKneeTransform.get());

    ref_ptr<MatrixTransform> rightFootTransform = new MatrixTransform();
    rightFootTransform->setMatrix(Matrix::translate(0.0f, 0.0f, -2.3f));
    rightFoot = new Feet(rightFootTransform.get());

    ref_ptr<MatrixTransform> leftFootTransform = new MatrixTransform();
    leftFootTransform->setMatrix(Matrix::translate(0.0f, 0.0f, -2.3f));
    leftFoot = new Feet(leftFootTransform.get());

    rightLeg->addChildBodyPart(rightLegBelowKnee->getTransform());
    leftLeg->addChildBodyPart(leftLegBelowKnee->getTransform());

    rightLegBelowKnee->addChildBodyPart(rightFoot->getTransform());
    leftLegBelowKnee->addChildBodyPart(leftFoot->getTransform());

    rightHand->addChildBodyPart(rightHandBelowElbow->getTransform());
    leftHand->addChildBodyPart(leftHandBelowElbow->getTransform());

    torso->addChildBodyPart(head->getTransform());
    torso->addChildBodyPart(rightHand->getTransform());
    torso->addChildBodyPart(leftHand->getTransform());
    torso->addChildBodyPart(leftLeg->getTransform());
    torso->addChildBodyPart(rightLeg->getTransform());
    
    ref_ptr<Group> body = new Group();
    body->addChild(torso->getTransform());

    return body;
    }
