#pragma once

#include "Label/Label.h"
#include "Utility\GridCtrl\GridCellCombo.h"
#include "Utility\GridCtrl\GridCellCheck.h"
#include "Utility\GridCtrl\GridCtrl.h"
#include "afxwin.h"

// CChartSetDlg 대화 상자입니다.

class CChartSetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChartSetDlg)

public:
	CChartSetDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CChartSetDlg();


	CLabel		m_LabelTitle;

	CLabel		m_Limit_04F_Balance;
	CLabel		m_Limit_07F_Balance;
	CLabel		m_Limit_OC;
	CLabel		m_Limit_OC_TH;
	CLabel		m_Limit_Max_Limit;
	
	void	setInterface();
	
	void	dispData();

	

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_CHART_SET };

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

	afx_msg void OnStnClickedLimitOcAlign();
	afx_msg void OnStnClickedLimitOcAlignTh();


	afx_msg void OnStnClickedLimit04fBalance();
	afx_msg void OnStnClickedLimit07fBalance();

public:
	//Grid
	int m_iSpecDisp;
	int mGridFixRow;
	CGridCtrl m_clGridChartSetSpec;
	CGridCtrl m_clGridChartAARoi;

	CComboBox m_ComboChartCount;
	CComboBox m_ComboChartType;
	CComboBox m_ComboChartFind;
	CComboBox m_ComboDemosaic;
	
	void InitGridCtrl_ChartSet();
	void ShowGridCtrl_ChartSet(int nMode = 0);//0 = show , 1 = 추가 ,2 = 삭제
	void GetGridCtrl_ChartSet();
	void FnTiltCal();
	//
	void InitGridCtrl_AARoiSet();
	void RoiGridReset(int nRow, int index);
	int sfrRow;
	int sfrCol;

	int roiRow;
	int roiCol;

	int mLocalChartCount;
	//
	afx_msg void OnClickedGridSfr(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickedGridRoi(NMHDR* pNMHDR, LRESULT* pResult);
	

};
