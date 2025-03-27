// ContinuousButton.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AA Bonder.h"
#include "ContinuousButton.h"


// CContinuousButton

IMPLEMENT_DYNAMIC(CContinuousButton, CButton)

CContinuousButton::CContinuousButton()
{
}

CContinuousButton::~CContinuousButton()
{
}


BEGIN_MESSAGE_MAP(CContinuousButton, CButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// CContinuousButton 메시지 처리기입니다.




void CContinuousButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	SetTimer(100, 300, NULL);
	GetParent()->SendMessage(WM_COMMAND, MAKELONG(GetDlgCtrlID(), BN_CLICKED), (LPARAM)m_hWnd);
	CButton::OnLButtonDown(nFlags, point);
}


void CContinuousButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	KillTimer(100);
	KillTimer(200);
	KillTimer(300);
	CButton::OnLButtonUp(nFlags, point);
}


void CContinuousButton::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(nIDEvent == 100){
		GetParent()->SendMessage(WM_COMMAND, MAKELONG(GetDlgCtrlID(), BN_CLICKED), (LPARAM)m_hWnd);
		KillTimer(100);
		SetTimer(200, 100, NULL);
	}
	else if(nIDEvent == 200){
		GetParent()->SendMessage(WM_COMMAND, MAKELONG(GetDlgCtrlID(), BN_CLICKED), (LPARAM)m_hWnd);
		KillTimer(200);
		SetTimer(300, 30, NULL);
	}
	else if(nIDEvent == 300){
		GetParent()->SendMessage(WM_COMMAND, MAKELONG(GetDlgCtrlID(), BN_CLICKED), (LPARAM)m_hWnd);
	}
	CButton::OnTimer(nIDEvent);
}
