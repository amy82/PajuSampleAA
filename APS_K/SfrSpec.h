#pragma once

#include "Label/Label.h"
#include "Utility\GridCtrl\GridCtrl.h"
#include "afxwin.h"

// CSfrSpec 대화 상자입니다.

class CSfrSpec : public CDialogEx
{
	DECLARE_DYNAMIC(CSfrSpec)

public:
	CSfrSpec(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSfrSpec();

	CLabel		m_LabelTitle;
	CLabel		m_Limit_04F_Balance;
	CLabel		m_Limit_07F_Balance;
	CLabel		m_Limit_OC;
	CLabel		m_Limit_OC_TH;
	CLabel		m_Limit_Max_Limit;
	
	void	setInterface();
	void	getData();
	void	dispData();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_SFR_SPEC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnBnClickedButtonMotorSave();
	DECLARE_EVENTSINK_MAP()
	void DblClickMsflexgridSfrSpec();
	afx_msg void OnStnClickedLimitCornorBalance();
	afx_msg void OnStnClickedLimitOcAlign();
	afx_msg void OnStnClickedLimitOcAlignTh();
	void DblClickMsflexgridSfrSpec2();

	int m_iSpecDisp;
	afx_msg void OnStnClickedLimit04fBalance();
	afx_msg void OnStnClickedLimit07fBalance();

public:
	//Grid
	CGridCtrl m_clGridSfrSpec;
	CGridCtrl m_clGridOcSpec;
	void	InitGridCtrl_Oc();
	void	InitGridCtrl_Sfr();
	void	ShowGridCtrl_Sfr();

	int sfrSpecRow;
	int sfrSpecCol;
	int ocRow;
	int ocCol;
	//
	afx_msg void OnClickedGridSfr(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickedGridOc(NMHDR* pNMHDR, LRESULT* pResult);
	
	//----------------------------------------------------------------------------------------------------
	afx_msg void OnStnClickedLimitMaxLimit();
};
