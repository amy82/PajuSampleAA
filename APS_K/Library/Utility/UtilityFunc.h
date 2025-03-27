#pragma once

//! 전역(Global) Utility 함수를 선언한다. 
//! 전역(Global) Utility 함수의 구현은 'UtilityFunc.cpp' 파일에서 한다. 
//! Program안에서 반복적으로 사용되는 기능들을 전역 함수로 제작하여 사용한다. 
//! Maked by LHW, 2010/6/1
//! Version : 2013/3/17

#include "../../stdafx.h"

//! 현재 시각 반환
CString GetString_CurrentSystemTime();											
//! 현재 시각 반환
CString GetString_CurrentLocalTime();
//! 현재 시각 반환
CString GetString_CurrentTime();									
//! 현재 시각 반환
CString GetString_CurrentTime_HMS();												
//! 현재 시각 반환
CString GetString_CurrentTime_AP();												

//! 입력된 시각을 비교하여, 시간차를 반환한다.
int CompareSystemTime(SYSTEMTIME strTime1, SYSTEMTIME strTime2);
//! 입력된 시각을 복사한다. (strTime1 = strTime2), strTime2의 시각을 strTime1에 입력한다. 
void CopySystemTime(SYSTEMTIME strTime_Source, SYSTEMTIME &strTime_Dest);

//! 문자열 파싱 함수
void ParseString(CStringArray& Token, CString& szOriginal, TCHAR* cpDelimiter);			
//! 문자열 파싱 함수
void ParseString(CStringArray& Token, CString& szOriginal, TCHAR cDelimiter);			
//! 문자열 분리 함수
bool GetSeparateNumber(CString szInput, int &iFirst, int &iSecond, TCHAR* cpDelimiter);				
//! 문자열 분리 함수
bool GetSeparateNumber(CString szInput, int &iFirst, double &dbSecond, TCHAR* cpDelimiter);			
//! 문자열 분리 함수
bool GetSeparateString(CString szInput, CString &szFirst, CString &szSecond, TCHAR* cpDelimiter);	

//! Text 파일(txt, csv 등) 읽기 함수
int ReadTextFile(CString szFilePath, CStringArray &arrContents);						
//! Text 파일(txt, csv 등) 저장 함수
int SaveTextFile(CString szFilePath, CString szContent, bool bAppend = false);			
//! Text 파일(txt, csv 등) 저장 함수
int SaveTextFile(CString szFilePath, CStringArray &arrContents, bool bAppend = false);	
//! Text 파일(txt, csv 등) 저장 함수
int SaveTextFile(CString szFilePath, TCHAR **pczContents, int iStartIndex, int iSaveTextSize, int iBufSize_1, bool bAppend = false);
//! CFileException의 에러 문자열 반환
CString GetErrorMsg_FileException(int iErrorValue);										

//! 프로그램이 실행된 폴더의 경로를 알아낸다. 
CString GetProgramExeFolderPath();
//! 주어진 경로명에서 Driver 이름만 추출한다. 
CString GetDriveName(CString szPath);														
//! 주어진 경로명에서 폴더 만의 경로를 추출
CString GetFolderPath(CString szFilePath);
//! 주어진 경로명에서 파일명 (확장자 포함)만을 추출
CString GetFileNameExt(CString szFilePath);	
//! 주어진 경로명에서 파일 확장자 만을 추출
CString GetFileExt(CString szFilePath);										
//! 주어진 경로명에 폴더, 파일이 존재하면 true
bool IsExist_Path(CString szInput);		
//! 주어진 폴더 경로명 맨 뒤에 "\\" 문자가 없으면 추가한다. 
CString Append_Char_FolderPath(CString szFolderPath);
//! 문자열이 폴더 이름으로 적합하면 true
bool IsValid_FolderName(CString szInput);													
//! 문자열이 경로명으로 적합하면 true
bool IsValid_Path(CString szInput);												
//! 폴더를 하위 폴더, 파일까지 모두 삭제
int RemoveFolder(CString szFolderPath);														
//! 폴더 하위의 폴더, 파일 목록을 가져온다. 
int GetList_Sub_FolderInfo(CString szFolderPath, CStringArray &arrInfo, bool bFile = false);
//! 폴더 하위의 파일을 모두 복사
int CopyFiles_In_Folder(CString szFolderPath_Source, CString szFolderPath_Dest);
//! 입력한 폴더 하위에 차례대로 폴더가 있는지 확인하고 없으면 생성한 뒤에 최종 폴더명을 반환
int CreateSubFolders(CString szFolderPath, CStringArray &arrSubFolderName, CString &szLastFolderPath);
//! 년,월,일을 하위 폴더명으로 생성한다. 
int CreateSubFolders(CString szFolderPath, int iYear, int iMonth, int iDay, CString &szLastFolderPath);
//! 년,월,일,시간을 하위 폴더명으로 생성한다. 
int CreateSubFolders(CString szFolderPath, int iYear, int iMonth, int iDay, int iHour, CString &szLastFolderPath);

//! 문자열이 실수 일 때, 소수점 자리수를 반환
int GetDoublePointIndex(CString szInput);											
//! 소수점 반올림 함수	
double GetFloor(double dbInput, int iResultMode);									
//! 실수를 입력된 소수점 자리수를 가진 문자열로 변환
CString GetStringFromDouble(double dbInput, int iPrecision);						
//! 실수를 실수로 나눈 나머지를 반환
double GetDoubleModulus(double dbInput, double dbDivide, int *piMultiply = NULL);	
//! 문자열을 정수부와 소수점 자리 부분의 2개의 정수로 반환
bool GetInteger_From_Double(CString szInput, int &iInterger, int &iDecimalPoint);
//! 문자열을 정수부와 소수점 자리 부분의 실수로 반환
bool GetInteger_From_Double(CString szInput, int &iInterger, double &dbDecimalPoint);

//! 문자열이 숫자(음수, 실수 포함)인지를 확인
bool IsValid_Digit(CString szInput);											
//! 문자열이 정수이면 true
bool IsValid_Integer(CString szInput, bool bMinusChk = false);											
//! 문자열이 실수이면 true
bool IsValid_Double(CString szInput, bool bMinusChk = false);					
//! 문자열이 지수이면 true를 반환
bool IsValid_Exponential(CString szInput);										
//! 문자열이 문자, 숫자이면 true
bool IsValid_AlphaNumeric(CString szInput);

//! 입력된 szInput1 문자열에서 szInput2 문자열이 포함된 개수를 알아낸다. 
int GetCount_String_In_String(CString szInput1, CString szInput2);					

//! 입력한 정수값을 2개로 분리하여, 2개의 8 bit 16진수로 반환
void Separate_Hex_From_Integer_8bit(int iInput, int &iHigh, int &iLow);
//! 입력한 2개의 8 bit 16진수값을 합쳐서, 1개의 정수값을 반환
void Merge_Integer_From_Hex_8bit(int iHigh, int iLow, int &iOutput);
//! 입력된 16진수 숫자에 해당하는 문자를 반환
TCHAR GetHexChar(int iInput);
//! 10진수를 16진수 숫자로 변경
long Convert_Decimal_To_Hex(int iInput_Decimal);
//! 입력된 16진수 숫자 문자열을 16진수 숫자로 변경
long HexString_to_Num(CString szHex);
long HexString_to_Num(LPTSTR czHex);
//! 입력된 16진수 숫자를 10진수 숫자로 변경, Hex -> Dec
int ConvertHexToDec(TCHAR *pszHex);										
//! 입력된 문자열을 실수형 숫자로 반환
double Convert_String_Double(CString szInput);	

//! 중심점 iCenterX, iCenterY의 좌표에 폭 iWidth, 높이 iHeight를 가진 사각 영역을 반환한다. 
CRect makeP2R(int iCenterX, int iCenterY, int iWidth, int iHeight);								

//! pWndofSub을 pWndToCenterOn의 중심에 위치시킨다. 
void CenterWindowOnOwner(CWnd* pWndToCenterOn, CWnd* pWndofSub, bool bFlag_Top = false);

//! 해당 객체를 화면 맨 위로 설정한다.
void Set_TopWindow(CWnd* pWnd);

//! HDD 드라이버의 목록을 가져온다.
int GetHDDList(CStringArray &arrDriveList);									
//! 드라이버의 남은 용량을 MByte 단위로 받는다. 
double GetRemainSize_InHDD(CString szDriver, double *pdbTotalSize = NULL);		

//! 입력한 리소스의 사각 영역을 가져온다.
int GetWindowRect_FromUI(int iUID, CWnd* pParentWnd, CRect &rcRet);
//! 입력한 리소스의 사각 영역을 가져온다.
int GetClientRect_FromUI(int iUID, CWnd* pParentWnd, CRect &rcRet);
//! 입력한 리소스의 사각 영역을 설정한다. 
int SetRect_InCtrl(int iUID, CWnd* pParentWnd, CRect rcInput);

//! 입력한 리소스의 핸들값을 가져온다.
HWND GetHandle_FromUI(int iUID, CWnd* pParentWnd);

//! 해당 컨트롤의 활성화/비활성화
int SetEnableState_InCtrl(int iUID, CWnd* pParentWnd, bool bEnable);
//! 해당 컨트롤의 활성화 여부
int GetEnableState_InCtrl(int iUID, CWnd* pParentWnd, bool &bGetEnable);			
//! 해당 컨트롤에 포커스 설정
int SetFous_InCtrl(int iUID, CWnd* pParentWnd);

//! 해당 컨트롤을 눈에 보이게 하거나 숨기기
int SetVisibleState_InCtrl(int iUID, CWnd* pParentWnd, bool bVisible);
//! 해당 컨트롤의 눈에 보이는 여부
int GetVisibleState_InCtrl(int iUID, CWnd* pParentWnd, bool &bGetVisible);

//! 해당 Button(또는 Check, Radio) 컨트롤의 선택 상태를 알아 낸다. 
int GetButtonCheckState_InCtrl(int iUID, CWnd* pParentWnd, bool &bGetCheck);
//! 해당 Button(또는 Check, Radio) 컨트롤의 선택 상태를 설정
int SetButtonCheckState_InCtrl(int iUID, CWnd* pParentWnd, bool bCheck);

//! 입력한 리소스에서 문자열을 가져온다. 
int GetString_FromUI(int iUID, CWnd* pParentWnd, CString &szRet);			
//! 입력한 리소스에서 양의 정수형 값을 가져온다. 
int GetIntegerValue_FromUI(int iUID, CWnd* pParentWnd);							
//! 입력한 리소스에서 실수형 값을 가져온다. 
int GetDoubleValue_FromUI(int iUID, CWnd* pParentWnd, double &dbRet);

//! 입력한 리소스에 문자열을 설정한다.
int SetString_to_UI(int iUID, CWnd* pParentWnd, CString szInput);

//! 입력된 문자열을 입력한 리소스를 가진 Edit 컨트롤에 표시한다. 
int SetString_InEditCtrl(int iUID, CWnd* pParentWnd, CString szText);			
//! 입력된 문자열을 입력한 리소스를 가진 Edit 컨트롤에 추가한다. 이 때, Edit 컨트롤은 'Multi Line' 속성을 가져야 한다. 
int AppendString_InEditCtrl(int iUID, CWnd* pParentWnd, CString szAdd, bool bNextLine, bool bReset = false);

//! 특정 CPU에서 Thread를 사용할 때, 사용 CPU를 지정하기 위한 Mask 처리 관련	
//! 입력된 데이터에서 SetProcessAffinityMask, SetThreadAffinityMask 함수에서 사용가능한 Mask 값을 구한다. 
DWORD GetMask_CPU_Affinity(int *piCPU_Use, int iSize);

//! Process (프로그램 전체)에서 사용하는 CPU를 설정한다.
//! [주의 사항] 
//!		1) Process에서 사용할 CPU는 하위의 모든 Thread가 사용할 CPU를 포함해야 한다. 
//!		2) Thread Affinity(친화도)는 항상 Process Affinity(친화도)의 서브셋이어야 한다.
//! [입력값]
//!     bFlag_All_CPU : true이면,  PC의 모든 CPU Core를 사용하는 것으로 설정한다. piCPU_Use, iSize 값은 사용하지 않는다.
//!                     false이면, iSize 크기의 piCPU_Use 버퍼의 데이터를 이용한다.
//!     piCPU_Use : 0 번 index가 1번 CPU를 가리킨다. 1번 index는 2번 CPU, ...
int SetProcessAffinity(bool bFlag_All_CPU, int *piCPU_Use = NULL, int iSize = 0);

//! bool abTest[16]일 때, 배열의 크기 : sizeof(abTest) / sizeof(bool)
//! 정수형 값을 bool형 배열(크기가 16 이상)로 변환
bool Convert_Integer_To_BooleanBuffer(int iInput, bool *pabOutput, int iBufSize_Output);
//! bool형 배열(크기가 16 이상)을 정수형 값으로 변환
bool Convert_BooleanBuffer_To_Integer(bool *pabInput, int iBufSize_Input, int *piOutput);

//! 16 bit 정수 2개를 합쳐서, 32 bit 정수 1개로 변환
int Convert_Integer_From_16bit_To_32bit(int iInput1_Low_16bit, int iInput2_High_16bit);

//! [주의 사항] double -> int 자료형 변환에서 반올림을 하지 않으면 심각한 오차가 발생한다. 반올림을 해도 오차가 '0'이 되지는 않는다.
//! [입력값] bFlag_Round_Off : true이면 반올림을 한다. 
//! 자료형 변환으로 인해 코드가 지저분해져서 추가한 함수, 단순히 입력값을 곱해주고 형 변환을 해서 반환한다. 
int CalcMultiply(double dbInput1, double dbInput2, bool bFlag_Round_Off = true);
int CalcMultiply(double dbInput1, int iInput2, bool bFlag_Round_Off = true);
CRect CalcMultiply(double dbInput, CRect rcInput, bool bFlag_Round_Off = true);
CRect CalcMultiply(double dbInputX, double dbInputY, CRect rcInput, bool bFlag_Round_Off = true);
//! 자료형 변환으로 인해 코드가 지저분해져서 추가한 함수, 단순히 첫번째 입력값을 2번째 입력값으로 나누어주고 형 변환을 해서 반환한다. 
//! 단, 2번째 입력값이 '0'이면 '0'을 반환한다. 
int CalcDivide(double dbInput1, double dbInput2, bool bFlag_Round_Off = true);
int CalcDivide(double dbInput1, int iInput2, bool bFlag_Round_Off = true);
int CalcDivide(int iInput1, double dbInput2, bool bFlag_Round_Off = true);
CRect CalcDivide(double dbInput, CRect rcInput, bool bFlag_Round_Off = true);
CRect CalcDivide(double dbInputX, double dbInputY, CRect rcInput, bool bFlag_Round_Off = true);

//! 입력된 사각 영역을 전체 사각 영역을 넘지 않도록 교정하여 반환 
void Get_Valid_Point(CRect rcEntire, CPoint &ptInput);
void Get_Valid_Line(CRect rcEntire, CPoint &ptStart, CPoint &ptEnd);
CRect Get_Valid_Rect(CRect rcEntire, CRect rcInputChk, bool bFlag_Base_Left, bool bFlag_Base_Top);

//! 마우스, 키보드 입력 등의 이벤트 발생이 있는지 체크.. 
void checkMessage();
//! Idle Loop Processing
bool PeekAndPump();
