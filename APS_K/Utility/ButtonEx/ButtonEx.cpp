// ButtonEx.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ButtonEx.h"


// CButtonEx

IMPLEMENT_DYNAMIC(CButtonEx, CButton)

CButtonEx::CButtonEx(BOOL bReadOnly/* = TRUE*/, BOOL bDepressed/* = FALSE*/, BOOL bCenterAlign/* = TRUE*/)
{
	m_bMove = false;
	m_bSelected = false;
	m_bBlink = false;
	m_dwTimeOver = 0;
	m_nUseBlink = 0;
	m_bCenterAlign = bCenterAlign;
	m_nMargin = DEFAULT_MARGIN;
	m_bReadOnly = bReadOnly;
	m_dwBlinkTime = 500;
	m_clFont.CreateFont(25, 9, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
}

CButtonEx::~CButtonEx()
{
}


BEGIN_MESSAGE_MAP(CButtonEx, CButton)
END_MESSAGE_MAP()



// CButtonEx 메시지 처리기입니다.


//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CButtonEx::SetCtrlFont(int nHeight, int nWidth, CString szFontName)
{
	m_clFont.DeleteObject();
	m_clFont.CreateFont(nHeight, nWidth, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, szFontName);
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CButtonEx::SetImage(UINT nID, UINT nImgWidth)
{
	m_imgList.Create(nID, nImgWidth);
	m_rcImage = m_imgList.GetImageDimension();
	m_ptCenter.x = 0;			//m_ptCenter.x - m_rcImage.cx/2;
	m_ptCenter.y = 0;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CButtonEx::SetPress(int nDraw)
{
	if (nDraw != m_nDrawImg)
	{
		m_nDrawImg = nDraw;
		RedrawWindow();
	}

	if (m_bBlink == true)
	{
		int nBlink = 0;
		nBlink = this->GetBlinkCtrl(0, 3);
		if (nBlink != m_nUseBlink)
		{
			m_nUseBlink = nBlink;
			RedrawWindow();
		}
	}
	return;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
int CButtonEx::GetBlinkCtrl(int nFirst, int nSecond)
{
	int nBlinkNo = m_nUseBlink;
	if ((GetTickCount() - m_dwTimeOver) > m_dwBlinkTime)
	{
		if (nBlinkNo == nFirst)	nBlinkNo = nSecond;
		else					nBlinkNo = nFirst;

		m_dwTimeOver = GetTickCount();
	}

	return  nBlinkNo;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CButtonEx::SetSelected(bool bClick)
{
	if (m_bSelected != bClick)
	{
		m_bSelected = bClick;
		Invalidate();
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CButtonEx::SetMoveCtrl(bool bMove)
{
	if (m_bMove != bMove && m_bBlink == false)
	{
		m_bMove = bMove;
		Invalidate();
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CButtonEx::SetBlink(bool bBlink)
{
	if (m_bBlink != bBlink)
	{
		m_bBlink = bBlink;
		RedrawWindow();
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CButtonEx::SetBlinkTime(DWORD dwInterval)
{
	m_dwBlinkTime = dwInterval;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
int	CButtonEx::GetDrawIndex()
{
	return m_nDrawImg;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CButtonEx::PreSubclassWindow()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	// make sure we are an owner draw button
	ModifyStyle(0, BS_OWNERDRAW);

	CRect rect;
	GetClientRect(rect);

	LOGFONT lf;
	GetFont()->GetLogFont(&lf);
	m_nRadius = lf.lfHeight;
	if (m_nRadius == 0)	m_nRadius = 15;
	if (m_nRadius < 0)		m_nRadius = (-1)*m_nRadius;
	m_nRadius = (int)(rect.bottom*0.5) - 5;

	// don't let the button get above this maximum radius
	// user can reset m_nRadius later, if desired
	if (m_nRadius > 6)
		m_nRadius = 6;

	m_ptCenter.x = rect.left + m_nRadius + 1;
	if (m_bCenterAlign)
		m_ptCenter.y = rect.top + (int)(rect.Height()*0.5 + 0.5);
	else
		m_ptCenter.y = rect.top + m_nRadius + 1;

	CButton::PreSubclassWindow();
}


void CButtonEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  지정된 항목을 그리는 코드를 추가합니다.
	ASSERT(lpDrawItemStruct != NULL);
	if (lpDrawItemStruct->itemAction != ODA_DRAWENTIRE)
		return;

	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rect = lpDrawItemStruct->rcItem;

	int nSavedDC = pDC->SaveDC();

	pDC->SelectStockObject(NULL_BRUSH);
	pDC->FillSolidRect(rect, ::GetSysColor(COLOR_BTNFACE));

	if (m_bBlink == true)
	{
		m_bSelected = false;
		m_bMove = false;
		m_imgList.Draw(pDC, m_nUseBlink/*Get_ShineCtrl(1, 2)*/, m_ptCenter);
	}
	else if (m_bSelected == true || m_bMove == true)
	{
		m_imgList.Draw(pDC, 2, m_ptCenter);
	}
	else
	{
		m_imgList.Draw(pDC, m_nDrawImg, m_ptCenter);
	}

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
		pDC->SetTextColor(RGB(255, 255, 255));

		// DT_CALCRECT 옵션이 들어가있으면 Rect로 텍스트가 출력되는 곳에대한 
		pDC->DrawText(strText, textRect, DT_CENTER | DT_NOPREFIX | DT_WORDBREAK | DT_CALCRECT);

		int iSizeX = textRect.right - textRect.left;
		int iSizeY = textRect.bottom - textRect.top;
		int iCurX = clientRect.right - clientRect.left;
		int iCurY = clientRect.bottom - clientRect.top;

		LastRect.left = (iCurX / 2) - (iSizeX / 2);
		LastRect.top = (iCurY / 2) - (iSizeY / 2) - 2;	//글씨 위쪽 공간이 조금씩 있나봐..   -2 해줘야되

		pDC->TextOut(LastRect.left, LastRect.top, strText);

	}

	pDC->RestoreDC(nSavedDC);
}
