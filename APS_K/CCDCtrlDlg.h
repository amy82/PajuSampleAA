#pragma once
#include "afxwin.h"


// CCCDCtrlDlg 대화 상자입니다.

class CCCDCtrlDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCCDCtrlDlg)

public:
	CCCDCtrlDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCCDCtrlDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_CCD_CTRL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonClose2();
	afx_msg void OnBnClickedButtonInit();
	afx_msg void OnBnClickedButtonLive();
	afx_msg void OnBnClickedButtonSnap();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg void OnBnClickedButtonOpenMiu();
	afx_msg void OnBnClickedButtonInitMiu();
	afx_msg void OnBnClickedButtonVcmReady();
	afx_msg void OnBnClickedButtonCodeWrite();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCurMeasure();
	afx_msg void OnBnClickedStopLive();
	afx_msg void OnBnClickedSensorWrite();
	afx_msg void OnBnClickedSensorRead();
	afx_msg void OnBnClickedBtnTest();
	
	afx_msg void OnBnClickedCheckGpio15();
	afx_msg void OnBnClickedCheckGpio13();
	afx_msg void OnBnClickedCheckGpio19();
	afx_msg void OnBnClickedCheckGpio21();
	afx_msg void OnBnClickedCheckGpio25();
	afx_msg void OnBnClickedCheckGpio27();
	afx_msg void OnBnClickedButtonGetGpio31();
	afx_msg void OnBnClickedButtonGetGpio33();
	afx_msg void OnBnClickedButtonUartSend();
	afx_msg void OnBnClickedButtonUartRxGet();
	CButton m_cGpio27Status;
	CButton m_cGpio13Status;
	CButton m_cGpio15Status;
	CButton m_cGpio19Status;
	CButton m_cGpio21Status;
	CButton m_cGpio25Status;
};
