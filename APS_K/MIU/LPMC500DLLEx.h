/******************************************************************************
*	Project : MIU Project (MIPI USB30)
*
*
*	
*	File Name : LPMC500DLLEx.h 
******************************************************************************/
#ifndef __V5U_DLLEX_H__
#define __V5U_DLLEX_H__


#ifdef _USRDLL
#define DLLFunction  __declspec(dllexport)
#else
#define DLLFunction  __declspec(dllimport)
#endif


#define _cplusplus

#ifdef _cplusplus
extern "C" {
#endif


/******************************************************************************
*   MIU ERROR CODE DEFINE
*******************************************************************************/
#define MIU_OK						0x00000000
#define MIU_CREATE_ERR				0x00000001	
#define MIU_NODEVICE				0x00000002
#define MIU_TIMEOUT					0x00000003
#define MIU_REGWRITEERROR           0x00000004
#define MIU_BOARDNUMBERDUPLICATION  0x00000005
#define MIU_ALREADY_OPENED			0x00000006
#define MIU_ALREADY_CLOSED			0x00000007
#define MIU_NOT_SUPPORT_MODEL		0x00000008
#define MIU_NOT_DIRECT_MODE			0x00000009

#define MIU_ENDPOINTOPENFAIL		0x00000052

#define MIU_NEW_FRAME				0x0100
#define MIU_RECEIVING				0x0101
#define MIU_NO_IMAGE				0x0102

#define AF_SUCCESS					0x0300
#define AF_TRY_AGAIN				0x0301
#define AF_LIMIT_FAIL				0x0302
#define AF_PEAK						0x0303


#define MIU_VOLTAGECTL_ERROR		0x00001001
#define MIU_PINCONTROL_ERROR		0x00001002
#define MIU_ADCSET_ERROR			0x00001003
#define	MIU_ADCREAD_ERROR			0x00001004
#define MIU_CALIBRATIONINIT_ERROR   0x00001005

/******************************************************************************
*   MIU EVENT CODE DEFINE
*******************************************************************************/
#define MIU_EVENT_TIMEOUT			0x0000F001
#define	MIU_EVENT_ATTACHED			0x0000F002
#define MIU_EVNET_DETACHED			0x0000F003


#define OS_TESTPIN_COUNT			55

// SensorUSBMode
#define	PARALLEL 1
#define	MIPI 2
#define	SENSOR1_USB2 3

/******************************************************************************
*   MIU Register TYPE
*******************************************************************************/
typedef enum {
    REG_MIU = 0,
    REG_IIC1,
	REG_LEDCONTROL,
	REG_OS
} MIU_REG_TYPE;





/******************************************************************************
* Structure of MIU InitialValue
*******************************************************************************/
typedef struct _MIUINITIALVALUE
{
	unsigned char	SensorMode;
	unsigned short	nWidth;
	unsigned short	nHeight;
	unsigned char	MCLKOnOff;
	unsigned char   MCLKSelection;
	float			MCLK;
	unsigned char	PCLKInversion;
	unsigned char	IICDeviceID;	
	unsigned char	IICMode;
	unsigned char	IICSpeed;
	unsigned char	IICReadRestart;
	unsigned char	IICReadRestartInterval;
	unsigned char	IICSCKPinCheck;
	unsigned char	IICAddressLength;
	unsigned char	IICDataLength;
	unsigned char	MIPILaneEnable;
	unsigned char	MIPIDataType;
	float			MIUIOVoltage;
	unsigned char	FirstPowerChannel;
	float			FirstPowerVoltage;
	unsigned char	SecondPowerChannel;
	float			SecondPowerVoltage;
	unsigned char	ThirdPowerChannel;
	float			ThirdPowerVoltage;
	unsigned char	FourthPowerChannel;
	float			FourthPowerVoltage;
	unsigned char	FifthPowerChannel;
	float			FifthPowerVoltage;
	unsigned char	Power5VoltOnOff;
	unsigned char	Power12VoltOnOff;
	unsigned char	InitialSkipCount;
	unsigned short	PreviewSkipCount;
	unsigned char	ParallelSamplingMode;
	unsigned char	ParallelBitsPerPixel;
	unsigned char	ParallelPixelComponent;
	unsigned char	ParallelBitShift;
	unsigned char   MIPI8bitMode;
}MIU_INITIALValue;



typedef struct _AF_ROI
{
	int nXStart;
	int nYStart;
}AF_ROI;


//20140903 추가
typedef struct _AFCONTROL
{
	unsigned char	nActuatorI2CID;
	unsigned char	nActuatorI2CMode; // (0 : 8bit address, 8bit data, 1 : 8bit address, 16bit data, 2 : 16bit address, 8bit data, 3 : 16bit address, 16bit data)
	unsigned char	nSensorI2CID;
	unsigned char	nSensorI2CMode;   // (0 : 8bit address, 8bit data, 1 : 8bit address, 16bit data, 2 : 16bit address, 8bit data, 3 : 16bit address, 16bit data)
	unsigned short	nMaxValue;
	unsigned short	nMinValue;
	unsigned short	nStepValue;
	unsigned short	nActuatorType; // Default : 0

	int				nRoiWidth;
	int				nRoiHeight;
	BOOL			bRoiOn;
	AF_ROI			AFRoi;
}AFCONTROL;




/******************************************************************************
*   MIUGetDeviceList : MIU Get Device List 
*
*	@param pDeviceCount[out], Device count
*   @param pDeviceList[out], Device List
*
*   @return     Error Value
******************************************************************************/
DLLFunction int __cdecl MIUGetDeviceList(char* pDeviceCount, char* pDeviceList);


/******************************************************************************
*   MIUOpenDevice : MIU Open 
*
*	@param		      
*
*   @return     Error Value
******************************************************************************/
DLLFunction int __cdecl MIUOpenDevice(char iDeviceIndex);


/******************************************************************************
*   MIUCloseDevice : MIU Close 
*
*   @return     Error Value
******************************************************************************/
DLLFunction int __cdecl MIUCloseDevice(char iDeviceIndex);

/******************************************************************************
*   MIUCloseAll : MIU Close All
*
*   @return     Error Value
******************************************************************************/
DLLFunction int __cdecl MIUCloseAll();


/******************************************************************************
*   MIUInitialize : MIU Initialize 
*	
*	@param		iDeviceIndex, [in] DeviceIndex
*
*   @return     Error Value
******************************************************************************/
DLLFunction int __cdecl MIUInitialize(char iDeviceIndex, MIU_INITIALValue InitialValue );


/******************************************************************************
*   MIUWriteRegister : MIU Register Write 
*
*	@param		iDeviceIndex, [in] DeviceIndex
*   @param      iRegisterType, [in] 어떤 Type의 Register를 읽을지 나타낸다. 
*               MIU_REG_TYPE 참고 
*   @param      nAddress, [in] 쓰고자 하는 Register의 address  
*   @param      nData, [in] Data Value
*
*   @return     Error Value
******************************************************************************/
DLLFunction int __cdecl MIUWriteRegister(char iDeviceIndex, MIU_REG_TYPE iRegisterType, unsigned short nAddress, unsigned short nData);


/******************************************************************************
*   MIUReadRegister : MIU Register Read 
*
*	@param		iDeviceIndex, [in] DeviceIndex
*   @param      iRegisterType, [in] 어떤 Type의 Register를 읽을지 나타낸다. 
*               MIU_REG_TYPE 참고 
*   @param      nAddress, [in] 쓰고자 하는 Register의 address  
*   @param      pData, [in, Out] Read Register Value
*
*   @return     Error Value
******************************************************************************/
DLLFunction int __cdecl MIUReadRegister(char iDeviceIndex, MIU_REG_TYPE iRegisterType, unsigned short nAddress, unsigned short* pData);





// KBS_0805
/******************************************************************************
*   MIUI2CBurstWrite : MIU Write Direct I2C 
*
*   @param      iDeviceIndex,      [in] Device Index
*   @param      nSlaveAddress,     [in] Write 할 target slave address 
*   @param      nAddress,          [in] target 의 address  
*   @param      nAddressByteCount, [in] target 의 address 로 할당된 byte count
*   @param      pData,             [Out]Write 할 데이터의 포인터
*   @param      pData,             [in] Write 할 데이터의 byte count
*   @return     Error Value
******************************************************************************/
DLLFunction int __cdecl MIUI2CBurstWrite(char iDeviceIndex, unsigned short nSlaveAddress, unsigned short nAddress, unsigned char nAddressByteCount, unsigned char* pData, unsigned short WriteByteCount);




// KBS_0805
/******************************************************************************
*   MIUI2CBurstRead : MIU Read Direct I2C 
*
*   @param      iDeviceIndex,      [in] Device Index
*   @param      nSlaveAddress,     [in] read 할 target slave address 
*   @param      nAddress,          [in] target 의 address  
*   @param      nAddressByteCount, [in] target 의 address 로 할당된 byte count
*   @param      pData,             [Out]읽어들일 데이터의 포인터
*   @param      pData,             [in] 읽어들일 데이터의 byte count
*   @return     Error Value
******************************************************************************/
DLLFunction int __cdecl MIUI2CBurstRead(char iDeviceIndex, unsigned short nSlaveAddress, unsigned short nAddress, unsigned char nAddressByteCount, unsigned char* pData, unsigned short ReadByteCount);





/******************************************************************************
*   MIUInitializeImageValue : MIU 에 Capture하게될 Image의 특성을 설정 한다.
*                             Image Receive Start 를 하기 전에 설정 한다.
*
*	@param		iDeviceIndex, [in] DeviceIndex
*   @param      PixelFormat, [in] 전송 Image의 PixelFormat 을 Write
*   @param      nWidth, [in] Image의 Width
*   @param      nHeight, [in] Image의 Height
*   @param      nMaxWidth, [in] Image의 Width
*   @param      nMaxHeight, [in] Image의 Height
*   @param      nBufferCount, [in] ImageBuffer Count
*
*   @return     Error Value
******************************************************************************/
DLLFunction int __cdecl MIUInitializeImageValue(char iDeviceIndex, unsigned int PixelFormat, unsigned int nWidth, 
												  unsigned int nHeight, unsigned int nMaxWidth, 
												  unsigned int nMaxHeight,unsigned char nBufferCount);

/******************************************************************************
*   MIUStart : MIU Capture Start
*
*	@param		iDeviceIndex, [in] DeviceIndex
*
*   @return     Error Value
******************************************************************************/
DLLFunction int __cdecl MIUStart(char iDeviceIndex);


/******************************************************************************
*   MIUStop : MIU Capture Stop
*
*	@param		iDeviceIndex, [in] DeviceIndex
*
*   @return     Error Value
******************************************************************************/
DLLFunction int __cdecl MIUStop(char iDeviceIndex);


/******************************************************************************
*   MIUPause : MIU Capture Pause for resolution change
*
*	@param		iDeviceIndex, [in] DeviceIndex
*
*   @return     Error Value
******************************************************************************/
DLLFunction int __cdecl MIUPause(char iDeviceIndex);


/******************************************************************************
*   MIUResume : MIU Capture Resume for resolution change
*
*	@param		iDeviceIndex, [in] DeviceIndex
*   @param      nWidth, [in] Width
*   @param      nHeight, [in] Height
*
*   @return     Error Value
******************************************************************************/
DLLFunction int __cdecl MIUResume(char iDeviceIndex, unsigned int nWidth, unsigned int nHeight);




/******************************************************************************
*   MIUResumeChageFormat : MIU Capture Resume for resolution change
*
*	@param		iDeviceIndex, [in] DeviceIndex
*   @param      PixelFormat, [in] Pixel Format
*
*   @return     Error Value
******************************************************************************/
DLLFunction int __cdecl MIUResumeChageFormat(char iDeviceIndex, unsigned int PixelFormat );



/******************************************************************************
*   MIUPause : MIU Capture Preview Pause
*
*	@param		iDeviceIndex, [in] DeviceIndex
*
*   @return     Error Value
******************************************************************************/
DLLFunction int __cdecl MIUPreviewPause(char iDeviceIndex);


/******************************************************************************
*   MIUResume : MIU Capture Preview Resume
*
*	@param		iDeviceIndex, [in] DeviceIndex
*
*   @return     Error Value
******************************************************************************/
DLLFunction int __cdecl MIUPreviewResume(char iDeviceIndex);




/******************************************************************************
*   MIUGetImageData : MIU Get Image Data
*
*	@param		iDeviceIndex, [in] DeviceIndex
*	@param      ppImagePoint, [in, Out] Display 할 Image Data의 Pointer를 가져올 Pointer
*   @param      pTimeStamp, [in, Out] TimeStamp 값을 가져갈 변수
*
*   @return     Receive Status
******************************************************************************/
DLLFunction int __cdecl MIUGetImageData(char iDeviceIndex, unsigned char** ppImagePoint, INT64* pTimeStamp);


/******************************************************************************
*   MIUGetDiagnostics : MIU Get Diagnostics
*
*	@param		iDeviceIndex, [in] DeviceIndex
*	@param      pImageCount [in, Out] 수신한 Image Count 값을 가져온다.
*   @param      pFramerate  [in, Out] Frame Rate (fps)을 가져온다.
*   @param      pBitrate    [in, Out] Bitrate를 가져온다. (Mbps 단위)
*
*   @return     Error Value
******************************************************************************/
DLLFunction int __cdecl MIUGetDiagnostics(char iDeviceIndex, unsigned int* pImageCount, float* pFramerate, float* pBitrate);



/******************************************************************************
*   MIUGetSensorFrameRate : MIU Get Sensor Frame Rate
*
*	@param		iDeviceIndex, [in] DeviceIndex
*   @param      pSensorFramerate  [in, Out] Sensor Frame Rate (fps)을 가져온다.
*
*   @return     Error Value
******************************************************************************/
DLLFunction int __cdecl MIUGetSensorFrameRate(char iDeviceIndex, float* pSensorFramerate);




/******************************************************************************
*   CurrentMeasureAllPowerOn : Current Measure AllPowerOn  (Power UP Sequence 설정)
*
*	@param		iDeviceIndex, [in] DeviceIndex
*   @param      n1stPowerPin, [in] 1st Power up pin
*   @param      n1stVoltage, [in] 1st Voltage 
*   @param      n2ndPowerPin, [in] 2nd Power up pin
*   @param      n2ndVoltage, [in] 2nd Voltage 
*   @param      n3rdPowerPin, [in] 3rd Power up pin
*   @param      n3rdVoltage, [in] 3rd Voltage 
*   @param      n4thPowerPin, [in] 4th Power up pin
*   @param      n4thVoltage, [in] 4th Voltage 
*   @param      n5thPowerPin, [in] 5th Power up pin
*   @param      n5thVoltage, [in] 5th Voltage 
*   
*   @return     Error Value 
******************************************************************************/
DLLFunction unsigned int  __cdecl CurrentMeasureAllPowerOn(char iDeviceIndex, unsigned char n1stPowerPin, float n1stVoltage,
													unsigned char n2ndPowerPin, float n2ndVoltage,
													unsigned char n3rdPowerPin, float n3rdVoltage,
													unsigned char n4thPowerPin, float n4thVoltage,
													unsigned char n5thPowerPin, float n5thVoltage);


/******************************************************************************
*   CurrentMeasureMode : Current Measure Mode Select  
*
*	@param		iDeviceIndex, [in] DeviceIndex
*   @param      Mode, [in] 측정 하고자 하는 Mode 0 : Dynamic Mode, 1 : Static Mode
*   
*   @return     Error Value 
******************************************************************************/
DLLFunction unsigned int __cdecl CurrentMeasureMode(char iDeviceIndex,unsigned char Mode);



/******************************************************************************
*   CurrentMeasureResult : Current Measure result  
*
*	@param		iDeviceIndex, [in] DeviceIndex
*   @param      nChannelNumber, [in] 측정 하고자 하는 channel number (0~4)
*   @param      CurrentMeasureResult, [out] Current measure result
*   @param      Mode, [in] Current measure Mode, 0 : Dynamic Mode, 1 : standby Mode
*   
*   @return     Error Value 
******************************************************************************/
DLLFunction unsigned int __cdecl CurrentMeasureResult(char iDeviceIndex, unsigned char nChannelNumber, double* CurrentMeasureResult, unsigned char Mode);



/******************************************************************************
*   CurrentMeasureDone : Current Measure all power off  
*
*	@param		iDeviceIndex, [in] DeviceIndex
*   
*   @return     Error Value 
******************************************************************************/
DLLFunction unsigned int __cdecl CurrentMeasurePowerOff(char iDeviceIndex);



/******************************************************************************
*   AutoCalibration : Auto Calibration 
*
*	@param		iDeviceIndex, [in] DeviceIndex
*   
*   @return     Error Value 
******************************************************************************/
DLLFunction void __cdecl AutoCalibration(char iDeviceIndex );


/******************************************************************************
*   InitializeCalibration : Initialize Calibration 
*
*	@param		iDeviceIndex, [in] DeviceIndex
*   
*   @return     Error Value 
******************************************************************************/
DLLFunction void __cdecl InitializeCalibration(char iDeviceIndex);



/******************************************************************************
*   FirmwareDownload : Firmware Download  
*
*	@param      iDeviceIndex, [in] DeviceIndex
*   @param      nSize, [in] Firmware image size
*   @param      pData, [in] Firmware image
*   
*   @return     Error Value 
******************************************************************************/
DLLFunction int __cdecl FirmwareDownload(char iDeviceIndex, unsigned int nSize, unsigned char* pData);


/******************************************************************************
*   MIUMainClockControl : Main clock control
*
*	@param      iDeviceIndex, [in] DeviceIndex
*   @param      bOnOff, [in] Clock On/Off setting 0 : Off, 1 : On
*   @param      ClockSelection, [in] 1 : Clock Generator, 2 : External Clock
*   
*   @return     Error Value 
******************************************************************************/
DLLFunction int __cdecl MIUMainClockControl(char iDeviceIndex, char bOnOff, char ClockSelection);


/******************************************************************************
*   MIUSetMCLK : MIU MCLK Setting 
*
*	@param      iDeviceIndex, [in] DeviceIndex
*   @param      fMCLK, [in] M Clock Value
*   
*   @return     Error Value 
******************************************************************************/
DLLFunction int __cdecl MIUSetMCLK(char iDeviceIndex, float fMCLK);



/******************************************************************************
*   MIUSetPowerChannel0 : Power channel 0 setting
*
*	@param		iDeviceIndex, [in] DeviceIndex
*   
*   @return     Error Value 
******************************************************************************/
DLLFunction int __cdecl MIUSetPowerChannel0(char iDeviceIndex, float fVoltage, char OnOff);


/******************************************************************************
*   MIUSetPowerChannel1 : Power channel 1 setting
*
*	@param		iDeviceIndex, [in] DeviceIndex
*   
*   @return     Error Value 
******************************************************************************/
DLLFunction int __cdecl MIUSetPowerChannel1(char iDeviceIndex, float fVoltage, char OnOff);


/******************************************************************************
*   MIUSetPowerChannel2 : Power channel 2 setting
*
*	@param		iDeviceIndex, [in] DeviceIndex
*   
*   @return     Error Value 
******************************************************************************/
DLLFunction int __cdecl MIUSetPowerChannel2(char iDeviceIndex, float fVoltage, char OnOff);

/******************************************************************************
*   MIUSetPowerChannel3 : Power channel 3 setting
*
*	@param		iDeviceIndex, [in] DeviceIndex
*   
*   @return     Error Value 
******************************************************************************/
DLLFunction int __cdecl MIUSetPowerChannel3(char iDeviceIndex, float fVoltage, char OnOff);


/******************************************************************************
*   MIUSetPowerChannel4 : Power channel 4 setting
*
*	@param		iDeviceIndex, [in] DeviceIndex
*   
*   @return     Error Value 
******************************************************************************/
DLLFunction int __cdecl MIUSetPowerChannel4(char iDeviceIndex, float fVoltage, char OnOff);


/******************************************************************************
*   MIUSetPowerChannel5V : 5Volt Power OnOff
*
*	@param		iDeviceIndex, [in] DeviceIndex
*   
*   @return     Error Value 
******************************************************************************/
DLLFunction int __cdecl MIUSetPowerChannel5V(char iDeviceIndex, char OnOff);


/******************************************************************************
*   MIUSetPowerChannel12V : 12Volt Power OnOff
*
*	@param		iDeviceIndex, [in] DeviceIndex
*   
*   @return     Error Value 
******************************************************************************/
DLLFunction int __cdecl MIUSetPowerChannel12V(char iDeviceIndex, char OnOff);


/******************************************************************************
*   MIUSetIOPowerChannel : Power channel IO setting
*
*	@param		iDeviceIndex, [in] DeviceIndex
*   
*   @return     Error Value 
******************************************************************************/
DLLFunction int __cdecl MIUSetIOPowerChannel(char iDeviceIndex, float fVoltage, char OnOff);


/******************************************************************************
*   MIUGetFirmwareInformation : Get Firmware Information
*
*	@param      iDeviceIndex, [in] DeviceIndex
*   @param      pInformation, [in, Out] pointer for getting firmware information  
*   
*   @return     Error Value 
******************************************************************************/
DLLFunction void __cdecl MIUGetFirmwareInformation(char iDeviceIndex, char* pInformation);




/******************************************************************************
*   MIUGetGPIStatus : Get GPI Status
*
*	@param      iDeviceIndex, [in] DeviceIndex
*   @param      nNumber, [in] GPI Number (0~5)
*   @param      pStatus, [in,out] GPI Status
*   
*   @return     Error Value 
******************************************************************************/
DLLFunction int __cdecl MIUGetGPIStatus(char iDeviceIndex, char nGPINumber, char* pStatus);


/******************************************************************************
*   MIUSetGPOStatus : Set GPO Status
*
*	@param      iDeviceIndex, [in] DeviceIndex
*   @param      nGPONumber, [in] GPO Number (0~1)
*   @param      nStatus, [in] GPO Status
*   
*   @return     Error Value 
******************************************************************************/
DLLFunction int __cdecl MIUSetGPOStatus(char iDeviceIndex, char nGPONumber, char nStatus);


/******************************************************************************
*   MIUGetGPIOMode : Get GPIO Mode
*
*	@param      iDeviceIndex, [in] DeviceIndex
*   @param      nGPIONumber, [in] GPIO Number (0~3)
*   @param      pMode, [in,out] GPIO Mode (0:Output, 1:Input)
*   
*   @return     Error Value 
******************************************************************************/
DLLFunction int __cdecl MIUGetGPIOMode(char iDeviceIndex, char nGPIONumber, char* pMode);


/******************************************************************************
*   MIUSetGPOStatus : Set GPIO Mode
*
*	@param      iDeviceIndex, [in] DeviceIndex
*   @param      nGPIONumber, [in] GPIO Number (0~3)
*   @param      nMode, [in] GPO Status
*   
*   @return     Error Value 
******************************************************************************/
DLLFunction int __cdecl MIUSetGPIOMode(char iDeviceIndex, char nGPIONumber, char nMode);


/******************************************************************************
*   MIUGetGPIOStatus : Get GPIO Status
*
*	@param      iDeviceIndex, [in] DeviceIndex
*   @param      nNumber, [in] GPIO Number (0~3)
*   @param      pStatus, [in,out] GPIO Status
*   
*   @return     Error Value 
******************************************************************************/
DLLFunction int __cdecl MIUGetGPIOStatus(char iDeviceIndex, char nGPIONumber, char* pStatus);


/******************************************************************************
*   MIUSetGPOStatus : Set GPIO Status
*
*	@param      iDeviceIndex, [in] DeviceIndex
*   @param      nNumber, [in] GPIO Number (0~3)
*   @param      nStatus, [in] GPO Status
*   
*   @return     Error Value 
******************************************************************************/
DLLFunction int __cdecl MIUSetGPIOStatus(char iDeviceIndex, char nGPIONumber, char nStatus);


// 20121025 
/******************************************************************************
*   OpenShortTest : Open Short Test  
*
*	@param      iDeviceIndex, [in] DeviceIndex
*   @param      UpperTestResult, [out] Upper Diode Test Result (OS_TESTPIN_COUNT (43) channel)
*   @param      LowerTestResult, [out] Lower Diode Test Result (OS_TESTPIN_COUNT (43) channel)
*   @param      nSensorMode, [in] SensorMode
*   @param      UpperEn, [in] Upper test pin Enable 
*   @param      LowererEn, [in] Lower test pin Enable 
*   @param      UpperSleep, [in] Upper test sleep time 
*   @param      LowerSleep, [in] Lower test sleep time
*   
*   @return     Error Value 
******************************************************************************/
DLLFunction unsigned int __cdecl OpenShortTest(char iDeviceIndex, float* UpperTestResult, float* LowerTestResult, unsigned char nInputCurrent, unsigned char nSensorMode,int* UpperEn, int* LowerEn, int UpperSleep, int LowerSleep);


/******************************************************************************
*   LeakageTest : Leakage Current Test  
*
*	@param      iDeviceIndex, [in] DeviceIndex
*   @param      LeakageTestResult, [out] Leakage Test Result (OS_TESTPIN_COUNT (43) channel)
*   @param      IOVoltage, [in] IO Channel Voltage
*   @param      nDelay, [in] Power, Gnd 관련 측정 delay
*   @param      LeakageEn, [in] Leakage test pin Enable
*   @param      LeakageSleep, [in] Leakage test sleep time
*   
*   @return     Error Value 
******************************************************************************/
DLLFunction unsigned int __cdecl LeakageTest(char iDeviceIndex, float* LeakageTestResult, float IOVoltage  , unsigned char nSensorMode,int* LeakageEn, int LeakageSleep);



/******************************************************************************
*   MIUSetI2CMode : MIU Set I2C Mode
*
*	@param		iDeviceIndex, [in] DeviceIndex
*               
*   @param      nMode (0 : 8bit address, 8bit data, 1 : 8bit address, 16bit data
*                      2 : 16bit address, 8bit data, 3 : 16bit address, 16bit data)
*
*   @return     Error Value
******************************************************************************/
DLLFunction int __cdecl MIUSetI2CMode(char iDeviceIndex, unsigned short nMode);


/******************************************************************************
*   MIUSetI2CID : MIU Set I2C ID
*
*	@param		iDeviceIndex, [in] DeviceIndex
*               
*   @param      nID (바꾸고자 하는 I2C ID)
*
*   @return     Error Value
******************************************************************************/
DLLFunction int __cdecl MIUSetI2CID(char iDeviceIndex, unsigned char nI2CID);



/******************************************************************************
*   MIUSet5V12VPowSequence : MIUSet5V12VPowSequence
*
*	@param		iDeviceIndex, [in] DeviceIndex
*               
*   @param      nSequence, 5v와 12v On 순서 
                0 : before 1st Power , 
				1 : before 2nd Power ,
				2 : before 3rd Power ,
				3 : before 4th Power ,
				4 : before 5th Power ,
				5 : after  5th Power 	

*
*   @return     Error Value
******************************************************************************/
DLLFunction int __cdecl MIUSet5V12VPowSequence(char iDeviceIndex, int nSequence);




/******************************************************************************
*   MIUSetPowerChSleep : MIUSetPowerChSleep
*
*	@param		iDeviceIndex, [in] DeviceIndex
*               
*   @param      PowerChSleep, power Ch별  Sleep // int PowerChSleep[6]

			    PowerChSleep[0] = 0; //1stPowerChannel Sleep
				PowerChSleep[1] = 0; //2ndPowerChannel Sleep
				PowerChSleep[2] = 0; //3rdPowerChannel Sleep
				PowerChSleep[3] = 0; //4thPowerChannel Sleep
				PowerChSleep[4] = 0; //5thPowerChannel Sleep
				PowerChSleep[5] = 0; //5V or 12V  Sleep


*
*   @return     Error Value
******************************************************************************/
DLLFunction int __cdecl MIUSetPowerChSleep(char iDeviceIndex, int* PowerChSleep);







/******************************************************************************
*   MIULSTtoFPGA : Setup Lens shading table in FPGA
*	@param		iDeviceIndex
*	@param		iLSCRomIndex

*   @return     Error Value
******************************************************************************/
DLLFunction int __cdecl MIULSTtoFPGA(char iDeviceIndex , unsigned char iLSCRomIndex);

/******************************************************************************
*   MIUReadLsVersion : Read Lens Shading version.
*
*	@param      iDeviceIndex, [in] DeviceIndex
*   @param      nSize, [in] Data size
*   @param      pData, [out] Data pointer
*   @param      nMemoryIndex, [in] EEPROM INDEX to convert to physical memory address
*   
*   @return     Error Value 
******************************************************************************/
DLLFunction int __cdecl MIUReadLsVersion(char iDeviceIndex, unsigned int nSize, unsigned char* pData, unsigned char nMemoryIndex);


/******************************************************************************
*   MIURomDataDownload : CalData   Download to EEPROM(BOOTROM) 
*
*	@param      iDeviceIndex, [in] DeviceIndex
*   @param      nSize, [in] Data size
*   @param      pData, [in] Data pointer
*   @param      nMemoryIndex, [in] EEPROM INDEX to convert to physical memory address
*   
*   @return     Error Value 
******************************************************************************/
DLLFunction int __cdecl MIURomDataDownload(char iDeviceIndex, unsigned int nSize, unsigned char* pData, unsigned char nMemoryIndex);




/******************************************************************************
*   LSCGetTableSize : Get LSC Table Size;
*
*	@param		nWidth,		[in] image  width
*	@param		nHeight,	[in] image  Height
*	@param		pSize,		[out] Table size
*
*   @return    return Status
******************************************************************************/
DLLFunction int __cdecl LSCGetTableSize(unsigned int nWidth, unsigned int nHeight, unsigned int* pSize);




/******************************************************************************
*   LSCTableMake : LSC Table 생성
*
*	@param		pAverageImage, [in] Average  Image
*
*   @return    return Status
******************************************************************************/
DLLFunction int __cdecl LSCTableMake(double* pAverageImage,unsigned int nWidth, unsigned int nHeight, unsigned short* pEvenTable, unsigned short* pOddTable, int* pEvenSize, int* pOddSize);

/******************************************************************************
*   MIUGetDeviceCount : MIUGetDeviceCount
*
*
*   @return     Device Count
******************************************************************************/
DLLFunction int __cdecl MIUGetDeviceCount();



/******************************************************************************
*   MIUGetDeviceCount : MIUCheckLicense
*
*
*   @return     Error Value
******************************************************************************/
DLLFunction int __cdecl MIUCheckLicense(char* inputStr);


/******************************************************************************
*   MIUGetDllVersion : Get DLL Version
*	@param		nVersion, [out] DLL Version

*   @return     Error Value
******************************************************************************/
DLLFunction int __cdecl MIUGetDllVersion(unsigned char* nVersion);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Event Callback
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef   void   (CALLBACK   *EventCallback)(char, int);  

/******************************************************************************
*   USBRestartCallback : Set Evnet Callback function
*
*   @return     Error Value
******************************************************************************/
DLLFunction void  WINAPI USBRestartCallback(EventCallback func, unsigned int WaitTime); 

#ifdef _cplusplus
}
#endif

#endif  //__V5U_DLLEX_H__
