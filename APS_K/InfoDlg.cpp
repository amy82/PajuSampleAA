// InfoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "InfoDlg.h"


// CInfoDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CInfoDlg, CDialogEx)

CInfoDlg::CInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInfoDlg::IDD, pParent)
	, m_bDicChange(FALSE)
	, m_bIrChartUse(FALSE)
	, m_bLaserInsp(FALSE)
	, m_bStainInspPass(FALSE)
    , m_bDefectInspPass(FALSE)
	, m_b1stAaEnable(FALSE)
	, chk_Dispense(FALSE)
	, chk_UvMTFInsp(FALSE)
	, chk_DispenseInsp(FALSE)
	, chk_PriductComp(FALSE)
	, m_sMES_IP(_T(""))
	, m_sMES_Factory(_T(""))
	, m_nMTF_INSP_Cnt(0)
	, bCircle(false)
	, bDistortionCenter(false)
	, m_RESIVION_NO(0)
	, chk_front(FALSE)
	, m_AARoiSelect(0)
	, chk_AUTO_Z_SEARCH(FALSE)
	, m_bAlignCamInsp(FALSE)
	, m_bSfrMaxValueInsp(FALSE)
{

	m_iAlignMode = 0;
}

CInfoDlg::~CInfoDlg()
{
}

void CInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_PASS_UV, m_bPassUV);
	DDX_Check(pDX, IDC_CHECK_STAIN_INSP, m_bStainInspPass);
	DDX_Check(pDX, IDC_CHECK_DEFECT_INSP, m_bDefectInspPass);//m_bDarkInsp);

	DDX_Check(pDX, IDC_CHECK_LASER_PCB, m_bEpoxyLaserInspPass);

	DDX_Check(pDX, IDC_CHECK_LASER_INSP, m_bLaserInsp);
	DDX_Check(pDX, IDC_CHECK_XY_CHANGE, m_bDicChange);
	DDX_Check(pDX, IDC_CHECK_IR_CHART_USE, m_bIrChartUse);
	
	DDX_Check(pDX, IDC_CHECK_SFR_MAX_TEST, m_bSfrMaxValueInsp);

	DDX_Check(pDX, IDC_CHECK_PASS_ALIGN_CAM, m_bAlignCamInsp);
	//
	DDX_Check(pDX, IDC_CHECK_1ST_AA_ENABLE, m_b1stAaEnable);
	DDX_Check(pDX, IDC_CHECK_PASS_DISPENSE, chk_Dispense);
	DDX_Check(pDX, IDC_CHECK_UV_INSP, chk_UvMTFInsp);

	DDX_Check(pDX, IDC_CHECK_PASS_DISPENSE_INSP, chk_DispenseInsp);
	DDX_Check(pDX, IDC_CHECK_PRODUCT_COMPLETE, chk_PriductComp);

	DDX_Control(pDX, IDC_ROI_SIZE_X, m_SFR_roi_Size_X);
	DDX_Control(pDX, IDC_ROI_SIZE_Y, m_SFR_roi_Size_Y);

	DDX_Control(pDX, IDC_BCR_IP, m_BCR_IP);
	DDX_Control(pDX, IDC_BCR_PORT, m_BCR_Port);

	DDX_Control(pDX, IDC_ROUGH_DELAY_AF1, m_rDelay_Af1);
	DDX_Control(pDX, IDC_ROUGH_STEP_AF1, m_rStep_Af1);
	DDX_Control(pDX, IDC_ROUGH_DIS_AF1, m_rDis_Af1);
	DDX_Control(pDX, IDC_ROUGH_VEL_AF1, m_rVel_Af1);
	DDX_Control(pDX, IDC_ROUGHT_AVR_CNT, m_rAve_Cnt);
	DDX_Control(pDX, IDC_AA_REPEAT_COUNT, m_AARepeatCount);
	DDX_Control(pDX, IDC_FINE_DELAY_AF3, m_fDelay_Af3);
	DDX_Control(pDX, IDC_FINE_DIS_AF3, m_fDis_Af3);
	DDX_Control(pDX, IDC_FINE_AVR_CNT, m_fAve_Cnt);

	DDX_Control(pDX, IDC_DELAY_CAM6, m_Delay_Cam6);
	DDX_Control(pDX, IDC_RETRY_CAM5, m_Retry_Cam5);
	DDX_Control(pDX, IDC_DELAY_CAM2, m_Delay_Cam2);
	DDX_Control(pDX, IDC_RETRY_CAM2, m_Retry_Cam2);
	DDX_Control(pDX, IDC_DELAY_CAM4, m_Delay_Cam4);

	//
	DDX_Control(pDX, IDC_CONTI_OFFSET_Z_DOWN, m_Conti_Z_Down);
	//
	DDX_Control(pDX, IDC_PREV_UV_OFFSET_X, m_Uv_offset_X);
	DDX_Control(pDX, IDC_PREV_UV_OFFSET_Y, m_Uv_offset_Y);
	DDX_Control(pDX, IDC_PREV_UV_OFFSET_Z, m_Uv_offset_Z);
	DDX_Control(pDX, IDC_PREV_UV_OFFSET_TX, m_Uv_offset_Tx);
	DDX_Control(pDX, IDC_PREV_UV_OFFSET_TY, m_Uv_offset_Ty);
	DDX_Control(pDX, IDC_PREV_UV_OFFSET_TH, m_Uv_offset_Th);

	DDX_Control(pDX, IDC_FINE_DIS_MAX, m_label_Move_MaxPos_Fine);

	DDX_Control(pDX, IDC_LIMIT_SFR, m_Limit_Sfr);
	DDX_Control(pDX, IDC_CCD_CELL_SIZE, m_Ccd_Size);

	DDX_Control(pDX, IDC_LIMIT_SFR_CEN, m_Lim_Sfr_Cen);
	DDX_Control(pDX, IDC_LIMIT_SFR_SIDE, m_Lim_Sfr_Side);

	DDX_Control(pDX, IDC_CHECKCNT, m_Check_Cnt);

	DDX_Control(pDX, IDC_MOVE_OFFSET_Z, m_Move_offsetZ);
	DDX_Control(pDX, IDC_UVTIME, m_Uv_Time);
	DDX_Control(pDX, IDC_UV_POWER, m_Uv_Power);

	DDX_Control(pDX, IDC_UV_WEIGHT, m_Uv_Weight);

	DDX_Control(pDX, IDC_TILE_WEIGHT_PRE, m_Tilt_Weight_Pre);
	DDX_Control(pDX, IDC_TILE_WEIGHT_POST, m_Tilt_Weight_Post);
	//
	DDX_Control(pDX, IDC_TILT_DIRECTION, m_Tilt_Direction[0]);
	DDX_Control(pDX, IDC_TILT_DIRECTION2, m_Tilt_Direction[1]);
	DDX_Control(pDX, IDC_TILT_DIRECTION3, m_Tilt_Direction[2]);
	DDX_Control(pDX, IDC_TILT_DIRECTION4, m_Tilt_Direction[3]);
	DDX_Control(pDX, IDC_TILT_DIRECTION5, m_Tilt_Direction[4]);

	DDX_Radio(pDX, IDC_RADIO_AAMODE_MARKCENT, m_iAlignMode);

	DDX_Control(pDX, IDC_POINT_IN_X2, m_Laser_In_X2);
	DDX_Control(pDX, IDC_POINT_IN_X3, m_Laser_In_X3);
	DDX_Control(pDX, IDC_POINT_IN_X4, m_Laser_In_X4);
	DDX_Control(pDX, IDC_POINT_IN_Y2, m_Laser_In_Y2);
	DDX_Control(pDX, IDC_POINT_IN_Y3, m_Laser_In_Y3);
	DDX_Control(pDX, IDC_POINT_IN_Y4, m_Laser_In_Y4);
	//Lens
	DDX_Control(pDX, IDC_POINT_OUT_X2, m_Laser_Out_X2);
	DDX_Control(pDX, IDC_POINT_OUT_X3, m_Laser_Out_X3);
	DDX_Control(pDX, IDC_POINT_OUT_X4, m_Laser_Out_X4);
	DDX_Control(pDX, IDC_POINT_OUT_Y2, m_Laser_Out_Y2);
	DDX_Control(pDX, IDC_POINT_OUT_Y3, m_Laser_Out_Y3);
	DDX_Control(pDX, IDC_POINT_OUT_Y4, m_Laser_Out_Y4);
	//Pcb
	DDX_Control(pDX, IDC_POINT_PCB_X2, m_Laser_Pcb_X2);
	DDX_Control(pDX, IDC_POINT_PCB_X3, m_Laser_Pcb_X3);
	DDX_Control(pDX, IDC_POINT_PCB_X4, m_Laser_Pcb_X4);
	DDX_Control(pDX, IDC_POINT_PCB_Y2, m_Laser_Pcb_Y2);
	DDX_Control(pDX, IDC_POINT_PCB_Y3, m_Laser_Pcb_Y3);
	DDX_Control(pDX, IDC_POINT_PCB_Y4, m_Laser_Pcb_Y4);

	DDX_Control(pDX, IDC_INSP_PCB_TX, m_Insp_pcb_tx);
	DDX_Control(pDX, IDC_INSP_PCB_TY, m_Insp_pcb_ty);



	DDX_Control(pDX, IDC_EPOXY_CHANGE_COUNT, m_Epoxy_Change_Count);
	DDX_Control(pDX, IDC_LOG_RETENTION_PERIOD, m_Log_Retention_Period);

	DDX_Check(pDX, IDC_CHECK_DOOR_INTERLOCK, m_bDoorInterlock);
	DDX_Control(pDX, IDC_MES_IP, m_MES_IP);
	DDX_Control(pDX, IDC_MES_FACTORY, m_MES_Factory);
	DDX_Control(pDX, IDC_MES_PORT, m_MES_PORT);
	DDX_Control(pDX, IDC_MES_COMP_FACTORY, m_MES_Comp_Factory);
	DDX_Control(pDX, IDC_MES_COMP_PORT, m_MES_Comp_PORT);
	DDX_Text(pDX, IDC_MES_IP, m_sMES_IP);
	DDX_Text(pDX, IDC_MES_FACTORY, m_sMES_Factory);
	DDX_Text(pDX, IDC_MES_COMP_FACTORY, m_sMES_Comp_Factory);

	DDX_Control(pDX, IDC_LINE_PULSE, m_Line_Pulse);
	DDX_Control(pDX, IDC_LINE_PULSE2, m_Gen2_Line_Pulse);


	DDX_Check(pDX, IDC_CHECK_PASS_F_CURTAIN, chk_front);
	DDX_Check(pDX, IDC_CHK_AUTO_Z_SEARCH, chk_AUTO_Z_SEARCH);
	DDX_Control(pDX, IDC_STC_AUTO_Z_SEARCH_CNT, m_AUTO_Z_SEARCH_CNT);
	DDX_Control(pDX, IDC_STC_AUTO_Z_SEARCH_VAL, m_AUTO_Z_SEARCH_VAL);

	//DDX_Radio(pDX, IDC_RADIO_V, m_AARoiSelect);
	DDX_Radio(pDX, IDC_RADIO_AAROI1, m_AARoiSelect);

	DDX_Control(pDX, IDC_COMBO_LIGHT1_PORT, m_ComboLightPort1);
	DDX_Control(pDX, IDC_COMBO_LIGHT2_PORT, m_ComboLightPort2);
	DDX_Control(pDX, IDC_COMBO_LIGHT3_PORT, m_ComboLightPort3);
	DDX_Control(pDX, IDC_COMBO_LIGHT4_PORT, m_ComboLightPort4);
	DDX_Control(pDX, IDC_COMBO_LIGHT5_PORT, m_ComboLightPort5);
	DDX_Control(pDX, IDC_COMBO_LIGHT_1STOC_PORT, m_ComboLightPort6);
	
	DDX_Control(pDX, IDC_COMBO_X100_BARCODE_PORT, m_ComboX100BarcodePort);
	DDX_Control(pDX, IDC_COMBO_BARCODE_PORT, m_ComboBarcodePort);
	DDX_Control(pDX, IDC_COMBO_LASER_PORT, m_ComboLaserPort);
	DDX_Control(pDX, IDC_COMBO_UV_PORT, m_ComboUvPort);
	DDX_Control(pDX, IDC_COMBO_UV_PORT2, m_ComboUvPort2);

	DDX_Control(pDX, IDC_COMBO_EPOXY, m_ComboEpoxy);

	DDX_Control(pDX, IDC_COMBO_UV, m_ComboUv);
}


BEGIN_MESSAGE_MAP(CInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CInfoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CInfoDlg::OnBnClickedCancel)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_OK, &CInfoDlg::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CInfoDlg::OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDC_CHECK_PASS_UV, &CInfoDlg::OnBnClickedCheckPassUv)
	ON_STN_CLICKED(IDC_ROUGH_STEP_AF1, &CInfoDlg::OnStnClickedRoughStepAf1)
	ON_STN_CLICKED(IDC_ROUGH_VEL_AF1, &CInfoDlg::OnStnClickedRoughVelAf1)
	ON_STN_CLICKED(IDC_ROUGH_DIS_AF1, &CInfoDlg::OnStnClickedRoughDisAf1)
	ON_STN_CLICKED(IDC_ROUGHT_AVR_CNT, &CInfoDlg::OnStnClickedRoughtAvrCnt)
	ON_STN_CLICKED(IDC_FINE_DELAY_AF3, &CInfoDlg::OnStnClickedFineDelayAf3)
	ON_STN_CLICKED(IDC_FINE_DIS_AF3, &CInfoDlg::OnStnClickedFineDisAf3)
	ON_STN_CLICKED(IDC_FINE_AVR_CNT, &CInfoDlg::OnStnClickedFineAvrCnt)
	ON_STN_CLICKED(IDC_LIMIT_SFR_CEN, &CInfoDlg::OnStnClickedLimitSfrCen)
	ON_STN_CLICKED(IDC_LIMIT_SFR_SIDE, &CInfoDlg::OnStnClickedLimitSfrSide)
	ON_STN_CLICKED(IDC_LIMIT_SFR, &CInfoDlg::OnStnClickedLimitSfr)
	ON_STN_CLICKED(IDC_CHECKCNT, &CInfoDlg::OnStnClickedCheckcnt)
	ON_STN_CLICKED(IDC_MOVE_OFFSET_Z, &CInfoDlg::OnStnClickedMoveOffsetZ)
	ON_STN_CLICKED(IDC_UVTIME, &CInfoDlg::OnStnClickedUvtime)
	ON_STN_CLICKED(IDC_PREV_UV_OFFSET_X, &CInfoDlg::OnStnClickedPrevUvOffsetX)
	ON_STN_CLICKED(IDC_PREV_UV_OFFSET_Y, &CInfoDlg::OnStnClickedPrevUvOffsetY)
	ON_STN_CLICKED(IDC_PREV_UV_OFFSET_Z, &CInfoDlg::OnStnClickedPrevUvOffsetZ)
	ON_STN_CLICKED(IDC_PREV_UV_OFFSET_TX, &CInfoDlg::OnStnClickedPrevUvOffsetTx)
	ON_STN_CLICKED(IDC_PREV_UV_OFFSET_TY, &CInfoDlg::OnStnClickedPrevUvOffsetTy)
	ON_STN_CLICKED(IDC_PREV_UV_OFFSET_TH, &CInfoDlg::OnStnClickedPrevUvOffsetTh)
	ON_STN_CLICKED(IDC_CCD_CELL_SIZE, &CInfoDlg::OnStnClickedCcdCellSize)
	ON_STN_CLICKED(IDC_DELAY_CAM6, &CInfoDlg::OnStnClickedDelayCam6)
	ON_STN_CLICKED(IDC_DELAY_CAM2, &CInfoDlg::OnStnClickedDelayCam2)
	ON_STN_CLICKED(IDC_DELAY_CAM4, &CInfoDlg::OnStnClickedDelayCam4)
	ON_STN_CLICKED(IDC_RETRY_CAM5, &CInfoDlg::OnStnClickedRetryCam5)
	ON_STN_CLICKED(IDC_RETRY_CAM2, &CInfoDlg::OnStnClickedRetryCam2)
	ON_STN_CLICKED(IDC_ROUGH_DELAY_AF1, &CInfoDlg::OnStnClickedRoughDelayAf1)

	ON_STN_CLICKED(IDC_POINT_IN_X2, &CInfoDlg::OnStnClickedPointInX2)
	ON_STN_CLICKED(IDC_POINT_IN_X3, &CInfoDlg::OnStnClickedPointInX3)
	ON_STN_CLICKED(IDC_POINT_IN_X4, &CInfoDlg::OnStnClickedPointInX4)
	ON_STN_CLICKED(IDC_POINT_OUT_X2, &CInfoDlg::OnStnClickedPointOutX2)
	ON_STN_CLICKED(IDC_POINT_OUT_X3, &CInfoDlg::OnStnClickedPointOutX3)
	ON_STN_CLICKED(IDC_POINT_OUT_X4, &CInfoDlg::OnStnClickedPointOutX4)
	ON_STN_CLICKED(IDC_POINT_IN_Y2, &CInfoDlg::OnStnClickedPointInY2)
	ON_STN_CLICKED(IDC_POINT_IN_Y3, &CInfoDlg::OnStnClickedPointInY3)
	ON_STN_CLICKED(IDC_POINT_IN_Y4, &CInfoDlg::OnStnClickedPointInY4)
	ON_STN_CLICKED(IDC_POINT_OUT_Y2, &CInfoDlg::OnStnClickedPointOutY2)
	ON_STN_CLICKED(IDC_POINT_OUT_Y3, &CInfoDlg::OnStnClickedPointOutY3)
	ON_STN_CLICKED(IDC_POINT_OUT_Y4, &CInfoDlg::OnStnClickedPointOutY4)
	
	

	ON_STN_CLICKED(IDC_FINE_DIS_MAX, &CInfoDlg::OnStnClickedFineDisMax)
	ON_STN_CLICKED(IDC_ROI_SIZE_X, &CInfoDlg::OnStnClickedRoiSizeX)
	ON_STN_CLICKED(IDC_ROI_SIZE_Y, &CInfoDlg::OnStnClickedRoiSizeY)
	ON_BN_CLICKED(IDC_CHECK_STAIN_INSP, &CInfoDlg::OnBnClickedCheckDefectInsp)
	ON_BN_CLICKED(IDC_CHECK_1ST_AA_ENABLE, &CInfoDlg::OnBnClickedCheck1stAaEnable)

	ON_BN_CLICKED(IDC_RADIO_AAMODE_OPTICAL, &CInfoDlg::OnBnClickedRadioAamodeOptical)

//	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_CHECK_PASS_DISPENSE, &CInfoDlg::OnBnClickedCheckPassDispense)
	ON_BN_CLICKED(IDC_CHECK_PASS_DISPENSE_INSP, &CInfoDlg::OnBnClickedCheckPassDispenseInsp)
	ON_BN_CLICKED(IDC_CHECK_PRODUCT_COMPLETE, &CInfoDlg::OnBnClickedCheckProductComplete)
	ON_BN_CLICKED(IDC_CHECK_DOOR_INTERLOCK, &CInfoDlg::OnBnClickedCheckDoorInterlock)
	ON_STN_CLICKED(IDC_EPOXY_CHANGE_COUNT, &CInfoDlg::OnStnClickedEpoxyChangeTime)
	ON_STN_CLICKED(IDC_MES_IP, &CInfoDlg::OnStnClickedMesIp)
	ON_STN_CLICKED(IDC_MES_FACTORY, &CInfoDlg::OnStnClickedMesFactory)
	ON_STN_CLICKED(IDC_MES_PORT, &CInfoDlg::OnStnClickedMesPort)
	ON_BN_CLICKED(IDC_RADIO_IC_CIRCLE, &CInfoDlg::OnBnClickedRadioIcCircle)
	ON_BN_CLICKED(IDC_RADIO_IC_DISTORTIONCENTER, &CInfoDlg::OnBnClickedRadioIcDistortioncenter)
	ON_BN_CLICKED(IDC_RADIO_AAMODE_MARKCENT, &CInfoDlg::OnBnClickedRadioAamodeMarkcent)
	ON_STN_CLICKED(IDC_LOG_RETENTION_PERIOD, &CInfoDlg::OnStnClickedRetentionPeriod)
	ON_STN_CLICKED(IDC_MES_COMP_FACTORY, &CInfoDlg::OnStnClickedMesCompFactory)
	ON_STN_CLICKED(IDC_MES_COMP_PORT, &CInfoDlg::OnStnClickedMesCompPort)
	ON_STN_CLICKED(IDC_LINE_PULSE, &CInfoDlg::OnStnClickedLinePulse)
	ON_BN_CLICKED(IDC_BUTTON_INITIAL, &CInfoDlg::OnBnClickedButtonInitial)
	ON_BN_CLICKED(IDC_RADIO_AAMODE_DISTORTIONCENTER, &CInfoDlg::OnBnClickedRadioAamodeDistortioncenter)
	ON_BN_CLICKED(IDC_CHECK_PASS_F_CURTAIN, &CInfoDlg::OnBnClickedCheckPassFCurtain)

	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_AAROI1, IDC_RADIO_AAROI3, &CInfoDlg::OnBnClickedRadioV) 
	//ON_CONTROL_RANGE(BN_CLICKED, IDC_RA1, IDC_RA6, RadioCtrl) 등록.

	ON_STN_CLICKED(IDC_UV_WEIGHT, &CInfoDlg::OnStnClickedUvWeight)
	ON_BN_CLICKED(IDC_CHK_AUTO_Z_SEARCH, &CInfoDlg::OnBnClickedChkAutoZSearch)
	ON_STN_CLICKED(IDC_STC_AUTO_Z_SEARCH_CNT, &CInfoDlg::OnStnClickedStcAutoZSearchCnt)
	ON_STN_CLICKED(IDC_STC_AUTO_Z_SEARCH_VAL, &CInfoDlg::OnStnClickedStcAutoZSearchVal)
	ON_STN_CLICKED(IDC_TILE_WEIGHT_PRE, &CInfoDlg::OnStnClickedTileWeightX)
	ON_STN_CLICKED(IDC_TILE_WEIGHT_POST, &CInfoDlg::OnStnClickedTileWeightY)
	ON_BN_CLICKED(IDC_CHECK_UV_INSP, &CInfoDlg::OnBnClickedCheckUvInsp)

	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_INFO_MARK_GRID, &CInfoDlg::OnDBClickedGridMark)
	ON_BN_CLICKED(IDC_CHECK_LASER_INSP, &CInfoDlg::OnBnClickedCheckLaserInsp)
	ON_STN_CLICKED(IDC_CONTI_OFFSET_Z_DOWN, &CInfoDlg::OnStnClickedContiOffsetZDown)
	ON_STN_CLICKED(IDC_INSP_PCB_TX, &CInfoDlg::OnStnClickedInspPcbTx)
	ON_STN_CLICKED(IDC_INSP_PCB_TY, &CInfoDlg::OnStnClickedInspPcbTy)
	ON_STN_CLICKED(IDC_POINT_PCB_X2, &CInfoDlg::OnStnClickedPointPcbX2)
	ON_STN_CLICKED(IDC_POINT_PCB_X3, &CInfoDlg::OnStnClickedPointPcbX3)
	ON_STN_CLICKED(IDC_POINT_PCB_X4, &CInfoDlg::OnStnClickedPointPcbX4)
	ON_STN_CLICKED(IDC_POINT_PCB_Y2, &CInfoDlg::OnStnClickedPointPcbY2)
	ON_STN_CLICKED(IDC_POINT_PCB_Y3, &CInfoDlg::OnStnClickedPointPcbY3)
	ON_STN_CLICKED(IDC_POINT_PCB_Y4, &CInfoDlg::OnStnClickedPointPcbY4)
	ON_STN_CLICKED(IDC_UV_POWER, &CInfoDlg::OnStnClickedUvPower)
	ON_STN_CLICKED(IDC_LINE_PULSE2, &CInfoDlg::OnStnClickedLinePulse2)
		ON_STN_CLICKED(IDC_TILT_DIRECTION, &CInfoDlg::OnStnClickedTiltDirection)
		ON_STN_CLICKED(IDC_TILT_DIRECTION2, &CInfoDlg::OnStnClickedTiltDirection2)
		ON_STN_CLICKED(IDC_TILT_DIRECTION3, &CInfoDlg::OnStnClickedTiltDirection3)
		ON_STN_CLICKED(IDC_TILT_DIRECTION4, &CInfoDlg::OnStnClickedTiltDirection4)
		ON_STN_CLICKED(IDC_TILT_DIRECTION5, &CInfoDlg::OnStnClickedTiltDirection5)
		ON_BN_CLICKED(IDC_CHECK_XY_CHANGE, &CInfoDlg::OnBnClickedCheckXyChange)
		ON_BN_CLICKED(IDC_CHECK_IR_CHART_USE, &CInfoDlg::OnBnClickedCheckIrChartUse)
		ON_BN_CLICKED(IDC_CHECK_SFR_MAX_TEST, &CInfoDlg::OnBnClickedCheckSfrMaxTest)
		ON_STN_CLICKED(IDC_AA_REPEAT_COUNT, &CInfoDlg::OnStnClickedAaRepeatCount)
		ON_STN_CLICKED(IDC_BCR_IP, &CInfoDlg::OnStnClickedBcrIp)
		ON_STN_CLICKED(IDC_BCR_PORT, &CInfoDlg::OnStnClickedBcrPort)
		END_MESSAGE_MAP()


// CInfoDlg 메시지 처리기입니다.


void CInfoDlg::OnBnClickedOk(){}
void CInfoDlg::OnBnClickedCancel(){CDialogEx::OnCancel();}


void CInfoDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow)
	{
		putData();

		UpdateData(false);
	}
}

void CInfoDlg::OnDBClickedGridMark(NMHDR* pNMHDR, LRESULT* pResult)
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

	if ( row <= 0 || col <= 0 )	return;

	CString sCellData = m_clGrid_Mark_Matching.GetItemText(row, col);

	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)sCellData);

	if ( dlg.DoModal() == IDOK )
	{
		m_clGrid_Mark_Matching.SetItemText(row, col, dlg.GetstrNum());
		m_clGrid_Mark_Matching.Invalidate();
	}
}
void CInfoDlg::InitGridCtrl_MarkMatching()
{
	CRect rect;
	CWnd *pWnd= (CWnd*)GetDlgItem(IDC_STATIC_INFO_MARK_GRID); 
	MarkRow = 5;//아래
	MarkCol = 2;//옆
	int margin = 4;
	int gridHeight = 32;
	int gridWidth1 = 90;
	int gridWidth2 = 110;
	int totalWidth = gridWidth1+(gridWidth2*(MarkCol-1));
	//
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = totalWidth +margin;
	rect.bottom = (gridHeight*MarkRow) +margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.

	GetDlgItem(IDC_STATIC_INFO_MARK_GRID)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGrid_Mark_Matching.Create(rect, this, IDC_STATIC_INFO_MARK_GRID, WS_TABSTOP | WS_VISIBLE);

	m_clGrid_Mark_Matching.SetTextBkColor(GRID_COLOR_WHITE);
	m_clGrid_Mark_Matching.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGrid_Mark_Matching.SetFixedTextColor(GRID_COLOR_WHITE);
	m_clGrid_Mark_Matching.SetReference_Setting();
	m_clGrid_Mark_Matching.EnableSelection(FALSE);
	m_clGrid_Mark_Matching.SetRowCount(MarkRow);
	m_clGrid_Mark_Matching.SetColumnCount(MarkCol);
	m_clGrid_Mark_Matching.SetFixedRowCount(1);
	m_clGrid_Mark_Matching.SetFixedColumnCount(1);

	CString tmpStr="";


	m_clGrid_Mark_Matching.SetItemText(0, 1, "Mark Matching(%)");

	m_clGrid_Mark_Matching.SetItemText(0, 0, "Pos");
	m_clGrid_Mark_Matching.SetItemText(1, 0, "Sensor");
	m_clGrid_Mark_Matching.SetItemText(2, 0, "Holder");
	m_clGrid_Mark_Matching.SetItemText(3, 0, "Lens");
	m_clGrid_Mark_Matching.SetItemText(4, 0, "Complete");


	//
	int i=0, j=0;
	for (i = 0; i < MarkRow; i++)
	{
		m_clGrid_Mark_Matching.SetRowHeight(i, gridHeight);
		for (j = 0; j < MarkCol; j++)
		{
			m_clGrid_Mark_Matching.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			if (i == 0)
			{
				if (j == 0)
				{
					m_clGrid_Mark_Matching.SetColumnWidth(j, gridWidth1);
				}else{
					m_clGrid_Mark_Matching.SetColumnWidth(j, gridWidth2);
				}
			}			
		}
	}
	m_clGrid_Mark_Matching.Invalidate();
}
void CInfoDlg::getData()
{
	CString sEditData="";
	TCHAR szData[SIZE_OF_100BYTE];

	UpdateData(true);

	sysData.m_iAASel = m_AARoiSelect;
	sysData.m_iAlignMode = m_iAlignMode;

	GetDlgItemText(IDC_BCR_IP, sEditData);
	_stprintf_s(sysData.m_szBarcodeIp, SIZE_OF_100BYTE, _T("%s"), (TCHAR*)(LPCTSTR)sEditData);

	GetDlgItemText(IDC_BCR_PORT, sEditData);
	sysData.m_nBarcodePort = atof(sEditData);

	GetDlgItemText(IDC_INSP_PCB_TX, sEditData);
	model.m_InspPcbTilt[0] = atof(sEditData);
	GetDlgItemText(IDC_INSP_PCB_TY, sEditData);
	model.m_InspPcbTilt[1] = atof(sEditData);
	
	GetDlgItemText(IDC_POINT_IN_X2, sEditData);
	model.m_InPos_X[0]	= atof(sEditData);
	GetDlgItemText(IDC_POINT_IN_X3, sEditData);
	model.m_InPos_X[1]	= atof(sEditData);
	GetDlgItemText(IDC_POINT_IN_X4, sEditData);
	model.m_InPos_X[2]	= atof(sEditData);
	GetDlgItemText(IDC_POINT_IN_Y2, sEditData);
	model.m_InPos_Y[0]	= atof(sEditData);
	GetDlgItemText(IDC_POINT_IN_Y3, sEditData);
	model.m_InPos_Y[1]	= atof(sEditData);
	GetDlgItemText(IDC_POINT_IN_Y4, sEditData);
	model.m_InPos_Y[2]	= atof(sEditData);

	GetDlgItemText(IDC_POINT_OUT_X2, sEditData);
	model.m_OutPos_X[0] = atof(sEditData);
	GetDlgItemText(IDC_POINT_OUT_X3, sEditData);
	model.m_OutPos_X[1] = atof(sEditData);
	GetDlgItemText(IDC_POINT_OUT_X4, sEditData);
	model.m_OutPos_X[2] = atof(sEditData);
	GetDlgItemText(IDC_POINT_OUT_Y2, sEditData);
	model.m_OutPos_Y[0] = atof(sEditData);
	GetDlgItemText(IDC_POINT_OUT_Y3, sEditData);
	model.m_OutPos_Y[1] = atof(sEditData);
	GetDlgItemText(IDC_POINT_OUT_Y4, sEditData);
	model.m_OutPos_Y[2] = atof(sEditData);

	GetDlgItemText(IDC_POINT_PCB_X2, sEditData);
	model.m_PcbLaserPos_X[0] = atof(sEditData);
	GetDlgItemText(IDC_POINT_PCB_X3, sEditData);
	model.m_PcbLaserPos_X[1] = atof(sEditData);
	GetDlgItemText(IDC_POINT_PCB_X4, sEditData);
	model.m_PcbLaserPos_X[2] = atof(sEditData);
	GetDlgItemText(IDC_POINT_PCB_Y2, sEditData);
	model.m_PcbLaserPos_Y[0] = atof(sEditData);
	GetDlgItemText(IDC_POINT_PCB_Y3, sEditData);
	model.m_PcbLaserPos_Y[1] = atof(sEditData);
	GetDlgItemText(IDC_POINT_PCB_Y4, sEditData);
	model.m_PcbLaserPos_Y[2] = atof(sEditData);

	model.strInfo_AF1.m_iDelayTime	= GetDlgItemInt(IDC_ROUGH_DELAY_AF1);
	model.strInfo_AF1.m_iStepCnt	= GetDlgItemInt(IDC_ROUGH_STEP_AF1);


	GetDlgItemText(IDC_ROUGH_DIS_AF1, sEditData);
	model.strInfo_AF1.m_dMoveDistance	= atof(sEditData);
	GetDlgItemText(IDC_ROUGH_VEL_AF1, sEditData);
	model.strInfo_AF1.m_dMoveVel		= atof(sEditData);

	model.strInfo_CCM.m_iCnt_Average_Thru_Focus = GetDlgItemInt(IDC_ROUGHT_AVR_CNT);
	model.AARepeatCount = GetDlgItemInt(IDC_AA_REPEAT_COUNT);


	model.strInfo_AF2.m_iDelayTime	= GetDlgItemInt(IDC_FINE_DELAY_AF3);
	GetDlgItemText(IDC_FINE_DIS_AF3, sEditData);
	model.strInfo_AF2.m_dMoveDistance	= atof(sEditData);
	model.strInfo_CCM.m_iCnt_Average_Fine_Focus = GetDlgItemInt(IDC_FINE_AVR_CNT);

	model.strInfo_Cam[0].m_iDelayTime	= GetDlgItemInt(IDC_DELAY_CAM6);
	model.strInfo_Cam[0].m_iRetryCnt	= GetDlgItemInt(IDC_RETRY_CAM5);

	model.strInfo_Cam[1].m_iDelayTime	= GetDlgItemInt(IDC_DELAY_CAM2);
	model.strInfo_Cam[1].m_iRetryCnt	= GetDlgItemInt(IDC_RETRY_CAM2);

	//model.strInfo_Cam[2].m_iDelayTime	= GetDlgItemInt(IDC_DELAY_CAM3);

	model.strInfo_Cam[3].m_iDelayTime	= GetDlgItemInt(IDC_DELAY_CAM4);

	GetDlgItemText(IDC_EDIT_MTF_LIMIT, sEditData);
	model.strInfo_AF1.m_fLimit_MTF		= (float)atof(sEditData);

	//////////////////////////////////////////////////////////////////////////
	/* UV 전 offset 이동 데이터 */
	GetDlgItemText(IDC_PREV_UV_OFFSET_X, sEditData);
	sysData.m_dOffset_Prev_UV_X			= atof(sEditData);

	GetDlgItemText(IDC_PREV_UV_OFFSET_Y, sEditData);
	sysData.m_dOffset_Prev_UV_Y			= atof(sEditData);

	GetDlgItemText(IDC_PREV_UV_OFFSET_Z, sEditData);
	sysData.m_dOffset_Prev_UV_Z			= atof(sEditData);

	GetDlgItemText(IDC_PREV_UV_OFFSET_TX, sEditData);
	sysData.m_dOffset_Prev_UV_Tx			= atof(sEditData);

	GetDlgItemText(IDC_PREV_UV_OFFSET_TY, sEditData);
	sysData.m_dOffset_Prev_UV_Ty			= atof(sEditData);

	GetDlgItemText(IDC_PREV_UV_OFFSET_TH, sEditData);
	sysData.m_dOffset_Prev_UV_Th			= atof(sEditData);
	//////////////////////////////////////////////////////////////////////////
	// 2차 AA 시작 지점 이동 거리
	GetDlgItemText(IDC_FINE_DIS_MAX, sEditData);
	sysData.m_dMove_MaxPos_Fine			= atof(sEditData);
	//////////////////////////////////////////////////////////////////////////
	
	GetDlgItemText(IDC_LIMIT_SFR, sEditData);
	model.strInfo_AF1.m_fLimit_MTF		= (float)atof(sEditData);

	GetDlgItemText(IDC_CCD_CELL_SIZE, sEditData);
	model.m_dSize_CCD_Cell				= atof(sEditData);

    sysData.m_iStaintInspPass = m_bStainInspPass;
    sysData.m_iDefectInspPass = m_bDefectInspPass;
    
	sysData.m_iLaserInspPass = m_bLaserInsp;
	sysData.m_iEpoxyLaserInspPass = m_bEpoxyLaserInspPass;
	sysData.m_iAlignCamInspPass = m_bAlignCamInsp;
	sysData.m_iSfrMaxValueInsp = m_bSfrMaxValueInsp;
	sysData.m_iDicChange = m_bDicChange;
	sysData.m_iIrChartUse = m_bIrChartUse;
	
	sysData.m_i1stAaEbable	= m_b1stAaEnable;

	model.m_iCnt_Check_SFR = GetDlgItemInt(IDC_CHECKCNT);

	GetDlgItemText(IDC_MOVE_OFFSET_Z, sEditData);
	model.m_dMove_Offset_Z = atof(sEditData);

	GetDlgItemText(IDC_ROI_SIZE_X, sEditData);
	model.m_iSize_ROI_X = atoi(sEditData);
	GetDlgItemText(IDC_ROI_SIZE_Y, sEditData);
	model.m_iSize_ROI_Y = atoi(sEditData);

	GetDlgItemText(IDC_UVTIME, sEditData);
	model.UV_Time = atoi(sEditData);

	GetDlgItemText(IDC_UV_POWER, sEditData);
	model.UV_Power = atoi(sEditData);
	
	
	GetDlgItemText(IDC_UV_WEIGHT, sEditData);	
	model.UV_Weight = atof(sEditData);

	GetDlgItemText(IDC_TILE_WEIGHT_PRE, sEditData);	
	model.Tilt_Weight_Pre = atof(sEditData);
	GetDlgItemText(IDC_TILE_WEIGHT_POST, sEditData);	
	model.Tilt_Weight_Post = atof(sEditData);

	GetDlgItemText(IDC_TILT_DIRECTION, sEditData);
	model.Tilt_Diretion[0] = atoi(sEditData);
	GetDlgItemText(IDC_TILT_DIRECTION2, sEditData);
	model.Tilt_Diretion[1] = atoi(sEditData);
	GetDlgItemText(IDC_TILT_DIRECTION3, sEditData);
	model.Tilt_Diretion[2] = atoi(sEditData);
	GetDlgItemText(IDC_TILT_DIRECTION4, sEditData);
	model.Tilt_Diretion[3] = atoi(sEditData);
	GetDlgItemText(IDC_TILT_DIRECTION5, sEditData);
	model.Tilt_Diretion[4] = atoi(sEditData);
	
	model.m_AUTO_Z_SEARCH=chk_AUTO_Z_SEARCH;

	GetDlgItemText(IDC_STC_AUTO_Z_SEARCH_CNT, sEditData);
	model.m_AUTO_Z_SEARCH_CNT = atoi(sEditData);

	GetDlgItemText(IDC_STC_AUTO_Z_SEARCH_VAL, sEditData);
	model.m_AUTO_Z_SEARCH_VAL = atof(sEditData);


	sysData.m_iMTFUvInsp = chk_UvMTFInsp;
	sysData.m_iDispensePass = chk_Dispense;		//Dispense Pass 모드 사용 여부
	sysData.m_iDispenseInspPass = chk_DispenseInsp;
	sysData.m_iUVPass = m_bPassUV;
	sysData.m_iFront = chk_front;
	sysData.m_iProductComp = chk_PriductComp;

	if( m_bDoorInterlock == 1)	sysData.iDoorInterlock = 1;
	else						sysData.iDoorInterlock = 0;


	GetDlgItemText(IDC_EPOXY_CHANGE_COUNT, sEditData);
	sysData.m_Epoxy_Change_Count = atoi(sEditData);

	GetDlgItemText(IDC_LOG_RETENTION_PERIOD, sEditData);
	sysData.m_Log_Retention_Period = atoi(sEditData);

	GetDlgItemText(IDC_MES_IP, sEditData);
	sysData.m_Mes_Ip_Number = sEditData;

	GetDlgItemText(IDC_MES_FACTORY, sEditData);
	sysData.m_Factory_Code = sEditData;

	GetDlgItemText(IDC_MES_PORT, sEditData);
	sysData.m_Mes_Port_Number = atoi(sEditData);

	GetDlgItemText(IDC_MES_COMP_FACTORY, sEditData);
	sysData.m_Comp_Factory_Code = sEditData;

	GetDlgItemText(IDC_MES_COMP_PORT, sEditData);
	sysData.m_Mes_Comp_Port_Number = atoi(sEditData);

	sysData.m_Factory_Code = m_sMES_Factory;
	sysData.m_Comp_Factory_Code = m_sMES_Comp_Factory;
	 
	sysData.m_Mes_Ip_Number = m_sMES_IP;

	GetDlgItemText(IDC_LINE_PULSE, sEditData);
	model.m_Line_Pulse = atof(sEditData);
	GetDlgItemText(IDC_LINE_PULSE2, sEditData);
	model.m_Gen2_Line_Pulse = atof(sEditData);
	



	GetDlgItemText(IDC_CONTI_OFFSET_Z_DOWN, sEditData);
	sysData.m_dOffset_Conti_Down_Z = atof(sEditData);

	sysData.nEpoxyIndex = m_ComboEpoxy.GetCurSel();
	sysData.nUvIndex = m_ComboUv.GetCurSel();
	
	sysData.iCommPort[COMM_LASER]	= m_ComboLaserPort.GetCurSel() + 1;
	sysData.iCommPort[COMM_BARCODE] = m_ComboBarcodePort.GetCurSel() + 1;
	sysData.iCommPort[COMM_X100_BCR] = m_ComboX100BarcodePort.GetCurSel() + 1;
	sysData.iCommPort[COMM_UV] = m_ComboUvPort.GetCurSel() + 1;
	sysData.iCommPort[COMM_UV2] = m_ComboUvPort2.GetCurSel() + 1;
	
	sysData.iCommPort[COMM_LIGHT1] = m_ComboLightPort1.GetCurSel() + 1;
	sysData.iCommPort[COMM_LIGHT2] = m_ComboLightPort2.GetCurSel() + 1;
	sysData.iCommPort[COMM_LIGHT3] = m_ComboLightPort3.GetCurSel() + 1;
	sysData.iCommPort[COMM_LIGHT4] = m_ComboLightPort4.GetCurSel() + 1;
	sysData.iCommPort[COMM_LIGHT5] = m_ComboLightPort5.GetCurSel() + 1;

	sysData.iCommPort[COMM_LIGHTOC_1ST] = m_ComboLightPort6.GetCurSel() + 1;
	
	sEditData.Format("%s" , m_clGrid_Mark_Matching.GetItemText(1, 1));
	model.m_MarkMatchingRate[0] =  atoi(sEditData);
	sEditData.Format("%s" , m_clGrid_Mark_Matching.GetItemText(2, 1));
	model.m_MarkMatchingRate[1] =  atoi(sEditData);
	sEditData.Format("%s" , m_clGrid_Mark_Matching.GetItemText(3, 1));
	model.m_MarkMatchingRate[2] =  atoi(sEditData);
	sEditData.Format("%s" , m_clGrid_Mark_Matching.GetItemText(4, 1));
	model.m_MarkMatchingRate[3] =  atoi(sEditData);
	m_clGrid_Mark_Matching.Invalidate();

}


void CInfoDlg::putData()
{
	CString sEditData="";

	m_iAlignMode	= sysData.m_iAlignMode;
	m_AARoiSelect   = sysData.m_iAASel;

	sEditData.Format("%.02lf", model.m_InspPcbTilt[0]);
	SetDlgItemText(IDC_INSP_PCB_TX, sEditData);
	sEditData.Format("%.02lf", model.m_InspPcbTilt[1]);
	SetDlgItemText(IDC_INSP_PCB_TY, sEditData);
	
	sEditData = sysData.m_szBarcodeIp;
	SetDlgItemText(IDC_BCR_IP, sEditData);
	sEditData.Format("%d", sysData.m_nBarcodePort);
	SetDlgItemText(IDC_BCR_PORT, sEditData);

	sEditData.Format("%.02lf", model.m_InPos_X[0]);
	SetDlgItemText(IDC_POINT_IN_X2, sEditData);
	sEditData.Format("%.02lf", model.m_InPos_X[1]);
	SetDlgItemText(IDC_POINT_IN_X3, sEditData);
	sEditData.Format("%.02lf", model.m_InPos_X[2]);
	SetDlgItemText(IDC_POINT_IN_X4, sEditData);
	sEditData.Format("%.02lf", model.m_InPos_Y[0]);
	SetDlgItemText(IDC_POINT_IN_Y2, sEditData);
	sEditData.Format("%.02lf", model.m_InPos_Y[1]);
	SetDlgItemText(IDC_POINT_IN_Y3, sEditData);
	sEditData.Format("%.02lf", model.m_InPos_Y[2]);
	SetDlgItemText(IDC_POINT_IN_Y4, sEditData);

	sEditData.Format("%.02lf", model.m_OutPos_X[0]);
	SetDlgItemText(IDC_POINT_OUT_X2, sEditData);
	sEditData.Format("%.02lf", model.m_OutPos_X[1]);
	SetDlgItemText(IDC_POINT_OUT_X3, sEditData);
	sEditData.Format("%.02lf", model.m_OutPos_X[2]);
	SetDlgItemText(IDC_POINT_OUT_X4, sEditData);
	sEditData.Format("%.02lf", model.m_OutPos_Y[0]);
	SetDlgItemText(IDC_POINT_OUT_Y2, sEditData);
	sEditData.Format("%.02lf", model.m_OutPos_Y[1]);
	SetDlgItemText(IDC_POINT_OUT_Y3, sEditData);
	sEditData.Format("%.02lf", model.m_OutPos_Y[2]);
	SetDlgItemText(IDC_POINT_OUT_Y4, sEditData);

	sEditData.Format("%.02lf", model.m_PcbLaserPos_X[0]);
	SetDlgItemText(IDC_POINT_PCB_X2, sEditData);
	sEditData.Format("%.02lf", model.m_PcbLaserPos_X[1]);
	SetDlgItemText(IDC_POINT_PCB_X3, sEditData);
	sEditData.Format("%.02lf", model.m_PcbLaserPos_X[2]);
	SetDlgItemText(IDC_POINT_PCB_X4, sEditData);
	sEditData.Format("%.02lf", model.m_PcbLaserPos_Y[0]);
	SetDlgItemText(IDC_POINT_PCB_Y2, sEditData);
	sEditData.Format("%.02lf", model.m_PcbLaserPos_Y[1]);
	SetDlgItemText(IDC_POINT_PCB_Y3, sEditData);
	sEditData.Format("%.02lf", model.m_PcbLaserPos_Y[2]);
	SetDlgItemText(IDC_POINT_PCB_Y4, sEditData);


	SetDlgItemInt(IDC_ROUGH_DELAY_AF1, model.strInfo_AF1.m_iDelayTime);
	SetDlgItemInt(IDC_ROUGH_STEP_AF1, model.strInfo_AF1.m_iStepCnt);
	sEditData.Format("%.03f", model.strInfo_AF1.m_dMoveDistance);
	SetDlgItemText(IDC_ROUGH_DIS_AF1, sEditData);
	sEditData.Format("%.03f", model.strInfo_AF1.m_dMoveVel);
	SetDlgItemText(IDC_ROUGH_VEL_AF1, sEditData);
	SetDlgItemInt(IDC_ROUGHT_AVR_CNT, model.strInfo_CCM.m_iCnt_Average_Thru_Focus);

	SetDlgItemInt(IDC_AA_REPEAT_COUNT, model.AARepeatCount);

	SetDlgItemInt(IDC_FINE_DELAY_AF3, model.strInfo_AF2.m_iDelayTime);
	sEditData.Format("%.03f", model.strInfo_AF2.m_dMoveDistance);
	SetDlgItemText(IDC_FINE_DIS_AF3, sEditData);
	SetDlgItemInt(IDC_FINE_AVR_CNT, model.strInfo_CCM.m_iCnt_Average_Fine_Focus);

	SetDlgItemInt(IDC_DELAY_CAM6, model.strInfo_Cam[0].m_iDelayTime);
	SetDlgItemInt(IDC_RETRY_CAM5, model.strInfo_Cam[0].m_iRetryCnt);

	SetDlgItemInt(IDC_DELAY_CAM2, model.strInfo_Cam[1].m_iDelayTime);
	SetDlgItemInt(IDC_RETRY_CAM2, model.strInfo_Cam[1].m_iRetryCnt);

	SetDlgItemInt(IDC_DELAY_CAM4, model.strInfo_Cam[3].m_iDelayTime);

	sEditData.Format("%.3f", model.strInfo_AF1.m_fLimit_MTF);
	SetDlgItemText(IDC_EDIT_MTF_LIMIT, sEditData);

	//////////////////////////////////////////////////////////////////////////
	/* UV 전 offset 이동 데이터 */
	sEditData.Format("%.3f", sysData.m_dOffset_Prev_UV_X);
	SetDlgItemText(IDC_PREV_UV_OFFSET_X, sEditData);

	sEditData.Format("%.3f", sysData.m_dOffset_Prev_UV_Y);
	SetDlgItemText(IDC_PREV_UV_OFFSET_Y, sEditData);

	sEditData.Format("%.3f", sysData.m_dOffset_Prev_UV_Z);
	SetDlgItemText(IDC_PREV_UV_OFFSET_Z, sEditData);

	sEditData.Format("%.3f", sysData.m_dOffset_Prev_UV_Tx);
	SetDlgItemText(IDC_PREV_UV_OFFSET_TX, sEditData);

	sEditData.Format("%.3f", sysData.m_dOffset_Prev_UV_Ty);
	SetDlgItemText(IDC_PREV_UV_OFFSET_TY, sEditData);

	sEditData.Format("%.3f", sysData.m_dOffset_Prev_UV_Th);
	SetDlgItemText(IDC_PREV_UV_OFFSET_TH, sEditData);



	
	//////////////////////////////////////////////////////////////////////////
	/* 2차 AA 시작 지점 이동 거리 */
	sEditData.Format("%.04lf", sysData.m_dMove_MaxPos_Fine);
	SetDlgItemText(IDC_FINE_DIS_MAX, sEditData);
	//////////////////////////////////////////////////////////////////////////

	sEditData.Format("%d", model.strInfo_CCM.m_iCnt_Average_Defect);

	sEditData.Format("%d", model.strInfo_CCM.m_iCnt_Average_Opt_Centering);

	sEditData.Format("%.03f", model.strInfo_AF1.m_fLimit_MTF);
	SetDlgItemText(IDC_LIMIT_SFR, sEditData);

	sEditData.Format("%.03f", model.m_dSize_CCD_Cell);
	SetDlgItemText(IDC_CCD_CELL_SIZE, sEditData);

	m_bPassUV		= sysData.m_iUVPass		? TRUE : FALSE;
	m_bStainInspPass = sysData.m_iStaintInspPass ? TRUE : FALSE;
	m_bDefectInspPass = sysData.m_iDefectInspPass ?  TRUE : FALSE;
	m_b1stAaEnable	= sysData.m_i1stAaEbable? TRUE : FALSE;
	m_bLaserInsp = sysData.m_iLaserInspPass ? TRUE : FALSE;
	m_bAlignCamInsp = sysData.m_iAlignCamInspPass ? TRUE : FALSE;
	m_bSfrMaxValueInsp = sysData.m_iSfrMaxValueInsp ? TRUE : FALSE;
	m_bEpoxyLaserInspPass = sysData.m_iEpoxyLaserInspPass ? TRUE : FALSE;
	m_bDicChange = sysData.m_iDicChange ? TRUE : FALSE;
	m_bIrChartUse = sysData.m_iIrChartUse ? TRUE : FALSE;

	SetDlgItemInt(IDC_CHECKCNT, model.m_iCnt_Check_SFR);
	sEditData.Format("%.03lf", model.m_dMove_Offset_Z);
	SetDlgItemText(IDC_MOVE_OFFSET_Z, sEditData);

	sEditData.Format("%d", model.m_iSize_ROI_X);
	SetDlgItemText(IDC_ROI_SIZE_X, sEditData);
	sEditData.Format("%d", model.m_iSize_ROI_Y);
	SetDlgItemText(IDC_ROI_SIZE_Y, sEditData);

	sEditData.Format("%d", model.UV_Time);
	SetDlgItemText(IDC_UVTIME, sEditData);

	sEditData.Format("%d", model.UV_Power);
	SetDlgItemText(IDC_UV_POWER, sEditData);

	sEditData.Format("%.01lf", model.UV_Weight);
	SetDlgItemText(IDC_UV_WEIGHT, sEditData);

	sEditData.Format("%.01lf", model.Tilt_Weight_Pre);
	SetDlgItemText(IDC_TILE_WEIGHT_PRE, sEditData);
	sEditData.Format("%.01lf", model.Tilt_Weight_Post);
	SetDlgItemText(IDC_TILE_WEIGHT_POST, sEditData);

	sEditData.Format("%d", model.Tilt_Diretion[0]);
	SetDlgItemText(IDC_TILT_DIRECTION, sEditData);

	sEditData.Format("%d", model.Tilt_Diretion[1]);
	SetDlgItemText(IDC_TILT_DIRECTION2, sEditData);
	sEditData.Format("%d", model.Tilt_Diretion[2]);
	SetDlgItemText(IDC_TILT_DIRECTION3, sEditData);
	sEditData.Format("%d", model.Tilt_Diretion[3]);
	SetDlgItemText(IDC_TILT_DIRECTION4, sEditData);
	sEditData.Format("%d", model.Tilt_Diretion[4]);
	SetDlgItemText(IDC_TILT_DIRECTION5, sEditData);
	
	chk_UvMTFInsp = sysData.m_iMTFUvInsp? TRUE : FALSE;
	chk_Dispense	= sysData.m_iDispensePass? TRUE : FALSE;	//도포 Pass 사용 여부
	chk_DispenseInsp = sysData.m_iDispenseInspPass? TRUE : FALSE;	//도포 검사 Pass
	chk_front =  sysData.m_iFront? TRUE : FALSE;
	chk_AUTO_Z_SEARCH=model.m_AUTO_Z_SEARCH?TRUE:FALSE;

	sEditData.Format("%d", model.m_AUTO_Z_SEARCH_CNT);
	SetDlgItemText(IDC_STC_AUTO_Z_SEARCH_CNT, sEditData);

	sEditData.Format("%.03lf", model.m_AUTO_Z_SEARCH_VAL);
	SetDlgItemText(IDC_STC_AUTO_Z_SEARCH_VAL, sEditData);
	
	chk_PriductComp = sysData.m_iProductComp? TRUE : FALSE;

	if( sysData.iDoorInterlock == 1 )	m_bDoorInterlock = 1;
	else								m_bDoorInterlock = 0;



	sEditData.Format("%d",sysData.m_Epoxy_Change_Count);
	SetDlgItemText(IDC_EPOXY_CHANGE_COUNT,sEditData);

	sEditData.Format("%d",sysData.m_Log_Retention_Period);
	SetDlgItemText(IDC_LOG_RETENTION_PERIOD,sEditData);

	sEditData.Format("%s",sysData.m_Mes_Ip_Number);
	SetDlgItemText(IDC_MES_IP,sEditData);

	sEditData.Format("%s",sysData.m_Factory_Code);
	SetDlgItemText(IDC_MES_FACTORY,sEditData);

	sEditData.Format("%d",sysData.m_Mes_Port_Number);
	SetDlgItemText(IDC_MES_PORT,sEditData);

	
	sEditData.Format("%s",sysData.m_Comp_Factory_Code);
	SetDlgItemText(IDC_MES_COMP_FACTORY,sEditData);

	sEditData.Format("%d",sysData.m_Mes_Comp_Port_Number);
	SetDlgItemText(IDC_MES_COMP_PORT,sEditData);

	sEditData.Format("%.04f", model.m_Line_Pulse);
	SetDlgItemText(IDC_LINE_PULSE, sEditData);
	sEditData.Format("%.04f", model.m_Gen2_Line_Pulse);
	SetDlgItemText(IDC_LINE_PULSE2, sEditData);
	

	sEditData.Format("%.3f", sysData.m_dOffset_Conti_Down_Z);
	SetDlgItemText(IDC_CONTI_OFFSET_Z_DOWN, sEditData);
	m_ComboEpoxy.SetCurSel(sysData.nEpoxyIndex);
	m_ComboUv.SetCurSel(sysData.nUvIndex);

	//포트 설정
	//COMM_LASER, COMM_BARCODE,  COMM_UV,  COMM_LIGHT1,  COMM_LIGHT2, COMM_LIGHT3, MAX_RS232_NO};
	m_ComboLightPort1.SetCurSel(sysData.iCommPort[COMM_LIGHT1] - 1);
	m_ComboLightPort2.SetCurSel(sysData.iCommPort[COMM_LIGHT2] - 1);
	m_ComboLightPort3.SetCurSel(sysData.iCommPort[COMM_LIGHT3] - 1);
	m_ComboLightPort4.SetCurSel(sysData.iCommPort[COMM_LIGHT4] - 1);
	m_ComboLightPort5.SetCurSel(sysData.iCommPort[COMM_LIGHT5] - 1);
	m_ComboLightPort6.SetCurSel(sysData.iCommPort[COMM_LIGHTOC_1ST] - 1);


	m_ComboX100BarcodePort.SetCurSel(sysData.iCommPort[COMM_X100_BCR] - 1);
	m_ComboBarcodePort.SetCurSel(sysData.iCommPort[COMM_BARCODE] - 1);
	m_ComboLaserPort.SetCurSel(sysData.iCommPort[COMM_LASER] - 1);
	m_ComboUvPort.SetCurSel(sysData.iCommPort[COMM_UV] - 1);
	m_ComboUvPort2.SetCurSel(sysData.iCommPort[COMM_UV2] - 1);
	sEditData.Format("%d", model.m_MarkMatchingRate[0]);
	m_clGrid_Mark_Matching.SetItemText(1, 1, sEditData);

	sEditData.Format("%d", model.m_MarkMatchingRate[1]);
	m_clGrid_Mark_Matching.SetItemText(2, 1, sEditData);

	sEditData.Format("%d", model.m_MarkMatchingRate[2]);
	m_clGrid_Mark_Matching.SetItemText(3, 1, sEditData);

	sEditData.Format("%d", model.m_MarkMatchingRate[3]);
	m_clGrid_Mark_Matching.SetItemText(4, 1, sEditData);


	UpdateData(false);
}


void CInfoDlg::OnBnClickedButtonOk()
{
	bool passFlag = password.m_bFlag;
	//if(sysData.m_iAASel==0)
 
	//if(passFlag == false)
	//{
	//	CString strTemp;
	//	CKeyPadDlg keyDlg;

	//	sLangChange.LoadStringA(IDS_STRING891);
	//	keyDlg.m_strKeyPad = sLangChange;	//"Password를 입력하세요."

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



	/*if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}
*/



	if(askMsg("검사 파라미터를 저장 하시겠습니까?")) 
	{
		getData();

		model.Save();
		model.Load();

		sysData.Save();
		sysData.Load();

		putData();
		UVCommand.UV_Shutter_PowerSet(model.UV_Power);// 95);//
	}
}


void CInfoDlg::OnBnClickedButtonCancel()
{
	CDialogEx::OnCancel();
}

//! Auto White Balance의 결과값 표시에 사용
void CInfoDlg::Apply_Result_Auto_White_Balance(double fi_dGain_Red, double fi_dGain_Green, double fi_dGain_Blue)
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}


	if ( fi_dGain_Red > 5.)		fi_dGain_Red = 5.;
	if ( fi_dGain_Green > 5. )	fi_dGain_Green = 5.;
	if ( fi_dGain_Blue > 5. )	fi_dGain_Blue = 5.;


}


void CInfoDlg::OnStnClickedRoughStepAf1()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if(f_num < 20)		f_num = 20;
		if(f_num > 85)		f_num = 85;

		celData.Format("%d", (int)(f_num));
		m_rStep_Af1.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedRoughVelAf1()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if(f_num < 1)		f_num = 1;
		if(f_num > 20)		f_num = 20;

		celData.Format("%.03f", f_num);
		m_rVel_Af1.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedRoughDisAf1()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if(f_num < 0.005)		f_num = 0.005f;
		if(f_num > 0.1)		f_num = 0.03f;

		celData.Format("%0.03f", f_num);
		m_rDis_Af1.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedRoughtAvrCnt()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		int d_num = (int)atoi(dlg.GetstrNum());

		if(d_num < 1)		d_num = 1;
		if(d_num > 30)		d_num = 30;

		celData.Format("%d", d_num);
		m_rAve_Cnt.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedFineDelayAf3()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if(f_num > 2000)		f_num = 2000;

		celData.Format("%d", (int)(f_num));
		m_fDelay_Af3.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedFineDisAf3()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if(f_num < 0.001)		f_num = 0.001f;
		if(f_num > 0.1)		f_num = 0.01f;

		celData.Format("%.03f", f_num);
		m_fDis_Af3.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedFineAvrCnt()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		int d_num = (int)atoi(dlg.GetstrNum());

		if(d_num < 1)		d_num = 1;
		if(d_num > 30)		d_num = 30;

		celData.Format("%d", d_num);
		m_fAve_Cnt.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedLimitSfrCen()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if(f_num < 0.01)		f_num = 0.01f;
		if(f_num > 0.9)			f_num = 0.9f;

		celData.Format("%.03f", (f_num));
		m_Lim_Sfr_Cen.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedLimitSfrSide()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if(f_num < 0.01)		f_num = 0.01f;
		if(f_num > 0.8)			f_num = 0.8f;

		celData.Format("%0.03f", (f_num));
		m_Lim_Sfr_Side.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedLimitSfr()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if(f_num < 0.2)		f_num = 0.2f;	
		if(f_num > 0.5)			f_num = 0.5f;

		celData.Format("%.03f", (f_num));
		m_Limit_Sfr.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedCheckcnt()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if(f_num < 2)		f_num = 2;
		if(f_num > 6)		f_num = 6;

		celData.Format("%d", (int)(f_num));
		m_Check_Cnt.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedMoveOffsetZ()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if(f_num < -0.2)		f_num = -0.2f;
		if(f_num > 0.2)		f_num = 0.2f;

		celData.Format("%.03f", (f_num));
		m_Move_offsetZ.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedUvtime()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if(f_num < 100)		f_num = 100;
		if(f_num > 30000)	f_num = 30000;

		celData.Format("%d", (int)(f_num));
		m_Uv_Time.SetText(celData);
	}
}

void CInfoDlg::OnStnClickedPrevUvOffsetX()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if(f_num < -0.5)		f_num = -0.50;
		if(f_num > 0.5)			f_num = 0.5;

		celData.Format("%.03f", (f_num));
		m_Uv_offset_X.SetText(celData);
	}
}

void CInfoDlg::OnStnClickedPrevUvOffsetY()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if(f_num < -0.5)		f_num = -0.5;
		if(f_num > 0.5)			f_num = 0.5;

		celData.Format("%.03f", (f_num));
		m_Uv_offset_Y.SetText(celData);
	}
}

void CInfoDlg::OnStnClickedPrevUvOffsetZ()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if (f_num < -1.5)		f_num = -1.5;//if(f_num < -0.5)		f_num = -0.5;
		if(f_num > 0.5)			f_num = 0.5;

		celData.Format("%.03f", (f_num));
		m_Uv_offset_Z.SetText(celData);
	}
}

void CInfoDlg::OnStnClickedPrevUvOffsetTx()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if(f_num < -2)		f_num = -2;
		if(f_num > 2)		f_num = 2;

		celData.Format("%.03f", (f_num));
		m_Uv_offset_Tx.SetText(celData);
	}
}

void CInfoDlg::OnStnClickedPrevUvOffsetTy()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if(f_num < -2)		f_num = -2;
		if(f_num > 2)		f_num = 2;

		celData.Format("%.03f", (f_num));
		m_Uv_offset_Ty.SetText(celData);
	}
}

void CInfoDlg::OnStnClickedPrevUvOffsetTh()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if(f_num < -2)		f_num = -2;
		if(f_num > 2)		f_num = 2;

		celData.Format("%.03f", (f_num));
		m_Uv_offset_Th.SetText(celData);
	}
}

void CInfoDlg::OnStnClickedCcdCellSize()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		m_Ccd_Size.SetText(dlg.GetstrNum());
	}
}

void CInfoDlg::OnStnClickedDelayCam6()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if(f_num < 0)		f_num = 0;
		if(f_num > 2000)	f_num = 2000;

		celData.Format("%d", (int)(f_num));
		m_Delay_Cam6.SetText(celData);
	}
}

void CInfoDlg::OnStnClickedDelayCam2()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if(f_num < 0)		f_num = 0;
		if(f_num > 2000)	f_num = 2000;

		celData.Format("%d", (int)(f_num));
		m_Delay_Cam2.SetText(celData);
	}
}

void CInfoDlg::OnStnClickedDelayCam4()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if(f_num < 0)		f_num = 0;
		if(f_num > 2000)	f_num = 2000;

		celData.Format("%d", (int)(f_num));
		m_Delay_Cam4.SetText(celData);
	}
}

void CInfoDlg::OnStnClickedRetryCam5()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if(f_num < 0)		f_num = 0;
		if(f_num > 20)		f_num = 20;

		celData.Format("%d", (int)(f_num));
		m_Retry_Cam5.SetText(celData);
	}
}

void CInfoDlg::OnStnClickedRetryCam2()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if(f_num < 0)		f_num = 0;
		if(f_num > 20)		f_num = 20;

		celData.Format("%d", (int)(f_num));
		m_Retry_Cam2.SetText(celData);
	}
}

void CInfoDlg::OnStnClickedRoughDelayAf1()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if(f_num < 0)			f_num = 0;
		if(f_num > 2000)		f_num = 2000;

		celData.Format("%d", (int)(f_num));
		m_rDelay_Af1.SetText(celData);
	}
}

BOOL CInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	m_SFR_roi_Size_X.SetBkColor(M_COLOR_WHITE);
	m_SFR_roi_Size_Y.SetBkColor(M_COLOR_WHITE);

	m_rDelay_Af1.SetBkColor(M_COLOR_WHITE);
	m_rStep_Af1.SetBkColor(M_COLOR_WHITE);
	m_rDis_Af1.SetBkColor(M_COLOR_WHITE);
	m_rVel_Af1.SetBkColor(M_COLOR_WHITE);
	m_rAve_Cnt.SetBkColor(M_COLOR_WHITE);
	m_AARepeatCount.SetBkColor(M_COLOR_WHITE);
	m_fDelay_Af3.SetBkColor(M_COLOR_WHITE);
	m_fDis_Af3.SetBkColor(M_COLOR_WHITE);
	m_fAve_Cnt.SetBkColor(M_COLOR_WHITE);

	m_Delay_Cam6.SetBkColor(M_COLOR_WHITE);
	m_Retry_Cam5.SetBkColor(M_COLOR_WHITE);
	m_Delay_Cam2.SetBkColor(M_COLOR_WHITE);
	m_Retry_Cam2.SetBkColor(M_COLOR_WHITE);
	m_Delay_Cam4.SetBkColor(M_COLOR_WHITE);

	m_Uv_offset_X.SetBkColor(M_COLOR_WHITE);
	m_Uv_offset_Y.SetBkColor(M_COLOR_WHITE);
	m_Uv_offset_Z.SetBkColor(M_COLOR_WHITE);
	m_Uv_offset_Tx.SetBkColor(M_COLOR_WHITE);
	m_Uv_offset_Ty.SetBkColor(M_COLOR_WHITE);
	m_Uv_offset_Th.SetBkColor(M_COLOR_WHITE);

	m_label_Move_MaxPos_Fine.SetBkColor(M_COLOR_WHITE);

	m_Limit_Sfr.SetBkColor(M_COLOR_WHITE);
	m_Ccd_Size.SetBkColor(M_COLOR_WHITE);


	m_Lim_Sfr_Cen.SetBkColor(M_COLOR_WHITE);
	m_Lim_Sfr_Side.SetBkColor(M_COLOR_WHITE);
	m_Check_Cnt.SetBkColor(M_COLOR_WHITE);
	m_Move_offsetZ.SetBkColor(M_COLOR_WHITE);

	m_Uv_Time.SetBkColor(M_COLOR_WHITE);
	m_Uv_Power.SetBkColor(M_COLOR_WHITE);
	m_Uv_Weight.SetBkColor(M_COLOR_WHITE);

	m_Tilt_Weight_Pre.SetBkColor(M_COLOR_WHITE);
	m_Tilt_Weight_Post.SetBkColor(M_COLOR_WHITE);
	
	m_MES_IP.SetBkColor(M_COLOR_WHITE);
	m_MES_PORT.SetBkColor(M_COLOR_WHITE);
	m_MES_Comp_PORT.SetBkColor(M_COLOR_WHITE);
	m_MES_Factory.SetBkColor(M_COLOR_WHITE);
	m_MES_Comp_Factory.SetBkColor(M_COLOR_WHITE);

	m_Laser_In_X2.SetBkColor(M_COLOR_WHITE);
	m_Laser_In_X3.SetBkColor(M_COLOR_WHITE);
	m_Laser_In_X4.SetBkColor(M_COLOR_WHITE);
	m_Laser_In_Y2.SetBkColor(M_COLOR_WHITE);
	m_Laser_In_Y3.SetBkColor(M_COLOR_WHITE);
	m_Laser_In_Y4.SetBkColor(M_COLOR_WHITE);

	m_Laser_Out_X2.SetBkColor(M_COLOR_WHITE);
	m_Laser_Out_X3.SetBkColor(M_COLOR_WHITE);
	m_Laser_Out_X4.SetBkColor(M_COLOR_WHITE);
	m_Laser_Out_Y2.SetBkColor(M_COLOR_WHITE);
	m_Laser_Out_Y3.SetBkColor(M_COLOR_WHITE);
	m_Laser_Out_Y4.SetBkColor(M_COLOR_WHITE);

	m_Laser_Pcb_X2.SetBkColor(M_COLOR_WHITE);
	m_Laser_Pcb_X3.SetBkColor(M_COLOR_WHITE);
	m_Laser_Pcb_X4.SetBkColor(M_COLOR_WHITE);
	m_Laser_Pcb_Y2.SetBkColor(M_COLOR_WHITE);
	m_Laser_Pcb_Y3.SetBkColor(M_COLOR_WHITE);
	m_Laser_Pcb_Y4.SetBkColor(M_COLOR_WHITE);

	m_Insp_pcb_tx.SetBkColor(M_COLOR_WHITE);
	m_Insp_pcb_ty.SetBkColor(M_COLOR_WHITE);


	m_Revision_No.SetBkColor(M_COLOR_WHITE);
	m_Epoxy_Change_Count.SetBkColor(M_COLOR_WHITE);
	m_Log_Retention_Period.SetBkColor(M_COLOR_WHITE);

	m_Line_Pulse.SetBkColor(M_COLOR_WHITE);
	m_Gen2_Line_Pulse.SetBkColor(M_COLOR_WHITE);

	CString str="";
	str.Format("%s",sysData.m_Mes_Ip_Number);
	m_sMES_IP = str;


	str.Format("%s",sysData.m_Factory_Code);
	m_sMES_Factory = str;

	str.Format("%s",sysData.m_Comp_Factory_Code);
	m_sMES_Comp_Factory = str;
	
	UpdateData(FALSE);
	
	InitGridCtrl_MarkMatching();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CInfoDlg::OnBnClickedCheckPassUv()
{
	UpdateData(true);
}

void CInfoDlg::OnStnClickedFineDisMax()
{
	CString celData="";
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if(f_num < -0.3)		f_num = -0.3f;
		if(f_num > 0.3)		f_num = 0.3f;

		celData.Format("%.03f", (f_num));
		m_label_Move_MaxPos_Fine.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedRoiSizeX()
{
	CString celData="";
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if(f_num < 3)			f_num = 3;
		if(f_num > 200)			f_num = 100;

		celData.Format("%d", (int)(f_num));
		m_SFR_roi_Size_X.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedRoiSizeY()
{
	CString celData="";
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if(f_num < 1)			f_num = 1;
		if(f_num > 200)			f_num = 200;

		celData.Format("%d", (int)(f_num));
		m_SFR_roi_Size_Y.SetText(celData);
	}
}


int CInfoDlg::calcImageBright()
{
	int targetBright = 100;
	float Gain = 50, CalibrationGain = 0.1f;
	int grabRetry = 10;

	vision.clearOverlay();

	bool bRet = MIU.GetCurrentInfo_Exposure_From_CCD_IMX135();
	if ( bRet == false )
	{
		errMsg2(Task.AutoFlag, MIU.sLogMessage);
		return -1;
	}

	int firstTime = gMIUDevice.IMX135.iExposureTime_Current;
	bRet = MIU.Set_ExposureTime_To_CCD_IMX135(firstTime);
	if ( bRet == false )
	{
		errMsg2(Task.AutoFlag, MIU.sLogMessage);
		return -1;
	}


	for(int i=0; i<grabRetry; i++)
	{
		vision.MilBufferUpdate();
		checkMessage();
	}

	int firstBright = getImageBright();

	if(firstBright == 100)
		return firstTime;


	int exposureTime = (int)(firstTime + (targetBright-firstBright) * Gain);
	bRet = MIU.Set_ExposureTime_To_CCD_IMX135(exposureTime);
	if ( bRet == false )
	{
		errMsg2(Task.AutoFlag, MIU.sLogMessage);
		return -1;
	}

	for(int i=0; i<grabRetry; i++)
	{
		vision.MilBufferUpdate();
		checkMessage();
	}

	int secondBright = getImageBright();

	if(secondBright == 100)
		return exposureTime;

	float rate = (firstTime-exposureTime) / (float)(firstBright-secondBright);

	int exposureTime2 = (int)(exposureTime + (targetBright-secondBright) * rate);
	bRet = MIU.Set_ExposureTime_To_CCD_IMX135(exposureTime2);
	if ( bRet == false )
	{
		errMsg2(Task.AutoFlag, MIU.sLogMessage);
		return -1;
	}

	for(int i=0; i<grabRetry; i++)
	{
		vision.MilBufferUpdate();
		checkMessage();
	}

	int thirdBright = getImageBright();
	if(thirdBright == 100)
		return exposureTime2;

	float rate2 = (secondBright-exposureTime2) / (float)(secondBright-thirdBright);

	int exposureTime3 = (int)(exposureTime2 + (targetBright-thirdBright) * rate);
	bRet = MIU.Set_ExposureTime_To_CCD_IMX135(exposureTime3);
	if ( bRet == false )
	{
		errMsg2(Task.AutoFlag, MIU.sLogMessage);
		return -1;
	}

	for(int i=0; i<grabRetry; i++)
	{
		vision.MilBufferUpdate();
		checkMessage();
	}

	int fourthBright = getImageBright();

	vision.drawOverlay(CCD) ;

	return exposureTime3;
}

int CInfoDlg::getImageBright()
{
	float roi_size = 0.25f;
	int avgVal = 0;

	int sizeX = MbufInquire(vision.MilProcImageChild[4], M_SIZE_X, NULL);
	int sizeY = MbufInquire(vision.MilProcImageChild[4], M_SIZE_Y, NULL);
	int pitch = MbufInquire(vision.MilProcImageChild[4], M_PITCH, NULL);

	int sx, sy, ex, ey, pos, sum;

	sx = (int)(sizeX/2 - sizeX*roi_size/2 + 0.5);
	ex = (int)(sizeX/2 + sizeX*roi_size/2 + 0.5);

	sy = (int)(sizeY/2 - sizeY*roi_size/2 + 0.5);
	ey = (int)(sizeY/2 + sizeY*roi_size/2 + 0.5);

	sum = 0;
	for(int y=sy; y<ey; y++)
	{
		pos = y*pitch + sx;
		for(int x=sx; x<ex; x++)
		{
			sum += vision.MilImageBuffer[3][pos];
			sum += vision.MilImageBuffer[4][pos];
			sum += vision.MilImageBuffer[5][pos];
			pos++;
		}
	}

	avgVal = (int)(sum / ( (ex-sx) * (ey-sy) * 3.0) + 0.5);

	return avgVal;
}

void CInfoDlg::OnBnClickedCheckDefectInsp()
{
	UpdateData(true);
}


void CInfoDlg::OnBnClickedCheck1stAaEnable()
{
	UpdateData(true);
}


void CInfoDlg::OnBnClickedRadioAamodeOptical()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CInfoDlg::EnableControl_AF()
{

}

void CInfoDlg::ShowSfrModeControl(bool mode)
{
	
}


void CInfoDlg::OnStnClickedPointInX2()
{
	CString celData="";
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());


		celData.Format("%.02lf", f_num);
		m_Laser_In_X2.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedPointInX3()
{
	CString celData="";
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());


		celData.Format("%.02lf", f_num);
		m_Laser_In_X3.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedPointInX4()
{
	CString celData="";
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());


		celData.Format("%.02lf", f_num);
		m_Laser_In_X4.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedPointOutX2()
{
	CString celData="";
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());
		celData.Format("%.02lf", f_num);
		m_Laser_Out_X2.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedPointOutX3()
{
	CString celData="";
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());


		celData.Format("%.02lf", f_num);
		m_Laser_Out_X3.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedPointOutX4()
{
	CString celData="";
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());


		celData.Format("%.02lf", f_num);
		m_Laser_Out_X4.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedPointInY2()
{
	CString celData="";
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());


		celData.Format("%.02lf", f_num);
		m_Laser_In_Y2.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedPointOutY2()
{
	CString celData="";
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());


		celData.Format("%.02lf", f_num);
		m_Laser_Out_Y2.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedPointOutY3()
{
	CString celData="";
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		celData.Format("%.02lf", f_num);
		m_Laser_Out_Y3.SetText(celData);
	}
}

void CInfoDlg::OnStnClickedPointOutY4()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		celData.Format("%.02lf", f_num);
		m_Laser_Out_Y4.SetText(celData);
	}
}

void CInfoDlg::OnStnClickedPointInY4()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		celData.Format("%.02lf", f_num);
		m_Laser_In_Y4.SetText(celData);
	}
}

void CInfoDlg::OnStnClickedPointInY3()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());


		celData.Format("%.02lf", f_num);
		m_Laser_In_Y3.SetText(celData);
	}
}

void CInfoDlg::OnBnClickedCheckPassDispense()
{
	UpdateData(true);
	if( chk_Dispense == TRUE )
		chk_DispenseInsp = true;

	UpdateData(false);
}

void CInfoDlg::OnBnClickedCheckPassDispenseInsp()
{
	UpdateData(true);
	if( chk_Dispense == TRUE )	chk_DispenseInsp = true;
	UpdateData(false);
}


void CInfoDlg::OnBnClickedCheckProductComplete()
{
	UpdateData(true);
}

void CInfoDlg::OnBnClickedCheckDoorInterlock()
{
	m_bDoorInterlock = !m_bDoorInterlock;
}

void CInfoDlg::OnStnClickedEpoxyChangeTime()
{
	CString celData="";
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		m_Epoxy_Change_Count.SetText(dlg.GetstrNum());
	}
	UpdateData(FALSE);
}

void CInfoDlg::OnStnClickedMesIp()
{
	CString celData="";
	CKeyPadDlg keyDlg(15, (LPTSTR)(LPCTSTR)celData);

	if (keyDlg.DoModal()==IDOK)
	{
		celData = keyDlg.GetstrKeypad();
		int strLength = celData.GetLength();
		if(strLength<1)
		{
			sLangChange.LoadStringA(IDS_STRING611);
			errMsg2(Task.AutoFlag, sLangChange);	//IP가 비정상입니다.
			return;
		}
		m_MES_IP.SetText(celData);
	}
	else
	{
		return;
	}
}


void CInfoDlg::OnStnClickedMesFactory()
{
	CKeyPadDlg keyDlg;
	CString strTemp="";
	keyDlg.m_strKeyPad = "Input Code";
		
	if (keyDlg.DoModal()==IDOK)
	{
		strTemp = keyDlg.GetstrKeypad();
		int strLength = strTemp.GetLength();
		if(strLength<1)
		{
			sLangChange.LoadStringA(IDS_STRING1284);	//설비코드명이 비정상입니다.
			errMsg2(Task.AutoFlag, sLangChange);
			return;
		}
		m_MES_Factory.SetText(strTemp);
	}
	else
	{
		return;
	}
}


void CInfoDlg::OnStnClickedMesPort()
{
	CString celData="";
	CString strTemp="";
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
//		m_MES_PORT.SetText(dlg.GetstrNum());
		strTemp = dlg.GetstrNum();

		GetDlgItem(IDC_MES_PORT)->SetWindowText(strTemp);	
	}
	else
	{
		return;
	}
}

void CInfoDlg::OnBnClickedRadioIcCircle()
{

}


void CInfoDlg::OnBnClickedRadioIcDistortioncenter()
{

}


void CInfoDlg::OnBnClickedRadioAamodeMarkcent()
{

}


void CInfoDlg::OnStnClickedRetentionPeriod()
{
	CString celData="";
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		m_Log_Retention_Period.SetText(dlg.GetstrNum());
	}
	UpdateData(FALSE);
}


void CInfoDlg::OnStnClickedMesCompFactory()
{
	CKeyPadDlg keyDlg;
	CString strTemp="";
	keyDlg.m_strKeyPad = "Input Code";

	
	if (keyDlg.DoModal()==IDOK)
	{
		strTemp = keyDlg.GetstrKeypad();
		int strLength = strTemp.GetLength();
		if(strLength<1)
		{
			sLangChange.LoadStringA(IDS_STRING1284);	//설비코드명이 비정상입니다.
			errMsg2(Task.AutoFlag, sLangChange);
			return;
		}
		m_MES_Comp_Factory.SetText(strTemp);
	}
	else
	{
		return;
	}
}


void CInfoDlg::OnStnClickedMesCompPort()
{
	CString celData="";
	CString strTemp="";
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
//		m_MES_PORT.SetText(dlg.GetstrNum());
		strTemp = dlg.GetstrNum();

		GetDlgItem(IDC_MES_COMP_PORT)->SetWindowText(strTemp);	

	}
	else
	{
		return;
	}
}


void CInfoDlg::OnStnClickedLinePulse()
{
	CString celData="";
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		m_Line_Pulse.SetText(dlg.GetstrNum());
	}
	UpdateData(FALSE);
}


void CInfoDlg::OnBnClickedButtonInitial()
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
		CString strTemp="";
		CKeyPadDlg keyDlg;

		sLangChange.LoadStringA(IDS_STRING891);
		keyDlg.m_strKeyPad = sLangChange;	//"Password를 입력하세요."

		if (keyDlg.DoModal()==IDOK)
		{
			strTemp = keyDlg.GetstrKeypad();

			passFlag = true;//strTemp.CompareNoCase(password.m_szPassword) ? false : true;
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

	sLangChange.LoadStringA(IDS_STRING1436);	//파라미터를 초기화 하시겠습니까?
	if(askMsg(sLangChange))
	{
		model.Load();
		sysData.Load();
		work.Load();

		putData();

//		! UV Lamp 장치에 Output Intensity를 실제로 적용한다.
		//int iRet = UVCommand.Set_Output_Intensity_1_Step(model.UV_Intensity);
		Sleep(50);
//		int iRet = UVCommand.Set_Shutter_AutoTime_1_Step(model.UV_Time/1000);

		CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
		if ( pFrame != NULL )
		{
			pFrame->func_Set_SFR_N_Type();
		}
	}
}


void CInfoDlg::OnBnClickedRadioAamodeDistortioncenter()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CInfoDlg::OnBnClickedCheckPassFCurtain()
{
	UpdateData(true);
}

void CInfoDlg::OnBnClickedRadioV(UINT msg)
{
	UpdateData(TRUE);
	CString str="";
	str.Format(_T("%d"),m_AARoiSelect);
	//AfxMessageBox(str);
	UpdateData(FALSE);
}


void CInfoDlg::OnStnClickedUvWeight()
{
	CString celData="";
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if(f_num < 0)		f_num = 0.0;
		if(f_num > 1)	f_num = 1.0;

		celData.Format("%.01lf", f_num);
		m_Uv_Weight.SetText(celData);
	}
}


void CInfoDlg::OnBnClickedChkAutoZSearch()
{
	UpdateData(true);
}


void CInfoDlg::OnStnClickedStcAutoZSearchCnt()
{
	CString celData="";
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		int f_num = atoi(dlg.GetstrNum());

		celData.Format("%d", f_num);
		m_AUTO_Z_SEARCH_CNT.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedStcAutoZSearchVal()
{
	CString celData="";
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		celData.Format("%.3lf", f_num);
		m_AUTO_Z_SEARCH_VAL.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedTileWeightX()
{
	CString celData="";
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if(f_num < -1)		f_num = -1.0;
		if(f_num > 1)	f_num = 1.0;

		celData.Format("%.01lf", f_num);
		m_Tilt_Weight_Pre.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedTileWeightY()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if(f_num < -1)		f_num = -1.0;
		if(f_num > 1)	f_num = 1.0;

		celData.Format("%.01lf", f_num);
		m_Tilt_Weight_Post.SetText(celData);
	}
}


void CInfoDlg::OnBnClickedCheckUvInsp()
{
	UpdateData(true);
}


void CInfoDlg::OnBnClickedCheckLaserInsp()
{
	UpdateData(true);
}


void CInfoDlg::OnStnClickedContiOffsetZDown()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if (dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if (f_num > 0.5)		f_num = 0.5;
		if (f_num < -0.5)			f_num = -0.5;

		celData.Format("%.03f", (f_num));
		m_Conti_Z_Down.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedInspPcbTx()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString celData = "";
	GetDlgItemText(IDC_INSP_PCB_TX, celData);
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if (dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if (f_num > 6)
		{
			f_num = 6.0;
		}
		if (f_num < -6)
		{
			f_num = -6.0;
		}
		celData.Format("%.03lf", f_num);
		m_Insp_pcb_tx.SetText(celData);
	}
}

void CInfoDlg::OnStnClickedInspPcbTy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString celData = "";
	GetDlgItemText(IDC_INSP_PCB_TY, celData);
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if (dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());
		if (f_num > 6)
		{
			f_num = 6.0;
		}
		if (f_num < -6)
		{
			f_num = -6.0;
		}
		celData.Format("%.03lf", f_num);
		m_Insp_pcb_ty.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedPointPcbX2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString celData = "";
	GetDlgItemText(IDC_POINT_PCB_X2, celData);
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if (dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());
		celData.Format("%.02lf", f_num);
		m_Laser_Pcb_X2.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedPointPcbX3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString celData = "";
	GetDlgItemText(IDC_POINT_PCB_X3, celData);
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if (dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());
		celData.Format("%.02lf", f_num);
		m_Laser_Pcb_X3.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedPointPcbX4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString celData = "";
	GetDlgItemText(IDC_POINT_PCB_X4, celData);
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if (dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());
		celData.Format("%.02lf", f_num);
		m_Laser_Pcb_X4.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedPointPcbY2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString celData = "";
	GetDlgItemText(IDC_POINT_PCB_Y2, celData);
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if (dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());
		celData.Format("%.02lf", f_num);
		m_Laser_Pcb_Y2.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedPointPcbY3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString celData = "";
	GetDlgItemText(IDC_POINT_PCB_Y3, celData);
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if (dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());
		celData.Format("%.02lf", f_num);
		m_Laser_Pcb_Y3.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedPointPcbY4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString celData = "";
	GetDlgItemText(IDC_POINT_PCB_Y4, celData);
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if (dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());
		celData.Format("%.02lf", f_num);
		m_Laser_Pcb_Y4.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedUvPower()
{
	// TODO: Add your control notification handler code here
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if (dlg.DoModal() == IDOK)
	{
		int i_num = atoi(dlg.GetstrNum());

		if (i_num < 1)		i_num = 0;
		if (i_num > 100)	i_num = 100;

		celData.Format("%d", i_num);
		m_Uv_Power.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedLinePulse2()
{
	// TODO: Add your control notification handler code here
	CString celData = "";
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if (dlg.DoModal() == IDOK)
	{
		m_Gen2_Line_Pulse.SetText(dlg.GetstrNum());
	}
	UpdateData(FALSE);
}


void CInfoDlg::OnStnClickedTiltDirection()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if (dlg.DoModal() == IDOK)
	{
		int mNum = atoi(dlg.GetstrNum());

		if (mNum > 0)
		{
			mNum = 1;
		}
		else
		{
			mNum = -1;
		}

		celData.Format("%d", (mNum));
		m_Tilt_Direction[0].SetText(celData);
	}
}


void CInfoDlg::OnStnClickedTiltDirection2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if (dlg.DoModal() == IDOK)
	{
		int mNum = atoi(dlg.GetstrNum());

		if (mNum > 0)
		{
			mNum = 1;
		}
		else
		{
			mNum = -1;
		}

		celData.Format("%d", (mNum));
		m_Tilt_Direction[1].SetText(celData);
	}
}


void CInfoDlg::OnStnClickedTiltDirection3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if (dlg.DoModal() == IDOK)
	{
		int mNum = atoi(dlg.GetstrNum());

		if (mNum > 0)
		{
			mNum = 1;
		}
		else
		{
			mNum = -1;
		}

		celData.Format("%d", (mNum));
		m_Tilt_Direction[2].SetText(celData);
	}
}


void CInfoDlg::OnStnClickedTiltDirection4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if (dlg.DoModal() == IDOK)
	{
		int mNum = atoi(dlg.GetstrNum());

		if (mNum > 0)
		{
			mNum = 1;
		}
		else
		{
			mNum = -1;
		}

		celData.Format("%d", (mNum));
		m_Tilt_Direction[3].SetText(celData);
	}
}


void CInfoDlg::OnStnClickedTiltDirection5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if (dlg.DoModal() == IDOK)
	{
		int mNum = atoi(dlg.GetstrNum());

		if (mNum > 0)
		{
			mNum = 1;
		}
		else
		{
			mNum = -1;
		}

		celData.Format("%d", (mNum));
		m_Tilt_Direction[4].SetText(celData);
	}
}


void CInfoDlg::OnBnClickedCheckXyChange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
}


void CInfoDlg::OnBnClickedCheckIrChartUse()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
}


void CInfoDlg::OnBnClickedCheckSfrMaxTest()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
}


void CInfoDlg::OnStnClickedAaRepeatCount()
{
	// TODO: Add your control notification handler code here
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if (dlg.DoModal() == IDOK)
	{
		int d_num = (int)atoi(dlg.GetstrNum());

		if (d_num < 0)		d_num = 0;
		if (d_num > 50)		d_num = 50;

		celData.Format("%d", d_num);
		m_AARepeatCount.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedBcrIp()
{
	// TODO: Add your control notification handler code here
	CString celData = "";
	CString strTemp;

	CGetNumDlg dlg(20, (LPTSTR)(LPCTSTR)celData);

	if (dlg.DoModal() == IDOK)
	{
		CString d_num = dlg.GetstrNum();
		celData.Format("%s", d_num);
		m_BCR_IP.SetText(celData);
	}
}


void CInfoDlg::OnStnClickedBcrPort()
{
	// TODO: Add your control notification handler code here
	CString celData = "";
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if (dlg.DoModal() == IDOK)
	{
		int d_num = (int)atoi(dlg.GetstrNum());
		celData.Format("%d", (int)(d_num));
		m_BCR_Port.SetText(celData);
	}
}
