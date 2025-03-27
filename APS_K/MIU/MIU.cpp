#include "stdafx.h"

#include "MIU.h"

#include "../AA Bonder.h"
#include "../AA BonderDlg.h"
#include "../RawToBmp.h"
#include "ConvertColor.h"
#include <winbase.h>

#define	BUFFER_COUNT	10
#define PAYLOAD_SIZE	1020
#define	BGGR				1	//BGBG
#define RGGB				2	//RGRG
#define GBRG				3	//GBGB
#define GRBG				4	//GRGR
#define RCCC				5	//RCCC
#define CCCR				6	
#define CRCC				7
#define	CCRC				8


CMeasureTimeElapsed::CMeasureTimeElapsed()
{
	Init_Time();
}

CMeasureTimeElapsed::~CMeasureTimeElapsed()
{
}

void CMeasureTimeElapsed::Init_Time()
{
	int i = 0;
	for ( i = 0; i < iBufSize_Measure_Time_Elapsed; i++ )
	{
		m_adTime[i] = 0.;
	}
	m_bFlag_Valid_Freq = false;
}

bool CMeasureTimeElapsed::Start_Time()
{
	if ( QueryPerformanceFrequency(&m_liFreq) == TRUE )
	{
		m_bFlag_Valid_Freq = true;
	}
	else
	{
		m_bFlag_Valid_Freq = false;		
	}

    if ( QueryPerformanceCounter(&m_liStartCounter) == FALSE )
	{
		m_bFlag_Valid_Freq = false;
	}

	return m_bFlag_Valid_Freq;
}

double CMeasureTimeElapsed::Measure_Time(int iIndex_Time)
{
	double dRet = -1.;

	if ( m_bFlag_Valid_Freq == false )
	{
		return dRet;
	}
	if ( iIndex_Time < 0 || iIndex_Time >= iBufSize_Measure_Time_Elapsed )
	{
		return dRet;
	}

	if ( QueryPerformanceCounter( &(m_aliCounter[iIndex_Time]) ) == TRUE )
	{
		dRet = ((double)(m_aliCounter[iIndex_Time].QuadPart - m_liStartCounter.QuadPart)) / ((double)m_liFreq.QuadPart);
		dRet *= 1000.;
	}
	
	m_adTime[iIndex_Time] = dRet;

	return dRet;
}


CMIU::CMIU()
{
	

	
}

CMIU::~CMIU()
{
	int i = 0;
	cvReleaseImage(&pImageBuf[0]);
	cvReleaseImage(&pImageBuf[1]);
	cvReleaseImage(&pImageBuf[2]);
	//delete[] gMIUDevice.pBuffer;

	if (gMIUDevice.imageItp != NULL)
	{
		cvReleaseImage(&gMIUDevice.imageItp);
		gMIUDevice.imageItp = NULL;
	}
	for (i = 0; i < 3; i++)
	{
		if (m_acvChildImage[i] != NULL)
		{
			cvReleaseImage(&m_acvChildImage[i]);
			m_acvChildImage[i] = NULL;
		}

		if (pImageBuf[i] != NULL)
		{
			cvReleaseImage(&pImageBuf[i]);
			pImageBuf[i] = NULL;
		}
	}


	SensorList_Free();

	if (m_hBoardLibrary)
	{
		pfnReleaseBoardControl fnReleaseBoard = (pfnReleaseBoardControl)GetProcAddress(m_hBoardLibrary, "ReleaseBoardControl");
		if( fnReleaseBoard )
			fnReleaseBoard(m_pBoard);

		FreeLibrary(m_hBoardLibrary);
		m_hBoardLibrary = NULL;
		m_pBoard = NULL;
	}
	if (vTempBuffer)
		delete vTempBuffer;
	vTempBuffer = NULL;

	if (vDefectMidBuffer_2800K)
		delete vDefectMidBuffer_2800K;
	vDefectMidBuffer_2800K = NULL;

	if (vDefectLowBuffer)
		delete vDefectLowBuffer;
	vDefectLowBuffer = NULL;

	if (vDefectMidBuffer_6500K)
		delete vDefectMidBuffer_6500K;
	vDefectMidBuffer_6500K = NULL;

	if (vChartBuffet)
		delete vChartBuffet;
	vChartBuffet = NULL;

	if (vChart_Second_Buffet)
		delete vChart_Second_Buffet;
	vChart_Second_Buffet = NULL;
	
	if (m_pFrameBMPBuffer)
		delete m_pFrameBMPBuffer;
	m_pFrameBMPBuffer = NULL;

	if (m_pFrameRawBuffer)
		delete m_pFrameRawBuffer;
	m_pFrameRawBuffer = NULL;



	
}
void CMIU::ImageBufferSet()
{
	INI_LOAD();		////ImageBufferSet
	//
	//
	//
	//! CCD Camera Sensor 영상 취득 관련 버퍼 생성
	//
	//
	cvBufferAlloc();		//ImageBufferSet

	
}
void CMIU::setInterface()
{
	m_pBoard = NULL;
	m_hBoardLibrary = NULL;
	m_pFrameRawBuffer = NULL;
	m_pFrameBMPBuffer = NULL;
	vChartBuffet = NULL;
	vChart_Second_Buffet = NULL;
	m_strIniFileName = "";
	m_cBoardIndex = 0;
	//--
	m_bFlag_Color_Covert_Ext = false;
	m_bFlag_Mil_Convert = true;
	m_bFlag_Averaging = false;

	gDeviceIndex = 0;
	gMIUDevice.iImageSave = 0;
	int i = 0;

	::GetLocalTime(&(gMIUDevice.TimeGrab));
	memset(&gMIUDevice, 0, sizeof(MIU_DEVICE));


	for (i = 0; i < iBufSize_CCM_Temp; i++)
	{
		memset(&(m_aTemp[i]), 0, sizeof(MIU_DEVICE));
		::GetLocalTime(&(m_aTemp[i].TimeGrab));
	}


	//라온피플 ★★★★★★
	//===================================================================================================================
	m_hBoardLibrary = LoadLibrary("GrabberDLL.dll");
	if (m_hBoardLibrary == NULL)
	{
		AfxMessageBox("[ERROR] Cannot Load Board Library");
	}

	pfnGetBoardControl fnGetInterface = (pfnGetBoardControl)GetProcAddress(m_hBoardLibrary, "GetBoardControl");
	if (fnGetInterface)
	{
		m_pBoard = (*fnGetInterface)(BOARD_TYPE_LAON1000OP);	//BOARD_TYPE_LAON
		if (m_pBoard == NULL)
		{
			AfxMessageBox("[ERROR] GetBoardControl Load Failed!");
		}
	}
	else
	{
		AfxMessageBox("[ERROR] Cannot Get Board Interface");
	}
	m_iDeviceCount = 2;
	memset(m_acIndexDevice, 0, 4);

	m_iIndexDevice = 1;

	m_pSID = NULL;
	m_iSensorListCnt = 0;

	for (i = 0; i < 3; i++)
	{
		m_acvChildImage[i] = NULL;
		pImageBuf[i] = NULL;
	}

	Init_Grab_Time();

	Init_Index_Grab();

	m_iSensorType = 1;

	m_cInputCurrent = 150;

	m_ubBurst = FALSE;

	sLogMessage = _T("");

	gMIUDevice.bMIUOpen = 0;
	gMIUDevice.bMIUInit = 0;
	gMIUDevice.bReadyVCM = 0;
	gMIUDevice.CurrentState = 0;

	gMIUDevice.nWidth = 0;
	gMIUDevice.nHeight = 0;

	gMIUDevice.fCcdSize = 1.75f;
	gMIUDevice.nDataFormat = 0;
	gMIUDevice.nOutMode = 0;
	gMIUDevice.nSensorType = 0;

	// by PRI	
	m_bFlagImgReady = 0;
	m_bFlagImgUsed = 0;
	Init_Display_Count();
	/////////////////////////////////////////////////////////

	bFlag_RawImageSave = false;
	ImageBufferSet();			//MIU.setInterface 최초

	
}
void CMIU::INI_LOAD(int index)
{
	char szTemp[MAX_PATH];
	CString uiFile=_T("");
	if (index == 0)
	{
		uiFile.Format("%s\\%s\\Initialize\\UIConfig\\UIConfig.ini", AA_MODEL_LOAD_DIR, modelList.curModelName);			//uiFile.Empty();
	}
	else
	{
		uiFile.Format("%s\\%s\\Initialize\\UIConfig\\UIConfig2.ini", AA_MODEL_LOAD_DIR, modelList.curModelName);			//uiFile.Empty();
	}
	
	theApp.MainDlg->putListLog(uiFile);

	m_cBoardIndex = GetPrivateProfileInt("UIConfig", "BoardIndex", 0, uiFile);
	CString iniFolder = "";
	GetPrivateProfileString("UIConfig", "GrabberINI", "Default.ini", szTemp, MAX_PATH, uiFile);
	selectedIniFile.Format("%s\\%s\\Initialize\\%s", AA_MODEL_LOAD_DIR, modelList.curModelName, szTemp);

	theApp.MainDlg->putListLog(selectedIniFile);
	m_pBoard->SetINIFile(selectedIniFile);

	int iRet = SelectSensor();

	m_pBoard->CloseBoard();
}
void CMIU::disConnectedInit()
{
	//theApp.MainDlg->m_bMiuRun = false; 
	gMIUDevice.CurrentState = 0;
	gMIUDevice.bMIUOpen = 0;
	gMIUDevice.bMIUInit = 0;
	gMIUDevice.bReadyVCM = 0;
	//Init_Index_Grab();
	//theApp.MainDlg->m_labelUsbLive.SetBkColor(M_COLOR_RED);
	//theApp.MainDlg->m_labelUsbLive.Invalidate();
}
void CMIU::Init_Index_Grab()
{
	//! CCM 영상 Thread 사이를 연결해 주는 index 초기화
	//! [주의 사항] Start를 하기 전까지 영상 취득을 하지 못하도록 전부 (-1)을 설정한다. 
	m_iIndex_Grab_Working = -1;
	m_iIndex_Grab_Ready = -1;
	m_iIndex_Grab_Used = -1;

	m_iIndex_Cvt_Clr_Working = -1;		
	m_iIndex_Cvt_Clr_Used = -1;

	m_iIndex_Cvt_Mil_Working = -1;		
	m_iIndex_Cvt_Mil_Used = -1;

	m_iIndex_Display_Working = -1;
}

void CMIU::Start_Index_Grab()
{
	//! 반드시, 동영상 Play로 초기화 한다. 
	int i = 0;
	/*for ( i = 0; i < iBufSize_CCM_Temp; i++ )
	{
		m_aTemp[i].CurrentState = 4;
	}*/

	//! CCM 영상 Thread 사이를 연결해 주는 index 초기화
	//! [주의 사항] 
	//!	  영상 취득 시작은 언제나 'm_iIndex_Grab_Working'을 '0'으로 초기화 하는데서 부터 시작한다. 
	//!   다른 index들은 모두 (-1)로 초기화되어야 한다.
	m_iIndex_Grab_Working = 0;
	m_iIndex_Grab_Ready = -1;
	m_iIndex_Grab_Used = -1;

	m_iIndex_Cvt_Clr_Working = -1;		
	m_iIndex_Cvt_Clr_Used = -1;

	m_iIndex_Cvt_Mil_Working = -1;		
	m_iIndex_Cvt_Mil_Used = -1;

	m_iIndex_Display_Working = -1;
}

//! Thread간 경과 시간 초기화
void CMIU::Init_Grab_Time()
{
	int i = 0;
	for ( i = 0; i < iBufSize_CCM_Time; i++ )
	{
		m_adTime_Grab[i] = 0.;
		m_aMeasureTime[i].Init_Time();
	}
}

//! Thread간 경과 시간 초기화
bool CMIU::Init_Grab_Time(int fi_iIndex_Time_Grab, bool fi_bFlag_Init_Temp)
{
	if ( fi_iIndex_Time_Grab < 0 || fi_iIndex_Time_Grab >= iBufSize_CCM_Time )
	{
		return false;
	}

	m_aMeasureTime[fi_iIndex_Time_Grab].Init_Time();

	if ( fi_bFlag_Init_Temp == true )
	{
		m_adTime_Grab[fi_iIndex_Time_Grab] = 0.;
	}

	return true;
}

//! Thread간 경과 시간 측정 시작
bool CMIU::Start_Grab_Time(int fi_iIndex_Time_Grab)
{
	if ( fi_iIndex_Time_Grab < 0 || fi_iIndex_Time_Grab >= iBufSize_CCM_Time )
	{
		return false;
	}

	bool bRet = m_aMeasureTime[fi_iIndex_Time_Grab].Start_Time();

	return bRet;
}

//! Thread간 경과 시간 측정, 단위 msec
double CMIU::Measure_Grab_Time(int fi_iIndex_Time_Grab)
{
	double dRet = -1.;

	if ( fi_iIndex_Time_Grab < 0 || fi_iIndex_Time_Grab >= iBufSize_CCM_Time )
	{
		return dRet;
	}

	bool bRet = m_aMeasureTime[fi_iIndex_Time_Grab].IsSuccess_Start_Time();
	if ( bRet == false )
	{
		return dRet;
	}
	
	dRet = m_aMeasureTime[fi_iIndex_Time_Grab].Measure_Time(0);
	
	m_adTime_Grab[fi_iIndex_Time_Grab] = dRet;

	return dRet;
}

//! Sensor 목록의 메모리를 해제
void CMIU::SensorList_Free()
{
	if ( m_iSensorListCnt > 0 && m_pSID != NULL )
	{
		int i = 0;

		for ( i = 0; i < m_iSensorListCnt; i++ )
		{
			if ( m_pSID[i].pInfo != NULL )
			{
				delete [] m_pSID[i].pInfo;
				m_pSID[i].pInfo = NULL;
			}
		}

		delete [] m_pSID;
		m_pSID = NULL;
	}
}

//! USB 3.0에 연결된 Device Search
int CMIU::Search_Device()
{
	/*int iErrorCode = MIU_OK;
	char cDeiveCount = 0;
	memset(m_acIndexDevice, 0, 2);
	iErrorCode = MIUGetDeviceList(&cDeiveCount, m_acIndexDevice);
	if ( iErrorCode != MIU_OK )
	{
		m_iDeviceCount = 1;
		sLogMessage.Format(_T("MIU Device - MIUGetDeviceList Error (Code : 0x%x)"), iErrorCode);
		return 0;
	}

	m_iDeviceCount = cDeiveCount;*/

	return m_iDeviceCount;
}
//! LPMC-500 Frame Grabber와 연결한다.
bool CMIU::Open()
{ 
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	CString logStr = "";
	pFrame->putListLog("		MIU Open 시작.");
	int	errorCode = 0;
	
	gMIUDevice.bMIUOpen = 0;
	gMIUDevice.bMIUInit = 0;
	gMIUDevice.bReadyVCM = 0;
	gMIUDevice.CurrentState = 0;

	CString strErrCount="";
	
	int _temp = 1;
	errorCode = m_pBoard->OpenBoard(m_cBoardIndex);

	if (errorCode)
	{	
		
		switch(errorCode)
		{
		case 1:
			strErrCount.Format("OpenBoard Error: ERR_BOARD_GET_LIST[%d]", errorCode);
			break;
		case 2:
			strErrCount.Format("OpenBoard Error: ERR_BOARD_NO_DEVICE[%d]", errorCode);
			break;
		case 3:
			strErrCount.Format("OpenBoard Error: ERR_BOARD_OPEN[%d]", errorCode);
			break;
		case 4:
			strErrCount.Format("OpenBoard Error: ERR_BOARD_INIT[%d]", errorCode);
			break;
		case 5:
			strErrCount.Format("OpenBoard Error: ERR_BOARD_SET_POWER_5_12[%d]", errorCode);
			break;
		case 6:
			strErrCount.Format("OpenBoard Error: ERR_BOARD_GRAB_START[%d]", errorCode);
			break;
		case 7:
			strErrCount.Format("OpenBoard Error: ERR_BOARD_I2C_WRITE[%d]", errorCode);
			break;
		case 8:
			strErrCount.Format("OpenBoard Error: ERR_BOARD_I2C_READ[%d]", errorCode);
			break;
		case 9:
			strErrCount.Format("OpenBoard Error: ERR_BOARD_BOOT_CAMERA[%d]", errorCode);
			break;
		case 10:
			strErrCount.Format("OpenBoard Error: ERR_BOARD_CLOSE[%d]", errorCode);
			break;
		case 11:
			strErrCount.Format("OpenBoard Error: ERR_BOARD_LOAD_MODEL[%d]", errorCode);
			break;
		}
		//AfxMessageBox(strErrCount);
		pFrame->putListLog(strErrCount);
		return false;
	}
	else
	{
		pFrame->putListLog("MIU Open 완료.");
		strErrCount.Format("OpenBoard Success");
		
	}

	//
	//! [주의 사항] 연결한 직후에는 사용할 수 없는 데이터이므로, 반드시 초기화 한다. 
	gMIUDevice.IMX135.bFlag_Valid = 0;

	//! Laon People에서의 답변 (2013/3/5)
	//!  - 0x00001006 Error는 MIUOpenDevice함수 호출시 반환하는 값으로 
	//!    다른 프로그램에서 이미 Open되어 있는 상태에서 다시 Open하려고 할 때 발생되는 Error 입니다.

	gMIUDevice.bMIUOpen = 1;

	//! 초기에는 저장된 값으로 설정한다. 
	//bool bRet = SelectSensor();
	
	//! Thread간 영상 취득 경과 시간 버퍼 초기화
	Init_Grab_Time();

	//! Display용 Frame Rate 측정값 초기화
	Init_Display_Count();
	//AfxMessageBox(strErrCount);
	logStr.Format("[MIU] Open 완료.");
	return true;
}

//! LPMC-500 Frame Grabber와의 연결을 해제한다. 
bool CMIU::Close()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	CString logStr;
	logStr.Format("  Close 시작.");
	MiuLogSave(logStr);

	int iRet = 0;
	bool bRtnFlag = true;
	if (m_pBoard->IsGrabStarted())//if ( gMIUDevice.CurrentState >= 2 )
	{
		Stop();
		Sleep(500);
	}
	//! 영상 취득을 중지한다. (CCD의 전원을 완전히 끈다)

	INI_LOAD();		//240725

	iRet = m_pBoard->CloseBoard();

	if(iRet != BOARD_SUCCESS)
	{
		return false;
	}
	theApp.MainDlg->m_labelUsbLive.SetBkColor(M_COLOR_RED);
	theApp.MainDlg->m_labelUsbLive.Invalidate();
	Sleep(200);

	//! Flag값 초기화
	gMIUDevice.bMIUOpen = 0;
	gMIUDevice.bMIUInit = 0;
	gMIUDevice.bReadyVCM = 0;

	//! [주의 사항] 연결이 끊어진 직후에는 사용할 수 없는 데이터이므로, 반드시 초기화 한다. 
	gMIUDevice.IMX135.bFlag_Valid = 0;

//	m_cPcie.DeviceReset() ;
	if(pFrame->m_bMiuRun)
	{
		pFrame->m_bMiuRun=false;
	}
	
	return bRtnFlag;
}

//! LPMC-800 Frame Grabber에서 사용하는 CCD Sensor를 선택한다. 
//! SensorList에서의 index를 이용하여, 사용할 CCD Sensor를 알려주어야 한다.
unsigned short ChecksumCalc(unsigned short* arr, unsigned int size)
{
	unsigned int tmp_checksum = 0, i;
	unsigned short checksum = 0;
	for (i = 0; i < size; i++)
	{
		tmp_checksum += arr[i];
	}
	checksum = (unsigned short)(tmp_checksum & 0x000000ff);
	return checksum;
}



bool CMIU::OtpWrite_Head_Fn()
{
	TCHAR szPos[SIZE_OF_1K];
	int i = 0;
	unsigned int errorCode = 0;
	unsigned short SlaveAddr = 0x24;

	unsigned short checkAddr = 0x3C06;
	
	const int maxArrLength = 30;
	unsigned short writeAddrArr[maxArrLength] = { 0x0000, };
	unsigned char writeData[maxArrLength] = { 0x00, };
	//
	unsigned char pReadData[MAX_PATH];
	memset(pReadData, 0x00, sizeof(pReadData));
	int writeDelay = 20;

	//
	//Command1 전송
	writeAddrArr[0] = 0x3000;
	writeAddrArr[1] = 0x3001;
	writeAddrArr[2] = 0x3002;
	writeAddrArr[3] = 0x3003;
	writeAddrArr[4] = 0x3004;
	writeAddrArr[5] = 0x3005;
	writeAddrArr[6] = 0x3006;
	writeAddrArr[7] = 0x3007;
	writeAddrArr[8] = 0x3008;
	writeAddrArr[9] = 0x3009;
	writeAddrArr[10] = 0x300a;
	writeAddrArr[11] = 0x300b;
	writeAddrArr[12] = 0x80bc;
	//
	writeData[0] = 0x00;
	writeData[1] = 0x00;
	writeData[2] = 0x00;
	writeData[3] = 0x00;
	writeData[4] = 0x00;
	writeData[5] = 0x06;
	writeData[6] = 0x00;
	writeData[7] = 0x00;
	writeData[8] = 0x30;
	writeData[9] = 0x17;
	writeData[10] = 0x01;
	writeData[11] = 0xF2;
	writeData[12] = 0x01;
	//
	const int Cmd1Length = 13;
	for (i = 0; i < Cmd1Length; i++)
	{
		Sleep(writeDelay);
		errorCode = m_pBoard->WriteI2CBurst(SlaveAddr, writeAddrArr[i], 2, writeData + i, 1);
		if (errorCode)
		{
			_stprintf_s(szPos, SIZE_OF_1K, _T("#1 Addr:%0x WriteI2CBurst errorCode:%d"), writeAddrArr[i], errorCode);
			theApp.MainDlg->putListLog(szPos);
			return false;
		}
	}
	Sleep(15);
	//Command 1 End
	//
	//
	memset(pReadData, 0x00, sizeof(pReadData));
	errorCode = m_pBoard->ReadI2CBurst(SlaveAddr, checkAddr, 2, pReadData, (unsigned short)1);
	if (pReadData[0] != 0x99)
	{
		_stprintf_s(szPos, SIZE_OF_1K, _T("0x3c06[%02X] Read Fail errorCode:%d"), pReadData[0], errorCode);
		theApp.MainDlg->putListLog(szPos);
		return false;
	}

	_stprintf_s(szPos, SIZE_OF_1K, _T("0x3c06[%02X] Read Pass"), pReadData[0]);
	theApp.MainDlg->putListLog(szPos);
	//
	//Command2 전송
	const int Cmd2Length = 14;
	writeAddrArr[0] = 0x3000;
	writeAddrArr[1] = 0x3001;
	writeAddrArr[2] = 0x3002;
	writeAddrArr[3] = 0x3003;
	writeAddrArr[4] = 0x3004;
	writeAddrArr[5] = 0x3005;
	writeAddrArr[6] = 0x3006;
	writeAddrArr[7] = 0x3007;
	writeAddrArr[8] = 0x3008;
	writeAddrArr[9] = 0x3009;
	writeAddrArr[10] = 0x300a;
	writeAddrArr[11] = 0x300b;
	writeAddrArr[12] = 0x300c;
	writeAddrArr[13] = 0x80bc;

	writeData[0] = 0x00;
	writeData[1] = 0x00;
	writeData[2] = 0x00;
	writeData[3] = 0x00;
	writeData[4] = 0x00;
	writeData[5] = 0x07;
	writeData[6] = 0x00;
	writeData[7] = 0x00;
	writeData[8] = 0x3D;
	writeData[9] = 0x84;
	writeData[10] = 0x02;
	writeData[11] = 0x40;
	writeData[12] = 0x00;
	writeData[13] = 0x01;
	for (i = 0; i < Cmd2Length; i++)
	{
		Sleep(writeDelay);
		errorCode = m_pBoard->WriteI2CBurst(SlaveAddr, writeAddrArr[i], 2, writeData + i, 1);
		if (errorCode)
		{
			_stprintf_s(szPos, SIZE_OF_1K, _T("#2 Addr:%0x WriteI2CBurst errorCode:%d"), writeAddrArr[i], errorCode);
			theApp.MainDlg->putListLog(szPos);
			return false;
		}
	}
	Sleep(15);
	//Command 2 End
	//
	//
	memset(pReadData, 0x00, sizeof(pReadData));
	errorCode = m_pBoard->ReadI2CBurst(SlaveAddr, checkAddr, 2, pReadData, (unsigned short)1);
	if (pReadData[0] != 0x99)
	{
		_stprintf_s(szPos, SIZE_OF_1K, _T("0x3c06[%02X] Read Fail errorCode:%d"), pReadData[0], errorCode);
		theApp.MainDlg->putListLog(szPos);
		return false;
	}
	_stprintf_s(szPos, SIZE_OF_1K, _T("0x3c06[%02X] Read Pass"), pReadData[0]);
	theApp.MainDlg->putListLog(szPos);

	//Command3 전송
	const int Cmd3Length = 16;
	writeAddrArr[0] = 0x3000;
	writeAddrArr[1] = 0x3001;
	writeAddrArr[2] = 0x3002;
	writeAddrArr[3] = 0x3003;
	writeAddrArr[4] = 0x3004;
	writeAddrArr[5] = 0x3005;
	writeAddrArr[6] = 0x3006;
	writeAddrArr[7] = 0x3007;
	writeAddrArr[8] = 0x3008;
	writeAddrArr[9] = 0x3009;
	writeAddrArr[10] = 0x300a;
	writeAddrArr[11] = 0x300b;
	writeAddrArr[12] = 0x300c;
	writeAddrArr[13] = 0x300d;
	writeAddrArr[14] = 0x300e;
	writeAddrArr[15] = 0x80bc;

	writeData[0] = 0x00;
	writeData[1] = 0x00;
	writeData[2] = 0x00;
	writeData[3] = 0x00;
	writeData[4] = 0x00;
	writeData[5] = 0x09;
	writeData[6] = 0x00;
	writeData[7] = 0x00;
	writeData[8] = 0x3D;
	writeData[9] = 0x88;
	writeData[10] = 0x04;
	writeData[11] = 0x70;
	writeData[12] = 0x18;
	writeData[13] = 0x70;
	writeData[14] = 0x23;
	writeData[15] = 0x01;

	for (i = 0; i < Cmd3Length; i++)
	{
		Sleep(writeDelay);
		errorCode = m_pBoard->WriteI2CBurst(SlaveAddr, writeAddrArr[i], 2, writeData + i, 1);
		if (errorCode)
		{
			_stprintf_s(szPos, SIZE_OF_1K, _T("#3 Addr:%0x WriteI2CBurst errorCode:%d"), writeAddrArr[i], errorCode);
			theApp.MainDlg->putListLog(szPos);
			return false;
		}
	}
	Sleep(15);
	//Command 3 End
	// 
	//
	//
	memset(pReadData, 0x00, sizeof(pReadData));
	errorCode = m_pBoard->ReadI2CBurst(SlaveAddr, checkAddr, 2, pReadData, (unsigned short)1);
	if (pReadData[0] != 0x99)
	{
		_stprintf_s(szPos, SIZE_OF_1K, _T("0x3c06[%02X] Read Fail errorCode:%d"), pReadData[0], errorCode);
		theApp.MainDlg->putListLog(szPos);
		return false;
	}	// 

	_stprintf_s(szPos, SIZE_OF_1K, _T("0x3c06[%02X] Read Pass"), pReadData[0]);
	theApp.MainDlg->putListLog(szPos);


	//Command4 전송
	const int Cmd4Length = 24;
	writeAddrArr[0] = 0x3000;
	writeAddrArr[1] = 0x3001;
	writeAddrArr[2] = 0x3002;
	writeAddrArr[3] = 0x3003;
	writeAddrArr[4] = 0x3004;
	writeAddrArr[5] = 0x3005;
	writeAddrArr[6] = 0x3006;
	writeAddrArr[7] = 0x3007;
	writeAddrArr[8] = 0x3008;
	writeAddrArr[9] = 0x3009;
	writeAddrArr[10] = 0x300a;
	writeAddrArr[11] = 0x300b;
	writeAddrArr[12] = 0x300c;
	writeAddrArr[13] = 0x300d;
	writeAddrArr[14] = 0x300e;
	writeAddrArr[15] = 0x300f;
	writeAddrArr[16] = 0x3010;
	writeAddrArr[17] = 0x3011;
	writeAddrArr[18] = 0x3012;
	writeAddrArr[19] = 0x3013;
	writeAddrArr[20] = 0x3014;
	writeAddrArr[21] = 0x3015;
	writeAddrArr[22] = 0x3016;
	writeAddrArr[23] = 0x80bc;

	writeData[0] = 0x00;
	writeData[1] = 0x00;
	writeData[2] = 0x00;
	writeData[3] = 0x00;
	writeData[4] = 0x00;
	writeData[5] = 0x11;	////0x0F;		//250107 이재현,김병기 요청
	writeData[6] = 0x00;
	writeData[7] = 0x00;
	writeData[8] = 0x70;
	writeData[9] = 0x18;
	writeData[10] = 0x0C;
	writeData[11] = (unsigned char)Task.ChipID[0];	//part_number[0] ASCII Code로 OTP에 Write  Barcode 읽은값
	writeData[12] = (unsigned char)Task.ChipID[1];	//part_number[1]
	writeData[13] = (unsigned char)Task.ChipID[2];	//part_number[2]
	writeData[14] = (unsigned char)Task.ChipID[3];	//part_number[3]
	writeData[15] = (unsigned char)Task.ChipID[4];	//part_number[4]
	writeData[16] = (unsigned char)Task.ChipID[5];	//part_number[5]
	writeData[17] = (unsigned char)Task.ChipID[6];	//part_number[6]
	writeData[18] = (unsigned char)Task.ChipID[7];	//part_number[7]
	writeData[19] = (unsigned char)Task.ChipID[8];	//part_number[8]
	writeData[20] = (unsigned char)Task.ChipID[9];	//part_number[9]
	writeData[21] = (unsigned char)Task.ChipID[10];	//part_number[10]
	writeData[22] = (unsigned char)Task.ChipID[11];	//part_number[11]
	writeData[23] = 0x01;


	/////_stprintf_s(Task.ChipID, sizeof(Task.ChipID), _T("EMPTY"));
	
	for (i = 0; i < Cmd4Length; i++)
	{
		Sleep(writeDelay);
		errorCode = m_pBoard->WriteI2CBurst(SlaveAddr, writeAddrArr[i], 2, writeData + i, 1);
		if (errorCode)
		{
			_stprintf_s(szPos, SIZE_OF_1K, _T("#4 Addr:%0x WriteI2CBurst errorCode:%d"), writeAddrArr[i], errorCode);
			theApp.MainDlg->putListLog(szPos);
			return false;
		}
	}
	Sleep(15);
	//Command 4 End
	// 
	memset(pReadData, 0x00, sizeof(pReadData));
	errorCode = m_pBoard->ReadI2CBurst(SlaveAddr, checkAddr, 2, pReadData, (unsigned short)1);
	if (pReadData[0] != 0x99)
	{
		_stprintf_s(szPos, SIZE_OF_1K, _T("0x3c06[%02X] Read Fail errorCode:%d"), pReadData[0], errorCode);
		theApp.MainDlg->putListLog(szPos);
		return false;
	}
	_stprintf_s(szPos, SIZE_OF_1K, _T("0x3c06[%02X] Read Pass"), pReadData[0]);
	theApp.MainDlg->putListLog(szPos);
	// 
	//Command5 전송
	const int Cmd5Length = 13;

	writeAddrArr[0] = 0x3000;
	writeAddrArr[1] = 0x3001;
	writeAddrArr[2] = 0x3002;
	writeAddrArr[3] = 0x3003;
	writeAddrArr[4] = 0x3004;
	writeAddrArr[5] = 0x3005;
	writeAddrArr[6] = 0x3006;
	writeAddrArr[7] = 0x3007;
	writeAddrArr[8] = 0x3008;
	writeAddrArr[9] = 0x3009;
	writeAddrArr[10] = 0x300a;
	writeAddrArr[11] = 0x300b;
	writeAddrArr[12] = 0x80bc;

	writeData[0] = 0x00;
	writeData[1] = 0x00;
	writeData[2] = 0x00;
	writeData[3] = 0x00;
	writeData[4] = 0x00;
	writeData[5] = 0x06;
	writeData[6] = 0x00;
	writeData[7] = 0x00;
	writeData[8] = 0x3D;
	writeData[9] = 0x80;
	writeData[10] = 0x01;
	writeData[11] = 0x01;
	writeData[12] = 0x01;

	for (i = 0; i < Cmd5Length; i++)
	{
		Sleep(writeDelay);
		errorCode = m_pBoard->WriteI2CBurst(SlaveAddr, writeAddrArr[i], 2, writeData + i, 1);
		if (errorCode)
		{
			_stprintf_s(szPos, SIZE_OF_1K, _T("#5 Addr:%0x WriteI2CBurst errorCode:%d"), writeAddrArr[i], errorCode);
			theApp.MainDlg->putListLog(szPos);
			return false;
		}
	}
	Sleep(15);
	//Command 5 End
	memset(pReadData, 0x00, sizeof(pReadData));
	errorCode = m_pBoard->ReadI2CBurst(SlaveAddr, checkAddr, 2, pReadData, (unsigned short)1);
	if (pReadData[0] != 0x99)
	{
		_stprintf_s(szPos, SIZE_OF_1K, _T("0x3c06[%02X] Read Fail errorCode:%d"), pReadData[0], errorCode);
		theApp.MainDlg->putListLog(szPos);
		return false;
	}
	_stprintf_s(szPos, SIZE_OF_1K, _T("Otp Write Complete!"));
	theApp.MainDlg->putListLog(szPos);


	return true;
}
bool CMIU::partNumberVerifyFn()
{
	TCHAR szPos[SIZE_OF_1K];
	_stprintf_s(szPos, SIZE_OF_1K, _T("Otd:[%s]"), MESCommunication.partNumber);
	theApp.MainDlg->putListLog(szPos);
	_stprintf_s(szPos, SIZE_OF_1K, _T("Bcr:[%s]"), Task.ChipID);
	theApp.MainDlg->putListLog(szPos);


	if (MESCommunication.partNumber.CompareNoCase(Task.ChipID) == 0) 
	{ // 대소문자 무시 비교
		//AfxMessageBox(_T("Strings are equal!"));

		
		theApp.MainDlg->putListLog(_T("PartNumber Verify Ok"));
		MESCommunication.OTPVerifyFail.Format(_T("PASS"));
	}
	else 
	{
		theApp.MainDlg->putListLog(_T("PartNumber Verify Fail"));
		MESCommunication.OTPVerifyFail.Format(_T("NG"));
	}

	
	//MESCommunication.partNumber


	
	return true;
}
bool CMIU::OtpRead_Head_Fn()		//Head Model
{
	TCHAR szPos[SIZE_OF_1K];
	int i = 0;
	unsigned int errorCode = 0;
	unsigned short SlaveAddr = 0x24;
	unsigned short checkAddr = 0x3C06;


	const int Cmd1Length = 13;
	unsigned short writeAddrArr[Cmd1Length] = { 0x3000, 0x3001, 0x3002, 0x3003, 0x3004, 0x3005, 0x3006, 0x3007, 0x3008, 0x3009, 0x300a, 0x300b, 0x80bc };
	unsigned char writeData[Cmd1Length] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x30, 0x17, 0x01, 0xF2, 0x01 };
	//
	unsigned char pReadData[MAX_PATH];
	memset(pReadData, 0x00, sizeof(pReadData));
	int writeDelay = 20;

	//
	//Command1 전송
	//
	for (i = 0; i < Cmd1Length; i++)
	{
		Sleep(writeDelay);
		errorCode = m_pBoard->WriteI2CBurst(SlaveAddr, writeAddrArr[i], 2, writeData + i, 1);
		if (errorCode)
		{
			_stprintf_s(szPos, SIZE_OF_1K, _T("#1 Addr:%0x WriteI2CBurst errorCode:%d"), writeAddrArr[i], errorCode);
			theApp.MainDlg->putListLog(szPos);
			return false;
		}
	}
	Sleep(15);
	//Command 1 End
	//
	//
	memset(pReadData, 0x00, sizeof(pReadData));
	errorCode = m_pBoard->ReadI2CBurst(SlaveAddr, checkAddr, 2, pReadData, (unsigned short)1);
	if (pReadData[0] != 0x99)
	{
		_stprintf_s(szPos, SIZE_OF_1K, _T("0x3c06[%02X] Read Fail errorCode:%d"), pReadData[0], errorCode);
		theApp.MainDlg->putListLog(szPos);
		return false;
	}
	//
	//Command2 전송
	//
	const int Cmd2Length = 13;
	writeData[0] = 0x00;
	writeData[1] = 0x00;
	writeData[2] = 0x00;
	writeData[3] = 0x00;
	writeData[4] = 0x00;
	writeData[5] = 0x06;
	writeData[6] = 0x00;
	writeData[7] = 0x00;
	writeData[8] = 0x3D;
	writeData[9] = 0x81;
	writeData[10] = 0x01;
	writeData[11] = 0x01;
	writeData[12] = 0x01;
	for (i = 0; i < Cmd2Length; i++)
	{
		Sleep(writeDelay);
		errorCode = m_pBoard->WriteI2CBurst(SlaveAddr, writeAddrArr[i], 2, writeData + i, 1);
		if (errorCode)
		{
			_stprintf_s(szPos, SIZE_OF_1K, _T("#2 Addr:%0x WriteI2CBurst errorCode:%d"), writeAddrArr[i], errorCode);
			theApp.MainDlg->putListLog(szPos);
			return false;
		}
	}
	Sleep(15);
	//Command 2 End
	//
	//
	memset(pReadData, 0x00, sizeof(pReadData));
	errorCode = m_pBoard->ReadI2CBurst(SlaveAddr, checkAddr, 2, pReadData, (unsigned short)1);
	if (pReadData[0] != 0x99)
	{
		_stprintf_s(szPos, SIZE_OF_1K, _T("0x3c06[%02X] Read Fail errorCode:%d"), pReadData[0], errorCode);
		theApp.MainDlg->putListLog(szPos);
		return false;
	}
	//
	//Command3 전송
	const int Cmd3Length = 12;
	//
	writeData[0] = 0x00;
	writeData[1] = 0x00;
	writeData[2] = 0x00;
	writeData[3] = 0x00;
	writeData[4] = 0x00;
	writeData[5] = 0x05;
	writeData[6] = 0x01;
	writeData[7] = 0x00;
	writeData[8] = 0x70;
	writeData[9] = 0x18;
	writeData[10] = 0x0C;
	writeData[11] = 0x01;

	writeAddrArr[11] = 0x80bc;
	for (i = 0; i < Cmd3Length; i++)
	{
		Sleep(writeDelay);
		errorCode = m_pBoard->WriteI2CBurst(SlaveAddr, writeAddrArr[i], 2, writeData + i, 1);
		if (errorCode)
		{
			_stprintf_s(szPos, SIZE_OF_1K, _T("#3 Addr:%0x WriteI2CBurst errorCode:%d"), writeAddrArr[i], errorCode);
			theApp.MainDlg->putListLog(szPos);
			return false;
		}
	}
	Sleep(15);

	//Command 3 End
	// 
	memset(pReadData, 0x00, sizeof(pReadData));
	errorCode = m_pBoard->ReadI2CBurst(SlaveAddr, checkAddr, 2, pReadData, (unsigned short)1);
	if (pReadData[0] != 0x99)
	{
		_stprintf_s(szPos, SIZE_OF_1K, _T("0x3c06[%02X] Read Fail errorCode:%d"), pReadData[0], errorCode);
		theApp.MainDlg->putListLog(szPos);
		return false;
	}

	//Part Number Read(3C07 ~ 3C12)
	const int pnReadLength = 12;
	unsigned char pData[MAX_PATH];
	memset(pData, 0x00, sizeof(pData));

	Sleep(15);
	errorCode = m_pBoard->ReadI2CBurst(SlaveAddr, 0x3C07, 2, pData, pnReadLength);
	if (errorCode)
	{
		_stprintf_s(szPos, SIZE_OF_1K, _T("PartNumber Read errorCode:%d"), errorCode);
		theApp.MainDlg->putListLog(szPos);
		return false;
	}
	CString tempData = _T("");
	for (i = 0; i < pnReadLength; i++)
	{
		tempData.AppendFormat("%02X", (char*)pData[i]);
	}
	MESCommunication.partNumber.Format(_T("%s"), CovertToChar(tempData, ASCII_MODE));
	_stprintf_s(szPos, SIZE_OF_1K, _T("PartNumber Read :[%s/%s]"), tempData, MESCommunication.partNumber);
	theApp.MainDlg->putListLog(szPos);

	tempData.Empty();
	return true;
}
bool CMIU::SensorIdRead_Head_Fn()
{
	TCHAR szPos[SIZE_OF_1K];
	int i = 0;
	unsigned int errorCode = 0;
	unsigned short SlaveAddr = 0x24;
	unsigned short Addr = 0x0000;
	unsigned short checkAddr = 0x3C06;
	const int Cmd1Length = 13;
	unsigned short AddrArr[Cmd1Length] = { 0x3000, 0x3001, 0x3002, 0x3003, 0x3004, 0x3005, 0x3006, 0x3007, 0x3008, 0x3009, 0x300a, 0x300b, 0x80bc };
	unsigned char Data[Cmd1Length] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x30, 0x17, 0x01, 0xF2, 0x01};

	unsigned char pReadData[MAX_PATH];
	memset(pReadData, 0x00, sizeof(pReadData));
	int writeDelay = 20;
	unsigned char test = 0x00;

	//memcpy(pReadData, Data + 5, 1);
	//
	//Command 1 Run
	//
	for (i = 0; i < Cmd1Length; i++)
	{
		Sleep(writeDelay);
		errorCode = m_pBoard->WriteI2CBurst(SlaveAddr, AddrArr[i], 2, Data + i, 1);
		if (errorCode)
		{
			_stprintf_s(szPos, SIZE_OF_1K, _T("Addr:%0x WriteI2CBurst errorCode:%d"), AddrArr[i], errorCode);
			theApp.MainDlg->putListLog(szPos);
			return false;
		}
	}

	Sleep(writeDelay);
	//Command 1 End
	//
	//
	memset(pReadData, 0x00, sizeof(pReadData));
	errorCode = m_pBoard->ReadI2CBurst(SlaveAddr, checkAddr, 2, pReadData, (unsigned short)1);
	if (pReadData[0] != 0x99)
	{
		if (pReadData[0] != 0x99)
		{
			return false;
		}
	}

	//Command2 진행
	//
	const int Cmd2Length = 13;
	Data[0] = 0x00;
	Data[1] = 0x00;
	Data[2] = 0x00;
	Data[3] = 0x00;
	Data[4] = 0x00;
	Data[5] = 0x06;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Data[8] = 0x3D;
	Data[9] = 0x81;
	Data[10] = 0x01;
	Data[11] = 0x01;
	Data[12] = 0x01;
	for (i = 0; i < Cmd2Length; i++)
	{
		Sleep(writeDelay);
		errorCode = m_pBoard->WriteI2CBurst(SlaveAddr, AddrArr[i], 2, Data + i, 1);
		if (errorCode)
		{
			_stprintf_s(szPos, SIZE_OF_1K, _T("Addr:%0x WriteI2CBurst errorCode:%d"), AddrArr[i], errorCode);
			theApp.MainDlg->putListLog(szPos);
			return false;
		}
	}
	//Command 2 End
	//
	Sleep(writeDelay);
	//
	//
	memset(pReadData, 0x00, sizeof(pReadData));
	errorCode = m_pBoard->ReadI2CBurst(SlaveAddr, checkAddr, 2, pReadData, (unsigned short)1);
	if (pReadData[0] != 0x99)
	{
		if (pReadData[0] != 0x99)
		{
			return false;
		}
	}
	Sleep(15);

	//Command3 진행
	const int Cmd3Length = 12;
	//
	Data[0] = 0x00;
	Data[1] = 0x00;
	Data[2] = 0x00;
	Data[3] = 0x00;
	Data[4] = 0x00;
	Data[5] = 0x05;
	Data[6] = 0x01;
	Data[7] = 0x00;
	Data[8] = 0x70;
	Data[9] = 0x00;
	Data[10] = 0x10;
	Data[11] = 0x01;

	AddrArr[11] = 0x80bc;

	for (i = 0; i < Cmd3Length; i++)		//Command3은  12개
	{
		Sleep(writeDelay);
		errorCode = m_pBoard->WriteI2CBurst(SlaveAddr, AddrArr[i], 2, Data + i, 1);
		if (errorCode)
		{
			_stprintf_s(szPos, SIZE_OF_1K, _T("Addr:%0x WriteI2CBurst errorCode:%d"), AddrArr[i], errorCode);
			theApp.MainDlg->putListLog(szPos);
			return false;
		}
	}
	//Command 3 End
	//
	Sleep(writeDelay);
	//
	//
	memset(pReadData, 0x00, sizeof(pReadData));
	errorCode = m_pBoard->ReadI2CBurst(SlaveAddr, checkAddr, 2, pReadData, (unsigned short)1);
	if (pReadData[0] != 0x99)
	{
		if (pReadData[0] != 0x99)
		{
			return false;
		}
	}

	//Sensor ID Read (3C07 ~ 3C16)

	const int snReadLength = 16;
	unsigned char pData[MAX_PATH];
	memset(pData, 0x00, sizeof(pData));

	Sleep(15);
	errorCode = m_pBoard->ReadI2CBurst(SlaveAddr, 0x3C07, 2, pData, snReadLength);
	if (errorCode)
	{
		_stprintf_s(szPos, SIZE_OF_1K, _T("Sensor Id Read errorCode:%d"), errorCode);
		theApp.MainDlg->putListLog(szPos);
		return false;
	}
	CString tempData = _T("");
	for (i = 0; i < snReadLength; i++)
	{
		tempData.AppendFormat("%02X", (char*)pData[i]);
	}

	MESCommunication.sensorId.Format(_T("%s"), tempData);


	_stprintf_s(szPos, SIZE_OF_1K, _T("Sensor Read :[%s]"), MESCommunication.sensorId);
	theApp.MainDlg->putListLog(szPos);

	tempData.Empty();
	return true;
}
bool CMIU::FwVersionRead_Head_Fn()
{
	TCHAR szPos[SIZE_OF_1K];
	int i = 0;
	unsigned int errorCode = 0;
	unsigned short SlaveAddr = 0x24;
	unsigned short checkAddr = 0x3C06;


	const int Cmd1Length = 7;
	unsigned short writeAddrArr[Cmd1Length] = { 0x3000, 0x3001, 0x3002, 0x3003, 0x3004, 0x3005, 0x80bc };
	unsigned char writeData[Cmd1Length] = { 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x01 };
	//
	unsigned char pReadData[MAX_PATH];
	memset(pReadData, 0x00, sizeof(pReadData));
	int writeDelay = 20;

	//Command 1 Run
		//
	for (i = 0; i < Cmd1Length; i++)
	{
		Sleep(writeDelay);
		errorCode = m_pBoard->WriteI2CBurst(SlaveAddr, writeAddrArr[i], 2, writeData + i, 1);
		if (errorCode)
		{
			_stprintf_s(szPos, SIZE_OF_1K, _T("Addr:%0x WriteI2CBurst errorCode:%d"), writeAddrArr[i], errorCode);
			theApp.MainDlg->putListLog(szPos);
			return false;
		}
	}

	Sleep(writeDelay);
	//Command 1 End
	//
	//



	memset(pReadData, 0x00, sizeof(pReadData));
	errorCode = m_pBoard->ReadI2CBurst(SlaveAddr, checkAddr, 2, pReadData, (unsigned short)1);
	if (pReadData[0] != 0x99)
	{
		_stprintf_s(szPos, SIZE_OF_1K, _T("0x3c06[%02X] Read Fail errorCode:%d"), pReadData[0], errorCode);
		theApp.MainDlg->putListLog(szPos);
		return false;
	}

	_stprintf_s(szPos, SIZE_OF_1K, _T("0x3c06[%02X] Read Pass"), pReadData[0]);
	theApp.MainDlg->putListLog(szPos);

	//
	// //
	// //
	//firmware version 읽기 (0x3C07 ~ 0x3C04)

	const int fwReadLength = 4;
	unsigned char pData[MAX_PATH];
	memset(pData, 0x00, sizeof(pData));

	Sleep(15);
	errorCode = m_pBoard->ReadI2CBurst(SlaveAddr, 0x3C07, 2, pData, fwReadLength);
	if (errorCode)
	{
		_stprintf_s(szPos, SIZE_OF_1K, _T("firmware version Read errorCode:%d"), errorCode);
		theApp.MainDlg->putListLog(szPos);
		return false;
	}
	CString tempData = _T("");

	/*for (i = 0; i < fwReadLength; i++)
	{
		tempData.AppendFormat("%02X", (char*)pData[i]);
	}*/

	tempData.Format("%02X%02X%02X%02X", (char*)pData[3], (char*)pData[2], (char*)pData[1], (char*)pData[0]);
	
	MESCommunication.fwVersion.Format(_T("%s"), tempData);
	//Firmware version: 0x00000006 ->v6


	_stprintf_s(szPos, SIZE_OF_1K, _T("firmware version Read :[%s]"), MESCommunication.fwVersion);
	theApp.MainDlg->putListLog(szPos);


	tempData.Empty();

	return true;

}

void CMIU::ISPmodeCheck()
{
	unsigned int errorCode = 0, i;
	unsigned short ReadByteCount;
	unsigned short AddressByteCount;
	unsigned short SlaveAddress;
	unsigned short TempAdress1[22] = { 0x33, 0x47, 0x0F, 0x00, 0x00, 0x00, 0x53, 0x00, 0x80, 0x02 ,0x00,0x00,0x00,0x00,0xFA,0x00,0x00, 0x00 ,0x00,0x00,0x00, 0x00 };
	unsigned short TempAdress2[11] = { 0x33, 0x51, 0x07, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00 };
	unsigned char TempData1[6] = { 0, };// = new unsigned short[6];//unsigned char TempData1[6] = { 0, };

	unsigned char TempData2[19] = { 0, };
	unsigned short checksum = 0;
	SlaveAddress = 0x6D;
	AddressByteCount = 22;
	ReadByteCount = 6;
	checksum = ChecksumCalc(TempAdress1, 22);
	TempAdress1[21] = checksum;
	errorCode = m_pBoard->ReadI2CMultiAddrBurst(SlaveAddress, TempAdress1, AddressByteCount, TempData1, ReadByteCount);
	//WriteI2CMultiAddrBurst

	if (errorCode)
	{
		CString ErrorMessage;
		ErrorMessage.Format(_T("BurstRead Fail!!! (Code : 0x%x)"), errorCode);
		AfxMessageBox(ErrorMessage);
	}
	TempAdress2[3] = TempData1[3];
	checksum = ChecksumCalc(TempAdress2, 11);
	TempAdress2[10] = checksum;
	AddressByteCount = 11;
	ReadByteCount = 19;

	errorCode = m_pBoard->ReadI2CMultiAddrBurst(SlaveAddress, TempAdress2, AddressByteCount, TempData2, ReadByteCount);
	if (!errorCode)
	{
		CString csFormat, csFormat1, csFormat2, csFormat3, csTemp1, csTemp2;
		for (i = 0; i < ReadByteCount; i++)
		{
			csTemp1.Format("%02X", TempData2[i]);
			csFormat1 += csTemp1;
		}
		csTemp2.Format("%02X", TempData2[15]);
		csFormat2 += csTemp2;
		csFormat = _T("ISP Mode:0x") + csFormat2 + _T(" , Read Data:") + csFormat1;
		//m_ctrlEditReadData.SetWindowTextA(csFormat);
		if (csFormat2 == _T("01")) csFormat3 = _T(" : rgb888_hdr");
		else if (csFormat2 == _T("02")) csFormat3 = _T(" : raw20");
		else if (csFormat2 == _T("03")) csFormat3 = _T(" : rgb888_linear");
		csFormat = _T("ISP Mode(0x") + csFormat2 + _T(")") + csFormat3;
		theApp.MainDlg->putListLog("rgb="+csFormat);
		//QueryResMsg(csFormat);
	}
	else
	{
		CString ErrorMessage;
		ErrorMessage.Format(_T("BurstRead Fail!!! (Code : 0x%x)"), errorCode);
		AfxMessageBox(ErrorMessage);
	}
	return; 
}
void CMIU::SwitchLinearToHDRMode()
{
	unsigned int errorCode = 0, i;
	unsigned short ReadByteCount, DataByteCount;
	unsigned short AddressByteCount;
	unsigned short SlaveAddress;
	unsigned short TempAdress1[18] = { 0x33, 0x47, 0x0B, 0x00, 0x00, 0x00, 0x12, 0x00, 0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00 };
	//unsigned short TempAdress1[18] = { 0x33, 0x47, 0x0B, 0x00, 0x00, 0x00, 0x12, 0x00, 0x80, 0x03,0x00,0x00,0x00,0x02,0x00,0x00,0x00, 0x00 };
	unsigned char TempData1[9] = { 0, };
	unsigned short checksum = 0;
	SlaveAddress = 0x6D;
	AddressByteCount = 18;
	ReadByteCount = 9;
	checksum = ChecksumCalc(TempAdress1, 18);
	TempAdress1[17] = checksum;
	//errorCode = I2CMABurstRead(SlaveAddress, TempAdress1, AddressByteCount, ReadByteCount, TempData1);
	errorCode = m_pBoard->ReadI2CMultiAddrBurst(SlaveAddress, TempAdress1, AddressByteCount, TempData1, ReadByteCount);
	if (errorCode)
	{
		CString ErrorMessage;
		ErrorMessage.Format(_T("BurstRead Fail!!! (Code : 0x%x)"), errorCode);
		AfxMessageBox(ErrorMessage);
	}
	//unsigned short TempAddr[2] = { 0x02,0xD6 };
	unsigned short TempAddr = 0x02D6;
	unsigned short ___TempAddr[2] = { 0x02, 0xD6};
	unsigned char TempData3[1] = { 0x9C, };
	unsigned char TempData4[1] = { 0x80, };
	unsigned short SlaveTempAddr = 0xC4;
	Sleep(1500);
	//SerFsyncControl(SER_SLAVE_ADDR, TempAddr, TempData3);
	//errorCode = m_pBoard->WriteI2CBurst(SlaveTempAddr, TempAddr, 2, TempData3, 1);
	//
	unsigned int nSlaveAddress = 0x62;// 0xC4;
	unsigned int nAddress = 0x02D6;
	unsigned char pData[5];
	pData[0] = 0x9C;
	//
	//errorCode = m_pBoard->WriteI2CBurst((unsigned short)nSlaveAddress, (unsigned short)nAddress, 2, pData, (unsigned short)1);
	errorCode = m_pBoard->WriteI2CBurst(SlaveTempAddr, TempAddr, 2, TempData3, 1);
	Sleep(50);
	//SerFsyncControl(SER_SLAVE_ADDR, TempAddr, TempData4);
	errorCode = m_pBoard->WriteI2CBurst(SlaveTempAddr, TempAddr, 2, TempData4, 1);
	Sleep(50); 
	//SerFsyncControl(SER_SLAVE_ADDR, TempAddr, TempData3);
	errorCode = m_pBoard->WriteI2CBurst(SlaveTempAddr, TempAddr, 2, TempData3, 1);
	Sleep(1000);
	ISPmodeCheck();

}
void CMIU::SwitchHDRToLinearMode()
{
	unsigned int errorCode = 0, i;
	unsigned short ReadByteCount;
	unsigned short DataByteCount;
	unsigned short AddressByteCount;
	unsigned short SlaveAddress;
	unsigned short TempAdress1[18] = { 0x33, 0x47, 0x0B, 0x00, 0x00, 0x00, 0x12, 0x00, 0x80, 0x03,0x00,0x00,0x00,0x02,0x00,0x00,0x00, 0x00 };
	unsigned char TempData1[9] = { 0, };
	unsigned short checksum = 0;
	SlaveAddress = 0x6D;
	AddressByteCount = 18;
	ReadByteCount = 9;
	checksum = ChecksumCalc(TempAdress1, 18); 
	TempAdress1[17] = checksum;
	errorCode = m_pBoard->ReadI2CMultiAddrBurst(SlaveAddress, TempAdress1, AddressByteCount, TempData1, ReadByteCount);
	if (errorCode)
	{
		CString ErrorMessage;
		ErrorMessage.Format(_T("BurstRead Fail!!! (Code : 0x%x)"), errorCode);
		AfxMessageBox(ErrorMessage);
	}
	unsigned short TempAddr = 0x02D6;// { 0x02, 0xD6 };//TempAddr[2] = { 0x02,0xD6 };
	unsigned char TempData3[1] = { 0x9C };
	unsigned char TempData4[1] = { 0x80 };
	unsigned short SlaveTempAddr = 0x62;// 0xC4;
	Sleep(1500);
	//SerFsyncControl(SER_SLAVE_ADDR, TempAddr, TempData3);//WriteI2CBurst , 1  0c4
	errorCode = m_pBoard->WriteI2CBurst(SlaveTempAddr, TempAddr, 2, TempData3, 1);
	Sleep(50);
	//SerFsyncControl(SER_SLAVE_ADDR, TempAddr, TempData4);
	errorCode = m_pBoard->WriteI2CBurst(SlaveTempAddr, TempAddr, 2, TempData4, 1);
	Sleep(50);
	//SerFsyncControl(SER_SLAVE_ADDR, TempAddr, TempData3);
	errorCode = m_pBoard->WriteI2CBurst(SlaveTempAddr, TempAddr, 2, TempData3, 1);
	Sleep(1000);
	ISPmodeCheck();
}
bool CMIU::SelectSensor()
{
	gMIUDevice.nWidth =  m_pBoard->GetWidth(); 
	gMIUDevice.nHeight =  m_pBoard->GetHeight();
	gMIUDevice.iPixelFormat = m_pBoard->GetDataFormat();
	gMIUDevice.nFrameImageSize = m_pBoard->GetFrameRawSize();

	////gMIUDevice.dTDATASPEC_n.eOutMode = OUTMODE_BAYER_GBRG;		//M_MPC 모델
	gMIUDevice.dTDATASPEC_n.eOutMode = (EOUTMODE)m_pBoard->GetOutMode();
	gMIUDevice.dTDATASPEC_n.eDataFormat = (EDATAFORMAT)m_pBoard->GetDataFormat();		//EDATAFORMAT 이 DATAFORMAT_YUV일때 +5
	gMIUDevice.dTDATASPEC_n.eSensorType = (ESENSORTYPE) m_pBoard->GetSensorType();

	gMIUDevice.dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_GRADIENT;
	gMIUDevice.dTDATASPEC_n.nBlackLevel = 0;
	return true;
}


void CMIU::GetImagePixelFormat(char* szPixelFormat, unsigned int* nPixelFormat)
{
	int nSelectIndex = 0;
	CString strPixelFormat;
	strPixelFormat.Format("%s", szPixelFormat); 

	
	if(strPixelFormat == "MIU_MONO8")						// Mono buffer format defines
	{
		nSelectIndex = 0; // Combo box index
		*nPixelFormat = MIU_MONO8;
	}
	else if(strPixelFormat == "MIU_MONO10_PACKED")
	{
		nSelectIndex = 1;
		*nPixelFormat = MIU_MONO10_PACKED;
	}
	else if(strPixelFormat == "MIU_MONO12_PACKED")
	{
		nSelectIndex = 2;
		*nPixelFormat = MIU_MONO12_PACKED;
	}
	else if(strPixelFormat == "MIU_MONO14")
	{
		nSelectIndex = 3;
		*nPixelFormat = MIU_MONO14;
	}
	else if(strPixelFormat == "MIU_BAYERGR8")				// Bayer buffer format defines
	{
		nSelectIndex = 4;
		*nPixelFormat = MIU_BAYERGR8;
	}
	else if(strPixelFormat == "MIU_BAYERRG8")
	{
		nSelectIndex = 5;
		*nPixelFormat = MIU_BAYERRG8;
	}
	else if(strPixelFormat == "MIU_BAYERGB8")
	{
		nSelectIndex = 6;
		*nPixelFormat = MIU_BAYERGB8;
	}
	else if(strPixelFormat == "MIU_BAYERBG8")
	{
		nSelectIndex = 7;
		*nPixelFormat = MIU_BAYERBG8;
	}
	else if(strPixelFormat == "MIU_BAYERGR10_PACKED")
	{
		nSelectIndex = 8;
		*nPixelFormat = MIU_BAYERGR10_PACKED;
	}
	else if(strPixelFormat == "MIU_BAYERRG10_PACKED")
	{
		nSelectIndex = 9;
		*nPixelFormat = MIU_BAYERRG10_PACKED;
	}
	else if(strPixelFormat == "MIU_BAYERGB10_PACKED")
	{
		nSelectIndex = 10;
		*nPixelFormat = MIU_BAYERGB10_PACKED;
	}
	else if(strPixelFormat == "MIU_BAYERBG10_PACKED")
	{
		nSelectIndex = 11;
		*nPixelFormat = MIU_BAYERBG10_PACKED;
	}
	else if(strPixelFormat == "MIU_BAYERGR12_PACKED")
	{
		nSelectIndex = 12;
		*nPixelFormat = MIU_BAYERGR12_PACKED;
	}
	else if(strPixelFormat == "MIU_BAYERRG12_PACKED")
	{
		nSelectIndex = 13;
		*nPixelFormat = MIU_BAYERRG12_PACKED;
	}
	else if(strPixelFormat == "MIU_BAYERGB12_PACKED")
	{
		nSelectIndex = 14;
		*nPixelFormat = MIU_BAYERGB12_PACKED;
	}
	else if(strPixelFormat == "MIU_BAYERBG12_PACKED")
	{
		nSelectIndex = 15;
		*nPixelFormat = MIU_BAYERBG12_PACKED;
	}
	else if(strPixelFormat == "MIU_RGB8_PACKED")		// RGB Packed buffer format defines
	{
		nSelectIndex = 16;
		*nPixelFormat = MIU_RGB8_PACKED;
	}
	else if(strPixelFormat == "MIU_BGR8_PACKED")
	{
		nSelectIndex = 17;
		*nPixelFormat = MIU_BGR8_PACKED;
	}
	else if(strPixelFormat == "MIU_RGB565")
	{
		nSelectIndex = 18;
		*nPixelFormat = MIU_RGB565;
	}
	else if(strPixelFormat == "MIU_BGR565")
	{
		nSelectIndex = 19;
		*nPixelFormat = MIU_BGR565;
	}
	else if(strPixelFormat == "MIU_YUV422_PACKED")		// YUV Packed buffer format defines
	{
		nSelectIndex = 20;
		*nPixelFormat = MIU_YUV422_PACKED;
	}
	else if(strPixelFormat == "MIU_YUV422_YUYV_PACKED")
	{
		nSelectIndex = 21;
		*nPixelFormat = MIU_YUV422_YUYV_PACKED;
	}
	else
	{
		AfxMessageBox("Check the Image Pixel Format!");
	}
}

//! 버퍼 생성
bool CMIU::cvBufferAlloc()
{
	int i = 0;
	CString logStr;
	int iWidth = m_pBoard->GetWidth();
	int iHeight = m_pBoard->GetHeight();

	//! 현재 정보의 유효성 검사	
	if ( gMIUDevice.nWidth <= 0 || gMIUDevice.nHeight <= 0 )
	{
		logStr.Format("  버퍼 생성 이상.");
		theApp.MainDlg->putListLog(logStr);
		logStr.Empty();
		return false;
	}
	if (gMIUDevice.imageItp != NULL)
	{
		cvReleaseImage(&gMIUDevice.imageItp);
		gMIUDevice.imageItp = NULL;
	}
	for (i = 0; i < 3; i++)
	{
		if (m_acvChildImage[i] != NULL)
		{
			cvReleaseImage(&m_acvChildImage[i]);
			m_acvChildImage[i] = NULL;
		}

		if (pImageBuf[i] != NULL)
		{
			cvReleaseImage(&pImageBuf[i]);
			pImageBuf[i] = NULL;
		}
	}

	
	if (m_pFrameRawBuffer != NULL)
	{
		delete[] m_pFrameRawBuffer;//delete[] m_pFrameRawBuffer; 
		m_pFrameRawBuffer = NULL;
	}
	
	if (m_pFrameBMPBuffer != NULL)
	{
		delete[] m_pFrameBMPBuffer;
		m_pFrameBMPBuffer = NULL;
	}
	if (vChartBuffet != NULL)
	{
		delete[] vChartBuffet;
		vChartBuffet = NULL;
	}
	if (vChart_Second_Buffet != NULL)
	{
		delete[] vChart_Second_Buffet;
		vChart_Second_Buffet = NULL;
	}
	if (vDefectMidBuffer_6500K != NULL)
	{
		delete[] vDefectMidBuffer_6500K;
		vDefectMidBuffer_6500K = NULL;
	}
	if (vDefectLowBuffer != NULL)
	{
		delete[] vDefectLowBuffer;
		vDefectLowBuffer = NULL;
	}
	if (vDefectMidBuffer_2800K != NULL)
	{
		delete[] vDefectMidBuffer_2800K;
		vDefectMidBuffer_2800K = NULL;
	}
	if (vTempBuffer != NULL)
	{
		delete[] vTempBuffer;
		vTempBuffer = NULL;
	}
	
	m_pFrameRawBuffer = new BYTE[m_pBoard->GetFrameRawSize()];
	vChartBuffet = new BYTE[m_pBoard->GetFrameRawSize()];
	vChart_Second_Buffet = new BYTE[m_pBoard->GetFrameRawSize()];
	vDefectMidBuffer_6500K = new BYTE[m_pBoard->GetFrameRawSize()];
	vDefectLowBuffer = new BYTE[m_pBoard->GetFrameRawSize()];
	vDefectMidBuffer_2800K = new BYTE[m_pBoard->GetFrameRawSize()];
	vTempBuffer = new BYTE[m_pBoard->GetFrameRawSize()];

	//bmp
	m_pFrameBMPBuffer = new BYTE[m_pBoard->GetFrameBMPSize()];
	memset(m_pFrameBMPBuffer, 0, m_pBoard->GetFrameBMPSize());
	//
	//
	//raw
	memset(vTempBuffer, 0, m_pBoard->GetFrameRawSize());
	memset(m_pFrameRawBuffer, 0, m_pBoard->GetFrameRawSize());
	memset(vChartBuffet, 0, m_pBoard->GetFrameRawSize());
	memset(vChart_Second_Buffet, 0, m_pBoard->GetFrameRawSize());
	memset(vDefectMidBuffer_6500K, 0, m_pBoard->GetFrameRawSize());
	memset(vDefectLowBuffer, 0, m_pBoard->GetFrameRawSize());
	memset(vDefectMidBuffer_2800K, 0, m_pBoard->GetFrameRawSize());


	gMIUDevice.imageItp = cvCreateImage(cvSize(gMIUDevice.nWidth,gMIUDevice.nHeight),IPL_DEPTH_8U,3);

	if ( m_bFlag_Mil_Convert == true )
	{
		m_acvChildImage[0] = cvCreateImage(cvSize(gMIUDevice.nWidth,gMIUDevice.nHeight), IPL_DEPTH_8U, 1);
		m_acvChildImage[1] = cvCreateImage(cvSize(gMIUDevice.nWidth,gMIUDevice.nHeight), IPL_DEPTH_8U, 1);
		m_acvChildImage[2] = cvCreateImage(cvSize(gMIUDevice.nWidth,gMIUDevice.nHeight), IPL_DEPTH_8U, 1);
	}	

	pImageBuf[0] = cvCreateImage(cvSize(iWidth, iHeight), IPL_DEPTH_8U, 1);
	pImageBuf[1] = cvCreateImage(cvSize(iWidth, iHeight), IPL_DEPTH_8U, 1);
	pImageBuf[2] = cvCreateImage(cvSize(iWidth, iHeight), IPL_DEPTH_8U, 1);

	//! <-------------------------------------------------------------------------------------------------------------------
	Init_Index_Grab();
	//! <-------------------------------------------------------------------------------------------------------------------

	
	logStr.Format("image buffer complete.");
	theApp.MainDlg->putListLog(logStr);

	logStr.Empty();
	return true;	
}

//! 버퍼 해제
void CMIU::cvBufferFree()
{
	int i = 0;
	//CString logStr;
	////.Format("  버퍼 해제 시작.");
	//theApp.MainDlg->putListLog(logStr);

	//! [주의 사항] 영상 취득만 중지해야한다. CCD의 전원까지 끄면 안된다.
	//Stop(false);
	//
	/*if ( gMIUDevice.imageItp != NULL )
	{
		cvReleaseImage(&gMIUDevice.imageItp);
		gMIUDevice.imageItp = NULL;
	}
	for (i = 0; i < 3; i++)
	{
		if (m_acvChildImage[i] != NULL)
		{
			cvReleaseImage(&m_acvChildImage[i]);
			m_acvChildImage[i] = NULL;
		}

		if (pImageBuf[i] != NULL)
		{
			cvReleaseImage(&pImageBuf[i]);
			pImageBuf[i] = NULL;
		}
	}
*/
	//logStr.Format("  버퍼 해제 완료.");
	//theApp.MainDlg->putListLog(logStr);
}


//! Open CV 이미지 ----> Mil Color 이미지 변환
bool CMIU::cvCopyToMil(MIL_ID* f_pDestBuf)
{
	if ( f_pDestBuf == NULL )
	{
		return false;
	}
	if ( m_bFlag_Mil_Convert == false )
	{
		return false;
	}
	if ( m_acvChildImage[0] == NULL || m_acvChildImage[1] == NULL || m_acvChildImage[2] == NULL )
	{
		cvBufferAlloc();		//cvCopyToMil
	}

	//! RGB 채널 분리..
	//cvCvtPixToPlane(gMIUDevice.imageItp, m_acvChildImage[0], m_acvChildImage[1], m_acvChildImage[2], NULL);
	cvSplit(gMIUDevice.imageItp, m_acvChildImage[0], m_acvChildImage[1], m_acvChildImage[2], NULL);

	MbufPut(f_pDestBuf[0], m_acvChildImage[2]->imageData);
	MbufPut(f_pDestBuf[1], m_acvChildImage[1]->imageData);
	MbufPut(f_pDestBuf[2], m_acvChildImage[0]->imageData);

	return true;
}

//! Mil Color 이미지 ----> Open CV 이미지
//! bFlag_Green : true이면 녹색 영역의 버퍼만 사용
bool CMIU::MilCopyToCv(MIL_ID* f_pDestBuf)
{
	if ( f_pDestBuf == NULL )
	{
		return false;
	}
	if ( m_bFlag_Mil_Convert == false )
	{
		return false;
	}
	if ( m_acvChildImage[0] == NULL || m_acvChildImage[1] == NULL || m_acvChildImage[2] == NULL )
	{
		cvBufferAlloc();	//MilCopyToCv
	}	

	MbufGet(f_pDestBuf[2], m_acvChildImage[0]->imageData);				// 2.6 msec
	MbufGet(f_pDestBuf[1], m_acvChildImage[1]->imageData);
	MbufGet(f_pDestBuf[0], m_acvChildImage[2]->imageData);
	
	//! 영상 전환 시 RGB --> BGR 로 색상 순서 변경..

	//cvCvtPlaneToPix(m_acvChildImage[2], m_acvChildImage[1], m_acvChildImage[0], NULL, gMIUDevice.imageItp);		// 57.5msec
	cvMerge(m_acvChildImage[2], m_acvChildImage[1], m_acvChildImage[0], NULL, gMIUDevice.imageItp);		// 57.5msec

	return true;
}


bool CMIU::CCM_Init()
{
	bool bRet = false;

	bRet = CcmInit();

	return bRet;
}

//! LPMC-500 Frame Grabber만 초기화
bool CMIU::MIU_Init()
{
//	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
//	CString logStr;
//	logStr.Format("[MIU] MIU_Init 호출.");
//	MiuLogSave(logStr);
//
//	//! 현재 정보의 유효성 검사
//	if ( m_iDeviceCount <= 0 )
//	{
//		return false;
//	}
//	
//	if ( m_pSID == NULL || m_iSensorListCnt <= 0 )
//	{
//		return false;
//	}	
//	if ( m_iSensor < 0 || m_iSensor >= m_iSensorListCnt )
//	{
//		return false;
//	}
//	if ( m_pSID[m_iSensor].pInfo == NULL || m_pSID[m_iSensor].nInfoCount <= 0 )
//	{
//		return false;
//	}
//	if ( m_iSensorType < 0 || m_iSensorType >= m_pSID[m_iSensor].nInfoCount )
//	{
//		return false;
//	}
//
//	if ( gMIUDevice.bMIUOpen != 1 )
//	{
//		sLogMessage.Format(_T("LPMC 연결을 확인하세요."));
//		return false;
//	}
//
//	//! CCD Sensor의 초기화 시작
//	gMIUDevice.CurrentState = 0;
//
//	char            szFile_Name_1[MAX_PATH]= {0};
//	char            szFile_Name[MAX_PATH]= {0};
//	char			szTemp[MAX_PATH];	
//	CString			strSectionValue;
//
//	//ISJ Data Load
//	//! CCD Sensor의 ini 파일의 절대 경로명을 알아낸다.
//	sprintf_s(szFile_Name, "%s\\%s_%s.ini", MIU_DIR, 
//		                                    m_pSID[m_iSensor].szSensorName, 
//											m_pSID[m_iSensor].pInfo[m_iSensorType].szResolution);
//
//#ifdef USE_MIU_OPEN_TACT
//	asTime[iCnt_Time].Format("FILE 확인 완료 - %.1f sec.", timeChecker.m_adTime[iCnt_Time] );
//	iCnt_Time++;
//#endif
//
//
//	//! CCD Sensor의 ini 파일에서 설정 정보를 읽어온다.
//			gMIUDevice.InitialValue.SensorMode = GetPrivateProfileInt("MIUConfiguration", "SensorMode" ,0 , szFile_Name);
//			gMIUDevice.InitialValue.nWidth = GetPrivateProfileInt("MIUConfiguration", "SensorWidth", 0, szFile_Name);
//			gMIUDevice.InitialValue.nHeight = GetPrivateProfileInt("MIUConfiguration", "SensorHeight", 0, szFile_Name);
//			gMIUDevice.nWidth = gMIUDevice.InitialValue.nWidth;
//			gMIUDevice.nHeight = gMIUDevice.InitialValue.nHeight;
//	
//			gMIUDevice.nMaxWidth = GetPrivateProfileInt("MIUConfiguration", "MAXWidth", 4000, szFile_Name);;			// Max Width
//			gMIUDevice.nMaxHeight = GetPrivateProfileInt("MIUConfiguration", "MAXHeight", 3000, szFile_Name);;			// Max Height   
//	
//			gMIUDevice.InitialValue.MCLKOnOff = GetPrivateProfileInt("MIUConfiguration", "MCLKOnOff" ,1 , szFile_Name);
//			gMIUDevice.InitialValue.MCLKSelection = GetPrivateProfileInt("MIUConfiguration", "MCLKSelection" ,1 , szFile_Name);
//			GetPrivateProfileString("MIUConfiguration","MCLK","0.0", szTemp, MAX_PATH, szFile_Name);
//			strSectionValue.Format("%s",szTemp);
//			sscanf(strSectionValue.GetBuffer(0),"%f",&gMIUDevice.InitialValue.MCLK);
//			//m_strMCLK.Format("%.2f",gMIUDevice.InitialValue.MCLK);
//	
//			gMIUDevice.InitialValue.PCLKInversion = GetPrivateProfileInt("MIUConfiguration", "PCLKInversion", 0, szFile_Name);
//			GetPrivateProfileString("MIUConfiguration","IICDeviceID","", szTemp, MAX_PATH, szFile_Name);
//			strSectionValue.Format("%s",szTemp);
//			sscanf(strSectionValue.GetBuffer(0),"%x",&gMIUDevice.InitialValue.IICDeviceID);
//			gMIUDevice.InitialValue.IICMode = GetPrivateProfileInt("MIUConfiguration", "IICMode", 0, szFile_Name);
//			gMIUDevice.InitialValue.IICSpeed = GetPrivateProfileInt("MIUConfiguration", "IICSpeed", 0, szFile_Name);
//			gMIUDevice.InitialValue.IICReadRestart = GetPrivateProfileInt("MIUConfiguration", "IICReadRestart", 1, szFile_Name);
//			gMIUDevice.InitialValue.IICReadRestartInterval = GetPrivateProfileInt("MIUConfiguration", "IICReadRestartInterval", 0, szFile_Name);
//			gMIUDevice.InitialValue.IICSCKPinCheck = GetPrivateProfileInt("MIUConfiguration", "IICSCKPinCheck", 0, szFile_Name);
//			gMIUDevice.InitialValue.IICAddressLength = GetPrivateProfileInt("MIUConfiguration", "IICAddressLength", 0, szFile_Name);
//			gMIUDevice.InitialValue.IICDataLength = GetPrivateProfileInt("MIUConfiguration", "IICDataLength", 0, szFile_Name);
//
//			gMIUDevice.InitialValue.MIPILaneEnable = GetPrivateProfileInt("MIUConfiguration", "MIPILaneEnable", 1, szFile_Name);
//			GetPrivateProfileString("MIUConfiguration","MIPIDataType","0x2B", szTemp, MAX_PATH, szFile_Name);
//			strSectionValue.Format("%s",szTemp);
//			sscanf(strSectionValue.GetBuffer(0),"%x",&gMIUDevice.InitialValue.MIPIDataType);
//	
//			gMIUDevice.InitialValue.MIPI8bitMode = GetPrivateProfileInt("MIUConfiguration", "MIPI8bitMode", 0, szFile_Name);
//
//			GetPrivateProfileString("MIUConfiguration","MIUIOVoltage","0.0", szTemp, MAX_PATH, szFile_Name);
//			strSectionValue.Format("%s",szTemp);
//			sscanf(strSectionValue.GetBuffer(0),"%f",&gMIUDevice.InitialValue.MIUIOVoltage);
//
//			gMIUDevice.InitialValue.FirstPowerChannel = GetPrivateProfileInt("MIUConfiguration", "1stPowerChannel", 0, szFile_Name);
//
//			GetPrivateProfileString("MIUConfiguration","1stPowerVoltage","0.0", szTemp, MAX_PATH, szFile_Name);
//			strSectionValue.Format("%s",szTemp);
//			sscanf(strSectionValue.GetBuffer(0),"%f",&gMIUDevice.InitialValue.FirstPowerVoltage);
//
//			gMIUDevice.InitialValue.SecondPowerChannel = GetPrivateProfileInt("MIUConfiguration", "2ndPowerChannel", 0, szFile_Name);
//
//			GetPrivateProfileString("MIUConfiguration","2ndPowerVoltage","0.0", szTemp, MAX_PATH, szFile_Name);
//			strSectionValue.Format("%s",szTemp);
//			sscanf(strSectionValue.GetBuffer(0),"%f",&gMIUDevice.InitialValue.SecondPowerVoltage);
//
//			gMIUDevice.InitialValue.ThirdPowerChannel = GetPrivateProfileInt("MIUConfiguration", "3rdPowerChannel", 0, szFile_Name);
//
//			GetPrivateProfileString("MIUConfiguration","3rdPowerVoltage","0.0", szTemp, MAX_PATH, szFile_Name);
//			strSectionValue.Format("%s",szTemp);
//			sscanf(strSectionValue.GetBuffer(0),"%f",&gMIUDevice.InitialValue.ThirdPowerVoltage);
//
//			gMIUDevice.InitialValue.FourthPowerChannel = GetPrivateProfileInt("MIUConfiguration", "4thPowerChannel", 0, szFile_Name);
//
//			GetPrivateProfileString("MIUConfiguration","4thPowerVoltage","0.0", szTemp, MAX_PATH, szFile_Name);
//			strSectionValue.Format("%s",szTemp);
//			sscanf(strSectionValue.GetBuffer(0),"%f",&gMIUDevice.InitialValue.FourthPowerVoltage);
//
//			gMIUDevice.InitialValue.FifthPowerChannel = GetPrivateProfileInt("MIUConfiguration", "5thPowerChannel", 0, szFile_Name);
//
//			GetPrivateProfileString("MIUConfiguration","5thPowerVoltage","0.0", szTemp, MAX_PATH, szFile_Name);
//			strSectionValue.Format("%s",szTemp);
//			sscanf(strSectionValue.GetBuffer(0),"%f",&gMIUDevice.InitialValue.FifthPowerVoltage);
//
//			gMIUDevice.InitialValue.Power5VoltOnOff = GetPrivateProfileInt("MIUConfiguration", "5VoltPowerOnOff", 0, szFile_Name);
//			gMIUDevice.InitialValue.Power12VoltOnOff = GetPrivateProfileInt("MIUConfiguration", "12VoltPowerOnOff", 0, szFile_Name);
//
//			gMIUDevice.InitialValue.InitialSkipCount = GetPrivateProfileInt("MIUConfiguration", "InitialSkipCount", 0, szFile_Name);
//			gMIUDevice.InitialValue.PreviewSkipCount = GetPrivateProfileInt("MIUConfiguration", "PreviewSkipCount", 0, szFile_Name);
//
//			gMIUDevice.InitialValue.ParallelSamplingMode = GetPrivateProfileInt("MIUConfiguration", "ParallelSamplingMode", 0, szFile_Name);
//			gMIUDevice.InitialValue.ParallelBitsPerPixel = GetPrivateProfileInt("MIUConfiguration", "ParallelBitsPerPixel", 0, szFile_Name);
//			gMIUDevice.InitialValue.ParallelPixelComponent = GetPrivateProfileInt("MIUConfiguration", "ParallelPixelComponent", 0, szFile_Name);
//			gMIUDevice.InitialValue.ParallelBitShift = GetPrivateProfileInt("MIUConfiguration", "ParallelBitShift", 0, szFile_Name);
//		
//	//! CCD Sensor에 초기 설정값을 적용한다.  
//	int iErrorCode = MIUInitialize(gDeviceIndex, gMIUDevice.InitialValue);
//	if ( iErrorCode != MIU_OK )
//	{
//		sLogMessage.Format(_T("'MIUInitialize'함수 오류 [%d]"), iErrorCode);
//
//		logStr.Format("[MIU[ MIU_Init 실패. CCD 동작을 다시 시작해 주세요.");
//		MiuLogSave(logStr);
//
//		pFrame->m_bMiuRun = false;
//
//		Close();
//
//		return false;
//	}
//
//#ifdef USE_MIU_OPEN_TACT
//	timeChecker.Measure_Time(iCnt_Time);
//	asTime[iCnt_Time].Format("MIU Init 완료 - %.1f sec.", timeChecker.m_adTime[iCnt_Time] - timeChecker.m_adTime[iCnt_Time-1] );
//	iCnt_Time++;
//#endif
//
//
//	gMIUDevice.bMIUInit = 1;
//
//	logStr.Format("[MIU] MIU_Init 완료.");
//	MiuLogSave(logStr);

	return true;
}


//! CCD Camera Sensor의 초기화만 진행한다.
bool CMIU::CCD_Init()
{
//	int errorCode;
//	CString logStr;
//	logStr.Format("[MIU] CCD_Init 호출.");
//	MiuLogSave(logStr);
//
//	//! 현재 정보의 유효성 검사
//	if ( m_iDeviceCount <= 0 )
//	{
//	return false;
//	}
//	if ( m_pSID == NULL || m_iSensorListCnt <= 0 )
//	{
//		return false;
//	}	
//	if ( m_iSensor < 0 || m_iSensor >= m_iSensorListCnt )
//	{
//		return false;
//	}
//	if ( m_pSID[m_iSensor].pInfo == NULL || m_pSID[m_iSensor].nInfoCount <= 0 )
//	{
//		return false;
//	}
//	if ( m_iSensorType < 0 || m_iSensorType >= m_pSID[m_iSensor].nInfoCount )
//	{
//		return false;
//	}
//
//	// 	if ( gMIUDevice.bMIUOpen != 1 )
//	// 	{
//	// 		sLogMessage.Format(_T("LPMC 연결을 확인하세요."));
//	// 		return false;
//	// 	}
//
//	if ( gMIUDevice.bMIUInit != 1 )
//	{
//		sLogMessage.Format(_T("LPMC Frame Grabber를 초기화 하십시오."));
//		return false;
//	}
//
//	logStr.Format("[MIU] CCD_Init 시작.");
//	MiuLogSave(logStr);
//
//	char            szFile_Name_1[MAX_PATH]= {0};
//	char            szFile_Name[MAX_PATH]= {0};
//	char			szTemp[MAX_PATH];
//	CStdioFile      flInitialFile;
//	CFileException  e;
//	CString         szLineRead;
//	char            fInitMode = 0;
//	unsigned int    nAddress, nData;
//	int				errorCount = 0;
//	BYTE			BurstWriteData[2048];
//	int				BurstWriteLength = 0;
//	int				BurstWriteLengthaddr = 0;
//	unsigned short  addr, data;
//	unsigned int	bustSleep	= 0;
//
//	int				i = 0;
//	bool			bFlag_Error_Display = false;
//	bool			bFlag_Error = false;
//
//	//int             iErrorCode = MIU_OK;
//
//	//! CCD Sensor의 ini 파일의 절대 경로명을 알아낸다.
//	sprintf_s(szFile_Name, "%s\\%s_%s.ini", MIU_DIR, 
//			  m_pSID[m_iSensor].szSensorName, 
//			  m_pSID[m_iSensor].pInfo[m_iSensorType].szResolution);
//
//	//! CCD Sensor의 ini 파일을 읽을 수 있도록 Open 합니다.
//	if(!flInitialFile.Open(szFile_Name, CFile::modeRead, &e))
//	{
//		sLogMessage.Format(_T("CCD Sensor의 ini 파일을 읽을 수 없습니다.{%s}"), szFile_Name);
//		return false;
//	}
//
//	//! 오류 Flag 초기화
//	bFlag_Error = false;
//
//	//! CCD Sensor의 ini 파일에서 Registry 설정 정보를 읽어와서, 
//	//! LPMC-500 Frame Grabber ('[MIU] 항목')와 CCD Sensor ('[Sensor] 항목')의 Registry에 실제로 적용합니다.
//
//#ifdef USE_MIU_OPEN_TACT
//	timeChecker.Measure_Time(iCnt_Time);
//	asTime[iCnt_Time].Format("CCD Init File Open 확인 While문 시작 - %.1f sec.", timeChecker.m_adTime[iCnt_Time] - timeChecker.m_adTime[iCnt_Time-1] );
//	iCnt_Time++;
//#endif
//
//	flInitialFile.SeekToBegin();
//	while( flInitialFile.ReadString(szLineRead) )
//	{		
//		if((szLineRead.Find("[MIU]")!=-1)&&(szLineRead.Find("[MIU]")<2))
//		{
//			fInitMode = 1;
//			
//		}
//		else if((szLineRead.Find("[Sensor]")!=-1)&&(szLineRead.Find("[Sensor]")<2))
//		{
//			fInitMode = 2;				
//		}
//		else if(((szLineRead.Find("Sleep")!=-1)&&((szLineRead.Find("Sleep")<2)))||((szLineRead.Find("SLEEP")!=-1)&&((szLineRead.Find("SLEEP")<2))))
//		{
//			sscanf(szLineRead.GetBuffer(0),"%s%d",szTemp,&nData);
//			if(BurstWriteLength == 0)
//			{
//				////////////////////////// 20130711 TRACE 추가
//				TRACE("Sleep = %d \n",nData);
//				Sleep(nData);
//				bustSleep = 0;
//			}
//			else
//			{
//				bustSleep = nData;
//
//			}			
//		}
//		else if(((szLineRead.Find("RESET")!=-1)&&((szLineRead.Find("RESET")<2)))||((szLineRead.Find("reset")!=-1)&&((szLineRead.Find("reset")<2))))
//		{
//			sscanf(szLineRead.GetBuffer(0),"%s%d",szTemp,&nData);
//			MIUWriteRegister(gDeviceIndex, REG_MIU, 0x04, (unsigned short) nData);			
//		}
//		else if(((szLineRead.Find("ENABLE")!=-1)&&((szLineRead.Find("ENABLE")<2)))||((szLineRead.Find("enable")!=-1)&&((szLineRead.Find("enable")<2))))
//		{
//			sscanf(szLineRead.GetBuffer(0),"%s%d",szTemp,&nData);
//			MIUWriteRegister(gDeviceIndex, REG_MIU, 0x05, (unsigned short) nData);			
//		}
//		else if(((szLineRead.Find("GPIO0")!=-1)&&((szLineRead.Find("GPIO0")<2)))||((szLineRead.Find("gpio0")!=-1)&&((szLineRead.Find("gpio0")<2))))
//		{
//			sscanf(szLineRead.GetBuffer(0),"%s%d",szTemp,&nData);
//			MIUSetGPIOStatus(gDeviceIndex, 0, nData);			
//		}
//		else if(((szLineRead.Find("GPIO1")!=-1)&&((szLineRead.Find("GPIO1")<2)))||((szLineRead.Find("gpio1")!=-1)&&((szLineRead.Find("gpio1")<2))))
//		{
//			sscanf(szLineRead.GetBuffer(0),"%s%d",szTemp,&nData);
//			MIUSetGPIOStatus(gDeviceIndex, 1, nData);				
//		}
//		else if(((szLineRead.Find("GPIO2")!=-1)&&((szLineRead.Find("GPIO2")<2)))||((szLineRead.Find("gpio2")!=-1)&&((szLineRead.Find("gpio2")<2))))
//		{
//			sscanf(szLineRead.GetBuffer(0),"%s%d",szTemp,&nData);
//			MIUSetGPIOStatus(gDeviceIndex, 2, nData);				
//		}
//		else if(((szLineRead.Find("GPIO3")!=-1)&&((szLineRead.Find("GPIO3")<2)))||((szLineRead.Find("gpio3")!=-1)&&((szLineRead.Find("gpio3")<2))))
//		{
//			sscanf(szLineRead.GetBuffer(0),"%s%d",szTemp,&nData);
//			MIUSetGPIOStatus(gDeviceIndex, 3, nData);				
//		}
//		else if(((szLineRead.Find("GPO0")!=-1)&&((szLineRead.Find("GPO0")<2)))||((szLineRead.Find("gpo0")!=-1)&&((szLineRead.Find("gpo0")<2))))
//		{
//			sscanf(szLineRead.GetBuffer(0),"%s%d",szTemp,&nData);
//			MIUSetGPOStatus(gDeviceIndex, 0, nData);			
//		}
//		else if(((szLineRead.Find("GPO1")!=-1)&&((szLineRead.Find("GPO1")<2)))||((szLineRead.Find("gpo1")!=-1)&&((szLineRead.Find("gpo1")<2))))
//		{
//			sscanf(szLineRead.GetBuffer(0),"%s%d",szTemp,&nData);
//			MIUSetGPOStatus(gDeviceIndex, 0, nData);			
//		}
//		else if(((szLineRead.Find("GPIOMODE0")!=-1)&&((szLineRead.Find("GPIOMODE0")<2)))||((szLineRead.Find("gpiomode0")!=-1)&&((szLineRead.Find("gpiomode0")<2))))
//		{
//			sscanf(szLineRead.GetBuffer(0),"%s%d",szTemp,&nData);
//			MIUSetGPIOMode(gDeviceIndex, 0, nData);		
//		}
//		else if(((szLineRead.Find("GPIOMODE1")!=-1)&&((szLineRead.Find("GPIOMODE1")<2)))||((szLineRead.Find("gpiomode1")!=-1)&&((szLineRead.Find("gpiomode1")<2))))
//		{
//			sscanf(szLineRead.GetBuffer(0),"%s%d",szTemp,&nData);
//			MIUSetGPIOMode(gDeviceIndex, 1, nData);		
//		}
//		else if(((szLineRead.Find("GPIOMODE2")!=-1)&&((szLineRead.Find("GPIOMODE2")<2)))||((szLineRead.Find("gpiomode2")!=-1)&&((szLineRead.Find("gpiomode2")<2))))
//		{
//			sscanf(szLineRead.GetBuffer(0),"%s%d",szTemp,&nData);
//			MIUSetGPIOMode(gDeviceIndex, 2, nData);		
//		}
//		else if(((szLineRead.Find("GPIOMODE3")!=-1)&&((szLineRead.Find("GPIOMODE3")<2)))||((szLineRead.Find("gpiomode3")!=-1)&&((szLineRead.Find("gpiomode3")<2))))
//		{
//			sscanf(szLineRead.GetBuffer(0),"%s%d",szTemp,&nData);
//			MIUSetGPIOMode(gDeviceIndex, 3, nData);		
//		}
//		else if(((szLineRead.Find("BULK")!=-1)&&((szLineRead.Find("BULK")<2)))||((szLineRead.Find("Bulk")!=-1)&&((szLineRead.Find("Bulk")<2))))
//		{
//			unsigned int	nCount; 
//			unsigned char	pData[256];
//			CString	 strInput;
//
//			sscanf(szLineRead.GetBuffer(0),"%s%d",szTemp,&nCount);
//
//			switch(nCount)
//			{
//				case 1:
//					sscanf(szLineRead.GetBuffer(0),"%s%d %x",szTemp,&nCount, pData);
//					break;
//				case 2:
//					sscanf(szLineRead.GetBuffer(0),"%s%d %x %x",szTemp,&nCount, &pData[0], &pData[1]);
//					break;
//				case 3:
//					sscanf(szLineRead.GetBuffer(0),"%s%d %x %x %x",szTemp,&nCount, &pData[0], &pData[1], &pData[2]);
//					break;
//				case 4:
//					sscanf(szLineRead.GetBuffer(0),"%s%d %x %x %x %x",szTemp,&nCount, &pData[0], &pData[1], &pData[2], &pData[3]);
//					break;
//				case 5:
//					sscanf(szLineRead.GetBuffer(0),"%s%d %x %x %x %x %x",szTemp,&nCount, &pData[0], &pData[1], &pData[2], &pData[3], &pData[4]);
//					break;
//				default:
//					break;
//			}
//			if(fInitMode == 2)
//			{
//				errorCode = MIUI2CBurstWrite(gDeviceIndex, gMIUDevice.InitialValue.IICDeviceID, pData[0], 1, &pData[1], nCount-1);
//				if(errorCode)
//				{
//					errorCount++;
//					TRACE("Error Code : 0x%x\n", errorCode);
//				}
//			}
//
//		}
//		else if(((szLineRead.Find("BITFIELD")!=-1)&&((szLineRead.Find("BITFIELD")<2)))||((szLineRead.Find("Bitfield")!=-1)&&((szLineRead.Find("Bitfield")<2))))
//		{
//			unsigned int	bitfield; 
//			unsigned int    ReadValue;
//			unsigned char	value;
//			CString	 strInput;
//			sscanf(szLineRead.GetBuffer(0),"%s %x %x %d",nAddress,&bitfield, &value);
//			if(fInitMode == 1)
//			{				
//				MIUReadRegister(gDeviceIndex, REG_MIU, (unsigned short) nAddress, (unsigned short*) &ReadValue);
//			}
//			else if(fInitMode == 2)
//			{
//				MIUReadRegister(gDeviceIndex, REG_IIC1, (unsigned short) nAddress, (unsigned short*) &ReadValue);
//			}
//			
//			if(value == 0)
//			{
//				ReadValue &= bitfield ^ 0xFFFFFFFF;
//			}
//			else
//			{
//				ReadValue |= bitfield;
//			}
//
//			if(fInitMode == 1)
//			{
//				TRACE("MIU Addr %x, DAta %x \n", nAddress, ReadValue);
//				MIUWriteRegister(gDeviceIndex, REG_MIU, (unsigned short) nAddress, (unsigned short) ReadValue);
//			}
//			else if(fInitMode == 2)
//			{
//				TRACE("Sensor Addr %x, DAta %x \n", nAddress, ReadValue);
//				MIUWriteRegister(gDeviceIndex, REG_IIC1, (unsigned short) nAddress, (unsigned short) ReadValue);
//				Sleep(1);
//			}		
//		}
//		else if(((szLineRead.Find("0x")!=-1)||(szLineRead.Find("0X")!=-1))&&(szLineRead.Find("0")==0))
//		{
//			sscanf_s(szLineRead.GetBuffer(0),"%x%x",&nAddress,&nData);
//            
//			if(fInitMode == 1)
//			{				
//				TRACE("MIU Addr %x, DAta %x \n", nAddress, nData);
//				errorCode = MIUWriteRegister(gDeviceIndex, REG_MIU, (unsigned short) nAddress, (unsigned short) nData);
//				if(errorCode)
//				{
//					errorCount++;
//					TRACE("Error Code : 0x%x\n", errorCode);
//				}
//			}
//			else if(fInitMode == 2)
//			{
//				// 0722
//				if(m_Burst == TRUE &&  (nAddress == 0x0F12  || nAddress == 0x0F14) )
//				{
//					if (BurstWriteLength == 0)
//					{
//						memset(BurstWriteData, 0, sizeof(BurstWriteData));
//
//						BurstWriteData[0] = nData >> 8 ;
//						BurstWriteData[1] = nData & 0xFF ;
//
//						BurstWriteLength = 2;
//						BurstWriteLengthaddr = 2;
//					}
//					else
//					{
//						BurstWriteData[BurstWriteLength] = nData >> 8 ;
//						BurstWriteData[BurstWriteLength+1] = nData & 0xFF ;
//						BurstWriteLength += 2;
//					}
//				
//					if (BurstWriteLength == 2046)
//					{						
//						errorCode = MIUI2CBurstWrite(gDeviceIndex, gMIUDevice.InitialValue.IICDeviceID, (unsigned short)nAddress, BurstWriteLengthaddr, BurstWriteData, BurstWriteLength);
//
//						if(errorCode) 
//						{
//							 errorCount++;
//							 TRACE("Burst Write Fail Error Code : 0x%x\n", errorCode);
//						 }
//						else
//						{
//							TRACE("Burst Write Ok  : %d Byte \n", BurstWriteLength);
//						}
//						BurstWriteLength = 0;
//						BurstWriteLengthaddr = 0;
//					}				
//				}
//				else
//				{
//					if (BurstWriteLength > 0 )
//					{						
//						if (BurstWriteLength == 2)
//						{
//							data =   (unsigned short) (BurstWriteData[0] << 8) + BurstWriteData[1];
//							TRACE("Sensor Addr %x, DAta %x \n", nAddress, data);
//							errorCode = MIUWriteRegister(gDeviceIndex, REG_IIC1, (unsigned short)nAddress, (unsigned short) data);
//							if(errorCode)
//							{
//								errorCount++;
//								TRACE("Error Code : 0x%x\n", errorCode);
//							}
//						}
//						else
//						{						
//							errorCode = MIUI2CBurstWrite(gDeviceIndex, gMIUDevice.InitialValue.IICDeviceID, (unsigned short)nAddress, BurstWriteLengthaddr, BurstWriteData, BurstWriteLength);
//							if(errorCode) 
//							{
//								 errorCount++;
//								 TRACE("Burst Write Fail Error Code : 0x%x\n", errorCode);
//							 }
//							else
//							{
//								TRACE("Burst Write Ok  : %d Byte \n", BurstWriteLength);
//							}
//							//Sleep(400);
//						}
//
//						if(bustSleep > 0)
//						{
//							////////////////////////// 20130711 TRACE 추가
//							TRACE("burst Sleep = %d \n",bustSleep);
//							Sleep(bustSleep); 
//							bustSleep = 0;
//						}
//
//						BurstWriteLength = 0;
//						BurstWriteLengthaddr = 0;
//						//Sleep(100);
//					}
//
//					TRACE("Sensor Addr %x, DAta %x \n", nAddress, nData);
//					errorCode = MIUWriteRegister(gDeviceIndex, REG_IIC1, (unsigned short) nAddress, (unsigned short) nData);
//					if(errorCode)
//					{
//						errorCount++;
//						TRACE("Error Code : 0x%x\n", errorCode);
//					}
//				}
//			}					
//		}
//		else if(((szLineRead.Find("I2C_MODE")!=-1)||(szLineRead.Find("I2C_Mode")!=-1))&&(szLineRead.Find("I")==0))
//		{
//			sscanf(szLineRead.GetBuffer(0),"%s%d",szTemp,&nData);
//			MIUSetI2CMode(gDeviceIndex, nData);
//			Sleep(100);
//		}
//		else if((szLineRead.Find("I2CID")!=-1)&&(szLineRead.Find("I")==0))
//		{
//			sscanf(szLineRead.GetBuffer(0),"%s%x",szTemp,&nData);
//			MIUSetI2CID(gDeviceIndex, nData);
//		}
//	}//! while
//
//#ifdef USE_MIU_OPEN_TACT
//	timeChecker.Measure_Time(iCnt_Time);
//	asTime[iCnt_Time].Format("While문 종료 - %.1f sec.", timeChecker.m_adTime[iCnt_Time] - timeChecker.m_adTime[iCnt_Time-1] );
//	iCnt_Time++;
//#endif
//
//
//
//	//! Registry 처리 중 오류 발생
//	if ( bFlag_Error == true )
//	{
//		//	return false;
//	}
//
//	// 0722
//	if (BurstWriteLength > 0 )
//	{		
//		if (BurstWriteLength == 2)
//		{
//			data =   (unsigned short) (BurstWriteData[0] << 8) + BurstWriteData[1];
//			TRACE("Sensor Addr %x, DAta %x \n", nAddress, data);
//			errorCode = MIUWriteRegister(gDeviceIndex, REG_IIC1, (unsigned short)nAddress, (unsigned short) data);
//			if(errorCode)
//			{
//				errorCount++;
//				TRACE("Error Code : 0x%x\n", errorCode);
//			}
//		}
//		else
//		{		
//			errorCode = MIUI2CBurstWrite(gDeviceIndex, gMIUDevice.InitialValue.IICDeviceID, (unsigned short)nAddress, BurstWriteLengthaddr, BurstWriteData, BurstWriteLength);
//			if(errorCode) 
//			{
//				 errorCount++;
//				 TRACE("Burst Write Fail Error Code : 0x%x\n", errorCode);
//			 }
//			else
//			{
//				TRACE("Burst Write Ok  : %d Byte \n", BurstWriteLength);
//			}
//		}
//
//		////////////////////////// 20130711 추가
//		if(bustSleep > 0)
//		{
//			TRACE("burst Sleep = %d \n",bustSleep);
//			Sleep(bustSleep); 
//			bustSleep = 0;
//			
//		}
//
//		BurstWriteLength = 0;
//		BurstWriteLengthaddr = 0;
//		//Sleep(100);
//	}
//
//#ifdef USE_MIU_OPEN_TACT
//	timeChecker.Measure_Time(iCnt_Time);
//	asTime[iCnt_Time].Format("CCD Init 완료 - %.1f sec.", timeChecker.m_adTime[iCnt_Time] - timeChecker.m_adTime[iCnt_Time-1] );
//	iCnt_Time++;
//#endif
//	 
//
//	//! Registry 처리 중 오류 발생
//	if ( bFlag_Error == true )
//	{
//		//	return false;
//	}
//
//	//! CCD Sensor의 초기화 완료
////	gMIUDevice.CurrentState = 1;
//	if(errorCount != 0)
//	{
//		CString strErrCount;
//		strErrCount.Format("I2C & Register Error Count : %d", errorCount);
//		errMsg2(Task.AutoFlag, strErrCount);	
//		return false;
//	}
//	logStr.Format("[MIU] CCD_Init 완료.");
//	MiuLogSave(logStr);
//
	return true;
}
bool CMIU::CcmInit()
{
	int iUnit=0;
	CString logStr;
	logStr.Format("[MIU] CcmInit 시작.");
	MiuLogSave(logStr);

	sLogMessage = "";
	//! 현재 정보의 유효성 검사
	if ( m_iDeviceCount <= 0 )
	{
		return false;
	}
	if ( iUnit < 0 /*|| iUnit >= m_iDeviceCount*/ )
	{
		return false;
	}
	if ( m_pSID == NULL || m_iSensorListCnt <= 0 )
	{
		return false;
	}	
	if ( m_iSensor < 0 || m_iSensor >= m_iSensorListCnt )
	{
		return false;
	}
	if ( m_pSID[m_iSensor].pInfo == NULL || m_pSID[m_iSensor].nInfoCount <= 0 )
	{
		return false;
	}
	if ( m_iSensorType < 0 || m_iSensorType >= m_pSID[m_iSensor].nInfoCount )
	{
		return false;
	}

	if ( gMIUDevice.bMIUOpen != 1 )
	{
		sLogMessage.Format(_T("LPMC 연결을 확인하세요."));
		return false;
	}

	bool bRet = false;
	bool bFlag_Grab_Stop = false;
	if ( gMIUDevice.CurrentState > 1 )
	{
		bFlag_Grab_Stop = true;

		//! 영상 취득 중지
		//! [주의 사항] 영상 취득만 중지해야한다. CCD의 전원까지 끄면 안된다.
		bRet = Stop( false);
	}

/////////////////////////////////////////////////
	//! Frame Grabber를 초기화 한다.
	bRet = MIU_Init();
	if ( bRet == false )
	{
		return false;
	}	
	
	Sleep(10);	
// 	//! CCD Camera Sensor를 초기화 한다.
	//====================================================================================================================CCD_Init
	bRet = CCD_Init();
	if ( bRet == false )
	{
		return false;
	}
////////////////////////////////////////////////
	//! 영상 취득을 새로 시작한다. 
	if ( bFlag_Grab_Stop == true )
	{
		bRet = Start();
	}
	
	logStr.Format("[MIU] CcmInit 완료.");
	MiuLogSave(logStr);

	return true;
}

//! 영상 취득 시작
//! 이미 영상 취득이 시작된 상태라면, 동영상 Display 시작
bool CMIU::Start()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	CString logStr;
	logStr.Format("MIU Start 시작.");
	theApp.MainDlg->putListLog(logStr);
	MiuLogSave(logStr);

#ifdef USE_MIU_OPEN_TACT
	bMiuLiveFrameFlag = false;
#endif
	if ( m_iDeviceCount <= 0 )
	{
		return false;
	}
	if(!m_pBoard->IsConnected())
	{
		logStr.Format("[CCD] Grabber Board 해제 상태");
		pFrame->putListLog(logStr);
		if(!Open())					// 85 msec.
		{
			pFrame->putListLog("	MIU Open 실패.");
			return false;
		}
		Sleep(500);
	}
	if ( gMIUDevice.CurrentState == 0 )
	{
		sLogMessage = _T("카메라 모듈 초기화를 수행 합니다.");

#ifdef USE_MIU_OPEN_TACT
		timeChecker.Measure_Time(iCnt_Time);
		asTime[iCnt_Time].Format("접속 CCM_Init(iUnit) - %.1f sec.", timeChecker.m_adTime[iCnt_Time] - timeChecker.m_adTime[iCnt_Time-1] );
		iCnt_Time++;
#endif

	}

#ifdef USE_MIU_OPEN_TACT
	timeChecker.Measure_Time(iCnt_Time);
	asTime[iCnt_Time].Format("접속 Init_Display_Count() - %.1f sec.", timeChecker.m_adTime[iCnt_Time] - timeChecker.m_adTime[iCnt_Time-1] );
	iCnt_Time++;
#endif
	if ( gMIUDevice.CurrentState < 2 )
	{ 		
		logStr.Format("[MIU] Start Buffer Alloc. [State : %d] ", gMIUDevice.CurrentState);
		MiuLogSave(logStr);
		
#ifdef USE_MIU_OPEN_TACT
		timeChecker.Measure_Time(iCnt_Time);
		asTime[iCnt_Time].Format("접속 cvBufferAlloc(iUnit) - %.1f sec.", timeChecker.m_adTime[iCnt_Time] - timeChecker.m_adTime[iCnt_Time-1] );
		iCnt_Time++;
#endif

#ifdef USE_MIU_OPEN_TACT
		timeChecker.Measure_Time(iCnt_Time);
		asTime[iCnt_Time].Format("접속 Start_Index_Grab(iUnit) - %.1f sec.", timeChecker.m_adTime[iCnt_Time] - timeChecker.m_adTime[iCnt_Time-1] );
		iCnt_Time++;
#endif

		Start_Index_Grab();

		//int iErrorCode = MIU_OK;
		
		//! Max Size는 사용 안함. 
#ifdef USE_MIU_OPEN_TACT
		timeChecker.Measure_Time(iCnt_Time);
		asTime[iCnt_Time].Format("접속 MIUInitializeImageValue(iUnit - %.1f sec.", timeChecker.m_adTime[iCnt_Time] - timeChecker.m_adTime[iCnt_Time-1] );
		iCnt_Time++;
#endif

#ifdef USE_MIU_OPEN_TACT
		timeChecker.Measure_Time(iCnt_Time);
		asTime[iCnt_Time].Format("접속 MIUStart(iUnit) - %.1f sec.", timeChecker.m_adTime[iCnt_Time] - timeChecker.m_adTime[iCnt_Time-1] );
		iCnt_Time++;
#endif
		//! 영상 취득 시작
		//iErrorCode = MIUStart(gDeviceIndex);
		if(m_pBoard->GrabStart()==BOARD_SUCCESS)
		{
			logStr.Format("[MIU] Start 완료.");
			MiuLogSave(logStr);
		}else
		{
			return false;
		}

	}

#ifdef USE_MIU_OPEN_TACT
	bMiuLiveFrameFlag = true;
	timeChecker.Measure_Time(iCnt_Time);
	asTime[iCnt_Time].Format("MIUStart 완료 - %.1f sec.", timeChecker.m_adTime[iCnt_Time] - timeChecker.m_adTime[iCnt_Time-1] );
	iCnt_Time++;
#endif
	return true;
}
//! [주의 사항] 
//!		bFlag_PowerOff가 true이면 CCD Sensor의 전원을 끈다. 
//!		이것은 맨 마지막에만 사용되도록 주의 해야 한다. 
//!		왜냐하면, 전원을 끄면, 초기화를 다시 해야만 영상을 다시 볼 수 있다.
//!		(초기화하려면, CMIU::CcmInit 함수 다시 호출해야 함)
bool CMIU::Stop(bool fi_bFlag_PowerOff)
{

	if (m_pBoard->IsGrabStarted())//if ( gMIUDevice.CurrentState >= 2 )
	{
		m_pBoard->GrabStop();
	}
	
	//! Flag값 초기화
	gMIUDevice.bMIUOpen = 0;
	gMIUDevice.CurrentState = 0;

	//! 영상 취득 Thread의 작동을 멈추게 한다. 
	Init_Index_Grab();

	if(theApp.MainDlg->m_bMiuRun)
	{
		theApp.MainDlg->m_bMiuRun=false;
	}
	theApp.MainDlg->m_labelUsbLive.SetBkColor(M_COLOR_RED);
	theApp.MainDlg->m_labelUsbLive.Invalidate();
	return true;
}

//! Display Frame Rate 측정용 함수
//! [주의 사항] 반드시, Display 직후에 호출한다. (Display를 하지 않을 경우에는 영상 취득 후의 최종 단계에서 호출한다.)
void CMIU::Add_Display_Count()
{
	(m_strDisplayDiag.iCnt_Display)++;
	
	double dElapsed = m_aMeasureTimeForDisplayFrameRate.Measure_Time(0);

	double dDuration = fabs(dElapsed - m_strDisplayDiag.dGrabStart);

	if ( dDuration > 0.001 )
	{
		m_fRate_Display = ((float)(m_strDisplayDiag.iCnt_Display)) / (float)dDuration;
	}
	else
	{
		m_fRate_Display = 0.f;
	}

	if ( m_strDisplayDiag.iCnt_Display > 50 )
	{
		m_strDisplayDiag.iCnt_Display = 0;
		m_strDisplayDiag.dGrabStart = m_aMeasureTimeForDisplayFrameRate.Measure_Time(0);
	}
}

//! Display Frame Rate 초기화
void CMIU::Init_Display_Count()
{
	m_aMeasureTimeForDisplayFrameRate.Init_Time();
	m_aMeasureTimeForDisplayFrameRate.Start_Time();	
	m_strDisplayDiag.dGrabStart = m_aMeasureTimeForDisplayFrameRate.Measure_Time(0);

	m_strDisplayDiag.iCnt_Display = 0;

	m_fRate_Display = 0.f;

	fGrapStatTickCount=GetTickCount();
}


int CMIU::OsTest_PinMapping(unsigned char ucSensorMode, float* TestResult)
{
	float tempData[OS_PIN_COUNT];

	memcpy(tempData,  TestResult, sizeof(tempData));
	memset(TestResult,         0, sizeof(tempData));
	
	if ( ucSensorMode == 1) // Parallel
	{
		TestResult[0] = tempData[48];
		TestResult[1] = tempData[49];
		TestResult[2] = tempData[50];
		TestResult[3] = tempData[51];
		TestResult[4] = tempData[53];
		TestResult[5] = tempData[54];
		TestResult[6] = tempData[4];
		TestResult[7] = tempData[16];
		TestResult[8] = tempData[1];
		TestResult[9] = tempData[15];
		TestResult[10] = tempData[53];
		TestResult[11] = tempData[54];
		TestResult[12] = tempData[21];
		TestResult[13] = tempData[36];
		TestResult[14] = tempData[27];
		TestResult[15] = tempData[28];
		TestResult[16] = tempData[20];
		TestResult[17] = tempData[43];
		TestResult[18] = tempData[31];
		TestResult[19] = tempData[45];
		TestResult[20] = tempData[33];
		TestResult[21] = tempData[34];
		TestResult[22] = tempData[30];
		TestResult[23] = tempData[32];
		TestResult[24] = tempData[37];
		TestResult[25] = tempData[38];
		TestResult[26] = tempData[39];
		TestResult[27] = tempData[40];
		TestResult[28] = tempData[22];
		TestResult[29] = tempData[42];
		TestResult[30] = tempData[53];
		TestResult[31] = tempData[54];
		TestResult[32] = tempData[0];
		TestResult[33] = tempData[24];
		TestResult[34] = tempData[5];
		TestResult[35] = tempData[8];
		TestResult[36] = tempData[44];
		TestResult[37] = tempData[6];
		TestResult[38] = tempData[52];

		TestResult[39] = 0; // Pin 40 Not Test
		// SPI
		TestResult[40] = tempData[7];
		TestResult[41] = tempData[19];
		TestResult[42] = tempData[9];
		TestResult[43] = tempData[18];
	}
	else //Mipi
	{
		TestResult[0] = tempData[48];
		TestResult[1] = tempData[49];
		TestResult[2] = tempData[50];
		TestResult[3] = tempData[51];
		TestResult[4] = tempData[53];
		TestResult[5] = tempData[54];
		TestResult[6] = tempData[4];
		TestResult[7] = tempData[13];
		TestResult[8] = tempData[1];
		TestResult[9] = tempData[41];
		TestResult[10] = tempData[53];
		TestResult[11] = tempData[54];
		TestResult[12] = tempData[16];
		TestResult[13] = tempData[25];
		TestResult[14] = tempData[15];
		TestResult[15] = tempData[26];
		TestResult[16] = tempData[53];
		TestResult[17] = tempData[54];
		TestResult[18] = tempData[2];
		TestResult[19] = tempData[35];
		TestResult[20] = tempData[3];
		TestResult[21] = tempData[10];
		TestResult[22] = tempData[53];
		TestResult[23] = tempData[54];
		TestResult[24] = tempData[17];
		TestResult[25] = tempData[29];
		TestResult[26] = tempData[14];
		TestResult[27] = tempData[23];
		TestResult[28] = tempData[53];
		TestResult[29] = tempData[54];
		TestResult[30] = tempData[53];
		TestResult[31] = tempData[12];
		TestResult[32] = tempData[53];
		TestResult[33] = tempData[11];
		TestResult[34] = tempData[0];
		TestResult[35] = tempData[54];
		TestResult[36] = tempData[53];
		TestResult[37] = tempData[54];
		TestResult[38] = tempData[52];

		TestResult[39] = 0; // Pin 40 Not Test

		// SPI
		TestResult[40] = tempData[7];
		TestResult[41] = tempData[19];
		TestResult[42] = tempData[9];
		TestResult[43] = tempData[18];
	}

	return 1;//MIU_OK;
}

//! Color 변환에 사용
//! *   Shift10BitMode : Test 용 -> 10 bit 를 8bit로 shift  
//!	*
//!	*   @param      pImage, [in] Image Pointer
//!	*   @param      nWidth, [in] Image Width
//!	*	@param		nHeight, [in] Image Height  
void CMIU::Shift10BitMode(unsigned char* pImage, unsigned char* pDest, unsigned int nWidth, unsigned int nHeight)
{
	unsigned int i,j,k;
	unsigned int nByteWidth;
	nByteWidth = nWidth * 5 / 4 ;

	unsigned int *piDest;
	piDest = (unsigned int *)pDest;

	nWidth >>= 2;

	for(i=0; i<nHeight; i++)
	{
		for(j=0, k=0; j<nWidth; j++, k+=5)
		{
			piDest[j] = (pImage[k+3]<<24) +  (pImage[k+2]<<16) +  (pImage[k+1]<<8) +  (pImage[k]);
		}

		piDest += nWidth;
		pImage += nByteWidth;
	}
}

//! Color 변환에 사용
//! *   Shift12BitMode : Test 용 -> 12 bit 를 8bit로 shift  
//!	*
//!	*   @param      pImage, [in] Image Pointer
//!	*   @param      nWidth, [in] Image Width
//!	*	@param		nHeight, [in] Image Height 
void CMIU::Shift12BitMode(unsigned char* pImage, unsigned char* pDest, unsigned int nWidth, unsigned int nHeight)
{
	unsigned int	i,j,k;
	unsigned int	nByteWidth;
	unsigned short *psDest;

	nByteWidth = nWidth * 3 / 2 ;
	psDest = (unsigned short *)pDest;
	nWidth >>= 1;
	for(i=0; i<nHeight; i++)
	{
		for(j=0, k = 0; j<nWidth; j++,k+=3)
		{
			psDest[j] =  (pImage[k+1]<<8) +  (pImage[k]);			
		}
		psDest += nWidth;
		pImage += nByteWidth;
	}
}

//! Color 변환에 사용
void CMIU::CopyBuffer(unsigned char* pImage, unsigned char* pDest, unsigned int nWidth, unsigned int nHeight)
{
	unsigned int	i,j;

	for(i=0; i<nHeight; i++)
	{
		for(j=0; j<nWidth; j++)
		{
			pDest[j] =  pImage[j];			
		}
		pDest += nWidth;
		pImage += nWidth;
	}
}

//! CCD Sensor별 설정
//! IMX135-0APH5-L CMOS, Sony, 2013/3/13
//! 색상별 Gain 설정
bool CMIU::SetRegister_WhiteBalance_Red_IMX135(CString fi_sGain)
{
	if ( m_iDeviceCount <= 0 )
	{
		return false;
	}
	if ( m_iIndexDevice < 0 )
	{
		return false;
	}
	if ( gMIUDevice.bMIUOpen != 1 )
	{
		sLogMessage.Format(_T("LPMC Check Connect"));
		return false;
	}
	if ( fi_sGain.GetLength() <= 0 )
	{
		return false;
	}

	//! 입력값을 2개의 16진수 숫자로 변환한다. 
	int iInteger = 0;
	double dDecimalPoint = 0;

	GetInteger_From_Double(fi_sGain, iInteger, dDecimalPoint);

	int iDecimalPoint = (int)(dDecimalPoint * 256.);

	long lGain_MSB = Convert_Decimal_To_Hex(iInteger);
	long lGain_LSB = Convert_Decimal_To_Hex(iDecimalPoint);

	int iErrorCode = 0;

	CString sAddress1 = _T("0x0210"), sAddress2 = _T("0x0211");

	long lAddress1 = HexString_to_Num(sAddress1);
	long lAddress2 = HexString_to_Num(sAddress2);

	//iErrorCode = MIUWriteRegister(m_iIndexDevice, REG_IIC1, (unsigned short)lAddress1, (unsigned short)lGain_MSB);
	//if ( iErrorCode != MIU_OK )
	//{
	//	return false;
	//}
	//iErrorCode = MIUWriteRegister(m_iIndexDevice, REG_IIC1, (unsigned short)lAddress2, (unsigned short)lGain_LSB);
	//if ( iErrorCode != MIU_OK )
	//{
	//	return false;
	//}
	
	return true;
}

bool CMIU::SetRegister_WhiteBalance_Green_IMX135(CString fi_sGain)
{
	if ( m_iDeviceCount <= 0 )
	{
		return false;
	}
	if ( m_iIndexDevice < 0 )
	{
		return false;
	}
	if ( gMIUDevice.bMIUOpen != 1 )
	{
		sLogMessage.Format(_T("LPMC Check Connect"));
		return false;
	}
	if ( fi_sGain.GetLength() <= 0 )
	{
		return false;
	}

	//! 입력값을 2개의 16진수 숫자로 변환한다. 
	int iInteger = 0;
	double dDecimalPoint = 0;

	GetInteger_From_Double(fi_sGain, iInteger, dDecimalPoint);

	int iDecimalPoint = (int)(dDecimalPoint * 256.);

	long lGain_MSB = Convert_Decimal_To_Hex(iInteger);
	long lGain_LSB = Convert_Decimal_To_Hex(iDecimalPoint);

	int iErrorCode = 0;

	//! Gr
	CString sAddress1 = _T("0x020E"), sAddress2 = _T("0x020F");

	long lAddress1 = HexString_to_Num(sAddress1);
	long lAddress2 = HexString_to_Num(sAddress2);

	/*iErrorCode = MIUWriteRegister(m_iIndexDevice, REG_IIC1, (unsigned short)lAddress1, (unsigned short)lGain_MSB);
	if ( iErrorCode != MIU_OK )
	{
		return false;
	}
	iErrorCode = MIUWriteRegister(m_iIndexDevice, REG_IIC1, (unsigned short)lAddress2, (unsigned short)lGain_LSB);
	if ( iErrorCode != MIU_OK )
	{
		return false;
	}*/

	//! Gb
	sAddress1 = _T("0x0214"), sAddress2 = _T("0x0215");

	lAddress1 = HexString_to_Num(sAddress1);
	lAddress2 = HexString_to_Num(sAddress2);

	/*iErrorCode = MIUWriteRegister(m_iIndexDevice, REG_IIC1, (unsigned short)lAddress1, (unsigned short)lGain_MSB);
	if ( iErrorCode != MIU_OK )
	{
		return false;
	}
	iErrorCode = MIUWriteRegister(m_iIndexDevice, REG_IIC1, (unsigned short)lAddress2, (unsigned short)lGain_LSB);
	if ( iErrorCode != MIU_OK )
	{
		return false;
	}*/

	return true;
}

bool CMIU::SetRegister_WhiteBalance_Blue_IMX135(CString fi_sGain)
{
	if ( m_iDeviceCount <= 0 )
	{
		return false;
	}
	if ( m_iIndexDevice < 0 )
	{
		return false;
	}
	if ( gMIUDevice.bMIUOpen != 1 )
	{
		sLogMessage.Format(_T("LPMC Check Connect"));
		return false;
	}
	if ( fi_sGain.GetLength() <= 0 )
	{
		return false;
	}

	//! 입력값을 2개의 16진수 숫자로 변환한다. 
	int iInteger = 0;
	double dDecimalPoint = 0;

	GetInteger_From_Double(fi_sGain, iInteger, dDecimalPoint);

	int iDecimalPoint = (int)(dDecimalPoint * 256.);

	long lGain_MSB = Convert_Decimal_To_Hex(iInteger);
	long lGain_LSB = Convert_Decimal_To_Hex(iDecimalPoint);

	int iErrorCode = 0;

	CString sAddress1 = _T("0x0212"), sAddress2 = _T("0x0213");

	long lAddress1 = HexString_to_Num(sAddress1);
	long lAddress2 = HexString_to_Num(sAddress2);

	/*iErrorCode = MIUWriteRegister(m_iIndexDevice, REG_IIC1, (unsigned short)lAddress1, (unsigned short)lGain_MSB);
	if ( iErrorCode != MIU_OK )
	{
		return false;
	}
	iErrorCode = MIUWriteRegister(m_iIndexDevice, REG_IIC1, (unsigned short)lAddress2, (unsigned short)lGain_LSB);
	if ( iErrorCode != MIU_OK )
	{
		return false;
	}*/

	return true;
}

bool CMIU::SetRegister_WhiteBalance_Red_IMX135(double fi_dGain)
{
	CString sInput = _T("");
	sInput.Format(_T("%g"), fi_dGain);
	bool bRet = SetRegister_WhiteBalance_Red_IMX135(sInput);
	return bRet;
}

bool CMIU::SetRegister_WhiteBalance_Green_IMX135(double fi_dGain)
{
	CString sInput = _T("");
	sInput.Format(_T("%g"), fi_dGain);
	bool bRet = SetRegister_WhiteBalance_Green_IMX135(sInput);
	return bRet;
}

bool CMIU::SetRegister_WhiteBalance_Blue_IMX135(double fi_dGain)
{
	CString sInput = _T("");
	sInput.Format(_T("%g"), fi_dGain);
	bool bRet = SetRegister_WhiteBalance_Blue_IMX135(sInput);
	return bRet;
}

//! Exposure Time 설정 (Added by LHW, 2013/3/14)
//! CCD Sensor의 현재 설정 정보를 가져온다.
bool CMIU::GetCurrentInfo_Exposure_From_CCD_IMX135()
{
	return true;
	//if ( m_iDeviceCount <= 0 )
	//{
	//	return false;
	//}
	//if ( m_iIndexDevice < 0 )
	//{
	//	return false;
	//}
	//if ( gMIUDevice.bMIUOpen != 1 )
	//{
	//	sLogMessage.Format(_T("LPMC Check Connect"));
	//	return false;
	//}

	//bool bRet = true;

	//int iErrorCode = 0;
	//CString sAddress1 = _T(""), sAddress2 = _T("");
	//long lAddress1 = 0, lAddress2 = 0;
	//int iData1 = 0, iData2 = 0, iData = 0;

	////unsigned short iPrePLLClk_OP_Div;	//! Register Address : 0x0305
	////unsigned short iPLL_OP_MPY;		//! Register Address : 0x030C, 0x030D
	////unsigned short iVTSYCK_Div;		//! Register Address : 0x0303
	////unsigned short iVTPXCK_Div;		//! Register Address : 0x0301

	////unsigned short iFrame_Length;		//! Register Address : 0x0340, 0x0341
	////unsigned short iLine_Length;		//! Register Address : 0x0342, 0x0343

	////unsigned short iIntegrationTime_Coarse;	//! Register Address : 0x0202, 0x0203
	////unsigned short iIntegrationTime_Fine;		//! Register Address : 0x0200, 0x0201 (Read Only)

	//sAddress1 = _T("0x0305");	
	//lAddress1 = HexString_to_Num(sAddress1);	
	//iErrorCode = MIUReadRegister(m_iIndexDevice, REG_IIC1, (unsigned short)lAddress1, (unsigned short*)&iData1);
	//if ( iData1 <= 0 )
	//{
	//	bRet = false;
	//	iData1 = 1;
	//}
	//gMIUDevice.IMX135.iPrePLLClk_OP_Div = (unsigned short)iData1;
	//
	//sAddress1 = _T("0x030C");
	//sAddress2 = _T("0x030D");
	//lAddress1 = HexString_to_Num(sAddress1);
	//lAddress2 = HexString_to_Num(sAddress2);
	//iErrorCode = MIUReadRegister(m_iIndexDevice, REG_IIC1, (unsigned short)lAddress1, (unsigned short*)&iData1);
	//iErrorCode = MIUReadRegister(m_iIndexDevice, REG_IIC1, (unsigned short)lAddress2, (unsigned short*)&iData2);
	//Merge_Integer_From_Hex_8bit(iData1, iData2, iData);
	//if ( iData <= 0 )
	//{
	//	bRet = false;
	//	iData = 1;
	//}
	//gMIUDevice.IMX135.iPLL_OP_MPY = (unsigned short)iData;

	//sAddress1 = _T("0x0303");	
	//lAddress1 = HexString_to_Num(sAddress1);	
	//iErrorCode = MIUReadRegister(m_iIndexDevice, REG_IIC1, (unsigned short)lAddress1, (unsigned short*)&iData1);
	//if ( iData1 <= 0 )
	//{
	//	bRet = false;
	//	iData1 = 1;
	//}
	//gMIUDevice.IMX135.iVTSYCK_Div = (unsigned short)iData1;

	//sAddress1 = _T("0x0301");	
	//lAddress1 = HexString_to_Num(sAddress1);	
	//iErrorCode = MIUReadRegister(m_iIndexDevice, REG_IIC1, (unsigned short)lAddress1, (unsigned short*)&iData1);
	//if ( iData1 <= 0 )
	//{
	//	bRet = false;
	//	iData1 = 1;
	//}
	//gMIUDevice.IMX135.iVTPXCK_Div = (unsigned short)iData1;

	//sAddress1 = _T("0x0340");
	//sAddress2 = _T("0x0341");
	//lAddress1 = HexString_to_Num(sAddress1);
	//lAddress2 = HexString_to_Num(sAddress2);
	//iErrorCode = MIUReadRegister(m_iIndexDevice, REG_IIC1, (unsigned short)lAddress1, (unsigned short*)&iData1);
	//iErrorCode = MIUReadRegister(m_iIndexDevice, REG_IIC1, (unsigned short)lAddress2, (unsigned short*)&iData2);
	//Merge_Integer_From_Hex_8bit(iData1, iData2, iData);
	//if ( iData <= 0 )
	//{
	//	bRet = false;
	//	iData = 1;
	//}
	//gMIUDevice.IMX135.iFrame_Length = (unsigned short)iData;

	//sAddress1 = _T("0x0342");
	//sAddress2 = _T("0x0343");
	//lAddress1 = HexString_to_Num(sAddress1);
	//lAddress2 = HexString_to_Num(sAddress2);
	//iErrorCode = MIUReadRegister(m_iIndexDevice, REG_IIC1, (unsigned short)lAddress1, (unsigned short*)&iData1);
	//iErrorCode = MIUReadRegister(m_iIndexDevice, REG_IIC1, (unsigned short)lAddress2, (unsigned short*)&iData2);
	//Merge_Integer_From_Hex_8bit(iData1, iData2, iData);
	//if ( iData <= 0 )
	//{
	//	bRet = false;
	//	iData = 1;
	//}
	//gMIUDevice.IMX135.iLine_Length = (unsigned short)iData;

	//sAddress1 = _T("0x0202");
	//sAddress2 = _T("0x0203");
	//lAddress1 = HexString_to_Num(sAddress1);
	//lAddress2 = HexString_to_Num(sAddress2);
	//iErrorCode = MIUReadRegister(m_iIndexDevice, REG_IIC1, (unsigned short)lAddress1, (unsigned short*)&iData1);
	//iErrorCode = MIUReadRegister(m_iIndexDevice, REG_IIC1, (unsigned short)lAddress2, (unsigned short*)&iData2);
	//Merge_Integer_From_Hex_8bit(iData1, iData2, iData);
	//if ( iData <= 0 )
	//{
	//	bRet = false;
	//	iData = 1;
	//}
	//gMIUDevice.IMX135.iIntegrationTime_Coarse = (unsigned short)iData;

	//sAddress1 = _T("0x0200");
	//sAddress2 = _T("0x0201");
	//lAddress1 = HexString_to_Num(sAddress1);
	//lAddress2 = HexString_to_Num(sAddress2);
	//iErrorCode = MIUReadRegister(m_iIndexDevice, REG_IIC1, (unsigned short)lAddress1, (unsigned short*)&iData1);
	//iErrorCode = MIUReadRegister(m_iIndexDevice, REG_IIC1, (unsigned short)lAddress2, (unsigned short*)&iData2);
	//Merge_Integer_From_Hex_8bit(iData1, iData2, iData);
	//if ( iData <= 0 )
	//{
	//	bRet = false;
	//	iData = 1;
	//}
	//gMIUDevice.IMX135.iIntegrationTime_Fine = (unsigned short)iData;

	//if ( bRet == false )
	//{
	//	return false;
	//}

	////! CCD Sensor의 매뉴얼을 참고하여 아래의 계산식을 알아내다.
	////! IMX135-0APH5-L Data Sheet 
	////! Clock System Diagram (Page 25 ~ 28)
	////! Frame Rate Calculation Formula (Page 42)
	////! Electronic shutter and integration time settings (Page 43)

	//double dValue_VTPXCK = 0;
	//dValue_VTPXCK  = gMIUDevice.InitialValue.MCLK * 1000. * 1000.;	//! CCD Sensor의 Main Clock값을 가져온다.
	//dValue_VTPXCK /= (double)(gMIUDevice.IMX135.iPrePLLClk_OP_Div);
	//dValue_VTPXCK *= (double)(gMIUDevice.IMX135.iPLL_OP_MPY);
	//dValue_VTPXCK /= ((double)(gMIUDevice.IMX135.iVTSYCK_Div * gMIUDevice.IMX135.iVTPXCK_Div));

	//double dTime_Line = 0.;
	//dTime_Line = ((double)(gMIUDevice.IMX135.iLine_Length)) / (2. * dValue_VTPXCK);

	//double dValue_Temp = 0.;
	//dValue_Temp = ((double)(gMIUDevice.IMX135.iIntegrationTime_Fine)) * 2. / ((double)(gMIUDevice.IMX135.iLine_Length));

	//double dTime_Exposure_Min = 0., dTime_Exposure_Max = 0., dTime_Exposure_Current = 0.;

	//dTime_Exposure_Min     = dTime_Line * (1. + dValue_Temp);
	//dTime_Exposure_Max     = dTime_Line * (((double)(gMIUDevice.IMX135.iFrame_Length - 4)) + dValue_Temp);
	//dTime_Exposure_Current = dTime_Line * (((double)(gMIUDevice.IMX135.iIntegrationTime_Coarse)) + dValue_Temp);

	////! sec ---> usec 단위 변환
	//gMIUDevice.IMX135.iExposureTime_Min     = (int)(dTime_Exposure_Min * 1000. * 1000.);
	//gMIUDevice.IMX135.iExposureTime_Max     = (int)(dTime_Exposure_Max * 1000. * 1000.);
	//gMIUDevice.IMX135.iExposureTime_Current = (int)(dTime_Exposure_Current * 1000. * 1000.);

	////! 데이터 사용 가능
	//gMIUDevice.IMX135.bFlag_Valid = 1;

	//return bRet;
}
void CMIU::SaveSfrImage(unsigned char* ucImage, int pitch, int sizeX, int sizeY, int index, CRect rcRoi)
{
	TCHAR szPos[SIZE_OF_1K];
	int mSizeX = 0;
	int mSizeY = 0;

	mSizeX = sizeX;
	mSizeY = sizeY;

	MbufAlloc2d(vision.MilSystem, mSizeX, mSizeY, 8 + M_UNSIGNED, M_IMAGE + M_PROC, &vision.MilSfrTargetImage);

	BOOL IsFind;
	CFileFind clFinder;
	TCHAR szPath[SIZE_OF_1K];
	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\%s\\SfrCrop"), BASE_LOG_DIR, model.mCurModelName);
	if (clFinder.FindFile(szPath) == FALSE)
	{
		CreateDirectory(szPath, NULL);
	}

	_stprintf_s(szPos, SIZE_OF_1K, _T("%s\\%s\\SfrCrop\\Crop_%d.bmp"), BASE_LOG_DIR,model.mCurModelName, index);
	MbufChild2d(vision.MilProcImageChild[3], rcRoi.left, rcRoi.top, mSizeX, mSizeY, &vision.MilSfrTargetImage);
	MbufSave(szPos, vision.MilSfrTargetImage);


	//
	//
	//MbufFree(MilSfrTargetImage);

}
//! Exposure Time 설정 (Added by LHW, 2013/3/14)
//! fi_iExposureTime : Exposure 시간, 단위 usec
bool CMIU::Set_ExposureTime_To_CCD_IMX135(int fi_iExposureTime)
{
	//if ( m_iDeviceCount <= 0 )
	//{
	//	return false;
	//}
	//if ( m_iIndexDevice < 0 )
	//{
	//	return false;
	//}
	//if ( gMIUDevice.bMIUOpen != 1 )
	//{
	//	sLogMessage.Format(_T("LPMC Check Connect"));
	//	return false;
	//}

	//if ( gMIUDevice.IMX135.bFlag_Valid != 1 )
	//{
	//	sLogMessage.Format(_T("IMX135 Sensor Data Not Used."));
	//	return false;
	//}

	//if ( fi_iExposureTime < gMIUDevice.IMX135.iExposureTime_Min || 
	//	 fi_iExposureTime > gMIUDevice.IMX135.iExposureTime_Max )
	//{
	//	return false;
	//}

	//if ( gMIUDevice.IMX135.iPrePLLClk_OP_Div <= 0 || 
	//	 gMIUDevice.IMX135.iVTSYCK_Div <= 0 || 
	//	 gMIUDevice.IMX135.iVTPXCK_Div <= 0 || 
	//	 gMIUDevice.IMX135.iLine_Length <= 0 )
	//{
	//	return false;
	//}
	//
	////! CCD Sensor의 매뉴얼을 참고하여 아래의 계산식을 알아내다.
	////! IMX135-0APH5-L Data Sheet 
	////! Clock System Diagram (Page 25 ~ 28)
	////! Frame Rate Calculation Formula (Page 42)
	////! Electronic shutter and integration time settings (Page 43)

	//double dValue_VTPXCK = 0;
	//dValue_VTPXCK  = gMIUDevice.InitialValue.MCLK * 1000. * 1000.;	//! CCD Sensor의 Main Clock값을 가져온다.
	//dValue_VTPXCK /= (double)(gMIUDevice.IMX135.iPrePLLClk_OP_Div);
	//dValue_VTPXCK *= (double)(gMIUDevice.IMX135.iPLL_OP_MPY);
	//dValue_VTPXCK /= ((double)(gMIUDevice.IMX135.iVTSYCK_Div * gMIUDevice.IMX135.iVTPXCK_Div));

	//double dTime_Line = 0.;
	//dTime_Line = ((double)(gMIUDevice.IMX135.iLine_Length)) / (2. * dValue_VTPXCK);

	//double dValue_Temp = 0.;
	//dValue_Temp = ((double)(gMIUDevice.IMX135.iIntegrationTime_Fine)) * 2. / ((double)(gMIUDevice.IMX135.iLine_Length));

	//if ( fi_iExposureTime <= ((int)dTime_Line) )
	//{
	//	return false;
	//}

	//double dTime_Coarse = 0.;
	//double dTime_Exposure = ((double)fi_iExposureTime) / (1000. * 1000);	//! 단위 변환, usec ---> sec
	//dTime_Coarse = dTime_Exposure / dTime_Line;
	//dTime_Coarse -= dValue_Temp;

	//int iTime_Coarse = (int)(dTime_Coarse + 0.5);

	//if ( iTime_Coarse < 1 )
	//{
	//	iTime_Coarse = 1;
	//}
	//if ( iTime_Coarse > (gMIUDevice.IMX135.iFrame_Length - 4) )
	//{
	//	iTime_Coarse = gMIUDevice.IMX135.iFrame_Length - 4;
	//}

	//int iErrorCode = 0;
	//CString sAddress1 = _T(""), sAddress2 = _T("");
	//long lAddress1 = 0, lAddress2 = 0;
	//int iData1 = 0, iData2 = 0;

	//Separate_Hex_From_Integer_8bit(iTime_Coarse, iData1, iData2);

	////! COARSE_INTEG_TIME 설정

	//sAddress1 = _T("0x0202");
	//sAddress2 = _T("0x0203");

	//lAddress1 = HexString_to_Num(sAddress1);
	//lAddress2 = HexString_to_Num(sAddress2);

	//iErrorCode = MIUWriteRegister(m_iIndexDevice, REG_IIC1, (unsigned short)lAddress1, (unsigned short)iData1);
	//if ( iErrorCode != MIU_OK )
	//{
	//	return false;
	//}
	//iErrorCode = MIUWriteRegister(m_iIndexDevice, REG_IIC1, (unsigned short)lAddress2, (unsigned short)iData2);
	//if ( iErrorCode != MIU_OK )
	//{
	//	return false;
	//}

	//gMIUDevice.IMX135.iExposureTime_Current = fi_iExposureTime;

	return true;
}

//! OIS (VCM) 사용 준비
//! [주의 사항] 반드시, Frame Grabber가 Open, Initialize 된 뒤에 사용해야 한다. (클래스 내의 Open, MIU_Init 함수 호출 후 사용 가능)
bool CMIU::ReadyVCM()
{
	if ( m_iDeviceCount <= 0 )
	{
		return false;
	}
	if ( m_iIndexDevice < 0 )
	{
		return false;
	}
	if ( gMIUDevice.bMIUOpen != 1 )
	{
		sLogMessage.Format(_T("LPMC 연결을 확인하세요."));
		return false;
	}
	if ( gMIUDevice.bMIUInit != 1 )
	{
		sLogMessage.Format(_T("LPMC Frame Grabber를 초기화 하십시오."));
		return false;
	}

	//MIUSetI2CIDOIS(m_iIndexDevice, 0x0C);	//! IIC Slave Address 상위 7bit
	//										//! 0x0C의 값은 Slave Device Address 값
	//										//! Write = 0x18 , Read =0x19 이고 이중 상위 7bit의 값으로 설정하도록 되어 있음
	//										//! VCM Driver 매뉴얼 (Ver. 1.93) 8 page 참조

	//MIUSetI2CModeOIS(m_iIndexDevice, 0);	//! Address 와 Data Length 설정
	//										//! 0 : 8bit address, 8bit data, 1 : 8bit address, 16bit data
	//										//! 2 : 16bit address, 8bit data, 3 : 16bit address, 16bit data

	gMIUDevice.bReadyVCM = 1;

	return true;
}

//! OIS, VCM Driver에 직접 데이터를 입력한다. 
bool CMIU::SetValue_VCM_Direct(BYTE fi_Byte1, BYTE fi_Byte2)
{
	if ( m_iDeviceCount <= 0 )
	{
		return false;
	}
	if ( m_iIndexDevice < 0 )
	{
		return false;
	}
	if ( gMIUDevice.bMIUOpen != 1 )
	{
		sLogMessage.Format(_T("LPMC 연결을 확인하세요."));
		return false;
	}
	if ( gMIUDevice.bMIUInit != 1 )
	{
		sLogMessage.Format(_T("LPMC Frame Grabber를 초기화 하십시오."));
		return false;
	}
	if ( gMIUDevice.bReadyVCM != 1 )
	{
		sLogMessage.Format(_T("LPMC Frame Grabber에서 VCM 부분을 초기화 하십시오."));
		return false;
	}

	//! MIUWriteOIS(char iDeviceIndex, unsigned short nAddress, unsigned short nData);
	//! MIUWriteOIS 함수에서 nAddress에 BYTE1, nData에 BYTE2 설정 (VCM Driver 매뉴얼 Ver 1.93 page 7 참고)
//	int iRet = MIUWriteOIS(m_iIndexDevice, fi_Byte1, fi_Byte2);

	return true;
}

//! 입력값에 VCM의 Data 값을 적용한 뒤에 반환한다. 
void CMIU::Apply_Data_Code_VCM(BYTE fi_Byte1, BYTE fi_Byte2, BYTE &fo_Byte1, BYTE &fo_Byte2, int fi_code)
{
	//! (VCM Driver 매뉴얼 Ver 1.93 page 7의 8.2 Register Format 참고)
	BYTE dataH = 0, dataL = 0;
	dataH = (fi_code>>4)&0x3f;
	dataL = (fi_code<<4)&0xf0;

	//! Data bit들의 값을 초기화한 후에 변경된 bit들을 적용
	fo_Byte1 = (fi_Byte1 & 0xc0) | dataH;
	fo_Byte2 = (fi_Byte2 & 0x0f) | dataL;
}

//! 입력값에서 VCM의 Data값을 추려낸다.
void CMIU::Get_Data_Code_VCM(BYTE fi_Byte1, BYTE fi_Byte2, int &fo_code)
{
	//! (VCM Driver 매뉴얼 Ver 1.93 page 7의 8.2 Register Format 참고)
	BYTE dataH = 0, dataL = 0;

	dataH = fi_Byte1 & 0x3f;
	dataL = fi_Byte2 & 0xf0;

	fo_code = (dataH << 4) | (dataL >> 4);
}

//! OIS, VCM Driver의 D0 ~ D9 bit에 대한 데이터를 입력한다. 
//! [입력값]
//!  code : 입력예) 0 mA(code = 0), 40 mA (code = 341) , 60 mA (code = 511) 
//!  bFlag_Get : true이면 현재의 VCM 설정값을 가져와서 작업한다. 
bool CMIU::MoveVCM_Code(int code)
{
	if ( code < 0 )
	{
		code = 0;
	}
	if ( code >= 1024 )
	{
		code = 1023;
	}
	//MIUSetI2CIDOIS(0, 0x0C);  // IIC Slave Address 상위 7bit
	//MIUSetI2CModeOIS(0, 0);   // Address 와 Data Length 설정


	BYTE dataH = (code>>4)&0x3f;
	BYTE dataL = (code<<4)&0xf0;

//	MIUWriteOIS(0, dataH, dataL);
	
	return true;
}

//! OIS, VCM Driver의 D0 ~ D9 bit에 대한 데이터를 입력한다.
//! [입력값]
//!  current : MoveVCM_Code와는 달리, 'mA 단위'의 전류값으로 입력한다.  
bool CMIU::MoveVCM_Current(int current)
{
	//! D[9:0] : Data input
	//! Output current = (D[9:0]/1023) X 120mA
	//! (VCM Driver 매뉴얼 Ver 1.93 page 7 참고)
	int code = (int)(((double)current / 120.) * 1023.);

	bool bRet = MoveVCM_Code(code);
	if ( bRet == false )
	{
		return false;
	}

	return true;
}

void CMIU::ReadRawImg(CString strInFileName,int nSizeX,int nSizeY,int nChannel,IplImage *outImage)
{
    FILE *fp;
    int i,j,k;
    char strFileName_c[256];
    strcpy(strFileName_c, strInFileName.GetBuffer());

	if(fopen_s(&fp,strFileName_c, "rb") ==0 )
	{
		unsigned char *temp;
		temp=(unsigned char *)calloc(sizeof(unsigned char),nSizeX*nSizeY);
		
		for(i=0;i<nSizeX;i++)
		{
			fread(temp,nSizeX*nChannel,sizeof(unsigned char),fp);

			for(j=0;j<nSizeY;j++)
			{
				for(k=0; k<nChannel; k++)
				{
					outImage->imageData[i*nSizeX*nChannel + j*nChannel+k] = temp[j*nChannel+k];
				}
			}
		}
		free(temp);

	}
	fclose(fp);
}

void CMIU::ReadRawImg2(CString strInFileName,int nSizeX,int nSizeY,int nChannel,IplImage *outImage)
{
  //   FILE *fp;
  //   int i,j,k;
  //   size_t size_i;
  //   TCHAR strFileName_tc[256];
  //   char strFileName_c[256];
  //   _tcscpy_s(strFileName_tc, strInFileName.GetLength()+1, strInFileName);
	 //wcstombs_s(&size_i, strFileName_c, (size_t)sizeof(strFileName_c), strFileName_tc, (size_t)_tcslen( strInFileName.GetLength() )+1 );

  //   if( fopen_s( &fp,strFileName_c, "rb" ) ==0 )
  //   {
  //       unsigned char *temp;
  //       temp=(unsigned char *)calloc(sizeof(unsigned char),nSizeX*nSizeY);
  //       for(i=0;i<nSizeX;i++)
  //       {
  //           fread(temp,nSizeX*nChannel,sizeof(unsigned char),fp);
  //           for(j=0;j<nSizeY;j++)
  //               for(k=0;k<nChannel;k++)
  //                   outImage->imageData[i*nSizeX*nChannel + j*nChannel+k]=temp[j*nChannel+k];
  //       }
  //       free(temp);
  //   }
  //   fclose(fp);
 }

int CMIU::Grab_StopImage()//norinda
{
	cvSplit(gMIUDevice.imageItp,  pImageBuf[0], pImageBuf[1], pImageBuf[2], NULL);


	MbufPut(vision.MilGrabImageChild[3], pImageBuf[2]->imageData);
	MbufPut(vision.MilGrabImageChild[4], pImageBuf[1]->imageData);
	MbufPut(vision.MilGrabImageChild[5], pImageBuf[0]->imageData);

	//
	return 1;
}


void CMIU::PRI_12BitToRaw8 ( unsigned char *p12Bit, unsigned char *pRawBit8 )	// 1280 x 964 12bit -> 1280 x 960 8bit
{
	int		x, y;
	int		m_iHeight, m_iWidth;
//	FILE *fp = fopen("h:\\test.dat","wt");
//	FILE *fp1 = fopen("h:\\test_8.dat","wt");


	m_iWidth = m_pSID->pInfo->nOutputWidth ;
	m_iHeight	= m_pSID->pInfo->nOutputHeight;
	
	
	for(y=0 ; y<m_iHeight ; y++)
	{

		
		for(x=0 ; x<m_iWidth/2 ; x=x++)
		{			
			pRawBit8[y*m_iWidth + x*2] = (p12Bit[(y+2)*m_iWidth*2 + 4*x+0]) ;		
			pRawBit8[y*m_iWidth + x*2+1 ] = (p12Bit[(y+2)*m_iWidth*2 + 4*x+2]);	
				

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

}




int CMIU::StopLive () {

	DWORD	waitRet ;
	DWORD	dwCode =0 ;

	if ( m_bThreadUsed )
	{
		m_bThreadUsed = false ;	
		Sleep(100) ;
		if(m_hImgViewThread) 
		{		
			waitRet = WaitForSingleObject(m_hImgViewThread, 1000) ;
			if(waitRet == WAIT_TIMEOUT)
			{
				GetExitCodeThread(m_hImgViewThread, &dwCode) ;
				if(dwCode == STILL_ACTIVE)
				{
					TerminateThread(m_hImgViewThread, 0) ;					
				}
			}			
		}
	}

	return true;
}

//void AdjustDisplaySize2(unsigned char* pFrameBuffer, unsigned char* p2byteBuffer, RawImgInfo* pRawImgInfo)
//{
//	if( pRawImgInfo->nSensorWidth != pRawImgInfo->nDisplaySizeX || pRawImgInfo->nSensorHeight != pRawImgInfo->nDisplaySizeY )
//	{
//		for( int y = pRawImgInfo->nDisplayStartPosY ; y < pRawImgInfo->nDisplayStartPosY+pRawImgInfo->nDisplaySizeY ; y++ )
//		{
//			memcpy( p2byteBuffer + (y-pRawImgInfo->nDisplayStartPosY)*pRawImgInfo->nDisplaySizeX*2, 
//				&pFrameBuffer[0]+(y*pRawImgInfo->nSensorWidth*2 + pRawImgInfo->nDisplayStartPosX), pRawImgInfo->nDisplaySizeX*2 );
//		}
//	}
//}

void CMIU::func_Set_InspImageCopy(int nType, BYTE* GrabImage,int AvrCount)
{
    CString str;
	memcpy(vTempBuffer, GrabImage, m_pBoard->GetFrameRawSize());

    if (nType == MID_6500K_RAW)
    {
        //Mid-level (6500K)
        str.Format("Mid_level_6500K");
		memcpy(vDefectMidBuffer_6500K, vTempBuffer, m_pBoard->GetFrameRawSize());
    }
    else if (nType == LOW_LEVEL_RAW)
    {
        //dark 이미지
        //low-level (Dark)
        str.Format("low_level_DARK");
		memcpy(vDefectLowBuffer, vTempBuffer, m_pBoard->GetFrameRawSize());
    }
    else if (nType == MID_2800K_RAW)
    {
        //Mid-level (2800K)  --Color Sensitivity 만 사용(2800K+6500K)
        str.Format("Mid_level_2800K");
		memcpy(vDefectMidBuffer_2800K, vTempBuffer, m_pBoard->GetFrameRawSize());
    }
    else if (nType == CHART_RAW)
    {
        str.Format("CHART1");
		memcpy(vChartBuffet, vTempBuffer, m_pBoard->GetFrameRawSize());
    }
	else if (nType == UV_BEFORE_CHART)
	{
		str.Format("UV_BEFORE_CHART_AVR_%d", AvrCount);
		memcpy(vChartBuffet, vTempBuffer, m_pBoard->GetFrameRawSize());
	}
	else if (nType == UV_AFTER_CHART)
	{
		str.Format("UV_AFTER_CHART_AVR_%d", AvrCount);
		memcpy(vChartBuffet, vTempBuffer, m_pBoard->GetFrameRawSize());
	}
	else if (nType == EOL_CHART)
	{
		str.Format("EOL_CHART_AVR_%d", AvrCount);
		memcpy(vChartBuffet, vTempBuffer, m_pBoard->GetFrameRawSize());
	}
	else if (nType == CHART_SECOND_RAW)
	{
		str.Format("CHART2");
		memcpy(vChart_Second_Buffet, vTempBuffer, m_pBoard->GetFrameRawSize());
	}
    else
    {
        //모두 초기화?
		memset(vChartBuffet, 0, m_pBoard->GetFrameRawSize());
		memset(vChart_Second_Buffet, 0, m_pBoard->GetFrameRawSize());
		memset(vDefectMidBuffer_6500K, 0, m_pBoard->GetFrameRawSize());
        memset(vDefectLowBuffer, 0, m_pBoard->GetFrameRawSize());
        memset(vDefectMidBuffer_2800K, 0, m_pBoard->GetFrameRawSize());

    }
	//g_clApsInsp.func_Insp_Shm_Illumination(vTempBuffer);
    RawImageSave(str, vTempBuffer);

	str.Empty();
}
void CMIU::RawImageSave(CString nType, BYTE* SaveImage)
{
    TCHAR szPath[SIZE_OF_1K];
    TCHAR szFilePath[SIZE_OF_1K];
    SYSTEMTIME stSysTime;
    CFileFind clFinder;
    CString sFileMode = _T("");
    CString strLog;
    CFile clFile;
    int i = 0;
    ::GetLocalTime(&stSysTime);
	

    /*if (_tcslen(g_clTaskWork[m_nUnit].m_szLotID) <= 0)
        _tcscpy_s(g_clTaskWork[m_nUnit].m_szLotID, SIZE_OF_100BYTE, _T("(NULL)"));

    if (_tcslen(g_clTaskWork[m_nUnit].m_szChipID) <= 0)
        _tcscpy_s(g_clTaskWork[m_nUnit].m_szChipID, SIZE_OF_100BYTE, _T("(NULL)"));*/

    if (clFinder.FindFile(BASE_LOG_DIR) == FALSE)
        CreateDirectory(BASE_LOG_DIR, NULL);

    _stprintf_s(szPath, SIZE_OF_1K, _T("%s\\%s"), BASE_LOG_DIR , model.mCurModelName);
    if (clFinder.FindFile(szPath) == FALSE)
        CreateDirectory(szPath, NULL);

    _stprintf_s(szPath, SIZE_OF_1K, _T("%s\\%s\\%04d%02d"), BASE_LOG_DIR, model.mCurModelName, stSysTime.wYear, stSysTime.wMonth);
    if (clFinder.FindFile(szPath) == FALSE)
        CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\%s\\%04d%02d\\%02d"), BASE_LOG_DIR, model.mCurModelName, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

    _stprintf_s(szPath, SIZE_OF_1K, _T("%s\\%s\\%04d%02d\\%02d\\Image"), BASE_LOG_DIR, model.mCurModelName, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay);
    if (clFinder.FindFile(szPath) == FALSE)
        CreateDirectory(szPath, NULL);


    _stprintf_s(szFilePath, SIZE_OF_1K, _T("%s\\%s_%s_%d_%02d%02d%02d%03d.raw"), szPath, Task.ChipID, (LPTSTR)(LPCTSTR)nType, gMIUDevice.dTDATASPEC_n.eDemosaicMethod, stSysTime.wHour, stSysTime.wMinute, stSysTime.wSecond, stSysTime.wMilliseconds);

    CFile           savefile;
    CFileException  e;

    if (!savefile.Open(szFilePath, CFile::modeCreate | CFile::modeWrite, &e))
    {
        strLog.Format("File open fail:");
        theApp.MainDlg->putListLog(strLog);
        return;
    }
    savefile.Write(SaveImage, m_pBoard->GetFrameRawSize());
    savefile.Close();


	sFileMode.Empty();
	strLog.Empty();
}

#define YUV422_MIRROR		5	//Cb0 Y0 Cr0 Y1 / Cb2 Y2 Cr2 Y3
#define YUV422				6	//Cb0 Y0 Cr0 Y1 / Cb2 Y2 Cr2 Y3
#define YUV422_Y			7	//Cb0 Y0 Cr0 Y1 / Cb2 Y2 Cr2 Y3
#define YUV422_2			8	//Y0 Cb0 Y1 Cr0 / Y2 Cb2 Y3 Cr2
#define YUV422_Y2			9	//Cb0 Y0 Cr0 Y1 / Cb2 Y2 Cr2 Y3

