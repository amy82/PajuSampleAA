#pragma once

#include "ExButton/exbutton.h"
#include "MSFlexGrid.h"

// CMotorHomDlg 대화 상자입니다.

class CMotorHomDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMotorHomDlg)

public:

	bool	timerRunFlag;

	CMotorHomDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMotorHomDlg();


	CMSFlexGrid	m_gridMotor;

	void setInterface();
	void dispMotorStatus();


	// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_MOTOR_HOME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonServoOnAll();
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonServoOffAll();
	afx_msg void OnBnClickedButtonHome();
	afx_msg void OnBnClickedButtonHomeStop();
	afx_msg void OnBnClickedButtonReset();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonMotor0();
	afx_msg void OnBnClickedButtonMotionInit();
};
