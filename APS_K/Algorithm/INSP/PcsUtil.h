#pragma once


// **************************************************************************************
// 
// 자주 사용되는 Util 함수들을 모아 재정리함.
//
//	History
//		2012.10.22	V 1.0.1		parkchas	Revision
//		2012.11.05	V 1.1.0		parkchas	재정리. Logfile 기록(Define 변경). 함수 추가.
//
// **************************************************************************************


//////////////////////////////////////////////////////////////////////////
// 변수 선언
//

/* LOG FILE 기록 방법 변수 정의 ( DIR , FILE NAME ) **********************************/
#ifndef LOGFILE
#define LOGFILE

#define LOGFILE_DIR_DAY			1	// LOGS/DAY		folder 생성
#define LOGFILE_DIR_MONTH		2	// LOGS/MONTH	folder 생성
#define LOGFILE_DIR_YEAR		4	// LOGS/YEAR	folder 생성
#define LOGFILE_DIR_FULLDAY		7	// LOGS/YEAR/MONTH/DAY folder 생성

#define LOGFILE_FILE_HOUR		64	// FileName(           hh) Filename 생성
#define LOGFILE_FILE_DATE		128	// FileName(yyyy-mm-dd   ) Filename 생성
#define LOGFILE_FILE_FULLDAY	192	// FileName(yyyy-mm-dd hh) Filename 생성
#endif


#define INVALID_ARGUMENT				20001


/*****************************************************************************/
/*	THREAD 관련 정의                                                          */
/*****************************************************************************/
#define THREAD_CREATE_MAXCNT_OVER		30001


/*****************************************************************************/
/*	FTP 관련 정의                                                          */
/*****************************************************************************/
#define FTP_DOWNLOAD_FAIL				40001


//////////////////////////////////////////////////////////////////////////
// Macro 선언
//
#ifndef UTCHAR
#define UTCHAR(var,len) TCHAR var[len]; ZeroMemory(var,sizeof(var));
#endif


//////////////////////////////////////////////////////////////////////////
// Process Function
//
void DoEvent(int iMiliSecond=10);


//////////////////////////////////////////////////////////////////////////
// Directory / File Function
//
BOOL WINAPI MakeFullDir(LPCTSTR lpszDirPath);

BOOL ReturnParameter(CString szOrigin, char cDelimeter, int nOrder, CString &szReturn);
void ReturnSeperatorFileName(LPCTSTR lpszFullPathName, LPCTSTR lpszPath, LPCTSTR lpszFileName);
void ReturnSeperatorFileName(CString szFullPathName, CString &szPath, CString &szFileName);

void GetCurTimeString(PTCHAR lpszCurTime, LPCTSTR alpszFlag);

BOOL WINAPI MakeSureDirectoryPathExists(LPCTSTR lpszDirPath);
// V 1.1.0 Revision
void _WriteLogFile(LPCTSTR apszLogMsg, LPCTSTR apszLogDir, LPCTSTR apszLogFile, UINT apuiOption=LOGFILE_DIR_FULLDAY | LOGFILE_FILE_FULLDAY);


BOOL SetRegistyStartProgram(BOOL bAutoExec, LPCSTR lpValueName, LPCSTR lpExeFileName);


// =======================================================================
//	Binary Data Operation
//
long arr2long (byte* arr, long start);


// =======================================================================
//	Hexa Data Operation
//
int CStringToHexaBytes(CString szInput, PBYTE pOutput);
int CharStringToHexaBytes(char* pszInput, PBYTE pOutput);
BYTE	byCode2AsciiValue( char cData );
int AsciiToHex(char *pSrc, char* pDst, int iSrcLength, char cSeperator);// 정수를 HEX 스트링으로...


// =======================================================================
//	영상 처리 기술
//	Bitmap Image
//
int BuildImageSize(int, int, int);						// 이미지 크기와 비트수 그리고 더미값을 통해 실제 이미지 크기 알아내기
int DetermineDummyValue(int, int);						// 비트맵 가로길이 4배수 나머지 값 알아내기
bool LoadBMPIntoDC ( HDC hDC, LPCTSTR bmpfile );
bool LoadBMPIntoDC ( HDC hDC, CRect rc, LPCTSTR bmpfile );
BYTE* LoadBMP24bit ( int* width, int* height, long* size, LPCTSTR bmpfile );
BYTE* ConvertBMPToRGBBuffer ( BYTE* Buffer, int width, int height );
bool SaveBMP24bit ( BYTE* Buffer, int width, int height, long paddedsize, LPCTSTR bmpfile );


// =======================================================================
//	File 함수
BOOL WINAPI FileExists(LPCTSTR szFileName);
BOOL FileFolderCopyMove(CString strSrcPath, CString strDestPath, UINT wFunc, HWND hWnd);
long GetFileSize(char* szFile);



// =======================================================================
//	Character 변형 함수
//
char *commify(double val, char *buf, int round=0);
//CString CommaString(double rVal, int round=0);
char* CommaString(double rVal, int round=0);
char* TrimRight( char * szAscii );
char* TrimLeft ( char * szAscii );
char* Trim	   ( char * szAscii );
char* TrimCopy ( char * szAscii );

int CharCount(CString szOrigin, char cDelimeter);
void CoordinateTrans( double sx, double sy, double *tx, double *ty, int type );
double ST2Second(SYSTEMTIME st);


// 진행시간 측정용 : mili-seconds 단위로 확인 가능하다.
// 사용법 : Instance 를 생성하고,
//          STARTTIMER() 함수를 호출하고 타이머를 시작한다.
//          GetElapsedTime() 함수로 진행시간을 리턴 받는다.

class CElapsedTimer
{
public:
	CElapsedTimer( BOOL bInitStart = FALSE )
	{
		sTime.HighPart = 0;					// 시작
		sTime.LowPart  = 0;					// 시작
		eTime.HighPart = 0;					// 시작
		eTime.LowPart  = 0;					// 시작
		freq.HighPart = 0;					// 시작
		freq.LowPart  = 0;					// 시작

		if( bInitStart ) STARTTIMER();
	};
	~CElapsedTimer() {};

private:
	LARGE_INTEGER sTime;					// 시작
	LARGE_INTEGER eTime;					// 끝남
	LARGE_INTEGER freq;						// 타이머 주기

public:
	void STARTTIMER( void )
	{
		QueryPerformanceFrequency( &freq );	// 타이머의 주기를 얻어서 freq에 저장
		QueryPerformanceCounter( &sTime );	// 시작시간 저장
	};

	__int64 GetElapsedTime()
	{
		QueryPerformanceCounter( &eTime );	// 동작 주기용 현재 시간을 가져온다.
		return ( eTime.QuadPart - sTime.QuadPart ) / ( freq.QuadPart / 1000 );
	};
};