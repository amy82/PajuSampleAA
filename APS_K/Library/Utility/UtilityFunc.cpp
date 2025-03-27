

#include "stdafx.h"
#include "UtilityFunc.h"

//! 'UtilityFunc.h' 파일에서 선언한 전역 함수들을 구현한다. 


//! [기능] 영국 그리니치 천문대 표준시각을 msec 단위까지 알아내어 문자열로 구성하여 반환한다. 
//! [반환값] 시각 표시 문자열
CString GetString_CurrentSystemTime()
{
	SYSTEMTIME stCurrentSystem;
	::GetSystemTime(&stCurrentSystem);
	CString szRet = _T("");
	szRet.Format(_T("%04d-%02d-%02d %02d:%02d:%02d [%d]"), 
		stCurrentSystem.wYear, stCurrentSystem.wMonth, stCurrentSystem.wDay, 
		stCurrentSystem.wHour, stCurrentSystem.wMinute, stCurrentSystem.wSecond, 
		stCurrentSystem.wMilliseconds);
	return szRet;
}

//! [기능] 현지 표준시각을 msec 단위까지 알아내어 문자열로 구성하여 반환한다. 
//! [반환값] 시각 표시 문자열
CString GetString_CurrentLocalTime()
{
	SYSTEMTIME stCurrentLocal;
	::GetLocalTime(&stCurrentLocal);
	CString szRet = _T("");
	szRet.Format(_T("%04d-%02d-%02d %02d:%02d:%02d [%d]"), 
		stCurrentLocal.wYear, stCurrentLocal.wMonth, stCurrentLocal.wDay, 
		stCurrentLocal.wHour, stCurrentLocal.wMinute, stCurrentLocal.wSecond, 
		stCurrentLocal.wMilliseconds);
	return szRet;
}

//! [기능] 현지 표준시각을 sec 단위까지 알아내어 문자열로 구성하여 반환한다.
//! [반환값] 시각 표시 문자열
CString GetString_CurrentTime()
{
	COleDateTime currentTime;
	currentTime = COleDateTime::GetCurrentTime();
	CString szRet = _T("");
	szRet.Format(_T("%04d%02d%02d_%02d%02d%02d"), currentTime.GetYear(), currentTime.GetMonth(), currentTime.GetDay(), 
		currentTime.GetHour(), currentTime.GetMinute(), currentTime.GetSecond());
	return szRet;
}

//! [기능] 현지 표준시각을 sec 단위까지 알아내어 문자열로 구성하여 반환한다. (시각을 0 ~ 24로 표시한다)
//! [반환값] 시각 표시 문자열
CString GetString_CurrentTime_HMS()
{
	COleDateTime currentTime;
	currentTime = COleDateTime::GetCurrentTime();
	CString szRet = _T("");
	szRet = currentTime.Format(_T("%Y-%m-%d %H:%M:%S"));
	return szRet;
}

//! [기능] 현지 표준시각을 sec 단위까지 알아내어 문자열로 구성하여 반환한다. (시각을 AM/PM으로 구분한다)
//! [반환값] 시각 표시 문자열
CString GetString_CurrentTime_AP()
{
	COleDateTime currentTime;
	currentTime = COleDateTime::GetCurrentTime();
	CString szRet = _T("");
	szRet = currentTime.Format(_T("%Y-%m-%d %I:%M:%S %p"));
	return szRet;
}

//! [기능] 주어진 절대 경로에 폴더, 파일이 존재하는지 확인한다. 
//! [입력값] szInput : 절대 경로명
//! [반환값] 폴더, 파일이 존재하면 true를 반환한다. 
bool IsExist_Path(CString szInput)
{
	DWORD dwAttribute;
	dwAttribute = ::GetFileAttributes(szInput);
	if ( dwAttribute == -1 )	//! 해당 경로에 폴더가 존재하지 않을 경우
	{
		return false;
	}

	return true;
}

//! [기능] 주어진 폴더 경로명 맨 뒤에 "\\" 문자가 없으면 추가한다. 
CString Append_Char_FolderPath(CString szFolderPath)
{
	CString szRetPath = _T("");
	szRetPath.Format(_T("%s"), szFolderPath);
	if ( szRetPath.Right(1) != _T("\\") )
	{
		szRetPath += _T("\\");
	}
	return szRetPath;
}

//! [기능] 문자열이 폴더명으로 적합하면 true
//! [입력값] 폴더의 절대 경로가 아니라, 폴더의 이름이 될 문자열
//! [반환값] true이면 입력된 문자열이 폴더명으로 적합하다. false이면 부적합하다.
bool IsValid_FolderName(CString szInput)
{
	int iLenInput = (int)(szInput.GetLength());
	if ( iLenInput <= 1 )
	{
		return true;
	}

	bool bRet = true;

	int i = 0;
	CString szTemp = _T("");
	szTemp = szInput;
	TCHAR *czTemp = szTemp.GetBuffer( szTemp.GetLength() + 1 );

	//! '\\, /, :, *, ?, \", <, >, |' 등의 문자는 폴더의 이름으로 사용할 수 없습니다.
	for ( i = 0; i < iLenInput; i++ )
	{
		if ( czTemp[i] == _T('/') || czTemp[i] == 0x5c || czTemp[i] == _T(':') || czTemp[i] == _T('|') || 
			czTemp[i] == _T('*') || czTemp[i] == _T('?') || czTemp[i] == _T('<') || czTemp[i] == _T('>') )
		{
			bRet = false;
			break;
		}
	}

	szTemp.ReleaseBuffer();

	return bRet;
}

//! [기능] 문자열이 경로명에 적합한지 확인한다. 
//! [반환값] 문자열이 경로명으로 적합하면 true, 문자열의 길이가 0이면 true를 반환함
bool IsValid_Path(CString szInput)
{
	int iLen = (int)(szInput.GetLength());
	if ( iLen <= 0 )
	{
		return true;
	}

	bool bRet = true;

	CString szTemp = _T("");
	szTemp = szInput;
	TCHAR *czTemp = szTemp.GetBuffer( iLen + 1 );

	if ( iLen == 1 )
	{
	}
	else
	{
		//! 0x5c : _T('\')

		for ( int i = 0; i < (iLen - 1); i++ )
		{
			if ( czTemp[i] == _T('/') && czTemp[i + 1] == _T('/') )	
			{
				bRet = false;
				break;
			}
			else if ( czTemp[i] == 0x5c && czTemp[i + 1] == 0x5c )
			{
				bRet = false;
				break;
			}
			else if ( czTemp[i] == 0x5c && czTemp[i + 1] == _T('/') )	
			{
				bRet = false;
				break;
			}
			else if ( czTemp[i] == _T('/') && czTemp[i + 1] == 0x5c )	
			{
				bRet = false;
				break;
			}
		}
	}

	szTemp.ReleaseBuffer();

	return bRet;
}

//! [기능]   프로그램이 실행된 폴더의 경로를 알아낸다. 
//! [반환값] 실행 파일이 위치한 폴더의 절대 경로명
CString GetProgramExeFolderPath()
{
	TCHAR szPath[_MAX_PATH  ];
	TCHAR drive [_MAX_DRIVE ];
    TCHAR dir   [_MAX_DIR   ];
    //TCHAR fname [_MAX_FNAME ];
    //TCHAR ext   [_MAX_EXT   ];
	GetModuleFileName(NULL, szPath, sizeof(szPath));
	_tsplitpath_s( szPath, drive, sizeof(drive), dir, sizeof(dir), NULL, 0, NULL, 0 );
	CString szRet = _T(""), szFolderPath = _T("");
	szFolderPath.Format(_T("%s%s"), drive, dir);
	szRet = Append_Char_FolderPath(szFolderPath);
	return szRet;
}

//! [기능] 폴더 삭제, 하위폴더, 파일이 있으면 모두 삭제한다.
//! [입력값] 폴더의 절대 경로명
//! [반환값] 정상적으로 작동하면 숫자 1을 반환하고, 오류가 발생하면 음수를 반환한다. 
int RemoveFolder(CString szFolderPath)
{
	//! 원래는 함수 인자가 'LPTSTR lpFolder'였지만 사용하기 불편하므로, 'CString szFolderPath'로 수정하다. 
	int iLength = (int)(szFolderPath.GetLength());
	if ( iLength <= 0 )
	{
		return -1;
	}

	if ( ::GetFileAttributes(szFolderPath) == -1 )	//! 폴더가 없을 경우
	{
		return -2;
	}

	LPTSTR lpFolder = NULL;
	lpFolder = szFolderPath.GetBuffer( iLength + 1 );

	WIN32_FIND_DATA		FindData;
    HANDLE				hFindHandle;
    TCHAR				czTemp[MAX_PATH];
    int					iLen_lpFolder = 0;

	//! 입력된 경로명의 유효성을 검사한다.
    if ( lpFolder == NULL )
    {
		szFolderPath.ReleaseBuffer();
        return -3;
    }
    if ( *lpFolder == '\0' )
    {
		szFolderPath.ReleaseBuffer();
        return -4;
    }

	//! 입력된 폴더의 하위 폴더, 파일 검색을 위한 검색 문자열 생성
    iLen_lpFolder = (int)(_tcslen(lpFolder));
    if ( lpFolder[iLen_lpFolder - 1] == '\\' )
    {
        _stprintf_s(czTemp, _T("%s*.*"), lpFolder);
    }
    else
    {
        _stprintf_s(czTemp, _T("%s\\*.*"), lpFolder);
    }

	//! 입력된 폴더의 하위 폴더, 파일 검색 시작
    hFindHandle = ::FindFirstFile(czTemp, &FindData);

	//! 입력된 폴더의 하위에 폴더나 파일이 있을 경우
    if ( INVALID_HANDLE_VALUE != hFindHandle )
    {
        while(1)
        {
			//! 찾아낸 파일, 폴더의 완전한 절대 경로명 생성
            if ( lpFolder[iLen_lpFolder - 1] == '\\' )
            {
                _stprintf_s(czTemp, _T("%s%s"), lpFolder, FindData.cFileName);
            }
            else
            {
                _stprintf_s(czTemp, _T("%s\\%s"), lpFolder, FindData.cFileName);
            }

			//! 폴더일 경우
            if(FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                if ( _tcscmp(FindData.cFileName, _T(".")) == 0 )	//! 자기 자신의 폴더를 의미
                {
                    //.    -->> skip
                }
                else if ( _tcscmp(FindData.cFileName, _T("..")) == 0 )	//! 상위 폴더를 의미
                {
                    //..   -->> skip
                }
                else
                {
                    RemoveFolder(czTemp);	//! 재귀 호출

					//! 폴더의 속성을 삭제가 가능하도록 수정한다. 
                    if ( (FindData.dwFileAttributes & FILE_ATTRIBUTE_READONLY) || 
                        (FindData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) )
                    {
                        ::SetFileAttributes(czTemp, FILE_ATTRIBUTE_NORMAL);
                    }

                    ::RemoveDirectory(czTemp);	//! 비어 있는 하위 폴더 삭제
                }
            }
            else
            {
                //! 파일일 경우

				//! 파일의 속성을 삭제가 가능하도록 수정한다. 
                if ( (FindData.dwFileAttributes & FILE_ATTRIBUTE_READONLY) || 
                    (FindData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) )
                {
                    ::SetFileAttributes(czTemp, FILE_ATTRIBUTE_NORMAL);
                }

                ::DeleteFile(czTemp);	//! 파일 삭제
            }

			//! 입력된 폴더 내에 다른 폴더, 파일이 있는지 계속 검사를 진행
            if ( !::FindNextFile(hFindHandle, &FindData) )
            {
                break;	//! 입력된 폴더 아래에 하위 폴더, 파일이 없으면 검색 중단
            }
        }
    }
    ::FindClose(hFindHandle);

	//! 폴더의 속성을 삭제가 가능하게 할 경우
    ::SetFileAttributes(lpFolder, FILE_ATTRIBUTE_NORMAL);
	//! 입력된 폴더 삭제
    ::RemoveDirectory(lpFolder);

	szFolderPath.ReleaseBuffer();

	return 1;
}

//! [기능] 입력된 경로의 폴더 아래에 있는 폴더의 이름이나 파일의 이름을 CStringArray 타입으로 가져온다. 
//! [입력값] szFolderPath : 폴더의 절대 경로, bFile : true이면 파일 이름의 목록을 가져온다, false이면 폴더 이름의 목록을 가져온다. 
//! [반환값] 정상적으로 작동하면 숫자 1을 반환하고, 오류가 발생하면 음수를 반환한다. 
//!			 arrInfo : 폴더 이름이나 파일 이름이 저장되어 반환된다. 
int GetList_Sub_FolderInfo(CString szFolderPath, CStringArray &arrInfo, bool bFile)
{
	int iLength = (int)(szFolderPath.GetLength());
	if ( iLength <= 0 )
	{
		return -1;
	}

	if ( ::GetFileAttributes(szFolderPath) == -1 )	//! 폴더가 없을 경우
	{
		return -2;
	}

	LPTSTR lpFolder = NULL;
	lpFolder = szFolderPath.GetBuffer( iLength + 1 );

	WIN32_FIND_DATA		FindData;
    HANDLE				hFindHandle;
    TCHAR				czTemp[MAX_PATH];
	TCHAR				czFindTemp[MAX_PATH];
    int					iLen_lpFolder = 0;
	CString				szAdd = _T("");
	TCHAR				*pcFound;
	int					iTempBufSize = 0, iFoundindex = 0;

	//! 입력된 경로명의 유효성을 검사한다.
    if ( lpFolder == NULL )
    {
		szFolderPath.ReleaseBuffer();
        return -3;
    }
    if ( *lpFolder == '\0' )
    {
		szFolderPath.ReleaseBuffer();
        return -4;
    }

	//! 기존 데이터 삭제
	arrInfo.RemoveAll();
	arrInfo.FreeExtra();

	//! 입력된 폴더의 하위 폴더, 파일 검색을 위한 검색 문자열 생성
    iLen_lpFolder = (int)(_tcslen(lpFolder));
    if ( lpFolder[iLen_lpFolder - 1] == '\\' )
    {
        _stprintf_s(czTemp, _T("%s*.*"), lpFolder);
    }
    else
    {
        _stprintf_s(czTemp, _T("%s\\*.*"), lpFolder);
    }

	//! 입력된 폴더의 하위 폴더, 파일 검색 시작
    hFindHandle = ::FindFirstFile(czTemp, &FindData);

	//! 입력된 폴더의 하위에 폴더나 파일이 있을 경우
    if ( INVALID_HANDLE_VALUE != hFindHandle )
    {
        while(1)
        {
			//! 폴더일 경우
            if(FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                if ( _tcscmp(FindData.cFileName, _T(".")) == 0 )	//! 자기 자신의 폴더를 의미
                {
                    //.    -->> skip
                }
                else if ( _tcscmp(FindData.cFileName, _T("..")) == 0 )	//! 상위 폴더를 의미
                {
                    //..   -->> skip
                }
                else
                {
					if ( FindData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM )	//! 운영 체제에서 자동 생성한 폴더일 경우
					{
						//   -->> skip
					}
					else
					{
						if ( bFile == false )
						{
							szAdd.Format(_T("%s"), FindData.cFileName);
							arrInfo.Add(szAdd);
						}
					}
                }
            }
            else
            {
                //! 파일일 경우

				if ( FindData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM )	//! 운영 체제에서 자동 생성한 파일일 경우
				{
					//   -->> skip
				}
				else
				{
					if ( bFile == true )
					{
						//! 확장자 문자열을 잘라내는 작업을 진행한다. 
						_tcscpy_s(czFindTemp, FindData.cFileName);
						pcFound = _tcsrchr( czFindTemp, _T('.') );
						if ( pcFound != NULL )	//! 확장자 문자열을 구분하는 '.'이 발견되다. 
						{
							iTempBufSize = (int)(sizeof(czFindTemp));
							iFoundindex = pcFound - czFindTemp;
							if ( iFoundindex > 0 && iFoundindex < iTempBufSize )
							{
								czFindTemp[iFoundindex] = NULL;
							}
						}
						szAdd.Format(_T("%s"), czFindTemp);
						arrInfo.Add(szAdd);
					}
				}
            }

			//! 입력된 폴더 내에 다른 폴더, 파일이 있는지 계속 검사를 진행
            if ( !::FindNextFile(hFindHandle, &FindData) )
            {
                break;	//! 입력된 폴더 아래에 하위 폴더, 파일이 없으면 검색 중단
            }
        }
    }
    ::FindClose(hFindHandle);

	szFolderPath.ReleaseBuffer();

	return 1;
}

//! [기능] 폴더 하위의 파일을 모두 복사
//! [입력값] szFolderPath_Source : 원본 파일이 있는 폴더의 절대 경로, 
//!	         szFolderPath_Dest : 복사하려는 목적 폴더의 절대 경로
//! [반환값] 정상적으로 작동하면 숫자 1을 반환하고, 오류가 발생하면 음수를 반환한다. 
int CopyFiles_In_Folder(CString szFolderPath_Source, CString szFolderPath_Dest)
{
	if ( szFolderPath_Source.GetLength() <= 0 || szFolderPath_Dest.GetLength() <= 0 )
	{
		return -1;
	}
	if ( ::GetFileAttributes(szFolderPath_Source) == -1 )	//! 폴더가 없을 경우
	{
		return -2;
	}
	if ( ::GetFileAttributes(szFolderPath_Dest) == -1 )	//! 폴더가 없을 경우
	{
		return -2;
	}

	//! 절대 경로명 뒤에 "\\" 문자가 없으면 추가한다. 
	if ( szFolderPath_Source.Right(1) != _T("\\") )
	{
		szFolderPath_Source += _T("\\");
	}
	if ( szFolderPath_Dest.Right(1) != _T("\\") )
	{
		szFolderPath_Dest += _T("\\");
	}
	//! 폴더 바로 아래의 모든 파일을 복사한다. 
	szFolderPath_Source += _T("*.*");

	CFileFind finder;
	CString szDestFilePath = _T("");

	BOOL bWorking = finder.FindFile(szFolderPath_Source);

	while(bWorking == TRUE)
	{
		bWorking = finder.FindNextFile();

		if ( finder.IsDots() )
		{
			continue;
		}
		if ( finder.IsDirectory() )
		{
			continue;
		}

		szDestFilePath = szFolderPath_Dest + finder.GetFileName();

		::CopyFile(finder.GetFilePath(), szDestFilePath, FALSE);
	}

	return 1;
}

//! [기능] 입력한 폴더 하위에 차례대로 폴더가 있는지 확인하고 없으면 생성한 뒤에 최종 폴더명을 반환
//! [입력값] szFolderPath : 부모 폴더의 절대 경로명, 
//!			 arrSubFolderName : 부모 폴더 아래의 하위 폴더의 이름 (index 0, index 1, ... 의 순서로 생성)
//! [반환값] 정상적으로 작동하면 숫자 1을 반환하고, 오류가 발생하면 음수를 반환한다. 
//!			 szLastFolderPath : 맨 마지막의 하위 폴더의 절대 경로명
int CreateSubFolders(CString szFolderPath, CStringArray &arrSubFolderName, CString &szLastFolderPath)
{
	szLastFolderPath = _T("");

	if ( szFolderPath.GetLength() <= 0 )
	{
		return -1;
	}
	if ( ::GetFileAttributes(szFolderPath) == -1 )	//! 폴더가 없을 경우
	{
		return -2;
	}
	int iSize_SubFolder = (int)(arrSubFolderName.GetSize());
	if ( iSize_SubFolder <= 0 )
	{
		return -3;
	}

	//! 절대 경로명 뒤에 "\\" 문자가 없으면 추가한다. 
	if ( szFolderPath.Right(1) != _T("\\") )
	{
		szFolderPath += _T("\\");
	}

	BOOL bCreateDirectory = FALSE;
	CString szSubFolderName = _T("");

	CString szSubFolderPath = szFolderPath;

	int i = 0;
	int iIndex_Failed = -1;
	for ( i = 0; i < iSize_SubFolder; i++ )
	{
		szSubFolderName = arrSubFolderName.GetAt(i);
		szSubFolderPath += szSubFolderName;
		if ( szSubFolderPath.Right(1) != _T("\\") )
		{
			szSubFolderPath += _T("\\");
		}

		if ( ::GetFileAttributes(szSubFolderPath) == -1 )	//! 폴더가 없을 경우
		{
			//! 폴더 생성
			bCreateDirectory = ::CreateDirectory(szSubFolderPath, NULL);
		}
		else
		{
			//! 이미 폴더가 있을 경우
			bCreateDirectory = TRUE;
		}

		if ( bCreateDirectory == FALSE )
		{
			iIndex_Failed = i;
			break;
		}
	}
	if ( iIndex_Failed >= 0 )
	{
		return -4;
	}

	szLastFolderPath = szSubFolderPath;

	return 1;
}

//! [기능] 년,월,일을 하위 폴더명으로 생성한다. 
int CreateSubFolders(CString szFolderPath, int iYear, int iMonth, int iDay, CString &szLastFolderPath)
{
	if ( iMonth < 0 || iMonth > 12 )
	{
		return -100;
	}
	if ( iDay <= 0 || iDay > 31 )
	{
		return -101;
	}

	int iRet = 0;

	CString szInput = _T("");
	CStringArray arrInput;
	arrInput.RemoveAll();
	arrInput.FreeExtra();

	szInput.Format(_T("%04d"), iYear);
	arrInput.Add(szInput);
	szInput.Format(_T("%02d"), iMonth);
	arrInput.Add(szInput);
	szInput.Format(_T("%02d"), iDay);
	arrInput.Add(szInput);

	iRet = CreateSubFolders(szFolderPath, arrInput, szLastFolderPath);

	arrInput.RemoveAll();
	arrInput.FreeExtra();

	return iRet;
}

//! [기능] 년,월,일,시간을 하위 폴더명으로 생성한다. 
int CreateSubFolders(CString szFolderPath, int iYear, int iMonth, int iDay, int iHour, CString &szLastFolderPath)
{
	if ( iMonth < 0 || iMonth > 12 )
	{
		return -100;
	}
	if ( iDay <= 0 || iDay > 31 )
	{
		return -101;
	}
	if ( iHour <= 0 || iHour > 24 )
	{
		return -102;
	}

	int iRet = 0;

	CString szInput = _T("");
	CStringArray arrInput;
	arrInput.RemoveAll();
	arrInput.FreeExtra();

	szInput.Format(_T("%04d"), iYear);
	arrInput.Add(szInput);
	szInput.Format(_T("%02d"), iMonth);
	arrInput.Add(szInput);
	szInput.Format(_T("%02d"), iDay);
	arrInput.Add(szInput);
	szInput.Format(_T("%02d"), iHour);
	arrInput.Add(szInput);

	iRet = CreateSubFolders(szFolderPath, arrInput, szLastFolderPath);

	arrInput.RemoveAll();
	arrInput.FreeExtra();

	return iRet;
}

//! [기능] 입력된 문자열이 정수인지 확인
//! [입력값] bMinusChk : true이면 문자열 맨 앞의 '-' 문자는 오류로 처리하지 않는다. 
//! [반환값] 문자열이 정수이면 true, 문자열의 길이가 0이면 true를 반환
bool IsValid_Integer(CString szInput, bool bMinusChk)
{
	int iLen = (int)(szInput.GetLength());
	if ( iLen <= 0 )
	{
		return true;
	}

	bool bRet = true;

	CString szTemp = _T("");
	szTemp = szInput;
	TCHAR *czTemp = szTemp.GetBuffer( iLen + 1 );

	for ( int i = 0; i < iLen; i++ )
	{
		if ( czTemp[i] < _T('0') || czTemp[i] > _T('9') )	
		{
			bRet = false;
			break;
		}
		else if ( czTemp[i] == _T('-') )
		{
			if ( bMinusChk == false || i != 0 )
			{
				bRet = false;
				break;
			}
		}
	}

	szTemp.ReleaseBuffer();

	return bRet;
}

//! [기능] 입력된 문자열이 실수인지 확인
//! [입력값] bMinusChk : true이면 문자열 맨 앞의 '-' 문자는 오류로 처리하지 않는다. 
//! [반환값] 문자열이 실수이면 true, 문자열의 길이가 0이면 true를 반환
bool IsValid_Double(CString szInput, bool bMinusChk)
{
	int iLen = (int)(szInput.GetLength());
	if ( iLen <= 0 )
	{
		return true;
	}

	bool bRet = true;
	int iPointCnt = 0;

	CString szTemp = _T("");
	szTemp = szInput;
	TCHAR *czTemp = szTemp.GetBuffer( iLen + 1 );

	for ( int i = 0; i < iLen; i++ )
	{
		if ( czTemp[i] == _T('.') )
		{
			iPointCnt++;
			continue;
		}
		else if ( czTemp[i] == _T('-') )
		{
			if ( bMinusChk == false || i != 0 )
			{
				bRet = false;
				break;
			}
		}
		else if ( czTemp[i] < _T('0') || czTemp[i] > _T('9') )	
		{			
			bRet = false;
			break;
		}
	}

	szTemp.ReleaseBuffer();

	if ( iPointCnt > 1 )
	{
		bRet = false;
	}

	return bRet;
}

//! [기능] 입력된 문자열이 지수인지 확인
//! [반환값] 문자열이 지수이면 true를 반환, 문자열의 길이가 0이면 true를 반환
bool IsValid_Exponential(CString szInput)
{
	int iLen = (int)(szInput.GetLength());
	if ( iLen <= 0 )
	{
		return true;
	}

	bool bRet = true;
	int iPointCnt = 0, iExpIndex = 0, iExpCnt = 0;

	CString szTemp = _T("");
	szTemp = szInput;
	TCHAR *czTemp = szTemp.GetBuffer( iLen + 1 );

	for ( int i = 0; i < iLen; i++ )
	{
		if ( czTemp[i] == _T('.') )
		{
			iPointCnt++;
			continue;
		}
		else if ( czTemp[i] == _T('-') )
		{
			if ( (i != 0) && (i != (iExpIndex + 1)) )
			{
				bRet = false;
				break;
			}
		}
		else if ( czTemp[i] < _T('0') || czTemp[i] > _T('9') )	
		{
			if ( czTemp[i] == _T('e') || czTemp[i] == _T('E') )
			{
				iExpIndex = i;
				iExpCnt++;
			}
			else
			{
				bRet = false;
				break;
			}
		}
	}

	szTemp.ReleaseBuffer();

	if ( iPointCnt > 1 )
	{
		bRet = false;
	}
	if ( iExpCnt > 1 )
	{
		bRet = false;
	}

	return bRet;
}

//! [기능] 입력된 문자열의 소수점 자리수를 알아 낸다.
//! [반환값] 문자열이 실수 일 때, 소수점 자리수를 반환
int GetDoublePointIndex(CString szInput)
{
	int iLen = (int)(szInput.GetLength());
	if ( iLen <= 0 )
	{
		return 0;
	}

	bool bFindPoint = false;
	int iCnt = 0;
	CString szTemp = _T("");
	szTemp = szInput;
	TCHAR *czTemp = szTemp.GetBuffer( iLen + 1 );

	for ( int i = (iLen - 1); i >= 0; i-- )
	{
		if ( czTemp[i] == _T('.') )
		{
			bFindPoint = true;
			break;
		}
		else
		{
			iCnt++;
		}
	}

	szTemp.ReleaseBuffer();

	if ( bFindPoint == false )
	{
		iCnt = 0;
	}

	return iCnt;
}

//! [기능] 문자열이 알파벳 문자, 숫자인지 확인한다. 
//! [반환값] 문자열이 문자, 숫자이면 true, 문자열의 길이가 0이면 true를 반환함
bool IsValid_AlphaNumeric(CString szInput)
{
	int iLen = (int)(szInput.GetLength());
	if ( iLen <= 0 )
	{
		return true;
	}

	bool bRet = true;

	CString szTemp = _T("");
	szTemp = szInput;
	TCHAR *czTemp = szTemp.GetBuffer( iLen + 1 );

	for ( int i = 0; i < iLen; i++ )
	{
		if ( czTemp[i] >= _T('0') || czTemp[i] <= _T('9') )	
		{
		}
		else if ( czTemp[i] >= _T('a') || czTemp[i] <= _T('z') )
		{
		}
		else if ( czTemp[i] >= _T('A') || czTemp[i] <= _T('Z') )
		{
		}
		else
		{
			bRet = false;
			break;
		}
	}

	szTemp.ReleaseBuffer();

	return bRet;
}

//! [기능] 문자열이 숫자(음수, 실수 포함, 지수형은 제외)인지를 확인
//! [반환값] 문자열이 숫자이면 true, 문자열의 길이가 0이면 true를 반환함
bool IsValid_Digit(CString szInput)
{
	CString szText;	
	TCHAR chTemp;
	bool bIsDigit = true;
	int  iIsPoint = 0;
	int  iIsMinus = 0;
	int  iStringLength = (int)(szInput.GetLength());
	
	for(int k = 0; k < iStringLength; k++)
	{
		chTemp = szInput.GetAt(k);

		if ( chTemp < _T('0') || chTemp > _T('9') )
		{
			if ( chTemp == _T('.') )
			{
				if ( k == 0  || k == (iStringLength - 1) || (iIsMinus > 0 && k == 1) )
				{
					//! '.'는 숫자의 처음과 끝에 있을 수 없으며, '-'가 있을 경우 그 바로 뒤에 있을 수 없음
					return false;	
				}
				else
				{
					++iIsPoint;
				}
			}
			else if ( chTemp == _T('-') )
			{
				if ( k != 0 )
				{
					return false;	//! '-'는 숫자의 맨 처음에만 있어야 함
				}
				else
				{
					++iIsMinus;
				}
			}
			else
			{
				bIsDigit = false;
			}
		}
	}

	if ( iIsPoint > 1 || iIsMinus > 1 )
	{
		bIsDigit = false;
	}

	return bIsDigit;
}

//! [기능] 입력한 경로에서 Driver 이름만을 추출한다. 
//! [입력값] szPath : 절대 경로명
//! [반환값] 드라이버 이름 문자열
CString GetDriveName(CString szPath)
{
	if ( szPath.GetLength() <= 0 )	//! 입력값 체크
	{
		return szPath;
	}

	TCHAR czPath[_MAX_PATH], drive[_MAX_DRIVE];
	_tcscpy_s(czPath, szPath);
	_tsplitpath_s( czPath, drive, _MAX_DRIVE, NULL, 0, NULL, 0, NULL, 0 );

	CString szReturnPath = _T("");
	szReturnPath.Format(_T("%s"), drive);

	return szReturnPath;
}

//! [기능] 입력한 경로에서 폴더 만의 경로를 추출한다. 
//! [입력값] szFilePath : 절대 경로명
//! [반환값] "{드라이버 명}:\\{폴더 경로}\\" 같은 폴더 만의 절대 경로명을 반환
CString GetFolderPath(CString szFilePath)
{
	if ( szFilePath.GetLength() <= 0 )	//! 입력값 체크
	{
		return szFilePath;
	}

	TCHAR czPath[_MAX_PATH], drive[_MAX_DRIVE], dir[_MAX_DIR];
	_tcscpy_s(czPath, szFilePath);
	_tsplitpath_s( czPath, drive, _MAX_DRIVE, dir, _MAX_DIR, NULL, 0, NULL, 0 );

	CString szReturnPath = _T("");
	szReturnPath.Format(_T("%s%s"), drive, dir);

	return szReturnPath;
}

//! [기능] 주어진 경로명에서 파일명 (확장자 포함)만을 추출
//! [입력값] szFilePath : 절대 경로명
CString GetFileNameExt(CString szFilePath)
{
	if ( szFilePath.GetLength() <= 0 )	//! 입력값 체크
	{
		return szFilePath;
	}

	TCHAR czPath[_MAX_PATH], drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];

	_tcscpy_s(czPath, szFilePath);
	_tsplitpath_s( czPath, drive, _MAX_DRIVE, dir, _MAX_DIR, fname, _MAX_FNAME, ext, _MAX_EXT );

	CString szReturnFileNameExt = _T("");
	szReturnFileNameExt.Format(_T("%s%s"), fname, ext);

	return szReturnFileNameExt;
}

//! 주어진 경로명에서 파일 확장자 만을 추출
//! [입력값] szFilePath : 절대 경로명
CString GetFileExt(CString szFilePath)
{
	if ( szFilePath.GetLength() <= 0 )	//! 입력값 체크
	{
		return szFilePath;
	}

	TCHAR czPath[_MAX_PATH], drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];

	_tcscpy_s(czPath, szFilePath);
	_tsplitpath_s( czPath, drive, _MAX_DRIVE, dir, _MAX_DIR, fname, _MAX_FNAME, ext, _MAX_EXT );

	CString szReturnFileExt = _T("");
	szReturnFileExt.Format(_T("%s"), ext);

	return szReturnFileExt;
}

//! [기능] 입력된 경로에 입력된 데이터로 Text 파일(txt, csv 같은 확장자를 가진 파일)을 저장한다. 
//! [입력값] szFilePath : 저장되는 파일의 절대 경로 (확장자까지 포함해야 한다), 
//!			 arrContents : 저장해야 할 문자열 데이터, 각 문자열 요소가 Text 파일에서의 1줄이다, 
//!						   CStringArray의 각 요소 문자열에 줄 바꿈 문자는 없어도 된다. 
//!			 bAppend : true이면 기존에 Text 파일이 있을 경우, 기존 파일의 뒤에 문자열 데이터를 추가한다. 
//!								기존의 파일이 없을 경우에는 새로 생성한다, 
//!					   false이면, 기존의 파일은 무조건 삭제하고, 새로운 파일을 생성한다. 
//! [반환값] 작업을 완료하면 숫자 1을 반환한다. 오류가 발생하면 음수나, 오류를 나타내는 정수값을 반환한다. 
int SaveTextFile(CString szFilePath, CStringArray &arrContents, bool bAppend)
{
	if ( szFilePath.GetLength() <= 0 )
	{
		return -1;
	}
	int iArrSize = (int)(arrContents.GetSize());
	if ( iArrSize <= 0 )	//! 저장해야 할 문자열이 없을 경우
	{
		return -2;
	}
	
	CString szFolderPath = GetFolderPath(szFilePath);
	if ( ::GetFileAttributes(szFolderPath) == -1 )	//! 파일이 저장되어야 할 폴더가 없을 경우
	{
		return -3;
	}

	UINT uFileOpenFlags;	//! 파일 속성 값

	if ( bAppend == false )
	{
		if ( ::GetFileAttributes(szFilePath) != -1 )	//! 기존 파일 삭제
		{
			::DeleteFile(szFilePath);
		}

		uFileOpenFlags = CFile::modeCreate | CFile::modeWrite | CFile::typeText | CFile::shareDenyWrite;
	}
	else
	{
		//! 파일 속성 값에 'CFile::modeNoTruncate' 추가
		uFileOpenFlags = CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText | CFile::shareDenyWrite;
	}

	try
	{
		CStdioFile SaveTextFile(szFilePath, uFileOpenFlags);	//! 파일 생성

		if ( bAppend == true )
		{
			SaveTextFile.SeekToEnd();	//! 맨 마지막 줄로 이동한다. 
		}

		int i = 0;
		CString szContent = _T(""), szWrite = _T("");

		for ( i = 0; i < iArrSize; i++ )
		{
			szContent = arrContents.GetAt(i);
			szWrite = szContent + _T("\n");		//! 줄 바꿈 문자 추가
			SaveTextFile.WriteString(szWrite);	//! 파일에 문자열을 저장한다. 
		}

		SaveTextFile.Close();
	}
	catch(CFileException *e)
	{
		int iErrorValue = e->m_cause;
		e->Delete();
		return iErrorValue;
	}

	return 1;
}

//! [기능] 입력된 경로에 입력된 데이터로 Text 파일(txt, csv 같은 확장자를 가진 파일)을 저장한다. 
//! [입력값] szFilePath : 저장되는 파일의 절대 경로 (확장자까지 포함해야 한다), 
//!			 szContent : 저장해야 할 문자열 데이터, 1줄에 해당하는 데이터를 입력한다. 끝에 줄 바꿈 문자는 없어도 된다. 
//!			 bAppend : true이면 기존에 Text 파일이 있을 경우, 기존 파일의 뒤에 문자열 데이터를 추가한다. 
//!								기존의 파일이 없을 경우에는 새로 생성한다, 
//!					   false이면, 기존의 파일은 무조건 삭제하고, 새로운 파일을 생성한다. 
//! [반환값] 작업을 완료하면 숫자 1을 반환한다. 오류가 발생하면 음수나, 오류를 나타내는 정수값을 반환한다.
int SaveTextFile(CString szFilePath, CString szContent, bool bAppend)
{
	if ( szFilePath.GetLength() <= 0 )
	{
		return -1;
	}

	CString szFolderPath = GetFolderPath(szFilePath);
	if ( ::GetFileAttributes(szFolderPath) == -1 )	//! 파일이 저장되어야 할 폴더가 없을 경우
	{
		return -2;
	}

	UINT uFileOpenFlags;	//! 파일 속성 값

	if ( bAppend == false )
	{
		if ( ::GetFileAttributes(szFilePath) != -1 )	//! 기존 파일 삭제
		{
			::DeleteFile(szFilePath);
		}

		uFileOpenFlags = CFile::modeCreate | CFile::modeWrite | CFile::typeText | CFile::shareDenyWrite;
	}
	else
	{
		//! 파일 속성 값에 'CFile::modeNoTruncate' 추가
		uFileOpenFlags = CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText | CFile::shareDenyWrite;
	}

	try
	{
		CStdioFile SaveTextFile(szFilePath, uFileOpenFlags);	//! 파일 생성

		if ( bAppend == true )
		{
			SaveTextFile.SeekToEnd();	//! 맨 마지막 줄로 이동한다. 
		}

		int i = 0;
		CString szWrite = _T("");

		szWrite = szContent + _T("\n");		//! 줄 바꿈 문자 추가
		SaveTextFile.WriteString(szWrite);	//! 파일에 문자열을 저장한다. 

		SaveTextFile.Close();
	}
	catch(CFileException *e)
	{
		int iErrorValue = e->m_cause;
		e->Delete();
		return iErrorValue;
	}

	return 1;
}

//! [기능] 입력된 경로에 입력된 데이터로 Text 파일(txt, csv 같은 확장자를 가진 파일)을 저장한다. 
//! [입력값] szFilePath : 저장되는 파일의 절대 경로 (확장자까지 포함해야 한다), 
//!			 pczContents : 저장해야 할 문자열 데이터, 2차원 배열이며, 1번째 index는 줄 번호를 의미한다. 문자열 버퍼가 Queue 형태로 운영된다고 가정한다.
//!						   pczContents의 각 문자열에 줄 바꿈 문자는 필요없다.
//!			 iStartIndex : 1번째 index에서의 시작 index, 
//!			 iSaveTextSize : 저장할 문자열의 줄 개수,  
//!			 iBufSize_1 : pczContents의 1번째 배열 포인터의 개수
//!			 bAppend : true이면 기존에 Text 파일이 있을 경우, 기존 파일의 뒤에 문자열 데이터를 추가한다. 
//!								기존의 파일이 없을 경우에는 새로 생성한다, 
//!					   false이면, 기존의 파일은 무조건 삭제하고, 새로운 파일을 생성한다. 
//! [반환값] 작업을 완료하면 숫자 1을 반환한다. 오류가 발생하면 음수나, 오류를 나타내는 정수값을 반환한다. 
int SaveTextFile(CString szFilePath, TCHAR **pczContents, int iStartIndex, int iSaveTextSize, int iBufSize_1, bool bAppend)
{
	if ( szFilePath.GetLength() <= 0 )
	{
		return -1;
	}

	//! 버퍼 유효성 검사
	if ( pczContents == NULL || iBufSize_1 <= 0 )
	{
		return -2;
	}
	//! 저장 index 검사
	if ( iStartIndex < 0 || iStartIndex >= iBufSize_1 || iSaveTextSize <= 0 || iSaveTextSize > iBufSize_1 )
	{
		return -3;
	}
		
	CString szFolderPath = GetFolderPath(szFilePath);
	if ( ::GetFileAttributes(szFolderPath) == -1 )	//! 파일이 저장되어야 할 폴더가 없을 경우
	{
		return -3;
	}

	UINT uFileOpenFlags;	//! 파일 속성 값

	if ( bAppend == false )
	{
		if ( ::GetFileAttributes(szFilePath) != -1 )	//! 기존 파일 삭제
		{
			::DeleteFile(szFilePath);
		}

		uFileOpenFlags = CFile::modeCreate | CFile::modeWrite | CFile::typeText | CFile::shareDenyWrite;
	}
	else
	{
		//! 파일 속성 값에 'CFile::modeNoTruncate' 추가
		uFileOpenFlags = CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText | CFile::shareDenyWrite;
	}

	try
	{
		CStdioFile SaveTextFile(szFilePath, uFileOpenFlags);	//! 파일 생성

		if ( bAppend == true )
		{
			SaveTextFile.SeekToEnd();	//! 맨 마지막 줄로 이동한다. 
		}

		int i = 0, iIndex = iStartIndex;
		CString szContent = _T(""), szWrite = _T("");

		for ( i = 0; i < iSaveTextSize; i++ )
		{
			if ( iIndex >= iBufSize_1 )	//! Queue형태의 문자열 버퍼가 끝에 다다랐을 때
			{
				iIndex = 0;
			}

			szContent.Format(_T("%s"), pczContents[iIndex++]);
			szWrite = szContent + _T("\n");		//! 줄 바꿈 문자 추가
			SaveTextFile.WriteString(szWrite);	//! 파일에 문자열을 저장한다. 
		}

		SaveTextFile.Close();
	}
	catch(CFileException *e)
	{
		int iErrorValue = e->m_cause;
		e->Delete();
		return iErrorValue;
	}

	return 1;
}

//! [기능] 입력된 경로의 Text 파일(txt, csv 같은 확장자를 가진 파일)을 읽어서 arrContents에 저장한다. 
//! [입력값] szFilePath : 저장되는 파일의 절대 경로
//! [반환값] 작업을 완료하면 숫자 1을 반환한다. 오류가 발생하면 음수나, 오류를 나타내는 정수값을 반환한다. 
//!			 arrContents : Text 파일의 문자열을 저장하여 반환한다. CStringArray 요소 1개가 Text 파일에서의 1줄이다. 
int ReadTextFile(CString szFilePath, CStringArray &arrContents)
{
	if ( szFilePath.GetLength() <= 0 )
	{
		return -1;
	}

	if ( ::GetFileAttributes(szFilePath) == -1 )	//! 파일이 없을 경우
	{
		return -2;
	}

	//! 기존 데이터 삭제
	arrContents.RemoveAll();
	arrContents.FreeExtra();

	try
	{
		CStdioFile ReadTextFile(szFilePath, CFile::modeRead | CFile::typeText | CFile::shareDenyNone);	//! 파일 열기

		CString szRead = _T("");

		while ( ReadTextFile.ReadString(szRead) )
		{
			arrContents.Add(szRead);
		}		

		ReadTextFile.Close();
	}
	catch(CFileException *e)
	{
		int iErrorValue = e->m_cause;
		e->Delete();
		return iErrorValue;
	}

	return 1;
}

//! [기능] 해당 int 값에 대한 에러 문자열을 반환
//! [입력값] iErrorValue : Error를 나타내는 CFileException의 m_cause 값
//! [반환값] 에러 문자열
CString GetErrorMsg_FileException(int iErrorValue)
{
	CString szReturn = _T("");

	switch(iErrorValue)
	{
	case CFileException::none:
		{
			szReturn = _T("No error ");
		}
		break;
	case CFileException::genericException:
		{
			szReturn = _T("An unspecified error occurred. ");
		}
		break;
	case CFileException::fileNotFound:
		{
			szReturn = _T("The file could not be located. ");
		}
		break;
	case CFileException::badPath:
		{
			szReturn = _T("All or part of the path is invalid. ");
		}
		break;
	case CFileException::tooManyOpenFiles:
		{
			szReturn = _T("The permitted number of open files was exceeded. ");
		}
		break;
	case CFileException::accessDenied:
		{
			szReturn = _T("The file could not be accessed. ");
		}
		break;
	case CFileException::invalidFile:
		{
			szReturn = _T("There was an attempt to use an invalid file handle. ");
		}
		break;
	case CFileException::removeCurrentDir:
		{
			szReturn = _T("The current working directory cannot be removed. ");
		}
		break;
	case CFileException::directoryFull:
		{
			szReturn = _T("There are no more directory entries. ");
		}
		break;
	case CFileException::badSeek:
		{
			szReturn = _T("There was an error trying to set the file pointer. ");
		}
		break;
	case CFileException::hardIO:
		{
			szReturn = _T("There was a hardware error. ");
		}
		break;
	case CFileException::sharingViolation:
		{
			szReturn = _T("A shared region was locked. ");
		}
		break;
	case CFileException::lockViolation:
		{
			szReturn = _T("There was an attempt to lock a region that was already locked. ");
		}
		break;
	case CFileException::diskFull:
		{
			szReturn = _T("The disk is full. ");
		}
		break;
	case CFileException::endOfFile:
		{
			szReturn = _T("The end of file was reached. ");
		}
		break;
	}

	return szReturn;
}

//! [기능] 문자열 파싱 함수
//! [함수 인자] Token : 파싱된 문자열이 순서대로 저장된다. 
//!				strOriginal : 입력된 문자열
//!				cpDelimiter : 파싱할 구분 문자 (예. UMAC에서 여러 개의 주소에서 값을 읽어들이면 0x0D로 구분되어 있다.)
void ParseString(CStringArray& Token, CString& szOriginal, TCHAR* cpDelimiter)
{
	int i = 0;
	int iOldPos = 0;
    Token.RemoveAll();
	Token.FreeExtra();

	int iOriginalLen = (int)(szOriginal.GetLength());

    for (i = 0; i < iOriginalLen; i++)
    {
        if (szOriginal.GetAt(i) == *cpDelimiter)
        {            
			Token.Add(szOriginal.Mid(iOldPos, i - iOldPos));
            iOldPos = i + 1;
        }
    }

	CString szLast = szOriginal.Mid(iOldPos, i - iOldPos);
	if ( szLast.GetLength() > 0 )
	{
		Token.Add(szLast);
	}
}

//! [기능] 문자열 파싱 함수
//! [함수 인자] Token : 파싱된 문자열이 순서대로 저장된다. 
//!				strOriginal : 입력된 문자열
//!				cDelimiter : 파싱할 구분 문자 (예. UMAC에서 여러 개의 주소에서 값을 읽어들이면 0x0D로 구분되어 있다.)
void ParseString(CStringArray& Token, CString& szOriginal, TCHAR cDelimiter)
{
	int i = 0;
	int iOldPos = 0;
    Token.RemoveAll();
	Token.FreeExtra();

	int iOriginalLen = (int)(szOriginal.GetLength());

    for (i = 0; i < iOriginalLen; i++)
    {
        if (szOriginal.GetAt(i) == cDelimiter)
        {            
			Token.Add(szOriginal.Mid(iOldPos, i - iOldPos));
            iOldPos = i + 1;
        }
    }

	CString szLast = szOriginal.Mid(iOldPos, i - iOldPos);
	if ( szLast.GetLength() > 0 )
	{
		Token.Add(szLast);
	}
}

//! [기능] 문자열 분리 함수, 문자열을 2개의 숫자로 분리한다.
//! [입력값] szInput : 입력된 문자열, 
//!			 cpDelimiter : 파싱할 구분 문자
//! [반환값] 작업이 완료되면 true를 반환한다. 오류가 발생하면 false를 반환한다. 
//!			 iFirst : 구분 문자 앞의 숫자, iSecond : 구분 문자 뒤의 숫자
bool GetSeparateNumber(CString szInput, int &iFirst, int &iSecond, TCHAR* cpDelimiter)
{
	int iLen = szInput.GetLength();
	if ( iLen <= 0 )
	{
		return false;
	}

	int iPos = szInput.Find(cpDelimiter);
	if ( iPos < 0 )	//! 구분 문자가 없을 때
	{
		return false;
	}

	if ( iPos == 0 )			//! 구분 문자가 맨 앞에 있을 때
	{
		return false;
	}
	if ( iPos == (iLen - 1) )	//! 구분 문자가 맨 뒤에 있을 때
	{
		return false;
	}

	CString szLeft = szInput.Left(iPos);
	CString szRight = szInput.Right(iLen - 1 - iPos);

	iFirst = _ttoi(szLeft);
	iSecond = _ttoi(szRight);

	return true;
}

//! [기능] 문자열 분리 함수, 문자열을 2개의 숫자로 분리한다.
//! [입력값] szInput : 입력된 문자열, 
//!			 cpDelimiter : 파싱할 구분 문자
//! [반환값] 작업이 완료되면 true를 반환한다. 오류가 발생하면 false를 반환한다. 
//!			 iFirst : 구분 문자 앞의 숫자, dbSecond : 구분 문자 뒤의 숫자
bool GetSeparateNumber(CString szInput, int &iFirst, double &dbSecond, TCHAR* cpDelimiter)
{
	int iLen = szInput.GetLength();
	if ( iLen <= 0 )
	{
		return false;
	}

	int iPos = szInput.Find(cpDelimiter);
	if ( iPos < 0 )	//! 구분 문자가 없을 때
	{
		return false;
	}

	if ( iPos == 0 )			//! 구분 문자가 맨 앞에 있을 때
	{
		return false;
	}
	if ( iPos == (iLen - 1) )	//! 구분 문자가 맨 뒤에 있을 때
	{
		return false;
	}

	CString szLeft = szInput.Left(iPos);
	CString szRight = szInput.Right(iLen - 1 - iPos);

	iFirst = _ttoi(szLeft);
	dbSecond = Convert_String_Double(szRight);

	return true;
}

//! [기능] 문자열 분리 함수, 문자열을 2개의 문자열로 분리한다.
//! [입력값] szInput : 입력된 문자열, 
//!			 cpDelimiter : 파싱할 구분 문자
//! [반환값] 작업이 완료되면 true를 반환한다. 오류가 발생하면 false를 반환한다. 
//!			 szFirst : 구분 문자 앞의 문자열, szSecond : 구분 문자 뒤의 문자열
bool GetSeparateString(CString szInput, CString &szFirst, CString &szSecond, TCHAR* cpDelimiter)
{
	int iLen = szInput.GetLength();
	if ( iLen <= 0 )
	{
		return false;
	}

	int iPos = szInput.Find(cpDelimiter);
	if ( iPos < 0 )	//! 구분 문자가 없을 때
	{
		szFirst = szInput;
		szSecond = _T("");
		return false;
	}

	if ( iPos == 0 )			//! 구분 문자가 맨 앞에 있을 때
	{
		return false;
	}
	if ( iPos == (iLen - 1) )	//! 구분 문자가 맨 뒤에 있을 때
	{
		return false;
	}

	szFirst = szInput.Left(iPos);
	szSecond = szInput.Right(iLen - 1 - iPos);

	return true;
}

#include <math.h>	//! pow, floor 함수 때문에 필요하다. 

//! [기능] 소수점 반올림 함수
//! [함수 인자] dbInput : 입력할 실수값
//!				iResultMode : 0 이상의 정수 가능
//!							  (예. 1 : 소수점 2째 자리에서 반올림, 2 : 소수점 3째 자리에서 반올림)
//!	[반환값] 반올림된 실수값
double GetFloor(double dbInput, int iResultMode)
{
	double dbResult = 0.;

	double dbBase = pow(10., iResultMode);
	dbResult = floor(dbBase * (dbInput + (0.5 / dbBase))) / dbBase;

	return dbResult;
}

//! 문자열을 정수부와 소수점 자리 부분의 2개의 정수로 반환
bool GetInteger_From_Double(CString szInput, int &iInterger, int &iDecimalPoint)
{
	int iLen = szInput.GetLength();
	if ( iLen <= 0 )
	{
		return false;
	}

	CString szInteger = _T(""), szDecimalPoint = _T("");

	GetSeparateString(szInput, szInteger, szDecimalPoint, _T("."));

	szInteger.TrimLeft();
	szInteger.TrimRight();
	szDecimalPoint.TrimLeft();
	szDecimalPoint.TrimRight();

	if ( szInteger.GetLength() <= 0 )
	{
		iInterger = 0;
	}
	else
	{
		iInterger = _ttoi(szInteger);
	}

	if ( szDecimalPoint.GetLength() <= 0 )
	{
		iDecimalPoint = 0;
	}
	else
	{
		iDecimalPoint = _ttoi(szDecimalPoint);
	}

	return true;
}

//! 문자열을 정수부와 소수점 자리 부분의 실수로 반환
bool GetInteger_From_Double(CString szInput, int &iInterger, double &dbDecimalPoint)
{
	int iLen = szInput.GetLength();
	if ( iLen <= 0 )
	{
		return false;
	}

	CString szInteger = _T(""), szDecimalPoint = _T("");

	GetSeparateString(szInput, szInteger, szDecimalPoint, _T("."));

	szInteger.TrimLeft();
	szInteger.TrimRight();
	szDecimalPoint.TrimLeft();
	szDecimalPoint.TrimRight();

	if ( szInteger.GetLength() <= 0 )
	{
		iInterger = 0;
	}
	else
	{
		iInterger = _ttoi(szInteger);
	}

	if ( szDecimalPoint.GetLength() <= 0 )
	{
		dbDecimalPoint = 0.;
	}
	else
	{
		CString szTemp = _T("");
		szTemp.Format(_T("0.%s"), szDecimalPoint);
		dbDecimalPoint = Convert_String_Double(szTemp);
	}

	return true;
}

//! [기능] 실수를 입력된 소수점 자리수를 가진 문자열로 변환
//! [함수 인자] dbInput : 입력할 실수값, iPrecision : 소수점 자리수
CString GetStringFromDouble(double dbInput, int iPrecision)
{
	CString szReturn = _T("");
	if ( iPrecision < 0 )
	{
		iPrecision = 0;
	}
	CString szPrecision = _T("");
	szPrecision.Format(_T("%%.%dlf"), iPrecision);
	szReturn.Format(szPrecision, GetFloor(dbInput, iPrecision));
	return szReturn;
}

//! 입력된 szInput1 문자열에서 szInput2 문자열이 포함된 개수를 알아낸다. 
//! [함수 인자] szInput1 : 원본 문자열, szInput2 : 원본 문자열에서 찾아내려고 하는 문자열
//! [반환값] szInput1 문자열 안에서 szInput2 문자열의 개수
//!			 문자열의 길이가 '0'이거나, 해당 문자열이 원본 문자열에 없으면 '0'을 반환
int GetCount_String_In_String(CString szInput1, CString szInput2)
{
	int iRet = 0;

	int iLength_Input = szInput1.GetLength();

	if ( iLength_Input <= 0 )
	{
		return 0;
	}
	if ( szInput2.GetLength() <= 0 )
	{
		return 0;
	}

	int iIndex_Start = 0;
	int iIndex_Ret_Start = 0;

	while(1)
	{
		if ( iIndex_Start > iLength_Input )
		{
			break;
		}

		iIndex_Ret_Start = szInput1.Find(szInput2, iIndex_Start);
		if ( iIndex_Ret_Start < 0 )
		{
			break;
		}

		iIndex_Start = iIndex_Ret_Start + 1;

		iRet++;
	}//! while(1)

	return iRet;
}

//! 입력한 정수값을 2개로 분리하여, 2개의 8 bit 16진수로 반환
void Separate_Hex_From_Integer_8bit(int iInput, int &iHigh, int &iLow)
{
	iLow  = iInput & 0xff;
	iHigh = (iInput >> 8) & 0xff;
}

//! 입력한 2개의 8 bit 16진수값을 합쳐서, 1개의 정수값을 반환
void Merge_Integer_From_Hex_8bit(int iHigh, int iLow, int &iOutput)
{
	iOutput =  iLow & 0xff;
	iOutput += (iHigh & 0xff) << 8;
}

//! 입력된 16진수 숫자에 해당하는 문자를 반환
TCHAR GetHexChar(int iInput)
{
	TCHAR cRet = '-';

	int iValue = iInput % 16;

	switch(iValue)
	{
	case 0:
		{
			cRet = '0';
		}
		break;
	case 1:
		{
			cRet = '1';
		}
		break;
	case 2:
		{
			cRet = '2';
		}
		break;
	case 3:
		{
			cRet = '3';
		}
		break;
	case 4:
		{
			cRet = '4';
		}
		break;
	case 5:
		{
			cRet = '5';
		}
		break;
	case 6:
		{
			cRet = '6';
		}
		break;
	case 7:
		{
			cRet = '7';
		}
		break;
	case 8:
		{
			cRet = '8';
		}
		break;
	case 9:
		{
			cRet = '9';
		}
		break;
	case 10:
		{
			cRet = 'A';
		}
		break;
	case 11:
		{
			cRet = 'B';
		}
		break;
	case 12:
		{
			cRet = 'C';
		}
		break;
	case 13:
		{
			cRet = 'D';
		}
		break;
	case 14:
		{
			cRet = 'E';
		}
		break;
	case 15:
		{
			cRet = 'F';
		}
		break;
	}

	return cRet;
}

//! 10진수를 16진수 숫자로 변경
long Convert_Decimal_To_Hex(int iInput_Decimal)
{
	//! 10진수를 16진수 문자열로 변환
	TCHAR czChar[100];
		
	int iCnt = 0;
	int iQuotient = 0;	//! 몫
	int iRemain = 0;	//! 나머지

	int iValue = iInput_Decimal;

	while(1)
	{
		iQuotient = iValue / 16;
		iRemain   = iValue % 16;

		czChar[iCnt++] = GetHexChar(iRemain);

		if ( iQuotient < 16 )
		{
			czChar[iCnt++] = GetHexChar(iQuotient);
			break;
		}

		iValue = iQuotient;
	}//! while(1)

	//! 입력한 문자열을 역순으로 변경한다. 
	int i = 0;
	TCHAR szNum[100];
	memset(szNum, 0, sizeof(szNum) * sizeof(TCHAR));
	for ( i = 0; i < iCnt; i++ )
	{
		_stprintf_s(szNum, _T("%s%c"), szNum, czChar[iCnt - i - 1]);
	}

	long lHex = HexString_to_Num(szNum);

	return lHex;
}

//! [기능] 입력된 문자열을 16진수 숫자로 변환한다. (예. 문자열 "0x16" -> 숫자 0x16)
//! [함수 인자] czHex : 문자열
//! [반환값] 16진수 정수값
//! [주의 사항] 입력된 문자열은 마지막에 NULL 문자를 가진 문자열이어야 한다. 
long HexString_to_Num(LPTSTR czHex)
{
	TCHAR szBuf[20];
	TCHAR *cpEnd;
	_stprintf_s(szBuf, _T("%s"), czHex);
	long lRet = _tcstol(szBuf, &cpEnd, 16);	//! 16진수 숫자로 변환
	return lRet;
}

long HexString_to_Num(CString szHex)
{
	int iLen = (int)(szHex.GetLength());
	if ( iLen <= 0 )
	{
		return -1;
	}
	TCHAR *czTemp = szHex.GetBuffer( iLen + 1 );
	long lRet = HexString_to_Num(czTemp);
	szHex.ReleaseBuffer();

	return lRet;
}

//! [기능] Hex -> Dec
//!        입력된 16진수 숫자를 10진수 숫자로 변경
int ConvertHexToDec(TCHAR *pszHex)
{
	int iDec = 0;
	int iTemp = 0;
    int iLen = 0;
    int i = 0;           

    iLen = _tcslen(pszHex);

    for (i = 0;  i < iLen ; i++)
    {
        iTemp = 0;                     

        if (*(pszHex+i) >= 'A' && *(pszHex+i) <='F')
            iTemp = (*(pszHex+i) - (TCHAR)'A' + 10);
        else
            iTemp = (*(pszHex+i) - (TCHAR)'0');

        iDec = iDec * 16 + iTemp;
    }

    return iDec;
}

//! [기능] 사각 영역의 기하학적 중심점의 좌표와 폭, 높이의 길이를 가지고, 사각 영역을 반환
//! [입력값] iCenterX : 사각 영역의 기하학적 중심점의 좌표 X,
//!			 iCenterY : 사각 영역의 기하학적 중심점의 좌표 Y, 
//!			 iWidth : 사각 영역의 폭, iHeight : 사각 영역의 높이
//! [반환값] 사각 영역
CRect makeP2R(int iCenterX, int iCenterY, int iWidth, int iHeight)
{
	CRect rcRet;

	rcRet.left = iCenterX - (iWidth >> 1);
	rcRet.top = iCenterY - (iHeight >> 1);
	rcRet.right = rcRet.left + iWidth;
	rcRet.bottom = rcRet.top + iHeight;

	return rcRet;
}

//! [기능] pWndofSub을 pWndToCenterOn의 중심에 위치 시킨다. 
//! [입력값] pWndToCenterOn : 기준 Window, pWndofSub : 위치를 설정하려는 Window
void CenterWindowOnOwner(CWnd* pWndToCenterOn, CWnd* pWndofSub, bool bFlag_Top)
{
	//! Window의 유효성 검사
	if ( pWndToCenterOn == NULL || pWndofSub == NULL )
	{
		return;
	}

	//! 각 Window의 사각 영역을 구한다. 
	CRect rectToCenterOn;
	pWndToCenterOn->GetWindowRect(&rectToCenterOn);

	CRect rectSubWindow;
	pWndofSub->GetWindowRect(&rectSubWindow);

	//! 중심으로 이동하기 위한 왼쪽 위의 좌표를 구한다. 
	int iXLeft = (int)((double)(rectToCenterOn.left + rectToCenterOn.right) / 2. - (double)(rectSubWindow.Width()) / 2.);
	int iYTop = (int)((double)(rectToCenterOn.top + rectToCenterOn.bottom) / 2. - (double)(rectSubWindow.Height()) / 2.);

	//! Window 위치 이동 (크기는 변경하지 않는다.)
	if ( bFlag_Top == true )
	{
		SetWindowPos(pWndofSub->GetSafeHwnd(), HWND_TOPMOST, iXLeft, iYTop, -1, -1, SWP_NOSIZE | SWP_NOACTIVATE);
	}
	else
	{
		SetWindowPos(pWndofSub->GetSafeHwnd(), NULL,		 iXLeft, iYTop, -1, -1, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
	}
	//pWndofSub->SetWindowPos(NULL, iXLeft, iYTop, -1, -1, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
}

//! [기능] 해당 객체를 화면 맨 위로 설정한다.
void Set_TopWindow(CWnd* pWnd)
{
	//! Window의 유효성 검사
	if ( pWnd == NULL )
	{
		return;
	}

	SetWindowPos(pWnd->GetSafeHwnd(), HWND_TOPMOST, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
}

//! [기능] HDD의 목록을 가져온다.
//! [반환값] 오류가 있을 경우에는 음수를 반환한다. arrDriveList에는 HDD의 목록이 들어 있다. 
//!			 HDD가 없으면 '0'을 반환한다. HDD가 발견되면 HDD의 개수를 반환한다. 
int GetHDDList(CStringArray &arrDriveList)
{
	arrDriveList.RemoveAll();
	arrDriveList.FreeExtra();

	//! 현재 PC의 드라이버 목록을 가져온다. 
	DWORD dwDrives = ::GetLogicalDrives();
	if ( dwDrives <= 0 )
	{
		return -1;
	}

	CString szDriverTemp = _T("");
	DWORD dwMask = 0x01;
	int i = 0;
	for ( i = 0; i < 32; i++ )
	{
		if ( dwDrives & (dwMask << i) )
		{
			szDriverTemp.Format(_T("%c:\\"), _T('A') + i);		//! 'A:\\ ~ Z:\\' 각각의 드라이버가 있는지 확인

			if ( GetDriveType(szDriverTemp) == DRIVE_FIXED )	//! HDD일 경우
			{
				arrDriveList.Add(szDriverTemp);
			}
			//! DRIVE_REMOVABLE : USB, DRIVE_CDROM : ODD
		}
	}

	int iSize = (int)(arrDriveList.GetSize());
	
	return iSize;
}

//! [기능] HDD의 남은 용량을 알아낸다. 
//! [입력값] 드라이버 이름 문자열 ("C:\\", "D:\\", ...)
//! [반환값] HDD의 남은 용량, 단위 MByte, 오류가 있을 경우에는 0을 반환한다. 
//!			 pdbTotalSize에 변수가 지정되어 있으면, HDD의 총 크기를 반환한다. 단위 MByte
double GetRemainSize_InHDD(CString szDriver, double *pdbTotalSize)
{
	if ( szDriver.GetLength() <= 0 )	//! 드라이버 이름 검사 
	{
		return 0.;
	}

	CString szDriverName = szDriver.Left(1);	//! 첫번째 글자만 가져온다. 

	//! 현재 PC의 드라이버 목록을 가져온다. 
	DWORD dwDrives = ::GetLogicalDrives();
	if ( dwDrives <= 0 )
	{
		return 0.;
	}

	bool bFind = false;
	CString szDriverTemp = _T("");
	DWORD dwMask = 0x01;
	int i = 0;
	for ( i = 0; i < 32; i++ )
	{
		if ( dwDrives & (dwMask << i) )
		{
			szDriverTemp.Format(_T("%c"), _T('A') + i);
			if ( szDriverName.CompareNoCase(szDriverTemp) == 0 )
			{
				bFind = true;
				break;
			}
		}
	}

	if ( bFind == false )	//! 입력한 드라이버가 현재 PC에 없을 때
	{
		return 0.;
	}

	//! HDD의 정보를 가져온다. 
	ULARGE_INTEGER i64FreeBytesToCaller, i64TotalBytes, i64FreeBytes;
	if ( ::GetDiskFreeSpaceEx(
			szDriverName + _T(":\\"), 
			(PULARGE_INTEGER)&i64FreeBytesToCaller, 
			(PULARGE_INTEGER)&i64TotalBytes, 
			(PULARGE_INTEGER)&i64FreeBytes) == FALSE )
	{
		return 0.;
	}

	if ( pdbTotalSize != NULL && i64TotalBytes.QuadPart != 0 )
	{
		*pdbTotalSize = (double)((DWORD)(i64TotalBytes.QuadPart / (1024 * 1024)));
	}

	if ( i64FreeBytesToCaller.QuadPart != 0 )
	{
		double dbMegaSize = (double)((DWORD)(i64FreeBytesToCaller.QuadPart / (1024 * 1024)));

		return dbMegaSize;
	}
	
	return 0.;
}

//! [기능] 입력한 리소스에서 문자열을 가져온다. 
//! [입력값] iUID : 리소스 ID, 화면 상의 Edit 컨트롤등의 ID값, pParentWnd : 부모 윈도우 포인터
//! [반환값] 오류가 있으면 음수를 반환, 오류가 없으면 1을 반환한다. 
//!				-1 : 부모 윈도우 포인터가 NULL이다. 
//!				-2 : 리소스 ID에 해당하는 컨트롤이 없다.
//!				-3 : 문자열의 길이가 0이다.
//!			 szRet : 반환되는 문자열
int GetString_FromUI(int iUID, CWnd* pParentWnd, CString &szRet)
{
	//! 입력값의 유효성 검사
	if ( pParentWnd == NULL )
	{
		return -1;
	}

	//! 리소스 ID에 해당하는 컨트롤의 유효성 검사
	CWnd* pWnd = NULL;
	pWnd = pParentWnd->GetDlgItem(iUID);
	if ( pWnd == NULL )
	{
		return -2;
	}

	//! 문자열을 가져온다. 
	pWnd->GetWindowText(szRet);

	//! 문자열의 길이를 검사
	szRet.TrimLeft();
	szRet.TrimRight();
	int iStringSize = (int)(szRet.GetLength());
	if ( iStringSize <= 0 )
	{
		return -3;
	}

	return 1;
}

//! [기능] 입력한 리소스에서 양의 정수형 값을 가져온다. 
//! [입력값] iUID : 리소스 ID, 화면 상의 Edit 컨트롤등의 ID값, pParentWnd : 부모 윈도우 포인터
//! [반환값] 리소스에 표시된 정수형 값, 오류가 있으면 음수를 반환
//!				-1 : 부모 윈도우 포인터가 NULL이다. 
//!				-2 : 리소스 ID에 해당하는 컨트롤이 없다.
//!				-3 : 문자열의 길이가 0이다.
//!				-4 : 문자열이 정수가 아니다. 
int GetIntegerValue_FromUI(int iUID, CWnd* pParentWnd)
{
	//! 입력값의 유효성 검사
	if ( pParentWnd == NULL )
	{
		return -1;
	}

	//! 리소스 ID에 해당하는 컨트롤의 유효성 검사
	CWnd* pWnd = NULL;
	pWnd = pParentWnd->GetDlgItem(iUID);
	if ( pWnd == NULL )
	{
		return -2;
	}

	//! 문자열을 가져온다. 
	CString szGetTemp = _T("");
	pWnd->GetWindowText(szGetTemp);

	//! 문자열의 길이를 검사
	szGetTemp.TrimLeft();
	szGetTemp.TrimRight();
	int iStringSize = (int)(szGetTemp.GetLength());
	if ( iStringSize <= 0 )
	{
		return -3;
	}

	//! 입력값이 정수인지 확인
	bool bDigit = true;
	int i = 0;
	for (i = 0; i < iStringSize; i++ )
	{
		if ( _istdigit( szGetTemp.GetAt(i) ) == 0 )
		{
			bDigit = false;
			break;
		}
	}
	if ( bDigit == false )
	{
		return -4;
	}

	//! 문자열 -> 숫자
	int iRet = _ttoi(szGetTemp);

	return iRet;
}

//! [기능] 입력한 리소스에서 실수형 값을 가져온다. 
//! [입력값] iUID : 리소스 ID, 화면 상의 Edit 컨트롤등의 ID값, pParentWnd : 부모 윈도우 포인터
//! [반환값] 오류가 있으면 음수를 반환, 오류가 없으면 1을 반환한다. 
//!				-1 : 부모 윈도우 포인터가 NULL이다. 
//!				-2 : 리소스 ID에 해당하는 컨트롤이 없다.
//!				-3 : 문자열의 길이가 0이다.
//!				-4 : 문자열이 실수값이 아니다. 
//!			 dbRet : 반환되는 실수값
int GetDoubleValue_FromUI(int iUID, CWnd* pParentWnd, double &dbRet)
{
	dbRet = -1.;

	//! 입력값의 유효성 검사
	if ( pParentWnd == NULL )
	{
		return -1;
	}

	//! 리소스 ID에 해당하는 컨트롤의 유효성 검사
	CWnd* pWnd = NULL;
	pWnd = pParentWnd->GetDlgItem(iUID);
	if ( pWnd == NULL )
	{
		return -2;
	}

	//! 문자열을 가져온다. 
	CString szGetTemp = _T("");
	pWnd->GetWindowText(szGetTemp);

	//! 문자열의 길이를 검사
	szGetTemp.TrimLeft();
	szGetTemp.TrimRight();
	int iStringSize = (int)(szGetTemp.GetLength());
	if ( iStringSize <= 0 )
	{
		return -3;
	}

	//! 입력값이 실수(지수형은 지원하지 않음)인지 확인
	bool bDigit = true;
	TCHAR tempCharacter;
	int i = 0, iDotCnt = 0;
	for (i = 0; i < iStringSize; i++ )
	{
		tempCharacter = szGetTemp.GetAt(i);

		if ( i == 0 )
		{
			if ( tempCharacter == _T('-') || tempCharacter == _T('+') )
			{
				continue;
			}
		}

		if ( tempCharacter == _T('.') )
		{
			iDotCnt++;
			continue;
		}

		if ( bDigit == true )
		{
			if ( _istdigit(tempCharacter) == 0 )
			{
				bDigit = false;			
			}
		}

		if ( bDigit == false )
		{
			break;
		}
	}
	if ( iDotCnt > 1 )
	{
		return -4;
	}
	if ( bDigit == false )
	{
		return -4;
	}

	//! 문자열 -> 숫자
	TCHAR *pEndString = _T("");
	double dbReturn = _tcstod(szGetTemp, &pEndString);

	dbRet = dbReturn;

	return 1;
}

//! [기능] 입력한 리소스에 문자열을 설정한다.
//! [입력값] iUID : 리소스 ID, pParentWnd : 부모 윈도우 포인터, szInput : 설정할 문자열
//! [반환값] 오류가 있으면 음수를 반환, 오류가 없으면 1을 반환한다. 
int SetString_to_UI(int iUID, CWnd* pParentWnd, CString szInput)
{
	//! 입력값의 유효성 검사
	if ( pParentWnd == NULL )
	{
		return -1;
	}

	//! 리소스 ID에 해당하는 컨트롤의 유효성 검사
	CWnd* pWnd = NULL;
	pWnd = pParentWnd->GetDlgItem(iUID);
	if ( pWnd == NULL )
	{
		return -2;
	}

	//! 문자열 설정
	pWnd->SetWindowText(szInput);

	return 1;
}

//! 입력한 리소스의 사각 영역을 가져온다.
int GetWindowRect_FromUI(int iUID, CWnd* pParentWnd, CRect &rcRet)
{
	rcRet.SetRectEmpty();

	//! 입력값의 유효성 검사
	if ( pParentWnd == NULL )
	{
		return -1;
	}

	//! 리소스 ID에 해당하는 컨트롤의 유효성 검사
	CWnd* pWnd = NULL;
	pWnd = pParentWnd->GetDlgItem(iUID);
	if ( pWnd == NULL )
	{
		return -2;
	}

	pWnd->GetWindowRect(&rcRet);

	return 1;
}

//! 입력한 리소스의 사각 영역을 가져온다.
int GetClientRect_FromUI(int iUID, CWnd* pParentWnd, CRect &rcRet)
{
	rcRet.SetRectEmpty();

	//! 입력값의 유효성 검사
	if ( pParentWnd == NULL )
	{
		return -1;
	}

	//! 리소스 ID에 해당하는 컨트롤의 유효성 검사
	CWnd* pWnd = NULL;
	pWnd = pParentWnd->GetDlgItem(iUID);
	if ( pWnd == NULL )
	{
		return -2;
	}

	pWnd->GetClientRect(&rcRet);

	return 1;
}

//! 입력한 리소스의 사각 영역을 설정한다. 
int SetRect_InCtrl(int iUID, CWnd* pParentWnd, CRect rcInput)
{
	//! 입력값의 유효성 검사
	if ( pParentWnd == NULL )
	{
		return -1;
	}

	//! 리소스 ID에 해당하는 컨트롤의 유효성 검사
	CWnd* pWnd = NULL;
	pWnd = pParentWnd->GetDlgItem(iUID);
	if ( pWnd == NULL )
	{
		return -2;
	}

	pWnd->MoveWindow(rcInput);

	return 1;
}

//! 입력한 리소스의 핸들값을 가져온다.
HWND GetHandle_FromUI(int iUID, CWnd* pParentWnd)
{
	//! 입력값의 유효성 검사
	if ( pParentWnd == NULL )
	{
		return NULL;
	}

	//! 리소스 ID에 해당하는 컨트롤의 유효성 검사
	CWnd* pWnd = NULL;
	pWnd = pParentWnd->GetDlgItem(iUID);
	if ( pWnd == NULL )
	{
		return NULL;
	}

	return pWnd->GetSafeHwnd();
}

//! [기능] 입력된 문자열을 실수형 숫자로 반환
//! [입력값] szInput : 문자열
//! [반환값] 실수형 숫자
double Convert_String_Double(CString szInput)
{
	TCHAR *pEndString = _T("");
	double dbReturn = _tcstod(szInput, &pEndString);
	return dbReturn;
}

//! [기능] 실수를 실수로 나눈 나머지를 반환
//! [입력값] dbInput : 입력값, dbDivide : 입력값을 나누어 주는 값
//! [반환값] 실수형 숫자, piMultiply : 입력값과 나누어 주는 값의 몫(정수배를 반환)
double GetDoubleModulus(double dbInput, double dbDivide, int *piMultiply)
{
	//! 나누어 주는 숫자가 너무 작으면 '0'을 반환
	if ( fabs(dbDivide) < 0.000001 )
	{
		return 0.;
	}

	double dbPortion = dbInput / dbDivide;
	int iPortion = (int)(dbPortion);
	double dbNewPortion = (double)iPortion;

	if ( piMultiply != NULL )
	{
		*piMultiply = iPortion;
	}

	double dbRet = dbInput - (dbNewPortion * dbDivide);
	return dbRet;
}

//! [기능] 해당 컨트롤에 포커스 설정
//! [입력값] iUID : 리소스 ID, 화면 상의 컨트롤등의 ID값, pParentWnd : 부모 윈도우 포인터
int SetFous_InCtrl(int iUID, CWnd* pParentWnd)
{
	//! 입력값의 유효성 검사
	if ( pParentWnd == NULL )
	{
		return -1;
	}

	//! 리소스 ID에 해당하는 컨트롤의 유효성 검사
	CWnd* pWnd = NULL;
	pWnd = pParentWnd->GetDlgItem(iUID);
	if ( pWnd == NULL )
	{
		return -2;
	}

	pWnd->SetFocus();

	return 1;
}

//! [기능] 해당 컨트롤을 눈에 보이게 하거나 숨기기
//! [입력값] iUID : 리소스 ID, 화면 상의 컨트롤등의 ID값, pParentWnd : 부모 윈도우 포인터
//!			 bVisible : true이면 해당 컨트롤을 눈에 보이게 하고, false이면 눈에 보이지 않게 한다. 
int SetVisibleState_InCtrl(int iUID, CWnd* pParentWnd, bool bVisible)
{
	//! 입력값의 유효성 검사
	if ( pParentWnd == NULL )
	{
		return -1;
	}

	//! 리소스 ID에 해당하는 컨트롤의 유효성 검사
	CWnd* pWnd = NULL;
	pWnd = pParentWnd->GetDlgItem(iUID);
	if ( pWnd == NULL )
	{
		return -2;
	}

	if ( bVisible == true )
	{
		pWnd->ShowWindow(SW_SHOW);
	}
	else
	{
		pWnd->ShowWindow(SW_HIDE);
	}

	return 1;
}

//! [기능] 해당 컨트롤의 눈에 보이는 여부
//! [입력값] iUID : 리소스 ID, 화면 상의 컨트롤등의 ID값, pParentWnd : 부모 윈도우 포인터
//!			 bVisible : true이면 해당 컨트롤을 눈에 보이고, false이면 눈에 보이지 않는다. 
int GetVisibleState_InCtrl(int iUID, CWnd* pParentWnd, bool &bGetVisible)
{
	//! 입력값의 유효성 검사
	if ( pParentWnd == NULL )
	{
		return -1;
	}

	//! 리소스 ID에 해당하는 컨트롤의 유효성 검사
	CWnd* pWnd = NULL;
	pWnd = pParentWnd->GetDlgItem(iUID);
	if ( pWnd == NULL )
	{
		return -2;
	}

	if ( pWnd->IsWindowVisible() == TRUE )
	{
		bGetVisible = true;
	}
	else
	{
		bGetVisible = false;
	}

	return 1;
}

//! [기능] 해당 컨트롤의 활성화/비활성화
//! [입력값] iUID : 리소스 ID, 화면 상의 컨트롤등의 ID값, pParentWnd : 부모 윈도우 포인터
//!			 bEnable : true이면 활성화, false이면 비활성화
int SetEnableState_InCtrl(int iUID, CWnd* pParentWnd, bool bEnable)
{
	//! 입력값의 유효성 검사
	if ( pParentWnd == NULL )
	{
		return -1;
	}

	//! 리소스 ID에 해당하는 컨트롤의 유효성 검사
	CWnd* pWnd = NULL;
	pWnd = pParentWnd->GetDlgItem(iUID);
	if ( pWnd == NULL )
	{
		return -2;
	}

	if ( bEnable == true )
	{
		pWnd->EnableWindow(TRUE);
	}
	else
	{
		pWnd->EnableWindow(FALSE);
	}

	return 1;
}

//! [기능] 해당 컨트롤의 활성화 여부
//! [입력값] iUID : 리소스 ID, 화면 상의 컨트롤등의 ID값, pParentWnd : 부모 윈도우 포인터
//!			 bGetEnable : true이면 활성화, false이면 비활성화
int GetEnableState_InCtrl(int iUID, CWnd* pParentWnd, bool &bGetEnable)
{
	//! 입력값의 유효성 검사
	if ( pParentWnd == NULL )
	{
		return -1;
	}

	//! 리소스 ID에 해당하는 컨트롤의 유효성 검사
	CWnd* pWnd = NULL;
	pWnd = pParentWnd->GetDlgItem(iUID);
	if ( pWnd == NULL )
	{
		return -2;
	}

	if ( pWnd->IsWindowEnabled() == TRUE )
	{
		bGetEnable = true;
	}
	else
	{
		bGetEnable = false;
	}

	return 1;
}

//! [기능] 해당 Button(또는 Check, Radio) 컨트롤의 선택 상태를 알아 낸다. 
//! [입력값] iUID : 리소스 ID, 화면 상의 컨트롤등의 ID값
//!			 pParentWnd : 부모 윈도우 포인터
//! [반환값] bGetCheck : 선택되어 있으면 true, 그렇지 않으면 false
int GetButtonCheckState_InCtrl(int iUID, CWnd* pParentWnd, bool &bGetCheck)
{
	bGetCheck = false;

	if ( pParentWnd == NULL )
	{
		return -1;
	}

	//! 리소스 ID에 해당하는 컨트롤의 유효성 검사
	CWnd* pWnd = NULL;
	pWnd = pParentWnd->GetDlgItem(iUID);
	if ( pWnd == NULL )
	{
		return -2;
	}

	UINT nChecked = pParentWnd->IsDlgButtonChecked(iUID);
	if ( nChecked != 0 )
	{
		bGetCheck = true;
	}
	else
	{
		bGetCheck = false;
	}

	return 1;
}

//! [기능] 해당 Button(또는 Check, Radio) 컨트롤의 선택 상태를 설정
//! [입력값] iUID : 리소스 ID, 화면 상의 컨트롤등의 ID값
//!			 pParentWnd : 부모 윈도우 포인터
//!			 bCheck : true이면 선택, false이면 선택 해제
int SetButtonCheckState_InCtrl(int iUID, CWnd* pParentWnd, bool bCheck)
{
	if ( pParentWnd == NULL )
	{
		return -1;
	}

	//! 리소스 ID에 해당하는 컨트롤의 유효성 검사
	CWnd* pWnd = NULL;
	pWnd = pParentWnd->GetDlgItem(iUID);
	if ( pWnd == NULL )
	{
		return -2;
	}

	if ( bCheck == true )
	{
		pParentWnd->SendDlgItemMessage(iUID, BM_SETCHECK, BST_CHECKED, 0);
	}
	else
	{
		pParentWnd->SendDlgItemMessage(iUID, BM_SETCHECK, BST_UNCHECKED, 0);
	}

	return 1;
}

//! [기능] 입력된 문자열 szText을 입력한 리소스 iUID를 가진 Edit 컨트롤에 표시한다. 
//! [입력값] iUID : 리소스 ID, 화면 상의 Edit 컨트롤등의 ID값, pParentWnd : 부모 윈도우 포인터, szText : 추가 문자열
//! [반환값] 작업을 완료하면 1을 반환, 오류가 있으면 음수를 반환
//!				-1 : 부모 윈도우 포인터가 NULL이다. 
//!				-2 : 리소스 ID에 해당하는 컨트롤이 없다.
//!				-3 : CEdit 형 변환 실패
int SetString_InEditCtrl(int iUID, CWnd* pParentWnd, CString szText)
{
	//! 입력값의 유효성 검사
	if ( pParentWnd == NULL )
	{
		return -1;
	}

	//! 리소스 ID에 해당하는 컨트롤의 유효성 검사
	CWnd* pWnd = NULL;
	pWnd = pParentWnd->GetDlgItem(iUID);
	if ( pWnd == NULL )
	{
		return -2;
	}

	CEdit *pEdit = (CEdit*)pWnd;
	if ( pEdit == NULL )
	{
		return -3;
	}

	pEdit->SetWindowText(szText);

	return 1;
}

//! [기능] 입력된 문자열 szAdd을 입력한 리소스 iUID를 가진 Edit 컨트롤에 추가한다. 
//! [입력값] iUID : 리소스 ID, 화면 상의 Edit 컨트롤등의 ID값, pParentWnd : 부모 윈도우 포인터, szAdd : 추가 문자열
//!			 bNextLine : true이면 입력 문자열 뒤로 줄 바꿈 문자를 추가한다. 
//!			 bReset : true이면 기존의 문자열을 삭제하고 새로 입력 시작한다. 
//! [반환값] 작업을 완료하면 1을 반환, 오류가 있으면 음수를 반환
//!				-1 : 부모 윈도우 포인터가 NULL이다. 
//!				-2 : 리소스 ID에 해당하는 컨트롤이 없다.
//!				-3 : CEdit 형 변환 실패
int AppendString_InEditCtrl(int iUID, CWnd* pParentWnd, CString szAdd, bool bNextLine, bool bReset)
{
	//! 입력값의 유효성 검사
	if ( pParentWnd == NULL )
	{
		return -1;
	}

	//! 리소스 ID에 해당하는 컨트롤의 유효성 검사
	CWnd* pWnd = NULL;
	pWnd = pParentWnd->GetDlgItem(iUID);
	if ( pWnd == NULL )
	{
		return -2;
	}

	CEdit *pEdit = (CEdit*)pWnd;
	if ( pEdit == NULL )
	{
		return -3;
	}

	//! 기존의 문자열 삭제, 새로 초기화
	if ( bReset == true )
	{
		pEdit->SetWindowText(_T(""));
	}

	CString szNew = szAdd;
	if ( bNextLine == true )
	{
		szNew += _T("\r\n");	//! 줄 바꿈 문자 추가 
	}
	
	//! 맨 마지막에 문자열 추가
	pEdit->SetSel(-1, -1);
	pEdit->ReplaceSel(szNew);

	//! 맨 마지막 줄로 이동한다. 
	int iLineSize = pEdit->GetLineCount();
	pEdit->LineScroll(iLineSize);

	return 1;
}

//! [기능] 'SetThreadAffinityMask' 함수의 Mask 인자값을 반환받는다. 
//! [입력값] piCPU_Use : int 배열, CPU를 사용하면 1, 사용하지 않으면 0, 
//!			             0 번 index가 1번 CPU를 가리킨다. 1번 index는 2번 CPU, ...
//!			 iSize : piCPU_Use 배열에서 사용할 데이터의 개수
//! [반환값] 'SetThreadAffinityMask' 함수의 Mask 인자값, 오류가 발생하면 0을 반환한다. 
DWORD GetMask_CPU_Affinity(int *piCPU_Use, int iSize)
{
	if ( piCPU_Use == NULL )
	{
		return 0;
	}

	//! 시스템의 사양을 알아낸다. 
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);

	//! CPU 개수와 버퍼 크기를 확인한다. 
	int iCPU_Size = (int)(sysInfo.dwNumberOfProcessors);
	if ( iSize <= 0 || iSize > iCPU_Size )
	{
		return 0;
	}

	int i = 0;
	DWORD dwRet = 0;

	iSize--;
	for ( i = iSize; i >= 0; i-- )
	{
		if ( piCPU_Use[i] != 0 )
		{
			dwRet = dwRet | (0x01 << (iSize - i));
		}
	}

	return dwRet;
}

//! Process (프로그램 전체)에서 사용하는 CPU를 설정한다.
//! [주의 사항] 
//!		1) Process에서 사용할 CPU는 하위의 모든 Thread가 사용할 CPU를 포함해야 한다. 
//!		2) Thread Affinity(친화도)는 항상 Process Affinity(친화도)의 서브셋이어야 한다.
//! [입력값]
//!     bFlag_All_CPU : true이면,  PC의 모든 CPU Core를 사용하는 것으로 설정한다. piCPU_Use, iSize 값은 사용하지 않는다.
//!                     false이면, iSize 크기의 piCPU_Use 버퍼의 데이터를 이용한다.
//!     piCPU_Use : 0 번 index가 1번 CPU를 가리킨다. 1번 index는 2번 CPU, ...
int SetProcessAffinity(bool bFlag_All_CPU, int *piCPU_Use, int iSize)
{
	if ( bFlag_All_CPU == false )
	{
		if ( piCPU_Use == NULL || iSize <= 0 )
		{
			return -1;
		}
	}

	//! 시스템의 사양을 알아낸다. 
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);	
	
	//! CPU 개수에 따라 사용할 CPU Core를 설정한다. 
	int iCPU_Size = (int)(sysInfo.dwNumberOfProcessors);
	if ( iCPU_Size <= 0 )
	{
		return -2;
	}

	int i = 0;	
	const int iBufSize_Process_CPU_Core = 100;

	//! GetMask_CPU_Affinity 함수에 입력할 버퍼
	int aiCPU[iBufSize_Process_CPU_Core];
	memset(aiCPU, 0, sizeof(aiCPU));

	//! 사용 가능한 CPU의 개수를 알아낸다.
	int iSize_Possible_CPU_Core = 0;
	if ( iCPU_Size >= iBufSize_Process_CPU_Core )
	{
		iSize_Possible_CPU_Core = iBufSize_Process_CPU_Core;
	}
	else
	{
		iSize_Possible_CPU_Core = iCPU_Size;
	}	

	if ( bFlag_All_CPU == false )
	{
		//! GetMask_CPU_Affinity 함수에 입력할 버퍼 설정
		//! 동시에 버퍼에서 설정된 사용 CPU 개수를 확인	
		int iCnt_Use_CPU = 0;
		for ( i = 0; i < iSize_Possible_CPU_Core; i++ )
		{
			if ( i >= iSize )
			{
				break;
			}

			if ( piCPU_Use[i] != 0 )
			{
				aiCPU[i] = 1;
				iCnt_Use_CPU++;
			}
		}

		if ( iCnt_Use_CPU <= 0 )
		{
			return -3;
		}
	}
	else
	{
		for ( i = 0; i < iSize_Possible_CPU_Core; i++ )
		{
			if ( i >= iBufSize_Process_CPU_Core )
			{
				break;
			}

			aiCPU[i] = 1;			
		}
	}

	DWORD dwMaskValue = GetMask_CPU_Affinity(aiCPU, iSize_Possible_CPU_Core);

	HANDLE hProcess = GetCurrentProcess();

	//! Process를 작동시킬 CPU를 선택한다.  
	DWORD dwRet = ::SetProcessAffinityMask(hProcess, dwMaskValue);
	if ( dwRet <= 0 )
	{
		DWORD dwError = GetLastError();

		//! The handle is invalid		
		if ( dwError == ERROR_INVALID_HANDLE )
		{
			return -4;
		}

		//! 'dwMaskValue' 입력값에 오류가 있음
		if ( dwError == ERROR_INVALID_PARAMETER )
		{
			return -5;
		}

		return -6;
	}

	return 1;
}

//! 정수형 값을 bool형 배열(크기가 16 이상)로 변환
bool Convert_Integer_To_BooleanBuffer(int iInput, bool *pabOutput, int iBufSize_Output)
{
	if ( pabOutput == NULL || iBufSize_Output < 16 )
	{
		return false;
	}

	int aiChk[16];
	aiChk[0]  = 0x0001;
	aiChk[1]  = 0x0002;
	aiChk[2]  = 0x0004;
	aiChk[3]  = 0x0008;
	aiChk[4]  = 0x0010;
	aiChk[5]  = 0x0020;
	aiChk[6]  = 0x0040;
	aiChk[7]  = 0x0080;
	aiChk[8]  = 0x0100;
	aiChk[9]  = 0x0200;
	aiChk[10] = 0x0400;
	aiChk[11] = 0x0800;
	aiChk[12] = 0x1000;
	aiChk[13] = 0x2000;
	aiChk[14] = 0x4000;
	aiChk[15] = 0x8000;

	int i = 0;
	for ( i = 0; i < 16; i++ )
	{
		if ( iInput & aiChk[i] )
		{
			pabOutput[i] = true;
		}
		else
		{
			pabOutput[i] = false;
		}
	}	

	return true;
}

//! bool형 배열(크기가 16 이상)을 정수형 값으로 변환
bool Convert_BooleanBuffer_To_Integer(bool *pabInput, int iBufSize_Input, int *piOutput)
{
	if ( pabInput == NULL || iBufSize_Input < 16 || piOutput == NULL )
	{
		return false;
	}

	int iRet = *piOutput;

	int aiChk[16];
	aiChk[0]  = 0x0001;
	aiChk[1]  = 0x0002;
	aiChk[2]  = 0x0004;
	aiChk[3]  = 0x0008;
	aiChk[4]  = 0x0010;
	aiChk[5]  = 0x0020;
	aiChk[6]  = 0x0040;
	aiChk[7]  = 0x0080;
	aiChk[8]  = 0x0100;
	aiChk[9]  = 0x0200;
	aiChk[10] = 0x0400;
	aiChk[11] = 0x0800;
	aiChk[12] = 0x1000;
	aiChk[13] = 0x2000;
	aiChk[14] = 0x4000;
	aiChk[15] = 0x8000;

	int i = 0;
	for ( i = 0; i < 16; i++ )
	{
		if ( pabInput[i] == true )
		{
			iRet |= aiChk[i];
		}
		else
		{
			iRet &= (~aiChk[i]);
		}
	}

	*piOutput = iRet;

	return true;
}

//! 16 bit 정수 2개를 합쳐서, 32 bit 정수 1개로 변환
//! [입력값] iInput1_Low_16bit, iInput2_High_16bit : 16 bit 정수 2개
//!			 iInput1_Low_16bit : 낮은 쪽 bit, iInput2_High_16bit : 높은 쪽 bit
//! [반환값] 32 bit 정수값
int Convert_Integer_From_16bit_To_32bit(int iInput1_Low_16bit, int iInput2_High_16bit)
{
	int iRet = 0;

	iRet = iInput1_Low_16bit & 0xffff;
	iRet += (iInput2_High_16bit & 0xffff) << 16;

	return iRet;
}

//! [입력값] bFlag_Round_Off : true이면 반올림을 한다.
int CalcMultiply(double dbInput1, double dbInput2, bool bFlag_Round_Off)
{
	int iRet = 0;
	double dbRet = 0.;
	dbRet = dbInput1 * dbInput2;
	if ( bFlag_Round_Off == true )
	{
		iRet = (int)(dbRet + 0.5);
	}
	else
	{
		iRet = (int)dbRet;
	}
	return iRet;
}

//! [입력값] bFlag_Round_Off : true이면 반올림을 한다.
int CalcMultiply(double dbInput1, int iInput2, bool bFlag_Round_Off)
{
	int iRet = 0;
	double dbRet = 0.;
	dbRet = dbInput1 * ((double)(iInput2));
	if ( bFlag_Round_Off == true )
	{
		iRet = (int)(dbRet + 0.5);
	}
	else
	{
		iRet = (int)dbRet;
	}
	return iRet;
}

//! [입력값] bFlag_Round_Off : true이면 반올림을 한다.
CRect CalcMultiply(double dbInput, CRect rcInput, bool bFlag_Round_Off)
{
	CRect rcRet;
	rcRet.left = CalcMultiply(dbInput, rcInput.left, bFlag_Round_Off);
	rcRet.top = CalcMultiply(dbInput, rcInput.top, bFlag_Round_Off);
	int iWidth = rcInput.Width();
	int iHeight = rcInput.Height();
	int iNewWidth = CalcMultiply(dbInput, iWidth, bFlag_Round_Off);
	int iNewHeight = CalcMultiply(dbInput, iHeight, bFlag_Round_Off);
	rcRet.right = rcRet.left + iNewWidth;
	rcRet.bottom = rcRet.top + iNewHeight;
	return rcRet;
}

//! [입력값] bFlag_Round_Off : true이면 반올림을 한다.
CRect CalcMultiply(double dbInputX, double dbInputY, CRect rcInput, bool bFlag_Round_Off)
{
	CRect rcRet;
	rcRet.left = CalcMultiply(dbInputX, rcInput.left, bFlag_Round_Off);
	rcRet.top = CalcMultiply(dbInputY, rcInput.top, bFlag_Round_Off);
	int iWidth = rcInput.Width();
	int iHeight = rcInput.Height();
	int iNewWidth = CalcMultiply(dbInputX, iWidth, bFlag_Round_Off);
	int iNewHeight = CalcMultiply(dbInputY, iHeight, bFlag_Round_Off);
	rcRet.right = rcRet.left + iNewWidth;
	rcRet.bottom = rcRet.top + iNewHeight;
	return rcRet;
}

//! [입력값] bFlag_Round_Off : true이면 반올림을 한다.
int CalcDivide(double dbInput1, double dbInput2, bool bFlag_Round_Off)
{
	if ( fabs(dbInput2) < 0.00001 )
	{
		return 0;
	}

	int iRet = 0;
	double dbRet = 0.;
	dbRet = dbInput1 / dbInput2;
	if ( bFlag_Round_Off == true )
	{
		iRet = (int)(dbRet + 0.5);
	}
	else
	{
		iRet = (int)dbRet;
	}
	return iRet;
}

//! [입력값] bFlag_Round_Off : true이면 반올림을 한다.
int CalcDivide(double dbInput1, int iInput2, bool bFlag_Round_Off)
{
	if ( iInput2 == 0 )
	{
		return 0;
	}

	int iRet = 0;
	double dbRet = 0.;
	dbRet = dbInput1 / ((double)(iInput2));
	if ( bFlag_Round_Off == true )
	{
		iRet = (int)(dbRet + 0.5);
	}
	else
	{
		iRet = (int)dbRet;
	}
	return iRet;
}

//! [입력값] bFlag_Round_Off : true이면 반올림을 한다.
int CalcDivide(int iInput1, double dbInput2, bool bFlag_Round_Off)
{
	if ( fabs(dbInput2) < 0.00001 )
	{
		return 0;
	}

	int iRet = 0;
	double dbRet = 0.;
	dbRet = ((double)(iInput1)) / dbInput2;
	if ( bFlag_Round_Off == true )
	{
		iRet = (int)(dbRet + 0.5);
	}
	else
	{
		iRet = (int)dbRet;
	}
	return iRet;
}

//! [입력값] bFlag_Round_Off : true이면 반올림을 한다.
CRect CalcDivide(double dbInput, CRect rcInput, bool bFlag_Round_Off)
{
	CRect rcRet;
	rcRet.left = CalcDivide(rcInput.left, dbInput, bFlag_Round_Off);
	rcRet.top = CalcDivide(rcInput.top, dbInput, bFlag_Round_Off);
	int iWidth = rcInput.Width();
	int iHeight = rcInput.Height();
	int iNewWidth = CalcDivide(iWidth, dbInput, bFlag_Round_Off);
	int iNewHeight = CalcDivide(iHeight, dbInput, bFlag_Round_Off);
	rcRet.right = rcRet.left + iNewWidth;
	rcRet.bottom = rcRet.top + iNewHeight;
	return rcRet;
}

//! [입력값] bFlag_Round_Off : true이면 반올림을 한다.
CRect CalcDivide(double dbInputX, double dbInputY, CRect rcInput, bool bFlag_Round_Off)
{
	CRect rcRet;
	rcRet.left = CalcDivide(rcInput.left, dbInputX, bFlag_Round_Off);
	rcRet.top = CalcDivide(rcInput.top, dbInputY, bFlag_Round_Off);
	int iWidth = rcInput.Width();
	int iHeight = rcInput.Height();
	int iNewWidth = CalcDivide(iWidth, dbInputX, bFlag_Round_Off);
	int iNewHeight = CalcDivide(iHeight, dbInputY, bFlag_Round_Off);
	rcRet.right = rcRet.left + iNewWidth;
	rcRet.bottom = rcRet.top + iNewHeight;
	return rcRet;
}

void Get_Valid_Point(CRect rcEntire, CPoint &ptInput)
{
	if ( ptInput.x < rcEntire.left )
	{
		ptInput.x = rcEntire.left;
	}
	if ( ptInput.x > rcEntire.right )
	{
		ptInput.x = rcEntire.right;
	}
	if ( ptInput.y < rcEntire.top )
	{
		ptInput.y = rcEntire.top;
	}
	if ( ptInput.y > rcEntire.bottom )
	{
		ptInput.y = rcEntire.bottom;
	}
}

void Get_Valid_Line(CRect rcEntire, CPoint &ptStart, CPoint &ptEnd)
{
	if ( ptStart.x < rcEntire.left )
	{
		ptStart.x = rcEntire.left;
	}
	if ( ptStart.x > rcEntire.right )
	{
		ptStart.x = rcEntire.right;
	}
	if ( ptStart.y < rcEntire.top )
	{
		ptStart.y = rcEntire.top;
	}
	if ( ptStart.y > rcEntire.bottom )
	{
		ptStart.y = rcEntire.bottom;
	}

	if ( ptEnd.x < rcEntire.left )
	{
		ptEnd.x = rcEntire.left;
	}
	if ( ptEnd.x > rcEntire.right )
	{
		ptEnd.x = rcEntire.right;
	}
	if ( ptEnd.y < rcEntire.top )
	{
		ptEnd.y = rcEntire.top;
	}
	if ( ptEnd.y > rcEntire.bottom )
	{
		ptEnd.y = rcEntire.bottom;
	}
}

//! 입력된 사각 영역을 전체 사각 영역을 넘지 않도록 교정하여 반환 
//! [입력값]
//!		rcEntire : 화면의 전체 사각 영역
//!		rcInputChk : 검증할 사각 영역
//!		bFlag_Base_Left : 검증할 사각 영역에서 왼쪽 변이 기준이면 true, 오른쪽 변이 기준이면 false
//!		bFlag_Base_Top : 검증할 사각 영역에서 위쪽 변이 기준이면 true, 아래쪽 변이 기준이면 false
CRect Get_Valid_Rect(CRect rcEntire, CRect rcInputChk, bool bFlag_Base_Left, bool bFlag_Base_Top)
{
	//CRect rcClient;
	//GetClientRect(rcClient);

	int iTempWidth = rcInputChk.Width();
	int iTempHeight = rcInputChk.Height();

	//! 사각 영역의 크기 제한
	if ( iTempWidth > rcEntire.Width() )
	{
		iTempWidth = rcEntire.Width();
		rcInputChk.right = rcInputChk.left + iTempWidth;
	}
	if ( iTempHeight > rcEntire.Height() )
	{
		iTempHeight = rcEntire.Height();
		rcInputChk.bottom = rcInputChk.top + iTempHeight;
	}
	if ( iTempWidth < 0 )
	{
		if ( bFlag_Base_Left == true )
		{
			rcInputChk.right = rcInputChk.left;
		}
		else
		{
			rcInputChk.left = rcInputChk.right;
		}
		
		iTempWidth = 0;
	}
	if ( iTempHeight < 0 )
	{
		if ( bFlag_Base_Top == true )
		{
			rcInputChk.bottom = rcInputChk.top;
		}
		else
		{
			rcInputChk.top = rcInputChk.bottom;
		}
		
		iTempHeight = 0;
	}

	//! 사각 영역의 위치 제한
	if ( rcInputChk.left < rcEntire.left )
	{
		rcInputChk.left = rcEntire.left;
		rcInputChk.right = rcInputChk.left + iTempWidth;
	}
	if ( rcInputChk.right > rcEntire.right )
	{
		rcInputChk.right = rcEntire.right;
		rcInputChk.left = rcInputChk.right - iTempWidth;
	}
	if ( rcInputChk.top < rcEntire.top )
	{
		rcInputChk.top = rcEntire.top;
		rcInputChk.bottom = rcInputChk.top + iTempHeight;
	}
	if ( rcInputChk.bottom > rcEntire.bottom )
	{
		rcInputChk.bottom = rcEntire.bottom;
		rcInputChk.top = rcInputChk.bottom - iTempHeight;
	}

	//! 사각 영역의 폭, 높이가 (-)값이 되지 않도록 한다.

	return rcInputChk;
}

//! 입력된 시각을 복사한다. (strTime_Dest = strTime_Source), 'strTime_Source'의 시각을 'strTime_Dest'에 입력한다. 
void CopySystemTime(SYSTEMTIME strTime_Source, SYSTEMTIME &strTime_Dest)
{
	strTime_Dest.wYear         = strTime_Source.wYear;
	strTime_Dest.wMonth        = strTime_Source.wMonth;
	strTime_Dest.wDay          = strTime_Source.wDay;
	strTime_Dest.wDayOfWeek    = strTime_Source.wDayOfWeek;
	strTime_Dest.wHour         = strTime_Source.wHour;
	strTime_Dest.wMinute       = strTime_Source.wMinute;
	strTime_Dest.wSecond       = strTime_Source.wSecond;
	strTime_Dest.wMilliseconds = strTime_Source.wMilliseconds;
}

//! [기능] 입력된 시각을 비교하여, 시간차를 반환한다.
//! [반환값] 
//!		1) strTime1이 strTime2보다 빠르면, 시간차를 음수로 반환한다. 
//!		2) strTime2이 strTime1보다 빠르면, 시간차를 양수로 반환한다. 
//!		3) 반환값의 단위는 msec이다.
//!		4) 반환값의 절대값이 '100000' 이면, 어느 쪽이 빠른지는 판별했으나, 시간차는 정확하지 못한 경우이다.
//!		5) 시각이 동일하면, '0'을 반환한다. 
int CompareSystemTime(SYSTEMTIME strTime1, SYSTEMTIME strTime2)
{
	int iRet = 0;

	FILETIME astrTempTime[2];
	LARGE_INTEGER astrTempInteger[2];

	_int64 iResult64 = 0;
	int iTimeDiff = 0;
	long lRet = 0;
	int iChk = 0;

	SystemTimeToFileTime( &strTime1, &(astrTempTime[0]) );
	SystemTimeToFileTime( &strTime2, &(astrTempTime[1]) );	

	lRet = CompareFileTime( &(astrTempTime[0]), &(astrTempTime[1]) );

	if ( lRet == 0 )
	{
		//! 2개의 시각이 동일하다. 
		iRet = 0;
	}
	else
	{
		memcpy( &(astrTempInteger[0]), &(astrTempTime[0]), sizeof(FILETIME) );
		memcpy( &(astrTempInteger[1]), &(astrTempTime[1]), sizeof(FILETIME) );

		_int64 iResult64 = (int)(astrTempInteger[0].QuadPart - astrTempInteger[1].QuadPart);

		iTimeDiff = (int)(iResult64 / 10000);

		iChk = iTimeDiff * lRet;

		if ( (iTimeDiff == 0) || (iChk < 0) )
		{
			//! 1) 시간차가 '0'이 나올 수 없으므로, 오류가 발생한 상태임
			//! 2) 시간차의 부호가 반대가 될 수 없으므로, 오류가 발생한 상태임

			if ( lRet < 0 )
			{
				iRet = -100000;
			}
			else
			{
				iRet = 100000;
			}
		}
		else
		{
			iRet = iTimeDiff;
		}
	}

	return iRet;
}

void checkMessage() 
{
	//MSG msg;
	//PeekMessage(&msg,::GetActiveWindow(),NULL,NULL,PM_REMOVE);
	//	//	PreTranslateMessage(&msg);
	//TranslateMessage(&msg);
	//DispatchMessage(&msg);
}

//! Idle Loop Processing (From MSDN 2010)
bool PeekAndPump()
{
	MSG msg;

    while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) 
	{
          if (!AfxGetApp()->PumpMessage()) 
		  {
               ::PostQuitMessage(0);
               return false;
          }
    }

	// let MFC do its idle processing
    LONG lIdle = 0;
    while (AfxGetApp()->OnIdle(lIdle++));

	// Perform some background processing here // using another call to OnIdle

    return true;
}

