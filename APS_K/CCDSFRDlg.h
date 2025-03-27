#pragma once

//! ===============================================
//! Added by LHW (2013/2/22)

//! 그래프 컨트롤 클래스 선언
class CGraph2DWnd;

//! 그래프 컨트롤의 개수
const int iBufSize_Graph_2D = 2;

//! 1개의 그래프 컨트롤에 그려지는 그래프의 개수
const int iBufSize_Graph_Overlap = 5;

//! 1개의 그래프를 이루는 그래프 데이터 버퍼의 크기
const int iBufSize_Pixel_Graph = 8192;

//! X축 수직선의 구분 index
const int iIndex_MTF4  = 0;	//! MTF(N/4)
const int iIndex_MTF8  = 1;	//! MTF(N/8)
const int iIndex_MTF50 = 2;	//! MTF50

#include "afxwin.h"
#include "Label/Label.h"

// CCCDSFRDlg 대화 상자입니다.

class CCCDSFRDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCCDSFRDlg)

public:
	CCCDSFRDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCCDSFRDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_CCD_SFR };



protected:
	//! 그래프 컨트롤 배열
	CGraph2DWnd *m_apGraphWnd[iBufSize_Graph_2D];	
	bool MakeGraphWnd();
	void ReleaseGraphWnd();

	//! 그래프 커서를 가지고 있는 그래프의 index, 0 based
	int m_aiIndex_Overlap_Cursor[iBufSize_Graph_2D];

	//! 프로그램 다운 방지용, 그래프 컨트롤 동시 접근 차단
	CCriticalSection m_acsGraph[iBufSize_Graph_2D];	

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
	int DrawGraph(int iIndex_Plot);	
	int SetCursorValue(int iIndex_Plot, int iIndex_Overlap, int iDataIndex, int iCursorIndex = 0);

public:
	//! =========================================================================================================
	//! 그래프 입력 데이터 버퍼	
	double m_adDataX        [iBufSize_Graph_2D][iBufSize_Graph_Overlap][iBufSize_Pixel_Graph];
	double m_adDataY        [iBufSize_Graph_2D][iBufSize_Graph_Overlap][iBufSize_Pixel_Graph];
	int    m_aiDataSize     [iBufSize_Graph_2D][iBufSize_Graph_Overlap];

	//! 그래프 상의 특정 지점에 X축에 수직선을 표시한다.
	double m_adData_MTF4    [iBufSize_Graph_2D][iBufSize_Graph_Overlap];	//! MTF(N/4) X축 값
	double m_adData_MTF8    [iBufSize_Graph_2D][iBufSize_Graph_Overlap];	//! MTF(N/8) X축 값
	double m_adData_MTF50   [iBufSize_Graph_2D][iBufSize_Graph_Overlap];	//! MTF50	 X축 값

	bool   m_abFlag_Visible [iBufSize_Graph_2D][iBufSize_Graph_Overlap];	//! true이면 그래프를 눈에 보이게 한다.
	int    m_aiCount_Visible[iBufSize_Graph_2D];							//! 눈에 보이는 그래프의 개수

	//! 버퍼 초기화
	bool Init_Buffser(int iIndex_Plot, int iIndex_Overlap);
	//! =========================================================================================================

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	void	drawROI();
	
    void    Raw_ImageSave(BYTE* rawImg, int index);
    void    CCARawImageLoad(BYTE* LoadImg, int index , bool autoRun = false);
	void	drawRectSFR(int iRectNo = 999);
	void	drawFieldCircleView();

    void	drawRectFOV(int iRectNo = 999);
    void    MoveRectFov(int nMoveType, int nType, int nMoveSize);
    void	drawRectSNR(int iRectNo = 999);
    void    MoveRectSNR(int nMoveType, int nType, int nMoveSize);

    CRect m_clRectDrawFov[MAX_FOV_COUNT];
    CRect m_clRectDrawSnr[MAX_SNR_COUNT];

    int GetSelectedSNRNo(CPoint point);
    int GetSelectedFOVNo(CPoint point);
	int		checkNoSFR(CPoint point);

	void	setInterface();

	void	initGrid();
	void	dispDataOnGrid();

	CRect	m_rcROI[COMMON_LAST_MARK_CNT];// LAST_MARK_CNT];

	int		m_iOffsetX_SFR[COMMON_LAST_MARK_CNT];//LAST_MARK_CNT];
	int		m_iOffsetY_SFR[COMMON_LAST_MARK_CNT];//LAST_MARK_CNT];

	int		m_iSizeX_SFR[COMMON_LAST_MARK_CNT];//LAST_MARK_CNT];
	int		m_iSizeY_SFR[COMMON_LAST_MARK_CNT];//LAST_MARK_CNT];

	CRect	m_rcFixedBox[COMMON_LAST_MARK_CNT];//LAST_MARK_CNT];
	CRect	m_rcRoiBox[4];						// 원형 마크 검색 영역
	
    
	int		m_iMoveSpeed;

	int		m_iCurNo_SFR;
    int	m_nSelectIndexFOV;
    int	m_nSelectIndexSNR;

	int		m_iStep;

	bool m_bShowFlag;
	CRect m_rcGridModel;

    void RegistFovMark();
    void RegistSnrMark();
public:
    void SetFovRoi();
    void SetSnrRoi();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();

	afx_msg void OnBnClickedButtonImgSave();
	afx_msg void OnBnClickedButtonImgLoad();
	//	BOOL m_iSelType;
	int m_iSelMoveType;

	CComboBox Combox_SFRIndex;
	void ComboxSet();
	void ComboxValueSet();

	int comBox_Index;
	CLabel m_SFR_X;
	CLabel m_SFR_Y;
	CLabel m_SFR_Dic;

	CLabel m_Uart_s;
	CLabel m_Uart_e;
	int curSfrPosX;
	int curSfrPosY;
	afx_msg void OnCbnCloseupComboSfr();
	//
	afx_msg void OnBnClickedRadioPos();
	afx_msg void OnBnClickedRadioSize();
	afx_msg void OnBnClickedButtonBoxUp();
	afx_msg void OnBnClickedButtonBoxDown();
	afx_msg void OnBnClickedButtonBoxLeft();
	afx_msg void OnBnClickedButtonBoxRight();
	afx_msg void OnBnClickedButtonBoxSpeed();
	afx_msg void OnBnClickedButtonRegist();
	afx_msg void OnBnClickedButtonSfrTest();

	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	


	afx_msg void OnBnClickedButtonAlignTest();
	

	int m_i_graph_disp_mode ;


	afx_msg void OnBnClickedButtonLivemode();
	BOOL m_bShadeCalibration;
	afx_msg void OnBnClickedButtonAutoAa();
	CExButton m_btnCoverOn;
	CExButton m_btnCoverOff;
	afx_msg void OnStnClickedStaticMotorspeed();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonRegistEdit();
	CLabel m_labelAlignResult;

public:
	void SetAlignData_Tilt(double dx, double dy);
	void SetAlignData_Shift(double dx, double dy);
    unsigned char* m_pImgBuff;

protected:
	double m_dTilt_X;
	double m_dTilt_Y;

	double m_dShift_X;
	double m_dShift_Y;
	bool bCircleView;
	void UpdateAlignData();
public:
	afx_msg void OnBnClickedPatternRegist();
	afx_msg void OnBnClickedPatternFind();
	afx_msg void OnBnClickedPatternPos();
	afx_msg void OnBnClickedPatternView();
	afx_msg void OnBnClickedDistortionPos();
	afx_msg void OnBnClickedBtnAutoZCalc();
	afx_msg void OnBnClickedBtnAutoZSearch();
	afx_msg void OnBnClickedButtonImgSave2();
	afx_msg void OnBnClickedButtonCcdOpen();



	afx_msg void OnBnClickedButtonCcdStop();
	afx_msg void OnBnClickedButtonCcdPlay();
	afx_msg void OnBnClickedButtonCcdClose();

	afx_msg void OnStnClickedEditSfrX();
	afx_msg void OnStnClickedEditSfrY();
	afx_msg void OnBnClickedBtnSfrposSave();
	afx_msg void OnBnClickedButtonModelLoad();
	afx_msg void OnBnClickedUartOpen();
	afx_msg void OnBnClickedUartClose();
	afx_msg void OnBnClickedUartSend();
	afx_msg void OnBnClickedUartSave();
	afx_msg void OnStnClickedEditUart1();
	afx_msg void OnStnClickedEditUart2();
	void UartSet();
	afx_msg void OnBnClickedButtonModelLoad2();
    afx_msg void OnBnClickedButtonRawLoad();
    afx_msg void OnBnClickedButton6500kRawLoad();
    afx_msg void OnBnClickedButton2800kRawLoad();
    afx_msg void OnBnClickedButtonDarkRawLoad();
    afx_msg void OnBnClickedButtonCcdFovMarkRegist();
    afx_msg void OnBnClickedButtonCcdFovMarkView();
    afx_msg void OnBnClickedButtonCcdSnrMarkRegist();
    afx_msg void OnBnClickedButtonCcdSnrRoiView();
	afx_msg void OnBnClickedButtonZooxLinearMode();
	afx_msg void OnBnClickedButtonChartSecondRawLoad();
	afx_msg void OnBnClickedButtonChartFirstRawLoad();
	afx_msg void OnStnClickedEditSfrDic();
	afx_msg void OnBnClickedButtonChartSetView();
	afx_msg void OnBnClickedPatternView2();
};
