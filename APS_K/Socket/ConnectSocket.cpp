// ConnectSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
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
	CString sMsg;
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	
	pFrame->m_bisConnect = false;
	pFrame->showLanConnect();
	pFrame->m_labelMes.SetBkColor(M_COLOR_RED);
	pFrame->m_labelMes.Invalidate();
	sMsg.Format("서버와 연결이 끊겼습니다.");	//"서버와 연결이 끊겼습니다."
	errMsg2(Task.AutoFlag, sMsg);	

	// 	ShutDown();
	// 	Close();

	//pFrame->func_SocketControl_ConnectCheck();

	CSocket::OnClose(nErrorCode);
	
//	::PostQuitMessage(0);
}


void CConnectSocket::OnReceive(int nErrorCode)
{

	CString sMsg;
	CString MESMsg;

	TCHAR szBuffer[1024];

	::ZeroMemory(szBuffer, sizeof(szBuffer));
	if(Receive(szBuffer, sizeof(szBuffer)) > 0)
	{
		CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
		sLangChange.LoadStringA(IDS_STRING211);
		sMsg.Format(sLangChange, szBuffer);
		pFrame->putListLog(sMsg);

		MESMsg.Format("%s",szBuffer);

		if(MESMsg.Left(2) == "H*")
		{
			CString temp;
			AfxExtractSubString(MESCommunication.sMES_LotId, MESMsg, 1, '*');
			AfxExtractSubString(temp, MESMsg, 2, '*');

			MESCommunication.iMES_Cnt = atoi(temp);

			pFrame->putListLog(MESCommunication.sMES_LotId);
			pFrame->m_labelLotName.SetText(MESCommunication.sMES_LotId);

			sprintf_s(Task.LotNo, MESCommunication.sMES_LotId, sizeof(MESCommunication.sMES_LotId) );
			sprintf_s(Task.ChipID, MESCommunication.sMES_LotId, sizeof(MESCommunication.sMES_LotId) );
			pFrame->func_ChipID_Draw();
		}
		else
		{
			SocketDataSave(RECEIVE_DATA, szBuffer);

			if ( lstrcmp(szBuffer, "IDCHK") == 0 )
			{
				CString sTemp;
				sTemp.Format("IDAA%d", sysData.m_iUnitNo);
				pFrame->m_Socket.Send(sTemp, lstrlen(sTemp) * 2);
			}
			else
			{
				pFrame->CheckMessage(szBuffer);
			}
		}
	}

	CSocket::OnReceive(nErrorCode);
}

void CConnectSocket::OnConnect(int nErrorCode)
{
	CSocket::OnConnect(nErrorCode);
}


BOOL CConnectSocket::OnMessagePending()
{
	MSG Message;

	if ( ::PeekMessage(&Message, NULL, WM_TIMER, WM_TIMER, PM_NOREMOVE) == TRUE )
	{
		if ( Message.wParam == 999 )
		{
			::PeekMessage(&Message, NULL, WM_TIMER, WM_TIMER, PM_REMOVE);
			CancelBlockingCall();
		}
	}

	return CSocket::OnMessagePending();
}
