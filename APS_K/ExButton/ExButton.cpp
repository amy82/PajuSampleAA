// ExButton.cpp : implementation file
//

#include "stdafx.h"
#include "ExButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExButton

CExButton::CExButton()
{
	m_clrBtnBack = RGB(246, 246, 246);
	m_clrBtnBack_Selected = RGB(216, 216, 216);

	m_clrBtnText = RGB(0, 0, 0);
	m_clrBtnText_Selected = RGB(0, 0, 0);

	m_iStateBtn = 0;	/* Normal */

	m_clrBtnNormal = m_clrBtnBack;
	m_clrBtnOn  = RGB(0,183,0);
	m_clrBtnOn2 = RGB(250,150,250);
	m_clrBtnOFF = RGB(201,0,0);

	m_clrBtnStart  = RGB(255,0,255);
	m_bSelected = false;
}

CExButton::~CExButton()
{
}


BEGIN_MESSAGE_MAP(CExButton, CButton)
	//{{AFX_MSG_MAP(CExButton)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExButton message handlers

void CExButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);
	CRect rt;
	rt = lpDrawItemStruct->rcItem;

	if ( m_bSelected == true )
	{
		dc.FillSolidRect(rt, m_clrBtnBack_Selected);
	}
	else
	{
		
		if (m_iStateBtn==0)			m_clrBtnBack = m_clrBtnNormal;/* Normal */
		else if (m_iStateBtn==1)	m_clrBtnBack = m_clrBtnOn;/* OK */
		else if (m_iStateBtn==2)	m_clrBtnBack = m_clrBtnOFF;/* NG */
		else if (m_iStateBtn==3)	m_clrBtnBack = m_clrBtnOn2;/* motor */
		else if (m_iStateBtn==4)	m_clrBtnBack = m_clrBtnStart;/* motor */

		dc.FillSolidRect(rt, m_clrBtnBack);
	}

	UINT state = lpDrawItemStruct->itemState;
	if ( state & ODS_SELECTED )
	{
		//! if it is pressed

		dc.DrawEdge(rt, EDGE_ETCHED, BF_RECT);
	}
	else
	{
		dc.DrawEdge(rt, EDGE_BUMP, BF_RECT);
	}

	if ( m_bSelected == true )
	{
		dc.SetBkColor(m_clrBtnBack_Selected);
		dc.SetTextColor(m_clrBtnText_Selected);
	}
	else
	{
		dc.SetBkColor(m_clrBtnBack);
		dc.SetTextColor(m_clrBtnText);
	}
	
	CString szTemp = _T("");
	GetWindowText(szTemp);
	dc.DrawText(szTemp, rt, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	if ( state & ODS_FOCUS )
	{
		//! if the button is focused

		int iChange = 3;
		rt.top += iChange;
		rt.left += iChange;
		rt.right -= iChange;
		rt.bottom -= iChange;
		dc.DrawFocusRect(rt);
	}

	dc.Detach();
}
