// LensDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "LensDlg.h"
#include "afxdialogex.h"

#include "MarkSetDlg.h"

#include "DelayMsgDlg.h"
#include "DisplacementDlg.h"


extern	CWinThread* pThread_TaskPcb;

// CLensDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CLensDlg, CDialogEx)

	CLensDlg::CLensDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLensDlg::IDD, pParent)
{
	m_iSelMoveType	= 0;
	m_iSelMotor		= 1;
}

CLensDlg::~CLensDlg()
{
}

void CLensDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_POS, m_iSelMoveType);
	DDX_Control(pDX, IDC_LABEL_DISP1, m_labelDisp1);
	DDX_Control(pDX, IDC_LABEL_DISP2, m_labelDisp2);
	DDX_Control(pDX, IDC_BUTTON_GRIP_ON, m_btnPcbTurn);
	DDX_Control(pDX, IDC_BUTTON_GRIP_OFF, m_btnPcbReTurn);
	DDX_Control(pDX, IDC_BUTTON_CONTACT_UP, m_btnContact_UP);
	DDX_Control(pDX, IDC_BUTTON_CONTACT_DOWN, m_btnContact_DOWN);


	//
	DDX_Control(pDX, IDC_BUTTON_MOTOR_ALIGN, m_btnAlignPos);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_ALIGN_Z, m_btnAlignPosZ);
	//
	DDX_Control(pDX, IDC_BUTTON_MOTOR_SUPPLY, m_btnSupplyPos);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_SUPPLY_Z, m_btnSupplyPosZ);
	//
	DDX_Control(pDX, IDC_BUTTON_MOTOR_BOND, m_btnBondPos);
	DDX_Control(pDX, IDC_BUTTON_Z_MOTOR_UP_BONDING, m_btnBondPosZ);


	//DDX_Control(pDX, IDC_BUTTON_Z_MOTOR_UP_BONDING, m_btnZBonding);
	//


	DDX_Control(pDX, IDC_BUTTON_MOTOR_COM_ALIGN, m_btnComAlignPos);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_COM_ALIGN_Z, m_btnComAlignPosZ);


	DDX_Control(pDX, IDC_BUTTON_MOTOR_DEFECT_INSP, m_btnDefectPos);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_DEFECT_INSP_Z, m_btnDefectPosZ);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_2800K_INSP, m_btn2800kPos);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_2800K_INSP_Z, m_btn2800kPosZ);


	//
	DDX_Control(pDX, IDC_BUTTON_MOTOR_SUPPLY2, m_btnSupplyPos2);

	DDX_Control(pDX, IDC_BUTTON_MOTOR_Z_WAIT, m_btnZWait);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_WAIT, m_btnWaitPos);


	DDX_Control(pDX, IDC_BUTTON_MOTOR_BOND2, m_btnBond2Pos);

	DDX_Control(pDX, IDC_BUTTON_PCB_SOCKET_DETECT, m_btnPcbCloseSonsor);
	DDX_Control(pDX, IDC_BUTTON_LENS_SENSOR, m_btnLensSonsor);
	DDX_Control(pDX, IDC_BUTTON_GOTO_PCBALIGN, m_btnPCB);
	DDX_Control(pDX, IDC_BUTTON_GOTO_LENSALIGN, m_btnLens);
	DDX_Control(pDX, IDC_BUTTON_GOTO_LENSEDGE_ALIGN, m_btnLensEdge);

	DDX_Control(pDX, IDC_LENS_ALIGN_RESULT, m_labelAlignResult);
	DDX_Control(pDX, IDC_BUTTON_BOX_LEFT, m_btn_BoxLeft);
	DDX_Control(pDX, IDC_BUTTON_BOX_UP, m_btn_BoxUP);
	DDX_Control(pDX, IDC_BUTTON_BOX_RIGHT, m_btn_BoxRight);
	DDX_Control(pDX, IDC_BUTTON_BOX_DOWN, m_btn_BoxDown);
	DDX_Control(pDX, IDC_BUTTON_EDGE_PCB_COVER_UP, m_btnLensCoverUP);
	DDX_Control(pDX, IDC_BUTTON_EDGE_PCB_COVER_DOWN, m_btnLensCoverDown);

	DDX_Control(pDX, IDC_BUTTON_PCBGRIP_FOR, m_btn_PcbGrip_For);
	DDX_Control(pDX, IDC_BUTTON_PCBGRIP_BACK, m_btn_PcbGrip_Back);
	DDX_Control(pDX, IDC_BUTTON_OC_FOR, m_btn_OC_For);
	DDX_Control(pDX, IDC_BUTTON_OC_BACK, m_btn_OC_Back);
	DDX_Control(pDX, IDC_BUTTON_PCB_DARK_UP, m_btnDarkUp);
	DDX_Control(pDX, IDC_BUTTON_PCB_DARK_DOWN, m_btnDarkDown);

	DDX_Control(pDX, IDC_BUTTON_COM_ALIGN, m_btnComAlign);

	//DDX_Control(pDX, IDC_BUTTON_BACKLIGHT_IN, m_btnBackLightOn);
	//DDX_Control(pDX, IDC_BUTTON_BACKLIGHT_OUT, m_btnBackLightOff);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_DARK_INSP, m_btnDarkPos);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_Z_DARK_INSP, m_btnDarkZPos);



	DDX_Control(pDX, IDC_BUTTON_EDGE_PCB_GRIP, m_btnPcbGrip);
	DDX_Control(pDX, IDC_BUTTON_EDGE_PCB_UNGRIP, m_btnPcbUnGrip);

	DDX_Control(pDX, IDC_BUTTON_UV_CYLINDER_UP, m_btnUVCylinder_Up);
	DDX_Control(pDX, IDC_BUTTON_UV_CYLINDER_DOWN, m_btnUVCylinder_Down);

	DDX_Control(pDX, IDC_BUTTON_MOTOR_PCB_LOADING, m_btnPcbLoadingPos);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_Z_PCB_LOADING, m_btnPcbLoadingZPos);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_COVER_LOADING, m_btnCoverLoadingPos);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_Z_COVER_LOADING, m_btnCoverLoadingZPos);
	//
	DDX_Control(pDX, IDC_BUTTON_MOTOR_COVER_UNLOADING, m_btnHolderUvPos);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_Z_COVER_UNLOADING, m_btnHolderUvZPos);



	DDX_Control(pDX, IDC_BUTTON_INSP_MOTOR_WAIT, m_btnInspXWaitPos);
	DDX_Control(pDX, IDC_BUTTON_INSP_MOTOR_ALIGN, m_btnInspXAlignPos);
	DDX_Control(pDX, IDC_BUTTON_INSP_MOTOR_DEFECT_INSP, m_btnInspXDefectPos);
	DDX_Control(pDX, IDC_BUTTON_INSP_MOTOR_DARK_INSP, m_btnInspXDarkPos);
}


BEGIN_MESSAGE_MAP(CLensDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLensDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CLensDlg::OnBnClickedCancel)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_BOX_SPEED, &CLensDlg::OnBnClickedButtonBoxSpeed)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_LIVEMODE, &CLensDlg::OnBnClickedButtonLivemode)
	ON_BN_CLICKED(IDC_BUTTON_REGIST, &CLensDlg::OnBnClickedButtonRegist)
	ON_BN_CLICKED(IDC_BUTTON_FIND, &CLensDlg::OnBnClickedButtonFind)
	ON_BN_CLICKED(IDC_RADIO_POS, &CLensDlg::OnBnClickedRadioPos)
	ON_BN_CLICKED(IDC_RADIO_SIZE, &CLensDlg::OnBnClickedRadioSize)
	ON_BN_CLICKED(IDC_BUTTON_BOX_UP, &CLensDlg::OnBnClickedButtonBoxUp)
	ON_BN_CLICKED(IDC_BUTTON_BOX_DOWN, &CLensDlg::OnBnClickedButtonBoxDown)
	ON_BN_CLICKED(IDC_BUTTON_BOX_LEFT, &CLensDlg::OnBnClickedButtonBoxLeft)
	ON_BN_CLICKED(IDC_BUTTON_BOX_RIGHT, &CLensDlg::OnBnClickedButtonBoxRight)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_SUPPLY, &CLensDlg::OnBnClickedButtonMotorSupply)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_ALIGN, &CLensDlg::OnBnClickedButtonMotorAlign)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_BOND, &CLensDlg::OnBnClickedButtonMotorBond)
	ON_BN_CLICKED(IDC_BUTTON_IMG_LOAD, &CLensDlg::OnBnClickedButtonImgLoad)
	ON_BN_CLICKED(IDC_BUTTON_IMG_SAVE, &CLensDlg::OnBnClickedButtonImgSave)
//	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON_MARKSET, &CLensDlg::OnBnClickedButtonMarkset)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_GRIP_ON, &CLensDlg::OnBnClickedButtonGripOn)
	ON_BN_CLICKED(IDC_BUTTON_GRIP_OFF, &CLensDlg::OnBnClickedButtonGripOff)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_WAIT, &CLensDlg::OnBnClickedButtonMotorWait)
	ON_BN_CLICKED(IDC_BUTTON_ALIGN_TEST, &CLensDlg::OnBnClickedButtonAlignTest)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_BOND2, &CLensDlg::OnBnClickedButtonMotorBond2)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_Menu_COPY, &CLensDlg::OnMenuCopy)
	ON_COMMAND(ID_Menu_DELETE, &CLensDlg::OnMenuDelete)
	ON_COMMAND(ID_Menu_PASTE, &CLensDlg::OnMenuPaste)
	ON_BN_CLICKED(IDC_BUTTON_GOTO_PCBALIGN, &CLensDlg::OnBnClickedButtonGotoPcbalign)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON_GOTO_LENSALIGN, &CLensDlg::OnBnClickedButtonGotoLensalign)
	ON_BN_CLICKED(IDC_BUTTON_GOTO_LENSEDGE_ALIGN, &CLensDlg::OnBnClickedButtonGotoLensedgeAlign)
	ON_BN_CLICKED(IDC_BUTTON_EDGE_PCB_COVER_UP, &CLensDlg::OnBnClickedButtonEdgePcbCoverUp)
	ON_BN_CLICKED(IDC_BUTTON_EDGE_PCB_COVER_DOWN, &CLensDlg::OnBnClickedButtonEdgePcbCoverDown)
	ON_BN_CLICKED(IDC_BUTTON_OC_FOR, &CLensDlg::OnBnClickedButtonPcbCoverFor)
	ON_BN_CLICKED(IDC_BUTTON_OC_BACK, &CLensDlg::OnBnClickedButtonPcbCoverBack)
	ON_BN_CLICKED(IDC_BUTTON_PCB_DARK_UP, &CLensDlg::OnBnClickedButtonPcbDarkUp)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_DARK_INSP, &CLensDlg::OnBnClickedButtonMotorDarkInsp)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_DEFECT_INSP, &CLensDlg::OnBnClickedButtonMotorDefectInsp)
	ON_BN_CLICKED(IDC_BUTTON_PCB_DARK_DOWN, &CLensDlg::OnBnClickedButtonPcbDarkDown)
	ON_BN_CLICKED(IDC_BUTTON_BACKLIGHT_IN, &CLensDlg::OnBnClickedButtonBacklightIn)
	ON_BN_CLICKED(IDC_BUTTON_BACKLIGHT_OUT, &CLensDlg::OnBnClickedButtonBacklightOut)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_SUPPLY2, &CLensDlg::OnBnClickedButtonMotorSupply2)
	ON_BN_CLICKED(IDC_BUTTON_EDGE_PCB_GRIP, &CLensDlg::OnBnClickedButtonEdgePcbGrip)
	ON_BN_CLICKED(IDC_BUTTON_EDGE_PCB_UNGRIP, &CLensDlg::OnBnClickedButtonEdgePcbUngrip)
	
	
	//ON_BN_CLICKED(IDC_BUTTON_BACKLIGHT_OUT_PRE, &CLensDlg::OnBnClickedButtonBacklightOutPre)
	//
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_Z_WAIT, &CLensDlg::OnBnClickedButtonMotorZWait)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_DEFECT_INSP_Z, &CLensDlg::OnBnClickedButtonMotorDefectInspZ)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_ALIGN_Z, &CLensDlg::OnBnClickedButtonMotorAlignZ)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_SUPPLY_Z, &CLensDlg::OnBnClickedButtonMotorSupplyZ)
	ON_BN_CLICKED(IDC_BUTTON_Z_MOTOR_UP_BONDING, &CLensDlg::OnBnClickedButtonZMotorUpBonding)
	ON_BN_CLICKED(IDC_BUTTON_BACKLIGHT_OUT_PRE, &CLensDlg::OnBnClickedButtonBacklightOutPre)
	ON_BN_CLICKED(IDC_BUTTON_COM_ALIGN, &CLensDlg::OnBnClickedButtonOpticalInsp)
	ON_BN_CLICKED(IDC_BUTTON_PCBGRIP_FOR, &CLensDlg::OnBnClickedButtonPcbGripFor)
	ON_BN_CLICKED(IDC_BUTTON_PCBGRIP_BACK, &CLensDlg::OnBnClickedButtonPcbGripBack)
	ON_BN_CLICKED(IDC_BUTTON_COM_ALIGN_TEST, &CLensDlg::OnBnClickedButtonComAlignTest)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_COM_ALIGN, &CLensDlg::OnBnClickedButtonMotorComAlign)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_COM_ALIGN_Z, &CLensDlg::OnBnClickedButtonMotorComAlignZ)

    ON_BN_CLICKED(IDC_BUTTON_MOTOR_2800K_INSP, &CLensDlg::OnBnClickedButtonMotor2800kInsp)
    ON_BN_CLICKED(IDC_BUTTON_MOTOR_2800K_INSP_Z, &CLensDlg::OnBnClickedButtonMotor2800kInspZ)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_Z_DARK_INSP, &CLensDlg::OnBnClickedButtonMotorZDarkInsp)
	ON_BN_CLICKED(IDC_BUTTON_CONTACT_UP, &CLensDlg::OnBnClickedButtonContactUp)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_PCB_LOADING, &CLensDlg::OnBnClickedButtonMotorPcbLoading)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_COVER_LOADING, &CLensDlg::OnBnClickedButtonMotorCoverLoading)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_Z_PCB_LOADING, &CLensDlg::OnBnClickedButtonMotorZPcbLoading)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_Z_COVER_LOADING, &CLensDlg::OnBnClickedButtonMotorZCoverLoading)
	ON_BN_CLICKED(IDC_BUTTON_CONTACT_DOWN, &CLensDlg::OnBnClickedButtonContactDown)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_COVER_UNLOADING, &CLensDlg::OnBnClickedButtonMotorCoverUnloading)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_Z_COVER_UNLOADING, &CLensDlg::OnBnClickedButtonMotorZCoverUnloading)
	ON_BN_CLICKED(IDC_BUTTON_UV_CYLINDER_UP, &CLensDlg::OnBnClickedButtonUvCylinderUp)
	ON_BN_CLICKED(IDC_BUTTON_UV_CYLINDER_DOWN, &CLensDlg::OnBnClickedButtonUvCylinderDown)
	ON_BN_CLICKED(IDC_BUTTON_INSP_MOTOR_WAIT, &CLensDlg::OnBnClickedButtonInspMotorWait)
	ON_BN_CLICKED(IDC_BUTTON_INSP_MOTOR_ALIGN, &CLensDlg::OnBnClickedButtonInspMotorAlign)
	ON_BN_CLICKED(IDC_BUTTON_INSP_MOTOR_DEFECT_INSP, &CLensDlg::OnBnClickedButtonInspMotorDefectInsp)
	ON_BN_CLICKED(IDC_BUTTON_INSP_MOTOR_DARK_INSP, &CLensDlg::OnBnClickedButtonInspMotorDarkInsp)
END_MESSAGE_MAP()


// CLensDlg 메시지 처리기입니다.

BOOL CLensDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	setInterface();
	//DigLedputData();

	//m_btn_BoxUP.SubclassDlgItem(IDC_BUTTON_BOX_UP, this);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CLensDlg::OnBnClickedOk(){}
void CLensDlg::OnBnClickedCancel(){}

void CLensDlg::setInterface()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	WINDOWPLACEMENT wndpl;

	/*wndpl.rcNormalPosition.left = pFrame->m_rectCamDispPos2.right+1;
	wndpl.rcNormalPosition.right = MAIN_DLG_SIZE_X;
	wndpl.rcNormalPosition.top = pFrame->m_rectCamDispPos1.top - SUB_DLG_OFFSET_Y+10;
	wndpl.rcNormalPosition.bottom = MAIN_DLG_SIZE_Y - 85;*/
	wndpl.rcNormalPosition = pFrame->m_rectCamDispPos2;
	wndpl.rcNormalPosition.right = pFrame->m_rectCamDispPos2.right + 100;
	wndpl.rcNormalPosition.left = pFrame->m_rectCamDispPos2.left - 10;
	wndpl.rcNormalPosition.top -= SUB_DLG_OFFSET_Y - 10;
	wndpl.rcNormalPosition.bottom = MAIN_DLG_SIZE_Y - 5 - 90;
	this->MoveWindow(&wndpl.rcNormalPosition);

	GetDlgItem(IDC_MARK_DISP1)->GetWindowPlacement(&wndpl);
	m_iMarkDispSizeX = wndpl.rcNormalPosition.right - wndpl.rcNormalPosition.left;
	m_iMarkDispSizeY = wndpl.rcNormalPosition.bottom - wndpl.rcNormalPosition.top;

#ifdef ON_LINE_VISION
	CWnd* pWnd;
	for (int i=0 ; i<2 ; i++)
	{
		pWnd = (CWnd*)GetDlgItem(IDC_MARK_DISP1+i);
		MdispSelectWindow(vision.MilMarkDisplay[PCB_Chip_MARK][i], vision.MilMarkSmallImage[PCB_Chip_MARK][i], pWnd->m_hWnd);
	}
#endif

	m_labelAlignResult.SetBkColor(M_COLOR_WHITE);


	m_iMoveSpeed = 10;
	m_rMarkBox.left		= 10;
	m_rMarkBox.top		= 10;
	m_rMarkBox.right	= CAM_SIZE_X - 10;
	m_rMarkBox.bottom	= CAM_SIZE_Y - 10;
	
	clickedMarkDisp(0);

	m_btnLens.m_iStateBtn = 1;
	m_btnLens.Invalidate();

	//GetDlgItem(IDC_BUTTON_PCBGRIP_FOR)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_BUTTON_PCBGRIP_BACK)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BUTTON_MOTOR_PCB_LOADING)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_MOTOR_Z_PCB_LOADING)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_MOTOR_COVER_LOADING)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_MOTOR_Z_COVER_LOADING)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_MOTOR_COVER_UNLOADING)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_MOTOR_Z_COVER_UNLOADING)->ShowWindow(SW_HIDE);
}


void CLensDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow)
	{
		if(Task.AutoFlag == 0){
			if(sysData.m_iProductComp == 1)
			{
				LightControlthird.ctrlLedVolume(LIGHT_PCB, model.m_iLedValue[LEDDATA_HOLDER]);
			}else
			{
				LightControlthird.ctrlLedVolume(LIGHT_PCB, model.m_iLedValue[LEDDATA_SENSOR]);
			}
			
		}
		initMarkGrid();

		ctrlLiveButton();
#ifdef ON_LINE_VISION
		dispMarkImage();
#endif
		dispData();
		#ifdef ON_LINE_VISION
		vision.clearOverlay(CAM1);
		vision.drawOverlay(CAM1);
		#endif

		gripErrCnt = centeringErrCnt = vaccumErrCnt = 0;

		timerRunFlag = false;
		m_bCopyFlag = false;
		m_iCopyMarkNo = -1;
		
		pushErrCnt = 0;

		SetTimer(LENS_TIMER, 100, NULL);
	}
	else
	{
		KillTimer(LENS_TIMER);
		#ifdef ON_LINE_VISION
		vision.clearOverlay(CAM1);
		vision.drawOverlay(CAM1);
		#endif


		CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

		pFrame->m_bMeasureDist = FALSE;
		pFrame->UpdateData(false);

		pFrame->m_rBox.left = 0;
		pFrame->m_rBox.top = 0;
		pFrame->m_rBox.right = 0;
		pFrame->m_rBox.bottom = 0;
	}
}


void CLensDlg::dispData()
{
	//CString tmpStr;

	/*tmpStr.Format("%d", model.m_iLimitRate[PCB_Chip_MARK][0]);
	m_gridMark.SetTextMatrix(1, 1, tmpStr);

	tmpStr.Format("%d", model.m_iLimitRate[PCB_Chip_MARK][1]);
	m_gridMark.SetTextMatrix(1, 2, tmpStr);*/
}

void CLensDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent==LENS_TIMER)
	{
		if (!timerRunFlag)
		{
			timerRunFlag = true;
			changeColorLensLiftBtn();
			changeColorPcbCoverSensorBtn();
			changeColorMotorPosBtn();
			changeColorBackLightBtn();
			changeColorGripBtn();
			changeColorLensSensorBtn();
			changeColorLensSensorLift();
			changeColorOcLightBtn();
			changeColorPcbTurnBtn();
			changeColorContactUpBtn();
			changeColorUvCylinderBtn();
			//changeColorOcBtn();		//PCB Cover 전/후진 On 상태 Check
			changeColorDarkBtn();		//Dark 검사 실린더 Up/Down 상태 Check
			changeColorPcbGripBtn();
			timerRunFlag = false;
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}



void CLensDlg::ctrlLiveButton()
{
	if (vision.getLiveMode())
	{	
		sLangChange.LoadStringA(IDS_STRING1464);	//동영상
		GetDlgItem(IDC_BUTTON_LIVEMODE)->SetWindowText(sLangChange);
	}
	else
	{
		sLangChange.LoadStringA(IDS_STRING1465);	//정지영상
		GetDlgItem(IDC_BUTTON_LIVEMODE)->SetWindowText(sLangChange);
	}
}

void CLensDlg::OnBnClickedButtonLivemode()
{
	////DIO_OUT_START_PB
	//Dio.HolderGrip(true, false);
	return;
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


void CLensDlg::getMarkSize()
{
	m_iMarkSizeX = m_rMarkBox.right - m_rMarkBox.left;
	m_iMarkSizeY = m_rMarkBox.bottom - m_rMarkBox.top;
}

void CLensDlg::OnBnClickedButtonRegist()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}
	
	if (vision.getLiveMode()){
		vision.getSnapImage(CAM1);
	}
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	getMarkSize();

	bool bRtn = vision.markRegist(CAM1, PCB_Chip_MARK, m_iMarkNo, m_rMarkBox);
	 
	if (!bRtn)
	{
		sLangChange.LoadStringA(IDS_STRING1466);	//마크등록 실패.
		::errMsg2(Task.AutoFlag, sLangChange);
		return;
	}

	CMarkSetDlg dlg(CAM1, PCB_Chip_MARK, m_iMarkNo, m_iMarkSizeX, m_iMarkSizeY, true);

	double dZoomX = (double)MARK_SIZE_X/(double)m_iMarkSizeX;
	double dZoomY = (double)MARK_SIZE_Y/(double)m_iMarkSizeY;

	if (dlg.DoModal()==IDOK)
	{

#ifdef USE_GEOMETRIC
		MmodDraw(M_DEFAULT, vision.ModModel[PCB_Chip_MARK][m_iMarkNo], vision.MilMarkImage[PCB_Chip_MARK][m_iMarkNo], M_DRAW_IMAGE, M_DEFAULT, M_DEFAULT);

		MmodInquire(vision.ModModel[PCB_Chip_MARK][m_iMarkNo], M_DEFAULT, M_REFERENCE_X+M_TYPE_DOUBLE, &model.m_MarkCenter[PCB_Chip_MARK][m_iMarkNo].x);
		MmodInquire(vision.ModModel[PCB_Chip_MARK][m_iMarkNo], M_DEFAULT, M_REFERENCE_Y+M_TYPE_DOUBLE, &model.m_MarkCenter[PCB_Chip_MARK][m_iMarkNo].y);
		MmodInquire(vision.ModModel[PCB_Chip_MARK][m_iMarkNo], M_DEFAULT, M_REFERENCE_X+M_TYPE_DOUBLE, &model.m_MarkOrigin[PCB_Chip_MARK][m_iMarkNo].x);
		MmodInquire(vision.ModModel[PCB_Chip_MARK][m_iMarkNo], M_DEFAULT, M_REFERENCE_Y+M_TYPE_DOUBLE, &model.m_MarkOrigin[PCB_Chip_MARK][m_iMarkNo].y);
#else
		MpatDraw(M_DEFAULT, vision.PatModel[PCB_Chip_MARK][m_iMarkNo], vision.MilMarkImage[PCB_Chip_MARK][m_iMarkNo], M_DRAW_IMAGE, M_DEFAULT, M_DEFAULT);

		MpatInquire(vision.PatModel[PCB_Chip_MARK][m_iMarkNo], M_CENTER_X, &model.m_MarkCenter[PCB_Chip_MARK][m_iMarkNo].x);
		MpatInquire(vision.PatModel[PCB_Chip_MARK][m_iMarkNo], M_CENTER_Y, &model.m_MarkCenter[PCB_Chip_MARK][m_iMarkNo].y);
		MpatInquire(vision.PatModel[PCB_Chip_MARK][m_iMarkNo], M_ORIGINAL_X, &model.m_MarkOrigin[PCB_Chip_MARK][m_iMarkNo].x);
		MpatInquire(vision.PatModel[PCB_Chip_MARK][m_iMarkNo], M_ORIGINAL_Y, &model.m_MarkOrigin[PCB_Chip_MARK][m_iMarkNo].y);
#endif

		MimResize(vision.MilMarkImage[PCB_Chip_MARK][m_iMarkNo], vision.MilMarkSmallImage[PCB_Chip_MARK][m_iMarkNo], dZoomX, dZoomY, M_DEFAULT);

		model.m_MarkSize[PCB_Chip_MARK][m_iMarkNo].x = m_iMarkSizeX;
		model.m_MarkSize[PCB_Chip_MARK][m_iMarkNo].y = m_iMarkSizeY;

		vision.geometricMarkPreProc(CAM1, PCB_Chip_MARK, m_iMarkNo);

		model.Save();
	}
}


void CLensDlg::OnBnClickedButtonFind()
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
		vision.setLiveMode(true);
	}

	double ep1;
	MappTimer(M_TIMER_RESET, &ep1);

//이해철 TEST
//#ifdef ON_LINE_VISION
	//model.loadMark(CAM1, PCB_Chip_MARK, 0);
	//vision.geometricMarkPreProc(CAM1, PCB_Chip_MARK, 0);
//#endif
	iMarkNo = vision.findMark(CAM1, PCB_Chip_MARK);


	double ep2;
	MappTimer(M_TIMER_READ, &ep2);

	sTemp.Format(" %.3lf msec", ep2 - ep1);
	vision.textlist[CAM1].addList((CAM_SIZE_X-140), (CAM_SIZE_Y-60), sTemp, M_COLOR_WHITE, 24, 10, "Arial");

	vision.drawOverlay(CAM1);

	if (iMarkNo!=-1)
	{
		MmodControl(vision.ModResult[PCB_Chip_MARK][iMarkNo], M_DEFAULT, M_DRAW_SCALE_X, CAM_REDUCE_FACTOR_X);
		MmodControl(vision.ModResult[PCB_Chip_MARK][iMarkNo], M_DEFAULT, M_DRAW_SCALE_Y, CAM_REDUCE_FACTOR_Y);

		MgraColor(M_DEFAULT, M_COLOR_GREEN);
		MmodDraw(M_DEFAULT, vision.ModResult[PCB_Chip_MARK][iMarkNo], vision.MilOverlayImage[CAM1], M_DRAW_BOX+M_DRAW_POSITION+M_DRAW_EDGES+M_DRAW_AXIS, M_DEFAULT, M_DEFAULT);
	}

	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	pFrame->m_rBox.left = 0;
	pFrame->m_rBox.top = 0;
	pFrame->m_rBox.right = 0;
	pFrame->m_rBox.bottom = 0;
}


void CLensDlg::OnBnClickedRadioPos()
{
	UpdateData(true);
}


void CLensDlg::OnBnClickedRadioSize()
{
	UpdateData(true);
}


void CLensDlg::OnBnClickedButtonBoxUp()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	/* 이동 */
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


void CLensDlg::OnBnClickedButtonBoxDown()
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


void CLensDlg::OnBnClickedButtonBoxLeft()
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


void CLensDlg::OnBnClickedButtonBoxRight()
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


void CLensDlg::OnBnClickedButtonBoxSpeed()
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


void CLensDlg::OnBnClickedButtonImgLoad()
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


void CLensDlg::OnBnClickedButtonImgSave()
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




void CLensDlg::dispMarkImage()
{
	double dZoomX, dZoomY;
#ifdef ON_LINE_VISION
	for (int i=0 ; i<2 ; i++)
	{
		MbufClear(vision.MilMarkImage[PCB_Chip_MARK][i], 0);
		MbufClear(vision.MilMarkSmallImage[PCB_Chip_MARK][i], 0);

		if (model.m_MarkSize[PCB_Chip_MARK][i].x<=0 || model.m_MarkSize[PCB_Chip_MARK][i].y<=0)
			continue;

		dZoomX = (double)MARK_SIZE_X/(double)model.m_MarkSize[PCB_Chip_MARK][i].x;
		dZoomY = (double)MARK_SIZE_Y/(double)model.m_MarkSize[PCB_Chip_MARK][i].y;

#ifdef USE_GEOMETRIC
		if (vision.ModModel[PCB_Chip_MARK][i]==M_NULL)	continue;

		MmodDraw(M_DEFAULT, vision.ModModel[PCB_Chip_MARK][i], vision.MilMarkImage[PCB_Chip_MARK][i], M_DRAW_IMAGE, M_DEFAULT, M_DEFAULT);
#else
		if (vision.PatModel[PCB_Chip_MARK][i]==M_NULL)	continue;

		MpatDraw(M_DEFAULT, vision.PatModel[PCB_Chip_MARK][i], vision.MilMarkImage[PCB_Chip_MARK][i], M_DRAW_IMAGE, M_DEFAULT, M_DEFAULT);
#endif

		MimResize(vision.MilMarkImage[PCB_Chip_MARK][i], vision.MilMarkSmallImage[PCB_Chip_MARK][i], dZoomX, dZoomY, M_DEFAULT);
	}
#endif
}

void CLensDlg::OnBnClickedButtonMarkset()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}


	int iMarkSizeX = model.m_MarkSize[PCB_Chip_MARK][m_iMarkNo].x;
	int iMarkSizeY = model.m_MarkSize[PCB_Chip_MARK][m_iMarkNo].y;

	MbufClear(vision.MilTempImage, 0);

#ifdef USE_GEOMETRIC
	MmodDraw(M_DEFAULT, vision.ModModel[PCB_Chip_MARK][m_iMarkNo], vision.MilTempImage, M_DRAW_IMAGE, M_DEFAULT, M_DEFAULT);
#else
	MpatDraw(M_DEFAULT, vision.PatModel[PCB_Chip_MARK][m_iMarkNo], vision.MilTempImage, M_DRAW_IMAGE, M_DEFAULT, M_DEFAULT);
#endif
	CMarkSetDlg dlg(CAM1, PCB_Chip_MARK, m_iMarkNo, iMarkSizeX, iMarkSizeY, false);

	double dZoomX = (double)MARK_SIZE_X/(double)iMarkSizeX;
	double dZoomY = (double)MARK_SIZE_Y/(double)iMarkSizeY;

	if (dlg.DoModal()==IDOK)
	{
#ifdef USE_GEOMETRIC
		MmodInquire(vision.ModModel[PCB_Chip_MARK][m_iMarkNo], M_DEFAULT, M_REFERENCE_X+M_TYPE_DOUBLE, &model.m_MarkCenter[PCB_Chip_MARK][m_iMarkNo].x);
		MmodInquire(vision.ModModel[PCB_Chip_MARK][m_iMarkNo], M_DEFAULT, M_REFERENCE_Y+M_TYPE_DOUBLE, &model.m_MarkCenter[PCB_Chip_MARK][m_iMarkNo].y);
		MmodInquire(vision.ModModel[PCB_Chip_MARK][m_iMarkNo], M_DEFAULT, M_REFERENCE_X+M_TYPE_DOUBLE, &model.m_MarkOrigin[PCB_Chip_MARK][m_iMarkNo].x);
		MmodInquire(vision.ModModel[PCB_Chip_MARK][m_iMarkNo], M_DEFAULT, M_REFERENCE_Y+M_TYPE_DOUBLE, &model.m_MarkOrigin[PCB_Chip_MARK][m_iMarkNo].y);
#else
		MpatInquire(vision.PatModel[PCB_Chip_MARK][m_iMarkNo], M_CENTER_X, &model.m_MarkCenter[PCB_Chip_MARK][m_iMarkNo].x);
		MpatInquire(vision.PatModel[PCB_Chip_MARK][m_iMarkNo], M_CENTER_Y, &model.m_MarkCenter[PCB_Chip_MARK][m_iMarkNo].y);
		MpatInquire(vision.PatModel[PCB_Chip_MARK][m_iMarkNo], M_ORIGINAL_X, &model.m_MarkOrigin[PCB_Chip_MARK][m_iMarkNo].x);
		MpatInquire(vision.PatModel[PCB_Chip_MARK][m_iMarkNo], M_ORIGINAL_Y, &model.m_MarkOrigin[PCB_Chip_MARK][m_iMarkNo].y);
#endif
		model.m_MarkSize[PCB_Chip_MARK][m_iMarkNo].x = iMarkSizeX;
		model.m_MarkSize[PCB_Chip_MARK][m_iMarkNo].y = iMarkSizeY;

		model.Save();
	}
}


void CLensDlg::clickedMarkDisp(int iMarkNo)
{
	if (iMarkNo==0)
	{
		m_labelDisp1.SetBkColor(M_COLOR_LIGHT_BLUE);
		m_labelDisp2.SetBkColor(M_COLOR_LIGHT_GRAY);

		m_iMarkNo = 0;
	}
	else
	{
		m_labelDisp1.SetBkColor(M_COLOR_LIGHT_GRAY);
		m_labelDisp2.SetBkColor(M_COLOR_LIGHT_BLUE);

		m_iMarkNo = 1;
	}

	m_labelDisp1.Invalidate();
	GetDlgItem(IDC_MARK_DISP1)->Invalidate();
	m_labelDisp2.Invalidate();
	GetDlgItem(IDC_MARK_DISP2)->Invalidate();
}

void CLensDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	WINDOWPLACEMENT wndpl1, wndpl2;
	CRect rTemp1, rTemp2;

	m_labelDisp1.GetWindowPlacement(&wndpl1);
	m_labelDisp2.GetWindowPlacement(&wndpl2);

	rTemp1 = wndpl1.rcNormalPosition;
	rTemp2 = wndpl2.rcNormalPosition;

	if (PtInRect(rTemp1, point))
		clickedMarkDisp(0);
	if (PtInRect(rTemp2, point))
		clickedMarkDisp(1);

	CDialogEx::OnLButtonDown(nFlags, point);
}


BEGIN_EVENTSINK_MAP(CLensDlg, CDialogEx)
	ON_EVENT(CLensDlg, IDC_MSFLEXGRID_LENS_MARK, DISPID_DBLCLICK, CLensDlg::DblClickMsflexgridMark, VTS_NONE)
END_EVENTSINK_MAP()


void CLensDlg::DblClickMsflexgridMark()
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


void CLensDlg::OnBnClickedButtonMotorWait()
{
	if( !func_TaskMovingCheck() )	return;
	//if (Dio.UVCylinderCheck(false, false))
	//{
	//	askMsg("[주의!] UV실린더 상승 후 X,Y대기위치 이동 하십시오!");//UV실린더가 하강상태면 X,Y이동 차단. ->UV실린더가 하강하고 있는때는 UV조사하는 순간밖에없다. 
	//	return;
	//}
	/*if( !func_MovingInterlock())
	{
		return;
	}*/
	g_bMovingflag =true; 
	if(!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		sLangChange.Format("PCB Z axis Wait_Pos Move Failed");
		delayMsg(sLangChange, 1000, M_COLOR_RED);
	}
	if( motor.Pcb_Motor_Move(Wait_Pos) )
	{
		CString sTmpLog;
		sLangChange.LoadStringA(IDS_STRING1015);	//PCB부 %s 이동 완료
		sTmpLog.Format(sLangChange, MotorPosName[Wait_Pos]);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
	}

	if( motor.Pcb_Tilt_Motor_Move(Wait_Pos) )
	{
		CString sTmpLog;
		sLangChange.LoadStringA(IDS_STRING1015);	//PCB부 %s 이동 완료
		sTmpLog.Format(sLangChange, MotorPosName[Wait_Pos]);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
	}
	g_bMovingflag =false;
}

void CLensDlg::OnBnClickedButtonMotorSupply()
{
	CString sTmpLog;

	if( !func_TaskMovingCheck() )	return;

	if( !func_MovingInterlock())
	{
		return;
	}
	g_bMovingflag =true;
	if(!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		sLangChange.Format("PCB Z axis Wait_Pos Move Failed");
		delayMsg(sLangChange, 1000, M_COLOR_RED);
	}
	//if( !motor.Pcb_Tilt_Motor_Move(Loading_Pos))
	//{
	//	sLangChange.LoadStringA(IDS_STRING1017);	//PCB부 Tx, Ty축 대기 위치 이동 실패
	//	sTmpLog.Format(sLangChange);
	//	delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_RED);
	//	g_bMovingflag =false;
	//	return;
	//}
	 
	if(	!motor.Pcb_Motor_Move(Loading_Pos))
	{
		sLangChange.LoadStringA(IDS_STRING1481);	//PCB부 %s 이동 실패
		sTmpLog.Format(sLangChange, MotorPosName[Loading_Pos]);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_RED);
		g_bMovingflag =false;
		return;
	}
	if (!motor.Pcb_Tilt_Motor_Move(Loading_Pos))
	{
		g_bMovingflag = false;
		return;
	}
	g_bMovingflag =false;
}

void CLensDlg::OnBnClickedButtonMotorAlign()
{
	if( !func_TaskMovingCheck() )	return;
	if( !func_MovingInterlock())
	{
		return;
	}
	g_bMovingflag =true;
	if(!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		sLangChange.Format("PCB Z axis Wait_Pos Move Failed");
		delayMsg(sLangChange, 1000, M_COLOR_RED);
	}
	if(	motor.Pcb_Motor_Move(Align_Pos))
	{
		sLangChange.LoadStringA(IDS_STRING1015);	//PCB부 %s 이동 완료
		sTempLang.Format(sLangChange, MotorPosName[Align_Pos]);
		delayMsg(sTempLang.GetBuffer(99), 3000, M_COLOR_GREEN);
	}

	

	g_bMovingflag =false;
}

void CLensDlg::OnBnClickedButtonMotorBond()
{
	CString sTmpLog;

	if( !func_TaskMovingCheck() )	return;
	if( !func_MovingInterlock())
	{
		return;
	}
	g_bMovingflag =true;
	if(!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		sLangChange.Format("PCB Z axis Wait_Pos Move Failed");
		delayMsg(sLangChange, 1000, M_COLOR_RED);
	}
	/*if( !motor.Pcb_Tilt_Motor_Move(Bonding_Pos))
	{
		g_bMovingflag =false;
		return;
	}*/
	//
//#if 0
//	double LensPosX = (float)model.axis[Motor_Lens_X].pos[Bonding_Pos] - (float)motor.GetEncoderPos(Motor_Lens_X);
//	double LensPosY = (float)model.axis[Motor_Lens_Y].pos[Bonding_Pos] - (float)motor.GetEncoderPos(Motor_Lens_Y);
//	double LensPosZ = (float)model.axis[Motor_Lens_Z].pos[Wait_Pos] - (float)motor.GetEncoderPos(Motor_Lens_Z);
//	if (fabs(LensPosX) < 2.1 && fabs(LensPosY) < 2.1&& fabs(LensPosZ) < 2.1)
//	{
//		sTmpLog.Format("Lens x,y 본딩위치에서 Lens z축 대기위치입니다.\n z축 회피후 이동바랍니다.");
//		delayMsg(sTmpLog.GetBuffer(99), 5000, M_COLOR_GREEN);
//		g_bMovingflag = false;
//		return;
//	}
//#endif 
	if(	motor.Pcb_Motor_Move(Bonding_Pos))
	{
		
		sLangChange.LoadStringA(IDS_STRING1015);	//PCB부 %s 이동 완료
		sTmpLog.Format(sLangChange, MotorPosName[Bonding_Pos]);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
	}

	g_bMovingflag =false;
}

void CLensDlg::OnBnClickedButtonMotorBond2()
{
	if( !func_TaskMovingCheck() )	return;

	g_bMovingflag =true;

	if( !func_MovingInterlock() )	return;

	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	double offsetX, offsetY, offsetTh;
	int iRtnVal;

	int  iRtn = pFrame->procCamAlign(CAM1, PCB_Chip_MARK, false, offsetX, offsetY, offsetTh);


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
			pos[0]	= (motor.GetCommandPos(Motor_PCB_X) - model.axis[Motor_PCB_X].pos[Align_Pos])	- offsetX;
			pos[1]	= (motor.GetCommandPos(Motor_PCB_Y) - model.axis[Motor_PCB_Y].pos[Align_Pos])	- offsetY;
			pos[2]	= (motor.GetCommandPos(Motor_PCB_TH) - model.axis[Motor_PCB_TH].pos[Align_Pos])	+ offsetTh;

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


void CLensDlg::OnBnClickedButtonGripOn()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}
	if(g_bMovingflag)
	{
		sLangChange.LoadStringA(IDS_STRING1228);	//모터 구동 중 사용 불가..
		delayMsg(sLangChange, 2000, M_COLOR_RED);
		return;
	}
	g_bMovingflag = true;

	Dio.PcbTurn(true, false);

	g_bMovingflag = false;
}

void CLensDlg::OnBnClickedButtonGripOff()
{
	//if( !func_TaskMovingCheck() )	return;
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}
	if(g_bMovingflag)
	{
		sLangChange.LoadStringA(IDS_STRING1228);	//모터 구동 중 사용 불가..
		delayMsg(sLangChange, 2000, M_COLOR_RED);
		return;
	}

	g_bMovingflag =true;

	Dio.PcbTurn(false, false);

	g_bMovingflag =false;
}

void CLensDlg::OnBnClickedButtonAlignTest()
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
	int  iRtn = pFrame->procCamAlign(CAM1, PCB_Chip_MARK, true, offsetX, offsetY, offsetTh);
	if(!_finite(offsetX)){offsetX=0;}
	if(!_finite(offsetY)){offsetY=0;}
	if(!_finite(offsetTh)){offsetTh=0;} 

	if (iRtn == 0)
	{
		iRtnVal = pFrame->AlignLimitCheck(CAM1, offsetX, offsetY, offsetTh);


		if(iRtnVal==0)
		{
			sLangChange.LoadStringA(IDS_STRING1263);	//보정값 이동 범위가 Limit 초과 했습니다.
			errMsg2(Task.AutoFlag, sLangChange);
		}
		else
		{
			short axis[3];
			double pos[3];

			axis[0] = Motor_PCB_X;
			axis[1] = Motor_PCB_Y;
			axis[2] = Motor_PCB_TH;
		
			pos[0]	= motor.GetCommandPos(Motor_PCB_X)		- offsetX;
			pos[1]	= motor.GetCommandPos(Motor_PCB_Y)		- offsetY;
			pos[2] = motor.GetCommandPos(Motor_PCB_TH) - offsetTh;
			

			Task.d_Align_offset_x[PCB_Chip_MARK] = -offsetX;
			Task.d_Align_offset_y[PCB_Chip_MARK] = -offsetY;
			Task.d_Align_offset_th[PCB_Chip_MARK] = offsetTh;

			motor.goMotorPos(3, axis, pos);
			sLangChange.LoadStringA(IDS_STRING1261);	//보정 이동 완료.
			delayMsg(sLangChange, 3000, M_COLOR_GREEN);
			Sleep(10);

			pos[0]	= (pos[0] - model.axis[Motor_PCB_X].pos[Align_Pos]);
			pos[1]	= (pos[1] - model.axis[Motor_PCB_Y].pos[Align_Pos]);
			pos[2]	= (pos[2] - model.axis[Motor_PCB_TH].pos[Align_Pos]);

			CString sTemp;
			sLangChange.LoadStringA(IDS_STRING1482);	//보정값 : %.3lf %.3lf %.3lf
			sTemp.Format(sLangChange, pos[0], pos[1], pos[2]);
			m_labelAlignResult.SetText(sTemp);
			m_labelAlignResult.Invalidate();

			double etime = myTimer(true);
			while(1)
			{
				if(motor.IsStopAxis(Motor_PCB_X)  && motor.IsStopAxis(Motor_PCB_Y) && 
					motor.IsStopAxis(Motor_PCB_TH) )		
				{
					Sleep(20);
					break;
				}
				if((myTimer(true) - etime) > 3000)
				{
					sLangChange.LoadStringA(IDS_STRING1260);	//보정 위치 이동 실패
					delayMsg(sLangChange, 3000, M_COLOR_RED);
					break;
				}
			}
		}
	}
	else
	{
		sLangChange.LoadStringA(IDS_STRING1215);	//마크 인식 실패.
		errMsg2(Task.AutoFlag, sLangChange);
	}

		//vision.textlist[CAM1].addList((CAM_SIZE_X-140), (CAM_SIZE_Y-60), sTemp, M_COLOR_WHITE, 24, 10, "Arial");
		//vision.drawOverlay(CAM1);

	CString sLog;
	//sLangChange.LoadStringA(IDS_STRING658);	//Lens Align 보정값 X:%.03f, Y:%.03f, Θ:%.04f
	sLangChange.LoadStringA(IDS_STRING1482);
	sLog.Format("Sensor Align " + sLangChange, offsetX, offsetY, offsetTh);
	pFrame->putListLog(sLog);
	sLog.Empty();
}




void CLensDlg::OnContextMenu(CWnd* pWnd, CPoint point)
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


void CLensDlg::OnMenuCopy()
{
	m_bCopyFlag = true;

	m_iCopyMarkNo = m_iMarkNo;
}


void CLensDlg::OnMenuDelete()
{
	model.m_MarkCenter[PCB_Chip_MARK][m_iMarkNo].x	=	0.0f;
	model.m_MarkCenter[PCB_Chip_MARK][m_iMarkNo].y	=	0.0f;
	model.m_MarkSize[PCB_Chip_MARK][m_iMarkNo].x		=	0;
	model.m_MarkSize[PCB_Chip_MARK][m_iMarkNo].y		=	0;
	model.m_iLimitRate[PCB_Chip_MARK][m_iMarkNo]		=	70;

	CString sDelFile;

#ifdef USE_GEOMETRIC
	MmodFree(vision.ModModel[PCB_Chip_MARK][m_iMarkNo]);
	vision.ModModel[PCB_Chip_MARK][m_iMarkNo] = M_NULL;

	sDelFile.Format("%s\\%s\\Data\\Mark\\LENS_Mark_%d.mod", AA_MODEL_LOAD_DIR, model.mCurModelName, m_iMarkNo);
#else
	MpatFree(vision.PatModel[PCB_Chip_MARK][m_iMarkNo]);
	vision.PatModel[PCB_Chip_MARK][m_iMarkNo] = M_NULL;

	sDelFile.Format("%s\\Model\\%s\\LENS_Mark_%d.pat", DATA_DIR, model.name, m_iMarkNo);
#endif

	::DeleteFile(sDelFile);

	model.Save();
	//	model.Load();

	dispMarkImage();
}


void CLensDlg::OnMenuPaste()
{
	m_bCopyFlag =false;

#ifdef USE_GEOMETRIC
	if (vision.ModModel[PCB_Chip_MARK][m_iCopyMarkNo]==NULL)
		return;
#else
	if (vision.PatModel[PCB_Chip_MARK][m_iCopyMarkNo]==NULL)
		return;
#endif

	model.m_MarkCenter[PCB_Chip_MARK][m_iMarkNo].x	=	model.m_MarkCenter[PCB_Chip_MARK][m_iCopyMarkNo].x;
	model.m_MarkCenter[PCB_Chip_MARK][m_iMarkNo].y	=	model.m_MarkCenter[PCB_Chip_MARK][m_iCopyMarkNo].y;
	model.m_MarkSize[PCB_Chip_MARK][m_iMarkNo]		=	model.m_MarkSize[PCB_Chip_MARK][m_iCopyMarkNo];
	model.m_iLimitRate[PCB_Chip_MARK][m_iMarkNo]		=	model.m_iLimitRate[PCB_Chip_MARK][m_iCopyMarkNo];

	CString sScr, sDes;
#ifdef USE_GEOMETRIC
	sScr.Format("%s\\%s\\Data\\Mark\\LENS_Mark_%d.mod", AA_MODEL_LOAD_DIR, model.mCurModelName, m_iCopyMarkNo);
	sDes.Format("%s\\%s\\Data\\Mark\\LENS_Mark_%d.mod", AA_MODEL_LOAD_DIR, model.mCurModelName, m_iMarkNo);

	//	MmodRestore(sScr, vision.ModModel[PCB_Chip_MARK][m_iMarkNo]);
#else
	sScr.Format("%s\\%s\\Data\\Mark\\LENS_Mark_%d.pat", AA_MODEL_LOAD_DIR, model.mCurModelName, m_iCopyMarkNo);
	sDes.Format("%s\\%s\\Data\\Mark\\LENS_Mark_%d.pat", AA_MODEL_LOAD_DIR, model.mCurModelName, m_iMarkNo);
#endif

	::CopyFile(sScr, sDes, FALSE);

	model.loadMark(CAM1, PCB_Chip_MARK, m_iMarkNo);
	model.Save();
	//	model.loadMark(PCB_Chip_MARK, m_iMarkNo);

	vision.geometricMarkPreProc(CAM1, PCB_Chip_MARK, m_iMarkNo);

	dispMarkImage();
}

void CLensDlg::changeColorLensSensorLift()
{
	bool bInLensLiftUpFlag, bInLensLiftDownFlag;
	bInLensLiftUpFlag = Dio.PCBPushCheck(true, false);
	bInLensLiftDownFlag = Dio.PCBPushCheck(false, false);

	if(bInLensLiftUpFlag)
	{
		m_btnLensCoverUP.m_iStateBtn = 1;
		m_btnLensCoverDown.m_iStateBtn = 0;
	}
	else if(bInLensLiftDownFlag)
	{
		m_btnLensCoverUP.m_iStateBtn = 0;
		m_btnLensCoverDown.m_iStateBtn = 1;
	}
	else
	{
		m_btnLensCoverUP.m_iStateBtn = 0;
		m_btnLensCoverDown.m_iStateBtn	= 0;
	}
	m_btnLensCoverUP.Invalidate();
	m_btnLensCoverDown.Invalidate();
}
void CLensDlg::changeColorOcLightBtn()
{
	bool flag = false;	
	flag = Dio.OcSlinderCheck(true, false);

	if (flag)
	{ 
		m_btn_OC_For.m_iStateBtn	= 1;
		m_btn_OC_Back.m_iStateBtn	= 0;
	}
	else
	{
		m_btn_OC_For.m_iStateBtn	= 0;
		m_btn_OC_Back.m_iStateBtn	= 1;
	}

	m_btn_OC_For.Invalidate();
	m_btn_OC_Back.Invalidate();

}
void CLensDlg::changeColorPcbTurnBtn()
{
	bool flag = false;
	bool flag2 = false;
	flag = Dio.PcbTurnCheck(true, false);

	if (flag)
	{
		m_btnPcbTurn.m_iStateBtn = 1;
		m_btnPcbReTurn.m_iStateBtn = 0;
	}
	else
	{
		m_btnPcbTurn.m_iStateBtn = 0;
		flag2 = Dio.PcbTurnCheck(false, false);
		if (flag2)
		{
			m_btnPcbTurn.m_iStateBtn = 0;
			m_btnPcbReTurn.m_iStateBtn = 1;
		}
		else
		{
			m_btnPcbReTurn.m_iStateBtn = 0;
		}

	}

	m_btnPcbTurn.Invalidate();
	m_btnPcbReTurn.Invalidate();
}

void CLensDlg::changeColorContactUpBtn()
{
	bool flag = false;
	bool flag2 = false;
	flag = Dio.ContactUpDownCheck(true, false);

	if (flag)
	{
		m_btnContact_UP.m_iStateBtn = 1;
		m_btnContact_DOWN.m_iStateBtn = 0;
	}
	else
	{
		m_btnContact_UP.m_iStateBtn = 0;
		flag2 = Dio.ContactUpDownCheck(false, false);
		if (flag2)
		{
			m_btnContact_UP.m_iStateBtn = 0;
			m_btnContact_DOWN.m_iStateBtn = 1;
		}
		else
		{
			m_btnContact_DOWN.m_iStateBtn = 0;
		}

	}

	m_btnContact_UP.Invalidate();
	m_btnContact_DOWN.Invalidate();
}

void CLensDlg::changeColorUvCylinderBtn()
{
	bool flag = false;
	bool flag2 = false;
	flag = Dio.UVCylinderCheck(true, false);

	if (flag)
	{
		m_btnUVCylinder_Up.m_iStateBtn = 1;
		m_btnUVCylinder_Down.m_iStateBtn = 0;
	}
	else
	{
		m_btnUVCylinder_Up.m_iStateBtn = 0;
		flag2 = Dio.UVCylinderCheck(false, false);
		if (flag2)
		{
			m_btnUVCylinder_Up.m_iStateBtn = 0;
			m_btnUVCylinder_Down.m_iStateBtn = 1;
		}
		else
		{
			m_btnUVCylinder_Down.m_iStateBtn = 0;
		}

	}

	m_btnUVCylinder_Up.Invalidate();
	m_btnUVCylinder_Down.Invalidate();
}

void CLensDlg::changeColorLensLiftBtn()
{
	bool flag = false;	
	bool flag2 = false;	
	flag = Dio.PcbGripCheck(true, false);

	if (flag)
	{ 
		m_btn_PcbGrip_For.m_iStateBtn	= 1;
		m_btn_PcbGrip_Back.m_iStateBtn	= 0;
	}
	else
	{
		m_btn_PcbGrip_For.m_iStateBtn	= 0;
		flag2 = Dio.PcbGripCheck(false, false);
		if (flag2)
		{
			m_btn_PcbGrip_For.m_iStateBtn	= 0;
			m_btn_PcbGrip_Back.m_iStateBtn	= 1;
		}else
		{
			m_btn_PcbGrip_Back.m_iStateBtn	= 0;
		}
		
	}

	m_btn_PcbGrip_For.Invalidate();
	m_btn_PcbGrip_Back.Invalidate();

}
void CLensDlg::changeColorGripBtn()
{
	int moduleNo = 3;
	int channelNo = 0;

	bool bOutGripForFlag	= (curOutDioByte[moduleNo][channelNo] & DIO_OUT_LENS_GRIP_FOR) ? true : false;
	bool bOutGripBackFlag	= (curOutDioByte[moduleNo][channelNo] & DIO_OUT_LENS_GRIP_BACK) ? true : false;

	//bool bInGripForFlag		= (curInDio[1] & DIO_IN_PCBSTAGE_GRIP_FOR) ? true : false;
	//bool bInGripBackFlag	= (curInDio[1] & DIO_IN_PCBSTAGE_GRIP_BACK) ? true : false;


	if(bOutGripForFlag && !bOutGripBackFlag)			// 전진..
	{
		//if(bInGripForFlag && !bInGripBackFlag)
		//{//전진 센서 On일 경우
		//	m_btnGrip_ON.m_iStateBtn	= 1;
		//	m_btnGrip_OFF.m_iStateBtn	= 0;
		//	gripErrCnt = 0;
		//}
		//else
		//{
		//	if(bInGripForFlag && bInGripBackFlag)
		//	{
		//		m_btnGrip_ON.m_iStateBtn	= 1;

		//		if(gripErrCnt>5)	m_btnGrip_OFF.m_iStateBtn	= 0;
		//		else				m_btnGrip_OFF.m_iStateBtn	= 2;
		//	}
		//	else if(!bInGripForFlag && !bInGripBackFlag)
		//	{

		//		if(gripErrCnt>5)	m_btnGrip_ON.m_iStateBtn	= 0;
		//		else				m_btnGrip_ON.m_iStateBtn	= 2;

		//		m_btnGrip_OFF.m_iStateBtn	= 0;
		//	}
		//	else // if(!bInGripForFlag && bInGripBackFlag)
		//	{
		//		if(gripErrCnt>5)
		//		{
		//			m_btnGrip_ON.m_iStateBtn	= 0;
		//			m_btnGrip_OFF.m_iStateBtn	= 0;
		//		}
		//		else
		//		{
		//			m_btnGrip_ON.m_iStateBtn	= 2;
		//			m_btnGrip_OFF.m_iStateBtn	= 1;
		//		}
		//	}

		//	if(gripErrCnt>10)
		//		gripErrCnt = 0;

		//	gripErrCnt++;
		//}
	}
	else if(!bOutGripForFlag && bOutGripBackFlag)		// 후진..
	{
		//if(!bInGripForFlag && bInGripBackFlag)
		//{
		//	m_btnGrip_ON.m_iStateBtn	= 0;
		//	m_btnGrip_OFF.m_iStateBtn	= 1;
		//	gripErrCnt = 0;
		//}
		//else
		//{
		//	if(bInGripForFlag && bInGripBackFlag)
		//	{
		//		if(gripErrCnt>5)
		//			m_btnGrip_ON.m_iStateBtn	= 0;
		//		else
		//			m_btnGrip_ON.m_iStateBtn	= 1;

		//		m_btnGrip_OFF.m_iStateBtn	= 1;
		//	}
		//	else if(!bInGripForFlag && !bInGripBackFlag)
		//	{
		//		m_btnGrip_ON.m_iStateBtn	= 0;

		//		if(gripErrCnt>5)
		//			m_btnGrip_OFF.m_iStateBtn	= 0;
		//		else
		//			m_btnGrip_OFF.m_iStateBtn	= 2;
		//	}
		//	else // if(!bInGripForFlag && bInGripBackFlag)
		//	{
		//		if(gripErrCnt>5)
		//		{
		//			m_btnGrip_ON.m_iStateBtn	= 0;
		//			m_btnGrip_OFF.m_iStateBtn	= 0;
		//		}
		//		else
		//		{
		//			m_btnGrip_ON.m_iStateBtn	= 1;
		//			m_btnGrip_OFF.m_iStateBtn	= 2;
		//		}
		//	}

		//	if(gripErrCnt>10)
		//		gripErrCnt = 0;

		//	gripErrCnt++;
		//}
	}
	else
	{
		/*if(bInGripForFlag)
			m_btnGrip_ON.m_iStateBtn	= 1;
		else
			m_btnGrip_ON.m_iStateBtn	= 0;
		
		if(bInGripBackFlag)
			m_btnGrip_OFF.m_iStateBtn	= 1;
		else
			m_btnGrip_OFF.m_iStateBtn	= 0;*/
	}

	//m_btnGrip_ON.Invalidate();
	//m_btnGrip_OFF.Invalidate();
}

bool CLensDlg::checkCurMotorPos(int iPos)
{
	double dCurPos = 0.0;
	double dMotorPos = 0.0;

	for (int i=Motor_PCB_X ; i<= Motor_PCB_Xt; i++)
	{
		//if (i == Motor_PCB_Z || i == Motor_PCB_Yt )//if ( iPos != Align_Pos && i == Motor_PCB_Z || i == Motor_PCB_Yt )
			//continue;
#if (____AA_WAY == PCB_TILT_AA)
		if (iPos == Bonding_Pos || iPos == Loading_Pos)
		{
			if (i == Motor_PCB_Yt || i == Motor_PCB_Xt )continue;
		}
#else
		
#endif
		if (i == Motor_PCB_Z)continue;
		//
		if (i == Motor_PCB_Yt || i == Motor_PCB_Xt) 
		{
			dCurPos = motor.GetCommandPos(i);
		}
		else 
		{
			dCurPos = motor.GetEncoderPos(i);	//motor.GetCommandPos(i);
		}
		dMotorPos	= model.axis[i].pos[iPos];

		if (iPos==4)
		{
			if (i==0)		dMotorPos	= model.axis[i].pos[Bonding_Pos] + Task.d_Align_offset_x[PCB_Chip_MARK];
			else if (i==1)	dMotorPos	= model.axis[i].pos[Bonding_Pos] + Task.d_Align_offset_y[PCB_Chip_MARK];
			else if (i==2)	dMotorPos	= model.axis[i].pos[Bonding_Pos] + Task.d_Align_offset_th[PCB_Chip_MARK];
		}
	//	double dis = ;
		if (fabs(dMotorPos-dCurPos) > 0.1)
			return false;
	}

	return true;
}

bool CLensDlg::checkMotorPos(int iPos)
{
	double dCurPos;
	double dMotorPos;

	for (int i=Motor_PCB_X ; i<=Motor_PCB_Y ; i++)
	{

		dCurPos		= motor.GetEncoderPos(i);	//motor.GetCommandPos(i);   //motor.GetEncoderPos_Disp(Motor_PCB_X);
		dMotorPos	= model.axis[i].pos[iPos];

		if (fabs(dMotorPos-dCurPos) > 1.5)
		{
			return false;
		}
	}

	return true;
}

bool CLensDlg::checkCurMotorZPos(int iPos)
{
	double dCurPos;
	double dMotorPos;

	dCurPos		= motor.GetEncoderPos(Motor_Lens_Z);	//motor.GetCommandPos(Motor_Lens_Z);
	dMotorPos	= model.axis[Motor_Lens_Z].pos[iPos];

	if (fabs(dMotorPos-dCurPos) > 0.01)
		return false;

	return true;
}

void CLensDlg::changeColorMotorPosBtn()
{
	int iIndex = -1;
	int iIndexZ = -1;

	if (checkCurMotorPos(Wait_Pos))				        iIndex = 0;	//대기
	else if (checkCurMotorPos(Loading_Pos))		        iIndex = 1;	//넘김
	else if (checkCurMotorPos(Align_Pos))		        iIndex = 2;	//Sensor Align
	else if (checkCurMotorPos(Bonding_Pos))		        iIndex = 3;	//Bonding 저장위치
	else if (checkCurMotorPos(OC_6500K_Pos))		    iIndex = 4;	//Stain 저장위치
    else if (checkCurMotorPos(CompleteAlign_Pos))		iIndex = 5;	//완제품 Align 저장위치
	//else if (checkCurMotorPos(OC_2800K_Pos))		    iIndex = 6;
	//else if (checkCurMotorPos(Dark_Pos))				iIndex = 7;
	//else if (checkCurMotorPos(Pcb_Loading_Pos))			iIndex = 8;
	//else if (checkCurMotorPos(Cover_Loading_Pos))		iIndex = 9;
	//else if (checkCurMotorPos(Holder_Uv_Pos))		iIndex = 11;
	//else if (checkCurMotorPos(Cover_UnLoading_Pos))		iIndex = 10;

    //
	m_btnWaitPos.m_iStateBtn = 0;
	m_btnSupplyPos.m_iStateBtn = 0;
	m_btnAlignPos.m_iStateBtn = 0;
	m_btnBondPos.m_iStateBtn = 0;
	m_btnDefectPos.m_iStateBtn = 0;
	m_btnComAlignPos.m_iStateBtn = 0;
	m_btnDarkPos.m_iStateBtn = 0;
	m_btn2800kPos.m_iStateBtn = 0;
	m_btnPcbLoadingPos.m_iStateBtn = 0;
	m_btnCoverLoadingPos.m_iStateBtn = 0;
	//m_btnCoverUnLoadingPos.m_iStateBtn = 0;
	m_btnHolderUvPos.m_iStateBtn = 0;


	if (iIndex==0)				m_btnWaitPos.m_iStateBtn = 3;
	else if (iIndex==1)			m_btnSupplyPos.m_iStateBtn = 3;
	else if (iIndex==2)			m_btnAlignPos.m_iStateBtn = 3;
	else if (iIndex==3)			m_btnBondPos.m_iStateBtn = 3;
	else if (iIndex==4)			m_btnDefectPos.m_iStateBtn = 3;
	else if (iIndex==5)			m_btnComAlignPos.m_iStateBtn = 3;
    else if (iIndex == 6)		m_btn2800kPos.m_iStateBtn = 3;
	else if (iIndex == 7)		m_btnDarkPos.m_iStateBtn = 3;
	else if (iIndex == 8)		m_btnPcbLoadingPos.m_iStateBtn = 3;
	else if (iIndex == 9)		m_btnCoverLoadingPos.m_iStateBtn = 3;
	else if (iIndex == 11)		m_btnHolderUvPos.m_iStateBtn = 3;
	//else if (iIndex == 10)		m_btnCoverUnLoadingPos.m_iStateBtn = 3;

	
   
	m_btnWaitPos.Invalidate();
	m_btnSupplyPos.Invalidate();
	m_btnAlignPos.Invalidate();
	m_btnBondPos.Invalidate();
	m_btnDefectPos.Invalidate();
	m_btnComAlignPos.Invalidate();
    m_btn2800kPos.Invalidate();
	m_btnDarkPos.Invalidate();
	m_btnPcbLoadingPos.Invalidate();
	m_btnCoverLoadingPos.Invalidate();
	//m_btnCoverUnLoadingPos.Invalidate();
	m_btnHolderUvPos.Invalidate();
	//-- Z축 표시
	if (checkCurMotorPosZ(Wait_Pos))
	{
		iIndexZ = 0;
	}
	else if (checkCurMotorPosZ(Loading_Pos))
	{
		iIndexZ = 1;
	}
	else if (checkCurMotorPosZ(OC_6500K_Pos))
	{
		iIndexZ = 2;
	}
	else if (checkCurMotorPosZ(Bonding_Pos))
	{
		iIndexZ = 3;
	}
	else if (checkCurMotorPosZ(Align_Pos))
	{
		iIndexZ = 4;
	}
    else if (checkCurMotorPosZ(CompleteAlign_Pos))
    {
        iIndexZ = 5;
    }
	else if (checkCurMotorPosZ(OC_2800K_Pos))
	{
		iIndexZ = 6;
	}
	else if (checkCurMotorPosZ(Dark_Pos))
	{
		iIndexZ = 7;
	}
	else if (checkCurMotorPosZ(Pcb_Loading_Pos))
	{
		iIndexZ = 8;
	}
	else if (checkCurMotorPosZ(Cover_Loading_Pos))
	{
		iIndexZ = 9;
	}
	else if (checkCurMotorPosZ(Holder_Uv_Pos))
	{
		iIndexZ = 11;
	}
	/*else if (checkCurMotorPosZ(Cover_UnLoading_Pos))
	{
		iIndexZ = 10;
	}*/

	m_btnZWait.m_iStateBtn	= 0;
	m_btnBondPosZ.m_iStateBtn	= 0;
	m_btnSupplyPosZ.m_iStateBtn	= 0;
	m_btnAlignPosZ.m_iStateBtn	= 0;
	m_btnDefectPosZ.m_iStateBtn = 0;
	m_btnComAlignPosZ.m_iStateBtn = 0;
    m_btn2800kPosZ.m_iStateBtn = 0;
	m_btnDarkZPos.m_iStateBtn = 0;
	m_btnPcbLoadingZPos.m_iStateBtn = 0;
	m_btnCoverLoadingZPos.m_iStateBtn = 0;
	//m_btnCoverUnLoadingZPos.m_iStateBtn = 0;
	m_btnHolderUvZPos.m_iStateBtn = 0;
	//
	if (iIndexZ==0)				m_btnZWait.m_iStateBtn	= 1;
	else if (iIndexZ==1)		m_btnSupplyPosZ.m_iStateBtn	= 1;
	else if (iIndexZ==2)		m_btnDefectPosZ.m_iStateBtn	= 1;
	else if (iIndexZ==3)		m_btnBondPosZ.m_iStateBtn	= 1;
	else if (iIndexZ==4)		m_btnAlignPosZ.m_iStateBtn	= 1;
    else if (iIndexZ == 5)			m_btnComAlignPosZ.m_iStateBtn = 1;
	else if (iIndexZ == 6)			m_btn2800kPosZ.m_iStateBtn = 1;
	else if (iIndexZ == 7)			m_btnDarkZPos.m_iStateBtn = 1;
	else if (iIndexZ == 8)			m_btnPcbLoadingZPos.m_iStateBtn = 1;
	else if (iIndexZ == 9)			m_btnCoverLoadingZPos.m_iStateBtn = 1;
	else if (iIndexZ == 11)			m_btnHolderUvZPos.m_iStateBtn = 1;
	//else if (iIndex == 10)			m_btnCoverUnLoadingZPos.m_iStateBtn = 1;


	m_btnZWait.Invalidate();
	m_btnSupplyPosZ.Invalidate();
	m_btnDefectPosZ.Invalidate();
	m_btnBondPosZ.Invalidate();
	m_btnAlignPosZ.Invalidate();
	m_btnComAlignPosZ.Invalidate();
    m_btn2800kPosZ.Invalidate();
	m_btnDarkZPos.Invalidate();
	m_btnPcbLoadingZPos.Invalidate();
	m_btnCoverLoadingZPos.Invalidate();
	//m_btnCoverUnLoadingZPos.Invalidate();
	m_btnHolderUvZPos.Invalidate();


	iIndex = -1;
	if (checkCurInspXMotorPos(Wait_Pos))						iIndex = 0;
	else if (checkCurInspXMotorPos(Align_Pos))					iIndex = 1;
	else if (checkCurInspXMotorPos(OC_6500K_Pos))				iIndex = 2;
	else if (checkCurInspXMotorPos(Dark_Pos))					iIndex = 3;

	m_btnInspXWaitPos.m_iStateBtn = 0;
	m_btnInspXAlignPos.m_iStateBtn = 0;
	m_btnInspXDefectPos.m_iStateBtn = 0;
	m_btnInspXDarkPos.m_iStateBtn = 0;

	if (iIndex == 0)			m_btnInspXWaitPos.m_iStateBtn = 3;
	else if (iIndex == 1)		m_btnInspXAlignPos.m_iStateBtn = 3;
	else if (iIndex == 2)		m_btnInspXDefectPos.m_iStateBtn = 3;
	else if (iIndex == 3)		m_btnInspXDarkPos.m_iStateBtn = 3;

	m_btnInspXWaitPos.Invalidate();
	m_btnInspXAlignPos.Invalidate();
	m_btnInspXDefectPos.Invalidate();
	m_btnInspXDarkPos.Invalidate();
}



void CLensDlg::initMarkGrid()
{
	//CString strTemp;

	//m_gridMark.SetRedraw(FALSE);

	//m_gridMark.SetRows(2);
	//m_gridMark.SetCols(3);

	//m_gridMark.SetColAlignment(0, 4);
	//m_gridMark.SetColAlignment(1, 4);
	//m_gridMark.SetColAlignment(2, 4);

	//m_gridMark.SetColWidth(0,1200);
	//m_gridMark.SetColWidth(1,950);
	//m_gridMark.SetColWidth(2,950);

	//sLangChange.LoadStringA(IDS_STRING761);	//Mark #1
	//m_gridMark.SetTextMatrix(0, 1, sLangChange);
	//sLangChange.LoadStringA(IDS_STRING762);	//Mark #2
	//m_gridMark.SetTextMatrix(0, 2, sLangChange);

	//sLangChange.LoadStringA(IDS_STRING767);	//Matching(%)
	//m_gridMark.SetTextMatrix(1, 0, sLangChange);

	//m_gridMark.SetRowHeight(1, 510);

	//for (int i=0 ; i<2 ; i++)
	//	m_gridMark.SetTextMatrix(1, i+1, "");

	//m_gridMark.SetRedraw(TRUE);
	//m_gridMark.Refresh();
}
void CLensDlg::changeColorPcbCoverSensorBtn()
{
	bool bInLensFlag;

	bInLensFlag = Dio.PCBCoverCloseCheck(true,false);//Dio.LensOnCheck(true, false);

	if(bInLensFlag)
	{
		m_btnPcbCloseSonsor.m_iStateBtn	= 1;
	}
	else
	{
		m_btnPcbCloseSonsor.m_iStateBtn	= 0;
	}
	m_btnPcbCloseSonsor.Invalidate();
}

void CLensDlg::changeColorLensSensorBtn()
{
	bool bInLensFlag;

	bInLensFlag = Dio.LensOnCheck(true, false);

	if(bInLensFlag)
	{
		vaccumErrCnt = 0;

		m_btnLensSonsor.m_iStateBtn	= 1;
	}
	else
	{
		m_btnLensSonsor.m_iStateBtn	= 0;
	}
	m_btnLensSonsor.Invalidate();
}


void CLensDlg::OnBnClickedButtonGotoPcbalign()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	pFrame->m_bIsLensMode = 1;
	pFrame->ctrlSubDlg(PCB_DLG);

}
void CLensDlg::DigLedputData()
{
	
}


void CLensDlg::OnBnClickedButtonGotoLensalign()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CLensDlg::OnBnClickedButtonGotoLensedgeAlign()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	pFrame->m_bIsLensMode = 2;
	pFrame->ctrlSubDlg(LENS_EDGE_DLG);
}


void CLensDlg::OnBnClickedButtonEdgePcbCoverUp()
{// Lens Lift 상승
	if( !func_TaskMovingCheck() )	return;

	g_bMovingflag =true;
	if(!checkCurMotorPos(Dispense_Pos) ||!checkCurMotorPos(Insp_Pos))
	{
		if(!Dio.PCBPushCheck(true, false) == true)
		{
			if(!Dio.PCBPush(true, true))
			{
			}
		}
	}
	MIU.Close();	

	Dio.Relay(true);	// 소켓보드 전원 차단(true)

	//Dio.PCBPush(true, false);

	g_bMovingflag =false;
}


void CLensDlg::OnBnClickedButtonEdgePcbCoverDown()
{// Lens Lift 하강
	if( !func_TaskMovingCheck() )	return;

	if(Dio.PcbGripCheck(false, false) == true)
	{
		CString sTemp;
		//sLangChange.LoadStringA(IDS_STRING1026);	//PCB부 커버 소켓이 열려 있습니다.
		sTemp.Format(_T("DO NOT MOVE!! PCB GRIP OUT STATE"));
		delayMsg(sTemp.GetBuffer(99), 3000, M_COLOR_DARK_GREEN);
		return;
	}

	g_bMovingflag =true;

	Dio.PCBPush(false, false);

	g_bMovingflag =false;
}

void CLensDlg::changeColorOcBtn()
{
	int moduleNo = 2;
	int channelNo = 0;

	//bool bOutPushForFlag	= (curOutDioByte[moduleNo][channelNo] & DIO_OUT_OC_FOR) ? true : false;
	//bool bOutPushBackFlag	= (curOutDioByte[moduleNo][channelNo] & DIO_OUT_OC_BACK) ? true : false;

	//bool bInPushForFlag		= (curInDio[1] & DIO_IN_OC_FOR) ? true : false;
	//bool bInPushBackFlag	= (curInDio[1] & DIO_IN_OC_BACK) ? true : false;


	//if(bOutPushForFlag && !bOutPushBackFlag)			// 전진..
	//{
	//	if(bInPushForFlag && !bInPushBackFlag)
	//	{
	//		m_btn_OC_For.m_iStateBtn	= 1;
	//		m_btn_OC_Back.m_iStateBtn	= 0;
	//		pushErrCnt = 0;
	//	}
	//	else
	//	{
	//		if(bInPushForFlag && bInPushBackFlag)
	//		{
	//			m_btn_OC_For.m_iStateBtn	= 1;

	//			if(pushErrCnt>5)
	//				m_btn_OC_Back.m_iStateBtn	= 0;
	//			else
	//				m_btn_OC_Back.m_iStateBtn	= 2;
	//		}
	//		else if(!bInPushForFlag && !bInPushBackFlag)
	//		{

	//			if(pushErrCnt>5)
	//				m_btn_OC_For.m_iStateBtn	= 0;
	//			else
	//				m_btn_OC_For.m_iStateBtn	= 2;

	//			m_btn_OC_Back.m_iStateBtn	= 0;
	//		}
	//		else // if(!bInPushForFlag && bInPushBackFlag)
	//		{
	//			if(pushErrCnt>5)
	//			{
	//				m_btn_OC_For.m_iStateBtn	= 0;
	//				m_btn_OC_Back.m_iStateBtn	= 0;
	//			}
	//			else
	//			{
	//				m_btn_OC_For.m_iStateBtn	= 2;
	//				m_btn_OC_Back.m_iStateBtn	= 1;
	//			}
	//		}

	//		if(pushErrCnt>10)
	//			pushErrCnt = 0;

	//		pushErrCnt++;
	//	}
	//}
	//else if(!bOutPushForFlag && bOutPushBackFlag)		// 후진..
	//{
	//	if(!bInPushForFlag && bInPushBackFlag)
	//	{
	//		m_btn_OC_For.m_iStateBtn	= 0;
	//		m_btn_OC_Back.m_iStateBtn	= 1;
	//		pushErrCnt = 0;
	//	}
	//	else
	//	{
	//		if(bInPushForFlag && bInPushBackFlag)
	//		{
	//			if(pushErrCnt>5)
	//				m_btn_OC_For.m_iStateBtn	= 0;
	//			else
	//				m_btn_OC_For.m_iStateBtn	= 1;

	//			m_btn_OC_Back.m_iStateBtn	= 1;
	//		}
	//		else if(!bInPushForFlag && !bInPushBackFlag)
	//		{
	//			m_btn_OC_For.m_iStateBtn	= 0;

	//			if(pushErrCnt>5)
	//				m_btn_OC_Back.m_iStateBtn	= 0;
	//			else
	//				m_btn_OC_Back.m_iStateBtn	= 2;
	//		}
	//		else // if(!bInPushForFlag && bInPushBackFlag)
	//		{
	//			if(pushErrCnt>5)
	//			{
	//				m_btn_OC_For.m_iStateBtn	= 0;
	//				m_btn_OC_Back.m_iStateBtn	= 0;
	//			}
	//			else
	//			{
	//				m_btn_OC_For.m_iStateBtn	= 1;
	//				m_btn_OC_Back.m_iStateBtn	= 2;
	//			}
	//		}

	//		if(pushErrCnt>10)
	//			pushErrCnt = 0;

	//		pushErrCnt++;
	//	}
	//}
	//else
	//{
	//	if(bInPushForFlag)
	//		m_btn_OC_For.m_iStateBtn	= 1;
	//	else
	//		m_btn_OC_For.m_iStateBtn	= 0;

	//	if(bInPushBackFlag)
	//		m_btn_OC_Back.m_iStateBtn	= 1;
	//	else
	//		m_btn_OC_Back.m_iStateBtn	= 0;
	//}

	//m_btn_OC_For.Invalidate();
	//m_btn_OC_Back.Invalidate();
}

void CLensDlg::OnBnClickedButtonPcbCoverFor()
{
	if( !func_TaskMovingCheck() )	return;

	g_bMovingflag = true;

	//Dio.OcSlinderMove(true, false);

	g_bMovingflag = false;
}



void CLensDlg::OnBnClickedButtonPcbCoverBack()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	if( !func_TaskMovingCheck() )	return;

	

	g_bMovingflag =true;

	//Dio.OcSlinderMove(false, false);

	g_bMovingflag =false;
}

void CLensDlg::changeColorDarkBtn()
{
	//int moduleNo = 2;
	//int channelNo = 2;

	//bool bOutPushForFlag	= motor.PCB_Z_Motor_Move(Dark_Pos) ? true : false;
	//bool bOutPushBackFlag	= motor.PCB_Z_Motor_Move(Wait_Pos) ? true : false;

	//bool bInPushForFlag		= motor.GetEncoderPos(Motor_PCB_Z) == model.axis[Motor_PCB_Z].pos[Dark_Pos] ? true : false;
	//bool bInPushBackFlag	= motor.GetEncoderPos(Motor_PCB_Z) == model.axis[Motor_PCB_Z].pos[Wait_Pos] ? true : false;


	//if(bOutPushForFlag && !bOutPushBackFlag)			// 전진..
	//{
	//	if(bInPushForFlag && !bInPushBackFlag)
	//	{
	//		m_btnDarkUp.m_iStateBtn	= 1;
	//		m_btnDarkDown.m_iStateBtn = 0;
	//		pushErrCnt = 0;
	//	}
	//	else
	//	{
	//		if(bInPushForFlag && bInPushBackFlag)
	//		{
	//			m_btnDarkUp.m_iStateBtn	= 1;

	//			if(pushErrCnt>5)
	//				m_btnDarkDown.m_iStateBtn	= 0;
	//			else
	//				m_btnDarkDown.m_iStateBtn	= 2;
	//		}
	//		else if(!bInPushForFlag && !bInPushBackFlag)
	//		{

	//			if(pushErrCnt>5)
	//				m_btnDarkUp.m_iStateBtn	= 0;
	//			else
	//				m_btnDarkUp.m_iStateBtn	= 2;

	//			m_btnDarkDown.m_iStateBtn	= 0;
	//		}
	//		else // if(!bInPushForFlag && bInPushBackFlag)
	//		{
	//			if(pushErrCnt>5)
	//			{
	//				m_btnDarkUp.m_iStateBtn	= 0;
	//				m_btnDarkDown.m_iStateBtn	= 0;
	//			}
	//			else
	//			{
	//				m_btnDarkUp.m_iStateBtn	= 2;
	//				m_btnDarkDown.m_iStateBtn	= 1;
	//			}
	//		}

	//		if(pushErrCnt>10)
	//			pushErrCnt = 0;

	//		pushErrCnt++;
	//	}
	//}
	//else if(!bOutPushForFlag && bOutPushBackFlag)		// 후진..
	//{
	//	if(!bInPushForFlag && bInPushBackFlag)
	//	{
	//		m_btnDarkUp.m_iStateBtn	= 0;
	//		m_btnDarkDown.m_iStateBtn	= 1;
	//		pushErrCnt = 0;
	//	}
	//	else
	//	{
	//		if(bInPushForFlag && bInPushBackFlag)
	//		{
	//			if(pushErrCnt>5)
	//				m_btnDarkUp.m_iStateBtn	= 0;
	//			else
	//				m_btnDarkUp.m_iStateBtn	= 1;

	//			m_btnDarkDown.m_iStateBtn	= 1;
	//		}
	//		else if(!bInPushForFlag && !bInPushBackFlag)
	//		{
	//			m_btnDarkUp.m_iStateBtn	= 0;

	//			if(pushErrCnt>5)
	//				m_btnDarkDown.m_iStateBtn	= 0;
	//			else
	//				m_btnDarkDown.m_iStateBtn	= 2;
	//		}
	//		else // if(!bInPushForFlag && bInPushBackFlag)
	//		{
	//			if(pushErrCnt>5)
	//			{
	//				m_btnDarkUp.m_iStateBtn	= 0;
	//				m_btnDarkDown.m_iStateBtn	= 0;
	//			}
	//			else
	//			{
	//				m_btnDarkUp.m_iStateBtn	= 1;
	//				m_btnDarkDown.m_iStateBtn	= 2;
	//			}
	//		}

	//		if(pushErrCnt>10)
	//			pushErrCnt = 0;

	//		pushErrCnt++;
	//	}
	//}
	//else
	//{
	//	if(bInPushForFlag)
	//		m_btnDarkUp.m_iStateBtn	= 1;
	//	else
	//		m_btnDarkUp.m_iStateBtn	= 0;

	//	if(bInPushBackFlag)
	//		m_btnDarkDown.m_iStateBtn	= 1;
	//	else
	//		m_btnDarkDown.m_iStateBtn	= 0;
	//}

	//m_btnDarkUp.Invalidate();
	//m_btnDarkDown.Invalidate();
}

void CLensDlg::OnBnClickedButtonPcbDarkUp()
{
	if( !func_TaskMovingCheck() )	return;

	if ( !checkCurMotorPos(Dark_Pos) )
	{
		delayMsg("Do not Dark Pos", 2000, M_COLOR_RED);
		return;
	}

	/* 이동중이면 Return */
	if(g_bMovingflag)		return;
	g_bMovingflag =true;
	
	Dio.PCBDark(true, false);
	g_bMovingflag =false;
}

bool CLensDlg::func_TaskMovingCheck()
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
	return true;
}

bool CLensDlg::func_MovingInterlock()
{
	if( !checkCurMotorPosZ(Wait_Pos) )
	{
		delayMsg("PCB Wait_Pos Z위치가 아닙니다", 1000, M_COLOR_RED);
		return false;
	}

	//if(!motor.LENS_Z_Motor_Move(Wait_Pos))
	//{
	//	sLangChange.LoadStringA(IDS_STRING739);	//Lens_Z축 대기위치 이동 실패.
	//	delayMsg(sLangChange, 1000, M_COLOR_RED);
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
	//if(!motor.Laser_Z_Motor_Move(Wait_Pos))
	//{
	//	sLangChange.LoadStringA(IDS_STRING641);	//Laser_Z축 대기위치 이동 실패
	//	delayMsg(sLangChange, 1000, M_COLOR_RED);
	//	g_bMovingflag =false;
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

	/*if( !Dio.LensLiftCheck(false, false) )
	{
		if ( !Dio.LensLift(false, true) )
		{
			g_bMovingflag =false;
			return false;
		}
	}*/

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

void CLensDlg::OnBnClickedButtonMotorDarkInsp()
{
	if( !func_TaskMovingCheck() )	return;

	g_bMovingflag =true;

	if( !func_MovingInterlock() )	return;

	if(!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		g_bMovingflag =false;
		return;
	}
	 
	if(motor.Pcb_Motor_Move(Dark_Pos))
	{
		CString sTmpLog;
		sLangChange.LoadStringA(IDS_STRING899);	//"PCB %s 이동 완료"
		sTmpLog.Format(sLangChange, MotorPosName[Dark_Pos]);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
	}

	g_bMovingflag = false;
}


void CLensDlg::OnBnClickedButtonMotorDefectInsp()
{
	if( !func_TaskMovingCheck() )	return;

	g_bMovingflag =true;

	if( !func_MovingInterlock())
	{
		g_bMovingflag =false;
		return;
	}

	if(motor.Pcb_Motor_Move(OC_6500K_Pos))
	{
		CString sTmpLog;
		sTmpLog.Format("PCB %s 이동 완료", MotorPosName[OC_6500K_Pos]);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
	}

	g_bMovingflag = false;
}


void CLensDlg::OnBnClickedButtonPcbDarkDown()
{
	if( !func_TaskMovingCheck() )	return;

	/* 이동중이면 Return */
	if(g_bMovingflag)		return;
	g_bMovingflag =true;
	
	Dio.PCBDark(false, false);

	g_bMovingflag =false;
}


void CLensDlg::OnBnClickedButtonMotorSupply2()
{
	if( !func_TaskMovingCheck() )	return;

	g_bMovingflag =true;

	if( !func_MovingInterlock() )	return;

	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	double offsetX, offsetY, offsetTh;
	int iRtnVal;
	int  iRtn = 0;//pFrame->procCamAlign(CAM1, PCB_Chip_MARK, false, offsetX, offsetY, offsetTh);
	
	CString sMsg;
	sLangChange.LoadStringA(IDS_STRING969);	//PCB Unit 보정 값[X:%.04lf, Y:%.04lf, T:%.04lf]으로 넘김 위치 이동 하시겠습니까?
	sMsg.Format(sLangChange, 
		Task.d_Align_offset_x[PCB_Chip_MARK], 
		Task.d_Align_offset_y[PCB_Chip_MARK], 
		Task.d_Align_offset_th[PCB_Chip_MARK] );

	if ( askMsg(sMsg) != IDOK)
	{
		g_bMovingflag =false;
		return;
	}
	offsetX = Task.d_Align_offset_x[PCB_Chip_MARK];
	offsetY = Task.d_Align_offset_y[PCB_Chip_MARK];
	offsetTh = Task.d_Align_offset_th[PCB_Chip_MARK];


	iRtnVal = pFrame->AlignLimitCheck(CAM1, offsetX, offsetY, offsetTh);
	//double pos[3];
	if(iRtnVal==0)
	{
		sLangChange.LoadStringA(IDS_STRING1263);	//보정값 이동 범위가 Limit 초과 했습니다.
			errMsg2(Task.AutoFlag, sLangChange);
	}
	else
	{
		//pos[0]	= (motor.GetCommandPos(Motor_PCB_X) - model.axis[Motor_PCB_X].pos[Align_Pos])	- offsetX;
		//pos[1]	= (motor.GetCommandPos(Motor_PCB_Y) - model.axis[Motor_PCB_Y].pos[Align_Pos])	- offsetY;
		//pos[2]	= (motor.GetCommandPos(Motor_PCB_TH) - model.axis[Motor_PCB_TH].pos[Align_Pos])	+ offsetTh;

		CString sTemp;
		sLangChange.LoadStringA(IDS_STRING1482);	//보정값 : %.3lf %.3lf %.3lf
		sTemp.Format(sLangChange, offsetX, offsetY, offsetTh);
		m_labelAlignResult.SetText(sTemp);
		m_labelAlignResult.Invalidate();

		if( !motor.Pcb_Motor_Move(Loading_Pos, offsetX, offsetY, offsetTh) )
		{
			CString sTmpLog;
			sLangChange.LoadStringA(IDS_STRING1016);	//PCB부 Lens %s 이동 완료
			sTmpLog.Format(sLangChange, MotorPosName[Loading_Pos]);
			delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
		}
	}


	pFrame->m_rBox.left = 0;
	pFrame->m_rBox.top = 0;
	pFrame->m_rBox.right = 0;
	pFrame->m_rBox.bottom = 0;

	g_bMovingflag =false;
}

void CLensDlg::OnBnClickedButtonBacklightIn()
{
	if( !func_TaskMovingCheck() )	return;

	/* 이동중이면 Return */
	if(g_bMovingflag)		return;
	g_bMovingflag =true;
	
	motor.PCB_Z_Motor_Move(Wait_Pos);

	g_bMovingflag =false;
}


void CLensDlg::OnBnClickedButtonBacklightOut()
{
	if( !func_TaskMovingCheck() )	return;

	if ( !checkCurMotorPos(Defect_Pos) )
	{
		delayMsg("Do not Defect Pos", 2000, M_COLOR_RED);
		return;
	}

	/* 이동중이면 Return */
	if(g_bMovingflag)		return;
	g_bMovingflag =true;
	
	if(!motor.PCB_Z_Motor_Move(Defect_Pos))
	{
		sLangChange.Format("PCB Z axis Defect Pos Move Failed");
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		g_bMovingflag =false;
		return;
	}

	g_bMovingflag =false;
}


void CLensDlg::changeColorBackLightBtn()
{
	//if (Dio.BackLightOnCheck(true, false))
	//{
	//	m_btnBackLightOn.m_iStateBtn	= 1;
	//	m_btnBackLightOff.m_iStateBtn	= 0;
	//}
	//else if (Dio.BackLightOnCheck(false, false))
	//{
	//	m_btnBackLightOn.m_iStateBtn	= 0;
	//	m_btnBackLightOff.m_iStateBtn	= 1;
	//}

	//m_btnBackLightOn.Invalidate();
	//m_btnBackLightOff.Invalidate();
}

bool CLensDlg::checkCurMotorPosZ(int iPos)
{	/* 모터 위치 확인 */
	double dCurPos;
	double dMotorPos;

	
	dCurPos		= motor.GetEncoderPos(Motor_PCB_Z);
	dMotorPos	= model.axis[Motor_PCB_Z].pos[iPos];

	if (fabs(dMotorPos-dCurPos) > 0.01)
		return false;

	return true;
}

bool CLensDlg::checkCurInspXMotorPos(int iPos)
{
	double dCurPos;
	double dMotorPos;


	dCurPos = motor.GetEncoderPos(Motor_Insp_X);	//motor.GetCommandPos(i);
	dMotorPos = model.axis[Motor_Insp_X].pos[iPos];

	if (fabs(dMotorPos - dCurPos) > 0.01)
		return false;

	return true;
}

void CLensDlg::OnBnClickedButtonEdgePcbGrip()
{//PCB GRIP
	if( !func_TaskMovingCheck() )	return;
	
	if(Dio.PCBPushCheck(false, false) == true)
	{
		CString sTemp;
		//sLangChange.LoadStringA(IDS_STRING1026);	//PCB부 커버 소켓이 열려 있습니다.
		sTemp.Format(_T("DO NOT MOVE!! PCB LIFT DOWN STATE"));
		delayMsg(sTemp.GetBuffer(99), 3000, M_COLOR_DARK_GREEN);
		return;
	}

	g_bMovingflag =true;

	Dio.Relay(true);	// 소켓보드 전원 차단(true)
	Dio.PcbGrip(true, false);

	g_bMovingflag =false;
}



void CLensDlg::OnBnClickedButtonEdgePcbUngrip()
{//PCB UNGRIP
	if( !func_TaskMovingCheck() )	return;

	if(Dio.PCBPushCheck(false, false) == true)
	{
		CString sTemp;
		sLangChange.LoadStringA(IDS_STRING1026);	//PCB부 커버 소켓이 열려 있습니다.
		//sTemp.Format(_T("DO NOT MOVE!! PCB LIFT DOWN STATE"));
		delayMsg(sTemp.GetBuffer(99), 3000, M_COLOR_DARK_GREEN);
		return;
	}

	g_bMovingflag =true;

	Dio.Relay(true);	// 소켓보드 전원 차단(true)

	Dio.PcbGrip(false, false);

	g_bMovingflag =false;
}


void CLensDlg::OnBnClickedButtonMotorZWait()
{
	if( !func_TaskMovingCheck() )	return;

	g_bMovingflag =true;

	if(!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		sLangChange.Format("PCB Z axis Wait_Pos Move Failed");
		delayMsg(sLangChange, 1000, M_COLOR_RED);
	}
	g_bMovingflag =false;
}

void CLensDlg::changeColorPcbGripBtn()
{
	int moduleNo = 3;
	int channelNo = 0;

	//bool bOutPcbGripForFlag	= (curOutDioByte[moduleNo][channelNo] & DIO_OUT_PCB_GRIP_FOR) ? true : false;
	//bool bOutPcbGripBackFlag	= (curOutDioByte[moduleNo][channelNo] & DIO_OUT_PCB_GRIP_BACK) ? true : false;

	//bool bInPcbGripForFlag		= (curInDio[1] & DIO_IN_PCB_GRIP_FOR) ? true : false;
	//bool bInPcbGripBackFlag	= (curInDio[1] & DIO_IN_PCB_GRIP_BACK) ? true : false;


	//if(bOutPcbGripForFlag && !bOutPcbGripBackFlag)			// 전진..
	//{
	//	if(bInPcbGripForFlag && !bInPcbGripBackFlag)
	//	{//전진 센서 On일 경우
	//		m_btnPcbGrip.m_iStateBtn	= 1;
	//		m_btnPcbUnGrip.m_iStateBtn	= 0;
	//		gripErrCnt = 0;
	//	}
	//	else
	//	{
	//		if(bInPcbGripForFlag && bInPcbGripBackFlag)
	//		{
	//			m_btnPcbGrip.m_iStateBtn	= 1;

	//			if(gripErrCnt>5)	m_btnPcbUnGrip.m_iStateBtn	= 0;
	//			else				m_btnPcbUnGrip.m_iStateBtn	= 2;
	//		}
	//		else if(!bInPcbGripForFlag && !bInPcbGripBackFlag)
	//		{

	//			if(gripErrCnt>5)	m_btnPcbGrip.m_iStateBtn	= 0;
	//			else				m_btnPcbGrip.m_iStateBtn	= 2;

	//			m_btnPcbUnGrip.m_iStateBtn	= 0;
	//		}
	//		else // if(!bInGripForFlag && bInGripBackFlag)
	//		{
	//			if(gripErrCnt>5)
	//			{
	//				m_btnPcbGrip.m_iStateBtn	= 0;
	//				m_btnPcbUnGrip.m_iStateBtn	= 0;
	//			}
	//			else
	//			{
	//				m_btnPcbGrip.m_iStateBtn	= 2;
	//				m_btnPcbUnGrip.m_iStateBtn	= 1;
	//			}
	//		}

	//		if(gripErrCnt>10)
	//			gripErrCnt = 0;

	//		gripErrCnt++;
	//	}
	//}
	//else if(!bOutPcbGripForFlag && bOutPcbGripBackFlag)		// 후진..
	//{
	//	if(!bInPcbGripForFlag && bInPcbGripBackFlag)
	//	{
	//		m_btnPcbGrip.m_iStateBtn	= 0;
	//		m_btnPcbUnGrip.m_iStateBtn	= 1;
	//		gripErrCnt = 0;
	//	}
	//	else
	//	{
	//		if(bInPcbGripForFlag && bInPcbGripBackFlag)
	//		{
	//			if(gripErrCnt>5)
	//				m_btnPcbGrip.m_iStateBtn	= 0;
	//			else
	//				m_btnPcbGrip.m_iStateBtn	= 1;

	//			m_btnPcbUnGrip.m_iStateBtn	= 1;
	//		}
	//		else if(!bInPcbGripForFlag && !bInPcbGripBackFlag)
	//		{
	//			m_btnPcbGrip.m_iStateBtn	= 0;

	//			if(gripErrCnt>5)
	//				m_btnPcbUnGrip.m_iStateBtn	= 0;
	//			else
	//				m_btnPcbUnGrip.m_iStateBtn	= 2;
	//		}
	//		else // if(!bInGripForFlag && bInGripBackFlag)
	//		{
	//			if(gripErrCnt>5)
	//			{
	//				m_btnPcbGrip.m_iStateBtn	= 0;
	//				m_btnPcbUnGrip.m_iStateBtn	= 0;
	//			}
	//			else
	//			{
	//				m_btnPcbGrip.m_iStateBtn	= 1;
	//				m_btnPcbUnGrip.m_iStateBtn	= 2;
	//			}
	//		}

	//		if(gripErrCnt>10)
	//			gripErrCnt = 0;

	//		gripErrCnt++;
	//	}
	//}
	//else
	//{
	//	if(bInPcbGripForFlag)
	//		m_btnPcbGrip.m_iStateBtn	= 1;
	//	else
	//		m_btnPcbGrip.m_iStateBtn	= 0;
	//	
	//	if(bInPcbGripBackFlag)
	//		m_btnPcbUnGrip.m_iStateBtn	= 1;
	//	else
	//		m_btnPcbUnGrip.m_iStateBtn	= 0;
	//}

	//m_btnPcbGrip.Invalidate();
	//m_btnPcbUnGrip.Invalidate();
}

void CLensDlg::OnBnClickedButtonZMotorUpBonding()
{
	if( !func_TaskMovingCheck() )	return;

	if ( !checkMotorPos(Bonding_Pos) )
	{
		delayMsg("Do not Bonding_Pos", 2000, M_COLOR_RED);
		return;
	}
	g_bMovingflag =true;
	CString sTmpLog = _T("");
	//pcb 가 본딩위치인지 체크해서 lens z축 회피해서 본딩위치 이동
	double LensPosX = (float)model.axis[Motor_Lens_X].pos[Bonding_Pos] - (float)motor.GetEncoderPos(Motor_Lens_X);
	double LensPosY = (float)model.axis[Motor_Lens_Y].pos[Bonding_Pos] - (float)motor.GetEncoderPos(Motor_Lens_Y);
	double LensPosZ = (float)model.axis[Motor_Lens_Z].pos[Bonding_Pos] - (float)motor.GetCommandPos(Motor_Lens_Z);
	//if (fabs(LensPosX) < 2.1 && fabs(LensPosY) < 2.1)
	if (fabs(LensPosX) > 0.3 && fabs(LensPosY) > 0.3)
	{
		if (fabs(LensPosZ) > 2.1)
		{
			if (sysData.m_iProductComp == 0)
			{

				sTmpLog.Format("Lens Z 본딩위치 이동후 진행하십시오!");
				delayMsg(sTmpLog, 5000, M_COLOR_RED);
				g_bMovingflag = false;
				return;
			}
		}
	}
	if(!motor.PCB_Z_Motor_Move(Bonding_Pos))
	{
		sLangChange.Format("PCB Z axis Bonding_Pos Move Failed");
		delayMsg(sLangChange, 1000, M_COLOR_RED);
	}

	g_bMovingflag =false;
}




void CLensDlg::OnBnClickedButtonMotorDefectInspZ()
{
	if( !func_TaskMovingCheck() )	return;

	if ( !checkCurMotorPos(OC_6500K_Pos) )
	{
		delayMsg("Do not OC 6500K Pos Pos", 2000, M_COLOR_RED);
		return;
	}

	g_bMovingflag =true;


	if(!motor.PCB_Z_Motor_Move(OC_6500K_Pos))
	{
		sLangChange.Format("PCB Z axis OC 6500K Pos Move Failed");
		delayMsg(sLangChange, 1000, M_COLOR_RED);
	}
	g_bMovingflag =false;
}


void CLensDlg::OnBnClickedButtonMotorAlignZ()
{
	if( !func_TaskMovingCheck() )	return;


	if ( !checkMotorPos(Align_Pos) )
	{
		delayMsg("Do not Align_Pos", 2000, M_COLOR_RED);
		return;
	}
	g_bMovingflag =true;

	if(!motor.PCB_Z_Motor_Move(Align_Pos))
	{
		sLangChange.Format("PCB Z axis Align_Pos Move Failed");
		delayMsg(sLangChange, 1000, M_COLOR_RED);
	}

	g_bMovingflag =false;
}


void CLensDlg::OnBnClickedButtonMotorSupplyZ()
{
	if( !func_TaskMovingCheck() )	return;
	if ( !checkMotorPos(Loading_Pos) )
	{
		delayMsg("Do not Loading_Pos", 2000, M_COLOR_RED);
		return;
	}
	g_bMovingflag =true;
	if(!motor.PCB_Z_Motor_Move(Loading_Pos))
	{
		sLangChange.Format("PCB Z axis Loading_Pos Move Failed");
		delayMsg(sLangChange, 1000, M_COLOR_RED);
	}

	g_bMovingflag =false;
}


void CLensDlg::OnBnClickedButtonBacklightOutPre()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CLensDlg::OnBnClickedButtonOpticalInsp()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}
	CString str="";
	int iRtn = 0;
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	pFrame->putListLog(" [수동 완제품Align 검사]");
	double offsetX = 0.0,offsetY = 0.0, offsetTh=0.0;
	//
	iRtn = pFrame->procCamComAlign(CAM1, PCB_Chip_MARK, false , offsetX, offsetY, offsetTh);
	if(iRtn==1)
	{
		str.Format("완제품 Align :x: %.4lf, y: %.4lf, th: %.4lf" ,offsetX,offsetY,offsetTh);
		pFrame->putListLog(str);
	}else
	{
		pFrame->putListLog("[수동 완제품Align 검사] 마크 인식 실패");
	}
}


void CLensDlg::OnBnClickedButtonPcbGripFor()
{
	//if( !func_TaskMovingCheck() )	return;

	g_bMovingflag = true;

	//Dio.LensLift(true, false);
	Dio.PcbGrip(true, false);

	g_bMovingflag = false;
}


void CLensDlg::OnBnClickedButtonPcbGripBack()
{
	if( !func_TaskMovingCheck() )	return;

	g_bMovingflag = true;

	//Dio.LensLift(false, false);
	Dio.PcbGrip(false, false); 

	g_bMovingflag = false;
}


void CLensDlg::OnBnClickedButtonComAlignTest()
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

	double offsetX = 0.0;
	double offsetY = 0.0;
	double offsetTh = 0.0;
	
	int iRtnVal = 0;
	int  iRtn = pFrame->procCamComAlign(CAM1, PCB_Chip_MARK, true, offsetX, offsetY, offsetTh);
	if(!_finite(offsetX)){offsetX=0;}
	if(!_finite(offsetY)){offsetY=0;}
	if(!_finite(offsetTh)){offsetTh=0;} 
	if (iRtn == 1)
	{

	offsetTh = 0.0;
		iRtnVal = pFrame->AlignLimitCheck(CAM1, offsetX, offsetY, offsetTh);


		if(iRtnVal==0)
		{
			sLangChange.LoadStringA(IDS_STRING1263);	//보정값 이동 범위가 Limit 초과 했습니다.
			errMsg2(Task.AutoFlag, sLangChange);
		}
		else
		{
			short axis[3];
			double pos[3];

			axis[0] = Motor_PCB_X;
			axis[1] = Motor_PCB_Y;
			axis[2] = Motor_PCB_TH;

			pos[0]	= motor.GetCommandPos(Motor_PCB_X)		- offsetX;
			pos[1]	= motor.GetCommandPos(Motor_PCB_Y)		- offsetY;
			pos[2]	= motor.GetCommandPos(Motor_PCB_TH)		+ offsetTh;

			Task.d_Align_offset_x[PCB_Chip_MARK] = -offsetX;
			Task.d_Align_offset_y[PCB_Chip_MARK] = -offsetY;
			Task.d_Align_offset_th[PCB_Chip_MARK] = offsetTh;

			motor.goMotorPos(3, axis, pos);
			sLangChange.LoadStringA(IDS_STRING1261);	//보정 이동 완료.
			delayMsg(sLangChange, 3000, M_COLOR_GREEN);
			Sleep(10);

			pos[0]	= (pos[0] - model.axis[Motor_PCB_X].pos[CompleteAlign_Pos]);
			pos[1]	= (pos[1] - model.axis[Motor_PCB_Y].pos[CompleteAlign_Pos]);
			pos[2]	= (pos[2] - model.axis[Motor_PCB_TH].pos[CompleteAlign_Pos]);

			CString sTemp="";
			sTemp.Format("보정값 : %.3lf %.3lf %.3lf", pos[0], pos[1], pos[2]);
			m_labelAlignResult.SetText(sTemp);
			m_labelAlignResult.Invalidate();

			double etime = myTimer(true);
			while(1)
			{
				if(motor.IsStopAxis(Motor_PCB_X)  && motor.IsStopAxis(Motor_PCB_Y) && 
					motor.IsStopAxis(Motor_PCB_TH) )		
				{
					Sleep(20);
					break;
				}
				if((myTimer(true) - etime) > 3000)
				{
					sLangChange.LoadStringA(IDS_STRING1260);	//보정 위치 이동 실패
					delayMsg(sLangChange, 3000, M_COLOR_RED);
					break;
				}
			}
		}
	}
	else
	{
		sLangChange.LoadStringA(IDS_STRING1215);	//마크 인식 실패.
		errMsg2(Task.AutoFlag, sLangChange);
	}

		//vision.textlist[CAM1].addList((CAM_SIZE_X-140), (CAM_SIZE_Y-60), sTemp, M_COLOR_WHITE, 24, 10, "Arial");
		//vision.drawOverlay(CAM1);

	CString sLog="";
	//sLangChange.LoadStringA(IDS_STRING658);	//Lens Align 보정값 X:%.03f, Y:%.03f, Θ:%.04f
	sLog.Format("완제품 Align 보정값 : %.3lf %.3lf %.3lf", offsetX, offsetY, offsetTh);
	pFrame->putListLog(sLog);
	sLog.Empty();
}


void CLensDlg::OnBnClickedButtonMotorComAlign()
{
	if( !func_TaskMovingCheck() )	return;
	if( !func_MovingInterlock())
	{
		return;
	}
	g_bMovingflag =true;
	if(!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		sLangChange.Format("PCB Z axis Wait_Pos Move Failed");
		delayMsg(sLangChange, 1000, M_COLOR_RED);
	}
	if(	motor.Pcb_Motor_Move(CompleteAlign_Pos))
	{
		sLangChange.LoadStringA(IDS_STRING1015);	//PCB부 %s 이동 완료
		sTempLang.Format(sLangChange, MotorPosName[CompleteAlign_Pos]);
		delayMsg(sTempLang.GetBuffer(99), 3000, M_COLOR_GREEN);
	}

	

	g_bMovingflag =false;
}


void CLensDlg::OnBnClickedButtonMotorComAlignZ()
{
	if( !func_TaskMovingCheck() )	return;


	if ( !checkMotorPos(CompleteAlign_Pos) )
	{
		delayMsg("Do not CompleteAlign_Pos", 2000, M_COLOR_RED);
		return;
	}
	g_bMovingflag =true;

	if(!motor.PCB_Z_Motor_Move(CompleteAlign_Pos))
	{
		sLangChange.Format("PCB Z axis CompleteAlign_Pos Move Failed");
		delayMsg(sLangChange, 1000, M_COLOR_RED);
	}

	g_bMovingflag =false;
}


void CLensDlg::OnBnClickedButtonMotor2800kInsp()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    if (!func_TaskMovingCheck())	return;

    g_bMovingflag = true;

    if (!func_MovingInterlock())
    {
        g_bMovingflag = false;
        return;
    }

    if (motor.Pcb_Motor_Move(OC_2800K_Pos))
    {
        CString sTmpLog;
        sTmpLog.Format("PCB %s 이동 완료", MotorPosName[OC_2800K_Pos]);
        delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
    }

    g_bMovingflag = false;
}


void CLensDlg::OnBnClickedButtonMotor2800kInspZ()
{
    if (!func_TaskMovingCheck())	return;

    if (!checkCurMotorPos(OC_2800K_Pos))
    {
        delayMsg("Do not OC_2800K_Pos Pos", 2000, M_COLOR_RED);
        return;
    }

    g_bMovingflag = true;


    if (!motor.PCB_Z_Motor_Move(OC_2800K_Pos))
    {
        sLangChange.Format("PCB Z axis OC_2800K_Pos Pos Move Failed");
        delayMsg(sLangChange, 1000, M_COLOR_RED);
    }
    g_bMovingflag = false;
}


void CLensDlg::OnBnClickedButtonMotorZDarkInsp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!func_TaskMovingCheck())	return;

	if (!checkCurMotorPos(Dark_Pos))
	{
		delayMsg("Do not Dark_Pos Pos", 2000, M_COLOR_RED);
		return;
	}

	g_bMovingflag = true;

	if (!motor.PCB_Z_Motor_Move(Dark_Pos))
	{
		sLangChange.Format("PCB Z axis Dark_Pos Pos Move Failed");
		delayMsg(sLangChange, 1000, M_COLOR_RED);
	}
	g_bMovingflag = false;
}


void CLensDlg::OnBnClickedButtonContactUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}
	if (g_bMovingflag)
	{
		sLangChange.LoadStringA(IDS_STRING1228);	//모터 구동 중 사용 불가..
		delayMsg(sLangChange, 2000, M_COLOR_RED);
		return;
	}
	g_bMovingflag = true;

	Dio.ContactUpDown(true, false);

	g_bMovingflag = false;
}


void CLensDlg::OnBnClickedButtonMotorPcbLoading()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sTmpLog;

	if (!func_TaskMovingCheck())	return;

	if (!func_MovingInterlock())
	{
		return;
	}
	g_bMovingflag = true;
	if (!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		sLangChange.Format("PCB Z axis Wait_Pos Move Failed");
		delayMsg(sLangChange, 1000, M_COLOR_RED);
	}
	if (!motor.Pcb_Tilt_Motor_Move(Pcb_Loading_Pos))
	{
		sLangChange.LoadStringA(IDS_STRING1017);	//PCB부 Tx, Ty축 대기 위치 이동 실패
		sTmpLog.Format(sLangChange);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_RED);
		g_bMovingflag = false;
		return;
	}

	if (!motor.Pcb_Motor_Move(Pcb_Loading_Pos))
	{
		sLangChange.LoadStringA(IDS_STRING1481);	//PCB부 %s 이동 실패
		sTmpLog.Format(sLangChange, MotorPosName[Pcb_Loading_Pos]);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_RED);
		g_bMovingflag = false;
		return;
	}

	g_bMovingflag = false;
}


void CLensDlg::OnBnClickedButtonMotorCoverLoading()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sTmpLog;

	if (!func_TaskMovingCheck())	return;

	if (!func_MovingInterlock())
	{
		return;
	}
	g_bMovingflag = true;
	if (!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		sLangChange.Format("PCB Z axis Wait_Pos Move Failed");
		delayMsg(sLangChange, 1000, M_COLOR_RED);
	}
	if (!motor.Pcb_Tilt_Motor_Move(Cover_Loading_Pos))
	{
		sLangChange.LoadStringA(IDS_STRING1017);	//PCB부 Tx, Ty축 대기 위치 이동 실패
		sTmpLog.Format(sLangChange);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_RED);
		g_bMovingflag = false;
		return;
	}

	if (!motor.Pcb_Motor_Move(Cover_Loading_Pos))
	{
		sLangChange.LoadStringA(IDS_STRING1481);	//PCB부 %s 이동 실패
		sTmpLog.Format(sLangChange, MotorPosName[Cover_Loading_Pos]);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_RED);
		g_bMovingflag = false;
		return;
	}

	g_bMovingflag = false;
}


void CLensDlg::OnBnClickedButtonMotorZPcbLoading()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!func_TaskMovingCheck())	return;
	if (!checkMotorPos(Pcb_Loading_Pos))
	{
		delayMsg("Do not Pcb_Loading_Pos", 2000, M_COLOR_RED);
		return;
	}
	g_bMovingflag = true;
	if (!motor.PCB_Z_Motor_Move(Pcb_Loading_Pos))
	{
		sLangChange.Format("PCB Z axis Pcb_Loading_Pos Move Failed");
		delayMsg(sLangChange, 1000, M_COLOR_RED);
	}

	g_bMovingflag = false;
}


void CLensDlg::OnBnClickedButtonMotorZCoverLoading()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!func_TaskMovingCheck())	return;
	if (!checkMotorPos(Cover_Loading_Pos))
	{
		delayMsg("Do not Cover_Loading_Pos", 2000, M_COLOR_RED);
		return;
	}
	g_bMovingflag = true;
	if (!motor.PCB_Z_Motor_Move(Cover_Loading_Pos))
	{
		sLangChange.Format("PCB Z axis Cover_Loading_Pos Move Failed");
		delayMsg(sLangChange, 1000, M_COLOR_RED);
	}

	g_bMovingflag = false;
}


void CLensDlg::OnBnClickedButtonContactDown()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}
	if (g_bMovingflag)
	{
		sLangChange.LoadStringA(IDS_STRING1228);	//모터 구동 중 사용 불가..
		delayMsg(sLangChange, 2000, M_COLOR_RED);
		return;
	}
	g_bMovingflag = true;

	Dio.ContactUpDown(false, false);

	g_bMovingflag = false;
}


void CLensDlg::OnBnClickedButtonMotorCoverUnloading()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sTmpLog;

	if (!func_TaskMovingCheck())	return;

	if (!func_MovingInterlock())
	{
		return;
	}
	g_bMovingflag = true;
	if (!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		sLangChange.Format("PCB Z axis Wait_Pos Move Failed");
		delayMsg(sLangChange, 1000, M_COLOR_RED);
	}
	if (!motor.Pcb_Tilt_Motor_Move(Holder_Uv_Pos))
	{
		sLangChange.LoadStringA(IDS_STRING1017);	//PCB부 Tx, Ty축 대기 위치 이동 실패
		sTmpLog.Format(sLangChange);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_RED);
		g_bMovingflag = false;
		return;
	}

	if (!motor.Pcb_Motor_Move(Holder_Uv_Pos))
	{
		sLangChange.LoadStringA(IDS_STRING1481);	//PCB부 %s 이동 실패
		sTmpLog.Format(sLangChange, MotorPosName[Holder_Uv_Pos]);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_RED);
		g_bMovingflag = false;
		return;
	}

	g_bMovingflag = false;
}


void CLensDlg::OnBnClickedButtonMotorZCoverUnloading()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!func_TaskMovingCheck())	return;
	if (!checkMotorPos(Holder_Uv_Pos))
	{
		delayMsg("Do not Holder_Uv_Pos", 2000, M_COLOR_RED);
		return;
	}
	g_bMovingflag = true;
	if (!motor.PCB_Z_Motor_Move(Holder_Uv_Pos))
	{
		sLangChange.Format("PCB Z axis Holder_Uv_Pos Move Failed");
		delayMsg(sLangChange, 1000, M_COLOR_RED);
	}

	g_bMovingflag = false;
}


void CLensDlg::OnBnClickedButtonUvCylinderUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}
	if (g_bMovingflag)
	{
		sLangChange.LoadStringA(IDS_STRING1228);	//모터 구동 중 사용 불가..
		delayMsg(sLangChange, 2000, M_COLOR_RED);
		return;
	}
	g_bMovingflag = true;
	Dio.UVCylinder_UPDOWN(true, false);
	g_bMovingflag = false;
}


void CLensDlg::OnBnClickedButtonUvCylinderDown()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}
	if (g_bMovingflag)
	{
		sLangChange.LoadStringA(IDS_STRING1228);	//모터 구동 중 사용 불가..
		delayMsg(sLangChange, 2000, M_COLOR_RED);
		return;
	}
	g_bMovingflag = true;
	Dio.UVCylinder_UPDOWN(false, false);
	g_bMovingflag = false;
}


void CLensDlg::OnBnClickedButtonInspMotorWait()
{
	// TODO: Add your control notification handler code here
	CString sTmpLog;
	if (!func_TaskMovingCheck())	return;
	//if (Dio.UVCylinderCheck(false, false))
	//{
	//	askMsg("[주의!] UV실린더 상승 후 X,Y대기위치 이동 하십시오!");//UV실린더가 하강상태면 X,Y이동 차단. ->UV실린더가 하강하고 있는때는 UV조사하는 순간밖에없다. 
	//	return;
	//}
	/*if( !func_MovingInterlock())
	{
	return;
	}*/
	g_bMovingflag = true;
	//if (!motor.PCB_Z_Motor_Move(Wait_Pos))
	//{
	//	sLangChange.Format("PCB Z axis Wait_Pos Move Failed");
	//	delayMsg(sLangChange, 1000, M_COLOR_RED);
	//}
	if (motor.INSP_Motor_MoveX(Wait_Pos))
	{
		sLangChange.LoadStringA(IDS_STRING1498);	//PCB부 %s 이동 완료
		sTmpLog.Format(sLangChange, MotorPosName[Wait_Pos]);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
	}


	//if (motor.Pcb_Tilt_Motor_Move(Wait_Pos))
	//{
	//	CString sTmpLog;
	//	sLangChange.LoadStringA(IDS_STRING1015);	//PCB부 %s 이동 완료
	//	sTmpLog.Format(sLangChange, MotorPosName[Wait_Pos]);
	//	delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
	//}
	g_bMovingflag = false;
}


void CLensDlg::OnBnClickedButtonInspMotorAlign()
{
	// TODO: Add your control notification handler code here
	if (!func_TaskMovingCheck())	return;
	if (!func_MovingInterlock())
	{
		return;
	}
	g_bMovingflag = true;
	if (!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		sLangChange.Format("PCB Z axis Wait_Pos Move Failed");
		delayMsg(sLangChange, 1000, M_COLOR_RED);
	}
	if (motor.INSP_Motor_MoveX(Align_Pos))
	{
		sLangChange.LoadStringA(IDS_STRING1498);	//insp x %s 이동 실패
		sTempLang.Format(sLangChange, MotorPosName[Align_Pos]);
		delayMsg(sTempLang.GetBuffer(99), 3000, M_COLOR_GREEN);
	}



	g_bMovingflag = false;
}


void CLensDlg::OnBnClickedButtonInspMotorDefectInsp()
{
	// TODO: Add your control notification handler code here
	CString sTmpLog;
	if (!func_TaskMovingCheck())	return;

	g_bMovingflag = true;

	if (!func_MovingInterlock())
	{
		g_bMovingflag = false;
		return;
	}

	if (motor.INSP_Motor_MoveX(OC_6500K_Pos))
	{
		sLangChange.LoadStringA(IDS_STRING1498);	//insp x %s 이동 실패
		sTmpLog.Format(sLangChange, MotorPosName[OC_6500K_Pos]);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
	}
	
	g_bMovingflag = false;
}


void CLensDlg::OnBnClickedButtonInspMotorDarkInsp()
{
	// TODO: Add your control notification handler code here
	CString sTmpLog;
	if (!func_TaskMovingCheck())	return;

	g_bMovingflag = true;

	if (!func_MovingInterlock())	return;

	if (!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		g_bMovingflag = false;
		return;
	}

	if (motor.INSP_Motor_MoveX(Dark_Pos))
	{
		sLangChange.LoadStringA(IDS_STRING1498);	//"PCB %s 이동 완료"
		sTmpLog.Format(sLangChange, MotorPosName[Dark_Pos]);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
	}
	
	g_bMovingflag = false;
}
