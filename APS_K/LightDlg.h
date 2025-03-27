#pragma once
#include "afxwin.h"


// CLightDlg 대화 상자입니다.

class CLightDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLightDlg)

public:
	CLightDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CLightDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_LIGHT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButtonSave();
	
	//afx_msg void OnBnClickedRadioResin();

	afx_msg void OnBnClickedOk();
	
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//
	CSliderCtrl m_sliderHolderLed;
	CSliderCtrl m_sliderEpoxyLed;
	CSliderCtrl m_sliderLensLed;
	CSliderCtrl m_sliderTopChartLed;
	//
	CSliderCtrl m_sliderCam1Led;
	CSliderCtrl m_sliderCam2Led;
	CSliderCtrl m_sliderCam3Led;
	//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	
	CLabel m_LabelHolderLight;
	CLabel m_LabelEpoxyLight;
	CLabel m_LabelLensLight;
	
	CLabel m_LabelTopChartLight;


	CLabel m_LabelChartLight;
	CLabel m_LabelOcLight;
	CLabel m_LabelAlignLight;
	//
	int    m_Bchart_Sel_Index;
	int    m_BchartData_Sel_Index;

	int    m_Align_Sel_Index;
	int    m_AlignData_Sel_Index;

	int    m_Oc_Sel_Index;
	int    m_OcData_Sel_Index;
	virtual BOOL OnInitDialog();
	bool onOffFlag;
	void setInterface();
	void dispData(int ch);
	void dispData_second(int ch);
	

	void dispData_CH1(int ch);
	void dispData_CH2(int ch);
	void dispData_CH3(int ch, int value);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnStnClickedEditLed();

	
	int m_iSelLED;
	int m_iSelData;	
	afx_msg void OnBnClickedButtonPwrOnoff();
	afx_msg void OnStnClickedEditLensLed();
	afx_msg void OnStnClickedEditOcLed();
	afx_msg void OnStnClickedEditTopchartLed();
	afx_msg void OnClickedTopChart(UINT nID);
	afx_msg void OnClickedCam1(UINT nID);
	afx_msg void OnClickedOc(UINT nID);
	
public:
	CExButton m_bTopChart1;
	CExButton m_bTopChart2;
	CExButton m_bTopChart3;
	CExButton m_bTopChart4;
	CExButton m_bTopChart5;
	CExButton m_bTopChart6;

	CExButton m_bLeftChart;
	CExButton m_bRightChart;

	CExButton m_bTotalChart;

	CExButton m_bSensorCam1;
	CExButton m_bHolderCam1;
	CExButton m_bEpoxyInspCam1;
	CExButton m_bLensCam1;
	//
	CExButton m_bStainOc;
	CExButton m_bStainOc2;
	CExButton m_bStainOc3;
	CExButton m_bStainOc4;
	CExButton m_bDefectOc;
	afx_msg void OnStnClickedEditBchartLed();
	afx_msg void OnBnClickedBtnChartChange();
	afx_msg void OnBnClickedBtnTop1Chartled();
	afx_msg void OnBnClickedBtnChartLedOff();
	afx_msg void OnBnClickedButtonLightClose();
};
