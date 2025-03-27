#pragma once


// CRS232CTestDlg 대화 상자입니다.

class CRS232CTestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRS232CTestDlg)

public:
	CRS232CTestDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRS232CTestDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_RS232C_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL Create(UINT nIDTemplate, CWnd* pParentWnd);
	void AddText(CString sInput);

public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonRs232cSend();
	afx_msg void OnBnClickedCancel();
	CComboBox m_cbCOMPort;
	afx_msg void OnClickedButtonRs232cCon();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	CComboBox m_cbCOMPort002;
	afx_msg void OnClickedButtonRs232cCon002();
	afx_msg void OnClickedButtonRs232cSend002();
};
