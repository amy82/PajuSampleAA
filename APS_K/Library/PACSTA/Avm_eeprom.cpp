#include "stdafx.h"
#include "../../AA Bonder.h"
#include "../../AA BonderDlg.h"

#include "../../DataHandler.h"
#include "Avm_eeprom.h"

#include "CommThread.h"
extern CSystemData sysData;
extern	CModelData		model;
CCommThread m_Comm;	//시리얼 통신 객체
CQueue m_Queue;	//시리얼 통신 객체C
				// Message ID
BYTE MESSAGEID_EEPROM_WRITE_READ = 0x01;
BYTE MESSAGEID_HEARTBEAT = 0x02;
BYTE MESSAGEID_OC_WRITE_READ = 0x03;
BYTE MESSAGEID_SENSOR_RW = 0x04;

// Message Type
BYTE MESSAGETYPE_NOTIFICATION = 0x00;
BYTE MESSAGETYPE_REQUEST = 0x01;
BYTE MESSAGETYPE_RESPONSE = 0x02;
CAvm_eeprom::CAvm_eeprom()
{
	FittingIndex = 0;
	EdgeIndex = 0;
	FittingSetEnd = false;		//시작할땐 false로 끝나면 true
}


CAvm_eeprom::~CAvm_eeprom()
{
}

bool CAvm_eeprom::AVMUart_init()
{
	CString portStr = "";
	if (!m_Comm.m_bConnected)
	{
		portStr.Format("\\\\.\\COM%d", sysData.iCommPort[COMM_AVM]);
		theApp.MainDlg->putListLog(portStr);
		//OpenPort(m_stPort,m_stBaud, m_stDatabit,m_stFlow, m_stParity, m_stStop)
		if (m_Comm.OpenPort(portStr, "115200", "8", "NO", "NO", "1"))//if (m_Comm.OpenPort("\\\\.\\COM10", "115200", "8", "NO", "NO", "1"))
		{
			//AfxMessageBox("1");
			theApp.MainDlg->putListLog("Uart Port Open Ok!");
			//접속 성공
		}
		else
		{
			theApp.MainDlg->putListLog("Uart Port Open Fail!");
			//접속 실패
		}
	}
	else
	{
		theApp.MainDlg->putListLog("Uart Connected!");
	}
	return true;
}
bool  CAvm_eeprom:: AVMUart_Close()
{
	m_Comm.ClosePort();
	return true;
}
bool CAvm_eeprom::ocSend()
{
	OC_RW sOC_Write;
	sOC_Write.ShiftCx = -10;
	sOC_Write.ShiftCy = -10;
	sOC_Write.RW = 1;

	//BYTE* bytesForWrite = new BYTE[sizeof(sOC_Write)];
	//memcpy(bytesForWrite, &sOC_Write, sizeof(sOC_Write));
	BYTE bytesForWrite[sizeof(sOC_Write)];
	memcpy(&bytesForWrite, &sOC_Write, sizeof(sOC_Write));
	BYTE* p = bytesForWrite;
	m_Comm.ComposePacket_oc(MESSAGEID_OC_WRITE_READ, MESSAGETYPE_NOTIFICATION, (BYTE)sizeof(sOC_Write), bytesForWrite);
	return true;
}
void CAvm_eeprom::FittingSet()
{
	CString str = "";
	str.Format("AVM UART START [%d]", FittingIndex);
	theApp.MainDlg->putListLog(str);
	//F0600D9C
	//00000064
	//F06009C0
	BYTE   fittingAddress[49] = {
		0xA8, 0x09, 0x60, 0xF0 ,//0
		0xAC, 0x09, 0x60, 0xF0 ,//1
		0xB0, 0x09, 0x60, 0xF0 ,//2
		0xB4, 0x09, 0x60, 0xF0 ,//3
		0xB8, 0x09, 0x60, 0xF0 ,//4
		0xBC, 0x09, 0x60, 0xF0 ,//5
		0xC0, 0x09, 0x60, 0xF0 ,//6
		0xC4, 0x09, 0x60, 0xF0 ,//7
		0xC8, 0x09, 0x60, 0xF0 ,//8
		0xCC, 0x09, 0x60, 0xF0 ,//9
		0xD0, 0x09, 0x60, 0xF0 ,//10
		0xD4, 0x09, 0x60, 0xF0  //11
	};
	/*

	F06009A8
	F06009AC
	F06009B0
	F06009B4
	F06009B8
	F06009BC
	F06009C0
	F06009C4
	F06009C8
	F06009CC
	F06009D0
	F06009D4
*/

	m_Comm.ComposePacketFittingSet(MESSAGEID_SENSOR_RW, MESSAGETYPE_NOTIFICATION, (BYTE)sizeof(SENSOR_RW), fittingAddress);
}
void CAvm_eeprom::EdgeOff()
{
	BYTE  address[45] =
	{
		0xF8, 0x10, 0x60, 0xF0 , //0
		0xB8, 0x01, 0x60, 0xF0 , //1
		0xBC, 0x01, 0x60, 0xF0 , //2
		0xC0, 0x01, 0x60, 0xF0 , //3
		0xC4, 0x01, 0x60, 0xF0 , //4
		0xC8, 0x01, 0x60, 0xF0 , //5
		0xCC, 0x01, 0x60, 0xF0 , //6
		0xD0, 0x01, 0x60, 0xF0 , //7
		0xD4, 0x01, 0x60, 0xF0 , //8
		0xD8, 0x01, 0x60, 0xF0 , //9
		0xDC, 0x01, 0x60, 0xF0	 //10
	};							  
	BYTE  data[45] =
	{
		0x20, 0x00, 0x00, 0x00 , //0		 //0x00000020
		0x00, 0x00, 0x00, 0x00 , //1		 //0x00000000
		0x00, 0x00, 0x00, 0x00 , //2		 //0x00000000
		0x00, 0x00, 0x00, 0x00 , //3		 //0x00000000
		0x00, 0x00, 0x00, 0x00 , //4		 //0x00000000
		0x00, 0x00, 0x00, 0x00 , //5		 //0x00000000
		0x00, 0x00, 0x00, 0x00 , //6		 //0x00000000
		0x00, 0x00, 0x00, 0x00 , //7		 //0x00000000
		0x00, 0x00, 0x00, 0x00 , //8		 //0x00000000
		0x00, 0x00, 0x00, 0x00 , //9		 //0x00000000
		0x00, 0x00, 0x00, 0x00	 //10		 //0x00000000
	};
	m_Comm.ComposePacket(MESSAGEID_SENSOR_RW, MESSAGETYPE_NOTIFICATION, (BYTE)sizeof(SENSOR_RW), address, data, (sizeof(address) + 1));
}
void CAvm_eeprom::Ae_Gain()
{
	/*
	0xF0600890
	0xF060088C
	0xF060087C
	//
	0x00000001 (배율)
	0x00000000 (fix)
	0x00000001 (fix)

	*/
	//model.m_Uart_Range1
	//model.m_Uart_Range2
	BYTE  address[12] =
	{
		0x90, 0x08, 0x60, 0xF0 , //0
		0x8C, 0x08, 0x60, 0xF0 , //1
		0x7C, 0x08, 0x60, 0xF0  //2
	};
	BYTE  data[12] =
	{
		0x01, 0x00, 0x00, 0x00 , //0	0x01, 0x00, 0x00, 0x00
		0x00, 0x00, 0x00, 0x00 , //1 (fix)
		0x01, 0x00, 0x00, 0x00  //2  (fix)
	};
	
	m_Comm.ComposePacket(MESSAGEID_SENSOR_RW, MESSAGETYPE_NOTIFICATION, (BYTE)sizeof(SENSOR_RW), address, data, (sizeof(address) + 1));
}
void CAvm_eeprom::ExpousreTime()
{
	/*
	0xF0600880(H)
	0xF0600884(L)
	0xF0600888
	//
	0x000000 00
	~
	0x000004 0F [00~0F]
	0x00000000(fix)
	*/
	//model.m_Uart_Range1
	//model.m_Uart_Range2
	BYTE  address[12] =
	{
		0x80, 0x08, 0x60, 0xF0 , //0
		0x84, 0x08, 0x60, 0xF0 , //1
		0x88, 0x08, 0x60, 0xF0  //2
	};
	BYTE  data[12] =
	{
		0x00, 0x00, 0x00, 0x00 , //0	0x00, 0x00, 0x00, 0x00
		0x0f, 0x04, 0x00, 0x00 , //1	0x0f, 0x04, 0x00, 0x00
		0x01, 0x00, 0x00, 0x00  //2 (fix)
	};
	m_Comm.ComposePacket(MESSAGEID_SENSOR_RW, MESSAGETYPE_NOTIFICATION, (BYTE)sizeof(SENSOR_RW), address, data, (sizeof(address) + 1));
}
void CAvm_eeprom::HDROff()
{
	/*
	0xF0601810
	0xF0602754
	0xF0602758
	//
	0x000000C5
	0x00000000
	0x0000000F

	*/
	BYTE  address[12] =
	{
		0x10, 0x18, 0x60, 0xF0 , //0
		0x54, 0x27, 0x60, 0xF0 , //1
		0x58, 0x27, 0x60, 0xF0  //2
	};
	BYTE  data[12] =
	{
		0xC5, 0x00, 0x00, 0x00 , //0
		0x00, 0x00, 0x00, 0x00 , //1
		0x0F, 0x00, 0x00, 0x00  //2 
	};
	m_Comm.ComposePacket(MESSAGEID_SENSOR_RW, MESSAGETYPE_NOTIFICATION, (BYTE)sizeof(SENSOR_RW), address, data, (sizeof(address) + 1));
}
bool CAvm_eeprom::AVMUart_sensorSend()
{
	

	
	//
	//unsigned char   edgeData[45] = { 
	//	0xF8, 0x10, 0x60, 0xF0 ,
	//	0xB8, 0x01, 0x60, 0xF0 ,
	//	0xBC, 0x01, 0x60, 0xF0 ,
	//	0xC0, 0x01, 0x60, 0xF0 ,
	//	0xC4, 0x01, 0x60, 0xF0 ,
	//	0xC8, 0x01, 0x60, 0xF0 ,
	//	0xCC, 0x01, 0x60, 0xF0 ,
	//	0xD0, 0x01, 0x60, 0xF0 ,
	//	0xD4, 0x01, 0x60, 0xF0 , 
	//	0xD8, 0x01, 0x60, 0xF0 ,
	//	0xDC, 0x01, 0x60, 0xF0
	//};//1
	/*
	0xF06010F8		0x00000020		4032827640	//센서는반대로  F8,10.6060.F0
	0xF06001B8		0x00000000		4032823736
	0xF06001BC		0x00000000		4032823740
	0xF06001C0		0x00000000
	0xF06001C4		0x00000000
	0xF06001C8		0x00000000
	0xF06001CC		0x00000000
	0xF06001D0		0x00000000
	0xF06001D4		0x00000000
	0xF06001D8		0x00000000
	0xF06001DC		0x00000000
	//

	*/
	BYTE bytesForWrite[sizeof(SENSOR_RW)];
	m_Comm.ComposePacketFittingSet(MESSAGEID_SENSOR_RW, MESSAGETYPE_NOTIFICATION, (BYTE)sizeof(SENSOR_RW), bytesForWrite);
	return true;
}

//데이터 수신(메세지 처리기)
LONG CAvm_eeprom::OnReceive(UINT port, LONG lParam)
{
	BYTE aByte;
	m_Comm.m_bReserveMsg = false;

	int size = (m_Comm.m_QueueRead).GetSize();
	if (size == 0) return 0;
	for (int i = 0; i<size; i++)
	{
		(m_Comm.m_QueueRead).GetByte(&aByte);
		//aByte 이용 여기서 데이터 처리
	}
	return 0;
}
