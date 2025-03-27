#pragma once

#include "afxwin.h"
#include "Utility\GridCtrl\GridCtrl.h"
#include "Utility\ButtonEx\ButtonEx.h"
#include "Label\Label.h"
// CCcdRISpecDlg 대화 상자입니다.

class CCcdRISpecDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCcdRISpecDlg)

public:
    CCcdRISpecDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCcdRISpecDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_CCD_RI_SPEC};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	void SetUnit(int nUnit);

	const int RISpecCount = 9;// 7;

    const int RIThresholdMaxCount = 21;

    int RiThresholdGridCount;
private:
	void InitCtrl();

	void InitRIGridCtrl();


	void ShowRISpec();
	void GetRISpec();

    void ShowRIThresholdSpec();
    void GetRIThresholdSpec();

    void InitRiThresholdGridCtrl1();
    void InitRiThresholdGridCtrl2();
    void InitRiThresholdGridCtrl3();
    void InitRiThresholdGridCtrl4();
    void InitRiThresholdGridCtrl5();

private:
    CGridCtrl m_clGridRIThresholdSpec1;
    CGridCtrl m_clGridRIThresholdSpec2;
    CGridCtrl m_clGridRIThresholdSpec3;
    CGridCtrl m_clGridRIThresholdSpec4;
    CGridCtrl m_clGridRIThresholdSpec5;

private:
    CGridCtrl m_clGridRI1Spec;
    CGridCtrl m_clGridRI2Spec;
	CGridCtrl m_clGridRI3Spec;
	CGridCtrl m_clGridRI4Spec;

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
	

	afx_msg void OnNMDblClickedRi1Spec(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMDblClickedRi2Spec(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnNMDblClickedRi3Spec(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnNMDblClickedRi5Spec(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnNMDblClickedRi6Spec(NMHDR* pNMHDR, LRESULT* pResult);




    //base
	afx_msg void OnNMDblClickedRi4Spec(NMHDR* pNMHDR, LRESULT* pResult);
	


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
