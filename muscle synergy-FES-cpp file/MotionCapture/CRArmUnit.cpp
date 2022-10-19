#include "stdafx.h"
#include "RCArmUnit.h"


CLimbUnit::CLimbUnit()
{
	jointOrg[2] = Vec3f(430, -50, 950);  // upper  -> idx : 2
	jointOrg[1] = Vec3f(520, -50, 160);  // lower  -> idx : 1
	jointOrg[0] = Vec3f(550, -50, -500); // hand   -> idx : 0
	jointOrg[3] = Vec3f(490, -20, -860); // endpos -> idx : 4
}

CLimbUnit::~CLimbUnit()
{
}

void CLimbUnit::setSide(int _side) {
	if (_side != 1) {
		side = _side;
		for (int j = 0; j < 4; j++) {
			jointOrg[j][0] = -jointOrg[j][0];
		}
	}
}

void CLimbUnit::setLimb(int partsIdx)
{
	limb = partsIdx;
	switch (partsIdx)
	{
	case 0:
		jointOrg[2] = Vec3f(430, -50, 950);  // upper  -> idx : 2
		jointOrg[1] = Vec3f(520, -50, 160);  // lower  -> idx : 1
		jointOrg[0] = Vec3f(550, -50, -500); // hand   -> idx : 0
		jointOrg[3] = Vec3f(490, -20, -860); // endpos -> idx : 4
		setSide(1);
		break;
	case 1:
		jointOrg[2] = Vec3f(430, -50, 950);  // upper  -> idx : 2
		jointOrg[1] = Vec3f(520, -50, 160);  // lower  -> idx : 1
		jointOrg[0] = Vec3f(550, -50, -500); // hand   -> idx : 0
		jointOrg[3] = Vec3f(490, -20, -860); // endpos -> idx : 4
		setSide(-1);
		break;
	case 2:
		jointOrg[2] = Vec3f(200, 10, -570);  // upper  -> idx : 2
		jointOrg[1] = Vec3f(170, 70, -1590);  // lower  -> idx : 1
		jointOrg[0] = Vec3f(170, 90, -2540); // hand   -> idx : 0
		jointOrg[3] = Vec3f(490, -20, -860); // endpos -> idx : 4
		setSide(1);
		break;
	case 3:
		jointOrg[2] = Vec3f(200, 10, -570);  // upper  -> idx : 2
		jointOrg[1] = Vec3f(170, 70, -1590);  // lower  -> idx : 1
		jointOrg[0] = Vec3f(170, 90, -2540); // hand   -> idx : 0
		jointOrg[3] = Vec3f(490, -20, -860); // endpos -> idx : 4
		setSide(-1);		
		break;
	}
}

void CLimbUnit::read()
{
	if (limb < 2)
	{
		if (side == 1) {
			m_ArmUnit[2].readObjData("../data/obj/rightUpperArm.txt");
			m_ArmUnit[1].readObjData("../data/obj/rightLowerArm.txt");
			m_ArmUnit[0].readObjData("../data/obj/rightHand.txt");
		}
		else {
			m_ArmUnit[2].readObjData("../data/obj/leftUpperArm.txt");
			m_ArmUnit[1].readObjData("../data/obj/leftLowerArm.txt");
			m_ArmUnit[0].readObjData("../data/obj/leftHand.txt");
		}
	}
	else
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

}

void CLimbUnit::draw()
{
	m_ArmUnit[2].drawObject(Vec3f(1, 1, 1));
	m_ArmUnit[1].drawObject(Vec3f(1, 1, 1));
	m_ArmUnit[0].drawObject(Vec3f(1, 1, 1));
}

void CLimbUnit::rotateMat(int idx, Mat3x3f rot)
{
	m_ArmUnit[idx].rotateC(rot);
}

// Mat3x3f CLimbUnit::calcMat(Vec3f angle, int dir) {
// 	float a = angle[2] * PI / 180;
// 	float b = angle[1] * PI / 180;
// 	float c = angle[0] * PI / 180;
// 	Vec3f r1;
// 	Vec3f r2;
// 	Vec3f r3;
// 	if (dir == 1) { // ZYX ȸ��
// 		r1 = Vec3f(cos(a)*cos(b), cos(a)*sin(b)*sin(c) - sin(a)*cos(c), cos(a)*sin(b)*cos(c) + sin(a)*sin(c));
// 		r2 = Vec3f(sin(a)*cos(b), sin(a)*sin(b)*sin(c) + cos(a)*cos(c), sin(a)*sin(b)*cos(c) - cos(a)*sin(c));
// 		r3 = Vec3f(-sin(b), cos(b)*sin(c), cos(b)*cos(c));
// 	}
// 	else {			// XYZ ȸ��
// 		r1 = Vec3f(cos(a)*cos(b), -sin(a)*cos(b), sin(b));
// 		r2 = Vec3f( cos(a)*sin(b)*sin(c) + sin(a)*cos(c), -sin(a)*sin(b)*sin(c) + cos(a)*cos(c), -cos(b)*sin(c));
// 		r3 = Vec3f(-cos(a)*sin(b)*cos(c) + sin(a)*sin(c),  sin(a)*sin(b)*cos(c) + cos(a)*sin(c),  cos(b)*cos(c));
// 	}

// 	return Mat3x3f(r1, r2, r3);
// }

void CLimbUnit::calcEnd(Vec3f hand, Vec3f lower, Vec3f upper)
{
	jointPos_FK[1] = jointOrg[2] + calcMat(upper, 1) * (jointOrg[1] - jointOrg[2]);
	jointPos_FK[0] = jointPos_FK[1] + calcMat(lower, 1) * (jointOrg[0] - jointOrg[1]);
	jointPos_FK[4] = jointPos_FK[0] + calcMat(hand,  1) * (jointOrg[4] - jointOrg[0]);
}


void CLimbUnit::calcInv(Vec3f wri2, Vec3f ang_elb)
{
	Vec3f sho = jointOrg[2];
	Vec3f elb = jointOrg[1];
	Vec3f wri = jointOrg[0];
	Vec3f end = jointOrg[3];
	Vec3f elb2 = wri2 + calcMat(ang_elb, 1) * (elb - wri);
	Vec3f L1_0 = elb - sho;
	Vec3f L2_0 = wri - elb;
	Vec3f L1_t = elb2 - sho;
	Vec3f L2_t = wri2 - elb2;
	Vec3f L3_t = L1_t + L2_t;
	Vec3f nx = calcCross(L1_t, L3_t); nx = nx / calcNorm(nx);
	float n_L1 = calcNorm(L1_t);
	float n_L2 = calcNorm(L2_t);
	float n_L3 = calcNorm(L3_t);

	theta4 = acos((n_L1*n_L1 + n_L2 * n_L2 - n_L3 * n_L3) / (2 * n_L1*n_L2)) * 180 / PI;
	theta4_ = theta4 - 180;

	float theta4_r = theta4_ * PI / 180;
	float vt = 1 - cos(theta4_r);
	Vec3f RK1 = Vec3f(nx[0] * nx[0] * vt + cos(theta4_r), nx[0] * nx[1] * vt - nx[2] * sin(theta4_r), nx[0] * nx[2] * vt + nx[1] * sin(theta4_r));
	Vec3f RK2 = Vec3f(nx[0] * nx[1] * vt + nx[2] * sin(theta4_r), nx[1] * nx[1] * vt + cos(theta4_r), nx[1] * nx[2] * vt - nx[0] * sin(theta4_r));
	Vec3f RK3 = Vec3f(nx[0] * nx[2] * vt - nx[1] * sin(theta4_r), nx[1] * nx[2] * vt + nx[0] * sin(theta4_r), nx[2] * nx[2] * vt + cos(theta4_r));
	Mat3x3f R_k = Mat3x3f(RK1, RK2, RK3);

	Mat3x3f R_sho = R_k * calcMat(ang_elb, 1); // new version1

	invAngle(2) = atan2f(R_sho(1, 0), R_sho(0, 0)) * 180 / PI;
	invAngle(1) = atan2f(-R_sho(2, 0), sqrt(R_sho(2, 1)*R_sho(2, 1) + R_sho(2, 2)*R_sho(2, 2))) * 180 / PI;
	invAngle(0) = atan2f(R_sho(2, 1), R_sho(2, 2)) * 180 / PI;

	jointPos_IK[1] = jointOrg[2] + calcMat(invAngle, 1) * (elb - sho);
	jointPos_IK[0] = jointPos_IK[1] + calcMat(ang_elb, 1) * (wri - elb);
	jointPos_IK[3] = jointPos_IK[0] + calcMat(ang_elb, 1) * (end - wri);
	
	updateJointAngle_IK2(ang_elb, ang_elb, invAngle);
}

Vec3f CLimbUnit::calcCross(Vec3f v1, Vec3f v2)
{
	Vec3f v3 = Vec3f(v1[1] * v2[2] - v1[2] * v2[1], 
					 v1[2] * v2[0] - v1[0] * v2[2], 
					 v1[0] * v2[1] - v1[1] * v2[0]);
	return v3;
}

float CLimbUnit::calcNorm(Vec3f v1)
{	
	return sqrt(v1[0] * v1[0] + v1[1] * v1[1] + v1[2] * v1[2]);
}

void CLimbUnit::updateJointAngle(Vec3f hand, Vec3f low, Vec3f up)
{
	calcEnd(hand, low, up);

	m_ArmUnit[2].translate(-jointOrg[2]);
	rotateMat(2, calcMat(up, 1));
	m_ArmUnit[2].translateC(jointOrg[2]);

	m_ArmUnit[1].translate(-jointOrg[1]);
	rotateMat(1, calcMat(low, 1));
	m_ArmUnit[1].translateC(jointPos_FK[1]);

	m_ArmUnit[0].translate(-jointOrg[0]);
	rotateMat(0, calcMat(hand, 1));
	m_ArmUnit[0].translateC(jointPos_FK[0]);
}

void CLimbUnit::updateJointAngle_IK2(Vec3f hand, Vec3f low, Vec3f up)
{
	m_ArmUnit[2].translate(-jointOrg[2]);
	rotateMat(2, calcMat(up, 1));
	m_ArmUnit[2].translateC(jointOrg[2]);

	m_ArmUnit[1].translate(-jointOrg[1]);
	rotateMat(1, calcMat(low, 1));
	m_ArmUnit[1].translateC(jointPos_IK[1]);

	m_ArmUnit[0].translate(-jointOrg[0]);
	rotateMat(0, calcMat(hand, 1));
	m_ArmUnit[0].translateC(jointPos_IK[0]);
}

Vec3f CLimbUnit::getPosition(int idx, int FK)
{
	if (FK == 1)
		return jointPos_FK[idx];
	else
		return jointPos_IK[idx];
}

Vec3f CLimbUnit::getTheta4()
{
	return Vec3f(theta4_, 0, 0);
}

Vec3f CLimbUnit::getInvAng()
{
	return invAngle;
}


