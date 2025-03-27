#pragma once



// CIoDlg 대화 상자입니다.

class CIoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CIoDlg)

public:
	CIoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CIoDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_IO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:

	CLabel	m_Title;

	int oldInVal[4];

	bool m_bShowFlag;
	bool timerRunFlag;

	void	setInterface();
	void	initIoGrid();
	void	dispInputData();
	void	dispOutputData();

	CRect	m_rcGridDioIn;
	CRect	m_rcGridDioOut;

	int inVal[2];
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	DECLARE_EVENTSINK_MAP()
	void DblClickGridIoOut();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);	
public:
	//Grid
	CGridCtrl m_clGrid_IO_In;
	CGridCtrl m_clGrid_IO_Out;
	void	InitGridCtrl_In();
	void	InitGridCtrl_Out();

	int inRow;
	int inCol;
	int outRow;
	int outCol;
	
	//
	afx_msg void OnDBClickedGridOut(NMHDR* pNMHDR, LRESULT* pResult);
};
