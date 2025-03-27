// ListenSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ListenSocket.h"
#include "ClientSocket.h"

// CListenSocket
CListenSocket::CListenSocket()
{

}

CListenSocket::~CListenSocket()
{
	
}


// CListenSocket 멤버 함수
void CListenSocket::OnAccept(int nErrorCode)
{
	CClientSocket* pClient = new CClientSocket;
	if(Accept(*pClient))
	{
		pClient->SetListenSocket(this);
		m_ptrClientSocketList.AddTail(pClient);

		CString sTemp = "IDCHK";

		pClient->Send(sTemp, lstrlen(sTemp) * 2);
	}
	else
	{
		delete pClient;
		sLangChange.LoadStringA(IDS_STRING1460);
		AfxMessageBox(sLangChange);	//"새 클라이언트 접속 시도 실패"
	}

	CAsyncSocket::OnAccept(nErrorCode);
}

void CListenSocket::CloseClientSocket(CAsyncSocket* pClient)
{
	POSITION pos;
	pos = m_ptrClientSocketList.Find(pClient);

	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	CString sTemp;
	int i;
	for (i=0 ; i<2 ; i ++)
	{
		if ( pFrame->m_pos[i] == pos )
		{
			sTempLang.LoadStringA(IDS_STRING1430);
			sLangChange.Format(sTempLang, i+1);
			sTemp.Format(sLangChange);	//"클라이언트 접속 종료(AA PC #%d)"
			pFrame->putListLog(sTemp);
			pFrame->func_Control_StateChange(i);
			break;
		}
	}

	if ( i == 2 )
		sLangChange.LoadStringA(IDS_STRING1296);
		sTemp.Format(sLangChange);
		pFrame->putListLog(sTemp);
		

	if(pos != NULL)
	{
		if(pClient != NULL)
		{
			pClient->ShutDown();
			pClient->Close();
		}

		m_ptrClientSocketList.RemoveAt(pos);

		CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

		for (int i=0 ; i<2 ; i++)
		{
			if ( pFrame->m_pos[i] == pos )
			{
				pFrame->m_pos[i] = NULL;
			}
		}

		delete pClient;
	}
}

bool CListenSocket::SendData(POSITION pos, CString sMessage)
{
	CClientSocket* pClient;
	
	if ( pos != NULL )
	{
		pClient = (CClientSocket*)m_ptrClientSocketList.GetAt(pos);

		if ( pClient != NULL )
		{
			if ( pClient->Send(sMessage, lstrlen(sMessage) * 2) < 0 )
			{
				return false;
			}
		}
	}

	return true;
}


bool CListenSocket::SendDataAll(CString sMessage)
{
	POSITION pos;
	pos = m_ptrClientSocketList.GetHeadPosition();

	CClientSocket* pClient = NULL;

	while(pos != NULL)
	{
		pClient = (CClientSocket*)m_ptrClientSocketList.GetNext(pos);

		if(pClient != NULL)
		{
			//if ( pClient->Send(sMessage, lstrlen(sMessage) * 2) < 0 )
			//{
			//	return false;
			//}
		}
	}

	return true;
}

