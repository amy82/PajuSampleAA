#pragma once
#include "Automotive.h"
#include "SerialComm.h"
class CRvc_Uart
{
public:
	CRvc_Uart();
	~CRvc_Uart();

	bool Rvc_Uartopen();
	bool Rvc_Uartsend();
	int DisableSharpness(IAutomotiveCamera* pCamera);
	int WriteRegister(IAutomotiveCamera* pCamera, unsigned char category, unsigned short addr, unsigned char dataLength, unsigned short data);
	void PrintLog(void* lpUserData, int nParaIndex, const char* lpszLog);

	pfnGetAutomotiveCamera fnGetInterface;
	IAutomotiveCamera* pCamera;
	bool isUsed;
	bool Rvc_Uartset();
	int DisableSend(unsigned char A[4] , unsigned char , unsigned char C[3]);
};

