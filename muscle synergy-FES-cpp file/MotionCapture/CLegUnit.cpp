#include "stdafx.h"
#include "CLegUnit.h"


CLegUnit::CLegUnit()
{
	jointOrg[2] = midUpper;
	jointOrg[1] = midLower;
	jointOrg[0] = midHand;

	jointPos[2] = midUpper;
	jointPos[1] = midLower;
	jointPos[0] = midHand;
}



CLegUnit::~CLegUnit()
{
}

void CLegUnit::setSide(int _side) {
	if (_side != 1) {
		side = _side;
		for (int j = 0; j < 3; j++) {
			jointOrg[j][0] = -jointOrg[j][0];
		}
	}
}


void CLegUnit::read()
{
	if (side == 1) {
		m_ArmUnit[2].readObjData("../data/obj/rightUpperLeg.txt");
		m_ArmUnit[1].readObjData("../data/obj/rightLowerLeg.txt");
		m_ArmUnit[0].readObjData("../data/obj/rightFoot.txt");
	}
	else {
		m_ArmUnit[2].readObjData("../data/obj/leftUpperLeg.txt");
		m_ArmUnit[1].readObjData("../data/obj/leftLowerLeg.txt");
		m_ArmUnit[0].readObjData("../data/obj/leftFoot.txt");
	}

}

void CLegUnit::draw()
{
	m_ArmUnit[2].drawObject(Vec3f(1, 1, 1));
	m_ArmUnit[1].drawObject(Vec3f(1, 1, 1));
	m_ArmUnit[0].drawObject(Vec3f(1, 1, 1));
}


void CLegUnit::rotateAll(Vec3f hand, Vec3f lower, Vec3f upper)
{
	upper = upper * PI / 180.0;
	lower = lower * PI / 180.0;
	hand = hand * PI / 180.0;

	transPart(-jointOrg[0], 0); // 손목 관절 원점 이동

	rotatePart(0, hand, 1);  // 손목 회전
	rotatePart(0, -lower, -1);

	transPart(jointOrg[0] - jointOrg[1], 1); // 팔꿈치 관절 원점 이동


	rotatePart(0, lower, 1);
	rotatePart(1, lower, 1); // 손목, 팔꿈치 회전
	rotatePart(0, -upper, -1);
	rotatePart(1, -upper, -1);


	transPart(jointOrg[1] - jointOrg[2], 1); // 어깨 관절 원점으로 이동

	rotatePart(2, upper, 1);
	rotatePart(1, upper, 1);
	rotatePart(0, upper, 1); // 손목, 팔꿈치, 어깨 회전

	transPart(jointOrg[2], 1); // 어깨 관절 원위치
}

void CLegUnit::rotateAll2(Vec3f hand, Vec3f lower, Vec3f upper)
{

	transPart(-jointOrg[0], 0); // 손목 관절 원점 이동

	rotatePart2(0, hand, 1);  // 손목 회전
	rotatePart2(0, -lower, -1);

	transPart(jointOrg[0] - jointOrg[1], 1); // 팔꿈치 관절 원점 이동


	rotatePart2(0, lower, 1);
	rotatePart2(1, lower, 1); // 손목, 팔꿈치 회전
	rotatePart2(0, -upper, -1);
	rotatePart2(1, -upper, -1);


	transPart(jointOrg[1] - jointOrg[2], 1); // 어깨 관절 원점으로 이동

	rotatePart2(2, upper, 1);
	rotatePart2(1, upper, 1);
	rotatePart2(0, upper, 1); // 손목, 팔꿈치, 어깨 회전

	transPart(jointOrg[2], 1); // 어깨 관절 원위치
}

void CLegUnit::transPart(Vec3f distance, int idx)
{
	if (idx == 0) { // 초기위치 기준 이동
		m_ArmUnit[2].translate(distance);
		m_ArmUnit[1].translate(distance);
		m_ArmUnit[0].translate(distance);
	}
	else { // 현재위치 기준 이동
		m_ArmUnit[2].translateC(distance);
		m_ArmUnit[1].translateC(distance);
		m_ArmUnit[0].translateC(distance);
	}

}

void CLegUnit::rotatePart(int idx, Vec3f angle, int dir)
{
	if (dir == 1) {
		m_ArmUnit[idx].rotateC(Vec3f(1, 0, 0), angle[0]);
		m_ArmUnit[idx].rotateC(Vec3f(0, 1, 0), angle[1]);
		m_ArmUnit[idx].rotateC(Vec3f(0, 0, 1), angle[2]);
	}
	else if (dir == -1) {
		m_ArmUnit[idx].rotateC(Vec3f(0, 0, 1), angle[2]);
		m_ArmUnit[idx].rotateC(Vec3f(0, 1, 0), angle[1]);
		m_ArmUnit[idx].rotateC(Vec3f(1, 0, 0), angle[0]);
	}
}

void CLegUnit::rotatePart2(int idx, Vec3f angle, int dir)
{
	rotateMat(idx, calMat(angle, dir));
}

void CLegUnit::rotateMat(int idx, Mat3x3f rot)
{
	m_ArmUnit[idx].rotateC(rot);
}

Mat3x3f CLegUnit::calMat(Vec3f angle, int dir) {
	float a = angle[2] * PI / 180;
	float b = angle[1] * PI / 180;
	float c = angle[0] * PI / 180;
	Vec3f r1;
	Vec3f r2;
	Vec3f r3;
	if (dir == 1) {
		r1 = Vec3f(cos(a)*cos(b), cos(a)*sin(b)*sin(c) - sin(a)*cos(c), cos(a)*sin(b)*cos(c) + sin(a)*sin(c));
		r2 = Vec3f(sin(a)*cos(b), sin(a)*sin(b)*sin(c) + cos(a)*cos(c), sin(a)*sin(b)*cos(c) - cos(a)*sin(c));
		r3 = Vec3f(-sin(b), cos(b)*sin(c), cos(b)*cos(c));
	}
	else {
		r1 = Vec3f(cos(a)*cos(b), -sin(a)*cos(b), sin(b));
		r2 = Vec3f(cos(a)*sin(b)*sin(c) + sin(a)*cos(c), -sin(a)*sin(b)*sin(c) + cos(a)*cos(c), -cos(b)*sin(c));
		r3 = Vec3f(-cos(a)*sin(b)*cos(c) + sin(a)*sin(c), sin(a)*sin(b)*cos(c) + cos(a)*sin(c), cos(b)*cos(c));
	}

	return Mat3x3f(r1, r2, r3);
}

