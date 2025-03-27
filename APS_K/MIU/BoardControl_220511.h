#pragma once

#include <string>

#define BOARD_SUCCESS				(0)
#define ERR_BOARD_GET_LIST			(1)
#define ERR_BOARD_NO_DEVICE			(2)
#define ERR_BOARD_OPEN				(3)
#define ERR_BOARD_INIT				(4)
#define ERR_BOARD_SET_POWER_5_12	(5)
#define ERR_BOARD_GRAB_START		(6)
#define ERR_BOARD_I2C_WRITE			(7)
#define ERR_BOARD_I2C_READ			(8)
#define ERR_BOARD_BOOT_CAMERA		(9)
#define ERR_BOARD_CLOSE				(10)
#define ERR_BOARD_LOAD_MODEL		(11)
#define ERR_BOARD_CURRENT_MODE		(12)
#define ERR_BOARD_CURRENT_RESULT	(13)

#define USB_EVENT_TIMEOUT			0x0000F001
#define	USB_EVENT_ATTACHED			0x0000F002
#define USB_EVNET_DETACHED			0x0000F003

typedef enum _BOARDTYPE
{
    BOARD_TYPE_LAON,
    BOARD_TYPE_POWER
} BOARDTYPE;

typedef   void   (CALLBACK   *EventCallback)(char, int);

class IBoardControl
{
public:
    IBoardControl() : m_bGrabStarted(false), m_nFrameRawSize(0)
    {
    }
    virtual ~IBoardControl(void) {}

    virtual int OpenBoard(char cBoardIndex) = 0;

    virtual int CloseBoard() = 0;

    virtual bool IsConnected() = 0;

    virtual int GrabStart() = 0;

    virtual void GrabStop() = 0;

    bool IsGrabStarted() const { return m_bGrabStarted; }

    virtual bool GetFrame(BYTE* pFrameRawBuffer, BYTE* pFrameBMPBuffer) = 0;

    virtual void GetFrameToBMP(BYTE* pFrameRawBuffer, BYTE* pFrameBMPBuffer) = 0;

    virtual bool ParseRegisterFile(const char* pszCmd) = 0;

    virtual bool PowerControl(bool bOnOff = false) = 0;

    int GetFrameRawSize() { return m_nFrameRawSize; }

    int GetFrameBMPSize() { return GetWidth() * GetHeight() * 3; }

    virtual int GetWidth() = 0;

    virtual int GetHeight() = 0;

    virtual int GetDataFormat() = 0;

    virtual int GetOutMode() = 0;

    virtual int GetSensorType() = 0;

    virtual bool BootCamera() = 0;

    virtual void SetINIFile(const char* pszIniFile) = 0;

    virtual int WriteI2CBurst(unsigned short nSlaveAddr, unsigned short nAddr, unsigned char nAddrByteCount, unsigned char* pData, unsigned short nWriteByteCount) = 0;

    virtual int ReadI2CBurst(unsigned short nSlaveAddr, unsigned short nAddr, unsigned char nAddrByteCount, unsigned char* pData, unsigned short nReadByteCount) = 0;

    virtual int WriteI2CMultiAddrBurst(unsigned short nSlaveAddr, unsigned short* nAddr, unsigned char nAddrByteCount, unsigned char* pData, unsigned short nWriteByteCount) = 0;

    virtual int ReadI2CMultiAddrBurst(unsigned short nSlaveAddr, unsigned short* nAddr, unsigned char nAddrByteCount, unsigned char* pData, unsigned short nReadByteCount) = 0;

    virtual int SetVirtualChannel(unsigned short cVCIndex) = 0;

    virtual int GetVirtualChannel(unsigned short* cVCIndex) = 0;

    virtual int SetISPControl(unsigned short nISPValue, bool on) = 0;

    virtual float GetSensorFrameRate() = 0;

    virtual int GetCurrentMeasure(double currentValue[5]) = 0;

    virtual void SetBrightestPoint(bool bOnOff, bool bOverlay, int nThreshold) = 0;

    virtual bool GetBrightestPoint(double &dX, double &dY) = 0;

    // Model Specific APIs
    // GET APIs
    virtual int GetHWVersion(unsigned char* retValue) = 0;
    virtual int GetModelType(unsigned char* retValue) = 0;
    virtual int GetIntrinsicData(unsigned char* retValue) = 0;
    virtual int GetPartNumber(unsigned char* retValue) = 0;
    virtual int GetCalValueOfOpticAxis(unsigned char* retValue) = 0;
    virtual int GetAECData(unsigned char* retValue) = 0;

    virtual int GetSWVersion(unsigned char* retValue) = 0;
    virtual int GetISPVersion(unsigned char* retValue) = 0;

    virtual int GetSensorID(unsigned char* retValue) = 0;
    virtual int GetOTPData(unsigned char* retValue) = 0;

    virtual int GetGeelyPartNumber(unsigned char* retValue) = 0;
    virtual int GetVolvoPartNumber(unsigned char* retValue) = 0;
    virtual int GetFingerprint(unsigned char* retValue) = 0;
    virtual int GetSensorLotInfo(unsigned char* retValue) = 0;
    virtual int GetBarcodeSerialNumber(unsigned char* retValue) = 0;
    virtual int GetGain(unsigned char* retValue) = 0;
    virtual int GetOcEEPROM(unsigned char* retValue) = 0;
    virtual int GetOcAfterCal(unsigned char* retValue) = 0;
    virtual int GetTypicalFocalLength(unsigned char* retValue) = 0;
    virtual bool GetCatRegister(unsigned char category, unsigned short addr, int nDataLength, unsigned char* pData) = 0;

    virtual int GetAlpha(unsigned char* retValue) = 0;
    virtual int GetCCDDummy(unsigned char* retValue) = 0;
    virtual int GetTOFReadSize(unsigned char* retValue) = 0;

    virtual int GetWPValue(unsigned char* retValue) = 0;

    // SET APIs
    virtual bool SetOTPData(int nDataLength, unsigned char* pData) = 0;

    virtual bool SetBarcodeSerialNumber(int nDataLength, unsigned char* pData) = 0;
    virtual bool SetOcSensor(int nDataLength, unsigned char* pData) = 0;
    virtual bool SetOcEEPROM(int nDataLength, unsigned char* pData) = 0;
    virtual bool SetOcAfterCal(int nDataLength, unsigned char* pData) = 0;
    virtual bool SetTypicalFocalLength(int nDataLength, unsigned char* pData) = 0;
    virtual bool SetCatRegister(unsigned char category, unsigned short addr, int nDataLength, unsigned char* pData) = 0;

    virtual bool SetAlpha(int nDataLength, unsigned char* pData) = 0;

    virtual bool SetWPEnable() = 0;
    virtual bool SetWPDisable() = 0;

    virtual void WINAPI USBCallback(EventCallback func, unsigned int WaitTime) = 0;
protected:
    bool m_bGrabStarted;
    int m_nFrameRawSize;

};

typedef IBoardControl* (*pfnGetBoardControl)(BOARDTYPE eBoardType);
typedef void(*pfnReleaseBoardControl)(IBoardControl*);


#ifdef BOARD_CONTROLLER_EXPORTS
#define BOARD_CONTROLLER_API	__declspec(dllexport)
#else
#define BOARD_CONTROLLER_API	__declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
    ///@brief Application can access this function. if application wants to access IBoardControl.
    /// please, call GetBoardControl.
    BOARD_CONTROLLER_API		IBoardControl* GetBoardControl(BOARDTYPE eBoardType = BOARD_TYPE_LAON);
    ///@brief Application must call ReleaseBoardControl when it want to release IBoardControl.
    BOARD_CONTROLLER_API		void ReleaseBoardControl(IBoardControl*);

#ifdef __cplusplus
}
#endif