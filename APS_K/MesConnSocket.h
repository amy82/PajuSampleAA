#pragma once

// CMesConnSocket 명령 대상입니다.

class CAABonderDlg;

class CMesConnSocket : public CSocket
{
public:
	CMesConnSocket();
	virtual ~CMesConnSocket();

public:
	void SetMainDlgPtr(CAABonderDlg* pDlg) { m_pMainDlg = pDlg; }
	int IDENTITY;
private:
	void ParseRecvBuff(unsigned char* pRecvBuff, int nRecvLen);
	void ParseRecvBcrBuff(unsigned char* pRecvBuff, int nRecvLen);

	void ProcessPacket(CString sData);

private:
	CAABonderDlg* m_pMainDlg;

	unsigned char m_sPacketBuff[SIZE_OF_1K];
	int m_nPacketBuffPosi;
	bool m_bStxState;

public:
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};


