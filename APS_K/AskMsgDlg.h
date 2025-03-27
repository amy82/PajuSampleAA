#pragma once

#include "Label/Label.h"

// CAskMsgDlg 대화 상자입니다.

class CAskMsgDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAskMsgDlg)

public:
	CAskMsgDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAskMsgDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_ASK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	CString		m_sMsg;
	CLabel		m_labelMsg;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonYes();
	afx_msg void OnBnClickedButtonNo();
};
