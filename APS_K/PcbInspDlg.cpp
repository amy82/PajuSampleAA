// PcbInspDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AA Bonder.h"
#include "AA BonderDlg.h"
#include "PcbInspDlg.h"
#include "afxdialogex.h"

#include "MarkSetDlg.h"
#include "GetNumDlg.h"

#include "DioControl.h"
#include "Vision.h"
#include "DataHandler.h"
#include "DelayMsgDlg.h"
#include "DisplacementDlg.h"


extern	CSystemData		sysData;
extern  CDelayMsgDlg*	delayDlg;

extern int curInDio[5];
extern int curOutDioByte[5][4];

/* Class */
extern	CVision			vision;
//extern	CMotorSet		motor;
extern	CDioControl		Dio;
extern	CModelData		model;

extern	CTask			Task;
extern	CKeyenceSensor	Keyence;

extern	bool JogPlusflag;
extern	bool JogMinusflag;


extern	bool g_bMovingflag;

extern CDisplacementDlg	*m_pDisplacementDlg;

int g_iPBrightInsp=0;
int g_iPContrastInsp=0;

// CPcbInspDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPcbInspDlg, CDialogEx)

CPcbInspDlg::CPcbInspDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPcbInspDlg::IDD, pParent)
{
	m_iSelMoveType	= 0;
	m_iSelMotor		= Motor_PCB_TH;
}

CPcbInspDlg::~CPcbInspDlg()
{
}

void CPcbInspDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSFLEXGRID_MARK, m_gridMark);
	DDX_Radio(pDX, IDC_RADIO_POS, m_iSelMoveType);
	DDX_Control(pDX, IDC_LABEL_DISP5, m_labelDisp5);
	DDX_Control(pDX, IDC_LABEL_DISP6, m_labelDisp6);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_ALIGN, m_btnAlignPos);
	DDX_Control(pDX, IDC_BUTTON_VACCUM_OFF, m_btnVaccumOff);
	DDX_Control(pDX, IDC_BUTTON_VACCUM_ON, m_btnVaccumOn);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_WAIT, m_btnWaitPos);
	DDX_Control(pDX, IDC_PCB_ALIGN_RESULT, m_labelAlignResult);

	DDX_Control(pDX, IDC_SLIDER_BRIGHT, m_sliderBright);
	DDX_Control(pDX, IDC_SLIDER_CONTRAST, m_sliderContrast);
	DDX_Control(pDX, IDC_EDIT_Bright, m_LabelBright);
	DDX_Control(pDX, IDC_EDIT_Contrast, m_LabelContrast);

	DDX_Control(pDX, IDC_BUTTON_BOX_LEFT, m_btn_BoxLeft);
	DDX_Control(pDX, IDC_BUTTON_BOX_UP, m_btn_BoxUP);
	DDX_Control(pDX, IDC_BUTTON_BOX_RIGHT, m_btn_BoxRight);
	DDX_Control(pDX, IDC_BUTTON_BOX_DOWN, m_btn_BoxDown);

	DDX_Control(pDX, IDC_BUTTON_LASER_DLG_OPEN, m_btnLaserDlgOpen);
	DDX_Control(pDX, IDC_BUTTON_LASER_MANUAL_SERACH2, m_btnLaserManualStart);

	DDX_Control(pDX, IDC_BUTTON_MOTOR_LASER_OUT1, m_btn_LaserOUT1);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_LASER_OUT2, m_btn_LaserOUT2);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_LASER_OUT3, m_btn_LaserOUT3);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_LASER_OUT4, m_btn_LaserOUT4);
	
	DDX_Control(pDX, IDC_BUTTON_MOTOR_ALIGN_LASER_POS_OUT, m_btnAlignLaserPosOut);
	DDX_Control(pDX, IDC_BUTTON_PCB_COVER_FOR, m_btnPushFor);
	DDX_Control(pDX, IDC_BUTTON_PCB_COVER_BACK, m_btnPushBack);
	DDX_Control(pDX, IDC_BUTTON_PCB_DARK_UP, m_btnDarkUp);
	DDX_Control(pDX, IDC_BUTTON_PCB_DARK_DOWN, m_btnDarkDown);

	DDX_Control(pDX, IDC_BUTTON_MOTOR_DARK_INSP, m_btnDarkPos);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_DEFECT_INSP, m_btnDefectPos);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_BOND, m_btnBondPos);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_BOND2, m_btnBondAlignPos);
}


BEGIN_MESSAGE_MAP(CPcbInspDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CPcbInspDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CPcbInspDlg::OnBnClickedCancel)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_LIVEMODE, &CPcbInspDlg::OnBnClickedButtonLivemode)
	ON_BN_CLICKED(IDC_BUTTON_REGIST, &CPcbInspDlg::OnBnClickedButtonRegist)
	ON_BN_CLICKED(IDC_BUTTON_FIND, &CPcbInspDlg::OnBnClickedButtonFind)
	ON_BN_CLICKED(IDC_RADIO_POS, &CPcbInspDlg::OnBnClickedRadioPos)
	ON_BN_CLICKED(IDC_RADIO_SIZE, &CPcbInspDlg::OnBnClickedRadioSize)
	ON_BN_CLICKED(IDC_BUTTON_BOX_UP, &CPcbInspDlg::OnBnClickedButtonBoxUp)
	ON_BN_CLICKED(IDC_BUTTON_BOX_DOWN, &CPcbInspDlg::OnBnClickedButtonBoxDown)
	ON_BN_CLICKED(IDC_BUTTON_BOX_LEFT, &CPcbInspDlg::OnBnClickedButtonBoxLeft)
	ON_BN_CLICKED(IDC_BUTTON_BOX_RIGHT, &CPcbInspDlg::OnBnClickedButtonBoxRight)
	ON_BN_CLICKED(IDC_BUTTON_BOX_SPEED, &CPcbInspDlg::OnBnClickedButtonBoxSpeed)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_ALIGN, &CPcbInspDlg::OnBnClickedButtonMotorAlign)
	ON_BN_CLICKED(IDC_BUTTON_MARKSET, &CPcbInspDlg::OnBnClickedButtonMarkset)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON_IMG_LOAD, &CPcbInspDlg::OnBnClickedButtonImgLoad)
	ON_BN_CLICKED(IDC_BUTTON_IMG_SAVE, &CPcbInspDlg::OnBnClickedButtonImgSave)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_VACCUM_ON, &CPcbInspDlg::OnBnClickedButtonVaccumOn)
	ON_BN_CLICKED(IDC_BUTTON_VACCUM_OFF, &CPcbInspDlg::OnBnClickedButtonVaccumOff)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_WAIT, &CPcbInspDlg::OnBnClickedButtonMotorWait)
	ON_BN_CLICKED(IDC_BUTTON_ALIGN_TEST2, &CPcbInspDlg::OnBnClickedButtonAlignTest2)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_Menu_COPY, &CPcbInspDlg::OnMenuCopy)
	ON_COMMAND(ID_Menu_DELETE, &CPcbInspDlg::OnMenuDelete)
	ON_COMMAND(ID_Menu_PASTE, &CPcbInspDlg::OnMenuPaste)
	ON_WM_HSCROLL()
	ON_STN_CLICKED(IDC_EDIT_Bright, &CPcbInspDlg::OnClickedEditBright)
	ON_STN_CLICKED(IDC_EDIT_Contrast, &CPcbInspDlg::OnClickedEditContrast)
	ON_BN_CLICKED(IDC_BUTTON_LASER_DLG_OPEN, &CPcbInspDlg::OnBnClickedButtonLaserDlgOpen)
	ON_BN_CLICKED(IDC_BUTTON_LASER_MANUAL_SERACH2, &CPcbInspDlg::OnBnClickedButtonLaserManualSerach2)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_LASER_OUT1, &CPcbInspDlg::OnBnClickedButtonMotorLaserOut1)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_LASER_OUT2, &CPcbInspDlg::OnBnClickedButtonMotorLaserOut2)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_LASER_OUT3, &CPcbInspDlg::OnBnClickedButtonMotorLaserOut3)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_LASER_OUT4, &CPcbInspDlg::OnBnClickedButtonMotorLaserOut4)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_ALIGN_LASER_POS_OUT, &CPcbInspDlg::OnBnClickedButtonMotorAlignLaserPosOut)
	ON_BN_CLICKED(IDC_BUTTON_PCB_COVER_FOR, &CPcbInspDlg::OnBnClickedButtonPcbCoverFor)
	ON_BN_CLICKED(IDC_BUTTON_PCB_COVER_BACK, &CPcbInspDlg::OnBnClickedButtonPcbCoverBack)
	ON_BN_CLICKED(IDC_BUTTON_PCB_DARK_UP, &CPcbInspDlg::OnBnClickedButtonPcbDarkUp)
	ON_BN_CLICKED(IDC_BUTTON_PCB_DARK_DOWN, &CPcbInspDlg::OnBnClickedButtonPcbDarkDown)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_DARK_INSP, &CPcbInspDlg::OnBnClickedButtonMotorDarkInsp)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_DEFECT_INSP, &CPcbInspDlg::OnBnClickedButtonMotorDefectInsp)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_BOND, &CPcbInspDlg::OnBnClickedButtonMotorBond)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_BOND2, &CPcbInspDlg::OnBnClickedButtonMotorBond2)
	ON_BN_CLICKED(IDC_BUTTON_SOCKET_TEST, &CPcbInspDlg::OnBnClickedButtonSocketTest)
END_MESSAGE_MAP()


// CPcbInspDlg 메시지 처리기입니다.
BOOL CPcbInspDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	setInterface();
	DigLedputData();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CPcbInspDlg::OnBnClickedOk(){}
void CPcbInspDlg::OnBnClickedCancel(){}


void CPcbInspDlg::setInterface()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	WINDOWPLACEMENT wndpl;
	this->GetWindowPlacement(&wndpl);

	wndpl.rcNormalPosition = pFrame->m_rectCamDispPos2;
	wndpl.rcNormalPosition.top -= SUB_DLG_OFFSET_Y-10;
	wndpl.rcNormalPosition.bottom = MAIN_DLG_SIZE_Y-5 - 100;
	this->MoveWindow(&wndpl.rcNormalPosition);

	GetDlgItem(IDC_MARK_DISP1)->GetWindowPlacement(&wndpl);
	m_iMarkDispSizeX = wndpl.rcNormalPosition.right - wndpl.rcNormalPosition.left;
	m_iMarkDispSizeY = wndpl.rcNormalPosition.bottom - wndpl.rcNormalPosition.top;

#ifdef ON_LINE_VISION
	CWnd* pWnd;
	pWnd = (CWnd*)GetDlgItem(IDC_MARK_DISP1);
	MdispSelectWindow(vision.MilMarkDisplay[PCB_Holder_MARK][0], vision.MilMarkSmallImage[PCB_Holder_MARK][0], pWnd->m_hWnd);
	pWnd = (CWnd*)GetDlgItem(IDC_MARK_DISP2);
	MdispSelectWindow(vision.MilMarkDisplay[PCB_Holder_MARK][1], vision.MilMarkSmallImage[PCB_Holder_MARK][1], pWnd->m_hWnd);
#endif

	ctrlLiveButton();

	m_iMoveSpeed = 10;
	m_rMarkBox.left = 10;
	m_rMarkBox.top = 10;
	m_rMarkBox.right = CAM_SIZE_X - 10;
	m_rMarkBox.bottom = CAM_SIZE_Y - 10;	
	

	m_labelAlignResult.SetBkColor(M_COLOR_WHITE);

	/* m_iMarkNo 초기화 */
	clickedMarkDisp(0);


	m_sliderBright.SetRangeMin(0,FALSE);
	m_sliderBright.SetRangeMax(255,FALSE);
	m_sliderBright.SetTicFreq(10);	

	m_sliderContrast.SetRangeMin(0,FALSE);
	m_sliderContrast.SetRangeMax(255,FALSE);
	m_sliderContrast.SetTicFreq(10);
}


void CPcbInspDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow)
	{
		if(Task.AutoFlag == 0)
			LightControl.ctrlLedVolume(LIGHT_PCB, model.m_iLedValue[LEDDATA_SENSOR]);

		/* Grid */
		initMarkGrid();

		ctrlLiveButton();
		#ifdef ON_LINE_VISION
		dispMarkImage();
		#endif
		dispData();
		DigLedputData();
		#ifdef ON_LINE_VISION
		vision.clearOverlay(CAM1);
		vision.drawOverlay(CAM1);
		#endif

		pushErrCnt = vaccumErrCnt = 0;

		timerRunFlag = false;
		m_bCopyFlag = false;
		m_iCopyMarkNo = -1;

		SetTimer(PCB_TIMER, 100, NULL);
	}
	else
	{
		KillTimer(PCB_TIMER);

		CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
		#ifdef ON_LINE_VISION
		vision.clearOverlay(CAM1);
		vision.drawOverlay(CAM1);
		#endif

		pFrame->m_bMeasureDist = FALSE;
		pFrame->UpdateData(false);

		pFrame->m_rBox.left = 0;
		pFrame->m_rBox.top = 0;
		pFrame->m_rBox.right = 0;
		pFrame->m_rBox.bottom = 0;
	}
}


void CPcbInspDlg::dispData()
{
	CString tmpStr;

	tmpStr.Format("%d", model.m_iLimitRate[PCB_Holder_MARK][0]);
	m_gridMark.SetTextMatrix(1, 1, tmpStr);

	tmpStr.Format("%d", model.m_iLimitRate[PCB_Holder_MARK][1]);
	m_gridMark.SetTextMatrix(1, 2, tmpStr);

}


void CPcbInspDlg::getData()
{
	CString strTemp;
	strTemp = m_gridMark.GetTextMatrix(1, 1);
	model.m_iLimitRate[PCB_Holder_MARK][0] = atoi(strTemp);

	strTemp = m_gridMark.GetTextMatrix(1, 2);
	model.m_iLimitRate[PCB_Holder_MARK][1] = atoi(strTemp);

	GetDlgItem(IDC_EDIT_Bright)->GetWindowText(strTemp);
	model.m_iBright[PCB_Holder_MARK]=atoi(strTemp);

	GetDlgItem(IDC_EDIT_Contrast)->GetWindowText(strTemp);
	model.m_iContrast[PCB_Holder_MARK]=atoi(strTemp);
}


void CPcbInspDlg::initMarkGrid()
{
	CString strTemp;

	m_gridMark.SetRows(2);
	m_gridMark.SetCols(3);

	m_gridMark.SetColAlignment(0, 4);
	m_gridMark.SetColAlignment(1, 4);
	m_gridMark.SetColAlignment(2, 4);

	m_gridMark.SetColWidth(0,1200);//1450
	m_gridMark.SetColWidth(1,950);//2350
	m_gridMark.SetColWidth(2,950);//2350

	sLangChange.LoadStringA(IDS_STRING761);
	m_gridMark.SetTextMatrix(0, 1, sLangChange);
	sLangChange.LoadStringA(IDS_STRING762);
	m_gridMark.SetTextMatrix(0, 2, sLangChange);


	sLangChange.LoadStringA(IDS_STRING767);
	m_gridMark.SetTextMatrix(1, 0, sLangChange);

	m_gridMark.SetRowHeight(1, 510);
}


void CPcbInspDlg::ctrlLiveButton()
{
	if (vision.getLiveMode())
	{
		sLangChange.LoadStringA(IDS_STRING1464);
		GetDlgItem(IDC_BUTTON_LIVEMODE)->SetWindowText(sLangChange);
	}
	else
	{
		sLangChange.LoadStringA(IDS_STRING1465);
		GetDlgItem(IDC_BUTTON_LIVEMODE)->SetWindowText(sLangChange);
	}
}

void CPcbInspDlg::OnBnClickedButtonLivemode()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	if(vision.getLiveMode())
		vision.setLiveMode(0);
	else
		vision.setLiveMode(1);

	ctrlLiveButton();
}

void CPcbInspDlg::getMarkSize()
{
	m_iMarkSizeX = m_rMarkBox.right - m_rMarkBox.left;
	m_iMarkSizeY = m_rMarkBox.bottom - m_rMarkBox.top;
}

void CPcbInspDlg::OnBnClickedButtonRegist()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	if (vision.getLiveMode())
		vision.getSnapImage(CAM1);

	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	getMarkSize();

	bool bRtn = vision.markRegist(CAM1, PCB_Holder_MARK, m_iMarkNo, m_rMarkBox);

	if (!bRtn)
	{
		sLangChange.LoadStringA(IDS_STRING1466);
		::errMsg2(Task.AutoFlag, sLangChange);
		return;
	}

	CMarkSetDlg dlg(CAM1, PCB_Holder_MARK, m_iMarkNo, m_iMarkSizeX, m_iMarkSizeY, true);

	double dZoomX = (double)MARK_SIZE_X/(double)m_iMarkSizeX;
	double dZoomY = (double)MARK_SIZE_Y/(double)m_iMarkSizeY;

	if (dlg.DoModal()==IDOK)
	{
#ifdef USE_GEOMETRIC
		MmodDraw(M_DEFAULT, vision.ModModel[PCB_Holder_MARK][m_iMarkNo], vision.MilMarkImage[PCB_Holder_MARK][m_iMarkNo], M_DRAW_IMAGE, M_DEFAULT, M_DEFAULT);

		MmodInquire(vision.ModModel[PCB_Holder_MARK][m_iMarkNo], M_DEFAULT, M_REFERENCE_X+M_TYPE_DOUBLE, &model.m_MarkCenter[PCB_Holder_MARK][m_iMarkNo].x);
		MmodInquire(vision.ModModel[PCB_Holder_MARK][m_iMarkNo], M_DEFAULT, M_REFERENCE_Y+M_TYPE_DOUBLE, &model.m_MarkCenter[PCB_Holder_MARK][m_iMarkNo].y);
		MmodInquire(vision.ModModel[PCB_Holder_MARK][m_iMarkNo], M_DEFAULT, M_REFERENCE_X+M_TYPE_DOUBLE, &model.m_MarkOrigin[PCB_Holder_MARK][m_iMarkNo].x);
		MmodInquire(vision.ModModel[PCB_Holder_MARK][m_iMarkNo], M_DEFAULT, M_REFERENCE_Y+M_TYPE_DOUBLE, &model.m_MarkOrigin[PCB_Holder_MARK][m_iMarkNo].y);
#else
		MpatDraw(M_DEFAULT, vision.PatModel[PCB_Holder_MARK][m_iMarkNo], vision.MilMarkImage[PCB_Holder_MARK][m_iMarkNo], M_DRAW_IMAGE, M_DEFAULT, M_DEFAULT);

		MpatInquire(vision.PatModel[PCB_Holder_MARK][m_iMarkNo], M_CENTER_X, &model.m_MarkCenter[PCB_Holder_MARK][m_iMarkNo].x);
		MpatInquire(vision.PatModel[PCB_Holder_MARK][m_iMarkNo], M_CENTER_Y, &model.m_MarkCenter[PCB_Holder_MARK][m_iMarkNo].y);
		MpatInquire(vision.PatModel[PCB_Holder_MARK][m_iMarkNo], M_ORIGINAL_X, &model.m_MarkOrigin[PCB_Holder_MARK][m_iMarkNo].x);
		MpatInquire(vision.PatModel[PCB_Holder_MARK][m_iMarkNo], M_ORIGINAL_Y, &model.m_MarkOrigin[PCB_Holder_MARK][m_iMarkNo].y);
#endif

		MimResize(vision.MilMarkImage[PCB_Holder_MARK][m_iMarkNo], vision.MilMarkSmallImage[PCB_Holder_MARK][m_iMarkNo], dZoomX, dZoomY, M_DEFAULT);

		model.m_MarkSize[PCB_Holder_MARK][m_iMarkNo].x = m_iMarkSizeX;
		model.m_MarkSize[PCB_Holder_MARK][m_iMarkNo].y = m_iMarkSizeY;

		vision.geometricMarkPreProc(CAM1, PCB_Holder_MARK, m_iMarkNo);

		model.Save();
	}
}


void CPcbInspDlg::OnBnClickedButtonFind()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	int iMarkNo;
	CString sTemp;

	vision.clearOverlay(CAM1);

	if(vision.getLiveMode())
	{
		vision.getSnapImage(CAM1);
	}

	double ep1;
	MappTimer(M_TIMER_RESET, &ep1);
	iMarkNo = vision.findMark(CAM1, PCB_Holder_MARK);
	double ep2;
	MappTimer(M_TIMER_READ, &ep2);

	sTemp.Format(" %.3lf sec", ep2 - ep1);
	vision.textlist[CAM1].addList((CAM_SIZE_X-140), (CAM_SIZE_Y-60), sTemp, M_COLOR_GREEN, 24, 10, "Arial");

	vision.drawOverlay(CAM1);

	if (iMarkNo!=-1)
	{
#ifdef USE_GEOMETRIC
		MgraColor(M_DEFAULT, M_COLOR_GREEN);
		MmodDraw(M_DEFAULT, vision.ModResult[PCB_Holder_MARK][iMarkNo], vision.MilOverlayImage[CAM1], M_DRAW_BOX+M_DRAW_POSITION+M_DRAW_EDGES+M_DRAW_AXIS, M_DEFAULT, M_DEFAULT);
#endif
	}

	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	pFrame->m_rBox.left = 0;
	pFrame->m_rBox.top = 0;
	pFrame->m_rBox.right = 0;
	pFrame->m_rBox.bottom = 0;
}


void CPcbInspDlg::OnBnClickedRadioPos()
{
	UpdateData(true);
}


void CPcbInspDlg::OnBnClickedRadioSize()
{
	UpdateData(true);
}


void CPcbInspDlg::OnBnClickedButtonBoxUp()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	if (m_iSelMoveType==0)
	{
		m_rMarkBox.top -= m_iMoveSpeed;
		m_rMarkBox.bottom -= m_iMoveSpeed;
	}
	/* 크기 */
	else
	{
		m_rMarkBox.bottom -= m_iMoveSpeed;
	}

	if (m_rMarkBox.top<1)
	{
		m_rMarkBox.top = 1;
		m_rMarkBox.bottom = 1 + m_rcFixedBox.Height();
	}

	vision.clearOverlay(CAM1);
	vision.boxlist[CAM1].addList(m_rMarkBox, PS_DOT, M_COLOR_GREEN);
	vision.drawOverlay(CAM1);

	pFrame->m_rBox = m_rcFixedBox = m_rMarkBox;
}


void CPcbInspDlg::OnBnClickedButtonBoxDown()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	/* 이동 */
	if (m_iSelMoveType==0)
	{
		m_rMarkBox.top += m_iMoveSpeed;
		m_rMarkBox.bottom += m_iMoveSpeed;
	}
	/* 크기 */
	else
	{
		m_rMarkBox.bottom += m_iMoveSpeed;
	}

	if (m_rMarkBox.bottom>CAM_SIZE_Y-1)
	{
		m_rMarkBox.bottom	= CAM_SIZE_Y - 1;
		m_rMarkBox.top		= m_rMarkBox.bottom - m_rcFixedBox.Height();
	}

	vision.clearOverlay(CAM1);
	vision.boxlist[CAM1].addList(m_rMarkBox, PS_DOT, M_COLOR_GREEN);
	vision.drawOverlay(CAM1);

	pFrame->m_rBox = m_rcFixedBox = m_rMarkBox;
}


void CPcbInspDlg::OnBnClickedButtonBoxLeft()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	/* 이동 */
	if (m_iSelMoveType==0)
	{
		m_rMarkBox.left -= m_iMoveSpeed;
		m_rMarkBox.right -= m_iMoveSpeed;
	}
	/* 크기 */
	else
	{
		m_rMarkBox.right -= m_iMoveSpeed;
	}

	if (m_rMarkBox.left<1)
	{
		m_rMarkBox.left		= 1;
		m_rMarkBox.right	= 1 + m_rcFixedBox.Width();
	}

	vision.clearOverlay(CAM1);
	vision.boxlist[CAM1].addList(m_rMarkBox, PS_DOT, M_COLOR_GREEN);
	vision.drawOverlay(CAM1);

	pFrame->m_rBox = m_rcFixedBox = m_rMarkBox;
}


void CPcbInspDlg::OnBnClickedButtonBoxRight()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	/* 이동 */
	if (m_iSelMoveType==0)
	{
		m_rMarkBox.left += m_iMoveSpeed;
		m_rMarkBox.right += m_iMoveSpeed;
	}
	/* 크기 */
	else
	{
		m_rMarkBox.right += m_iMoveSpeed;
	}

	if (m_rMarkBox.right>CAM_SIZE_X-1)
	{
		m_rMarkBox.right	= CAM_SIZE_X - 1;
		m_rMarkBox.left		= m_rMarkBox.right - m_rcFixedBox.Width();
	}

	vision.clearOverlay(CAM1);
	vision.boxlist[CAM1].addList(m_rMarkBox, PS_DOT, M_COLOR_GREEN);
	vision.drawOverlay(CAM1);

	pFrame->m_rBox = m_rcFixedBox = m_rMarkBox;
}


void CPcbInspDlg::OnBnClickedButtonBoxSpeed()
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


void CPcbInspDlg::dispMarkImage()
{
	double dZoomX, dZoomY;

	for (int i=0 ; i<2 ; i++)
	{
		MbufClear(vision.MilMarkImage[PCB_Holder_MARK][i], 0);
		MbufClear(vision.MilMarkSmallImage[PCB_Holder_MARK][i], 0);


		if (model.m_MarkSize[PCB_Holder_MARK][i].x<=0 ||model.m_MarkSize[PCB_Holder_MARK][i].y<=0)
			continue;

		dZoomX = (double)MARK_SIZE_X/(double)model.m_MarkSize[PCB_Holder_MARK][i].x;
		dZoomY = (double)MARK_SIZE_Y/(double)model.m_MarkSize[PCB_Holder_MARK][i].y;

#ifdef USE_GEOMETRIC
		if (vision.ModModel[PCB_Holder_MARK][i]==M_NULL)	continue;

		MmodDraw(M_DEFAULT, vision.ModModel[PCB_Holder_MARK][i], vision.MilMarkImage[PCB_Holder_MARK][i], M_DRAW_IMAGE, M_DEFAULT, M_DEFAULT);
#else
		if (vision.PatModel[PCB_Holder_MARK][i]==M_NULL)	continue;

		MpatDraw(M_DEFAULT, vision.PatModel[PCB_Holder_MARK][i], vision.MilMarkImage[PCB_Holder_MARK][i], M_DRAW_IMAGE, M_DEFAULT, M_DEFAULT);
#endif

		MimResize(vision.MilMarkImage[PCB_Holder_MARK][i], vision.MilMarkSmallImage[PCB_Holder_MARK][i], dZoomX, dZoomY, M_DEFAULT);
	}
}

void CPcbInspDlg::OnBnClickedButtonMarkset()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	int iMarkSizeX = model.m_MarkSize[PCB_Holder_MARK][m_iMarkNo].x;
	int iMarkSizeY = model.m_MarkSize[PCB_Holder_MARK][m_iMarkNo].y;

#ifdef USE_GEOMETRIC
	MmodDraw(M_DEFAULT, vision.ModModel[PCB_Holder_MARK][m_iMarkNo], vision.MilTempImage, M_DRAW_IMAGE, M_DEFAULT, M_DEFAULT);
#else
	MpatDraw(M_DEFAULT, vision.PatModel[PCB_Holder_MARK][m_iMarkNo], vision.MilTempImage, M_DRAW_IMAGE, M_DEFAULT, M_DEFAULT);
#endif

	CMarkSetDlg dlg(CAM1, PCB_Holder_MARK, m_iMarkNo, iMarkSizeX, iMarkSizeY, false);

	double dZoomX = (double)MARK_SIZE_X/(double)iMarkSizeX;
	double dZoomY = (double)MARK_SIZE_Y/(double)iMarkSizeY;

	if (dlg.DoModal()==IDOK)
	{
#ifdef USE_GEOMETRIC
		MmodInquire(vision.ModModel[PCB_Holder_MARK][m_iMarkNo], M_DEFAULT, M_REFERENCE_X+M_TYPE_DOUBLE, &model.m_MarkCenter[PCB_Holder_MARK][m_iMarkNo].x);
		MmodInquire(vision.ModModel[PCB_Holder_MARK][m_iMarkNo], M_DEFAULT, M_REFERENCE_Y+M_TYPE_DOUBLE, &model.m_MarkCenter[PCB_Holder_MARK][m_iMarkNo].y);
		MmodInquire(vision.ModModel[PCB_Holder_MARK][m_iMarkNo], M_DEFAULT, M_REFERENCE_X+M_TYPE_DOUBLE, &model.m_MarkOrigin[PCB_Holder_MARK][m_iMarkNo].x);
		MmodInquire(vision.ModModel[PCB_Holder_MARK][m_iMarkNo], M_DEFAULT, M_REFERENCE_Y+M_TYPE_DOUBLE, &model.m_MarkOrigin[PCB_Holder_MARK][m_iMarkNo].y);
#else								   
		MpatInquire(vision.PatModel[PCB_Holder_MARK][m_iMarkNo], M_CENTER_X, &model.m_MarkCenter[PCB_Holder_MARK][m_iMarkNo].x);
		MpatInquire(vision.PatModel[PCB_Holder_MARK][m_iMarkNo], M_CENTER_Y, &model.m_MarkCenter[PCB_Holder_MARK][m_iMarkNo].y);
		MpatInquire(vision.PatModel[PCB_Holder_MARK][m_iMarkNo], M_ORIGINAL_X, &model.m_MarkOrigin[PCB_Holder_MARK][m_iMarkNo].x);
		MpatInquire(vision.PatModel[PCB_Holder_MARK][m_iMarkNo], M_ORIGINAL_Y, &model.m_MarkOrigin[PCB_Holder_MARK][m_iMarkNo].y);
#endif
		model.m_MarkSize[PCB_Holder_MARK][m_iMarkNo].x = iMarkSizeX;
		model.m_MarkSize[PCB_Holder_MARK][m_iMarkNo].y = iMarkSizeY;

		model.Save();
	}
}



void CPcbInspDlg::OnBnClickedButtonImgLoad()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	vision.loadImageonExplorer(CAM1);

	ctrlLiveButton();

	OnBnClickedButtonFind();
}


void CPcbInspDlg::OnBnClickedButtonImgSave()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	int liveMode = vision.getLiveMode();

	vision.saveImageonExplorer(CAM1);

	vision.setLiveMode(liveMode);
}


void CPcbInspDlg::clickedMarkDisp(int iMarkNo)
{
	if (iMarkNo==0)
	{
		m_labelDisp5.SetBkColor(M_COLOR_LIGHT_BLUE);
		m_labelDisp6.SetBkColor(M_COLOR_LIGHT_GRAY);

		m_iMarkNo = 0;
	}
	else
	{
		m_labelDisp5.SetBkColor(M_COLOR_LIGHT_GRAY);
		m_labelDisp6.SetBkColor(M_COLOR_LIGHT_BLUE);

		m_iMarkNo = 1;
	}

	m_labelDisp5.Invalidate();
	GetDlgItem(IDC_MARK_DISP1)->Invalidate();
	m_labelDisp6.Invalidate();
	GetDlgItem(IDC_MARK_DISP2)->Invalidate();
}

void CPcbInspDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	WINDOWPLACEMENT wndpl1, wndpl2;
	CRect rTemp1, rTemp2;

	m_labelDisp5.GetWindowPlacement(&wndpl1);
	m_labelDisp6.GetWindowPlacement(&wndpl2);

	rTemp1 = wndpl1.rcNormalPosition;
	rTemp2 = wndpl2.rcNormalPosition;

	if (PtInRect(rTemp1, point))
		clickedMarkDisp(0);
	if (PtInRect(rTemp2, point))
		clickedMarkDisp(1);

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CPcbInspDlg::OnBnClickedButtonVaccumOn()
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


	if(Task.AutoFlag ==2) return;

	Dio.PCBvaccumOn(VACCUM_ON, false);
}


void CPcbInspDlg::OnBnClickedButtonVaccumOff()
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

	if(Task.AutoFlag ==2) return;

	Dio.PCBvaccumOn(VACCUM_OFF, false);
}


BEGIN_EVENTSINK_MAP(CPcbInspDlg, CDialogEx)
	//ON_EVENT(CPcbInspDlg, IDC_MSFLEXGRID_MARK, DISPID_DBLCLICK, CPcbInspDlg::DblClickMsflexgridMark, VTS_NONE)
END_EVENTSINK_MAP()


void CPcbInspDlg::DblClickMsflexgridMark()
{
	/*if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	int col = m_gridMark.GetMouseCol();
	int row = m_gridMark.GetMouseRow();


	CString celData = m_gridMark.GetTextMatrix(row, col);


	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		CString curStr = dlg.GetstrNum();

		int iVal = atoi(curStr);
		if(iVal<30)		iVal = 30;
		if(iVal>100)	iVal = 100;

		celData.Format("%d", iVal);

		m_gridMark.SetTextMatrix(row, col, celData);
	}*/
}



void CPcbInspDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent==PCB_TIMER)
	{
		if (!timerRunFlag)
		{
			timerRunFlag = true;

			changeColorMotorPosBtn();

			// IO 버튼 추가..
			//changeColorVaccumBtn();
			changeColorPushBtn();		//PCB Cover 전/후진 On 상태 Check
			changeColorDarkBtn();		//Dark 검사 실린더 Up/Down 상태 Check

			timerRunFlag = false;
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CPcbInspDlg::OnBnClickedButtonAlignTest2()
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

	double offsetX, offsetY, offsetTh;
	int iRtnVal;
	int  iRtn = pFrame->procCamAlign(CAM1, PCB_Holder_MARK, true, offsetX, offsetY, offsetTh);

	if (iRtn == 0)
	{
		iRtnVal = pFrame->AlignLimitCheck(CAM1, offsetX, offsetY, offsetTh);


		if(iRtnVal==0)
		{
			sLangChange.LoadStringA(IDS_STRING1263);
			errMsg2(Task.AutoFlag, sLangChange);
		}
		else
		{
			short axis[3];
			double pos[3];

			axis[0] = Motor_PCB_X;
			axis[1] = Motor_PCB_Y;
			axis[2] = Motor_PCB_TH;

			pos[0]	= motor.GetCommandPos(Motor_PCB_X)	- offsetX;
			pos[1]	= motor.GetCommandPos(Motor_PCB_Y)	- offsetY;
			pos[2]	= motor.GetCommandPos(Motor_PCB_TH)	+ offsetTh;

			motor.goMotorPos(3, axis, pos);
			sLangChange.LoadStringA(IDS_STRING1261);
			delayMsg(sLangChange, 3000, M_COLOR_GREEN);
			Sleep(10);

			pos[0]	= (pos[0] - model.axis[Motor_PCB_X].pos[Align_Pos]);
			pos[1]	= (pos[1] - model.axis[Motor_PCB_Y].pos[Align_Pos]);
			pos[2]	= (pos[2] - model.axis[Motor_PCB_TH].pos[Align_Pos]);

			CString sTemp;
			sTempLang.LoadStringA(IDS_STRING1264);
			sLangChange.Format(sTempLang, pos[0], pos[1], pos[2]);
			sTemp.Format(sLangChange, pos[0], pos[1], pos[2]);
			m_labelAlignResult.SetText(sTemp);
			m_labelAlignResult.Invalidate();

			double etime = myTimer(true);
			while(1)
			{
				if(motor.IsStopAxis(Motor_PCB_X)  && motor.IsStopAxis(Motor_PCB_Y)  && motor.IsStopAxis(Motor_PCB_TH))		
				{
					Sleep(20);
					break;
				}
				if((myTimer(true) - etime) > 3000)
				{
					sLangChange.LoadStringA(IDS_STRING1260);
					delayMsg(sLangChange, 3000, M_COLOR_RED);
					break;
				}
			}
		}
	}
	else
		sLangChange.LoadStringA(IDS_STRING1215);
		errMsg2(Task.AutoFlag, sLangChange);

	CString sLog;
	sTempLang.LoadStringA(IDS_STRING1467);
	sLangChange.Format(sTempLang, offsetX, offsetY, offsetTh);
	sLog.Format(sLangChange);
	pFrame->putListLog(sLog);

	pFrame->m_rBox.left = 0;
	pFrame->m_rBox.top = 0;
	pFrame->m_rBox.right = 0;
	pFrame->m_rBox.bottom = 0;
}


void CPcbInspDlg::OnBnClickedButtonMotorWait()
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

	CString sTmpLog;
	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;
	g_bMovingflag =true;
	if( !func_MovingInterlock() )	return;
	
	if( !motor.Pcb_Tilt_Motor_Move(Wait_Pos))
	{
		sLangChange.LoadStringA(IDS_STRING1017);	//PCB부 Tx, Ty축 대기 위치 이동 실패
		sTmpLog.Format(sLangChange);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
		g_bMovingflag =false;
		return;
	}

	if(!motor.Pcb_Motor_Move(Wait_Pos))
	{
		sLangChange.LoadStringA(IDS_STRING1020);	//PCB부 X, Y, Theta축 대기 위치 이동 실패
		sTmpLog.Format(sLangChange);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
		g_bMovingflag =false;
		return;
	}
	sLangChange.LoadStringA(IDS_STRING899);	//"PCB %s 이동 완료"
	sTmpLog.Format(sLangChange, MotorPosName[Wait_Pos]);
	delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);

	g_bMovingflag =false;
}

void CPcbInspDlg::OnBnClickedButtonMotorAlign()
{
	if( !func_TaskMovingCheck() )	return;

	/* 이동중이면 Return */
	g_bMovingflag =true;

	if( !func_MovingInterlock() )	return;


	if(motor.Pcb_Motor_Move(Holder_Pos))
	{
		CString sTmpLog;
		sLangChange.LoadStringA(IDS_STRING899);	//"PCB %s 이동 완료"
		sTmpLog.Format(sLangChange, MotorPosName[Align_Pos]);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
	}

	g_bMovingflag =false;
}


void CPcbInspDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rcTemp1, rcTemp2;
	WINDOWPLACEMENT wndpl1, wndpl2;
	GetDlgItem(IDC_MARK_DISP1)->GetWindowPlacement(&wndpl1);
	GetDlgItem(IDC_MARK_DISP2)->GetWindowPlacement(&wndpl2);
	rcTemp1 = wndpl1.rcNormalPosition;
	rcTemp2 = wndpl2.rcNormalPosition;

	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	CPoint p = point;
	p.x -= pFrame->m_rectCamDispPos2.left;
	p.y -= pFrame->m_rectCamDispPos2.top + SUB_DLG_OFFSET_Y;

	if (PtInRect(rcTemp1, p))
		clickedMarkDisp(0);
	else if (PtInRect(rcTemp2, p))
		clickedMarkDisp(1);
	else
		return;

	CMenu* pMenu = NULL;
	CMenu* pSubMenu= NULL;

	pMenu = new CMenu();
	pMenu->LoadMenu(IDR_MENU1);
	pSubMenu = pMenu->GetSubMenu(0);

	if (m_bCopyFlag)	pSubMenu->EnableMenuItem(ID_Menu_PASTE, MF_ENABLED);
	else				pSubMenu->EnableMenuItem(ID_Menu_PASTE, MF_GRAYED);

	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

void CPcbInspDlg::OnMenuCopy()
{
	m_bCopyFlag = true;

	m_iCopyMarkNo = m_iMarkNo;
}

void CPcbInspDlg::OnMenuDelete()
{
	model.m_MarkCenter[PCB_Holder_MARK][m_iMarkNo].x	=	0.0f;
	model.m_MarkCenter[PCB_Holder_MARK][m_iMarkNo].y	=	0.0f;
	model.m_MarkSize[PCB_Holder_MARK][m_iMarkNo].x		=	0;
	model.m_MarkSize[PCB_Holder_MARK][m_iMarkNo].y		=	0;
	model.m_iLimitRate[PCB_Holder_MARK][m_iMarkNo]		=	70;

	CString sDelFile;

#ifdef USE_GEOMETRIC
	MmodFree(vision.ModModel[PCB_Holder_MARK][m_iMarkNo]);
	vision.ModModel[PCB_Holder_MARK][m_iMarkNo] = M_NULL;

	sDelFile.Format("%s\\Model\\%s\\PCB_Mark_%d.mod", DATA_DIR, model.name, m_iMarkNo);
#else
	MpatFree(vision.PatModel[PCB_Holder_MARK][m_iMarkNo]);
	vision.PatModel[PCB_Holder_MARK][m_iMarkNo] = M_NULL;

	sDelFile.Format("%s\\Model\\%s\\PCB_Mark_%d.pat", DATA_DIR, model.name, m_iMarkNo);
#endif

	::DeleteFile(sDelFile);

	model.Save();
	//	model.Load();

	dispMarkImage();
}


void CPcbInspDlg::OnMenuPaste()
{
	m_bCopyFlag =false;

#ifdef USE_GEOMETRIC
	if (vision.ModModel[PCB_Holder_MARK][m_iCopyMarkNo]==NULL)
		return;
#else
	if (vision.PatModel[PCB_Holder_MARK][m_iCopyMarkNo]==NULL)
		return;
#endif

	model.m_MarkCenter[PCB_Holder_MARK][m_iMarkNo].x	=	model.m_MarkCenter[PCB_Holder_MARK][m_iCopyMarkNo].x;
	model.m_MarkCenter[PCB_Holder_MARK][m_iMarkNo].y	=	model.m_MarkCenter[PCB_Holder_MARK][m_iCopyMarkNo].y;
	model.m_MarkSize[PCB_Holder_MARK][m_iMarkNo]		=	model.m_MarkSize[PCB_Holder_MARK][m_iCopyMarkNo];
	model.m_iLimitRate[PCB_Holder_MARK][m_iMarkNo]		=	model.m_iLimitRate[PCB_Holder_MARK][m_iCopyMarkNo];

	CString sScr, sDes;
#ifdef USE_GEOMETRIC
	sScr.Format("%s\\Model\\%s\\PCB_Mark_%d.mod", DATA_DIR, model.name, m_iCopyMarkNo);
	sDes.Format("%s\\Model\\%s\\PCB_Mark_%d.mod", DATA_DIR, model.name, m_iMarkNo);
#else
	sScr.Format("%s\\Model\\%s\\PCB_Mark_%d.pat", DATA_DIR, model.name, m_iCopyMarkNo);
	sDes.Format("%s\\Model\\%s\\PCB_Mark_%d.pat", DATA_DIR, model.name, m_iMarkNo);
#endif

	::CopyFile(sScr, sDes, FALSE);

	model.loadMark(CAM1, PCB_Holder_MARK, m_iMarkNo);
	model.Save();

	vision.geometricMarkPreProc(CAM1, PCB_Holder_MARK, m_iMarkNo);

	dispMarkImage();
}


void CPcbInspDlg::changeColorVaccumBtn()
{
	int moduleNo = 0;
	int channelNo = 1;

	bool bOutVaccumFlag, bOutBlowFlag, bInVaccumOnFlag;			// 둘 다 OFF 시 흡착, Vaccum만 살면 탈착

	bInVaccumOnFlag = Dio.PCBvaccumOnCheck(true, false);


	bOutVaccumFlag = (curOutDioByte[moduleNo][channelNo] & DIO_OUT_PCB_VACUUM) ? true : false;
	bOutBlowFlag = (curOutDioByte[moduleNo][channelNo] & DIO_OUT_PCB_VACUUM_OFF) ? true : false;


	/*if(!bOutVaccumFlag && !bOutBlowFlag)
	{
		if(bInVaccumOnFlag)
		{
			vaccumErrCnt = 0;

			m_btnVaccumOn.m_iStateBtn	= 1;
			m_btnVaccumOff.m_iStateBtn	= 0;
		}
		else
		{
			if(vaccumErrCnt<5)
				m_btnVaccumOn.m_iStateBtn	= 0;
			else 
				m_btnVaccumOn.m_iStateBtn	= 2;
		
			if(vaccumErrCnt >=10)
				vaccumErrCnt = 0;

			vaccumErrCnt++;
			m_btnVaccumOff.m_iStateBtn	= 0;
		}
	}*/


	if (bInVaccumOnFlag)
	{
		m_btnVaccumOn.m_iStateBtn	= 1;
		m_btnVaccumOff.m_iStateBtn	= 0;
	}
	else
	{
		m_btnVaccumOn.m_iStateBtn	= 0;
		m_btnVaccumOff.m_iStateBtn	= 1;
	}

	m_btnVaccumOn.Invalidate();
	m_btnVaccumOff.Invalidate();
}

bool CPcbInspDlg::checkCurMotorPos(int iPos)
{
	double dCurPos;
	double dMotorPos;

	for (int i=Motor_PCB_X ; i<=Motor_PCB_TH; i++)
	{
		dCurPos		= motor.GetEncoderPos(i);	//motor.GetCommandPos(i);
		dMotorPos	= model.axis[i].pos[iPos];

		if (iPos==4)
		{
			if (i==0)		dMotorPos	= model.axis[i].pos[Bonding_Pos] + Task.d_Align_offset_x[PCB_Holder_MARK];
			else if (i==1)	dMotorPos	= model.axis[i].pos[Bonding_Pos] + Task.d_Align_offset_y[PCB_Holder_MARK];
			else if (i==2)	dMotorPos	= model.axis[i].pos[Bonding_Pos] + Task.d_Align_offset_th[PCB_Holder_MARK];
		}

		if (fabs(dMotorPos-dCurPos) > 0.01)
			return false;
	}

	return true;
}

bool CPcbInspDlg::checkCurMotorPosZ(int iPos)
{	/* 모터 위치 확인 */
	double dCurPos;
	double dMotorPos;

	
	dCurPos		= motor.GetEncoderPos(Motor_PCB_Z);	//motor.GetCommandPos(i);
	dMotorPos	= model.axis[Motor_PCB_Z].pos[iPos];

	if (fabs(dMotorPos-dCurPos) > 0.01)
		return false;

	return true;
}

void CPcbInspDlg::changeColorMotorPosBtn()
{
	int iIndex = - 1;

	if (checkCurMotorPos(Wait_Pos))				iIndex = 0;
	else if (checkCurMotorPos(Holder_Pos))		iIndex = 1;
	else if ( checkCurMotorPos(Defect_Pos) )	iIndex = 2;
	else if ( checkCurMotorPos(Dark_Pos) )		iIndex = 3;
	else if (checkCurMotorPos(Bonding_Pos))		iIndex = 4;	

	m_btnWaitPos.m_iStateBtn = 0;
	m_btnAlignPos.m_iStateBtn = 0;
	m_btnDefectPos.m_iStateBtn = 0;
	m_btnDarkPos.m_iStateBtn = 0;
	m_btnBondPos.m_iStateBtn = 0;

	//m_btn_LaserOUT1.m_iStateBtn = 0;
	//m_btn_LaserOUT2.m_iStateBtn = 0;
	//m_btn_LaserOUT3.m_iStateBtn = 0;
	//m_btn_LaserOUT4.m_iStateBtn = 0;

	if (iIndex==0)			m_btnWaitPos.m_iStateBtn = 3;
	else if (iIndex==1)		m_btnAlignPos.m_iStateBtn = 3;
	else if (iIndex==2)		m_btnDefectPos.m_iStateBtn = 3;
	else if (iIndex==3)		m_btnDarkPos.m_iStateBtn = 3;
	else if (iIndex==4)		m_btnBondPos.m_iStateBtn = 3;

	m_btnWaitPos.Invalidate();
	m_btnAlignPos.Invalidate();
	m_btnDefectPos.Invalidate();
	m_btnDarkPos.Invalidate();
	m_btnBondPos.Invalidate();
}


void CPcbInspDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	UpdateData(true);
	CSliderCtrl *Slider=(CSliderCtrl*)pScrollBar;
	CString strTemp;

	int Pos = Slider->GetPos();

	if((UINT)pScrollBar==(UINT)&m_sliderBright)
	{
		if(Pos>=0 && Pos<=255)
		{
			strTemp.Format("%d", m_sliderBright.GetPos());
			GetDlgItem(IDC_EDIT_Bright)->SetWindowText(strTemp);
			g_iPBrightInsp = Pos;

			long chRef;
			chRef = M_CH1_REF;

			MdigReference(vision.MilDigitizer, M_BLACK_REF+chRef, g_iPBrightInsp);			
		}
	}
	else if((UINT)pScrollBar==(UINT)&m_sliderContrast)
	{
		if(Pos>=0 && Pos<=255)
		{
			strTemp.Format("%d", m_sliderContrast.GetPos());
			GetDlgItem(IDC_EDIT_Contrast)->SetWindowText(strTemp);
			g_iPContrastInsp = Pos; 

			long chRef;
			chRef = M_CH1_REF;

			MdigReference(vision.MilDigitizer, M_WHITE_REF+chRef, g_iPContrastInsp);
		}
	}

	UpdateData(false);	

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CPcbInspDlg::OnClickedEditBright()
{
	long chRef;
	chRef = M_CH1_REF;
	CString celData;
	int iTemp;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		m_LabelBright.SetText(dlg.GetstrNum());
	}	

	iTemp = atoi(dlg.GetstrNum());
	m_sliderBright.SetPos(iTemp);

	if(Task.AutoFlag != 1)
	{
		g_iPBrightInsp = iTemp; 
		MdigReference(vision.MilDigitizer, M_BLACK_REF+chRef, g_iPBrightInsp);
	}
}


void CPcbInspDlg::OnClickedEditContrast()
{
	long chRef;
	chRef = M_CH1_REF;
	CString celData;
	int iTemp;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		m_LabelContrast.SetText(dlg.GetstrNum());
	}	

	iTemp = atoi(dlg.GetstrNum());
	m_sliderContrast.SetPos(iTemp);

	if(Task.AutoFlag != 1)
	{
		g_iPContrastInsp = iTemp;
		MdigReference(vision.MilDigitizer, M_WHITE_REF+chRef,g_iPContrastInsp);
	}
}

void CPcbInspDlg::DigLedputData()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)(AfxGetApp()->m_pMainWnd);
	long chRef;
	chRef = M_CH1_REF;

	if (g_iPBrightInsp<0)			g_iPBrightInsp = 0;
	else if (g_iPBrightInsp<0)		g_iPBrightInsp = 0;

	if (g_iPContrastInsp<0)			g_iPContrastInsp = 0;
	else if (g_iPContrastInsp<0)	g_iPContrastInsp = 0;

	CString tmpStr="";
	tmpStr.Format("%d", model.m_iBright[PCB_Holder_MARK]);
	GetDlgItem(IDC_EDIT_Bright)->SetWindowText(tmpStr);
	m_sliderBright.SetPos(model.m_iBright[PCB_Holder_MARK]);

	tmpStr.Format("%d", model.m_iContrast[PCB_Holder_MARK]);
	GetDlgItem(IDC_EDIT_Contrast)->SetWindowText(tmpStr);
	m_sliderContrast.SetPos(model.m_iContrast[PCB_Holder_MARK]);

	//pFrame->SetDigReference(PCB_Holder_MARK);

	UpdateData(false);
}

void CPcbInspDlg::OnBnClickedButtonLaserDlgOpen()
{
	if (m_pDisplacementDlg->IsWindowVisible())
		m_pDisplacementDlg->ShowWindow(false);
	else
		m_pDisplacementDlg->ShowWindow(true);
}


void CPcbInspDlg::OnBnClickedButtonLaserManualSerach2()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	double dVel;

	Keyence.func_LT9030_Scan(dVel);

	CString sLog;
	sLangChange.LoadStringA(IDS_STRING635);	//Laser 수동 측정 값(mm) : %lf
	sLog.Format(sLangChange, dVel);
	pFrame->putListLog(sLog);
}


bool CPcbInspDlg::func_TaskMovingCheck()
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

	if(g_bMovingflag)
	{
		sLangChange.LoadStringA(IDS_STRING1228);	//모터 구동 중 사용 불가..
		delayMsg(sLangChange, 2000, M_COLOR_RED);
		return false;
	}

	if(Dio.PCBCoverCloseCheck(true, false) == false)
	{
		CString sTemp;
		sLangChange.LoadStringA(IDS_STRING1026);	//PCB부 커버 소켓이 열려 있습니다.
		sTemp.Format(sLangChange);
		delayMsg(sTemp.GetBuffer(99), 3000, M_COLOR_DARK_GREEN);
		return false;
	}
	return true;
}


bool CPcbInspDlg::func_MovingInterlock()
{
	//if(!motor.LENS_Z_Motor_Move(Wait_Pos))
	//{
	//	delayMsg("Lens_Z축 대기위치 이동 실패.", 1000, M_COLOR_RED);
	//	g_bMovingflag = false;
	//	return false;
	//}
	//if(!motor.PCB_Z_Motor_Move(Wait_Pos))
	//{
	//	sLangChange.LoadStringA(IDS_STRING1012);	//PCB_Z축 대기위치 이동 실패.
	//	delayMsg(sLangChange, 1000, M_COLOR_RED);
	//	g_bMovingflag = false;
	//	return false;
	//}
	
	//if( !Dio.PCBDarkCheck(true, false) )
	//{//Dark 검사 실린더 하강일 경우 상승
	//	if( !Dio.PCBDark(true, true) )
	//	{
	//		sLangChange.LoadStringA(IDS_STRING488);	//Dark검사 실린더 상승 실패.
	//		delayMsg(sLangChange, 1000, M_COLOR_RED);
	//		g_bMovingflag =false;
	//		return false;
	//	}
	//}

	return true;
}

void CPcbInspDlg::OnBnClickedButtonMotorLaserOut1()
{
	if( !func_TaskMovingCheck() )	return;

	/* 이동중이면 Return */
	g_bMovingflag =true;
	if( !func_MovingInterlock() )	return;

	if( motor.Pcb_Motor_Move_Laser(4) )
	{
		CString sTmpLog;
		sLangChange.LoadStringA(IDS_STRING1024);	//"PCB부 외부 Laser 변위 측정 1차위치 이동 완료"
		sTmpLog.Format(sLangChange);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
	}

	g_bMovingflag =false;
}


void CPcbInspDlg::OnBnClickedButtonMotorLaserOut2()
{
	if( !func_TaskMovingCheck() )	return;

	/* 이동중이면 Return */
	g_bMovingflag =true;

	if( !func_MovingInterlock() )	return;

	if( motor.Pcb_Motor_Move_Laser(5) )
	{
		CString sTmpLog;
		sLangChange.LoadStringA(IDS_STRING1486);	//"PCB부 외부 Laser 변위 측정 2차위치 이동 완료"
		sTmpLog.Format(sLangChange);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
	}

	g_bMovingflag =false;
}


void CPcbInspDlg::OnBnClickedButtonMotorLaserOut3()
{
	if( !func_TaskMovingCheck() )	return;

	/* 이동중이면 Return */
	g_bMovingflag =true;
	if( !func_MovingInterlock() )	return;

	if( motor.Pcb_Motor_Move_Laser(6) )
	{
		CString sTmpLog;
		sLangChange.LoadStringA(IDS_STRING1487);	//"PCB부 외부 Laser 변위 측정 3차위치 이동 완료"
		sTmpLog.Format(sLangChange);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
	}

	g_bMovingflag =false;
}


void CPcbInspDlg::OnBnClickedButtonMotorLaserOut4()
{
	if( !func_TaskMovingCheck() )	return;

	/* 이동중이면 Return */
	g_bMovingflag =true;
	if( !func_MovingInterlock() )	return;

	if( motor.Pcb_Motor_Move_Laser(7) )
	{
		CString sTmpLog;
		sLangChange.LoadStringA(IDS_STRING1488);	//"PCB부 외부 Laser 변위 측정 4차위치 이동 완료"
		sTmpLog.Format(sLangChange);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
	}

	g_bMovingflag =false;
}


void CPcbInspDlg::OnBnClickedButtonMotorAlignLaserPosOut()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	CDPoint LaserPos[4];
	CString sLog;
	int iLaserDelay = model.strInfo_Cam[0].m_iDelayTime;	//Laser 측정전 Delay
	double dTx, dTy;

	if( !func_TaskMovingCheck() )	return;

	/* 이동중이면 Return */
	g_bMovingflag =true;
	if( !func_MovingInterlock() )	return;

	m_btnAlignLaserPosOut.m_iStateBtn = 1;
	m_btnAlignLaserPosOut.Invalidate();
	for(int iNo = 0; iNo < 4; iNo++)
	{
		motor.Pcb_Motor_Move_Laser(iNo+4);

		Task.PCBTaskTime = myTimer(true);
		while(1)
		{
			if((myTimer(true) - Task.PCBTaskTime) > iLaserDelay && (motor.IsStopAxis(Motor_PCB_X) && motor.IsStopAxis(Motor_PCB_Y)))
			{
				break;
			}
			else if( (myTimer(true) - Task.PCBTaskTime) > iLaserDelay*2 )
			{
				sLangChange.LoadStringA(IDS_STRING1257);	//변위 측정 위치 이동 완료 시간 초과....
				delayMsg(sLangChange, 2000, M_COLOR_RED);
				g_bMovingflag = false;
				return;
			}

			checkMessage();
			Sleep(5);
			checkMessage();
		}

		Keyence.func_LT9030_Scan(Task.m_Laser_Point[iNo]);

		LaserPos[iNo].x = motor.GetEncoderPos(Motor_PCB_X);
		LaserPos[iNo].y = motor.GetEncoderPos(Motor_PCB_Y);

		sLangChange.LoadStringA(IDS_STRING636);	//Laser 외부 측정값 (%d) : %.04f
		sLog.Format(sLangChange, iNo+1, Task.m_Laser_Point[iNo]);
		pFrame->putListLog(sLog);

		checkMessage();
		Sleep(5);
		checkMessage();
	}

	g_bMovingflag = false;
	pFrame->_calcLaserTilt(LaserPos, Task.m_Laser_Point, dTx, dTy);
	
	m_btnAlignLaserPosOut.m_iStateBtn = 0;
	m_btnAlignLaserPosOut.Invalidate();
	sLangChange.LoadStringA(IDS_STRING622);	//Laser Tilting 외부 보정값 X:%.04f, Y:%.04f
	sLog.Format(sLangChange, dTx, dTy);
	pFrame->putListLog(sLog);
}

void CPcbInspDlg::changeColorPushBtn()
{
	int moduleNo = 2;
	int channelNo = 2;

	bool bOutPushForFlag	= (curOutDioByte[moduleNo][channelNo] & DIO_OUT_PCB_PUSH_FOR) ? true : false;
	bool bOutPushBackFlag	= (curOutDioByte[moduleNo][channelNo] & DIO_OUT_PCB_PUSH_BACK) ? true : false;

	bool bInPushForFlag		= (curInDio[1] & DIO_IN_PCB_PUSH_FOR) ? true : false;
	bool bInPushBackFlag	= (curInDio[1] & DIO_IN_PCB_PUSH_BACK) ? true : false;


	if(bOutPushForFlag && !bOutPushBackFlag)			// 전진..
	{
		if(bInPushForFlag && !bInPushBackFlag)
		{
			m_btnPushFor.m_iStateBtn	= 1;
			m_btnPushBack.m_iStateBtn	= 0;
			pushErrCnt = 0;
		}
		else
		{
			if(bInPushForFlag && bInPushBackFlag)
			{
				m_btnPushFor.m_iStateBtn	= 1;

				if(pushErrCnt>5)
					m_btnPushBack.m_iStateBtn	= 0;
				else
					m_btnPushBack.m_iStateBtn	= 2;
			}
			else if(!bInPushForFlag && !bInPushBackFlag)
			{

				if(pushErrCnt>5)
					m_btnPushFor.m_iStateBtn	= 0;
				else
					m_btnPushFor.m_iStateBtn	= 2;

				m_btnPushBack.m_iStateBtn	= 0;
			}
			else // if(!bInPushForFlag && bInPushBackFlag)
			{
				if(pushErrCnt>5)
				{
					m_btnPushFor.m_iStateBtn	= 0;
					m_btnPushBack.m_iStateBtn	= 0;
				}
				else
				{
					m_btnPushFor.m_iStateBtn	= 2;
					m_btnPushBack.m_iStateBtn	= 1;
				}
			}

			if(pushErrCnt>10)
				pushErrCnt = 0;

			pushErrCnt++;
		}
	}
	else if(!bOutPushForFlag && bOutPushBackFlag)		// 후진..
	{
		if(!bInPushForFlag && bInPushBackFlag)
		{
			m_btnPushFor.m_iStateBtn	= 0;
			m_btnPushBack.m_iStateBtn	= 1;
			pushErrCnt = 0;
		}
		else
		{
			if(bInPushForFlag && bInPushBackFlag)
			{
				if(pushErrCnt>5)
					m_btnPushFor.m_iStateBtn	= 0;
				else
					m_btnPushFor.m_iStateBtn	= 1;

				m_btnPushBack.m_iStateBtn	= 1;
			}
			else if(!bInPushForFlag && !bInPushBackFlag)
			{
				m_btnPushFor.m_iStateBtn	= 0;

				if(pushErrCnt>5)
					m_btnPushBack.m_iStateBtn	= 0;
				else
					m_btnPushBack.m_iStateBtn	= 2;
			}
			else // if(!bInPushForFlag && bInPushBackFlag)
			{
				if(pushErrCnt>5)
				{
					m_btnPushFor.m_iStateBtn	= 0;
					m_btnPushBack.m_iStateBtn	= 0;
				}
				else
				{
					m_btnPushFor.m_iStateBtn	= 1;
					m_btnPushBack.m_iStateBtn	= 2;
				}
			}

			if(pushErrCnt>10)
				pushErrCnt = 0;

			pushErrCnt++;
		}
	}
	else
	{
		if(bInPushForFlag)
			m_btnPushFor.m_iStateBtn	= 1;
		else
			m_btnPushFor.m_iStateBtn	= 0;

		if(bInPushBackFlag)
			m_btnPushBack.m_iStateBtn	= 1;
		else
			m_btnPushBack.m_iStateBtn	= 0;
	}

	m_btnPushFor.Invalidate();
	m_btnPushBack.Invalidate();
}

void CPcbInspDlg::changeColorDarkBtn()
{
	int moduleNo = 2;
	int channelNo = 2;

	bool bOutPushForFlag	= motor.PCB_Z_Motor_Move(Dark_Pos) ? true : false;
	bool bOutPushBackFlag	= motor.PCB_Z_Motor_Move(Wait_Pos) ? true : false;

	bool bInPushForFlag		= motor.GetEncoderPos(Motor_PCB_Z) == model.axis[Motor_PCB_Z].pos[Dark_Pos] ? true : false;
	bool bInPushBackFlag	= motor.GetEncoderPos(Motor_PCB_Z) == model.axis[Motor_PCB_Z].pos[Wait_Pos] ? true : false;


	if(bOutPushForFlag && !bOutPushBackFlag)			// 전진..
	{
		if(bInPushForFlag && !bInPushBackFlag)
		{
			m_btnDarkUp.m_iStateBtn	= 1;
			m_btnDarkDown.m_iStateBtn = 0;
			pushErrCnt = 0;
		}
		else
		{
			if(bInPushForFlag && bInPushBackFlag)
			{
				m_btnDarkUp.m_iStateBtn	= 1;

				if(pushErrCnt>5)
					m_btnDarkDown.m_iStateBtn	= 0;
				else
					m_btnDarkDown.m_iStateBtn	= 2;
			}
			else if(!bInPushForFlag && !bInPushBackFlag)
			{

				if(pushErrCnt>5)
					m_btnDarkUp.m_iStateBtn	= 0;
				else
					m_btnDarkUp.m_iStateBtn	= 2;

				m_btnDarkDown.m_iStateBtn	= 0;
			}
			else // if(!bInPushForFlag && bInPushBackFlag)
			{
				if(pushErrCnt>5)
				{
					m_btnDarkUp.m_iStateBtn	= 0;
					m_btnDarkDown.m_iStateBtn	= 0;
				}
				else
				{
					m_btnDarkUp.m_iStateBtn	= 2;
					m_btnDarkDown.m_iStateBtn	= 1;
				}
			}

			if(pushErrCnt>10)
				pushErrCnt = 0;

			pushErrCnt++;
		}
	}
	else if(!bOutPushForFlag && bOutPushBackFlag)		// 후진..
	{
		if(!bInPushForFlag && bInPushBackFlag)
		{
			m_btnDarkUp.m_iStateBtn	= 0;
			m_btnDarkDown.m_iStateBtn	= 1;
			pushErrCnt = 0;
		}
		else
		{
			if(bInPushForFlag && bInPushBackFlag)
			{
				if(pushErrCnt>5)
					m_btnDarkUp.m_iStateBtn	= 0;
				else
					m_btnDarkUp.m_iStateBtn	= 1;

				m_btnDarkDown.m_iStateBtn	= 1;
			}
			else if(!bInPushForFlag && !bInPushBackFlag)
			{
				m_btnDarkUp.m_iStateBtn	= 0;

				if(pushErrCnt>5)
					m_btnDarkDown.m_iStateBtn	= 0;
				else
					m_btnDarkDown.m_iStateBtn	= 2;
			}
			else // if(!bInPushForFlag && bInPushBackFlag)
			{
				if(pushErrCnt>5)
				{
					m_btnDarkUp.m_iStateBtn	= 0;
					m_btnDarkDown.m_iStateBtn	= 0;
				}
				else
				{
					m_btnDarkUp.m_iStateBtn	= 1;
					m_btnDarkDown.m_iStateBtn	= 2;
				}
			}

			if(pushErrCnt>10)
				pushErrCnt = 0;

			pushErrCnt++;
		}
	}
	else
	{
		if(bInPushForFlag)
			m_btnDarkUp.m_iStateBtn	= 1;
		else
			m_btnDarkUp.m_iStateBtn	= 0;

		if(bInPushBackFlag)
			m_btnDarkDown.m_iStateBtn	= 1;
		else
			m_btnDarkDown.m_iStateBtn	= 0;
	}

	m_btnDarkUp.Invalidate();
	m_btnDarkDown.Invalidate();
}

void CPcbInspDlg::OnBnClickedButtonPcbCoverFor()
{
	if( !func_TaskMovingCheck() )	return;

	g_bMovingflag = true;

	Dio.PCBPush(true, false);

	g_bMovingflag = false;
}

void CPcbInspDlg::OnBnClickedButtonPcbCoverBack()
{
	if( !func_TaskMovingCheck() )	return;
	
	g_bMovingflag =true;

	Dio.PCBPush(false, false);

	g_bMovingflag =false;
}


void CPcbInspDlg::OnBnClickedButtonPcbDarkUp()
{
	if( !func_TaskMovingCheck() )	return;

	g_bMovingflag =true;

	Dio.PCBDark(true, false);

	g_bMovingflag =false;
}


void CPcbInspDlg::OnBnClickedButtonPcbDarkDown()
{
	if( !func_TaskMovingCheck() )	return;

	g_bMovingflag =true;

	Dio.PCBDark(false, false);

	g_bMovingflag =false;
}


void CPcbInspDlg::OnBnClickedButtonMotorDarkInsp()
{
	if( !func_TaskMovingCheck() )	return;

	g_bMovingflag =true;

	if( !func_MovingInterlock() )	return;

	if(motor.Pcb_Motor_Move(Dark_Pos))
	{
		CString sTmpLog;
		sLangChange.LoadStringA(IDS_STRING899);	//"PCB %s 이동 완료"
		sTmpLog.Format(sLangChange, MotorPosName[Dark_Pos]);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
	}

	g_bMovingflag = false;
}


void CPcbInspDlg::OnBnClickedButtonMotorDefectInsp()
{
	if( !func_TaskMovingCheck() )	return;

	g_bMovingflag =true;

	if( !func_MovingInterlock() )	return;

	if(motor.Pcb_Motor_Move(Defect_Pos))
	{
		CString sTmpLog;
		sLangChange.LoadStringA(IDS_STRING899);	//"PCB %s 이동 완료"
		sTmpLog.Format(sLangChange, MotorPosName[Defect_Pos]);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
	}

	g_bMovingflag = false;
}


void CPcbInspDlg::OnBnClickedButtonMotorBond()
{
	CString sTmpLog;

	if( !func_TaskMovingCheck() )	return;

	g_bMovingflag =true;

	if( !func_MovingInterlock() )	return;

	if(	motor.Pcb_Motor_Move(Bonding_Pos))
	{
		sLangChange.LoadStringA(IDS_STRING1015);	//PCB부 %s 이동 완료
		sTmpLog.Format(sLangChange, MotorPosName[Bonding_Pos]);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
	}

	g_bMovingflag =false;
}


void CPcbInspDlg::OnBnClickedButtonMotorBond2()
{
	if( !func_TaskMovingCheck() )	return;
	
	g_bMovingflag =true;
	if( !func_MovingInterlock() )	return;

	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	double offsetX, offsetY, offsetTh;
	int iRtnVal;

	int  iRtn = pFrame->procCamAlign(CAM1, PCB_Holder_MARK, false, offsetX, offsetY, offsetTh);

	if (iRtn == 0)
	{
		iRtnVal = pFrame->AlignLimitCheck(CAM1, offsetX, offsetY, offsetTh);

		double pos[3];
		if(iRtnVal==0)
		{
			sLangChange.LoadStringA(IDS_STRING1263);	//보정값 이동 범위가 Limit 초과 했습니다.
			errMsg2(Task.AutoFlag, sLangChange);
		}
		else
		{			
			pos[0]	= (motor.GetCommandPos(Motor_PCB_X) - model.axis[Motor_PCB_X].pos[Holder_Pos])	- offsetX;
			pos[1]	= (motor.GetCommandPos(Motor_PCB_Y) - model.axis[Motor_PCB_Y].pos[Holder_Pos])	- offsetY;
			pos[2]	= (motor.GetCommandPos(Motor_PCB_TH) - model.axis[Motor_PCB_TH].pos[Holder_Pos])	+ offsetTh;

			if(	motor.Pcb_Motor_Move(Bonding_Pos, pos[0], pos[1], pos[2]))
			{
				CString sTmpLog;
				sLangChange.LoadStringA(IDS_STRING1015);	//PCB부 %s 이동 완료
				sTmpLog.Format(sLangChange, MotorPosName[Bonding_Pos]);
				delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
			}

			CString sTemp;
			sLangChange.LoadStringA(IDS_STRING1482);	//보정값 : %.3lf %.3lf %.3lf
			sTemp.Format(sLangChange, pos[0], pos[1], offsetTh);
			m_labelAlignResult.SetText(sTemp);
			m_labelAlignResult.Invalidate();

		}
	}
	else
	{
		sLangChange.LoadStringA(IDS_STRING1215);	//마크 인식 실패.
		errMsg2(Task.AutoFlag, sLangChange);
	}

	pFrame->m_rBox.left = 0;
	pFrame->m_rBox.top = 0;
	pFrame->m_rBox.right = 0;
	pFrame->m_rBox.bottom = 0;

	g_bMovingflag =false;
}


void CPcbInspDlg::OnBnClickedButtonSocketTest()
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

	if(Task.m_bPBStart == 0)
	{
		sLangChange.LoadStringA(IDS_STRING1248);	//바코드 정보가 존재하지 않습니다.,
		errMsg2(Task.AutoFlag, sLangChange);
		return;
	}

	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	pFrame->func_Socket_Barcode();
	
}
