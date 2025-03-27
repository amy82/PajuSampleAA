#pragma once

#include "msflexgrid.h"
#include "Label/Label.h"
#include "Library/AutoRepeat/AutoRepeatButton.h"

// CResinDlg 대화 상자입니다.

class CResinDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CResinDlg)

public:
	CResinDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CResinDlg();

	int m_iImageIndex;

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_RESIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	bool	timerRunFlag;

	void	setInterface();
	void	dispAreaPos();
	void	dispData();
	void	ctrlLiveButton();
	void	initResinGrid();
	void	initMotorGrid();
	void	changeMotorNo(int motorNo);
	void	dispMotorStatus();
	void	CheckJogMotorSpeed();

	void	changeColorDischargeBtn();			/* 토출 버튼 색상 바꾸기 */
	int		checkSyringeMotorPos(int iIndex);	/* Syring 모터 위치 확인 */
	void	changeColorSyringeBtn();			/* Syring 버튼 색상 바꾸기 */
	void	changeColorMotorPosBtn();			/* 모터 위치 확인 */
	bool	checkCurMotorPos(int iPos);			/* 모터 위치 확인 */
	void	checkResinpara();

	int		dischargeEpoxy();				/* Epoxy 점 찍기 */
	int		findEpoxyPoint();				/* Epoxy 위치 찾기 */
	int		calcOffset_Epoxy();				/* Epoxy 도포 위치 offset 계산 */
	void	putEpoxyCalcData();				/* Epoxy 위치 계산용 기준위치와 offset 거리 넣기 */
	void	getEpoxyCalcData();				/* Epoxy 위치 계산용 기준위치와 offset 거리 얻기 */
	void    showEpoxyCalcControl();			/* Epoxy 위치 계산용 컨트롤러들 보이기/숨기기 */
	void	drawArea_EpoxyCalc();			/* Epoxy 위치 계산 시 찾을 영역 그리기 */

	int		m_iBase_X;
	int		m_iBase_Y;
	double	m_dOffset_X;
	double	m_dOffset_Y;
	CRect	m_rcArea_EpoxyCalc;

	MIL_ID  MilOriginImage;
	MIL_ID	MilOriginImageChild[3];
	MIL_ID	MilBinaryImage;
	MIL_ID  MilBinaryImageChild[3];
	MIL_ID	MilBlobResult;
	MIL_ID	MilBlobFeatureList;

	long	m_iTotalBlobs;

	double	m_dCogX;
	double	m_dCogY;

	bool	m_bSelArea[4];

	CRect	m_rArea[4];
	CRect	m_rcFixedBox;

	CLabel	m_labelMotorName;

	int		m_iSelMotor;
	int		m_iMoveSpeed;

	CMSFlexGrid	m_gridMotor;
	CMSFlexGrid m_gridResin;
	double  m_fMotorJogSpeed;
	bool OLD_JogPlusflag;
	bool OLD_JogMinusflag;

	int DrowBox;

public:
	int m_iCamNo;
	BOOL m_bCalc_Epoxy_Pos;
	int m_iSelType_EpoxyCalc;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	CSliderCtrl m_sliderLed;
	afx_msg void OnBnClickedButtonParaSave();
	afx_msg void OnBnClickedButtonBoxUp();
	afx_msg void OnBnClickedButtonBoxDown();
	afx_msg void OnBnClickedButtonBoxLeft();
	afx_msg void OnBnClickedButtonBoxRight();
	afx_msg void OnBnClickedButtonBoxSpeed();
	afx_msg void OnBnClickedRadioPos();
	afx_msg void OnBnClickedRadioSize();
	int m_iSelArea;
	afx_msg void OnBnClickedRadioSelarea1();
	afx_msg void OnBnClickedRadioSelarea2();
	afx_msg void OnBnClickedRadioSelarea3();
	afx_msg void OnBnClickedRadioSelarea4();
	int m_iSelMoveType;
	afx_msg void OnBnClickedButtonLivemode();
	afx_msg void OnBnClickedButtonImgLoad();
	afx_msg void OnBnClickedButtonImgSave();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedButtonMotorSave();
	DECLARE_EVENTSINK_MAP()
	void DblClickMsflexgridMotor();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonResinInsp();
	afx_msg void OnBnClickedButtonMotorAlign();
	afx_msg void OnBnClickedButtonMotorEmission();
	afx_msg void OnBnClickedButtonMotorSpeed();
	afx_msg void OnBnClickedButtonSyringeOn();
	afx_msg void OnBnClickedButtonSyringeOff();
	afx_msg void OnBnClickedButtonDischargeOn();
	afx_msg void OnBnClickedButtonDischargeOff();
	afx_msg void OnBnClickedButtonPlusX();
	afx_msg void OnBnClickedButtonMinusX();
	afx_msg void OnBnClickedButtonResinDraw();
	void DblClickMsflexgridResin();
	CAutoRepeatButton m_JogMinus;
	CAutoRepeatButton m_JogPlus;
	CExButton m_btnAlignPos;
	CExButton m_btnEmissionPos;
	CExButton m_btnInspPos;
	CExButton m_btnSyringeOff;
	CExButton m_btnSyringeOn;
	CExButton m_btnDischargeOff;
	CExButton m_btnDischargeOn;
	CExButton m_btnEpoxyCalPos;
	CExButton m_btnEpoxyCalInspPos;
	afx_msg void OnBnClickedRadioPcbAlign();
	afx_msg void OnBnClickedRadioEpoxy();
//	int m_bResinPara;
	BOOL m_bResinPara;
	afx_msg void OnBnClickedCheckResinDraw();
//	CExButton m_btnResinInsptect;
	afx_msg void OnBnClickedButtonResinInspect();
	afx_msg void OnBnClickedButtonEpoxyCal();
	afx_msg void OnBnClickedButtonEpoxyCalInsp();
	afx_msg void OnBnClickedCheckResinInspDisp();
	afx_msg void OnBnClickedButtonEpoxyCalc2();
	afx_msg void OnBnClickedCheckEpoxyCalc();
	BOOL m_bResinInspDIsp;
	afx_msg void OnBnClickedRadioSelTypeEpoxyCalc();
	afx_msg void OnBnClickedRadioSelTypeEpoxyCalc2();
	afx_msg void OnBnClickedButtonFindEpoxyPoint();
};
