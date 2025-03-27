#include "stdafx.h"
#include "Avm_eeprom.h"
#include "../../AA Bonder.h"
#include "../../AA BonderDlg.h"

#include "../../DataHandler.h"
#include "UartAddress.h"
extern CSystemData sysData;


CAvm_eeprom::CAvm_eeprom()
{

}


CAvm_eeprom::~CAvm_eeprom()
{
}

bool CAvm_eeprom::AVMUart_init()
{
	CString port = "";
	if (!m_Comm.m_bConnected)
	{
		port.Format("\\\\.\\COM%d", sysData.iCommPort[COMM_AVM]);// sysData.iCommPort[COMM_RVC]);

		if (m_Comm.OpenPort(port, "115200", "8", "NO", "NO", "1"))//if (m_Comm.OpenPort("\\\\.\\COM10", "115200", "8", "NO", "NO", "1"))
		{
			//AfxMessageBox("1");
			theApp.MainDlg->putListLog("mComm Open ok!");
			//접속 성공
		}
		else
		{
			theApp.MainDlg->putListLog("mComm Open Fail!");
			//접속 실패
		}
	}
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
	//m_Comm.ComposePacket_oc(MESSAGEID_OC_WRITE_READ, MESSAGETYPE_NOTIFICATION, (BYTE)sizeof(sOC_Write), bytesForWrite);
	return true;
}
void CAvm_eeprom::FittingSet()
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
	
	m_Comm.ComposePacketFittingSet(MESSAGEID_SENSOR_RW, MESSAGETYPE_NOTIFICATION, (BYTE)sizeof(SENSOR_RW), fittingAddress);
}
void CAvm_eeprom::EdgeOff()
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

	m_Comm.ComposePacket(MESSAGEID_SENSOR_RW, MESSAGETYPE_NOTIFICATION, (BYTE)sizeof(SENSOR_RW), edgeData);
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
	//BYTE bytesForWrite[sizeof(SENSOR_RW)];
	//m_Comm.ComposePacketFittingSet(MESSAGEID_SENSOR_RW, MESSAGETYPE_NOTIFICATION, (BYTE)sizeof(SENSOR_RW), bytesForWrite);
	//m_Comm.ComposePacket(MESSAGEID_SENSOR_RW, MESSAGETYPE_NOTIFICATION, (BYTE)sizeof(SENSOR_RW), bytesForWrite);
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
