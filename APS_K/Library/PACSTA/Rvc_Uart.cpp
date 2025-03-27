#include "stdafx.h"
#include "Rvc_Uart.h"

#include "../../AA Bonder.h"
#include "../../AA BonderDlg.h"


#include "../../DataHandler.h"
extern CSystemData sysData;
CRvc_Uart::CRvc_Uart()
{
	isUsed = false;
}


CRvc_Uart::~CRvc_Uart()
{
}
bool CRvc_Uart::Rvc_Uartsend()
{
	// true: trun on, false: turn off 
	theApp.MainDlg->putListLog("RVC UART START");
	int reserved = 0;
	if (pCamera->OriginalView(true, &reserved) <= 0)
	{
		//cout << "cannot show original view" << endl;
		theApp.MainDlg->putListLog("cannot show original view");
		return false;
	}

	if (DisableSharpness(pCamera) <= 0)
	{
		//cout << "cannot disable sharpness" << endl;
		theApp.MainDlg->putListLog("cannot disable sharpness");
		return false;
	}
	while(isUsed)
	{
		// Todo: Keep the original view sending TesterPresent
		pCamera->GetUDS()->TesterPresent(0);
		Sleep(2000); // 3000 ms 
	}
	return true;
}
bool CRvc_Uart::Rvc_Uartopen()
{
	int portNum = 7;// sysData.iCommPort[COMM_RVC];
	CString portStr;
	portStr.Format("\\\\.\\COM%d", portNum );
	theApp.MainDlg->putListLog(portStr);
	int ret = CSerialComm::GetInstance().Open(portNum, 416000, 8, ONESTOPBIT, EVENPARITY);//ONESTOPBIT, EVENPARITY );
	//int ret = CSerialComm::GetInstance().Open(COM_PORT, 416000, 8, ONESTOPBIT, EVENPARITY);
	if (ret <= 0)
	{
		theApp.MainDlg->putListLog("Uart Port Open Fail!");
		return false;
	}
	else
	{
		theApp.MainDlg->putListLog("Uart Port Open Ok!");
	}

	if (pCamera->Setup() <= 0)
	{
		//cout << "DES board setup error" << endl;
		theApp.MainDlg->putListLog("DES board setup error");
		return false;
	}

	
	return true;
}
bool CRvc_Uart::Rvc_Uartset()
{
	HMODULE hLibray = ::LoadLibrary("AutomotivePACStA.dll");

	if (hLibray == nullptr)
	{
		//cout << "Cannot load library" << endl;
		theApp.MainDlg->putListLog("Cannot load library");
		return false;
	}

	//pfnGetAutomotiveCamera fnGetInterface = (pfnGetAutomotiveCamera)GetProcAddress(hLibray, "GetAutomotiveCamera");
	fnGetInterface = (pfnGetAutomotiveCamera)GetProcAddress(hLibray, "GetAutomotiveCamera");

	if (fnGetInterface == nullptr)
	{
		//cout << "Cannot load automotive interface " << endl;
		theApp.MainDlg->putListLog("Cannot load automotive interface");
		return false;
	}
	//IAutomotiveCamera* pCamera = (*fnGetInterface)();
	pCamera = (*fnGetInterface)();
	if (pCamera == nullptr)
	{
		//cout << "Cannot load automotive camera object." << endl;
		theApp.MainDlg->putListLog("Cannot load automotive camera object.");
		return false;
	}

	pCamera->SetComm(&CSerialComm::GetInstance());
	//pCamera->SetLogConfig(PrintLog, 0, 0);
	return true;
}
void CRvc_Uart::PrintLog(void* lpUserData, int nParaIndex, const char* lpszLog)
{
	// TODO:: implement to print log
	cout << lpszLog << endl;
}
int CRvc_Uart::WriteRegister(IAutomotiveCamera* pCamera, unsigned char category, unsigned short addr, unsigned char dataLength, unsigned short data)
{
	unsigned char writeLength = 0x03;

	unsigned char writeAddr[4];
	writeAddr[0] = 0xf0;
	writeAddr[1] = category;
	writeAddr[2] = (addr >> 8) & 0xff;
	writeAddr[3] = addr & 0xff;

	unsigned char writeData[3];
	writeData[0] = dataLength;
	writeData[1] = (data >> 8) & 0xff;
	writeData[2] = data & 0xff;

	int ret = pCamera->GetUDS()->WriteMemoryByAddress(0x14, writeAddr, &writeLength, writeData);
	if (ret <= 0)
	{
		//cout << "WriteRegister failed" << endl;
	}

	return ret;
}
int CRvc_Uart::DisableSend(unsigned char A[4], unsigned char B, unsigned char C[3])
{
	if (pCamera->GetUDS()->WriteMemoryByAddress(0x14, A, &B, C) <= 0)
	{
		//cout << "sharpness mainPM set to 0x00 failed" << endl;
		return 0;
	}
	return 1;
}
int CRvc_Uart::DisableSharpness(IAutomotiveCamera* pCamera)
{
	// 
	//unsigned char sharpnessAddr[4] = { 0xf0, 0x00, 0x81, 0x32 }; // 4 bytes fix
	//unsigned char writeLength = 0x03;
	//unsigned char writeData[3] = { 0x02, 0x00, 0x00 };//default , on , off
	//if (pCamera->GetUDS()->WriteMemoryByAddress(0x14, sharpnessAddr, &writeLength, writeData) <= 0)
	//{
	//	//cout << "sharpness value set to 0x00 failed" << endl;
	//	return 0;
	//}

	//unsigned char mainPMAddr[4] = { 0xf0, 0x00, 0x83, 0x69 };
	//if (pCamera->GetUDS()->WriteMemoryByAddress(0x14, mainPMAddr, &writeLength, writeData) <= 0)
	//{
	//	//cout << "sharpness mainPM set to 0x00 failed" << endl;
	//	return 0;
	//}
	unsigned char writeLength = 0x03;
	//
	unsigned char writeDataAE[3] = { 0x02, 0x00, 0x00 };//default , on , off
	unsigned char mainPMAddrAE[4] = { 0xf0, 0x00, 0x80, 0x05 };//AE
	DisableSend(mainPMAddrAE, writeLength, writeDataAE);
	unsigned char writeDataHDR[3] = { 0x02, 0x00, 0x00 };
	unsigned char mainPMAddrHDR[4] = { 0xf0, 0x00, 0x08, 0x02 };
	DisableSend(mainPMAddrHDR, writeLength, writeDataHDR);
	unsigned char writeDataGAMMA[3] = { 0x02, 0x00, 0x00 };
	unsigned char mainPMAddrGAMMA[4] = { 0xf0, 0x00, 0x12, 0x00 };
	DisableSend(mainPMAddrGAMMA, writeLength, writeDataGAMMA);
	unsigned char writeDataEDGE[3] = { 0x02, 0x00, 0x00 };
	unsigned char mainPMAddrEDGE[4] = { 0xf0, 0x00, 0x83, 0x07 };
	DisableSend(mainPMAddrEDGE, writeLength, writeDataEDGE);
	unsigned char writeDataAWB[3] = { 0x02, 0x00, 0x06 };
	unsigned char mainPMAddrAWB[4] = { 0xf0, 0x00, 0x04, 0x50 };
	DisableSend(mainPMAddrAWB, writeLength, writeDataAWB);
	unsigned char writeDataAWB2[3] = { 0x02, 0x00, 0x19 };
	unsigned char mainPMAddrAWB2[4] = { 0xf0, 0x00, 0x80, 0x62 };
	DisableSend(mainPMAddrAWB2, writeLength, writeDataAWB2);

	unsigned char writeDataAES[3] = { 0x02, 0x00, 0xEE };
	unsigned char mainPMAddrAES[4] = { 0xf0, 0x01, 0x30, 0x12 };
	DisableSend(mainPMAddrAES, writeLength, writeDataAES);

	//isp = f000 , sensor = f001
	

	//cout << "Disable sharpness success" << endl;

	return 1;
}

