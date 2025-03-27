// MesConnSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MesConnSocket.h"
#include "AA Bonder.h"
#include "AA BonderDlg.h"

#define BCR_STX				0x02
#define BCR_ETX				0x03

#define BCR_CR				0x0d
// CMesConnSocket

CMesConnSocket::CMesConnSocket()
{
	m_pMainDlg = NULL;
	m_bStxState = false;
}

CMesConnSocket::~CMesConnSocket()
{
}


// CMesConnSocket 멤버 함수

//-----------------------------------------------------------------------------
//
//	OnClose
//
//-----------------------------------------------------------------------------
void CMesConnSocket::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	// MES_SOCKET = 0, BCR_SOCKET = 0, MAX_SOCKET_TYPE};
	if (m_pMainDlg != NULL)
	{
		/*if (IDENTITY == MES_SOCKET)
		{
			m_pMainDlg->DisConnectMes();
		}
		else if (IDENTITY == BCR_SOCKET)
		{
			m_pMainDlg->DisConnectBarcode();
		}*/
		m_pMainDlg->DisConnectBarcode();

	}

	CSocket::OnClose(nErrorCode);
}

//-----------------------------------------------------------------------------
//
//	OnReceive
//
//-----------------------------------------------------------------------------
void CMesConnSocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	unsigned char sRecvBuff[SIZE_OF_1K];
	memset(sRecvBuff, 0x00, sizeof(sRecvBuff));
	int nRecvLen;

	nRecvLen = this->Receive(sRecvBuff, sizeof(sRecvBuff));
	if (nRecvLen > 0)
	{
		m_bStxState = false;
		this->ParseRecvBcrBuff(sRecvBuff, nRecvLen);

	}

	CSocket::OnReceive(nErrorCode);
}

//-----------------------------------------------------------------------------
//
//	패킷 파싱
//
//-----------------------------------------------------------------------------
void CMesConnSocket::ParseRecvBuff(unsigned char* pRecvBuff, int nRecvLen)
{
	CString sData = _T("");
	int i;

	for (i = 0; i < nRecvLen; i++)
	{
		// STX 안받은 상태
		if (m_bStxState == false)
		{
			// STX 수신?
			if (pRecvBuff[i] == 'H')
			{
				memset(m_sPacketBuff, 0x00, sizeof(m_sPacketBuff));
				m_nPacketBuffPosi = 0;

				m_sPacketBuff[m_nPacketBuffPosi] = pRecvBuff[i];

				m_bStxState = true;
			}
		}
		else
		{
			if (m_nPacketBuffPosi > (sizeof(m_sPacketBuff) - 1))
			{
				m_bStxState = false;
				continue;
			}

			m_nPacketBuffPosi++;
			m_sPacketBuff[m_nPacketBuffPosi] = pRecvBuff[i];

			//if (m_sPacketBuff[m_nPacketBuffPosi] == 'T') = mes일때
			if ((m_sPacketBuff[m_nPacketBuffPosi] == 'T') && m_nPacketBuffPosi>=53)
			{
				sData = (char*)m_sPacketBuff;

				this->ProcessPacket(sData);

				m_bStxState = false;
			}
		}
	}
}

//-----------------------------------------------------------------------------
//
//	패킷 파싱
//
//-----------------------------------------------------------------------------
void CMesConnSocket::ParseRecvBcrBuff(unsigned char* pRecvBuff, int nRecvLen)
{
	CString sData = _T("");
	CString sTemp = _T("\r");
	int i;

	for (i = 0; i < nRecvLen; i++)
	{
		// STX 안받은 상태
		if (m_bStxState == false)
		{
			// STX 수신?
			if (pRecvBuff[i] == BCR_STX)
			{
				memset(m_sPacketBuff, 0x00, sizeof(m_sPacketBuff));
				m_nPacketBuffPosi = 0;

				m_sPacketBuff[m_nPacketBuffPosi] = pRecvBuff[i];

				m_bStxState = true;
			}
		}
		else
		{
			if (m_nPacketBuffPosi > (sizeof(m_sPacketBuff) - 1))
			{
				m_bStxState = false;
				continue;
			}

			m_nPacketBuffPosi++;
			m_sPacketBuff[m_nPacketBuffPosi] = pRecvBuff[i];

			if (m_sPacketBuff[m_nPacketBuffPosi] == BCR_ETX)
			{
				CString mTemp = _T("");
				mTemp = (char*)m_sPacketBuff;
				sData = mTemp.Mid(1, m_nPacketBuffPosi - 1);
				this->ProcessPacket(sData);
				m_bStxState = false;
				mTemp.Empty();
			}
		}
	}
	sData.Empty();
}
//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CMesConnSocket::ProcessPacket(CString sData)
{

	_stprintf_s(Task.ChipID, SIZE_OF_100BYTE, _T("%s"), (TCHAR*)(LPCTSTR)sData);
	theApp.MainDlg->func_ChipID_Draw();
	g_ADOData.func_AATaskToRecordID(modelList.curModelName, Task.ChipID);
	//CString sToken = _T("");
	//CString sMsg = _T("");
	//TCHAR szLog[SIZE_OF_1K];
	//// 수신 로그
	//PrintLog((TCHAR*)(LPCTSTR)sData, 00000, 0, false, 999);
	//if (sData.Left(2) == _T("H*"))
	//{
	//	AfxExtractSubString(sToken, sData, 1, _T('*'));
	//	PrintLog((TCHAR*)(LPCTSTR)sToken, 00000, 0, false, 999);
	//	//
	//	_stprintf_s(TaskWork.m_szChipID, SIZE_OF_100BYTE, _T("%s"), (TCHAR*)(LPCTSTR)sToken);
	//	AfxExtractSubString(sToken, sData, 2, _T('*'));
	//	//
	//	TaskWork.m_nMesCnt = _ttoi((TCHAR*)(LPCTSTR)sToken);

	//	CString parseTemp;
	//	CString EEpromTemp;
	//	EEpromTemp.Empty();
	//	AfxExtractSubString(EEpromTemp, sData, 3, '*');
	//	int i = 0;
	//	int j = 0;
	//	int leng = 0;
	//	int index = 0;
	//	int nCount = count((LPCTSTR)EEpromTemp, (LPCTSTR)EEpromTemp + EEpromTemp.GetLength(), _T(';'));
	//	
	//	for (i = 0; i < 5; i++)
	//	{
	//		_stprintf_s(TaskWork.mMesGetEEpromData[i], SIZE_OF_1K, _T("00"));
	//	}
	//	for (i = 0; i < nCount + 1; i++)
	//	{
	//		parseTemp.Empty();
	//		AfxExtractSubString(parseTemp, EEpromTemp, i, ';');
	//		leng = parseTemp.GetLength();
	//		leng = parseTemp.GetAllocLength();
	//		 
	//		_stprintf_s(szLog, SIZE_OF_1K, _T("[RECV]EEPROM LENGTH:[%d = %d]"), i, leng);
	//		PrintLog(szLog, 00000, 0);


	//		_stprintf_s(TaskWork.mMesGetEEpromData[i], SIZE_OF_1K, _T("%s"), parseTemp);
	//		_stprintf_s(szLog, SIZE_OF_1K, _T("[RECV]EEPROM DATA :%d[%s]"), i + 1, TaskWork.mMesGetEEpromData[i]);
	//		PrintLog(szLog, 00000, 0);

	//	}

	//	parseTemp.Empty();
	//	EEpromTemp.Empty();
	//	TaskWork.m_bRecvMesBcr = true;
	//}
	//else
	//{
	//	int nBcrCount = sData.GetLength();
	//	
	//	if (nBcrCount < 53)
	//	{
	//		_stprintf_s(szLog, SIZE_OF_1K, _T("BCR - %s"), (TCHAR*)(LPCTSTR)sData);
	//		PrintLog(szLog, 00000, 0, false, TRANSFER_UNIT);
	//		TaskWork.TransferTask.m_bBcrRead = false;
	//	}
	//	else
	//	{
	//		TaskWork.TransferTask.m_bBcrRead = true;
	//		_stprintf_s(TaskWork.TransferTask.m_szLoadBcr, SIZE_OF_100BYTE, _T("%s"), (TCHAR*)(LPCTSTR)sData);
	//		_stprintf_s(szLog, SIZE_OF_1K, _T("BCR - %s"), (TCHAR*)(LPCTSTR)TaskWork.TransferTask.m_szLoadBcr);
	//		PrintLog(szLog, 00000, 0, false, TRANSFER_UNIT);
	//		MainDlg->ShowBarcode(TaskWork.TransferTask.m_szLoadBcr);
	//		//여기서 MES 가상포트로 신호 날려라 200402
	//		char szBuff[SIZE_OF_100BYTE];
	//		if (ModelData.m_nMesPass == 0)	//m_clSerialThread.m_bMesBcrOpen == true && 
	//		{
	//			//Mes사용시 가상포트로 보낸후 mes에서 리턴받고 AA로 보낸다.
	//			sprintf_s(szBuff, SIZE_OF_100BYTE, "%s\r", TaskWork.TransferTask.m_szLoadBcr);
	//			MainDlg->m_clSerialThread.SendMesBcrReadSet(szBuff);
	//			_stprintf_s(szLog, SIZE_OF_100BYTE, _T("Send to 가상 Mes - %s"), (TCHAR*)(LPCTSTR)TaskWork.TransferTask.m_szLoadBcr);
	//			PrintLog(szLog, 00000, 0, false, TRANSFER_UNIT);
	//			TaskWork.m_bRecvMesBcr = false;
	//		}
	//	}

	//}

	//sToken.Empty();
	//sMsg.Empty();
}