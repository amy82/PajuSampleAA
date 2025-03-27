// TimeFFTWnd.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include <stdlib.h>		//! __max, __min 때문에 필요
#include <math.h>
#include <float.h>
#include <afxpriv.h>	//! CPreviewDC 때문에 필요
#include ".\\Graph2DWnd.h"

#include ".\\Graph2D_Data.h"
#include ".\graph2dwnd.h"


// CGraph2DWnd

IMPLEMENT_DYNAMIC(CGraph2DWnd, CWnd)
CGraph2DWnd::CGraph2DWnd()
{
	m_iPlotIndex = -1;
	m_bChanged = false;
	m_bCreateDC = false;
	m_bMultiPlotOneAxis = false;
	m_bCursorEventMsg = false;
	m_bAutoDrawCompleteMsg = false;	//! Added by LHW [2008/7/01]
	m_bZoomEventMsg = false;		//! Added by LHW [2008/4/19], 초기값 변경 Modify by LHW [2009/2/2]
	m_bDataPointEventMsg = false;	//! Added by LHW [2008/5/23]
	m_bAxisYEventMsg = false;		//! Added by LHW [2008/7/31]
	m_bTimeAxisXEventMsg = false;	//! Added by LHW [2008/8/18]
	m_bRegionCursorEventMsg = false;//! Added by LHW [2008/11/28]
	m_bXAutoRangeShowGraph = true;
	m_bYAutoRangeShowGraph = true;
	m_bYAutoRangeValueLine = false;
	m_bXValueLineRMouseDownChk = false;		//! Added by LHW [2008/4/19]
	m_bChildCursorRMouseDownChk = false;	//! Added by LHW [2008/6/13]
	m_bAuxCursorRMouseDownChk = false;		//! Added by LHW [2008/8/5]
	m_bRegionCursorRMouseDownChk = false;	//! Added by LHW [2008/11/28]
	m_bSelfCreateResourcePtr = false;
	m_pPlotResource = NULL;
	m_arrYMapper.RemoveAll();
	m_arrYMapper.FreeExtra();
	m_arrResourceY.RemoveAll();
	m_arrResourceY.FreeExtra();
	m_arrValueLineY.RemoveAll();	//! Added by LHW [2008/3/29]
	m_arrValueLineY.FreeExtra();	//! Added by LHW [2008/3/29]
	m_arrPlotData.RemoveAll();
	m_arrPlotData.FreeExtra();
	m_arrGraphEquation.RemoveAll();	//! Added by LHW [2008/8/22]
	m_arrGraphEquation.FreeExtra();	//! Added by LHW [2008/8/22]	
	m_bDrawing = false;
	m_bCalcCursor = false;
	m_bCalcChildCursor = false;		//! Added by LHW [2008/6/13]
	m_bCalcAuxCursor = false;		//! Added by LHW [2008/8/4]
	m_hMsgHandle = NULL;
	m_CurRect.SetRectEmpty();
	m_DataRect.SetRectEmpty();
	m_graphRect.SetRectEmpty();
	m_RealGraphRect.SetRectEmpty();
	m_crZoomArea.SetRectEmpty();
	m_MainTitleRect.SetRectEmpty();
	m_SubTitleRect.SetRectEmpty();
	m_crAxisY_Left_Event.SetRectEmpty();	//! Added by LHW [2008/7/31], Modify by LHW [2009/2/2]
	m_crAxisY_Right_Event.SetRectEmpty();	//! Added by LHW [2008/7/31], Modify by LHW [2009/2/2]
	m_AxisCaptionRect.SetRectEmpty();		//! Added by LHW [2008/8/01]
	m_crAxisX_Event.SetRectEmpty();			//! Added by LHW [2009/2/2]		
	m_ptSave.x = 0;
	m_ptSave.y = 0;
	m_iCursorMargin = 2;
	m_iRealGraphHeight = 0;
	m_eMouseOperationMode = E_GRAPH2D_CURSOR_XY;
	m_eCursorSearchMode = E_GRAPH2D_CURSOR_SEARCH_X_RANGE;
	m_eCursorLineMode = E_GRAPH2D_CURSOR_LINE_XY;
	m_bZoomMouseDown = false;
	m_bPanMouseDown = false;
	m_strPanPosition.InitInfo();
	m_iPanOffsetX = 0;
	m_iPanOffsetY = 0;	
	m_bDrawCompleteMsg = false;			//! Added by LHW [2008/5/31]
	m_bSelectedCursorLine = true;		//! Added by LHW [2008/5/14]
	m_bSelectedChildCursorLine = true;	//! Added by LHW [2008/6/16]
	m_bSelectedRegionCursorLine = true;	//! Added by LHW [2008/11/28]
	m_bCursorOverlap = true;			//! Added by LHW [2008/5/15]
	m_eCursorAllSearchMode = E_GRAPH2D_CURSOR_ALL_SEARCH_SELECT;	//! Added by LHW [2008/7/24]
	m_bCursorSelected = false;
	m_bCursorInfoSelected = false;
	m_iSelectCursorIndex = 0;
	m_iSelectedCursorIndex = 0;
	m_bAuxCursorSelected = false;		//! Added by LHW [2008/8/4]
	m_hCursor_Horz = AfxGetApp()->LoadStandardCursor(IDC_SIZEWE);
	m_hCursor_Vert = AfxGetApp()->LoadStandardCursor(IDC_SIZENS);
	m_hCursor_Move = AfxGetApp()->LoadStandardCursor(IDC_SIZEALL);
	m_hCursor_Pan_DOWN = NULL;
	m_hCursor_Pan_UP = NULL;
	m_hCursor_DataPoint_Event = NULL;		//! Added by LHW [2008/5/28]
	m_hCursor_Zoom_X = NULL;				//! Added by LHW [2009/2/2]
	m_hCursor_Zoom_Y = NULL;				//! Added by LHW [2009/2/2]
	m_hCursor_Zoom_XY = NULL;				//! Added by LHW [2009/2/2]
	m_hCursor_Pan_X = NULL;					//! Added by LHW [2009/2/2]
	m_hCursor_Pan_Y = NULL;					//! Added by LHW [2009/2/2]
	m_bDataPointCusor = false;				//! Added by LHW [2008/5/28]
	m_bDataPointSearchProcessing = false;	//! Added by LHW [2008/9/19]
	m_bDataPointSearchComplete = false;		//! Added by LHW [2008/5/28]
	m_bLeftMouseDown = false;				//! Added by LHW [2008/5/28]
	m_bRightMouseDown = false;				//! Added by LHW [2009/2/2]
	m_bMouseMoved = false;					//! Added by LHW [2009/2/2]
	m_bAxisEventFront = false;				//! Added by LHW [2009/2/2]
	m_arrCursor.RemoveAll();
	m_arrCursor.FreeExtra();
	m_arrChildCursor.RemoveAll();		//! Added by LHW [2008/6/13]
	m_arrChildCursor.FreeExtra();		//! Added by LHW [2008/6/13]
	m_arrRegionCursor.RemoveAll();		//! Added by LHW [2008/11/28]
	m_arrRegionCursor.FreeExtra();		//! Added by LHW [2008/11/28]
	m_iSelectChildCursorIndex = 0;		//! Added by LHW [2008/6/13]
	m_iSelectedChildCursorIndex = 0;	//! Added by LHW [2008/6/14]
	m_iSelectRegionCursorIndex = 0;		//! Added by LHW [2008/11/28]
	m_iSelectedRegionCursorIndex = 0;	//! Added by LHW [2008/11/28]
	m_iSelectRegionCursorLineIndex = 0;	//! Added by LHW [2008/11/30]
	m_bRegionCursorSelected = false;	//! Added by LHW [2008/11/28]
	m_bChildCursorSelected = false;		//! Added by LHW [2008/6/13]
	m_bChildCursorInfoSelected = false;	//! Added by LHW [2008/6/13]
	m_bChildCursorOverlap = false;		//! Added by LHW [2008/6/13], Modify by LHW [2008/8/20] : 초기값 false로 변경
	m_iChildCursorMargin = 2;			//! Added by LHW [2008/6/13]
	m_iRegionCursorMargin = 2;			//! Added by LHW [2008/11/30]
	m_iTopOverlapIndex = -1;			//! Added by LHW [2008/7/24]
	m_iShowGridY_OverlapIndex = 0;		//! Added by LHW [2008/7/30]
	m_iGridMarginX = 3;					//! Added by LHW [2008/7/24]
	m_iGridMarginY = 2;					//! Added by LHW [2008/7/24]
	m_bCloseCursorSelect = false;		//! Added by LHW [2008/7/24]
	m_bMouseMoveProcessing = false;		//! Added by LHW [2008/7/24]
	m_iSelectAuxCursorGroupIndex = 0;	//! Added by LHW [2008/8/4]
	m_iSelectedAuxCursorGroupIndex = 0;	//! Added by LHW [2008/8/4]
	m_iSelectAuxCursorIndex = 0;		//! Added by LHW [2008/8/4]
	m_iSelectedAuxCursorIndex = 0;		//! Added by LHW [2008/8/4]
	m_bXAutoRangeEquation = false;		//! Added by LHW [2008/8/25]
	m_bYAutoRangeEquation = false;		//! Added by LHW [2008/8/25]
	m_iAxisCaptionMarginX = 2;			//! Added by LHW [2008/11/28]
	m_bXAutoRangeRegionCursor = false;	//! Added by LHW [2008/12/14]
	m_bYAutoRangeRegionCursor = false;	//! Added by LHW [2008/12/14]
	m_bXScaleLock = false;				//! Added by LHW [2008/12/27]
	m_bYScaleLock = false;				//! Added by LHW [2008/12/27]
	m_bAxisXZoom = false;		//! Added by LHW [2009/2/2]
	m_bAxisYzoom = false;		//! Added by LHW [2009/2/2]
	m_bAxisXYZoom = false;		//! Added by LHW [2009/2/2]
	m_bAxisXPan = false;		//! Added by LHW [2009/2/2]
	m_bAxisYPan = false;		//! Added by LHW [2009/2/2]
	m_bAxisXYPan = false;		//! Added by LHW [2009/2/2]
	m_bTemporaryMouseOperation = false;	//! Added by LHW [2009/2/2]
	m_bSysmbolOnceDraw = true;	//! Added by LHW [2009/2/19]
	m_bDrawBackGroundImage = false;	//! Added by LHW [2009/2/25]
	m_bAlwaysInitYPos = true;	//! Added by LHW [2009/2/27]
	m_bCursorUpDownSearchOperation = false;	//! Added by LHW [2009/3/1]
	m_iCursorUpDownSearchMargin = 10;		//! Added by LHW [2009/3/1]

	m_eSelectCursorType = E_GRAPH2D_MOVE_MAIN_CURSOR_TYPE;	//! Added by LHW [2008/6/16]

	MakePlotBuffer(1);
}

CGraph2DWnd::~CGraph2DWnd()
{
	m_DrawRgn.DeleteObject();

	RemoveAllPlotBuffer();

	RemoveAllXValueLine();		//! Added by LHW [2008/4/19]
	RemoveAllYValueLine();		//! Added by LHW [2008/3/29]
	RemoveAllAuxCursor();		//! Added by LHW [2008/4/1]
	RemoveAllChildCursor();		//! Added by LHW [2008/6/13]
	RemoveAllGraphEquation();	//! Added by LHW [2008/8/23]
	RemoveAllRegionCursor();	//! Added by LHW [2008/11/28]
	
	m_arrCursor.RemoveAll();
	m_arrCursor.FreeExtra();

	ReleaseResourcePtr();

	//! Added by LHW [2008/7/4]
	if(m_DrawDC.GetSafeHdc() || m_DrawBitmap.GetSafeHandle())
	{
		m_DrawDC.DeleteDC();
		m_DrawBitmap.DeleteObject();		
	}
}


BEGIN_MESSAGE_MAP(CGraph2DWnd, CWnd)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()



// CGraph2DWnd 메시지 처리기입니다.


void CGraph2DWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	//! Modify by LHW [2008/10/25] : 화면 크기가 바뀌면 Y축의 X좌표를 초기화
	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize > 0 )
	{
		for ( int i = 0; i < iGraphSize; i++ )
		{
			m_arrResourceY.GetAt(i)->m_iLeftXPtofYAxis = 0;
			m_arrResourceY.GetAt(i)->m_iRightXPtofYAxis = 0;
		}
	}

	m_bChanged = true;
	Invalidate();
}

void CGraph2DWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CWnd::OnPaint()을(를) 호출하지 마십시오.

	if ( m_bDrawing == true )
	{
		return;
	}

	m_bDrawing = true;

	CDC *pDC = GetDC();
	CRect crClient;
	GetClientRect(&crClient);
	Display(pDC, crClient, false);
	ReleaseDC(pDC);

	if ( m_bDrawCompleteMsg == true )
	{
		if ( m_hMsgHandle != NULL )
		{
			::SendMessage(m_hMsgHandle, WM_GRAPH2D_DRAW_COMPLETE, 0, 0);
		}
		m_bDrawCompleteMsg = false;
	}

	m_bMouseMoveProcessing = false;	//! Added by LHW [2008/7/24]
	m_bDrawing = false;
}

//! Modify by LHW [2008/4/10] : 소스 정리
//! Modify by LHW [2008/4/28] : crInfo.top관련 수정
//! Modify by LHW [2008/5/28] : m_bLeftMouseDown 추가
//! Modify by LHW [2008/6/13] : 자식 커서 관련 부분 추가
//! Modify by LHW [2008/6/14] : m_iSelectedChildCursorIndex 추가
//! Modify by LHW [2008/6/15] : SetFlag_If_CursorMoved 추가
//! Modify by LHW [2008/6/16] : bChildCursorSelected 관련 오류 수정, m_eSelectCursorType 추가
//! Modify by LHW [2008/7/24] : m_bCloseCursorSelect 추가
//! Modify by LHW [2008/7/31] : m_AxisLeftRect, m_AxisRightRect 부분 추가
//! Modify by LHW [2008/8/4, 2008/8/5] : 보조 커서 마우스 이벤트 처리 추가
//! Modify by LHW [2008/8/20] : Y축 커서 이벤트 받는 부분 수정
//! Modify by LHW [2008/10/25] : E_GRAPH2D_ZOOM_Y 추가
//! Modify by LHW [2008/11/28] : 영역 표시 커서 관련 추가
//! Modify by LHW [2008/12/1] : 영역 표시 커서 선에 둘러싸인 사각 영역 이벤트 추가
//! Modify by LHW [2008/12/27] : 영역 표시 커서에서 m_bYScaleLock 추가
//! Modify by LHW [2009/1/6] : m_ptMouseDownPos 추가
//! Modify by LHW [2009/2/2] : m_AxisLeftRect, m_AxisRightRect를 m_crAxisY_Left_Event, m_crAxisY_Right_Event로 변경
//!							   키보드로 Alt, Shift 키를 눌렀을 때, 확대, 축소, Pan 동작 기능 추가, m_bMouseMoved 추가
//! Modify by LHW [2009/2/14] : 오른쪽 Alt 키 추가
void CGraph2DWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	m_bMouseMoved = false;
	m_bAxisEventFront = false;
	m_bTemporaryMouseOperation = false;
    
	if ( m_bAxisXZoom == true || m_bAxisYzoom == true || m_bAxisXYZoom == true || m_bAxisXPan == true || m_bAxisYPan == true || m_bAxisXYPan == true )
	{
		if ( m_eMouseOperationMode == E_GRAPH2D_CURSOR_XY )
		{
			if ( GetKeyState(VK_LMENU) < 0 || GetKeyState(VK_RMENU) < 0 )	//! Alt 키
			{
				if ( m_bAxisXYZoom == true )
				{
					if ( m_DataRect.PtInRect(point) )
					{
						m_eMouseOperationMode = E_GRAPH2D_ZOOM_XY;
						m_bTemporaryMouseOperation = true;
					}
				}
				if ( m_bTemporaryMouseOperation == false && m_bAxisXZoom == true )
				{
					if ( m_crAxisX_Event.PtInRect(point) )
					{
						m_eMouseOperationMode = E_GRAPH2D_ZOOM_X;
						m_bTemporaryMouseOperation = true;

						int iChkWidth = (int)(((double)(m_crAxisX_Event.Width())) / 2.);
						if ( (m_crAxisX_Event.left + iChkWidth) >= point.x )
						{
							m_bAxisEventFront = true;
						}
					}
				}
				if ( m_bTemporaryMouseOperation == false && m_bAxisYzoom == true )
				{
					if ( m_crAxisY_Left_Event.PtInRect(point) || m_crAxisY_Right_Event.PtInRect(point) )
					{
						m_eMouseOperationMode = E_GRAPH2D_ZOOM_Y;
						m_bTemporaryMouseOperation = true;

						int iChkHeight = 0;
						if ( m_crAxisY_Left_Event.Height() > 0 )
						{
							iChkHeight = (int)(((double)(m_crAxisY_Left_Event.Height())) / 2.);
							if ( (m_crAxisY_Left_Event.top + iChkHeight) >= point.y )
							{
								m_bAxisEventFront = true;
							}
						}
						else if ( m_crAxisY_Right_Event.Height() > 0 )
						{
							iChkHeight = (int)(((double)(m_crAxisY_Right_Event.Height())) / 2.);
							if ( (m_crAxisY_Right_Event.top + iChkHeight) >= point.y )
							{
								m_bAxisEventFront = true;
							}
						}						
					}
				}
			}
			else if ( GetKeyState(VK_LSHIFT) < 0 || GetKeyState(VK_RSHIFT) < 0 )	//! Shift 키
			{
				if ( m_bAxisXYPan == true )
				{
					if ( m_DataRect.PtInRect(point) )
					{
						m_eMouseOperationMode = E_GRAPH2D_PAN_XY;
						m_bTemporaryMouseOperation = true;
					}
				}
				if ( m_bTemporaryMouseOperation == false && m_bAxisXPan == true )
				{
					if ( m_crAxisX_Event.PtInRect(point) )
					{
						m_eMouseOperationMode = E_GRAPH2D_PAN_X;
						m_bTemporaryMouseOperation = true;

						int iChkWidth = (int)(((double)(m_crAxisX_Event.Width())) / 2.);
						if ( (m_crAxisX_Event.left + iChkWidth) >= point.x )
						{
							m_bAxisEventFront = true;
						}
					}
				}
				if ( m_bTemporaryMouseOperation == false && m_bAxisYPan == true )
				{
					if ( m_crAxisY_Left_Event.PtInRect(point) || m_crAxisY_Right_Event.PtInRect(point) )
					{
						m_eMouseOperationMode = E_GRAPH2D_PAN_Y;
						m_bTemporaryMouseOperation = true;

						int iChkHeight = 0;
						if ( m_crAxisY_Left_Event.Height() > 0 )
						{
							iChkHeight = (int)(((double)(m_crAxisY_Left_Event.Height())) / 2.);
							if ( (m_crAxisY_Left_Event.top + iChkHeight) >= point.y )
							{
								m_bAxisEventFront = true;
							}
						}
						else if ( m_crAxisY_Right_Event.Height() > 0 )
						{
							iChkHeight = (int)(((double)(m_crAxisY_Right_Event.Height())) / 2.);
							if ( (m_crAxisY_Right_Event.top + iChkHeight) >= point.y )
							{
								m_bAxisEventFront = true;
							}
						}
					}
				}
			}
		}
	}

	if ( m_bTemporaryMouseOperation == false )
	{
		if ( m_bAxisYEventMsg == true )
		{
			if ( m_crAxisY_Left_Event.PtInRect(point) || m_crAxisY_Right_Event.PtInRect(point) )
			{
				return;
			}
		}
	}

	SetCapture();

	if ( GetPlotBufferSize() > 0 && m_bDrawing == false && m_bCalcCursor == false && m_bCalcChildCursor == false )
	{
		switch(m_eMouseOperationMode)
		{
		case E_GRAPH2D_CURSOR_XY:
			{
				if ( GetRealVisualDataSize(true) > 0 )	//! 데이터가 출력되어 있을 경우에만 다음 과정 진행
				{
					int iCursorOperationFlag = 0;	//! 커서 선택 종류
													//! 0 : 초기값, 1 : 그래프가 여러 개일 경우 모든 그래프로 커서 이동 가능
													//! 2 : 현재 그래프를 따라 커서 이동 가능, 3 : 커서 정보창 이동 가능

					int i = 0, j = 0;
					bool bChildCursorSelected = false, bAuxCursorSelected = false, bRegionCursorSelected = false;;

					//! 자식 커서가 있으면 마우스 이벤트가 발생했는지 확인
					int iChildCursorSize = (int)(m_arrChildCursor.GetSize());
					if ( iChildCursorSize > 0 )
					{
						int iSelectChildCursorIndex = -1;
						for ( i = 0; i < iChildCursorSize; i++ )
						{
							if ( m_arrChildCursor.GetAt(i)->m_crSelectX.PtInRect(point) && m_arrChildCursor.GetAt(i)->m_crSelectY.PtInRect(point) )
							{
								//! 자식 커서 점을 선택했을 때

								iSelectChildCursorIndex = i;
								iCursorOperationFlag = 1;
								break;
							}
							if ( m_arrChildCursor.GetAt(i)->m_crSelectX.PtInRect(point) || 
								(m_arrChildCursor.GetAt(i)->m_strCursorInfo.eLineMode == E_GRAPH2D_CHILD_CURSOR_LINE_XY && m_arrChildCursor.GetAt(i)->m_crSelectY.PtInRect(point)) )
							{
								//! 자식 커서 선을 선택했을 때

								iSelectChildCursorIndex = i;
								iCursorOperationFlag = 2;
								break;
							}
							if ( m_arrChildCursor.GetAt(i)->m_crInfo.PtInRect(point) )
							{
								//! 자식 커서 정보창을 선택했을 때

								iSelectChildCursorIndex = i;
								iCursorOperationFlag = 3;
								break;
							}
						}
						if ( iSelectChildCursorIndex >= 0 && iSelectChildCursorIndex < iChildCursorSize )
						{
							m_iSelectChildCursorIndex = iSelectChildCursorIndex;
							m_iSelectedChildCursorIndex = iSelectChildCursorIndex;
							bChildCursorSelected = true;
							m_eSelectCursorType = E_GRAPH2D_MOVE_CHILD_CURSOR_TYPE;

							if ( iCursorOperationFlag > 0 )
							{
								switch(iCursorOperationFlag)
								{
								case 1:
									{
										m_bChildCursorOverlap = true;
										m_bChildCursorSelected = true;
										m_bChildCursorInfoSelected = false;
									}
									break;
								case 2:
									{
										m_bChildCursorOverlap = false;
										m_bChildCursorSelected = true;
										m_bChildCursorInfoSelected = false;
									}
									break;
								case 3:
									{
										m_bChildCursorOverlap = false;
										m_bChildCursorSelected = false;
										m_bChildCursorInfoSelected = true;
									}
									break;
								}
							}
						}
					}

					//! 자식 커서에 마우스 이벤트가 없고, 보조 커서가 있으면 마우스 이벤트가 발생했는지 확인
					if ( bChildCursorSelected == false )
					{
						int iAuxCursorGroupSize = GetCurrentAuxCursorGroupSize();
						if ( iAuxCursorGroupSize > 0 )
						{
							int iAuxCursorSize = 0;
							strGraph2D_Aux_Cursor_Extend strAuxCursor;

							for ( i = 0; i < iAuxCursorGroupSize; i++ )
							{
								if ( m_arrAuxCursorGroup.GetAt(i)->m_strGroupInfo.bShow == false )
								{
									continue;
								}

								iAuxCursorSize = GetCurrentAuxCursorSize(i);
								if ( iAuxCursorSize <= 0 )
								{
									continue;
								}

								for ( j = 0; j < iAuxCursorSize; j++ )
								{
									strAuxCursor = m_arrAuxCursorGroup.GetAt(i)->m_arrCursorInfo.GetAt(j);
									if ( strAuxCursor.bValid == false )
									{
										continue;
									}
									if ( strAuxCursor.strAuxCursorUser.bMouseEvent == false || strAuxCursor.strAuxCursorUser.bIndependency == false )
									{
										continue;
									}

									if ( strAuxCursor.crSelectX.PtInRect(point) )
									{
										m_iSelectAuxCursorGroupIndex = i;
										m_iSelectedAuxCursorGroupIndex = i;
										m_iSelectAuxCursorIndex = j;
										m_iSelectedAuxCursorIndex = j;
										m_bAuxCursorSelected = true;
										bAuxCursorSelected = true;
										break;
									}
								}					
							}
						}
					}

					//! 자식 커서, 보조 커서에 마우스 이벤트가 없고, 영역 커서에 마우스 이벤트가 있는지 확인
					if ( bChildCursorSelected == false && bAuxCursorSelected == false )
					{
						int iRegionCursorSize = (int)(m_arrRegionCursor.GetSize());
						if ( iRegionCursorSize > 0 )
						{
							for ( i = 0; i < iRegionCursorSize; i++ )
							{
								if ( m_arrRegionCursor.GetAt(i)->m_strCursorInfo.bShow == false )
								{
									continue;
								}

								if ( m_arrRegionCursor.GetAt(i)->IsPtInSelect(point, m_iSelectRegionCursorLineIndex) )
								{
									m_iSelectRegionCursorIndex = i;
									m_iSelectedRegionCursorIndex = i;
									m_bRegionCursorSelected = true;
									bRegionCursorSelected = true;
									m_bYScaleLock = true;
									break;
								}
								else if ( m_arrRegionCursor.GetAt(i)->m_crSelectRegion.PtInRect(point) )
								{
									m_iSelectRegionCursorLineIndex = REGION_CURSOR_CENTER;
									m_arrRegionCursor.GetAt(i)->m_ptMouseSave = point;

									m_iSelectRegionCursorIndex = i;
									m_iSelectedRegionCursorIndex = i;
									m_bRegionCursorSelected = true;
									bRegionCursorSelected = true;
									m_bYScaleLock = true;
									break;
								}
							}
						}
					}

					//! 자식 커서, 보조 커서, 영역 표시 커서에 마우스 이벤트가 없고, 커서에 마우스 이벤트가 있는지 확인
					if ( bChildCursorSelected == false && bAuxCursorSelected == false && bRegionCursorSelected == false )
					{			
						int iCursorSize = (int)(m_arrCursor.GetSize());
						if ( iCursorSize > 0 )
						{
							iCursorOperationFlag = 0;
							int iSelectCursorIndex = -1, iCloseCursorIndex = -1;
							int iDistanceTemp = 0, iDistanceMin = INT_MAX;
							int iTempXPos = 0, iTempYPos = 0;
							strGraph2DCursorInfo strCursorInfo;
							for ( i = 0; i < iCursorSize; i++ )
							{
								strCursorInfo = m_arrCursor.GetAt(i);

								if ( strCursorInfo.bMaxHold == false )
								{
									if ( strCursorInfo.crSelectX.PtInRect(point) && strCursorInfo.crSelectY.PtInRect(point) )
									{
										//! 커서 점을 정확하게 선택했을 때

										iSelectCursorIndex = i;
										iCursorOperationFlag = 1;
										break;
									}
									if ( strCursorInfo.crSelectX.PtInRect(point) || 
										(strCursorInfo.eLineMode == E_GRAPH2D_CURSOR_LINE_XY && strCursorInfo.crSelectY.PtInRect(point)) )
									{
										//! 커서 선을 선택했을 때

										iSelectCursorIndex = i;
										iCursorOperationFlag = 2;
										break;
									}
								}

								if ( strCursorInfo.crInfo.PtInRect(point) )
								{
									//! 커서 정보창을 마우스로 선택했을 때

									iSelectCursorIndex = i;
									iCursorOperationFlag = 3;
									break;
								}

								if ( strCursorInfo.bMaxHold == false && m_bCloseCursorSelect == true )
								{
									//! 마우스에서 가장 가까운 커서를 찾아냄

									iTempXPos = strCursorInfo.iXPos;
									iTempYPos = strCursorInfo.iYPos;
									iDistanceTemp = ((iTempXPos - point.x) * (iTempXPos - point.x)) + ((iTempYPos - point.y) * (iTempYPos - point.y));
									if ( iDistanceTemp < iDistanceMin )
									{
										iDistanceMin = iDistanceTemp;
										iCloseCursorIndex = i;
									}
								}
							}
							if ( m_bCloseCursorSelect == false )
							{
								iCloseCursorIndex = m_iSelectedCursorIndex;	//! Flag값에 따라 기존 선택 커서를 설정
							}
							if ( iSelectCursorIndex >= 0 && iSelectCursorIndex < iCursorSize )
							{					
								m_iSelectCursorIndex = iSelectCursorIndex;
								m_iSelectedCursorIndex = iSelectCursorIndex;
								m_eSelectCursorType = E_GRAPH2D_MOVE_MAIN_CURSOR_TYPE;

								if ( iCursorOperationFlag > 0 )
								{
									switch(iCursorOperationFlag)
									{
									case 1:
										{
											m_bCursorOverlap = true;
											m_bCursorSelected = true;
											m_bCursorInfoSelected = false;
										}
										break;
									case 2:
										{
											m_bCursorOverlap = false;
											m_bCursorSelected = true;
											m_bCursorInfoSelected = false;
										}
										break;
									case 3:
										{
											m_bCursorOverlap = false;
											m_bCursorSelected = false;
											m_bCursorInfoSelected = true;
										}
										break;
									}

									/*CRect rcClip;
									GetWindowRect(&rcClip);
									ClipCursor(&rcClip);*/						
								}
							}
							else
							{
								if ( iCloseCursorIndex >= 0 && iCloseCursorIndex < iCursorSize )
								{
									strCursorInfo = m_arrCursor.GetAt(iCloseCursorIndex);
									if ( CalcCursorPos(point.x, point.y, false, &strCursorInfo) == true )
									{
										strCursorInfo.crInfo.top = point.y;
										m_arrCursor.SetAt(iCloseCursorIndex, strCursorInfo);

										m_iSelectCursorIndex = iCloseCursorIndex;
										m_iSelectedCursorIndex = iCloseCursorIndex;
										m_eSelectCursorType = E_GRAPH2D_MOVE_MAIN_CURSOR_TYPE;

										m_bCursorOverlap = false;
										m_bCursorSelected = true;
										m_bCursorInfoSelected = false;

										SetFlag_If_CursorMoved(iCloseCursorIndex);
										
										/*CRect rcClip;
										GetWindowRect(&rcClip);
										ClipCursor(&rcClip);*/

										SendCursorEventMsg(iCloseCursorIndex, true, E_GRAPH2D_CURSOR_MOVE, &strCursorInfo);
										m_bChanged = true;
										Invalidate();									
									}
								}
							}
						}
					}
				}
			}
			break;
		case E_GRAPH2D_ZOOM_XY:
			{
				bool bValid = false;

				if ( GetRealDataSize() > 0 )	//! 데이터가 있을 경우에만 다음 과정 진행
				{
					if ( m_DataRect.PtInRect(point) )
					{
						bValid = true;
					}
				}

				if ( bValid == true )
				{
					m_ptMouseDownPos = point;
					
					m_crZoomArea.left = point.x;
					m_crZoomArea.right = point.x;
					m_crZoomArea.top = point.y;
					m_crZoomArea.bottom = point.y;
					m_bZoomMouseDown = true;
					SendMessage(WM_SETCURSOR);
				}
			}
			break;
		case E_GRAPH2D_ZOOM_X:
			{
				bool bValid = false;

				if ( GetRealDataSize() > 0 )	//! 데이터가 있을 경우에만 다음 과정 진행
				{
					if ( m_bTemporaryMouseOperation == false )
					{
						if ( m_DataRect.PtInRect(point) )
						{
							bValid = true;
						}
					}
					else
					{
						if ( m_crAxisX_Event.PtInRect(point) || m_DataRect.PtInRect(point) )
						{
							bValid = true;							
						}
					}
				}

				if ( bValid == true )
				{
					m_ptMouseDownPos = point;
						
					m_crZoomArea.left = point.x;
					m_crZoomArea.right = point.x;
					m_crZoomArea.top = m_DataRect.top + 1;
					m_crZoomArea.bottom = m_DataRect.bottom - 1;
					m_bZoomMouseDown = true;
					SendMessage(WM_SETCURSOR);
				}
			}
			break;
		case E_GRAPH2D_ZOOM_Y:
			{
				bool bValid = false;

				if ( GetRealDataSize() > 0 )	//! 데이터가 있을 경우에만 다음 과정 진행
				{
					if ( m_bTemporaryMouseOperation == false )
					{
						if ( m_DataRect.PtInRect(point) )
						{
							bValid = true;
						}
					}
					else
					{
						if ( m_crAxisY_Left_Event.PtInRect(point) || m_crAxisY_Right_Event.PtInRect(point) || m_DataRect.PtInRect(point) )
						{
							bValid = true;							
						}
					}
				}

				if ( bValid == true )
				{
					m_ptMouseDownPos = point;
						
					m_crZoomArea.left = m_DataRect.left + 1;
					m_crZoomArea.right = m_DataRect.right - 1;
					m_crZoomArea.top = point.y;
					m_crZoomArea.bottom = point.y;
					m_bZoomMouseDown = true;
					SendMessage(WM_SETCURSOR);
				}
			}
			break;
		case E_GRAPH2D_PAN_XY:
			{
				bool bValid = false;

				if ( GetRealDataSize() > 0 )	//! 데이터가 있을 경우에만 다음 과정 진행
				{
					if ( m_DataRect.PtInRect(point) )
					{
						bValid = true;
					}
				}

				if ( bValid == true )
				{
					m_strPanPosition.iStartX = m_strPanPosition.iEndX = point.x;
					m_strPanPosition.iStartY = m_strPanPosition.iEndY = point.y;
					m_bPanMouseDown = true;
					SendMessage(WM_SETCURSOR);
				}
			}
			break;
		case E_GRAPH2D_PAN_X:
			{
				bool bValid = false;

				if ( GetRealDataSize() > 0 )	//! 데이터가 있을 경우에만 다음 과정 진행
				{
					if ( m_bTemporaryMouseOperation == false )
					{
						if ( m_DataRect.PtInRect(point) )
						{
							bValid = true;
						}
					}
					else
					{
						if ( m_crAxisX_Event.PtInRect(point) || m_DataRect.PtInRect(point) )
						{
							bValid = true;
						}
					}
				}

				if ( bValid == true )
				{
					m_strPanPosition.iStartX = m_strPanPosition.iEndX = point.x;
					m_strPanPosition.iStartY = m_strPanPosition.iEndY = point.y;
					m_bPanMouseDown = true;
					SendMessage(WM_SETCURSOR);
				}
			}
			break;
		case E_GRAPH2D_PAN_Y:
			{
				bool bValid = false;

				if ( GetRealDataSize() > 0 )	//! 데이터가 있을 경우에만 다음 과정 진행
				{
					if ( m_bTemporaryMouseOperation == false )
					{
						if ( m_DataRect.PtInRect(point) )
						{
							bValid = true;
						}
					}
					else
					{
						if ( m_crAxisY_Left_Event.PtInRect(point) || m_crAxisY_Right_Event.PtInRect(point) || m_DataRect.PtInRect(point) )
						{
							bValid = true;
						}
					}
				}

				if ( bValid == true )
				{
					m_strPanPosition.iStartX = m_strPanPosition.iEndX = point.x;
					m_strPanPosition.iStartY = m_strPanPosition.iEndY = point.y;
					m_bPanMouseDown = true;
					SendMessage(WM_SETCURSOR);
				}
			}
			break;
		}
	}

	m_bLeftMouseDown = true;
	m_bMouseMoveProcessing = false;	//! Added by LHW [2008/7/24]

	if ( m_hMsgHandle != NULL )
	{
		CPoint curPos;
		GetCursorPos(&curPos);

		m_strMouseDownInfo.InitInfo();
		m_strMouseDownInfo.iPlotIndex = m_iPlotIndex;
		m_strMouseDownInfo.iMouseDownX = curPos.x;
		m_strMouseDownInfo.iMouseDownY = curPos.y;
		::SendMessage(m_hMsgHandle, WM_GRAPH2D_LMOUSE_DOWN, 0, (LPARAM)&m_strMouseDownInfo);
	}

	CWnd::OnLButtonDown(nFlags, point);
}

//! Modify by LHW [2008/4/28] : crInfo.top관련 수정
//! Modify by LHW [2008/6/13] : 자식 커서 관련 추가
//! Modify by LHW [2008/6/15] : SetFlag_If_CursorMoved 추가
//! Modify by LHW [2008/7/24] : m_bMouseMoveProcessing 추가
//! Modify by LHW [2008/8/4, 2008/8/5] : 보조 커서 마우스 이벤트 처리 추가
//! Modify by LHW [2008/9/19] : CPU 부하를 줄이기 위해 Ctrl키를 눌렀을 때의 처리를 추가
//! Modify by LHW [2008/10/25] : E_GRAPH2D_ZOOM_Y 추가, Zoom 영역 설정 부분 수정
//! Modify by LHW [2008/11/28] : 영역 표시 커서 관련 부분 추가
//! Modify by LHW [2008/12/1] : SendRegionCursorEventMsg 추가
//! Modify by LHW [2008/12/27] : 영역 표시 커서에서 m_bYScaleLock 추가
//! Modify by LHW [2009/1/6] : 확대 영역 설정 부분 수정, m_ptMouseDownPos 추가
//! Modify by LHW [2009/2/2] : E_GRAPH2D_PAN_X, E_GRAPH2D_PAN_Y 관련 부분 추가, m_bMouseMoved 추가
void CGraph2DWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	switch(m_eMouseOperationMode)
	{
	case E_GRAPH2D_CURSOR_XY:
		{
			if ( /*m_bLeftMouseDown == true &&*/ m_bDataPointEventMsg == true && (nFlags & MK_CONTROL) != 0 /*GetKeyState(VK_CONTROL) < 0*/ )
			{
				if ( m_bDataPointSearchProcessing == false )
				{
					m_bDataPointSearchProcessing = true;
					m_bDataPointSearchComplete = SearchDataPoint(point);
					m_bDataPointSearchProcessing = false;
				}
			}
			else
			{
				if ( m_bMouseMoveProcessing == false && m_bDrawing == false && m_bCalcCursor == false && m_bCalcChildCursor == false && m_bCalcAuxCursor == false )
				{
					if ( m_bCursorSelected == true )
					{
						//! 커서 이동
						if ( m_iSelectCursorIndex >= 0 && m_iSelectCursorIndex < (int)(m_arrCursor.GetSize()) )
						{
							strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(m_iSelectCursorIndex);
							if ( strCursorInfo.bMaxHold == false )
							{
								if ( CalcCursorPos(point.x, point.y, false, &strCursorInfo) == true )
								{
									m_bMouseMoveProcessing = true;
									strCursorInfo.crInfo.top = point.y;	//! 커서 정보창이 마우스와 같이 움직이도록 설정
									m_arrCursor.SetAt(m_iSelectCursorIndex, strCursorInfo);
									SetFlag_If_CursorMoved(m_iSelectCursorIndex);
									m_bChanged = true;
									Invalidate();
									SendCursorEventMsg(m_iSelectCursorIndex, true, E_GRAPH2D_CURSOR_MOVE, &strCursorInfo);
								}
							}
						}
					}
					else if ( m_bChildCursorSelected == true )
					{
						//! 자식 커서 이동
						if ( m_iSelectChildCursorIndex >= 0 && m_iSelectChildCursorIndex < (int)(m_arrChildCursor.GetSize()) )
						{
							if ( CalcChildCursorPos(point.x, point.y, false, m_iSelectChildCursorIndex) == true )
							{
								m_bMouseMoveProcessing = true;
								m_bChanged = true;
								Invalidate();
							}
						}
					}
					else if ( m_bCursorInfoSelected == true )
					{
						//! 커서 정보창 이동
						if ( m_iSelectCursorIndex >= 0 && m_iSelectCursorIndex < (int)(m_arrCursor.GetSize()) )
						{
							m_bMouseMoveProcessing = true;
							strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(m_iSelectCursorIndex);
							strCursorInfo.crInfo.top = point.y;
							strCursorInfo.crData = m_DataRect;
							m_arrCursor.SetAt(m_iSelectCursorIndex, strCursorInfo);
							m_bChanged = true;
							Invalidate();
						}
					}
					else if ( m_bChildCursorInfoSelected == true )
					{
						//! 자식 커서 정보창 이동
						if ( m_iSelectChildCursorIndex >= 0 && m_iSelectChildCursorIndex < (int)(m_arrChildCursor.GetSize()) )
						{
							m_bMouseMoveProcessing = true;
							m_arrChildCursor.GetAt(m_iSelectChildCursorIndex)->m_crInfo.top = point.y;
							m_arrChildCursor.GetAt(m_iSelectChildCursorIndex)->m_crData = m_DataRect;
							m_bChanged = true;
							Invalidate();
						}
					}
					else if ( m_bAuxCursorSelected == true )
					{
						//! 보조 커서 이동
						if ( m_iSelectAuxCursorGroupIndex >= 0 && m_iSelectAuxCursorGroupIndex < (int)(m_arrAuxCursorGroup.GetSize()) )
						{
							int iAuxCursorSize = (int)(m_arrAuxCursorGroup.GetAt(m_iSelectAuxCursorGroupIndex)->m_arrCursorInfo.GetSize());
							if ( m_iSelectAuxCursorIndex >= 0 && m_iSelectAuxCursorIndex < iAuxCursorSize )
							{
								if ( CalcAuxCursorPos(point.x, point.y, m_iSelectAuxCursorGroupIndex, m_iSelectAuxCursorIndex) == true )
								{
									m_bMouseMoveProcessing = true;
									m_bChanged = true;
									Invalidate();
								}
							}
						}
					}
					else if ( m_bRegionCursorSelected == true )
					{
						//! 영역 표시 커서 이동
						if ( m_iSelectRegionCursorIndex >= 0 && m_iSelectRegionCursorIndex < (int)(m_arrRegionCursor.GetSize()) )
						{
							if ( CalcRegionCursorPos(point.x, point.y, m_iSelectRegionCursorIndex, m_iSelectRegionCursorLineIndex) == true )
							{
								m_bMouseMoveProcessing = true;
								m_bYScaleLock = true;
								m_bChanged = true;
								Invalidate();
								SendRegionCursorEventMsg(m_iSelectRegionCursorIndex);
							}
						}
					}
				}
			}			
		}
		break;
	case E_GRAPH2D_ZOOM_XY:
		{
			if ( m_bZoomMouseDown == true )
			{
				int iZoomPosX = 0, iZoomPosY = 0;

				//! 그래프 영역을 벗어나지 않도록 검사
				if ( m_DataRect.right < point.x )
				{
					iZoomPosX = m_DataRect.right;					
				}
				else if ( m_DataRect.left > point.x )
				{
					iZoomPosX = m_DataRect.left;					
				}
				else
				{
					iZoomPosX = point.x;					
				}

				if ( m_ptMouseDownPos.x > iZoomPosX )
				{
					m_crZoomArea.left = iZoomPosX;
					m_crZoomArea.right = m_ptMouseDownPos.x;
				}
				else
				{
					m_crZoomArea.left = m_ptMouseDownPos.x;
					m_crZoomArea.right = iZoomPosX;
				}

				if ( m_DataRect.bottom < point.y )
				{
					iZoomPosY = m_DataRect.bottom;					
				}
				else if ( m_DataRect.top > point.y )
				{
					iZoomPosY = m_DataRect.top;					
				}
				else
				{
					iZoomPosY = point.y;					
				}

				if ( m_ptMouseDownPos.y > iZoomPosY )
				{
					m_crZoomArea.top = m_ptMouseDownPos.y;
					m_crZoomArea.bottom = iZoomPosY;
				}
				else
				{
					m_crZoomArea.top = iZoomPosY;
					m_crZoomArea.bottom = m_ptMouseDownPos.y;
				}
				
				Invalidate();
			}
		}
		break;
	case E_GRAPH2D_ZOOM_X:
		{
			if ( m_bZoomMouseDown == true )
			{
				int iZoomPosX = 0;

				//! 그래프 영역을 벗어나지 않도록 검사
				if ( (m_DataRect.right - 1) <= point.x )
				{
					iZoomPosX = m_DataRect.right - 2;					
				}
				else if ( m_DataRect.left >= point.x )
				{
					iZoomPosX = m_DataRect.left + 1;					
				}
				else
				{
					iZoomPosX = point.x;					
				}

				if ( m_ptMouseDownPos.x > iZoomPosX )
				{
					m_crZoomArea.left = iZoomPosX;
					m_crZoomArea.right = m_ptMouseDownPos.x;
				}
				else
				{
					m_crZoomArea.left = m_ptMouseDownPos.x;
					m_crZoomArea.right = iZoomPosX;
				}

				Invalidate();
			}
		}
		break;
	case E_GRAPH2D_ZOOM_Y:
		{
			if ( m_bZoomMouseDown == true )
			{
				int iZoomPosY = 0;

				//! 그래프 영역을 벗어나지 않도록 검사
				if ( m_DataRect.top >= point.y )
				{
					iZoomPosY = m_DataRect.top + 1;					
				}
				else if ( m_DataRect.bottom <= point.y )
				{
					iZoomPosY = m_DataRect.bottom - 1;					
				}
				else
				{
					iZoomPosY = point.y;					
				}

				if ( m_ptMouseDownPos.y > iZoomPosY )
				{
					m_crZoomArea.top = m_ptMouseDownPos.y;
					m_crZoomArea.bottom = iZoomPosY;
				}
				else
				{
					m_crZoomArea.top = iZoomPosY;
					m_crZoomArea.bottom = m_ptMouseDownPos.y;
				}

				Invalidate();
			}
		}
		break;
	case E_GRAPH2D_PAN_XY:
		{
			if ( m_bPanMouseDown == true )
			{
				int iMoveX = 0, iMoveY = 0;

				if ( m_DataRect.left > point.x )
				{
					iMoveX = m_DataRect.left;
				}
				else
				{
					iMoveX = point.x;
				}

				if ( m_DataRect.right < point.x )
				{
					iMoveX = m_DataRect.right;
				}
				else
				{
					iMoveX = point.x;
				}

				if ( m_DataRect.top > point.y )
				{
					iMoveY = m_DataRect.top;
				}
				else
				{
					iMoveY = point.y;
				}

				if ( m_DataRect.bottom < point.y )
				{
					iMoveY = m_DataRect.bottom;
				}
				else
				{
					iMoveY = point.y;
				}

				m_strPanPosition.iEndX = iMoveX;
				m_strPanPosition.iEndY = iMoveY;

				if ( ApplyPanPosition() == true )
				{
					m_strPanPosition.iStartX = iMoveX;
					m_strPanPosition.iStartY = iMoveY;
					m_bChanged = true;
					Invalidate();
				}
			}
		}
		break;
	case E_GRAPH2D_PAN_X:
		{
			if ( m_bPanMouseDown == true )
			{
				int iMoveX = 0;

				if ( m_DataRect.left > point.x )
				{
					iMoveX = m_DataRect.left;
				}
				else
				{
					iMoveX = point.x;
				}

				if ( m_DataRect.right < point.x )
				{
					iMoveX = m_DataRect.right;
				}
				else
				{
					iMoveX = point.x;
				}

				m_strPanPosition.iEndX = iMoveX;

				if ( ApplyPanPosition() == true )
				{
					m_strPanPosition.iStartX = iMoveX;					
					m_bChanged = true;
					Invalidate();
				}
			}
		}
		break;
	case E_GRAPH2D_PAN_Y:
		{
			if ( m_bPanMouseDown == true )
			{
				int iMoveY = 0;

				if ( m_DataRect.top > point.y )
				{
					iMoveY = m_DataRect.top;
				}
				else
				{
					iMoveY = point.y;
				}

				if ( m_DataRect.bottom < point.y )
				{
					iMoveY = m_DataRect.bottom;
				}
				else
				{
					iMoveY = point.y;
				}
				
				m_strPanPosition.iEndY = iMoveY;

				if ( ApplyPanPosition() == true )
				{					
					m_strPanPosition.iStartY = iMoveY;
					m_bChanged = true;
					Invalidate();
				}
			}
		}
		break;
	}

	m_bMouseMoved = true;

	CWnd::OnMouseMove(nFlags, point);
}

//! Modify by LHW [2008/4/28] : crInfo.top관련 수정
//! Modify by LHW [2008/5/28] : m_bLeftMouseDown, Data-Point Event관련 부분 추가
//! Modify by LHW [2008/6/13] : 자식 커서 관련 추가
//! Modify by LHW [2008/6/15] : SetFlag_If_CursorMoved 추가
//! Modify by LHW [2008/8/4, 2008/8/5] : 보조 커서 작업 부분 추가
//! Modify by LHW [2008/9/19] : CPU 부하를 줄이기 위해 Ctrl키를 눌렀을 때의 처리를 수정
//! Modify by LHW [2008/10/25] : E_GRAPH2D_ZOOM_Y 추가
//! Modify by LHW [2008/11/28] : 영역 표시 커서 관련 추가
//! Modify by LHW [2008/12/1] : SendRegionCursorEventMsg 추가
//! Modify by LHW [2008/12/27] : 영역 표시 커서에서 m_bYScaleLock 추가
//! Modify by LHW [2009/2/2] : 키보드로 Alt, Shift 키를 눌렀을 때, 확대, 축소, Pan 동작 기능 추가, m_bMouseMoved 추가
//! Modify by LHW [2009/2/3] : Pan 기능 수정
//! Modify by LHW [2009/2/14] : 확대, 축소 기능 관련 수정
//! Modify by LHW [2009/3/1] : Pan 관련 메시지 발생 부분 추가
void CGraph2DWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	/*if ( m_bCursorSelected == true || m_bCursorInfoSelected == true )
	{
		ClipCursor(NULL);
	}*/

	m_bYScaleLock = false;

	switch(m_eMouseOperationMode)
	{
	case E_GRAPH2D_CURSOR_XY:
		{
			if ( m_bLeftMouseDown == true && m_bDataPointEventMsg == true && (nFlags & MK_CONTROL) != 0 /*GetKeyState(VK_CONTROL) < 0*/ )
			{
				if ( m_bDataPointSearchComplete == false )
				{
					if ( m_bDataPointSearchProcessing == false )
					{
						m_bDataPointSearchProcessing = true;
						m_bDataPointSearchComplete = SearchDataPoint(point);
						m_bDataPointSearchProcessing = false;
					}
				}
				if ( m_bDataPointSearchComplete == true )
				{
					if ( m_hMsgHandle != NULL )
					{
						::SendMessage(m_hMsgHandle, WM_GRAPH2D_DATA_POINT_EVENT, 0, (LPARAM)&m_strDataPointEventInfo);
					}

					m_bDataPointSearchComplete = false;
				}
			}
			else
			{
				if ( m_bDrawing == false && m_bCalcCursor == false && m_bCalcChildCursor == false && m_bCalcAuxCursor == false )
				{
					if ( m_bCursorSelected == true )
					{
						//! 커서 이동
						if ( m_iSelectCursorIndex >= 0 && m_iSelectCursorIndex < (int)(m_arrCursor.GetSize()) )
						{
							strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(m_iSelectCursorIndex);
							if ( strCursorInfo.bMaxHold == false )
							{
								if ( CalcCursorPos(point.x, point.y, false, &strCursorInfo) == true )
								{
									strCursorInfo.crInfo.top = point.y;	//! 커서 정보창이 마우스와 같이 움직이도록 설정
									m_arrCursor.SetAt(m_iSelectCursorIndex, strCursorInfo);
									SetFlag_If_CursorMoved(m_iSelectCursorIndex);
									m_bChanged = true;
									Invalidate();
									SendCursorEventMsg(m_iSelectCursorIndex, true, E_GRAPH2D_CURSOR_MOVE, &strCursorInfo);
								}
							}
						}
					}
					else if ( m_bChildCursorSelected == true )
					{
						//! 자식 커서 이동
						if ( m_iSelectChildCursorIndex >= 0 && m_iSelectChildCursorIndex < (int)(m_arrChildCursor.GetSize()) )
						{
							if ( CalcChildCursorPos(point.x, point.y, false, m_iSelectChildCursorIndex) == true )
							{
								m_bChanged = true;
								Invalidate();
							}
						}
					}
					else if ( m_bCursorInfoSelected == true )
					{
						//! 커서 정보창 이동
						if ( m_iSelectCursorIndex >= 0 && m_iSelectCursorIndex < (int)(m_arrCursor.GetSize()) )
						{
							strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(m_iSelectCursorIndex);
							strCursorInfo.crInfo.top = point.y;
							strCursorInfo.crData = m_DataRect;
							m_arrCursor.SetAt(m_iSelectCursorIndex, strCursorInfo);
							m_bChanged = true;
							Invalidate();
						}
					}
					else if ( m_bChildCursorInfoSelected == true )
					{
						//! 자식 커서 정보창 이동
						if ( m_iSelectChildCursorIndex >= 0 && m_iSelectChildCursorIndex < (int)(m_arrChildCursor.GetSize()) )
						{
							m_arrChildCursor.GetAt(m_iSelectChildCursorIndex)->m_crInfo.top = point.y;
							m_arrChildCursor.GetAt(m_iSelectChildCursorIndex)->m_crData = m_DataRect;
							m_bChanged = true;
							Invalidate();
						}
					}
					else if ( m_bAuxCursorSelected == true )
					{
						//! 보조 커서 이동
						if ( m_iSelectAuxCursorGroupIndex >= 0 && m_iSelectAuxCursorGroupIndex < (int)(m_arrAuxCursorGroup.GetSize()) )
						{
							int iAuxCursorSize = (int)(m_arrAuxCursorGroup.GetAt(m_iSelectAuxCursorGroupIndex)->m_arrCursorInfo.GetSize());
							if ( m_iSelectAuxCursorIndex >= 0 && m_iSelectAuxCursorIndex < iAuxCursorSize )
							{
								if ( CalcAuxCursorPos(point.x, point.y, m_iSelectAuxCursorGroupIndex, m_iSelectAuxCursorIndex) == true )
								{									
									m_bChanged = true;
									Invalidate();
								}
							}
						}
					}
					else if ( m_bRegionCursorSelected == true )
					{
						//! 영역 표시 커서 이동
						if ( m_iSelectRegionCursorIndex >= 0 && m_iSelectRegionCursorIndex < (int)(m_arrRegionCursor.GetSize()) )
						{
							if ( CalcRegionCursorPos(point.x, point.y, m_iSelectRegionCursorIndex, m_iSelectRegionCursorLineIndex) == true )
							{						
								m_bChanged = true;
								Invalidate();
								SendRegionCursorEventMsg(m_iSelectRegionCursorIndex);
							}
						}
					}
				}
			}
		}
		break;
	case E_GRAPH2D_ZOOM_XY:
		{
			if ( m_bZoomMouseDown == true )
			{
				if ( ZoomArea(m_crZoomArea, false) == true )
				{
					m_crZoomArea.SetRectEmpty();
					m_bChanged = true;
					Invalidate();
				}

				m_bZoomMouseDown = false;
			}
		}
		break;
	case E_GRAPH2D_ZOOM_X:
		{
			bool bValid = false;

			if ( m_bMouseMoved == true )
			{
				if ( m_bZoomMouseDown == true )
				{
					if ( m_bTemporaryMouseOperation == true )
					{
						if ( m_crZoomArea.Width() > 0 )
						{
							bValid = true;
						}
					}
					else
					{
						bValid = true;
					}									
				}
			}
			
			/*if ( m_bTemporaryMouseOperation == true && bValid == false )
			{
				int iChkWidth = (int)(((double)(m_DataRect.Width())) / 2.);

				if ( m_bAxisEventFront == true )
				{
					m_crZoomArea.left = m_DataRect.left + 1;
					m_crZoomArea.right = m_DataRect.left + iChkWidth;
				}
				else
				{
					m_crZoomArea.left = m_DataRect.left + iChkWidth + 1;
					m_crZoomArea.right = m_DataRect.right - 2;
				}

				bValid = true;
			}*/

			if ( m_bTemporaryMouseOperation == true && bValid == false )
			{
				double dbInputMinX = 0., dbInputMaxX = 0.;
				double dbMinValue = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbManualMin;
				double dbMaxValue = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbManualMax;
				double dbMiddleValue = dbMinValue + ((dbMaxValue - dbMinValue) / 2.);
				if ( m_bAxisEventFront == true )
				{
					dbInputMinX = dbMinValue;
					dbInputMaxX = dbMiddleValue;
				}
				else
				{
					dbInputMinX = dbMiddleValue;
					dbInputMaxX = dbMaxValue;
				}

				if ( ZoomX(dbInputMinX, dbInputMaxX, false) == true )
				{
					m_crZoomArea.SetRectEmpty();
					m_bChanged = true;
					Invalidate();
				}
			}

			if ( bValid == true )
			{
				if ( ZoomArea(m_crZoomArea, false, E_GRAPH2D_ZOOM_DIRECTION_X) == true )
				{
					m_crZoomArea.SetRectEmpty();
					m_bChanged = true;
					Invalidate();
				}
			}

			m_bZoomMouseDown = false;
		}
		break;
	case E_GRAPH2D_ZOOM_Y:
		{
			bool bValid = false;

			if ( m_bMouseMoved == true )
			{
				if ( m_bZoomMouseDown == true )
				{
					if ( m_bTemporaryMouseOperation == true )
					{
						if ( m_crZoomArea.Height() > 0 )
						{
							bValid = true;
						}
					}
					else
					{
						bValid = true;
					}
				}
			}
			
			/*if ( m_bTemporaryMouseOperation == true && bValid == false )
			{
				int iChkHeight = (int)(((double)(m_DataRect.Height())) / 2.);
				
				if ( m_bAxisEventFront == true )
				{
					m_crZoomArea.top = m_DataRect.top + 1;
					m_crZoomArea.bottom = m_DataRect.top + iChkHeight;
				}
				else
				{
					m_crZoomArea.top = m_DataRect.top + iChkHeight + 1;
					m_crZoomArea.bottom = m_DataRect.bottom - 1;
				}

				bValid = true;
			}*/

			if ( m_bTemporaryMouseOperation == true && bValid == false )
			{
				int i = 0;
				double dbMinValue = 0., dbMaxValue = 0., dbMiddleValue = 0.;
				int iGraphBufSize = GetPlotBufferSize();
				if ( iGraphBufSize > 0 )
				{
					for ( i = 0; i < iGraphBufSize; i++ )
					{
						dbMinValue = m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbManualMin;
						dbMaxValue = m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbManualMax;
						dbMiddleValue = dbMinValue + ((dbMaxValue - dbMinValue) / 2.);

						if ( m_bAxisEventFront == true )
						{
							m_arrResourceY.GetAt(i)->m_dbTempRangeMin = dbMiddleValue;
							m_arrResourceY.GetAt(i)->m_dbTempRangeMax = dbMaxValue;
						}
						else
						{
							m_arrResourceY.GetAt(i)->m_dbTempRangeMin = dbMinValue;
							m_arrResourceY.GetAt(i)->m_dbTempRangeMax = dbMiddleValue;
						}
					}

					if ( ZoomY(false) == true )
					{
						m_crZoomArea.SetRectEmpty();
						m_bChanged = true;
						Invalidate();
					}
				}
			}

			if ( bValid == true )
			{
				if ( ZoomArea(m_crZoomArea, false, E_GRAPH2D_ZOOM_DIRECTION_Y) == true )
				{
					m_crZoomArea.SetRectEmpty();
					m_bChanged = true;
					Invalidate();
				}
			}

			m_bZoomMouseDown = false;
		}
		break;
	case E_GRAPH2D_PAN_XY:		
		{
			if ( m_bPanMouseDown == true )
			{
				if ( ApplyPanPosition() == true )
				{
					m_strPanPosition.InitInfo();
					m_bChanged = true;
					Invalidate();
				}

				m_bPanMouseDown = false;
				SendMessage(WM_SETCURSOR);

				if ( m_hMsgHandle != NULL )
				{
					::SendMessage(m_hMsgHandle, WM_GRAPH2D_PAN_XY_EVENT, 0, 0);
				}
			}
		}
		break;
	case E_GRAPH2D_PAN_X:
		{
			if ( m_bPanMouseDown == true )
			{
				if ( m_bTemporaryMouseOperation == true && m_bMouseMoved == false )
				{
					if ( m_strPanPosition.iEndX == m_strPanPosition.iStartX )
					{
						int iChkWidth = (int)(((double)(m_DataRect.Width())) / 2.);

						if ( m_bAxisEventFront == true )
						{
							m_strPanPosition.iStartX = m_DataRect.left + iChkWidth + 1;
							m_strPanPosition.iEndX = m_DataRect.left;
						}
						else
						{
							m_strPanPosition.iStartX = m_DataRect.left + iChkWidth + 1;
							m_strPanPosition.iEndX = m_DataRect.right;
						}
					}
				}

				if ( ApplyPanPosition() == true )
				{
					m_strPanPosition.InitInfo();
					m_bChanged = true;
					Invalidate();
				}

				m_bPanMouseDown = false;
				SendMessage(WM_SETCURSOR);

				if ( m_hMsgHandle != NULL )
				{
					::SendMessage(m_hMsgHandle, WM_GRAPH2D_PAN_X_EVENT, 0, 0);
				}
			}
		}
		break;
	case E_GRAPH2D_PAN_Y:
		{
			if ( m_bPanMouseDown == true )
			{
				if ( m_bTemporaryMouseOperation == true && m_bMouseMoved == false )
				{
					if ( m_strPanPosition.iEndY == m_strPanPosition.iStartY )
					{
						int iChkHeight = (int)(((double)(m_DataRect.Height())) / 2.);

						if ( m_bAxisEventFront == true )
						{
							m_strPanPosition.iStartY = m_DataRect.top + iChkHeight + 1;
							m_strPanPosition.iEndY = m_DataRect.top;
						}
						else
						{
							m_strPanPosition.iStartY = m_DataRect.top + iChkHeight + 1;
							m_strPanPosition.iEndY = m_DataRect.bottom;
						}
					}
				}

				if ( ApplyPanPosition() == true )
				{
					m_strPanPosition.InitInfo();
					m_bChanged = true;
					Invalidate();
				}

				m_bPanMouseDown = false;
				SendMessage(WM_SETCURSOR);

				if ( m_hMsgHandle != NULL )
				{
					::SendMessage(m_hMsgHandle, WM_GRAPH2D_PAN_Y_EVENT, 0, 0);
				}
			}
		}
		break;
	}

	ReleaseCapture();
	m_bCursorSelected = false;
	m_bCursorInfoSelected = false;
	m_bCursorOverlap = false;
	m_bChildCursorSelected = false;
	m_bChildCursorInfoSelected = false;
	m_bChildCursorOverlap = false;
	m_bAuxCursorSelected = false;
	m_bRegionCursorSelected = false;
	m_iSelectAuxCursorGroupIndex = -1;
	m_iSelectAuxCursorIndex = -1;
	m_iSelectCursorIndex = -1;
	m_iSelectChildCursorIndex = -1;
	m_iSelectRegionCursorIndex = -1;
	m_bLeftMouseDown = false;
	m_bMouseMoveProcessing = false;	//! Added by LHW [2008/7/24]
	m_bMouseMoved = false;

	if ( m_bTemporaryMouseOperation == true )
	{
		m_eMouseOperationMode = E_GRAPH2D_CURSOR_XY;
		m_bTemporaryMouseOperation = false;
		SendMessage(WM_SETCURSOR);
	}

	CWnd::OnLButtonUp(nFlags, point);
}

//! Added by LHW [2008/5/23]
//! Modify by LHW [2008/5/23] : Data-Point에 이벤트 관련 부분 제거
//! Modify by LHW [2008/7/31] : Y축에서 더블 클릭이 발생하면 메시지 발송하도록 기능 추가
//! Modify by LHW [2009/2/2] : m_AxisLeftRect, m_AxisRightRect를 m_crAxisY_Left_Event, m_crAxisY_Right_Event로 변경
//! Modify by LHW [2009/2/14] : 확대, 축소, Pan을 위해 Alt, Shift 키를 누른 상태에서는 WM_GRAPH2D_AXIS_Y_EVENT 메시지를 보내지 않도록 수정
void CGraph2DWnd::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if ( m_bAxisYEventMsg == true && m_hMsgHandle != NULL )
	{
		if ( m_crAxisY_Left_Event.PtInRect(point) || m_crAxisY_Right_Event.PtInRect(point) )
		{
			bool bTemporaryMouseOperation = false;

			if ( m_bAxisXZoom == true || m_bAxisYzoom == true || m_bAxisXYZoom == true || m_bAxisXPan == true || m_bAxisYPan == true || m_bAxisXYPan == true )
			{
				if ( GetKeyState(VK_LMENU) < 0 || GetKeyState(VK_RMENU) < 0 )	//! Alt 키
				{
					if ( m_bAxisXYZoom == true )
					{
						if ( m_DataRect.PtInRect(point) )
						{
							bTemporaryMouseOperation = true;
						}
					}
					if ( bTemporaryMouseOperation == false && m_bAxisXZoom == true )
					{
						if ( m_crAxisX_Event.PtInRect(point) )
						{
							bTemporaryMouseOperation = true;
						}
					}
					if ( bTemporaryMouseOperation == false && m_bAxisYzoom == true )
					{
						if ( m_crAxisY_Left_Event.PtInRect(point) || m_crAxisY_Right_Event.PtInRect(point) )
						{
							bTemporaryMouseOperation = true;
						}
					}
				}

				if ( (bTemporaryMouseOperation == false) && (GetKeyState(VK_LSHIFT) < 0 || GetKeyState(VK_RSHIFT) < 0) )	//! Shift 키
				{
					if ( m_bAxisXYPan == true )
					{
						if ( m_DataRect.PtInRect(point) )
						{
							bTemporaryMouseOperation = true;
						}
					}
					if ( bTemporaryMouseOperation == false && m_bAxisXPan == true )
					{
						if ( m_crAxisX_Event.PtInRect(point) )
						{
							bTemporaryMouseOperation = true;
						}
					}
					if ( bTemporaryMouseOperation == false && m_bAxisYPan == true )
					{
						if ( m_crAxisY_Left_Event.PtInRect(point) || m_crAxisY_Right_Event.PtInRect(point) )
						{
							bTemporaryMouseOperation = true;
						}
					}
				}
			}

			if ( bTemporaryMouseOperation == false )
			{
				::SendMessage(m_hMsgHandle, WM_GRAPH2D_AXIS_Y_EVENT, 0, 0);
			}
		}
	}

	//! Data-Point에 이벤트가 발생했는지 검색
	/*if ( m_bDataPointEventMsg == true && m_hMsgHandle != NULL )
	{
		if ( m_DataRect.Width() > 0 && m_DataRect.Height() > 0 )
		{
			int iGraphSize = GetPlotBufferSize();
			if ( iGraphSize > 0 )
			{
				bool bSearch = false;
				int i = 0, j = 0, iDrawDataSize = 0;
				int iVisualDataStartIndex = 0, iVisualDataEndIndex = 0;				
				CRect crEvent;

				for ( i = 0; i < iGraphSize; i++ )
				{
					if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.bShowGraph == false )
					{
						continue;
					}
					if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.bShowEventRect == false )
					{
						continue;
					}

					iDrawDataSize = m_arrPlotData.GetAt(i)->GetPointSize();
					if ( iDrawDataSize <= 0 )
					{
						continue;
					}

					if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.eDrawRangeMode == E_GRAPH2D_VISIBLE_RANGE_DRAW )
					{
						iVisualDataStartIndex = m_arrPlotData.GetAt(i)->m_iVisualDataStartIndex;
						iVisualDataEndIndex = m_arrPlotData.GetAt(i)->m_iVisualDataEndIndex;			
					}
					else
					{
						iVisualDataStartIndex = 0;
						iVisualDataEndIndex = iDrawDataSize;
					}

					for ( j = iVisualDataStartIndex; j < iVisualDataEndIndex; j++ )
					{
						if ( m_arrPlotData.GetAt(i)->GetCustomData(j) < 0 )
						{
							continue;
						}

						crEvent = m_arrPlotData.GetAt(i)->GetDataPointRect(j);
						if ( crEvent.PtInRect(point) )
						{
							bSearch = true;
							m_strDataPointEventInfo.iOverlapIndex = i;
							m_strDataPointEventInfo.iDataIndex = j;
							m_strDataPointEventInfo.dbXData = m_arrPlotData.GetAt(i)->GetXPoint2D(j);
							m_strDataPointEventInfo.dbYData = m_arrPlotData.GetAt(i)->GetYPoint2D(j);
							m_strDataPointEventInfo.iCustomData = m_arrPlotData.GetAt(i)->GetCustomData(j);							
							break;
						}

						if ( bSearch == true )
						{
							break;
						}
					}

					if ( bSearch == true )
					{
						break;
					}
				}

				if ( bSearch == true )
				{
					::SendMessage(m_hMsgHandle, WM_GRAPH2D_DATA_POINT_EVENT, 0, (LPARAM)&m_strDataPointEventInfo);
				}
			}			
		}		
	}*/

	CWnd::OnLButtonDblClk(nFlags, point);
}

void CGraph2DWnd::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	/*if ( m_bCursorSelected == true || m_bCursorInfoSelected == true )
	{
		ClipCursor(NULL);
	}*/

	//! Added by LHW [2009/2/2]
	m_bTemporaryMouseOperation = false;

	if ( m_bAxisXZoom == true || m_bAxisYzoom == true || m_bAxisXYZoom == true )
	{
		if ( m_eMouseOperationMode == E_GRAPH2D_CURSOR_XY )
		{
			//! Modify by LHW [2009/2/14] : 오른쪽 Alt 키 추가
			if ( GetKeyState(VK_LMENU) < 0 || GetKeyState(VK_RMENU) < 0 )	//! Alt 키
			{
				if ( m_bAxisXYZoom == true )
				{
					if ( m_DataRect.PtInRect(point) )
					{
						m_eMouseOperationMode = E_GRAPH2D_ZOOM_XY;
						m_bTemporaryMouseOperation = true;
					}
				}
				if ( m_bTemporaryMouseOperation == false && m_bAxisXZoom == true )
				{
					if ( m_crAxisX_Event.PtInRect(point) )
					{
						m_eMouseOperationMode = E_GRAPH2D_ZOOM_X;
						m_bTemporaryMouseOperation = true;
					}
				}
				if ( m_bTemporaryMouseOperation == false && m_bAxisYzoom == true )
				{
					if ( m_crAxisY_Left_Event.PtInRect(point) || m_crAxisY_Right_Event.PtInRect(point) )
					{
						m_eMouseOperationMode = E_GRAPH2D_ZOOM_Y;
						m_bTemporaryMouseOperation = true;
					}
				}
			}			
		}
	}

	m_bCursorSelected = false;
	m_bCursorInfoSelected = false;
	m_bCursorOverlap = false;
	m_bChildCursorOverlap = false;		//! Added by LHW [2008/8/20]
	m_bRegionCursorSelected = false;	//! Added by LHW [2008/11/28]
	m_iSelectCursorIndex = -1;
	m_iSelectChildCursorIndex = -1;		//! Added by LHW [2008/6/14]	
	m_iSelectAuxCursorGroupIndex = -1;	//! Added by LHW [2008/8/5]
	m_iSelectAuxCursorIndex = -1;		//! Added by LHW [2008/8/5]
	m_iSelectRegionCursorIndex = -1;	//! Added by LHW [2008/11/28]

	int i = 0, j = 0, iPtX = 0, iPtY = 0;

	CPoint curPos;
	GetCursorPos(&curPos);
	iPtX = curPos.x;
	iPtY = curPos.y;
	ScreenToClient(&curPos);
	m_ptSave = curPos;

	if ( m_bTemporaryMouseOperation == false )	//! Modify by LHW [2009/2/2]
	{
		if ( !m_DataRect.PtInRect(point) )
		{
			return;
		}
	}

	m_bRightMouseDown = true;	//! Added by LHW [2009/2/2]

	switch(m_eMouseOperationMode)
	{
	case E_GRAPH2D_CURSOR_XY:
		{
			int iCursorSize = (int)(m_arrCursor.GetSize());
			if ( iCursorSize > 0 )
			{
				int iSelectCursorIndex = -1;
				strGraph2DCursorInfo strCursorInfo;
				for ( int i = 0; i < iCursorSize; i++ )
				{
					strCursorInfo = m_arrCursor.GetAt(i);
					if ( strCursorInfo.crSelectX.PtInRect(point) || strCursorInfo.crSelectY.PtInRect(point) )
					{
						iSelectCursorIndex = i;
						break;
					}
				}
				if ( iSelectCursorIndex >= 0 && iSelectCursorIndex < iCursorSize )
				{
					m_iSelectCursorIndex = iSelectCursorIndex;
					m_iSelectedCursorIndex = iSelectCursorIndex;
					m_eSelectCursorType = E_GRAPH2D_MOVE_MAIN_CURSOR_TYPE;	//! Added by LHW [2008/6/16]
				}
			}
		}
		break;
	case E_GRAPH2D_ZOOM_XY:
	case E_GRAPH2D_ZOOM_X:
	case E_GRAPH2D_ZOOM_Y:	//! Modify by LHW [2008/10/25]
		{
			if ( m_bTemporaryMouseOperation == true )
			{
				SendMessage(WM_SETCURSOR);
			}
		}
		break;		
	case E_GRAPH2D_PAN_XY:
		{
		}
		break;
	}

	if ( m_bTemporaryMouseOperation == false )
	{
		//! X축 특정 값 표시선에 마우스 이벤트가 있는지 검사, Added by LHW [2008/4/19]
		bool bXValueLineEvent = false;
		int iXValueLineIndex = -1;
		if ( m_bXValueLineRMouseDownChk == true )
		{
			int iValueLineSizeX = (int)(m_arrValueLineX.GetSize());
			if ( iValueLineSizeX > 0 )
			{
				for ( i = 0; i < iValueLineSizeX; i++ )
				{
					if ( m_arrValueLineX.GetAt(i)->m_crSelect.PtInRect(point) )
					{
						bXValueLineEvent = true;
						iXValueLineIndex = i;
						break;
					}
				}
			}
		}

		//! 자식 커서에 마우스 이벤트가 있는지 검사, Added by LHW [2008/6/13]
		bool bChildCursorEvent = false;
		int iChildCursorIndex = -1;
		if ( m_bChildCursorRMouseDownChk == true )
		{
			int iChildCursorSize = (int)(m_arrChildCursor.GetSize());
			if ( iChildCursorSize > 0 )
			{
				for ( i = 0; i < iChildCursorSize; i++ )
				{
					if ( m_arrChildCursor.GetAt(i)->m_crSelectX.PtInRect(point) || m_arrChildCursor.GetAt(i)->m_crSelectY.PtInRect(point) )
					{
						bChildCursorEvent = true;
						iChildCursorIndex = i;
					}
				}
				if ( iChildCursorIndex >= 0 && iChildCursorIndex < iChildCursorSize )
				{
					m_iSelectChildCursorIndex = iChildCursorIndex;
					m_iSelectedChildCursorIndex = iChildCursorIndex;
					m_eSelectCursorType = E_GRAPH2D_MOVE_CHILD_CURSOR_TYPE;	//! Added by LHW [2008/6/16]
				}
			}
		}

		//! 보조 커서에 마우스 이벤트가 있는지 검사, Added by LHW [2008/8/5]
		bool bAuxCursorEvent = false;
		if ( m_bAuxCursorRMouseDownChk == true )
		{
			int iAuxCursorGroupSize = GetCurrentAuxCursorGroupSize();
			if ( iAuxCursorGroupSize > 0 )
			{
				int iAuxCursorSize = 0;
				strGraph2D_Aux_Cursor_Extend strAuxCursor;

				for ( i = 0; i < iAuxCursorGroupSize; i++ )
				{
					if ( m_arrAuxCursorGroup.GetAt(i)->m_strGroupInfo.bShow == false )
					{
						continue;
					}

					iAuxCursorSize = GetCurrentAuxCursorSize(i);
					if ( iAuxCursorSize <= 0 )
					{
						continue;
					}

					for ( j = 0; j < iAuxCursorSize; j++ )
					{
						strAuxCursor = m_arrAuxCursorGroup.GetAt(i)->m_arrCursorInfo.GetAt(j);
						if ( strAuxCursor.bValid == false )
						{
							continue;
						}

						if ( strAuxCursor.crSelectX.PtInRect(point) )
						{
							m_iSelectAuxCursorGroupIndex = i;
							m_iSelectedAuxCursorGroupIndex = i;
							m_iSelectAuxCursorIndex = j;
							m_iSelectedAuxCursorIndex = j;
							bAuxCursorEvent = true;
							break;
						}
					}
				}
			}
		}

		//! 영역 표시 커서에 마우스 이벤트가 있는지 검사, Added by LHW [2008/11/28]
		bool bRegionCursorEvent = false;
		if ( m_bRegionCursorRMouseDownChk == true )
		{
			int iRegionCursorSize = (int)(m_arrRegionCursor.GetSize());
			if ( iRegionCursorSize > 0 )
			{
				for ( i = 0; i < iRegionCursorSize; i++ )
				{
					if ( m_arrRegionCursor.GetAt(i)->m_strCursorInfo.bShow == false )
					{
						continue;
					}

					if ( m_arrRegionCursor.GetAt(i)->IsPtInSelect(point, m_iSelectRegionCursorLineIndex) )
					{
						m_iSelectRegionCursorIndex = i;
						m_iSelectedRegionCursorIndex = i;					
						bRegionCursorEvent = true;
						break;
					}
				}
			}
		}
		
		if ( m_hMsgHandle != NULL )
		{
			m_strMouseDownInfo.InitInfo();
			m_strMouseDownInfo.iPlotIndex = m_iPlotIndex;
			m_strMouseDownInfo.iMouseDownX = iPtX;
			m_strMouseDownInfo.iMouseDownY = iPtY;
			m_strMouseDownInfo.bXValueLineEvent = bXValueLineEvent;
			m_strMouseDownInfo.iXValueLineIndex = iXValueLineIndex;
			m_strMouseDownInfo.bChildCursorEvent = bChildCursorEvent;
			m_strMouseDownInfo.bAuxCursorEvent = bAuxCursorEvent;
			m_strMouseDownInfo.bRegionCursorEvent = bRegionCursorEvent;
			::SendMessage(m_hMsgHandle, WM_GRAPH2D_RMOUSE_DOWN, 0, (LPARAM)&m_strMouseDownInfo);
		}
	}

	CWnd::OnRButtonDown(nFlags, point);
}

//! Added by LHW [2009/2/2]
void CGraph2DWnd::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if ( m_bTemporaryMouseOperation == true && m_bRightMouseDown == true )
	{
		switch(m_eMouseOperationMode)
		{
		case E_GRAPH2D_ZOOM_XY:
		case E_GRAPH2D_ZOOM_X:
		case E_GRAPH2D_ZOOM_Y:
			{
				ZoomOut();
				m_bChanged = true;
				Invalidate();
			}
			break;
		}
	}

	m_bRightMouseDown = false;

	if ( m_bTemporaryMouseOperation == true )
	{
		m_eMouseOperationMode = E_GRAPH2D_CURSOR_XY;
		m_bTemporaryMouseOperation = false;
		SendMessage(WM_SETCURSOR);
	}

	CWnd::OnRButtonUp(nFlags, point);
}

//! Added by LHW [2008/5/28] : Data-Point에 이벤트가 발생했는지 검색
//! Modify by LHW [2008/8/9] : 영역 index 관련 오류 수정
bool CGraph2DWnd::SearchDataPoint(CPoint ptInput)
{
	if ( m_bDataPointEventMsg == false )
	{
		return false;
	}
	if ( m_hMsgHandle == NULL )
	{
		return false;
	}
	if ( m_DataRect.Width() <= 0 || m_DataRect.Height() <= 0 )
	{
		return false;
	}

	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize <= 0 )
	{
		return false;
	}

	bool bSearch = false;
	int i = 0, j = 0, iDrawDataSize = 0;
	int iVisualDataStartIndex = 0, iVisualDataEndIndex = 0;				
	CRect crEvent;

	for ( i = 0; i < iGraphSize; i++ )
	{
		if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.bShowGraph == false )
		{
			continue;
		}
		if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.bShowEventRect == false )
		{
			continue;
		}

		iDrawDataSize = m_arrPlotData.GetAt(i)->GetPointSize();
		if ( iDrawDataSize <= 0 )
		{
			continue;
		}

		if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.eDrawRangeMode == E_GRAPH2D_VISIBLE_RANGE_DRAW )
		{
			iVisualDataStartIndex = m_arrPlotData.GetAt(i)->m_iVisualDataStartIndex;
			iVisualDataEndIndex = m_arrPlotData.GetAt(i)->m_iVisualDataEndIndex + 1;			
		}
		else
		{
			iVisualDataStartIndex = 0;
			iVisualDataEndIndex = iDrawDataSize;
		}

		for ( j = iVisualDataStartIndex; j < iVisualDataEndIndex; j++ )
		{
			if ( m_arrPlotData.GetAt(i)->GetCustomData(j) < 0 )
			{
				continue;
			}

			crEvent = m_arrPlotData.GetAt(i)->GetDataPointRect(j);
			if ( crEvent.PtInRect(ptInput) )
			{
				bSearch = true;
				m_strDataPointEventInfo.iOverlapIndex = i;
				m_strDataPointEventInfo.iDataIndex = j;
				m_strDataPointEventInfo.dbXData = m_arrPlotData.GetAt(i)->GetXPoint2D(j);
				m_strDataPointEventInfo.dbYData = m_arrPlotData.GetAt(i)->GetYPoint2D(j);
				m_strDataPointEventInfo.iCustomData = m_arrPlotData.GetAt(i)->GetCustomData(j);							
				break;
			}

			if ( bSearch == true )
			{
				break;
			}
		}

		if ( bSearch == true )
		{
			break;
		}	
	}

	return bSearch;
}

void CGraph2DWnd::SetPlotIndex(int iPlotIndex)
{
	m_iPlotIndex = iPlotIndex;
}

int CGraph2DWnd::GetPlotIndex() const
{
	return m_iPlotIndex;
}

void CGraph2DWnd::SetPanCursor(HCURSOR hNewPanCursor1, HCURSOR hNewPanCursor2)
{
	m_hCursor_Pan_DOWN = hNewPanCursor1;
	m_hCursor_Pan_UP = hNewPanCursor2;
}

//! Added by LHW [2008/5/28]
void CGraph2DWnd::SetDataPointCursor(HCURSOR hNewDataPointCursor)
{
	m_hCursor_DataPoint_Event = hNewDataPointCursor;
}

//! Added by LHW [2009/2/2]
void CGraph2DWnd::SetZoomXYCursor(HCURSOR hNewCursor)
{
	m_hCursor_Zoom_XY = hNewCursor;
}

//! Added by LHW [2009/2/2]
void CGraph2DWnd::SetZoomXCursor(HCURSOR hNewCursor)
{
	m_hCursor_Zoom_X = hNewCursor;
}

//! Added by LHW [2009/2/2]
void CGraph2DWnd::SetZoomYCursor(HCURSOR hNewCursor)
{
	m_hCursor_Zoom_Y = hNewCursor;
}

//! Added by LHW [2009/2/2]
void CGraph2DWnd::SetPanXCursor(HCURSOR hNewCursor)
{
	m_hCursor_Pan_X = hNewCursor;
}

//! Added by LHW [2009/2/2]
void CGraph2DWnd::SetPanYCursor(HCURSOR hNewCursor)
{
	m_hCursor_Pan_Y = hNewCursor;
}

bool CGraph2DWnd::SetResourcePtr(CGraph2D_Resource *pResource)
{
	if ( pResource == NULL )
	{
		return false;
	}
	if ( m_pPlotResource != NULL )
	{
		return false;
	}

	m_pPlotResource = pResource;
	m_bSelfCreateResourcePtr = false;

	return true;
}

bool CGraph2DWnd::MakeResourcePtr()
{
	if ( m_pPlotResource != NULL )
	{
		return false;
	}

	m_pPlotResource = new CGraph2D_Resource;
	if ( m_pPlotResource == NULL )
	{
		return false;
	}

	m_bSelfCreateResourcePtr = true;

	return true;
}

bool CGraph2DWnd::ReleaseResourcePtr()
{
	if ( m_bSelfCreateResourcePtr == true && m_pPlotResource != NULL )
	{
		delete m_pPlotResource;
		m_pPlotResource = NULL;

		return true;
	}

	return false;
}

double CGraph2DWnd::GetFloor(double dbInput, int iResultMode)
{
	double dbResult = 0.;

	double dbBase = pow(10., iResultMode);
	dbResult = floor(dbBase * (dbInput + (0.5 / dbBase))) / dbBase;

	return dbResult;
}

bool CGraph2DWnd::SetResourceInfo(strGraph2DResourceInfo strInfo)
{
	if ( m_pPlotResource == NULL )
	{
		return false;
	}

	m_pPlotResource->m_strResourceInfo = strInfo;

	return true;
}

bool CGraph2DWnd::GetResourceInfo(strGraph2DResourceInfo &strInfo)
{
	if ( m_pPlotResource == NULL )
	{
		return false;
	}

	strInfo = m_pPlotResource->m_strResourceInfo;

	return true;
}

bool CGraph2DWnd::SetResourceYInfo(strGraph2D_Y_Axis_Info strInfo, int iOverlapIndex)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}

	m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo = strInfo;

	return true;
}

bool CGraph2DWnd::GetResourceYInfo(strGraph2D_Y_Axis_Info &strInfo, int iOverlapIndex)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}

	strInfo = m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo;

	return true;
}

//! Added by LHW [2008/10/25]
bool CGraph2DWnd::Init_XPos_YAxis(int iOverlapIndex)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}

	m_arrResourceY.GetAt(iOverlapIndex)->m_iLeftXPtofYAxis = 0;
	m_arrResourceY.GetAt(iOverlapIndex)->m_iRightXPtofYAxis = 0;

	return true;
}

//! Added by LHW [2008/10/25]
bool CGraph2DWnd::Get_XPos_YAxis(int iOverlapIndex, int &iLeftXPtofYAxis, int &iRightXPtofYAxis)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}

	iLeftXPtofYAxis = m_arrResourceY.GetAt(iOverlapIndex)->m_iLeftXPtofYAxis;
	iRightXPtofYAxis = m_arrResourceY.GetAt(iOverlapIndex)->m_iRightXPtofYAxis;

	return true;
}

//! Added by LHW [2008/10/25]
bool CGraph2DWnd::Set_XPos_YAxis(int iOverlapIndex, int iLeftXPtofYAxis, int iRightXPtofYAxis)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}

	m_arrResourceY.GetAt(iOverlapIndex)->m_iLeftXPtofYAxis = iLeftXPtofYAxis;
	m_arrResourceY.GetAt(iOverlapIndex)->m_iRightXPtofYAxis = iRightXPtofYAxis;

	return true;
}

bool CGraph2DWnd::SetPlotData(double *pdbInY, int iInputSize, int iOverlapIndex)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}
	if ( pdbInY == NULL || iInputSize <= 0 )
	{
		return false;
	}

	//m_arrCursor.RemoveAll();
	//m_arrCursor.FreeExtra();
	//DeleteAllCursor(true);	//! Modify by LHW [2008/4/21] 추가, Modify by LHW [2008/7/29] 삭제

	return m_arrPlotData.GetAt(iOverlapIndex)->SetPoint2D(pdbInY, iInputSize);
}

bool CGraph2DWnd::SetPlotData(double dbStartX, double dbIncrementX, double *pdbInY, int iInputSize, int iOverlapIndex)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}
	if ( pdbInY == NULL || iInputSize <= 0 )
	{
		return false;
	}

	//m_arrCursor.RemoveAll();
	//m_arrCursor.FreeExtra();
	//DeleteAllCursor(true);	//! Modify by LHW [2008/4/21] 추가, Modify by LHW [2008/7/29] 삭제

	return m_arrPlotData.GetAt(iOverlapIndex)->SetPoint2D(dbStartX, dbIncrementX, pdbInY, iInputSize);
}

bool CGraph2DWnd::SetPlotData(double *pdbInX, double *pdbInY, int iInputSize, int iOverlapIndex)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}
	if ( pdbInX == NULL || pdbInY == NULL || iInputSize <= 0 )
	{
		return false;
	}

	//m_arrCursor.RemoveAll();
	//m_arrCursor.FreeExtra();
	//DeleteAllCursor(true);	//! Modify by LHW [2008/4/21] 추가, Modify by LHW [2008/7/29] 삭제

	return m_arrPlotData.GetAt(iOverlapIndex)->SetPoint2D(pdbInX, pdbInY, iInputSize);
}

//! Added by LHW [2008/4/2]
bool CGraph2DWnd::SetPlotData(COleDateTime timeStartX, int iIncrementSecondX, double *pdbInY, int iInputSize, int iOverlapIndex)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}
	if ( pdbInY == NULL || iInputSize <= 0 )
	{
		return false;
	}

	//m_arrCursor.RemoveAll();
	//m_arrCursor.FreeExtra();
	//DeleteAllCursor(true);	//! Modify by LHW [2008/4/21] 추가, Modify by LHW [2008/7/29] 삭제

	m_arrPlotData.GetAt(iOverlapIndex)->ClearBuffer2D();

	COleDateTime timeTemp, timeInput;
	COleDateTimeSpan timeTempSpan(0, 0, 0, iIncrementSecondX);

	timeInput = timeStartX;
	m_arrPlotData.GetAt(iOverlapIndex)->AddPoint2D((double)(timeInput.m_dt), pdbInY[0]);

	if ( iInputSize > 1 )
	{
		for ( int i = 1; i < iInputSize; i++ )
		{
			timeTemp = timeInput;
			timeInput = timeTemp + timeTempSpan;
			m_arrPlotData.GetAt(iOverlapIndex)->AddPoint2D((double)(timeInput.m_dt), pdbInY[i]);
		}
	}

	return m_arrPlotData.GetAt(iOverlapIndex)->DecideMinMax();
}

bool CGraph2DWnd::AddPlotData(double dbInX, double dbInY, int iOverlapIndex)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}

	return m_arrPlotData.GetAt(iOverlapIndex)->AddPoint2D(dbInX, dbInY);
}

//! Added by LHW [2008/4/2]
bool CGraph2DWnd::AddPlotData(COleDateTime timeInX, double dbInY, int iOverlapIndex)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}

	return m_arrPlotData.GetAt(iOverlapIndex)->AddPoint2D((double)(timeInX.m_dt), dbInY);
}

//! Added by LHW [2008/5/23]
bool CGraph2DWnd::SetPlotData(double *pdbInY, int *piCustomData, int iInputSize, int iOverlapIndex)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}
	if ( pdbInY == NULL || iInputSize <= 0 )
	{
		return false;
	}
	
	//DeleteAllCursor(true); //! Modify by LHW [2008/7/29] 삭제

	return m_arrPlotData.GetAt(iOverlapIndex)->SetPoint2D(pdbInY, piCustomData, iInputSize);
}

//! Added by LHW [2008/5/23]
bool CGraph2DWnd::SetPlotData(double dbStartX, double dbIncrementX, double *pdbInY, int *piCustomData, int iInputSize, int iOverlapIndex)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}
	if ( pdbInY == NULL || iInputSize <= 0 )
	{
		return false;
	}
	
	//DeleteAllCursor(true);	//! Modify by LHW [2008/7/29] 삭제

	return m_arrPlotData.GetAt(iOverlapIndex)->SetPoint2D(dbStartX, dbIncrementX, pdbInY, piCustomData, iInputSize);
}

//! Added by LHW [2008/5/23]
bool CGraph2DWnd::SetPlotData(double *pdbInX, double *pdbInY, int *piCustomData, int iInputSize, int iOverlapIndex)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}
	if ( pdbInX == NULL || pdbInY == NULL || iInputSize <= 0 )
	{
		return false;
	}

	//DeleteAllCursor(true);	//! Modify by LHW [2008/7/29] 삭제

	return m_arrPlotData.GetAt(iOverlapIndex)->SetPoint2D(pdbInX, pdbInY, piCustomData, iInputSize);
}

//! Added by LHW [2008/5/23]
bool CGraph2DWnd::SetPlotData(COleDateTime timeStartX, int iIncrementSecondX, double *pdbInY, int *piCustomData, int iInputSize, int iOverlapIndex)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}
	if ( pdbInY == NULL || iInputSize <= 0 )
	{
		return false;
	}
	
	//DeleteAllCursor(true);	//! Modify by LHW [2008/7/29] 삭제

	m_arrPlotData.GetAt(iOverlapIndex)->ClearBuffer2D();

	COleDateTime timeTemp, timeInput;
	COleDateTimeSpan timeTempSpan(0, 0, 0, iIncrementSecondX);

	timeInput = timeStartX;
	if ( piCustomData != NULL )
	{
		m_arrPlotData.GetAt(iOverlapIndex)->AddPoint2D((double)(timeInput.m_dt), pdbInY[0], piCustomData[0]);
	}
	else
	{
		m_arrPlotData.GetAt(iOverlapIndex)->AddPoint2D((double)(timeInput.m_dt), pdbInY[0]);
	}

	if ( iInputSize > 1 )
	{
		for ( int i = 1; i < iInputSize; i++ )
		{
			timeTemp = timeInput;
			timeInput = timeTemp + timeTempSpan;
			if ( piCustomData != NULL )
			{
				m_arrPlotData.GetAt(iOverlapIndex)->AddPoint2D((double)(timeInput.m_dt), pdbInY[i], piCustomData[i]);
			}
			else
			{
				m_arrPlotData.GetAt(iOverlapIndex)->AddPoint2D((double)(timeInput.m_dt), pdbInY[i]);
			}
		}
	}

	return m_arrPlotData.GetAt(iOverlapIndex)->DecideMinMax();
}

//! Added by LHW [2008/5/23]
bool CGraph2DWnd::AddPlotData(int iCustomData, double dbInX, double dbInY, int iOverlapIndex)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}

	return m_arrPlotData.GetAt(iOverlapIndex)->AddPoint2D(dbInX, dbInY, iCustomData);
}

//! Added by LHW [2008/5/23]
bool CGraph2DWnd::AddPlotData(int iCustomData, COleDateTime timeInX, double dbInY, int iOverlapIndex)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}

	return m_arrPlotData.GetAt(iOverlapIndex)->AddPoint2D((double)(timeInX.m_dt), dbInY, iCustomData);
}

bool CGraph2DWnd::ClearPlotData(int iOverlapIndex)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}

	return m_arrPlotData.GetAt(iOverlapIndex)->ClearBuffer2D();
}

bool CGraph2DWnd::DecideMinMax(int iOverlapIndex)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}

	return m_arrPlotData.GetAt(iOverlapIndex)->DecideMinMax();
}

bool CGraph2DWnd::SetCaptionX(CString szInput)
{
	if ( m_pPlotResource == NULL )
	{
		return false;
	}

	((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.szCaption1 = szInput;

	return true;
}

//! Modify by LHW [2008/7/24]
bool CGraph2DWnd::SetCaptionY(CString szInput1, CString szInput2, int iOverlapIndex)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}

	m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.szCaption1 = szInput1;
	m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.szCaption2 = szInput2;

	return true;
}

bool CGraph2DWnd::SetCursorUnitX(CString szInput)
{
	if ( m_pPlotResource == NULL )
	{
		return false;
	}

	((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.szCursorUnit = szInput;

	return true;
}

bool CGraph2DWnd::SetCursorUnitY(CString szInput, int iOverlapIndex)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}

	m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.szCursorUnit = szInput;

	return true;
}

//! Modify by LHW [2008/4/2] : bShow 추가
//! Modify by LHW [2008/8/9] : 실제 데이터를 가졌을 경우만을 고려하도록 수정
//! Modify by LHW [2008/8/25] : 함수식으로 그려지는 그래프를 고려하는 부분을 추가
//! Modify by LHW [2008/8/26] : bShowChk관련 작업 추가
//! Modify by LHW [2008/12/14] : bRegionCursor 관련 작업 추가
double CGraph2DWnd::GetRealMinX(bool bEquation, bool bRegionCursor, bool bShow)
{
	double dbReturn = 0.;
	int i = 0, iOverlapIndexTemp = 0;	
	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize > 0 )
	{		
		bool bReturnFlag = false;
		double dbMinTemp = DBL_MAX;

		if ( bShow == true )
		{
			for ( i = 0; i < iGraphSize; i++ )
			{
				if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.bShowGraph == true && m_arrPlotData.GetAt(i)->GetPointSize() > 0 )
				{
					if ( dbMinTemp > m_arrPlotData.GetAt(i)->m_dbMinX )
					{
						bReturnFlag = true;
						dbMinTemp = m_arrPlotData.GetAt(i)->m_dbMinX;
					}
				}
			}
		}
		else
		{
			for ( i = 0; i < iGraphSize; i++ )
			{
				if ( m_arrPlotData.GetAt(i)->GetPointSize() > 0 )
				{
					if ( dbMinTemp > m_arrPlotData.GetAt(i)->m_dbMinX )
					{
						bReturnFlag = true;
						dbMinTemp = m_arrPlotData.GetAt(i)->m_dbMinX;
					}
				}
			}
		}

		if ( bReturnFlag == true )
		{
			dbReturn = dbMinTemp;
		}		
	}
	if ( bEquation == true )
	{
		int iGraphEquationSize = (int)(m_arrGraphEquation.GetSize());
		if ( iGraphEquationSize > 0 )
		{
			for ( i = 0; i < iGraphEquationSize; i++ )
			{
				if ( m_arrGraphEquation.GetAt(i)->m_strEquationInfo.bShow == false )
				{
					continue;
				}
				iOverlapIndexTemp = m_arrGraphEquation.GetAt(i)->m_strEquationInfo.iOverlapIndex;
				if ( iOverlapIndexTemp < 0 || iOverlapIndexTemp >= iGraphSize )
				{
					continue;
				}
				if ( m_arrGraphEquation.GetAt(i)->m_strEquationInfo.bShowGraphChk == true && 
					(m_arrResourceY.GetAt(iOverlapIndexTemp)->m_strResourceYinfo.bShowGraph == false || m_arrPlotData.GetAt(iOverlapIndexTemp)->GetPointSize() <= 0) )
				{
					continue;
				}
				if ( m_arrGraphEquation.GetAt(i)->m_strEquationInfo.bShowChk == true && m_arrGraphEquation.GetAt(i)->m_strEquationInfo.bShow == false )
				{
					continue;
				}
				if ( dbReturn > m_arrGraphEquation.GetAt(i)->m_strEquationInfo.dbStartRangeX )
				{
					dbReturn = m_arrGraphEquation.GetAt(i)->m_strEquationInfo.dbStartRangeX;
				}
			}
		}
	}
	if ( bRegionCursor == true )
	{
		int iRegionCursorSize = (int)(m_arrRegionCursor.GetSize());
		if ( iRegionCursorSize > 0 )
		{
			for ( i = 0; i < iRegionCursorSize; i++ )
			{
				if ( m_arrRegionCursor.GetAt(i)->m_strCursorInfo.bShow == false )
				{
					continue;
				}
				iOverlapIndexTemp = m_arrRegionCursor.GetAt(i)->m_strCursorInfo.iOverlapIndex;
				if ( iOverlapIndexTemp < 0 || iOverlapIndexTemp >= iGraphSize )
				{
					continue;
				}
				if ( m_arrRegionCursor.GetAt(i)->m_strCursorInfo.bShowGraphChk == true && 
					(m_arrResourceY.GetAt(iOverlapIndexTemp)->m_strResourceYinfo.bShowGraph == false || m_arrPlotData.GetAt(iOverlapIndexTemp)->GetPointSize() <= 0) )
				{
					continue;
				}
				if ( dbReturn > m_arrRegionCursor.GetAt(i)->m_dbMinDataX )
				{
					dbReturn = m_arrRegionCursor.GetAt(i)->m_dbMinDataX;
				}
			}
		}
	}
	return dbReturn;
}

//! Modify by LHW [2008/4/2] : bShow 추가
//! Modify by LHW [2008/8/9] : 실제 데이터를 가졌을 경우만을 고려하도록 수정
//! Modify by LHW [2008/8/25] : 함수식으로 그려지는 그래프를 고려하는 부분을 추가
//! Modify by LHW [2008/8/26] : bShowChk 관련 작업 추가
//! Modify by LHW [2008/12/14] : bRegionCursor 관련 작업 추가
double CGraph2DWnd::GetRealMaxX(bool bEquation, bool bRegionCursor, bool bShow)
{
	double dbReturn = 0.;
	int i = 0, iOverlapIndexTemp = 0;
	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize > 0 )
	{		
		bool bReturnFlag = false;
		double dbMaxTemp = DBL_MAX * (-1.);

		if ( bShow == true )
		{
			for ( i = 0; i < iGraphSize; i++ )
			{
				if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.bShowGraph == true && m_arrPlotData.GetAt(i)->GetPointSize() > 0 )
				{
					if ( dbMaxTemp < m_arrPlotData.GetAt(i)->m_dbMaxX )
					{
						bReturnFlag = true;
						dbMaxTemp = m_arrPlotData.GetAt(i)->m_dbMaxX;
					}
				}
			}
		}
		else
		{
			for ( i = 0; i < iGraphSize; i++ )
			{
				if ( m_arrPlotData.GetAt(i)->GetPointSize() > 0 )
				{
					if ( dbMaxTemp < m_arrPlotData.GetAt(i)->m_dbMaxX )
					{
						bReturnFlag = true;
						dbMaxTemp = m_arrPlotData.GetAt(i)->m_dbMaxX;
					}
				}
			}
		}

		if ( bReturnFlag == true )
		{
			dbReturn = dbMaxTemp;
		}		
	}
	if ( bEquation == true )
	{
		int iGraphEquationSize = (int)(m_arrGraphEquation.GetSize());
		if ( iGraphEquationSize > 0 )
		{
			for ( i = 0; i < iGraphEquationSize; i++ )
			{
				if ( m_arrGraphEquation.GetAt(i)->m_strEquationInfo.bShow == false )
				{
					continue;
				}
				iOverlapIndexTemp = m_arrGraphEquation.GetAt(i)->m_strEquationInfo.iOverlapIndex;
				if ( iOverlapIndexTemp < 0 || iOverlapIndexTemp >= iGraphSize )
				{
					continue;
				}
				if ( m_arrGraphEquation.GetAt(i)->m_strEquationInfo.bShowGraphChk == true && 
					(m_arrResourceY.GetAt(iOverlapIndexTemp)->m_strResourceYinfo.bShowGraph == false || m_arrPlotData.GetAt(iOverlapIndexTemp)->GetPointSize() <= 0) )
				{
					continue;
				}
				if ( m_arrGraphEquation.GetAt(i)->m_strEquationInfo.bShowChk == true && m_arrGraphEquation.GetAt(i)->m_strEquationInfo.bShow == false )
				{
					continue;
				}
				if ( dbReturn < m_arrGraphEquation.GetAt(i)->m_strEquationInfo.dbEndRangeX )
				{
					dbReturn = m_arrGraphEquation.GetAt(i)->m_strEquationInfo.dbEndRangeX;
				}
			}
		}
	}
	if ( bRegionCursor == true )
	{
		int iRegionCursorSize = (int)(m_arrRegionCursor.GetSize());
		if ( iRegionCursorSize > 0 )
		{
			for ( i = 0; i < iRegionCursorSize; i++ )
			{
				if ( m_arrRegionCursor.GetAt(i)->m_strCursorInfo.bShow == false )
				{
					continue;
				}
				iOverlapIndexTemp = m_arrRegionCursor.GetAt(i)->m_strCursorInfo.iOverlapIndex;
				if ( iOverlapIndexTemp < 0 || iOverlapIndexTemp >= iGraphSize )
				{
					continue;
				}
				if ( m_arrRegionCursor.GetAt(i)->m_strCursorInfo.bShowGraphChk == true && 
					(m_arrResourceY.GetAt(iOverlapIndexTemp)->m_strResourceYinfo.bShowGraph == false || m_arrPlotData.GetAt(iOverlapIndexTemp)->GetPointSize() <= 0) )
				{
					continue;
				}
				if ( dbReturn < m_arrRegionCursor.GetAt(i)->m_dbMaxDataX )
				{
					dbReturn = m_arrRegionCursor.GetAt(i)->m_dbMaxDataX;
				}
			}
		}
	}
	return dbReturn;
}

//! Added by LHW [2008/7/28]
double CGraph2DWnd::GetRealMinY(int iOverlapIndex)
{
	int iGraphSize = GetPlotBufferSize();
	if ( iOverlapIndex < 0 || iOverlapIndex >= iGraphSize )
	{
		return 0.;
	}

	return m_arrPlotData.GetAt(iOverlapIndex)->m_dbMinY;
}

//! Added by LHW [2008/7/28]
double CGraph2DWnd::GetRealMaxY(int iOverlapIndex)
{
	int iGraphSize = GetPlotBufferSize();
	if ( iOverlapIndex < 0 || iOverlapIndex >= iGraphSize )
	{
		return 0.;
	}

	return m_arrPlotData.GetAt(iOverlapIndex)->m_dbMaxY;
}

//! Added by LHW [2008/4/4]
//! Modify by LHW [2008/8/9] : 실제 데이터를 가졌을 경우만을 고려하도록 수정
//! Modify by LHW [2008/8/21] : bShowChk관련 작업 추가
double CGraph2DWnd::GetMinCompareYValueLine(int iOverlapIndex, double dbInput)
{
	double dbReturn = dbInput;

	if ( IsValidOverlapIndex(iOverlapIndex) == true )
	{
		int iYValueLineSize = (int)(m_arrValueLineY.GetSize());
		if ( iYValueLineSize > 0 )
		{
			int i = 0, iOverlapIndexTemp = 0;
			bool bReturnFlag = false;
			double dbMinTemp = DBL_MAX;

			for ( i = 0; i < iYValueLineSize; i++ )
			{
				iOverlapIndexTemp = m_arrValueLineY.GetAt(i)->m_strYLineInfo.iOverlapIndex;
				if ( iOverlapIndexTemp != iOverlapIndex )
				{
					continue;
				}
				if ( m_arrValueLineY.GetAt(i)->m_strYLineInfo.bGraphShowChk == true && 
					(m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.bShowGraph == false || 
					m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize() <= 0) )
				{
					continue;
				}
				if ( m_arrValueLineY.GetAt(i)->m_strYLineInfo.bShowChk == true && m_arrValueLineY.GetAt(i)->m_strYLineInfo.bShow == false )
				{
					continue;
				}

				if ( dbMinTemp > m_arrValueLineY.GetAt(i)->m_strYLineInfo.dbValue )
				{
					bReturnFlag = true;
					dbMinTemp = m_arrValueLineY.GetAt(i)->m_strYLineInfo.dbValue;
				}				
			}

			if ( bReturnFlag == true )
			{
				if ( dbReturn > dbMinTemp )
				{
					dbReturn = dbMinTemp;
				}
			}
		}
	}

	return dbReturn;
}

//! Added by LHW [2008/4/4]
//! Modify by LHW [2008/8/9] : 실제 데이터를 가졌을 경우만을 고려하도록 수정
//! Modify by LHW [2008/8/21] : bShowChk관련 작업 추가
double CGraph2DWnd::GetMaxCompareYValueLine(int iOverlapIndex, double dbInput)
{
	double dbReturn = dbInput;

	if ( IsValidOverlapIndex(iOverlapIndex) == true )
	{
		int iYValueLineSize = (int)(m_arrValueLineY.GetSize());
		if ( iYValueLineSize > 0 )
		{
			int i = 0, iOverlapIndexTemp = 0;
			bool bReturnFlag = false;
			double dbMaxTemp = DBL_MAX * (-1.);

			for ( i = 0; i < iYValueLineSize; i++ )
			{
				iOverlapIndexTemp = m_arrValueLineY.GetAt(i)->m_strYLineInfo.iOverlapIndex;
				if ( iOverlapIndexTemp != iOverlapIndex )
				{
					continue;
				}
				if ( m_arrValueLineY.GetAt(i)->m_strYLineInfo.bGraphShowChk == true && 
					(m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.bShowGraph == false || 
					m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize() <= 0) )
				{
					continue;
				}
				if ( m_arrValueLineY.GetAt(i)->m_strYLineInfo.bShowChk == true && m_arrValueLineY.GetAt(i)->m_strYLineInfo.bShow == false )
				{
					continue;
				}

				if ( dbMaxTemp < m_arrValueLineY.GetAt(i)->m_strYLineInfo.dbValue )
				{
					bReturnFlag = true;
					dbMaxTemp = m_arrValueLineY.GetAt(i)->m_strYLineInfo.dbValue;
				}				
			}

			if ( bReturnFlag == true )
			{
				if ( dbReturn < dbMaxTemp )
				{
					dbReturn = dbMaxTemp;
				}
			}
		}
	}

	return dbReturn;
}

//! Added by LHW [2008/8/25]
//! Modify by LHW [2008/8/26] : bShowChk 부분 추가
double CGraph2DWnd::GetMinCompareYEquation(int iOverlapIndex, double dbInput)
{
	double dbReturn = dbInput;

	if ( IsValidOverlapIndex(iOverlapIndex) == true )
	{
		int iGraphEquationSize = (int)(m_arrGraphEquation.GetSize());
		if ( iGraphEquationSize > 0 )
		{
			int i = 0, iOverlapIndexTemp = 0;
			bool bReturnFlag = false;
			double dbMinTemp = DBL_MAX;

			for ( i = 0; i < iGraphEquationSize; i++ )
			{
				iOverlapIndexTemp = m_arrGraphEquation.GetAt(i)->m_strEquationInfo.iOverlapIndex;
				if ( iOverlapIndexTemp != iOverlapIndex )
				{
					continue;
				}
				if ( m_arrGraphEquation.GetAt(i)->m_strEquationInfo.bShowGraphChk == true && 
					(m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.bShowGraph == false || 
					m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize() <= 0) )
				{
					continue;
				}
				if ( m_arrGraphEquation.GetAt(i)->m_strEquationInfo.bShowChk == true && m_arrGraphEquation.GetAt(i)->m_strEquationInfo.bShow == false )
				{
					continue;
				}
				
				if ( dbMinTemp > m_arrGraphEquation.GetAt(i)->m_dbDataMinY )
				{
					bReturnFlag = true;
					dbMinTemp = m_arrGraphEquation.GetAt(i)->m_dbDataMinY;
				}				
			}

			if ( bReturnFlag == true )
			{
				if ( dbReturn > dbMinTemp )
				{
					dbReturn = dbMinTemp;
				}
			}
		}
	}

	return dbReturn;
}

//! Added by LHW [2008/8/25]
//! Modify by LHW [2008/8/26] : bShowChk 부분 추가
double CGraph2DWnd::GetMaxCompareYEquation(int iOverlapIndex, double dbInput)
{
	double dbReturn = dbInput;

	if ( IsValidOverlapIndex(iOverlapIndex) == true )
	{
		int iGraphEquationSize = (int)(m_arrGraphEquation.GetSize());
		if ( iGraphEquationSize > 0 )
		{
			int i = 0, iOverlapIndexTemp = 0;
			bool bReturnFlag = false;
			double dbMaxTemp = DBL_MAX * (-1.);

			for ( i = 0; i < iGraphEquationSize; i++ )
			{
				iOverlapIndexTemp = m_arrGraphEquation.GetAt(i)->m_strEquationInfo.iOverlapIndex;
				if ( iOverlapIndexTemp != iOverlapIndex )
				{
					continue;
				}
				if ( m_arrGraphEquation.GetAt(i)->m_strEquationInfo.bShowGraphChk == true && 
					(m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.bShowGraph == false || 
					m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize() <= 0) )
				{
					continue;
				}
				if ( m_arrGraphEquation.GetAt(i)->m_strEquationInfo.bShowChk == true && m_arrGraphEquation.GetAt(i)->m_strEquationInfo.bShow == false )
				{
					continue;
				}
				
				if ( dbMaxTemp < m_arrGraphEquation.GetAt(i)->m_dbDataMaxY )
				{
					bReturnFlag = true;
					dbMaxTemp = m_arrGraphEquation.GetAt(i)->m_dbDataMaxY;
				}				
			}

			if ( bReturnFlag == true )
			{
				if ( dbReturn < dbMaxTemp )
				{
					dbReturn = dbMaxTemp;
				}
			}
		}
	}

	return dbReturn;
}

//! Added by LHW [2008/12/14]
double CGraph2DWnd::GetMinCompareYRegionCursor(int iOverlapIndex, double dbInput)
{
	double dbReturn = dbInput;

	if ( IsValidOverlapIndex(iOverlapIndex) == true )
	{
		int iRegionCursorSize = (int)(m_arrRegionCursor.GetSize());
		if ( iRegionCursorSize > 0 )
		{
			int i = 0, iOverlapIndexTemp = 0;
			bool bReturnFlag = false;
			double dbMinTemp = DBL_MAX;

			for ( i = 0; i < iRegionCursorSize; i++ )
			{
				iOverlapIndexTemp = m_arrRegionCursor.GetAt(i)->m_strCursorInfo.iOverlapIndex;
				if ( iOverlapIndexTemp != iOverlapIndex )
				{
					continue;
				}
				if ( m_arrRegionCursor.GetAt(i)->m_strCursorInfo.bShowGraphChk == true && 
					(m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.bShowGraph == false || 
					m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize() <= 0) )
				{
					continue;
				}

				if ( dbMinTemp > m_arrRegionCursor.GetAt(i)->m_dbMinDataY )
				{
					bReturnFlag = true;
					dbMinTemp = m_arrRegionCursor.GetAt(i)->m_dbMinDataY;
				}
			}

			if ( bReturnFlag == true )
			{
				if ( dbReturn > dbMinTemp )
				{
					dbReturn = dbMinTemp;
				}
			}
		}
	}

	return dbReturn;
}

//! Added by LHW [2008/12/14]
double CGraph2DWnd::GetMaxCompareYRegionCursor(int iOverlapIndex, double dbInput)
{
	double dbReturn = dbInput;

	if ( IsValidOverlapIndex(iOverlapIndex) == true )
	{
		int iRegionCursorSize = (int)(m_arrRegionCursor.GetSize());
		if ( iRegionCursorSize > 0 )
		{
			int i = 0, iOverlapIndexTemp = 0;
			bool bReturnFlag = false;
			double dbMaxTemp = DBL_MAX * (-1.);

			for ( i = 0; i < iRegionCursorSize; i++ )
			{
				iOverlapIndexTemp = m_arrRegionCursor.GetAt(i)->m_strCursorInfo.iOverlapIndex;
				if ( iOverlapIndexTemp != iOverlapIndex )
				{
					continue;
				}
				if ( m_arrRegionCursor.GetAt(i)->m_strCursorInfo.bShowGraphChk == true && 
					(m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.bShowGraph == false || 
					m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize() <= 0) )
				{
					continue;
				}

				if ( dbMaxTemp < m_arrRegionCursor.GetAt(i)->m_dbMaxDataY )
				{
					bReturnFlag = true;
					dbMaxTemp = m_arrRegionCursor.GetAt(i)->m_dbMaxDataY;
				}
			}

			if ( bReturnFlag == true )
			{
				if ( dbReturn < dbMaxTemp )
				{
					dbReturn = dbMaxTemp;
				}
			}
		}
	}

	return dbReturn;
}

//! Modify by LHW [2008/4/2] : bShow 추가
//! Modify by LHW [2008/4/4] : bYValueLine 추가
//! Modify by LHW [2008/8/9] : 실제 데이터를 가졌을 경우만을 고려하도록 수정
//! Modify by LHW [2008/8/21] : bShowChk관련 작업 추가
//! Modify by LHW [2008/8/25] : 함수식으로 그려지는 그래프를 고려하는 부분을 추가
//! Modify by LHW [2008/8/26] : bShowChk 부분 추가
//! Modify by LHW [2008/12/14] : bRegionCursor 부분 추가
//! Modify by LHW [2009/3/5] : m_bAutoRangeY_UsingRangeX 부분 추가
double CGraph2DWnd::GetRealMinY(bool bEquation, bool bYValueLine, bool bRegionCursor, bool bShow)
{
	double dbReturn = 0.;
	int i = 0, j = 0, iOverlapIndex = 0;
	double dbMinTemp = DBL_MAX, dbDataTemp = 0.;
	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize > 0 )
	{
		bool bReturnFlag = false;
		dbMinTemp = DBL_MAX;

		if ( bShow == true )
		{
			for ( i = 0; i < iGraphSize; i++ )
			{
				if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.bShowGraph == true && m_arrPlotData.GetAt(i)->GetPointSize() > 0 )
				{
					if ( m_bAutoRangeY_UsingRangeX == true )
					{
						if ( GetMinY_UsingRangeX(dbDataTemp, i) == false )
						{
							dbDataTemp = -1.;
						}
					}
					else
					{
						dbDataTemp = m_arrPlotData.GetAt(i)->m_dbMinY;
					}

					if ( dbMinTemp > dbDataTemp )
					{
						bReturnFlag = true;
						dbMinTemp = dbDataTemp;
					}
				}
			}
		}
		else
		{
			for ( i = 0; i < iGraphSize; i++ )
			{
				if ( m_arrPlotData.GetAt(i)->GetPointSize() > 0 )
				{
					if ( m_bAutoRangeY_UsingRangeX == true )
					{
						if ( GetMinY_UsingRangeX(dbDataTemp, i) == false )
						{
							dbDataTemp = -1.;
						}
					}
					else
					{
						dbDataTemp = m_arrPlotData.GetAt(i)->m_dbMinY;
					}

					if ( dbMinTemp > dbDataTemp )
					{
						bReturnFlag = true;
						dbMinTemp = dbDataTemp;
					}
				}
			}
		}

		if ( bReturnFlag == true )
		{
			dbReturn = dbMinTemp;
		}

		if ( bYValueLine == true )
		{
			iOverlapIndex = 0;
			bReturnFlag = false;
			dbMinTemp = DBL_MAX;
			int iYValueLineSize = (int)(m_arrValueLineY.GetSize());
			if ( iYValueLineSize > 0 )
			{
				for ( i = 0; i < iYValueLineSize; i++ )
				{
					iOverlapIndex = m_arrValueLineY.GetAt(i)->m_strYLineInfo.iOverlapIndex;
					if ( IsValidOverlapIndex(iOverlapIndex) == false )
					{
						continue;
					}
					if ( m_arrValueLineY.GetAt(i)->m_strYLineInfo.bGraphShowChk == true && 
						m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.bShowGraph == false && 
						m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize() <= 0 )
					{
						continue;
					}
					if ( m_arrValueLineY.GetAt(i)->m_strYLineInfo.bShowChk == true && m_arrValueLineY.GetAt(i)->m_strYLineInfo.bShow == false )
					{
						continue;
					}

					if ( dbMinTemp > m_arrValueLineY.GetAt(i)->m_strYLineInfo.dbValue )
					{
						bReturnFlag = true;
						dbMinTemp = m_arrValueLineY.GetAt(i)->m_strYLineInfo.dbValue;
					}					
				}

				if ( bReturnFlag == true )
				{
					if ( dbReturn > dbMinTemp )
					{
						dbReturn = dbMinTemp;
					}
				}
			}
		}

		if ( bEquation == true )
		{
			int iGraphEquationSize = (int)(m_arrGraphEquation.GetSize());
			if ( iGraphEquationSize > 0 )
			{
				for ( i = 0; i < iGraphEquationSize; i++ )
				{
					if ( m_arrGraphEquation.GetAt(i)->m_strEquationInfo.bShow == false )
					{
						continue;
					}
					iOverlapIndex = m_arrGraphEquation.GetAt(i)->m_strEquationInfo.iOverlapIndex;
					if ( iOverlapIndex < 0 || iOverlapIndex >= iGraphSize )
					{
						continue;
					}
					if ( m_arrGraphEquation.GetAt(i)->m_strEquationInfo.bShowGraphChk == true && 
						(m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.bShowGraph == false || 
						m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize() <= 0) )
					{
						continue;
					}
					if ( m_arrGraphEquation.GetAt(i)->m_strEquationInfo.bShowChk == true && m_arrGraphEquation.GetAt(i)->m_strEquationInfo.bShow == false )
					{
						continue;
					}

					if ( dbReturn > m_arrGraphEquation.GetAt(i)->m_dbDataMinY )
					{
						dbReturn = m_arrGraphEquation.GetAt(i)->m_dbDataMinY;
					}
				}
			}
		}

		if ( bRegionCursor == true )
		{
			int iRegionCursorSize = (int)(m_arrRegionCursor.GetSize());
			if ( iRegionCursorSize > 0 )
			{
				for ( i = 0; i < iRegionCursorSize; i++ )
				{
					if ( m_arrRegionCursor.GetAt(i)->m_strCursorInfo.bShow == false )
					{
						continue;
					}
					iOverlapIndex = m_arrRegionCursor.GetAt(i)->m_strCursorInfo.iOverlapIndex;
					if ( iOverlapIndex < 0 || iOverlapIndex >= iGraphSize )
					{
						continue;
					}
					if ( m_arrRegionCursor.GetAt(i)->m_strCursorInfo.bShowGraphChk == true && 
						(m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.bShowGraph == false || 
						m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize() <= 0) )
					{
						continue;
					}

					if ( dbReturn > m_arrRegionCursor.GetAt(i)->m_dbMinDataY )
					{
						dbReturn = m_arrRegionCursor.GetAt(i)->m_dbMinDataY;
					}
				}
			}
		}
	}

	return dbReturn;
}

//! Modify by LHW [2008/4/2] : bShow 추가
//! Modify by LHW [2008/4/4] : bYValueLine 추가
//! Modify by LHW [2008/8/9] : 실제 데이터를 가졌을 경우만을 고려하도록 수정
//! Modify by LHW [2008/8/21] : bShowChk관련 작업 추가
//! Modify by LHW [2008/8/25] : 함수식으로 그려지는 그래프를 고려하는 부분을 추가
//! Modify by LHW [2008/8/26] : bShowChk 부분 추가
//! Modify by LHW [2008/12/14] : bRegionCursor 부분 추가
//! Modify by LHW [2009/3/5] : m_bAutoRangeY_UsingRangeX 부분 추가
double CGraph2DWnd::GetRealMaxY(bool bEquation, bool bYValueLine, bool bRegionCursor, bool bShow)
{
	double dbReturn = 0.;
	int i = 0, j = 0;	
	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize > 0 )
	{
		bool bReturnFlag = false;
		double dbMaxTemp = DBL_MAX * (-1.), dbDataTemp = 0.;

		if ( bShow == true )
		{
			for ( i = 0; i < iGraphSize; i++ )
			{
				if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.bShowGraph == true && m_arrPlotData.GetAt(i)->GetPointSize() > 0 )
				{
					if ( m_bAutoRangeY_UsingRangeX == true )
					{
						if ( GetMaxY_UsingRangeX(dbDataTemp, i) == false )
						{
							dbDataTemp = -1.;
						}
					}
					else
					{
						dbDataTemp = m_arrPlotData.GetAt(i)->m_dbMaxY;
					}

					if ( dbMaxTemp < dbDataTemp )
					{
						bReturnFlag = true;
						dbMaxTemp = dbDataTemp;
					}
				}
			}
		}
		else
		{
			for ( i = 0; i < iGraphSize; i++ )
			{
				if ( m_arrPlotData.GetAt(i)->GetPointSize() > 0 )
				{
					if ( m_bAutoRangeY_UsingRangeX == true )
					{
						if ( GetMaxY_UsingRangeX(dbDataTemp, i) == false )
						{
							dbDataTemp = -1.;
						}
					}
					else
					{
						dbDataTemp = m_arrPlotData.GetAt(i)->m_dbMaxY;
					}

					if ( dbMaxTemp < dbDataTemp )
					{
						bReturnFlag = true;
						dbMaxTemp = dbDataTemp;
					}
				}
			}
		}

		if ( bReturnFlag == true )
		{
			dbReturn = dbMaxTemp;
		}

		int iOverlapIndex = 0;

		if ( bYValueLine == true )
		{
			iOverlapIndex = 0;
			bReturnFlag = false;
			dbMaxTemp = DBL_MAX * (-1.);
			int iYValueLineSize = (int)(m_arrValueLineY.GetSize());
			if ( iYValueLineSize > 0 )
			{
				for ( i = 0; i < iYValueLineSize; i++ )
				{
					iOverlapIndex = m_arrValueLineY.GetAt(i)->m_strYLineInfo.iOverlapIndex;
					if ( IsValidOverlapIndex(iOverlapIndex) == false )
					{
						continue;
					}
					if ( m_arrValueLineY.GetAt(i)->m_strYLineInfo.bGraphShowChk == true && 
						m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.bShowGraph == false && 
						m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize() <= 0 )
					{
						continue;
					}
					if ( m_arrValueLineY.GetAt(i)->m_strYLineInfo.bShowChk == true && m_arrValueLineY.GetAt(i)->m_strYLineInfo.bShow == false )
					{
						continue;
					}

					if ( dbMaxTemp < m_arrValueLineY.GetAt(i)->m_strYLineInfo.dbValue )
					{
						bReturnFlag = true;
						dbMaxTemp = m_arrValueLineY.GetAt(i)->m_strYLineInfo.dbValue;
					}					
				}

				if ( bReturnFlag == true )
				{
					if ( dbReturn < dbMaxTemp )
					{
						dbReturn = dbMaxTemp;
					}
				}
			}
		}

		if ( bEquation == true )
		{
			int iGraphEquationSize = (int)(m_arrGraphEquation.GetSize());
			if ( iGraphEquationSize > 0 )
			{
				for ( i = 0; i < iGraphEquationSize; i++ )
				{
					if ( m_arrGraphEquation.GetAt(i)->m_strEquationInfo.bShow == false )
					{
						continue;
					}
					iOverlapIndex = m_arrGraphEquation.GetAt(i)->m_strEquationInfo.iOverlapIndex;
					if ( iOverlapIndex < 0 || iOverlapIndex >= iGraphSize )
					{
						continue;
					}
					if ( m_arrGraphEquation.GetAt(i)->m_strEquationInfo.bShowGraphChk == true && 
						(m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.bShowGraph == false || 
						m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize() <= 0) )
					{
						continue;
					}
					if ( m_arrGraphEquation.GetAt(i)->m_strEquationInfo.bShowChk == true && m_arrGraphEquation.GetAt(i)->m_strEquationInfo.bShow == false )
					{
						continue;
					}

					if ( dbReturn < m_arrGraphEquation.GetAt(i)->m_dbDataMaxY )
					{
						dbReturn = m_arrGraphEquation.GetAt(i)->m_dbDataMaxY;
					}
				}
			}
		}

		if ( bRegionCursor == true )
		{
			int iRegionCursorSize = (int)(m_arrRegionCursor.GetSize());
			if ( iRegionCursorSize > 0 )
			{
				for ( i = 0; i < iRegionCursorSize; i++ )
				{
					if ( m_arrRegionCursor.GetAt(i)->m_strCursorInfo.bShow == false )
					{
						continue;
					}
					iOverlapIndex = m_arrRegionCursor.GetAt(i)->m_strCursorInfo.iOverlapIndex;
					if ( iOverlapIndex < 0 || iOverlapIndex >= iGraphSize )
					{
						continue;
					}
					if ( m_arrRegionCursor.GetAt(i)->m_strCursorInfo.bShowGraphChk == true && 
						(m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.bShowGraph == false || 
						m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize() <= 0) )
					{
						continue;
					}

					if ( dbReturn < m_arrRegionCursor.GetAt(i)->m_dbMaxDataY )
					{
						dbReturn = m_arrRegionCursor.GetAt(i)->m_dbMaxDataY;
					}
				}
			}
		}
	}

	return dbReturn;
}

//! Added by LHW [2013/2/22]
bool CGraph2DWnd::GetPlotDataX(double &dbValueX, int iDataIndex, int iOverlapIndex)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}
	int iDataSize = m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize();
	if ( iDataSize <= 0 )
	{
		return false;
	}
	if ( iDataIndex < 0 || iDataIndex >= iDataSize )
	{
		return false;
	}

	dbValueX = m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(iDataIndex);

	return true;
}

//! Added by LHW [2013/2/22]
bool CGraph2DWnd::GetPlotDataY(double &dbValueY, int iDataIndex, int iOverlapIndex)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}
	int iDataSize = m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize();
	if ( iDataSize <= 0 )
	{
		return false;
	}
	if ( iDataIndex < 0 || iDataIndex >= iDataSize )
	{
		return false;
	}

	dbValueY = m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(iDataIndex);

	return true;
}

//! Added by LHW [2009/3/5]
bool CGraph2DWnd::GetMinY_UsingRangeX(double &dbMinY, int iOverlapIndex)
{
	if ( m_dbMinX_AutoRangeY > m_dbMaxX_AutoRangeY )
	{
		return false;
	}
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}
	int iDataSize = m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize();
	if ( iDataSize <= 0 )
	{
		return false;
	}

	int i = 0, iCount = 0;
	double dbDataX = 0., dbDataY = 0.;
	double dbReturn = DBL_MAX;

	for ( i = 0; i < iDataSize; i++ )
	{
		dbDataX = m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(i);
		dbDataY = m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(i);

		if ( dbDataX < m_dbMinX_AutoRangeY || dbDataX > m_dbMaxX_AutoRangeY )
		{
			continue;
		}

		if ( dbReturn > dbDataY )
		{
			dbReturn = dbDataY;
		}

		iCount++;
	}

	if ( iCount <= 0 )
	{
		return false;
	}

	dbMinY = dbReturn;

	return true;
}

//! Added by LHW [2009/3/5]
bool CGraph2DWnd::GetMaxY_UsingRangeX(double &dbMaxY, int iOverlapIndex)
{
	if ( m_dbMinX_AutoRangeY > m_dbMaxX_AutoRangeY )
	{
		return false;
	}
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}
	int iDataSize = m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize();
	if ( iDataSize <= 0 )
	{
		return false;
	}

	int i = 0, iCount = 0;
	double dbDataX = 0., dbDataY = 0.;
	double dbReturn = DBL_MAX * (-1.);

	for ( i = 0; i < iDataSize; i++ )
	{
		dbDataX = m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(i);
		dbDataY = m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(i);

		if ( dbDataX < m_dbMinX_AutoRangeY || dbDataX > m_dbMaxX_AutoRangeY )
		{
			continue;
		}

		if ( dbReturn < dbDataY )
		{
			dbReturn = dbDataY;
		}

		iCount++;
	}

	if ( iCount <= 0 )
	{
		return false;
	}

	dbMaxY = dbReturn;

	return true;
}

//! 눈에 보이는 그래프의 X축 최소값, Added by LHW [2008/4/18]
double CGraph2DWnd::GetVisualMinX()
{
	return m_XMapper.m_dbXDataMin;
}

//! 눈에 보이는 그래프의 X축 최대값, Added by LHW [2008/4/18]
double CGraph2DWnd::GetVisualMaxX()
{
	return m_XMapper.m_dbXDataMax;
}

//! 눈에 보이는 그래프의 Y축 최소값, Added by LHW [2008/4/18]
bool CGraph2DWnd::GetVisualMinY(double &dbMinY, int iOverlapIndex)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}

	strYRangeMapper strYMapper;
	strYMapper = m_arrYMapper.GetAt(iOverlapIndex);
	dbMinY = strYMapper.m_dbYDataMin;

	return true;
}

//! 눈에 보이는 그래프의 Y축 최대값, Added by LHW [2008/4/18]
bool CGraph2DWnd::GetVisualMaxY(double &dbMaxY, int iOverlapIndex)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}

	strYRangeMapper strYMapper;
	strYMapper = m_arrYMapper.GetAt(iOverlapIndex);
	dbMaxY = strYMapper.m_dbYDataMax;

	return true;
}

//! Added by LHW [2008/7/02]
bool CGraph2DWnd::GetAutoRangeMinX(double &dbMinX)
{
	if ( m_pPlotResource == NULL )
	{
		return false;
	}

	dbMinX = ((CGraph2D_Resource*)m_pPlotResource)->m_dbAutoRangeMin;

	return true;
}

//! Added by LHW [2008/7/02]
bool CGraph2DWnd::GetAutoRangeMaxX(double &dbMaxX)
{
	if ( m_pPlotResource == NULL )
	{
		return false;
	}

	dbMaxX = ((CGraph2D_Resource*)m_pPlotResource)->m_dbAutoRangeMax;

	return true;
}

//! Added by LHW [2008/7/02]
bool CGraph2DWnd::GetAutoRangeMinY(double &dbMinY, int iOverlapIndex)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}

	dbMinY = m_arrResourceY.GetAt(iOverlapIndex)->m_dbAutoRangeMin;

	return true;
}

//! Added by LHW [2008/7/02]
bool CGraph2DWnd::GetAutoRangeMaxY(double &dbMaxY, int iOverlapIndex)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}

	dbMaxY = m_arrResourceY.GetAt(iOverlapIndex)->m_dbAutoRangeMax;

	return true;
}

//! Added by LHW [2008/4/15] : 해당 그래프의 최대값의 index를 반환, 오류가 발생하면 -1을 반환
int CGraph2DWnd::GetDataIndexofMaxValue(int iOverlapIndex)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return -1;
	}

	int iDataSize = m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize();
	if ( iDataSize <= 0 )
	{
		return -1;
	}

	return m_arrPlotData.GetAt(iOverlapIndex)->m_iMaxIndex;
}

//! Added by LHW [2009/2/27]
int CGraph2DWnd::GetDataIndexofMaxValue(int iOverlapIndex, int iStartDataIndex, int iEndDataIndex)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return -1;
	}

	int iDataSize = m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize();
	if ( iDataSize <= 0 )
	{
		return -1;
	}

	if ( iStartDataIndex < 0 )
	{
		iStartDataIndex = 0;
	}
	if ( iStartDataIndex >= iDataSize )
	{
		iStartDataIndex = iDataSize - 1;
	}
	if ( iEndDataIndex < 0 )
	{
		iEndDataIndex = 0;
	}
	if ( iEndDataIndex >= iDataSize )
	{
		iEndDataIndex = iDataSize - 1;
	}
	
	if ( iStartDataIndex > iEndDataIndex )
	{
		return -1;
	}

	int i = 0, iReturnIndex = -1;
	double dbMaxTemp = DBL_MAX * (-1.);
	double dbTemp = 0.;

	for ( i = iStartDataIndex; i < iEndDataIndex; i++ )
	{
		dbTemp = m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(i);
		if ( dbTemp > dbMaxTemp )
		{
			dbMaxTemp = dbTemp;
			iReturnIndex = i;			
		}
	}

	return iReturnIndex;
}

//! Added by LHW [2009/2/27]
int CGraph2DWnd::GetDataIndexofMaxValue(int iOverlapIndex, double dbStartValue, double dbEndValue)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return -1;
	}

	int iDataSize = m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize();
	if ( iDataSize <= 0 )
	{
		return -1;
	}

	if ( dbStartValue > dbEndValue )
	{
		return -1;
	}

	int i = 0, iReturnIndex = -1;
	double dbMaxTemp = DBL_MAX * (-1.);
	double dbTempX = 0., dbTempY = 0.;

	for ( i = 0; i < iDataSize; i++ )
	{
		dbTempX = m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(i);
		if ( dbTempX < dbStartValue )
		{
			continue;
		}
		if ( dbTempX > dbEndValue )
		{
			break;
		}

		dbTempY = m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(i);
		if ( dbTempY > dbMaxTemp )
		{
			dbMaxTemp = dbTempY;
			iReturnIndex = i;			
		}
	}

	return iReturnIndex;
}

//! Added by LHW [2009/2/27]
int CGraph2DWnd::GetDataIndexofMaxValue(int iOverlapIndex, COleDateTime timeStart, COleDateTime timeEnd)
{
	return GetDataIndexofMaxValue(iOverlapIndex, (double)(timeStart.m_dt), (double)(timeEnd.m_dt));
}

//! Modify by LHW [2008/4/2]
int CGraph2DWnd::GetRealDataSize(bool bShow)
{
	int i = 0, iReturn = 0, iDataSize = 0;
	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize > 0 )
	{
		if ( bShow == true )
		{
			for ( i = 0; i < iGraphSize; i++ )
			{
				if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.bShowGraph == true )
				{
					iDataSize = m_arrPlotData.GetAt(i)->GetPointSize();
					if ( iReturn < iDataSize )
					{
						iReturn = iDataSize;
					}
				}
			}
		}
		else
		{
			for ( i = 0; i < iGraphSize; i++ )
			{
				iDataSize = m_arrPlotData.GetAt(i)->GetPointSize();
				if ( iReturn < iDataSize )
				{
					iReturn = iDataSize;
				}
			}
		}		
	}
	return iReturn;
}

//! Added by LHW [2008/8/02]
int CGraph2DWnd::GetRealDataSize(int iOverlapIndex, bool bShow)
{
	int iGraphSize = GetPlotBufferSize();
	if ( iOverlapIndex < 0 || iOverlapIndex >= iGraphSize )
	{
		return -1;
	}

	if ( bShow == true && m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.bShowGraph == false )
	{
		return 0;
	}

	return m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize();
}

//! Modify by LHW [2008/4/2]
int CGraph2DWnd::GetRealVisualDataSize(bool bShow)
{
	int i = 0, iReturn = 0;
	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize > 0 )
	{
		if ( bShow == true )
		{
			for ( i = 0; i < iGraphSize; i++ )
			{
				if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.bShowGraph == true )
				{
					if ( iReturn < m_arrPlotData.GetAt(i)->m_iVisualDataSize )
					{
						iReturn = m_arrPlotData.GetAt(i)->m_iVisualDataSize;
					}
				}
			}
		}
		else
		{
			for ( i = 0; i < iGraphSize; i++ )
			{
				if ( iReturn < m_arrPlotData.GetAt(i)->m_iVisualDataSize )
				{
					iReturn = m_arrPlotData.GetAt(i)->m_iVisualDataSize;
				}
			}
		}		
	}
	return iReturn;
}

//! Added by LHW [2008/11/18]
int CGraph2DWnd::GetRealVisualDataSize(int iOverlapIndex, bool bShow)
{
	int iGraphSize = GetPlotBufferSize();
	if ( iOverlapIndex < 0 || iOverlapIndex >= iGraphSize )
	{
		return -1;
	}

	if ( bShow == true && m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.bShowGraph == false )
	{
		return 0;
	}

	return m_arrPlotData.GetAt(iOverlapIndex)->m_iVisualDataSize;
}

//! Added by LHW [2008/11/18]
bool CGraph2DWnd::GetVisualDataIndex(int iOverlapIndex, int &iStartDataIndex, int &iEndDataIndex)
{
	int iGraphSize = GetPlotBufferSize();
	if ( iOverlapIndex < 0 || iOverlapIndex >= iGraphSize )
	{
		return false;
	}

	if ( m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.bShowGraph == false )
	{
		return false;
	}
	
	iStartDataIndex = m_arrPlotData.GetAt(iOverlapIndex)->m_iVisualRealDataStartIndex;
	iEndDataIndex = m_arrPlotData.GetAt(iOverlapIndex)->m_iVisualRealDataEndIndex;

	return true;
}

//! Modify by LHW [2008/4/2]
bool CGraph2DWnd::IsAutoRange(bool bDirectionX, bool bDirectionY, bool bShow)
{
	if ( m_pPlotResource == NULL )
	{
		return false;
	}

	bool bAutoRange = false;

	if ( bDirectionX == true )
	{
		bAutoRange = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bAutoRange;
		if ( bAutoRange == false )
		{
			return false;
		}
	}

	if ( bDirectionY == true )
	{
		int i = 0, iGraphSize = GetPlotBufferSize();
		if ( iGraphSize > 0 )
		{
			if ( bShow == true )
			{
				for ( i = 0; i < iGraphSize; i++ )
				{
					if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.bShowGraph == true )
					{
						bAutoRange = m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.bAutoRange;
						if ( bAutoRange == false )
						{
							return false;
						}
					}
				}
			}
			else
			{
				for ( i = 0; i < iGraphSize; i++ )
				{
					bAutoRange = m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.bAutoRange;
					if ( bAutoRange == false )
					{
						return false;
					}
				}
			}
		}
	}

	return true;
}

bool CGraph2DWnd::IsShowGraph()
{
	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize > 0 )
	{
		for ( int i = 0; i < iGraphSize; i++ )
		{
			if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.bShowGraph == true && m_arrPlotData.GetAt(i)->GetPointSize() > 0 )
			{
				return true;
			}
		}
	}

	return false;
}

bool CGraph2DWnd::IsScreenDrawing()
{
	return m_bDrawing;
}

//! Modify by LHW [2008/6/14] : ReCalcChildCursorPos 추가
//! Modify by LHW [2008/6/15] : UpdateCursorDataIndex_Childcursor 추가
//!	반드시 ReCalcCursorPos, UpdateCursorDataIndex_Childcursor, ReCalcChildCursorPos 순으로 호출해야 함
//! Modify by LHW [2009/2/25] : 배경 이미지 그리는 부분 추가
bool CGraph2DWnd::Display(CDC *pDC, const CRect crDraw, bool bPrintFlag)
{
	//!  현재 윈도우의 사각 영역 확인
	if ( crDraw.Width() <= 2 || crDraw.Height() <= 2 )
	{
		return false;
	}

	if ( bPrintFlag == false )
	{
		//!  DC가 생성되지 않았거나 설정이 변경되었을 경우
		if ( !m_bCreateDC || m_bChanged )
		{
			m_CurRect = crDraw;

			//!  관련 정보 초기화
			DrawInit(pDC);

			ReadyDraw(&m_DrawDC);

			ReCalcCursorPos();
			//UpdateCursorDataIndex_Childcursor();
			ReCalcChildCursorPos();
			CalcAuxCursor();
			CalcRegionCursor();	//! Added by LHW [2008/11/28]

			m_bCreateDC = true;
			m_bChanged = false;
		}

		DrawBackground(&m_DrawDC);

		if ( m_bDrawBackGroundImage == true )
		{
			if ( m_bmpBackground.GetPixelPtr() != 0 )
			{
				int iX = crDraw.left;
				while ( iX < crDraw.right )
				{
					m_bmpBackground.DrawDIB(&m_DrawDC, iX, crDraw.top);
					iX += m_bmpBackground.GetWidth();
				}
			}
		}
	
		DrawZoomArea(&m_DrawDC);
		DrawAxis(&m_DrawDC);
		DrawInfo(&m_DrawDC);
		DrawData(&m_DrawDC);
		DrawValueLineX(&m_DrawDC);	//! Added by LHW [2008/4/19]
		DrawValueLineY(&m_DrawDC);	//! Added by LHW [2008/3/29]
		DrawAuxCursor(&m_DrawDC);	//! Added by LHW [2008/4/1]
		DrawChildCursor(&m_DrawDC);	//! Added by LHW [2008/6/13]
		DrawRegionCursor(&m_DrawDC);//! Added by LHW [2008/11/28]
		DrawCursor(&m_DrawDC);

		pDC->BitBlt(crDraw.left, crDraw.top, crDraw.Width(), crDraw.Height(), &m_DrawDC, 0, 0, SRCCOPY);
	}
	else
	{
		//! 인쇄를 할 때에는 메모리 DC 사용으로 인해 문제가 생길 수 있음
		m_CurRect = crDraw;
		ReadyDraw(pDC);
		ReCalcCursorPos();
		//UpdateCursorDataIndex_Childcursor();
		ReCalcChildCursorPos();
		CalcAuxCursor();
		CalcRegionCursor();	//! Added by LHW [2008/11/28]

		m_bCreateDC = true;
		m_bChanged = false;

		DrawBackground(pDC);

		if ( m_bDrawBackGroundImage == true )
		{
			if ( m_bmpBackground.GetPixelPtr() != 0 )
			{
				int iX = crDraw.left;
				while ( iX < crDraw.right )
				{
					m_bmpBackground.DrawDIB(pDC, iX, crDraw.top);
					iX += m_bmpBackground.GetWidth();
				}
			}
		}
		
		DrawZoomArea(pDC);
		DrawAxis(pDC);
		DrawInfo(pDC);
		DrawData(pDC);
		DrawValueLineX(pDC);	//! Added by LHW [2008/4/19]
		DrawValueLineY(pDC);	//! Added by LHW [2008/3/29]
		DrawAuxCursor(pDC);		//! Added by LHW [2008/4/1]
		DrawChildCursor(pDC);	//! Added by LHW [2008/6/13]
		DrawRegionCursor(pDC);	//! Added by LHW [2008/11/28]
		DrawCursor(pDC);
	}

	return true;
}

//! Modify by LHW [2008/4/04] : Auto Range 설정 부분 수정
//! Modify by LHW [2008/4/10] : m_graphRect 관련 부분 수정, 1 pixel의 빈 여백 때문
//! modify by LHW [2008/4/17] : X, Y축 Min, Max 값 설정 부분 수정
//! Modify by LHW [2008/4/19] : X축 특정값 표시선 부분 추가
//! Modify by LHW [2008/5/23] : SetDataPointRect 함수 추가
//! Modify by LHW [2008/6/13] : 자식 커서 관련 추가
//! Modify by LHW [2008/6/30] : X, Y축의 Margin 계산 부분 수정, X, Y축의 소수점 자리수 자동 설정 기능 추가
//! Modify by LHW [2008/7/01] : m_bAutoDrawCompleteMsg 추가, X, Y축 AutoRange 설정에 대칭 기능 추가, 지수값으로 눈금을 그릴 때의 여유값 부분 수정
//!								X, Y 축 Range 설정 부분 위치 수정, Y축을 보여줄 X 좌표 설정 부분 수정
//! Modify by LHW [2008/7/02] : X축 소수점 자리수 자동 설정 부분 오류 수정, Auto Range일 때의 값 저장 추가, 소수점에 따라 Grid의 X축 간격 조절 기능 추가
//! Modify by LHW [2008/7/24] : X,Y축의 문자열 표시 관련 수정, 여백 설정 부분 수정, Grid Margin 값 계산
//! Modify by LHW [2008/7/31] : m_AxisLeftRect, m_AxisRightRect 설정 부분 추가
//! Modify by LHW [2008/8/01] : m_AxisCaptionRect 설정 부분 추가
//! Modify by LHW [2008/8/02] : 소수점 자리수 설정부분에 GetCalcData 함수 사용하도록 수정
//! Modify by LHW [2008/8/07] : E_GRAPH2D_XY_CAPTION_POS_UNITE_Y일 때의 iYMinGap 계산 오류 수정
//! Modify by LHW [2008/8/11] : X축이 시간일 때, X축 단위 표시 부분의 오류 수정
//! Modify by LHW [2008/8/18] : WM_GRAPH2D_DECIDE_TIME_X_AXIS 메시지 발생 부분 추가
//! Modify by LHW [2008/8/23] : 함수식으로 그려지는 그래프의 리소스 설정 부분 추가
//! Modify by LHW [2008/8/25] : 함수식으로 그려지는 그래프를 고려하여 Auto Range 설정하도록 수정
//! Modify by LHW [2008/8/26] : 함수식으로 그려지는 그래프 부분의 Y축 최소, 최대값 구하는 부분의 위치를 변경
//! Modify by LHW [2008/9/2] : X,Y축 Auto Range일 때의 Min, Max 값을 반드시 게산하도록 수정 (현재 Manual Range이더라도 Auto Range일 때의 값을 알수 있도록)
//! Modify by LHW [2008/10/24] : E_GRAPH2D_XY_CAPTION_POS_ONLY_XY 추가
//! Modify by LHW [2008/10/25] : GetStringMaxWidth_AxisY 추가, Y축을 보여줄 X 좌표 설정 부분 수정
//! Modify by LHW [2008/11/18] : 그래프의 눈에 보이는 부분의 index를 구하는 부분의 수정
//! Modify by LHW [2008/11/28] : m_AxisCaptionRect 설정 부분 수정, m_iAxisCaptionMarginX 설정 부분 추가
//! Modify by LHW [2008/11/30] : m_iRegionCursorMargin 추가
//! Modify by LHW [2008/12/1] : 영역 표시 커서 리소스 재설정 부분 추가
//! Modify by LHW [2008/12/14] : 영역 표시 커서를 고려하여 X, Y축 AutoRange를 설정하도록 수정
//! Modify by LHW [2008/12/27] : E_GRAPH2D_XY_CAPTION_POS_ONE_Y 관련 추가, m_bXScaleLock, m_bYScaleLock 추가
//! Modify by LHW [2009/2/2] : m_AxisLeftRect, m_AxisRightRect를 m_crAxisY_Left_Event, m_crAxisY_Right_Event로 변경, m_crAxisX_Event 추가
//! Modify by LHW [2009/2/3] : Y축선의 문자열 크기 설정 부분 추가, Y축선의 문자열을 표시할 여백 설정 부분 추가
//! Modify by LHW [2009/2/4] : 각 축의 최소, 최대값 처리에 bMaxOperation, bMinOperation 관련 부분 추가, bAutoRangeGridSize, iAutoRangeGridSize 관련 부분 추가
//! Modify by LHW [2009/2/5] : bMaxOperation, bMinOperation 관련 부분 수정
//! Modify by LHW [2009/2/26] : 제목 문자열 폰트 관련 작업 수정
//! Modify by LHW [2009/2/27] : m_bAlwaysInitYPos 관련 추가
//! Modify by LHW [2009/3/5] : m_bAutoRangeY_UsingRangeX 관련 추가
//! Modify by LHW [2009/3/6] : m_bAutoRangeY_UsingRangeX관련 오류 수정
//! Modify by LHW [2009/3/9] : Y축 선의 문자열이 그래프 오른쪽 바깥에 위치할 경우 부분 수정
//! Modify by LHW [2009/5/28] : Y축 Range 설정, bMarginFlag 부분 오류 수정
//! Modify by LHW [2009/5/30] : E_GRAPH2D_AUTO_RANGE_RESERVED_STEP 적용
//! Modify by LHW [2012/12/20] : E_GRAPH2D_XY_CAPTION_POS_ONLY_X 적용
//! Modify by LHW [2013/3/26] : bDirection_Plus 관련 처리 적용
//! Modify by LHW [2013/4/1] : X, Y축 자동 소수점 자리수 설정 기능 추가
bool CGraph2DWnd::ReadyDraw(CDC *pDC)
{
	int iGraphSize = GetPlotBufferSize();
	if ( m_pPlotResource == NULL || iGraphSize <= 0  )
	{
		return false;
	}
	
	int i = 0, j = 0;

	m_iCursorMargin = (int)((double)(m_CurRect.Width()) * 0.0014);
	if ( m_iCursorMargin < 2 )
	{
		m_iCursorMargin = 2;
	}

	m_iChildCursorMargin = (int)((double)(m_CurRect.Width()) * 0.0014);
	if ( m_iChildCursorMargin < 2 )
	{
		m_iChildCursorMargin = 2;
	}

	m_iRegionCursorMargin = (int)((double)(m_CurRect.Width()) * 0.0014);
	if ( m_iRegionCursorMargin < 2 )
	{
		m_iRegionCursorMargin = 2;
	}

	//! 색상 변화등을 반영하기 위해 리소스 객체를 지우고 다시 생성
	//! 글자 크기를 사각 영역의 크기에 따라 결정
	int iNewBaseFontHeight = (int)((double)(m_CurRect.Height()) * 0.0426666);
	int iNewBaseFontHeightFromWidth = (int)((double)(m_CurRect.Width()) * 0.008038585 * 1.7422);
	if ( iNewBaseFontHeight > iNewBaseFontHeightFromWidth )
	{
		iNewBaseFontHeight = iNewBaseFontHeightFromWidth;
	}
	//iNewBaseFontHeight = -MulDiv(iNewBaseFontHeight, GetDeviceCaps(pDC->GetSafeHdc(), LOGPIXELSY), 72);
	iNewBaseFontHeight = -iNewBaseFontHeight;
	if ( abs(iNewBaseFontHeight) < 10 )
	{
		iNewBaseFontHeight = -10;
	}
	if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.bGridFontHeight == true )
	{
		((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.iGridFontHeight = iNewBaseFontHeight;
	}
	if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.bCursorFontHeight == true )
	{
		((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.iCursorFontHeight = iNewBaseFontHeight;
	}
	if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.bLegendFontHeight == true )
	{
		((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.iLegendFontHeight = iNewBaseFontHeight;
	}
	if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strMainTitleInfo.bTitleFontHeight == true )
	{
		((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strMainTitleInfo.iTitleFontHeight = (int)(((double)iNewBaseFontHeight) * 1.1);
	}
	if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strSubTitleInfo.bTitleFontHeight == true )
	{
		((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strSubTitleInfo.iTitleFontHeight = iNewBaseFontHeight;
	}
	((CGraph2D_Resource*)m_pPlotResource)->ReleaseResource();
	((CGraph2D_Resource*)m_pPlotResource)->SetResource();

	for ( i = 0; i < iGraphSize; i++ )
	{
		m_arrResourceY.GetAt(i)->ReleaseResource();
		m_arrResourceY.GetAt(i)->SetResource();
	}
	
	int iXValueLinesize = (int)(m_arrValueLineX.GetSize());
	if ( iXValueLinesize > 0 )
	{
		for ( i = 0; i < iXValueLinesize; i++ )
		{
			m_arrValueLineX.GetAt(i)->ReleaseResource();
			m_arrValueLineX.GetAt(i)->m_iFontHeight = (int)(((double)iNewBaseFontHeight) * 0.7);
			m_arrValueLineX.GetAt(i)->SetResource();
		}
	}

	int iYValueLinesize = (int)(m_arrValueLineY.GetSize());
	if ( iYValueLinesize > 0 )
	{
		for ( i = 0; i < iYValueLinesize; i++ )
		{
			m_arrValueLineY.GetAt(i)->ReleaseResource();
			m_arrValueLineY.GetAt(i)->m_iFontHeight = (int)(((double)iNewBaseFontHeight) * 0.7);
			m_arrValueLineY.GetAt(i)->SetResource();
		}
	}

	int iGraphEquationSize = (int)(m_arrGraphEquation.GetSize());
	if ( iGraphEquationSize > 0 )
	{
		for ( i = 0; i < iGraphEquationSize; i++ )
		{
			m_arrGraphEquation.GetAt(i)->ReleaseResource();
			m_arrGraphEquation.GetAt(i)->SetResource();
		}
	}

	int iChildCursorSize = (int)(m_arrChildCursor.GetSize());
	if ( iChildCursorSize > 0 )
	{
		for ( i = 0; i < iChildCursorSize; i++ )
		{
			if ( m_arrChildCursor.GetAt(i)->m_strCursorInfo.bCursorFontHeight == true )
			{
				m_arrChildCursor.GetAt(i)->m_strCursorInfo.iCursorFontHeight = iNewBaseFontHeight;
			}

			m_arrChildCursor.GetAt(i)->ReleaseResource();
			m_arrChildCursor.GetAt(i)->SetResource();
		}
	}

	int iRegionCursorSize = (int)(m_arrRegionCursor.GetSize());
	if ( iRegionCursorSize > 0 )
	{
		for ( i = 0; i < iRegionCursorSize; i++ )
		{
			if ( m_arrRegionCursor.GetAt(i)->m_strCursorInfo.bCursorFontHeight == true )
			{
				m_arrRegionCursor.GetAt(i)->m_strCursorInfo.iCursorFontHeight = iNewBaseFontHeight;
			}

			m_arrRegionCursor.GetAt(i)->ReleaseResource();
			m_arrRegionCursor.GetAt(i)->SetResource();
		}
	}

	//! <------------------------------------------------------------------------------------------------------------
	//! 보조 커서 관련 리소스 재 생성, Added by LHW [2008/3/31]
	//! Modify by LHW [2008/5/9] : iRadius 크기 작게 수정
	int iAuxCursorGroupSize = GetCurrentAuxCursorGroupSize();
	if ( iAuxCursorGroupSize > 0 )
	{
		for ( i = 0; i < iAuxCursorGroupSize; i++ )
		{
			if ( m_arrAuxCursorGroup.GetAt(i)->m_strGroupInfo.bRadius == true )
			{				
				//m_arrAuxCursorGroup.GetAt(i)->m_strGroupInfo.iRadius = (int)(((double)(abs(iNewBaseFontHeight))) * 0.5);
				m_arrAuxCursorGroup.GetAt(i)->m_strGroupInfo.iRadius = (int)(((double)(abs(iNewBaseFontHeight))) * 0.25);
				if ( m_arrAuxCursorGroup.GetAt(i)->m_strGroupInfo.iRadius < 4 )
				{
					m_arrAuxCursorGroup.GetAt(i)->m_strGroupInfo.iRadius = 4;
				}
			}
			if ( m_arrAuxCursorGroup.GetAt(i)->m_strGroupInfo.bFontHeight == true )
			{
				m_arrAuxCursorGroup.GetAt(i)->m_strGroupInfo.iFontHeight = (int)(((double)iNewBaseFontHeight) * 0.7);
			}
		}

		for ( i = 0; i < iAuxCursorGroupSize; i++ )
		{
			m_arrAuxCursorGroup.GetAt(i)->ReleaseResource();
			m_arrAuxCursorGroup.GetAt(i)->SetResource();
		}
	}
	//! ------------------------------------------------------------------------------------------------------------>


	bool bMarginFlag = false;
	double dbRangeMinTemp = 0., dbRangeMaxTemp = 0., dbRangeSizeTemp = 0., dbMarginTemp = 0.;

	//! X축 Range 설정
	//if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bAutoRange == true )
	if ( m_bXScaleLock == false )
	{
		bMarginFlag = false;

		if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.eAutoRangeReservedMin == E_GRAPH2D_AUTO_RANGE_RESERVED_FORCED )
		{
			dbRangeMinTemp = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbAutoRangeReservedMin;
		}
		else
		{
			dbRangeMinTemp = GetRealMinX(m_bXAutoRangeEquation, m_bXAutoRangeRegionCursor, m_bXAutoRangeShowGraph);

			if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.eAutoRangeReservedMin == E_GRAPH2D_AUTO_RANGE_RESERVED_CONSIDER )
			{
				if ( dbRangeMinTemp > ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbAutoRangeReservedMin )
				{
					dbRangeMinTemp = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbAutoRangeReservedMin;
				}
			}

			if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.eAutoRangeReservedMin == E_GRAPH2D_AUTO_RANGE_RESERVED_STEP )
			{
				if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bMarginIncludeMin == false )
				{
					dbRangeMinTemp = GetCompareXMinBound(dbRangeMinTemp);
				}
			}
		}

		if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.eAutoRangeReservedMax == E_GRAPH2D_AUTO_RANGE_RESERVED_FORCED )
		{
			dbRangeMaxTemp = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbAutoRangeReservedMax;
		}
		else
		{
			dbRangeMaxTemp = GetRealMaxX(m_bXAutoRangeEquation, m_bXAutoRangeRegionCursor, m_bXAutoRangeShowGraph);

			if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.eAutoRangeReservedMax == E_GRAPH2D_AUTO_RANGE_RESERVED_CONSIDER )
			{
				if ( dbRangeMaxTemp < ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbAutoRangeReservedMax )
				{
					dbRangeMaxTemp = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbAutoRangeReservedMax;
				}
			}

			if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.eAutoRangeReservedMax == E_GRAPH2D_AUTO_RANGE_RESERVED_STEP )
			{
				if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bMarginIncludeMax == false )
				{
					dbRangeMaxTemp = GetCompareXMaxBound(dbRangeMaxTemp);
				}
			}
		}

		if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bSymmetry == true )
		{
			dbRangeMaxTemp = __max(fabs(dbRangeMaxTemp), fabs(dbRangeMinTemp));
			dbRangeMinTemp = dbRangeMaxTemp * (-1.);
		}

		dbRangeSizeTemp = dbRangeMaxTemp - dbRangeMinTemp;

		if ( fabs(dbRangeSizeTemp) < 0.0000001 )
		{
			if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bMarginZero == true )
			{
				dbMarginTemp = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbMarginZero;
				bMarginFlag = true;				
			}
		}
		else
		{
			switch( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.eMarginType )
			{
			case E_GRAPH2D_RANGE_MARGIN_PERCENT:
				{
					dbMarginTemp = dbRangeSizeTemp * (((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbMargin / 100.);
					bMarginFlag = true;		
				}
				break;
			case E_GRAPH2D_RANGE_MARGIN_MAX_PERCENT:
				{
					dbMarginTemp = __max(fabs(dbRangeMaxTemp), fabs(dbRangeMinTemp)) * (((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbMargin / 100.);
					bMarginFlag = true;
				}
				break;
			case E_GRAPH2D_RANGE_MARGIN_VALUE:
				{
					dbMarginTemp = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbMargin;
					bMarginFlag = true;	
				}
				break;
			}
		}

		if ( bMarginFlag == true )
		{
			if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.eAutoRangeReservedMin == E_GRAPH2D_AUTO_RANGE_RESERVED_NONE )
			{
				dbRangeMinTemp -= dbMarginTemp;
			}
			if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.eAutoRangeReservedMax == E_GRAPH2D_AUTO_RANGE_RESERVED_NONE )
			{
				dbRangeMaxTemp += dbMarginTemp;
			}

			if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.eAutoRangeReservedMin == E_GRAPH2D_AUTO_RANGE_RESERVED_STEP )
			{
				if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bMarginIncludeMin == true )
				{
					dbRangeMinTemp = GetCompareXMinBound(dbRangeMinTemp);
				}
			}
			if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.eAutoRangeReservedMax == E_GRAPH2D_AUTO_RANGE_RESERVED_STEP )
			{
				if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bMarginIncludeMax == true )
				{
					dbRangeMaxTemp = GetCompareXMaxBound(dbRangeMaxTemp);
				}
			}
		}

		if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bAutoRange == true )
		{
			if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bMaxOperation == true )
			{
				if ( dbRangeMaxTemp > 0. )
				{
					dbRangeMaxTemp = DecideMinMaxOperation(dbRangeMaxTemp);
				}				
			}
			if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bMinOperation == true )
			{
				if ( dbRangeMinTemp < 0. )
				{
					dbRangeMinTemp = DecideMinMaxOperation(dbRangeMinTemp);
				}
			}
			if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bSymmetry == true )
			{
				dbRangeMaxTemp = __max(fabs(dbRangeMaxTemp), fabs(dbRangeMinTemp));
				dbRangeMinTemp = dbRangeMaxTemp * (-1.);
			}

			if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bAutoRangeGridSize = true )
			{
				((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.iGridSize = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.iAutoRangeGridSize;
			}

			((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbManualMin = dbRangeMinTemp;
			((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbManualMax = dbRangeMaxTemp;
		}
		
		((CGraph2D_Resource*)m_pPlotResource)->m_dbAutoRangeMin = dbRangeMinTemp;
		((CGraph2D_Resource*)m_pPlotResource)->m_dbAutoRangeMax = dbRangeMaxTemp;
	}


	double dbRangeTemp = 0., dbRangeTempMax = 0., dbRangeTempMin = 0.;
	bool bGridTextPrecisionModifyFlag = false, bCursorTextPrecisionModifyFlag = false;

	//! X축 소수점 자리수 자동 설정	
	if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.eGridTextType == E_GRAPH2D_GRID_DOUBLE )
	{
		if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bAutoGridTextPrecision == true )
		{
			dbRangeTempMax = GetCalcData(((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbManualMax, true, false);
			dbRangeTempMin = GetCalcData(((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbManualMin, true, false);
			dbRangeTemp = dbRangeTempMax - dbRangeTempMin;

			if ( dbRangeTemp >= 1000. )
			{
				((CGraph2D_Resource*)m_pPlotResource)->m_iGridTextPrecision = 0;
				((CGraph2D_Resource*)m_pPlotResource)->m_eGridTextType = E_GRAPH2D_GRID_DOUBLE;
			}
			else if ( dbRangeTemp >= 100. )
			{
				((CGraph2D_Resource*)m_pPlotResource)->m_iGridTextPrecision = 1;
				((CGraph2D_Resource*)m_pPlotResource)->m_eGridTextType = E_GRAPH2D_GRID_DOUBLE;
			}
			else if ( dbRangeTemp >= 10. )
			{
				((CGraph2D_Resource*)m_pPlotResource)->m_iGridTextPrecision = 2;
				((CGraph2D_Resource*)m_pPlotResource)->m_eGridTextType = E_GRAPH2D_GRID_DOUBLE;
			}
			else if ( dbRangeTemp >= 0.1 )
			{
				((CGraph2D_Resource*)m_pPlotResource)->m_iGridTextPrecision = 3;
				((CGraph2D_Resource*)m_pPlotResource)->m_eGridTextType = E_GRAPH2D_GRID_DOUBLE;
			}
			else if ( dbRangeTemp >= 0.01 )
			{
				((CGraph2D_Resource*)m_pPlotResource)->m_iGridTextPrecision = 4;
				((CGraph2D_Resource*)m_pPlotResource)->m_eGridTextType = E_GRAPH2D_GRID_DOUBLE;
			}
			else if ( dbRangeTemp >= 0.001 )
			{
				((CGraph2D_Resource*)m_pPlotResource)->m_iGridTextPrecision = 5;
				((CGraph2D_Resource*)m_pPlotResource)->m_eGridTextType = E_GRAPH2D_GRID_DOUBLE;
			}
			else if ( dbRangeTemp >= 0.0001 )
			{
				((CGraph2D_Resource*)m_pPlotResource)->m_iGridTextPrecision = 6;
				((CGraph2D_Resource*)m_pPlotResource)->m_eGridTextType = E_GRAPH2D_GRID_DOUBLE;
			}
			else
			{
				((CGraph2D_Resource*)m_pPlotResource)->m_iGridTextPrecision = 7;
				((CGraph2D_Resource*)m_pPlotResource)->m_eGridTextType = E_GRAPH2D_GRID_DOUBLE;
				//((CGraph2D_Resource*)m_pPlotResource)->m_iGridTextPrecision = 3;
				//((CGraph2D_Resource*)m_pPlotResource)->m_eGridTextType = E_GRAPH2D_GRID_EXP;
			}
			bGridTextPrecisionModifyFlag = true;
		}		
		if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bAutoCursorTextPrecision == true )
		{
			dbRangeTempMax = GetCalcData(((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbManualMax, true, true);
			dbRangeTempMin = GetCalcData(((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbManualMin, true, true);
			dbRangeTemp = dbRangeTempMax - dbRangeTempMin;

			if ( dbRangeTemp >= 1000. )
			{
				((CGraph2D_Resource*)m_pPlotResource)->m_iCursorTextPrecision = 0;
				((CGraph2D_Resource*)m_pPlotResource)->m_eCursorTextType = E_GRAPH2D_GRID_DOUBLE;
			}
			else if ( dbRangeTemp >= 100. )
			{
				((CGraph2D_Resource*)m_pPlotResource)->m_iCursorTextPrecision = 1;
				((CGraph2D_Resource*)m_pPlotResource)->m_eCursorTextType = E_GRAPH2D_GRID_DOUBLE;
			}
			else if ( dbRangeTemp >= 10. )
			{
				((CGraph2D_Resource*)m_pPlotResource)->m_iCursorTextPrecision = 2;
				((CGraph2D_Resource*)m_pPlotResource)->m_eCursorTextType = E_GRAPH2D_GRID_DOUBLE;
			}
			else if ( dbRangeTemp >= 0.1 )
			{
				((CGraph2D_Resource*)m_pPlotResource)->m_iCursorTextPrecision = 3;
				((CGraph2D_Resource*)m_pPlotResource)->m_eCursorTextType = E_GRAPH2D_GRID_DOUBLE;
			}
			else if ( dbRangeTemp >= 0.01 )
			{
				((CGraph2D_Resource*)m_pPlotResource)->m_iCursorTextPrecision = 4;
				((CGraph2D_Resource*)m_pPlotResource)->m_eCursorTextType = E_GRAPH2D_GRID_DOUBLE;
			}
			else if ( dbRangeTemp >= 0.001 )
			{
				((CGraph2D_Resource*)m_pPlotResource)->m_iCursorTextPrecision = 5;
				((CGraph2D_Resource*)m_pPlotResource)->m_eCursorTextType = E_GRAPH2D_GRID_DOUBLE;
			}
			else if ( dbRangeTemp >= 0.0001 )
			{
				((CGraph2D_Resource*)m_pPlotResource)->m_iCursorTextPrecision = 6;
				((CGraph2D_Resource*)m_pPlotResource)->m_eCursorTextType = E_GRAPH2D_GRID_DOUBLE;
			}
			else
			{
				((CGraph2D_Resource*)m_pPlotResource)->m_iCursorTextPrecision = 7;
				((CGraph2D_Resource*)m_pPlotResource)->m_eCursorTextType = E_GRAPH2D_GRID_DOUBLE;
				//((CGraph2D_Resource*)m_pPlotResource)->m_iCursorTextPrecision = 3;
				//((CGraph2D_Resource*)m_pPlotResource)->m_eCursorTextType = E_GRAPH2D_GRID_EXP;
			}
			bCursorTextPrecisionModifyFlag = true;
		}
	}
	if ( bGridTextPrecisionModifyFlag == false )
	{
		((CGraph2D_Resource*)m_pPlotResource)->m_iGridTextPrecision = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.iGridTextPrecision;
		((CGraph2D_Resource*)m_pPlotResource)->m_eGridTextType = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.eGridTextType;
	}
	if ( bCursorTextPrecisionModifyFlag == false )
	{
		((CGraph2D_Resource*)m_pPlotResource)->m_iCursorTextPrecision = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.iCursorTextPrecision;		
		((CGraph2D_Resource*)m_pPlotResource)->m_eCursorTextType = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.eGridTextType;
	}

	SetGraphEquationMinMaxY();

	//! Y축 Range 설정
	if ( m_bYScaleLock == false )
	{
		double dbRealMinY = 0., dbRealMaxY = 0.;
		if ( m_bMultiPlotOneAxis == true )
		{
			dbRealMinY = GetRealMinY(m_bYAutoRangeEquation, m_bYAutoRangeValueLine, m_bYAutoRangeRegionCursor, m_bYAutoRangeShowGraph);
			dbRealMaxY = GetRealMaxY(m_bYAutoRangeEquation, m_bYAutoRangeValueLine, m_bYAutoRangeRegionCursor, m_bYAutoRangeShowGraph);
		}
		for ( i = 0; i < iGraphSize; i++ )
		{
			//if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.bAutoRange == true )
			{
				bMarginFlag = false;

				if ( m_bMultiPlotOneAxis == false )
				{
					//! Y축이 여러 개일 경우

					if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.eAutoRangeReservedMin == E_GRAPH2D_AUTO_RANGE_RESERVED_FORCED )
					{
						dbRangeMinTemp = m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbAutoRangeReservedMin;
					}
					else
					{
						if ( m_bAutoRangeY_UsingRangeX == true )
						{
							if ( GetMinY_UsingRangeX(dbRangeMinTemp, i) == false )
							{
								dbRangeMinTemp = -1.;
							}
						}
						else
						{
							dbRangeMinTemp = m_arrPlotData.GetAt(i)->m_dbMinY;
						}

						if ( m_bYAutoRangeValueLine == true )
						{
							dbRangeMinTemp = GetMinCompareYValueLine(i, dbRangeMinTemp);
						}
						
						if ( m_bYAutoRangeEquation == true )
						{
							dbRangeMinTemp = GetMinCompareYEquation(i, dbRangeMinTemp);
						}

						if ( m_bYAutoRangeRegionCursor == true )
						{
							dbRangeMinTemp = GetMinCompareYRegionCursor(i, dbRangeMinTemp);
						}

						if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.eAutoRangeReservedMin == E_GRAPH2D_AUTO_RANGE_RESERVED_CONSIDER )
						{
							if ( dbRangeMinTemp > m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbAutoRangeReservedMin )
							{
								dbRangeMinTemp = m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbAutoRangeReservedMin;
							}
						}

						if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.eAutoRangeReservedMin == E_GRAPH2D_AUTO_RANGE_RESERVED_STEP )
						{
							if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.bMarginIncludeMin == false )
							{
								dbRangeMinTemp = GetCompareYMinBound(i, dbRangeMinTemp);
							}
						}
					}

					if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.eAutoRangeReservedMax == E_GRAPH2D_AUTO_RANGE_RESERVED_FORCED )
					{
						dbRangeMaxTemp = m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbAutoRangeReservedMax;
					}
					else
					{
						if ( m_bAutoRangeY_UsingRangeX == true )
						{
							if ( GetMaxY_UsingRangeX(dbRangeMaxTemp, i) == false )
							{
								dbRangeMaxTemp = -1.;
							}
						}
						else
						{
							dbRangeMaxTemp = m_arrPlotData.GetAt(i)->m_dbMaxY;
						}

						if ( m_bYAutoRangeValueLine == true )
						{
							dbRangeMaxTemp = GetMaxCompareYValueLine(i, dbRangeMaxTemp);
						}

						if ( m_bYAutoRangeEquation == true )
						{
							dbRangeMaxTemp = GetMaxCompareYEquation(i, dbRangeMaxTemp);
						}

						if ( m_bYAutoRangeRegionCursor == true )
						{
							dbRangeMaxTemp = GetMaxCompareYRegionCursor(i, dbRangeMaxTemp);
						}
						
						if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.eAutoRangeReservedMax == E_GRAPH2D_AUTO_RANGE_RESERVED_CONSIDER )
						{
							if ( dbRangeMaxTemp < m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbAutoRangeReservedMax )
							{
								dbRangeMaxTemp = m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbAutoRangeReservedMax;
							}
						}

						if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.eAutoRangeReservedMax == E_GRAPH2D_AUTO_RANGE_RESERVED_STEP )
						{
							if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.bMarginIncludeMax == false )
							{
								dbRangeMaxTemp = GetCompareYMaxBound(i, dbRangeMaxTemp);
							}
						}
					}

					if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.bSymmetry == true )
					{
						dbRangeMaxTemp = __max(fabs(dbRangeMaxTemp), fabs(dbRangeMinTemp));
						dbRangeMinTemp = dbRangeMaxTemp * (-1.);
					}

					dbRangeSizeTemp = dbRangeMaxTemp - dbRangeMinTemp;

					if ( fabs(dbRangeSizeTemp) < 0.0000001 )
					{
						if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.bMarginZero == true )
						{
							dbMarginTemp = m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbMarginZero;
							bMarginFlag = true;						
						}
					}
					else
					{
						switch( m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.eMarginType )
						{
						case E_GRAPH2D_RANGE_MARGIN_PERCENT:
							{
								dbMarginTemp = dbRangeSizeTemp * (m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbMargin / 100.);
								bMarginFlag = true;							
							}
							break;
						case E_GRAPH2D_RANGE_MARGIN_MAX_PERCENT:
							{
								dbMarginTemp = __max(fabs(dbRangeMaxTemp), fabs(dbRangeMinTemp)) * (m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbMargin / 100.);
								bMarginFlag = true;
							}
							break;
						case E_GRAPH2D_RANGE_MARGIN_VALUE:
							{
								dbMarginTemp = m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbMargin;
								bMarginFlag = true;							
							}
							break;
						}
					}

					if ( bMarginFlag == true )
					{
						if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.eAutoRangeReservedMin == E_GRAPH2D_AUTO_RANGE_RESERVED_NONE )
						{
							dbRangeMinTemp -= dbMarginTemp;
						}
						if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.eAutoRangeReservedMax == E_GRAPH2D_AUTO_RANGE_RESERVED_NONE )
						{
							dbRangeMaxTemp += dbMarginTemp;
						}

						if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.eAutoRangeReservedMin == E_GRAPH2D_AUTO_RANGE_RESERVED_STEP )
						{
							if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.bMarginIncludeMin == true )
							{
								dbRangeMinTemp = GetCompareYMinBound(i, dbRangeMinTemp);
							}
						}
						if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.eAutoRangeReservedMax == E_GRAPH2D_AUTO_RANGE_RESERVED_STEP )
						{
							if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.bMarginIncludeMax == true )
							{
								dbRangeMaxTemp = GetCompareYMaxBound(i, dbRangeMaxTemp);
							}
						}
					}
				}
				else
				{
					//! Y축이 무조건 1개로 통합 표시되는 경우

					if ( m_arrResourceY.GetAt(0)->m_strResourceYinfo.strAxisInfo.eAutoRangeReservedMin == E_GRAPH2D_AUTO_RANGE_RESERVED_FORCED )
					{
						dbRangeMinTemp = m_arrResourceY.GetAt(0)->m_strResourceYinfo.strAxisInfo.dbAutoRangeReservedMin;
					}
					else
					{
						dbRangeMinTemp = dbRealMinY;

						if ( m_arrResourceY.GetAt(0)->m_strResourceYinfo.strAxisInfo.eAutoRangeReservedMin == E_GRAPH2D_AUTO_RANGE_RESERVED_CONSIDER )
						{
							if ( dbRangeMinTemp > m_arrResourceY.GetAt(0)->m_strResourceYinfo.strAxisInfo.dbAutoRangeReservedMin )
							{
								dbRangeMinTemp = m_arrResourceY.GetAt(0)->m_strResourceYinfo.strAxisInfo.dbAutoRangeReservedMin;
							}
						}

						if ( m_arrResourceY.GetAt(0)->m_strResourceYinfo.strAxisInfo.eAutoRangeReservedMin == E_GRAPH2D_AUTO_RANGE_RESERVED_STEP )
						{
							if ( m_arrResourceY.GetAt(0)->m_strResourceYinfo.strAxisInfo.bMarginIncludeMin == false )
							{
								dbRangeMinTemp = GetCompareYMinBound(0, dbRangeMinTemp);
							}
						}
					}

					if ( m_arrResourceY.GetAt(0)->m_strResourceYinfo.strAxisInfo.eAutoRangeReservedMax == E_GRAPH2D_AUTO_RANGE_RESERVED_FORCED )
					{
						dbRangeMaxTemp = m_arrResourceY.GetAt(0)->m_strResourceYinfo.strAxisInfo.dbAutoRangeReservedMax;
					}
					else
					{
						dbRangeMaxTemp = dbRealMaxY;

						if ( m_arrResourceY.GetAt(0)->m_strResourceYinfo.strAxisInfo.eAutoRangeReservedMax == E_GRAPH2D_AUTO_RANGE_RESERVED_CONSIDER )
						{
							if ( dbRangeMaxTemp < m_arrResourceY.GetAt(0)->m_strResourceYinfo.strAxisInfo.dbAutoRangeReservedMax )
							{
								dbRangeMaxTemp = m_arrResourceY.GetAt(0)->m_strResourceYinfo.strAxisInfo.dbAutoRangeReservedMax;
							}
						}

						if ( m_arrResourceY.GetAt(0)->m_strResourceYinfo.strAxisInfo.eAutoRangeReservedMax == E_GRAPH2D_AUTO_RANGE_RESERVED_STEP )
						{
							if ( m_arrResourceY.GetAt(0)->m_strResourceYinfo.strAxisInfo.bMarginIncludeMax == false )
							{
								dbRangeMaxTemp = GetCompareYMaxBound(0, dbRangeMaxTemp);
							}
						}
					}

					if ( m_arrResourceY.GetAt(0)->m_strResourceYinfo.strAxisInfo.bSymmetry == true )
					{
						dbRangeMaxTemp = __max(fabs(dbRangeMaxTemp), fabs(dbRangeMinTemp));
						dbRangeMinTemp = dbRangeMaxTemp * (-1.);
					}
					
					dbRangeSizeTemp = dbRangeMaxTemp - dbRangeMinTemp;

					if ( fabs(dbRangeSizeTemp) < 0.0000001 )
					{
						if ( m_arrResourceY.GetAt(0)->m_strResourceYinfo.strAxisInfo.bMarginZero == true )
						{
							dbMarginTemp = m_arrResourceY.GetAt(0)->m_strResourceYinfo.strAxisInfo.dbMarginZero;
							bMarginFlag = true;						
						}
					}
					else
					{
						switch( m_arrResourceY.GetAt(0)->m_strResourceYinfo.strAxisInfo.eMarginType )
						{
						case E_GRAPH2D_RANGE_MARGIN_PERCENT:
							{
								dbMarginTemp = dbRangeSizeTemp * (m_arrResourceY.GetAt(0)->m_strResourceYinfo.strAxisInfo.dbMargin / 100.);
								bMarginFlag = true;							
							}
							break;
						case E_GRAPH2D_RANGE_MARGIN_MAX_PERCENT:
							{
								dbMarginTemp = __max(fabs(dbRangeMaxTemp), fabs(dbRangeMinTemp)) * (m_arrResourceY.GetAt(0)->m_strResourceYinfo.strAxisInfo.dbMargin / 100.);
								bMarginFlag = true;
							}
							break;
						case E_GRAPH2D_RANGE_MARGIN_VALUE:
							{
								dbMarginTemp = m_arrResourceY.GetAt(0)->m_strResourceYinfo.strAxisInfo.dbMargin;
								bMarginFlag = true;							
							}
							break;
						}
					}

					if ( bMarginFlag == true )
					{
						if ( m_arrResourceY.GetAt(0)->m_strResourceYinfo.strAxisInfo.eAutoRangeReservedMin == E_GRAPH2D_AUTO_RANGE_RESERVED_NONE )
						{
							dbRangeMinTemp -= dbMarginTemp;
						}
						if ( m_arrResourceY.GetAt(0)->m_strResourceYinfo.strAxisInfo.eAutoRangeReservedMax == E_GRAPH2D_AUTO_RANGE_RESERVED_NONE )
						{
							dbRangeMaxTemp += dbMarginTemp;
						}

						if ( m_arrResourceY.GetAt(0)->m_strResourceYinfo.strAxisInfo.eAutoRangeReservedMin == E_GRAPH2D_AUTO_RANGE_RESERVED_STEP )
						{
							if ( m_arrResourceY.GetAt(0)->m_strResourceYinfo.strAxisInfo.bMarginIncludeMin == true )
							{
								dbRangeMinTemp = GetCompareYMinBound(0, dbRangeMinTemp);
							}
						}
						if ( m_arrResourceY.GetAt(0)->m_strResourceYinfo.strAxisInfo.eAutoRangeReservedMax == E_GRAPH2D_AUTO_RANGE_RESERVED_STEP )
						{
							if ( m_arrResourceY.GetAt(0)->m_strResourceYinfo.strAxisInfo.bMarginIncludeMax == true )
							{
								dbRangeMaxTemp = GetCompareYMaxBound(0, dbRangeMaxTemp);
							}
						}
					}
				}		

				if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.bAutoRange == true )
				{
					if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.bMaxOperation == true )
					{
						if ( dbRangeMaxTemp > 0. )
						{
							dbRangeMaxTemp = DecideMinMaxOperation(dbRangeMaxTemp);
						}
					}
					if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.bMinOperation == true )
					{
						if ( dbRangeMinTemp < 0. )
						{
							dbRangeMinTemp = DecideMinMaxOperation(dbRangeMinTemp);
						}
					}
					if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.bSymmetry == true )
					{
						dbRangeMaxTemp = __max(fabs(dbRangeMaxTemp), fabs(dbRangeMinTemp));
						dbRangeMinTemp = dbRangeMaxTemp * (-1.);
					}

					if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.bAutoRangeGridSize == true )
					{
						m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.iGridSize = m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.iAutoRangeGridSize;
					}

					m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbManualMin = dbRangeMinTemp;
					m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbManualMax = dbRangeMaxTemp;
				}

				m_arrResourceY.GetAt(i)->m_dbAutoRangeMin = dbRangeMinTemp;
				m_arrResourceY.GetAt(i)->m_dbAutoRangeMax = dbRangeMaxTemp;
			}
		}
	}

	//! Y축 소수점 자리수 자동 설정
	for ( i = 0; i < iGraphSize; i++ )
	{
		bGridTextPrecisionModifyFlag = false;
		bCursorTextPrecisionModifyFlag = false;

		if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.eGridTextType == E_GRAPH2D_GRID_DOUBLE )
		{
			if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.bAutoGridTextPrecision == true )
			{
				dbRangeTempMax = GetCalcData(m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbManualMax, false, false, i);
				dbRangeTempMin = GetCalcData(m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbManualMin, false, false, i);
				dbRangeTemp = dbRangeTempMax - dbRangeTempMin;

				if ( dbRangeTemp >= 1000. )
				{
					m_arrResourceY.GetAt(i)->m_iGridTextPrecision = 0;
					m_arrResourceY.GetAt(i)->m_eGridTextType = E_GRAPH2D_GRID_DOUBLE;
				}
				else if ( dbRangeTemp >= 100. )
				{
					m_arrResourceY.GetAt(i)->m_iGridTextPrecision = 1;
					m_arrResourceY.GetAt(i)->m_eGridTextType = E_GRAPH2D_GRID_DOUBLE;
				}
				else if ( dbRangeTemp >= 10. )
				{
					m_arrResourceY.GetAt(i)->m_iGridTextPrecision = 2;
					m_arrResourceY.GetAt(i)->m_eGridTextType = E_GRAPH2D_GRID_DOUBLE;
				}
				else if ( dbRangeTemp >= 0.1 )
				{
					m_arrResourceY.GetAt(i)->m_iGridTextPrecision = 3;
					m_arrResourceY.GetAt(i)->m_eGridTextType = E_GRAPH2D_GRID_DOUBLE;
				}
				else if ( dbRangeTemp >= 0.01 )
				{
					m_arrResourceY.GetAt(i)->m_iGridTextPrecision = 4;
					m_arrResourceY.GetAt(i)->m_eGridTextType = E_GRAPH2D_GRID_DOUBLE;
				}
				else if ( dbRangeTemp >= 0.001 )
				{
					m_arrResourceY.GetAt(i)->m_iGridTextPrecision = 5;
					m_arrResourceY.GetAt(i)->m_eGridTextType = E_GRAPH2D_GRID_DOUBLE;
				}
				else if ( dbRangeTemp >= 0.0001 )
				{
					m_arrResourceY.GetAt(i)->m_iGridTextPrecision = 6;
					m_arrResourceY.GetAt(i)->m_eGridTextType = E_GRAPH2D_GRID_DOUBLE;
				}
				else
				{
					m_arrResourceY.GetAt(i)->m_iGridTextPrecision = 7;
					m_arrResourceY.GetAt(i)->m_eGridTextType = E_GRAPH2D_GRID_DOUBLE;
					//m_arrResourceY.GetAt(i)->m_iGridTextPrecision = 3;
					//m_arrResourceY.GetAt(i)->m_eGridTextType = E_GRAPH2D_GRID_EXP;
				}
				bGridTextPrecisionModifyFlag = true;
			}
			if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.bAutoCursorTextPrecision == true )
			{
				dbRangeTempMax = GetCalcData(m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbManualMax, false, true, i);
				dbRangeTempMin = GetCalcData(m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbManualMin, false, true, i);
				dbRangeTemp = dbRangeTempMax - dbRangeTempMin;

				if ( dbRangeTemp >= 1000. )
				{
					m_arrResourceY.GetAt(i)->m_iCursorTextPrecision = 0;
					m_arrResourceY.GetAt(i)->m_eCursorTextType = E_GRAPH2D_GRID_DOUBLE;
				}
				else if ( dbRangeTemp >= 100. )
				{
					m_arrResourceY.GetAt(i)->m_iCursorTextPrecision = 1;
					m_arrResourceY.GetAt(i)->m_eCursorTextType = E_GRAPH2D_GRID_DOUBLE;
				}
				else if ( dbRangeTemp >= 10. )
				{
					m_arrResourceY.GetAt(i)->m_iCursorTextPrecision = 2;
					m_arrResourceY.GetAt(i)->m_eCursorTextType = E_GRAPH2D_GRID_DOUBLE;
				}
				else if ( dbRangeTemp >= 0.1 )
				{
					m_arrResourceY.GetAt(i)->m_iCursorTextPrecision = 3;
					m_arrResourceY.GetAt(i)->m_eCursorTextType = E_GRAPH2D_GRID_DOUBLE;
				}
				else if ( dbRangeTemp >= 0.01 )
				{
					m_arrResourceY.GetAt(i)->m_iCursorTextPrecision = 4;
					m_arrResourceY.GetAt(i)->m_eCursorTextType = E_GRAPH2D_GRID_DOUBLE;
				}
				else if ( dbRangeTemp >= 0.001 )
				{
					m_arrResourceY.GetAt(i)->m_iCursorTextPrecision = 5;
					m_arrResourceY.GetAt(i)->m_eCursorTextType = E_GRAPH2D_GRID_DOUBLE;
				}
				else if ( dbRangeTemp >= 0.0001 )
				{
					m_arrResourceY.GetAt(i)->m_iCursorTextPrecision = 6;
					m_arrResourceY.GetAt(i)->m_eCursorTextType = E_GRAPH2D_GRID_DOUBLE;
				}
				else
				{
					m_arrResourceY.GetAt(i)->m_iCursorTextPrecision = 7;
					m_arrResourceY.GetAt(i)->m_eCursorTextType = E_GRAPH2D_GRID_DOUBLE;
					//m_arrResourceY.GetAt(i)->m_iCursorTextPrecision = 3;
					//m_arrResourceY.GetAt(i)->m_eCursorTextType = E_GRAPH2D_GRID_EXP;
				}
				bCursorTextPrecisionModifyFlag = true;
			}
		}

		if ( bGridTextPrecisionModifyFlag == false )
		{
			m_arrResourceY.GetAt(i)->m_iGridTextPrecision = m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.iGridTextPrecision;
			m_arrResourceY.GetAt(i)->m_eGridTextType = m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.eGridTextType;
		}
		if ( bCursorTextPrecisionModifyFlag == false )
		{
			m_arrResourceY.GetAt(i)->m_iCursorTextPrecision = m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.iCursorTextPrecision;
			m_arrResourceY.GetAt(i)->m_eCursorTextType = m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.eGridTextType;
		}
	}

	if ( m_bTimeAxisXEventMsg == true )
	{
		if ( m_hMsgHandle != NULL )
		{
			::SendMessage(m_hMsgHandle, WM_GRAPH2D_DECIDE_TIME_X_AXIS, 0, 0);
		}
	}


	//! 글자 크기를 기준값으로 설정
	CString szGrid = _T("");
	CSize sizeGrid;

	int iGridBaseWidth = 0, iGridBaseHeight = 0;
	m_pOldFont = pDC->SelectObject( &(((CGraph2D_Resource*)m_pPlotResource)->m_ftGridText) );
	szGrid = _T("ABCD");
	sizeGrid = pDC->GetTextExtent(szGrid);
	iGridBaseWidth = (int)(((double)(sizeGrid.cx)) / 4.);
	iGridBaseHeight = sizeGrid.cy;
	pDC->SelectObject(m_pOldFont);

	int iLegendBaseWidth = 0, iLegendBaseHeight = 0;
	m_pOldFont = pDC->SelectObject( &(((CGraph2D_Resource*)m_pPlotResource)->m_ftLegend) );
	szGrid = _T("ABCD");
	sizeGrid = pDC->GetTextExtent(szGrid);
	iLegendBaseWidth = (int)(((double)(sizeGrid.cx)) / 4.);
	iLegendBaseHeight = sizeGrid.cy;
	pDC->SelectObject(m_pOldFont);

	int iYPosition = m_CurRect.top;

	if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strMainTitleInfo.bShow == true )
	{
		int iMainTitleBaseWidth = 0, iMainTitleBaseHeight = 0;
		m_pOldFont = pDC->SelectObject( &(((CGraph2D_Resource*)m_pPlotResource)->m_ftMainTitle) );
		szGrid = _T("ABCD");
		sizeGrid = pDC->GetTextExtent(szGrid);
		iMainTitleBaseWidth = (int)(((double)(sizeGrid.cx)) / 4.);
		iMainTitleBaseHeight = sizeGrid.cy;
		pDC->SelectObject(m_pOldFont);

		m_MainTitleRect.left = m_CurRect.left;
		m_MainTitleRect.right = m_CurRect.right;
		m_MainTitleRect.top = iYPosition;
		m_MainTitleRect.bottom = m_MainTitleRect.top + (int)(((double)iMainTitleBaseHeight) * 1.2);
		iYPosition = m_MainTitleRect.bottom;
	}

	if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strSubTitleInfo.bShow == true )
	{
		int iSubTitleBaseWidth = 0, iSubTitleBaseHeight = 0;
		m_pOldFont = pDC->SelectObject( &(((CGraph2D_Resource*)m_pPlotResource)->m_ftMainTitle) );
		szGrid = _T("ABCD");
		sizeGrid = pDC->GetTextExtent(szGrid);
		iSubTitleBaseWidth = (int)(((double)(sizeGrid.cx)) / 4.);
		iSubTitleBaseHeight = sizeGrid.cy;
		pDC->SelectObject(m_pOldFont);

		m_SubTitleRect.left = m_CurRect.left;
		m_SubTitleRect.right = m_CurRect.right;
		m_SubTitleRect.top = iYPosition;
		m_SubTitleRect.bottom = m_SubTitleRect.top + (int)(((double)iSubTitleBaseHeight) * 1.2);
		iYPosition = m_SubTitleRect.bottom;
	}

	m_iGridMarginX = (int)((double)(iLegendBaseWidth) * 1.);
	if ( m_iGridMarginX < 3 )
	{
		m_iGridMarginX = 3;
	}
	m_iGridMarginY = (int)((double)(iLegendBaseHeight) / 7.);
	if ( m_iGridMarginY < 2 )
	{
		m_iGridMarginY = 2;
	}
	m_iAxisCaptionMarginX = iLegendBaseHeight;
	if ( m_iAxisCaptionMarginX < 2 )
	{
		m_iAxisCaptionMarginX = 2;
	}


	//! 아래로 실제 그래프가 그려지는 영역을 구함
	int iXMinGap = 0, iXMaxGap = 0, iYMinGap = 0, iYMaxGap = 0;
	
	//! X, Y축의 문자열이 표시되는 영역을 설정
	if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition == E_GRAPH2D_XY_CAPTION_POS_UNITE || 
		((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition == E_GRAPH2D_XY_CAPTION_POS_ONLY_XY || 
		((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition == E_GRAPH2D_XY_CAPTION_POS_UNITE_Y || 
		((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition == E_GRAPH2D_XY_CAPTION_POS_ONE_Y )
	{
		m_AxisCaptionRect.left = m_CurRect.left;
		m_AxisCaptionRect.right = m_CurRect.right;
		m_AxisCaptionRect.top = iYPosition;
		m_AxisCaptionRect.bottom = m_AxisCaptionRect.top + (int)(((double)iLegendBaseHeight) * 1.2);
		iYPosition = m_AxisCaptionRect.bottom;
	}
	else
	{
		m_AxisCaptionRect.SetRectEmpty();			
	}
	iYMaxGap = (int)((double)(iLegendBaseHeight) * 0.3);

	//! 눈금 길이 결정
	int iDivisionLength = 0;
	if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.bAutoDivisionLength == true )
	{
		iDivisionLength = (int)((double)iLegendBaseHeight * 1.3 / 5.);
		if ( iDivisionLength < 5 )
		{
			iDivisionLength = 5;
		}
		((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.iDivisionLength = iDivisionLength;
	}
	else
	{
		iDivisionLength = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.iDivisionLength;
	}

	//! X축 아래쪽의 높이를 구함
	if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.eGridVisualType == E_GRAPH2D_DATA_VISUAL_TIME && 
		((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bTimeGrid_CoupleRow == true )
	{
		if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition == E_GRAPH2D_XY_CAPTION_POS_SEPARATE || 
			 ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition == E_GRAPH2D_XY_CAPTION_POS_UNITE_Y || 
			 ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition == E_GRAPH2D_XY_CAPTION_POS_ONE_Y || 
			 ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition == E_GRAPH2D_XY_CAPTION_POS_ONLY_X )
		{
			iYMinGap = (iGridBaseHeight * 3) + (iDivisionLength * 1) + (m_iGridMarginY * 4);
		}
		else
		{
			iYMinGap = (iGridBaseHeight * 2) + (iDivisionLength * 1) + (m_iGridMarginY * 3);
		}
	}
	else
	{
		if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition == E_GRAPH2D_XY_CAPTION_POS_SEPARATE || 
			 ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition == E_GRAPH2D_XY_CAPTION_POS_UNITE_Y || 
			 ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition == E_GRAPH2D_XY_CAPTION_POS_ONE_Y || 
			 ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition == E_GRAPH2D_XY_CAPTION_POS_ONLY_X )
		{
			iYMinGap = (iGridBaseHeight * 2) + (iDivisionLength * 1) + (m_iGridMarginY * 3);
		}
		else
		{
			iYMinGap = iGridBaseHeight + iDivisionLength + (m_iGridMarginY * 2);
		}
	}

	iXMinGap = (int)((double)(iGridBaseWidth) * 3.);

	if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition == E_GRAPH2D_XY_CAPTION_POS_UNITE || 
		((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition == E_GRAPH2D_XY_CAPTION_POS_ONLY_XY )
	{
		iXMaxGap = (int)((double)(iGridBaseWidth) * 3.);
	}
	else
	{
		iXMaxGap = (int)((double)(iGridBaseWidth) * 2.);
	}


	//! Y축을 보여줄 X 좌표 설정
	bool bLeftShowAxis = false, bRightShowAxis = false;
	int iXAxisGap = 0;//, iXAxisGapExp = 0;
	int iLimitXPosofYAxis = (int)(((double)(m_CurRect.Width())) / 2.);
	int iLeftXPtofYAxis = m_CurRect.left;
	int iRightXPtofYAxis = m_CurRect.right;
	if ( m_bAlwaysInitYPos == true )
	{
		for ( i = 0; i < iGraphSize; i++ )
		{
			Init_XPos_YAxis(i);
		}
	}
	if ( iGraphSize > 1 && m_bMultiPlotOneAxis == false )	//! Y축이 여러 개일 때
	{
		//! 왼쪽의 Y축
		for ( i = 0; i < iGraphSize; i++ )
		{
			if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.bShowGraph == true && m_arrResourceY.GetAt(i)->m_strResourceYinfo.bAxisLeft == true && 
				m_arrPlotData.GetAt(i)->GetPointSize() > 0 )
			{
				bLeftShowAxis = true;
				GetStringMaxWidth_AxisY(pDC, i, m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbManualMin, m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbManualMax, iXAxisGap);
				
				iXAxisGap += iDivisionLength;
				iXAxisGap += m_iGridMarginX;
				iXAxisGap += m_iGridMarginX;
				if ( iXAxisGap > iLimitXPosofYAxis )
				{
					iXAxisGap = iLimitXPosofYAxis;
				}
				if ( iXAxisGap < m_arrResourceY.GetAt(i)->m_iLeftXPtofYAxis )
				{
					iXAxisGap = m_arrResourceY.GetAt(i)->m_iLeftXPtofYAxis;
				}
				else
				{
					m_arrResourceY.GetAt(i)->m_iLeftXPtofYAxis = iXAxisGap;
				}

				iLeftXPtofYAxis += iXAxisGap;
				
				/*if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.eGridTextType == E_GRAPH2D_GRID_EXP || 
					m_arrResourceY.GetAt(i)->m_eGridTextType == E_GRAPH2D_GRID_EXP )
				{
					iXAxisGapExp = iGridBaseWidth * (7 + m_arrResourceY.GetAt(i)->m_iGridTextPrecision);
					iLeftXPtofYAxis += iXAxisGapExp;
				}
				else
				{
					iXAxisGap = iGridBaseWidth * (5 + m_arrResourceY.GetAt(i)->m_iGridTextPrecision);
					iLeftXPtofYAxis += iXAxisGap;
				}*/
				m_arrResourceY.GetAt(i)->m_iDrawXPt = iLeftXPtofYAxis;				
			}
		}
		//! 오른쪽의 Y축
		for ( i = (iGraphSize - 1); i >= 0; i-- )
		{
			if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.bShowGraph == true && m_arrResourceY.GetAt(i)->m_strResourceYinfo.bAxisLeft == false && 
				m_arrPlotData.GetAt(i)->GetPointSize() > 0 )
			{
				bRightShowAxis = true;
				GetStringMaxWidth_AxisY(pDC, i, m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbManualMin, m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbManualMax, iXAxisGap);
				
				iXAxisGap += iDivisionLength;
				iXAxisGap += m_iGridMarginX;
				iXAxisGap += m_iGridMarginX;
				if ( iXAxisGap > iLimitXPosofYAxis )
				{
					iXAxisGap = iLimitXPosofYAxis;
				}
				if ( iXAxisGap < m_arrResourceY.GetAt(i)->m_iRightXPtofYAxis )
				{
					iXAxisGap = m_arrResourceY.GetAt(i)->m_iRightXPtofYAxis;
				}
				else
				{
					m_arrResourceY.GetAt(i)->m_iRightXPtofYAxis = iXAxisGap;
				}

				iRightXPtofYAxis -= iXAxisGap;

				/*if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.eGridTextType == E_GRAPH2D_GRID_EXP || 
					m_arrResourceY.GetAt(i)->m_eGridTextType == E_GRAPH2D_GRID_EXP )
				{
					iXAxisGapExp = iGridBaseWidth * (7 + m_arrResourceY.GetAt(i)->m_iGridTextPrecision);
					iRightXPtofYAxis -= iXAxisGapExp;
				}
				else
				{
					iXAxisGap = iGridBaseWidth * (5 + m_arrResourceY.GetAt(i)->m_iGridTextPrecision);
					iRightXPtofYAxis -= iXAxisGap;
				}*/
				m_arrResourceY.GetAt(i)->m_iDrawXPt = iRightXPtofYAxis;
			}
		}
		if ( bLeftShowAxis == false )
		{
			iLeftXPtofYAxis += iXMinGap;
		}
		else
		{
			iLeftXPtofYAxis += iLegendBaseWidth;
		}
		if ( bRightShowAxis == false )
		{
			iRightXPtofYAxis -= iXMaxGap;
		}
		else
		{
			iRightXPtofYAxis -= (iLegendBaseWidth * 2);	//! X, Y축 표시 글자, Y축 문자열 때문에 여백을 추가
		}
	}
	else
	{
		//bool bExistExp = false;
		/*for ( i = 0; i < iGraphSize; i++ )
		{
			if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.eGridTextType == E_GRAPH2D_GRID_EXP || 
					m_arrResourceY.GetAt(i)->m_eGridTextType == E_GRAPH2D_GRID_EXP )
			{
				bExistExp = true;
			}
		}*/

		//iXAxisGapExp = iGridBaseWidth * (7 + m_arrResourceY.GetAt(0)->m_iGridTextPrecision);
		//iXAxisGap = iGridBaseWidth * (5 + m_arrResourceY.GetAt(0)->m_iGridTextPrecision);

		GetStringMaxWidth_AxisY(pDC, 0, m_arrResourceY.GetAt(0)->m_strResourceYinfo.strAxisInfo.dbManualMin, m_arrResourceY.GetAt(0)->m_strResourceYinfo.strAxisInfo.dbManualMax, iXAxisGap);
		iXAxisGap += iDivisionLength;
		iXAxisGap += m_iGridMarginX;
		iXAxisGap += m_iGridMarginX;
		if ( iXAxisGap > iLimitXPosofYAxis )
		{
			iXAxisGap = iLimitXPosofYAxis;
		}
		
		if ( m_arrResourceY.GetAt(0)->m_strResourceYinfo.bAxisLeft == true )
		{
			//! 왼쪽 Y축
			bLeftShowAxis = true;

			if ( iXAxisGap < m_arrResourceY.GetAt(0)->m_iLeftXPtofYAxis )
			{
				iXAxisGap = m_arrResourceY.GetAt(0)->m_iLeftXPtofYAxis;
			}
			else
			{
				m_arrResourceY.GetAt(0)->m_iLeftXPtofYAxis = iXAxisGap;
			}

			/*if ( bExistExp == true )
			{
				iLeftXPtofYAxis += iXAxisGapExp;
			}
			else*/
			{
				iLeftXPtofYAxis += iXAxisGap;
			}
			for ( i = 0; i < iGraphSize; i++ )
			{
				m_arrResourceY.GetAt(i)->m_iDrawXPt = iLeftXPtofYAxis;
			}
			iRightXPtofYAxis -= iXMaxGap;
		}
		else
		{
			//! 오른쪽 Y축
			bRightShowAxis = true;
			iLeftXPtofYAxis += iXMinGap;

			if ( iXAxisGap < m_arrResourceY.GetAt(0)->m_iRightXPtofYAxis )
			{
				iXAxisGap = m_arrResourceY.GetAt(0)->m_iRightXPtofYAxis;
			}
			else
			{
				m_arrResourceY.GetAt(0)->m_iRightXPtofYAxis = iXAxisGap;
			}
			/*if ( bExistExp == true )
			{
				iRightXPtofYAxis -= iXAxisGapExp;
			}
			else*/
			{
				iRightXPtofYAxis -= iXMaxGap;
			}
			for ( i = 0; i < iGraphSize; i++ )
			{
				m_arrResourceY.GetAt(i)->m_iDrawXPt = iRightXPtofYAxis;
			}
		}
	}

	//! Y축 선의 문자열이 그래프 오른쪽 바깥에 위치할 경우 
	if ( iYValueLinesize > 0 )
	{
		CString szYLine = _T("");
		CSize sizeYLine;
		int iYLineMaxSize = 0, iYLineStringLen = 0, iYLineMargin = 0, iYLineMargineMax = 0;

		for ( i = 0; i < iYValueLinesize; i++ )
		{
			if ( m_arrValueLineY.GetAt(i)->m_strYLineInfo.bShow == true && m_arrValueLineY.GetAt(i)->m_strYLineInfo.bShowText == true && m_arrValueLineY.GetAt(i)->m_strYLineInfo.bTextPosExt == true )
			{
				szYLine = m_arrValueLineY.GetAt(i)->m_strYLineInfo.szText;
				iYLineStringLen = szYLine.GetLength();
				if ( iYLineStringLen <= 0 )
				{
					continue;
				}

				m_pOldFont = pDC->SelectObject( &(m_arrValueLineY.GetAt(i)->m_ftValueLineY) );
				sizeYLine = pDC->GetTextExtent(szYLine);
				if ( iYLineMaxSize < sizeYLine.cx )
				{
					iYLineMaxSize = sizeYLine.cx;
				}
				iYLineMargin = (int)(((double)(sizeYLine.cx)) / ((double)iYLineStringLen));
				iYLineMargin *= 2;
				if ( iYLineMargineMax < iYLineMargin )
				{
					iYLineMargineMax = iYLineMargin;
				}
				pDC->SelectObject(m_pOldFont);
			}
		}

		if ( iYLineMaxSize > 0 )
		{
			iYLineMaxSize += iYLineMargineMax;
			iRightXPtofYAxis -= iYLineMaxSize;
		}
	}

	//! Axis 선을 포함한 그래프 영역 설정	
	m_DataRect.left = iLeftXPtofYAxis;
	m_DataRect.right = iRightXPtofYAxis;
	m_DataRect.top = iYPosition + iYMaxGap;
	m_DataRect.bottom = m_CurRect.bottom - iYMinGap;

	//! 그래프 영역이 없을 경우
	if ( m_DataRect.left > m_DataRect.right )
	{
		m_DataRect.right = m_DataRect.left;
	}
	if ( m_DataRect.top > m_DataRect.bottom )
	{
		m_DataRect.bottom = m_DataRect.top;
	}

	//! X, Y축의 문자열이 표시되는 영역에서 X축 시작 위치를 재 설정
	if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition == E_GRAPH2D_XY_CAPTION_POS_UNITE || 
		 ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition == E_GRAPH2D_XY_CAPTION_POS_ONLY_XY || 
		 ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition == E_GRAPH2D_XY_CAPTION_POS_UNITE_Y || 
		 ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition == E_GRAPH2D_XY_CAPTION_POS_ONE_Y || 
		 ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition == E_GRAPH2D_XY_CAPTION_POS_ONLY_X )
	{
		m_AxisCaptionRect.left = m_DataRect.left;
	}

	//! 그래프 영역 객체 생성, 인쇄 미리보기 창에서는 좌표계가 틀리므로 좌표를 맞추어 주어야 함
	m_DrawRgn.DeleteObject();
	if ( pDC->IsKindOf(RUNTIME_CLASS(CPreviewDC)) )
	{
		CRect rectClip = m_DataRect;
		pDC->LPtoDP(&rectClip);	//! Modify by LHW [2008/4/8]

		CPreviewDC *pPrevDC = (CPreviewDC*)pDC;

		pPrevDC->PrinterDPtoScreenDP(&rectClip.TopLeft()); 
		pPrevDC->PrinterDPtoScreenDP(&rectClip.BottomRight());

		CPoint ptOrg;
		::GetViewportOrgEx(pDC->m_hDC, &ptOrg);
		rectClip += ptOrg;

		m_DrawRgn.CreateRectRgnIndirect(&rectClip);
	}
	else
	{
		m_DrawRgn.CreateRectRgnIndirect(&m_DataRect);
	}

	//! Axis 선을 포함하지 않는 그래프 영역 설정
	m_graphRect.left = m_DataRect.left + 1;
	m_graphRect.right = m_DataRect.right - 1;
	m_graphRect.top = m_DataRect.top + 1;
	m_graphRect.bottom = m_DataRect.bottom - 1;

	//! 그래프 영역이 없을 경우
	if ( m_graphRect.left > m_graphRect.right )
	{
		m_graphRect.right = m_graphRect.left;
	}
	if ( m_graphRect.top > m_graphRect.bottom )
	{
		m_graphRect.bottom = m_graphRect.top;
	}

	//! Y축 Event (여러개의 축 <-> 하나의 축 변환) 영역 설정
	m_crAxisY_Left_Event.SetRectEmpty();
	m_crAxisY_Right_Event.SetRectEmpty();
	if ( bLeftShowAxis == true )
	{
		m_crAxisY_Left_Event.left = m_CurRect.left;
		m_crAxisY_Left_Event.right = m_DataRect.left;
		m_crAxisY_Left_Event.top = m_DataRect.top;
		m_crAxisY_Left_Event.bottom = m_DataRect.bottom;
	}
	if ( bRightShowAxis == true )
	{
		m_crAxisY_Right_Event.left = m_DataRect.right;
		m_crAxisY_Right_Event.right = m_CurRect.right;
		m_crAxisY_Right_Event.top = m_DataRect.top;
		m_crAxisY_Right_Event.right = m_DataRect.bottom;
	}

	//! X축 Event 영역 설정
	m_crAxisX_Event.SetRectEmpty();
	m_crAxisX_Event.left = m_DataRect.left;
	m_crAxisX_Event.right = m_DataRect.right;
	m_crAxisX_Event.top = m_DataRect.bottom;
	m_crAxisX_Event.bottom = m_CurRect.bottom;
	
	//! X축 Range 설정	
	m_XMapper.m_iXPtMin = m_graphRect.left;
	m_XMapper.m_iXPtMax = m_graphRect.right - 1;
	if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bDirection_Plus == true )
	{
		//! 왼쪽에서 오른쪽으로 값이 증가
		m_XMapper.m_dbXDataMin = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbManualMin;
		m_XMapper.m_dbXDataMax = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbManualMax;		
	}
	else
	{
		//! 오른쪽에서 왼쪽으로 값이 증가
		m_XMapper.m_dbXDataMin = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbManualMax;
		m_XMapper.m_dbXDataMax = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbManualMin;		
	}	
	m_XMapper.CalcCoeff();

	//! Y축 Range 설정
	int iYBorderMin = m_graphRect.top;
	int iYBorderMax = m_graphRect.bottom;	
	strYRangeMapper strYMapper;
	for ( i = 0; i < iGraphSize; i++ )
	{
		strYMapper = m_arrYMapper.GetAt(i);
		strYMapper.m_iYPtMin = iYBorderMin;
		strYMapper.m_iYPtMax = iYBorderMax;
		if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.bDirection_Plus == true )
		{
			//! 아래쪽에서 위쪽으로 값이 증가
			strYMapper.m_dbYDataMin = m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbManualMin;
			strYMapper.m_dbYDataMax = m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbManualMax;			
		}
		else
		{
			//! 위쪽에서 아래쪽으로 값이 증가
			strYMapper.m_dbYDataMin = m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbManualMax;
			strYMapper.m_dbYDataMax = m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbManualMin;			
		}		
		strYMapper.CalcCoeff();
		m_arrYMapper.SetAt(i, strYMapper);
	}
	m_iRealGraphHeight = iYBorderMax - iYBorderMin + 1;
	
	//! 그래프의 눈에 보이는 데이터의 구간 index값과 눈에 보이는 데이터의 개수, 최대값 index, 그래프의 실제 사각 영역을 알아냄
	//! 확대된 상태에 대비
	m_RealGraphRect.SetRectEmpty();
	double dbXData = 0., dbYData = 0., dbMaxTemp = 0.;	
	int iXPt = 0, iYPt = 0, iDrawDataSize = 0;
	int iVisualCnt = 0, iStartIndexTemp = 0, iEndIndexTemp = 0, iMaxIndexTemp = 0, iRealStartIndexTemp = -1, iRealEndIndexTemp = 0;
	for ( i = 0; i < iGraphSize; i++ )
	{
		iVisualCnt = 0, iStartIndexTemp = 0, iEndIndexTemp = 0, iMaxIndexTemp = 0, iRealStartIndexTemp = -1, iRealEndIndexTemp = 0;
		m_arrPlotData.GetAt(i)->m_iVisualDataSize = 0;
		m_arrPlotData.GetAt(i)->m_iVisualDataStartIndex = 0;
		m_arrPlotData.GetAt(i)->m_iVisualDataEndIndex = 0;
		m_arrPlotData.GetAt(i)->m_iVisualMaxIndex = -1;
		m_arrPlotData.GetAt(i)->m_iVisualRealDataStartIndex = 0;
		m_arrPlotData.GetAt(i)->m_iVisualRealDataEndIndex = 0;

		iDrawDataSize = m_arrPlotData.GetAt(i)->GetPointSize();
		if ( iDrawDataSize <= 0 )
		{
			continue;
		}
		strYMapper = m_arrYMapper.GetAt(i);

		dbMaxTemp = DBL_MAX * (-1.);
		iMaxIndexTemp = -1;

		for ( j = 0; j < iDrawDataSize; j++ )
		{
			dbXData = m_arrPlotData.GetAt(i)->GetXPoint2D(j);
			dbYData = m_arrPlotData.GetAt(i)->GetYPoint2D(j);

			iXPt = m_XMapper.CalcXDataToPt(dbXData);
			iYPt = strYMapper.CalcYDataToPt(dbYData);

			if ( m_RealGraphRect.left > iXPt )
			{
				m_RealGraphRect.left = iXPt;
			}
			if ( m_RealGraphRect.right < iXPt )
			{
				m_RealGraphRect.right = iXPt;
			}
			if ( m_RealGraphRect.top > iYPt )
			{
				m_RealGraphRect.top = iYPt;
			}
			if ( m_RealGraphRect.bottom < iYPt )
			{
				m_RealGraphRect.bottom = iYPt;
			}
			
			if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bDirection_Plus == true )
			{
				//! 왼쪽에서 오른쪽으로 값이 증가

				if ( dbXData < m_XMapper.m_dbXDataMin )
				{
					iStartIndexTemp = j;
					iRealStartIndexTemp = j;
				}

				if ( dbXData >= m_XMapper.m_dbXDataMin && dbXData <= m_XMapper.m_dbXDataMax )
				{
					iVisualCnt++;
					iEndIndexTemp = j;
					iRealEndIndexTemp = j;
				}
			}
			else
			{
				//! 오른쪽에서 왼쪽으로 값이 증가

				if ( dbXData > m_XMapper.m_dbXDataMin )
				{
					iStartIndexTemp = j;
					iRealStartIndexTemp = j;
				}

				if ( dbXData >= m_XMapper.m_dbXDataMax && dbXData <= m_XMapper.m_dbXDataMin )
				{
					iVisualCnt++;
					iEndIndexTemp = j;
					iRealEndIndexTemp = j;
				}
			}

			if ( dbMaxTemp < dbYData )
			{
				dbMaxTemp = dbYData;
				iMaxIndexTemp = j;
			}			
		}//! for ( j = 0; j < iDrawDataSize; j++ )

		//! 실제 눈에 보이는 데이터들만의 index
		iRealStartIndexTemp++;
		if ( iRealStartIndexTemp < 0 )
		{
			iRealStartIndexTemp = 0;
		}
		if ( iRealEndIndexTemp <= 0 )
		{
			iRealEndIndexTemp = iRealStartIndexTemp;
		}
		if ( iRealEndIndexTemp >= iDrawDataSize )
		{
			iRealEndIndexTemp = iDrawDataSize - 1;
		}

		//! 실제 눈에 보이는 것보다 2개의 데이터를 더 붙여 설정 (커서 동작 때문)
		if ( iEndIndexTemp <= 0 )
		{
			iEndIndexTemp = iStartIndexTemp;
		}
		iStartIndexTemp--;
		if ( iStartIndexTemp < 0 )
		{
			iStartIndexTemp = 0;
		}		
		iEndIndexTemp += 2;
		if ( iEndIndexTemp >= iDrawDataSize )
		{
			iEndIndexTemp = iDrawDataSize - 1;
		}

		m_arrPlotData.GetAt(i)->m_iVisualDataStartIndex = iStartIndexTemp;
		m_arrPlotData.GetAt(i)->m_iVisualDataEndIndex = iEndIndexTemp;
		m_arrPlotData.GetAt(i)->m_iVisualDataSize = iVisualCnt;
		m_arrPlotData.GetAt(i)->m_iVisualMaxIndex = iMaxIndexTemp;
		m_arrPlotData.GetAt(i)->m_iVisualRealDataStartIndex = iRealStartIndexTemp;
		m_arrPlotData.GetAt(i)->m_iVisualRealDataEndIndex = iRealEndIndexTemp;
	}//! for ( i = 0; i < iGraphSize; i++ )

	//! Max-Hold 커서 관련 작업 진행
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize > 0 )
	{
		int iOverlapIndex = 0, iCursorDataIndex = 0;
		for ( i = 0; i < iCursorSize; i++ )
		{
			strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(i);
			if ( strCursorInfo.bMaxHold == true )
			{
				iOverlapIndex = strCursorInfo.iSelectOverlapIndex;
				if ( iOverlapIndex >= 0 && iOverlapIndex < iGraphSize )
				{
					iCursorDataIndex = m_arrPlotData.GetAt(iOverlapIndex)->m_iVisualMaxIndex;
					if ( iCursorDataIndex >= 0 )
					{
						if ( SetCursorInfo(iCursorDataIndex, &strCursorInfo, iOverlapIndex) == true )
						{
							m_arrCursor.SetAt(i, strCursorInfo);
						}
					}
				}
			}
		}
	}

	//! X 특정값 표시선의 이벤트 가능 영역을 설정
	iXValueLinesize = (int)(m_arrValueLineX.GetSize());
	if ( iXValueLinesize > 0 )
	{
		double dbValueX = 0.;
		int iValuePosX = 0;
		CRect crSelect;
		for ( i = 0; i < iXValueLinesize; i++ )
		{
			dbValueX = m_arrValueLineX.GetAt(i)->m_strXLineInfo.dbValue;
			iValuePosX = m_XMapper.CalcXDataToPt(dbValueX);
			crSelect.left = iValuePosX - m_iCursorMargin;
			crSelect.right = iValuePosX + m_iCursorMargin;
			crSelect.top = m_DataRect.top;
			crSelect.bottom = m_DataRect.bottom;
			m_arrValueLineX.GetAt(i)->m_crSelect = crSelect;
		}
	}

	//! Data-Point의 Event 사각 영역을 계산
	if ( m_bDataPointEventMsg == true )
	{
		SetDataPointRect();
	}

	if ( m_bAutoDrawCompleteMsg == true )
	{
		m_bDrawCompleteMsg = true;
	}

	return true;
}

//! Added by LHW [2008/8/25]
//! Modify by LHW [2008/8/26] : X축 입력값 부분 수정
//! Modify by LHW [2008/9/1] : dbInputOffsetX, dbOutputOffsetY 추가, bUseExp 관련 부분 추가
//! Modify by LHW [2008/9/3] : dbXDataWithOffset 추가
bool CGraph2DWnd::SetGraphEquationMinMaxY()
{
	int iGraphEquationSize = (int)(m_arrGraphEquation.GetSize());
	if ( iGraphEquationSize <= 0 )
	{
		return false;
	}

	bool bDataExist = false;
	int i = 0, j = 0;
	double dbXData = 0., dbXDataWithOffset = 0., dbYData = 0.;
	double dbMinTemp = DBL_MAX, dbMaxTemp = DBL_MAX * (-1.);

	double dbRangeMinX = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbManualMin;
	double dbRangeMaxX = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbManualMax;
	double dbIntervalX = dbRangeMaxX - dbRangeMinX;
	if ( dbIntervalX <= 0. )
	{
		return false;
	}
	int iIntervalSizeX = GetSystemMetrics(SM_CXSCREEN);
	if ( iIntervalSizeX <= 0 )
	{
		return false;
	}
	double dbIncrementX = dbIntervalX / ((double)iIntervalSizeX);

	for ( i = 0; i < iGraphEquationSize; i++ )
	{
		if ( m_arrGraphEquation.GetAt(i)->m_strEquationInfo.iCoeffSize <= 0 || m_arrGraphEquation.GetAt(i)->m_strEquationInfo.pdbCoeff == NULL )
		{
			continue;
		}
		if ( m_arrGraphEquation.GetAt(i)->m_strEquationInfo.bUseExp == true && m_arrGraphEquation.GetAt(i)->m_strEquationInfo.iCoeffSize < 2 )
		{
			continue;
		}
		
		bDataExist = false;
		dbMinTemp = DBL_MAX, dbMaxTemp = DBL_MAX * (-1.);
		dbXData = m_arrGraphEquation.GetAt(i)->m_strEquationInfo.dbStartRangeX;
		for ( j = 0; j < (iIntervalSizeX + 1); j++ )
		{
			if ( dbXData < m_arrGraphEquation.GetAt(i)->m_strEquationInfo.dbStartRangeX || 
				dbXData > m_arrGraphEquation.GetAt(i)->m_strEquationInfo.dbEndRangeX )
			{
				continue;
			}

			bDataExist = true;
			dbXDataWithOffset = dbXData;
			dbXDataWithOffset += m_arrGraphEquation.GetAt(i)->m_strEquationInfo.dbInputOffsetX;
			if ( m_arrGraphEquation.GetAt(i)->m_strEquationInfo.bUseExp == true )
			{
				dbYData = exp(m_arrGraphEquation.GetAt(i)->m_strEquationInfo.pdbCoeff[0]) * exp((dbXDataWithOffset + 1.) * m_arrGraphEquation.GetAt(i)->m_strEquationInfo.pdbCoeff[1]);
			}
			else
			{
				dbYData = CalcPolynomialEquation(m_arrGraphEquation.GetAt(i)->m_strEquationInfo.pdbCoeff, m_arrGraphEquation.GetAt(i)->m_strEquationInfo.iCoeffSize, dbXDataWithOffset);			
			}
			dbYData += m_arrGraphEquation.GetAt(i)->m_strEquationInfo.dbOutputOffsetY;
			if ( dbYData < dbMinTemp )
			{
				dbMinTemp = dbYData;
			}
			if ( dbYData > dbMaxTemp )
			{
				dbMaxTemp = dbYData;
			}

			dbXData += dbIncrementX;
		}

		if ( bDataExist == true )
		{
			m_arrGraphEquation.GetAt(i)->m_dbDataMaxY = dbMaxTemp;
			m_arrGraphEquation.GetAt(i)->m_dbDataMinY = dbMinTemp;
		}
	}

	return true;
}

//! Added by LHW [2008/4/1]
int CGraph2DWnd::CalcLinearInterpolate(int iX1, int iY1, int iX2, int iY2, int iInputX)
{
	int iNomial = (iX2 * iY1) - (iX1 * iY2);
	int iNumerator = ((iY2 - iY1) * iInputX) + iNomial;
	int iDenominator = iX2 - iX1;
	int iResult = (int)(((double)iNumerator) / ((double)iDenominator));
	return iResult;
}

int CGraph2DWnd::GetGraphWidth()
{
	int iReturn = m_XMapper.m_iXPtMax - m_XMapper.m_iXPtMin + 1;
	if ( iReturn < 0 )
	{
		iReturn = 0;
	}
	return iReturn;
}

int CGraph2DWnd::GetGraphHeight()
{
	int iReturn = m_iRealGraphHeight;
	if ( iReturn < 0 )
	{
		iReturn = 0;
	}
	return iReturn;
}

//! Added by LHW [2008/10/25]
bool CGraph2DWnd::GetStringMaxWidth_AxisY(CDC *pDC, int iOverlapIndex, double dbMinValue, double dbMaxValue, int &iMaxWidth)
{
	iMaxWidth = 0;

	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}

	CString szGrid = _T("");
	CSize sizeGrid;
	int iTempWidth = 0;

	m_pOldFont = pDC->SelectObject( &(((CGraph2D_Resource*)m_pPlotResource)->m_ftGridText) );

	if ( m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.bShowMin == true )
	{
		szGrid = GetVisualDataText(dbMinValue, false, false, false, iOverlapIndex);
		sizeGrid = pDC->GetTextExtent(szGrid);
		iTempWidth = sizeGrid.cx;
		if ( iMaxWidth < iTempWidth )
		{
			iMaxWidth = iTempWidth;
		}

		if ( m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.eGridVisualType == E_GRAPH2D_DATA_VISUAL_TIME && 
			m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.bTimeGrid_CoupleRow == true )
		{
			szGrid = GetVisualDataText(dbMinValue, false, true, false, iOverlapIndex);
			sizeGrid = pDC->GetTextExtent(szGrid);
			iTempWidth = sizeGrid.cx;
			if ( iMaxWidth < iTempWidth )
			{
				iMaxWidth = iTempWidth;
			}			
		}		
	}

	if ( m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.bShowMax == true )
	{
		szGrid = GetVisualDataText(dbMaxValue, false, false, false, iOverlapIndex);
		sizeGrid = pDC->GetTextExtent(szGrid);
		iTempWidth = sizeGrid.cx;
		if ( iMaxWidth < iTempWidth )
		{
			iMaxWidth = iTempWidth;
		}

		if ( m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.eGridVisualType == E_GRAPH2D_DATA_VISUAL_TIME && 
			m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.bTimeGrid_CoupleRow == true )
		{
			szGrid = GetVisualDataText(dbMaxValue, false, true, false, iOverlapIndex);
			sizeGrid = pDC->GetTextExtent(szGrid);
			iTempWidth = sizeGrid.cx;
			if ( iMaxWidth < iTempWidth )
			{
				iMaxWidth = iTempWidth;
			}
		}
	}

	pDC->SelectObject(m_pOldFont);

	return true;
}

bool CGraph2DWnd::DrawInit(CDC *pDC)
{
	if(m_DrawDC.GetSafeHdc() || m_DrawBitmap.GetSafeHandle())
	{
		m_DrawDC.DeleteDC();
		m_DrawBitmap.DeleteObject();		
	}
	if(m_DrawDC.CreateCompatibleDC(pDC))
	{
		if(m_DrawBitmap.CreateCompatibleBitmap(pDC, m_CurRect.Width(), m_CurRect.Height()))
			m_pOldDrawBitmap = m_DrawDC.SelectObject(&m_DrawBitmap) ;
	}

	return true;
}

bool CGraph2DWnd::DrawBackground(CDC *pDC)
{
	pDC->FillRect( &m_CurRect, &(((CGraph2D_Resource*)m_pPlotResource)->m_brEntireBackGround) );
	pDC->FillRect( &m_DataRect, &(((CGraph2D_Resource*)m_pPlotResource)->m_brGraphBackGround) );

	return true;
}

//! Modify by LHW [2008/4/4] : GetVisualDataText 함수를 사용하도록 수정
//! Modify by LHW [2008/4/18] : bXYCaptionPosition이 true일 때만 'Y' 표시
//! Modify by LHW [2008/7/24] : bXYCaptionPosition이 아닌 eXYCaptionPosition 으로 수정, Margin 관련값 수정
//! Modify by LHW [2008/7/30] : m_iShowGridY_OverlapIndex 추가, bDrawGrid 삭제
//! Modify by LHW [2008/10/24] : E_GRAPH2D_XY_CAPTION_POS_ONLY_XY 추가
//! Modify by LHW [2013/3/26] : bDirection_Plus 추가
bool CGraph2DWnd::DrawAxisY(CDC *pDC, int iOverlapIndex, bool bOnlyAxis, bool bLeft)
{
	pDC->SetBkMode(TRANSPARENT);

	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}

	int iDrawDataSize = m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize();
	if ( iDrawDataSize <= 0 )
	{
		return false;
	}

	pDC->SetBkMode(TRANSPARENT);

	strYRangeMapper strYMapper = m_arrYMapper.GetAt(iOverlapIndex);

	int iXPosition = m_arrResourceY.GetAt(iOverlapIndex)->m_iDrawXPt;

	if ( bOnlyAxis == true )
	{
		m_penOld = pDC->SelectObject( &(((CGraph2D_Resource*)m_pPlotResource)->m_penAxis) );		
	}
	else
	{
		m_penOld = pDC->SelectObject( &(m_arrResourceY.GetAt(iOverlapIndex)->m_penYAxis) );
	}
	pDC->MoveTo(iXPosition, strYMapper.m_iYPtMax);
	pDC->LineTo(iXPosition, strYMapper.m_iYPtMin);	
	pDC->SelectObject(m_penOld);
	

	int iDivisionLength = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.iDivisionLength;
	int iMarginY = m_iGridMarginY;
	int iMarginX = m_iGridMarginX;

	bool bStop = false;
	int i = 0, iXOffset = 0, iYOffset = 0, iGridPosY = 0, iGridSize = 0;
	double dbGrid = 0., dbIncrement= 0.;
	CString szGrid = _T("");
	CSize sizeGrid;

	switch ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition )
	{
	case E_GRAPH2D_XY_CAPTION_POS_UNITE:
	case E_GRAPH2D_XY_CAPTION_POS_ONLY_XY:
		{
			m_pOldFont = pDC->SelectObject( &(((CGraph2D_Resource*)m_pPlotResource)->m_ftLegend) );
			m_clrBackup = pDC->GetTextColor();
			
			if ( bOnlyAxis == true )
			{
				pDC->SetTextColor(((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.clrLegend);
				szGrid = _T("Y");
			}
			else
			{
				pDC->SetTextColor(m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.clrData);
				szGrid.Format(_T("Y%d"), iOverlapIndex + 1);
			}
			sizeGrid = pDC->GetTextExtent(szGrid);
			iXOffset = (int)(((double)(sizeGrid.cx)) / 2.);
			iYOffset = (int)(((double)(sizeGrid.cy)) * 1.3);
			pDC->TextOut(iXPosition - iXOffset, m_DataRect.top - iYOffset, szGrid);

			pDC->SelectObject(m_pOldFont);	
			pDC->SetTextColor(m_clrBackup);
		}
		break;
	case E_GRAPH2D_XY_CAPTION_POS_SEPARATE:
		{
			m_pOldFont = pDC->SelectObject( &(((CGraph2D_Resource*)m_pPlotResource)->m_ftLegend) );
			m_clrBackup = pDC->GetTextColor();
			pDC->SetTextColor(m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.clrData);

			szGrid = _T("Y");
			sizeGrid = pDC->GetTextExtent(szGrid);			
			iYOffset = (int)(((double)(sizeGrid.cy)) * 1.3);

			if ( bOnlyAxis == false )
			{
				szGrid = m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.szCaption1;
				if ( szGrid.GetLength() > 0 )
				{
					sizeGrid = pDC->GetTextExtent(szGrid);
					iXOffset = (int)(((double)(sizeGrid.cx)) / 2.);
					pDC->TextOut(iXPosition - iXOffset, m_DataRect.top - iYOffset, szGrid);
				}

				szGrid = m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.szCaption2;
				if ( szGrid.GetLength() > 0 )
				{
					sizeGrid = pDC->GetTextExtent(szGrid);
					iXOffset = (int)(((double)(sizeGrid.cx)) / 2.);
					iGridPosY = m_DataRect.top - (iYOffset * 2);
					if ( iGridPosY < m_CurRect.top )
					{
						iGridPosY = m_CurRect.top;
					}
					pDC->TextOut(iXPosition - iXOffset, iGridPosY, szGrid);
				}
			}

			pDC->SelectObject(m_pOldFont);	
			pDC->SetTextColor(m_clrBackup);
		}
		break;
	}

	m_clrBackup = pDC->GetTextColor();
	if ( bOnlyAxis == true )
	{
		pDC->SetTextColor(((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.clrGridText);
	}
	else
	{
		pDC->SetTextColor( m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.clrData );
	}

	m_pOldFont = pDC->SelectObject( &(((CGraph2D_Resource*)m_pPlotResource)->m_ftGridText) );
	
	if ( m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.bShowMin == true )
	{
		if ( m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.eGridVisualType == E_GRAPH2D_DATA_VISUAL_TIME && 
			 m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.bTimeGrid_CoupleRow == true )
		{
			//! 아래 줄을 먼저 쓰고, 윗줄을 씀
			szGrid = GetVisualDataText(strYMapper.m_dbYDataMin, false, true, false, iOverlapIndex);
			sizeGrid = pDC->GetTextExtent(szGrid);			
			iYOffset = (int)(((double)(sizeGrid.cy)) / 2.);
			iGridPosY = strYMapper.m_iYPtMax - iYOffset;
			if ( bLeft == true )
			{
				iXOffset = sizeGrid.cx + iDivisionLength + iMarginX;
				pDC->TextOut(iXPosition - iXOffset, iGridPosY, szGrid);
			}
			else
			{
				iXOffset = iDivisionLength + iMarginX;
				pDC->TextOut(iXPosition + iXOffset, iGridPosY, szGrid);
			}

			iGridPosY -= sizeGrid.cy;
			szGrid = GetVisualDataText(strYMapper.m_dbYDataMin, false, false, false, iOverlapIndex);
			sizeGrid = pDC->GetTextExtent(szGrid);			
			if ( bLeft == true )
			{
				iXOffset = sizeGrid.cx + iDivisionLength + iMarginX;
				pDC->TextOut(iXPosition - iXOffset, iGridPosY - iMarginY, szGrid);
			}
			else
			{
				iXOffset = iDivisionLength + iMarginX;
				pDC->TextOut(iXPosition + iXOffset, iGridPosY - iMarginY, szGrid);
			}
		}
		else
		{
			szGrid = GetVisualDataText(strYMapper.m_dbYDataMin, false, false, false, iOverlapIndex);
			sizeGrid = pDC->GetTextExtent(szGrid);			
			iYOffset = (int)(((double)(sizeGrid.cy)) / 2.);
			iGridPosY = strYMapper.m_iYPtMax - iYOffset;
			if ( bLeft == true )
			{
				iXOffset = sizeGrid.cx + iDivisionLength + iMarginX;
				pDC->TextOut(iXPosition - iXOffset, iGridPosY, szGrid);
			}
			else
			{
				iXOffset = iDivisionLength + iMarginX;
				pDC->TextOut(iXPosition + iXOffset, iGridPosY, szGrid);
			}
		}

		if ( bOnlyAxis == true )
		{
			m_penOld = pDC->SelectObject( &(((CGraph2D_Resource*)m_pPlotResource)->m_penAxis) );
		}
		else
		{
			m_penOld = pDC->SelectObject( &(m_arrResourceY.GetAt(iOverlapIndex)->m_penYAxis) );
		}
		pDC->MoveTo(iXPosition, strYMapper.m_iYPtMax);
		if ( bLeft == true )
		{
			pDC->LineTo(iXPosition - iDivisionLength, strYMapper.m_iYPtMax);
		}
		else
		{
			pDC->LineTo(iXPosition + iDivisionLength, strYMapper.m_iYPtMax);
		}
		pDC->SelectObject(m_penOld);
	}

	if ( m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.bShowMax == true )
	{
		szGrid = GetVisualDataText(strYMapper.m_dbYDataMax, false, false, false, iOverlapIndex);
		sizeGrid = pDC->GetTextExtent(szGrid);		
		iYOffset = (int)(((double)(sizeGrid.cy)) / 2.);
		iGridPosY = strYMapper.m_iYPtMin - iYOffset;
		if ( bLeft == true )
		{
			iXOffset = sizeGrid.cx + iDivisionLength + iMarginX;
			pDC->TextOut(iXPosition - iXOffset, iGridPosY, szGrid);
		}
		else
		{
			iXOffset = iDivisionLength + iMarginX;
			pDC->TextOut(iXPosition + iXOffset, iGridPosY, szGrid);
		}

		if ( m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.eGridVisualType == E_GRAPH2D_DATA_VISUAL_TIME && 
			 m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.bTimeGrid_CoupleRow == true )
		{
			iGridPosY += sizeGrid.cy;
			szGrid = GetVisualDataText(strYMapper.m_dbYDataMax, false, true, false, iOverlapIndex);					
			if ( bLeft == true )
			{
				sizeGrid = pDC->GetTextExtent(szGrid);
				iXOffset = sizeGrid.cx + iDivisionLength + iMarginX;
				pDC->TextOut(iXPosition - iXOffset, iGridPosY + iMarginY, szGrid);
			}
			else
			{
				iXOffset = iDivisionLength + iMarginX;
				pDC->TextOut(iXPosition + iXOffset, iGridPosY + iMarginY, szGrid);
			}
		}

		if ( bOnlyAxis == true )
		{
			m_penOld = pDC->SelectObject( &(((CGraph2D_Resource*)m_pPlotResource)->m_penAxis) );
		}
		else
		{
			m_penOld = pDC->SelectObject( &(m_arrResourceY.GetAt(iOverlapIndex)->m_penYAxis) );
		}
		pDC->MoveTo(iXPosition, strYMapper.m_iYPtMin);
		if ( bLeft == true )
		{
			pDC->LineTo(iXPosition - iDivisionLength, strYMapper.m_iYPtMin);
		}
		else
		{
			pDC->LineTo(iXPosition + iDivisionLength, strYMapper.m_iYPtMin);
		}
		pDC->SelectObject(m_penOld);
	}

	if ( m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.bShowGrid == true )
	{
		//bool bDrawGrid = false;

		if ( m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.bIncrementGrid == true )
		{
			if ( m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.bDirection_Plus == true )
			{
				//! 아래쪽에서 위쪽으로 값이 증가
				dbIncrement = fabs(m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.dbIncrementGrid);
			}
			else
			{
				//! 위쪽에서 아래쪽으로 값이 증가
				dbIncrement = (-1.) * fabs(m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.dbIncrementGrid);
			}

			bStop = false;

			//if ( dbIncrement > 0. )
			//{
				dbGrid = strYMapper.m_dbYDataMin + dbIncrement;

				while(1)
				{
					if ( m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.bDirection_Plus == true )
					{
						//! 아래쪽에서 위쪽으로 값이 증가
						if ( dbGrid >= strYMapper.m_dbYDataMax )
						{
							bStop = true;
						}
					}
					else
					{
						//! 위쪽에서 아래쪽으로 값이 증가
						if ( dbGrid <= strYMapper.m_dbYDataMax )
						{
							bStop = true;
						}
					}

					if ( bStop == true )
					{
						break;
					}

					iGridPosY = strYMapper.CalcYDataToPt(dbGrid);

					if ( m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.eGridVisualType == E_GRAPH2D_DATA_VISUAL_TIME && 
						 m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.bTimeGrid_CoupleRow == true )
					{
						szGrid = GetVisualDataText(dbGrid, false, false, false, iOverlapIndex);
						sizeGrid = pDC->GetTextExtent(szGrid);						
						iYOffset = sizeGrid.cy + iMarginY;
						if ( bLeft == true )
						{
							iXOffset = sizeGrid.cx + iDivisionLength + iMarginX;
							pDC->TextOut(iXPosition - iXOffset, iGridPosY - iYOffset, szGrid);
						}
						else
						{
							iXOffset = iDivisionLength + iMarginX;
							pDC->TextOut(iXPosition + iXOffset, iGridPosY - iYOffset, szGrid);
						}

						szGrid = GetVisualDataText(dbGrid, false, true, false, iOverlapIndex);						
						iYOffset = iMarginY;
						if ( bLeft == true )
						{
							sizeGrid = pDC->GetTextExtent(szGrid);
							iXOffset = sizeGrid.cx + iDivisionLength + iMarginX;
							pDC->TextOut(iXPosition - iXOffset, iGridPosY + iYOffset, szGrid);
						}
						else
						{
							iXOffset = iDivisionLength + iMarginX;
							pDC->TextOut(iXPosition + iXOffset, iGridPosY + iYOffset, szGrid);
						}
					}
					else
					{
						szGrid = GetVisualDataText(dbGrid, false, false, false, iOverlapIndex);
						sizeGrid = pDC->GetTextExtent(szGrid);						
						iYOffset = (int)(((double)(sizeGrid.cy)) / 2.);
						if ( bLeft == true )
						{
							iXOffset = sizeGrid.cx + iDivisionLength + iMarginX;
							pDC->TextOut(iXPosition - iXOffset, iGridPosY - iYOffset, szGrid);
						}
						else
						{
							iXOffset = iDivisionLength + iMarginX;
							pDC->TextOut(iXPosition + iXOffset, iGridPosY - iYOffset, szGrid);
						}
					}

					if ( bOnlyAxis == true )
					{
						m_penOld = pDC->SelectObject( &(((CGraph2D_Resource*)m_pPlotResource)->m_penAxis) );
					}
					else
					{
						m_penOld = pDC->SelectObject( &(m_arrResourceY.GetAt(iOverlapIndex)->m_penYAxis) );
					}
					pDC->MoveTo(iXPosition, iGridPosY);
					if ( bLeft == true )
					{
						pDC->LineTo(iXPosition - iDivisionLength, iGridPosY);
					}
					else
					{
						pDC->LineTo(iXPosition + iDivisionLength, iGridPosY);
					}
					pDC->SelectObject(m_penOld);

					if ( m_iShowGridY_OverlapIndex == iOverlapIndex )
					{
						//bDrawGrid = true;
						m_penOld = pDC->SelectObject( &(((CGraph2D_Resource*)m_pPlotResource)->m_penGrid) );
						pDC->MoveTo(m_DataRect.left + 1, iGridPosY);
						pDC->LineTo(m_DataRect.right - 1, iGridPosY);
						pDC->SelectObject(m_penOld);
					}

					dbGrid += dbIncrement;
				}//! while(1)
			//}
		}
		else
		{
			iGridSize = m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.iGridSize;
			if ( iGridSize > 0 )
			{
				for ( i = 1; i < iGridSize; i++ )
				{
					dbGrid = strYMapper.m_dbYDataMin + (double)(strYMapper.m_dbYDataMax - strYMapper.m_dbYDataMin) * (double)i / (double)iGridSize;
					iGridPosY = strYMapper.CalcYDataToPt(dbGrid);

					if ( m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.eGridVisualType == E_GRAPH2D_DATA_VISUAL_TIME && 
						 m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.bTimeGrid_CoupleRow == true )
					{
						szGrid = GetVisualDataText(dbGrid, false, false, false, iOverlapIndex);
						sizeGrid = pDC->GetTextExtent(szGrid);						
						iYOffset = sizeGrid.cy + iMarginY;
						if ( bLeft == true )
						{
							iXOffset = sizeGrid.cx + iDivisionLength + iMarginX;
							pDC->TextOut(iXPosition - iXOffset, iGridPosY - iYOffset, szGrid);
						}
						else
						{
							iXOffset = iDivisionLength + iMarginX;
							pDC->TextOut(iXPosition + iXOffset, iGridPosY - iYOffset, szGrid);
						}

						szGrid = GetVisualDataText(dbGrid, false, true, false, iOverlapIndex);						
						iYOffset = iMarginY;
						if ( bLeft == true )
						{
							sizeGrid = pDC->GetTextExtent(szGrid);
							iXOffset = sizeGrid.cx + iDivisionLength + iMarginX;
							pDC->TextOut(iXPosition - iXOffset, iGridPosY + iYOffset, szGrid);
						}
						else
						{
							iXOffset = iDivisionLength + iMarginX;
							pDC->TextOut(iXPosition + iXOffset, iGridPosY + iYOffset, szGrid);
						}
					}
					else
					{
						szGrid = GetVisualDataText(dbGrid, false, false, false, iOverlapIndex);
						sizeGrid = pDC->GetTextExtent(szGrid);						
						iYOffset = (int)(((double)(sizeGrid.cy)) / 2.);
						if ( bLeft == true )
						{
							iXOffset = sizeGrid.cx + iDivisionLength + iMarginX;
							pDC->TextOut(iXPosition - iXOffset, iGridPosY - iYOffset, szGrid);
						}
						else
						{
							iXOffset = iDivisionLength + iMarginX;
							pDC->TextOut(iXPosition + iXOffset, iGridPosY - iYOffset, szGrid);
						}
					}

					if ( bOnlyAxis == true )
					{
						m_penOld = pDC->SelectObject( &(((CGraph2D_Resource*)m_pPlotResource)->m_penAxis) );
					}
					else
					{
						m_penOld = pDC->SelectObject( &(m_arrResourceY.GetAt(iOverlapIndex)->m_penYAxis) );
					}
					pDC->MoveTo(iXPosition, iGridPosY);
					if ( bLeft == true )
					{
						pDC->LineTo(iXPosition - iDivisionLength, iGridPosY);
					}
					else
					{
						pDC->LineTo(iXPosition + iDivisionLength, iGridPosY);
					}
					pDC->SelectObject(m_penOld);

					if ( m_iShowGridY_OverlapIndex == iOverlapIndex )
					{
						//bDrawGrid = true;
						m_penOld = pDC->SelectObject( &(((CGraph2D_Resource*)m_pPlotResource)->m_penGrid) );
						pDC->MoveTo(m_DataRect.left + 1, iGridPosY);
						pDC->LineTo(m_DataRect.right - 1, iGridPosY);
						pDC->SelectObject(m_penOld);
					}
				}
			}
		}		
	}

	pDC->SelectObject(m_pOldFont);	
	pDC->SetTextColor(m_clrBackup);

	return true;
}

//! Added by LHW [2008/8/11]
CString CGraph2DWnd::GetDeltaTimeText(double dbDeltaTime)
{
	CString szReturn = _T("");

	COleDateTimeSpan timeSpanTemp;
	timeSpanTemp.m_span = fabs(dbDeltaTime);

	int iDaysTemp = 0, iHoursTemporary = 0;
	int iHoursTemp = timeSpanTemp.GetHours();
	int iMinutesTemp = timeSpanTemp.GetMinutes();
	int iSecondsTemp = timeSpanTemp.GetSeconds();

	if ( iHoursTemp < 1 )
	{
		if ( iMinutesTemp < 1 )
		{
			szReturn.Format(_T("%dsec"), iSecondsTemp);
		}
		else
		{
			szReturn.Format(_T("%dmin : %dsec"), iMinutesTemp, iSecondsTemp);
		}
	}
	else
	{
		iDaysTemp = iHoursTemp / 24;
		iHoursTemporary = iHoursTemp % 24;

		if ( iDaysTemp < 1 )
		{
			szReturn.Format(_T("%dhour : %dmin : %dsec"), iHoursTemporary, iMinutesTemp, iSecondsTemp);
		}
		else
		{
			szReturn.Format(_T("%d day : %dhour : %dmin : %dsec"), iDaysTemp, iHoursTemporary, iMinutesTemp, iSecondsTemp);
		}
	}

	return szReturn;
}

//! Added by LHW [2008/4/3]
//! Modify by LHW [2008/4/9] : E_GRAPH2D_DATA_VISUAL_MILLI_SECOND 부분 추가
//! Modify by LHW [2008/4/16] : kilo 처리 부분 추가
//! Modify by LHW [2008/6/30] : 지수 표시일 때는 kilo 처리하지 않도록 수정, eGridTextType, iPrecision 처리 부분 수정
//! Modify by LHW [2008/8/2] : iOverlapIndex 체크 부분 추가
//! Modify by LHW [2008/8/7] : 지수형 표시 부분 오류 수정
//! Modify by LHW [2008/10/22] : 정수형 표시 부분 오류 수정
//! Modify by LHW [2009/3/1] : bGridCalc, bCursorCalc 관련 수정
CString CGraph2DWnd::GetVisualDataText(double dbData, bool bDirectionX, bool bSecondRow, bool bCursorText, int iOverlapIndex)
{
	CString szReturn = _T("");

	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return szReturn;
	}
	
	bool bCoupleRowInTime = false, bKilo = false, bGridCalc = true, bCursorCalc = true;
	double dbResult = 0., dbCoeffTemp = 0., dbYOffsetTemp = 0.;
	int iPrecision = 0, iData = 0, iMinuteTemp = 0, iHourTemp = 0, iSecondTemp = 0, iMilliSecondTemp = 0;
	CString szPrecision = _T(""), szGridTimeFormat1 = _T(""), szGridTimeFormat2 = _T(""), szCursorTimeFormat = _T("");
	E_GRAPH2D_GRID_TEXT_TYPE eGridTextType = E_GRAPH2D_GRID_INTEGER;
	E_GRAPH2D_DATA_VISUAL_TYPE eGridVisualType = E_GRAPH2D_DATA_VISUAL_LINEAR;
	E_GRAPH2D_DATA_CALC_TYPE eDataCalcType = E_GRAPH2D_DATA_CALC_MULTIPLY;
	COleDateTime timeTemp;

	if ( bDirectionX == false )
	{
		//eGridTextType = m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.eGridTextType;		
		eGridVisualType = m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.eGridVisualType;
		bKilo = m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.bKilo;

		if ( bCursorText == false )
		{
			eGridTextType = m_arrResourceY.GetAt(iOverlapIndex)->m_eGridTextType;
			iPrecision = m_arrResourceY.GetAt(iOverlapIndex)->m_iGridTextPrecision;
			//iPrecision = m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.iGridTextPrecision;
		}
		else
		{
			eGridTextType = m_arrResourceY.GetAt(iOverlapIndex)->m_eCursorTextType;
			iPrecision = m_arrResourceY.GetAt(iOverlapIndex)->m_iCursorTextPrecision;
			//iPrecision = m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.iCursorTextPrecision;
		}

		bCoupleRowInTime = m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.bTimeGrid_CoupleRow;
		szGridTimeFormat1 = m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.szGridTimeFormat1;
		szGridTimeFormat2 = m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.szGridTimeformat2;
		szCursorTimeFormat = m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.szCursorTimeFormat;

		bGridCalc = m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.bGridCalc;
		bCursorCalc = m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.bCursorCalc;
	}
	else
	{
		//eGridTextType = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.eGridTextType;		
		eGridVisualType = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.eGridVisualType;
		bKilo = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bKilo;

		if ( bCursorText == false )
		{
			eGridTextType = ((CGraph2D_Resource*)m_pPlotResource)->m_eGridTextType;
			iPrecision = ((CGraph2D_Resource*)m_pPlotResource)->m_iGridTextPrecision;
			//iPrecision = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.iGridTextPrecision;
		}
		else
		{
			eGridTextType = ((CGraph2D_Resource*)m_pPlotResource)->m_eCursorTextType;
			iPrecision = ((CGraph2D_Resource*)m_pPlotResource)->m_iCursorTextPrecision;
			//iPrecision = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.iCursorTextPrecision;
		}

		bCoupleRowInTime = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bTimeGrid_CoupleRow;
		szGridTimeFormat1 = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.szGridTimeFormat1;
		szGridTimeFormat2 = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.szGridTimeformat2;
		szCursorTimeFormat = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.szCursorTimeFormat;

		bGridCalc = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bGridCalc;
		bCursorCalc = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bCursorCalc;
	}

	if ( eGridVisualType == E_GRAPH2D_DATA_VISUAL_LINEAR || eGridVisualType == E_GRAPH2D_DATA_VISUAL_CALCULATION )
	{
		switch(eGridTextType)
		{
		case E_GRAPH2D_GRID_INTEGER:
			{
				szPrecision = _T("%d");
			}
			break;
		case E_GRAPH2D_GRID_DOUBLE:
			{			
				szPrecision.Format(_T("%%.%dlf"), iPrecision);
			}
			break;
		case E_GRAPH2D_GRID_EXP:
			{
				szPrecision.Format(_T("%%.%dle"), iPrecision);
			}
			break;
		}
	}

	if ( eGridVisualType == E_GRAPH2D_DATA_VISUAL_CALCULATION )
	{
		if ( bCursorText == false )
		{
			if ( bGridCalc == false )
			{
				eGridVisualType = E_GRAPH2D_DATA_VISUAL_LINEAR;
			}
		}
		else
		{
			if ( bCursorCalc == false )
			{
				eGridVisualType = E_GRAPH2D_DATA_VISUAL_LINEAR;
			}
		}		
	}

	switch(eGridVisualType)
	{
	case E_GRAPH2D_DATA_VISUAL_LINEAR:
		{
			if ( dbData >= 1000. && bKilo == true && eGridTextType != E_GRAPH2D_GRID_EXP )
			{
				dbData /= 1000.;
				if ( eGridTextType == E_GRAPH2D_GRID_INTEGER )
				{
					szReturn.Format(szPrecision, (int)dbData);
				}
				else
				{
					szReturn.Format(szPrecision, GetFloor(dbData, iPrecision));
				}
				szReturn += _T("k");
			}
			else
			{
				if ( eGridTextType == E_GRAPH2D_GRID_EXP )
				{
					szReturn.Format(szPrecision, dbData);
				}
				else
				{
					if ( eGridTextType == E_GRAPH2D_GRID_INTEGER )
					{
						szReturn.Format(szPrecision, (int)dbData);
					}
					else
					{
						szReturn.Format(szPrecision, GetFloor(dbData, iPrecision));
					}
				}
			}
		}
		break;
	case E_GRAPH2D_DATA_VISUAL_CALCULATION:
		{
			if ( bDirectionX == true )
			{
				dbCoeffTemp = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbCoeff;
				dbYOffsetTemp = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbYOffset;
				eDataCalcType = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.eDataCalcType;
			}
			else
			{
				dbCoeffTemp = m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.dbCoeff;
				dbYOffsetTemp = m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.dbYOffset;
				eDataCalcType = m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.eDataCalcType;
			}

			if ( eDataCalcType == E_GRAPH2D_DATA_CALC_DIVIDE )
			{
				if ( fabs(dbCoeffTemp) < 0.0000001 )
				{
					dbCoeffTemp = 1.;
				}
				dbResult = (dbData / dbCoeffTemp) + dbYOffsetTemp;
			}
			else
			{
				dbResult = (dbCoeffTemp * dbData) + dbYOffsetTemp;
			}

			if ( dbResult >= 1000. && bKilo == true && eGridTextType != E_GRAPH2D_GRID_EXP )
			{
				dbResult /= 1000.;
				if ( eGridTextType == E_GRAPH2D_GRID_INTEGER )
				{
					szReturn.Format(szPrecision, (int)dbResult);
				}
				else
				{
					szReturn.Format(szPrecision, GetFloor(dbResult, iPrecision));
				}
				szReturn += _T("k");
			}
			else
			{
				if ( eGridTextType == E_GRAPH2D_GRID_EXP )
				{
					szReturn.Format(szPrecision, dbResult);
				}
				else
				{
					if ( eGridTextType == E_GRAPH2D_GRID_INTEGER )
					{
						szReturn.Format(szPrecision, (int)dbResult);
					}
					else
					{
						szReturn.Format(szPrecision, GetFloor(dbResult, iPrecision));
					}
				}
			}
		}
		break;	
	case E_GRAPH2D_DATA_VISUAL_TIME:
		{
			timeTemp.m_dt = dbData;

			if ( bCursorText == true )
			{
				szReturn = timeTemp.Format(szCursorTimeFormat);				
			}
			else
			{
				if ( bSecondRow == false )
				{
					szReturn = timeTemp.Format(szGridTimeFormat1);
				}
				else
				{
					szReturn = timeTemp.Format(szGridTimeFormat2);
				}
			}
		}
		break;
	case E_GRAPH2D_DATA_VISUAL_SECOND:
		{
			iData = (int)dbData;
			iMinuteTemp = iData / 60;
			iSecondTemp = iData - (iMinuteTemp * 60);
			iHourTemp = iMinuteTemp / 60;
			iMinuteTemp = iMinuteTemp - (iHourTemp * 60);

			if ( iHourTemp < 1 )
			{
				if ( iMinuteTemp < 1 )
				{
					szReturn.Format(_T("%dsec"), iSecondTemp);
				}
				else
				{
					szReturn.Format(_T("%dmin : %dsec"), iMinuteTemp, iSecondTemp);
				}
			}
			else
			{
				szReturn.Format(_T("%dhour : %dmin : %dsec"), iHourTemp, iMinuteTemp, iSecondTemp);
			}
		}
		break;
	case E_GRAPH2D_DATA_VISUAL_MILLI_SECOND:
		{
			iData = (int)dbData;
			iSecondTemp = iData / 1000;
			iMilliSecondTemp = iData - (iSecondTemp * 1000);
			iMinuteTemp = iSecondTemp / 60;
			iSecondTemp = iSecondTemp - (iMinuteTemp * 60);
			iHourTemp = iMinuteTemp / 60;
			iMinuteTemp = iMinuteTemp - (iHourTemp * 60);

			if ( iHourTemp < 1 )
			{
				if ( iMinuteTemp < 1 )
				{
					if ( iSecondTemp < 1 )
					{
						szReturn.Format(_T("%dmillisec"), iMilliSecondTemp);
					}
					else
					{
						szReturn.Format(_T("%dsec : %dmillisec"), iSecondTemp, iMilliSecondTemp);
					}
				}
				else
				{
					szReturn.Format(_T("%dmin : %dsec : %dmillisec"), iMinuteTemp, iSecondTemp, iMilliSecondTemp);
				}
			}
			else
			{
				szReturn.Format(_T("%dhour : %dmin : %dsec : %dmillisec"), iHourTemp, iMinuteTemp, iSecondTemp, iMilliSecondTemp);
			}
		}
		break;	
	}

	return szReturn;
}

//! Added by LHW [2008/8/02]
double CGraph2DWnd::GetCalcData(double dbData, bool bDirectionX, bool bCursorText, int iOverlapIndex)
{
	double dbReturn = -1.;

	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return dbReturn;
	}

	//bool bKilo = false;
	double dbCoeffTemp = 0., dbYOffsetTemp = 0.;
	//E_GRAPH2D_GRID_TEXT_TYPE eGridTextType = E_GRAPH2D_GRID_INTEGER;
	E_GRAPH2D_DATA_VISUAL_TYPE eGridVisualType = E_GRAPH2D_DATA_VISUAL_LINEAR;
	E_GRAPH2D_DATA_CALC_TYPE eDataCalcType = E_GRAPH2D_DATA_CALC_MULTIPLY;

	if ( bDirectionX == false )
	{
		eGridVisualType = m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.eGridVisualType;
		//bKilo = m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.bKilo;

		/*if ( bCursorText == false )
		{
			eGridTextType = m_arrResourceY.GetAt(iOverlapIndex)->m_eGridTextType;
		}
		else
		{
			eGridTextType = m_arrResourceY.GetAt(iOverlapIndex)->m_eCursorTextType;
		}*/
	}
	else
	{
		eGridVisualType = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.eGridVisualType;
		//bKilo = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bKilo;

		/*if ( bCursorText == false )
		{
			eGridTextType = ((CGraph2D_Resource*)m_pPlotResource)->m_eGridTextType;
		}
		else
		{
			eGridTextType = ((CGraph2D_Resource*)m_pPlotResource)->m_eCursorTextType;
		}*/
	}

	switch(eGridVisualType)
	{
	case E_GRAPH2D_DATA_VISUAL_LINEAR:
		{
			dbReturn = dbData;

			/*if ( dbReturn >= 1000. && bKilo == true && eGridTextType != E_GRAPH2D_GRID_EXP )
			{
				dbReturn /= 1000.;
			}*/			
		}
		break;
	case E_GRAPH2D_DATA_VISUAL_CALCULATION:
		{
			if ( bDirectionX == true )
			{
				dbCoeffTemp = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbCoeff;
				dbYOffsetTemp = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbYOffset;
				eDataCalcType = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.eDataCalcType;
			}
			else
			{
				dbCoeffTemp = m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.dbCoeff;
				dbYOffsetTemp = m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.dbYOffset;
				eDataCalcType = m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.eDataCalcType;
			}

			if ( eDataCalcType == E_GRAPH2D_DATA_CALC_DIVIDE )
			{
				if ( fabs(dbCoeffTemp) < 0.0000001 )
				{
					dbCoeffTemp = 1.;
				}
				dbReturn = (dbData / dbCoeffTemp) + dbYOffsetTemp;
			}
			else
			{
				dbReturn = (dbCoeffTemp * dbData) + dbYOffsetTemp;
			}

			/*if ( dbReturn >= 1000. && bKilo == true && eGridTextType != E_GRAPH2D_GRID_EXP )
			{
				dbReturn /= 1000.;
			}*/
		}
		break;
	}

	return dbReturn;
}

//! Modify by LHW [2008/4/3] : X축 표시 문자열이 Linear, Time, Second 등 일 때를 구분하도록 수정
//! Modify by LHW [2008/4/9] : E_GRAPH2D_DATA_VISUAL_MILLI_SECOND 부분 추가
//! Modify by LHW [2008/4/19] : bXYCaptionPosition이 true일 때만 'X' 표시
//! Modify by LHW [2008/7/02] : X축 눈금 문자열의 위치 체크 추가
//! Modify by LHW [2008/7/24] : bXYCaptionPosition이 아닌 eXYCaptionPosition 으로 수정, 맨 아래쪽 Y 좌표 알아내는 부분 추가, Margin 관련값 수정
//! Modify by LHW [2008/7/30] : m_iShowGridY_OverlapIndex 추가
//! Modify by LHW [2008/10/24] : E_GRAPH2D_XY_CAPTION_POS_ONLY_XY 추가
//! Modify by LHW [2008/12/27] : E_GRAPH2D_XY_CAPTION_POS_ONE_Y 추가
//! Modify by LHW [2012/12/20] : E_GRAPH2D_XY_CAPTION_POS_ONLY_X 적용
//! Modify by LHW [2013/3/26] : bDirection_Plus 적용
bool CGraph2DWnd::DrawAxis(CDC *pDC)
{
	if ( m_DataRect.Width() <= 0 || m_DataRect.Height() <= 0 )
	{
		return false;
	}

	pDC->SetBkMode(TRANSPARENT);

	//! 축 외곽선 그리기
	m_penOld = pDC->SelectObject( &(((CGraph2D_Resource*)m_pPlotResource)->m_penAxis) );
	int iAxisThickness = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.iAxisThickness;
	if ( iAxisThickness <= 0 )
	{
		iAxisThickness = 1;
	}
	iAxisThickness--;
	pDC->MoveTo(m_DataRect.left, m_DataRect.top);
	pDC->LineTo(m_DataRect.right + iAxisThickness, m_DataRect.top);
	pDC->LineTo(m_DataRect.right + iAxisThickness, m_DataRect.bottom + iAxisThickness);
	pDC->LineTo(m_DataRect.left, m_DataRect.bottom + iAxisThickness);
	pDC->LineTo(m_DataRect.left, m_DataRect.top - iAxisThickness);
	pDC->SelectObject(m_penOld);

	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize <= 0 )
	{
		return false;
	}
	if ( GetRealDataSize() <= 0 )
	{
		return false;
	}

	int iDivisionLength = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.iDivisionLength;	//! 눈금선의 길이
	int iMarginY = m_iGridMarginY;
	int iMarginX = m_iGridMarginX;

	bool bSetBottomPos = false;
	int iBottomPosY = 0;

	bool bStop = false;
	int i = 0, iXPos = 0, iXOffset = 0, iYOffset = 0, iGridPosX = 0, iGridPosY = 0, iGridSize = 0;
	double dbGrid = 0., dbIncrement= 0.;
	CString szGrid = _T("");
	CSize sizeGrid;
	
	m_pOldFont = pDC->SelectObject( &(((CGraph2D_Resource*)m_pPlotResource)->m_ftGridText) );
	m_clrBackup = pDC->GetTextColor();
	pDC->SetTextColor(((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.clrGridText);

	//! 최소값을 그릴 경우
	if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bShowMin == true )
	{
		szGrid = GetVisualDataText(m_XMapper.m_dbXDataMin, true, false, false);
		sizeGrid = pDC->GetTextExtent(szGrid);
		if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.eGridVisualType == E_GRAPH2D_DATA_VISUAL_TIME && 
			((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bTimeGrid_CoupleRow == true )
		{
			iXOffset = 0;
		}
		else if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.eGridVisualType == E_GRAPH2D_DATA_VISUAL_SECOND || 
			((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.eGridVisualType == E_GRAPH2D_DATA_VISUAL_MILLI_SECOND )
		{
			iXOffset = 0;
		}
		else
		{			
			iXOffset = (int)(((double)(sizeGrid.cx)) / 2.);
		}
		iGridPosX = m_XMapper.m_iXPtMin - iXOffset;
		if ( iGridPosX < m_CurRect.left )
		{
			iGridPosX = m_CurRect.left;
		}
		iGridPosY = m_DataRect.bottom + iDivisionLength + iMarginY;
		pDC->TextOut(iGridPosX, iGridPosY, szGrid);

		if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.eGridVisualType == E_GRAPH2D_DATA_VISUAL_TIME && 
			((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bTimeGrid_CoupleRow == true )
		{
			iGridPosY += sizeGrid.cy;
			szGrid = GetVisualDataText(m_XMapper.m_dbXDataMin, true, true, false);
			sizeGrid = pDC->GetTextExtent(szGrid);
			iXOffset = 0;
			iGridPosX = m_XMapper.m_iXPtMin - iXOffset;
			if ( iGridPosX < m_CurRect.left )
			{
				iGridPosX = m_CurRect.left;
			}
			iGridPosY += (iMarginY);
			pDC->TextOut(iGridPosX, iGridPosY, szGrid);
		}

		m_penOld = pDC->SelectObject( &(((CGraph2D_Resource*)m_pPlotResource)->m_penAxis) );
		pDC->MoveTo(m_XMapper.m_iXPtMin, m_DataRect.bottom);
		pDC->LineTo(m_XMapper.m_iXPtMin, m_DataRect.bottom + iDivisionLength);
		pDC->SelectObject(m_penOld);

		if ( bSetBottomPos == false )
		{
			iBottomPosY = iGridPosY + sizeGrid.cy;
			bSetBottomPos = true;
		}
	}

	//! 최대값을 그릴 경우
	if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bShowMax == true )
	{
		szGrid = GetVisualDataText(m_XMapper.m_dbXDataMax, true, false, false);
		sizeGrid = pDC->GetTextExtent(szGrid);
		if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.eGridVisualType == E_GRAPH2D_DATA_VISUAL_TIME && 
			((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bTimeGrid_CoupleRow == true )
		{
			iXOffset = sizeGrid.cx;
		}
		else if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.eGridVisualType == E_GRAPH2D_DATA_VISUAL_SECOND || 
			((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.eGridVisualType == E_GRAPH2D_DATA_VISUAL_MILLI_SECOND )
		{
			iXOffset = sizeGrid.cx;
		}
		else
		{
			iXOffset = (int)(((double)(sizeGrid.cx)) / 2.);
		}
		iGridPosX = m_XMapper.m_iXPtMax - iXOffset;
		if ( (m_XMapper.m_iXPtMax + iXOffset) > m_CurRect.right )
		{
			iGridPosX = m_CurRect.right - sizeGrid.cx;
		}
		iGridPosY = m_DataRect.bottom + iDivisionLength + iMarginY;
		pDC->TextOut(iGridPosX, iGridPosY, szGrid);

		if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.eGridVisualType == E_GRAPH2D_DATA_VISUAL_TIME && 
			((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bTimeGrid_CoupleRow == true )
		{
			iGridPosY += sizeGrid.cy;
			szGrid = GetVisualDataText(m_XMapper.m_dbXDataMax, true, true, false);
			sizeGrid = pDC->GetTextExtent(szGrid);
			iXOffset = sizeGrid.cx;
			iGridPosX = m_XMapper.m_iXPtMax - iXOffset;
			if ( (m_XMapper.m_iXPtMax + iXOffset) > m_CurRect.right )
			{
				iGridPosX = m_CurRect.right - sizeGrid.cx;
			}
			iGridPosY += (iMarginY);
			pDC->TextOut(iGridPosX, iGridPosY, szGrid);
		}

		m_penOld = pDC->SelectObject( &(((CGraph2D_Resource*)m_pPlotResource)->m_penAxis) );
		pDC->MoveTo(m_XMapper.m_iXPtMax, m_DataRect.bottom);
		pDC->LineTo(m_XMapper.m_iXPtMax, m_DataRect.bottom + iDivisionLength);
		pDC->SelectObject(m_penOld);

		if ( bSetBottomPos == false )
		{
			iBottomPosY = iGridPosY + sizeGrid.cy;
			bSetBottomPos = true;
		}
	}

	//! 중간 부분의 눈금을 그릴 경우
	if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bShowGrid == true )
	{
		//! 고정된 X축 간격으로 눈금 위치를 설정
		if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bIncrementGrid == true )
		{
			if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bDirection_Plus == true )
			{
				//! 왼쪽에서 오른쪽으로 값이 증가
				dbIncrement = fabs(((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbIncrementGrid);
			}
			else
			{
				//! 오른쪽에서 왼쪽으로 값이 증가
				dbIncrement = (-1.) * fabs(((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbIncrementGrid);
			}

			bStop = false;

			//if ( dbIncrement > 0. )
			//{
				dbGrid = m_XMapper.m_dbXDataMin + dbIncrement;

				while(1)
				{
					if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bDirection_Plus == true )
					{
						//! 왼쪽에서 오른쪽으로 값이 증가
						if ( dbGrid >= m_XMapper.m_dbXDataMax )
						{
							bStop = true;
						}
					}
					else
					{
						//! 오른쪽에서 왼쪽으로 값이 증가
						if ( dbGrid <= m_XMapper.m_dbXDataMax )
						{
							bStop = true;
						}
					}

					if ( bStop == true )
					{
						break;
					}

					iXPos = m_XMapper.CalcXDataToPt(dbGrid);

					szGrid = GetVisualDataText(dbGrid, true, false, false);
					sizeGrid = pDC->GetTextExtent(szGrid);
					iXOffset = (int)(((double)(sizeGrid.cx)) / 2.);
					iGridPosX = iXPos - iXOffset;
					if ( iGridPosX < m_CurRect.left )
					{
						iGridPosX = m_CurRect.left;
					}
					if ( (iXPos + iXOffset) > m_CurRect.right )
					{
						iGridPosX = m_CurRect.right - sizeGrid.cx;
					}
					iGridPosY = m_DataRect.bottom + iDivisionLength + iMarginY;
					pDC->TextOut(iGridPosX, iGridPosY, szGrid);

					if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.eGridVisualType == E_GRAPH2D_DATA_VISUAL_TIME && 
						 ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bTimeGrid_CoupleRow == true )
					{
						iGridPosY += sizeGrid.cy;
						szGrid = GetVisualDataText(dbGrid, true, true, false);
						sizeGrid = pDC->GetTextExtent(szGrid);
						iXOffset = (int)(((double)(sizeGrid.cx)) / 2.);
						iGridPosX = iXPos - iXOffset;
						if ( iGridPosX < m_CurRect.left )
						{
							iGridPosX = m_CurRect.left;
						}
						if ( (iXPos + iXOffset) > m_CurRect.right )
						{
							iGridPosX = m_CurRect.right - sizeGrid.cx;
						}
						iGridPosY += (iMarginY);
						pDC->TextOut(iGridPosX, iGridPosY, szGrid);
					}

					m_penOld = pDC->SelectObject( &(((CGraph2D_Resource*)m_pPlotResource)->m_penAxis) );
					pDC->MoveTo(iXPos, m_DataRect.bottom);
					pDC->LineTo(iXPos, m_DataRect.bottom + iDivisionLength);
					pDC->SelectObject(m_penOld);

					m_penOld = pDC->SelectObject( &(((CGraph2D_Resource*)m_pPlotResource)->m_penGrid) );
					pDC->MoveTo(iXPos, m_DataRect.top + 1);
					pDC->LineTo(iXPos, m_DataRect.bottom - 1);
					pDC->SelectObject(m_penOld);

					dbGrid += dbIncrement;

					if ( bSetBottomPos == false )
					{
						iBottomPosY = iGridPosY + sizeGrid.cy;
						bSetBottomPos = true;
					}
				}//! while(1)
			//}
		}
		else
		{
			//! 고정된 눈금 개수를 현재 X축 폭으로 나누어 눈금 위치 설정
			iGridSize = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.iGridSize;
			if ( iGridSize > 0 )
			{
				for ( i = 1; i < iGridSize; i++ )
				{
					dbGrid = m_XMapper.m_dbXDataMin + (double)(m_XMapper.m_dbXDataMax - m_XMapper.m_dbXDataMin) * (double)i / (double)iGridSize;
					iXPos = m_XMapper.CalcXDataToPt(dbGrid);

					szGrid = GetVisualDataText(dbGrid, true, false, false);
					sizeGrid = pDC->GetTextExtent(szGrid);
					iXOffset = (int)(((double)(sizeGrid.cx)) / 2.);
					iGridPosX = iXPos - iXOffset;
					if ( iGridPosX < m_CurRect.left )
					{
						iGridPosX = m_CurRect.left;
					}
					if ( (iXPos + iXOffset) > m_CurRect.right )
					{
						iGridPosX = m_CurRect.right - sizeGrid.cx;
					}
					iGridPosY = m_DataRect.bottom + iDivisionLength + iMarginY;
					pDC->TextOut(iGridPosX, iGridPosY, szGrid);

					if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.eGridVisualType == E_GRAPH2D_DATA_VISUAL_TIME && 
						 ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bTimeGrid_CoupleRow == true )
					{
						iGridPosY += sizeGrid.cy;
						szGrid = GetVisualDataText(dbGrid, true, true, false);
						sizeGrid = pDC->GetTextExtent(szGrid);
						iXOffset = (int)(((double)(sizeGrid.cx)) / 2.);
						iGridPosX = iXPos - iXOffset;
						if ( iGridPosX < m_CurRect.left )
						{
							iGridPosX = m_CurRect.left;
						}
						if ( (iXPos + iXOffset) > m_CurRect.right )
						{
							iGridPosX = m_CurRect.right - sizeGrid.cx;
						}
						iGridPosY += (iMarginY);
						pDC->TextOut(iGridPosX, iGridPosY, szGrid);
					}

					m_penOld = pDC->SelectObject( &(((CGraph2D_Resource*)m_pPlotResource)->m_penAxis) );
					pDC->MoveTo(iXPos, m_DataRect.bottom);
					pDC->LineTo(iXPos, m_DataRect.bottom + iDivisionLength);
					pDC->SelectObject(m_penOld);

					m_penOld = pDC->SelectObject( &(((CGraph2D_Resource*)m_pPlotResource)->m_penGrid) );
					pDC->MoveTo(iXPos, m_DataRect.top + 1);
					pDC->LineTo(iXPos, m_DataRect.bottom - 1);
					pDC->SelectObject(m_penOld);

					if ( bSetBottomPos == false )
					{
						iBottomPosY = iGridPosY + sizeGrid.cy;
						bSetBottomPos = true;
					}
				}
			}
		}
	}

	pDC->SelectObject(m_pOldFont);	
	pDC->SetTextColor(m_clrBackup);


	switch( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition )
	{
	case E_GRAPH2D_XY_CAPTION_POS_UNITE:
	case E_GRAPH2D_XY_CAPTION_POS_ONLY_XY:
		{
			m_pOldFont = pDC->SelectObject( &(((CGraph2D_Resource*)m_pPlotResource)->m_ftLegend) );
			m_clrBackup = pDC->GetTextColor();
			pDC->SetTextColor(((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.clrLegend);

			//! X축 오른쪽에 'X"라는 표시를 그림
			szGrid = _T("X");
			sizeGrid = pDC->GetTextExtent(szGrid);
			pDC->TextOut(m_DataRect.right + 5, m_DataRect.bottom - sizeGrid.cy, szGrid);

			pDC->SelectObject(m_pOldFont);	
			pDC->SetTextColor(m_clrBackup);
		}
		break;		
	case E_GRAPH2D_XY_CAPTION_POS_SEPARATE:
	case E_GRAPH2D_XY_CAPTION_POS_UNITE_Y:
	case E_GRAPH2D_XY_CAPTION_POS_ONE_Y:
	case E_GRAPH2D_XY_CAPTION_POS_ONLY_X:
		{
			if ( bSetBottomPos == false )
			{
				iBottomPosY = m_DataRect.bottom;
				bSetBottomPos = true;
			}

			iBottomPosY += (iMarginY);

			m_pOldFont = pDC->SelectObject( &(((CGraph2D_Resource*)m_pPlotResource)->m_ftLegend) );
			m_clrBackup = pDC->GetTextColor();
			pDC->SetTextColor(((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.clrLegend);

			szGrid = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.szCaption1;
			if ( szGrid.GetLength() > 0 )
			{
				sizeGrid = pDC->GetTextExtent(szGrid);
				pDC->TextOut(m_DataRect.left + ((int)(((double)(m_DataRect.Width())) / 2.)) - (int)(((double)(sizeGrid.cx)) / 2.), iBottomPosY, szGrid);
			}

			pDC->SelectObject(m_pOldFont);	
			pDC->SetTextColor(m_clrBackup);
		}
		break;
	}

	if ( IsShowGraph() == false )
	{
		return false;
	}

	if ( iGraphSize > 1 && m_bMultiPlotOneAxis == false )	//! 그래프가 여러 개이고, Multi-Axis로 표시해야 할 때
	{
		//! 왼쪽 Y축을 그림
		for ( i = (iGraphSize - 1); i >= 0; i-- )
		{
			if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.bAxisLeft == true )
			{
				if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.bShowGraph == true )
				{
					DrawAxisY(pDC, i, false, true);
				}
			}
		}

		//! 오른쪽 Y축을 그림
		for ( i = 0; i < iGraphSize; i++ )
		{
			if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.bAxisLeft == false )
			{
				if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.bShowGraph == true )
				{
					DrawAxisY(pDC, i, false, false);
				}
			}
		}
	}
	else	//! Y축이 1개만 있을 경우
	{
		m_iShowGridY_OverlapIndex = 0;

		if ( m_arrResourceY.GetAt(0)->m_strResourceYinfo.bAxisLeft == true )
		{
			DrawAxisY(pDC, 0, true, true);
		}
		else
		{
			DrawAxisY(pDC, 0, true, false);
		}
	}

	return true;
}

//! Modify by LHW [2008/4/18] : 제목 표시 부분을 윗쪽으로 이동
//! Modify by LHW [2008/8/01] : eXYCaptionPosition, bYCaptionLeftPos 관련 부분 추가, 수정
//! Modify by LHW [2008/10/24] : 반환값 부분 수정
//! Modify by LHW [2008/11/28] : 각 축의 통합 문자열 표시 부분 수정
//! Modify by LHW [2008/12/27] : E_GRAPH2D_XY_CAPTION_POS_ONE_Y 관련 추가
bool CGraph2DWnd::DrawInfo(CDC *pDC)
{
	if ( m_pPlotResource == NULL )
	{
		return false;
	}
	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize <= 0 )
	{
		return false;
	}

	pDC->SetBkMode(TRANSPARENT);

	int iXOffset = 0;
	CString szInfo = _T("");
	CSize sizeInfo;
	int iXPos = 0, iYPos = 0;

	//! 주 제목
	if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strMainTitleInfo.bShow == true && m_MainTitleRect.Height() > 0 && m_MainTitleRect.Width() > 0 )
	{
		m_clrBackup = pDC->GetTextColor();
		m_pOldFont = pDC->SelectObject( &( ((CGraph2D_Resource*)m_pPlotResource)->m_ftMainTitle ) );
		pDC->SetTextColor( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strSubTitleInfo.clrTitle );
		szInfo = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strMainTitleInfo.szTitle;
		sizeInfo = pDC->GetTextExtent(szInfo);		
		switch(((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strMainTitleInfo.eAlign)
		{
		case E_GRAPH2D_TITLE_ALIGN_LEFT:
			{
				iXOffset = (int)(((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strMainTitleInfo.dbLeftMargin * ((double)(m_MainTitleRect.Width())) / 100.);
				iXPos = m_MainTitleRect.left + iXOffset;
			}
			break;
		case E_GRAPH2D_TITLE_ALIGN_CENTER:
			{
				iXOffset = (int)(((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strMainTitleInfo.dbLeftMargin * ((double)(m_MainTitleRect.Width())) / 100.);
				iXPos = m_MainTitleRect.left + (int)(((double)(m_MainTitleRect.Width())) / 2.) - (int)((double)(sizeInfo.cx) / 2.) + iXOffset;	
			}
			break;
		case E_GRAPH2D_TITLE_ALIGN_RIGHT:
			{
				iXOffset = (int)(((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strMainTitleInfo.dbRightMargin * ((double)(m_MainTitleRect.Width())) / 100.);
				iXPos = m_MainTitleRect.right - iXOffset - sizeInfo.cx;
			}
			break;
		}
		iYPos = m_MainTitleRect.top + 1;
		pDC->TextOut(iXPos, iYPos, szInfo);
		pDC->SetTextColor(m_clrBackup);
		pDC->SelectObject(m_pOldFont);		
	}

	//! 부 제목
	if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strSubTitleInfo.bShow == true && m_SubTitleRect.Height() > 0 && m_SubTitleRect.Width() > 0 )
	{
		m_clrBackup = pDC->GetTextColor();
		m_pOldFont = pDC->SelectObject( &( ((CGraph2D_Resource*)m_pPlotResource)->m_ftSubTitle ) );
		pDC->SetTextColor( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strMainTitleInfo.clrTitle );
		szInfo = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strSubTitleInfo.szTitle;
		sizeInfo = pDC->GetTextExtent(szInfo);
		switch(((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strSubTitleInfo.eAlign)
		{
		case E_GRAPH2D_TITLE_ALIGN_LEFT:
			{
				iXOffset = (int)(((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strSubTitleInfo.dbLeftMargin * ((double)(m_SubTitleRect.Width())) / 100.);
				iXPos = m_SubTitleRect.left + iXOffset;
			}
			break;
		case E_GRAPH2D_TITLE_ALIGN_CENTER:
			{
				iXOffset = (int)(((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strSubTitleInfo.dbLeftMargin * ((double)(m_SubTitleRect.Width())) / 100.);
				iXPos = m_SubTitleRect.left + (int)(((double)(m_SubTitleRect.Width())) / 2.) - (int)((double)(sizeInfo.cx) / 2.) + iXOffset;
			}
			break;
		case E_GRAPH2D_TITLE_ALIGN_RIGHT:
			{
				iXOffset = (int)(((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strSubTitleInfo.dbRightMargin * ((double)(m_SubTitleRect.Width())) / 100.);
				iXPos = m_SubTitleRect.right - iXOffset - sizeInfo.cx;
			}
			break;
		}
		iYPos = m_SubTitleRect.top + 1;
		pDC->TextOut(iXPos, iYPos, szInfo);
		pDC->SetTextColor(m_clrBackup);
		pDC->SelectObject(m_pOldFont);		
	}

	if ( GetRealDataSize() <= 0 )
	{
		return true;
	}

	int i = 0;

	if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition == E_GRAPH2D_XY_CAPTION_POS_UNITE || 
		 ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition == E_GRAPH2D_XY_CAPTION_POS_UNITE_Y )
	{
		//! 표시할 문자열이 없을 경우를 체크
		int iLenMin = 0, iLenTemp = 0;
		if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition != E_GRAPH2D_XY_CAPTION_POS_UNITE_Y )
		{
			iLenMin = ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.szCaption1.GetLength();
		}
		else
		{
			iLenMin = INT_MIN;
		}

		for ( i = 0; i < iGraphSize; i++ )
		{
			if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.bShowGraph == true && m_arrPlotData.GetAt(i)->GetPointSize() > 0 )
			{
				iLenTemp = m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.szCaption1.GetLength();
				if ( iLenMin < iLenTemp )
				{
					iLenMin = iLenTemp;
				}
			}
		}
		if ( iLenMin <= 0 )
		{
			return true;
		}
	}
	else if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition == E_GRAPH2D_XY_CAPTION_POS_ONE_Y )
	{
		if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.szCaptionY.GetLength() <= 0 )
		{
			return true;
		}
	}
	else
	{
		return true;
	}
	
	CString szAddTemp = _T("");
	strYCaption strAddCaptionY, strCaptionY;
	CArray<strYCaption, strYCaption&> arrCaptionY;
	arrCaptionY.RemoveAll();
	arrCaptionY.FreeExtra();

	//! 문자열의 전체 길이를 알기 위해 문자열을 연결하여 szInfo에 입력
	szInfo = _T("[");

	int iCount_LeftPosY = 0, iCount_RightPosY = 0;	//! Y축이 왼쪽에 그려지는지 오른쪽에 그려지는지의 개수

	if ( (((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition != E_GRAPH2D_XY_CAPTION_POS_UNITE_Y) && 
		(((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition != E_GRAPH2D_XY_CAPTION_POS_ONE_Y) )
	{
		szAddTemp.Format(_T("X : %s"), ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.szCaption1);
		szInfo += szAddTemp;
	}

	if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition == E_GRAPH2D_XY_CAPTION_POS_ONE_Y )
	{
		szAddTemp.Format(_T("%s]"), ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.szCaptionY);
		szInfo += szAddTemp;
	}
	else
	{
		if ( iGraphSize == 1 )
		{
			if ( m_arrResourceY.GetAt(0)->m_strResourceYinfo.bShowGraph == true && m_arrPlotData.GetAt(0)->GetPointSize() > 0 )
			{
				if ( m_arrResourceY.GetAt(0)->m_strResourceYinfo.bAxisLeft == true )
				{
					iCount_LeftPosY++;
				}
				else
				{
					iCount_RightPosY++;
				}

				if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition == E_GRAPH2D_XY_CAPTION_POS_UNITE_Y )
				{
					szAddTemp.Format(_T("Y1 : %s"), m_arrResourceY.GetAt(0)->m_strResourceYinfo.strAxisInfo.szCaption1);
					szInfo += szAddTemp;
				}
				else
				{
					szAddTemp = _T(", ");
					szInfo += szAddTemp;
					szAddTemp.Format(_T("Y : %s"), m_arrResourceY.GetAt(0)->m_strResourceYinfo.strAxisInfo.szCaption1);
					szInfo += szAddTemp;
				}
			}
			szAddTemp = _T("]");
			szInfo += szAddTemp;
		}
		else
		{
			if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition == E_GRAPH2D_XY_CAPTION_POS_UNITE && m_bMultiPlotOneAxis == true )
			{
				if ( IsShowGraph() == true )
				{
					szAddTemp = _T(", ");
					szInfo += szAddTemp;
					szAddTemp = _T("Y : ");
					szInfo += szAddTemp;

					for ( i = 0; i < iGraphSize; i++ )
					{
						if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.bShowGraph == true && m_arrPlotData.GetAt(i)->GetPointSize() > 0 )
						{
							if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.bAxisLeft == true )
							{
								iCount_LeftPosY++;
							}
							else
							{
								iCount_RightPosY++;
							}

							szAddTemp.Format(_T("%s"), m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.szCaption1);
							strAddCaptionY.szCaption = szAddTemp;
							strAddCaptionY.clrCaption = m_arrResourceY.GetAt(i)->m_strResourceYinfo.clrData;
							arrCaptionY.Add(strAddCaptionY);
							szInfo += szAddTemp;

							szAddTemp = _T(", ");
							szInfo += szAddTemp;
						}
					}
				}			

				szInfo.TrimRight(_T(" "));
				szInfo.TrimRight(_T(","));
				szAddTemp = _T("]");
				szInfo += szAddTemp;
			}
			else
			{
				for ( i = 0; i < iGraphSize; i++ )
				{
					if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.bShowGraph == true && m_arrPlotData.GetAt(i)->GetPointSize() > 0 )
					{
						if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.bAxisLeft == true )
						{
							iCount_LeftPosY++;
						}
						else
						{
							iCount_RightPosY++;
						}

						if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition == E_GRAPH2D_XY_CAPTION_POS_UNITE && i == 0 )
						{
							szAddTemp = _T(", ");
							szInfo += szAddTemp;
						}

						szAddTemp.Format(_T("Y%d : %s"), i + 1, m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.szCaption1);
						strAddCaptionY.szCaption = szAddTemp;
						strAddCaptionY.clrCaption = m_arrResourceY.GetAt(i)->m_strResourceYinfo.clrData;
						arrCaptionY.Add(strAddCaptionY);
						szInfo += szAddTemp;					
					}
				}

				szInfo.TrimRight(_T(" "));
				szInfo.TrimRight(_T(","));
				szAddTemp = _T("]");
				szInfo += szAddTemp;
			}		
		}
	}

	m_pOldFont = pDC->SelectObject( &( ((CGraph2D_Resource*)m_pPlotResource)->m_ftLegend ) );
	
	sizeInfo = pDC->GetTextExtent(szInfo);	//! 문자열의 크기를 알아냄
	

	if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.bYCaptionLeftPos == true )
	{
		if ( iCount_LeftPosY > 0 )
		{
			iXPos = m_AxisCaptionRect.left + m_iAxisCaptionMarginX;
		}
		else
		{
			iXPos = m_AxisCaptionRect.left;
		}
	}
	else
	{
		if ( iCount_RightPosY > 0 )
		{
			iXPos = m_AxisCaptionRect.right - sizeInfo.cx - m_iAxisCaptionMarginX;
		}
		else
		{
			iXPos = m_AxisCaptionRect.right - sizeInfo.cx;
		}
	}
	iYPos = m_AxisCaptionRect.top + 1;

	if ( (((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition == E_GRAPH2D_XY_CAPTION_POS_UNITE && iGraphSize == 1) || 
		 (((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition == E_GRAPH2D_XY_CAPTION_POS_ONE_Y) )
	{
		m_clrBackup = pDC->GetTextColor();
		pDC->SetTextColor( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.clrLegend );
		pDC->TextOut(iXPos, iYPos, szInfo);
		pDC->SetTextColor(m_clrBackup);
	}
	else
	{
		//! Y축이 여러 개일 경우 그래프 색상에 맞추어 글자색을 설정

		m_clrBackup = pDC->GetTextColor();
		pDC->SetTextColor( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.clrLegend );

		szInfo = _T("[");
		sizeInfo = pDC->GetTextExtent(szInfo);
		pDC->TextOut(iXPos, iYPos, szInfo);
		iXPos += sizeInfo.cx;

		if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition == E_GRAPH2D_XY_CAPTION_POS_UNITE )
		{
			szInfo.Format(_T("X : %s"), ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.szCaption1);
			sizeInfo = pDC->GetTextExtent(szInfo);
			pDC->TextOut(iXPos, iYPos, szInfo);
			iXPos += sizeInfo.cx;
		}

		pDC->SetTextColor(m_clrBackup);


		int iYCaptionSize = (int)(arrCaptionY.GetSize());

		if ( iYCaptionSize > 0 )
		{
			if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition == E_GRAPH2D_XY_CAPTION_POS_UNITE && m_bMultiPlotOneAxis == true )
			{
				if ( IsShowGraph() == true )
				{
					szInfo = _T(", ");
					szInfo += _T("Y : ");
					m_clrBackup = pDC->GetTextColor();
					pDC->SetTextColor( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.clrLegend );
					sizeInfo = pDC->GetTextExtent(szInfo);
					pDC->TextOut(iXPos, iYPos, szInfo);
					iXPos += sizeInfo.cx;
					pDC->SetTextColor(m_clrBackup);

					for ( i = 0; i < iYCaptionSize; i++ )
					{
						strCaptionY = arrCaptionY.GetAt(i);
						szInfo = strCaptionY.szCaption;

						m_clrBackup = pDC->GetTextColor();
						pDC->SetTextColor( strCaptionY.clrCaption );

						szInfo = strCaptionY.szCaption;
						sizeInfo = pDC->GetTextExtent(szInfo);
						pDC->TextOut(iXPos, iYPos, szInfo);
						iXPos += sizeInfo.cx;

						pDC->SetTextColor(m_clrBackup);


						if ( i != (iYCaptionSize - 1) )
						{
							m_clrBackup = pDC->GetTextColor();
							pDC->SetTextColor( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.clrLegend );

							szInfo = _T(", ");
							sizeInfo = pDC->GetTextExtent(szInfo);
							pDC->TextOut(iXPos, iYPos, szInfo);
							iXPos += sizeInfo.cx;

							pDC->SetTextColor(m_clrBackup);
						}
					}
				}
			}
			else
			{
				if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.eXYCaptionPosition == E_GRAPH2D_XY_CAPTION_POS_UNITE )
				{
					m_clrBackup = pDC->GetTextColor();
					pDC->SetTextColor( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.clrLegend );

					szInfo = _T(", ");
					sizeInfo = pDC->GetTextExtent(szInfo);
					pDC->TextOut(iXPos, iYPos, szInfo);
					iXPos += sizeInfo.cx;

					pDC->SetTextColor(m_clrBackup);
				}

				for ( i = 0; i < iYCaptionSize; i++ )
				{
					strCaptionY = arrCaptionY.GetAt(i);
					szInfo = strCaptionY.szCaption;

					m_clrBackup = pDC->GetTextColor();
					pDC->SetTextColor( strCaptionY.clrCaption );
					
					sizeInfo = pDC->GetTextExtent(szInfo);
					pDC->TextOut(iXPos, iYPos, szInfo);
					iXPos += sizeInfo.cx;

					pDC->SetTextColor(m_clrBackup);

					if ( i != (iYCaptionSize - 1) )
					{
						m_clrBackup = pDC->GetTextColor();
						pDC->SetTextColor( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.clrLegend );

						szInfo = _T(", ");
						sizeInfo = pDC->GetTextExtent(szInfo);
						pDC->TextOut(iXPos, iYPos, szInfo);
						iXPos += sizeInfo.cx;

						pDC->SetTextColor(m_clrBackup);
					}
				}
			}
		}

		m_clrBackup = pDC->GetTextColor();
		pDC->SetTextColor( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.clrLegend );
		szInfo = _T("]");
		pDC->TextOut(iXPos, iYPos, szInfo);
		pDC->SetTextColor(m_clrBackup);
	}
	
	pDC->SelectObject(m_pOldFont);

	arrCaptionY.RemoveAll();
	arrCaptionY.FreeExtra();

	return true;
}

//! Added by LHW [2008/5/23]
//! Modify by LHW [2008/8/9] : 영역 index 관련 오류 수정
bool CGraph2DWnd::SetDataPointRect()
{
	if ( m_DataRect.Width() <= 0 || m_DataRect.Height() <= 0 )
	{
		return false;
	}
	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize <= 0 )
	{
		return false;
	}

	int i = 0, j = 0, iXPt = 0, iYPt = 0, iDrawDataSize = 0, iEventRectSize = 0;
	int iVisualDataStartIndex = 0, iVisualDataEndIndex = 0;
	strYRangeMapper strYMapper;
	CRect crEvent;

	for ( i = 0; i < iGraphSize; i++ )
	{
		if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.bShowGraph == false )
		{
			continue;
		}
		if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.bShowEventRect == false )
		{
			continue;
		}

		iDrawDataSize = m_arrPlotData.GetAt(i)->GetPointSize();
		if ( iDrawDataSize <= 0 )
		{
			continue;
		}

		strYMapper = m_arrYMapper.GetAt(i);
		iEventRectSize = m_arrResourceY.GetAt(i)->m_strResourceYinfo.iEventRectSize;
		if ( iEventRectSize <= 0 )
		{
			iEventRectSize = 1;
		}

		if ( iDrawDataSize == 1 )
		{
			if ( m_arrPlotData.GetAt(i)->GetCustomData(0) >= 0 )
			{
				iXPt = m_XMapper.CalcXDataToPt( m_arrPlotData.GetAt(i)->GetXPoint2D(0) );
				iYPt = strYMapper.CalcYDataToPt( m_arrPlotData.GetAt(i)->GetYPoint2D(0) );
				crEvent.left = iXPt - iEventRectSize;
				crEvent.right = iXPt + iEventRectSize;
				crEvent.top = iYPt - iEventRectSize;
				crEvent.bottom = iYPt + iEventRectSize;
				m_arrPlotData.GetAt(i)->SetDataPointRect(0, crEvent);
			}
			continue;
		}

		if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.eDrawRangeMode == E_GRAPH2D_VISIBLE_RANGE_DRAW )
		{
			iVisualDataStartIndex = m_arrPlotData.GetAt(i)->m_iVisualDataStartIndex;
			iVisualDataEndIndex = m_arrPlotData.GetAt(i)->m_iVisualDataEndIndex + 1;		
		}
		else
		{
			iVisualDataStartIndex = 0;
			iVisualDataEndIndex = iDrawDataSize;
		}

		for ( j = iVisualDataStartIndex; j < iVisualDataEndIndex; j++ )
		{
			if ( m_arrPlotData.GetAt(i)->GetCustomData(j) < 0 )
			{
				continue;
			}

			iXPt = m_XMapper.CalcXDataToPt( m_arrPlotData.GetAt(i)->GetXPoint2D(j) );
			iYPt = strYMapper.CalcYDataToPt( m_arrPlotData.GetAt(i)->GetYPoint2D(j) );

			crEvent.left = iXPt - iEventRectSize;
			crEvent.right = iXPt + iEventRectSize;
			crEvent.top = iYPt - iEventRectSize;
			crEvent.bottom = iYPt + iEventRectSize;
			m_arrPlotData.GetAt(i)->SetDataPointRect(j, crEvent);
		}
	}

	return true;
}

//! Modify by LHW [2008/4/10] : crLastPoint, FillRect, SetPixel 추가, LineTo함수의 문제로 인해 마지막 점이 정확하게 그려지지 않기 때문
//! Modify by LHW [2008/5/23] : 데이터가 1개일 때, 2개 이상일 때로 구분, crLastPoint -> crPoint, 작은 사각형으로 표시하는 모드 추가, 데이터 점에 이벤트용 사각형 표시 추가
//! Modify by LHW [2008/7/24] : m_iTopOverlapIndex, DrawGraph 관련 수정
//! Modify by LHW [2008/8/23] : DrawEquation 추가
bool CGraph2DWnd::DrawData(CDC *pDC)
{
	if ( m_DataRect.Width() <= 0 || m_DataRect.Height() <= 0 )
	{
		return false;
	}
	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize <= 0 )
	{
		return false;
	}
	
	//bool bMoveToFlag = true;
	//int i = 0, j = 0, iXPt = 0, iYPt = 0, iDrawDataSize = 0, iPointRectSize = 0;
	//int iVisualDataStartIndex = 0, iVisualDataEndIndex = 0;
	//strYRangeMapper strYMapper;
	//CRect crPoint;
	
	pDC->SelectClipRgn(&m_DrawRgn);	
	pDC->SetBkMode(TRANSPARENT);

	for ( int i = 0; i < iGraphSize; i++ )
	{
		if ( m_iTopOverlapIndex != i )
		{
			DrawGraph(pDC, i);
			DrawEquation(pDC, i);
		}
	}

	if ( m_iTopOverlapIndex >= 0 && m_iTopOverlapIndex < iGraphSize )
	{
		DrawGraph(pDC, m_iTopOverlapIndex);
		DrawEquation(pDC, m_iTopOverlapIndex);
	}
	
	/*for ( i = 0; i < iGraphSize; i++ )
	{
		if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.bShowGraph == false )
		{
			continue;
		}

		iDrawDataSize = m_arrPlotData.GetAt(i)->GetPointSize();
		if ( iDrawDataSize <= 0 )
		{
			continue;
		}

		m_penOld = pDC->SelectObject( &( m_arrResourceY.GetAt(i)->m_penData ) );

		bMoveToFlag = true;
		strYMapper = m_arrYMapper.GetAt(i);

		if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.eDrawRangeMode == E_GRAPH2D_VISIBLE_RANGE_DRAW )
		{
			iVisualDataStartIndex = m_arrPlotData.GetAt(i)->m_iVisualDataStartIndex;
			iVisualDataEndIndex = m_arrPlotData.GetAt(i)->m_iVisualDataEndIndex + 1;	
		}
		else
		{
			iVisualDataStartIndex = 0;
			iVisualDataEndIndex = iDrawDataSize;
		}

		switch(m_arrResourceY.GetAt(i)->m_strResourceYinfo.eDataDrawType)
		{
		case E_GRAPH2D_DATA_DRAW_LINE:
			{
				for ( j = iVisualDataStartIndex; j < iVisualDataEndIndex; j++ )
				{
					iXPt = m_XMapper.CalcXDataToPt( m_arrPlotData.GetAt(i)->GetXPoint2D(j) );
					iYPt = strYMapper.CalcYDataToPt( m_arrPlotData.GetAt(i)->GetYPoint2D(j) );

					if ( bMoveToFlag == true )
					{
						bMoveToFlag = false;
						pDC->MoveTo(iXPt, iYPt);
					}
					else
					{
						pDC->LineTo(iXPt, iYPt);
					}			
				}

				iPointRectSize = m_arrResourceY.GetAt(i)->m_strResourceYinfo.iLineWidth;

				if ( iPointRectSize == 1 )
				{
					pDC->SetPixel(iXPt, iYPt, m_arrResourceY.GetAt(i)->m_strResourceYinfo.clrData);
				}
				else
				{
					crPoint.left = iXPt - iPointRectSize;
					crPoint.right = iXPt + iPointRectSize;
					crPoint.top = iYPt - iPointRectSize;
					crPoint.bottom = iYPt + iPointRectSize;
					pDC->FillRect(&crPoint, &(m_arrResourceY.GetAt(i)->m_brSymbol));
				}
			}
			break;
		case E_GRAPH2D_DATA_DRAW_RECTANGLE:
			{
				iPointRectSize = m_arrResourceY.GetAt(i)->m_strResourceYinfo.iLineWidth;

				if ( iPointRectSize == 1 )
				{
					for ( j = iVisualDataStartIndex; j < iVisualDataEndIndex; j++ )
					{
						iXPt = m_XMapper.CalcXDataToPt( m_arrPlotData.GetAt(i)->GetXPoint2D(j) );
						iYPt = strYMapper.CalcYDataToPt( m_arrPlotData.GetAt(i)->GetYPoint2D(j) );

						pDC->SetPixel(iXPt, iYPt, m_arrResourceY.GetAt(i)->m_strResourceYinfo.clrData);
					}
				}
				else
				{
					for ( j = iVisualDataStartIndex; j < iVisualDataEndIndex; j++ )
					{
						iXPt = m_XMapper.CalcXDataToPt( m_arrPlotData.GetAt(i)->GetXPoint2D(j) );
						iYPt = strYMapper.CalcYDataToPt( m_arrPlotData.GetAt(i)->GetYPoint2D(j) );

						crPoint.left = iXPt - iPointRectSize;
						crPoint.right = iXPt + iPointRectSize;
						crPoint.top = iYPt - iPointRectSize;
						crPoint.bottom = iYPt + iPointRectSize;
						pDC->FillRect(&crPoint, &(m_arrResourceY.GetAt(i)->m_brSymbol));
					}
				}
			}
			break;
		}
		
		pDC->SelectObject(m_penOld);
	}

	if ( m_bDataPointEventMsg == true )
	{
		m_pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
		CRect crEvent;

		for ( i = 0; i < iGraphSize; i++ )
		{
			if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.bShowGraph == false )
			{
				continue;
			}
			if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.bShowEventRect == false )
			{
				continue;
			}

			iDrawDataSize = m_arrPlotData.GetAt(i)->GetPointSize();
			if ( iDrawDataSize <= 0 )
			{
				continue;
			}

			m_penOld = pDC->SelectObject( &( m_arrResourceY.GetAt(i)->m_penEvent ) );

			strYMapper = m_arrYMapper.GetAt(i);

			if ( iDrawDataSize == 1 )
			{
				if ( m_arrPlotData.GetAt(i)->GetCustomData(j) >= 0 )
				{
					crEvent = m_arrPlotData.GetAt(i)->GetDataPointRect(j);
					pDC->Rectangle(crEvent);
				}
				continue;
			}

			if ( m_arrResourceY.GetAt(i)->m_strResourceYinfo.eDrawRangeMode == E_GRAPH2D_VISIBLE_RANGE_DRAW )
			{
				iVisualDataStartIndex = m_arrPlotData.GetAt(i)->m_iVisualDataStartIndex;
				iVisualDataEndIndex = m_arrPlotData.GetAt(i)->m_iVisualDataEndIndex;			
			}
			else
			{
				iVisualDataStartIndex = 0;
				iVisualDataEndIndex = iDrawDataSize;
			}

			for ( j = iVisualDataStartIndex; j < iVisualDataEndIndex; j++ )
			{
				if ( m_arrPlotData.GetAt(i)->GetCustomData(j) < 0 )
				{
					continue;
				}

				crEvent = m_arrPlotData.GetAt(i)->GetDataPointRect(j);
				pDC->Rectangle(crEvent);
			}

			pDC->SelectObject(m_penOld);
		}

		pDC->SelectObject(m_pOldBrush);
	}*/
	
	pDC->SelectClipRgn(NULL);

	return true;
}

//! Added by LHW [2008/7/24]
//! Modify by LHW [2008/8/9] : Event 사각 영역을 그리는 부분에서 index 처리부분 수정
//! Modify by LHW [2009/2/3] : 심볼을 그리는 부분이 추가되며 관련 부분 수정
//! Modify by LHW [2009/2/4] : 심볼의 크기에 따른 처리 부분 수정
//! Modify by LHW [2009/2/19] : m_bSysmbolOnceDraw 관련 추가
//! Modify by LHW [2013/3/26] : 마지막 점이 그려지는 부분 수정 (색상 설정 오류)
bool CGraph2DWnd::DrawGraph(CDC *pDC, int iOverlapIndex)
{
	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize <= 0 )
	{
		return false;
	}
	if ( iOverlapIndex < 0 || iOverlapIndex >= iGraphSize )
	{
		return false;
	}

	bool bMoveToFlag = true;
	E_GRAPH2D_DRAW_SYMBOL_TYPE eSymbolType = E_GRAPH2D_DRAW_RECTANGLE;
	int i = 0, iXPt = 0, iYPt = 0, iDrawDataSize = 0, iPointRectSize = 0, iSymbolSize = 0;
	int iVisualDataStartIndex = 0, iVisualDataEndIndex = 0;
	strYRangeMapper strYMapper;
	CRect crPoint;

	if ( m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.bShowGraph == false )
	{
		return true;
	}

	iDrawDataSize = m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize();
	if ( iDrawDataSize <= 0 )
	{
		return true;
	}

	bMoveToFlag = true;
	strYMapper = m_arrYMapper.GetAt(iOverlapIndex);

	if ( m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.eDrawRangeMode == E_GRAPH2D_VISIBLE_RANGE_DRAW )
	{
		iVisualDataStartIndex = m_arrPlotData.GetAt(iOverlapIndex)->m_iVisualDataStartIndex;
		iVisualDataEndIndex = m_arrPlotData.GetAt(iOverlapIndex)->m_iVisualDataEndIndex + 1;	
	}
	else
	{
		iVisualDataStartIndex = 0;
		iVisualDataEndIndex = iDrawDataSize;
	}

	/*COleDateTime timeTest;
	CSize sizeTest;
	CString szTest = _T(""), szOldX = _T("");
	int iOldX = 0, iYPos = 0;*/

	if ( m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.eDataDrawType == E_GRAPH2D_DATA_DRAW_LINE || 
		m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.eDataDrawType == E_GRAPH2D_DATA_DRAW_LINE_SYMBOL )
	{
		m_penOld = pDC->SelectObject( &( m_arrResourceY.GetAt(iOverlapIndex)->m_penData ) );

		for ( i = iVisualDataStartIndex; i < iVisualDataEndIndex; i++ )
		{
			//timeTest.m_dt = m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(i);
			//szTest = timeTest.Format(_T("%Y/%m/%d %H:%M:%S"));

			iXPt = m_XMapper.CalcXDataToPt( m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(i) );
			iYPt = strYMapper.CalcYDataToPt( m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(i) );

			/*if ( i != iVisualDataStartIndex )
			{
				if ( abs(iXPt - iOldX) > 300 )
				{
					int ll = 1;
				}
			}

			iOldX = iXPt;
			szOldX = szTest;*/

			if ( bMoveToFlag == true )
			{
				bMoveToFlag = false;
				pDC->MoveTo(iXPt, iYPt);
			}
			else
			{
				pDC->LineTo(iXPt, iYPt);
			}

			/*iYPos = iYPt + 2;
			pDC->TextOut(iXPt, iYPos, szTest);

			sizeTest = pDC->GetTextExtent(szTest);
			iYPos = iYPos + sizeTest.cy + 2;
			szTest.Format(_T("%.08f"), m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(i));
			pDC->TextOut(iXPt, iYPos, szTest);

			sizeTest = pDC->GetTextExtent(szTest);
			iYPos = iYPos + sizeTest.cy + 2;
			szTest.Format(_T("%d"), iXPt);
			pDC->TextOut(iXPt, iYPos, szTest);

			sizeTest = pDC->GetTextExtent(szTest);
			iYPos = iYPos + sizeTest.cy + 2;
			szTest.Format(_T("%.08f ~ %.08f"), m_XMapper.m_dbXDataMin, m_XMapper.m_dbXDataMax);
			pDC->TextOut(iXPt, iYPos, szTest);

			sizeTest = pDC->GetTextExtent(szTest);
			iYPos = iYPos + sizeTest.cy + 2;
			szTest.Format(_T("%d ~ %d"), m_XMapper.m_iXPtMin, m_XMapper.m_iXPtMax);
			pDC->TextOut(iXPt, iYPos, szTest);*/
		}

		//! MoveTo, LineTo 함수의 오류로 인해 마지막 점이 그려지지 않으므로 직접 그림
		iPointRectSize = m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.iLineWidth;

		if ( iPointRectSize == 1 )
		{
			pDC->SetPixel(iXPt, iYPt, m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.clrData);
		}
		else
		{
			crPoint.left   = iXPt - (iPointRectSize / 2);
			crPoint.right  = iXPt + (iPointRectSize / 2);
			crPoint.top    = iYPt - (iPointRectSize / 2);
			crPoint.bottom = iYPt + (iPointRectSize / 2);
			//pDC->FillRect(&crPoint, &(m_arrResourceY.GetAt(iOverlapIndex)->m_brSymbol));
			pDC->FillSolidRect(&crPoint, m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.clrData);
		}

		pDC->SelectObject(m_penOld);
	}

	bool bSymbolDrawFlag = false;

	if ( m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.eDataDrawType == E_GRAPH2D_DATA_DRAW_SYMBOL || 
		 m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.eDataDrawType == E_GRAPH2D_DATA_DRAW_LINE_SYMBOL )
	{
		eSymbolType = m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.eSymbolType;
		iSymbolSize = m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.iSymbolSize;
		
		m_pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
		m_penOld = pDC->SelectObject( &( m_arrResourceY.GetAt(iOverlapIndex)->m_penSymbol ) );

		if ( iSymbolSize <= 0 )
		{
			for ( i = iVisualDataStartIndex; i < iVisualDataEndIndex; i++ )
			{
				iXPt = m_XMapper.CalcXDataToPt( m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(i) );
				iYPt = strYMapper.CalcYDataToPt( m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(i) );

				pDC->SetPixel(iXPt, iYPt, m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.clrData);
			}
		}
		else
		{
			for ( i = iVisualDataStartIndex; i < iVisualDataEndIndex; i++ )
			{
				iXPt = m_XMapper.CalcXDataToPt( m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(i) );
				iYPt = strYMapper.CalcYDataToPt( m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(i) );

				DrawSymbol(pDC, iXPt, iYPt, eSymbolType, iSymbolSize, &(m_arrResourceY.GetAt(iOverlapIndex)->m_brSymbol));
			}
		}

		pDC->SelectObject(m_penOld);
		pDC->SelectObject(m_pOldBrush);

		bSymbolDrawFlag = true;
	}

	if ( m_bDataPointEventMsg == true )
	{
		if ( m_bSysmbolOnceDraw == true && bSymbolDrawFlag == true )
		{
			return true;
		}

		if ( m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.bShowEventRect == false )
		{
			return true;
		}

		//CRect crEvent;

		eSymbolType = m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.eEventSymbolType;
		iSymbolSize = m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.iEventRectSize;
		
		m_pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);		
		m_penOld = pDC->SelectObject( &( m_arrResourceY.GetAt(iOverlapIndex)->m_penEvent ) );

		if ( iDrawDataSize == 1 )
		{
			if ( m_arrPlotData.GetAt(iOverlapIndex)->GetCustomData(0) >= 0 )
			{
				iXPt = m_XMapper.CalcXDataToPt( m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(0) );
				iYPt = strYMapper.CalcYDataToPt( m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(0) );

				DrawSymbol(pDC, iXPt, iYPt, eSymbolType, iSymbolSize, &(m_arrResourceY.GetAt(iOverlapIndex)->m_brEvent));

				//crEvent = m_arrPlotData.GetAt(iOverlapIndex)->GetDataPointRect(0);
				//pDC->Rectangle(crEvent);
			}			
		}
		else
		{
			if ( m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.eDrawRangeMode == E_GRAPH2D_VISIBLE_RANGE_DRAW )
			{
				iVisualDataStartIndex = m_arrPlotData.GetAt(iOverlapIndex)->m_iVisualDataStartIndex;
				iVisualDataEndIndex = m_arrPlotData.GetAt(iOverlapIndex)->m_iVisualDataEndIndex + 1;			
			}
			else
			{
				iVisualDataStartIndex = 0;
				iVisualDataEndIndex = iDrawDataSize;
			}

			for ( i = iVisualDataStartIndex; i < iVisualDataEndIndex; i++ )
			{
				if ( m_arrPlotData.GetAt(iOverlapIndex)->GetCustomData(i) < 0 )
				{
					continue;
				}

				iXPt = m_XMapper.CalcXDataToPt( m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(i) );
				iYPt = strYMapper.CalcYDataToPt( m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(i) );

				DrawSymbol(pDC, iXPt, iYPt, eSymbolType, iSymbolSize, &(m_arrResourceY.GetAt(iOverlapIndex)->m_brEvent));

				//crEvent = m_arrPlotData.GetAt(iOverlapIndex)->GetDataPointRect(i);
				//pDC->Rectangle(crEvent);
			}
		}

		pDC->SelectObject(m_penOld);
		pDC->SelectObject(m_pOldBrush);
	}

	return true;
}

//! Added by LHW [2009/2/3]
//! Modify by LHW [2009/2/26] : 심볼의 크기를 맞추기 위해 삼각형, 원일 경우 Offset값 추가
//! Modify by LHW [2009/3/6] : E_GRAPH2D_DRAW_CROSS, E_GRAPH2D_DRAW_DIAMOND, E_GRAPH2D_DRAW_REVERSE_TRIANGLE 추가
bool CGraph2DWnd::DrawSymbol(CDC *pDC, int iXPt, int iYPt, E_GRAPH2D_DRAW_SYMBOL_TYPE eType, int iSymbolSize, CBrush *pBrush)
{
	if ( iSymbolSize <= 0 )
	{
		return false;
	}

	switch(eType)
	{
	case E_GRAPH2D_DRAW_RECTANGLE:
		{
			CRect crDraw;
			crDraw.left = iXPt - iSymbolSize;
			crDraw.right = iXPt + iSymbolSize;
			crDraw.top = iYPt - iSymbolSize;
			crDraw.bottom = iYPt + iSymbolSize;
			pDC->Rectangle(crDraw);
		}
		break;
	case E_GRAPH2D_DRAW_FILL_RECT:
		{
			if ( pBrush != NULL )
			{
				CRect crDraw;
				crDraw.left = iXPt - iSymbolSize;
				crDraw.right = iXPt + iSymbolSize;
				crDraw.top = iYPt - iSymbolSize;
				crDraw.bottom = iYPt + iSymbolSize;
				pDC->FillRect(&crDraw, pBrush);
			}
		}
		break;
	case E_GRAPH2D_DRAW_TRIANGLE:
		{
			int iNewSymbolSize = iSymbolSize + 2;
			int iXDis = (int)((double)iNewSymbolSize * 0.86);
			int iYDis = (int)((double)iNewSymbolSize * 0.5);
			int aiXPt[3], aiYPt[3];
			aiXPt[0] = iXPt;
			aiXPt[1] = iXPt - iXDis;
			aiXPt[2] = iXPt + iXDis;
			aiYPt[0] = iYPt - iNewSymbolSize;
			aiYPt[1] = iYPt + iYDis;
			aiYPt[2] = iYPt + iYDis;
			pDC->MoveTo(aiXPt[0], aiYPt[0]);
			pDC->LineTo(aiXPt[1], aiYPt[1]);
			pDC->LineTo(aiXPt[2], aiYPt[2]);
			pDC->LineTo(aiXPt[0], aiYPt[0]);
		}
		break;
	case E_GRAPH2D_DRAW_CIRCLE:
		{
			int iNewSymbolSize = iSymbolSize + 1;
			CRect crDraw;
			crDraw.left = iXPt - iNewSymbolSize;
			crDraw.right = iXPt + iNewSymbolSize;
			crDraw.top = iYPt - iNewSymbolSize;
			crDraw.bottom = iYPt + iNewSymbolSize;
			pDC->Ellipse(crDraw);
		}
		break;
	case E_GRAPH2D_DRAW_CROSS:
		{
			CRect crDraw;
			crDraw.left = iXPt - iSymbolSize;
			crDraw.right = iXPt + iSymbolSize;
			crDraw.top = iYPt - iSymbolSize;
			crDraw.bottom = iYPt + iSymbolSize;
			pDC->MoveTo(crDraw.left, crDraw.top);
			pDC->LineTo(crDraw.right, crDraw.bottom);
			pDC->MoveTo(crDraw.right, crDraw.top);
			pDC->LineTo(crDraw.left, crDraw.bottom);
		}
		break;
	case E_GRAPH2D_DRAW_DIAMOND:
		{
			int iNewSymbolSize = iSymbolSize + 2;
			int aiXPt[4], aiYPt[4];
			aiXPt[0] = iXPt;
			aiXPt[1] = iXPt - iNewSymbolSize;
			aiXPt[2] = iXPt;
			aiXPt[3] = iXPt + iNewSymbolSize;
			aiYPt[0] = iYPt - iNewSymbolSize;
			aiYPt[1] = iYPt;
			aiYPt[2] = iYPt + iNewSymbolSize;
			aiYPt[3] = iYPt;		
			pDC->MoveTo(aiXPt[0], aiYPt[0]);
			pDC->LineTo(aiXPt[1], aiYPt[1]);
			pDC->LineTo(aiXPt[2], aiYPt[2]);
			pDC->LineTo(aiXPt[3], aiYPt[3]);
			pDC->LineTo(aiXPt[0], aiYPt[0]);
		}
		break;
	case E_GRAPH2D_DRAW_REVERSE_TRIANGLE:
		{
			int iNewSymbolSize = iSymbolSize + 2;
			int iXDis = (int)((double)iNewSymbolSize * 0.86);
			int iYDis = (int)((double)iNewSymbolSize * 0.5);
			int aiXPt[3], aiYPt[3];
			aiXPt[0] = iXPt;
			aiXPt[1] = iXPt - iXDis;
			aiXPt[2] = iXPt + iXDis;
			aiYPt[0] = iYPt + iNewSymbolSize;
			aiYPt[1] = iYPt - iYDis;
			aiYPt[2] = iYPt - iYDis;
			pDC->MoveTo(aiXPt[0], aiYPt[0]);
			pDC->LineTo(aiXPt[1], aiYPt[1]);
			pDC->LineTo(aiXPt[2], aiYPt[2]);
			pDC->LineTo(aiXPt[0], aiYPt[0]);
		}
		break;
	}

	return true;
}

//! Added by LHW [2008/8/23]
//! Modify by LHW [2008/8/25] : X축 최소, 최대값 적용하도록 수정
//! Modify by LHW [2008/9/1] : dbInputOffsetX, dbOutputOffsetY 추가, bUseExp 관련 부분 추가, iOverlapIndex 관련 오류 수정
bool CGraph2DWnd::DrawEquation(CDC *pDC, int iOverlapIndex)
{
	int iGraphEquationSize = (int)(m_arrGraphEquation.GetSize());
	if ( iGraphEquationSize <= 0 )
	{
		return false;
	}

	bool bGraphShow = true;
	if ( m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.bShowGraph == false )
	{
		bGraphShow = false;
	}
	if ( m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize() <= 0 )
	{
		bGraphShow = false;
	}

	bool bMoveToFlag = true;
	int i = 0, j = 0, iXPt = 0, iYPt = 0;
	int iVisualDataStartIndex = 0, iVisualDataEndIndex = 0;
	double dbXData = 0., dbYData = 0.;
	strYRangeMapper strYMapper;

	for ( i = 0; i < iGraphEquationSize; i++ )
	{
		if ( m_arrGraphEquation.GetAt(i)->m_strEquationInfo.bShow == false )
		{
			continue;
		}
		if ( m_arrGraphEquation.GetAt(i)->m_strEquationInfo.bShowGraphChk == true && bGraphShow == false )
		{
			continue;
		}
		if ( m_arrGraphEquation.GetAt(i)->m_strEquationInfo.iCoeffSize <= 0 || m_arrGraphEquation.GetAt(i)->m_strEquationInfo.pdbCoeff == NULL )
		{
			continue;
		}
		if ( m_arrGraphEquation.GetAt(i)->m_strEquationInfo.bUseExp == true && m_arrGraphEquation.GetAt(i)->m_strEquationInfo.iCoeffSize < 2 )
		{
			continue;
		}
		if ( iOverlapIndex < 0 )
		{
			continue;
		}
		if ( m_arrGraphEquation.GetAt(i)->m_strEquationInfo.iOverlapIndex != iOverlapIndex )
		{
			continue;
		}

		bMoveToFlag = true;
		strYMapper = m_arrYMapper.GetAt(iOverlapIndex);
		iVisualDataStartIndex = m_arrPlotData.GetAt(iOverlapIndex)->m_iVisualDataStartIndex;
		iVisualDataEndIndex = m_arrPlotData.GetAt(iOverlapIndex)->m_iVisualDataEndIndex + 1;
		
		m_penOld = pDC->SelectObject( &( m_arrGraphEquation.GetAt(i)->m_penLine ) );

		for ( j = m_XMapper.m_iXPtMin; j < m_XMapper.m_iXPtMax; j++ )
		{
			iXPt = j;
			dbXData = m_XMapper.CalcPtToXData(iXPt);

			if ( dbXData < m_arrGraphEquation.GetAt(i)->m_strEquationInfo.dbStartRangeX || dbXData > m_arrGraphEquation.GetAt(i)->m_strEquationInfo.dbEndRangeX )
			{
				continue;
			}

			dbXData += m_arrGraphEquation.GetAt(i)->m_strEquationInfo.dbInputOffsetX;
			if ( m_arrGraphEquation.GetAt(i)->m_strEquationInfo.bUseExp == true )
			{
				dbYData = exp(m_arrGraphEquation.GetAt(i)->m_strEquationInfo.pdbCoeff[0]) * exp((dbXData + 1.) * m_arrGraphEquation.GetAt(i)->m_strEquationInfo.pdbCoeff[1]);
			}
			else
			{
				dbYData = CalcPolynomialEquation(m_arrGraphEquation.GetAt(i)->m_strEquationInfo.pdbCoeff, m_arrGraphEquation.GetAt(i)->m_strEquationInfo.iCoeffSize, dbXData);
			}
			dbYData += m_arrGraphEquation.GetAt(i)->m_strEquationInfo.dbOutputOffsetY;
			iYPt = strYMapper.CalcYDataToPt(dbYData);

			if ( bMoveToFlag == true )
			{
				bMoveToFlag = false;
				pDC->MoveTo(iXPt, iYPt);
			}
			else
			{
				pDC->LineTo(iXPt, iYPt);
			}
		}

		pDC->SelectObject(m_penOld);
	}

	return true;
}

//! Added by LHW [2008/8/23]
double CGraph2DWnd::CalcPolynomialEquation(double *pdbCoeff, int iCoeffSize, double dbInput)
{
	double dbReturn = 0., dbNomial = 0.;
	int i = 0, j = 0, iMultiplySize = 0;

	for ( i = 0; i < iCoeffSize; i++ )
	{
		dbNomial = pdbCoeff[i];
		iMultiplySize = iCoeffSize - i - 1;

		if ( iMultiplySize > 0 )
		{
			for ( j = 0; j < iMultiplySize; j++ )
			{
				dbNomial *= dbInput;
			}
		}

		dbReturn += dbNomial;
	}

	return dbReturn;
}

//! Added by LHW [2009/2/4]
double CGraph2DWnd::DecideMinMaxOperation(double dbInput)
{
	double dbAbsInput = fabs(dbInput);
	double dbReturn = 0., dbOldReturn = 0.;
	double dbChkBorder = 0.;
	int iCnt = 0, iType = 0;
	double dbSupply = 0;
	
	dbReturn = 1.;
	dbChkBorder = dbReturn * 0.9;

	if ( dbAbsInput > dbChkBorder )
	{
		iCnt = 0;

		while(1)
		{
			dbChkBorder = dbReturn * 0.9;
			if ( dbAbsInput <= dbChkBorder )
			{
				break;
			}
			
			iCnt++;
			iType = iCnt % 3;
			dbSupply = (double)(iCnt / 3);
			
			switch(iType)
			{
			case 0:
				{
					dbReturn = pow(10., dbSupply);
				}
				break;
			case 1:
				{
					dbReturn = pow(10., dbSupply) * 2.5;
				}
				break;
			case 2:
				{
					dbReturn = pow(10., dbSupply) * 5.;
				}
				break;
			}			
		}
	}
	else if ( dbAbsInput > 0.000001 )
	{
		iCnt = 2;

		while(1)
		{
			dbChkBorder = dbReturn * 0.9;
			if ( dbAbsInput > dbChkBorder )
			{
				dbReturn = dbOldReturn;
				break;
			}
		
			iCnt++;
			iType = iCnt % 3;
			dbSupply = (double)(iCnt / 3);
			dbSupply *= (-1.);
			dbOldReturn = dbReturn;
			
			switch(iType)
			{
			case 0:
				{
					dbReturn = pow(10., dbSupply) * 5.;					
				}
				break;
			case 1:
				{
					dbReturn = pow(10., dbSupply) * 2.5;
				}
				break;
			case 2:
				{
					dbReturn = pow(10., dbSupply);
				}
				break;
			}			
		}
	}

	if ( dbInput < 0. )
	{
		dbReturn *= (-1.);
	}

	return dbReturn;
}

//! Modify by LHW [2008/10/25] : E_GRAPH2D_ZOOM_Y 추가
//! Modify by LHW [2008/11/18] : 사각 영역 체크 추가
//! Modify by LHW [2009/1/6] : NormalizeRect 추가
bool CGraph2DWnd::DrawZoomArea(CDC *pDC)
{
	if ( m_eMouseOperationMode != E_GRAPH2D_ZOOM_XY && m_eMouseOperationMode != E_GRAPH2D_ZOOM_X && m_eMouseOperationMode != E_GRAPH2D_ZOOM_Y )
	{
		return false;
	}
	if ( m_DataRect.Width() <= 0 || m_DataRect.Height() <= 0 )
	{
		return false;
	}
	if ( m_pPlotResource == NULL )
	{
		return false;
	}

	m_crZoomArea.NormalizeRect();

	if ( m_crZoomArea.Width() <= 0 || m_crZoomArea.Height() <= 0 )
	{
		return false;
	}
	
	pDC->FillRect( &m_crZoomArea, &(((CGraph2D_Resource*)m_pPlotResource)->m_brZoomArea) );

	return true;
}

//! Added by LHW [2008/4/19]
//! Modify by LHW [2009/2/2] : 예외 사항 대처 부분 수정
bool CGraph2DWnd::DrawValueLineX(CDC *pDC)
{
	if ( m_DataRect.Width() <= 0 || m_DataRect.Height() <= 0 )
	{
		return false;
	}
	int iValueLineSize = (int)(m_arrValueLineX.GetSize());
	if ( iValueLineSize <= 0 )
	{
		return false;
	}
	
	int i = 0, iXPt = 0, iLen = 0, iMargin = 0;
	CString szValueX = _T("");
	CSize sizeValueX;

	pDC->SetBkMode(TRANSPARENT);

	for ( i = 0; i < iValueLineSize; i++ )
	{
		if ( m_arrValueLineX.GetAt(i)->m_strXLineInfo.bShow == false )
		{
			continue;
		}
		
		iXPt = m_XMapper.CalcXDataToPt( m_arrValueLineX.GetAt(i)->m_strXLineInfo.dbValue );

		if ( iXPt <= m_graphRect.left || iXPt >= m_graphRect.right )
		{
			continue;
		}

		m_pOldFont = pDC->SelectObject( &( m_arrValueLineX.GetAt(i)->m_ftValueLineX ) );
		m_clrBackup = pDC->GetTextColor();
		pDC->SetTextColor( m_arrValueLineX.GetAt(i)->m_strXLineInfo.clrValue );
		m_penOld = pDC->SelectObject( &( m_arrValueLineX.GetAt(i)->m_penXLine ) );

		pDC->MoveTo(iXPt, m_graphRect.top);
		pDC->LineTo(iXPt, m_graphRect.bottom);

		szValueX = m_arrValueLineX.GetAt(i)->m_strXLineInfo.szText;
		iLen = szValueX.GetLength();
		if ( iLen > 0 )
		{
			sizeValueX = pDC->GetTextExtent(szValueX);
			iMargin = (int)(((double)(sizeValueX.cx)) / ((double)iLen));
			if ( (iXPt + iMargin + sizeValueX.cx) >= m_graphRect.right )
			{
				pDC->TextOut(iXPt - iMargin - sizeValueX.cx, m_graphRect.top + 1, szValueX);
			}
			else
			{
				pDC->TextOut(iXPt + iMargin, m_graphRect.top + 1, szValueX);
			}
		}

		pDC->SelectObject(m_penOld);
		pDC->SetTextColor(m_clrBackup);
		pDC->SelectObject(m_pOldFont);
	}

	return true;
}

//! Added by LHW [2008/3/29]
//! Modify by LHW [2009/2/3] : Y축선의 문자열 표시 부분 추가
bool CGraph2DWnd::DrawValueLineY(CDC *pDC)
{
	if ( m_DataRect.Width() <= 0 || m_DataRect.Height() <= 0 )
	{
		return false;
	}
	int iValueLineSize = (int)(m_arrValueLineY.GetSize());
	if ( iValueLineSize <= 0 )
	{
		return false;
	}
	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize <= 0 )
	{
		return false;
	}

	int i = 0, iYPt = 0, iOverlapIndex = 0, iDrawDataSize = 0;
	int iTextXPt = 0, iTextYPt = 0, iLen = 0, iMarginX = 0, iMarginY = 0;
	strYRangeMapper strYMapper;
	CString szValueY = _T("");
	CSize sizeValueY;

	pDC->SetBkMode(TRANSPARENT);

	for ( i = 0; i < iValueLineSize; i++ )
	{
		if ( m_arrValueLineY.GetAt(i)->m_strYLineInfo.bShow == false )
		{
			continue;
		}

		iOverlapIndex = m_arrValueLineY.GetAt(i)->m_strYLineInfo.iOverlapIndex;
		if ( IsValidOverlapIndex(iOverlapIndex) == false )
		{
			continue;
		}
		iDrawDataSize = m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize();
		if ( iDrawDataSize <= 0 )
		{
			continue;
		}

		if ( m_arrValueLineY.GetAt(i)->m_strYLineInfo.bGraphShowChk == true && m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.bShowGraph == false )
		{
			continue;
		}

		strYMapper = m_arrYMapper.GetAt(iOverlapIndex);
		iYPt = strYMapper.CalcYDataToPt( m_arrValueLineY.GetAt(i)->m_strYLineInfo.dbValue );

		if ( iYPt <= m_graphRect.top || iYPt >= m_graphRect.bottom )	//! Modify by LHW [2008/4/15] : 영역을 벗어나면 그리지 않게 함
		{
			continue;
		}

		m_pOldFont = pDC->SelectObject( &( m_arrValueLineY.GetAt(i)->m_ftValueLineY ) );
		m_clrBackup = pDC->GetTextColor();
		pDC->SetTextColor( m_arrValueLineY.GetAt(i)->m_strYLineInfo.clrValue );
		m_penOld = pDC->SelectObject( &( m_arrValueLineY.GetAt(i)->m_penYLine ) );

		pDC->MoveTo(m_graphRect.left, iYPt);
		pDC->LineTo(m_graphRect.right, iYPt);

		szValueY = m_arrValueLineY.GetAt(i)->m_strYLineInfo.szText;
		iLen = szValueY.GetLength();
		if ( iLen > 0 )
		{
			sizeValueY = pDC->GetTextExtent(szValueY);

			iMarginX = (int)(((double)(sizeValueY.cx)) / ((double)iLen));
			if ( iMarginX <= 0 )
			{
				iMarginX = 1;
			}

			if ( m_arrValueLineY.GetAt(i)->m_strYLineInfo.bTextPosExt == false )
			{				
				iMarginY = (int)(((double)(sizeValueY.cy)) / 6.);				
				if ( iMarginY <= 0 )
				{
					iMarginY = 1;
				}
				iTextXPt = m_graphRect.right - sizeValueY.cx - iMarginX;
				iTextYPt = iYPt - sizeValueY.cy - iMarginY;
			}
			else
			{
				iTextXPt = m_DataRect.right + iMarginX;
				iTextYPt = iYPt - (int)(((double)(sizeValueY.cy)) / 2.);				
			}

			pDC->TextOut(iTextXPt, iTextYPt, szValueY);
		}

		pDC->SelectObject(m_penOld);
		pDC->SetTextColor(m_clrBackup);
		pDC->SelectObject(m_pOldFont);
	}

	return true;
}

//! Added by LHW [2008/3/31]
//! Modify by LHW [2008/4/1] : 보조 커서를 보이거나 숨기는 기능 추가, 값이 유효해야 보이게 함
//! Modify by LHW [2008/4/19] : E_GRAPH2D_AUX_CURSOR_DRAW_MODE를 적용하도록 수정
//! Modify by LHW [2008/4/21] : E_GRAPH2D_AUX_CURSOR_DASH_LINE 적용
//! Modify by LHW [2008/8/04] : eDrawMode를 strGraph2D_Aux_CursorGroup에서 strGraph2D_Aux_Cursor로 이동
bool CGraph2DWnd::DrawAuxCursor(CDC *pDC)
{
	if ( m_DataRect.Width() <= 0 || m_DataRect.Height() <= 0 )
	{
		return false;
	}

	int iAuxCursorGroupSize = GetCurrentAuxCursorGroupSize();
	if ( iAuxCursorGroupSize <= 0 )
	{
		return false;
	}

	bool bVertical = false;
	int i = 0, j = 0, iAuxCursorSize = 0, iRadius = 0, iLen = 0, iLenTest = 0, iMargin = 0;
	int iXPt = 0, iYPt = 0;
	CString szTemp = _T(""), szSizeTest = _T("");
	CSize sizeTemp, sizeTest;
	strGraph2D_Aux_Cursor_Extend strAuxCursor;

	for ( i = 0; i < iAuxCursorGroupSize; i++ )
	{
		m_pOldFont = pDC->SelectObject( &( m_arrAuxCursorGroup.GetAt(i)->m_ftAuxCursorText ) );
		m_clrBackup = pDC->GetTextColor();
		pDC->SetTextColor( m_arrAuxCursorGroup.GetAt(i)->m_strGroupInfo.clrAuxCursorText );
		m_pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);

		if ( m_arrAuxCursorGroup.GetAt(i)->m_strGroupInfo.bShow == false )
		{
			continue;
		}

		iAuxCursorSize = GetCurrentAuxCursorSize(i);
		if ( iAuxCursorSize <= 0 )
		{
			continue;
		}

		szSizeTest = _T("ABCDabcd1234");
		iLenTest = szSizeTest.GetLength();
		sizeTest = pDC->GetTextExtent(szSizeTest);
		if ( iLenTest > 0 )
		{
			iMargin = (int)( ((double)(sizeTest.cx)) / (((double)iLenTest) * 2.) );
		}
		else
		{
			iMargin = 5;
		}

		for ( j = 0; j < iAuxCursorSize; j++ )
		{
			strAuxCursor = m_arrAuxCursorGroup.GetAt(i)->m_arrCursorInfo.GetAt(j);
			if ( strAuxCursor.bValid == false )
			{
				continue;
			}

			iXPt = strAuxCursor.iXPos;
			iYPt = strAuxCursor.iYPos;
			
			if ( (iXPt < m_graphRect.left) || (iXPt > m_graphRect.right) )
			{
				continue;
			}
			if ( (iYPt < m_graphRect.top) || (iYPt > m_graphRect.bottom) )
			{
				continue;
			}

			bVertical = m_arrAuxCursorGroup.GetAt(i)->m_strGroupInfo.bFontVertical;
			iRadius = m_arrAuxCursorGroup.GetAt(i)->m_strGroupInfo.iRadius;

			szTemp = strAuxCursor.strAuxCursorUser.szCursorText;

			switch(strAuxCursor.strAuxCursorUser.eDrawMode)
			{
			case E_GRAPH2D_AUX_CURSOR_CIRCLE:
			case E_GRAPH2D_AUX_CURSOR_SOLID_LINE:
				{
					m_penOld = pDC->SelectObject( &( m_arrAuxCursorGroup.GetAt(i)->m_penAuxCursorSolid ) );
				}
				break;
			case E_GRAPH2D_AUX_CURSOR_DOT_LINE:
				{
					m_penOld = pDC->SelectObject( &( m_arrAuxCursorGroup.GetAt(i)->m_penAuxCursorDot ) );
				}
				break;
			case E_GRAPH2D_AUX_CURSOR_DASH_LINE:
				{
					m_penOld = pDC->SelectObject( &( m_arrAuxCursorGroup.GetAt(i)->m_penAuxCursorDash ) );
				}
				break;
			}

			if ( strAuxCursor.strAuxCursorUser.eDrawMode == E_GRAPH2D_AUX_CURSOR_CIRCLE )
			{
				pDC->Ellipse(iXPt - iRadius, iYPt - iRadius, iXPt + iRadius, iYPt + iRadius);

				iLen = szTemp.GetLength();
				if ( iLen > 0 )
				{
					sizeTemp = pDC->GetTextExtent(szTemp);

					if ( bVertical == true )
					{
						if ( (iYPt - (2 * iRadius) - sizeTemp.cx) <= m_graphRect.top )
						{
							if ( (iYPt + (3 * iRadius) + sizeTemp.cx) >= m_graphRect.bottom )
							{
								pDC->TextOut(iXPt - (int)(((double)(sizeTemp.cy)) / 2.), m_graphRect.top + (3 * iRadius) + sizeTemp.cx, szTemp);
							}
							else
							{
								pDC->TextOut(iXPt - (int)(((double)(sizeTemp.cy)) / 2.), iYPt + (3 * iRadius) + sizeTemp.cx, szTemp);
							}
						}
						else
						{
							pDC->TextOut(iXPt - (int)(((double)(sizeTemp.cy)) / 2.), iYPt - (2 * iRadius), szTemp);
						}
					}
					else
					{
						if ( (iYPt - sizeTemp.cy - iRadius) <= m_graphRect.top )
						{
							pDC->TextOut(iXPt - (int)(((double)(sizeTemp.cx)) / 2.), m_graphRect.top + 1, szTemp);
						}
						else
						{
							pDC->TextOut(iXPt - (int)(((double)(sizeTemp.cx)) / 2.), iYPt - sizeTemp.cy - iRadius, szTemp);
						}
					}
				}
			}
			else
			{
				pDC->MoveTo(iXPt, m_graphRect.top);
				pDC->LineTo(iXPt, m_graphRect.bottom);

				iLen = szTemp.GetLength();
				if ( iLen > 0 )
				{
					sizeTemp = pDC->GetTextExtent(szTemp);
					if ( (iXPt + iMargin + sizeTemp.cx) >= m_graphRect.right )
					{
						pDC->TextOut(iXPt - iMargin - sizeTemp.cx, m_graphRect.top + 1, szTemp);
					}
					else
					{
						pDC->TextOut(iXPt + iMargin, m_graphRect.top + 1, szTemp);
					}
				}
			}

			pDC->SelectObject(m_penOld);
		}	

		pDC->SelectObject(m_pOldBrush);
		pDC->SetTextColor(m_clrBackup);
		pDC->SelectObject(m_pOldFont);
	}

	return true;
}

//! Added by LHW [2008/6/13]
//! Modify by LHW [2008/6/15] : iCursorSize 추가
//! Modify by LHW [2008/6/16] : DeltaX, DeltaY 표시 관련 수정, 선택된 자식 커서를 다르게 표시하도록 수정
//! Modify by LHW [2008/8/11] : 커서값 문자열을 설정하는 부분을 수정, GetDeltaTimeText 추가
bool CGraph2DWnd::DrawChildCursor(CDC *pDC)
{
	if ( m_DataRect.Width() <= 0 || m_DataRect.Height() <= 0 )
	{
		return false;
	}
	int iChildCursorSize = (int)(m_arrChildCursor.GetSize());
	if ( iChildCursorSize <= 0 )
	{
		return false;
	}
	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize <= 0 )
	{
		return false;
	}
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize <= 0 )
	{
		return false;
	}

	int i = 0, iCursorPointSize = 0;
	int iOverlapIndex = 0;
	CRect crCursorPoint;
	CString szCursorInfo = _T(""), szCursorDeltaInfo = _T(""), szAddTemp = _T("");
	CSize sizeCursorInfo, sizeCursorDeltaInfo;
	strYRangeMapper strYMapper;
	CPoint ptCheck;
	double dbXData = 0., dbYData = 0., dbDeltaX = 0., dbDeltaY = 0.;
	int iCursorInfoWidth = 0, iCursorInfoHeight = 0, iCursorInfoMargin = 0;
	CRect crInfo;

	pDC->SelectClipRgn(&m_DrawRgn);	//! 확대한 상태에서의 커서 조작때문에 필요
	pDC->SetBkMode(TRANSPARENT);

	//! 커서 선을 그림
	m_pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
	for ( i = 0; i < iChildCursorSize; i++ )
	{
		m_pOldFont = pDC->SelectObject( &(m_arrChildCursor.GetAt(i)->m_ftCursorText) );
		szCursorInfo = _T("abcdABCD");
		sizeCursorInfo = pDC->GetTextExtent(szCursorInfo);
		iCursorPointSize = (int)(((double)(sizeCursorInfo.cx)) / 16.);
		if ( iCursorPointSize < 1 )
		{
			iCursorPointSize = 1;
		}
		pDC->SelectObject(m_pOldFont);

		ptCheck.x = m_arrChildCursor.GetAt(i)->m_iXPos;
		ptCheck.y = m_arrChildCursor.GetAt(i)->m_iYPos;

		iOverlapIndex = m_arrChildCursor.GetAt(i)->m_strCursorInfo.iOverlapIndex;
		if ( iOverlapIndex < 0 )
		{
			iOverlapIndex = 0;
		}
		if ( iOverlapIndex >= iGraphSize )
		{
			iOverlapIndex = iGraphSize - 1;
		}
		m_arrChildCursor.GetAt(i)->m_strCursorInfo.iOverlapIndex = iOverlapIndex;

		if ( m_arrChildCursor.GetAt(i)->m_strCursorInfo.bShowGraphChk == true && m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.bShowGraph == false )
		{
			continue;
		}

		strYMapper = m_arrYMapper.GetAt(iOverlapIndex);

		crCursorPoint.left = ptCheck.x - iCursorPointSize;
		crCursorPoint.top = ptCheck.y - iCursorPointSize;
		crCursorPoint.right = ptCheck.x + iCursorPointSize;
		crCursorPoint.bottom = ptCheck.y + iCursorPointSize;

		if ( m_bSelectedChildCursorLine == true && m_iSelectedChildCursorIndex == i )
		{
			m_penOld = pDC->SelectObject( &(m_arrChildCursor.GetAt(i)->m_penSelectCursorLine) );
		}
		else
		{
			m_penOld = pDC->SelectObject( &(m_arrChildCursor.GetAt(i)->m_penCursorLine) );
		}

		pDC->MoveTo(ptCheck.x, m_graphRect.top);
		pDC->LineTo(ptCheck.x, m_graphRect.bottom);

		if ( m_arrChildCursor.GetAt(i)->m_strCursorInfo.eLineMode == E_GRAPH2D_CURSOR_LINE_XY )
		{
			pDC->MoveTo(m_graphRect.left, ptCheck.y);
			pDC->LineTo(m_graphRect.right, ptCheck.y);
		}

		if ( m_arrChildCursor.GetAt(i)->m_strCursorInfo.bShowPoint == true )
		{
			pDC->Rectangle(crCursorPoint);
		}

		pDC->SelectObject(m_penOld);		
	}
	pDC->SelectObject(m_pOldBrush);

	//! 커서 정보창을 그림
	for ( i = 0; i < iChildCursorSize; i++ )
	{
		if ( m_arrChildCursor.GetAt(i)->m_strCursorInfo.bShowValueX == false && m_arrChildCursor.GetAt(i)->m_strCursorInfo.bShowValueY == false && 
			m_arrChildCursor.GetAt(i)->m_strCursorInfo.bShowValueDeltaX == false && m_arrChildCursor.GetAt(i)->m_strCursorInfo.bShowValueDeltaY == false )
		{
			continue;
		}

		m_penOld = pDC->SelectObject( &(m_arrChildCursor.GetAt(i)->m_penCursorTextBorder) );
		m_clrBackup = pDC->SetTextColor(m_arrChildCursor.GetAt(i)->m_strCursorInfo.clrCursorText);
		m_pOldFont = pDC->SelectObject( &(m_arrChildCursor.GetAt(i)->m_ftCursorText) );

		ptCheck.x = m_arrChildCursor.GetAt(i)->m_iXPos;
		ptCheck.y = m_arrChildCursor.GetAt(i)->m_iYPos;

		if ( ptCheck.x < m_DataRect.left || ptCheck.x > m_DataRect.right )
		{
			continue;
		}

		iOverlapIndex = m_arrChildCursor.GetAt(i)->m_strCursorInfo.iOverlapIndex;

		if ( m_arrChildCursor.GetAt(i)->m_strCursorInfo.bShowGraphChk == true && m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.bShowGraph == false )
		{
			continue;
		}

		dbXData = m_arrChildCursor.GetAt(i)->m_dbXData;
		dbYData = m_arrChildCursor.GetAt(i)->m_dbYData;
		dbDeltaX = m_arrChildCursor.GetAt(i)->m_dbDeltaX;
		dbDeltaY = m_arrChildCursor.GetAt(i)->m_dbDeltaY;

		szCursorInfo = _T("");

		if ( m_arrChildCursor.GetAt(i)->m_strCursorInfo.bShowStringX == true )
		{
			szCursorInfo += _T("X : ");
		}

		if ( m_arrChildCursor.GetAt(i)->m_strCursorInfo.bShowValueX == true )
		{
			szCursorInfo += GetVisualDataText(dbXData, true, false, true, iOverlapIndex);
			szCursorInfo += ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.szCursorUnit;
		}
		else
		{
			szCursorInfo = _T("");
		}

		if ( (m_arrChildCursor.GetAt(i)->m_strCursorInfo.bShowStringX == true || m_arrChildCursor.GetAt(i)->m_strCursorInfo.bShowValueX == true) && 
			(m_arrChildCursor.GetAt(i)->m_strCursorInfo.bShowStringY == true || m_arrChildCursor.GetAt(i)->m_strCursorInfo.bShowValueY == true) )
		{
			szCursorInfo += _T(", ");
		}

		if ( m_arrChildCursor.GetAt(i)->m_strCursorInfo.bShowStringY == true )
		{
			szCursorInfo += _T("Y : ");
		}

		if ( m_arrChildCursor.GetAt(i)->m_strCursorInfo.bShowValueY == true )
		{
			szAddTemp = GetVisualDataText(dbYData, false, false, true, iOverlapIndex);
			szCursorInfo += szAddTemp;
			szCursorInfo += m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.szCursorUnit;
		}

		if ( m_arrChildCursor.GetAt(i)->m_strCursorInfo.bShowValueDeltaX == true )
		{
			if ( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.eGridVisualType == E_GRAPH2D_DATA_VISUAL_TIME )
			{
				szAddTemp = GetDeltaTimeText(dbDeltaX);
			}
			else
			{
				szAddTemp = GetVisualDataText(dbDeltaX, true, false, true, iOverlapIndex);
			}
			
			szCursorDeltaInfo = _T("ΔX : ");
			szCursorDeltaInfo += szAddTemp;
			szCursorDeltaInfo += ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.szCursorUnit;
		}
		else
		{
			szCursorDeltaInfo = _T("");
		}

		if ( m_arrChildCursor.GetAt(i)->m_strCursorInfo.bShowValueDeltaX == true && m_arrChildCursor.GetAt(i)->m_strCursorInfo.bShowValueDeltaY == true )
		{
			szCursorDeltaInfo += _T(", ");
		}

		if ( m_arrChildCursor.GetAt(i)->m_strCursorInfo.bShowValueDeltaY == true )
		{
			szAddTemp = GetVisualDataText(dbDeltaY, false, false, true, iOverlapIndex);
			szCursorDeltaInfo += _T("ΔY : ");
			szCursorDeltaInfo += szAddTemp;
			szCursorDeltaInfo += m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.szCursorUnit;
		}

		iCursorInfoMargin = m_iCursorMargin * 2;

		sizeCursorInfo = pDC->GetTextExtent(szCursorInfo);
		sizeCursorDeltaInfo = pDC->GetTextExtent(szCursorDeltaInfo);

		iCursorInfoWidth = sizeCursorInfo.cx;
		if ( iCursorInfoWidth < sizeCursorDeltaInfo.cx )
		{
			iCursorInfoWidth = sizeCursorDeltaInfo.cx;
		}
		iCursorInfoWidth += iCursorInfoMargin;

		iCursorInfoHeight = sizeCursorInfo.cy + iCursorInfoMargin;
		iCursorInfoHeight += (sizeCursorDeltaInfo.cy + iCursorInfoMargin);

		crInfo = m_arrChildCursor.GetAt(i)->m_crInfo;

		crInfo.right = crInfo.left + iCursorInfoWidth;
		crInfo.bottom = crInfo.top + iCursorInfoHeight;

		//! 자식 커서 정보 위치 확인
		if ( (crInfo.left > m_DataRect.left + (int)(((double)(m_DataRect.Width())) / 2.)) && 
			(crInfo.right > m_DataRect.right) )
		{
			crInfo.right = crInfo.left - iCursorInfoMargin;
			crInfo.left = crInfo.right - iCursorInfoWidth;
		}
		if ( crInfo.top < m_DataRect.top )
		{
			crInfo.top = m_DataRect.top;
			crInfo.bottom = crInfo.top + iCursorInfoHeight;
		}
		if ( crInfo.bottom > m_DataRect.bottom )
		{
			crInfo.bottom = m_DataRect.bottom;
			crInfo.top = crInfo.bottom - iCursorInfoHeight;
		}

		m_arrChildCursor.GetAt(i)->m_crInfo = crInfo;

		if ( m_arrChildCursor.GetAt(i)->m_strCursorInfo.bShowInfo == true )
		{
			pDC->FillRect( &crInfo, &(m_arrChildCursor.GetAt(i)->m_brCursorTextBack) );

			pDC->MoveTo(crInfo.left, crInfo.top);
			pDC->LineTo(crInfo.right, crInfo.top);
			pDC->LineTo(crInfo.right, crInfo.bottom);
			pDC->LineTo(crInfo.left, crInfo.bottom);
			pDC->LineTo(crInfo.left, crInfo.top);

			pDC->TextOut(crInfo.left + m_iCursorMargin, crInfo.top + m_iCursorMargin, szCursorInfo);
			pDC->TextOut(crInfo.left + m_iCursorMargin, crInfo.top + sizeCursorInfo.cy + (m_iCursorMargin * 3), szCursorDeltaInfo);
		}

		pDC->SetTextColor(m_clrBackup);
		pDC->SelectObject(m_penOld);
		pDC->SelectObject(m_pOldFont);
	}

	pDC->SelectClipRgn(NULL);

	return true;
}

//! Added by LHW [2008/11/28]
//! Modify by LHW [2008/11/30] : 실제 기능 구현
//! Modify by LHW [2008/12/1] : 커서 문자열 시작 위치 부분 수정, 커서가 눈에 안 보이면 문자열을 그리지 않도록 수정
//! Modify by LHW [2009/1/6] : 영역 커서와 연결된 그래프의 데이터 개수가 0개이면 커서를 그리지 않게 수정
bool CGraph2DWnd::DrawRegionCursor(CDC *pDC)
{
	if ( m_DataRect.Width() <= 0 || m_DataRect.Height() <= 0 )
	{
		return false;
	}
	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize <= 0 )
	{
		return false;
	}
	int iRegionCursorSize = (int)(m_arrRegionCursor.GetSize());
	if ( iRegionCursorSize <= 0 )
	{
		return false;
	}

	int i = 0, iOverlapIndex = 0, iTextPosX = 0, iTextPosY = 0;
	CString szCursorInfo = _T("");
	CSize sizeCursorInfo;

	pDC->SelectClipRgn(&m_DrawRgn);	//! 확대한 상태에서의 커서 조작때문에 필요
	pDC->SetBkMode(TRANSPARENT);

	for ( i = 0; i < iRegionCursorSize; i++ )
	{
		if ( m_arrRegionCursor.GetAt(i)->m_strCursorInfo.bShow == false )
		{
			continue;
		}

		iOverlapIndex = m_arrRegionCursor.GetAt(i)->m_strCursorInfo.iOverlapIndex;
		if ( iOverlapIndex < 0 )
		{
			iOverlapIndex = 0;
		}
		if ( iOverlapIndex >= iGraphSize )
		{
			iOverlapIndex = iGraphSize - 1;
		}
		m_arrRegionCursor.GetAt(i)->m_strCursorInfo.iOverlapIndex = iOverlapIndex;

		if ( m_arrRegionCursor.GetAt(i)->m_strCursorInfo.bShowGraphChk == true && m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.bShowGraph == false )
		{
			continue;
		}
		if ( m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize() <= 0 )
		{
			continue;
		}

		if ( m_bSelectedRegionCursorLine == true && m_iSelectedRegionCursorIndex == i )
		{
			m_penOld = pDC->SelectObject( &(m_arrRegionCursor.GetAt(i)->m_penSelectCursorLine) );
		}
		else
		{
			m_penOld = pDC->SelectObject( &(m_arrRegionCursor.GetAt(i)->m_penCursorLine) );
		}

		pDC->MoveTo( m_arrRegionCursor.GetAt(i)->m_iMinPosX, m_graphRect.bottom );
		pDC->LineTo( m_arrRegionCursor.GetAt(i)->m_iMinPosX, m_arrRegionCursor.GetAt(i)->m_iMaxPosY );
		pDC->LineTo( m_arrRegionCursor.GetAt(i)->m_iMaxPosX, m_arrRegionCursor.GetAt(i)->m_iMaxPosY );
		pDC->LineTo( m_arrRegionCursor.GetAt(i)->m_iMaxPosX, m_graphRect.bottom );
		pDC->MoveTo( m_arrRegionCursor.GetAt(i)->m_iMinPosX, m_arrRegionCursor.GetAt(i)->m_iMinPosY );
		pDC->LineTo( m_arrRegionCursor.GetAt(i)->m_iMaxPosX, m_arrRegionCursor.GetAt(i)->m_iMinPosY );

		pDC->SelectObject(m_penOld);

		if ( m_arrRegionCursor.GetAt(i)->m_strCursorInfo.bShowText == false )
		{
			continue;
		}

		szCursorInfo = m_arrRegionCursor.GetAt(i)->m_strCursorInfo.szCursorText;
		if ( szCursorInfo.GetLength() <= 0 )
		{
			continue;
		}

		if ( m_arrRegionCursor.GetAt(i)->m_iMaxPosX < m_XMapper.m_iXPtMin || m_arrRegionCursor.GetAt(i)->m_iMinPosX > m_XMapper.m_iXPtMax )
		{
			continue;
		}

		m_clrBackup = pDC->SetTextColor(m_arrRegionCursor.GetAt(i)->m_strCursorInfo.clrCursorText);
		m_pOldFont = pDC->SelectObject( &(m_arrRegionCursor.GetAt(i)->m_ftCursorText) );
		
		sizeCursorInfo = pDC->GetTextExtent(szCursorInfo);
		iTextPosX = m_arrRegionCursor.GetAt(i)->m_iMinPosX + (int)( ((double)(m_arrRegionCursor.GetAt(i)->m_iMaxPosX - m_arrRegionCursor.GetAt(i)->m_iMinPosX)) / 2. ) - (int)( ((double)(sizeCursorInfo.cx)) / 2. );
		if ( iTextPosX < m_graphRect.left )
		{
			iTextPosX = m_graphRect.left;
		}
		if ( (iTextPosX + sizeCursorInfo.cx) > m_graphRect.right )
		{
			iTextPosX = m_graphRect.right - sizeCursorInfo.cx;
		}
		iTextPosY = m_arrRegionCursor.GetAt(i)->m_iMaxPosY - sizeCursorInfo.cy - m_iRegionCursorMargin;
		if ( iTextPosY <= m_graphRect.top )
		{
			iTextPosY = m_graphRect.top + 1;
		}
		if ( (m_arrRegionCursor.GetAt(i)->m_iMaxPosY - m_graphRect.top) <= sizeCursorInfo.cy )
		{
			iTextPosY = m_arrRegionCursor.GetAt(i)->m_iMaxPosY + 1;
		}
		pDC->TextOut(iTextPosX, iTextPosY, szCursorInfo);

		pDC->SetTextColor(m_clrBackup);		
		pDC->SelectObject(m_pOldFont);
	}

	pDC->SelectClipRgn(NULL);

	return true;
}

//! Modify by LHW [2008/4/9] : 커서 점 위치의 정확한 구별을 위해 사각형으로 표시
//! Modify by LHW [2008/4/15] : bShowValueX, bShowValueY 적용
//! Modify by LHW [2008/4/18] : bShowPoint 적용
//! Modify by LHW [2008/4/19] : bShowGraphChk 적용, 커서 정보창을 그릴 때 X방향 영역만 확인
//! Modify by LHW [2008/7/01] : 커서값 문자열을 설정하는 부분을 수정, szAddTemp 삭제
bool CGraph2DWnd::DrawCursor(CDC *pDC)
{
	if ( m_DataRect.Width() <= 0 || m_DataRect.Height() <= 0 )
	{
		return false;
	}
	if ( m_pPlotResource == NULL )
	{
		return false;
	}
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize <= 0 )
	{
		return false;
	}
	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize <= 0 )
	{
		return false;
	}
	
	int i = 0, iCursorPointSize = 0;
	int iOverlapIndex = 0;
	int iCursorInfoMargin = 0;
	strGraph2DCursorInfo strCursorInfo;
	CRect crCursorPoint;
	CString szCursorInfo = _T("");//, szAddTemp = _T("");
	CSize sizeCursorInfo;
	strYRangeMapper strYMapper;
	CPoint ptCheck;

	pDC->SelectClipRgn(&m_DrawRgn);	//! 확대한 상태에서의 커서 조작때문에 필요
	pDC->SetBkMode(TRANSPARENT);

	m_pOldFont = pDC->SelectObject( &( ((CGraph2D_Resource*)m_pPlotResource)->m_ftCursorText ) );
	szCursorInfo = _T("abcdABCD");
	sizeCursorInfo = pDC->GetTextExtent(szCursorInfo);
	iCursorPointSize = (int)(((double)(sizeCursorInfo.cx)) / 16.);
	if ( iCursorPointSize < 1 )
	{
		iCursorPointSize = 1;
	}
	pDC->SelectObject(m_pOldFont);

	//! 커서 선을 그림
	//m_penOld = pDC->SelectObject( &( ((CGraph2D_Resource*)m_pPlotResource)->m_penCursorLine ) );
	m_pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
	for ( i = 0; i < iCursorSize; i++ )
	{
		strCursorInfo = m_arrCursor.GetAt(i);

		ptCheck.x = strCursorInfo.iXPos;
		ptCheck.y = strCursorInfo.iYPos;

		/*if ( !m_DataRect.PtInRect(ptCheck) )
		{
			continue;
		}*/

		iOverlapIndex = strCursorInfo.iSelectOverlapIndex;
		if ( iOverlapIndex < 0 )
		{
			iOverlapIndex = 0;
			strCursorInfo.iSelectOverlapIndex = iOverlapIndex;
			m_arrCursor.SetAt(i, strCursorInfo);
		}
		if ( iOverlapIndex >= iGraphSize )
		{
			iOverlapIndex = iGraphSize - 1;
			strCursorInfo.iSelectOverlapIndex = iOverlapIndex;
			m_arrCursor.SetAt(i, strCursorInfo);
		}

		if ( strCursorInfo.bShowGraphChk == true && m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.bShowGraph == false )
		{
			continue;
		}

		strYMapper = m_arrYMapper.GetAt(iOverlapIndex);

		crCursorPoint.left = strCursorInfo.iXPos - iCursorPointSize;
		crCursorPoint.top = strCursorInfo.iYPos - iCursorPointSize;
		crCursorPoint.right = strCursorInfo.iXPos + iCursorPointSize;
		crCursorPoint.bottom = strCursorInfo.iYPos + iCursorPointSize;

		if ( m_bSelectedCursorLine == true && m_iSelectedCursorIndex == i )
		{
			m_penOld = pDC->SelectObject( &( ((CGraph2D_Resource*)m_pPlotResource)->m_penCursorLineSelected ) );
		}
		else
		{
			m_penOld = pDC->SelectObject( &( ((CGraph2D_Resource*)m_pPlotResource)->m_penCursorLine ) );
		}
        
		pDC->MoveTo(strCursorInfo.iXPos, m_graphRect.top);
		pDC->LineTo(strCursorInfo.iXPos, m_graphRect.bottom);

		if ( strCursorInfo.eLineMode == E_GRAPH2D_CURSOR_LINE_XY )
		{
			pDC->MoveTo(m_graphRect.left, strCursorInfo.iYPos);
			pDC->LineTo(m_graphRect.right, strCursorInfo.iYPos);
		}

		if ( strCursorInfo.bShowPoint == true )
		{
			//pDC->FillRect(crCursorPoint, &( ((CGraph2D_Resource*)m_pPlotResource)->m_brCursorPoint ));
			pDC->Rectangle(crCursorPoint);
		}

		pDC->SelectObject(m_penOld);
	}
	pDC->SelectObject(m_pOldBrush);
	//pDC->SelectObject(m_penOld);

	//! 커서값 문자열을 구성
	for ( i = 0; i < iCursorSize; i++ )
	{
		strCursorInfo = m_arrCursor.GetAt(i);
		iOverlapIndex = strCursorInfo.iSelectOverlapIndex;
		strCursorInfo.szXData = GetVisualDataText(strCursorInfo.dbXData, true, false, true, iOverlapIndex);
		strCursorInfo.szYData = GetVisualDataText(strCursorInfo.dbYData, false, false, true, iOverlapIndex);
		m_arrCursor.SetAt(i, strCursorInfo);
	}

	//! 커서 정보창을 그림
	m_penOld = pDC->SelectObject( &( ((CGraph2D_Resource*)m_pPlotResource)->m_penCursorTextBorder ) );
	m_clrBackup = pDC->SetTextColor( ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.clrCursorText );
	m_pOldFont = pDC->SelectObject( &( ((CGraph2D_Resource*)m_pPlotResource)->m_ftCursorText ) );
	for ( i = 0; i < iCursorSize; i++ )
	{
		strCursorInfo = m_arrCursor.GetAt(i);

		if ( strCursorInfo.bShowValueX == false && strCursorInfo.bShowValueY == false )
		{
			continue;
		}

		ptCheck.x = strCursorInfo.iXPos;
		ptCheck.y = strCursorInfo.iYPos;

		/*if ( !m_DataRect.PtInRect(ptCheck) )
		{
			continue;
		}*/
		if ( ptCheck.x < m_DataRect.left || ptCheck.x > m_DataRect.right )
		{
			continue;
		}

		iOverlapIndex = strCursorInfo.iSelectOverlapIndex;

		if ( strCursorInfo.bShowGraphChk == true && m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.bShowGraph == false )
		{
			continue;
		}

		szCursorInfo = _T("");

		if ( strCursorInfo.bShowStringX == true )
		{
			szCursorInfo += _T("X : ");
		}

		if ( strCursorInfo.bShowValueX == true )
		{
			szCursorInfo += strCursorInfo.szXData;//GetVisualDataText(strCursorInfo.dbXData, true, false, true, iOverlapIndex);
			szCursorInfo += ((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.szCursorUnit;
		}
		else
		{
			szCursorInfo += _T("");
		}

		if ( (strCursorInfo.bShowStringX == true || strCursorInfo.bShowValueX == true) && 
			(strCursorInfo.bShowStringY == true || strCursorInfo.bShowValueY == true) )
		{
			szCursorInfo += _T(", ");
		}

		if ( strCursorInfo.bShowStringY == true )
		{
			szCursorInfo += _T("Y : ");
		}

		if ( strCursorInfo.bShowValueY == true )
		{
			//szAddTemp = GetVisualDataText(strCursorInfo.dbYData, false, false, true, iOverlapIndex);
			szCursorInfo += strCursorInfo.szYData;//szAddTemp;
			szCursorInfo += m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.szCursorUnit;
		}
		
		iCursorInfoMargin = m_iCursorMargin * 2;

		sizeCursorInfo = pDC->GetTextExtent(szCursorInfo);
		strCursorInfo.crInfo.right = strCursorInfo.crInfo.left + sizeCursorInfo.cx + iCursorInfoMargin;
		strCursorInfo.crInfo.bottom = strCursorInfo.crInfo.top + sizeCursorInfo.cy + iCursorInfoMargin;

		//! 커서 정보 위치 확인
		if ( (strCursorInfo.crInfo.left > m_DataRect.left + (int)(((double)(m_DataRect.Width())) / 2.)) && 
			(strCursorInfo.crInfo.right > m_DataRect.right) )
		{
			strCursorInfo.crInfo.right = strCursorInfo.crInfo.left - iCursorInfoMargin;
			strCursorInfo.crInfo.left = strCursorInfo.crInfo.right - sizeCursorInfo.cx - iCursorInfoMargin;
		}
		if ( strCursorInfo.crInfo.top < m_DataRect.top )
		{
			strCursorInfo.crInfo.top = m_DataRect.top;
			strCursorInfo.crInfo.bottom = strCursorInfo.crInfo.top + sizeCursorInfo.cy + iCursorInfoMargin;
		}
		if ( strCursorInfo.crInfo.bottom > m_DataRect.bottom )
		{
			strCursorInfo.crInfo.bottom = m_DataRect.bottom;
			strCursorInfo.crInfo.top = strCursorInfo.crInfo.bottom - sizeCursorInfo.cy - iCursorInfoMargin;
		}

		m_arrCursor.SetAt(i, strCursorInfo);

		if ( strCursorInfo.bShowInfo == true )
		{
			pDC->FillRect(&(strCursorInfo.crInfo), &( ((CGraph2D_Resource*)m_pPlotResource)->m_brCursorTextBack ));

			pDC->MoveTo(strCursorInfo.crInfo.left, strCursorInfo.crInfo.top);
			pDC->LineTo(strCursorInfo.crInfo.right, strCursorInfo.crInfo.top);
			pDC->LineTo(strCursorInfo.crInfo.right, strCursorInfo.crInfo.bottom);
			pDC->LineTo(strCursorInfo.crInfo.left, strCursorInfo.crInfo.bottom);
			pDC->LineTo(strCursorInfo.crInfo.left, strCursorInfo.crInfo.top);

			pDC->TextOut(strCursorInfo.crInfo.left + m_iCursorMargin, strCursorInfo.crInfo.top + m_iCursorMargin, szCursorInfo);
		}
	}
	pDC->SetTextColor(m_clrBackup);
	pDC->SelectObject(m_penOld);
	pDC->SelectObject(m_pOldFont);
	pDC->SelectClipRgn(NULL);

	return true;
}

//! Added by LHW [2009/3/1]
//! Modify by LHW [2009/3/2] : 데이터 검색 구간 오류 수정
bool CGraph2DWnd::SearchEqualValueX(int iOverlapIndex1, int iDataIndex1, int iOverlapIndex2, int &iDataIndex2, int iMargin)
{
	iDataIndex2 = -1;

	if ( iMargin < 0 )
	{
		iMargin = 0;
	}
	if ( IsValidOverlapIndex(iOverlapIndex1) == false )
	{
		return false;
	}
	if ( IsValidOverlapIndex(iOverlapIndex2) == false )
	{
		return false;
	}

	if ( iDataIndex1 < 0 )
	{
		return false;
	}
	int iDrawDataSize1 = m_arrPlotData.GetAt(iOverlapIndex1)->GetPointSize();
	if ( iDataIndex1 >= iDrawDataSize1 )
	{
		return false;
	}
	int iDrawDataSize2 = m_arrPlotData.GetAt(iOverlapIndex2)->GetPointSize();
	if ( iDrawDataSize2 <= 0 )
	{
		return false;
	}

	double dbDataX1 = m_arrPlotData.GetAt(iOverlapIndex1)->GetXPoint2D(iDataIndex1);
	double dbDataX2 = 0.;

	int iSearchMarginStart = 0, iSearchMarginEnd = 0;
	if ( iMargin == 0 )
	{
		iSearchMarginStart = 0;
		iSearchMarginEnd = iDrawDataSize2;
	}
	else
	{
		iSearchMarginStart = iDataIndex1 - iMargin;
		if ( iSearchMarginStart < 0 )
		{
			iSearchMarginStart = 0;
		}
		iSearchMarginEnd = iDataIndex1 + iMargin;
		if ( iSearchMarginEnd >= iDrawDataSize2 )
		{
			iSearchMarginEnd = iDrawDataSize2 - 1;
		}
	}

	double dbDiffTemp = 0., dbMinDiff = DBL_MAX;
	int i = 0;
	for ( i = iSearchMarginStart; i <= iSearchMarginEnd; i++ )
	{
		dbDataX2 = m_arrPlotData.GetAt(iOverlapIndex2)->GetXPoint2D(i);

		dbDiffTemp = fabs(dbDataX2 - dbDataX1);
		if ( dbDiffTemp < dbMinDiff )
		{
			dbMinDiff = dbDiffTemp;
			iDataIndex2 = i;			
		}
	}

	return true;
}

//! Added by LHW [2008/4/15] : 키보드의 키를 눌렀을 경우의 커서 이동 처리
//! Modify by LHW [2008/6/16] : 자식 커서의 키보드 조작 부분 추가
//! Modify by LHW [2009/3/1] : m_bCursorUpDownSearchOperation, m_iCursorUpDownSearchMargin 관련 수정
bool CGraph2DWnd::CursorOperationWithKeyBoard(E_GRAPH2D_KEY_TYPE eKeyType, int iMoveSize)
{
	if ( m_eSelectCursorType == E_GRAPH2D_MOVE_MAIN_CURSOR_TYPE )
	{
		if ( GetCurrentCursorSize() > 0 )
		{
			int iSelectCursorIndex = -1;

			if ( IsCursorSelected(iSelectCursorIndex) == true )
			{
				if ( iSelectCursorIndex >= 0 )
				{
					int iOldOverlapIndex = 0, iCount = 0, iNewCurDataIndex = 0;
					int iGraphSize = 0, iOverlapIndex = -1, iCurDataIndex = 0;
					if ( GetCursorOverlapIndex(iSelectCursorIndex, iOverlapIndex) == true )
					{
						switch(eKeyType)
						{
						case E_GRAPH2D_KEY_UP_ARROW:
							{
								if ( iOverlapIndex >= 0 )
								{
									iCount = 0;
									iOldOverlapIndex = iOverlapIndex;

									if ( GetCursorDataIndex(iSelectCursorIndex, iCurDataIndex) == true )
									{
										iGraphSize = GetPlotBufferSize();

										while( iCount < iGraphSize )
										{
											iOverlapIndex--;
											if ( iOverlapIndex < 0 )
											{
												iOverlapIndex = iGraphSize - 1;
											}

											if ( m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize() > 0 )
											{
												break;
											}

											iCount++;
										}

										if ( iOldOverlapIndex == iOverlapIndex )
										{
											return false;
										}

										if ( m_bCursorUpDownSearchOperation == true )
										{
											if ( SearchEqualValueX(iOldOverlapIndex, iCurDataIndex, iOverlapIndex, iNewCurDataIndex, m_iCursorUpDownSearchMargin) == true )
											{
												iCurDataIndex = iNewCurDataIndex;
											}
										}

										if ( MoveCursor(iSelectCursorIndex, iCurDataIndex, false, iOverlapIndex) == true )
										{
											m_bChanged = true;									
											return true;
										}
									}
								}
							}
							break;
						case E_GRAPH2D_KEY_DOWN_ARROW:
							{
								if ( iOverlapIndex >= 0 )
								{
									iCount = 0;
									iOldOverlapIndex = iOverlapIndex;

									if ( GetCursorDataIndex(iSelectCursorIndex, iCurDataIndex) == true )
									{
										iGraphSize = GetPlotBufferSize();

										while( iCount < iGraphSize )
										{
											iOverlapIndex++;
											if ( iOverlapIndex >= iGraphSize )
											{
												iOverlapIndex = 0;
											}

											if ( m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize() > 0 )
											{
												break;
											}

											iCount++;
										}

										if ( iOldOverlapIndex == iOverlapIndex )
										{
											return false;
										}

										if ( m_bCursorUpDownSearchOperation == true )
										{
											if ( SearchEqualValueX(iOldOverlapIndex, iCurDataIndex, iOverlapIndex, iNewCurDataIndex, m_iCursorUpDownSearchMargin) == true )
											{
												iCurDataIndex = iNewCurDataIndex;
											}
										}

										if ( MoveCursor(iSelectCursorIndex, iCurDataIndex, false, iOverlapIndex) == true )
										{
											m_bChanged = true;									
											return true;
										}
									}
								}
							}
							break;
						case E_GRAPH2D_KEY_LEFT_ARROW:	//! 왼쪽 화살표 키
							{
								//! 커서를 왼쪽 한칸 이동
								if ( MoveCursor(iSelectCursorIndex, false, false, iOverlapIndex) == true )
								{
									m_bChanged = true;								
									return true;
								}
							}
							break;
						case E_GRAPH2D_KEY_RIGHT_ARROW:	//! 오른쪽 화살표 키
							{
								if ( MoveCursor(iSelectCursorIndex, true, false, iOverlapIndex) == true )
								{
									m_bChanged = true;								
									return true;
								}
							}
							break;
						case E_GRAPH2D_KEY_PAGE_UP:		//! Page Up 키
							{
								//! 커서를 왼쪽으로 최대 iMoveSize칸 이동
								if ( GetCursorDataIndex(iSelectCursorIndex, iCurDataIndex) == true )
								{
									if ( MoveCursor(iSelectCursorIndex, iCurDataIndex - iMoveSize, false, iOverlapIndex) == true )
									{
										m_bChanged = true;									
										return true;
									}
								}
							}
							break;
						case E_GRAPH2D_KEY_PAGE_DOWN:	//! Page Down 키
							{
								//! 커서를 오른쪽으로 최대 iMoveSize칸 이동
								if ( GetCursorDataIndex(iSelectCursorIndex, iCurDataIndex) == true )
								{
									if ( MoveCursor(iSelectCursorIndex, iCurDataIndex + iMoveSize, false, iOverlapIndex) == true )
									{
										m_bChanged = true;									
										return true;
									}
								}
							}
							break;
						}
					}
				}
			}
		}
	}
	else if ( m_eSelectCursorType == E_GRAPH2D_MOVE_CHILD_CURSOR_TYPE )
	{
		if ( GetCurrentChildCursorSize() > 0 )
		{
			int iSelectedChildCursorIndex = -1;

			if ( IsChildCursorSelected(iSelectedChildCursorIndex) == true )
			{
				if ( iSelectedChildCursorIndex >= 0 )
				{
					int iGraphSize = 0, iOverlapIndex = -1, iCurDataIndex = 0;
					iOverlapIndex = m_arrChildCursor.GetAt(iSelectedChildCursorIndex)->m_strCursorInfo.iOverlapIndex;
					iCurDataIndex = m_arrChildCursor.GetAt(iSelectedChildCursorIndex)->m_iDataIndex;

					switch(eKeyType)
					{
					case E_GRAPH2D_KEY_UP_ARROW:
						{
							iGraphSize = GetPlotBufferSize();
							iOverlapIndex--;
							if ( iOverlapIndex < 0 )
							{
								iOverlapIndex = iGraphSize - 1;
							}
						}
						break;
					case E_GRAPH2D_KEY_DOWN_ARROW:
						{
							iGraphSize = GetPlotBufferSize();
							iOverlapIndex++;
							if ( iOverlapIndex >= iGraphSize )
							{
								iOverlapIndex = 0;
							}
						}
						break;
					case E_GRAPH2D_KEY_LEFT_ARROW:
						{
							iCurDataIndex--;
						}
						break;
					case E_GRAPH2D_KEY_RIGHT_ARROW:
						{
							iCurDataIndex++;
						}
						break;
					case E_GRAPH2D_KEY_PAGE_UP:
						{
							iCurDataIndex -= iMoveSize;
						}
						break;
					case E_GRAPH2D_KEY_PAGE_DOWN:
						{
							iCurDataIndex += iMoveSize;
						}
						break;
					}

					MoveChildCursor(iSelectedChildCursorIndex, iCurDataIndex, iOverlapIndex);
				}
			}
		}
	}

	return false;
}

//! Modify by LHW [2008/4/4] : 마우스로 커서 움직이는 속도 향상 작업, strGraph2DCursorInfo구조체의 iSearchMargin 추가 작업
//! Modify by LHW [2008/4/16] : 경계 부분에서 마우스로 커서 조작을 원할하게 하기 위해 X Range안에서 dbXData값이 있도록 수정
//! Modify by LHW [2008/4/17] : bAddCursorFlag 추가, 커서 추가작업일 때는 bAddCursorFlag는 true이어야 함
//! Modify by LHW [2008/4/19] : 눈에 보이지 않더라도 처리되도록 수정(부분적으로 iVisualDataSize 사용하지 않음), 영역 확인을 X축 방향으로만 진행
//! Modify by LHW [2008/5/15] : m_bCursorOverlapAllSearch 추가
//! Modify by LHW [2008/5/15] : iXPos, iYPos와의 최소 거리 검색 방법 수정 (X축 기준으로 판정, X축 거리가 동일하면 Y축 거리로 판정)
//! Modify by LHW [2008/6/13] : 'm_bCalcCursor = false' 추가
//! Modify by LHW [2008/7/24] : m_bCursorOverlapAllSearch 삭제하고 대신에 m_eCursorAllSearchMode 추가
//! Modify by LHW [2008/8/9] : 영역 index 관련 오류 수정
//! Modify by LHW [2008/8/19] : 검색 영역 설정 부분 수정
//! Modify by LHW [2008/8/20] : m_eCursorSearchMode가 E_GRAPH2D_CURSOR_SEARCH_X_VISUAL일 경우를 추가
//! Modify by LHW [2009/6/4] : 마우스를 움직일 때의 커서 동작의 오차를 줄이는 작업을 진행
bool CGraph2DWnd::CalcCursorPos(int iXPos, int iYPos, bool bAddCursorFlag, strGraph2DCursorInfo* pstrCursorInfo)
{
	if ( m_DataRect.Width() <= 0 || m_DataRect.Height() <= 0 )
	{
		return false;
	}
	if ( m_RealGraphRect.Width() <= 0 || m_RealGraphRect.Height() <= 0 )
	{
		return false;
	}

	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize <= 0 || pstrCursorInfo == NULL )
	{
		return false;
	}
	
	m_bCalcCursor = true;

	if ( pstrCursorInfo->iSelectOverlapIndex >= iGraphSize )
	{
		pstrCursorInfo->iSelectOverlapIndex = iGraphSize - 1;
	}

	int i = 0, j = 0;
	int iCursorDataIndex = -1, iCursorDataIndexTemp = -1;
	int iCompress = 0, iDrawDataSize = 0, iVisualDataSize = 0;
	int iOverlapIndex = 0, iOverlapTempIndex = 0;
	double dbXData = 0., dbYData = 0., dbIncrement = 0.;
	int iTempXPos = 0, iTempYPos = 0, iCursorIndexTemp = 0;
	double dbTempXDataMax = 0., dbTempXDataMin = 0.;
	int iDistanceTempX = 0, iDistanceMinX = INT_MAX, iDistanceTempMinX = INT_MAX;
	int iDistanceTempY = 0, iDistanceMinY = INT_MAX, iDistanceTempMinY = INT_MAX;	
	bool bShowDataExist = false;
	int iSearchStart = 0, iSearchEnd = 0;
	strYRangeMapper strYMapper;
	int iSearchRangeForAddCursor = 0;

	if ( m_eCursorAllSearchMode == E_GRAPH2D_CURSOR_ALL_SEARCH_NONE )
	{
		m_bCursorOverlap = false;
	}
	
	//! 데이터를 검색할 구간 index를 설정하고 가장 가까운 데이터 index를 찾음	
	if ( ( (m_eCursorAllSearchMode == E_GRAPH2D_CURSOR_ALL_SEARCH_SELECT || m_eCursorAllSearchMode == E_GRAPH2D_CURSOR_ALL_SEARCH_NONE) && 
		m_bCursorOverlap == false ) && ( pstrCursorInfo->iSelectOverlapIndex >= 0 && pstrCursorInfo->iSelectOverlapIndex < iGraphSize ) )
	{
		//! 특정 그래프의 데이터 만 검색

		iOverlapIndex = pstrCursorInfo->iSelectOverlapIndex;
		iDrawDataSize = m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize();
		iVisualDataSize = m_arrPlotData.GetAt(iOverlapIndex)->m_iVisualDataSize;		
		if ( iDrawDataSize <= 0 /*|| iVisualDataSize <= 0*/ )
		{
			m_bCalcCursor = false;
			return false;
		}

		if ( bAddCursorFlag == true )
		{
			if ( iVisualDataSize <= 0 )
			{
				m_bCalcCursor = false;
				return false;
			}

			iSearchRangeForAddCursor = iVisualDataSize / 10;
			if ( iSearchRangeForAddCursor < 100 )
			{
				iSearchRangeForAddCursor = 100;
			}
			if ( iSearchRangeForAddCursor > (iVisualDataSize / 2) )
			{
				iSearchRangeForAddCursor = iVisualDataSize / 2;
			}			
		}

		switch(m_eCursorSearchMode)
		{
		case E_GRAPH2D_CURSOR_SEARCH_X_RANGE:
			{
				if ( iVisualDataSize == 1 )
				{
					iSearchStart = m_arrPlotData.GetAt(iOverlapIndex)->m_iVisualDataStartIndex;
					iSearchEnd = m_arrPlotData.GetAt(iOverlapIndex)->m_iVisualDataEndIndex + 1;
				}
				else
				{
					dbTempXDataMax = m_arrPlotData.GetAt(iOverlapIndex)->m_dbMaxX;
					dbTempXDataMin = m_arrPlotData.GetAt(iOverlapIndex)->m_dbMinX;

					//iCompress = (int)( (dbTempXDataMax - dbTempXDataMin) / (double)(m_RealGraphRect.Width()) );
					iCompress = (int)( ((double)iVisualDataSize) / ((double)(m_RealGraphRect.Width())) );
					iCompress += pstrCursorInfo->iSearchMargin;
					iCompress += iSearchRangeForAddCursor;
					//! X축 방향의 최대값과 실제 데이터 사이의 간격을 계산
					dbIncrement = (dbTempXDataMax - dbTempXDataMin) / (double)(iDrawDataSize - 1);
					
					//! 함수의 인자로 주어진 X 좌표에 해당하는 X 방향값을 구한 뒤,
					//! 이를 간격으로 나누어 실제 데이터에서의 예상 index값을 구함
					dbXData = m_XMapper.CalcPtToXData(iXPos);
					if ( dbXData < m_XMapper.m_dbXDataMin )
					{
						dbXData = m_XMapper.m_dbXDataMin;
					}
					if ( dbXData > m_XMapper.m_dbXDataMax )
					{
						dbXData = m_XMapper.m_dbXDataMax;
					}
					iCursorIndexTemp = (int)((dbXData - dbTempXDataMin) / dbIncrement);//! 예상 index값
					//! 예상 index값 주위의 index 구간을 정함
					iSearchStart = iCursorIndexTemp - iCompress;					
					iSearchEnd = iCursorIndexTemp + iCompress;					
				}
			}
			break;
		case E_GRAPH2D_CURSOR_SEARCH_X_VISUAL:
			{
				iSearchStart = m_arrPlotData.GetAt(iOverlapIndex)->m_iVisualDataStartIndex;
				iSearchEnd = m_arrPlotData.GetAt(iOverlapIndex)->m_iVisualDataEndIndex + 1;
			}
			break;
		case E_GRAPH2D_CURSOR_SEARCH_ALL:
			{
				iSearchStart = 0;
				iSearchEnd = iDrawDataSize - 1;
			}
			break;
		}

		if ( iSearchStart < 0 )
		{
			iSearchStart = 0;
		}
		if ( iSearchStart >= iDrawDataSize )
		{
			iSearchStart = iDrawDataSize - 1;
		}
		if ( iSearchEnd < 0 )
		{
			iSearchEnd = 0;
		}
		if ( iSearchEnd >= iDrawDataSize )
		{
			iSearchEnd = iDrawDataSize - 1;
		}
        
		strYMapper = m_arrYMapper.GetAt(iOverlapIndex);

		for ( i = iSearchStart; i <= iSearchEnd; i++ )
		{
			dbXData = m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(i);
			dbYData = m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(i);

			if ( (dbXData >= m_XMapper.m_dbXDataMin && dbXData <= m_XMapper.m_dbXDataMax) /*&& 
				(dbYData >= strYMapper.m_dbYDataMin && dbYData <= strYMapper.m_dbYDataMax)*/ )
			{
				bShowDataExist = true;

				iTempXPos = m_XMapper.CalcXDataToPt(dbXData);
				iTempYPos = strYMapper.CalcYDataToPt(dbYData);

				//! 가장 가까운 지점의 데이터를 선택
				/*iDistanceTemp = ((iTempXPos - iXPos) * (iTempXPos - iXPos)) + ((iTempYPos - iYPos) * (iTempYPos - iYPos));
				if ( iDistanceTemp < iDistanceMin )
				{
					iDistanceMin = iDistanceTemp;
					iCursorDataIndex = i;
				}*/
				iDistanceTempX = (iTempXPos - iXPos) * (iTempXPos - iXPos);
				iDistanceTempY = (iTempYPos - iYPos) * (iTempYPos - iYPos);
				if ( iDistanceTempX < iDistanceMinX )
				{
					iDistanceMinX = iDistanceTempX;
					iDistanceMinY = iDistanceTempY;
					iCursorDataIndex = i;					
				}
				else if ( iDistanceTempX == iDistanceMinX )
				{					
					if ( iDistanceTempY < iDistanceMinY )
					{
						iDistanceMinX = iDistanceTempX;
						iDistanceMinY = iDistanceTempY;
						iCursorDataIndex = i;
					}
				}
			}
		}
	}
	else
	{
		for ( i = 0; i < iGraphSize; i++ )
		{
			iDrawDataSize = m_arrPlotData.GetAt(i)->GetPointSize();
			iVisualDataSize = m_arrPlotData.GetAt(i)->m_iVisualDataSize;		
			if ( iDrawDataSize <= 0 /*|| iVisualDataSize <= 0*/ )
			{
				continue;
			}

			if ( bAddCursorFlag == true && iVisualDataSize <= 0 )
			{
				continue;
			}

			if ( bAddCursorFlag == true )
			{
				iSearchRangeForAddCursor = iVisualDataSize / 10;
				if ( iSearchRangeForAddCursor < 100 )
				{
					iSearchRangeForAddCursor = 100;
				}
				if ( iSearchRangeForAddCursor > (iVisualDataSize / 2) )
				{
					iSearchRangeForAddCursor = iVisualDataSize / 2;
				}
			}

			switch(m_eCursorSearchMode)
			{
			case E_GRAPH2D_CURSOR_SEARCH_X_RANGE:
				{
					if ( iVisualDataSize == 1 )
					{
						iSearchStart = m_arrPlotData.GetAt(i)->m_iVisualDataStartIndex;
						iSearchEnd = m_arrPlotData.GetAt(i)->m_iVisualDataEndIndex + 1;
					}
					else
					{
						dbTempXDataMax = m_arrPlotData.GetAt(i)->m_dbMaxX;
						dbTempXDataMin = m_arrPlotData.GetAt(i)->m_dbMinX;

						//iCompress = (int)( (dbTempXDataMax - dbTempXDataMin) / (double)(m_RealGraphRect.Width()) );
						iCompress = (int)( ((double)iVisualDataSize) / ((double)(m_RealGraphRect.Width())) );
						iCompress += pstrCursorInfo->iSearchMargin;
						iCompress += iSearchRangeForAddCursor;
						//! X축 방향의 최대값과 실제 데이터 사이의 간격을 계산
						dbIncrement = (dbTempXDataMax - dbTempXDataMin) / (double)(iDrawDataSize - 1);

						//! 함수의 인자로 주어진 X 좌표에 해당하는 X 방향값을 구한 뒤,
						//! 이를 간격으로 나누어 실제 데이터에서의 예상 index값을 구함
						dbXData = m_XMapper.CalcPtToXData(iXPos);
						if ( dbXData < m_XMapper.m_dbXDataMin )
						{
							dbXData = m_XMapper.m_dbXDataMin;
						}
						if ( dbXData > m_XMapper.m_dbXDataMax )
						{
							dbXData = m_XMapper.m_dbXDataMax;
						}
						iCursorIndexTemp = (int)((dbXData - dbTempXDataMin) / dbIncrement);//! 예상 index값
						//! 예상 index값 주위의 index 구간을 정함
						iSearchStart = iCursorIndexTemp - iCompress;						
						iSearchEnd = iCursorIndexTemp + iCompress;						
					}
				}
				break;
			case E_GRAPH2D_CURSOR_SEARCH_X_VISUAL:
				{
					iSearchStart = m_arrPlotData.GetAt(i)->m_iVisualDataStartIndex;
					iSearchEnd = m_arrPlotData.GetAt(i)->m_iVisualDataEndIndex + 1;
				}
				break;
			case E_GRAPH2D_CURSOR_SEARCH_ALL:
				{
					iSearchStart = 0;
					iSearchEnd = iDrawDataSize - 1;
				}
				break;
			}

			if ( iSearchStart < 0 )
			{
				iSearchStart = 0;
			}
			if ( iSearchStart >= iDrawDataSize )
			{
				iSearchStart = iDrawDataSize - 1;
			}
			if ( iSearchEnd < 0 )
			{
				iSearchEnd = 0;
			}
			if ( iSearchEnd >= iDrawDataSize )
			{
				iSearchEnd = iDrawDataSize - 1;
			}

			strYMapper = m_arrYMapper.GetAt(i);
			iCursorDataIndexTemp = -1;
			
			iDistanceTempMinX = INT_MAX;
			iDistanceTempMinY = INT_MAX;

			for ( j = iSearchStart; j <= iSearchEnd; j++ )
			{
				dbXData = m_arrPlotData.GetAt(i)->GetXPoint2D(j);
				dbYData = m_arrPlotData.GetAt(i)->GetYPoint2D(j);

				if ( (dbXData >= m_XMapper.m_dbXDataMin && dbXData <= m_XMapper.m_dbXDataMax) /*&& 
					(dbYData >= strYMapper.m_dbYDataMin && dbYData <= strYMapper.m_dbYDataMax)*/ )
				{
					bShowDataExist = true;

					iTempXPos = m_XMapper.CalcXDataToPt(dbXData);
					iTempYPos = strYMapper.CalcYDataToPt(dbYData);

					//! 가장 가까운 지점의 데이터를 선택
					/*iDistanceTemp = ((iTempXPos - iXPos) * (iTempXPos - iXPos)) + ((iTempYPos - iYPos) * (iTempYPos - iYPos));
					if ( iDistanceTemp < iDistanceTempMin )
					{
						iDistanceTempMin = iDistanceTemp;
						iCursorDataIndexTemp = j;
						iOverlapTempIndex = i;
					}*/
					iDistanceTempX = (iTempXPos - iXPos) * (iTempXPos - iXPos);
					iDistanceTempY = (iTempYPos - iYPos) * (iTempYPos - iYPos);

					if ( iDistanceTempX < iDistanceTempMinX )
					{
						iDistanceTempMinX = iDistanceTempX;
						iDistanceTempMinY = iDistanceTempY;
						iCursorDataIndexTemp = j;
						iOverlapTempIndex = i;					
					}
					else if ( iDistanceTempX == iDistanceTempMinX )
					{						
						if ( iDistanceTempY < iDistanceTempMinY )
						{						
							iDistanceTempMinY = iDistanceTempY;
							iDistanceTempMinY = iDistanceTempY;
							iCursorDataIndexTemp = j;
							iOverlapTempIndex = i;	
						}
					}
				}
			}

			/*if ( iDistanceTempMin < iDistanceMin && iCursorDataIndexTemp != -1 )
			{
				iDistanceMin = iDistanceTempMin;
				iOverlapIndex = iOverlapTempIndex;
				iCursorDataIndex = iCursorDataIndexTemp;
			}*/
			if ( iCursorDataIndexTemp != -1 )
			{
				if ( iDistanceTempMinX < iDistanceMinX )
				{
					iDistanceMinX = iDistanceTempMinX;
					iDistanceMinY = iDistanceTempMinY;
					iOverlapIndex = iOverlapTempIndex;
					iCursorDataIndex = iCursorDataIndexTemp;
				}
				else if ( iDistanceTempMinX == iDistanceMinX )
				{
					if ( iDistanceTempMinY < iDistanceMinY )
					{
						iDistanceMinX = iDistanceTempMinX;
						iDistanceMinY = iDistanceTempMinY;
						iOverlapIndex = iOverlapTempIndex;
						iCursorDataIndex = iCursorDataIndexTemp;
					}
				}
			}
		}
	}

	if ( bShowDataExist == false )
	{
		m_bCalcCursor = false;
		return false;
	}

	bool bReturn = SetCursorInfo(iCursorDataIndex, pstrCursorInfo, iOverlapIndex);

	m_bCalcCursor = false;

	return bReturn;
}

//! Modify by LHW [2008/7/01] : szXData, szYData 처리 부분 추가
bool CGraph2DWnd::SetCursorInfo(int iCursorDataIndex, strGraph2DCursorInfo* pstrCursorInfo, int iOverlapIndex)
{
	if ( pstrCursorInfo == NULL )
	{
		return false;
	}

	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize <= 0 || pstrCursorInfo == NULL )
	{
		return false;
	}
	if ( pstrCursorInfo->bMaxHold == true && (iOverlapIndex < 0 || iOverlapIndex >= iGraphSize) )
	{
		return true;
	}
	if ( iOverlapIndex < 0 )
	{
		iOverlapIndex = 0;
	}
	if ( iOverlapIndex >= iGraphSize )
	{
		iOverlapIndex = iGraphSize - 1;
	}

	int iDrawDataSize = m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize();
	if ( iDrawDataSize <= 0 )
	{
		return false;
	}
	if ( pstrCursorInfo->bMaxHold == true && (iCursorDataIndex < 0 || iCursorDataIndex >= iDrawDataSize) )
	{
		return true;
	}
	if ( iCursorDataIndex < 0 )
	{
		iCursorDataIndex = 0;
	}
	if ( iCursorDataIndex >= iDrawDataSize )
	{
		iCursorDataIndex = iDrawDataSize - 1;
	}

	double dbXData = 0., dbYData = 0.;
	int iTempXPos = 0, iTempYPos = 0;

	dbXData = m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(iCursorDataIndex);
	dbYData = m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(iCursorDataIndex);

	strYRangeMapper strYMapper = m_arrYMapper.GetAt(iOverlapIndex);
	iTempXPos = m_XMapper.CalcXDataToPt(dbXData);
	iTempYPos = strYMapper.CalcYDataToPt(dbYData);

	pstrCursorInfo->iDataIndex = iCursorDataIndex;
	pstrCursorInfo->iSelectOverlapIndex = iOverlapIndex;
	pstrCursorInfo->dbXData = dbXData;
	pstrCursorInfo->dbYData = dbYData;
	pstrCursorInfo->szXData = GetVisualDataText(dbXData, true, false, true, iOverlapIndex);
	pstrCursorInfo->szYData = GetVisualDataText(dbYData, false, false, true, iOverlapIndex);
	pstrCursorInfo->iXPos = iTempXPos;
	pstrCursorInfo->iYPos = iTempYPos;

	pstrCursorInfo->crInfo.left = iTempXPos + m_iCursorMargin;
	pstrCursorInfo->crSelectX.left = iTempXPos - m_iCursorMargin;
	pstrCursorInfo->crSelectX.right = iTempXPos + m_iCursorMargin;
	pstrCursorInfo->crSelectX.top = m_DataRect.top;
	pstrCursorInfo->crSelectX.bottom = m_DataRect.bottom;
	pstrCursorInfo->crSelectY.left = m_DataRect.left;
	pstrCursorInfo->crSelectY.right = m_DataRect.right;
	pstrCursorInfo->crSelectY.top = iTempYPos - m_iCursorMargin;
	pstrCursorInfo->crSelectY.bottom = iTempYPos + m_iCursorMargin;

	return true;
}

//! Modify by LHW [2008/6/15] : RemoveOneChildCursor 추가
//! Modify by LHW [2008/7/01] : szXData, szYData 처리 부분 추가
void CGraph2DWnd::ReCalcCursorPos()
{
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize <= 0 )
	{
		return;
	}
	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize <= 0 )
	{
		return;
	}
	
	int i = 0, iDataIndex = 0, iOverlapIndex = 0, iDrawDataSize = 0;
	double dbXData = 0., dbYData = 0.;
	int iXPos = 0, iYPos = 0;
	strGraph2DCursorInfo strCursorInfo;
	strYRangeMapper strYMapper;
	
	for ( i = 0; i < iCursorSize; i++ )
	{
		strCursorInfo = m_arrCursor.GetAt(i);

		iOverlapIndex = strCursorInfo.iSelectOverlapIndex;		
		if ( iOverlapIndex >= iGraphSize )
		{
			iOverlapIndex = iGraphSize - 1;
		}
		if ( iOverlapIndex < 0 )
		{
			iOverlapIndex = 0;
		}

		iDrawDataSize = m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize();
		if ( iDrawDataSize <= 0 )
		{
			//! 자식 커서 삭제
			RemoveChildCursor(strCursorInfo.iElementIndex);
			m_arrCursor.RemoveAt(i);
			m_arrCursor.FreeExtra();
			iCursorSize = (int)(m_arrCursor.GetSize());			
			i--;			
			continue;
		}
		//! Modify by LHW [2008/4/18] 주석 처리
		/*if ( m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.bShowGraph == false )	//! 커서와 연결된 그래프가 안 보이면 커서 삭제
		{
			m_arrCursor.RemoveAt(i);
			m_arrCursor.FreeExtra();
			iCursorSize = (int)(m_arrCursor.GetSize());
			i--;
			continue;
		}*/

		strYMapper = m_arrYMapper.GetAt(iOverlapIndex);

		iDataIndex = strCursorInfo.iDataIndex;
		if ( iDataIndex < 0 || iDataIndex >= iDrawDataSize )
		{
			iDataIndex = 0;
			strCursorInfo.iDataIndex = 0;
		}
		dbXData = m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(iDataIndex);
		dbYData = m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(iDataIndex);		
		iXPos = m_XMapper.CalcXDataToPt(dbXData);
		iYPos = strYMapper.CalcYDataToPt(dbYData);

		strCursorInfo.dbXData = dbXData;
		strCursorInfo.dbYData = dbYData;
		strCursorInfo.szXData = GetVisualDataText(dbXData, true, false, true, iOverlapIndex);
		strCursorInfo.szYData = GetVisualDataText(dbYData, false, false, true, iOverlapIndex);
		strCursorInfo.iXPos = iXPos;
		strCursorInfo.iYPos = iYPos;

		strCursorInfo.crInfo.left = iXPos + m_iCursorMargin;
		//! 화면 크기가 변하더라더 지난 번의 화면 크기를 바탕으로 새로운 Y방향 위치 계산
		strCursorInfo.crInfo.top = m_DataRect.top + 
			(int)( (double)(strCursorInfo.crInfo.top - strCursorInfo.crData.top) * (double)(m_DataRect.Height()) / (double)(strCursorInfo.crData.Height()) );
		strCursorInfo.crData = m_DataRect;

		strCursorInfo.crSelectX.left = iXPos - m_iCursorMargin;
		strCursorInfo.crSelectX.right = iXPos + m_iCursorMargin;
		strCursorInfo.crSelectX.top = m_DataRect.top;
		strCursorInfo.crSelectX.bottom = m_DataRect.bottom;
		strCursorInfo.crSelectY.left = m_DataRect.left;
		strCursorInfo.crSelectY.right = m_DataRect.right;
		strCursorInfo.crSelectY.top = iYPos - m_iCursorMargin;
		strCursorInfo.crSelectY.bottom = iYPos + m_iCursorMargin;

		m_arrCursor.SetAt(i, strCursorInfo);
	}	
}

//! Added by LHW [2008/6/14]
//! Modify by LHW [2008/6/15] : 부모 커서와의 연동 처리 부분 추가
//! Modify by LHW [2008/6/16] : 부모 커서와의 연동 처리 관련 오류 수정
//! Modify by LHW [2008/6/17] : 부모 커서의 Element index를 가져오는 부분의 오류 수정
//! Modify by LHW [2008/7/29] : RemoveOneChildCursor 호출 부분 수정
void CGraph2DWnd::ReCalcChildCursorPos()
{
	int iChildCursorSize = (int)(m_arrChildCursor.GetSize());
	if ( iChildCursorSize <= 0 )
	{
		return;
	}
	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize <= 0 )
	{
		return;
	}
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize <= 0 )
	{
		return;
	}

	int i = 0, iDataIndex = 0, iOverlapIndex = 0, iDrawDataSize = 0;	
	double dbXData = 0., dbYData = 0.;
	int iXPos = 0, iYPos = 0;
	strYRangeMapper strYMapper;
	strGraph2DCursorInfo strCursorInfo;
	CRect crInfo, crData;

	int iCursorElementIndex = 0, iCursorIndex = 0, iCursorDataIndex = 0, iDataInterval = 0, iCursorOldDataIndex = 0;
	double dbCursorXData = 0., dbCursorYData = 0., dbDeltaX = 0., dbDeltaY = 0.;

	for ( i = 0; i < iChildCursorSize; i++ )
	{
		m_arrChildCursor.GetAt(i)->m_bDataValid = false;

		iOverlapIndex = m_arrChildCursor.GetAt(i)->m_strCursorInfo.iOverlapIndex;
		if ( iOverlapIndex >= iGraphSize )
		{
			iOverlapIndex = iGraphSize - 1;
		}
		if ( iOverlapIndex < 0 )
		{
			iOverlapIndex = 0;
		}

		iDrawDataSize = m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize();
		if ( iDrawDataSize <= 0 )
		{
			RemoveOneChildCursor(i);
			iChildCursorSize = (int)(m_arrChildCursor.GetSize());
			i--;
			continue;
		}

		iCursorElementIndex = m_arrChildCursor.GetAt(i)->m_strCursorInfo.iCursorElementIndex;
		if ( GetCursorIndexFromElementIndex(iCursorElementIndex, iCursorIndex) == false )
		{
			continue;
		}

		strCursorInfo = m_arrCursor.GetAt(iCursorIndex);
		iCursorDataIndex = strCursorInfo.iDataIndex;
		
		if ( m_arrChildCursor.GetAt(i)->m_strCursorInfo.bFollowCursor == true && m_arrChildCursor.GetAt(i)->m_bCursorMoved == true )
		{
			iDataIndex = m_arrChildCursor.GetAt(i)->m_iDataIndex;
			iCursorOldDataIndex = m_arrChildCursor.GetAt(i)->m_iCursorDataIndex;
			if ( iCursorDataIndex != iCursorOldDataIndex )
			{
				iDataInterval = iDataIndex - iCursorOldDataIndex;				
				iDataIndex = iDataInterval + iCursorDataIndex;
				m_arrChildCursor.GetAt(i)->m_iDataIndex = iDataIndex;
			}
		}

		m_arrChildCursor.GetAt(i)->m_iCursorDataIndex = iCursorDataIndex;

		iDataIndex = m_arrChildCursor.GetAt(i)->m_iDataIndex;
		if ( iDataIndex < 0 )
		{
			iDataIndex = 0;
			m_arrChildCursor.GetAt(i)->m_iDataIndex = iDataIndex;
		}
		if ( iDataIndex >= iDrawDataSize )
		{
			iDataIndex = iDrawDataSize - 1;
			m_arrChildCursor.GetAt(i)->m_iDataIndex = iDataIndex;
		}

		dbCursorXData = m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(iCursorDataIndex);
		dbCursorYData = m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(iCursorDataIndex);

		dbXData = m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(iDataIndex);
		dbYData = m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(iDataIndex);

		strYMapper = m_arrYMapper.GetAt(iOverlapIndex);
		iXPos = m_XMapper.CalcXDataToPt(dbXData);
		iYPos = strYMapper.CalcYDataToPt(dbYData);

		crInfo = m_arrChildCursor.GetAt(i)->m_crInfo;
		crData = m_arrChildCursor.GetAt(i)->m_crData;

		m_arrChildCursor.GetAt(i)->m_crInfo.left = iXPos + m_iChildCursorMargin;
		//! 화면 크기가 변하더라도 지난 번의 화면 크기를 바탕으로 새로운 Y방향 위치 계산
		if ( crData.Height() > 0 )
		{
			m_arrChildCursor.GetAt(i)->m_crInfo.top = m_DataRect.top + 
				(int)( (double)(crInfo.top - crData.top) * (double)(m_DataRect.Height()) / (double)(crData.Height()) );
		}
		m_arrChildCursor.GetAt(i)->m_crData = m_DataRect;

		m_arrChildCursor.GetAt(i)->m_dbXData = dbXData;
		m_arrChildCursor.GetAt(i)->m_dbYData = dbYData;
		m_arrChildCursor.GetAt(i)->m_iXPos = iXPos;
		m_arrChildCursor.GetAt(i)->m_iYPos = iYPos;
		m_arrChildCursor.GetAt(i)->m_dbDeltaX = dbCursorXData - dbXData;
		m_arrChildCursor.GetAt(i)->m_dbDeltaY = dbCursorYData - dbYData;
		m_arrChildCursor.GetAt(i)->m_crSelectX.left = iXPos - m_iChildCursorMargin;
		m_arrChildCursor.GetAt(i)->m_crSelectX.right = iXPos + m_iChildCursorMargin;
		m_arrChildCursor.GetAt(i)->m_crSelectX.top = m_DataRect.top;
		m_arrChildCursor.GetAt(i)->m_crSelectX.bottom = m_DataRect.bottom;
		m_arrChildCursor.GetAt(i)->m_crSelectY.left = m_DataRect.left;
		m_arrChildCursor.GetAt(i)->m_crSelectY.right = m_DataRect.right;
		m_arrChildCursor.GetAt(i)->m_crSelectY.top = iYPos - m_iChildCursorMargin;
		m_arrChildCursor.GetAt(i)->m_crSelectY.bottom = iYPos + m_iChildCursorMargin;

		m_arrChildCursor.GetAt(i)->m_bDataValid = true;
		m_arrChildCursor.GetAt(i)->m_bCursorMoved = false;
	}
}

//! Added by LHW [2008/6/13]
//! Modify by LHW [2008/6/15] : iCursorSize 추가
//! Modify by LHW [2008/6/16] : SetChildCursorInfo, 정보 창 수직 방향 위치 관련 수정
//! Modify by LHW [2008/8/9] : 영역 index 관련 오류 수정
//! Modify by LHW [2008/8/19] : 검색 영역 설정 부분 수정
//! Modify by LHW [2008/8/20] : 검색 구간 설정 방법 수정, m_bChildCursorOverlap 추가
//! Modify by LHW [2009/6/4] : 마우스를 움직일 때의 커서 동작의 오차를 줄이는 작업을 진행
bool CGraph2DWnd::CalcChildCursorPos(int iXPos, int iYPos, bool bAddCursorFlag, int iChildCursorIndex)
{
	if ( m_DataRect.Width() <= 0 || m_DataRect.Height() <= 0 )
	{
		return false;
	}
	if ( m_RealGraphRect.Width() <= 0 || m_RealGraphRect.Height() <= 0 )
	{
		return false;
	}

	int iChildCursorSize = (int)(m_arrChildCursor.GetSize());
	if ( iChildCursorSize <= 0 )
	{
		return false;
	}
	if ( iChildCursorIndex < 0 || iChildCursorIndex >= iChildCursorSize )
	{
		return false;
	}

	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize <= 0 )
	{
		return false;
	}
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize <= 0 )
	{
		return false;
	}

	m_bCalcChildCursor = true;

	int i = 0, j = 0;
	int iCursorDataIndex = -1, iCursorDataIndexTemp = -1;
	int iCompress = 0, iDrawDataSize = 0, iVisualDataSize = 0;
	int iOverlapIndex = 0, iOverlapTempIndex = 0;
	double dbXData = 0., dbYData = 0., dbIncrement = 0.;
	double dbTempXDataMax = 0., dbTempXDataMin = 0.;
	int iTempXPos = 0, iTempYPos = 0, iCursorIndexTemp = 0;
	int iDistanceTempX = 0, iDistanceMinX = INT_MAX, iDistanceTempMinX = INT_MAX;
	int iDistanceTempY = 0, iDistanceMinY = INT_MAX, iDistanceTempMinY = INT_MAX;	
	bool bShowDataExist = false;
	int iSearchStart = 0, iSearchEnd = 0, iSearchMargin = 0;
	strYRangeMapper strYMapper;
	int iSearchRangeForAddCursor = 0;

	E_GRAPH2D_CHILD_CURSOR_SEARCH_MODE eChildCursorSearchMode = m_arrChildCursor.GetAt(iChildCursorIndex)->m_strCursorInfo.eSearchMode;
	iSearchMargin = m_arrChildCursor.GetAt(iChildCursorIndex)->m_strCursorInfo.iSearchMargin;

	iOverlapIndex = m_arrChildCursor.GetAt(iChildCursorIndex)->m_strCursorInfo.iOverlapIndex;
	if ( iOverlapIndex < 0 )
	{
		iOverlapIndex = 0;
	}
	if ( iOverlapIndex >= iGraphSize )
	{
		iOverlapIndex = iGraphSize - 1;
	}
	m_arrChildCursor.GetAt(iChildCursorIndex)->m_strCursorInfo.iOverlapIndex = iOverlapIndex;

	m_arrChildCursor.GetAt(iChildCursorIndex)->m_crInfo.top = iYPos;

	//! 데이터를 검색할 구간 index를 설정하고 가장 가까운 데이터 index를 찾음
	if ( m_arrChildCursor.GetAt(iChildCursorIndex)->m_strCursorInfo.bCursorOverlapAllSearch == false && m_bChildCursorOverlap == false )
	{
		//! 특정 그래프의 데이터 만 검색

		iDrawDataSize = m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize();
		iVisualDataSize = m_arrPlotData.GetAt(iOverlapIndex)->m_iVisualDataSize;
		if ( iDrawDataSize <= 0 /*|| iVisualDataSize <= 0*/ )
		{
			m_bCalcChildCursor = false;
			return false;
		}

		if ( bAddCursorFlag == true )
		{
			if ( iVisualDataSize <= 0 )
			{
				m_bCalcChildCursor = false;
				return false;
			}

			iSearchRangeForAddCursor = iVisualDataSize / 10;
			if ( iSearchRangeForAddCursor < 100 )
			{
				iSearchRangeForAddCursor = 100;
			}
			if ( iSearchRangeForAddCursor > (iVisualDataSize / 2) )
			{
				iSearchRangeForAddCursor = iVisualDataSize / 2;
			}
		}

		switch(eChildCursorSearchMode)
		{
		case E_GRAPH2D_CHILD_CURSOR_SEARCH_X_RANGE:
			{
				if ( iVisualDataSize == 1 )
				{
					iSearchStart = m_arrPlotData.GetAt(iOverlapIndex)->m_iVisualDataStartIndex;
					iSearchEnd = m_arrPlotData.GetAt(iOverlapIndex)->m_iVisualDataEndIndex + 1;
				}
				else
				{
					dbTempXDataMax = m_arrPlotData.GetAt(iOverlapIndex)->m_dbMaxX;
					dbTempXDataMin = m_arrPlotData.GetAt(iOverlapIndex)->m_dbMinX;

					//iCompress = (int)((dbTempXDataMax - dbTempXDataMin) / (double)(m_RealGraphRect.Width()));
					iCompress = (int)( ((double)iVisualDataSize) / ((double)(m_RealGraphRect.Width())) );
					iCompress += iSearchMargin;
					iCompress += iSearchRangeForAddCursor;

					//! X축 방향의 최대값과 실제 데이터 사이의 간격을 계산
					dbIncrement = (dbTempXDataMax - dbTempXDataMin) / (double)(iDrawDataSize - 1);

					//! 함수의 인자로 주어진 X 좌표에 해당하는 X 방향값을 구한 뒤,
					//! 이를 간격으로 나누어 실제 데이터에서의 예상 index값을 구함
					dbXData = m_XMapper.CalcPtToXData(iXPos);
					if ( dbXData < m_XMapper.m_dbXDataMin )
					{
						dbXData = m_XMapper.m_dbXDataMin;
					}
					if ( dbXData > m_XMapper.m_dbXDataMax )
					{
						dbXData = m_XMapper.m_dbXDataMax;
					}
					iCursorIndexTemp = (int)((dbXData - dbTempXDataMin) / dbIncrement);//! 예상 index값
					//! 예상 index값 주위의 index 구간을 정함
					iSearchStart = iCursorIndexTemp - iCompress;					
					iSearchEnd = iCursorIndexTemp + iCompress;					
				}
			}
			break;
		case E_GRAPH2D_CHILD_CURSOR_SEARCH_X_VISUAL:
			{
				iSearchStart = m_arrPlotData.GetAt(iOverlapIndex)->m_iVisualDataStartIndex;
				iSearchEnd = m_arrPlotData.GetAt(iOverlapIndex)->m_iVisualDataEndIndex + 1;
			}
			break;
		case E_GRAPH2D_CHILD_CURSOR_SEARCH_ALL:
			{
				iSearchStart = 0;
				iSearchEnd = iDrawDataSize - 1;
			}
			break;
		}

		if ( iSearchStart < 0 )
		{
			iSearchStart = 0;
		}
		if ( iSearchStart >= iDrawDataSize )
		{
			iSearchStart = iDrawDataSize - 1;
		}
		if ( iSearchEnd < 0 )
		{
			iSearchEnd = 0;
		}
		if ( iSearchEnd >= iDrawDataSize )
		{
			iSearchEnd = iDrawDataSize - 1;
		}

		strYMapper = m_arrYMapper.GetAt(iOverlapIndex);

		for ( i = iSearchStart; i <= iSearchEnd; i++ )
		{
			dbXData = m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(i);
			dbYData = m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(i);

			if ( dbXData >= m_XMapper.m_dbXDataMin && dbXData <= m_XMapper.m_dbXDataMax )
			{
				bShowDataExist = true;

				iTempXPos = m_XMapper.CalcXDataToPt(dbXData);
				iTempYPos = strYMapper.CalcYDataToPt(dbYData);

				//! 가장 가까운 지점의 데이터를 선택				
				iDistanceTempX = (iTempXPos - iXPos) * (iTempXPos - iXPos);
				iDistanceTempY = (iTempYPos - iYPos) * (iTempYPos - iYPos);
				if ( iDistanceTempX < iDistanceMinX )
				{
					iDistanceMinX = iDistanceTempX;
					iDistanceMinY = iDistanceTempY;
					iCursorDataIndex = i;					
				}
				else if ( iDistanceTempX == iDistanceMinX )
				{					
					if ( iDistanceTempY < iDistanceMinY )
					{
						iDistanceMinX = iDistanceTempX;
						iDistanceMinY = iDistanceTempY;
						iCursorDataIndex = i;
					}
				}
			}
		}
	}
	else
	{
		for ( i = 0; i < iGraphSize; i++ )
		{
			iDrawDataSize = m_arrPlotData.GetAt(i)->GetPointSize();
			iVisualDataSize = m_arrPlotData.GetAt(i)->m_iVisualDataSize;		
			if ( iDrawDataSize <= 0 /*|| iVisualDataSize <= 0*/ )
			{
				continue;
			}

			if ( bAddCursorFlag == true && iVisualDataSize <= 0 )
			{
				continue;
			}

			if ( bAddCursorFlag == true )
			{
				iSearchRangeForAddCursor = iVisualDataSize / 10;
				if ( iSearchRangeForAddCursor < 100 )
				{
					iSearchRangeForAddCursor = 100;
				}
				if ( iSearchRangeForAddCursor > (iVisualDataSize / 2) )
				{
					iSearchRangeForAddCursor = iVisualDataSize / 2;
				}
			}

			switch(eChildCursorSearchMode)
			{
			case E_GRAPH2D_CURSOR_SEARCH_X_RANGE:
				{
					if ( iVisualDataSize == 1 )
					{
						iSearchStart = m_arrPlotData.GetAt(i)->m_iVisualDataStartIndex;
						iSearchEnd = m_arrPlotData.GetAt(i)->m_iVisualDataEndIndex + 1;
					}
					else
					{
						dbTempXDataMax = m_arrPlotData.GetAt(i)->m_dbMaxX;
						dbTempXDataMin = m_arrPlotData.GetAt(i)->m_dbMinX;

						//iCompress = (int)((dbTempXDataMax - dbTempXDataMin) / (double)(m_RealGraphRect.Width()));
						iCompress = (int)( ((double)iVisualDataSize) / ((double)(m_RealGraphRect.Width())) );
						iCompress += iSearchMargin;
						iCompress += iSearchRangeForAddCursor;
						//! X축 방향의 최대값과 실제 데이터 사이의 간격을 계산
						dbIncrement = (dbTempXDataMax - dbTempXDataMin) / (double)(iDrawDataSize - 1);

						//! 함수의 인자로 주어진 X 좌표에 해당하는 X 방향값을 구한 뒤,
						//! 이를 간격으로 나누어 실제 데이터에서의 예상 index값을 구함
						dbXData = m_XMapper.CalcPtToXData(iXPos);
						if ( dbXData < m_XMapper.m_dbXDataMin )
						{
							dbXData = m_XMapper.m_dbXDataMin;
						}
						if ( dbXData > m_XMapper.m_dbXDataMax )
						{
							dbXData = m_XMapper.m_dbXDataMax;
						}
						iCursorIndexTemp = (int)((dbXData - dbTempXDataMin) / dbIncrement);//! 예상 index값
						//! 예상 index값 주위의 index 구간을 정함
						iSearchStart = iCursorIndexTemp - iCompress;						
						iSearchEnd = iCursorIndexTemp + iCompress;						
					}
				}
				break;
			case E_GRAPH2D_CURSOR_SEARCH_ALL:
				{
					iSearchStart = 0;
					iSearchEnd = iDrawDataSize - 1;
				}
				break;
			}

			if ( iSearchStart < 0 )
			{
				iSearchStart = 0;
			}
			if ( iSearchStart >= iDrawDataSize )
			{
				iSearchStart = iDrawDataSize - 1;
			}
			if ( iSearchEnd < 0 )
			{
				iSearchEnd = 0;
			}
			if ( iSearchEnd >= iDrawDataSize )
			{
				iSearchEnd = iDrawDataSize - 1;
			}

			strYMapper = m_arrYMapper.GetAt(i);
			iCursorDataIndexTemp = -1;
			iDistanceTempMinX = INT_MAX;
			iDistanceTempMinY = INT_MAX;

			for ( j = iSearchStart; j <= iSearchEnd; j++ )
			{
				dbXData = m_arrPlotData.GetAt(i)->GetXPoint2D(j);
				dbYData = m_arrPlotData.GetAt(i)->GetYPoint2D(j);

				if ( dbXData >= m_XMapper.m_dbXDataMin && dbXData <= m_XMapper.m_dbXDataMax )
				{
					bShowDataExist = true;

					iTempXPos = m_XMapper.CalcXDataToPt(dbXData);
					iTempYPos = strYMapper.CalcYDataToPt(dbYData);

					//! 가장 가까운 지점의 데이터를 선택					
					iDistanceTempX = (iTempXPos - iXPos) * (iTempXPos - iXPos);
					iDistanceTempY = (iTempYPos - iYPos) * (iTempYPos - iYPos);

					if ( iDistanceTempX < iDistanceTempMinX )
					{
						iDistanceTempMinX = iDistanceTempX;
						iDistanceTempMinY = iDistanceTempY;
						iCursorDataIndexTemp = j;
						iOverlapTempIndex = i;					
					}
					else if ( iDistanceTempX == iDistanceTempMinX )
					{						
						if ( iDistanceTempY < iDistanceTempMinY )
						{						
							iDistanceTempMinY = iDistanceTempY;
							iDistanceTempMinY = iDistanceTempY;
							iCursorDataIndexTemp = j;
							iOverlapTempIndex = i;	
						}
					}
				}
			}

			if ( iCursorDataIndexTemp != -1 )
			{
				if ( iDistanceTempMinX < iDistanceMinX )
				{
					iDistanceMinX = iDistanceTempMinX;
					iDistanceMinY = iDistanceTempMinY;
					iOverlapIndex = iOverlapTempIndex;
					iCursorDataIndex = iCursorDataIndexTemp;
				}
				else if ( iDistanceTempMinX == iDistanceMinX )
				{
					if ( iDistanceTempMinY < iDistanceMinY )
					{
						iDistanceMinX = iDistanceTempMinX;
						iDistanceMinY = iDistanceTempMinY;
						iOverlapIndex = iOverlapTempIndex;
						iCursorDataIndex = iCursorDataIndexTemp;
					}
				}
			}
		}
	}

	if ( bShowDataExist == false )
	{
		m_bCalcChildCursor = false;
		return false;
	}

	bool bReturn = SetChildCursorInfo(iCursorDataIndex, iChildCursorIndex, bAddCursorFlag, iOverlapIndex);

	m_bCalcChildCursor = false;

	return bReturn;
}

//! Modify by LHW [2008/6/16]
bool CGraph2DWnd::SetChildCursorInfo(int iCursorDataIndex, int iChildCursorIndex, bool bAddFlag, int iOverlapIndex)
{
	int iChildCursorSize = (int)(m_arrChildCursor.GetSize());
	if ( iChildCursorSize <= 0 )
	{
		return false;
	}
	if ( iChildCursorIndex < 0 || iChildCursorIndex >= iChildCursorSize )
	{
		return false;
	}
	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize <= 0 )
	{
		return false;
	}
	if ( iOverlapIndex < 0 )
	{
		iOverlapIndex = 0;
	}
	if ( iOverlapIndex >= iGraphSize )
	{
		iOverlapIndex = iGraphSize - 1;
	}

	int iDrawDataSize = m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize();
	if ( iDrawDataSize <= 0 )
	{
		return false;
	}
	if ( iCursorDataIndex < 0 )
	{
		iCursorDataIndex = 0;
	}
	if ( iCursorDataIndex >= iDrawDataSize )
	{
		iCursorDataIndex = iDrawDataSize - 1;
	}

	double dbXData = 0., dbYData = 0.;
	int iTempXPos = 0, iTempYPos = 0;

	dbXData = m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(iCursorDataIndex);
	dbYData = m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(iCursorDataIndex);

	strYRangeMapper strYMapper = m_arrYMapper.GetAt(iOverlapIndex);
	iTempXPos = m_XMapper.CalcXDataToPt(dbXData);
	iTempYPos = strYMapper.CalcYDataToPt(dbYData);

	m_arrChildCursor.GetAt(iChildCursorIndex)->m_iDataIndex = iCursorDataIndex;
	m_arrChildCursor.GetAt(iChildCursorIndex)->m_strCursorInfo.iOverlapIndex = iOverlapIndex;
	m_arrChildCursor.GetAt(iChildCursorIndex)->m_dbXData = dbXData;
	m_arrChildCursor.GetAt(iChildCursorIndex)->m_dbYData = dbYData;
	m_arrChildCursor.GetAt(iChildCursorIndex)->m_iXPos = iTempXPos;
	m_arrChildCursor.GetAt(iChildCursorIndex)->m_iYPos = iTempYPos;

	m_arrChildCursor.GetAt(iChildCursorIndex)->m_crInfo.left = iTempXPos + m_iChildCursorMargin;
	m_arrChildCursor.GetAt(iChildCursorIndex)->m_crSelectX.left = iTempXPos - m_iChildCursorMargin;
	m_arrChildCursor.GetAt(iChildCursorIndex)->m_crSelectX.right = iTempXPos + m_iChildCursorMargin;
	m_arrChildCursor.GetAt(iChildCursorIndex)->m_crSelectX.top = m_DataRect.top;
	m_arrChildCursor.GetAt(iChildCursorIndex)->m_crSelectX.bottom = m_DataRect.bottom;
	m_arrChildCursor.GetAt(iChildCursorIndex)->m_crSelectY.left = m_DataRect.left;
	m_arrChildCursor.GetAt(iChildCursorIndex)->m_crSelectY.right = m_DataRect.right;
	m_arrChildCursor.GetAt(iChildCursorIndex)->m_crSelectY.top = iTempYPos - m_iChildCursorMargin;
	m_arrChildCursor.GetAt(iChildCursorIndex)->m_crSelectY.bottom = iTempYPos + m_iChildCursorMargin;

	if ( bAddFlag == true )
	{
		m_arrChildCursor.GetAt(iChildCursorIndex)->m_crInfo.top = iTempYPos;
	}

	return true;
}

//! Added by LHW [2008/11/28]
//! Modify by LHW [2008/11/30] : 실제 기능 구현
//! Modify by LHW [2008/12/1] : 입력값의 Range 오류에 대처하는 부분 추가
//! Modify by LHW [2008/12/1] : 영역 표시 커서 선에 둘러싸인 사각 영역 관련 추가
bool CGraph2DWnd::CalcRegionCursorPos(int iXPos, int iYPos, int iRegionCursorIndex, int iRegionCursorLineIndex)
{
	if ( m_DataRect.Width() <= 0 || m_DataRect.Height() <= 0 )
	{
		return false;
	}
	if ( m_RealGraphRect.Width() <= 0 || m_RealGraphRect.Height() <= 0 )
	{
		return false;
	}

	if ( iRegionCursorLineIndex < 0 || iRegionCursorLineIndex > REGION_CURSOR_SELECT_SIZE )
	{
		return false;
	}

	int iRegionCursorSize = (int)(m_arrRegionCursor.GetSize());
	if ( iRegionCursorSize <= 0 )
	{
		return false;
	}
	if ( iRegionCursorIndex < 0 || iRegionCursorIndex >= iRegionCursorSize )
	{
		return false;
	}

	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize <= 0 )
	{
		return false;
	}

	int iOverlapIndex = 0;
	strYRangeMapper strYMapper;

	iOverlapIndex = m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_strCursorInfo.iOverlapIndex;
	if ( iOverlapIndex < 0 )
	{
		iOverlapIndex = 0;
	}
	if ( iOverlapIndex >= iGraphSize )
	{
		iOverlapIndex = iGraphSize - 1;
	}
	m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_strCursorInfo.iOverlapIndex = iOverlapIndex;

	strYMapper = m_arrYMapper.GetAt(iOverlapIndex);

	//! REGION_CURSOR_SELECT_SIZE 개의 커서 선 중 선택된 커서 선의 위치를 변경
	switch(iRegionCursorLineIndex)
	{
	case REGION_CURSOR_LEFT_VERT:
		{
			if ( iXPos >= m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_iMaxPosX )
			{
				iXPos = m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_iMaxPosX - 1;
			}
			if ( iXPos < m_XMapper.m_iXPtMin )
			{
				iXPos = m_XMapper.m_iXPtMin;
			}

			m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_iMinPosX = iXPos;
			m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_dbMinDataX = m_XMapper.CalcPtToXData(iXPos);
			if ( m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_dbMinDataX < m_XMapper.m_dbXDataMin )
			{
				m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_dbMinDataX = m_XMapper.m_dbXDataMin;
			}
		}
		break;
	case REGION_CURSOR_RIGHT_VERT:
		{
			if ( iXPos <= m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_iMinPosX )
			{
				iXPos = m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_iMinPosX + 1;
			}
			if ( iXPos > m_XMapper.m_iXPtMax )
			{
				iXPos = m_XMapper.m_iXPtMax;
			}

			m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_iMaxPosX = iXPos;
			m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_dbMaxDataX = m_XMapper.CalcPtToXData(iXPos);
			if ( m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_dbMaxDataX > m_XMapper.m_dbXDataMax )
			{
				m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_dbMaxDataX = m_XMapper.m_dbXDataMax;
			}
		}
		break;
	case REGION_CURSOR_UP_HORZ:
		{
			if ( iYPos >= m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_iMinPosY )
			{
				iYPos = m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_iMinPosY - 1;
			}
			if ( iYPos < strYMapper.m_iYPtMin )
			{
				iYPos = strYMapper.m_iYPtMin;
			}

			m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_iMaxPosY = iYPos;
			m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_dbMaxDataY = strYMapper.CalcPtToYData(iYPos);
			if ( m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_dbMaxDataY > strYMapper.m_dbYDataMax )
			{
				m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_dbMaxDataY = strYMapper.m_dbYDataMax;
			}
		}
		break;
	case REGION_CURSOR_DOWN_HORZ:
		{
			if ( iYPos <= m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_iMaxPosY )
			{
				iYPos = m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_iMaxPosY + 1;
			}
			if ( iYPos > strYMapper.m_iYPtMax )
			{
				iYPos = strYMapper.m_iYPtMax;
			}

			m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_iMinPosY = iYPos;
			m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_dbMinDataY = strYMapper.CalcPtToYData(iYPos);
			if ( m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_dbMinDataY < strYMapper.m_dbYDataMin )
			{
				m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_dbMinDataY = strYMapper.m_dbYDataMin;
			}
		}
		break;
	case REGION_CURSOR_CENTER:
		{
			int iDeltaX = iXPos - m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_ptMouseSave.x;
			int iRegionWidth = m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_iMaxPosX - m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_iMinPosX;
			int iNewMinXPos = m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_iMinPosX + iDeltaX;
			int iNewMaxXPos = m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_iMaxPosX + iDeltaX;
			if ( iNewMinXPos < m_XMapper.m_iXPtMin )
			{
				iNewMinXPos = m_XMapper.m_iXPtMin;
				iNewMaxXPos = iNewMinXPos + iRegionWidth;
			}
			if ( iNewMaxXPos > m_XMapper.m_iXPtMax )
			{
				iNewMaxXPos = m_XMapper.m_iXPtMax;
				iNewMinXPos = iNewMaxXPos - iRegionWidth;
			}
			m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_iMinPosX = iNewMinXPos;
			m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_iMaxPosX = iNewMaxXPos;

			m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_dbMinDataX = m_XMapper.CalcPtToXData(iNewMinXPos);
			if ( m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_dbMinDataX < m_XMapper.m_dbXDataMin )
			{
				m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_dbMinDataX = m_XMapper.m_dbXDataMin;
			}
			m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_dbMaxDataX = m_XMapper.CalcPtToXData(iNewMaxXPos);
			if ( m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_dbMaxDataX > m_XMapper.m_dbXDataMax )
			{
				m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_dbMaxDataX = m_XMapper.m_dbXDataMax;
			}

			CPoint ptNewSave;
			ptNewSave.x = iXPos;
			ptNewSave.y = iYPos;
			m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_ptMouseSave = ptNewSave;
		}
		break;
	}

	return true;
}

//! Added by LHW [2008/11/28]
//! Modify by LHW [2008/11/30] : 실제 기능 구현
//! Modify by LHW [2008/12/1] : 커서 선에 둘러싸인 영역 설정
bool CGraph2DWnd::CalcRegionCursor()
{
	int iRegionCursorSize = (int)(m_arrRegionCursor.GetSize());
	if ( iRegionCursorSize <= 0 )
	{
		return false;
	}

	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize <= 0 )
	{
		return false;
	}

	int i = 0, iOverlapIndexTemp = 0;
	int iMinXPosTemp = 0, iMaxXPosTemp = 0, iMinYPosTemp = 0, iMaxYPosTemp = 0;
	strYRangeMapper strYMapper;

	//! 화면의 크기가 변하더라도 커서 위치 유지
	for ( i = 0; i < iRegionCursorSize; i++ )
	{
		iOverlapIndexTemp = m_arrRegionCursor.GetAt(i)->m_strCursorInfo.iOverlapIndex;
		if ( iOverlapIndexTemp < 0 || iOverlapIndexTemp >= iGraphSize )
		{
			continue;
		}

		iMinXPosTemp = m_XMapper.CalcXDataToPt( m_arrRegionCursor.GetAt(i)->m_dbMinDataX );
		iMaxXPosTemp = m_XMapper.CalcXDataToPt( m_arrRegionCursor.GetAt(i)->m_dbMaxDataX );

		strYMapper = m_arrYMapper.GetAt(iOverlapIndexTemp);

		iMinYPosTemp = strYMapper.CalcYDataToPt( m_arrRegionCursor.GetAt(i)->m_dbMinDataY );
		iMaxYPosTemp = strYMapper.CalcYDataToPt( m_arrRegionCursor.GetAt(i)->m_dbMaxDataY );

		m_arrRegionCursor.GetAt(i)->m_iMinPosX = iMinXPosTemp;
		m_arrRegionCursor.GetAt(i)->m_iMaxPosX = iMaxXPosTemp;
		m_arrRegionCursor.GetAt(i)->m_iMinPosY = iMinYPosTemp;
		m_arrRegionCursor.GetAt(i)->m_iMaxPosY = iMaxYPosTemp;

		//! 커서 선으로 둘러싸인 영역 설정
		m_arrRegionCursor.GetAt(i)->m_crSelectRegion.left = iMinXPosTemp;
		m_arrRegionCursor.GetAt(i)->m_crSelectRegion.right = iMaxXPosTemp;
		m_arrRegionCursor.GetAt(i)->m_crSelectRegion.top = iMaxYPosTemp;
		m_arrRegionCursor.GetAt(i)->m_crSelectRegion.bottom = iMinYPosTemp;

		//! 커서 선의 선택 영역 설정
		m_arrRegionCursor.GetAt(i)->m_crSelectLine[REGION_CURSOR_LEFT_VERT].left = iMinXPosTemp - m_iRegionCursorMargin;
		m_arrRegionCursor.GetAt(i)->m_crSelectLine[REGION_CURSOR_LEFT_VERT].right = iMinXPosTemp + m_iRegionCursorMargin;
		m_arrRegionCursor.GetAt(i)->m_crSelectLine[REGION_CURSOR_LEFT_VERT].top = iMaxYPosTemp;
		m_arrRegionCursor.GetAt(i)->m_crSelectLine[REGION_CURSOR_LEFT_VERT].bottom = m_DataRect.bottom;

		m_arrRegionCursor.GetAt(i)->m_crSelectLine[REGION_CURSOR_UP_HORZ].left = iMinXPosTemp;
		m_arrRegionCursor.GetAt(i)->m_crSelectLine[REGION_CURSOR_UP_HORZ].right = iMaxXPosTemp;
		m_arrRegionCursor.GetAt(i)->m_crSelectLine[REGION_CURSOR_UP_HORZ].top = iMaxYPosTemp - m_iRegionCursorMargin;
		m_arrRegionCursor.GetAt(i)->m_crSelectLine[REGION_CURSOR_UP_HORZ].bottom = iMaxYPosTemp + m_iRegionCursorMargin;

		m_arrRegionCursor.GetAt(i)->m_crSelectLine[REGION_CURSOR_DOWN_HORZ].left = iMinXPosTemp;
		m_arrRegionCursor.GetAt(i)->m_crSelectLine[REGION_CURSOR_DOWN_HORZ].right = iMaxXPosTemp;
		m_arrRegionCursor.GetAt(i)->m_crSelectLine[REGION_CURSOR_DOWN_HORZ].top = iMinYPosTemp - m_iRegionCursorMargin;
		m_arrRegionCursor.GetAt(i)->m_crSelectLine[REGION_CURSOR_DOWN_HORZ].bottom = iMinYPosTemp + m_iRegionCursorMargin;

		m_arrRegionCursor.GetAt(i)->m_crSelectLine[REGION_CURSOR_RIGHT_VERT].left = iMaxXPosTemp - m_iRegionCursorMargin;
		m_arrRegionCursor.GetAt(i)->m_crSelectLine[REGION_CURSOR_RIGHT_VERT].right = iMaxXPosTemp + m_iRegionCursorMargin;
		m_arrRegionCursor.GetAt(i)->m_crSelectLine[REGION_CURSOR_RIGHT_VERT].top = iMaxYPosTemp;
		m_arrRegionCursor.GetAt(i)->m_crSelectLine[REGION_CURSOR_RIGHT_VERT].bottom = m_DataRect.bottom;
	}

	return true;
}

//! Added by LHW [2008/6/15]
//! Modify by LHW [2008/6/16] : m_eSelectCursorType 추가
//! Modify by LHW [2008/6/17] : 부모 커서의 Element index를 가져오는 부분의 오류 수정
bool CGraph2DWnd::SetFlag_If_CursorMoved(int iCursorIndex)
{
	int iChildCursorSize = (int)(m_arrChildCursor.GetSize());
	if ( iChildCursorSize <= 0 )
	{
		return false;
	}
	if ( IsValidCursorIndex(iCursorIndex) == false )
	{
		return false;
	}

	int iCursorElementIndex = -1;
	if ( GetCursorElementIndexFromIndex(iCursorIndex, iCursorElementIndex) == false )
	{
		return false;
	}

	for ( int i = 0; i < iChildCursorSize; i++ )
	{
		if ( m_arrChildCursor.GetAt(i)->m_strCursorInfo.iCursorElementIndex == iCursorElementIndex )
		{
			m_arrChildCursor.GetAt(i)->m_bCursorMoved = true;
		}
	}

	m_eSelectCursorType = E_GRAPH2D_MOVE_MAIN_CURSOR_TYPE;

	return true;
}

//! Added by LHW [2008/6/15]
//bool CGraph2DWnd::UpdateCursorDataIndex_Childcursor()
//{
//	int iCursorSize = (int)(m_arrCursor.GetSize());
//	if ( iCursorSize <= 0 )
//	{
//		return false;
//	}
//	int iChildCursorSize = (int)(m_arrChildCursor.GetSize());
//	if ( iChildCursorSize <= 0 )
//	{
//		return false;
//	}
//
//	strGraph2DCursorInfo strCursorInfo;
//	int iCursorElementIndex = 0, iCursorIndex = 0;
//	int i = 0, j = 0;
//	for ( i = 0; i < iChildCursorSize; i++ )
//	{
//		iCursorElementIndex = m_arrChildCursor.GetAt(i)->m_iElementIndex;
//		if ( GetCursorIndexFromElementIndex(iCursorElementIndex, iCursorIndex) == false )
//		{
//			continue;
//		}
//
//		strCursorInfo = m_arrCursor.GetAt(iCursorIndex);
//
//		m_arrChildCursor.GetAt(i)->m_iCursorDataIndex = strCursorInfo.iDataIndex;
//	}
//
//	return true;
//}

//! Modify by LHW [2008/4/17] : E_GRAPH2D_CURSOR_LINE_XY 체크 부분 추가
//! Modify by LHW [2008/5/28] : E_GRAPH2D_CURSOR_XY상태에서 왼쪽 Ctrl키를 누르면 Data-Point관련 동작하도록 수정
//! Modify by LHW [2008/6/13] : 자식 커서에서의 커서 변경 부분 추가
//! Modify by LHW [2008/6/16] : 자식 커서 개수 관련 오류 수정
//! Modify by LHW [2008/8/4] : 보조 커서 관련 부분 추가
//! Modify by LHW [2008/8/20] : E_GRAPH2D_CHILD_CURSOR_LINE_XY 추가
//! Modify by LHW [2008/9/19] : CPU 부하를 줄이기 위해 Ctrl키를 눌렀을 때의 처리를 수정
//! Modify by LHW [2008/10/25] : E_GRAPH2D_ZOOM_Y 추가
//! Modify by LHW [2008/11/30] : 영역 표시 커서 추가
//! Modify by LHW [2008/12/1] : 영역 표시 커서 선에 둘러싸인 사각 영역 관련 추가
//! Modify by LHW [2009/2/2] : Alt, Shift 키를 누른 상태에서 확대, 축소, Pan 기능을 수행할 때의 커서 변경 추가
//! Modify by LHW [2009/2/14] : Alt, Shift 키를 누른 상태이면 무조건 확대, 축소, Pan 기능 커서로 변경되도록 수정
BOOL CGraph2DWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	switch(m_eMouseOperationMode)
	{
	case E_GRAPH2D_CURSOR_XY:
		{
			if ( m_bDataPointEventMsg == true && m_bDataPointCusor == true 
					&& m_hCursor_DataPoint_Event != NULL && GetKeyState(VK_CONTROL) < 0 )
			{
				/*if ( m_bDataPointSearchProcessing == false )
				{
					m_bDataPointSearchProcessing = true;
					CPoint curPos;
					GetCursorPos(&curPos);
					ScreenToClient(&curPos);
					m_bDataPointSearchComplete = SearchDataPoint(curPos);
					m_bDataPointSearchProcessing = false;										
				}*/

				if ( m_bDataPointSearchComplete == true )
				{						
					SetCursor(m_hCursor_DataPoint_Event);
					return TRUE;
				}
			}
			else
			{
				//! 확대, 축소, Pan
				if ( m_bAxisXZoom == true || m_bAxisYzoom == true || m_bAxisXYZoom == true || m_bAxisXPan == true || m_bAxisYPan == true || m_bAxisXYPan == true )
				{
					bool bTemporaryMouseOperation = false;

					if ( GetKeyState(VK_LMENU) < 0 || GetKeyState(VK_RMENU) < 0 )	//! Alt 키
					{
						CPoint curPos;
						GetCursorPos(&curPos);
						ScreenToClient(&curPos);

						if ( m_bAxisXYZoom == true && m_hCursor_Zoom_XY != NULL )
						{
							if ( m_DataRect.PtInRect(curPos) )
							{
								bTemporaryMouseOperation = true;

								SetCursor(m_hCursor_Zoom_XY);
								return TRUE;
							}
						}
						if ( bTemporaryMouseOperation == false && m_bAxisXZoom == true && m_hCursor_Zoom_X != NULL )
						{
							if ( m_crAxisX_Event.PtInRect(curPos) )
							{
								bTemporaryMouseOperation = true;

								SetCursor(m_hCursor_Zoom_X);
								return TRUE;
							}
						}
						if ( bTemporaryMouseOperation == false && m_bAxisYzoom == true && m_hCursor_Zoom_Y != NULL )
						{
							if ( m_crAxisY_Left_Event.PtInRect(curPos) || m_crAxisY_Right_Event.PtInRect(curPos) )
							{
								bTemporaryMouseOperation = true;

								SetCursor(m_hCursor_Zoom_Y);
								return TRUE;
							}
						}
					}
					
					if ( (bTemporaryMouseOperation == false) && (GetKeyState(VK_LSHIFT) < 0 || GetKeyState(VK_RSHIFT) < 0) )	//! Shift 키
					{
						CPoint curPos;
						GetCursorPos(&curPos);
						ScreenToClient(&curPos);

						if ( m_bAxisXYPan == true && m_hCursor_Pan_UP != NULL )
						{
							if ( m_DataRect.PtInRect(curPos) )
							{
								bTemporaryMouseOperation = true;

								SetCursor(m_hCursor_Pan_UP);
								return TRUE;
							}
						}
						if ( bTemporaryMouseOperation == false && m_bAxisXPan == true && m_hCursor_Pan_X != NULL )
						{
							if ( m_crAxisX_Event.PtInRect(curPos) )
							{
								bTemporaryMouseOperation = true;

								SetCursor(m_hCursor_Pan_X);
								return TRUE;
							}
						}
						if ( bTemporaryMouseOperation == false && m_bAxisYPan == true && m_hCursor_Pan_Y != NULL )
						{
							if ( m_crAxisY_Left_Event.PtInRect(curPos) || m_crAxisY_Right_Event.PtInRect(curPos) )
							{
								bTemporaryMouseOperation = true;

								SetCursor(m_hCursor_Pan_Y);
								return TRUE;
							}
						}
					}
				}

				//! 커서
				int iCursorSize = (int)(m_arrCursor.GetSize());
				if ( iCursorSize > 0 )
				{
					CPoint curPos;
					GetCursorPos(&curPos);
					ScreenToClient(&curPos);

					strGraph2DCursorInfo strCursorInfo;

					for ( int i = 0; i < iCursorSize; i++ )
					{
						strCursorInfo = m_arrCursor.GetAt(i);

						if ( m_bCursorInfoSelected == false )
						{
							if ( strCursorInfo.crSelectX.PtInRect(curPos) && strCursorInfo.crSelectY.PtInRect(curPos) )
							{
								SetCursor(m_hCursor_Move);
								return TRUE;
							}
							if ( strCursorInfo.crSelectX.PtInRect(curPos) )
							{
								SetCursor(m_hCursor_Horz);
								return TRUE;
							}
							if ( strCursorInfo.eLineMode == E_GRAPH2D_CURSOR_LINE_XY && strCursorInfo.crSelectY.PtInRect(curPos) )
							{
								SetCursor(m_hCursor_Vert);
								return TRUE;
							}
						}

						if ( strCursorInfo.bShowInfo == true && m_bCursorSelected == false )
						{
							if ( strCursorInfo.crInfo.PtInRect(curPos) )
							{
								SetCursor(m_hCursor_Vert);
								return TRUE;
							}
						}
					}
				}

				//! 자식 커서
				int iChildCursorSize = (int)(m_arrChildCursor.GetSize());
				if ( iChildCursorSize > 0 )
				{
					CPoint curPos;
					GetCursorPos(&curPos);
					ScreenToClient(&curPos);

					for ( int i = 0; i < iChildCursorSize; i++ )
					{
						if ( m_bChildCursorInfoSelected == false )
						{
							if ( m_arrChildCursor.GetAt(i)->m_crSelectX.PtInRect(curPos) && m_arrChildCursor.GetAt(i)->m_crSelectY.PtInRect(curPos) )
							{
								SetCursor(m_hCursor_Move);
								return TRUE;
							}
							if ( m_arrChildCursor.GetAt(i)->m_crSelectX.PtInRect(curPos) )
							{
								SetCursor(m_hCursor_Horz);
								return TRUE;
							}
							if ( m_arrChildCursor.GetAt(i)->m_strCursorInfo.eLineMode == E_GRAPH2D_CHILD_CURSOR_LINE_XY && 
								m_arrChildCursor.GetAt(i)->m_crSelectY.PtInRect(curPos) )
							{
								SetCursor(m_hCursor_Vert);
								return TRUE;
							}
						}

						if ( m_arrChildCursor.GetAt(i)->m_strCursorInfo.bShowInfo == true && m_bChildCursorSelected == false )
						{
							if ( m_arrChildCursor.GetAt(i)->m_crInfo.PtInRect(curPos) )
							{
								SetCursor(m_hCursor_Vert);
								return TRUE;
							}
						}
					}
				}

				//! 보조 커서
				int iAuxCursorGroupSize = GetCurrentAuxCursorGroupSize();
				if ( iAuxCursorGroupSize > 0 )
				{
					CPoint curPos;
					GetCursorPos(&curPos);
					ScreenToClient(&curPos);

					int i = 0, j = 0, iAuxCursorSize = 0;
					strGraph2D_Aux_Cursor_Extend strAuxCursor;

					for ( i = 0; i < iAuxCursorGroupSize; i++ )
					{
						if ( m_arrAuxCursorGroup.GetAt(i)->m_strGroupInfo.bShow == false )
						{
							continue;
						}

						iAuxCursorSize = GetCurrentAuxCursorSize(i);
						if ( iAuxCursorSize <= 0 )
						{
							continue;
						}

						for ( j = 0; j < iAuxCursorSize; j++ )
						{
							strAuxCursor = m_arrAuxCursorGroup.GetAt(i)->m_arrCursorInfo.GetAt(j);
							if ( strAuxCursor.bValid == false )
							{
								continue;
							}

							if ( strAuxCursor.strAuxCursorUser.bMouseEvent == true )
							{
								if ( strAuxCursor.crSelectX.PtInRect(curPos) )
								{
									SetCursor(m_hCursor_Horz);
									return TRUE;
								}
							}
						}
					}
				}

				//! 영역 표시 커서
				int iRegionCursorSize = (int)(m_arrRegionCursor.GetSize());
				if ( iRegionCursorSize > 0 )
				{
					CPoint curPos;
					GetCursorPos(&curPos);
					ScreenToClient(&curPos);

					int iRegionCursorLineIndex = -1;

					for ( int i = 0; i < iRegionCursorSize; i++ )
					{
						if ( m_arrRegionCursor.GetAt(i)->IsPtInSelect(curPos, iRegionCursorLineIndex) == true )
						{
							if ( iRegionCursorLineIndex == REGION_CURSOR_LEFT_VERT || iRegionCursorLineIndex == REGION_CURSOR_RIGHT_VERT )
							{
								SetCursor(m_hCursor_Horz);
								return TRUE;
							}
							else if ( iRegionCursorLineIndex == REGION_CURSOR_UP_HORZ || iRegionCursorLineIndex == REGION_CURSOR_DOWN_HORZ )
							{
								SetCursor(m_hCursor_Vert);
								return TRUE;
							}
						}
						else if ( m_arrRegionCursor.GetAt(i)->m_crSelectRegion.PtInRect(curPos) )
						{
							SetCursor(m_hCursor_Move);
							return TRUE;
						}
					}
				}
			}
		}
		break;
	case E_GRAPH2D_ZOOM_XY:
		{
			if ( m_bZoomMouseDown == true )
			{
				if ( m_hCursor_Zoom_XY != NULL )
				{
					CPoint curPos;
					GetCursorPos(&curPos);
					ScreenToClient(&curPos);

					if ( m_DataRect.PtInRect(curPos) )
					{
						SetCursor(m_hCursor_Zoom_XY);
						return TRUE;
					}
				}
			}
		}
		break;
	case E_GRAPH2D_ZOOM_X:
		{
			if ( m_bZoomMouseDown == true )
			{
				if ( m_hCursor_Zoom_X != NULL )
				{
					CPoint curPos;
					GetCursorPos(&curPos);
					ScreenToClient(&curPos);

					if ( m_DataRect.PtInRect(curPos) || m_crAxisX_Event.PtInRect(curPos) )
					{
						SetCursor(m_hCursor_Zoom_X);
						return TRUE;
					}
				}
			}
		}
		break;
	case E_GRAPH2D_ZOOM_Y:
		{
			if ( m_bZoomMouseDown == true )
			{
				if ( m_hCursor_Zoom_Y != NULL )
				{
					CPoint curPos;
					GetCursorPos(&curPos);
					ScreenToClient(&curPos);

					if ( m_DataRect.PtInRect(curPos) || m_crAxisY_Left_Event.PtInRect(curPos) || m_crAxisY_Right_Event.PtInRect(curPos) )
					{
						SetCursor(m_hCursor_Zoom_Y);
						return TRUE;
					}
				}
			}
		}
		break;
	case E_GRAPH2D_PAN_XY:
		{
			if ( m_bPanMouseDown == true )
			{
				if ( m_hCursor_Pan_DOWN != NULL )
				{
					CPoint curPos;
					GetCursorPos(&curPos);
					ScreenToClient(&curPos);

					if ( m_DataRect.PtInRect(curPos) )
					{
						SetCursor(m_hCursor_Pan_DOWN);
						return TRUE;
					}
				}
			}
			else
			{
				if ( m_hCursor_Pan_UP != NULL )
				{
					CPoint curPos;
					GetCursorPos(&curPos);
					ScreenToClient(&curPos);

					if ( m_DataRect.PtInRect(curPos) )
					{
						SetCursor(m_hCursor_Pan_UP);
						return TRUE;
					}
				}
			}
		}
		break;
	case E_GRAPH2D_PAN_X:
		{
			if ( m_bPanMouseDown == true )
			{
				if ( m_hCursor_Pan_X != NULL )
				{
					CPoint curPos;
					GetCursorPos(&curPos);
					ScreenToClient(&curPos);

					if ( m_DataRect.PtInRect(curPos) || m_crAxisX_Event.PtInRect(curPos) )
					{
						SetCursor(m_hCursor_Pan_X);
						return TRUE;
					}
				}
			}
		}
		break;
	case E_GRAPH2D_PAN_Y:
		{
			if ( m_bPanMouseDown == true )
			{
				if ( m_hCursor_Pan_Y != NULL )
				{
					CPoint curPos;
					GetCursorPos(&curPos);
					ScreenToClient(&curPos);

					if ( m_DataRect.PtInRect(curPos) || m_crAxisY_Left_Event.PtInRect(curPos) || m_crAxisY_Right_Event.PtInRect(curPos) )
					{
						SetCursor(m_hCursor_Pan_Y);
						return TRUE;
					}
				}
			}
		}
		break;
	}

	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

//! Added by LHW [2008/12/1]
bool CGraph2DWnd::SendRegionCursorEventMsg(int iRegionCursorIndex)
{
	if ( m_bRegionCursorEventMsg == false )
	{
		return true;
	}

	if ( m_hMsgHandle == NULL )
	{
		return false;
	}

	if ( IsValidRegionCursorIndex(iRegionCursorIndex) == false )
	{
		return false;
	}

	m_strRegionCursorEventInfo.InitInfo();
	m_strRegionCursorEventInfo.iPlotIndex = m_iPlotIndex;
	m_strRegionCursorEventInfo.iCursorIndex = iRegionCursorIndex;
	m_strRegionCursorEventInfo.dbMinDataX = m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_dbMinDataX;
	m_strRegionCursorEventInfo.dbMaxDataX = m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_dbMaxDataX;
	m_strRegionCursorEventInfo.dbMinDataY = m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_dbMinDataY;
	m_strRegionCursorEventInfo.dbMaxDataY = m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_dbMaxDataY;
	m_strRegionCursorEventInfo.iMinPosX = m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_iMinPosX;
	m_strRegionCursorEventInfo.iMaxPosX = m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_iMaxPosX;
	m_strRegionCursorEventInfo.iMinPosY = m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_iMinPosY;
	m_strRegionCursorEventInfo.iMaxPosY = m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_iMaxPosY;

	::SendMessage(m_hMsgHandle, WM_GRAPH2D_REGION_CURSOR_EVENT, 0, (LPARAM)&m_strRegionCursorEventInfo);

	return true;
}

bool CGraph2DWnd::SendCursorEventMsg(int iCursorIndex, bool bMouseOperation, E_GRAPH2D_CURSOR_OPERATION_MODE eOperationMode, strGraph2DCursorInfo* pstrCursorInfo)
{
	if ( m_bCursorEventMsg == false )
	{
		return true;
	}

	if ( pstrCursorInfo == NULL )
	{
		return false;
	}

	if ( m_hMsgHandle == NULL )
	{
		return false;
	}

	m_strCursorEventInfo.iPlotIndex = m_iPlotIndex;

	m_strCursorEventInfo.iCursorIndex = iCursorIndex;
	m_strCursorEventInfo.bMouseOperation = bMouseOperation;
	m_strCursorEventInfo.eOperationMode = eOperationMode;
	m_strCursorEventInfo.eLineMode = pstrCursorInfo->eLineMode;

	m_strCursorEventInfo.iOverlapIndex = pstrCursorInfo->iSelectOverlapIndex;
	m_strCursorEventInfo.iDataIndex = pstrCursorInfo->iDataIndex;

	m_strCursorEventInfo.dbXData = pstrCursorInfo->dbXData;
	m_strCursorEventInfo.dbYData = pstrCursorInfo->dbYData;
	m_strCursorEventInfo.iXPos = pstrCursorInfo->iXPos;
	m_strCursorEventInfo.iYPos = pstrCursorInfo->iYPos;

	m_strCursorEventInfo.bMaxHold = pstrCursorInfo->bMaxHold;
	m_strCursorEventInfo.iSearchMargin = pstrCursorInfo->iSearchMargin;

	::SendMessage(m_hMsgHandle, WM_GRAPH2D_CURSOR_EVENT, 0, (LPARAM)&m_strCursorEventInfo);

	return true;
}

bool CGraph2DWnd::ShowToggleCursorInfoInSelected(bool bRecvEvent)
{
	return ShowToggleCursorInfo(m_iSelectCursorIndex, bRecvEvent);	
}

bool CGraph2DWnd::ShowToggleCursorInfo(int iCursorIndex, bool bRecvEvent)
{
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize > 0 )
	{
		if ( iCursorIndex >= 0 && iCursorIndex < iCursorSize )
		{
			strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(iCursorIndex);
			strCursorInfo.bShowInfo = !(strCursorInfo.bShowInfo);
			m_arrCursor.SetAt(iCursorIndex, strCursorInfo);
			if ( bRecvEvent == false )
			{
				SendCursorEventMsg(iCursorIndex, false, E_GRAPH2D_CURSOR_SHOW_INFO, &strCursorInfo);
			}
			return true;
		}
	}
	return false;
}

bool CGraph2DWnd::ShowCursorInfoInSelected(bool bShow, bool bRecvEvent)
{
	return ShowCursorInfo(m_iSelectCursorIndex, bShow, bRecvEvent);
}

bool CGraph2DWnd::ShowCursorInfo(int iCursorIndex, bool bShow, bool bRecvEvent)
{
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize > 0 )
	{
		if ( iCursorIndex >= 0 && iCursorIndex < iCursorSize )
		{
			strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(iCursorIndex);
			strCursorInfo.bShowInfo = bShow;
			m_arrCursor.SetAt(iCursorIndex, strCursorInfo);
			if ( bRecvEvent == false )
			{
				SendCursorEventMsg(iCursorIndex, false, E_GRAPH2D_CURSOR_SHOW_INFO, &strCursorInfo);
			}
			return true;
		}
	}
	return false;
}

bool CGraph2DWnd::DeleteCursorInSelected(bool bRecvEvent)
{
	return DeleteCursor(m_iSelectCursorIndex, bRecvEvent);	
}

//! Modify by LHW [2008/4/19] : 보조 커서 삭제 부분 추가
//! Modify by LHW [2008/6/14] : 자식 커서 삭제 부분 추가
bool CGraph2DWnd::DeleteCursor(int iCursorIndex, bool bRecvEvent)
{
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize > 0 )
	{
		if ( iCursorIndex >= 0 && iCursorIndex < iCursorSize )
		{			
			strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(iCursorIndex);

			//! 자식 커서 삭제
			RemoveChildCursor(strCursorInfo.iElementIndex);

			//! 보조 커서 삭제
			if ( strCursorInfo.iAuxCursorGroupElementIndex >= 0 )
			{
				int iDeleteAuxCursorGroupIndex = -1;
				GetAuxCursorGroupIndexFromElementIndex(strCursorInfo.iAuxCursorGroupElementIndex, iDeleteAuxCursorGroupIndex);
				RemoveOneAuxCursorGroup(iDeleteAuxCursorGroupIndex);
			}

			m_arrCursor.RemoveAt(iCursorIndex);
			m_arrCursor.FreeExtra();

			//! Modify by LHW [2008/4/11]
			if ( m_iSelectCursorIndex == iCursorIndex )
			{
				m_iSelectCursorIndex = -1;
			}

			//! Modify by LHW [2008/4/11]
			if ( m_iSelectedCursorIndex == iCursorIndex )
			{
				iCursorSize = (int)(m_arrCursor.GetSize());			
				if ( m_iSelectedCursorIndex >= iCursorSize )
				{
					m_iSelectedCursorIndex = iCursorSize - 1;
				}
				if ( m_iSelectedCursorIndex < 0 )
				{
					m_iSelectedCursorIndex = 0;
				}
			}

			if ( bRecvEvent == false )
			{
				SendCursorEventMsg(iCursorIndex, false, E_GRAPH2D_CURSOR_DELETE, &strCursorInfo);
			}

			return true;
		}
	}
	return false;
}

//! Added by LHW [2008/7/29]
bool CGraph2DWnd::DeleteAllCursor(int iOverlapIndex, bool bRecvEvent)
{
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize <= 0 )
	{
		return false;
	}
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}

	int i = 0;
	strGraph2DCursorInfo strCursorInfoForCheck;
	for ( i = 0; i < iCursorSize; i++ )
	{
		strCursorInfoForCheck = m_arrCursor.GetAt(i);
		if ( strCursorInfoForCheck.iSelectOverlapIndex == iOverlapIndex )
		{
			if ( DeleteCursor(i, bRecvEvent) == false )
			{
				return false;
			}

			iCursorSize = (int)(m_arrCursor.GetSize());
			i--;
		}
	}

	return true;
}

//! Modify by LHW [2008/4/19] : 보조 커서 삭제 부분 추가
//! Modify by LHW [2008/6/14] : 자식 커서 삭제 부분 추가
bool CGraph2DWnd::DeleteAllCursor(bool bRecvEvent)
{
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize > 0 )
	{
		strGraph2DCursorInfo strCursorInfo;
		int iDeleteAuxCursorGroupIndex = -1;

		for ( int i = 0; i < iCursorSize; i++ )
		{
			strCursorInfo = m_arrCursor.GetAt(i);

			//! 자식 커서 삭제
			RemoveChildCursor(strCursorInfo.iElementIndex);

			//! 보조 커서 삭제
			if ( strCursorInfo.iAuxCursorGroupElementIndex >= 0 )
			{
				GetAuxCursorGroupIndexFromElementIndex(strCursorInfo.iAuxCursorGroupElementIndex, iDeleteAuxCursorGroupIndex);
				RemoveOneAuxCursorGroup(iDeleteAuxCursorGroupIndex);
			}
		}
	}

	m_arrCursor.RemoveAll();
	m_arrCursor.FreeExtra();
	m_iSelectCursorIndex = 0;
	m_iSelectedCursorIndex = 0;
	strGraph2DCursorInfo strCursorInfo;
	strCursorInfo.InitInfo();
	if ( bRecvEvent == false )
	{
		SendCursorEventMsg(-1, false, E_GRAPH2D_CURSOR_DELETE_ALL, &strCursorInfo);
	}
	return true;
}

//! Added by LHW [2008/7/29]
bool CGraph2DWnd::ReAdjustAllCursor(bool bSearchDirectionFlag)
{
	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize <= 0 )
	{
		return false;
	}
	
	bool bSearchFlag = false;
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize > 0 )
	{
		strGraph2DCursorInfo strCursorInfo;

		int i = 0, j = 0, iNewGraphIndex = 0, iOldGraphIndex = 0;

		for ( i = 0; i < iCursorSize; i++ )
		{
			bSearchFlag = false;
			strCursorInfo = m_arrCursor.GetAt(i);
			iOldGraphIndex = strCursorInfo.iSelectOverlapIndex;

			iGraphSize = (int)(m_arrPlotData.GetSize());
			if ( iOldGraphIndex < 0 || iOldGraphIndex >= iGraphSize )
			{
				bSearchFlag = true;
			}
			else
			{
				if ( m_arrPlotData.GetAt(iOldGraphIndex)->GetPointSize() <= 0 )
				{
					bSearchFlag = true;
				}
			}

			if ( bSearchFlag == true )
			{
				iNewGraphIndex = -1;

				if ( bSearchDirectionFlag == true )
				{
					for ( j = 0; j < iGraphSize; j++ )
					{
						if ( m_arrPlotData.GetAt(j)->GetPointSize() > 0 )
						{
							iNewGraphIndex = j;
							break;
						}
					}
				}
				else
				{
					for ( j = (iGraphSize - 1); j >= 0 ; j-- )
					{
						if ( m_arrPlotData.GetAt(j)->GetPointSize() > 0 )
						{
							iNewGraphIndex = j;
							break;
						}
					}
				}

				strCursorInfo.iSelectOverlapIndex = iNewGraphIndex;
				m_arrCursor.SetAt(i, strCursorInfo);
			}			
		}
	}

	return true;
}

bool CGraph2DWnd::IsShowCursorInfoInSelected()
{	
	return IsShowCursorInfo(m_iSelectCursorIndex);
}

bool CGraph2DWnd::IsShowCursorInfo(int iCursorIndex)
{
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize > 0 )
	{
		if ( iCursorIndex >= 0 && iCursorIndex < iCursorSize )
		{
			strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(iCursorIndex);
			return strCursorInfo.bShowInfo;
		}
	}
	return false;
}

//! Modify by LHW [2008/7/24] : iOverlapIndex 추가
bool CGraph2DWnd::AddCursorInMouseClick(bool bRecvEvent, int iOverlapIndex)
{
	return AddCursorInPosition(m_ptSave.x, m_ptSave.y, bRecvEvent, iOverlapIndex);	
}

//! Modify by LHW [2008/4/28] : crInfo.top관련 수정
//! Modify by LHW [2008/6/16] : m_eSelectCursorType 추가
//! Modify by LHW [2008/7/24] : iOverlapIndex 추가
bool CGraph2DWnd::AddCursorInPosition(int iXPos, int iYPos, bool bRecvEvent, int iOverlapIndex)
{
	if ( iXPos < 0 || iYPos < 0 )
	{
		return false;
	}

	strGraph2DCursorInfo strCursorInfo;
	strCursorInfo.InitInfo();

	strCursorInfo.iSelectOverlapIndex = iOverlapIndex;

	if ( CalcCursorPos(iXPos, iYPos, true, &strCursorInfo) == false )
	{
		return false;
	}

	int iElementIndex = GetCursorPossibleElementIndex();
	if ( iElementIndex < 0 )
	{
		return false;
	}

	strCursorInfo.iElementIndex = iElementIndex;
	strCursorInfo.crInfo.top = strCursorInfo.iYPos;// + m_iCursorMargin;
	strCursorInfo.crData = m_DataRect;
	strCursorInfo.eLineMode = m_eCursorLineMode;

	m_arrCursor.Add(strCursorInfo);

	int iCursorSize = GetCurrentCursorSize();
	if ( iCursorSize <= 0 )
	{
		return false;
	}

	m_iSelectCursorIndex = iCursorSize - 1;
	m_iSelectedCursorIndex = iCursorSize - 1;
	m_eSelectCursorType = E_GRAPH2D_MOVE_MAIN_CURSOR_TYPE;

	if ( bRecvEvent == false )
	{
		int iCursorSize = (int)(m_arrCursor.GetSize());
		SendCursorEventMsg(iCursorSize - 1, true, E_GRAPH2D_CURSOR_ADD, &strCursorInfo);
	}

	return true;
}

//! Modify by LHW [2008/4/28] : crInfo.top관련 수정
//! Modify by LHW [2008/6/16] : m_eSelectCursorType 추가
//! Modify by LHW [2013/2/22] : iSelectOverlapIndex 오류 수정
bool CGraph2DWnd::AddCursorInDataIndex(int iDataIndex, bool bRecvEvent, int iOverlapIndex)
{
	strGraph2DCursorInfo strCursorInfo;
	strCursorInfo.InitInfo();
	strCursorInfo.iSelectOverlapIndex = iOverlapIndex;

	if ( SetCursorInfo(iDataIndex, &strCursorInfo, iOverlapIndex) == false )
	{
		return false;
	}
	int iElementIndex = GetCursorPossibleElementIndex();
	if ( iElementIndex < 0 )
	{
		return false;
	}

	strCursorInfo.iElementIndex = iElementIndex;
	strCursorInfo.crInfo.top = strCursorInfo.iYPos;// + m_iCursorMargin;
	strCursorInfo.crData = m_DataRect;
	strCursorInfo.eLineMode = m_eCursorLineMode;

	m_arrCursor.Add(strCursorInfo);

	int iCursorSize = GetCurrentCursorSize();
	if ( iCursorSize <= 0 )
	{
		return false;
	}

	m_iSelectCursorIndex = iCursorSize - 1;
	m_iSelectedCursorIndex = iCursorSize - 1;
	m_eSelectCursorType = E_GRAPH2D_MOVE_MAIN_CURSOR_TYPE;

	if ( bRecvEvent == false )
	{
		int iCursorSize = (int)(m_arrCursor.GetSize());
		SendCursorEventMsg(iCursorSize - 1, false, E_GRAPH2D_CURSOR_ADD, &strCursorInfo);
	}

	return true;
}

int CGraph2DWnd::GetCurrentCursorSize()
{
	return (int)(m_arrCursor.GetSize());
}

bool CGraph2DWnd::IsCurrentCursorSelect(int &iSelectCursorIndex)
{
	iSelectCursorIndex = -1;

	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize > 0 )
	{
		if ( m_iSelectCursorIndex >= 0 && m_iSelectCursorIndex < iCursorSize )
		{
			iSelectCursorIndex = m_iSelectCursorIndex;
			return true;
		}
	}
	return false;
}

bool CGraph2DWnd::IsCursorSelected(int &iSelectCursorIndex)
{
	iSelectCursorIndex = -1;

	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize > 0 )
	{
		if ( m_iSelectedCursorIndex >= 0 && m_iSelectedCursorIndex < iCursorSize )
		{
			iSelectCursorIndex = m_iSelectedCursorIndex;
			return true;
		}
	}
	return false;
}

//! Modify by LHW [2008/6/15] : SetFlag_If_CursorMoved 추가
bool CGraph2DWnd::MoveCursor(int iCursorIndex, bool bMoveRight, bool bRecvEvent, int iOverlapIndex)
{
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize > 0 )
	{
		if ( iCursorIndex >= 0 && iCursorIndex < iCursorSize )
		{
			if ( IsValidOverlapIndex(iOverlapIndex) == false )
			{
				return false;
			}
			int iDrawDataSize = m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize();
			if ( iDrawDataSize <= 0 )
			{
				return false;
			}
			if ( m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.bShowGraph == false )
			{
				return false;
			}

			strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(iCursorIndex);

			if ( strCursorInfo.bMaxHold == true )
			{
				return false;
			}

			int iCurrentCursorDataIndex = strCursorInfo.iDataIndex;
			if ( bMoveRight == true )
			{
				iCurrentCursorDataIndex++;
			}
			else
			{
				iCurrentCursorDataIndex--;
			}

			if ( iCurrentCursorDataIndex < 0 )
			{
				iCurrentCursorDataIndex = 0;
			}
			if ( iCurrentCursorDataIndex >= iDrawDataSize )
			{
				iCurrentCursorDataIndex = iDrawDataSize - 1;
			}

			if ( SetCursorInfo(iCurrentCursorDataIndex, &strCursorInfo, iOverlapIndex) == false )
			{
				return false;
			}

			m_arrCursor.SetAt(iCursorIndex, strCursorInfo);

			SetFlag_If_CursorMoved(iCursorIndex);

			if ( bRecvEvent == false )
			{
				SendCursorEventMsg(iCursorIndex, false, E_GRAPH2D_CURSOR_MOVE, &strCursorInfo);
			}
			
			return true;
		}
	}

	return false;
}

//! Modify by LHW [2008/6/15] : SetFlag_If_CursorMoved 추가
bool CGraph2DWnd::MoveCursor(int iCursorIndex, int iDataIndex, bool bRecvEvent, int iOverlapIndex)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}
	if ( m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.bShowGraph == false )
	{
		return false;
	}

	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize > 0 )
	{
		if ( iCursorIndex >= 0 && iCursorIndex < iCursorSize )
		{
			strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(iCursorIndex);

			if ( strCursorInfo.bMaxHold == true )
			{
				return false;
			}

			if ( SetCursorInfo(iDataIndex, &strCursorInfo, iOverlapIndex) == false )
			{
				return false;
			}

			m_arrCursor.SetAt(iCursorIndex, strCursorInfo);

			SetFlag_If_CursorMoved(iCursorIndex);

			if ( bRecvEvent == false )
			{
				SendCursorEventMsg(iCursorIndex, false, E_GRAPH2D_CURSOR_MOVE, &strCursorInfo);
			}
			
			return true;
		}
	}

	return false;
}

bool CGraph2DWnd::MoveAuxCursor(int iAuxCursorGroupIndex, int iAuxCursorIndex, int iDataIndex, int iOverlapIndex)
{
	if ( m_hMsgHandle == NULL )
	{
		return false;
	}
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}
	if ( m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.bShowGraph == false )
	{
		return false;
	}
	int iDrawDataSize = m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize();
	if ( iDrawDataSize <= 0 )
	{
		return false;
	}

	int iAuxCursorGroupSize = GetCurrentAuxCursorGroupSize();
	if ( iAuxCursorGroupIndex < 0 || iAuxCursorGroupIndex >= iAuxCursorGroupSize )
	{
		return false;
	}

	int iAuxCursorSize = GetCurrentAuxCursorSize(iAuxCursorGroupIndex);
	if ( iAuxCursorIndex < 0 || iAuxCursorIndex >= iAuxCursorSize )
	{
		return false;
	}

	strGraph2D_Aux_Cursor_Extend strAuxCursor;
	strAuxCursor = m_arrAuxCursorGroup.GetAt(iAuxCursorGroupIndex)->m_arrCursorInfo.GetAt(iAuxCursorIndex);

	if ( strAuxCursor.strAuxCursorUser.bIndependency == false )
	{
		return false;
	}

	if ( iDataIndex < 0 )
	{
		iDataIndex = 0;
	}
	if ( iDataIndex >= iDrawDataSize )
	{
		iDataIndex = iDrawDataSize - 1;
	}

	m_strAuxCursorEventInfo.iPlotIndex = m_iPlotIndex;
	m_strAuxCursorEventInfo.iAuxCursorGroupElementIndex = m_arrAuxCursorGroup.GetAt(iAuxCursorGroupIndex)->m_iElementIndex;
	m_strAuxCursorEventInfo.iAuxCursorElementIndex = strAuxCursor.iElementIndex;
	m_strAuxCursorEventInfo.iAuxCursorGroupIndex = iAuxCursorGroupIndex;
	m_strAuxCursorEventInfo.iAuxCursorIndex = iAuxCursorIndex;

	m_strAuxCursorEventInfo.iDataIndex = iDataIndex;
	m_strAuxCursorEventInfo.dbXData = m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(iDataIndex);
	m_strAuxCursorEventInfo.dbYData = m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(iDataIndex);

	::SendMessage(m_hMsgHandle, WM_GRAPH2D_AUX_CURSOR_EVENT, 0, (LPARAM)&m_strAuxCursorEventInfo);

	return true;
}

bool CGraph2DWnd::GetCursorOverlapIndex(int iCursorIndex, int &iOverlapIndex)
{
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize > 0 )
	{
		if ( iCursorIndex >= 0 && iCursorIndex < iCursorSize )
		{
			strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(iCursorIndex);
			iOverlapIndex = strCursorInfo.iSelectOverlapIndex;
			return true;
		}
	}

	return false;
}

//! Added by LHW [2008/7/29]
bool CGraph2DWnd::SetCursorOverlapIndex(int iCursorIndex, int iOverlapIndex)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}

	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize > 0 )
	{
		if ( iCursorIndex >= 0 && iCursorIndex < iCursorSize )
		{
			strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(iCursorIndex);
			strCursorInfo.iSelectOverlapIndex = iOverlapIndex;
			m_arrCursor.SetAt(iCursorIndex, strCursorInfo);
			return true;
		}
	}

	return false;
}

bool CGraph2DWnd::GetCursorDataIndex(int iCursorIndex, int &iDataIndex)
{
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize > 0 )
	{
		if ( iCursorIndex >= 0 && iCursorIndex < iCursorSize )
		{
			strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(iCursorIndex);
			iDataIndex = strCursorInfo.iDataIndex;
			return true;
		}
	}

	return false;
}

bool CGraph2DWnd::GetCursorLineMode(int iCursorIndex, E_GRAPH2D_CURSOR_LINE_MODE &eLineMode)
{
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize > 0 )
	{
		if ( iCursorIndex >= 0 && iCursorIndex < iCursorSize )
		{
			strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(iCursorIndex);
			eLineMode = strCursorInfo.eLineMode;
			return true;
		}
	}

	return false;
}

bool CGraph2DWnd::SetCursorLineMode(int iCursorIndex, E_GRAPH2D_CURSOR_LINE_MODE eLineMode, bool bRecvEvent)
{
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize > 0 )
	{
		if ( iCursorIndex >= 0 && iCursorIndex < iCursorSize )
		{
			strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(iCursorIndex);
			strCursorInfo.eLineMode = eLineMode;
			m_arrCursor.SetAt(iCursorIndex, strCursorInfo);
			if ( bRecvEvent == false )
			{
				SendCursorEventMsg(iCursorIndex, false, E_GRAPH2D_CURSOR_LINE, &strCursorInfo);
			}
			return true;
		}
	}

	return false;
}

bool CGraph2DWnd::GetCursorMaxHold(int iCursorIndex, bool &bMaxHold)
{
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize > 0 )
	{
		if ( iCursorIndex >= 0 && iCursorIndex < iCursorSize )
		{
			strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(iCursorIndex);
			bMaxHold = strCursorInfo.bMaxHold;
			return true;
		}
	}

	return false;
}

bool CGraph2DWnd::SetCursorMaxHold(int iCursorIndex, bool bMaxHold, bool bRecvEvent)
{
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize > 0 )
	{
		if ( iCursorIndex >= 0 && iCursorIndex < iCursorSize )
		{
			strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(iCursorIndex);
			strCursorInfo.bMaxHold = bMaxHold;
			m_arrCursor.SetAt(iCursorIndex, strCursorInfo);
			if ( bRecvEvent == false )
			{
				SendCursorEventMsg(iCursorIndex, false, E_GRAPH2D_CURSOR_MAX_HOLD, &strCursorInfo);
			}
			return true;
		}
	}

	return false;
}

bool CGraph2DWnd::GetCursorValue(int iCursorIndex, int &iDataIndex, double &dbValueX, double &dbValueY)
{
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize > 0 )
	{
		if ( iCursorIndex >= 0 && iCursorIndex < iCursorSize )
		{
			strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(iCursorIndex);
			dbValueX = strCursorInfo.dbXData;
			dbValueY = strCursorInfo.dbYData;
			iDataIndex = strCursorInfo.iDataIndex;
			return true;
		}
	}

	return false;
}

//! Added by LHW [2008/7/24]
//! Modify by LHW [2009/1/9] : 중간 처리 부분의 오류 수정
//! Modify by LHW [2009/3/1] : 값을 찾아내는 과정을 개선
//! Modify by LHW [2009/4/2] : 실수형 값이 동일하다는 판정을 하는 기준을 작게 설정
bool CGraph2DWnd::GetDataYValue(int iDataIndex, double dbValueX, int iOverlapIndex, bool bEqualInterval, double &dbValueY)
{
	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize <= 0 )
	{
		return false;
	}
	if ( iOverlapIndex < 0 || iOverlapIndex >= iGraphSize )
	{
		return false;
	}
	int iDrawDataSize = m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize();
	if ( iDrawDataSize <= 0 )
	{
		return false;
	}

	double dbTempX = 0.;
	if ( iDataIndex >= 0 && iDataIndex < iDrawDataSize )
	{
		dbTempX = m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(iDataIndex);
		if ( fabs(dbTempX - dbValueX) < 0.0000001 )
		{
			dbValueY = m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(iDataIndex);
			return true;
		}
	}
	if ( iDrawDataSize <= 1 )
	{
		return false;
	}
	if ( dbValueX > m_arrPlotData.GetAt(iOverlapIndex)->m_dbMaxX )
	{
		return false;
	}
	if ( dbValueX < m_arrPlotData.GetAt(iOverlapIndex)->m_dbMinX )
	{
		return false;
	}

	bool bExactSearch = false;
	int i = 0, iTempIndex = -1;

	if ( bEqualInterval == true )
	{
		//! X축 방향의 최대값과 실제 데이터 사이의 간격을 계산
		double dbIncrement = (m_arrPlotData.GetAt(iOverlapIndex)->m_dbMaxX - m_arrPlotData.GetAt(iOverlapIndex)->m_dbMinX) / (double)(iDrawDataSize - 1);
		//! 실제 데이터에서의 예상 index값을 구함
		iTempIndex = (int)((dbValueX - m_arrPlotData.GetAt(iOverlapIndex)->m_dbMinX) / dbIncrement);
		if ( iTempIndex >= 0 && iTempIndex < iDrawDataSize )
		{
			dbTempX = m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(iTempIndex);
			if ( fabs(dbTempX - dbValueX) < 0.0000001 )
			{
				dbValueY = m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(iTempIndex);
				return true;
			}
		}

		int iSearchStart = iTempIndex - 10;
		if ( iSearchStart < 0 )
		{
			iSearchStart = 0;
		}
		int iSearchEnd = iTempIndex + 10;
		if ( iSearchEnd >= iDrawDataSize )
		{
			iSearchEnd = iDrawDataSize - 1;
		}

		bExactSearch = false;
		iTempIndex = -1;
		for ( i = iSearchStart; i < iSearchEnd; i++ )
		{
			dbTempX = m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(i);
			if ( fabs(dbTempX - dbValueX) < 0.0000001 )
			{
				iTempIndex = i;
				bExactSearch = true;
				break;
			}
			if ( dbTempX > dbValueX )
			{
				iTempIndex = i;				
				break;
			}
		}
		if ( bExactSearch == true )
		{
			dbValueY = m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(iTempIndex);
			return true;
		}
		if ( iTempIndex < 0 )
		{
			bEqualInterval = false;
		}
	}

	if ( bEqualInterval == false )
	{
		bExactSearch = false;
		iTempIndex = 0;
		for ( i = 0; i < iDrawDataSize; i++ )
		{
			dbTempX = m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(i);
			if ( fabs(dbTempX - dbValueX) < 0.0000001 )
			{
				bExactSearch = true;
				dbValueY = m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(i);
				break;
			}
			
			if ( dbTempX > dbValueX )
			{
				iTempIndex = i;
				break;
			}
		}

		if ( bExactSearch == true )
		{
			return true;
		}
	}

	if ( iTempIndex <= 0 )
	{
		iTempIndex = 1;
	}
	if ( iTempIndex >= iDrawDataSize )
	{
		iTempIndex = iDrawDataSize - 1;
	}
	double dbX1 = m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(iTempIndex - 1);
	double dbX2 = m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(iTempIndex);
	double dbY1 = m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(iTempIndex - 1);
	double dbY2 = m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(iTempIndex);
	double dbTemp = (dbX2 * dbY1) - (dbX1 * dbY2);
	dbValueY = (((dbY2 - dbY1) * dbValueX) + dbTemp) / (dbX2 - dbX1);

	return true;
}

//! Added by LHW [2008/7/01]
bool CGraph2DWnd::GetCursorValueString(int iCursorIndex, CString &szValueX, CString &szValueY)
{
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize > 0 )
	{
		if ( iCursorIndex >= 0 && iCursorIndex < iCursorSize )
		{
			strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(iCursorIndex);
			szValueX = strCursorInfo.szXData;
			szValueY = strCursorInfo.szYData;
			return true;
		}
	}

	return false;
}

//! Added by LHW [2008/7/01]
bool CGraph2DWnd::GetCursorRealPrecision(int iCursorIndex, int &iPrecisionX, int &iPrecisionY)
{
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize > 0 )
	{
		if ( iCursorIndex >= 0 && iCursorIndex < iCursorSize )
		{
			strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(iCursorIndex);
			int iOverlapIndex = strCursorInfo.iSelectOverlapIndex;
			if ( IsValidOverlapIndex(iOverlapIndex) == false )
			{
				return false;
			}
			iPrecisionX = ((CGraph2D_Resource*)m_pPlotResource)->m_iCursorTextPrecision;
			iPrecisionY = m_arrResourceY.GetAt(iOverlapIndex)->m_iCursorTextPrecision;
		}
	}

	return false;
}

//! Added by LHW [2008/4/4]
bool CGraph2DWnd::GetCursorSearchMargin(int iCursorIndex, int &iMargin)
{
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize > 0 )
	{
		if ( iCursorIndex >= 0 && iCursorIndex < iCursorSize )
		{
			strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(iCursorIndex);
			iMargin = strCursorInfo.iSearchMargin;
			return true;
		}
	}

	return false;
}

//! Added by LHW [2008/4/4]
bool CGraph2DWnd::SetCursorSearchMargin(int iCursorIndex, int iMargin, bool bRecvEvent)
{
	if ( iMargin < 0 )
	{
		return false;
	}

	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize > 0 )
	{
		if ( iCursorIndex >= 0 && iCursorIndex < iCursorSize )
		{
			strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(iCursorIndex);
			strCursorInfo.iSearchMargin = iMargin;
			m_arrCursor.SetAt(iCursorIndex, strCursorInfo);
			if ( bRecvEvent == false )
			{
				SendCursorEventMsg(iCursorIndex, false, E_GRAPH2D_CURSOR_SERACH_MARGIN, &strCursorInfo);
			}
			return true;
		}
	}

	return false;
}

//! Added by LHW [2008/4/4]
bool CGraph2DWnd::GetCursorValueVisible(int iCursorIndex, bool &bVisibleX, bool &bVisibleY)
{
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize > 0 )
	{
		if ( iCursorIndex >= 0 && iCursorIndex < iCursorSize )
		{
			strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(iCursorIndex);
			bVisibleX = strCursorInfo.bShowValueX;
			bVisibleY = strCursorInfo.bShowValueY;
			return true;
		}
	}

	return false;
}

//! Added by LHW [2008/4/4]
bool CGraph2DWnd::SetCursorValueVisible(int iCursorIndex, bool bVisibleX, bool bVisibleY, bool bRecvEvent)
{
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize > 0 )
	{
		if ( iCursorIndex >= 0 && iCursorIndex < iCursorSize )
		{
			strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(iCursorIndex);
			strCursorInfo.bShowValueX = bVisibleX;
			strCursorInfo.bShowValueY = bVisibleY;
			m_arrCursor.SetAt(iCursorIndex, strCursorInfo);
			if ( bRecvEvent == false )
			{
				SendCursorEventMsg(iCursorIndex, false, E_GRAPH2D_CURSOR_VALUE_VISIBLE, &strCursorInfo);
			}
			return true;
		}
	}

	return false;
}

//! Addded by LHW [2008/8/01]
bool CGraph2DWnd::GetCursorXYStringVisible(int iCursorIndex, bool &bVisibleX, bool &bVisibleY)
{
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize > 0 )
	{
		if ( iCursorIndex >= 0 && iCursorIndex < iCursorSize )
		{
			strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(iCursorIndex);
			bVisibleX = strCursorInfo.bShowStringX;
			bVisibleY = strCursorInfo.bShowStringY;
			return true;
		}
	}

	return false;
}

//! Addded by LHW [2008/8/01]
bool CGraph2DWnd::SetCursorXYStringVisible(int iCursorIndex, bool bVisibleX, bool bVisibleY, bool bRecvEvent)
{
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize > 0 )
	{
		if ( iCursorIndex >= 0 && iCursorIndex < iCursorSize )
		{
			strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(iCursorIndex);
			strCursorInfo.bShowStringX = bVisibleX;
			strCursorInfo.bShowStringY = bVisibleY;
			m_arrCursor.SetAt(iCursorIndex, strCursorInfo);
			if ( bRecvEvent == false )
			{
				SendCursorEventMsg(iCursorIndex, false, E_GRAPH2D_CURSOR_VALUE_VISIBLE, &strCursorInfo);
			}
			return true;
		}
	}

	return false;
}

//! Added by LHW [2008/4/18]
bool CGraph2DWnd::GetCursorPointVisible(int iCursorIndex, bool &bVisible)
{
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize > 0 )
	{
		if ( iCursorIndex >= 0 && iCursorIndex < iCursorSize )
		{
			strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(iCursorIndex);
			bVisible = strCursorInfo.bShowPoint;			
			return true;
		}
	}

	return false;
}

//! Added by LHW [2008/4/18]
bool CGraph2DWnd::SetCursorPointVisible(int iCursorIndex, bool bVisible, bool bRecvEvent)
{
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize > 0 )
	{
		if ( iCursorIndex >= 0 && iCursorIndex < iCursorSize )
		{
			strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(iCursorIndex);
			strCursorInfo.bShowPoint = bVisible;			
			m_arrCursor.SetAt(iCursorIndex, strCursorInfo);
			if ( bRecvEvent == false )
			{
				SendCursorEventMsg(iCursorIndex, false, E_GRAPH2D_CURSOR_POINT_VISIBLE, &strCursorInfo);
			}
			return true;
		}
	}

	return false;
}

//! Added by LHW [2008/4/19]
//! Modify by LHW [2008/6/12]
bool CGraph2DWnd::GetCursorAuxCursorGroupIndex(int iCursorIndex, int &iAuxCursorGroupElementIndex)
{
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize > 0 )
	{
		if ( iCursorIndex >= 0 && iCursorIndex < iCursorSize )
		{
			strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(iCursorIndex);
			iAuxCursorGroupElementIndex = strCursorInfo.iAuxCursorGroupElementIndex;			
			return true;
		}
	}

	return false;
}

//! Added by LHW [2008/4/19]
//! Modify by LHW [2008/6/12]
bool CGraph2DWnd::SetCursorAuxCursorGroupIndex(int iCursorIndex, int iAuxCursorGroupElementIndex)
{
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize > 0 )
	{
		if ( iCursorIndex >= 0 && iCursorIndex < iCursorSize )
		{
			strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(iCursorIndex);
			strCursorInfo.iAuxCursorGroupElementIndex = iAuxCursorGroupElementIndex;			
			m_arrCursor.SetAt(iCursorIndex, strCursorInfo);
			
			return true;
		}
	}

	return false;
}

//! Added by LHW [2008/4/19]
bool CGraph2DWnd::GetCursorGraphVisibleCheck(int iCursorIndex, bool &bVisibleChk)
{
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize > 0 )
	{
		if ( iCursorIndex >= 0 && iCursorIndex < iCursorSize )
		{
			strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(iCursorIndex);
			bVisibleChk = strCursorInfo.bShowGraphChk;			
			return true;
		}
	}

	return false;
}

//! Added by LHW [2008/4/19]
bool CGraph2DWnd::SetCursorGraphVisibleCheck(int iCursorIndex, bool bVisibleChk)
{
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize > 0 )
	{
		if ( iCursorIndex >= 0 && iCursorIndex < iCursorSize )
		{
			strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(iCursorIndex);
			strCursorInfo.bShowGraphChk = bVisibleChk;			
			m_arrCursor.SetAt(iCursorIndex, strCursorInfo);
			
			return true;
		}
	}

	return false;
}

bool CGraph2DWnd::MakePlotBuffer(int iNewSize)
{
	if ( iNewSize <= 0 )
	{
		return false;
	}

	RemoveAllPlotBuffer();

	for ( int i = 0; i < iNewSize; i++ )
	{
		CGraph2D_Data* pPlotData = NULL;
		CGraph2D_ResourceY* pResourceY = NULL;
		pPlotData = new CGraph2D_Data;
		pResourceY = new CGraph2D_ResourceY;
		if ( pPlotData == NULL || pResourceY == NULL )
		{
			if ( pPlotData != NULL )
			{
				delete pPlotData;
				pPlotData = NULL;
			}
			if ( pResourceY != NULL )
			{
				delete pResourceY;
				pResourceY = NULL;
			}
			RemoveAllPlotBuffer();
			return false;
		}

		pPlotData->m_iElementIndex = i;
		pResourceY->m_iElementIndex = i;

		m_arrPlotData.Add(pPlotData);
		m_arrResourceY.Add(pResourceY);
		
		strYRangeMapper strYMapper;		
		m_arrYMapper.Add(strYMapper);
	}

	return true;
}

//! 기존 버퍼 뒤에 새로운 버퍼를 추가, Added by LHW [2008/4/11]
bool CGraph2DWnd::AddPlotBuffer()
{
	CGraph2D_Data* pPlotData = NULL;
	CGraph2D_ResourceY* pResourceY = NULL;
	pPlotData = new CGraph2D_Data;
	pResourceY = new CGraph2D_ResourceY;
	if ( pPlotData == NULL || pResourceY == NULL )
	{
		if ( pPlotData != NULL )
		{
			delete pPlotData;
			pPlotData = NULL;
		}
		if ( pResourceY != NULL )
		{
			delete pResourceY;
			pResourceY = NULL;
		}
		return false;
	}

	pPlotData->m_iElementIndex = GetDataBufferPossibleElementIndex();
	pResourceY->m_iElementIndex = GetResourceYPossibleElementIndex();

	m_arrPlotData.Add(pPlotData);
	m_arrResourceY.Add(pResourceY);
	
	strYRangeMapper strYMapper;
	m_arrYMapper.Add(strYMapper);

	return true;
}

int CGraph2DWnd::GetPlotBufferSize() const
{
	int iPlotDataSize = (int)(m_arrPlotData.GetSize());
	int iAxisYSize = (int)(m_arrResourceY.GetSize());
	int iSize = __min(iPlotDataSize, iAxisYSize);
	return __min(iSize, (int)(m_arrYMapper.GetSize()));
}

//! Added by LHW [2008/6/15]
bool CGraph2DWnd::IsValidCursorIndex(int iCursorIndex)
{
	if ( iCursorIndex < 0 )
	{
		return false;
	}
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize <= 0 )
	{
		return false;
	}
	if ( iCursorIndex >= iCursorSize )
	{
		return false;
	}

	return true;
}

bool CGraph2DWnd::IsValidOverlapIndex(int iOverlapIndex)
{
	if ( iOverlapIndex < 0 )
	{
		return false;
	}
	int iSize = GetPlotBufferSize();
	if ( iSize <= 0 )
	{
		return false;
	}
	if ( iOverlapIndex >= iSize )
	{
		return false;
	}

	return true;
}

//! Added by LHW [2008/4/19]
bool CGraph2DWnd::IsValidXValueLineIndex(int iLineIndex)
{
	if ( iLineIndex < 0 )
	{
		return false;
	}
	int iSize = (int)(m_arrValueLineX.GetSize());
	if ( iSize <= 0 )
	{
		return false;
	}
	if ( iLineIndex >= iSize )
	{
		return false;
	}

	return true;
}

//! Added by LHW [2008/3/29]
bool CGraph2DWnd::IsValidYValueLineIndex(int iLineIndex)
{
	if ( iLineIndex < 0 )
	{
		return false;
	}
	int iSize = (int)(m_arrValueLineY.GetSize());
	if ( iSize <= 0 )
	{
		return false;
	}
	if ( iLineIndex >= iSize )
	{
		return false;
	}

	return true;
}

//! Added by LHW [2008/8/23]
bool CGraph2DWnd::IsValidGraphEquationIndex(int iGraphIndex)
{
	if ( iGraphIndex < 0 )
	{
		return false;
	}
	int iSize = (int)(m_arrGraphEquation.GetSize());
	if ( iSize <= 0 )
	{
		return false;
	}
	if ( iGraphIndex >= iSize )
	{
		return false;
	}

	return true;
}

//! Added by LHW [2008/11/28]
bool CGraph2DWnd::IsValidRegionCursorIndex(int iRegionCursorIndex)
{
	if ( iRegionCursorIndex < 0 )
	{
		return false;
	}
	int iSize = (int)(m_arrRegionCursor.GetSize());
	if ( iSize <= 0 )
	{
		return false;
	}
	if ( iRegionCursorIndex >= iSize )
	{
		return false;
	}

	return true;
}

bool CGraph2DWnd::RemoveOnePlotBuffer(int iOverlapIndex)
{
	int iSize = __min((int)(m_arrPlotData.GetSize()), (int)(m_arrResourceY.GetSize()));
	if ( iSize > 0 )
	{
		if ( iOverlapIndex < 0 || iOverlapIndex >= iSize )
		{
			return false;
		}

		m_arrResourceY.GetAt(iOverlapIndex)->ReleaseResource();
		delete m_arrResourceY.GetAt(iOverlapIndex);
		m_arrResourceY.RemoveAt(iOverlapIndex);

		m_arrPlotData.GetAt(iOverlapIndex)->ClearBuffer2D();
		delete m_arrPlotData.GetAt(iOverlapIndex);
		m_arrPlotData.RemoveAt(iOverlapIndex);

		m_arrYMapper.RemoveAt(iOverlapIndex);

		iSize = __min((int)(m_arrPlotData.GetSize()), (int)(m_arrResourceY.GetSize()));
		iSize = __min(iSize, (int)(m_arrYMapper.GetSize()));
		if ( iSize <= 0 )
		{
			m_arrResourceY.RemoveAll();
			m_arrResourceY.FreeExtra();
			m_arrPlotData.RemoveAll();
			m_arrPlotData.FreeExtra();
			m_arrYMapper.RemoveAll();
			m_arrYMapper.FreeExtra();
		}

		return true;
	}

	return false;
}

void CGraph2DWnd::RemoveAllPlotBuffer()
{
	int iSize = 0;

	while(1)
	{
		iSize = (int)(m_arrResourceY.GetSize());
		if ( iSize <= 0 )
		{
			break;
		}

		m_arrResourceY.GetAt(0)->ReleaseResource();
		delete m_arrResourceY.GetAt(0);
		m_arrResourceY.RemoveAt(0);
	}

	m_arrResourceY.RemoveAll();
	m_arrResourceY.FreeExtra();

	while(1)
	{
		iSize = (int)(m_arrPlotData.GetSize());
		if ( iSize <= 0 )
		{
			break;
		}

		m_arrPlotData.GetAt(0)->ClearBuffer2D();
		delete m_arrPlotData.GetAt(0);
		m_arrPlotData.RemoveAt(0);
	}

	m_arrPlotData.RemoveAll();
	m_arrPlotData.FreeExtra();

	m_arrYMapper.RemoveAll();
	m_arrYMapper.FreeExtra();
}

//! Modify by LHW [2008/4/19] : bRecvEvent 추가
bool CGraph2DWnd::ZoomArea(CRect crZoomArea, bool bRecvEvent, E_GRAPH2D_ZOOM_DIRECTION eMode)
{
	if ( m_DataRect.Width() <= 0 || m_DataRect.Height() <= 0 )
	{
		return false;
	}
	if ( abs(crZoomArea.Width()) < 1 || abs(crZoomArea.Height()) < 1 )
	{
		return false;
	}
	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize <= 0 )
	{
		return false;
	}

	int i = 0;

	//! 변경하기 전 Range 설정을 저장
	((CGraph2D_Resource*)m_pPlotResource)->AddZoomRecord();
	for ( i = 0; i < iGraphSize; i++ )
	{
		m_arrResourceY.GetAt(i)->AddZoomRecord();		
	}

	//! X축 Range 설정 변경
	if ( eMode != E_GRAPH2D_ZOOM_DIRECTION_Y )
	{
		int iXPtMin = __min(crZoomArea.left, crZoomArea.right);
		int iXPtMax = __max(crZoomArea.left, crZoomArea.right);
		((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bAutoRange = false;
		((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbManualMin = m_XMapper.CalcPtToXData(iXPtMin);
		((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbManualMax = m_XMapper.CalcPtToXData(iXPtMax);
	}

	//! Y축 Range 설정 변경
	if ( eMode != E_GRAPH2D_ZOOM_DIRECTION_X )
	{
		int iYPtMax = __min(crZoomArea.top, crZoomArea.bottom);
		int iYPtMin = __max(crZoomArea.top, crZoomArea.bottom);
		strYRangeMapper strYMapper;
		for ( i = 0; i < iGraphSize; i++ )
		{
			strYMapper = m_arrYMapper.GetAt(i);
			m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.bAutoRange = false;
			m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbManualMin = strYMapper.CalcPtToYData(iYPtMin);
			m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbManualMax = strYMapper.CalcPtToYData(iYPtMax);		
		}
	}

	if ( bRecvEvent == false )
	{
		SendZoomEventMsg(E_GRAPH2D_ZOOM_IN);
	}
	
	return true;
}

//! Added by LHW [2009/2/14]
bool CGraph2DWnd::ZoomX(double dbMin, double dbMax, bool bRecvEvent)
{
	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize <= 0 )
	{
		return false;
	}

	int i = 0;

	//! 변경하기 전 Range 설정을 저장
	((CGraph2D_Resource*)m_pPlotResource)->AddZoomRecord();
	for ( i = 0; i < iGraphSize; i++ )
	{
		m_arrResourceY.GetAt(i)->AddZoomRecord();		
	}

	//! X축 Range 설정 변경
	double dbMinX = __min(dbMin, dbMax);
	double dbMaxX = __max(dbMin, dbMax);
	((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bAutoRange = false;
	((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbManualMin = dbMinX;
	((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbManualMax = dbMaxX;

	if ( bRecvEvent == false )
	{
		SendZoomEventMsg(E_GRAPH2D_ZOOM_IN);
	}
	
	return true;
}

//! Added by LHW [2009/2/14]
bool CGraph2DWnd::ZoomY(bool bRecvEvent)
{
	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize <= 0 )
	{
		return false;
	}
	
	int i = 0;

	//! 변경하기 전 Range 설정을 저장
	((CGraph2D_Resource*)m_pPlotResource)->AddZoomRecord();
	for ( i = 0; i < iGraphSize; i++ )
	{
		m_arrResourceY.GetAt(i)->AddZoomRecord();		
	}

	double dbMinY = 0., dbMaxY = 0.;

	//! Y축 Range 설정 변경
	for ( i = 0; i < iGraphSize; i++ )
	{
		dbMinY = __min(m_arrResourceY.GetAt(i)->m_dbTempRangeMin, m_arrResourceY.GetAt(i)->m_dbTempRangeMax);
		dbMaxY = __max(m_arrResourceY.GetAt(i)->m_dbTempRangeMin, m_arrResourceY.GetAt(i)->m_dbTempRangeMax);
		m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.bAutoRange = false;
		m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbManualMin = dbMinY;
		m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbManualMax = dbMaxY;
	}

	if ( bRecvEvent == false )
	{
		SendZoomEventMsg(E_GRAPH2D_ZOOM_IN);
	}
	
	return true;
}

//! Modify by LHW [2008/4/19] : bRecvEvent 추가
bool CGraph2DWnd::ZoomOut(bool bRecvEvent)
{
	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize <= 0 )
	{
		return false;
	}
	int iRecordSizeX = (int)(((CGraph2D_Resource*)m_pPlotResource)->m_arrZoomRecord.GetSize());
	if ( iRecordSizeX <= 0 )
	{
		return false;
	}
	int iRecordSizeY = 0;

	int i = 0;
	strZoomRecord strZoomX, strZoomY;

	strZoomX = ((CGraph2D_Resource*)m_pPlotResource)->m_arrZoomRecord.GetAt(iRecordSizeX - 1);
	((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bAutoRange = strZoomX.bAutoRange;
	((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbManualMin = strZoomX.dbMin;
	((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbManualMax = strZoomX.dbMax;

	for ( i = 0; i < iGraphSize; i++ )
	{
		iRecordSizeY = (int)(m_arrResourceY.GetAt(i)->m_arrZoomRecord.GetSize());
		strZoomY = m_arrResourceY.GetAt(i)->m_arrZoomRecord.GetAt(iRecordSizeY - 1);
		m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.bAutoRange = strZoomY.bAutoRange;
		m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbManualMin = strZoomY.dbMin;
		m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbManualMax = strZoomY.dbMax;
	}

	((CGraph2D_Resource*)m_pPlotResource)->m_arrZoomRecord.RemoveAt(iRecordSizeX - 1);
	for ( i = 0; i < iGraphSize; i++ )
	{
		iRecordSizeY = (int)(m_arrResourceY.GetAt(i)->m_arrZoomRecord.GetSize());
		m_arrResourceY.GetAt(i)->m_arrZoomRecord.RemoveAt(iRecordSizeY - 1);		
	}

	if ( bRecvEvent == false )
	{
		SendZoomEventMsg(E_GRAPH2D_ZOOM_OUT);
	}

	return true;
}

//! Modify by LHW [2008/4/17] : bDirectionX, bDirectionY 추가
//! Modify by LHW [2008/4/19] : bRecvEvent 추가
bool CGraph2DWnd::ZoomFirstBack(bool bDirectionX, bool bDirectionY, bool bRecvEvent)
{
	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize <= 0 )
	{
		return false;
	}
	int iRecordSize = (int)(((CGraph2D_Resource*)m_pPlotResource)->m_arrZoomRecord.GetSize());
	if ( iRecordSize <= 0 )
	{
		return false;
	}

	if ( bDirectionX == true )
	{
		strZoomRecord strZoomX;
		strZoomX = ((CGraph2D_Resource*)m_pPlotResource)->m_arrZoomRecord.GetAt(0);
		((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bAutoRange = strZoomX.bAutoRange;
		((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbManualMin = strZoomX.dbMin;
		((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbManualMax = strZoomX.dbMax;

		((CGraph2D_Resource*)m_pPlotResource)->m_arrZoomRecord.RemoveAll();
		((CGraph2D_Resource*)m_pPlotResource)->m_arrZoomRecord.FreeExtra();
	}

	if ( bDirectionY == true )
	{
		int i = 0;
		strZoomRecord strZoomY;
		for ( i = 0; i < iGraphSize; i++ )
		{
			strZoomY = m_arrResourceY.GetAt(i)->m_arrZoomRecord.GetAt(0);
			m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.bAutoRange = strZoomY.bAutoRange;
			m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbManualMin = strZoomY.dbMin;
			m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbManualMax = strZoomY.dbMax;

			m_arrResourceY.GetAt(i)->m_arrZoomRecord.RemoveAll();
			m_arrResourceY.GetAt(i)->m_arrZoomRecord.FreeExtra();
		}
	}

	if ( bRecvEvent == false )
	{
		SendZoomEventMsg(E_GRAPH2D_ZOOM_OUT);
	}

	return true;
}

//! Modify by LHW [2008/4/17] : bDirectionX, bDirectionY 추가
//! Modify by LHW [2008/4/18] : 저장된 정보 삭제 부분 수정
//! Modify by LHW [2008/4/19] : bRecvEvent 추가
bool CGraph2DWnd::ZoomFit(bool bDirectionX, bool bDirectionY, bool bRecvEvent)
{
	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize <= 0 )
	{
		return false;
	}

	if ( bDirectionX == true )
	{
		((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bAutoRange = true;		
		((CGraph2D_Resource*)m_pPlotResource)->m_dbPanOffset = 0;
	}

	int i = 0;

	if ( bDirectionY == true )
	{
		for ( i = 0; i < iGraphSize; i++ )
		{
			m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.bAutoRange = true;
			m_arrResourceY.GetAt(i)->m_dbPanOffset = 0;
		}
	}

	((CGraph2D_Resource*)m_pPlotResource)->m_arrZoomRecord.RemoveAll();
	((CGraph2D_Resource*)m_pPlotResource)->m_arrZoomRecord.FreeExtra();

	for ( i = 0; i < iGraphSize; i++ )
	{
		m_arrResourceY.GetAt(i)->m_arrZoomRecord.RemoveAll();
		m_arrResourceY.GetAt(i)->m_arrZoomRecord.FreeExtra();
	}

	m_iPanOffsetX = 0;
	m_iPanOffsetY = 0;

	m_bZoomMouseDown = false;
	m_bPanMouseDown = false;

	m_bCursorSelected = false;
	m_bCursorInfoSelected = false;
	m_bCursorOverlap = false;
	m_iSelectCursorIndex = -1;

	if ( bRecvEvent == false )
	{
		SendZoomEventMsg(E_GRAPH2D_ZOOM_FIT);
	}

	return true;
}

bool CGraph2DWnd::IsZoomIn()
{
	int iRecordSize = (int)(((CGraph2D_Resource*)m_pPlotResource)->m_arrZoomRecord.GetSize());
	if ( iRecordSize > 0 )
	{
		return true;
	}

	return false;
}

//! Added by LHW [2008/4/19] : Zoom 이벤트 메시지 발송
bool CGraph2DWnd::SendZoomEventMsg(E_GRAPH2D_ZOOM_OPERATION_MODE eZoomMode)
{
	if ( m_bZoomEventMsg == false )
	{
		return true;
	}

	if ( m_hMsgHandle == NULL )
	{
		return false;
	}

	m_strZoomEventInfo.InitInfo();
	m_strZoomEventInfo.iPlotIndex = m_iPlotIndex;
	m_strZoomEventInfo.eZoomMode = eZoomMode;

	::SendMessage(m_hMsgHandle, WM_GRAPH2D_ZOOM_EVENT, 0, (LPARAM)&m_strZoomEventInfo);

	return true;
}

bool CGraph2DWnd::ApplyPanPosition()
{
	if ( m_DataRect.Width() <= 0 || m_DataRect.Height() <= 0 )
	{
		return false;
	}
	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize <= 0 )
	{
		return false;
	}
	if ( m_pPlotResource == NULL )
	{
		return false;
	}

	double dbOffsetX = m_XMapper.CalcPtToXData(m_strPanPosition.iEndX) - m_XMapper.CalcPtToXData(m_strPanPosition.iStartX);
	double dbOffsetY = 0.;

	m_iPanOffsetX += (m_strPanPosition.iEndX - m_strPanPosition.iStartX);

	((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.bAutoRange = false;
	((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbManualMin -= dbOffsetX;
	((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.dbManualMax -= dbOffsetX;
	((CGraph2D_Resource*)m_pPlotResource)->m_dbPanOffset -= dbOffsetX;

	strYRangeMapper strYMapper;
	for ( int i = 0; i < iGraphSize; i++ )
	{
		strYMapper = m_arrYMapper.GetAt(i);
		dbOffsetY = strYMapper.CalcPtToYData(m_strPanPosition.iEndY) - strYMapper.CalcPtToYData(m_strPanPosition.iStartY);
		m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.bAutoRange = false;
		m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbManualMin -= dbOffsetY;
		m_arrResourceY.GetAt(i)->m_strResourceYinfo.strAxisInfo.dbManualMax -= dbOffsetY;
		m_arrResourceY.GetAt(i)->m_dbPanOffset -= dbOffsetY;
	}

	m_iPanOffsetY += (m_strPanPosition.iEndY - m_strPanPosition.iStartY);

	return true;
}

bool CGraph2DWnd::IsPanOperated()
{
	if ( abs(m_iPanOffsetX) != 0 || abs(m_iPanOffsetY) != 0 )
	{
		return true;
	}

	return false;
}

//! Added by LHW [2009/5/30]
bool CGraph2DWnd::Add_XMinBound(double dbInput)
{
	if ( m_pPlotResource == NULL )
	{
		return false;
	}

	((CGraph2D_Resource*)m_pPlotResource)->m_arrMinBound.Add(dbInput);

	return true;
}

//! Added by LHW [2009/5/30]
bool CGraph2DWnd::Add_XMaxBound(double dbInput)
{
	if ( m_pPlotResource == NULL )
	{
		return false;
	}

	((CGraph2D_Resource*)m_pPlotResource)->m_arrMaxBound.Add(dbInput);

	return true;
}

//! Added by LHW [2009/5/30]
bool CGraph2DWnd::RemoveAll_XMinBound()
{
	if ( m_pPlotResource == NULL )
	{
		return false;
	}

	((CGraph2D_Resource*)m_pPlotResource)->m_arrMinBound.RemoveAll();
	((CGraph2D_Resource*)m_pPlotResource)->m_arrMinBound.FreeExtra();

	return true;
}

//! Added by LHW [2009/5/30]
bool CGraph2DWnd::RemoveAll_XMaxBound()
{
	if ( m_pPlotResource == NULL )
	{
		return false;
	}

	((CGraph2D_Resource*)m_pPlotResource)->m_arrMaxBound.RemoveAll();
	((CGraph2D_Resource*)m_pPlotResource)->m_arrMaxBound.FreeExtra();

	return true;
}

//! Added by LHW [2009/5/30]
bool CGraph2DWnd::Add_YMinBound(int iOverlapIndex, double dbInput)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}

	m_arrResourceY.GetAt(iOverlapIndex)->m_arrMinBound.Add(dbInput);

	return true;
}

//! Added by LHW [2009/5/30]
bool CGraph2DWnd::Add_YMaxBound(int iOverlapIndex, double dbInput)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}

	m_arrResourceY.GetAt(iOverlapIndex)->m_arrMaxBound.Add(dbInput);

	return true;
}

//! Added by LHW [2009/5/30]
bool CGraph2DWnd::RemoveAll_YMinBound(int iOverlapIndex)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}

	m_arrResourceY.GetAt(iOverlapIndex)->m_arrMinBound.RemoveAll();
	m_arrResourceY.GetAt(iOverlapIndex)->m_arrMinBound.FreeExtra();

	return true;
}

//! Added by LHW [2009/5/30]
bool CGraph2DWnd::RemoveAll_YMaxBound(int iOverlapIndex)
{
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}

	m_arrResourceY.GetAt(iOverlapIndex)->m_arrMaxBound.RemoveAll();
	m_arrResourceY.GetAt(iOverlapIndex)->m_arrMaxBound.FreeExtra();

	return true;
}

double CGraph2DWnd::GetCompareXMinBound(double dbInput)
{
	double dbReturn = dbInput;

	if ( m_pPlotResource != NULL )
	{
		int iBoundSize = (int)(((CGraph2D_Resource*)m_pPlotResource)->m_arrMinBound.GetSize());
		if ( iBoundSize > 0 )
		{
			bool bDecide = false;
			int i = 0;
			double dbBoundTemp = 0., dbReturnTemp = dbInput;

			for ( i = 0; i < iBoundSize; i++ )
			{
				dbBoundTemp = ((CGraph2D_Resource*)m_pPlotResource)->m_arrMinBound.GetAt(i);
				if ( bDecide == false )
				{
					if ( dbReturnTemp > dbBoundTemp )
					{
						bDecide = true;
						dbReturnTemp = dbBoundTemp;
					}
				}
				else
				{
					if ( (dbReturnTemp < dbBoundTemp) && (dbInput > dbBoundTemp) )
					{
						dbReturnTemp = dbBoundTemp;
					}
				}				
			}

			dbReturn = dbReturnTemp;
		}
	}

	return dbReturn;
}

double CGraph2DWnd::GetCompareXMaxBound(double dbInput)
{
	double dbReturn = dbInput;

	if ( m_pPlotResource != NULL )
	{
		int iBoundSize = (int)(((CGraph2D_Resource*)m_pPlotResource)->m_arrMaxBound.GetSize());
		if ( iBoundSize > 0 )
		{
			bool bDecide = false;
			int i = 0;
			double dbBoundTemp = 0., dbReturnTemp = dbInput;

			for ( i = 0; i < iBoundSize; i++ )
			{
				dbBoundTemp = ((CGraph2D_Resource*)m_pPlotResource)->m_arrMaxBound.GetAt(i);
				if ( bDecide == false )
				{
					if ( dbReturnTemp < dbBoundTemp )
					{
						bDecide = true;
						dbReturnTemp = dbBoundTemp;
					}
				}
				else
				{
					if ( (dbReturnTemp > dbBoundTemp) && (dbInput < dbBoundTemp) )
					{
						dbReturnTemp = dbBoundTemp;
					}
				}				
			}

			dbReturn = dbReturnTemp;
		}
	}

	return dbReturn;
}

//! Added by LHW [2009/5/30]
double CGraph2DWnd::GetCompareYMinBound(int iOverlapIndex, double dbInput)
{
	double dbReturn = dbInput;

	if ( IsValidOverlapIndex(iOverlapIndex) == true )
	{
		int iBoundSize = (int)(m_arrResourceY.GetAt(iOverlapIndex)->m_arrMinBound.GetSize());
		if ( iBoundSize > 0 )
		{
			bool bDecide = false;
			int i = 0;
			double dbBoundTemp = 0., dbReturnTemp = dbInput;

			for ( i = 0; i < iBoundSize; i++ )
			{
				dbBoundTemp = m_arrResourceY.GetAt(iOverlapIndex)->m_arrMinBound.GetAt(i);
				if ( bDecide == false )
				{
					if ( dbReturnTemp > dbBoundTemp )
					{
						bDecide = true;
						dbReturnTemp = dbBoundTemp;
					}
				}
				else
				{
					if ( (dbReturnTemp < dbBoundTemp) && (dbInput > dbBoundTemp) )
					{
						dbReturnTemp = dbBoundTemp;
					}
				}				
			}

			dbReturn = dbReturnTemp;
		}
	}

	return dbReturn;
}

//! Added by LHW [2009/5/30]
double CGraph2DWnd::GetCompareYMaxBound(int iOverlapIndex, double dbInput)
{
	double dbReturn = dbInput;

	if ( IsValidOverlapIndex(iOverlapIndex) == true )
	{
		int iBoundSize = (int)(m_arrResourceY.GetAt(iOverlapIndex)->m_arrMaxBound.GetSize());
		if ( iBoundSize > 0 )
		{
			bool bDecide = false;
			int i = 0;
			double dbBoundTemp = 0., dbReturnTemp = dbInput;

			for ( i = 0; i < iBoundSize; i++ )
			{
				dbBoundTemp = m_arrResourceY.GetAt(iOverlapIndex)->m_arrMaxBound.GetAt(i);
				if ( bDecide == false )
				{
					if ( dbReturnTemp < dbBoundTemp )
					{
						bDecide = true;
						dbReturnTemp = dbBoundTemp;
					}
				}
				else
				{
					if ( (dbReturnTemp > dbBoundTemp) && (dbInput < dbBoundTemp) )
					{
						dbReturnTemp = dbBoundTemp;
					}
				}				
			}

			dbReturn = dbReturnTemp;
		}
	}

	return dbReturn;
}

//! Added by LHW [2008/4/19]
int CGraph2DWnd::GetXValueLineSize()
{
	return (int)(m_arrValueLineX.GetSize());
}

//! Added by LHW [2008/4/19]
bool CGraph2DWnd::SetXValueLineInfo(int iLineIndex, strValueLineXInfo strXLineInfo)
{
	if ( IsValidXValueLineIndex(iLineIndex) == false )
	{
		return false;
	}

	m_arrValueLineX.GetAt(iLineIndex)->m_strXLineInfo = strXLineInfo;

	return true;
}

//! Added by LHW [2008/4/19]
bool CGraph2DWnd::GetXValueLineInfo(int iLineIndex, strValueLineXInfo &strXLineInfo)
{
	if ( IsValidXValueLineIndex(iLineIndex) == false )
	{
		return false;
	}

	strXLineInfo = m_arrValueLineX.GetAt(iLineIndex)->m_strXLineInfo;

	return true;
}

//! Added by LHW [2008/4/19]
int CGraph2DWnd::AddXValueLine(strValueLineXInfo strXLineInfo)
{
	int iElementIndex = GetXValueLinePossibleElementIndex();
	if ( iElementIndex < 0 )
	{
		return -1;
	}
	CGraph2D_ValueLineX *pXValueLine = NULL;
	pXValueLine = new CGraph2D_ValueLineX;
	if ( pXValueLine == NULL )
	{
		return -1;
	}
	pXValueLine->m_iElementIndex = iElementIndex;
	pXValueLine->m_strXLineInfo = strXLineInfo;
	m_arrValueLineX.Add(pXValueLine);
	return (GetXValueLineSize() - 1);
}

//! Added by LHW [2008/4/19]
bool CGraph2DWnd::RemoveOneXValueLine(int iLineIndex)
{
	if ( IsValidXValueLineIndex(iLineIndex) == false )
	{
		return false;
	}

	m_arrValueLineX.GetAt(iLineIndex)->ReleaseResource();
	delete m_arrValueLineX.GetAt(iLineIndex);
	m_arrValueLineX.RemoveAt(iLineIndex);

	return true;
}

//! Added by LHW [2008/4/19]
void CGraph2DWnd::RemoveAllXValueLine()
{
	int iSize = 0;

	while(1)
	{
		iSize = (int)(m_arrValueLineX.GetSize());
		if ( iSize <= 0 )
		{
			break;
		}

		m_arrValueLineX.GetAt(0)->ReleaseResource();
		delete m_arrValueLineX.GetAt(0);
		m_arrValueLineX.RemoveAt(0);
	}

	m_arrValueLineX.RemoveAll();
	m_arrValueLineX.FreeExtra();
}

//! Added by LHW [2008/3/29]
int CGraph2DWnd::GetYValueLineSize()
{
	return (int)(m_arrValueLineY.GetSize());
}

//! Added by LHW [2008/3/29]
bool CGraph2DWnd::SetYValueLineInfo(int iLineIndex, strValueLineYInfo strYLineInfo)
{
	if ( IsValidYValueLineIndex(iLineIndex) == false )
	{
		return false;
	}

	m_arrValueLineY.GetAt(iLineIndex)->m_strYLineInfo = strYLineInfo;

	return true;
}

//! Added by LHW [2008/3/29]
bool CGraph2DWnd::GetYValueLineInfo(int iLineIndex, strValueLineYInfo &strYLineInfo)
{
	if ( IsValidYValueLineIndex(iLineIndex) == false )
	{
		return false;
	}

	strYLineInfo = m_arrValueLineY.GetAt(iLineIndex)->m_strYLineInfo;

	return true;
}

//! Added by LHW [2008/3/29]
int CGraph2DWnd::AddYValueLine(strValueLineYInfo strYLineInfo)
{
	int iElementIndex = GetYValueLinePossibleElementIndex();
	if ( iElementIndex < 0 )
	{
		return -1;
	}
	CGraph2D_ValueLineY *pYValueLine = NULL;
	pYValueLine = new CGraph2D_ValueLineY;
	if ( pYValueLine == NULL )
	{
		return -1;
	}
	pYValueLine->m_iElementIndex = iElementIndex;
	pYValueLine->m_strYLineInfo = strYLineInfo;
	m_arrValueLineY.Add(pYValueLine);
	return (GetYValueLineSize() - 1);
}

//! Added by LHW [2008/3/29]
bool CGraph2DWnd::RemoveOneYValueLine(int iLineIndex)
{
	if ( IsValidYValueLineIndex(iLineIndex) == false )
	{
		return false;
	}

	m_arrValueLineY.GetAt(iLineIndex)->ReleaseResource();
	delete m_arrValueLineY.GetAt(iLineIndex);
	m_arrValueLineY.RemoveAt(iLineIndex);

	return true;
}

//! Added by LHW [2008/3/29]
void CGraph2DWnd::RemoveAllYValueLine()
{
	int iSize = 0;

	while(1)
	{
		iSize = (int)(m_arrValueLineY.GetSize());
		if ( iSize <= 0 )
		{
			break;
		}

		m_arrValueLineY.GetAt(0)->ReleaseResource();
		delete m_arrValueLineY.GetAt(0);
		m_arrValueLineY.RemoveAt(0);
	}

	m_arrValueLineY.RemoveAll();
	m_arrValueLineY.FreeExtra();
}

//! Added by LHW [2008/8/23]
int CGraph2DWnd::GetGraphEquationSize()
{
	return (int)(m_arrGraphEquation.GetSize());
}

//! Added by LHW [2008/8/23]
bool CGraph2DWnd::SetGraphEquationInfo(int iGraphIndex, strGraph2DEquationInfo strEquationInfo)
{
	if ( IsValidGraphEquationIndex(iGraphIndex) == false )
	{
		return false;
	}

	m_arrGraphEquation.GetAt(iGraphIndex)->m_strEquationInfo = strEquationInfo;

	return true;
}

//! Added by LHW [2008/8/23]
bool CGraph2DWnd::GetGraphEquationInfo(int iGraphIndex, strGraph2DEquationInfo &strEquationInfo)
{
	if ( IsValidGraphEquationIndex(iGraphIndex) == false )
	{
		return false;
	}
	
	strEquationInfo = m_arrGraphEquation.GetAt(iGraphIndex)->m_strEquationInfo;

	return true;
}

//! Added by LHW [2008/8/23]
int CGraph2DWnd::AddGraphEquation(strGraph2DEquationInfo strEquationInfo)
{
	int iElementIndex = GetGraphEquationPossibleElementIndex();
	if ( iElementIndex < 0 )
	{
		return -1;
	}
	CGraph2D_Equation *pGraphEquation = NULL;
	pGraphEquation = new CGraph2D_Equation;
	if ( pGraphEquation == NULL )
	{
		return -1;
	}
	pGraphEquation->m_iElementIndex = iElementIndex;
	pGraphEquation->m_strEquationInfo = strEquationInfo;
	m_arrGraphEquation.Add(pGraphEquation);
	return (GetGraphEquationSize() - 1);
}

//! Added by LHW [2008/8/23]
bool CGraph2DWnd::RemoveOneGraphEquation(int iGraphIndex)
{
	if ( IsValidGraphEquationIndex(iGraphIndex) == false )
	{
		return false;
	}

	m_arrGraphEquation.GetAt(iGraphIndex)->ReleaseStructureBuf();
	m_arrGraphEquation.GetAt(iGraphIndex)->ReleaseResource();
	delete m_arrGraphEquation.GetAt(iGraphIndex);
	m_arrGraphEquation.RemoveAt(iGraphIndex);

	int iSize = (int)(m_arrGraphEquation.GetSize());
	if ( iSize <= 0 )
	{
		m_arrGraphEquation.RemoveAll();
		m_arrGraphEquation.FreeExtra();
	}

	return true;
}

//! Added by LHW [2008/8/23]
void CGraph2DWnd::RemoveAllGraphEquation()
{
	int iSize = 0;

	while(1)
	{
		iSize = (int)(m_arrGraphEquation.GetSize());
		if ( iSize <= 0 )
		{
			break;
		}

		m_arrGraphEquation.GetAt(0)->ReleaseStructureBuf();
		m_arrGraphEquation.GetAt(0)->ReleaseResource();
		delete m_arrGraphEquation.GetAt(0);
		m_arrGraphEquation.RemoveAt(0);
	}

	m_arrGraphEquation.RemoveAll();
	m_arrGraphEquation.FreeExtra();
}

//! Added by LHW [2008/6/14]
int CGraph2DWnd::GetCurrentChildCursorSize()
{
	return (int)(m_arrChildCursor.GetSize());
}

//! Added by LHW [2008/6/14]
bool CGraph2DWnd::IsCurrentChildCursorSelect(int &iSelectChildCursorIndex)
{
	iSelectChildCursorIndex = -1;

	int iChildCursorSize = (int)(m_arrChildCursor.GetSize());
	if ( iChildCursorSize > 0 )
	{
		if ( m_iSelectChildCursorIndex >= 0 && m_iSelectChildCursorIndex < iChildCursorSize )
		{
			iSelectChildCursorIndex = m_iSelectChildCursorIndex;
			return true;
		}
	}
	return false;
}

//! Added by LHW [2008/6/14]
bool CGraph2DWnd::IsChildCursorSelected(int &iSelectChildCursorIndex)
{
	iSelectChildCursorIndex = -1;

	int iChildCursorSize = (int)(m_arrChildCursor.GetSize());
	if ( iChildCursorSize > 0 )
	{
		if ( m_iSelectedChildCursorIndex >= 0 && m_iSelectedChildCursorIndex < iChildCursorSize )
		{
			iSelectChildCursorIndex = m_iSelectedChildCursorIndex;
			return true;
		}
	}
	return false;
}

//! Added by LHW [2008/6/16]
//! Modify by LHW [2008/6/17] : 부모 커서의 Element index를 가져오는 부분의 오류 수정
bool CGraph2DWnd::IsExistChildCursor(int iElementCursorIndex)
{
	int iChildCursorSize = (int)(m_arrChildCursor.GetSize());
	if ( iChildCursorSize <= 0 )
	{
		return false;
	}
	if ( iElementCursorIndex < 0 )
	{
		return false;
	}

	for ( int i = 0; i < iChildCursorSize; i++ )
	{
		if ( m_arrChildCursor.GetAt(i)->m_strCursorInfo.iCursorElementIndex == iElementCursorIndex )
		{
			return true;
		}
	}

	return false;
}

//! Added by LHW [2008/6/14]
bool CGraph2DWnd::IsValidChildCursorIndex(int iChildCursorIndex)
{
	if ( iChildCursorIndex < 0 )
	{
		return false;
	}
	int iChildCursorSize = (int)(m_arrChildCursor.GetSize());
	if ( iChildCursorSize <= 0 )
	{
		return false;
	}
	if ( iChildCursorIndex >= iChildCursorSize )
	{
		return false;
	}

	return true;
}

//! Added by LHW [2008/6/14]
//! Modify by LHW [2008/6/16] : m_DataRect 설정 부분 추가
int CGraph2DWnd::AddChildCursor(strGraph2D_Child_Cursor strChildCursor)
{
	if ( IsValidOverlapIndex(strChildCursor.iOverlapIndex) == false )
	{
		return -1;
	}
	int iOverlapIndex = strChildCursor.iOverlapIndex;
	int iElementIndex = GetChildCursorPossibleElementIndex();
	if ( iElementIndex < 0 )
	{
		return -1;
	}
	//! 자식 커서와 연결될 커서가 있는지 확인
	if ( IsExistCursorElementIndex(strChildCursor.iCursorElementIndex) == false )
	{
		return -1;
	}
	int iCursorIndex = -1;
	if ( GetCursorIndexFromElementIndex(strChildCursor.iCursorElementIndex, iCursorIndex) == false )
	{
		return -1;
	}
	strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(iCursorIndex);
	int iNewDataIndex = strCursorInfo.iDataIndex;
	int iDataSize = m_arrPlotData.GetAt(strChildCursor.iOverlapIndex)->GetPointSize();
	int iVisualDataSize = m_arrPlotData.GetAt(strChildCursor.iOverlapIndex)->m_iVisualDataSize;
	if ( iVisualDataSize < 20 )
	{
		iVisualDataSize = 20;
	}
	iNewDataIndex -= (iVisualDataSize / 10);
	if ( iNewDataIndex < 0 )
	{
		iNewDataIndex = 0;
	}
	if ( iNewDataIndex >= iDataSize )
	{
		iNewDataIndex = iDataSize - 1;
	}

	CGraph2D_Child_Cursor *pChildCursor = NULL;
	pChildCursor = new CGraph2D_Child_Cursor;
	if ( pChildCursor == NULL )
	{
		return -1;
	}
	pChildCursor->m_iElementIndex = iElementIndex;
	pChildCursor->m_strCursorInfo = strChildCursor;
	pChildCursor->m_iDataIndex = iNewDataIndex;
	pChildCursor->m_crData = m_DataRect;
	m_arrChildCursor.Add(pChildCursor);

	int iNewChildCursorIndex = (int)(m_arrChildCursor.GetSize()) - 1;

	if ( SetChildCursorInfo(iNewDataIndex, iNewChildCursorIndex, true, iOverlapIndex) == false )
	{
		RemoveOneChildCursor(iNewChildCursorIndex);
		return -1;
	}

	m_iSelectChildCursorIndex = iNewChildCursorIndex;
	m_iSelectedChildCursorIndex = iNewChildCursorIndex;

	return iNewChildCursorIndex;
}

//! Added by LHW [2008/6/14]
bool CGraph2DWnd::SetChildCursorInfo(int iChildCursorIndex, strGraph2D_Child_Cursor strChildCursor)
{
	if ( IsValidChildCursorIndex(iChildCursorIndex) == false )
	{
		return false;
	}

	m_arrChildCursor.GetAt(iChildCursorIndex)->m_strCursorInfo = strChildCursor;

	return true;
}

//! Added by LHW [2008/6/14]
bool CGraph2DWnd::GetChildCursorInfo(int iChildCursorIndex, strGraph2D_Child_Cursor &strChildCursor)
{
	if ( IsValidChildCursorIndex(iChildCursorIndex) == false )
	{
		return false;
	}

	strChildCursor = m_arrChildCursor.GetAt(iChildCursorIndex)->m_strCursorInfo;

	return true;
}

//! Added by LHW [2008/6/15]
//! Modify by LHW [2008/6/16] : m_eSelectCursorType 추가
bool CGraph2DWnd::MoveChildCursor(int iChildCursorIndex, int iDataIndex, int iOverlapIndex)
{
	if ( IsValidChildCursorIndex(iChildCursorIndex) == false )
	{
		return false;
	}
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}
	if ( m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.bShowGraph == false )
	{
		return false;
	}

	m_arrChildCursor.GetAt(iChildCursorIndex)->m_iDataIndex = iDataIndex;

	m_eSelectCursorType = E_GRAPH2D_MOVE_CHILD_CURSOR_TYPE;

	return true;
}

//! Added by LHW [2008/6/14]
//! Modify by LHW [2008/6/17] : iDataIndex값 설정 오류 수정
bool CGraph2DWnd::GetChildCursorValue(int iChildCursorIndex, bool &bValid, int &iDataIndex, double &dbValueX, double &dbValueY, double &dbDeltaX, double &dbDeltaY)
{
	if ( IsValidChildCursorIndex(iChildCursorIndex) == false )
	{
		return false;
	}

	bValid = m_arrChildCursor.GetAt(iChildCursorIndex)->m_bDataValid;
	iDataIndex = m_arrChildCursor.GetAt(iChildCursorIndex)->m_iDataIndex;
	dbValueX = m_arrChildCursor.GetAt(iChildCursorIndex)->m_dbXData;
	dbValueY = m_arrChildCursor.GetAt(iChildCursorIndex)->m_dbYData;
	dbDeltaX = m_arrChildCursor.GetAt(iChildCursorIndex)->m_dbDeltaX;
	dbDeltaY = m_arrChildCursor.GetAt(iChildCursorIndex)->m_dbDeltaY;

	return true;
}

//! Added by LHW [2008/6/14]
//! Modify by LHW [2008/6/16] : m_eSelectCursorType 추가
bool CGraph2DWnd::RemoveOneChildCursor(int iChildCursorIndex)
{
	if ( IsValidChildCursorIndex(iChildCursorIndex) == false )
	{
		return false;
	}

	m_arrChildCursor.GetAt(iChildCursorIndex)->ReleaseResource();
	delete m_arrChildCursor.GetAt(iChildCursorIndex);
	m_arrChildCursor.RemoveAt(iChildCursorIndex);

	if ( m_iSelectChildCursorIndex == iChildCursorIndex )
	{
		m_iSelectChildCursorIndex = -1;
	}

	int iChildCursorSize = (int)(m_arrChildCursor.GetSize());

	if ( m_iSelectedChildCursorIndex == iChildCursorIndex )
	{
		if ( m_iSelectedChildCursorIndex >= iChildCursorSize )
		{
			m_iSelectedChildCursorIndex = iChildCursorSize - 1;
		}
		if ( m_iSelectedChildCursorIndex < 0 )
		{
			m_iSelectedChildCursorIndex = 0;
		}
	}
	
	if ( iChildCursorSize <= 0 )
	{
		m_arrChildCursor.RemoveAll();
		m_arrChildCursor.FreeExtra();
	}

	m_eSelectCursorType = E_GRAPH2D_MOVE_MAIN_CURSOR_TYPE;

	return true;
}

//! Added by LHW [2008/6/14]
//! Modify by LHW [2008/6/16] : m_eSelectCursorType 추가
//! Modify by LHW [2008/6/17] : 부모 커서의 Element index를 가져오는 부분의 오류 수정
void CGraph2DWnd::RemoveChildCursor(int iElementCursorIndex)
{
	int iCnt = 0, iChildCursorSize = 0;
	while(1)
	{
		iChildCursorSize = (int)(m_arrChildCursor.GetSize());
		if ( iChildCursorSize <= 0 )
		{
			break;
		}
		if ( iCnt >= iChildCursorSize )
		{
			break;
		}

		if ( m_arrChildCursor.GetAt(iCnt)->m_strCursorInfo.iCursorElementIndex == iElementCursorIndex )
		{
			m_arrChildCursor.GetAt(iCnt)->ReleaseResource();
			delete m_arrChildCursor.GetAt(iCnt);
			m_arrChildCursor.RemoveAt(iCnt);

			if ( m_iSelectChildCursorIndex == iCnt )
			{
				m_iSelectChildCursorIndex = -1;
			}

			if ( m_iSelectedChildCursorIndex == iCnt )
			{
				iChildCursorSize = (int)(m_arrChildCursor.GetSize());

				if ( m_iSelectedChildCursorIndex >= iChildCursorSize )
				{
					m_iSelectedChildCursorIndex = iChildCursorSize - 1;
				}
				if ( m_iSelectedChildCursorIndex < 0 )
				{
					m_iSelectedChildCursorIndex = 0;
				}
			}
		}
		else
		{
			iCnt++;
		}
	}

	iChildCursorSize = (int)(m_arrChildCursor.GetSize());
	if ( iChildCursorSize <= 0 )
	{
		m_arrChildCursor.RemoveAll();
		m_arrChildCursor.FreeExtra();
	}

	m_eSelectCursorType = E_GRAPH2D_MOVE_MAIN_CURSOR_TYPE;
}

//! Added by LHW [2008/6/13]
//! Modify by LHW [2008/6/16] : m_eSelectCursorType 추가
void CGraph2DWnd::RemoveAllChildCursor()
{
	int iSize = 0;

	while(1)
	{
		iSize = (int)(m_arrChildCursor.GetSize());
		if ( iSize <= 0 )
		{
			break;
		}

		m_arrChildCursor.GetAt(0)->ReleaseResource();
		delete m_arrChildCursor.GetAt(0);
		m_arrChildCursor.RemoveAt(0);
	}

	m_arrChildCursor.RemoveAll();
	m_arrChildCursor.FreeExtra();

	m_eSelectCursorType = E_GRAPH2D_MOVE_MAIN_CURSOR_TYPE;
}

//! Added by LHW [2008/11/28]
//! Modify by LHW [2008/11/30] : 실질적인 내용 구현
int CGraph2DWnd::GetCurrentRegionCursorSize()
{
	return (int)(m_arrRegionCursor.GetSize());
}

//! Added by LHW [2008/11/28]
//! Modify by LHW [2008/11/30] : 실질적인 내용 구현
bool CGraph2DWnd::IsCurrentRegionCursorSelect(int &iSelectRegionCursorIndex)
{
	iSelectRegionCursorIndex = -1;

	int iRegionCursorSize = (int)(m_arrRegionCursor.GetSize());
	if ( iRegionCursorSize > 0 )
	{
		if ( m_iSelectRegionCursorIndex >= 0 && m_iSelectRegionCursorIndex < iRegionCursorSize )
		{
			iSelectRegionCursorIndex = m_iSelectRegionCursorIndex;
			return true;
		}
	}
	return false;
}

//! Added by LHW [2008/11/28]
//! Modify by LHW [2008/11/30] : 실질적인 내용 구현
bool CGraph2DWnd::IsRegionCursorSelected(int &iSelectRegionCursorIndex)
{
	iSelectRegionCursorIndex = -1;

	int iRegionCursorSize = (int)(m_arrRegionCursor.GetSize());
	if ( iRegionCursorSize > 0 )
	{
		if ( m_iSelectedRegionCursorIndex >= 0 && m_iSelectedRegionCursorIndex < iRegionCursorSize )
		{
			iSelectRegionCursorIndex = m_iSelectedChildCursorIndex;
			return true;
		}
	}
	return false;
}

//! Added by LHW [2008/11/28]
//! Modify by LHW [2008/11/30] : 실질적인 내용 구현
//! Modify by LHW [2008/12/16] : bChkOverlapIndex 추가
int CGraph2DWnd::AddRegionCursor(strGraph2D_Region_Cursor strRegionCursor, bool bChkOverlapIndex)
{
	if ( bChkOverlapIndex == true )
	{
		if ( IsValidOverlapIndex(strRegionCursor.iOverlapIndex) == false )
		{
			return -1;
		}
	}

	int iOverlapIndex = strRegionCursor.iOverlapIndex;
	int iElementIndex = GetRegionCursorPossibleElementIndex();
	if ( iElementIndex < 0 )
	{
		return -1;
	}

	CGraph2D_Region_Cursor *pRegionCursor = NULL;
	pRegionCursor = new CGraph2D_Region_Cursor;
	if ( pRegionCursor == NULL )
	{
		return -1;
	}
	pRegionCursor->m_iElementIndex = iElementIndex;
	pRegionCursor->m_strCursorInfo = strRegionCursor;
	m_arrRegionCursor.Add(pRegionCursor);

	int iNewRegionCursorIndex = (int)(m_arrRegionCursor.GetSize()) - 1;

	m_iSelectRegionCursorIndex = iNewRegionCursorIndex;
	m_iSelectedRegionCursorIndex = iNewRegionCursorIndex;

	return iNewRegionCursorIndex;
}

//! Added by LHW [2008/11/28]
//! Modify by LHW [2008/11/30] : 실질적인 내용 구현
bool CGraph2DWnd::SetRegionCursorInfo(int iRegionCursorIndex, strGraph2D_Region_Cursor strRegionCursor)
{
	if ( IsValidRegionCursorIndex(iRegionCursorIndex) == false )
	{
		return false;
	}

	m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_strCursorInfo = strRegionCursor;

	return true;
}

//! Added by LHW [2008/11/28]
//! Modify by LHW [2008/11/30] : 실질적인 내용 구현
bool CGraph2DWnd::GetRegionCursorInfo(int iRegionCursorIndex, strGraph2D_Region_Cursor &strRegionCursor)
{
	if ( IsValidRegionCursorIndex(iRegionCursorIndex) == false )
	{
		return false;
	}

	strRegionCursor = m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_strCursorInfo;

	return true;
}

//! Added by LHW [2008/11/28]
//! Modify by LHW [2008/11/30] : 실질적인 내용 구현
//! Modify by LHW [2008/12/1] : 입력값 오류 체크 추가
bool CGraph2DWnd::MoveRegionCursor(int iRegionCursorIndex, double dbInputMinX, double dbInputMaxX, double dbInputMinY, double dbInputMaxY)
{
	if ( dbInputMinX >= dbInputMaxX || dbInputMinY >= dbInputMaxY )
	{
		return false;
	}
	if ( IsValidRegionCursorIndex(iRegionCursorIndex) == false )
	{
		return false;
	}

	m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_dbMinDataX = dbInputMinX;
	m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_dbMaxDataX = dbInputMaxX;
	m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_dbMinDataY = dbInputMinY;
	m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_dbMaxDataY = dbInputMaxY;

	return true;
}

//! Added by LHW [2008/11/28]
//! Modify by LHW [2008/11/30] : 실질적인 내용 구현
bool CGraph2DWnd::GetRegionCursorValue(int iRegionCursorIndex, double &dbOutputMinX, double &dbOutputMaxX, double &dbOutputMinY, double &dbOutputMaxY)
{
	if ( IsValidRegionCursorIndex(iRegionCursorIndex) == false )
	{
		return false;
	}

	dbOutputMinX = m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_dbMinDataX;
	dbOutputMaxX = m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_dbMaxDataX;
	dbOutputMinY = m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_dbMinDataY;
	dbOutputMaxY = m_arrRegionCursor.GetAt(iRegionCursorIndex)->m_dbMaxDataY;

	return true;
}

//! Added by LHW [2008/11/28]
//! Modify by LHW [2008/11/30] : 실질적인 내용 구현
bool CGraph2DWnd::RemoveOneRegionCursor(int iRegionCursorIndex)
{
	if ( IsValidRegionCursorIndex(iRegionCursorIndex) == false )
	{
		return false;
	}

	m_arrRegionCursor.GetAt(iRegionCursorIndex)->ReleaseResource();
	delete m_arrRegionCursor.GetAt(iRegionCursorIndex);
	m_arrRegionCursor.RemoveAt(iRegionCursorIndex);

	if ( m_iSelectRegionCursorIndex == iRegionCursorIndex )
	{
		m_iSelectRegionCursorIndex = -1;
	}

	int iRegionCursorSize = (int)(m_arrRegionCursor.GetSize());

	if ( m_iSelectedRegionCursorIndex == iRegionCursorIndex )
	{
		if ( m_iSelectedRegionCursorIndex >= iRegionCursorSize )
		{
			m_iSelectedRegionCursorIndex = iRegionCursorSize - 1;
		}
		if ( m_iSelectedRegionCursorIndex < 0 )
		{
			m_iSelectedRegionCursorIndex = 0;
		}
	}
	
	if ( iRegionCursorSize <= 0 )
	{
		m_arrRegionCursor.RemoveAll();
		m_arrRegionCursor.FreeExtra();
	}

	return true;
}

//! Added by LHW [2008/11/28]
//! Modify by LHW [2008/11/30] : 실질적인 내용 구현
void CGraph2DWnd::RemoveAllRegionCursor()
{
	int iSize = 0;

	while(1)
	{
		iSize = (int)(m_arrRegionCursor.GetSize());
		if ( iSize <= 0 )
		{
			break;
		}

		m_arrRegionCursor.GetAt(0)->ReleaseResource();
		delete m_arrRegionCursor.GetAt(0);
		m_arrRegionCursor.RemoveAt(0);
	}

	m_arrRegionCursor.RemoveAll();
	m_arrRegionCursor.FreeExtra();
}

//! Added by LHW [2008/6/16]
E_GRAPH2D_MOVE_CURSOR_TYPE CGraph2DWnd::IsCurrentMoveCursorType()
{
	return m_eSelectCursorType;
}

//! Added by LHW [2008/3/31]
int CGraph2DWnd::GetCurrentAuxCursorGroupSize()
{
	return (int)(m_arrAuxCursorGroup.GetSize());
}

//! Added by LHW [2008/3/31]
int CGraph2DWnd::GetCurrentAuxCursorSize(int iAuxCursorGroupIndex)
{
	int iAuxCursorGroupSize = GetCurrentAuxCursorGroupSize();
	if ( iAuxCursorGroupIndex < 0 || iAuxCursorGroupIndex >= iAuxCursorGroupSize )
	{
		return false;
	}

	return m_arrAuxCursorGroup.GetAt(iAuxCursorGroupIndex)->GetCursorInfoSize();
}

//! Added by LHW [2008/8/5]
bool CGraph2DWnd::IsCurrentAuxCursorSelect(int &iSelectAuxCursorGroupIndex, int &iSelectAuxCursorIndex)
{
	iSelectAuxCursorGroupIndex = -1;
	iSelectAuxCursorIndex = -1;

	int iAuxCursorGroupSize = (int)(m_arrAuxCursorGroup.GetSize());
	if ( iAuxCursorGroupSize > 0 )
	{
		if ( m_iSelectAuxCursorGroupIndex >= 0 && m_iSelectAuxCursorGroupIndex < iAuxCursorGroupSize )
		{
			int iAuxCursorSize = 0;
			for ( int i = 0; i < iAuxCursorGroupSize; i++ )
			{
				iAuxCursorSize = m_arrAuxCursorGroup.GetAt(i)->GetCursorInfoSize();
				if ( m_iSelectAuxCursorIndex >= 0 && m_iSelectAuxCursorIndex < iAuxCursorSize )
				{
					iSelectAuxCursorGroupIndex = m_iSelectAuxCursorGroupIndex;
					iSelectAuxCursorIndex = m_iSelectAuxCursorIndex;
					return true;
				}
			}
		}
	}
	return false;
}

//! Added by LHW [2008/8/5]
bool CGraph2DWnd::IsAuxCursorSelected(int &iSelectAuxCursorGroupIndex, int &iSelectAuxCursorIndex)
{
	iSelectAuxCursorGroupIndex = -1;
	iSelectAuxCursorIndex = -1;

	int iAuxCursorGroupSize = (int)(m_arrAuxCursorGroup.GetSize());
	if ( iAuxCursorGroupSize > 0 )
	{
		if ( m_iSelectedAuxCursorGroupIndex >= 0 && m_iSelectedAuxCursorGroupIndex < iAuxCursorGroupSize )
		{
			int iAuxCursorSize = 0;
			for ( int i = 0; i < iAuxCursorGroupSize; i++ )
			{
				iAuxCursorSize = m_arrAuxCursorGroup.GetAt(i)->GetCursorInfoSize();
				if ( m_iSelectedAuxCursorIndex >= 0 && m_iSelectedAuxCursorIndex < iAuxCursorSize )
				{
					iSelectAuxCursorGroupIndex = m_iSelectedAuxCursorGroupIndex;
					iSelectAuxCursorIndex = m_iSelectedAuxCursorIndex;
					return true;
				}
			}
		}
	}
	return false;
}

//! Added by LHW [2008/3/31]
//! Modify by LHW [2008/4/11] : strGraph2D_Aux_Cursor_Extend 추가에 따른 수정
bool CGraph2DWnd::SetAuxCursorInfo(int iAuxCursorGroupIndex, int iAuxCursorIndex, strGraph2D_Aux_Cursor strAuxCursorInfo)
{
	int iAuxCursorGroupSize = GetCurrentAuxCursorGroupSize();
	if ( iAuxCursorGroupIndex < 0 || iAuxCursorGroupIndex >= iAuxCursorGroupSize )
	{
		return false;
	}

	int iAuxCursorSize = GetCurrentAuxCursorSize(iAuxCursorGroupIndex);
	if ( iAuxCursorSize <= 0 )
	{
		return false;
	}
	if ( iAuxCursorIndex < 0 || iAuxCursorIndex >= iAuxCursorSize )
	{
		return false;
	}
	
	strGraph2D_Aux_Cursor_Extend strAuxCursor;
	strAuxCursor = m_arrAuxCursorGroup.GetAt(iAuxCursorGroupIndex)->m_arrCursorInfo.GetAt(iAuxCursorIndex);
	strAuxCursor.strAuxCursorUser = strAuxCursorInfo;
	m_arrAuxCursorGroup.GetAt(iAuxCursorGroupIndex)->m_arrCursorInfo.SetAt(iAuxCursorIndex, strAuxCursor);

	return true;
}

//! Added by LHW [2008/3/31]
//! Modify by LHW [2008/4/11] : strGraph2D_Aux_Cursor_Extend 추가에 따른 수정
bool CGraph2DWnd::GetAuxCursorInfo(int iAuxCursorGroupIndex, int iAuxCursorIndex, strGraph2D_Aux_Cursor &strAuxCursorInfo)
{
	int iAuxCursorGroupSize = GetCurrentAuxCursorGroupSize();
	if ( iAuxCursorGroupIndex < 0 || iAuxCursorGroupIndex >= iAuxCursorGroupSize )
	{
		return false;
	}

	int iAuxCursorSize = GetCurrentAuxCursorSize(iAuxCursorGroupIndex);
	if ( iAuxCursorIndex < 0 || iAuxCursorIndex >= iAuxCursorSize )
	{
		return false;
	}

	strGraph2D_Aux_Cursor_Extend strAuxCursor;
	strAuxCursor = m_arrAuxCursorGroup.GetAt(iAuxCursorGroupIndex)->m_arrCursorInfo.GetAt(iAuxCursorIndex);
	strAuxCursorInfo = strAuxCursor.strAuxCursorUser;

	return true;
}

//! Added by LHW [2008/5/31]
//! Modify by LHW [2008/6/3]
bool CGraph2DWnd::GetAuxCursorValue(int iAuxCursorGroupIndex, int iAuxCursorIndex, bool &bValid, int &iDataIndex, double &dbValueX, double &dbValueY)
{
	bValid = false;

	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize <= 0 )
	{
		return false;
	}
	int iAuxCursorGroupSize = GetCurrentAuxCursorGroupSize();
	if ( iAuxCursorGroupIndex < 0 || iAuxCursorGroupIndex >= iAuxCursorGroupSize )
	{
		return false;
	}

	int iAuxCursorSize = GetCurrentAuxCursorSize(iAuxCursorGroupIndex);
	if ( iAuxCursorIndex < 0 || iAuxCursorIndex >= iAuxCursorSize )
	{
		return false;
	}

	strGraph2D_Aux_Cursor_Extend strAuxCursor;
	strAuxCursor = m_arrAuxCursorGroup.GetAt(iAuxCursorGroupIndex)->m_arrCursorInfo.GetAt(iAuxCursorIndex);

	bValid = strAuxCursor.bValid;
	iDataIndex = strAuxCursor.iRealDataIndex;
	dbValueX = strAuxCursor.dbXData;
	dbValueY = strAuxCursor.dbYData;
	
	return true;
}

//! Added by LHW [2008/3/31]
bool CGraph2DWnd::SetAuxCursorGroupInfo(int iAuxCursorGroupIndex, strGraph2D_Aux_CursorGroup strAuxCursorGroupInfo)
{
	int iAuxCursorGroupSize = GetCurrentAuxCursorGroupSize();
	if ( iAuxCursorGroupIndex < 0 || iAuxCursorGroupIndex >= iAuxCursorGroupSize )
	{
		return false;
	}

	m_arrAuxCursorGroup.GetAt(iAuxCursorGroupIndex)->m_strGroupInfo = strAuxCursorGroupInfo;

	return true;
}

//! Added by LHW [2008/3/31]
bool CGraph2DWnd::GetAuxCursorGroupInfo(int iAuxCursorGroupIndex, strGraph2D_Aux_CursorGroup &strAuxCursorGroupInfo)
{
	int iAuxCursorGroupSize = GetCurrentAuxCursorGroupSize();
	if ( iAuxCursorGroupIndex < 0 || iAuxCursorGroupIndex >= iAuxCursorGroupSize )
	{
		return false;
	}

	strAuxCursorGroupInfo = m_arrAuxCursorGroup.GetAt(iAuxCursorGroupIndex)->m_strGroupInfo;

	return true;
}

//! Added by LHW [2008/7/27]
bool CGraph2DWnd::ChangeAuxCursorGroupOverlapIndex(int iAuxCursorGroupIndex, int iOverlapIndex)
{
	int iGraphSize = GetPlotBufferSize();
	if ( iOverlapIndex < 0 || iOverlapIndex >= iGraphSize )
	{
		return false;
	}
	int iAuxCursorGroupSize = GetCurrentAuxCursorGroupSize();
	if ( iAuxCursorGroupIndex < 0 || iAuxCursorGroupIndex >= iAuxCursorGroupSize )
	{
		return false;
	}

	int iAuxCursorSize = GetCurrentAuxCursorSize(iAuxCursorGroupIndex);
	if ( iAuxCursorSize <= 0 )
	{
		return true;
	}

	strGraph2D_Aux_Cursor_Extend strAuxCursor;
	for ( int i = 0; i < iAuxCursorSize; i++ )
	{
		strAuxCursor = m_arrAuxCursorGroup.GetAt(iAuxCursorGroupIndex)->m_arrCursorInfo.GetAt(i);
		strAuxCursor.strAuxCursorUser.iOverlapIndex = iOverlapIndex;
		m_arrAuxCursorGroup.GetAt(iAuxCursorGroupIndex)->m_arrCursorInfo.SetAt(i, strAuxCursor);
	}

	return true;
}

//! Added by LHW [2008/3/31]
//! Modify by LHW [2008/4/11] : strGraph2D_Aux_Cursor_Extend 추가에 따른 수정
int CGraph2DWnd::AddAuxCursor(strGraph2D_Aux_Cursor strAuxCursorInfo, int iAuxCursorGroupIndex)
{
	int iAuxCursorGroupSize = GetCurrentAuxCursorGroupSize();
	if ( iAuxCursorGroupIndex < -1 || iAuxCursorGroupIndex >= iAuxCursorGroupSize )
	{
		return -1;
	}

	int iElementIndex = 0;

	strGraph2D_Aux_Cursor_Extend strAuxCursor;
	strAuxCursor.InitInfo();

	if ( iAuxCursorGroupIndex == -1 )
	{
		iElementIndex = GetAuxCursorGroupPossibleElementIndex();
		if ( iElementIndex < 0 )
		{
			return -1;
		}

		CGraph2D_Aux_CursorGroup *pAuxCursorGroup = NULL;
		pAuxCursorGroup = new CGraph2D_Aux_CursorGroup;
		if ( pAuxCursorGroup == NULL )
		{
			return -1;
		}
		pAuxCursorGroup->m_arrCursorInfo.RemoveAll();
		pAuxCursorGroup->m_arrCursorInfo.FreeExtra();
		pAuxCursorGroup->m_iElementIndex = iElementIndex;
		
		strAuxCursor.iElementIndex = 0;
		strAuxCursor.strAuxCursorUser = strAuxCursorInfo;
		pAuxCursorGroup->m_arrCursorInfo.Add(strAuxCursor);

		m_arrAuxCursorGroup.Add(pAuxCursorGroup);
		return (GetCurrentAuxCursorGroupSize() - 1);
	}
	
	iElementIndex = m_arrAuxCursorGroup.GetAt(iAuxCursorGroupIndex)->GetAuxCursorPossibleElementIndex();
	if ( iElementIndex < 0 )
	{
		return -1;
	}
	strAuxCursor.iElementIndex = iElementIndex;
	strAuxCursor.strAuxCursorUser = strAuxCursorInfo;
	m_arrAuxCursorGroup.GetAt(iAuxCursorGroupIndex)->m_arrCursorInfo.Add(strAuxCursor);
	return iAuxCursorGroupIndex;
}

//! Added by LHW [2008/3/31]
bool CGraph2DWnd::RemoveOneAuxCursor(int iAuxCursorGroupIndex, int iAuxCursorIndex)
{
	int iAuxCursorGroupSize = GetCurrentAuxCursorGroupSize();
	if ( iAuxCursorGroupIndex < 0 || iAuxCursorGroupIndex >= iAuxCursorGroupSize )
	{
		return false;
	}

	int iAuxCursorSize = GetCurrentAuxCursorSize(iAuxCursorGroupIndex);
	if ( iAuxCursorIndex < 0 || iAuxCursorIndex >= iAuxCursorSize )
	{
		return false;
	}

	m_arrAuxCursorGroup.GetAt(iAuxCursorGroupIndex)->m_arrCursorInfo.RemoveAt(iAuxCursorIndex);

	return true;
}

//! Added by LHW [2008/3/31]
bool CGraph2DWnd::RemoveOneAuxCursorGroup(int iAuxCursorGroupIndex)
{
	int iAuxCursorGroupSize = GetCurrentAuxCursorGroupSize();
	if ( iAuxCursorGroupIndex < 0 || iAuxCursorGroupIndex >= iAuxCursorGroupSize )
	{
		return false;
	}

	m_arrAuxCursorGroup.GetAt(iAuxCursorGroupIndex)->ReleaseResource();
	m_arrAuxCursorGroup.GetAt(iAuxCursorGroupIndex)->m_arrCursorInfo.RemoveAll();
	m_arrAuxCursorGroup.GetAt(iAuxCursorGroupIndex)->m_arrCursorInfo.FreeExtra();

	delete m_arrAuxCursorGroup.GetAt(iAuxCursorGroupIndex);
	m_arrAuxCursorGroup.RemoveAt(iAuxCursorGroupIndex);

	if ( GetCurrentAuxCursorGroupSize() <= 0 )
	{
		m_arrAuxCursorGroup.RemoveAll();
		m_arrAuxCursorGroup.FreeExtra();
	}

	return true;
}

//! Added by LHW [2008/3/31]
void CGraph2DWnd::RemoveAllAuxCursor()
{
	int iSize = 0;

	while(1)
	{
		iSize = (int)(m_arrAuxCursorGroup.GetSize());
		if ( iSize <= 0 )
		{
			break;
		}

		m_arrAuxCursorGroup.GetAt(0)->ReleaseResource();
		m_arrAuxCursorGroup.GetAt(0)->m_arrCursorInfo.RemoveAll();
		m_arrAuxCursorGroup.GetAt(0)->m_arrCursorInfo.FreeExtra();

		delete m_arrAuxCursorGroup.GetAt(0);
		m_arrAuxCursorGroup.RemoveAt(0);
	}

	m_arrAuxCursorGroup.RemoveAll();
	m_arrAuxCursorGroup.FreeExtra();
}

//! Added by LHW [2008/4/1]
//! Modify by LHW [2008/4/11] : strGraph2D_Aux_Cursor_Extend 추가에 따른 수정
//! Modify by LHW [2008/5/29] : 보조 커서 값이 데이터 최소, 최대값 밖일 경우의 에러 처리 추가
//! Modify by LHW [2008/5/31] : 보조 커서 값, index 설정 부분 추가
//! Modify by LHW [2008/6/3] : 보조 커서 값을 찾을 수 없을 때의 오류 처리부분 수정
//! Modify by LHW [2008/8/4] : crSelectX, crSelectY 설정 부분 추가
//! Modify by LHW [2008/8/19] : 검색 영역 설정 부분 수정
//! Modify by LHW [2008/8/20] : 검색 구간 설정 방법 수정
//! Modify by LHW [2008/12/29] : 잘못된 입력값 처리 부분 추가
//! Modify by LHW [2009/6/4] : 마우스를 움직일 때의 커서 동작의 오차를 줄이는 작업을 진행
bool CGraph2DWnd::CalcAuxCursor()
{
	int iAuxCursorGroupSize = GetCurrentAuxCursorGroupSize();
	if ( iAuxCursorGroupSize <= 0 )
	{
		return false;
	}
	if ( m_DataRect.Width() <= 0 || m_DataRect.Height() <= 0 )
	{
		return false;
	}
	if ( m_RealGraphRect.Width() <= 0 || m_RealGraphRect.Height() <= 0 )
	{
		return false;
	}
	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize <= 0 )
	{
		return false;
	}
	int iCursorSize = GetCurrentCursorSize();

	int i = 0, j = 0, k = 0, iAuxCursorSize = 0;
	int iXPt = 0, iXPt1 = 0, iXPt2 = 0, iYPt = 0, iYPt1 = 0, iYPt2 = 0;
	strGraph2D_Aux_Cursor_Extend strAuxCursor;
	strYRangeMapper strYMapper;
	strGraph2DCursorInfo strMainCursor;

	bool bLarge = false, bExact = false;
	int iCursorIndex = 0, iOverlapIndex = 0, iCursorDataIndex = -1, iCursorDataIndexTemp = -1;
	int iCompress = 0, iDrawDataSize = 0, iVisualDataSize = 0, iCursorIndexTemp = 0;
	double dbXData = 0., dbYData = 0., dbXData1 = 0., dbYData1 = 0., dbXData2 = 0., dbYData2 = 0.;
	double dbTempXDataMax = 0., dbTempXDataMin = 0.;
	double dbIncrement = 0., dbXDataTemp = 0., dbXIntervalTemp = 0., dbXMinTemp = 0.;
	int iSearchStart = 0, iSearchEnd = 0;
	int iCursorSelIndex1 = -1, iCursorSelIndex2 = -1, iCursorSelIndex3 = -1, iTempXPos = 0;

	for ( i = 0; i < iAuxCursorGroupSize; i++ )
	{
		iAuxCursorSize = GetCurrentAuxCursorSize(i);
		if ( iAuxCursorSize <= 0 )
		{
			continue;
		}

		for ( j = 0; j < iAuxCursorSize; j++ )
		{
			strAuxCursor = m_arrAuxCursorGroup.GetAt(i)->m_arrCursorInfo.GetAt(j);

			strAuxCursor.bValid = false;

			iOverlapIndex = strAuxCursor.strAuxCursorUser.iOverlapIndex;
			if ( iOverlapIndex < 0 || iOverlapIndex >= iGraphSize )
			{
				m_arrAuxCursorGroup.GetAt(i)->m_arrCursorInfo.SetAt(j, strAuxCursor);
				continue;
			}
			iDrawDataSize = m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize();
			if ( iDrawDataSize <= 1 )
			{
				m_arrAuxCursorGroup.GetAt(i)->m_arrCursorInfo.SetAt(j, strAuxCursor);
				continue;
			}
			iVisualDataSize = m_arrPlotData.GetAt(iOverlapIndex)->m_iVisualDataSize;

			strYMapper = m_arrYMapper.GetAt(iOverlapIndex);

			if ( strAuxCursor.strAuxCursorUser.eCursorType == E_GRAPH2D_AUX_CURSOR_FIXED_INDEX )
			{
				iCursorDataIndex = strAuxCursor.strAuxCursorUser.iDataIndex;
				if ( iCursorDataIndex < 0 || iCursorDataIndex >= iDrawDataSize )
				{
					m_arrAuxCursorGroup.GetAt(i)->m_arrCursorInfo.SetAt(j, strAuxCursor);
					continue;
				}

				dbXData = m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(iCursorDataIndex);
				dbYData = m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(iCursorDataIndex);

				iXPt = m_XMapper.CalcXDataToPt(dbXData);	//! 보조 커서의 X 위치 결정
				iYPt = strYMapper.CalcYDataToPt(dbYData);	//! 보조 커서의 Y 위치 결정

				strAuxCursor.strAuxCursorUser.dbXData = dbXData;
				strAuxCursor.iXPos = iXPt;
				strAuxCursor.iYPos = iYPt;

				strAuxCursor.crSelectX.left = iXPt - m_iCursorMargin;
				strAuxCursor.crSelectX.right = iXPt + m_iCursorMargin;
				strAuxCursor.crSelectX.top = m_DataRect.top;
				strAuxCursor.crSelectX.bottom = m_DataRect.bottom;
				strAuxCursor.crSelectY.left = m_DataRect.left;
				strAuxCursor.crSelectY.right = m_DataRect.right;
				strAuxCursor.crSelectY.top = iYPt - m_iCursorMargin;
				strAuxCursor.crSelectY.bottom = iYPt + m_iCursorMargin;

				strAuxCursor.iRealDataIndex = iCursorDataIndex;
				strAuxCursor.dbXData = dbXData;
				strAuxCursor.dbYData = dbYData;
			}			
			else
			{
				if ( strAuxCursor.strAuxCursorUser.eCursorType == E_GRAPH2D_AUX_CURSOR_VARIABLE )
				{
					iCursorIndex = strAuxCursor.strAuxCursorUser.iCursorIndex;
					if ( iCursorIndex < 0 || iCursorIndex >= iCursorSize )
					{
						m_arrAuxCursorGroup.GetAt(i)->m_arrCursorInfo.SetAt(j, strAuxCursor);
						continue;
					}
					strMainCursor = m_arrCursor.GetAt(iCursorIndex);
					if ( strMainCursor.iDataIndex < 0 || strMainCursor.iDataIndex >= iDrawDataSize )
					{
						m_arrAuxCursorGroup.GetAt(i)->m_arrCursorInfo.SetAt(j, strAuxCursor);
						continue;
					}
					if ( strMainCursor.iSelectOverlapIndex < 0 || strMainCursor.iSelectOverlapIndex >= iGraphSize )
					{
						m_arrAuxCursorGroup.GetAt(i)->m_arrCursorInfo.SetAt(j, strAuxCursor);
						continue;
					}

					dbXData = strMainCursor.dbXData + strAuxCursor.strAuxCursorUser.dbXData;
				}
				else
				{
					dbXData = strAuxCursor.strAuxCursorUser.dbXData;
				}

				/*if ( _isnan(dbXData) )
				{
					m_arrAuxCursorGroup.GetAt(i)->m_arrCursorInfo.SetAt(j, strAuxCursor);
					continue;
				}*/
				if ( !_finite(dbXData) )
				{
					m_arrAuxCursorGroup.GetAt(i)->m_arrCursorInfo.SetAt(j, strAuxCursor);
					continue;
				}

				iXPt = m_XMapper.CalcXDataToPt(dbXData);	//! 보조 커서의 X 위치 결정

				//! 검색 구간 설정
				switch(strAuxCursor.strAuxCursorUser.eSearchMode)
				{
				case E_GRAPH2D_AUX_CURSOR_SEARCH_X_RANGE:
					{
						dbTempXDataMax = m_arrPlotData.GetAt(iOverlapIndex)->m_dbMaxX;
						dbTempXDataMin = m_arrPlotData.GetAt(iOverlapIndex)->m_dbMinX;

						//iCompress = (int)((dbTempXDataMax - dbTempXDataMin) / (double)(m_RealGraphRect.Width())) + 100;
						iCompress = (int)( ((double)iVisualDataSize) / ((double)(m_RealGraphRect.Width())) );
						iCompress += strAuxCursor.strAuxCursorUser.iSearchMargin;
						//! X축 방향의 최대값과 실제 데이터 사이의 간격을 계산
						dbIncrement = (dbTempXDataMax - dbTempXDataMin) / (double)(iDrawDataSize - 1);

						//! X 방향값을 간격으로 나누어 실제 데이터에서의 예상 index값을 구함
						iCursorIndexTemp = (int)((dbXData - dbTempXDataMin) / dbIncrement);//! 예상 index값
						//! 예상 index값 주위의 index 구간을 정함
						iSearchStart = iCursorIndexTemp - iCompress;					
						iSearchEnd = iCursorIndexTemp + iCompress;
					}
					break;
				case E_GRAPH2D_AUX_CURSOR_SEARCH_X_VISUAL:
					{
						iSearchStart = m_arrPlotData.GetAt(iOverlapIndex)->m_iVisualDataStartIndex;
						iSearchEnd = m_arrPlotData.GetAt(iOverlapIndex)->m_iVisualDataEndIndex + 1;
					}
					break;
				case E_GRAPH2D_AUX_CURSOR_SEARCH_ALL:
					{
						iSearchStart = 0;
						iSearchEnd = iDrawDataSize - 1;
					}
					break;
				}

				if ( iSearchStart < 0 )
				{
					iSearchStart = 0;
				}
				if ( iSearchStart >= iDrawDataSize )
				{
					iSearchStart = iDrawDataSize - 1;
				}
				if ( iSearchEnd < 0 )
				{
					iSearchEnd = 0;
				}
				if ( iSearchEnd >= iDrawDataSize )
				{
					iSearchEnd = iDrawDataSize - 1;
				}

				if ( iSearchStart == iSearchEnd )
				{
					strAuxCursor.dbXData = dbXData;
					m_arrAuxCursorGroup.GetAt(i)->m_arrCursorInfo.SetAt(j, strAuxCursor);
					continue;
				}

				bLarge = false, bExact = false;
				iCursorSelIndex1 = -1, iCursorSelIndex2 = -1, iCursorSelIndex3 = -1;
				dbXMinTemp = DBL_MAX;

				for ( k = iSearchStart; k <= iSearchEnd; k++ )
				{
					dbXDataTemp = m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(k);
					iTempXPos = m_XMapper.CalcXDataToPt(dbXDataTemp);

					//! 가장 가까운 index를 찾아야 함
					dbXIntervalTemp = fabs(dbXDataTemp - dbXData);
					if ( dbXMinTemp > dbXIntervalTemp )
					{
						dbXMinTemp = dbXIntervalTemp;
						iCursorSelIndex1 = k;
						bExact = true;
					}

					//! 보조 커서보다 한 단계 작고, 한 단계 큰 값의 구간을 구함
					if ( iXPt < iTempXPos )
					{
						if ( bLarge == false )
						{
							iCursorSelIndex3 = k;
							bLarge = true;
						}				
					}
					if ( iXPt > iTempXPos )
					{
						iCursorSelIndex2 = k;
					}					
				}

				if ( iCursorSelIndex1 >= 0 )
				{
					dbXDataTemp = m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(iCursorSelIndex1);
					iTempXPos = m_XMapper.CalcXDataToPt(dbXDataTemp);
					if ( iXPt == iTempXPos )
					{
						bExact = true;
					}
				}

				//! Y 좌표 설정
				if ( bExact == true )
				{
					dbYData = m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(iCursorSelIndex1);
					iYPt = strYMapper.CalcYDataToPt(dbYData);	//! 보조 커서의 Y 위치 결정

					strAuxCursor.iRealDataIndex = iCursorSelIndex1;
					strAuxCursor.dbXData = dbXData;
					strAuxCursor.dbYData = dbYData;
				}
				else
				{
					if ( iCursorSelIndex2 == -1 )
					{
						dbXData1 = m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(0);						
						dbYData1 = m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(0);
						iCursorSelIndex2 = 0;
					}
					else
					{
						dbXData1 = m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(iCursorSelIndex2);						
						dbYData1 = m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(iCursorSelIndex2);
					}

					iXPt1 = m_XMapper.CalcXDataToPt(dbXData1);
					iYPt1 = strYMapper.CalcYDataToPt(dbYData1);

					if ( iCursorSelIndex3 == -1 )
					{
						dbXData2 = m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(iDrawDataSize - 1);						
						dbYData2 = m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(iDrawDataSize - 1);
						iCursorSelIndex3 = iDrawDataSize - 1;
					}
					else
					{
						dbXData2 = m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(iCursorSelIndex3);						
						dbYData2 = m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(iCursorSelIndex3);
					}

					iXPt2 = m_XMapper.CalcXDataToPt(dbXData2);
					iYPt2 = strYMapper.CalcYDataToPt(dbYData2);

					iYPt = CalcLinearInterpolate(iXPt1, iYPt1, iXPt2, iYPt2, iXPt);	//! 보조 커서의 Y 위치 결정

					if ( fabs(dbXData - dbXData1) > fabs(dbXData - dbXData2) )
					{
						strAuxCursor.iRealDataIndex = iCursorSelIndex3;
						strAuxCursor.dbXData = dbXData2;
						strAuxCursor.dbYData = dbYData2;
					}
					else
					{
						strAuxCursor.iRealDataIndex = iCursorSelIndex2;
						strAuxCursor.dbXData = dbXData1;
						strAuxCursor.dbYData = dbYData1;
					}
				}

				strAuxCursor.iXPos = iXPt;
				strAuxCursor.iYPos = iYPt;

				strAuxCursor.crSelectX.left = iXPt - m_iCursorMargin;
				strAuxCursor.crSelectX.right = iXPt + m_iCursorMargin;
				strAuxCursor.crSelectX.top = m_DataRect.top;
				strAuxCursor.crSelectX.bottom = m_DataRect.bottom;
				strAuxCursor.crSelectY.left = m_DataRect.left;
				strAuxCursor.crSelectY.right = m_DataRect.right;
				strAuxCursor.crSelectY.top = iYPt - m_iCursorMargin;
				strAuxCursor.crSelectY.bottom = iYPt + m_iCursorMargin;
			}

			strAuxCursor.bValid = true;

			m_arrAuxCursorGroup.GetAt(i)->m_arrCursorInfo.SetAt(j, strAuxCursor);			
		}
	}

	return true;
}

//! Added by LHW [2008/8/5]
//! Modify by LHW [2008/8/9] : 영역 index 관련 오류 수정
//! Modify by LHW [2008/8/19] : 검색 영역 설정 부분 수정, Main 커서의 Boundary 체크 부분 추가
//! Modify by LHW [2008/8/20] : 검색 영역 설정 부분 수정
//! Modify by LHW [2009/6/4] : 마우스를 움직일 때의 커서 동작의 오차를 줄이는 작업을 진행
bool CGraph2DWnd::CalcAuxCursorPos(int iXPos, int iYPos, int iAuxCursorGroupIndex, int iAuxCursorIndex)
{
	if ( m_hMsgHandle == NULL )
	{
		return false;
	}
	if ( m_DataRect.Width() <= 0 || m_DataRect.Height() <= 0 )
	{
		return false;
	}
	if ( m_RealGraphRect.Width() <= 0 || m_RealGraphRect.Height() <= 0 )
	{
		return false;
	}

	int iGraphSize = GetPlotBufferSize();
	if ( iGraphSize <= 0 )
	{
		return false;
	}

	int iAuxCursorGroupSize = (int)(m_arrAuxCursorGroup.GetSize());
	if ( iAuxCursorGroupIndex < 0 || iAuxCursorGroupIndex >= iAuxCursorGroupSize )
	{
		return false;
	}
	if ( m_arrAuxCursorGroup.GetAt(iAuxCursorGroupIndex)->m_strGroupInfo.bShow == false )
	{
		return false;
	}

	int iAuxCursorSize = (int)(m_arrAuxCursorGroup.GetAt(iAuxCursorGroupIndex)->m_arrCursorInfo.GetSize());
	if ( iAuxCursorIndex < 0 || iAuxCursorIndex >= iAuxCursorSize )
	{
		return false;
	}

	strGraph2D_Aux_Cursor_Extend strAuxCursor;
	strAuxCursor = m_arrAuxCursorGroup.GetAt(iAuxCursorGroupIndex)->m_arrCursorInfo.GetAt(iAuxCursorIndex);

	if ( strAuxCursor.strAuxCursorUser.bMouseEvent == false || strAuxCursor.strAuxCursorUser.bIndependency == false )
	{
		return false;
	}

	int iOverlapIndex = strAuxCursor.strAuxCursorUser.iOverlapIndex;
	if ( iOverlapIndex < 0 || iOverlapIndex >= iGraphSize )
	{
		return false;
	}
	int iDrawDataSize = m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize();
	if ( iDrawDataSize <= 0 )
	{
		return false;
	}
	int iVisualDataSize = m_arrPlotData.GetAt(iOverlapIndex)->m_iVisualDataSize;

	int iCursorSize = (int)(m_arrCursor.GetSize());
	int iMainCursorIndex = strAuxCursor.strAuxCursorUser.iCursorIndex;
	if ( iMainCursorIndex < 0 || iMainCursorIndex >= iCursorSize )
	{
		return false;
	}
	strGraph2DCursorInfo strCursorInfo = m_arrCursor.GetAt(iMainCursorIndex);

	switch(strAuxCursor.strAuxCursorUser.eBoundaryMode)
	{
	case E_GRAPH2D_AUX_CURSOR_BOUNDARY_CURSOR_LEFT:
		{
			if ( iXPos > strCursorInfo.iXPos )
			{
				iXPos = strCursorInfo.iXPos;
			}
		}
		break;
	case E_GRAPH2D_AUX_CURSOR_BOUNDARY_CURSOR_RIGHT:
		{
			if ( iXPos < strCursorInfo.iXPos )
			{
				iXPos = strCursorInfo.iXPos;
			}
		}
		break;
	}
    
	m_bCalcAuxCursor = true;

	int i = 0, j = 0;
	int iCursorDataIndex = -1, iCursorDataIndexTemp = -1;
	int iCompress = 0, iOverlapTempIndex = 0;
	double dbXData = 0., dbYData = 0., dbIncrement = 0.;
	double dbTempXDataMax = 0., dbTempXDataMin = 0.;
	int iTempXPos = 0, iTempYPos = 0, iCursorIndexTemp = 0;
	int iDistanceTempX = 0, iDistanceMinX = INT_MAX, iDistanceTempMinX = INT_MAX;
	int iDistanceTempY = 0, iDistanceMinY = INT_MAX, iDistanceTempMinY = INT_MAX;	
	bool bShowDataExist = false;
	int iSearchStart = 0, iSearchEnd = 0;
	strYRangeMapper strYMapper;
	int iSearchRangeForAddCursor = 0;

	//! 데이터를 검색할 구간 index를 설정하고 가장 가까운 데이터 index를 찾음
	if ( strAuxCursor.strAuxCursorUser.bCursorOverlapAllSearch == false )
	{
		switch(strAuxCursor.strAuxCursorUser.eMouseSearchMode)
		{
		case E_GRAPH2D_AUX_CURSOR_SEARCH_X_RANGE:
			{
				if ( iVisualDataSize == 1 )
				{
					iSearchStart = m_arrPlotData.GetAt(iOverlapIndex)->m_iVisualDataStartIndex;
					iSearchEnd = m_arrPlotData.GetAt(iOverlapIndex)->m_iVisualDataEndIndex + 1;
				}
				else
				{
					dbTempXDataMax = m_arrPlotData.GetAt(iOverlapIndex)->m_dbMaxX;
					dbTempXDataMin = m_arrPlotData.GetAt(iOverlapIndex)->m_dbMinX;

					//iCompress = (int)((dbTempXDataMax - dbTempXDataMin) / (double)(m_RealGraphRect.Width()));
					iCompress = (int)( ((double)iVisualDataSize) / ((double)(m_RealGraphRect.Width())) );
					iCompress += strAuxCursor.strAuxCursorUser.iSearchMargin;					
					//! X축 방향의 최대값과 실제 데이터 사이의 간격을 계산
					dbIncrement = (dbTempXDataMax - dbTempXDataMin) / (double)(iDrawDataSize - 1);

					//! 함수의 인자로 주어진 X 좌표에 해당하는 X 방향값을 구한 뒤,
					//! 이를 간격으로 나누어 실제 데이터에서의 예상 index값을 구함
					dbXData = m_XMapper.CalcPtToXData(iXPos);
					if ( dbXData < m_XMapper.m_dbXDataMin )
					{
						dbXData = m_XMapper.m_dbXDataMin;
					}
					if ( dbXData > m_XMapper.m_dbXDataMax )
					{
						dbXData = m_XMapper.m_dbXDataMax;
					}
					iCursorIndexTemp = (int)((dbXData - dbTempXDataMin) / dbIncrement);//! 예상 index값
					//! 예상 index값 주위의 index 구간을 정함
					iSearchStart = iCursorIndexTemp - iCompress;					
					iSearchEnd = iCursorIndexTemp + iCompress;					
				}
			}
			break;
		case E_GRAPH2D_AUX_CURSOR_SEARCH_X_VISUAL:
			{
				iSearchStart = m_arrPlotData.GetAt(iOverlapIndex)->m_iVisualDataStartIndex;
				iSearchEnd = m_arrPlotData.GetAt(iOverlapIndex)->m_iVisualDataEndIndex + 1;
			}
			break;
		case E_GRAPH2D_AUX_CURSOR_SEARCH_ALL:
			{
				iSearchStart = 0;
				iSearchEnd = iDrawDataSize - 1;
			}
			break;
		}

		if ( iSearchStart < 0 )
		{
			iSearchStart = 0;
		}
		if ( iSearchStart >= iDrawDataSize )
		{
			iSearchStart = iDrawDataSize - 1;
		}
		if ( iSearchEnd < 0 )
		{
			iSearchEnd = 0;
		}
		if ( iSearchEnd >= iDrawDataSize )
		{
			iSearchEnd = iDrawDataSize - 1;
		}

		strYMapper = m_arrYMapper.GetAt(iOverlapIndex);

		for ( i = iSearchStart; i <= iSearchEnd; i++ )
		{
			dbXData = m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(i);
			dbYData = m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(i);

			if (dbXData >= m_XMapper.m_dbXDataMin && dbXData <= m_XMapper.m_dbXDataMax)
			{
				bShowDataExist = true;

				iTempXPos = m_XMapper.CalcXDataToPt(dbXData);
				iTempYPos = strYMapper.CalcYDataToPt(dbYData);

				iDistanceTempX = (iTempXPos - iXPos) * (iTempXPos - iXPos);
				iDistanceTempY = (iTempYPos - iYPos) * (iTempYPos - iYPos);
				if ( iDistanceTempX < iDistanceMinX )
				{
					iDistanceMinX = iDistanceTempX;
					iDistanceMinY = iDistanceTempY;
					iCursorDataIndex = i;					
				}
				else if ( iDistanceTempX == iDistanceMinX )
				{					
					if ( iDistanceTempY < iDistanceMinY )
					{
						iDistanceMinX = iDistanceTempX;
						iDistanceMinY = iDistanceTempY;
						iCursorDataIndex = i;
					}
				}
			}
		}
	}
	else
	{
		for ( i = 0; i < iGraphSize; i++ )
		{
			iDrawDataSize = m_arrPlotData.GetAt(i)->GetPointSize();
			iVisualDataSize = m_arrPlotData.GetAt(i)->m_iVisualDataSize;		
			if ( iDrawDataSize <= 0 || iVisualDataSize <= 0 )
			{
				continue;
			}

			switch(strAuxCursor.strAuxCursorUser.eMouseSearchMode)
			{
			case E_GRAPH2D_AUX_CURSOR_SEARCH_X_RANGE:
				{
					if ( iVisualDataSize == 1 )
					{
						iSearchStart = m_arrPlotData.GetAt(i)->m_iVisualDataStartIndex;
						iSearchEnd = m_arrPlotData.GetAt(i)->m_iVisualDataEndIndex + 1;
					}
					else
					{
						dbTempXDataMax = m_arrPlotData.GetAt(i)->m_dbMaxX;
						dbTempXDataMin = m_arrPlotData.GetAt(i)->m_dbMinX;

						//iCompress = (int)((dbTempXDataMax - dbTempXDataMin) / (double)(m_RealGraphRect.Width()));
						iCompress = (int)( ((double)iVisualDataSize) / ((double)(m_RealGraphRect.Width())) );
						iCompress += strAuxCursor.strAuxCursorUser.iSearchMargin;						
						//! X축 방향의 최대값과 실제 데이터 사이의 간격을 계산
						dbIncrement = (dbTempXDataMax - dbTempXDataMin) / (double)(iDrawDataSize - 1);

						//! 함수의 인자로 주어진 X 좌표에 해당하는 X 방향값을 구한 뒤,
						//! 이를 간격으로 나누어 실제 데이터에서의 예상 index값을 구함
						dbXData = m_XMapper.CalcPtToXData(iXPos);
						if ( dbXData < m_XMapper.m_dbXDataMin )
						{
							dbXData = m_XMapper.m_dbXDataMin;
						}
						if ( dbXData > m_XMapper.m_dbXDataMax )
						{
							dbXData = m_XMapper.m_dbXDataMax;
						}
						iCursorIndexTemp = (int)((dbXData - dbTempXDataMin) / dbIncrement);//! 예상 index값
						//! 예상 index값 주위의 index 구간을 정함
						iSearchStart = iCursorIndexTemp - iCompress;						
						iSearchEnd = iCursorIndexTemp + iCompress;						
					}
				}
				break;
			case E_GRAPH2D_AUX_CURSOR_SEARCH_X_VISUAL:
				{
					iSearchStart = m_arrPlotData.GetAt(i)->m_iVisualDataStartIndex;
					iSearchEnd = m_arrPlotData.GetAt(i)->m_iVisualDataEndIndex + 1;
				}
				break;
			case E_GRAPH2D_AUX_CURSOR_SEARCH_ALL:
				{
					iSearchStart = 0;
					iSearchEnd = iDrawDataSize - 1;
				}
				break;
			}

			if ( iSearchStart < 0 )
			{
				iSearchStart = 0;
			}
			if ( iSearchStart >= iDrawDataSize )
			{
				iSearchStart = iDrawDataSize - 1;
			}
			if ( iSearchEnd < 0 )
			{
				iSearchEnd = 0;
			}
			if ( iSearchEnd >= iDrawDataSize )
			{
				iSearchEnd = iDrawDataSize - 1;
			}

			strYMapper = m_arrYMapper.GetAt(i);
			iCursorDataIndexTemp = -1;			
			iDistanceTempMinX = INT_MAX;
			iDistanceTempMinY = INT_MAX;

			for ( j = iSearchStart; j <= iSearchEnd; j++ )
			{
				dbXData = m_arrPlotData.GetAt(i)->GetXPoint2D(j);
				dbYData = m_arrPlotData.GetAt(i)->GetYPoint2D(j);

				if ( dbXData >= m_XMapper.m_dbXDataMin && dbXData <= m_XMapper.m_dbXDataMax )
				{
					bShowDataExist = true;

					iTempXPos = m_XMapper.CalcXDataToPt(dbXData);
					iTempYPos = strYMapper.CalcYDataToPt(dbYData);

					iDistanceTempX = (iTempXPos - iXPos) * (iTempXPos - iXPos);
					iDistanceTempY = (iTempYPos - iYPos) * (iTempYPos - iYPos);

					if ( iDistanceTempX < iDistanceTempMinX )
					{
						iDistanceTempMinX = iDistanceTempX;
						iDistanceTempMinY = iDistanceTempY;
						iCursorDataIndexTemp = j;
						iOverlapTempIndex = i;					
					}
					else if ( iDistanceTempX == iDistanceTempMinX )
					{						
						if ( iDistanceTempY < iDistanceTempMinY )
						{						
							iDistanceTempMinY = iDistanceTempY;
							iDistanceTempMinY = iDistanceTempY;
							iCursorDataIndexTemp = j;
							iOverlapTempIndex = i;	
						}
					}
				}
			}

			if ( iCursorDataIndexTemp != -1 )
			{
				if ( iDistanceTempMinX < iDistanceMinX )
				{
					iDistanceMinX = iDistanceTempMinX;
					iDistanceMinY = iDistanceTempMinY;
					iOverlapIndex = iOverlapTempIndex;
					iCursorDataIndex = iCursorDataIndexTemp;
				}
				else if ( iDistanceTempMinX == iDistanceMinX )
				{
					if ( iDistanceTempMinY < iDistanceMinY )
					{
						iDistanceMinX = iDistanceTempMinX;
						iDistanceMinY = iDistanceTempMinY;
						iOverlapIndex = iOverlapTempIndex;
						iCursorDataIndex = iCursorDataIndexTemp;
					}
				}
			}
		}
	}

	if ( bShowDataExist == false )
	{
		m_bCalcAuxCursor = false;
		return false;
	}

	m_strAuxCursorEventInfo.iPlotIndex = m_iPlotIndex;
	m_strAuxCursorEventInfo.iAuxCursorGroupElementIndex = m_arrAuxCursorGroup.GetAt(iAuxCursorGroupIndex)->m_iElementIndex;
	m_strAuxCursorEventInfo.iAuxCursorElementIndex = strAuxCursor.iElementIndex;
	m_strAuxCursorEventInfo.iAuxCursorGroupIndex = iAuxCursorGroupIndex;
	m_strAuxCursorEventInfo.iAuxCursorIndex = iAuxCursorIndex;

	m_strAuxCursorEventInfo.iDataIndex = iCursorDataIndex;
	m_strAuxCursorEventInfo.dbXData = m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(iCursorDataIndex);
	m_strAuxCursorEventInfo.dbYData = m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(iCursorDataIndex);

	::SendMessage(m_hMsgHandle, WM_GRAPH2D_AUX_CURSOR_EVENT, 0, (LPARAM)&m_strAuxCursorEventInfo);
	
	m_bCalcAuxCursor = false;

	return true;
}

//! Added by LHW [2008/4/10]
bool CGraph2DWnd::MakeFromMaxValuesToAuxCursor(int iAuxCursorSize, int &iAuxCursorGroupIndex, int iOverlapIndex)
{
	iAuxCursorGroupIndex = -1;

	if ( iAuxCursorSize <= 0 )
	{
		return false;
	}
	if ( m_pPlotResource == NULL )
	{
		return false;
	}
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}
	int iDrawDataSize = m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize();
	if ( iDrawDataSize <= 0 )
	{
		return false;
	}

	if ( m_arrPlotData.GetAt(iOverlapIndex)->SortYDirection(false) == false )
	{
		return false;
	}

	strGraph2D_Aux_Cursor strAuxCursorAdd;
	strGraph2D_Aux_CursorGroup strAuxCursorGroup;
	CString szValueX = _T(""), szValueY = _T("");
	int i = 0, iDataIndex_Sort = 0;

	strAuxCursorAdd.InitInfo();
	strAuxCursorAdd.eCursorType = E_GRAPH2D_AUX_CURSOR_FIXED_INDEX;
	strAuxCursorAdd.eSearchMode = E_GRAPH2D_AUX_CURSOR_SEARCH_X_RANGE;
	strAuxCursorAdd.iOverlapIndex = iOverlapIndex;
	iDataIndex_Sort = m_arrPlotData.GetAt(iOverlapIndex)->GetIndexPoint2D_Sort(0);
	strAuxCursorAdd.iDataIndex = iDataIndex_Sort;
	szValueX = GetVisualDataText( m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(iDataIndex_Sort), true, false, true, iOverlapIndex);
	szValueY = GetVisualDataText( m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(iDataIndex_Sort), false, false, true, iOverlapIndex);
	strAuxCursorAdd.szCursorText.Format(_T("%s%s, %s%s"), szValueX, 
		((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.szCursorUnit, 
		szValueY, m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.szCursorUnit);

	iAuxCursorGroupIndex = AddAuxCursor(strAuxCursorAdd);

	if ( iAuxCursorGroupIndex >= 0 )
	{
		if ( iAuxCursorSize > 1 )
		{
			for ( i = 1; i < iAuxCursorSize; i++ )
			{
				strAuxCursorAdd.InitInfo();
				strAuxCursorAdd.eCursorType = E_GRAPH2D_AUX_CURSOR_FIXED_INDEX;
				strAuxCursorAdd.eSearchMode = E_GRAPH2D_AUX_CURSOR_SEARCH_X_RANGE;
				strAuxCursorAdd.iOverlapIndex = iOverlapIndex;
				iDataIndex_Sort = m_arrPlotData.GetAt(iOverlapIndex)->GetIndexPoint2D_Sort(i);
				strAuxCursorAdd.iDataIndex = iDataIndex_Sort;
				szValueX = GetVisualDataText( m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(iDataIndex_Sort), true, false, true, iOverlapIndex);
				szValueY = GetVisualDataText( m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(iDataIndex_Sort), false, false, true, iOverlapIndex);
				strAuxCursorAdd.szCursorText.Format(_T("%s%s, %s%s"), szValueX, 
					((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.szCursorUnit, 
					szValueY, m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.szCursorUnit);
				AddAuxCursor(strAuxCursorAdd, iAuxCursorGroupIndex);
			}
		}

		GetAuxCursorGroupInfo(iAuxCursorGroupIndex, strAuxCursorGroup);
		strAuxCursorGroup.bShow = true;
		strAuxCursorGroup.bRadius = true;
		strAuxCursorGroup.bFontHeight = true;
		strAuxCursorGroup.bFontVertical = true;
		strAuxCursorGroup.iSolidPenThickness = 1;
		strAuxCursorGroup.clrAuxCursor = RGB(255, 128, 0);
		strAuxCursorGroup.clrAuxCursorText = RGB(255, 128, 0);
		SetAuxCursorGroupInfo(iAuxCursorGroupIndex, strAuxCursorGroup);
	}

	return true;
}

//! Added by LHW [2008/4/10]
//! Modify by LHW [2008/9/1] : iMaxAddSize 추가
bool CGraph2DWnd::MakeFromThresholdToAuxCursor(double dbThreshold, int iMaxAddSize, int &iAuxCursorGroupIndex, int iOverlapIndex)
{
	iAuxCursorGroupIndex = -1;

	if ( m_pPlotResource == NULL )
	{
		return false;
	}
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}
	int iDrawDataSize = m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize();
	if ( iDrawDataSize <= 0 )
	{
		return false;
	}

	bool bFirstFlag = true;
	int i = 0, iCnt = 0;
	strGraph2D_Aux_Cursor strAuxCursorAdd;
	strGraph2D_Aux_CursorGroup strAuxCursorGroup;
	CString szValueX = _T(""), szValueY = _T("");

	for ( i = 0; i < iDrawDataSize; i++ )
	{
		if ( m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(i) < dbThreshold )
		{
			continue;
		}
		if ( iMaxAddSize >= 0 && iCnt >= iMaxAddSize )
		{
			break;
		}

		strAuxCursorAdd.InitInfo();
		strAuxCursorAdd.eCursorType = E_GRAPH2D_AUX_CURSOR_FIXED_INDEX;
		strAuxCursorAdd.eSearchMode = E_GRAPH2D_AUX_CURSOR_SEARCH_X_RANGE;
		strAuxCursorAdd.iOverlapIndex = iOverlapIndex;
		strAuxCursorAdd.iDataIndex = i;
		szValueX = GetVisualDataText( m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(i), true, false, true, iOverlapIndex);
		szValueY = GetVisualDataText( m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(i), false, false, true, iOverlapIndex);
		strAuxCursorAdd.szCursorText.Format(_T("%s%s, %s%s"), szValueX, 
					((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.szCursorUnit, 
					szValueY, m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.szCursorUnit);

		if ( bFirstFlag == true )
		{
			iAuxCursorGroupIndex = AddAuxCursor(strAuxCursorAdd);
			if ( iAuxCursorGroupIndex < 0 )
			{
				return false;
			}

			bFirstFlag = false;
		}
		else
		{
			AddAuxCursor(strAuxCursorAdd, iAuxCursorGroupIndex);
		}

		iCnt++;
	}

	if ( iCnt <= 0 || iAuxCursorGroupIndex < 0 )
	{
		return false;
	}

	if ( iCnt > 0 && iAuxCursorGroupIndex >= 0 )
	{
		GetAuxCursorGroupInfo(iAuxCursorGroupIndex, strAuxCursorGroup);
		strAuxCursorGroup.bShow = true;
		strAuxCursorGroup.bRadius = true;
		strAuxCursorGroup.bFontHeight = true;
		strAuxCursorGroup.bFontVertical = true;
		strAuxCursorGroup.iSolidPenThickness = 1;
		strAuxCursorGroup.clrAuxCursor = RGB(0, 128, 255);
		strAuxCursorGroup.clrAuxCursorText = RGB(0, 128, 255);
		SetAuxCursorGroupInfo(iAuxCursorGroupIndex, strAuxCursorGroup);
	}

	return true;
}

//! Added by LHW [2008/4/11]
bool CGraph2DWnd::IsExistCursorElementIndex(int iElementIndex)
{
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize <= 0 )
	{
		return false;
	}
	bool bExist = false;
	strGraph2DCursorInfo strCursor;
	for ( int i = 0; i < iCursorSize; i++ )
	{
		strCursor = m_arrCursor.GetAt(i);
		if ( strCursor.iElementIndex == iElementIndex )
		{
			bExist = true;
			break;
		}
	}

	return bExist;
}

//! Added by LHW [2008/6/14]
bool CGraph2DWnd::IsExistChildCursorElementIndex(int iElementIndex)
{
	int iChildCursorSize = (int)(m_arrChildCursor.GetSize());
	if ( iChildCursorSize <= 0 )
	{
		return false;
	}
	bool bExist = false;
	for ( int i = 0; i < iChildCursorSize; i++ )
	{
		if ( m_arrChildCursor.GetAt(i)->m_iElementIndex == iElementIndex )
		{
			bExist = true;
			break;
		}
	}

	return bExist;
}

//! Added by LHW [2008/4/11]
bool CGraph2DWnd::IsExistAuxCursorGroupElementIndex(int iElementIndex)
{
	int iAuxCursorGroupSize = (int)(m_arrAuxCursorGroup.GetSize());
	if ( iAuxCursorGroupSize <= 0 )
	{
		return false;
	}
	bool bExist = false;
	for ( int i = 0; i < iAuxCursorGroupSize; i++ )
	{
		if ( m_arrAuxCursorGroup.GetAt(i)->m_iElementIndex == iElementIndex )
		{
			bExist = true;
			break;
		}
	}

	return bExist;
}

//! Added by LHW [2008/11/28]
//! Modify by LHW [2008/11/30] : 실질적인 내용 구현
bool CGraph2DWnd::IsExistRegionCursorElementIndex(int iElementIndex)
{
	int iRegionCursorSize = (int)(m_arrRegionCursor.GetSize());
	if ( iRegionCursorSize <= 0 )
	{
		return false;
	}
	bool bExist = false;
	for ( int i = 0; i < iRegionCursorSize; i++ )
	{
		if ( m_arrRegionCursor.GetAt(i)->m_iElementIndex == iElementIndex )
		{
			bExist = true;
			break;
		}
	}

	return bExist;
}

//! Added by LHW [2008/4/11]
bool CGraph2DWnd::IsExistResourceYElementIndex(int iElementIndex)
{
	int iResourceYSize = (int)(m_arrResourceY.GetSize());
	if ( iResourceYSize <= 0 )
	{
		return false;
	}
	bool bExist = false;
	for ( int i = 0; i < iResourceYSize; i++ )
	{
		if ( m_arrResourceY.GetAt(i)->m_iElementIndex == iElementIndex )
		{
			bExist = true;
			break;
		}
	}

	return bExist;
}

//! Added by LHW [2008/4/11]
bool CGraph2DWnd::IsExistDataBufferElementIndex(int iElementIndex)
{
	int iDataBufferSize = (int)(m_arrPlotData.GetSize());
	if ( iDataBufferSize <= 0 )
	{
		return false;
	}
	bool bExist = false;
	for ( int i = 0; i < iDataBufferSize; i++ )
	{
		if ( m_arrPlotData.GetAt(i)->m_iElementIndex == iElementIndex )
		{
			bExist = true;
			break;
		}
	}

	return bExist;
}

//! Added by LHW [2008/4/19]
bool CGraph2DWnd::IsExistXValueLineElementIndex(int iElementIndex)
{
	int iXValueLineSize = (int)(m_arrValueLineX.GetSize());
	if ( iXValueLineSize <= 0 )
	{
		return false;
	}
	bool bExist = false;
	for ( int i = 0; i < iXValueLineSize; i++ )
	{
		if ( m_arrValueLineX.GetAt(i)->m_iElementIndex == iElementIndex )
		{
			bExist = true;
			break;
		}
	}

	return bExist;
}

//! Added by LHW [2008/4/11]
bool CGraph2DWnd::IsExistYValueLineElementIndex(int iElementIndex)
{
	int iYValueLineSize = (int)(m_arrValueLineY.GetSize());
	if ( iYValueLineSize <= 0 )
	{
		return false;
	}
	bool bExist = false;
	for ( int i = 0; i < iYValueLineSize; i++ )
	{
		if ( m_arrValueLineY.GetAt(i)->m_iElementIndex == iElementIndex )
		{
			bExist = true;
			break;
		}
	}

	return bExist;
}

//! Added by LHW [2008/8/23]
bool CGraph2DWnd::IsExistGraphEquationElementIndex(int iElementIndex)
{
	int iGraphEquationSize = (int)(m_arrGraphEquation.GetSize());
	if ( iGraphEquationSize <= 0 )
	{
		return false;
	}
	bool bExist = false;
	for ( int i = 0; i < iGraphEquationSize; i++ )
	{
		if ( m_arrGraphEquation.GetAt(i)->m_iElementIndex == iElementIndex )
		{
			bExist = true;
			break;
		}
	}

	return bExist;
}

//! Added by LHW [2008/4/11]
int CGraph2DWnd::GetCursorPossibleElementIndex()
{
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize <= 0 )
	{
		return 0;
	}
	int iReturn = -1;
	while(1)
	{
		if ( iReturn >= INT_MAX )
		{
			break;
		}

		iReturn++;

		if ( IsExistCursorElementIndex(iReturn) == false )
		{
			break;
		}		
	}

	return iReturn;
}

//! Added by LHW [2008/6/14]
int CGraph2DWnd::GetChildCursorPossibleElementIndex()
{
	int iChildCursorSize = (int)(m_arrChildCursor.GetSize());
	if ( iChildCursorSize <= 0 )
	{
		return 0;
	}
	int iReturn = -1;
	while(1)
	{
		if ( iReturn >= INT_MAX )
		{
			break;
		}

		iReturn++;

		if ( IsExistChildCursorElementIndex(iReturn) == false )
		{
			break;
		}
	}

	return iReturn;
}

//! Added by LHW [2008/4/11]
int CGraph2DWnd::GetAuxCursorGroupPossibleElementIndex()
{
	int iAuxCursorGroupSize = (int)(m_arrAuxCursorGroup.GetSize());
	if ( iAuxCursorGroupSize <= 0 )
	{
		return 0;
	}
	int iReturn = -1;
	while(1)
	{
		if ( iReturn >= INT_MAX )
		{
			break;
		}

		iReturn++;

		if ( IsExistAuxCursorGroupElementIndex(iReturn) == false )
		{
			break;
		}		
	}

	return iReturn;
}

//! Added by LHW [2008/11/28]
//! Modify by LHW [2008/11/30] : 실질적인 내용 구현
int CGraph2DWnd::GetRegionCursorPossibleElementIndex()
{
	int iRegionCursorSize = (int)(m_arrRegionCursor.GetSize());
	if ( iRegionCursorSize <= 0 )
	{
		return 0;
	}
	int iReturn = -1;
	while(1)
	{
		if ( iReturn >= INT_MAX )
		{
			break;
		}

		iReturn++;

		if ( IsExistRegionCursorElementIndex(iReturn) == false )
		{
			break;
		}
	}

	return iReturn;
}

//! Added by LHW [2008/4/11]
int CGraph2DWnd::GetResourceYPossibleElementIndex()
{
	int iResourceYSize = (int)(m_arrResourceY.GetSize());
	if ( iResourceYSize <= 0 )
	{
		return 0;
	}
	int iReturn = -1;
	while(1)
	{
		if ( iReturn >= INT_MAX )
		{
			break;
		}

		iReturn++;

		if ( IsExistResourceYElementIndex(iReturn) == false )
		{
			break;
		}		
	}

	return iReturn;
}

//! Added by LHW [2008/4/11]
int CGraph2DWnd::GetDataBufferPossibleElementIndex()
{
	int iDataBufferSize = (int)(m_arrPlotData.GetSize());
	if ( iDataBufferSize <= 0 )
	{
		return 0;
	}
	int iReturn = -1;
	while(1)
	{
		if ( iReturn >= INT_MAX )
		{
			break;
		}

		iReturn++;

		if ( IsExistDataBufferElementIndex(iReturn) == false )
		{
			break;
		}		
	}

	return iReturn;
}

//! Added by LHW [2008/4/19]
int CGraph2DWnd::GetXValueLinePossibleElementIndex()
{
	int iXValueLineSize = (int)(m_arrValueLineX.GetSize());
	if ( iXValueLineSize <= 0 )
	{
		return 0;
	}
	int iReturn = -1;
	while(1)
	{
		if ( iReturn >= INT_MAX )
		{
			break;
		}

		iReturn++;

		if ( IsExistXValueLineElementIndex(iReturn) == false )
		{
			break;
		}		
	}

	return iReturn;
}

//! Added by LHW [2008/4/11]
int CGraph2DWnd::GetYValueLinePossibleElementIndex()
{
	int iYValueLineSize = (int)(m_arrValueLineY.GetSize());
	if ( iYValueLineSize <= 0 )
	{
		return 0;
	}
	int iReturn = -1;
	while(1)
	{
		if ( iReturn >= INT_MAX )
		{
			break;
		}

		iReturn++;

		if ( IsExistYValueLineElementIndex(iReturn) == false )
		{
			break;
		}		
	}

	return iReturn;
}

//! Added by LHW [2008/8/23]
int CGraph2DWnd::GetGraphEquationPossibleElementIndex()
{
	int iGraphEquationSize = (int)(m_arrGraphEquation.GetSize());
	if ( iGraphEquationSize <= 0 )
	{
		return false;
	}
	int iReturn = -1;
	while(1)
	{
		if ( iReturn >= INT_MAX )
		{
			break;
		}

		iReturn++;

		if ( IsExistGraphEquationElementIndex(iReturn) == false )
		{
			break;
		}
	}

	return iReturn;
}

//! Added by LHW [2008/4/11]
bool CGraph2DWnd::GetCursorIndexFromElementIndex(int iElementIndex, int &iIndex)
{
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize <= 0 )
	{
		return false;
	}
	iIndex = -1;
	strGraph2DCursorInfo strCursor;
	for ( int i = 0; i < iCursorSize; i++ )
	{
		strCursor = m_arrCursor.GetAt(i);
		if ( strCursor.iElementIndex == iElementIndex )
		{
			iIndex = i;
			break;
		}
	}
	if ( iIndex < 0 )
	{
		return false;
	}

	return true;
}

//! Added by LHW [2008/6/14]
bool CGraph2DWnd::GetChildCursorIndexFromElementIndex(int iElementIndex, int &iIndex)
{
	int iChildCursorSize = (int)(m_arrChildCursor.GetSize());
	if ( iChildCursorSize <= 0 )
	{
		return false;
	}
	iIndex = -1;
	for ( int i = 0; i < iChildCursorSize; i++ )
	{
		if ( m_arrChildCursor.GetAt(i)->m_iElementIndex == iElementIndex )
		{
			iIndex = i;
			break;
		}		
	}
	if ( iIndex < 0 )
	{
		return false;
	}

	return true;
}

//! Added by LHW [2008/4/11]
bool CGraph2DWnd::GetAuxCursorGroupIndexFromElementIndex(int iElementIndex, int &iIndex)
{
	int iAuxCursorGroupSize = (int)(m_arrAuxCursorGroup.GetSize());
	if ( iAuxCursorGroupSize <= 0 )
	{
		return false;
	}
	iIndex = -1;
	for ( int i = 0; i < iAuxCursorGroupSize; i++ )
	{
		if ( m_arrAuxCursorGroup.GetAt(i)->m_iElementIndex == iElementIndex )
		{
			iIndex = i;
			break;
		}		
	}
	if ( iIndex < 0 )
	{
		return false;
	}

	return true;
}

//! Added by LHW [2008/11/28]
//! Modify by LHW [2008/11/30] : 실질적인 내용 구현
bool CGraph2DWnd::GetRegionCursorIndexFromElementIndex(int iElementIndex, int &iIndex)
{
	int iRegionCursorSize = (int)(m_arrRegionCursor.GetSize());
	if ( iRegionCursorSize <= 0 )
	{
		return false;
	}
	iIndex = -1;
	for ( int i = 0; i < iRegionCursorSize; i++ )
	{
		if ( m_arrRegionCursor.GetAt(i)->m_iElementIndex == iElementIndex )
		{
			iIndex = i;
			break;
		}		
	}
	if ( iIndex < 0 )
	{
		return false;
	}

	return true;
}

//! Added by LHW [2008/4/11]
bool CGraph2DWnd::GetResourceYIndexFromElementIndex(int iElementIndex, int &iIndex)
{
	int iResourceYSize = (int)(m_arrResourceY.GetSize());
	if ( iResourceYSize <= 0 )
	{
		return false;
	}
	iIndex = -1;
	for ( int i = 0; i < iResourceYSize; i++ )
	{
		if ( m_arrResourceY.GetAt(i)->m_iElementIndex == iElementIndex )
		{
			iIndex = i;
			break;
		}		
	}
	if ( iIndex < 0 )
	{
		return false;
	}

	return true;
}

//! Added by LHW [2008/4/11]
bool CGraph2DWnd::GetDataBufferIndexFromElementIndex(int iElementIndex, int &iIndex)
{
	int iDataBufferSize = (int)(m_arrPlotData.GetSize());
	if ( iDataBufferSize <= 0 )
	{
		return false;
	}
	iIndex = -1;
	for ( int i = 0; i < iDataBufferSize; i++ )
	{
		if ( m_arrPlotData.GetAt(i)->m_iElementIndex == iElementIndex )
		{
			iIndex = i;
			break;
		}		
	}
	if ( iIndex < 0 )
	{
		return false;
	}

	return true;
}

//! Added by LHW [2008/4/19]
bool CGraph2DWnd::GetXValueLineIndexFromElementIndex(int iElementIndex, int &iIndex)
{
	int iXValueLineSize = (int)(m_arrValueLineX.GetSize());
	if ( iXValueLineSize <= 0 )
	{
		return false;
	}
	iIndex = -1;
	for ( int i = 0; i < iXValueLineSize; i++ )
	{
		if ( m_arrValueLineX.GetAt(i)->m_iElementIndex == iElementIndex )
		{
			iIndex = i;
			break;
		}		
	}
	if ( iIndex < 0 )
	{
		return false;
	}

	return true;
}

//! Added by LHW [2008/4/11]
bool CGraph2DWnd::GetYValueLineIndexFromElementIndex(int iElementIndex, int &iIndex)
{
	int iYValueLineSize = (int)(m_arrValueLineY.GetSize());
	if ( iYValueLineSize <= 0 )
	{
		return false;
	}
	iIndex = -1;
	for ( int i = 0; i < iYValueLineSize; i++ )
	{
		if ( m_arrValueLineY.GetAt(i)->m_iElementIndex == iElementIndex )
		{
			iIndex = i;
			break;
		}		
	}
	if ( iIndex < 0 )
	{
		return false;
	}

	return true;
}

//! Added by LHW [2008/8/23]
bool CGraph2DWnd::GetGraphEquationIndexFromElementIndex(int iElementIndex, int &iIndex)
{
	int iGraphEquationSize = (int)(m_arrGraphEquation.GetSize());
	if ( iGraphEquationSize <= 0 )
	{
		return false;
	}
	iIndex = -1;
	for ( int i = 0; i < iGraphEquationSize; i++ )
	{
		if ( m_arrGraphEquation.GetAt(i)->m_iElementIndex == iElementIndex )
		{
			iIndex = i;
			break;
		}
	}
	if ( iIndex < 0 )
	{
		return false;
	}

	return true;
}

//! Added by LHW [2008/4/11]
bool CGraph2DWnd::GetCursorElementIndexFromIndex(int iIndex, int &iElementIndex)
{
	int iCursorSize = (int)(m_arrCursor.GetSize());
	if ( iCursorSize <= 0 )
	{
		return false;
	}
	if ( iIndex < 0 || iIndex >= iCursorSize )
	{
		return false;
	}

	strGraph2DCursorInfo strCursor = m_arrCursor.GetAt(iIndex);
	iElementIndex = strCursor.iElementIndex;
	return true;
}

//! Added by LHW [2008/6/14]
bool CGraph2DWnd::GetChildCursorElementIndexFromIndex(int iIndex, int &iElementIndex)
{
	int iChildCursorSize = (int)(m_arrChildCursor.GetSize());
	if ( iChildCursorSize <= 0 )
	{
		return false;
	}
	if ( iIndex < 0 || iIndex >= iChildCursorSize )
	{
		return false;
	}

	iElementIndex = m_arrChildCursor.GetAt(iIndex)->m_iElementIndex;
	return true;
}

//! Added by LHW [2008/4/11]
bool CGraph2DWnd::GetAuxCursorGroupElementIndexFromIndex(int iIndex, int &iElementIndex)
{
	int iAuxCursorGroupSize = (int)(m_arrAuxCursorGroup.GetSize());
	if ( iAuxCursorGroupSize <= 0 )
	{
		return false;
	}
	if ( iIndex < 0 || iIndex >= iAuxCursorGroupSize )
	{
		return false;
	}

	iElementIndex = m_arrAuxCursorGroup.GetAt(iIndex)->m_iElementIndex;
	return true;
}

//! Added by LHW [2008/11/28]
//! Modify by LHW [2008/11/30] : 실질적인 내용 구현
bool CGraph2DWnd::GetRegionCursorElementIndexFromIndex(int iIndex, int &iElementIndex)
{
	int iRegionCursorSize = (int)(m_arrRegionCursor.GetSize());
	if ( iRegionCursorSize <= 0 )
	{
		return false;
	}
	if ( iIndex < 0 || iIndex >= iRegionCursorSize )
	{
		return false;
	}

	iElementIndex = m_arrRegionCursor.GetAt(iIndex)->m_iElementIndex;
	return true;
}

//! Added by LHW [2008/4/11]
bool CGraph2DWnd::GetResourceYElementIndexFromIndex(int iIndex, int &iElementIndex)
{
	int iResourceYSize = (int)(m_arrResourceY.GetSize());
	if ( iResourceYSize <= 0 )
	{
		return false;
	}
	if ( iIndex < 0 || iIndex >= iResourceYSize )
	{
		return false;
	}

	iElementIndex = m_arrResourceY.GetAt(iIndex)->m_iElementIndex;
	return true;
}

//! Added by LHW [2008/4/11]
bool CGraph2DWnd::GetDataBufferElementIndexFromIndex(int iIndex, int &iElementIndex)
{
	int iDataBufferSize = (int)(m_arrPlotData.GetSize());
	if ( iDataBufferSize <= 0 )
	{
		return false;
	}
	if ( iIndex < 0 || iIndex >= iDataBufferSize )
	{
		return false;
	}

	iElementIndex = m_arrPlotData.GetAt(iIndex)->m_iElementIndex;
	return true;
}

//! Added by LHW [2008/4/19]
bool CGraph2DWnd::GetXValueLineElementIndexFromIndex(int iIndex, int &iElementIndex)
{
	int iXValueLineSize = (int)(m_arrValueLineX.GetSize());
	if ( iXValueLineSize <= 0 )
	{
		return false;
	}
	if ( iIndex < 0 || iIndex >= iXValueLineSize )
	{
		return false;
	}

	iElementIndex = m_arrValueLineX.GetAt(iIndex)->m_iElementIndex;
	return true;
}

//! Added by LHW [2008/4/11]
bool CGraph2DWnd::GetYValueLineElementIndexFromIndex(int iIndex, int &iElementIndex)
{
	int iYValueLineSize = (int)(m_arrValueLineY.GetSize());
	if ( iYValueLineSize <= 0 )
	{
		return false;
	}
	if ( iIndex < 0 || iIndex >= iYValueLineSize )
	{
		return false;
	}

	iElementIndex = m_arrValueLineY.GetAt(iIndex)->m_iElementIndex;
	return true;
}

//! Added by LHW [2008/8/23]
bool CGraph2DWnd::GetGraphEquationElementIndexFromIndex(int iIndex, int &iElementIndex)
{
	int iGraphEquationSize = (int)(m_arrGraphEquation.GetSize());
	if ( iGraphEquationSize <= 0 )
	{
		return false;
	}
	if ( iIndex < 0 || iIndex >= iGraphEquationSize )
	{
		return false;
	}

	iElementIndex = m_arrGraphEquation.GetAt(iIndex)->m_iElementIndex;
	return true;
}

//! Added by LHW [2008/4/19] : 일정 구간안의 Peak 값을 찾는 함수
bool CGraph2DWnd::GetLocalPeakDataIndex(int iStartDataIndex, int iEndDataIndex, int &iPeakDataIndex, int iOverlapIndex)
{
	iPeakDataIndex = -1;

	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}

	if ( iStartDataIndex >= iEndDataIndex )
	{
		return false;
	}
	
	int iDrawDataSize = m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize();
	if ( iDrawDataSize <= 0 )
	{
		return false;
	}

	if ( iStartDataIndex >= (iDrawDataSize - 1) )
	{
		return false;
	}
	
	int iSearchStartIndex = iStartDataIndex;
	if ( iSearchStartIndex < 0 )
	{
		iSearchStartIndex = 0;
	}
	int iSearchEndIndex = iEndDataIndex;
	if ( iSearchEndIndex >= iDrawDataSize )
	{
		iSearchEndIndex = iDrawDataSize - 1;
	}

	double dbData = 0., dbPrevData = 0., dbMaxPeak = DBL_MAX * (-1.);
	bool bValueIncreased = false;

	dbPrevData = m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(iSearchStartIndex);
	iSearchStartIndex++;
	for ( int i = iSearchStartIndex; i < iSearchEndIndex; i++ )
	{
		dbData = m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(i);
		if ( dbData > dbPrevData )
		{
			bValueIncreased = true;
		}
		else
		{
			if ( bValueIncreased == true )
			{
				if ( dbPrevData > dbMaxPeak )
				{
					dbMaxPeak = dbPrevData;
					iPeakDataIndex = i - 1;
				}
			}

			bValueIncreased = false;
		}

		dbPrevData = dbData;
	}

	if ( iPeakDataIndex < 0 )
	{
		return false;
	}

	return true;
}

//! Added by LHW [2008/4/28]
bool CGraph2DWnd::MakeFromMaxPeakValuesToAuxCursor(int iAuxCursorSize, int &iAuxCursorGroupIndex, int iOverlapIndex)
{
	iAuxCursorGroupIndex = -1;

	if ( iAuxCursorSize <= 0 )
	{
		return false;
	}
	if ( m_pPlotResource == NULL )
	{
		return false;
	}
	if ( IsValidOverlapIndex(iOverlapIndex) == false )
	{
		return false;
	}
	int iDrawDataSize = m_arrPlotData.GetAt(iOverlapIndex)->GetPointSize();
	if ( iDrawDataSize <= 2 )
	{
		return false;
	}

	m_arrPlotData.GetAt(iOverlapIndex)->ClearBufferSort();

	int i = 0;
	strDataForSort strSortInputData;
	int iPeakDataIndex = -1;
	double dbData = 0., dbPrevData = 0.;
	bool bValueIncreased = false;
	dbPrevData = m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(0);
	for ( i = 1; i < iDrawDataSize; i++ )
	{
		dbData = m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(i);
		if ( dbData > dbPrevData )
		{
			bValueIncreased = true;
		}
		else
		{
			if ( bValueIncreased == true )
			{
				iPeakDataIndex = i - 1;

				strSortInputData.iDataIndex = iPeakDataIndex;
				strSortInputData.dbData = m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(iPeakDataIndex);
				m_arrPlotData.GetAt(iOverlapIndex)->AddDataSort(strSortInputData);
			}

			bValueIncreased = false;
		}

		dbPrevData = dbData;
	}

	m_arrPlotData.GetAt(iOverlapIndex)->SortProc(false);

	int iRealAuxCursorSize = iAuxCursorSize;
	if ( iRealAuxCursorSize > m_arrPlotData.GetAt(iOverlapIndex)->GetSortDataSize() )
	{
		iRealAuxCursorSize = m_arrPlotData.GetAt(iOverlapIndex)->GetSortDataSize();
	}

	if ( iRealAuxCursorSize <= 0 )
	{
		return false;
	}

	strGraph2D_Aux_Cursor strAuxCursorAdd;
	strGraph2D_Aux_CursorGroup strAuxCursorGroup;
	CString szValueX = _T(""), szValueY = _T("");
	int iDataIndex_Sort = 0;

	strAuxCursorAdd.InitInfo();
	strAuxCursorAdd.eCursorType = E_GRAPH2D_AUX_CURSOR_FIXED_INDEX;
	strAuxCursorAdd.eSearchMode = E_GRAPH2D_AUX_CURSOR_SEARCH_X_RANGE;
	strAuxCursorAdd.iOverlapIndex = iOverlapIndex;
	iDataIndex_Sort = m_arrPlotData.GetAt(iOverlapIndex)->GetIndexPoint2D_Sort(0);
	strAuxCursorAdd.iDataIndex = iDataIndex_Sort;
	szValueX = GetVisualDataText( m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(iDataIndex_Sort), true, false, true, iOverlapIndex);
	szValueY = GetVisualDataText( m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(iDataIndex_Sort), false, false, true, iOverlapIndex);
	strAuxCursorAdd.szCursorText.Format(_T("%s%s, %s%s"), szValueX, 
		((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.szCursorUnit, 
		szValueY, m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.szCursorUnit);

	iAuxCursorGroupIndex = AddAuxCursor(strAuxCursorAdd);

	if ( iAuxCursorGroupIndex >= 0 )
	{
		if ( iRealAuxCursorSize > 1 )
		{
			for ( i = 1; i < iRealAuxCursorSize; i++ )
			{
				strAuxCursorAdd.InitInfo();
				strAuxCursorAdd.eCursorType = E_GRAPH2D_AUX_CURSOR_FIXED_INDEX;
				strAuxCursorAdd.eSearchMode = E_GRAPH2D_AUX_CURSOR_SEARCH_X_RANGE;
				strAuxCursorAdd.iOverlapIndex = iOverlapIndex;
				iDataIndex_Sort = m_arrPlotData.GetAt(iOverlapIndex)->GetIndexPoint2D_Sort(i);
				strAuxCursorAdd.iDataIndex = iDataIndex_Sort;
				szValueX = GetVisualDataText( m_arrPlotData.GetAt(iOverlapIndex)->GetXPoint2D(iDataIndex_Sort), true, false, true, iOverlapIndex);
				szValueY = GetVisualDataText( m_arrPlotData.GetAt(iOverlapIndex)->GetYPoint2D(iDataIndex_Sort), false, false, true, iOverlapIndex);
				strAuxCursorAdd.szCursorText.Format(_T("%s%s, %s%s"), szValueX, 
					((CGraph2D_Resource*)m_pPlotResource)->m_strResourceInfo.strAxisInfoX.szCursorUnit, 
					szValueY, m_arrResourceY.GetAt(iOverlapIndex)->m_strResourceYinfo.strAxisInfo.szCursorUnit);
				AddAuxCursor(strAuxCursorAdd, iAuxCursorGroupIndex);
			}
		}

		GetAuxCursorGroupInfo(iAuxCursorGroupIndex, strAuxCursorGroup);
		strAuxCursorGroup.bShow = true;
		strAuxCursorGroup.bRadius = true;
		strAuxCursorGroup.bFontHeight = true;
		strAuxCursorGroup.bFontVertical = true;
		strAuxCursorGroup.iSolidPenThickness = 1;
		strAuxCursorGroup.clrAuxCursor = RGB(64, 0, 128);
		strAuxCursorGroup.clrAuxCursorText = RGB(64, 0, 128);
		SetAuxCursorGroupInfo(iAuxCursorGroupIndex, strAuxCursorGroup);
	}

	return true;
}
