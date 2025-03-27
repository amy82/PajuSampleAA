#pragma once


// CListenSocket 명령 대상입니다.

class CListenSocket : public CAsyncSocket
{
public:
	CListenSocket();
	virtual ~CListenSocket();

	
	CPtrList	m_ptrClientSocketList;

	virtual void OnAccept(int nErrorCode);
	void CloseClientSocket(CAsyncSocket* pClient);
	bool SendData(POSITION pos, CString sMessage);
	bool SendDataAll(CString sMessage);
};
