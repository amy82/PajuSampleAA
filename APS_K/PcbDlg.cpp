// PcbDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "PcbDlg.h"
#include "afxdialogex.h"

#include "MarkSetDlg.h"
#include "EpoxyDlg.h"


int g_iPBright=0;
int g_iPContrast=0;

// CPcbDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPcbDlg, CDialogEx)

	CPcbDlg::CPcbDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPcbDlg::IDD, pParent)
{
	m_iSelMoveType	= 0;
	m_iSelMotor		= Motor_PCB_TH;
}

CPcbDlg::~CPcbDlg()
{
}

void CPcbDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_POS, m_iSelMoveType);
	DDX_Control(pDX, IDC_LABEL_DISP5, m_labelDisp5);
	DDX_Control(pDX, IDC_LABEL_DISP6, m_labelDisp6);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_BOND, m_btnBondPos);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_BOND2, m_btnBond2Pos);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_PDISPENSE_POS, m_btnPDispensePos);
	DDX_Control(pDX, IDC_BUTTON_Z_MOTOR_PDISPENSE_POS, m_btnPDispenseZPos);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_TDISPENSE_POS, m_btnTDispensePos);
	DDX_Control(pDX, IDC_BUTTON_Z_MOTOR_TDISPENSE_POS, m_btnTDispenseZPos);


	DDX_Control(pDX, IDC_BUTTON_MOTOR_EXPOXY_TARGET_POS, m_btnExpoxyTarget);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_SENSOR_CONTACT_POS, m_btnSensorContact);
	DDX_Control(pDX, IDC_BUTTON_VACCUM_OFF, m_btnVaccumOff);
	DDX_Control(pDX, IDC_BUTTON_VACCUM_ON, m_btnVaccumOn);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_WAIT, m_btnWaitPos);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_HOLDER, m_btnHolderPos);
	DDX_Control(pDX, IDC_BUTTON_Z_MOTOR_HOLDER, m_btnHolderZ);
	//
	DDX_Control(pDX, IDC_BUTTON_GOTO_LENSALIGN, m_btnPCB);
	DDX_Control(pDX, IDC_BUTTON_GOTO_PCBALIGN, m_btnLens);

	DDX_Control(pDX, IDC_BUTTON_GOTO_LENSEDGE_ALIGN, m_btnLensEdge);

	DDX_Control(pDX, IDC_PCB_ALIGN_RESULT, m_labelAlignResult);

	DDX_Control(pDX, IDC_EDIT_CLEAN_POS, m_LabelClean);

	DDX_Control(pDX, IDC_BUTTON_BOX_LEFT, m_btn_BoxLeft);
	DDX_Control(pDX, IDC_BUTTON_BOX_UP, m_btn_BoxUP);
	DDX_Control(pDX, IDC_BUTTON_BOX_RIGHT, m_btn_BoxRight);
	DDX_Control(pDX, IDC_BUTTON_BOX_DOWN, m_btn_BoxDown);
	DDX_Control(pDX, IDC_BUTTON_EPOXY, m_btnEpoxy);

	//
	DDX_Control(pDX, IDC_BUTTON_Z_MOTOR_WAIT, m_btnWaitZ);

	DDX_Control(pDX, IDC_BUTTON_Z_MOTOR_DISPENSE, m_btnDispenseZ);
	DDX_Control(pDX, IDC_BUTTON_LASER_DLG_OPEN, m_btnLaserDlgOpen);
	DDX_Control(pDX, IDC_BUTTON_LASER_MANUAL_SERACH2, m_btnLaserManualStart);

	DDX_Control(pDX, IDC_BUTTON_MOTOR_DISPLACE_IN1, m_btn_LaserIN1);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_DISPLACE_IN2, m_btn_LaserIN2);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_DISPLACE_IN3, m_btn_LaserIN3);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_DISPLACE_IN4, m_btn_LaserIN4);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_LASER_OUT1, m_btn_LaserOUT1);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_LASER_OUT2, m_btn_LaserOUT2);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_LASER_OUT3, m_btn_LaserOUT3);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_LASER_OUT4, m_btn_LaserOUT4);

	DDX_Control(pDX, IDC_BUTTON_MOTOR_ALIGN_LASER_POS, m_btnAlignLaserPos);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_ALIGN_LASER_POS_OUT, m_btnAlignLaserPosOut);

	DDX_Control(pDX, IDC_BUTTON_SENSOR_CONTACT, m_btnSensorContect);
	DDX_Check(pDX, IDC_CHECK_Edge_disp, m_bResinInspDIsp);
	DDX_Control(pDX, IDC_BUTTON_REPOXY, m_btnRepoxy);
	DDX_Control(pDX, IDC_BUTTON_LEPOXY, m_btnLepoxy);
	DDX_Control(pDX, IDC_BUTTON_Z_MOTOR_LDISPENSE, m_btnZldis);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_SENSOR_CONTACT_POS2, m_btnCon2);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_EXPOXY_TARGET_POS2, m_btnTapos2);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_LBOND, m_btnLbond);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_RBOND, m_btnRbond);
	DDX_Control(pDX, IDC_BUTTON_LASER_LIFT_UP, m_btnLaserLiftUp);
	DDX_Control(pDX, IDC_BUTTON_LASER_LIFT_DOWN, m_btnLaserLiftDown);
	DDX_Radio(pDX, IDC_RADIO_CIRCLE, m_radio);
	DDX_Control(pDX, IDC_BUTTON_VACCUM_SOL, m_btnVaccumSol);
	DDX_Control(pDX, IDC_BUTTON_Z_MOTOR_LASER, m_btnLaserZ);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_RESIN_POS, m_btnResinPos);
	DDX_Control(pDX, IDC_BUTTON_MOTOR_SENSOR_CONTACT_ZPOS, m_btnSensorContactZ);

	DDX_Control(pDX, IDC_BUTTON_MOTOR_CONTI_EPOXY, m_btnContiPos);
	DDX_Control(pDX, IDC_BUTTON_Z_MOTOR_CONTI_EPOXY, m_btnContiPosZ);

	DDX_Control(pDX, IDC_BUTTON_LASER_CYL_UP_LASERTAB, m_btn_Laser_CylUp_LaserTab);
	DDX_Control(pDX, IDC_BUTTON_LASER_CYL_DOWN_LASERTAB, m_btn_Laser_CylDown_LaserTab);
	DDX_Control(pDX, IDC_BUTTON_INSP_X_MOTOR_WAIT, m_btnInspXWaitPos);
	DDX_Control(pDX, IDC_BUTTON_INSP_X_MOTOR_HOLDER, m_btnInspXHolderPos);
	DDX_Control(pDX, IDC_BUTTON_INSP_X_MOTOR_BOND, m_btnInspXBondPos);
	DDX_Control(pDX, IDC_BUTTON_INSP_X_MOTOR_PDISPENSE_POS, m_btnInspXPDispensePos);
	DDX_Control(pDX, IDC_BUTTON_INSP_X_MOTOR_TDISPENSE_POS, m_btnInspXTDispensePos);
}


BEGIN_MESSAGE_MAP(CPcbDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CPcbDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CPcbDlg::OnBnClickedCancel)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_LIVEMODE, &CPcbDlg::OnBnClickedButtonLivemode)
	ON_BN_CLICKED(IDC_BUTTON_REGIST, &CPcbDlg::OnBnClickedButtonRegist)
	ON_BN_CLICKED(IDC_BUTTON_FIND, &CPcbDlg::OnBnClickedButtonFind)
	ON_BN_CLICKED(IDC_RADIO_POS, &CPcbDlg::OnBnClickedRadioPos)
	ON_BN_CLICKED(IDC_RADIO_SIZE, &CPcbDlg::OnBnClickedRadioSize)
	ON_BN_CLICKED(IDC_BUTTON_BOX_UP, &CPcbDlg::OnBnClickedButtonBoxUp)
	ON_BN_CLICKED(IDC_BUTTON_BOX_DOWN, &CPcbDlg::OnBnClickedButtonBoxDown)
	ON_BN_CLICKED(IDC_BUTTON_BOX_LEFT, &CPcbDlg::OnBnClickedButtonBoxLeft)
	ON_BN_CLICKED(IDC_BUTTON_BOX_RIGHT, &CPcbDlg::OnBnClickedButtonBoxRight)
	ON_BN_CLICKED(IDC_BUTTON_BOX_SPEED, &CPcbDlg::OnBnClickedButtonBoxSpeed)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_ALIGN, &CPcbDlg::OnBnClickedButtonMotorAlign)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_BOND, &CPcbDlg::OnBnClickedButtonMotorBond)
	ON_BN_CLICKED(IDC_BUTTON_MARKSET, &CPcbDlg::OnBnClickedButtonMarkset)
//	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON_IMG_LOAD, &CPcbDlg::OnBnClickedButtonImgLoad)
	ON_BN_CLICKED(IDC_BUTTON_IMG_SAVE, &CPcbDlg::OnBnClickedButtonImgSave)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_VACCUM_ON, &CPcbDlg::OnBnClickedButtonVaccumOn)
	ON_BN_CLICKED(IDC_BUTTON_VACCUM_OFF, &CPcbDlg::OnBnClickedButtonVaccumOff)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_WAIT, &CPcbDlg::OnBnClickedButtonMotorWait)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_BOND2, &CPcbDlg::OnBnClickedButtonMotorBond2)
	ON_BN_CLICKED(IDC_BUTTON_ALIGN_TEST2, &CPcbDlg::OnBnClickedButtonAlignTest2)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_Menu_COPY, &CPcbDlg::OnMenuCopy)
	ON_COMMAND(ID_Menu_DELETE, &CPcbDlg::OnMenuDelete)
	ON_COMMAND(ID_Menu_PASTE, &CPcbDlg::OnMenuPaste)
	ON_BN_CLICKED(IDC_BUTTON_GOTO_PCBALIGN, &CPcbDlg::OnBnClickedButtonGotoPcbalign)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON_GOTO_LENSEDGE_ALIGN, &CPcbDlg::OnBnClickedButtonGotoLensedgeAlign)
	ON_BN_CLICKED(IDC_BUTTON_GOTO_LENSALIGN, &CPcbDlg::OnBnClickedButtonGotoLensalign)
	ON_BN_CLICKED(IDC_BUTTON_EPOXY, &CPcbDlg::OnBnClickedButtonEpoxy)
	ON_BN_CLICKED(IDC_BUTTON_Z_MOTOR_WAIT, &CPcbDlg::OnBnClickedButtonZMotorWait)
	ON_BN_CLICKED(IDC_BUTTON_Z_MOTOR_DISPENSE, &CPcbDlg::OnBnClickedButtonZMotorDispense)
	ON_BN_CLICKED(IDC_BUTTON_LASER_DLG_OPEN, &CPcbDlg::OnBnClickedButtonLaserDlgOpen)
	ON_BN_CLICKED(IDC_BUTTON_LASER_MANUAL_SERACH2, &CPcbDlg::OnBnClickedButtonLaserManualSerach2)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_DISPLACE_IN1, &CPcbDlg::OnBnClickedButtonMotorDisplaceIn1)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_DISPLACE_IN2, &CPcbDlg::OnBnClickedButtonMotorDisplaceIn2)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_DISPLACE_IN3, &CPcbDlg::OnBnClickedButtonMotorDisplaceIn3)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_DISPLACE_IN4, &CPcbDlg::OnBnClickedButtonMotorDisplaceIn4)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_LASER_OUT1, &CPcbDlg::OnBnClickedButtonMotorLaserOut1)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_LASER_OUT2, &CPcbDlg::OnBnClickedButtonMotorLaserOut2)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_LASER_OUT3, &CPcbDlg::OnBnClickedButtonMotorLaserOut3)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_LASER_OUT4, &CPcbDlg::OnBnClickedButtonMotorLaserOut4)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_ALIGN_LASER_POS, &CPcbDlg::OnBnClickedButtonMotorAlignLaserPos)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_ALIGN_LASER_POS_OUT, &CPcbDlg::OnBnClickedButtonMotorAlignLaserPosOut)
	ON_BN_CLICKED(IDC_BUTTON_SENSOR_CONTACT, &CPcbDlg::OnBnClickedButtonSensorContact)
	ON_BN_CLICKED(IDC_BUTTON_EPOXY_CALC, &CPcbDlg::OnBnClickedButtonEpoxyCalc)
	ON_BN_CLICKED(IDC_BUTTON_FINDBASE_EPOXY, &CPcbDlg::OnBnClickedButtonFindbaseEpoxy)
	ON_BN_CLICKED(IDC_BUTTON_FIND_EPOXY, &CPcbDlg::OnBnClickedButtonFindEpoxy)
	ON_BN_CLICKED(IDC_BUTTON_OFFSET_SAVE, &CPcbDlg::OnBnClickedButtonOffsetSave)
	ON_BN_CLICKED(IDC_BUTTON_EPOXY_INSP1, &CPcbDlg::OnBnClickedButtonEpoxyInsp1)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_SENSOR_CONTACT_POS, &CPcbDlg::OnBnClickedButtonMotorSensorContactPos)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_EXPOXY_TARGET_POS, &CPcbDlg::OnBnClickedButtonMotorExpoxyTargetPos)
	ON_STN_CLICKED(IDC_PCB_ALIGN_RESULT, &CPcbDlg::OnStnClickedPcbAlignResult)
	ON_STN_CLICKED(IDC_EDIT_CLEAN_POS, &CPcbDlg::OnStnClickedEditCleanPos)
	ON_BN_CLICKED(IDC_BUTTON_CHOICE_EPOXY, &CPcbDlg::OnBnClickedButtonChoiceEpoxy)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_LBOND, &CPcbDlg::OnBnClickedButtonMotorLbond)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_RBOND, &CPcbDlg::OnBnClickedButtonMotorRbond)
	ON_BN_CLICKED(IDC_BUTTON_Z_MOTOR_LDISPENSE, &CPcbDlg::OnBnClickedButtonZMotorLdispense)
	ON_BN_CLICKED(IDC_BUTTON_LEPOXY, &CPcbDlg::OnBnClickedButtonLepoxy)
	ON_BN_CLICKED(IDC_BUTTON_REPOXY, &CPcbDlg::OnBnClickedButtonRepoxy)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_SENSOR_CONTACT_POS2, &CPcbDlg::OnBnClickedButtonMotorSensorContactPos2)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_EXPOXY_TARGET_POS2, &CPcbDlg::OnBnClickedButtonMotorExpoxyTargetPos2)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_CIRCLE, IDC_RADIO_LINE, RadioCtrl)
	ON_BN_CLICKED(IDC_BUTTON_ECAL_SAVE, &CPcbDlg::OnBnClickedButtonEcalSave)
	ON_BN_CLICKED(IDC_BUTTON_LASER_LIFT_UP, &CPcbDlg::OnBnClickedButtonLaserLiftUp)
	ON_BN_CLICKED(IDC_BUTTON_LASER_LIFT_DOWN, &CPcbDlg::OnBnClickedButtonLaserLiftDown)
	ON_BN_CLICKED(IDC_BUTTON_VACCUM_SOL, &CPcbDlg::OnBnClickedButtonVaccumSol)
	ON_BN_CLICKED(IDC_BUTTON_Z_MOTOR_LASER, &CPcbDlg::OnBnClickedButtonZMotorLaser)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_RESIN_POS, &CPcbDlg::OnBnClickedButtonMotorResinPos)
	ON_EN_CHANGE(IDC_EDIT_OFFSET_X, &CPcbDlg::OnEnChangeEditOffsetX)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_EXPOXY_TARGET_Z2, &CPcbDlg::OnBnClickedButtonMotorExpoxyTargetZ)
	ON_BN_CLICKED(IDC_BUTTON_EPOXY_ROI, &CPcbDlg::OnBnClickedButtonEpoxyRoi)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_SENSOR_CONTACT_ZPOS, &CPcbDlg::OnBnClickedButtonMotorSensorContactZpos)
	ON_BN_CLICKED(IDC_BUTTON_Z_MOTOR_HOLDER, &CPcbDlg::OnBnClickedButtonZMotorHolder)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_HOLDER, &CPcbDlg::OnBnClickedButtonMotorHolder)
	ON_BN_CLICKED(IDC_BUTTON_EPOXY_ROI_VIEW, &CPcbDlg::OnBnClickedButtonEpoxyRoiView)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_CONTI_EPOXY, &CPcbDlg::OnBnClickedButtonMotorContiEpoxy)
	ON_BN_CLICKED(IDC_BUTTON_Z_MOTOR_CONTI_EPOXY, &CPcbDlg::OnBnClickedButtonZMotorContiEpoxy)
	ON_BN_CLICKED(IDC_BUTTON_SMALL_EPOXY, &CPcbDlg::OnBnClickedButtonSmallEpoxy)
	ON_EN_CHANGE(IDC_EDIT_OFFSET_Y, &CPcbDlg::OnEnChangeEditOffsetY)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_PDISPENSE_POS, &CPcbDlg::OnBnClickedButtonMotorPdispensePos)
	ON_BN_CLICKED(IDC_BUTTON_Z_MOTOR_PDISPENSE_POS, &CPcbDlg::OnBnClickedButtonZMotorPdispensePos)
	ON_BN_CLICKED(IDC_BUTTON_LASER_CYL_UP_LASERTAB, &CPcbDlg::OnBnClickedButtonLaserCylUpLasertab)
	ON_BN_CLICKED(IDC_BUTTON_LASER_CYL_DOWN_LASERTAB, &CPcbDlg::OnBnClickedButtonLaserCylDownLasertab)
	ON_BN_CLICKED(IDC_BUTTON_SMALL_CIRCLE_EPOXY, &CPcbDlg::OnBnClickedButtonSmallCircleEpoxy)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_TDISPENSE_POS, &CPcbDlg::OnBnClickedButtonMotorTdispensePos)
	ON_BN_CLICKED(IDC_BUTTON_Z_MOTOR_TDISPENSE_POS, &CPcbDlg::OnBnClickedButtonZMotorTdispensePos)
	ON_BN_CLICKED(IDC_BUTTON_INSP_X_MOTOR_WAIT, &CPcbDlg::OnBnClickedButtonInspXMotorWait)
	ON_BN_CLICKED(IDC_BUTTON_INSP_X_MOTOR_HOLDER, &CPcbDlg::OnBnClickedButtonInspXMotorHolder)
	ON_BN_CLICKED(IDC_BUTTON_INSP_X_MOTOR_BOND, &CPcbDlg::OnBnClickedButtonInspXMotorBond)
	ON_BN_CLICKED(IDC_BUTTON_INSP_X_MOTOR_PDISPENSE_POS, &CPcbDlg::OnBnClickedButtonInspXMotorPdispensePos)
	ON_BN_CLICKED(IDC_BUTTON_INSP_X_MOTOR_TDISPENSE_POS, &CPcbDlg::OnBnClickedButtonInspXMotorTdispensePos)
	ON_BN_CLICKED(IDC_BUTTON_EPOXY_WEIGHT, &CPcbDlg::OnBnClickedButtonEpoxyWeight)
END_MESSAGE_MAP()


// CPcbDlg 메시지 처리기입니다.
BOOL CPcbDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//sysData.Load();
	setInterface();
	//DigLedputData(PCB_Holder_MARK);
	CButton* pButton = (CButton*)GetDlgItem(IDC_RADIO_CIRCLE);
	CButton* pButton2 = (CButton*)GetDlgItem(IDC_RADIO_LINE);
	pButton->SetCheck(TRUE); 
	m_radio = 0;
	m_vacuumsol = 0;




	return TRUE;  // return TRUE unless you set the focus to a control
	 //예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CPcbDlg::OnBnClickedOk(){}
void CPcbDlg::OnBnClickedCancel(){}


void CPcbDlg::setInterface()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	WINDOWPLACEMENT wndpl;
	this->GetWindowPlacement(&wndpl);

	wndpl.rcNormalPosition = pFrame->m_rectCamDispPos2;
	wndpl.rcNormalPosition.left = pFrame->m_rectCamDispPos2.left - 10;
	wndpl.rcNormalPosition.right = pFrame->m_rectCamDispPos2.right + 100;
	wndpl.rcNormalPosition.top -= SUB_DLG_OFFSET_Y - 10;
	wndpl.rcNormalPosition.bottom = MAIN_DLG_SIZE_Y - 5 - 90;
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

	m_btnPCB.m_iStateBtn  =1;
	m_btnPCB.Invalidate();

#if (____AA_WAY == LENS_TILT_AA)
	GetDlgItem(IDC_BUTTON_LASER_LIFT_UP)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_LASER_LIFT_DOWN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_MOTOR_CONTI_EPOXY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_Z_MOTOR_CONTI_EPOXY)->ShowWindow(SW_HIDE);
	//
	//
#endif


	GetDlgItem(IDC_BUTTON_MOTOR_PDISPENSE_POS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_Z_MOTOR_PDISPENSE_POS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_MOTOR_TDISPENSE_POS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_Z_MOTOR_TDISPENSE_POS)->ShowWindow(SW_HIDE);
	
	GetDlgItem(IDC_BUTTON_SMALL_EPOXY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_SMALL)->ShowWindow(SW_HIDE);

	



	/*GetDlgItem(IDC_STATIC_INSP_X)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_INSP_X_MOTOR_WAIT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_INSP_X_MOTOR_HOLDER)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_INSP_X_MOTOR_BOND)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_INSP_X_MOTOR_PDISPENSE_POS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_INSP_X_MOTOR_TDISPENSE_POS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_LASER_CYL_UP_LASERTAB)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_LASER_CYL_DOWN_LASERTAB)->ShowWindow(SW_HIDE);*/
}


void CPcbDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow)
	{
		if (sysData.m_iProductComp == 1)
		{
			//
			GetDlgItem(IDC_EDIT_Contrast2)->SetWindowTextA("완제품 변위 측정 위치 이동");
		}
		else
		{
			GetDlgItem(IDC_EDIT_Contrast2)->SetWindowTextA("AA 변위 측정 위치 이동");
		}
		
		if (Task.AutoFlag == 0) {
			LightControl.ctrlLedVolume(LIGHT_PCB, model.m_iLedValue[LEDDATA_HOLDER]);
		}
		if(m_radio == 0)
		{
			m_dOffsetX = model.m_dEpoxyOffsetX;
			m_dOffsetY = model.m_dEpoxyOffsetY;
		}
		else if(m_radio == 1)
		{
			m_dOffsetX = model.m_dEpoxy2OffsetX;
			m_dOffsetY = model.m_dEpoxy2OffsetY;
		}
		PutEpoxyDataOnEdit();

		/* Grid */
		initMarkGrid();

		ctrlLiveButton();
		#ifdef ON_LINE_VISION
		dispMarkImage();
		#endif
		dispData();
		//DigLedputData(PCB_Holder_MARK);
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


void CPcbDlg::dispData()
{
	/*CString tmpStr;

	tmpStr.Format("%d", model.m_iLimitRate[PCB_Holder_MARK][0]);
	m_gridMark.SetTextMatrix(1, 1, tmpStr);

	tmpStr.Format("%d", model.m_iLimitRate[PCB_Holder_MARK][1]);
	m_gridMark.SetTextMatrix(1, 2, tmpStr);*/

}


void CPcbDlg::getData()
{
	/*CString strTemp;
	strTemp = m_gridMark.GetTextMatrix(1, 1);
	model.m_iLimitRate[PCB_Holder_MARK][0] = atoi(strTemp);

	strTemp = m_gridMark.GetTextMatrix(1, 2);
	model.m_iLimitRate[PCB_Holder_MARK][1] = atoi(strTemp);*/
}


void CPcbDlg::initMarkGrid()
{
	//CString strTemp;

	//m_gridMark.SetRows(2);
	//m_gridMark.SetCols(3);

	//m_gridMark.SetColAlignment(0, 4);
	//m_gridMark.SetColAlignment(1, 4);
	//m_gridMark.SetColAlignment(2, 4);

	//m_gridMark.SetColWidth(0,1200);//1450
	//m_gridMark.SetColWidth(1,950);//2350
	//m_gridMark.SetColWidth(2,950);//2350

	//sLangChange.LoadStringA(IDS_STRING761);	//Mark #1
	//m_gridMark.SetTextMatrix(0, 1, sLangChange);
	//sLangChange.LoadStringA(IDS_STRING762);	//Mark #2
	//m_gridMark.SetTextMatrix(0, 2, sLangChange);

	//sLangChange.LoadStringA(IDS_STRING767);	//Matching(%)
	//m_gridMark.SetTextMatrix(1, 0, sLangChange);

	//m_gridMark.SetRowHeight(1, 510);
}


void CPcbDlg::ctrlLiveButton()
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

void CPcbDlg::OnBnClickedButtonLivemode()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	
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

void CPcbDlg::getMarkSize()
{
	m_iMarkSizeX = m_rMarkBox.right - m_rMarkBox.left;
	m_iMarkSizeY = m_rMarkBox.bottom - m_rMarkBox.top;
}

void CPcbDlg::OnBnClickedButtonRegist()
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

	bool bRtn = vision.markRegist(CAM1, PCB_Holder_MARK, m_iMarkNo, m_rMarkBox);

	if (!bRtn)
	{
		sLangChange.LoadStringA(IDS_STRING1466);	//마크등록 실패.
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


void CPcbDlg::OnBnClickedButtonFind()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	int iMarkNo = 0;
	CString sTemp="";

	vision.clearOverlay(CAM1);

	if(vision.getLiveMode())
	{
		vision.getSnapImage(CAM1);
		vision.setLiveMode(true);
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


void CPcbDlg::OnBnClickedRadioPos()
{
	UpdateData(true);
}


void CPcbDlg::OnBnClickedRadioSize()
{
	UpdateData(true);
}


void CPcbDlg::OnBnClickedButtonBoxUp()
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


void CPcbDlg::OnBnClickedButtonBoxDown()
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


void CPcbDlg::OnBnClickedButtonBoxLeft()
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


void CPcbDlg::OnBnClickedButtonBoxRight()
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


void CPcbDlg::OnBnClickedButtonBoxSpeed()
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


void CPcbDlg::dispMarkImage()
{
	double dZoomX, dZoomY;

	for (int i=0 ; i<2 ; i++)
	{
#ifdef ON_LINE_VISION
		MbufClear(vision.MilMarkImage[PCB_Holder_MARK][i], 0);
		MbufClear(vision.MilMarkSmallImage[PCB_Holder_MARK][i], 0);
#endif

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

void CPcbDlg::OnBnClickedButtonMarkset()
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



void CPcbDlg::OnBnClickedButtonImgLoad()
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


void CPcbDlg::OnBnClickedButtonImgSave()
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


void CPcbDlg::clickedMarkDisp(int iMarkNo)
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

void CPcbDlg::OnLButtonDown(UINT nFlags, CPoint point)
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



void CPcbDlg::OnBnClickedButtonVaccumOn()
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


void CPcbDlg::OnBnClickedButtonVaccumOff()
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


BEGIN_EVENTSINK_MAP(CPcbDlg, CDialogEx)
END_EVENTSINK_MAP()




void CPcbDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent==PCB_TIMER)
	{
		if (!timerRunFlag)
		{
			timerRunFlag = true;

			changeColorMotorPosBtn();
			changeColorLaserBtn();

			timerRunFlag = false;
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CPcbDlg::OnBnClickedButtonAlignTest2()
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
	if(!_finite(offsetX)){offsetX=0;}
	if(!_finite(offsetY)){offsetY=0;}
	if(!_finite(offsetTh)){offsetTh=0;} 
	if (iRtn == 0) 
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

			pos[0]	= motor.GetCommandPos(Motor_PCB_X)	- offsetX;
			pos[1]	= motor.GetCommandPos(Motor_PCB_Y)	- offsetY;
			//pos[2]	= motor.GetCommandPos(Motor_PCB_TH)	+ offsetTh;
			pos[2] = motor.GetCommandPos(Motor_PCB_TH) - offsetTh;

			

			motor.goMotorPos(3, axis, pos);
			sLangChange.LoadStringA(IDS_STRING1261);	//보정 이동 완료.
			delayMsg(sLangChange, 3000, M_COLOR_GREEN);
			Sleep(10);

			pos[0]	= (pos[0] - model.axis[Motor_PCB_X].pos[Holder_Pos]);
			pos[1]	= (pos[1] - model.axis[Motor_PCB_Y].pos[Holder_Pos]);
			pos[2]	= (pos[2] - model.axis[Motor_PCB_TH].pos[Holder_Pos]);//0.0;

			CString sTemp;
			sLangChange.LoadStringA(IDS_STRING1482);	//보정값 : %.3lf %.3lf %.3lf
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

	CString sLog;
	sLangChange.LoadStringA(IDS_STRING1467);	//PCB Align 보정값 X:%.03f, Y:%.03f, Θ:%.04f
	sLog.Format(sLangChange, offsetX, offsetY, offsetTh);
	pFrame->putListLog(sLog);

	pFrame->m_rBox.left = 0;
	pFrame->m_rBox.top = 0;
	pFrame->m_rBox.right = 0;
	pFrame->m_rBox.bottom = 0;
}


void CPcbDlg::OnBnClickedButtonMotorWait()
{
	CString sTmpLog;
	if( !func_TaskMovingCheck() )	return;

	/* 이동중이면 Return */
	if( !func_MovingInterlock())
	{
		return;
	}
	g_bMovingflag =true;
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

void CPcbDlg::OnBnClickedButtonMotorAlign()
{

}

void CPcbDlg::OnBnClickedButtonMotorBond()
{
	if( !func_TaskMovingCheck() )	return;

	/* 이동중이면 Return */
	if( !func_MovingInterlock())
	{
		return;
	}
	g_bMovingflag =true;
	CString sTmpLog="";
	if(!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		sLangChange.Format("PCB Z axis Wait_Pos Move Failed");
		delayMsg(sLangChange, 1000, M_COLOR_RED);
	}

	if(!motor.Pcb_Motor_Move(Dispense_Pos,Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]))
	{
		sLangChange.LoadStringA(IDS_STRING898);	//"PCB %s 이동 실패"
		sTmpLog.Format(sLangChange, MotorPosName[Dispense_Pos]);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_RED);
	}

	sLangChange.LoadStringA(IDS_STRING899);	//"PCB %s 이동 완료"
	sTmpLog.Format(sLangChange, MotorPosName[Dispense_Pos]);
	delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
	g_bMovingflag =false;
}

void CPcbDlg::OnBnClickedButtonMotorBond2()
{
	if( !func_TaskMovingCheck() )	return;

	/* 이동중이면 Return */
	g_bMovingflag =true;

	//if( !Dio.PCBDarkCheck(true, false) )
	//{//Dark 검사 실린더 하강일 경우 상승
	//	if( !Dio.PCBDark(true, true) )
	//	{
	//		sLangChange.LoadStringA(IDS_STRING488);	//Dark검사 실린더 상승 실패.
	//		delayMsg(sLangChange, 1000, M_COLOR_RED);
	//		g_bMovingflag =false;
	//		return;
	//	}
	//}

	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	
	if(!motor.LENS_Z_Motor_Move(Wait_Pos))
	{
		sLangChange.LoadStringA(IDS_STRING739);	//Lens_Z축 대기위치 이동 실패.
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		g_bMovingflag =false;
		return;
	}
	if(!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		sLangChange.LoadStringA(IDS_STRING1012);	//PCB_Z축 대기위치 이동 실패.
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		g_bMovingflag =false;
		return;
	}
	//if(!motor.Laser_Z_Motor_Move(Wait_Pos))
	//{
	//	sLangChange.LoadStringA(IDS_STRING641);	//Laser_Z축 대기위치 이동 실패
	//	delayMsg(sLangChange, 1000, M_COLOR_RED);
	//	g_bMovingflag =false;
	//	return;
	//}


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
			pos[0]	= (motor.GetCommandPos(Motor_PCB_X) - model.axis[Motor_PCB_X].pos[Align_Pos])	- offsetX;
			pos[1]	= (motor.GetCommandPos(Motor_PCB_Y) - model.axis[Motor_PCB_Y].pos[Align_Pos])	- offsetY;
			pos[2]	= (motor.GetCommandPos(Motor_PCB_TH) - model.axis[Motor_PCB_TH].pos[Align_Pos])	+ offsetTh;

			CString sTemp;
			sLangChange.LoadStringA(IDS_STRING1482);	//보정값 : %.3lf %.3lf %.3lf
			sTemp.Format(sLangChange, pos[0], pos[1], pos[2]);
			m_labelAlignResult.SetText(sTemp);
			m_labelAlignResult.Invalidate();

			if(	motor.Pcb_Motor_Move(Dispense_Pos, pos[0], pos[1], pos[2]))
			{
				CString sTmpLog;
				sLangChange.LoadStringA(IDS_STRING1015);	//PCB부 %s 이동 완료
				sTmpLog.Format(sLangChange, MotorPosName[Dispense_Pos]);
				delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
			}
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



void CPcbDlg::OnContextMenu(CWnd* pWnd, CPoint point)
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

void CPcbDlg::OnMenuCopy()
{
	m_bCopyFlag = true;

	m_iCopyMarkNo = m_iMarkNo;
}

void CPcbDlg::OnMenuDelete()
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

	sDelFile.Format("%s\\%s\\Data\\Mark\\%s\\PCB_Mark_%d.mod", AA_MODEL_LOAD_DIR, model.mCurModelName, m_iMarkNo);
#else
	MpatFree(vision.PatModel[PCB_Holder_MARK][m_iMarkNo]);
	vision.PatModel[PCB_Holder_MARK][m_iMarkNo] = M_NULL;

	sDelFile.Format("%s\\Model\\%s\\PCB_Mark_%d.pat", DATA_DIR, model.mCurModelName, m_iMarkNo);
#endif

	::DeleteFile(sDelFile);

	model.Save();
	//	model.Load();

	dispMarkImage();
}


void CPcbDlg::OnMenuPaste()
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
	sScr.Format("%s\\%s\\Data\\Mark\\PCB_Mark_%d.mod", AA_MODEL_LOAD_DIR, model.mCurModelName, m_iCopyMarkNo);
	sDes.Format("%s\\%s\\Data\\Mark\\PCB_Mark_%d.mod", AA_MODEL_LOAD_DIR, model.mCurModelName, m_iMarkNo);
#else
	sScr.Format("%s\\%s\\Data\\Mark\\PCB_Mark_%d.pat", AA_MODEL_LOAD_DIR, model.mCurModelName, m_iCopyMarkNo);
	sDes.Format("%s\\%s\\Data\\Mark\\PCB_Mark_%d.pat", AA_MODEL_LOAD_DIR, model.mCurModelName, m_iMarkNo);
#endif

	::CopyFile(sScr, sDes, FALSE);

	model.loadMark(CAM1, PCB_Holder_MARK, m_iMarkNo);
	model.Save();

	vision.geometricMarkPreProc(CAM1, PCB_Holder_MARK, m_iMarkNo);

	dispMarkImage();
}


void CPcbDlg::changeColorVaccumBtn()
{
	//int moduleNo = 2;
	//int channelNo = 3;

	//bool bOutVaccumFlag, bOutBlowFlag, bInVaccumOnFlag;			// 둘 다 OFF 시 흡착, Vaccum만 살면 탈착

	//bInVaccumOnFlag = Dio.PCBvaccumOnCheck(true, false);


	//bOutVaccumFlag = (curOutDioByte[moduleNo][channelNo] & DIO_OUT_PCB_VACUUM) ? true : false;
	//bOutBlowFlag = (curOutDioByte[moduleNo][channelNo] & DIO_OUT_PCB_VACUUM_OFF) ? true : false;


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


	/*if (bOutVaccumFlag)
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
	m_btnVaccumOff.Invalidate();*/
}
bool CPcbDlg::checkCurLensMotorPos(int iPos)
{
	double dCurPos;
	double dMotorPos;

	for (int i=Motor_Lens_X ; i<=Motor_Lens_Y; i++)
	{
		dCurPos		= motor.GetEncoderPos(i);	//motor.GetCommandPos(i);
		dMotorPos	= model.axis[i].pos[iPos];
		if(iPos== Laser_Lens_Pos)
		{
			if (i==6)		dMotorPos	= model.axis[i].pos[Laser_Lens_Pos];
			else if (i==7)	dMotorPos	= model.axis[i].pos[Laser_Lens_Pos];
			if (fabs(dMotorPos-dCurPos) > (fabs(model.m_OutPos_Y[1])+5)){return false;}	//레이저 위치에서만 레이저실린더 하강 가능하게....레이저
		}else
		{
			if (fabs(dMotorPos-dCurPos) > 0.01)
			return false;
		}
		
	}

	return true;
}
bool CPcbDlg::checkCurInspXMotorPos(int iPos)
{

	return true;
}
bool CPcbDlg::checkCurMotorPos(int iPos)
{
	double dCurPos;
	double dMotorPos;
	for (int i=Motor_PCB_X ; i<=Motor_PCB_TH; i++)
	{
		if (i == Motor_PCB_Z)continue;
		if (MOTOR_TYPE[i] == STEPING)
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
			if (i== Motor_PCB_X)		dMotorPos	= model.axis[i].pos[Bonding_Pos] + Task.d_Align_offset_x[PCB_Holder_MARK];
			else if (i== Motor_PCB_Y)	dMotorPos	= model.axis[i].pos[Bonding_Pos] + Task.d_Align_offset_y[PCB_Holder_MARK];
			else if (i== Motor_PCB_TH)	dMotorPos	= model.axis[i].pos[Bonding_Pos] + Task.d_Align_offset_th[PCB_Holder_MARK];
		}
		else if(iPos==Dispense_Pos)
		{
			if (i== Motor_PCB_X)		dMotorPos	= model.axis[i].pos[Dispense_Pos] + Task.d_Align_offset_x[PCB_Chip_MARK];
			else if (i== Motor_PCB_Y)	dMotorPos	= model.axis[i].pos[Dispense_Pos] + Task.d_Align_offset_y[PCB_Chip_MARK];
			else if (i== Motor_PCB_TH)	dMotorPos	= model.axis[i].pos[Dispense_Pos] + Task.d_Align_offset_th[PCB_Chip_MARK];
		}
		else if(iPos==Clean_Pos)
		{
			if (i== Motor_PCB_X)		dMotorPos	= model.axis[i].pos[Clean_Pos];
			else if (i== Motor_PCB_Y)	dMotorPos	= model.axis[i].pos[Clean_Pos];
			else if (i== Motor_PCB_TH)	dMotorPos	= model.axis[i].pos[Clean_Pos];
		}
		else if (iPos == CompleteAlign_Pos)
		{
			if (i == Motor_PCB_X)		dMotorPos = model.axis[i].pos[CompleteAlign_Pos];
			else if (i == Motor_PCB_Y)	dMotorPos = model.axis[i].pos[CompleteAlign_Pos];
			else if (i == Motor_PCB_TH)	dMotorPos = model.axis[i].pos[CompleteAlign_Pos];
		}
		else if (iPos == Com_Laser_Pos)
		{
			if (i == Motor_PCB_X)		dMotorPos = model.axis[i].pos[Com_Laser_Pos] + Task.d_Align_offset_x[PCB_Chip_MARK];
			else if (i == Motor_PCB_Y)	dMotorPos = model.axis[i].pos[Com_Laser_Pos] + Task.d_Align_offset_y[PCB_Chip_MARK];
			else if (i == Motor_PCB_TH)	dMotorPos = model.axis[i].pos[Com_Laser_Pos] + Task.d_Align_offset_th[PCB_Chip_MARK];
		}
		else if(iPos== Laser_Lens_Pos)
		{
			if (i== Motor_PCB_X)		dMotorPos	= model.axis[i].pos[Laser_Lens_Pos];
			else if (i== Motor_PCB_Y)	dMotorPos	= model.axis[i].pos[Laser_Lens_Pos];
			else if (i== Motor_PCB_TH)	dMotorPos	= model.axis[i].pos[Laser_Lens_Pos];
			if (fabs(dMotorPos-dCurPos) > (fabs(model.m_OutPos_Y[1])+3)){return false;}	//레이저 위치에서만 레이저실린더 하강 가능하게....레이저
		}else
		{
			if (fabs(dMotorPos-dCurPos) > 0.01){return false;}
			
		}
		if (fabs(dMotorPos - dCurPos) > 0.01) { return false; }
	}

	return true;
}

bool CPcbDlg::checkCurMotorPosZ(int iPos)
{	/* 모터 위치 확인 */
	double dCurPos;
	double dMotorPos;

	
	dCurPos		= motor.GetEncoderPos(Motor_PCB_Z);	//motor.GetCommandPos(i);
	dMotorPos	= model.axis[Motor_PCB_Z].pos[iPos];

	if (fabs(dMotorPos-dCurPos) > 0.01)
		return false;

	return true;
}

void CPcbDlg::changeColorMotorPosBtn()
{
	int iIndex = - 1;

	if (checkCurMotorPos(Wait_Pos))							iIndex = 0;
	else if (checkCurMotorPos(Holder_Pos))					iIndex = 2;
	else if (checkCurMotorPos(Dispense_Pos))				iIndex = 3;
	else if (checkCurMotorPos(Contact_Pos))					iIndex = 4;
	else if (checkCurMotorPos(Calc_Pos))					iIndex = 5;
	else if (checkCurMotorPos(Align_Pos))					iIndex = 6;
	else if (checkCurMotorPos(CompleteAlign_Pos))			iIndex = 7;
	else if (checkCurMotorPos(Clean_Pos))					iIndex = 10;
	else if (checkCurMotorPos(Com_Laser_Pos))				iIndex = 11;
	else if (checkCurMotorPos(PDispense_Pos))				iIndex = 12;


	m_btnWaitPos.m_iStateBtn = 0;
	m_btnHolderPos.m_iStateBtn =0;
	m_btnBondPos.m_iStateBtn = 0;
	m_btnExpoxyTarget.m_iStateBtn = 0;
	m_btnSensorContact.m_iStateBtn = 0;
	m_btnResinPos.m_iStateBtn = 0;
	m_btnContiPos.m_iStateBtn = 0;
	m_btnPDispensePos.m_iStateBtn = 0;
	//
	
	if (iIndex==0)			m_btnWaitPos.m_iStateBtn = 3;
	else if (iIndex==2)		m_btnHolderPos.m_iStateBtn = 3;
	else if (iIndex==3)		m_btnBondPos.m_iStateBtn = 3;
	else if (iIndex==4)		m_btnSensorContact.m_iStateBtn = 3;
	else if (iIndex == 5)		m_btnExpoxyTarget.m_iStateBtn = 3;
	else if (iIndex == 11)		m_btnContiPos.m_iStateBtn = 3;
	else if (iIndex == 12)		m_btnPDispensePos.m_iStateBtn = 3;
	
	m_btnWaitPos.Invalidate();
	m_btnHolderPos.Invalidate();
	m_btnBondPos.Invalidate();
	m_btnSensorContact.Invalidate();
	m_btnExpoxyTarget.Invalidate();
	m_btnResinPos.Invalidate();
	m_btnContiPos.Invalidate();
	m_btnPDispensePos.Invalidate();

	//-- Z축 표시
	iIndex = - 1;

	if (checkCurMotorPosZ(Wait_Pos))
	{
		iIndex = 0;
	}
	else if (checkCurMotorPosZ(Dispense_Pos))
	{
		iIndex = 1;
	}
	else if (checkCurMotorPosZ(Clean_Pos))
	{
		iIndex = 3;
	}
	else if (checkCurMotorPosZ(Contact_Pos))
	{
		iIndex = 4;
	}
	else if (checkCurMotorPosZ(CompleteAlign_Pos))
	{
		iIndex = 5;
	}
	else if (checkCurMotorPosZ(Holder_Pos))
	{
		iIndex = 6;
	}
	else if (checkCurMotorPosZ(Com_Laser_Pos))
	{
		iIndex = 7;
	}
	else if (checkCurMotorPosZ(PDispense_Pos))
	{
		iIndex = 8;
	}
	//

	m_btnWaitZ.m_iStateBtn = 0;
	m_btnDispenseZ.m_iStateBtn = 0;
	m_btnLaserZ.m_iStateBtn = 0;
	m_btnSensorContactZ.m_iStateBtn = 0;
	m_btnHolderZ.m_iStateBtn  = 0;
	m_btnContiPosZ.m_iStateBtn = 0;
	m_btnPDispenseZPos.m_iStateBtn = 0;
	//
	//
	if (iIndex==0)			m_btnWaitZ.m_iStateBtn = 3;
	else if (iIndex==1)		m_btnDispenseZ.m_iStateBtn = 3;
	else if (iIndex==2)		m_btnLaserZ.m_iStateBtn = 3;
	else if (iIndex==4)		m_btnSensorContactZ.m_iStateBtn = 3;
	else if (iIndex == 6)	    m_btnHolderZ.m_iStateBtn = 3;
	else if (iIndex == 7)	    m_btnContiPosZ.m_iStateBtn = 3;
	else if (iIndex == 8)	    m_btnPDispenseZPos.m_iStateBtn = 3;

	
	m_btnWaitZ.Invalidate();
	m_btnHolderZ.Invalidate();
	m_btnDispenseZ.Invalidate();
	m_btnLaserZ.Invalidate();
	m_btnSensorContactZ.Invalidate();
	m_btnContiPosZ.Invalidate();
	m_btnPDispenseZPos.Invalidate();

}

void CPcbDlg::OnBnClickedButtonGotoPcbalign()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	pFrame->m_bIsLensMode = 0;
	pFrame->ctrlSubDlg(LENS_DLG);

	//DigLedputData(PCB_Chip_MARK);
}

void CPcbDlg::DigLedputData(int iMark)
{

}

void CPcbDlg::OnBnClickedButtonGotoLensedgeAlign()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	pFrame->m_bIsLensMode = 2;
	pFrame->ctrlSubDlg(LENS_EDGE_DLG);

	//DigLedputData(LENS_Align_MARK);
}


void CPcbDlg::OnBnClickedButtonGotoLensalign()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CPcbDlg::OnBnClickedButtonEpoxy()
{
	CString logStr = "";
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

	if ( !checkCurMotorPos(Dispense_Pos) )
	{
		sLangChange.LoadStringA(IDS_STRING542);	//Epoxy 기준위치 이동 후 진행하세요.
		delayMsg(sLangChange, 2000, M_COLOR_RED);
		return;
	}

	/* 이동중이면 Return */
	if(g_bMovingflag)		return;
	g_bMovingflag =true;

	if(!motor.PCB_Z_Motor_Move(Dispense_Pos))
	{
		g_bMovingflag =false;
		return;
	}

	model.Load();
 
	theApp.MainDlg->MainEpoxyRun();


	return;

}


void CPcbDlg::OnBnClickedButtonZMotorWait()
{
	if( !func_TaskMovingCheck() )	return;

	/* 이동중이면 Return */
	g_bMovingflag =true;

	if(!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		sLangChange.Format("PCB Z axis Wait_Pos Move Failed");
		delayMsg(sLangChange, 1000, M_COLOR_RED);
	}

	g_bMovingflag =false;
}


void CPcbDlg::OnBnClickedButtonZMotorDispense()
{
	if( !func_TaskMovingCheck() )	return;

	/* 이동중이면 Return */

	if ( !checkCurMotorPos(Dispense_Pos) )
	{
		delayMsg("Do not Dispense_Pos", 2000, M_COLOR_RED);
		return;
	}
	g_bMovingflag =true;

	if(!motor.PCB_Z_Motor_Move(Dispense_Pos))
	{
		sLangChange.Format("PCB Z axis Dispense_Pos Move Failed");
		delayMsg(sLangChange, 1000, M_COLOR_RED);
	}
	g_bMovingflag =false;
}

void CPcbDlg::OnBnClickedButtonLaserDlgOpen()
{
	/*if (m_pDisplacementDlg->IsWindowVisible())
		m_pDisplacementDlg->ShowWindow(false);
	else
		m_pDisplacementDlg->ShowWindow(true);*/
}


void CPcbDlg::OnBnClickedButtonLaserManualSerach2()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	double dVel;
	//Keyence.func_CL3000_Scan(dVel);
	
	Keyence.func_LT9030_Scan(dVel);

	CString sLog;
	sLangChange.LoadStringA(IDS_STRING635);	//Laser 수동 측정 값(mm) : %lf
	sLog.Format(sLangChange, dVel);
	pFrame->putListLog(sLog);
	//레이저 설정창 보이기
	//GetDlgItem(IDC_BUTTON_LASER_DLG_OPEN)->ShowWindow(SW_SHOW);
}

bool CPcbDlg::func_TaskMovingCheck()
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

bool CPcbDlg::func_MovingInterlock()
{
	if( !checkCurMotorPosZ(Wait_Pos) )
	{
		delayMsg("PCB Wait_Pos Z위치가 아닙니다", 1000, M_COLOR_RED);
		return false;
	}
	return true;
}
void CPcbDlg::OnBnClickedButtonMotorDisplaceIn1()
{
	if( !func_TaskMovingCheck() )	return;

	/* 이동중이면 Return */
	g_bMovingflag =true;

	if(!motor.LENS_Z_Motor_Move(Wait_Pos))
	{
		g_bMovingflag =false;
		return;
	}
	if(!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		g_bMovingflag =false;
		return;
	}
	//if(!motor.Laser_Z_Motor_Move(Wait_Pos))
	//{
	//	g_bMovingflag =false;
	//	return;
	//}

	//if( motor.Pcb_Motor_Move_Laser(0) )
	//{
	//	if(motor.Laser_Z_Motor_Move(Laser_In_Pos))
	//	{
	//		CString sTmpLog;
	//		sLangChange.LoadStringA(IDS_STRING1021);
	//		sTmpLog.Format(sLangChange);	//PCB부 내부 Laser 변위 측정 1차위치 이동 완료
	//		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
	//	}
	//}

	g_bMovingflag =false;
}


void CPcbDlg::OnBnClickedButtonMotorDisplaceIn2()
{
	if( !func_TaskMovingCheck() )	return;

	/* 이동중이면 Return */
	g_bMovingflag =true;

	if(!motor.LENS_Z_Motor_Move(Wait_Pos))
	{
		g_bMovingflag =false;
		return;
	}
	if(!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		g_bMovingflag =false;
		return;
	}
	//if(!motor.Laser_Z_Motor_Move(Wait_Pos))
	//{
	//	g_bMovingflag =false;
	//	return;
	//}

	if( motor.Pcb_Motor_Move_Laser(1) )
	{
		//if(motor.Laser_Z_Motor_Move(Laser_In_Pos))
		//{
		//	CString sTmpLog;
		//	sLangChange.LoadStringA(IDS_STRING1483);	//PCB부 내부 Laser 변위 측정 2차위치 이동 완료
		//	sTmpLog.Format(sLangChange);
		//	delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
		//}
	}

	g_bMovingflag =false;
}


void CPcbDlg::OnBnClickedButtonMotorDisplaceIn3()
{
	if( !func_TaskMovingCheck() )	return;

	/* 이동중이면 Return */
	g_bMovingflag =true;

	if(!motor.LENS_Z_Motor_Move(Wait_Pos))
	{
		g_bMovingflag =false;
		return;
	}
	if(!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		g_bMovingflag =false;
		return;
	}
	//if(!motor.Laser_Z_Motor_Move(Wait_Pos))
	//{
	//	g_bMovingflag =false;
	//	return;
	//}

	if( motor.Pcb_Motor_Move_Laser(2) )
	{
		//if(motor.Laser_Z_Motor_Move(Laser_In_Pos))
		//{
		//	CString sTmpLog;
		//	sLangChange.LoadStringA(IDS_STRING1484);	//PCB부 내부 Laser 변위 측정 3차위치 이동 완료
		//	sTmpLog.Format(sLangChange);
		//	delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
		//}
	}

	g_bMovingflag =false;
}


void CPcbDlg::OnBnClickedButtonMotorDisplaceIn4()
{
	if( !func_TaskMovingCheck() )	return;

	/* 이동중이면 Return */
	g_bMovingflag =true;

	if(!motor.LENS_Z_Motor_Move(Wait_Pos))
	{
		g_bMovingflag =false;
		return;
	}
	if(!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		g_bMovingflag =false;
		return;
	}
	//if(!motor.Laser_Z_Motor_Move(Wait_Pos))
	//{
	//	g_bMovingflag =false;
	//	return;
	//}

	if( motor.Pcb_Motor_Move_Laser(3) )
	{
		//if(motor.Laser_Z_Motor_Move(Laser_In_Pos))
		//{
		//	CString sTmpLog;
		//	sLangChange.LoadStringA(IDS_STRING1485);	//PCB부 내부 Laser 변위 측정 4차위치 이동 완료
		//	sTmpLog.Format(sLangChange);
		//	delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
		//}
	}

	g_bMovingflag =false;
}


void CPcbDlg::OnBnClickedButtonMotorLaserOut1()
{
	if( !func_TaskMovingCheck() )	return;

	

	/*double lensPosY = 0.0;
	lensPosY = (float)motor.GetEncoderPos(Motor_Lens_Y);
	if (lensPosY < model.axis[Motor_Lens_Y].pos[Bonding_Pos])
	{
		delayMsg("LENS 대기위치 이동후 진행바랍니다.", 3000, M_COLOR_RED);
		return;
	}*/

	/* 이동중이면 Return */
	g_bMovingflag =true;
	CString sTmpLog="";
	if (!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		g_bMovingflag = false;
		return;
	}
	int pMotorPos = -1;
	if (sysData.m_iProductComp == 1)
	{
		pMotorPos = Com_Laser_Pos;

	}
	else
	{
		pMotorPos = Laser_Pcb_Pos;
	}

	if (motor.Pcb_Motor_Move_Laser(0, 0, 0, 0))
	{
		if (motor.PCB_Z_Motor_Move(pMotorPos))
		{

			delayMsg("Pcb부 Laser 변위 측정 1차위치 이동 완료", 3000, M_COLOR_GREEN);
		}

	}
	else
	{
		delayMsg("Pcb부 Laser 변위 위치 확인 바람", 2000, M_COLOR_RED);
	}
	
	g_bMovingflag = false;
}


void CPcbDlg::OnBnClickedButtonMotorLaserOut2()
{
	if( !func_TaskMovingCheck() )	return;
	double lensPosY = 0.0;
	lensPosY = (float)motor.GetEncoderPos(Motor_Lens_Y);
	/*if (lensPosY < model.axis[Motor_Lens_Y].pos[Bonding_Pos])
	{
		delayMsg("LENS 대기위치 이동후 진행바랍니다.", 3000, M_COLOR_RED);
		return;
	}*/
	/* 이동중이면 Return */
	g_bMovingflag =true;
	CString sTmpLog="";
	if (!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		g_bMovingflag = false;
		return;
	}
	int pMotorPos = -1;
	if (sysData.m_iProductComp == 1)
	{
		pMotorPos = Com_Laser_Pos;

	}
	else
	{
		pMotorPos = Laser_Pcb_Pos;
	}

	if (motor.Pcb_Motor_Move_Laser(1, 0, 0, 0))
	{
		if (motor.PCB_Z_Motor_Move(pMotorPos))
		{

			delayMsg("Pcb부 Laser 변위 측정 2차위치 이동 완료", 3000, M_COLOR_GREEN);
		}

	}
	else
	{
		delayMsg("Pcb부 Laser 변위 위치 확인 바람", 2000, M_COLOR_RED);
	}
	
	g_bMovingflag = false;
	
}


void CPcbDlg::OnBnClickedButtonMotorLaserOut3()
{
	if( !func_TaskMovingCheck() )	return;
	double lensPosY = 0.0;
	lensPosY = (float)motor.GetEncoderPos(Motor_Lens_Y);
	/*if (lensPosY < model.axis[Motor_Lens_Y].pos[Bonding_Pos])
	{
		delayMsg("LENS 대기위치 이동후 진행바랍니다.", 3000, M_COLOR_RED);
		return;
	}*/
	/* 이동중이면 Return */
	g_bMovingflag =true;
	CString sTmpLog="";
	if (!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		g_bMovingflag = false;
		return;
	}
	int pMotorPos = -1;
	if (sysData.m_iProductComp == 1)
	{
		pMotorPos = Com_Laser_Pos;

	}
	else
	{
		pMotorPos = Laser_Pcb_Pos;
	}

	if (motor.Pcb_Motor_Move_Laser(2, 0, 0, 0))
	{
		if (motor.PCB_Z_Motor_Move(pMotorPos))
		{

			delayMsg("Pcb부 Laser 변위 측정 3차위치 이동 완료", 3000, M_COLOR_GREEN);
		}

	}
	else
	{
		delayMsg("Pcb부 Laser 변위 위치 확인 바람", 2000, M_COLOR_RED);
	}
	
	g_bMovingflag = false;
	
}


void CPcbDlg::OnBnClickedButtonMotorLaserOut4()
{
	if( !func_TaskMovingCheck() )	return;
	double lensPosY = 0.0;
	lensPosY = (float)motor.GetEncoderPos(Motor_Lens_Y);
	/*if (lensPosY < model.axis[Motor_Lens_Y].pos[Bonding_Pos])
	{
		delayMsg("LENS 대기위치 이동후 진행바랍니다.", 3000, M_COLOR_RED);
		return;
	}*/
	/* 이동중이면 Return */
	g_bMovingflag =true;
	CString sTmpLog=""; 
	if (!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		g_bMovingflag = false;
		return;
	}
	int pMotorPos = -1;
	if (sysData.m_iProductComp == 1)
	{
		pMotorPos = Com_Laser_Pos;

	}
	else
	{
		pMotorPos = Laser_Pcb_Pos;
	}

	if (motor.Pcb_Motor_Move_Laser(3, 0, 0, 0))
	{
		if (motor.PCB_Z_Motor_Move(pMotorPos))
		{

			delayMsg("Pcb부 Laser 변위 측정 4차위치 이동 완료", 3000, M_COLOR_GREEN);
		}

	}
	else
	{
		delayMsg("Pcb부 Laser 변위 위치 확인 바람", 2000, M_COLOR_RED);
	}
	
	g_bMovingflag = false;
	
}


void CPcbDlg::OnBnClickedButtonMotorAlignLaserPos()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	CDPoint LaserPos[4];
	CString sLog;
	int iLaserDelay = model.strInfo_Cam[0].m_iDelayTime;	//Laser 측정전 Delay
	double dTx, dTy;

	if( !func_TaskMovingCheck() )	return;

	/* 이동중이면 Return */
	g_bMovingflag =true;

	//if( !Dio.PCBDarkCheck(true, false) )
	//{//Dark 검사 실린더 하강일 경우 상승
	//	if( !Dio.PCBDark(true, true) )
	//	{
	//		sLangChange.LoadStringA(IDS_STRING488);	//Dark검사 실린더 상승 실패.
	//		delayMsg(sLangChange, 1000, M_COLOR_RED);
	//		g_bMovingflag =false;
	//		return;
	//	}
	//}

	/*if(!motor.LENS_Z_Motor_Move(Laser_Pos))
	{
		g_bMovingflag =false;
		return;
	}*/
	if(!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		g_bMovingflag =false;
		return;
	}
	//if(!motor.Laser_Z_Motor_Move(Wait_Pos))
	//{
	//	g_bMovingflag =false;
	//	return;
	//}

	m_btnAlignLaserPos.m_iStateBtn = 1;
	m_btnAlignLaserPos.Invalidate();

	//motor.Laser_Z_Motor_Move(Laser_In_Pos);
	Sleep(500);	//최주임님, Delay 확인
	//for(int iNo = 0; iNo < 4; iNo++)
	//{
	//	motor.Pcb_Motor_Move_Laser(iNo);
	//	
	//	Task.PCBTaskTime = myTimer(true);
	//	while(1)
	//	{
	//		if((myTimer(true) - Task.PCBTaskTime) > iLaserDelay && (motor.IsStopAxis(Motor_PCB_X) && motor.IsStopAxis(Motor_PCB_Y)))
	//		{
	//			break;
	//		}
	//		else if( (myTimer(true) - Task.PCBTaskTime) > iLaserDelay*2 )
	//		{
	//			sLangChange.LoadStringA(IDS_STRING1257);	//변위 측정 위치 이동 완료 시간 초과....
	//			delayMsg(sLangChange, 2000, M_COLOR_RED);
	//			g_bMovingflag = false;
	//			return;
	//		}

	//		checkMessage();
	//		Sleep(5);
	//		checkMessage();
	//	}

	//	Sleep(500);	//최주임님, Delay 확인
	//	Keyence.func_LT9030_Scan(Task.m_Laser_Point[iNo]);

	//	LaserPos[iNo].x = motor.GetEncoderPos(Motor_PCB_X) - sysData.dDataset[Motor_PCB_X];
	//	LaserPos[iNo].y = motor.GetEncoderPos(Motor_PCB_Y) - sysData.dDataset[Motor_PCB_Y];

	//	sLangChange.LoadStringA(IDS_STRING625);	//Laser 내부 측정값 (%d) : %.04f")
	//	sLog.Format(sLangChange, iNo+1, Task.m_Laser_Point[iNo]);
	//	pFrame->putListLog(sLog);

	//	checkMessage();
	//	Sleep(5);
	//	checkMessage();

	//}

	g_bMovingflag = false;
	pFrame->_calcLaserTilt(LaserPos, Task.m_Laser_Point, dTx, dTy);
	
	m_btnAlignLaserPos.m_iStateBtn = 0;
	m_btnAlignLaserPos.Invalidate();
	sLangChange.LoadStringA(IDS_STRING621);	//Laser Tilting 내부 보정값 X:%.04f, Y:%.04f
	sLog.Format(sLangChange, dTx, dTy);
	pFrame->putListLog(sLog);
}


void CPcbDlg::OnBnClickedButtonMotorAlignLaserPosOut()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	CDPoint LaserPos[4];
	CString sLog;
	int iLaserDelay = model.strInfo_Cam[0].m_iDelayTime;	//Laser 측정전 Delay
	double dTx, dTy;

	if( !func_TaskMovingCheck() )	return;

	/* 이동중이면 Return */
	g_bMovingflag =true;
	if (!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		g_bMovingflag = false;
		return;
	}


	m_btnAlignLaserPosOut.m_iStateBtn = 1;
	m_btnAlignLaserPosOut.Invalidate();

	
	Sleep(500);
	//Com_Laser_Pos
	int pMotorPos = -1;
	if (sysData.m_iProductComp == 1)
	{
		pMotorPos = Com_Laser_Pos;

	}
	else
	{
		pMotorPos = Laser_Pcb_Pos;
	}
	Task.oldLaserTx = 0.1;
	Task.oldLaserTy = 0.1;
	for(int iNo = 0; iNo < 4; iNo++)
	{
		motor.Pcb_Motor_Move_Laser(iNo, 0, 0, 0);
		Sleep(10);
		motor.PCB_Z_Motor_Move(pMotorPos);

		Task.PCBTaskTime = myTimer(true);
		while(1)
		{
			if((myTimer(true) - Task.PCBTaskTime) > iLaserDelay && (motor.IsStopAxis(Motor_PCB_X) && motor.IsStopAxis(Motor_PCB_Y) && motor.IsStopAxis(Motor_PCB_Z)))
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
			Sleep(5);
		}
		Sleep(400);
		Keyence.func_LT9030_Scan(Task.m_Laser_Point[iNo]);
		//Keyence.func_CL3000_Scan(Task.m_Laser_Point[iNo]);

		LaserPos[iNo].x = motor.GetEncoderPos(Motor_PCB_X);
		LaserPos[iNo].y = motor.GetEncoderPos(Motor_PCB_Y);


		sLog.Format("Laser 측정값 (%d) : %.04f", iNo+1, Task.m_Laser_Point[iNo]);
		pFrame->putListLog(sLog);

		checkMessage();
		Sleep(5);
		checkMessage();
	}

	g_bMovingflag = false;
	pFrame->_calcLaserTilt(LaserPos, Task.m_Laser_Point, dTx, dTy);
	
	m_btnAlignLaserPosOut.m_iStateBtn = 0;
	m_btnAlignLaserPosOut.Invalidate();

	sLog.Format("Laser Tilting 보정값 X:%.04f, Y:%.04f", dTx, dTy);
	pFrame->putListLog(sLog);
	motor.Pcb_Move_Tilt(dTx, dTy);
}


void CPcbDlg::OnBnClickedButtonSensorContact()
{
	
	CString sLog;
	if( !func_TaskMovingCheck() )	return;

	/* 이동중이면 Return */
	g_bMovingflag =true;

	if(!motor.LENS_Z_Motor_Move(Wait_Pos))
	{
		g_bMovingflag =false;
		return;
	}
	if(!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		g_bMovingflag =false;
		return;
	}

	if(m_radio == 0)
	{	
		if ( motor.moveSensorContactPos(true) == false )
		{
			g_bMovingflag = false;
			return;
		}

		double dVel = 0.1;
		double dCurPos = 0;//
		CString sTemp1, sTemp2;

		motor.JogMove(Motor_PCB_Z, dVel * sysData.fMotorResol[Motor_PCB_Z]);

		double ep = myTimer(true);

		while (1)
		{
			if ( Dio.SensorContactCheck() == 0 )		/* 센서 감지 되면 */
			{
				motor.StopAxis(Motor_PCB_Z);
				break;
			}

			if ( motor.GetPosiSensor(Motor_PCB_Z) == true )		/* Limit 센서 감지 되면 */
			{
				sLangChange.LoadStringA(IDS_STRING539);
				sTemp1.Format(sLangChange);	//Epoxy Z축 모터 (-) Limit 감지
				errMsg2(Task.AutoFlag, sTemp1);

				motor.StopAxis(Motor_PCB_Z);
				return;
			}

			if (myTimer(true) - ep > 30000)		/* 측정 시간 초과 */
			{
				sLangChange.LoadStringA(IDS_STRING1286);	//센서 감지 시간 초과.
				sTemp1.Format(sLangChange);
				errMsg2(Task.AutoFlag, sTemp1);

				motor.StopAxis(Motor_PCB_Z);
				g_bMovingflag = false;
				return;
			}

			dCurPos = motor.GetCommandPos(Motor_PCB_Z);

			checkMessage();
			::Sleep(5);
		}
		dCurPos = motor.GetCommandPos(Motor_PCB_Z);
		
		sLangChange.LoadStringA(IDS_STRING1194);	//도포 Z축 위치를 계산 하시겠습니까?
		sTemp1 = sLangChange + _T("\n\n");
		sTempLang.LoadStringA(IDS_STRING117);
		sLangChange.Format(sTempLang, (dCurPos), model.axis[Motor_PCB_Z].pos[Contact_Pos]);
		sTemp2.Format(sLangChange);

		CString sMsg;
		sMsg = sTemp1 + sTemp2;

		float fGap = (float)(model.axis[Motor_PCB_Z].pos[Contact_Pos] - dCurPos);

		if ( askMsg(sMsg) == true )
		{
			model.axis[Motor_PCB_Z].pos[Contact_Pos] = (float)dCurPos;
			model.axis[Motor_PCB_Z].pos[Dispense_Pos] = -fGap + model.axis[Motor_PCB_Z].pos[Dispense_Pos];
			model.axis[Motor_PCB_Z].pos[Calc_Pos] = -fGap + model.axis[Motor_PCB_Z].pos[Calc_Pos];
		
			model.Save();
			model.Load();
		}
	}
	//motor.moveWaitPos_Z(true);
	g_bMovingflag = false;
}


void CPcbDlg::OnBnClickedButtonEpoxyCalc()
{
	CString sLog;
	if( !func_TaskMovingCheck() )	return;

	/* 이동중이면 Return */
	g_bMovingflag =true;

	//if( !Dio.PCBDarkCheck(true, false) )
	//{//Dark 검사 실린더 하강일 경우 상승
	//	if( !Dio.PCBDark(true, true) )
	//	{
	//		sLangChange.LoadStringA(IDS_STRING488);	//Dark검사 실린더 상승 실패.
	//		delayMsg(sLangChange, 1000, M_COLOR_RED);
	//		g_bMovingflag =false;
	//		return;
	//	}
	//}
	if(!motor.LENS_Z_Motor_Move(Wait_Pos))
	{
		g_bMovingflag =false;
		return;
	}
	if(!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		g_bMovingflag =false;
		return;
	}
	if(m_radio == 0)
	{
		if ( motor.movePointDischargePos(true) == false )
		{
			g_bMovingflag = false;
			return;
		}

		if ( motor.movePointDischargePos_Z(true) == false )	
		{
			g_bMovingflag = false;
			return;
		}

		//if ( Dio.EpoxyDischargeOn(true, true) == false )
		//{
		//	g_bMovingflag = false;
		//	Dio.EpoxyDischargeOn(false, false);
		//	return;
		//}
		::Sleep(300);
		double dCalcX = -16.287;
		double dCalcY = -4.973;
		if(model.m_dEpoxyOffsetX == 0 && model.m_dEpoxyOffsetY == 0)
		{
			model.axis[Motor_PCB_X].pos[Dispense_Pos] = model.axis[Motor_PCB_X].pos[Calc_Pos] + dCalcX;//model.m_dEpoxyOffsetX;
			model.axis[Motor_PCB_Y].pos[Dispense_Pos] = model.axis[Motor_PCB_Y].pos[Calc_Pos] + dCalcY;//model.m_dEpoxyOffsetY;
		}
		else
		{
			model.axis[Motor_PCB_X].pos[Dispense_Pos] = model.axis[Motor_PCB_X].pos[Calc_Pos] + model.m_dEpoxyOffsetX;
			model.axis[Motor_PCB_Y].pos[Dispense_Pos] = model.axis[Motor_PCB_Y].pos[Calc_Pos] + model.m_dEpoxyOffsetY;
		}
		model.Save();
		model.Load();

		CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
		CString sLog;
		sLangChange.LoadStringA(IDS_STRING546);
		sLog.Format(sLangChange, dCalcX, dCalcY);//model.m_dEpoxyOffsetX, model.m_dEpoxyOffsetY);
		pFrame->putListLog(sLog);
		
		//if ( Dio.EpoxyDischargeOn(false, true) == false )
		//{
		//	g_bMovingflag = false;
		//	return;
		//}

		//if ( motor.moveWaitPos_Z(true) == false )
		//{
		//	g_bMovingflag = false;
		//	return;
		//}
		//::Sleep(250);
		//if ( motor.Pcb_Motor_Move(Resin_Pos) == false )
		//{
		//	g_bMovingflag = false;
		//	return;
		//}
	}
	//if(m_radio == 1)
	//{
	//	if ( motor.movePointDischarge2Pos(true) == false )
	//	{
	//		g_bMovingflag = false;
	//		return;
	//	}

	//	if ( motor.movePointDischarge2Pos_Z(true) == false )	
	//	{
	//		g_bMovingflag = false;
	//		return;
	//	}

	//	if ( Dio.EpoxyDischargeOn2(true, true) == false )
	//	{
	//		g_bMovingflag = false;
	//		Dio.EpoxyDischargeOn(false, false);
	//		return;
	//	}

	//	::Sleep(250);

	//	if ( Dio.EpoxyDischargeOn2(false, true) == false )
	//	{
	//		g_bMovingflag = false;
	//		return;
	//	}

	//	if ( motor.moveWaitPos_Z(true) == false )
	//	{
	//		g_bMovingflag = false;
	//		return;
	//	}

	//	if ( motor.Pcb_Motor_Move(Resin_Pos) == false )
	//	{
	//		g_bMovingflag = false;
	//		return;
	//	}	
	//}
//	Task.bManual_FindEpoxy = true;



	g_bMovingflag = false;
}


void CPcbDlg::OnBnClickedButtonFindbaseEpoxy()
{
	if( !func_TaskMovingCheck() )	return;

	LightControl.ctrlLedVolume(LIGHT_PCB, model.m_iLedValue[LEDDATA_RESIN_CALC]);
	Sleep(100);

	vision.clearOverlay();

	if ( FindEpoxyPoint5(CAM1) < 0 )		return;

	vision.drawOverlay(CAM1);

	m_iBaseX = (int)(m_dCogX+0.5);
	m_iBaseY = (int)(m_dCogY+0.5);
	m_dCogX = m_dCogY = 0;
}

void CPcbDlg::OnBnClickedButtonFindEpoxy()
{
	if( !func_TaskMovingCheck() )	return;

//	LightControl.ctrlLedVolume(LIGHT_PCB, model.m_iLedValue[LEDDATA_RESIN_CALC]);
//	Sleep(100);

	vision.clearOverlay();

//	if ( FindEpoxyPoint5(CAM1) < 0 )		return;

//	vision.drawOverlay(CAM1);

	//if ( CalcEpoxyOffset() < 0 )
	//{
	//	errMsg2(Task.AutoFlag, "도포 보정값 계산 실패");

	//	return;
	//}

	m_dOffsetX = model.axis[Motor_PCB_X].pos[Dispense_Pos] - model.axis[Motor_PCB_X].pos[Calc_Pos];
	m_dOffsetY = model.axis[Motor_PCB_Y].pos[Dispense_Pos] - model.axis[Motor_PCB_Y].pos[Calc_Pos];

	PutEpoxyDataOnEdit();
	
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	CString sLog;
	sLangChange.LoadStringA(IDS_STRING546);	//Epoxy 보정값 계산 완료 X:%.03f, Y:%.03f
	sLog.Format(sLangChange, m_dOffsetX, m_dOffsetY);
	pFrame->putListLog(sLog);

	//m_iBaseX = (int)(m_dCogX+0.5);
	//m_iBaseY = (int)(m_dCogY+0.5);
	//m_dCogX = m_dCogY = 0;
}

int CPcbDlg::FindEpoxyPoint(int iCh)
{
#if 0
	if(iCh >= 2	) return 0;

	CString sMsg;
	int iSx, iSy, iEx, iEy;
	int iPos,sum;
	int aiHist[CAM_SIZE_X] = {0,};
	int aiHisty[CAM_SIZE_X] = {0,};
	unsigned char* pucImage;

	//if(vision.getLiveMode())
	//{
	//	vision.getSnapImage(iCh);
	//	vision.setLiveMode(true);
	//}


	int inspSize = 50;
	iSx = CAM_SIZE_X/4 - inspSize + 120;
	iEx = CAM_SIZE_X/4 + inspSize + 120;
	iSy = CAM_SIZE_Y/2 - inspSize - 170;
	iEy = CAM_SIZE_Y/2 + inspSize - 170;

	vision.boxlist[iCh].addList(iSx, iSy, iEx, iEy, PS_DOT, M_COLOR_RED);

	MbufAllocColor(vision.MilSystem, 1, CAM_SIZE_X, CAM_SIZE_Y, M_DEF_IMAGE_TYPE, M_IMAGE+M_PROC, &MilBinaryImage);
	MbufClear(MilBinaryImage, 0);

	MbufCopy(vision.MilProcImage[iCh], MilBinaryImage);

	int iSizeX = MbufInquire(vision.MilProcImage[iCh], M_PITCH, M_NULL);
	int iWidth = MbufInquire(vision.MilProcImage[iCh], M_SIZE_X, M_NULL);
	int iHeight = MbufInquire(vision.MilProcImage[iCh], M_SIZE_Y, M_NULL);

	int iPitch_Ori, iHeight_Ori, iWidth_Ori;
	iPitch_Ori = MbufInquire(MilBinaryImage, M_PITCH, NULL);
	iWidth_Ori = MbufInquire(MilBinaryImage, M_SIZE_X, NULL);
	iHeight_Ori = MbufInquire(MilBinaryImage, M_SIZE_Y, NULL);
	pucImage = (unsigned char*)GlobalAlloc(GMEM_ZEROINIT, iPitch_Ori*iHeight_Ori);
	MbufInquire(MilBinaryImage, M_HOST_ADDRESS, &pucImage);

	for (int x=iSx ; x<iEx ; x++)
	{
		sum = 0;
		iPos = iSy * iSizeX + x;

		for (int y=iSy ; y<iEy ; y++)
		{
			sum += vision.MilImageBuffer[iCh][iPos];
			iPos += iSizeX;
		}
		aiHist[x] = sum;
	}

	for (int y=iSy ; y<iEy ; y++)
	{
		sum = 0;
		iPos = y * iSizeX + iSx;

		for (int x=iSx ; x<iEx ; x++)
		{
			sum += vision.MilImageBuffer[iCh][iPos];
			iPos ++;
		}
		aiHisty[y] = sum;
	}

	int iMax = 99999;
	int iMax_Second = 99999;
	int iIndex1, iIndex2;

	for (int i= iSx; i<iEx ; i++)
	{
		if ( aiHist[i] < iMax )
		{
			iMax = aiHist[i];
			iIndex1 = i;
		}
	}

	for (int i=iSy ; i<iEy ; i++)
	{
		if ( aiHisty[i] < iMax_Second )
		{
			iMax_Second = aiHisty[i];
			iIndex2 = i;
		}
	}

	int iThreshold = (iIndex1 + iIndex2) / 2;
	for (int y=0 ; y<iHeight_Ori ; y++)
	{
		iPos = y * iPitch_Ori;

		for (int x=0 ; x<iWidth_Ori ; x++)
		{
			if ( x> iSx && x < iEx && y > iSy && y < iEy)
			{
				if ( pucImage[iPos] > iThreshold )
				{
					pucImage[iPos] = 255;
				}
				else
				{
					pucImage[iPos] = 0;
				}
			}
			else
			{
				pucImage[iPos] = 255;
			}

			iPos++;
		}
	}

	MblobAllocFeatureList(vision.MilSystem, &MilBlobFeatureList);

	MblobSelectFeature(MilBlobFeatureList, M_AREA);
	MblobSelectFeature(MilBlobFeatureList, M_CENTER_OF_GRAVITY);

	MblobAllocResult(vision.MilSystem, &MilBlobResult);

	MblobCalculate(MilBinaryImage, M_NULL, MilBlobFeatureList, MilBlobResult);

	MblobSelect(MilBlobResult, M_EXCLUDE, M_AREA, M_LESS_OR_EQUAL, 800, M_NULL);
#ifdef  _M_X64
	LONG64 iTotalBlobs = 0;
#else 
	long iTotalBlobs = 0;
#endif
	
	MblobGetNumber(MilBlobResult, &iTotalBlobs);

	if ( iTotalBlobs < 1 )
	{
		sLangChange.LoadStringA(IDS_STRING1208);		//레진 위치를 찾지 못했습니다.
		sMsg.Format(sLangChange);
		errMsg2(Task.AutoFlag, sMsg);

		vision.drawOverlay(iCh);

		return -1;
	}

	if ( iTotalBlobs > 1 )
	{
		sLangChange.LoadStringA(IDS_STRING1411);	//찾은 레진 위치가 많습니다. ( %d )
		sMsg.Format(sLangChange, iTotalBlobs);
		errMsg2(Task.AutoFlag, sMsg);

		vision.drawOverlay(iCh);

		return -1;
	}

	MblobGetResult(MilBlobResult, M_CENTER_OF_GRAVITY_X, &m_dCogX);
	MblobGetResult(MilBlobResult, M_CENTER_OF_GRAVITY_Y, &m_dCogY);

	//vision.crosslist[1].addList((int)(m_dCogX + 0.5), (int)(m_dCogY + 0.5), 100, M_COLOR_GREEN);
	vision.crosslist[iCh].addList(iIndex1+0.5, iIndex2+0.5, 100, M_COLOR_GREEN);
	if(m_radio == 0)
	{
		vision.crosslist[iCh].addList(model.m_EpoxyBaseP.x, model.m_EpoxyBaseP.y, 100, M_COLOR_RED);
	}
	else if(m_radio == 1)
	{
		vision.crosslist[iCh].addList(model.m_Epoxy2BaseP.x, model.m_Epoxy2BaseP.y, 100, M_COLOR_RED);
	}

	//sMsg.Format("X : %.2lf Y %.2lf", m_dCogX, m_dCogY);
	m_dCogX = iIndex1;
	m_dCogY = iIndex2;
	sMsg.Format("X : %.2lf Y %.2lf", m_dCogX, m_dCogY);

	vision.textlist[iCh].addList(100, 100, sMsg, M_COLOR_RED, 16, 12, "Arial");

	MbufFree(MilBlobResult);
	MilBlobResult = M_NULL;

	MbufFree(MilBlobFeatureList);
	MilBlobFeatureList = M_NULL;

	MbufFree(MilBinaryImage);
	MilBinaryImage = M_NULL;

	GlobalUnlock(pucImage);
#endif
	return 1;
}


int CPcbDlg::FindEpoxyPoint2(int iCh)
{
#if 0
	if(iCh >= 2	) return 0;

	CString sMsg;
	int iSx, iSy, iEx, iEy;
	int iPos;
	int aiHist[256] = {0,};
	unsigned char* pucImage;

	if(vision.getLiveMode())
	{
		vision.getSnapImage(iCh);
		vision.setLiveMode(true);
	}

	//iSx = 300;
	//iSy = 200;
	//iEx = 730;
	//iEy = 550;
	int inspSize = 50;
	iSx = CAM_SIZE_X/4 - inspSize + 110;
	iEx = CAM_SIZE_X/4 + inspSize + 100;
	iSy = CAM_SIZE_Y/2 - inspSize - 130;
	iEy = CAM_SIZE_Y/2 + inspSize - 150;


	vision.boxlist[iCh].addList(iSx, iSy, iEx, iEy, PS_DOT, M_COLOR_RED);

	MbufAllocColor(vision.MilSystem, 1, CAM_SIZE_X, CAM_SIZE_Y, M_DEF_IMAGE_TYPE, M_IMAGE+M_PROC, &MilBinaryImage);
	MbufClear(MilBinaryImage, 0);

	//MbufCopy(vision.MilProcImage[0], MilBinaryImage);
	MbufCopy(vision.MilProcImageChild[iCh], MilBinaryImage);

	int iSizeX = MbufInquire(vision.MilProcImageChild[iCh], M_PITCH, M_NULL);
	int iWidth = MbufInquire(vision.MilProcImageChild[iCh], M_SIZE_X, M_NULL);
	int iHeight = MbufInquire(vision.MilProcImageChild[iCh], M_SIZE_Y, M_NULL);

	int iPitch_Ori, iHeight_Ori, iWidth_Ori;
	iPitch_Ori = MbufInquire(MilBinaryImage, M_PITCH, M_NULL);
	iWidth_Ori = MbufInquire(MilBinaryImage, M_SIZE_X, M_NULL);
	iHeight_Ori = MbufInquire(MilBinaryImage, M_SIZE_Y, M_NULL);
	pucImage = (unsigned char*)GlobalAlloc(GMEM_ZEROINIT, iPitch_Ori*iHeight_Ori);
	MbufInquire(MilBinaryImage, M_HOST_ADDRESS, &pucImage);

	for (int y=iSy ; y<iEy ; y++)
	{
		iPos = y * iSizeX + iSx;

		for (int x=iSx ; x<iEx ; x++)
		{
			aiHist[vision.MilImageBuffer[1][iPos++]]++;
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

	for (int y=0 ; y<iHeight_Ori ; y++)
	{
		iPos = y * iPitch_Ori;

		for (int x=0 ; x<iWidth_Ori ; x++)
		{
			if ( x> iSx && x < iEx && y > iSy && y < iEy)
			{
				if ( pucImage[iPos] > iThreshold )
				{
					pucImage[iPos] = 0;
				}
				else
				{
					pucImage[iPos] = 255;
				}
			}
			else
			{
				pucImage[iPos] = 0;
			}

			iPos++;
		}
	}

	MblobAllocFeatureList(vision.MilSystem, &MilBlobFeatureList);

	MblobSelectFeature(MilBlobFeatureList, M_AREA);
	MblobSelectFeature(MilBlobFeatureList, M_CENTER_OF_GRAVITY);

	MblobAllocResult(vision.MilSystem, &MilBlobResult);

	MblobCalculate(MilBinaryImage, M_NULL, MilBlobFeatureList, MilBlobResult);

	MblobSelect(MilBlobResult, M_EXCLUDE, M_AREA, M_LESS_OR_EQUAL, 800, M_NULL);
#ifdef  _M_X64
	LONG64 iTotalBlobs = 0;
#else 
	long iTotalBlobs = 0;
#endif
	
	MblobGetNumber(MilBlobResult, &iTotalBlobs);

	if ( iTotalBlobs < 1 )
	{
		sLangChange.LoadStringA(IDS_STRING1208);		//레진 위치를 찾지 못했습니다.
		sMsg.Format(sLangChange);
		errMsg2(Task.AutoFlag, sMsg);

		vision.drawOverlay(iCh);
		return -1;
	}

	if ( iTotalBlobs > 1 )
	{
		sLangChange.LoadStringA(IDS_STRING1411);	//찾은 레진 위치가 많습니다. ( %d )
		sMsg.Format(sLangChange, iTotalBlobs);
		errMsg2(Task.AutoFlag, sMsg);

		vision.drawOverlay(iCh);

		return -1;
	}

	MblobGetResult(MilBlobResult, M_CENTER_OF_GRAVITY_X, &m_dCogX);
	MblobGetResult(MilBlobResult, M_CENTER_OF_GRAVITY_Y, &m_dCogY);

	vision.crosslist[iCh].addList((int)(m_dCogX + 0.5), (int)(m_dCogY + 0.5), 100, M_COLOR_MAGENTA);
	if(m_radio == 0)
	{
		vision.crosslist[iCh].addList(model.m_EpoxyBaseP.x, model.m_EpoxyBaseP.y, 100, M_COLOR_RED);
	}
	else if(m_radio == 1)
	{
		vision.crosslist[iCh].addList(model.m_Epoxy2BaseP.x, model.m_Epoxy2BaseP.y, 100, M_COLOR_RED);
	}

	sMsg.Format("X : %.2lf Y %.2lf", m_dCogX, m_dCogY);
	vision.textlist[iCh].addList(100, 100, sMsg, M_COLOR_RED, 16, 12, "Arial");

	MbufFree(MilBlobResult);
	MilBlobResult = M_NULL;

	MbufFree(MilBlobFeatureList);
	MilBlobFeatureList = M_NULL;

	MbufFree(MilBinaryImage);
	MilBinaryImage = M_NULL;

	GlobalUnlock(pucImage);
#endif
	return 1;
}

int CPcbDlg::CalcEpoxyOffset()
{
	if(m_radio == 0)
	{
		m_dOffsetX = ((int)(m_dCogX+0.5) - model.m_EpoxyBaseP.x ) * sysData.dCamResol[1].x;
		m_dOffsetY = (model.m_EpoxyBaseP.y - (int)(m_dCogY+0.5)) * sysData.dCamResol[1].y;
	}
	else if(m_radio == 1)
	{
		m_dOffsetX = ((int)(m_dCogX+0.5) - model.m_Epoxy2BaseP.x ) * sysData.dCamResol[1].x;
		m_dOffsetY = (model.m_Epoxy2BaseP.y - (int)(m_dCogY+0.5)) * sysData.dCamResol[1].y;
	}

	return 1;
}

void CPcbDlg::PutEpoxyDataOnEdit()
{
	CString sTemp;

	sTemp.Format("%.3lf", m_dOffsetX);
	SetDlgItemText(IDC_EDIT_OFFSET_X, sTemp);
	sTemp.Format("%.3lf", m_dOffsetY);
	SetDlgItemText(IDC_EDIT_OFFSET_Y, sTemp);
}

void CPcbDlg::OnBnClickedButtonOffsetSave()
{
	if( !func_TaskMovingCheck() )	return;

	sLangChange.LoadStringA(IDS_STRING536);	//Epoxy Offset. \n적용 하시겠습니까?"
	_stprintf_s(motor.m_szLogMsg, sLangChange);
	if (askMsg(motor.m_szLogMsg) == IDOK)
	{
		CString sTemp;
		GetDlgItemText(IDC_EDIT_OFFSET_X, sTemp);
		model.m_dEpoxyOffsetX = (float)atof(sTemp);
		GetDlgItemText(IDC_EDIT_OFFSET_Y, sTemp);
		model.m_dEpoxyOffsetY = (float)atof(sTemp);

		
		model.Save();
		model.Load();
	}

	PutEpoxyDataOnEdit();
}


void CPcbDlg::OnBnClickedButtonEpoxyInsp1()
{
	if( !func_TaskMovingCheck() )	return;
	vision.clearOverlay(CAM1);
	model.Load();

	double offsetX=0.0, offsetY=0.0, offsetTh=0.0;
	CString logStr="";
	logStr.Format(_T("MANUAL EPOXY TEST"));
	theApp.MainDlg->putListLog(logStr);
#ifndef NORINDA_MODE

	LightControl.ctrlLedVolume(LIGHT_PCB, model.m_iLedValue[LEDDATA_HOLDER]);
	Sleep(500);

	
	theApp.MainDlg->procCamAlign(CAM1, PCB_Holder_MARK, false, offsetX, offsetY, offsetTh);

	logStr.Format("		Pcb : X : %.3lf, Y :%.3lf", offsetX , offsetY);
	theApp.MainDlg->putListLog(logStr);
#endif
	
	//
#ifndef NORINDA_MODE

	LightControl.ctrlLedVolume(LIGHT_PCB, model.m_iLedValue[LEDDATA_EPOXY_INSP]);		// Align만 조명 ON
	Sleep(500);
#endif
	
	bool rtn = theApp.MainDlg->_EpoxyFinddispense(CAM1);		//Manual

	if(rtn)
	{
		vision.textlist[CAM1].addList(860, 690, "O K", M_COLOR_GREEN, 30, 15, "Arial");
	}else
	{
		vision.textlist[CAM1].addList(860, 690, "N G", M_COLOR_RED, 30, 15, "Arial");
	}
	vision.drawOverlay(CAM1);
}
void CPcbDlg::drawRect_Circle_EpoxyInsp()
{
	CRect inRect;
	double centX = Task.d_mark_pos_x[PCB_Holder_MARK][0];
	double centY = Task.d_mark_pos_y[PCB_Holder_MARK][0];
	if(centX == 0 || centY ==0)
	{
		centX = CAM_SIZE_X/2;
		centY = CAM_SIZE_Y/2;
	}
	centX += model.dEpoxyOffset_X;
	centY += model.dEpoxyOffset_Y;
	vision.clearOverlay(CAM1);
	//사각
	for (int i=0; i<4; i++)
	{ 
		inRect.left = (centX + model.m_ResingRectStart[i].x);
		inRect.top =	(centY + model.m_ResingRectStart[i].y);
		inRect.right = (centX + (model.m_ResingRectStart[i].x+ model.m_ResingRectSize[i].x)); 
		inRect.bottom = (centY + (model.m_ResingRectStart[i].y+ model.m_ResingRectSize[i].y));
		vision.boxlist[CAM1].addList(inRect, PS_SOLID, M_COLOR_GREEN);
	}
	//원형
	int iCh = CAM1;
	CPoint inRadius, outRadius;
	float inOffsetX = 0.0;
	float inOffsetY = 0.0;
	float outOffsetX = 0.0;
	float outOffsetY = 0.0;
	//float inOffsetX		= (float)((model.m_ResinDrawSize.x*1) - model.m_dResinInspOffset[0].x);	//안쪽 Offset
	//float inOffsetY		= (float)((model.m_ResinDrawSize.y*1) - model.m_dResinInspOffset[0].y);
	//float outOffsetX	= (float)((model.m_ResinDrawSize.x*1) + model.m_dResinInspOffset[1].x);	//바깥쪽 Offset
	//float outOffsetY	= (float)((model.m_ResinDrawSize.y*1) + model.m_dResinInspOffset[1].y);
		
	int i_limit_rate	= model.m_iResinInspLimit;

	int margine = 5;

	//char	szDispData[256];
	
	for (int Pos = 0; Pos < 4; Pos++)
	{
		centX = Task.d_mark_pos_x[PCB_Holder_MARK][0];
		centY = Task.d_mark_pos_y[PCB_Holder_MARK][0];
		if(centX == 0 || centY ==0)
		{
			centX = CAM_SIZE_X/2;
			centY = CAM_SIZE_Y/2;
		}
		centX += model.dEpoxyOffset_X + model.m_CircleDrawCenter[Pos].x;
		centY += model.dEpoxyOffset_Y + model.m_CircleDrawCenter[Pos].y;

		inOffsetX		= (float)((model.m_CircleDrawSize[Pos].x*1) - model.m_dResinInspOffset[0].x);	//안쪽 Offset
		inOffsetY		= (float)((model.m_CircleDrawSize[Pos].y*1) - model.m_dResinInspOffset[0].y);
		outOffsetX		= (float)((model.m_CircleDrawSize[Pos].x*1) + model.m_dResinInspOffset[1].x);	//바깥쪽 Offset
		outOffsetY		= (float)((model.m_CircleDrawSize[Pos].y*1) + model.m_dResinInspOffset[1].y);

		inRadius.x = (int)inOffsetX / sysData.dCamResol[iCh].x;
		outRadius.x = (int)outOffsetX / sysData.dCamResol[iCh].x;
		CRect  outRect;
		inRect.left		= (int)(centX - inOffsetX / sysData.dCamResol[iCh].x  );
		inRect.right	= (int)(centX + inOffsetX / sysData.dCamResol[iCh].x  );
		inRect.top		= (int)(centY - inOffsetY / sysData.dCamResol[iCh].y  );
		inRect.bottom	= (int)(centY + inOffsetY / sysData.dCamResol[iCh].y  );
		
		outRect.left	= (int)(centX - outOffsetX / sysData.dCamResol[iCh].x );
		outRect.right	= (int)(centX + outOffsetX / sysData.dCamResol[iCh].x );
		outRect.top		= (int)(centY - outOffsetY / sysData.dCamResol[iCh].y );
		outRect.bottom	= (int)(centY + outOffsetY / sysData.dCamResol[iCh].y );

		vision.crosslist[iCh].addList((int)centX, (int)centY, 120, M_COLOR_BLUE);	// 도포 검사 중심 위치..
		vision.boxlist[iCh].addList(inRect, PS_SOLID, M_COLOR_RED);				// 도포 검사 영역..
		vision.boxlist[iCh].addList(outRect, PS_SOLID, M_COLOR_GREEN);
		vision.drawOverlay(CAM1);
	}
}
	
void CPcbDlg::drawRectEpoxyInsp()//(int iRectNo)
{
	CRect inRect;
	double centX =Task.d_mark_pos_x[PCB_Holder_MARK][0];
	double centY = Task.d_mark_pos_y[PCB_Holder_MARK][0];
	int i = 0;

	if(centX == 0 || centY ==0) 
	{
		centX = CAM_SIZE_X/2;
		centY = CAM_SIZE_Y/2;
	}
	centX += model.dEpoxyOffset_X;
	centY += model.dEpoxyOffset_Y;
	vision.clearOverlay(CAM1);


	for (i = 0; i < 4; i++)
	{ 
		int ndPosx = 0;
		int ndPosy = 0;

		ndPosx = (centX + (model.m_ResingRectStart[i].x)) - (model.m_ResingRectSize[i].x / 2);
		ndPosy = (centY + (model.m_ResingRectStart[i].y)) - (model.m_ResingRectSize[i].y / 2);

		inRect.left = ndPosx;
		inRect.top = ndPosy;
		inRect.right = (inRect.left + (model.m_ResingRectSize[i].x ));
		inRect.bottom = (inRect.top + (model.m_ResingRectSize[i].y ));

		/*inRect.left = (centX + model.m_ResingRectStart[i].x);
		inRect.top =	(centY + model.m_ResingRectStart[i].y);
		inRect.right = (centX + (model.m_ResingRectStart[i].x+ model.m_ResingRectSize[i].x)); 
		inRect.bottom = (centY + (model.m_ResingRectStart[i].y+ model.m_ResingRectSize[i].y));*/

		vision.boxlist[CAM1].addList(inRect, PS_SOLID, M_COLOR_GREEN);
	}
	vision.drawOverlay(CAM1);
}
void CPcbDlg::drawCircleEpoxyInsp()//(int iRectNo)
{
	int iCh = CAM1;
	double centX = Task.d_mark_pos_x[PCB_Holder_MARK][0];
	double centY =Task.d_mark_pos_y[PCB_Holder_MARK][0];
	if(centX == 0 || centY ==0)
	{
		centX = CAM_SIZE_X/2;
		centY = CAM_SIZE_Y/2;
	}
	CPoint inRadius, outRadius;
	float inOffsetX		= (float)((model.m_ResinDrawSize.x*1) - model.m_dResinInspOffset[0].x);	//안쪽 Offset
	float inOffsetY		= (float)((model.m_ResinDrawSize.y*1) - model.m_dResinInspOffset[0].y);
	float outOffsetX	= (float)((model.m_ResinDrawSize.x*1) + model.m_dResinInspOffset[1].x);	//바깥쪽 Offset
	float outOffsetY	= (float)((model.m_ResinDrawSize.y*1) + model.m_dResinInspOffset[1].y);
	inRadius.x	= (int)inOffsetX/ sysData.dCamResol[iCh].x;
	outRadius.x	= (int)outOffsetX/ sysData.dCamResol[iCh].x;		
	int i_limit_rate	= model.m_iResinInspLimit;

	int margine = 5;

	//char	szDispData[256];
	CString sTemp="";
	vision.clearOverlay();

	
	centX += model.dEpoxyOffset_X;
	centX += model.dEpoxyOffset_Y;

	CRect inRect, outRect;
	inRect.left		= (int)(centX - inOffsetX / sysData.dCamResol[iCh].x  );
	inRect.right	= (int)(centX + inOffsetX / sysData.dCamResol[iCh].x  );
	inRect.top		= (int)(centY - inOffsetY / sysData.dCamResol[iCh].y  );
	inRect.bottom	= (int)(centY + inOffsetY / sysData.dCamResol[iCh].y  );
																		  
	outRect.left	= (int)(centX - outOffsetX / sysData.dCamResol[iCh].x );
	outRect.right	= (int)(centX + outOffsetX / sysData.dCamResol[iCh].x );
	outRect.top		= (int)(centY - outOffsetY / sysData.dCamResol[iCh].y );
	outRect.bottom	= (int)(centY + outOffsetY / sysData.dCamResol[iCh].y );

	vision.crosslist[iCh].addList((int)centX, (int)centY, 30, M_COLOR_GREEN);	// 도포 검사 중심 위치..
	vision.boxlist[iCh].addList(inRect, PS_SOLID, M_COLOR_RED);				// 도포 검사 영역..
	vision.boxlist[iCh].addList(outRect, PS_SOLID, M_COLOR_GREEN);
	vision.drawOverlay(CAM1);
}
void CPcbDlg::OnBnClickedButtonMotorSensorContactPos()
{
	if( !func_TaskMovingCheck() )	return;

	/* 이동중이면 Return */
	g_bMovingflag =true;

	//if( !Dio.PCBDarkCheck(true, false) )
	//{//Dark 검사 실린더 하강일 경우 상승
	//	if( !Dio.PCBDark(true, true) )
	//	{
	//		sLangChange.LoadStringA(IDS_STRING488);	//Dark검사 실린더 상승 실패.
	//		delayMsg(sLangChange, 1000, M_COLOR_RED);
	//		g_bMovingflag =false;
	//		return;
	//	}
	//}

	//if( !Dio.LaserLiftCheck(true, false) )
	//{//Laser 검사 실린더 하강일 경우 상승
	//	if( !Dio.LaserLift(true, true) )
	//	{
	//		//sLangChange.LoadStringA(IDS_STRING488);	//Dark검사 실린더 상승 실패.
	//		delayMsg(_T("LaserCheck The Cylinder Rises Fail"), 1000, M_COLOR_RED);
	//		g_bMovingflag =false;
	//		return;
	//	}
	//}

	if(!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		g_bMovingflag =false;
		return;
	}
	if(motor.Pcb_Motor_Move(Contact_Pos))
	{
		CString sTmpLog;
		sLangChange.LoadStringA(IDS_STRING1015);	//PCB부 %s 이동 완료
		sTmpLog.Format(sLangChange, "Contact_Pos");
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
	}
	g_bMovingflag =false;
}


void CPcbDlg::OnBnClickedButtonMotorExpoxyTargetPos()
{
	if( !func_TaskMovingCheck() )	return;

	/* 이동중이면 Return */
	g_bMovingflag =true;

	if(!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		g_bMovingflag =false;
		return;
	}

	if(motor.Pcb_Motor_Move(Calc_Pos))
	{
		CString sTmpLog;
		sLangChange.LoadStringA(IDS_STRING899);	//"PCB %s 이동 완료"
		sTmpLog.Format(sLangChange, MotorPosName[Calc_Pos]);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
	}

	g_bMovingflag =false;
}


void CPcbDlg::OnStnClickedPcbAlignResult()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
int CPcbDlg::FindEpoxyPoint4(int iCh)
{

#if 0
	CString sMsg;
	int iSx, iSy, iEx, iEy;
	int iPos,sum;
	int aiHist[CAM_SIZE_X] = {0,};
	int aiHisty[CAM_SIZE_X] = {0,};
	unsigned char* pucImage;

	if(vision.getLiveMode())
	{
		vision.getSnapImage(iCh);
		vision.setLiveMode(true);
	}

	int inspSize = 50;
	//iSx = CAM_SIZE_X/2 - inspSize;
	//iEx = CAM_SIZE_X/2 + inspSize;
	//iSy = CAM_SIZE_Y/2 - inspSize;
	//iEy = CAM_SIZE_Y/2 + inspSize;
	iSx = CAM_SIZE_X/4 - inspSize + 110;
	iEx = CAM_SIZE_X/4 + inspSize + 100;
	iSy = CAM_SIZE_Y/2 - inspSize - 130;
	iEy = CAM_SIZE_Y/2 + inspSize - 150;

	// 	iSx = model.m_rcArea_EpoxyCalc.left;
	// 	iSy = model.m_rcArea_EpoxyCalc.top;
	// 	iEx = model.m_rcArea_EpoxyCalc.right;
	// 	iEy = model.m_rcArea_EpoxyCalc.bottom;

	vision.boxlist[iCh].addList(iSx, iSy, iEx, iEy, PS_DOT, M_COLOR_RED);

	MbufAllocColor(vision.MilSystem, 1, CAM_SIZE_X, CAM_SIZE_Y, M_DEF_IMAGE_TYPE, M_IMAGE+M_PROC, &MilBinaryImage);
	MbufClear(MilBinaryImage, 0);

	MbufCopy(vision.MilProcImage[0], MilBinaryImage);

	int iSizeX = MbufInquire(vision.MilProcImage[0], M_PITCH, M_NULL);
	int iWidth = MbufInquire(vision.MilProcImage[0], M_SIZE_X, M_NULL);
	int iHeight = MbufInquire(vision.MilProcImage[0], M_SIZE_Y, M_NULL);

	int iPitch_Ori, iHeight_Ori, iWidth_Ori;
	iPitch_Ori = MbufInquire(MilBinaryImage, M_PITCH, M_NULL);
	iWidth_Ori = MbufInquire(MilBinaryImage, M_SIZE_X, M_NULL);
	iHeight_Ori = MbufInquire(MilBinaryImage, M_SIZE_Y, M_NULL);
	pucImage = (unsigned char*)GlobalAlloc(GMEM_ZEROINIT, iPitch_Ori*iHeight_Ori);
	MbufInquire(MilBinaryImage, M_HOST_ADDRESS, &pucImage);

	for (int x=iSx ; x<iEx ; x++)
	{
		sum = 0;
		iPos = iSy * iSizeX + x;

		for (int y=iSy ; y<iEy ; y++)
		{
			sum += vision.MilImageBuffer[iCh][iPos];
			iPos += iSizeX;
		}
		aiHist[x] = sum;
	}

	for (int y=iSy ; y<iEy ; y++)
	{
		sum = 0;
		iPos = y * iSizeX + iSx;

		for (int x=iSx ; x<iEx ; x++)
		{
			sum += vision.MilImageBuffer[iCh][iPos];
			iPos ++;
		}
		aiHisty[y] = sum;
	}

	int iMax = 99999;
	int iMax_Second = 99999;
	int iIndex1, iIndex2;
	//중앙 동그라미 찾기
	bool first = false;
	bool second = false;
	bool three = false;
	bool four = false;
	for (int i= iSx; i<iEx ; i++)
	{
		if (first == false )//&& second == false /*&& three == false && four == false*/)
		{
			if ( aiHist[i] < iMax && aiHist[i-1] > aiHist[i])
			{
				iMax = aiHist[i];
				iIndex1 = i;
			}
			else if ( aiHist[i] > iMax && aiHist[i-1] < aiHist[i] && i != iSx)
			{
				first = true;
			}
		}
		//else if(first == true && second == false /*&& three == false && four == false*/)
		//{
		//	if ( aiHist[i] > iMax && aiHist[i-1] < aiHist[i])
		//	{
		//		iMax = aiHist[i];
		//		iIndex1 = i;
		//	}
		//	else if ( aiHist[i] < iMax && aiHist[i-1] > aiHist[i])
		//	{
		//		second = true;
		//	}
		//}
		//else if (first == true && second == true && three == false && four == false)
		//{
		//	if ( aiHist[i] < iMax && aiHist[i-1] > aiHist[i])
		//	{
		//		iMax = aiHist[i];
		//		iIndex1 = i;
		//	}
		//	else if ( aiHist[i] > iMax && aiHist[i-1] < aiHist[i] && i != iSx)
		//	{
		//		three = true;
		//	}
		//}
		//else if(first == true && second == true && three == true && four == false)
		//{
		//	if ( aiHist[i] > iMax && aiHist[i-1] < aiHist[i])
		//	{
		//		iMax = aiHist[i];
		//		iIndex1 = i;
		//	}
		//	else if ( aiHist[i] < iMax && aiHist[i-1] > aiHist[i])
		//	{
		//		four = true;
		//	}
		//}
		//else
		//{
		//	if ( aiHist[i] < iMax && aiHist[i-1] > aiHist[i])
		//	{
		//		iMax = aiHist[i];
		//		iIndex1 = i;
		//	}
		//	else if ( aiHist[i] > iMax && aiHist[i-1] < aiHist[i] && i != iSx)
		//	{
		//		break;
		//	}
		//}
	}

	
	first = false;
	second = false;
	for (int i=iSy ; i<iEy ; i++)
	{
		if (first == false && second == false)
		{
			if ( aiHisty[i] < iMax_Second && aiHisty[i-1] > aiHisty[i])
			{
				iMax_Second = aiHisty[i];
				iIndex2 = i;
			}
			else if ( aiHisty[i] > iMax_Second && aiHisty[i-1] < aiHisty[i] && i != iSy)
			{
				first = true;
			}
		}
		else if (first == true && second == false)
		{
			if ( aiHisty[i] > iMax_Second && aiHisty[i-1] < aiHisty[i])
			{
				iMax_Second = aiHisty[i];
				iIndex2 = i;
			}
			else if ( aiHisty[i] < iMax_Second && aiHisty[i-1] > aiHisty[i])
			{
				second = true;
			}
		}
		else
		{
			if ( aiHisty[i] < iMax_Second && aiHisty[i-1] > aiHisty[i])
			{
				iMax_Second = aiHisty[i];
				iIndex2 = i;
			}
			else if ( aiHisty[i] > iMax_Second && aiHisty[i-1] < aiHisty[i])
			{
				break;
			}
		}

	}

	int iThreshold = (iIndex1 + iIndex2) / 2;

	for (int y=0 ; y<iHeight_Ori ; y++)
	{
		iPos = y * iPitch_Ori;

		for (int x=0 ; x<iWidth_Ori ; x++)
		{
			if ( x> iSx && x < iEx && y > iSy && y < iEy)
			{
				if ( pucImage[iPos] > iThreshold )
				{
					pucImage[iPos] = 255;
				}
				else
				{
					pucImage[iPos] = 0;
				}
			}
			else
			{
				pucImage[iPos] = 255;
			}

			iPos++;
		}
	}

	MblobAllocFeatureList(vision.MilSystem, &MilBlobFeatureList);

	MblobSelectFeature(MilBlobFeatureList, M_AREA);
	MblobSelectFeature(MilBlobFeatureList, M_CENTER_OF_GRAVITY);

	MblobAllocResult(vision.MilSystem, &MilBlobResult);

	MblobCalculate(MilBinaryImage, M_NULL, MilBlobFeatureList, MilBlobResult);

	MblobSelect(MilBlobResult, M_EXCLUDE, M_AREA, M_LESS_OR_EQUAL, 800, M_NULL);
#ifdef  _M_X64
	LONG64 iTotalBlobs = 0;
#else 
	long iTotalBlobs = 0;
#endif
	
	MblobGetNumber(MilBlobResult, &iTotalBlobs);

	if ( iTotalBlobs < 1 )
	{
		sLangChange.LoadStringA(IDS_STRING1208);		//레진 위치를 찾지 못했습니다.
		sMsg.Format(sLangChange);
		errMsg2(Task.AutoFlag, sMsg);

		vision.drawOverlay(iCh);

		return -1;
	}

	if ( iTotalBlobs > 1 )
	{
		sLangChange.LoadStringA(IDS_STRING1411);	//찾은 레진 위치가 많습니다. ( %d )
		sMsg.Format(sLangChange, iTotalBlobs);
		errMsg2(Task.AutoFlag, sMsg);

		vision.drawOverlay(iCh);

		return -1;
	}

	MblobGetResult(MilBlobResult, M_CENTER_OF_GRAVITY_X, &m_dCogX);
	MblobGetResult(MilBlobResult, M_CENTER_OF_GRAVITY_Y, &m_dCogY);

	//vision.crosslist[1].addList((int)(m_dCogX + 0.5), (int)(m_dCogY + 0.5), 100, M_COLOR_GREEN);
	vision.crosslist[iCh].addList((int)(iIndex1), (int)(iIndex2), 100, M_COLOR_GREEN);
	if(m_radio == 0)
	{
		vision.crosslist[iCh].addList((int)(model.m_EpoxyBaseP.x), (int)(model.m_EpoxyBaseP.y), 100, M_COLOR_RED);
	}
	else if(m_radio == 1)
	{
		vision.crosslist[iCh].addList((int)(model.m_Epoxy2BaseP.x), (int)(model.m_Epoxy2BaseP.y), 100, M_COLOR_RED);
	}
	//sMsg.Format("X : %.2lf Y %.2lf", m_dCogX, m_dCogY);
	m_dCogX = iIndex1;
	m_dCogY = iIndex2;
	sMsg.Format("X : %.2lf Y %.2lf", m_dCogX, m_dCogY);

	vision.textlist[iCh].addList(100, 100, sMsg, M_COLOR_RED, 16, 12, "Arial");

	MbufFree(MilBlobResult);
	MilBlobResult = M_NULL;

	MbufFree(MilBlobFeatureList);
	MilBlobFeatureList = M_NULL;

	MbufFree(MilBinaryImage);
	MilBinaryImage = M_NULL;

	GlobalUnlock(pucImage);
#endif
	return 1;
}
int CPcbDlg::FindEpoxyPoint5(int iCh)
{
#if 0
	CString sMsg;
	int iSx, iSy, iEx, iEy;
	int iPos,sum;
	int aiHist[CAM_SIZE_X] = {0,};
	int aiHisty[CAM_SIZE_X] = {0,};
	unsigned char* pucImage;

	if(vision.getLiveMode())
	{
		vision.getSnapImage(iCh);
		vision.setLiveMode(true);
	}

	int inspSize = 200;
	iSx = CAM_SIZE_X/4 - inspSize + 320;
	iEx = CAM_SIZE_X/4 + inspSize + 200;
	iSy = CAM_SIZE_Y/2 - inspSize + 80;
	iEy = CAM_SIZE_Y/2 + inspSize - 90;


	vision.boxlist[iCh].addList(iSx, iSy, iEx, iEy, PS_DOT, M_COLOR_RED);

	MbufAllocColor(vision.MilSystem, 1, CAM_SIZE_X, CAM_SIZE_Y, M_DEF_IMAGE_TYPE, M_IMAGE+M_PROC, &MilBinaryImage);
	MbufClear(MilBinaryImage, 0);

	MbufCopy(vision.MilProcImageChild[iCh], MilBinaryImage);

	int iSizeX = MbufInquire(vision.MilProcImageChild[iCh], M_PITCH, M_NULL);
	int iWidth = MbufInquire(vision.MilProcImageChild[iCh], M_SIZE_X, M_NULL);
	int iHeight = MbufInquire(vision.MilProcImageChild[iCh], M_SIZE_Y, M_NULL);

	int iPitch_Ori, iHeight_Ori, iWidth_Ori;
	iPitch_Ori = MbufInquire(MilBinaryImage, M_PITCH, M_NULL);
	iWidth_Ori = MbufInquire(MilBinaryImage, M_SIZE_X, M_NULL);
	iHeight_Ori = MbufInquire(MilBinaryImage, M_SIZE_Y, M_NULL);
	pucImage = (unsigned char*)GlobalAlloc(GMEM_ZEROINIT, iPitch_Ori*iHeight_Ori);
	MbufInquire(MilBinaryImage, M_HOST_ADDRESS, &pucImage);


	int iIndex1, iIndex2;
	int iMax = 0;
	int iMax_Second = 99999;
	
	for (int x=iSx ; x<iEx ; x++)
	{
		sum = 0;
		iPos = iSy * iSizeX + x;

		for (int y=iSy ; y<iEy ; y++)
		{
			sum += vision.MilImageBuffer[iCh][iPos];
			iPos += iSizeX;
		}

		if( sum / (iEy-iSy) > iMax )
			iMax = (int)(sum / (iEy - iSy));
	}

	iIndex1 = iMax;

	iMax = 0;
	for (int y=iSy ; y<iEy ; y++)
	{
		sum = 0;
		iPos = y * iSizeX + iSx;

		for (int x=iSx ; x<iEx ; x++)
		{
			sum += vision.MilImageBuffer[iCh][iPos];
			iPos ++;
		}

		if( sum / (iEx-iSx) > iMax )
			iMax = (int)(sum / (iEy - iSy));
	}
	
	if(iMax > iIndex1)
		iIndex1 = iMax;
	iIndex2 = iMax;
	

	int iThreshold = (int)(iIndex1);


	for (int y=0 ; y<iHeight_Ori ; y++)
	{
		iPos = y * iPitch_Ori;

		for (int x=0 ; x<iWidth_Ori ; x++)
		{
			if ( x> iSx && x < iEx && y > iSy && y < iEy)
			{
				if ( pucImage[iPos] > iThreshold )
				{
					pucImage[iPos] = 255;
				}
				else
				{
					pucImage[iPos] = 0;
				}
			}
			else
			{
				pucImage[iPos] = 0;
			}

			iPos++;
		}
	}

	MblobAllocFeatureList(vision.MilSystem, &MilBlobFeatureList);

	MblobSelectFeature(MilBlobFeatureList, M_AREA);
	MblobSelectFeature(MilBlobFeatureList, M_NUMBER_OF_HOLES+M_SORT1_UP);
	MblobSelectFeature(MilBlobFeatureList, M_CENTER_OF_GRAVITY);

	MblobAllocResult(vision.MilSystem, &MilBlobResult);

	MblobCalculate(MilBinaryImage, M_NULL, MilBlobFeatureList, MilBlobResult);

	MblobSelect(MilBlobResult, M_EXCLUDE, M_AREA, M_LESS_OR_EQUAL, 1000, M_NULL);
#ifdef  _M_X64
	LONG64 iTotalBlobs = 0;
#else 
	long iTotalBlobs = 0;
#endif
	
	MblobGetNumber(MilBlobResult, &iTotalBlobs);

	//MbufSave("D:/test5.bmp", vision.MilProcImageChild[iCh]);
	MbufSave("D:/test6.bmp", MilBinaryImage);

	if ( iTotalBlobs < 1 )
	{
		sLangChange.LoadStringA(IDS_STRING1208);		//레진 위치를 찾지 못했습니다.
		sMsg.Format(sLangChange);
		errMsg2(Task.AutoFlag, sMsg);

		vision.drawOverlay(iCh);

		return -1;
	}

	if ( iTotalBlobs > 1 )
	{
		sLangChange.LoadStringA(IDS_STRING1411);	//찾은 레진 위치가 많습니다. ( %d )
		sMsg.Format(sLangChange, iTotalBlobs);
		errMsg2(Task.AutoFlag, sMsg);

		vision.drawOverlay(iCh);

		return -1;
	}

	MblobGetResult(MilBlobResult, M_CENTER_OF_GRAVITY_X, &m_dCogX);
	MblobGetResult(MilBlobResult, M_CENTER_OF_GRAVITY_Y, &m_dCogY);

	//vision.crosslist[1].addList((int)(m_dCogX + 0.5), (int)(m_dCogY + 0.5), 100, M_COLOR_GREEN);
	vision.crosslist[iCh].addList((int)(m_dCogX), (int)(m_dCogY), 100, M_COLOR_GREEN);
	if(m_radio == 0)
	{
		vision.crosslist[iCh].addList((int)(model.m_EpoxyBaseP.x), (int)(model.m_EpoxyBaseP.y), 100, M_COLOR_RED);
	}
	else if(m_radio == 1)
	{
		vision.crosslist[iCh].addList((int)(model.m_Epoxy2BaseP.x), (int)(model.m_Epoxy2BaseP.y), 100, M_COLOR_RED);
	}

	sMsg.Format("X : %.2lf Y %.2lf", m_dCogX, m_dCogY);
	vision.textlist[iCh].addList(100, 100, sMsg, M_COLOR_RED, 16, 12, "Arial");

	MbufFree(MilBlobResult);
	MilBlobResult = M_NULL;

	MbufFree(MilBlobFeatureList);
	MilBlobFeatureList = M_NULL;

	MbufFree(MilBinaryImage);
	MilBinaryImage = M_NULL;

	GlobalUnlock(pucImage);
#endif
	return 1;
}
void CPcbDlg::OnStnClickedEditCleanPos()
{
	CString celData;

	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		int i_num = atoi(dlg.GetstrNum());
		celData.Format("%d", (i_num));
		GetDlgItem(IDC_EDIT_CLEAN_POS)->SetWindowText(celData);
	}	
}


void CPcbDlg::OnBnClickedButtonChoiceEpoxy()
{
	if( !func_TaskMovingCheck() )	return;

	//! 선택된 위치 일단 그려줌.
	vision.clearOverlay();

	int inspSize = 200;
	int iSx = CAM_SIZE_X/4 - inspSize + 100;
	int iEx = CAM_SIZE_X/4 + inspSize + 100;
	int iSy = CAM_SIZE_Y/2 - inspSize - 40;
	int iEy = CAM_SIZE_Y/2 + inspSize - 110;

	vision.boxlist[CAM1].addList(iSx, iSy, iEx, iEy, PS_DOT, M_COLOR_RED);

	if(m_radio == 0)
	{
	vision.crosslist[CAM1].addList((int)(Task.cpMEpoxyPos.x), (int)(Task.cpMEpoxyPos.y), 100, M_COLOR_GREEN);
	vision.crosslist[CAM1].addList((int)(model.m_EpoxyBaseP.x), (int)(model.m_EpoxyBaseP.y), 100, M_COLOR_RED);
	}
	else if(m_radio == 1)
	{
	vision.crosslist[CAM1].addList((int)(Task.cpMEpoxyPos.x), (int)(Task.cpMEpoxyPos.y), 100, M_COLOR_GREEN);
	vision.crosslist[CAM1].addList((int)(model.m_Epoxy2BaseP.x), (int)(model.m_Epoxy2BaseP.y), 100, M_COLOR_RED);
	}

	vision.drawOverlay(CAM1);
	//!!!!

	CString sTemp;
	sLangChange.LoadStringA(IDS_STRING1445);	//화면에 선택 된 위치로 계산 하시겠습니까?
	sTemp.Format(sLangChange);
	if( !askMsg(sTemp.GetBuffer(99)) )
	{
		return;
	}

	m_dCogX = Task.cpMEpoxyPos.x;
	m_dCogY = Task.cpMEpoxyPos.y;

	if ( CalcEpoxyOffset() < 0 )
	{
		sLangChange.LoadStringA(IDS_STRING1199);	//도포 보정값 계산 실패
		errMsg2(Task.AutoFlag, sLangChange);
		return;
	}

	PutEpoxyDataOnEdit();
	
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	CString sLog;
	sLangChange.LoadStringA(IDS_STRING546);	//Epoxy 보정값 계산 완료 X:%.03f, Y:%.03f
	sLog.Format(sLangChange, m_dOffsetX, m_dOffsetY);
	pFrame->putListLog(sLog);

	m_iBaseX = (int)(m_dCogX+0.5);
	m_iBaseY = (int)(m_dCogY+0.5);

	m_dCogX = m_dCogY = 0;
	Task.bManual_FindEpoxy = false;
}


void CPcbDlg::OnBnClickedButtonMotorLbond()
{
	if( !func_TaskMovingCheck() )	return;

	/* 이동중이면 Return */
	g_bMovingflag =true;

	//if( !Dio.PCBDarkCheck(true, false) )
	//{//Dark 검사 실린더 하강일 경우 상승
	//	if( !Dio.PCBDark(true, true) )
	//	{
	//		sLangChange.LoadStringA(IDS_STRING488);	//Dark검사 실린더 상승 실패.
	//		delayMsg(sLangChange, 1000, M_COLOR_RED);
	//		g_bMovingflag =false;
	//		return;
	//	}
	//}

	if(!motor.LENS_Z_Motor_Move(Wait_Pos))
	{
		sLangChange.LoadStringA(IDS_STRING739);	//Lens_Z축 대기위치 이동 실패.
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		g_bMovingflag =false;
		return;
	}
	if(!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		sLangChange.LoadStringA(IDS_STRING1012);	//PCB_Z축 대기위치 이동 실패.
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		g_bMovingflag =false;
		return;
	}

	CString sTmpLog;
	if(!motor.Pcb_Motor_Move(Holder_Uv_Pos))
	{
		sLangChange.LoadStringA(IDS_STRING898);	//"PCB %s 이동 실패"
		sTmpLog.Format(sLangChange, MotorPosName[Holder_Uv_Pos]);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_RED);
	}
	sLangChange.LoadStringA(IDS_STRING899);	//"PCB %s 이동 완료"
	sTmpLog.Format(sLangChange, MotorPosName[Holder_Uv_Pos]);
	delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
	g_bMovingflag =false;
}


void CPcbDlg::OnBnClickedButtonMotorRbond()
{
	if( !func_TaskMovingCheck() )	return;

	/* 이동중이면 Return */
	g_bMovingflag =true;

	//if( !Dio.PCBDarkCheck(true, false) )
	//{//Dark 검사 실린더 하강일 경우 상승
	//	if( !Dio.PCBDark(true, true) )
	//	{
	//		sLangChange.LoadStringA(IDS_STRING488);	//Dark검사 실린더 상승 실패.
	//		delayMsg(sLangChange, 1000, M_COLOR_RED);
	//		g_bMovingflag =false;
	//		return;
	//	}
	//}

	if(!motor.LENS_Z_Motor_Move(Wait_Pos))
	{
		sLangChange.LoadStringA(IDS_STRING739);	//Lens_Z축 대기위치 이동 실패.
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		g_bMovingflag =false;
		return;
	}
	if(!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		sLangChange.LoadStringA(IDS_STRING1012);	//PCB_Z축 대기위치 이동 실패.
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		g_bMovingflag =false;
		return;
	}



}


void CPcbDlg::OnBnClickedButtonZMotorLdispense()
{
	
	if( !func_TaskMovingCheck() )	return;

	/* 이동중이면 Return */
	g_bMovingflag =true;

	//if( !Dio.PCBDarkCheck(true, false) )
	//{//Dark 검사 실린더 하강일 경우 상승
	//	if( !Dio.PCBDark(true, true) )
	//	{
	//		sLangChange.LoadStringA(IDS_STRING488);	//Dark검사 실린더 상승 실패.
	//		delayMsg(sLangChange, 1000, M_COLOR_RED);
	//		g_bMovingflag =false;
	//		return;
	//	}
	//}

	motor.PCB_Z_Motor_Move(Holder_Uv_Pos);

	g_bMovingflag =false;

}


void CPcbDlg::OnBnClickedButtonLepoxy()
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

	if ( !checkCurMotorPos(Holder_Uv_Pos) )
	{
		delayMsg("Epoxy 왼쪽 직선 기준위치 이동 후 진행하세요.", 2000, M_COLOR_RED);
		return;
	}

	CString sTmpLog;
	/* 이동중이면 Return */
	if(g_bMovingflag)		return;
	g_bMovingflag =true;

	if(!motor.LENS_Z_Motor_Move(Wait_Pos))
	{
		g_bMovingflag =false;
		return;
	}
	if(!motor.PCB_Z_Motor_Move(Holder_Uv_Pos))
	{
		g_bMovingflag =false;
		return;
	}

	CString sTempLog;

	motor.func_Epoxy_Left_StraightDraw();

	sTmpLog.Format("PCB 왼쪽 직선 도포 완료");
	delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);

	if(!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		g_bMovingflag =false;
		return;
	}

	g_bMovingflag =false;
}


void CPcbDlg::OnBnClickedButtonRepoxy()
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

}

void CPcbDlg::OnBnClickedButtonMotorSensorContactPos2()
{
	if( !func_TaskMovingCheck() )	return;

	/* 이동중이면 Return */
	g_bMovingflag =true;

	//if( !Dio.PCBDarkCheck(true, false) )
	//{//Dark 검사 실린더 하강일 경우 상승
	//	if( !Dio.PCBDark(true, true) )
	//	{
	//		sLangChange.LoadStringA(IDS_STRING488);	//Dark검사 실린더 상승 실패.
	//		delayMsg(sLangChange, 1000, M_COLOR_RED);
	//		g_bMovingflag =false;
	//		return;
	//	}
	//}

	if(!motor.LENS_Z_Motor_Move(Wait_Pos))
	{
		g_bMovingflag =false;
		return;
	}
	if(!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		g_bMovingflag =false;
		return;
	}


	g_bMovingflag =false;
}


void CPcbDlg::OnBnClickedButtonMotorExpoxyTargetPos2()
{
	if( !func_TaskMovingCheck() )	return;

	/* 이동중이면 Return */
	g_bMovingflag =true;

	//if( !Dio.PCBDarkCheck(true, false) )
	//{//Dark 검사 실린더 하강일 경우 상승
	//	if( !Dio.PCBDark(true, true) )
	//	{
	//		sLangChange.LoadStringA(IDS_STRING488);	//Dark검사 실린더 상승 실패.
	//		delayMsg(sLangChange, 1000, M_COLOR_RED);
	//		g_bMovingflag =false;
	//		return;
	//	}
	//}

	if(!motor.LENS_Z_Motor_Move(Wait_Pos))
	{
		g_bMovingflag =false;
		return;
	}
	if(!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		g_bMovingflag =false;
		return;
	}

	if(motor.Pcb_Motor_Move(Calc2_Pos))
	{
		if( motor.PCB_Z_Motor_Move(Calc2_Pos) )
		{
			CString sTmpLog;
			sLangChange.LoadStringA(IDS_STRING899);	//"PCB %s 이동 완료"
			sTmpLog.Format(sLangChange, MotorPosName[Calc2_Pos]);
			delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
		}
	}

	g_bMovingflag =false;
}

afx_msg void CPcbDlg::RadioCtrl(UINT ID)
{
	switch(ID)
	{
	case IDC_RADIO_CIRCLE:
		m_radio = 0;
		break;
	case IDC_RADIO_LINE:
		m_radio = 1;
		break;
	default:
		break;
	}
	return afx_msg void();
}


//void CPcbDlg::OnBnClickedButtonEcalSave22()
//{
//	model.Load();
//	sysData.Load();
//	double dGetmotorX = 0;
//	double dGetmotorY = 0;
//	CString sLog;
//	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
//
//	dGetmotorX = motor.GetEncoderPos_Disp(0);
//	dGetmotorY = motor.GetEncoderPos_Disp(1);
//	model.axis[Motor_PCB_X].pos[Calc_Pos] = dGetmotorX + sysData.dDataset[0];
//	model.axis[Motor_PCB_Y].pos[Calc_Pos] = dGetmotorY + sysData.dDataset[1];
//
//	model.Save();
//	model.Load();
//	sLog.Format("Epoxy Calc Postion Teaching Save Complete");
//	pFrame->putListLog(sLog);
//
//	::Sleep(300);
//
//	double dCalcX = 7.116;
//	double dCalcY = 23.091;
//	if(model.m_dEpoxyOffsetX == 0 && model.m_dEpoxyOffsetY == 0)
//	{
//		model.axis[Motor_PCB_X].pos[Dispense_Pos] = model.axis[Motor_PCB_X].pos[Calc_Pos] + dCalcX;//model.m_dEpoxyOffsetX;
//		model.axis[Motor_PCB_Y].pos[Dispense_Pos] = model.axis[Motor_PCB_Y].pos[Calc_Pos] + dCalcY;//model.m_dEpoxyOffsetY;
//	}
//	else
//	{
//		model.axis[Motor_PCB_X].pos[Dispense_Pos] = model.axis[Motor_PCB_X].pos[Calc_Pos] + model.m_dEpoxyOffsetX;
//		model.axis[Motor_PCB_Y].pos[Dispense_Pos] = model.axis[Motor_PCB_Y].pos[Calc_Pos] + model.m_dEpoxyOffsetY;
//	}
//	model.Save();
//	model.Load();
//
//	sLangChange.LoadStringA(IDS_STRING546);
//	sLog.Format(sLangChange, dCalcX, dCalcY);//model.m_dEpoxyOffsetX, model.m_dEpoxyOffsetY);
//	pFrame->putListLog(sLog);
//
//}


void CPcbDlg::OnBnClickedButtonEcalSave()
{
	CString sTemp;
	model.Load();
	double dGetmotorX = 0;
	double dGetmotorY = 0;
	double dGetCalcX = 0;
	double dGetCalcY = 0;
	CString sLog,sTemp1,sTemp2,sMsg,sLangChange;
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	double dOffsetCalcPosX = 0.000;
	double dOffsetCalcPosY = 0.000;
	//dCurPos		= motor.GetEncoderPos(i);	//motor.GetCommandPos(i);
	dGetmotorX = motor.GetEncoderPos_Disp(Motor_PCB_X);//motor.GetEncoderPos(Motor_PCB_X);//
	dGetmotorY = motor.GetEncoderPos_Disp(Motor_PCB_Y);//motor.GetEncoderPos(Motor_PCB_X);//

	dGetCalcX = (-sysData.dDataset[Motor_PCB_X]+model.axis[Motor_PCB_X].pos[Calc_Pos]); 
	dGetCalcY = (-sysData.dDataset[Motor_PCB_Y]+model.axis[Motor_PCB_Y].pos[Calc_Pos]);

	dOffsetCalcPosX = dGetmotorX - dGetCalcX;
	dOffsetCalcPosY = dGetmotorY - dGetCalcY;
	//(5 - 6)= -1 , (-5 - -6)= 1 (
	if(fabs(dOffsetCalcPosX) > 5 || fabs(dOffsetCalcPosY) > 5)
	{
		sTemp.Format(_T("현재값이 기존값에서 5mm이상 벗어나있습니다.\n다시 확인하세요."));
		errMsg2(Task.AutoFlag, sTemp);
		return;
	}


//////////////////////////////////
	sTemp1 = "CAL POS위치를 현재 위치로 재 지정 하시겠습니까? \n";
	sLangChange.Format("현재 X(%.3lf),Y(%.3lf)  ,  기존 X(%.3lf),Y(%.3lf)",dGetmotorX,dGetmotorY,dGetCalcX,dGetCalcY);
	//sLangChange.Format("현재 X(%.3lf),Y(%.3lf)  ,  기존 X(%.3lf),Y(%.3lf)",dGetmotorX,dGetmotorY,model.axis[Motor_PCB_X].pos[Calc_Pos],model.axis[Motor_PCB_Y].pos[Calc_Pos]);
	sTemp2.Format(sLangChange);

	sMsg = sTemp1 + sTemp2;

	if ( askMsg(sMsg) == true )
	{


		model.axis[Motor_PCB_X].pos[Calc_Pos] = motor.GetEncoderPos(Motor_PCB_X);//dGetmotorX;// + sysData.dDataset[0];
		model.axis[Motor_PCB_Y].pos[Calc_Pos] = motor.GetEncoderPos(Motor_PCB_Y);//dGetmotorY;// + sysData.dDataset[1];

		model.axis[Motor_PCB_X].pos[Dispense_Pos] += dOffsetCalcPosX;//model.m_dEpoxyOffsetX;
		model.axis[Motor_PCB_Y].pos[Dispense_Pos] += dOffsetCalcPosY;//model.m_dEpoxyOffsetY;

		model.axis[Motor_PCB_X].pos[Contact_Pos] += dOffsetCalcPosX;//model.m_dEpoxyOffsetX;
		model.axis[Motor_PCB_Y].pos[Contact_Pos] += dOffsetCalcPosY;//model.m_dEpoxyOffsetY; 

		

		model.Save();
		model.Load();
		sLog.Format("Epoxy Calc Postion Teaching Save Complete");
		pFrame->putListLog(sLog);
	}
//////////////////////////////////


	//Sleep(300);



	//if(model.m_dEpoxyOffsetX == 0 && model.m_dEpoxyOffsetY == 0)
	//{
	//	model.axis[Motor_PCB_X].pos[Dispense_Pos] = model.axis[Motor_PCB_X].pos[Calc_Pos] + dCalcX;//model.m_dEpoxyOffsetX;
	//	model.axis[Motor_PCB_Y].pos[Dispense_Pos] = model.axis[Motor_PCB_Y].pos[Calc_Pos] + dCalcY;//model.m_dEpoxyOffsetY;
	//}
	//else
	//{
	//	model.axis[Motor_PCB_X].pos[Dispense_Pos] = model.axis[Motor_PCB_X].pos[Calc_Pos] + model.m_dEpoxyOffsetX;
	//	model.axis[Motor_PCB_Y].pos[Dispense_Pos] = model.axis[Motor_PCB_Y].pos[Calc_Pos] + model.m_dEpoxyOffsetY;
	//}

	//model.Save();
	//model.Load();

	//sLangChange.LoadStringA(IDS_STRING546);
	//sLog.Format(sLangChange, dCalcX, dCalcY);//model.m_dEpoxyOffsetX, model.m_dEpoxyOffsetY);
	//pFrame->putListLog(sLog);

}


void CPcbDlg::OnBnClickedButtonLaserLiftUp()
{
	if( !func_TaskMovingCheck() )	return;
	if ( !checkCurMotorPos(Wait_Pos) )
	{
		delayMsg("Do not Wait_Pos", 2000, M_COLOR_RED);
		return;
	}
	g_bMovingflag = true;

	//Dio.CamLaserSlinderMove(true, false);
	g_bMovingflag = false;
}


void CPcbDlg::OnBnClickedButtonLaserLiftDown()
{
	if( !func_TaskMovingCheck() )	return; 

	/*if(!checkCurLensMotorPos(Laser_Lens_Pos))
	{
		delayMsg("PCB Not Laser_Pos", 2000, M_COLOR_RED);
		return;
	}*/
	g_bMovingflag = true;
	//Dio.CamLaserSlinderMove(false, false);
	g_bMovingflag = false;
}


void CPcbDlg::changeColorLaserBtn()
{
	if (Dio.CamLaserSlinderCheck(true, false))
	{
		m_btnLaserLiftUp.m_iStateBtn = 1;
	}
	else
	{
		m_btnLaserLiftUp.m_iStateBtn = 0;
	}


	if (Dio.CamLaserSlinderCheck(false, false))
	{
		m_btnLaserLiftDown.m_iStateBtn = 1;
	}
	else
	{
		m_btnLaserLiftDown.m_iStateBtn = 0;
	}

	m_btnLaserLiftUp.Invalidate();
	m_btnLaserLiftDown.Invalidate();
}

void CPcbDlg::changeColorLaserCylinderLaserTabBtn()
{
	/*bool flag = false;
	bool flag2 = false;
	flag = Dio.LaserCylinderCheck(true, false);

	if (flag)
	{
		m_btn_Laser_CylUp_LaserTab.m_iStateBtn = 1;
		m_btn_Laser_CylDown_LaserTab.m_iStateBtn = 0;
	}
	else
	{
		m_btn_Laser_CylUp_LaserTab.m_iStateBtn = 0;
		flag2 = Dio.LaserCylinderCheck(false, false);
		if (flag2)
		{
			m_btn_Laser_CylUp_LaserTab.m_iStateBtn = 0;
			m_btn_Laser_CylDown_LaserTab.m_iStateBtn = 1;
		}
		else
		{
			m_btn_Laser_CylDown_LaserTab.m_iStateBtn = 0;
		}

	}

	m_btn_Laser_CylUp_LaserTab.Invalidate();
	m_btn_Laser_CylDown_LaserTab.Invalidate();*/
}

void CPcbDlg::OnBnClickedButtonVaccumSol()
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
}

void CPcbDlg::changeColorVaccumSolBtn()
{
	/*int moduleNo = 2;
	int channelNo = 0;

	bool bOutOpenFlag;

	bOutOpenFlag = (curOutDioByte[moduleNo][channelNo] & DIO_OUT_VACUUM_SOL) ? true : false;

	if (bOutOpenFlag)
	{
		m_btnVaccumSol.m_iStateBtn	= 1;
	}
	else
	{
		m_btnVaccumSol.m_iStateBtn	= 0;
	}

	m_btnVaccumSol.Invalidate();*/
}

void CPcbDlg::OnBnClickedButtonZMotorLaser()
{ 
	if( !func_TaskMovingCheck() )	return;

	/* 이동중이면 Return */
	g_bMovingflag =true;

	motor.LENS_Z_Motor_Move(Laser_Lens_Pos);

	g_bMovingflag =false;
}


void CPcbDlg::OnBnClickedButtonMotorResinPos()
{
	
}


void CPcbDlg::OnEnChangeEditOffsetX()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CPcbDlg::OnBnClickedButtonMotorExpoxyTargetZ()
{
	if( !func_TaskMovingCheck() )	return;

	/* 이동중이면 Return */
	if ( !checkCurMotorPos(Calc_Pos) )
	{
		delayMsg("Calc_Pos 위치이동 후 진행하세요", 3000, M_COLOR_RED);
		return;
	}
	g_bMovingflag =true;

	if(!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		g_bMovingflag =false;
		return;
	}
	if( motor.PCB_Z_Motor_Move(Calc_Pos))
	{
		CString sTmpLog;
		sLangChange.LoadStringA(IDS_STRING899);	//"PCB %s 이동 완료"
		sTmpLog.Format(sLangChange, MotorPosName[Calc_Pos]);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
	}
	g_bMovingflag =false; 
}






void CPcbDlg::OnBnClickedButtonEpoxyRoi()
{
	//Dio.EpoxyDischargeOn(false, false/*true*/);
	CEpoxyDlg EpoxyDlg;
	EpoxyDlg.DoModal();
	/*
	도포검사 영역
	CResinRoiDlg roidlg;
	roidlg.DoModal();
	*/
}


void CPcbDlg::OnBnClickedButtonMotorSensorContactZpos()
{
	UpdateData(true);

	if( !func_TaskMovingCheck() )	return;

	/*이동중이면 Return */
	if ( !checkCurMotorPos(Contact_Pos) )
	{
		delayMsg("Contact_Pos 위치이동 후 진행하세요", 3000, M_COLOR_RED);
		return;
	}

	g_bMovingflag =true;

	if( !motor.PCB_Z_Motor_Move(Contact_Pos) )
	{
		delayMsg("Contact_Pos위치 하강 실패.", 1000, M_COLOR_RED);
		g_bMovingflag =false;
		return;
	}

	g_bMovingflag =false;
}





void CPcbDlg::OnBnClickedButtonZMotorHolder()
{
	if( !func_TaskMovingCheck() )	return;

	/* 이동중이면 Return */
	if ( !checkCurMotorPos(Holder_Pos) )
	{
		delayMsg("Do not Holder_Pos", 2000, M_COLOR_RED);
		return;
	}
	g_bMovingflag =true;
	if(!motor.PCB_Z_Motor_Move(Holder_Pos))
	{
		sLangChange.Format("PCB Z axis Holder_Pos Move Failed");
		delayMsg(sLangChange, 1000, M_COLOR_RED);
	}

	g_bMovingflag =false;
}


void CPcbDlg::OnBnClickedButtonMotorHolder()
{
	if( !func_TaskMovingCheck() )	return;

	/* 이동중이면 Return */
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
	if(motor.Pcb_Motor_Move(Holder_Pos))
	{
		CString sTmpLog;
		sLangChange.LoadStringA(IDS_STRING899);	//"PCB %s 이동 완료"
		sTmpLog.Format(sLangChange, MotorPosName[Holder_Pos]);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
	}
	g_bMovingflag =false;
}


void CPcbDlg::OnBnClickedButtonEpoxyRoiView()
{
	//LightControl.ctrlLedVolume(LIGHT_PCB, model.m_iLedValue[LEDDATA_EPOXY_INSP]);

	drawRectEpoxyInsp();
	//drawRect_Circle_EpoxyInsp();
	//drawCircleEpoxyInsp();

	return;
}


void CPcbDlg::OnBnClickedButtonMotorContiEpoxy()
{
	if (!func_TaskMovingCheck())	return;

	/* 이동중이면 Return */
	if (!func_MovingInterlock())
	{
		return;
	}
	g_bMovingflag = true;
	CString sTmpLog = "";
	if (!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		sLangChange.Format("PCB Z axis Wait_Pos Move Failed");
		delayMsg(sLangChange, 1000, M_COLOR_RED);
	}
	if (!motor.Pcb_Motor_Move(Com_Laser_Pos, Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]))
	{
		sLangChange.LoadStringA(IDS_STRING898);	//"PCB %s 이동 실패"
		sTmpLog.Format(sLangChange, MotorPosName[Com_Laser_Pos]);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_RED);
	}
	sLangChange.LoadStringA(IDS_STRING899);	//"PCB %s 이동 완료"
	sTmpLog.Format(sLangChange, MotorPosName[Com_Laser_Pos]);
	delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
	g_bMovingflag = false;
}


void CPcbDlg::OnBnClickedButtonZMotorContiEpoxy()
{
	if (!func_TaskMovingCheck())	return;

	/* 이동중이면 Return */

	if (!checkCurMotorPos(Com_Laser_Pos))
	{
		delayMsg("Do not Com_Laser_Pos", 2000, M_COLOR_RED);
		return;
	}
	g_bMovingflag = true;

	if (!motor.PCB_Z_Motor_Move(Com_Laser_Pos))
	{
		sLangChange.Format("PCB Z axis Com_Laser_Pos Move Failed");
		delayMsg(sLangChange, 1000, M_COLOR_RED);
	}
	g_bMovingflag = false;
}


void CPcbDlg::OnBnClickedButtonSmallEpoxy()
{
	CString logStr = "";


	if (Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	if (Task.AutoFlag == 2)
	{
		sLangChange.LoadStringA(IDS_STRING1468);
		delayMsg(sLangChange, 2000, M_COLOR_RED);// 일시 정지 중 사용 불가
		return;
	}

	if (!checkCurMotorPos(PDispense_Pos))
	{
		logStr.Format("PDispense_Pos not Pos");
		delayMsg(logStr, 2000, M_COLOR_RED);
		return;
	}

	/* 이동중이면 Return */
	if (g_bMovingflag)		return;
	g_bMovingflag = true;

	if (!motor.PCB_Z_Motor_Move(PDispense_Pos))
	{
		g_bMovingflag = false;
		return;
	}


	CString sTempLog = "";

	//model.Load();

	//motor.func_Epoxy_Point_Draw();
	//motor.func_Trinity_Epoxy_Rect_Draw();		//
	//motor.func_New_Epoxy_Rect_Arck_Draw();	//


	if (!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		g_bMovingflag = false;
		return;
	}


	/*if (!motor.Pcb_Motor_Move(Wait_Pos))
	{
		g_bMovingflag = false;
		return;
	}*/

	sTempLog.Format("PCB 도포 구동 완료");
	delayMsg(sTempLog.GetBuffer(99), 3000, M_COLOR_GREEN);

	g_bMovingflag = false;
	logStr.Empty();
}


void CPcbDlg::OnEnChangeEditOffsetY()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CPcbDlg::OnBnClickedButtonMotorPdispensePos()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!func_TaskMovingCheck())	return;

	/* 이동중이면 Return */
	if (!func_MovingInterlock())
	{
		return;
	}
	g_bMovingflag = true;
	CString sTmpLog = "";
	if (!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		sLangChange.Format("PCB Z axis Wait_Pos Move Failed");
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		g_bMovingflag = false;
		return;
	}

	if (!motor.Pcb_Motor_Move(PDispense_Pos))//,0.0,0.0,0.0))
	{


		sLangChange.LoadStringA(IDS_STRING898);	//"PCB %s 이동 실패"
		sTmpLog.Format(sLangChange, MotorPosName[PDispense_Pos]);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_RED);
		g_bMovingflag = false;
		return;
	}
	if (!motor.Pcb_Tilt_Motor_Move(PDispense_Pos))
	{
		g_bMovingflag = false;
		return;
	}
	sLangChange.LoadStringA(IDS_STRING899);	//"PCB %s 이동 완료"
	sTmpLog.Format(sLangChange, MotorPosName[PDispense_Pos]);
	delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
	g_bMovingflag = false;
}


void CPcbDlg::OnBnClickedButtonZMotorPdispensePos()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!func_TaskMovingCheck())	return;

	/* 이동중이면 Return */

	if (!checkCurMotorPos(PDispense_Pos))
	{
		delayMsg("Do not PDispense_Pos", 2000, M_COLOR_RED);
		return;
	}

	g_bMovingflag = true;

	if (!motor.PCB_Z_Motor_Move(PDispense_Pos))
	{
		sLangChange.Format("PCB Z axis PDispense_Pos Move Failed");
		delayMsg(sLangChange, 1000, M_COLOR_RED);
	}
	g_bMovingflag = false;
}


void CPcbDlg::OnBnClickedButtonLaserCylUpLasertab()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!func_TaskMovingCheck())	return;
	if (!checkCurMotorPos(Wait_Pos))
	{
		delayMsg("Do not Wait_Pos", 2000, M_COLOR_RED);
		return;
	}
	g_bMovingflag = true;

	Dio.CamLaserSlinderMove(true, false);

	g_bMovingflag = false;
}


void CPcbDlg::OnBnClickedButtonLaserCylDownLasertab()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!func_TaskMovingCheck())	return;

	/*if(!checkCurLensMotorPos(Laser_Out_Pos))
	{
	delayMsg("PCB Not Laser_Pos", 2000, M_COLOR_RED);
	return;
	}*/
	g_bMovingflag = true;
	Dio.CamLaserSlinderMove(false, false);

	g_bMovingflag = false;
}


void CPcbDlg::OnBnClickedButtonSmallCircleEpoxy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString logStr = "";


	if (Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	if (Task.AutoFlag == 2)
	{
		sLangChange.LoadStringA(IDS_STRING1468);
		delayMsg(sLangChange, 2000, M_COLOR_RED);// 일시 정지 중 사용 불가
		return;
	}

	if (!checkCurMotorPos(Dispense_Pos2))
	{
		logStr.Format("Dispense_Pos2 not Pos");
		delayMsg(logStr, 2000, M_COLOR_RED);
		return;
	}

	/* 이동중이면 Return */
	if (g_bMovingflag)		return;
	g_bMovingflag = true;

	if (!motor.PCB_Z_Motor_Move(Dispense_Pos2))
	{
		g_bMovingflag = false;
		return;
	}


	CString sTempLog = "";

	model.Load();

	//motor.func_Epoxy_Point_Draw();

	motor.func_Trinity_Epoxy_Circle_Draw();

	if (!motor.PCB_Z_Motor_Move(Wait_Pos)) 
	{
		g_bMovingflag = false;
		return;
	}


	/*if (!motor.Pcb_Motor_Move(Wait_Pos))
	{
	g_bMovingflag = false; 
	return;
	}*/

	sTempLog.Format("PCB 도포 구동 완료");
	delayMsg(sTempLog.GetBuffer(99), 3000, M_COLOR_GREEN);

	g_bMovingflag = false;
}


void CPcbDlg::OnBnClickedButtonMotorTdispensePos()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (!func_TaskMovingCheck())	return;

	/* 이동중이면 Return */
	if (!func_MovingInterlock())
	{
		return;
	}
	g_bMovingflag = true;
	CString sTmpLog = "";
	if (!motor.PCB_Z_Motor_Move(Wait_Pos))
	{
		sLangChange.Format("PCB Z axis Wait_Pos Move Failed");
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		g_bMovingflag = false;
		return;
	}

	if (!motor.Pcb_Motor_Move(Dispense_Pos2))//,0.0,0.0,0.0))
	{


		sLangChange.LoadStringA(IDS_STRING898);	//"PCB %s 이동 실패"
		sTmpLog.Format(sLangChange, MotorPosName[Dispense_Pos2]);
		delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_RED);
		g_bMovingflag = false;
		return;
	}
	if (!motor.Pcb_Tilt_Motor_Move(Dispense_Pos2))
	{
		g_bMovingflag = false;
		return;
	}
	sLangChange.LoadStringA(IDS_STRING899);	//"PCB %s 이동 완료"
	sTmpLog.Format(sLangChange, MotorPosName[Dispense_Pos2]);
	delayMsg(sTmpLog.GetBuffer(99), 3000, M_COLOR_GREEN);
	g_bMovingflag = false;
}


void CPcbDlg::OnBnClickedButtonZMotorTdispensePos()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (!func_TaskMovingCheck())	return;

	/* 이동중이면 Return */

	if (!checkCurMotorPos(Dispense_Pos2))
	{
		delayMsg("Do not Dispense_Pos2", 2000, M_COLOR_RED);
		return;
	}

	g_bMovingflag = true;

	if (!motor.PCB_Z_Motor_Move(Dispense_Pos2))
	{
		sLangChange.Format("PCB Z axis Dispense_Pos2 Move Failed"); 
		delayMsg(sLangChange, 1000, M_COLOR_RED);
	}
	g_bMovingflag = false;
}


void CPcbDlg::OnBnClickedButtonInspXMotorWait()
{
	CString sTmpLog;
	if (!func_TaskMovingCheck())	return;

	/* 이동중이면 Return */
	if (!func_MovingInterlock())
	{
		return;
	}

}


void CPcbDlg::OnBnClickedButtonInspXMotorHolder()
{
	if (!func_TaskMovingCheck())	return;

	/* 이동중이면 Return */
	if (!func_MovingInterlock())
	{
		return;
	}

}


void CPcbDlg::OnBnClickedButtonInspXMotorBond()
{
	if (!func_TaskMovingCheck())	return;

	/* 이동중이면 Return */
	if (!func_MovingInterlock())
	{
		return;
	}
	
}


void CPcbDlg::OnBnClickedButtonInspXMotorPdispensePos()
{
	if (!func_TaskMovingCheck())	return;

	/* 이동중이면 Return */
	if (!func_MovingInterlock())
	{
		return;
	}
	
}


void CPcbDlg::OnBnClickedButtonInspXMotorTdispensePos()
{
	if (!func_TaskMovingCheck())	return;

	/* 이동중이면 Return */
	if (!func_MovingInterlock())
	{
		return;
	}
}


void CPcbDlg::OnBnClickedButtonEpoxyWeight()
{
	// TODO: Add your control notification handler code here
	CString logStr = "";
	if (Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	if (Task.AutoFlag == 2)
	{
		sLangChange.LoadStringA(IDS_STRING1468);
		delayMsg(sLangChange, 2000, M_COLOR_RED);// 일시 정지 중 사용 불가
		return;
	}

	if (!checkCurMotorPos(Dispense_Pos))
	{
		sLangChange.LoadStringA(IDS_STRING542);	//Epoxy 기준위치 이동 후 진행하세요.
		delayMsg(sLangChange, 2000, M_COLOR_RED);
		return;
	}

	/* 이동중이면 Return */
	if (g_bMovingflag)		return;
	g_bMovingflag = true;

	if (!motor.PCB_Z_Motor_Move(Dispense_Pos1))
	{
		g_bMovingflag = false;
		return;
	}

	model.Load();

	theApp.MainDlg->MainEpoxyRun();


	return;
}
