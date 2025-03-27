// ConnectSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "../AA Bonder.h"
#include "../AA BonderDlg.h"
#include "ConnectSocket.h"


// CConnectSocket

CConnectSocket::CConnectSocket()
{
}

CConnectSocket::~CConnectSocket()
{
}


// CConnectSocket 멤버 함수


void CConnectSocket::OnClose(int nErrorCode)
{
	ShutDown();
	Close();

	CSocket::OnClose(nErrorCode);

	AfxMessageBox(_T("ERROR: Disconnected from server!"));
	::PostQuitMessage(0);
}


void CConnectSocket::OnReceive(int nErrorCode)
{
	TCHAR szBuffer[1024];
	::ZeroMemory(szBuffer, sizeof(szBuffer));

	if(Receive(szBuffer, sizeof(szBuffer)) > 0)
	{
		CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

		if ( lstrcmp(szBuffer, "IDCHK") == 0 )
		{
			CString sTemp = "ID";
			pFrame->m_Socket.Send(sTemp, lstrlen(sTemp) * 2);
		}
	}

	CSocket::OnReceive(nErrorCode);
}


void CConnectSocket::OnConnect(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CSocket::OnConnect(nErrorCode);
}


BOOL CConnectSocket::OnMessagePending()
{
	MSG Message;

	if ( ::PeekMessage(&Message, NULL, WM_TIMER, WM_TIMER, PM_NOREMOVE) == TRUE )
	{
		if ( Message.wParam == 10 )
		{
			::PeekMessage(&Message, NULL, WM_TIMER, WM_TIMER, PM_REMOVE);
			CancelBlockingCall();
		}
	}

	return CSocket::OnMessagePending();
}
