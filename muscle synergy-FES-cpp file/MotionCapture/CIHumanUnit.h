#pragma once
#include "CRArmUnit.h"
#include "CBodyUnit.h"
#include "CHeadUnit.h"

class CIHumanUnit
{
public:
	CIHumanUnit();
	~CIHumanUnit();

	virtual void read();
	virtual void draw();
	virtual void calcInv();
	void updateJointAngle(int partsIdx, Vec3f angle1, Vec3f angle2, Vec3f angle3);
	void updateInvAngle(int partsIdx, Vec3f wriPos, Vec3f elbAngle);
	Vec3f getPosition(int partsIdx, int jointIdx, int FK);
	void calcPosition(int partsIdx, Vec3f hand, Vec3f lower, Vec3f upper);
	Vec3f getInvAngle(int partsIdx, int jointIdx);
	Mat3x3f calcMat(Vec3f angle, int dir);
	Vec3f calcCross(Vec3f v1, Vec3f v2);
	float calcNorm(Vec3f v1);
	float clamp(float f1, float lowLimit, float highLimit);
	Mat3x3f getRollMat(float v1);
	Mat3x3f getPitchMat(float v1);
	Mat3x3f getYawMat(float v1);
	

private:
	CLimbUnit m_Limb[4];
	CBodyUnit m_body;
	CHeadUnit m_head;

};
