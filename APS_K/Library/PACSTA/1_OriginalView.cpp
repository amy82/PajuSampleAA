#include <iostream>
#include <Windows.h>
#include "Automotive.h"
#include "SerialComm.h"

using namespace std;

void PrintLog(void* lpUserData, int nParaIndex, const char* lpszLog)
{
	// TODO:: implement to print log
	cout << lpszLog << endl;
}

int DisableSharpness(IAutomotiveCamera* pCamera)
{
	// 
	unsigned char sharpnessAddr[4] = {0xf0, 0x00, 0x81, 0x32}; // 4 bytes fix
	unsigned char writeLength = 0x03;
	unsigned char writeData[3] = {0x01, 0x00, 0x00};
	if( pCamera->GetUDS()->WriteMemoryByAddress(0x14, sharpnessAddr, &writeLength, writeData) <= 0 )
	{
		cout << "sharpness value set to 0x00 failed" << endl;
		return 0;
	}

	unsigned char mainPMAddr[4] = { 0xf0, 0x00, 0x83, 0x69 };
	if( pCamera->GetUDS()->WriteMemoryByAddress(0x14, mainPMAddr, &writeLength, writeData) <= 0 )
	{
		cout << "sharpness mainPM set to 0x00 failed" << endl;
		return 0;
	}

	cout << "Disable sharpness success" << endl;

	return 1;
}

int WriteRegister(IAutomotiveCamera* pCamera, unsigned char category, unsigned short addr, unsigned char dataLength, unsigned short data)
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
	if( ret <= 0 )
	{
		cout << "WriteRegister failed" << endl;
	}

	return ret;	  
}


int main()
{
	// Load "AutomotivePACSta" library
	HMODULE hLibray = ::LoadLibrary("AutomotivePACStA.dll");
	if( hLibray == nullptr) 
	{
		cout << "Cannot load library" << endl;
		return 0;
	}

	pfnGetAutomotiveCamera fnGetInterface = (pfnGetAutomotiveCamera)GetProcAddress(hLibray, "GetAutomotiveCamera");
	if( fnGetInterface == nullptr)
	{
		cout << "Cannot load automotive interface " << endl;
		return 0;
	}

	IAutomotiveCamera* pCamera = (*fnGetInterface)();
	if( pCamera == nullptr)
	{
		cout << "Cannot load automotive camera object." << endl;
		return 0;
	}

	pCamera->SetComm(&CSerialComm::GetInstance());
	pCamera->SetLogConfig(PrintLog, 0, 0);

	// Serial communication create & open 
	int ret = CSerialComm::GetInstance().Open( COM_PORT, 416000, 8, ONESTOPBIT, EVENPARITY );
	if( ret <= 0 )
	{
		// Open Failed 
		return 0;
	}

	if( pCamera->Setup() <= 0 ) 
	{
		cout << "DES board setup error" << endl;
		return 0;
	}

	// true: trun on, false: turn off 
	int reserved = 0;
	if( pCamera->OriginalView(true, &reserved) <= 0 )
	{
		cout << "cannot show original view" << endl;
		return 0; 
	}

	if( DisableSharpness(pCamera) <= 0  )
	{
		cout << "cannot disable sharpness" << endl;
		return 0;
	}

	while(1)
	{
		// Todo: Keep the original view sending TesterPresent
		if( pCamera->GetUDS()->TesterPresent(0) > 0 )
		{
			Sleep(3000); // 3000 ms 
		}
		else
		{
			// TesterPresent failed
			return 0;
		}

	}

	return 0;
}

