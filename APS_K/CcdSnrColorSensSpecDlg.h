#pragma once

#include "afxwin.h"
#include "Utility\GridCtrl\GridCtrl.h"
#include "Utility\ButtonEx\ButtonEx.h"
#include "Label\Label.h"
// CCcdSnrColorSensSpecDlg 대화 상자입니다.

class CCcdSnrColorSensSpecDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCcdSnrColorSensSpecDlg)

public:
    CCcdSnrColorSensSpecDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCcdSnrColorSensSpecDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_CCD_SNR_COLORSENS_SPEC};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	void SetUnit(int nUnit);
	const int SnrMaxCount = 4;// 3;
	const int ColorSensitivityMaxCount = 9;
private:
	void InitCtrl();
	
	void InitSnrGridCtrl();
    void InitColorSensitivityGridCtrl();

	void ShowSnrSpec();
	void GetSnrSpec();
	void ShowColorSensitivitySpec();
	void GetColorSensitivitySpec();
private:
	CGridCtrl m_clGridSnrSpec;
	CGridCtrl m_clGridColorSensitivitySpec;

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
	
	afx_msg void OnNMDblClickedColorSensitivitySpec(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMDblClickedSnrSpec(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnStnClickedStaticCcdSfrSpecCenterSfrLimitVal();
	afx_msg void OnStnClickedStaticCcdSfrSpecCornerSfrLimitVal();
	afx_msg void OnStnClickedStaticCcdSfrSpecCornerSfrDeviationLimitVal();
	afx_msg void OnStnClickedStaticCcdSfrSpecOcXyVal();
	afx_msg void OnStnClickedStaticCcdSfrSpecOcThVal();
	afx_msg void OnBnClickedButtonCcdSfrSpecSave();
	afx_msg void OnBnClickedButtonCcdSfrSpecClose();
	
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
	CExButton m_clColorButtonSave;
	CExButton m_clColorButtonClose;
};
