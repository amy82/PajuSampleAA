#include "StdAfx.h"
#include ".\\Graph2D_Resource.h"

CGraph2D_Resource::CGraph2D_Resource(void)
{
	m_dbPanOffset = 0.;
	m_strResourceInfo.InitInfo();
	SetResource();

	m_arrZoomRecord.RemoveAll();
	m_arrZoomRecord.FreeExtra();

	m_eGridTextType = E_GRAPH2D_GRID_INTEGER;	//! Modify by LHW [2008/6/30]
	m_eCursorTextType = E_GRAPH2D_GRID_INTEGER;	//! Modify by LHW [2008/6/30]
	m_iGridTextPrecision = 1;	//! Modify by LHW [2008/6/30]
	m_iCursorTextPrecision = 1;	//! Modify by LHW [2008/6/30]
	m_dbAutoRangeMin = 0.;		//! Modify by LHW [2008/7/02]
	m_dbAutoRangeMax = 0.;		//! Modify by LHW [2008/7/02]

	m_arrMinBound.RemoveAll();	//! Modify by LHW [2009/5/30]
	m_arrMinBound.FreeExtra();	//! Modify by LHW [2009/5/30]
	m_arrMaxBound.RemoveAll();	//! Modify by LHW [2009/5/30]
	m_arrMaxBound.FreeExtra();	//! Modify by LHW [2009/5/30]
}

CGraph2D_Resource::~CGraph2D_Resource(void)
{
	ReleaseResource();

	m_arrZoomRecord.RemoveAll();
	m_arrZoomRecord.FreeExtra();

	m_arrMinBound.RemoveAll();	//! Modify by LHW [2009/5/30]
	m_arrMinBound.FreeExtra();	//! Modify by LHW [2009/5/30]
	m_arrMaxBound.RemoveAll();	//! Modify by LHW [2009/5/30]
	m_arrMaxBound.FreeExtra();	//! Modify by LHW [2009/5/30]
}

//! Modify by LHW [2008/5/14] : m_penCursorLineSelected 부분 추가
//! Modify by LHW [2009/2/26] : 제목 문자 폰트 처리 부분 수정
void CGraph2D_Resource::SetResource()
{
	m_brEntireBackGround.CreateSolidBrush(m_strResourceInfo.clrEntireBackGround);
	m_brGraphBackGround.CreateSolidBrush(m_strResourceInfo.clrGraphBackGround);
	m_brCursorPoint.CreateSolidBrush(m_strResourceInfo.clrCursorPoint);
	m_brCursorTextBack.CreateSolidBrush(m_strResourceInfo.clrCursorTextBack);
	m_brZoomArea.CreateSolidBrush(m_strResourceInfo.clrZoomArea);

	if ( m_strResourceInfo.iAxisThickness <= 0 )
	{
		m_strResourceInfo.iAxisThickness = 1;
	}
	m_penAxis.CreatePen(PS_SOLID, m_strResourceInfo.iAxisThickness, m_strResourceInfo.clrAxis);
	if ( m_strResourceInfo.iGridThickness <= 0 )
	{
		m_strResourceInfo.iGridThickness = 1;
	}
	m_penGrid.CreatePen(PS_DOT, m_strResourceInfo.iGridThickness, m_strResourceInfo.clrGrid);
	if ( m_strResourceInfo.iCursorLineThickness <= 0 )
	{
		m_strResourceInfo.iCursorLineThickness = 1;
	}
	m_penCursorLine.CreatePen(PS_SOLID, m_strResourceInfo.iCursorLineThickness, m_strResourceInfo.clrCursorLine);
	m_penCursorLineSelected.CreatePen(PS_SOLID, m_strResourceInfo.iCursorLineThickness, m_strResourceInfo.clrCursorSelectedLine);
	if ( m_strResourceInfo.iCursorTextBorderThickness <= 0 )
	{
		m_strResourceInfo.iCursorTextBorderThickness = 1;
	}
	m_penCursorTextBorder.CreatePen(PS_SOLID, m_strResourceInfo.iCursorTextBorderThickness, m_strResourceInfo.clrCursorTextBorder);

	if ( m_strResourceInfo.szGridFontName.GetLength() <= 0 )
	{
		m_strResourceInfo.szGridFontName = _T("MS Sans Serif");
	}
	if ( m_strResourceInfo.szCursorFontName.GetLength() <= 0 )
	{
		m_strResourceInfo.szCursorFontName = _T("MS Sans Serif");
	}
	if ( m_strResourceInfo.szLegendFontName.GetLength() <= 0 )
	{
		m_strResourceInfo.szLegendFontName = _T("MS Sans Serif");
	}
	if ( m_strResourceInfo.strMainTitleInfo.szTitleFontName.GetLength() <= 0 )
	{
		m_strResourceInfo.strMainTitleInfo.szTitleFontName = _T("MS Sans Serif");
	}
	if ( m_strResourceInfo.strSubTitleInfo.szTitleFontName.GetLength() <= 0 )
	{
		m_strResourceInfo.strSubTitleInfo.szTitleFontName = _T("MS Sans Serif");
	}
	m_ftGridText.CreateFont(m_strResourceInfo.iGridFontHeight, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, m_strResourceInfo.szGridFontName);
	m_ftCursorText.CreateFont(m_strResourceInfo.iCursorFontHeight, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, m_strResourceInfo.szCursorFontName);
	m_ftLegend.CreateFont(m_strResourceInfo.iLegendFontHeight, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, m_strResourceInfo.szLegendFontName);

	int iFontWeight = FW_NORMAL;
	if ( m_strResourceInfo.strMainTitleInfo.bBold == true )
	{
		iFontWeight = FW_BOLD;
	}
	m_ftMainTitle.CreateFont(m_strResourceInfo.strMainTitleInfo.iTitleFontHeight, 0, 0, 0, iFontWeight, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, m_strResourceInfo.strMainTitleInfo.szTitleFontName);
	
	iFontWeight = FW_NORMAL;
	if ( m_strResourceInfo.strSubTitleInfo.bBold == true )
	{
		iFontWeight = FW_BOLD;
	}
	m_ftSubTitle.CreateFont(m_strResourceInfo.strSubTitleInfo.iTitleFontHeight, 0, 0, 0, iFontWeight, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, m_strResourceInfo.strSubTitleInfo.szTitleFontName);
}

//! Modify by LHW [2008/5/14] : m_penCursorLineSelected 부분 추가
void CGraph2D_Resource::ReleaseResource()
{
	m_brEntireBackGround.DeleteObject();
	m_brGraphBackGround.DeleteObject();
	m_brCursorPoint.DeleteObject();
	m_brCursorTextBack.DeleteObject();
	m_brZoomArea.DeleteObject();

	m_penAxis.DeleteObject();
	m_penGrid.DeleteObject();	
	m_penCursorLine.DeleteObject();
	m_penCursorLineSelected.DeleteObject();
	m_penCursorTextBorder.DeleteObject();

	m_ftGridText.DeleteObject();
	m_ftCursorText.DeleteObject();
	m_ftLegend.DeleteObject();
	m_ftMainTitle.DeleteObject();
	m_ftSubTitle.DeleteObject();
}

void CGraph2D_Resource::AddZoomRecord()
{
	strZoomRecord strAddZoomX;
	strAddZoomX.bAutoRange = m_strResourceInfo.strAxisInfoX.bAutoRange;
	strAddZoomX.dbMin = m_strResourceInfo.strAxisInfoX.dbManualMin;
	strAddZoomX.dbMax = m_strResourceInfo.strAxisInfoX.dbManualMax;
	m_arrZoomRecord.Add(strAddZoomX);
}

CGraph2D_ResourceY::CGraph2D_ResourceY(void)
{
	m_iElementIndex = -1;	//! Modify by LHW [2008/4/11]
	m_dbPanOffset = 0.;
	m_iDrawXPt = 0;	
	m_strResourceYinfo.InitInfo();	
	SetResource();

	m_arrZoomRecord.RemoveAll();
	m_arrZoomRecord.FreeExtra();

	m_eGridTextType = E_GRAPH2D_GRID_INTEGER;	//! Modify by LHW [2008/6/30]
	m_eCursorTextType = E_GRAPH2D_GRID_INTEGER;	//! Modify by LHW [2008/6/30]
	m_iGridTextPrecision = 1;	//! Modify by LHW [2008/6/30]
	m_iCursorTextPrecision = 1;	//! Modify by LHW [2008/6/30]
	m_dbAutoRangeMin = 0.;		//! Modify by LHW [2008/7/02]
	m_dbAutoRangeMax = 0.;		//! Modify by LHW [2008/7/02]
	m_iLeftXPtofYAxis = 0;		//! Modify by LHW [2008/10/25]
	m_iRightXPtofYAxis = 0;		//! Modify by LHW [2008/10/25]

	m_dbTempRangeMax = 0.;		//! Modify by LHW [2009/2/14]
	m_dbTempRangeMin = 0.;		//! Modify by LHW [2009/2/14]

	m_arrMinBound.RemoveAll();	//! Modify by LHW [2009/5/30]
	m_arrMinBound.FreeExtra();	//! Modify by LHW [2009/5/30]
	m_arrMaxBound.RemoveAll();	//! Modify by LHW [2009/5/30]
	m_arrMaxBound.FreeExtra();	//! Modify by LHW [2009/5/30]
}

CGraph2D_ResourceY::~CGraph2D_ResourceY(void)
{
	ReleaseResource();

	m_arrZoomRecord.RemoveAll();
	m_arrZoomRecord.FreeExtra();

	m_arrMinBound.RemoveAll();	//! Modify by LHW [2009/5/30]
	m_arrMinBound.FreeExtra();	//! Modify by LHW [2009/5/30]
	m_arrMaxBound.RemoveAll();	//! Modify by LHW [2009/5/30]
	m_arrMaxBound.FreeExtra();	//! Modify by LHW [2009/5/30]
}

//! Modify by LHW [2008/4/10] : m_brData 추가
//! Modify by LHW [2008/5/23] : eDataDrawType, iLineWidth, m_penEvent 관련 추가
//! Modify by LHW [2008/5/23] : iEventLineWidth 관련 추가
//! Modify by LHW [2008/7/24] : eLineType 관련 추가
//! Modify by LHW [2009/2/3] : m_brData를 m_brSymbol로 수정, m_penSymbol, m_brEvent 추가
//! Modify by LHW [2009/2/27] : 데이터 선의 두께를 설정하는 부분의 오류를 수정
void CGraph2D_ResourceY::SetResource()
{
	m_penYAxis.CreatePen(PS_SOLID, 1, m_strResourceYinfo.clrData);
	if ( m_strResourceYinfo.iLineWidth <= 0 )
	{
		m_strResourceYinfo.iLineWidth = 1;
	}
	if ( m_strResourceYinfo.eDataDrawType == E_GRAPH2D_DATA_DRAW_LINE || m_strResourceYinfo.eDataDrawType == E_GRAPH2D_DATA_DRAW_LINE_SYMBOL )
	{
		switch( m_strResourceYinfo.eLineType )
		{
		case E_GRAPH2D_LINE_TYPE_SOLID:
			{
				m_penData.CreatePen(PS_SOLID, m_strResourceYinfo.iLineWidth, m_strResourceYinfo.clrData);
			}
			break;
		case E_GRAPH2D_LINE_TYPE_DOT:
			{
				m_penData.CreatePen(PS_DOT, 1, m_strResourceYinfo.clrData);
			}
			break;
		case E_GRAPH2D_LINE_TYPE_DASH:
			{
				m_penData.CreatePen(PS_DASH, 1, m_strResourceYinfo.clrData);
			}
			break;
		case E_GRAPH2D_LINE_TYPE_DASH_DOT:
			{
				m_penData.CreatePen(PS_DASHDOT, 1, m_strResourceYinfo.clrData);
			}
			break;
		case E_GRAPH2D_LINE_TYPE_DASH_DOTDOT:
			{
				m_penData.CreatePen(PS_DASHDOTDOT, 1, m_strResourceYinfo.clrData);
			}
			break;
		}
	}
	else
	{
		m_penData.CreatePen(PS_SOLID, 1, m_strResourceYinfo.clrData);
	}

	if ( m_strResourceYinfo.iSymbolLineWidth <= 0 )
	{
		m_strResourceYinfo.iSymbolLineWidth = 1;
	}
	m_penSymbol.CreatePen(PS_SOLID, m_strResourceYinfo.iSymbolLineWidth, m_strResourceYinfo.clrSymbol);
	m_brSymbol.CreateSolidBrush(m_strResourceYinfo.clrSymbol);
	if ( m_strResourceYinfo.iSymbolSize <= 0 )
	{
		m_strResourceYinfo.iSymbolSize = 1;
	}

	if ( m_strResourceYinfo.iEventLineWidth <= 0 )
	{
		m_strResourceYinfo.iEventLineWidth = 1;
	}
	m_penEvent.CreatePen(PS_SOLID, m_strResourceYinfo.iEventLineWidth, m_strResourceYinfo.clrEventRect);	
	m_brEvent.CreateSolidBrush(m_strResourceYinfo.clrEventRect);
	if ( m_strResourceYinfo.iEventRectSize <= 0 )
	{
		m_strResourceYinfo.iEventRectSize = 1;
	}
}

//! Modify by LHW [2008/4/10] : m_brData 추가
//! Modify by LHW [2008/5/23] : m_penEvent 추가
//! Modify by LHW [2009/2/3] : m_brData를 m_brSymbol로 수정, m_penSymbol, m_brEvent 추가
void CGraph2D_ResourceY::ReleaseResource()
{
	m_penYAxis.DeleteObject();
	m_penData.DeleteObject();
	m_penSymbol.DeleteObject();
	m_penEvent.DeleteObject();
	m_brSymbol.DeleteObject();
	m_brEvent.DeleteObject();
}

void CGraph2D_ResourceY::AddZoomRecord()
{
	strZoomRecord strAddZoomY;
	strAddZoomY.bAutoRange = m_strResourceYinfo.strAxisInfo.bAutoRange;
	strAddZoomY.dbMin = m_strResourceYinfo.strAxisInfo.dbManualMin;
	strAddZoomY.dbMax = m_strResourceYinfo.strAxisInfo.dbManualMax;
	m_arrZoomRecord.Add(strAddZoomY);
}

//! Added by LHW [2008/4/19]
CGraph2D_ValueLineX::CGraph2D_ValueLineX(void)
{
	m_iElementIndex = -1;
	m_iFontHeight = 14;
	m_strXLineInfo.InitInfo();
	m_crSelect.SetRectEmpty();
	SetResource();
}

//! Added by LHW [2008/4/19]
CGraph2D_ValueLineX::~CGraph2D_ValueLineX(void)
{
	ReleaseResource();
}

//! Added by LHW [2008/4/19]
void CGraph2D_ValueLineX::SetResource()
{
	if ( m_strXLineInfo.iLineWidth <= 0 )
	{
		m_strXLineInfo.iLineWidth = 1;
	}
	m_penXLine.CreatePen(PS_SOLID, m_strXLineInfo.iLineWidth, m_strXLineInfo.clrValue);

	m_ftValueLineX.CreateFont(m_iFontHeight, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, _T("MS Sans Serif"));
}

//! Added by LHW [2008/4/19]
void CGraph2D_ValueLineX::ReleaseResource()
{
	m_penXLine.DeleteObject();
	m_ftValueLineX.DeleteObject();
}

//! Added by LHW [2008/3/29]
CGraph2D_ValueLineY::CGraph2D_ValueLineY(void)
{
	m_iElementIndex = -1;	//! Modify by LHW [2008/4/11]
	m_iFontHeight = 14;		//! Modify by LHW [2009/2/3]
	m_strYLineInfo.InitInfo();	
	SetResource();
}

//! Added by LHW [2008/3/29]
CGraph2D_ValueLineY::~CGraph2D_ValueLineY(void)
{
	ReleaseResource();
}

//! Added by LHW [2008/3/29]
void CGraph2D_ValueLineY::SetResource()
{
	if ( m_strYLineInfo.iLineWidth <= 0 )
	{
		m_strYLineInfo.iLineWidth = 1;
	}
	m_penYLine.CreatePen(PS_SOLID, m_strYLineInfo.iLineWidth, m_strYLineInfo.clrValue);

	m_ftValueLineY.CreateFont(m_iFontHeight, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, _T("MS Sans Serif"));	//! Modify by LHW [2009/2/3]
}

//! Added by LHW [2008/3/29]
void CGraph2D_ValueLineY::ReleaseResource()
{
	m_penYLine.DeleteObject();
	m_ftValueLineY.DeleteObject();	//! Modify by LHW [2009/2/3]
}

//! Added by LHW [2008/8/22]
CGraph2D_Equation::CGraph2D_Equation(void)
{
	m_iElementIndex = -1;
	m_strEquationInfo.InitInfo();
	m_dbDataMinY = 0.;	//! Y축 최소값
	m_dbDataMaxY = 0.;	//! Y축 최대값
	SetResource();
}

//! Added by LHW [2008/8/22]
CGraph2D_Equation::~CGraph2D_Equation(void)
{
	ReleaseStructureBuf();
	ReleaseResource();
}

//! Added by LHW [2008/8/22]
void CGraph2D_Equation::SetResource()
{
	if ( m_strEquationInfo.iLineWidth <= 0 )
	{
		m_strEquationInfo.iLineWidth = 1;
	}

	switch(m_strEquationInfo.eLineType)
	{
	case E_GRAPH2D_LINE_TYPE_SOLID:
		{
			m_penLine.CreatePen(PS_SOLID, m_strEquationInfo.iLineWidth, m_strEquationInfo.clrLine);
		}
		break;
	case E_GRAPH2D_LINE_TYPE_DOT:
		{
			m_penLine.CreatePen(PS_DOT, 1, m_strEquationInfo.clrLine);
		}
		break;
	case E_GRAPH2D_LINE_TYPE_DASH:
		{
			m_penLine.CreatePen(PS_DASH, 1, m_strEquationInfo.clrLine);
		}
		break;
	case E_GRAPH2D_LINE_TYPE_DASH_DOT:
		{
			m_penLine.CreatePen(PS_DASHDOT, 1, m_strEquationInfo.clrLine);
		}
		break;
	case E_GRAPH2D_LINE_TYPE_DASH_DOTDOT:
		{
			m_penLine.CreatePen(PS_DASHDOTDOT, 1, m_strEquationInfo.clrLine);
		}
		break;
	}	
}

//! Added by LHW [2008/8/22]
void CGraph2D_Equation::ReleaseResource()
{
	m_penLine.DeleteObject();
}

//! Added by LHW [2008/8/22]
void CGraph2D_Equation::ReleaseStructureBuf()
{
	m_strEquationInfo.ReleaseCoeffBuf();
}

//! Added by LHW [2008/11/28]
//! Modify by LHW [2008/12/1] : m_crSelectRegion 추가
CGraph2D_Region_Cursor::CGraph2D_Region_Cursor(void)
{
	m_iElementIndex = -1;
	m_dbMinDataX = 1.;
	m_dbMaxDataX = 2.;
	m_dbMinDataY = 1.;
	m_dbMaxDataY = 2.;
	m_iMinPosX = 10;
	m_iMaxPosX = 20;
	m_iMinPosY = 10;
	m_iMaxPosY = 20;
	m_strCursorInfo.InitInfo();

	m_crSelectRegion.SetRectEmpty();
	for ( int i = 0; i < REGION_CURSOR_SELECT_SIZE; i++ )
	{
		m_crSelectLine[i].SetRectEmpty();
	}
}

//! Added by LHW [2008/11/28]
CGraph2D_Region_Cursor::~CGraph2D_Region_Cursor(void)
{
	ReleaseResource();
}

//! Added by LHW [2008/11/28]
void CGraph2D_Region_Cursor::SetResource()
{
	if ( m_strCursorInfo.iCursorLineThickness <= 0 )
	{
		m_strCursorInfo.iCursorLineThickness = 1;
	}
	m_penCursorLine.CreatePen(PS_SOLID, m_strCursorInfo.iCursorLineThickness, m_strCursorInfo.clrCursorLine);
	m_penSelectCursorLine.CreatePen(PS_SOLID, m_strCursorInfo.iCursorLineThickness, m_strCursorInfo.clrSelectCursorLine);

	if ( m_strCursorInfo.szCursorFontName.GetLength() <= 0 )
	{
		m_strCursorInfo.szCursorFontName = _T("MS Sans Serif");
	}
	m_ftCursorText.CreateFont(m_strCursorInfo.iCursorFontHeight, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, m_strCursorInfo.szCursorFontName);
}

//! Added by LHW [2008/11/28]
void CGraph2D_Region_Cursor::ReleaseResource()
{
	m_penCursorLine.DeleteObject();
	m_penSelectCursorLine.DeleteObject();
	m_ftCursorText.DeleteObject();
}

//! Added by LHW [2008/11/28]
//! Modify by LHW [2008/11/30] : iCursorLineIndex 추가
bool CGraph2D_Region_Cursor::IsPtInSelect(CPoint ptInput, int &iCursorLineIndex)
{
	bool bReturn = false;
	iCursorLineIndex = -1;
	for ( int i = 0; i < REGION_CURSOR_SELECT_SIZE; i++ )
	{
		if ( m_crSelectLine[i].PtInRect(ptInput) == TRUE )
		{
			iCursorLineIndex = i;
			bReturn = true;
			break;
		}
	}
	return bReturn;
}

//! Added by LHW [2008/6/12]
//! Modify by LHW [2008/6/13] : m_dbDeltaX, m_dbDeltaY, m_iDataIndex 추가
//! Modify by LHW [2008/6/14] : m_bDataValid 추가
//! Modify by LHW [2008/6/15] : m_iCursorDataIndex, m_bCursorMoved 추가
CGraph2D_Child_Cursor::CGraph2D_Child_Cursor(void)
{
	m_iElementIndex = -1;
	m_iDataIndex = -1;
	m_iCursorDataIndex = -1;
	m_bCursorMoved = false;
	m_bDataValid = false;
	m_dbXData = 0.;
	m_dbYData = 0.;
	m_dbDeltaX = 0.;
	m_dbDeltaY = 0.;
	m_iXPos = 0;
	m_iYPos = 0;
	m_crSelectX.SetRectEmpty();
	m_crSelectY.SetRectEmpty();
	m_crInfo.SetRectEmpty();
	m_crData.SetRectEmpty();
	m_strCursorInfo.InitInfo();
}

//! Added by LHW [2008/6/12]
CGraph2D_Child_Cursor::~CGraph2D_Child_Cursor(void)
{
	ReleaseResource();
}

//! Added by LHW [2008/6/12]
//! Modify by LHW [2008/6/16] : m_penSelectCursorLine 추가
void CGraph2D_Child_Cursor::SetResource()
{
	m_brCursorPoint.CreateSolidBrush(m_strCursorInfo.clrCursorPoint);
	m_brCursorTextBack.CreateSolidBrush(m_strCursorInfo.clrCursorTextBack);

	if ( m_strCursorInfo.iCursorLineThickness <= 0 )
	{
		m_strCursorInfo.iCursorLineThickness = 1;
	}
	m_penCursorLine.CreatePen(PS_SOLID, m_strCursorInfo.iCursorLineThickness, m_strCursorInfo.clrCursorLine);
	m_penSelectCursorLine.CreatePen(PS_SOLID, m_strCursorInfo.iCursorLineThickness, m_strCursorInfo.clrSelectCursorLine);

	if ( m_strCursorInfo.iCursorTextBorderThickness <= 0 )
	{
		m_strCursorInfo.iCursorTextBorderThickness = 1;
	}
	m_penCursorTextBorder.CreatePen(PS_SOLID, m_strCursorInfo.iCursorTextBorderThickness, m_strCursorInfo.clrCursorTextBorder);

	if ( m_strCursorInfo.szCursorFontName.GetLength() <= 0 )
	{
		m_strCursorInfo.szCursorFontName = _T("MS Sans Serif");
	}
	m_ftCursorText.CreateFont(m_strCursorInfo.iCursorFontHeight, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, m_strCursorInfo.szCursorFontName);
}

//! Added by LHW [2008/6/12]
//! Modify by LHW [2008/6/16] : m_penSelectCursorLine 추가
void CGraph2D_Child_Cursor::ReleaseResource()
{
	m_brCursorPoint.DeleteObject();
	m_brCursorTextBack.DeleteObject();
	m_penCursorLine.DeleteObject();
	m_penSelectCursorLine.DeleteObject();
	m_penCursorTextBorder.DeleteObject();
	m_ftCursorText.DeleteObject();
}

//! Added by LHW [2008/3/31]
CGraph2D_Aux_CursorGroup::CGraph2D_Aux_CursorGroup(void)
{
	m_iElementIndex = -1;		//! Modify by LHW [2008/4/11]
	m_iAuxCursorElementCnt = 0;	//! Modify by LHW [2008/4/11]
	m_strGroupInfo.InitInfo();
	SetResource();

	m_arrCursorInfo.RemoveAll();
	m_arrCursorInfo.FreeExtra();
}

//! Added by LHW [2008/3/31]
CGraph2D_Aux_CursorGroup::~CGraph2D_Aux_CursorGroup(void)
{
	ReleaseResource();

	m_arrCursorInfo.RemoveAll();
	m_arrCursorInfo.FreeExtra();
}

//! Added by LHW [2008/3/31]
//! Modify by LHW [2008/4/19]
//! Modify by LHW [2008/4/21] : eDrawMode 부분 수정
//! Modify by LHW [2008/5/9] : bFontBold 적용 부분 추가
//! Modify by LHW [2008/8/04] : 보조 커서의 Pen 부분을 수정
void CGraph2D_Aux_CursorGroup::SetResource()
{
	if ( m_strGroupInfo.iSolidPenThickness <= 0 )
	{
		m_strGroupInfo.iSolidPenThickness = 1;
	}
	if ( m_strGroupInfo.szFontName.GetLength() <= 0 )
	{
		m_strGroupInfo.szFontName = _T("MS Sans Serif");
	}
	
	m_penAuxCursorSolid.CreatePen(PS_SOLID, m_strGroupInfo.iSolidPenThickness, m_strGroupInfo.clrAuxCursor);

	//! 점선, 쇄선등은 굵기가 1 이외에는 지원이 되지 않음
	m_penAuxCursorDot.CreatePen(PS_DOT, 1, m_strGroupInfo.clrAuxCursor);
	m_penAuxCursorDash.CreatePen(PS_DASH, 1, m_strGroupInfo.clrAuxCursor);
	
	if ( m_strGroupInfo.bFontVertical == false )
	{
		if ( m_strGroupInfo.bFontBold == true )
		{
			m_ftAuxCursorText.CreateFont(m_strGroupInfo.iFontHeight, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, m_strGroupInfo.szFontName);
		}
		else
		{
			m_ftAuxCursorText.CreateFont(m_strGroupInfo.iFontHeight, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, m_strGroupInfo.szFontName);
		}
	}
	else
	{
		if ( m_strGroupInfo.bFontBold == true )
		{
			m_ftAuxCursorText.CreateFont(m_strGroupInfo.iFontHeight, 0, 900, 900, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, m_strGroupInfo.szFontName);
		}
		else
		{
			m_ftAuxCursorText.CreateFont(m_strGroupInfo.iFontHeight, 0, 900, 900, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, m_strGroupInfo.szFontName);
		}
	}
}

//! Added by LHW [2008/3/31]
//! Modify by LHW [2008/8/04] : 보조 커서의 Pen 부분을 수정
void CGraph2D_Aux_CursorGroup::ReleaseResource()
{
	//m_penAuxCursor.DeleteObject();
	m_penAuxCursorSolid.DeleteObject();
	m_penAuxCursorDot.DeleteObject();
	m_penAuxCursorDash.DeleteObject();
	m_ftAuxCursorText.DeleteObject();
}

//! Added by LHW [2008/3/31]
int CGraph2D_Aux_CursorGroup::GetCursorInfoSize()
{
	return (int)(m_arrCursorInfo.GetSize());
}

//! Added by LHW [2008/4/11]
int CGraph2D_Aux_CursorGroup::GetAuxCursorPossibleElementIndex()
{
	int iAuxCursorSize = (int)(m_arrCursorInfo.GetSize());
	if ( iAuxCursorSize <= 0 )
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

		if ( IsExistAuxCursorElementIndex(iReturn) == false )
		{
			break;
		}		
	}

	return iReturn;
}

//! Added by LHW [2008/4/11]
bool CGraph2D_Aux_CursorGroup::IsExistAuxCursorElementIndex(int iElementIndex)
{	
	int iAuxCursorSize = (int)(m_arrCursorInfo.GetSize());
	if ( iAuxCursorSize <= 0 )
	{
		return false;
	}
	bool bExist = false;
	strGraph2D_Aux_Cursor_Extend strAuxCursorExtend;
	for ( int i = 0; i < iAuxCursorSize; i++ )
	{
		strAuxCursorExtend = m_arrCursorInfo.GetAt(i);
		if ( strAuxCursorExtend.iElementIndex == iElementIndex )
		{
			bExist = true;
			break;
		}
	}

	return bExist;
}

//! Added by LHW [2008/4/11]
bool CGraph2D_Aux_CursorGroup::GetAuxCursorIndexFromElementIndex(int iElementIndex, int &iIndex)
{
	int iAuxCursorSize = (int)(m_arrCursorInfo.GetSize());
	if ( iAuxCursorSize <= 0 )
	{
		return false;
	}
	iIndex = -1;
	strGraph2D_Aux_Cursor_Extend strAuxCursorExtend;
	for ( int i = 0; i < iAuxCursorSize; i++ )
	{
		strAuxCursorExtend = m_arrCursorInfo.GetAt(i);
		if ( strAuxCursorExtend.iElementIndex == iElementIndex )
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
bool CGraph2D_Aux_CursorGroup::GetAuxCursorElementIndexFromIndex(int iIndex, int &iElementIndex)
{
	int iAuxCursorSize = (int)(m_arrCursorInfo.GetSize());
	if ( iAuxCursorSize <= 0 )
	{
		return false;
	}
	if ( iIndex < 0 || iIndex >= iAuxCursorSize )
	{
		return false;
	}

	strGraph2D_Aux_Cursor_Extend strAuxCursorExtend = m_arrCursorInfo.GetAt(iIndex);
	iElementIndex = strAuxCursorExtend.iElementIndex;
	return true;
}
