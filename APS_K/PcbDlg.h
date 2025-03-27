#pragma once


#include "Library/AutoRepeat/AutoRepeatButton.h"
#include "afxwin.h"
#include "ContinuousButton.h"

//#include "c:\documents and settings\user\바탕 화면\aa bonder-20130723\label\label.h"
//#include "c:\documents and settings\user\바탕 화면\aa bonder-20130723\label\label.h"
// CPcbDlg 대화 상자입니다.

class CPcbDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPcbDlg)

public:
	CPcbDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPcbDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_PCB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	bool	timerRunFlag;

	void	setInterface();
	void	initMarkGrid();
	void	ctrlLiveButton();
	void	getMarkSize();
	void	dispMarkImage();
	void	clickedMarkDisp(int iMarkNo);

	void	getData();
	void	dispData();


	int		pushErrCnt,  vaccumErrCnt;

	void	changeColorVaccumBtn();			/* Vaccum 버튼 색상 바꾸기 */
	void	changeColorMotorPosBtn();		/* 모터 위치 별 색상 바꾸기 */
	void	changeColorVaccumSolBtn();			/* Vaccum 버튼 색상 바꾸기 */

	void	changeColorLaserBtn();			// Laser Lift 색상 바꾸기

	void	changeColorLaserCylinderLaserTabBtn();

	bool	checkCurInspXMotorPos(int iPos);
	bool	checkCurMotorPos(int iPos);		/* 모터 위치 확인 */
	bool	checkCurMotorPosZ(int iPos);	/* 모터 위치 확인 */
	bool    checkCurLensMotorPos(int iPos);
	void	DigLedputData(int iMark);

	bool func_MovingInterlock();


	int m_iMarkDispSizeX;
	int m_iMarkDispSizeY;
	int m_iMoveSpeed;
	int m_iCopyMarkNo;
	int m_iMarkSizeX;
	int	m_iMarkSizeY;
	int m_iMarkNo;

	bool m_bCopyFlag;

	CRect m_rMarkBox;
	CRect m_rcFixedBox;

	CLabel m_labelDisp5;
	CLabel m_labelDisp6;

	CLabel m_labelAlignResult;


	int m_iSelMotor;
	double m_fMotorJogSpeed;
	bool OLD_JogPlusflag;
	bool OLD_JogMinusflag;

	double	m_dCogX;
	double	m_dCogY;
	int		m_iBaseX;
	int		m_iBaseY;
	double	m_dOffsetX;
	double	m_dOffsetY;

	//MIL_ID	MilBinaryImage;
	//MIL_ID	MilBlobFeatureList;
	//MIL_ID	MilBlobResult;

	int	FindEpoxyPoint(int iCh);
	int	FindEpoxyPoint2(int iCh);
	int FindEpoxyPoint4(int iCh);
	int FindEpoxyPoint5(int iCh);

	int	CalcEpoxyOffset();
	void PutEpoxyDataOnEdit();

	int m_radio;
	int m_vacuumsol;

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	int m_iSelMoveType;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedButtonLivemode();
	afx_msg void OnBnClickedButtonRegist();
	afx_msg void OnBnClickedButtonFind();
	afx_msg void OnBnClickedRadioPos();
	afx_msg void OnBnClickedRadioSize();
	afx_msg void OnBnClickedButtonBoxUp();
	afx_msg void OnBnClickedButtonBoxDown();
	afx_msg void OnBnClickedButtonBoxLeft();
	afx_msg void OnBnClickedButtonBoxRight();
	afx_msg void OnBnClickedButtonBoxSpeed();
	afx_msg void OnBnClickedButtonMotorAlign();
	afx_msg void OnBnClickedButtonMotorBond();
	afx_msg void OnBnClickedButtonMarkset();
	afx_msg void OnBnClickedButtonImgLoad();
	afx_msg void OnBnClickedButtonImgSave();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonVaccumOn();
	afx_msg void OnBnClickedButtonVaccumOff();
	DECLARE_EVENTSINK_MAP()
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonMotorWait();
	afx_msg void OnBnClickedButtonMotorBond2();
	afx_msg void OnBnClickedButtonAlignTest2();
	CAutoRepeatButton m_JogPlus;
	CAutoRepeatButton m_JogMinus;
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnMenuCopy();
	afx_msg void OnMenuDelete();
	afx_msg void OnMenuPaste();
	
	CExButton m_btnVaccumOff;
	CExButton m_btnVaccumOn;	
	CExButton m_btnVaccumSol;

	CExButton m_btnResinPos;
	CExButton m_btnWaitPos;
	CExButton m_btnHolderPos;
	CExButton m_btnAlignPos;
	CExButton m_btnBondPos;
	CExButton m_btnBond2Pos;

	CExButton m_btnPDispensePos;
	CExButton m_btnPDispenseZPos;
	CExButton m_btnTDispensePos;
	CExButton m_btnTDispenseZPos;

	
	CExButton m_btnExpoxyTarget;
	CExButton m_btnSensorContact;
	CExButton m_btnRepoxy;
	CExButton m_btnLepoxy;
	CExButton m_btnZldis;
	CExButton m_btnTapos2;
	CExButton m_btnCon2;
	CExButton m_btnLbond;
	CExButton m_btnRbond;

	CExButton m_btnContiPos;
	CExButton m_btnContiPosZ;

	CExButton m_btnLaserLiftUp;
	CExButton m_btnLaserLiftDown;


	CExButton m_btnEpoxy;
	CExButton m_btnWaitZ;
	CExButton m_btnHolderZ;
	CExButton m_btnDispenseZ;
	CExButton m_btnLaserZ;

	CExButton m_btnLaserDlgOpen;
	CExButton m_btnLaserManualStart;

	CExButton m_btn_LaserIN1;
	CExButton m_btn_LaserIN2;
	CExButton m_btn_LaserIN3;
	CExButton m_btn_LaserIN4;
	CExButton m_btn_LaserOUT1;
	CExButton m_btn_LaserOUT2;
	CExButton m_btn_LaserOUT3;
	CExButton m_btn_LaserOUT4;
	CExButton m_btnAlignLaserPos;
	CExButton m_btnAlignLaserPosOut;
	CExButton m_btnSensorContect;

	CExButton m_btn_Laser_CylUp_LaserTab;
	CExButton m_btn_Laser_CylDown_LaserTab;

	BOOL m_bResinInspDIsp;

	bool func_TaskMovingCheck();

	afx_msg void OnBnClickedButtonGotoPcbalign();
	CExButton m_btnPCB;
	CExButton m_btnLens;
	CExButton m_btnLensEdge;
//	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CLabel m_LabelClean;

	CContinuousButton m_btn_BoxLeft;
	CContinuousButton m_btn_BoxUP;
	CContinuousButton m_btn_BoxRight;
	CContinuousButton m_btn_BoxDown;


	


	afx_msg void OnBnClickedButtonGotoLensedgeAlign();
	afx_msg void OnBnClickedButtonGotoLensalign();
	afx_msg void OnBnClickedButtonEpoxy();
	afx_msg void OnBnClickedButtonZMotorWait();
	afx_msg void OnBnClickedButtonZMotorDispense();
	afx_msg void OnBnClickedButtonLaserDlgOpen();
	afx_msg void OnBnClickedButtonLaserManualSerach2();
	afx_msg void OnBnClickedButtonMotorDisplaceIn1();
	afx_msg void OnBnClickedButtonMotorDisplaceIn2();
	afx_msg void OnBnClickedButtonMotorDisplaceIn3();
	afx_msg void OnBnClickedButtonMotorDisplaceIn4();
	afx_msg void OnBnClickedButtonMotorLaserOut1();
	afx_msg void OnBnClickedButtonMotorLaserOut2();
	afx_msg void OnBnClickedButtonMotorLaserOut3();
	afx_msg void OnBnClickedButtonMotorLaserOut4();
	afx_msg void OnBnClickedButtonMotorAlignLaserPos();
	afx_msg void OnBnClickedButtonMotorAlignLaserPosOut();
	afx_msg void OnBnClickedButtonSensorContact();
	afx_msg void OnBnClickedButtonEpoxyCalc();
	afx_msg void OnBnClickedButtonFindbaseEpoxy();
	afx_msg void OnBnClickedButtonFindEpoxy();
	afx_msg void OnBnClickedButtonOffsetSave();
	afx_msg void OnBnClickedButtonEpoxyInsp1();
	afx_msg void OnBnClickedButtonMotorSensorContactPos();
	afx_msg void OnBnClickedButtonMotorExpoxyTargetPos();
	afx_msg void OnStnClickedPcbAlignResult();
	afx_msg void OnStnClickedEditCleanPos();
	afx_msg void OnBnClickedButtonChoiceEpoxy();
	afx_msg void OnBnClickedButtonMotorLbond();
	afx_msg void OnBnClickedButtonMotorRbond();
	afx_msg void OnBnClickedButtonZMotorLdispense();
	afx_msg void OnBnClickedButtonLepoxy();
	afx_msg void OnBnClickedButtonRepoxy();
	afx_msg void OnBnClickedButtonMotorSensorContactPos2();
	afx_msg void OnBnClickedButtonMotorExpoxyTargetPos2();
	afx_msg void OnBnClickedRadioCircle();
	afx_msg void OnBnClickedRadioLine();
	afx_msg void RadioCtrl(UINT ID);
	afx_msg void OnBnClickedButtonEcalSave();
	afx_msg void OnBnClickedButtonLaserLiftUp();
	afx_msg void OnBnClickedButtonLaserLiftDown();
	afx_msg void OnBnClickedButtonVaccumSol();
	afx_msg void OnBnClickedButtonZMotorLaser();
	afx_msg void OnBnClickedButtonMotorResinPos();
	afx_msg void OnEnChangeEditOffsetX();
	afx_msg void OnBnClickedButtonMotorResinPos2();
	afx_msg void OnBnClickedButtonMotorExpoxyTargetZ();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButtonEpoxyRoi();
	afx_msg void OnBnClickedButtonMotorSensorContactZpos();
	CExButton m_btnSensorContactZ;
	afx_msg void OnBnClickedButtonZMotorHolder();
	afx_msg void OnBnClickedButtonMotorHolder();

	public:
		void drawRectEpoxyInsp();
		void drawCircleEpoxyInsp();
		void drawRect_Circle_EpoxyInsp();
		afx_msg void OnBnClickedButtonEpoxyRoiView();
		afx_msg void OnBnClickedButtonMotorContiEpoxy();
		afx_msg void OnBnClickedButtonZMotorContiEpoxy();
		afx_msg void OnBnClickedButtonSmallEpoxy();
		afx_msg void OnEnChangeEditOffsetY();
		afx_msg void OnBnClickedButtonMotorPdispensePos();
		afx_msg void OnBnClickedButtonZMotorPdispensePos();
		afx_msg void OnBnClickedButtonLaserCylUpLasertab();
		afx_msg void OnBnClickedButtonLaserCylDownLasertab();
		afx_msg void OnBnClickedButtonSmallCircleEpoxy();
		afx_msg void OnBnClickedButtonMotorTdispensePos();
		afx_msg void OnBnClickedButtonZMotorTdispensePos();
		CExButton m_btnInspXWaitPos;
		CExButton m_btnInspXHolderPos;
		CExButton m_btnInspXBondPos;
		CExButton m_btnInspXPDispensePos;
		CExButton m_btnInspXTDispensePos;
		afx_msg void OnBnClickedButtonInspXMotorWait();
		afx_msg void OnBnClickedButtonInspXMotorHolder();
		afx_msg void OnBnClickedButtonInspXMotorBond();
		afx_msg void OnBnClickedButtonInspXMotorPdispensePos();
		afx_msg void OnBnClickedButtonInspXMotorTdispensePos();
		afx_msg void OnBnClickedButtonEpoxyWeight();
};
