#pragma once
#include "CArmUnit.h"
#include "CBodyUnit.h"
#include "CHeadUnit.h"

class CHumanUnit
{
public:
	CHumanUnit();
	~CHumanUnit();

	void read();
	void draw();
	void updateJointAngle(int partsIdx, Vec3f angle1, Vec3f angle2, Vec3f angle3);
	void updateInvAngle(int partsIdx, Vec3f wriPos, Vec3f elbAngle);
	Vec3f getPosition(int partsIdx, int jointIdx, int FK);
	void calcPosition(int partsIdx, Vec3f hand, Vec3f lower, Vec3f upper);
	Vec3f getInvAngle(int partsIdx, int jointIdx);

private:
	CLimbUnit m_Limb[4];
	CBodyUnit m_body;
	CHeadUnit m_head;

};

