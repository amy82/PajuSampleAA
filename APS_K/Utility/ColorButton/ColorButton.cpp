// ColorButton.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ColorButton.h"


// CColorButton

IMPLEMENT_DYNAMIC(CColorButton, CButton)

CColorButton::CColorButton()
{
	m_clrBtnBack = RGB(55, 73, 93);
	m_clrBtnBack_Selected = RGB(42, 55, 71);	/* 선택 Click */

	m_clrBtnText = RGB(255, 255, 255);
	m_clrBtnText_Selected = RGB(255, 255, 255);

	m_clrBtnNormal = m_clrBtnBack;					/* Normal */
	m_clrBtnOn = RGB(83, 180, 153);			/* OK */
	m_clrBtnOn2 = RGB(238, 194, 47);			/* OK2 */
	m_clrBtnERR = RGB(206, 0, 0);				/* ERROR */
	m_clrBtnRUN = RGB(181, 206, 0);				/* 동작중 */
	m_clrBtnDISABLE = RGB(243, 156, 17);				/* 미사용 */

	m_nStateBtn = 0;	/* Normal */
	m_dwTimeOver = 0;
	m_nUseBlink = 0;
	m_bBlink = false;
	m_bSelected = false;
	m_dwBlinkTime = 500;
	m_clFont.CreateFont(23, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
}

CColorButton::~CColorButton()
{
}


BEGIN_MESSAGE_MAP(CColorButton, CButton)
END_MESSAGE_MAP()



// CColorButton 메시지 처리기입니다.

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CColorButton::SetCtrlFont(int nHeight, int nWidth, CString szFontName)
{
	m_clFont.DeleteObject();

	m_clFont.CreateFont(nHeight, nWidth, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, szFontName);
	Invalidate();
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CColorButton::SetSelected(bool bSelect)
{
	if (m_bSelected != bSelect)
	{
		m_bSelected = bSelect;
		Invalidate();
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CColorButton::ChangeColor(int nState)
{
	if (m_bBlink == true)
	{
		int nBlinkNo = GetBlinkCtrl();
		if (m_nUseBlink != nBlinkNo)
		{
			m_nUseBlink = nBlinkNo;
			Invalidate();
		}		
	}
	else if (m_nStateBtn != nState)
	{
		m_nStateBtn = nState;
		Invalidate();
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
int CColorButton::GetBlinkCtrl()
{
	int nBlinkNo = m_nUseBlink;
	if ((GetTickCount() - m_dwTimeOver) > m_dwBlinkTime)
	{
		if (m_nUseBlink == 0)	nBlinkNo = 1;
		else					nBlinkNo = 0;

		m_dwTimeOver = GetTickCount();
	}

	return nBlinkNo;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CColorButton::SetBlink(bool bBlink)
{
	if (m_bBlink != bBlink)
	{
		m_bBlink = bBlink;
		Invalidate();
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CColorButton::SetBlinkTime(DWORD dwInterval)
{
	m_dwBlinkTime = dwInterval;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CColorButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  지정된 항목을 그리는 코드를 추가합니다.
	ASSERT(lpDrawItemStruct != NULL);
	if (lpDrawItemStruct->itemAction != ODA_DRAWENTIRE)
		return;

	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rect = lpDrawItemStruct->rcItem;
	if (pDC == NULL)	return;

	int nSavedDC = pDC->SaveDC();

	pDC->SelectStockObject(NULL_BRUSH);
	//pDC->FillSolidRect(rect, ::GetSysColor(COLOR_BTNFACE));


	if (m_bBlink == true)
	{
		COLORREF m_clrShine;
		if (m_nUseBlink == 0)	m_clrShine = m_clrBtnOn2;
		else					m_clrShine = m_clrBtnERR;

		pDC->FillSolidRect(rect, m_clrShine);
	}
	else if (m_bSelected == true)
	{
		pDC->FillSolidRect(rect, m_clrBtnBack_Selected);
	}
	else
	{
		switch (m_nStateBtn)
		{
		/* Normal */
		case 0:	m_clrBtnBack = m_clrBtnNormal;		break;
		/* OK-1 */
		case 1:	m_clrBtnBack = m_clrBtnOn;			break;
		/* OK-1 */
		case 2:	m_clrBtnBack = m_clrBtnOn2;			break;
		/* ERROR */
		case 3:	m_clrBtnBack = m_clrBtnERR;			break;
		/* 동작중 */
		case 4:	m_clrBtnBack = m_clrBtnRUN;			break;
		/* 미사용 */
		case 5:	m_clrBtnBack = m_clrBtnDISABLE;		break;
		}
		
		pDC->FillSolidRect(rect, m_clrBtnBack);
	}
	//BDR_RAISEDOUTER	안쪽 테두리
	//BDR_SUNKENINNER	안쪽 테두리	
	//#define EDGE_RAISED     (BDR_RAISEDOUTER | BDR_RAISEDINNER)
	//#define EDGE_SUNKEN     (BDR_SUNKENOUTER | BDR_SUNKENINNER)
	//#define EDGE_ETCHED     (BDR_SUNKENOUTER | BDR_RAISEDINNER)
	//#define EDGE_BUMP       (BDR_RAISEDOUTER | BDR_SUNKENINNER)
	//pDC->DrawEdge(rect, EDGE_RAISED, BF_RECT);
	//pDC->DrawEdge(rect, EDGE_RAISED, BF_LEFT | BF_BOTTOM);

	//UINT state = lpDrawItemStruct->itemState;
	//if ( state & ODS_SELECTED )	pDC->DrawEdge(rect, EDGE_ETCHED, BF_RECT);
	//else						pDC->DrawEdge(rect, EDGE_RAISED, BF_RECT);

	// draw the text if there is any
	CString strText;
	GetWindowText(strText);
	CSize Extent;
	CPoint pt;
	pDC->SelectObject(m_clFont);

	CRect textRect, clientRect, LastRect;
	GetClientRect(clientRect);
	textRect = clientRect;

	if (!strText.IsEmpty())
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(m_clrBtnText);


		//DT_BOTTOM	: 텍스트를 바닥에 정렬합니다.	DT_SINGLELINE 플래그가 지정되어 있을 경우에만 사용할 수 있습니다.
		//DT_CALCRECT : 출력될 텍스트의 너비와 높이를 계산합니다. 이 플래그가 지정되어 있을 경우 텍스트는 출력되지 않고 DrawText 함수는 높이를 리턴합니다.
		//DT_CENTER : 텍스트를 가운데 정렬합니다.
		//DT_INTERNAL : 텍스트 메트릭 계산을 위해 시스템 폰트를 사용합니다.
		//DT_NOCLIP : 화면 밖을 벗어나는 텍스트도 출력합니다. 이 플래그가 지정되었을 경우 DrawText 함수는 약간 더 빨라집니다.
		//DT_SINGLELINE : 모든 텍스트를 한 줄로 출력합니다. 멀티 라인은 무시됩니다.
		//DT_VCENTER : 텍스트를 수직 가운데에 정렬합니다. DT_SINGLELINE 플래그가 지정되어 있을 경우에만 사용할 수 있습니다.
		//DT_WORDBREAK : 텍스트가 사각 영역 끝을 넘을 경우 자동개행합니다. 이 플래그가 지정되지 않을 경우 모든 텍스트는 한 줄로 출력됩니다.

		// DT_CALCRECT 옵션이 들어가있으면 Rect로 텍스트가 출력되는 곳에대한 

		pDC->DrawText(strText, textRect, DT_CALCRECT);

		int iSizeX = textRect.right - textRect.left;
		int iSizeY = textRect.bottom - textRect.top;

		int iCurX = clientRect.right - clientRect.left;
		int iCurY = clientRect.bottom - clientRect.top;

		LastRect.top = (iCurY / 2) - (iSizeY / 2);
		LastRect.left = (iCurX / 2) - (iSizeX / 2);
		LastRect.bottom = (iCurY / 2) + (iSizeY / 2);
		LastRect.right = (iCurX / 2) + (iSizeX / 2);

		pDC->DrawText(strText, LastRect, DT_CENTER | DT_NOCLIP | ES_MULTILINE);
	}

	pDC->RestoreDC(nSavedDC);
}
