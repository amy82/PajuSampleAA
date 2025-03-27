#pragma once
#include "Label/Label.h"
#include "afxwin.h"

// CInfoDlg 대화 상자입니다.

class CInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInfoDlg)

public:
	CInfoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CInfoDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_INFO_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:
	int		calcImageBright();
	int		getImageBright();

public:
	CLabel	m_SFR_roi_Size_X;
	CLabel	m_SFR_roi_Size_Y;
	CLabel	m_BCR_IP;
	CLabel	m_BCR_Port;

	CLabel	m_rDelay_Af1;
	CLabel	m_rStep_Af1;
	CLabel	m_rDis_Af1;
	CLabel	m_rVel_Af1;
	CLabel	m_rAve_Cnt;
	CLabel  m_AARepeatCount;
	CLabel	m_fDelay_Af3;
	CLabel	m_fDis_Af3;
	CLabel	m_fAve_Cnt;

	CLabel	m_Delay_Cam6;
	CLabel	m_Retry_Cam5;
	CLabel	m_Delay_Cam2;
	CLabel	m_Retry_Cam2;
	CLabel	m_Delay_Cam4;


	CLabel	m_Laser_In_X2;
	CLabel	m_Laser_In_X3;
	CLabel	m_Laser_In_X4;
	CLabel	m_Laser_In_Y2;
	CLabel	m_Laser_In_Y3;
	CLabel	m_Laser_In_Y4;

	CLabel	m_Laser_Out_X2;
	CLabel	m_Laser_Out_X3;
	CLabel	m_Laser_Out_X4;
	CLabel	m_Laser_Out_Y2;
	CLabel	m_Laser_Out_Y3;
	CLabel	m_Laser_Out_Y4;

	CLabel	m_Laser_Pcb_X2;
	CLabel	m_Laser_Pcb_X3;
	CLabel	m_Laser_Pcb_X4;
	CLabel	m_Laser_Pcb_Y2;
	CLabel	m_Laser_Pcb_Y3;
	CLabel	m_Laser_Pcb_Y4;

	CLabel	m_Insp_pcb_tx;
	CLabel	m_Insp_pcb_ty;


	CLabel  m_Conti_Z_Down;
	CLabel	m_Uv_offset_X;
	CLabel	m_Uv_offset_Y;
	CLabel	m_Uv_offset_Z;
	CLabel	m_Uv_offset_Tx;
	CLabel	m_Uv_offset_Ty;
	CLabel	m_Uv_offset_Th;

	CLabel	m_Limit_Sfr;
	CLabel	m_Ccd_Size;

	CLabel	m_Lim_Sfr_Cen;
	CLabel	m_Lim_Sfr_Side;	
	CLabel	m_Check_Cnt;
	CLabel	m_Move_offsetZ;

	CLabel	m_Uv_Time;
	CLabel  m_Uv_Power;
	CLabel	m_label_Move_MaxPos_Fine;


	BOOL	m_bDoorInterlock;
	CLabel	m_Revision_No;
	CLabel	m_Epoxy_Change_Count;
	CLabel	m_Log_Retention_Period;

	CLabel	m_AUTO_Z_SEARCH_CNT;
	CLabel	m_AUTO_Z_SEARCH_VAL;

	void	getData();
	void	putData();
	void	EnableControl_AF();
	
	//! Auto White Balance의 결과값 표시에 사용
	void Apply_Result_Auto_White_Balance(double fi_dGain_Red, double fi_dGain_Green, double fi_dGain_Blue);

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnBnClickedCheckPassUv();
	
	BOOL m_bPassUV;
	BOOL m_bDefectInspPass;
	BOOL m_bStainInspPass;
	
	BOOL m_b1stAaEnable;
	BOOL chk_Dispense;
	BOOL chk_UvMTFInsp;
	BOOL chk_DispenseInsp;
	BOOL chk_PriductComp;
	BOOL m_bOldQuadMTF;
	BOOL m_bLaserInsp;
	BOOL m_bAlignCamInsp;
	BOOL m_bSfrMaxValueInsp;
	BOOL m_bEpoxyLaserInspPass;
	BOOL m_bDicChange;
	BOOL m_bIrChartUse;
	afx_msg void OnStnClickedRoughStepAf1();
	afx_msg void OnStnClickedRoughVelAf1();
	afx_msg void OnStnClickedRoughDisAf1();
	afx_msg void OnStnClickedRoughtAvrCnt();
	afx_msg void OnStnClickedFineDelayAf3();
	afx_msg void OnStnClickedFineDisAf3();
	afx_msg void OnStnClickedFineAvrCnt();
	afx_msg void OnStnClickedLimitSfrCen();
	afx_msg void OnStnClickedLimitSfrSide();
	afx_msg void OnStnClickedLimitSfr();
	afx_msg void OnStnClickedCheckcnt();
	afx_msg void OnStnClickedMoveOffsetZ();
	afx_msg void OnStnClickedUvtime();
	afx_msg void OnStnClickedPrevUvOffsetX();
	afx_msg void OnStnClickedPrevUvOffsetY();
	afx_msg void OnStnClickedPrevUvOffsetZ();
	afx_msg void OnStnClickedPrevUvOffsetTx();
	afx_msg void OnStnClickedPrevUvOffsetTy();
	afx_msg void OnStnClickedPrevUvOffsetTh();
	afx_msg void OnStnClickedCcdCellSize();
	afx_msg void OnStnClickedDelayCam6();
	afx_msg void OnStnClickedDelayCam2();
	afx_msg void OnStnClickedDelayCam4();
	afx_msg void OnStnClickedRetryCam5();
	afx_msg void OnStnClickedRetryCam2();
	afx_msg void OnStnClickedRoughDelayAf1();
	virtual BOOL OnInitDialog();

	afx_msg void OnStnClickedFineDisMax();
	afx_msg void OnStnClickedLensRotaterLimit();
	afx_msg void OnStnClickedRoiSizeX();
	afx_msg void OnStnClickedRoiSizeY();
	afx_msg void OnStnClickedExpTimeInput2();
	afx_msg void OnStnClickedBlowTimePcb();
	afx_msg void OnBnClickedCheckDefectInsp();
	afx_msg void OnBnClickedCheck1stAaEnable();
	afx_msg void OnBnClickedRadioAamodeOptical();

	int m_iAlignMode;		// 광축 Align 모드
	int m_nMTF_INSP_Cnt;	// MTF Final 검사 측정 Point(17 or 25 Point)
	void ShowSfrModeControl(bool mode);

	afx_msg void OnBnClickedRadioC();
	afx_msg void OnBnClickedRadioB();
	afx_msg void OnBnClickedRadioA();
//	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnStnClickedPointInX2();
	afx_msg void OnStnClickedPointInX3();
	afx_msg void OnStnClickedPointInX4();
	afx_msg void OnStnClickedPointOutX2();
	afx_msg void OnStnClickedPointOutX3();
	afx_msg void OnStnClickedPointOutX4();
	afx_msg void OnStnClickedPointInY2();
	afx_msg void OnStnClickedPointOutY2();
	afx_msg void OnStnClickedPointOutY3();
	afx_msg void OnStnClickedPointOutY4();
	afx_msg void OnStnClickedPointInY4();
	afx_msg void OnStnClickedPointInY3();
	afx_msg void OnBnClickedCheckPassDispense();
	afx_msg void OnBnClickedCheckPassDispenseInsp();
	afx_msg void OnBnClickedCheckProductComplete();
	afx_msg void OnBnClickedCheckDoorInterlock();
	afx_msg void OnStnClickedEpoxyChangeTime();
	CLabel m_MES_IP;
	afx_msg void OnStnClickedMesIp();
	afx_msg void OnStnClickedMesFactory();
	CLabel m_MES_Factory;
	CLabel m_MES_PORT;
	CLabel m_MES_Comp_Factory;
	CLabel m_MES_Comp_PORT;
	CLabel m_MES_Q_PORT;
	afx_msg void OnStnClickedMesPort();
	CString m_sMES_IP;
	CString m_sMES_Factory;
	CString m_sMES_Comp_Factory;
	afx_msg void OnStnClickedEditMtfOffset();
	bool bCircle;
	bool bDistortionCenter;
	afx_msg void OnBnClickedRadioIcCircle();
	afx_msg void OnBnClickedRadioIcDistortioncenter();
	afx_msg void OnBnClickedRadioAamodeMarkcent();
	int m_RESIVION_NO;
	CLabel m_ResivionNo;
	afx_msg void OnStnClickedRetentionPeriod();
	afx_msg void OnStnClickedMes();
	afx_msg void OnStnClickedMesCompFactory();
	afx_msg void OnStnClickedMesCompPort();
	afx_msg void OnStnClickedLinePulse();
	CLabel m_Line_Pulse;
	CLabel m_Gen2_Line_Pulse;


	afx_msg void OnBnClickedButtonInitial();
	afx_msg void OnBnClickedRadioAamodeDistortioncenter();
	BOOL chk_front;
	BOOL chk_AUTO_Z_SEARCH;
	afx_msg void OnBnClickedCheckPassFCurtain();
	afx_msg void OnBnClickedRadioV(UINT msg);
	int m_AARoiSelect;
	CLabel m_Uv_Weight;
	CLabel m_Tilt_Weight_Pre;
	CLabel m_Tilt_Weight_Post;
	CLabel m_Tilt_Direction[5];
	afx_msg void OnStnClickedUvWeight();
	afx_msg void OnBnClickedChkAutoZSearch();
	afx_msg void OnStnClickedStcAutoZSearchCnt();
	afx_msg void OnStnClickedStcAutoZSearchVal();
	afx_msg void OnStnClickedTileWeightX();
	afx_msg void OnStnClickedTileWeightY();
	afx_msg void OnBnClickedCheckUvInsp();

public:
	CComboBox m_ComboUv;
	CComboBox m_ComboEpoxy;
	CComboBox m_ComboLightPort1;//백두 조명
	CComboBox m_ComboLightPort2;//irv chart 조명
	CComboBox m_ComboLightPort3;//irv oc 조명
	CComboBox m_ComboBarcodePort;
	CComboBox m_ComboX100BarcodePort;
	CComboBox m_ComboLaserPort;
	CComboBox m_ComboUvPort;
	CComboBox m_ComboUvPort2;
public:
	//Grid
	CGridCtrl m_clGrid_Mark_Matching;
	void	InitGridCtrl_MarkMatching();
	int MarkRow;
	int MarkCol;
	//
	afx_msg void OnDBClickedGridMark(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedCheckLaserInsp();
	afx_msg void OnStnClickedContiOffsetZDown();
	afx_msg void OnStnClickedInspPcbTx();
	afx_msg void OnStnClickedInspPcbTy();
	afx_msg void OnStnClickedPointPcbX2();
	afx_msg void OnStnClickedPointPcbX3();
	afx_msg void OnStnClickedPointPcbX4();
	afx_msg void OnStnClickedPointPcbY2();
	afx_msg void OnStnClickedPointPcbY3();
	afx_msg void OnStnClickedPointPcbY4();
	afx_msg void OnStnClickedUvPower();
	afx_msg void OnStnClickedLinePulse2();
	afx_msg void OnStnClickedTiltDirection();
	afx_msg void OnStnClickedTiltDirection2();
	afx_msg void OnStnClickedTiltDirection3();
	afx_msg void OnStnClickedTiltDirection4();
	afx_msg void OnStnClickedTiltDirection5();
	afx_msg void OnBnClickedCheckXyChange();
	afx_msg void OnBnClickedCheckIrChartUse();
	CComboBox m_ComboLightPort4;
	CComboBox m_ComboLightPort5;
	CComboBox m_ComboLightPort6;
	afx_msg void OnBnClickedCheckSfrMaxTest();
	afx_msg void OnStnClickedAaRepeatCount();
	afx_msg void OnStnClickedBcrIp();
	afx_msg void OnStnClickedBcrPort();
};
