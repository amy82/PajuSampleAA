#pragma once
#include "../../stdafx.h"

#include "Automotive.h"
#include "Windows.h"

#define MAXBLOCK        256

#define FC_NONE			0x00
#define FC_DTRDSR       0x01
#define FC_RTSCTS       0x02
#define FC_XONXOFF      0x04

#define ASCII_BEL       0x07
#define ASCII_BS        0x08
#define ASCII_LF        0x0A
#define ASCII_CR        0x0D
#define ASCII_XON       0x11
#define ASCII_XOFF      0x13

#define REG_ISP			0x00
#define REG_SENSOR		0x01

#define COM_PORT 9


class CSerialComm : public IAutomotiveComm
{
	CSerialComm(void);
	CSerialComm(const CSerialComm&);
	CSerialComm& operator=(const CSerialComm&);

	BOOL Setup();
	void CheckModemStatus();
	int WriteCommBlock( BYTE* pData, DWORD dwBytesToWrite );
	int ReadCommBlock( BYTE* pBlock, int nMaxLength );

public:
	~CSerialComm(void);

	static CSerialComm& GetInstance()
	{
		static CSerialComm self;
		return self;
	}

	BOOL Open( BYTE port, DWORD dwBaudRate = CBR_4800, BYTE byByteSize = 8, BYTE byStopBits = ONESTOPBIT, BYTE byParity = NOPARITY );
	void OnReceive( BYTE* pData, int nSize ) ;

	int Send(unsigned char* buffer, int length, unsigned long timeOutms = 1000);
	int Receive(unsigned char* buffer, int length, unsigned long timeOutms = 1000) { return 0; } // NOT SUPPORTED at PAC StA
	int GetReceivedPacket(unsigned char* pPacket, int size) { return 0; } // NOT SUPPORTED at PAC StA

	static unsigned int __stdcall CommWatchProc( LPVOID lpData );

private:
	HANDLE		m_hComm;
	BYTE		m_cPort;
	volatile BOOL	m_bConnected;
	BYTE		m_cByteSize, m_cFlowCtrl, m_cParity, m_cStopBits;
	DWORD		m_dwBaudRate;
	HANDLE		m_hWatchEvent;
	HANDLE		m_hWatchThread;
	unsigned int	m_nThreadID;

	OVERLAPPED	m_osWrite, m_osRead;

	BOOL		m_bWaitEventSet;
	HANDLE		m_hWaitEvent;

};

