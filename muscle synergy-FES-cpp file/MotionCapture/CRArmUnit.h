#pragma once

#include "Graphics\SurfaceObj.h"
#include "CIHumanUnit.h"
#define ARM_JOINT 4
#define ARM_LINK 4

class CLimbUnit : public CIHumanUnit
{
public:
	CLimbUnit();
	~CLimbUnit();

public:


	virtual void draw();
	virtual void read();
	virtual void calcInv(Vec3f wri2, Vec3f ang_elb);

	void setSide(int _side);
	void setLimb(int partsIdx);




	void updateJointAngle(Vec3f hand, Vec3f low, Vec3f up);
	void updateJointAngle_IK2(Vec3f hand, Vec3f low, Vec3f up);

	void rotateMat(int jointIdx, Mat3x3f rot);
	void calcEnd(Vec3f hand, Vec3f lower, Vec3f upper);

	Vec3f calcCross(Vec3f v1, Vec3f v2);
	float calcNorm(Vec3f v1);
	
	// Mat3x3f calcMat(Vec3f angle, int dir);

	Vec3f getPosition(int jointIdx, int FK);
	Vec3f getTheta4();
	Vec3f getInvAng();

private:
	int side = 1;
	int limb = 0;

	SurfaceObj m_ArmUnit[ARM_LINK];

	Vec3f jointPos_FK[ARM_JOINT];
	Vec3f jointPos_IK[ARM_JOINT];
	Vec3f jointOrg[ARM_JOINT];	
	
	float theta4;
	float theta4_;
	Vec3f invAngle;


};

