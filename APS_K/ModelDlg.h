#pragma once


#include "afxwin.h"
#include "label\label.h"


#include "ExButton/exbutton.h"


// CModelDlg 대화 상자입니다.

class CModelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModelDlg)

public:
	CModelDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CModelDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_MODEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	CLabel m_labelCurSensorName;

	CLabel m_Epoxy_Shot;
	CLabel m_Epoxy_Alarm;
	CLabel m_Epoxy_Start_Time;
	CLabel m_Epoxy_Last_Time;
	CLabel m_Socket_Count;
	CLabel m_Socket_Alarm;
	CLabel m_Socket_Reset;

	CExButton m_btnFreeRun;

	bool m_bShowFlag;
	CRect m_rcGridModel;

	//CMSFlexGrid	m_gridModel;
	CFont font;

	void	setInterface();
	void	initModelGrid();
	int		getCurRowOnGrid();
	void	copyModel(int iScrNo, int iDesNo);
	void	dispCurModel();
	void	initListBox();
	void	initListBox2(int iIndex);
	void	dispCurSensor();
	void	putData();
	bool ModelCheck(CString newModel);
	bool FnAllFolderCopy(CString Src, CString Dest);
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedButtonCreate();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	DECLARE_EVENTSINK_MAP()
	void DblClickMsflexgridModel();
	afx_msg void OnBnClickedButtonParametersetting();
	afx_msg void OnBnClickedButtonDataset();
	afx_msg void OnBnClickedButtonFreeRun();
	afx_msg void OnBnClickedButtonSfrSpec();
	afx_msg void OnBnClickedBtnBarcode();
	void ClickMsflexgridEpoxyInspPara();
	CStatic m_Mes_Port;
	afx_msg void OnBnClickedButtonSfrSpec2();
	afx_msg void OnStnClickedEditEpoxyAlarmTime();
	afx_msg void OnStnClickedStaEpoxyAlarmTime2();
	afx_msg void OnStnClickedEditEpoxyShot();
	afx_msg void OnStnClickedEditEpoxyAlarm();
	afx_msg void OnStnClickedEditEpoxyStartTime();
	afx_msg void OnStnClickedEditEpoxyLastTime();
	afx_msg void OnBnClickedButtonEpoxyReset();
	afx_msg void OnStnClickedEditSocketCount();
	afx_msg void OnStnClickedEditSocketAlarm();
	afx_msg void OnBnClickedButtonSocketReset();
public:
	//Grid
	CGridCtrl m_clGridModel;
	void	InitGridCtrl_Model();
	void	ShowGridCtrl_Model(int nMode = 0);
	void	changeModelNo(int IndexNo);
	int ModelRow;
	int ModelCol;
	int ModelCurCol;
	int fixRow;
	//
	afx_msg void OnDBClickedGridModelb(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGridClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/);
	CStatic m_stDisplay;
	void GrabImgLoad();
	afx_msg void OnBnClickedBtnEepromDlg();
	afx_msg void OnBnClickedButtonModelLoad();
	afx_msg void OnBnClickedButtonCopy();
};
