// MotorDlg.cpp : 구현 파일입니다.
//Dispenser , 완제품

#include "stdafx.h"
#include "PcbTeachingDis.h"
#include "afxdialogex.h"

#include "EpoxyDlg.h"



// CMotorDlg3 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMotorDlg3, CDialogEx)

	CMotorDlg3::CMotorDlg3(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMotorDlg3::IDD, pParent)
{
	m_bFindTop		=	false;
	m_bFindBottom	=	false;
	m_bFindLeft		=	false;
	m_bFindRight	=	false;
}

CMotorDlg3::~CMotorDlg3()
{
}

void CMotorDlg3::DoDataExchange(CDataExchange* pDX)
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
	//DDX_Control(pDX, IDC_MSFLEXGRID_STATE, m_gridState);
	DDX_Radio(pDX, IDC_RADIO_PCB2, m_iSelCam);
	DDX_Control(pDX, IDC_BUTTON_GOTO_LENSLASERALIGNMOTOR, m_btnMot4);
}


BEGIN_MESSAGE_MAP(CMotorDlg3, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMotorDlg3::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMotorDlg3::OnBnClickedCancel)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_RADIO_LENS, &CMotorDlg3::OnBnClickedRadioLens)
	ON_BN_CLICKED(IDC_RADIO_PCB2, &CMotorDlg3::OnBnClickedRadioPcb)
	ON_BN_CLICKED(IDC_RADIO_CCD2, &CMotorDlg3::OnBnClickedRadioCcd)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_POS_SAVE, &CMotorDlg3::OnBnClickedButtonMotorPosSave)
	ON_BN_CLICKED(IDC_BUTTON_ALARM_RESET, &CMotorDlg3::OnBnClickedButtonAlarmReset)
	ON_BN_CLICKED(IDC_BUTTON_JOG_PLUS, &CMotorDlg3::OnBnClickedButtonJogPlus)
	ON_BN_CLICKED(IDC_BUTTON_JOG_MINUS, &CMotorDlg3::OnBnClickedButtonJogMinus)
	ON_BN_CLICKED(IDC_BUTTON_ORIGIN_ALL, &CMotorDlg3::OnBnClickedButtonOriginAll)
	ON_BN_CLICKED(IDC_BUTTON_SERVO_ON_ALL, &CMotorDlg3::OnBnClickedButtonServoOnAll)
	ON_BN_CLICKED(IDC_BUTTON_SERVO_OFF_ALL, &CMotorDlg3::OnBnClickedButtonServoOffAll)
	ON_BN_CLICKED(IDC_BUTTON_ALARM_RESET_ALL, &CMotorDlg3::OnBnClickedButtonAlarmResetAll)
	ON_BN_CLICKED(IDC_BUTTON_STOP_ALL, &CMotorDlg3::OnBnClickedButtonStopAll)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_ORIGIN, &CMotorDlg3::OnBnClickedButtonMotorOrigin)
	ON_BN_CLICKED(IDC_BUTTON_SERVO_ON, &CMotorDlg3::OnBnClickedButtonServoOn)
	ON_BN_CLICKED(IDC_BUTTON_SERBO_OFF, &CMotorDlg3::OnBnClickedButtonSerboOff)
	ON_BN_CLICKED(IDC_RADIO_MOTOR_SPEED1, &CMotorDlg3::OnBnClickedRadioMotorSpeed1)
	ON_BN_CLICKED(IDC_RADIO_MOTOR_SPEED2, &CMotorDlg3::OnBnClickedRadioMotorSpeed2)
	ON_BN_CLICKED(IDC_RADIO_MOTOR_SPEED3, &CMotorDlg3::OnBnClickedRadioMotorSpeed3)
	ON_BN_CLICKED(IDC_CHECK_RESOLUTION, &CMotorDlg3::OnBnClickedCheckResolution)
	ON_BN_CLICKED(IDC_BUTTON_RESOLUTION, &CMotorDlg3::OnBnClickedButtonResolution)
	ON_BN_CLICKED(IDC_BUTTON_JOG_STOP, &CMotorDlg3::OnBnClickedButtonJogStop)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_Vel_SOFTLIMIT, &CMotorDlg3::OnBnClickedButtonMotorVelSoftlimit)
	ON_BN_CLICKED(IDC_BUTTON_TEST2, &CMotorDlg3::OnBnClickedButtonTest2)
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CMotorDlg3::OnBnClickedButtonTest)
	
	ON_BN_CLICKED(IDC_BUTTON_GOTO_LENSMOTOR, &CMotorDlg3::OnBnClickedButtonGotoLensmotor)
	ON_STN_CLICKED(IDC_STATIC_MOTORSPEED, &CMotorDlg3::OnStnClickedStaticMotorspeed)

	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_GOTO_PCBMOTOR, &CMotorDlg3::OnBnClickedButtonGotoPcbmotor)
	ON_BN_CLICKED(IDC_BUTTON_EPOXYSET, &CMotorDlg3::OnBnClickedButtonEpoxyset)

	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_TEACHDISPENSE_GRID, &CMotorDlg3::OnDBClickedGridDispense)
	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_RESOLDISPENSE_GRID, &CMotorDlg3::OnDBClickedGridDispenseResol)

	ON_NOTIFY(NM_RCLICK, IDC_STATIC_TEACHDISPENSE_GRID, &CMotorDlg3::OnRClickedGridDispense)
	
	
	ON_BN_CLICKED(IDC_BUTTON_GOTO_LENSLASERALIGNMOTOR, &CMotorDlg3::OnBnClickedButtonGotoLenslaseralignmotor)
END_MESSAGE_MAP()


// CMotorDlg3 메시지 처리기입니다.
BOOL CMotorDlg3::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	m_iSelCam = 0;
	m_iSelMotor = 1;
	m_iMotorSpeed = 0;
	m_fMotorJogSpeed = MOTOR_JOG_LOW;
	m_iVel_Limit = 1;

	//initMotorGrid();
	InitGridCtrl_Dispense();
	InitGridCtrl_DispenseResol();
	setInterface();

	changeMotorNo(Motor_PCB_X);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CMotorDlg3::OnBnClickedOk(){}
void CMotorDlg3::OnBnClickedCancel(){}

void CMotorDlg3::setInterface()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	WINDOWPLACEMENT wndpl;
	this->GetWindowPlacement(&wndpl);

	/*wndpl.rcNormalPosition.left = pFrame->m_rectCamDispPos2.right+1;
	wndpl.rcNormalPosition.right = MAIN_DLG_SIZE_X;
	wndpl.rcNormalPosition.top = pFrame->m_rectCamDispPos1.top - SUB_DLG_OFFSET_Y+10;
	wndpl.rcNormalPosition.bottom = MAIN_DLG_SIZE_Y - 85;
*/

	wndpl.rcNormalPosition = pFrame->m_rectCamDispPos2;
	wndpl.rcNormalPosition.right = pFrame->m_rectCamDispPos2.right + 50;
	wndpl.rcNormalPosition.top -= SUB_DLG_OFFSET_Y - 10;
	wndpl.rcNormalPosition.bottom = MAIN_DLG_SIZE_Y - 80;
	this->MoveWindow(&wndpl.rcNormalPosition);

	m_JogPlus.SetButtonStyle(0);
	m_JogMinus.SetButtonStyle(0);

	CheckVelLimit();
	MotorVellimitView();

	m_btnMot3.m_iStateBtn =1;
	m_btnMot3.Invalidate();

	m_LabelMotorSpeed.SetBkColor(M_COLOR_WHITE);
	m_LabelMotorSpeed.SetText("0.1");
	m_LabelMotorSpeed.Invalidate();
}
void CMotorDlg3::InitGridCtrl_Dispense()
{
	CRect rect;
	CWnd *pWnd= (CWnd*)GetDlgItem(IDC_STATIC_TEACHDISPENSE_GRID); 
	DispenseRow = 14 + 3;//아래
	DispenseCol = 7;//옆
	
	int margin = 4;
	int gridHeight = 35;
	int gridWidth1 = 120;
	int gridWidth2 = 68;
	int totalWidth = gridWidth1+(gridWidth2*(DispenseCol-1));
	//
	pWnd->GetWindowRect(rect);//pWnd->GetClientRect(rect);
	ScreenToClient(rect);//ClientToScreen(rect);

	rect.right = totalWidth +margin;
	rect.bottom = (gridHeight*DispenseRow) +margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.

	GetDlgItem(IDC_STATIC_TEACHDISPENSE_GRID)->GetWindowRect(rect);
	ScreenToClient(rect);//ScreenToClient(rect);
	m_clGridTeachingDispense.Create(rect, this, IDC_STATIC_TEACHDISPENSE_GRID, WS_TABSTOP | WS_VISIBLE);

	m_clGridTeachingDispense.SetTextBkColor(GRID_COLOR_WHITE);
	m_clGridTeachingDispense.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridTeachingDispense.SetFixedTextColor(GRID_COLOR_WHITE);
	m_clGridTeachingDispense.SetReference_Setting();
	m_clGridTeachingDispense.EnableSelection(FALSE);
	m_clGridTeachingDispense.SetRowCount(DispenseRow);
	m_clGridTeachingDispense.SetColumnCount(DispenseCol);
	m_clGridTeachingDispense.SetFixedRowCount(1);
	m_clGridTeachingDispense.SetFixedColumnCount(1);

	CString tmpStr="";
	for (int i = Motor_PCB_X; i <= Motor_PCB_Z; i++)
	
	{
		tmpStr.Format("%s",MotorName[i]);
		m_clGridTeachingDispense.SetItemText(0, i+1, tmpStr);
	}

	m_clGridTeachingDispense.SetItemText(1, 0, "ALARM");	//Alarm
	m_clGridTeachingDispense.SetItemText(2, 0, "Limit(-)");
	m_clGridTeachingDispense.SetItemText(3, 0, "HOME");
	m_clGridTeachingDispense.SetItemText(4, 0, "Limit(+)");
	m_clGridTeachingDispense.SetItemText(5, 0, "속도(mm/s)");
	m_clGridTeachingDispense.SetItemText(6, 0, "가속도(sec)");

	m_clGridTeachingDispense.SetItemText(7, 0, MotorPosName[Com_Laser_Pos]);
	m_clGridTeachingDispense.SetItemText(8, 0, MotorPosName[Dispense_Pos]);
	m_clGridTeachingDispense.SetItemText(9, 0, MotorPosName[Laser_Pcb_Pos]);
	m_clGridTeachingDispense.SetItemText(10, 0, MotorPosName[CompleteAlign_Pos]);
	m_clGridTeachingDispense.SetItemText(11, 0, MotorPosName[PDispense_Pos]);
	m_clGridTeachingDispense.SetItemText(12, 0, MotorPosName[Holder_Uv_Pos]);
	m_clGridTeachingDispense.SetItemText(13, 0, MotorPosName[Dispense_Pos1]);
	m_clGridTeachingDispense.SetItemText(14, 0, MotorPosName[Dispense_Pos2]);
	m_clGridTeachingDispense.SetItemText(15, 0, MotorPosName[Dispense_Pos3]);
	m_clGridTeachingDispense.SetItemText(DispenseRow-1, 0, "현재 위치");
	int iIndex=0;
	for (int i = Motor_PCB_X; i <= Motor_PCB_Z; i++)
	
	{
		iIndex = i;

		tmpStr.Format("%s", MotorName[i]);
		m_clGridTeachingDispense.SetItemText(0, iIndex+1, tmpStr);
	}

	//
	int i=0, j=0;
	for (i = 0; i < DispenseRow; i++)
	{
		m_clGridTeachingDispense.SetRowHeight(i, gridHeight);
		
		for (j = 0; j < DispenseCol; j++)
		{
			m_clGridTeachingDispense.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridTeachingDispense.SetColumnWidth(j, gridWidth1);
				}else{
					m_clGridTeachingDispense.SetColumnWidth(j, gridWidth2);
				}
			}			
		}
	}
	m_clGridTeachingDispense.Invalidate();
}
void CMotorDlg3::ShowGridCtrl_Dispense()
{
	CString posStr="";
	double pos=0.0;
	int iIndex=0;
	for (int i = Motor_PCB_X; i <= Motor_PCB_Z; i++)
	
	{
		iIndex = i;

		getMotorPos(i, Com_Laser_Pos, pos, true);
		posStr.Format("%0.3f", pos);
		m_clGridTeachingDispense.SetItemText(7, iIndex+1, posStr);

		getMotorPos(i, Dispense_Pos, pos, true);
		posStr.Format("%0.3f", pos);
		m_clGridTeachingDispense.SetItemText(8, iIndex+1, posStr);

		getMotorPos(i, Laser_Pcb_Pos, pos, true);
		posStr.Format("%0.3f", pos);
		m_clGridTeachingDispense.SetItemText(9, iIndex+1, posStr);

		getMotorPos(i, CompleteAlign_Pos, pos, true);
		posStr.Format("%0.3f", pos);
		m_clGridTeachingDispense.SetItemText(10, iIndex + 1, posStr);

		getMotorPos(i, PDispense_Pos, pos, true);
		posStr.Format("%0.3f", pos);
		m_clGridTeachingDispense.SetItemText(11, iIndex + 1, posStr);


		getMotorPos(i, Holder_Uv_Pos, pos, true);
		posStr.Format("%0.3f", pos);
		m_clGridTeachingDispense.SetItemText(12, iIndex + 1, posStr);

		
		getMotorPos(i, Dispense_Pos1, pos, true);
		posStr.Format("%0.3f", pos);
		m_clGridTeachingDispense.SetItemText(13, iIndex + 1, posStr);

		getMotorPos(i, Dispense_Pos2, pos, true);
		posStr.Format("%0.3f", pos);
		m_clGridTeachingDispense.SetItemText(14, iIndex + 1, posStr);

		getMotorPos(i, Dispense_Pos3, pos, true);
		posStr.Format("%0.3f", pos);
		m_clGridTeachingDispense.SetItemText(15, iIndex + 1, posStr);
	}

	m_clGridTeachingDispense.Invalidate();
}
void CMotorDlg3::InitGridCtrl_DispenseResol()
{
	CRect rect;
	CWnd *pWnd= (CWnd*)GetDlgItem(IDC_STATIC_RESOLDISPENSE_GRID); 
	DispenseResolRow = 2;//아래
	DispenseResolCol = 5;//옆
	int margin = 4;
	int gridHeight = 30;
	int gridWidth1 = 45;
	int gridWidth2 = 67;
	int totalWidth = gridWidth1+(gridWidth2*(DispenseResolCol-1));
	//
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = totalWidth +margin;
	rect.bottom = (gridHeight*DispenseResolRow) +margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.

	GetDlgItem(IDC_STATIC_RESOLDISPENSE_GRID)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGridResolDispense.Create(rect, this, IDC_STATIC_RESOLDISPENSE_GRID, WS_TABSTOP | WS_VISIBLE);

	m_clGridResolDispense.SetTextBkColor(GRID_COLOR_WHITE);
	m_clGridResolDispense.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridResolDispense.SetFixedTextColor(GRID_COLOR_WHITE);
	m_clGridResolDispense.SetReference_Setting();
	m_clGridResolDispense.EnableSelection(FALSE);
	m_clGridResolDispense.SetRowCount(DispenseResolRow);
	m_clGridResolDispense.SetColumnCount(DispenseResolCol);
	m_clGridResolDispense.SetFixedRowCount(1);
	m_clGridResolDispense.SetFixedColumnCount(1);

	CString tmpStr="";

	m_clGridResolDispense.SetItemText(0, 1, _T("RESOL X"));
	m_clGridResolDispense.SetItemText(0, 2, _T("RESOL Y"));
	m_clGridResolDispense.SetItemText(0, 3, "ANGLE X");
	m_clGridResolDispense.SetItemText(0, 4, "ANGLE Y");

	m_clGridResolDispense.SetItemText(1, 0, "PCB");

	
	//
	int i=0, j=0;
	for (i = 0; i < DispenseResolRow; i++)
	{
		m_clGridResolDispense.SetRowHeight(i, gridHeight);
		
		for (j = 0; j < DispenseResolCol; j++)
		{
			m_clGridResolDispense.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridResolDispense.SetColumnWidth(j, gridWidth1);
				}else{
					m_clGridResolDispense.SetColumnWidth(j, gridWidth2);
				}
			}			
		}
	}
	m_clGridResolDispense.Invalidate();
}
void CMotorDlg3::ShowGridCtrl_DispenseResol()
{


}

void CMotorDlg3::OnRClickedGridDispense(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;

	int row = pNMGridView->iRow;
	int col = pNMGridView->iColumn;

	if (Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	if (col < 0 || row < 0)										//JJH.	수정
		return;

	CString celData;

	int curCol = col;
	if (col == 0)
		curCol = m_iSelMotor + 1;


	changeMotorNo(curCol - 1);

	if (col == 0)														//JJH.	수정
	{
		if (row >= 7 && row < DispenseRow)
		{
			if (Task.AutoFlag == 0 && (row == 13 || row == 14 || row == 15))
			{
				celData.Format(_T("%s위치로 이동하시겠습니까?"), MotorPosName[row + 13]);///Dispense_Pos1 = 26
				if (askMsg(celData))
				{
					if (motor.PCB_Z_Motor_Move(Wait_Pos) == true)
					{
						if (motor.Pcb_Motor_Move(row + 13) == true)	//Dispense_Pos1 = 26
						{
							if (motor.PCB_Z_Motor_Move(row + 13) == true)
							{
							}
						}
					}
					return;
				}

			}
		}
	}
}

void CMotorDlg3::OnDBClickedGridDispense(NMHDR* pNMHDR, LRESULT* pResult)
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

	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	if(col<0 || row<0)										//JJH.	수정
		return;

	CString celData;

	int curCol = col;
	if(col == 0)
		curCol = m_iSelMotor + 1;


	changeMotorNo(curCol-1);
	if(col == 0)														//JJH.	수정
	{
		if(row>=7 && row<DispenseRow)
		{
			m_clGridTeachingDispense.SetItemBkColor(row,curCol,GRID_COLOR_RED);

			celData = m_clGridTeachingDispense.GetItemText(DispenseRow-1, curCol);
			m_clGridTeachingDispense.SetItemText(row, curCol, celData);
			m_clGridTeachingDispense.Invalidate();

			
		}
	}
	else
	{
		if(row>=5 && row<DispenseRow)
		{
			m_clGridTeachingDispense.SetItemBkColor(row,col,GRID_COLOR_RED);


			celData = m_clGridTeachingDispense.GetItemText(row, col);
			CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);

			if(dlg.DoModal() == IDOK)
			{
				CString curStr = dlg.GetstrNum();
				double fVal = atof(curStr);

				if(row==5)
				{
					if(m_iVel_Limit == 0 )
					{
						if(fVal<1)				fVal = 1;
						if(fVal>500)			fVal = 500;
					}
					else
					{
						if(fVal<0.01)			fVal = 0.01;
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
				m_clGridTeachingDispense.SetItemText(row, col, celData);
			}
			else
			{
				m_clGridTeachingDispense.SetItemBkColor(row, col,GRID_COLOR_SELECT);
			}
			m_clGridTeachingDispense.Invalidate();
		}
	}
}
void CMotorDlg3::OnDBClickedGridDispenseResol(NMHDR* pNMHDR, LRESULT* pResult)
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

	CString celData = m_clGridResolDispense.GetItemText(row, col);


	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		CString curStr = dlg.GetstrNum();

		double dVal = atof(curStr);

		celData.Format("%.4lf", dVal);

		m_clGridResolDispense.SetItemText(row, col, celData);
		m_clGridResolDispense.Invalidate();
	}

}
void CMotorDlg3::changeCamera()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)(AfxGetApp()->m_pMainWnd);
	pFrame->setCamDisplay(m_iSelCam,0);

	dispResolDataOnGrid();

	if (m_bCalcResol)
		changeCalcMode();
}


void CMotorDlg3::OnBnClickedRadioLens()
{
	UpdateData(true);
	changeCamera();
}

void CMotorDlg3::OnBnClickedRadioPcb()
{
	UpdateData(true);
	changeCamera();
}


void CMotorDlg3::OnBnClickedRadioCcd()
{
	UpdateData(true);
	changeCamera();
}

void CMotorDlg3::initMotorGrid()
{
	//CString tmpStr;
	//m_gridState.SetRedraw(FALSE);
	//for(int i=0;i<4;i++)
	//	m_gridState.SetColAlignment(i, 4);

	//m_gridState.SetColWidth(0,1500);
	//m_gridState.SetColWidth(1,2000);
	//m_gridState.SetColWidth(2,2100);
	//m_gridState.SetColWidth(3,2100);

	//sLangChange.LoadStringA(IDS_STRING1126);
	//m_gridState.SetTextMatrix(1, 0, sLangChange);	//Value
	//sLangChange.LoadStringA(IDS_STRING471);
	//m_gridState.SetTextMatrix(0, 1, sLangChange);	//Clean 현재 Cnt
	//sLangChange.LoadStringA(IDS_STRING469);
	//m_gridState.SetTextMatrix(0, 2, sLangChange);	//Clean 패드 크기 X(mm)
	//sLangChange.LoadStringA(IDS_STRING470);
	//m_gridState.SetTextMatrix(0, 3, sLangChange);	//Clean 패드 크기 Y(mm)

	//m_gridState.SetRedraw(TRUE);
	//m_gridState.Refresh();



	//m_gridMotor.SetRedraw(FALSE);
	//for(int i=0;i<7;i++){
	//	m_gridMotor.SetColAlignment(i, 4);
	//}

	//m_gridMotor.SetColWidth(0,1200);
	//m_gridMotor.SetColWidth(1,1076);
	//m_gridMotor.SetColWidth(2,1076);
	//m_gridMotor.SetColWidth(3,1076);
	//m_gridMotor.SetColWidth(4,1076);
	//m_gridMotor.SetColWidth(5,1076);
	//m_gridMotor.SetColWidth(6,1076);

	//
	//m_gridMotor.SetRedraw(TRUE);
	//m_gridMotor.Refresh();
}


void CMotorDlg3::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if(bShow)
	{
		CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

		m_iSelCam = pFrame->m_iCurCamNo = 1;

		changeCamera();
		UpdateData(false);

		ShowGridCtrl_Dispense();
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




void CMotorDlg3::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent==MOTOR_TIMER)
	{
		if (!timerRunFlag)
		{
			timerRunFlag = true;
			dispMotorStatus();

			timerRunFlag = false;
		}
		int m_MotorNum = m_iSelMotor;

		// JOG 이동 + 방향
		if(JogPlusflag == true && OLD_JogPlusflag == false)
			motor.JogMove(m_MotorNum, sysData.fMotorSpeed[m_MotorNum] * sysData.fMotorResol[m_MotorNum] * m_fMotorJogSpeed);
		else if(JogPlusflag == false && OLD_JogPlusflag == true)
			motor.JogStop(m_MotorNum);
		OLD_JogPlusflag = JogPlusflag;


		// JOG 이동 - 방향
		if(JogMinusflag == true && OLD_JogMinusflag == false)
			motor.JogMove(m_MotorNum, -sysData.fMotorSpeed[m_MotorNum] * sysData.fMotorResol[m_MotorNum]  * m_fMotorJogSpeed);
		else if(JogMinusflag== false && OLD_JogMinusflag == true)
			motor.JogStop(m_MotorNum);
		OLD_JogMinusflag = JogMinusflag;
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CMotorDlg3::dispMotorStatus()
{
	//CString str;
	//char sLog[100];
	double	motorPos = 0.0;
	TCHAR szLog[SIZE_OF_1K];

	int iIndex = 0;
	for (int i = Motor_PCB_X; i <= Motor_PCB_Z; i++)
	
	{
		iIndex = i;

		
		if ((i == Motor_Lens_Xt) || (i == Motor_PCB_Xt) || (i == Motor_PCB_Yt))		//스태핑 모터
			motorPos	= motor.GetCommandPos_Disp(i);
		else
			motorPos	= motor.GetEncoderPos_Disp(i);
		
		_stprintf_s(szLog, SIZE_OF_1K, _T("%.03f"), motorPos);
		m_clGridTeachingDispense.SetItemText(DispenseRow-1, iIndex+1, szLog);

		if ( motor.GetAmpFault(i) )
		{
			m_clGridTeachingDispense.SetItemBkColor(1,(iIndex+1),GRID_COLOR_RED);
			 
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
			m_clGridTeachingDispense.SetItemBkColor(1,(iIndex+1),GRID_COLOR_WHITE);
		} 

		if ( motor.GetNegaSensor(i) )
		{
			m_clGridTeachingDispense.SetItemBkColor(2,(iIndex+1),GRID_COLOR_RED);

			if(!delayDlg->IsWindowVisible())
			{
				if (i == Motor_PCB_Z)continue;
				//sTempLang.LoadStringA(IDS_STRING150);
				//sLangChange.Format(sTempLang, MotorName[i]);
 				//_stprintf_s(sLog, sLangChange);
				_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] - Limit 감지"), MotorName[i]);
				delayMsg(szLog, 3000, M_COLOR_RED);
			}
		}
		else
		{
			m_clGridTeachingDispense.SetItemBkColor(2,(iIndex+1),GRID_COLOR_WHITE);
		}

		if( motor.GetHomeSensor(i) )
			m_clGridTeachingDispense.SetItemBkColor(3,(iIndex+1),GRID_COLOR_GREEN);
		else
			m_clGridTeachingDispense.SetItemBkColor(3,(iIndex+1),GRID_COLOR_WHITE);

		if ( motor.GetPosiSensor(i) )
		{
			m_clGridTeachingDispense.SetItemBkColor(4,(iIndex+1),GRID_COLOR_RED);
			/*sTempLang.LoadStringA(IDS_STRING151);
			sLangChange.Format(sTempLang, MotorName[i]);
 			_stprintf_s(sLog, sLangChange);*/
			_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] + Limit 감지"), MotorName[i]);
			if(!delayDlg->IsWindowVisible())				delayMsg(szLog,3000,M_COLOR_RED);
		}
		else
		{
			m_clGridTeachingDispense.SetItemBkColor(4,(iIndex+1),GRID_COLOR_WHITE);
		}
		Sleep(1);
	}
	m_clGridTeachingDispense.Invalidate();
}



void CMotorDlg3::OnBnClickedButtonOriginAll()
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

void CMotorDlg3::OnBnClickedButtonServoOnAll()
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

void CMotorDlg3::OnBnClickedButtonServoOffAll()
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
			sprintf_s(dispStr, "All Motor Servo OFF ");
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

void CMotorDlg3::OnBnClickedButtonStopAll()
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
		_stprintf_s(dispStr, _T("All Motor Servo OFF."));
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


void CMotorDlg3::OnBnClickedButtonAlarmResetAll()
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


void CMotorDlg3::getResolDataOnGrid()
{
	CString sTemp="";
	
	sTemp = m_clGridResolDispense.GetItemText(1, 1);
	sysData.dCamResol[m_iSelCam].x = atof(sTemp);
	sTemp = m_clGridResolDispense.GetItemText(1, 2);
	sysData.dCamResol[m_iSelCam].y = atof(sTemp);
	sTemp = m_clGridResolDispense.GetItemText(1, 3);
	sysData.dCamAngle[m_iSelCam].x = atof(sTemp);
	sTemp = m_clGridResolDispense.GetItemText(1, 4);
	sysData.dCamAngle[m_iSelCam].y = atof(sTemp);
}


void CMotorDlg3::OnBnClickedButtonMotorOrigin()
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

	sprintf_s(dispStr, "%s Motor HomeSensor Complete", MotorName[m_iSelMotor]);
	pFrame->putListLog(dispStr);

	g_bMovingflag =false;
}

void CMotorDlg3::OnBnClickedButtonServoOn()
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

	g_bMovingflag = true;
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

void CMotorDlg3::OnBnClickedButtonSerboOff()
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
	sprintf_s(dispStr, "%s Motor Servo Off ", MotorName[m_MotorNum]);
	delayMsg(dispStr, 5000, M_COLOR_GREEN);

	if(!motor.AmpDisable(m_MotorNum))
	{
		sprintf_s(dispStr, "%s Motor Servo Off Move Error.", MotorName[m_MotorNum]);
		errMsg2(Task.AutoFlag, dispStr);
	}

	g_bMovingflag =false;
}

void CMotorDlg3::OnBnClickedButtonAlarmReset()
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

	int m_MotorNum = m_iSelMotor;
	if(!askMsg("Select Motor Alarm Reset ?"))
		return;

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


void CMotorDlg3::OnBnClickedRadioMotorSpeed1()
{
	m_fMotorJogSpeed = MOTOR_JOG_LOW;
	UpdateData(true);
}


void CMotorDlg3::OnBnClickedRadioMotorSpeed2()
{
	m_fMotorJogSpeed = MOTOR_JOG_MID;
	UpdateData(true);
}


void CMotorDlg3::OnBnClickedRadioMotorSpeed3()
{
	m_fMotorJogSpeed = MOTOR_JOG_HIGH;
	UpdateData(true);
}


void CMotorDlg3::OnBnClickedButtonJogPlus()
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


void CMotorDlg3::OnBnClickedButtonJogMinus()
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

void CMotorDlg3::OnBnClickedButtonJogStop()
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

void CMotorDlg3::OnBnClickedButtonMotorPosSave()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	//bool passFlag = password.m_bFlag;

	//if(passFlag == false)
	//{
	//	CString strTemp;
	//	CKeyPadDlg keyDlg;

	//	sLangChange.LoadStringA(IDS_STRING891);
	//	keyDlg.m_strKeyPad = sLangChange;	//"Password를 입력하세요."

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

	//if(passFlag)
	//{
	//	password.m_bFlag = true;
	//}
	//else
	//{
	//	sLangChange.LoadStringA(IDS_STRING892);
	//	errMsg2(Task.AutoFlag, sLangChange);	//"Password를 잘 못 입력했습니다."
	//	return;
	//}
	

	CString cellStr;

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
			cellStr = m_clGridTeachingDispense.GetItemText(5, iIndex+1);
			model.axis[i].m_dLimit_OK = (float)atof(cellStr);

			cellStr = m_clGridTeachingDispense.GetItemText(6, iIndex+1);
			model.axis[i].m_dLimit_Err = (float)atof(cellStr);

		}
		else
		{
			cellStr = m_clGridTeachingDispense.GetItemText(5, iIndex+1);
			sysData.fMotorSpeed[i] = (float)atof(cellStr);

			cellStr = m_clGridTeachingDispense.GetItemText(6, iIndex+1);
			sysData.fMotorAccTime[i] = (float)atof(cellStr);

			
		}
	

		cellStr = m_clGridTeachingDispense.GetItemText(7, iIndex+1);
		model.axis[i].pos[Com_Laser_Pos] = (atof(cellStr) + sysData.dDataset[i]);

		cellStr = m_clGridTeachingDispense.GetItemText(8, iIndex+1);
		model.axis[i].pos[Dispense_Pos] = (atof(cellStr) + sysData.dDataset[i]);

		cellStr = m_clGridTeachingDispense.GetItemText(9, iIndex+1);
		model.axis[i].pos[Laser_Pcb_Pos] = (atof(cellStr) + sysData.dDataset[i]);

		cellStr = m_clGridTeachingDispense.GetItemText(10, iIndex + 1);
		model.axis[i].pos[CompleteAlign_Pos] = (atof(cellStr) + sysData.dDataset[i]);

		cellStr = m_clGridTeachingDispense.GetItemText(11, iIndex + 1);
		model.axis[i].pos[PDispense_Pos] = (atof(cellStr) + sysData.dDataset[i]);

		cellStr = m_clGridTeachingDispense.GetItemText(12, iIndex + 1);
		model.axis[i].pos[Holder_Uv_Pos] = (atof(cellStr) + sysData.dDataset[i]);

		cellStr = m_clGridTeachingDispense.GetItemText(13, iIndex + 1);
		model.axis[i].pos[Dispense_Pos1] = (atof(cellStr) + sysData.dDataset[i]);

		cellStr = m_clGridTeachingDispense.GetItemText(14, iIndex + 1);
		model.axis[i].pos[Dispense_Pos2] = (atof(cellStr) + sysData.dDataset[i]);

		cellStr = m_clGridTeachingDispense.GetItemText(15, iIndex + 1);
		model.axis[i].pos[Dispense_Pos3] = (atof(cellStr) + sysData.dDataset[i]);

	}

	model.Save();
	sysData.Save();

	LogSave("Teach 저장");

	cellStr.Empty();
}


void CMotorDlg3::changeMotorNo(int motorNo)
{
	int j = m_iSelMotor + 1;

	for(int i=5; i <DispenseRow; i++)
	{
		m_clGridTeachingDispense.SetItemBkColor(i , (m_iSelMotor+1),GRID_COLOR_WHITE);
	}


	m_iSelMotor = motorNo;
	for(int i=5; i <DispenseRow; i++)
	{
		m_clGridTeachingDispense.SetItemBkColor(i , (m_iSelMotor+1),GRID_COLOR_SELECT);
	}
	m_clGridTeachingDispense.Invalidate();
}


BEGIN_EVENTSINK_MAP(CMotorDlg3, CDialogEx)

END_EVENTSINK_MAP()


void CMotorDlg3::DblClickMsflexgridMotor()
{
	
}

void CMotorDlg3::dispResolDataOnGrid()
{
	CString sTemp="";
	m_clGridResolDispense.SetItemText(0, 1, _T("RESOL X"));
	m_clGridResolDispense.SetItemText(0, 2, _T("RESOL Y"));
	m_clGridResolDispense.SetItemText(0, 3, "ANGLE X");
	m_clGridResolDispense.SetItemText(0, 4, "ANGLE Y");

	m_clGridResolDispense.SetItemText(1, 0, "PCB");

	sTemp.Format("%.4lf", sysData.dCamResol[m_iSelCam].x);
	m_clGridResolDispense.SetItemText(1, 1, sTemp);
	sTemp.Format("%.4lf", sysData.dCamResol[m_iSelCam].y);
	m_clGridResolDispense.SetItemText(1, 2, sTemp);
	sTemp.Format("%.4lf", sysData.dCamAngle[m_iSelCam].x);
	m_clGridResolDispense.SetItemText(1, 3, sTemp);
	sTemp.Format("%.4lf", sysData.dCamAngle[m_iSelCam].y);
	m_clGridResolDispense.SetItemText(1, 4, sTemp);
}


void CMotorDlg3::changeCalcMode()
{
	m_bFindTop		=	false;
	m_bFindBottom	=	false;
	m_bFindLeft		=	false;
	m_bFindRight	=	false;

	GetDlgItem(IDC_BUTTON_RESOLUTION)->EnableWindow(FALSE);

	if (m_bCalcResol)
	{
		GetDlgItem(IDC_STATIC_RESOLDISPENSE_GRID)->ShowWindow(true);
		GetDlgItem(IDC_BUTTON_RESOLUTION)->ShowWindow(true);
		m_clGridResolDispense.ShowWindow(SW_SHOW);
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
		GetDlgItem(IDC_STATIC_RESOLDISPENSE_GRID)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_RESOLUTION)->ShowWindow(false);
		m_clGridResolDispense.ShowWindow(SW_HIDE);

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


void CMotorDlg3::OnBnClickedCheckResolution()
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


void CMotorDlg3::DblClickMsflexgridResol()
{
	
}


void CMotorDlg3::drawResolBackGround()
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


void CMotorDlg3::getMarkAndMotor(int iPos)
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

	CString sMotorPos="";
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

void CMotorDlg3::OnBnClickedButtonResolution()
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
		m_clGridResolDispense.SetItemText(1, 1, sTemp);
		sTemp.Format("%.4lf", m_dTempResol.y);
		m_clGridResolDispense.SetItemText(1, 2, sTemp);
		sTemp.Format("%.4lf", m_dTempAngle.x);
		m_clGridResolDispense.SetItemText(1, 3, sTemp);
		sTemp.Format("%.4lf", m_dTempAngle.y);
		m_clGridResolDispense.SetItemText(1, 4, sTemp);

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

void CMotorDlg3::CheckVelLimit()
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


void CMotorDlg3::OnBnClickedButtonMotorVelSoftlimit()
{
	CheckVelLimit();
	MotorVellimitView();
}

void CMotorDlg3::MotorVellimitView()
{
	CString strTemp;
	CString temp;

	int iIndex;
	if(m_iVel_Limit ==1)
	{
		m_clGridTeachingDispense.SetItemText(5, 0, "OK Limit");
		m_clGridTeachingDispense.SetItemText(6, 0, "ERR Limit");

		for (int i = Motor_PCB_X; i <= Motor_PCB_Z; i++)
		
		{
			iIndex = i;

			temp.Format("%0.3f", model.axis[i].m_dLimit_OK);
			m_clGridTeachingDispense.SetItemText(5, iIndex+1, temp);

			temp.Format("%0.3f", model.axis[i].m_dLimit_Err);
			m_clGridTeachingDispense.SetItemText(6, iIndex+1, temp);
		}
	}
	else	// 속도 가속도
	{
		m_clGridTeachingDispense.SetItemText(5, 0, "속도(mm/s)");
		m_clGridTeachingDispense.SetItemText(6, 0, "가속도(sec)");
		for (int i = Motor_PCB_X; i <= Motor_PCB_Z; i++)
		
		{
			iIndex = i;

			temp.Format("%0.3f", sysData.fMotorSpeed[i]);
			m_clGridTeachingDispense.SetItemText(5, iIndex+1, temp);

			temp.Format("%.03f", sysData.fMotorAccTime[i]);
			m_clGridTeachingDispense.SetItemText(6, iIndex+1, temp);

		}
	}
}


void CMotorDlg3::OnBnClickedButtonTest2()
{
	if(Task.AutoFlag == 1) 
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	//if(Task.AutoFlag == 2)
	//{
	//	sLangChange.LoadStringA(IDS_STRING1468);
	//	delayMsg(sLangChange, 2000, M_COLOR_RED);// 일시 정지 중 사용 불가
	//	return;
	//}


	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;
	g_bMovingflag =true;
	int m_MotorNum = m_iSelMotor;
	CString temp;
	GetDlgItem(IDC_STATIC_MOTORSPEED)->GetWindowText(temp);
	double pos;
	pos = atof(temp);

	if ( pos > 3)	pos = 3;

	motor.MoveAxis(m_MotorNum, REL, -pos, 4, 0);				// 4: 조그 이동 속도..

	g_bMovingflag =false;
}


void CMotorDlg3::OnBnClickedButtonTest()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	//if(Task.AutoFlag == 2)
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
	int m_MotorNum = m_iSelMotor;
	if ( pos < 0)
	{
		sLangChange.LoadStringA(IDS_STRING1340);	//이동 거리 입력 값이 (-) 입니다
		errMsg2(0, sLangChange);
		return;
	}

	if ( pos > 3)	pos = 3;

	motor.MoveAxis(m_MotorNum, REL, +pos, 4, 0);				// 4: 조그 이동 속도..

	g_bMovingflag =false;
}


bool CMotorDlg3::registPatMark(int iCamNo, CRect rcBox)
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


void CMotorDlg3::OnBnClickedButtonGotoLensmotor()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	pFrame->m_bIsMotorMode = 0;
	pFrame->ctrlSubDlg(MOTOR_DLG);
}


void CMotorDlg3::OnStnClickedStaticMotorspeed()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		m_LabelMotorSpeed.SetText(dlg.GetstrNum());
	}
}


void CMotorDlg3::dispMotorPos()
{
	/*CString posStr;
	double pos;
*/

	/*m_gridMotor.SetRedraw(FALSE);

	int iIndex;
	for(int i=Motor_PCB_X;i<=Motor_PCB_Z;i++)
	{
		iIndex = i;

		getMotorPos(i, Contact_Pos, pos, true);
		posStr.Format("%0.3f", pos);
		m_gridMotor.SetTextMatrix(7, iIndex+1, posStr);

		getMotorPos(i, Calc_Pos, pos, true);
		posStr.Format("%0.3f", pos);
		m_gridMotor.SetTextMatrix(8, iIndex+1, posStr);

		getMotorPos(i, Dispense_Pos, pos, true);
		posStr.Format("%0.3f", pos);
		m_gridMotor.SetTextMatrix(9, iIndex+1, posStr);

		getMotorPos(i, CompleteAlign_Pos, pos, true);
		posStr.Format("%0.3f", pos);
		m_gridMotor.SetTextMatrix(10, iIndex+1, posStr);

	}

	m_gridMotor.SetRedraw(TRUE);
	m_gridMotor.Refresh();  */

	/*m_gridState.SetRedraw(FALSE);
	posStr.Format("%d", model.Cleancnt);
	m_gridState.SetTextMatrix(1, 1, posStr);

	posStr.Format("%0.3f", model.Cleanpad[0]);
	m_gridState.SetTextMatrix(1, 2, posStr);

	posStr.Format("%0.3f", model.Cleanpad[1]);
	m_gridState.SetTextMatrix(1, 3, posStr);

	m_gridState.SetRedraw(TRUE);
	m_gridState.Refresh();  */

}



void CMotorDlg3::OnMouseMove(UINT nFlags, CPoint point)
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


void CMotorDlg3::OnLButtonUp(UINT nFlags, CPoint point)
{
	JogMinusflag = false;
	JogPlusflag = false;

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMotorDlg3::OnBnClickedButtonGotoPcbmotor()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	pFrame->m_bIsMotorMode = 1;
	pFrame->ctrlSubDlg(MOTOR_DLG2);
}


void CMotorDlg3::DblClickMsflexgridState()
{
	//int iRow = m_gridState.GetMouseRow();
	//int iCol = m_gridState.GetMouseCol();

	//if ( iRow <= 0 || iCol <= 0 )	return;

	//if( iCol < 0 )
	//{
	//	CString cellStr;
	//	sLangChange.LoadStringA(IDS_STRING467);
	//	cellStr.Format(sLangChange);	//Clean 위치를 초기화 하시겠습니까?
	//	if( !askMsg(cellStr.GetBuffer(99)) )
	//	{
	//		return;
	//	}

	//	model.Cleancnt = 0;
	//}
	//else 
	//{
	//	CString sCellData = m_gridState.GetTextMatrix(iRow, iCol);

	//	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)sCellData);
	//	if ( dlg.DoModal() == IDOK )
	//	{
	//		m_gridState.SetTextMatrix(iRow, iCol, dlg.GetstrNum());
	//	}
	//}
}


void CMotorDlg3::OnBnClickedButtonEpoxyset()
{ 
	CEpoxyDlg EpoxyDlg;
	EpoxyDlg.DoModal();
}



void CMotorDlg3::OnBnClickedButtonGotoLenslaseralignmotor()
{
	// TODO: Add your control notification handler code here
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	pFrame->m_bIsMotorMode = 3;
	pFrame->ctrlSubDlg(MOTOR_DLG4);
}
