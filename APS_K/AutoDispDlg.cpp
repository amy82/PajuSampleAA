// AutorunDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AutoDispDlg.h"

//! ====================================================================================
//! 그래프 컨트롤 클래스를 포함시킨다. 
#include "Graph2D/Graph2DWnd/Graph2DWnd.h"
//! ====================================================================================
// CAutoDispDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAutoDispDlg, CDialogEx)

	CAutoDispDlg::CAutoDispDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAutoDispDlg::IDD, pParent)
{
	int i = 0, j = 0;
	for ( i = 0; i < BUFFER_SIZE_GRAPH_2D; i++ )
	{
		m_apGraphWnd[i] = NULL;	

		m_aiIndex_Overlap_Cursor[i] = 0;

		m_aiCount_Visible[i] = BUFFER_SIZE_GRAPH_OVERLAP;

		for ( j = 0; j < BUFFER_SIZE_GRAPH_OVERLAP; j++ )
		{
			Init_Buffser(i, j);

			m_abFlag_Visible[i][j] = true;					
		}		
	}
}

CAutoDispDlg::~CAutoDispDlg()
{
}

void CAutoDispDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LABEL_CUR_TASK, m_label_Cur_Task);
	DDX_Control(pDX, IDC_LABEL_GRAPH1, m_label_Graph1);
	DDX_Control(pDX, IDC_LABEL_GRAPH2, m_label_Graph2);
	DDX_Control(pDX, IDC_LABEL_GRAPH3, m_label_Graph3);
	DDX_Control(pDX, IDC_LABEL_GRAPH5, m_label_Graph5);
	DDX_Control(pDX, IDC_LABEL_DISP3, m_label_Disp_Opt);
	DDX_Control(pDX, IDC_LABEL_DISP4, m_label_Disp_Defect);
}


BEGIN_MESSAGE_MAP(CAutoDispDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAutoDispDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CAutoDispDlg::OnBnClickedCancel)
	ON_WM_SHOWWINDOW()

	ON_MESSAGE(WM_GRAPH2D_CURSOR_EVENT, OnCursorEventMsgInPlot)	//! Added by LHW (2013/2/22)

	ON_WM_DESTROY()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CAutoDispDlg 메시지 처리기입니다.


void CAutoDispDlg::OnBnClickedOk(){}
void CAutoDispDlg::OnBnClickedCancel(){}

BOOL CAutoDispDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	setInterface();

	bool bRet = MakeGraphWnd();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CAutoDispDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
}


void CAutoDispDlg::setInterface()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	WINDOWPLACEMENT wndpl;

	wndpl.rcNormalPosition = pFrame->m_rectCamDispPos2;
	wndpl.rcNormalPosition.left = pFrame->m_rectCamDispPos2.left + 100;
	wndpl.rcNormalPosition.top -= SUB_DLG_OFFSET_Y - 10;
	wndpl.rcNormalPosition.bottom = MAIN_DLG_SIZE_Y - 5 - 95;
	wndpl.rcNormalPosition.right = MAIN_DLG_SIZE_X;
	this->MoveWindow(&wndpl.rcNormalPosition);

	UpdateData(false);

	m_label_Cur_Task
		.SetBkColor(GRID_COLOR_GREEN)
		.SetFontBold(TRUE)
		.SetFontSize(24)
		.SetText("");

	sLangChange.LoadStringA(IDS_STRING1094);
	m_label_Graph1
		.SetBkColor(M_COLOR_WHITE)
		.SetFontBold(TRUE)
		.SetFontSize(16)
		.SetText(sLangChange);

	sLangChange.LoadStringA(IDS_STRING1067);
	m_label_Graph2
		.SetBkColor(M_COLOR_WHITE)
		.SetFontBold(TRUE)
		.SetFontSize(16)
		.SetText(sLangChange);

	sLangChange.LoadStringA(IDS_STRING570);
	m_label_Graph3
		.SetBkColor(M_COLOR_WHITE)
		.SetFontBold(TRUE)
		.SetFontSize(16)
		.SetText(sLangChange);

	sLangChange.LoadStringA(IDS_STRING1415);
	m_label_Graph5
		.SetBkColor(M_COLOR_WHITE)
		.SetFontBold(TRUE)
		.SetFontSize(16)
		.SetText(sLangChange);

	sLangChange.LoadStringA(IDS_STRING885);
	m_label_Disp_Opt
		.SetBkColor(M_COLOR_WHITE)
		.SetFontBold(TRUE)
		.SetFontSize(16)
		.SetText(sLangChange);

	sLangChange.LoadStringA(IDS_STRING1343);
	m_label_Disp_Defect
		.SetBkColor(M_COLOR_WHITE)
		.SetFontBold(TRUE)
		.SetFontSize(16)
		.SetText(sLangChange);

	CRect rcClient;

	GetDlgItem(IDC_DISP_OPT)->GetClientRect(rcClient);
	m_iSizeX_Client	= rcClient.right - rcClient.left;
	m_iSizeY_Client	= rcClient.bottom - rcClient.top;
#ifdef ON_LINE_VISION
	vision.InitBuffer_AutoDisplay(m_iSizeX_Client, m_iSizeY_Client);

	CWnd* pWnd;
	
	pWnd = GetDlgItem(IDC_DISP_OPT);
	MdispSelectWindow(vision.MilOptDisplayImage, vision.MilOptImage, pWnd->m_hWnd);
	pWnd = GetDlgItem(IDC_DISP_DEFECT);
	MdispSelectWindow(vision.MilDefectDisplayImage, vision.MilDefectImage, pWnd->m_hWnd);

	vision.enableOverlay_AutoDisp();
#endif
}


//! 커서를 왼쪽으로 움직이게 한다.
void CAutoDispDlg::MoveCursor_Left_Graph(int iIndex_Plot)
{
	if ( iIndex_Plot < 0 || iIndex_Plot >= BUFFER_SIZE_GRAPH_2D )
	{
		return;
	}

	if ( m_apGraphWnd[iIndex_Plot] != NULL )
	{
		if ( m_apGraphWnd[iIndex_Plot]->GetCurrentCursorSize() > 0 )
		{			
			m_apGraphWnd[iIndex_Plot]->MoveCursor(0, false, false, m_aiIndex_Overlap_Cursor[iIndex_Plot]);
			m_apGraphWnd[iIndex_Plot]->Invalidate();
		}
	}
}

//! 커서를 오른쪽으로 움직이게 한다.
void CAutoDispDlg::MoveCursor_Right_Graph(int iIndex_Plot)
{
	if ( iIndex_Plot < 0 || iIndex_Plot >= BUFFER_SIZE_GRAPH_2D )
	{
		return;
	}

	if ( m_apGraphWnd[iIndex_Plot] != NULL )
	{
		if ( m_apGraphWnd[iIndex_Plot]->GetCurrentCursorSize() > 0 )
		{			
			m_apGraphWnd[iIndex_Plot]->MoveCursor(0, true, false, m_aiIndex_Overlap_Cursor[iIndex_Plot]);
			m_apGraphWnd[iIndex_Plot]->Invalidate();
		}
	}
}

//! 그래프에서 커서 이벤트가 발생하면 메시지가 온다.
LRESULT CAutoDispDlg::OnCursorEventMsgInPlot(WPARAM wParam, LPARAM lParam)
{
	int iTemp = (int)wParam;
	strGraph2D_Cursor_Event* pCursorInfo = (strGraph2D_Cursor_Event*)lParam;

	if ( pCursorInfo == NULL || m_apGraphWnd == NULL )
	{
		return 0;
	}

	int iPlotIndex    = pCursorInfo->iPlotIndex;	
	int iOverlapIndex = pCursorInfo->iOverlapIndex;
	int iDataIndex    = pCursorInfo->iDataIndex;
	int iCursorIndex  = pCursorInfo->iCursorIndex;

	int iRet = SetCursorValue(iPlotIndex, iOverlapIndex, iDataIndex, iCursorIndex);
	if ( iRet < 0 )
	{
		return 0;
	}

	return 1;
}

//! 현재 그래프의 커서값을 Edit 컨트롤에 표시
//! 그래프 커서는 해당 그래프에 종속되지만, 현재는 그래프 데이터의 X축 간격이 동일하다.
//! 즉, 해당 그래프의 커서 데이터의 index에 해당하는 다른 그래프의 데이터를 표시하면 된다. 
int CAutoDispDlg::SetCursorValue(int iIndex_Plot, int iIndex_Overlap, int iDataIndex, int iCursorIndex)
{
	if ( iIndex_Plot < 0 || iIndex_Plot >= BUFFER_SIZE_GRAPH_2D )
	{
		return -1;
	}
	if ( iIndex_Overlap < 0 || iIndex_Overlap >= BUFFER_SIZE_GRAPH_OVERLAP )
	{
		return -2;
	}
	if ( iDataIndex < 0 || iDataIndex >= BUFFER_SIZE_PIXEL_GRAPH )
	{
		return -3;
	}
	if ( m_apGraphWnd == NULL )
	{
		return -4;
	}

	bool abRet[2];
	int i = 0;
	double  adDataX[BUFFER_SIZE_GRAPH_OVERLAP], adDataY[BUFFER_SIZE_GRAPH_OVERLAP];
	CString asDataX[BUFFER_SIZE_GRAPH_OVERLAP], asDataY[BUFFER_SIZE_GRAPH_OVERLAP], asData[BUFFER_SIZE_GRAPH_OVERLAP];
	strGraph2D_Y_Axis_Info strAxisYInfo;	//! Y축

	for (i = 0; i < BUFFER_SIZE_GRAPH_OVERLAP; i++ )
	{		
		m_apGraphWnd[iIndex_Plot]->GetResourceYInfo(strAxisYInfo, i);		

		if ( strAxisYInfo.bShowGraph == false )
		{
			abRet[0] = false;
			abRet[1] = false;
		}
		else
		{			
			abRet[0] = m_apGraphWnd[iIndex_Plot]->GetPlotDataX(adDataX[i], iDataIndex, i);
			if ( abRet[0] == true )
			{
				asDataX[i].Format(_T("%.3lf"), adDataX[i]);
			}
			else
			{
				asDataX[i] = _T("-");
			}

			abRet[1] = m_apGraphWnd[iIndex_Plot]->GetPlotDataY(adDataY[i], iDataIndex, i);
			if ( abRet[1] == true )
			{
				asDataY[i].Format(_T("%.3lf"), adDataY[i]);
			}
			else
			{
				asDataY[i] = _T("-");
			}
		}		

		if ( (abRet[0] == true) && (abRet[1] == true) )
		{
			asData[i].Format(_T("%s,%s"), asDataX[i], asDataY[i]);
		}
		else
		{
			asData[i] = _T("-");
		}
	}

	return 1;
}

//! 체크 박스를 이용하여 그래프를 눈에 보이거나 숨긴다.
//! 이 때, 그래프 커서 관련 작업을 같이 진행한다. 
//!		1) 그래프 커서는 5개의 그래프 중 1개의 그래프에 종속된다.
//!		2) 그래프를 눈에 보이지 않게 하면, 해당 그래프의 커서도 같이 눈에 보이지 않게 된다.
//!		3) 눈에 보이지 않게 되는 커서는 삭제하고, 눈에 보이는 그래프에 같은 위치에 그래프 커서를 추가한다. 
void CAutoDispDlg::Proc_GraphVisible(int iIndex_Plot, int iIndex_Overlap)
{
	if ( iIndex_Plot < 0 || iIndex_Plot >= BUFFER_SIZE_GRAPH_2D )
	{
		return;
	}
	if ( iIndex_Overlap < 0 || iIndex_Overlap >= BUFFER_SIZE_GRAPH_OVERLAP )
	{
		return;
	}

	bool bFlag_Visible_Old = m_abFlag_Visible[iIndex_Plot][iIndex_Overlap];	
	bool bFlag_Visible = false;

	int iCount_Visible = m_aiCount_Visible[iIndex_Plot];

	bFlag_Visible = !bFlag_Visible_Old;

	if ( bFlag_Visible == true )
	{
		iCount_Visible++;
	}
	else
	{
		iCount_Visible--;
	}

	bool bRet = false;

	if ( iCount_Visible <= 0 )
	{
		bRet = false;
	}
	else
	{
		bRet = SetGraphVisible(iIndex_Plot, iIndex_Overlap, bFlag_Visible);		
	}

	if ( bRet == true )
	{
		m_abFlag_Visible[iIndex_Plot][iIndex_Overlap] = bFlag_Visible;
		m_aiCount_Visible[iIndex_Plot] = iCount_Visible;

		ExChangeCursor(iIndex_Plot);
		UpdateCursorValue(iIndex_Plot);
	}
	else
	{
		//! 강제 원복 시킨다.
		m_abFlag_Visible[iIndex_Plot][iIndex_Overlap] = bFlag_Visible_Old;

		SetGUI_Graph_Visible_Chk();
	}

	if ( iCount_Visible <= 0 )
	{
		sLangChange.LoadStringA(IDS_STRING1414);	//최소한 1개의 그래프는 눈에 보이도록 선택해야 합니다.
		errMsg2(Task.AutoFlag, sLangChange);
	}
}

//! 해당 그래프의 커서 표시 갱신
int CAutoDispDlg::UpdateCursorValue(int iIndex_Plot)
{
	if ( iIndex_Plot < 0 || iIndex_Plot >= BUFFER_SIZE_GRAPH_2D )
	{
		return -1;
	}
	if ( m_apGraphWnd == NULL )
	{
		return -2;
	}

	int iOverlapIndex = 0;
	int iDataIndex = 0;
	m_apGraphWnd[iIndex_Plot]->GetCursorOverlapIndex(0, iOverlapIndex);
	m_apGraphWnd[iIndex_Plot]->GetCursorDataIndex(0, iDataIndex);

	int iRet = SetCursorValue(iIndex_Plot, iOverlapIndex, iDataIndex, 0);

	return 1;
}

//! 눈에 안보이는 그래프 커서 삭제하고, 동일한 위치에 눈에 보이는 그래프에 커서 추가
int CAutoDispDlg::ExChangeCursor(int iIndex_Plot)
{
	int iOverlapIndex = m_aiIndex_Overlap_Cursor[iIndex_Plot];
	if ( iOverlapIndex < 0 || iOverlapIndex >= BUFFER_SIZE_GRAPH_OVERLAP )
	{
		return -1;
	}

	if ( m_abFlag_Visible[iIndex_Plot][iOverlapIndex] == true )
	{
		//! 그래프가 눈에 보이므로, 문제가 없다.
		return 1;
	}

	//! 삭제할 그래프 커서의 현재 정보를 알아낸다.
	int iDataIndex = 0;
	m_apGraphWnd[iIndex_Plot]->GetCursorDataIndex(0, iDataIndex);

	m_apGraphWnd[iIndex_Plot]->DeleteAllCursor(false);

	//! 눈에 보이는 그래프 중에서 1개를 고른다.
	int i = 0;
	int iIndex_Overlap_Add = -1;
	for ( i = 0; i < BUFFER_SIZE_GRAPH_OVERLAP; i++ )
	{
		if ( m_abFlag_Visible[iIndex_Plot][i] == true )
		{
			iIndex_Overlap_Add = i;
			break;
		}
	}

	m_apGraphWnd[iIndex_Plot]->AddCursorInDataIndex(iDataIndex, true, iIndex_Overlap_Add);
	m_apGraphWnd[iIndex_Plot]->SetCursorValueVisible(0, false, false, false);
	m_aiIndex_Overlap_Cursor[iIndex_Plot] = iIndex_Overlap_Add;

	return 1;
}

//! GUI 처리 함수
//! 체크 박스에 현재 설정값 표시
void CAutoDispDlg::SetGUI_Graph_Visible_Chk()
{
// 	SetButtonCheckState_InCtrl(IDC_CHECK_PLOT1_ROI_1, this, m_abFlag_Visible[0][0]);
// 	SetButtonCheckState_InCtrl(IDC_CHECK_PLOT1_ROI_2, this, m_abFlag_Visible[0][1]);
// 	SetButtonCheckState_InCtrl(IDC_CHECK_PLOT1_ROI_3, this, m_abFlag_Visible[0][2]);
// 	SetButtonCheckState_InCtrl(IDC_CHECK_PLOT1_ROI_4, this, m_abFlag_Visible[0][3]);
// 	SetButtonCheckState_InCtrl(IDC_CHECK_PLOT1_ROI_5, this, m_abFlag_Visible[0][4]);
// 
// 	SetButtonCheckState_InCtrl(IDC_CHECK_PLOT2_ROI_1, this, m_abFlag_Visible[1][0]);
// 	SetButtonCheckState_InCtrl(IDC_CHECK_PLOT2_ROI_2, this, m_abFlag_Visible[1][1]);
// 	SetButtonCheckState_InCtrl(IDC_CHECK_PLOT2_ROI_3, this, m_abFlag_Visible[1][2]);
// 	SetButtonCheckState_InCtrl(IDC_CHECK_PLOT2_ROI_4, this, m_abFlag_Visible[1][3]);
// 	SetButtonCheckState_InCtrl(IDC_CHECK_PLOT2_ROI_5, this, m_abFlag_Visible[1][4]);

	m_abFlag_Visible[0][0] = true;
	m_abFlag_Visible[0][1] = true;
	m_abFlag_Visible[0][2] = true;
	m_abFlag_Visible[0][3] = true;
	m_abFlag_Visible[0][4] = true;

	m_abFlag_Visible[1][0] = true;
	m_abFlag_Visible[1][1] = true;
	m_abFlag_Visible[1][2] = true;
	m_abFlag_Visible[1][3] = true;
	m_abFlag_Visible[1][4] = true;

	m_abFlag_Visible[2][0] = true;
	m_abFlag_Visible[2][1] = true;
	m_abFlag_Visible[2][2] = true;
	m_abFlag_Visible[2][3] = true;
	m_abFlag_Visible[2][4] = true;
}

//! 그래프를 눈에 보이거나 숨길 때
bool CAutoDispDlg::SetGraphVisible(int iIndex_Plot, int iIndex_Overlap, bool bFlag_Visible)
{
	if ( iIndex_Plot < 0 || iIndex_Plot >= BUFFER_SIZE_GRAPH_2D )
	{
		return false;
	}
	if ( iIndex_Overlap < 0 || iIndex_Overlap >= BUFFER_SIZE_GRAPH_OVERLAP )
	{
		return false;
	}
	if ( m_apGraphWnd[iIndex_Plot] == NULL )
	{
		return false;
	}

	strGraph2D_Y_Axis_Info strAxisYInfo;	//! Y축

	m_apGraphWnd[iIndex_Plot]->GetResourceYInfo(strAxisYInfo, iIndex_Overlap);

	if ( m_aiDataSize[iIndex_Plot][iIndex_Overlap] <= 0 )
	{
		strAxisYInfo.bShowGraph = false;
	}
	else
	{
		strAxisYInfo.bShowGraph = bFlag_Visible;
	}

	m_apGraphWnd[iIndex_Plot]->SetResourceYInfo(strAxisYInfo, iIndex_Overlap);

	m_apGraphWnd[iIndex_Plot]->m_bChanged = true;
	m_apGraphWnd[iIndex_Plot]->Invalidate();

	return true;
}


//! 버퍼 초기화
bool CAutoDispDlg::Init_Buffser(int iIndex_Plot, int iIndex_Overlap)
{
	if ( iIndex_Plot < 0 || iIndex_Plot >= BUFFER_SIZE_GRAPH_2D )
	{
		return false;
	}
	if ( iIndex_Overlap < 0 || iIndex_Overlap >= BUFFER_SIZE_GRAPH_OVERLAP )
	{
		return false;
	}

	int i = 0;
	for ( i = 0; i < BUFFER_SIZE_PIXEL_GRAPH; i++ )
	{
		m_adDataX[iIndex_Plot][iIndex_Overlap][i] = 0.;
		m_adDataY[iIndex_Plot][iIndex_Overlap][i] = 0.;
	}

	m_aiDataSize[iIndex_Plot][iIndex_Overlap] = 0;

	m_adData_MTF4[iIndex_Plot][iIndex_Overlap] = 0.;
	m_adData_MTF8[iIndex_Plot][iIndex_Overlap] = 0.;
	m_adData_MTF50[iIndex_Plot][iIndex_Overlap] = 0.;

	return true;
}

//! 그래프 컨트롤 생성
bool CAutoDispDlg::MakeGraphWnd()
{
	ReleaseGraphWnd();

	int iIndex_Failed = -1;
	int iRet = 0;
	int i = 0, j = 0;

	for ( i = 0; i < BUFFER_SIZE_GRAPH_2D; i++ )
	{
		m_apGraphWnd[i] = new CGraph2DWnd;
		if ( m_apGraphWnd[i] == NULL )
		{
			iIndex_Failed = i;
			break;
		}
	}
	if ( iIndex_Failed >= 0 )
	{
		return false;
	}

	BOOL bCreateWnd = FALSE;

	for ( i = 0; i < BUFFER_SIZE_GRAPH_2D; i++ )
	{
		bCreateWnd = m_apGraphWnd[i]->Create(NULL, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, CRect(0, 0, 0, 0), this, 0x0000, NULL);
		if ( bCreateWnd == FALSE )
		{
			iIndex_Failed = i;
			break;
		}
	}
	if ( iIndex_Failed >= 0 )
	{
		return false;
	}

	strGraph2D_Y_Axis_Info strAxisYInfo;	//! Y축
	strGraph2DResourceInfo strResourceInfo;	//! X축

	for ( i = 0; i < BUFFER_SIZE_GRAPH_2D; i++ )
	{
		//! 각각 리소스 정보를 갖도록 함
		m_apGraphWnd[i]->MakeResourcePtr();

		//! 5개의 그래프를 그릴 수 있게 한다.
		m_apGraphWnd[i]->MakePlotBuffer(BUFFER_SIZE_GRAPH_OVERLAP);

		//! 그래프 컨트롤의 고유 식별 index를 설정
		m_apGraphWnd[i]->SetPlotIndex(i);

		//! 여러 개의 그래프라도 Y축은 1개이다.
		m_apGraphWnd[i]->m_bMultiPlotOneAxis = true;

		m_apGraphWnd[i]->m_bCursorEventMsg            = true;
		m_apGraphWnd[i]->m_bRegionCursorEventMsg      = false;
		m_apGraphWnd[i]->m_bRegionCursorRMouseDownChk = false;
		m_apGraphWnd[i]->m_bXAutoRangeRegionCursor    = false;
		m_apGraphWnd[i]->m_bYAutoRangeRegionCursor    = false;

		//! 추가 될 커서 선 표시 방식 설정
		m_apGraphWnd[i]->m_eCursorLineMode = E_GRAPH2D_CUROSR_LINE_X;

		m_apGraphWnd[i]->m_eCursorAllSearchMode      = E_GRAPH2D_CURSOR_ALL_SEARCH_NONE;
		m_apGraphWnd[i]->m_bXValueLineRMouseDownChk  = false;
		m_apGraphWnd[i]->m_bChildCursorRMouseDownChk = false;
		m_apGraphWnd[i]->m_bAutoDrawCompleteMsg      = false;
		m_apGraphWnd[i]->m_bAxisYEventMsg            = false;
		m_apGraphWnd[i]->m_bAuxCursorRMouseDownChk   = false;

		for ( j = 0; j < BUFFER_SIZE_GRAPH_OVERLAP; j++ )
		{
			m_apGraphWnd[i]->GetResourceYInfo(strAxisYInfo, j);
			strAxisYInfo.bShowGraph = false;

			//! 그래프 색상
			switch(j)
			{
			case 0:
				{
					strAxisYInfo.clrData = RGB(0, 0, 255);
				}
				break;
			case 1:
				{
					strAxisYInfo.clrData = RGB(255, 0, 0);
				}
				break;
			case 2:
				{
					strAxisYInfo.clrData = RGB(0, 255, 0);
				}
				break;
			case 3:
				{
					strAxisYInfo.clrData = RGB(63, 0, 153);
				}
				break;
			case 4:
				{
					strAxisYInfo.clrData = RGB(0, 216, 255);
				}
				break;
			}//! switch(j)

			//! 그래프에서 Y축 Range는 그래프 데이터가 튀지 않는 한에는 '0 ~ 1'로 고정한다. 
			strAxisYInfo.strAxisInfo.eAutoRangeReservedMax = E_GRAPH2D_AUTO_RANGE_RESERVED_CONSIDER;
			strAxisYInfo.strAxisInfo.eAutoRangeReservedMin = E_GRAPH2D_AUTO_RANGE_RESERVED_CONSIDER;
			strAxisYInfo.strAxisInfo.eMarginType = E_GRAPH2D_RANGE_MARGIN_NONE;
			strAxisYInfo.strAxisInfo.dbAutoRangeReservedMax = 1.0;
			strAxisYInfo.strAxisInfo.dbAutoRangeReservedMin = 0.;
			strAxisYInfo.iLineWidth = 3;

			strAxisYInfo.strAxisInfo.iGridTextPrecision = 3;
			strAxisYInfo.strAxisInfo.iCursorTextPrecision = 3;
			m_apGraphWnd[i]->SetResourceYInfo(strAxisYInfo, j);

		}//! for ( j = 0; j < BUFFER_SIZE_GRAPH_OVERLAP; j++ )




		////////////////////// 정재호 수정..
		m_apGraphWnd[i]->GetResourceInfo(strResourceInfo);
		strResourceInfo.iAxisThickness						= 1;
		strResourceInfo.clrEntireBackGround					= RGB(231, 231, 231);	//! 그래프 바탕 색상
		strResourceInfo.strAxisInfoX.iCursorTextPrecision	= 0;

		/* LKS */
		//////////////////////////////////////////////////////////////////////////
		if ( i < 2 )
		{
			strResourceInfo.strAxisInfoX.eGridTextType			= E_GRAPH2D_GRID_DOUBLE;	//E_GRAPH2D_GRID_INTEGER;
			strResourceInfo.strAxisInfoX.bIncrementGrid         = false;	//! Modify by LHW (2013/3/26)
			strResourceInfo.strAxisInfoX.dbIncrementGrid        = -5.0;
			strResourceInfo.strAxisInfoX.iGridTextPrecision		= 3;//0;
			strResourceInfo.strAxisInfoX.bDirection_Plus        = false;	//! Added by LHW (2013/3/26)
		}
		else
		{
			strResourceInfo.strAxisInfoX.eGridTextType			= E_GRAPH2D_GRID_DOUBLE;//E_GRAPH2D_GRID_INTEGER;
			strResourceInfo.strAxisInfoX.bIncrementGrid         = false;
			strResourceInfo.strAxisInfoX.dbIncrementGrid        = 5.0;
			strResourceInfo.strAxisInfoX.iGridTextPrecision		= 3;//0;
			strResourceInfo.strAxisInfoX.bDirection_Plus        = true;		//! Added by LHW (2013/3/26)
		}		
		//////////////////////////////////////////////////////////////////////////

		strResourceInfo.strMainTitleInfo.bShow				= true;
		strResourceInfo.strMainTitleInfo.eAlign				= E_GRAPH2D_TITLE_ALIGN_CENTER;		
		m_apGraphWnd[i]->SetResourceInfo(strResourceInfo);

		//! <------------------------------------------------------------
		//! X축 특정값 표시선 추가, X축에 수직선
		//! 추가되는 순서에 주의한다. 
		strValueLineXInfo strXLineInfo;

		strXLineInfo.InitInfo();
		strXLineInfo.bShow = false;
		strXLineInfo.dbValue = 0.;
		strXLineInfo.clrValue = RGB(255, 0, 0);
		strXLineInfo.iLineWidth = 1;
		strXLineInfo.szText.Format(_T("[%d] MTF(N/4)"), j + 1);
		m_apGraphWnd[i]->AddXValueLine(strXLineInfo);

		strXLineInfo.InitInfo();
		strXLineInfo.bShow = false;
		strXLineInfo.dbValue = 0.;
		strXLineInfo.clrValue = RGB(0, 0, 255);
		strXLineInfo.iLineWidth = 1;
		strXLineInfo.szText.Format(_T("[%d] MTF(N/8)"), j + 1);
		m_apGraphWnd[i]->AddXValueLine(strXLineInfo);

		strXLineInfo.InitInfo();
		strXLineInfo.bShow = false;
		strXLineInfo.dbValue = 0.;
		strXLineInfo.clrValue = RGB(255, 128, 0);
		strXLineInfo.iLineWidth = 1;
		strXLineInfo.szText.Format(_T("[%d] MTF50"), j + 1);
		m_apGraphWnd[i]->AddXValueLine(strXLineInfo);
		//! <------------------------------------------------------------

		//! 그래프의 X, Y축 이름을 설정
		m_apGraphWnd[i]->SetCaptionX(_T(""));
		m_apGraphWnd[i]->SetCaptionY(_T("MTF"), _T(""));

		m_apGraphWnd[i]->GetResourceInfo(strResourceInfo);
		strResourceInfo.strMainTitleInfo.szTitle = _T("SFR");
		m_apGraphWnd[i]->SetResourceInfo(strResourceInfo);

		//! 메시지를 받을 핸들 설정
		m_apGraphWnd[i]->m_hMsgHandle = this->m_hWnd;		
	}

	CRect rcGraph;

	/* Through Graph */
	iRet = GetWindowRect_FromUI(IDC_STATIC_PLOT1, this, rcGraph);	
	ScreenToClient(rcGraph);
	m_apGraphWnd[0]->MoveWindow(rcGraph);
	/* Fine Graph */
	iRet = GetWindowRect_FromUI(IDC_STATIC_PLOT3, this, rcGraph);
	ScreenToClient(rcGraph);
	m_apGraphWnd[1]->MoveWindow(rcGraph);
	/* SFR Graph */
	iRet = GetWindowRect_FromUI(IDC_STATIC_PLOT2, this, rcGraph);
	ScreenToClient(rcGraph);
	m_apGraphWnd[2]->MoveWindow(rcGraph);

	for ( i = 0; i < BUFFER_SIZE_GRAPH_2D; i++ )
	{
		m_apGraphWnd[i]->m_bChanged = true;
	}

	return true;
}

//! 그래프 컨트롤 해제
void CAutoDispDlg::ReleaseGraphWnd()
{
	int i = 0;
	for ( i = 0; i < BUFFER_SIZE_GRAPH_2D; i++ )
	{
		if ( m_apGraphWnd[i] != NULL )
		{
			m_apGraphWnd[i]->DestroyWindow();

			delete m_apGraphWnd[i];
			m_apGraphWnd[i] = NULL;
		}
	}
}

//! 그래프에 데이터를 입력한다. 
int CAutoDispDlg::DrawGraph(int iIndex_Plot)
{
	if ( iIndex_Plot < 0 || iIndex_Plot >= BUFFER_SIZE_GRAPH_2D)
	{
		return -1;
	}

	int j = 0;
	//	bool bRet = false;
	int iIndex_Line_X_MTF4 = 0;
	int iIndex_Line_X_MTF8 = 0;
	int iIndex_Line_X_MTF50 = 0;

	strGraph2D_Y_Axis_Info strAxisYInfo;	//! Y축
	strValueLineXInfo      strXLineInfo;	//! X축

	//! 1) 그래프에 데이터를 입력한다. 
	//! 2) 만약, 커서 (Mouse로 조작 가능한 그래프 데이터 표시 기능)가 없으면 추가한다. 
	//! 3) 그래프를 다시 그린다. 

	if ( m_apGraphWnd[iIndex_Plot] != NULL )
	{
		if ( iIndex_Plot == 0 )
		{
			for ( j = 0; j < BUFFER_SIZE_GRAPH_OVERLAP; j++ )
			{
				//! <-----------------------------------------------------------
				//! 그래프가 눈에 보이는 여부를 설정한다.
				m_apGraphWnd[iIndex_Plot]->GetResourceYInfo(strAxisYInfo, j);

				m_aiDataSize[iIndex_Plot][j] = Task.m_iCnt_Step_AA_Total;

				if ( m_aiDataSize[iIndex_Plot][j] <= 0 )
				{
					strAxisYInfo.bShowGraph = false;
				}
				else
				{
					strAxisYInfo.bShowGraph = m_abFlag_Visible[iIndex_Plot][j];
				}

				m_apGraphWnd[iIndex_Plot]->SetResourceYInfo(strAxisYInfo, j);

				int iIndex = 0;

				if ( Task.m_bFlag_Decrease_SFR == true )
				{
					iIndex = model.m_iCnt_Check_SFR;
				}

				for(int i_tmp=iIndex; i_tmp<m_aiDataSize[iIndex_Plot][j]; i_tmp++)
				{
#if (____AA_WAY == PCB_TILT_AA)
					m_adDataX[iIndex_Plot][j][i_tmp-iIndex] = Task.SFR.fMotorPos[i_tmp][theApp.MainDlg->TITLE_MOTOR_Z]*-1;
#elif (____AA_WAY == LENS_TILT_AA)
					m_adDataX[iIndex_Plot][j][i_tmp-iIndex] = Task.SFR.fMotorPos[i_tmp][theApp.MainDlg->TITLE_MOTOR_Z]; 
					//움직이는 Z축 값 부호에 따라 다르게 
#endif

					m_adDataY[iIndex_Plot][j][i_tmp-iIndex] = Task.SFR.fSfrN4[i_tmp][j];
				}

				//! 그래프에 데이터 입력
				//m_apGraphWnd[i]->SetPlotData(m_adDataX[i], m_adDataY[i], m_aiDataSize[i]);
				m_apGraphWnd[iIndex_Plot]->SetPlotData(m_adDataX[iIndex_Plot][j], m_adDataY[iIndex_Plot][j], m_aiDataSize[iIndex_Plot][j]-iIndex, j);

			}
			//! <-----------------------------------------------------------------------------------------------------------------------------------------
		}
		else if ( iIndex_Plot == 1)
		{
			for ( j = 0; j < BUFFER_SIZE_GRAPH_OVERLAP; j++ )
			{
				//! <-----------------------------------------------------------
				//! 그래프가 눈에 보이는 여부를 설정한다.
				m_apGraphWnd[iIndex_Plot]->GetResourceYInfo(strAxisYInfo, j);

				m_aiDataSize[iIndex_Plot][j] = Task.m_iCnt_Step_AA_Total - Task.m_iCnt_Second_AA_Start;

				if ( m_aiDataSize[iIndex_Plot][j] <= 0 )
				{
					strAxisYInfo.bShowGraph = false;
				}
				else
				{
					strAxisYInfo.bShowGraph = m_abFlag_Visible[iIndex_Plot][j];
				}

				m_apGraphWnd[iIndex_Plot]->SetResourceYInfo(strAxisYInfo,j);

				for(int i_tmp=0; i_tmp<m_aiDataSize[iIndex_Plot][j]; i_tmp++)
				{
#if (____AA_WAY == PCB_TILT_AA)
					m_adDataX[iIndex_Plot][j][i_tmp] = Task.SFR.fMotorPos[i_tmp+Task.m_iCnt_Second_AA_Start][theApp.MainDlg->TITLE_MOTOR_Z]*-1;
#elif (____AA_WAY == LENS_TILT_AA)	
					m_adDataX[iIndex_Plot][j][i_tmp] = Task.SFR.fMotorPos[i_tmp+Task.m_iCnt_Second_AA_Start][theApp.MainDlg->TITLE_MOTOR_Z];
#endif

					
					m_adDataY[iIndex_Plot][j][i_tmp] = Task.SFR.fSfrN4[i_tmp+Task.m_iCnt_Second_AA_Start][j];
//////////////////////////////////////////////////////////////////////////////////////////
				}

				m_apGraphWnd[iIndex_Plot]->SetPlotData(m_adDataX[iIndex_Plot][j], m_adDataY[iIndex_Plot][j], m_aiDataSize[iIndex_Plot][j], j);
			}
		}

		m_apGraphWnd[iIndex_Plot]->m_bChanged = true;
		m_apGraphWnd[iIndex_Plot]->Invalidate();
	}

	return 1;
}

void CAutoDispDlg::AddCursor_In_Graph()
{
	int i = 0;
	bool bRet = false;
	for ( i = 0; i < BUFFER_SIZE_GRAPH_2D; i++ )
	{
		if ( m_apGraphWnd[i]== NULL )
		{
			continue;
		}

		//! 커서가 없으면, 추가한다.
		if ( m_apGraphWnd[i]->GetCurrentCursorSize() <= 0 )
		{
			bRet = m_apGraphWnd[i]->AddCursorInDataIndex(0, false);
			m_apGraphWnd[i]->SetCursorValueVisible(0, false, false, false);
		}

		m_apGraphWnd[i]->m_bChanged = true;
		m_apGraphWnd[i]->Invalidate();
	}
}


void CAutoDispDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	ReleaseGraphWnd();
}


void CAutoDispDlg::dispCurTaskOnLabel(int iRtn, CString sLabel)
{
	COLORREF color;

	if ( iRtn > 0 )		color = GRID_COLOR_GREEN;
	else				color = M_COLOR_RED;

	m_label_Cur_Task
		.SetBkColor(color)
		.SetText(sLabel);

	m_label_Cur_Task.Invalidate();
}

BOOL CAutoDispDlg::DestroyWindow()
{
	vision.DeleteBuffer_AutoDisp();

	return CDialogEx::DestroyWindow();
}


void CAutoDispDlg::DispResultImage_Opt()
{
	double dFactorX, dFactorY;
	
	dFactorX	= (double)(m_iSizeX_Client)/(double)(gMIUDevice.nWidth);
	dFactorY	= (double)(m_iSizeY_Client)/(double)(gMIUDevice.nHeight);

	vision.GetBuffer_AutoDisp(0, dFactorX, dFactorY);

	MbufClear(vision.MilOptOverlayImage, vision.TransparentColor_Opt);

	CPoint OptCenterP;

	OptCenterP.x	= (int)(Task.dOpticalPosX * dFactorX + 0.5);
	OptCenterP.y	= (int)(Task.dOpticalPosY * dFactorY + 0.5);

	MgraColor(M_DEFAULT, M_COLOR_RED);
	MgraLine(M_DEFAULT, vision.MilOptOverlayImage, (OptCenterP.x-50), OptCenterP.y, (OptCenterP.x+50), OptCenterP.y);
	MgraLine(M_DEFAULT, vision.MilOptOverlayImage, OptCenterP.x, (OptCenterP.y-50), OptCenterP.x, (OptCenterP.y+50));

	MgraColor(M_DEFAULT, M_COLOR_BLUE);
	MgraLine(M_DEFAULT, vision.MilOptOverlayImage, 0, m_iSizeY_Client/2, m_iSizeX_Client, m_iSizeY_Client/2);
	MgraLine(M_DEFAULT, vision.MilOptOverlayImage, m_iSizeX_Client/2, 0, m_iSizeX_Client/2, m_iSizeY_Client);

	CString sTemp;
	sTemp.Format("X : %.03f mm", Task.dOpticalShiftX);
	MgraColor(M_DEFAULT, M_COLOR_MAGENTA);
	MgraText(M_DEFAULT, vision.MilOptOverlayImage, 10, 10, sTemp.GetBuffer());
	sTemp.Format("Y : %.03f mm", Task.dOpticalShiftY);
	MgraText(M_DEFAULT, vision.MilOptOverlayImage, 10, 30, sTemp.GetBuffer());
}


void CAutoDispDlg::DispResultImage_Defect()
{
	double dFactorX, dFactorY;

	dFactorX	= (double)(m_iSizeX_Client)/(double)(gMIUDevice.nWidth);
	dFactorY	= (double)(m_iSizeY_Client)/(double)(gMIUDevice.nHeight);

	vision.GetBuffer_AutoDisp(1, dFactorX, dFactorY);

	MbufClear(vision.MilDefectOverlayImage, vision.TransparentColor_Defect);

	CRect rcReduceBox;

	MgraColor(M_DEFAULT, M_COLOR_RED);
	for (int i=0 ; i<Task.iCnt_Total_Defect ; i++)
	{
		rcReduceBox.left		= (int)(Task.defect.rect[i].left	* dFactorX + 0.5);
		rcReduceBox.top			= (int)(Task.defect.rect[i].top		* dFactorY + 0.5);
		rcReduceBox.right		= (int)(Task.defect.rect[i].right	* dFactorX + 0.5);
		rcReduceBox.bottom		= (int)(Task.defect.rect[i].bottom	* dFactorY + 0.5);

		if(rcReduceBox.top == rcReduceBox.bottom)
			rcReduceBox.bottom++;

		if(rcReduceBox.left == rcReduceBox.right)
			rcReduceBox.right++;

		MgraRect(M_DEFAULT, vision.MilDefectOverlayImage, rcReduceBox.left, rcReduceBox.top, rcReduceBox.right, rcReduceBox.bottom);
	}
}


void CAutoDispDlg::DrawBarGraph()
{
	CString sTemp;
	int i = 0;
	int j = 0;
	HWND hWnd = GetDlgItem(IDC_STATIC_PLOT4)->m_hWnd;
	CDC pDC;
	HDC hDC = ::GetDC(hWnd);

	pDC.Attach(hDC);

	CRect rcClient;
	GetDlgItem(IDC_STATIC_PLOT4)->GetClientRect(rcClient);

	CBrush Brush;
	CBrush* pOldBrush;
	Brush.CreateSolidBrush(RGB(255,255,255));
	pOldBrush = pDC.SelectObject(&Brush);

	pDC.FillRect(rcClient, &Brush);

	int iSizeX_Client = rcClient.right - rcClient.left;
	int iSizeY_Client = rcClient.bottom - rcClient.top;
	int iOffsetY = 20;

	CPen* pOldPen;
	CPen pen_LineBase;
	CPen pen_LineVertical;
	CPen pen_LineLimitCen;
	CPen pen_LineLimitSide;

	CFont font_LimitVal;
	CFont font_BarName;
	CFont* pOldFont;

	pen_LineBase.CreatePen(PS_SOLID, 1, RGB(0,0,0));
	pen_LineVertical.CreatePen(PS_DOT, 1, RGB(0,0,0));
	pen_LineLimitCen.CreatePen(PS_SOLID, 1, RGB(128,0,0));
	pen_LineLimitSide.CreatePen(PS_SOLID, 1, RGB(128,0,128));


	pOldPen = pDC.SelectObject(&pen_LineBase);

	pDC.MoveTo(5, iSizeY_Client - iOffsetY);
	pDC.LineTo(iSizeX_Client - 5, iSizeY_Client - iOffsetY);

	pOldPen = pDC.SelectObject(&pen_LineVertical);

	pDC.MoveTo(5, 0);
	pDC.LineTo(iSizeX_Client - 5, 0);

	pDC.MoveTo(5, (iSizeY_Client - iOffsetY) / 4 * 1);
	pDC.LineTo(iSizeX_Client - 5, (iSizeY_Client - iOffsetY) / 4 * 1);

	pDC.MoveTo(5, (iSizeY_Client - iOffsetY) / 4 * 2);
	pDC.LineTo(iSizeX_Client - 5, (iSizeY_Client - iOffsetY) / 4 * 2);

	pDC.MoveTo(5, (iSizeY_Client - iOffsetY) / 4 * 3);
	pDC.LineTo(iSizeX_Client - 5, (iSizeY_Client - iOffsetY) / 4 * 3);

	font_LimitVal.CreateFont(10,6,0,0,0,0,0,0,DEFAULT_CHARSET,0,0,0,0,"Airal");
	pOldFont = pDC.SelectObject(&font_LimitVal);
	/*
	pOldPen = pDC.SelectObject(&pen_LineLimitCen);
	pDC.MoveTo(5, (iSizeY_Client-iOffsetY) - (int)(sysData.dLimit_SFR_Cen * (iSizeY_Client-iOffsetY)+0.5));
	pDC.LineTo(iSizeX_Client - 5, (iSizeY_Client-iOffsetY) - (int)(sysData.dLimit_SFR_Cen * (iSizeY_Client-iOffsetY)+0.5));
	sTemp.Format("%.2lf", sysData.dLimit_SFR_Cen);
	pDC.SetTextColor(RGB(128,0,0));
	pDC.TextOut(iSizeX_Client - 30, (iSizeY_Client-iOffsetY) - (int)(sysData.dLimit_SFR_Cen * (iSizeY_Client-iOffsetY)+0.5) - 12, sTemp);

	pOldPen = pDC.SelectObject(&pen_LineLimitSide);
	pDC.MoveTo(5, (iSizeY_Client-iOffsetY) - (int)(sysData.dLimit_SFR_Side * (iSizeY_Client-iOffsetY)+0.5));
	pDC.LineTo(iSizeX_Client - 5, (iSizeY_Client-iOffsetY) - (int)(sysData.dLimit_SFR_Side * (iSizeY_Client-iOffsetY)+0.5));
	sTemp.Format("%.2lf", sysData.dLimit_SFR_Side);
	pDC.SetTextColor(RGB(128,0,128));
	pDC.TextOut(iSizeX_Client - 30, (iSizeY_Client-iOffsetY) - (int)(sysData.dLimit_SFR_Side * (iSizeY_Client-iOffsetY)+0.5) - 12, sTemp);
	*/
	CPen pen_Cen, pen_LeftUpper, pen_RightUpper, pen_LeftLower, pen_RightLower;
	pen_Cen.CreatePen(PS_SOLID, 4, RGB(0,0,255));
	pen_LeftUpper.CreatePen(PS_SOLID, 4, RGB(255,0,0));
	pen_RightUpper.CreatePen(PS_SOLID, 4, RGB(0,255,0));
	pen_LeftLower.CreatePen(PS_SOLID, 4, RGB(63,0,153));
	pen_RightLower.CreatePen(PS_SOLID, 4, RGB(0,216,255));

	font_BarName.CreateFont(12,7,0,0,0,0,0,0,DEFAULT_CHARSET,0,0,0,0,"Arial");
	pOldFont = pDC.SelectObject(&font_BarName);
	pDC.SetTextColor(RGB(0,0,0));
	double MtfSfr[5];
	int mCount = 0;
	int mRoiIndex = 0;
	int mTotalCount = 0;
	double mTempMtf = 0.0;
	
	for (i = 0; i < model.mGlobalChartCount; i++)
	{
		mCount = 0;
		mTempMtf = 0.0;
		if (model.sfrElem.m_AATiltRoiIndex[mRoiIndex] == i)
		{
				
			for (j = 0; j < 4; j++)
			{
				if (model.sfrElem.m_SfrTestUse[i][j] == 1)
				{
					if (sysData.m_iProductComp == 1)
					{
						mTempMtf += MandoInspLog.dMTF_PostUV[mTotalCount];
					}
					else
					{
						if (Task.PCBTask == 65000 || Task.PCBTask == 60200)
						{
							mTempMtf += MandoInspLog.dMTF_PreUV[mTotalCount];
						}
						else
						{
							mTempMtf += MandoInspLog.dMTF_PostUV[mTotalCount];
						}
					}
						
					mCount++;
					mTotalCount++;
				}
			}
			MtfSfr[mRoiIndex] = mTempMtf / mCount;
			mRoiIndex++;
		}
		else
		{
			for (j = 0; j < 4; j++)
			{
				if (model.sfrElem.m_SfrTestUse[i][j] == 1)
				{
					mTotalCount++;
				}
			}
		}
	}

	
	for (int i=0 ; i<MAX_MTF_NO ; i++)
	{
		if ( i == 0 )		pOldPen = pDC.SelectObject(&pen_Cen);
		else if ( i == 1 )	pOldPen = pDC.SelectObject(&pen_LeftUpper);
		else if ( i == 2 )	pOldPen = pDC.SelectObject(&pen_RightUpper);
		else if ( i == 3 )	pOldPen = pDC.SelectObject(&pen_LeftLower);
		else if ( i == 4 )	pOldPen = pDC.SelectObject(&pen_RightLower);

		pDC.MoveTo((iSizeX_Client-5)/6*(i+1), iSizeY_Client - iOffsetY);

//////////////////////////////////////////////////////////////////////////////////////////
		if(sysData.m_iProductComp == 1) 
		{
			//MandoInspLog.dMTF_PostUV

			pDC.LineTo((iSizeX_Client-5)/6*(i+1), (iSizeY_Client - iOffsetY) - (int)(MtfSfr[i] * (iSizeY_Client - iOffsetY)+0.5));
			sTemp.Format("%.3lf", MtfSfr[i]);
			pDC.TextOut((iSizeX_Client-5)/6*(i+1)-15, (iSizeY_Client - iOffsetY) - (int)(MtfSfr[i] * (iSizeY_Client - iOffsetY)+0.5) - 10, sTemp);
		}else
		{
			//pDC.LineTo((iSizeX_Client-5)/6*(i+1), (iSizeY_Client - iOffsetY) - (int)(Task.SFR.fSfrN4[Task.m_iDrawBarStep-1][i] * (iSizeY_Client - iOffsetY)+0.5));
			pDC.LineTo((iSizeX_Client - 5) / 6 * (i + 1), (iSizeY_Client - iOffsetY) - (int)(MtfSfr[i] * (iSizeY_Client - iOffsetY) + 0.5));
			//sTemp.Format("%.3lf", Task.SFR.fSfrN4[Task.m_iDrawBarStep-1][i]);
			sTemp.Format("%.3lf", MtfSfr[i]);
			pDC.TextOut((iSizeX_Client-5)/6*(i+1)-15, (iSizeY_Client - iOffsetY) - (int)(MtfSfr[i] * (iSizeY_Client - iOffsetY)+0.5) - 10, sTemp);
		}
		
//////////////////////////////////////////////////////////////////////////////////////////
	}

	
	
	
	pDC.SetTextColor(RGB(0, 0, 255));
	pDC.TextOut((iSizeX_Client - 5) / 6 - 13, (iSizeY_Client - iOffsetY) + 5, "CEN");
	pDC.SetTextColor(RGB(255, 0, 0));
	if (model.mGlobalChartType == 0)
	{
		//X자형
		pDC.TextOut((iSizeX_Client - 5) / 6 * 2 - 10, (iSizeY_Client - iOffsetY) + 5, "TL");
		pDC.SetTextColor(RGB(0, 255, 0));
		pDC.TextOut((iSizeX_Client - 5) / 6 * 3 - 10, (iSizeY_Client - iOffsetY) + 5, "TR");
		pDC.SetTextColor(RGB(63, 0, 153));
		pDC.TextOut((iSizeX_Client - 5) / 6 * 4 - 10, (iSizeY_Client - iOffsetY) + 5, "BL");
		pDC.SetTextColor(RGB(0, 216, 255));
		pDC.TextOut((iSizeX_Client - 5) / 6 * 5 - 10, (iSizeY_Client - iOffsetY) + 5, "BR");
	}
	else
	{
		pDC.TextOut((iSizeX_Client - 5) / 6 * 2 - 10, (iSizeY_Client - iOffsetY) + 5, "T");
		pDC.SetTextColor(RGB(0, 255, 0));
		pDC.TextOut((iSizeX_Client - 5) / 6 * 3 - 10, (iSizeY_Client - iOffsetY) + 5, "B");
		pDC.SetTextColor(RGB(63, 0, 153));
		pDC.TextOut((iSizeX_Client - 5) / 6 * 4 - 10, (iSizeY_Client - iOffsetY) + 5, "L");
		pDC.SetTextColor(RGB(0, 216, 255));
		pDC.TextOut((iSizeX_Client - 5) / 6 * 5 - 10, (iSizeY_Client - iOffsetY) + 5, "R");
	}
	



	pDC.SelectObject(pOldPen);
	pen_LineBase.DeleteObject();
	pen_LineVertical.DeleteObject();
	pen_LineLimitCen.DeleteObject();
	pen_LineLimitSide.DeleteObject();

	pen_Cen.DeleteObject();
	pen_LeftUpper.DeleteObject();
	pen_RightUpper.DeleteObject();
	pen_LeftLower.DeleteObject();
	pen_RightLower.DeleteObject();

	pDC.SelectObject(pOldBrush);
	Brush.DeleteObject();

	pDC.SelectObject(pOldFont);
	font_LimitVal.DeleteObject();
	font_BarName.DeleteObject();

	pDC.Detach();
	::ReleaseDC(hWnd, hDC);
	sTemp.Empty();
}

void CAutoDispDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	DrawBarGraph();
}
