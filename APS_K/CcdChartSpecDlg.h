#pragma once

#include "afxwin.h"
#include "Utility\GridCtrl\GridCtrl.h"
#include "Utility\ButtonEx\ButtonEx.h"
#include "Label\Label.h"
// CCcdChartSpecDlg 대화 상자입니다.

class CCcdChartSpecDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCcdChartSpecDlg)

public:
    CCcdChartSpecDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCcdChartSpecDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_CCD_CHART_SPEC};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	void SetUnit(int nUnit);
	const int ChartMaxCount = 6;
private:
	void InitCtrl();
	void InitChartGridCtrl();

	void ShowChartSpec();
	void GetChartSpec();
private:
	CGridCtrl m_clGridChartSpec;

	CFont m_clFontSmall;
	CFont m_clFontMid;
	CFont m_clFontBig;

	int m_nUnit;

public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	
	afx_msg void OnNMDblClickedChartSpec(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnBnClickedButtonCcdChartSpecSave();
    afx_msg void OnBnClickedButtonCcdChartSpecClose();

    //
	afx_msg void OnStnClickedStaticCcdSfrSpecCenterSfrLimitVal();
	afx_msg void OnStnClickedStaticCcdSfrSpecCornerSfrLimitVal();
	afx_msg void OnStnClickedStaticCcdSfrSpecCornerSfrDeviationLimitVal();
	afx_msg void OnStnClickedStaticCcdSfrSpecOcXyVal();
	afx_msg void OnStnClickedStaticCcdSfrSpecOcThVal();
    
	
	
public:
	CLabel m_clColorStaticTopBar;
    CLabel m_clColorStaticCenterSfrLimit;
    CLabel m_clColorStaticCenterSfrLimitVal;
    CLabel m_clColorStaticCornerSfrLimit;
    CLabel m_clColorStaticCornerSfrLimitVal;
    CLabel m_clColorStaticCornerSfrDeviationLimit;
    CLabel m_clColorStaticCornerSfrDeviationLimitVal;
    CLabel m_clColorStaticOCXY;
    CLabel m_clColorStaticOCXYVal;
    CLabel m_clColorStaticOCTh;
    CLabel m_clColorStaticOCThVal;


    CLabel m_clColorStaticHfovMin;
    CLabel m_clColorStaticHfovMax;
    CLabel m_clColorStaticVfovMin;
    CLabel m_clColorStaticVfovMax;
    CLabel m_clColorStaticDistortionMin;
    CLabel m_clColorStaticDistortionMax;

    CLabel m_clColorStaticHfovMinVal;
    CLabel m_clColorStaticHfovMaxVal;
    CLabel m_clColorStaticVfovMinVal;
    CLabel m_clColorStaticVfovMaxVal;
    CLabel m_clColorStaticDistortionMinVal;
    CLabel m_clColorStaticDistortionMaxVal;
	CExButton m_clColorButtonSave;
	CExButton m_clColorButtonClose;


    afx_msg void OnStnClickedStaticCcdHfovMinVal();
    afx_msg void OnStnClickedStaticCcdHfovMaxVal();
    afx_msg void OnStnClickedStaticCcdVfovMinVal();
    afx_msg void OnStnClickedStaticCcdVfovMaxVal();
    afx_msg void OnStnClickedStaticCcdDistortionMinVal();
    afx_msg void OnStnClickedStaticCcdDistortionMaxVal();
};
