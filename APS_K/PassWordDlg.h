#pragma once


#include "Label/Label.h"
// CPassWordDlg 대화 상자입니다.

class CPassWordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPassWordDlg)

public:
	CPassWordDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPassWordDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_PASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	CLabel	m_labelPassWord;

	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();

	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};
