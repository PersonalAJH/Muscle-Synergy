#include "stdafx.h"
#include "CRLegUnit.h"


CLegUnit::CLegUnit()
{
	jointOrg[2] = Vec3f(200, 10, -570);
	jointOrg[1] = Vec3f(170, 70, -1590);
	jointOrg[0] = Vec3f(170, 90, -2540);
}



CLegUnit::~CLegUnit()
{
}

void CLegUnit::setSide(int side_) {
	if (side_ != 1) {
		side = side_;
		for (int j = 0; j < 3; j++) {
			jointOrg[j][0] = -jointOrg[j][0];
		}
	}
}


void CLegUnit::read()
{
	if (side == 1) {
		m_LegUnit[2].readObjData("../data/obj/rightUpperLeg.txt");
		m_LegUnit[1].readObjData("../data/obj/rightLowerLeg.txt");
		m_LegUnit[0].readObjData("../data/obj/rightFoot.txt");
	}
	else {
		m_LegUnit[2].readObjData("../data/obj/leftUpperLeg.txt");
		m_LegUnit[1].readObjData("../data/obj/leftLowerLeg.txt");
		m_LegUnit[0].readObjData("../data/obj/leftFoot.txt");
	}

}

void CLegUnit::draw()
{
	m_LegUnit[2].drawObject(Vec3f(1, 1, 1));
	m_LegUnit[1].drawObject(Vec3f(1, 1, 1));
	m_LegUnit[0].drawObject(Vec3f(1, 1, 1));
}


void CLegUnit::rotateAll(Vec3f hand, Vec3f lower, Vec3f upper)
{
	upper = upper * PI / 180.0;
	lower = lower * PI / 180.0;
	hand = hand * PI / 180.0;

	transPart(-jointOrg[0], 0); 
	rotatePart(0, hand, 1); 
	rotatePart(0, -lower, -1);
	transPart(jointOrg[0] - jointOrg[1], 1); 

	rotatePart(0, lower, 1);
	rotatePart(1, lower, 1); 
	rotatePart(0, -upper, -1);
	rotatePart(1, -upper, -1);

	transPart(jointOrg[1] - jointOrg[2], 1); 
	rotatePart(2, upper, 1);
	rotatePart(1, upper, 1);
	rotatePart(0, upper, 1); 

	transPart(jointOrg[2], 1); 
}

void CLegUnit::calcInv(Vec3f wri2, Vec3f ang_elb)
{

}


void CLegUnit::rotateAll2(Vec3f hand, Vec3f lower, Vec3f upper)
{

	transPart(-jointOrg[0], 0); 
	rotatePart2(0, hand, 1); 
	rotatePart2(0, -lower, -1);
	transPart(jointOrg[0] - jointOrg[1], 1);


	rotatePart2(0, lower, 1);
	rotatePart2(1, lower, 1); 
	rotatePart2(0, -upper, -1);
	rotatePart2(1, -upper, -1);


	transPart(jointOrg[1] - jointOrg[2], 1); 
	rotatePart2(2, upper, 1);
	rotatePart2(1, upper, 1);
	rotatePart2(0, upper, 1); 
	transPart(jointOrg[2], 1);
}

void CLegUnit::transPart(Vec3f distance, int idx)
{
	if (idx == 0) { 
		m_LegUnit[2].translate(distance);
		m_LegUnit[1].translate(distance);
		m_LegUnit[0].translate(distance);
	}
	else { 
		m_LegUnit[2].translateC(distance);
		m_LegUnit[1].translateC(distance);
		m_LegUnit[0].translateC(distance);
	}

}

void CLegUnit::rotatePart(int idx, Vec3f angle, int dir)
{
	if (dir == 1) {
		m_LegUnit[idx].rotateC(Vec3f(1, 0, 0), angle[0]);
		m_LegUnit[idx].rotateC(Vec3f(0, 1, 0), angle[1]);
		m_LegUnit[idx].rotateC(Vec3f(0, 0, 1), angle[2]);
	}
	else if (dir == -1) {
		m_LegUnit[idx].rotateC(Vec3f(0, 0, 1), angle[2]);
		m_LegUnit[idx].rotateC(Vec3f(0, 1, 0), angle[1]);
		m_LegUnit[idx].rotateC(Vec3f(1, 0, 0), angle[0]);
	}
}

void CLegUnit::rotatePart2(int idx, Vec3f angle, int dir)
{
	rotateMat(idx, calMat(angle, dir));
}

void CLegUnit::rotateMat(int idx, Mat3x3f rot)
{
	m_LegUnit[idx].rotateC(rot);
}

