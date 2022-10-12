#pragma once
#include "Graphics\SurfaceObj.h"

class CBodyUnit
{
public:
	CBodyUnit();
	~CBodyUnit();
	void read();
	void draw();
private:
	SurfaceObj m_BodyUnit[2];
};

