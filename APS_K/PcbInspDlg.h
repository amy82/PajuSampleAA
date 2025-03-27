#pragma once
#include "Library/AutoRepeat/AutoRepeatButton.h"
#include "afxwin.h"
#include "ContinuousButton.h"


// CPcbInspDlg 대화 상자입니다.

class CPcbInspDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPcbInspDlg)

public:
	CPcbInspDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPcbInspDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_PCB_INSP };

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


	bool	checkCurMotorPos(int iPos);		/* 모터 위치 확인 */
	bool	checkCurMotorPosZ(int iPos);	/* 모터 위치 확인 */
	void	DigLedputData();
	

	//CMSFlexGrid	m_gridMark;
	//CMSFlexGrid	m_gridMotor;

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
	afx_msg void OnBnClickedButtonMotorAlign();
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
	
	CExButton m_btnVaccumOff;
	CExButton m_btnVaccumOn;	

	CExButton m_btnWaitPos;
	CExButton m_btnAlignPos;


	CExButton m_btnLaserDlgOpen;
	CExButton m_btnLaserManualStart;

	CExButton m_btn_LaserOUT1;
	CExButton m_btn_LaserOUT2;
	CExButton m_btn_LaserOUT3;
	CExButton m_btn_LaserOUT4;
	CExButton m_btnAlignLaserPosOut;

	CExButton m_btnPushFor;
	CExButton m_btnPushBack;
	CExButton m_btnDarkUp;
	CExButton m_btnDarkDown;

	CExButton m_btnDarkPos;
	CExButton m_btnDefectPos;
	CExButton m_btnBondPos;
	CExButton m_btnBondAlignPos;

	bool func_TaskMovingCheck();
	bool func_MovingInterlock();

	void	changeColorPushBtn();			/* PCB Cover 전/후진 버튼 색상 바꾸기 */
	void	changeColorDarkBtn();			/* Dark 실린더 버튼 색상 바꾸기 */

	CSliderCtrl m_sliderBright;
	CSliderCtrl m_sliderContrast;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnClickedEditBright();
	afx_msg void OnClickedEditContrast();
	CLabel m_LabelBright;
	CLabel m_LabelContrast;

	CContinuousButton m_btn_BoxLeft;
	CContinuousButton m_btn_BoxUP;
	CContinuousButton m_btn_BoxRight;
	CContinuousButton m_btn_BoxDown;
	afx_msg void OnBnClickedButtonLaserDlgOpen();
	afx_msg void OnBnClickedButtonLaserManualSerach2();
	afx_msg void OnBnClickedButtonMotorLaserOut1();
	afx_msg void OnBnClickedButtonMotorLaserOut2();
	afx_msg void OnBnClickedButtonMotorLaserOut3();
	afx_msg void OnBnClickedButtonMotorLaserOut4();
	afx_msg void OnBnClickedButtonMotorAlignLaserPosOut();
	afx_msg void OnBnClickedButtonPcbCoverFor();
	afx_msg void OnBnClickedButtonPcbCoverBack();
	afx_msg void OnBnClickedButtonPcbDarkUp();
	afx_msg void OnBnClickedButtonPcbDarkDown();
	afx_msg void OnBnClickedButtonMotorDarkInsp();
	afx_msg void OnBnClickedButtonMotorDefectInsp();
	afx_msg void OnBnClickedButtonMotorBond();
	afx_msg void OnBnClickedButtonMotorBond2();
	afx_msg void OnBnClickedButtonSocketTest();
};
