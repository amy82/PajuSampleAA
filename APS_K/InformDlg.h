#pragma once


#include "Resource.h"
#include "Label/Label.h"

// CInformDlg 대화 상자입니다.

class CInformDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInformDlg)

public:
	CInformDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CInformDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_INFORM };

	CString		titleStr;
	CString		m_sMsg;
	COLORREF	color;
	COLORREF	bkColor;

	CLabel		m_labelInformMsg;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonClose();
	virtual BOOL OnInitDialog();
};
