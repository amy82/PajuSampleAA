// MotorHomDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AA Bonder.h"
#include "MotorHomDlg.h"
#include "afxdialogex.h"
#include "MotorSet.h"
#include "DioControl.h"


extern		CMotorSet	motor;
extern bool g_bMovingflag;
extern	CDioControl		Dio;

// CMotorHomDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMotorHomDlg, CDialogEx)

	CMotorHomDlg::CMotorHomDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMotorHomDlg::IDD, pParent)
{

}

CMotorHomDlg::~CMotorHomDlg()
{
}

void CMotorHomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_MSFLEXGRID_MOTOR, m_gridMotor);
}


BEGIN_MESSAGE_MAP(CMotorHomDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SERVO_ON_ALL, &CMotorHomDlg::OnBnClickedButtonServoOnAll)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CMotorHomDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_SERVO_OFF_ALL, &CMotorHomDlg::OnBnClickedButtonServoOffAll)
	ON_BN_CLICKED(IDC_BUTTON_HOME, &CMotorHomDlg::OnBnClickedButtonHome)
	ON_BN_CLICKED(IDC_BUTTON_HOME_STOP, &CMotorHomDlg::OnBnClickedButtonHomeStop)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CMotorHomDlg::OnBnClickedButtonReset)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_MOTION_INIT, &CMotorHomDlg::OnBnClickedButtonMotionInit)
END_MESSAGE_MAP()


// CMotorHomDlg 메시지 처리기입니다.


void CMotorHomDlg::OnBnClickedButtonReset()
{
	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;
	g_bMovingflag =true;

	char dispStr[100];
	sprintf_s(dispStr, "모터 Drive의 Alarm을 해제 합니다.");
	delayMsg(dispStr, 5000, M_COLOR_BLUE);

	if(!motor.AmpFaultResetAll())
	{
		errMsg("Amp Fault가 정상적으로 Reset되지 않았습니다");

		delayMsg(dispStr, -1, M_COLOR_GREEN);
	}
	else
	{
		sprintf_s(dispStr, "모터 Drive의 Alarm 해제.");
		delayMsg(dispStr, 1500, M_COLOR_GREEN);
	}

	g_bMovingflag =false;
}


void CMotorHomDlg::OnBnClickedButtonExit()
{
	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;
	g_bMovingflag =true;
	KillTimer(HOME_TIMER);

	g_bMovingflag =false;

	CDialogEx::OnOK();
}


BOOL CMotorHomDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	setInterface();

	timerRunFlag = false;
	SetTimer(HOME_TIMER, 200, NULL);

	return TRUE;
}

void CMotorHomDlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == HOME_TIMER)
	{
		if (!timerRunFlag)
		{
			timerRunFlag = true;

			dispMotorStatus();

			timerRunFlag = false;
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CMotorHomDlg::dispMotorStatus()
{
	CString str;
	int		status;
	double	motorPos;

	m_gridMotor.SetRedraw(FALSE);

	for(int i=0; i<MAX_MOTOR_NO; i++)
	{
		status	= motor.GetAxisStatus(i);
		motorPos	= motor.GetCurrentPos(i);


		str.Format("%.03f", motorPos);
		m_gridMotor.SetTextMatrix(i+1, 1, str);										// 모터 좌표..


		m_gridMotor.SetRow(i+1);

		m_gridMotor.SetCol(2);														// 원점 복귀
		if(motor.m_bOrgFlag[i])						m_gridMotor.SetCellBackColor(GRID_COLOR_GREEN);
		else										m_gridMotor.SetCellBackColor(GRID_COLOR_RED);

		//		m_gridMotor.SetCol(3);														// Servo On
		//		if(status[i] & ST_INPOSITION_STATUS)		m_gridMotor.SetCellBackColor(GRID_COLOR_GREEN);
		//		else										m_gridMotor.SetCellBackColor(0);

		m_gridMotor.SetCol(3);														// In-Position
		if(motor.GetInposition(i))					m_gridMotor.SetCellBackColor(GRID_COLOR_GREEN);
		else										m_gridMotor.SetCellBackColor(0);


		m_gridMotor.SetCol(4);														// (-) 센서
		if(status & ST_NEG_LIMIT)					m_gridMotor.SetCellBackColor(GRID_COLOR_RED);
		else										m_gridMotor.SetCellBackColor(0);

		m_gridMotor.SetCol(5);														// HOM 센서
		if(status & ST_HOME_SWITCH)					m_gridMotor.SetCellBackColor(GRID_COLOR_GREEN);
		else										m_gridMotor.SetCellBackColor(0);

		m_gridMotor.SetCol(6);														// (+) 센서
		if(status & ST_POS_LIMIT)					m_gridMotor.SetCellBackColor(GRID_COLOR_RED);
		else										m_gridMotor.SetCellBackColor(0);

		m_gridMotor.SetCol(7);														// Servo Alarm
		if(status & ST_AMP_FAULT)
			m_gridMotor.SetCellBackColor(GRID_COLOR_RED);
		else
			m_gridMotor.SetCellBackColor(0);
	}

	m_gridMotor.SetRedraw(TRUE); 
	m_gridMotor.Refresh();
}

void CMotorHomDlg::setInterface()
{
	CString tmpStr;

	m_gridMotor.SetRedraw(false); 

	m_gridMotor.SetRows(MAX_MOTOR_NO+1);
	m_gridMotor.SetCols(8);

	for(int i=0;i<MAX_MOTOR_NO+1;i++)
	{
		m_gridMotor.SetRowHeight(i, 450);
	}

	for(int i=0;i<8;i++)
		m_gridMotor.SetColAlignment(i, 4);

	int width = 870;
	m_gridMotor.SetColWidth(0,1600);
	m_gridMotor.SetColWidth(1,1600);
	m_gridMotor.SetColWidth(2,width);
	m_gridMotor.SetColWidth(3,width);
	m_gridMotor.SetColWidth(4,width);
	m_gridMotor.SetColWidth(5,width);
	m_gridMotor.SetColWidth(6,width);
	m_gridMotor.SetColWidth(7,width);

	m_gridMotor.SetTextMatrix(0, 0, "모터명");
	m_gridMotor.SetTextMatrix(0, 1, "현재 위치");
	m_gridMotor.SetTextMatrix(0, 2, "원점 확인");
	m_gridMotor.SetTextMatrix(0, 3, "In-Pos");
	m_gridMotor.SetTextMatrix(0, 4, "Limit (-)");
	m_gridMotor.SetTextMatrix(0, 5, "HOME");
	m_gridMotor.SetTextMatrix(0, 6, "Limit (+)");
	m_gridMotor.SetTextMatrix(0, 7, "Alram");

	for(int i=0; i<MAX_MOTOR_NO; i++)
	{
		m_gridMotor.SetTextMatrix(i+1, 0, MotorName[i]);
	}


	m_gridMotor.SetRedraw(TRUE); 
	m_gridMotor.Refresh();
}


void CMotorHomDlg::OnBnClickedButtonMotionInit()
{
	char dispStr[100];
	sprintf_s(dispStr, "모션 보드를 초기화 합니다.");
	delayMsg(dispStr, 5000, M_COLOR_BLUE);


	motor.MMC_Close();

	if(!motor.MMC_Init(dispStr))
	{
		errMsg(dispStr);

		char logStr[1000];
		sprintf_s(logStr, "모터 초기화에 실패 하였습니다. 2");
		errMsg(logStr);

	}
	else
	{
		sprintf_s(dispStr, "모션 보드를 초기화 성공.");
		delayMsg(dispStr, 1000, M_COLOR_GREEN);
	}
}

void CMotorHomDlg::OnBnClickedButtonServoOnAll()
{
	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;
	g_bMovingflag =true;

	char dispStr[100];
	sprintf_s(dispStr, "모터를 전체 Servo ON 힙니다.");
	delayMsg(dispStr, 5000, M_COLOR_BLUE);

	if(!motor.AmpEnableAll())
	{
		errMsg("Servo On 동작 이상");
	}
	else
	{
		sprintf_s(dispStr, "모터를 전체 Servo ON.");
		delayMsg(dispStr, 1500, M_COLOR_GREEN);
	}

	g_bMovingflag =false;
}

void CMotorHomDlg::OnBnClickedButtonServoOffAll()
{
	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;
	g_bMovingflag =true;

	char dispStr[100];
	sprintf_s(dispStr, "모터를 전체 Servo OFF.");
	delayMsg(dispStr, 5000, M_COLOR_BLUE);

	if(!motor.AmpDisableAll())
	{
		errMsg("Servo Off 동작 이상");
	}
	else
	{
		sprintf_s(dispStr, "모터를 전체 Servo OFF.");
		delayMsg(dispStr, 1500, M_COLOR_GREEN);
	}

	g_bMovingflag =false;
}


void CMotorHomDlg::OnBnClickedButtonHome()
{
	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;
	g_bMovingflag =true;

	if (askMsg("전체 원점 복귀 동작을 실행 하시겠습니까?"))
	{
		Dio.setLedLight(1);
		delayMsg("전체 모터를 원점 복귀 합니다.", 500000, M_COLOR_DARK_GREEN);
		motor.HomeProcessAll();
		delayMsg("전체 모터 원점 복귀를 완료.", 50000, M_COLOR_GREEN);
	}

	g_bMovingflag =false;
}


void CMotorHomDlg::OnBnClickedButtonHomeStop()
{
	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;
	g_bMovingflag =true;

	char dispStr[100];
	sprintf_s(dispStr, "모터 정지 中.");
	delayMsg(dispStr, 5000, M_COLOR_BLUE);

	if(!motor.StopAxisAll())
	{
		errMsg("모터 정지 동작 시간 초과 [1sec]");
	}
	else
	{
		sprintf_s(dispStr, "모터 정지.");
		delayMsg(dispStr, 1500, M_COLOR_GREEN);
	}

	g_bMovingflag =false;
}
