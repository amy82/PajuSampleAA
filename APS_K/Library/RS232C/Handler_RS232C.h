#pragma once

//! RS-232C Serial 통신 클래스
//! Maked by LHW (2013/2/6), Visual C++ 2010에서 제작
//! 마지막 작업 날짜 : 2013/5/3

//! 사용하는 RS-232C Serial Port (COM1, COM2, ...)마다 CHandler_RS232C 클래스를 상속한 클래스를 만들어서 사용한다. 
//! CHandler_RS232C 클래스는 RS-232C Serial 통신의 기본적인 형태를 다룬다. 

//! CHandler_RS232C 클래스를 상속한 클래스에서는 해당 Port에 장착되는 장비의 Packet Protocol 처리를 제작한다. 


#include <afxmt.h>	//! CCriticalSection 때문에 필요

//! [주의 사항] 장비에 따라 STX, ETX는 사용하지 않기도 한다. (장비의 Protocol 문서 확인 필요)
//! 문자열 패킷의 시작에 사용되는 Ascii 분자
#define STX	0x02
//! 문자열 패킷의 마침에 사용되는 Ascii 분자
#define ETX 0x03


//! PC의 Serial Port 목록을 알아낸다. 
//! 프로그램 전체에서 1개의 객체만 있으면 된다.
class CList_RS232C
{
public:
	CList_RS232C(void);
	~CList_RS232C(void);

public:
	CStringArray m_arrList_ComPort;	//! PC의 Serial Port 목록

	bool GetList_SerialPort();		//! PC의 Serial Port를 알아내어 m_arrList_ComPort에 저장한다. 
};


//! RS-232C Serial 통신 설정을 도와주는 클래스
//!  - 멤버 함수에 특정 index를 입력하면, CHandler_RS232C 클래스에서 사용할 수 있는RS-232C 설정값을 반환한다. 
//!  - GUI의 Combo Box와 함께 사용하면, 편리하게 사용할 수 있다. 
//! # RS-232C 송/수신 데이터 처리에 유용한 함수 포함
class CHelper_Setup_RS232C
{
public:
	CHelper_Setup_RS232C(void);
	~CHelper_Setup_RS232C(void);

public:
	//! index (0 based) ----->> CHandler_RS232C 클래스에서 사용할 수 있는RS-232C 설정값
	//! [주의 사항] 
	//!   1) 해당 값이 없으면, false를 반환
	//!	  2) psItemName에 CString 변수가 입력되고, 함수 반환값이 true이면, 해당 문자열이 반환된다. 이 문자열로 Combo Box를 구성할 수 있다.
	bool GetValue_BaudRate (int iIndex_BaudRate,  DWORD &dwRetBaudRate,  CString *psItemName = NULL);	
	bool GetValue_DataBit  (int iIndex_DataBit,   BYTE  &byRetDataBit,   CString *psItemName = NULL);
	bool GetValue_StopBit  (int iIndex_StopBit,   BYTE  &byRetStopBit,   CString *psItemName = NULL);
	bool GetValue_ParityBit(int iIndex_ParityBit, BYTE  &byRetParityBit, CString *psItemName = NULL);

	//! CHandler_RS232C 클래스에서 사용할 수 있는RS-232C 설정값 ----->> index (0 based)
	//! [주의 사항] 해당 값이 없으면, 음수를 반환
	int GetIndex_BaudRate (DWORD dwBaudRate);	
	int GetIndex_DataBit  (BYTE  byDataBit);
	int GetIndex_StopBit  (BYTE  byStopBit);
	int GetIndex_ParityBit(BYTE  byParityBit);

	//! Baud Rate 값을 정수형으로 반환
	int GetBaudRateValue_Integer_FromConstant(DWORD dwBaudRate);

	//! 정수형 값을 BYTE 배열의 데이터로 변환
	int Convert_Integer_To_ArrayByte(int iInput, BYTE* pbyOutputBuf, int iOutputBufSize);
};

//! 흐름 제어 종류 (Handshaking)
// 1) No handshaking, so data is always send even if the receiver
//    cannot handle the data anymore. This can lead to data loss,
//    when the sender is able to transmit data faster then the
//    receiver can handle.
// 2) Hardware handshaking, where the RTS/CTS lines are used to
//    indicate if data can be sent. This mode requires that both
//    ports and the cable support hardware handshaking. Hardware
//    handshaking is the most reliable and efficient form of
//    handshaking available, but is hardware dependant.
// 3) Software handshaking, where the XON/XOFF characters are used
//    to throttle the data. A major drawback of this method is that
//    these characters cannot be used for data anymore.
typedef enum
{
	EHandshakeUnknown		= -1,	// Unknown
	EHandshakeOff			=  0,	// No handshaking
	EHandshakeHardware		=  1,	// Hardware handshaking (RTS/CTS)
	EHandshakeSoftware		=  2	// Software handshaking (XON/XOFF)
}EHandshake;

//! CPU Core 사용 설정 버퍼의 크기
const int iBufSize_RS232C_CPU_Core = 30;

//! RS-232C Serial 통신을 하는 장비마다의 설정 정보 구조체
struct strSetupInfo_RS232C
{
	//! COM Port 이름
	CString sPortName;

	//! RS-232C 통신 설정
	DWORD	dwBaudRate;
	BYTE	byDataBit;
	BYTE	byStopBit;
	BYTE	byParityBit;

	//! 흐름 제어
	EHandshake   eFlowControl;	
	
	//! 기존의 COM Port 처리 여부
	//! true이면, 기존의 열려 있는 COM Port를 닫고, 재 설정한다. 
	bool	bFlag_Close_COM_Port;
	//! bFlag_Close_COM_Port가 true일 때, Thread를 닫는데 주어지는 시간, 단위 msec
	//! ClosePort() 함수에서도 사용된다.
	int		iTimeOut_Close_Thread;

	//! Thread 설정
	bool    bFlag_Recv_ThreadStart; //! true이면, RS-232C COM Port를 열고 나서, 바로 수신 Thread를 생성한다. 
	int		aiCPU[iBufSize_RS232C_CPU_Core];
	bool	bFlag_Use_CPU_Affinity;	//! aiCPU 버퍼의 설정을 이용하여, 특정 CPU Core에서 수신 Thread 동작

	strSetupInfo_RS232C()
	{
		InitInfo();
	}

	void InitInfo()
	{
		sPortName   = _T("COM1");

		dwBaudRate  = CBR_38400;
		byDataBit   = 8;
		byStopBit   = ONESTOPBIT;
		byParityBit = NOPARITY;

		eFlowControl = EHandshakeOff;		
		
		bFlag_Close_COM_Port = false;
		iTimeOut_Close_Thread = 3000;

		bFlag_Recv_ThreadStart = false;
		int i = 0;
		for ( i = 0; i < iBufSize_RS232C_CPU_Core; i++ )
		{
			aiCPU[i] = 0;
		}
		bFlag_Use_CPU_Affinity = false;
	}

	strSetupInfo_RS232C& operator=(const strSetupInfo_RS232C &input)	//! 연산자 재정의
	{
		sPortName   = input.sPortName;

		dwBaudRate  = input.dwBaudRate;
		byDataBit   = input.byDataBit;
		byStopBit   = input.byStopBit;
		byParityBit = input.byParityBit;

		eFlowControl = input.eFlowControl;		
		
		bFlag_Close_COM_Port = input.bFlag_Close_COM_Port;
		iTimeOut_Close_Thread = input.iTimeOut_Close_Thread;

		bFlag_Recv_ThreadStart = input.bFlag_Recv_ThreadStart;
		int i = 0;
		for ( i = 0; i < iBufSize_RS232C_CPU_Core; i++ )
		{
			aiCPU[i] = input.aiCPU[i];
		}
		bFlag_Use_CPU_Affinity = input.bFlag_Use_CPU_Affinity;

		return *this;
	}

	bool Copy(strSetupInfo_RS232C *pstrInput)
	{
		if ( pstrInput == NULL )
		{
			return false;
		}

		sPortName   = pstrInput->sPortName;

		dwBaudRate  = pstrInput->dwBaudRate;
		byDataBit   = pstrInput->byDataBit;
		byStopBit   = pstrInput->byStopBit;
		byParityBit = pstrInput->byParityBit;

		eFlowControl = pstrInput->eFlowControl;		
		
		bFlag_Close_COM_Port  = pstrInput->bFlag_Close_COM_Port;
		iTimeOut_Close_Thread = pstrInput->iTimeOut_Close_Thread;

		bFlag_Recv_ThreadStart = pstrInput->bFlag_Recv_ThreadStart;
		int i = 0;
		for ( i = 0; i < iBufSize_RS232C_CPU_Core; i++ )
		{
			aiCPU[i] = pstrInput->aiCPU[i];
		}
		bFlag_Use_CPU_Affinity = pstrInput->bFlag_Use_CPU_Affinity;

		return true;
	}
};

//! RS-232C Serial 통신 상태 구조체
struct strStateInfo_RS232C
{
	//! COM Port가 열렸으면 true를 설정
	bool bFlag_Connected;
	//! 현재 송신 작업 중이면 true를 설정한다.
	bool bFlag_Sending;
	
	//! 수신 Thread가 작동 중이면 true로 설정
	bool bFlag_Thread_Operate;
	//! true이면,  수신 Thread가 정상 동작하도록 한다. 
	//! false이면, 수신 Thread가 Stop되지는 않으나 실질적인 동작을 하지 않도록 한다.
	bool bFlag_Thread_Active;
	//! 현재 수신 Thread에서 수신 작업 중이면 true를 설정한다.
	bool bFlag_Recv_Acting_In_Thread;

	strStateInfo_RS232C()
	{
		InitInfo();
	}

	void InitInfo()
	{
		InitInfo_Comm();

		InitInfo_Thread();
	}

	//! RS-232C 통신 관련 초기화
	void InitInfo_Comm()
	{
		bFlag_Connected   = false;
		bFlag_Sending     = false;
	}

	//! Thread 관련 초기화
	void InitInfo_Thread()
	{
		bFlag_Thread_Operate        = false;
		bFlag_Thread_Active         = true;
		bFlag_Recv_Acting_In_Thread = false;
	}

	strStateInfo_RS232C& operator=(const strStateInfo_RS232C &input)	//! 연산자 재정의
	{
		bFlag_Connected   = input.bFlag_Connected;
		bFlag_Sending     = input.bFlag_Sending;

		bFlag_Thread_Operate        = input.bFlag_Thread_Operate;
		bFlag_Thread_Active         = input.bFlag_Thread_Active;
		bFlag_Recv_Acting_In_Thread = input.bFlag_Recv_Acting_In_Thread;

		return *this;
	}
};

//! RS-232C Serial 통신 클래스
//! RS-232C Serial 통신을 하는 장비 (COM Port)마다 이 클래스를 상속한 클래스의 객체를 생성해야 한다. 
class CHandler_RS232C
{
public:
	CHandler_RS232C(void);
	~CHandler_RS232C(void);

private:
	// 특정 CPU에서 Thread를 사용할 때, 사용 CPU를 지정하기 위한 Mask 처리 관련
	DWORD				GetMask_CPU_Affinity(int *piBuf_CPU_Use, int iBufSize_CPU_Use);
	int					Set_CPU_Affinity(int *piBuf_CPU_Use, int iBufSize_CPU_Use);

	CWinThread			*m_pThread_RecvComm;				//! 수신 Thread 객체
	friend UINT			Thread_Receive_Comm(LPVOID pParam);	//! Thread 본체 함수, 수신 데이터를 처리한다. 	

protected:
	HANDLE		        m_hComm;			//! 통신 포트 파일 핸들
	
    OVERLAPPED	        m_osReceive;		//! 포트 파일 Overlapped structure
	OVERLAPPED	        m_osSend;			//! 포트 파일 Overlapped structure

	void*				m_pReceiveProcPtr;	  //! 수신 문자열을 보낼 클래스의 포인터
	CCriticalSection	m_csReceiveProcPtr;	  //! m_pReceiveProcPtr의 보호용
	
	bool				m_bFlag_Stop;		  //! true이면 작업 도중 수신 Thread를 중지한다. 초기값은 false이다.

	//! RS-232C 통신이 연결된 후에 맨 처음 1번 만 실행해야 할 기능을 구현하다. 
	virtual void ReadyDevice() = 0;

	//! 수신된 문자열을 위의 m_pReceiveProcPtr에 전달한다. 
	//! CHandler_RS232C 클래스를 상속한 클래스에서 구현해 준다. 
	//! [주의 사항] 
	//!		1) 위의 Thread_Receive_Comm 함수에서 호출되는 함수이다. "다른 곳에서는 이 함수를 호출하면 안된다 !!!!!!!!!!!! "
	//!     2) 하지만, 이 클래스를 상속한 클래스에서 반드시 내부 기능을 구현해야 한다. 즉, 수신 데이터를 받아 처리하는 기능을 구현해야 한다. 
	//!		   이는 현재의 클래스 구조를 유지하면서, 시간 지연 없이 수신 데이터의 처리를 가능하게 한다. 
	//! [입력값]
	//!		pProcPtr    : 현재 설정된 m_pReceiveProcPtr
	//!		pbyBuff     : 수신된 문자열
    //!     iSize       : 수신된 문자열의 크기
	//!		bActiveFlag : true이면 수신 문자열을 STX, ETX에 맞게 정리하나, 최종적으로 처리하지는 않는다. 
	//!     iCnt_Recv   : 수신 처리 회수
	virtual void ProcessReceiveData(void *pProcPtr, BYTE *pbyBuff, int iSize, bool bFlag_Active, int iCnt_Recv) = 0;

	//! 수신 처리를 끝마치고 나서의 요청 작업
	virtual void PostProcRecvData() = 0;

public:	
	bool	g_bReady_UV;
	strSetupInfo_RS232C m_strCommSetupInfo;	//! 통신이 연결될 때의 설정 정보
	strStateInfo_RS232C m_strCommStateInfo;	//! 통신이 연결되고 나서의 상태값

	//! 수신된 데이터를 최종적으로 처리하는 클래스를 설정한다. 
	//! m_pReceiveProcPtr를 설정한다.
	void    SetReceiveProcPtr(void* pInput);
	
	//! Thread 조작 함수
	int		StartThread(bool bFlag_Use_CPU_Affinity, int *piBuf_CPU_Use = NULL, int iBufSize_CPU_Use = 0);
	int		Stop_Thread();
	int		Stop_Thread_Waiting(int iTimeOut = 0);

	//! 현 상태 정보 반환
	bool    IsConnected();
	CString GetCurrent_PortName();
	DWORD	GetCurrent_BaudRate();
	BYTE	GetCurrent_DataBit();
	BYTE	GetCurrent_StopBit();
	BYTE	GetCurrent_ParityBit();

	//! 통신 시작 함수
	int     OpenPort(strSetupInfo_RS232C *pstrSetupInfo);

	//! 송신 작업 함수
	DWORD   WriteComm(CString szSend, bool bSTX_ETX = false);
	DWORD   WriteComm(BYTE *pbyBuff, DWORD nSizeToSend, bool bSTX_ETX = false);

	//! 수신 작업 함수
	DWORD   ReceiveComm(BYTE *pbyBuff, DWORD nSizeToReceive);

	//! 통신 마침 함수
	void    ClosePort();
	void    ClosePort(int iTimeOut);

	int myNum;
};

