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

