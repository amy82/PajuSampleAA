
#include "stdafx.h"
#include "PcsUtil.h"

/* Wait Process **************************************************************/
// 2012.11.24 11:05 parkchas, pc마다 특성이 틀려서.. 할수없이 Gettick 사용.. cpu는 좀 올라가겠지만..
//
void DoEvent(int iMiliSecond)
{
	MSG msg ; 
	DWORD dwTickStart = GetTickCount();
	DWORD dwTickcur;

	// 계산 소비시간을 90%로 산정함.
//	for (int idx=0;idx<(int)(iMiliSecond * 1/10.0);idx++)
	while(TRUE)
	{
		if(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg) ; 
			::DispatchMessage(&msg) ; 
		}
		Sleep(1);	// 무한반복은 cpu를 너무 먹어요.. // By ckl [20140710]???
		dwTickcur = GetTickCount();
		if (dwTickcur-dwTickStart>=(DWORD)iMiliSecond)
		{
			break;
		}
	}
}

/* Make Full Directory *******************************************************/
BOOL WINAPI MakeFullDir(LPCTSTR lpszDirPath)
{
	int nPos = 0;
	char sTempDir[400] = {0,};
 
	while (lpszDirPath[nPos] != NULL)
	{
		if (lpszDirPath[nPos]=='\\' || lpszDirPath[nPos]=='/')
		{
			ZeroMemory(sTempDir,sizeof(sTempDir));
			memcpy(sTempDir,lpszDirPath,nPos);
			// 2013.02.07 parkchas, <CR><LF>제거.
			if (sTempDir[strlen(sTempDir)-1]==0x0D || sTempDir[strlen(sTempDir)-1]==0x0A) sTempDir[strlen(sTempDir)-1] = NULL;
			if (sTempDir[strlen(sTempDir)-1]==0x0D || sTempDir[strlen(sTempDir)-1]==0x0A) sTempDir[strlen(sTempDir)-1] = NULL;
			CreateDirectory(sTempDir, NULL);
		}
		nPos++;
	}

	return CreateDirectory(lpszDirPath, NULL);
}

/* String에서 특정 문자 위치 찾기 ******************************************************/
BOOL ReturnParameter(CString szOrigin, char cDelimeter, int nOrder, CString &szReturn)
{
	int iStartPos=0,iEndPos=0;
	CString szTarget;
	int i = 0;

	while(1)
	{
		iEndPos =  szOrigin.Find(cDelimeter,iStartPos);
		if (i == nOrder-1)
		{
			break;
		}
		else
		{
			if (iEndPos == -1)
			{
				return FALSE;
			}
			iStartPos = iEndPos+1;
			i++;
		}
	}
	if (iEndPos == -1)
	{
		iEndPos = szOrigin.GetLength();
	}
	szReturn.Format(_T("%s"),szOrigin.Mid(iStartPos,iEndPos - iStartPos));
	szReturn.TrimLeft();
	return TRUE;
}


/* FullPath에서 Path랑 FileName 분리. 현재는 Window Type만 지원 ***********************************/
void ReturnSeperatorFileName(LPCTSTR lpszFullPathName, LPCTSTR lpszPath, LPCTSTR lpszFileName)
{
	CString szFullPathName=_T("");
	CString szPath = _T("");
	CString szFileName = _T("");
	szFullPathName.Format(_T("%s"),lpszFullPathName);

	CString szTmp;
	CString szMakeDir;
	CFileFind fFind;
	int iIndex = 1;

	for(;;)
	{
		if (iIndex == 1)  /*It includes driver chanracter like C:\\*/
		{
			if (ReturnParameter(szFullPathName,'\\',iIndex++,szTmp))
			{
				szMakeDir = szTmp + "\\";
				continue;
			}
		}
		if (ReturnParameter(szFullPathName,'\\',iIndex++,szTmp))
		{
			szMakeDir += szTmp + "\\";
		}
		else break;
	}

	szFileName.Format("%s",szTmp);
	szPath.Format("%s",szFullPathName.Mid(0,szFullPathName.GetLength() - szFileName.GetLength() - 1));

	strcpy_s((PTCHAR)lpszPath,szPath.GetLength()+1,(LPCTSTR)szPath);
	strcpy_s((PTCHAR)lpszFileName,szFileName.GetLength()+1,(LPCTSTR)szFileName);
}
void ReturnSeperatorFileName(CString szFullPathName, CString &szPath, CString &szFileName)
{
	CString szTmp;
	CString szMakeDir;
	CFileFind fFind;
	int iIndex = 1;

	for(;;)
	{
		if (iIndex == 1)  /*It includes driver chanracter like C:\\*/
		{
			if (ReturnParameter(szFullPathName,'\\',iIndex++,szTmp))
			{
				szMakeDir = szTmp + "\\";
				continue;
			}
		}
		if (ReturnParameter(szFullPathName,'\\',iIndex++,szTmp))
		{
			szMakeDir += szTmp + "\\";
		}
		else break;
	}

	szFileName.Format("%s",szTmp);
	szPath.Format("%s",szFullPathName.Mid(0,szFullPathName.GetLength() - szFileName.GetLength() - 1));
}


/* 현재시각 문자열 생성 ************************************************************/
// Flag에 있는 값만 획득한다.
//	Flag = YMDhmsi (Y=YYYY, y=yy, i=milisecond)
void GetCurTimeString(PTCHAR lpszCurTime, LPCTSTR alpszFlag)
{
	// 초기화
	TCHAR	tcTemp[10];
	ZeroMemory(tcTemp,sizeof(tcTemp));

	// get current time
	SYSTEMTIME st;
	::GetLocalTime(&st);

	// get string time
	if (strchr(alpszFlag,'Y')) {sprintf_s(tcTemp,_T("%04d-"),st.wYear	 ); strcat_s(lpszCurTime,30,tcTemp);}
	if (strchr(alpszFlag,'y')) {sprintf_s(tcTemp,_T("%02d-"),st.wYear%100); strcat_s(lpszCurTime,30,tcTemp);}
	if (strchr(alpszFlag,'M')) {sprintf_s(tcTemp,_T("%02d-"),st.wMonth   ); strcat_s(lpszCurTime,30,tcTemp);}
	if (strchr(alpszFlag,'D')) {sprintf_s(tcTemp,_T("%02d" ),st.wDay     ); strcat_s(lpszCurTime,30,tcTemp);}
	if (strchr(alpszFlag,'h')) {sprintf_s(tcTemp,_T(" %02d"),st.wHour    ); strcat_s(lpszCurTime,30,tcTemp);}
	if (strchr(alpszFlag,'m')) {sprintf_s(tcTemp,_T(":%02d"),st.wMinute  ); strcat_s(lpszCurTime,30,tcTemp);}
	if (strchr(alpszFlag,'s')) {sprintf_s(tcTemp,_T(":%02d"),st.wSecond  ); strcat_s(lpszCurTime,30,tcTemp);}
	if (strchr(alpszFlag,'i')) {sprintf_s(tcTemp,_T(":%03d"),st.wMinute  ); strcat_s(lpszCurTime,30,tcTemp);}
}


/* Log File Write ************************************************************/
void _WriteLogFile(LPCTSTR apszLogMsg, LPCTSTR apszLogDir, LPCTSTR apszLogFile, UINT apuiOption)
{
	// 1. get current date time
	SYSTEMTIME st;	
	::GetLocalTime(&st);

	char sNowTickTime[100] = {0,};
	ZeroMemory(sNowTickTime,sizeof(sNowTickTime));
	sprintf_s(sNowTickTime,"%04d-%02d-%02d %02d:%02d:%02d:%03d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);

	// 2. LOG FILE PATH 설정
	char sLogDir[400] = {0,};
	char sTemp[100] = {0,};
	ZeroMemory(sLogDir,sizeof(sLogDir));
	ZeroMemory(sTemp,sizeof(sTemp));

	sprintf_s(sLogDir,"%s",apszLogDir);
	if (apuiOption & LOGFILE_DIR_YEAR)
	{
		sprintf_s(sTemp,"\\%04d",st.wYear);
		strcat_s(sLogDir,sTemp);
	} 
	if (apuiOption & LOGFILE_DIR_MONTH)
	{
		sprintf_s(sTemp,"\\%02d",st.wMonth);
		strcat_s(sLogDir,sTemp);
	} 
	if (apuiOption & LOGFILE_DIR_DAY)
	{
		sprintf_s(sTemp,"\\%02d",st.wDay);
		strcat_s(sLogDir,sTemp);
	} 

	// 3. directory 생성
	MakeSureDirectoryPathExists(sLogDir);


	// 4. log file name 설정
	char sLogFile[500] = {0,};
	ZeroMemory(sLogFile,sizeof(sLogFile));
	sprintf_s(sLogFile,"%s\\%s",sLogDir,apszLogFile);

	if (apuiOption & LOGFILE_FILE_FULLDAY)		// 파일명에 날짜 포함
	{
		sprintf_s(sTemp,"(%04d-%02d-%02d %02d).LOG",st.wYear,st.wMonth,st.wDay,st.wHour);
		strcat_s(sLogFile,sTemp);
	}
	else if ((apuiOption & LOGFILE_FILE_DATE)==0 && (apuiOption & LOGFILE_FILE_HOUR))		// 파일명에 시간 포함
	{
		sprintf_s(sTemp,"(%02d).LOG",st.wHour);
		strcat_s(sLogFile,sTemp);
	}
	else if ((apuiOption & LOGFILE_FILE_DATE) && (apuiOption & LOGFILE_FILE_HOUR)==0)		// 파일명에 시간 포함
	{
		sprintf_s(sTemp,"(%04d-%02d-%02d).LOG",st.wYear,st.wMonth,st.wDay);
		strcat_s(sLogFile,sTemp);
	}

	// 5. 메시지에 시간 포함
	char sMsg[8000] = {0,};												// 2012.11.08  JYH  1000 -> 8000 : 긴데이터 처리용
	ZeroMemory(sMsg,sizeof(sMsg));
	sprintf_s(sMsg,sizeof(sMsg)-1,"[%s] %s",sNowTickTime,apszLogMsg);	// 2012.11.08  JYH  999 -> sizeof(sMsg)-1 : 긴데이터 처리용

	// 6. 메시지 파일 기록
	CStdioFile file;
	CFileException fe;
	if (!file.Open(sLogFile, CFile::modeReadWrite, &fe))
	{
		// 1st, exists 검사
		if (fe.m_cause==CFileException::fileNotFound)
		{
			if (!file.Open(sLogFile, CFile::modeCreate|CFile::modeWrite, &fe)) 
			{
				return;
			}
		}
		// 2nd, if exists, wait, reopon
		else if (fe.m_cause==CFileException::accessDenied || fe.m_cause==CFileException::sharingViolation)
		{
			BOOL bOpened = FALSE;
			for (int i=0;i<10;i++)
			{
				DoEvent(10);
				if (file.Open(sLogFile, CFile::modeReadWrite, &fe))
				{
					bOpened = TRUE;
					break;
				}
			}
			if (!bOpened) return;
		} 
		else
		{
			UTCHAR(sLogFile2,500);
			sprintf_s(sLogFile2,"%s.log",sLogFile);
			if (!file.Open(sLogFile2, CFile::modeReadWrite, &fe))
			{
				if (!file.Open(sLogFile2, CFile::modeCreate|CFile::modeWrite, &fe)) 
				{
					return;
				}
			}
		}
	}

	file.SeekToEnd();
	file.WriteString(sMsg);
	file.WriteString(_T("\n"));
	file.Close();
}


//////////////////////////////////////////////////////////////////////////
// 시작프로그램 등록
BOOL SetRegistyStartProgram(BOOL bAutoExec, LPCSTR lpValueName, LPCSTR lpExeFileName)
{
	HKEY hKey;
	LONG lRes;
	if (bAutoExec)
	{
		if (lpValueName == NULL || lpExeFileName == NULL) return FALSE;

		lRes = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0L, KEY_WRITE, &hKey);
		if( lRes == ERROR_SUCCESS )
		{
			lRes = ::RegSetValueEx(hKey, lpValueName, 0, REG_SZ, (BYTE*)lpExeFileName, lstrlen(lpExeFileName)); 
			::RegCloseKey(hKey);

			if(lRes == ERROR_SUCCESS) 
			{
				//AfxMessageBox("성공적으로 시작 프로그램에서 등록됐습니다.");
			}
			else
			{
				//AfxMessageBox("Error");
				return FALSE;
			}
		}
		else if(lRes == ERROR_ACCESS_DENIED)
		{
			//AfxMessageBox("이 소프트웨어를 설치하기 위해서는 이 컴퓨터에 대한 충분한 권한이 있어야 합니다.");
			return FALSE;
		}
		else
		{
			//AfxMessageBox("Error");
			return FALSE;
		}
	}
	else 
	{
		lRes = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hKey);
		if( lRes != ERROR_SUCCESS )
		{
			return FALSE;
		}

		lRes = RegDeleteValue(hKey, lpValueName);      
		RegCloseKey(hKey);
		if(lRes == ERROR_SUCCESS) 
		{
			//AfxMessageBox("성공적으로 시작 프로그램에서 삭제됐습니다.");
		}
		else if(lRes == ERROR_FILE_NOT_FOUND)
		{
			//AfxMessageBox("프로그램이 시작 프로그램에 등록되어 있지 않습니다.");
			return FALSE;
		}
		else
		{
			//AfxMessageBox("시작 프로그램에서 삭제하지 못했습니다.");
			return FALSE;
		}
	}

	return TRUE;
}

// ===============================================================
//	4Byte 숫자 Binary를 LONG으로 변환시킴
long arr2long (byte* arr, long start) 
{
	long i = 0;
	long len = 4;
	long cnt = 0;
	byte* tmp = new byte[len];
	for (i = start; i < (start + len); i++) {
		tmp[cnt] = arr[i];
		cnt++;
	}
	long accum = 0;
	i = 0;
	for ( int shiftBy = 0; shiftBy < 32; shiftBy += 8 ) {
		accum |= ( (long)( tmp[i] & 0xff ) ) << shiftBy;
		i++;
	}

	delete[] tmp;
	return accum;
}


// ===============================================================
//	BITMAP Image size 계산시 width, height 다를 경우 dummy size 추가 계산 보정.
//
int BuildImageSize(int nWidth, int nHeight, int nBitCount)
{
	int nResult = 0;
	int nDummy = DetermineDummyValue(nBitCount, nWidth);

	switch (nBitCount)
	{
	case 1: if (nWidth >= 8) nResult = ((nWidth / 8) + nDummy) * nHeight; break;
	case 4: if (nWidth >= 2) nResult = ((nWidth / 2) + nDummy) * nHeight; break;
	case 8: nResult = (nWidth + nDummy) * nHeight; break;
	case 16: nResult = ((nWidth * 2) + nDummy) * nHeight; break;
	case 24: nResult = ((nWidth * 3) + nDummy) * nHeight; break;
	case 32: nResult = ((nWidth * 4) + nDummy) * nHeight; break;
	}

	return nResult;
}

int DetermineDummyValue(int nBitCount, int nWidth)
{
	int nDummy = 0;

	switch (nBitCount)
	{
	case 1: if (nWidth >= 8) nDummy = (nWidth / 8) % 4;	break;
	case 4:	if (nWidth >= 2) nDummy = (nWidth / 2) % 4;	break;
	case 8:	nDummy = nWidth % 4; break;
	case 16: nDummy = (nWidth * 2) % 4; break;
	case 24: nDummy = (nWidth * 3) % 4; break;
	case 32: nDummy = (nWidth * 4) % 4; break;
	}

	((4 - nDummy) == 4) ? nDummy = 0 : nDummy = 4 - nDummy;

	return nDummy;
}


//*----------------------------------------------------------------------------
//* \fn    	MakeSureDirectoryPathExists
//* \brief 	디렉토리의 존재유무 체크, 디렉토리 없으면 만들고, 파일 존재유무 검사
//*----------------------------------------------------------------------------	
BOOL WINAPI MakeSureDirectoryPathExists(LPCTSTR lpszDirPath)
{
	CString strDirPath = lpszDirPath;
	
	int nPos = 0;
   
	while((nPos = strDirPath.Find('\\', nPos+1)) != -1) 
	{
		CreateDirectory(strDirPath.Left(nPos), NULL);
	}

	return CreateDirectory(lpszDirPath, NULL);
}


//*----------------------------------------------------------------------------
//* \fn    	CStringToHexaBytes
//* \brief 	문자열을 Hexa Bytes 문자열로 변환한다. : FF => 0xFF (2bytes -> 1byte)
//*			Argument	pOutPut : 초기화된 상태로 넘겨주세요.
//*			Return Value : 변환된 문자열 길이
//*----------------------------------------------------------------------------	
int CStringToHexaBytes(CString szInput, PBYTE pOutput)
{
	//--> 문자열의 길이를 얻어서..
	int nStrLength = szInput.GetLength();
	
	int nLimit = 256 * 2;
	
	//--> 문자열 길이가 제한값보다 크면..오류 2번
	if( nStrLength >= nLimit )	return -2;
	

	BYTE byHigh, byLow;
	
	//--> 버퍼 입력 포지션..
	int nBufPos = 0;
	
	//--> 입력값을 구분해서.. 바이트 단위로 처리하기..
	for(int i=0; (i + 1)<nStrLength; i+=2 )
	{
		byHigh = byCode2AsciiValue( szInput[i] );
		byLow  = byCode2AsciiValue( szInput[i + 1] );
		
		pOutput[nBufPos++] = (byHigh << 4) | byLow;		
	}
	
	//--> 오류없음.
	int nNmg = nStrLength % 2;
	
	//--> 실제 변환된 바이트 수는 전체 데이터 갯수에 따라서.. 잘 생각해 보세여..
	//    왜..이런 연산식이..나오는지는..
	int nSendSu = ( nNmg <= 1 )  ?  (nStrLength / 2) : (INT)((nStrLength + 1) / 2);
	
	//--> 실제 변환된 바이트 수..넘기기..
	return nSendSu;
}

int CharStringToHexaBytes(char* pszInput, PBYTE pOutput)
{
	//--> 문자열의 길이를 얻어서..
	int nStrLength = (int)strlen(pszInput);
	int nLimit = 256 * 2;

	//--> 문자열 길이가 제한값보다 크면..오류 2번
	if( nStrLength >= nLimit )	return -2;


	BYTE byHigh, byLow;

	//--> 버퍼 입력 포지션..
	int nBufPos = 0;

	//--> 입력값을 구분해서.. 바이트 단위로 처리하기..
	for(int i=0; (i + 1)<nStrLength; i+=2 )
	{
		byHigh = byCode2AsciiValue( pszInput[i] );
		byLow  = byCode2AsciiValue( pszInput[i + 1] );

		pOutput[nBufPos++] = (byHigh << 4) | byLow;		
	}

	//--> 오류없음.
	int nNmg = nStrLength % 2;

	//--> 실제 변환된 바이트 수는 전체 데이터 갯수에 따라서.. 잘 생각해 보세여..
	//    왜..이런 연산식이..나오는지는..
	int nSendSu = ( nNmg <= 1 )  ?  (nStrLength / 2) : (INT)((nStrLength + 1) / 2);

	//--> 실제 변환된 바이트 수..넘기기..
	return nSendSu;
}


BYTE byCode2AsciiValue( char cData )
{
	BYTE byAsciiValue;

	//--> '0' ~ '9' => 0 ~ 9
	if( ('0' <= cData) && (cData <= '9') )
	{
		byAsciiValue = cData - '0';
	}	//--> 'A' ~ 'F' => 10 ~ 15
	else if( ('A' <= cData) && (cData <= 'F') )
	{
		byAsciiValue = (cData - 'A') + 10;
	}	//--> 'a' ~ 'f' => 10 ~ 15
	else if( ('a' <= cData) && (cData <= 'f') )
	{
		byAsciiValue = (cData - 'a') + 10;
	}
	else	//--> 잘못된 값을... 0 으로 처리
	{
		byAsciiValue = 0;
	}

	//--> 변환값을 리턴하죠..
	return byAsciiValue;
}


int AsciiToHex(char *pSrc, char* pDst, int iSrcLength, char cSeperator)// 정수를 HEX 스트링으로...
{
	if(iSrcLength > 2048) return 0;	// 2048 : size of buffer

	int i;
	char czTmp[3+1]={0, };
	int iSize = 2;

	if(cSeperator)
		iSize = 2+1;

	memset(pDst, 0, iSrcLength*iSize);

	for(i=0; i<iSrcLength; i++)
	{
		{
			if(cSeperator != 0)
			{
				sprintf_s(czTmp, "%02X%c", (BYTE) pSrc[i], cSeperator);
			}
			else
			{
				sprintf_s(czTmp, "%02X", (BYTE) pSrc[i]);
			}
		}

		memcpy(&pDst[i*iSize], czTmp, iSize);
	}


	if(cSeperator)
		pDst[iSrcLength*iSize - 1] = '\0';
	else
		pDst[iSrcLength*iSize] = '\0';

	return iSrcLength*iSize;
}

BOOL WINAPI FileExists(LPCTSTR szFileName)
{
	FILE *fp = NULL;
	//fp = fopen(szFileName,"r");
	fopen_s(&fp,szFileName,"r");
	if ( !fp )	// doesnt exist
	{		
		return FALSE;
	}

	// exists
	if(fp)		fclose(fp);
	return TRUE;
}



// http://groups.google.co.kr/group/comp.lang.c/msg/165f11c5f832321e?dmode=source

/*****************************************************************************
 *                                commify()                                  *
 *                                                                           *
 *  Commify a number, that is add commas between every third digit ahead of  *
 *  the decimal point.  Rounds off to abs(round) digits following the        *
 *  decimal point. Stores the results into the buf[] passed to the function  *
 *  and returns a pointer to it.  Uses the standard library function fcvt()  *
 *  to do the conversion from the double val to the string of digits.        *
 *                                                                           *
 *  2012.11.20 parkchas, val=0일 경우 . 안찍음.(if round=0)                  *
 *                                                                           *
 *****************************************************************************/
char *commify(double val, char *buf, int round) 
{
	static char *result = NULL;
	char *nmr = NULL;
	int dp=0, sign=0;

	result = buf;

	if (round < 0)                        /*  Be sure round-off is positive  */
		round = -round;

	//  nmr = fcvt(val, round, &dp, &sign);   /*  Convert number to a string     */
	//nmr = _fcvt(val, round, &dp, &sign);   /*  Convert number to a string     */
	char temp[MAX_PATH] = {0,};ZeroMemory(temp,sizeof(temp));
	nmr = temp;
	_fcvt_s(temp, 100,val, round, &dp, &sign);   /*  Convert number to a string     */

	if (sign)                             /*  Prefix minus sign if negative  */
		*buf++ = '-';

	if (dp <= 0)
	{                         /*  Check if number is less than 1 */
		if (dp < -round)                    /*  Set dp to max(dp, -round)      */
			dp = -round;
		*buf++ = '0';                       /*  Prefix with "0."               */
		if (round!=0)
		{
			*buf++ = '.';
		}
		while (dp++)                        /*  Write zeros following decimal  */
			*buf++ = '0';                     /*     point                       */
	}
	else {                                /*  Number is >= 1, commify it     */
		while (dp--){
			*buf++ = *nmr++;
			if (dp % 3 == 0)
				*buf++ = dp ? ',' : '.';
		}
	}

//	strcpy(buf, nmr);                     /*  Append rest of digits         */
	if (strlen(nmr))
	{
		strcpy_s(buf,strlen(nmr)+1, nmr);                     /*  Append rest of digits         */
	}
	return result;                        /*  following dec pt              */
}

// 2012.11.15 00:20 parkchas, 변형 생성
//	- cstring에서 자꾸 죽어. static char로 바꿀래.. 나중에 다시 고민.
char* CommaString(double rVal,int round) 
{
	//CString szReturn = "";

	static char	buf[100] = {0,};
	ZeroMemory(buf,sizeof(buf));
	commify(rVal, buf, round);

	return buf;
}


char* TrimRight( char * szAscii )
{
	int nLen = (int)strlen( szAscii );

	for (int idx=nLen-1; idx > 0; idx-- ) 
	{
		if ( szAscii[idx] == ' ' || szAscii[idx] == '\r' || szAscii[idx] == '\n' ) 
		{
			szAscii[idx] = NULL;
		}
		else 
		{
			break;
		}
	}

	return szAscii;
}

char* TrimLeft( char * szAscii )
{
	CString	szTemp(szAscii);
	szTemp.TrimLeft();
	sprintf_s(szAscii,szTemp.GetLength()+1,"%s",(LPCTSTR)szTemp);

	return szAscii;
}

// Original Data를 변형
char* Trim( char * szAscii )
{
	CString	szTemp(szAscii);
	szTemp.Trim();
	sprintf_s(szAscii,szTemp.GetLength()+1,"%s",(LPCTSTR)szTemp);

	return szAscii;
}

// Original Data는 변형없이 Return : 최대길이 260 (MAX_PATH)
// 2013.03.15 20:11 PARKCHAS, 동시 전송 메시지 대응위해 STATIC을 여러개 늘림.
char* TrimCopy( char * szAscii )
{
	CString	szTemp(szAscii);
	szTemp.Trim();

	static short	nCount = 0;
	nCount = (nCount+1) % 50;
	static char szReturn[50][MAX_PATH] = {0,};
	sprintf_s(szReturn[nCount],szTemp.GetLength()+1,"%s",(LPCTSTR)szTemp);

	return szReturn[nCount];
}


BOOL FileFolderCopyMove(CString strSrcPath, CString strDestPath, UINT wFunc, HWND hWnd)
{
	BOOL bRet = FALSE;

	SHFILEOPSTRUCT FileOp = {0};
	char szTemp[MAX_PATH]; ZeroMemory(szTemp,sizeof(szTemp));

	strcpy_s(szTemp, strSrcPath.GetLength()+1,(LPCSTR)strSrcPath);
	szTemp[strSrcPath.GetLength() + 1] = NULL;

	FileOp.hwnd = hWnd;
	FileOp.wFunc = wFunc;	// FO_COPY, FO_MOVE
	FileOp.pFrom = szTemp;
	FileOp.pTo = LPSTR(LPCTSTR(strDestPath));
	FileOp.fFlags = FOF_MULTIDESTFILES | FOF_NOCONFIRMATION | FOF_SILENT;
	FileOp.fAnyOperationsAborted = false;
	FileOp.hNameMappings = NULL;
	FileOp.lpszProgressTitle = NULL;

	if( SHFileOperation(&FileOp) == 0 )
		bRet = TRUE;

	return bRet;
}


int CharCount(CString szOrigin, char cDelimeter)
{
	CString data = szOrigin;
	return data.Remove(cDelimeter);
}


void CoordinateTrans( double sx, double sy, double *tx, double *ty, int type )
{
	switch (type) 
	{
	case 0:
		*tx = sx;
		*ty = sy;
		break;

	case 1:
		*tx = sx * -1.0;
		*ty = sy;
		break;

	case 2:
		*tx = sx * -1.0;
		*ty = sy * -1.0;
		break;

	case 3:
		*tx = sx;
		*ty = sy * -1.0;
		break;

	case 4:
		*tx = sy;
		*ty = sx;
		break;

	case 5:
		*tx = sy * -1.0;
		*ty = sx;
		break;

	case 6:
		*tx = sy * -1.0;
		*ty = sx * -1.0;
		break;

	case 7:
		*tx = sy;
		*ty = sx * -1.0;
		break;
	}
}


double ST2Second(SYSTEMTIME st)
{
	double time = st.wHour*3600.0 + st.wMinute*60.0 + st.wSecond + st.wMilliseconds/1000.0;
	return time;
}


bool LoadBMPIntoDC ( HDC hDC, LPCTSTR bmpfile )
{ 
	// Now we check if the supplied arguments are valid. If not we return false.
	if ( ( NULL == hDC  ) || ( NULL == bmpfile ) )
		return false; 
	
	// We then use the windows function LoadImage to load the bitmap into a Bitmap Handle: 	
	HANDLE hBmp = LoadImage ( NULL, bmpfile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE ); 
	
	// The first parameter is the instance that contains the image, 
	// but since we are loading it from a file and not from a resource, this is NULL. 
	// The second param is the filename. With the third one we tell the function to load a bitmap (it can also load icons and cursors). 
	// The next two params are desired width and height. 0 means that we want the actual bitmap size read from the file. 
	// Finally we have to tell the function that we want to load the bitmap from a file. 
	// To load an image from a resource file we would use the function like this:

// 	HANDLE hBmp = LoadImage ( hInstance, MAKEINTRESOURCE(imageid),	IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR ); 
	
	// where hInstance is the handle of the instance of the program (the HINSTANCE in WinMain), 
	// imageid is the identifier of the image in the resourcefile and LR_DEFAULTCOLOR is the standard do-nothing flag.
	// Now we do a quick check if the function returned a usable handle: 	
	
	if ( NULL == hBmp )		return false;   
	
	// At this point we have a valid image handle. Now we want to select it into a device context. 
	// Unfortunately it is not possible to select it directly into a visible DC, 
	// but only into a memory DC, so we have to create that first: 	
	
	HDC dcmem = CreateCompatibleDC ( NULL ); 
	
	// This function created a memory device context that is compatible to the screen. 
	// Now we can select the bitmap into it: 	
	
	if ( NULL == SelectObject ( dcmem, hBmp ) )
	{	
		// failed to load bitmap into device context
		DeleteDC ( dcmem ); 
		return false; 
	} 
	
	// If the function fails it deletes the memory dc and returns from the function.
	// If it was successful we can now blit the image from the memory dc to the visible dc we supplied as the first parameter to our LoadBMPIntoDC function.
	// To blit the entire image we first have to find out it's size though, 
	// but the WinAPI supplies us with an easy way to get the width and height of a bitmap handle: 	
	
	BITMAP bm;
	GetObject ( hBmp, sizeof(bm), &bm ); 
	
	// This function loads the information from the handle, which is not much more then a pointer, 
	// into a BITMAP structure that lets us access the width and height of the image, 
	// stored in bm.bmWidth and bm.bmHeight. 
	// With those values we can now blit the whole image to the visible DC: 	
	// and blit it to the visible dc

	if ( BitBlt ( hDC, 0, 0, bm.bmWidth, bm.bmHeight, dcmem, 0, 0, SRCCOPY ) == 0 )
	{	
		// failed the blit
		DeleteDC ( dcmem ); 
		return false; 
	} 
	
	// The function blits the entire image to the upper left of the visible DC and cleans up on failure.
	//	On success we can now see the image on the screen.
	//	Now we don't need the memory dc anymore and can finish the function: 	
	
	DeleteDC ( dcmem );  // clear up the memory dc	
	return true;
}


bool LoadBMPIntoDC ( HDC hDC, CRect rc, LPCTSTR bmpfile )
{ 
	// Now we check if the supplied arguments are valid. If not we return false.
	if ( ( NULL == hDC  ) || ( NULL == bmpfile ) )
		return false; 

	// We then use the windows function LoadImage to load the bitmap into a Bitmap Handle: 	
	HANDLE hBmp = LoadImage ( NULL, bmpfile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE ); 

	// The first parameter is the instance that contains the image, 
	// but since we are loading it from a file and not from a resource, this is NULL. 
	// The second param is the filename. With the third one we tell the function to load a bitmap (it can also load icons and cursors). 
	// The next two params are desired width and height. 0 means that we want the actual bitmap size read from the file. 
	// Finally we have to tell the function that we want to load the bitmap from a file. 
	// To load an image from a resource file we would use the function like this:

	// 	HANDLE hBmp = LoadImage ( hInstance, MAKEINTRESOURCE(imageid),	IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR ); 

	// where hInstance is the handle of the instance of the program (the HINSTANCE in WinMain), 
	// imageid is the identifier of the image in the resourcefile and LR_DEFAULTCOLOR is the standard do-nothing flag.
	// Now we do a quick check if the function returned a usable handle: 	

	if ( NULL == hBmp )		return false;   

	// At this point we have a valid image handle. Now we want to select it into a device context. 
	// Unfortunately it is not possible to select it directly into a visible DC, 
	// but only into a memory DC, so we have to create that first: 	

	HDC dcmem = CreateCompatibleDC ( NULL ); 

	// This function created a memory device context that is compatible to the screen. 
	// Now we can select the bitmap into it: 	

	if ( NULL == SelectObject ( dcmem, hBmp ) )
	{	
		// failed to load bitmap into device context
		DeleteDC ( dcmem ); 
		return false; 
	} 

	// If the function fails it deletes the memory dc and returns from the function.
	// If it was successful we can now blit the image from the memory dc to the visible dc we supplied as the first parameter to our LoadBMPIntoDC function.
	// To blit the entire image we first have to find out it's size though, 
	// but the WinAPI supplies us with an easy way to get the width and height of a bitmap handle: 	

	BITMAP bm;
	GetObject ( hBmp, sizeof(bm), &bm ); 

	// This function loads the information from the handle, which is not much more then a pointer, 
	// into a BITMAP structure that lets us access the width and height of the image, 
	// stored in bm.bmWidth and bm.bmHeight. 
	// With those values we can now blit the whole image to the visible DC: 	
	// and blit it to the visible dc

//	if ( BitBlt ( hDC, 0, 0, bm.bmWidth, bm.bmHeight, dcmem, 0, 0, SRCCOPY ) == 0 )
	if ( StretchBlt(hDC,rc.left,rc.top,rc.Width(),rc.Height(),dcmem,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY ) == 0 )
	{	
		// failed the blit
		DeleteDC ( dcmem ); 
		return false; 
	} 

	// The function blits the entire image to the upper left of the visible DC and cleans up on failure.
	//	On success we can now see the image on the screen.
	//	Now we don't need the memory dc anymore and can finish the function: 	

	DeleteDC ( dcmem );  // clear up the memory dc	
	return true;
}


// example
// int x, y;
// long size;
// BYTE* Buffer = LoadBMP24bit ( &x, &y, &size, L"test.bmp" );
BYTE* LoadBMP24bit ( int* width, int* height, long* size, LPCTSTR bmpfile )
{
	BITMAPFILEHEADER bmpheader;
	BITMAPINFOHEADER bmpinfo;
	DWORD bytesread; 

	// Note that we take three pointers as parameters for width, height and size, 
	// since we will return the image dimensions and size in these variables. 
	// bmpfile is of course the filename of the bitmap, and the return value of the function will be a pointer to the image data.
	//	First lets try to open the file: 	
	HANDLE file = CreateFile ( bmpfile , GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL );
	if ( NULL == file )
		return NULL; 
	// Just a quick note here: it's useful to write if ( NULL == file ) instead of if ( file == NULL ) to prevent bugs, 
	// since on accidently typing if ( file = NULL ) the compiler will not complain but assign NULL to the file handle. 
	// if ( NULL = file ) will spawn a compiler error, so you can prevent bugs easily this way. 
	//	Back to the topic: now we opened the file and can read the file header. 
	// On error we will close the file and return from the function. 	
	if ( ReadFile ( file, &bmpheader, sizeof ( BITMAPFILEHEADER ), &bytesread, NULL ) == false )
	{
		CloseHandle ( file );
		return NULL;
	} 
	// Now we can read the info header: 	
	if ( ReadFile ( file, &bmpinfo, sizeof ( BITMAPINFOHEADER ), &bytesread, NULL ) == false )
	{
		CloseHandle ( file );
		return NULL;
	} 
	// Since we are only going to load 24bit .bmps here we now do some checking of the header contents.
	//	First check if the file is actually a bitmap: 	
	if ( bmpheader.bfType != 'MB' )
	{
		CloseHandle ( file );
		return NULL;
	} 
	// check if it's uncompressed 	
	if ( bmpinfo.biCompression != BI_RGB )
	{
		CloseHandle ( file );
		return NULL;
	} 
	// and check if it's 24bit 	
	if ( bmpinfo.biBitCount != 24 )
	{
		CloseHandle ( file );
		return NULL;
	} 
	// When we are here we actually have a 24 bit bmp, 
	// so lets get its size and dimensions. 
	// We'll store them in the supplied variables: 	
	*width   = bmpinfo.biWidth;
	*height  = abs ( bmpinfo.biHeight );
	*size = bmpheader.bfSize - bmpheader.bfOffBits; 
	// To be independent of the type of info header, 
	// we compute the imaga data size as the whole file size minus the distance from file origin to start of image data.
	//	Now we create a buffer to hold the data 	
	BYTE* Buffer = new BYTE[ *size ]; 
	// Again, to be independent of info header version, we set the file pointer to the start of image data as told by the bfOffBits: 	
	SetFilePointer ( file, bmpheader.bfOffBits, NULL, FILE_BEGIN ); 
	// And now we can read in the data. We make sure that on error the Buffer gets deleted so we don't create memory leaks: 	
	if ( ReadFile ( file, Buffer, *size, &bytesread, NULL ) == false )
	{
		delete [] Buffer;
		CloseHandle ( file );
		return NULL;
	} 
	// and finish the function 	
	CloseHandle ( file );
	return Buffer;
}

// example
// RGBTriplet* buffer = (RGBTriplet*)ConvertBMPToRGBBuffer	( imagedata, width, height );
BYTE* ConvertBMPToRGBBuffer ( BYTE* Buffer, int width, int height )
{
	if ( ( NULL == Buffer ) || ( width == 0 ) || ( height == 0 ) )
		return NULL; 
	// Now we have to find out the number of bytes every scanline is padded with 	
	int padding = 0;
	int scanlinebytes = width * 3;
	while ( ( scanlinebytes + padding ) % 4 != 0 )
		padding++; 
	// At the end of the while loop padding will hold the number of padding bytes.
	//
	//	Now we can get the length in bytes of a padded scanline: 	
	int psw = scanlinebytes + padding; 
	// And construct the buffer to hold the output 	
	BYTE* newbuf = new BYTE[width*height*3]; 
	// The 3 stands for the number of bytes in one RGBTriplet of course.
	//
	//	Now comes the heart of the function: 	
	long bufpos = 0;   
	long newpos = 0;
	for ( int y = 0; y < height; y++ )
		for ( int x = 0; x < 3 * width; x+=3 )
		{
			newpos = y * 3 * width + x;     
			bufpos = ( height - y - 1 ) * psw + x;

			newbuf[newpos] = Buffer[bufpos + 2];       
			newbuf[newpos + 1] = Buffer[bufpos+1]; 
			newbuf[newpos + 2] = Buffer[bufpos];     
		} 

		// What exactly happens in this loop?
		// 			For clear code and some more speed we declare two variables that will hold the buffer indices.
		// 			The first for loop loops trough each scanline in the image data, the second loop hits every 3rd byte in a scanline, meaning the start of every RGB triplet(representing a pixel).
		// 			Then we compute the index the current pixel will have in the new RGB buffer as current scanline * imagewidth * numberofbytesperpixel + position of current pixel.
		// 			Next we compute the position we have to look at for the current pixel in the image data. The image was stored upside down in the .bmp, thus if we want to find a pixel color in the first line we have to look at the last scanline in the image data. Because we start indexing arrays with 0, the scanline to look for is imageheight - currentscanline (the y variable of the loop) - 1.
		// 			To get the exact pixel position, we have to multiply the scanline number by the amount of bytes per scanline in the buffer, which we already computed in psw. And finally we add the x position of the current pixel.
		// 			So now we have the position the pixel (x, y) will have in the new buffer in newpos, and the position the color values for this pixel are at in the image data is in bufpos.
		// 			Now we could just assign those values, but remember that the color values themselves are stored in BGR format in the image, and we want them in RGB format, so we have to swap the bytes at our position (red value) and the one at our poition+2 (blue value).
		// 			I hope that was halfway clear :)
		// 
		// 			Now we can finish the function: 	

		return newbuf;
}

bool SaveBMP24bit ( BYTE* Buffer, int width, int height, long paddedsize, LPCTSTR bmpfile )
{ 
	//Buffer is an array that contains the image data, width and height are the dimensions of the image to save, 
	//and paddedsize is the size of Buffer in bytes. bmpfile is the filename to save to.
	//First we declare the header structs and clear them: 	
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER info;
	memset ( &bmfh, 0, sizeof (BITMAPFILEHEADER ) );
	memset ( &info, 0, sizeof (BITMAPINFOHEADER ) ); 
	//Next we fill the file header with data: 	
	bmfh.bfType = 0x4d42;       // 0x4d42 = 'BM'
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;
	bmfh.bfSize = sizeof(BITMAPFILEHEADER) + 
		sizeof(BITMAPINFOHEADER) + paddedsize;
	bmfh.bfOffBits = 0x36; 
	//and the info header: 	
	info.biSize = sizeof(BITMAPINFOHEADER);
	info.biWidth = width;
	info.biHeight = height;
	info.biPlanes = 1;	
	info.biBitCount = 24;
	info.biCompression = BI_RGB;	
	info.biSizeImage = 0;
	info.biXPelsPerMeter = 0x0ec4;  
	info.biYPelsPerMeter = 0x0ec4;     
	info.biClrUsed = 0;	
	info.biClrImportant = 0;  
	//Some explanations: we want to save as a 24 bit RGB image, so we have to set biCompression to BI_RGB, biBitCount to 24 and biPlanes to 1.
	//	In 24 bit images we can set the biSizeImage value to 0 since it is ignored.
	//	For PelsPerMeter i simply use the values that Paint uses when saving bitmaps.
	//	Since we have no palette, we set the biClrUsed to 0, and biClrImportant being zero means that all colors are important.

	//	Now we can open a file to save to ( again i'm using windows functions but it doesnt matter what file I/O functions you use of course) 	
	HANDLE file = CreateFile ( bmpfile , GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
	if ( NULL == file )
	{
		CloseHandle ( file );
		return false;
	} 
	//Now we write the file header and info header: 	
	unsigned long bwritten;
	if ( WriteFile ( file, &bmfh, sizeof ( BITMAPFILEHEADER ), 
		&bwritten, NULL ) == false )
	{	
		CloseHandle ( file );
		return false;
	}

	if ( WriteFile ( file, &info, sizeof ( BITMAPINFOHEADER ), 
		&bwritten, NULL ) == false )
	{	
		CloseHandle ( file );
		return false;
	} 
	//and finally the image data: 	
	if ( WriteFile ( file, Buffer, paddedsize, &bwritten, NULL ) == false )
	{	
		CloseHandle ( file );
		return false;
	} 
	//Now we can close our function with 	
	CloseHandle ( file );
	return true;
}


//////////////////////////////////////////////////////////////////////////
//	File Size 획득
//
#include <fstream>
long GetFileSize(char* szFile)
{
	FILE *pFile = NULL;

	// get the file stream
	fopen_s( &pFile, szFile, "rb" );

	// set the file pointer to end of file
	fseek( pFile, 0, SEEK_END );

	// get the file size
	long lSize = ftell( pFile );

	// return the file pointer to begin of file if you want to read it
	// rewind( pFile );

	// close stream and release buffer
	if(pFile)		fclose( pFile );

	return lSize;
}
