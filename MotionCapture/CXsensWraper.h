#pragma once
#include "afxwin.h"
#include "MotionCapture.h"
#include <xsensdeviceapi.h> // The Xsens device API header
#include "conio.h"			// For non ANSI _kbhit() and _getch()

#include <string>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <set>
#include <list>
#include <utility>

#include "xsmutex.h"
#include <xstypes/xstime.h>

#define MAXDEVICE 11


class CXsensWraper
{
public:
	CXsensWraper();
	~CXsensWraper();

	void setDeviceID(char *deviceID, int idx);
	void setXsens();
	void runXsens();
	Vec3f getAngle(int idx);
	Vec3f getjhAngle(int idx);
	Vec3f getGyro(int idx);
	Vec3f getAcc(int idx);
	Vec3f getAng(int idx);

	void setInitialYaw();



private:
	bool	initialCheck;
	int		totalDevice;
	char*	deviceAry[MAXDEVICE];
	int		deviceNum[MAXDEVICE];
	Vec3f	angleData[MAXDEVICE];
	Vec3f	jh_angleData[MAXDEVICE];
	Vec3f	angleData_0[MAXDEVICE];
	Vec3f   avelData[MAXDEVICE];
	Vec3f	accData[MAXDEVICE];
	Vec3f   angVelData[MAXDEVICE];
	float	initialYaw[MAXDEVICE] = { 0, };


};

