#pragma once
#include "Comm_RS232C.h"
class CKeyenceSensor
{
public:
	CKeyenceSensor(void);
	~CKeyenceSensor(void);

	DWORD				dwReceive ;			//! 수신한 Byte 크기
	CComm_RS232C		serial;

	bool func_RS232_CommOpen(int iPort, int iBaudRate);
	void func_RS232_CommClose();

	bool func_LT9030_Connect(void);
	bool func_RS232_ScanCheck(CString &sComm);

	bool func_CL3000_Scan(double &laserVal);
	bool func_LT9030_Scan(double &laserVal);				//변위 측정 Reading
	bool func_LT9030_ReScan(CString &sRtnComm);				//변위 측정 재 Reading
	bool func_LT9030_AutoZeroSet(int iCh, bool bOn);		//Auto Zero Setting ON/OFF
	bool func_LT9030_KeyLock(bool bOn);						//Key Lock ON/OFF


	bool	bThreadHand;
	HANDLE	m_hThreadComm;		//THREAD 핸들

	bool func_CreateCommLT9030(void);
};

DWORD ThreadCommLT9030(CKeyenceSensor* pKeyence);