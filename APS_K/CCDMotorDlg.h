#pragma once


#include "msflexgrid.h"
#include "Label/Label.h"
#include "Library/AutoRepeat/AutoRepeatButton.h"


// CCCDMotorDlg 대화 상자입니다.

class CCCDMotorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCCDMotorDlg)

public:
	CCCDMotorDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCCDMotorDlg();

	void	setInterface();
	void	initMotorGrid();
	void	dispMotorStatus();
	void	dispData();

	void	changeMotorNo(int motorNo);
	void	CheckJogMotorSpeed();

	CMSFlexGrid	m_gridMotor;

	CLabel	m_labelMotorName;

	int m_iSelMotor;
	bool timerRunFlag;
	double m_fMotorJogSpeed;
	bool OLD_JogPlusflag;
	bool OLD_JogMinusflag;

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_CCD_MOTOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedButtonMotorSave();
	DECLARE_EVENTSINK_MAP()
	void DblClickMsflexgridMotor();
	afx_msg void OnBnClickedButtonMotorWait();
	afx_msg void OnBnClickedButtonMotorSupply();
	afx_msg void OnBnClickedButtonMotorAlign();
	afx_msg void OnBnClickedButtonMotorBond();
	afx_msg void OnBnClickedButtonMotorBond2();
	afx_msg void OnBnClickedButtonMotorSpeed();
	CAutoRepeatButton m_JogPlus;
	CAutoRepeatButton m_JogMinus;
	afx_msg void OnBnClickedButtonPlusX();
	afx_msg void OnBnClickedButtonMinusX();
};
