#pragma once


// CCcdDlg 대화 상자입니다.

#include "ExButton/exbutton.h"

//! 현재 선택된 자식 Dialog를 나타낸다. 
#define	CCD_VIEW_DEFECT		0
#define CCD_VIEW_OSCHECK	1
#define CCD_VIEW_SFR		2
#define CCD_VIEW_INSP_MODE	3

//class CCCDOSChkDlg;
class CCCDSFRDlg;
class CCCDInspModeDlg;


class CCcdDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCcdDlg)

public:
	CCcdDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCcdDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_CCD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:


	//! 버튼 폰트
	CFont m_ftNormal;
	CFont m_ftSelected;
	bool CreateFont_Child_Dlg_Btn();

	int     m_iMode_View;	//! 현재 선택된 자식 Dialog를 나타내는 숫자 (CCD_VIEW_BOARD ~ CCD_VIEW_TEST)

	int     Make_Child_Dialog();
	void    Delete_Child_Dialog();

	void	setInterface();
	void    setInterface_Child_Dialog();

	
	bool    SetVisible_Child_Dialog(int iMode_View, bool bFlag_Visible);

public:
	void    Hide_All_Child_Dialog();	
	void    SetView_Child_Dialog(int iMode_View);

	//CCCDOSChkDlg *m_pOSChkDlg;
	CCCDSFRDlg	 *m_pSFRDlg;
	CCCDInspModeDlg *m_pInspModeDlg;


public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDestroy();

	CExButton m_btnOSChk;
	CExButton m_btnSFR;
	CExButton m_btnDefect;
	CExButton m_btnInspMode;

	afx_msg void OnBnClickedButtonCcdOscheck();
	afx_msg void OnBnClickedButtonCcdSfr();
	afx_msg void OnBnClickedButtonCcdDefect();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	void SetAlignData_Tilt(double dx, double dy);
	void SetAlignData_Shift(double dx, double dy);
	void DisplayFrameRate(int iFrameRate);
	afx_msg void OnBnClickedButtonMandoInsp();
};
