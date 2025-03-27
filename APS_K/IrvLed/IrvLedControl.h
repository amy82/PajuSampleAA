#pragma once
#include "../keyence/Comm_RS232C.h"
class CIrvLedControl
{
public:
	CIrvLedControl(void);
	~CIrvLedControl(void);

	DWORD				dwReceive ;			//! 수신한 Byte 크기
	CComm_RS232C		serialOC;
	CComm_RS232C		serialChart;

	bool Irv_RS232_CommOpen(int iPort, int iBaudRate , int type);
	void Irv_RS232_CommClose();
	void Irv_Light_SetValue(int iValue, int type);
	void IrvLight_Power(int iValue , int type);
	bool func_LT9030_Connect(void);

	bool	bThreadHand;
	HANDLE	m_hThreadLed;		//THREAD 핸들
};

DWORD ThreadLedLT9030(CIrvLedControl* pIrvLedCtl);