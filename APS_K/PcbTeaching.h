#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#include "Label/Label.h"
#include "Library/AutoRepeat/AutoRepeatButton.h"
#include "ExButton/exbutton.h"
#include "Utility\GridCtrl\GridCtrl.h"

// CMotorDlg2 대화 상자입니다.
//class CLightDlg;
class CMotorDlg2 : public CDialogEx
{
	DECLARE_DYNAMIC(CMotorDlg2)

public:
	CMotorDlg2(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMotorDlg2();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_PCB_TEACHING};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	bool	timerRunFlag;

	void	setInterface();
	void	dispMotorStatus();	

	void	changeMotorNo(int motorNo);
	void	changeCamera();
	void	changeCalcMode();
	void	dispResolDataOnGrid();
	void	getResolDataOnGrid();

	void	drawResolBackGround();
	void	getMarkAndMotor(int iPos);
	void	MotorVelSoftlimitView();

	bool	registPatMark(int iCamNo, CRect rcBox);

	void	CheckVelLimit();
	void	MotorVellimitView();
	void	changeColorMotorPosBtn(int SelPos);



	int m_iSelCam;
	int m_iSelMotor;
	int m_iMarkSizeX;
	int m_iMarkSizeY;

	int testCount;
	double m_fMotorJogSpeed;
	bool OLD_JogPlusflag;
	bool OLD_JogMinusflag;

	bool m_bFindTop;
	bool m_bFindBottom;
	bool m_bFindLeft;
	bool m_bFindRight;
	int m_iVel_Limit;		//0:속도, 1: Align 리미트

	CDPoint m_dFindCenter[4];
	CDPoint m_dMotorPos[4];
	CDPoint m_dTempResol;
	CDPoint m_dTempAngle;

	BOOL m_bCalcResol;


public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedRadioLens();
	afx_msg void OnBnClickedRadioPcb();
	afx_msg void OnBnClickedRadioCcd();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonMotorPosSave();
	afx_msg void OnBnClickedButtonAlarmReset();
	DECLARE_EVENTSINK_MAP()
	afx_msg void OnBnClickedButtonJogPlus();
	afx_msg void OnBnClickedButtonJogMinus();
	afx_msg void OnBnClickedButtonOriginAll();
	afx_msg void OnBnClickedButtonServoOnAll();
	afx_msg void OnBnClickedButtonServoOffAll();
	afx_msg void OnBnClickedButtonAlarmResetAll();
	afx_msg void OnBnClickedButtonStopAll();
	afx_msg void OnBnClickedButtonMotorOrigin();
	afx_msg void OnBnClickedButtonServoOn();
	afx_msg void OnBnClickedButtonSerboOff();
	afx_msg void OnBnClickedRadioMotorSpeed1();
	afx_msg void OnBnClickedRadioMotorSpeed2();
	afx_msg void OnBnClickedRadioMotorSpeed3();
	afx_msg void OnBnClickedCheckResolution();
	CAutoRepeatButton m_JogPlus;
	CAutoRepeatButton m_JogMinus;
	afx_msg void OnBnClickedButtonResolution();
	afx_msg void OnBnClickedButtonJogStop();
	afx_msg void OnBnClickedButtonMotorVelSoftlimit();
	int m_iMotorSpeed;
	afx_msg void OnBnClickedButtonTest2();
	afx_msg void OnBnClickedButtonTest();

	afx_msg void OnBnClickedButtonGotoLensmotor();
	CExButton m_btnMot1;
	CExButton m_btnMot2;
	CExButton m_btnMot3;
	CLabel m_LabelMotorSpeed;
	afx_msg void OnStnClickedStaticMotorspeed();

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonGotoDispencemotor();
	afx_msg void OnBnClickedButtonGotoPcbmotor();

public:
	//Grid
	CGridCtrl m_clGridTeachingPcb;
	CGridCtrl m_clGridResolPcb;
	void	InitGridCtrl_Pcb();
	void	ShowGridCtrl_Pcb();
	void	InitGridCtrl_Resol();
	void	ShowGridCtrl_Resol();
	
	int pcbRow;
	int pcbCol;
	int resolRow;
	int resolCol;
	
	//
	afx_msg void OnDBClickedGridPcb(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDBClickedGridResol(NMHDR* pNMHDR, LRESULT* pResult);
	
	afx_msg void OnBnClickedButtonGotoLenslaseralignmotor();
	CExButton m_btnMot4;
};
