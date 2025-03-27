// ClientSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ClientSocket.h"
#include "ListenSocket.h"

// CClientSocket

CClientSocket::CClientSocket()
{

}

CClientSocket::~CClientSocket()
{
}


// CClientSocket 멤버 함수


void CClientSocket::SetListenSocket(CAsyncSocket* pSocket)
{
	m_pListenSocket = pSocket;
}

void CClientSocket::OnClose(int nErrorCode)
{
	CSocket::OnClose(nErrorCode);

	CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
	pServerSocket->CloseClientSocket(this);
}

void CClientSocket::OnReceive(int nErrorCode)
{

	CString sLog;
	TCHAR szBuffer[1024];
	::ZeroMemory(szBuffer, sizeof(szBuffer));

	if(Receive(szBuffer, sizeof(szBuffer)) > 0)
	{
		CString sTemp;
		CString MESMsg;

		sTemp.Format("%s", szBuffer);

		CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
		
		sLog.Format("[RECV] %s", szBuffer);
		pFrame->putListLog(sLog);

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
			if ( lstrcmp(sTemp.Left(2), "ID") == 0 )
			{
				CString sIPAddress;
				UINT	uPortNum;
				GetPeerName(sIPAddress, uPortNum);
				pFrame->CheckClientPosition(this, sIPAddress);
			}
			else
			{
				pFrame->ServerCheckMessage(this, sTemp);
			}
		}
	}

	CSocket::OnReceive(nErrorCode);
}
