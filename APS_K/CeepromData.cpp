#include "stdafx.h"
#include "CeepromData.h"


CeepromData::CeepromData()
{

}

CeepromData::~CeepromData()
{
}

//STRING 은 ASCII 로 변경
//HEX 는 는 값 그대로 (12 = 0X12)
//FLOAT 는 HEX로 변경해서 입력
//-12.22 = 0xc143851f
//CString data = _T("0.12345");//0x3dfcd35b   //48464950515253
//
void CeepromData::eeprom_Data_Sum(CString WriteData, int WritebyteLength, int type, byte* rtnData, bool autoRun)
{
	unsigned char pData[MAX_PATH];
	int errorCode = 0;
	int i = 0;
	int j = 0;
	int leng = WriteData.GetLength();
	int value = 0;
	float fNum = 0.0;
	double testnum = 0.0;
	CString strTemp;
	int startNum = 0;
	unsigned char szTemp[MAX_PATH];
	memset(pData, 0, sizeof(pData));
	memset(rtnData, 0, WritebyteLength);

	if (type == FLOAT_MODE)
	{
		fNum = (float)_ttof(WriteData);//fNum = (_ttof(WriteData));//atof  //wtof
		memcpy(szTemp, &fNum, sizeof(float));//들어갈때 반대로 값이 들어간다 
	}
	else if (type == ASCII_MODE)
	{
		startNum = (WritebyteLength - 1 - leng);
		strTemp = CovertToHex(WriteData, type);
	}
	strTemp.Replace(" ", "");
	//
	switch (type)
	{
	case ASCII_MODE:

		leng = WritebyteLength;
		break;
	case FLOAT_MODE:
		leng = 4;
		for (i = 0; i < leng; i++)
		{
			strTemp.AppendFormat("%02X", szTemp[3 - i]);// szTemp[3 - x]);
		}
		break;
	case DEC_MODE:
		//
		leng = 1;
		//
		//dec -->hex로 바꾸는 코드
		value = _ttoi(WriteData);
		strTemp.Format("%x ", value);
		//strTemp.Format("%s", WriteData);//그대로 쓰는 코드
		
		break;
	case HEX_MODE:
		leng = WritebyteLength;
		strTemp.Format("%s", WriteData);//그대로 쓰는 코드
		break;
	}
	for (int i = 0; i < leng; i++)
	{
		if (type == ASCII_MODE)
		{
			if (i == (leng - 1))
			{
				pData[i] = (unsigned char)_tcstol("00", NULL, 16);
			}
			else if (i >= (startNum))
			{
				//value = (int)(WriteData[i - startNum]);
				pData[i] = (unsigned char)_tcstol(strTemp.Mid((i - startNum) * 2, 2), NULL, 16);
			}
			else
			{
				pData[i] = (unsigned char)_tcstol("00", NULL, 16);
			}
		}
		else
		{
			pData[i] = (unsigned char)_tcstol(strTemp.Mid(i * 2, 2), NULL, 16);//hex코드로 입력했을대기존코드

		}
		rtnData[i] = pData[i];
	}
}

CString CeepromData::EEPROM_Read(CString ReadAddress, int ReadbyteLength, int type , int autoRun)
{
	CString rtnStr = _T("");
	if (!MIU.m_pBoard->IsConnected())
	{
		theApp.MainDlg->putListLog("[CCD] Grabber Board 해제 상태");
		rtnStr = "false";
		return rtnStr;
	}
	unsigned char pData[MAX_PATH];
	int errorCode = 0;
	int i = 0;
	unsigned int nAddress;
	sscanf_s(ReadAddress.GetBuffer(0), "%x", &nAddress);
	memset(pData, 0x00, sizeof(pData));
	BYTE	m_Str_DataLength = (byte)ReadbyteLength;
	Sleep(1);
	errorCode = MIU.m_pBoard->ReadI2CBurst((unsigned short)0x50, (unsigned short)nAddress, 2, pData, (unsigned short)m_Str_DataLength);
	Sleep(10);
	CString tempData = _T("");

	
	if (errorCode)
	{
		tempData.Format("Error : %d", errorCode);
		theApp.MainDlg->putListLog(tempData);
		tempData.AppendFormat(" %s", GetErrorStr(errorCode));
		theApp.MainDlg->putListLog(tempData);
		tempData.Format("FLASE");
		return tempData;
	}
	else
	{
		rtnStr.Empty();
		for (int i = 0; i < (int)m_Str_DataLength; i++)
		{
			tempData.AppendFormat("%02X", (char*)pData[i]);
		}
		rtnStr = CovertToChar(tempData, type);
	}
	if (autoRun == false)
	{
		theApp.MainDlg->putListLog(rtnStr);
	}
	
	return rtnStr;
}
byte CeepromData::EEPROM_Write(CString WriteAddress, CString WriteData , int WritebyteLength , int type, byte* rtnData , bool autoRun)
{
	unsigned char pData[MAX_PATH];
	int errorCode = 0;
	int i = 0;
	int j = 0;
	int leng = WriteData.GetLength();
	int value = 0;
	float fNum = 0.0;
	CString strTemp;

	unsigned char szTemp[MAX_PATH];
	memset(pData, 0, sizeof(pData));
	memset(szTemp, 0x00, sizeof(szTemp));
	memset(rtnData, 0x00, 32);
	if (!MIU.m_pBoard->IsConnected())
	{
		theApp.MainDlg->putListLog("[CCD] Grabber Board 해제 상태");
		return (byte)errorCode;
	}
	if (type == DEC_MODE)
	{
		strTemp = WriteData;
	}
	else if (type == FLOAT_MODE)
	{
		fNum = (_ttof(WriteData));
		memcpy(szTemp, &fNum, sizeof(float));//들어갈때 반대로 값이 들어간다
	}
	else if (type == ASCII_MODE)
	{
		strTemp = CovertToHex(WriteData, type);
	}
	strTemp.Replace(" ", "");
	//
	switch (type)
	{
	case ASCII_MODE:
		for (i = 0; i < leng; i++)
		{
			value = (int)(WriteData[i]);
			strTemp.AppendFormat("%x ", value);
		}
		
		break;
	case FLOAT_MODE:
		leng = 4;
		for (i = 0; i < leng; i++)
		{
			strTemp.AppendFormat("%02X", szTemp[3 - i]);// szTemp[3 - x]);
		}
		break;
	case DEC_MODE:
		//
		leng = 1;
		//dec -->hex로 바꾸는 코드
		//value = _ttoi(WriteData);
		//strTemp.Format("%x ", value);
		//
		
		strTemp.Format("%s", WriteData);//그대로 쓰는 코드
		break;
	}
	for (int i = 0; i < leng; i++)
	{
		pData[i] = (unsigned char)_tcstol(strTemp.Mid(i * 2, 2), NULL, 16);//hex코드로 입력했을대기존코드
	}
	memcpy(rtnData, pData, leng);
	return (byte)errorCode;
	/*unsigned int nSlaveAddress;
	unsigned int nAddress;
	BYTE	m_Str_DataLength = (byte)WritebyteLength;
	sscanf_s(WriteAddress.GetBuffer(0), "%x", &nAddress);
	Sleep(10);
	errorCode = theApp.MainDlg->m_pBoard->WriteI2CBurst((unsigned short)0x50, (unsigned short)nAddress, 2, pData, (unsigned short)m_Str_DataLength);
	Sleep(1);
	if (autoRun == true)
	{
		return (byte)errorCode;
	}
	
	CString logStr = _T("");
	if (errorCode)
	{
		logStr.Format("Error : %d", errorCode);
		theApp.MainDlg->putListLog(logStr);
		logStr.AppendFormat(" %s", GetErrorStr(errorCode));
		theApp.MainDlg->putListLog(logStr);
	}
	else
	{
		theApp.MainDlg->putListLog("wright ok!");
	}*/
	return (byte)errorCode;
}

CString CeepromData::CovertToHex(CString data, int type)
{
	CString rtnValue;
	CString temporary;
	unsigned char szTemp[1024];
	int value = 0;
	float fNum = 0.0;
	temporary.Empty();
	rtnValue.Empty();
	data.Replace(" ", "");
	memset(szTemp, 0x00, 1024);
	int len = 0;

	if (type == FLOAT_MODE)
	{
		fNum = (_ttof(data));
		memcpy(szTemp, &fNum, sizeof(float));
		len = 4;
	}
	else if (type == ASCII_MODE)
	{
		len = data.GetLength();
	}
	else if (type == DEC_MODE)
	{
		len = 1;
	}
	else if (type == HEX_MODE)
	{
		len = 1;
	}
	for (int x = 0; x < len; x++)
	{
		if (type == FLOAT_MODE)
		{
			temporary.Format("%02X", szTemp[3 - x]);// szTemp[3 - x]);
													//Hex 로 변경
		}
		else if (type == ASCII_MODE)
		{
			value = (int)(data[x]);
			temporary.Format("%X", value);//temporary.Format("%02X", value);기존
										  //temporary.Format("%d", value);//
										  //ASCII : 입력된 String 을 ASCII Code 로 변경
		}
		else if (type == DEC_MODE)
		{
			value = _ttoi(data);
			temporary.Format("%X", value);
		}
		else if (type == HEX_MODE)
		{
			value = _ttoi(data);
			temporary.Format("%X", value);
		}
		rtnValue += temporary;
	}
	return rtnValue;
}
CString CeepromData::CovertToChar(CString data, int mode)
{
	CString rtnValue;
	CString temporary;
	temporary.Empty();
	rtnValue.Empty();
	data.Replace(" ", "");
	int len = (int)data.GetLength();
	byte value;
	UINT32 AAA;
	float fNum = 0.0;
	if (mode == ASCII_MODE)
	{
		for (int x = 0; x < len; x++)//for (int x = 0; x < len; x += 2)
		{
			value = (byte)_tcstol(data.Mid(x * 2, 2), NULL, 16);
			temporary.Format("%c", value);
			rtnValue += temporary;
		}
	}
	else if (mode == FLOAT_MODE)
	{
		sscanf_s(data.GetBuffer(0), "%X", &AAA);
		fNum = *((float*)&AAA);
		rtnValue.Format("%f", fNum);
	}
	else if (mode == DEC_MODE)
	{
		value = (byte)_tcstol(data.Mid(0, 2), NULL, 16);
		temporary.Format("%X", value);
		rtnValue += temporary;
	}
	else if (mode == HEX_MODE)
	{
		value = (byte)_tcstol(data.Mid(0, 2), NULL, 16);
		temporary.Format("%d", value);
		rtnValue += temporary;
	}

	return rtnValue;
}


void CeepromData::ReadInit()
{
	//DB LOAD
	//
	BARCODE_ID = _T("EMPTY");
	UPDDATE_BY = _T("EMPTY");
	UPDATE_DATE = _T("EMPTY");
	UPDATE_DATE_DETAIL[0] = _T("0"), UPDATE_DATE_DETAIL[1] = _T("0"), UPDATE_DATE_DETAIL[2] = _T("0"), UPDATE_DATE_DETAIL[3] = _T("0"), UPDATE_DATE_DETAIL[4] = _T("0"), UPDATE_DATE_DETAIL[5] = _T("0");
	MAP_VER = _T("EMPTY");
	SMT_FLAG = _T("EMPTY");
	CAM_LOCATION = _T("EMPTY");
	
	MANUFACTURER_NAME = _T("EMPTY");
	MANUFACTURER_PN = _T("EMPTY");
	PLACE_OF_MANUFACTURE = _T("EMPTY");
	MANUFACTURE_ASSEMBLY_LINE = _T("EMPTY");
	LENS_NAME = _T("EMPTY");
	SENSOR_NAME = _T("EMPTY");
	SERIALIZER_NAME = _T("EMPTY");

	CFA = _T("EMPTY");
	LENGTH_FOCUS = _T("EMPTY");
	IMGR_INPUT_CLK_FREQ = _T("EMPTY");
	DISTORTION_MODEL = _T("EMPTY");
	//
	//AA
	OC_X = _T("EMPTY"), OC_Y = _T("EMPTY");
	RC2800K = _T("EMPTY"), BC2800K = _T("EMPTY"), CRCB2800K = _T("EMPTY");
	RC6500K = _T("EMPTY"), BC6500K = _T("EMPTY"), CRCB6500K = _T("EMPTY");
	RI_RED[10][10], RICLEAR_R[10][10], RICLEAR_B[10][10], RI_BLUE[10][10];
	MTF_0F = _T("EMPTY");
	MTF_4F_A = _T("EMPTY"), MTF_4F_B = _T("EMPTY"), MTF_4F_C = _T("EMPTY"), MTF_4F_D = _T("EMPTY");
	MTF_8F_A = _T("EMPTY"), MTF_8F_B = _T("EMPTY"), MTF_8F_C = _T("EMPTY"), MTF_8F_D = _T("EMPTY");
	//
	//CAL
	DISTORTION_CX = _T("EMPTY"), DISTORTION_CY = _T("EMPTY");
	DIST_K1 = _T("EMPTY"), DIST_K2 = _T("EMPTY"), DIST_K3 = _T("EMPTY"), DIST_K4 = _T("EMPTY"), DIST_K5 = _T("EMPTY"), DIST_K6 = _T("EMPTY");
	DIST_P1 = _T("EMPTY"), DIST_P2 = _T("EMPTY");
	AVR_D= _T("EMPTY"), MAX_D = _T("EMPTY");
	DIS_FOCAL_LENGTH = _T("EMPTY");
	CAM_ROLL = _T("EMPTY"), CAM_PITCH = _T("EMPTY"), CAM_YAW = _T("EMPTY");
	//
	//

}



void CeepromData::func_EEPROM_ReadData_LodSave()		//cal대대
{

	
}

CString CeepromData::GetErrorStr(int errorCode)
{
	CString retStr;
	switch (errorCode)
	{
	case ERR_BOARD_GET_LIST:
		retStr = "ERR_BOARD_GET_LIST";
		break;
	case ERR_BOARD_NO_DEVICE:
		retStr = "ERR_BOARD_NO_DEVICE";
		break;
	case ERR_BOARD_OPEN:
		retStr = "ERR_BOARD_OPEN";
		break;
	case ERR_BOARD_INIT:
		retStr = "ERR_BOARD_INIT";
		break;
	case ERR_BOARD_SET_POWER_5_12:
		retStr = "ERR_BOARD_SET_POWER_5_12";
		break;
	case ERR_BOARD_GRAB_START:
		retStr = "ERR_BOARD_GRAB_START";
		break;
	case ERR_BOARD_I2C_WRITE:
		retStr = "ERR_BOARD_I2C_WRITE";
		break;
	case ERR_BOARD_I2C_READ:
		retStr = "ERR_BOARD_I2C_READ";
		break;
	case ERR_BOARD_BOOT_CAMERA:
		retStr = "ERR_BOARD_BOOT_CAMERA";
		break;
	case ERR_BOARD_CLOSE:
		retStr = "ERR_BOARD_CLOSE";
		break;
	case ERR_BOARD_LOAD_MODEL:
		retStr = "ERR_BOARD_LOAD_MODEL";
		break;
	default:
		break;
	}
	return retStr;
}