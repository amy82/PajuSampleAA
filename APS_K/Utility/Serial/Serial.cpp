#include "StdAfx.h"
#include "Serial.h"


CSerial::CSerial()
{
	m_sbOpen = false;
}


CSerial::~CSerial()
{
}


//-----------------------------------------------------------------------------
//
//	시리얼 포트 오픈
//
//-----------------------------------------------------------------------------
bool CSerial::Open(unsigned int nPort, unsigned int nBaudRate)
{
	COMMTIMEOUTS stCommTimeOuts;
	DCB stDcb;
	TCHAR szPort[100];

	if (m_sbOpen == true)
	{
		return true;
	}

	if (nPort > 9)
	{
		_stprintf_s(szPort, 100, _T("\\\\.\\COM%d"), nPort);
	}
	else
	{
		_stprintf_s(szPort, 100, _T("COM%d"), nPort);
	}

	m_hConsole = CreateFile(szPort, GENERIC_READ | GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
	if (m_hConsole == NULL)
	{
		return false;
	}

	stCommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;
	stCommTimeOuts.ReadTotalTimeoutMultiplier = 0;
	stCommTimeOuts.ReadTotalTimeoutConstant = 0;
	stCommTimeOuts.WriteTotalTimeoutMultiplier = 0;
	stCommTimeOuts.WriteTotalTimeoutConstant = 5000;
	SetCommTimeouts(m_hConsole, &stCommTimeOuts);

	stDcb.DCBlength = sizeof(DCB);
	GetCommState(m_hConsole, &stDcb);
	stDcb.BaudRate = nBaudRate;
	stDcb.ByteSize = 8;
	stDcb.Parity = 0;
	stDcb.StopBits = 0;
	stDcb.fOutxDsrFlow = 0;
	stDcb.fDtrControl = 1;
	stDcb.fOutxCtsFlow = 0;
	stDcb.fRtsControl = 1;
	stDcb.fOutX = 0;
	stDcb.fInX = 0;
	stDcb.XonChar = (char)17;
	stDcb.XoffChar = (char)19;
	stDcb.XonLim = 100;
	stDcb.XoffLim = 100;
	stDcb.fBinary = 1;
	stDcb.fParity = 1;

	if (SetCommState(m_hConsole, &stDcb) == FALSE)
	{
		CloseHandle(m_hConsole);
		return false;
	}

	if (SetupComm(m_hConsole, 10000, 10000) == FALSE)
	{
		CloseHandle(m_hConsole);
		return false;
	}

	memset(&m_stReadOverlapped, 0, sizeof(OVERLAPPED));
	m_stReadOverlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (m_stReadOverlapped.hEvent == NULL)
	{
		CloseHandle(m_hConsole);
		return false;
	}

	memset(&m_stWriteOverlapped, 0, sizeof(OVERLAPPED));
	m_stWriteOverlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (m_stWriteOverlapped.hEvent == NULL)
	{
		CloseHandle(m_hConsole);
		CloseHandle(m_stReadOverlapped.hEvent);
		return false;
	}

	PurgeComm(m_hConsole, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);

	m_sbOpen = true;

	return true;
}

//-----------------------------------------------------------------------------
//
//	시리얼 포트 닫기
//
//-----------------------------------------------------------------------------
void CSerial::Close(void)
{
	if (m_sbOpen == false)
	{
		return;
	}

	CloseHandle(m_stReadOverlapped.hEvent);
	CloseHandle(m_stWriteOverlapped.hEvent);
	CloseHandle(m_hConsole);

	PurgeComm(m_hConsole, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);

	m_sbOpen = false;
}

//-----------------------------------------------------------------------------
//
//	시리얼 패킷 송신
//
//-----------------------------------------------------------------------------
unsigned int CSerial::SendData(const unsigned char* pBuffer, unsigned int nBuffSize)
{
	COMSTAT stComStat;
	unsigned long nErrorFlag;
	unsigned long nRetVal;

	if (m_sbOpen == false)
	{
		return 0;
	}

	if (WriteFile(m_hConsole, pBuffer, nBuffSize, &nRetVal, &m_stWriteOverlapped) == FALSE)
	{
		if (GetLastError() == ERROR_IO_PENDING)
		{
			while (GetOverlappedResult(m_hConsole, &m_stWriteOverlapped, &nRetVal, TRUE) == FALSE)
			{
				ClearCommError(m_hConsole, &nErrorFlag, &stComStat);
			}
		}
	}

	return nRetVal;
}

//-----------------------------------------------------------------------------
//
//	시리얼 패킷 수신
//
//-----------------------------------------------------------------------------
unsigned int CSerial::ReadData(unsigned char* pBuffer, unsigned int nBuffSize)
{
	COMSTAT stComStat;
	unsigned long nErrorFlag;
	unsigned long nSizeToRead;
	unsigned long nRetVal;

	if (m_sbOpen == false)
	{
		return 0;
	}

	ClearCommError(m_hConsole, &nErrorFlag, &stComStat);
	if (nBuffSize < stComStat.cbInQue)
	{
		nSizeToRead = nBuffSize;
	}
	else
	{
		nSizeToRead = stComStat.cbInQue;
	}

	if (ReadFile(m_hConsole, pBuffer, nSizeToRead, &nRetVal, &m_stReadOverlapped) == FALSE)
	{
		if (GetLastError() == ERROR_IO_PENDING)
		{
			while (GetOverlappedResult(m_hConsole, &m_stReadOverlapped, &nRetVal, TRUE) == FALSE)
			{
				ClearCommError(m_hConsole, &nErrorFlag, &stComStat);
			}
		}
	}

	return nRetVal;
}