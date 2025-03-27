#include "stdafx.h"
#include "CommThread.h"
#include "../../AA Bonder.h"
#include "../../AA BonderDlg.h"

// 메세지를 받을 윈도우 핸들, 부모 윈도우에서 HWND hCommWnd= this->m_hWnd로
// 설정해 준다.

BYTE HEADER_SIZE = 3;
BYTE CRC_SIZE = 1;

/* Header Index */
BYTE SOCIF_FRAME_SOF = 0xFF;
BYTE SOCIF_HEADERINDEX_SOF = 0;
BYTE SOCIF_HEADERINDEX_ID_AND_TYPE = 1;
BYTE SOCIF_HEADERINDEX_BODYLEN = 2;

/* Packet Index */
BYTE SOCIF_FRAME_INDEX_SOF = 0;
BYTE SOCIF_FRAME_INDEX_MESSAGE_ID_AND_TYPE = 1;
BYTE SOCIF_FRAME_INDEX_TYPE = 2;
BYTE SOCIF_FRAME_INDEX_BODYLENGTH = 3;
BYTE SOCIF_FRAME_INDEX_BODY = 4;
// CQueue 구현부========================================= 
 
// Queue의 생성자
struct _OC_RW22
{
	BYTE RW;
	BYTE ShiftCx;
	BYTE ShiftCy;
}OC_RW22;


CQueue::CQueue()
{
	Clear();
}

// Queue를 초기화
void CQueue::Clear()
{
	m_iHead = m_iTail = 0;
	memset(buff, 0, BUFF_SIZE);
}

// Queue에 들어 있는 자료 개수.
int CQueue::GetSize()
{
	return (m_iHead - m_iTail + BUFF_SIZE) % BUFF_SIZE;
}

// Queue에 1 byte 넣음.
BOOL CQueue::PutByte(BYTE b)
{
	if (GetSize() == (BUFF_SIZE-1)) return FALSE;
	buff[m_iHead++] = b;
	m_iHead %= BUFF_SIZE;

	return TRUE;
}

// Queue에서 1 byte 꺼냄.
BOOL CQueue::GetByte(BYTE* pb)
{
	if (GetSize() == 0) return FALSE;
	*pb = buff[m_iTail++];
	m_iTail %= BUFF_SIZE;

	return TRUE;
}

// 포트 sPortName을 dwBaud 속도로 연다.
// ThreadWatchComm 함수에서 포트에 무언가 읽혔을 때 MainWnd에 알리기
// 위해 WM_COMM_READ메시지를 보낼때 같이 보낼 wPortID값을 전달 받는다.
BOOL CCommThread::OpenPort(CString m_stPort,CString m_stBaud,CString m_stDatabit,
						   	CString m_stFlow,CString m_stParity,CString m_stStop)
{
	// Local 변수.
	COMMTIMEOUTS	timeouts;
	DCB				dcb;
	DWORD			dwThreadID;

	// 변수 초기화

	// overlapped structure 변수 초기화.
	m_osRead.Offset = 0;
	m_osRead.OffsetHigh = 0;
	if (! (m_osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)))	
		return FALSE;
	m_osWrite.Offset = 0;
	m_osWrite.OffsetHigh = 0;
	if (! (m_osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)))
		return FALSE;
	
	// 포트 열기
	m_hComm = CreateFile( m_stPort, 
		GENERIC_READ | GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 
		NULL);
	if (m_hComm == (HANDLE) -1) return FALSE;

	// 포트 상태 설정.

	// EV_RXCHAR event 설정
//	SetCommMask( m_hComm, EV_RXCHAR);	

//	WaitCommEvent( m_hComm, NULL, NULL);// ********
	// InQueue, OutQueue 크기 설정.
	SetupComm( m_hComm, 4096, 4096);	

	// 포트 비우기.
	PurgeComm( m_hComm,	PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR);

	// timeout 설정.
	GetCommTimeouts( m_hComm, &timeouts);
	timeouts.ReadIntervalTimeout = 0xFFFFFFFF;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.ReadTotalTimeoutConstant = 0;
	timeouts.WriteTotalTimeoutMultiplier = 2* CBR_9600 / atol(m_stBaud);
	timeouts.WriteTotalTimeoutConstant = 0;
	SetCommTimeouts( m_hComm, &timeouts);

	// dcb 설정
	dcb.DCBlength = sizeof(DCB);
	GetCommState( m_hComm, &dcb);	// 예전 값을 읽음.
	dcb.BaudRate = atol(m_stBaud);
	dcb.ByteSize = atoi(m_stDatabit);
	dcb.Parity = m_stParity.GetLength()-2;
	dcb.StopBits = static_cast<int>(atof(m_stStop)*2-2);


	if (m_stFlow.Compare("XON/XOFF")==0) 
	{
		dcb.fInX = dcb.fOutX = 1;		// Xon, Xoff 사용.
	}
	else
	{
		dcb.fInX = dcb.fOutX = 0;
	}
	if (m_stFlow.Compare("HARDWARE")==0)
	{
		dcb.fOutxCtsFlow = 1;
		dcb.fOutxDsrFlow = 1;
		dcb.fDtrControl  = 2;
		dcb.fRtsControl  = 2;
	}
	else
	{
		dcb.fOutxCtsFlow = 0;
		dcb.fOutxDsrFlow = 0;
		dcb.fDtrControl  = 1;
		dcb.fRtsControl  = 1;
	}

	dcb.XonChar = ASCII_XON;
	dcb.XoffChar = ASCII_XOFF;
	dcb.XonLim = 100;
	dcb.XoffLim = 100;
	if (! SetCommState( m_hComm, &dcb))	return FALSE;

	// 포트 감시 쓰레드 생성.
	m_bConnected = TRUE;
	m_hThreadWatchComm = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)ThreadWatchComm, this, 0, &dwThreadID);
	if (! m_hThreadWatchComm)
	{
		ClosePort();
		return FALSE;
	}

	return TRUE;
}
	
// 포트를 닫는다.
void CCommThread::ClosePort()
{
	m_bConnected = FALSE;
	SetCommMask( m_hComm, 0);
	PurgeComm( m_hComm,					
		PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR);
	CloseHandle( m_hComm);
}

// 포트에 pBuff의 내용을 nToWrite만큼 쓴다.
// 실제로 쓰여진 Byte수를 리턴한다.
DWORD CCommThread::WriteComm(BYTE *pBuff, DWORD nToWrite)
{
	DWORD	dwWritten, dwError, dwErrorFlags;
	COMSTAT	comstat;

	if (! WriteFile( m_hComm, pBuff, nToWrite, &dwWritten, &m_osWrite))
	{
		if (GetLastError() == ERROR_IO_PENDING)
		{
			// 읽을 문자가 남아 있거나 전송할 문자가 남아 있을 경우 Overapped IO의
			// 특성에 따라 ERROR_IO_PENDING 에러 메시지가 전달된다.
			//timeouts에 정해준 시간만큼 기다려준다.
			while (! GetOverlappedResult( m_hComm, &m_osWrite, &dwWritten, TRUE))
			{
				dwError = GetLastError();
				if (dwError != ERROR_IO_INCOMPLETE)
				{
					ClearCommError( m_hComm, &dwErrorFlags, &comstat);
					break;
				}
			}
		}
		else
		{
			dwWritten = 0;
			ClearCommError( m_hComm, &dwErrorFlags, &comstat);
		}
	}

	return dwWritten;
}

// 포트로부터 pBuff에 nToWrite만큼 읽는다.
// 실제로 읽혀진 Byte수를 리턴한다.
DWORD CCommThread::ReadComm(BYTE *pBuff, DWORD nToRead)
{
	DWORD	dwRead, dwError, dwErrorFlags;
	COMSTAT	comstat;

	//----------------- system queue에 도착한 byte수만 미리 읽는다.
	ClearCommError( m_hComm, &dwErrorFlags, &comstat);
	dwRead = comstat.cbInQue;
	
	if (dwRead > 0)
	{
		//nToRead = 읽을 최대 바이트 수
		//dwRead = 동기 hFile 매개 변수를 사용할 때 읽은 바이트 수를 수신하는 변수에 대한 포인터 
		//DWORD = unsigned long   -1~1
		//UINT = unsigned int 0~1
		if (!ReadFile(m_hComm, pBuff, nToRead, &dwRead, &m_osRead))

		{
			if (GetLastError() == ERROR_IO_PENDING)
			{
				//--------- timeouts에 정해준 시간만큼 기다려준다.
				while (! GetOverlappedResult( m_hComm, &m_osRead, &dwRead, TRUE))
				{
					dwError = GetLastError();
					if (dwError != ERROR_IO_INCOMPLETE)
					{
						ClearCommError( m_hComm, &dwErrorFlags, &comstat);
						break;
					}
				}
			}
			else
			{
				dwRead = 0;
				ClearCommError( m_hComm, &dwErrorFlags, &comstat);
			}
		}
	}

	return dwRead;
}

// 포트를 감시하고, 읽힌 내용이 있으면 
// m_ReadData에 저장한 뒤에 MainWnd에 메시지를 보내어 Buffer의 내용을
// 읽어가라고 신고한다.

DWORD	ThreadWatchComm(CCommThread* pComm)
{
	DWORD		dwEvent;
	OVERLAPPED	os;
	BOOL		bOk = TRUE;
	//BYTE		buff[1024];	 // 읽기 버퍼//BYTE		buff[2048];	 // 읽기 버퍼
	DWORD		dwRead;	 // 읽은 바이트수.

	// Event, OS 설정.
	memset( &os, 0, sizeof(OVERLAPPED));
	if (! (os.hEvent = CreateEvent( NULL, TRUE, FALSE, NULL)))
		bOk = FALSE;
	if (! SetCommMask( pComm->m_hComm, EV_RXCHAR))
		bOk = FALSE;
	if (! bOk)
	{
		AfxMessageBox("Error while creating ThreadWatchComm, " + pComm->m_sPortName);
		return FALSE;
	}

	// 포트를 감시하는 루프.
	while (pComm->m_bConnected)
	{
		dwEvent = 0;

		// 포트에 읽을 거리가 올때까지 기다린다.
		WaitCommEvent( pComm->m_hComm, &dwEvent, NULL);
		
		if ((dwEvent & EV_RXCHAR) == EV_RXCHAR)
		{
			// 포트에서 읽을 수 있는 만큼 읽는다.
			do	
			{
				try
				{
					dwRead = pComm->ReadComm(pComm->recvBuffer, 256);//dwRead = pComm->ReadComm( buff, 2048);
					pComm->nSizeReceived += (UINT)dwRead;
					//==========================================================================================================
					while (true)
					{
						if (pComm->ProcessPacket2() <= 0)
							break;
					}
				}
				catch (CException* e)
				{
					pComm->nSizeReceived = 0;
				}
				//============================================================================================================
				/*
				//주석처리 181227_1
				if (BUFF_SIZE - pComm->m_QueueRead.GetSize() > (int)dwRead)
				{
					for (WORD i = 0; i < dwRead; i++) {
						pComm->m_QueueRead.PutByte(buff[i]);
					}

				}
				else {
					AfxMessageBox("m_QueueRead FULL!");
				}*/
			} while (dwRead);
			//	읽어 가도록 메시지를 보낸다.
			if (!(pComm->m_bReserveMsg))
			{
				pComm->m_bReserveMsg = true;
				::PostMessage(pComm->hCommWnd, WM_COMM_READ, pComm->m_wPortID, 0);
			}
		}
	}	
	
	// 포트가 ClosePort에 의해 닫히면 m_bConnected 가 FALSE가 되어 종료.

	CloseHandle( os.hEvent);
	pComm->m_hThreadWatchComm = NULL;

	return TRUE;
}
int CCommThread::ProcessPacket2()
{
	if (nSizeReceived <= HEADER_SIZE)//HEADER_SIZE = 3
		return 0;

	BYTE bodyStart = (BYTE)ReceiveFrameCheck();
	if (bodyStart == 0)
	{
		nSizeReceived = 0;
		return 0;
	}

	BYTE headStart = (BYTE)(bodyStart - HEADER_SIZE);

	BYTE Identifier = recvBuffer[headStart];
	BYTE nType = (BYTE)(recvBuffer[headStart + 1] >> 6);
	BYTE nID = (BYTE)(recvBuffer[headStart + 1] & 0x3F);
	BYTE nBodyLen = recvBuffer[headStart + 2];
	BYTE nCRC = recvBuffer[HEADER_SIZE + nBodyLen];
	BYTE nCrcStartValue = 0;

	if (nSizeReceived < HEADER_SIZE + nBodyLen + CRC_SIZE)
	{
		//    nSizeReceived = 0;
		return 0;
	}


	DWORD nSizeToHandle = (DWORD)(HEADER_SIZE + nBodyLen + CRC_SIZE);
	DWORD nRemainder = nSizeReceived - nSizeToHandle;

	if (nCRC != CRC_CalculateCRC8(recvBuffer, HEADER_SIZE + nBodyLen, nCrcStartValue))
	{
//		Console.WriteLine("CRC is not correct..Packet Loss Count");
		nSizeReceived = 0;
		return 0;
	}

	for (int i = 0; i < nBodyLen; i++)
	{
		body_buffer[i] = recvBuffer[i + HEADER_SIZE];
	}


	switch (nID)
	{
	/*case MESSAGEID_EEPROM_WRITE_READ:
		EEPROM_READ(body_buffer, nBodyLen);
		break;
	case MESSAGEID_HEARTBEAT:
		HeartBeatRead(body_buffer, nBodyLen);
		break;
	case MESSAGEID_OC_WRITE_READ:
		OCRead(body_buffer, nBodyLen);
		break;*/
	case 0x02:	//MESSAGEID_HEARTBEAT = 0x02;
		//HeartBeatRead(body_buffer, nBodyLen);
		//theApp.MainDlg->putListLog("HeartBeatRead");
		break;
	case 0x04:	//MESSAGEID_SENSOR_RW = 0x04;
		theApp.MainDlg->putListLog("ooookk");
		if (FittingIndex <= 12)
		{
			FittingIndex++;
			FittingSet();
		}
		
		//SensorRead(body_buffer, nBodyLen);		//보여주는 부분 콘솔에
		break;
	default: break;
	}

	//Buffer.BlockCopy(packet_buffer, 0, m_QueueRead.buff, 0, (int)1024);
	memcpy(recvBuffer, packet_buffer, sizeof(recvBuffer));
	//this.Refresh();
	//this.Invalidate();

	//   nSizeReceived -= nSizeToHandle;

	nSizeReceived = 0;
	return 0;// (int)nSizeToHandle;
}



int CCommThread::ReceiveFrameCheck()
{

	BYTE nParsingIndex = SOCIF_FRAME_INDEX_SOF;
	BYTE nID = 0;
	BYTE readCount = 0;

	BYTE nExpectedBodyLen[4];// = { 96,1,3,10 };
	nExpectedBodyLen[0] = 96;
	nExpectedBodyLen[1] = 1;
	nExpectedBodyLen[2] = 3;
	nExpectedBodyLen[3] = 10;
	for (int i = 0; i<nSizeReceived; i++)
	{

		BYTE rxData = recvBuffer[i];//m_QueueRead.buff[i];

		if (nParsingIndex == SOCIF_FRAME_INDEX_SOF)
		{
			if (rxData == SOCIF_FRAME_SOF)
			{
				nParsingIndex = SOCIF_FRAME_INDEX_MESSAGE_ID_AND_TYPE;
			}
			else
			{
				;

			}
		}
		else if (nParsingIndex == SOCIF_FRAME_INDEX_MESSAGE_ID_AND_TYPE)
		{
			nID = (BYTE)(rxData & 0x3F);

			if (nID <= 0x04)//MESSAGEID_SENSOR_RW)
			{
				nParsingIndex = SOCIF_FRAME_INDEX_BODYLENGTH;
			}
			else
			{
				nParsingIndex = SOCIF_FRAME_INDEX_SOF;
			}
		}
		else if (nParsingIndex == SOCIF_FRAME_INDEX_BODYLENGTH)
		{
			if (nExpectedBodyLen[nID - 1] == rxData)
			{
				nParsingIndex = SOCIF_FRAME_INDEX_BODY;
				readCount = 0;
			}
			else
			{
				nParsingIndex = SOCIF_FRAME_INDEX_SOF;
			}
		}
		else if (nParsingIndex == SOCIF_FRAME_INDEX_BODY)
		{
			return i;
		}
	}

	return 0;
}



CCommThread::CCommThread()
{
	nSizeReceived = 0;
	m_bConnected = FALSE;
	m_bReserveMsg = FALSE;
	hCommWnd = NULL;
	
}
CStringArray* CCommThread::GetPorts(){
	CStringArray* ComPorts = new CStringArray;
    HKEY  hSerialCom;
    TCHAR buffer[_MAX_PATH], data[_MAX_PATH];
    DWORD len, type, dataSize;
    long  i;

    if (::RegOpenKeyEx(HKEY_LOCAL_MACHINE, 
                       _T("HARDWARE\\DEVICEMAP\\SERIALCOMM"), 
                       0, 
                       KEY_ALL_ACCESS, 
                       &hSerialCom) == ERROR_SUCCESS)
    {
        for (i=0, len=dataSize=_MAX_PATH; 
            ::RegEnumValue(hSerialCom, 
                           i, 
                           buffer, 
                           &len, 
                           NULL, 
                           &type, 
                           (unsigned char*)data,
                           &dataSize)==ERROR_SUCCESS; i++, len=dataSize=_MAX_PATH)
        {
                data[dataSize-1] = NULL;
                //if (strncmp(data, "COM", 3) == 0)
				ComPorts->Add(data);
        }
 
 
        ::RegCloseKey(hSerialCom);
    }
	return ComPorts;
}
void CCommThread::EdgeOff()
{
	BYTE  edgeData[45] =
	{
		0xF8, 0x10, 0x60, 0xF0 ,
		0xB8, 0x01, 0x60, 0xF0 ,
		0xBC, 0x01, 0x60, 0xF0 ,
		0xC0, 0x01, 0x60, 0xF0 ,
		0xC4, 0x01, 0x60, 0xF0 ,
		0xC8, 0x01, 0x60, 0xF0 ,
		0xCC, 0x01, 0x60, 0xF0 ,
		0xD0, 0x01, 0x60, 0xF0 ,
		0xD4, 0x01, 0x60, 0xF0 ,
		0xD8, 0x01, 0x60, 0xF0 ,
		0xDC, 0x01, 0x60, 0xF0
	};

	ComposePacket(MESSAGEID_SENSOR_RW, MESSAGETYPE_NOTIFICATION, (BYTE)sizeof(SENSOR_RW), edgeData);
}
void CCommThread::FittingSet()
{
	theApp.MainDlg->putListLog("AVM UART FittingSet");
	BYTE   fittingAddress[49] = {
		0xA8, 0x09, 0x60, 0xF0 ,
		0xAC, 0x09, 0x60, 0xF0 ,
		0xB0, 0x09, 0x60, 0xF0 ,
		0xB4, 0x09, 0x60, 0xF0 ,
		0xB8, 0x09, 0x60, 0xF0 ,
		0xBC, 0x09, 0x60, 0xF0 ,
		0xC0, 0x09, 0x60, 0xF0 ,
		0xC4, 0x09, 0x60, 0xF0 ,
		0xC8, 0x09, 0x60, 0xF0 ,
		0xCC, 0x09, 0x60, 0xF0 ,
		0xD0, 0x09, 0x60, 0xF0 ,
		0xD4, 0x09, 0x60, 0xF0
	};

	ComposePacketFittingSet(MESSAGEID_SENSOR_RW, MESSAGETYPE_NOTIFICATION, (BYTE)sizeof(SENSOR_RW), fittingAddress);
}
void CCommThread::ComposePacket_oc(BYTE nID, BYTE nType, BYTE nBodyLength, BYTE* arrBody)
{
	BYTE arrBody__[3];
	arrBody__[0] = 1;
	arrBody__[1] = 20;
	arrBody__[2] = 10;

	/*BYTE RW;
	unsigned int Address;
	BYTE length;
	unsigned int data;*/

	// todo: handle Message Type
	int	nWritten = 0;

	// todo: handle Message Type
	BYTE     nCRC = 0;
	BYTE nCrcStartValue = 0;

	// todo: CRC calculation.
	BYTE i;
	BYTE* tmpArrPacket = new BYTE[HEADER_SIZE + nBodyLength];


	BYTE	___arrHeader[3];
	___arrHeader[SOCIF_HEADERINDEX_SOF] = SOCIF_FRAME_SOF;
	___arrHeader[SOCIF_HEADERINDEX_ID_AND_TYPE] = nID;
	___arrHeader[SOCIF_HEADERINDEX_ID_AND_TYPE] = (BYTE)(___arrHeader[SOCIF_HEADERINDEX_ID_AND_TYPE] | (nType << 6));
	___arrHeader[SOCIF_HEADERINDEX_BODYLEN] = nBodyLength;


	for (i = 0; i < HEADER_SIZE; i++)
	{
		tmpArrPacket[i] = ___arrHeader[i];
	}
	for (i = 0; i < nBodyLength; i++)
	{
		tmpArrPacket[i + HEADER_SIZE] = arrBody__[i];
	}

	WriteComm(___arrHeader, HEADER_SIZE);
	Sleep(1);//
	WriteComm(arrBody__, nBodyLength);
	Sleep(1);//

	nCRC = CRC_CalculateCRC8(tmpArrPacket, HEADER_SIZE + nBodyLength, nCrcStartValue);
	tmpArrPacket[HEADER_SIZE + nBodyLength - 3] = nCRC;

	WriteComm(&nCRC, 1);
	delete[] tmpArrPacket;
}
void CCommThread::ComposePacketFittingSet(BYTE nID, BYTE nType, BYTE nBodyLength, BYTE* arrBody)
{
	int	nWritten = 0;
	BYTE nCRC = 0;
	BYTE nCrcStartValue = 0;
	// todo: CRC calculation.
	BYTE i;
	BYTE* tmpArrPacket = new BYTE[HEADER_SIZE + nBodyLength];
	BYTE BodyWrite[10];
	BYTE	___arrHeader[3];
	___arrHeader[SOCIF_HEADERINDEX_SOF] = SOCIF_FRAME_SOF;
	___arrHeader[SOCIF_HEADERINDEX_ID_AND_TYPE] = nID;
	___arrHeader[SOCIF_HEADERINDEX_ID_AND_TYPE] = (BYTE)(___arrHeader[SOCIF_HEADERINDEX_ID_AND_TYPE] | (nType << 6));
	___arrHeader[SOCIF_HEADERINDEX_BODYLEN] = nBodyLength;

	BYTE   fittingData[13] = {
		0x40, 0xF0, 0x40, 0xF0,
		0x40, 0xF0, 0x00, 0x40,
		0xF0, 0x00, 0x40, 0xF0
	};

	for (i = 0; i < HEADER_SIZE; i++)
	{
		tmpArrPacket[i] = ___arrHeader[i];
	}
	int FittingSetLen = 12;//12;
	for (int i = FittingIndex; i < FittingIndex+1; i++)
	{
		BodyWrite[0] = 1;
		for (int j = 0; j < 4; j++)
		{
			BodyWrite[j + 1] = arrBody[(i * 4) + j];//1,2,3,4
			if (j == 0)
			{
				//fittingData
				BodyWrite[j + 6] = fittingData[i];
			}
			else
			{
				BodyWrite[j + 6] = 0x00;
			}

		}
		BodyWrite[5] = 10;

		for (int k = 0; k < nBodyLength; k++)
		{
			tmpArrPacket[k + HEADER_SIZE] = BodyWrite[k];
		}
		nCRC = CRC_CalculateCRC8(tmpArrPacket, HEADER_SIZE + nBodyLength, nCrcStartValue);
//--------------------------------------------------------------------------
		WriteComm(___arrHeader, HEADER_SIZE);
		WriteComm(BodyWrite, nBodyLength);
		WriteComm(&nCRC, 1);
	}
	delete[] tmpArrPacket;
}
void CCommThread::ComposePacket(BYTE nID, BYTE nType, BYTE nBodyLength, BYTE* arrBody)
{
	int	nWritten = 0;
	BYTE nCRC = 0;
	BYTE nCrcStartValue = 0;
	BYTE i;
	BYTE* tmpArrPacket = new BYTE[HEADER_SIZE + nBodyLength];
	BYTE bytesForWrite[10];
	BYTE	___arrHeader[3];
	___arrHeader[SOCIF_HEADERINDEX_SOF] = SOCIF_FRAME_SOF;
	___arrHeader[SOCIF_HEADERINDEX_ID_AND_TYPE] = nID;
	___arrHeader[SOCIF_HEADERINDEX_ID_AND_TYPE] = (BYTE)(___arrHeader[SOCIF_HEADERINDEX_ID_AND_TYPE] | (nType << 6));
	___arrHeader[SOCIF_HEADERINDEX_BODYLEN] = nBodyLength;

	 for(i = 0; i < HEADER_SIZE; i++)
	{
		tmpArrPacket[i] = ___arrHeader[i];
	}
	 int EdgeLen = 11;
	 for (int i = 0; i < EdgeLen; i++)
	 {
		 bytesForWrite[0] = 1;
		 for (int j = 0; j < 4; j++)
		 {
			 bytesForWrite[j+1] = arrBody[(i*4)+j];
			  if (i == 0 && j==0)
			 {
				 bytesForWrite[j+6] = 0x20;
			 }
			 else
			 {
				 bytesForWrite[j+6] = 0x00;
			 }
		 }
		 bytesForWrite[5] = 10;
		
		 for (int k = 0; k < nBodyLength; k++)
		 {
			 tmpArrPacket[k + HEADER_SIZE] = bytesForWrite[k];
		 }
		 nCRC = CRC_CalculateCRC8(tmpArrPacket, HEADER_SIZE + nBodyLength, nCrcStartValue);
		 //-----------------------------------------------------------------------------------------------
		 WriteComm(___arrHeader, HEADER_SIZE); 
		 WriteComm(bytesForWrite, nBodyLength);
		
		 WriteComm(&nCRC, 1);
	 }
	 delete[] tmpArrPacket;
}
 BYTE CCommThread::CRC_CalculateCRC8(BYTE* Crc_DataPtr, int Crc_Length, BYTE Crc_StartValue8)
 {
        int count;
			
//
//BYTE* Crc8Table = new BYTE[256]{
BYTE Crc8Table[256] ={
	0x00, 0x1d, 0x3a, 0x27,
	0x74, 0x69, 0x4e, 0x53,
	0xe8, 0xf5, 0xd2, 0xcf,
	0x9c, 0x81, 0xa6, 0xbb,
	0xcd, 0xd0, 0xf7, 0xea,
	0xb9, 0xa4, 0x83, 0x9e,
	0x25, 0x38, 0x1f, 0x02,
	0x51, 0x4c, 0x6b, 0x76,
	0x87, 0x9a, 0xbd, 0xa0,
	0xf3, 0xee, 0xc9, 0xd4,
	0x6f, 0x72, 0x55, 0x48,
	0x1b, 0x06, 0x21, 0x3c,
	0x4a, 0x57, 0x70, 0x6d,
	0x3e, 0x23, 0x04, 0x19,
	0xa2, 0xbf, 0x98, 0x85,
	0xd6, 0xcb, 0xec, 0xf1,
	0x13, 0x0e, 0x29, 0x34,
	0x67, 0x7a, 0x5d, 0x40,
	0xfb, 0xe6, 0xc1, 0xdc,
	0x8f, 0x92, 0xb5, 0xa8,
	0xde, 0xc3, 0xe4, 0xf9,
	0xaa, 0xb7, 0x90, 0x8d,
	0x36, 0x2b, 0x0c, 0x11,
	0x42, 0x5f, 0x78, 0x65,
	0x94, 0x89, 0xae, 0xb3,
	0xe0, 0xfd, 0xda, 0xc7,
	0x7c, 0x61, 0x46, 0x5b,
	0x08, 0x15, 0x32, 0x2f,
	0x59, 0x44, 0x63, 0x7e,
	0x2d, 0x30, 0x17, 0x0a,
	0xb1, 0xac, 0x8b, 0x96,
	0xc5, 0xd8, 0xff, 0xe2,
	0x26, 0x3b, 0x1c, 0x01,
	0x52, 0x4f, 0x68, 0x75,
	0xce, 0xd3, 0xf4, 0xe9,
	0xba, 0xa7, 0x80, 0x9d,
	0xeb, 0xf6, 0xd1, 0xcc,
	0x9f, 0x82, 0xa5, 0xb8,
	0x03, 0x1e, 0x39, 0x24,
	0x77, 0x6a, 0x4d, 0x50,
	0xa1, 0xbc, 0x9b, 0x86,
	0xd5, 0xc8, 0xef, 0xf2,
	0x49, 0x54, 0x73, 0x6e,
	0x3d, 0x20, 0x07, 0x1a,
	0x6c, 0x71, 0x56, 0x4b,
	0x18, 0x05, 0x22, 0x3f,
	0x84, 0x99, 0xbe, 0xa3,
	0xf0, 0xed, 0xca, 0xd7,
	0x35, 0x28, 0x0f, 0x12,
	0x41, 0x5c, 0x7b, 0x66,
	0xdd, 0xc0, 0xe7, 0xfa,
	0xa9, 0xb4, 0x93, 0x8e,
	0xf8, 0xe5, 0xc2, 0xdf,
	0x8c, 0x91, 0xb6, 0xab,
	0x10, 0x0d, 0x2a, 0x37,
	0x64, 0x79, 0x5e, 0x43,
	0xb2, 0xaf, 0x88, 0x95,
	0xc6, 0xdb, 0xfc, 0xe1,
	0x5a, 0x47, 0x60, 0x7d,
	0x2e, 0x33, 0x14, 0x09,
	0x7f, 0x62, 0x45, 0x58,
	0x0b, 0x16, 0x31, 0x2c,
	0x97, 0x8a, 0xad, 0xb0,
	0xe3, 0xfe, 0xd9, 0xc4
	};
    BYTE crc_value = Crc_StartValue8;

    for (count = 0; count < Crc_Length; count++)
    {
        crc_value = Crc8Table[crc_value ^ Crc_DataPtr[count]];
    }
    return crc_value;
 }