// ColorStatic.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ColorStatic.h"


// CColorStatic

IMPLEMENT_DYNAMIC(CColorStatic, CStatic)

CColorStatic::CColorStatic()
{
	// Set default parent window and notification message
	m_pParent = NULL;

	// Set default foreground text
	m_crTextColor = ::GetSysColor(COLOR_BTNTEXT);

	// Set default background text
	m_crBkColor = ::GetSysColor(COLOR_BTNFACE);

	// Set default background brush
	m_brBkgnd.CreateSolidBrush(m_crBkColor);
}

CColorStatic::~CColorStatic()
{
}


BEGIN_MESSAGE_MAP(CColorStatic, CStatic)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_DESTROY()
END_MESSAGE_MAP()



// CColorStatic 메시지 처리기입니다.



//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
HBRUSH CColorStatic::CtlColor(CDC* pDC, UINT nCtlColor)
{
	// TODO:  여기서 DC의 특성을 변경합니다.
	pDC->SetTextColor(m_crTextColor);
	pDC->SetBkColor(m_crBkColor);

	// TODO:  부모 처리기가 호출되지 않을 경우 Null이 아닌 브러시를 반환합니다.
	return (HBRUSH)m_brBkgnd;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CColorStatic::OnDestroy()
{
	CStatic::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// Destroy resources
	m_brBkgnd.DeleteObject();
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CColorStatic::SetTextColor(COLORREF crTextColor)
{
	// Set new foreground color
	if (crTextColor != 0xffffffff)
	{
		m_crTextColor = crTextColor;
	}
	else // Set default foreground color
	{
		m_crTextColor = ::GetSysColor(COLOR_BTNTEXT);
	}

	// Repaint control
	Invalidate();
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CColorStatic::SetBkColor(COLORREF crBkColor)
{
	// Set new background color
	if (crBkColor != 0xffffffff)
	{
		m_crBkColor = crBkColor;
	}
	else // Set default background color
	{
		m_crBkColor = ::GetSysColor(COLOR_BTNFACE);
	}

	m_brBkgnd.DeleteObject();
	m_brBkgnd.CreateSolidBrush(m_crBkColor);

	// Repaint control
	Invalidate();
}