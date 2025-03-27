// CCDMotorDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AA Bonder.h"
#include "AA BonderDlg.h"
#include "CCDMotorDlg.h"
#include "afxdialogex.h"

#include "GetNumDlg.h"
//#include "MotorSet.h"
#include "DioControl.h"
#include "DataHandler.h"


extern	CSystemData		sysData;
//extern	CMotorSet		motor;
extern	CDioControl		Dio;
extern	CModelData		model;
extern	CTask			Task;

extern	bool JogPlusflag;
extern	bool JogMinusflag;

extern bool g_bMovingflag;

// CCCDMotorDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCCDMotorDlg, CDialogEx)

CCCDMotorDlg::CCCDMotorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCCDMotorDlg::IDD, pParent)
{
	m_iSelMotor = -1;
}

CCCDMotorDlg::~CCCDMotorDlg()
{
}

void CCCDMotorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_MOTOR_NAME, m_labelMotorName);
	DDX_Control(pDX, IDC_MSFLEXGRID_MOTOR, m_gridMotor);
	DDX_Control(pDX, IDC_BUTTON_PLUS_X, m_JogPlus);
	DDX_Control(pDX, IDC_BUTTON_MINUS_X, m_JogMinus);
}


BEGIN_MESSAGE_MAP(CCCDMotorDlg, CDialogEx)
	ON_WM_TIMER()
//	ON_WM_SHOWWINDOW()
ON_WM_SHOWWINDOW()
ON_BN_CLICKED(IDC_BUTTON_MOTOR_SAVE, &CCCDMotorDlg::OnBnClickedButtonMotorSave)
ON_BN_CLICKED(IDC_BUTTON_MOTOR_WAIT, &CCCDMotorDlg::OnBnClickedButtonMotorWait)
ON_BN_CLICKED(IDC_BUTTON_MOTOR_SUPPLY, &CCCDMotorDlg::OnBnClickedButtonMotorSupply)
ON_BN_CLICKED(IDC_BUTTON_MOTOR_ALIGN, &CCCDMotorDlg::OnBnClickedButtonMotorAlign)
ON_BN_CLICKED(IDC_BUTTON_MOTOR_BOND, &CCCDMotorDlg::OnBnClickedButtonMotorBond)
ON_BN_CLICKED(IDC_BUTTON_MOTOR_BOND2, &CCCDMotorDlg::OnBnClickedButtonMotorBond2)
ON_BN_CLICKED(IDC_BUTTON_MOTOR_SPEED, &CCCDMotorDlg::OnBnClickedButtonMotorSpeed)
ON_BN_CLICKED(IDC_BUTTON_PLUS_X, &CCCDMotorDlg::OnBnClickedButtonPlusX)
ON_BN_CLICKED(IDC_BUTTON_MINUS_X, &CCCDMotorDlg::OnBnClickedButtonMinusX)
END_MESSAGE_MAP()


// CCCDMotorDlg 메시지 처리기입니다.


BOOL CCCDMotorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	setInterface();

	initMotorGrid();

	return TRUE;
}


void CCCDMotorDlg::setInterface()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

// 	WINDOWPLACEMENT wndpl;

// 	wndpl.rcNormalPosition = pFrame->m_rectCamDispPos2;
// 	wndpl.rcNormalPosition.top -= SUB_DLG_OFFSET_Y;
// 	wndpl.rcNormalPosition.bottom = MAIN_DLG_SIZE_Y-5;
// 	this->MoveWindow(&wndpl);
	CheckJogMotorSpeed();
	m_JogPlus.SetButtonStyle(0);
	m_JogMinus.SetButtonStyle(0);

	m_labelMotorName
		.SetBkColor(GRID_COLOR_SELECT)
		.SetTextColor(M_COLOR_BLACK)
		.SetFontBold(TRUE)
		.SetFontSize(24);
}


void CCCDMotorDlg::initMotorGrid()
{
	CString tmpStr;

	m_gridMotor.SetRedraw(FALSE);

	m_gridMotor.SetRows(7);
	m_gridMotor.SetCols(9);

	for(int i=0;i<7;i++)
	{
		m_gridMotor.SetRowHeight(i, 510);
	}

	for(int i=0;i<9;i++)
		m_gridMotor.SetColAlignment(i, 4);

	m_gridMotor.SetColWidth(0,1600);
	m_gridMotor.SetColWidth(1,1700);
	m_gridMotor.SetColWidth(2,1700);
	m_gridMotor.SetColWidth(3,1700);
	m_gridMotor.SetColWidth(4,1700);
	m_gridMotor.SetColWidth(5,900);
	m_gridMotor.SetColWidth(6,900);
	m_gridMotor.SetColWidth(7,900);
	m_gridMotor.SetColWidth(8,900);


	m_gridMotor.SetTextMatrix(0, 1, "현재 위치");
	m_gridMotor.SetTextMatrix(0, 2, MotorPosName[Loading_Pos]);
	m_gridMotor.SetTextMatrix(0, 3, MotorPosName[Align_Pos]);
	m_gridMotor.SetTextMatrix(0, 4, MotorPosName[Bonding_Pos]);
	m_gridMotor.SetTextMatrix(0, 5, "Limit(-)");
	m_gridMotor.SetTextMatrix(0, 6, "HOME");
	m_gridMotor.SetTextMatrix(0, 7, "Limit(+)");
	m_gridMotor.SetTextMatrix(0, 8, "Alram");

	for(int i=Motor_Lens_X; i<=Motor_Lens_Yt; i++)
	{
		m_gridMotor.SetTextMatrix(i+1-Motor_Lens_X, 0, MotorName[i]);
	}

	m_gridMotor.SetRedraw(TRUE);
	m_gridMotor.Refresh();
}


void CCCDMotorDlg::dispMotorStatus()
{
	CString str;
	double	motorPos;

	m_gridMotor.SetRedraw(FALSE);

	for(int i=Motor_Lens_X; i<=Motor_Lens_Yt; i++)
	{
		m_gridMotor.SetRow(i+1-Motor_Lens_X);

		if (i == Motor_Lens_Yt)
			motorPos	= motor.GetCommandPos(i);
		else
			motorPos	= motor.GetEncoderPos(i);	//motor.GetCommandPos(i);

		str.Format("%.03f", motorPos);
		m_gridMotor.SetTextMatrix(i+1-Motor_Lens_X, 1, str);						// 모터 좌표..


		m_gridMotor.SetCol(5);														// (-) 센서
		if(motor.GetNegaSensor(i))					m_gridMotor.SetCellBackColor(GRID_COLOR_RED);
		else										m_gridMotor.SetCellBackColor(0);

		m_gridMotor.SetCol(6);														// HOM 센서
		if(motor.GetHomeSensor(i))					m_gridMotor.SetCellBackColor(GRID_COLOR_GREEN);
		else										m_gridMotor.SetCellBackColor(0);

		m_gridMotor.SetCol(7);														// (+) 센서
		if(motor.GetPosiSensor(i))					m_gridMotor.SetCellBackColor(GRID_COLOR_RED);
		else										m_gridMotor.SetCellBackColor(0);

		m_gridMotor.SetCol(8);														// Servo Alarm
		if(motor.GetAmpFault(i))					m_gridMotor.SetCellBackColor(GRID_COLOR_RED);
		else										m_gridMotor.SetCellBackColor(0);
	}

	m_gridMotor.SetRedraw(TRUE); 
	m_gridMotor.Refresh();
}


void CCCDMotorDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent==CCR_MOTOR_TIMER)
	{
		if (!timerRunFlag)
		{
			timerRunFlag = true;

			dispMotorStatus();

			timerRunFlag = false;
		}
		// JOG 이동 + 방향
		if(JogPlusflag == true && OLD_JogPlusflag == false)
			motor.JogMove(m_iSelMotor, sysData.fMotorSpeed[m_iSelMotor] * sysData.fMotorResol[m_iSelMotor] * m_fMotorJogSpeed);
		else if(JogPlusflag == false && OLD_JogPlusflag == true)
			motor.JogStop(m_iSelMotor);
		OLD_JogPlusflag = JogPlusflag;


		// JOG 이동 - 방향
		if(JogMinusflag == true && OLD_JogMinusflag == false)
			motor.JogMove(m_iSelMotor, -sysData.fMotorSpeed[m_iSelMotor] * sysData.fMotorResol[m_iSelMotor] * m_fMotorJogSpeed);
		else if(JogMinusflag== false && OLD_JogMinusflag == true)
			motor.JogStop(m_iSelMotor);
		OLD_JogMinusflag = JogMinusflag;
	}


	CDialogEx::OnTimer(nIDEvent);
}

void CCCDMotorDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

 	if (bShow)
 	{
//		Dio.setLedLight(0);

		dispData();

		changeMotorNo(Motor_Lens_X);

 		timerRunFlag = false;
 
 		SetTimer(CCR_MOTOR_TIMER, 200, NULL);
 	}
	else
	{
		KillTimer(CCR_MOTOR_TIMER);
	}
}

void CCCDMotorDlg::changeMotorNo(int motorNo)
{
	if(m_iSelMotor==motorNo)
		return;

	if(motorNo<Motor_Lens_X || motorNo>Motor_Lens_Yt)
		return;

	m_gridMotor.SetRedraw(FALSE);

	m_gridMotor.SetRow(m_iSelMotor+1-Motor_Lens_X);
	m_gridMotor.SetCol(0);
	m_gridMotor.SetCellBackColor(0);
	m_gridMotor.SetCol(1);
	m_gridMotor.SetCellBackColor(0);
	m_gridMotor.SetCol(2);
	m_gridMotor.SetCellBackColor(0);
	m_gridMotor.SetCol(3);
	m_gridMotor.SetCellBackColor(0);
	m_gridMotor.SetCol(4);
	m_gridMotor.SetCellBackColor(0);


	m_iSelMotor = motorNo;
	m_labelMotorName.SetText(MotorName[m_iSelMotor]);

	m_gridMotor.SetRow(motorNo+1);
	m_gridMotor.SetCol(0);
	m_gridMotor.SetCellBackColor(GRID_COLOR_SELECT);
	m_gridMotor.SetCol(1);
	m_gridMotor.SetCellBackColor(GRID_COLOR_SELECT);
	m_gridMotor.SetCol(2);
	m_gridMotor.SetCellBackColor(GRID_COLOR_SELECT);
	m_gridMotor.SetCol(3);
	m_gridMotor.SetCellBackColor(GRID_COLOR_SELECT);
	m_gridMotor.SetCol(4);
	m_gridMotor.SetCellBackColor(GRID_COLOR_SELECT);

	m_gridMotor.SetRedraw(TRUE);
	m_gridMotor.Refresh();
}


void CCCDMotorDlg::dispData()
{
	double pos;
	CString celData;

	for(int i=Motor_Lens_X; i<=Motor_Lens_Yt; i++)
	{
		for(int index=Loading_Pos; index<=Bonding_Pos; index++)
		{
			if(!getMotorPos(i, index, pos, true))
				continue;

			celData.Format("%.03f", pos);
			m_gridMotor.SetTextMatrix(i+1-Motor_Lens_X, index+1, celData);
		}
	}
}

void CCCDMotorDlg::OnBnClickedButtonMotorSave()
{
	CString cellStr;

	m_gridMotor.SetRedraw(FALSE);

	for(int i=Motor_Lens_X;i<=Motor_Lens_Yt;i++)
	{
		for(int index=1;index<4;index++)			// 공급 위치, Align 위치, Bonding 위치
		{
			cellStr = m_gridMotor.GetTextMatrix(i+1-Motor_Lens_X, index+1);
			model.axis[i].pos[index] = atof(cellStr);
		}
	}

	m_gridMotor.SetRedraw(TRUE);
	m_gridMotor.Refresh();

	model.Save();
}


BEGIN_EVENTSINK_MAP(CCCDMotorDlg, CDialogEx)
	ON_EVENT(CCCDMotorDlg, IDC_MSFLEXGRID_MOTOR, DISPID_DBLCLICK, CCCDMotorDlg::DblClickMsflexgridMotor, VTS_NONE)
END_EVENTSINK_MAP()


void CCCDMotorDlg::DblClickMsflexgridMotor()
{
	int col = m_gridMotor.GetMouseCol();
	int row = m_gridMotor.GetMouseRow();

	if(row<1)
		return;

	double pos;

	int index = 1;

	if(!getMotorPos(row-1, index, pos, false))
		return;

	if(col==0)
	{
		changeMotorNo(row-1);
	}
	else if(col>=2 && col<=4)
	{
		CString tmpStr;
		tmpStr.Format("현재 위치를 [ %s ] 값으로 입력 하시겠습니까?", MotorPosName[col-1]);

		if(askMsg(tmpStr.GetBuffer(99)))
		{
			tmpStr = m_gridMotor.GetTextMatrix(row, 1);
			m_gridMotor.SetTextMatrix(row, col, tmpStr);
		}
	}
}


void CCCDMotorDlg::OnBnClickedButtonMotorWait()
{
	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;
	g_bMovingflag =true;

	motor.Lens_Motor_Move(Wait_Pos);

	g_bMovingflag =false;
}


void CCCDMotorDlg::OnBnClickedButtonMotorSupply()
{
	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;
	g_bMovingflag =true;

	motor.Lens_Motor_Move(Loading_Pos);

	g_bMovingflag =false;
}


void CCCDMotorDlg::OnBnClickedButtonMotorAlign()
{
	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;
	g_bMovingflag =true;

	motor.Lens_Motor_Move(Align_Pos);

	g_bMovingflag =false;
}


void CCCDMotorDlg::OnBnClickedButtonMotorBond()
{
	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;
	g_bMovingflag =true;

	motor.Lens_Motor_Move(Bonding_Pos);

	g_bMovingflag =false;
}


void CCCDMotorDlg::OnBnClickedButtonMotorBond2()
{
	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;
	g_bMovingflag =true;

	motor.Lens_Motor_Move(Bonding_Pos, Task.d_Align_offset_x[CAM1], Task.d_Align_offset_y[CAM1], Task.d_Align_offset_th[CAM1]);

	g_bMovingflag =false;
}


void CCCDMotorDlg::OnBnClickedButtonMotorSpeed()
{
	CheckJogMotorSpeed();
}
void CCCDMotorDlg::CheckJogMotorSpeed()
{
	CString strTemp;
	GetDlgItem(IDC_BUTTON_MOTOR_SPEED)->GetWindowText(strTemp);

	if (strTemp=="LOW")
	{
		m_fMotorJogSpeed = MOTOR_JOG_MID;
		GetDlgItem(IDC_BUTTON_MOTOR_SPEED)->SetWindowText("MEDIUM");
	}
	else if (strTemp=="MEDIUM")
	{
		m_fMotorJogSpeed = MOTOR_JOG_HIGH;
		GetDlgItem(IDC_BUTTON_MOTOR_SPEED)->SetWindowText("HIGH");
	}
	else if (strTemp=="HIGH")
	{
		m_fMotorJogSpeed = MOTOR_JOG_LOW;
		GetDlgItem(IDC_BUTTON_MOTOR_SPEED)->SetWindowText("LOW");
	}
}

void CCCDMotorDlg::OnBnClickedButtonPlusX()
{
	JogPlusflag = true;
}


void CCCDMotorDlg::OnBnClickedButtonMinusX()
{
	JogMinusflag = true;
}

