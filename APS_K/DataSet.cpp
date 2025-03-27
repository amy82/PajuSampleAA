// DataSet.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DataSet.h"


// CDataSet 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDataSet, CDialogEx)

CDataSet::CDataSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDataSet::IDD, pParent)
{
	m_iMotorSpeed = 0;
}

CDataSet::~CDataSet()
{
}

void CDataSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
//	DDX_Control(pDX, IDC_MSFLEXGRID_MOTOR, m_gridMotor);
	DDX_Control(pDX, IDC_STATIC_MOTOR_NAME, m_labelMotorName);
	DDX_Control(pDX, IDC_BUTTON_JOG_PLUS, m_JogPlus);
	DDX_Control(pDX, IDC_BUTTON_JOG_MINUS, m_JogMinus);
	DDX_Radio(pDX, IDC_RADIO_MOTOR_SPEED1, m_iMotorSpeed);

	DDX_Control(pDX, IDC_STATIC_MOTORSPEED, m_LabelMotorSpeed);
}


BEGIN_MESSAGE_MAP(CDataSet, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDataSet::OnBnClickedOk)
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_SAVE, &CDataSet::OnBnClickedButtonMotorSave)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_ORIGIN, &CDataSet::OnBnClickedButtonMotorOrigin)
	ON_BN_CLICKED(IDC_BUTTON_SERVO_ON, &CDataSet::OnBnClickedButtonServoOn)
	ON_BN_CLICKED(IDC_BUTTON_SERBO_OFF, &CDataSet::OnBnClickedButtonSerboOff)
	ON_BN_CLICKED(IDC_BUTTON_ALARM_RESET, &CDataSet::OnBnClickedButtonAlarmReset)
	ON_BN_CLICKED(IDC_BUTTON_TEST2, &CDataSet::OnBnClickedButtonTest2)
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CDataSet::OnBnClickedButtonTest)
	ON_BN_CLICKED(IDC_RADIO_MOTOR_SPEED1, &CDataSet::OnBnClickedRadioMotorSpeed1)
	ON_BN_CLICKED(IDC_RADIO_MOTOR_SPEED2, &CDataSet::OnBnClickedRadioMotorSpeed2)
	ON_BN_CLICKED(IDC_RADIO_MOTOR_SPEED3, &CDataSet::OnBnClickedRadioMotorSpeed3)
	ON_BN_CLICKED(IDC_BUTTON_JOG_MINUS, &CDataSet::OnBnClickedButtonJogMinus)
	ON_BN_CLICKED(IDC_BUTTON_JOG_STOP, &CDataSet::OnBnClickedButtonJogStop)
	ON_BN_CLICKED(IDC_BUTTON_JOG_PLUS, &CDataSet::OnBnClickedButtonJogPlus)
	ON_STN_CLICKED(IDC_STATIC_MOTORSPEED, &CDataSet::OnStnClickedStaticMotorspeed)

	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_DATASET_GRID, &CDataSet::OnDBClickedGridDataSet)
END_MESSAGE_MAP()


// CDataSet 메시지 처리기입니다.


void CDataSet::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


BOOL CDataSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();
//	initMotorGrid();
	InitGridCtrl_DataSet();
	setInterface();
	m_iSelMotor = 0;
	changeMotorNo(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void	CDataSet::InitGridCtrl_DataSet()
{
	CRect rect;
	CWnd *pWnd= (CWnd*)GetDlgItem(IDC_STATIC_DATASET_GRID); 
	DataSetRow = 4;//아래
	DataSetCol = MAX_MOTOR_NO+1;//옆
	int margin = 5;
	int gridHeight = 40;
	int gridWidth1 = 100;
	int gridWidth2 = 75;
	int totalWidth = gridWidth1+(gridWidth2*(DataSetCol-1));
	//
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = totalWidth +margin;
	rect.bottom = (gridHeight*DataSetRow) +margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.

	GetDlgItem(IDC_STATIC_DATASET_GRID)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGridDataSet.Create(rect, this, IDC_STATIC_DATASET_GRID, WS_TABSTOP | WS_VISIBLE);

	m_clGridDataSet.SetTextBkColor(GRID_COLOR_WHITE);
	m_clGridDataSet.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridDataSet.SetFixedTextColor(GRID_COLOR_WHITE);
	m_clGridDataSet.SetReference_Setting();
	m_clGridDataSet.EnableSelection(FALSE);
	m_clGridDataSet.SetRowCount(DataSetRow);
	m_clGridDataSet.SetColumnCount(DataSetCol);
	m_clGridDataSet.SetFixedRowCount(1);
	m_clGridDataSet.SetFixedColumnCount(1);

	CString tmpStr="";

	m_clGridDataSet.SetItemText(0, 0, "강제 원점");
	m_clGridDataSet.SetItemText(1, 0, "모터 기계치");
	m_clGridDataSet.SetItemText(2, 0, "모터 Display");
	m_clGridDataSet.SetItemText(3, 0, "강제 원점 값");
	//
	for(int i=0; i<MAX_MOTOR_NO; i++)
	{
		tmpStr.Format("%s" , MotorName[i]);
		m_clGridDataSet.SetItemText(0, i+1, tmpStr);
	}

	int i=0, j=0;
	for (i = 0; i < DataSetRow; i++)
	{
		m_clGridDataSet.SetRowHeight(i, gridHeight);
		
		for (j = 0; j < DataSetCol; j++)
		{
			m_clGridDataSet.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridDataSet.SetColumnWidth(j, gridWidth1);
				}else{
					m_clGridDataSet.SetColumnWidth(j, gridWidth2);
				}
			}			
		}
	}
	m_clGridDataSet.Invalidate();
}
void	CDataSet::ShowGridCtrl_DataSet()
{
	CString sTemp="";
	for(int i=0; i<MAX_MOTOR_NO;i++)
	{
		sTemp.Format("%.03f", sysData.dDataset[i]);
		m_clGridDataSet.SetItemText(3, i+1, sTemp);
	}
	m_clGridDataSet.Invalidate();
	m_fMotorJogSpeed = MOTOR_JOG_LOW;

	m_JogPlus.SetButtonStyle(0);
	m_JogMinus.SetButtonStyle(0);

	
	m_iMotorSpeed = 0;
}
void CDataSet::OnDBClickedGridDataSet(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
	
	int col = pNMGridView->iColumn;
	int row = pNMGridView->iRow;
	if(col<1 || row<0)										//JJH.	수정
		return;
	//if(col<1)		return;

	CString celData;

	if(row <=2)
	{
		changeMotorNo(col-1);
	}
	else if(row==3)
	{
		celData = m_clGridDataSet.GetItemText(row, col);

		CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
		if(dlg.DoModal() == IDOK)
		{
			CString curStr = dlg.GetstrNum();
			m_clGridDataSet.SetItemText(row, col, curStr);
		}
	}

}
void CDataSet::initMotorGrid()
{
	//CString tmpStr;

	//m_gridMotor.SetRedraw(FALSE);

	//m_gridMotor.SetRows(4);
	//m_gridMotor.SetCols(MAX_MOTOR_NO+1);


	//m_gridMotor.SetColWidth(0, 1600);
	//m_gridMotor.SetColAlignment(0, 4);
	//for(int i=1;i<MAX_MOTOR_NO+1;i++)
	//{
	//	m_gridMotor.SetColWidth(i, 1088);
	//	m_gridMotor.SetColAlignment(i, 4);
	//}

	//for(int i=0;i<4;i++)
	//	m_gridMotor.SetRowHeight(i,720);

	//sLangChange.LoadStringA(IDS_STRING1142);	//강제 원점
	//m_gridMotor.SetTextMatrix(0, 0, sLangChange);
	//sLangChange.LoadStringA(IDS_STRING1229);	//모터 기계치
	//m_gridMotor.SetTextMatrix(1, 0, sLangChange);
	//sLangChange.LoadStringA(IDS_STRING1221);	//모터 Display
	//m_gridMotor.SetTextMatrix(2, 0, sLangChange);
	//sLangChange.LoadStringA(IDS_STRING1144);	//강제 원점 값
	//m_gridMotor.SetTextMatrix(3, 0, sLangChange);

	//for(int i=0; i<MAX_MOTOR_NO; i++)
	//{
	//	m_gridMotor.SetTextMatrix(0, i+1, MotorName[i]);
	//}
	//m_gridMotor.SetRedraw(TRUE);
	//m_gridMotor.Refresh();
}


void CDataSet::setInterface()
{
	m_labelMotorName
		.SetBkColor(GRID_COLOR_GREEN)
		.SetTextColor(M_COLOR_BLACK)
		.SetFontBold(TRUE)
		.SetFontSize(24);

	m_LabelMotorSpeed
		.SetText("0.1")
		.SetBkColor(M_COLOR_WHITE);
	m_LabelMotorSpeed.Invalidate();

}

void CDataSet::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
	if(bShow)
	{
		//initMotorGrid();
		ShowGridCtrl_DataSet();
		//setInterface();  
		SetTimer(MOTOR_TIMER, 200, NULL);

	}
	else
	{
		KillTimer(MOTOR_TIMER);
	}
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CDataSet::OnTimer(UINT_PTR nIDEvent)
{
	CString str="";
	double	motorPos=0.0;

	//m_gridMotor.SetRedraw(FALSE);

	for(int i=0; i<MAX_MOTOR_NO; i++)
	{
	//	m_clGridDataSet.SetColumnCount(i+1);//m_clGridDataSet.SetCol(i+1);
	//	m_clGridDataSet.set
		if (i == Motor_PCB_Z || i == Motor_Lens_Z || i == Motor_Lens_Xt || i == Motor_Lens_Yt || i == Motor_PCB_Xt || i == Motor_PCB_Yt){
			motorPos	= motor.GetCommandPos(i);
		}else{
			motorPos = motor.GetEncoderPos(i);
		}
		str.Format("%.03f", motorPos);
		m_clGridDataSet.SetItemText(1, i+1, str);										// 기계치(순수 원점) 모터 좌표..

		if (i == Motor_PCB_Z || i == Motor_Lens_Z || i == Motor_Lens_Xt || i == Motor_Lens_Yt || i == Motor_PCB_Xt || i == Motor_PCB_Yt){
			motorPos = motor.GetCommandPos_Disp(i);
		}else{
			motorPos = motor.GetEncoderPos_Disp(i);
		}
		str.Format("%.03f", motorPos);
		m_clGridDataSet.SetItemText(2, i+1, str);										// Display 용 모터 좌표..
	}
	m_clGridDataSet.Invalidate();
	//m_gridMotor.SetRedraw(TRUE); 
	//m_gridMotor.Refresh();


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


	CDialogEx::OnTimer(nIDEvent);
}

BEGIN_EVENTSINK_MAP(CDataSet, CDialogEx)
	//ON_EVENT(CDataSet, IDC_MSFLEXGRID_MOTOR, DISPID_DBLCLICK, CDataSet::DblClickMsflexgridMotor, VTS_NONE)
END_EVENTSINK_MAP()


void CDataSet::DblClickMsflexgridMotor()
{
	/*int col = m_gridMotor.GetMouseCol();
	int row = m_gridMotor.GetMouseRow();

	if(col<1)		return;

	CString celData;

	if(row <=2)
	{
		changeMotorNo(col-1);
	}
	else if(row==3)
	{
		celData = m_gridMotor.GetTextMatrix(row, col);

		CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
		if(dlg.DoModal() == IDOK)
		{
			CString curStr = dlg.GetstrNum();
			m_gridMotor.SetTextMatrix(row, col, curStr);
		}
	}*/
}

void CDataSet::changeMotorNo(int motorNo)
{
	if(m_iSelMotor==motorNo)
		return;

	//	if(motorNo<Motor_Lens_X || motorNo>Motor_Syringe)
	//		return;

	//m_gridMotor.SetRedraw(FALSE);

	//m_gridMotor.SetCol(m_iSelMotor+1);
	//m_gridMotor.SetRow(1);
	m_clGridDataSet.SetItemBkColor(1, m_iSelMotor+1  , GRID_COLOR_WHITE);
	//m_gridMotor.SetRow(2);
	m_clGridDataSet.SetItemBkColor(2, m_iSelMotor+1  , GRID_COLOR_WHITE);
//	m_gridMotor.SetRow(3);
	m_clGridDataSet.SetItemBkColor(3, m_iSelMotor+1  , GRID_COLOR_WHITE);


	m_iSelMotor = motorNo;
//	m_labelMotorName.SetText(MotorName[m_iSelMotor]);

	//m_gridMotor.SetCol(motorNo+1);
	// 	m_gridMotor.SetCol(1);
	// 	m_gridMotor.SetCellBackColor(GRID_COLOR_SELECT);
	//m_gridMotor.SetRow(1);
	
	m_clGridDataSet.SetItemBkColor(1 ,motorNo+1 , GRID_COLOR_SELECT);
//	m_gridMotor.SetRow(2);
	m_clGridDataSet.SetItemBkColor(2 ,motorNo+1 , GRID_COLOR_SELECT);
	//m_gridMotor.SetRow(3);
	m_clGridDataSet.SetItemBkColor(3 ,motorNo+1 , GRID_COLOR_SELECT);
	
	m_clGridDataSet.Invalidate();
	//m_gridMotor.SetRedraw(TRUE);
	//m_gridMotor.Refresh();
}



void CDataSet::OnBnClickedButtonMotorSave()
{
	CString cellStr;

	for(int i=0;i<MAX_MOTOR_NO;i++)
	{
		cellStr = m_clGridDataSet.GetItemText(3, i+1);
		sysData.dDataset[i] = atof(cellStr);
	}
	sysData.Save();
	sysData.Load();

	CString sTemp;
	for(int i=0; i<MAX_MOTOR_NO;i++)
	{
		sTemp.Format("%.03f", sysData.dDataset[i]);
		m_clGridDataSet.SetItemText(3, i+1, sTemp);
	}
}


void CDataSet::OnBnClickedButtonMotorOrigin()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	char dispStr[100];

	if(Task.AutoFlag ==2)
	{
		sTempLang.LoadStringA(IDS_STRING115);
		sLangChange.Format(sTempLang, MotorName[m_iSelMotor]);
		_stprintf_s(dispStr, sLangChange);
		pFrame->putListLog(dispStr);

		return;
	}

	/* 이동중이면 Return */
	if(g_bMovingflag)
	{
		sTempLang.LoadStringA(IDS_STRING114);
		sLangChange.Format(sTempLang, MotorName[m_iSelMotor]);
		_stprintf_s(dispStr, sLangChange);
		pFrame->putListLog(dispStr);

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

void CDataSet::OnBnClickedButtonServoOn()
{
	if(Task.AutoFlag ==2) return;
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

void CDataSet::OnBnClickedButtonSerboOff()
{
	if(Task.AutoFlag ==2) return;
	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;

	sLangChange.LoadStringA(IDS_STRING1282);	//선택 모터 Servo Off 하시겠습니까?
	if(!askMsg(sLangChange))
		return;

	g_bMovingflag =true;

	char dispStr[100];
	sprintf_s(dispStr, "%s Motor Servo Off Start.", MotorName[m_iSelMotor]);
	delayMsg(dispStr, 5000, M_COLOR_GREEN);

	if(!motor.AmpDisable(m_iSelMotor))
	{
		sprintf_s(dispStr, "%s Motor Servo Off Move Error.", MotorName[m_iSelMotor]);
		errMsg2(Task.AutoFlag, dispStr);
	}

	g_bMovingflag =false;
}

void CDataSet::OnBnClickedButtonAlarmReset()
{
	if(!askMsg("Select Motor Alarm Reset ?"))
		return;

	char dispStr[100];
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


void CDataSet::OnBnClickedButtonTest2()
{
	if(Task.AutoFlag ==2) return;
	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;
	g_bMovingflag =true;
	

	CString temp;
	GetDlgItem(IDC_STATIC_MOTORSPEED)->GetWindowText(temp);
	double pos;
	pos = atof(temp);

	if ( pos > 5)	pos = 5;

	motor.MoveAxis(m_iSelMotor, REL, -pos, 4, 0);

	g_bMovingflag =false;
}


void CDataSet::OnBnClickedButtonTest()
{
	if(Task.AutoFlag ==2) return;

	if(g_bMovingflag)
		return;

	g_bMovingflag =true;

	CString temp;
	GetDlgItem(IDC_STATIC_MOTORSPEED)->GetWindowText(temp);
	double pos;
	pos = atof(temp);

	if ( pos > 5)	pos = 5;

	motor.MoveAxis(m_iSelMotor, REL, +pos, 4, 0);

	g_bMovingflag =false;
}

void CDataSet::OnBnClickedRadioMotorSpeed1()
{
	m_fMotorJogSpeed = MOTOR_JOG_LOW;
	UpdateData(true);
}


void CDataSet::OnBnClickedRadioMotorSpeed2()
{
	m_fMotorJogSpeed = MOTOR_JOG_MID;
	UpdateData(true);
}


void CDataSet::OnBnClickedRadioMotorSpeed3()
{
	m_fMotorJogSpeed = MOTOR_JOG_HIGH;
	UpdateData(true);
}


void CDataSet::OnBnClickedButtonJogPlus()
{
	if(!motor.GetAmpEnable(m_iSelMotor))
	{
		motor.m_bOrgFlag[m_iSelMotor] = false;
		sLangChange.LoadStringA(IDS_STRING393);
		errMsg2(Task.AutoFlag, sLangChange);	//AMP Servo 알람 발생. Jog 이동 동작 실패
		g_bMovingflag = false;
		return;
	}
	JogPlusflag = true;
}


void CDataSet::OnBnClickedButtonJogMinus()
{
	if(!motor.GetAmpEnable(m_iSelMotor))
	{
		motor.m_bOrgFlag[m_iSelMotor] = false;
		sLangChange.LoadStringA(IDS_STRING393);
		errMsg2(Task.AutoFlag, sLangChange);	//AMP Servo 알람 발생. Jog 이동 동작 실패
		g_bMovingflag = false;
		return;
	}
	JogMinusflag = true;
}

void CDataSet::OnBnClickedButtonJogStop()
{

	motor.JogStop(m_iSelMotor);
}


void CDataSet::OnStnClickedStaticMotorspeed()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		m_LabelMotorSpeed.SetText(dlg.GetstrNum());
	}
}
