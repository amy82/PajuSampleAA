// ResinDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AA Bonder.h"
#include "AA BonderDlg.h"
#include "ResinDlg.h"
#include "afxdialogex.h"


#include "GetNumDlg.h"
#include "vision.h"
#include "MotorSet.h"
#include "DioControl.h"
#include "DataHandler.h"

#include "MIU/LPMC500DLLEx.h"
#include "DelayMsgDlg.h"

/* Class */
extern	CVision			vision;
extern	CMotorSet		motor;
extern	CDioControl		Dio;
extern	CModelData		model;
extern	CSystemData		sysData;

extern	CTask			Task;

extern  CDelayMsgDlg*	delayDlg;


extern	bool JogPlusflag;
extern	bool JogMinusflag;
extern	bool g_bMovingflag;
// CResinDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CResinDlg, CDialogEx)

	CResinDlg::CResinDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CResinDlg::IDD, pParent)
	
{

	m_iSelArea		= 0;
	m_iSelMoveType	= 0;
	m_iSelMotor		= Motor_PCB_TH;
	m_iCamNo = 1;
	//  m_bResinPara = 0;
	m_iSelType_EpoxyCalc = 0;
}

CResinDlg::~CResinDlg()
{
}

void CResinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_LED, m_sliderLed);
	DDX_Radio(pDX, IDC_RADIO_SELAREA1, m_iSelArea);
	DDX_Radio(pDX, IDC_RADIO_POS, m_iSelMoveType);
	DDX_Control(pDX, IDC_MSFLEXGRID_MOTOR, m_gridMotor);
	DDX_Control(pDX, IDC_STATIC_MOTOR_NAME, m_labelMotorName);
	DDX_Control(pDX, IDC_MSFLEXGRID_RESIN, m_gridResin);
	DDX_Control(pDX, IDC_BUTTON_MINUS_X, m_JogMinus);
	DDX_Control(pDX, IDC_BUTTON_PLUS_X, m_JogPlus);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_ALIGN, m_btnAlignPos);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_EMISSION, m_btnEmissionPos);
	DDX_Control(pDX, IDC_BUTTON_RESIN_INSP, m_btnInspPos);
	DDX_Control(pDX, IDC_BUTTON_SYRINGE_OFF, m_btnSyringeOff);
	DDX_Control(pDX, IDC_BUTTON_SYRINGE_ON, m_btnSyringeOn);
	DDX_Control(pDX, IDC_BUTTON_DISCHARGE_OFF, m_btnDischargeOff);
	DDX_Control(pDX, IDC_BUTTON_DISCHARGE_ON, m_btnDischargeOn);
	//	DDX_Control(pDX, IDC_BUTTON_RESIN_INSPECT, m_btnResinInsptect);
	DDX_Radio(pDX, IDC_RADIO_PCB_ALIGN, m_iCamNo);
	//  DDX_Check(pDX, IDC_CHECK_RESIN_DRAW, m_bResinPara);
	DDX_Check(pDX, IDC_CHECK_RESIN_DRAW, m_bResinPara);
	DDX_Control(pDX, IDC_BUTTON_EPOXY_CAL, m_btnEpoxyCalPos);
	DDX_Control(pDX, IDC_BUTTON_EPOXY_CAL_INSP, m_btnEpoxyCalInspPos);

	DDX_Check(pDX, IDC_CHECK_RESIN_INSP_DISP, m_bResinInspDIsp);

	DDX_Check(pDX, IDC_CHECK_EPOXY_CALC, m_bCalc_Epoxy_Pos);
	DDX_Radio(pDX, IDC_RADIO_SEL_TYPE_EPOXY_CALC, m_iSelType_EpoxyCalc);
}


BEGIN_MESSAGE_MAP(CResinDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CResinDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CResinDlg::OnBnClickedCancel)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_PARA_SAVE, &CResinDlg::OnBnClickedButtonParaSave)
	ON_BN_CLICKED(IDC_BUTTON_BOX_UP, &CResinDlg::OnBnClickedButtonBoxUp)
	ON_BN_CLICKED(IDC_BUTTON_BOX_DOWN, &CResinDlg::OnBnClickedButtonBoxDown)
	ON_BN_CLICKED(IDC_BUTTON_BOX_LEFT, &CResinDlg::OnBnClickedButtonBoxLeft)
	ON_BN_CLICKED(IDC_BUTTON_BOX_RIGHT, &CResinDlg::OnBnClickedButtonBoxRight)
	ON_BN_CLICKED(IDC_BUTTON_BOX_SPEED, &CResinDlg::OnBnClickedButtonBoxSpeed)
	ON_BN_CLICKED(IDC_RADIO_POS, &CResinDlg::OnBnClickedRadioPos)
	ON_BN_CLICKED(IDC_RADIO_SIZE, &CResinDlg::OnBnClickedRadioSize)
	ON_BN_CLICKED(IDC_RADIO_SELAREA1, &CResinDlg::OnBnClickedRadioSelarea1)
	ON_BN_CLICKED(IDC_RADIO_SELAREA2, &CResinDlg::OnBnClickedRadioSelarea2)
	ON_BN_CLICKED(IDC_RADIO_SELAREA3, &CResinDlg::OnBnClickedRadioSelarea3)
	ON_BN_CLICKED(IDC_RADIO_SELAREA4, &CResinDlg::OnBnClickedRadioSelarea4)
	ON_BN_CLICKED(IDC_BUTTON_LIVEMODE, &CResinDlg::OnBnClickedButtonLivemode)
	ON_BN_CLICKED(IDC_BUTTON_IMG_LOAD, &CResinDlg::OnBnClickedButtonImgLoad)
	ON_BN_CLICKED(IDC_BUTTON_IMG_SAVE, &CResinDlg::OnBnClickedButtonImgSave)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_SAVE, &CResinDlg::OnBnClickedButtonMotorSave)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_RESIN_INSP, &CResinDlg::OnBnClickedButtonResinInsp)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_ALIGN, &CResinDlg::OnBnClickedButtonMotorAlign)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_EMISSION, &CResinDlg::OnBnClickedButtonMotorEmission)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_SPEED, &CResinDlg::OnBnClickedButtonMotorSpeed)
	ON_BN_CLICKED(IDC_BUTTON_SYRINGE_ON, &CResinDlg::OnBnClickedButtonSyringeOn)
	ON_BN_CLICKED(IDC_BUTTON_SYRINGE_OFF, &CResinDlg::OnBnClickedButtonSyringeOff)
	ON_BN_CLICKED(IDC_BUTTON_DISCHARGE_ON, &CResinDlg::OnBnClickedButtonDischargeOn)
	ON_BN_CLICKED(IDC_BUTTON_DISCHARGE_OFF, &CResinDlg::OnBnClickedButtonDischargeOff)
	ON_BN_CLICKED(IDC_BUTTON_PLUS_X, &CResinDlg::OnBnClickedButtonPlusX)
	ON_BN_CLICKED(IDC_BUTTON_MINUS_X, &CResinDlg::OnBnClickedButtonMinusX)
	ON_BN_CLICKED(IDC_BUTTON_RESIN_DRAW, &CResinDlg::OnBnClickedButtonResinDraw)
	ON_BN_CLICKED(IDC_RADIO_PCB_ALIGN, &CResinDlg::OnBnClickedRadioPcbAlign)
	ON_BN_CLICKED(IDC_RADIO_EPOXY, &CResinDlg::OnBnClickedRadioEpoxy)
	ON_BN_CLICKED(IDC_CHECK_RESIN_DRAW, &CResinDlg::OnBnClickedCheckResinDraw)
	ON_BN_CLICKED(IDC_BUTTON_RESIN_INSPECT, &CResinDlg::OnBnClickedButtonResinInspect)
	ON_BN_CLICKED(IDC_BUTTON_EPOXY_CAL, &CResinDlg::OnBnClickedButtonEpoxyCal)
	ON_BN_CLICKED(IDC_BUTTON_EPOXY_CAL_INSP, &CResinDlg::OnBnClickedButtonEpoxyCalInsp)
	ON_BN_CLICKED(IDC_CHECK_RESIN_INSP_DISP, &CResinDlg::OnBnClickedCheckResinInspDisp)
	ON_BN_CLICKED(IDC_BUTTON_EPOXY_CALC2, &CResinDlg::OnBnClickedButtonEpoxyCalc2)
	ON_BN_CLICKED(IDC_CHECK_EPOXY_CALC, &CResinDlg::OnBnClickedCheckEpoxyCalc)
	ON_BN_CLICKED(IDC_RADIO_SEL_TYPE_EPOXY_CALC, &CResinDlg::OnBnClickedRadioSelTypeEpoxyCalc)
	ON_BN_CLICKED(IDC_RADIO_SEL_TYPE_EPOXY_CALC2, &CResinDlg::OnBnClickedRadioSelTypeEpoxyCalc2)
	ON_BN_CLICKED(IDC_BUTTON_FIND_EPOXY_POINT, &CResinDlg::OnBnClickedButtonFindEpoxyPoint)
END_MESSAGE_MAP()


// CResinDlg 메시지 처리기입니다.
BOOL CResinDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	setInterface();
	DrowBox =0;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CResinDlg::OnBnClickedOk(){}
void CResinDlg::OnBnClickedCancel(){}


void CResinDlg::setInterface()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	WINDOWPLACEMENT wndpl;
	this->GetWindowPlacement(&wndpl);

	wndpl.rcNormalPosition = pFrame->m_rectCamDispPos2;
	wndpl.rcNormalPosition.top -= SUB_DLG_OFFSET_Y;
	wndpl.rcNormalPosition.bottom = MAIN_DLG_SIZE_Y-5;
	this->MoveWindow(&wndpl.rcNormalPosition);

	m_rArea[0] = model.m_rResinInspArea[0];
	m_rArea[1] = model.m_rResinInspArea[1];
	m_rArea[2] = model.m_rResinInspArea[2];
	m_rArea[3] = model.m_rResinInspArea[3];

	m_iMoveSpeed = 10;

	CString strTemp;
	m_sliderLed.SetRange(0, 255);
	m_sliderLed.SetTicFreq(32);
	m_sliderLed.SetPos(model.m_iLedValue[CAM3]);
	strTemp.Format("%d", model.m_iLedValue[CAM3]);
	GetDlgItem(IDC_EDIT_LED)->SetWindowText(strTemp);
	strTemp.Format("1.0");
	GetDlgItem(IDC_EDIT_MOVE_VAL)->SetWindowText(strTemp);

	CheckJogMotorSpeed();
	m_JogPlus.SetButtonStyle(0);
	m_JogMinus.SetButtonStyle(0);

	m_labelMotorName
		.SetBkColor(GRID_COLOR_SELECT)
		.SetTextColor(M_COLOR_BLACK)
		.SetFontBold(TRUE)
		.SetFontSize(24);
}

void CResinDlg::dispData()
{
	double pos;
	CString celData;

	m_bResinPara = sysData.bResinflag;
	checkResinpara();

	celData.Format("%0.3f", model.m_dResinInspOffset[0].x);
	GetDlgItem(IDC_EDIT_RESIN_OFFSET_X_INSIDE)->SetWindowText(celData);
	celData.Format("%0.3f", model.m_dResinInspOffset[0].y);
	GetDlgItem(IDC_EDIT_RESIN_OFFSET_Y_INSIDE)->SetWindowText(celData);

	celData.Format("%0.3f", model.m_dResinInspOffset[1].x);
	GetDlgItem(IDC_EDIT_RESIN_OFFSET_X_OUTSIDE)->SetWindowText(celData);
	celData.Format("%0.3f", model.m_dResinInspOffset[1].y);
	GetDlgItem(IDC_EDIT_RESIN_OFFSET_Y_OUTSIDE)->SetWindowText(celData);

	celData.Format("%d", model.m_iResinInspLimit);
	GetDlgItem(IDC_EDIT_RESIN_INSP_LIMIT)->SetWindowText(celData);


	celData.Format("%0.3f", sysData.dResin_speed);
	GetDlgItem(IDC_EDIT_RESIN_SPEED)->SetWindowText(celData);
	celData.Format("%d", sysData.iResin_delay_start);
	GetDlgItem(IDC_EDIT_RESIN_START)->SetWindowText(celData);
	celData.Format("%0.3f", sysData.fResin_dist_end);
	GetDlgItem(IDC_EDIT_RESIN_END)->SetWindowText(celData);
	celData.Format("%d", sysData.iResin_delay_start2);
	GetDlgItem(IDC_EDIT_RESIN_START2)->SetWindowText(celData);
	celData.Format("%0.3f", sysData.fResin_dist_end2);
	GetDlgItem(IDC_EDIT_RESIN_END2)->SetWindowText(celData);

	m_sliderLed.SetPos(model.m_iLedValue[CAM3]);
	celData.Format("%d", model.m_iLedValue[CAM3]);
	GetDlgItem(IDC_EDIT_LED)->SetWindowText(celData);

	celData.Format("%.03f", model.m_ResinDrawSize.x);
	m_gridResin.SetTextMatrix(1, 1, celData);

	celData.Format("%.03f", model.m_ResinDrawSize.y);
	m_gridResin.SetTextMatrix(1, 2, celData);


	m_gridMotor.SetRedraw(false);

	for(int i=Motor_PCB_X; i<=Motor_Syringe; i++)
	{
		if(getMotorPos(i, Align_Pos, pos))
		{
			celData.Format("%.03f", pos);
			m_gridMotor.SetTextMatrix(i+1-Motor_PCB_X, 2, celData);
		}

		if(getMotorPos(i, Epoxy_Pos, pos))
		{
			celData.Format("%.03f", pos);
			m_gridMotor.SetTextMatrix(i+1-Motor_PCB_X, 3, celData);
		}

		if(getMotorPos(i, Bonding_Pos, pos))
		{
			celData.Format("%.03f", pos);
			m_gridMotor.SetTextMatrix(i+1-Motor_PCB_X, 4, celData);
		}
	}

	m_gridMotor.SetRow(4);
	m_gridMotor.SetCol(4);
	m_gridMotor.SetCellBackColor(GRID_COLOR_SPARE_MOTOR);


	m_gridMotor.SetRedraw(TRUE);
	m_gridMotor.Refresh();
	UpdateData(false);
}

void CResinDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow)
	{
		m_iCamNo = 0;
		m_iImageIndex = 0;

		initResinGrid();
		initMotorGrid();

		ctrlLiveButton();

		m_iSelArea = 0;
		dispAreaPos();

		dispData();
		changeMotorNo(Motor_PCB_X);

		changeColorDischargeBtn();

		m_bCalc_Epoxy_Pos = FALSE;
		m_iBase_X = model.m_iBase_Epoxy_X;
		m_iBase_Y = model.m_iBase_Epoxy_Y;
		m_dOffset_X = model.m_dOffset_Epoxy_X;
		m_dOffset_Y = model.m_dOffset_Epoxy_Y;

		m_rcArea_EpoxyCalc = model.m_rcArea_EpoxyCalc;

		putEpoxyCalcData();
		showEpoxyCalcControl();
		UpdateData(false);

		timerRunFlag = false;
		SetTimer(RESIN_TIMER, 200, NULL);
	}
	else
	{
		CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

		KillTimer(RESIN_TIMER);

		vision.clearOverlay(CAM3);
		vision.drawOverlay(CAM3);

		pFrame->m_bMeasureDist = FALSE;
		pFrame->UpdateData(false);

		pFrame->m_rBox.left = 0;
		pFrame->m_rBox.top = 0;
		pFrame->m_rBox.right = 0;
		pFrame->m_rBox.bottom = 0;
	}
}


void CResinDlg::dispAreaPos()
{
	CString strTemp;

	vision.clearOverlay(CAM3);

	switch (m_iSelArea)
	{
	case 0:
		vision.boxlist[CAM3].addList(m_rArea[0], PS_SOLID, M_COLOR_BLUE);
		break;						 
	case 1:
		vision.boxlist[CAM3].addList(m_rArea[1], PS_SOLID, M_COLOR_BLUE);
		break;						 
	case 2:
		vision.boxlist[CAM3].addList(m_rArea[2], PS_SOLID, M_COLOR_BLUE);
		break;						 
	case 3:
		vision.boxlist[CAM3].addList(m_rArea[3], PS_SOLID, M_COLOR_BLUE);
		break;
	}

	strTemp.Format("AREA LEFT        [ %d ]", m_rArea[m_iSelArea].left);
	vision.textlist[CAM3].addList((CAM_SIZE_X-200), 20, strTemp, M_COLOR_WHITE, 17, 7, "Arial Black");

	strTemp.Format("AREA TOP         [ %d ]", m_rArea[m_iSelArea].top);
	vision.textlist[CAM3].addList((CAM_SIZE_X-200), 40, strTemp, M_COLOR_WHITE, 17, 7, "Arial Black");

	strTemp.Format("AREA RIGHT     [ %d ]", m_rArea[m_iSelArea].right);
	vision.textlist[CAM3].addList((CAM_SIZE_X-200), 60, strTemp, M_COLOR_WHITE, 17, 7, "Arial Black");

	strTemp.Format("AREA BOTTOM [ %d ]", m_rArea[m_iSelArea].bottom);
	vision.textlist[CAM3].addList((CAM_SIZE_X-200), 80, strTemp, M_COLOR_WHITE, 17, 7, "Arial Black");

	vision.drawOverlay(CAM3);

	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	pFrame->m_rBox = m_rArea[m_iSelArea];
}


void CResinDlg::OnBnClickedButtonParaSave()
{
	CString strTemp;
	
	sysData.bResinflag = m_bResinPara;
	GetDlgItem(IDC_EDIT_RESIN_SPEED)->GetWindowText(strTemp);
	sysData.dResin_speed = atof(strTemp);
	GetDlgItem(IDC_EDIT_RESIN_START)->GetWindowText(strTemp);
	sysData.iResin_delay_start = atoi(strTemp);
	GetDlgItem(IDC_EDIT_RESIN_END)->GetWindowText(strTemp);
	sysData.fResin_dist_end = (float)atof(strTemp);
	GetDlgItem(IDC_EDIT_RESIN_START2)->GetWindowText(strTemp);
	sysData.iResin_delay_start2 = atoi(strTemp);
	GetDlgItem(IDC_EDIT_RESIN_END2)->GetWindowText(strTemp);
	sysData.fResin_dist_end2 = (float)atof(strTemp);
	sysData.Save();


	GetDlgItem(IDC_EDIT_LED)->GetWindowText(strTemp);
	model.m_rResinInspArea[m_iSelArea] = m_rArea[m_iSelArea];
	model.m_iLedValue[CAM3] = atoi(strTemp);

	strTemp = m_gridResin.GetTextMatrix(1, 1);
	model.m_ResinDrawSize.x = (atof)(strTemp);

	strTemp = m_gridResin.GetTextMatrix(1, 2);
	model.m_ResinDrawSize.y = (atof)(strTemp);

	GetDlgItem(IDC_EDIT_RESIN_OFFSET_X_INSIDE)->GetWindowText(strTemp);
	model.m_dResinInspOffset[0].x = atof(strTemp);
	GetDlgItem(IDC_EDIT_RESIN_OFFSET_Y_INSIDE)->GetWindowText(strTemp);
	model.m_dResinInspOffset[0].y = atof(strTemp);

	GetDlgItem(IDC_EDIT_RESIN_OFFSET_X_OUTSIDE)->GetWindowText(strTemp);
	model.m_dResinInspOffset[1].x = (float)atof(strTemp);
	GetDlgItem(IDC_EDIT_RESIN_OFFSET_Y_OUTSIDE)->GetWindowText(strTemp);
	model.m_dResinInspOffset[1].y = atof(strTemp);

	GetDlgItem(IDC_EDIT_RESIN_INSP_LIMIT)->GetWindowText(strTemp);
	model.m_iResinInspLimit = atoi(strTemp);

	getEpoxyCalcData();

	model.Save();
}


void CResinDlg::OnBnClickedButtonBoxUp()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	/* 이동 */
	if (m_iSelMoveType==0)
	{
		m_rArea[m_iSelArea].top		-= m_iMoveSpeed;
		m_rArea[m_iSelArea].bottom	-= m_iMoveSpeed;
	}
	/* 크기 */
	else
	{
		m_rArea[m_iSelArea].bottom	-= m_iMoveSpeed;
	}

	if (m_rArea[m_iSelArea].top	<1)
	{
		m_rArea[m_iSelArea].top		= 1;
		m_rArea[m_iSelArea].bottom	= 1 + m_rcFixedBox.Height();
	}


	dispAreaPos();

	pFrame->m_rBox = m_rcFixedBox = m_rArea[m_iSelArea];
}


void CResinDlg::OnBnClickedButtonBoxDown()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	/* 이동 */
	if (m_iSelMoveType==0)
	{
		m_rArea[m_iSelArea].top		+= m_iMoveSpeed;
		m_rArea[m_iSelArea].bottom	+= m_iMoveSpeed;
	}
	/* 크기 */
	else
	{
		m_rArea[m_iSelArea].bottom	+= m_iMoveSpeed;
	}

	if (m_rArea[m_iSelArea].bottom>CAM_SIZE_Y-1)
	{
		m_rArea[m_iSelArea].bottom	= CAM_SIZE_Y - 1;
		m_rArea[m_iSelArea].top		= m_rArea[m_iSelArea].bottom - m_rcFixedBox.Height();
	}


	dispAreaPos();

	pFrame->m_rBox = m_rcFixedBox = m_rArea[m_iSelArea];
}


void CResinDlg::OnBnClickedButtonBoxLeft()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	/* 이동 */
	if (m_iSelMoveType==0)
	{
		m_rArea[m_iSelArea].left	-= m_iMoveSpeed;
		m_rArea[m_iSelArea].right	-= m_iMoveSpeed;
	}
	/* 크기 */
	else
	{
		m_rArea[m_iSelArea].right	-= m_iMoveSpeed;
	}

	if (m_rArea[m_iSelArea].left<1)
	{
		m_rArea[m_iSelArea].left	= 1;
		m_rArea[m_iSelArea].right	= 1 + m_rcFixedBox.Width();
	}


	dispAreaPos();

	pFrame->m_rBox = m_rcFixedBox = m_rArea[m_iSelArea];
}


void CResinDlg::OnBnClickedButtonBoxRight()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;


	/* 이동 */
	if (m_iSelMoveType==0)
	{
		m_rArea[m_iSelArea].left	+= m_iMoveSpeed;
		m_rArea[m_iSelArea].right	+= m_iMoveSpeed;
	}
	/* 크기 */
	else
	{
		m_rArea[m_iSelArea].right	+= m_iMoveSpeed;
	}

	if (m_rArea[m_iSelArea].right>CAM_SIZE_X-1)
	{
		m_rArea[m_iSelArea].right	= CAM_SIZE_X - 1;
		m_rArea[m_iSelArea].left	= m_rArea[m_iSelArea].right - m_rcFixedBox.Width();
	}


	dispAreaPos();

	pFrame->m_rBox = m_rcFixedBox = m_rArea[m_iSelArea];
}


void CResinDlg::OnBnClickedButtonBoxSpeed()
{
	CString strTemp;
	GetDlgItem(IDC_BUTTON_BOX_SPEED)->GetWindowText(strTemp);

	if (strTemp=="10")
	{
		m_iMoveSpeed = 1;
		GetDlgItem(IDC_BUTTON_BOX_SPEED)->SetWindowText("1");
	}
	else
	{
		m_iMoveSpeed = 10;
		GetDlgItem(IDC_BUTTON_BOX_SPEED)->SetWindowText("10");
	}
}


void CResinDlg::OnBnClickedRadioPos()
{
	UpdateData(true);
}


void CResinDlg::OnBnClickedRadioSize()
{
	UpdateData(true);
}


void CResinDlg::OnBnClickedRadioSelarea1()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	pFrame->m_rBox.left = 0;
	pFrame->m_rBox.top = 0;
	pFrame->m_rBox.right = 0;
	pFrame->m_rBox.bottom = 0;

	m_rArea[0] = model.m_rResinInspArea[0];

	UpdateData(true);
	dispAreaPos();
}


void CResinDlg::OnBnClickedRadioSelarea2()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	pFrame->m_rBox.left = 0;
	pFrame->m_rBox.top = 0;
	pFrame->m_rBox.right = 0;
	pFrame->m_rBox.bottom = 0;

	m_rArea[1] = model.m_rResinInspArea[1];

	UpdateData(true);
	dispAreaPos();


#ifndef		ON_LINE_MODE

	int tmpIndex;

	for(int i=1; i<1087; i++)
	{
		tmpIndex = m_iImageIndex + i;
		tmpIndex = tmpIndex % 1086;


		CString FileName;
		FileName.Format("%s\\(%d).bmp", IMG_DIR, tmpIndex);
		vision.loadImage(CAM2, FileName);


		bool rtn = pFrame->_inspResign(0, m_bResinInspDIsp ? 2 : 1);
		pFrame->putListLog(FileName);
		
		vision.textlist[CAM2].addList(150, 20, FileName, M_COLOR_RED, 17, 10, "Arial");

		if(rtn)			vision.textlist[CAM2].addList(600, 720, "O K", M_COLOR_GREEN, 30, 15, "Arial");
		else			vision.textlist[CAM2].addList(600, 720, "N G", M_COLOR_RED, 30, 15, "Arial");

		vision.drawOverlay(CAM2);

		checkMessage();
		checkMessage();
		checkMessage();
		checkMessage();
		checkMessage();
		checkMessage();
		checkMessage();
		checkMessage();
		checkMessage();


		if(!rtn)
			break;
	}

	m_iImageIndex = tmpIndex;
#endif
}


void CResinDlg::OnBnClickedRadioSelarea3()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	pFrame->m_rBox.left = 0;
	pFrame->m_rBox.top = 0;
	pFrame->m_rBox.right = 0;
	pFrame->m_rBox.bottom = 0;

	m_rArea[2] = model.m_rResinInspArea[2];

	UpdateData(true);
	dispAreaPos();
}


void CResinDlg::OnBnClickedRadioSelarea4()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	pFrame->m_rBox.left = 0;
	pFrame->m_rBox.top = 0;
	pFrame->m_rBox.right = 0;
	pFrame->m_rBox.bottom = 0;

	m_rArea[3] = model.m_rResinInspArea[3];

	UpdateData(true);
	dispAreaPos();


#ifndef		ON_LINE_MODE

	m_iImageIndex--;

	if(m_iImageIndex<1)
		m_iImageIndex = 1087;

	CString FileName;
	FileName.Format("%s\\(%d).bmp", IMG_DIR, m_iImageIndex);

	vision.loadImage(CAM2, FileName);


	bool rtn = pFrame->_inspResign(0, m_bResinInspDIsp ? 2 : 1);


	vision.textlist[CAM2].addList(150, 20, FileName, M_COLOR_RED, 17, 10, "Arial");

	if(rtn)
		vision.textlist[CAM2].addList(600, 720, "O K", M_COLOR_GREEN, 30, 15, "Arial");
	else
	{
		vision.textlist[CAM2].addList(600, 720, "N G", M_COLOR_RED, 30, 15, "Arial");
	}
	vision.drawOverlay(CAM2);
#endif
}

void CResinDlg::ctrlLiveButton()
{
	if (vision.getLiveMode())
		GetDlgItem(IDC_BUTTON_LIVEMODE)->SetWindowText("동영상");
	else
		GetDlgItem(IDC_BUTTON_LIVEMODE)->SetWindowText("정지영상");
}

void CResinDlg::OnBnClickedButtonLivemode()
{
	if(vision.getLiveMode())
		vision.setLiveMode(0);
	else
		vision.setLiveMode(1);

	ctrlLiveButton();
}


void CResinDlg::OnBnClickedButtonImgLoad()
{
	if(m_iCamNo==0)
		vision.loadImageonExplorer(CAM2);
	else
		vision.loadImageonExplorer(CAM3);

	ctrlLiveButton();
}


void CResinDlg::OnBnClickedButtonImgSave()
{

	int liveMode = vision.getLiveMode();

	if(m_iCamNo==0)
		vision.saveImageonExplorer(CAM2);
	else
		vision.saveImageonExplorer(CAM3);


	vision.setLiveMode(liveMode);
}


void CResinDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CString strTemp;

	if (nSBCode<=5)
	{
		strTemp.Format("%d", m_sliderLed.GetPos());
		GetDlgItem(IDC_EDIT_LED)->SetWindowText(strTemp);

		Dio.ctrlLedVolume(1+m_iCamNo, m_sliderLed.GetPos());
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CResinDlg::initResinGrid()
{
	CString strTemp;

	m_gridResin.SetRows(2);
	m_gridResin.SetCols(3);

	m_gridResin.SetColAlignment(0, 4);
	m_gridResin.SetColAlignment(1, 4);
	m_gridResin.SetColAlignment(2, 4);

	m_gridResin.SetColWidth(0,1450);
	m_gridResin.SetColWidth(1,2350);
	m_gridResin.SetColWidth(2,2350);

	m_gridResin.SetTextMatrix(0, 1, "Size X");
	m_gridResin.SetTextMatrix(0, 2, "Size Y");


	m_gridResin.SetTextMatrix(1, 0, "Resin Draw(mm)");

	m_gridResin.SetRowHeight(1, 510);
}

void CResinDlg::initMotorGrid()
{
	CString tmpStr;

	m_gridMotor.SetRedraw(FALSE);

	m_gridMotor.SetRows(5);
	m_gridMotor.SetCols(9);

	for(int i=0;i<5;i++)
		m_gridMotor.SetRowHeight(i, 510);

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
	m_gridMotor.SetTextMatrix(0, 2, MotorPosName[Align_Pos]);
	m_gridMotor.SetTextMatrix(0, 3, MotorPosName[Epoxy_Pos]);
	m_gridMotor.SetTextMatrix(0, 4, MotorPosName[Bonding_Pos]);
	m_gridMotor.SetTextMatrix(0, 5, "Limit(-)");
	m_gridMotor.SetTextMatrix(0, 6, "HOME");
	m_gridMotor.SetTextMatrix(0, 7, "Limit(+)");
	m_gridMotor.SetTextMatrix(0, 8, "Alram");

	for(int i=Motor_PCB_X; i<=Motor_Syringe; i++)
	{
		m_gridMotor.SetTextMatrix(i+1-Motor_PCB_X, 0, MotorName[i]);
	}

	m_gridMotor.SetRedraw(TRUE);
	m_gridMotor.Refresh();
}


void CResinDlg::OnBnClickedButtonMotorSave()
{
	CString cellStr;

	m_gridMotor.SetRedraw(FALSE);

	for(int i=Motor_PCB_X;i<=Motor_Syringe;i++)
	{
		cellStr = m_gridMotor.GetTextMatrix(i+1 - Motor_PCB_X, 2);
		model.axis[i].pos[Align_Pos] = atof(cellStr);

		cellStr = m_gridMotor.GetTextMatrix(i+1 - Motor_PCB_X, 3);
		model.axis[i].pos[Epoxy_Pos] = atof(cellStr);

		cellStr = m_gridMotor.GetTextMatrix(i+1 - Motor_PCB_X, 4);
		model.axis[i].pos[Bonding_Pos] = atof(cellStr);
	}

	m_gridMotor.SetRedraw(TRUE);
	m_gridMotor.Refresh();

	model.Save();
}


void CResinDlg::changeMotorNo(int motorNo)
{
	if(m_iSelMotor==motorNo)
		return;

	if(motorNo<Motor_PCB_X || motorNo>Motor_Syringe)
		return;

	m_gridMotor.SetRedraw(FALSE);

	m_gridMotor.SetRow(m_iSelMotor+1 - Motor_PCB_X);
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

	m_gridMotor.SetRow(motorNo+1 - Motor_PCB_X);
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


	m_gridMotor.SetRow(Motor_Syringe+1 - Motor_PCB_X);
	m_gridMotor.SetCol(4);
	m_gridMotor.SetCellBackColor(GRID_COLOR_SPARE_MOTOR);

	m_gridMotor.SetRedraw(TRUE);
	m_gridMotor.Refresh();
}


BEGIN_EVENTSINK_MAP(CResinDlg, CDialogEx)
	ON_EVENT(CResinDlg, IDC_MSFLEXGRID_MOTOR, DISPID_DBLCLICK, CResinDlg::DblClickMsflexgridMotor, VTS_NONE)
	ON_EVENT(CResinDlg, IDC_MSFLEXGRID_RESIN, DISPID_DBLCLICK, CResinDlg::DblClickMsflexgridResin, VTS_NONE)
END_EVENTSINK_MAP()


void CResinDlg::DblClickMsflexgridMotor()
{
	int col = m_gridMotor.GetMouseCol();
	int row = m_gridMotor.GetMouseRow();
	int index;

	if(row<1)
		return;

	double pos;

	if(col==0)
	{
		changeMotorNo(row-1+Motor_PCB_X);
	}
	else if(col>=2 && col<=4)
	{
		if(row ==4 && col ==4)
			return;

		if(col == 2) 		index = Align_Pos;
		else if(col == 3)	index = Epoxy_Pos;
		else if(col == 4)	index = Bonding_Pos;

		if(!getMotorPos(row-1+Motor_PCB_X, index, pos))
			return;

		CString tmpStr;
		tmpStr.Format("현재 위치를 [ %s ] 값으로 입력 하시겠습니까?", MotorPosName[index]);

		if(askMsg(tmpStr.GetBuffer(99)))
		{
			tmpStr = m_gridMotor.GetTextMatrix(row, 1);
			m_gridMotor.SetTextMatrix(row, col, tmpStr);
		}
	}
}


void CResinDlg::dispMotorStatus()
{
	CString str;
	char sLog[100];
	int		status;
	double	motorPos;

	m_gridMotor.SetRedraw(FALSE);

	for(int i=Motor_PCB_X; i<=Motor_Syringe; i++)
	{
		m_gridMotor.SetRow(i+1 - Motor_PCB_X);

		status		= motor.GetAxisStatus(i);
		motorPos	= motor.GetCurrentPos(i);

		str.Format("%.03f", motorPos);
		m_gridMotor.SetTextMatrix(i+1-Motor_PCB_X, 1, str);							// 모터 좌표..


		if(status & ST_NEG_LIMIT)					
		{
			m_gridMotor.SetCellBackColor(GRID_COLOR_RED);
			sprintf_s(sLog, "[%s] - Limit 감지",MotorName[i]);
			if(!delayDlg->IsWindowVisible())				delayMsg(sLog,3000,M_COLOR_RED);
		}
		else										m_gridMotor.SetCellBackColor(0);

		m_gridMotor.SetCol(6);														// HOM 센서
		if(status & ST_HOME_SWITCH)					m_gridMotor.SetCellBackColor(GRID_COLOR_GREEN);
		else										m_gridMotor.SetCellBackColor(0);

		m_gridMotor.SetCol(7);														// (+) 센서
		if(status & ST_POS_LIMIT)	
		{
			m_gridMotor.SetCellBackColor(GRID_COLOR_RED);
			sprintf_s(sLog, "[%s] + Limit 감지",MotorName[i]);
			if(!delayDlg->IsWindowVisible())				delayMsg(sLog,3000,M_COLOR_RED);
		}
		else										m_gridMotor.SetCellBackColor(0);

		m_gridMotor.SetCol(8);														// Servo Alarm
		if(status & ST_AMP_FAULT)
		{	
			m_gridMotor.SetCellBackColor(GRID_COLOR_RED);
			sprintf_s(sLog, "[%s] AMP 알람 감지",MotorName[i]);
			if(!delayDlg->IsWindowVisible())				delayMsg(sLog,3000,M_COLOR_RED);
		}
		else										m_gridMotor.SetCellBackColor(0);
	}

	m_gridMotor.SetRedraw(TRUE); 
	m_gridMotor.Refresh();
}

void CResinDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent==RESIN_TIMER)
	{
		if (!timerRunFlag)
		{
			timerRunFlag = true;

			dispMotorStatus();

			timerRunFlag = false;
		}
// 		// JOG 이동 + 방향
// 		if(JogPlusflag == true && OLD_JogPlusflag == false)
// 			motor.JogMove(m_iSelMotor, sysData.fMotorSpeed[m_iSelMotor] * sysData.fMotorResol[m_iSelMotor] * m_fMotorJogSpeed);
// 		else if(JogPlusflag == false && OLD_JogPlusflag == true)
// 			motor.JogStop(m_iSelMotor);
// 		OLD_JogPlusflag = JogPlusflag;
// 
// 
// 		// JOG 이동 - 방향
// 		if(JogMinusflag == true && OLD_JogMinusflag == false)
// 			motor.JogMove(m_iSelMotor, -sysData.fMotorSpeed[m_iSelMotor] * sysData.fMotorResol[m_iSelMotor] * m_fMotorJogSpeed);
// 		else if(JogMinusflag== false && OLD_JogMinusflag == true)
// 			motor.JogStop(m_iSelMotor);
// 		OLD_JogMinusflag = JogMinusflag;

		changeColorSyringeBtn();
		changeColorMotorPosBtn();
		changeColorDischargeBtn();
	}

	CDialogEx::OnTimer(nIDEvent);
}






void CResinDlg::OnBnClickedButtonMotorAlign()
{
	if(Task.AutoFlag ==2) return;
	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;
	g_bMovingflag =true;

	if(!motor.LENS_Z_Motor_Move(Wait_Pos))
	{
		CString sTmpLog;
		sTmpLog.Format("Lens Z축 %s 이동 실패", MotorPosName[Wait_Pos]);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_RED);
		g_bMovingflag =false;
		return;
	}

	Dio.setLedLight(0);
	motor.Pcb_Motor_Move(Align_Pos);

	g_bMovingflag =false;	
}


void CResinDlg::OnBnClickedButtonMotorEmission()
{
	if(Task.AutoFlag ==2) return;
	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;
	g_bMovingflag =true;

	if(!motor.LENS_Z_Motor_Move(Wait_Pos))
	{
		CString sTmpLog;
		sTmpLog.Format("Lens Z축 %s 이동 실패", MotorPosName[Wait_Pos]);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_RED);
		g_bMovingflag =false;
		return;
	}

	Dio.setLedLight(0);
	motor.Pcb_Motor_Move(Epoxy_Pos, Task.d_Align_offset_x[CAM2], Task.d_Align_offset_y[CAM2], Task.d_Align_offset_th[CAM2]);

	g_bMovingflag =false;
}

void CResinDlg::OnBnClickedButtonResinInsp()
{
	if(Task.AutoFlag ==2) return;
	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;
	g_bMovingflag =true;

	if(!motor.LENS_Z_Motor_Move(Wait_Pos))
	{
		CString sTmpLog;
		sTmpLog.Format("Lens Z축 %s 이동 실패", MotorPosName[Wait_Pos]);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_RED);
		g_bMovingflag =false;
		return;
	}

	int pos;
	if(m_iSelArea == 0)			pos = EpoxyInsp0_Pos;	
	else if(m_iSelArea == 1)	pos = EpoxyInsp1_Pos;
	else if(m_iSelArea == 2)	pos = EpoxyInsp2_Pos;
	else if(m_iSelArea == 3)	pos = EpoxyInsp3_Pos;

	Dio.setLedLight(0);
	motor.Pcb_Motor_Move(pos, Task.d_Align_offset_x[CAM2], Task.d_Align_offset_y[CAM2], Task.d_Align_offset_th[CAM2]);

	g_bMovingflag =false;
}


void CResinDlg::OnBnClickedButtonSyringeOn()
{
	if(Task.AutoFlag ==2) return;
	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;
	g_bMovingflag =true;

	if(	motor.Syringe_Motor_Move(Wait_Pos))
	{
		CString sTmpLog;
		sTmpLog.Format("Syringe %s 이동 완료", MotorPosName[Wait_Pos]);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
	}

	g_bMovingflag =false;
}

void CResinDlg::OnBnClickedButtonSyringeOff()
{
	if(Task.AutoFlag ==2) return;
	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;
	g_bMovingflag =true;

	if(	motor.Syringe_Motor_Move(Epoxy_Pos))
	{
		CString sTmpLog;
		sTmpLog.Format("Syringe %s 이동 완료", MotorPosName[Epoxy_Pos]);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
	}

	g_bMovingflag =false;
}


void CResinDlg::OnBnClickedButtonDischargeOn()
{
	if(Task.AutoFlag ==2) return;
	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;
	g_bMovingflag =true;

	Dio.DischargeOn(true);

	g_bMovingflag =false;
}


void CResinDlg::OnBnClickedButtonDischargeOff()
{
	if(Task.AutoFlag ==2) return;
	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;
	g_bMovingflag =true;

	Dio.DischargeOn(false);

	g_bMovingflag =false;
}

void CResinDlg::OnBnClickedButtonMotorSpeed()
{
	CheckJogMotorSpeed();
}
void CResinDlg::CheckJogMotorSpeed()
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



void CResinDlg::OnBnClickedButtonPlusX()
{
	if(Task.AutoFlag ==2) return;
	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;
	g_bMovingflag =true;

	CString temp;
	GetDlgItem(IDC_EDIT_MOVE_VAL)->GetWindowText(temp);
	double pos;
	pos = atof(temp);

	if ( pos > 3)	pos = 3;

	motor.MoveAxis(m_iSelMotor, REL, pos, 4, 20);

	g_bMovingflag =false;

	//	JogPlusflag = true;
}


void CResinDlg::OnBnClickedButtonMinusX()
{
	if(Task.AutoFlag ==2) return;
	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;
	g_bMovingflag =true;

	CString temp;
	GetDlgItem(IDC_EDIT_MOVE_VAL)->GetWindowText(temp);
	double pos;
	pos = atof(temp);

	if ( pos > 3)	pos = 3;

	motor.MoveAxis(m_iSelMotor, REL, -pos, 4, 20);

	g_bMovingflag =false;

	//	JogMinusflag = true;
}


void CResinDlg::DblClickMsflexgridResin()
{
	int col = m_gridResin.GetMouseCol();
	int row = m_gridResin.GetMouseRow();


	CString celData = m_gridResin.GetTextMatrix(row, col);


	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		CString curStr = dlg.GetstrNum();

		double dVal = atof(curStr);
		if(dVal<0)		dVal = 0;
		if(dVal>2000)	dVal = 2000;

		celData.Format("%.03f", dVal);

		m_gridResin.SetTextMatrix(row, col, celData);
	}
}


void CResinDlg::OnBnClickedButtonResinDraw()
{
	if(Task.AutoFlag ==2) return;
	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;
	g_bMovingflag =true;

	motor.ResinDraw(0);
	while(1)
	{
		if(axis_done(Motor_PCB_Y))		
		{
			motor.Pcb_Motor_Move(Loading_Pos, Task.d_Align_offset_x[CAM2], Task.d_Align_offset_y[CAM2], Task.d_Align_offset_th[CAM2]);
			break;
		}
	}

	g_bMovingflag =false;
}



void CResinDlg::changeColorSyringeBtn()
{
	if (checkSyringeMotorPos(Wait_Pos))
	{
		m_btnSyringeOn.m_iStateBtn	= 1;
		m_btnSyringeOff.m_iStateBtn	= 0;
	}
	else if (checkSyringeMotorPos(Epoxy_Pos))
	{
		m_btnSyringeOn.m_iStateBtn	= 0;
		m_btnSyringeOff.m_iStateBtn	= 1;
	}
	else
	{
		m_btnSyringeOn.m_iStateBtn	= 0;
		m_btnSyringeOff.m_iStateBtn	= 0;
	}

	m_btnSyringeOn.Invalidate();
	m_btnSyringeOff.Invalidate();
}


void CResinDlg::changeColorDischargeBtn()
{
	if (Dio.DischargeOnCheck(true))
	{
		m_btnDischargeOn.m_iStateBtn	= 1;
		m_btnDischargeOff.m_iStateBtn	= 0;
	}
	else if (Dio.DischargeOnCheck(false))
	{
		m_btnDischargeOn.m_iStateBtn	= 0;
		m_btnDischargeOff.m_iStateBtn	= 1;
	}

	m_btnDischargeOn.Invalidate();
	m_btnDischargeOff.Invalidate();
}



bool CResinDlg::checkCurMotorPos(int iPos)
{
	double dCurPos;
	double dMotorPos;

	for (int i=Motor_PCB_X ; i<=Motor_PCB_TH; i++)
	{
		dCurPos		= motor.GetCurrentPos(i);
		dMotorPos	= model.axis[i].pos[iPos];

		if (fabs(dMotorPos-dCurPos) >0.01)
			return false;
	}

	return true;
}

void CResinDlg::changeColorMotorPosBtn()
{
	int iIndex = -1;

	if (checkCurMotorPos(Align_Pos))
	{
		iIndex = 0;
	}
	else if (checkCurMotorPos(Epoxy_Pos))
	{
		iIndex = 1;
	}
	else if (checkCurMotorPos(EpoxyInsp0_Pos))
	{
		iIndex = 2;
	}
	else if (checkCurMotorPos(EpoxyInsp1_Pos))
	{
		iIndex = 2;
	}
	else if (checkCurMotorPos(EpoxyInsp2_Pos))
	{
		iIndex = 2;
	}
	else if (checkCurMotorPos(EpoxyInsp3_Pos))
	{
		iIndex = 2;
	}
	else if (checkCurMotorPos(Epoxy_Cal_Pos))
	{
		iIndex = 3;
	}
	else if (checkCurMotorPos(Epoxy_Cal_Insp_Pos))
	{
		iIndex = 4;
	}
	else
		return;

	m_btnAlignPos.m_iStateBtn = 0;
	m_btnEmissionPos.m_iStateBtn = 0;
	m_btnInspPos.m_iStateBtn = 0;
	m_btnEpoxyCalPos.m_iStateBtn = 0;
	m_btnEpoxyCalInspPos.m_iStateBtn = 0;

	if (iIndex==0)			m_btnAlignPos.m_iStateBtn = 1;
	else if (iIndex==1)		m_btnEmissionPos.m_iStateBtn = 1;
	else if (iIndex==2)		m_btnInspPos.m_iStateBtn = 1;
	else if (iIndex==3)		m_btnEpoxyCalPos.m_iStateBtn = 1;
	else if (iIndex==4)		m_btnEpoxyCalInspPos.m_iStateBtn = 1;

	m_btnAlignPos.Invalidate();
	m_btnEmissionPos.Invalidate();
	m_btnInspPos.Invalidate();
	m_btnEpoxyCalPos.Invalidate();
	m_btnEpoxyCalInspPos.Invalidate();
}


int CResinDlg::checkSyringeMotorPos(int iIndex)
{
	double	dCurPos		= motor.GetCurrentPos(Motor_Syringe);
	double	dMotorPos	= model.axis[Motor_Syringe].pos[iIndex];

	if (fabs(dMotorPos-dCurPos)>0.01)
		return 0;

	return 1;
}


void CResinDlg::OnBnClickedRadioPcbAlign()
{
	UpdateData();
	CAABonderDlg* pFrame = (CAABonderDlg*)(AfxGetApp()->m_pMainWnd);
	pFrame->setCamDisplay(m_iCamNo+1,0);
}


void CResinDlg::OnBnClickedRadioEpoxy()
{
	UpdateData();
	CAABonderDlg* pFrame = (CAABonderDlg*)(AfxGetApp()->m_pMainWnd);
	pFrame->setCamDisplay(m_iCamNo+1,0);
}


void CResinDlg::OnBnClickedCheckResinDraw()
{
	UpdateData(true);
	checkResinpara();
}


void CResinDlg::checkResinpara()
{
	if(m_bResinPara)
	{
		GetDlgItem(IDC_EDIT_RESIN_START) -> EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_RESIN_END) -> EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_RESIN_START) -> EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_RESIN_END) -> EnableWindow(FALSE);
	}
}


void CResinDlg::OnBnClickedButtonResinInspect()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	bool rtn = pFrame->_inspResign(0, m_bResinInspDIsp ? 2 : 1);

	if(rtn)
		vision.textlist[CAM2].addList(600, 720, "O K", M_COLOR_GREEN, 30, 15, "Arial");
	else
	{
		vision.textlist[CAM2].addList(600, 720, "N G", M_COLOR_RED, 30, 15, "Arial");
	}
	vision.drawOverlay(CAM2);

	
	pFrame->m_rBox.left = 0;
	pFrame->m_rBox.top = 0;
	pFrame->m_rBox.right = 0;
	pFrame->m_rBox.bottom = 0;
}


void CResinDlg::OnBnClickedButtonEpoxyCal()
{
	if(Task.AutoFlag ==2) return;
	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;
	g_bMovingflag =true;

	if(	motor.Pcb_Motor_Move(Epoxy_Cal_Pos))
	{
		motor.Syringe_Motor_Move(Epoxy_Cal_Pos);
		CString sTmpLog;
		sTmpLog.Format("PCB부 %s 이동 완료", MotorPosName[Epoxy_Cal_Pos]);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
	}

	g_bMovingflag =false;
}


void CResinDlg::OnBnClickedButtonEpoxyCalInsp()
{
	if(Task.AutoFlag ==2) return;
	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;
	g_bMovingflag =true;

	if(	motor.Pcb_Motor_Move(Epoxy_Cal_Insp_Pos))
	{
		motor.Syringe_Motor_Move(Epoxy_Cal_Insp_Pos);
		CString sTmpLog;
		sTmpLog.Format("PCB부 %s 이동 완료", MotorPosName[Epoxy_Cal_Insp_Pos]);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
	}

	g_bMovingflag =false;
}


void CResinDlg::OnBnClickedCheckResinInspDisp()
{
	UpdateData(true);
}

int CResinDlg::findEpoxyPoint()
{
	CString sMsg;
	int iSx, iSy, iEx, iEy;
	int iPos;
	int aiHist[256] = {0,};

	vision.clearOverlay(CAM2);

	Sleep(500);

	if(vision.getLiveMode())
	{
		vision.getSnapImage(CAM2);
		vision.setLiveMode(true);
	}

	iSx = model.m_rcArea_EpoxyCalc.left;
	iSy = model.m_rcArea_EpoxyCalc.top;
	iEx = model.m_rcArea_EpoxyCalc.right;
	iEy = model.m_rcArea_EpoxyCalc.bottom;

	vision.boxlist[CAM2].addList(iSx, iSy, iEx, iEy, PS_DOT, M_COLOR_RED);

	MbufAllocColor(vision.MilSystem, 3L, (iEx-iSx), (iEy-iSy), M_DEF_IMAGE_TYPE, M_IMAGE+M_PROC, &MilOriginImage);
	MbufClear(MilOriginImage, 0);
	MbufChildColor(MilOriginImage, M_GREEN, &MilOriginImageChild[0]);

	MbufAllocColor(vision.MilSystem, 1L, (iEx-iSx), (iEy-iSy), M_DEF_IMAGE_TYPE, M_IMAGE+M_PROC, &MilBinaryImage);
	MbufClear(MilBinaryImage, 0);

	MbufCopyColor2d(vision.MilProcImage[0], MilOriginImage, M_GREEN, iSx, iSy, M_GREEN, 0, 0, (iEx-iSx), (iEy-iSy));

	int iSizeX = MbufInquire(vision.MilProcImageChild[CAM2], M_PITCH, M_NULL);

	for (int y=iSy ; y<iEy ; y++)
	{
		iPos = y * iSizeX + iSx;

		for (int x=iSx ; x<iEx ; x++)
		{
			aiHist[vision.Image[CAM2][iPos++]]++;
		}
	}

	int iMax = -1;
	int iIndex1, iIndex2;

	for (int i=0 ; i<256 ; i++)
	{
		if ( aiHist[i] > iMax )
		{
			iMax = aiHist[i];
			iIndex1 = i;
		}
	}

	int iMax_Second = -1;

	for (int i=0 ; i<256 ; i++)
	{
		if ( aiHist[i] > iMax_Second && iMax > aiHist[i] )
		{
			iMax_Second = aiHist[i];
			iIndex2 = i;
		}
	}

	int iThreshold = (iIndex1 + iIndex2) / 2;

	MimBinarize(MilOriginImageChild[0], MilBinaryImage, M_INCLUDE, 0, iThreshold);

	MblobAllocFeatureList(vision.MilSystem, &MilBlobFeatureList);

	MblobSelectFeature(MilBlobFeatureList, M_AREA);
	MblobSelectFeature(MilBlobFeatureList, M_CENTER_OF_GRAVITY);

	MblobAllocResult(vision.MilSystem, &MilBlobResult);

	MblobCalculate(MilBinaryImage, M_NULL, MilBlobFeatureList, MilBlobResult);

	MblobSelect(MilBlobResult, M_EXCLUDE, M_AREA, M_LESS_OR_EQUAL, 800, M_NULL); 

	MblobGetNumber(MilBlobResult, &m_iTotalBlobs);

	if ( m_iTotalBlobs < 1 )
	{
		sMsg.Format("레진 위치를 찾지 못했습니다.");
		errMsg(sMsg.GetBuffer());

		vision.drawOverlay(CAM2);

		return -1;
	}

	if ( m_iTotalBlobs > 1 )
	{
		sMsg.Format("찾은 레진 위치가 많습니다. ( %d )", m_iTotalBlobs);
		errMsg(sMsg.GetBuffer());

		vision.drawOverlay(CAM2);

		return -1;
	}

	double dCogX;
	double dCogY;

	MblobGetResult(MilBlobResult, M_CENTER_OF_GRAVITY_X, &dCogX);
	MblobGetResult(MilBlobResult, M_CENTER_OF_GRAVITY_Y, &dCogY);

	//	sMsg.Format("Blobs : %d", m_iTotalBlobs);
	//	vision.textlist[CAM2].addList(200, 200, sMsg, M_COLOR_RED, 16, 12, "Arial");

	vision.crosslist[CAM2].addList(model.m_iBase_Epoxy_X, model.m_iBase_Epoxy_Y, 100, M_COLOR_RED);
	vision.crosslist[CAM2].addList((int)(iSx+dCogX + 0.5), (int)(iSy+dCogY + 0.5), 100, M_COLOR_MAGENTA);

	int iCenter_Area_X = (iEx+iSx)/2;
	int iCenter_Area_Y = (iEy+iSy)/2;

	m_dCogX = (double)iSx + dCogX;
	m_dCogY = (double)iSy + dCogY;

	MbufFree(MilBlobResult);
	MilBlobResult = M_NULL;

	MbufFree(MilBlobFeatureList);
	MilBlobFeatureList = M_NULL;

	MbufFree(MilOriginImageChild[0]);
	MilOriginImageChild[0] = M_NULL;
	MilOriginImageChild[1] = M_NULL;
	MilOriginImageChild[2] = M_NULL;

	MbufFree(MilBinaryImage);
	MilBinaryImage = M_NULL;

	MbufFree(MilOriginImage);
	MilOriginImage = M_NULL;

	vision.drawOverlay(CAM2);

	return 1;
}


int CResinDlg::dischargeEpoxy()
{
	Dio.DischargeOn(true);
	Sleep(100);
	Dio.DischargeOn(false);

	return 1;
}


int CResinDlg::calcOffset_Epoxy()
{
	m_dOffset_X = (model.m_iBase_Epoxy_X - m_dCogX) * sysData.dCamResol[CAM2].x * -1.0;
	m_dOffset_Y = (model.m_iBase_Epoxy_Y - m_dCogY) * sysData.dCamResol[CAM2].y * -1.0;

	/* 보정값 수정 (확인 필요) */
	m_dOffset_X /= 2.0;
	m_dOffset_Y /= 2.0;

	return 1;
}


void CResinDlg::OnBnClickedButtonEpoxyCalc2()
{
	int iRtn;

#ifdef ON_LINE_MOTOR
	if(	motor.Pcb_Motor_Move(Epoxy_Cal_Pos))
	{
		motor.Syringe_Motor_Move(Epoxy_Cal_Pos);
		CString sTmpLog;
		sTmpLog.Format("PCB부 %s 이동 완료", MotorPosName[Epoxy_Cal_Pos]);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
	}

	iRtn  = dischargeEpoxy();
	if ( iRtn < 0 )	return;

	::Sleep(500);

//	Dio.setLedLight(0);
	Dio.ctrlLedVolume(1, 80);

	if(	motor.Pcb_Motor_Move(Epoxy_Cal_Insp_Pos))
	{
		motor.Syringe_Motor_Move(Epoxy_Cal_Insp_Pos);
		CString sTmpLog;
		sTmpLog.Format("PCB부 %s 이동 완료", MotorPosName[Epoxy_Cal_Insp_Pos]);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
	}
#endif

	iRtn = findEpoxyPoint();
	if ( iRtn < 0 )	return;

	iRtn = calcOffset_Epoxy();
	if ( iRtn < 0 )	return;

	putEpoxyCalcData();
}


void CResinDlg::getEpoxyCalcData()
{
	CString sData;

	model.m_iBase_Epoxy_X = GetDlgItemInt(IDC_EDIT_EPOXY_BASE_X);
	model.m_iBase_Epoxy_Y = GetDlgItemInt(IDC_EDIT_EPOXY_BASE_Y);

	GetDlgItemText(IDC_EDIT_EPOXY_OFFSET_X, sData);
	model.m_dOffset_Epoxy_X = atof(sData);
	GetDlgItemText(IDC_EDIT_EPOXY_OFFSET_Y, sData);
	model.m_dOffset_Epoxy_Y = atof(sData);

	model.m_rcArea_EpoxyCalc = m_rcArea_EpoxyCalc;
}


void CResinDlg::putEpoxyCalcData()
{
	CString sData;

	SetDlgItemInt(IDC_EDIT_EPOXY_BASE_X, m_iBase_X);
	SetDlgItemInt(IDC_EDIT_EPOXY_BASE_Y, m_iBase_Y);

	sData.Format("%.03lf", m_dOffset_X);
	SetDlgItemText(IDC_EDIT_EPOXY_OFFSET_X, sData);
	sData.Format("%.03lf", m_dOffset_Y);
	SetDlgItemText(IDC_EDIT_EPOXY_OFFSET_Y, sData);
}

void CResinDlg::showEpoxyCalcControl()
{
	GetDlgItem(IDC_STATIC_CALC_EPOXY)->ShowWindow(m_bCalc_Epoxy_Pos);
	GetDlgItem(IDC_BUTTON_EPOXY_CALC2)->ShowWindow(m_bCalc_Epoxy_Pos);
	GetDlgItem(IDC_BUTTON_FIND_EPOXY_POINT)->ShowWindow(m_bCalc_Epoxy_Pos);
	GetDlgItem(IDC_STATIC_BASE_X)->ShowWindow(m_bCalc_Epoxy_Pos);
	GetDlgItem(IDC_STATIC_BASE_Y)->ShowWindow(m_bCalc_Epoxy_Pos);
	GetDlgItem(IDC_EDIT_EPOXY_BASE_X)->ShowWindow(m_bCalc_Epoxy_Pos);
	GetDlgItem(IDC_EDIT_EPOXY_BASE_Y)->ShowWindow(m_bCalc_Epoxy_Pos);
	GetDlgItem(IDC_STATIC_OFFSET_X)->ShowWindow(m_bCalc_Epoxy_Pos);
	GetDlgItem(IDC_STATIC_OFFSET_Y)->ShowWindow(m_bCalc_Epoxy_Pos);
	GetDlgItem(IDC_EDIT_EPOXY_OFFSET_X)->ShowWindow(m_bCalc_Epoxy_Pos);
	GetDlgItem(IDC_EDIT_EPOXY_OFFSET_Y)->ShowWindow(m_bCalc_Epoxy_Pos);
	GetDlgItem(IDC_RADIO_SEL_TYPE_EPOXY_CALC)->ShowWindow(m_bCalc_Epoxy_Pos);
	GetDlgItem(IDC_RADIO_SEL_TYPE_EPOXY_CALC2)->ShowWindow(m_bCalc_Epoxy_Pos);

	if ( !m_bCalc_Epoxy_Pos )
	{
		vision.clearOverlay(CAM2);
		vision.drawOverlay(CAM2);
	}
}

void CResinDlg::OnBnClickedCheckEpoxyCalc()
{
	m_bCalc_Epoxy_Pos = !m_bCalc_Epoxy_Pos;

	showEpoxyCalcControl();
}

void CResinDlg::OnBnClickedRadioSelTypeEpoxyCalc()
{
	UpdateData(true);
	m_rcArea_EpoxyCalc = model.m_rcArea_EpoxyCalc;
}


void CResinDlg::OnBnClickedRadioSelTypeEpoxyCalc2()
{
	UpdateData(true);
	m_iBase_X = model.m_iBase_Epoxy_X;
	m_iBase_Y = model.m_iBase_Epoxy_Y;
}


void CResinDlg::OnBnClickedButtonFindEpoxyPoint()
{
	int iRtn;

	iRtn = findEpoxyPoint();
	if ( iRtn < 0 )	return;

	iRtn = calcOffset_Epoxy();
	if ( iRtn < 0 )	return;

	putEpoxyCalcData();
}