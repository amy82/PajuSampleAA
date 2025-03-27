#include "StdAfx.h"
#include "Comm_RS232C.h"
//#include "../../AA Bonder.h"
//#include "../../AA BonderDlg.h"

bool	g_Comm_bReady_UV;

CCommList_RS232C::CCommList_RS232C(void)
{
	m_arrList_ComPort.RemoveAll();
	m_arrList_ComPort.FreeExtra();
}

CCommList_RS232C::~CCommList_RS232C(void)
{
	m_arrList_ComPort.RemoveAll();
	m_arrList_ComPort.FreeExtra();
}

//! [기능]   PC의 Serial Port를 알아내어 m_arrComPortList에 저장한다. 
//! [반환값] 작업을 완료하면 true를 반환한다. 
bool CCommList_RS232C::GetList_SerialPort()
{
	HKEY hResKey = NULL;

	//! Registry에 접근한다. 	
	long nRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("HARDWARE\\DEVICEMAP\\SERIALCOMM"), 0, KEY_READ, &hResKey);

	//! Registry에 접근 실패
	if ( nRet != ERROR_SUCCESS )
	{
		return false;
	}

	//! 목록 초기화
	m_arrList_ComPort.RemoveAll();
	m_arrList_ComPort.FreeExtra();

	//! 변수, 버퍼 초기화
	DWORD i = 0, dwKeyType = 0;
	TCHAR czKeyName[8192], czKeyValue[8192];
	DWORD dwKeyNameBufSize = (DWORD)(sizeof(czKeyName));
	DWORD dwKeyValueBufSize = (DWORD)(sizeof(czKeyValue));
	CString szAddValue = _T("");

	//! Registry에서 PC의 Serial Port를 알아내어 m_arrComPortList에 저장한다. 
	for ( i = 0; ; i++ )
	{
		dwKeyNameBufSize = (DWORD)(sizeof(czKeyName));
		dwKeyValueBufSize = (DWORD)(sizeof(czKeyValue));

		nRet = RegEnumValue(hResKey, i, czKeyName, &dwKeyNameBufSize, NULL, &dwKeyType, (LPBYTE)czKeyValue, &dwKeyValueBufSize);

		if ( nRet == ERROR_SUCCESS )
		{
			szAddValue.Format(_T("%s"), czKeyValue);
			m_arrList_ComPort.Add(szAddValue);
		}
		else
		{
			//! ERROR_NO_MORE_ITEMS : 더 이상 읽어올 값이 없을 때
			break;
		}
	}

	//! Registry 접근 핸들을 닫는다.
	RegCloseKey(hResKey);

	return true;
}


CCommHelper_Setup_RS232C::CCommHelper_Setup_RS232C(void)
{
}

CCommHelper_Setup_RS232C::~CCommHelper_Setup_RS232C(void)
{
}

bool CCommHelper_Setup_RS232C::GetValue_BaudRate(int iIndex_BaudRate, DWORD &dwRetBaudRate, CString *psItemName)
{
	bool bRet = true;

	switch(iIndex_BaudRate)
	{
	case 0:
		{
			dwRetBaudRate = CBR_1200;

			if ( psItemName != NULL )
			{
				*psItemName = _T("1200");
			}
		}
		break;
	case 1:
		{
			dwRetBaudRate = CBR_2400;

			if ( psItemName != NULL )
			{
				*psItemName = _T("2400");
			}
		}
		break;
	case 2:
		{
			dwRetBaudRate = CBR_4800;

			if ( psItemName != NULL )
			{
				*psItemName = _T("4800");
			}
		}
		break;
	case 3:
		{
			dwRetBaudRate = CBR_9600;

			if ( psItemName != NULL )
			{
				*psItemName = _T("9600");
			}
		}
		break;
	case 4:
		{
			dwRetBaudRate = CBR_19200;

			if ( psItemName != NULL )
			{
				*psItemName = _T("19200");
			}
		}
		break;
	case 5:
		{
			dwRetBaudRate = CBR_38400;

			if ( psItemName != NULL )
			{
				*psItemName = _T("38400");
			}
		}
		break;
	case 6:
		{
			dwRetBaudRate = CBR_115200;

			if ( psItemName != NULL )
			{
				*psItemName = _T("115200");
			}
		}
		break;		
	default:
		{
			dwRetBaudRate = CBR_38400;
			bRet = false;

			if ( psItemName != NULL )
			{
				*psItemName = _T("");
			}
		}
		break;
	}

	return bRet;
}

bool CCommHelper_Setup_RS232C::GetValue_DataBit(int iIndex_DataBit, BYTE  &byRetDataBit, CString *psItemName)
{
	bool bRet = true;

	switch(iIndex_DataBit)
	{
	case 0:
		{
			byRetDataBit = 5;
		}
		break;
	case 1:
		{
			byRetDataBit = 6;
		}
		break;
	case 2:
		{
			byRetDataBit = 7;
		}
		break;
	case 3:
		{
			byRetDataBit = 8;
		}
		break;
	default:
		{
			byRetDataBit = 8;
			bRet = false;
		}
		break;
	}

	if ( psItemName != NULL )
	{
		if ( bRet == true )
		{
			int iDataBit = (int)(byRetDataBit);
			psItemName->Format(_T("%d"), iDataBit);
		}
		else
		{
			*psItemName = _T("");
		}
	}

	return bRet;
}

bool CCommHelper_Setup_RS232C::GetValue_StopBit(int iIndex_StopBit, BYTE  &byRetStopBit, CString *psItemName)
{
	bool bRet = true;

	switch(iIndex_StopBit)
	{
	case 0:
		{
			byRetStopBit = ONESTOPBIT;

			if ( psItemName != NULL )
			{
				*psItemName = _T("1");
			}
		}
		break;
	case 1:
		{
			byRetStopBit = TWOSTOPBITS;

			if ( psItemName != NULL )
			{
				*psItemName = _T("2");
			}
		}
		break;
	default:
		{
			byRetStopBit = ONESTOPBIT;
			bRet = false;

			if ( psItemName != NULL )
			{
				*psItemName = _T("");
			}
		}
		break;
	}
	
	return bRet;
}

bool CCommHelper_Setup_RS232C::GetValue_ParityBit(int iIndex_ParityBit, BYTE  &byRetParityBit, CString *psItemName)
{
	bool bRet = true;

	switch(iIndex_ParityBit)
	{
	case 0:
		{
			byRetParityBit = NOPARITY;

			if ( psItemName != NULL )
			{
				*psItemName = _T("None");
			}
		}
		break;
	case 1:
		{
			byRetParityBit = ODDPARITY;

			if ( psItemName != NULL )
			{
				*psItemName = _T("Odd");
			}
		}
		break;
	case 2:
		{
			byRetParityBit = EVENPARITY;

			if ( psItemName != NULL )
			{
				*psItemName = _T("Even");
			}
		}
		break;
	default:
		{
			byRetParityBit = NOPARITY;
			bRet= false;

			if ( psItemName != NULL )
			{
				*psItemName = _T("");
			}
		}
		break;
	}

	return bRet;
}

int CCommHelper_Setup_RS232C::GetIndex_BaudRate(DWORD dwBaudRate)
{
	int iIndex_Ret = -1;

	if ( dwBaudRate == CBR_1200 )
	{
		iIndex_Ret = 0;
	}
	else if ( dwBaudRate == CBR_2400 )
	{
		iIndex_Ret = 1;
	}
	else if ( dwBaudRate == CBR_4800 )
	{
		iIndex_Ret = 2;
	}
	else if ( dwBaudRate == CBR_9600 )
	{
		iIndex_Ret = 3;
	}
	else if ( dwBaudRate == CBR_19200 )
	{
		iIndex_Ret = 4;
	}
	else if ( dwBaudRate == CBR_38400 )
	{
		iIndex_Ret = 5;
	}
	else if ( dwBaudRate == CBR_115200 )
	{
		iIndex_Ret = 6;
	}
	
	return iIndex_Ret;
}

int CCommHelper_Setup_RS232C::GetIndex_DataBit(BYTE byDataBit)
{
	int iIndex_Ret = -1;

	if ( byDataBit == 5 )
	{
		iIndex_Ret = 0;
	}
	else if ( byDataBit == 6 )
	{
		iIndex_Ret = 1;
	}
	else if ( byDataBit == 7 )
	{
		iIndex_Ret = 2;
	}
	else if ( byDataBit == 8 )
	{
		iIndex_Ret = 3;
	}

	return iIndex_Ret;
}

int CCommHelper_Setup_RS232C::GetIndex_StopBit(BYTE byStopBit)
{
	int iIndex_Ret = -1;

	if ( byStopBit == TWOSTOPBITS )
	{
		iIndex_Ret = 1;
	}
	else if ( byStopBit == ONESTOPBIT )
	{
		iIndex_Ret = 0;
	}

	return iIndex_Ret;
}

int CCommHelper_Setup_RS232C::GetIndex_ParityBit(BYTE byParityBit)
{
	int iIndex_Ret = -1;

	if ( byParityBit == NOPARITY )
	{
		iIndex_Ret = 0;
	}
	else if ( byParityBit == ODDPARITY )
	{
		iIndex_Ret = 1;
	}
	else if ( byParityBit == EVENPARITY )
	{
		iIndex_Ret = 2;
	}

	return iIndex_Ret;
}

//! [기능]   Baud Rate 값을 정수형으로 반환
//! [입력값] 'CBR_'로 시작되는 Baud Rate 상수값
//! [반환값] Baud Rate 정수형 값
int CCommHelper_Setup_RS232C::GetBaudRateValue_Integer_FromConstant(DWORD dwBaudRate)
{
	int iRet = 38400;

	switch(dwBaudRate)
	{
	case CBR_1200:
		{
			iRet = 1200;
		}
		break;
	case CBR_2400:
		{
			iRet = 2400;
		}
		break;
	case CBR_4800:
		{
			iRet = 4800;
		}
		break;
	case CBR_9600:
		{
			iRet = 9600;
		}
		break;
	case CBR_19200:
		{
			iRet = 19200;
		}
		break;
	case CBR_38400:
		{
			iRet = 38400;
		}
		break;
	case CBR_115200:
		{
			iRet = 115200;
		}
		break;
	}

	return iRet;
}

//! [기능] 정수형 값을 BYTE 배열의 데이터로 변환
//! [입력값] iInput : 정수형 값, pbyOutputBuf : BYTE 배열, 충분히 큰 배열을 입력해야 한다. 
//!			 iOutputBufSize : pbyOutputBuf의 크기
//! [반환값] 작업이 완료되면 pbyOutputBuf에 입력된 데이터의 크기를 반환한다. 오류가 발생하면 음수를 반환한다. 
int CCommHelper_Setup_RS232C::Convert_Integer_To_ArrayByte(int iInput, BYTE* pbyOutputBuf, int iOutputBufSize)
{
	if ( pbyOutputBuf == NULL || iOutputBufSize <= 0 )
	{
		return -1;
	}

	TCHAR czInteger[64];
	memset(czInteger, 0x00, sizeof(czInteger));
	_itot_s(iInput, czInteger, 10);	//! Convert an integer to a string, 10진수 Base radix 사용

	int iLength = _tcsclen(czInteger);

	if ( iLength >= iOutputBufSize )
	{
		return -2;
	}

	int i = 0;
	for ( i = 0; i < iLength; i++ )
	{
		pbyOutputBuf[i] = (BYTE)(czInteger[i]);
	}

	return iLength;
}


CComm_RS232C::CComm_RS232C(void)
{
	//! 초기화
	m_hComm = NULL;

	m_strCommSetupInfo.InitInfo();
	m_strCommStateInfo.InitInfo();

	m_osReceive.hEvent = NULL;
	m_osSend.hEvent = NULL;

	m_pThread_RecvComm = NULL;

	m_pReceiveProcPtr = NULL;	

	m_bFlag_Stop = false;	
}

CComm_RS232C::~CComm_RS232C(void)
{
	m_csReceiveProcPtr.Lock();
	m_pReceiveProcPtr = NULL;
	m_csReceiveProcPtr.Unlock();

	ClosePort();
}

//! [기능] 'SetThreadAffinityMask' 함수의 Mask 인자값을 반환받는다. 
//! [입력값] piBuf_CPU_Use : int 배열, CPU를 사용하면 1, 사용하지 않으면 0, 
//!							 0 번 index가 1번 CPU를 가리킨다. 1번 index는 2번 CPU, ...
//!			 iBufSize_CPU_Use : piBuf_CPU_Use 배열에서 사용할 데이터의 개수
//! [반환값] 'SetThreadAffinityMask' 함수의 Mask 인자값, 오류가 발생하면 0을 반환한다. 
DWORD CComm_RS232C::GetMask_CPU_Affinity(int *piBuf_CPU_Use, int iBufSize_CPU_Use)
{
	if ( piBuf_CPU_Use == NULL )
	{
		return 0;
	}

	//! 시스템의 사양을 알아낸다. 
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);

	//! CPU 개수와 버퍼 크기를 확인한다. 
	int iCPU_Size = (int)(sysInfo.dwNumberOfProcessors);
	if ( iBufSize_CPU_Use <= 0 || iBufSize_CPU_Use > iCPU_Size )
	{
		return 0;
	}

	int i = 0;
	DWORD dwRet = 0;

	iBufSize_CPU_Use--;
	for ( i = iBufSize_CPU_Use; i >= 0; i-- )
	{
		if ( piBuf_CPU_Use[i] != 0 )	//! CPU를 사용할 경우
		{
			dwRet = dwRet | (0x01 << (iBufSize_CPU_Use - i));
		}
	}

	return dwRet;
}

int	CComm_RS232C::Set_CPU_Affinity(int *piBuf_CPU_Use, int iBufSize_CPU_Use)
{
	//! 아직, Thread가 생성되지 않았음
	if ( m_pThread_RecvComm == NULL )
	{
		return -1;
	}

	if ( piBuf_CPU_Use == NULL )
	{
		return -2;
	}

	//! 시스템의 사양을 알아낸다. 
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);

	//! CPU 개수와 버퍼 크기를 확인한다. 
	int iCPU_Size = (int)(sysInfo.dwNumberOfProcessors);
	if ( iCPU_Size <= 0 )
	{
		return -3;
	}

	//! CPU가 1 Core 이므로 이 기능을 사용하지 않는다.
	if ( iCPU_Size == 1 )
	{
		return 0;
	}
	
	//! 사용 가능한 CPU의 개수를 알아낸다.
	int iSize_Possible_CPU_Core = 0;
	if ( iCPU_Size > intBufSize_RS232C_CPU_Core )
	{
		iSize_Possible_CPU_Core = intBufSize_RS232C_CPU_Core;
	}
	else
	{
		iSize_Possible_CPU_Core = iCPU_Size;
	}

	//! GetMask_CPU_Affinity 함수에 입력할 버퍼
	int aiCPU[intBufSize_RS232C_CPU_Core];
	memset(aiCPU, 0, sizeof(aiCPU));

	//! GetMask_CPU_Affinity 함수에 입력할 버퍼 설정
	//! 동시에 버퍼에서 설정된 사용 CPU 개수를 확인
	int i = 0;
	int iCnt_Use_CPU = 0;
	for ( i = 0; i < iSize_Possible_CPU_Core; i++ )
	{
		if ( i >= iBufSize_CPU_Use )
		{
			break;
		}
		if ( piBuf_CPU_Use[i] != 0 )
		{
			aiCPU[i] = 1;
			iCnt_Use_CPU++;
		}
	}

	//! 현재 PC에서 사용할 CPU가 없을 경우
	if ( iCnt_Use_CPU <= 0 )
	{
		//! 맨 마지막 CPU를 사용하도록 강제 설정
		aiCPU[iSize_Possible_CPU_Core - 1] = 1;
	}

	DWORD dwMaskValue = GetMask_CPU_Affinity(aiCPU, iSize_Possible_CPU_Core);

	//! Process를 작동시킬 CPU를 선택한다.  
	DWORD dwRet = ::SetThreadAffinityMask(m_pThread_RecvComm->m_hThread, dwMaskValue);
	if ( dwRet <= 0 )
	{
		DWORD dwError = GetLastError();

		//! The handle is invalid
		//! Thread가 시작하자 마자 Thread 본체 함수에서 중단된 경우이다.
		if ( dwError == ERROR_INVALID_HANDLE )
		{
			return -4;
		}

		//! 'dwMaskValue' 입력값에 오류가 있음
		if ( dwError == ERROR_INVALID_PARAMETER )
		{
			return -5;
		}

		return -6;
	}

	return 1;
}

//! [기능] Thread 작동을 시작한다.
int CComm_RS232C::StartThread(bool bFlag_Use_CPU_Affinity, int *piBuf_CPU_Use, int iBufSize_CPU_Use)
{
	if ( m_pThread_RecvComm != NULL )
	{
		return -1;
	}

	//! Thread가 아직 작동 중일 때
	if ( m_strCommStateInfo.bFlag_Thread_Operate == true )
	{
		return -2;
	}

	//! RS-232C COM Port가 열리지 않았을 때
	if ( m_strCommStateInfo.bFlag_Connected == false )
	{
		return -3;
	}

	if ( bFlag_Use_CPU_Affinity == true )
	{
		if ( piBuf_CPU_Use == NULL || iBufSize_CPU_Use <= 0 )
		{
			return -4;
		}
	}

	//! 관련 변수 초기화
	m_strCommStateInfo.InitInfo_Thread();
	m_pThread_RecvComm = NULL;
	m_bFlag_Stop = false;

	//! Thread 생성
	m_pThread_RecvComm = AfxBeginThread(m_Thread_Receive_Comm, this, THREAD_PRIORITY_NORMAL, 0, 0);

	if ( m_pThread_RecvComm == NULL )
	{
		return -5;
	}

	//! 특정 CPU Core에서 작동하는 기능을 사용하지 않는다.
	if ( bFlag_Use_CPU_Affinity == false )
	{
		return 1;
	}

	int iRet = Set_CPU_Affinity(m_strCommSetupInfo.aiCPU, intBufSize_RS232C_CPU_Core);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	return 1;
}

//! [기능] 도중에 Thread 작동을 멈춥니다. Thread가 멈추는 것을 기다리지 않는다.
int CComm_RS232C::Stop_Thread()
{
	if ( m_pThread_RecvComm == NULL )
	{
		return -1;
	}

	//! Thread 정지 Flag를 On한다. 
	m_bFlag_Stop = true;

	m_pThread_RecvComm = NULL;

	return 1;
}

//! [기능]   Thread가 멈추는 것을 기다린다. 
//! [입력값] iTimeOut : 대기 시간을 msec 단위로 입력합니다. 
int CComm_RS232C::Stop_Thread_Waiting(int iTimeOut)
{
	if ( m_pThread_RecvComm == NULL )
	{
		return -1;
	}

	//! Thread가 이미 멈추어 있는 경우
	if ( m_strCommStateInfo.bFlag_Thread_Operate == false )
	{
		return 1;
	}

	//! Thread 정지 Flag를 On한다. 
	m_bFlag_Stop = true;

	bool bRet = true;	//! true이면 제한 시간안에 정상 종료된 것임
	int iTimeCounter = 0, iWaitTime = 0;
	MSG msg;

	for ( iTimeCounter = iTimeOut;; )
	{
		if ( iTimeOut > 0 )
		{
			iWaitTime = iTimeOut;

			//! iTimeOut 값이 너무 크면 프로그램이 멈추어 버리므로, 100 msec 만큼 잘라서 반복적으로 처리한다. 
			if ( iWaitTime > 100 )
			{
				iWaitTime = 100;
			}

			Sleep(iWaitTime);
		}
		else
		{
			iWaitTime = 0;
		}

		if ( m_strCommStateInfo.bFlag_Thread_Operate == false )
		{
			break;
		}

		//! 프로그램이 Holding되지 않도록 메시지 처리
		if(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);

			if ( msg.message == 0 )
			{
				break;
			}
		}

		if ( iTimeOut > 0 )
		{
			iTimeOut -= iWaitTime;	//! 대기 시간을 빼어 나간다. 

			if ( iTimeOut <= 0 )	//! 입력한 대기 시간이 지났을 경우
			{
				bRet = false;
				break;
			}
		}
		else
		{
			//! 대기 시간이 없을 경우 
			bRet = false;
			break;
		}
	}

	if ( bRet == true )
	{
		m_pThread_RecvComm = NULL;

		TRACE(_T("CComm_RS232C::Stop_Thread_Waiting [%s] Stop OK \n"), m_strCommSetupInfo.sPortName);
	}
	else
	{
		TRACE(_T("CComm_RS232C::Stop_Thread_Waiting [%s] Stop Error \n"), m_strCommSetupInfo.sPortName);

		return -2;
	}

	return 1;
}

//! [기능] 수신 데이터를 처리할 클래스의 instance의 포인터를 설정한다. 
//! [입력값] pInput : 클래스의 void 포인터 
void CComm_RS232C::SetReceiveProcPtr(void* pInput)
{
	m_csReceiveProcPtr.Lock();
	m_pReceiveProcPtr = pInput;
	m_csReceiveProcPtr.Unlock();
}

//! [기능] 수신 Thread 본체 함수
UINT m_Thread_Receive_Comm(LPVOID pParam)
{
	CComm_RS232C *pSerial = (CComm_RS232C*)pParam;

	if ( pSerial == NULL )
	{
		return 0;
	}
	if ( pSerial->m_hComm == NULL )
	{
		return 0;
	}

	int         iCnt_Recv_Action = 0;
	DWORD		dwEvent;
	OVERLAPPED	os;
	bool		bOK = true;
	BYTE		byRecvBuff[4096];		//! 수신 버퍼 
	DWORD		dwReceive = 0;			//! 수신한 Byte 크기 
	void		*pReceiveProcPtr = NULL;//! m_pReceiveProcPtr의 포인터를 임시 저장, 작업 도중에 포인터가 변경되는 것에 대비한다. 

	memset(&os, 0, sizeof(OVERLAPPED));

	os.hEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
	if ( os.hEvent == NULL )
	{
		bOK = false;
	}

	if ( ::SetCommMask(pSerial->m_hComm, EV_RXCHAR) == FALSE )
	{
		bOK = false;
	}

	if ( bOK == false )	//! Thread 내부 설정 실패
	{
		return 0;
	}

	//! Thread가 동작을 시작했음을 설정한다.
	pSerial->m_strCommStateInfo.bFlag_Thread_Operate = true;

	//! RS-232C 통신이 연결되고 맨 처음 1번만 실행된다.
	pSerial->ReadyDevice();

	while(1)
	{
		if ( pSerial == NULL )
		{
			break;
		}
		if ( pSerial->IsConnected() == false )
		{
			break;
		}
		if ( pSerial->m_bFlag_Stop == true )		//! Thread를 멈춘다.
		{
			break;
		}
		
		//! COM Port에 수신할 데이터가 오기를 기다린다. 
		//! 이 지점에서 Pending 된다. 
		::WaitCommEvent( pSerial->m_hComm, &dwEvent, NULL );	

		//! COM Port에 데이터가 수신되었을 때 
		if ( (dwEvent & EV_RXCHAR) == EV_RXCHAR )
		{
			iCnt_Recv_Action = 0;

			//! COM Port에서 읽을수 있는만큼 읽는다. 
			do
			{
				if ( pSerial == NULL )
				{
					break;
				}
				if ( pSerial->IsConnected() == false )
				{
					break;
				}
				if ( pSerial->m_bFlag_Stop == true )	//! Thread를 멈춘다.
				{
					break;
				}
								
				memset(byRecvBuff, 0x00, 4096);
				//! byRecvBuff에 수신된 데이터를 임시 저장한다. 
				dwReceive = pSerial->ReceiveComm( byRecvBuff, sizeof(byRecvBuff) );

				if (dwReceive > 0 && g_Comm_bReady_UV==false)
				{
					CString tmp;
					tmp.Format("%s", byRecvBuff);
					int index = tmp.Find("CNT1OK");

					if(index>=0)
					{
						g_Comm_bReady_UV = true;
					}
				}
				//! 현재 설정된 m_pReceiveProcPtr 포인터를 가져온다. 
				pSerial->m_csReceiveProcPtr.Lock();
				pReceiveProcPtr = pSerial->m_pReceiveProcPtr;
				pSerial->m_csReceiveProcPtr.Unlock();

				if ( pSerial->m_strCommStateInfo.bFlag_Recv_Acting_In_Thread == true )
				{
					//! 수신 데이터를 처리하는 중일 때

					Sleep(10);
					continue;
				}

				//! byRecvBuff의 데이터를 전달하여, CComm_RS232C 클래스에서 상속받은 클래스에서 처리하도록 한다. 
				if ( pReceiveProcPtr != NULL )
				{
					pSerial->m_strCommStateInfo.bFlag_Recv_Acting_In_Thread = true;

					if ( pSerial->m_strCommStateInfo.bFlag_Thread_Active == false )
					{
						//! 실질적인 동작을 차단한다. 
					}
					else
					{
	//					pSerial->ProcessReceiveData( pReceiveProcPtr, byRecvBuff, (int)dwReceive, pSerial->m_strCommStateInfo.bFlag_Thread_Active, iCnt_Recv_Action );
					}

					iCnt_Recv_Action++;

					pSerial->m_strCommStateInfo.bFlag_Recv_Acting_In_Thread = false;
				}

			}while(dwReceive);

			//! 수신 처리를 끝마치고 나서의 요청 작업
// LHC			pSerial->PostProcRecvData();
		}
	}//! while(1)

	if ( os.hEvent != NULL )
	{
		::CloseHandle(os.hEvent);
	}

	//! Thread가 종료되었음을 확인 설정한다. 
	if ( pSerial != NULL )
	{
		pSerial->m_strCommStateInfo.bFlag_Thread_Operate = false;
	}

	return 1;
}

bool CComm_RS232C::IsConnected()
{
	return m_strCommStateInfo.bFlag_Connected;
}

CString CComm_RS232C::GetCurrent_PortName()
{
	return m_strCommSetupInfo.sPortName;
}

DWORD CComm_RS232C::GetCurrent_BaudRate()
{
	return m_strCommSetupInfo.dwBaudRate;
}

BYTE CComm_RS232C::GetCurrent_DataBit()
{
	return m_strCommSetupInfo.byDataBit;
}

BYTE CComm_RS232C::GetCurrent_StopBit()
{
	return m_strCommSetupInfo.byStopBit;
}

BYTE CComm_RS232C::GetCurrent_ParityBit()
{
	return m_strCommSetupInfo.byParityBit;
}

//! 통신 시작 함수
//! [기능] RS-232C Serial 통신을 하기 위해 통신 포트를 연다. 
int CComm_RS232C::OpenPort(stringSetupInfo_RS232C *pstrSetupInfo)
{
	if ( pstrSetupInfo == NULL )
	{
		return -1;
	}

	if ( pstrSetupInfo->bFlag_Close_COM_Port == true )
	{
		if ( m_strCommStateInfo.bFlag_Connected == true )
		{
			//! 현재 포트가 열려 있으면, 닫고 재 설정한다. 
			ClosePort(pstrSetupInfo->iTimeOut_Close_Thread);
		}
	}
	else
	{
		if ( m_strCommStateInfo.bFlag_Connected == true )
		{
			return -2;
		}
	}

	CString sGetPortName = pstrSetupInfo->sPortName;

	sGetPortName.TrimLeft();
	sGetPortName.TrimRight();

	int iLen = sGetPortName.GetLength();

	//! 입력값 유효성 검사
	if ( iLen <= 0 )
	{
		return -3;
	}
	if ( pstrSetupInfo->dwBaudRate <= 0 )
	{
		return -4;
	}
	if ( pstrSetupInfo->byDataBit <= 0 )
	{
		return -5;
	}

	CString sPortName = _T("");

	if ( iLen > 4 )
	{
		//! COM10보다 클 경우
		sPortName = _T("\\\\.\\") + sGetPortName;
	}
	else
	{
		sPortName = sGetPortName;
	}

	//! Overlapped structure 초기화 
	m_osReceive.Offset = 0;
	m_osReceive.OffsetHigh = 0;
	m_osReceive.hEvent = NULL;

	m_osReceive.hEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
	if ( m_osReceive.hEvent == NULL )
	{
		ClosePort(pstrSetupInfo->iTimeOut_Close_Thread);
		return -6;
	}

	m_osSend.Offset = 0;
	m_osSend.OffsetHigh = 0;
	m_osSend.hEvent = NULL;

	m_osSend.hEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
	if ( m_osSend.hEvent == NULL )
	{
		ClosePort(pstrSetupInfo->iTimeOut_Close_Thread);
		return -7;
	}

	//! RS-232C 포트 열기 
	m_hComm = ::CreateFile(sPortName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
	if ( m_hComm == INVALID_HANDLE_VALUE )
	{
		DWORD dwError = ::GetLastError();
		ClosePort(pstrSetupInfo->iTimeOut_Close_Thread);
		return -8;
	}

	//! 포트 상태 설정 

	::SetCommMask(m_hComm, EV_RXCHAR);	//! EV_RXCHAR Event 설정 (Data is received on input)

	::SetupComm(m_hComm, 4096, 4096);	//! InQueue, OutQueue 크기 설정 

	::PurgeComm(m_hComm, PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR);	//! COM Port 내부 버퍼 비우기 

	//! Timeout 설정 (Non-blocking 수신 Read Timeout 설정)
	// 1) Blocking reads, which will cause the 'Read' method to block
	//    until the requested number of bytes have been read. This is
	//    useful if you know how many data you will receive.
	// 2) Non-blocking reads, which will read as many bytes into your
	//    buffer and returns almost immediately. This is often the
	//    preferred setting.
	COMMTIMEOUTS timeOuts;
	timeOuts.ReadIntervalTimeout = 0xFFFFFFFF;
	timeOuts.ReadTotalTimeoutMultiplier = 0;
	timeOuts.ReadTotalTimeoutConstant = 0;
	timeOuts.WriteTotalTimeoutMultiplier = 2 * CBR_9600 / pstrSetupInfo->dwBaudRate;
	timeOuts.WriteTotalTimeoutConstant = 0;
	::SetCommTimeouts(m_hComm, &timeOuts);

	//! dcb 설정, 포트의 실질적인 제어를 담당하는 DCB 구조체값 설정 
	DCB dcb;
	dcb.DCBlength = sizeof(DCB);

	::GetCommState(m_hComm, &dcb);	//! 현재 설정된 값을 가져온다. 

	//! the CTS (clear-to-send) signal 
	//! the DSR (data-set-ready) signal 
	//! The RTS (request-to-send) flow control

	//! 흐름 제어
	switch(pstrSetupInfo->eFlowControl)
	{
	case EHandshakeHardwareAdd:
		{
			dcb.fOutxCtsFlow = TRUE;					// Enable CTS monitoring
			dcb.fOutxDsrFlow = TRUE;					// Enable DSR monitoring
			dcb.fDtrControl = DTR_CONTROL_HANDSHAKE;	// Enable DTR handshaking
			dcb.fOutX = FALSE;							// Disable XON/XOFF for transmission
			dcb.fInX = FALSE;							// Disable XON/XOFF for receiving
			dcb.fRtsControl = RTS_CONTROL_HANDSHAKE;	// Enable RTS handshaking
		}
		break;
	case EHandshakeSoftwareAdd:
		{
			dcb.fOutxCtsFlow = FALSE;					// Disable CTS (Clear To Send)
			dcb.fOutxDsrFlow = FALSE;					// Disable DSR (Data Set Ready)
			dcb.fDtrControl = DTR_CONTROL_DISABLE;		// Disable DTR (Data Terminal Ready)
			dcb.fOutX = TRUE;							// Enable XON/XOFF for transmission
			dcb.fInX = TRUE;							// Enable XON/XOFF for receiving
			dcb.fRtsControl = RTS_CONTROL_DISABLE;		// Disable RTS (Ready To Send)
		}
		break;	
	default:
		{
			//! 'EHandshakeOff' 포함
			dcb.fOutxCtsFlow = FALSE;					// Disable CTS monitoring
			dcb.fOutxDsrFlow = FALSE;					// Disable DSR monitoring
			dcb.fDtrControl = DTR_CONTROL_DISABLE;		// Disable DTR monitoring
			dcb.fOutX = FALSE;							// Disable XON/XOFF for transmission
			dcb.fInX = FALSE;							// Disable XON/XOFF for receiving
			dcb.fRtsControl = RTS_CONTROL_DISABLE;		// Disable RTS (Ready To Send)
		}
		break;
	}//! switch(pstrSetupInfo->eFlowControl)
	
	//! If this member is TRUE, binary mode is enabled. 
	//! Windows does not support nonbinary mode transfers, so this member must be TRUE.
	dcb.fBinary = TRUE;
	//! The minimum number of bytes in use allowed in the input buffer before flow control is activated to allow transmission by the sender. 
	//! This assumes that either XON/XOFF, RTS, or DTR input flow control is specified in the fInX, fRtsControl, or fDtrControl members. 
	dcb.XonLim = 0;
	//! The minimum number of free bytes allowed in the input buffer before flow control is activated to inhibit the sender. 
	//! Note that the sender may transmit characters after the flow control signal has been activated, so this value should never be zero. 
	//! This assumes that either XON/XOFF, RTS, or DTR input flow control is specified in the fInX, fRtsControl, or fDtrControl members. 
	//! The maximum number of bytes in use allowed is calculated by subtracting this value from the size, in bytes, of the input buffer. 
	dcb.XoffLim = 0;
	//! If this member is TRUE, the communications driver is sensitive to the state of the DSR signal. 
	//! The driver ignores any bytes received, unless the DSR modem input line is high. 
	dcb.fDsrSensitivity = 0;
	//! If this member is TRUE, the driver terminates all read and write operations with an error status if an error occurs. 
	//! The driver will not accept any further communications operations until the application has acknowledged the error by calling the ClearCommError function. 
	dcb.fAbortOnError = 0; 

	//! 함수 인자로 입력한 포트 설정값 입력 
	dcb.BaudRate = pstrSetupInfo->dwBaudRate;
	dcb.ByteSize = pstrSetupInfo->byDataBit;
	dcb.StopBits = pstrSetupInfo->byStopBit;
	dcb.Parity   = pstrSetupInfo->byParityBit;

	//! 포트에 재 설정된 dcb 구조체를 반영 시킨다. 
	if ( ::SetCommState(m_hComm, &dcb) == FALSE )
	{
		ClosePort(pstrSetupInfo->iTimeOut_Close_Thread);
		return -9;
	}

	//! 설정값 멤버 변수에 저장
	m_strCommSetupInfo.Copy(pstrSetupInfo);

	//! 초기화
	m_strCommStateInfo.InitInfo();
	m_pThread_RecvComm = NULL;	

	//! Flag 값 설정
	m_strCommStateInfo.bFlag_Connected = true;
	if ( m_strCommSetupInfo.bFlag_Recv_ThreadStart == false )
	{
		//! RS-232C 통신이 연결되고 맨 처음 1번만 실행된다.
		ReadyDevice();

		return 1;
	}

	//! 수신 Thread 생성
	int iRet = StartThread(m_strCommSetupInfo.bFlag_Use_CPU_Affinity, m_strCommSetupInfo.aiCPU, intBufSize_RS232C_CPU_Core);
	if ( iRet < 0 )
	{
		return (-100 + iRet);
	}
	return 1;
}

//! 송신 작업 함수
//! [기능]   현재 열려진 포트에 szSend의 내용을 쓴다. 
//! [입력값] szSend : 송신할 문자열, bSTX_ETX : true이면 송신하려는 데이터의 앞, 뒤로 STX (0x02), ETX (0x03) 문자를 붙인다. 
//! [반환값] 실제로 송신한 Byte 개수를 반환한다. 
//! [주의]   송신할 문자열의 크기에 제한이 있다. 현재는 영문자, 숫자 기준으로 8190자까지 송신할 수 있다. 
DWORD CComm_RS232C::WriteComm(CString szSend, bool bSTX_ETX)
{
    int iStringSize = szSend.GetLength();
	if ( iStringSize <= 0 )
	{
		return 0;
	}
	
	const DWORD dwSendBufferSize = 8192;
	BYTE bySendBuffer[dwSendBufferSize];
	DWORD j, dwSendDataSize = (DWORD)iStringSize;

	//! 송신할 문자열이 너무 길 때
	if ( dwSendBufferSize < dwSendDataSize )
	{
		return 0;
	}

	//! CString -> BYTE 배열 
	for ( j = 0; j < dwSendDataSize; j++ )
	{
		bySendBuffer[j] = (BYTE)(szSend.GetAt(j));
	}

	return WriteComm(bySendBuffer, dwSendDataSize, bSTX_ETX);
}

//! 송신 작업 함수
//! [기능]   현재 열려진 포트에 pbyBuff의 내용을 nSizeToReceive만큼 쓴다. 
//! [입력값] pbyBuff : RS-232C Serial 통신으로 송신할 데이터가 있는 버퍼, nSizeToSend : 송신할 데이터의 크기, 단위 Byte 개수 
//!			 bSTX_ETX : true이면 송신하려는 데이터의 앞, 뒤로 STX (0x02), ETX (0x03) 문자를 붙인다. 
//! [반환값] 실제로 송신한 Byte 개수를 반환한다. 
//! [주의]   송신할 문자열의 크기에 제한이 있다. 현재는 영문자, 숫자 기준으로 8190자까지 송신할 수 있다. 
DWORD CComm_RS232C::WriteComm(BYTE *pbyBuff, DWORD nSizeToSend, bool bSTX_ETX)
{
	DWORD dwWritten = 0, dwError = 0, dwErrorFlags = 0;
	COMSTAT comstat;

	if ( m_hComm == NULL )	//! 포트의 유효성 검사 
	{
		return 0;
	}
	if ( pbyBuff == NULL || nSizeToSend <= 0 )	//! 송신 데이터의 유효성 검사 
	{
		return 0;
	}
	if ( m_strCommStateInfo.bFlag_Connected == false )//! 포트가 열려 있지 않은 상태일 때 
	{
		return 0;
	}

	if ( m_strCommStateInfo.bFlag_Sending == true )	//! 현재 송신 작업 중일 때 
	{
		return 0;
	}

	m_strCommStateInfo.bFlag_Sending = true;

	const DWORD dwSendBuffSize = 8192;
	BYTE bySendBuff[dwSendBuffSize];
	DWORD i, dwSendSize = nSizeToSend;

	if ( bSTX_ETX == true )
	{
		dwSendSize += 2;
	}
	
	if ( dwSendSize > dwSendBuffSize )	//! 송신하려는 데이터가 버퍼의 크기 보다 크다. 
	{
		m_strCommStateInfo.bFlag_Sending = false;
		return 0;
	}

	if ( bSTX_ETX == true )
	{
		bySendBuff[0] = STX;
		for ( i = 0; i < nSizeToSend; i++ )
		{
			bySendBuff[i + 1] = pbyBuff[i];
		}
		bySendBuff[i + 1] = ETX;
	}
	else
	{
		for ( i = 0; i < dwSendSize; i++ )
		{
			bySendBuff[i] = pbyBuff[i];
		}
	}

	if ( ::WriteFile( m_hComm, bySendBuff, dwSendSize, &dwWritten, &m_osSend ) == FALSE )
	{
		//! 아직 송신할 문자가 남았을 경우
		if ( ::GetLastError() == ERROR_IO_PENDING )
		{
			//! 읽을 문자가 남아 있거나 전송할 문자가 남아 있을 경우 Overapped IO의 특성에 따라 
			//! ERROR_IO_PENDING 에러 메시지가 전달된다. 
			//! 이때는 timeouts에 정해준 시간만큼 기다려준다. 
			while( ::GetOverlappedResult( m_hComm, &m_osSend, &dwWritten, TRUE ) == FALSE )
			{
				dwError = ::GetLastError();
				if ( dwError != ERROR_IO_INCOMPLETE )
				{
					::ClearCommError( m_hComm, &dwErrorFlags, &comstat );
					break;
				}
			}
		}
		else
		{
			dwWritten = 0;
			::ClearCommError( m_hComm, &dwErrorFlags, &comstat );
		}
	}

	m_strCommStateInfo.bFlag_Sending = false;
	
	//! 포트로 실제로 송신된 개수를 반환한다. 
	return dwWritten;
}

//! 수신 작업 함수
//! [기능]   열려진 포트로부터 nSizeToReceive만큼의 데이터를 읽어서 pbyBuff에 저장한다. 
//! [입력값] pbyBuff : RS-232C Serial 통신으로 수신할 데이터를 받을 버퍼, 
//!			 nSizeToReceive : 수신된 데이터에서 읽어들여 pbyBuff에 저장할 데이터의 크기, 단위 Byte 개수 
//! [반환값] 실제로 수신되어 읽혀진 Byte 개수를 반환한다. 
DWORD CComm_RS232C::ReceiveComm(BYTE *pbyBuff, DWORD nSizeToReceive)
{
//! [주의 사항] dwReaded값을 0으로 초기화하지 않으면 Release Static 컴파일 버전에서 오류가 발생한다. 
	DWORD	dwRead = 0, dwReaded = 0, dwError = 0, dwErrorFlags = 0;
	COMSTAT	comstat;

	if ( m_hComm == NULL )	//! 포트의 유효성 검사 
	{
		return 0;
	}
	if ( pbyBuff == NULL || nSizeToReceive <= 0 )	//! 수신 데이터 버퍼의 유효성 검사 
	{
		return 0;
	}
	if ( m_strCommStateInfo.bFlag_Connected == false )	//! 포트가 열려 있지 않은 상태일 때 
	{
		return 0;
	}

	//! System Queue에 도착한 Byte 개수만 미리 읽는다. 
	::ClearCommError( m_hComm, &dwErrorFlags, &comstat );
	dwRead = comstat.cbInQue;

	if ( dwRead > 0 )	//! System Queue에 수신된 데이터가 있을 때 
	{
		if ( ::ReadFile( m_hComm, pbyBuff, nSizeToReceive, &dwReaded, &m_osReceive ) == FALSE )
		{
			//! 수신할 데이터가 아직 남았을 때 
			if ( ::GetLastError() == ERROR_IO_PENDING )
			{
				//! timeouts에 정해준 시간만큼 기다려준다. 
				while( ::GetOverlappedResult( m_hComm, &m_osReceive, &dwReaded, TRUE ) == FALSE )
				{
					dwError = ::GetLastError();
					if ( dwError != ERROR_IO_INCOMPLETE )
					{
						::ClearCommError( m_hComm, &dwErrorFlags, &comstat );
						break;
					}
				}
			}
			else
			{
				dwRead = 0;
				::ClearCommError( m_hComm, &dwErrorFlags, &comstat );
			}
		}
	}

	//! 실제로 읽어들인 Byte 개수를 반환한다. 
	return dwReaded;
}

//! 통신 마침 함수
void CComm_RS232C::ClosePort()
{
	ClosePort(m_strCommSetupInfo.iTimeOut_Close_Thread);
}

//! 통신 마침 함수
//! [기능]   RS-232C Serial 통신 포트를 닫는다. Thread, Event 등을 해제한다. 
//! [입력값] iTimeOut : 수신 Thread 중지하는 작업의 대기 시간, 단위 msec 
void CComm_RS232C::ClosePort(int iTimeOut)
{
	//! 수신 Thread 작동을 중지시키기 위한 Flag 설정
	m_bFlag_Stop = true;

	if ( m_hComm != NULL )
	{
		//! Mask 해제, 대기하는 WaitCommEvent를 중지
		::SetCommMask(m_hComm, 0);
		//! 포트 비우기, 대기 중인 데이터를 비워준다. 
		::PurgeComm(m_hComm, PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR);
	}

	int iRet = Stop_Thread_Waiting(iTimeOut);

	if ( m_osSend.hEvent != NULL )
	{
		::CloseHandle(m_osSend.hEvent);
		m_osSend.hEvent = NULL;
	}

	if ( m_osReceive.hEvent != NULL )
	{
		::CloseHandle(m_osReceive.hEvent);
		m_osReceive.hEvent = NULL;
	}

	if ( m_hComm != NULL )
	{		
		//! 핸들 닫기 
		::CloseHandle(m_hComm);
		m_hComm = NULL;
	}

	m_strCommStateInfo.bFlag_Connected = false;
}
void CComm_RS232C::ReadyDevice()
{
	// 필요없음 LHC
}