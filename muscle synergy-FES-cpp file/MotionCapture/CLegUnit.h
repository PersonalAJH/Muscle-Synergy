#pragma once

#include "Graphics\SurfaceObj.h"
#define ARM_JOINT 3
#define ARM_LINK 3

class CLegUnit
{
public:
	CLegUnit();
	~CLegUnit();

public:
	void setSide(int _side);
	void draw();
	void read();

	void rotateAll(Vec3f hand, Vec3f lower, Vec3f upper);
	void rotateAll2(Vec3f hand, Vec3f lower, Vec3f upper);
	void transPart(Vec3f distance, int idx);
	void rotatePart(int idx, Vec3f angle, int dir);
	void rotatePart2(int idx, Vec3f angle, int dir);

	void rotateMat(int idx, Mat3x3f rot);
	Mat3x3f calMat(Vec3f angle, int dir);

private:
	int side = 1;

	Vec3f midUpper = Vec3f(200, 10, -570);
	Vec3f midLower = Vec3f(170, 70, -1590);
	Vec3f midHand = Vec3f(170, 90, -2540);

	SurfaceObj m_ArmUnit[ARM_LINK];

	Vec3f jointPos[ARM_JOINT];
	Vec3f jointOrg[ARM_JOINT];



};