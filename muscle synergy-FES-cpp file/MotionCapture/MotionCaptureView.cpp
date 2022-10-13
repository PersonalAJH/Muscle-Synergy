
// MotionCaptureView.cpp : CMotionCaptureView 클래스의 구현
//
#include <stdio.h>
#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MotionCapture.h"


#endif

#include "MotionCaptureDoc.h"
#include "C:\Users\JH\Desktop\코드\Muscle-Synergy\muscle synergy-FES-cpp file\MotionCapture\MotionCaptureView.h"

#include <Windows.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CMotionCaptureView

IMPLEMENT_DYNCREATE(CMotionCaptureView, CView)

BEGIN_MESSAGE_MAP(CMotionCaptureView, CView)
   // 표준 인쇄 명령입니다.
   ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
   ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
   ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
   ON_WM_KEYDOWN()
   ON_WM_LBUTTONDOWN()
   ON_WM_LBUTTONUP()
   ON_WM_MOUSEMOVE()
   ON_WM_MOUSEWHEEL()
   ON_WM_RBUTTONDOWN()
   ON_WM_RBUTTONUP()
   ON_WM_SIZE()
   ON_WM_TIMER()
END_MESSAGE_MAP()

// CMotionCaptureView 생성/소멸

CMotionCaptureView::CMotionCaptureView()
{
   // TODO: 여기에 생성 코드를 추가합니다.
   FILE_R_ang = fopen("data2.txt", "w");
   FILE_L_ang = fopen("data3.txt", "w");
   FILE_R_angvel = fopen("data4.txt", "w");
   FILE_L_angvel = fopen("data5.txt", "w");
}

CMotionCaptureView::~CMotionCaptureView()
{
   fclose(LegData);
   fclose(FILE_R_ang);
   fclose(FILE_L_ang);
   fclose(FILE_R_angvel);
   fclose(FILE_L_angvel);

}

BOOL CMotionCaptureView::PreCreateWindow(CREATESTRUCT& cs)
{
   // TODO: CREATESTRUCT cs를 수정하여 여기에서
   //  Window 클래스 또는 스타일을 수정합니다.
   return CView::PreCreateWindow(cs);
}

void CMotionCaptureView::OnDraw(CDC* /*pDC*/)
{
   CMotionCaptureDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);
   if (!pDoc)
      return;

   // TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
   wglMakeCurrent(m_hDC, m_hRC);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   DrawView();
   SwapBuffers(m_hDC);
}

BOOL CMotionCaptureView::OnPreparePrinting(CPrintInfo* pInfo)
{
   // 기본적인 준비
   return DoPreparePrinting(pInfo);
}

void CMotionCaptureView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
   // TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMotionCaptureView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
   // TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMotionCaptureView 진단

#ifdef _DEBUG
void CMotionCaptureView::AssertValid() const
{
   CView::AssertValid();
}

void CMotionCaptureView::Dump(CDumpContext& dc) const
{
   CView::Dump(dc);
}

CMotionCaptureDoc* CMotionCaptureView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
   ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMotionCaptureDoc)));
   return (CMotionCaptureDoc*)m_pDocument;
}
#endif //_DEBUG

// CMotionCaptureView 메시지 처리기

void CMotionCaptureView::OnInitialUpdate()
{
   // FES 2개 포트 설정
   port_name[0] = "COM13";   // 첫번째 FES,   오른쪽 위
   port_name[1] = "COM14";   // 두번째 FES,   오른쪽 아래

   // 자극 전류 크기 설정
   for (int i = 0; i < 8; i++) {
      //currentSwitch[i] = true;
      //currentAmp[i] = 0;
      //currentAmpTemp[i] = 0;
      //currentPWTemp[i] = 400;
      //currentPW[i] = currentPWTemp[i];   //전류의 크기 설정시에는 PW 400µs로 고정
      currentPW[i] = 0;
   }
   
   AmpData = fopen("Ampdata.txt", "r");
   fscanf(AmpData, "%f %f %f %f %f %f %f %f", &currentAmp[0], &currentAmp[1], &currentAmp[2], &currentAmp[3], &currentAmp[4], &currentAmp[5], &currentAmp[6], &currentAmp[7]);
   fclose(AmpData);

   for (int i = 0; i < 8; i++) {
      std::cout << "출력값" << currentAmp[i] << std::endl;
   }
   //find_current_stimulation(port_name[0]);         // 초반에 EMG 측정 때 같이 측정하고 그후엔 안함 
   //channelNum = 4;   // 두번째 FES 채널은 4부터 시작
   //find_current_stimulation(port_name[1]);
   

   LEFT_DOWN = false;
   RIGHT_DOWN = false;
   START = false;
   SetTimer(1, 10, NULL);
   InitGL();

   // Xsens 센서 총 11개
   //xsensWraper.setDeviceID("00B43008", 0);
   //xsensWraper.setDeviceID("00B42707", 1);
//    xsensWraper.setDeviceID("00B43037", 0);         //R 다리
   //xsensWraper.setDeviceID("00B42B8A", 3);
   //xsensWraper.setDeviceID("00B43009", 1);         // L 다리   
   //xsensWraper.setDeviceID("00B42FED", 5);
   //xsensWraper.setDeviceID("00B43026", 6);
   //xsensWraper.setDeviceID("00B42AEE", 7);
   //xsensWraper.setDeviceID("00B42B8A", 8);
   //xsensWraper.setDeviceID("00B42BA4", 9);
   //xsensWraper.setDeviceID("00B426BC", 10);

   // 사용할 센서, 번호는 0번부터 지정


   xsensWraper.setDeviceID("00B42FED", 0);
   xsensWraper.setDeviceID("00B43026", 1);
   xsensWraper.setDeviceID("00B43037", 2);
   xsensWraper.setDeviceID("00B43009", 3);
   xsensWraper.setDeviceID("00B42AEE", 4);
   xsensWraper.setDeviceID("00B42707", 5);
   xsensWraper.setXsens();                                   

   m_Human.read();
   

   tmp = 0;
   Cyclenum = 0;
   Cyclenum_2 = 0;
   R_Ave[0] = Vec3f(0,0,0);
   R_Ave[1] = Vec3f(0, 0, 0);

   jhstatenum = 1;

   CView::OnInitialUpdate();
   R_FootAng.reserve(20);

}


void CMotionCaptureView::OnTimer(UINT_PTR nIDEvent)
{   
   // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
   InvalidateRect(NULL, FALSE);
   CView::OnTimer(nIDEvent);


   xsensWraper.runXsens();

   //for (int i = 0; i < 2; i++)
   //{
   //   sensorAngle[i] = xsensWraper.getAngle(i);
   //   sensorAngularVel[i] = xsensWraper.getGyro(i);
   //}
   

   R_Angle = -xsensWraper.getjhAngle(0);
   L_Angle = -xsensWraper.getjhAngle(1);
   



   R_MoCapAngle[0] = -xsensWraper.getAngle(0);      //진규
   L_MoCapAngle[0] = -xsensWraper.getAngle(1);      //진규
   //R_MoCapAngle[1] = xsensWraper.getAngle(2);      //진규
   //L_MoCapAngle[1] = xsensWraper.getAngle(3);      //진규
   //R_AngularVelocity = -xsensWraper.getAng(0);
   //L_AngularVelocity = -xsensWraper.getAng(1);
   R_AngularVelocity = -xsensWraper.getGyro(0);
   L_AngularVelocity = -xsensWraper.getGyro(1);
   
   R_Anglesag = R_Angle[0];
   L_Anglesag = L_Angle[0];
   R_AngularVelocitysag=R_AngularVelocity[0];
   L_AngularVelocitysag=L_AngularVelocity[0];
   
   m_Human.updateJointAngle(2, R_MoCapAngle[0], R_MoCapAngle[0], R_MoCapAngle[0]);
   m_Human.updateJointAngle(3, L_MoCapAngle[0], L_MoCapAngle[0], L_MoCapAngle[0]);



   

   
   State();
   tmp++;
   Cyclenum_2 = Cyclenum % 5;
   update();

   if ((front_1 > mid_1) && (back_1 > mid_1))  //&& (jhtmp < 0)
   {
      if (tmp > 60)
      {
         update_tmp();
      }
   }
   
   Stimulation();
   fprintf(FILE_R_ang, "%f \n", R_Anglesag);
   fprintf(FILE_L_ang, "%f \n", L_Anglesag);
   fprintf(FILE_R_angvel, "%f \n", R_AngularVelocitysag);
   fprintf(FILE_L_angvel, "%f \n", L_AngularVelocitysag);


}


void CMotionCaptureView::DrawView() 
{
   glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_LIGHTING_BIT);
   SetupView();
   UpdateView();

   m_Human.draw();
   
   Vec3f wriPos = m_Human.getPosition(limb, 0, 1);
      
   GLUquadricObj *qobj = 0;
   qobj = gluNewQuadric();
   glPushMatrix();
   glColor3f(0, 0, 1);
   glTranslatef(wriPos[0], wriPos[1], wriPos[2]);
   gluSphere(qobj, 100, 50, 50);
   glPopMatrix();
}

void CMotionCaptureView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
   char lsChar;
   lsChar = char(nChar);

   if (lsChar == 'Z')
   {
      xsensWraper.setInitialYaw();
   }
   if (lsChar == 'W')
   {
      simulCheck = false;
      logCheck = true;
      LegData = fopen("test10.txt", "w");
      fprintf(LegData, "UpperAngle(R)\tLowerAngle(R)\tUpperLegAV(R)\tLowerLegAV(R)\n");
      std::cout << "! Start Recording\n  ..." << std::endl;
   }
   if (lsChar == 'E')
   {
      logCheck = false;
      std::cout << "! Stop Recording" << std::endl;
   }
   if (lsChar == 'R')
   {
      char test[100];
      logCheck = false;
      simulCheck = true;
      LegData = fopen("test1.txt", "r");
      //fscanf(LegData, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n");
      std::cout << "! Start Simulation" << std::endl;
      std::cout << simulCheck << std::endl;
   }
   if (lsChar == 'T')
   {
      simulCheck = false;
      std::cout << "! Stop Simulation" << std::endl;
   }
   if (lsChar == 'A')
   {
      limb = 0;
      std::cout << "! RightArm Tracking..." << std::endl;
   }
   if (lsChar == 'S')
   {
      limb = 1;
      std::cout << "! LeftArm Tracking..." << std::endl;
   }
   if (lsChar == 'D')
   {
      limb = 2;
      std::cout << "! RightLeg Tracking..." << std::endl;
   }
   if (lsChar == 'F')
   {
      limb = 3;
      std::cout << "! LeftLeg Tracking..." << std::endl;
   }

   if (lsChar == 'Q')
   {
      fprintf(FILE_R_ang, " test is strating\n");
      fprintf(FILE_L_ang, " test is strating\n");
      fprintf(FILE_R_angvel, " test is strating\n");
      fprintf(FILE_L_angvel, " test is strating\n");

   }
   CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMotionCaptureView::OnLButtonDown(UINT nFlags, CPoint point)
{
   // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
   LEFT_DOWN = true;
   CView::OnLButtonDown(nFlags, point);
}

void CMotionCaptureView::OnLButtonUp(UINT nFlags, CPoint point)
{
   // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
   LEFT_DOWN = false;
   CView::OnLButtonUp(nFlags, point);
}

void CMotionCaptureView::OnMouseMove(UINT nFlags, CPoint point)
{
   // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
   m_MousePos[0] = point.x;
   m_MousePos[1] = -point.y;
   m_DMousePos = m_MousePos - m_PreMousePos;

   if (LEFT_DOWN)
      m_Cam.RotCamPos(m_DMousePos);
   if (RIGHT_DOWN)
      m_Cam.MoveCamPos(m_DMousePos);
   m_PreMousePos = m_MousePos;
   CView::OnMouseMove(nFlags, point);
}

BOOL CMotionCaptureView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
   // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
   Vec3d temp;
   m_Cam.m_Distance += zDelta * 0.5;
   m_Cam.RotCamPos(temp);
   return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CMotionCaptureView::OnRButtonDown(UINT nFlags, CPoint point)
{
   // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
   RIGHT_DOWN = true;
   CView::OnRButtonDown(nFlags, point);
}

void CMotionCaptureView::OnRButtonUp(UINT nFlags, CPoint point)
{
   // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
   RIGHT_DOWN = false;
   CView::OnRButtonUp(nFlags, point);
}

void CMotionCaptureView::OnSize(UINT nType, int cx, int cy)
{
   CView::OnSize(nType, cx, cy);

   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
   CSize size(cx, cy);
   m_WindowHeight = size.cy;
   m_WindowWidth = size.cx;
}


void CMotionCaptureView::SetupView()
{
   GLfloat diffuseLight[] = { 0.4f,0.4f,0.4f,1.0f };
   GLfloat ambientLight[] = { 0.2f,0.2f,0.2f,1.0f };
   GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

   glEnable(GL_DEPTH_TEST);
   glEnable(GL_CULL_FACE);
   //   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   //   glEnable(GL_BLEND);

   glEnable(GL_COLOR_MATERIAL);
   glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

   glEnable(GL_LIGHTING);
   glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
   glEnable(GL_LIGHT0);

   glFrontFace(GL_CCW);  
   //glFrontFace(GL_CW);
   glShadeModel(GL_SMOOTH);
   glPolygonMode(GL_FRONT, GL_FILL);
}

void CMotionCaptureView::UpdateView()
{
   glViewport(0, 0, m_WindowWidth, m_WindowHeight);
   float fovy = 45;
   float aspect = float(m_WindowWidth) / float(m_WindowHeight);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   gluPerspective(fovy, aspect, 1, 10000);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   //gluLookAt(m_Cam.m_Pos[0], m_Cam.m_Pos[1], m_Cam.m_Pos[2],
   //   m_Cam.m_Center[0], m_Cam.m_Center[1], m_Cam.m_Center[2],
   //   0, 0, 1);

   gluLookAt(m_Cam.m_Pos[0], m_Cam.m_Pos[1], m_Cam.m_Pos[2],
      m_Cam.m_Center[0], m_Cam.m_Center[1], m_Cam.m_Center[2],
      m_Cam.m_Up[0], m_Cam.m_Up[1], m_Cam.m_Up[2]);

   //gluLookAt(0, 5000, 1000,
   //   0, 0, 0,
   //   0, 0, 1);
}

void CMotionCaptureView::RunSimul()
{
   if (!feof(LegData))
   {
      float time;
      Vec3f rAngle[2];
      Vec3f lAngle[2];
      Vec3f fAngle[2];
      fscanf(LegData, "%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n", &rAngle[0][0], &rAngle[0][1], &rAngle[0][2],
         &rAngle[1][0], &rAngle[1][1], &rAngle[1][2], &lAngle[0][0], &lAngle[0][1], &lAngle[0][2], &lAngle[1][0], &lAngle[1][1], &lAngle[1][2], &time);
      //std::cout << angle[0] << std::endl;
      if (initial)
      {
         rAngle0[1] = rAngle[1];
         lAngle0[1] = lAngle[1];
         rAngle0[0] = rAngle[0];
         lAngle0[0] = lAngle[0];
         initial = false;
      }

      for (int j = 0; j < 2; j++)
      {
         rAngle[j] = rAngle[j] - rAngle0[j];
         lAngle[j] = lAngle[j] - lAngle0[j];
         rAngle[j][2] = 90;//rAngle0[j][2];
         lAngle[j][2] = 90;//lAngle0[j][2];
      }
      fAngle[0] = rAngle[1];
      fAngle[0][2] = 0;
      fAngle[1] = lAngle[1];
      fAngle[1][2] = 0;

      m_Human.updateJointAngle(2, fAngle[1], lAngle[1], lAngle[0]);
   }
}


void CMotionCaptureView::InitGL()
{
   COpenGL Initgl;

   //Initgl에 windows handle을 넘겨준다
   Initgl.SetHWND(m_hWnd);
   Initgl.SetupPixelFormat();
   base = Initgl.base;

   m_hDC = Initgl.m_hDC;
   m_hRC = Initgl.m_hRC;

   //Initgl.SetupShader("../shader/local");
   //m_ShaderProg = Initgl.GetProgLog();
   //glUniform3f(glGetUniformLocation(m_ShaderProg, "LightPosition"), 1000.0, 1000.0, 1000.0);
}

void CMotionCaptureView::GlPrint(const char *text)
{
   glPushAttrib(GL_LIST_BIT);
   glListBase(base - 32);
   glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
   glPopAttrib();
}

void CMotionCaptureView::mid_level_stimulation(const char *port_name) {
   //최종 자극 주는 함수 
   Smpt_device device = { 0 };
   smpt_open_serial_port(&device, port_name);

   //std::cout << "port_name : " << port_name << std::endl;      jh

   Smpt_ml_init ml_init = { 0 };           /* Struct for ml_init command */
   fill_ml_init(&device, &ml_init);
   smpt_send_ml_init(&device, &ml_init); /* Send the ml_init command to the stimulation unit */

   Smpt_ml_update ml_update = { 0 };       /* Struct for ml_update command */
   fill_ml_update(&device, &ml_update, port_name);
   smpt_send_ml_update(&device, &ml_update);

   Smpt_ml_get_current_data ml_get_current_data = { 0 };
   fill_ml_get_current_data(&device, &ml_get_current_data);
   smpt_send_ml_get_current_data(&device, &ml_get_current_data);

   /*if (statenumTemp != statenum) {
      smpt_send_ml_stop(&device, smpt_packet_number_generator_next(&device));
   }   
   smpt_close_serial_port(&device);*/

};

void CMotionCaptureView::fill_ml_init(Smpt_device * const device, Smpt_ml_init *const ml_init) { 
   /* Clear ml_init struct and set the data */
   smpt_clear_ml_init(ml_init);
   ml_init->packet_number = smpt_packet_number_generator_next(device);
};

void CMotionCaptureView::fill_ml_update(Smpt_device * const device, Smpt_ml_update *const ml_update, const char *port_name) {
   // Clear ml_update and set the data
   // 파라미터 설정 함수 

   if (port_name == "COM14") {      
      portBias = 4;
   }

   smpt_clear_ml_update(ml_update);
   ml_update->enable_channel[Smpt_Channel_Red] = true;   // Enable channel red 
   ml_update->enable_channel[Smpt_Channel_Blue] = true;  // Enable channel blue
   ml_update->enable_channel[Smpt_Channel_Black] = true; // Enable channel black
   ml_update->enable_channel[Smpt_Channel_White] = true; // Enable channel white
   ml_update->packet_number = smpt_packet_number_generator_next(device);

   // 0번 채널(red) 파라미터 설정
   ml_update->channel_config[Smpt_Channel_Red].number_of_points = 3;  // Set the number of points
   ml_update->channel_config[Smpt_Channel_Red].ramp = 1;            // 확인         
   ml_update->channel_config[Smpt_Channel_Red].period = 50;           // Frequency: 20 Hz

   /* Set the stimulation pulse */
   /* First point, current: (currentAmp) mA, positive, pulse width: (currentPW) µs */ 
   ml_update->channel_config[Smpt_Channel_Red].points[0].current = currentAmp[0 + portBias];
   ml_update->channel_config[Smpt_Channel_Red].points[0].time = currentPW[0 + portBias];

   // 1번 채널(blue) 파라미터 설정
   ml_update->channel_config[Smpt_Channel_Blue].number_of_points = 3;  // Set the number of points
   ml_update->channel_config[Smpt_Channel_Blue].ramp = 1;               
   ml_update->channel_config[Smpt_Channel_Blue].period = 50;         // Frequency: 20 Hz

   // First point, current: (CurrentAmp) mA, positive, pulse width: (currentPW) µs
   ml_update->channel_config[Smpt_Channel_Blue].points[0].current = currentAmp[1 + portBias];
   ml_update->channel_config[Smpt_Channel_Blue].points[0].time = currentPW[1 + portBias];

   // 2번 채널(black) 파라미터 설정
   ml_update->channel_config[Smpt_Channel_Black].number_of_points = 3;  // Set the number of points
   ml_update->channel_config[Smpt_Channel_Black].ramp = 1;              
   ml_update->channel_config[Smpt_Channel_Black].period = 50;         // Frequency: 20 Hz

   // First point, current: (CurrentAmp) mA, positive, pulse width: (currentPW) µs
   ml_update->channel_config[Smpt_Channel_Black].points[0].current = currentAmp[2 + portBias];
   ml_update->channel_config[Smpt_Channel_Black].points[0].time = currentPW[2 + portBias];

   // 3번 채널(white) 파라미터 설정
   ml_update->channel_config[Smpt_Channel_White].number_of_points = 3;  // Set the number of points
   ml_update->channel_config[Smpt_Channel_White].ramp = 1;              // Three lower pre-pulses 
   ml_update->channel_config[Smpt_Channel_White].period = 50;         // Frequency: 20 Hz

   // First point, current: (CurrentAmp) mA, positive, pulse width: (currentPW) µs
   ml_update->channel_config[Smpt_Channel_White].points[0].current = currentAmp[3 + portBias];
   ml_update->channel_config[Smpt_Channel_White].points[0].time = currentPW[3 + portBias];
   
};

void CMotionCaptureView::fill_ml_get_current_data(Smpt_device * const device, Smpt_ml_get_current_data *const ml_get_current_data) {
   // FES 기계로 명령을 전해주는 함수 

   ml_get_current_data->packet_number = smpt_packet_number_generator_next(device);
   ml_get_current_data->data_selection[Smpt_Ml_Data_Stimulation] = true; // get stimulation data 
};

void CMotionCaptureView::find_current_stimulation(const char *port_name) {
   //초기 amplitude 결정 하는 함수 

   std::cout << "port_name : " << port_name << std::endl;
   std::cout << "******전류의 크기 설정 0mA부터 시작******" << std::endl;
   portBias = 0;

   if (port_name == "COM10") {
      portBias = 4;
   }

   while (currentSwitch[channelNum]) {
      Smpt_device device = { 0 };
      smpt_open_serial_port(&device, port_name);

      Smpt_ml_init ml_init = { 0 };           // Struct for ml_init command
      fill_ml_init(&device, &ml_init);
      smpt_send_ml_init(&device, &ml_init); // Send the ml_init command to the stimulation unit


      Smpt_ml_update ml_update = { 0 };       // Struct for ml_update command
      fill_ml_update(&device, &ml_update, port_name);
      smpt_send_ml_update(&device, &ml_update);

      Smpt_ml_get_current_data ml_get_current_data = { 0 };
      fill_ml_get_current_data(&device, &ml_get_current_data);
      smpt_send_ml_get_current_data(&device, &ml_get_current_data);

      //smpt_send_ml_stop(&device, smpt_packet_number_generator_next(&device)); //자극 멈춤, 주석처리 없애면 한번자극하고 끝남
      smpt_close_serial_port(&device); //serial port 닫음

      std::cout << "현재 전류의 크기" << currentAmp[channelNum] << "mA   ";
      std::cout << "아픔?(y/n)" << std::endl;
      char DetectPain;
      std::cin >> DetectPain;

      if (DetectPain == 'y') {
         currentSwitch[channelNum] = false;
         DetectPain = 'n';

         currentAmpTemp[channelNum] = currentAmp[channelNum] - 1;
                  
         if (channelNum < 3 + portBias) {
            currentAmp[channelNum] = 0;
            channelNum++;
            std::cout << "다음 설정 채널" << channelNum << "번" << std::endl;
            find_current_stimulation(port_name);
         }
         else {
            
            for (int i = 0; i + portBias < 4 + portBias; i++) {
               currentAmp[i + portBias] = currentAmpTemp[i + portBias];
               currentPW[i + portBias] = 0;
               std::cout << i +portBias << "번 채널   " << currentAmp[i + portBias] << "mA" << std::endl;
            }
            if (port_name == "COM10") {
               std::cout << "******* 채널 별 전류 크기 *******" << std::endl;
               AmpData = fopen("Ampdata.txt", "w");
               for (int i = 0; i < 4 + portBias; i++) {
                  std::cout << i << "번 채널   " << currentAmp[i] << "mA" << std::endl;
                  fprintf(AmpData, "%f\t", currentAmp[i]);
                  currentPW[i] = 0; // PW를 0으로 설정
               }
               fclose(AmpData);
            }
            break;
         }
      }
      else {
         currentAmp[channelNum] = currentAmp[channelNum] + 1;
      }
   }
};



void CMotionCaptureView::Stimulation() {
   //statenumTemp = statenum;   // state 변화는지 확인하기 위함
   if (jhstatenum == 1)
   {   
      //td::cout << "   state 1      " << std::endl;
      /*
      currentAmp[0] = 10;   currentAmp[1] = 10;   currentAmp[2] = 10;   currentAmp[3] = 10;
      currentAmp[4] = 10;   currentAmp[5] = 10;   currentAmp[6] = 10;   currentAmp[7] = 10;
      */
      // 초기 전류 설정이 끝나면 PW을 0으로 PW를 설정해줘야함
      currentPW[0] = 0;   currentPW[1] = 0;   currentPW[2] = 0;   currentPW[3] = 0;
      currentPW[4] = 250;   currentPW[5] = 250;   currentPW[6] = 0;   currentPW[7] = 0;
            
      mid_level_stimulation(port_name[0]);
      mid_level_stimulation(port_name[1]);

   }

   if (jhstatenum == 2)
   {
      //std::cout << "   state 2      " << std::endl;
      /*
      currentAmp[0] = 10;   currentAmp[1] = 10;   currentAmp[2] = 10;   currentAmp[3] = 10;
      currentAmp[4] = 10;   currentAmp[5] = 10;   currentAmp[6] = 10;   currentAmp[7] = 10;
      */
      // 초기 전류 설정이 끝나면 PW을 0으로 PW를 설정해줘야함
      currentPW[0] = 0;   currentPW[1] = 0;   currentPW[2] = 0;   currentPW[3] = 0;
      currentPW[4] = 0;   currentPW[5] = 0;   currentPW[6] = 0;   currentPW[7] = 0;
      
      mid_level_stimulation(port_name[0]);
      mid_level_stimulation(port_name[1]);
   }

   if (jhstatenum == 3)
   {   
      //std::cout << "   state 3      " << std::endl;
      /*
      currentAmp[0] = 10;   currentAmp[1] = 10;   currentAmp[2] = 10;   currentAmp[3] = 10;
      currentAmp[4] = 10;   currentAmp[5] = 10;   currentAmp[6] = 10;   currentAmp[7] = 10;
      */
      // 초기 전류 설정이 끝나면 PW을 0으로 PW를 설정해줘야함
      currentPW[0] = 0;   currentPW[1] = 0;   currentPW[2] = 0;   currentPW[3] = 0;
      currentPW[4] = 0;   currentPW[5] = 150;   currentPW[6] = 0;   currentPW[7] = 0;

      mid_level_stimulation(port_name[0]);
      mid_level_stimulation(port_name[1]);

   }

   if (jhstatenum == 4)
   {   
      //std::cout << "   state 4      " << std::endl;
      /*
      currentAmp[0] = 10;   currentAmp[1] = 10;   currentAmp[2] = 10;   currentAmp[3] = 10;
      currentAmp[4] = 10;   currentAmp[5] = 10;   currentAmp[6] = 10;   currentAmp[7] = 10;
      */
      // 초기 전류 설정이 끝나면 PW을 0으로 PW를 설정해줘야함
      currentPW[0] = 0;   currentPW[1] = 0;   currentPW[2] = 0;   currentPW[3] = 0;
      currentPW[4] = 0;   currentPW[5] = 0;   currentPW[6] = 0;   currentPW[7] = 0;
      
      mid_level_stimulation(port_name[0]);
      mid_level_stimulation(port_name[1]);

   }

   if (jhstatenum == 5)
   {   
      //std::cout << "   state 5      " << std::endl;
      /*
      currentAmp[0] = 10;   currentAmp[1] = 10;   currentAmp[2] = 10;   currentAmp[3] = 10;
      currentAmp[4] = 10;   currentAmp[5] = 10;   currentAmp[6] = 10;   currentAmp[7] = 10;
      */
      // 초기 전류 설정이 끝나면 PW을 0으로 PW를 설정해줘야함
      currentPW[0] = 150;   currentPW[1] = 0;   currentPW[2] = 0;   currentPW[3] = 0;
      currentPW[4] = 100;   currentPW[5] = 0;   currentPW[6] = 0;   currentPW[7] = 0;

      mid_level_stimulation(port_name[0]);
      mid_level_stimulation(port_name[1]);

   }

   if (jhstatenum == 6)
   {   
      //std::cout << "   state 6      " << std::endl;
      /*
      currentAmp[0] = 10;   currentAmp[1] = 10;   currentAmp[2] = 10;   currentAmp[3] = 10;
      currentAmp[4] = 10;   currentAmp[5] = 10;   currentAmp[6] = 10;   currentAmp[7] = 10;
      */
      // 초기 전류 설정이 끝나면 PW을 0으로 PW를 설정해줘야함
      currentPW[0] = 0;   currentPW[1] = 0;   currentPW[2] = 0;   currentPW[3] = 0;
      currentPW[4] = 0;   currentPW[5] = 0;   currentPW[6] = 0;   currentPW[7] = 0;

      mid_level_stimulation(port_name[0]);
      mid_level_stimulation(port_name[1]);

   }
}

void CMotionCaptureView::State() {
   //이전 다섯개의 평균을 이용 R_Angle L_Angle R_AngularVelocity  L_AngularVelocity   
   // R_IC = 1 : R_Angle 이 가장 작을때            
   // L_EC = 2 : L_Angular velocity 가 가장 작을때
   // L_MS = 3 : L_Angular Velocity 가 가장 클때
   // L_IC = 4 : L_Angle 이 가장 작을 때
   // R_EC = 5 : R_Angular velocity 가 가장 작을때
   // R_MS = 6 : R_Angular Velocity 가 가장 클때

   // 이니셜 컨택트 지정 

	R_FootAng.push_back(R_Anglesag);
	if(R_FootAng.size() > 20){
		R_FootAng.erase(R_FootAng.begin());
	}

   windownum = 2;
   front_1 = 0; back_1 = 0;
   for (int i = 19-2*windownum; i < 19-windownum; i++) {
      front_1 = front_1 + R_FootAng.at(i);
   }

   for (int i = 20 - windownum; i < 20; i++) {
      back_1 = back_1 + R_FootAng.at(i);
   }

   mid_1 = windownum * R_FootAng.at(19 - windownum);




   if (tmp < av_L_EC) {
      jhstatenum = 1;
   }
   else if (av_L_EC < tmp < av_L_MS) {
      jhstatenum = 2;
   }
   else if (av_L_MS < tmp < av_L_IC) {
      jhstatenum = 3;
   }
   else if (av_L_IC < tmp < av_R_EC) {
      jhstatenum = 4;
   }
   else if (av_R_EC < tmp < av_R_MS) {
      jhstatenum = 5;
   }
   else
      jhstatenum = 6;
   



}

int   CMotionCaptureView::Max(float state[]) {

   int j = 1;
   float max = state[0];
   for (int i = 0; i < 200; i++) {
      if (state[i] > max)
      {
         j = i;
         max = state[i];
      }
   }
   return j;
}

int    CMotionCaptureView::Min(float state[]) {

   int j = 1;
   float min = state[0];
   for (int i = 1; i < 200; i++) {
      if (state[i] < min)
      {
         j = i; 
         min = state[i];
      }
   }
   return j;
}

void CMotionCaptureView::update() {


   R_AngleCycle[Cyclenum_2][tmp] = R_Anglesag;
   L_AngleCycle[Cyclenum_2][tmp] = L_Anglesag;
   R_AngularvelocityCycle[Cyclenum_2][tmp] = R_AngularVelocitysag;
   L_AngularvelocityCycle[Cyclenum_2][tmp] = L_AngularVelocitysag;
}


void CMotionCaptureView::update_tmp() {

   fprintf(FILE_R_ang, " this is IC");
   fprintf(FILE_L_ang, " this is IC");
   fprintf(FILE_R_angvel, " this is IC");
   fprintf(FILE_L_angvel, " this is IC");

   for (int i = 0; i < 200; i++)
   {
      R_AngleCycle_tmp[i] = 0;
      L_AngleCycle_tmp[i] = 0;
      R_AngularvelocityCycle_tmp[i] = 0;
      L_AngularvelocityCycle_tmp[i] = 0;
   }


   for (int i = 0; i < 200; i++) {
      R_AngleCycle_tmp[i] = R_AngleCycle[Cyclenum_2-1][i];
      L_AngleCycle_tmp[i] = L_AngleCycle[Cyclenum_2-1][i];
      R_AngularvelocityCycle_tmp[i] = R_AngularvelocityCycle[Cyclenum_2-1][i];
      L_AngularvelocityCycle_tmp[i] = L_AngularvelocityCycle[Cyclenum_2-1][i];
   }

   int zeronum = 0;

   zeronum = Zeronum(R_AngleCycle_tmp);

      for (int i = 0; i < 4; i++) {
         L_EC[i] = L_EC[i + 1];
         L_MS[i] = L_MS[i + 1];
         L_IC[i] = L_IC[i + 1];
         R_EC[i] = R_EC[i + 1];
         R_MS[i] = R_MS[i + 1];
      }

      L_EC[4] = Min(L_AngularvelocityCycle_tmp);
      L_MS[4] = Max(L_AngularvelocityCycle_tmp);
      L_IC[4] = Min(L_AngleCycle_tmp);
      R_EC[4] = Min(R_AngularvelocityCycle_tmp);
      R_MS[4] = Max(R_AngularvelocityCycle_tmp);


      av_L_EC = 0;
      av_L_MS = 0;
      av_L_IC = 0;
      av_R_EC = 0;
      av_R_MS = 0;


      for (int i = 0; i < 4; i++) {
         av_L_EC = av_L_EC + L_EC[i];
         av_L_MS = av_L_MS + L_MS[i];
         av_L_IC = av_L_IC + L_IC[i];
         av_R_EC = av_R_EC + R_EC[i];
         av_R_MS = av_R_MS + R_MS[i];
      }

      av_L_EC = av_L_EC / 5;
      av_L_MS = av_L_MS / 5;
      av_L_IC = av_L_IC / 5;
      av_R_EC = av_R_EC / 5;
      av_R_MS = av_R_MS / 5;


      tmp = 0;
      Cyclenum++;
      printf("statenum : %d \n", Cyclenum);
      printf("L_EC : %d , L_MS : %d , L_IC : %d, R_EC : %d , R_MS : %d \n ", L_EC[4], L_MS[4], L_IC[4], R_EC[4], R_MS[4]);
      
   
}


int CMotionCaptureView::Zeronum(float state[200]) {

   int idx=0;
   for (int i = 0; i < 200; i++)
   {
      if (state[i] == 0.0)
      {
         idx = idx + 1;
      }
   }
   return 200-idx;
}

