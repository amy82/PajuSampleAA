#pragma once

#include "Label/Label.h"
//! ===============================================
//! Added by LHW (2013/2/22)

//! 그래프 컨트롤 클래스 선언
class CGraph2DWnd;

//! 그래프 컨트롤의 개수
// const int iBufSize_Graph_2D = 2;
// 
// //! 1개의 그래프 컨트롤에 그려지는 그래프의 개수
// const int iBufSize_Graph_Overlap = 5;
// 
// //! 1개의 그래프를 이루는 그래프 데이터 버퍼의 크기
// const int iBufSize_Pixel_Graph = 8192;

//! X축 수직선의 구분 index
// const int iIndex_Max_Center		= 0;
// const int iIndex_Max_UpperLeft	= 1;
// const int iIndex_Max_UpperRight = 2;
// const int iIndex_Max_LowerLeft	= 3;
// const int iIndex_Max_LowerRight = 4;

// const int iIndex_MTF4  = 0;	//! MTF(N/4)
// const int iIndex_MTF8  = 1;	//! MTF(N/8)
// const int iIndex_MTF50 = 2;	//! MTF50

#define BUFFER_SIZE_GRAPH_2D		3
#define BUFFER_SIZE_GRAPH_OVERLAP	5
#define BUFFER_SIZE_PIXEL_GRAPH		8192

#define INDEX_MTF4	0
#define INDEX_MTF8	1
#define INDEX_MTF50	2

// CAutoDispDlg 대화 상자입니다.

class CAutoDispDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAutoDispDlg)

public:
	CAutoDispDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAutoDispDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_AUTODISP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

protected:
	void	setInterface();

	//! 그래프 컨트롤 배열
	CGraph2DWnd *m_apGraphWnd[3];	
	bool MakeGraphWnd();
	void ReleaseGraphWnd();

	//! 그래프 커서를 가지고 있는 그래프의 index, 0 based
	int m_aiIndex_Overlap_Cursor[BUFFER_SIZE_GRAPH_2D];

	//! 프로그램 다운 방지용, 그래프 컨트롤 동시 접근 차단
	CCriticalSection m_acsGraph[2];	

	//! 그래프를 눈에 보이거나 숨길 때
	void Proc_GraphVisible(int iIndex_Plot, int iIndex_Overlap);
	bool SetGraphVisible(int iIndex_Plot, int iIndex_Overlap, bool bFlag_Visible);
	int UpdateCursorValue(int iIndex_Plot);
	//! 눈에 안보이는 그래프 커서 삭제하고, 동일한 위치에 눈에 보이는 그래프에 커서 추가
	int ExChangeCursor(int iIndex_Plot);

	//! 커서를 움직이게 할 때
	void MoveCursor_Left_Graph(int iIndex_Plot);
	void MoveCursor_Right_Graph(int iIndex_Plot);

	//! 그래프의 커서 이벤트를 받을 때
	LRESULT OnCursorEventMsgInPlot(WPARAM wParam, LPARAM lParam);	

	//! GUI 처리 함수
	void SetGUI_Graph_Visible_Chk();

	//! 임시 데이터 생성
	int RangedRandDemo( int range_min, int range_max, int n );
	void SetTempData(int iIndex_Plot);

	//! 그래프를 그리고, 그래프 커서값을 표시한다.
	int SetCursorValue(int iIndex_Plot, int iIndex_Overlap, int iDataIndex, int iCursorIndex = 0);

	

public:
	//! =========================================================================================================
	//! 그래프 입력 데이터 버퍼	
	double m_adDataX        [BUFFER_SIZE_GRAPH_2D][BUFFER_SIZE_GRAPH_OVERLAP][BUFFER_SIZE_PIXEL_GRAPH];
	double m_adDataY        [BUFFER_SIZE_GRAPH_2D][BUFFER_SIZE_GRAPH_OVERLAP][BUFFER_SIZE_PIXEL_GRAPH];
	int    m_aiDataSize     [BUFFER_SIZE_GRAPH_2D][BUFFER_SIZE_GRAPH_OVERLAP];

	//! 그래프 상의 특정 지점에 X축에 수직선을 표시한다.
	double m_adData_MTF4    [BUFFER_SIZE_GRAPH_2D][BUFFER_SIZE_GRAPH_OVERLAP];	//! MTF(N/4) X축 값
	double m_adData_MTF8    [BUFFER_SIZE_GRAPH_2D][BUFFER_SIZE_GRAPH_OVERLAP];	//! MTF(N/8) X축 값
	double m_adData_MTF50   [BUFFER_SIZE_GRAPH_2D][BUFFER_SIZE_GRAPH_OVERLAP];	//! MTF50	 X축 값

	bool   m_abFlag_Visible [BUFFER_SIZE_GRAPH_2D][BUFFER_SIZE_GRAPH_OVERLAP];	//! true이면 그래프를 눈에 보이게 한다.
	int    m_aiCount_Visible[BUFFER_SIZE_GRAPH_2D];							//! 눈에 보이는 그래프의 개수

	CLabel	m_label_Cur_Task;
	CLabel	m_label_Graph1;
	CLabel	m_label_Graph2;
	CLabel	m_label_Graph3;
	CLabel  m_label_Graph5;
	CLabel	m_label_Disp_Opt;
	CLabel	m_label_Disp_Defect;

	int		m_iCur_Index_Through;

	//! 버퍼 초기화
	bool Init_Buffser(int iIndex_Plot, int iIndex_Overlap);

	int DrawGraph(int iIndex_Plot);				/* iMode 0 : 수동모드 1 : 자동모드 */

	void	dispCurTaskOnLabel(int iRtn, CString sLabel);

	//! 그래프에 커서를 추가한다. 
	void AddCursor_In_Graph();

	//! =========================================================================================================

	void	DispResultImage_Opt();
	void	DispResultImage_Defect();
	void	DrawBarGraph();

	int		m_iSizeX_Client;
	int		m_iSizeY_Client;

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL DestroyWindow();
	afx_msg void OnPaint();
};
