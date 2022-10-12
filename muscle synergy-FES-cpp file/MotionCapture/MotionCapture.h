
// MotionCapture.h : MotionCapture ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.
#include "Graphics/OpenGL.h"
#include "Graphics/Camera.h"
#include "DataTypes/Vec.h"
#include "DataTypes/Mat.h"
#include "Graphics\SurfaceObj.h"


// CMotionCaptureApp:
// �� Ŭ������ ������ ���ؼ��� MotionCapture.cpp�� �����Ͻʽÿ�.
//

class CMotionCaptureApp : public CWinAppEx
{
public:
	CMotionCaptureApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMotionCaptureApp theApp;
