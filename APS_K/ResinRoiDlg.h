#pragma once

#include "afxcmn.h"
#include "afxwin.h"

#include "Label/Label.h"
#include "Library/AutoRepeat/AutoRepeatButton.h"
#include "ExButton/exbutton.h"


// CResinRoiDlg 대화 상자입니다.

class CResinRoiDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CResinRoiDlg)

public:
	CResinRoiDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CResinRoiDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_RESIN_ROI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	void	dispMotorPos();
	void	func_GridInit_ArcRoi();
	void	func_GridInit_LineRoi();
	//CMSFlexGrid m_gridArcRoi;		//원호보간 Model Data Draw
	//CMSFlexGrid m_gridLineRoi;		//원호보간 Model Data Draw

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonResinRoiSave();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	DECLARE_EVENTSINK_MAP()
	void DblClickMsflexgridArcRoi();
	void DblClickMsflexgridLineRoi();
	void displayData_ResinRoi();
	void getData_ResinRoi();
};
