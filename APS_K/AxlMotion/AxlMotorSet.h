#pragma once

#include "../StdAfx.h"
//#include "AxlDefine.h"


//! AjinExTek Motion Controller 클래스
//! Created, 2013/4/10
//! Recently Modified, 2013/4/19

//! 1] 아진엑스텍 Motion Controller는 위치 제어만 지원한다. 하지만, AxmMoveVel 처럼 일정한 속도로 움직이는 기능을 제공한다. 
//! 2] RTEX 제품 (PCI-R1604)에서는 Interrupt, Software Limit을 지원하지 않는다. 
//! 3] 서보 부하율을 알 수 있는 기능은 없다. 
//! 4] PCI-R1604 A4N, A5N의 경우 비상정지 입력단이 존재하지 않는다.
//!     (모션 모듈에 있는 비상정지 입력단 으로 신호를 넣게 되며 신호가 들어오면 ESTOP을 자동으로 내려 모든 모션에 대해서 정지)

//! [주의 사항] AA Bonder Vision부 Homing에서 기구 간섭
//!		1) 배사 조명을 후진 시킨 후에 Homing을 시작해야 한다. 
//!		2) Lens Z축 Motor가 위쪽으로 올라간 후에 다른 Motor들을 Homing해야 한다.
//!		3) PCB Y축 Motor가 (-) Limit 센서 쪽으로 간 이후에, PCB X, Theta 축 Motor를 Homing해야 한다. 
//!		4) PCB Theta축 Motor를 Homing하기 전에, PCB Cover 공기압 실린더를 상승시켜야 한다. 

//! 기존의 MMC Motion Controller와 함수명을 최대한 같이 하여, 소스 코드의 수정량을 줄인다. 


//! 아래 구조체는 특정 위치 (Limit 센서나 Home 센서)에서 자동으로 멈추도록 하여 모터를 움직일 때 사용한다.
struct strMove_Input_Signal_Search
{
	double dVel;
	double dAccel;

	//! 검출 신호 설정 (아래 4개의 변수 중 1개는 true이어야 한다)
	bool bEndLimit_Positive;
	bool bEndLimit_Negative;
	bool bHomeSensor;
	bool bPhase_Encoder_Z;		//! Encoder의 Z상 신호

	//! Edge 설정 (아래 2개의 변수 중 1개는 true이어야 한다)
	bool bEdge_Down;
	bool bEdge_Up;

	//! 정지 방법 (아래 2개의 변수 중 1개는 true이어야 한다)
	bool bEmergency;
	bool bSlowDown;

	strMove_Input_Signal_Search()
	{
		InitInfo();
	}

	void InitInfo()
	{
		dVel = 0.;
		dAccel = 0.;

		bEndLimit_Positive = false;
		bEndLimit_Negative = false;
		bHomeSensor = false;
		bPhase_Encoder_Z = false;

		bEdge_Down = false;
		bEdge_Up = false;

		bEmergency = false;
		bSlowDown = false;
	}

	strMove_Input_Signal_Search& operator=(const strMove_Input_Signal_Search &input)	//! '=' 연산자 overloading
	{
		dVel   = input.dVel;
		dAccel = input.dAccel;

		bEndLimit_Positive = input.bEndLimit_Positive;
		bEndLimit_Negative = input.bEndLimit_Negative;
		bHomeSensor        = input.bHomeSensor;
		bPhase_Encoder_Z   = input.bPhase_Encoder_Z;

		bEdge_Down = input.bEdge_Down;
		bEdge_Up   = input.bEdge_Up;

		bEmergency = input.bEmergency;
		bSlowDown  = input.bSlowDown;

		return *this;
	}
};//! struct strMove_Input_Signal_Search


class CAxlMotorSet
{
public:
	CAxlMotorSet(void);
	~CAxlMotorSet(void);

private:
	//! 해당 절대 경로의 파일에 Motion Board의 설정값을 파일로 저장 가능
	CString m_sMotionSettingFilePath;



public:
	CString sMsg;
	bool m_bOrgFlag[MAX_MOTOR_NO];
	char m_szLogMsg[256];

	CCriticalSection m_criHomeProc;

	bool bAxdConnect;

	bool Axl_Init();
	int  Axl_Axisconfig();
	int  Axl_DIO_Config();
	bool Axl_DIO_Reset();

	void Axl_Close();


	bool InDIO(int moduleNo, int &inVal);
	bool OutDIO(int moduleNo, int outVal);
	bool OutDIO(int moduleNo, int chNo, int no);

	bool GetOutputIO(int moduleNo, int &outVal);


	bool AmpEnable(int iAxis);				//! 지정 축의 Servo-On을 실시
	bool AmpEnableAll();						
	bool AmpDisable(int iAxis);				//! 지정 축의 Servo-Off을 실시
	bool AmpDisableAll();
	bool GetAmpEnable(int iAxis);			//! 지정 축의 Servo-On 신호의 출력 상태를 반환(T=ON, F=OFF 상태)
	bool GetAmpEnableAll();					//! AAB Unit별 Servo-Off 상태가 있을 경우 false
	
	bool AmpFaultReset(int iAxis);			//! 알람 Reset후 Servo-On 실시
	bool AmpFaultResetAll();
	int	 AmpFaultCheck();					//! 알람 신호 확인

	bool GetAmpFault( int iAxis);			//! 지정 축의 알람 상태 반환
	
	bool GetInposition(int iAxis);			//! 지정 축의 Motor가 목표 지점에 도착했는지 확인
	bool GetInpositionPos(int iAxis, double dPos);	//! 지정 축의 Motor가 목표 지점에 도착했는지 확인( Encord값으로 확인)
	bool GetHomeSensor(int iAxis);			//! 지정 축의 Home 센서 신호의 입력 확인
	bool GetNegaSensor(int iAxis);			//! 지정 축의 (-)리미트 센서 신호의 입력 확인
	bool GetPosiSensor(int iAxis);			//! 지정 축의 (+)리미트 센서 신호의 입력 확인

	bool ActCRC(int axis);

	bool IsStopAxis(int axis);				//! 모터 정지 상태 반환(T=정지, F=구동중)
	bool StopAxis(int axis);
	bool StopAxisAll();

	double GetEncoderPos(int iAxis);		//! Linear 모터 위치 좌표 반환
	double GetEncoderPos_Disp(int iAxis);	//! Linear 모터 위치좌표에서 강제 원점 좌표까지 계산된 좌표 반환
	double GetCommandPos(int iAxis);		//! Steping 모터 위치 좌표 반환
	double GetCommandPos_Disp(int iAxis);	//! Steping 모터 위치좌표에서 강제 원점 좌표까지 계산된 좌표 반환	
	double CalcAccFromAccTime(double dVel, double dTime);						//! 가속도 = 속도/(가속 시간)으로 계산
	BOOL JogMove(int iAxis, double dVel);										//! 설정한 속도로 구동한다.
	BOOL JogStop(int iAxis);													//! 지정한 축의 구동을 감속정지합니다.
	bool MoveAxis(int axis, bool AbSFlag, double dPos, double dVel, float iAcc);						//! 지정 축을 절대 구동 또는 상대 구동으로 이동한다.
	bool MoveAxisMulti(int iAxisCnt, short iAxis[MAX_MOTOR_NO], double pos[MAX_MOTOR_NO], int iSpeed);	//! 여러 개의 축에 대해서 현재의 위치에서 지정한 거리만큼 이동을 동시에 시작한다

	bool MoveAxis_To_Sensor(int axis, strMove_Input_Signal_Search *pstrInput);



	

	bool goMotorPos(int no, short axis[MAX_MOTOR_NO], double pos[MAX_MOTOR_NO], bool bAutoRun = true);

	bool goMotorZPos(int no, short axis[MAX_MOTOR_NO], double pos[MAX_MOTOR_NO], double dVel, bool bAutoRun = true);

	bool Move_From_GUI(int axis, int iID_GUI, CWnd* pParentWnd, bool bPlus = true);
		
	bool GetResult_Home_Search(int axis, CString &sResult);	//! Home 검색 작업 상태 및 결과 문자열을 알아낸다. 
	int IsCompleted_Home_Search(int axis);					//! Home검색 상태 확인(0=Fail, 1=Success, 2=Searching)
	int  GetRate_Home_Search(int axis);						//! Home 검색 작업 중의 진행 정도 반환, (단위 : %) 

	void Stop_Home_Search(int iAxis);						//! Home 검색 중에 강제로 중지 시킴

	int  Start_Home_Search(int iAxis);						//! Home 검색 작업 시작	
	DWORD SetHomeSearchSpeed(int iAxis);					//! 원점 검색시 사용되는 속도 설정	



	//! 아래의 함수들은 실제 장비에서 다시 제작해야 함
	int  HomeCheck();

	//! 기존 방식	
	bool HomeProcess(int axis);		//! 개별 원점 동작
	bool HomeProcessAll();			//! 전체 원점 동작.
	bool HomeProcessAll_2st();			//! 전체 원점 동작.

	int HomeSubReqProcess(int iAxis, int iStep, double &checkTime);	//! 실제 원점 동작.

	int HomeSubProcess(int axis, int iStep, double &iTime);		//! 실제 원점 동작. - 만도향 버젼.
	


	bool Lens_Motor_Conti_Down(int MotorAxis, bool waitFlag);//


	bool Lens_Motor_Move(int index, double offsetX=0.0, double offsetY=0.0, double offsetTh =0.0);
	bool Lens_Motor_MoveX(int index, double offsetY = 0.0 , bool bWait = true);
	bool Lens_Motor_MoveY(int index, double offsetY = 0.0, bool bWait = true);
	bool Lens_Motor_MoveXY(int index, double offsetX=0.0, double offsetY=0.0, bool bWait = true);
	bool Lens_Motor_Align_Move(double offsetX=0, double offsetY=0, double offsetTh=0.0);			/* Align Retry를 위해 추가 */
	bool Lens_Tilt_Motor_Move(int index, double offsetX=0.0, double offsetY=0.0);
	bool Lens_Motor_Move_Laser(int Pos, double offsetX, double offsetY, double offsetTh);		// Lens Tilt를 위해 추가
	


	bool Pcb_Motor_Move(int index, double offsetX = 0.0, double offsetY = 0.0, double offsetTh = 0.0, bool bWait = true);
	bool Pcb_Motor_MoveY(int index, double offsetY = 0.0 , bool bWait = true );  //정지확인 없는 이동 함수
	bool Pcb_Motor_MoveXY(int index, double offsetX = 0.0, double offsetY = 0.0, bool bWait = true);

	bool Dispense_XY_Motor_Move(int index, double dVel, double offsetX = 0, double offsetY = 0, double offsetTh = 0);
	bool DispenseGoMotorPos(int no, short axis[MAX_MOTOR_NO], double pos[MAX_MOTOR_NO], double dVel);
	bool Dispense_Z_Motor_Move(int index, double dVel);

	
	bool Pcb_Motor_Align_Move(double offsetX=0, double offsetY=0, double offsetTh=0);			/* Align Retry를 위해 추가 */

	bool Pcb_Side_Align_Move(int index, double offsetTx = 0);	//! Align 이동시만 사용 할것
	bool Pcb_Move_Side_Tilt(double offsetTy = 0, double offsetTh = 0);



	bool Pcb_Holder_Align_Move(int index, double offsetX=0, double offsetY=0, double offsetTh=0);	//! Align 이동시만 사용 할것
	bool Pcb_Tilt_Align_Move(double offsetX=0, double offsetY=0);
	bool Pcb_Tilt_Motor_Move(int index, double offsetX=0.0, double offsetY=0.0);
	
	bool Pcb_Tilt_Trinity_Move(double offsetX = 0, double offsetY = 0);

	bool Pcb_Motor_Move_Side_Laser(int Pos, double offsetX = 0, double offsetY = 0, double offsetTh = 0);
	
	bool Pcb_Motor_Move_Laser(int Pos, double offsetX = 0, double offsetY = 0, double offsetTh = 0);
	bool Pcb_Motor_Move_ComLaser(int Pos, double offsetX = 0, double offsetY = 0, double offsetTh = 0);	//완제품 Laser Pos
	bool Pcb_Move_Tilt(double offsetX = 0, double offsetY = 0);
	bool Lens_Move_Tilt(double offsetX=0, double offsetY=0);
	
	bool moveEpoxyCleanPos(int iIndex, bool waitFlag);

	bool LENS_Z_Motor_Move(int index , bool evasionMode = false);//evasion = 회피모드


	bool PCB_Z_Motor_Move(int index, double offsetZ = 0.0);
	bool PCB_Z_V_Motor_Move(int index,double dVel);

	bool checkLensMotorPos(int index, int naxisNum = 2);
	bool checkPcbMotorPos(int index);
	bool checkInspMotorPos(int index);

	bool Pcb_Motor_CircleMove(double dAngle, bool bWait = true, int Pos = 0);	//원호 보간 구동(PCB X/Y축)
	bool Pcb_Motor_Twister_Move(double dAngle, bool bWait = true, int Pos = 0);	//원호 보간 구동(PCB X/Y축)
	bool func_Epoxy_CircleDraw(bool CONTI = false);	//Dispenser 실제 도포 하며 원호 보간 구동  , conti모델 작은원그릴때만 true
	bool func_Epoxy_Draw();	//Dispenser 실제 도포 하며 아크 보간 구동
	bool func_Epoxy_Point_Draw();
	bool func_Epoxy_Rect_Circle_Draw();		//sony 모델 직선과 원형 


	bool func_New_Epoxy_Rect_Arck_Draw();


	bool func_Trinity_Epoxy_Rect_Draw();		//뒷면 외곽 선
	bool func_Trinity_Epoxy_Circle_Draw();		//뒷면 원형 3포인트

	bool func_Epoxy_Right_StraightDraw();	//20150603 도포I/O가 2개라서 Left, Right 나눔
	bool func_Epoxy_Left_StraightDraw();	//20150603 도포I/O가 2개라서 Left, Right 나눔
	bool Straight_Dispense_MoveAxis(int axis, bool AbSFlag, double dPos, double dVel, float iAcc); //20150603 직선 도포할 때 Y축 움직이는 함수

	bool Continue_Line_Arck_Dispense(); 	//직선 + 아크  모터 멈춤없이 진행

	bool moveSensorContactPos(bool waitFlag);
	bool checkOriginStatus(int iCnt, short* axis);		/* 원점 복귀 여부 확인 */
	bool moveWaitPos_Z(bool waitFlag);

	bool movePointDischargePos(bool waitFlag);		
	bool movePointDischarge2Pos(bool waitFlag);		
	bool moveDispensePos_Z(int iPcbNo, bool waitFlag);
	bool movePointDischargePos_Z(bool waitFlag);	
	bool moveDispense2Pos_Z(int iPcbNo, bool waitFlag);
	bool movePointDischarge2Pos_Z(bool waitFlag);



	
	bool Trinityt_Dispense_MoveAxis();//M_TRINITY 모델 연속 도포

};//! class CAxlMotorSet

