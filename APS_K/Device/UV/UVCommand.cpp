#include "StdAfx.h"
#include "UVCommand.h"

CUVCommand::CUVCommand(void)
{
	m_iRecvSize = 0;
	memset(m_acRecvStorage, 0, sizeof(m_acRecvStorage));
		
	m_iNo_Machine = -1;

	m_iMode_Control = 0;
	m_iMode_Program = 1;
	m_dOutputIntensity = 0.;

	//! [주의 사항] 반드시, '%'를 단위로 고정하여 사용한다. 
	m_iUnit_Output_Intensity = 1;

	m_bFlag_Request_INP = false;

	m_bFlag_Ready = false;
	m_bFlag_Stable = false;

	Init_Buffer_Input_Pin();
}


CUVCommand::~CUVCommand(void)
{
	//! UV Lamp RS-232C 통신 해제
	Close_Device();
}

//! [기능] Serial RS-232C 통신 시작
//! [주의 사항] 반드시, SetReceiveProcPtr 함수로 수신 처리를 할 Dialog나 GUI 클래스를 설정하고, 이 함수를 호출한다. 
bool CUVCommand::Connect_Device(int iPort)
{
	CString sPort;
	sPort.Format("COM%d", iPort);

	if ( sPort.GetLength() < 4 )
	{
		return false;
	}
	if ( sPort.Find(_T("COM"), 0) < 0 )
	{
		return false;
	}

	//! 초기화
	Init_Buffer_Input_Pin();

	m_bFlag_Ready = false;
	m_bFlag_Stable = false;
	//m_iNo_Machine = iNoMachine;

	//! 매뉴얼 32 페이지의 내용에 따라 입력
	strSetupInfo_RS232C strSerial;
	strSerial.InitInfo();
	strSerial.dwBaudRate = CBR_9600;	
	strSerial.byDataBit    = 8;
	strSerial.byStopBit    = ONESTOPBIT;
	strSerial.byParityBit  = NOPARITY;
	strSerial.sPortName    = sPort;
	strSerial.eFlowControl = EHandshakeOff;
	strSerial.bFlag_Close_COM_Port   = true;
	strSerial.bFlag_Use_CPU_Affinity = false;
	strSerial.bFlag_Recv_ThreadStart = true;
	strSerial.iTimeOut_Close_Thread  = 3000;
	int iReturn = OpenPort(&strSerial);

	if ( iReturn < 0 )
	{

		return false;
	}	
	
	return true;
}

//! [기능] Serial RS-232C 통신 마침
void CUVCommand::Close_Device()
{	
	//! 안전을 위해 셔터는 닫고, Lamp는 꺼둔다. 
	UV_Shutter_Close();
	UV_Lamp_Off();

	//! UV Lamp Front Panel에서 제어하는 방식으로 변경
	Set_Control_Mode_Front_Panel();

	//! RS-232C 통신을 마친다. 
	ClosePort();

	m_iNo_Machine = -1;
	m_bFlag_Ready = false;
	m_bFlag_Stable = false;
}

//! 수신 처리 Thread를 생성하고 나서, 맨처음 1번만 실행된다. 
 void CUVCommand::ReadyDevice()
 {
	 int iRet = 0;

	 //! PC에서 RS-232C 통신으로 제어하는 방식으로 변경
	 //iRet = Set_Control_Mode_RS232C();
	 Sleep(50);
	 //! Output Intensity를 RS-232C로 수동 조절하기 위하여 'Step 1'로 설정한다.
	// iRet = Set_Program_Mode_1_Step();
	 Sleep(50);
	 //! UV 빛의 세기를 설정한다. 
	// iRet = Set_Output_Intensity_1_Step(model.UV_Intensity);
	 Sleep(50);
	 //Time 설정
	 //iRet = Set_Shutter_AutoTime_1_Step(model.UV_Time/1000);
	 Sleep(50);

	 //! 안전을 위해 셔터는 반드시 닫아둔다. 
	// UV_Shutter_Close();
	 Sleep(50);
	 //! UV Lamp를 켠다. Lamp 안정화에 5분 정도가 걸리므로, 프로그램이 켜지자 마자 Lamp를 켜둔다. 
	// iRet = UV_Lamp_On();
	 Sleep(50);
	 //! 현재 장치의 상태를 알아낸다. 
	// iRet = Ask_Input_Pin();

	 //! UV Lamp 기본적인 작동 준비 완료
	 m_bFlag_Ready = true;
 }

 //! 수신 처리를 마칠때 마다, 1회 실행된다. 
 void CUVCommand::PostProcRecvData()
 {
	 /*if ( m_bFlag_Request_INP == true )
	 {
		 Ask_Output_Intensity();

		 m_bFlag_Request_INP = false;
	 }*/
 }

//! [기능] RS-232C Serial 통신으로 받은 문자열을 받아, STX, STX 문자를 구분 문자로 하여, 
//!		   1개의 문자열을 추출하여 OutputRecvData 함수에 전달한다. 
//! [주의 사항] 
//!       하지만, UV 장치는 STX, ETX 구분 문자를 구별하지 않으므로, 주의한다. 
//!	      수신 문자열에서 '0x0D'가 구분을 담당하지만, 1개의 문자열 내에서도 구분이 있다.
//!       Front Panel 제어 방식이면, 무조건 'ERR' 문자열이 수신 된다. 단, 'CNTQ'에서는 'ERR' 뒤에 'CNT0' 문자열이 온다. 
void CUVCommand::ProcessReceiveData(void *pProcPtr, BYTE *pbyBuff, int iSize, bool bFlag_Active, int iCnt_Recv)
{
	if ( m_iNo_Machine < 0 )
	{
		return;
	}
	if ( pProcPtr == NULL || pbyBuff == NULL || iSize <= 0 )
	{
		return;
	}
	
	TCHAR acRecvTmp[8192];
	memset(acRecvTmp, 0, sizeof(acRecvTmp));
	_tcscpy_s(acRecvTmp, m_acRecvStorage);	//! 저번 함수 호출 때에 남은 데이터를 가져온다. 

	int iRecvCnt = m_iRecvSize;
	if ( iRecvCnt < 0 )
	{
		iRecvCnt = 0;
	}

	int i = 0;
	for ( i = 0; i < iSize; i++ )
	{
		if ( (pbyBuff[i] == UV_STX)  && (iRecvCnt == 0) )		//! 시작
		{
			memset(acRecvTmp, 0, sizeof(acRecvTmp));
			iRecvCnt = 0;			
		}
		else if ( (pbyBuff[i] == UV_ETX) && (iRecvCnt > 0) )	//! 마침
		{
			acRecvTmp[iRecvCnt] = 0x00;
			iRecvCnt++;

			if ( bFlag_Active == true )
			{
				//! 준비된 수신 문자열을 실제로 사용한다. 
				OutputRecvData(pProcPtr, acRecvTmp, iRecvCnt, iCnt_Recv);
			}

			memset(acRecvTmp, 0, sizeof(acRecvTmp));
			iRecvCnt = 0;			
		}
		else
		{
			acRecvTmp[iRecvCnt] = (TCHAR)(pbyBuff[i]);	//! pbyBuff -> acRecvTmp 버퍼로 데이터를 옮긴다. 
			iRecvCnt++;
		}
	}

	acRecvTmp[iRecvCnt] = 0x00;
	m_iRecvSize = iRecvCnt;

	memset(m_acRecvStorage, 0, sizeof(m_acRecvStorage));
	_tcscpy_s(m_acRecvStorage, acRecvTmp);	//! 처리하고 남은 데이터를 다음 함수 호출때를 위해 저장해 둔다. 	
}

//! [기능] 수신 받은 문자열을 Parsing하거나, 다른 곳에 전달한다. 이 함수에 입력된 문자열은 STX, ETX 사이의 것이다. 
void CUVCommand::OutputRecvData(void *pProcPtr, TCHAR *pcBuff, int iDataSize, int iCnt_Recv)
{
	//! TCHAR* -> CString 
	CString sRecv = _T("");
	sRecv.Format(_T("%s"), pcBuff);

	int iStringLength = (int)(sRecv.GetLength());
	
	/*if ( pProcPtr != NULL )
	{
		((CAABonderDlg*)pProcPtr)->Parse_From_UV_Lamp(sRecv, iCnt_Recv, m_iNo_Machine);
	}*/
}

//! [기능] UV Controller에 데이터를 전송한다. 
//! [입력값] pbySend : 전송 데이터, iSendSize : 전송 데이터의 크기
//! [반환값] 전송에 성공하면 '1'을 반환하고, 그렇지 않으면 음수를 반환한다. 
//! [주의 사항] STX, ETX 문자를 포함한 전송 데이터를 입력하지 않는다. STX, ETX 문자는 이 함수에서 자동으로 포함시킨다. 
int CUVCommand::SendData_UV_Controller(BYTE *pbySend, int iSendSize)
{	
	if ( pbySend == NULL || iSendSize <= 0 )
	{
		return -1;
	}
	
	BYTE bySendBuf[256];
	memset(bySendBuf, 0x00, sizeof(bySendBuf));

	int i = 0;
	DWORD dwSendCnt = 0;

	//! 실제 UV Lamp 장치에서 테스트해 본 결과, 구분 문자를 끝에 1개를 붙여야 한다. (2013/5/3)
	//! 앞에 '0x0D'가 붙으면, 'ERR' 문자열이 수신된다. 

	//bySendBuf[dwSendCnt++] = 0x0D;
	for ( i = 0; i < iSendSize; i++ )
	{
		bySendBuf[dwSendCnt++] = pbySend[i];
	}
	bySendBuf[dwSendCnt++] = 0x0D;

	DWORD dwRet = WriteComm(bySendBuf, dwSendCnt);
	if ( dwRet < dwSendCnt )
	{
		return -3;
	}

	return 1;
}

bool CUVCommand::Altis_UV_Connect(int data)
{
	unsigned char sSendBuff[100];
	int nSendSize = 0;
	memset(sSendBuff, 0x00, sizeof(sSendBuff));
	CString sSend = _T("");

	

	if (data == 0)
	{
		//FF 03 00 00 00 05 90 17  
		sSendBuff[0] = 0xFF;								//Header
		sSendBuff[1] = 0x03;								//Length
		sSendBuff[2] = 0x00;
		sSendBuff[3] = 0x00;
		sSendBuff[4] = 0x00;
		sSendBuff[5] = 0x05;
		sSendBuff[6] = 0x90;
		sSendBuff[7] = 0x17;
		sSend = _T("FF03000000059017");
		
	}
	else if (data == 1)
	{
		//FF 03 01 00 00 2B 11 F7   
		sSendBuff[0] = 0xFF;								//Header
		sSendBuff[1] = 0x03;								//Length
		sSendBuff[2] = 0x01;
		sSendBuff[3] = 0x00;
		sSendBuff[4] = 0x00;
		sSendBuff[5] = 0x2B;
		sSendBuff[6] = 0x11;
		sSendBuff[7] = 0xF7;
		sSend = _T("FF030100002B11F7");
		
	}
	else if (data == 2)
	{
		//FF 03 02 00 00 2B 11 B3  
		sSendBuff[0] = 0xFF;								//Header
		sSendBuff[1] = 0x03;								//Length
		sSendBuff[2] = 0x02;
		sSendBuff[3] = 0x00;
		sSendBuff[4] = 0x00;
		sSendBuff[5] = 0x2B;
		sSendBuff[6] = 0x11;
		sSendBuff[7] = 0xB3;
		sSend = _T("FF030200002B11B3");
		
	}
	else if (data == 3)
	{
		//FF 03 03 00 00 2B 10 4F   
		sSendBuff[0] = 0xFF;								//Header
		sSendBuff[1] = 0x03;								//Length
		sSendBuff[2] = 0x03;
		sSendBuff[3] = 0x00;
		sSendBuff[4] = 0x00;
		sSendBuff[5] = 0x2B;
		sSendBuff[6] = 0x10;
		sSendBuff[7] = 0x4F;
		sSend = _T("FF030300002B104F");
		
	}
	else if (data == 4)
	{
		//FF 03 04 00 00 2B 11 3B
		sSendBuff[0] = 0xFF;								//Header
		sSendBuff[1] = 0x03;								//Length
		sSendBuff[2] = 0x04;
		sSendBuff[3] = 0x00;
		sSendBuff[4] = 0x00;
		sSendBuff[5] = 0x2B;
		sSendBuff[6] = 0x11;
		sSendBuff[7] = 0x3B;
		sSend = _T("FF030400002B113B");
	}
	
	int iRet = SendData_UV_Controller(sSend);
	if (iRet < 0)
	{
		return false;
	}

	return true;
	/*nSendSize = 8;

	Sleep(100);
	int nRetVal = SendData_UV_Controller(sSendBuff, nSendSize);
	if (nRetVal < 0)
	{
		return false;
	}

	return true;*/
}

bool CUVCommand::Altis_UC_Controller_OnOff(int channel, int onoff, int data)
{
	unsigned char sSendBuff[100];
	int nSendSize = 0;
	char mch = 0x00 + channel;
	memset(sSendBuff, 0x00, sizeof(sSendBuff));
	sSendBuff[0] = 0x01;								//Header 01 10 01 2A 00 01 02 00 01 70 9A 
	sSendBuff[1] = 0x10;								//Length
	sSendBuff[2] = 0x01;
	sSendBuff[3] = 0x2A;
	sSendBuff[4] = 0x00;
	sSendBuff[5] = 0x01;
	sSendBuff[6] = 0x02;
	sSendBuff[7] = 0x00;//(char)(mch & 0x00FF);	//Channel (0x1 ~ 0x4)
	sSendBuff[8] = (onoff == 0) ? 0x01 : 0x00;;
	sSendBuff[9] = 0x70;// (onoff == 0) ? 0x01 : 0x00;
	sSendBuff[10] = 0x9A;
	nSendSize = 11;
	//
	//sSendBuff[11] = 0x0A;
	//sSendBuff[12] = 0x0D;
	//01 10 01 2A 00 01 02 00 01 70 9A 
	CString sSend = _T("");

	sSend = _T("0110012A0001020001709A");
	int iRet = SendData_UV_Controller(sSend);
	if (iRet < 0)
	{
		return false;
	}

	return true;
	/*Sleep(100);
	int nRetVal = SendData_UV_Controller(sSendBuff, nSendSize);
	if (nRetVal < 0)
	{
		return false;
	}

	return true;*/
}

//! [기능] UV Controller에 데이터를 전송한다. 
//! [입력값] sSend : 전송 데이터, 전송 데이터 크기는 내부에서 처리한다. 
//! [반환값] 전송에 성공하면 '1'을 반환하고, 그렇지 않으면 음수를 반환한다. 
//! [주의 사항] STX, ETX 문자를 포함한 전송 데이터를 입력하지 않는다. STX, ETX 문자는 이 함수에서 자동으로 포함시킨다. 
int CUVCommand::SendData_UV_Controller(CString sSend)
{
	int iStringSize = sSend.GetLength();
	if ( iStringSize <= 0 )
	{
		return -1;
	}

	BYTE bySendBuffer[256];
	memset(bySendBuffer, 0x00, sizeof(bySendBuffer));

	int i = 0;
	for ( i = 0; i < iStringSize; i++ )
	{
		bySendBuffer[i] = (BYTE)(sSend.GetAt(i));
	}

	int iRet = SendData_UV_Controller(bySendBuffer, iStringSize);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	return 1;
}

void CUVCommand::Set_Flag_UV_Lamp_Stable()
{
	m_bFlag_Stable = true;
}

//! UV Lamp가 기본적인 동작 준비를 마치면 true를 반환
bool CUVCommand::IsReady()
{
	if ( m_iNo_Machine < 0 )
	{
		return false;
	}

	return m_bFlag_Ready;
}

//! UV Lamp가 안정화되면 true를 반환
bool CUVCommand::IsStable_UV_Lamp()
{
	if ( IsReady() == false )
	{
		return false;
	}

	return m_bFlag_Stable;
}

int CUVCommand::Set_Control_Mode_Front_Panel()
{
	CString sSend = _T("");

	sSend = _T("CNT0");

	int iRet = SendData_UV_Controller(sSend);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	return 1;
}
int CUVCommand::Set_Control_Mode_RS232C()
{
	CString sSend = _T("");

	sSend = _T("CNT1");

	int iRet = SendData_UV_Controller(sSend);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	return 1;
}
int CUVCommand::Ask_Control_Mode()
{
	CString sSend = _T("");

	sSend = _T("CNTQ");

	int iRet = SendData_UV_Controller(sSend);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	return 1;
}

int CUVCommand::Set_Program_Mode_1_Step()
{
	CString sSend = _T("");

	sSend = _T("PROG_1STEP");

	int iRet = SendData_UV_Controller(sSend);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	return 1;
}
int CUVCommand::Set_Program_Mode_7_Steps()
{
	CString sSend = _T("");

	sSend = _T("PROG_7STEP");

	int iRet = SendData_UV_Controller(sSend);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	return 1;
}
int CUVCommand::Ask_Program_Mode()
{
	CString sSend = _T("");
#ifdef	ON_LINE_UV_LAMP
	sSend = _T("PROG?");

	int iRet = SendData_UV_Controller(sSend);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	for (int i=0; i<10; i++)
	{
		::Sleep(20);
		checkMessage();
	}

	if (iRet == 0)
	{
		return -1;
	}
#endif

	return 1;
}
	
int CUVCommand::UV_Lamp_On()
{
	CString sSend = _T("");

	sSend = _T("L1");

	int iRet = SendData_UV_Controller(sSend);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	return 1;
}
int CUVCommand::UV_Lamp_Off()
{
	CString sSend = _T("");

	sSend = _T("L0");

	int iRet = SendData_UV_Controller(sSend);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	return 1;
}
int CUVCommand::UV_Shutter_PowerSet(int value)
{
	CString sSend = _T("");

	sSend.Format(":EP,%d\n", value);
	int iRet = SendData_UV_Controller(sSend);
	if (iRet < 0)
	{
		return (-10 + iRet);
	}

	return 1;
}
int CUVCommand::UV_Shutter_Open()
{
	CString sSend = _T("");

	sSend = _T(":EONT\n");
	//sSend.AppendFormat("%d\n", value);
	int iRet = SendData_UV_Controller(sSend);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	return 1;
}
int CUVCommand::UV_Shutter_Close()
{
	CString sSend = _T("");

	//sSend = _T("S0");
	sSend = _T(":E0\n");
	int iRet = SendData_UV_Controller(sSend);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	return 1;
}

int CUVCommand::Set_Shutter_AutoTime_1_Step(double fi_dTime)
{
	CString sSend = _T("");

	if ( fi_dTime < 0 || fi_dTime > 999.9 )
	{
		return -1;
	}

	CString sFormat = _T(""), sNumber = _T("");
	sFormat = _T("%05.1f");
	sNumber.Format(sFormat, fi_dTime);
	sSend.Format(_T("AT%s"), sNumber);

	int iRet = SendData_UV_Controller(sSend);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	return 1;
}
int CUVCommand::Ask_Shutter_AutoTime_1_Step(double *fo_pdTime)
{
	if ( fo_pdTime == NULL )
	{
		return -1;
	}

	CString sSend = _T("");

	sSend = _T("ATQ");

	int iRet = SendData_UV_Controller(sSend);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	return 1;
}

int CUVCommand::Start_Shutter_Auto_Operation_1_Step()
{
	CString sSend = _T("");

	sSend = _T("ATS");

	int iRet = SendData_UV_Controller(sSend);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	return 1;
}
int CUVCommand::Ask_RemainTime_Shutter_Auto_Operation_1_Step(double *fo_pdTime)
{
	if ( fo_pdTime == NULL )
	{
		return -1;
	}

	CString sSend = _T("");

	sSend = _T("ATT");

	int iRet = SendData_UV_Controller(sSend);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	return 1;
}

int CUVCommand::Set_Diaphragm_Stop()
{
	CString sSend = _T("");

	sSend = _T("INT0");

	int iRet = SendData_UV_Controller(sSend);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	return 1;
}
int CUVCommand::Set_Diaphragm_Up()
{
	CString sSend = _T("");

	sSend = _T("INT1");

	int iRet = SendData_UV_Controller(sSend);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	return 1;
}
int CUVCommand::Set_Diaphragm_Down()
{
	CString sSend = _T("");

	sSend = _T("INT2");

	int iRet = SendData_UV_Controller(sSend);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	return 1;
}
int CUVCommand::Set_Diaphragm_Up_1_Point()
{
	CString sSend = _T("");

	sSend = _T("INT3");

	int iRet = SendData_UV_Controller(sSend);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	return 1;
}
int CUVCommand::Set_Diaphragm_Down_1_Point()
{
	CString sSend = _T("");

	sSend = _T("INT4");

	int iRet = SendData_UV_Controller(sSend);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	return 1;
}

int CUVCommand::Set_Output_Intensity_1_Step(double fi_dInput)
{
	CString sSend = _T("");

	CString sFormat = _T(""), sNumber = _T("");
	
	if ( m_iUnit_Output_Intensity == 1 )
	{
		//! 단위 %

		if ( fi_dInput < 0. )
		{
			fi_dInput = 0.;
		}
		if ( fi_dInput > 100. )
		{
			fi_dInput = 100.;
		}
		
		sNumber.Format(_T("%03d"), (int)fi_dInput);
	}
	else
	{
		//! 단위 W

		if ( fi_dInput < 0. )
		{
			fi_dInput = 0.;
		}
		
		sFormat = _T("%3.2f");
		sNumber.Format(sFormat, fi_dInput);
	}

	sSend.Format(_T("INTSET%s"), sNumber);

	int iRet = SendData_UV_Controller(sSend);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	return 1;
}
int CUVCommand::Ask_Output_Intensity()
{
	CString sSend = _T("");

	sSend = _T("INTQ");

	int iRet = SendData_UV_Controller(sSend);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	return 1;
}

int CUVCommand::Reset_UV_Lamp_Operation_Time()
{
	CString sSend = _T("");

	sSend = _T("LAMPCLR");

	int iRet = SendData_UV_Controller(sSend);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	return 1;
}
int CUVCommand::Ask_UV_Lamp_Operation_time()
{
	CString sSend = _T("");

	sSend = _T("LIF");

	int iRet = SendData_UV_Controller(sSend);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	return 1;
}

int CUVCommand::Set_Cure_Program_Info_7_Steps(int fi_iNoProgram, sreSetupInfo_UV_Program *fi_pstrInput)
{	
	if ( fi_iNoProgram < 1 || fi_iNoProgram > 9 )
	{
		return -1;
	}
	if ( fi_pstrInput == NULL )
	{
		return -2;
	}

	int iRet = fi_pstrInput->IsValid();

	if ( iRet < 0 )
	{
		return (-1000 + iRet);
	}

	CString sSend = _T("");
	CString sParameter = _T("");
	CString sFormat = _T(""), sNumber = _T(""), sTime = _T("");
	int i = 0;

	for ( i = 0; i < iBufSize_Step_In_Cure; i++ )
	{
		if ( fi_pstrInput->iUnit_Output_Intensity == 1 )
		{
			//! %
			sNumber.Format(_T("%03d"), (int)(fi_pstrInput->adIntensity[i]));
		}
		else
		{
			//! W
			sFormat = _T("%3.2f");
			sNumber.Format(sFormat, fi_pstrInput->adIntensity[i]);
		}

		sFormat = _T("%05.1f");		
		sTime.Format(sFormat, fi_pstrInput->adTime[i]);

		sParameter += sNumber;
		sParameter += _T(",");

		sParameter += sTime;
		sParameter += _T(",");
	}//! for ( i = 0; i < iBufSize_Step_In_Cure; i++ )

	sParameter.TrimRight(_T(","));

	sSend.Format(_T("CURE%d%d%d:%s"), fi_iNoProgram, fi_pstrInput->iModel_Shutter, fi_pstrInput->iUnit_Output_Intensity, sParameter);

	iRet = SendData_UV_Controller(sSend);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	return 1;
}
int CUVCommand::Ask_Cure_Program_Info_7_Steps(int fi_iNoProgram)
{
	if ( fi_iNoProgram < 1 || fi_iNoProgram > 9 )
	{
		return -1;
	}

	CString sSend = _T("");

	sSend.Format(_T("CUREQ%d"), fi_iNoProgram);

	int iRet = SendData_UV_Controller(sSend);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	return 1;
}
int CUVCommand::Start_Cure_Program_7_Steps(int fi_iNoProgram)
{
	if ( fi_iNoProgram < 1 || fi_iNoProgram > 9 )
	{
		return -1;
	}

	CString sSend = _T("");

	sSend.Format(_T("START%d"), fi_iNoProgram);

	int iRet = SendData_UV_Controller(sSend);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	return 1;
}
int CUVCommand::Stop_Cure_Program_7_Steps()
{	
	CString sSend = _T("");

	sSend = _T("STOP");

	int iRet = SendData_UV_Controller(sSend);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	return 1;
}
int CUVCommand::Ask_Cure_Program_Progress_7_Steps()
{	
	CString sSend = _T("");

	sSend = _T("STPQ");

	int iRet = SendData_UV_Controller(sSend);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	return 1;
}

//! 'INP' 관련 Flag 버퍼 초기화
//! RS-232C 통신 관련해서는 사용되지 않음, 사용자 편의를 위한 Flag 변수로 사용하기 위함 (특히, 중복 처리 방지)
void CUVCommand::Init_Buffer_Input_Pin()
{
	int i = 0;
	for ( i = 0; i < iBufSize_INP_Bit; i++ )
	{
		m_aiBuf_INP_Bit[i] = 0;
	}
}

//! 'INP' Command를 UV 장치에 보내어 현재의 다양한 설정 정보를 알아낸다. 
//! 'CAABonderDlg::Parse_From_UV_Lamp' 함수의 'INP' 항목에서 수신 처리
int CUVCommand::Ask_Input_Pin()
{
	CString sSend = _T("");

	sSend = _T("INP");

	int iRet = SendData_UV_Controller(sSend);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	return 1;
}

//! NG 상세 내용 문자열을 알아낸다. 
//! UV 장치에서의 수신 문자열에서 'NG' 다음의 숫자의 의미를 이용한다. 
CString CUVCommand::GetExplanationNG(CString sNumberNG)
{
	CString sRet = _T("");
	sRet.Format(_T("NG Number [%s]"), sNumberNG);

	if ( sNumberNG.GetLength() != 2 )
	{
		return sRet;
	}	

	sNumberNG.TrimLeft(_T("0"));
	sNumberNG.TrimRight(_T("0"));

	int iNumberNG = _ttoi(sNumberNG);

	switch(iNumberNG)
	{
	case 1:
		{
			sRet += _T(" : ");
			sRet += _T("Lamp trigger being applied. ");
		}
		break;
	case 2:
		{
			sRet += _T(" : ");
			sRet += _T("Memory cure being executed. ");
		}
		break;
	case 3:
		{
			sRet += _T(" : ");
			sRet += _T("Shutter auto function being executed. ");
		}
		break;
	case 4:
		{
			sRet += _T(" : ");
			sRet += _T("Optical feedback unit unconnected. ");
		}
		break;
	case 5:
		{
			sRet += _T(" : ");
			sRet += _T("Error not reaching memory cure setting of output intensity(W) ");
		}
		break;
	}//! switch(iNumberNG)

	return sRet;
}