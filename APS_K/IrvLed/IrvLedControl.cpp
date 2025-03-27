#include "StdAfx.h"
#include "IrvLedControl.h"

CIrvLedControl::CIrvLedControl(void)
{
	m_hThreadLed = NULL;
}


CIrvLedControl::~CIrvLedControl(void)
{
}


bool CIrvLedControl::Irv_RS232_CommOpen(int iPort, int iBaudRate , int type)
{
	CString sPort;
	sPort.Format("COM%d", iPort);
	int iReturn;

	stringSetupInfo_RS232C stringSerial;
	stringSerial.InitInfo();
	stringSerial.dwBaudRate   = (DWORD)iBaudRate;//CBR_9600;
	stringSerial.byDataBit    = 8;
	stringSerial.byStopBit    = ONESTOPBIT;
	stringSerial.byParityBit  = NOPARITY;
	stringSerial.sPortName    = sPort;
	stringSerial.eFlowControl = EHandshakeUnknownAdd;
	stringSerial.bFlag_Close_COM_Port   = true;
	stringSerial.bFlag_Use_CPU_Affinity = false;
	stringSerial.bFlag_Recv_ThreadStart = false;	//! 수신 데이터 처리용 Thread를 생성하지 않음
	stringSerial.iTimeOut_Close_Thread  = 3000;
	if(type==0)
	{
		iReturn = serialOC.OpenPort(&stringSerial);
	}else
	{
		iReturn = serialChart.OpenPort(&stringSerial);
	}
	

	if ( iReturn < 0 )
	{
		return false;
	}

	return true;
}

void CIrvLedControl::Irv_RS232_CommClose()
{
	serialOC.ClosePort(300);
	serialChart.ClosePort(300);
}
void CIrvLedControl::IrvLight_Power(int iValue , int type)
{
	if(iValue>1)
	{
		iValue = 1;
	}
	CString sSendMsg = _T("");
	CString sRtnComm = _T("");
	CString sMsgBuff = _T("");
	CString ErrMsg = _T("");
	CString sMsg = _T("");
	CString sResult = _T("");
	unsigned char byteData[6];
	byteData[0] = 0x5A;
	byteData[1] = 0x07;
	byteData[2] = 0x01;
	//
	byteData[3] = 0x05;//0x05; = 0N/OFF
	
	byteData[4] = iValue;//0 = off , 1 = on
	byteData[5] = 0x88;

	if(type==0)
	{
		serialOC.WriteComm((BYTE*)byteData,6);   // Scan 명령어 전송
	}else
	{
		serialChart.WriteComm((BYTE*)byteData,6);   // Scan 명령어 전송
	}
	
	Sleep(100);

}
void CIrvLedControl::Irv_Light_SetValue(int iValue , int type)
{
	CString sSendMsg = _T("");
	CString sRtnComm = _T("");
	CString sMsgBuff = _T("");
	CString ErrMsg = _T("");
	CString sMsg = _T("");
	CString sResult = _T("");
	if(iValue<0)
	{
		iValue = 0;
	}
	BYTE byteData[7];
	memset(byteData, 0x00, sizeof(byteData));
	byteData[0] = 0x5A;
	byteData[1] = 0x07;
	byteData[2] = 0x01;
	//
	byteData[3] = 0x03;

	//byteData[4] = 0xE7;//0xE7// 0~100 ; A = 1.0 
	//byteData[5] = 0x3;//0x03; = 0011 ( 512+256) = 768,512,256
	if(iValue<256)
	{
		byteData[4] = iValue;
	}else
	{
		byteData[4] = iValue;//0xE7;
	}
	if(iValue>=768)
	{
		byteData[5] = 0x3;
	}else if(iValue>=512)
	{
		byteData[5] = 0x2;
	}else if(iValue>=256)
	{
		byteData[5] = 0x1;
	}else
	{
		byteData[5] = 0x0;
	}
	//999  0x3E7
	byteData[6] = 0x88;//packet End

	if(type==0)
	{
		serialOC.WriteComm((BYTE*)byteData,7);   // Scan 명령어 전송
	}else
	{
		serialChart.WriteComm((BYTE*)byteData,7);   // Scan 명령어 전송
	}
	Sleep(100);

	
}