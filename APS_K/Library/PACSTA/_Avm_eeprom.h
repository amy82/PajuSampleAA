#pragma once

#include "CommThread.h"

#define READ            1
#define WRITE           2
#define EXIT            3

#define BUFFER_SIZE     32



typedef struct EEPROM_READ_WRITE
{

	BYTE RW;

	/*ulong GEELY_PART_NO;
	ulong VCC_PART_NO;
	uint SerialNO;

	UINT Fx;
	uint Fy;
	uint Cx;
	uint Cy;
	uint K1;
	uint K2;
	uint K3;
	uint K4;
	uint K5;

	uint D1;
	uint D2;
	uint D3;
	uint D4;
	uint D5;
	uint D6;
	uint D7;
	uint D8;
	uint D9;

	BYTE CRC;

	BYTE Address;
	BYTE Data;*/
}_EEPROM_READ_WRITE;
class CAvm_eeprom
{
public:
	CAvm_eeprom();
	~CAvm_eeprom();

	bool AVMUart_init();
	bool AVMUart_sensorSend();
	bool ocSend();
	//
	LONG OnReceive(UINT port, LONG lParam);	//메세지 처리기
	CCommThread m_Comm;	//시리얼 통신 객체
	CQueue m_Queue;	//시리얼 통신 객체C

	void FittingSet();
	void EdgeOff();


};

