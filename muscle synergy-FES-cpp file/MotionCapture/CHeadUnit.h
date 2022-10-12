#pragma once
#include "Graphics\SurfaceObj.h"

class CHeadUnit
{
public:
	CHeadUnit();
	~CHeadUnit();

	void draw();
	void read();

private:
	SurfaceObj m_HeadUnit[2];
};

