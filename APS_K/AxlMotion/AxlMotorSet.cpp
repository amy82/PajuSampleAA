#include "StdAfx.h"
#include "AxlMotorSet.h"

extern bool bThreadTaskReadyRun;

 


CAxlMotorSet::CAxlMotorSet(void)
{
	int i = 0;
	for ( i = 0; i < MAX_MOTOR_NO; i++ )
	{
		m_bOrgFlag[i] = false;
	}

	bAxdConnect = true;
	//! Motor 설정 정보 저장 파일의 절대 경로 (Motion Controller Library에서 지원하는 기능)
	m_sMotionSettingFilePath = _T("C:/Program Files/EzSoftware UC/EzSoftware/MotionSetting.mot");
	//m_sMotionSettingFilePath = "C:\\Program Files\\EzSoftware RM\\EzSoftware\\MotionSetting.mot";
}

CAxlMotorSet::~CAxlMotorSet(void)
{
	Axl_Close();
}




bool CAxlMotorSet::InDIO(int moduleNo, int &inVal)
{
	DWORD ret = 0;
	DWORD val = 0x00;

#ifdef ON_LINE_MOTOR
	ret = AxdiReadInportDword(moduleNo, 0, &val);
#endif

	inVal = ~val & 0xFFFFFFFF;

	if(ret)
		return false;

	return true;
}


bool CAxlMotorSet::OutDIO(int moduleNo, int no)
{
	DWORD ret = 0;
	if(moduleNo == 1)
	{
		moduleNo = 2;
	}

#ifdef ON_LINE_MOTOR
	ret = AxdoWriteOutportDword(moduleNo+1, 0, ~no & 0xFFFFFFFF);
#endif

	if(ret)
	{
		Sleep(5);
		checkMessage();

		ret = AxdoWriteOutportDword(moduleNo+1, 0, ~no & 0xFFFFFFFF);

		if(ret)
		{
			CString tmpStr;
			sTempLang.LoadStringA(IDS_STRING888);
			sLangChange.Format(sTempLang, ret, no);
			tmpStr.Format(sLangChange);			//OUTPUT 신호 전송 실패 1-2
			errMsg2(Task.AutoFlag, tmpStr);

			return false;
		}
	}

	curOutDioByte[moduleNo][0] = no & 0xFF;
	curOutDioByte[moduleNo][1] = (no>>8) & 0xFF;
	curOutDioByte[moduleNo][2] = (no>>16) & 0xFF;
	curOutDioByte[moduleNo][3] = (no>>24) & 0xFF;

	return true;
}


bool CAxlMotorSet::OutDIO(int moduleNo, int chNo, int no)
{

	if(moduleNo<0 || moduleNo == 1 || moduleNo>=3)
	{
		CString tmpStr;
		sTempLang.LoadStringA(IDS_STRING497);
		sLangChange.Format(sTempLang, moduleNo);
		tmpStr.Format(sLangChange);	//DIO 출력 모듈 번호[%d]가 비정상입니다.
		errMsg2(Task.AutoFlag, tmpStr);

		return false;
	}

	if(chNo<0 || chNo>=4)
	{
		CString tmpStr;
		sTempLang.LoadStringA(IDS_STRING498);
		sLangChange.Format(sTempLang, moduleNo);
		tmpStr.Format(sLangChange);	//DIO 출력 체널 번호[%d]가 비정상입니다.
		errMsg2(Task.AutoFlag, tmpStr);

		return false;
	}

	DWORD ret = 0;

#ifdef ON_LINE_MOTOR
	ret = AxdoWriteOutportByte(moduleNo+1, chNo, (~no) & 0xFF);

	if(ret)
	{
		Sleep(5);
		checkMessage();

		ret = AxdoWriteOutportByte(moduleNo+1, chNo, (~no) & 0xFF);

		if(ret)
		{
			CString tmpStr;
			sTempLang.LoadStringA(IDS_STRING889);
			sLangChange.Format(sTempLang, ret, chNo, no);
			tmpStr.Format(sLangChange);	//OUTPUT 신호 전송 실패 2-2
			errMsg2(Task.AutoFlag, tmpStr);

			return false;
		}
	}
#endif

	curOutDioByte[moduleNo][chNo] = no & 0xFF;

	return true;
}

bool CAxlMotorSet::GetOutputIO(int moduleNo, int& val)
{
	val = 0;
	DWORD ret = 0;
	DWORD dwValue = 0;

#ifdef ON_LINE_MOTOR
	ret = AxdoReadOutportDword(moduleNo+1, 0, &dwValue);
#endif

	val = ~dwValue & 0xFFFFFFFF;

	if(ret)
		return false;

	return true;
}


bool CAxlMotorSet::Axl_Init()
{
	int i = 0;
	for ( i = 0; i < MAX_MOTOR_NO; i++ )
		m_bOrgFlag[i] = false;

	DWORD dwRet = 0;

#ifdef	ON_LINE_MOTOR
	dwRet = AxlOpen(0);		// 0 : 쓰레기값..
	if ( dwRet != AXT_RT_SUCCESS )
	{
		_tcscpy_s(m_szLogMsg, _T("모션 보드 초기화를 실패 하였습니다."));
		LogSave(m_szLogMsg);
		return false;
	}

	//! 등록된 AXL 사용가능 보드의 개수를 확인한다.
	long lBoardCounts = 0;
	AxlGetBoardCount(&lBoardCounts);
	if ( lBoardCounts <1)// <= 0 )
	{
		_tcscpy_s(m_szLogMsg, _T("모션 보드 인식을 실패 하였습니다."));
		LogSave(m_szLogMsg);
		return false;
	}

	TCHAR* pszPath = NULL;
	pszPath = m_sMotionSettingFilePath.GetBuffer( m_sMotionSettingFilePath.GetLength() + 0 );

	if ( IsExist_Path(m_sMotionSettingFilePath) == true )
	{
		//! 모든 축의 초기 값을 지정한 파일에서 읽어 설정한다. 
		if ( AxmMotLoadParaAll(pszPath) != AXT_RT_SUCCESS )
		{
			_tcscpy_s(m_szLogMsg, _T("모션 파라미터 파일이 없습니다."));
			LogSave(m_szLogMsg);
			return false;
		}
	}
	else
	{
		//! 모든 축의 초기 값을 파일에 저장 한다. 
		AxmMotSaveParaAll(pszPath);    
	}

	m_sMotionSettingFilePath.ReleaseBuffer(); 
#endif

	//! 초기 설정
	AmpDisableAll();
	int iRet_Axis = Axl_Axisconfig();
	
	int iRet_DIO  = Axl_DIO_Config();
	bool bRet_DIO_Reset = Axl_DIO_Reset();

	return true;
}




//! 모든 DIO 모듈에 초기값을 입력한다. 
bool CAxlMotorSet::Axl_DIO_Reset()
{
	//! 라이브러리가 초기화 되어 있는지 확인한다.

#ifdef	ON_LINE_MOTOR
	//! DIO 모듈이 있는지 확인한다.
	DWORD dwStatus = STATUS_NOTEXIST;
	AxdInfoIsDIOModule(&dwStatus);
	if(dwStatus != STATUS_EXIST)
	{
		_tcscpy_s(m_szLogMsg, _T("IO 입출력 모듈 인식을 실패 하였습니다."));
		LogSave(m_szLogMsg);
		return false;
	}

	// DIO모듈의 개수를 확인
	long lModuleCounts = 0, lCount;
	AxdInfoGetModuleCount(&lModuleCounts);

	// DIO모듈의 입출력 신호레벨을 Low로 초기 설정한다.
	for( int ModuleNo = 0; ModuleNo < lModuleCounts; ModuleNo++ )
	{
		lCount = 0;
		AxdInfoGetInputCount(ModuleNo, &lCount);
		if(lCount > 0)
		{
			AxdiLevelSetInportDword(ModuleNo, 0, 0); 
		}

		lCount = 0;
		AxdInfoGetOutputCount(ModuleNo, &lCount);
		if(lCount > 0)
		{
			AxdoLevelSetOutportDword(ModuleNo, 0, 0);
		}
	}
#endif

	return true;
}


//! 장비 전체의 Axis의 초기 설정을 진행한다. 
//! [주의 사항] 
//!    1) 반드시, 'Axl_Init' 함수의 'AxmMotLoadParaAll' 함수 호출 후에 이 함수를 호출하여야 한다. 
//!    2) PCI-R1604의 A4N, A5N서보드라이브의 경우(PM제외) Limit/Home/Servo On/Inposition의 Level을 설정 하실 수 없고 High또는 Low로 고정이 되어있습니다. 
//!		  Limit 센서의 A/B접을 바꾸고자 할때는 서보드라이브의 파라메터를 바꾸어야 합니다.
int CAxlMotorSet::Axl_Axisconfig() 
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

#ifdef	ON_LINE_MOTOR

	DWORD Status = 0;
	DWORD dwReturn = 0;

	//! 보드내에 인터럽트 사용을 해제 시킨다. (RTEX 지원 안함)
	AxlInterruptDisable();

	//! 시스템에 장착된 축 개수를 확인
	long lAxisCount = 0;
	AxmInfoGetAxisCount(&lAxisCount);

	if (lAxisCount != MAX_MOTOR_NO + 1)//임시
	{
		sLangChange.LoadStringA(IDS_STRING1231);	//모터 드라이브 개수 불일치.
		_stprintf_s(m_szLogMsg, sLangChange);
		pFrame->putListLog(m_szLogMsg);
		return -4;
	}

	int    iFailed = -1;

	for(int i=0; i<MAX_MOTOR_NO; i++)
	{

		dwReturn = AxmInfoIsInvalidAxisNo(i);
		if ( dwReturn != AXT_RT_SUCCESS )
		{
			sTempLang.LoadStringA(IDS_STRING161);
			sLangChange.Format(sTempLang, MotorName[i]);
			_stprintf_s(m_szLogMsg, sLangChange);
			pFrame->putListLog(m_szLogMsg);
			iFailed = i;
			continue;
		}


		dwReturn = AxmMotSetMoveUnitPerPulse(i, 1, 1);
		if ( dwReturn != AXT_RT_SUCCESS )
		{
			sTempLang.LoadStringA(IDS_STRING162);
			sLangChange.Format(sTempLang, MotorName[i]);
			_stprintf_s(m_szLogMsg, sLangChange);
			pFrame->putListLog(m_szLogMsg);
			iFailed = i;	
		}


		dwReturn = AxmMotSetMinVel(i, 1);
		if ( dwReturn != AXT_RT_SUCCESS )
		{
			sTempLang.LoadStringA(IDS_STRING163);
			sLangChange.Format(sTempLang, MotorName[i]);
			_stprintf_s(m_szLogMsg, sLangChange);
			pFrame->putListLog(m_szLogMsg);
			iFailed = i;			
		}

#ifdef MOTOR_ACC_TYPE_SEC
		dwReturn = AxmMotSetAccelUnit(i, SEC);	//UNIT_SEC2
#else
		dwReturn = AxmMotSetAccelUnit(i, UNIT_SEC2);	//UNIT_SEC2
#endif
		if ( dwReturn != AXT_RT_SUCCESS )
		{
			sTempLang.LoadStringA(IDS_STRING160);
			sLangChange.Format(sTempLang, MotorName[i]);
			_stprintf_s(m_szLogMsg, sLangChange);
			pFrame->putListLog(m_szLogMsg);
			iFailed = i;			
		}

		dwReturn = AxmMotSetProfileMode(i, ASYM_S_CURVE_MODE);
		if ( dwReturn != AXT_RT_SUCCESS )
		{
			sTempLang.LoadStringA(IDS_STRING158);
			sLangChange.Format(sTempLang, MotorName[i]);
			_stprintf_s(m_szLogMsg, sLangChange);
			pFrame->putListLog(m_szLogMsg);
			iFailed = i;
		}

		dwReturn = AxmMotSetAbsRelMode(i, POS_ABS_MODE);
		if ( dwReturn != AXT_RT_SUCCESS )
		{
			sTempLang.LoadStringA(IDS_STRING166);
			sLangChange.Format(sTempLang, MotorName[i]);
			_stprintf_s(m_szLogMsg, sLangChange);
			pFrame->putListLog(m_szLogMsg);
			iFailed = i;			
		}

		DWORD	dwHomLevel;

		dwReturn = AxmHomeSetSignalLevel(i, LOW);//기존
		dwReturn = AxmHomeGetSignalLevel(i, &dwHomLevel);
		if ( dwReturn != AXT_RT_SUCCESS )
		{
			sTempLang.LoadStringA(IDS_STRING155);
			sLangChange.Format(sTempLang, MotorName[i]);
			_stprintf_s(m_szLogMsg, sLangChange);
			pFrame->putListLog(m_szLogMsg);
			iFailed = i;			
		}

		DWORD	dwMaxVel; 
		dwMaxVel = AxmMotSetMaxVel(i, MOTOR_SPEED_MAX[i] * sysData.fMotorResol[i]);
		if ( dwReturn != AXT_RT_SUCCESS )
		{
			sTempLang.LoadStringA(IDS_STRING168);
			sLangChange.Format(sTempLang, MotorName[i]);
			_stprintf_s(m_szLogMsg, sLangChange);
			pFrame->putListLog(m_szLogMsg);
			iFailed = i;			
		}

		//! OneHighLowHigh      1펄스 방식, PULSE(Active High)  +방향(DIR=Low)  / -방향(DIR=High)
		//! OneHighHighLow      1펄스 방식, PULSE(Active High)  +방향(DIR=High) / -방향(DIR=Low)
		//! OneLowLowHigh       1펄스 방식, PULSE(Active Low)   +방향(DIR=Low)  / -방향(DIR=High)
		//! OneLowHighLow       1펄스 방식, PULSE(Active Low)   +방향(DIR=High) / -방향(DIR=Low)
		//! TwoCcwCwHigh        2펄스 방식, PULSE(CW:-방향)  DIR(CCW:+방향), Active High
		//! TwoCcwCwLow         2펄스 방식, PULSE(CW:-방향)  DIR(CCW:+방향), Active Low
		//! TwoCwCcwHigh        2펄스 방식, PULSE(CW:+방향)  DIR(CCW:-방향), Active High
		//! TwoCwCcwLow         2펄스 방식, PULSE(CW:+방향)  DIR(CCW:-방향), Active Low		

		if( MOTOR_TYPE[i] == STEPING)				// Step 모터 드라이브는 출력 방식, 리미트 설정 틀림.
		{

			dwReturn = AxmSignalSetInpos(i, UNUSED);
			if ( dwReturn != AXT_RT_SUCCESS )
			{
				sTempLang.LoadStringA(IDS_STRING156);
				sLangChange.Format(sTempLang, MotorName[i]);
				_stprintf_s(m_szLogMsg, sLangChange);
				pFrame->putListLog(m_szLogMsg);
				iFailed = i;
			}
	
			dwReturn = AxmMotSetPulseOutMethod(i, TwoCcwCwHigh);
			if ( dwReturn != AXT_RT_SUCCESS )
			{
				sTempLang.LoadStringA(IDS_STRING154);
				sLangChange.Format(sTempLang, MotorName[i]);
				_stprintf_s(m_szLogMsg, sLangChange);
				pFrame->putListLog(m_szLogMsg);
				iFailed = i;
			}

			dwReturn = AxmSignalSetStop(i, EMERGENCY_STOP, HIGH);
			if ( dwReturn != AXT_RT_SUCCESS )
			{
				sTempLang.LoadStringA(IDS_STRING164);
				sLangChange.Format(sTempLang, MotorName[i]);
				_stprintf_s(m_szLogMsg, sLangChange);
				pFrame->putListLog(m_szLogMsg);
				iFailed = i;			
			}
			dwReturn = AxmSignalSetLimit(i, EMERGENCY_STOP, LOW, LOW);//low 기존
			
			if ( dwReturn != AXT_RT_SUCCESS )
			{
				sTempLang.LoadStringA(IDS_STRING157);
				sLangChange.Format(sTempLang, MotorName[i]);
				_stprintf_s(m_szLogMsg, sLangChange);
				pFrame->putListLog(m_szLogMsg);
				iFailed = i;
			}

			dwReturn = AxmMotSetEncInputMethod(i, ObverseSqr4Mode);
			if ( dwReturn != AXT_RT_SUCCESS )
			{
				sTempLang.LoadStringA(IDS_STRING153);
				sLangChange.Format(sTempLang, MotorName[i]);
				_stprintf_s(m_szLogMsg, sLangChange);
				pFrame->putListLog(m_szLogMsg);
				iFailed = i;			
			}


			dwReturn = AxmSignalSetServoOnLevel(i, HIGH);
			if ( dwReturn != AXT_RT_SUCCESS )
			{
				sTempLang.LoadStringA(IDS_STRING159);
				sLangChange.Format(sTempLang, MotorName[i]);
				_stprintf_s(m_szLogMsg, sLangChange);
				pFrame->putListLog(m_szLogMsg);
				iFailed = i;
			}
		}
		else
		{
			dwReturn = AxmSignalSetInpos(i, HIGH);
			if ( dwReturn != AXT_RT_SUCCESS )
			{
				sTempLang.LoadStringA(IDS_STRING156);
				sLangChange.Format(sTempLang, MotorName[i]);
				_stprintf_s(m_szLogMsg, sLangChange);
				pFrame->putListLog(m_szLogMsg);
				iFailed = i;
			}

			dwReturn = AxmSignalSetStop(i, EMERGENCY_STOP, LOW);
			if ( dwReturn != AXT_RT_SUCCESS )
			{

				sTempLang.LoadStringA(IDS_STRING164);
				sLangChange.Format(sTempLang, MotorName[i]);
				_stprintf_s(m_szLogMsg, sLangChange);
				pFrame->putListLog(m_szLogMsg);
				iFailed = i;			
			}
			dwReturn = AxmSignalSetLimit(i, EMERGENCY_STOP, HIGH, HIGH);

			if ( dwReturn != AXT_RT_SUCCESS )
			{
				sTempLang.LoadStringA(IDS_STRING156);
				sLangChange.Format(sTempLang, MotorName[i]);
				_stprintf_s(m_szLogMsg, sLangChange);
				pFrame->putListLog(m_szLogMsg);
				iFailed = i;
			}
		}
		dwReturn = AxmSignalSetServoAlarm(i, HIGH);
		if ( dwReturn != AXT_RT_SUCCESS )
		{
			iFailed = i;			
		}
	}

	if ( iFailed >= 0 )
	{
		return (-1000 - iFailed);
	}

#endif

	return 1;
}

//! 장비 전체의 DIO 단자의 초기 설정을 진행한다. 
//! [주의 사항] 반드시, 'Axl_Init' 함수의 'AxmMotLoadParaAll' 함수 호출 후에 이 함수를 호출하여야 한다. 
int CAxlMotorSet::Axl_DIO_Config()
{
#ifdef	ON_LINE_MOTOR
	DWORD Status = 0;
	DWORD dwReturn = 0;

	int i = 0, j = 0;
	long lModuleCounts = 0, lInputCounts = 0, lOutputCounts = 0;
	int ModuleNo = 0;

	DWORD uLevel = HIGH, dwStatus;

	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	//DWORD dwStatus2;
	//DWORD Code = AxlOpenNoReset(7);
	//Code = AxdInfoIsDIOModule(&dwStatus2);
	//! 전체 시스템에 장착되어 있는 DIO모듈의 개수를 확인
	AxdInfoGetModuleCount(&lModuleCounts);

	if(lModuleCounts != 4)
	{
		bAxdConnect = false;
		sLangChange.LoadStringA(IDS_STRING194);
		sTempLang.Format(sLangChange, lModuleCounts);
		_stprintf_s(m_szLogMsg, sTempLang);
		pFrame->putListLog(m_szLogMsg);
	}


	//! 입력 모듈..
	AxdInfoGetInputCount(0, &lInputCounts);
	if ( lInputCounts == 32 )
	{
		for ( j=0; j<lInputCounts; j++ )
			AxdiLevelSetInportBit(0, j, HIGH);
	}
	else
	{
		bAxdConnect = false;
		sLangChange.LoadStringA(IDS_STRING1489);	//[IO 모듈 ] 입력 모듈 확인 비정상 [%d EA] .
		sprintf_s(m_szLogMsg, sLangChange, lInputCounts);
		pFrame->putListLog(m_szLogMsg);
		return 0;
	}


	//! 출력 모듈..
	AxdInfoGetOutputCount(1, &lOutputCounts);
	if (lOutputCounts == 32)
	{
		for ( j = 0; j < lOutputCounts; j++ )
			AxdoLevelSetOutportBit(1, j, HIGH);
	}
	else
	{
		bAxdConnect = false;
		sLangChange.LoadStringA(IDS_STRING195);
		_stprintf_s(m_szLogMsg, sLangChange, lOutputCounts);	//"[IO 모듈 ] 출력 모듈 확인 비정상 [%d EA] ."
		pFrame->putListLog(m_szLogMsg);
		return 0;
	}
#endif

	return 1;
}

void CAxlMotorSet::Axl_Close()
{
	int i = 0;

#ifdef ON_LINE_MOTOR

	//! 모든 Motor를 정지한다. 
	for(i=0; i<MAX_MOTOR_NO; i++)
	{
		AxmMoveSStop(i);		
	}

	TCHAR* pszPath = NULL;
	pszPath = m_sMotionSettingFilePath.GetBuffer( m_sMotionSettingFilePath.GetLength() + 1 );
	//! 모든 축의 현재 설정값을 파일에 저장 한다. 
	AxmMotSaveParaAll(pszPath);
	m_sMotionSettingFilePath.ReleaseBuffer();

	AxlClose();

#endif

	for ( i = 0; i < MAX_MOTOR_NO; i++ )
	{
		m_bOrgFlag[i] = false;
	}
}

int CAxlMotorSet::Start_Home_Search(int iAxis)
{//! Home 검색 작업 시작
	m_criHomeProc.Lock();

	DWORD dwReturn = 0;
	DWORD level;

	AxmSignalIsServoOn(iAxis, &level);
	if ( level != ENABLE )
	{
		AxmSignalServoOn(iAxis, ENABLE);	

		for(int i=0; i<20; i++)
		{
			Sleep(5);
			CheckHandle();
		}

		AxmSignalIsServoOn(iAxis, &level);
		if ( level != ENABLE )
		{
			sLangChange.LoadStringA(IDS_STRING1235);
			sMsg.Format(_T("[ %s ] ") + sLangChange, MotorName[iAxis]);		//모터 원점 검색 서보 ON 실패.!!
			errMsg2(Task.AutoFlag, sMsg);
			m_criHomeProc.Unlock();
			return -3;
		}
	}


	//! +++++++++++++++++++++++++++++++++++++++++++++++++++++
	//!    DIR_CCW    00h     (-) 방향
	//!    DIR_CW     01h     (+) 방향
	//! [lHmsig]
	//!    PosEndLimit  00h   +Elm(End limit) +방향 리미트 센서 신호
	//!    NegEndLimit  01h   -Elm(End limit) -방향 리미트 센서 신호
	//!    HomeSensor   04h   IN0(ORG)  원점 센서 신호
	//! [dwZphas]
	//!    DISABLE      00h   Z상 검출 사용하지 않음
	//!    + 방향       01h   Z상 검출 +방향사용
	//!    - 방향       02h   Z상 검출 -방향사용
	
	long    lHmDir = DIR_CW;			//! 원점검색을 초기에 진행할 방향설정
	DWORD   lHmsig =  HomeSensor;		//! 원점 검색에 사용 할 신호설정
	DWORD   dwZphas = DISABLE;			//! 1차 원점검색 완료 후 엔코더 Z상 검출 유무 설정
	double  dwHClrTim = 2000.0;			//! 원점검색 완료 후 지령위치와 Encoder위치를 Clear하기 위해 대기하는 시간설정 [mSec단위]
	double  dwHOffset = 0.0;			//! 원점검색이 완료된 후 기구 원점으로 이동 후 원점 재설정 할 위치
	
	lHmDir = MOTOR_HOME_DIR[iAxis];
	lHmsig = MOTOR_HOME_SIG[iAxis];

	dwReturn = AxmHomeSetMethod(iAxis, lHmDir, lHmsig, dwZphas, dwHClrTim, dwHOffset);
	if ( dwReturn != AXT_RT_SUCCESS )
	{
		sLangChange.LoadStringA(IDS_STRING1236);
		sMsg.Format(_T("[ %s ] ") + sLangChange, MotorName[iAxis]);		//모터 원점 검색 설정 실패
		errMsg2(Task.AutoFlag, sMsg);
		m_criHomeProc.Unlock();
		return -4;
	}


	dwReturn = SetHomeSearchSpeed(iAxis);	//원점 검색 속도 설정
	if ( dwReturn != AXT_RT_SUCCESS )
	{
		sLangChange.LoadStringA(IDS_STRING1236);		//모터 원점 속도 설정 실패
		sMsg.Format(_T("[ %s ] ") + sLangChange, MotorName[iAxis]);errMsg2(Task.AutoFlag, sMsg);
		errMsg2(Task.AutoFlag, sMsg);
		m_criHomeProc.Unlock();
		return -6;
	}

	dwReturn = AxmHomeSetStart(iAxis);
	if ( dwReturn != AXT_RT_SUCCESS )
	{
		//! Error Code 확인
		CString sError = _T("");
		GetResult_Home_Search(iAxis, sError);
		errMsg2(Task.AutoFlag, sMsg);
		m_criHomeProc.Unlock();
		return -7;
	}

	m_criHomeProc.Unlock();
	return 1;
}


DWORD CAxlMotorSet::SetHomeSearchSpeed(int iAxis)
 {//! 원점 검색시 사용되는 속도 설정
 /*
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 // 원점을 빠르고 정밀하게 검색하기 위해 여러 단계의 스탭으로 검출한다. 이때 각 스탭에 사용 될 속도를 설정한다. 
 // 이 속도들의 설정값에 따라 원점검색 시간과, 원점검색 정밀도가 결정된다. 
 // 각 스탭별 속도들을 적절히 바꿔가면서 각 축의 원점검색 속도를 설정하면 된다. 
 // (자세한 내용은 AxmMotSaveParaAll 설명 부분 참조)
 // 원점검색시 사용될 속도를 설정하는 함수
 // [dVelFirst]- 1차구동속도   [dVelSecond]-검출후속도   [dVelThird]- 마지막 속도  [dvelLast]- index검색및 정밀하게 검색하기위해. 
 // [dAccFirst]- 1차구동가속도 [dAccSecond]-검출후가속도 
 */
	DWORD dwReturn = 0;
	double dVelFirst = 20000.;		
	double dVelSecond = 10000.;
	double dVelThird = 4000.;
	double dvelLast = 500.;	

	double dAccFirst = 0.1;		
	double dAccSecond = 0.1;


	double dAccCalFirst = 0.0, dAccCalSecond = 0.0;
//! 원점 속도 조절 할것.
#ifndef ORG_INITIAL_SETTING	
		switch(iAxis)
	{
		case Motor_PCB_X:			//! PCB 공급 X축
			dVelFirst = 15000.;		dVelSecond = 5000.;		dVelThird = 500;		dvelLast = 50.;		dAccFirst = 0.1;	dAccSecond = 0.1;
			break;

		case Motor_PCB_Y:			//! PCB 공급 Y축
			dVelFirst = 10000.;		dVelSecond = 5000.;		dVelThird = 500;		dvelLast = 50.;		dAccFirst = 0.1;	dAccSecond = 0.1;
			break;

		case Motor_PCB_TH:			//! PCB 공급 THETA축
			dVelFirst = 3000.;		dVelSecond = 2000.;		dVelThird = 500;		dvelLast = 50.;		dAccFirst = 0.1;	dAccSecond = 0.1;
			break;

		case Motor_PCB_Xt:			//! PCB 공급 TX축
			dVelFirst = 2000;		dVelSecond = 1000.;		dVelThird = 500;		dvelLast = 50.;		dAccFirst = 0.1;	dAccSecond = 0.1;
			break;

		case Motor_PCB_Yt:			//! PCB 공급 TY축
			dVelFirst = 2000;		dVelSecond = 1000.;		dVelThird = 500;		dvelLast = 50.;		dAccFirst = 0.1;	dAccSecond = 0.1;
			break;

		case Motor_PCB_Z:			//! PCB Z축
			dVelFirst = 3000.;		dVelSecond = 2000.;		dVelThird = 500;		dvelLast = 50.;		dAccFirst = 0.1;	dAccSecond = 0.1;
			break;

		case Motor_Lens_X:			//! LENS 공급 X축
			dVelFirst = 3000.;		dVelSecond = 2000.;		dVelThird = 500;		dvelLast = 50.;		dAccFirst = 0.1;	dAccSecond = 0.1;
			break;

		case Motor_Lens_Y:			//! LENS 공급 Y축
			dVelFirst = 3000.;		dVelSecond = 2000.;		dVelThird = 500;		dvelLast = 50.;		dAccFirst = 0.1;	dAccSecond = 0.1;
			break;

		case Motor_Lens_Z:			//! LENS 공급 Z축
			dVelFirst = 4000.;		dVelSecond = 3000.;		dVelThird = 2000;		dvelLast = 50.;		dAccFirst = 0.1;	dAccSecond = 0.1;
			break;

		case Motor_Lens_Xt:			//! LENS 공급 TX축
			dVelFirst = 500;		dVelSecond = 400.;		dVelThird = 200;		dvelLast = 50.;		dAccFirst = 0.1;	dAccSecond = 0.1;
			break;

		case Motor_Lens_Yt:			//! LENS 공급 TY축
			dVelFirst = 2000;		dVelSecond = 1000.;		dVelThird = 500;		dvelLast = 50.;		dAccFirst = 0.1;	dAccSecond = 0.1;
			break;
	default://유효하지 않는 모터 번호
		dwReturn = AXT_RT_INVALID_MODULE_POS;
		break;	
	}

#else		//!!!!!!!!! 초기 Setting 시, 모터 원점 검색 속도 하향시.
	switch(iAxis)
	{
	case Motor_PCB_X:			//! PCB 공급 X축
		dVelFirst = 10000.;		dVelSecond = 5000.;		dVelThird = 500;		dvelLast = 50.;		dAccFirst = 0.1;	dAccSecond = 0.1;
		break;

	case Motor_PCB_Y:			//! PCB 공급 Y축
		dVelFirst = 10000.;		dVelSecond = 5000.;		dVelThird = 500;		dvelLast = 50.;		dAccFirst = 0.1;	dAccSecond = 0.1;
		break;

	case Motor_PCB_TH:			//! PCB 공급 THETA축
		dVelFirst = 3000.;		dVelSecond = 2000.;		dVelThird = 500;		dvelLast = 50.;		dAccFirst = 0.1;	dAccSecond = 0.1;
		break;

	case Motor_PCB_Xt:			//! PCB 공급 TX축
		dVelFirst = 2000;		dVelSecond = 1000.;		dVelThird = 500;		dvelLast = 50.;		dAccFirst = 0.1;	dAccSecond = 0.1;
		break;

	case Motor_PCB_Yt:			//! PCB 공급 TY축
		dVelFirst = 2000;		dVelSecond = 1000.;		dVelThird = 500;		dvelLast = 50.;		dAccFirst = 0.1;	dAccSecond = 0.1;
		break;

	case Motor_PCB_Z:			//! DISPENSER Z축
		dVelFirst = 3000.;		dVelSecond = 2000.;		dVelThird = 500;		dvelLast = 50.;		dAccFirst = 0.1;	dAccSecond = 0.1;
		break;

	case Motor_Lens_X:			//! LENS 공급 X축
		dVelFirst = 3000.;		dVelSecond = 2000.;		dVelThird = 500;		dvelLast = 50.;		dAccFirst = 0.1;	dAccSecond = 0.1;
		break;

	case Motor_Lens_Y:			//! LENS 공급 Y축
		dVelFirst = 3000.;		dVelSecond = 2000.;		dVelThird = 500;		dvelLast = 50.;		dAccFirst = 0.1;	dAccSecond = 0.1;
		break;

	case Motor_Lens_Z:			//! LENS 공급 Z축
		dVelFirst = 3000.;		dVelSecond = 2000.;		dVelThird = 500;		dvelLast = 50.;		dAccFirst = 0.1;	dAccSecond = 0.1;
		break;

	case Motor_Lens_Xt:			//! LENS 공급 TX축
		dVelFirst = 500;		dVelSecond = 400.;		dVelThird = 200;		dvelLast = 50.;		dAccFirst = 0.1;	dAccSecond = 0.1;
		break;

	case Motor_Lens_Yt:			//! LENS 공급 TY축
		dVelFirst = 2000;		dVelSecond = 1000.;		dVelThird = 500;		dvelLast = 50.;		dAccFirst = 0.1;	dAccSecond = 0.1;
		break;


	default://유효하지 않는 모터 번호
		dwReturn = AXT_RT_INVALID_MODULE_POS;
		break;	
	}
#endif
	
	
#ifdef MOTOR_ACC_TYPE_SEC
	dAccCalFirst = dAccFirst;
	dAccCalSecond = dAccSecond;
#else
	dAccCalFirst = dAccFirst * (9.8 * 1000 *  sysData.fMotorResol[iAxis]);
	dAccCalSecond = dAccFirst * (9.8 * 1000 *  sysData.fMotorResol[iAxis]);		//! 가속 
#endif	

	if( dwReturn == 0 )
	{
		dwReturn = AxmHomeSetVel(iAxis, dVelFirst, dVelSecond, dVelThird, dvelLast, dAccCalFirst, dAccCalSecond);
	}
	
	return dwReturn;
}

//! Home 검색 작업 중이면 false이고, 그렇지 않으면 true를 반환
int CAxlMotorSet::IsCompleted_Home_Search(int axis)
{
	DWORD dwReturn = 0;
	DWORD uHomeResult;

	AxmHomeGetResult(axis, &uHomeResult);
	//! 현재 원점검색이 진행중일 경우
	if ( uHomeResult == HOME_SEARCHING )		return 2;
	if ( uHomeResult == HOME_SUCCESS )			return 1; 
	if ( uHomeResult == HOME_ERR_AMP_FAULT)		return -1;
	if ( uHomeResult == HOME_ERR_NOT_DETECT)	return -2;
	if ( uHomeResult == HOME_ERR_NEG_LIMIT)		return -3;
	if ( uHomeResult == HOME_ERR_POS_LIMIT)		return -4;
	if ( uHomeResult == HOME_ERR_UNKNOWN)		return -5;

	return 0;
}

//! Home 검색 중에 강제로 중지 시킴
void CAxlMotorSet::Stop_Home_Search(int iAxis)
{//! Home 검색 중에 강제로 중지 시킴
	AxmMoveSStop(iAxis);
}


//! Home 검색 작업 중의 진행 정도, 단위 %로 반환된다. 
int CAxlMotorSet::GetRate_Home_Search(int axis)
{
	DWORD dwReturn = 0;
	DWORD uHomeStepNumber,uHomeMainStepNumber;

	//! 원점검색 시작되면 진행율을 확인할 수 있다. 원점검색이 완료되면 성공여부와 관계없이 100을 반환하게 된다.
	//! uHomeMainStepNumber은 겐트리일 경우 마스터,슬레이브가 동작하는지 확인할 때 이용한다.
	//!  (마스터축 동작일 때는 0을 리턴, 슬레이브동작일 때는 10을 리턴한다.)
	dwReturn = AxmHomeGetRate(axis, &uHomeMainStepNumber, &uHomeStepNumber);

	//! 원점검색 진행율(단위: %)
	return uHomeStepNumber;
}

//! Home 검색 작업 결과 문자열을 알아낸다. 
bool CAxlMotorSet::GetResult_Home_Search(int axis, CString &sResult)
{
	DWORD uHomeResult;
	AxmHomeGetResult(axis, &uHomeResult);

	bool bRet = false;

	switch(uHomeResult)
	{
	case HOME_SUCCESS:
		{
			sResult = _T("원점 검색이 성공적으로 종료 됐을 경우");
			bRet = true;
		}
		break;
	case HOME_SEARCHING:
		{
			sResult = _T("현재 원점검색이 진행중일 경우");
		}
		break;
	case HOME_ERR_GNT_RANGE:
		{
			sResult = _T("겐트리 구동축의 Master축과 Slave축의 원점검색 결과가 설정한 OffsetRange를 벗어났을경우");
		}
		break;
	case HOME_ERR_USER_BREAK:
		{
			sResult = _T("원점 검색중 사용자가 정지 명령을 실행했을 경우");
		}
		break;
	case HOME_ERR_VELOCITY:
		{
			sResult = _T("원점 검색의 속도 설정 값 중 한 개라도 0보다 작거나 같을경우");
		}
		break;
	case HOME_ERR_AMP_FAULT:
		{
			sResult = _T("원점 검색중 서보팩 알람이 발생할 경우");
		}
		break;
	case HOME_ERR_NEG_LIMIT:
		{
			sResult = _T("(+)방향으로 원점센서 검출 중 (-)리미트 센서가 감지될 경우");
		}
		break;
	case HOME_ERR_POS_LIMIT:
		{
			sResult = _T("(-)방향으로 원점센서 검출 중 (+)리미트 센서가 감지될 경우");
		}
		break;
	case HOME_ERR_NOT_DETECT:
		{
			sResult = _T("원점센서가 감지되지 않을경우");
		}
		break;
	case HOME_ERR_UNKNOWN:
		{
			sResult = _T("알수없는 채널(축) 번호(0 ~ (최대축수 - 1))로 원점검색을 시작하려 했을경우");
		}
		break;
	default:
		{
			sResult = _T("Error");
		}
		break;
	}//! switch(uHomeResult)

	return bRet;
}

//! 특정 위치 (Limit 센서나 Home 센서)에서 자동으로 멈추도록 하여 모터를 움직일 때 사용한다.
//! 지정 축에서 설정된 신호를 검출한다
//! 리미트 센서신호나 원점 센서신호, 서보 드라이버의 Z상 신호 또는 범용 입력 신호들의 Edge를 검출할 수 있다.
//! 주로 원점검색 구동 함수 구현 시 사용하는 함수이다.
//! [주의 사항] 
//!		1) End Limit 센서를 찾을 경우, 신호의 Active Level 상태를 검출한다.
//!     2) Emergency Stop으로 사용할 경우, 가감속이 무시되며 지정된 속도로 가속 급정지하게된다.
bool CAxlMotorSet::MoveAxis_To_Sensor(int axis, strMove_Input_Signal_Search *pstrInput)
{
	//! 입력값 확인
	if ( pstrInput == NULL )
	{
		return false;
	}

	double dVel   = pstrInput->dVel;
	double dAccel = pstrInput->dAccel;

	long lDetectSignal = -1;
	long lSignalEdge = -1;
	long lSignalMethod = -1;

	//! lDetectSignal 설정
	if ( pstrInput->bEndLimit_Negative == true )
	{
		lDetectSignal = NegEndLimit;
	}
	if ( pstrInput->bEndLimit_Positive == true )
	{
		lDetectSignal = PosEndLimit;
	}
	if ( pstrInput->bHomeSensor == true )
	{
		lDetectSignal = HomeSensor;
	}
	if ( pstrInput->bPhase_Encoder_Z == true )
	{
		lDetectSignal = EncodZPhase;
	}

	//! lSignalEdge 설정
	if ( pstrInput->bEdge_Down == true )
	{
		lSignalEdge = SIGNAL_DOWN_EDGE;
	}
	if ( pstrInput->bEdge_Up == true )
	{
		lSignalEdge = SIGNAL_UP_EDGE;
	}

	//! lSignalMethod 설정
	if ( pstrInput->bEmergency == true )
	{
		lSignalMethod = EMERGENCY_STOP;
	}
	if ( pstrInput->bSlowDown == true )
	{
		lSignalMethod = SLOWDOWN_STOP;
	}

	//! 입력값 확인
	if ( lDetectSignal == NegEndLimit )
		dVel = -1 * fabs(pstrInput->dVel);
	else
		dVel = fabs(pstrInput->dVel);


	if ( dAccel < 0. )
	{
		return false;
	}
	if ( lDetectSignal < 0 )
	{
		return false;
	}
	if ( lSignalEdge < 0 )
	{
		return false;
	}
	if ( lSignalMethod < 0 )
	{
		return false;
	}

	DWORD dwReturn = 0;

	//! 지정 축에서 설정된 신호를 검출할 때까지 모터를 움직인다. 
	dwReturn = AxmMoveSignalSearch(axis, dVel, dAccel, lDetectSignal, lSignalEdge, lSignalMethod);
	if ( dwReturn != AXT_RT_SUCCESS )
	{
		return false;
	}

	return true;
}

//! Added by LHW (2013/4/16)
//! GUI 화면에서 설정한 길이만큼 움직인다. (상대 이동)
//! GUI 화면에서 많이 사용되는 기능이라서 따로 함수를 만들다. 
bool CAxlMotorSet::Move_From_GUI(int axis, int iID_GUI, CWnd* pParentWnd, bool bPlus)
{
	if ( pParentWnd == NULL )
	{
		return false;
	}
	if ( g_bMovingflag == true )
	{
		return false;
	}
	g_bMovingflag = true;

	CString sGetTemp = _T("");
	GetString_FromUI(iID_GUI, pParentWnd, sGetTemp);

	double dGetTemp = atof(sGetTemp);
	if ( dGetTemp > 3. )
	{
		dGetTemp = 3.;
	}
	else if (dGetTemp < -3 )
	{
		dGetTemp = -3;
	}

	if ( bPlus == false )
	{
		dGetTemp *= (-1.);
	}

	MoveAxis(axis, REL, dGetTemp, 4, 20);

	g_bMovingflag =false;
	
	return true;
}

//! CRC 신호 설정(펄스 출력형 모션 제어기에 한정된 기능)
//! 특정 서보팩의 경우 구동이 완료된 시점에서 또는 리미트센서를 감지한 경우에 
//! 외부에서 CRC(Current Remaining Clear)신호를 받아 서보팩이 가지고 있는 잔여 펄스를 지워주어야 하는 경우가 발생한다.
//! [주의 사항] CRC 신호 설정 기능은 펄스 출력형 모션제어기(PCI-N804/404, RTEX-PM)에서만 사용할 수 있는 기능이다.
bool CAxlMotorSet::ActCRC(int axis)
{
	DWORD dwReturn = 0;
	long  BoardNo = 0;
	long  ModulePos = 0;
	DWORD ModuleID = 0;

	DWORD uLevel, uMethod;


	//! ModuleID (Module의 종류)
	//! 'AXHS.h' 파일 : 'C:\Program Files\EzSoftware RM\AXL(Library)\C, C++' 폴더안에 있음 (AXT_FUNC_MODULE)	
	//!      AXT_SMC_R1V04    = 0x09,   // CAMC-QI, 1 Axis, For RTEX SLAVE only	
	dwReturn = AxmInfoGetAxis(axis, &BoardNo, &ModulePos, &ModuleID);
	if ( dwReturn != AXT_RT_SUCCESS )
	{
		return false;
	}
	if ( ModuleID != AXT_SMC_R1V04 )
	{
		return false;
	}

	//! 지정 축에 CRC 신호 사용 여부 설정을 반환 한다.
	dwReturn = AxmCrcGetMaskLevel(axis, &uLevel, &uMethod);
	if ( dwReturn != AXT_RT_SUCCESS )
	{
		return false;
	}
	if ( uLevel == UNUSED )
	{
		//! CRC 신호 사용안함
		return false;
	}

	//! 지정 축에 CRC 신호를 강제적으로 출력을 발생시킨다. (일정 시간 동안만 작용시킴)
	AxmCrcSetOutput(axis, ENABLE);
	Sleep(10);
	AxmCrcSetOutput(axis, DISABLE);

	return true;
}

bool CAxlMotorSet::AmpDisable(int axis)
{
	m_bOrgFlag[axis] = false;
	double dDecel = 0.;

#ifdef ON_LINE_MOTOR

	AxmMoveStop(axis, dDecel);	
	AxmSignalServoOn(axis, DISABLE);

	
	if (axis != Motor_Lens_Xt && axis != Motor_PCB_Xt && axis != Motor_PCB_Yt) {
		AxmSignalServoAlarmReset(axis, ENABLE);
	}
#endif

	return true;
}
bool CAxlMotorSet::AmpDisableAll()
{
	bool rtnVal = true;
	double dDecel = 0.;

	for(int i=0; i<MAX_MOTOR_NO; i++)
	{
		m_bOrgFlag[i] = false;

#ifdef ON_LINE_MOTOR
		AxmMoveStop(i, dDecel);		
		AxmSignalServoOn(i, DISABLE);
	
		if (i != Motor_Lens_Xt && i != Motor_PCB_Xt && i != Motor_PCB_Yt)
			AxmSignalServoAlarmReset(i, ENABLE);
	}

	Sleep(500);

	for(int i=0; i<MAX_MOTOR_NO; i++)
	{
		if (i != Motor_Lens_Xt && i != Motor_PCB_Xt && i != Motor_PCB_Yt)
			AxmSignalServoAlarmReset(i, DISABLE);
#endif
	}

	return true;
}
bool CAxlMotorSet::AmpEnable(int axis)
{
	DWORD level = ENABLE;

#ifdef ON_LINE_MOTOR

	StopAxis(axis);

	//! 이미 Servo On 상태인지 확인한다. 
	AxmSignalIsServoOn(axis, &level);
	if ( level == ENABLE )
	{
		return true;
	}
	m_bOrgFlag[axis] = false;
	AxmSignalServoOn(axis, ENABLE);	


	Sleep(100);

	AxmSignalIsServoOn(axis, &level);
	if ( level != ENABLE )
	{
		return false;
	}
#endif

	return true;
}
bool CAxlMotorSet::AmpEnableAll()
{
	bool rtnVal = true;
	DWORD level = ENABLE;
	int i = 0;


	StopAxisAll();
	Sleep(100);
	int iRet_Axis = Axl_Axisconfig();

	if(iRet_Axis != 1)
	{
		sLangChange.LoadStringA(IDS_STRING1281);	//서보 모터 드라이브 초기화 실패.
		errMsg2(Task.AutoFlag, sLangChange);
		return	false;
	}


	for ( i = 0; i < MAX_MOTOR_NO; i++ )
	{
		m_bOrgFlag[i] = false;

#ifdef ON_LINE_MOTOR

		AxmSignalIsServoOn(i, &level);
		if ( level == ENABLE )
		{
			continue;
		}

		AxmSignalServoOn(i, ENABLE);	

		AxmSignalIsServoOn(i, &level);
		if ( level != ENABLE )
		{
			rtnVal = false;
		}
#endif		
	}

	Sleep(100);

	//! 1개라도 Servo On 실패가 있으면, 다시 시도한다. 
	if ( rtnVal == false )
	{
		rtnVal = true;

		for ( i = 0; i < MAX_MOTOR_NO; i++ )
		{
#ifdef ON_LINE_MOTOR
			//! 이미 Servo On 상태인지 확인한다. 
			AxmSignalIsServoOn(i, &level);
			if ( level == ENABLE )
			{
				continue;
			}

			AxmSignalServoOn(i, ENABLE);	

			Sleep(100);

			AxmSignalIsServoOn(i, &level);
			if ( level != ENABLE )
			{
				rtnVal = false;
			}
#endif		
		}
	}//! if ( rtnVal == false )

	if(!rtnVal)
	{
		TCHAR dispStr[100];
		_stprintf_s(dispStr, "AmpEnableAll 실패.");	//AmpEnableAll 실패.
		LogSave(dispStr);
	}

	return rtnVal;
}


bool CAxlMotorSet::AmpFaultReset(int axis)
{
	m_bOrgFlag[axis] = false;
	double dDecel = 0.;

#ifdef ON_LINE_MOTOR

	DWORD level;

	AxmMoveStop(axis, dDecel);	
	AxmSignalServoOn(axis, DISABLE);

	AxmSignalServoAlarmReset(axis, ENABLE);

	Sleep(100);

	AxmSignalServoAlarmReset(axis, DISABLE);
	AxmSignalServoOn(axis, ENABLE);	

	Sleep(100);

	AxmSignalIsServoOn(axis, &level);
	if ( level != ENABLE )
	{
		return false;
	}
#endif

	return true;
}
bool CAxlMotorSet::AmpFaultResetAll()
{
	int i = 0;

	for(i=0; i<MAX_MOTOR_NO; i++)
	{
		AmpDisable(i);
	}

	Sleep(1000);

	for( i=0; i<MAX_MOTOR_NO; i++)
	{
		AmpEnable(i);
	}

	return true;
}

int	CAxlMotorSet::AmpFaultCheck()
{
	DWORD upStatus;
	int iAmpFaultFlag = 0;

	for(int i=0; i<MAX_MOTOR_NO; i++)
	{
		// 축의 알람 신호 확인
		AxmSignalReadServoAlarm(i, &upStatus);

		if(upStatus == ACTIVE)
		{
			iAmpFaultFlag += 0x01<<i;
			m_bOrgFlag[i] = true;
		}
	}

	Task.iAmpFaultFlag = iAmpFaultFlag;
	return iAmpFaultFlag;
}


//! Motor가 목표 지점에 도착했는지 확인
bool CAxlMotorSet::GetInposition(int axis)
{
#ifdef ON_LINE_MOTOR

	DWORD dwRet = 0;
	DWORD use;

	//! Inposition 신호 설정 확인
	dwRet = AxmSignalGetInpos(axis, &use);
	if ( dwRet != AXT_RT_SUCCESS )
	{
		return false;
	}
	if ( use == UNUSED )
	{
		return false;
	}

	//! Inpositon 신호의 입력 확인
	DWORD upStatus = INACTIVE;
	dwRet = AxmSignalReadInpos(axis, &upStatus);
	if ( dwRet != AXT_RT_SUCCESS )
	{
		return false;
	}
	if ( upStatus == INACTIVE )
	{
		return false;
	}	
#endif
	return true;
}

bool CAxlMotorSet::GetInpositionPos(int iAxis, double dPos)
{//! 지정 축의 Motor가 목표 지점에 도착했는지 확인( Encord값으로 확인)
	DWORD dwRet = 0, use = 0;

	if( !IsStopAxis(iAxis) || fabs(GetEncoderPos(iAxis) - dPos) > 0.005 )	return false;

	return true;
}

bool CAxlMotorSet::GetHomeSensor(int axis)
{
#ifdef ON_LINE_MOTOR
	DWORD dwRet = 0;
	int nAxis = axis;
	//DWORD state;

	//dwRet = AxmHomeGetSignalLevel(axis, &state);
	//if ( dwRet != AXT_RT_SUCCESS )
	//{
	//	return false;
	//}

	//int ret = home_switch(axis);
	//return ret ? true : false;
	//! Home 신호의 입력 확인
	DWORD upStatus = 0;
	dwRet = AxmHomeReadSignal(nAxis, &upStatus);
	if ( dwRet != AXT_RT_SUCCESS )
	{
		return false;
	}
	if ( upStatus == INACTIVE )
	{
		return false;
	}
#endif
	return true;
}
bool CAxlMotorSet::GetPosiSensor(int axis)
{
#ifdef ON_LINE_MOTOR
	DWORD dwRet = 0;
	DWORD StopMode = 0;
	DWORD PositiveLevel = 0;
	DWORD NegativeLevel = 0;
	int nAxis = axis;
	dwRet = AxmSignalGetLimit(nAxis, &StopMode, &PositiveLevel, &NegativeLevel);
	if ( dwRet != AXT_RT_SUCCESS )
	{
		return false;
	}
	if ( PositiveLevel == UNUSED )
	{
		//! 사용 안함		
		return false;
	}

	//int ret = pos_switch(axis);
	//return ret ? true : false;
	//! 리미트 센서 입력 상태 확인
	DWORD upPositiveLevel = 0;
	DWORD upNegativeLevel = 0;
	dwRet = AxmSignalReadLimit(nAxis, &upPositiveLevel, &upNegativeLevel);
	if ( dwRet != AXT_RT_SUCCESS )
	{
		return false;
	}
	if ( upPositiveLevel == ACTIVE )
	{
		return true;
	}
#endif

	return false;
}
bool CAxlMotorSet::GetNegaSensor(int axis)
{
#ifdef ON_LINE_MOTOR
	DWORD dwRet = 0;
	DWORD StopMode = 0;
	DWORD PositiveLevel = 0;
	DWORD NegativeLevel = 0;
	int nAxis = axis;
	dwRet = AxmSignalGetLimit(nAxis, &StopMode, &PositiveLevel, &NegativeLevel);
	if ( dwRet != AXT_RT_SUCCESS )
	{
		return false;
	}
	if ( NegativeLevel == UNUSED )
	{
		//! 사용 안함		
		return false;
	}

	//int ret = neg_switch(axis);
	//return ret ? true : false;
	//! 리미트 센서 입력 상태 확인
	DWORD upPositiveLevel = 0;
	DWORD upNegativeLevel = 0;
	dwRet = AxmSignalReadLimit(nAxis, &upPositiveLevel, &upNegativeLevel);
	if ( dwRet != AXT_RT_SUCCESS )
	{
		return false;
	}
	if ( upNegativeLevel == ACTIVE )
	{
		return true;
	}
#endif

	return false;
}
//! 축의 알람이 발생하면 true를 반환
bool CAxlMotorSet::GetAmpFault(int axis)
{
#ifdef	ON_LINE_MOTOR

	DWORD dwRet = 0;
	DWORD use = 0;

	int nAxis = axis;
	dwRet = AxmSignalGetServoAlarm(nAxis, &use);
	if ( dwRet != AXT_RT_SUCCESS )
	{		
		return true;
	}
	if ( use == UNUSED )
	{
		return true;
	}

	DWORD upStatus = 0;
	// 축의 알람 신호 확인
	dwRet = AxmSignalReadServoAlarm(nAxis, &upStatus);
	if ( dwRet != AXT_RT_SUCCESS )
	{
		m_bOrgFlag[nAxis] = false;
		return true;
	}
	if(upStatus == ACTIVE)
	{
		m_bOrgFlag[nAxis] = false;
		return true;
	}
#endif

	return false;
}

bool CAxlMotorSet::GetAmpEnable(int axis)
{
	DWORD upStatus;
// Servo 알람 확인.
	AxmSignalIsServoOn(axis, &upStatus);	// upStatus  1: Servo On
	if(upStatus == ACTIVE)
	{
		return true;
	}

	m_bOrgFlag[axis] = false;
	return false;
}


bool CAxlMotorSet::GetAmpEnableAll()
{
	DWORD upStatus;
	bool rtnVal = true;

	for(int i=0; i<MAX_MOTOR_NO; i++)
	{
		AxmSignalIsServoOn(i, &upStatus);	// upStatus  1: Servo On
		if(upStatus != ACTIVE)
		{
			m_bOrgFlag[i] = false;
			rtnVal = false;
		}
	}

	return rtnVal;
}


double CAxlMotorSet::GetEncoderPos(int axis)
{
	double pos = 0;
#ifdef ON_LINE_MOTOR
	//if (axis == Motor_Lens_Xt || axis == Motor_Lens_Yt || axis == Motor_PCB_Xt || axis == Motor_PCB_Yt || axis == Motor_PCB_Z || axis == Motor_Lens_Z
		//|| axis == Motor_PCB_TH || axis == Motor_LensAlign_TH || axis == Motor_LensAlign_Yt || axis == Motor_LensAlign_Xt || axis == Motor_LensLaser_Yt || axis == Motor_LensLaser_Xt)
	if(MOTOR_TYPE[axis] == STEPING)
	{
		AxmStatusGetCmdPos(axis, &pos);	
	}else
	{
		AxmStatusGetActPos(axis, &pos);
	}
#endif

	pos /= sysData.fMotorResol[axis];

	return (float)pos;
}

double CAxlMotorSet::GetCommandPos(int axis)
{
	double pos = 0;

#ifdef ON_LINE_MOTOR

	AxmStatusGetCmdPos(axis, &pos);	
#endif

	pos /= sysData.fMotorResol[axis];

	return (float)pos;
}

double CAxlMotorSet::GetEncoderPos_Disp(int axis)
{
	double pos = 0;
	int mAxis = axis;
#ifdef ON_LINE_MOTOR
	AxmStatusGetActPos(mAxis, &pos);
#endif

	pos /= sysData.fMotorResol[mAxis];
	pos -= sysData.dDataset[mAxis];

	return (float)pos;
}

double CAxlMotorSet::GetCommandPos_Disp(int axis)
{
	double pos = 0.0;

	int mAxis = axis;
#ifdef ON_LINE_MOTOR
	AxmStatusGetCmdPos(mAxis, &pos);
#endif

	pos /= sysData.fMotorResol[mAxis];
	pos -= sysData.dDataset[mAxis];

	return (float)pos;
}

//! Motor가 정지했으면 true를 반환
bool CAxlMotorSet::IsStopAxis(int axis)
{
#ifdef ON_LINE_MOTOR

	//! 축의 구동 상태를 확인
	DWORD Status;
	DWORD dwRet = AxmStatusReadInMotion(axis, &Status);
	if ( dwRet != AXT_RT_SUCCESS )
	{
		return false;
	}
	if (Status == FALSE)
	{
		//! 모터가 정지하였습니다.
		return true;
	}
#endif

	return false;
}



bool CAxlMotorSet::StopAxis(int axis)
{
#ifdef ON_LINE_MOTOR
	
	AxmMoveSStop(axis);
	Stop_Home_Search(axis);

	CTimeChecker timeChk;
	timeChk.Init_Time();
	timeChk.Start_Time();

	double t_duration = 0.;
	
	while(!IsStopAxis(axis))
	{
		DoEvents();

		t_duration = timeChk.Measure_Time(0);
		
		if(t_duration>1000)
		{
			//clear_status(axis);

			sTempLang.LoadStringA(IDS_STRING167);
			sLangChange.Format(sTempLang, MotorName[axis]);
			TCHAR temp[200];
			wsprintf(temp,sLangChange);
			CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
			pFrame->putListLog(temp);
			LogSave(temp);

			return false;
		}

		Sleep(5);
	}	
#endif

	return true;
}
bool CAxlMotorSet::StopAxisAll()
{
	int i;
	bool runFlag[MAX_MOTOR_NO] = {0, };

#ifdef ON_LINE_MOTOR
	for(i=0; i<MAX_MOTOR_NO; i++)
	{
		//! 현재 구동 중인 처음에 사용자가 입력한 가속도만큼 모션 동작을 감속하면서 정지하는 함수이다. 
		AxmMoveSStop(i);
		Stop_Home_Search(i);

		runFlag[i] = 1;
	}
#endif

	CTimeChecker timeChk;

	timeChk.Init_Time();
	timeChk.Start_Time();
	double t_duration = 0.0;

	while(1)
	{
		t_duration = timeChk.Measure_Time(0);

		if(t_duration>1000)
		{
			LogSave("All Motor Stop Time Exceed. [1 sec]");
			return false;
		}

		for(i=0; i<MAX_MOTOR_NO; i++)
		{
			if (runFlag[i])
			{

#ifdef ON_LINE_MOTOR
				if(!IsStopAxis(i))
#endif
				{
					runFlag[i] = 0;
					break;
				}
			}
		}

		if(i==MAX_MOTOR_NO)
			break;

		DoEvents();

		Sleep(5);
	}
	
	return true;
}



BOOL CAxlMotorSet::JogMove(int axis, double dVel)
{// 나중에 축 별로 나누어서 사용.
	if(GetAmpFault(axis))
		return FALSE;

	double dAcc = (sysData.fMotorAccTime[axis]);  //(short)
	int ret = 0;
	DWORD dwRet = 0;
#ifdef	ON_LINE_MOTOR
	dwRet = AxmMoveVel(axis, dVel, dAcc, dAcc);
#endif
	ret = dwRet;

	return ret;
}
BOOL CAxlMotorSet::JogStop(int axis)
{
	//++ 지정한 축의 구동을 감속정지합니다.
	AxmMoveSStop(axis);

#ifdef	ON_LINE_MOTOR
	CTimeChecker timeChk;

	timeChk.Init_Time();
	timeChk.Start_Time();
	double t_duration = 0.0;

	while(!IsStopAxis(axis))
	{
		DoEvents();

		t_duration = timeChk.Measure_Time(0);

		if(t_duration > 1000)
		{
			LogSave("JOG Move Stop Time Exceed. [1 sec]");
			return false;
		}
	}
#endif

	return true;
}

bool CAxlMotorSet::DispenseGoMotorPos(int no, short axis[MAX_MOTOR_NO], double pos[MAX_MOTOR_NO], double dVel)
{
	long   axis2[MAX_MOTOR_NO] = { 0, };
	double pos2[MAX_MOTOR_NO] = { 0, };
	double vel[MAX_MOTOR_NO] = { 0, };
	double acc[MAX_MOTOR_NO] = { 0, };
	double dec[MAX_MOTOR_NO] = { 0, };

	int cnt = 0;
	double curPos = 0.0;

	for (int i = 0; i<no; i++)
	{
		if (!m_bOrgFlag[axis[i]])
			return false;

		if (!IsStopAxis(axis[i]))
		{
			CString tmpStr = "";
			sLangChange.LoadStringA(IDS_STRING1239);
			tmpStr.Format(_T("[%s] ") + sLangChange + _T(" [goMotoPos]"), MotorName[axis[i]]);
			errMsg2(Task.AutoFlag, tmpStr);
			return false;
		}

		if (axis[i] == Motor_PCB_Z || axis[i] == Motor_Lens_Z || axis[i] == Motor_Lens_Xt || axis[i] == Motor_Lens_Yt || axis[i] == Motor_PCB_Xt || axis[i] == Motor_PCB_Yt || axis[i] == Motor_PCB_TH) {
			curPos = GetCommandPos(axis[i]);
		}
		else {
			curPos = GetEncoderPos(axis[i]);
		}

		//! Motor의 이동 목표 위치, 속도, 가속도/감속도 등을 알아낸다. 
		axis2[cnt] = axis[i];
		pos2[cnt] = pos[i] * sysData.fMotorResol[axis[i]];

		vel[cnt] = dVel * sysData.fMotorResol[axis[i]];//sysData.fMotorSpeed[axis[i]] * sysData.fMotorResol[axis[i]];

		acc[cnt] = sysData.fMotorAccTime[axis[i]]; //! 가속 가속도
		dec[cnt] = sysData.fMotorAccTime[axis[i]];//sysData.iMotorDecTime[axis[i]];

		if (fabs(pos[i] - curPos)<0.001) { 			// 이동할 위치에서 5um 이상 차이가 없을때는 움직이지 않음.
			continue;
		}
		else {
			cnt++;
		}
	}

	//! 여러 개의 축에 대해서 현재의 위치에서 지정한 거리만큼 이동을 동시에 시작한다. 
	//! 이 함수를 사용하면 여러 개의 축이 동시에 작업을 시작한다. 
	//! 이 함수는 여러 축이 동기를 맞추어 작업을 시작해야 하는 경우에 사용한다. 
	//! 펄스 출력이 시작되는 시점에서 함수를 벗어난다.
#ifdef ON_LINE_MOTOR
	AxmMoveStartMultiPos(cnt, axis2, pos2, vel, acc, dec);
	Sleep(10);
#endif

	return true;
}
bool CAxlMotorSet::goMotorPos(int no, short axis[MAX_MOTOR_NO], double pos[MAX_MOTOR_NO], bool bAutoRun)
{
	long   axis2[MAX_MOTOR_NO] = {0, };
	double pos2[MAX_MOTOR_NO] = {0, };
	double vel[MAX_MOTOR_NO] = {0, };
	double acc[MAX_MOTOR_NO] = {0, };
	double dec[MAX_MOTOR_NO] = {0, };

	int cnt = 0;
	double curPos = 0.0;

	for(int i=0; i<no; i++)
	{
		if(!m_bOrgFlag[axis[i]])
			return false;

		if(!IsStopAxis(axis[i]))
		{
			CString tmpStr="";
			sLangChange.LoadStringA(IDS_STRING1239);
			tmpStr.Format(_T("[%s] ") + sLangChange + _T(" [goMotoPos]"), MotorName[axis[i]]);
			errMsg2(Task.AutoFlag, tmpStr);
			return false;
		}

		//if (axis[i] == Motor_PCB_Z || axis[i] == Motor_Lens_Z || axis[i] == Motor_Lens_Xt || axis[i] == Motor_Lens_Yt || axis[i] == Motor_Lens_TH || axis[i] == Motor_PCB_Xt || axis[i] == Motor_PCB_Yt	|| axis[i] == Motor_PCB_TH 
			//|| axis[i] == Motor_LensAlign_Z || axis[i] == Motor_LensAlign_TH || axis[i] == Motor_LensAlign_Yt || axis[i] == Motor_LensAlign_Xt || axis[i] == Motor_LensLaser_Yt || axis[i] == Motor_LensLaser_Xt)
		if(MOTOR_TYPE[i] == STEPING)
		{
			curPos = GetCommandPos(axis[i]);
		}else{
			curPos = GetEncoderPos(axis[i]);
		}
		
		//! Motor의 이동 목표 위치, 속도, 가속도/감속도 등을 알아낸다. 
		axis2[cnt] = axis[i];
		pos2[cnt] = pos[i] * sysData.fMotorResol[axis[i]];
		if ( bAutoRun == true )
		{ 
			vel[cnt] = sysData.fMotorSpeed[axis[i]] * sysData.fMotorResol[axis[i]];
		}
		else
		{
			vel[cnt] = sysData.fMotorSpeed[axis[i]] * sysData.fMotorResol[axis[i]];
		}
		acc[cnt] = sysData.fMotorAccTime[axis[i]]; //! 가속 가속도
		dec[cnt] = sysData.fMotorAccTime[axis[i]];//sysData.iMotorDecTime[axis[i]];

		if( fabs(pos[i]-curPos)<0.001){ 			// 이동할 위치에서 5um 이상 차이가 없을때는 움직이지 않음.
			continue;
		}else{
			cnt++;
		}
	}

	//! 여러 개의 축에 대해서 현재의 위치에서 지정한 거리만큼 이동을 동시에 시작한다. 
	//! 이 함수를 사용하면 여러 개의 축이 동시에 작업을 시작한다. 
	//! 이 함수는 여러 축이 동기를 맞추어 작업을 시작해야 하는 경우에 사용한다. 
	//! 펄스 출력이 시작되는 시점에서 함수를 벗어난다.
#ifdef ON_LINE_MOTOR
	AxmMoveStartMultiPos(cnt, axis2, pos2, vel, acc, dec);
	Sleep(10);
#endif

	return true;
}

bool CAxlMotorSet::goMotorZPos(int no, short axis[MAX_MOTOR_NO],double pos[MAX_MOTOR_NO],double dVel, bool bAutoRun)
{
	long   axis2[MAX_MOTOR_NO] = {0, };
	double pos2[MAX_MOTOR_NO] = {0, };
	double vel[MAX_MOTOR_NO] = {0, };
	double acc[MAX_MOTOR_NO] = {0, };
	double dec[MAX_MOTOR_NO] = {0, };

	int cnt =0;
	double curPos;

	for(int i=0; i<no; i++)
	{
		if(!m_bOrgFlag[axis[i]])
			return false;

		if(!IsStopAxis(axis[i]))
		{
			CString tmpStr;
			sLangChange.LoadStringA(IDS_STRING1239);
			tmpStr.Format(_T("[%s] ") + sLangChange + _T(" [goMotoPos]"), MotorName[axis[i]]);
			errMsg2(Task.AutoFlag, tmpStr);
			return false;
		}

		//if (axis[i] == Motor_Lens_Xt || axis[i] == Motor_Lens_Yt || axis[i] == Motor_PCB_Xt || axis[i] == Motor_PCB_Yt || axis[i] == Motor_PCB_Z || axis[i] == Motor_Lens_Z
			//|| axis[i] == Motor_LensAlign_Z || axis[i] == Motor_LensAlign_TH || axis[i] == Motor_LensAlign_Yt || axis[i] == Motor_LensAlign_Xt || axis[i] == Motor_LensLaser_Yt || axis[i] == Motor_LensLaser_Xt)
		if (MOTOR_TYPE[i] == STEPING)
		{
			curPos = GetCommandPos(axis[i]);
		}else{
			curPos = GetEncoderPos(axis[i]); //GetCommandPos(axis[i]);
		}
		
		//! Motor의 이동 목표 위치, 속도, 가속도/감속도 등을 알아낸다. 
		axis2[cnt] = axis[i];
		pos2[cnt] = pos[i] * sysData.fMotorResol[axis[i]];
		if ( bAutoRun == true )
		{
			vel[cnt] = dVel * sysData.fMotorResol[axis[i]];//sysData.fMotorSpeed[axis[i]] * sysData.fMotorResol[axis[i]];
		}
		else
		{
			vel[cnt] = dVel * sysData.fMotorResol[axis[i]];//sysData.fMotorSpeed[axis[i]] * sysData.fMotorResol[axis[i]];
		}
		acc[cnt] = sysData.fMotorAccTime[axis[i]]; //! 가속 가속도
		dec[cnt] = sysData.fMotorAccTime[axis[i]];//sysData.iMotorDecTime[axis[i]];

		if( fabs(pos[i]-curPos)<0.003) 			// 이동할 위치에서 5um 이상 차이가 없을때는 움직이지 않음.
			continue;
		else
			cnt++;
	}

	//! 여러 개의 축에 대해서 현재의 위치에서 지정한 거리만큼 이동을 동시에 시작한다. 
	//! 이 함수를 사용하면 여러 개의 축이 동시에 작업을 시작한다. 
	//! 이 함수는 여러 축이 동기를 맞추어 작업을 시작해야 하는 경우에 사용한다. 
	//! 펄스 출력이 시작되는 시점에서 함수를 벗어난다.
#ifdef ON_LINE_MOTOR
	AxmMoveStartMultiPos(cnt, axis2, pos2, vel, acc, dec);
	Sleep(10);
#endif

	return true;
}
bool CAxlMotorSet::MoveAxis(int axis, bool AbSFlag, double dPos, double dVel, float iAcc)
{	// abs 1:absolute, 0:increment
	if(GetAmpFault(axis))
	{
		m_bOrgFlag[axis] = false;
		sLangChange.LoadStringA(IDS_STRING1453);
		LogSave(sLangChange);		//"AMP Alarm 발생. MoveAxis 동작 실패."
		return false;
	}

	if(!GetAmpEnable(axis))
	{
		m_bOrgFlag[axis] = false;
	
		sLangChange.LoadStringA(IDS_STRING1226);
		CString tmpStr;
		tmpStr.Format(_T("[%s] ") + sLangChange, MotorName[axis]);
		errMsg2(Task.AutoFlag, tmpStr);
		return false;
	}

	if(AbSFlag == ABS)
	{
		double curPos;

		//if (axis == Motor_PCB_Z || axis == Motor_Lens_Z || axis == Motor_Lens_Xt || axis == Motor_Lens_Yt || axis == Motor_PCB_Xt || axis == Motor_PCB_Yt 
			//|| axis == Motor_PCB_Z || axis == Motor_PCB_TH || axis == Motor_LensAlign_TH || axis == Motor_LensAlign_Yt || axis == Motor_LensAlign_Xt || axis == Motor_LensLaser_Yt || axis == Motor_LensLaser_Xt)
		if (MOTOR_TYPE[axis] == STEPING)
		{
			curPos = GetCommandPos(axis);
		}else{
			curPos = GetEncoderPos(axis);
		}
		if(fabs(curPos - dPos) < 0.0001)	
		{
			return true;
		}

		if(m_bOrgFlag[axis]==false)
		{
			TCHAR	motorMSG[256];
			sTempLang.LoadStringA(IDS_STRING367);
			sLangChange.Format(sTempLang, axis+1);
			wsprintf(motorMSG, sLangChange);
			return false;
		}
	}
	else if(AbSFlag==REL)
	{
		//if (axis == Motor_PCB_Z || axis == Motor_Lens_Z || axis == Motor_Lens_Xt || axis == Motor_Lens_Yt || axis == Motor_PCB_Xt || axis == Motor_PCB_Yt || axis == Motor_PCB_Z 
		//	|| axis == Motor_PCB_TH || axis == Motor_LensAlign_TH || axis == Motor_LensAlign_Yt || axis == Motor_LensAlign_Xt || axis == Motor_LensLaser_Yt || axis == Motor_LensLaser_Xt)
		if (MOTOR_TYPE[axis] == STEPING)
		{
			dPos += GetCommandPos(axis);
		}else{
			dPos += GetEncoderPos(axis);
		}
	}

	dPos *= sysData.fMotorResol[axis];
	if(dPos>0)					dPos = (int)(dPos+0.5);

	long   axisAll[MAX_MOTOR_NO] = {0, };
	double posAll[MAX_MOTOR_NO] = {0, };
	double velAll[MAX_MOTOR_NO] = {0, };
	double accAll[MAX_MOTOR_NO] = {0, };
	double decAll[MAX_MOTOR_NO] = {0, };

	axisAll[0] = axis;
	posAll[0] = dPos;
	velAll[0] = dVel * sysData.fMotorResol[axis];
	accAll[0] = sysData.fMotorAccTime[axis]; //! 가속 가속도
	decAll[0] = sysData.fMotorAccTime[axis];

	//! 여러 개의 축에 대해서 현재의 위치에서 지정한 거리만큼 이동을 동시에 시작한다. 
	//! 이 함수를 사용하면 여러 개의 축이 동시에 작업을 시작한다. 
	//! 이 함수는 여러 축이 동기를 맞추어 작업을 시작해야 하는 경우에 사용한다. 
	//! 펄스 출력이 시작되는 시점에서 함수를 벗어난다.
	//AxmMoveStartMultiPos(1, axisAll, posAll, velAll, accAll, decAll);
	AxmMoveStartPos(axis, dPos, velAll[0], accAll[0], decAll[0]);

	Sleep(10);
	return true;
}


bool CAxlMotorSet::MoveAxisMulti(int iAxisCnt, short iAxis[MAX_MOTOR_NO], double pos[MAX_MOTOR_NO], int iSpeed)
{//! 여러 개의 축에 대해서 현재의 위치에서 지정한 거리만큼 이동을 동시에 시작한다
	long   axis2[MAX_MOTOR_NO] = {0, };
	double pos2[MAX_MOTOR_NO] = {0, };
	double vel[MAX_MOTOR_NO] = {0, };
	double acc[MAX_MOTOR_NO] = {0, };
	double dec[MAX_MOTOR_NO] = {0, };
	CString tmpStr;
	int iCnt =0;
	double curPos;

	for(int i=0; i<iAxisCnt; i++)
	{
		if(!m_bOrgFlag[iAxis[i]])
		{
			return false;
		}

		if(!IsStopAxis(iAxis[i]))
		{
			sLangChange.LoadStringA(IDS_STRING1239);
			tmpStr.Format(_T("[ %s ] ") + sLangChange + _T(" [MoveAxisMulti]"), MotorName[ iAxis[i] ]);
			errMsg2(Task.AutoFlag, tmpStr);
			return false;
		}

		if(MOTOR_TYPE[ iAxis[i] ] == STEPING)	curPos = GetCommandPos(iAxis[i]);
		else									curPos = GetEncoderPos(iAxis[i]); 

		
		//! Motor의 이동 목표 위치, 속도, 가속도/감속도 등을 알아낸다. 
		axis2[iCnt] = iAxis[i];
		pos2[iCnt] = pos[i] * sysData.fMotorResol[iAxis[i]];
		vel[iCnt] = sysData.fMotorSpeed[iAxis[i]] * sysData.fMotorResol[iAxis[i]];

#ifdef MOTOR_ACC_TYPE_SEC
		acc[iCnt] = sysData.fMotorAccTime[ iAxis[i] ];	//! 가속도
		dec[iCnt] = sysData.fMotorAccTime[ iAxis[i] ];	//! 감속도
#else
/*가속도 단위 (G)
-> 9.8m/s^2  X 1000mm/m   X   2000plses/mm     =      pls/s^2   */
		acc[iCnt] = sysData.fMotorAccTime[ iAxis[i] ] * (9.8 * 1000 *  sysData.fMotorResol[ iAxis[i] ]);//! 가속도 
		dec[iCnt] = sysData.fMotorDecTime[ iAxis[i] ] * (9.8 * 1000 *  sysData.fMotorResol[ iAxis[i] ]);//! 감속도
#endif

		if( fabs(pos2[i]-curPos) < 0.005) 			// 이동할 위치에서 5um 이상 차이가 없을때는 움직이지 않음.
			continue;
		else
			iCnt++;
	}

	if( iCnt == 0 )	return true;	//이동 범위가 없을 경우 Return

	//m_csMoveMulti.Lock();
	//! 여러 개의 축에 대해서 현재의 위치에서 지정한 거리만큼 이동을 동시에 시작한다. 
	//! 이 함수를 사용하면 여러 개의 축이 동시에 작업을 시작한다. 
	//! 이 함수는 여러 축이 동기를 맞추어 작업을 시작해야 하는 경우에 사용한다. 
	//! 펄스 출력이 시작되는 시점에서 함수를 벗어난다.
#ifdef ON_LINE_MOTOR
	AxmMoveStartMultiPos(iCnt, axis2, pos2, vel, acc, dec);
#endif

	//m_csMoveMulti.Unlock();

	return true;
}

//! 가속도 = 속도/(가속 시간)으로 계산
double CAxlMotorSet::CalcAccFromAccTime(double dVel, double dTime)
{
	double dRet = 0.;

	if ( fabs(dTime) < 0.001 )
	{
		//! 가속 시간이 너무 짧아서 강제로 가속 시간을 2 sec로 고정
		dRet = dVel / 2.;
	}
	else
	{
		dRet = dVel / dTime;
		dRet *= 1000.; //! 단위 변환 msec -> sec
	}

	return dRet;
}

int CAxlMotorSet::HomeSubReqProcess(int iAxis, int iStep, double &checkTime)
{
	CString sMsg;	
	int iRtnStep = iStep;
	double curTime = myTimer(true); 

	switch(iStep)
	{
	case 100:
		m_bOrgFlag[iAxis] = false;
		if( Start_Home_Search(iAxis) < 0 )
		{
			sLangChange.LoadStringA(IDS_STRING322);
			wsprintf(m_szLogMsg, sLangChange, MotorName[iAxis]);	//"[원점] %s (HOM) 원점 복귀 명령 실패."
			iRtnStep = -100;
			break;
		}

		checkTime = myTimer(true);
		iRtnStep = 200;
		break;

	case 200:
		{ 
			bool bHomeProc=true, bHomeError=true;

			int iHomFlag = motor.IsCompleted_Home_Search(iAxis);
			if( iHomFlag < 1 )	
				bHomeError = false;				//원점 동작 Error 정지 일 경우
			if( iHomFlag == 2 )	bHomeProc = false;				//원점 동작 진행 중일 경우.
			if( iHomFlag == 1 )
			{//! 정상적으로 원점이 검색 되었을 경우
				iRtnStep = 500;
			}
	
			if( bHomeError == false )	
			{//! 비정상 알람(원점 동작 정지)
				sLangChange.LoadStringA(IDS_STRING328);
				wsprintf(m_szLogMsg, sLangChange, MotorName[iAxis], iStep);		//"[원점] %s 원점 동작 Error 발생 정지.[STEP:%d]"
				iRtnStep = -200;
				break;
			}
			else if( bHomeProc == false )
			{//! 원점 동작이 끝이 안난 경우
				if((curTime - checkTime) > MOTOR_ORIGIN_TIME)
				{
					sLangChange.LoadStringA(IDS_STRING329);
					wsprintf(m_szLogMsg, sLangChange, MotorName[iAxis], iStep);	//"[원점] %s 원점 동작 이동 시간 초과..[STEP:%d]"
					iRtnStep = -200;
				}
			}
		}
		break;

	case 500:
		m_bOrgFlag[iAxis] = true;
		iRtnStep = 1000;
		break;

	}

	return iRtnStep;
}

int CAxlMotorSet::HomeSubProcess(int axis, int iStep, double &checkTime)
{
	////////////////////////////////////////////////////////
	// Lens X	Home (+)방향
	// Lens Y	Home (+)방향
	// Lens Z	Home (+)방향
	// Lens Tx	  -	 
	// Lens Ty	Home (-)방향
	// PCB X	Home (-)방향
	// PCB Y	Home (-)방향
	// PCB Z	  -	 
	////////////////////////////////////////////////////////
	CString sMsg="";	
	int iRtnStep = iStep;
	
	CString sLog="";
	DWORD dwReturn = 0;
	DWORD statusMechanical = 0;
	DWORD statusMotion = 0;

	double dAcc = sysData.fMotorAccTime[axis]*3;
	double dVel = sysData.fMotorResol[axis]*20;
	double curTime = myTimer(true); 

	if ((axis == Motor_Lens_Xt) || (axis == Motor_PCB_Xt) || (axis == Motor_PCB_Yt) || (axis == Motor_Lens_Z))
	{
		dVel /= 4;
	}



	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	if ((axis == Motor_Lens_X) || (axis == Motor_Lens_Y) || (axis == Motor_Lens_Z) || (axis == Motor_PCB_Z) ||
		(axis == Motor_Lens_Xt) /*|| (axis == Motor_PCB_TH)*/)
	{// Home (+)방향
		switch(iStep)
		{
		case 100:
			dwReturn = AxmMoveSignalSearch(axis, dVel, dAcc, PosEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP);
			Sleep(5);

			if ( dwReturn != AXT_RT_SUCCESS )
			{
				sLangChange.LoadStringA(IDS_STRING316);
				wsprintf(m_szLogMsg, sLangChange, MotorName[axis]);	//"[원점] %s (+) 이동 지령 실패."
				iRtnStep = -200;
			}
			else
			{
				checkTime = myTimer(true);
				iRtnStep = 200;
			}
			break;
		
		case 200:
//			if(IsStopAxis(axis))
			if(GetPosiSensor(axis) && IsStopAxis(axis))
			{
				if(axis == Motor_PCB_Z)
				{
					dwReturn = AxmMoveSignalSearch(axis, -dVel/4, dAcc, HomeSensor, SIGNAL_DOWN_EDGE, SLOWDOWN_STOP);
					if ( dwReturn != AXT_RT_SUCCESS )
					{
						sLangChange.LoadStringA(IDS_STRING324);
						wsprintf(m_szLogMsg, sLangChange, MotorName[axis]);	//"[원점] %s (HOM) 이동 지령 실패."
						iRtnStep = -200;
					}
					else
					{
						checkTime = myTimer(true);
						iRtnStep = 300;
					}
				}
				else
				{
					dwReturn = AxmMoveSignalSearch(axis, -dVel, dAcc, HomeSensor, SIGNAL_DOWN_EDGE, SLOWDOWN_STOP);
					if ( dwReturn != AXT_RT_SUCCESS )
					{
						sLangChange.LoadStringA(IDS_STRING324);	//[원점] %s (HOM) 이동 지령 실패.
						wsprintf(m_szLogMsg, sLangChange, MotorName[axis]);
						iRtnStep = -200;
					}
					else
					{
						checkTime = myTimer(true);
						iRtnStep = 300;
					}
				}
			}
			else if((curTime - checkTime) > MOTOR_MOVE_TIME)
			{
				StopAxis(axis);
				sLangChange.LoadStringA(IDS_STRING315);
				wsprintf(m_szLogMsg, sLangChange, MotorName[axis]);	//"[원점] %s (+) 센서 감지 시간 초과"
				iRtnStep = -200;
			}
			break;

		case 300:
//			if(IsStopAxis(axis))
			if(!GetHomeSensor(axis) && IsStopAxis(axis))
			{
				dwReturn = AxmMoveSignalSearch(axis, dVel/20, dAcc, HomeSensor, SIGNAL_UP_EDGE, EMERGENCY_STOP);
				if ( dwReturn != AXT_RT_SUCCESS )
				{
					sLangChange.LoadStringA(IDS_STRING320);
					wsprintf(m_szLogMsg, sLangChange, MotorName[axis]);	//"[원점] %s (HOM) 검색 지령 실패."
					iRtnStep = -300;
				}
				else
				{
					checkTime = myTimer(true);
					iRtnStep = 400;
				}
			}
			else if((curTime - checkTime) > MOTOR_MOVE_TIME)
			{
				StopAxis(axis);
				sLangChange.LoadStringA(IDS_STRING323);
				wsprintf(m_szLogMsg, sLangChange, MotorName[axis]);	//"[원점] %s (HOM) 이동 시간 초과"
				iRtnStep = -300;
			}
			break;

		case 400:
//			if(IsStopAxis(axis))
			if(GetHomeSensor(axis) && IsStopAxis(axis))
			{
				checkTime = myTimer(true);
				iRtnStep = 500;
			}
			else if((curTime - checkTime) > MOTOR_MOVE_TIME)
			{
				StopAxis(axis);
				sLangChange.LoadStringA(IDS_STRING319);
				wsprintf(m_szLogMsg, sLangChange, MotorName[axis]);	//"[원점] %s (HOM) 검색 시간 초과"
				iRtnStep = -400;
			}
			break;

		case 500:
			if((curTime - checkTime) > 2000)
			{
				AxmStatusSetActPos(axis, 0.);
				AxmStatusSetCmdPos(axis, 0.);
				m_bOrgFlag[axis] = true;
				iRtnStep = 1000;
			}
			break;
		}
	}
	else if( (axis == Motor_PCB_X) || (axis == Motor_PCB_Y) || (axis == Motor_PCB_TH))
	{// Home (-)방향
		switch(iStep)
		{
		case 100:
			//dwReturn = AxmMoveSignalSearch(axis, dVel, dAcc, HomeSensor, SIGNAL_DOWN_EDGE, EMERGENCY_STOP);
			dwReturn = AxmMoveSignalSearch(axis, -dVel, dAcc, NegEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP);
			Sleep(5);

			if ( dwReturn != AXT_RT_SUCCESS )
			{
				sLangChange.LoadStringA(IDS_STRING313);
				wsprintf(m_szLogMsg, sLangChange, MotorName[axis]);	//"[원점] %s (-) 이동 지령 실패."
				iRtnStep = -200;
			}
			else
			{
				checkTime = myTimer(true);
				iRtnStep = 200;
			}
			break;

		case 200:
			if(GetNegaSensor(axis) && IsStopAxis(axis))
			{
				// PNT 0829..
				if ((axis != Motor_Lens_Xt) && (axis != Motor_PCB_Xt) && (axis != Motor_PCB_Yt))	//-- 스태핑 모터가 아닐 경우만 위치 Setting
				{
					AxmStatusSetActPos(axis, 0.);
					AxmStatusSetCmdPos(axis, 0.);
				}

				dwReturn = AxmMoveSignalSearch(axis, dVel, dAcc, HomeSensor, SIGNAL_DOWN_EDGE, SLOWDOWN_STOP);

				if ( dwReturn != AXT_RT_SUCCESS )
				{
					sLangChange.LoadStringA(IDS_STRING324);
						wsprintf(m_szLogMsg, sLangChange, MotorName[axis]);	//"[원점] %s (HOM) 이동 지령 실패."
					iRtnStep = -200;
				}
				else
				{
					checkTime = myTimer(true);
					if ((axis != Motor_Lens_Xt) && (axis != Motor_PCB_Xt) && (axis != Motor_PCB_Yt))		iRtnStep = 300;
					else																				iRtnStep = 301;
				}
			}
			else if((curTime - checkTime) > MOTOR_MOVE_TIME)
			{
				StopAxis(axis);
				sLangChange.LoadStringA(IDS_STRING311);
				wsprintf(m_szLogMsg, sLangChange, MotorName[axis]);	//"[원점] %s (-) 센서 감지 시간 초과"
				iRtnStep = -200;
			}

			break;


		case 300:
			if ((axis != Motor_Lens_Xt) && (axis != Motor_PCB_Xt) && (axis != Motor_PCB_Yt))	//-- 스태핑 모터가 아닐 경우만 위치 Setting
			{
				if( GetEncoderPos(axis) > 100.0 ) //wook 0826  100mm
				//if( !GetHomeSensor(axis) && IsStopAxis(axis))
				{
					StopAxis(axis);
					sLangChange.LoadStringA(IDS_STRING326);
					wsprintf(m_szLogMsg, sLangChange, MotorName[axis],(int)GetEncoderPos(axis));	//"[원점] %s Home 센서 감지 거리(%02d [mm]) 초과"
					iRtnStep = -300;
					break;
				}
				if((curTime - checkTime) > MOTOR_MOVE_TIME)
				{
					StopAxis(axis);
					sLangChange.LoadStringA(IDS_STRING321);
					wsprintf(m_szLogMsg, sLangChange, MotorName[axis]);	//[원점] %s (HOM) 센서 감지 시간 초과"
					iRtnStep = -300;
					break;
				}
				if(!IsStopAxis(axis)) 
					break;
			}

			iRtnStep++;
			break;

		case 301:
			if(IsStopAxis(axis))
//			if(!GetHomeSensor(axis) && IsStopAxis(axis))
			{
				dwReturn = AxmMoveSignalSearch(axis, -dVel/20, dAcc, HomeSensor, SIGNAL_UP_EDGE, EMERGENCY_STOP);

				if ( dwReturn != AXT_RT_SUCCESS )
				{
					sLangChange.LoadStringA(IDS_STRING320);
					wsprintf(m_szLogMsg, sLangChange, MotorName[axis]);	//"[원점] %s (HOM) 검색 지령 실패."
					iRtnStep = -iRtnStep;
				}
				else
				{
					checkTime = myTimer(true);

					iRtnStep = 500;
				}
			}
			else if((curTime - checkTime) > MOTOR_MOVE_TIME)
			{
				StopAxis(axis);
				sLangChange.LoadStringA(IDS_STRING323);
				wsprintf(m_szLogMsg, sLangChange, MotorName[axis]);	//"[원점] %s (HOM) 이동 시간 초과"
				iRtnStep = -iRtnStep;
			}
			break;

		case 500:
			//if(IsStopAxis(axis))
			if(GetHomeSensor(axis) && IsStopAxis(axis))
			{
				if (axis == Motor_Lens_Xt || axis == Motor_PCB_Xt || axis == Motor_PCB_Yt)	//스태핑 모터의 경우 AMP OFF 이후 원점 Setting
				{
					AmpDisable(axis);
					checkTime = myTimer(true);
					iRtnStep = 510;	//--> 스태핑 모터만 
					break;
				}

				checkTime = myTimer(true);
				iRtnStep = 600;
			}
			else if((curTime - checkTime) > MOTOR_MOVE_TIME)
			{
				sLangChange.LoadStringA(IDS_STRING319);
				wsprintf(m_szLogMsg, sLangChange, MotorName[axis]);	//"[원점] %s (HOM) 검색 시간 초과"
				iRtnStep = -500;
			}
			break;
		case 510:
			if( GetAmpEnable(axis) == false)
			{
				iRtnStep = 600;
				break;
			}
			else if((curTime - checkTime) > IO_CHECK_TIME) //3초만
			{
				StopAxis(axis);
				sLangChange.LoadStringA(IDS_STRING327);
				wsprintf(m_szLogMsg, sLangChange, MotorName[axis]);	//"[원점] %s Servo Off 실패"
				iRtnStep = -600;
			}
			break;

		case 600:
			if((curTime - checkTime) > 2000)
			{
				AxmStatusSetActPos(axis, 0.);
				AxmStatusSetCmdPos(axis, 0.);

				if (axis == Motor_Lens_Xt || axis == Motor_PCB_Xt || axis == Motor_PCB_Yt)	//스태핑 모터의 경우 AMP OFF 이후 원점 Setting
				{
					AmpEnable(axis);
				}
				m_bOrgFlag[axis] = true;
				iRtnStep = 1000;
			}
			break;
		}
	}
	//else if((axis == Motor_Lens_Xt) ||(axis == Motor_Lens_Xt) )
	else if ((axis == Motor_PCB_Yt) || (axis == Motor_Lens_Xt) || (axis == Motor_PCB_Xt))
	{// - Limit 가 Home
		switch(iStep)
		{
		case 100:
			
			dwReturn = AxmMoveSignalSearch(axis, -dVel, dAcc, NegEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP);
			Sleep(5);

			if ( dwReturn != AXT_RT_SUCCESS )
			{
				sLangChange.LoadStringA(IDS_STRING313);
				wsprintf(m_szLogMsg, sLangChange, MotorName[axis]);	//"[원점] %s (-) 이동 지령 실패."
				iRtnStep = -100;
			}
			else
			{
				checkTime = myTimer(true);
				iRtnStep = 200;
			}
			break;

		case 200:
//			if(IsStopAxis(axis))
			if(GetNegaSensor(axis) && IsStopAxis(axis))
			{
				CString sLog;
				sTempLang.LoadStringA(IDS_STRING109);
				sLangChange.Format(sTempLang, MotorName[axis]);
				sLog.Format(sLangChange);
				pFrame->putListLog(sLog);
			
				checkTime = myTimer(true);
				iRtnStep = 250;
			}
			else if((curTime - checkTime) > MOTOR_MOVE_TIME)
			{
				StopAxis(axis);
				sLangChange.LoadStringA(IDS_STRING317);
				wsprintf(m_szLogMsg, sLangChange, MotorName[axis]);	//"[원점] %s (+)방향 이동 실패"
				iRtnStep = -200;
			}
			break;

		case 250:
			if( IsStopAxis(axis) )
			{
				double moveVal = 2;
				double moveDist = 0.5;
				dwReturn = MoveAxis(axis, false, moveDist, moveVal, (float)dAcc);	
				if ( dwReturn != TRUE ){
					sLangChange.LoadStringA(IDS_STRING325);
					wsprintf(m_szLogMsg, sLangChange, MotorName[axis]);	//"[원점] %s +0.5mm 이동 지령 실패 (Down)."
					iRtnStep = -250;
				} else {
					checkTime = myTimer(true);
					iRtnStep = 251;
				}
			}
			else if((curTime - checkTime) > MOTOR_MOVE_TIME)
			{
				StopAxis(axis);
				sLangChange.LoadStringA(IDS_STRING317);
				wsprintf(m_szLogMsg, sLangChange, MotorName[axis]);	//"[원점] %s (+)방향 이동 실패"
				iRtnStep = -250;
			}
			break;
		case 251:
			if( IsStopAxis(axis) )
			{
				if( GetHomeSensor(axis) )
				{//Home센서가 들어 왔을 경우 홈센서가 나갈때까지 +1mm씩 이동
					checkTime = myTimer(true);
					iRtnStep = 260;
				}
				else 
				{
					checkTime = myTimer(true);
					iRtnStep = 250;
				}
			}
			else if((curTime - checkTime) > MOTOR_MOVE_TIME)
			{
				StopAxis(axis);
				sLangChange.LoadStringA(IDS_STRING317);
				wsprintf(m_szLogMsg, sLangChange, MotorName[axis]);	//"[원점] %s (+)방향 이동 실패"
				iRtnStep = -251;
			}
			break;

		case 260:
			if(GetHomeSensor(axis) && IsStopAxis(axis))
			{//Home 센서가 계속 들어온 상태라면 안들어올때가지 +이동
				double moveVal = 2;
				double moveDist = 0.5;
				dwReturn = MoveAxis(axis, false, moveDist, moveVal, (float)dAcc);	
				if ( dwReturn != TRUE ){
					sLangChange.LoadStringA(IDS_STRING325);
					wsprintf(m_szLogMsg, sLangChange, MotorName[axis]);	//"[원점] %s +0.5mm 이동 지령 실패 (Down)."
					iRtnStep = -260;
				} else {
					checkTime = myTimer(true);
					iRtnStep = 261;
				}
			}
			else if( !GetHomeSensor(axis) && IsStopAxis(axis) )
			{
				checkTime = myTimer(true);
				iRtnStep = 300;
			}
			else if((curTime - checkTime) > MOTOR_MOVE_TIME)
			{
				StopAxis(axis);
				sLangChange.LoadStringA(IDS_STRING317);
				wsprintf(m_szLogMsg, sLangChange, MotorName[axis]);	//"[원점] %s (+)방향 이동 실패"
				iRtnStep = -260;
			}
			break;
		case 261:
			if( IsStopAxis(axis) )
			{
				if( !GetHomeSensor(axis) )
				{//Home센서가 Off일 경우 다음 Step
					checkTime = myTimer(true);
					iRtnStep = 300;
				}
				else 
				{
					checkTime = myTimer(true);
					iRtnStep = 260;
				}
			}
			else if((curTime - checkTime) > MOTOR_MOVE_TIME)
			{
				StopAxis(axis);
				sLangChange.LoadStringA(IDS_STRING317);
				wsprintf(m_szLogMsg, sLangChange, MotorName[axis]);	//"[원점] %s (+)방향 이동 실패"
				iRtnStep = -261;
			}
			break;

		case 300:
//			if(IsStopAxis(axis))
			if(!GetNegaSensor(axis) && IsStopAxis(axis))
			{
				CString sLog;
				sTempLang.LoadStringA(IDS_STRING110);
				sLangChange.Format(sTempLang, MotorName[axis]);
				sLog.Format(sLangChange);
				pFrame->putListLog(sLog);

				dwReturn = AxmMoveSignalSearch(axis, -dVel/20, dAcc, HomeSensor, SIGNAL_UP_EDGE, EMERGENCY_STOP);
				Sleep(5);

				if ( dwReturn != AXT_RT_SUCCESS )
				{
					sLangChange.LoadStringA(IDS_STRING312);
					wsprintf(m_szLogMsg, sLangChange, MotorName[axis]);	//"[원점] %s (-) 이동 지령 실패 (Up)."
					iRtnStep = -300;
				}
				else
				{
					checkTime = myTimer(true);
					iRtnStep = 400;
				}
			}
			else if((curTime - checkTime) > MOTOR_MOVE_TIME)
			{
				StopAxis(axis);
				sLangChange.LoadStringA(IDS_STRING314);
				wsprintf(m_szLogMsg, sLangChange, MotorName[axis]);	//"[원점] %s (-) 인식 시간 초과"
				iRtnStep = -300;
			}
			break;

		case 400:
			if(GetHomeSensor(axis) && IsStopAxis(axis))
			{

				checkTime = myTimer(true);
				iRtnStep = 500;
			}
			else if((curTime - checkTime) > MOTOR_MOVE_TIME)
			{
				StopAxis(axis);
				sLangChange.LoadStringA(IDS_STRING318);
				wsprintf(m_szLogMsg, sLangChange, MotorName[axis]);	//"[원점] %s (H) 인식 시간 초과2"
				iRtnStep = -400;
			}
			break;

		case 500:
			if((curTime - checkTime) > 1000)
			{
				if (axis == Motor_Lens_Xt || axis == Motor_PCB_Xt || axis == Motor_PCB_Yt)
				{//-- 스태핑은 전원 Off후 Set
					AmpDisable(axis);
					Sleep(100);
					checkTime = myTimer(true);
					iRtnStep = 600;
					break;
				}
				AxmStatusSetActPos(axis, 0.);
				AxmStatusSetCmdPos(axis, 0.);

				m_bOrgFlag[axis] = true;
				iRtnStep = 1000;
			}
			break;
		case 600:
			if(GetAmpEnable(axis) == false)
			{
				AxmStatusSetActPos(axis, 0.);
				AxmStatusSetCmdPos(axis, 0.);
				Sleep(100);
				AmpEnable(axis);
				m_bOrgFlag[axis] = true;
				iRtnStep = 1000;
			}
			else if((curTime - checkTime) > 10000/*IO_CHECK_TIME*/) //3초만
			{
				StopAxis(axis);
				sLangChange.LoadStringA(IDS_STRING327);
				wsprintf(m_szLogMsg, sLangChange, MotorName[axis]);	//"[원점] %s Servo Off 실패"
				iRtnStep = -600;
			}
			checkMessage();
		}
	}
	return iRtnStep;
}

bool CAxlMotorSet::HomeProcess(int axis)
{
	if ( axis < 0 || axis >= MAX_MOTOR_NO )		return false;

	if ( IsStopAxis(axis) == false )
	{//! Motor가 멈춘 상태인지 확인
		CString tmpStr;
		sLangChange.LoadStringA(IDS_STRING310);
		tmpStr.Format(sLangChange, MotorName[axis]);
		errMsg2(Task.AutoFlag, tmpStr);
		return false;
	}

	if(!AmpEnable(Motor_Lens_Z))
	{
		sLangChange.LoadStringA(IDS_STRING706);	//Lens Z 모터 서보 On 실패
		errMsg2(Task.AutoFlag, sLangChange);
		return false;
	}

	if(!AmpEnable(axis))
	{
		sLangChange.LoadStringA(IDS_STRING1280);	//서보 On 동작 실패
		errMsg2(Task.AutoFlag, sLangChange);
		return false;
	}


	m_bOrgFlag[axis] = false;
	bool bChk_Amp_Fault   = GetAmpFault(axis);

	if ( bChk_Amp_Fault == true )
	{
		AmpFaultReset(axis);
		Sleep(100);
	}

	if(axis!=Motor_Lens_Z && (!GetAmpEnable(Motor_Lens_Z)))
	{
		sLangChange.LoadStringA(IDS_STRING728);	//Lens 부 Z축이 Servo OFF 상태입니다.
		errMsg2(Task.AutoFlag, sLangChange);
		return false;
	}

	CString sLog;
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	sLangChange.LoadStringA(IDS_STRING165);
	sLog.Format(sLangChange, MotorName[axis]);	//[%s] 모터 원점 복귀 시작.
	pFrame->putListLog(sLog);


	CTimeChecker timeChk;
	double t_duration = 0.;
	double curTime, checkTime, OrginTime;

	double subTime = 0;
	int iStep = 100;
	int iHomeRtnStep = 0;

	OrginTime = myTimer(true);

	while (1)
	{
		bool bChk_Amp = GetAmpFault(axis);
		if(bChk_Amp)
		{
			sLangChange.LoadStringA(IDS_STRING1278);	//서보 Amp Fault 발생.
			errMsg2(Task.AutoFlag, sLangChange);
			return false;
		}

		bChk_Amp = GetAmpEnable(axis);
		if(!bChk_Amp)
		{//! 정상적인 Servo Off 시점을 제외한 나머지 알람.
			if (!(axis == Motor_Lens_Xt && iHomeRtnStep == 600) &&
				!(axis == Motor_PCB_Yt && iHomeRtnStep == 600) &&
				!(axis == Motor_PCB_Xt && iHomeRtnStep == 600))
			{
				sLangChange.LoadStringA(IDS_STRING1279);	//서보 Off 발생.
				errMsg2(Task.AutoFlag, sLangChange);
				return false;
			}
		}

		curTime = myTimer(true);

		switch(iStep)
		{
		case 100:
			checkTime = myTimer(true);
			if( m_bOrgFlag[Motor_Lens_Z] == true )
			{
				LENS_Z_Motor_Move(Wait_Pos);;
				iStep = 400;
			}
			else
			{
				AmpEnable(Motor_Lens_Z);
				iStep = 400;
			}
			break;

		case 400:
			if( IsStopAxis(Motor_Lens_Z) )
			{
				checkTime = myTimer(true);
				iStep = 900;
			}
			else if((curTime - checkTime) > MOTOR_MOVE_TIME)
			{
				sLangChange.LoadStringA(IDS_STRING337);
				errMsg2(Task.AutoFlag, sLangChange);
				iStep = -400;
			}
			break;

		//case 500:
		//	if(m_bOrgFlag[Motor_Laser_Z] == true)
		//	{
		//		Laser_Z_Motor_Move(Wait_Pos);;
		//		iStep = 510;
		//	}
		//	else
		//	{
		//		AmpEnable(Motor_Laser_Z);
		//		iStep = 510;
		//	}
		//	break;

		//case 510:
		//	if( IsStopAxis(Motor_Laser_Z) )
		//	{
		//		iHomeRtnStep = 100;	
		//		checkTime = myTimer(true);
		//		iStep = 900;
		//	}
		//	else if((curTime - checkTime) > MOTOR_MOVE_TIME)
		//	{
		//		sLangChange.LoadStringA(IDS_STRING332);
		//		errMsg2(Task.AutoFlag, sLangChange);
		//		iStep = -500;
		//	}
		//	break;

		case 900:
			if(m_bOrgFlag[axis] == true)
				iStep = 1000;
			break;
		}//main switch


		if(iHomeRtnStep >= 100 && iHomeRtnStep < 1000)
		{
			iHomeRtnStep = HomeSubReqProcess(axis, iHomeRtnStep, subTime);
			if(iHomeRtnStep < 0)
			{
				StopAxis(axis);
				errMsg2(Task.AutoFlag, m_szLogMsg);
				return false;
			}
		}

		if(iHomeRtnStep == 1000)
			break;

	

		if(iHomeRtnStep < 0 || iHomeRtnStep > 1000 ||
			iStep < 0 )
		{
			sLangChange.LoadStringA(IDS_STRING340);
			errMsg2(Task.AutoFlag, sLangChange);	//("[원점] 모터 원점 복귀 실패"
			return false;
		}

		if((curTime - OrginTime) > MOTOR_ORIGIN_TIME)
		{
			StopAxisAll();
			sLangChange.LoadStringA(IDS_STRING341);
			errMsg2(Task.AutoFlag, sLangChange);	//"[원점] 원점 복귀 시간 초과"
			return false;
		}

		checkMessage();
		Sleep(5);
		checkMessage();
	}

	return true;
}



bool CAxlMotorSet::HomeProcessAll()
{
	strMove_Input_Signal_Search strTemp;
	CString sLog = "";
	CTimeChecker timeChk;
	double t_duration = 0.0;

	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	sLog.Format("전체 모터를 원점 복귀 합니다.");	//전체 모터 원점 복귀 시작.
	pFrame->putListLog(sLog);

	sLangChange.LoadStringA(IDS_STRING1332);//"원점 복귀중"
	pFrame->m_labelHom.SetBkColor(M_COLOR_GRAY);
	pFrame->m_labelHom.SetText(sLangChange);
	pFrame->m_labelHom.Invalidate();

	pFrame->m_btnOrigin.m_iStateBtn = 0;
	pFrame->m_btnOrigin.Invalidate();


	StopAxisAll();
	Sleep(10);

	for (int i = Motor_Lens_X; i <= Motor_PCB_TH; i++)
	{
		m_bOrgFlag[i] = false;

		if (IsStopAxis(i) == false)
		{
			sLangChange.LoadStringA(IDS_STRING1244);
			sLog.Format(_T("[%s] ") + sLangChange, MotorName[i]);	//모터가 동작 중 입니다
			errMsg2(Task.AutoFlag, sLog);
			return false;
		}

		bool bChk_Amp_Fault = GetAmpFault(i);

		if (bChk_Amp_Fault == true)
		{
			sLangChange.LoadStringA(IDS_STRING1223);
			sLog.Format(_T("[%s] ") + sLangChange, MotorName[i]);		//모터 Home AmpFault 상태
			errMsg2(Task.AutoFlag, sLog);
			return false;
		}
	}

	if (!AmpEnableAll())
	{
		sLangChange.LoadStringA(IDS_STRING1329);
		errMsg2(Task.AutoFlag, sLangChange);	//"원점 복귀 중 전체 서보 On 실패"
		return false;
	}

	int MainStep = 100;
	int iStep[MAX_MOTOR_NO];
	double iTime[MAX_MOTOR_NO];

	for (int i = 0; i<MAX_MOTOR_NO; i++)
	{
		iStep[i] = 0;	// 100부터 시작
		iTime[i] = 0;
	}

	double dAcc = 0.0;
	double dVel = 0.0;

	double curTime, checkTime, OriginStartTime;

	double dSpeed = 15.0f;
	OriginStartTime = myTimer(true);
	CString logStr = "";
	while (1)
	{
		int bChk_Amp = AmpFaultCheck();
		if (bChk_Amp)
		{
			sLangChange.LoadStringA(IDS_STRING1278);	//서보 Amp Fault 발생.
			errMsg2(Task.AutoFlag, sLangChange);
			return false;
		}
		for (int i = 0; i<MAX_MOTOR_NO; i++)
		{
			if (!GetAmpEnable(i))
			{
				if (!(i == Motor_Lens_Xt  && iStep[Motor_Lens_Xt] == 600) &&
					!(i == Motor_PCB_Xt  && iStep[Motor_PCB_Xt] == 600) &&
					!(i == Motor_PCB_Yt  && iStep[Motor_PCB_Yt] == 600))
				{
					sLangChange.LoadStringA(IDS_STRING1279);	//서보 Off 발생.
					errMsg2(Task.AutoFlag, sLangChange);
					return false;
				}
			}
		}

		curTime = myTimer(true);
		//motor.InDIO(0, curInDio[0]);
		motor.InDIO(2, curInDio[1]);
		switch (MainStep)
		{
		case 100:
			if (Dio.CamLaserSlinderMove(false, false))
			{
				MainStep = 150;
			}
			else
			{
				logStr.Format("Laser/Cam 실린더 후진 실패");
				errMsg2(Task.AutoFlag, logStr);
			}
			Task.PCBTaskTime = myTimer(true);
			break;
		case 150:
			if (Dio.CamLaserSlinderCheck(false, false))
			{
				logStr.Format("Laser/Cam 실린더 후진 완료");
				theApp.MainDlg->putListLog(logStr);
				MainStep = 200;
			}
			else if ((myTimer(true) - Task.PCBTaskTime) > IO_DELAY_TIME)
			{
				logStr.Format("Laser/Cam 실린더 후진 시간 초과");
				errMsg2(Task.AutoFlag, logStr);
				MainStep = -150;
			}
			break;
		case 200:
			/*if(!Dio.LensMotorGrip(false, false))
			{
			sLangChange.LoadStringA(IDS_STRING334);
			errMsg2(Task.AutoFlag, sLangChange);
			MainStep = -200;
			break;
			}
			Task.PCBTaskTime = myTimer(true);*/
			MainStep = 210;
			break;

		case 210:
			/*if(Dio.LensMotorGripCheck(false, false))
			{
			MainStep = 300;
			}
			else if((myTimer(true) - Task.PCBTaskTime) > IO_DELAY_TIME)
			{
			sLangChange.LoadStringA(IDS_STRING333);
			errMsg2(Task.AutoFlag, sLangChange);
			MainStep = -210;
			}*/
			MainStep = 300;
			break;

		case 300:
			dAcc = sysData.fMotorAccTime[Motor_Lens_Z];
			dVel = 10 * sysData.fMotorResol[Motor_Lens_Z];
			AxmMoveVel(Motor_Lens_Z, dVel, dAcc, dAcc);
			checkTime = myTimer(true);
			MainStep = 400;
			break;
		case 400:
			if (GetPosiSensor(Motor_Lens_Z) && IsStopAxis(Motor_Lens_Z))
			{
				dAcc = sysData.fMotorAccTime[Motor_PCB_Z];
				dVel = 10 * sysData.fMotorResol[Motor_PCB_Z];
				AxmMoveVel(Motor_PCB_Z, -dVel, dAcc, dAcc);		// 음수 이동
				checkTime = myTimer(true);
				MainStep = 405;//410;
			}
			else if ((curTime - checkTime) > MOTOR_MOVE_TIME)
			{
				//sLangChange.LoadStringA(IDS_STRING337);
				errMsg2(Task.AutoFlag, "[원점] Lens Z축 (+)이동 실패");
				MainStep = -400;
			}
			break;

		case 405://! PCB Z축 (-) Limit 위치 이동
			if (GetNegaSensor(Motor_PCB_Z) && IsStopAxis(Motor_PCB_Z))
			{
				dAcc = sysData.fMotorAccTime[Motor_PCB_Y];
				dVel = 50 * sysData.fMotorResol[Motor_PCB_Y];
				AxmMoveVel(Motor_PCB_Y, -dVel, dAcc, dAcc);		// 음수 이동
				checkTime = myTimer(true);
				MainStep = 410;
			}
			else if ((curTime - checkTime) > MOTOR_MOVE_TIME)
			{
				//sLangChange.LoadStringA(IDS_STRING338);
				sLangChange.Format("PCB Z-Axis Move Fail");
				errMsg2(Task.AutoFlag, sLangChange);
				MainStep = -405;
			}
			break;

		case 410://! Lens Y축 (+) Limit 위치 이동
			if (GetNegaSensor(Motor_PCB_Y) && IsStopAxis(Motor_PCB_Y))

			{
				dAcc = sysData.fMotorAccTime[Motor_Lens_Y];
				dVel = 35 * sysData.fMotorResol[Motor_Lens_Y];
				AxmMoveVel(Motor_Lens_Y, dVel, dAcc, dAcc);
				checkTime = myTimer(true);
				MainStep = 500;
			}
			else if ((curTime - checkTime) > MOTOR_MOVE_TIME)
			{
				sLangChange.LoadStringA(IDS_STRING338);
				errMsg2(Task.AutoFlag, sLangChange);
				MainStep = -410;
			}
			break;

		case 500://! Lens X축 (+) Limit 위치 이동
			if (GetPosiSensor(Motor_Lens_Y) && IsStopAxis(Motor_Lens_Y))
			{
				dAcc = sysData.fMotorAccTime[Motor_Lens_X];
				dVel = 15 * sysData.fMotorResol[Motor_Lens_X];
				AxmMoveVel(Motor_Lens_X, dVel, dAcc, dAcc);
				checkTime = myTimer(true);
				MainStep = 550;
			}
			else if ((curTime - checkTime) > MOTOR_MOVE_TIME)
			{
				sLangChange.LoadStringA(IDS_STRING336);
				errMsg2(Task.AutoFlag, sLangChange);
				MainStep = -500;
			}
			break;

		case 550://! PCB Y축 (-) Limit 위치 이동
			if (GetPosiSensor(Motor_Lens_X) && IsStopAxis(Motor_Lens_X))
			{
				dAcc = sysData.fMotorAccTime[Motor_PCB_X];
				dVel = 20 * sysData.fMotorResol[Motor_PCB_X];
				AxmMoveVel(Motor_PCB_X, -dVel, dAcc, dAcc);
				checkTime = myTimer(true);
				MainStep = 600;
			}
			else if ((curTime - checkTime) > MOTOR_MOVE_TIME)
			{
				sLangChange.LoadStringA(IDS_STRING335);
				errMsg2(Task.AutoFlag, sLangChange);
				MainStep = -550;
			}
			break;
		case 600:
			if (GetNegaSensor(Motor_PCB_X) && IsStopAxis(Motor_PCB_X))
			{
				iStep[Motor_Lens_Y] = 100;	// Lens Y 원점 시작
				checkTime = myTimer(true);
				MainStep = 800;
			}
			else if ((curTime - checkTime) > MOTOR_MOVE_TIME)
			{
				sLangChange.LoadStringA(IDS_STRING335);
				errMsg2(Task.AutoFlag, "[원점] Pcb X축 (+)이동 실패");
				MainStep = -550;
			}
			break;
		case 800:
			//if(m_bOrgFlag[Motor_Lens_Y] == true)
			//{// 전체 Home 시작
			iStep[Motor_PCB_Y] = 100;	// PCB Y 원점 시작
			iStep[Motor_PCB_X] = 100;
			iStep[Motor_Lens_X] = 100;
			iStep[Motor_Lens_Z] = 100;
			iStep[Motor_Lens_Xt] = 100;
			iStep[Motor_Lens_Yt] = 100;
			iStep[Motor_PCB_TH] = 100;
			iStep[Motor_PCB_Xt] = 100;
			iStep[Motor_PCB_Yt] = 100;
			iStep[Motor_PCB_Z] = 100;
			MainStep = 900;
			//}
			break;

		case 900:
			if ((m_bOrgFlag[Motor_Lens_X] == true) && (m_bOrgFlag[Motor_Lens_Y] == true) && (m_bOrgFlag[Motor_Lens_Z] == true) && (m_bOrgFlag[Motor_Lens_Xt] == true) &&
				(m_bOrgFlag[Motor_Lens_Yt] == true) && (m_bOrgFlag[Motor_PCB_X] == true) && (m_bOrgFlag[Motor_PCB_Y] == true) && (m_bOrgFlag[Motor_PCB_TH] == true) &&
				(m_bOrgFlag[Motor_PCB_Xt] == true) && (m_bOrgFlag[Motor_PCB_Yt] == true) && (m_bOrgFlag[Motor_PCB_Z] == true))
			{//! 전체 원점 검색 완료 Check
				MainStep = 1000;
			}
			break;
		}//main switch

		for (int i = 0; i< MAX_MOTOR_NO; i++)
		{
			if (iStep[i] >= 100 && iStep[i] < 1000)
			{
				iStep[i] = HomeSubReqProcess(i, iStep[i], iTime[i]);
				if (iStep[i] < 0)
				{
					StopAxisAll();
					errMsg2(Task.AutoFlag, m_szLogMsg);
					return false;
				}
			}
		}

		if (MainStep == 1000)	break;
		if (MainStep < 0 || MainStep > 1000)
		{
			sLangChange.LoadStringA(IDS_STRING343);
			errMsg2(Task.AutoFlag, sLangChange);	//[원점] 전체 원점 복귀 실패

			sLangChange.LoadStringA(IDS_STRING1333);
			pFrame->m_labelHom.SetText(sLangChange);	//"원점복귀 실패"
			pFrame->m_labelHom.SetBkColor(M_COLOR_RED);
			pFrame->m_labelHom.Invalidate();

			pFrame->m_btnOrigin.m_iStateBtn = 2;
			pFrame->m_btnOrigin.Invalidate();

			return false;
		}

		if ((curTime - OriginStartTime) > MOTOR_ORIGIN_TIME * 1000)
		{
			StopAxisAll();
			sLangChange.LoadStringA(IDS_STRING342);
			errMsg2(Task.AutoFlag, sLangChange);	//[원점] 전체 원점 복귀 시간 초과

			sLangChange.LoadStringA(IDS_STRING1333);
			pFrame->m_labelHom.SetText(sLangChange);	//"원점복귀 실패"
			pFrame->m_labelHom.SetBkColor(M_COLOR_RED);
			pFrame->m_labelHom.Invalidate();

			pFrame->m_btnOrigin.m_iStateBtn = 2;
			pFrame->m_btnOrigin.Invalidate();

			return false;
		}
		checkMessage();
		Sleep(5);
		checkMessage();
	}

	sLangChange.LoadStringA(IDS_STRING1334);
	pFrame->m_labelHom.SetText(sLangChange);	//"원점복귀 완료"
	pFrame->m_labelHom.SetBkColor(M_COLOR_GREEN);
	pFrame->m_labelHom.Invalidate();

	pFrame->m_btnOrigin.m_iStateBtn = 1;
	pFrame->m_btnOrigin.Invalidate();

	return true;
}
int CAxlMotorSet::HomeCheck()
{
	int iHomeCheckFlag = 0;
	for (int i = 0; i<MAX_MOTOR_NO; i++)
	{
		if (bThreadTaskReadyRun == true && i == Motor_Lens_Xt)//if (bThreadTaskReadyRun == true && i==Motor_Lens_Yt && i==Motor_PCB_Yt&& i==Motor_PCB_Xt)	
			continue;
		if (m_bOrgFlag[i] == false)
			iHomeCheckFlag += 0x01 << i;
	}

	Task.iHomeErrorFlag = iHomeCheckFlag;
	return iHomeCheckFlag;
}

bool CAxlMotorSet::Lens_Motor_Align_Move(double offsetX, double offsetY, double offsetTh)
{
	double eTime;
	short axis[4];	/* axis[0] : X , axis[1] : Y , axis[2] : Z , axis[3] : Theta */
	double pos[4];	/* axis[0] : X , axis[1] : Y , axis[2] : Z , axis[3] : Theta */

	char logMsg[1000];


	double d_dist_X		= model.axis[Motor_Lens_X].pos[Lens_Pos] + offsetX ;	
	double d_dist_Y		= model.axis[Motor_Lens_Y].pos[Lens_Pos] + offsetY;	
	
	for (int i=Motor_Lens_X; i<=Motor_Lens_Y; i++)
	{
		if(i==Motor_Lens_Z)
			continue;


		if(!m_bOrgFlag[i])
		{
			sLangChange.LoadStringA(IDS_STRING198);
			sTempLang.Format(sLangChange, MotorName[i]);
			_stprintf_s(logMsg, sTempLang);	//"[Lens 부] %s 모터가 원점 복귀를 하지 않았습니다."
			errMsg2(Task.AutoFlag, logMsg);

			return false;
		}

		axis[i-Motor_Lens_X]	= i;
				
		if(i==Motor_Lens_X)				pos[i-Motor_Lens_X]	= model.axis[i].pos[Lens_Pos] + offsetX;		/* Align 위치부터 이동 */
		else if(i==Motor_Lens_Y)		pos[i-Motor_Lens_X]	= model.axis[i].pos[Lens_Pos] + offsetY;		/* Align 위치부터 이동 */
	}


	double MotorPos[2];
// 	MotorPos[0] = GetEncoderPos(Motor_Lens_X) - model.axis[Motor_Lens_X].pos[Align_Pos];
// 	MotorPos[1] = GetEncoderPos(Motor_Lens_Y) - model.axis[Motor_Lens_Y].pos[Align_Pos];

	MotorPos[0] = GetEncoderPos(Motor_Lens_X);
	MotorPos[1] = GetEncoderPos(Motor_Lens_Y);

	if(fabs(MotorPos[0]-model.axis[Motor_Lens_X].pos[Lens_Pos]) > model.axis[Motor_Lens_X].m_dLimit_Err)
	{
		sLangChange.LoadStringA(IDS_STRING196);
		_stprintf_s(logMsg, sLangChange, model.axis[Motor_Lens_X].m_dLimit_Err, model.axis[Motor_Lens_X].pos[Lens_Pos], MotorPos[0]);
		errMsg2(Task.AutoFlag, logMsg);
		return false;
	}

	if(fabs(MotorPos[1]-model.axis[Motor_Lens_Y].pos[Lens_Pos]) > model.axis[Motor_Lens_Y].m_dLimit_Err)
	{
		sLangChange.LoadStringA(IDS_STRING197);
		_stprintf_s(logMsg, sLangChange, model.axis[Motor_Lens_Y].m_dLimit_Err, model.axis[Motor_Lens_Y].pos[Lens_Pos], MotorPos[1]);
		errMsg2(Task.AutoFlag, logMsg);
		return false;
	}


	double startTime = myTimer(true);

	int step=0;

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif

	while(1)
	{
		switch(step)
		{
		case 0:			
			goMotorPos(2, axis, pos);			// X, Y
			step = 10;
			break;

		case 10:
			step = 100;
			break;

		case 100:								// 이동 완료 확인..
			if( IsStopAxis(Motor_Lens_X) && GetInposition(Motor_Lens_X) )		step = 101;
			break;

		case 101:
			if( IsStopAxis(Motor_Lens_Y) && GetInposition(Motor_Lens_Y) )		step = 1000;
			break;		
			
		default:
			break;
		}

		if(step==1000)
			break;


		eTime = myTimer(true);
		if(eTime-startTime > MOTOR_MOVE_TIME)
		{
			if(step>100)
			{
				int motorNo = step - 100;	
				sLangChange.LoadStringA(IDS_STRING723);	//Lens 부 [%s 모터] 이동 시간 초과
				_stprintf_s(logMsg, sLangChange, MotorName[motorNo]);
			}
			else
			{
				sLangChange.LoadStringA(IDS_STRING734);	//Lens 부 이동 비정상
				_stprintf_s(logMsg, sLangChange);
			}
			errMsg2(Task.AutoFlag, logMsg);

			return false;
		}

		Sleep(5);
		checkMessage();
	}

	return true;
}


bool CAxlMotorSet::Lens_Tilt_Motor_Move(int index, double offsetX, double offsetY)
{
	char logMsg[1000];
	double eTime;
	short axis[3];
	double pos[3];
	int axis_cnt = 0;
	double dOffsetLimit = 1.0;

	for (int i = Motor_Lens_Xt; i <= Motor_Lens_Yt; i++)
	{
		if (!m_bOrgFlag[i])
		{
			sTempLang.LoadStringA(IDS_STRING108);
			sLangChange.Format(sTempLang, MotorName[i]);
			_stprintf_s(logMsg, sLangChange);
			errMsg2(Task.AutoFlag, logMsg);
			return false;
		}

		/*axis[i-Motor_Lens_Xt]		= i;

		if(i==Motor_Lens_Xt)				pos[i-Motor_Lens_Xt]	= model.axis[i].pos[index] + offsetX;
		else if(i==Motor_Lens_Yt)			pos[i-Motor_Lens_Yt]	= model.axis[i].pos[index] + offsetY;*/
	}


	double MotorPos[2];

	MotorPos[0] = GetCommandPos(Motor_Lens_Xt) - model.axis[Motor_Lens_Xt].pos[index];
	MotorPos[1] = GetEncoderPos(Motor_Lens_Yt) - model.axis[Motor_Lens_Yt].pos[index];

	if (fabs(MotorPos[0]) > 4.1)//model.axis[Motor_Lens_Xt].m_dLimit_Err)
	{
		sLangChange.LoadStringA(IDS_STRING688);	//LENS TX 모터가 Limit를 벗어 났습니다. [Encoder %.03lf, Teaching %.03lf]
		_stprintf_s(logMsg, sLangChange, GetCommandPos(Motor_Lens_Xt), model.axis[Motor_Lens_Xt].pos[index]);
		errMsg2(Task.AutoFlag, logMsg);
		return false;
	}

	if (fabs(MotorPos[1]) > 4.1)//model.axis[Motor_Lens_Yt].m_dLimit_Err)
	{
		sLangChange.LoadStringA(IDS_STRING692);	//LENS TY 모터가 Limit를 벗어 났습니다. [Encoder %.03lf, Teaching %.03lf]
		_stprintf_s(logMsg, sLangChange, GetEncoderPos(Motor_Lens_Yt), model.axis[Motor_Lens_Yt].pos[index]);
		errMsg2(Task.AutoFlag, logMsg);
		return false;
	}
	axis[0] = Motor_Lens_Xt;
	axis[1] = Motor_Lens_Yt;	//axis[0]		= Motor_Lens_Yt;

	pos[0] = model.axis[Motor_Lens_Xt].pos[index];// + offsetX;
	pos[1] = model.axis[Motor_Lens_Yt].pos[index];// + offsetX;

	int step = 0;

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif

	double startTime;

	while (1)
	{
		switch (step)
		{
		case 0:									// 2축 모터 대기 위치로 이동 명령..
			startTime = myTimer(true);
			goMotorPos(2, axis, pos);
			step = 100;
			break;

		case 100:								// 이동 완료 확인..
			if (IsStopAxis(Motor_Lens_Xt))			step = 101;
			break;

		case 101:
			if (IsStopAxis(Motor_Lens_Yt))		step = 1000;
			break;

		default:
			break;
		}

		if (step == 1000)
			break;


		eTime = myTimer(true);
		if (eTime - startTime > MOTOR_MOVE_TIME)
		{
			StopAxis(Motor_Lens_Xt);
			StopAxis(Motor_Lens_Yt);

			if (step>100)
			{
				int motorNo = step - 100;
				sLangChange.LoadStringA(IDS_STRING723);	//Lens 부 [%s 모터] 이동 시간 초과
				_stprintf_s(logMsg, sLangChange, MotorName[motorNo]);
			}
			else
			{
				sLangChange.LoadStringA(IDS_STRING735);	//LENS 부 틸팅축 이동 시간 초과
				_stprintf_s(logMsg, sLangChange);
			}

			errMsg2(Task.AutoFlag, logMsg);

			return false;
		}

		Sleep(5);
		checkMessage();
	}

	return true;
}

bool CAxlMotorSet::Lens_Motor_Conti_Down(int index, bool waitFlag)
{
	double eTime = 0.0;
	short axis[1];
	double pos[1];
	CString logStr = "";
	double LensDownHeight = 1.0;
	LensDownHeight = fabs(model.m_ContiDownOffset);// (double)atof(logStr);
	double dWaitZPos = model.axis[Motor_Lens_Z].pos[Wait_Pos];
	if (LensDownHeight > 15.0)
	{
		LensDownHeight = 15.0;
	}
	axis[0] = index;
	pos[0] = GetEncoderPos(index) - LensDownHeight;
	logStr.Format("%s 모터 이동 합니다.", MotorPosName[index]);
	int step = 0;
	double startTime = 0.0;
	goMotorPos(1, axis, pos);

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif

	while (waitFlag)
	{
		switch (step)
		{
		case 0:
			startTime = myTimer(true);
			step = 100;
			break;
		case 100:								// 이동 완료 확인..
			if (IsStopAxis(index)) //if (IsStopAxis(Motor_Lens_Z))
			{
				step = 1000;
			}
			break;

		default:
			break;
		}
		if (step == 1000) {
			break;
		}
		eTime = myTimer(true);
		if ((eTime - startTime)>MOTOR_MOVE_TIME)
		{
			if (step>100)
			{
				logStr.Format("%s 이동 시간 초과", MotorPosName[index]);
			}
			else
			{
				logStr.Format("%s 이동 동 비정상", MotorPosName[index]);
			}
			errMsg2(Task.AutoFlag, logStr);
			return false;
		}
		Sleep(5);
	}
	return true;
}

bool CAxlMotorSet::Lens_Motor_Move(int index, double offsetX, double offsetY, double offsetTh)
{
	double eTime;
	short axis[6];
	double pos[6];

	char logMsg[1000];

	for (int i = 0; i<MAX_MOTOR_NO; i++)
	{
		if (!m_bOrgFlag[i])
		{
			sLangChange.LoadStringA(IDS_STRING1246);	//모터가 원점 복귀를 하지 않았습니다.
			_stprintf_s(logMsg, _T("%s ") + sLangChange, MotorName[i]);
			errMsg2(Task.AutoFlag, logMsg);
			return false;
		}
	}

	if (index<Wait_Pos || index>Dispense_Pos3)//Bonding_Pos)
	{
		sLangChange.LoadStringA(IDS_STRING729);	//Lens 부 모터 이동 위치가 비정상입니다.
		_stprintf_s(logMsg, sLangChange + _T(" [index : %d]"), index);
		errMsg2(Task.AutoFlag, logMsg);

		return false;
	}

	//if(index==Bonding_Pos)
	//{
	//	double dMotor = GetEncoderPos(Motor_PCB_Y) - model.axis[Motor_PCB_Y].pos[index];

	//	if(dMotor > -model.axis[Motor_PCB_Y].m_dLimit_Err)
	//	{
	//		bool b_pcb_push_state = Dio.PCBCoverCloseCheck(true, false);
	//		if (b_pcb_push_state == false)
	//		{
	//			sLangChange.LoadStringA(IDS_STRING1026);	//PCB부 커버 소켓이 열려 있습니다.
	//			_stprintf_s(logMsg, sLangChange);
	//			errMsg2(Task.AutoFlag, logMsg);
	//			return false;
	//		}
	//	}

	//	//Dio.BackLightOn(false, true);
	//}




	int step = 0;
	double startTime = 0.0;


	bool b_Z_Move_Flag = false;
	double d_dist_X = model.axis[Motor_Lens_X].pos[index] - GetEncoderPos(Motor_Lens_X);
	double d_dist_Y = model.axis[Motor_Lens_Y].pos[index] - GetEncoderPos(Motor_Lens_Y);

	if (fabs(d_dist_X)>model.axis[Motor_Lens_X].m_dLimit_Err || fabs(d_dist_Y)>model.axis[Motor_Lens_Y].m_dLimit_Err)
	{
		axis[0] = Motor_Lens_Z;		// Z, Tilx X, Tilt Y 축 대기 위치 이동 후 X, Y, Θ, Tx, Ty 동작, 동작 완료 후 Z 동작..
		axis[1] = Motor_Lens_Xt;
		axis[2] = Motor_Lens_Yt;

		pos[0] = model.axis[Motor_Lens_Z].pos[index];
		pos[1] = model.axis[Motor_Lens_Xt].pos[index];
		pos[2] = model.axis[Motor_Lens_Yt].pos[index];


		step = 0;

		while (1)
		{
			switch (step)
			{
			case 0:									// 5축 모터 대기 위치로 이동 명령..
				goMotorPos(3, axis, pos);			// Z, Xt, Yt
				startTime = myTimer(true);
				step = 100;
				break;

			case 100:								// 이동 완료 확인..
				if (IsStopAxis(Motor_Lens_Z))		step = 101;
				break;

			case 101:
				if (IsStopAxis(Motor_Lens_Xt))		step = 102;
				break;

			case 102:
				if (IsStopAxis(Motor_Lens_Yt))	step = 1000;
				break;

			default:
				break;
			}

			if (step == 1000)
				break;


			eTime = myTimer(true);
			if (eTime - startTime>MOTOR_MOVE_TIME)
			{
				if (step>100)
				{
					int motorNo = step - 100;
					sLangChange.LoadStringA(IDS_STRING722);	//Lens 부 [%s 모터] %s 이동 시간 초과
					_stprintf_s(logMsg, sLangChange, MotorName[motorNo], MotorPosName[index]);
				}
				else
				{
					sLangChange.LoadStringA(IDS_STRING720);	//Lens 부 %s 이동 비정상
					_stprintf_s(logMsg, sLangChange, MotorPosName[index]);
				}
				errMsg2(Task.AutoFlag, logMsg);

				return false;
			}

			Sleep(5);
			checkMessage();
		}
	}

	for (int i = Motor_Lens_X; i <= Motor_Lens_Xt; i++)
	{
		//clear_status(i);

		if (!m_bOrgFlag[i])
		{
			sTempLang.LoadStringA(IDS_STRING108);
			sLangChange.Format(sTempLang, MotorName[i]);
			_stprintf_s(logMsg, sLangChange);
			errMsg2(Task.AutoFlag, logMsg);
			return false;
		}

		axis[i - Motor_Lens_X] = i;

		if (index == Bonding_Pos)								// Bonding_Pos 이동 시 Align 위치에서 인식한 x, y, Theta 보정값 적용..
		{
			if (fabs(offsetX)>model.axis[Motor_Lens_X].m_dLimit_Err || fabs(offsetY)>model.axis[Motor_Lens_Y].m_dLimit_Err)
			{
				sLangChange.LoadStringA(IDS_STRING733);	//Lens 부 보정값이 비정상입니다
				sprintf_s(logMsg, sLangChange, offsetX, offsetY);
				errMsg2(Task.AutoFlag, logMsg);
				return false;
			}

			if (i == Motor_Lens_X)				pos[i - Motor_Lens_X] = model.axis[i].pos[index] + offsetX;
			else if (i == Motor_Lens_Y)		pos[i - Motor_Lens_X] = model.axis[i].pos[index] + offsetY;
			else if (i == Motor_Lens_Z)		pos[i - Motor_Lens_X] = model.axis[i].pos[index];
			else							pos[i - Motor_Lens_X] = model.axis[i].pos[index];
		}
		else
			pos[i - Motor_Lens_X] = model.axis[i].pos[index];
	}

	int b_bonding_move_flag = 0;

	if (index == Bonding_Pos || index == Loading_Pos)
	{
		b_bonding_move_flag = 1;
	}
	else
	{
		double d_x_pos = abs(GetEncoderPos(Motor_Lens_X) - model.axis[Motor_Lens_X].pos[Bonding_Pos]);
		double d_y_pos = abs(GetEncoderPos(Motor_Lens_Y) - model.axis[Motor_Lens_Y].pos[Bonding_Pos]);
		double d_x2_pos = abs(GetEncoderPos(Motor_Lens_X) - model.axis[Motor_Lens_X].pos[Loading_Pos]);
		double d_y2_pos = abs(GetEncoderPos(Motor_Lens_Y) - model.axis[Motor_Lens_Y].pos[Loading_Pos]);

		// PCB x, y 모터가 본딩 위치 근처에 있으면..
		if ((d_x_pos<model.axis[Motor_Lens_X].m_dLimit_Err) && (d_y_pos<model.axis[Motor_Lens_Y].m_dLimit_Err) || (d_x2_pos<model.axis[Motor_Lens_X].m_dLimit_Err) && (d_y2_pos<model.axis[Motor_Lens_Y].m_dLimit_Err))
		{
			b_bonding_move_flag = 2;
		}
		//b_bonding_move_flag = 2;
		else		b_bonding_move_flag = 0;
	}

	sLangChange.LoadStringA(IDS_STRING721);//Lens 부 %s로 이동 합니다.	
	_stprintf_s(logMsg, sLangChange, MotorPosName[index]);
	//	delayMsg(logMsg, 10000, M_COLOR_BLUE);


	startTime = myTimer(true);
	step = 0;

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif

	while (1)
	{
		switch (step)
		{
		case 0:									// Lens 모터 대기 위치로 이동 명령..
												// 1: 본딩위치 들어갈때, 2: 본딩 위치에서 나올 떄, 0:xyΘ 같이 움직일 때.
			if (b_bonding_move_flag == 1)
			{
				goMotorPos(1, axis, pos);				// x 모터
			}
			else if (b_bonding_move_flag == 2)
			{
				goMotorPos(1, axis + 1, pos + 1);			// Y 모터
			}
			else if (b_bonding_move_flag == 0)
			{
				goMotorPos(2, axis, pos);
			}
			step = 100;
			break;

		case 100:								// 이동 완료 확인..
			if ((IsStopAxis(Motor_Lens_X) && GetInposition(Motor_Lens_X)) &&
				(IsStopAxis(Motor_Lens_Y) && GetInposition(Motor_Lens_Y)))
			{
				if (b_bonding_move_flag == 1)
				{
					goMotorPos(1, axis + 1, pos + 1);		// Y 이동..
				}
				else if (b_bonding_move_flag == 2)
				{
					goMotorPos(1, axis, pos);			// X 이동..
				}
				else
					goMotorPos(2, axis, pos);
				step = 101;
			}

			break;

		case 101:
			if ((IsStopAxis(Motor_Lens_X) && GetInposition(Motor_Lens_X)) &&
				(IsStopAxis(Motor_Lens_Y) && GetInposition(Motor_Lens_Y)))
				step = 1000;
			break;

		default:
			break;
		}

		if (step == 1000)
			break;


		eTime = myTimer(true);
		if (eTime - startTime > MOTOR_MOVE_TIME)
		{
			if (step>100)
			{
				int motorNo = step - 100;
				sLangChange.LoadStringA(IDS_STRING722);	//Lens 부 [%s 모터] %s 이동 시간 초과
				_stprintf_s(logMsg, sLangChange, MotorName[motorNo], MotorPosName[index]);
			}
			else
			{
				sLangChange.LoadStringA(IDS_STRING720);	//Lens 부 %s 이동 비정상
				_stprintf_s(logMsg, sLangChange, MotorPosName[index]);
			}
			errMsg2(Task.AutoFlag, logMsg);

			return false;
		}

		Sleep(5);
		checkMessage();
}



	// Z 축은 대기로 이동 한 후 나머지 모터 동작하고, 다른 모터 동작 완료 되면 Z 축 이동..
	//	if(index!=Loading_Pos)
	{
		step = 0;

#ifndef	ON_LINE_MOTOR
		step = 1000;
#endif


		axis[0] = Motor_Lens_Z;
		axis[1] = Motor_Lens_Xt;
		axis[2] = Motor_Lens_Yt;



		pos[0] = model.axis[Motor_Lens_Z].pos[index];
		pos[1] = model.axis[Motor_Lens_Xt].pos[index];
		pos[2] = model.axis[Motor_Lens_Yt].pos[index];

		while (1)
		{
			switch (step)
			{
			case 0:									// 모든 모터 위치 이동 완료 후 Z축 1mm  원래 위치로 이동
				if (index == Loading_Pos || index == Bonding_Pos)
				{
					goMotorPos(2, axis, pos);
				}
				else
				{
					goMotorPos(3, axis, pos);
				}
				step = 102;
				break;

			case 102:								// 이동 완료 확인..
				if (IsStopAxis(Motor_Lens_Yt) && GetInposition(Motor_Lens_Yt))
				{
					step = 103;
				}
				break;

			case 103:								// 이동 완료 확인..
				if (IsStopAxis(Motor_Lens_Xt))
					step = 104;
				break;

			case 104:								// 이동 완료 확인..
				if (IsStopAxis(Motor_Lens_Z) && GetInposition(Motor_Lens_Z))
					step = 1000;
				break;

			default:
				break;
			}
			if (step == 1000)
				break;

			eTime = myTimer(true);
			if (eTime - startTime > MOTOR_MOVE_TIME)
			{
				if (step>100)
				{
					int motorNo = step - 100;
					sLangChange.LoadStringA(IDS_STRING722);	//Lens 부 [%s 모터] %s 이동 시간 초과
					_stprintf_s(logMsg, sLangChange, MotorName[motorNo], MotorPosName[index]);
				}
				else
				{
					sLangChange.LoadStringA(IDS_STRING720);	//Lens 부 %s 이동 비정상
					_stprintf_s(logMsg, sLangChange, MotorPosName[index]);
				}

				errMsg2(Task.AutoFlag, logMsg);

				return false;
			}

			Sleep(5);
			checkMessage();
		}
	}

	return true;
}

bool CAxlMotorSet::Lens_Motor_MoveX(int index, double offsetY, bool bWait)
{
	double eTime = 0.0;
	short axis[1];
	double pos[1];

	char logMsg[1000];
	CString logStr = _T("");

	if (!m_bOrgFlag[Motor_Lens_X])
	{
		sLangChange.LoadStringA(IDS_STRING1246);	//모터가 원점 복귀를 하지 않았습니다.
		_stprintf_s(logMsg, _T("%s ") + sLangChange, MotorName[Motor_Lens_X]);
		errMsg2(Task.AutoFlag, logMsg);
		return false;
	}

	if (index<Wait_Pos || index>ContiTailDelay_Pos)
	{
		sLangChange.LoadStringA(IDS_STRING729);	//Lens 부 모터 이동 위치가 비정상입니다.
		_stprintf_s(logMsg, sLangChange + _T(" [index : %d]"), index);
		errMsg2(Task.AutoFlag, logMsg);

		return false;
	}


	int step = 0;
	double startTime = 0.0;
	double lensPosX = 0.0;
	double lensPosY = 0.0;

	double lensBondPosX = 0.0;
	double lensBondPosY = 0.0;

	double lensCurrentPosY = 0.0;
	bool b_Z_Move_Flag = false;
	double d_dist_Y = model.axis[Motor_Lens_X].pos[index] - GetEncoderPos(Motor_Lens_X);


	axis[0] = Motor_Lens_X;


	pos[0] = model.axis[Motor_Lens_X].pos[index];


	step = 0;

	int MoveType = 0;//0 = x,y동시 이동 , 1 = y축 부터  , 2 = x축 부터 이동
	Task.bMotorRunStop = true;
	while (1)
	{
		if (Task.bMotorRunStop == false)	//Lens_Motor_MoveX
		{
			StopAxis(Motor_Lens_X);
			return false;
		}
		switch (step)
		{
		case 0:
			goMotorPos(1, axis, pos);

			startTime = myTimer(true);
			step = 100;
			break;
		case 100:
			if (bWait == false)
			{
				step = 1000;
				break;
			}
			if (IsStopAxis(Motor_Lens_X))
			{
				step = 1000;
			}
			break;

		default:
			break;
		}

		if (step == 1000)
			break;


		eTime = myTimer(true);
		if (eTime - startTime>MOTOR_MOVE_TIME)
		{
			if (step>100)
			{
				int motorNo = step - 100;
				_stprintf_s(logMsg, "Lens 부 [%s 모터] %s 이동 시간 초과", MotorName[motorNo], MotorPosName[index]);
			}
			else
			{
				_stprintf_s(logMsg, "Lens 부 %s 이동 비정상", MotorPosName[index]);
			}
			errMsg2(Task.AutoFlag, logMsg);

			return false;
		}

		Sleep(5);
	}

	return true;
}



bool CAxlMotorSet::Pcb_Motor_MoveY(int index, double offsetY, bool bWait)
{
	double eTime = 0.0;
	short axis[1];
	double pos[1];

	char logMsg[1000];
	CString logStr = _T("");

	if (!m_bOrgFlag[Motor_PCB_Y])
	{
		sLangChange.LoadStringA(IDS_STRING1246);	//모터가 원점 복귀를 하지 않았습니다.
		_stprintf_s(logMsg, _T("%s ") + sLangChange, MotorName[Motor_PCB_Y]);
		errMsg2(Task.AutoFlag, logMsg);
		return false;
	}

	if (index<Wait_Pos || index>ContiTailDelay_Pos)
	{
		sLangChange.LoadStringA(IDS_STRING729);	//Lens 부 모터 이동 위치가 비정상입니다.
		_stprintf_s(logMsg, sLangChange + _T(" [index : %d]"), index);
		errMsg2(Task.AutoFlag, logMsg);

		return false;
	}


	int step = 0;
	double startTime = 0.0;
	double lensPosX = 0.0;
	double lensPosY = 0.0;

	double lensBondPosX = 0.0;
	double lensBondPosY = 0.0;

	double lensCurrentPosY = 0.0;
	bool b_Z_Move_Flag = false;
	double d_dist_Y = model.axis[Motor_PCB_Y].pos[index] - GetEncoderPos(Motor_PCB_Y);


	axis[0] = Motor_PCB_Y;
	pos[0] = model.axis[Motor_PCB_Y].pos[index];


	step = 0;

	int MoveType = 0;//0 = x,y동시 이동 , 1 = y축 부터  , 2 = x축 부터 이동

	if (index == Bonding_Pos)
	{
		//bool  b_PCB_cover_push_down = Dio.PCBCoverCloseCheck(true, false);
		//if(b_PCB_cover_push_down==false)
		//{
		//	sLangChange.LoadStringA(IDS_STRING1026);	//PCB부 커버 소켓이 열려 있습니다.
		//	_stprintf_s(logMsg, sLangChange);
		//	errMsg2(Task.AutoFlag,logMsg);

		//	return false;
		//}
	}

#if 0
	lensPosX = (float)model.axis[Motor_Lens_X].pos[Loading_Pos] - (float)GetEncoderPos(Motor_Lens_X);
	lensPosY = (float)model.axis[Motor_Lens_Y].pos[Loading_Pos] - (float)GetEncoderPos(Motor_Lens_Y);

	lensBondPosX = (float)model.axis[Motor_Lens_X].pos[Bonding_Pos] - (float)GetEncoderPos(Motor_Lens_X);
	lensBondPosY = (float)model.axis[Motor_Lens_Y].pos[Bonding_Pos] - (float)GetEncoderPos(Motor_Lens_Y);

	lensCurrentPosY = (float)GetEncoderPos(Motor_Lens_Y);
	if (fabs(lensPosX) < 1.1 && fabs(lensPosY) < 1.1)
	{
		MoveType = 1;//현재 위치가 로딩위치면 y축 먼저 뒤로 빠져야된다.렌즈그리퍼가 렌즈를 감싸고 있을수있어서.
	}
	else if (fabs(lensBondPosX) < 1.1 && fabs(lensBondPosY) < 1.1)
	{
		MoveType = 1;//현재 위치가 본딩위치면 y축 먼저 뒤로 빠져야된다.렌즈그리퍼가 렌즈를 감싸고 있을수있어서.
	}
	else
	{
		if (index == Loading_Pos)
		{
			MoveType = 2;//x축먼저 이동후 y축 이동 , 높이 때문에 렌즈 몸통 사이로 그리퍼가 들어아야돼서 x축을 맞추고 y축 진행
		}
		else if (index == Bonding_Pos)
		{
			if (lensCurrentPosY < (float)model.axis[Motor_Lens_Y].pos[Bonding_Pos])
			{
				//cl를 지나 pcb쪽에 있따.
				//여기서 본딩갈때는 y축부터
				MoveType = 1;
			}
			else
			{
				MoveType = 2;
			}
		}

		else if (index == Wait_Pos)
		{
			MoveType = 2;// 1;//y축 먼저 이동후 x축 이동
		}
		else
		{

			MoveType = 1;
		}
	}
#endif
	Task.bMotorRunStop = true;
	while (1)
	{
		if (Task.bMotorRunStop == false)	//pcb Motor MoveY
		{
			StopAxis(Motor_PCB_Y);
			return false;
		}
		switch (step)
		{
		case 0:
			goMotorPos(1, axis, pos);

			startTime = myTimer(true);
			step = 1000;
			break;
		case 100:
			if (IsStopAxis(Motor_PCB_Y))
			{
				step = 1000;
			}
			break;

		default:
			break;
		}

		if (step == 1000)
			break;


		eTime = myTimer(true);
		if (eTime - startTime>MOTOR_MOVE_TIME)
		{
			if (step>100)
			{
				int motorNo = step - 100;
				_stprintf_s(logMsg, "Pcb 부 [%s 모터] %s 이동 시간 초과", MotorName[motorNo], MotorPosName[index]);
			}
			else
			{
				_stprintf_s(logMsg, "Pcb 부 %s 이동 비정상", MotorPosName[index]);
			}
			errMsg2(Task.AutoFlag, logMsg);

			return false;
		}

		Sleep(5);
	}

	return true;

}


bool CAxlMotorSet::Lens_Motor_MoveY(int index, double offsetY, bool bWait)
{
	double eTime = 0.0;
	short axis[1];
	double pos[1];

	char logMsg[1000];
	CString logStr = _T("");

	if (!m_bOrgFlag[Motor_Lens_Y])
	{
		sLangChange.LoadStringA(IDS_STRING1246);	//모터가 원점 복귀를 하지 않았습니다.
		_stprintf_s(logMsg, _T("%s ") + sLangChange, MotorName[Motor_Lens_Y]);
		errMsg2(Task.AutoFlag, logMsg);
		return false;
	}

	if (index<Wait_Pos || index>ContiTailDelay_Pos)
	{
		sLangChange.LoadStringA(IDS_STRING729);	//Lens 부 모터 이동 위치가 비정상입니다.
		_stprintf_s(logMsg, sLangChange + _T(" [index : %d]"), index);
		errMsg2(Task.AutoFlag, logMsg);

		return false;
	}


	int step = 0;
	double startTime = 0.0;
	double lensPosX = 0.0;
	double lensPosY = 0.0;

	double lensBondPosX = 0.0;
	double lensBondPosY = 0.0;

	double lensCurrentPosY = 0.0;
	bool b_Z_Move_Flag = false;
	double d_dist_Y = model.axis[Motor_Lens_Y].pos[index] - GetEncoderPos(Motor_Lens_Y);


	axis[0] = Motor_Lens_Y;


	pos[0] = model.axis[Motor_Lens_Y].pos[index];


	step = 0;

	int MoveType = 0;//0 = x,y동시 이동 , 1 = y축 부터  , 2 = x축 부터 이동
#if 0
	lensPosX = (float)model.axis[Motor_Lens_X].pos[Loading_Pos] - (float)GetEncoderPos(Motor_Lens_X);
	lensPosY = (float)model.axis[Motor_Lens_Y].pos[Loading_Pos] - (float)GetEncoderPos(Motor_Lens_Y);

	lensBondPosX = (float)model.axis[Motor_Lens_X].pos[Bonding_Pos] - (float)GetEncoderPos(Motor_Lens_X);
	lensBondPosY = (float)model.axis[Motor_Lens_Y].pos[Bonding_Pos] - (float)GetEncoderPos(Motor_Lens_Y);

	lensCurrentPosY = (float)GetEncoderPos(Motor_Lens_Y);
	if (fabs(lensPosX) < 1.1 && fabs(lensPosY) < 1.1)
	{
		MoveType = 1;//현재 위치가 로딩위치면 y축 먼저 뒤로 빠져야된다.렌즈그리퍼가 렌즈를 감싸고 있을수있어서.
	}
	else if (fabs(lensBondPosX) < 1.1 && fabs(lensBondPosY) < 1.1)
	{
		MoveType = 1;//현재 위치가 본딩위치면 y축 먼저 뒤로 빠져야된다.렌즈그리퍼가 렌즈를 감싸고 있을수있어서.
	}
	else
	{
		if (index == Loading_Pos)
		{
			MoveType = 2;//x축먼저 이동후 y축 이동 , 높이 때문에 렌즈 몸통 사이로 그리퍼가 들어아야돼서 x축을 맞추고 y축 진행
		}
		else if (index == Bonding_Pos)
		{
			if (lensCurrentPosY < (float)model.axis[Motor_Lens_Y].pos[Bonding_Pos])
			{
				//cl를 지나 pcb쪽에 있따.
				//여기서 본딩갈때는 y축부터
				MoveType = 1;
			}
			else
			{
				MoveType = 2;
			}
		}

		else if (index == Wait_Pos)
		{
			MoveType = 2;// 1;//y축 먼저 이동후 x축 이동
		}
		else
		{

			MoveType = 1;
		}
	}
#endif
	Task.bMotorRunStop = true;
	while (1)
	{
		if (Task.bMotorRunStop == false)	//Lens_Motor_MoveY
		{
			StopAxis(Motor_Lens_Y);
			return false;
		}
		switch (step)
		{
		case 0:
			goMotorPos(1, axis, pos);

			startTime = myTimer(true);
			step = 100;
			break;
		case 100:
			if (bWait == false)
			{
				step = 1000;
				break;
			}
			if (IsStopAxis(Motor_Lens_Y))
			{
				step = 1000;
			}
			break;

		default:
			break;
		}

		if (step == 1000)
			break;


		eTime = myTimer(true);
		if (eTime - startTime>MOTOR_MOVE_TIME)
		{
			if (step>100)
			{
				int motorNo = step - 100;
				_stprintf_s(logMsg, "Lens 부 [%s 모터] %s 이동 시간 초과", MotorName[motorNo], MotorPosName[index]);
			}
			else
			{
				_stprintf_s(logMsg, "Lens 부 %s 이동 비정상", MotorPosName[index]);
			}
			errMsg2(Task.AutoFlag, logMsg);

			return false;
		}

		Sleep(5);
	}

	return true;

}



bool CAxlMotorSet::Lens_Motor_MoveXY(int index, double offsetX, double offsetY, bool bWait)
{
	double eTime;
	short axis[6];
	double pos[6];

	char logMsg[1000];
	CString logStr = "";
	for (int i = 0; i<MAX_MOTOR_NO; i++)
	{
		if (!m_bOrgFlag[i])
		{
			sLangChange.LoadStringA(IDS_STRING1246);	//모터가 원점 복귀를 하지 않았습니다.
			_stprintf_s(logMsg, _T("%s ") + sLangChange, MotorName[i]);
			errMsg2(Task.AutoFlag, logMsg);
			return false;
		}
}

	if (index<Wait_Pos || index>Dispense_Pos3)
	{
		sLangChange.LoadStringA(IDS_STRING729);	//Lens 부 모터 이동 위치가 비정상입니다.
		_stprintf_s(logMsg, sLangChange + _T(" [index : %d]"), index);
		errMsg2(Task.AutoFlag, logMsg);

		return false;
	}


	if (index == Wait_Pos || index == Loading_Pos || index == Bonding_Pos)
	{
		if (Dio.CamLaserSlinderCheck(true, false))
		{
			logStr.Format("Laser/Cam 실린더 전진 상태입니다.");
			errMsg2(Task.AutoFlag, logMsg);
			return false;
		}
	}

	//if(index==Bonding_Pos)
	//{
	//	double dMotor = GetEncoderPos(Motor_PCB_Y)/*GetCommandPos(Motor_PCB_Y)*/ - model.axis[Motor_PCB_Y].pos[index];

	//	if(dMotor > -model.axis[Motor_PCB_Y].m_dLimit_Err)
	//	{
	//		bool b_pcb_push_state = Dio.PCBCoverCloseCheck(true, false);
	//		if (b_pcb_push_state == false)
	//		{
	//			sLangChange.LoadStringA(IDS_STRING1026);	//PCB부 커버 소켓이 열려 있습니다.
	//			_stprintf_s(logMsg, sLangChange);
	//			errMsg2(Task.AutoFlag, logMsg);
	//			return false;
	//		}
	//	}

	//	//Dio.BackLightOn(false, true);
	//}

	int step = 0;
	double startTime;


	bool b_Z_Move_Flag = false;
	double d_dist_X = model.axis[Motor_Lens_X].pos[index] - GetEncoderPos(Motor_Lens_X)/*GetCommandPos(Motor_Lens_X)*/;
	double d_dist_Y = model.axis[Motor_Lens_Y].pos[index] - GetEncoderPos(Motor_Lens_Y)/*GetCommandPos(Motor_Lens_Y)*/;


	axis[0] = Motor_Lens_X;
	axis[1] = Motor_Lens_Y;

	pos[0] = model.axis[Motor_Lens_X].pos[index];
	pos[1] = model.axis[Motor_Lens_Y].pos[index];

	step = 0;
	Task.bMotorRunStop = true;
	while (1)
	{
		if (Task.bMotorRunStop == false)	//Lens_Motor_MoveXY
		{
			StopAxis(Motor_Lens_X);
			StopAxis(Motor_Lens_Y);
			return false;
		}
		switch (step)
		{
		case 0:									// 2축 모터 대기 위치로 이동 명령..
			goMotorPos(2, axis, pos);			// Xt, Yt
			startTime = myTimer(true);
			step = 100;
			break;
		case 100:
			if (IsStopAxis(Motor_Lens_X) && fabs((GetEncoderPos(Motor_Lens_X) - pos[0])) < 0.1)
			{
				step = 101;
			}
			break;
		case 101:
			if (IsStopAxis(Motor_Lens_Y) && fabs((GetEncoderPos(Motor_Lens_Y) - pos[1])) < 0.1)
			{
				step = 1000;
			}
			break;

		default:
			break;
		}

		if (step == 1000)
			break;


		eTime = myTimer(true);
		if (eTime - startTime>MOTOR_MOVE_TIME)
		{
			if (step>100)
			{
				int motorNo = step - 100;
				sLangChange.LoadStringA(IDS_STRING722);	//Lens 부 [%s 모터] %s 이동 시간 초과
				_stprintf_s(logMsg, sLangChange, MotorName[motorNo], MotorPosName[index]);
			}
			else
			{
				sLangChange.LoadStringA(IDS_STRING720);	//Lens 부 %s 이동 비정상
				_stprintf_s(logMsg, sLangChange, MotorPosName[index]);
			}
			errMsg2(Task.AutoFlag, logMsg);

			return false;
		}

		Sleep(5);
		checkMessage();
	}

	return true;

}


bool CAxlMotorSet::Pcb_Motor_Align_Move(double offsetX, double offsetY, double offsetTh)
{
	char logMsg[1000];
	double eTime;
	short axis[3];
	double pos[3];
	int axis_cnt = 0;
	double dOffsetLimit = 1.0;


	for (int i = Motor_PCB_X; i <= Motor_PCB_TH; i++)
	{
		if (!m_bOrgFlag[i])
		{
			sLangChange.LoadStringA(IDS_STRING1001);	//PCB 부 모터가 원점 복귀를 하지 않았습니다.
			_stprintf_s(logMsg, _T("%s ") + sLangChange, MotorName[i]);
			errMsg2(Task.AutoFlag, logMsg);
			return false;
		}

		axis[i - Motor_PCB_X] = i;

		if (i == Motor_PCB_X)				pos[i - Motor_PCB_X] = model.axis[i].pos[Align_Pos] + offsetX;
		else if (i == Motor_PCB_Y)			pos[i - Motor_PCB_X] = model.axis[i].pos[Align_Pos] + offsetY;
		else if (i == Motor_PCB_TH)		pos[i - Motor_PCB_X] = model.axis[i].pos[Align_Pos] + offsetTh;
	}

	double MotorPos[2];
	MotorPos[0] = GetEncoderPos(Motor_PCB_X) - model.axis[Motor_PCB_X].pos[Align_Pos];
	MotorPos[1] = GetEncoderPos(Motor_PCB_Y) - model.axis[Motor_PCB_Y].pos[Align_Pos];

	if (fabs(MotorPos[0]) > model.axis[Motor_PCB_X].m_dLimit_Err)
	{
		sLangChange.LoadStringA(IDS_STRING970);	//PCB X 모터가 Align 보정 Limit를 벗어 났습니다. [Encoder %.03lf, Teaching %.03lf]
		_stprintf_s(logMsg, sLangChange, GetEncoderPos(Motor_PCB_X), model.axis[Motor_PCB_X].pos[Align_Pos]);
		errMsg2(Task.AutoFlag, logMsg);
		return false;
	}

	if (fabs(MotorPos[1]) > model.axis[Motor_PCB_Y].m_dLimit_Err)
	{
		sLangChange.LoadStringA(IDS_STRING973);	//PCB Y 모터가 Align 보정 Limit를 벗어 났습니다. [Encoder %.03lf, Teaching %.03lf]
		_stprintf_s(logMsg, sLangChange, GetEncoderPos(Motor_PCB_Y), model.axis[Motor_PCB_Y].pos[Align_Pos]);
		errMsg2(Task.AutoFlag, logMsg);
		return false;
	}

	int step = 0;

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif


	double startTime;

	while (1)
	{
		switch (step)
		{
		case 0:									// 3축 모터 대기 위치로 이동 명령..
			startTime = myTimer(true);
			goMotorPos(3, axis, pos);
			step = 100;
			break;

		case 100:								// 이동 완료 확인..
			if (IsStopAxis(Motor_PCB_X) && GetInposition(Motor_PCB_X))			step = 101;
			break;

		case 101:
			if (IsStopAxis(Motor_PCB_Y) && GetInposition(Motor_PCB_Y))		step = 102;
			break;

		case 102:
			if (IsStopAxis(Motor_PCB_TH) && GetInposition(Motor_PCB_TH))		step = 1000;
			break;

		default:
			break;
		}

		if (step == 1000)
			break;


		eTime = myTimer(true);
		if (eTime - startTime > MOTOR_MOVE_TIME)
		{
			StopAxis(Motor_PCB_X);
			StopAxis(Motor_PCB_Y);
			StopAxis(Motor_PCB_TH);

			if (step>100)
			{
				int motorNo = step - 100;
				sLangChange.LoadStringA(IDS_STRING1482);	//PCB 부 [%s 모터] 이동 시간 초과
				_stprintf_s(logMsg, sLangChange, MotorName[motorNo]);
			}
			else
			{
				sLangChange.LoadStringA(IDS_STRING994);	//PCB 부 Align 보정 이동 시간 초과
				_stprintf_s(logMsg, sLangChange);
			}

			errMsg2(Task.AutoFlag, logMsg);

			return false;
		}

		Sleep(5);
		checkMessage();
	}


#ifdef ON_LINE_MOTOR
	for (int i = Motor_PCB_X; i <= Motor_PCB_TH; i++)
	{
		double curPos = GetEncoderPos(axis[i - Motor_PCB_X]);
		double cmdPos = GetCommandPos(axis[i - Motor_PCB_X]);

		double errVal = fabs(pos[i - Motor_PCB_X] - curPos);

		if (errVal>IN_POSITION_VAL)
		{
			sLangChange.LoadStringA(IDS_STRING995);	//PCB 부 Align 보정 이동 후 %s 모터 위치 오차 발생
			_stprintf_s(logMsg, sLangChange, MotorName[i], pos[i], curPos, cmdPos);
			LogSave(logMsg);

			checkMessage();


			for (int j = 0; j<10; j++)
			{
				Sleep(5);
				checkMessage();
			}


			curPos = GetEncoderPos(axis[i - Motor_PCB_X]);
			cmdPos = GetCommandPos(axis[i - Motor_PCB_X]);

			errVal = fabs(pos[i - Motor_PCB_X] - curPos);

			if (errVal>IN_POSITION_VAL)
			{
				sLangChange.LoadStringA(IDS_STRING995);	//PCB 부 Align 보정 이동 후 %s 모터 위치 오차 발생
				_stprintf_s(logMsg, sLangChange, MotorName[i], pos[i], curPos, cmdPos);
				errMsg2(Task.AutoFlag, logMsg);

				return false;
			}

			return false;
		}
	}
#endif


	return true;
}

bool CAxlMotorSet::Dispense_XY_Motor_Move(int index, double dDispenseSpeed, double offsetX, double offsetY, double offsetTh)
{
	char logMsg[1000];
	double eTime = 0.0;
	short axis[3];
	double pos[3];
	int axis_cnt = 0;

	if (!m_bOrgFlag[Motor_PCB_X] || !m_bOrgFlag[Motor_PCB_Y] || !m_bOrgFlag[Motor_PCB_TH])
	{
		sLangChange.LoadStringA(IDS_STRING1001);	//PCB 부 모터가 원점 복귀를 하지 않았습니다.
		_stprintf_s(logMsg, sLangChange);
		errMsg2(Task.AutoFlag, logMsg);
		return false;
	}

	if (index<Wait_Pos || index >= MAX_POS_NO)
	{
		sLangChange.LoadStringA(IDS_STRING1000);	//PCB 부 모터 이동 위치가 비정상입니다
		_stprintf_s(logMsg, sLangChange, index);
		LogSave(logMsg);
		errMsg2(Task.AutoFlag, logMsg);

		return false;
	}



	double zPos = 0.0;

	
	if (fabs(offsetX)>model.axis[Motor_PCB_X].m_dLimit_Err)
	{
		sLangChange.LoadStringA(IDS_STRING997);	//PCB 부 X 축 보정값 허용 범위[± %.01f]를 초과 하였습니다
		_stprintf_s(logMsg, sLangChange, model.axis[Motor_PCB_X].m_dLimit_Err, offsetX);
		errMsg2(Task.AutoFlag, logMsg);

		return false;
	}

	if (fabs(offsetY)>model.axis[Motor_PCB_Y].m_dLimit_Err)
	{
		sLangChange.LoadStringA(IDS_STRING998);	//PCB 부 Y 축 보정값 허용 범위[± %.01f]를 초과 하였습니다.
		_stprintf_s(logMsg, sLangChange, model.axis[Motor_PCB_Y].m_dLimit_Err, offsetY);
		errMsg2(Task.AutoFlag, logMsg);

		return false;
	}

	if (fabs(offsetTh)>model.axis[Motor_PCB_TH].m_dLimit_Err)
	{
		sLangChange.LoadStringA(IDS_STRING999);	//PCB 부 Θ축 보정값 허용 범위[± %.01f]를 초과 하였습니다
		_stprintf_s(logMsg, sLangChange, model.axis[Motor_PCB_TH].m_dLimit_Err, offsetTh);
		errMsg2(Task.AutoFlag, logMsg);

		return false;
	}

	axis[0] = Motor_PCB_X;
	axis[1] = Motor_PCB_Y;
	axis[2] = Motor_PCB_TH;

	pos[0] = model.axis[Motor_PCB_X].pos[index] + offsetX;
	pos[1] = model.axis[Motor_PCB_Y].pos[index] + offsetY;
	pos[2] = model.axis[Motor_PCB_TH].pos[index] + offsetTh;

	_stprintf_s(logMsg, "PCB X,Y %s로 이동 합니다.", MotorPosName[index]);
	//	delayMsg(logMsg, 10000, M_COLOR_BLUE);


	int step = 0;

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif

	double startTime;

	int b_bonding_move_flag = 1;
	while (1)
	{
		switch (step)
		{
		case 0:									// 3축 모터 대기 위치로 이동 명령..
			startTime = myTimer(true);

			DispenseGoMotorPos(3, axis, pos, dDispenseSpeed);

			step = 100;
			break;

		case 100:								// 이동 완료 확인..
			if ((IsStopAxis(Motor_PCB_X) && GetInposition(Motor_PCB_X)) &&
				(IsStopAxis(Motor_PCB_Y) && GetInposition(Motor_PCB_Y)) &&
				(IsStopAxis(Motor_PCB_TH)))
			{
				step = 101;
			}

			break;

		case 101:

			step = 1000;
			break;

		default:
			break;
		}

		if (step == 1000)
			break;


		eTime = myTimer(true);
		if (eTime - startTime > MOTOR_MOVE_TIME)
		{
			StopAxis(Motor_PCB_X);
			StopAxis(Motor_PCB_Y);
			StopAxis(Motor_PCB_TH);

			if (step>100)
			{
				int motorNo = step - 100;
				sLangChange.LoadStringA(IDS_STRING1479);	//PCB 부 [%s 모터] %s 이동 시간 초과
				_stprintf_s(logMsg, sLangChange, MotorName[motorNo], MotorPosName[index]);
			}
			else
			{
				sLangChange.LoadStringA(IDS_STRING992);	//PCB 부 %s 이동 비정상
				_stprintf_s(logMsg, sLangChange, MotorPosName[index]);
			}

			errMsg2(Task.AutoFlag, logMsg);

			return false;
		}

		Sleep(5);
		checkMessage();
	}

	return true;
}



bool CAxlMotorSet::Pcb_Motor_MoveXY(int index, double offsetX, double offsetY, bool bWait)
{
	char logMsg[1000];
	double eTime = 0.0;
	short axis[2];
	double pos[2];
	int axis_cnt = 0;

	if(!m_bOrgFlag[Motor_PCB_X] || !m_bOrgFlag[Motor_PCB_Y])
	{
		sLangChange.LoadStringA(IDS_STRING1001);	//PCB 부 모터가 원점 복귀를 하지 않았습니다.
		_stprintf_s(logMsg, sLangChange);
		errMsg2(Task.AutoFlag,logMsg);
		return false;
	}

	if(index<Wait_Pos || index>=MAX_POS_NO)
	{
		sLangChange.LoadStringA(IDS_STRING1000);	//PCB 부 모터 이동 위치가 비정상입니다
		_stprintf_s(logMsg, sLangChange, index);
		LogSave(logMsg);
		errMsg2(Task.AutoFlag, logMsg);

		return false;
	}

	//if (Dio.LaserCylinderCheck(false, false))
	//{
	//	sLangChange.LoadStringA(IDS_STRING1497);	//LASER 실린더가 하강 상태 입니다.
	//	_stprintf_s(logMsg, sLangChange);
	//	errMsg2(Task.AutoFlag, logMsg);
	//	return false;
	//}


	//double MotorPos[3];
	//MotorPos[0] = fabs(GetEncoderPos(Motor_Lens_X) - model.axis[Motor_Lens_X].pos[Bonding_Pos]);
	//MotorPos[1] = fabs(GetEncoderPos(Motor_Lens_Y) - model.axis[Motor_Lens_Y].pos[Bonding_Pos]);
	//MotorPos[2] = fabs(GetCommandPos(Motor_Lens_Z) - model.axis[Motor_Lens_Z].pos[Wait_Pos]);

	//// Lens가 X,Y 본딩 위치일 경우 , Lens Z 축 확인 
	//if(MotorPos[0] < model.axis[Motor_Lens_X].m_dLimit_Err && MotorPos[1] < model.axis[Motor_Lens_Y].m_dLimit_Err)
	//{
	//	if (MotorPos[2] > 1)		// PCB가 본딩 위치로 이동 할때 Lens Z축 대기 위치 확인
	//	{
	//		//sLangChange.LoadStringA(IDS_STRING719);	//Lens 모터가 본딩 위치에 있습니다.
	//		//_stprintf_s(logMsg, sLangChange);
	//		errMsg2(Task.AutoFlag, "Lens Z축 대기가 아닙니다.");
	//		return false;
	//	}

	//		
	//}

	double pcbPosX = 0.0;
	double pcbPosY = 0.0;
	double zPos = 0.0;
	
	// 본딩위치로 들어 가거나, 나올 때는 X 축 먼저 이동 후 Y 모터 이동 목적..
	//최주임님 확인.
	int b_bonding_move_flag = 0;

	if (index == Bonding_Pos || index == Loading_Pos)
	{
		b_bonding_move_flag = 1;		//X축 부터 이동
	}
	else
	{
		double d_x_pos = abs(GetEncoderPos(Motor_PCB_X) - model.axis[Motor_PCB_X].pos[Bonding_Pos]);
		double d_y_pos = abs(GetEncoderPos(Motor_PCB_Y) - model.axis[Motor_PCB_Y].pos[Bonding_Pos]);

		double d_x2_pos = abs(GetEncoderPos(Motor_PCB_X) - model.axis[Motor_PCB_X].pos[Loading_Pos]);
		double d_y2_pos = abs(GetEncoderPos(Motor_PCB_Y) - model.axis[Motor_PCB_Y].pos[Loading_Pos]);

		// PCB x, y 모터가 본딩 위치 근처에 있으면..
		//if( (d_x_pos<model.axis[Motor_PCB_X].m_dLimit_Err) && (d_y_pos<model.axis[Motor_PCB_Y].m_dLimit_Err) || (d_x2_pos<model.axis[Motor_PCB_X].m_dLimit_Err) && (d_y2_pos<model.axis[Motor_PCB_Y].m_dLimit_Err))

		double dCheckPos = motor.GetEncoderPos(Motor_PCB_Y);
		
		if (dCheckPos > (model.axis[Motor_PCB_Y].pos[Bonding_Pos] - 10.0))
		{
			b_bonding_move_flag = 2;
		}
		else
		{
			b_bonding_move_flag = 0;
		}
	}

	if(fabs(offsetX)>model.axis[Motor_PCB_X].m_dLimit_Err)
	{
		sLangChange.LoadStringA(IDS_STRING997);	//PCB 부 X 축 보정값 허용 범위[± %.01f]를 초과 하였습니다
		_stprintf_s(logMsg, sLangChange, model.axis[Motor_PCB_X].m_dLimit_Err, offsetX);
		errMsg2(Task.AutoFlag,logMsg);

		return false;
	}

	if(fabs(offsetY)>model.axis[Motor_PCB_Y].m_dLimit_Err)
	{
		sLangChange.LoadStringA(IDS_STRING998);	//PCB 부 Y 축 보정값 허용 범위[± %.01f]를 초과 하였습니다.
		_stprintf_s(logMsg, sLangChange, model.axis[Motor_PCB_Y].m_dLimit_Err, offsetY);
		errMsg2(Task.AutoFlag, logMsg);

		return false;
	}

	if (index == Bonding_Pos && sysData.m_iProductComp == 1)//if (index == Bonding_Pos && (Task.dAAPcbMotor[0] != 0 && Task.dAAPcbMotor[1] != 0 && Task.dAAPcbMotor[2]!=0))
	{
		axis[0] = Motor_PCB_X;
		axis[1] = Motor_PCB_Y;
#if (____AA_WAY == PCB_TILT_AA)
		pos[0]	= Task.dAAPcbMotor[0] + offsetX;	//PCB X access 저장된 값
		pos[1]	= Task.dAAPcbMotor[1] + offsetY;	//PCB Y
#elif (____AA_WAY == LENS_TILT_AA)
		pos[0]	= model.axis[Motor_PCB_X].pos[index] + offsetX;
		pos[1]	= model.axis[Motor_PCB_Y].pos[index] + offsetY;
#endif
	}
	else
	{
		axis[0] = Motor_PCB_X;
		axis[1] = Motor_PCB_Y;

		pos[0]	= model.axis[Motor_PCB_X].pos[index] + offsetX;
		pos[1]	= model.axis[Motor_PCB_Y].pos[index] + offsetY;
		
	}

	_stprintf_s(logMsg, "PCB 부 %s로 이동 합니다.", MotorPosName[index]);

	int step = 0;

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif

	double startTime;
	Task.bMotorRunStop = true;

	while(1)
	{
		if (Task.bMotorRunStop == false)	//pcb Motor MoveXY
		{
			StopAxis(Motor_PCB_X);
			StopAxis(Motor_PCB_Y);
			return false;
		}
		switch(step)
		{
		case 0:									// 3축 모터 대기 위치로 이동 명령..
			startTime = myTimer(true);

			// 1: 본딩위치 들어갈때, 2: 본딩 위치에서 나올 떄, 0:xyΘ 같이 움직일 때.
			if(b_bonding_move_flag == 1)
			{
				goMotorPos(1, axis, pos);				// x 모터
			}
			else if(b_bonding_move_flag == 2)
			{
				goMotorPos(1, axis + 1, pos + 1);			// Y 모터
			}
			else
			{
				goMotorPos(2, axis, pos);
			}

			step = 100;
			break;

		case 100:								// 이동 완료 확인..
			pcbPosX = fabs(GetEncoderPos(Motor_PCB_X) - model.axis[Motor_PCB_X].pos[index] + offsetX);
			pcbPosY = fabs(GetEncoderPos(Motor_PCB_Y) - model.axis[Motor_PCB_Y].pos[index] + offsetY);
			if( IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y) && pcbPosX < 0.05 && pcbPosY < 0.05)
			{
				if(b_bonding_move_flag==1)
				{
					goMotorPos(1, axis+1, pos+1);		// Y 이동..
				}
				else if(b_bonding_move_flag==2)
				{
					goMotorPos(1, axis, pos);			// X 이동..
				}
				else
				{
					goMotorPos(2, axis, pos);
				}
				step = 101;
			}

			break;

		case 101:
			pcbPosX = fabs(GetEncoderPos(Motor_PCB_X) - model.axis[Motor_PCB_X].pos[index] + offsetX);
			pcbPosY = fabs(GetEncoderPos(Motor_PCB_Y) - model.axis[Motor_PCB_Y].pos[index] + offsetY);
			if (IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y) && pcbPosX < 0.05 && pcbPosY < 0.05)
			{
				step = 1000;
			}
			break;
		default:
			break;
		}

		if (step == 1000)
		{
			break;
		}

		eTime = myTimer(true);
		if(eTime-startTime > MOTOR_MOVE_TIME)
		{
			StopAxis(Motor_PCB_X);
			StopAxis(Motor_PCB_Y);

			if(step>100)
			{
				int motorNo = step - 100;
				_stprintf_s(logMsg, "PCB 부 [%s 모터] %s 이동 시간 초과", MotorName[motorNo], MotorPosName[index]);
			}
			else
			{
				_stprintf_s(logMsg, "PCB 부 %s 이동 비정상", MotorPosName[index]);
			}

			errMsg2(Task.AutoFlag,logMsg);

			return false;
		}

		Sleep(5);
	}
	return true;
}

bool CAxlMotorSet::Pcb_Motor_Move(int index, double offsetX, double offsetY, double offsetTh, bool bWait)
{
	char logMsg[1000];
	double eTime = 0.0;
	short axis[3];
	double pos[3];
	int axis_cnt = 0;

	if (!m_bOrgFlag[Motor_PCB_X] || !m_bOrgFlag[Motor_PCB_Y] || !m_bOrgFlag[Motor_PCB_TH])
	{
		sLangChange.LoadStringA(IDS_STRING1001);	//PCB 부 모터가 원점 복귀를 하지 않았습니다.
		_stprintf_s(logMsg, sLangChange);
		errMsg2(Task.AutoFlag, logMsg);
		return false;
	}

	if (index<Wait_Pos || index >= MAX_POS_NO)
	{
		sLangChange.LoadStringA(IDS_STRING1000);	//PCB 부 모터 이동 위치가 비정상입니다
		_stprintf_s(logMsg, sLangChange, index);
		LogSave(logMsg);
		errMsg2(Task.AutoFlag, logMsg);

		return false;
	}

	//if (Dio.LaserCylinderCheck(false, false))
	//{
	//	sLangChange.LoadStringA(IDS_STRING1497);	//LASER 실린더가 하강 상태 입니다.
	//	_stprintf_s(logMsg, sLangChange);
	//	errMsg2(Task.AutoFlag, logMsg);
	//	return false;
	//}

	if (index == Bonding_Pos)
	{
		//bool  b_PCB_cover_push_down = Dio.PCBCoverCloseCheck(true, false);
		//if(b_PCB_cover_push_down==false)
		//{
		//	sLangChange.LoadStringA(IDS_STRING1026);	//PCB부 커버 소켓이 열려 있습니다.
		//	_stprintf_s(logMsg, sLangChange);
		//	errMsg2(Task.AutoFlag,logMsg);

		//	return false;
		//}
	}

	double pcbPosX = 0.0;
	double pcbPosY = 0.0;
	double MotorPos[3];
	MotorPos[0] = fabs(GetEncoderPos(Motor_Lens_X) - model.axis[Motor_Lens_X].pos[Bonding_Pos]);
	MotorPos[1] = fabs(GetEncoderPos(Motor_Lens_Y) - model.axis[Motor_Lens_Y].pos[Bonding_Pos]);
	MotorPos[2] = fabs(GetEncoderPos(Motor_Lens_Z) - model.axis[Motor_Lens_Z].pos[Wait_Pos]);

	// Lens가 X,Y 본딩 위치일 경우 , Lens Z 축 확인 
	//if (MotorPos[0] < model.axis[Motor_Lens_X].m_dLimit_Err && MotorPos[1] < model.axis[Motor_Lens_Y].m_dLimit_Err)
	//{
	//	if (MotorPos[2] > 1)		// PCB가 본딩 위치로 이동 할때 Lens Z축 대기 위치 확인
	//	{
	//		//sLangChange.LoadStringA(IDS_STRING719);	//Lens 모터가 본딩 위치에 있습니다.
	//		//_stprintf_s(logMsg, sLangChange);
	//		errMsg2(Task.AutoFlag, "Lens Z축 대기가 아닙니다.");
	//		return false;
	//	}


	//}


	double zPos = 0.0;

	// 본딩위치로 들어 가거나, 나올 때는 X 축 먼저 이동 후 Y 모터 이동 목적..
	//최주임님 확인.
	int b_bonding_move_flag = 0;

	if (index == Bonding_Pos || index == Loading_Pos)
	{
		b_bonding_move_flag = 1;
	}
	else
	{
		double d_x_pos = abs(GetEncoderPos(Motor_PCB_X) - model.axis[Motor_PCB_X].pos[Bonding_Pos]);
		double d_y_pos = abs(GetEncoderPos(Motor_PCB_Y) - model.axis[Motor_PCB_Y].pos[Bonding_Pos]);
		double d_x2_pos = abs(GetEncoderPos(Motor_PCB_X) - model.axis[Motor_PCB_X].pos[Loading_Pos]);
		double d_y2_pos = abs(GetEncoderPos(Motor_PCB_Y) - model.axis[Motor_PCB_Y].pos[Loading_Pos]);

		// PCB x, y 모터가 본딩 위치 근처에 있으면..
		if ((d_x_pos<model.axis[Motor_PCB_X].m_dLimit_Err) && (d_y_pos<model.axis[Motor_PCB_Y].m_dLimit_Err) || (d_x2_pos<model.axis[Motor_PCB_X].m_dLimit_Err) && (d_y2_pos<model.axis[Motor_PCB_Y].m_dLimit_Err))
		{
			b_bonding_move_flag = 2;
		}
		//b_bonding_move_flag = 2;
		else		b_bonding_move_flag = 0;
	}
	if (index != Wait_Pos)
	{
		if (fabs(offsetX)>model.axis[Motor_PCB_X].m_dLimit_Err)
		{
			sLangChange.LoadStringA(IDS_STRING997);	//PCB 부 X 축 보정값 허용 범위[± %.01f]를 초과 하였습니다
			_stprintf_s(logMsg, sLangChange, model.axis[Motor_PCB_X].m_dLimit_Err, offsetX);
			errMsg2(Task.AutoFlag, logMsg);

			return false;
		}
	}

	if (index != Wait_Pos)
	{
		if (fabs(offsetY)>model.axis[Motor_PCB_Y].m_dLimit_Err)
		{
			sLangChange.LoadStringA(IDS_STRING998);	//PCB 부 Y 축 보정값 허용 범위[± %.01f]를 초과 하였습니다.
			_stprintf_s(logMsg, sLangChange, model.axis[Motor_PCB_Y].m_dLimit_Err, offsetY);
			errMsg2(Task.AutoFlag, logMsg);

			return false;
		}
	}
	if (index != Wait_Pos)
	{
		if (fabs(offsetTh)>model.axis[Motor_PCB_TH].m_dLimit_Err)
		{
			sLangChange.LoadStringA(IDS_STRING999);	//PCB 부 Θ축 보정값 허용 범위[± %.01f]를 초과 하였습니다
			_stprintf_s(logMsg, sLangChange, model.axis[Motor_PCB_TH].m_dLimit_Err, offsetTh);
			errMsg2(Task.AutoFlag, logMsg);

			return false;
		}
	}

	if (index == Bonding_Pos && sysData.m_iProductComp == 1)//if (index == Bonding_Pos && (Task.dAAPcbMotor[0] != 0 && Task.dAAPcbMotor[1] != 0 && Task.dAAPcbMotor[2]!=0))
	{
		axis[0] = Motor_PCB_X;
		axis[1] = Motor_PCB_Y;
		axis[2] = Motor_PCB_TH;
#if (____AA_WAY == PCB_TILT_AA)
		pos[0] = Task.dAAPcbMotor[0] + offsetX;	//PCB X access 저장된 값
		pos[1] = Task.dAAPcbMotor[1] + offsetY;	//PCB Y
		pos[2] = Task.dAAPcbMotor[2] + offsetTh;	//PCB TH

		
#elif (____AA_WAY == LENS_TILT_AA)
		pos[0] = model.axis[Motor_PCB_X].pos[index] + offsetX;
		pos[1] = model.axis[Motor_PCB_Y].pos[index] + offsetY;
		pos[2] = model.axis[Motor_PCB_TH].pos[index] + offsetTh;
#endif
	}
	else
	{
		axis[0] = Motor_PCB_X;
		axis[1] = Motor_PCB_Y;
		axis[2] = Motor_PCB_TH;

		pos[0] = model.axis[Motor_PCB_X].pos[index] + offsetX;
		pos[1] = model.axis[Motor_PCB_Y].pos[index] + offsetY;
		pos[2] = model.axis[Motor_PCB_TH].pos[index] + offsetTh;

	}

	sLangChange.LoadStringA(IDS_STRING993);	//PCB 부 %s로 이동 합니다.
	_stprintf_s(logMsg, sLangChange, MotorPosName[index]);

	int step = 0;

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif

	double startTime = 0.0;

	/*if (bWait == false)
	{
		b_bonding_move_flag = 0;
	}*/

	Task.bMotorRunStop = true;
	while (1)
	{
		if (Task.bMotorRunStop == false)	//pcb Motor Move
		{
			StopAxis(Motor_PCB_X);
			StopAxis(Motor_PCB_Y);
			StopAxis(Motor_PCB_TH);
			return false;
		}
		switch (step)
		{
		case 0:									// 3축 모터 대기 위치로 이동 명령..
			startTime = myTimer(true);

			// 1: 본딩위치 들어갈때, 2: 본딩 위치에서 나올 떄, 0:xyΘ 같이 움직일 때.
			if (b_bonding_move_flag == 1)
			{
				goMotorPos(1, axis, pos);				// x 모터
				if(index!=Loading_Pos)
				{
					goMotorPos(1, axis+2, pos+2);			// Th 모터
				}
				
			}
			else if (b_bonding_move_flag == 2)
			{
				goMotorPos(1, axis + 1, pos + 1);			// Y 모터
			}
			else if (b_bonding_move_flag == 0)
			{
				goMotorPos(3, axis, pos);
			}

			step = 100;
			break;

		case 100:								// 이동 완료 확인..
			if( ( IsStopAxis(Motor_PCB_X) && GetInposition(Motor_PCB_X) ) && 
				( IsStopAxis(Motor_PCB_Y) && GetInposition(Motor_PCB_Y) ) && 
				( IsStopAxis(Motor_PCB_TH) && GetInposition(Motor_PCB_TH) ) )
			{
				if (b_bonding_move_flag == 1)
				{
					goMotorPos(1, axis + 1, pos + 1);		// Y 이동..
				}
				else if (b_bonding_move_flag == 2)
				{
					goMotorPos(1, axis, pos);			// X 이동..
					goMotorPos(1, axis + 2, pos + 2);		// Th 이동..
				}
				else
					goMotorPos(3, axis, pos);
				step = 101;
			}

			break;

		case 101:
			pcbPosX = fabs(GetEncoderPos(Motor_PCB_X) - (model.axis[Motor_PCB_X].pos[index] + offsetX));
			pcbPosY = fabs(GetEncoderPos(Motor_PCB_Y) - (model.axis[Motor_PCB_Y].pos[index] + offsetY));


			if (IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y) && pcbPosX < 0.5 && pcbPosY < 0.5)
			{
				step = 102;
			}
			break;

		case 102:
			if( IsStopAxis(Motor_PCB_TH) && GetInposition(Motor_PCB_TH) )
				step = 1000;
			break;

		default:
			break;
		}

		if (step == 1000)
			break;


		eTime = myTimer(true);
		if (eTime - startTime > MOTOR_MOVE_TIME)
		{
			StopAxis(Motor_PCB_X);
			StopAxis(Motor_PCB_Y);
			StopAxis(Motor_PCB_TH);

			if (step>100)
			{
				int motorNo = step - 100;
				sLangChange.LoadStringA(IDS_STRING1479);	//PCB 부 [%s 모터] %s 이동 시간 초과
				_stprintf_s(logMsg, sLangChange, MotorName[motorNo], MotorPosName[index]);
			}
			else
			{
				sLangChange.LoadStringA(IDS_STRING992);	//PCB 부 %s 이동 비정상
				_stprintf_s(logMsg, sLangChange, MotorPosName[index]);
			}

			errMsg2(Task.AutoFlag, logMsg);

			return false;
		}

		Sleep(5);
	}

	return true;
}


bool CAxlMotorSet::LENS_Z_Motor_Move(int index, bool evasionMode)
{
	double eTime = 0.0;
	short axis[1];
	double pos[1];

	char logMsg[1000];

	double lensPosX = 0.0;
	double lensPosY = 0.0;
		
	if(index == Loading_Pos) 
	{
		bool b_lens_grip_closed = Dio.LensMotorGripCheck(false, false);

		if(b_lens_grip_closed==false)
		{
			sLangChange.LoadStringA(IDS_STRING666);	//Lens Grip Close 상태입니다
			errMsg2(Task.AutoFlag, sLangChange);
			return false;
		}

	}
	
	if(!m_bOrgFlag[Motor_Lens_Z])
	{
		sLangChange.LoadStringA(IDS_STRING726);	//Lens 부 Z 모터가 원점 복귀를 하지 않았습니다.
		_stprintf_s(logMsg, sLangChange);
		errMsg2(Task.AutoFlag,logMsg);

		return false;
	}

	if(index == Loading_Pos)
	{
		for(int i=Motor_Lens_X; i<= Motor_Lens_Xt; i++)
		{
			if (i == Motor_Lens_Z)
				continue;

			double dCheckPos = 0.0;

			if (i == Motor_Lens_Xt)		dCheckPos = GetCommandPos(i);
			else						dCheckPos = GetEncoderPos(i);	//GetCommandPos(i);
	 
			if(fabs(dCheckPos-model.axis[i].pos[Loading_Pos])>1)
			{
				sLangChange.LoadStringA(IDS_STRING731);	//Lens 부 모터가 Loading 위치를 벗어나 있습니다.
				_stprintf_s(logMsg, sLangChange);
				errMsg2(Task.AutoFlag, logMsg);
				return false;
			}

		}

		pos[0]	= model.axis[Motor_Lens_Z].pos[Loading_Pos];
	}
	else if(index == Bonding_Pos)
	{
		for(int i=Motor_Lens_X; i<= Motor_Lens_Xt; i++)
		{
			if (i == Motor_Lens_Z)
				continue;

			double dCheckPos = 0.0;

			if (i == Motor_Lens_Xt)
				dCheckPos = GetCommandPos(i);
			else
				dCheckPos = GetEncoderPos(i);	
			
			if(i == Motor_Lens_Z)		// z축 본딩 위치에 있을 경우 다시 본딩 위치로 이동 하라 했을 경우 error 발생.
			{
				if(fabs(dCheckPos-model.axis[i].pos[Bonding_Pos])< model.axis[i].m_dLimit_Err)
				{
					sLangChange.LoadStringA(IDS_STRING727);	//Lens 부 Z축 모터가 Bonding 위치에 있습니다.
					_stprintf_s(logMsg, sLangChange);
					errMsg2(Task.AutoFlag,logMsg);
					return false;
				}
			}
			else	// Lens 다른 모터..
			{
				if(fabs(dCheckPos-model.axis[i].pos[Bonding_Pos]) > model.axis[i].m_dLimit_Err)
				{
					sLangChange.LoadStringA(IDS_STRING730);	//Lens 부 모터가 Bonding 위치를 벗어나 있습니다.
					_stprintf_s(logMsg, sLangChange);
					errMsg2(Task.AutoFlag, logMsg);

					return false;
				}
			}
		}
		
		pos[0]	= model.axis[Motor_Lens_Z].pos[Bonding_Pos];
	}
	else
	{
		
		pos[0] = model.axis[Motor_Lens_Z].pos[index];
	}
	axis[0] = Motor_Lens_Z;

	sLangChange.LoadStringA(IDS_STRING1480);	//Lens 부 %s 모터 이동 합니다.
	_stprintf_s(logMsg, sLangChange, MotorPosName[Motor_Lens_Z]);


	int step=0;
	
	double startTime;

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif

	while(1)
	{
		switch(step)
		{
		case 0:
			startTime = myTimer(true);
			goMotorPos(1, axis, pos);
			step = 100;
			break;

		case 100:								// 이동 완료 확인..
			if(IsStopAxis(Motor_Lens_Z))
				step = 1000;
			break;

		default:
			break;
		}

		if(step==1000)
			break;


		eTime = myTimer(true);
		if((eTime-startTime)>MOTOR_MOVE_TIME)
		{
			if(step>100)
			{
				sLangChange.LoadStringA(IDS_STRING723);	//Lens 부 [%s 모터] 이동 시간 초과
				_stprintf_s(logMsg, sLangChange, MotorPosName[Motor_Lens_Z]);
			}
			else
			{
				sLangChange.LoadStringA(IDS_STRING720);	//Lens 부 %s 이동 비정상
				_stprintf_s(logMsg, sLangChange, MotorPosName[Motor_Lens_Z]);
			}

			errMsg2(Task.AutoFlag, logMsg);

			return false;
		}

		checkMessage();
		Sleep(5);
	}

	return true;
}
bool CAxlMotorSet::func_Epoxy_Rect_Circle_Draw()
{
	int step = 0;
	double startTime = 0.0;
	double eTime = 0.0;
	double curTime = 0.0;
	DWORD dwReturn = 0;
	long axis[2];
	double acc = 0.0;
	double dec = 0.0;
	double MoveStartTime = 0.0;
	long lSize = 2, lCoordinate = 0;
	double dTimeAngle = 90.0;
	double dEndDeg1ToTime = 0.0;	//1도당 걸리는 시간 
	CString sMsg = "";
	axis[0] = Motor_PCB_X; //축번호
	axis[1] = Motor_PCB_Y;
	double dMidPos[2];
	double dEndPos[2];
	acc = model.dAcc;		//! 가감속도
	dec = model.dAcc;
	//
	dEndDeg1ToTime = (( (model.dRadiusLength * 1) * M_PI) / (sqrt(model.dEpoxySpeed  * model.dEpoxySpeed /2)) ) /360;
	//1도당 걸리는 시간 = 원주율 / 속도 / 360
	while(1)
	{
		
			switch(step)
			{
			case 0:
				if(Straight_Dispense_MoveAxis(Motor_PCB_X, REL, (model.dDisLength[0]) * -1, model.dEpoxySpeed, model.dAcc))//bottom Line
				{
					startTime = myTimer(true);
					step = 100;
				}
				break;
					
			case 100:									
				curTime = myTimer(true);	//현재 시간을 얻어서 토출 On이후 대기 시간을 조절
				if( curTime-startTime > model.dOnTime * 1000 )	//설정 Delay 시간 대기 후 토출
				{
					step = 110;
				}			
				break;

			case 110:									
				startTime = myTimer(true);
				if( Dio.EpoxyDischargeOn(true, true) )		//Epoxy 토출 ON 
				{
					step = 120;
				}
				else 
				{
					sLangChange.LoadStringA(IDS_STRING188);
					sMsg.Format(sLangChange);	//"[Dispence동작] Epoxy 토출 신호 이상 발생_토출 ON 신호"
					errMsg2(Task.AutoFlag, sMsg);
					step = -0;
				}
				break;
			case 120:
				if( IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y))
				{
					Pcb_Motor_CircleMove(dTimeAngle, false, 100);//원1 우측하단
					
					step = 130;
				}
				
				break;
			case 130:
				if( IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y) )
				{
					AxmMotSetMoveUnitPerPulse(Motor_PCB_X, 1, 1);	//Unit/Pulse 원래형태로 변경(1:1 매칭으로)
					AxmMotSetMoveUnitPerPulse(Motor_PCB_Y, 1, 1);
					if(Straight_Dispense_MoveAxis(Motor_PCB_Y, REL, (model.dDisLength[1]) * -1, model.dEpoxySpeed, model.dAcc))//right Line
					{
						step = 135;
					}
				}
				break;
			case 135:
				if (IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y))
				{
					//원 그리기전 직선
					if (Straight_Dispense_MoveAxis(Motor_PCB_X, REL, (model.dDisLength[4]) * 1, model.dEpoxySpeed, model.dAcc))
					{
						step = 140;
					}
				}
				break;
			case 140:
				//원2 우측상단
				if( IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y) )
				{
					Pcb_Motor_CircleMove(dTimeAngle, false, 200);//우측 상단
					
					step = 145;
				}
				break;
			case 145:
				if (IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y))
				{
					//원 그리기전 직선
					if (Straight_Dispense_MoveAxis(Motor_PCB_Y, REL, (model.dDisLength[5]) * -1, model.dEpoxySpeed, model.dAcc))
					{
						step = 150;
					}
				}
				break;
			case 150:
				if( IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y) )
				{
					AxmMotSetMoveUnitPerPulse(Motor_PCB_X, 1, 1);	//Unit/Pulse 원래형태로 변경(1:1 매칭으로)
					AxmMotSetMoveUnitPerPulse(Motor_PCB_Y, 1, 1);
					if(Straight_Dispense_MoveAxis(Motor_PCB_X, REL, (model.dDisLength[2]) * 1, model.dEpoxySpeed, model.dAcc))//top Line
					{
						step = 160;
					}
				}
				break;
			case 160:
				//원3 좌측상단
				if( IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y) ) 
				{
					Pcb_Motor_CircleMove(dTimeAngle, false, 300);	//좌측 상단
					
					step = 170;
				}
				break;
			case 170:
				if( IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y) )
				{
					AxmMotSetMoveUnitPerPulse(Motor_PCB_X, 1, 1);	//Unit/Pulse 원래형태로 변경(1:1 매칭으로)
					AxmMotSetMoveUnitPerPulse(Motor_PCB_Y, 1, 1);
					if(Straight_Dispense_MoveAxis(Motor_PCB_Y, REL, (model.dDisLength[3]) * 1, model.dEpoxySpeed, model.dAcc))//left Line
					{
						step = 175;
						
					}
				}
				break;
			case 175:
				if (IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y))
				{
					//원 그리기전 직선
					if (Straight_Dispense_MoveAxis(Motor_PCB_X, REL, (model.dDisLength[6]) * -1, model.dEpoxySpeed, model.dAcc))
					{
						step = 180;
					}
				}
				break;
			case 180:
				if( IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y) ) 
				{
					Pcb_Motor_CircleMove(dTimeAngle, false, 400);	//좌측 하단
					step = 190;
					
					MoveStartTime = myTimer(true);
				}
				break;
			case 190:
				if (IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y))
				{
					//원 그리기전 직선
					if (Straight_Dispense_MoveAxis(Motor_PCB_Y, REL, (model.dDisLength[7]) * 1, model.dEpoxySpeed, model.dAcc))
					{
						step = 200;
					}
				}
				break;
			case 200:// 모터 도착전 토출 OFF Time 처리

				step = 400;
				break;
			case 400:
				if( IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y) )
				{
					curTime = myTimer(true); 
					if( (dEndDeg1ToTime*dTimeAngle - model.dOffTime) * 1000  <  (curTime - MoveStartTime))
					{
						if( !Dio.EpoxyDischargeOn(false, false) )		//Epoxy 토출 Off
						{
							sLangChange.LoadStringA(IDS_STRING187);
							sMsg.Format(sLangChange);	//"[Dispence동작] Epoxy 토출 신호 이상 발생_토출 OFF 신호"
							errMsg2(Task.AutoFlag, sMsg);
							return false;
						}
						Dio.EpoxyDischargeOn(false, false);
						Sleep(model.dOffTime);
					
						step = 410;	
					}
				}
				break;
			case 410:
				if( ( IsStopAxis(Motor_PCB_X) && GetInposition(Motor_PCB_X) ) && 
					( IsStopAxis(Motor_PCB_Y) && GetInposition(Motor_PCB_Y) ) )
				{
					AxmMotSetMoveUnitPerPulse(Motor_PCB_X, 1, 1);	//Unit/Pulse 원래형태로 변경(1:1 매칭으로)
					AxmMotSetMoveUnitPerPulse(Motor_PCB_Y, 1, 1);

					if(Straight_Dispense_MoveAxis(Motor_PCB_X, REL, model.dDisLength[0] * -1 * 0.5, model.dEpoxySpeed, model.dAcc))	//추가 보간
					{
						step = 500;	
					}	
				}
				break;
			case 500: //모터 동작 완료까지 대기
				if( ( IsStopAxis(Motor_PCB_X) && GetInposition(Motor_PCB_X) ) && 
					( IsStopAxis(Motor_PCB_Y) && GetInposition(Motor_PCB_Y) ) )
					{
						step = 1000;
					}
				break;
			default:
				step = 1000;
				break;
			}	

		if(step==1000)		break;

		eTime = myTimer(true);
		if(eTime-startTime > 2000000)
		{
			StopAxis(Motor_PCB_X);
			StopAxis(Motor_PCB_Y);

			if(step>100)
			{
				int motorNo = step - 100;
				sMsg.Format("[Dispence동작][%s,%s 모터] Circle 동작 이동 시간 초과", MotorName[Motor_PCB_X], MotorName[Motor_PCB_Y]);
			} else
			{
				sMsg.Format("PCB 부 Dispence 동작 Circle 이동 비정상");
			}
			errMsg2(Task.AutoFlag, sMsg);

			return false;
		}

		Sleep(5);
	}

	return true;
}



bool CAxlMotorSet::func_Trinity_Epoxy_Rect_Draw()
{
	int step = 0;
	double startTime = 0.0;
	double eTime = 0.0;
	double curTime = 0.0;
	DWORD dwReturn = 0;
	long axis[2];
	double acc = 0.0;
	double dec = 0.0;
	double MoveStartTime = 0.0;
	long lSize = 2, lCoordinate = 0;
	double dTimeAngle = 90.0;
	double dEndDeg1ToTime = 0.0;	//1도당 걸리는 시간 
	CString sMsg = "";
	axis[0] = Motor_PCB_X; //축번호
	axis[1] = Motor_PCB_Y;
	double dMidPos[2];
	double dEndPos[2];
	acc = model.dAcc;		//! 가감속도
	dec = model.dAcc;
	//
	dEndDeg1ToTime = (((model.dRadiusLength * 1) * M_PI) / (sqrt(model.dEpoxySpeed  * model.dEpoxySpeed / 2))) / 360;
	//1도당 걸리는 시간 = 원주율 / 속도 / 360
	while (1)
	{

		switch (step)
		{
		case 0:
			if (model.dOnTime == 0.0)
			{
				Dio.EpoxyDischargeOn(true, false);
			}
			if(Trinityt_Dispense_MoveAxis())
			{
				startTime = myTimer(true);
				step = 100;
			}
			break;

		case 100:
			if (model.dOnTime == 0.0)
			{
				step = 400;
				break;
			}
			curTime = myTimer(true);	//현재 시간을 얻어서 토출 On이후 대기 시간을 조절
			if (curTime - startTime > model.dOnTime * 1000)	//설정 Delay 시간 대기 후 토출
			{
				step = 200;
			}
			break;

		case 200:
			startTime = myTimer(true);
			if (Dio.EpoxyDischargeOn(true, true))		//Epoxy 토출 ON 
			{
				step = 400;// 4000;
			}
			else
			{
				sLangChange.LoadStringA(IDS_STRING188);
				sMsg.Format(sLangChange);	//"[Dispence동작] Epoxy 토출 신호 이상 발생_토출 ON 신호"
				errMsg2(Task.AutoFlag, sMsg);
				step = -0;
			}
			break;
		case 400:
			if (IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y))
			{
				if (!Dio.EpoxyDischargeOn(false, false))		//Epoxy 토출 Off
				{
					sMsg.Format("[Dispence동작] Epoxy 토출 신호 이상 발생_토출 OFF 신호");
					errMsg2(Task.AutoFlag, sMsg);
					return false;
				}
				step = 500;
				//curTime = myTimer(true);
				//if ((dEndDeg1ToTime*dTimeAngle - model.dOffTime) * 1000  <  (curTime - MoveStartTime))
				//{
				//	if (!Dio.EpoxyDischargeOn(false, false))		//Epoxy 토출 Off
				//	{
				//		sMsg.Format("[Dispence동작] Epoxy 토출 신호 이상 발생_토출 OFF 신호");
				//		errMsg2(Task.AutoFlag, sMsg);
				//		return false;
				//	}
				//	step = 410;
				//}
			}
		case 500:
			if (IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y))
			{

				if (Straight_Dispense_MoveAxis(Motor_PCB_X, REL, model.dDisLength[3] * -1 * 0.2, model.dEpoxySpeed, model.dAcc))	//추가 보간
				{
					step = 550;
				}
			}
			break;
		case 550:
			if ((IsStopAxis(Motor_PCB_X)) && (IsStopAxis(Motor_PCB_Y)))
			{
				step = 1000;
			}
			break;

			//----------------------------------------------------------------------------------------------------------------------------
			//----------------------------------------------------------------------------------------------------------------------------
		case 1000:
			
			step = 5000;
			break;
		default:
			step = 5000;
			break;
		}

		if (step == 5000)		break;

		eTime = myTimer(true);
		if (eTime - startTime > 2000000)
		{
			AxmMotSetMoveUnitPerPulse(Motor_PCB_X, 1, 1);	//Unit/Pulse 원래형태로 변경(1:1 매칭으로)
			AxmMotSetMoveUnitPerPulse(Motor_PCB_Y, 1, 1);

			StopAxis(Motor_PCB_X);
			StopAxis(Motor_PCB_Y);

			if (step>100)
			{
				int motorNo = step - 100;
				sMsg.Format("[Dispence동작]Circle 동작 이동 시간 초과");
			}
			else
			{
				sMsg.Format("PCB 부 Dispence 동작 Circle 이동 비정상");
			}
			errMsg2(Task.AutoFlag, sMsg);

			return false;
		}

		Sleep(5);
	}

	return true;
}


bool CAxlMotorSet::func_Trinity_Epoxy_Circle_Draw()
{
	int step = 0;
	double startTime = 0.0;
	double eTime = 0.0;
	double curTime = 0.0;
	DWORD dwReturn = 0;
	long axis[2];
	double acc = 0.0;
	double dec = 0.0;
	double MoveStartTime = 0.0;
	long lSize = 2, lCoordinate = 0;
	double dTimeAngle = 90.0;
	double dEndDeg1ToTime = 0.0;	//1도당 걸리는 시간 
	CString sMsg = "";
	axis[0] = Motor_PCB_X; //축번호
	axis[1] = Motor_PCB_Y;
	double dMidPos[2];
	double dEndPos[2];
	acc = model.dAcc;		//! 가감속도
	dec = model.dAcc;
	//
	dEndDeg1ToTime = (((model.dRadiusLength * 1) * M_PI) / (sqrt(model.dEpoxySpeed  * model.dEpoxySpeed / 2))) / 360;

	Task.bTrinityDoubleDispense = false;
	//1도당 걸리는 시간 = 원주율 / 속도 / 360
	while (1)
	{

		switch (step)
		{
		case 0:
			startTime = myTimer(true);
			step = 1000;
			break;
		case 1000:
			step = 2000;
			break;
			//
			//----------------------------------------------------------------------------------------------------------------------------
			//----------------------------------------------------------------------------------------------------------------------------
		case 2000:
			//두번째 원
			step = 2100; 
			break;
		case 2100:
			if (IsStopAxis(Motor_PCB_Z))
			{
				if (motor.Dispense_XY_Motor_Move(Dispense_Pos2, 10.0))
				{
					step = 2200;
				}
			}
			break;
		case 2200:
			if (IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y) && IsStopAxis(Motor_PCB_Z))
			{
				if (motor.Dispense_Z_Motor_Move(Dispense_Pos2, 5.0))
				{
					step = 2250; 
				}
			}
			break;

		case 2250:
			if (Task.bTrinityDoubleDispense == true) 
			{
				if (IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y) && IsStopAxis(Motor_PCB_Z))
				{
					//Z축 하단 회피
					Sleep(500);
					if (Straight_Dispense_MoveAxis(Motor_PCB_Z, REL, -0.4, model.dEpoxySpeed, model.dAcc))  
					{
						step = 2300;
					}
				}
			}
			else
			{
				
				step = 2300;
			}
			break;
		case 2300:

			startTime = myTimer(true);
			if (Dio.EpoxyDischargeOn2(true, true))		//Epoxy 토출 ON 
			{
				step = 2350;
			}
			else
			{
				sMsg.Format("[Dispence동작] Epoxy 토출 신호 이상 발생_토출 ON 신호");
				errMsg2(Task.AutoFlag, sMsg);
				step = 0;
			}
			break;

		case 2350:
			if (IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y) && IsStopAxis(Motor_PCB_Z))
			{
				Pcb_Motor_Twister_Move(180, false, 2);//회오리 180도씩 , 반지름 늘려가면서 도포
				step = 2400;

				MoveStartTime = myTimer(true);
			}
			break;
		case 2400:
			curTime = myTimer(true);
			if ((IsStopAxis(Motor_PCB_X)) && (IsStopAxis(Motor_PCB_Y)))
			{
				AxmMotSetMoveUnitPerPulse(Motor_PCB_X, 1, 1);	//Unit/Pulse 원래형태로 변경(1:1 매칭으로)
				AxmMotSetMoveUnitPerPulse(Motor_PCB_Y, 1, 1);
				if (!Dio.EpoxyDischargeOn2(false, false))		//Epoxy 토출 Off
				{
					sMsg.Format("[Dispence동작] Epoxy 토출 신호 이상 발생_토출 OFF 신호");
					errMsg2(Task.AutoFlag, sMsg);
					return false;
				}
				step = 2500;
			}
			break;
		case 2500:
			if (Task.bTrinityDoubleDispense == false)
			{
				if (IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y) && IsStopAxis(Motor_PCB_Z))
				{
					//Z축 하단 회피
					if (Straight_Dispense_MoveAxis(Motor_PCB_Z, REL, -3.0, model.dEpoxySpeed, model.dAcc))
					{
						Task.bTrinityDoubleDispense = true;	//덧 도포
						step = 2000;
						break;
					}
				} 
				step = 2500;
				break;
			}
			else
			{
				step = 3000;
				break;
			}
			break;
			//
			//----------------------------------------------------------------------------------------------------------------------------
			//----------------------------------------------------------------------------------------------------------------------------
		case 3000:
			Task.bTrinityDoubleDispense = false;
			step = 3050;
			break;
		case 3050:
			
			//세번째 원
			if (IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y) && IsStopAxis(Motor_PCB_Z))
			{
				//Z축 하단 회피
				if (Straight_Dispense_MoveAxis(Motor_PCB_Z, REL, 3.0 * -1, model.dEpoxySpeed, model.dAcc))
				{
					step = 3100;
				}
			}
			break;
		case 3100:
			if (IsStopAxis(Motor_PCB_Z))
			{
				if (motor.Dispense_XY_Motor_Move(Dispense_Pos3, 10.0))
				{
					step = 3200;
				}
			}
			break;
		case 3200:
			if (IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y) && IsStopAxis(Motor_PCB_Z))
			{
				if (motor.Dispense_Z_Motor_Move(Dispense_Pos3, 5.0))
				{
					step = 3250;
				}
			}
			break;
		case 3250:
			if (Task.bTrinityDoubleDispense == true)
			{
				if (IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y) && IsStopAxis(Motor_PCB_Z))
				{
					//Z축 하단 회피
					Sleep(500);
					if (Straight_Dispense_MoveAxis(Motor_PCB_Z, REL, -0.4, model.dEpoxySpeed, model.dAcc))
					{
						step = 3300;
						break;
					}
				}
			}
			else
			{

				step = 3300;
			}
			break;
		case 3300:
			startTime = myTimer(true);
			if (Dio.EpoxyDischargeOn2(true, true))		//Epoxy 토출 ON 
			{
				step = 3400;
			}
			else
			{
				sMsg.Format("[Dispence동작] Epoxy 토출 신호 이상 발생_토출 ON 신호");
				errMsg2(Task.AutoFlag, sMsg);
				step = 0;
			}
			break;
		case 3400:
			if (IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y) && IsStopAxis(Motor_PCB_Z))
			{
				Pcb_Motor_Twister_Move(180, false, 3);//회오리 180도씩 , 반지름 늘려가면서 도포
				step = 3500;

				MoveStartTime = myTimer(true);
			}
			break;
		
		case 3500: //모터 동작 완료까지 대기 
				   //if ((IsStopAxis(Motor_PCB_X) && GetInposition(Motor_PCB_X)) &&(IsStopAxis(Motor_PCB_Y) && GetInposition(Motor_PCB_Y)))
			if ((IsStopAxis(Motor_PCB_X)) && (IsStopAxis(Motor_PCB_Y)))
			{
				AxmMotSetMoveUnitPerPulse(Motor_PCB_X, 1, 1);	//Unit/Pulse 원래형태로 변경(1:1 매칭으로)
				AxmMotSetMoveUnitPerPulse(Motor_PCB_Y, 1, 1);

				if (!Dio.EpoxyDischargeOn2(false, false))		//Epoxy 토출 Off
				{
					sMsg.Format("[Dispence] Epoxy 토출 신호 이상 발생_토출 OFF 신호");
					errMsg2(Task.AutoFlag, sMsg);
					return false;
				}
				step = 4000;
			}
			break;
		case 4000:
			if (Task.bTrinityDoubleDispense == false)
			{
				if (IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y) && IsStopAxis(Motor_PCB_Z))
				{
					Task.bTrinityDoubleDispense = true;
					step = 3050; 
					break;
				}
			}
			else
			{
				step = 5000;
				break;
			}
			break;
		default:
			step = 5000;
			break;
		}

		if (step == 5000)		break;

		eTime = myTimer(true);
		if (eTime - startTime > 2000000) 
		{
			AxmMotSetMoveUnitPerPulse(Motor_PCB_X, 1, 1);	//Unit/Pulse 원래형태로 변경(1:1 매칭으로)
			AxmMotSetMoveUnitPerPulse(Motor_PCB_Y, 1, 1);

			StopAxis(Motor_PCB_X);
			StopAxis(Motor_PCB_Y);

			if (step>100)
			{
				int motorNo = step - 100;
				sMsg.Format("[Dispence동작]Circle 동작 이동 시간 초과");
			}
			else
			{
				sMsg.Format("PCB 부 Dispence 동작 Circle 이동 비정상");
			}
			errMsg2(Task.AutoFlag, sMsg);

			return false;
		}

		Sleep(5);
	}

	return true;
}
bool CAxlMotorSet::func_New_Epoxy_Rect_Arck_Draw()
{
	int step = 0;
	double startTime = 0.0;
	double eTime = 0.0;
	double curTime = 0.0;
	DWORD dwReturn = 0;
	long axis[2];
	double acc = 0.0;
	double dec = 0.0;
	double MoveStartTime = 0.0;
	long lSize = 2, lCoordinate = 0;
	double dTimeAngle = 90.0;
	double dEndDeg1ToTime = 0.0;	//1도당 걸리는 시간 
	CString sMsg = "";
	axis[0] = Motor_PCB_X; //축번호
	axis[1] = Motor_PCB_Y;
	double dMidPos[2];
	double dEndPos[2];
	acc = model.dAcc;		//! 가감속도
	dec = model.dAcc;
	//
	dEndDeg1ToTime = (((model.dRadiusLength * 1) * M_PI) / (sqrt(model.dEpoxySpeed  * model.dEpoxySpeed / 2))) / 360;
	//1도당 걸리는 시간 = 원주율 / 속도 / 360
	while (1)
	{

		switch (step)
		{
		case 0:
			if (model.dOnTime == 0.0)
			{
				Dio.EpoxyDischargeOn(true, false);
			}
			if (Continue_Line_Arck_Dispense() )//bottom Line
			{
				startTime = myTimer(true);
				step = 100;
			}
			break;

		case 100:
			if (model.dOnTime == 0.0)
			{
				step = 150;
				break;
			}
			curTime = myTimer(true);	//현재 시간을 얻어서 토출 On이후 대기 시간을 조절
			if (curTime - startTime > model.dOnTime * 1000)	//설정 Delay 시간 대기 후 토출
			{
				step = 110;
			}
			break;

		case 110:
			startTime = myTimer(true);
			if (Dio.EpoxyDischargeOn(true, false))		//Epoxy 토출 ON 
			{
				step = 120;
			}
			else
			{
				sLangChange.LoadStringA(IDS_STRING188);
				sMsg.Format(sLangChange);	//"[Dispence동작] Epoxy 토출 신호 이상 발생_토출 ON 신호"
				errMsg2(Task.AutoFlag, sMsg);
				step = -0;
			}
			break;
		case 150:
			step = 200;
			break;
		case 200:

			step = 400;
			break;
		case 400:
			if (IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y))
			{
				curTime = myTimer(true);
				if (!Dio.EpoxyDischargeOn(false, false))		//Epoxy 토출 Off
				{
					sMsg.Format("[Dispence동작] Epoxy 토출 신호 이상 발생_토출 OFF 신호");	//"[Dispence동작] Epoxy 토출 신호 이상 발생_토출 OFF 신호"
					errMsg2(Task.AutoFlag, sMsg);
					return false;
				}
				step = 410;
				
				//if ((dEndDeg1ToTime*dTimeAngle - model.dOffTime) * 1000  <  (curTime - MoveStartTime))
				//{
				//	if (!Dio.EpoxyDischargeOn(false, false))		//Epoxy 토출 Off
				//	{
				//		sMsg.Format("[Dispence동작] Epoxy 토출 신호 이상 발생_토출 OFF 신호");	//"[Dispence동작] Epoxy 토출 신호 이상 발생_토출 OFF 신호"
				//		errMsg2(Task.AutoFlag, sMsg);
				//		return false;
				//	}
				//	Dio.EpoxyDischargeOn(false, false);
				//	Sleep(model.dOffTime);

				//	step = 410;
				//}
			}
			break;
		case 410:
			if (IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y))
			{

				if (Straight_Dispense_MoveAxis(Motor_PCB_X, REL, model.dDisLength[4] * -1 * 0.2, model.dEpoxySpeed, model.dAcc))	//추가 보간
				{
					step = 500;
				}
			}
			break;
		case 500: //모터 동작 완료까지 대기
			if ((IsStopAxis(Motor_PCB_X) ) &&(IsStopAxis(Motor_PCB_Y) ))
			{
				step = 1000;
			}
			break;
		default:
			step = 1000;
			break;
		}

		if (step == 1000)		break;

		eTime = myTimer(true);
		if (eTime - startTime > 2000000)
		{
			StopAxis(Motor_PCB_X);
			StopAxis(Motor_PCB_Y);

			if (step>100)
			{
				int motorNo = step - 100;
				sMsg.Format("[Dispence동작][%s,%s 모터] Circle 동작 이동 시간 초과", MotorName[Motor_PCB_X], MotorName[Motor_PCB_Y]);
			}
			else
			{
				sMsg.Format("PCB 부 Dispence 동작 Circle 이동 비정상");
			}
			errMsg2(Task.AutoFlag, sMsg);

			return false;
		}

		Sleep(5);
	}

	return true;
}

bool CAxlMotorSet::func_Epoxy_Draw()
{
	int step=0;
	double startTime=0.0;
	double eTime = 0.0;
	double curTime = 0.0;
	double MoveStartTime = 0.0;
	DWORD dwReturn = 0;
	long axis[2];
	double acc, dec;
	long lSize = 2, lCoordinate = 0;
	CString sMsg;
	axis[0] = Motor_PCB_X; //축번호
	axis[1] = Motor_PCB_Y;
	
	
	acc = model.dAcc;		//! 가감속도
	dec = model.dAcc;
	Task.bMotorRunStop = true;
	while(1)
	{
		if (Task.bMotorRunStop == false)		//사각도포
		{
			Dio.EpoxyDischargeOn(false, false);
			StopAxis(Motor_PCB_X);
			StopAxis(Motor_PCB_Y);
			return false;
		}
		switch(step)
		{
		case 0:
			if(Straight_Dispense_MoveAxis(Motor_PCB_X, REL, (model.dDisLength[0]) * -1, model.dEpoxySpeed, model.dAcc))
			{
				startTime = myTimer(true);
				step = 100;
			}
			break;
					
		case 100:									
			curTime = myTimer(true);	//현재 시간을 얻어서 토출 On이후 대기 시간을 조절
			if( curTime-startTime > model.dOnTime * 100 )	//설정 Delay 시간 대기 후 토출
			{
				step = 110;
			}			
			break;

		case 110:									
			startTime = myTimer(true);
			if( Dio.EpoxyDischargeOn(true, true) )		//Epoxy 토출 ON 
			{
				step = 130;
			}
			else 
			{
				sLangChange.LoadStringA(IDS_STRING188);
				sMsg.Format(sLangChange);	//"[Dispence동작] Epoxy 토출 신호 이상 발생_토출 ON 신호"
				errMsg2(Task.AutoFlag, sMsg);
				step = -0;
			}
			break;

		case 130:
			if( IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y) )
			{
				if(Straight_Dispense_MoveAxis(Motor_PCB_Y, REL, (model.dDisLength[1]) * -1, model.dEpoxySpeed, model.dAcc))
				{
					step = 150;
				}
			}
			break;

		case 150:
			if( IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y) )
			{
				if(Straight_Dispense_MoveAxis(Motor_PCB_X, REL, (model.dDisLength[2]), model.dEpoxySpeed, model.dAcc))
				{
					step = 170;
				}
			}
			break;

		case 170:
			if( IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y) )
			{
				if(Straight_Dispense_MoveAxis(Motor_PCB_Y, REL, (model.dDisLength[3]), model.dEpoxySpeed, model.dAcc))
				{
					MoveStartTime = myTimer(true);
					step = 400;
				}
			}
			break;

		case 400:
			step = 450;
			//curTime = myTimer(true);
			//if (curTime - MoveStartTime > model.dOffTime * 1000)	//설정 Delay 시간 대기 후 모터 이동
			//{
			//	if (!Dio.EpoxyDischargeOn(false, false))		//Epoxy 토출 Off
			//	{
			//		sLangChange.LoadStringA(IDS_STRING187);
			//		sMsg.Format(sLangChange);	//"[Dispence동작] Epoxy 토출 신호 이상 발생_토출 OFF 신호"
			//		errMsg2(Task.AutoFlag, sMsg);
			//		Dio.EpoxyDischargeOn(false, false);

			//		return false;
			//	}
			//	Dio.EpoxyDischargeOn(false, false);
			//	step = 450;
			//}
				
			break;
		case 450:
			if ((IsStopAxis(Motor_PCB_X) && GetInposition(Motor_PCB_X)) &&
				(IsStopAxis(Motor_PCB_Y) && GetInposition(Motor_PCB_Y)))
			{
				//curTime = myTimer(true);
				if (!Dio.EpoxyDischargeOn(false, false))		//Epoxy 토출 Off
				{
					sMsg.Format("[Dispence동작] Epoxy 토출 신호 이상 발생_토출 OFF 신호");	
					errMsg2(Task.AutoFlag, sMsg);
					return false;
				}
				Dio.EpoxyDischargeOn(false, false);
				//Sleep(model.dOffTime);
				Straight_Dispense_MoveAxis(Motor_PCB_X, REL, model.dDisLength[0] * -1 * model.dDisLength[4], model.dEpoxySpeed, model.dAcc);	//추가 보간 = UI 상 DisLength 5 값으로 
				step = 500;
			}
			break;
		case 500: //모터 동작 완료까지 대기
			if( ( IsStopAxis(Motor_PCB_X) && GetInposition(Motor_PCB_X) ) && 
				( IsStopAxis(Motor_PCB_Y) && GetInposition(Motor_PCB_Y) ) ){
				step = 1000;	
				}
			break;
		default:
			step = 1000;
			break;
		}

		if(step==1000)		break;

		eTime = myTimer(true);
		if(eTime-startTime > 2000000)
		{
			StopAxis(Motor_PCB_X);
			StopAxis(Motor_PCB_Y);

			if(step>100){
				int motorNo = step - 100;
				sLangChange.LoadStringA(IDS_STRING189);
				sMsg.Format(sLangChange, MotorName[Motor_PCB_X], MotorName[Motor_PCB_Y]);	//"[Dispence동작][%s,%s 모터] Circle 동작 이동 시간 초과"
			} else {
				sLangChange.LoadStringA(IDS_STRING996);
				sMsg.Format(sLangChange);
			}
			errMsg2(Task.AutoFlag, sMsg);

			return false;
		}

		Sleep(5);
	}

	return true;

}

bool CAxlMotorSet::func_Epoxy_CircleDraw(bool CONTI)//Dispenser 실제 도포 하며 원호 보간 구동
{
	int step=0;
	double startTime;
	double MoveStartTime;
	double eTime, curTime;
	CString sMsg;
	double dEndDeg1ToTime = 0.0;	//1도당 걸리는 시간 
	double dTimeAngle = 0.0;
	double dDrawAng = 0.0;
	double dDrawLength = 0.0;
	int SizeCheck = 0;
	int dCircleSpeed = 0.0;
	double dCircleOffTime = 0.0;
	 
	dDrawLength = model.dRadiusLength;
	dDrawAng = model.dAngle;
	dCircleSpeed = model.dCircleSpeed;
	dCircleOffTime = model.dOffTime;
	//dConti_RadiusLength
	//dConti_Angle
	//----------------------------------------------------------------------------
	bool mOffCheck = false;
	if (dDrawAng > 360)	//if (model.dAngle > 360)
	{
		dTimeAngle = 360;		//Epoxy 토출 Off Time시 계사
	}
	else
	{
		dTimeAngle = dDrawAng;
	}

	//1도당 걸리는 시간 = (원주율 * 속도) / 360 /   가속/감속
	//dEndDeg1ToTime = (( (model.dRadiusLength * 1) * M_PI) / (sqrt(model.dCircleSpeed  * model.dCircleSpeed/2)) ) / 360;	//1도당 걸리는 시간 = 원주율 / 속도 / 360
	  dEndDeg1ToTime = (( (dDrawLength * 1) * M_PI) / (sqrt(dCircleSpeed  * dCircleSpeed /2)) ) / 360;	//1도당 걸리는 시간 = 원주율 / 속도 / 360
	//dEndDeg1ToTime = (( (model.dRadiusLength * 1) * M_PI) / sqrt(model.dSpeed) ) / 360;	//1도당 걸리는 시간 = 원주율 / 속도 / 360
	Task.bMotorRunStop = true;
	while(1)
	{
		if (Task.bMotorRunStop == false)	//원형 도포
		{
			Dio.EpoxyDischargeOn(false, false);

			StopAxis(Motor_PCB_X);
			StopAxis(Motor_PCB_Y);

			AxmMotSetMoveUnitPerPulse(Motor_PCB_X, 1, 1);	//Unit/Pulse 원래형태로 변경(1:1 매칭으로)
			AxmMotSetMoveUnitPerPulse(Motor_PCB_Y, 1, 1);
			return false;
		}
		switch(step)
		{
		case 0:									
			startTime = myTimer(true);
			if( Dio.EpoxyDischargeOn(true, true) )		//Epoxy 토출 ON 
			{
				step = 100;
			}
			else 
			{
				sMsg.Format("[Dispence동작] Epoxy 토출 신호 이상 발생_토출 ON 신호");
				errMsg2(Task.AutoFlag, sMsg);
				return false;
			}
			break;
		case 100:								
			curTime = myTimer(true);	//현재 시간을 얻어서 토출 On이후 대기 시간을 조절
			if( curTime-startTime > model.dOnTime * 1000 )	//설정 Delay 시간 대기 후 모터 이동
			{
				Pcb_Motor_CircleMove(dTimeAngle, false , SizeCheck);		//정원 그리기
				//PcbDis_Motor_CircleMove(dTimeAngle, false, SizeCheck);		//정원 그리기
				MoveStartTime = myTimer(true);
				step = 200;
			}
			break;
		case 200:// 모터 도착전 토출 OFF Time 처리
			curTime = myTimer(true);
			//1도당시간*각도 - (출발시간-현재시간) < 설정시간

			if (((dEndDeg1ToTime*dTimeAngle) - dCircleOffTime) * 1000 < (curTime - MoveStartTime)  && mOffCheck == false)
			{
				mOffCheck = true;
				Dio.EpoxyDischargeOn(false, false);
			}
			if (IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y))//if (IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y)) 
			{
				if( !Dio.EpoxyDischargeOn(false, false/*true*/) )		//Epoxy 토출 Off
				{
					sMsg.Format("[Dispence동작] Epoxy 토출 신호 이상 발생_토출 OFF 신호");
					errMsg2(Task.AutoFlag, sMsg);
					Dio.EpoxyDischargeOn(false, false);
					
					AxmMotSetMoveUnitPerPulse(Motor_PCB_X, 1, 1);	//Unit/Pulse 원래형태로 변경(1:1 매칭으로)
					AxmMotSetMoveUnitPerPulse(Motor_PCB_Y, 1, 1);
					return false;
				}
				else
				{
					if(dDrawAng > 360)	step = 400;	//360도 보다 많을 경우 더 회전(원호보간에서 360도까지 허용됨,)
					else					step = 500;	//360도 보다 작을 경우 더이상 회전 안함
				}
			}
			break;

		case 400:
			if( ( IsStopAxis(Motor_PCB_X) && GetInposition(Motor_PCB_X) ) &&
				( IsStopAxis(Motor_PCB_Y) && GetInposition(Motor_PCB_Y) ) )
			{
				Pcb_Motor_CircleMove(dDrawAng - dTimeAngle, true , SizeCheck);	//추가 각도 보간
				//PcbDis_Motor_CircleMove(dDrawAng - dTimeAngle, true, SizeCheck);	//추가 각도 보간
				step = 500;	
			}
			break;

		case 500: //모터 동작 완료까지 대기
			if( ( IsStopAxis(Motor_PCB_X) && GetInposition(Motor_PCB_X) ) &&
				( IsStopAxis(Motor_PCB_Y) && GetInposition(Motor_PCB_Y) ) ){
				AxmMotSetMoveUnitPerPulse(Motor_PCB_X, 1, 1);	//Unit/Pulse 원래형태로 변경(1:1 매칭으로)
				AxmMotSetMoveUnitPerPulse(Motor_PCB_Y, 1, 1);
				step = 1000;	
				}
			break;
		default:
			step = 1000;
			break;
		}

		if(step==1000)		break;

		eTime = myTimer(true);
		if(eTime-startTime > 100000)
		{
			StopAxis(Motor_PCB_X);
			StopAxis(Motor_PCB_Y);

			if(step>100){
				int motorNo = step - 100;
				sMsg.Format("[Dispence동작][%s,%s 모터] Circle 동작 이동 시간 초과", MotorName[Motor_PCB_X], MotorName[Motor_PCB_Y]);
			} else {
				sMsg.Format("PCB 부 Dispence 동작 Circle 이동 비정상");
			}
			errMsg2(Task.AutoFlag, sMsg);

			AxmMotSetMoveUnitPerPulse(Motor_PCB_X,1,1);	//Unit/Pulse 원래형태로 변경
			AxmMotSetMoveUnitPerPulse(Motor_PCB_Y,1,1);

			return false;
		}

		Sleep(5);
		checkMessage();
	}

	AxmMotSetMoveUnitPerPulse(Motor_PCB_X, 1, 1);	//Unit/Pulse 원래형태로 변경(1:1 매칭으로)
	AxmMotSetMoveUnitPerPulse(Motor_PCB_Y, 1, 1);
	return true;
}

bool CAxlMotorSet::func_Epoxy_Point_Draw() 
{
	int step = 0;
	double startTime = 0.0;
	double eTime = 0.0;
	double curTime = 0.0;
	DWORD dwReturn = 0;
	long axis[2];
	double acc, dec;
	double dMovePos = 0.0;
	double dMoveZGap = 4.0;
	long lSize = 2, lCoordinate = 0;
	CString sMsg;
	axis[0] = Motor_PCB_X; //축번호
	axis[1] = Motor_PCB_Y;


	acc = model.dAcc;		//! 가감속도
	dec = model.dAcc;

	while (1)
	{

		switch (step)
		{
		case 0:
			startTime = myTimer(true);
			if (Dio.EpoxyDischargeOn(true, true) == false)		//Epoxy 토출 ON 
			{
				sMsg.Format("[Dispence동작] Epoxy 토출 신호 이상 발생_토출 ON 신호");
				errMsg2(Task.AutoFlag, sMsg);
				step = -0;
				break;
			}
			step = 100;
			Task.PCBTaskTime = myTimer(true); 
			break;
		case 100:
			if (myTimer(true) - Task.PCBTaskTime > model.dSmallOffTime * 1000)
			{
				if (Dio.EpoxyDischargeOn(false, false) == false)		//Epoxy 토출 Off
				{
					sMsg.Format("[Dispence동작] Epoxy 토출 신호 이상 발생_토출 OFF 신호");
					errMsg2(Task.AutoFlag, sMsg);
					return false;
				}
				step = 110;
			}
			break;
		case 110:
			//z축 하강
			dMovePos = motor.GetCommandPos(Motor_PCB_Z) - dMoveZGap;
			motor.MoveAxis(Motor_PCB_Z, ABS, dMovePos, sysData.fMotorSpeed[Motor_PCB_Z], sysData.fMotorAccTime[Motor_PCB_Z]);
			step = 120;
			Task.PCBTaskTime = myTimer(true);
			break;
		case 120:
			//z축 정지 확인
			if ((motor.IsStopAxis(Motor_PCB_Z)))
			{
				step = 150;
			}
			else if ((myTimer(true) - Task.PCBTaskTime) > 5000)
			{
				sMsg.Format("[Dispence동작] pcb Z 정지 이상 - %d", step);
				errMsg2(Task.AutoFlag, sMsg);
				step = -120;
				break;
			}
			break;
		case 150:
			//2번째 Point 이동
			if (Straight_Dispense_MoveAxis(Motor_PCB_X, REL, (model.dDisLength[0]) * -1, model.dEpoxySpeed, model.dAcc))
			{
				startTime = myTimer(true);
				step = 160;
			}
			break;
		case 160:
			if (IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y))
			{
				step = 200;
			}
			break;
		case 200:
			//z축 상승
			dMovePos = motor.GetCommandPos(Motor_PCB_Z) + dMoveZGap;
			motor.MoveAxis(Motor_PCB_Z, ABS, dMovePos, sysData.fMotorSpeed[Motor_PCB_Z], sysData.fMotorAccTime[Motor_PCB_Z]);
			Task.PCBTaskTime = myTimer(true);
			step = 210;
			break;
		case 210:
			//z축 정지확인
			if ((motor.IsStopAxis(Motor_PCB_Z)))
			{
				step = 250;
			}
			else if ((myTimer(true) - Task.PCBTaskTime) > 5000)
			{
				sMsg.Format("[Dispence동작] pcb Z 정지 이상 - %d", step);
				errMsg2(Task.AutoFlag, sMsg);
				step = -210;
				break;
			}
			break;
		case 250:
			if (Dio.EpoxyDischargeOn(true, true) == false)		//Epoxy 토출 ON 
			{
				sMsg.Format("[Dispence동작] Epoxy 토출 신호 이상 발생_토출 ON 신호");
				errMsg2(Task.AutoFlag, sMsg);
				step = -250;
				break;
			}
			step = 260;
			startTime = myTimer(true);
			break;
		case 260:
			if (myTimer(true) - startTime > model.dSmallOffTime * 1000)
			{
				if (Dio.EpoxyDischargeOn(false, false) == false)		//Epoxy 토출 Off
				{
					sMsg.Format("[Dispence동작] Epoxy 토출 신호 이상 발생_토출 OFF 신호");
					errMsg2(Task.AutoFlag, sMsg);
					return false;
				}
				step = 270;
			}
			break;
		case 270:
			//z축 하강
			dMovePos = motor.GetCommandPos(Motor_PCB_Z) - dMoveZGap;
			motor.MoveAxis(Motor_PCB_Z, ABS, dMovePos, sysData.fMotorSpeed[Motor_PCB_Z], sysData.fMotorAccTime[Motor_PCB_Z]);
			Task.PCBTaskTime = myTimer(true);
			step = 280;
			break;
		case 280:
			//z축 정지 확인
			if ((motor.IsStopAxis(Motor_PCB_Z)))
			{
				step = 300;
			}
			else if ((myTimer(true) - Task.PCBTaskTime) > 5000)
			{
				sMsg.Format("[Dispence동작] pcb Z 정지 이상 - %d" , step);
				errMsg2(Task.AutoFlag, sMsg);
				step = -280;
				break;
			}
			break;
		case 300:
			//2번째 Point 이동
			if (Straight_Dispense_MoveAxis(Motor_PCB_Y, REL, (model.dDisLength[1]) * -1, model.dEpoxySpeed, model.dAcc))
			{
				startTime = myTimer(true);
				step = 310;
			}
			break;
		case 310:
			if (IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y))
			{
				step = 350;
			}
			break;
		case 350:
			//z축 상승
			dMovePos = motor.GetCommandPos(Motor_PCB_Z) + dMoveZGap;
			motor.MoveAxis(Motor_PCB_Z, ABS, dMovePos, sysData.fMotorSpeed[Motor_PCB_Z], sysData.fMotorAccTime[Motor_PCB_Z]);
			Task.PCBTaskTime = myTimer(true);
			step = 360;
			break;
		case 360:
			//z축 정지확인
			if ((motor.IsStopAxis(Motor_PCB_Z)))
			{
				step = 400;
			}
			else if ((myTimer(true) - Task.PCBTaskTime) > 5000)
			{
				sMsg.Format("[Dispence동작] pcb Z 정지 이상 - %d", step);
				errMsg2(Task.AutoFlag, sMsg);
				step = -360;
				break;
			}
			break;
		case 400:
			if (Dio.EpoxyDischargeOn(true, true) == false)		//Epoxy 토출 ON 
			{
				sMsg.Format("[Dispence동작] Epoxy 토출 신호 이상 발생_토출 ON 신호");
				errMsg2(Task.AutoFlag, sMsg);
				step = -400;
				break;
			}
			step = 410;
			startTime = myTimer(true);
			break;
		case 410:
			curTime = myTimer(true);	//현재 시간을 얻어서 토출 On이후 대기 시간후 off
			if (curTime - startTime > model.dSmallOffTime * 1000)
			{
				if (Dio.EpoxyDischargeOn(false, false) == false)		//Epoxy 토출 Off
				{
					sMsg.Format("[Dispence동작] Epoxy 토출 신호 이상 발생_토출 OFF 신호");
					errMsg2(Task.AutoFlag, sMsg);
					return false;
				}
				step = 420;
			}
			break;
		case 420:
			//z축 하강
			dMovePos = motor.GetCommandPos(Motor_PCB_Z) - dMoveZGap;
			motor.MoveAxis(Motor_PCB_Z, ABS, dMovePos, sysData.fMotorSpeed[Motor_PCB_Z], sysData.fMotorAccTime[Motor_PCB_Z]);
			Task.PCBTaskTime = myTimer(true);
			step = 430;
			break;
		case 430:
			//z축 하강 확인
			if ((motor.IsStopAxis(Motor_PCB_Z)))
			{
				step = 450;
			}
			else if ((myTimer(true) - Task.PCBTaskTime) > 5000)
			{
				sMsg.Format("[Dispence동작] pcb Z 정지 이상 - %d", step);
				errMsg2(Task.AutoFlag, sMsg);
				step = -430;
				break;
			}
			break;
		case 450:
			//2번째 Point 이동
			if (Straight_Dispense_MoveAxis(Motor_PCB_X, REL, (model.dDisLength[2]) * 1, model.dEpoxySpeed, model.dAcc))
			{
				startTime = myTimer(true);
				step = 460;
			}
			break;
		case 460:
			if (IsStopAxis(Motor_PCB_X) && IsStopAxis(Motor_PCB_Y))
			{
				step = 470;
			}
			break;
		case 470:
			//z축 상승
			dMovePos = motor.GetCommandPos(Motor_PCB_Z) + dMoveZGap;
			motor.MoveAxis(Motor_PCB_Z, ABS, dMovePos, sysData.fMotorSpeed[Motor_PCB_Z], sysData.fMotorAccTime[Motor_PCB_Z]);
			Task.PCBTaskTime = myTimer(true);
			step = 480;
			break;
		case 480:
			//z축 상승 확인
			if ((motor.IsStopAxis(Motor_PCB_Z)))
			{
				step = 500;
			}
			else if ((myTimer(true) - Task.PCBTaskTime) > 5000)
			{
				sMsg.Format("[Dispence동작] pcb Z 정지 이상 - %d", step);
				errMsg2(Task.AutoFlag, sMsg);
				step = -480;
				break;
			}
			break;
		case 500:
			if (Dio.EpoxyDischargeOn(true, true) == false)		//Epoxy 토출 ON 
			{
				sMsg.Format("[Dispence동작] Epoxy 토출 신호 이상 발생_토출 ON 신호");
				errMsg2(Task.AutoFlag, sMsg);
				step = -500;
				break;
			}
			step = 510;
			startTime = myTimer(true);
			break;
		case 510:
			if (myTimer(true) - startTime > model.dSmallOffTime * 1000)
			{
				if (Dio.EpoxyDischargeOn(false, false) == false)		//Epoxy 토출 Off
				{
					sMsg.Format("[Dispence동작] Epoxy 토출 신호 이상 발생_토출 OFF 신호");
					errMsg2(Task.AutoFlag, sMsg);
					return false;
				}
				step = 600;
			}
			break;
		case 600:
			if ((IsStopAxis(Motor_PCB_X) && GetInposition(Motor_PCB_X)) &&
				(IsStopAxis(Motor_PCB_Y) && GetInposition(Motor_PCB_Y)))
			{
				if (!Dio.EpoxyDischargeOn(false, false))		//Epoxy 토출 Off
				{
					sMsg.Format("[Dispence동작] Epoxy 토출 신호 이상 발생_토출 OFF 신호");
					errMsg2(Task.AutoFlag, sMsg);
					return false;
				}
				step = 1000;
			}
			break;
		default:
			step = 1000;
			break;
		}

		if (step == 1000)		break;

		eTime = myTimer(true);
		if (eTime - startTime > 2000000)
		{
			StopAxis(Motor_PCB_X);
			StopAxis(Motor_PCB_Y);

			if (step>100) {
				int motorNo = step - 100;
				sLangChange.LoadStringA(IDS_STRING189);
				sMsg.Format(sLangChange, MotorName[Motor_PCB_X], MotorName[Motor_PCB_Y]);	//"[Dispence동작][%s,%s 모터] Circle 동작 이동 시간 초과"
			}
			else {
				sLangChange.LoadStringA(IDS_STRING996);
				sMsg.Format(sLangChange);
			}
			errMsg2(Task.AutoFlag, sMsg);

			return false;
		}

		Sleep(5);
		checkMessage();
	}

	return true;

}

bool CAxlMotorSet::Pcb_Motor_Twister_Move(double dAngle, bool bWait, int Pos)
{	
	//원호 보간 구동(PCB X/Y축) -> bWait=true일 경우 완료 동작 까지 Check,
	//**** bWait=false 일 경우 Unit/Pulse를 원래대로 돌리지 않으니 외부에서 해줘야 함.,,,
	DWORD dwReturn = 0;
	long axis[2];
	double acc = 0.0;
	double dec = 0.0;
	double dMidPos[2];
	double dEndPos[2];
	long lSize = 2, lCoordinate = 0, eTime;

	CString sMsg = _T("");
	//TRINITY
	bool TrinityCircleChange = false;
	int TrinityAlgle = 0;
	double TrinityCircleRadius = 0.0;

	if (!m_bOrgFlag[Motor_PCB_X] || !m_bOrgFlag[Motor_PCB_Y])
	{
		sLangChange.LoadStringA(IDS_STRING1001);
		sMsg.Format(sLangChange);	//PCB 부 모터가 원점 복귀를 하지 않았습니다.
		errMsg2(Task.AutoFlag, sMsg);
		return false;
	}


	axis[0] = Motor_PCB_X; //축번호
	axis[1] = Motor_PCB_Y;


	acc = model.dAcc;		//! 가감속도
	dec = model.dAcc;
	double TEMPRadiusLength = 0.0;
	long MOTOR_DIR = DIR_CCW;
	//dMidPos[0] = 0;	//원의 중심 위치 X	
	//dMidPos[1] = (sqrt(model.dRadiusLength * model.dRadiusLength + model.dRadiusLength * model.dRadiusLength) * -1 ) * 0.53;//0.65;	//				Y

	double offsetR1_X = 0.0;
	double offsetR2_X = 0.0;
	double offsetR3_X = 0.0;
	double offsetR4_X = 0.0;
	double offsetR1_Y = 0.0;
	double offsetR2_Y = 0.0;
	double offsetR3_Y = 0.0;
	double offsetR4_Y = 0.0;

	double CircleRadius = 0.0;
	double CircleSpeed = 0.0;

	CircleRadius = model.dRadiusLength;
	CircleSpeed = model.dTwister_Speed;	// model.dEpoxySpeed;


	//motor x,y resolution 값 비교하여 큰 값을 넣어주면 됩니다..
	//현재 resolution 값이 x : 5000  y : 1000 이므로 5000을 넣어 주었습니다.
	//주의할점은 도포하기전에 펄스 변경하시고 도포끝나면 바로 1:1로 바꾸어 주어야 합니다..
	//그렇지 않으면 모터가 이상하게 동작합니다..
	// 

	///////////////////////////////////////////////////////////////////////////////////////////////////

	AxmContiWriteClear(lCoordinate);
	AxmContiSetAxisMap(lCoordinate, lSize, axis);
	double dRadius[3][4] = {
		{ 0.2 , 0.4 , 0.6 , 0.8 } ,
		{ 0.2 , 0.4 , 0.8 , 1.0 } ,  
		{ 0.5 , 1.2 , 2.4 , 3.6 }
	};
	AxmContiSetAbsRelMode(lCoordinate, 1);		//상태위치 구동(1) , 절대좌표(0)
	CircleSpeed = 2;
	AxmContiBeginNode(lCoordinate);
	if (Pos == 3) 
	{
		//큰 원
		CircleSpeed = model.dTwister_Speed * sysData.fMotorResol[Motor_PCB_X];
	}
	else
	{
		//작은 원
		CircleSpeed = (model.dTwister_Speed * 0.8) * sysData.fMotorResol[Motor_PCB_X];
	}
	
	int dic = -1;
	for (int i = 0; i < 4; i++)
	{ 
		if (i == 3)
		{
			if (Pos == 3) {
				dAngle = 350;
			}
			else
			{
				dAngle = 270;
			}
			
		}
		TrinityCircleRadius = dRadius[Pos - 1][i];	// 0.5; 
		dMidPos[0] = 0.0; 
		dMidPos[1] =((sqrt(TrinityCircleRadius * TrinityCircleRadius + TrinityCircleRadius * TrinityCircleRadius) * dic) * 0.5) * 10000.0;
		AxmCircleAngleMove(lCoordinate, axis, dMidPos, dAngle, CircleSpeed, acc, dec, MOTOR_DIR);
		dic *= -1;
	} 
	
	AxmContiEndNode(lCoordinate);
	// 상대위치 구동시작.
	AxmContiSetAbsRelMode(lCoordinate, 1);
	// 연속보간구동 시작.
	AxmContiStart(lCoordinate, 0, 0);


	int step = 0;
	double startTime = 0.0;
	while (1)
	{
		switch (step)
		{
		case 0:
			startTime = myTimer(true);
			if (bWait == true)	step = 100;	//완료 Check
			else				step = 1000; //종료
			break;
		case 100:								// 이동 완료 확인..
			if (IsStopAxis(Motor_PCB_X) && GetInposition(Motor_PCB_X))
			{
				AxmMotSetMoveUnitPerPulse(Motor_PCB_X, 1, 1);	//Unit/Pulse 원래형태로 변경
				AxmMotSetMoveUnitPerPulse(Motor_PCB_Y, 1, 1);
				step = 1000;
			}
			break;
		default:
			break;
		}

		if (step == 1000)		break;

		eTime = myTimer(true);
		if (eTime - startTime > 30000)
		{
			StopAxis(Motor_PCB_X);
			StopAxis(Motor_PCB_Y);

			if (step>100) 
			{
				int motorNo = step - 100;
				sMsg.Format("[Dispence동작] Circle 동작 이동 시간 초과");	//"[Dispence동작][%s,%s 모터] Circle 동작 이동 시간 초과"
			}
			else 
			{
				sMsg.Format("PCB 부 Dispence 동작 Circle 이동 비정상");
			}
			errMsg2(Task.AutoFlag, sMsg);

			AxmMotSetMoveUnitPerPulse(Motor_PCB_X, 1, 1);	//Unit/Pulse 원래형태로 변경
			AxmMotSetMoveUnitPerPulse(Motor_PCB_Y, 1, 1);
			return false;
		}
		Sleep(5);
	}
	if (bWait == true)
	{
		AxmMotSetMoveUnitPerPulse(Motor_PCB_X, 1, 1);	//Unit/Pulse 원래형태로 변경(1:1 매칭으로)
		AxmMotSetMoveUnitPerPulse(Motor_PCB_Y, 1, 1);
	}

	return true;
}

bool CAxlMotorSet::Pcb_Motor_CircleMove(double dAngle, bool bWait, int Pos)
{	
	
	//원호 보간 구동(PCB X/Y축) -> bWait=true일 경우 완료 동작 까지 Check,
	//**** bWait=false 일 경우 Unit/Pulse를 원래대로 돌리지 않으니 외부에서 해줘야 함.,,,

	DWORD dwReturn = 0;
	long axis[2];
	double acc, dec;
	double dMidPos[2];
	double dEndPos[2];
	long lSize = 2, lCoordinate = 0, eTime;


	CString sMsg = _T("");

	//TRINITY
	bool TrinityCircleChange = false;
	int TrinityAlgle = 0;
	double TrinityCircleRadius = 0.0;

	if (!m_bOrgFlag[Motor_PCB_X] || !m_bOrgFlag[Motor_PCB_Y])
	{
		sLangChange.LoadStringA(IDS_STRING1001);
		sMsg.Format(sLangChange);	//PCB 부 모터가 원점 복귀를 하지 않았습니다.
		errMsg2(Task.AutoFlag, sMsg);
		return false;
	}


	axis[0] = Motor_PCB_X; //축번호
	axis[1] = Motor_PCB_Y;


	acc = model.dAcc;		//! 가감속도
	dec = model.dAcc;

	double TEMPRadiusLength = 0.0;

	long MOTOR_DIR;

	//dMidPos[0] = 0;	//원의 중심 위치 X	
	//dMidPos[1] = (sqrt(model.dRadiusLength * model.dRadiusLength + model.dRadiusLength * model.dRadiusLength) * -1 ) * 0.53;//0.65;	//				Y

	double offsetR1_X = 0.0;
	double offsetR2_X = 0.0;
	double offsetR3_X = 0.0;
	double offsetR4_X = 0.0;
	double offsetR1_Y = 0.0;
	double offsetR2_Y = 0.0;
	double offsetR3_Y = 0.0;
	double offsetR4_Y = 0.0;

	double CircleRadius = 0.0;
	double CircleSpeed = 0.0;
	if (Pos == 999)
	{
		CircleRadius = model.dConti_RadiusLength;//dConti_RadiusLength
		CircleSpeed = model.dSmallSpeed;
	}
	else if (Pos == 100 || Pos == 200 || Pos == 300 || Pos == 400)
	{
		CircleRadius = model.dConti_RadiusLength;//dConti_RadiusLength
		CircleSpeed = model.dSmallSpeed;
	}
	else
	{
		CircleRadius = model.dRadiusLength;
		CircleSpeed = model.dCircleSpeed;	// model.dEpoxySpeed;
	}

	offsetR1_X = model.dCircleRadiusCenterOffsetX[0];
	offsetR2_X = model.dCircleRadiusCenterOffsetX[1];
	offsetR3_X = model.dCircleRadiusCenterOffsetX[2];
	offsetR4_X = model.dCircleRadiusCenterOffsetX[3];
	//
	offsetR1_Y = model.dCircleRadiusCenterOffsetY[0];
	offsetR2_Y = model.dCircleRadiusCenterOffsetY[1];
	offsetR3_Y = model.dCircleRadiusCenterOffsetY[2];
	offsetR4_Y = model.dCircleRadiusCenterOffsetY[3];

	if (offsetR1_X > 10.0)offsetR1_X = 10.0;
	if (offsetR2_X > 10.0)offsetR2_X = 10.0;
	if (offsetR3_X > 10.0)offsetR3_X = 10.0;
	if (offsetR4_X > 10.0)offsetR4_X = 10.0;
	if (offsetR1_X < -10.0)offsetR1_X = -10.0;
	if (offsetR2_X < -10.0)offsetR2_X = -10.0;
	if (offsetR3_X < -10.0)offsetR3_X = -10.0;
	if (offsetR4_X < -10.0)offsetR4_X = -10.0;
	//
	if (offsetR1_Y > 10.0)offsetR1_Y = 10.0;
	if (offsetR2_Y > 10.0)offsetR2_Y = 10.0;
	if (offsetR3_Y > 10.0)offsetR3_Y = 10.0;
	if (offsetR4_Y > 10.0)offsetR4_Y = 10.0;
	if (offsetR1_Y < -10.0)offsetR1_Y = -10.0;
	if (offsetR2_Y < -10.0)offsetR2_Y = -10.0;
	if (offsetR3_Y < -10.0)offsetR3_Y = -10.0;
	if (offsetR4_Y < -10.0)offsetR4_Y = -10.0;
	switch (Pos)
	{
	case 0:
		//기존 원형 도포 방식
		dMidPos[0] = 0;	//원의 중심 위치 X	
		dMidPos[1] = (sqrt(CircleRadius * CircleRadius + CircleRadius * CircleRadius) * -1) * 0.5;//Y
		MOTOR_DIR = DIR_CCW;
		break;
		//=======================================================================================================================================
		//=======================================================================================================================================
	case 100://우측하단
		dMidPos[0] = model.dCircleRadiusCenterOffsetX[0];
		dMidPos[1] = model.dCircleRadiusCenterOffsetY[0];
		dEndPos[0] = model.dCircleRadiusEndOffsetX[0];
		dEndPos[1] = model.dCircleRadiusEndOffsetY[0];
		MOTOR_DIR = DIR_CCW;


		break;
	case 200://우측상단
		//
		dMidPos[0] = model.dCircleRadiusCenterOffsetX[1];
		dMidPos[1] = model.dCircleRadiusCenterOffsetY[1];
		dEndPos[0] = model.dCircleRadiusEndOffsetX[1];
		dEndPos[1] = model.dCircleRadiusEndOffsetY[1];
		MOTOR_DIR = DIR_CW;

		break;
	case 300://좌측상단
		dMidPos[0] = model.dCircleRadiusCenterOffsetX[2];
		dMidPos[1] = model.dCircleRadiusCenterOffsetY[2];
		dEndPos[0] = model.dCircleRadiusEndOffsetX[2];
		dEndPos[1] = model.dCircleRadiusEndOffsetY[2];
		MOTOR_DIR = DIR_CCW;

		break;
	case 400://좌측하단
		dMidPos[0] = model.dCircleRadiusCenterOffsetX[3];
		dMidPos[1] = model.dCircleRadiusCenterOffsetY[3];
		dEndPos[0] = model.dCircleRadiusEndOffsetX[3];
		dEndPos[1] = model.dCircleRadiusEndOffsetY[3];
		MOTOR_DIR = DIR_CW;

		break;
	
	case 999:
		//기존 원형 도포 방식 conti
		dMidPos[0] = 0;	//원의 중심 위치 X	 
		dMidPos[1] = (sqrt(CircleRadius * CircleRadius + CircleRadius * CircleRadius) * -1) * 0.5;//Y
		MOTOR_DIR = DIR_CCW;
		break;
	default:
		return false;
		break;
	}
	//20150603 - motor x,y resolution 값 비교하여 큰 값을 넣어주면 됩니다..
	//현재 resolution 값이 x : 5000  y : 1000 이므로 5000을 넣어 주었습니다.
	//주의할점은 도포하기전에 펄스 변경하시고 도포끝나면 바로 1:1로 바꾸어 주어야 합니다..
	//그렇지 않으면 모터가 이상하게 동작합니다..
	//



//20150603 - motor x,y resolution 값 비교하여 큰 값을 넣어주면 됩니다..
//현재 resolution 값이 x : 5000  y : 1000 이므로 5000을 넣어 주었습니다.
//주의할점은 도포하기전에 펄스 변경하시고 도포끝나면 바로 1:1로 바꾸어 주어야 합니다..
//그렇지 않으면 모터가 이상하게 동작합니다..
// 

	dwReturn = AxmMotSetMoveUnitPerPulse(Motor_PCB_X, 1, 1000);	//Unit/Pulse 변경 - X
	dwReturn = AxmMotSetMoveUnitPerPulse(Motor_PCB_Y, 1, 1000);	//					Y



	///////////////////////////////////////////////////////////////////////////////////////////////////

	AxmContiWriteClear(lCoordinate);
	AxmContiSetAxisMap(lCoordinate, lSize, axis);
	AxmContiSetAbsRelMode(lCoordinate, 1);		//상태위치 구동(1) , 절대좌표(0)
	

	//AxmCircleAngleMove(lCoordinate, axis, dMidPos, dAngle, model.dEpoxySpeed, acc, dec, DIR_CCW);  //반시계방향 원그리기 명령:DIR_CCW

	if (Pos == 0)
	{
		AxmCircleAngleMove(lCoordinate, axis, dMidPos, dAngle, CircleSpeed, acc, dec, MOTOR_DIR);
	}
	else
	{
		//반원
		////AxmCircleCenterMove(lCoordinate, axis, dMidPos, dEndPos, CircleSpeed, acc, dec, MOTOR_DIR);
		AxmCirclePointMove(lCoordinate, axis, dMidPos, dEndPos, CircleSpeed, acc, dec, 0);	///기존 설정값 때문에 마곡거 사용
		//0 = Arc
		//1 = Circle
	}
	int step=0;
	double startTime;
	while(1)
	{
		switch(step)
		{
		case 0:									
			startTime = myTimer(true);
			if( bWait == true)	step = 100;	//완료 Check
			else				step = 1000; //종료
			break;
		case 100:								// 이동 완료 확인..
			if ((IsStopAxis(Motor_PCB_X) && GetInposition(Motor_PCB_X)) &&
				(IsStopAxis(Motor_PCB_Y) && GetInposition(Motor_PCB_Y))) {
				step = 1000;
			}
			break;
		default:
			break;
		}

		if(step==1000)		break;

		eTime = myTimer(true);
		if(eTime-startTime > 30000)
		{
			StopAxis(Motor_PCB_X);
			StopAxis(Motor_PCB_Y);

			if(step>100){
				int motorNo = step - 100;
				sMsg.Format("[Dispence동작][%s,%s 모터] Circle 동작 이동 시간 초과", MotorName[Motor_PCB_X], MotorName[Motor_PCB_Y]);	//"[Dispence동작][%s,%s 모터] Circle 동작 이동 시간 초과"
			} else {
				sMsg.Format("PCB 부 Dispence 동작 Circle 이동 비정상");
			}
			errMsg2(Task.AutoFlag, sMsg);

			AxmMotSetMoveUnitPerPulse(Motor_PCB_X,1,1);	//Unit/Pulse 원래형태로 변경
			AxmMotSetMoveUnitPerPulse(Motor_PCB_Y,1,1);
			return false;
		}
		Sleep(5);
		checkMessage();
	}
	if( bWait == true)	
	{
		AxmMotSetMoveUnitPerPulse(Motor_PCB_X, 1, 1);	//Unit/Pulse 원래형태로 변경(1:1 매칭으로)
		AxmMotSetMoveUnitPerPulse(Motor_PCB_Y, 1, 1);
	}

	return true;
}

bool CAxlMotorSet::checkPcbMotorPos(int index)
{
	double posX		= GetEncoderPos(Motor_PCB_X)  - model.axis[Motor_PCB_X].pos[index];
	double posY		= GetEncoderPos(Motor_PCB_Y)  - model.axis[Motor_PCB_Y].pos[index];
	double posTh	= GetCommandPos(Motor_PCB_TH) - model.axis[Motor_PCB_TH].pos[index];

	if (fabs(posX) < 0.1 && fabs(posY) < 0.1 && fabs(posTh) < 0.1)
	{
		return true;
	}
	else
	{
		return false;
	}
}



bool CAxlMotorSet::checkLensMotorPos(int index, int naxisNum)
{
	double posX = GetEncoderPos(Motor_Lens_X) - model.axis[Motor_Lens_X].pos[index];
	double posY = GetEncoderPos(Motor_Lens_Y) - model.axis[Motor_Lens_Y].pos[index];


	if (naxisNum == 2)
	{
		if (fabs(posX) < 0.1 && fabs(posY) < 0.1)
		{
			return true;
		}
	}
	else if (naxisNum == 1)
	{
		if (fabs(posX) < 0.1)
		{
			return true;
		}
	}
	else if (naxisNum == 0)
	{
		if (fabs(posY) < 0.1)
		{
			return true;
		}
	}

	return false;
}

bool CAxlMotorSet::checkInspMotorPos(int index)
{

	return false;
}
bool CAxlMotorSet::Dispense_Z_Motor_Move(int index, double dVel)
{
	double eTime;
	short axis[1];
	double pos[1];

	char logMsg[1000];


	if (!m_bOrgFlag[Motor_PCB_Z])
	{
		sLangChange.LoadStringA(IDS_STRING555);	//PCB 부 Z 모터가 원점 복귀를 하지 않았습니다.
		_stprintf_s(logMsg, sLangChange);
		errMsg2(Task.AutoFlag, logMsg);

		return false;
	}

	pos[0] = model.axis[Motor_PCB_Z].pos[index];
	axis[0] = Motor_PCB_Z;

	/*pos[0]	= model.axis[Motor_PCB_Z].pos[index];
	axis[0] = Motor_PCB_Z;*/

	sLangChange.LoadStringA(IDS_STRING991);	//"PCB 부 %s 모터 이동 합니다.
	_stprintf_s(logMsg, sLangChange, MotorPosName[Motor_PCB_Z]);


	int step = 0;

	double startTime;

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif

	while (1)
	{
		switch (step)
		{
		case 0:
			startTime = myTimer(true);
			DispenseGoMotorPos(1, axis, pos, dVel);
			step = 100;
			break;

		case 100:								// 이동 완료 확인..
			if (IsStopAxis(Motor_PCB_Z))
				step = 1000;
			break;

		default:
			break;
		}

		if (step == 1000)
			break;


		eTime = myTimer(true);
		if ((eTime - startTime)>MOTOR_MOVE_TIME)
		{
			if (step>100)
			{
				sLangChange.LoadStringA(IDS_STRING1479);	//PCB 부 [%s 모터] 이동 시간 초과
				_stprintf_s(logMsg, sLangChange, MotorPosName[Motor_PCB_Z]);
			}
			else
			{
				sLangChange.LoadStringA(IDS_STRING992);	//PCB 부 %s 이동 비정상
				_stprintf_s(logMsg, sLangChange, MotorPosName[Motor_PCB_Z]);
			}

			errMsg2(Task.AutoFlag, logMsg);

			return false;
		}

		checkMessage();
		Sleep(5);
	}

	return true;
}
bool CAxlMotorSet::PCB_Z_Motor_Move(int index, double offsetZ)
{
	double eTime;
	short axis[1];
	double pos[1];

	char logMsg[1000];

	
	if(!m_bOrgFlag[Motor_PCB_Z])
	{
		sLangChange.LoadStringA(IDS_STRING555);	//PCB 부 Z 모터가 원점 복귀를 하지 않았습니다.
		_stprintf_s(logMsg, sLangChange);
		errMsg2(Task.AutoFlag,logMsg);

		return false;
	}

	if(sysData.m_iProductComp == 1 && index == Bonding_Pos)//if(sysData.m_iProductComp == 1  && !(Task.dAAPcbMotor[0] == 0 && Task.dAAPcbMotor[1] == 0 && Task.dAAPcbMotor[2] == 0 && Task.dAAPcbMotor[3] == 0 && Task.dAAPcbMotor[4] == 0 && Task.dAAPcbMotor[5] == 0))
	{
#if (____AA_WAY == PCB_TILT_AA)
		pos[0] = Task.dAAPcbMotor[5];
		axis[0] = Motor_PCB_Z;
#elif (____AA_WAY == LENS_TILT_AA)
		pos[0] = model.axis[Motor_PCB_Z].pos[index];
		axis[0] = Motor_PCB_Z;
#endif
		
	}
	else
	{
		pos[0]	= model.axis[Motor_PCB_Z].pos[index] + offsetZ;
		axis[0] = Motor_PCB_Z;
	}
	
	/*pos[0]	= model.axis[Motor_PCB_Z].pos[index];
	axis[0] = Motor_PCB_Z;*/

	sLangChange.LoadStringA(IDS_STRING991);	//"PCB 부 %s 모터 이동 합니다.
	_stprintf_s(logMsg, sLangChange, MotorPosName[Motor_PCB_Z]);


	int step=0;
	
	double startTime;

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif

	while(1)
	{
		switch(step)
		{
		case 0:
			startTime = myTimer(true);
			goMotorPos(1, axis, pos);
			step = 100;
			break;

		case 100:								// 이동 완료 확인..
			if(IsStopAxis(Motor_PCB_Z))
				step = 1000;
			break;

		default:
			break;
		}

		if(step==1000)
			break;


		eTime = myTimer(true);
		if((eTime-startTime)>MOTOR_MOVE_TIME)
		{
			if(step>100)
			{
				sLangChange.LoadStringA(IDS_STRING1479);	//PCB 부 [%s 모터] 이동 시간 초과
				_stprintf_s(logMsg, sLangChange, MotorPosName[Motor_PCB_Z]);
			}
			else
			{
				sLangChange.LoadStringA(IDS_STRING992);	//PCB 부 %s 이동 비정상
				_stprintf_s(logMsg, sLangChange, MotorPosName[Motor_PCB_Z]);
			}

			errMsg2(Task.AutoFlag, logMsg);

			return false;
		}

		checkMessage();
		Sleep(5);
	}

	return true;
}

bool CAxlMotorSet::Pcb_Motor_Move_ComLaser(int Pos, double offsetX, double offsetY, double offsetTh)
{
	char logMsg[1000];
	double eTime = 0.0;
	short axis[3];
	double pos[3];
	int axis_cnt = 0;

	if (!m_bOrgFlag[Motor_PCB_X] || !m_bOrgFlag[Motor_PCB_Y] || !m_bOrgFlag[Motor_PCB_TH])
	{
		sLangChange.LoadStringA(IDS_STRING1001);	//PCB 부 모터가 원점 복귀를 하지 않았습니다.
		_stprintf_s(logMsg, sLangChange);
		errMsg2(Task.AutoFlag, logMsg);
		return false;
	}

	double MotorPos[3];
	MotorPos[0] = fabs(GetEncoderPos(Motor_Lens_X) - model.axis[Motor_Lens_X].pos[Bonding_Pos]);
	MotorPos[1] = fabs(GetEncoderPos(Motor_Lens_Y) - model.axis[Motor_Lens_Y].pos[Bonding_Pos]);
	MotorPos[2] = fabs(GetEncoderPos(Motor_Lens_Z) - model.axis[Motor_Lens_Z].pos[Wait_Pos]);

	// Lens가 X,Y 본딩 위치일 경우 , Lens Z 축 확인 
	if (MotorPos[0] < model.axis[Motor_Lens_X].m_dLimit_Err && MotorPos[1] < model.axis[Motor_Lens_Y].m_dLimit_Err)
	{
		if (MotorPos[2] > 1)		// PCB가 본딩 위치로 이동 할때 Lens Z축 대기 위치 확인
		{
			//sLangChange.LoadStringA(IDS_STRING719);	//Lens 모터가 본딩 위치에 있습니다.
			//_stprintf_s(logMsg, sLangChange);
			errMsg2(Task.AutoFlag, "Lens Z축 대기가 아닙니다.");
			return false;
		}


	}


	double zPos = 0;


	if (fabs(offsetX)>model.axis[Motor_PCB_X].m_dLimit_Err)
	{
		sLangChange.LoadStringA(IDS_STRING997);	//PCB 부 X 축 보정값 허용 범위[± %.01f]를 초과 하였습니다
		_stprintf_s(logMsg, sLangChange, model.axis[Motor_PCB_X].m_dLimit_Err, offsetX);
		errMsg2(Task.AutoFlag, logMsg);

		return false;
	}

	if (fabs(offsetY)>model.axis[Motor_PCB_Y].m_dLimit_Err)
	{
		sLangChange.LoadStringA(IDS_STRING998);	//PCB 부 Y 축 보정값 허용 범위[± %.01f]를 초과 하였습니다.
		_stprintf_s(logMsg, sLangChange, model.axis[Motor_PCB_Y].m_dLimit_Err, offsetY);
		errMsg2(Task.AutoFlag, logMsg);

		return false;
	}

	if (fabs(offsetTh)>model.axis[Motor_PCB_TH].m_dLimit_Err)
	{
		sLangChange.LoadStringA(IDS_STRING999);	//PCB 부 Θ축 보정값 허용 범위[± %.01f]를 초과 하였습니다
		_stprintf_s(logMsg, sLangChange, model.axis[Motor_PCB_TH].m_dLimit_Err, offsetTh);
		errMsg2(Task.AutoFlag, logMsg);

		return false;
	}


	axis[0] = Motor_PCB_X;
	axis[1] = Motor_PCB_Y;
	axis[2] = Motor_PCB_TH;


	int pMotorPos = -1;
	pMotorPos = Com_Laser_Pos;
	if (Pos == 0)
	{
		pos[0] = model.axis[Motor_PCB_X].pos[pMotorPos] + offsetX;
		pos[1] = model.axis[Motor_PCB_Y].pos[pMotorPos] + offsetY;
		pos[2] = model.axis[Motor_PCB_TH].pos[pMotorPos] + offsetTh;
	}
	else if (Pos == 1)
	{
		pos[0] = model.axis[Motor_PCB_X].pos[pMotorPos] + offsetX - model.m_OutPos_X[0];
		pos[1] = model.axis[Motor_PCB_Y].pos[pMotorPos] + offsetY - model.m_OutPos_Y[0];

		pos[2] = model.axis[Motor_PCB_TH].pos[pMotorPos] + offsetTh;
	}
	else if (Pos == 2)
	{
		pos[0] = model.axis[Motor_PCB_X].pos[pMotorPos] + offsetX - model.m_OutPos_X[1];
		pos[1] = model.axis[Motor_PCB_Y].pos[pMotorPos] + offsetY - model.m_OutPos_Y[1];

		pos[2] = model.axis[Motor_PCB_TH].pos[pMotorPos] + offsetTh;
	}
	else if (Pos == 3)
	{
		pos[0] = model.axis[Motor_PCB_X].pos[pMotorPos] + offsetX - model.m_OutPos_X[2];
		pos[1] = model.axis[Motor_PCB_Y].pos[pMotorPos] + offsetY - model.m_OutPos_Y[2];

		pos[2] = model.axis[Motor_PCB_TH].pos[pMotorPos] + offsetTh;
	}

	_stprintf_s(logMsg, "PCB 부 %s로 이동 합니다.", MotorPosName[pMotorPos]);


	int step = 0;

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif

	double startTime;


	while (1)
	{
		switch (step)
		{
		case 0:									// 3축 모터 대기 위치로 이동 명령..
			startTime = myTimer(true);
			goMotorPos(3, axis, pos);
			step = 100;
			break;

		case 100:								// 이동 완료 확인..
			if ((IsStopAxis(Motor_PCB_X) && GetInposition(Motor_PCB_X)) &&
				(IsStopAxis(Motor_PCB_Y) && GetInposition(Motor_PCB_Y)) &&
				(IsStopAxis(Motor_PCB_TH)))
			{
				step = 101;
			}

			break;

		case 101:
			if ((IsStopAxis(Motor_PCB_X) && GetInposition(Motor_PCB_X)) &&
				(IsStopAxis(Motor_PCB_Y) && GetInposition(Motor_PCB_Y)))
				step = 102;
			break;

		case 102:
			if (IsStopAxis(Motor_PCB_TH))
				step = 1000;
			break;

		default:
			break;
		}

		if (step == 1000)
			break;


		eTime = myTimer(true);
		if (eTime - startTime > MOTOR_MOVE_TIME)
		{
			StopAxis(Motor_PCB_X);
			StopAxis(Motor_PCB_Y);
			StopAxis(Motor_PCB_TH);

			if (step>100)
			{
				int motorNo = step - 100;
				sprintf_s(logMsg, "PCB 부 [%s 모터] %s 이동 시간 초과", MotorName[motorNo], MotorPosName[pMotorPos]);
			}
			else
			{
				_stprintf_s(logMsg, "PCB 부 %s 이동 비정상", MotorPosName[pMotorPos]);
			}

			errMsg2(Task.AutoFlag, logMsg);

			return false;
		}

		Sleep(5);
		checkMessage();
	}
	//#endif
	return true;
}



bool CAxlMotorSet::Pcb_Motor_Move_Laser(int Pos, double offsetX, double offsetY, double offsetTh)
{
//#if 0
	char logMsg[1000];
	double eTime = 0.0;
	short axis[3];
	double pos[3];
	int axis_cnt =0;

	if(!m_bOrgFlag[Motor_PCB_X] || !m_bOrgFlag[Motor_PCB_Y] || !m_bOrgFlag[Motor_PCB_TH])
	{
		sLangChange.LoadStringA(IDS_STRING1001);	//PCB 부 모터가 원점 복귀를 하지 않았습니다.
		_stprintf_s(logMsg, sLangChange);
		errMsg2(Task.AutoFlag,logMsg);
		return false;
	}

	double MotorPos[3];
	MotorPos[0] = fabs(GetEncoderPos(Motor_Lens_X) - model.axis[Motor_Lens_X].pos[Bonding_Pos]);
	MotorPos[1] = fabs(GetEncoderPos(Motor_Lens_Y) - model.axis[Motor_Lens_Y].pos[Bonding_Pos]);
	MotorPos[2] = fabs(GetCommandPos(Motor_Lens_Z) - model.axis[Motor_Lens_Z].pos[Wait_Pos]);

	// Lens가 X,Y 본딩 위치일 경우 , Lens Z 축 확인 
	if(MotorPos[0] < model.axis[Motor_Lens_X].m_dLimit_Err && MotorPos[1] < model.axis[Motor_Lens_Y].m_dLimit_Err)
	{
		if (MotorPos[2] > 1)		// PCB가 본딩 위치로 이동 할때 Lens Z축 대기 위치 확인
		{
			//sLangChange.LoadStringA(IDS_STRING719);	//Lens 모터가 본딩 위치에 있습니다.
			//_stprintf_s(logMsg, sLangChange);
			errMsg2(Task.AutoFlag, "Lens Z축 대기가 아닙니다.");
			return false;
		}


	}


	double zPos = 0;
	

	if(fabs(offsetX)>model.axis[Motor_PCB_X].m_dLimit_Err)
	{
		sLangChange.LoadStringA(IDS_STRING997);	//PCB 부 X 축 보정값 허용 범위[± %.01f]를 초과 하였습니다
		_stprintf_s(logMsg, sLangChange, model.axis[Motor_PCB_X].m_dLimit_Err, offsetX);
		errMsg2(Task.AutoFlag,logMsg);

		return false;
	}

	if(fabs(offsetY)>model.axis[Motor_PCB_Y].m_dLimit_Err)
	{
		sLangChange.LoadStringA(IDS_STRING998);	//PCB 부 Y 축 보정값 허용 범위[± %.01f]를 초과 하였습니다.
		_stprintf_s(logMsg, sLangChange, model.axis[Motor_PCB_Y].m_dLimit_Err, offsetY);
		errMsg2(Task.AutoFlag, logMsg);

		return false;
	}

	if(fabs(offsetTh)>model.axis[Motor_PCB_TH].m_dLimit_Err)
	{
		sLangChange.LoadStringA(IDS_STRING999);	//PCB 부 Θ축 보정값 허용 범위[± %.01f]를 초과 하였습니다
		_stprintf_s(logMsg, sLangChange, model.axis[Motor_PCB_TH].m_dLimit_Err, offsetTh);
		errMsg2(Task.AutoFlag, logMsg);

		return false;
	}


	axis[0] = Motor_PCB_X;
	axis[1] = Motor_PCB_Y;
	axis[2] = Motor_PCB_TH;
	int pMotorPos = -1;

	if (sysData.m_iProductComp == 1)
	{
		pMotorPos = Com_Laser_Pos;

	}
	else
	{
		pMotorPos = Laser_Pcb_Pos;
	}
	if( Pos == 0)
	{
		pos[0]	= model.axis[Motor_PCB_X].pos[pMotorPos] + offsetX;
		pos[1]	= model.axis[Motor_PCB_Y].pos[pMotorPos] + offsetY;
		pos[2]	= model.axis[Motor_PCB_TH].pos[pMotorPos] + offsetTh;
	}
	else if( Pos == 1)
	{
		if (sysData.m_iProductComp == 1)
		{
			pos[0] = model.axis[Motor_PCB_X].pos[pMotorPos] + offsetX - model.m_OutPos_X[0];
			pos[1] = model.axis[Motor_PCB_Y].pos[pMotorPos] + offsetY - model.m_OutPos_Y[0];
		}
		else
		{
			pos[0] = model.axis[Motor_PCB_X].pos[pMotorPos] + offsetX - model.m_PcbLaserPos_X[0];
			pos[1] = model.axis[Motor_PCB_Y].pos[pMotorPos] + offsetY - model.m_PcbLaserPos_Y[0];
		}
		
		pos[2]	= model.axis[Motor_PCB_TH].pos[pMotorPos] + offsetTh;
	}
	else if( Pos == 2)
	{
		if (sysData.m_iProductComp == 1)
		{
			pos[0] = model.axis[Motor_PCB_X].pos[pMotorPos] + offsetX - model.m_OutPos_X[1];
			pos[1] = model.axis[Motor_PCB_Y].pos[pMotorPos] + offsetY - model.m_OutPos_Y[1];
		}
		else
		{
			pos[0] = model.axis[Motor_PCB_X].pos[pMotorPos] + offsetX - model.m_PcbLaserPos_X[1];
			pos[1] = model.axis[Motor_PCB_Y].pos[pMotorPos] + offsetY - model.m_PcbLaserPos_Y[1];
		}
		
		pos[2]	= model.axis[Motor_PCB_TH].pos[pMotorPos] + offsetTh;
	}
	else if( Pos == 3)
	{
		if (sysData.m_iProductComp == 1)
		{
			pos[0] = model.axis[Motor_PCB_X].pos[pMotorPos] + offsetX - model.m_OutPos_X[2];
			pos[1] = model.axis[Motor_PCB_Y].pos[pMotorPos] + offsetY - model.m_OutPos_Y[2];
		}
		else
		{
			pos[0] = model.axis[Motor_PCB_X].pos[pMotorPos] + offsetX - model.m_PcbLaserPos_X[2];
			pos[1] = model.axis[Motor_PCB_Y].pos[pMotorPos] + offsetY - model.m_PcbLaserPos_Y[2];
		}
		
		pos[2]	= model.axis[Motor_PCB_TH].pos[pMotorPos] + offsetTh;
	}
	
	_stprintf_s(logMsg, "PCB 부 %s로 이동 합니다.", MotorPosName[pMotorPos]);


	int step=0;

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif

	double startTime = 0.0;

	Task.bMotorRunStop = true;
	while(1)
	{
		if (Task.bMotorRunStop == false)	//Pcb_Motor_Move_Laser
		{
			StopAxis(Motor_PCB_X);
			StopAxis(Motor_PCB_Y);
			StopAxis(Motor_PCB_TH);
			return false;
		}
		switch(step)
		{
		case 0:									// 3축 모터 대기 위치로 이동 명령..
			startTime = myTimer(true);
			goMotorPos(3, axis, pos);
			step = 100;
			break;

		case 100:								// 이동 완료 확인..
			if( ( IsStopAxis(Motor_PCB_X) && GetInposition(Motor_PCB_X) ) && 
				( IsStopAxis(Motor_PCB_Y) && GetInposition(Motor_PCB_Y) ) && 
				( IsStopAxis(Motor_PCB_TH) && GetInposition(Motor_PCB_TH) ) )
			{
				step = 101;
			}

			break;

		case 101:
			if( ( IsStopAxis(Motor_PCB_X) && GetInposition(Motor_PCB_X) ) && 
			    ( IsStopAxis(Motor_PCB_Y) && GetInposition(Motor_PCB_Y) ) )
				step = 102;
			break;

		case 102:
			if( IsStopAxis(Motor_PCB_TH) && GetInposition(Motor_PCB_TH) )
				step = 1000;
			break;

		default:
			break;
		}

		if(step==1000)
			break;


		eTime = myTimer(true);
		if(eTime-startTime > MOTOR_MOVE_TIME)
		{
			StopAxis(Motor_PCB_X);
			StopAxis(Motor_PCB_Y);
			StopAxis(Motor_PCB_TH);

			if(step>100)
			{
				int motorNo = step - 100;
				sprintf_s(logMsg, "PCB 부 [%s 모터] %s 이동 시간 초과", MotorName[motorNo], MotorPosName[pMotorPos]);
			}
			else
			{
				_stprintf_s(logMsg, "PCB 부 %s 이동 비정상", MotorPosName[pMotorPos]);
			}

			errMsg2(Task.AutoFlag,logMsg);

			return false;
		}

		Sleep(5);
	}
//#endif
	return true;
}


bool CAxlMotorSet::Lens_Motor_Move_Laser(int Pos, double offsetX, double offsetY, double offsetTh)
{
	char logMsg[1000];
	double eTime;
	short axis[2];
	double pos[2];
	int axis_cnt =0;

	if(!m_bOrgFlag[Motor_PCB_X] || !m_bOrgFlag[Motor_PCB_Y] || !m_bOrgFlag[Motor_PCB_TH])
	{
		sLangChange.LoadStringA(IDS_STRING1001);	//PCB 부 모터가 원점 복귀를 하지 않았습니다.
		_stprintf_s(logMsg, sLangChange);
		errMsg2(Task.AutoFlag,logMsg);
		return false;
	}

	double MotorPos[3];
	MotorPos[0] = fabs(GetEncoderPos(Motor_Lens_X) - model.axis[Motor_Lens_X].pos[Bonding_Pos]);
	MotorPos[1] = fabs(GetEncoderPos(Motor_Lens_Y) - model.axis[Motor_Lens_Y].pos[Bonding_Pos]);
	//MotorPos[2] = fabs(GetEncoderPos(Motor_Lens_Z) - model.axis[Motor_Lens_Z].pos[Wait_Pos]);

	// Lens가 X,Y 본딩 위치일 경우 , Lens Z 축 확인 
	if(MotorPos[0] < model.axis[Motor_Lens_X].m_dLimit_Err && MotorPos[1] < model.axis[Motor_Lens_Y].m_dLimit_Err)
	{
		if (Dio.PCBCoverCloseCheck(true, false) == false)
		{
			sLangChange.LoadStringA(IDS_STRING1026);	//PCB부 커버 소켓이 열려 있습니다.
			_stprintf_s(logMsg, sLangChange);
			errMsg2(Task.AutoFlag, logMsg);
			return false;
		}

		if(MotorPos[2] > 1)		// PCB가 본딩 위치로 이동 할때 Lens Z축 대기 위치 확인
		{
			sLangChange.LoadStringA(IDS_STRING719);	//Lens 모터가 본딩 위치에 있습니다.
			_stprintf_s(logMsg, sLangChange);
			errMsg2(Task.AutoFlag,logMsg);
			return false;
		}
	}


	double zPos = 0;
	

	if(fabs(offsetX)>model.axis[Motor_Lens_X].m_dLimit_Err)
	{
		sLangChange.LoadStringA(IDS_STRING997);	//PCB 부 X 축 보정값 허용 범위[± %.01f]를 초과 하였습니다
		_stprintf_s(logMsg, sLangChange, model.axis[Motor_PCB_X].m_dLimit_Err, offsetX);
		errMsg2(Task.AutoFlag,logMsg);

		return false;
	}

	if(fabs(offsetY)>model.axis[Motor_Lens_Y].m_dLimit_Err)
	{
		sLangChange.LoadStringA(IDS_STRING998);	//PCB 부 Y 축 보정값 허용 범위[± %.01f]를 초과 하였습니다.
		_stprintf_s(logMsg, sLangChange, model.axis[Motor_PCB_Y].m_dLimit_Err, offsetY);
		errMsg2(Task.AutoFlag, logMsg);

		return false;
	}


	axis[0] = Motor_Lens_X;
	axis[1] = Motor_Lens_Y;
	//axis[2] = Motor_Lens_TH;
	if(fabs(model.m_OutPos_X[0])>55||model.m_OutPos_X[1]>55||model.m_OutPos_Y[0]>55||model.m_OutPos_Y[1]>55){return false;}
	if( Pos == 0)
	{
		pos[0]	= model.axis[Motor_Lens_X].pos[Laser_Lens_Pos] + offsetX;
		pos[1]	= model.axis[Motor_Lens_Y].pos[Laser_Lens_Pos] + offsetY;
	}
	else if( Pos == 1)
	{
		pos[0]	= model.axis[Motor_Lens_X].pos[Laser_Lens_Pos] + offsetX - model.m_OutPos_X[0];
		pos[1]	= model.axis[Motor_Lens_Y].pos[Laser_Lens_Pos] + offsetY - model.m_OutPos_Y[0];
	}
	else if( Pos == 2)
	{
		pos[0]	= model.axis[Motor_Lens_X].pos[Laser_Lens_Pos] + offsetX - model.m_OutPos_X[1];
		pos[1]	= model.axis[Motor_Lens_Y].pos[Laser_Lens_Pos] + offsetY - model.m_OutPos_Y[1];
	}
	else if( Pos == 3)
	{
		pos[0]	= model.axis[Motor_Lens_X].pos[Laser_Lens_Pos] + offsetX - model.m_OutPos_X[2];
		pos[1]	= model.axis[Motor_Lens_Y].pos[Laser_Lens_Pos] + offsetY - model.m_OutPos_Y[2];
	}
	_stprintf_s(logMsg, "Lens 부 %s로 이동 합니다.", MotorPosName[Laser_Lens_Pos]);
		//delayMsg(logMsg, 10000, M_COLOR_BLUE);


	int step=0;

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif

	double startTime;


	while(1)
	{
		switch(step)
		{
		case 0:									// 3축 모터 대기 위치로 이동 명령..
			startTime = myTimer(true);
			goMotorPos(2, axis, pos);
			step = 100;
			break;

		case 100:								// 이동 완료 확인..
			if( ( IsStopAxis(Motor_Lens_X) && GetInposition(Motor_Lens_X) ) && 
				( IsStopAxis(Motor_Lens_Y) && GetInposition(Motor_Lens_Y) ) )
			{
				step = 101;
			}

			break;

		case 101:
			if( ( IsStopAxis(Motor_Lens_X) && GetInposition(Motor_Lens_X) ) && 
			    ( IsStopAxis(Motor_Lens_Y) && GetInposition(Motor_Lens_Y) ) )
				step = 102;
			break;

		case 102:
				step = 1000;
			break;

		default:
			break;
		}

		if(step==1000)
			break;


		eTime = myTimer(true);
		if(eTime-startTime > MOTOR_MOVE_TIME)
		{
			StopAxis(Motor_Lens_X);
			StopAxis(Motor_Lens_Y);
			if(step>100)
			{
				int motorNo = step - 100;
				sprintf_s(logMsg, "Lens 부 [%s 모터] %s 이동 시간 초과", MotorName[motorNo], MotorPosName[Laser_Lens_Pos]);
			}
			else
			{
				_stprintf_s(logMsg, "Lens 부 %s 이동 비정상", MotorPosName[Laser_Lens_Pos]);
				
			}

			errMsg2(Task.AutoFlag,logMsg);

			return false;
		}

		Sleep(5);
	}
	return true;
}

bool CAxlMotorSet::Pcb_Move_Tilt(double offsetX, double offsetY)
{
	char logMsg[1000];
	double eTime;
	short axis[3];
	double pos[3];
	int axis_cnt =0;

	if(!m_bOrgFlag[Motor_PCB_Xt] || !m_bOrgFlag[Motor_PCB_Yt])
	{
		sLangChange.LoadStringA(IDS_STRING1001);	//PCB 부 모터가 원점 복귀를 하지 않았습니다.
		_stprintf_s(logMsg, sLangChange);
		errMsg2(Task.AutoFlag,logMsg);
		return false;
	}

	if(fabs(offsetX)>model.axis[Motor_PCB_Xt].m_dLimit_Err)
	{
		sLangChange.LoadStringA(IDS_STRING997);	//PCB 부 X 축 보정값 허용 범위[± %.01f]를 초과 하였습니다
		_stprintf_s(logMsg, sLangChange, model.axis[Motor_PCB_X].m_dLimit_Err, offsetX);
		errMsg2(Task.AutoFlag,logMsg);

		return false;
	}

	if(fabs(offsetY)>model.axis[Motor_PCB_Yt].m_dLimit_Err)
	{
		sLangChange.LoadStringA(IDS_STRING998);	//PCB 부 Y 축 보정값 허용 범위[± %.01f]를 초과 하였습니다.
		_stprintf_s(logMsg, sLangChange, model.axis[Motor_PCB_Y].m_dLimit_Err, offsetY);
		errMsg2(Task.AutoFlag, logMsg);

		return false;
	}

	axis[0] = Motor_PCB_Xt;
	axis[1] = Motor_PCB_Yt;

	if (sysData.m_iProductComp == 1 && Task.AutoFlag != 1)		//완제품 모드이고, 수동 레이저 일때는 보정돼야된다.
	{
		pos[0] = offsetX;
		pos[1] = offsetY;
	}
	else
	{
		pos[0] = GetEncoderPos(Motor_PCB_Xt) + offsetX;
		pos[1] = GetEncoderPos(Motor_PCB_Yt) + offsetY;
	}

	int step=0;

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif

	double startTime;


	while(1)
	{
		switch(step)
		{
		case 0:									// 3축 모터 대기 위치로 이동 명령..
			startTime = myTimer(true);

			goMotorPos(2, axis, pos);

			step = 100;
			break;

		case 100:								// 이동 완료 확인..
			if( ( IsStopAxis(Motor_PCB_Xt) /*&& GetInposition(Motor_PCB_Xt)*/ ) && 
				( IsStopAxis(Motor_PCB_Yt) /*&& GetInposition(Motor_PCB_Yt)*/ ) )
			{
				step = 1000;
			}

			break;

		default:
			break;
		}

		if(step==1000)
			break;


		eTime = myTimer(true);
		if(eTime-startTime > MOTOR_MOVE_TIME)
		{
			StopAxis(Motor_PCB_Xt);
			StopAxis(Motor_PCB_Yt);

			if(step>100)
			{
				int motorNo = step - 100;
				sLangChange.LoadStringA(IDS_STRING1482);	//PCB 부 [%s 모터] 이동 시간 초과
				_stprintf_s(logMsg, sLangChange, MotorName[motorNo]);
			}
			else
			{
				sLangChange.LoadStringA(IDS_STRING1483);	//PCB 부 이동 비정상
				_stprintf_s(logMsg, sLangChange);
			}

			errMsg2(Task.AutoFlag,logMsg);

			return false;
		}

		Sleep(5);
	}
	
	return true;
}

bool CAxlMotorSet::Lens_Move_Tilt(double offsetX, double offsetY)
{
	char logMsg[1000];
	double eTime;
	short axis[3];
	double pos[3];
	int axis_cnt =0;

	if(!m_bOrgFlag[Motor_Lens_Xt] || !m_bOrgFlag[Motor_Lens_Yt])
	{
		sLangChange.LoadStringA(IDS_STRING1001);	//PCB 부 모터가 원점 복귀를 하지 않았습니다.
		_stprintf_s(logMsg, sLangChange);
		errMsg2(Task.AutoFlag,logMsg);
		return false;
	}

	if(fabs(offsetX)>model.axis[Motor_Lens_Xt].m_dLimit_Err)
	{
		sLangChange.LoadStringA(IDS_STRING997);	//PCB 부 X 축 보정값 허용 범위[± %.01f]를 초과 하였습니다
		_stprintf_s(logMsg, _T("Lens TX-Axis Limit") );// model.axis[Motor_Lens_Xt].m_dLimit_Err, offsetX);
		errMsg2(Task.AutoFlag,logMsg);

		return false;
	}

	if(fabs(offsetY)>model.axis[Motor_Lens_Yt].m_dLimit_Err)
	{
		sLangChange.LoadStringA(IDS_STRING998);	//PCB 부 Y 축 보정값 허용 범위[± %.01f]를 초과 하였습니다.
		_stprintf_s(logMsg, _T("Lens TY-Axis Limit"));// , model.axis[Motor_Lens_Y].m_dLimit_Err, offsetY);
		errMsg2(Task.AutoFlag, logMsg);

		return false;
	}

	axis[0] = Motor_Lens_Xt;
	axis[1] = Motor_Lens_Yt;

	pos[0] = GetCommandPos(Motor_Lens_Xt) + offsetX;
	pos[1]	= GetEncoderPos(Motor_Lens_Yt) - offsetY;

	int step=0;

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif

	double startTime;


	while(1)
	{
		switch(step)
		{
		case 0:									// 3축 모터 대기 위치로 이동 명령..
			startTime = myTimer(true);

			goMotorPos(2, axis, pos);

			step = 100;
			break;

		case 100:								// 이동 완료 확인..
			if( ( IsStopAxis(Motor_Lens_Xt) /*&& GetInposition(Motor_PCB_Xt)*/ ) && 
				( IsStopAxis(Motor_Lens_Yt) /*&& GetInposition(Motor_PCB_Yt)*/ ) )
			{
				step = 1000;
			}

			break;

		default:
			break;
		}

		if(step==1000)
			break;


		eTime = myTimer(true);
		if(eTime-startTime > MOTOR_MOVE_TIME)
		{
			StopAxis(Motor_Lens_Xt);
			StopAxis(Motor_Lens_Yt);

			if(step>100)
			{
				int motorNo = step - 100;
				sLangChange.LoadStringA(IDS_STRING1482);	//PCB 부 [%s 모터] 이동 시간 초과
				_stprintf_s(logMsg, sLangChange, MotorName[motorNo]);
			}
			else
			{
				sLangChange.LoadStringA(IDS_STRING1483);	//PCB 부 이동 비정상
				_stprintf_s(logMsg, sLangChange);
			}

			errMsg2(Task.AutoFlag,logMsg);

			return false;
		}

		Sleep(5);
		checkMessage();
	}
	
	return true;
}

bool CAxlMotorSet::Pcb_Holder_Align_Move(int index, double offsetX, double offsetY, double offsetTh)
{
	char logMsg[1000];
	double eTime;
	short axis[3];
	double pos[3];
	int axis_cnt = 0;
	double dOffsetLimit = 1.0;


	for (int i = Motor_PCB_X; i <= Motor_PCB_TH; i++)
	{
		if (!m_bOrgFlag[i])
		{
			sLangChange.LoadStringA(IDS_STRING1001);	//PCB 부 모터가 원점 복귀를 하지 않았습니다.
			_stprintf_s(logMsg, _T("%s ") + sLangChange, MotorName[i]);
			errMsg2(Task.AutoFlag, logMsg);
			return false;
		}

		axis[i - Motor_PCB_X] = i;

		if (i == Motor_PCB_X)				pos[i - Motor_PCB_X] = model.axis[i].pos[index] + offsetX;
		else if (i == Motor_PCB_Y)		pos[i - Motor_PCB_X] = model.axis[i].pos[index] + offsetY;
		else if (i == Motor_PCB_TH)		pos[i - Motor_PCB_X] = model.axis[i].pos[index] + offsetTh;
	}

	double MotorPos[2];
	MotorPos[0] = GetEncoderPos(Motor_PCB_X) - model.axis[Motor_PCB_X].pos[index];
	MotorPos[1] = GetEncoderPos(Motor_PCB_Y) - model.axis[Motor_PCB_Y].pos[index];

	if (fabs(MotorPos[0]) > model.axis[Motor_PCB_X].m_dLimit_Err)
	{
		sLangChange.LoadStringA(IDS_STRING970);	//PCB X 모터가 Align 보정 Limit를 벗어 났습니다. [Encoder %.03lf, Teaching %.03lf]
		_stprintf_s(logMsg, sLangChange, GetEncoderPos(Motor_PCB_X), model.axis[Motor_PCB_X].pos[Align_Pos]);
		errMsg2(Task.AutoFlag, logMsg);
		return false;
	}

	if (fabs(MotorPos[1]) > model.axis[Motor_PCB_Y].m_dLimit_Err)
	{
		sLangChange.LoadStringA(IDS_STRING973);	//PCB Y 모터가 Align 보정 Limit를 벗어 났습니다. [Encoder %.03lf, Teaching %.03lf]
		_stprintf_s(logMsg, sLangChange, GetEncoderPos(Motor_PCB_Y), model.axis[Motor_PCB_Y].pos[Align_Pos]);
		errMsg2(Task.AutoFlag, logMsg);
		return false;
	}
	//20170215 holder 부분 th모터 추가
	if (fabs(MotorPos[1]) > model.axis[Motor_PCB_TH].m_dLimit_Err)//
	{
		sLangChange.LoadStringA(IDS_STRING973);	//PCB Y 모터가 Align 보정 Limit를 벗어 났습니다. [Encoder %.03lf, Teaching %.03lf]
		_stprintf_s(logMsg, "PCB TH 모터가 Align 보정 Limit를 벗어 났습니다. [Encoder %.03lf, Teaching %.03lf]", GetEncoderPos(Motor_PCB_TH), model.axis[Motor_PCB_TH].pos[Align_Pos]);
		errMsg2(Task.AutoFlag, logMsg);
		return false;
	}

	int step = 0;

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif


	double startTime;

	while (1)
	{
		switch (step)
		{
		case 0:									// 3축 모터 대기 위치로 이동 명령..
			startTime = myTimer(true);
			goMotorPos(3, axis, pos);
			step = 100;
			break;

		case 100:								// 이동 완료 확인..
			if (IsStopAxis(Motor_PCB_X) && GetInposition(Motor_PCB_X))			step = 101;
			break;

		case 101:
			if (IsStopAxis(Motor_PCB_Y) && GetInposition(Motor_PCB_Y))		step = 102;
			break;

		case 102:
			if (IsStopAxis(Motor_PCB_TH) && GetInposition(Motor_PCB_TH))		step = 1000;
			break;

		default:
			break;
		}

		if (step == 1000)
			break;


		eTime = myTimer(true);
		if (eTime - startTime > MOTOR_MOVE_TIME)
		{
			StopAxis(Motor_PCB_X);
			StopAxis(Motor_PCB_Y);
			StopAxis(Motor_PCB_TH);

			if (step>100)
			{
				int motorNo = step - 100;
				sLangChange.LoadStringA(IDS_STRING1482);	//PCB 부 [%s 모터] 이동 시간 초과
				_stprintf_s(logMsg, sLangChange, MotorName[motorNo]);
			}
			else
			{
				sLangChange.LoadStringA(IDS_STRING994);	//PCB 부 Align 보정 이동 시간 초과
				_stprintf_s(logMsg, sLangChange);
			}

			errMsg2(Task.AutoFlag, logMsg);

			return false;
		}

		Sleep(5);
		checkMessage();
	}


#ifdef ON_LINE_MOTOR
	for (int i = Motor_PCB_X; i <= Motor_PCB_TH; i++)
	{
		double curPos = GetEncoderPos(axis[i - Motor_PCB_X]);
		double cmdPos = GetCommandPos(axis[i - Motor_PCB_X]);

		double errVal = fabs(pos[i - Motor_PCB_X] - curPos);

		if (errVal>IN_POSITION_VAL)
		{
			sLangChange.LoadStringA(IDS_STRING995);	//PCB 부 Align 보정 이동 후 %s 모터 위치 오차 발생
			_stprintf_s(logMsg, sLangChange, MotorName[i], pos[i], curPos, cmdPos);
			LogSave(logMsg);

			checkMessage();


			for (int j = 0; j<10; j++)
			{
				Sleep(5);
				checkMessage();
			}


			curPos = GetEncoderPos(axis[i - Motor_PCB_X]);
			cmdPos = GetCommandPos(axis[i - Motor_PCB_X]);

			errVal = fabs(pos[i - Motor_PCB_X] - curPos);

			if (errVal>IN_POSITION_VAL)
			{
				sLangChange.LoadStringA(IDS_STRING995);	//PCB 부 Align 보정 이동 후 %s 모터 위치 오차 발생
				_stprintf_s(logMsg, sLangChange, MotorName[i], pos[i], curPos, cmdPos);
				errMsg2(Task.AutoFlag, logMsg);

				return false;
			}

			return false;
		}
	}
#endif

	return true;
}

bool CAxlMotorSet::moveEpoxyCleanPos(int iIndex, bool waitFlag)
{
	char logMsg[1000];
	double eTime;
	short axis[4] = {Motor_PCB_X, Motor_PCB_Y, Motor_PCB_TH};
	double pos[4];
	int iIndex_X, iIndex_Y;
	int iCntX, iCntY;

	if(!m_bOrgFlag[Motor_PCB_X] || !m_bOrgFlag[Motor_PCB_Y] || !m_bOrgFlag[Motor_PCB_TH])
	{
		sLangChange.LoadStringA(IDS_STRING1001);	//PCB 부 모터가 원점 복귀를 하지 않았습니다.
		_stprintf_s(logMsg, sLangChange);
		errMsg2(Task.AutoFlag,logMsg);
		return false;
	}
	if ( (motor.IsStopAxis(Motor_PCB_X) == false)		||
		(motor.IsStopAxis(Motor_PCB_Y) == false)		)
	{
		sLangChange.LoadStringA(IDS_STRING551);	//Epoxy부 X, Y 축 모터가 동작 중입니다.
		_stprintf_s(logMsg, sLangChange);
		errMsg2(Task.AutoFlag, logMsg);
		return false;
	}


	if(!PCB_Z_Motor_Move(Wait_Pos))
		return false;


	iCntX = (int)(model.Cleanpad[0]);
	iCntY = (int)(model.Cleanpad[1]);

	if(iCntX == 0 && iCntY == 0)
	{
		sLangChange.LoadStringA(IDS_STRING466);
		_stprintf_s(logMsg, sLangChange);	//clean pad 크기가 0 입니다!!
		errMsg2(Task.AutoFlag, logMsg);
		return false;
	}
	if (iIndex >= iCntX*iCntY)
	{
		model.Cleancnt = 0;
		iIndex = 0;
	}

	iIndex_X = iIndex % iCntX;
	iIndex_Y = iIndex / iCntX;

	pos[0] = model.axis[Motor_PCB_X].pos[Clean_Pos] - iIndex_X;
	pos[1] = model.axis[Motor_PCB_Y].pos[Clean_Pos] + iIndex_Y;
	pos[2] = model.axis[Motor_PCB_TH].pos[Clean_Pos];

	goMotorPos(3, axis, pos);

	int step=100;

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif

	eTime = myTimer(true);
	while (waitFlag)
	{
		switch(step)
		{
		case 100:		
			if(motor.IsStopAxis(Motor_PCB_X))
				step = 200;
			break;
		case 200:
			if(motor.IsStopAxis(Motor_PCB_Y))
				step = 300;
			break;
		case 300:
			if(motor.IsStopAxis(Motor_PCB_TH))
				step = 1000;
			break;
		default:
			break;
		}

		if(step==1000)
			break;


		if(myTimer(true) - eTime>MOTOR_MOVE_TIME)
		{
			motor.StopAxis(Motor_PCB_X);
			motor.StopAxis(Motor_PCB_Y);
			motor.StopAxis(Motor_PCB_TH);

			sLangChange.LoadStringA(IDS_STRING550);
			_stprintf_s(logMsg, sLangChange);	//"Epoxy부 X, Y 축 Clean 위치 이동 실패"
			errMsg2(Task.AutoFlag,logMsg);

			return false;
		}

		Sleep(5);
		checkMessage();
	}

	return true;
}

bool CAxlMotorSet::Pcb_Tilt_Align_Move(double offsetX, double offsetY)
{
	char logMsg[1000];
	double eTime;
	short axis[3];
	double pos[3];
	int axis_cnt = 0;
	double dOffsetLimit = 1.0;


	for (int i = Motor_PCB_Xt; i <= Motor_PCB_Yt; i++)
	{
		if (!m_bOrgFlag[i])
		{
			sLangChange.LoadStringA(IDS_STRING1001);	//PCB 부 모터가 원점 복귀를 하지 않았습니다.
			_stprintf_s(logMsg, _T("%s ") + sLangChange, MotorName[i]);
			errMsg2(Task.AutoFlag, logMsg);
			return false;
		}

		axis[i - Motor_PCB_Xt] = i;

		if (i == Motor_PCB_Xt)					pos[i - Motor_PCB_Xt] = model.axis[i].pos[Laser_Pcb_Pos] + offsetX;
		else if (i == Motor_PCB_Yt)			pos[i - Motor_PCB_Xt] = model.axis[i].pos[Laser_Pcb_Pos] + offsetY;
	}

	double MotorPos[2];
	MotorPos[0] = GetCommandPos(Motor_PCB_Xt) - model.axis[Motor_PCB_Xt].pos[Laser_Pcb_Pos];
	MotorPos[1] = GetCommandPos(Motor_PCB_Yt) - model.axis[Motor_PCB_Yt].pos[Laser_Pcb_Pos];

	if (fabs(MotorPos[0]) > model.axis[Motor_PCB_Xt].m_dLimit_Err)
	{
		sLangChange.LoadStringA(IDS_STRING1490);
		sprintf_s(logMsg, sLangChange, GetCommandPos(Motor_PCB_Xt), model.axis[Motor_PCB_Xt].pos[Laser_Pcb_Pos]);
		errMsg2(Task.AutoFlag, logMsg);
		return false;
	}

	if (fabs(MotorPos[1]) > model.axis[Motor_PCB_Yt].m_dLimit_Err)
	{
		sLangChange.LoadStringA(IDS_STRING1491);
		sprintf_s(logMsg, sLangChange, GetCommandPos(Motor_PCB_Yt), model.axis[Motor_PCB_Yt].pos[Laser_Pcb_Pos]);
		errMsg2(Task.AutoFlag, logMsg);
		return false;
	}

	int step = 0;

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif


	double startTime;

	while (1)
	{
		switch (step)
		{
		case 0:									// 3축 모터 대기 위치로 이동 명령..
			startTime = myTimer(true);
			goMotorPos(2, axis, pos);
			step = 100;
			break;

		case 100:								// 이동 완료 확인..
			if (IsStopAxis(Motor_PCB_Xt))		step = 101;
			break;

		case 101:
			if (IsStopAxis(Motor_PCB_Yt))		step = 1000;
			break;

		default:
			break;
		}

		if (step == 1000)
			break;


		eTime = myTimer(true);
		if (eTime - startTime > MOTOR_MOVE_TIME)
		{
			StopAxis(Motor_PCB_Xt);
			StopAxis(Motor_PCB_Yt);

			if (step>100)
			{
				int motorNo = step - 100;
				sLangChange.LoadStringA(IDS_STRING1482);	//PCB 부 [%s 모터] 이동 시간 초과
				_stprintf_s(logMsg, sLangChange, MotorName[motorNo]);
			}
			else
			{
				sLangChange.LoadStringA(IDS_STRING994);	//PCB 부 Align 보정 이동 시간 초과
				_stprintf_s(logMsg, sLangChange);
			}

			errMsg2(Task.AutoFlag, logMsg);

			return false;
		}

		Sleep(5);
		checkMessage();
	}


#ifdef ON_LINE_MOTOR
	for (int i = Motor_PCB_Xt; i <= Motor_PCB_Yt; i++)
	{
		double curPos = GetEncoderPos(axis[i - Motor_PCB_Xt]);
		double cmdPos = GetCommandPos(axis[i - Motor_PCB_Xt]);

		double errVal = fabs(pos[i - Motor_PCB_Xt] - curPos);

		if (errVal>IN_POSITION_VAL)
		{
			sLangChange.LoadStringA(IDS_STRING995);	//PCB 부 Align 보정 이동 후 %s 모터 위치 오차 발생
			_stprintf_s(logMsg, sLangChange, MotorName[i], pos[i], curPos, cmdPos);
			LogSave(logMsg);

			checkMessage();


			for (int j = 0; j<10; j++)
			{
				Sleep(5);
				checkMessage();
			}


			curPos = GetEncoderPos(axis[i - Motor_PCB_Xt]);
			cmdPos = GetCommandPos(axis[i - Motor_PCB_Xt]);

			errVal = fabs(pos[i - Motor_PCB_Xt] - curPos);

			if (errVal>IN_POSITION_VAL)
			{
				sLangChange.LoadStringA(IDS_STRING995);	//PCB 부 Align 보정 이동 후 %s 모터 위치 오차 발생
				_stprintf_s(logMsg, sLangChange, MotorName[i], pos[i], curPos, cmdPos);
				errMsg2(Task.AutoFlag, logMsg);

				return false;
			}

			return false;
		}
	}
#endif

	return true;
}

bool CAxlMotorSet::Pcb_Tilt_Trinity_Move(double offsetX, double offsetY)
{
	char logMsg[1000];
	double eTime;
	short axis[2];
	double pos[2] = { 0.0, };
	int axis_cnt = 0;
	double dOffsetLimit = 1.0;


	for (int i = Motor_PCB_Xt; i <= Motor_PCB_Yt; i++)
	{
		if (!m_bOrgFlag[i])
		{
			sLangChange.LoadStringA(IDS_STRING1001);	//PCB 부 모터가 원점 복귀를 하지 않았습니다.
			_stprintf_s(logMsg, _T("%s ") + sLangChange, MotorName[i]);
			errMsg2(Task.AutoFlag, logMsg);
			return false;
		}

	}


	axis[0] = Motor_PCB_Xt;
	axis[1] = Motor_PCB_Yt;

	pos[0] = offsetX;		// model.axis[Motor_PCB_Xt].pos[index];// + offsetX;
	pos[1] = offsetY;		// model.axis[Motor_PCB_Yt].pos[index];// + offsetX;
	int step = 0;

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif


	double startTime;

	while (1)
	{
		switch (step)
		{
		case 0:									// 2축 모터 대기 위치로 이동 명령..
			startTime = myTimer(true);
			goMotorPos(2, axis, pos);//goMotorPos(2, axis, pos);
			step = 100;
			break;

		case 100:								// 이동 완료 확인..
			if (IsStopAxis(Motor_PCB_Xt))		step = 101;
			break;

		case 101:
			if (IsStopAxis(Motor_PCB_Yt))		step = 1000;
			break;

		default:
			break;
		}

		if (step == 1000)
			break;


		eTime = myTimer(true);
		if (eTime - startTime > MOTOR_MOVE_TIME)
		{
			StopAxis(Motor_PCB_Xt);
			StopAxis(Motor_PCB_Yt);

			if (step>100)
			{
				int motorNo = step - 100;
				sLangChange.LoadStringA(IDS_STRING1482);	//PCB 부 [%s 모터] 이동 시간 초과
				_stprintf_s(logMsg, sLangChange, MotorName[motorNo]);
			}
			else
			{
				sLangChange.LoadStringA(IDS_STRING1002);	//PCB 부 틸팅축 이동 시간 초과
				_stprintf_s(logMsg, sLangChange);
			}

			errMsg2(Task.AutoFlag, logMsg);

			return false;
		}

		Sleep(5);
		checkMessage();
	}


	return true;
}
 




bool CAxlMotorSet::Pcb_Tilt_Motor_Move(int index, double offsetX, double offsetY)
{
	char logMsg[1000];
	double eTime;
	short axis[3];
	double pos[3] = { 0.0, };
	int axis_cnt = 0;
	double dOffsetLimit = 1.0;


	for (int i = Motor_PCB_Xt; i <= Motor_PCB_Yt; i++)
	{
		if (!m_bOrgFlag[i])
		{
			sLangChange.LoadStringA(IDS_STRING1001);	//PCB 부 모터가 원점 복귀를 하지 않았습니다.
			_stprintf_s(logMsg, _T("%s ") + sLangChange, MotorName[i]);
			errMsg2(Task.AutoFlag, logMsg);
			return false;
		}

		/*axis[i-Motor_PCB_Xt]		= i;

		if(i==Motor_PCB_Xt)					pos[i-Motor_PCB_Xt]	= model.axis[i].pos[index] + offsetX;
		else if(i==Motor_PCB_Yt)			pos[i-Motor_PCB_Xt]	= model.axis[i].pos[index] + offsetY;*/
	}


	double MotorPos[2] = { 0.0, };
	MotorPos[0] = GetEncoderPos(Motor_PCB_Xt) - model.axis[Motor_PCB_Xt].pos[index];
	MotorPos[1] = GetEncoderPos(Motor_PCB_Yt) - model.axis[Motor_PCB_Yt].pos[index];

	if (fabs(MotorPos[0]) > model.axis[Motor_PCB_Xt].m_dLimit_Err)
	{
		sLangChange.LoadStringA(IDS_STRING1490);
		sprintf_s(logMsg, sLangChange, GetEncoderPos(Motor_PCB_Xt), model.axis[Motor_PCB_Xt].pos[Laser_Pcb_Pos]);
		errMsg2(Task.AutoFlag, logMsg);
		return false;
	}

	if (fabs(MotorPos[1]) > model.axis[Motor_PCB_Yt].m_dLimit_Err)
	{
		sLangChange.LoadStringA(IDS_STRING1491);
		sprintf_s(logMsg, sLangChange, GetEncoderPos(Motor_PCB_Yt), model.axis[Motor_PCB_Yt].pos[Laser_Pcb_Pos]);
		errMsg2(Task.AutoFlag, logMsg);
		return false;
	}
	if (sysData.m_iProductComp == 1 && index == Bonding_Pos)
	{
		axis[0] = Motor_PCB_Xt;
		axis[1] = Motor_PCB_Yt;
		pos[0] = Task.dAAPcbMotor[3];	 //PCB TX 
		pos[1] = Task.dAAPcbMotor[4];	 //PCB TY 
	}
	else
	{
		axis[0] = Motor_PCB_Xt;
		axis[1] = Motor_PCB_Yt;

		pos[0] = model.axis[Motor_PCB_Xt].pos[index];// + offsetX;
		pos[1] = model.axis[Motor_PCB_Yt].pos[index];// + offsetX;
	}
	int step = 0;

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif


	double startTime;

	while (1)
	{
		switch (step)
		{
		case 0:									// 2축 모터 대기 위치로 이동 명령..
			startTime = myTimer(true);
			goMotorPos(2, axis, pos);//goMotorPos(2, axis, pos);
			step = 100;
			break;

		case 100:								// 이동 완료 확인..
			if (IsStopAxis(Motor_PCB_Xt))		step = 101;
			break;

		case 101:
			if (IsStopAxis(Motor_PCB_Yt))		step = 1000;
			break;

		default:
			break;
		}

		if (step == 1000)
			break;


		eTime = myTimer(true);
		if (eTime - startTime > MOTOR_MOVE_TIME)
		{
			StopAxis(Motor_PCB_Xt);
			StopAxis(Motor_PCB_Yt);

			if (step>100)
			{
				int motorNo = step - 100;
				sLangChange.LoadStringA(IDS_STRING1482);	//PCB 부 [%s 모터] 이동 시간 초과
				_stprintf_s(logMsg, sLangChange, MotorName[motorNo]);
			}
			else
			{
				sLangChange.LoadStringA(IDS_STRING1002);	//PCB 부 틸팅축 이동 시간 초과
				_stprintf_s(logMsg, sLangChange);
			}

			errMsg2(Task.AutoFlag, logMsg);

			return false;
		}

		Sleep(5);
		checkMessage();
	}

	return true;
}




bool CAxlMotorSet::moveSensorContactPos(bool waitFlag)
{
	double eTime;
	short axis[4] = {Motor_PCB_X, Motor_PCB_Y, Motor_PCB_TH, Motor_PCB_Z};//short axis[2] = {Motor_PCB_Y, Motor_Epoxy_Z};
	double pos[4];

	if( checkOriginStatus(3, axis) == false )
	{
		sLangChange.LoadStringA(IDS_STRING552);	//Epoxy부 X, Y, Th 축 모터가 원점 복귀를 하지 않았습니다.
		_stprintf_s(m_szLogMsg, sLangChange);
		errMsg2(Task.AutoFlag, m_szLogMsg);
		return false;
	}

	if ( (IsStopAxis(Motor_PCB_X) == false) || (IsStopAxis(Motor_PCB_Y) == false) )
	{
		sLangChange.LoadStringA(IDS_STRING551);	//Epoxy부 X, Y 축 모터가 동작 중입니다.
		_stprintf_s(m_szLogMsg, sLangChange);
		errMsg2(Task.AutoFlag, m_szLogMsg);
		return false;
	}

	if(!moveWaitPos_Z(true))	return false;

	pos[0] = model.axis[Motor_PCB_X].pos[Contact_Pos]; 
	pos[1] = model.axis[Motor_PCB_Y].pos[Contact_Pos];
	pos[2] = model.axis[Motor_PCB_TH].pos[Contact_Pos];
	goMotorPos(3, axis, pos);

	while(1)
	{
		if( (IsStopAxis(Motor_PCB_X)) && IsStopAxis(Motor_PCB_Y) && IsStopAxis(Motor_PCB_TH) ) break; 
	}

	pos[0] = model.axis[Motor_PCB_X].pos[Contact_Pos]; 
	pos[1] = model.axis[Motor_PCB_Y].pos[Contact_Pos];
	pos[2] = model.axis[Motor_PCB_TH].pos[Contact_Pos];
	pos[3] = model.axis[Motor_PCB_Z].pos[Contact_Pos] - 1.0;
	goMotorPos(4, axis, pos);

	int step=100;

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif

	eTime = myTimer(true);
	while (waitFlag)
	{
		switch(step)
		{
		case 100:		
			if(IsStopAxis(Motor_PCB_Y))
				step = 200;
			break;

		case 200:
			if (IsStopAxis(Motor_PCB_Z) == true)
				step = 1000;
		default:
			break;
		}

		if(step==1000)
			break;


		if(myTimer(true) - eTime>MOTOR_MOVE_TIME)
		{
			StopAxis(Motor_PCB_Y);
			StopAxis(Motor_PCB_Z);
			
			sLangChange.LoadStringA(IDS_STRING554);	//Epoxy부 Y, Z축 센서 측정 위치 이동 실패
			_stprintf_s(m_szLogMsg, sLangChange);
			errMsg2(Task.AutoFlag,m_szLogMsg);

			return false;
		}

		Sleep(5);
		checkMessage();
	}

	return true;
}




bool CAxlMotorSet::checkOriginStatus(int iCnt, short* axis)
{
	CString sLog;

	for (int i=0 ; i<iCnt ; i++)
	{
		if ( GetAmpFault(axis[i]) != false )
		{
			sLangChange.LoadStringA(IDS_STRING1245);
			sLog.Format(_T("%s ") + sLangChange, MotorName[axis[i]]);	//모터가 알람 상태입니다.
			errMsg2(Task.AutoFlag, sLog);
			return false;
		}
	}

	for (int i=0 ; i<iCnt ; i++)
	{
		if ( m_bOrgFlag[axis[i]] == false )
		{
			sLangChange.LoadStringA(IDS_STRING1246);
			sLog.Format(_T("%s ") + sLangChange, MotorName[axis[i]]);	//모터가 원점 복귀를 하지 않았습니다
			errMsg2(Task.AutoFlag, sLog);
			return false;
		}
	}

	return true;
}

bool CAxlMotorSet::moveWaitPos_Z(bool waitFlag)
{
	double eTime;
	short axis[2];
	double pos[2];

	if(!m_bOrgFlag[Motor_PCB_Z])
	{	
		sLangChange.LoadStringA(IDS_STRING555);
		_stprintf_s(m_szLogMsg, sLangChange);	//"Epoxy부 Z 축 모터가 원점 복귀를 하지 않았습니다."
		errMsg2(Task.AutoFlag, m_szLogMsg);
		return false;
	}

	if ( IsStopAxis(Motor_PCB_Z) == false )
	{
		sLangChange.LoadStringA(IDS_STRING558);
		_stprintf_s(m_szLogMsg, sLangChange);	//"Epoxy부 Z축 모터가 동작 중입니다."
		errMsg2(Task.AutoFlag, m_szLogMsg);
		return false;
	}

	axis[0] = Motor_PCB_Z;
	pos[0] = model.axis[Motor_PCB_Z].pos[Wait_Pos];

	goMotorPos(1, axis, pos);

	int step=100;

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif

	eTime = myTimer(true);
	while (waitFlag)
	{
		switch(step)
		{
		case 100:		
			if(IsStopAxis(Motor_PCB_Z))
				step = 1000;
			break;

		default:
			break;
		}

		if(step==1000)
			break;


		if((myTimer(true) - eTime) > MOTOR_MOVE_TIME)
		{
			StopAxis(Motor_PCB_Z);
			sLangChange.LoadStringA(IDS_STRING556);
			_stprintf_s(m_szLogMsg, sLangChange);	//"Epoxy부 Z축 대기 위치 이동 실패"
			errMsg2(Task.AutoFlag,m_szLogMsg);

			return false;
		}

		Sleep(5);
		checkMessage();
	}
	return true;
}



bool CAxlMotorSet::movePointDischargePos(bool waitFlag)
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	double eTime;
	short axis[3] = {Motor_PCB_X, Motor_PCB_Y, Motor_PCB_TH};
	double pos[3];

	if( checkOriginStatus(3, axis) == false )
	{
		sLangChange.LoadStringA(IDS_STRING1246);
		_stprintf_s(m_szLogMsg, sLangChange);	//"PCB부 X, Th, Y 축 모터가 원점 복귀를 하지 않았습니다."
		errMsg2(Task.AutoFlag, m_szLogMsg);
		return false;
	}

	if ( (IsStopAxis(Motor_PCB_X) == false)		||
		 (IsStopAxis(Motor_PCB_TH) == false)	||
		 (IsStopAxis(Motor_PCB_Y) == false)		)
	{
		sLangChange.LoadStringA(IDS_STRING1019);
		_stprintf_s(m_szLogMsg, sLangChange);	//"PCB부 X, Th, Y 축 모터가 동작 중입니다."
		errMsg2(Task.AutoFlag, m_szLogMsg);
		return false;
	}

	if(!moveWaitPos_Z(true))
		return false;

	pos[0]	= model.axis[Motor_PCB_X].pos[Calc_Pos];
	pos[1]	= model.axis[Motor_PCB_Y].pos[Calc_Pos];
	pos[2]	= model.axis[Motor_PCB_TH].pos[Calc_Pos];

	//startMoveAxis(3, axis, pos);
	goMotorPos(3, axis, pos);

	int step=100;

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif

	eTime = myTimer(true);
	while (waitFlag)
	{
		switch(step)
		{
		case 100:		
			if(IsStopAxis(Motor_PCB_X))
				step = 200;
			break;
		case 200:
			if(IsStopAxis(Motor_PCB_TH))
				step = 300;
			break;
		case 300:
			if(IsStopAxis(Motor_PCB_Y))
				step = 1000;
			break;
		default:
			break;
		}

		if(step==1000)
			break;


		if(myTimer(true) - eTime>MOTOR_MOVE_TIME)
		{
			StopAxis(Motor_PCB_X);
			StopAxis(Motor_PCB_TH);
			StopAxis(Motor_PCB_Y);

			sLangChange.LoadStringA(IDS_STRING1018);
			_stprintf_s(m_szLogMsg, sLangChange);		//"PCB부 X, Th, Y 축 Point 토출 위치 이동 실패"
			errMsg2(Task.AutoFlag,m_szLogMsg);

			return false;
		}

		Sleep(5);
		checkMessage();
	}

	return true;
}

//도포 calc2

bool CAxlMotorSet::movePointDischarge2Pos(bool waitFlag)
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	double eTime;
	short axis[3] = {Motor_PCB_X, Motor_PCB_Y, Motor_PCB_TH};
	double pos[3];

	if( checkOriginStatus(3, axis) == false )
	{
		sLangChange.LoadStringA(IDS_STRING1246);
		_stprintf_s(m_szLogMsg, sLangChange);	//"PCB부 X, Th, Y 축 모터가 원점 복귀를 하지 않았습니다."
		errMsg2(Task.AutoFlag, m_szLogMsg);
		return false;
	}

	if ( (IsStopAxis(Motor_PCB_X) == false)		||
		 (IsStopAxis(Motor_PCB_TH) == false)	||
		 (IsStopAxis(Motor_PCB_Y) == false)		)
	{
		sLangChange.LoadStringA(IDS_STRING1019);
		_stprintf_s(m_szLogMsg, sLangChange);	//"PCB부 X, Th, Y 축 모터가 동작 중입니다."
		errMsg2(Task.AutoFlag, m_szLogMsg);
		return false;
	}

	if(!moveWaitPos_Z(true))
		return false;

	pos[0]	= model.axis[Motor_PCB_X].pos[Calc2_Pos];
	pos[1]	= model.axis[Motor_PCB_Y].pos[Calc2_Pos];
	pos[2]	= model.axis[Motor_PCB_TH].pos[Calc2_Pos];

	//startMoveAxis(3, axis, pos);
	goMotorPos(3, axis, pos);

	int step=100;

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif

	eTime = myTimer(true);
	while (waitFlag)
	{
		switch(step)
		{
		case 100:		
			if(IsStopAxis(Motor_PCB_X))
				step = 200;
			break;
		case 200:
			if(IsStopAxis(Motor_PCB_TH))
				step = 300;
			break;
		case 300:
			if(IsStopAxis(Motor_PCB_Y))
				step = 1000;
			break;
		default:
			break;
		}

		if(step==1000)
			break;


		if(myTimer(true) - eTime>MOTOR_MOVE_TIME)
		{
			StopAxis(Motor_PCB_X);
			StopAxis(Motor_PCB_TH);
			StopAxis(Motor_PCB_Y);

			sLangChange.LoadStringA(IDS_STRING1018);
			_stprintf_s(m_szLogMsg, sLangChange);		//"PCB부 X, Th, Y 축 Point 토출 위치 이동 실패"
			errMsg2(Task.AutoFlag,m_szLogMsg);

			return false;
		}

		Sleep(5);
		checkMessage();
	}

	return true;
}

bool CAxlMotorSet::moveDispensePos_Z(int iPcbNo, bool waitFlag)
{
	double eTime;
	short axis[2];
	double pos[2];

	if(!m_bOrgFlag[Motor_PCB_Z])
	{
		sLangChange.LoadStringA(IDS_STRING555);
		_stprintf_s(m_szLogMsg, sLangChange);	//"Epoxy부 Z 축 모터가 원점 복귀를 하지 않았습니다."
		errMsg2(Task.AutoFlag, m_szLogMsg);
		return false;
	}

	if ( IsStopAxis(Motor_PCB_Z) == false )
	{
		sLangChange.LoadStringA(IDS_STRING558);
		_stprintf_s(m_szLogMsg, sLangChange);	//"Epoxy부 Z축 모터가 동작 중입니다."
		errMsg2(Task.AutoFlag, m_szLogMsg);
		return false;
	}

	axis[0] = Motor_PCB_Z;
	pos[0] = model.axis[Motor_PCB_Z].pos[Dispense_Pos] + model.offset.f_epoxy_z_dispense_offset[iPcbNo];

	//startMoveAxis(1, axis, pos);
	goMotorPos(1, axis, pos);

	int step=100;

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif

	eTime = myTimer(true);
	while (waitFlag)
	{
		switch(step)
		{
		case 100:		
			if(IsStopAxis(Motor_PCB_Z))
				step = 1000;
			break;

		default:
			break;
		}

		if(step==1000)
			break;


		if((myTimer(true) - eTime) > MOTOR_MOVE_TIME)
		{
			StopAxis(Motor_PCB_Z);
			sLangChange.LoadStringA(IDS_STRING557);
			_stprintf_s(m_szLogMsg, sLangChange);	//"Epoxy부 Z축 도포 위치 이동 실패"
			errMsg2(Task.AutoFlag,m_szLogMsg);

			return false;
		}

		Sleep(5);
		checkMessage();
	}
	return true;
}

bool CAxlMotorSet::movePointDischargePos_Z(bool waitFlag)
{
	double eTime;
	short axis[1] = {Motor_PCB_Z};
	double pos[1];

	if( checkOriginStatus(1, axis) == false )
	{
		sLangChange.LoadStringA(IDS_STRING555);
		_stprintf_s(m_szLogMsg, sLangChange);	//"Epoxy부 Z 축 모터가 원점 복귀를 하지 않았습니다."
		errMsg2(Task.AutoFlag, m_szLogMsg);
		return false;
	}

	if ( (IsStopAxis(Motor_PCB_Z) == false) )
	{
		sLangChange.LoadStringA(IDS_STRING558);
		_stprintf_s(m_szLogMsg, sLangChange);	//"Epoxy부 Z축 모터가 동작 중입니다."
		errMsg2(Task.AutoFlag, m_szLogMsg);
		return false;
	}

	pos[0] = model.axis[Motor_PCB_Z].pos[Calc_Pos];

	//startMoveAxis(1, axis, pos);
	goMotorPos(1, axis, pos);

	int step=100;

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif

	eTime = myTimer(true);
	while (waitFlag)
	{
		switch(step)
		{
		case 100:		
			if(IsStopAxis(Motor_PCB_Z))
				step = 1000;
			break;
		default:
			break;
		}

		if(step==1000)
			break;


		if(myTimer(true) - eTime>MOTOR_MOVE_TIME)
		{
			StopAxis(Motor_PCB_Y);
			sLangChange.LoadStringA(IDS_STRING553);
			_stprintf_s(m_szLogMsg, sLangChange);		//"Epoxy부 Y 축 Point 토출 위치 이동 실패"
			errMsg2(Task.AutoFlag,m_szLogMsg);

			return false;
		}

		Sleep(5);
		checkMessage();
	}

	return true;
}

//도포 calc Z

bool CAxlMotorSet::movePointDischarge2Pos_Z(bool waitFlag)
{
	double eTime;
	short axis[1] = {Motor_PCB_Z};
	double pos[1];

	if( checkOriginStatus(1, axis) == false )
	{
		sLangChange.LoadStringA(IDS_STRING555);
		_stprintf_s(m_szLogMsg, sLangChange);	//"Epoxy부 Z 축 모터가 원점 복귀를 하지 않았습니다."
		errMsg2(Task.AutoFlag, m_szLogMsg);
		return false;
	}

	if ( (IsStopAxis(Motor_PCB_Z) == false) )
	{
		sLangChange.LoadStringA(IDS_STRING558);
		_stprintf_s(m_szLogMsg, sLangChange);	//"Epoxy부 Z축 모터가 동작 중입니다."
		errMsg2(Task.AutoFlag, m_szLogMsg);
		return false;
	}

	pos[0] = model.axis[Motor_PCB_Z].pos[Calc2_Pos];

	//startMoveAxis(1, axis, pos);
	goMotorPos(1, axis, pos);

	int step=100;

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif

	eTime = myTimer(true);
	while (waitFlag)
	{
		switch(step)
		{
		case 100:		
			if(IsStopAxis(Motor_PCB_Z))
				step = 1000;
			break;
		default:
			break;
		}

		if(step==1000)
			break;


		if(myTimer(true) - eTime>MOTOR_MOVE_TIME)
		{
			StopAxis(Motor_PCB_Y);
			
			sLangChange.LoadStringA(IDS_STRING553);
			_stprintf_s(m_szLogMsg, sLangChange);		//"Epoxy부 Y 축 Point 토출 위치 이동 실패"
			errMsg2(Task.AutoFlag,m_szLogMsg);

			return false;
		}

		Sleep(5);
		checkMessage();
	}

	return true;
}
bool CAxlMotorSet::func_Epoxy_Left_StraightDraw()
{//직선 도포 
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	int step=0;
//	double startTime;
//	double MoveStartTime;
	//double eTime, curTime;
	int iEpoxyDelay = model.iEpoxyDelay;
	CString sMsg;

	while(1)
	{
		switch(step)
		{
		case 0:
			if( Dio.EpoxyDischargeOn2(true))
			{
				Sleep(500);
				step = 40;
			}
			else
			{
				sLangChange.LoadStringA(IDS_STRING188);
				sMsg.Format(sLangChange);	//"[Dispence동작] Epoxy 토출 신호 이상 발생_토출 ON 신호"
				errMsg2(Task.AutoFlag, sMsg);
				return false;
			}
			break;

		case 40:		
			if(Straight_Dispense_MoveAxis(Motor_PCB_Y, REL, model.dEpoxySize, model.dEpoxySpeed, model.dAcc))
			{
				double ep = myTimer(true);

				while (1)
				{
					if ( myTimer(true)-ep < 5000)
					{
						if ( motor.IsStopAxis(Motor_PCB_Y) && motor.GetInposition(Motor_PCB_Y) )
						{
							sLangChange.LoadStringA(IDS_STRING192);
							sMsg.Format(sLangChange);	//"[Dispense동작] Epoxy Y축 이동 완료"
							pFrame->putListLog(sMsg);
							step = 50;
							break;
						}
					}
					else
					{
						sLangChange.LoadStringA(IDS_STRING191);
						sMsg.Format(sLangChange);		//"[Dispense동작] Epoxy Y축 이동 실패"
						errMsg2(Task.AutoFlag, sMsg);
						return false;
					}
				}
			}
			else
			{
				sLangChange.LoadStringA(IDS_STRING191);
				sMsg.Format(sLangChange);		//"[Dispense동작] Epoxy Y축 이동 실패"
				errMsg2(Task.AutoFlag, sMsg);
				return false;
			}
			break;

		case 50:
			if(StopAxis(Motor_PCB_Y))
			{
				Dio.EpoxyDischargeOn2(false, false);
				sLangChange.LoadStringA(IDS_STRING193);
				sMsg.Format(sLangChange);	//"[Dispense동작] Epoxy 토출 Off 완료"
				pFrame->putListLog(sMsg);
				Sleep(iEpoxyDelay);
			}
			else
			{
				Dio.EpoxyDischargeOn2(false, false);
			}
			step = 1000;
			break;
		
		default:
			step = 1000;
			break;
		}

		if(step==1000)		break;
	}

	return true;
}

bool CAxlMotorSet::func_Epoxy_Right_StraightDraw()
{//직선 도포 
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	int step=0;
//	double startTime;
//	double MoveStartTime;
//	double eTime, curTime;
	int iEpoxyDelay = model.iEpoxyDelay;
	CString sMsg;

	while(1)
	{
		switch(step)
		{
		case 0:
			if( Dio.EpoxyDischargeOn2(true))
			{
				Sleep(500);
				step = 40;
			}
			else
			{
				sLangChange.LoadStringA(IDS_STRING188);
				sMsg.Format(sLangChange);	//"[Dispence동작] Epoxy 토출 신호 이상 발생_토출 ON 신호"
				errMsg2(Task.AutoFlag, sMsg);
				return false;
			}
			break;

		case 40:		
			if(Straight_Dispense_MoveAxis(Motor_PCB_Y, REL, model.dEpoxySize, model.dEpoxySpeed, model.dAcc))
			{
				double ep = myTimer(true);

				while (1)
				{
					if ( myTimer(true)-ep < 5000)
					{
						if ( motor.IsStopAxis(Motor_PCB_Y) && motor.GetInposition(Motor_PCB_Y) )
						{
							sLangChange.LoadStringA(IDS_STRING192);
							sMsg.Format(sLangChange);	//"[Dispense동작] Epoxy Y축 이동 완료"
							pFrame->putListLog(sMsg);
							step = 50;
							break;
						}
					}
					else
					{
						sLangChange.LoadStringA(IDS_STRING191);
						sMsg.Format(sLangChange);		//"[Dispense동작] Epoxy Y축 이동 실패"
						errMsg2(Task.AutoFlag, sMsg);
						return false;
					}
				}
			}
			else
			{
				sLangChange.LoadStringA(IDS_STRING191);
				sMsg.Format(sLangChange);		//"[Dispense동작] Epoxy Y축 이동 실패"
				errMsg2(Task.AutoFlag, sMsg);
				return false;
			}
			break;

		case 50:
			if(StopAxis(Motor_PCB_Y))
			{
				Dio.EpoxyDischargeOn2(false, false);

				sLangChange.LoadStringA(IDS_STRING193);
				sMsg.Format(sLangChange);	//"[Dispense동작] Epoxy 토출 Off 완료"
				pFrame->putListLog(sMsg);
				Sleep(iEpoxyDelay);
			}
			else
			{
				Dio.EpoxyDischargeOn2(false, false);
			}
			step = 1000;
			break;
		
		default:
			step = 1000;
			break;
		}

		if(step==1000)		break;
	}

	return true;
}

bool CAxlMotorSet::Trinityt_Dispense_MoveAxis()
{	// abs 1:absolute, 0:increment\



	//if (AbSFlag == ABS)
	//{
	//	double curPos;
	//	if (axis == Motor_Lens_Xt || axis == Motor_Lens_Yt || axis == Motor_PCB_Xt || axis == Motor_PCB_Yt)
	//		curPos = GetCommandPos(axis);	//GetCommandPos(axis);
	//	else
	//		curPos = GetEncoderPos(axis);	//GetCommandPos(axis);
	//	if (fabs(curPos - dPos) < 0.0001)
	//	{
	//		return true;
	//	}
	//	if (m_bOrgFlag[axis] == false)
	//	{
	//		TCHAR	motorMSG[256];
	//		sTempLang.LoadStringA(IDS_STRING367);
	//		sLangChange.Format(sTempLang, axis + 1);
	//		wsprintf(motorMSG, sLangChange);
	//		return false;
	//	}
	//}
	//else if (AbSFlag == REL)
	//{
	//	if (axis == Motor_Lens_Xt || axis == Motor_Lens_Yt || axis == Motor_PCB_Xt || axis == Motor_PCB_Yt)
	//		dPos += GetCommandPos(axis);
	//	else
	//		dPos += GetEncoderPos(axis);	//GetCommandPos(axis);
	//}
	//dPos *= sysData.fMotorResol[axis];
	//if (dPos>0)					dPos = (int)(dPos + 0.5);

	long   axisAll[MAX_MOTOR_NO] = { 0, };
	double posAll[MAX_MOTOR_NO] = { 0, };
	double velAll[MAX_MOTOR_NO] = { 0, };
	double accAll[MAX_MOTOR_NO] = { 0, };
	double decAll[MAX_MOTOR_NO] = { 0, };


	//! 여러 개의 축에 대해서 현재의 위치에서 지정한 거리만큼 이동을 동시에 시작한다. 
	//! 이 함수를 사용하면 여러 개의 축이 동시에 작업을 시작한다. 
	//! 이 함수는 여러 축이 동기를 맞추어 작업을 시작해야 하는 경우에 사용한다. 
	//! 펄스 출력이 시작되는 시점에서 함수를 벗어난다.

	//210716
	//
	//
	long MOTOR_DIR = 0;
	double dAngle = 0.0;
	double CircleSpeed = 0.0;
	double TrinityCircleRadius = 0.0;
	double dPos[2];
	double dMidPos[2];
	double dEndPos[2];
	dMidPos[0] = dMidPos[1] = 0.0;
	dEndPos[0] = dEndPos[1] = 0.0;
	dPos[0] = dPos[1] = 0.0;
	int cnt = 2;
	long    lAxis[2];
	lAxis[0] = Motor_PCB_X; //축번호
	lAxis[1] = Motor_PCB_Y;

	long    lPosSize = 2;
	long  lCoordinate = 0;

	AxmContiWriteClear(lCoordinate);
	AxmContiSetAxisMap(lCoordinate, lPosSize, lAxis);

	// 상대위치 구동등록.
	AxmContiSetAbsRelMode(lCoordinate, 1);
	AxmContiBeginNode(lCoordinate);
	//
	axisAll[0] = Motor_PCB_X;
	axisAll[1] = Motor_PCB_Y;
	velAll[0] = model.dEpoxySpeed * sysData.fMotorResol[axisAll[0]];
	velAll[1] = model.dEpoxySpeed * sysData.fMotorResol[axisAll[1]];
	accAll[0] = accAll[1] = model.dAcc;
	decAll[0] = decAll[1] = model.dAcc;

	//===================================================================================================================================
	//동작 1 
	//하단 직선
	posAll[0] = posAll[1] = 0.0;
	posAll[0] = model.dDisLength[0] * -1;
	posAll[0] *= sysData.fMotorResol[Motor_PCB_X];
	//
	if (posAll[0]>0) posAll[0] = (int)(posAll[0] + 0.5);
	posAll[1] *= sysData.fMotorResol[Motor_PCB_Y];
	
	
	accAll[0] = accAll[1] = model.dAcc;   
	decAll[0] = decAll[1] = model.dAcc;
	velAll[0] = model.dEpoxySpeed * sysData.fMotorResol[axisAll[0]];
	AxmLineMove(lCoordinate, posAll, velAll[0], accAll[0], decAll[0]); 
	//===================================================================================================================================
	//동작 2
	//우측 하단 커브
	CircleSpeed = model.dConti_Speed * sysData.fMotorResol[axisAll[0]];
	dMidPos[0] = model.dCircleRadiusCenterOffsetX[0]*10000; 
	dMidPos[1] = model.dCircleRadiusCenterOffsetY[0] * 10000;
	dEndPos[0] = model.dCircleRadiusEndOffsetX[0] * 10000;
	dEndPos[1] = model.dCircleRadiusEndOffsetY[0] * 10000;   
	MOTOR_DIR = DIR_CCW;
	AxmCircleCenterMove(lCoordinate, axisAll, dMidPos, dEndPos, CircleSpeed, accAll[0], decAll[0], MOTOR_DIR);
	//===================================================================================================================================
	//동작 3
	//우측 직선
	axisAll[0] = Motor_PCB_X;
	axisAll[1] = Motor_PCB_Y; 
	posAll[0] = posAll[1] = 0.0;
	posAll[0] *= sysData.fMotorResol[Motor_PCB_X];

	posAll[1] = model.dDisLength[1] * -1; 
	posAll[1] *= sysData.fMotorResol[Motor_PCB_Y];
	if (posAll[1]>0)					posAll[1] = (int)(posAll[1] + 0.5);

	velAll[0] = model.dEpoxySpeed * sysData.fMotorResol[axisAll[0]];
	AxmLineMove(lCoordinate, posAll, velAll[0], accAll[0], decAll[0]);
	//===================================================================================================================================
	//동작 4
	//우측상단 커브 전 직선
	posAll[0] = posAll[1] = 0.0;
	posAll[0] = model.dDisLength[4] * 1;
	posAll[0] *= sysData.fMotorResol[Motor_PCB_X];
	//
	if (posAll[0]>0) posAll[0] = (int)(posAll[0] + 0.5);
	posAll[1] *= sysData.fMotorResol[Motor_PCB_Y];


	accAll[0] = accAll[1] = model.dAcc;
	decAll[0] = decAll[1] = model.dAcc;

	velAll[0] = model.dConti_Speed * sysData.fMotorResol[axisAll[0]];

	AxmLineMove(lCoordinate, posAll, velAll[0], accAll[0], decAll[0]);
	//===================================================================================================================================
	//동작 5
	//우측상단 커브
	CircleSpeed = model.dConti_Speed * sysData.fMotorResol[axisAll[0]];
	dMidPos[0] = model.dCircleRadiusCenterOffsetX[1] * 10000;
	dMidPos[1] = model.dCircleRadiusCenterOffsetY[1] * 10000; 
	dEndPos[0] = model.dCircleRadiusEndOffsetX[1] * 10000;
	dEndPos[1] = model.dCircleRadiusEndOffsetY[1] * 10000;
	MOTOR_DIR = DIR_CW;
	AxmCircleCenterMove(lCoordinate, axisAll, dMidPos, dEndPos, CircleSpeed, accAll[0], decAll[0], MOTOR_DIR);
	//===================================================================================================================================
	//동작 6
	//우측상단 커브 후 직선
	axisAll[0] = Motor_PCB_X;
	axisAll[1] = Motor_PCB_Y;
	posAll[0] = posAll[1] = 0.0;
	posAll[0] *= sysData.fMotorResol[Motor_PCB_X];

	posAll[1] = model.dDisLength[5] * -1;
	posAll[1] *= sysData.fMotorResol[Motor_PCB_Y];
	if (posAll[1]>0)					posAll[1] = (int)(posAll[1] + 0.5);

	velAll[0] = model.dConti_Speed * sysData.fMotorResol[axisAll[0]];
	AxmLineMove(lCoordinate, posAll, velAll[0], accAll[0], decAll[0]);

	//===================================================================================================================================
	//동작 7
	//상단 직선
	posAll[0] = posAll[1] = 0.0;

	posAll[0] = model.dDisLength[2] * 1;
	posAll[0] *= sysData.fMotorResol[Motor_PCB_X];
	//
	if (posAll[0]>0)					posAll[0] = (int)(posAll[0] + 0.5);
	posAll[1] *= sysData.fMotorResol[Motor_PCB_Y];

	velAll[0] = model.dEpoxySpeed * sysData.fMotorResol[axisAll[0]];
	AxmLineMove(lCoordinate, posAll, velAll[0], accAll[0], decAll[0]);
	//===================================================================================================================================
	//동작 8
	//좌측 상단 커브
	CircleSpeed = model.dConti_Speed * sysData.fMotorResol[axisAll[0]];
	dMidPos[0] = model.dCircleRadiusCenterOffsetX[2] * 10000;
	dMidPos[1] = model.dCircleRadiusCenterOffsetY[2] * 10000;
	dEndPos[0] = model.dCircleRadiusEndOffsetX[2] * 10000;
	dEndPos[1] = model.dCircleRadiusEndOffsetY[2] * 10000;
	MOTOR_DIR = DIR_CCW;
	AxmCircleCenterMove(lCoordinate, axisAll, dMidPos, dEndPos, CircleSpeed, accAll[0], decAll[0], MOTOR_DIR);
	//===================================================================================================================================
	//동작 9
	//좌측 직선
	posAll[0] = posAll[1] = 0.0;
	posAll[0] *= sysData.fMotorResol[Motor_PCB_X];

	posAll[1] = model.dDisLength[3] * 1;
	posAll[1] *= sysData.fMotorResol[Motor_PCB_Y];
	if (posAll[1]>0)					posAll[1] = (int)(posAll[1] + 0.5);

	velAll[0] = model.dEpoxySpeed * sysData.fMotorResol[axisAll[0]];
	AxmLineMove(lCoordinate, posAll, velAll[0], accAll[0], decAll[0]);
	//===================================================================================================================================
	//동작 10
	//좌측상단 커브 전 직선
	posAll[0] = posAll[1] = 0.0;

	posAll[0] = model.dDisLength[6] * -1;
	posAll[0] *= sysData.fMotorResol[Motor_PCB_X];
	//
	if (posAll[0]>0)					posAll[0] = (int)(posAll[0] + 0.5);
	posAll[1] *= sysData.fMotorResol[Motor_PCB_Y];

	velAll[0] = model.dConti_Speed * sysData.fMotorResol[axisAll[0]];
	AxmLineMove(lCoordinate, posAll, velAll[0], accAll[0], decAll[0]);
	//===================================================================================================================================
	//동작 11
	//좌측 하단 커브
	CircleSpeed = model.dConti_Speed * sysData.fMotorResol[axisAll[0]];
	dMidPos[0] = model.dCircleRadiusCenterOffsetX[3] * 10000;
	dMidPos[1] = model.dCircleRadiusCenterOffsetY[3] * 10000;
	dEndPos[0] = model.dCircleRadiusEndOffsetX[3] * 10000;
	dEndPos[1] = model.dCircleRadiusEndOffsetY[3] * 10000;
	MOTOR_DIR = DIR_CW;
	AxmCircleCenterMove(lCoordinate, axisAll, dMidPos, dEndPos, CircleSpeed, accAll[0], decAll[0], MOTOR_DIR);
	//===================================================================================================================================
	//동작 12
	//좌측상단 커브 후 직선
	posAll[0] = posAll[1] = 0.0;
	posAll[0] *= sysData.fMotorResol[Motor_PCB_X];

	posAll[1] = model.dDisLength[7] * 1;
	posAll[1] *= sysData.fMotorResol[Motor_PCB_Y];
	if (posAll[1]>0)					posAll[1] = (int)(posAll[1] + 0.5);

	velAll[0] = model.dConti_Speed * sysData.fMotorResol[axisAll[0]];
	AxmLineMove(lCoordinate, posAll, velAll[0], accAll[0], decAll[0]); 

	 
	//===================================================================================================================================
	//
	AxmContiEndNode(lCoordinate);
	// 상대위치 구동시작.
	AxmContiSetAbsRelMode(lCoordinate, 1);
	// 연속보간구동 시작.
	AxmContiStart(lCoordinate, 0, 0);

	
	Sleep(10);
	return true;
}
bool CAxlMotorSet::Continue_Line_Arck_Dispense()
{
	long   axisAll[MAX_MOTOR_NO] = { 0, };
	double posAll[MAX_MOTOR_NO] = { 0, };
	double velAll[MAX_MOTOR_NO] = { 0, };
	double accAll[MAX_MOTOR_NO] = { 0, };
	double decAll[MAX_MOTOR_NO] = { 0, };


	//! 여러 개의 축에 대해서 현재의 위치에서 지정한 거리만큼 이동을 동시에 시작한다. 
	//! 이 함수를 사용하면 여러 개의 축이 동시에 작업을 시작한다. 
	//! 이 함수는 여러 축이 동기를 맞추어 작업을 시작해야 하는 경우에 사용한다. 
	//! 펄스 출력이 시작되는 시점에서 함수를 벗어난다.

	//210716
	//
	//
	long MOTOR_DIR = 0;
	double dAngle = 0.0;
	double CircleSpeed = 0.0;
	double TrinityCircleRadius = 0.0;
	double dPos[2];
	double dMidPos[2];
	double dEndPos[2];
	dMidPos[0] = dMidPos[1] = 0.0;
	dEndPos[0] = dEndPos[1] = 0.0;
	//dPos[0] = dPos[1] = 0.0;
	int cnt = 2;
	long    lAxis[2];
	lAxis[0] = Motor_PCB_X; //축번호
	lAxis[1] = Motor_PCB_Y;

	long    lPosSize = 2;
	long  lCoordinate = 0;

	AxmContiWriteClear(lCoordinate);
	AxmContiSetAxisMap(lCoordinate, lPosSize, lAxis);

	// 상대위치 구동등록.
	AxmContiSetAbsRelMode(lCoordinate, 1);
	AxmContiBeginNode(lCoordinate);
	//
	axisAll[0] = Motor_PCB_X;
	axisAll[1] = Motor_PCB_Y;
	velAll[0] = model.dEpoxySpeed * sysData.fMotorResol[axisAll[0]];
	velAll[1] = model.dEpoxySpeed * sysData.fMotorResol[axisAll[1]];
	accAll[0] = accAll[1] = model.dAcc;
	decAll[0] = decAll[1] = model.dAcc;

	//===================================================================================================================================
	//동작 1 
	//하단 직선
	posAll[0] = posAll[1] = 0.0;
	posAll[0] = model.dDisLength[4] * -1;
	posAll[0] *= sysData.fMotorResol[Motor_PCB_X];
	//
	if (posAll[0]>0) posAll[0] = (int)(posAll[0] + 0.5);
	posAll[1] *= sysData.fMotorResol[Motor_PCB_Y];


	accAll[0] = accAll[1] = model.dAcc;
	decAll[0] = decAll[1] = model.dAcc;
	AxmLineMove(lCoordinate, posAll, velAll[0], accAll[0], decAll[0]);
	//===================================================================================================================================
	//동작 2
	//우측 하단 커브
	CircleSpeed = model.dCircleSpeed * sysData.fMotorResol[axisAll[0]]; 
	dMidPos[0] = model.dCircleRadiusCenterOffsetX[0] * 10000;
	dMidPos[1] = model.dCircleRadiusCenterOffsetY[0] * 10000;
	dEndPos[0] = model.dCircleRadiusEndOffsetX[0] * 10000;
	dEndPos[1] = model.dCircleRadiusEndOffsetY[0] * 10000;
	MOTOR_DIR = DIR_CCW;

	AxmCircleCenterMove(lCoordinate, axisAll, dMidPos, dEndPos, CircleSpeed, accAll[0], decAll[0], MOTOR_DIR);
	//===================================================================================================================================
	//동작 3
	//우측 직선
	axisAll[0] = Motor_PCB_X;
	axisAll[1] = Motor_PCB_Y;
	posAll[0] = posAll[1] = 0.0;
	posAll[0] *= sysData.fMotorResol[Motor_PCB_X];

	posAll[1] = model.dDisLength[5] * -1;
	posAll[1] *= sysData.fMotorResol[Motor_PCB_Y];
	if (posAll[1]>0)					posAll[1] = (int)(posAll[1] + 0.5);

	AxmLineMove(lCoordinate, posAll, velAll[0], accAll[0], decAll[0]);
	//===================================================================================================================================
	//동작 4
	//우측상단 커브 전 직선
	//posAll[0] = posAll[1] = 0.0;
	//posAll[0] = model.dDisLength[4] * 1;
	//posAll[0] *= sysData.fMotorResol[Motor_PCB_X];
	////
	//if (posAll[0]>0) posAll[0] = (int)(posAll[0] + 0.5);
	//posAll[1] *= sysData.fMotorResol[Motor_PCB_Y];


	//accAll[0] = accAll[1] = model.dAcc;
	//decAll[0] = decAll[1] = model.dAcc;
	//AxmLineMove(lCoordinate, posAll, velAll[0], accAll[0], decAll[0]);
	//===================================================================================================================================
	//동작 5
	//우측상단 커브
	CircleSpeed = model.dCircleSpeed * sysData.fMotorResol[axisAll[0]];
	dMidPos[0] = model.dCircleRadiusCenterOffsetX[1] * 10000;
	dMidPos[1] = model.dCircleRadiusCenterOffsetY[1] * 10000;
	dEndPos[0] = model.dCircleRadiusEndOffsetX[1] * 10000;
	dEndPos[1] = model.dCircleRadiusEndOffsetY[1] * 10000; 
	MOTOR_DIR = DIR_CCW;
	AxmCircleCenterMove(lCoordinate, axisAll, dMidPos, dEndPos, CircleSpeed, accAll[0], decAll[0], MOTOR_DIR);
	//===================================================================================================================================
	//동작 6
	//우측상단 커브 후 직선
	/*axisAll[0] = Motor_PCB_X;
	axisAll[1] = Motor_PCB_Y; 
	posAll[0] = posAll[1] = 0.0;
	posAll[0] *= sysData.fMotorResol[Motor_PCB_X];

	posAll[1] = model.dDisLength[5] * -1;
	posAll[1] *= sysData.fMotorResol[Motor_PCB_Y];
	if (posAll[1]>0)					posAll[1] = (int)(posAll[1] + 0.5);

	AxmLineMove(lCoordinate, posAll, velAll[0], accAll[0], decAll[0]);*/

	//===================================================================================================================================
	//동작 7
	//상단 직선
	posAll[0] = posAll[1] = 0.0;

	posAll[0] = model.dDisLength[6] * 1;
	posAll[0] *= sysData.fMotorResol[Motor_PCB_X];
	//
	if (posAll[0]>0)					posAll[0] = (int)(posAll[0] + 0.5);
	posAll[1] *= sysData.fMotorResol[Motor_PCB_Y];

	AxmLineMove(lCoordinate, posAll, velAll[0], accAll[0], decAll[0]);
	//===================================================================================================================================
	//동작 8
	//좌측 상단 커브
	CircleSpeed = model.dCircleSpeed * sysData.fMotorResol[axisAll[0]];
	dMidPos[0] = model.dCircleRadiusCenterOffsetX[2] * 10000;
	dMidPos[1] = model.dCircleRadiusCenterOffsetY[2] * 10000;
	dEndPos[0] = model.dCircleRadiusEndOffsetX[2] * 10000;
	dEndPos[1] = model.dCircleRadiusEndOffsetY[2] * 10000;
	MOTOR_DIR = DIR_CCW;
	AxmCircleCenterMove(lCoordinate, axisAll, dMidPos, dEndPos, CircleSpeed, accAll[0], decAll[0], MOTOR_DIR);
	//===================================================================================================================================
	//동작 9
	//좌측 직선
	posAll[0] = posAll[1] = 0.0;
	posAll[0] *= sysData.fMotorResol[Motor_PCB_X];

	posAll[1] = model.dDisLength[7] * 1;
	posAll[1] *= sysData.fMotorResol[Motor_PCB_Y];
	if (posAll[1]>0)					posAll[1] = (int)(posAll[1] + 0.5);


	AxmLineMove(lCoordinate, posAll, velAll[0], accAll[0], decAll[0]);
	//===================================================================================================================================
	//동작 10
	//좌측상단 커브 전 직선
	//posAll[0] = posAll[1] = 0.0;

	//posAll[0] = model.dDisLength[6] * -1;
	//posAll[0] *= sysData.fMotorResol[Motor_PCB_X];
	////
	//if (posAll[0]>0)					posAll[0] = (int)(posAll[0] + 0.5);
	//posAll[1] *= sysData.fMotorResol[Motor_PCB_Y];

	//AxmLineMove(lCoordinate, posAll, velAll[0], accAll[0], decAll[0]);
	//===================================================================================================================================
	//동작 11
	//좌측 하단 커브
	CircleSpeed = model.dCircleSpeed * sysData.fMotorResol[axisAll[0]];
	dMidPos[0] = model.dCircleRadiusCenterOffsetX[3] * 10000;
	dMidPos[1] = model.dCircleRadiusCenterOffsetY[3] * 10000;
	dEndPos[0] = model.dCircleRadiusEndOffsetX[3] * 10000;
	dEndPos[1] = model.dCircleRadiusEndOffsetY[3] * 10000;
	MOTOR_DIR = DIR_CCW;
	AxmCircleCenterMove(lCoordinate, axisAll, dMidPos, dEndPos, CircleSpeed, accAll[0], decAll[0], MOTOR_DIR);
	//===================================================================================================================================
	//동작 12
	//좌측상단 커브 후 직선
	//도포 끊어야돼서 주석처리함 
	/*posAll[0] = posAll[1] = 0.0;
	posAll[0] *= sysData.fMotorResol[Motor_PCB_X];

	posAll[1] = model.dDisLength[7] * 1;
	posAll[1] *= sysData.fMotorResol[Motor_PCB_Y];
	if (posAll[1]>0)					posAll[1] = (int)(posAll[1] + 0.5);


	AxmLineMove(lCoordinate, posAll, velAll[0], accAll[0], decAll[0]);*/ 


	//===================================================================================================================================
	//
	AxmContiEndNode(lCoordinate);
	// 상대위치 구동시작.
	AxmContiSetAbsRelMode(lCoordinate, 1);
	// 연속보간구동 시작.
	AxmContiStart(lCoordinate, 0, 0);

	 
	Sleep(10);
	return true;
}

bool CAxlMotorSet::Straight_Dispense_MoveAxis(int axis, bool AbSFlag, double dPos, double dVel, float iAcc)
{	// abs 1:absolute, 0:increment\

	if (GetAmpFault(axis))
	{
		m_bOrgFlag[axis] = false;
		sLangChange.LoadStringA(IDS_STRING1453);
		LogSave(sLangChange);		//"AMP Alarm 발생. MoveAxis 동작 실패."
		return false;
	}

	if (!GetAmpEnable(axis))
	{
		m_bOrgFlag[axis] = false;

		CString tmpStr;
		sLangChange.LoadStringA(IDS_STRING1226);
		tmpStr.Format(_T("[%s] ") + sLangChange, MotorName[axis]);
		errMsg2(Task.AutoFlag, tmpStr);
		return false;
	}

	if (AbSFlag == ABS)
	{
		double curPos = 0.0;

		if (axis == Motor_Lens_Xt || axis == Motor_PCB_Xt || axis == Motor_PCB_Yt)
			curPos = GetCommandPos(axis);	//GetCommandPos(axis);
		else
			curPos = GetEncoderPos(axis);	//GetCommandPos(axis);

		if (fabs(curPos - dPos) < 0.0001)
		{
			return true;
		}

		if (m_bOrgFlag[axis] == false)
		{
			TCHAR	motorMSG[256];
			sTempLang.LoadStringA(IDS_STRING367);
			sLangChange.Format(sTempLang, axis + 1);
			wsprintf(motorMSG, sLangChange);
			return false;
		}
	}
	else if (AbSFlag == REL)
	{
		if (axis == Motor_Lens_Xt || axis == Motor_PCB_Xt || axis == Motor_PCB_Yt)
			dPos += GetCommandPos(axis);
		else
			dPos += GetEncoderPos(axis);	//GetCommandPos(axis);
	}

	dPos *= sysData.fMotorResol[axis];
	if (dPos>0)					dPos = (int)(dPos + 0.5);

	long   axisAll[MAX_MOTOR_NO] = { 0, };
	double posAll[MAX_MOTOR_NO] = { 0, };
	double velAll[MAX_MOTOR_NO] = { 0, };
	double accAll[MAX_MOTOR_NO] = { 0, };
	double decAll[MAX_MOTOR_NO] = { 0, };

	axisAll[0] = axis;
	posAll[0] = dPos;
	velAll[0] = dVel * sysData.fMotorResol[axis];
	accAll[0] = model.dAcc; //! 가속 가속도
	decAll[0] = model.dAcc;

	//! 여러 개의 축에 대해서 현재의 위치에서 지정한 거리만큼 이동을 동시에 시작한다. 
	//! 이 함수를 사용하면 여러 개의 축이 동시에 작업을 시작한다. 
	//! 이 함수는 여러 축이 동기를 맞추어 작업을 시작해야 하는 경우에 사용한다. 
	//! 펄스 출력이 시작되는 시점에서 함수를 벗어난다.
	//AxmMoveStartMultiPos(1, axisAll, posAll, velAll, accAll, decAll);
	AxmMoveStartPos(axis, dPos, velAll[0], accAll[0], decAll[0]);
	Sleep(10);
	return true;
}