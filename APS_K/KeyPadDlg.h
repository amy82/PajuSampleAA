#pragma once
#include "afxwin.h"

#include "Label/Label.h"

// CKeyPadDlg 대화 상자입니다.

class CKeyPadDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CKeyPadDlg)

public:
	virtual ~CKeyPadDlg();

	CString		m_strKeyPad;
	CString		GetstrKeypad();
	BOOL	m_FirstFlag;
	CKeyPadDlg(int maxchar=20, char* getkeypad="", CWnd* pParent = NULL);

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_KEYPAD };

private:
	CLabel	m_labelModifyData;

	int		m_intMaxChar;
	int		m_nPointKeyPad;
	

	BOOL VerifyMaxChar();
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
	afx_msg void OnBnClickedButtonA();
	afx_msg void OnBnClickedButtonB();
	afx_msg void OnBnClickedButtonC();
	afx_msg void OnBnClickedButtonD();
	afx_msg void OnBnClickedButtonE();
	afx_msg void OnBnClickedButtonF();
	afx_msg void OnBnClickedButtonG();
	afx_msg void OnBnClickedButtonH();
	afx_msg void OnBnClickedButtonI();
	afx_msg void OnBnClickedButtonJ();
	afx_msg void OnBnClickedButtonK();
	afx_msg void OnBnClickedButtonL();
	afx_msg void OnBnClickedButtonN();
	afx_msg void OnBnClickedButtonM();
	afx_msg void OnBnClickedButtonO();
	afx_msg void OnBnClickedButtonP();
	afx_msg void OnBnClickedButtonQ();
	afx_msg void OnBnClickedButtonR();
	afx_msg void OnBnClickedButtonS();
	afx_msg void OnBnClickedButtonT();
	afx_msg void OnBnClickedButtonU();
	afx_msg void OnBnClickedButtonV();
	afx_msg void OnBnClickedButtonW();
	afx_msg void OnBnClickedButtonX();
	afx_msg void OnBnClickedButtonY();
	afx_msg void OnBnClickedButtonZ();
	afx_msg void OnBnClickedButtonBack();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonEsc();
	//
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonComma();
	afx_msg void OnBnClickedButtonUnderBar();
};
