// PciExpWrapper.cpp: implementation of the CPciExpWrapper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PciExpWrapper.h"
#include "PciExpCore.h"
#include "pci_error.h"
#include <stdlib.h>
#include <stdio.h>
#include "time.h"
#include "math.h"
#include "sys/stat.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm")
#pragma warning(disable:4101 4333 4305 4553 4390 4101 4244 4996)

CPciExpCore		*gp_clsPCIExpress;

#define _CM_SW_VERSION			"CM IMG GRABBER LIB V7.4.1"

// memory map start
#define SRIO_BUF_NUM_IMG		0
#define SRIO_BUF_NUM_PWR		1
#define SRIO_BUF_NUM_GPIO		2
// addr 0000~00f0 : image grab related registers
#define ADDR_GRAB_TRIGGER_EN	0x000
#define ADDR_SRIO_STATUS		0x010
#define ADDR_GRAB_DEF			0x020
#define ADDR_PHERI_RESET_CTRL	0x030
#define ADDR_HW_VERSION			0x050
#define ADDR_FW_VERSION			0x060
#define ADDR_SEND_INFO			0x070
#define ADDR_CAROPTIC_SENSOR_RST	0x080
#define ADDR_VHSYNC_REVERSE		0x090

// addr 0100~01f0 : Mipi Setting
#define ADDR_MIPI_CLK_DELAY_RST	0x110
#define ADDR_MIPI_CLK_DELAY		0x120
#define ADDR_OUTPUT_FORMAT		0x130
#define ADDR_CRC_CLEAR			0x140
// addr 0200~02f0 : PWR1, 2, 3, 4 enable and voltage control, LED_PWR enable control
#define ADDR_PWR1_EN			0x200
#define ADDR_PWR2_EN			0x210
#define ADDR_PWR3_EN			0x220
#define ADDR_PWR4_EN			0x230
#define ADDR_PWR_LED_EN			0x240
#define ADDR_PWR_I2C_WR			0x280
#define ADDR_PWR_I2C_RD			0x280
#define ADDR_PWR_I2C_RD_RDY		0x290
#define ADDR_PWR_I2C_RD_SIZE	0x290
// addr 0300~03f0 : GPIO, Aux. Clk, Enc
#define ADDR_GPIO_ALT_FUNC		0x300
#define ADDR_GPIO1P8_DIR		0x310
#define ADDR_GPIO3P3_DIR		0x320
#define ADDR_EXT_GPIO3P3_DIR	0x330
#define ADDR_GPIO1P8_WR			0x340
#define ADDR_GPIO3P3_WR			0x350
#define ADDR_EXT_GPIO3P3_WR		0x360
#define ADDR_GPIO1P8_RD			0x370
#define ADDR_GPIO3P3_RD			0x380
#define ADDR_EXT_GPIO3P3_RD		0x390
#define ADDR_ROTARY_SW_RD		0x3a0
// addr 0400~04f0 : CLK Control, Flash Control, MIPI IO control
#define ADDR_CLK_I2C_WR			0x400
#define ADDR_CLK_I2C_RD			0x400
#define ADDR_CLK_I2C_RD_RDY		0x410
#define ADDR_CLK_I2C_RD_SIZE	0x410
#define ADDR_CLK_EN				0x430
#define ADDR_MIPI_IO			0x480


// addr 0500~05f0 : CM I2C Control       		
#define ADDR_IMG_I2C_CMD_WR		0x500
#define ADDR_IMG_I2C_DATA_WR	0x510
#define ADDR_IMG_I2C_CLK_REF	0x520
#define ADDR_IMG_I2C_ACT_SEL	0x530
#define ADDR_IMG_AD5840_DLY		0x540
#define ADDR_IMG_AD5840_CMD_WR	0x550
#define ADDR_IMG_AD5840_F_DATA	0x560
#define ADDR_IMG_AD5840_L_DATA	0x570
#define ADDR_IMG_SI2C_FRAME_DLY	0x580
#define ADDR_IMG_SI2C_CMD_WR	0x590
#define ADDR_IMG_SI2C_DATA_WR	0x5A0
// addr 0600~06f0 : Measure Current and Voltage
#define ADDR_VOLTAGE_EN			0x600
#define ADDR_CURRENT_EN			0x610
#define ADDR_PWR_STB_CURRENT1	0x620
#define ADDR_PWR_STB_CURRENT2	0x640
#define ADDR_PWR_DYN_CURRENT1	0x660
#define ADDR_PWR_DYN_CURRENT2	0x680
#define ADDR_PWR_VOLTAGE1		0x6b0
#define ADDR_PWR_VOLTAGE2		0x6c0
#define ADDR_FLASH_PWR_EN		0x6d0
#define ADDR_FLASH_PWR			0x6e0


// addr 0c00~0cf0 : Voltage I2C Control for Diff Position
#define ADDR_PW_I2C_CMD_WR		0xC00
#define ADDR_PW_I2C_DATA_WR		0xC10
#define ADDR_PW_I2C_CLK_REF		0xC20
#define ADDR_PW_I2C_ACT_SEL		0xC30
#define ADDR_PW_AD5840_DLY		0xC40
#define ADDR_PW_AD5840_CMD_WR	0xC50
#define ADDR_PW_AD5840_F_DATA	0xC60
#define ADDR_PW_AD5840_L_DATA	0xC70
#define ADDR_PW_SI2C_FRAME_DLY	0xC80
#define ADDR_PW_SI2C_CMD_WR		0xC90
#define ADDR_PW_SI2C_DATA_WR	0xCA0


// addr 0700~07f0 : flash control
// addr 0800~08f0 : Aux clk, Enc, UART
#define ADDR_AUX_CLK_CTRL		0x800
#define ADDR_ENC_CTRL			0x810
#define ADDR_UART_TX			0x850
#define ADDR_UART_RX			0x860
#define ADDR_UART_RES_STAT		0x870


// memory map end

#define I2C_CMD_CODE			0x14C80000
#define I2C_DATA_CODE			0xb55a0000
#define SI2C_DATA_CODE			0x00b55a00

#define I2C_CMD_NORMAL_I2C		0xA5
#define I2C_CMD_SLEEP			0xA3
#define I2C_CMD_WRITE			0x00
#define I2C_CMD_READ			0x01
        
#define CM_VLATAGE_MAX			3.5
#define CM_VLATAGE_MIN			0.95
        
#define NWRITE_BLK_SIZE			524288
#define NREAD_BLK_SIZE			524288
#define SKIP_FRAME				0
#define Fxo						31.98
#define Fvco_MIN				2080.0
#define HS_DIV_MAX				1022.0
#define FRAC_VAL				536870912.0	// 2^29 = 536870912

// ref. vol = 3000mV, resolution = 16bit(65535), gain = 0.5		-> 3000 / 65535 / 0.5			= 0.09155413138017853055619134813458
#define VOLTAGE_PARAM			0.09155413138017853055619134813458
// ref. vol = 3000mV, resolution = 16bit(65535), gain = 4.984	-> 3000 / 65535 /4.984			= 0.00918480451245771775242690089633
#define DYNAMIC_CURRENT_PARAM	0.00918480451245771775242690089633		// mA 단위 출력
// ref. vol = 1000mV, resolution = 16bit(65535), gain = 495		-> 1000 / 65535 / 495 * 1000	= 0.03082630686201297325124287815979
#define STANDBY_CURRENT_PARAM	0.03082630686201297325124287815979		// uA 단위 출력
// ref. vol = 3000mV, resolution = 16bit(65535), gain = 1.990	-> 3000 / 65535 / 1.99			= 0.023003550598034806672409886465976
#define FLASH_CURRENT_PARAM		0.023003550598034806672409886465976		// mA 단위 출력

#define RAM_RD_RETRY_NUM		10	//
#define I2C_RETRY_NUM			3	// 3회 retry
#define I2C_TIME_LIMIT			30	// 10ms
#define PWR_READ_TIME_LIMIT		30	// 5ms
#define SRIO_RESP_DLY			0 

#define FLASH_ADDR_GRABBER_PARAM		0xff0000
#define GRABBER_PARAM_WR_CODE			0xEAC0BCF6

// gpio control reg.
typedef struct
{
	unsigned short	gpio00	: 1 ;
	unsigned short	gpio01	: 1 ;
	unsigned short	gpio02	: 1 ;
	unsigned short	gpio03	: 1 ;
	unsigned short	gpio04	: 1 ;
	unsigned short	gpio05	: 1 ;
	unsigned short	gpio06	: 1 ;
	unsigned short	gpio07	: 1 ;
		
    unsigned short	gpio08	: 1 ;
	unsigned short	gpio09	: 1 ;
	unsigned short	gpio10	: 1 ;
	unsigned short	gpio11	: 1 ;
	unsigned short	gpio12	: 1 ;
	unsigned short	gpio13	: 1 ;
	unsigned short	gpio14	: 1 ;
	unsigned short	gpio15	: 1 ;
} tagGPIO_BIT ;
typedef union
{
	unsigned short	all ;
	tagGPIO_BIT		bit ;
} tagGPIO_REG ;

// main clk control reg.
typedef struct
{
	unsigned char		LP2 ;
	unsigned char		LP1 ;

	unsigned int		M_Frac ;
	unsigned short int	M_Int ;

	unsigned short int	HS_DIV ;
	unsigned char		LS_DIV ;
} tagCLK_GEN ;

static int	gI2CWriteTryNum ;
static int	gI2CReadTryNum ;
static int	gI2CWriteRetInfo[I2C_RETRY_NUM][256] ;
static int	gI2CReadRetInfo[I2C_RETRY_NUM][256] ;

static int	gPWI2CWriteTryNum ;
static int	gPWI2CReadTryNum ;
static int	gPWI2CWriteRetInfo[I2C_RETRY_NUM][256] ;
static int	gPWI2CReadRetInfo[I2C_RETRY_NUM][256] ;
// ois innotek 을 위한 변수들, ois 용 말고는 사용하지 말것
static CPciExpWrapper	*g_wrapper[4] ;
/////////////////////////////////////////////////

CPciExpWrapper::CPciExpWrapper()
{
	m_nPara = 1;
	m_bErrorLog = 0 ;
	m_nAllocPCIXpCore = 0;
	gp_clsPCIExpress = NULL;
	m_tFwVersion = FW_VESION8 ;

	// ois innotek 을 위한 코드, ois 용 말고는 사용하지 말것
	for(int i=0 ; i<4 ; i++) 
	{
		g_wrapper[i] = NULL ;
	}
	/////////////////////////////////////////////////
	
	::InitializeCriticalSection(&m_csI2C) ;
}
CPciExpWrapper::~CPciExpWrapper()
{
	if(gp_clsPCIExpress)	delete gp_clsPCIExpress ;
	
	::DeleteCriticalSection(&m_csI2C) ;
}

int CPciExpWrapper::DeviceOpenWithDevInfo(int nReqBusNum, int nReqFuncNum, int nReqDevNum) 
{
	int lRet, nDeviceNum;
	int pciCardNum, nDrvVer, nBusNum, nFuncNum, nDevNum;
	int i;

	if (m_nAllocPCIXpCore)
		return STATUS_PCIEXP_CLOSEFIRST;
		
	if(gp_clsPCIExpress)	delete gp_clsPCIExpress ;
	
	nDeviceNum = 1;

	m_nAllocPCIXpCore = nDeviceNum;
	gp_clsPCIExpress = new CPciExpCore;

	lRet = gp_clsPCIExpress[0].OpenDevice(0);
	if (lRet) return lRet;

	gp_clsPCIExpress[0].GetDeviceInformation(&pciCardNum, &nDrvVer, &nBusNum, &nFuncNum, &nDevNum);
	gp_clsPCIExpress[0].CloseDevice();
	for (i=0; i < pciCardNum; i++) {
		lRet = gp_clsPCIExpress[0].OpenDevice(i);
		gp_clsPCIExpress[0].GetDeviceInformation(&pciCardNum, &nDrvVer, &nBusNum, &nFuncNum, &nDevNum);
		if ( (nReqBusNum == nBusNum) && (nReqFuncNum == nFuncNum) && (nReqDevNum == nDevNum)) {
			lRet = gp_clsPCIExpress[0].ChkPhyMemStatus();

			if (lRet)	{
				m_nAllocPCIXpCore = 0;		return lRet;
			}

			lRet = gp_clsPCIExpress[0].IFCardResetSet();
			if (lRet) return lRet;
			Sleep(50);
			lRet = gp_clsPCIExpress[0].IFCardResetClr();
			if (lRet) return lRet;
			Sleep(10);
			lRet = gp_clsPCIExpress[0].KernelMemoryAllocate(2*1024*1024);
			if (lRet) return lRet;
			Sleep(100);

			return STATUS_PCIEXP_SUCCESS;
		}
		gp_clsPCIExpress[0].CloseDevice();

	}
	m_nAllocPCIXpCore = 0;
	delete gp_clsPCIExpress;

	return STATUS_PCIEXP_NODEVICE;
}


int CPciExpWrapper::GetDeviceInfo(int nMaxDevNum, ISD_DEV_INFO	*devInfo) {
	int lRet, i;
	int pciCardNum, nDrvVer, nBusNum, nFuncNum, nDevNum;

	if(gp_clsPCIExpress)	delete gp_clsPCIExpress ;
	
	m_nAllocPCIXpCore = 1;	
	gp_clsPCIExpress = new CPciExpCore;

	for (i=0; i < nMaxDevNum; i++) {
		lRet = gp_clsPCIExpress->OpenDevice(i);
		if (lRet == STATUS_PCIEXP_NODEVICE) {
			m_nAllocPCIXpCore = 0;
			delete gp_clsPCIExpress;
			gp_clsPCIExpress = NULL;
			return (i+1);	// 존재하는 디바이스의 숫자를 Return
		}
		else if (lRet) {
			m_nAllocPCIXpCore = 0;
			delete gp_clsPCIExpress;
			gp_clsPCIExpress = NULL;
			return lRet;
		}
		
		gp_clsPCIExpress->GetDeviceInformation(&pciCardNum, &nDrvVer, &nBusNum, &nFuncNum, &nDevNum);

		devInfo[i].nTotalPCICardNumber	=	pciCardNum;
		devInfo[i].nDevDrvVer			=	nDrvVer;
		devInfo[i].cBusNumber			=	nBusNum;
		devInfo[i].cFuncNumber			=	nFuncNum;
		devInfo[i].cDevNumber			=	nDevNum;

		lRet = gp_clsPCIExpress->CloseDevice();
	}
	m_nAllocPCIXpCore = 0;
	delete gp_clsPCIExpress;
	gp_clsPCIExpress = NULL;

	return STATUS_PCIEXP_SUCCESS;
}

int	CPciExpWrapper::DeviceOpen(int nDeviceNum) {
	int lRet;//, nDeviceNum;
	int pciCardNum, nDrvVer, nBusNum, nFuncNum, nDevNum;
	

	if (m_nAllocPCIXpCore)
	{
		DeviceClose() ;
		//return STATUS_PCIEXP_CLOSEFIRST;
	}

	if(gp_clsPCIExpress)	delete gp_clsPCIExpress ;
	
	m_nAllocPCIXpCore = 1;
	gp_clsPCIExpress = new CPciExpCore;

	lRet = gp_clsPCIExpress[0].OpenDevice(nDeviceNum);
	if (lRet) {
		m_nAllocPCIXpCore = 0;
		delete(gp_clsPCIExpress);
		return lRet;
	}

	gp_clsPCIExpress[0].GetDeviceInformation(&pciCardNum, &nDrvVer, &nBusNum, &nFuncNum, &nDevNum);

	lRet = gp_clsPCIExpress[0].ChkPhyMemStatus();

	if (lRet)	{
		m_nAllocPCIXpCore = 0;
		delete(gp_clsPCIExpress);
		return lRet;
	}

	lRet = gp_clsPCIExpress[0].IFCardResetSet();
	if (lRet) {
		m_nAllocPCIXpCore = 0;
		delete(gp_clsPCIExpress);
		return lRet;
	}
	Sleep(10);
	lRet = gp_clsPCIExpress[0].IFCardResetClr();
	if (lRet) {
		m_nAllocPCIXpCore = 0;
		delete(gp_clsPCIExpress);
		return lRet;
	}
	Sleep(10);
	lRet = gp_clsPCIExpress[0].KernelMemoryAllocate(2*1024*1024);
	if (lRet) {
		m_nAllocPCIXpCore = 0;
		delete(gp_clsPCIExpress);
		return lRet;
	}
	Sleep(10);	

	return STATUS_PCIEXP_SUCCESS;
}

int CPciExpWrapper::DeviceClose() {
	int lRet;
	
	if (m_nAllocPCIXpCore == 0)
		return STATUS_PCIEXP_OPENFIRST;

	lRet = gp_clsPCIExpress[0].KernelMemroyFree();

	lRet = gp_clsPCIExpress[0].CloseDevice();
	if (lRet) return lRet;

	m_nAllocPCIXpCore = 0;
	delete gp_clsPCIExpress;
	gp_clsPCIExpress = NULL;
	return STATUS_PCIEXP_SUCCESS;
}

int	CPciExpWrapper::DeviceReset() {
	int lRet;
	int val[4];
	int	addr[2], sTime, eTime;
	tagGRABBER_PARAM	tmpParam ;

	if (m_nAllocPCIXpCore == 0) 
		return STATUS_PCIEXP_OPENFIRST;

	lRet = STATUS_PCIEXP_SUCCESS;

	lRet = gp_clsPCIExpress[0].srio_user_rst();
	Sleep(10);
	if (lRet) 
		return (lRet | 0x00010000);
	lRet = gp_clsPCIExpress[0].srio_peer_reset();
	if (lRet) 
		return (lRet | 0x00020000);
	Sleep(10);
	lRet = gp_clsPCIExpress[0].srio_user_rst();	
	if (lRet) 
		return (lRet | 0x00010000);
	Sleep(10);

	addr[1] = 0;
	val[1]	= 0;
	
	addr[0]	= 0x0; 
	addr[1] = 0;
	val[0]	= 0;

	lRet = gp_clsPCIExpress[0].srio_nread(0, addr, 8);
	if		(lRet)			return STATUS_PCIEXP_NREADFAIL;

	sTime = GetTickCount();
	
	for (;;) {
		lRet = gp_clsPCIExpress[0].srio_nread_done_chk(val);
		if(lRet == STATUS_PCIEXP_SUCCESS)
		{
			// 20140303 grabber param 추가
			CM_GetGrabberParam(&tmpParam) ;
			
			CM_SetMIPIClockPhaseDelay(tmpParam.phase_tap) ;	// mipi clock delay

			return STATUS_PCIEXP_SUCCESS;	// 읽히는 값은 
		}
		eTime = GetTickCount();
		if		((eTime - sTime) > 300)				return STATUS_PCIEXP_TIMEOUT;
		Sleep(1);
	}

	return STATUS_PCIEXP_SUCCESS; //	실제 올수없는 영역임

}
int CPciExpWrapper::CM_RegisterWrite(int nOffset, __int64 n64Value) {
	int lRet;
	int	addr[2], data[2];

	memcpy(data, &n64Value, 8);
	addr[1] = 0;
	addr[0] = nOffset;

	lRet = gp_clsPCIExpress[0].srio_nwrite(0, addr, 8, data);

	return lRet;
}

int CPciExpWrapper::CM_RegisterRead(int nOffset, __int64 *n64Value) {
	int		lRet, addr[2], data[2];
	int		sTime, eTime;

	addr[1] = 0;
	addr[0] = nOffset;

	lRet = gp_clsPCIExpress[0].srio_nread(0, addr, 8);
	if		(lRet)			return STATUS_PCIEXP_NREADFAIL;

	sTime = GetTickCount();

	for (;;) {
		lRet = gp_clsPCIExpress[0].srio_nread_done_chk(data);
		if		(lRet == STATUS_PCIEXP_SUCCESS)	{
			n64Value[0] =  ( (__int64)data[1] & 0x00000000ffffffff) | ( ((__int64) data[0]<<32) & 0xffffffff00000000) ;
			return STATUS_PCIEXP_SUCCESS;	// 읽히는 값은 
		}
		eTime = GetTickCount();
		if		((eTime - sTime) > 300)				return STATUS_PCIEXP_TIMEOUT;
		//Sleep(1);
	}

	return lRet;
}
int	CPciExpWrapper::CM_CheckReadDone(int k, int nThreadID, int *nReadValue)
{
	int ret ;

	ret = gp_clsPCIExpress->ReqChkDone(k, nThreadID, nReadValue) ;

	return ret;
}
// version
void CPciExpWrapper::CM_GetSWVersionInfo(char *pVersion)
{
	char	*str ;
	int		i ;

	str = _CM_SW_VERSION ;

	for(i=0 ; *str != 0 ; i++)
	{
		*pVersion++ = *str++ ;
	}
	*pVersion = 0 ;
}
int CPciExpWrapper::CM_GetImageGrabberVersion(char *pHwVersion, char *pFwVersion)
{
	__int64		rdData ;
	int			ret ;
	char		tempCode ;

	ret = CM_RegisterRead(ADDR_FW_VERSION, &rdData) ;
	if(ret != STATUS_PCIEXP_SUCCESS)	return ret ;

	// i/f card 에 따라 endian 이 다를 경우 대비
	tempCode = (char)( (rdData >> 56) & 0x0ff) ;
	if(tempCode == 'F')		m_bIFCardEndian = true ;
	else					m_bIFCardEndian = false ;

	if(tempCode == 'F')		tempCode = (char)( (rdData >> 24) & 0x0ff) ;
	else					tempCode = (char)( (rdData >> 32) & 0x0ff) ;
	// fw version save
	if(tempCode == '5')			m_tFwVersion = FW_VESION5 ;
	else if(tempCode == '6')	m_tFwVersion = FW_VESION6 ;
	else if(tempCode == '7')	m_tFwVersion = FW_VESION7 ;
	else						m_tFwVersion = FW_VESION8 ;

	if(m_bIFCardEndian == false)	// 구버전 IF
	{
		*pFwVersion++ = (char)( (rdData >> 0) & 0x0ff) ;
		*pFwVersion++ = (char)( (rdData >> 8) & 0x0ff) ;
		*pFwVersion++ = (char)( (rdData >> 16) & 0x0ff) ;
		*pFwVersion++ = (char)( (rdData >> 24) & 0x0ff) ;
		*pFwVersion++ = (char)( (rdData >> 32) & 0x0ff) ;
		*pFwVersion++ = (char)( (rdData >> 40) & 0x0ff) ;
		*pFwVersion++ = (char)( (rdData >> 48) & 0x0ff) ;
		*pFwVersion++ = (char)( (rdData >> 56) & 0x0ff) ;
		*pFwVersion = 0 ;
	}
	else
	{
		*pFwVersion++ = (char)( (rdData >> 56) & 0x0ff) ;
		*pFwVersion++ = (char)( (rdData >> 48) & 0x0ff) ;
		*pFwVersion++ = (char)( (rdData >> 40) & 0x0ff) ;
		*pFwVersion++ = (char)( (rdData >> 32) & 0x0ff) ;
		*pFwVersion++ = (char)( (rdData >> 24) & 0x0ff) ;
		*pFwVersion++ = (char)( (rdData >> 16) & 0x0ff) ;
		*pFwVersion++ = (char)( (rdData >> 8) & 0x0ff) ;
		*pFwVersion++ = (char)( (rdData >> 0) & 0x0ff) ;
		*pFwVersion = 0 ;
	}
	ret = CM_RegisterRead(ADDR_HW_VERSION, &rdData) ;
	if(ret != STATUS_PCIEXP_SUCCESS)	return ret ;
	if(m_bIFCardEndian == false)	// 구버전 IF
	{
		*pHwVersion++ = (char)( (rdData >> 0) & 0x0ff) ;
		*pHwVersion++ = (char)( (rdData >> 8) & 0x0ff) ;
		*pHwVersion++ = (char)( (rdData >> 16) & 0x0ff) ;
		*pHwVersion++ = (char)( (rdData >> 24) & 0x0ff) ;
		*pHwVersion++ = (char)( (rdData >> 32) & 0x0ff) ;
		*pHwVersion++ = (char)( (rdData >> 40) & 0x0ff) ;
		*pHwVersion++ = (char)( (rdData >> 48) & 0x0ff) ;
		*pHwVersion++ = (char)( (rdData >> 56) & 0x0ff) ;
		*pHwVersion = 0 ;
	}
	else
	{
		*pHwVersion++ = (char)( (rdData >> 56) & 0x0ff) ;
		*pHwVersion++ = (char)( (rdData >> 48) & 0x0ff) ;
		*pHwVersion++ = (char)( (rdData >> 40) & 0x0ff) ;
		*pHwVersion++ = (char)( (rdData >> 32) & 0x0ff) ;
		*pHwVersion++ = (char)( (rdData >> 24) & 0x0ff) ;
		*pHwVersion++ = (char)( (rdData >> 16) & 0x0ff) ;
		*pHwVersion++ = (char)( (rdData >> 8) & 0x0ff) ;
		*pHwVersion++ = (char)( (rdData >> 0) & 0x0ff) ;
		*pHwVersion = 0 ;
	}
	return ret ;
}
int CPciExpWrapper::CM_GetImageGrabberID(void)
{
	int				ret ;
	int				addr[2], data[2] ;
	int				threadID ;
	int				checkBit ;
	int				rxData[2] ;
	int				startTime ;
	int				endTime ;
	int				limitTime ;

	threadID = 0 ;
	CM_CheckReadDone(SRIO_BUF_NUM_GPIO, threadID, &rxData[0]) ;

	addr[1] = 0 ;
	addr[0] = ADDR_ROTARY_SW_RD ;
	data[1] = 0 ;
	data[0] = threadID ;	// 8bit thread id
	ret = gp_clsPCIExpress[0].srio_nwrite(SRIO_BUF_NUM_GPIO, addr, 8, data) ;

	startTime = GetTickCount() ;
	while(1)
	{
		Sleep(SRIO_RESP_DLY) ;
		ret = CM_CheckReadDone(SRIO_BUF_NUM_GPIO, threadID, &rxData[0]) ;
		checkBit = (rxData[0] & 0x80000000) ;
		if(checkBit == 0x80000000)
		{
			return rxData[1] & 0x0F ;
		}
		endTime = GetTickCount() ;
		limitTime = endTime - startTime ;
		if(limitTime > PWR_READ_TIME_LIMIT)
		{
			//CM_DebugViewMsg("Read timeout for Image Grabber ID") ;
			return RET_GRABBER_RD_ERR ;
		}
	}
}
void CPciExpWrapper::CM_DebugViewMsg(char *szStr, ...)
{
/*
#ifdef _CM_DEBUG
	va_list			ap ;
	char			buffer[1024] ;
	char			str[1024] ;

	va_start(ap, szStr) ;
	vsprintf_s(buffer, szStr, ap) ; 
	va_end(ap) ;

	sprintf_s(str, 1024, "PRI : %s\r\n", buffer) ;

	OutputDebugString(str) ;
#else
#endif
*/
}
// img
int CPciExpWrapper::CM_ChkGrabDone(int *nCurrentIndex)
{
	int lRet;

	lRet = gp_clsPCIExpress[0].GrabChkDone64(nCurrentIndex);

	return lRet;
}

int	CPciExpWrapper::CM_ImageCopySafe(int nIndexNum, int **nBuffer)
{
	int		ret ;
	int		length ;
	int		frameValid ;
	int		i ;
	int		errCnt ;

	if (m_iOutFormat == OUT_FORMAT_RAW8)
	{
		length = m_iWidth * m_iHeight ;;

	}
	else if (m_iOutFormat == OUT_FORMAT_12BIT)
	{
		if (m_iPixelPer2byte)		length = m_iWidth * m_iHeight * 2 * 2;
		else						length = m_iWidth * m_iHeight * 2;
	}
	else if (m_iOutFormat == OUT_FORMAT_RAW10)
	{
		length = m_iRaw10Width * m_iHeight ;
	}

	

	//20140303 이미지 info 받도록 수정
	if(m_tFwVersion == FW_VESION5)
	{
		ret = gp_clsPCIExpress[0].mem_phymem_copy_back_safe(nBuffer, nIndexNum-1, length) ;

		return ret ;
	}
	
	ret = gp_clsPCIExpress[0].mem_phymem_copy_back_safe(nBuffer, nIndexNum-1, length) ;
	return ret ;
	/*
	errCnt = 0 ;
	for(i=0 ; i<3 ; i++)
	{
		CM_CopyImgInfo(nIndexNum-1-i) ;

		frameValid = CM_InfoIsValidFrame() ;
		
		if(frameValid != FRAME_VALID_OK)
		{
			errCnt++ ;
		}
		else
		{
			ret = gp_clsPCIExpress[0].mem_phymem_copy_back_safe(nBuffer, nIndexNum-1, length) ;
			if(ret)	return ret ;

			break ;
		}
	}
	if(errCnt != 0)
	{
		CM_GrabReStart() ;
	}

	return i ;
	*/
}
int CPciExpWrapper::CM_GrabStart(int nImgWidth, int nImgHeight, int nGrabOption)
{
	int			ret ;
	__int64		grabLen ;
	int			width ;

	if(m_tFwVersion != FW_VESION5)
	{
		CM_ImgInfoEnable() ;	// Img info rec. enable
	}
	
	CM_GrabEnable(0) ;		// trigger off
	CM_ResetMIPIClock(1) ;	// mipi reset
	
	m_iWidth = nImgWidth;
	m_iRaw10Width = (nImgWidth * 5/4) ;
	m_iHeight = nImgHeight ;
	
	if(m_iOutFormat == OUT_FORMAT_RAW8)
	{
		if(m_bRevInfo == 1)		m_iGrabLength = (__int64)( (m_iWidth * m_iHeight) + 7 + 0x100) & 0xfffffff8 ;
		else					m_iGrabLength = (__int64)( (m_iWidth * m_iHeight) + 7) & 0xfffffff8 ;
	}
	else if (m_iOutFormat == OUT_FORMAT_12BIT)
	{
		if (m_iPixelPer2byte == 1){
			if(m_bRevInfo == 1)		m_iGrabLength = (__int64)( (m_iWidth * m_iHeight*2*2 ) + 7 + 0x100) & 0xfffffff8 ;
			else					m_iGrabLength = (__int64)( (m_iWidth * m_iHeight*2*2) + 7) & 0xfffffff8 ;
		}
		else {
			if(m_bRevInfo == 1)		m_iGrabLength = (__int64)( (m_iWidth * m_iHeight*2 ) + 7 + 0x100) & 0xfffffff8 ;
			else					m_iGrabLength = (__int64)( (m_iWidth * m_iHeight*2) + 7) & 0xfffffff8 ;
		}
		
	}
	else
	{
		if(m_bRevInfo == 1)		m_iGrabLength = (__int64)( (m_iRaw10Width * m_iHeight) + (nImgWidth % 4) + 7 + 0x100) & 0xfffffff8 ;
		else					m_iGrabLength = (__int64)( (m_iRaw10Width * m_iHeight) + (nImgWidth % 4) + 7) & 0xfffffff8 ;
	}
		

	ret = CM_MemInit(m_iGrabLength, 5000) ;

	CM_SetGrabDef() ;
	//CM_SetMipiLane(m_nLaneNum);
			
	CM_ResetMIPIClock(0) ;	// mipi reset off
	CM_GrabEnable(1) ;		// trigger on
	
	return ret ;
}
int CPciExpWrapper::CM_GrabStop(void)
{
	int	ret ;

	ret = CM_GrabEnable(0) ;		// trigger on
	Sleep(10) ;
	
	return ret ;
}
int CPciExpWrapper::CM_GrabReStart(void)
{
	int			ret ;
	__int64		grabLen ;

	CM_GrabEnable(0) ;		// trigger off
	Sleep(5) ;
	CM_ResetMIPIClock(1) ;	// mipi reset
	Sleep(5) ;

	ret = CM_MemInit(m_iGrabLength, 5000) ;

	CM_ResetMIPIClock(0) ;	// mipi reset off
	CM_GrabEnable(1) ;		// trigger on
	
	return ret ;
}
void CPciExpWrapper::CM_Raw10ToRaw8(unsigned char *pRaw10, unsigned char *pRaw8)
{
	int		x, y, k ;

	for(y=0 ; y<m_iHeight ; y++)
	{
		for(x=0 ; x<m_iWidth/4 ; x++)
		{
			for(k=0 ; k<4 ; k++)
			{
				pRaw8[y*m_iWidth + 4*x + k] = (pRaw10[y*m_iRaw10Width + 5*x + k]) ;
			}
		}
	}
}

void CPciExpWrapper::CM_Interlace_fusion(unsigned char *pRaw8_out, unsigned char *pRaw8_1, unsigned char *pRaw8_2){		//
	int		x, y, k ;
	for(y=0 ; y<m_iHeight ; y++)
	{
		
		for(x=0 ; x<m_iWidth*2; x++){
			pRaw8_out[ y*m_iWidth*2*2 + x ] = pRaw8_1[y*m_iWidth*2 + x];
			pRaw8_out[ y*m_iWidth*2*2 + (1 * m_iWidth*2)  + x ] = pRaw8_2[y*m_iWidth*2 + x];
		}
	}
}


void CPciExpWrapper::CM_YUV411ToRaw8(unsigned char *p12Bit, unsigned char *pRaw8){		//
	int		x, y, k ;
	for(y=0 ; y<m_iHeight ; y++)
	{
		for(x=0 ; x<m_iWidth/4 ; x++)		// 4 pixel , 8byte
		{			
// 			pRaw8[y*m_iWidth*2 + x*8+1 ] =	p12Bit[y*m_iWidth*2 + 8*x+1];		// Y0
// 			pRaw8[y*m_iWidth*2 + x*8+0 ] =  ( ( p12Bit[y*m_iWidth*2 + 8*x+0] & 0x0c ) << 4 ) | ( ( p12Bit[y*m_iWidth*2 + 8*x+2] & 0x0c ) << 2 ) | ( ( p12Bit[y*m_iWidth*2 + 8*x+4] & 0x0c ) ) | ( ( p12Bit[y*m_iWidth*2 + 8*x+6] & 0x0c ) >> 2 ) ;
// 			pRaw8[y*m_iWidth*2 + x*8+3 ] =	p12Bit[y*m_iWidth*2 + 8*x+3];		// Y1
// 			pRaw8[y*m_iWidth*2 + x*8+2 ] =  ( ( p12Bit[y*m_iWidth*2 + 8*x+0] & 0x03 ) << 6 ) | ( ( p12Bit[y*m_iWidth*2 + 8*x+2] & 0x03 ) << 4 ) | ( ( p12Bit[y*m_iWidth*2 + 8*x+4] & 0x03 << 2 ) ) | ( ( p12Bit[y*m_iWidth*2 + 8*x+6] & 0x03 ) ) ;
// 			pRaw8[y*m_iWidth*2 + x*8+5 ] =	p12Bit[y*m_iWidth*2 + 8*x+5];		// Y2
// 			pRaw8[y*m_iWidth*2 + x*8+4 ] =  ( ( p12Bit[y*m_iWidth*2 + 8*x+0] & 0x0c ) << 4 ) | ( ( p12Bit[y*m_iWidth*2 + 8*x+2] & 0x0c ) << 2 ) | ( ( p12Bit[y*m_iWidth*2 + 8*x+4] & 0x0c ) ) | ( ( p12Bit[y*m_iWidth*2 + 8*x+6] & 0x0c ) >> 2 ) ;
// 			pRaw8[y*m_iWidth*2 + x*8+7 ] =	p12Bit[y*m_iWidth*2 + 8*x+7];		// Y3
// 			pRaw8[y*m_iWidth*2 + x*8+6 ] =  ( ( p12Bit[y*m_iWidth*2 + 8*x+0] & 0x03 ) << 6 ) | ( ( p12Bit[y*m_iWidth*2 + 8*x+2] & 0x03 ) << 4 ) | ( ( p12Bit[y*m_iWidth*2 + 8*x+4] & 0x03 << 2 ) ) | ( ( p12Bit[y*m_iWidth*2 + 8*x+6] & 0x03 ) ) ;

			
			pRaw8[y*m_iWidth*2 + x*8+1 ] =	(( p12Bit[y*m_iWidth*2 + 8*x+0] & 0x0f ) << 4) | (( p12Bit[y*m_iWidth*2 + 8*x+1] & 0xf0 ) >> 4) ;		// Y0
			pRaw8[y*m_iWidth*2 + x*8+0 ] =  (( p12Bit[y*m_iWidth*2 + 8*x+0] & 0xc0 )) | ( ( p12Bit[y*m_iWidth*2 + 8*x+2] & 0xc0 ) >> 2 ) | ( ( p12Bit[y*m_iWidth*2 + 8*x+4] & 0xc0 ) >> 4 ) | ( ( p12Bit[y*m_iWidth*2 + 8*x+6] & 0xc0 ) >> 6 ) ;
			pRaw8[y*m_iWidth*2 + x*8+3 ] =	(( p12Bit[y*m_iWidth*2 + 8*x+2] & 0x0f ) << 4) | (( p12Bit[y*m_iWidth*2 + 8*x+3] & 0xf0 ) >> 4) ;		// Y1
			pRaw8[y*m_iWidth*2 + x*8+2 ] =  (( p12Bit[y*m_iWidth*2 + 8*x+0] & 0x30 ) << 2 ) | ( ( p12Bit[y*m_iWidth*2 + 8*x+2] & 0x30 )) | ( ( p12Bit[y*m_iWidth*2 + 8*x+4] & 0x30 ) >> 2 ) | ( ( p12Bit[y*m_iWidth*2 + 8*x+6] & 0x30 ) >> 4 ) ;
			pRaw8[y*m_iWidth*2 + x*8+5 ] =	(( p12Bit[y*m_iWidth*2 + 8*x+4] & 0x0f ) << 4) | (( p12Bit[y*m_iWidth*2 + 8*x+5] & 0xf0 ) >> 4) ;		// Y2
			pRaw8[y*m_iWidth*2 + x*8+4 ] =  (( p12Bit[y*m_iWidth*2 + 8*x+0] & 0xc0 )) | ( ( p12Bit[y*m_iWidth*2 + 8*x+2] & 0xc0 ) >> 2 ) | ( ( p12Bit[y*m_iWidth*2 + 8*x+4] & 0xc0 ) >> 4 ) | ( ( p12Bit[y*m_iWidth*2 + 8*x+6] & 0xc0 ) >> 6 ) ;
			pRaw8[y*m_iWidth*2 + x*8+7 ] =	(( p12Bit[y*m_iWidth*2 + 8*x+6] & 0x0f ) << 4) | (( p12Bit[y*m_iWidth*2 + 8*x+7] & 0xf0 ) >> 4) ;		// Y3
			pRaw8[y*m_iWidth*2 + x*8+6 ] =  (( p12Bit[y*m_iWidth*2 + 8*x+0] & 0x30 ) << 2 ) | ( ( p12Bit[y*m_iWidth*2 + 8*x+2] & 0x30 )) | ( ( p12Bit[y*m_iWidth*2 + 8*x+4] & 0x30 ) >> 2 ) | ( ( p12Bit[y*m_iWidth*2 + 8*x+6] & 0x30 ) >> 4 ) ;


		}		


	}
}

void CPciExpWrapper::CM_YUV422ToRaw8(unsigned char *p12Bit, unsigned char *pRaw8){
	int		x, y, k ;

	
	for(y=0 ; y<m_iHeight ; y++)
	{
		for(x=0 ; x<m_iWidth ; x++)
		{			
			
			pRaw8[y*m_iWidth*2 + x*2] = ( (( p12Bit[y*m_iWidth*4 + 4*x+0] & 0xf ) << 4 ) | (( p12Bit[y*m_iWidth*4 + 4*x+1] & 0xf0 ) >> 4 ) ) ;		
			pRaw8[y*m_iWidth*2 + x*2+1 ] = ( (( p12Bit[y*m_iWidth*4 + 4*x+2] & 0xf ) << 4 ) | (( p12Bit[y*m_iWidth*4 + 4*x+3] & 0xf0 ) >> 4 ) ) ;	
			


//			pRaw8[y*m_iWidth + x*2] = (p12Bit[y*m_iWidth*2 + 4*x+0]) ;		
//			pRaw8[y*m_iWidth + x*2+1 ] = (p12Bit[y*m_iWidth*2 + 4*x+2]);	


//			if ( ( y == m_iHeight -1 ) && (x == m_iWidth - 1 ) ) 
//				Sleep(0);
		}

		
	}
}

void CPciExpWrapper::CM_12BitToRaw8(unsigned char *p12Bit, unsigned char *pRaw8)
{
	int		x, y, k ;
//	FILE *fp = fopen("h:\\test.dat","wt");
//	FILE *fp1 = fopen("h:\\test_8.dat","wt");

	for(y=0 ; y<m_iHeight ; y++)
	{
/////////////////////
//		for(x=0 ; x<m_iWidth ; x=x+2)
//		{			
//				pRaw8[y*m_iWidth + x] = (p12Bit[y*m_iWidth*2 + 2*x]) ;		
//				fprintf (fp,"%02x%02x ", p12Bit[y*m_iWidth*2 + 2*x],p12Bit[y*m_iWidth*2 + 2*x+1]);
//				fprintf (fp1,"%02x ", pRaw8[y*m_iWidth + x]);
//////////////////////

////////////////////////
//		for(x=0 ; x<m_iWidth/2 ; x=x++)
//		{			
//			pRaw8[y*m_iWidth + x*2] = (p12Bit[y*m_iWidth*2 + 4*x+2]) ;		
//			pRaw8[y*m_iWidth + x*2+1 ] = (p12Bit[y*m_iWidth*2 + 4*x+0]);	
////////////////////////

		/*for(x=0 ; x<m_iWidth/4 ; x=x++)
		{			
			pRaw8[y*m_iWidth + x*4] = (p12Bit[y*m_iWidth*2 + 8*x+2]) ;		
			pRaw8[y*m_iWidth + x*4+1 ] = (p12Bit[y*m_iWidth*2 + 8*x+0]);	
			pRaw8[y*m_iWidth + x*4+2 ] = (p12Bit[y*m_iWidth*2 + 8*x+6]);	
			pRaw8[y*m_iWidth + x*4+3 ] = (p12Bit[y*m_iWidth*2 + 8*x+4]);	*/
		
		
		for(x=0 ; x<m_iWidth/2 ; x=x++)
		{			
			pRaw8[y*m_iWidth + x*2] = (p12Bit[y*m_iWidth*2 + 4*x+0]) ;		
			pRaw8[y*m_iWidth + x*2+1 ] = (p12Bit[y*m_iWidth*2 + 4*x+2]);	
				

			/*fprintf (fp,"%02x%02x %02x%02x ", p12Bit[y*m_iWidth*2 + 4*x],p12Bit[y*m_iWidth*2 + 4*x+1], p12Bit[y*m_iWidth*2 + 4*x+2],p12Bit[y*m_iWidth*2 + 4*x+3]   );
//			fprintf (fp,"%02x%02x %02x%02x ", p12Bit[y*m_iWidth*2 + 2*x],p12Bit[y*m_iWidth*2 + 2*x+1], p12Bit[y*m_iWidth*2 + 2*x+2],p12Bit[y*m_iWidth*2 + 2*x+3]   );


			fprintf (fp1,"%02x %02x ", pRaw8[y*m_iWidth + x*2], pRaw8[y*m_iWidth + x*2+1 ]);

			if ( pRaw8[y*m_iWidth + x*2] == 0x3f || pRaw8[y*m_iWidth + x*2] == 0x7f || pRaw8[y*m_iWidth + x*2+1] == 0x3f || pRaw8[y*m_iWidth + x*2] == 0x7f  ) {
				printf(" ");
			}*/
		
		}				
			
//		fprintf (fp,"\n");						
//		fprintf (fp1,"\n");			
		
		
		/////////
	}
////	fwrite ((void*)p12Bit,2,m_iHeight*m_iWidth, fp  );
//	fprintf (fp,"\n");						
//	for ( x= 0 ; x < 256; x= x+2)	{
//		fprintf (fp,"%02x%02x ", p12Bit[m_iWidth * m_iHeight * 2 + x], p12Bit[m_iWidth * m_iHeight * 2 + x+1] );						
//	}
//	fclose ( fp);
//	fclose ( fp1);
}

int	CPciExpWrapper::CM_MemInit(__int64 nGrabLength, int nTimeOutMs) {

	int lRet;

	lRet = gp_clsPCIExpress[0].InitDevPhyMemory64(nGrabLength, nTimeOutMs);

	return lRet;
}
int	CPciExpWrapper::CM_ImageCopy(int nIndexNum, int *nBuffer, int nLength) {
	int lRet;
	
	lRet = gp_clsPCIExpress[0].mem_phymem_copy_back(nBuffer, nIndexNum, nLength);

	return lRet;
}
int CPciExpWrapper::CM_GrabEnable(bool bOn)
{
	int	ret ;

	ret = CM_RegisterWrite(ADDR_GRAB_TRIGGER_EN, bOn) ;	// trigger

	return ret ;
}
int CPciExpWrapper::CM_SetGrabDef(void)
{
	int			ret ;

	m_iline_cnt = m_iHeight ;

	if(m_iOutFormat == OUT_FORMAT_RAW8)
	{
		ret = CM_RegisterWrite(ADDR_GRAB_DEF,  ( (__int64)(m_iWidth | (m_iHeight<<16) ) ) | ( (__int64)(m_iWidth * m_iHeight) << 32) ) ;
	}
	else if (m_iOutFormat == OUT_FORMAT_12BIT)
	{
		if (m_iPixelPer2byte == 1){
			ret = CM_RegisterWrite(ADDR_GRAB_DEF,  ( (__int64)(m_iWidth*2*2 | (m_iHeight<<16) ) ) | ( (__int64)(m_iWidth * m_iHeight*2*2) << 32) ) ;	
		}
		else {
			ret = CM_RegisterWrite(ADDR_GRAB_DEF,  ( (__int64)(m_iWidth*2 | (m_iHeight<<16) ) ) | ( (__int64)(m_iWidth * m_iHeight*2) << 32) ) ;	
		}
	}
	else
	{
		ret = CM_RegisterWrite(ADDR_GRAB_DEF,  ( (__int64)(m_iRaw10Width | (m_iHeight<<16) ) ) | ( (__int64)(m_iRaw10Width * m_iHeight) << 32) ) ;
	}	

	return ret ;
}
int CPciExpWrapper::CM_ResetMIPIClock(bool bOn)
{
	int	ret ;

	if(bOn)
	{
		ret = CM_RegisterWrite(ADDR_PHERI_RESET_CTRL, 0x0f) ;	// Mipi sensor reset
	}
	else
	{
		ret = CM_RegisterWrite(ADDR_PHERI_RESET_CTRL, 0x0) ;	// Mipi sensor reset
	}

	return ret ;
}

int CPciExpWrapper::CM_SetMipiLane(int nLaneVal)
{
	int lRet;
	int	addr[2], data[2];
	int nLaneDef;

	nLaneDef =	(nLaneVal == 4) ? 1 :
		(nLaneVal == 2) ? 2 :
		(nLaneVal == 1) ? 4 : 1;

	//memcpy(data, &nLaneVal, 4);

	data[0] = nLaneDef;
	data[1] = 0;
	addr[1] = 0;
	addr[0] = 0x100;

	lRet = gp_clsPCIExpress[0].srio_nwrite(0, addr, 8, data);

	return lRet;
}
int	CPciExpWrapper::CM_SetMIPIGpio(int iVal)
{
	int		ret ;

	ret = CM_RegisterWrite(ADDR_MIPI_IO, iVal) ;

	return ret ;
}
int CPciExpWrapper::CM_SetMIPIClockPhaseDelay(int uiDelayTap)
{
	int		ret ;

	ret = CM_RegisterWrite(ADDR_MIPI_CLK_DELAY, uiDelayTap) ;
	Sleep(10) ;
	ret = CM_RegisterWrite(ADDR_MIPI_CLK_DELAY_RST, 0x01) ;
	Sleep(10) ;

	return ret ;
}
/*
int CPciExpWrapper::CM_SetOutputFormat(int uiFormat)						// by SJ 150828
{
	int		ret ;

	m_iOutFormat = uiFormat ;
	ret = CM_RegisterWrite(ADDR_OUTPUT_FORMAT, m_iOutFormat) ;

	return ret ;
}*/

int CPciExpWrapper::CM_SetOutputFormat(int uiFormat, int pixelperbyte = 0, int interlace = 0)			// added by SJ 151119
{
	int		ret ;

	m_iOutFormat = uiFormat ;
	ret = CM_RegisterWrite(ADDR_OUTPUT_FORMAT, m_iOutFormat) ;

	if ( 0 == pixelperbyte ) 		m_iPixelPer2byte = 0;
	else							m_iPixelPer2byte = 1;
	
	if ( 0 == interlace ) 			m_iInterlace = 0;
	else							m_iInterlace = 1;


	return ret ;
}

int	CPciExpWrapper::CM_SensorEject(void)
{
	int		ret ;
	
	ret = CM_SetGpio(GPIO_1P8_PORT13, 0) ;		if(ret) return 0x01 ;	Sleep(5) ;
	ret = CM_SetGpio(GPIO_1P8_PORT15, 0) ;		if(ret) return 0x02 ;	Sleep(5) ;
	ret = CM_SetMclk(0, 0.1f);					if(ret) return 0x04 ;	Sleep(5) ;

	ret = CM_EnablePower(POWER_CH1, FALSE) ;	if(ret) return 0x08 ;	Sleep(10) ;
	ret = CM_EnablePower(POWER_CH2, FALSE) ;	if(ret) return 0x10 ;	Sleep(10) ;
	ret = CM_EnablePower(POWER_CH3, FALSE) ;	if(ret) return 0x20 ;	Sleep(10) ;
	ret = CM_EnablePower(POWER_CH4, FALSE) ;	if(ret) return 0x40 ;	Sleep(10) ;
	ret = CM_EnablePower(POWER_LED, FALSE) ;	if(ret) return 0x80 ;	Sleep(10) ;

	return 0 ;
}
int	CPciExpWrapper::CM_SaveGrabberParam(void)
{
	int				ret ;
	int				index ;
	int				iOffset ;
	unsigned char	flashWrData[256] ;

	if(m_tFwVersion == FW_VESION5)
	{
		return true ;
	}

	for(index=0 ; index<256 ; index++)	flashWrData[index] = 0xff ;

	flashWrData[0]	= (m_tGrabberParam.wr_date_year >> 24) & 0x0ff ;
	flashWrData[1]	= (m_tGrabberParam.wr_date_year >> 16) & 0x0ff ;
	flashWrData[2]	= (m_tGrabberParam.wr_date_year >> 8) & 0x0ff ;
	flashWrData[3]	= (m_tGrabberParam.wr_date_year >> 0) & 0x0ff ;
	flashWrData[4]	= (m_tGrabberParam.wr_date_Day >> 24) & 0x0ff ;
	flashWrData[5]	= (m_tGrabberParam.wr_date_Day >> 16) & 0x0ff ;
	flashWrData[6]	= (m_tGrabberParam.wr_date_Day >> 8) & 0x0ff ;
	flashWrData[7]	= (m_tGrabberParam.wr_date_Day >> 0) & 0x0ff ;

	flashWrData[8]	= (m_tGrabberParam.wr_code >> 24) & 0x0ff ;
	flashWrData[9]	= (m_tGrabberParam.wr_code >> 16) & 0x0ff ;
	flashWrData[10]	= (m_tGrabberParam.wr_code >> 8) & 0x0ff ;
	flashWrData[11]	= (m_tGrabberParam.wr_code >> 0) & 0x0ff ;
	flashWrData[12]	= 0 ;
	flashWrData[13]	= 0 ;
	flashWrData[14]	= 0 ;
	flashWrData[15]	= 0 ;

	iOffset = (int)(m_tGrabberParam.cur_offset_ch0 * 1000) ;
	flashWrData[16]	= (iOffset >> 24) & 0x0ff ;
	flashWrData[17]	= (iOffset >> 16) & 0x0ff ;
	flashWrData[18]	= (iOffset >> 8) & 0x0ff ;
	flashWrData[19]	= (iOffset >> 0) & 0x0ff ;

	iOffset = (int)(m_tGrabberParam.cur_offset_ch1 * 1000) ;
	flashWrData[20]	= (iOffset >> 24) & 0x0ff ;
	flashWrData[21]	= (iOffset >> 16) & 0x0ff ;
	flashWrData[22]	= (iOffset >> 8) & 0x0ff ;
	flashWrData[23]	= (iOffset >> 0) & 0x0ff ;

	iOffset = (int)(m_tGrabberParam.cur_offset_ch2 * 1000) ;
	flashWrData[24]	= (iOffset >> 24) & 0x0ff ;
	flashWrData[25]	= (iOffset >> 16) & 0x0ff ;
	flashWrData[26]	= (iOffset >> 8) & 0x0ff ;
	flashWrData[27]	= (iOffset >> 0) & 0x0ff ;

	iOffset = (int)(m_tGrabberParam.cur_offset_ch3 * 1000) ;
	flashWrData[28]	= (iOffset >> 24) & 0x0ff ;
	flashWrData[29]	= (iOffset >> 16) & 0x0ff ;
	flashWrData[30]	= (iOffset >> 8) & 0x0ff ;
	flashWrData[31]	= (iOffset >> 0) & 0x0ff ;

	if( (m_tGrabberParam.phase_tap<0) & (m_tGrabberParam.phase_tap>0x1f) )	m_tGrabberParam.phase_tap = 0 ;
	flashWrData[32]	= m_tGrabberParam.phase_tap & 0x0ff ;

	ret = FLASH_Sector_Erase(FLASH_ADDR_GRABBER_PARAM) ;
	if(ret == false)	return false ;
	ret = FLASH_8x32_Write(FLASH_ADDR_GRABBER_PARAM, &flashWrData[0], 255) ;
	if(ret == false)	return false ;

	return true ;
}
int	CPciExpWrapper::CM_SetGrabberParam(tagGRABBER_PARAM *pGrabberParam)
{
	int				ret ;
	time_t			nowTime ;
	struct tm		timeinfo ;	
	int				len ;	
	int				iOffset ;
	unsigned char	flashWrData[256] ;
	char			dataStr[64] ;

	nowTime = time(NULL) ;
	localtime_s(&timeinfo, &nowTime) ;
	len = sprintf_s((char*)&dataStr[0], 64, "%.4d%.2d%.2d", timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday) ;
	
	m_tGrabberParam.wr_date_year = ( (dataStr[0]<<24) & 0xff000000) | ( (dataStr[1]<<16) & 0x00ff0000) | ( (dataStr[2]<<8) & 0x0000ff00) | (dataStr[3] & 0x0ff) ;
	m_tGrabberParam.wr_date_Day = ( (dataStr[4]<<24) & 0xff000000) | ( (dataStr[5]<<16) & 0x00ff0000) | ( (dataStr[6]<<8) & 0x0000ff00) | (dataStr[7] & 0x0ff) ;
	m_tGrabberParam.wr_code = GRABBER_PARAM_WR_CODE ;
	m_tGrabberParam.cur_offset_ch0	= pGrabberParam->cur_offset_ch0 ;
	m_tGrabberParam.cur_offset_ch1	= pGrabberParam->cur_offset_ch1 ;
	m_tGrabberParam.cur_offset_ch2	= pGrabberParam->cur_offset_ch2 ;
	m_tGrabberParam.cur_offset_ch3	= pGrabberParam->cur_offset_ch3 ;
	m_tGrabberParam.phase_tap		= pGrabberParam->phase_tap ;

	ret = CM_SaveGrabberParam() ;

	return ret ;
}

int	CPciExpWrapper::CM_GetGrabberParam(tagGRABBER_PARAM *pGrabberParam)
{
	char	hwVersion[16] ;
	char	fwVersion[16] ;
	char	tempCode ;
	int		iOffset ;
	float	fOffset ;
	__int64	flashRdData[32] ;
	int		ret ;
	
	ret = CM_GetImageGrabberVersion(&hwVersion[0], &fwVersion[0]) ;
	if(ret)
	{
		m_tGrabberParam.cur_offset_ch0 = 0 ;
		m_tGrabberParam.cur_offset_ch1 = 0 ;
		m_tGrabberParam.cur_offset_ch2 = 0 ;
		m_tGrabberParam.cur_offset_ch3 = 0 ;

		m_tGrabberParam.phase_tap = 0 ;
		return ret ;
	}

	if(m_tFwVersion == FW_VESION5)
	{
		m_tGrabberParam.cur_offset_ch0 = 0 ;
		m_tGrabberParam.cur_offset_ch1 = 0 ;
		m_tGrabberParam.cur_offset_ch2 = 0 ;
		m_tGrabberParam.cur_offset_ch3 = 0 ;

		m_tGrabberParam.phase_tap = 0 ;
		return true ;
	}

	ret = FLASH_8x32_Read(FLASH_ADDR_GRABBER_PARAM, &flashRdData[0]) ;
	if(ret == false)	return ret ;

	m_tGrabberParam.wr_date_year =  (int)( (flashRdData[0] >> 32) & 0xffffffff ) ;
	m_tGrabberParam.wr_date_Day =  (int)(flashRdData[0] & 0xffffffff ) ;

	m_tGrabberParam.wr_code = (int)( (flashRdData[1] >> 32) & 0xffffffff ) ;

	iOffset = (int)( (flashRdData[2] >> 32) & 0xffffffff ) ;
	fOffset = (float)iOffset / 1000.0 ;
	m_tGrabberParam.cur_offset_ch0 = fOffset ;

	iOffset = (int)(flashRdData[2] & 0xffffffff) ;
	fOffset = (float)iOffset / 1000.0 ;
	m_tGrabberParam.cur_offset_ch1 = fOffset ;

	iOffset = (int)( (flashRdData[3] >> 32) & 0xffffffff ) ;
	fOffset = (float)iOffset / 1000.0 ;
	m_tGrabberParam.cur_offset_ch2 = fOffset ;

	iOffset = (int)(flashRdData[3] & 0xffffffff) ;
	fOffset = (float)iOffset / 1000.0 ;
	m_tGrabberParam.cur_offset_ch3 = fOffset ;

	m_tGrabberParam.phase_tap = (char)( (flashRdData[4] >> 56) & 0x0ff) ;

	if(m_tGrabberParam.wr_code != GRABBER_PARAM_WR_CODE)
	{
		m_tGrabberParam.cur_offset_ch0 = 0 ;
		m_tGrabberParam.cur_offset_ch1 = 0 ;
		m_tGrabberParam.cur_offset_ch2 = 0 ;
		m_tGrabberParam.cur_offset_ch3 = 0 ;
		m_tGrabberParam.phase_tap = 0 ;

		CM_SetGrabberParam(&m_tGrabberParam) ;
	}

	*pGrabberParam = m_tGrabberParam ;
	
	return true ;
}

int	CPciExpWrapper::CM_SetGrabberParamPhaseTap(char chTap)
{
	int		ret ;

	m_tGrabberParam.phase_tap = chTap ;

	if( (m_tGrabberParam.phase_tap<0) & (m_tGrabberParam.phase_tap>0x1f) )	m_tGrabberParam.phase_tap = 0 ;

	ret = CM_SaveGrabberParam() ;

	return ret ;
}
int	CPciExpWrapper::CM_SetGrabberParamCurrentOffSet(float fCh0, float fCh1, float fCh2, float fCh3)
{
	int		ret ;

	m_tGrabberParam.cur_offset_ch0 = fCh0 ;
	m_tGrabberParam.cur_offset_ch1 = fCh1 ;
	m_tGrabberParam.cur_offset_ch2 = fCh2 ;
	m_tGrabberParam.cur_offset_ch3 = fCh3 ;

	ret = CM_SaveGrabberParam() ;

	return ret ;
}
int	CPciExpWrapper::CM_GetGrabberParamPhaseTap(char *pTap)
{
	int		ret ;
	tagGRABBER_PARAM	param ;

	ret = CM_GetGrabberParam(&param) ;
	if(ret == false)	return false ;

	*pTap = m_tGrabberParam.phase_tap ;

	return ret ;
}
int	CPciExpWrapper::CM_GetGrabberParamCurrentOffSet(float *pCh0, float *pCh1, float *pCh2, float *pCh3)
{
	int		ret ;
	tagGRABBER_PARAM	param ;

	ret = CM_GetGrabberParam(&param) ;
	if(ret == false)	return false ;

	*pCh0 = m_tGrabberParam.cur_offset_ch0 ;
	*pCh1 = m_tGrabberParam.cur_offset_ch1 ;
	*pCh2 = m_tGrabberParam.cur_offset_ch2 ;
	*pCh3 = m_tGrabberParam.cur_offset_ch3 ;

	return ret ;
}
// power control and measure voltage and current
int CPciExpWrapper::CM_PowerQueueRead(int uiAddr, int *pData)
{
	int				threadID ;
	int				rxData[2] ;
	int				addr[2], data[2] ;
	int				ret ;	
	int				checkBit ;
	int				startTime ;
	int				endTime ;
	int				limitTime ;
	
	threadID = 0 ;
	CM_CheckReadDone(SRIO_BUF_NUM_PWR, threadID, &rxData[0]) ;

	addr[1] = 0 ;
	addr[0] = uiAddr ;
	data[1] = 0 ;
	data[0] = threadID ;	// 8bit thread id
	ret = gp_clsPCIExpress[0].srio_nwrite(SRIO_BUF_NUM_PWR, addr, 8, data) ;

	startTime = GetTickCount() ;
	while(1)
	{
		Sleep(SRIO_RESP_DLY) ;
		ret = CM_CheckReadDone(SRIO_BUF_NUM_PWR, threadID, &rxData[0]) ;
		checkBit = (rxData[0] & 0x80000000) ;
		if(checkBit == 0x80000000)
		{
			*pData = rxData[1] ;
			return PWR_RET_OK ;
		}
		endTime = GetTickCount() ;
		limitTime = endTime - startTime ;	
		if(limitTime > PWR_READ_TIME_LIMIT)
		{
			return PWR_RET_COM_ERR ;
		}
	}
}
int	CPciExpWrapper::CM_GetResistorValue(int iChannel, float fVoltage)
{
	int			txData ;
	float		vrVal ;
	int			rstep ;

	//if(fVoltage > CM_VLATAGE_MAX)		fVoltage = CM_VLATAGE_MAX ;
	//else if(fVoltage < CM_VLATAGE_MIN)	fVoltage = CM_VLATAGE_MIN ;
		
	vrVal = 25000.0 * (fVoltage / 0.8 - 1.0) ;
	rstep = (int)(vrVal * 256.0 / 100000.0) ;
	if(rstep >= 0xff)		rstep = 0xff ;
	else if(rstep < 0)		rstep = 0x0 ;

	if(iChannel == POWER_CH1)		txData = 0x00A60000 ;
	else if(iChannel == POWER_CH2)	txData = 0x00A60100 ;
	else if(iChannel == POWER_CH3)	txData = 0x00A00000 ;
	else if(iChannel == POWER_CH4)	txData = 0x00A00100 ;
	else if(iChannel == POWER_LED)	txData = 0x00A80000 ;
	else							txData = 0x00A60000 ;

	txData = txData | (rstep & 0x000000ff) ;

	return txData ;
}
int	CPciExpWrapper::CM_DirectGetVoltage(float *pPwr1Vol, float *pPwr2Vol, float *pPwr3Vol, float *pPwr4Vol)
{
	int			addr ;
	__int64		data ;	
	int			ret ;
	int			adcVal ;
	
	addr = ADDR_PWR_VOLTAGE1 ;
	
	ret = CM_RegisterRead(addr, &data) ;
	if(ret)		return PWR_RET_COM_ERR ;	
	
	adcVal = (data >> 48) & 0x0ffff ;
	*pPwr1Vol = VOLTAGE_PARAM * (float)adcVal ;

	adcVal = (data >> 32) & 0x0ffff ;
	*pPwr2Vol = VOLTAGE_PARAM * (float)adcVal ;
	
	adcVal = (data >> 16) & 0x0ffff ;
	*pPwr3Vol = VOLTAGE_PARAM * (float)adcVal ;

	adcVal = data & 0x0ffff ;
	*pPwr4Vol = VOLTAGE_PARAM * (float)adcVal ;
	
	return PWR_RET_OK ;	
}
int	CPciExpWrapper::CM_EnablePower(int iChannel, BOOL bEn)
{
	int		ret ;
	int		addr ;

	addr = ( (iChannel - 1) << 4 ) & 0x0f0 ;
	addr = addr | ADDR_PWR1_EN ;

	ret = CM_RegisterWrite(addr, bEn) ;
	if(ret)		return PWR_RET_COM_ERR ;	

	return PWR_RET_OK ;
}

int	CPciExpWrapper::CM_SetVoltage(int iChannel, float fVoltage)
{
	float		targetVol ;
	int			txData ;
	int			ret ;
	float		vol1, vol2, vol3, vol4 ;
	float		vol_err ;
	
	if( (iChannel < POWER_CH1) || (iChannel > POWER_CH4) )	return PWR_RET_BIT_RANGE_ERR ;
	
	if(fVoltage > CM_VLATAGE_MAX)		fVoltage = CM_VLATAGE_MAX ;
	else if(fVoltage < CM_VLATAGE_MIN)	fVoltage = CM_VLATAGE_MIN ;

	targetVol = fVoltage ;
	txData = CM_GetResistorValue(iChannel, targetVol) ;
	ret = CM_RegisterWrite(ADDR_PWR_I2C_WR, txData) ;
	if(ret)		return PWR_RET_COM_ERR ;
	Sleep(200) ;
	
	// 1. retry 1
	CM_DirectGetVoltage(&vol1, &vol2, &vol3, &vol4) ;

	if(iChannel == POWER_CH1)		vol_err = fVoltage - (vol1 / 1000.0) ;
	else if(iChannel == POWER_CH2)	vol_err = fVoltage - (vol2 / 1000.0) ;
	else if(iChannel == POWER_CH3)	vol_err = fVoltage - (vol3 / 1000.0) ;
	else if(iChannel == POWER_CH4)	vol_err = fVoltage - (vol4 / 1000.0) ;
	else							vol_err = 0 ;
	
	targetVol = targetVol + vol_err ;
	txData = CM_GetResistorValue(iChannel, targetVol) ;
	ret = CM_RegisterWrite(ADDR_PWR_I2C_WR, txData) ;
	Sleep(200) ;
	
	CM_DirectGetVoltage(&vol1, &vol2, &vol3, &vol4) ;
	if(iChannel == POWER_CH1)		vol_err = fVoltage - (vol1 / 1000.0) ;
	else if(iChannel == POWER_CH2)	vol_err = fVoltage - (vol2 / 1000.0) ;
	else if(iChannel == POWER_CH3)	vol_err = fVoltage - (vol3 / 1000.0) ;
	else if(iChannel == POWER_CH4)	vol_err = fVoltage - (vol4 / 1000.0) ;
	else							vol_err = 0 ;
	
	targetVol = targetVol + vol_err ;
	txData = CM_GetResistorValue(iChannel, targetVol) ;
	ret = CM_RegisterWrite(ADDR_PWR_I2C_WR, txData) ;
	
	Sleep(200) ;
	
	CM_DirectGetVoltage(&vol1, &vol2, &vol3, &vol4) ;

	return ret ;
	
	/*
	int			txData ;
	float		vrVal ;
	int			rstep ;
	int			lRet ;

	if(fVoltage > CM_VLATAGE_MAX)
	{
		fVoltage = CM_VLATAGE_MAX ;
	}
	else if(fVoltage < CM_VLATAGE_MIN)
	{
		fVoltage = CM_VLATAGE_MIN ;
	}
		
	vrVal = 25000.0 * (fVoltage / 0.8 - 1.0) ;
	rstep = (int)(vrVal * 256.0 / 100000.0) ;
	if(rstep >= 0xff)	rstep = 0xff ;

	if(iChannel == POWER_CH1)		txData = 0x00A60000 ;
	else if(iChannel == POWER_CH2)	txData = 0x00A60100 ;
	else if(iChannel == POWER_CH3)	txData = 0x00A00000 ;
	else if(iChannel == POWER_CH4)	txData = 0x00A00100 ;
	else if(iChannel == POWER_LED)	txData = 0x00A80000 ;
	else							txData = 0x00A60000 ;

	txData = txData | (rstep & 0x000000ff) ;
	
	lRet = CM_RegisterWrite(ADDR_PWR_I2C_WR, txData) ;

	return lRet;
	*/
}



int	CPciExpWrapper::CM_VoltageMeasurementEnable(int bEnable)
{	
	int		ret ;

	if(m_tFwVersion == FW_VESION5)
	{
		ret = CM_RegisterWrite(0x6f0, bEnable) ;
	}
	else
	{
		ret = CM_RegisterWrite(ADDR_VOLTAGE_EN, bEnable) ;
		if(ret)		return PWR_RET_COM_ERR ;
	}
	return PWR_RET_OK ;
}

int	CPciExpWrapper::CM_GetVoltage(float *pPwr1Vol, float *pPwr2Vol, float *pPwr3Vol, float *pPwr4Vol)
{
	int		vol_ch1_2 ;
	int		vol_ch3_4 ;	
	int		adcVal ;
	int		ret ;

	ret = CM_PowerQueueRead(ADDR_PWR_VOLTAGE1, &vol_ch1_2) ;
	if(ret == PWR_RET_COM_ERR)	return PWR_RET_COM_ERR ;
	
	adcVal = (vol_ch1_2 >> 16) & 0x0ffff ;
	*pPwr1Vol = VOLTAGE_PARAM * (float)adcVal ;

	adcVal = vol_ch1_2 & 0x0ffff ;
	*pPwr2Vol = VOLTAGE_PARAM * (float)adcVal ;
	
	ret = CM_PowerQueueRead(ADDR_PWR_VOLTAGE2, &vol_ch3_4) ;
	if(ret == PWR_RET_COM_ERR)	return PWR_RET_COM_ERR ;
	
	adcVal = (vol_ch3_4 >> 16) & 0x0ffff ;
	*pPwr3Vol = VOLTAGE_PARAM * (float)adcVal ;

	adcVal = vol_ch3_4 & 0x0ffff ;
	*pPwr4Vol = VOLTAGE_PARAM * (float)adcVal ;
	
	return PWR_RET_OK ;
}
int	CPciExpWrapper::CM_CurrentMeasurementEnable(int bEnable)
{	
	int		ret ;

	ret = CM_RegisterWrite(ADDR_CURRENT_EN, bEnable) ;
	if(ret)		return PWR_RET_COM_ERR ;
	
	return PWR_RET_OK ;
}
int	CPciExpWrapper::CM_GetCurrentOffSet(float *pPwr1Cur, float *pPwr2Cur, float *pPwr3Cur, float *pPwr4Cur)
{
	int		stb_cur_ch1_2 ;
	int		stb_cur_ch3_4 ;	
	int		adcVal ;
	int		ret ;

	ret = CM_PowerQueueRead(ADDR_PWR_STB_CURRENT1, &stb_cur_ch1_2) ;
	if(ret == PWR_RET_COM_ERR)	return PWR_RET_COM_ERR ;
	
	adcVal = (stb_cur_ch1_2 >> 16) & 0x0ffff ;
	*pPwr1Cur = STANDBY_CURRENT_PARAM * (float)adcVal ;

	adcVal = stb_cur_ch1_2 & 0x0ffff ;
	*pPwr2Cur = STANDBY_CURRENT_PARAM * (float)adcVal ;
	
	ret = CM_PowerQueueRead(ADDR_PWR_STB_CURRENT2, &stb_cur_ch3_4) ;
	if(ret == PWR_RET_COM_ERR)	return PWR_RET_COM_ERR ;
	
	adcVal = (stb_cur_ch3_4 >> 16) & 0x0ffff ;
	*pPwr3Cur = STANDBY_CURRENT_PARAM * (float)adcVal ;

	adcVal = stb_cur_ch3_4 & 0x0ffff ;
	*pPwr4Cur = STANDBY_CURRENT_PARAM * (float)adcVal ;
	
	return PWR_RET_OK ;
}
int	CPciExpWrapper::CM_GetStandbyCurrent(float *pPwr1Cur, float *pPwr2Cur, float *pPwr3Cur, float *pPwr4Cur)
{
	int		stb_cur_ch1_2 ;
	int		stb_cur_ch3_4 ;	
	int		adcVal ;
	int		ret ;

	ret = CM_PowerQueueRead(ADDR_PWR_STB_CURRENT1, &stb_cur_ch1_2) ;
	if(ret == PWR_RET_COM_ERR)	return PWR_RET_COM_ERR ;
	
	adcVal = (stb_cur_ch1_2 >> 16) & 0x0ffff ;
	*pPwr1Cur = (STANDBY_CURRENT_PARAM * (float)adcVal) - m_tGrabberParam.cur_offset_ch0 ;

	adcVal = stb_cur_ch1_2 & 0x0ffff ;
	*pPwr2Cur = (STANDBY_CURRENT_PARAM * (float)adcVal) - m_tGrabberParam.cur_offset_ch1 ;
	
	ret = CM_PowerQueueRead(ADDR_PWR_STB_CURRENT2, &stb_cur_ch3_4) ;
	if(ret == PWR_RET_COM_ERR)	return PWR_RET_COM_ERR ;
	
	adcVal = (stb_cur_ch3_4 >> 16) & 0x0ffff ;
	*pPwr3Cur = (STANDBY_CURRENT_PARAM * (float)adcVal) - m_tGrabberParam.cur_offset_ch2 ;

	adcVal = stb_cur_ch3_4 & 0x0ffff ;
	*pPwr4Cur = (STANDBY_CURRENT_PARAM * (float)adcVal) - m_tGrabberParam.cur_offset_ch3 ;
	
	return PWR_RET_OK ;
}

int	CPciExpWrapper::CM_GetDynamicCurrent(float *pPwr1Cur, float *pPwr2Cur, float *pPwr3Cur, float *pPwr4Cur)
{
	int		dyn_cur_ch1_2 ;
	int		dyn_cur_ch3_4 ;	
	int		adcVal ;
	int		ret ;

	ret = CM_PowerQueueRead(ADDR_PWR_DYN_CURRENT1, &dyn_cur_ch1_2) ;
	if(ret == PWR_RET_COM_ERR)	return PWR_RET_COM_ERR ;
	
	adcVal = (dyn_cur_ch1_2 >> 16) & 0x0ffff ;
	*pPwr1Cur = (DYNAMIC_CURRENT_PARAM * (float)adcVal) - (m_tGrabberParam.cur_offset_ch0 * 0.001) ;

	adcVal = dyn_cur_ch1_2 & 0x0ffff ;
	*pPwr2Cur = (DYNAMIC_CURRENT_PARAM * (float)adcVal) - (m_tGrabberParam.cur_offset_ch1 * 0.001) ;
	
	ret = CM_PowerQueueRead(ADDR_PWR_DYN_CURRENT2, &dyn_cur_ch3_4) ;
	if(ret == PWR_RET_COM_ERR)	return PWR_RET_COM_ERR ;
	
	adcVal = (dyn_cur_ch3_4 >> 16) & 0x0ffff ;
	*pPwr3Cur = (DYNAMIC_CURRENT_PARAM * (float)adcVal) - (m_tGrabberParam.cur_offset_ch2 * 0.001) ;

	adcVal = dyn_cur_ch3_4 & 0x0ffff ;
	*pPwr4Cur = (DYNAMIC_CURRENT_PARAM * (float)adcVal) - (m_tGrabberParam.cur_offset_ch3 * 0.001) ;
	
	return PWR_RET_OK ;

}
int	CPciExpWrapper::CM_FlashPowerMeasurementEnable(int bEnable)
{	
	int		ret ;

	ret = CM_RegisterWrite(ADDR_FLASH_PWR_EN, bEnable) ;
	if(ret)		return PWR_RET_COM_ERR ;
	
	return PWR_RET_OK ;
}
int	CPciExpWrapper::CM_GetFlashPower(float *pFlashVol, float *pFlashCur)
{
	int		flash_pwr ;
	int		adcVal ;
	int		ret ;

	ret = CM_PowerQueueRead(ADDR_FLASH_PWR, &flash_pwr) ;
	if(ret == PWR_RET_COM_ERR)	return PWR_RET_COM_ERR ;
	
	adcVal = (flash_pwr >> 16) & 0x0ffff ;
	*pFlashVol = VOLTAGE_PARAM * (float)adcVal ;

	adcVal = flash_pwr & 0x0ffff ;
	*pFlashCur = FLASH_CURRENT_PARAM * (float)adcVal ;
	
	return PWR_RET_OK ;
}
// Gpio control
int CPciExpWrapper::CM_GpioQueueRead(int uiAddr)
{
	int				threadID ;
	int				rxData[2] ;
	int				addr[2], data[2] ;
	int				ret ;	
	int				checkBit ;
	int				startTime ;
	int				endTime ;
	int				limitTime ;
	
	threadID = 1 ;
	CM_CheckReadDone(SRIO_BUF_NUM_GPIO, threadID, &rxData[0]) ;

	addr[1] = 0 ;
	addr[0] = uiAddr ;
	data[1] = 0 ;
	data[0] = threadID ;	// 8bit thread id
	ret = gp_clsPCIExpress[0].srio_nwrite(SRIO_BUF_NUM_GPIO, addr, 8, data) ;

	startTime = GetTickCount() ;
	while(1)
	{
		Sleep(SRIO_RESP_DLY) ;
		ret = CM_CheckReadDone(SRIO_BUF_NUM_GPIO, threadID, &rxData[0]) ;
		checkBit = (rxData[0] & 0x80000000) ;
		if(checkBit == 0x80000000)
		{
			return rxData[1] & 0xff ;
		}
		endTime = GetTickCount() ;
		limitTime = endTime - startTime ;	
		if(limitTime > PWR_READ_TIME_LIMIT)
		{
			return 0xFFFFFFFF ;
		}
	}
}
int	CPciExpWrapper::CM_GetGpio1P8Dir(void)
{	
	int			addr ;
	__int64		data ;	
	int			ret ;
	int			dir ;
	
	addr = ADDR_GPIO1P8_DIR ;
	
	ret = CM_RegisterRead(addr, &data) ;
	if(ret)		return GPIO_RET_COM_ERR ;	
	
	dir = (int)data & 0x3f ;
	
	return dir ;
}
int	CPciExpWrapper::CM_SetGpio1P8Dir(int uiGpioBit, int bDir)
{
	int			addr ;
	__int64		data ;
	int			ret ;
	
	if( (uiGpioBit < GPIO_1P8_PORT13) || (uiGpioBit > GPIO_1P8_PORT27) )	return GPIO_RET_BIT_RANGE_ERR ;
	
	addr = ADDR_GPIO1P8_DIR | (uiGpioBit << 12) ;	
	data = bDir & 0x01 ;

	ret = CM_RegisterWrite(addr, data) ;
	if(ret)		return GPIO_RET_COM_ERR ;	
	
	return GPIO_RET_OK ;
}
int	CPciExpWrapper::CM_DirectGetGpio1P8(int uiGpioBit)
{
	int			addr ;
	__int64		data ;	
	int			ret ;
	tagGPIO_REG	gpio ;
	
	if( (uiGpioBit < GPIO_1P8_PORT13) || (uiGpioBit > GPIO_1P8_PORT27) )	return GPIO_RET_BIT_RANGE_ERR ;
	
	addr = ADDR_GPIO1P8_RD ;
	
	ret = CM_RegisterRead(addr, &data) ;
	if(ret)		return GPIO_RET_COM_ERR ;	
	
	gpio.all = (unsigned short)data & 0x3f ;
	
	if(uiGpioBit == GPIO_1P8_PORT13)		return gpio.bit.gpio00 ;
	else if(uiGpioBit == GPIO_1P8_PORT15)	return gpio.bit.gpio01 ;
	else if(uiGpioBit == GPIO_1P8_PORT19)	return gpio.bit.gpio02 ;
	else if(uiGpioBit == GPIO_1P8_PORT21)	return gpio.bit.gpio03 ;
	else if(uiGpioBit == GPIO_1P8_PORT25)	return gpio.bit.gpio04 ;
	else if(uiGpioBit == GPIO_1P8_PORT27)	return gpio.bit.gpio05 ;
	else									return GPIO_RET_BIT_RANGE_ERR ;
}
int	CPciExpWrapper::CM_SetGpio1P8(int uiGpioBit, int bHigh)
{
	int			addr ;
	__int64		data ;
	int			ret ;
	
	if( (uiGpioBit < GPIO_1P8_PORT13) || (uiGpioBit > GPIO_1P8_PORT27) )	return GPIO_RET_BIT_RANGE_ERR ;
	
	addr = ADDR_GPIO1P8_WR | (uiGpioBit << 12) ;	
	data = bHigh & 0x01 ;

	ret = CM_RegisterWrite(addr, data) ;
	if(ret)		return GPIO_RET_COM_ERR ;

	return GPIO_RET_OK ;
}
int CPciExpWrapper::CM_GetGpio1P8(int uiGpioBit)
{
	int		rxData ;
	tagGPIO_REG	gpio ;
	
	if( (uiGpioBit < GPIO_1P8_PORT13) || (uiGpioBit > GPIO_1P8_PORT27) )	return GPIO_RET_BIT_RANGE_ERR ;
	
	rxData = CM_GpioQueueRead(ADDR_GPIO1P8_RD) ;
	if(rxData == 0xffffffff)	return GPIO_RET_COM_ERR ;
	
	gpio.all = (unsigned short)rxData & 0x3f ;
	
	if(uiGpioBit == GPIO_1P8_PORT13)		return gpio.bit.gpio00 ;
	else if(uiGpioBit == GPIO_1P8_PORT15)	return gpio.bit.gpio01 ;
	else if(uiGpioBit == GPIO_1P8_PORT19)	return gpio.bit.gpio02 ;
	else if(uiGpioBit == GPIO_1P8_PORT21)	return gpio.bit.gpio03 ;
	else if(uiGpioBit == GPIO_1P8_PORT25)	return gpio.bit.gpio04 ;
	else if(uiGpioBit == GPIO_1P8_PORT27)	return gpio.bit.gpio05 ;
	else									return GPIO_RET_BIT_RANGE_ERR ;
}
int	CPciExpWrapper::CM_GetGpio3P3Dir(void)
{	
	int			addr ;
	__int64		data ;	
	int			ret ;
	int			dir ;
	
	addr = ADDR_GPIO3P3_DIR ;
	
	ret = CM_RegisterRead(addr, &data) ;
	if(ret)		return GPIO_RET_COM_ERR ;	
	
	dir = (int)data & 0x03 ;
	
	return dir ;
}
int	CPciExpWrapper::CM_SetGpio3P3Dir(int uiGpioBit, int bDir)
{
	int			addr ;
	__int64		data ;
	int			ret ;
	
	if( (uiGpioBit < GPIO_3P3_PORT31) || (uiGpioBit > GPIO_3P3_PORT33) )	return GPIO_RET_BIT_RANGE_ERR ;
	
	addr = ADDR_GPIO3P3_DIR | (uiGpioBit << 12) ;	
	data = bDir & 0x01 ;

	ret = CM_RegisterWrite(addr, data) ;
	if(ret)		return GPIO_RET_COM_ERR ;	
	
	return GPIO_RET_OK ;
}
int	CPciExpWrapper::CM_DirectGetGpio3P3(int uiGpioBit)
{
	int			addr ;
	__int64		data ;	
	int			ret ;
	tagGPIO_REG	gpio ;
	
	if( (uiGpioBit < GPIO_3P3_PORT31) || (uiGpioBit > GPIO_3P3_PORT33) )	return GPIO_RET_BIT_RANGE_ERR ;
	
	addr = ADDR_GPIO3P3_RD ;
	
	ret = CM_RegisterRead(addr, &data) ;
	if(ret)		return GPIO_RET_COM_ERR ;	
	
	gpio.all = (unsigned short)data & 0x3f ;
	
	if(uiGpioBit == GPIO_3P3_PORT31)		return gpio.bit.gpio00 ;
	else if(uiGpioBit == GPIO_3P3_PORT33)	return gpio.bit.gpio01 ;
	else									return GPIO_RET_BIT_RANGE_ERR ;
}
int	CPciExpWrapper::CM_SetGpio3P3(int uiGpioBit, int bHigh)
{
	int			addr ;
	__int64		data ;
	int			ret ;
	
	if( (uiGpioBit < GPIO_3P3_PORT31) || (uiGpioBit > GPIO_3P3_PORT33) )	return GPIO_RET_BIT_RANGE_ERR ;
	
	addr = ADDR_GPIO3P3_WR | (uiGpioBit << 12) ;	
	data = bHigh & 0x01 ;

	ret = CM_RegisterWrite(addr, data) ;
	if(ret)		return GPIO_RET_COM_ERR ;

	return GPIO_RET_OK ;
}
int CPciExpWrapper::CM_GetGpio3P3(int uiGpioBit)
{
	int		rxData ;
	tagGPIO_REG	gpio ;
	
	if( (uiGpioBit < GPIO_3P3_PORT31) || (uiGpioBit > GPIO_3P3_PORT33) )	return GPIO_RET_BIT_RANGE_ERR ;
	
	rxData = CM_GpioQueueRead(ADDR_GPIO3P3_RD) ;
	if(rxData == 0xffffffff)	return GPIO_RET_COM_ERR ;
	
	gpio.all = (unsigned short)rxData & 0x03 ;
	
	if(uiGpioBit == GPIO_3P3_PORT31)		return gpio.bit.gpio00 ;
	else if(uiGpioBit == GPIO_3P3_PORT33)	return gpio.bit.gpio01 ;
	else									return GPIO_RET_BIT_RANGE_ERR ;
}
int	CPciExpWrapper::CM_GetExtGpio3P3Dir(void)
{	
	int			addr ;
	__int64		data ;	
	int			ret ;
	int			dir ;
	
	addr = ADDR_EXT_GPIO3P3_DIR ;
	
	ret = CM_RegisterRead(addr, &data) ;
	if(ret)		return GPIO_RET_COM_ERR ;	
	
	dir = (int)data & 0x3FF ;
	
	return dir ;
}
int	CPciExpWrapper::CM_SetExtGpio3P3Dir(int uiGpioBit, int bDir)
{
	int			addr ;
	__int64		data ;
	int			ret ;
	
	if( (uiGpioBit < EXT_GPIO_3P3_PORT1) || (uiGpioBit > EXT_GPIO_3P3_PORT10) )	return GPIO_RET_BIT_RANGE_ERR ;
	
	addr = ADDR_EXT_GPIO3P3_DIR | (uiGpioBit << 12) ;	
	data = bDir & 0x01 ;

	ret = CM_RegisterWrite(addr, data) ;
	if(ret)		return GPIO_RET_COM_ERR ;	
	
	return GPIO_RET_OK ;
}
int	CPciExpWrapper::CM_DirectGetExtGpio3P3(int uiGpioBit)
{
	int			addr ;
	__int64		data ;	
	int			ret ;
	tagGPIO_REG	gpio ;
	
	if( (uiGpioBit < EXT_GPIO_3P3_PORT1) || (uiGpioBit > EXT_GPIO_3P3_PORT10) )	return GPIO_RET_BIT_RANGE_ERR ;
	
	addr = ADDR_EXT_GPIO3P3_RD ;
	
	ret = CM_RegisterRead(addr, &data) ;
	if(ret)		return GPIO_RET_COM_ERR ;	
	
	gpio.all = (unsigned short)data & 0x3f ;
	
	if(uiGpioBit == EXT_GPIO_3P3_PORT1)			return gpio.bit.gpio00 ;
	else if(uiGpioBit == EXT_GPIO_3P3_PORT2)	return gpio.bit.gpio01 ;
	else if(uiGpioBit == EXT_GPIO_3P3_PORT3)	return gpio.bit.gpio02 ;
	else if(uiGpioBit == EXT_GPIO_3P3_PORT4)	return gpio.bit.gpio03 ;
	else if(uiGpioBit == EXT_GPIO_3P3_PORT5)	return gpio.bit.gpio04 ;
	else if(uiGpioBit == EXT_GPIO_3P3_PORT6)	return gpio.bit.gpio05 ;
	else if(uiGpioBit == EXT_GPIO_3P3_PORT7)	return gpio.bit.gpio06 ;
	else if(uiGpioBit == EXT_GPIO_3P3_PORT8)	return gpio.bit.gpio07 ;
	else if(uiGpioBit == EXT_GPIO_3P3_PORT9)	return gpio.bit.gpio08 ;
	else if(uiGpioBit == EXT_GPIO_3P3_PORT10)	return gpio.bit.gpio09 ;
	else										return GPIO_RET_BIT_RANGE_ERR ;
}
int	CPciExpWrapper::CM_SetExtGpio3P3(int uiGpioBit, int bHigh)
{
	int			addr ;
	__int64		data ;
	int			ret ;
	
	if( (uiGpioBit < EXT_GPIO_3P3_PORT1) || (uiGpioBit > EXT_GPIO_3P3_PORT10) )	return GPIO_RET_BIT_RANGE_ERR ;
	
	addr = ADDR_EXT_GPIO3P3_WR | (uiGpioBit << 12) ;	
	data = bHigh & 0x01 ;

	ret = CM_RegisterWrite(addr, data) ;
	if(ret)		return GPIO_RET_COM_ERR ;

	return GPIO_RET_OK ;
}
int CPciExpWrapper::CM_GetExtGpio3P3(int uiGpioBit)
{
	int		rxData ;
	tagGPIO_REG	gpio ;
	
	if( (uiGpioBit < EXT_GPIO_3P3_PORT1) || (uiGpioBit > EXT_GPIO_3P3_PORT10) )	return GPIO_RET_BIT_RANGE_ERR ;
	
	rxData = CM_GpioQueueRead(ADDR_EXT_GPIO3P3_RD) ;
	if(rxData == 0xffffffff)	return GPIO_RET_COM_ERR ;
	
	gpio.all = (unsigned short)rxData & 0x03FF ;
	
	if(uiGpioBit == EXT_GPIO_3P3_PORT1)			return gpio.bit.gpio00 ;
	else if(uiGpioBit == EXT_GPIO_3P3_PORT2)	return gpio.bit.gpio01 ;
	else if(uiGpioBit == EXT_GPIO_3P3_PORT3)	return gpio.bit.gpio02 ;
	else if(uiGpioBit == EXT_GPIO_3P3_PORT4)	return gpio.bit.gpio03 ;
	else if(uiGpioBit == EXT_GPIO_3P3_PORT5)	return gpio.bit.gpio04 ;
	else if(uiGpioBit == EXT_GPIO_3P3_PORT6)	return gpio.bit.gpio05 ;
	else if(uiGpioBit == EXT_GPIO_3P3_PORT7)	return gpio.bit.gpio06 ;
	else if(uiGpioBit == EXT_GPIO_3P3_PORT8)	return gpio.bit.gpio07 ;
	else if(uiGpioBit == EXT_GPIO_3P3_PORT9)	return gpio.bit.gpio08 ;
	else if(uiGpioBit == EXT_GPIO_3P3_PORT10)	return gpio.bit.gpio09 ;
	else										return GPIO_RET_BIT_RANGE_ERR ;
}
// clock control : main clk, aux clk, i2c clk
int	CPciExpWrapper::CM_SetMclk(int bOn, float fFreq)
{
	int				ret ;
	tagCLK_GEN		clkGen ;
	double			ls_div ;
	double			hs_div ;
	double			multiplier ;
	__int64			reg0, reg5, reg6, reg7, reg8, reg9, reg10, reg11, reg132 ;

	ret = CM_RegisterWrite(ADDR_CLK_EN, bOn) ;
	if(ret) return CLK_RET_COM_ERR ;

	// 1. Calculate LS_DIV
	ls_div = Fvco_MIN / (fFreq * HS_DIV_MAX) ;
	if(ls_div <= 1)
	{
		ls_div = 1.0 ;
		clkGen.LS_DIV = 0 ;
	}
	else if( (ls_div > 1) && (ls_div <= 2) )
	{
		ls_div = 2.0 ;
		clkGen.LS_DIV = 1 ;
	}
	else if( (ls_div > 2) && (ls_div <= 4) )
	{
		ls_div = 4.0 ;
		clkGen.LS_DIV = 2 ;
	}
	else if( (ls_div > 4) && (ls_div <= 8) )
	{
		ls_div = 8.0 ;
		clkGen.LS_DIV = 3 ;
	}
	else if( (ls_div > 8) && (ls_div <= 16) )
	{
		ls_div = 16.0 ;
		clkGen.LS_DIV = 4 ;
	}
	else if( (ls_div > 16) && (ls_div <= 32) )
	{
		ls_div = 32.0 ;
		clkGen.LS_DIV = 5 ;
	}
	else
	{
		ls_div = 32.0 ;
		clkGen.LS_DIV = 5 ;
	}
	// 2. Calculate HS_DIV
	hs_div = Fvco_MIN / (fFreq * ls_div) ;
	
	if(hs_div < 8)			hs_div = 8 ;
	else if(hs_div > 1020)	hs_div = 1020 ;
	
	if( ( (int)hs_div % 2) == 0)	clkGen.HS_DIV = (int)hs_div + 2 ;
	else							clkGen.HS_DIV = (int)hs_div + 1 ;
	
	hs_div = clkGen.HS_DIV ;
	// 3. Calculate M, M_Int, M_Frac
	multiplier = ls_div * hs_div * fFreq / Fxo ;
	clkGen.M_Int = (int)multiplier ;
	clkGen.M_Frac = (multiplier - (double)clkGen.M_Int) * FRAC_VAL ;
	if( (multiplier > 65.040650407) && (multiplier <= 65.259980246) )
	{
		clkGen.LP1 = 2 ;
		clkGen.LP2 = 2 ;
	}
	else if( (multiplier > 65.259980246) && (multiplier <= 67.859763463) )
	{
		clkGen.LP1 = 2 ;
		clkGen.LP2 = 3 ;
	}
	else if( (multiplier > 67.859763463) && (multiplier <= 72.937624981) )
	{
		clkGen.LP1 = 3 ;
		clkGen.LP2 = 3 ;
	}
	else if( (multiplier > 72.937624981) && (multiplier <= 75.843265046) )
	{
		clkGen.LP1 = 3 ;
		clkGen.LP2 = 4 ;
	}
	else if( (multiplier > 75.843265046) && (multiplier <= 78.173858662) )
	{
		clkGen.LP1 = 4 ;
		clkGen.LP2 = 4 ;
	}
	
	reg132	= 0x00aa8400 ;	// clk off
	reg0	= 0x00aa0000 |  ( (clkGen.LP2 << 4) & 0xF0) | (clkGen.LP1 & 0x0F) ;
	reg5	= 0x00aa0500 | (clkGen.M_Frac & 0x0ff) ;
	reg6	= 0x00aa0600 | ( (clkGen.M_Frac >> 8) & 0x0ff) ;
	reg7	= 0x00aa0700 | ( (clkGen.M_Frac >> 16) & 0x0ff) ;
	reg8	= 0x00aa0800 | ( (clkGen.M_Frac >> 24) & 0x01f) | ( (clkGen.M_Int << 5) & 0xE0) ;
	reg9	= 0x00aa0900 | ( (clkGen.M_Int >> 3) & 0x3F) ;
	reg10	= 0x00aa0a00 | (clkGen.HS_DIV & 0xFF) ;
	reg11	= 0x00aa0b00 | ( (clkGen.HS_DIV >>8) & 0x03) | ( (clkGen.LS_DIV << 4) & 0x70) ;

	ret = CM_RegisterWrite(ADDR_CLK_I2C_WR, reg132) ;
	if(ret) return CLK_RET_COM_ERR ;
	Sleep(10) ;		
	ret = CM_RegisterWrite(ADDR_CLK_I2C_WR, reg0) ;
	if(ret) return CLK_RET_COM_ERR ;
	Sleep(10) ;	
	ret = CM_RegisterWrite(ADDR_CLK_I2C_WR, reg5) ;
	if(ret) return CLK_RET_COM_ERR ;
	Sleep(10) ;	
	ret = CM_RegisterWrite(ADDR_CLK_I2C_WR, reg6) ;
	if(ret) return CLK_RET_COM_ERR ;
	Sleep(10) ;	
	ret = CM_RegisterWrite(ADDR_CLK_I2C_WR, reg7) ;
	if(ret) return CLK_RET_COM_ERR ;
	Sleep(10) ;	
	ret = CM_RegisterWrite(ADDR_CLK_I2C_WR, reg8) ;
	if(ret) return CLK_RET_COM_ERR ;
	Sleep(10) ;	
	ret = CM_RegisterWrite(ADDR_CLK_I2C_WR, reg9) ;
	if(ret) return CLK_RET_COM_ERR ;
	Sleep(10) ;	
	ret = CM_RegisterWrite(ADDR_CLK_I2C_WR, reg10) ;
	if(ret) return CLK_RET_COM_ERR ;
	Sleep(10) ;	
	ret = CM_RegisterWrite(ADDR_CLK_I2C_WR, reg11) ;
	if(ret) return CLK_RET_COM_ERR ;
	Sleep(100) ;	

	reg132	= 0x00aa8400 | 0x01 ;	// Freq Cal Set
	ret = CM_RegisterWrite(ADDR_CLK_I2C_WR, reg132) ;
	if(ret) return CLK_RET_COM_ERR ;
	Sleep(100) ;

	reg132	= 0x00aa8400 | 0x04 ;	// enable clk
	ret = CM_RegisterWrite(ADDR_CLK_I2C_WR, reg132) ;
	if(ret) return CLK_RET_COM_ERR ;
	Sleep(100) ;

	return CLK_RET_OK ;
}
int CPciExpWrapper::CM_SetAuxClk(int bOn, int uiFreq)
{
	int		ret ;
	int			addr ;
	__int64		data ;
	int		wrFreq;

	if(bOn)
	{
		CM_SetGpio1P8Dir(GPIO_1P8_PORT27, 0) ;	// output set
		// set aux clk
		addr = ADDR_GPIO_ALT_FUNC | (0 << 12) ;
		data = 1 ;
		
		ret = CM_RegisterWrite(addr, data) ;
		if(ret)		return CLK_RET_COM_ERR ;
		// set freq 
		wrFreq = (uiFreq == 8) ? 1 : (uiFreq == 9) ? 2 : (uiFreq == 10) ? 4 : 0 ;
		data = 0x80 | wrFreq ;
		
		ret = CM_RegisterWrite(ADDR_AUX_CLK_CTRL, data) ;
		if(ret)		return CLK_RET_COM_ERR ;
		
		return CLK_RET_OK ;
	}
	else
	{
		// set gpio
		addr = ADDR_GPIO_ALT_FUNC | (0 << 12) ;
		data = 0 ;
		
		ret = CM_RegisterWrite(addr, data) ;
		if(ret)		return CLK_RET_COM_ERR ;
		// disable aux clk
		data = 0 ;
		ret = CM_RegisterWrite(ADDR_AUX_CLK_CTRL, data) ;
		if(ret)		return CLK_RET_COM_ERR ;
		
		return CLK_RET_OK ;
	}
}
int	CPciExpWrapper::CM_I2CSetClk(int iClk)
{
	int		ret ;
	int		clkRef ;

	// BIT_CLK_REF = ( CLK / (BITGEN_CLK_OUT * 4 * 2) ) - 1 ;
	clkRef = 25000 / (iClk * 4 * 2) - 1 ;

	ret = CM_RegisterWrite(ADDR_IMG_I2C_CLK_REF, clkRef) ;
	if(ret)		return CLK_RET_COM_ERR ;
	
	return CLK_RET_OK ;
}
// 이전 버전 호환 함수
int	CPciExpWrapper::CM_SetGpio(int iIoNum, int bHigh)
{
	int		ret ;
	int		addr ;
	if(m_tFwVersion == FW_VESION5)
	{
		addr = ( (iIoNum - 1) << 4 ) & 0x0f0 ;
		addr = addr | 0x300 ;

		ret = CM_RegisterWrite(addr, bHigh) ;
	}
	else
	{
		ret = CM_SetGpio1P8(iIoNum, bHigh) ;
	}
	
	return ret ;
}
int CPciExpWrapper::CM_GetGpio31(void)
{
	int		ret ;
	int		rxData ;

	if(m_tFwVersion == FW_VESION5)
	{
		rxData = CM_GpioQueueRead(0x360) ;
		if(rxData == 0xffffffff)	return GPIO_RET_COM_ERR ;
	
		ret = (unsigned short)rxData & 0x01 ;
	}
	else
	{
		ret = CM_GetGpio3P3(GPIO_3P3_PORT31) ;
	}
	return ret ;
}
int CPciExpWrapper::CM_GetGpio33(void)
{
	int		ret ;
	int		rxData ;

	if(m_tFwVersion == FW_VESION5)
	{
		rxData = CM_GpioQueueRead(0x370) ;
		if(rxData == 0xffffffff)	return GPIO_RET_COM_ERR ;
	
		ret = (unsigned short)rxData & 0x01 ;
	}
	else
	{	
		ret = CM_GetGpio3P3(GPIO_3P3_PORT33) ;
	}
	return ret ;
}
int CPciExpWrapper::CM_SocketOpen(void)
{
	int ret ;

	if(m_tFwVersion == FW_VESION5)
	{
		ret = CM_GetGpio33() ;
	}
	else
	{	
		ret = CM_GetGpio3P3(GPIO_3P3_PORT33) ;
	}
	return ret ;
}
int CPciExpWrapper::CM_SocketBoardConnetion(void)
{
	int ret ;
	if(m_tFwVersion == FW_VESION5)
	{
		ret = CM_GetGpio31() ;
	}
	else
	{	
		ret = CM_GetGpio3P3(GPIO_3P3_PORT31) ;
	}

	return ret ;
}
int CPciExpWrapper::CM_SetGpioClk(int bOn, int nFreq)
{
	int		ret ;	

	if(m_tFwVersion == FW_VESION5)
	{
		int		ret ;
		int		addr[2], data[2] ;
		int		wrFreq;

		wrFreq =	(nFreq == 8) ? 1 :
					(nFreq == 9) ? 2 :
					(nFreq == 10) ? 4 :0 ;

		addr[1] = 0 ;
		addr[0] = 0x380 ;
		data[1] = 0 ;
		data[0] = ( (bOn << 15) & 0x8000) | (wrFreq & 0x07) ;	

		ret = gp_clsPCIExpress[0].srio_nwrite(2, addr, 8, data) ;

		return ret ;
	}
	ret = CM_SetAuxClk(bOn, nFreq) ;

	return ret ;
}
//IMG infomation
int CPciExpWrapper::CM_ImgInfoEnable(void)
{
	int			ret ;
	int			addr ;
	__int64		data ;

	CM_SetExtGpio3P3Dir(EXT_GPIO_3P3_PORT1, 1) ;	// input set
	CM_SetExtGpio3P3Dir(EXT_GPIO_3P3_PORT3, 1) ;	// input set
	// set enc
	addr = ADDR_GPIO_ALT_FUNC | (1 << 12) ;
	data = 1 ;
		
	ret = CM_RegisterWrite(addr, data) ;
	if(ret)		return IMG_INFO_RET_COM_ERR ;	

	ret = CM_RegisterWrite(ADDR_SEND_INFO, 0x01) ;	// 0->not send, 1-> info. send
	if(ret)		return IMG_INFO_RET_COM_ERR ;	
	ret = CM_RegisterWrite(ADDR_ENC_CTRL, 0x01) ;	// enc enable
	if(ret)		return IMG_INFO_RET_COM_ERR ;	

	m_bRevInfo = true ;	
	
	m_iframe_cnt = 0 ;

	return IMG_INFO_DATA_OK ;
}
int CPciExpWrapper::CM_ImgInfoDisable(void)
{
	int			ret ;
	int			addr ;
	__int64		data ;

	// set enc
	addr = ADDR_GPIO_ALT_FUNC | (1 << 12) ;
	data = 0 ;
		
	ret = CM_RegisterWrite(addr, data) ;
	if(ret)		return IMG_INFO_RET_COM_ERR ;		
		
	ret = CM_RegisterWrite(ADDR_SEND_INFO, 0x00) ;	// 0->not send, 1-> info. send
	if(ret)		return IMG_INFO_RET_COM_ERR ;	
	ret = CM_RegisterWrite(ADDR_ENC_CTRL, 0x00) ;	// enc disable
	if(ret)		return IMG_INFO_RET_COM_ERR ;	
	m_bRevInfo = false ;

	return IMG_INFO_DATA_OK ;
}
int CPciExpWrapper::CM_CopyImgInfo(int nIndexNum)
{
	int				ret ;
	int				infoSize ;
	int				width ;
	unsigned char	*buf ;
	int				offset ;

	if(m_tFwVersion == FW_VESION5)
	{
		return IMG_INFO_DATA_OK ;
	}
	if(m_bRevInfo == true)
	{
		buf = NULL ;
		infoSize = sizeof(tagIMG_INFO) ;

		if(m_iOutFormat == OUT_FORMAT_RAW8)
		{
			offset = (m_iWidth * m_iHeight) / 1 ;
		}
		else if(m_iOutFormat == OUT_FORMAT_12BIT)
		{
			if (m_iPixelPer2byte)
				offset = (m_iWidth * m_iHeight) * 2*2 ;
			else
				offset = (m_iWidth * m_iHeight) * 2 ;
		}
		else
		{
			offset = (m_iRaw10Width * m_iHeight) / 1 ;
		}	

		if (m_iInterlace) offset *=2;
		
		ret = gp_clsPCIExpress[0].PhyMemCopy((int**)&buf, nIndexNum - 1, offset, infoSize) ;

		memcpy(&m_tImgInfo, buf, infoSize) ;

		return IMG_INFO_DATA_OK ;
	}
	return IMG_INFO_DISABLE ;
}
int	CPciExpWrapper::CM_InfoIsValidFrame(void)
{
#define FRAME_CODE_HIGH		0x50524920
#define FRAME_CODE_LOW		0x494d4700

	int		valid ;
	short int *imgInfo;
	imgInfo = (short int *) &m_tImgInfo;
	if(m_tFwVersion == FW_VESION5)
	{
		return IMG_INFO_DATA_OK ;
	}

	if(m_bRevInfo == true)
	{
		valid = IMG_INFO_DATA_OK ;
		if(m_tImgInfo.validCodeH != FRAME_CODE_HIGH)	valid = valid | FRAME_CODE_HIGH_ERR ;
		if(m_tImgInfo.validCodeL != FRAME_CODE_LOW)		valid = valid | FRAME_CODE_LOW_ERR ;
		//if(m_tImgInfo.frame_cnt <= m_iframe_cnt)		valid = valid | FRAME_COUNT_ERR ;
		if(m_tImgInfo.line_cnt != m_iline_cnt)			valid = valid | FRAME_LINE_COUNT_ERR ;				

		if(m_tImgInfo.frm_valid_check == 0 )			valid = valid | FRAME_PIXEL_COUNT_ERR;			// by SJ 150828

		if(valid == IMG_INFO_DATA_OK)					m_iframe_cnt = m_tImgInfo.frame_cnt ;

		return valid ;
	}
	return IMG_INFO_DISABLE ;
}
int	CPciExpWrapper::CM_InfoGetFrameCnt(int *pFrameCount)
{
	if(m_bRevInfo == true)
	{
		*pFrameCount = m_tImgInfo.frame_cnt ;
		return IMG_INFO_DATA_OK ;
	}
	return IMG_INFO_DISABLE ;
}
int	CPciExpWrapper::CM_InfoGetLineCnt(int *pLineCount)
{
	if(m_bRevInfo == true)
	{
		*pLineCount = m_tImgInfo.line_cnt ;
		return IMG_INFO_DATA_OK ;
	}
	return IMG_INFO_DISABLE ;
}

int	CPciExpWrapper::CM_InfoGetVolage(float *pPwr1Vol, float *pPwr2Vol, float *pPwr3Vol, float *pPwr4Vol)
{
	double	tmp ;

	if(m_bRevInfo == true)
	{
		tmp = (double)( (m_tImgInfo.vol_ch1_2 >> 16) & 0x0ffff) ;
		*pPwr1Vol = (float)(VOLTAGE_PARAM * tmp) ;

		tmp = (double)(m_tImgInfo.vol_ch1_2 & 0x0ffff) ;
		*pPwr2Vol = (float)(VOLTAGE_PARAM * tmp) ;

		tmp = (double)( (m_tImgInfo.vol_ch3_4 >> 16) & 0x0ffff) ;
		*pPwr3Vol = (float)(VOLTAGE_PARAM * tmp) ;

		tmp = (double)(m_tImgInfo.vol_ch3_4 & 0x0ffff) ;
		*pPwr4Vol = (float)(VOLTAGE_PARAM * tmp) ;
		return IMG_INFO_DATA_OK ;
	}
	return IMG_INFO_DISABLE ;
}
int	CPciExpWrapper::CM_InfoGetStandbyCurrent(float *pPwr1Cur, float *pPwr2Cur, float *pPwr3Cur, float *pPwr4Cur)
{
	double	tmp ;

	if(m_bRevInfo == true)
	{
		tmp = (double)( (m_tImgInfo.stb_cur_ch1_2 >> 16) & 0x0ffff) ;
		*pPwr1Cur = (float)(STANDBY_CURRENT_PARAM * tmp) ;

		tmp = (double)(m_tImgInfo.stb_cur_ch1_2 & 0x0ffff) ;
		*pPwr2Cur = (float)(STANDBY_CURRENT_PARAM * tmp) ;

		tmp = (double)( (m_tImgInfo.stb_cur_ch3_4 >> 16) & 0x0ffff) ;
		*pPwr3Cur = (float)(STANDBY_CURRENT_PARAM * tmp) ;

		tmp = (double)(m_tImgInfo.stb_cur_ch3_4 & 0x0ffff) ;
		*pPwr4Cur = (float)(STANDBY_CURRENT_PARAM * tmp) ;
		return IMG_INFO_DATA_OK ;
	}
	return IMG_INFO_DISABLE ;
}
int	CPciExpWrapper::CM_InfoGetDynamicCurrent(float *pPwr1Cur, float *pPwr2Cur, float *pPwr3Cur, float *pPwr4Cur)
{
	double	tmp ;

	if(m_bRevInfo == true)
	{
		tmp = (double)( (m_tImgInfo.dyn_cur_ch1_2 >> 16) & 0x0ffff) ;
		*pPwr1Cur = (float)(DYNAMIC_CURRENT_PARAM * tmp) ;

		tmp = (double)(m_tImgInfo.dyn_cur_ch1_2 & 0x0ffff) ;
		*pPwr2Cur = (float)(DYNAMIC_CURRENT_PARAM * tmp) ;

		tmp = (double)( (m_tImgInfo.dyn_cur_ch3_4 >> 16) & 0x0ffff) ;
		*pPwr3Cur = (float)(DYNAMIC_CURRENT_PARAM * tmp) ;

		tmp = (double)(m_tImgInfo.dyn_cur_ch3_4 & 0x0ffff) ;
		*pPwr4Cur = (float)(DYNAMIC_CURRENT_PARAM * tmp) ;
		return IMG_INFO_DATA_OK ;
	}
	return IMG_INFO_DISABLE ;
}
int	CPciExpWrapper::CM_InfoGetFlashPower(float *pVol, float *pCur)
{
	double	tmp ;

	if(m_bRevInfo == true)
	{
		tmp = (double)( (m_tImgInfo.flash_pwr >> 16) & 0x0ffff) ;
		*pVol = (float)(VOLTAGE_PARAM * tmp) ;

		tmp = (double)(m_tImgInfo.flash_pwr & 0x0ffff) ;
		*pCur = (float)(FLASH_CURRENT_PARAM * tmp) ;
		
		return IMG_INFO_DATA_OK ;
	}
	return IMG_INFO_DISABLE ;
}
int	CPciExpWrapper::CM_InfoGetEncStatus(int *pEncStatus)
{
	if(m_bRevInfo == true)
	{
		*pEncStatus = m_tImgInfo.enc_info ;
		return IMG_INFO_DATA_OK ;
	}
	return IMG_INFO_DISABLE ;
}
int	CPciExpWrapper::CM_InfoGetEnc(int *pEncValue)
{
	if(m_bRevInfo == true)
	{
		*pEncValue = m_tImgInfo.enc_val ;
		return IMG_INFO_DATA_OK ;
	}
	return IMG_INFO_DISABLE ;
}
int CPciExpWrapper::CM_ImgInfoEncReset(void)
{
	int		ret ;

	if(m_bRevInfo == true)
	{
		ret = CM_RegisterWrite(ADDR_ENC_CTRL, 0x80) ;	
		return IMG_INFO_DATA_OK ;
	}
	return IMG_INFO_DISABLE ;
}
int	CPciExpWrapper::CM_InfoGetCRC(int *pCRCErrCnt, int *pCRCErrFrmCnt, int *pCRCErrTotalCnt)
{
	if(m_bRevInfo == true)
	{
		*pCRCErrCnt			= m_tImgInfo.crc_err_cnt ;
		*pCRCErrFrmCnt		= m_tImgInfo.crc_err_frm_cnt ;
		*pCRCErrTotalCnt	= m_tImgInfo.crc_err_total_cnt ;
		return IMG_INFO_DATA_OK ;
	}
	return IMG_INFO_DISABLE ;
}
int	CPciExpWrapper::CM_InfoCRCInfoClear(void)
{
	int		ret ;

	if(m_bRevInfo == true)
	{
		ret = CM_RegisterWrite(ADDR_CRC_CLEAR, 0x00) ;	
		return IMG_INFO_DATA_OK ;
	}
	return IMG_INFO_DISABLE ;
}
// I2C 관련 함수 모두 내용 수정함
int CPciExpWrapper::CM_SetI2CData(int nRegAddr, int nData)
{
	int		addr[2] ;
	int		data[2] ;
	int		ret ;
	
	addr[1] = 0 ;
	addr[0] = ADDR_IMG_I2C_DATA_WR ;
	data[1] = I2C_DATA_CODE | (nRegAddr & 0x0000ffff) ;
	data[0] = nData ;

	ret = gp_clsPCIExpress->srio_nwrite(0, addr, 8, data) ;
	if(ret)		return I2C_RET_COM_ERR ;
	
	return I2C_RET_OK ;
}
int CPciExpWrapper::CM_SetI2CCommand(int nCmdType, int nThreadId, bool bIsRead, int nRegAddrSize, int nDataSize, int nSlaveAddr, int nDataLength)
{	
	int		isBurst ;
	int		isRead ;
	int		regAddrSize ;
	int		dataSize ;
	int		dataLength ;
	int		threadId ;
	int		slaveAddr ;
	int		cmdType ;
	int		cmdData ;
	int		addr[2] ;
	int		data[2] ;
	int		ret ;

	// cmd fifo : 8 byte	
	// 1 byte - 7:0 bit	: cmd code high
	// 2 byte - 7:0 bit	: cmd code low
	// 3 byte - 7:0 bit	: reser.
	// 4 byte - 7:0 bit	: cmd type
	// 5 byte - 7 bit	: 0->single, 1->burst
	// 5 byte - 6 ibt	: 0->wr, 1->rd
	// 5 byte - 5:4 bit	: reg size
	// 5 byte - 3:0 bit	: data size
	// 6 byte - 7:0 bit	: data length for burst
	// 7 byte - 7:0 bit	: thread ID
	// 8 byte - 7 bit	: reserve
	// 8 byte - 6:0 bit	: slave address

	isBurst		= 0x80000000 ;
	isRead		= (bIsRead == 1) ? 0x40000000 : 0x0 ;
	regAddrSize	= (nRegAddrSize << 28) & 0x30000000 ;
	dataSize	= (nDataSize << 24) & 0x07000000 ;
	dataLength	= (nDataLength << 16) & 0xff0000 ;
	threadId	= (nThreadId << 8) & 0xff00 ;
	slaveAddr	= nSlaveAddr & 0x07f ;

	cmdType = I2C_CMD_CODE | (nCmdType & 0x0000ffff) ;
	cmdData = 0 ;
	cmdData = isBurst | isRead | regAddrSize | dataSize | dataLength | threadId | slaveAddr ;
	
	addr[1] = 0 ;
	addr[0] = ADDR_IMG_I2C_CMD_WR ;	
	data[1] = cmdType ;
	data[0] = cmdData ;	

	ret = gp_clsPCIExpress->srio_nwrite(0, addr, 8, data) ;
	if(ret)		return I2C_RET_COM_ERR ;
	
	return I2C_RET_OK ;
}
int CPciExpWrapper::CM_GetI2CResponse(int nThreadId, int *pRdDataH, int *pRdDataL)
{
	int		resData[2] ;
	int		ret ;

	ret = CM_CheckReadDone(SRIO_BUF_NUM_IMG, nThreadId, &resData[0]) ;
	if(ret)		return I2C_RET_COM_ERR ;
	
	*pRdDataH = resData[0] ;
	*pRdDataL = resData[1] ;

	return (resData[0] & 0xFF000000) ;
}
int CPciExpWrapper::CM_ClearI2CResRam(int nThreadId)
{
	int		readIndex ;
	int		resCheck ;
	int		rdDataH, rdDataL ;

	// 혹시 이전 data 가 들어 있으면 지운다. 10 회 까지 실행 해본다. 
	for(readIndex=0 ; readIndex<RAM_RD_RETRY_NUM ;readIndex++)
	{
		resCheck = (CM_GetI2CResponse(nThreadId, &rdDataH, &rdDataL) & 0x80000000) ;
		if(resCheck == 0x0)
		{
			return readIndex ;
		}
		Sleep(SRIO_RESP_DLY) ;		
	}
	return RAM_RD_RETRY_NUM ;
}
int	CPciExpWrapper::CM_WriteI2C(int nRegAddrSize, int nDataSize, int nSlaveAddr, int nRegAddr, int *pData, int nDataLength)
{
	int		i ;
	int		dataBuf[256] ;
	int		threadId ;
	int		ramClear ;
	int		ret ;
	int		resCheck ;
	int		startTime ;
	int		endTime ;
	int		limitTime ;	
	int		errorCount ;
	int		rdDataH, rdDataL ;

	::EnterCriticalSection(&m_csI2C) ;

	threadId = 0 ;

	if(nDataLength > 0xff)				nDataLength = 0xff ;
	// data copy
	for(i=0 ; i<nDataLength ; i++)		dataBuf[i] = *pData++ ;
	// clear ram buf
	for(i=0 ; i<nDataLength ; i++)
	{
		ramClear = CM_ClearI2CResRam(i) ;
		if(ramClear >= RAM_RD_RETRY_NUM)
		{
			gI2CWriteRetInfo[gI2CWriteTryNum][threadId] = I2C_RET_RAM_CLR_ERR ;
			I2CErrLogWrite("Write:RamClearErr: SAddr:%x RegAddr:%x ThreadId:%x", nSlaveAddr, nRegAddr, i) ;
			::LeaveCriticalSection(&m_csI2C) ;
			return I2C_RET_RAM_CLR_ERR ;
		}
	}	
	// put data
	for(int i=0 ; i<nDataLength ; i++)
	{
		ret = CM_SetI2CData(nRegAddr, dataBuf[i]) ;
		if(ret != I2C_RET_OK)
		{
			gI2CWriteRetInfo[gI2CWriteTryNum][threadId] = I2C_RET_COM_ERR ;
			I2CErrLogWrite("Write:IFComErr:SetI2cData: SAddr:%x RegAddr:%x ThreadId:%x Data:%x", nSlaveAddr, nRegAddr, i, dataBuf[i]) ;
			::LeaveCriticalSection(&m_csI2C) ;
			return I2C_RET_COM_ERR ;
		}
		Sleep(SRIO_RESP_DLY) ;	
	}
	// put cmd	
	ret = CM_SetI2CCommand(I2C_CMD_NORMAL_I2C, threadId, I2C_CMD_WRITE, nRegAddrSize, nDataSize, nSlaveAddr, nDataLength) ;
	if(ret != I2C_RET_OK)
	{
		gI2CWriteRetInfo[gI2CWriteTryNum][threadId] = I2C_RET_COM_ERR ;
		I2CErrLogWrite("Write:IFComErr:SetI2cCmd: SAddr:%x RegAddr:%x ThreadId:%x", nSlaveAddr, nRegAddr, i) ;
		::LeaveCriticalSection(&m_csI2C) ;
		return I2C_RET_COM_ERR ;
	}
	// wait response
	errorCount = 0 ;
	for(i=0 ; i<nDataLength ; i++)
	{
		Sleep(SRIO_RESP_DLY) ;
		startTime = GetTickCount() ;
		while(1)
		{
			resCheck = CM_GetI2CResponse(threadId, &rdDataH, &rdDataL) ;
			if(resCheck == I2C_RET_ACK_SUCCESS) 
			{
				gI2CWriteRetInfo[gI2CWriteTryNum][threadId] = I2C_RET_ACK_SUCCESS ;
				threadId++ ;				
				nRegAddr++ ;
				break ;
			}
			else if(resCheck == I2C_RET_CMD_ERR)
			{				
				gI2CWriteRetInfo[gI2CWriteTryNum][threadId] = I2C_RET_CMD_ERR ;
				I2CErrLogWrite("Write:WrongCmdErr: cmdtype:%x ThreadId:%x RdWr:%x RegAddrSize:%x DataSize:%x SAddr:%x DataLength:%x",
							I2C_CMD_NORMAL_I2C, threadId, I2C_CMD_WRITE, nRegAddrSize, nDataSize, nSlaveAddr, nDataLength) ;
				I2CErrLogWrite("Write:WrongCmdErrData: RegAddr:%x WrData:%x ErrCode:%x",
							nRegAddr, dataBuf[i], (BYTE)( (resCheck >> 24) & 0x0ff) ) ;
				I2CErrLogWrite("Write:ResponseData: %.8x %.8x", rdDataH, rdDataL) ;				
				
				::LeaveCriticalSection(&m_csI2C) ;
				return I2C_RET_CMD_ERR ;
			}
			else if(resCheck == I2C_RET_DATA_ERR)
			{
				gI2CWriteRetInfo[gI2CWriteTryNum][threadId] = I2C_RET_DATA_ERR ;
				I2CErrLogWrite("Write:WrongDataErr: cmdtype:%x ThreadId:%x RdWr:%x RegAddrSize:%x DataSize:%x SAddr:%x DataLength:%x",
							I2C_CMD_NORMAL_I2C, threadId, I2C_CMD_WRITE, nRegAddrSize, nDataSize, nSlaveAddr, nDataLength) ;
				I2CErrLogWrite("Write:WrongDataErrData: RegAddr:%x WrData:%x ErrCode:%x",
							nRegAddr, dataBuf[i], (BYTE)( (resCheck >> 24) & 0x0ff) ) ;
				I2CErrLogWrite("Write:ResponseData: %.8x %.8x", rdDataH, rdDataL) ;

				::LeaveCriticalSection(&m_csI2C) ;
				return I2C_RET_DATA_ERR ;
			}
			else if(resCheck == I2C_RET_BUS_BUSY_ERR)
			{
				gI2CWriteRetInfo[gI2CWriteTryNum][threadId] = I2C_RET_BUS_BUSY_ERR ;
				I2CErrLogWrite("Write:BusBusyErr: SAddr:%x RegAddr:%x ThreadId:%x WrData:%x ErrCode:%x",
							nSlaveAddr, nRegAddr, threadId, dataBuf[i], (BYTE)( (resCheck >> 24) & 0x0ff) ) ;
				I2CErrLogWrite("Write:ResponseData: %.8x %.8x", rdDataH, rdDataL) ;
				
				::LeaveCriticalSection(&m_csI2C) ;
				return I2C_RET_BUS_BUSY_ERR ;
			}
			else if( (resCheck == I2C_RET_ACK_ERR_SLAVE) || (resCheck == I2C_RET_ACK_ERR_REG1) || (resCheck == I2C_RET_ACK_ERR_REG2) || 
					(resCheck == I2C_RET_ACK_ERR_DATA1) || (resCheck == I2C_RET_ACK_ERR_DATA2) || 
					(resCheck == I2C_RET_ACK_ERR_DATA3) || (resCheck == I2C_RET_ACK_ERR_DATA4) )
			{
				I2CErrLogWrite("Write:AckErr: SAddr:%x RegAddr:%x ThreadId:%x WrData:%x ErrCode:%x",
							nSlaveAddr, nRegAddr, threadId, dataBuf[i], (BYTE)( (resCheck >> 24) & 0x0ff) ) ;
				I2CErrLogWrite("Write:ResponseData: %.8x %.8x", rdDataH, rdDataL) ;
				
				gI2CWriteRetInfo[gI2CWriteTryNum][threadId] = resCheck ;
				threadId++ ;
				errorCount++ ;				
				nRegAddr++ ;
				break ;
			}	
			endTime = GetTickCount() ;
			limitTime = endTime - startTime ;			
			if(limitTime > I2C_TIME_LIMIT)
			{
				I2CErrLogWrite("Write:TimerOutErr: SAddr:%x RegAddr:%x ThreadId:%x WrData:%x",
							nSlaveAddr, nRegAddr, threadId, dataBuf[i]) ;

				gI2CWriteRetInfo[gI2CWriteTryNum][threadId] = I2C_RET_TIMEOUT_ERR ;
				threadId++ ;
				errorCount++ ;
				nRegAddr++ ;
				break ;
			}	
		}
	}
	::LeaveCriticalSection(&m_csI2C) ;
	return errorCount ;
}
int	CPciExpWrapper::CM_ReadI2C(int nRegAddrSize, int nDataSize, int nSlaveAddr, int nRegAddr, int *pData, int nDataLength)
{
	int		ret ;
	int		i ;
	int		ramClear ;
	int		threadId ;
	int		resCheck ;
	int		rdDataH, rdDataL ;
	int		startTime ;
	int		endTime ;
	int		limitTime ;
	int		errorCount ;

	::EnterCriticalSection(&m_csI2C) ;

	threadId = 0 ;

	if(nDataLength > 0xff)	nDataLength = 0xff ;
	// clear ram buf
	for(i=0 ; i<nDataLength ; i++)
	{
		ramClear = CM_ClearI2CResRam(i) ;
		if(ramClear >= RAM_RD_RETRY_NUM)
		{
			gI2CReadRetInfo[gI2CReadTryNum][threadId] = I2C_RET_RAM_CLR_ERR ;
			I2CErrLogWrite("Read:RamClearErr: SAddr:%x RegAddr:%x ThreadId:%x", nSlaveAddr, nRegAddr, i) ;
			::LeaveCriticalSection(&m_csI2C);	// 20131010 Critical Section 추가
			return I2C_RET_RAM_CLR_ERR ;
		}
	}	
	// put data, only 1 byte about read
	ret = CM_SetI2CData(nRegAddr, 0) ;
	if(ret != I2C_RET_OK)
	{
		gI2CReadRetInfo[gI2CReadTryNum][threadId] = I2C_RET_COM_ERR ;
		I2CErrLogWrite("Read:IFComErr:SetI2cData: SAddr:%x RegAddr:%x ThreadId:%x", nSlaveAddr, nRegAddr, i) ;
		::LeaveCriticalSection(&m_csI2C) ;
		return I2C_RET_COM_ERR ;
	}
	Sleep(SRIO_RESP_DLY) ;		// put cmd
	
	ret = CM_SetI2CCommand(I2C_CMD_NORMAL_I2C, threadId, I2C_CMD_READ, nRegAddrSize, nDataSize, nSlaveAddr, nDataLength) ;
	if(ret != I2C_RET_OK)
	{
		gI2CReadRetInfo[gI2CReadTryNum][threadId] = I2C_RET_COM_ERR ;
		I2CErrLogWrite("Read:IFComErr:SetI2cCmd: SAddr:%x RegAddr:%x ThreadId:%x", nSlaveAddr, nRegAddr, i) ;
		::LeaveCriticalSection(&m_csI2C) ;
		return I2C_RET_COM_ERR ;
	}
	// wait response
	errorCount = 0 ;
	for(int i=0 ; i<nDataLength ; i++)
	{
		Sleep(SRIO_RESP_DLY) ;
		startTime = GetTickCount() ;
		while(1)
		{
			resCheck = CM_GetI2CResponse(threadId, &rdDataH, &rdDataL) ;
			if(resCheck == I2C_RET_ACK_SUCCESS)
			{
				gI2CReadRetInfo[gI2CReadTryNum][threadId] = I2C_RET_ACK_SUCCESS ;
				*pData++ = rdDataL ;
				threadId++ ;
				nRegAddr++ ;
				break ;
			}
			else if(resCheck == I2C_RET_CMD_ERR)
			{
				gI2CReadRetInfo[gI2CReadTryNum][threadId] = I2C_RET_CMD_ERR ;
				I2CErrLogWrite("Read:WrongCmdErr: cmdtype:%x ThreadId:%x RdWr:%x RegAddrSize:%x DataSize:%x SAddr:%x DataLength:%x",
							I2C_CMD_NORMAL_I2C, threadId, I2C_CMD_READ, nRegAddrSize, nDataSize, nSlaveAddr, nDataLength) ;
				I2CErrLogWrite("Read:WrongCmdErrData: RegAddr:%x ErrCode:%x",
							nRegAddr, (BYTE)( (resCheck >> 24) & 0x0ff) ) ;
				I2CErrLogWrite("Read:ResponseData: %.8x %.8x", rdDataH, rdDataL) ;

				::LeaveCriticalSection(&m_csI2C) ;
				return I2C_RET_CMD_ERR ;
			}
			else if(resCheck == I2C_RET_DATA_ERR)
			{
				gI2CReadRetInfo[gI2CReadTryNum][threadId] = I2C_RET_DATA_ERR ;
				I2CErrLogWrite("Read:WrongDataErr: cmdtype:%x ThreadId:%x RdWr:%x RegAddrSize:%x DataSize:%x SAddr:%x DataLength:%x",
							I2C_CMD_NORMAL_I2C, threadId, I2C_CMD_READ, nRegAddrSize, nDataSize, nSlaveAddr, nDataLength) ;
				I2CErrLogWrite("Read:WrongDataErrData: RegAddr:%x ErrCode:%x",
							nRegAddr, (BYTE)( (resCheck >> 24) & 0x0ff) ) ;
				I2CErrLogWrite("Read:ResponseData: %.8x %.8x", rdDataH, rdDataL) ;

				::LeaveCriticalSection(&m_csI2C) ;
				return I2C_RET_DATA_ERR ;
			}
			else if(resCheck == I2C_RET_BUS_BUSY_ERR)
			{
				gI2CReadRetInfo[gI2CReadTryNum][threadId] = I2C_RET_BUS_BUSY_ERR ;
				I2CErrLogWrite("Read:BusBusyErr: SAddr:%x RegAddr:%x ThreadId:%x ErrCode:%x",
							nSlaveAddr, nRegAddr, threadId, (BYTE)( (resCheck >> 24) & 0x0ff) ) ;
				I2CErrLogWrite("Read:ResponseData: %.8x %.8x", rdDataH, rdDataL) ;
				
				::LeaveCriticalSection(&m_csI2C) ;
				return I2C_RET_BUS_BUSY_ERR ;
			}
			else if( (resCheck == I2C_RET_ACK_ERR_SLAVE) || (resCheck == I2C_RET_ACK_ERR_REG1) || (resCheck == I2C_RET_ACK_ERR_REG2) || 
					(resCheck == I2C_RET_ACK_ERR_DATA1) || (resCheck == I2C_RET_ACK_ERR_DATA2) || 
					(resCheck == I2C_RET_ACK_ERR_DATA3) || (resCheck == I2C_RET_ACK_ERR_DATA4) )
			{
				I2CErrLogWrite("Read:AckErr: SAddr:%x RegAddr:%x ThreadId:%x ErrCode:%x",
							nSlaveAddr, nRegAddr, threadId, (BYTE)( (resCheck >> 24) & 0x0ff) ) ;
				I2CErrLogWrite("Read:ResponseData: %.8x %.8x", rdDataH, rdDataL) ;
				
				gI2CReadRetInfo[gI2CReadTryNum][threadId] = resCheck ;
				threadId++ ;
				errorCount++ ;				
				nRegAddr++ ;
				break ;
			}
			
			endTime = GetTickCount() ;
			limitTime = endTime - startTime ;			
			if(limitTime > I2C_TIME_LIMIT)
			{
				I2CErrLogWrite("Read:TimerOutErr: SAddr:%x RegAddr:%x ThreadId:%x",
							nSlaveAddr, nRegAddr, threadId) ;

				gI2CReadRetInfo[gI2CReadTryNum][threadId] = I2C_RET_TIMEOUT_ERR ;
				threadId++ ;
				errorCount++ ;
				nRegAddr++ ;				
				break ;
			}
		}
	}
	::LeaveCriticalSection(&m_csI2C) ;
	return errorCount ;
}
int	CPciExpWrapper::CM_I2CSingleWrite(int nID, int nRegAddrSize, int nDataSize, int nSlaveAddr, int nRegAddr, int nData)
{
	int		retryIndex ;
	int		ret ;
	int		errorCnt ;
	
	// retry 3회 실시
	errorCnt = 0 ;
	for(retryIndex=0 ; retryIndex<I2C_RETRY_NUM ; retryIndex++)
	{
		gI2CWriteTryNum = retryIndex ;
		ret = CM_WriteI2C(nRegAddrSize, nDataSize, nSlaveAddr, nRegAddr, &nData, 1) ;
		if(ret == 0)
		{
			break ;
		}
		else
		{
			I2CErrLogWrite("SingleWriteRetry: %d\r\n", retryIndex + 1) ;
			errorCnt++ ;
		}
		Sleep(1) ;
	}
	return errorCnt ;	// error 발생
}
int	CPciExpWrapper::CM_I2CSingleRead(int nID, int nRegAddrSize, int nDataSize, int nSlaveAddr, int nRegAddr, int *pData)
{
	int		retryIndex ;
	int		ret ;
	int		errorCnt ;
	int		rdData ;
	
	// retry 3회 실시
	errorCnt = 0 ;
	for(retryIndex=0 ; retryIndex<I2C_RETRY_NUM ; retryIndex++)
	{
		gI2CReadTryNum = retryIndex ;
		ret = CM_ReadI2C(nRegAddrSize, nDataSize, nSlaveAddr, nRegAddr, pData, 1) ;
		if(ret == 0)
		{
			break ;
		}
		else
		{
			I2CErrLogWrite("SingleReadRetry: %d\r\n", retryIndex + 1) ;			
			errorCnt++ ;
		}
		Sleep(1) ;
	}
	return errorCnt ;	// error 발생
}
int	CPciExpWrapper::CM_I2CBurstWrite(int nID, int nRegAddrSize, int nDataSize, int nSlaveAddr, int nRegAddr, int *pData, int nDataLength)
{
	int		retryIndex ;
	int		ret ;
	int		errorCnt ;
	
	// retry 3회 실시
	errorCnt = 0 ;
	for(retryIndex=0 ; retryIndex<I2C_RETRY_NUM ; retryIndex++)
	{
		gI2CWriteTryNum = retryIndex ;
		ret = CM_WriteI2C(nRegAddrSize, nDataSize, nSlaveAddr, nRegAddr, pData, nDataLength) ;
		if(ret == 0)
		{
			break ;
		}
		else
		{
			I2CErrLogWrite("BurstWriteRetry: %d\r\n", retryIndex + 1) ;
			errorCnt++ ;
		}
		Sleep(1) ;
	}
	return errorCnt ;	// error 발생
}

int	CPciExpWrapper::CM_I2CBurstRead(int nID, int nRegAddrSize, int nDataSize, int nSlaveAddr, int nRegAddr, int *pData, int nDataLength)
{
	int		retryIndex ;
	int		ret ;
	int		errorCnt ;
	
	// retry 3회 실시
	errorCnt = 0 ;
	for(retryIndex=0 ; retryIndex<I2C_RETRY_NUM ; retryIndex++)
	{
		gI2CReadTryNum = retryIndex ;
		ret = CM_ReadI2C(nRegAddrSize, nDataSize, nSlaveAddr, nRegAddr, pData, nDataLength) ;
		if(ret == 0)
		{
			break ;
		}
		else
		{
			I2CErrLogWrite("BurstReadRetry: %d\r\n", retryIndex + 1) ;
			errorCnt++ ;
		}
		Sleep(1) ;
	}
	return errorCnt ;	// error 발생
}
int	CPciExpWrapper::CM_I2CSleep(float fMiliSecond)
{
	int		ramClear ;
	int		msTime ;
	int		ret ;
	int		threadId ;
	int		resCheck ;
	int		rdDataH, rdDataL ;
	int		startTime ;
	int		endTime ;
	int		limitTime ;	

	ramClear = CM_ClearI2CResRam(0) ;
	if(ramClear >= RAM_RD_RETRY_NUM)
	{
		I2CErrLogWrite("Sleep:RamClearErr: time:%dms", fMiliSecond) ;
		return I2C_RET_RAM_CLR_ERR ;
	}
		
	msTime = (int)(fMiliSecond * 10) ;
	threadId = 0 ;
	
	ret = CM_SetI2CData(0, msTime) ;
	if(ret != I2C_RET_OK)
	{
		I2CErrLogWrite("Sleep:IFComErr:SetI2cData: time:%dms", fMiliSecond) ;
		return I2C_RET_COM_ERR ;
	}
	ret = CM_SetI2CCommand(I2C_CMD_SLEEP, threadId, 0, 0, 0, 0, 0) ;
	if(ret != I2C_RET_OK)
	{
		I2CErrLogWrite("Sleep:IFComErr:SetI2cCmd: time:%dms", fMiliSecond) ;
		return I2C_RET_COM_ERR ;
	}
	
	Sleep((int)fMiliSecond - 1) ;
	startTime = GetTickCount() ;
	while(1)
	{
		resCheck = CM_GetI2CResponse(threadId, &rdDataH, &rdDataL) ;
		if(resCheck == I2C_RET_ACK_SUCCESS)	return I2C_RET_SLEEP_OK ;

		endTime = GetTickCount() ;
		limitTime = endTime - startTime ;
		if(limitTime > I2C_TIME_LIMIT)		return I2C_RET_TIMEOUT_ERR ;
	}
}
int CPciExpWrapper::CM_I2CGetWriteResult(tagI2C_RESULT *pBufPoint)
{
	memcpy(pBufPoint, &gI2CWriteRetInfo[0][0], 3 * 256 * 4) ;
	
	return 0 ;	
}
int CPciExpWrapper::CM_I2CGetReadResult(tagI2C_RESULT *pBufPoint)
{
	memcpy(pBufPoint, &gI2CReadRetInfo[0][0], 3 * 256 * 4) ;
	
	return 0 ;	
}
int CPciExpWrapper::AD5840_SpecialI2CEnable(bool bEn)
{
	int		addr[2] ;
	int		data[2] ;
	int		ret ;

	// send data ;
	addr[1] = 0 ;
	addr[0] = ADDR_IMG_I2C_ACT_SEL ;
	data[1] = 0 ;
	if(bEn == true)	data[0] = 0x02 ;
	else			data[0] = 0x01 ;

	ret = gp_clsPCIExpress->srio_nwrite(0, addr, 8, data) ;
	if(ret)		return S_I2C_RET_COM_ERR ;
	
	return S_I2C_RET_OK ;
}
int CPciExpWrapper::AD5840_SpecialI2CSetData(int nFirstPosiX, int nFirstPosiY, int nLastPosiX, int nLastPosiY)
{
	int		addr[2] ;
	int		data[2] ;
	int		ret ;	

	addr[1] = 0 ;
	addr[0] = ADDR_IMG_AD5840_F_DATA ;
	data[1] = I2C_DATA_CODE ;
	//data[0] = ( (nFirstPosiX << 12) & 0x0f00000) | ( (nFirstPosiY << 8) & 0x0f0000) | ( (nFirstPosiX << 8) & 0x0ff00) | (nFirstPosiY & 0x0ff) ;
	data[0] = ( (nFirstPosiX << 11) & 0x0380000) | ( (nFirstPosiY << 8) & 0x070000) | ( (nFirstPosiX << 8) & 0x0ff00) | (nFirstPosiY & 0x0ff) ;

	ret = gp_clsPCIExpress->srio_nwrite(0, addr, 8, data) ;
	if(ret)		return S_I2C_RET_COM_ERR ;
	
	addr[0] = ADDR_IMG_AD5840_L_DATA ;
	data[0] = ( (nLastPosiX << 11) & 0x0380000) | ( (nLastPosiY << 8) & 0x070000) | ( (nLastPosiX << 8) & 0x0ff00) | (nLastPosiY & 0x0ff) ;

	ret = gp_clsPCIExpress->srio_nwrite(0, addr, 8, data) ;
	if(ret)		return S_I2C_RET_COM_ERR ;

	return S_I2C_RET_OK ;
}
int CPciExpWrapper::AD5840_SpecialI2CSetCmd(int nSAddr, int nFPosiSize, int nLPosiSize, int nHallDataSize, int nHallRdSize)
{
	int		tmp ;
	int		addr[2] ;
	int		data[2] ;
	int		ret ;	

	addr[1] = 0 ;
	addr[0] = ADDR_IMG_AD5840_CMD_WR ;
	// 7 byte			: cmd code high
	// 6 byte			: cmd code low
	// 5 byte			: reser.
	// 4 byte - 7:4 bit : first posi data size
	// 4 byte - 3:0 bit	: Last posi data size
	// 3 byte - 3:0 bit	: hall data size
	// 2 byte			: hall data read size high
	// 1 byte			: hall data read size low
	// 0 byte - 6:0 bit	: slave address
	data[1] = I2C_CMD_CODE ;
	tmp = (nFPosiSize << 4) & 0x00f0 ;
	data[1] = data[1] + tmp ;
	tmp = nLPosiSize & 0x000f ;
	data[1] = data[1] + tmp ;	

	data[0] = (nHallDataSize << 24) & 0x0f000000 ;
	tmp = (nHallRdSize << 8) & 0x00ffff00 ;
	data[0] = data[0] + tmp ;
	tmp = nSAddr & 0x0000007F ;
	data[0] = data[0] + tmp ;

	ret = gp_clsPCIExpress->srio_nwrite(0, addr, 8, data) ;
	if(ret)		return S_I2C_RET_COM_ERR ;

	return S_I2C_RET_OK ;
}
int CPciExpWrapper::AD5840_SpecialI2CSetDelayTime(int nTxDelayNano, int nRxDelayNano)
{
	int		addr[2] ;
	int		data[2] ;
	int		ret ;	

	addr[1] = 0 ;
	addr[0] = ADDR_IMG_AD5840_DLY ;
	data[1] = (nRxDelayNano / 10) & 0xffffffff ;
	data[0] = (nTxDelayNano / 10) & 0xffffffff ;

	ret = gp_clsPCIExpress->srio_nwrite(0, addr, 8, data) ;
	if(ret)		return S_I2C_RET_COM_ERR ;

	return S_I2C_RET_OK ;
}
int CPciExpWrapper::AD5840_SpecialI2C(int nSAddr, int nFirstPosiX, int nFirstPosiY, bool bLastPosiEn, int nLastPosiX, int nLastPosiY, int nHallRdSize, int *pXValue, int *pYValue)
{
	int		ret ;
	int		i ;
	int		ramClear ;
	int		threadId ;	
	int		startTime ;
	int		endTime ;
	int		limitTime ;
	int		resCheck ;
	int		rdDataH, rdDataL ;
	int		hallVal[3] ;

	::EnterCriticalSection(&m_csI2C) ;

	ret = AD5840_SpecialI2CEnable(true) ;
	if(ret)		return S_I2C_RET_COM_ERR ;	
	// clear ram buf
	for(i=0 ; i<=0xff ; i++)
	{
		ramClear = CM_ClearI2CResRam(i) ;
		if(ramClear >= RAM_RD_RETRY_NUM)
		{			
			I2CErrLogWrite("SI2C:RamClearErr: ThreadId:%x", i) ;
			::LeaveCriticalSection(&m_csI2C) ;

			ret = AD5840_SpecialI2CEnable(false) ;
			return S_I2C_RET_RAM_CLR_ERR ;
		}
	}
	// put data
	ret = AD5840_SpecialI2CSetData(nFirstPosiX, nFirstPosiY, nLastPosiX, nLastPosiY) ;
	if(ret)
	{
		I2CErrLogWrite("SI2C:IFComErr:SetData: FirstPosi:(%d, %d), LastPosi:(%d, %d)", nFirstPosiX, nFirstPosiY, nLastPosiX, nLastPosiY) ;
		::LeaveCriticalSection(&m_csI2C) ;

		ret = AD5840_SpecialI2CEnable(false) ;
		return S_I2C_RET_COM_ERR ;
	}
	// put cmd
	if(bLastPosiEn == 0)	ret = AD5840_SpecialI2CSetCmd(nSAddr, 3, 0, 3, nHallRdSize) ;
	else					ret = AD5840_SpecialI2CSetCmd(nSAddr, 3, 3, 3, nHallRdSize) ;
	if(ret)
	{
		I2CErrLogWrite("SI2C:IFComErr:SetCmd: SAddr:%x, HallRdSize:%x", nSAddr, nHallRdSize) ;
		::LeaveCriticalSection(&m_csI2C) ;

		ret = AD5840_SpecialI2CEnable(false) ;
		return S_I2C_RET_COM_ERR ;
	}
	// wait response about first posi data
	threadId = 0 ;
	Sleep(SRIO_RESP_DLY) ;
	startTime = GetTickCount() ;
	while(1)
	{
		resCheck = CM_GetI2CResponse(threadId, &rdDataH, &rdDataL) ;
		if(resCheck == S_I2C_RET_ACK_SUCCESS)
		{
			break ;
		}
		else if( (resCheck != S_I2C_RET_ACK_SUCCESS) && (resCheck != 0) )
		{
			I2CErrLogWrite("SI2C:FirstPosiTxErr: FirstPosi:(%d, %d), ErrCode:%x", nFirstPosiX, nFirstPosiY, resCheck) ;
			::LeaveCriticalSection(&m_csI2C) ;

			ret = AD5840_SpecialI2CEnable(false) ;
			return resCheck ;
		}
		endTime = GetTickCount() ;
		limitTime = endTime - startTime ;			
		if(limitTime > I2C_TIME_LIMIT)
		{
			I2CErrLogWrite("SI2C:FirstPosiTimerOutErr: FirstPosi:(%d, %d)", nFirstPosiX, nFirstPosiY) ;
			::LeaveCriticalSection(&m_csI2C) ;

			ret = AD5840_SpecialI2CEnable(false) ;
			return S_I2C_RET_TIMEOUT_ERR ;
		}	
	}
	// read hall value
	threadId++ ;
	for(int i=0 ; i<nHallRdSize ; i++)
	{
		Sleep(SRIO_RESP_DLY) ;
		startTime = GetTickCount() ;
		while(1)
		{
			resCheck = CM_GetI2CResponse( (threadId & 0x0ff), &rdDataH, &rdDataL) ;
			if(resCheck == I2C_RET_ACK_SUCCESS)
			{
				//*pHallValue++ = rdDataL & 0x00ffffff ;
				hallVal[0] = (rdDataL >> 16) & 0x00ff ;
				hallVal[1] = (rdDataL >> 8) & 0x00ff ;
				hallVal[2] = (rdDataL >> 0) & 0x00ff ;

				*pXValue = ( (hallVal[0] << 4) & 0x0ff0) + ( (hallVal[1] >> 4) & 0x000f) ;
				*pYValue = ( (hallVal[1] << 8) & 0x0f00) + ( (hallVal[2] >> 0) & 0x00ff) ;
				
				*pXValue++ = (rdDataL >> 12) & 0x0fff ;
				*pYValue++ = (rdDataL >> 0) & 0x0fff ;

				threadId++ ;
				break ;
			}
			else if( (resCheck != S_I2C_RET_ACK_SUCCESS) && (resCheck != 0) )
			{
				I2CErrLogWrite("SI2C:HallRdErr: HallRdSize:%x, CurCnt:%x, ErrCode:%x", nHallRdSize, i, resCheck) ;
				::LeaveCriticalSection(&m_csI2C) ;

				ret = AD5840_SpecialI2CEnable(false) ;
				return resCheck ;
			}
			endTime = GetTickCount() ;
			limitTime = endTime - startTime ;			
			if(limitTime > I2C_TIME_LIMIT)
			{
				I2CErrLogWrite("SI2C:HallRdTimerOutErr: HallRdSize:%x, CurCnt:%x", nHallRdSize, i) ;
				::LeaveCriticalSection(&m_csI2C) ;

				ret = AD5840_SpecialI2CEnable(false) ;
				return S_I2C_RET_TIMEOUT_ERR ;
			}
		}
	}
	// wait response about last posi data
	if(bLastPosiEn == 0)
	{
		ret = AD5840_SpecialI2CEnable(false) ;
		if(ret)		return S_I2C_RET_COM_ERR ;

		return S_I2C_RET_OK ;
	}
	Sleep(SRIO_RESP_DLY) ;
	startTime = GetTickCount() ;
	while(1)
	{
		resCheck = CM_GetI2CResponse( (threadId & 0x0ff), &rdDataH, &rdDataL) ;
		if(resCheck == S_I2C_RET_ACK_SUCCESS)
		{
			break ;
		}
		else if( (resCheck != S_I2C_RET_ACK_SUCCESS) && (resCheck != 0) )
		{
			I2CErrLogWrite("SI2C:LastPosiTxErr: LastPosi:(%d, %d), ErrCode:%x", nLastPosiX, nLastPosiY, resCheck) ;
			::LeaveCriticalSection(&m_csI2C) ;

			ret = AD5840_SpecialI2CEnable(false) ;
			return resCheck ;
		}
		endTime = GetTickCount() ;
		limitTime = endTime - startTime ;			
		if(limitTime > I2C_TIME_LIMIT)
		{
			I2CErrLogWrite("SI2C:LastPosiTimerOutErr: LastPosi:(%d, %d)", nLastPosiX, nLastPosiY) ;
			::LeaveCriticalSection(&m_csI2C) ;

			ret = AD5840_SpecialI2CEnable(false) ;
			return S_I2C_RET_TIMEOUT_ERR ;
		}	
	}

	ret = AD5840_SpecialI2CEnable(false) ;
	if(ret)		return S_I2C_RET_COM_ERR ;

	return S_I2C_RET_OK ;
}
int CPciExpWrapper::SpecialI2CEnable(bool bEn)
{
	int		addr[2] ;
	int		data[2] ;
	int		ret ;

	// send data ;
	addr[1] = 0 ;
	addr[0] = ADDR_IMG_I2C_ACT_SEL ;
	data[1] = 0 ;
	if(bEn == true)	data[0] = 0x04 ;
	else			data[0] = 0x01 ;

	ret = gp_clsPCIExpress->srio_nwrite(0, addr, 8, data) ;
	if(ret)		return S_I2C_RET_COM_ERR ;
	
	return S_I2C_RET_OK ;
}
int CPciExpWrapper::SpecialI2CSetData(int nDataSize, BYTE *pData, int nLastDataSize, BYTE *pLastData)
{
	int		txData ;
	int		addr[2] ;
	int		data[2] ;
	int		ret ;	
	int		i ;

	addr[1] = 0 ;
	addr[0] = ADDR_IMG_SI2C_DATA_WR ;
	data[1] = 0 ;
	for(i=0 ; i<nDataSize ; i++)
	{
		txData = (int)*pData++ ;
		data[0] = SI2C_DATA_CODE + (txData & 0x0ff) ;

		ret = gp_clsPCIExpress->srio_nwrite(0, addr, 8, data) ;
		if(ret)		return S_I2C_RET_COM_ERR ;
	}	
	for(i=0 ; i<nLastDataSize ; i++)
	{
		txData = (int)*pLastData++ ;
		data[0] = SI2C_DATA_CODE + (txData & 0x0ff) ;

		ret = gp_clsPCIExpress->srio_nwrite(0, addr, 8, data) ;
		if(ret)		return S_I2C_RET_COM_ERR ;
	}

	return S_I2C_RET_OK ;
}
int CPciExpWrapper::SpecialI2CSetCmd(int nSAddr, int nTxDataSize, int nRxDataSize, int nRxRepeatSize, int nLastTxDataSize)
{
	int		tmp ;
	int		addr[2] ;
	int		data[2] ;
	int		ret ;	

	addr[1] = 0 ;
	addr[0] = ADDR_IMG_SI2C_CMD_WR ;
	// cmd : 8 byte
	// 7 byte - 7:0 bit	: cmd code high
	// 6 byte - 7:0 bit	: cmd code low
	// 5 byte - 7:0 bit : tx data size
	// 4 byte - 7:0 bit	: rx size
	// 3 byte - 7:0 bit	: last tx size
	// 2 byte - 7:0 bit	: hall data read size high
	// 1 byte - 7:0 bit	: hall data read size low
	// 0 byte - 7 bit	: reserve
	// 0 byte - 6:0 bit	: slave address	
	data[1] = I2C_CMD_CODE ;
	tmp = (nTxDataSize << 8) & 0xff00 ;
	data[1] = data[1] + tmp ;
	tmp = nRxDataSize & 0x00ff ;
	data[1] = data[1] + tmp ;	

	data[0] = (nLastTxDataSize << 24) & 0xff000000 ;
	tmp = (nRxRepeatSize << 8) & 0x00ffff00 ;
	data[0] = data[0] + tmp ;
	tmp = nSAddr & 0x0000007F ;
	data[0] = data[0] + tmp ;

	ret = gp_clsPCIExpress->srio_nwrite(0, addr, 8, data) ;
	if(ret)		return S_I2C_RET_COM_ERR ;

	return S_I2C_RET_OK ;
}
int CPciExpWrapper::SpecialI2CSetDelayTime(int nTxDelayNano, int nRxDelayNano)
{
	int		addr[2] ;
	int		data[2] ;
	int		ret ;	

	addr[1] = 0 ;
	addr[0] = ADDR_IMG_SI2C_FRAME_DLY ;
	data[1] = (nRxDelayNano / 10) & 0xffffffff ;
	data[0] = (nTxDelayNano / 10) & 0xffffffff ;

	ret = gp_clsPCIExpress->srio_nwrite(0, addr, 8, data) ;
	if(ret)		return S_I2C_RET_COM_ERR ;

	return S_I2C_RET_OK ;
}
int CPciExpWrapper::SpecialI2C(BYTE byID, int nData, BYTE *dacBuf, int nRead, int nBytesPerRead, BYTE *hallBuf, int nPosi, BYTE *posBuf)
{
	int		ret ;
	int		i ;
	int		ramClear ;
	int		threadId ;	
	int		startTime ;
	int		endTime ;
	int		limitTime ;
	int		resCheck ;
	int		rdDataH, rdDataL ;
	int		hallVal[3] ;

	::EnterCriticalSection(&m_csI2C) ;

	if(nRead == 0)			nBytesPerRead = 0 ;

	ret = SpecialI2CEnable(true) ;
	if(ret)
	{
		::LeaveCriticalSection(&m_csI2C) ;
		return S_I2C_RET_COM_ERR ;	
	}
	// clear ram buf
	for(i=0 ; i<=0xff ; i++)
	{
		ramClear = CM_ClearI2CResRam(i) ;
		if(ramClear >= RAM_RD_RETRY_NUM)
		{			
			I2CErrLogWrite("SI2C:RamClearErr: ThreadId:%x", i) ;
			::LeaveCriticalSection(&m_csI2C) ;

			ret = SpecialI2CEnable(false) ;
			return S_I2C_RET_RAM_CLR_ERR ;
		}
	}
	// put data
	// int SpecialI2CSetData(int nDataSize, BYTE *pData, int nLastDataSize, BYTE *pLastData) ;
	ret = SpecialI2CSetData(nData, dacBuf, nPosi, posBuf) ;
	if(ret)
	{
		I2CErrLogWrite("SI2C:IFComErr:SetData: nDataSize:%d, nLastDataSize:%d", nData, nPosi) ;
		::LeaveCriticalSection(&m_csI2C) ;

		ret = SpecialI2CEnable(false) ;
		return S_I2C_RET_COM_ERR ;
	}
	// put cmd
	//int SpecialI2CSetCmd(int nSAddr, int nTxDataSize, int nRxDataSize, int nRxRepeatSize, int nLastTxDataSize)
	ret = SpecialI2CSetCmd(byID, nData, nBytesPerRead, nRead, nPosi) ;
	if(ret)
	{
		I2CErrLogWrite("SI2C:IFComErr:SetCmd: SAddr:%x, nTxDataSize:%d, nRxDataSize:%d, nRxRepeatSize:%d, nLastTxDataSize:%d", byID, nData, nData, nRead, nPosi) ;
		::LeaveCriticalSection(&m_csI2C) ;

		ret = SpecialI2CEnable(false) ;
		return S_I2C_RET_COM_ERR ;
	}
	// wait response about first posi data
	threadId = 0 ;
	Sleep(SRIO_RESP_DLY) ;
	startTime = GetTickCount() ;
	if(nData != 0)
	{
		while(1)
		{
			resCheck = CM_GetI2CResponse(threadId, &rdDataH, &rdDataL) ;
			if(resCheck == S_I2C_RET_ACK_SUCCESS)
			{
				break ;
			}
			else if( (resCheck != S_I2C_RET_ACK_SUCCESS) && (resCheck != 0) )
			{
				I2CErrLogWrite("SI2C:FirstPosiTxErr: ErrCode:%x", resCheck) ;
				::LeaveCriticalSection(&m_csI2C) ;

				ret = SpecialI2CEnable(false) ;
				return resCheck ;
			}
			endTime = GetTickCount() ;
			limitTime = endTime - startTime ;			
			if(limitTime > I2C_TIME_LIMIT)
			{
				I2CErrLogWrite("SI2C:FirstPosiTimerOutErr:") ;
				::LeaveCriticalSection(&m_csI2C) ;

				ret = SpecialI2CEnable(false) ;
				return S_I2C_RET_TIMEOUT_ERR ;
			}	
		}
		threadId++ ;
	}
	// read hall value	
	for(int i=0 ; i<(nRead * nBytesPerRead) ; i++)
	{
		Sleep(SRIO_RESP_DLY) ;
		startTime = GetTickCount() ;
		while(1)
		{
			resCheck = CM_GetI2CResponse( (threadId & 0x0ff), &rdDataH, &rdDataL) ;
			if(resCheck == I2C_RET_ACK_SUCCESS)
			{
				*hallBuf++ = rdDataL & 0x0ff ;
				threadId++ ;
				break ;
			}
			else if( (resCheck != S_I2C_RET_ACK_SUCCESS) && (resCheck != 0) )
			{
				I2CErrLogWrite("SI2C:HallRdErr: HCurCnt:%x, ErrCode:%x", i, resCheck) ;
				::LeaveCriticalSection(&m_csI2C) ;

				ret = SpecialI2CEnable(false) ;
				return resCheck ;
			}
			endTime = GetTickCount() ;
			limitTime = endTime - startTime ;			
			if(limitTime > I2C_TIME_LIMIT)
			{
				I2CErrLogWrite("SI2C:HallRdTimerOutErr: CurCnt:%x", i) ;
				::LeaveCriticalSection(&m_csI2C) ;

				ret = SpecialI2CEnable(false) ;
				return S_I2C_RET_TIMEOUT_ERR ;
			}
		}
	}
	// wait response about last posi data
	if(nPosi == 0)
	{
		::LeaveCriticalSection(&m_csI2C) ;

		ret = SpecialI2CEnable(false) ;
		if(ret)		return S_I2C_RET_COM_ERR ;

		return S_I2C_RET_OK ;
	}
	Sleep(SRIO_RESP_DLY) ;
	startTime = GetTickCount() ;
	while(1)
	{
		resCheck = CM_GetI2CResponse( (threadId & 0x0ff), &rdDataH, &rdDataL) ;
		if(resCheck == S_I2C_RET_ACK_SUCCESS)
		{
			break ;
		}
		else if( (resCheck != S_I2C_RET_ACK_SUCCESS) && (resCheck != 0) )
		{
			I2CErrLogWrite("SI2C:LastPosiTxErr: ErrCode:%x", resCheck) ;
			::LeaveCriticalSection(&m_csI2C) ;

			ret = SpecialI2CEnable(false) ;
			return resCheck ;
		}
		endTime = GetTickCount() ;
		limitTime = endTime - startTime ;			
		if(limitTime > I2C_TIME_LIMIT)
		{
			I2CErrLogWrite("SI2C:LastPosiTimerOutErr:") ;
			::LeaveCriticalSection(&m_csI2C) ;

			ret = SpecialI2CEnable(false) ;
			return S_I2C_RET_TIMEOUT_ERR ;
		}
	}

	::LeaveCriticalSection(&m_csI2C) ;

	ret = SpecialI2CEnable(false) ;
	if(ret)		return S_I2C_RET_COM_ERR ;

	return S_I2C_RET_OK ;
}


// firm upgrade
bool CPciExpWrapper::FlashGetResFifoDcnt(int *pDataCnt)
{
	__int64		rxData ;
	__int64		dCnt ;
	int			ret ;

	ret = CM_RegisterRead(0x760, &rxData) ;
	if(ret)		return false ;

	dCnt = (int)rxData & 0xffff ;
	if(m_bIFCardEndian == false)	dCnt = ( (rxData << 48) & 0xff00)	|  ( (rxData >> 56) & 0x00ff) ;
	else							dCnt = rxData & 0xffff ;

	*pDataCnt = dCnt ;

	return true ;
}
bool CPciExpWrapper::FlashGetResFifoData(__int64 *pData)
{
	__int64		rxData ;
	char		*pDataAddr ;
	int			ret ;

	ret = CM_RegisterRead(0x730, &rxData) ;
	if(ret)		return false ;

	pDataAddr = (char*)pData ;

	if(m_bIFCardEndian == false)	// 구버전 IF
	{
		*pDataAddr++ = (char)( (rxData >> 56) & 0x0ff) ;
		*pDataAddr++ = (char)( (rxData >> 48) & 0x0ff) ;
		*pDataAddr++ = (char)( (rxData >> 40) & 0x0ff) ;
		*pDataAddr++ = (char)( (rxData >> 32) & 0x0ff) ;
		*pDataAddr++ = (char)( (rxData >> 24) & 0x0ff) ;
		*pDataAddr++ = (char)( (rxData >> 16) & 0x0ff) ;
		*pDataAddr++ = (char)( (rxData >> 8) & 0x0ff) ;
		*pDataAddr++ = (char)( (rxData >> 0) & 0x0ff) ;		
	}
	else
	{
		*pDataAddr++ = (char)( (rxData >> 0) & 0x0ff) ;
		*pDataAddr++ = (char)( (rxData >> 8) & 0x0ff) ;
		*pDataAddr++ = (char)( (rxData >> 16) & 0x0ff) ;
		*pDataAddr++ = (char)( (rxData >> 24) & 0x0ff) ;
		*pDataAddr++ = (char)( (rxData >> 32) & 0x0ff) ;
		*pDataAddr++ = (char)( (rxData >> 40) & 0x0ff) ;
		*pDataAddr++ = (char)( (rxData >> 48) & 0x0ff) ;
		*pDataAddr++ = (char)( (rxData >> 56) & 0x0ff) ;
	}
	return true ;
	/*
	if(m_bIFCardEndian == false)	// 구버전 IF
	{
		*pFwVersion++ = (char)( (rdData >> 0) & 0x0ff) ;
		*pFwVersion++ = (char)( (rdData >> 8) & 0x0ff) ;
		*pFwVersion++ = (char)( (rdData >> 16) & 0x0ff) ;
		*pFwVersion++ = (char)( (rdData >> 24) & 0x0ff) ;
		*pFwVersion++ = (char)( (rdData >> 32) & 0x0ff) ;
		*pFwVersion++ = (char)( (rdData >> 40) & 0x0ff) ;
		*pFwVersion++ = (char)( (rdData >> 48) & 0x0ff) ;
		*pFwVersion++ = (char)( (rdData >> 56) & 0x0ff) ;
		*pFwVersion = 0 ;
	}
	else
	{
		*pFwVersion++ = (char)( (rdData >> 56) & 0x0ff) ;
		*pFwVersion++ = (char)( (rdData >> 48) & 0x0ff) ;
		*pFwVersion++ = (char)( (rdData >> 40) & 0x0ff) ;
		*pFwVersion++ = (char)( (rdData >> 32) & 0x0ff) ;
		*pFwVersion++ = (char)( (rdData >> 24) & 0x0ff) ;
		*pFwVersion++ = (char)( (rdData >> 16) & 0x0ff) ;
		*pFwVersion++ = (char)( (rdData >> 8) & 0x0ff) ;
		*pFwVersion++ = (char)( (rdData >> 0) & 0x0ff) ;
		*pFwVersion = 0 ;
	}
	*/
}
BOOL CPciExpWrapper::FLASH_8x32_Write(int nAddress, unsigned char *data, unsigned char byteLength)
{
	unsigned char *SendData;
	int m_ibyteCnt=0;
	__int64 writeVal, writeVal1, leftbyte=0, data1;

	SendData = data;

	for (int i = 0 ; i < (byteLength / 8)+1 ; i++){
		writeVal = 0;

		if (i < (byteLength+1)/8 ){
			for (int j = 0 ; j < 8; j++){
				writeVal += SendData[j] * (__int64)pow((double)0x100, 7-j );
			}
			SendData = &*(data + (i+1)*8) ;
		}
		else if( (byteLength+1) % 8 != 0 ){
			for (int j = 0 ; j < (byteLength) % 8 ; j++){
				writeVal += SendData[j] * (__int64)pow((double)0x100, 7-j );
			}
			for (int j =  (byteLength) % 8 ; j < 8 ; j++){
				writeVal += 0xff * (__int64)pow((double)0x100, 7-j );
			}
		}

		CM_RegisterWrite(0x720, writeVal);				
	}

	writeVal = 0x0111000000000000 + ((__int64)nAddress * 0x1000000) + (__int64)((byteLength/8+1) * 0x10000)  ;
	CM_RegisterWrite(0x710, writeVal);
	Sleep(10);

	return TRUE;
}

BOOL CPciExpWrapper::FLASH_Bulk_Erase(){
	//0303
	return TRUE;
}

BOOL CPciExpWrapper::FLASH_Sector_Erase(int nAddress )
{	
	__int64		writeVal, data;	

	writeVal = 0x0302000000000000 + ((__int64)nAddress * 0x1000000);	
	CM_RegisterWrite(0x710, writeVal);
	Sleep(1000);

	return TRUE;
}
void CPciExpWrapper::FLASH_ResFlush(void)
{
	int			dCnt ;
	__int64		tmp ;

	while(1)
	{
		FlashGetResFifoDcnt(&dCnt) ;
		if(dCnt != 0)		for(int i = 0 ; i< dCnt ; i++)	CM_RegisterRead(0x730, &tmp) ;			
		else				break ;
	}	
}

BOOL CPciExpWrapper::FLASH_Verification(char* str)
{
	__int64		writeVal, data;	
	int			DataCnt = 0, FileSize;
	unsigned char Rcv_Data[8];
	FILE *fp;
	struct stat sb;

	if (stat (str, &sb) != 0){
		return FALSE;
	}

	FLASH_ResFlush();

	fp=fopen(str, "rb");
	
	while(1){
		writeVal = 0x0211000000000100 + ((__int64)DataCnt * 0x1000000);
		CM_RegisterWrite(0x710, writeVal);
		
		while(1){
			CM_RegisterRead(0x760, &data);
			if ( data == 32)
				break;
		}
		
		fseek(fp,DataCnt,0);
		if ( sb.st_size - 256 > DataCnt ){
			for (int i = 0 ; i < 32 ; i++){
				CM_RegisterRead(0x730, &data);
				fread(Rcv_Data,1,8,fp);
				for (int j= 0 ; j< 8 ; j++){
					if (Rcv_Data[j] != ((data >> (8*(7-j))) & 0xff) ){
						fclose(fp);
						return FALSE;			
					}
				}	
			}
			
		}
		else{
			for (int i= DataCnt; DataCnt < sb.st_size ; DataCnt = DataCnt + 8){
				CM_RegisterRead(0x730, &data);

				if (DataCnt +8 < sb.st_size){
					fread(Rcv_Data,1,8,fp);
					for (int j= 0 ; j< 8 ; j++){
						if (Rcv_Data[j] != ((data >> (8*(7-j))) & 0xff) ){
							fclose(fp);
							return FALSE;			
						}
					}
				}
				else {
					fread(Rcv_Data,1, (sb.st_size - DataCnt), fp);
					for (int j= 0 ; j< (sb.st_size - DataCnt) ; j++){
						if (Rcv_Data[j] != ((data >> (8*(7-j))) & 0xff) ){
							fclose(fp);
							return FALSE;			
						}
					}

				}				
			}
			fclose(fp);
			FLASH_ResFlush();
			return TRUE;
		}
		DataCnt += 256;	
	}

	FLASH_ResFlush();
	
	return TRUE;
}
BOOL CPciExpWrapper::FLASH_8x32_Read(int nAddress, __int64 *pRdData)
{
	__int64			addr ;
	__int64			data ;
	int				dCount ;
	int				startTime ;
	int				endTime ;
	int				limitTime ;
	unsigned char	rdData[8] ;
	int				i ;

	FLASH_ResFlush() ;

	if(nAddress < 0xFF0000)	return false ;

	addr = (__int64)nAddress * 0x1000000 ;
	data = 0x0211000000000100 + addr ;

	CM_RegisterWrite(0x710, data) ;

	Sleep(0) ;
	startTime = GetTickCount() ;
	while(1)
	{
		FlashGetResFifoDcnt(&dCount) ;
		//CM_RegisterRead(0x760, &data) ;
		if(dCount == 32)	break ;

		endTime = GetTickCount() ;
		limitTime = endTime - startTime ;			
		if(limitTime > 100)	return false ;
	}
	for(i=0 ; i<32 ; i++)
	{
		FlashGetResFifoData(&data) ;
		//CM_RegisterRead(0x730, &data) ;
		*pRdData++ = data ;		
	}

	FLASH_ResFlush() ;

	return true ;
}
// I2C Error Log
#define I2C_ERROR_LOG_DIRECTORY_STRING			"D:\\LG_PRI_I2C_ERR_LOG"

int CPciExpWrapper::SetErrLog(int iPara, bool bSet)
{
	m_nPara = iPara ;
	m_bErrorLog = bSet ;

	I2CErrLogFileCreate() ;

	return 0 ;
}

int CPciExpWrapper::I2CErrLogFileCreate(void)
{
	time_t			nowTime ;
	struct tm		timeinfo ;	
	int				len ;	
	
	/*
	if(m_bErrorLog == true)
	{
		CreateDirectory(I2C_ERROR_LOG_DIRECTORY_STRING, NULL) ;
	
		nowTime = time(NULL) ;
		localtime_s(&timeinfo, &nowTime) ;
		len = sprintf_s(&m_cErrLogFileName[0], 64, "%s\\PARA%02d_%d%.2d%.2d_%.2d%.2d%.2d", I2C_ERROR_LOG_DIRECTORY_STRING, m_nPara,
						timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday,
						timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec) ;
		m_cErrLogFileName[len++] = '.' ;
		m_cErrLogFileName[len++] = 't' ;
		m_cErrLogFileName[len++] = 'x' ;
		m_cErrLogFileName[len++] = 't' ;
		m_cErrLogFileName[len++] = 0 ;
	}*/

	return 0 ;
}
int CPciExpWrapper::I2CErrLogWrite(char *szStr, ...)
{
	time_t			nowTime ;
	struct tm		timeinfo ;	
	va_list			ap ;
	char			buffer[1024] ;
	char			str[1024] ;
	int				len ;
	int				ret ;

	if(m_bErrorLog == true)
	{
		ret = fopen_s(&m_pErrLogFile, &m_cErrLogFileName[0], "a+") ;
		if(ret)	return ret ;

		fseek(m_pErrLogFile , 0 , SEEK_END) ;
		
		nowTime = time(NULL) ;
		localtime_s(&timeinfo, &nowTime) ;
	
		fprintf_s(m_pErrLogFile, "%d%.2d%.2d_%.2d:%.2d:%.2d", timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday,
				timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec) ; 
	
		va_start(ap, szStr) ;
		vsprintf_s(buffer, szStr, ap) ; 
		va_end(ap) ;

		len = sprintf_s(str, 1024, ": %s\r\n", buffer) ;	
	
		fwrite(&str[0], 1, len, m_pErrLogFile) ;
		fclose(m_pErrLogFile) ;
	}
	
	return 0 ;
}
// ini parser
int	CPciExpWrapper::INI_GetI2cSlaveAddr(char *fileName, unsigned char *cSlaveAddr) {
	unsigned int	slaveAddr;
	char			line[256], test[64];
	char			*cRet;
	FILE			*fp;
	char			*p;

	fp = fopen(fileName, "rt");
	if (fp == NULL)	return 3;	// file open error
	memset(test, 0, 64);
	
	for (;;) {
		cRet = fgets(line, 256, fp);
		if (cRet == NULL)	{
			if (fp != NULL) fclose(fp);
			return 1;
		}
		p = strtok (line, " \t");
		if (p != NULL && ((*p != '/')&&(*(p+1)!='/')) && *p != '\n')
		{
			memcpy(test, p, 20);
			strupr(test);
			if (! strcmp (test, "HVS_SENSOR_SLAVEADDR")) {
				memcpy(test, p, 32);
				strupr(test);
				sscanf(test, "HVS_SENSOR_SLAVEADDR=0X%x", &slaveAddr);
				*cSlaveAddr = slaveAddr&0x7f;
				if (fp != NULL) fclose(fp);
				return 0;
			}
			// 20140304 봉 추가
			memcpy(test, p, 20);
			strupr(test);
			if (! strcmp (test, "OIS_SENSOR_SLAVEADDR")) {
				memcpy(test, p, 32);
				strupr(test);
				sscanf(test, "OIS_SENSOR_SLAVEADDR=0X%x", &slaveAddr);
				*cSlaveAddr = slaveAddr&0x7f;
				if (fp != NULL) fclose(fp);
				return 0;
			}
			memcpy(test, p, 20);
			strupr(test);
			if (! strcmp (test, "PRI_SENSOR_SLAVEADDR")) {
				memcpy(test, p, 32);
				strupr(test);
				sscanf(test, "PRI_SENSOR_SLAVEADDR=0X%x", &slaveAddr);
				*cSlaveAddr = slaveAddr&0x7f;
				if (fp != NULL) fclose(fp);
				return 0;
			}
		}
	}
	if (fp != NULL) fclose(fp);
	return 0x2;
}


int	CPciExpWrapper::INI_GetImgResolution(char *fileName, int *nWidth, int *nHeight, int *SensorFormat) {
	unsigned int	width, height, sformat;
	char			line[256], test[64];
	char			*cRet;
	FILE			*fp;
	char			*p;
	int				nFlag=0;

	fp = fopen(fileName, "rt");

	if (fp == NULL)	return 3;	// file open error
	memset(test, 0, 64);

	for (;;) {
		cRet = fgets(line, 256, fp);
		if (cRet == NULL)	{
			if (fp != NULL) fclose(fp);
			return 1;
		}
		p = strtok (line, " \t");
		if (p != NULL && ((*p != '/')&&(*(p+1)!='/')) && *p != '\n')
		{
			memset(test, 0, 64);
			memcpy(test, p, 17);
			strupr(test);
			if (! strcmp (test, "HVS_SENSOR_SIZE_X")) {
				memcpy(test, p, 32);
				strupr(test);
				sscanf(test, "HVS_SENSOR_SIZE_X=%d", &width);
				nFlag |= 0x1;
			}
			memset(test, 0, 64);
			memcpy(test, p, 17);
			strupr(test);
			if (! strcmp (test, "HVS_SENSOR_SIZE_Y")) {
				memcpy(test, p, 32);
				strupr(test);
				sscanf(test, "HVS_SENSOR_SIZE_Y=%d", &height);
				nFlag |= 0x2;
			}
			memset(test, 0, 64);
			memcpy(test, p, 22);
			strupr(test);
			if (! strcmp (test, "HVS_SENSOR_DATA_FORMAT")) {
				memcpy(test, p, 32);
				strupr(test);
				sscanf(test, "HVS_SENSOR_DATA_FORMAT=%d", &sformat);
				nFlag |= 0x4;
			}
			memset(test, 0, 64);

			// 20140304 봉 추가
			memset(test, 0, 64);
			memcpy(test, p, 17);
			strupr(test);
			if (! strcmp (test, "OIS_SENSOR_SIZE_X")) {
				memcpy(test, p, 32);
				strupr(test);
				sscanf(test, "OIS_SENSOR_SIZE_X=%d", &width);
				nFlag |= 0x1;
			}
			memset(test, 0, 64);
			memcpy(test, p, 17);
			strupr(test);
			if (! strcmp (test, "OIS_SENSOR_SIZE_Y")) {
				memcpy(test, p, 32);
				strupr(test);
				sscanf(test, "OIS_SENSOR_SIZE_Y=%d", &height);
				nFlag |= 0x2;
			}
			memset(test, 0, 64);
			memcpy(test, p, 22);
			strupr(test);
			if (! strcmp (test, "OIS_SENSOR_DATA_FORMAT")) {
				memcpy(test, p, 32);
				strupr(test);
				sscanf(test, "OIS_SENSOR_DATA_FORMAT=%d", &sformat);
				nFlag |= 0x4;
			}
			memset(test, 0, 64);
			memcpy(test, p, 17);
			strupr(test);
			if (! strcmp (test, "PRI_SENSOR_SIZE_X")) {
				memcpy(test, p, 32);
				strupr(test);
				sscanf(test, "PRI_SENSOR_SIZE_X=%d", &width);
				nFlag |= 0x1;
			}
			memset(test, 0, 64);
			memcpy(test, p, 17);
			strupr(test);
			if (! strcmp (test, "PRI_SENSOR_SIZE_Y")) {
				memcpy(test, p, 32);
				strupr(test);
				sscanf(test, "PRI_SENSOR_SIZE_Y=%d", &height);
				nFlag |= 0x2;
			}
			memset(test, 0, 64);
			memcpy(test, p, 22);
			strupr(test);
			if (! strcmp (test, "PRI_SENSOR_DATA_FORMAT")) {
				memcpy(test, p, 32);
				strupr(test);
				sscanf(test, "PRI_SENSOR_DATA_FORMAT=%d", &sformat);
				nFlag |= 0x4;
			}
		}
		if (nFlag == 0x7) {
			SensorFormat[0]		= sformat;
			nWidth[0] = width;
			nHeight[0] = height;
			if (fp != NULL) fclose(fp);
			return 0;
		}
	}
	if (fp != NULL) fclose(fp);
	return 0x2;
}

int	CPciExpWrapper::INI_GetI2cCommands(char *fileName, unsigned char sensorID, I2C_CMD_LIST *cmdPtr, int nMaxCmd) {

	char			line[256], test[64];
	char			*cRet;
	FILE			*fp;
	char			*p;
	int				nFlag=0;
	unsigned int	currentID;
	unsigned int	addr, wrval;
	int				curIndex;
	int				nSleepTime;
	unsigned int	i2cMode ;	// 20140204 16M 추가

	fp = fopen(fileName, "rt");

	if (fp == NULL)	return 3;	// file open error
	memset(test, 0, 64);
	memset(cmdPtr, 0, sizeof(I2C_CMD_LIST)*nMaxCmd);
	curIndex = 0;

	for (;;) {
		cRet = fgets(line, 256, fp);
		if (cRet == NULL) {
			if (fp != NULL) fclose(fp);
			return curIndex;
		}
		p = strtok (line, " \t");
		if (p != NULL && ((*p != '/')&&(*(p+1)!='/')) && *p != '\n')
		{
 			strupr(p);
			if (! strcmp (p, "SLAVE")) {
				currentID = 0;
				p = strtok(NULL, " \t");
				strupr(p);
				sscanf(p, "0X%x", &currentID);
			}
			// 20140204 16M 추가
			else if (! strcmp (p, "I2CMODE")) {
				i2cMode = 2 ;	// default : reg 2, data 1
				p = strtok(NULL, " \t");
				strupr(p);
				sscanf(p, "%d", &i2cMode);
			}
			// 20140204 16M 추가 end
			else if (((*p=='0')&&(*(p+1)=='X'))&&(currentID == sensorID)) {
				wrval	= 0xffffffff;
				addr	= 0xffffffff;
				sscanf(p, "0X%x", &addr);
				p = strtok(NULL, " \t");
				strupr(p);
				sscanf(p, "0X%x", &wrval);
				if ((addr != 0xffffffff)&&(wrval!=0xffffffff)) {
					cmdPtr[curIndex].cSlaveID	= currentID;
					cmdPtr[curIndex].snAddr		= addr;
					cmdPtr[curIndex].cWriteVal	= wrval;
					cmdPtr[curIndex].nI2cMode	= i2cMode ;	// 20140204 16M 추가
					curIndex++;
				}
			}
			else if ((!strcmp (p, "SLEEP"))&&(currentID == sensorID)) {
				p = strtok(NULL, " \t");
				nSleepTime = 0;
				sscanf(p, "%d", &nSleepTime);
				if (nSleepTime != 0) {
					cmdPtr[curIndex].cSlaveID	= 0xff;
					cmdPtr[curIndex].snAddr		= nSleepTime;
					cmdPtr[curIndex].cWriteVal	= 0;
					curIndex++;
					if (curIndex == nMaxCmd) {
						if (fp != NULL) fclose(fp);
						return nMaxCmd;
					}
				}
			}
		}

	}
	if (fp != NULL) fclose(fp);
	return 0xffffffff;

//	return 0x2;
}
int CPciExpWrapper::DS90UB914A_Init(){

	unsigned char		addr;
	unsigned short		regaddr;
	unsigned int		cWriteVal ;
	int					data;
	int					ret= 0;

	addr = 0x60;
	regaddr = 0x07; cWriteVal = 0xb4;
	ret |= CM_I2CBurstWrite(0, 1, 1, addr, regaddr, (int*)&cWriteVal, 1) ;
	Sleep (10);

	regaddr = 0x08; cWriteVal = 0x20;
	ret |= CM_I2CBurstWrite(0, 1, 1, addr, regaddr, (int*)&cWriteVal, 1) ;
	Sleep (10);

	regaddr = 0x09; cWriteVal = 0xa0;
	ret |= CM_I2CBurstWrite(0, 1, 1, addr, regaddr, (int*)&cWriteVal, 1) ;
	Sleep (10);

	regaddr = 0x10; cWriteVal = 0x20;
	ret |= CM_I2CBurstWrite(0, 1, 1, addr, regaddr, (int*)&cWriteVal, 1) ;
	Sleep (10);

	regaddr = 0x11; cWriteVal = 0xa0;
	ret |= CM_I2CBurstWrite(0, 1, 1, addr, regaddr, (int*)&cWriteVal, 1) ;
	Sleep (10);

	regaddr = 0x43; cWriteVal = 0x37;
	ret |= CM_I2CBurstWrite(0, 1, 1, addr, regaddr, (int*)&cWriteVal, 1) ;
	Sleep (10);

	return ret;
}

int CPciExpWrapper::GEELY_Sony_Avm_Reset(){
	CM_RegisterWrite(ADDR_CAROPTIC_SENSOR_RST,0);
	Sleep (500);
	CM_RegisterWrite(ADDR_CAROPTIC_SENSOR_RST,1);	
	return 0;
}


int CPciExpWrapper::AR0132_ReadOTPM(unsigned int* Rcvdata){
	unsigned char		addr;
	unsigned short		regaddr;
	unsigned int		cWriteVal ;
	int					data;
	

	addr = 0x10;

	regaddr = 0x301a; cWriteVal = 0x10d8;
	CM_I2CBurstWrite(0, 2, 2, addr, regaddr, (int*)&cWriteVal, 1) ;
	Sleep (10);

	regaddr = 0x304c; cWriteVal = 0x60;
	CM_I2CBurstWrite(0, 2, 2, addr, regaddr, (int*)&cWriteVal, 1) ;
	Sleep (10);

	regaddr = 0x304a; cWriteVal = 0x200;
	CM_I2CBurstWrite(0, 2, 2, addr, regaddr, (int*)&cWriteVal, 1) ;
	Sleep (10);
	
	regaddr = 0x304a; cWriteVal = 0x210;
	CM_I2CBurstWrite(0, 2, 2, addr, regaddr, (int*)&cWriteVal, 1) ;
	

	regaddr = 0x3800; cWriteVal = 0x210;
	CM_I2CBurstRead(0, 2, 2, addr, regaddr, &data, 1) ;
	Rcvdata[0] = data;

	regaddr = 0x3802; cWriteVal = 0x210;
	CM_I2CBurstRead(0, 2, 2, addr, regaddr, &data, 1) ;
	Rcvdata[1] = data;

	regaddr = 0x3804; cWriteVal = 0x210;
	CM_I2CBurstRead(0, 2, 2, addr, regaddr, &data, 1) ;
	Rcvdata[2] = data;

	regaddr = 0x3806; cWriteVal = 0x210;
	CM_I2CBurstRead(0, 2, 2, addr, regaddr, &data, 1) ;
	Rcvdata[3] = data;

	regaddr = 0x3808; cWriteVal = 0x210;
	CM_I2CBurstRead(0, 2, 2, addr, regaddr, &data, 1) ;
	Rcvdata[4] = data;

	regaddr = 0x380a; cWriteVal = 0x210;
	CM_I2CBurstRead(0, 2, 2, addr, regaddr, &data, 1) ;
	Rcvdata[5] = data;

	regaddr = 0x380c; cWriteVal = 0x210;
	CM_I2CBurstRead(0, 2, 2, addr, regaddr, &data, 1) ;
	Rcvdata[6] = data;

	regaddr = 0x380e; cWriteVal = 0x210;
	CM_I2CBurstRead(0, 2, 2, addr, regaddr, &data, 1) ;
	Rcvdata[7] = data;

	return 0;
}

// ois innotek 함수들, ois 용 말고는 사용하지 말것
int CPciExpWrapper::SetWrapperInstance(int nBoard, CPciExpWrapper *wrapper, int para, bool bErrorLog)
{
	if		(nBoard == 0)	g_wrapper[0] = wrapper ;
	else if	(nBoard == 1)	g_wrapper[1] = wrapper ;
	else if	(nBoard == 2)	g_wrapper[2] = wrapper ;
	else if	(nBoard == 3)	g_wrapper[3] = wrapper ;
	
	SetErrLog(para, bErrorLog) ;

	return 0 ;
}
BOOL CPciExpWrapper::TWI_WriteMultipleA(int nSlvAddr, unsigned char *data, int len)
{
	int				buf[256] ;
	int				address ;
	int				i, j ;
	int				ret ;
	int				rdData[256] ;
	unsigned char	rd[256] ;
	int				checkOK ;

	address = ( (int)data[1] & 0xff) | ( ( (int)data[0] << 8) & 0xff00 ) ;
	
	for(i=0 ; i<len-2 ; i++) 
	{
		buf[i] = (int)data[i+2] & 0xff ;
	}	
	ret = CM_I2CBurstWrite(0, 2, 1, nSlvAddr, address, &buf[0], len-2) ;
	if(ret)		return FALSE ;
	
	return TRUE ;	
}
BOOL CPciExpWrapper::TWI_ReadMultipleIadrA(int nSlvAddr, int len, int addr, int addrLn, unsigned char *data)
{
	int		ret ;
	int		rdData[512] ;

	ret = CM_I2CBurstRead(0, addrLn, 1, nSlvAddr, addr,&rdData[0], len) ;
	if(ret)		return FALSE ;	
	
	for(int i=0 ; i<len ; i++)
	{
		*data++ = (unsigned char)rdData[i] & 0xff ;
	}
	return TRUE ;
}
BOOL CPciExpWrapper::E2P_WriteSingleIadrA(int nSlvAddr, int addr, unsigned char data)
{
	int		ret ;
	int		wrData ;

	wrData = (int)data & 0xff ;
	ret = CM_I2CBurstWrite(0, 2, 1, nSlvAddr, addr, &wrData, 1) ;
	if(ret)		return FALSE ;
	Sleep(10) ;
	
	return TRUE ;
}
// len 에 무조건 1을 넣어야지 정상동작, addLn 사용하지 않음..
BOOL CPciExpWrapper::E2P_ReadSingleIadrA(int nSlvAddr, int len, int addr, int addrLn, unsigned char *data)
{
	int		ret ;
	int		rdData ;
		

	ret = CM_I2CBurstRead(0, addrLn, 1, nSlvAddr, addr, &rdData, len) ;
	if(ret)		return FALSE ;
	
	*data = (unsigned char)rdData & 0xff ;
	return TRUE ;
}
int GetFrameCount(void)
{
	int		grabCount;
	
	if(g_wrapper[0] == NULL)	return 0 ;
	
	g_wrapper[0]->CM_ChkGrabDone(&grabCount) ;
	
	return grabCount ;
}
BOOL I2CWrite(int nRegAddrSize, int nDataSize, int nSlaveAddr, int nRegAddr, int *pData, int nDataLength)
{
	int ret = 1 ;
	
	if(g_wrapper[0] == NULL)	return FALSE ;
	
	ret = g_wrapper[0]->CM_I2CBurstWrite(0, nRegAddrSize, nDataSize, nSlaveAddr, nRegAddr, pData, nDataLength) ;
	
	return (ret == 0) ? TRUE : FALSE ;
}
BOOL I2CRead(int nRegAddrSize, int nDataSize, int nSlaveAddr, int nRegAddr, int *pData, int nDataLength)
{
	int ret = 1 ;
	
	if(g_wrapper[0] == NULL)	return FALSE ;
	
	ret = g_wrapper[0]->CM_I2CBurstRead(0, nRegAddrSize, nDataSize, nSlaveAddr, nRegAddr, pData, nDataLength) ;

	return (ret == 0) ? TRUE : FALSE ;
}
BOOL TWI_WriteMultiple(int nSlvAddr, unsigned char *data, int len)
{	
	if(g_wrapper[0] == NULL)	return FALSE ;	
	return g_wrapper[0]->TWI_WriteMultipleA(nSlvAddr, data, len) ;
}
BOOL TWI_ReadMultipleIadr(int nSlvAddr, int len, int addr, int addrLn, unsigned char *data)
{
	if(g_wrapper[0] == NULL)	return FALSE ;
	return g_wrapper[0]->TWI_ReadMultipleIadrA(nSlvAddr, len, addr, addrLn, data) ;
}
BOOL E2P_WriteSingleIadr(int  SlvAddr, int addr, unsigned char data)
{
	if(g_wrapper[0] == NULL)	return FALSE ;
	return g_wrapper[0]->E2P_WriteSingleIadrA(SlvAddr, addr, data) ;
}
BOOL E2P_ReadSingleIadr(int nSlvAddr, int len, int addr, int addrLn, unsigned char *data)
{
	if(g_wrapper[0] == NULL)	return FALSE ;
	return g_wrapper[0]->E2P_ReadSingleIadrA(nSlvAddr, len, addr, addrLn, data) ;
}

int	CPciExpWrapper::CM_SetVoltage_LKAS(int iChannel, float fVoltage)
{
	float		targetVol ;
	int			txData ;
	int			ret ;
	float		vol1, vol2, vol3, vol4 ;
	float		vol_err ;
	int slaveAddr;
	int data;

	int	temp_mul; 
	
	if( (iChannel < POWER_LKAS_CH1) || (iChannel > POWER_LKAS_CH4) )	return PWR_RET_BIT_RANGE_ERR ;
	
	
	if(fVoltage > CM_VLATAGE_MAX)		fVoltage = CM_VLATAGE_MAX ;
	else if(fVoltage < CM_VLATAGE_MIN)	fVoltage = CM_VLATAGE_MIN ;


	if (iChannel == POWER_LKAS_CH1)	slaveAddr = 0x18;
	else if (iChannel == POWER_LKAS_CH2)	slaveAddr = 0x19;
	else if (iChannel == POWER_LKAS_CH3)	slaveAddr = 0x1a;
	else if (iChannel == POWER_LKAS_CH4)	slaveAddr = 0x1b;

	

	temp_mul = 0xbf - (((fVoltage+0.001) / 0.05 ) - 11);

	
//	ret = CM_WritePWI2C(1, 1, slaveAddr,regAddr, &data, 1);
	ret = CM_WritePWI2C(1, 1, slaveAddr,0x01, 0, 1);
	Sleep(100);
	ret = CM_WritePWI2C(1, 1, slaveAddr,0x02, 0, 1);
	Sleep(100);
	ret = CM_WritePWI2C(1, 1, slaveAddr,0x03, 0xff, 1);
	Sleep(100);
	ret = CM_WritePWI2C(1, 1, slaveAddr,0x03, temp_mul, 1);

	

	////////////////////////

	
	return ret ;
	
	/*
	int			txData ;
	float		vrVal ;
	int			rstep ;
	int			lRet ;

	if(fVoltage > CM_VLATAGE_MAX)
	{
		fVoltage = CM_VLATAGE_MAX ;
	}
	else if(fVoltage < CM_VLATAGE_MIN)
	{
		fVoltage = CM_VLATAGE_MIN ;
	}
		
	vrVal = 25000.0 * (fVoltage / 0.8 - 1.0) ;
	rstep = (int)(vrVal * 256.0 / 100000.0) ;
	if(rstep >= 0xff)	rstep = 0xff ;

	if(iChannel == POWER_CH1)		txData = 0x00A60000 ;
	else if(iChannel == POWER_CH2)	txData = 0x00A60100 ;
	else if(iChannel == POWER_CH3)	txData = 0x00A00000 ;
	else if(iChannel == POWER_CH4)	txData = 0x00A00100 ;
	else if(iChannel == POWER_LED)	txData = 0x00A80000 ;
	else							txData = 0x00A60000 ;

	txData = txData | (rstep & 0x000000ff) ;
	
	lRet = CM_RegisterWrite(ADDR_PWR_I2C_WR, txData) ;

	return lRet;
	*/
}

int	CPciExpWrapper::CM_WritePWI2C(int nRegAddrSize, int nDataSize, int nSlaveAddr, int nRegAddr, int pData, int nDataLength)
{
	int		i ;
	int		dataBuf[256] ;
	int		threadId ;
	int		ramClear ;
	int		ret ;
	int		resCheck ;
	int		startTime ;
	int		endTime ;
	int		limitTime ;	
	int		errorCount ;
	int		rdDataH, rdDataL ;


	i=0;
	threadId = 0 ;

	if(nDataLength > 0xff)				nDataLength = 0xff ;
	// data copy
	//	for(i=0 ; i<nDataLength ; i++)		dataBuf[i] = *pData++ ;
	dataBuf[0] = pData ;
	// clear ram buf

	// put data
	for(int i=0 ; i<nDataLength ; i++)
	{
		ret = CM_SetPWI2CData(nRegAddr, dataBuf[i]) ;
		if(ret != I2C_RET_OK)
		{
			gPWI2CWriteRetInfo[gI2CWriteTryNum][threadId] = I2C_RET_COM_ERR ;
			I2CErrLogWrite("Write:IFComErr:SetI2cData: SAddr:%x RegAddr:%x ThreadId:%x Data:%x", nSlaveAddr, nRegAddr, i, dataBuf[i]) ;
			::LeaveCriticalSection(&m_csI2C) ;
			return I2C_RET_COM_ERR ;
		}
		Sleep(SRIO_RESP_DLY) ;	
	}
	// put cmd	
	ret = CM_SetPWI2CCommand(I2C_CMD_NORMAL_I2C, threadId, I2C_CMD_WRITE, nRegAddrSize, nDataSize, nSlaveAddr, nDataLength) ;
	if(ret != I2C_RET_OK)
	{
		gPWI2CWriteRetInfo[gI2CWriteTryNum][threadId] = I2C_RET_COM_ERR ;
		I2CErrLogWrite("Write:IFComErr:SetI2cCmd: SAddr:%x RegAddr:%x ThreadId:%x", nSlaveAddr, nRegAddr, i) ;
		::LeaveCriticalSection(&m_csI2C) ;
		return I2C_RET_COM_ERR ;
	}
	// wait response
	errorCount = 0 ;
	for(i=0 ; i<nDataLength ; i++)
	{
		Sleep(SRIO_RESP_DLY) ;
		startTime = GetTickCount() ;
		while(1)
		{
			resCheck = CM_GetPWI2CResponse(threadId, &rdDataH, &rdDataL) ;
			if(resCheck == I2C_RET_ACK_SUCCESS) 
			{
				gPWI2CWriteRetInfo[gI2CWriteTryNum][threadId] = I2C_RET_ACK_SUCCESS ;
				threadId++ ;				
				nRegAddr++ ;
				break ;
			}
			else if(resCheck == I2C_RET_CMD_ERR)
			{				
				gPWI2CWriteRetInfo[gI2CWriteTryNum][threadId] = I2C_RET_CMD_ERR ;
				I2CErrLogWrite("Write:WrongCmdErr: cmdtype:%x ThreadId:%x RdWr:%x RegAddrSize:%x DataSize:%x SAddr:%x DataLength:%x",
					I2C_CMD_NORMAL_I2C, threadId, I2C_CMD_WRITE, nRegAddrSize, nDataSize, nSlaveAddr, nDataLength) ;
				I2CErrLogWrite("Write:WrongCmdErrData: RegAddr:%x WrData:%x ErrCode:%x",
					nRegAddr, dataBuf[i], (BYTE)( (resCheck >> 24) & 0x0ff) ) ;
				I2CErrLogWrite("Write:ResponseData: %.8x %.8x", rdDataH, rdDataL) ;				

				::LeaveCriticalSection(&m_csI2C) ;
				return I2C_RET_CMD_ERR ;
			}
			else if(resCheck == I2C_RET_DATA_ERR)
			{
				gPWI2CWriteRetInfo[gI2CWriteTryNum][threadId] = I2C_RET_DATA_ERR ;
				I2CErrLogWrite("Write:WrongDataErr: cmdtype:%x ThreadId:%x RdWr:%x RegAddrSize:%x DataSize:%x SAddr:%x DataLength:%x",
					I2C_CMD_NORMAL_I2C, threadId, I2C_CMD_WRITE, nRegAddrSize, nDataSize, nSlaveAddr, nDataLength) ;
				I2CErrLogWrite("Write:WrongDataErrData: RegAddr:%x WrData:%x ErrCode:%x",
					nRegAddr, dataBuf[i], (BYTE)( (resCheck >> 24) & 0x0ff) ) ;
				I2CErrLogWrite("Write:ResponseData: %.8x %.8x", rdDataH, rdDataL) ;

				::LeaveCriticalSection(&m_csI2C) ;
				return I2C_RET_DATA_ERR ;
			}
			else if(resCheck == I2C_RET_BUS_BUSY_ERR)
			{
				gPWI2CWriteRetInfo[gI2CWriteTryNum][threadId] = I2C_RET_BUS_BUSY_ERR ;
				I2CErrLogWrite("Write:BusBusyErr: SAddr:%x RegAddr:%x ThreadId:%x WrData:%x ErrCode:%x",
					nSlaveAddr, nRegAddr, threadId, dataBuf[i], (BYTE)( (resCheck >> 24) & 0x0ff) ) ;
				I2CErrLogWrite("Write:ResponseData: %.8x %.8x", rdDataH, rdDataL) ;

				::LeaveCriticalSection(&m_csI2C) ;
				return I2C_RET_BUS_BUSY_ERR ;
			}
			else if( (resCheck == I2C_RET_ACK_ERR_SLAVE) || (resCheck == I2C_RET_ACK_ERR_REG1) || (resCheck == I2C_RET_ACK_ERR_REG2) || 
				(resCheck == I2C_RET_ACK_ERR_DATA1) || (resCheck == I2C_RET_ACK_ERR_DATA2) || 
				(resCheck == I2C_RET_ACK_ERR_DATA3) || (resCheck == I2C_RET_ACK_ERR_DATA4) )
			{
				I2CErrLogWrite("Write:AckErr: SAddr:%x RegAddr:%x ThreadId:%x WrData:%x ErrCode:%x",
					nSlaveAddr, nRegAddr, threadId, dataBuf[i], (BYTE)( (resCheck >> 24) & 0x0ff) ) ;
				I2CErrLogWrite("Write:ResponseData: %.8x %.8x", rdDataH, rdDataL) ;

				gPWI2CWriteRetInfo[gI2CWriteTryNum][threadId] = resCheck ;
				threadId++ ;
				errorCount++ ;				
				nRegAddr++ ;
				break ;
			}	
			endTime = GetTickCount() ;
			limitTime = endTime - startTime ;			
			if(limitTime > I2C_TIME_LIMIT)
			{
				I2CErrLogWrite("Write:TimerOutErr: SAddr:%x RegAddr:%x ThreadId:%x WrData:%x",
					nSlaveAddr, nRegAddr, threadId, dataBuf[i]) ;

				gPWI2CWriteRetInfo[gI2CWriteTryNum][threadId] = I2C_RET_TIMEOUT_ERR ;
				threadId++ ;
				errorCount++ ;
				nRegAddr++ ;
				break ;
			}	
		}
	}

	return errorCount ;
}

int CPciExpWrapper::CM_SetPWI2CData(int nRegAddr, int nData)
{
	int		addr[2] ;
	int		data[2] ;
	int		ret ;

	addr[1] = 0 ;
	addr[0] = ADDR_PW_I2C_DATA_WR ;
	data[1] = I2C_DATA_CODE | (nRegAddr & 0x0000ffff) ;
	data[0] = nData ;

	ret = gp_clsPCIExpress->srio_nwrite(0, addr, 8, data) ;
	if(ret)		return I2C_RET_COM_ERR ;

	return I2C_RET_OK ;
}
int CPciExpWrapper::CM_SetPWI2CCommand(int nCmdType, int nThreadId, bool bIsRead, int nRegAddrSize, int nDataSize, int nSlaveAddr, int nDataLength)
{	
	int		isBurst ;
	int		isRead ;
	int		regAddrSize ;
	int		dataSize ;
	int		dataLength ;
	int		threadId ;
	int		slaveAddr ;
	int		cmdType ;
	int		cmdData ;
	int		addr[2] ;
	int		data[2] ;
	int		ret ;

	// cmd fifo : 8 byte	
	// 1 byte - 7:0 bit	: cmd code high
	// 2 byte - 7:0 bit	: cmd code low
	// 3 byte - 7:0 bit	: reser.
	// 4 byte - 7:0 bit	: cmd type
	// 5 byte - 7 bit	: 0->single, 1->burst
	// 5 byte - 6 ibt	: 0->wr, 1->rd
	// 5 byte - 5:4 bit	: reg size
	// 5 byte - 3:0 bit	: data size
	// 6 byte - 7:0 bit	: data length for burst
	// 7 byte - 7:0 bit	: thread ID
	// 8 byte - 7 bit	: reserve
	// 8 byte - 6:0 bit	: slave address

	isBurst		= 0x80000000 ;
	isRead		= (bIsRead == 1) ? 0x40000000 : 0x0 ;
	regAddrSize	= (nRegAddrSize << 28) & 0x30000000 ;
	dataSize	= (nDataSize << 24) & 0x07000000 ;
	dataLength	= (nDataLength << 16) & 0xff0000 ;
	threadId	= (nThreadId << 8) & 0xff00 ;
	slaveAddr	= nSlaveAddr & 0x07f ;

	cmdType = I2C_CMD_CODE | (nCmdType & 0x0000ffff) ;
	cmdData = 0 ;
	cmdData = isBurst | isRead | regAddrSize | dataSize | dataLength | threadId | slaveAddr ;

	addr[1] = 0 ;
	addr[0] = ADDR_PW_I2C_CMD_WR ;	
	data[1] = cmdType ;
	data[0] = cmdData ;	

	ret = gp_clsPCIExpress->srio_nwrite(0, addr, 8, data) ;
	if(ret)		return I2C_RET_COM_ERR ;

	return I2C_RET_OK ;
}
int CPciExpWrapper::CM_GetPWI2CResponse(int nThreadId, int *pRdDataH, int *pRdDataL)
{
	int		resData[2] ;
	int		ret ;

	ret = CM_CheckReadDone(SRIO_BUF_NUM_GPIO, nThreadId, &resData[0]) ;
	if(ret)		return I2C_RET_COM_ERR ;

	*pRdDataH = resData[0] ;
	*pRdDataL = resData[1] ;

	return (resData[0] & 0xFF000000) ;
}

/*
int CPciExpWrapper::CM_PWI2CGetWriteResult(tagI2C_RESULT *pBufPoint)
{
	memcpy(pBufPoint, &gPWI2CWriteRetInfo[0][0], 3 * 256 * 4) ;

	return 0 ;	
}
int CPciExpWrapper::CM_PWI2CGetReadResult(tagI2C_RESULT *pBufPoint)
{
	memcpy(pBufPoint, &gPWI2CReadRetInfo[0][0], 3 * 256 * 4) ;

	return 0 ;	
}*/
/////////////////////////////////////////////////

int CPciExpWrapper::UART_Tx_Send(int data)
{
	CM_RegisterWrite(ADDR_UART_TX, (__int64)data );
	return 0;
}

int CPciExpWrapper::UART_Rx_Rcv(void)
{
	__int64 RcvData;

	CM_RegisterRead(ADDR_UART_RES_STAT, &RcvData);
	if ( ( RcvData & 0x100000000 ) >>32 == 1 ) return -1;
	else CM_RegisterRead(ADDR_UART_RX, &RcvData);

	return (int)RcvData ;
}

int CPciExpWrapper::SetVHsyncReverse(int value)
{
#define ADDR_UART_TX			0x850
#define ADDR_UART_RX			0x860
#define ADDR_UART_RES_STAT		0x870
#define ADDR_VHSYNC_REVERSE		0x090

	CM_RegisterWrite(ADDR_VHSYNC_REVERSE, (__int64)value );
	return 0;
}
