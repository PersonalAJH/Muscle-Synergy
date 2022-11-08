#pragma once

#include "Graphics\SurfaceObj.h"
#include "CIHumanUnit.h"
#define LEG_JOINT 3
#define LEG_LINK 3

class CLegUnit : public CIHumanUnit
{
public:
	CLegUnit();
	~CLegUnit();

public:
	void setSide(int _side);
	virtual void draw();
	virtual void read();
	virtual void calcInv(Vec3f wri2, Vec3f ang_elb);

	void rotateAll(Vec3f hand, Vec3f lower, Vec3f upper);
	void rotateAll2(Vec3f hand, Vec3f lower, Vec3f upper);
	void transPart(Vec3f distance, int idx);
	void rotatePart(int idx, Vec3f angle, int dir);
	void rotatePart2(int idx, Vec3f angle, int dir);

	void rotateMat(int idx, Mat3x3f rot);
	Mat3x3f calMat(Vec3f angle, int dir);

private:
	int side = 1;


	SurfaceObj m_LegUnit[LEG_LINK];
	Vec3f jointPos[LEG_JOINT];
	Vec3f jointOrg[LEG_JOINT];
};