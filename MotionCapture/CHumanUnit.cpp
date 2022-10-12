#include "stdafx.h"
#include "CHumanUnit.h"




CHumanUnit::CHumanUnit()
{
	for (int i = 0; i < 4; i++)
	{
		m_Limb[i].setLimb(i);
	}
}


CHumanUnit::~CHumanUnit()
{
}

void CHumanUnit::read()
{
	m_body.read();
	m_head.read();
	for (int i = 0; i < 4; i++)
	{
		m_Limb[i].read();
	}

}

void CHumanUnit::draw()
{
	m_body.draw();
	m_head.draw();
	for (int i = 0; i < 4; i++)
	{
		m_Limb[i].draw();
	}
}

void CHumanUnit::updateJointAngle(int partsIdx, Vec3f angle1, Vec3f angle2, Vec3f angle3)
{
	m_Limb[partsIdx].updateJointAngle(angle1, angle2, angle3);
}

void CHumanUnit::updateInvAngle(int partsIdx, Vec3f wriPos, Vec3f elbAngle)
{
	m_Limb[partsIdx].calcInv(wriPos, elbAngle);
}

Vec3f CHumanUnit::getPosition(int partsIdx, int joint, int FK)
{
	return m_Limb[partsIdx].getPosition(joint, FK);
}

void CHumanUnit::calcPosition(int partsIdx, Vec3f hand, Vec3f lower, Vec3f upper)
{
	m_Limb[partsIdx].calcEnd(hand, lower, upper);
}

Vec3f CHumanUnit::getInvAngle(int partsIdx, int jointIdx)
{
	if (jointIdx == 2)
		return m_Limb[partsIdx].getInvAng();
	else if (jointIdx == 1)
		return m_Limb[partsIdx].getTheta4();
}

