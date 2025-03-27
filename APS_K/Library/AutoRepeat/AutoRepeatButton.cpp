// AutoRepeatButton.cpp : implementation file
//

#include "stdafx.h"
#include "AutoRepeatButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoRepeatButton

CAutoRepeatButton::CAutoRepeatButton()
{
}

CAutoRepeatButton::~CAutoRepeatButton()
{
}


BEGIN_MESSAGE_MAP(CAutoRepeatButton, CButton)
	//{{AFX_MSG_MAP(CAutoRepeatButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoRepeatButton message handlers
#define INITIAL_DELAY 500
#define REPEAT_DELAY  10
#define IDT_TIMER 1

void CAutoRepeatButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	GetParent()->SendMessage(WM_COMMAND, MAKELONG(GetDlgCtrlID(), BN_CLICKED), (LPARAM)m_hWnd);

	SetTimer(IDT_TIMER, INITIAL_DELAY, NULL);
	sent = 0;

	// JOG 전체다 요기로... 체크
	/* 이동중이면 Return */
	if(g_bMovingflag)
		return;
	g_bMovingflag =true;

	
	CButton::OnLButtonDown(nFlags, point);
}

void CAutoRepeatButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	KillTimer(IDT_TIMER);
	
	if(GetCapture() != NULL)
	{ /* release capture */
		ReleaseCapture();
		
		if(sent == 0 && (GetState() & BST_PUSHED) != 0)
		GetParent()->SendMessage(WM_COMMAND, MAKELONG(GetDlgCtrlID(), BN_CLICKED), (LPARAM)m_hWnd);
	} /* release capture */
    
	JogPlusflag = JogMinusflag =false;

	g_bMovingflag = false;
	CButton::OnLButtonUp(nFlags, point);
}

void CAutoRepeatButton::OnTimer(UINT_PTR nIDEvent) 
{
	if( (GetState() & BST_PUSHED) == 0)	return;

	SetTimer(IDT_TIMER, REPEAT_DELAY, NULL);
	GetParent()->SendMessage(WM_COMMAND, MAKELONG(GetDlgCtrlID(), BN_CLICKED), (LPARAM)m_hWnd);
	sent++;

	CButton::OnTimer(nIDEvent);
}
