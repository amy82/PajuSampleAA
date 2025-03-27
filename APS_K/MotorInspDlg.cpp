// MotorInspDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AA Bonder.h"
#include "AA BonderDlg.h"
#include "MotorInspDlg.h"
#include "afxdialogex.h"
#include "DataHandler.h"
#include "Vision.h"
#include "GetNumDlg.h"
#include "LightDlg.h"
#include "DioControl.h"
#include "DelayMsgDlg.h"
#include "KeyPadDlg.h"

#include "MIU/Miu.h"
#include "MIU/ConvertColor.h"
#include "MIU/PixelFormat.h"


extern	MIU_DEVICE		gMIUDevice;

extern	CSystemData		sysData;
extern	CModelData		model;
extern	CVision			vision;

extern	CPasswordData	password;

extern  CTask			Task;
extern	CDioControl		Dio;

extern	bool JogPlusflag;
extern	bool JogMinusflag;
extern  bool g_bMovingflag;

extern  CDelayMsgDlg*	delayDlg;

// CMotorInspDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMotorInspDlg, CDialogEx)

CMotorInspDlg::CMotorInspDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMotorInspDlg::IDD, pParent)
{
	m_bFindTop		=	false;
	m_bFindBottom	=	false;
	m_bFindLeft		=	false;
	m_bFindRight	=	false;
}

CMotorInspDlg::~CMotorInspDlg()
{
}

void CMotorInspDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_LENS, m_iSelCam);
	DDX_Control(pDX, IDC_MSFLEXGRID_MOTOR, m_gridMotor);
	DDX_Control(pDX, IDC_MSFLEXGRID_RESOL, m_gridResol);
	DDX_Check(pDX, IDC_CHECK_RESOLUTION, m_bCalcResol);
	DDX_Control(pDX, IDC_BUTTON_JOG_PLUS, m_JogPlus);
	DDX_Control(pDX, IDC_BUTTON_JOG_MINUS, m_JogMinus);
	DDX_Radio(pDX, IDC_RADIO_MOTOR_SPEED1, m_iMotorSpeed);
	DDX_Control(pDX, IDC_STATIC_MOTORSPEED, m_LabelMotorSpeed);
}


BEGIN_MESSAGE_MAP(CMotorInspDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMotorInspDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMotorInspDlg::OnBnClickedCancel)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_RADIO_LENS, &CMotorInspDlg::OnBnClickedRadioLens)
	ON_BN_CLICKED(IDC_RADIO_PCB2, &CMotorInspDlg::OnBnClickedRadioPcb)
	ON_BN_CLICKED(IDC_RADIO_CCD2, &CMotorInspDlg::OnBnClickedRadioCcd)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_POS_SAVE, &CMotorInspDlg::OnBnClickedButtonMotorPosSave)
	ON_BN_CLICKED(IDC_BUTTON_ALARM_RESET, &CMotorInspDlg::OnBnClickedButtonAlarmReset)
	ON_BN_CLICKED(IDC_BUTTON_JOG_PLUS, &CMotorInspDlg::OnBnClickedButtonJogPlus)
	ON_BN_CLICKED(IDC_BUTTON_JOG_MINUS, &CMotorInspDlg::OnBnClickedButtonJogMinus)
	ON_BN_CLICKED(IDC_BUTTON_ORIGIN_ALL, &CMotorInspDlg::OnBnClickedButtonOriginAll)
	ON_BN_CLICKED(IDC_BUTTON_SERVO_ON_ALL, &CMotorInspDlg::OnBnClickedButtonServoOnAll)
	ON_BN_CLICKED(IDC_BUTTON_SERVO_OFF_ALL, &CMotorInspDlg::OnBnClickedButtonServoOffAll)
	ON_BN_CLICKED(IDC_BUTTON_ALARM_RESET_ALL, &CMotorInspDlg::OnBnClickedButtonAlarmResetAll)
	ON_BN_CLICKED(IDC_BUTTON_STOP_ALL, &CMotorInspDlg::OnBnClickedButtonStopAll)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_ORIGIN, &CMotorInspDlg::OnBnClickedButtonMotorOrigin)
	ON_BN_CLICKED(IDC_BUTTON_SERVO_ON, &CMotorInspDlg::OnBnClickedButtonServoOn)
	ON_BN_CLICKED(IDC_BUTTON_SERBO_OFF, &CMotorInspDlg::OnBnClickedButtonSerboOff)
	ON_BN_CLICKED(IDC_RADIO_MOTOR_SPEED1, &CMotorInspDlg::OnBnClickedRadioMotorSpeed1)
	ON_BN_CLICKED(IDC_RADIO_MOTOR_SPEED2, &CMotorInspDlg::OnBnClickedRadioMotorSpeed2)
	ON_BN_CLICKED(IDC_RADIO_MOTOR_SPEED3, &CMotorInspDlg::OnBnClickedRadioMotorSpeed3)
	ON_BN_CLICKED(IDC_CHECK_RESOLUTION, &CMotorInspDlg::OnBnClickedCheckResolution)
	ON_BN_CLICKED(IDC_BUTTON_RESOLUTION, &CMotorInspDlg::OnBnClickedButtonResolution)
	ON_BN_CLICKED(IDC_BUTTON_JOG_STOP, &CMotorInspDlg::OnBnClickedButtonJogStop)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_Vel_SOFTLIMIT, &CMotorInspDlg::OnBnClickedButtonMotorVelSoftlimit)
	ON_BN_CLICKED(IDC_BUTTON_TEST2, &CMotorInspDlg::OnBnClickedButtonTest2)
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CMotorInspDlg::OnBnClickedButtonTest)	
	ON_STN_CLICKED(IDC_STATIC_MOTORSPEED, &CMotorInspDlg::OnStnClickedStaticMotorspeed)

	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_RADIO_LENS2, &CMotorInspDlg::OnBnClickedRadioLens2)
END_MESSAGE_MAP()


// CMotorInspDlg 메시지 처리기입니다.
BOOL CMotorInspDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	m_iSelCam = 0;
	m_iSelMotor = 1;
	m_iMotorSpeed = 0;
	m_fMotorJogSpeed = MOTOR_JOG_LOW;
	m_iVel_Limit = 1;

	initMotorGrid();
	setInterface();

	changeMotorNo(Motor_PCB_X);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CMotorInspDlg::OnBnClickedOk(){}
void CMotorInspDlg::OnBnClickedCancel(){}

void CMotorInspDlg::setInterface()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	WINDOWPLACEMENT wndpl;
	this->GetWindowPlacement(&wndpl);

	wndpl.rcNormalPosition = pFrame->m_rectCamDispPos2;
	wndpl.rcNormalPosition.top -= SUB_DLG_OFFSET_Y;
	wndpl.rcNormalPosition.bottom = MAIN_DLG_SIZE_Y-5 - 95;
	this->MoveWindow(&wndpl.rcNormalPosition);

	m_JogPlus.SetButtonStyle(0);
	m_JogMinus.SetButtonStyle(0);

	CheckVelLimit();
	MotorVellimitView();

	m_LabelMotorSpeed.SetBkColor(M_COLOR_WHITE);
	m_LabelMotorSpeed.SetText("0.1");
	m_LabelMotorSpeed.Invalidate();
}

void CMotorInspDlg::changeCamera()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)(AfxGetApp()->m_pMainWnd);
	pFrame->setCamDisplay(m_iSelCam,0);

	dispResolDataOnGrid();

	if (m_bCalcResol)
		changeCalcMode();
}


void CMotorInspDlg::OnBnClickedRadioLens()
{
	UpdateData(true);
	changeCamera();
}

void CMotorInspDlg::OnBnClickedRadioPcb()
{
	UpdateData(true);
	changeCamera();
}


void CMotorInspDlg::OnBnClickedRadioCcd()
{
	UpdateData(true);
	changeCamera();
}

void CMotorInspDlg::initMotorGrid()
{
	CString tmpStr;

	m_gridMotor.SetRedraw(FALSE);


	for(int i=0;i<6;i++)
		m_gridMotor.SetColAlignment(i, 4);

	m_gridMotor.SetColWidth(0,1150);
	m_gridMotor.SetColWidth(1,1308);
	m_gridMotor.SetColWidth(2,1308);
	m_gridMotor.SetColWidth(3,1308);
	m_gridMotor.SetColWidth(4,1308);
	m_gridMotor.SetColWidth(5,1308);
	sLangChange.LoadStringA(IDS_STRING383);
	m_gridMotor.SetTextMatrix(1, 0, sLangChange);	//Alarm
	sLangChange.LoadStringA(IDS_STRING753);	//Limit(-)
	m_gridMotor.SetTextMatrix(2, 0, sLangChange);
	sLangChange.LoadStringA(IDS_STRING600);	//HOME
	m_gridMotor.SetTextMatrix(3, 0, sLangChange);
	sLangChange.LoadStringA(IDS_STRING754);	//Limit(+)
	m_gridMotor.SetTextMatrix(4, 0, sLangChange);
	sLangChange.LoadStringA(IDS_STRING1288);	//속도(mm/s)
	m_gridMotor.SetTextMatrix(5, 0, sLangChange);
	sLangChange.LoadStringA(IDS_STRING1140);	//가속도(sec)
	m_gridMotor.SetTextMatrix(6, 0, sLangChange);

	m_gridMotor.SetTextMatrix(7, 0, MotorPosName[0]);
	m_gridMotor.SetTextMatrix(8, 0, MotorPosName[2]);
	m_gridMotor.SetTextMatrix(9, 0, MotorPosName[6]);
	m_gridMotor.SetTextMatrix(10, 0, MotorPosName[8]);
	m_gridMotor.SetTextMatrix(11, 0, MotorPosName[9]);
	m_gridMotor.SetTextMatrix(12, 0, MotorPosName[10]);
	sLangChange.LoadStringA(IDS_STRING1444);	//현재 위치
	m_gridMotor.SetTextMatrix(13, 0, sLangChange);

	//m_gridMotor.SetTextMatrix(2, 3, _T("원점센서"));

	int iIndex;
	for(int i=Motor_PCB_X; i<= Motor_PCB_Z; i++)
	{
		iIndex = i;

		tmpStr.Format("[%d] %s", i, MotorName[i]);
		m_gridMotor.SetTextMatrix(0, iIndex+1, tmpStr);
	}

	m_gridMotor.SetRedraw(TRUE);
	m_gridMotor.Refresh();
}

void CMotorInspDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if(bShow)
	{
		CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

		m_iSelCam = pFrame->m_iCurCamNo = 1;

		changeCamera();
		UpdateData(false);

		dispMotorPos();
		MotorVellimitView();

		dispResolDataOnGrid();

		changeCalcMode();

		timerRunFlag = false;
		SetTimer(MOTOR_TIMER, 200, NULL);

		UpdateData(false);
	}
	else
	{
		CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

		#ifdef ON_LINE_VISION
		vision.clearOverlay();
		vision.drawOverlay();
		#endif

		pFrame->m_bMeasureDist = FALSE;
		pFrame->UpdateData(false);

		m_bCalcResol = false;

		KillTimer(MOTOR_TIMER);
	}
}




void CMotorInspDlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent==MOTOR_TIMER)
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
			motor.JogMove(m_iSelMotor, -sysData.fMotorSpeed[m_iSelMotor] * sysData.fMotorResol[m_iSelMotor]  * m_fMotorJogSpeed);
		else if(JogMinusflag== false && OLD_JogMinusflag == true)
			motor.JogStop(m_iSelMotor);
		OLD_JogMinusflag = JogMinusflag;
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CMotorInspDlg::dispMotorStatus()
{
	CString str;
	char sLog[100];
	double	motorPos;


	m_gridMotor.SetRedraw(FALSE);
	int iIndex;

	for(int i=Motor_PCB_X; i<=Motor_PCB_Z; i++)
	{
		iIndex = i;

		m_gridMotor.SetCol(iIndex+1);													// 모터 좌표..
		if( (i==Motor_Lens_Xt) || (i == Motor_PCB_Xt) || (i == Motor_PCB_Yt) )	//스태핑 모터
			motorPos	= motor.GetCommandPos_Disp(i);
		else
			motorPos	= motor.GetEncoderPos_Disp(i);


		str.Format("%.03f", motorPos);
		m_gridMotor.SetTextMatrix(13, iIndex+1, str);


		m_gridMotor.SetRow(1);														// Servo Alarm
		if ( motor.GetAmpFault(i) )
		{
			m_gridMotor.SetCellBackColor(GRID_COLOR_RED);

			if(!delayDlg->IsWindowVisible())
			{
				sTempLang.LoadStringA(IDS_STRING152);
				sLangChange.Format(sTempLang, MotorName[i]);
 				_stprintf_s(sLog, sLangChange);
				delayMsg(sLog,3000,M_COLOR_RED);
			}
		}
		else
		{
			m_gridMotor.SetCellBackColor(0);
		}


		m_gridMotor.SetRow(2);														// (-) 센서
		if ( motor.GetNegaSensor(i) )
		{
			m_gridMotor.SetCellBackColor(GRID_COLOR_RED);

			if(!delayDlg->IsWindowVisible())
			{
				sTempLang.LoadStringA(IDS_STRING150);
				sLangChange.Format(sTempLang, MotorName[i]);
 				_stprintf_s(sLog, sLangChange);
				delayMsg(sLog, 3000, M_COLOR_RED);
			}
		}
		else
		{
			m_gridMotor.SetCellBackColor(0);
		}


		m_gridMotor.SetRow(3);														// HOM 센서
		if( motor.GetHomeSensor(i) )
			m_gridMotor.SetCellBackColor(GRID_COLOR_GREEN);
		else
			m_gridMotor.SetCellBackColor(0);


		m_gridMotor.SetRow(4);														// (+) 센서
		if ( motor.GetPosiSensor(i) )
		{
			m_gridMotor.SetCellBackColor(GRID_COLOR_RED);
			sTempLang.LoadStringA(IDS_STRING151);
			sLangChange.Format(sTempLang, MotorName[i]);
 			_stprintf_s(sLog, sLangChange);
			if(!delayDlg->IsWindowVisible())				delayMsg(sLog,3000,M_COLOR_RED);
		}
		else
		{
			m_gridMotor.SetCellBackColor(0);
		}
	}

	m_gridMotor.SetRedraw(TRUE); 
	m_gridMotor.Refresh();
}



void CMotorInspDlg::OnBnClickedButtonOriginAll()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	if(Task.AutoFlag == 2)
	{
		sLangChange.LoadStringA(IDS_STRING1468);
		delayMsg(sLangChange, 2000, M_COLOR_RED);// 일시 정지 중 사용 불가
		return;
	}


	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	CString sTemp;

	/* 이동중이면 Return */
	if(g_bMovingflag)
	{
		sLangChange.LoadStringA(IDS_STRING1394);	//전체 원점 복귀 실패 - 모터 이동 중
		sTemp.Format(sLangChange);
		pFrame->putListLog(sTemp);
		return;
	}
	g_bMovingflag =true;

	if (!m_bCalcResol)
	{
		sLangChange.LoadStringA(IDS_STRING1391);	//전체 원점 복귀 동작을 실행 하시겠습니까?
		if (askMsg(sLangChange))
		{
			LightControl.ctrlLedVolume(LIGHT_CHART_L, model.m_iLedValue[LEDDATA_CHART_L]);
			LightControl.ctrlLedVolume(LIGHT_CHART_R, model.m_iLedValue[LEDDATA_CHART_R]);
			LightControl.ctrlLedVolume(LIGHT_CHART_U1, model.m_iLedValue[LEDDATA_CHART_U1]);
			LightControl.ctrlLedVolume(LIGHT_CHART_U2, model.m_iLedValue[LEDDATA_CHART_U2]);
			LightControl.ctrlLedVolume(LIGHT_CHART_U3, model.m_iLedValue[LEDDATA_CHART_U3]);
			sLangChange.LoadStringA(IDS_STRING1392);	//전체 원점 복귀 수행합니다
			delayMsg(sLangChange, 50000, M_COLOR_DARK_GREEN);
			sTemp.Format(sLangChange);
			pFrame->putListLog(sTemp);

			if(motor.HomeProcessAll())
			{
				sLangChange.LoadStringA(IDS_STRING1387);
				sTemp.Format(sLangChange);
			}
			else
			{
				sLangChange.LoadStringA(IDS_STRING1386);	//전체 모터 원점 복귀 실패.
				sTemp.Format(sLangChange);
			}
			
			delayMsg(sTemp.GetBuffer(99), 50000, M_COLOR_GREEN);
			pFrame->putListLog(sTemp);
		}
	}
	else
	{/* TOP 찾기 */
		getMarkAndMotor(0);
	}

	g_bMovingflag =false;
}

void CMotorInspDlg::OnBnClickedButtonServoOnAll()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	if(Task.AutoFlag == 2)
	{
		sLangChange.LoadStringA(IDS_STRING1468);
		delayMsg(sLangChange, 2000, M_COLOR_RED);// 일시 정지 중 사용 불가
		return;
	}


	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	CString sTemp;

	/* 이동중이면 Return */
	if(g_bMovingflag)
	{
		sLangChange.LoadStringA(IDS_STRING1394);	//전체 원점 복귀 실패 - 모터 이동 중
		sTemp.Format(sLangChange);
		pFrame->putListLog(sTemp);
		return;
	}
	g_bMovingflag =true;


	if (!m_bCalcResol)
	{
		sLangChange.LoadStringA(IDS_STRING1384);	//전체 Servo On 하시겠습니까?
		if(askMsg(sLangChange))
		{
			TCHAR dispStr[100];
			sLangChange.LoadStringA(IDS_STRING1474);	//모터를 전체 Servo ON 합니다.
			_stprintf_s(dispStr, sLangChange);
			delayMsg(dispStr, 5000, M_COLOR_GREEN);

			if(!motor.AmpEnableAll())
			{
				sLangChange.LoadStringA(IDS_STRING1475);	//Servo On 동작 이상
				errMsg2(Task.AutoFlag, sLangChange);
			}
		}
	}
	else
	{/* BOTTOM 찾기 */
		getMarkAndMotor(1);
	}

	g_bMovingflag =false;
}

void CMotorInspDlg::OnBnClickedButtonServoOffAll()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	if(Task.AutoFlag == 2)
	{
		sLangChange.LoadStringA(IDS_STRING1468);
		delayMsg(sLangChange, 2000, M_COLOR_RED);// 일시 정지 중 사용 불가
		return;
	}


	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;
	g_bMovingflag =true;

	if (!m_bCalcResol)
	{
		if(askMsg("All Servo Off ?"))
		{
			char dispStr[100];
			sprintf_s(dispStr, "All Motor Servo OFF");
			delayMsg(dispStr, 5000, M_COLOR_GREEN);

			if(!motor.AmpDisableAll())
			{
				errMsg2(Task.AutoFlag, "Servo Off Move Error");
			}
		}
	}
	else
	{/* LEFT 찾기 */
		getMarkAndMotor(2);
	}

	g_bMovingflag =false;
}

void CMotorInspDlg::OnBnClickedButtonStopAll()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	if(Task.AutoFlag == 2)
	{
		sLangChange.LoadStringA(IDS_STRING1468);
		delayMsg(sLangChange, 2000, M_COLOR_RED);// 일시 정지 중 사용 불가
		return;
	}


	if (!m_bCalcResol)
	{
		char dispStr[100];
		sprintf_s(dispStr, "All Motor Servo OFF");
		delayMsg(dispStr, 5000, M_COLOR_GREEN);

		if(!motor.StopAxisAll())
		{
			sLangChange.LoadStringA(IDS_STRING1242);	//모터 정지 동작 시간 초과 [1sec]
			errMsg2(Task.AutoFlag, sLangChange);
		}
	}
	else
	{/* RIGHT 찾기 */
		getMarkAndMotor(3);
	}
}


void CMotorInspDlg::OnBnClickedButtonAlarmResetAll()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	if(Task.AutoFlag == 2)
	{
		sLangChange.LoadStringA(IDS_STRING1468);
		delayMsg(sLangChange, 2000, M_COLOR_RED);// 일시 정지 중 사용 불가
		return;
	}


	if (!m_bCalcResol)
	{
		sLangChange.LoadStringA(IDS_STRING1385);	//전체 모터 Alarm Reset 하시겠습니까?
		if(!askMsg(sLangChange))
			return;

		TCHAR dispStr[100];
		sLangChange.LoadStringA(IDS_STRING1222);	//모터 Drive의 Alarm을 해제 합니다.
		_stprintf_s(dispStr, sLangChange);
		delayMsg(dispStr, 5000, M_COLOR_GREEN);

		if(!motor.AmpFaultResetAll())
		{
			sLangChange.LoadStringA(IDS_STRING392);
			errMsg2(Task.AutoFlag, sLangChange);	//Amp Fault가 정상적으로 Reset되지 않았습니다
		}
	}
	else
	{/* 분해능 저장 */
		//if( m_iSelCam >= CAM2 )
		//{
		//	sLangChange.LoadStringA(IDS_STRING430);
		//	delayMsg(sLangChange, 2000, M_COLOR_RED);	//calibration 정보는 CAM1,2번만 가능합니다.
		//	return;		
		//}

		bool passFlag = password.m_bFlag;

		if(passFlag == false)
		{
			CString strTemp;
			CKeyPadDlg keyDlg;

			sLangChange.LoadStringA(IDS_STRING891);
		keyDlg.m_strKeyPad = sLangChange;	//"Password를 입력하세요."

			if (keyDlg.DoModal()==IDOK)
			{
				strTemp = keyDlg.GetstrKeypad();

				passFlag = strTemp.CompareNoCase(password.m_szPassword) ? false : true;
			}
			else
			{
				return;
			}
		}


		if(passFlag)
		{
			password.m_bFlag = true;
		}
		else
		{
			sLangChange.LoadStringA(IDS_STRING892);
		errMsg2(Task.AutoFlag, sLangChange);	//"Password를 잘 못 입력했습니다."
			return;
		}


		getResolDataOnGrid();
		sysData.Save();
		sysData.Load();
	}
}


void CMotorInspDlg::getResolDataOnGrid()
{
	CString sTemp;

	sTemp = m_gridResol.GetTextMatrix(1, 1);
	sysData.dCamResol[m_iSelCam].x = atof(sTemp);
	sTemp = m_gridResol.GetTextMatrix(1, 2);
	sysData.dCamResol[m_iSelCam].y = atof(sTemp);
	sTemp = m_gridResol.GetTextMatrix(1, 3);
	sysData.dCamAngle[m_iSelCam].x = atof(sTemp);
	sTemp = m_gridResol.GetTextMatrix(1, 4);
	sysData.dCamAngle[m_iSelCam].y = atof(sTemp);
}


void CMotorInspDlg::OnBnClickedButtonMotorOrigin()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	if(Task.AutoFlag == 2)
	{
		sLangChange.LoadStringA(IDS_STRING1468);
		delayMsg(sLangChange, 2000, M_COLOR_RED);// 일시 정지 중 사용 불가
		return;
	}


	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	char dispStr[100];
	
	/* 이동중이면 Return */
	if(g_bMovingflag)
	{
		sLangChange.LoadStringA(IDS_STRING1473);	//%s 모터 원점 복귀 실패 - 모터 이동 중
		_stprintf_s(dispStr, sLangChange, MotorName[m_iSelMotor]);
		pFrame->putListLog(dispStr);

		return;
	}


	CString tmpStr;
	sLangChange.LoadStringA(IDS_STRING1472);	//[%s 모터] 원점 복귀 하시겠습니까?
	tmpStr.Format(sLangChange, MotorName[m_iSelMotor]);

	if(!askMsg(tmpStr.GetBuffer(99)))
	{
		return;
	}

	g_bMovingflag =true;

	sTempLang.LoadStringA(IDS_STRING113);
	sLangChange.Format(sTempLang, MotorName[m_iSelMotor]);
	_stprintf_s(dispStr, sLangChange);
	delayMsg(dispStr, 2000, M_COLOR_GREEN);
	sTempLang.LoadStringA(IDS_STRING113);
	sLangChange.Format(sTempLang, MotorName[m_iSelMotor]);
	_stprintf_s(dispStr, sLangChange);
	pFrame->putListLog(dispStr);


	motor.HomeProcess(m_iSelMotor);
	

	sprintf_s(dispStr, "%s Motor HomeSeneor Complete", MotorName[m_iSelMotor]);
	pFrame->putListLog(dispStr);

	g_bMovingflag =false;
}

void CMotorInspDlg::OnBnClickedButtonServoOn()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	if(Task.AutoFlag == 2)
	{
		sLangChange.LoadStringA(IDS_STRING1468);
		delayMsg(sLangChange, 2000, M_COLOR_RED);// 일시 정지 중 사용 불가
		return;
	}


	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;
	sLangChange.LoadStringA(IDS_STRING1283);	//선택 모터 Servo On 하시겠습니까?
	if(!askMsg(sLangChange))
		return;

	g_bMovingflag =true;

	TCHAR dispStr[100];
	sTempLang.LoadStringA(IDS_STRING112);
	sLangChange.Format(sTempLang, MotorName[m_iSelMotor]);
	_stprintf_s(dispStr, sLangChange);
	delayMsg(dispStr, 5000, M_COLOR_GREEN);

	if(!motor.AmpEnable(m_iSelMotor))
	{
		sTempLang.LoadStringA(IDS_STRING111);
		sLangChange.Format(sTempLang, MotorName[m_iSelMotor]);
		_stprintf_s(dispStr, sLangChange);
		errMsg2(Task.AutoFlag, dispStr);
	}

	g_bMovingflag =false;
}

void CMotorInspDlg::OnBnClickedButtonSerboOff()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	if(Task.AutoFlag == 2)
	{
		sLangChange.LoadStringA(IDS_STRING1468);
		delayMsg(sLangChange, 2000, M_COLOR_RED);// 일시 정지 중 사용 불가
		return;
	}


	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;

	sLangChange.LoadStringA(IDS_STRING1282);	//선택 모터 Servo Off 하시겠습니까?
	if(!askMsg(sLangChange))
		return;

	g_bMovingflag =true;

	char dispStr[100];
	sprintf_s(dispStr, "%s Motor Servo Off.", MotorName[m_iSelMotor]);
	delayMsg(dispStr, 5000, M_COLOR_GREEN);

	if(!motor.AmpDisable(m_iSelMotor))
	{
		sprintf_s(dispStr, "%s Motor Servo Off Move Error.", MotorName[m_iSelMotor]);
		errMsg2(Task.AutoFlag, dispStr);
	}

	g_bMovingflag =false;
}

void CMotorInspDlg::OnBnClickedButtonAlarmReset()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	if(Task.AutoFlag == 2)
	{
		sLangChange.LoadStringA(IDS_STRING1468);
		delayMsg(sLangChange, 2000, M_COLOR_RED);// 일시 정지 중 사용 불가
		return;
	}


	if(!askMsg("Select Motor Alarm Reset?"))
		return;

	TCHAR dispStr[100];
	sLangChange.LoadStringA(IDS_STRING1222);	//모터 Drive의 Alarm을 해제 합니다.
	_stprintf_s(dispStr, _T("%s ") + sLangChange, MotorName[m_iSelMotor]);

	delayMsg(dispStr, 5000, M_COLOR_GREEN);

	if(!motor.AmpFaultReset(m_iSelMotor))
	{
		sLangChange.LoadStringA(IDS_STRING1470);	//%s 모터의 Amp Fault가 정상적으로 Reset 되지 않았습니다
		_stprintf_s(dispStr, sLangChange, MotorName[m_iSelMotor]);
		errMsg2(Task.AutoFlag, dispStr);
	}
}


void CMotorInspDlg::OnBnClickedRadioMotorSpeed1()
{
	m_fMotorJogSpeed = MOTOR_JOG_LOW;
	UpdateData(true);
}


void CMotorInspDlg::OnBnClickedRadioMotorSpeed2()
{
	m_fMotorJogSpeed = MOTOR_JOG_MID;
	UpdateData(true);
}


void CMotorInspDlg::OnBnClickedRadioMotorSpeed3()
{
	m_fMotorJogSpeed = MOTOR_JOG_HIGH;
	UpdateData(true);
}


void CMotorInspDlg::OnBnClickedButtonJogPlus()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	if(Task.AutoFlag == 2)
	{
		sLangChange.LoadStringA(IDS_STRING1468);
		delayMsg(sLangChange, 2000, M_COLOR_RED);// 일시 정지 중 사용 불가
		return;
	}

	JogPlusflag = true;
}


void CMotorInspDlg::OnBnClickedButtonJogMinus()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	if(Task.AutoFlag == 2)
	{
		sLangChange.LoadStringA(IDS_STRING1468);
		delayMsg(sLangChange, 2000, M_COLOR_RED);// 일시 정지 중 사용 불가
		return;
	}


	JogMinusflag = true;
}

void CMotorInspDlg::OnBnClickedButtonJogStop()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	if(Task.AutoFlag == 2)
	{
		sLangChange.LoadStringA(IDS_STRING1468);
		delayMsg(sLangChange, 2000, M_COLOR_RED);// 일시 정지 중 사용 불가
		return;
	}

	motor.JogStop(m_iSelMotor);
}

void CMotorInspDlg::OnBnClickedButtonMotorPosSave()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	bool passFlag = password.m_bFlag;

	if(passFlag == false)
	{
		CString strTemp;
		CKeyPadDlg keyDlg;

		sLangChange.LoadStringA(IDS_STRING891);
		keyDlg.m_strKeyPad = sLangChange;	//"Password를 입력하세요."

		if (keyDlg.DoModal()==IDOK)
		{
			strTemp = keyDlg.GetstrKeypad();
			
			passFlag = strTemp.CompareNoCase(password.m_szPassword) ? false : true;
		}
		else
		{
			return;
		}
	}

	if(passFlag)
	{
		password.m_bFlag = true;
	}
	else
	{
		sLangChange.LoadStringA(IDS_STRING892);
		errMsg2(Task.AutoFlag, sLangChange);	//"Password를 잘 못 입력했습니다."
		return;
	}
	

	CString cellStr;

	m_gridMotor.SetRedraw(FALSE);

	sLangChange.LoadStringA(IDS_STRING1435);	//파라미터를 저장 하시겠습니까?
	cellStr.Format(sLangChange);

	if( !askMsg(cellStr.GetBuffer(99)) )
	{
		return;
	}

	changeMotorNo(m_iSelMotor);

	int iIndex;
	for(int i=Motor_PCB_X;i<=Motor_PCB_Z;i++)
	{
		iIndex = i;

		if(m_iVel_Limit == 1)
		{
			cellStr = m_gridMotor.GetTextMatrix(5, iIndex+1);
			model.axis[i].m_dLimit_OK = (float)atof(cellStr);

			cellStr = m_gridMotor.GetTextMatrix(6, iIndex+1);
			model.axis[i].m_dLimit_Err = (float)atof(cellStr);
		}
		else
		{
			cellStr = m_gridMotor.GetTextMatrix(5, iIndex+1);
			sysData.fMotorSpeed[i] = (float)atof(cellStr);

			cellStr = m_gridMotor.GetTextMatrix(6, iIndex+1);
			sysData.fMotorAccTime[i] = (float)atof(cellStr);
		}

		cellStr = m_gridMotor.GetTextMatrix(7, iIndex+1);
		model.axis[i].pos[Wait_Pos] = (atof(cellStr) + sysData.dDataset[i]);

		cellStr = m_gridMotor.GetTextMatrix(8, iIndex+1);
		model.axis[i].pos[Holder_Pos] = (atof(cellStr) + sysData.dDataset[i]);

		cellStr = m_gridMotor.GetTextMatrix(9, iIndex+1);
		model.axis[i].pos[Laser_Out_Pos] = (atof(cellStr) + sysData.dDataset[i]);

		cellStr = m_gridMotor.GetTextMatrix(10, iIndex+1);
		model.axis[i].pos[Bonding_Pos] = (atof(cellStr) + sysData.dDataset[i]);

		cellStr = m_gridMotor.GetTextMatrix(11, iIndex+1);
		model.axis[i].pos[Dark_Pos] = (atof(cellStr) + sysData.dDataset[i]);

		cellStr = m_gridMotor.GetTextMatrix(12, iIndex+1);
		model.axis[i].pos[Defect_Pos] = (atof(cellStr) + sysData.dDataset[i]);

	}

	model.Save();
	sysData.Save();

	m_gridMotor.SetRedraw(TRUE);
	m_gridMotor.Refresh();   
	sLangChange.LoadStringA(IDS_STRING1434);
	LogSave(sLangChange);
}


void CMotorInspDlg::changeMotorNo(int motorNo)
{
	m_gridMotor.SetRedraw(FALSE);
	int j = m_iSelMotor + 1;
	m_gridMotor.SetCol(m_iSelMotor + 1);
	for(int i=5; i<=13; i++)
	{
		m_gridMotor.SetRow(i);
		m_gridMotor.SetCellBackColor(0);
	}


	m_iSelMotor = motorNo;

	m_gridMotor.SetCol(motorNo+1);
	for(int i=5; i<=13; i++)
	{
		m_gridMotor.SetRow(i);
		m_gridMotor.SetCellBackColor(GRID_COLOR_SELECT);
	}

	m_gridMotor.SetRedraw(TRUE);
	m_gridMotor.Refresh();
}


BEGIN_EVENTSINK_MAP(CMotorInspDlg, CDialogEx)
	ON_EVENT(CMotorInspDlg, IDC_MSFLEXGRID_MOTOR, DISPID_DBLCLICK, CMotorInspDlg::DblClickMsflexgridMotor, VTS_NONE)
	ON_EVENT(CMotorInspDlg, IDC_MSFLEXGRID_RESOL, DISPID_DBLCLICK, CMotorInspDlg::DblClickMsflexgridResol, VTS_NONE)
END_EVENTSINK_MAP()


void CMotorInspDlg::DblClickMsflexgridMotor()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	int col = m_gridMotor.GetMouseCol();
	int row = m_gridMotor.GetMouseRow();



	if(col<0 || row<0)										//JJH.	수정
		return;

	CString celData;

	int curCol = col;
	if(col == 0)
		curCol = m_iSelMotor + 1;


	changeMotorNo(curCol-1);

	if(col == 0)														//JJH.	수정
	{
		if(row>=7 && row<13)
		{
			m_gridMotor.SetRow(row);
			m_gridMotor.SetCol(curCol);
			m_gridMotor.SetCellBackColor(GRID_COLOR_RED);

			celData = m_gridMotor.GetTextMatrix(13, curCol);
			m_gridMotor.SetTextMatrix(row, curCol, celData);
		}
	}
	else
	{
		if(row>=5 && row<13)
		{
			m_gridMotor.SetRow(row);
			m_gridMotor.SetCol(col);
			m_gridMotor.SetCellBackColor(GRID_COLOR_RED);


			celData = m_gridMotor.GetTextMatrix(row, col);
			CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);

			if(dlg.DoModal() == IDOK)
			{
				CString curStr = dlg.GetstrNum();
				double fVal = atof(curStr);

				if(row==5)
				{
					if(m_iVel_Limit ==0)
					{
						if(fVal<1)				fVal = 1;
						if(fVal>500)			fVal = 500;
					}
					else
					{
						if(fVal<0.03)			fVal = 0.01;
						if(fVal>0.5)			fVal = 0.5;
					}
				}
				else if(row==6)
				{
					if(m_iVel_Limit ==0)
					{
						if(fVal<0.01)			fVal = 0.01;
						if(fVal>1)				fVal = 1;
					}
					else
					{
						if(fVal<1)				fVal = 1;
						if(fVal>5)				fVal = 5;
					}
				}

				celData.Format("%.03f", fVal);
				m_gridMotor.SetTextMatrix(row, col, celData);
			}
			else
			{
				m_gridMotor.SetRow(row);
				m_gridMotor.SetCol(col);
				m_gridMotor.SetCellBackColor(GRID_COLOR_SELECT);
			}
		}
	}
}

void CMotorInspDlg::dispResolDataOnGrid()
{
	CString sTemp;

	sTemp = "PCB";


	m_gridResol.SetColAlignment(0, 4);
	m_gridResol.SetColAlignment(1, 4);
	m_gridResol.SetColAlignment(2, 4);
	m_gridResol.SetColAlignment(3, 4);
	m_gridResol.SetColAlignment(4, 4);

	m_gridResol.SetColWidth(0, 550);
	m_gridResol.SetColWidth(1, 1000);
	m_gridResol.SetColWidth(2, 1000);
	m_gridResol.SetColWidth(3, 1000);
	m_gridResol.SetColWidth(4, 1000);

	m_gridResol.SetTextMatrix(0, 1, "RESOL X");
	m_gridResol.SetTextMatrix(0, 2, "RESOL Y");
	sLangChange.LoadStringA(IDS_STRING395);
	m_gridResol.SetTextMatrix(0, 3, sLangChange);
	sLangChange.LoadStringA(IDS_STRING396);
	m_gridResol.SetTextMatrix(0, 4, sLangChange);

	m_gridResol.SetTextMatrix(1, 0, sTemp);

	sTemp.Format("%.4lf", sysData.dCamResol[m_iSelCam].x);
	m_gridResol.SetTextMatrix(1, 1, sTemp);
	sTemp.Format("%.4lf", sysData.dCamResol[m_iSelCam].y);
	m_gridResol.SetTextMatrix(1, 2, sTemp);
	sTemp.Format("%.4lf", sysData.dCamAngle[m_iSelCam].x);
	m_gridResol.SetTextMatrix(1, 3, sTemp);
	sTemp.Format("%.4lf", sysData.dCamAngle[m_iSelCam].y);
	m_gridResol.SetTextMatrix(1, 4, sTemp);
}


void CMotorInspDlg::changeCalcMode()
{
	m_bFindTop		=	false;
	m_bFindBottom	=	false;
	m_bFindLeft		=	false;
	m_bFindRight	=	false;

	GetDlgItem(IDC_BUTTON_RESOLUTION)->EnableWindow(FALSE);

	if (m_bCalcResol)
	{
		GetDlgItem(IDC_MSFLEXGRID_RESOL)->ShowWindow(true);
		GetDlgItem(IDC_BUTTON_RESOLUTION)->ShowWindow(true);

		sLangChange.LoadStringA(IDS_STRING1476);		//분해능 <<
		SetDlgItemText(IDC_CHECK_RESOLUTION, sLangChange);

		sLangChange.LoadStringA(IDS_STRING1101);		
		SetDlgItemText(IDC_BUTTON_ORIGIN_ALL, sLangChange);			//Top")
		sLangChange.LoadStringA(IDS_STRING422);						//
		SetDlgItemText(IDC_BUTTON_SERVO_ON_ALL, sLangChange);		//Bottom
		sLangChange.LoadStringA(IDS_STRING646);						//
		SetDlgItemText(IDC_BUTTON_SERVO_OFF_ALL, sLangChange);		//Left"
		sLangChange.LoadStringA(IDS_STRING1043);						//
		SetDlgItemText(IDC_BUTTON_STOP_ALL, sLangChange);			//Right
		sLangChange.LoadStringA(IDS_STRING1382);						//저장
		SetDlgItemText(IDC_BUTTON_ALARM_RESET_ALL, sLangChange);

		#ifdef ON_LINE_VISION
		vision.clearOverlay(m_iSelCam);
		drawResolBackGround();
		vision.drawOverlay(m_iSelCam);
		#endif
	}
	else
	{
		GetDlgItem(IDC_MSFLEXGRID_RESOL)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_RESOLUTION)->ShowWindow(false);

		sLangChange.LoadStringA(IDS_STRING1265);		//분해능 >>
		SetDlgItemText(IDC_CHECK_RESOLUTION, sLangChange);

		sLangChange.LoadStringA(IDS_STRING1390);	//전체 원점 복귀
		SetDlgItemText(IDC_BUTTON_ORIGIN_ALL, sLangChange);
		sLangChange.LoadStringA(IDS_STRING1055);	//Servo On
		SetDlgItemText(IDC_BUTTON_SERVO_ON_ALL, sLangChange);
		sLangChange.LoadStringA(IDS_STRING1054);	//Servo Off
		SetDlgItemText(IDC_BUTTON_SERVO_OFF_ALL, sLangChange);
		sLangChange.LoadStringA(IDS_STRING1241);	//모터 정지
		SetDlgItemText(IDC_BUTTON_STOP_ALL, sLangChange);
		sLangChange.LoadStringA(IDS_STRING388);
		SetDlgItemText(IDC_BUTTON_ALARM_RESET_ALL, sLangChange);

		#ifdef ON_LINE_VISION
		vision.clearOverlay();
		vision.drawOverlay();
		#endif		
	}
}


void CMotorInspDlg::OnBnClickedCheckResolution()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	if(Task.AutoFlag == 2)
	{
		sLangChange.LoadStringA(IDS_STRING1468);
		delayMsg(sLangChange, 2000, M_COLOR_RED);// 일시 정지 중 사용 불가
		return;
	}


	m_bCalcResol = !m_bCalcResol;

	changeCalcMode();
}


void CMotorInspDlg::DblClickMsflexgridResol()
{
	int col = m_gridResol.GetMouseCol();
	int row = m_gridResol.GetMouseRow();

	CString celData = m_gridResol.GetTextMatrix(row, col);


	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		CString curStr = dlg.GetstrNum();

		double dVal = atof(curStr);

		celData.Format("%.4lf", dVal);

		m_gridResol.SetTextMatrix(row, col, celData);
	}
}


void CMotorInspDlg::drawResolBackGround()
{
	CRect rTemp;
	COLORREF color;

	/* TOP */
	if (m_bFindTop)
		color = M_COLOR_GREEN;
	else
		color = M_COLOR_RED;

	rTemp.left		=	(int)(CAM_SIZE_X*0.35 + 0.5);
	rTemp.top		=	5;
	rTemp.right		=	(int)(CAM_SIZE_X*0.65 + 0.5);
	rTemp.bottom	=	(int)(CAM_SIZE_Y*0.35 + 0.5);

	vision.boxlist[m_iSelCam].addList(rTemp, PS_SOLID, color);

	/* BOTTOM */
	if (m_bFindBottom)
		color = M_COLOR_GREEN;
	else
		color = M_COLOR_RED;

	rTemp.left		=	(int)(CAM_SIZE_X*0.35 + 0.5);
	rTemp.top		=	(int)(CAM_SIZE_Y*0.65 + 0.5);
	rTemp.right		=	(int)(CAM_SIZE_X*0.65 + 0.5);
	rTemp.bottom	=	CAM_SIZE_Y - 5;

	vision.boxlist[m_iSelCam].addList(rTemp, PS_SOLID, color);

	/* LEFT */
	if (m_bFindLeft)
		color = M_COLOR_GREEN;
	else
		color = M_COLOR_RED;

	rTemp.left		=	5;
	rTemp.top		=	(int)(CAM_SIZE_Y*0.35 + 0.5);
	rTemp.right		=	(int)(CAM_SIZE_X*0.3 + 0.5);
	rTemp.bottom	=	(int)(CAM_SIZE_Y*0.65 + 0.5);

	vision.boxlist[m_iSelCam].addList(rTemp, PS_SOLID, color);

	/* RIGHT */
	if (m_bFindRight)
		color = M_COLOR_GREEN;
	else
		color = M_COLOR_RED;

	rTemp.left		=	(int)(CAM_SIZE_X*0.7 + 0.5);
	rTemp.top		=	(int)(CAM_SIZE_Y*0.35 + 0.5);
	rTemp.right		=	CAM_SIZE_X-5;
	rTemp.bottom	=	(int)(CAM_SIZE_Y*0.65 + 0.5);

	vision.boxlist[m_iSelCam].addList(rTemp, PS_SOLID, color);
}


void CMotorInspDlg::getMarkAndMotor(int iPos)
{
	int iRtn;
	double dRate, dAngle;
	int iType;

	vision.clearOverlay(m_iSelCam);

	vision.getSnapImage(m_iSelCam);
	vision.setLiveMode(true);

	if( m_iSelCam == 1 )	iType =  PCB_Chip_MARK;
	else					iType =  PCB_Holder_MARK;

#ifdef USE_GEOMETRIC
	iRtn = vision.geometricModelFinder(iPos+1, m_iSelCam, iType, 0,  m_dFindCenter[iPos], dRate, dAngle);
#else
	iRtn = vision.patternMatching(iPos+1, m_iSelCam, iType,  0, m_dFindCenter[iPos], dRate, dAngle);
#endif

	if (iRtn!=FIND_OK)
	{
		sLangChange.LoadStringA(IDS_STRING1216);	//마크 찾기 실패
		::errMsg2(Task.AutoFlag, sLangChange);
		return;
	}

	/* TOP */
	if (iPos==0)
	{
		if (iRtn==FIND_OK)
			m_bFindTop = true;
		else
			m_bFindTop = false;
	}
	/* BOTTOM */
	else if (iPos==1)
	{
		if (iRtn==FIND_OK)
			m_bFindBottom = true;
		else
			m_bFindBottom = false;
	}
	/* LEFT */
	else if (iPos==2)
	{
		if (iRtn==FIND_OK)
			m_bFindLeft = true;
		else
			m_bFindLeft = false;
	}
	/* RIGHT */
	else if (iPos==3)
	{
		if (iRtn==FIND_OK)
			m_bFindRight = true;
		else
			m_bFindRight = false;
	}

	if (m_iSelCam==CAM1 || m_iSelCam==CAM2)
	{
		m_dMotorPos[iPos].x = motor.GetEncoderPos(Motor_PCB_X);	//motor.GetCommandPos(Motor_PCB_X);
		m_dMotorPos[iPos].y = motor.GetEncoderPos(Motor_PCB_Y);	//motor.GetCommandPos(Motor_PCB_Y);
	}
	//else if (m_iSelCam<Cam_Cnt)
	//{
	//	m_dMotorPos[iPos].x = motor.GetEncoderPos(Motor_Lens_X);	//motor.GetCommandPos(Motor_Lens_X);
	//	m_dMotorPos[iPos].y = motor.GetEncoderPos(Motor_Lens_Y);	//motor.GetCommandPos(Motor_Lens_Y);
	//}

	CString sMotorPos;
	sMotorPos.Format("Motor [ %.3lf %.3lf]", m_dMotorPos[iPos].x, m_dMotorPos[iPos].y);
	vision.textlist[m_iSelCam].addList(15, 40, sMotorPos, M_COLOR_YELLOW, 17, 10, "Arial");

	vision.drawResolResult(m_iSelCam, m_iMarkSizeX, m_iMarkSizeY, m_dFindCenter[iPos], iRtn);

	drawResolBackGround();

	vision.drawOverlay(m_iSelCam);

	CAABonderDlg* pFrmae = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	pFrmae->putListLog(sMotorPos);

	if (m_bFindTop && m_bFindBottom && m_bFindLeft && m_bFindRight)
		GetDlgItem(IDC_BUTTON_RESOLUTION)->EnableWindow(TRUE);
}

void CMotorInspDlg::OnBnClickedButtonResolution()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	if(Task.AutoFlag == 2)
	{
		sLangChange.LoadStringA(IDS_STRING1468);
		delayMsg(sLangChange, 2000, M_COLOR_RED);// 일시 정지 중 사용 불가
		return;
	}


	if (m_bFindTop && m_bFindBottom && m_bFindLeft && m_bFindRight)
	{
		m_dTempResol.x	=	fabs(m_dMotorPos[3].x-m_dMotorPos[2].x) / fabs(m_dFindCenter[3].x-m_dFindCenter[2].x);
		m_dTempResol.y	=	fabs(m_dMotorPos[1].y-m_dMotorPos[0].y) / fabs(m_dFindCenter[1].y-m_dFindCenter[0].y);
		m_dTempAngle.x	=	atan((m_dFindCenter[3].y-m_dFindCenter[2].y) / (m_dFindCenter[3].x-m_dFindCenter[2].x));
		m_dTempAngle.y	=	atan((m_dFindCenter[0].x-m_dFindCenter[1].x) / (m_dFindCenter[1].y-m_dFindCenter[0].y));

		m_dTempAngle.x	= m_dTempAngle.x * 180.0/M_PI;
		m_dTempAngle.y	= m_dTempAngle.y * 180.0/M_PI;

		if (!_finite(m_dTempResol.x)		||
			!_finite(m_dTempResol.y)		||
			!_finite(m_dTempAngle.x)		||
			!_finite(m_dTempAngle.y)			)
		{
			sLangChange.LoadStringA(IDS_STRING1157);	//계산 오류 발생.
			::errMsg2(Task.AutoFlag, sLangChange);

			m_bFindTop		=	false;
			m_bFindBottom	=	false;
			m_bFindLeft		=	false;
			m_bFindRight	=	false;

			GetDlgItem(IDC_BUTTON_RESOLUTION)->EnableWindow(FALSE);

			vision.clearOverlay(m_iSelCam);
			drawResolBackGround();
			vision.drawOverlay(m_iSelCam);

			return;
		}

		CString sTemp;

		sTemp.Format("%.4lf", m_dTempResol.x);
		m_gridResol.SetTextMatrix(1, 1, sTemp);
		sTemp.Format("%.4lf", m_dTempResol.y);
		m_gridResol.SetTextMatrix(1, 2, sTemp);
		sTemp.Format("%.4lf", m_dTempAngle.x);
		m_gridResol.SetTextMatrix(1, 3, sTemp);
		sTemp.Format("%.4lf", m_dTempAngle.y);
		m_gridResol.SetTextMatrix(1, 4, sTemp);

		m_bFindTop		=	false;
		m_bFindBottom	=	false;
		m_bFindLeft		=	false;
		m_bFindRight	=	false;

		GetDlgItem(IDC_BUTTON_RESOLUTION)->EnableWindow(FALSE);

		vision.clearOverlay(m_iSelCam);
		drawResolBackGround();
		vision.drawOverlay(m_iSelCam);
	}
}

void CMotorInspDlg::CheckVelLimit()
{
	CString strTemp;
	GetDlgItem(IDC_BUTTON_MOTOR_Vel_SOFTLIMIT)->GetWindowText(strTemp);

	if (m_iVel_Limit ==0)
	{
		m_iVel_Limit = 1;
		sLangChange.LoadStringA(IDS_STRING1262);	//보정값 LIMIT
		GetDlgItem(IDC_BUTTON_MOTOR_Vel_SOFTLIMIT)->SetWindowText(sLangChange);
	}
	else 
	{
		m_iVel_Limit = 0;
		sLangChange.LoadStringA(IDS_STRING1289);	//속도/ 가속도
		GetDlgItem(IDC_BUTTON_MOTOR_Vel_SOFTLIMIT)->SetWindowText(sLangChange);
	}
}


void CMotorInspDlg::OnBnClickedButtonMotorVelSoftlimit()
{
	CheckVelLimit();
	MotorVellimitView();
}

void CMotorInspDlg::MotorVellimitView()
{
	CString strTemp;
	CString temp;
	m_gridMotor.SetRedraw(FALSE);

	int iIndex;
	if(m_iVel_Limit ==1)
	{
		sLangChange.LoadStringA(IDS_STRING879);	//OK Limit"
		m_gridMotor.SetTextMatrix(5, 0, sLangChange);
		sLangChange.LoadStringA(IDS_STRING559);	//ERR Limit
		m_gridMotor.SetTextMatrix(6, 0, sLangChange);

		for(int i=Motor_PCB_X;i<=Motor_PCB_Z;i++)
		{
			iIndex = i;

			temp.Format("%0.3f", model.axis[i].m_dLimit_OK);
			m_gridMotor.SetTextMatrix(5, iIndex+1, temp);

			temp.Format("%0.3f", model.axis[i].m_dLimit_Err);
			m_gridMotor.SetTextMatrix(6, iIndex+1, temp);
		}
	}
	else	// 속도 가속도
	{
		sLangChange.LoadStringA(IDS_STRING1288);	//속도(mm/s)
		m_gridMotor.SetTextMatrix(5, 0, sLangChange);
		sLangChange.LoadStringA(IDS_STRING1140);	//가속도(sec)
		m_gridMotor.SetTextMatrix(6, 0, sLangChange);

		for(int i=Motor_PCB_X;i<=Motor_PCB_Z;i++)
		{
			iIndex = i;

			temp.Format("%0.3f", sysData.fMotorSpeed[i]);
			m_gridMotor.SetTextMatrix(5, iIndex+1, temp);

			temp.Format("%.03f", sysData.fMotorAccTime[i]);
			m_gridMotor.SetTextMatrix(6, iIndex+1, temp);

		}
	}

	m_gridMotor.SetRedraw(TRUE);
	m_gridMotor.Refresh();   
}


void CMotorInspDlg::OnBnClickedButtonTest2()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	if(Task.AutoFlag == 2)
	{
		sLangChange.LoadStringA(IDS_STRING1468);
		delayMsg(sLangChange, 2000, M_COLOR_RED);// 일시 정지 중 사용 불가
		return;
	}


	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;
	g_bMovingflag =true;

	CString temp;
	GetDlgItem(IDC_STATIC_MOTORSPEED)->GetWindowText(temp);
	double pos;
	pos = atof(temp);

	if ( pos > 3)	pos = 3;

	motor.MoveAxis(m_iSelMotor, REL, -pos, 4, 0);				// 4: 조그 이동 속도..

	g_bMovingflag =false;
}


void CMotorInspDlg::OnBnClickedButtonTest()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	if(Task.AutoFlag == 2)
	{
		sLangChange.LoadStringA(IDS_STRING1468);
		delayMsg(sLangChange, 2000, M_COLOR_RED);// 일시 정지 중 사용 불가
		return;
	}


	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;
	g_bMovingflag =true;

	CString temp;
	GetDlgItem(IDC_STATIC_MOTORSPEED)->GetWindowText(temp);
	double pos;
	pos = atof(temp);

	if ( pos < 0)
	{
		sLangChange.LoadStringA(IDS_STRING1340);	//이동 거리 입력 값이 (-) 입니다
		errMsg2(0, sLangChange);
		return;
	}

	if ( pos > 3)	pos = 3;

	motor.MoveAxis(m_iSelMotor, REL, +pos, 4, 0);				// 4: 조그 이동 속도..

	g_bMovingflag =false;
}


bool CMotorInspDlg::registPatMark(int iCamNo, CRect rcBox)
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return false;
	}

	if(Task.AutoFlag == 2)
	{
		sLangChange.LoadStringA(IDS_STRING1468);
		delayMsg(sLangChange, 2000, M_COLOR_RED);// 일시 정지 중 사용 불가
		return false;
	}


	if (vision.getLiveMode())
		vision.getSnapImage(iCamNo);

	int iRealCam = iCamNo;

	m_iMarkSizeX = rcBox.right - rcBox.left;
	m_iMarkSizeY = rcBox.bottom - rcBox.top;

	if (m_iMarkSizeX<=0 || m_iMarkSizeY<=0 || m_iMarkSizeX>=CAM_SIZE_X || m_iMarkSizeY>=CAM_SIZE_Y)
	{
		sLangChange.LoadStringA(IDS_STRING1377);	//잘못된 영역입니다.
		errMsg2(Task.AutoFlag, sLangChange);
		return false;
	}

	if(m_iMarkSizeX < 30 || m_iMarkSizeY < 30)
	{
		sLangChange.LoadStringA(IDS_STRING1205);	//등록 박스 사이즈가 너무 작습니다.
		errMsg2(Task.AutoFlag, sLangChange);
		return false;
	}

	if (vision.PatModel[iCamNo][0])
	{
		MpatFree(vision.PatModel[iCamNo][0]);
		vision.PatModel[iCamNo][0] = M_NULL;
	}

	MpatAllocModel(vision.MilSystem, vision.MilProcImageChild[iRealCam], rcBox.left, rcBox.top, m_iMarkSizeX, m_iMarkSizeY, M_NORMALIZED, &vision.PatModel[iCamNo][0]);

	return true;
}


void CMotorInspDlg::OnStnClickedStaticMotorspeed()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		m_LabelMotorSpeed.SetText(dlg.GetstrNum());
	}
}


void CMotorInspDlg::dispMotorPos()
{
	CString posStr;
	double pos;


	m_gridMotor.SetRedraw(FALSE);

	int iIndex;
	for(int i=Motor_PCB_X;i<=Motor_PCB_Z ;i++)
	{
		iIndex = i;

		getMotorPos(i, Wait_Pos, pos, true);
		posStr.Format("%0.3f", pos);
		m_gridMotor.SetTextMatrix(7, iIndex+1, posStr);

		getMotorPos(i, Holder_Pos, pos, true);
		posStr.Format("%0.3f", pos);
		m_gridMotor.SetTextMatrix(8, iIndex+1, posStr);

		getMotorPos(i, Laser_Out_Pos, pos, true);
		posStr.Format("%0.3f", pos);
		m_gridMotor.SetTextMatrix(9, iIndex+1, posStr);

		getMotorPos(i, Bonding_Pos, pos, true);
		posStr.Format("%0.3f", pos);
		m_gridMotor.SetTextMatrix(10, iIndex+1, posStr);

		getMotorPos(i, Dark_Pos, pos, true);
		posStr.Format("%0.3f", pos);
		m_gridMotor.SetTextMatrix(11, iIndex+1, posStr);

		getMotorPos(i, Defect_Pos, pos, true);
		posStr.Format("%0.3f", pos);
		m_gridMotor.SetTextMatrix(12, iIndex+1, posStr);
	}

	m_gridMotor.SetRedraw(TRUE);
	m_gridMotor.Refresh();  
}



void CMotorInspDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if(!(nFlags & 0x01))
	{
		if(JogMinusflag)
			JogMinusflag = false;

		if(JogPlusflag)
			JogPlusflag = false;
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CMotorInspDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	JogMinusflag = false;
	JogPlusflag = false;

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMotorInspDlg::OnBnClickedRadioLens2()
{
	UpdateData(true);
	changeCamera();
}
