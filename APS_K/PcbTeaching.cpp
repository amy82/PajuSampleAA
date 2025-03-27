// MotorDlg.cpp : 구현 파일입니다.
//pcb

#include "stdafx.h"
#include "PcbTeaching.h"
#include "afxdialogex.h"
#include "DelayMsgDlg.h"

// CMotorDlg2 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMotorDlg2, CDialogEx)

	CMotorDlg2::CMotorDlg2(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMotorDlg2::IDD, pParent)
{
	m_bFindTop		=	false;
	m_bFindBottom	=	false;
	m_bFindLeft		=	false;
	m_bFindRight	=	false;
	testCount = 0;
}

CMotorDlg2::~CMotorDlg2()
{
}

void CMotorDlg2::DoDataExchange(CDataExchange* pDX)
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


BEGIN_MESSAGE_MAP(CMotorDlg2, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMotorDlg2::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMotorDlg2::OnBnClickedCancel)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_RADIO_LENS, &CMotorDlg2::OnBnClickedRadioLens)
	ON_BN_CLICKED(IDC_RADIO_PCB2, &CMotorDlg2::OnBnClickedRadioPcb)
	ON_BN_CLICKED(IDC_RADIO_CCD2, &CMotorDlg2::OnBnClickedRadioCcd)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_POS_SAVE, &CMotorDlg2::OnBnClickedButtonMotorPosSave)
	ON_BN_CLICKED(IDC_BUTTON_ALARM_RESET, &CMotorDlg2::OnBnClickedButtonAlarmReset)
	ON_BN_CLICKED(IDC_BUTTON_JOG_PLUS, &CMotorDlg2::OnBnClickedButtonJogPlus)
	ON_BN_CLICKED(IDC_BUTTON_JOG_MINUS, &CMotorDlg2::OnBnClickedButtonJogMinus)
	ON_BN_CLICKED(IDC_BUTTON_ORIGIN_ALL, &CMotorDlg2::OnBnClickedButtonOriginAll)
	ON_BN_CLICKED(IDC_BUTTON_SERVO_ON_ALL, &CMotorDlg2::OnBnClickedButtonServoOnAll)
	ON_BN_CLICKED(IDC_BUTTON_SERVO_OFF_ALL, &CMotorDlg2::OnBnClickedButtonServoOffAll)
	ON_BN_CLICKED(IDC_BUTTON_ALARM_RESET_ALL, &CMotorDlg2::OnBnClickedButtonAlarmResetAll)
	ON_BN_CLICKED(IDC_BUTTON_STOP_ALL, &CMotorDlg2::OnBnClickedButtonStopAll)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_ORIGIN, &CMotorDlg2::OnBnClickedButtonMotorOrigin)
	ON_BN_CLICKED(IDC_BUTTON_SERVO_ON, &CMotorDlg2::OnBnClickedButtonServoOn)
	ON_BN_CLICKED(IDC_BUTTON_SERBO_OFF, &CMotorDlg2::OnBnClickedButtonSerboOff)
	ON_BN_CLICKED(IDC_RADIO_MOTOR_SPEED1, &CMotorDlg2::OnBnClickedRadioMotorSpeed1)
	ON_BN_CLICKED(IDC_RADIO_MOTOR_SPEED2, &CMotorDlg2::OnBnClickedRadioMotorSpeed2)
	ON_BN_CLICKED(IDC_RADIO_MOTOR_SPEED3, &CMotorDlg2::OnBnClickedRadioMotorSpeed3)
	ON_BN_CLICKED(IDC_CHECK_RESOLUTION, &CMotorDlg2::OnBnClickedCheckResolution)
	ON_BN_CLICKED(IDC_BUTTON_RESOLUTION, &CMotorDlg2::OnBnClickedButtonResolution)
	ON_BN_CLICKED(IDC_BUTTON_JOG_STOP, &CMotorDlg2::OnBnClickedButtonJogStop)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_Vel_SOFTLIMIT, &CMotorDlg2::OnBnClickedButtonMotorVelSoftlimit)
	ON_BN_CLICKED(IDC_BUTTON_TEST2, &CMotorDlg2::OnBnClickedButtonTest2)
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CMotorDlg2::OnBnClickedButtonTest)
	
	ON_BN_CLICKED(IDC_BUTTON_GOTO_LENSMOTOR, &CMotorDlg2::OnBnClickedButtonGotoLensmotor)
	ON_STN_CLICKED(IDC_STATIC_MOTORSPEED, &CMotorDlg2::OnStnClickedStaticMotorspeed)

	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_GOTO_DISPENCEMOTOR, &CMotorDlg2::OnBnClickedButtonGotoDispencemotor)
	ON_BN_CLICKED(IDC_BUTTON_GOTO_PCBMOTOR, &CMotorDlg2::OnBnClickedButtonGotoPcbmotor)

	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_TEACHPCB_GRID, &CMotorDlg2::OnDBClickedGridPcb)
	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_RESOLPCB_GRID, &CMotorDlg2::OnDBClickedGridResol)
	
	
	ON_BN_CLICKED(IDC_BUTTON_GOTO_LENSLASERALIGNMOTOR, &CMotorDlg2::OnBnClickedButtonGotoLenslaseralignmotor)
END_MESSAGE_MAP()


// CMotorDlg2 메시지 처리기입니다.
BOOL CMotorDlg2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_iSelCam = 0;
	m_iSelMotor = 1;
	m_iMotorSpeed = 0;
	m_fMotorJogSpeed = MOTOR_JOG_LOW;
	m_iVel_Limit = 1;

	InitGridCtrl_Pcb();
	InitGridCtrl_Resol();
	setInterface();

	changeMotorNo(Motor_PCB_X);
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CMotorDlg2::OnBnClickedOk(){}
void CMotorDlg2::OnBnClickedCancel(){}

void CMotorDlg2::InitGridCtrl_Pcb()
{
	CRect rect;
	CWnd *pWnd= (CWnd*)GetDlgItem(IDC_STATIC_TEACHPCB_GRID); 
#if (____AA_WAY == PCB_TILT_AA)
	pcbRow = 15;//아래
#elif (____AA_WAY == LENS_TILT_AA)
	pcbRow = 16;// 19;//아래
#endif

	pcbCol = 7;//옆

	
	int margin = 4;
	int gridHeight = 35;//;
	int gridWidth1 = 120;
	int gridWidth2 = 68;
	int totalWidth = gridWidth1+(gridWidth2*(pcbCol-1));
	//
	pWnd->GetWindowRect(rect);//pWnd->GetClientRect(rect);
	ScreenToClient(rect);//ClientToScreen(rect);

	rect.right = totalWidth +margin;
	rect.bottom = (gridHeight*pcbRow) +margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.

	GetDlgItem(IDC_STATIC_TEACHPCB_GRID)->GetWindowRect(rect);
	ScreenToClient(rect);//ScreenToClient(rect);
	m_clGridTeachingPcb.Create(rect, this, IDC_STATIC_TEACHPCB_GRID, WS_TABSTOP | WS_VISIBLE);

	m_clGridTeachingPcb.SetTextBkColor(GRID_COLOR_WHITE);
	m_clGridTeachingPcb.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridTeachingPcb.SetFixedTextColor(GRID_COLOR_WHITE);
	m_clGridTeachingPcb.SetReference_Setting();
	m_clGridTeachingPcb.EnableSelection(FALSE);
	m_clGridTeachingPcb.SetRowCount(pcbRow);
	m_clGridTeachingPcb.SetColumnCount(pcbCol);
	m_clGridTeachingPcb.SetFixedRowCount(1);
	m_clGridTeachingPcb.SetFixedColumnCount(1);

	CString tmpStr="";
	for (int i = Motor_PCB_X; i <= Motor_PCB_Z; i++)
	
	{
		tmpStr.Format("%s",MotorName[i]);
		m_clGridTeachingPcb.SetItemText(0, i+1, tmpStr);
	}

	m_clGridTeachingPcb.SetItemText(1, 0, "ALARM");	
	m_clGridTeachingPcb.SetItemText(2, 0,  "Limit(-)");
	m_clGridTeachingPcb.SetItemText(3, 0, "HOME");
	m_clGridTeachingPcb.SetItemText(4, 0, "Limit(+)");
	m_clGridTeachingPcb.SetItemText(5, 0, "속도(mm/s)");
	m_clGridTeachingPcb.SetItemText(6, 0, "가속도(sec)");

	m_clGridTeachingPcb.SetItemText(7, 0, MotorPosName[Wait_Pos]);
	m_clGridTeachingPcb.SetItemText(8, 0, MotorPosName[Loading_Pos]);
	m_clGridTeachingPcb.SetItemText(9, 0, MotorPosName[Holder_Pos]);
	m_clGridTeachingPcb.SetItemText(10, 0, MotorPosName[Align_Pos]);
	m_clGridTeachingPcb.SetItemText(11, 0, MotorPosName[Bonding_Pos]);
	m_clGridTeachingPcb.SetItemText(12, 0, MotorPosName[Dark_Pos]);
    m_clGridTeachingPcb.SetItemText(13, 0, MotorPosName[OC_6500K_Pos]);
#if (____AA_WAY == PCB_TILT_AA)
   // m_clGridTeachingPcb.SetItemText(14, 0, MotorPosName[OC_2800K_Pos]);

#elif (____AA_WAY == LENS_TILT_AA)
	m_clGridTeachingPcb.SetItemText(14, 0, MotorPosName[Lens_Pos]);
	//m_clGridTeachingPcb.SetItemText(15, 0, MotorPosName[Pcb_Loading_Pos]);
	//m_clGridTeachingPcb.SetItemText(16, 0, MotorPosName[Cover_Loading_Pos]);
	//m_clGridTeachingPcb.SetItemText(17, 0, MotorPosName[Cover_UnLoading_Pos]);
#endif


	
	m_clGridTeachingPcb.SetItemText(pcbRow-1, 0, "현재 위치");
	//
	int i=0, j=0;
	for (i = 0; i < pcbRow; i++)
	{
		m_clGridTeachingPcb.SetRowHeight(i, gridHeight);
		
		for (j = 0; j < pcbCol; j++)
		{
			m_clGridTeachingPcb.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridTeachingPcb.SetColumnWidth(j, gridWidth1);
				}else{
					m_clGridTeachingPcb.SetColumnWidth(j, gridWidth2);
				}
			}			
		}
	}
	m_clGridTeachingPcb.Invalidate();
}

void CMotorDlg2::ShowGridCtrl_Pcb()
{
	CString posStr = "";
	double pos = 0.0;
	for (int i = Motor_PCB_X; i <= Motor_PCB_Z; i++)
	
	{
		getMotorPos(i, Wait_Pos, pos, true);
		posStr.Format("%0.3f", pos);
		m_clGridTeachingPcb.SetItemText(7, i+1, posStr);

		getMotorPos(i, Loading_Pos, pos, true);
		posStr.Format("%0.3f", pos);
		m_clGridTeachingPcb.SetItemText(8, i+1, posStr);

		getMotorPos(i, Holder_Pos, pos, true);
		posStr.Format("%0.3f", pos);
		m_clGridTeachingPcb.SetItemText(9, i+1, posStr);

		getMotorPos(i, Align_Pos, pos, true);
		posStr.Format("%0.3f", pos);
		m_clGridTeachingPcb.SetItemText(10, i+1, posStr);

		getMotorPos(i, Bonding_Pos, pos, true);
		posStr.Format("%0.3f", pos);
		m_clGridTeachingPcb.SetItemText(11, i+1, posStr);

		getMotorPos(i, Dark_Pos, pos, true);
		posStr.Format("%0.3f", pos);
		m_clGridTeachingPcb.SetItemText(12, i+1, posStr);

        getMotorPos(i, OC_6500K_Pos, pos, true);
        posStr.Format("%0.3f", pos);
        m_clGridTeachingPcb.SetItemText(13, i + 1, posStr);

        //  , ,

#if (____AA_WAY == PCB_TILT_AA)

#elif (____AA_WAY == LENS_TILT_AA)
		getMotorPos(i, Lens_Pos, pos, true);
		posStr.Format("%0.3f", pos);
		m_clGridTeachingPcb.SetItemText(14, i + 1, posStr);

		
#endif

	}

	m_clGridTeachingPcb.Invalidate();
}

void CMotorDlg2::OnDBClickedGridPcb(NMHDR* pNMHDR, LRESULT* pResult)
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
		curCol = m_iSelMotor + 1;

	changeMotorNo(curCol-1);

	if(col == 0)														//JJH.	수정
	{
		if(row>=7 && row<pcbRow)
		{
			m_clGridTeachingPcb.SetItemBkColor(row , curCol, GRID_COLOR_RED);

			celData = m_clGridTeachingPcb.GetItemText(pcbRow-1, curCol);
			m_clGridTeachingPcb.SetItemText(row, curCol, celData);
			m_clGridTeachingPcb.Invalidate();
		}
	}
	else
	{
		if(row>=5 && row<pcbRow)
		{
			m_clGridTeachingPcb.SetItemBkColor(row , curCol, GRID_COLOR_RED);


			celData = m_clGridTeachingPcb.GetItemText(row, col);
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
						if (fVal > 500)			fVal = 500;
						
					}
					else
					{
						if(fVal<0.03)			fVal = 0.03;
						if (fVal>5.5)			fVal = 5.5;//if(fVal>0.5)			fVal = 0.5;
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
				m_clGridTeachingPcb.SetItemText(row, col, celData);
			}
			else
			{
				m_clGridTeachingPcb.SetItemBkColor(row , col, GRID_COLOR_SELECT);
			}
			m_clGridTeachingPcb.Invalidate();
		}
	}
}

void CMotorDlg2::InitGridCtrl_Resol()
{
	CRect rect;
	CWnd *pWnd= (CWnd*)GetDlgItem(IDC_STATIC_RESOLPCB_GRID); 
	resolRow = 2;//아래
	resolCol = 5;//옆
	int margin = 4;
	int gridHeight = 30;
	int gridWidth1 = 45;
	int gridWidth2 = 67;
	int totalWidth = gridWidth1+(gridWidth2*(resolCol-1));
	//
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = totalWidth +margin;
	rect.bottom = (gridHeight*resolRow) +margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.

	GetDlgItem(IDC_STATIC_RESOLPCB_GRID)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGridResolPcb.Create(rect, this, IDC_STATIC_RESOLPCB_GRID, WS_TABSTOP | WS_VISIBLE);

	m_clGridResolPcb.SetTextBkColor(GRID_COLOR_WHITE);
	m_clGridResolPcb.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridResolPcb.SetFixedTextColor(GRID_COLOR_WHITE);
	m_clGridResolPcb.SetReference_Setting();
	m_clGridResolPcb.EnableSelection(FALSE);
	m_clGridResolPcb.SetRowCount(resolRow);
	m_clGridResolPcb.SetColumnCount(resolCol);
	m_clGridResolPcb.SetFixedRowCount(1);
	m_clGridResolPcb.SetFixedColumnCount(1);

	CString tmpStr="";

	m_clGridResolPcb.SetItemText(0, 1, _T("RESOL X"));
	m_clGridResolPcb.SetItemText(0, 2, _T("RESOL Y"));
	m_clGridResolPcb.SetItemText(0, 3, "ANGLE X");
	m_clGridResolPcb.SetItemText(0, 4, "ANGLE Y");

	m_clGridResolPcb.SetItemText(1, 0, "PCB");
	//
	int i=0, j=0;
	for (i = 0; i < resolRow; i++)
	{
		m_clGridResolPcb.SetRowHeight(i, gridHeight);
		
		for (j = 0; j < resolCol; j++)
		{
			m_clGridResolPcb.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridResolPcb.SetColumnWidth(j, gridWidth1);
				}else{
					m_clGridResolPcb.SetColumnWidth(j, gridWidth2);
				}
			}			
		}
	}
	m_clGridResolPcb.Invalidate();

}
void CMotorDlg2::ShowGridCtrl_Resol()
{

}

void CMotorDlg2::OnDBClickedGridResol(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
	
	int col = pNMGridView->iColumn;
	int row = pNMGridView->iRow;
	if(col<1 || row<1)										//JJH.	수정
		return;
	CString celData = m_clGridResolPcb.GetItemText(row, col);


	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		CString curStr = dlg.GetstrNum();

		double dVal = atof(curStr);

		celData.Format("%.4lf", dVal);

		m_clGridResolPcb.SetItemText(row, col, celData);
	}
	m_clGridResolPcb.Invalidate();
}


void CMotorDlg2::dispResolDataOnGrid()
{
	CString sTemp="";
	sTemp.Format("%.4lf", sysData.dCamResol[m_iSelCam].x);
	m_clGridResolPcb.SetItemText(1, 1, sTemp);
	sTemp.Format("%.4lf", sysData.dCamResol[m_iSelCam].y);
	m_clGridResolPcb.SetItemText(1, 2, sTemp);
	sTemp.Format("%.4lf", sysData.dCamAngle[m_iSelCam].x);
	m_clGridResolPcb.SetItemText(1, 3, sTemp);
	sTemp.Format("%.4lf", sysData.dCamAngle[m_iSelCam].y);
	m_clGridResolPcb.SetItemText(1, 4, sTemp);
}

void CMotorDlg2::setInterface()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	WINDOWPLACEMENT wndpl;
	this->GetWindowPlacement(&wndpl);

	//
	/*wndpl.rcNormalPosition.left = pFrame->m_rectCamDispPos2.right+1;
	wndpl.rcNormalPosition.right = MAIN_DLG_SIZE_X;
	wndpl.rcNormalPosition.top = pFrame->m_rectCamDispPos1.top - SUB_DLG_OFFSET_Y+10;
	wndpl.rcNormalPosition.bottom = MAIN_DLG_SIZE_Y - 85;*/


	wndpl.rcNormalPosition = pFrame->m_rectCamDispPos2;
	wndpl.rcNormalPosition.right = pFrame->m_rectCamDispPos2.right + 50;
	wndpl.rcNormalPosition.top -= SUB_DLG_OFFSET_Y - 10;
	wndpl.rcNormalPosition.bottom = MAIN_DLG_SIZE_Y - 80;
	this->MoveWindow(&wndpl.rcNormalPosition);

	m_JogPlus.SetButtonStyle(0);
	m_JogMinus.SetButtonStyle(0);

	CheckVelLimit();
	MotorVellimitView();

	m_btnMot1.m_iStateBtn =1;
	m_btnMot1.Invalidate();

	m_LabelMotorSpeed.SetBkColor(M_COLOR_WHITE);
	m_LabelMotorSpeed.SetText("0.1");
	m_LabelMotorSpeed.Invalidate();
}

void CMotorDlg2::changeCamera()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)(AfxGetApp()->m_pMainWnd);
	pFrame->setCamDisplay(m_iSelCam,0);

	dispResolDataOnGrid();

	if (m_bCalcResol)
		changeCalcMode();
}


void CMotorDlg2::OnBnClickedRadioLens()
{
	UpdateData(true);
	changeCamera();
}

void CMotorDlg2::OnBnClickedRadioPcb()
{
	UpdateData(true);
	changeCamera();
}


void CMotorDlg2::OnBnClickedRadioCcd()
{
	UpdateData(true);
	changeCamera();
}

void CMotorDlg2::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if(bShow)
	{
		CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

		m_iSelCam = pFrame->m_iCurCamNo = 1;

		changeCamera();
		UpdateData(false);

		ShowGridCtrl_Pcb();
		MotorVellimitView();

		dispResolDataOnGrid();

		changeCalcMode();

		timerRunFlag = false;
		SetTimer(MOTOR_TIMER, 300, NULL);
		SetTimer(JOG_TIMER, 50, NULL);
		
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
		KillTimer(JOG_TIMER);
		
	}
}



void CMotorDlg2::MotorVellimitView()
{
	CString strTemp="";
	CString temp="";
	int i = 0;
	int iIndex=0;
	if(m_iVel_Limit ==1)
	{
		m_clGridTeachingPcb.SetItemText(5, 0, "OK Limit");
		m_clGridTeachingPcb.SetItemText(6, 0, "ERR Limit");

		for (int i = Motor_PCB_X; i <= Motor_PCB_Z; i++)
		
		{
			iIndex = i;

			temp.Format("%0.3f", model.axis[i].m_dLimit_OK);
			m_clGridTeachingPcb.SetItemText(5, iIndex+1, temp);

			temp.Format("%0.3f", model.axis[i].m_dLimit_Err);
			m_clGridTeachingPcb.SetItemText(6, iIndex+1, temp);
		}
	}
	else	// 속도 가속도
	{
		m_clGridTeachingPcb.SetItemText(5, 0, "속도(mm/s)");
		m_clGridTeachingPcb.SetItemText(6, 0, "가속도(sec)");

		for (int i = Motor_PCB_X; i <= Motor_PCB_Z; i++)
		
		{
			iIndex = i;

			temp.Format("%0.3f", sysData.fMotorSpeed[i]);
			m_clGridTeachingPcb.SetItemText(5, iIndex+1, temp);

			temp.Format("%.03f", sysData.fMotorAccTime[i]);
			m_clGridTeachingPcb.SetItemText(6, iIndex+1, temp);

		}
	}

}

void CMotorDlg2::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent==MOTOR_TIMER)
	{
		/*if (!timerRunFlag)
		{
			timerRunFlag = true;
			dispMotorStatus();

			timerRunFlag = false;
		}*/
		dispMotorStatus();
		
	}
	if (nIDEvent == JOG_TIMER)
	{
		int m_MotorNum = m_iSelMotor;
		// JOG 이동 + 방향
		if (JogPlusflag == true && OLD_JogPlusflag == false)
			motor.JogMove(m_MotorNum, sysData.fMotorSpeed[m_MotorNum] * sysData.fMotorResol[m_MotorNum] * m_fMotorJogSpeed);
		else if (JogPlusflag == false && OLD_JogPlusflag == true)
			motor.JogStop(m_MotorNum);
		OLD_JogPlusflag = JogPlusflag;


		// JOG 이동 - 방향
		if (JogMinusflag == true && OLD_JogMinusflag == false)
		{
			
			motor.JogMove(m_MotorNum, -sysData.fMotorSpeed[m_MotorNum] * sysData.fMotorResol[m_MotorNum] * m_fMotorJogSpeed);
		}
		else if (JogMinusflag == false && OLD_JogMinusflag == true)
			motor.JogStop(m_MotorNum);
		OLD_JogMinusflag = JogMinusflag;
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CMotorDlg2::dispMotorStatus()
{
	TCHAR szLog[SIZE_OF_1K];
	//CString str = _T("");
	//char sLog[100];
	double	motorPos = 0.0;

	int iIndex = 0;
	//_stprintf_s(szLog, SIZE_OF_1K, _T("Test = %d") , testCount);
	//testCount++;
	//theApp.MainDlg->putListLog(szLog);
	for (int i = Motor_PCB_X; i <= Motor_PCB_Z; i++)
	
	{
		iIndex = i;

		if ((i == Motor_Lens_Xt) || (i == Motor_PCB_Xt) || (i == Motor_PCB_Yt))	//스태핑 모터
		{
			motorPos = motor.GetCommandPos_Disp(i);
		}
		else {
			motorPos = motor.GetEncoderPos_Disp(i);
		}
		_stprintf_s(szLog, SIZE_OF_1K, _T("%.03f"), motorPos);
		m_clGridTeachingPcb.SetItemText(pcbRow-1, iIndex+1, szLog);

		if ( motor.GetAmpFault(i) ) 
		{
			m_clGridTeachingPcb.SetItemBkColor(1,(iIndex+1),GRID_COLOR_RED);

			if(!delayDlg->IsWindowVisible())
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] AMP 알람 감지"), MotorName[i]);
				delayMsg(szLog,3000,M_COLOR_RED);
			}
		}
		else
		{
			m_clGridTeachingPcb.SetItemBkColor(1,(iIndex+1),GRID_COLOR_WHITE);
		}

		if ( motor.GetNegaSensor(i) )
		{
			m_clGridTeachingPcb.SetItemBkColor(2,(iIndex+1),GRID_COLOR_RED);

			if(!delayDlg->IsWindowVisible())
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] - Limit 감지"), MotorName[i]);
				delayMsg(szLog, 3000, M_COLOR_RED);
			}
		}
		else
		{
			m_clGridTeachingPcb.SetItemBkColor(2,(iIndex+1),GRID_COLOR_WHITE);
		}

		if( motor.GetHomeSensor(i) )
			m_clGridTeachingPcb.SetItemBkColor(3,(iIndex+1),GRID_COLOR_GREEN);
		else
			m_clGridTeachingPcb.SetItemBkColor(3,(iIndex+1),GRID_COLOR_WHITE);

		if ( motor.GetPosiSensor(i) )
		{
			m_clGridTeachingPcb.SetItemBkColor(4,(iIndex+1),GRID_COLOR_RED);
			_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] + Limit 감지"), MotorName[i]);
			if(!delayDlg->IsWindowVisible())				delayMsg(szLog,3000,M_COLOR_RED);
		}
		else
		{
			m_clGridTeachingPcb.SetItemBkColor(4,(iIndex+1),GRID_COLOR_WHITE);
		}
	}
	////////////////////////////////////////////////////////////////////////////////////
	//
	//									Motor_Insp_X
	//
	////////////////////////////////////////////////////////////////////////////////////
	m_clGridTeachingPcb.Invalidate();
}



void CMotorDlg2::OnBnClickedButtonOriginAll()
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
	//CString sTemp;

	///* 이동중이면 Return */
	//if(g_bMovingflag)
	//{
	//	sLangChange.LoadStringA(IDS_STRING1394);	//전체 원점 복귀 실패 - 모터 이동 중
	//	sTemp.Format(sLangChange);
	//	pFrame->putListLog(sTemp);
	//	return;
	//}
	//g_bMovingflag =true;

	//if (!m_bCalcResol)
	//{
	//	sLangChange.LoadStringA(IDS_STRING1391);	//전체 원점 복귀 동작을 실행 하시겠습니까?
	//	if (askMsg(sLangChange))
	//	{
	//		sLangChange.LoadStringA(IDS_STRING1392);	//전체 원점 복귀 수행합니다
	//		delayMsg(sLangChange, 50000, M_COLOR_DARK_GREEN);
	//		sTemp.Format(sLangChange);
	//		pFrame->putListLog(sTemp);

	//		if(motor.HomeProcessAll())
	//		{
	//			sLangChange.LoadStringA(IDS_STRING1387);	//전체 모터 원점 복귀 완료
	//			sTemp.Format(sLangChange);
	//		}
	//		else
	//		{
	//			sLangChange.LoadStringA(IDS_STRING1386);	//전체 모터 원점 복귀 실패.
	//			sTemp.Format(sLangChange);
	//		}
	//		
	//		delayMsg(sTemp.GetBuffer(99), 50000, M_COLOR_GREEN);
	//		pFrame->putListLog(sTemp);
	//	}
	//}
	//else
	//{/* TOP 찾기 */
	//	getMarkAndMotor(0);
	//}

	//g_bMovingflag =false;
}

void CMotorDlg2::OnBnClickedButtonServoOnAll()
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

void CMotorDlg2::OnBnClickedButtonServoOffAll()
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

void CMotorDlg2::OnBnClickedButtonStopAll()
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
		_stprintf_s(dispStr, _T("All Motor Servo OFF 합니다."));
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


void CMotorDlg2::OnBnClickedButtonAlarmResetAll()
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


void CMotorDlg2::getResolDataOnGrid()
{
	CString sTemp="";

	sTemp = m_clGridResolPcb.GetItemText(1, 1);
	sysData.dCamResol[m_iSelCam].x = atof(sTemp);
	sTemp = m_clGridResolPcb.GetItemText(1, 2);
	sysData.dCamResol[m_iSelCam].y = atof(sTemp);
	sTemp = m_clGridResolPcb.GetItemText(1, 3);
	sysData.dCamAngle[m_iSelCam].x = atof(sTemp);
	sTemp = m_clGridResolPcb.GetItemText(1, 4);
	sysData.dCamAngle[m_iSelCam].y = atof(sTemp);
}


void CMotorDlg2::OnBnClickedButtonMotorOrigin()
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
	int m_MotorNum = m_iSelMotor;
	/* 이동중이면 Return */
	if(g_bMovingflag)
	{
		sLangChange.LoadStringA(IDS_STRING1473);	//%s 모터 원점 복귀 실패 - 모터 이동 중
		_stprintf_s(dispStr, sLangChange, MotorName[m_MotorNum]);
		pFrame->putListLog(dispStr);

		return;
	}


	CString tmpStr="";
	tmpStr.Format("[%s 모터] 원점 복귀 하시겠습니까?", MotorName[m_MotorNum]);

	if(!askMsg(tmpStr))
	{
		return;
	}

	g_bMovingflag =true;

	tmpStr.Format("%s 모터 원점 복귀를 수행 합니다.", MotorName[m_MotorNum]);
	_stprintf_s(dispStr, tmpStr);
	delayMsg(dispStr, 2000, M_COLOR_GREEN);

	tmpStr.Format("%s 모터 원점 복귀를 수행 합니다.", MotorName[m_MotorNum]);
	_stprintf_s(dispStr, tmpStr);
	pFrame->putListLog(dispStr);


	motor.HomeProcess(m_MotorNum);
	tmpStr.Format("%s 원점 복귀 완료.");
	sprintf_s(dispStr, tmpStr, MotorName[m_MotorNum]);
	pFrame->putListLog(dispStr);

	g_bMovingflag =false;

	tmpStr.Empty();
}

void CMotorDlg2::OnBnClickedButtonServoOn()
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
	int m_MotorNum = m_iSelMotor;
	TCHAR dispStr[100];
	sTempLang.LoadStringA(IDS_STRING112);
	sLangChange.Format(sTempLang, MotorName[m_MotorNum]);
	_stprintf_s(dispStr, sLangChange);
	delayMsg(dispStr, 5000, M_COLOR_GREEN);
	
	if(!motor.AmpEnable(m_MotorNum))
	{
		sTempLang.LoadStringA(IDS_STRING111);
		sLangChange.Format(sTempLang, MotorName[m_MotorNum]);
		_stprintf_s(dispStr, sLangChange);
		errMsg2(Task.AutoFlag, dispStr);
	}

	g_bMovingflag =false;
}

void CMotorDlg2::OnBnClickedButtonSerboOff()
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
	int m_MotorNum = m_iSelMotor;
	char dispStr[100];
	sprintf_s(dispStr, "%s Motor Servo Off .", MotorName[m_MotorNum]);
	delayMsg(dispStr, 5000, M_COLOR_GREEN);

	if(!motor.AmpDisable(m_MotorNum))
	{
		sprintf_s(dispStr, "%s Motor Servo Off Move Error.", MotorName[m_MotorNum]);
		errMsg2(Task.AutoFlag, dispStr);
	}

	g_bMovingflag =false;
}

void CMotorDlg2::OnBnClickedButtonAlarmReset()
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
	int m_MotorNum = m_iSelMotor;
	TCHAR dispStr[100];
	sLangChange.LoadStringA(IDS_STRING1222);	//모터 Drive의 Alarm을 해제 합니다.
	_stprintf_s(dispStr, _T("%s ") + sLangChange, MotorName[m_MotorNum]);

	delayMsg(dispStr, 5000, M_COLOR_GREEN);

	if(!motor.AmpFaultReset(m_MotorNum))
	{
		sLangChange.LoadStringA(IDS_STRING1470);	//%s 모터의 Amp Fault가 정상적으로 Reset 되지 않았습니다
		_stprintf_s(dispStr, sLangChange, MotorName[m_MotorNum]);
		errMsg2(Task.AutoFlag, dispStr);
	}
}


void CMotorDlg2::OnBnClickedRadioMotorSpeed1()
{
	m_fMotorJogSpeed = MOTOR_JOG_LOW;
	UpdateData(true);
}


void CMotorDlg2::OnBnClickedRadioMotorSpeed2()
{
	m_fMotorJogSpeed = MOTOR_JOG_MID;
	UpdateData(true);
}


void CMotorDlg2::OnBnClickedRadioMotorSpeed3()
{
	m_fMotorJogSpeed = MOTOR_JOG_HIGH;
	UpdateData(true);
}


void CMotorDlg2::OnBnClickedButtonJogPlus()
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


void CMotorDlg2::OnBnClickedButtonJogMinus()
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

void CMotorDlg2::OnBnClickedButtonJogStop()
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

void CMotorDlg2::OnBnClickedButtonMotorPosSave()
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
	//		
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
	

	CString cellStr="";

	//m_gridMotor.SetRedraw(FALSE);

	sLangChange.LoadStringA(IDS_STRING1435);	//파라미터를 저장 하시겠습니까?
	cellStr.Format(sLangChange);

	if( !askMsg(cellStr.GetBuffer(99)) )
	{
		return;
	}

	changeMotorNo(m_iSelMotor);

	int iIndex;
	for (int i = Motor_PCB_X; i <= Motor_PCB_Z; i++)
	
	{
		iIndex = i;

		if(m_iVel_Limit == 1)
		{
			cellStr = m_clGridTeachingPcb.GetItemText(5, iIndex+1);
			model.axis[i].m_dLimit_OK = (float)atof(cellStr);

			cellStr = m_clGridTeachingPcb.GetItemText(6, iIndex+1);
			model.axis[i].m_dLimit_Err = (float)atof(cellStr);

		}
		else
		{
			cellStr = m_clGridTeachingPcb.GetItemText(5, iIndex+1);
			sysData.fMotorSpeed[i] = (float)atof(cellStr);

			cellStr = m_clGridTeachingPcb.GetItemText(6, iIndex+1);
			sysData.fMotorAccTime[i] = (float)atof(cellStr);

		}

		cellStr = m_clGridTeachingPcb.GetItemText(7, iIndex+1);
		model.axis[i].pos[Wait_Pos] = (atof(cellStr) + sysData.dDataset[i]);

		cellStr = m_clGridTeachingPcb.GetItemText(8, iIndex+1);
		model.axis[i].pos[Loading_Pos] = (atof(cellStr) + sysData.dDataset[i]);

		cellStr = m_clGridTeachingPcb.GetItemText(9, iIndex+1);
		model.axis[i].pos[Holder_Pos] = (atof(cellStr) + sysData.dDataset[i]);

		cellStr = m_clGridTeachingPcb.GetItemText(10, iIndex+1);
		model.axis[i].pos[Align_Pos] = (atof(cellStr) + sysData.dDataset[i]);

		cellStr = m_clGridTeachingPcb.GetItemText(11, iIndex+1);
		model.axis[i].pos[Bonding_Pos] = (atof(cellStr) + sysData.dDataset[i]);

		cellStr = m_clGridTeachingPcb.GetItemText(12, iIndex+1);
		model.axis[i].pos[Dark_Pos] = (atof(cellStr) + sysData.dDataset[i]);

        cellStr = m_clGridTeachingPcb.GetItemText(13, iIndex + 1);
        model.axis[i].pos[OC_6500K_Pos] = (atof(cellStr) + sysData.dDataset[i]);

#if (____AA_WAY == PCB_TILT_AA)
       /* cellStr = m_clGridTeachingPcb.GetItemText(14, iIndex + 1);
        model.axis[i].pos[OC_2800K_Pos] = (atof(cellStr) + sysData.dDataset[i]);*/

#elif (____AA_WAY == LENS_TILT_AA)
		cellStr = m_clGridTeachingPcb.GetItemText(14, iIndex + 1);
		model.axis[i].pos[Lens_Pos] = (atof(cellStr) + sysData.dDataset[i]);
		/*cellStr = m_clGridTeachingPcb.GetItemText(15, iIndex + 1);
		model.axis[i].pos[Pcb_Loading_Pos] = (atof(cellStr) + sysData.dDataset[i]);
		cellStr = m_clGridTeachingPcb.GetItemText(16, iIndex + 1);
		model.axis[i].pos[Cover_Loading_Pos] = (atof(cellStr) + sysData.dDataset[i]);
		cellStr = m_clGridTeachingPcb.GetItemText(17, iIndex + 1);
		model.axis[i].pos[Cover_UnLoading_Pos] = (atof(cellStr) + sysData.dDataset[i]);*/


		
#endif
	}

	model.Save();
	sysData.Save();

	sLangChange.LoadStringA(IDS_STRING1434);
	LogSave(sLangChange);
}


void CMotorDlg2::changeMotorNo(int motorNo)
{
	int j = m_iSelMotor + 1;
	for(int i=5; i < pcbRow; i++)
	{
		m_clGridTeachingPcb.SetItemBkColor(i , (m_iSelMotor+1),GRID_COLOR_WHITE);
	}


	m_iSelMotor = motorNo;

	for(int i=5; i < pcbRow; i++)
	{
		m_clGridTeachingPcb.SetItemBkColor(i , (m_iSelMotor+1),GRID_COLOR_SELECT);
	}
	m_clGridTeachingPcb.Invalidate();
}


BEGIN_EVENTSINK_MAP(CMotorDlg2, CDialogEx)

END_EVENTSINK_MAP()




void CMotorDlg2::changeCalcMode()
{
	m_bFindTop		=	false;
	m_bFindBottom	=	false;
	m_bFindLeft		=	false;
	m_bFindRight	=	false;

	GetDlgItem(IDC_BUTTON_RESOLUTION)->EnableWindow(FALSE);

	if (m_bCalcResol)
	{
		GetDlgItem(IDC_BUTTON_RESOLUTION)->ShowWindow(true);
		GetDlgItem(IDC_STATIC_RESOLPCB_GRID)->ShowWindow(true);
		m_clGridResolPcb.ShowWindow(SW_SHOW);
		SetDlgItemText(IDC_CHECK_RESOLUTION, "분해능 <<");

		SetDlgItemText(IDC_BUTTON_ORIGIN_ALL, "Top");			//Top")
		SetDlgItemText(IDC_BUTTON_SERVO_ON_ALL, "Bottom");		//Bottom
		SetDlgItemText(IDC_BUTTON_SERVO_OFF_ALL, "Left");		//Left"
		SetDlgItemText(IDC_BUTTON_STOP_ALL, "Right");			//Right
		SetDlgItemText(IDC_BUTTON_ALARM_RESET_ALL, "저장");

		#ifdef ON_LINE_VISION
		vision.clearOverlay(m_iSelCam);
		drawResolBackGround();
		vision.drawOverlay(m_iSelCam);
		#endif
	}
	else
	{
		GetDlgItem(IDC_BUTTON_RESOLUTION)->ShowWindow(false);
		GetDlgItem(IDC_STATIC_RESOLPCB_GRID)->ShowWindow(false);
		m_clGridResolPcb.ShowWindow(SW_HIDE);
		SetDlgItemText(IDC_CHECK_RESOLUTION, "분해능 >>");

		SetDlgItemText(IDC_BUTTON_ORIGIN_ALL, "전체 원점 복귀");
		SetDlgItemText(IDC_BUTTON_SERVO_ON_ALL, "Servo On");
		SetDlgItemText(IDC_BUTTON_SERVO_OFF_ALL, "Servo Off");
		SetDlgItemText(IDC_BUTTON_STOP_ALL, "모터 정지");
		SetDlgItemText(IDC_BUTTON_ALARM_RESET_ALL, "Alarm Reset");

		#ifdef ON_LINE_VISION
		vision.clearOverlay(m_iSelCam);
		vision.drawOverlay(m_iSelCam);
		#endif		
	}
}


void CMotorDlg2::OnBnClickedCheckResolution()
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


void CMotorDlg2::drawResolBackGround()
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


void CMotorDlg2::getMarkAndMotor(int iPos)
{
	int iRtn;
	double dRate, dAngle;
	int iType;

	vision.clearOverlay(m_iSelCam);

	vision.getSnapImage(m_iSelCam);
	vision.setLiveMode(true);

	if( m_iSelCam == 1 )	iType =  PCB_Chip_MARK;
	else					iType =  LENS_Align_MARK;

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
	else if (m_iSelCam<Cam_Cnt)
	{
		m_dMotorPos[iPos].x = motor.GetEncoderPos(Motor_Lens_X);	//motor.GetCommandPos(Motor_Lens_X);
		m_dMotorPos[iPos].y = motor.GetEncoderPos(Motor_Lens_Y);	//motor.GetCommandPos(Motor_Lens_Y);
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

void CMotorDlg2::OnBnClickedButtonResolution()
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
		m_clGridResolPcb.SetItemText(1, 1, sTemp);
		sTemp.Format("%.4lf", m_dTempResol.y);
		m_clGridResolPcb.SetItemText(1, 2, sTemp);
		sTemp.Format("%.4lf", m_dTempAngle.x);
		m_clGridResolPcb.SetItemText(1, 3, sTemp);
		sTemp.Format("%.4lf", m_dTempAngle.y);
		m_clGridResolPcb.SetItemText(1, 4, sTemp);

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

void CMotorDlg2::CheckVelLimit()
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


void CMotorDlg2::OnBnClickedButtonMotorVelSoftlimit()
{
	CheckVelLimit();
	MotorVellimitView();
}



void CMotorDlg2::OnBnClickedButtonTest2()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	//if(Task.AutoFlag == 2&&m_iSelMotor != Motor_PCB_Z)
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

	if ( pos > 3)	pos = 3;

	int m_MotorNum = m_iSelMotor;

	motor.MoveAxis(m_MotorNum, REL, -pos, 4, 0);				// 4: 조그 이동 속도..

	g_bMovingflag =false;
}


void CMotorDlg2::OnBnClickedButtonTest()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	//if(Task.AutoFlag == 2&&m_iSelMotor != Motor_PCB_Z)
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

	if ( pos < 0)
	{
		sLangChange.LoadStringA(IDS_STRING1340);	//이동 거리 입력 값이 (-) 입니다
		errMsg2(0, sLangChange);
		return;
	}

	if ( pos > 3)	pos = 3;
	int m_MotorNum = m_iSelMotor;

	motor.MoveAxis(m_MotorNum, REL, +pos, 4, 0);				// 4: 조그 이동 속도..

	g_bMovingflag =false;
}


bool CMotorDlg2::registPatMark(int iCamNo, CRect rcBox)
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


void CMotorDlg2::OnBnClickedButtonGotoLensmotor()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	pFrame->m_bIsMotorMode = 0;
	pFrame->ctrlSubDlg(MOTOR_DLG);
}


void CMotorDlg2::OnStnClickedStaticMotorspeed()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		m_LabelMotorSpeed.SetText(dlg.GetstrNum());
	}
}





void CMotorDlg2::OnMouseMove(UINT nFlags, CPoint point)
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


void CMotorDlg2::OnLButtonUp(UINT nFlags, CPoint point)
{
	JogMinusflag = false;
	JogPlusflag = false;

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMotorDlg2::OnBnClickedButtonGotoDispencemotor()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	pFrame->m_bIsMotorMode = 2;
	pFrame->ctrlSubDlg(MOTOR_DLG3);	
}


void CMotorDlg2::OnBnClickedButtonGotoPcbmotor()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}



void CMotorDlg2::OnBnClickedButtonGotoLenslaseralignmotor()
{
	// TODO: Add your control notification handler code here
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	pFrame->m_bIsMotorMode = 3;
	pFrame->ctrlSubDlg(MOTOR_DLG4);
}
