#include "stdafx.h"
#include "CHeadUnit.h"


CHeadUnit::CHeadUnit()
{
}


CHeadUnit::~CHeadUnit()
{
}

void CHeadUnit::draw()
{
	m_HeadUnit[1].drawObject(Vec3f(1, 1, 1));
	m_HeadUnit[0].drawObject(Vec3f(1, 1, 1));
}

void CHeadUnit::read()
{
	m_HeadUnit[1].readObjData("../data/obj/head.txt");
	m_HeadUnit[0].readObjData("../data/obj/neck.txt");
}
