#pragma once


#include "Resource.h"
#include "Label/Label.h"


// CDelayMsgDlg 대화 상자입니다.

class CDelayMsgDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDelayMsgDlg)

public:
	CDelayMsgDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDelayMsgDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_DELAY };

	int timerRunFlag;

	int			delay;
	CTime		showTime;
	CTime		curTime;
	CString		titleStr;
	COLORREF	color;
	COLORREF	bkColor;

	CLabel		m_labelDelayMsg;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
