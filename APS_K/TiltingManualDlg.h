#pragma once
#include "Label/Label.h"
#include "ExButton/exbutton.h"
// CTiltingManualDlg 대화 상자입니다.

class CTiltingManualDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTiltingManualDlg)

public:
	CTiltingManualDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTiltingManualDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_MANUAL_TILTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CExButton m_btnOk;
	CExButton m_btnStop;
	
	CLabel	edit_TiltingTX;
	CLabel	edit_TiltingTY;

	virtual BOOL OnInitDialog();
	afx_msg void OnStnClickedEditTiltingX();
	afx_msg void OnStnClickedEditTiltingY();
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonStop();
};
