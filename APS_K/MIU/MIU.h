#pragma once

//! LPMC-500 Frame Grabber 조작용 클래스
//! 1대의 LPMC-500 Frame Grabber를 조작할 수 있도록 한다.
//! Modified by LHW (2013/2/25)
//! 최종 작업일 : 2013/5/22, by LHW

#include "../stdafx.h"
#include "mil.h"
#include <cv.h>
#include <highgui.h>
#include "PixelFormat.h"
//#include "LPMC500DLLEx.h"
#include "BoardControl.h"
//
//#define RGGB	1
//#define GRBG	2
//#define GBRG	3
//#define BGGR	4
//
//#define RCCC	5
//#define CRCC	6
//#define CCRC	7
//#define CCCR	8

typedef enum IMAGE_FILE_TYPE_t {
	IMAGE_TYPE_RAW = 0,
	IMAGE_TYPE_BMP,
	IMAGE_TYPE_JPG,
	IMAGE_TYPE_AVI_BMP,
	IMAGE_TYPE_AVI_SELECT
} IMAGE_FILE_TYPE;

//! Sony, IMX135-0APH5-L, 13M, CMOS, Sensor에서 사용하는 정보 구조체
//! Sony, IMX179QQH5-C, 8M, CMOS, Sensor에서도 동일한 주소값을 가지는 것을 확인 (2013/4/23)
//! Exposure Time 관련 정보 구조체

//! Sony, IMX135-0APH5-L, 13M, CMOS, Sensor에서 사용하는 정보 구조체
//! Sony, IMX179QQH5-C, 8M, CMOS, Sensor에서도 동일한 주소값을 가지는 것을 확인 (2013/4/23)
//! Exposure Time 관련 정보 구조체
typedef struct _Info_IMX135 {
	//unsigned short iMainClock;

	char bFlag_Valid;	//! 유효한 데이터이면 '1', 그렇지 않으면 '0'

	unsigned short iPrePLLClk_OP_Div;	//! Register Address : 0x0305
	unsigned short iPLL_OP_MPY;			//! Register Address : 0x030C, 0x030D
	unsigned short iVTSYCK_Div;			//! Register Address : 0x0303
	unsigned short iVTPXCK_Div;			//! Register Address : 0x0301

	unsigned short iFrame_Length;		//! Register Address : 0x0340, 0x0341
	unsigned short iLine_Length;		//! Register Address : 0x0342, 0x0343

	unsigned short iIntegrationTime_Coarse;	//! Register Address : 0x0202, 0x0203
	unsigned short iIntegrationTime_Fine;	//! Register Address : 0x0200, 0x0201 (Read Only)

	//! 단위 us
	int iExposureTime_Min;		//! Exposure Time의 가능한 최소값
	int iExposureTime_Max;		//! Exposure Time의 가능한 최대값
	int iExposureTime_Current;	//! Exposure Time의 현재값
} Info_IMX135, *PInfo_IMX135, *LPInfo_IMX135;

typedef struct _Info_IMX247 {
	//unsigned short iMainClock;

	char bFlag_Valid;	//! 유효한 데이터이면 '1', 그렇지 않으면 '0'

	unsigned short iPrePLLClk_OP_Div;	//! Register Address : 0x0305
	unsigned short iPLL_OP_MPY;			//! Register Address : 0x030C, 0x030D
	unsigned short iVTSYCK_Div;			//! Register Address : 0x0303
	unsigned short iVTPXCK_Div;			//! Register Address : 0x0301

	unsigned short iFrame_Length;		//! Register Address : 0x0340, 0x0341
	unsigned short iLine_Length;		//! Register Address : 0x0342, 0x0343

	unsigned short iIntegrationTime_Coarse;	//! Register Address : 0x0202, 0x0203
	unsigned short iIntegrationTime_Fine;	//! Register Address : 0x0200, 0x0201 (Read Only)

	//! 단위 us
	int iExposureTime_Min;		//! Exposure Time의 가능한 최소값
	int iExposureTime_Max;		//! Exposure Time의 가능한 최대값
	int iExposureTime_Current;	//! Exposure Time의 현재값
} Info_IMX247, *PInfo_IMX247, *LPInfo_IMX247;

/******************************************************************************
*
*   MIU Device 구조체 
*
*******************************************************************************/
typedef struct strMIUDevice
{
	unsigned char		bMIUOpen ;			//! LPMC-500 Frame Grabber와 연결되어 있으면 '1', 아니면 '0'
	unsigned char       bMIUInit;			//! LPMC-500 Frame Grabber가 초기화 되어 있으면 '1', 그렇지 않으면 '0'
	unsigned char       bReadyVCM;			//! VCM Driver 사용 준비가 완료되면 '1', 그렇지 않으면 '0'
	unsigned char		CurrentState;		//	-1:영상 획득 Thread 빠져 나옴.
											//	0: NULL, 
											//	1: 초기화 완료 (Frame Grabber와 CCD Camera Sensor 모두 초기화 완료해야 '1'이 된다.), 
											//	2: 카메라는 찍지만 프로그램에서 아무것도 안함. Multi Thread 함수에서 일부러 영상 취득을 하지 않고 있는 상태
											//	3: 정지 영상 획득
											//	4: 동영상 Display
	
	unsigned char       bBayerFormat;		//! Bayer Color Format이면 '1', 그렇지 않으면 '0'

	SYSTEMTIME			TimeGrab;			//! 영상 취득했을 때의 시각

	Info_IMX135			IMX135;				//! 특정 CCD Sensor 관련 정보 구조체

	Info_IMX247			IMX247;				//! 특정 CCD Sensor 관련 정보 구조체

	float				fCcdSize;
	
	//MIU_INITIALValue	InitialValue;
	unsigned short		iSensorID;			// Sensor Product ID
	unsigned short		iSensorType;		// Sensor Resolution
	unsigned int		iPixelFormat;		// Sensor Out Format
	unsigned short		nMaxWidth;			// Max Width
	unsigned short		nMaxHeight;			// Max Height   
	int					nWidth;				// Sensor Width//unsigned short		nWidth;				// Sensor Width
	int					nHeight;			// Sensor Height    
	unsigned short		nBitPerPixel;		// Bit Per Pixel
	unsigned int		nFrameImageSize;	// 1 Frame Image size  
	unsigned int		nFrameRawSize;		// 1 Frame RAW size (Only Data Size)

	int					nDataFormat;
	int					nOutMode;
	int					nSensorType;

	IplImage*			imageItp;			// Display 
	char				szWindowName[256];
	
	unsigned char		fResizeFlag;
	unsigned short		nDisplayWidth;  // Display Width
	unsigned short		nDisplayHeight; // Display Height

	unsigned char		iImageSave;     // Image 저장 관련 flag 0:저장 안함, 1: Still Capture, 2:동영상 저장 
	unsigned char		fSaveNewFrame;  // 저장할 Image가 있는지 알려주는 flag

	unsigned short		*pBuffer;


	TDATASPEC dTDATASPEC_n;
} MIU_DEVICE, *PMIU_DEVICE;



//=================================================================================================
// Structure of sensor's information
//=================================================================================================
typedef struct _SENSOR_INFORMATION
{
	char			szResolution[256];		//  Resolution 
	int				nOutputWidth;           //  Image size Width
	int				nOutputHeight;          //  Image size Height
	unsigned int	iPixelFormat;           //  Pixel Format
}SENSOR_INFORMATION;


//=================================================================================================
// Structure of Sensor List
//=================================================================================================
typedef struct _IMAGESENSOR_LIST
{
	char				szSensorName[256];	// Sensor Name
	int					nInfoCount;         // Info Count
	SENSOR_INFORMATION* pInfo;	            // Sensor Information Pointer
}IMAGESENSOR_LIST;

//! Display FrameRate 측정용 구조체
struct strDiagInfo_Display
{
	int     iCnt_Display;
	double	dGrabStart;	
};

//! 경과 시간 측정용 클래스
const int iBufSize_Measure_Time_Elapsed = 100;
class CMeasureTimeElapsed
{
public:
	CMeasureTimeElapsed();
	~CMeasureTimeElapsed();

private:
	bool				m_bFlag_Valid_Freq;
	LARGE_INTEGER		m_liFreq;
	LARGE_INTEGER		m_liStartCounter;
	LARGE_INTEGER		m_aliCounter[iBufSize_Measure_Time_Elapsed];
	
public:
	double				m_adTime[iBufSize_Measure_Time_Elapsed];

	inline bool IsSuccess_Start_Time() { return m_bFlag_Valid_Freq; }

	void   Init_Time();
	bool   Start_Time();
	double Measure_Time(int iIndex_Time);
};


//! <-------------------------------------------------------------------------------------------------------------------
//! 50개 정도의 버퍼를 생성하려면, 메모리 할당 중에 프로그램이 다운될 정도임
//! 처음에는 6개 정도의 버퍼를 사용하고, 필요하면 1개 씩 늘려야 함
const int iBufSize_CCM_Temp = 4;
//! <-------------------------------------------------------------------------------------------------------------------

//! 영상 취득 경과 시간 저장용 버퍼의 크기
const int iBufSize_CCM_Time = 20;

//! 흑백 이미지의 Averaging 처리를 위한 버퍼의 개수
const int iBufSize_BW_Avg = 1;


class CMIU
{
public:
	CMIU();
	~CMIU();

public:
	bool				m_bFlag_Color_Covert_Ext;	//! Laon People사에서 제공한 Color 변환 함수를 사용하지 않을 때 true로 설정
	bool				m_bFlag_Mil_Convert;		//! Mil 버퍼 변환 기능을 제공하면 true로 설정
	bool				m_bFlag_Averaging;			//! Add_Sum_To_Buffer, Get_Average_From_Buffer 함수를 사용하려면 true로 설정
	
	//! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	int                 m_iDeviceCount;		//! 연결된 LPMC-500 Frame Grabber의 개수

	IMAGESENSOR_LIST*   m_pSID;				//! 'ImageSensor.ini' 파일에서 읽어온 CCD Sensor의 목록 정보
	int                 m_iSensorListCnt;	//! 'ImageSensor.ini' 파일에서 읽어온 CCD Sensor의 개수
		 
	BOOL                m_ubBurst;			//! CcmInit 함수에서 사용, CCD Sensor에서 Registry에 한꺼번에 입력값을 넣을 수 있을 때 true로 설정

	unsigned char		m_cInputCurrent;	//! Open/Short 검사에서의 입력 전류값 (Range 0 ~ 200, 초기값 150)

	IplImage*	        m_acvChildImage[3];	//! 임시 버퍼, Open CV <----> Mil 버퍼 변환에 필요하다. 

	CString             sLogMessage;		//! 오류 문자열

	float				m_fRate_Display;	//! Display용 Frame Rate 출력값

	CCriticalSection	m_csGrabLock;		//! 영상 취득을 안정되게 Stop하게 하기 위해 추가, 영상 취득 동시 접근 차단

	//! <-------------------------------------------------------------------------------------------------------------------
	//! Multi Thread 함수를 이용하여, Display Frame/sec를 최대한 올리기 위한 Queue형 버퍼와 버퍼 관리를 위한 index
	//! m_aTemp의 index, 0 based
	int                 m_iIndex_Grab_Working;		//! 영상 취득할 예정이거나, 영상 취득 중인 버퍼의 index, 0 based
	int                 m_iIndex_Grab_Ready;		//! 영상 취득이 완료되고, Color 변환 준비가 완료된 버퍼의 index, 0 based
	int					m_iIndex_Grab_Used;			//!	Color 변환이 완료된 버퍼의 index, 0 based

	int					m_iIndex_Cvt_Clr_Working;	//! Color 변환 중인 버퍼의 index, 0 based
	int					m_iIndex_Cvt_Clr_Used;		//! Color 변환 완료된 버퍼의 index, 0 based

	int					m_iIndex_Cvt_Mil_Working;	//! Open CV --> Mil 버퍼 변환 중인 버퍼의 index, 0 based
	int					m_iIndex_Cvt_Mil_Used;		//! Open CV --> Mil 버퍼 변환 완료된 버퍼의 index, 0 based

	int					m_iIndex_Display_Working;	//! 화면에 표시될 예정이거나, 화면에 표시 중인 버퍼의 index, 0 based

	MIU_DEVICE			m_aTemp[iBufSize_CCM_Temp];	//! 이미지 버퍼의 본체, 취득용, Color 변환용 버퍼를 모두 가지고 있다.
	
	//! Thread로 구분된 영상 취득 과정 사이의 경과 시간
	double				m_adTime_Grab[iBufSize_CCM_Time]; //! 단위 msec	
	//! <-------------------------------------------------------------------------------------------------------------------

	BOOL m_ChkBurst;

	
public:	
	//! 'ImageSensor.ini' 파일에서 CCD Sensor의 목록 정보를 읽어온다.
	bool SensorListInitialize();
	void setInterface();
	void ImageBufferSet();
	//! PC에 USB 3.0으로 연결된 LPMC-Frame Grabber를 찾아본다.
	int  Search_Device();

	//! Model이 변경될 때마다 호출해 주어야 한다. 
	//! 만약, LPMC-800 Frame Grabber가 이미 Open되어 있다면, Model 변경 후에 이 함수를 반드시 호출해 주어야 한다. 
	bool SelectSensor();

	void CMIU::GetImagePixelFormat(char* szPixelFormat, unsigned int* nPixelFormat);

	//! 현재 선택된 LPM-500 Frame Grabber의 장치 index를 반환한다. 0 based
	inline int GetIndexDevice() { return m_iIndexDevice; }

	//! Display Frame Rate 측정용 함수
	//! [주의 사항] 반드시, Display 직후에 호출한다. (Display를 하지 않을 경우에는 영상 취득 후의 최종 단계에서 호출한다.)
	void Add_Display_Count();
	//! Display Frame Rate 초기화
	void Init_Display_Count();

	//! Thread로 구분된 영상 취득 과정 사이의 경과 시간 측정 관련 함수
	void   Init_Grab_Time();
	bool   Init_Grab_Time(int fi_iIndex_Time_Grab, bool fi_bFlag_Init_Temp = false);
	bool   Start_Grab_Time(int fi_iIndex_Time_Grab);
	double Measure_Grab_Time(int fi_iIndex_Time_Grab);

	//! <---------------------------------------------------------------------------------------------------------------------------
	//! LPMC-500 Frame Grabber와 연결한다. 
	bool Open();
	//! Open/Short Test
	bool OSTest(int f_iOsCheckFlag[OS_PIN_COUNT], float	f_foOsUpperResult[OS_PIN_COUNT], float f_foOsLowerResult[OS_PIN_COUNT]);

	//! LPMC-500 Frame Grabber와 CCD Sensor를 모두 초기화 한다. 2가지를 모두 초기화 해야 영상 취득을 할 수 있다.
	bool CcmInit();
	bool CCM_Init();

	//! LPMC-500 Frame Grabber만 초기화
	//! [주의 사항] OIS (VCM) 관련 기능을 사용하기 위해서는 Frame Grabber를 반드시 초기화해야 한다. 
	bool MIU_Init();
	//! CCD Camera Sensor의 초기화만 진행한다.
	bool CCD_Init();
	//! 버퍼 생성
	bool cvBufferAlloc();

	//! 영상 취득 시작
	bool Start();

	//! gMIUDevice.imageItp 버퍼 관련 조작 함수
	bool cvCopyToMil(MIL_ID* f_pDestBuf);
	bool MilCopyToCv(MIL_ID* f_pDestBuf);

	//! 영상 취득을 마친다.
	bool Stop(bool fi_bFlag_PowerOff = false);

	//! 버퍼 해제
	void cvBufferFree();

	//! LPMC-500 Frame Grabber와의 연결을 끊는다. 
	bool Close();
	void SwitchHDRToLinearMode();
	void SwitchLinearToHDRMode();
	void ISPmodeCheck();
	//! <---------------------------------------------------------------------------------------------------------------------------
	//Head Model


	bool OtpWrite_Head_Fn();		//AA
	bool SensorIdRead_Head_Fn();	//AA + Eol
	bool FwVersionRead_Head_Fn();	//Eol

	bool OtpRead_Head_Fn();			//Eol
	bool partNumberVerifyFn();		//eol
	//

	//! Averaging 처리용 함수
	int Add_Sum_To_Buffer(IplImage* fi_cvInput, bool fi_bFlag_Start, int fi_iIndex_Avg = 0);
	int Get_Average_From_Buffer(IplImage* fo_cvOutput, int fi_iIndex_Avg = 0);

	//! Color 변환에 사용
	void Shift10BitMode(unsigned char* pImage, unsigned char* pDest, unsigned int nWidth, unsigned int nHeight);
	void Shift12BitMode(unsigned char* pImage, unsigned char* pDest, unsigned int nWidth, unsigned int nHeight);
	void Shift12to16BitMode(unsigned char* p12bitRaw, unsigned char* p16bitRaw ,int nWidth, int nHeight);
	void CopyBuffer(unsigned char* pImage, unsigned char* pDest, unsigned int nWidth, unsigned int nHeight);
	void CCCR_Interpolation(unsigned short* pData, int nWidth, int nHeight);

	//! ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//! CCD Sensor별 설정
	//! IMX135-0APH5-L CMOS, Sony, 2013/3/13
	//! 색상별 Gain 설정
	bool SetRegister_WhiteBalance_Red_IMX135  (double fi_dGain);
	bool SetRegister_WhiteBalance_Green_IMX135(double fi_dGain);
	bool SetRegister_WhiteBalance_Blue_IMX135 (double fi_dGain);
	bool SetRegister_WhiteBalance_Red_IMX135  (CString fi_sGain);
	bool SetRegister_WhiteBalance_Green_IMX135(CString fi_sGain);
	bool SetRegister_WhiteBalance_Blue_IMX135 (CString fi_sGain);
	//! Exposure Time 설정 (Added by LHW, 2013/3/14)
	bool GetCurrentInfo_Exposure_From_CCD_IMX135();
	bool Set_ExposureTime_To_CCD_IMX135(int fi_iExposureTime);	//! fi_iExposureTime : Exposure 시간, 단위 usec
	//! ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool CMIU::SetValue_VCM_Direct(BYTE fi_Byte1, BYTE fi_Byte2);

	//! ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//! OIS
	//! 사용 드라이버 : DW9714 - 10bit Resolution VCM driver IC with I2C interface (DONGWOON ANATECH), Ver 1.93
	//! Lens 모듈 제어 함수
	//! 2013/5/22 추가 (Added by LHW)
	//! 
	//! Laon People사에 문의해본 답변
	//!  1) VCM Control 관련하여 새로운 IIC 함수들은 새로운 FPGA Version이 적용된 LPMC-500CV BoardVersion에서만 사용가능 
	//!	 2) 기존 Sensor와 IIC 통신하던 Pin과 다르게 GPIO Pin을 이용하여 OIS Board와 IIC 통신
	//!	 3) DLL의 Version은 1.0.0.4
	//!	 4) VCM에 전원 인가는 MIUInitialize()함수를 호출해야 전원이 인가 되도록 되어 있으며, 
	//!		MIUOpenDevice()함수와 MIUInitialize()함수 호출뒤에 사용 가능 (클래스 내의 Open, MIU_Init 함수 호출 후 사용 가능)
	//!  5) 영상 취득후에 사용 가능, 추가된 OIS IIC 함수 호출뒤에 Sensor를 다시 연결할 필요는 없음
	//!  6) FPGA나 DLL함수는 VCM으로 IIC 통신을 할수 있도록만 설정 되어 있으며 내부에서 따로 'Slew Rate Control' 등의 처리는 하지 않음
	//!  7) Data input bit (D0 ~ D9)이외의 bit 제어는 직접 'MIUWriteOIS' 함수로 입력해야 함

	//! VCM Diver 사용 준비
	bool ReadyVCM();
	//! mA 단위로 값을 입력받아 적용
	bool MoveVCM_Current(int current);

	//! 아래의 함수들은 반드시 필요할 때만 사용한다. 

	//! code값으로 입력받아 적용
	bool MoveVCM_Code(int code);
	//! 입력된 code값을 입력된 BYTE값의 bit에 적용하여 반환한다.
	void Apply_Data_Code_VCM(BYTE fi_Byte1, BYTE fi_Byte2, BYTE &fo_Byte1, BYTE &fo_Byte2, int fi_code);
	//! 입력된 BYTE값의 bit에서 code값을 알아낸다.
	void Get_Data_Code_VCM(BYTE fi_Byte1, BYTE fi_Byte2, int &fo_code);
	//! 입력된 BYTE값을 직접 적용한다. 
	//! ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
private:
	char m_acIndexDevice[4];	//! PC의 USB 3.0에 연결된 LPMC-500 Frame Grabber의 구분 index들
	int  m_iIndexDevice;		//! 사용할 LPMC-500 Frame Grabber의 구분 index, 0 ~ 3

	int	 m_iSensor;				//! 현재 선택된 CCD Sensor의 index, 0 based, m_pSID의 1번째 index
	int	 m_iSensorType;			//! 현재 선택된 CCD Sensor의 index, 0 based, m_pSID의 2번쩨 index

	//! Display Frame Rate 측정용 구조체
	strDiagInfo_Display m_strDisplayDiag;
	CMeasureTimeElapsed m_aMeasureTimeForDisplayFrameRate;

	//! Thread로 구분된 영상 취득 과정 사이의 경과 시간
	CMeasureTimeElapsed m_aMeasureTime[iBufSize_CCM_Time];



private:
	//! m_pSID의 메모리 해제
	void SensorList_Free();

	//! LPMC-500 Frame Grabber와 CCD Sensor사이의 Interface pin의 번호를 다시 맞춘다.
	int  OsTest_PinMapping(unsigned char ucSensorMode, float* TestResult);

	//! Multi Thread 영상 취득 관련 index 초기화
	void Init_Index_Grab();
	void Start_Index_Grab();
// PRI Grabber Porting
public:
	bool bFlag_RawImageSave;
	HANDLE			m_hImgViewThread ;
	DWORD			m_dwImgViewThreadID;
	IplImage	*pImageBuf[3];



	int				preIdx ;
	int	m_PreIdx ;
	float m_FrameRate;
	void ReadRawImg(CString strInFileName,int nSizeX,int nSizeY,int nChannel,IplImage *outImage);
	void ReadRawImg2(CString strInFileName,int nSizeX,int nSizeY,int nChannel,IplImage *outImage);
	void SaveSfrImage(unsigned char* ucImage, int pitch, int sizeX, int sizeY, int index, CRect rcRoi);
	int GetCurrent ( float *pPwrCur );
	int Grab_StopImage ();
	int StopLive ();
	int TestPattern_CHK();
	int ImageShow();
    void RawImageSave(CString str, BYTE* SaveImage);


	bool m_bFlagImgReady;
	bool m_bFlagImgUsed;	// 디스플레이 스레드가 돌거나 정지이미지 memset 일때
	bool m_bThreadUsed;	
	bool b_BufCopyflag;
	void RawToBmp2(unsigned char *pRaw8,unsigned char *pBMP,int image_width,int image_height,int bayer_format);
	//void RawToBmp2(unsigned short *pRaw8,unsigned char *pBMP,int image_width,int image_height,int bayer_format);
	int SaveRawImage();

	int iUseClic;
	void PRI_12BitToRaw8 (unsigned char *p12Bit, unsigned char *pRawBit8 );

	void SetUartHead();
	
	unsigned char *pBmpBuffer;
	unsigned char *pImageData;
	unsigned char *pImageTemp;
	unsigned char *pImageTemp1;
	
	
	//-- 20140907 Test Pattern 관련(PRI 김세진 연구원)
/*
TestPattern Check() 함수 내용 설명
1. Image Grab 상태에서 실행 되어야 합니다.
2. 강제로 Test Pattern Mode로 바꿔 줄 수 있습니다.
3. 레프런스 이미지를 선택 혹은 강제로 지정 가능합니다.
4. 테스트 종료 후, 함수 리턴전에 강제로 Image Mode로 바꿔줄 수 있습니다.
*/
	BYTE* vTempBuffer;

	int  m_iPatternTest_ErrCnt;
	BOOL m_Burst; 
	void func_Set_InspImageCopy(int nType, BYTE* GrabImage, int AvrCount = 0);	//검사버퍼로 Image 저장
	float	fGrapStatTickCount;		// fps계산용



public:
	CString selectedIniFile ;
	//
	char m_cBoardIndex;
	IBoardControl*	m_pBoard;				// for dynamic loading
	HMODULE	 m_hBoardLibrary;
	CString m_strIniFileName;

	BYTE* m_pFrameRawBuffer;
	BYTE* m_pFrameBMPBuffer;
	BYTE* vChartBuffet;
	BYTE* vChart_Second_Buffet;
	BYTE* vDefectMidBuffer_6500K;	//중간밝기 이미지 (dark/Defect/Blemish/RI/Color Uniformity 검출용)
	BYTE* vDefectLowBuffer;			//암흑 영상(Hot Defect 검출용)
	BYTE* vDefectMidBuffer_2800K;	//중간밝기 (Color Sensitivity 검출용)

	void disConnectedInit();
	void INI_LOAD(int index = 0);

};
