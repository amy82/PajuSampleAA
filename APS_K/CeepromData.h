#pragma once
class CeepromData
{
public:
	CeepromData();
	~CeepromData();

public:
	CString EEPROM_Read(CString ReadAddress, int ReadbyteLength, int type, int autoRun);
	byte EEPROM_Write(CString WriteAddress, CString Data, int byteLength, int type , byte* rtnData, bool autoRun);
	void eeprom_Data_Sum(CString WriteData, int WritebyteLength, int type, byte* rtnData, bool autoRun);
	//
	void ReadInit();
	CString GetErrorStr(int errorCode);
	void func_EEPROM_ReadData_LodSave();
	CString CovertToHex(CString data, int type);
	CString CovertToChar(CString data, int type);
public:
	//--------------------------------------------------------------------------------------------------------------------------------
	//
	//
	//DB LOAD
	//
	CString BARCODE_ID;
	CString UPDDATE_BY;
	CString UPDATE_DATE;
	CString UPDATE_DATE_DETAIL[6];
	CString MAP_VER;
	CString SMT_FLAG;
	CString CAM_LOCATION;
	//
	CString MANUFACTURER_NAME;
	CString MANUFACTURER_PN;
	CString PLACE_OF_MANUFACTURE;
	CString MANUFACTURE_ASSEMBLY_LINE;
	CString LENS_NAME;
	CString SENSOR_NAME;
	CString SERIALIZER_NAME;
	
	CString CFA;
	CString LENGTH_FOCUS;
	CString IMGR_INPUT_CLK_FREQ;
	CString DISTORTION_MODEL;
	//
	//AA
	CString OC_X, OC_Y;
	CString RC2800K, BC2800K, CRCB2800K;
	CString RC6500K, BC6500K, CRCB6500K;
	CString RI_RED[10][10],  RICLEAR_R[10][10], RICLEAR_B[10][10] , RI_BLUE[10][10];
	CString MTF_0F;
	CString MTF_4F_A, MTF_4F_B, MTF_4F_C, MTF_4F_D;
	CString MTF_8F_A, MTF_8F_B, MTF_8F_C, MTF_8F_D;
	//
	//CAL
	CString DISTORTION_CX, DISTORTION_CY;
	CString DIST_K1, DIST_K2, DIST_K3, DIST_K4, DIST_K5, DIST_K6;
	CString DIST_P1, DIST_P2;
	CString AVR_D, MAX_D;
	CString DIS_FOCAL_LENGTH;
	CString CAM_ROLL, CAM_PITCH, CAM_YAW;
	//
	//

	
	//
	////--------------------------------------------------------------------------------------------------------------------------------

};


class CDBLoadData
{
public:

	CString cLotId;
	CString Camera_Location;
	CString CreateDateTime, OC_X, OC_Y, DC_X, DC_Y, K1, K2, K3, K4, K5, K6, P1, P2;
	CString AverD, MaxD, FOCAL_LENGTH;
	CString RC2800, RC6500, BC2800, BC6500, CR2800, CR6500;
	CString MTF_C_0, MTF_C_4A, MTF_C_4B, MTF_C_4C, MTF_C_4D, MTF_C_8A, MTF_C_8B, MTF_C_8C, MTF_C_8D;
	CString DPC_X, DPC_Y;
	CString ROLL, PITCH, YAW;

	CString DB_MTF_0_1, DB_MTF_0_2, DB_MTF_0_3, DB_MTF_0_4, DB_MTF_4_1, DB_MTF_4_2, DB_MTF_4_3, DB_MTF_4_4, DB_MTF_4_5, DB_MTF_4_6, DB_MTF_4_7, DB_MTF_4_8;
	CString DB_MTF_8_1, DB_MTF_8_2, DB_MTF_8_3, DB_MTF_8_4, DB_MTF_8_5, DB_MTF_8_6, DB_MTF_8_7, DB_MTF_8_8;

	CString strRIRED[10][10], strRIBLUE[10][10], strRICR[10][10], strRICB[10][10];
	CDBLoadData()
	{
		
	}
};

