// DigitST.cpp : implementation file
//

#include "stdafx.h"
#include "DigitST.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDigitST

CDigitST::CDigitST()
{
	// Default number of digits
	m_nPrecision = 2;

	// Default value
	m_nValue = 0.0f;

	// Don't display zeroes
	m_bZeroPadding = FALSE;

	// Default resize is RIGHT-BOTTOM
	m_dwResize = ST_RIGHT | ST_BOTTOM;

	m_nWidth = 0;
	m_nHeight = 0;
}


CDigitST::~CDigitST()
{
}


BEGIN_MESSAGE_MAP(CDigitST, CStatic)
	//{{AFX_MSG_MAP(CDigitST)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDigitST message handlers


void CDigitST::OnPaint() 
{
	PAINTSTRUCT lpPaint;

	BeginPaint(&lpPaint);

	CWindowDC dc(this);

	// If there is a bitmap loaded
	if (m_bmDigit.m_hObject) DrawDigits(&dc);

	EndPaint(&lpPaint);
} // End of OnPaint


BOOL CDigitST::SetStyle(UINT nBitmapId, int nPrecision)
{
	BITMAP bm;
	BOOL bRet;

	// Detach any previuos bitmap
	m_bmDigit.Detach();
	// Load new bitmap
	bRet = m_bmDigit.LoadBitmap(nBitmapId);
	// If all ok
	if (bRet == TRUE)
	{
		// Get dimension
		m_bmDigit.GetBitmap(&bm);
		// Width of a SINGLE digit in a 12 digits bitmap
		m_nWidth = (int)bm.bmWidth / 13;
		// Height of the digits
		m_nHeight = bm.bmHeight;

		SetPrecision(nPrecision);
	}

	return bRet;
} // End of SetStyle


void CDigitST::SetValue(float nValue, BOOL bRepaint)
{
	// Set new value
	m_nValue = nValue;

	// Repaint control
	if (bRepaint == TRUE) Invalidate();
} // End of SetValue


float CDigitST::GetValue()
{
	return m_nValue;
} // End of GetValue


void CDigitST::SetPrecision(int nPrecision, BOOL bResize)
{
	// Set number of digits
	// Some security
	if (nPrecision >= ST_MIN_PRECISION && nPrecision <= ST_MAX_PRECISION)
		m_nPrecision = nPrecision;

	// Resize control
	if (bResize == TRUE) Resize();
} // End of SetPrecision


int CDigitST::GetPrecision()
{
	return m_nPrecision;
} // End of GetPrecision


void CDigitST::SetResize(DWORD dwResize, BOOL bResize)
{
	m_dwResize = dwResize;

	// Resize control
	if (bResize == TRUE) Resize();
} // End of SetResize


DWORD CDigitST::GetResize()
{
	return m_dwResize;
} // End of GetResize


void CDigitST::SetZeroPadding(BOOL bPad, BOOL bRepaint)
{
	// Set new padding style
	m_bZeroPadding = bPad;

	// Repaint control
	if (bRepaint == TRUE) Invalidate();
} // End of SetZeroPadding


BOOL CDigitST::GetZeroPadding()
{
	return m_bZeroPadding;
} // End of GetZeroPadding


void CDigitST::Inc(BOOL bRepaint)
{
	SetValue(GetValue() + 1, bRepaint);
} // End of Inc


void CDigitST::Dec(BOOL bRepaint)
{
	SetValue(GetValue() - 1, bRepaint);
} // End of Dec


const char* CDigitST::GetVersionC()
{
  return "1.0";
} // End of GetVersionC


const short CDigitST::GetVersionI()
{
  return 10; // Divide by 10 to get actual version
} // End of GetVersionI


void CDigitST::DrawDigits(CDC* pDC)
{
	char szValue[ST_MAX_PRECISION+1];

	int nLoop;
	int destX;
	CRect rectCtrl;
	int nAsciiChar;
	CBitmap* pOldBitmap;

    CDC memDC;
	memDC.CreateCompatibleDC(pDC);

	// Select bitmap
	pOldBitmap = memDC.SelectObject(&m_bmDigit);
	
	GetClientRect(rectCtrl);

	// Start from more significative digit
	destX = BORDER_SPACE;

	PrepareString(szValue);

	for (nLoop = 0; nLoop < m_nPrecision; nLoop++)
	{
		if (m_bZeroPadding == TRUE && m_nValue >= 0)
			nAsciiChar = 0;
		else
			nAsciiChar = 12;

		// If included in '0'..'9'
		if (szValue[nLoop] >= '0' && szValue[nLoop] <= '9')
			nAsciiChar = szValue[nLoop] - 48;

		// If signed
		if (szValue[nLoop] == '-') nAsciiChar = 11;

		if (szValue[nLoop] == '.') nAsciiChar = 10;

		pDC->BitBlt(destX, BORDER_SPACE, m_nWidth, m_nHeight, &memDC, 0+(m_nWidth*nAsciiChar), 0, SRCCOPY);
		destX += m_nWidth;
	}

	// Restore old selected bitmap
	memDC.SelectObject(pOldBitmap);
} // End of DrawDigits


void CDigitST::Resize()
{
	CRect rectCtrl;

	Invalidate();

	// Modify control rect to fit all digits (specified by m_nPrecision)
	GetWindowRect(rectCtrl);
	GetParent()->ScreenToClient(rectCtrl);

	// Resize to RIGHT
	if (m_dwResize & ST_RIGHT)
		rectCtrl.right = rectCtrl.left + (m_nWidth * m_nPrecision)+(BORDER_SPACE*2);
	else
	// Resize to LEFT
		rectCtrl.left = rectCtrl.right - (m_nWidth * m_nPrecision)-(BORDER_SPACE*2);

	// Resize to BOTTOM
	if (m_dwResize & ST_BOTTOM)
		rectCtrl.bottom = rectCtrl.top + m_nHeight+(BORDER_SPACE*2);
	else
	// Resize to TOP
		rectCtrl.top = rectCtrl.bottom - m_nHeight-(BORDER_SPACE*2);

	MoveWindow(rectCtrl);
} // End of Resize


void CDigitST::PrepareString(char* szDest)
{
	char szStr[ST_MAX_PRECISION+1];	

	sprintf(szStr, "%*.0f", m_nPrecision,m_nValue);
	sprintf(szDest, "%*s", m_nPrecision, &szStr[strlen(szStr)-m_nPrecision]);
} // End of PrepareString


#undef ST_MIN_PRECISION
#undef ST_MAX_PRECISION
#undef BORDER_SPACE
