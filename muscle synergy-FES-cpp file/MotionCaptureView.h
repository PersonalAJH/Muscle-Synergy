
// MotionCaptureView.h : CMotionCaptureView 클래스의 인터페이스
//

#pragma once

#include "CHumanUnit.h"
#include "CXsensWraper.h"

#include "FES\smpt_client.h"
#include "FES\smpt_messages.h"
#include "FES\smpt_packet_number_generator.h"
#pragma comment (lib, "libsmpt.lib")

// Mid_level stimulation : pulse frequency 생성
#include "FES\smpt_ml_client.h"

class CMotionCaptureView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMotionCaptureView();
	DECLARE_DYNCREATE(CMotionCaptureView)

// 특성입니다.
public:
	CMotionCaptureDoc* GetDocument() const;
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMotionCaptureView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// functions
protected:
	void InitGL();
	VOID GlPrint(const char *text);

	//Drawing
	void DrawView();
	void SetupView();
	void UpdateView();
	


	//ETC
	void RunSimul();
	
	//Electrical Stimulation
	void mid_level_stimulation(const char *port_name);
	void fill_ml_init(Smpt_device * const device, Smpt_ml_init *const ml_init);
	void fill_ml_update(Smpt_device * const device, Smpt_ml_update *const ml_update, const char *port_name);
	void fill_ml_get_current_data(Smpt_device * const device, Smpt_ml_get_current_data *const ml_get_current_data);

	// 통증이 오는 전류의 크기 찾기
	void find_current_stimulation(const char *port_name);
	bool currentSwitch[8];
	float currentAmp[8];
	float currentAmpTemp[8];
	float currentPW[8];
	float currentPWTemp[8];
	int portBias;
	int channelNum = 0;
	const char *port_name[2];	// FES usb 포트 번호
	FILE* AmpData;

protected:
	FILE* f;
	FILE* ff;
	FILE* fff;
	FILE* ffff;
	
	FILE* LegData;
	bool logCheck = false;
	bool simulCheck = false;
	bool initial = true;
	Vec3f rAngle0[2];
	Vec3f lAngle0[2];
	Vec3f sensorAngle[2];
	Vec3f sensorAngularVel[2];


	//정환
	Vec3f R_Angle;
	Vec3f L_Angle;
	Vec3f R_Ave[3];
	Vec3f R_Avetmp;
	
	Vec3f R_MoCapAngle[2];
	Vec3f L_MoCapAngle[2];
	Vec3f R_AngularVelocity;
	Vec3f L_AngularVelocity;

	float R_Anglesag;
	float R_AngularVelocitysag;
	float L_Anglesag;
	float L_AngularVelocitysag;
	float jhtmp[100];

	void Stimulation();
	void State();
	void update();
	void update_tmp();
	int Max(float state[]);
	int Min(float state[]);
	int Zeronum(float state[200]);

	int windownum;
	float jhtmp_1[20];
	float jhtmp_2[20];
	float jhtmp_3[20];
	float jhtmp_4[20];

	float statenumTemp;
	float jhstatenum;
	float front_1;	float front_2;	 float front_3;	 float front_4;
	float back_1;	float back_2;	 float back_3;	 float back_4;
	float mid_1;	float mid_2;	 float mid_3;	 float mid_4;
	int tmp;
	float OneCycle[5][200];  //30ms 에 한번 보행 한번에 최대 3초 100개만있어도 가능  수정 필요 100개의 사이클만 하는게 아니기 때문에 여러 싸이클상황시
	int Cyclenum;
	int Cyclenum_2;
	float OneCycle_2[200];

	float R_AngleCycle[5][200];
	float L_AngleCycle[5][200];
	float R_AngularvelocityCycle[5][200];
	float L_AngularvelocityCycle[5][200];

	float R_AngleCycle_tmp[200];
	float L_AngleCycle_tmp[200];
	float R_AngularvelocityCycle_tmp[200];
	float L_AngularvelocityCycle_tmp[200];

	int R_EC[5];	int L_EC[5];	
	int R_MS[5];	int L_MS[5];
	int R_IC[5];	int L_IC[5];

	int av_L_EC;	int av_R_EC;
	int av_L_MS;	int av_R_MS;
	int av_L_IC;	int av_R_IC;


	HDC     m_hDC;
	HGLRC   m_hRC;
	GLuint	base;

	//shader id
	GLuint m_ShaderProg;

	//flag
	bool LEFT_DOWN;
	bool RIGHT_DOWN;
	bool MODE;
	bool START;

	//window크기
	int m_WindowHeight;
	int m_WindowWidth;

	//camera
	CCamera m_Cam;

	//mouse position
	Vec3d m_MousePos;
	Vec3d m_PreMousePos;
	Vec3d m_DMousePos;

	CHumanUnit m_Human;
	CXsensWraper xsensWraper;
	int limb = 0;
	

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // MotionCaptureView.cpp의 디버그 버전
inline CMotionCaptureDoc* CMotionCaptureView::GetDocument() const
   { return reinterpret_cast<CMotionCaptureDoc*>(m_pDocument); }
#endif

