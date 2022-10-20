#include "stdafx.h"
#include "CIHumanUnit.h"




CIHumanUnit::CIHumanUnit()
{
	for (int i = 0; i < 4; i++)
	{
		m_Limb[i].setLimb(i);
	}
}


CIHumanUnit::~CIHumanUnit()
{
}



Mat3x3f CIHumanUnit::calcMat(Vec3f angle, int dir) {
	float a = angle[2] * PI / 180;
	float b = angle[1] * PI / 180;
	float c = angle[0] * PI / 180;
	Vec3f r1;
	Vec3f r2;
	Vec3f r3;
	if (dir == 1) { // ZYX Euler
		r1 = Vec3f(cos(a)*cos(b), cos(a)*sin(b)*sin(c) - sin(a)*cos(c), cos(a)*sin(b)*cos(c) + sin(a)*sin(c));
		r2 = Vec3f(sin(a)*cos(b), sin(a)*sin(b)*sin(c) + cos(a)*cos(c), sin(a)*sin(b)*cos(c) - cos(a)*sin(c));
		r3 = Vec3f(-sin(b), cos(b)*sin(c), cos(b)*cos(c));
	}
	else {			// XYZ Euler
		r1 = Vec3f(cos(a)*cos(b), -sin(a)*cos(b), sin(b));
		r2 = Vec3f( cos(a)*sin(b)*sin(c) + sin(a)*cos(c), -sin(a)*sin(b)*sin(c) + cos(a)*cos(c), -cos(b)*sin(c));
		r3 = Vec3f(-cos(a)*sin(b)*cos(c) + sin(a)*sin(c),  sin(a)*sin(b)*cos(c) + cos(a)*sin(c),  cos(b)*cos(c));
	}

	return Mat3x3f(r1, r2, r3);
}

Vec3f CIHumanUnit::calcCross(Vec3f v1, Vec3f v2)
{
	Vec3f v3 = Vec3f(v1[1] * v2[2] - v1[2] * v2[1], 
					 v1[2] * v2[0] - v1[0] * v2[2], 
					 v1[0] * v2[1] - v1[1] * v2[0]);
	return v3;
}

float CIHumanUnit::calcNorm(Vec3f v1)
{	
	return sqrt(v1[0] * v1[0] + v1[1] * v1[1] + v1[2] * v1[2]);
}


float CIHumanUnit::clamp(float f1, float lowLimit, float highLimit)
{
	float result;
	if (lowLimit > highLimit) {
		float tmp = highLimit;
		highLimit = lowLimit;
		lowLimit = tmp;
	}

	if (result < lowLimit) {
		result = lowLimit;
	}

	if (result > highLimit) {
		result = highLimit;
	}

	return result;
}


Mat3x3f CIHumanUnit::getRollMat(float v1)
{
	Mat3x3f result;
	float v1_sin, v1_cos;
	v1_sin = sin(v1);
	v1_cos = cos(v1);
	Vec3f r1,r2,r3;
	
	r1 = Vec3f(v1_cos, -v1_sin,0.0f);
	r2 = Vec3f(v1_sin, v1_cos, 0.0f);
	r3 = Vec3f(0.0f, 0.0f,1.0f);
	
	result = Mat3x3f(r1,r2,r3);
	return result;
}

Mat3x3f CIHumanUnit::getPitchMat(float v1)
{
	Mat3x3f result;
	float v1_sin, v1_cos;
	v1_sin = sin(v1);
	v1_cos = cos(v1);
	Vec3f r1,r2,r3;
	r1 = Vec3f(v1_cos, 0.0f, v1_sin);
	r2 = Vec3f(0.0f, 1.0f, 0.0f);
	r3 = Vec3f(-v1_sin, 0.0f, v1_cos);
	
	result = Mat3x3f(r1,r2,r3);
	return result;
}

Mat3x3f CIHumanUnit::getYawMat(float v1)
{
	Mat3x3f result;
	float v1_sin, v1_cos;
	v1_sin = sin(v1);
	v1_cos = cos(v1);
	Vec3f r1,r2,r3;
	r1 = Vec3f(1.0f, 0.0f,0.0f);
	r2 = Vec3f(0.0f, v1_cos, -v1_sin);
	r3 = Vec3f(0.0f, v1_sin, v1_cos);
	
	result = Mat3x3f(r1,r2,r3);
	return result;
}



void CIHumanUnit::updateJointAngle(int partsIdx, Vec3f angle1, Vec3f angle2, Vec3f angle3)
{
	m_Limb[partsIdx].updateJointAngle(angle1, angle2, angle3);
}

void CIHumanUnit::updateInvAngle(int partsIdx, Vec3f wriPos, Vec3f elbAngle)
{
	m_Limb[partsIdx].calcInv(wriPos, elbAngle);
}

Vec3f CIHumanUnit::getPosition(int partsIdx, int joint, int FK)
{
	return m_Limb[partsIdx].getPosition(joint, FK);
}

void CIHumanUnit::calcPosition(int partsIdx, Vec3f hand, Vec3f lower, Vec3f upper)
{
	m_Limb[partsIdx].calcEnd(hand, lower, upper);
}

Vec3f CIHumanUnit::getInvAngle(int partsIdx, int jointIdx)
{
	if (jointIdx == 2)
		return m_Limb[partsIdx].getInvAng();
	else if (jointIdx == 1)
		return m_Limb[partsIdx].getTheta4();
}

