#include "StdAfx.h"
#include "BarcodeRead.h"
#include "../AA BonderDlg.h"



CBarcodeRead::CBarcodeRead(void)
{
}


CBarcodeRead::~CBarcodeRead(void)
{
}

bool CBarcodeRead::func_Comm_Open(int iPort, int iBoudRate)
{

	CString sPort;
	sPort.Format("COM%d", iPort);
	int iReturn;

	stringSetupInfo_RS232C stringSerial;
	stringSerial.InitInfo();
	stringSerial.dwBaudRate   = (DWORD)iBoudRate;//CBR_9600;
	stringSerial.byDataBit    = 8;
	stringSerial.byStopBit    = ONESTOPBIT;
	stringSerial.byParityBit  = NOPARITY;
	stringSerial.sPortName    = sPort;
	stringSerial.eFlowControl = EHandshakeUnknownAdd;
	stringSerial.bFlag_Close_COM_Port   = true;
	stringSerial.bFlag_Use_CPU_Affinity = false;
	stringSerial.bFlag_Recv_ThreadStart = false;	//! 수신 데이터 처리용 Thread를 생성하지 않음
	stringSerial.iTimeOut_Close_Thread  = 3000;
	iReturn = serial.OpenPort(&stringSerial);

	if ( iReturn < 0 )
	{
		return false;
	}

	return true;
}


void CBarcodeRead::func_Comm_Close(void)
{
	serial.ClosePort(300);
}

bool CBarcodeRead::func_Barcode_Read(CString &BarcodeID)
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	BYTE		byRecvBuff[4096];		//! 수신 버퍼
	DWORD		dwReceive;
	memset(byRecvBuff, 0x00, 4096);

	dwReceive = serial.ReceiveComm( byRecvBuff, sizeof(byRecvBuff) );  // 결과값 받기

	if(dwReceive > 1)
	{
		BarcodeID = byRecvBuff;
		return TRUE;
	}

	return false;
}

