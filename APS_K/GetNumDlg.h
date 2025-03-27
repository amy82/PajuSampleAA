#pragma once
#include "afxwin.h"

#include "Label/Label.h"

// CGetNumDlg 대화 상자입니다.

class CGetNumDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGetNumDlg)

public:
	virtual ~CGetNumDlg();

	CString	m_strTitle;
	CString GetstrNum();

	CGetNumDlg(int maxchar=10, char* getnum="0.0", CWnd* pParent = NULL);

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_NUM };


private:
	CLabel	m_labelModifyData;

	int		m_intMaxChar;
	int		m_nPointNum;
	BOOL	m_FirstFlag;
	CString	m_strGetNum;

	BOOL VerifyMaxChar();
	void InitStaticDispWnd();

	void UpdateDisplay();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButtonDot();
	afx_msg void OnBnClickedButtonSign();
	afx_msg void OnBnClickedButtonBack();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonEsc();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonPls();
};
