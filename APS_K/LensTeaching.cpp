// MotorDlg.cpp : 구현 파일입니다.
//lens

#include "stdafx.h"
#include "AA Bonder.h"
#include "AA BonderDlg.h"
#include "LensTeaching.h"
#include "afxdialogex.h"
#include "DelayMsgDlg.h"


extern  bool bThreadTaskReadyRun;



// CMotorDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMotorDlg, CDialogEx)

	CMotorDlg::CMotorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMotorDlg::IDD, pParent)
{
	m_bFindTop		=	false;
	m_bFindBottom	=	false;
	m_bFindLeft		=	false;
	m_bFindRight	=	false;
}

CMotorDlg::~CMotorDlg()
{
}

void CMotorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Check(pDX, IDC_CHECK_RESOLUTION, m_bCalcResol);
	DDX_Control(pDX, IDC_BUTTON_JOG_PLUS, m_JogPlus);
	DDX_Control(pDX, IDC_BUTTON_JOG_MINUS, m_JogMinus);
	DDX_Radio(pDX, IDC_RADIO_MOTOR_SPEED1, m_iMotorSpeed);
	DDX_Control(pDX, IDC_BUTTON_GOTO_PCBMOTOR, m_btnMot1);
	DDX_Control(pDX, IDC_BUTTON_GOTO_LENSMOTOR, m_btnMot2);
	DDX_Control(pDX, IDC_BUTTON_GOTO_DISPENCEMOTOR, m_btnMot3);
	DDX_Control(pDX, IDC_STATIC_MOTORSPEED, m_LabelMotorSpeed);
	DDX_Radio(pDX, IDC_RADIO_PCB2, m_iSelCam);
	DDX_Control(pDX, IDC_BUTTON_GOTO_LENSLASERALIGNMOTOR, m_btnMot4);
}


BEGIN_MESSAGE_MAP(CMotorDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMotorDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMotorDlg::OnBnClickedCancel)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_RADIO_LENS, &CMotorDlg::OnBnClickedRadioLens)
	ON_BN_CLICKED(IDC_RADIO_PCB2, &CMotorDlg::OnBnClickedRadioPcb)
	ON_BN_CLICKED(IDC_RADIO_CCD2, &CMotorDlg::OnBnClickedRadioCcd)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_POS_SAVE, &CMotorDlg::OnBnClickedButtonMotorPosSave)
	ON_BN_CLICKED(IDC_BUTTON_ALARM_RESET, &CMotorDlg::OnBnClickedButtonAlarmReset)
	ON_BN_CLICKED(IDC_BUTTON_JOG_PLUS, &CMotorDlg::OnBnClickedButtonJogPlus)
	ON_BN_CLICKED(IDC_BUTTON_JOG_MINUS, &CMotorDlg::OnBnClickedButtonJogMinus)
	ON_BN_CLICKED(IDC_BUTTON_ORIGIN_ALL, &CMotorDlg::OnBnClickedButtonOriginAll)
	ON_BN_CLICKED(IDC_BUTTON_SERVO_ON_ALL, &CMotorDlg::OnBnClickedButtonServoOnAll)
	ON_BN_CLICKED(IDC_BUTTON_SERVO_OFF_ALL, &CMotorDlg::OnBnClickedButtonServoOffAll)
	ON_BN_CLICKED(IDC_BUTTON_ALARM_RESET_ALL, &CMotorDlg::OnBnClickedButtonAlarmResetAll)
	ON_BN_CLICKED(IDC_BUTTON_STOP_ALL, &CMotorDlg::OnBnClickedButtonStopAll)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_ORIGIN, &CMotorDlg::OnBnClickedButtonMotorOrigin)
	ON_BN_CLICKED(IDC_BUTTON_SERVO_ON, &CMotorDlg::OnBnClickedButtonServoOn)
	ON_BN_CLICKED(IDC_BUTTON_SERBO_OFF, &CMotorDlg::OnBnClickedButtonSerboOff)
	ON_BN_CLICKED(IDC_RADIO_MOTOR_SPEED1, &CMotorDlg::OnBnClickedRadioMotorSpeed1)
	ON_BN_CLICKED(IDC_RADIO_MOTOR_SPEED2, &CMotorDlg::OnBnClickedRadioMotorSpeed2)
	ON_BN_CLICKED(IDC_RADIO_MOTOR_SPEED3, &CMotorDlg::OnBnClickedRadioMotorSpeed3)
	ON_BN_CLICKED(IDC_CHECK_RESOLUTION, &CMotorDlg::OnBnClickedCheckResolution)
	ON_BN_CLICKED(IDC_BUTTON_RESOLUTION, &CMotorDlg::OnBnClickedButtonResolution)
	ON_BN_CLICKED(IDC_BUTTON_JOG_STOP, &CMotorDlg::OnBnClickedButtonJogStop)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_Vel_SOFTLIMIT, &CMotorDlg::OnBnClickedButtonMotorVelSoftlimit)
	ON_BN_CLICKED(IDC_BUTTON_TEST2, &CMotorDlg::OnBnClickedButtonTest2)
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CMotorDlg::OnBnClickedButtonTest)
	
	ON_BN_CLICKED(IDC_BUTTON_GOTO_PCBMOTOR, &CMotorDlg::OnBnClickedButtonGotoPcbmotor)
	ON_STN_CLICKED(IDC_STATIC_MOTORSPEED, &CMotorDlg::OnStnClickedStaticMotorspeed)

	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_GOTO_DISPENCEMOTOR, &CMotorDlg::OnBnClickedButtonGotoDispencemotor)

	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_TEACHLENS_GRID, &CMotorDlg::OnDBClickedGridLens)
	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_RESOLLENS_GRID, &CMotorDlg::OnDBClickedGridLensResol)
	
	
	ON_BN_CLICKED(IDC_BUTTON_GOTO_LENSLASERALIGNMOTOR, &CMotorDlg::OnBnClickedButtonGotoLenslaseralignmotor)
END_MESSAGE_MAP()


// CMotorDlg 메시지 처리기입니다.
BOOL CMotorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	motorTemp = 0;
	m_iSelCam = 0;
	m_iSelMotor = Motor_Lens_X;
	m_iMotorSpeed = 0;
	m_fMotorJogSpeed = MOTOR_JOG_LOW;
	m_iVel_Limit = 1;

	InitGridCtrl_Lens();
	InitGridCtrl_LensResol();
	setInterface();

	changeMotorNo(Motor_Lens_X);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CMotorDlg::OnBnClickedOk(){}
void CMotorDlg::OnBnClickedCancel(){}

void CMotorDlg::setInterface()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	WINDOWPLACEMENT wndpl;
	this->GetWindowPlacement(&wndpl);

	/*wndpl.rcNormalPosition.left = pFrame->m_rectCamDispPos2.right+1;
	wndpl.rcNormalPosition.right = MAIN_DLG_SIZE_X;
	wndpl.rcNormalPosition.top = pFrame->m_rectCamDispPos1.top - SUB_DLG_OFFSET_Y+10;
	wndpl.rcNormalPosition.bottom = MAIN_DLG_SIZE_Y - 85;*/

	wndpl.rcNormalPosition = pFrame->m_rectCamDispPos2;
	wndpl.rcNormalPosition.right = pFrame->m_rectCamDispPos2.right + 200;
	wndpl.rcNormalPosition.top -= SUB_DLG_OFFSET_Y - 10;
	wndpl.rcNormalPosition.bottom = MAIN_DLG_SIZE_Y - 80;
	this->MoveWindow(&wndpl.rcNormalPosition);

	m_JogPlus.SetButtonStyle(0);
	m_JogMinus.SetButtonStyle(0);

	CheckVelLimit();
	MotorVellimitView();

	m_btnMot2.m_iStateBtn =1;
	m_btnMot2.Invalidate();

	m_LabelMotorSpeed.SetText("0.1");
	m_LabelMotorSpeed.SetBkColor(M_COLOR_WHITE);
	m_LabelMotorSpeed.Invalidate();
}

void CMotorDlg::InitGridCtrl_Lens()
{
	CRect rect;
	CWnd *pWnd= (CWnd*)GetDlgItem(IDC_STATIC_TEACHLENS_GRID); 
#if (____AA_WAY == PCB_TILT_AA)
	LensRow = 13;//아래
#elif (____AA_WAY == LENS_TILT_AA)
	LensRow = 14;//아래
#endif	
	LensCol = 6;//옆
	
	int margin = 4;
	int gridHeight = 40;// 32;
	int gridWidth1 = 120;

	int gridWidth2 = 82;
	int totalWidth = gridWidth1+(gridWidth2*(LensCol-1));
	//
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = totalWidth +margin;
	rect.bottom = (gridHeight*LensRow) + margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.

	GetDlgItem(IDC_STATIC_TEACHLENS_GRID)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGridTeachingLens.Create(rect, this, IDC_STATIC_TEACHLENS_GRID, WS_TABSTOP | WS_VISIBLE);

	m_clGridTeachingLens.SetTextBkColor(GRID_COLOR_WHITE);
	m_clGridTeachingLens.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridTeachingLens.SetFixedTextColor(GRID_COLOR_WHITE);
	m_clGridTeachingLens.SetReference_Setting();
	m_clGridTeachingLens.EnableSelection(FALSE);
	m_clGridTeachingLens.SetRowCount(LensRow);
	m_clGridTeachingLens.SetColumnCount(LensCol);
	m_clGridTeachingLens.SetFixedRowCount(1);
	m_clGridTeachingLens.SetFixedColumnCount(1);

	CString tmpStr="";
	for (int i = Motor_Lens_X; i <= Motor_Lens_Xt; i++)
	{
		tmpStr.Format("%s",  MotorName[i]);
		m_clGridTeachingLens.SetItemText(0, i - Motor_Lens_X+1, tmpStr);
	}

	m_clGridTeachingLens.SetItemText(1, 0, "ALARM");	//Alarm
	m_clGridTeachingLens.SetItemText(2, 0, "Limit(-)");
	m_clGridTeachingLens.SetItemText(3, 0, "HOME");
	m_clGridTeachingLens.SetItemText(4, 0, "Limit(+)");
	m_clGridTeachingLens.SetItemText(5, 0, "속도(mm/s)");
	m_clGridTeachingLens.SetItemText(6, 0, "가속도(sec)");

	m_clGridTeachingLens.SetItemText(7, 0, MotorPosName[Wait_Pos]);
	m_clGridTeachingLens.SetItemText(8, 0, MotorPosName[Loading_Pos]);
	m_clGridTeachingLens.SetItemText(9, 0, MotorPosName[Bonding_Pos]);
#if (____AA_WAY == PCB_TILT_AA)
	m_clGridTeachingLens.SetItemText(10, 0, MotorPosName[Lens_Pos]);
	m_clGridTeachingLens.SetItemText(11, 0, MotorPosName[Laser_Lens_Pos]);
#else
	m_clGridTeachingLens.SetItemText(10, 0, MotorPosName[Pcb_Loading_Pos]);
	m_clGridTeachingLens.SetItemText(11, 0, MotorPosName[Cover_Loading_Pos]);
	m_clGridTeachingLens.SetItemText(12, 0, MotorPosName[Holder_Uv_Pos]);

	
#endif
	
	m_clGridTeachingLens.SetItemText(LensRow-1, 0, "현재 위치");

	
	//
	int i=0, j=0;
	for (i = 0; i < LensRow; i++)
	{
		m_clGridTeachingLens.SetRowHeight(i, gridHeight);
		
		for (j = 0; j < LensCol; j++)
		{
			m_clGridTeachingLens.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridTeachingLens.SetColumnWidth(j, gridWidth1);
				}else{
					m_clGridTeachingLens.SetColumnWidth(j, gridWidth2);
				}
			}			
		}
	}
	m_clGridTeachingLens.Invalidate();

}
void CMotorDlg::ShowGridCtrl_Lens()
{
	//m_clGridTeachingLens
	CString posStr="";
	double pos=0.0;
	int iIndex=0;
	for (int i = Motor_Lens_X; i <= Motor_Lens_Xt; i++)
	{
		iIndex = i - Motor_Lens_X;
		getMotorPos(i, Wait_Pos, pos, true);
		posStr.Format("%0.3f", pos);
		m_clGridTeachingLens.SetItemText(7, iIndex+1, posStr);

		getMotorPos(i, Loading_Pos, pos, true);
		posStr.Format("%0.3f", pos);
		m_clGridTeachingLens.SetItemText(8, iIndex+1, posStr);

		getMotorPos(i, Bonding_Pos, pos, true);
		posStr.Format("%0.3f", pos);
		m_clGridTeachingLens.SetItemText(9, iIndex+1, posStr);
#if (____AA_WAY == PCB_TILT_AA)
		getMotorPos(i, Lens_Pos, pos, true);
		posStr.Format("%0.3f", pos);
		m_clGridTeachingLens.SetItemText(10, iIndex+1, posStr);

		getMotorPos(i, Laser_Lens_Pos, pos, true);
		posStr.Format("%0.3f", pos);
		m_clGridTeachingLens.SetItemText(11, iIndex+1, posStr);
#else
		getMotorPos(i, Pcb_Loading_Pos, pos, true);
		posStr.Format("%0.3f", pos);
		m_clGridTeachingLens.SetItemText(10, iIndex + 1, posStr);

		getMotorPos(i, Cover_Loading_Pos, pos, true);
		posStr.Format("%0.3f", pos);
		m_clGridTeachingLens.SetItemText(11, iIndex + 1, posStr);

		getMotorPos(i, Holder_Uv_Pos, pos, true);
		posStr.Format("%0.3f", pos);
		m_clGridTeachingLens.SetItemText(12, iIndex + 1, posStr);

		
#endif	
	}

}
void CMotorDlg::InitGridCtrl_LensResol()
{
	CRect rect;
	CWnd *pWnd= (CWnd*)GetDlgItem(IDC_STATIC_RESOLLENS_GRID); 
	LensResolRow = 2;//아래
	LensResolCol = 5;//옆
	int margin = 4;
	int gridHeight = 30;
	int gridWidth1 = 45;
	int gridWidth2 = 67;
	int totalWidth = gridWidth1+(gridWidth2*(LensResolCol-1));
	//
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = totalWidth +margin;
	rect.bottom = (gridHeight*LensResolRow) +margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.

	GetDlgItem(IDC_STATIC_RESOLLENS_GRID)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGridResolLens.Create(rect, this, IDC_STATIC_RESOLLENS_GRID, WS_TABSTOP | WS_VISIBLE);

	m_clGridResolLens.SetTextBkColor(GRID_COLOR_WHITE);
	m_clGridResolLens.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridResolLens.SetFixedTextColor(GRID_COLOR_WHITE);
	m_clGridResolLens.SetReference_Setting();
	m_clGridResolLens.EnableSelection(FALSE);
	m_clGridResolLens.SetRowCount(LensResolRow);
	m_clGridResolLens.SetColumnCount(LensResolCol);
	m_clGridResolLens.SetFixedRowCount(1);
	m_clGridResolLens.SetFixedColumnCount(1);

	CString tmpStr="";
	m_clGridResolLens.SetItemText(1, 0, "LENS");

	m_clGridResolLens.SetItemText(0, 1, "RESOL X");		//RESOL X
	m_clGridResolLens.SetItemText(0, 2, "RESOL Y");		//RESOL Y
	m_clGridResolLens.SetItemText(0, 3, "ANGLE X");		//ANGLE X
	m_clGridResolLens.SetItemText(0, 4, "ANGLE Y");		//ANGLE Y

	

	
	//
	int i=0, j=0;
	for (i = 0; i < LensResolRow; i++)
	{
		m_clGridResolLens.SetRowHeight(i, gridHeight);
		
		for (j = 0; j < LensResolCol; j++)
		{
			m_clGridResolLens.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridResolLens.SetColumnWidth(j, gridWidth1);
				}else{
					m_clGridResolLens.SetColumnWidth(j, gridWidth2);
				}
			}			
		}
	}
	m_clGridResolLens.Invalidate();
}
void CMotorDlg::ShowGridCtrl_LensResol()
{
	//m_clGridResolLens
}
void CMotorDlg::OnDBClickedGridLens(NMHDR* pNMHDR, LRESULT* pResult)
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;

	int row = pNMGridView->iRow;
	int col = pNMGridView->iColumn;
	if(col<0 || row<0)										//JJH.	수정
		return;

	CString celData;

	int curCol = col;
	if(col == 0)
		curCol = m_iSelMotor+1 - Motor_Lens_X;


	changeMotorNo(curCol-1+Motor_Lens_X);


	if(col == 0)														//JJH.	수정
	{
		if(row>=7 && row<LensRow)////12    20180104_2
		{

			m_clGridTeachingLens.SetItemBkColor(row , curCol , GRID_COLOR_RED);

			celData = m_clGridTeachingLens.GetItemText(LensRow-1, curCol);////12    20180104_2
			m_clGridTeachingLens.SetItemText(row, curCol, celData);
			m_clGridTeachingLens.Invalidate();
		}

	}
	else
	{
		if(row>=5 && row<LensRow)//12    20180104_2
		{
			m_clGridTeachingLens.SetItemBkColor(row , curCol , GRID_COLOR_RED);
			celData = m_clGridTeachingLens.GetItemText(row, col);
			CGetNumDlg dlg(12, (LPTSTR)(LPCTSTR)celData);

			if(dlg.DoModal() == IDOK)
			{
				CString curStr = dlg.GetstrNum();
				double fVal = atof(curStr);

				if(row==5)
				{
					if(m_iVel_Limit ==0)
					{
						if(fVal<1)				fVal = 1;
						if (fVal > 500)			fVal = 500;
						
					}
					else
					{
						if(fVal<0.03)			fVal = 0.03;
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
						if(fVal>3)				fVal = 3;
					}
				}

				celData.Format("%.03f", fVal);
				m_clGridTeachingLens.SetItemText(row, col, celData);
			}
			else
			{
				m_clGridTeachingLens.SetItemBkColor(row , col , GRID_COLOR_SELECT);
			}
			m_clGridTeachingLens.Invalidate();
		}
	}

}
void CMotorDlg::OnDBClickedGridLensResol(NMHDR* pNMHDR, LRESULT* pResult)
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
	
	int col = pNMGridView->iColumn;
	int row = pNMGridView->iRow;

	CString celData = m_clGridResolLens.GetItemText(row, col);


	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		CString curStr = dlg.GetstrNum();

		double dVal = atof(curStr);

		celData.Format("%.4lf", dVal);

		m_clGridResolLens.SetItemText(row, col, celData);
	}
	m_clGridResolLens.Invalidate();
}
void CMotorDlg::changeCamera()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)(AfxGetApp()->m_pMainWnd);
	pFrame->setCamDisplay(m_iSelCam,0);

	dispResolDataOnGrid();

	if (m_bCalcResol)
		changeCalcMode();
}


void CMotorDlg::OnBnClickedRadioLens()
{
	UpdateData(true);
	changeCamera();
}

void CMotorDlg::OnBnClickedRadioPcb()
{
	UpdateData(true);
	changeCamera();
}

void CMotorDlg::OnBnClickedRadioCcd()
{
	UpdateData(true);
	changeCamera();
}

void CMotorDlg::initMotorGrid()
{
	
}

void CMotorDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if(bShow)
	{
		CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
		 
		/*if(gMIUDevice.CurrentState>3)
			m_iSelCam = pFrame->m_iCurCamNo = 2;
		else*/
			//m_iSelCam = pFrame->m_iCurCamNo = 1;
		m_iSelCam = pFrame->m_iCurCamNo = 1;
		changeCamera();
		UpdateData(false);

		ShowGridCtrl_Lens();
		//dispMotorPos();
		MotorVellimitView();

		dispResolDataOnGrid();

		changeCalcMode();

		timerRunFlag = false;
		SetTimer(MOTOR_TIMER, 300, NULL);
#ifdef ON_LINE_VISION
		vision.clearOverlay(m_iSelCam);
		vision.drawOverlay(m_iSelCam);
#endif
		UpdateData(false);
	}
	else
	{
		CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

#ifdef ON_LINE_VISION
		vision.clearOverlay(m_iSelCam);
		vision.drawOverlay(m_iSelCam);
#endif

		pFrame->m_bMeasureDist = FALSE;
		pFrame->UpdateData(false);

		m_bCalcResol = false;

		KillTimer(MOTOR_TIMER);
	}
}


void CMotorDlg::OnTimer(UINT_PTR nIDEvent)
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
		if (JogPlusflag == true && OLD_JogPlusflag == false) {
			motor.JogMove(m_iSelMotor, sysData.fMotorSpeed[m_iSelMotor] * sysData.fMotorResol[m_iSelMotor] * m_fMotorJogSpeed);
		}
		else if (JogPlusflag == false && OLD_JogPlusflag == true) {
			motor.JogStop(m_iSelMotor );
		}
		OLD_JogPlusflag = JogPlusflag;


		// JOG 이동 - 방향
		if (JogMinusflag == true && OLD_JogMinusflag == false) {
			motor.JogMove(m_iSelMotor, -sysData.fMotorSpeed[m_iSelMotor] * sysData.fMotorResol[m_iSelMotor] * m_fMotorJogSpeed);
		}
		else if (JogMinusflag == false && OLD_JogMinusflag == true) {
			motor.JogStop(m_iSelMotor);
		}
		OLD_JogMinusflag = JogMinusflag;
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CMotorDlg::dispMotorStatus()
{
	TCHAR szLog[SIZE_OF_1K];
	double	motorPos = 0.0;

	int iIndex = 0;

	//m_gridMotor.SetRedraw(FALSE);
	for (int i = Motor_Lens_X; i <= Motor_Lens_Xt; i++)
	{
		iIndex = i - Motor_Lens_X;
		
		if((i == Motor_Lens_Xt) || (i== Motor_Lens_Yt) || (i == Motor_PCB_Xt) || (i == Motor_PCB_Yt) )		// 스태핑 모터
			motorPos	= motor.GetCommandPos_Disp(i);
		else
			motorPos	= motor.GetEncoderPos_Disp(i);

		_stprintf_s(szLog, SIZE_OF_1K, _T("%.03f"), motorPos);
		m_clGridTeachingLens.SetItemText(LensRow-1, iIndex+1, szLog);//12  20180104_2


		if ( motor.GetAmpFault(i) )
		{
			m_clGridTeachingLens.SetItemBkColor(1,(iIndex+1),GRID_COLOR_RED);

			if(!delayDlg->IsWindowVisible())
			{
				/*sTempLang.LoadStringA(IDS_STRING152);
				sLangChange.Format(sTempLang, MotorName[i]);
 				_stprintf_s(sLog, sLangChange);*/
				_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] AMP 알람 감지"), MotorName[i]);
				delayMsg(szLog,3000,M_COLOR_RED);
			}
		}
		else
		{
			m_clGridTeachingLens.SetItemBkColor(1,(iIndex+1),GRID_COLOR_WHITE);
		}
		if ( motor.GetNegaSensor(i) )
		{
			m_clGridTeachingLens.SetItemBkColor(2,(iIndex+1),GRID_COLOR_RED);

			if (bThreadTaskReadyRun == false && i != Motor_Lens_Xt)
			
			{
				if(!delayDlg->IsWindowVisible())
				{
					/*sTempLang.LoadStringA(IDS_STRING150);
					sLangChange.Format(sTempLang, MotorName[i]);
 					_stprintf_s(sLog, sLangChange);*/
					_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] - Limit 감지"), MotorName[i]);
					delayMsg(szLog, 3000, M_COLOR_RED);
				}
			}
		}
		else
		{
			m_clGridTeachingLens.SetItemBkColor(2,(iIndex+1),GRID_COLOR_WHITE);
		}


		if( motor.GetHomeSensor(i) )
			m_clGridTeachingLens.SetItemBkColor(3,(iIndex+1),GRID_COLOR_GREEN);
		else
			m_clGridTeachingLens.SetItemBkColor(3,(iIndex+1),GRID_COLOR_WHITE);


		if ( motor.GetPosiSensor(i) )
		{
			m_clGridTeachingLens.SetItemBkColor(4,(iIndex+1),GRID_COLOR_RED);
			/*sTempLang.LoadStringA(IDS_STRING151);
			sLangChange.Format(sTempLang, MotorName[i]);
 			_stprintf_s(sLog, sLangChange);*/
			_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] + Limit 감지"), MotorName[i]);
			if(!delayDlg->IsWindowVisible())				delayMsg(szLog,3000,M_COLOR_RED);
		}
		else
		{
			m_clGridTeachingLens.SetItemBkColor(4,(iIndex+1),GRID_COLOR_WHITE);
		}
		Sleep(1);
	}
	m_clGridTeachingLens.Invalidate();
}


void CMotorDlg::OnBnClickedButtonOriginAll()
{
	//if(Task.AutoFlag == 1)
	//{
	//	sLangChange.LoadStringA(IDS_STRING1463);
	//	delayMsg(sLangChange, 1000, M_COLOR_RED);
	//	return;
	//}

	//if(Task.AutoFlag == 2)
	//{
	//	sLangChange.LoadStringA(IDS_STRING1468);
	//	delayMsg(sLangChange, 2000, M_COLOR_RED);// 일시 정지 중 사용 불가
	//	return;
	//}


	//CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	//CString dispStr;
	//
	//if(g_bMovingflag)
	//{
	//	sLangChange.LoadStringA(IDS_STRING1394);	//전체 원점 복귀 실패 - 모터 이동 중
	//	dispStr.Format(sLangChange);
	//	pFrame->putListLog(dispStr);

	//	return;
	//}
	//g_bMovingflag =true;

	//if (!m_bCalcResol)
	//{
	//	sLangChange.LoadStringA(IDS_STRING1391);	//전체 원점 복귀 동작을 실행 하시겠습니까?
	//	if (askMsg(sLangChange))
	//	{
	//		sLangChange.LoadStringA(IDS_STRING1388);	//전체 모터를 원점 복귀 합니다
	//		delayMsg(sLangChange, 50000, M_COLOR_DARK_GREEN);
	//		dispStr.Format(dispStr, sLangChange);
	//		pFrame->putListLog(dispStr);

	//		if(motor.HomeProcessAll())
	//		{
	//			sLangChange.LoadStringA(IDS_STRING1387);	//전체 모터 원점 복귀 완료
	//			dispStr.Format(sLangChange);
	//		}
	//		else
	//		{
	//			sLangChange.LoadStringA(IDS_STRING1386);	//전체 모터 원점 복귀 실패.
	//			dispStr.Format(sLangChange);
	//		}
	//		delayMsg(dispStr.GetBuffer(99), 50000, M_COLOR_GREEN);
	//		pFrame->putListLog(dispStr);
	//	}
	//}
	//else
	//{/* TOP 찾기 */
	//	getMarkAndMotor(0);
	//}

	//g_bMovingflag =false;
}

void CMotorDlg::OnBnClickedButtonServoOnAll()
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

	if(g_bMovingflag)
		return;

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
				LogSave(sLangChange);

				delayMsg(dispStr, -1, M_COLOR_GREEN);
			}
		}
	}
	else
	{/* BOTTOM 찾기 */
		getMarkAndMotor(1);
	}

	g_bMovingflag =false;
}

void CMotorDlg::OnBnClickedButtonServoOffAll()
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
			TCHAR dispStr[100];
			_stprintf_s(dispStr, _T("All Motor Servo OFF."));
			delayMsg(dispStr, 5000, M_COLOR_GREEN);

			if(!motor.AmpDisableAll())
			{
				errMsg2(Task.AutoFlag, _T("Servo Off Move Error"));
				LogSave(_T("Servo Off Move Error"));

				delayMsg(dispStr, -1, M_COLOR_GREEN);
			}
		}
	}
	else
	{/* LEFT 찾기 */
		getMarkAndMotor(2);
	}

	g_bMovingflag =false;
}

void CMotorDlg::OnBnClickedButtonStopAll()
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
		TCHAR dispStr[100];
		_stprintf_s(dispStr, _T("All Motor Servo OFF"));
		delayMsg(dispStr, 5000, M_COLOR_GREEN);

		if(!motor.StopAxisAll())
		{
			sLangChange.LoadStringA(IDS_STRING1242);	//모터 정지 동작 시간 초과 [1sec]
			errMsg2(Task.AutoFlag, sLangChange);
			LogSave(sLangChange);

			delayMsg(dispStr, -1, M_COLOR_GREEN);
		}
	}
	else
	{/* RIGHT 찾기 */
		getMarkAndMotor(3);
	}
}


void CMotorDlg::OnBnClickedButtonAlarmResetAll()
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
			LogSave(sLangChange);

			delayMsg(dispStr, -1, M_COLOR_GREEN);
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


void CMotorDlg::getResolDataOnGrid()
{
	CString sTemp="";

	sTemp = m_clGridTeachingLens.GetItemText(1, 1);
	sysData.dCamResol[m_iSelCam].x = atof(sTemp);
	sTemp = m_clGridTeachingLens.GetItemText(1, 2);
	sysData.dCamResol[m_iSelCam].y = atof(sTemp);
	sTemp = m_clGridTeachingLens.GetItemText(1, 3);
	sysData.dCamAngle[m_iSelCam].x = atof(sTemp);
	sTemp = m_clGridTeachingLens.GetItemText(1, 4);
	sysData.dCamAngle[m_iSelCam].y = atof(sTemp);
}


void CMotorDlg::OnBnClickedButtonMotorOrigin()
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
		sTempLang.LoadStringA(IDS_STRING114);
		sLangChange.Format(sTempLang, MotorName[m_iSelMotor]);
		_stprintf_s(dispStr, sLangChange);
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
	pFrame->putListLog(dispStr);

	motor.HomeProcess(m_iSelMotor);

	sTempLang.LoadStringA(IDS_STRING116);
	sLangChange.Format(sTempLang, MotorName[m_iSelMotor]);
	_stprintf_s(dispStr, sLangChange);
	pFrame->putListLog(dispStr);

	g_bMovingflag =false;
}

void CMotorDlg::OnBnClickedButtonServoOn()
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
	delayMsg(dispStr, 1500, M_COLOR_GREEN);

	if(!motor.AmpEnable(m_iSelMotor))
	{
		sTempLang.LoadStringA(IDS_STRING111);
		sLangChange.Format(sTempLang, MotorName[m_iSelMotor]);
		_stprintf_s(dispStr, sLangChange);
		errMsg2(Task.AutoFlag, dispStr);
		LogSave(dispStr);

		delayMsg(dispStr, -1, M_COLOR_GREEN);
	}

	g_bMovingflag =false;
}

void CMotorDlg::OnBnClickedButtonSerboOff()
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
	sprintf_s(dispStr, "%s Motor Servo Off", MotorName[m_iSelMotor]);
	delayMsg(dispStr, 5000, M_COLOR_GREEN);

	if(!motor.AmpDisable(m_iSelMotor))
	{
		sprintf_s(dispStr, "%s Motor Servo Off Move Error.", MotorName[m_iSelMotor]);
		errMsg2(Task.AutoFlag, dispStr);
		LogSave(dispStr);

		delayMsg(dispStr, -1, M_COLOR_GREEN);
	}

	g_bMovingflag =false;
}

void CMotorDlg::OnBnClickedButtonAlarmReset()
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


	if(!askMsg("Select Motor Alarm Reset ?"))
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
		LogSave(dispStr);

		delayMsg(dispStr, -1, M_COLOR_GREEN);
	}
}


void CMotorDlg::OnBnClickedRadioMotorSpeed1()
{
	m_fMotorJogSpeed = MOTOR_JOG_LOW;
	UpdateData(true);
}


void CMotorDlg::OnBnClickedRadioMotorSpeed2()
{
	m_fMotorJogSpeed = MOTOR_JOG_MID;
	UpdateData(true);
}


void CMotorDlg::OnBnClickedRadioMotorSpeed3()
{
	m_fMotorJogSpeed = MOTOR_JOG_HIGH;
	UpdateData(true);
}


void CMotorDlg::OnBnClickedButtonJogPlus()
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


void CMotorDlg::OnBnClickedButtonJogMinus()
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

void CMotorDlg::OnBnClickedButtonJogStop()
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

void CMotorDlg::OnBnClickedButtonMotorPosSave()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	bool passFlag = password.m_bFlag;

	//if(passFlag == false)
	//{
	//	CString strTemp;
	//	CKeyPadDlg keyDlg;

	//	keyDlg.m_strKeyPad = "Password를 입력하세요.";

	//	if (keyDlg.DoModal()==IDOK)
	//	{
	//		strTemp = keyDlg.GetstrKeypad();
	//		passFlag = strTemp.CompareNoCase(password.m_szPassword) ? false : true;
	//	}
	//	else
	//	{
	//		return;
	//	}
	//}

	passFlag = true;
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

	//m_gridMotor.SetRedraw(FALSE);

	sLangChange.LoadStringA(IDS_STRING1435);	//파라미터를 저장 하시겠습니까?
	cellStr.Format(sLangChange);

	if( !askMsg(cellStr.GetBuffer(99)) )
	{
		return;
	}

	changeMotorNo(m_iSelMotor);

	int iIndex;
	for (int i = Motor_Lens_X; i<Motor_Lens_Xt + 1; i++)
	
	{
		iIndex = i - Motor_Lens_X;
		if(m_iVel_Limit == 1)
		{
			cellStr = m_clGridTeachingLens.GetItemText(5, iIndex+1);
			model.axis[i].m_dLimit_OK = (float)atof(cellStr);

			cellStr = m_clGridTeachingLens.GetItemText(6, iIndex+1);
			model.axis[i].m_dLimit_Err = (float)atof(cellStr);
		}
		else
		{//이리들어옴
			cellStr = m_clGridTeachingLens.GetItemText(5, iIndex+1);
			sysData.fMotorSpeed[i] = (float)atof(cellStr);

			cellStr = m_clGridTeachingLens.GetItemText(6, iIndex+1);
			sysData.fMotorAccTime[i] = (float)atof(cellStr);
		}

		cellStr = m_clGridTeachingLens.GetItemText(7, iIndex+1);
		model.axis[i].pos[Wait_Pos] = (atof(cellStr) + sysData.dDataset[i]);

		cellStr = m_clGridTeachingLens.GetItemText(8, iIndex+1);
		model.axis[i].pos[Loading_Pos] = (atof(cellStr) + sysData.dDataset[i]);

		cellStr = m_clGridTeachingLens.GetItemText(9, iIndex+1);
		model.axis[i].pos[Bonding_Pos] = (atof(cellStr) + sysData.dDataset[i]);
#if (____AA_WAY == PCB_TILT_AA)
		cellStr = m_clGridTeachingLens.GetItemText(10, iIndex+1);
		model.axis[i].pos[Lens_Pos] = (atof(cellStr) + sysData.dDataset[i]);

		cellStr = m_clGridTeachingLens.GetItemText(11, iIndex+1);
		model.axis[i].pos[Laser_Lens_Pos] = (atof(cellStr) + sysData.dDataset[i]);

#else
		cellStr = m_clGridTeachingLens.GetItemText(10, iIndex + 1);
		model.axis[i].pos[Pcb_Loading_Pos] = (atof(cellStr) + sysData.dDataset[i]);

		cellStr = m_clGridTeachingLens.GetItemText(11, iIndex + 1);
		model.axis[i].pos[Cover_Loading_Pos] = (atof(cellStr) + sysData.dDataset[i]);

		cellStr = m_clGridTeachingLens.GetItemText(12, iIndex + 1);
		model.axis[i].pos[Holder_Uv_Pos] = (atof(cellStr) + sysData.dDataset[i]);


		
#endif
	
	}

	model.Save();
	sysData.Save();

	sLangChange.LoadStringA(IDS_STRING1434);
	LogSave(sLangChange);
}


void CMotorDlg::changeMotorNo(int motorNo)
{
	for(int i=5; i<LensRow; i++)
	{
		m_clGridTeachingLens.SetItemBkColor(i , (m_iSelMotor+1-Motor_Lens_X),GRID_COLOR_WHITE);
	}


	m_iSelMotor = motorNo;

	for(int i=5; i<LensRow; i++)
	{
		m_clGridTeachingLens.SetItemBkColor(i , (m_iSelMotor+1-Motor_Lens_X),GRID_COLOR_SELECT);
	}
	m_clGridTeachingLens.Invalidate();
}


BEGIN_EVENTSINK_MAP(CMotorDlg, CDialogEx)

END_EVENTSINK_MAP()


void CMotorDlg::dispResolDataOnGrid()
{
	CString sTemp="";
	sTemp.Format("%.4lf", sysData.dCamResol[m_iSelCam].x);
	m_clGridResolLens.SetItemText(1, 1, sTemp);
	sTemp.Format("%.4lf", sysData.dCamResol[m_iSelCam].y);
	m_clGridResolLens.SetItemText(1, 2, sTemp);
	sTemp.Format("%.4lf", sysData.dCamAngle[m_iSelCam].x);
	m_clGridResolLens.SetItemText(1, 3, sTemp);
	sTemp.Format("%.4lf", sysData.dCamAngle[m_iSelCam].y);
	m_clGridResolLens.SetItemText(1, 4, sTemp);
}


void CMotorDlg::changeCalcMode()
{
	m_bFindTop		=	false;
	m_bFindBottom	=	false;
	m_bFindLeft		=	false;
	m_bFindRight	=	false;

	GetDlgItem(IDC_BUTTON_RESOLUTION)->EnableWindow(FALSE);

	if (m_bCalcResol)
	{
		GetDlgItem(IDC_STATIC_RESOLLENS_GRID)->ShowWindow(true);
		GetDlgItem(IDC_BUTTON_RESOLUTION)->ShowWindow(true);
		m_clGridResolLens.ShowWindow(SW_SHOW);

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
		GetDlgItem(IDC_STATIC_RESOLLENS_GRID)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_RESOLUTION)->ShowWindow(false);
		m_clGridResolLens.ShowWindow(SW_HIDE);
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
		vision.clearOverlay(m_iSelCam);
		vision.drawOverlay(m_iSelCam);
		#endif
	}
}


void CMotorDlg::OnBnClickedCheckResolution()
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


void CMotorDlg::DblClickMsflexgridResol()
{
	
}


void CMotorDlg::drawResolBackGround()
{
	CRect rTemp;
	COLORREF color;

	/* TOP */
	if (m_bFindTop){
		color = M_COLOR_GREEN;
	}else{
		color = M_COLOR_RED;
	}
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


void CMotorDlg::getMarkAndMotor(int iPos)
{
	int iRtn;
	double dRate, dAngle;
	int iType = 0;
	if( m_iSelCam == 1 )	iType =  PCB_Chip_MARK;
	else					iType =  LENS_Align_MARK;

	vision.clearOverlay(m_iSelCam);

	vision.getSnapImage(m_iSelCam);
	vision.setLiveMode(true);

#ifdef USE_GEOMETRIC
	iRtn = vision.geometricModelFinder(iPos+1, m_iSelCam, iType, 0,  m_dFindCenter[iPos], dRate, dAngle);
#else
	iRtn = vision.patternMatching(iPos+1, m_iSelCam, iType, 0, m_dFindCenter[iPos], dRate, dAngle);
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

	if ( m_iSelCam== CAM1 )
	{
		m_dMotorPos[iPos].x = motor.GetEncoderPos(Motor_PCB_X);	//motor.GetCommandPos(Motor_PCB_X);
		m_dMotorPos[iPos].y = motor.GetEncoderPos(Motor_PCB_Y);	//motor.GetCommandPos(Motor_PCB_Y);
	}
	else if (m_iSelCam == CAM2)
	{
		m_dMotorPos[iPos].x = motor.GetEncoderPos(Motor_Lens_X);	//motor.GetCommandPos(Motor_Lens_X);
		m_dMotorPos[iPos].y = motor.GetEncoderPos(Motor_Lens_Y);	///*motor.GetCommandPos(Motor_Lens_Y)*/;
	}

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

void CMotorDlg::OnBnClickedButtonResolution()
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

		CString sTemp="";

		sTemp.Format("%.4lf", m_dTempResol.x);
		m_clGridTeachingLens.SetItemText(1, 1, sTemp);
		sTemp.Format("%.4lf", m_dTempResol.y);
		m_clGridTeachingLens.SetItemText(1, 2, sTemp);
		sTemp.Format("%.4lf", m_dTempAngle.x);
		m_clGridTeachingLens.SetItemText(1, 3, sTemp);
		sTemp.Format("%.4lf", m_dTempAngle.y);
		m_clGridTeachingLens.SetItemText(1, 4, sTemp);

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

void CMotorDlg::CheckVelLimit()
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


void CMotorDlg::OnBnClickedButtonMotorVelSoftlimit()
{
	CheckVelLimit();
	MotorVellimitView();
}

void CMotorDlg::MotorVellimitView()
{
	CString temp="";
	int i = 0;
	int iIndex;
	if(m_iVel_Limit == 1)		// Align Limit
	{
		m_clGridTeachingLens.SetItemText(5, 0, "OK Limit");
		m_clGridTeachingLens.SetItemText(6, 0, "ERR Limit");

		for (int i = Motor_Lens_X; i <= Motor_Lens_Xt + 1; i++)
		
		{
			iIndex = i - Motor_Lens_X;
			temp.Format("%0.3f", model.axis[i].m_dLimit_OK);
			m_clGridTeachingLens.SetItemText(5, iIndex+1, temp);

			temp.Format("%0.3f", model.axis[i].m_dLimit_Err);
			m_clGridTeachingLens.SetItemText(6, iIndex+1, temp);
		}
	}
	else	// 속도 가속도
	{
		m_clGridTeachingLens.SetItemText(5, 0, "속도(mm/s)");
		m_clGridTeachingLens.SetItemText(6, 0, "가속도(sec)");

		for (int i = Motor_Lens_X; i <= Motor_Lens_Xt; i++)
		
		{
			iIndex = i - Motor_Lens_X;
			temp.Format("%0.3f", sysData.fMotorSpeed[i]);
			m_clGridTeachingLens.SetItemText(5, iIndex+1, temp);

			temp.Format("%.03f", sysData.fMotorAccTime[i]);
			m_clGridTeachingLens.SetItemText(6, iIndex+1, temp);
		}
	}

}


void CMotorDlg::OnBnClickedButtonTest2()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	//if(Task.AutoFlag == 2&&m_iSelMotor != Motor_Lens_Z)
	//{
	//	sLangChange.LoadStringA(IDS_STRING1468);
	//	delayMsg(sLangChange, 2000, M_COLOR_RED);// 일시 정지 중 사용 불가
	//	return;
	//}


	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;

	g_bMovingflag =true;

	CString temp;
	GetDlgItem(IDC_STATIC_MOTORSPEED)->GetWindowText(temp);
	double pos;
	pos = atof(temp);

	if ( pos > 5)	pos = 5;

	if(m_iSelMotor == Motor_Lens_Xt || m_iSelMotor == Motor_Lens_Yt || m_iSelMotor == Motor_PCB_Xt || m_iSelMotor == Motor_PCB_Yt)
		motor.MoveAxis(m_iSelMotor, REL, -pos, 1, 0.1f);
	else
		motor.MoveAxis(m_iSelMotor, REL, -pos, 4, 0.2f);

	g_bMovingflag =false;
}


void CMotorDlg::OnBnClickedButtonTest()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	//if(Task.AutoFlag == 2 && m_iSelMotor != Motor_Lens_Z)
	//{
	//	sLangChange.LoadStringA(IDS_STRING1468);
	//	delayMsg(sLangChange, 2000, M_COLOR_RED);// 일시 정지 중 사용 불가
	//	return;
	//}


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

	if (m_iSelMotor == Motor_Lens_Xt || m_iSelMotor == Motor_Lens_Yt || m_iSelMotor == Motor_PCB_Xt || m_iSelMotor == Motor_PCB_Yt)
		motor.MoveAxis(m_iSelMotor, REL, +pos, 1, 0.1f);
	else
		motor.MoveAxis(m_iSelMotor, REL, +pos, 4, 0.2f);


	g_bMovingflag =false;
}


bool CMotorDlg::registPatMark(int iCamNo, CRect rcBox)
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


void CMotorDlg::OnBnClickedButtonGotoPcbmotor()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	pFrame->m_bIsMotorMode = 1;
	pFrame->ctrlSubDlg(MOTOR_DLG2);	
}

void CMotorDlg::OnStnClickedStaticMotorspeed()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		m_LabelMotorSpeed.SetText(dlg.GetstrNum());
	}
}


void CMotorDlg::dispMotorPos()
{	
	
}

void CMotorDlg::OnMouseMove(UINT nFlags, CPoint point)
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


void CMotorDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	JogMinusflag = false;
	JogPlusflag = false;

	CDialogEx::OnLButtonUp(nFlags, point);
}



void CMotorDlg::OnBnClickedButtonGotoDispencemotor()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	pFrame->m_bIsMotorMode = 2;
	pFrame->ctrlSubDlg(MOTOR_DLG3);	
}




void CMotorDlg::OnBnClickedButtonGotoLenslaseralignmotor()
{
	// TODO: Add your control notification handler code here
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	pFrame->m_bIsMotorMode = 3;
	pFrame->ctrlSubDlg(MOTOR_DLG4);
}
