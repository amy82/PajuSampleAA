#include "stdafx.h"

#include "SerialComm.h"
#include <process.h>

CSerialComm::CSerialComm(void) : m_hComm(NULL), m_cPort(0), m_bConnected(FALSE), m_cByteSize(0), m_cFlowCtrl(0), m_cParity(0), m_cStopBits(0),
	m_dwBaudRate(0), m_hWatchEvent(NULL), m_hWatchThread(NULL), m_nThreadID(0), m_bWaitEventSet(FALSE), m_hWaitEvent(NULL)
{
	
}

CSerialComm::~CSerialComm(void)
{
	if( m_hWaitEvent)
		CloseHandle(m_hWaitEvent);

   // clean up event objects
   CloseHandle( m_osRead.hEvent );
   CloseHandle( m_osWrite.hEvent );

   m_bConnected = FALSE;
}

BOOL CSerialComm::Setup()
{
	BOOL	bRetVal;
	BOOL	bSet;
	DCB		dcb;
	
	if ( m_hComm == INVALID_HANDLE_VALUE )
		return FALSE;
	
	dcb.DCBlength = sizeof( DCB );
	
	::GetCommState( m_hComm, &dcb );
	
	dcb.BaudRate = m_dwBaudRate;
	dcb.ByteSize = m_cByteSize;
	dcb.Parity = m_cParity;
	dcb.StopBits = m_cStopBits;
	
	// setup hardware flow control
	
	bSet = (BOOL)( (m_cFlowCtrl & FC_DTRDSR) != 0 );
	dcb.fOutxDsrFlow = bSet;
	if ( bSet )
		dcb.fDtrControl = DTR_CONTROL_HANDSHAKE;
	else
		dcb.fDtrControl = DTR_CONTROL_ENABLE;
	
	bSet = (BOOL)( (m_cFlowCtrl & FC_RTSCTS) != 0 );
	dcb.fOutxCtsFlow = bSet;
	if ( bSet )
		dcb.fRtsControl = RTS_CONTROL_HANDSHAKE;
	else
		dcb.fRtsControl = RTS_CONTROL_ENABLE;
	
	// setup software flow control
	bSet = (BOOL)( (m_cFlowCtrl & FC_XONXOFF) != 0 );
	
	dcb.fInX = dcb.fOutX = bSet;
	dcb.XonChar = 0x00;
	dcb.XoffChar = 0x00;
	dcb.XonLim = 100;
	dcb.XoffLim = 100;
	
	// other various settings
	dcb.fBinary = TRUE;
	dcb.fParity = FALSE;//패리티 검사 활성화시 TRUE로 설정
	
	bRetVal = ::SetCommState( m_hComm, &dcb ) ;
	
	return bRetVal;
}

BOOL CSerialComm::Open( BYTE port, DWORD dwBaudRate /*= CBR_4800*/, BYTE byByteSize /*= 8*/, BYTE byStopBits /*= ONESTOPBIT*/, BYTE byParity /*= NOPARITY*/ )
{
	m_cPort = port;
	m_dwBaudRate = dwBaudRate;
	m_cByteSize = byByteSize;
	m_cParity = byParity;
	m_cStopBits = byStopBits;

	m_hComm = INVALID_HANDLE_VALUE;
	m_bConnected = FALSE;
	
	m_cFlowCtrl = 0;

	m_osWrite.Offset = 0;
	m_osWrite.OffsetHigh = 0;
	m_osRead.Offset = 0;
	m_osRead.OffsetHigh = 0;
	
	// create I/O event used for overlapped reads / writes
	m_osRead.hEvent = ::CreateEvent( NULL, TRUE, FALSE, NULL );
	if ( m_osRead.hEvent == NULL )
	{
		return FALSE;
	}
	m_osWrite.hEvent = ::CreateEvent( NULL, TRUE, FALSE, NULL );

	if ( m_osWrite.hEvent == NULL )
	{
		::CloseHandle( m_osRead.hEvent );
		return FALSE;
	}

	TCHAR szComFile[16];

	if ( m_cPort <= 9 )
		wsprintf( szComFile, "COM%d:", m_cPort );
	else
		wsprintf( szComFile, "\\\\.\\COM%d", m_cPort );
	
	DWORD dwFlag = 0;

	dwFlag = /*FILE_ATTRIBUTE_NORMAL | */FILE_FLAG_OVERLAPPED;
	
	if ( ( m_hComm  =
		::CreateFile( szComFile, GENERIC_READ | GENERIC_WRITE,
		0,                    // exclusive access
		NULL,                 // no security attrs
		OPEN_EXISTING,
		dwFlag,
		NULL ) ) == INVALID_HANDLE_VALUE )
		return FALSE;
	else
	{
		// get any early notifications
		::SetCommMask( m_hComm, EV_RXCHAR | EV_CTS | EV_DSR | EV_RLSD | EV_RING );
		
		// setup device buffers
		::SetupComm( m_hComm, 4096, 4096 );
		
		// purge any information in the buffer
		::PurgeComm( m_hComm, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR );
		
		COMMTIMEOUTS  CommTimeOuts;
		// set up for overlapped I/O
		CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;
		CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
		CommTimeOuts.ReadTotalTimeoutConstant = 0;
		// CBR_9600 is approximately 1byte/ms. For our purposes, allow
		// double the expected time per character for a fudge factor.
		CommTimeOuts.WriteTotalTimeoutMultiplier = 2*CBR_9600/m_dwBaudRate;
		CommTimeOuts.WriteTotalTimeoutConstant = 0;
		::SetCommTimeouts( m_hComm, &CommTimeOuts );
	}
	
	HANDLE	hCommWatchThread = NULL;
	unsigned int nThreadID;
	
	if ( Setup() )
	{
		m_bConnected = TRUE;
		
		// Create a secondary thread
		// to watch for an event.
		if ( NULL == (hCommWatchThread =
				(HANDLE)::_beginthreadex( (LPSECURITY_ATTRIBUTES) NULL,
								0,
								CommWatchProc,
								(LPVOID) this,
								0, &nThreadID ) ) )
		{
			m_bConnected = FALSE;
			::CloseHandle( m_hComm ) ;
			return FALSE;
		}
		else
		{
			m_nThreadID = nThreadID;
			m_hWatchThread = hCommWatchThread;
		
			// assert DTR
			::EscapeCommFunction( m_hComm, SETDTR );
		}

		m_hWaitEvent = ::CreateEvent(NULL, TRUE, FALSE, 0);
	}
	else
	{
		m_bConnected = FALSE;
		::CloseHandle( m_hComm );
	}

	return TRUE;
}

void CSerialComm::CheckModemStatus()
{
	return;
	DWORD dwEvtMask;
	// Retrieve modem control-register values.
	::GetCommModemStatus( m_hComm, &dwEvtMask );

	if ( (dwEvtMask & (MS_DSR_ON|MS_RLSD_ON)) == 0 && (dwEvtMask & MS_CTS_ON) != 0 )
	{
		// Disconnect Device
	}

	if ( (dwEvtMask & (MS_RING_ON|MS_RLSD_ON)) == (MS_RING_ON|MS_RLSD_ON) )		// cable disconnect
	{
		// Disconnect Device
	}
}

int CSerialComm::WriteCommBlock( BYTE* pData, DWORD dwBytesToWrite )
{
	BOOL        bWriteStat;
	DWORD       dwBytesWritten;
	DWORD       dwBytesSent = 0;
	LPOVERLAPPED pOverlap = NULL;

	if ( !m_bConnected )
		return 0;

	pOverlap = &m_osWrite;

	CheckModemStatus();	

	bWriteStat = ::WriteFile( m_hComm, pData, dwBytesToWrite, &dwBytesWritten, pOverlap );
	
	DWORD       dwErrorFlags;
	COMSTAT     ComStat;
	DWORD   	dwError;
	TCHAR       szError[128];
	
	if ( !bWriteStat )
	{
		if ( (dwError = ::GetLastError()) == ERROR_IO_PENDING )
		{
			while ( !::GetOverlappedResult( m_hComm,	&m_osWrite, &dwBytesWritten, TRUE ) )
			{
				dwError = ::GetLastError();
				if ( dwError == ERROR_IO_INCOMPLETE )
				{
					// normal result if not finished
					dwBytesSent += dwBytesWritten;
					continue;
				}
				else
				{
					// an error occurred, try to recover
					wsprintf( szError, TEXT("<CE-%u>"), dwError );

					::ClearCommError( m_hComm, &dwErrorFlags, &ComStat );
					if ( dwErrorFlags > 0 )
					{
						wsprintf( szError, TEXT("<CE-%u>"), dwErrorFlags ) ;
					}
					break;
				}
			}
			
			dwBytesSent += dwBytesWritten;
			
			if ( dwBytesSent != dwBytesToWrite )
				wsprintf(szError, TEXT("Probable Write Timeout: Total of %ld bytes sent"), dwBytesSent);
			else
				wsprintf(szError, TEXT("%ld bytes written"), dwBytesSent);
		}
		else
		{
			// some other error occurred
			::ClearCommError( m_hComm, &dwErrorFlags, &ComStat );
			if ( dwErrorFlags > 0)
			{
				wsprintf( szError, TEXT("<CE-%u>"), dwErrorFlags );
			}
			return FALSE;
		}
	}

	return dwBytesWritten;
}

int CSerialComm::ReadCommBlock( BYTE* pBlock, int nMaxLength )
{
	BOOL       bReadStat;
	COMSTAT    ComStat;
	DWORD      dwErrorFlags;
	DWORD      dwLength;
	LPOVERLAPPED lpOverlap = NULL;

	lpOverlap = &m_osRead;
	
	// only try to read number of bytes in queue
	::ClearCommError( m_hComm, &dwErrorFlags, &ComStat );
	dwLength = __min( (DWORD) nMaxLength, ComStat.cbInQue );
	if ( dwLength > 0 )
	{
		bReadStat = ::ReadFile( m_hComm, pBlock, dwLength, &dwLength, lpOverlap );

		DWORD      dwError;
		TCHAR      szError[ 10 ];
		
		if ( !bReadStat )
		{
			if ( ::GetLastError() == ERROR_IO_PENDING )
			{
				// We have to wait for read to complete.
				// This function will timeout according to the
				// CommTimeOuts.ReadTotalTimeoutConstant variable
				// Every time it times out, check for port errors
				while ( !GetOverlappedResult( m_hComm, &m_osRead, &dwLength, TRUE ) )
				{
					dwError = ::GetLastError();
					if ( dwError == ERROR_IO_INCOMPLETE )
						// normal result if not finished
						continue;
					else
					{
						// an error occurred, try to recover
						wsprintf( szError, TEXT("<CE-%u>"), dwError );
						::ClearCommError( m_hComm, &dwErrorFlags, &ComStat );
						if ( dwErrorFlags > 0 )
						{
							wsprintf( szError, TEXT("<CE-%u>"), dwErrorFlags ) ;
						}
						break;
					}
				}
			}
			else
			{
				// some other error occurred
				dwLength = 0 ;
				::ClearCommError( m_hComm, &dwErrorFlags, &ComStat );
				if ( dwErrorFlags > 0 )
				{
					wsprintf( szError, TEXT("<CE-%u>"), dwErrorFlags ) ;
				}
			}
		}
	}
	
	return dwLength;
}

unsigned int __stdcall CSerialComm::CommWatchProc( LPVOID lpData )
{
	DWORD		dwEvtMask;
	int			nLength;
	BYTE		pcIn[ MAXBLOCK + 1];
	CSerialComm*		pComm = (CSerialComm*) lpData;

	DWORD		dwSetEvtmask;

	OVERLAPPED	os;	
	memset( &os, 0, sizeof( OVERLAPPED ) );
	
	// create I/O event used for overlapped read
	os.hEvent = ::CreateEvent( NULL, TRUE, FALSE, NULL );
	if (os.hEvent == NULL)
	{
		// Failed to create event for thread!
		return FALSE;
	}

	dwSetEvtmask = EV_RXCHAR | EV_CTS | EV_DSR | EV_RLSD | EV_RING;
	
	if ( !::SetCommMask( pComm->m_hComm, dwSetEvtmask ) )
		return FALSE;

	BOOL bCheckOK = FALSE;

	while ( pComm->m_bConnected )
	{
		dwEvtMask = 0;

		pComm->CheckModemStatus();

		::SetCommMask( pComm->m_hComm, dwSetEvtmask );

		BOOL bWaitOK = ::WaitCommEvent( pComm->m_hComm, &dwEvtMask, NULL );
		if ( bWaitOK )
		{
			//XTRACE( _T("dwEvtMask: %X\r\n"), dwEvtMask );
			if ( (dwEvtMask & EV_RXCHAR) == EV_RXCHAR )
			{
				do
				{
					if ( nLength = pComm->ReadCommBlock( pcIn, MAXBLOCK ) )
					{
						pComm->OnReceive( pcIn, nLength ) ;
					}
				}
				while ( nLength > 0 );
			}
		}
		else
		{
			// ERROR: WaitCommEvent
			break;
		}

	}
	
	// get rid of event handle
	::CloseHandle( os.hEvent ) ;
	
	// clear information in structure (kind of a "we're done flag")
	pComm->m_nThreadID = 0;
	pComm->m_hWatchThread = NULL;

	::_endthreadex(0);
	
	return TRUE;
}


int CSerialComm::Send(unsigned char* buffer, int length, unsigned long timeOutms /*= 1000*/)
{
	int nWrittenBytes = WriteCommBlock(buffer, length);
	if( nWrittenBytes <= 0 )
		return 0;

	if( timeOutms > 0 )
	{
		m_bWaitEventSet = TRUE;

		// wait for event during timeout ms.
		if( ::WaitForSingleObject(m_hWaitEvent, timeOutms ) == WAIT_TIMEOUT )
		{
			::ResetEvent(m_hWaitEvent);
			return -1;
		}
		::ResetEvent(m_hWaitEvent);
	}


	return 1;
}


void CSerialComm::OnReceive( BYTE* pData, int nSize ) 
{ 
	if( pData && nSize > 0 && m_pReceiver)
	{
		int nProcessedSize = 0;
		if( m_pReceiver->OnPacketReceive(pData, nSize, nProcessedSize) )
		{
			if( m_bWaitEventSet )
			{
				m_bWaitEventSet = FALSE;
				::SetEvent(m_hWaitEvent);
			}
		}

	}
}

