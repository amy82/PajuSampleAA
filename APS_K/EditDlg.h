#pragma once


// CEditDlg 대화 상자입니다.

class CEditDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEditDlg)

public:
	CEditDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CEditDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	CString getTextOnEdit();

	CString m_strText;
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
