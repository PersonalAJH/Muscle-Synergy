#include "stdafx.h"
#include "CBodyUnit.h"


CBodyUnit::CBodyUnit()
{
}


CBodyUnit::~CBodyUnit()
{
}

void CBodyUnit::read()
{
	m_BodyUnit[1].readObjData("../data/obj/upperBody.txt");
	m_BodyUnit[0].readObjData("../data/obj/lowerBody.txt");
}

void CBodyUnit::draw()
{
	m_BodyUnit[1].drawObject(Vec3f(1, 1, 1));
	m_BodyUnit[0].drawObject(Vec3f(1, 1, 1));
}
