#pragma once


#include "Library/AutoRepeat/AutoRepeatButton.h"
#include "afxwin.h"
#include "ContinuousButton.h"
#include "ExButton/exbutton.h"
#include "Label/Label.h"

// CLensEdgeDlg 대화 상자입니다.

class CLensEdgeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLensEdgeDlg)

public:
	CLensEdgeDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CLensEdgeDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_LENS_EDGE };

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


	int		pushErrCnt, coverErrCnt, vaccumErrCnt;

	void	changeColorVaccumBtn();			/* Vaccum 버튼 색상 바꾸기 */
	void	changeColorMotorPosBtn();		/* 모터 위치 별 색상 바꾸기 */
	void	changeColorGripBtn();			// Grip 버튼 별 색상 바꾸기
	void	changeColorUVBtn();			// Grip 버튼 별 색상 바꾸기
	void	changeColorTailGripBtn();
	void	changeColorLaserCylinderLensTabBtn();//Laser 실린더 Btn
	bool	checkCurMotorPos(int iPos);		/* 모터 위치 확인 */
	bool	checkCurMotorPCBPos(int iPos);	//PCB Unit Align 위치 확인
	bool checkCurMotorPCBPosZ(int iPos);
	bool	checkCurMotorPosZ(int iPos);	//Z축 모터 위치 확인
	void	DigLedputData();

	bool	checkCurInspXMotorPos(int iPos); /*INSP X 모터 위치 확인*/

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
	afx_msg void OnBnClickedButtonMotorSupply();
	afx_msg void OnBnClickedButtonMotorAlign();
	afx_msg void OnBnClickedButtonMotorGiveUp();
	afx_msg void OnBnClickedButtonMarkset();
	afx_msg void OnBnClickedButtonImgLoad();
	afx_msg void OnBnClickedButtonImgSave();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonVaccumOn();
	afx_msg void OnBnClickedButtonVaccumOff();
	DECLARE_EVENTSINK_MAP()
	void DblClickMsflexgridMark();
	void DblClickMsflexgridMotor();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonMotorWait();
	afx_msg void OnBnClickedButtonAlignTest2();
	CAutoRepeatButton m_JogPlus;
	CAutoRepeatButton m_JogMinus;
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnMenuCopy();
	afx_msg void OnMenuDelete();
	afx_msg void OnMenuPaste();
	CExButton m_btnLaserCamFor;
	CExButton m_btnLaserCamBack;


	CExButton m_btnCoverOn;
	CExButton m_btnCoverOff;
	CExButton m_btnPushOff;
	CExButton m_btnPushOn;
	CExButton m_btnVaccumOff;
	CExButton m_btnVaccumOn;	

	CExButton m_btnWaitPos;
	CExButton m_btnSupplyPos;
	CExButton m_btnAlignPos;
	CExButton m_btnGiveUpPos;

	CExButton m_btnPcbLoadPos;
	CExButton m_btnPcbLoadZPos;
	CExButton m_btnCoverLoadPos;
	CExButton m_btnCoverLoadZPos;
	CExButton m_btnCoverUnLoadPos;
	CExButton m_btnCoverUnLoadZPos;

	CExButton m_btnAlignZPos;
	CExButton m_btn_ZWaitePos;
	CExButton m_btn_ZLoading;
	CExButton m_btn_ZBonding;
	CExButton m_btn_UVOn;
	CExButton m_btn_UVOff;
	CExButton m_btn_PcbUVOn;
	CExButton m_btn_PcbUVOff;
	
	CExButton m_btn_Laser_CylUp_LensTab;
	CExButton m_btn_Laser_CylDown_LensTab;

	CExButton m_btn_ContiDelay;
	CExButton m_btn_ZContiDelay;

	CExButton m_btnPcbAlignPos;
	CExButton m_btnPcbAlignZPos;
	
	afx_msg void OnBnClickedButtonPcbCoverOn();
	afx_msg void OnBnClickedButtonPcbCoverOff();
	afx_msg void OnBnClickedButtonGotoPcbalign();
	CExButton m_btnPCB;
	CExButton m_btnLens;
	CExButton m_btnLoadingAlign;
	CExButton m_btnLoading;
	CExButton m_btnLensEdge;

	CLabel	m_Conti_Down_Offset;
//	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	CContinuousButton m_btn_BoxLeft;
	CContinuousButton m_btn_BoxUP;
	CContinuousButton m_btn_BoxRight;
	CContinuousButton m_btn_BoxDown;
	afx_msg void OnBnClickedButtonGotoLensalign();
	afx_msg void OnBnClickedButtonEdgeGotoLensalign();
	afx_msg void OnBnClickedButtonZMotorUp2();
	afx_msg void OnBnClickedButtonZMotorDown();
	afx_msg void OnBnClickedButtonZMotorDownBonding();
	afx_msg void OnBnClickedButtonEdgeMotorLoadingAlign();
	afx_msg void OnBnClickedButtonEdgeEpoxyUvOn();
	afx_msg void OnBnClickedButtonEdgeEpoxyUvOff();
	afx_msg void OnBnClickedButtonEdgeMotorLoading();

	bool checkInterlockLoadingZ();
	bool func_TaskMovingCheck();
	bool func_MovingInterlock();
	afx_msg void OnBnClickedButtonZMotorAlign();
	afx_msg void OnBnClickedBtnCamLaserFor();
	afx_msg void OnBnClickedBtnCamLaserBack();
	afx_msg void OnBnClickedButtonEdgeMotorPcbalign();
	afx_msg void OnBnClickedButtonZMotorPcbalign();
	afx_msg void OnBnClickedButtonZMotorContiPos();
	afx_msg void OnStnClickedStcContiDownOffset();
	afx_msg void OnBnClickedButtonMotorContiPos();
	afx_msg void OnBnClickedButtonLensLaserPos1();
	afx_msg void OnBnClickedButtonLaserAutoInsp();
	afx_msg void OnBnClickedButtonLensLaserPos2();
	afx_msg void OnBnClickedButtonLensLaserPos3();
	afx_msg void OnBnClickedButtonLensLaserPos4();
	afx_msg void OnBnClickedButtonLaserManualInsp();
	afx_msg void OnBnClickedButtonSminiUvOn();
	afx_msg void OnBnClickedButtonSminiUvOff();
	afx_msg void OnBnClickedButtonEdgeMotorPcbload();
	afx_msg void OnBnClickedButtonEdgeZMotorPcbload();
	afx_msg void OnBnClickedButtonEdgeMotorCoverload();
	afx_msg void OnBnClickedButtonEdgeZMotorCoverload();
	afx_msg void OnBnClickedButtonEdgeMotorCoverunload();
	afx_msg void OnBnClickedButtonEdgeZMotorCoverunload();
	afx_msg void OnBnClickedButtonLaserCylUpLenstab();
	afx_msg void OnBnClickedButtonLaserCylDownLenstab();
	CExButton m_btnInspXAlignPos;
	afx_msg void OnBnClickedButtonEdgeInspXMotorAlign();
	CExButton m_btnInspXWaitPos;
	afx_msg void OnBnClickedButtonEdgeInspXMotorWait();
	afx_msg void OnBnClickedButtonLensHoleAlign();
};
