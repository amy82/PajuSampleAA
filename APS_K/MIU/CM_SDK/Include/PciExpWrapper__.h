// PciExpWrapper.h: interface for the CPciExpWrapper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PCIEXPWRAPPER_H__114BF46B_9176_44E0_983E_BDC6F7BCD4C6__INCLUDED_)
#define AFX_PCIEXPWRAPPER_H__114BF46B_9176_44E0_983E_BDC6F7BCD4C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef _DLL_COMPILE
#define DLL_API	__declspec(dllexport)
#endif

#include "stdio.h"

// cam configuration 관련 상수 정의
#define OUT_FORMAT_RAW10		0x01
#define OUT_FORMAT_RAW8			0x02
#define OUT_FORMAT_12BIT		0x03
// power 관련 상수 정의
#define POWER_CH1				1
#define POWER_CH2				2
#define POWER_CH3				3
#define POWER_CH4				4
#define POWER_LED				5
// GPIO 관련 상수 정의
#define GPIO13					0	// 이전 버전 혼환
#define GPIO15					1
#define GPIO19					2
#define GPIO21					3
#define GPIO25					4
#define GPIO27					5	// 이전 버전 혼환

#define GPIO_1P8_PORT13			0
#define GPIO_1P8_PORT15			1
#define GPIO_1P8_PORT19			2
#define GPIO_1P8_PORT21			3
#define GPIO_1P8_PORT25			4
#define GPIO_1P8_PORT27			5

#define GPIO_3P3_PORT31			0
#define GPIO_3P3_PORT33			1

#define EXT_GPIO_3P3_PORT1		0
#define EXT_GPIO_3P3_PORT2		1
#define EXT_GPIO_3P3_PORT3		2
#define EXT_GPIO_3P3_PORT4		3
#define EXT_GPIO_3P3_PORT5		4
#define EXT_GPIO_3P3_PORT6		5
#define EXT_GPIO_3P3_PORT7		6
#define EXT_GPIO_3P3_PORT8		7
#define EXT_GPIO_3P3_PORT9		8
#define EXT_GPIO_3P3_PORT10		9
// CLK 관련 상수 정의
#define GPIO_CLK_OFF			0x00
#define GPIO_CLK_8Mhz			0x01
#define GPIO_CLK_9Mhz			0x02
#define GPIO_CLK_10Mhz			0x04
// IMG Info 관련 상수 정의

// return value
#define RET_GRABBER_RD_ERR		0xff000001
// Power 관련 return value
#define PWR_RET_OK				0x00000000
#define PWR_RET_COM_ERR			0xFF000001
#define PWR_RET_BIT_RANGE_ERR	0xFF000002
// GPIO 관련 return value
#define GPIO_RET_OK				0x00000000
#define GPIO_RET_COM_ERR		0xFF000001
#define GPIO_RET_BIT_RANGE_ERR	0xFF000002
// CLK 관련 return value
#define CLK_RET_OK				0x00000000
#define CLK_RET_COM_ERR			0xFF000001
// IMG Info 관련 return value
#define IMG_INFO_DATA_OK		0x00000000
#define IMG_INFO_RET_COM_ERR	0xFF000001
#define IMG_INFO_DISABLE		0xFF000002
#define FRAME_VALID_OK			0x00000000
#define FRAME_CODE_HIGH_ERR		0x00000001
#define FRAME_CODE_LOW_ERR		0x00000002
#define FRAME_COUNT_ERR			0x00000004
#define FRAME_LINE_COUNT_ERR	0x00000008
// i2c 관련 return value
#define I2C_RET_OK				0x00000000
#define I2C_RET_COM_ERR			0xFF000001
#define I2C_RET_RAM_CLR_ERR		0xFF000002
#define I2C_RET_TIMEOUT_ERR		0xFF000003
#define I2C_RET_SLEEP_OK		0x80000000
#define I2C_RET_ACK_SUCCESS		0x80000000	// 8'b10000000 ;
#define I2C_RET_CMD_ERR			0x9F000000	// 8'b10011111 ;	// 9F
#define I2C_RET_DATA_ERR		0x9E000000	// 8'b10011110 ;	// 9E
#define I2C_RET_BUS_BUSY_ERR	0x8F000000	// 8'b10001111 ;
#define I2C_RET_ACK_ERR_SLAVE	0xC0000000	// 8'b11000000 ;
#define I2C_RET_ACK_ERR_REG1	0xA0000000	// 8'b10100000 ;
#define I2C_RET_ACK_ERR_REG2	0x90000000	// 8'b10010000 ;
#define I2C_RET_ACK_ERR_DATA1	0x88000000	// 8'b10001000 ;
#define I2C_RET_ACK_ERR_DATA2	0x84000000	// 8'b10000100 ;
#define I2C_RET_ACK_ERR_DATA3	0x82000000	// 8'b10000010 ;
#define I2C_RET_ACK_ERR_DATA4	0x81000000	// 8'b10000001 ;
// ad5840 special i2c 관련 return value
#define S_I2C_RET_OK					0x00000000
#define S_I2C_RET_COM_ERR				0xFF000001
#define S_I2C_RET_RAM_CLR_ERR			0xFF000002
#define S_I2C_RET_TIMEOUT_ERR			0xFF000003
#define S_I2C_RET_ACK_SUCCESS			0x80000000	// 8'b10000000 ;
#define S_I2C_RET_INVALID_ACT_ERR		0xFF000000	// 8'b1111_1111 ; // 8'hff ;
#define S_I2C_RET_CMD_ERR				0x9F000000	// 8'b1001_1111 ; // 8'h9F ;
#define S_I2C_RET_DATA_ERR				0x9e000000	// 8'b1001_1110 ; // 8'h9E ;
#define S_I2C_RET_ACK_ERR_VCM_SADDR		0xA1000000	// 8'b1010_0001 ; // 8'hA1 ;
#define S_I2C_RET_ACK_ERR_VCM_DATA1		0xA2000000	// 8'b1010_0010 ; // 8'hA2 ;
#define S_I2C_RET_ACK_ERR_VCM_DATA2		0xA3000000	// 8'b1010_0011 ; // 8'hA3 ;
#define S_I2C_RET_ACK_ERR_VCM_DATA3		0xA4000000	// 8'b1010_0100 ; // 8'hA4 ;
#define S_I2C_RET_ACK_ERR_HALL_SADDR	0xA5000000	// 8'b1010_0101 ; // 8'hA5 ;
#define S_I2C_RET_ACK_ERR_POSI_SADDR	0xA6000000	// 8'b1010_0110 ; // 8'hA6 ;
#define S_I2C_RET_ACK_ERR_POSI_DATA1	0xA7000000	// 8'b1010_0111 ; // 8'hA7 ;
#define S_I2C_RET_ACK_ERR_POSI_DATA2	0xA8000000	// 8'b1010_1000 ; // 8'hA8 ;
#define S_I2C_RET_ACK_ERR_POSI_DATA3	0xA9000000	// 8'b1010_1001 ; // 8'hA9 ;
#define S_I2C_RET_BUS_BUSY_VCM_START	0xB1000000	// 8'b1011_0001 ; // 8'hB1 ;
#define S_I2C_RET_BUS_BUSY_VCM_STOP		0xB2000000	// 8'b1011_0010 ; // 8'hB2 ;
#define S_I2C_RET_BUS_BUSY_HALL_START	0xB3000000	// 8'b1011_0011 ; // 8'hB3 ;
#define S_I2C_RET_BUS_BUSY_HALL_STOP	0xB4000000	// 8'b1011_0100 ; // 8'hB4 ;
#define S_I2C_RET_BUS_BUSY_POSI_START	0xB5000000	// 8'b1011_0101 ; // 8'hB5 ;
#define S_I2C_RET_BUS_BUSY_POSI_STOP	0xB6000000	// 8'b1011_0110 ; // 8'hB6 ;
#define S_I2C_RET_BUS_BUSY_STOP			0xB7000000	// 8'b1011_0111 ; // 8'hB7 ;


typedef struct _ISD_DEV_INFO
{
	UINT		nDevDrvVer;
	UINT		nTotalPCICardNumber;
	UCHAR		cBusNumber;
	UCHAR		cFuncNumber;
	UCHAR		cDevNumber;
} ISD_DEV_INFO;

//typedef struct _I2C_CMD_LIST
//{
//	unsigned char		cSlaveID;
//	unsigned short int	snAddr;
//	unsigned char		cWriteVal;
//} I2C_CMD_LIST;
// 20140204 16M 수정
typedef struct _I2C_CMD_LIST
{
	unsigned char		cSlaveID ;
	unsigned short int	snAddr ;
	unsigned int		cWriteVal ;
	unsigned int		nI2cMode ;	
} I2C_CMD_LIST;


typedef struct
{
	int		frame_cnt ;			// 0 word
	int		line_cnt ;			// 1 word
	int		mipi_word_info ;	// 2 word
	int		mipi_err_info ;		// 3 word
	int		enc_info ;			// 4 word
	int		enc_val ;			// 5 word
	int		reser6[2] ;			// 6,7 word
	int		vol_ch1_2 ;			// 8 word
	int		vol_ch3_4 ;			// 9 word
	int		reser10[2] ;		// 10,11 word
	int		dyn_cur_ch1_2 ;		// 12 word
	int		dyn_cur_ch3_4 ;		// 13 word
	int		stb_cur_ch1_2 ;		// 14 word
	int		stb_cur_ch3_4 ;		// 15 word
	int		flash_pwr ;			// 16 word
	int		crc_err_cnt ;		// 17 word
	int		crc_err_frm_cnt ;	// 18 word
	int		crc_err_total_cnt ;	// 19 word
	int		reser17[42] ;		// 20~61 word
	int		validCodeH ;		// 62 word
	int		validCodeL ;		// 63 word
} tagIMG_INFO ;

typedef struct
{
	int			wr_date_year ;
	int			wr_date_Day ;
	int			wr_code ;
	int			reser1 ;
	float		cur_offset_ch0 ;
	float		cur_offset_ch1 ;
	float		cur_offset_ch2 ;
	float		cur_offset_ch3 ;
	char		phase_tap ;
	char		reser2[7] ;
} tagGRABBER_PARAM ;

typedef struct
{
	int		firstTry[256] ;
	int		secondTry[256] ;
	int		thirdTry[256] ;
} tagI2C_RESULT ;

typedef enum
{
	FW_VESION5 = 0,
	FW_VESION6,
	FW_VESION7,
	FW_VESION8
} tagFW_VESION ;

#ifdef _DLL_COMPILE
class DLL_API CPciExpWrapper  
#else
class CPciExpWrapper  
#endif
{
private :	
	bool			m_bRevInfo ;
	tagIMG_INFO		m_tImgInfo ;
	int				m_iframe_cnt ;
	int				m_iline_cnt ;
	int				m_iWidth ;
	int				m_iRaw10Width ;
	int				m_iHeight ;
	__int64			m_iGrabLength ;
	int				m_iOutFormat ;
	tagGRABBER_PARAM	m_tGrabberParam ;
	tagFW_VESION	m_tFwVersion ;
	bool			m_bIFCardEndian ;

public:
	int					m_nPara;
	bool				m_bErrorLog ;
	CRITICAL_SECTION	m_csI2C ;
	// PCIe
	int GetDeviceInfo				(int nMaxDevNum, ISD_DEV_INFO	*devInfo);
	int DeviceOpen					(int nDeviceNum);	// to open device
	int DeviceOpenWithDevInfo		(int nReqBusNum, int nReqFuncNum, int nReqDevNum);
	int DeviceClose					();
	int DeviceReset					();	// device reset & I/F Card reset	

	int CM_RegisterWrite			(int nOffset, __int64 n64Value) ;
	int CM_RegisterRead				(int nOffset, __int64 *n64Value) ;
	int	CM_CheckReadDone			(int k, int nThreadID, int *nReadValue) ;
    // version
    void CM_GetSWVersionInfo		(char *pVersion) ;
	int CM_GetImageGrabberVersion	(char *pHwVersion, char *pFwVersion) ;
	int CM_GetImageGrabberID		(void) ;
	void CM_DebugViewMsg			(char *szStr, ...) ;
    // Img    
	int CM_ChkGrabDone				(int *nCurrentIndex);
	int CM_ImageCopySafe			(int nIndexNum, int **nBuffer);
	int CM_GrabStart				(int nImgWidth, int nImgHeight, int nGrabOption) ;
	int CM_GrabStop					(void) ;
	int CM_GrabReStart				(void) ;
	void CM_Raw10ToRaw8				(unsigned char *pRaw10, unsigned char *pRaw8) ;
	void CM_12BitToRaw8				(unsigned char *pRaw10, unsigned char *pRaw8) ;

	int CM_MemInit					(__int64 nGrabLength, int nTimeOutMs);
	int CM_ImageCopy				(int nIndexNum, int *nBuffer, int nLength);	
	int CM_GrabEnable				(bool bOn) ;
	int CM_SetGrabDef				(void) ;
	int CM_ResetMIPIClock			(bool bOn) ;	
	int CM_SetMipiLane				(int nLaneVal) ;
	int CM_SetMIPIGpio				(int iVal) ;
	int CM_SetMIPIClockPhaseDelay	(int uiDelayTap) ;
	int CM_SetOutputFormat			(int uiFormat) ;
	int CM_SensorEject				(void) ;
	int	CM_SaveGrabberParam			(void) ;
	int	CM_SetGrabberParam			(tagGRABBER_PARAM *pGrabberParam) ;
	int	CM_GetGrabberParam			(tagGRABBER_PARAM *pGrabberParam) ;
	int	CM_SetGrabberParamPhaseTap	(char chTap) ;
	int	CM_SetGrabberParamCurrentOffSet(float fCh0, float fCh1, float fCh2, float fCh3) ;
	int	CM_GetGrabberParamPhaseTap	(char *pTap) ;
	int	CM_GetGrabberParamCurrentOffSet(float *pCh0, float *pCh1, float *pCh2, float *pCh3) ;
    // power control and measure voltage and current  
    int CM_PowerQueueRead			(int uiAddr, int *pData) ;
    int	CM_GetResistorValue			(int iChannel, float fVoltage) ;
    int	CM_DirectGetVoltage			(float *pPwr1Vol, float *pPwr2Vol, float *pPwr3Vol, float *pPwr4Vol) ;
    		
	int CM_EnablePower				(int iChannel, BOOL bEn) ;			// TRUE -> on, FALSE -> off
	int CM_SetVoltage				(int iChannel, float fVoltage) ;	// voltage set range : 1.0 ~ 5.0V
	int CM_VoltageMeasurementEnable	(int bEnable) ;						//  1-> enable, 0 -> disable
	int CM_GetVoltage				(float *pPwr1Vol, float *pPwr2Vol, float *pPwr3Vol, float *pPwr4Vol) ;
	int CM_CurrentMeasurementEnable	(int bEnable) ;
	int	CM_GetCurrentOffSet			(float *pPwr1Cur, float *pPwr2Cur, float *pPwr3Cur, float *pPwr4Cur) ;
	int CM_GetStandbyCurrent		(float *pPwr1Cur, float *pPwr2Cur, float *pPwr3Cur, float *pPwr4Cur) ;
	int CM_GetDynamicCurrent		(float *pPwr1Cur, float *pPwr2Cur, float *pPwr3Cur, float *pPwr4Cur) ;
	int CM_FlashPowerMeasurementEnable	(int bEnable) ;						//  1-> enable, 0 -> disable
	int CM_GetFlashPower			(float *pFlashVol, float *pFlashCur) ;	
	// Gpio control
	int CM_GpioQueueRead			(int uiAddr) ;
	
	int	CM_GetGpio1P8Dir			(void) ;		 	
	int	CM_SetGpio1P8Dir			(int uiGpioBit, int bDir) ;		//  1-> input, 0 -> output
	int	CM_DirectGetGpio1P8			(int uiGpioBit) ;
	int	CM_SetGpio1P8				(int uiGpioBit, int bHigh) ;
	int CM_GetGpio1P8				(int uiGpioBit) ;
		
	int	CM_GetGpio3P3Dir			(void) ;
	int	CM_SetGpio3P3Dir			(int uiGpioBit, int bDir) ;		//  1-> input, 0 -> output
	int	CM_DirectGetGpio3P3			(int uiGpioBit) ;
	int	CM_SetGpio3P3				(int uiGpioBit, int bHigh) ;
	int CM_GetGpio3P3				(int uiGpioBit) ;
	
	int	CM_GetExtGpio3P3Dir			(void) ;
	int	CM_SetExtGpio3P3Dir			(int uiGpioBit, int bDir) ;		//  1-> input, 0 -> output
	int	CM_DirectGetExtGpio3P3		(int uiGpioBit) ;
	int	CM_SetExtGpio3P3			(int uiGpioBit, int bHigh) ;
	int CM_GetExtGpio3P3			(int uiGpioBit) ;
	// clk control
	int CM_SetMclk					(int bOn, float fFreq) ;
	int CM_SetAuxClk				(int bOn, int uiFreq) ;
	int CM_I2CSetClk				(int iClk) ;
	// 이전 버전 호환 함수
	int CM_SetGpio					(int iIoNum, int bHigh) ;			//  1-> high, 0 -> low
	int CM_GetGpio31				(void) ;	// return value : 1-> high, 0-> low, ff -> read error
	int CM_GetGpio33				(void) ;	// return value : 1-> high, 0-> low, ff -> read error
	int CM_SocketOpen				(void) ;	// return value : 1-> open, 0-> close, ff -> read error
	int CM_SocketBoardConnetion		(void) ;	// return value : 1-> connetion, 0->disconntion, ff -> read error
	int CM_SetGpioClk				(int bOn, int nFreq) ;	// bOn : 1->on, 0->off(output zero), nFreq->GPIO_CLK_OFF, GPIO_CLK_8Mhz, GPIO_CLK_9Mhz, GPIO_CLK_10Mhz
	// IMG infomation
	int CM_ImgInfoEnable			(void) ;
	int CM_ImgInfoDisable			(void) ;
	int CM_CopyImgInfo				(int nIndexNum) ;	
	int	CM_InfoIsValidFrame			(void) ;
	int CM_InfoGetFrameCnt			(int *pFrameCount) ;
	int CM_InfoGetLineCnt			(int *pLineCount) ;	
	int CM_InfoGetVolage			(float *pPwr1Vol, float *pPwr2Vol, float *pPwr3Vol, float *pPwr4Vol) ;
	int CM_InfoGetStandbyCurrent	(float *pPwr1Cur, float *pPwr2Cur, float *pPwr3Cur, float *pPwr4Cur) ;
	int CM_InfoGetDynamicCurrent	(float *pPwr1Cur, float *pPwr2Cur, float *pPwr3Cur, float *pPwr4Cur) ;	
	int	CM_InfoGetFlashPower		(float *pVol, float *pCur) ;
	int CM_InfoGetEncStatus			(int *pEncStatus) ;
	int CM_InfoGetEnc				(int *pEncValue) ;
	int CM_ImgInfoEncReset			(void) ;
	int	CM_InfoGetCRC				(int *pCRCErrCnt, int *pCRCErrFrmCnt, int *pCRCErrTotalCnt) ;
	int	CM_InfoCRCInfoClear			(void) ;
	// i2c
	int CM_SetI2CData				(int nRegAddr, int nData) ;
	int CM_SetI2CCommand			(int nCmdType, int nThreadId, bool bIsRead, int nRegAddrSize, int nDataSize, int nSlaveAddr, int nDataLength) ;
	int CM_GetI2CResponse			(int nThreadId, int *pRdDataH, int *pRdDataL) ;
	int CM_ClearI2CResRam			(int nThreadId) ;
	int CM_WriteI2C					(int nRegAddrSize, int nDataSize, int nSlaveAddr, int nRegAddr, int *pData, int nDataLength) ;
	int CM_ReadI2C					(int nRegAddrSize, int nDataSize, int nSlaveAddr, int nRegAddr, int *pData, int nDataLength) ;
	// retry 3 회 실시, return value는 error count 이다.
	// error는 CM_I2CGetWriteResult, CM_I2CGetReadResult 를 이용하여 확인 가능하다
	int CM_I2CSingleWrite			(int nID, int nRegAddrSize, int nDataSize, int nSlaveAddr, int nRegAddr, int nData) ;
	int CM_I2CSingleRead			(int nID, int nRegAddrSize, int nDataSize, int nSlaveAddr, int nRegAddr, int *pData) ;
	int CM_I2CBurstWrite			(int nID, int nRegAddrSize, int nDataSize, int nSlaveAddr, int nRegAddr, int *pData, int nDataLength) ;
	int CM_I2CBurstRead				(int nID, int nRegAddrSize, int nDataSize, int nSlaveAddr, int nRegAddr, int *pData, int nDataLength) ;
	int CM_I2CSleep					(float fMiliSecond) ;
	int CM_I2CGetWriteResult		(tagI2C_RESULT *pBufPoint) ;
	int CM_I2CGetReadResult			(tagI2C_RESULT *pBufPoint) ;

	int AD5840_SpecialI2CEnable		(bool bEn) ;
	int AD5840_SpecialI2CSetData	(int nFirstPosiX, int nFirstPosiY, int nLastPosiX, int nLastPosiY) ;
	int AD5840_SpecialI2CSetCmd		(int nSAddr, int nFPosiSize, int nLPosiSize, int nHallDataSize, int nHallRdSize) ;
	int AD5840_SpecialI2CSetDelayTime(int nTxDelayNano, int nRxDelayNano) ;
	int AD5840_SpecialI2C			(int nSAddr, int nFirstPosiX, int nFirstPosiY, bool bLastPosiEn, int nLastPosiX, int nLastPosiY, int nHallRdSize, int *pXValue, int *pYValue) ;

	int SpecialI2CEnable			(bool bEn) ;
	int SpecialI2CSetData			(int nDataSize, BYTE *pData, int nLastDataSize, BYTE *pLastData) ;
	int SpecialI2CSetCmd			(int nSAddr, int nTxDataSize, int nRxDataSize, int nRxRepeatSize, int nLastTxDataSize) ;
	int SpecialI2CSetDelayTime		(int nTxDelayNano, int nRxDelayNano) ;
	int SpecialI2C					(BYTE byID, int nData, BYTE *dacBuf, int nRead, int nBytesPerRead, BYTE *hallBuf, int nPosi, BYTE *posBuf) ;

	// firm upgrade
	bool FlashGetResFifoDcnt		(int *pDataCnt) ;
	bool FlashGetResFifoData		(__int64 *pData) ;
	BOOL FLASH_8x32_Write			(int nAddress, unsigned char *data, unsigned char byteLength) ;
	BOOL FLASH_Bulk_Erase			(void) ;
	BOOL FLASH_Sector_Erase			(int nAddress) ;
	void FLASH_ResFlush				(void) ;
	BOOL FLASH_Verification			(char* str) ;
	BOOL FLASH_8x32_Read			(int nAddress, __int64 *pRdData) ;

	// I2C Error Log
	FILE*	m_pErrLogFile ;
	char m_cErrLogFileName[256] ;
	int SetErrLog					(int iPara, bool bSet) ;
	int I2CErrLogFileCreate			(void) ;
	int I2CErrLogWrite				(char *szStr, ...) ;
	// ini parser
	int INI_GetI2cSlaveAddr			(char *fileName, unsigned char *cSlaveAddr) ;
	int INI_GetImgResolution		(char *fileName, int *nWidth, int *nHeight, int *nSensorFormat) ;
	int INI_GetI2cCommands			(char *fileName, unsigned char sensorID, I2C_CMD_LIST *cmdPtr, int nMaxCmd) ;	

	// ois innotek 함수들, ois 용 말고는 사용하지 말것
	int SetWrapperInstance			(int nBoard, CPciExpWrapper *wrapper, int para = 1, bool bErrorLog = false) ;
	BOOL TWI_WriteMultipleA			(int nSlvAddr, unsigned char *data, int len) ;
	BOOL TWI_ReadMultipleIadrA		(int nSlvAddr, int len, int addr, int addrLn, unsigned char *data) ;
	BOOL E2P_WriteSingleIadrA		(int nSlvAddr, int addr, unsigned char data) ;
	BOOL E2P_ReadSingleIadrA		(int nSlvAddr, int len, int addr, int addrLn, unsigned char *data) ;
	/////////////////////////////////////////////////
	
	int m_nAllocPCIXpCore;
	CPciExpWrapper();
	virtual ~CPciExpWrapper();
};

// ois innotek 함수들, ois 용 말고는 사용하지 말것
#ifdef _DLL_COMPILE
	int DLL_API GetFrameCount(void) ;
	BOOL DLL_API I2CWrite(int nRegAddrSize, int nDataSize, int nSlaveAddr, int nRegAddr, int *pData, int nDataLength);
	BOOL DLL_API I2CRead(int nRegAddrSize, int nDataSize, int nSlaveAddr, int nRegAddr, int *pData, int nDataLength) ;
	BOOL DLL_API TWI_WriteMultiple(int nSlvAddr, unsigned char *data, int len) ;
	BOOL DLL_API TWI_ReadMultipleIadr(int nSlvAddr, int len, int addr, int addrLn, unsigned char *data) ;
	BOOL DLL_API E2P_WriteSingleIadr(int nSlvAddr, int addr, unsigned char data) ;
	BOOL DLL_API E2P_ReadSingleIadr(int nSlvAddr, int len, int addr, int addrLn, unsigned char *data) ;		
#else
	int GetFrameCount(void) ;
	BOOL I2CWrite(int nRegAddrSize, int nDataSize, int nSlaveAddr, int nRegAddr, int *pData, int nDataLength);
	BOOL I2CRead(int nRegAddrSize, int nDataSize, int nSlaveAddr, int nRegAddr, int *pData, int nDataLength) ;
	BOOL TWI_WriteMultiple(int nSlvAddr, unsigned char *data, int len) ;
	BOOL TWI_ReadMultipleIadr(int nSlvAddr, int len, int addr, int addrLn, unsigned char *data) ;
	BOOL E2P_WriteSingleIadr(int nSlvAddr, int addr, unsigned char data) ;
	BOOL E2P_ReadSingleIadr(int nSlvAddr, int len, int addr, int addrLn, unsigned char *data) ;	
#endif
/////////////////////////////////////////////////

#endif // !defined(AFX_PCIEXPWRAPPER_H__114BF46B_9176_44E0_983E_BDC6F7BCD4C6__INCLUDED_)

