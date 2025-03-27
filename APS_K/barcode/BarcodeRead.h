#pragma once
#include "../keyence/Comm_RS232C.h"

class CBarcodeRead
{
public:
	CBarcodeRead(void);
	~CBarcodeRead(void);

	CComm_RS232C	serial;

	bool func_Comm_Open(int iPort, int iBoudRate);
	void func_Comm_Close(void);
	bool func_Barcode_Read(CString &BarcodeID);

};

