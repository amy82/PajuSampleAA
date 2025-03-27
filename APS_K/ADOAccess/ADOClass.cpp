// ADOClass.cpp: implementation of the CADOClass class.
//
//////////////////////////////////////////////////////////////////////
// Includes

#include "stdafx.h"
#include "ADOClass.h"
#include <ATLCONV.H>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CADOClass::CADOClass()
{
	// 초기화
	m_pConnection = NULL;
	m_pCommand = NULL;
	m_pRs = NULL;
	bADOConnect = false;
	::CoInitialize(NULL);

}

CADOClass::~CADOClass()
{
 	::CoUninitialize();
}


BOOL CADOClass::func_AA_DBConnect()
{
	CString strPath="";
	CString strConnect="";
	strPath.Format("%s\\%s\\AABondingRecord", AA_MODEL_LOAD_DIR, model.mCurModelName);
	

	//strConnect.Format(_T("Driver={Microsoft Access Driver (*.mdb)};Dbq=%s.mdb;DefaultDir=;Uid=Admin;Pwd=;"), strPath);
#ifdef  _M_X64
	strConnect.Format("Driver={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=%s.mdb;DefaultDir=;Uid=Admin;Pwd=;", strPath);
#else 
	strConnect.Format(_T("Driver={Microsoft Access Driver (*.mdb)};Dbq=%s.mdb;DefaultDir=;Uid=Admin;Pwd=;"), strPath);	
#endif
	
	Sleep(100);
	if (FALSE == Connect((CStringA)strConnect))
	{
		return false;
	}
	Sleep(100);

	bADOConnect = true;
	return true;
}

void CADOClass::func_AA_DBDisConnect()
{
	bADOConnect = false;
	DisConnect();
}



/*
// 1. AA 제품 생산간, Laser 내부/외부 변위 측정 결과값 저장 
// 2. 내부/외부 Laser 변위 측정 편차 저장(Tx, Ty)
// 3. Lans Aling Data(X/Y/T), PCB Holder Align Data(X/Y/T) 보정량 저장
// 4. Lans/PCB Holder간 보정량 편차 저장(X/Y/T)
*/
bool CADOClass::func_AATaskToRecordID(CString sUseModel, CString sBarcodeID)
{
	CString sDBQry = "";
	CString sCTime = _T("");
	SYSTEMTIME m_TIME;
	GetLocalTime(&m_TIME);
	sCTime.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"), m_TIME.wYear, m_TIME.wMonth, m_TIME.wDay, m_TIME.wHour, m_TIME.wMinute, m_TIME.wSecond);

	if( bADOConnect == false){
		if( !func_AA_DBConnect() ) 
			return false;
	}

	CString sEmpty = "";
	if( sBarcodeID == sEmpty || sBarcodeID == "EMPTY" )
	{//바코드 정보가 없으면 저장 안하고 넘어감.
		//func_AA_DBDisConnect();
		return true;
	}

	m_csAdoProcPtr.Lock();
	//! 바코드 정보가 있는지 먼저 읽기
	sDBQry.Format(_T("SELECT * FROM AABonding WHERE ([_BARCODE_ID] = '%s')"),	sBarcodeID);
	//sDBQry.Format(_T("SELECT * FROM AABonding WHERE ([_BARCODE_ID] LIKE '%%%s%%')"),	sBarcodeID);
	ExecuteQryRs(sDBQry);
	
	

	if( IsEOF() ) 		//내역 없음
	{//!신규 레코드 추가
		if(sysData.m_iProductComp==1)
		{
			m_csAdoProcPtr.Unlock();
			return false;
		}
		sDBQry.Format(_T("INSERT INTO AABonding([_TIME], [_USEMODEL], [_BARCODE_ID]) VALUES('%s', '%s', '%s')"), sCTime, sUseModel, sBarcodeID);
		if( ExecuteQryRs(sDBQry) == FALSE)
		{
			m_csAdoProcPtr.Unlock();
			return false;
		}
	}
	else
	{//! 레코드 갱신([_TIME], 모델)
		sDBQry.Format("UPDATE AABonding SET [_TIME] = '%s',  [_USEMODEL] = '%s' WHERE [_BARCODE_ID] = '%s' ",
			sCTime, sUseModel, sBarcodeID);

		if( ExecuteQryRs(sDBQry) == FALSE)
		{
			//func_AA_DBDisConnect();
			m_csAdoProcPtr.Unlock();
			return false;
		}
		
	}

	//func_AA_DBDisConnect();
	m_csAdoProcPtr.Unlock();

	return true;
}

bool CADOClass::func_AATaskToRecordLaser(CString sBarcodeID, double dOffsetX, double dOffsetY, double dValue[8])
{
	CString sDBQry = "";
	if( bADOConnect == false){
		if( !func_AA_DBConnect() ) return false;
	}

	CString sEmpty = "";
	if( sBarcodeID == sEmpty || sBarcodeID == "EMPTY" )
	{//바코드 정보가 없으면 저장 안하고 넘어감.
		//func_AA_DBDisConnect();
		return true;
	}

	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	sDBQry.Format("UPDATE AABonding "
		"SET [_USEMODEL] = '%s', [LaserTiltTX] = %f,  [LaserTiltTY] = %f, [LaserIn1] = %f, [LaserIn2] = %f, [LaserIn3] = %f, [LaserIn4] = %f,"
		"[LaserOut1] = %f, [LaserOut2] = %f, [LaserOut3] = %f, [LaserOut4]  = %f "
		"WHERE [_BARCODE_ID] = '%s'",
		modelList.curModelName,
		dOffsetX, dOffsetY,
		dValue[0], dValue[1], dValue[2], dValue[3],
		dValue[4], dValue[5], dValue[6], dValue[7],
		sBarcodeID );
	
	m_csAdoProcPtr.Lock();
	
	if( ExecuteQryRs(sDBQry) == FALSE)
	{
		//func_AA_DBDisConnect();
		m_csAdoProcPtr.Unlock();
		return false;
	}

	//func_AA_DBDisConnect();
	m_csAdoProcPtr.Unlock();
	return true;
}

bool CADOClass::func_AATaskToRecordAlign(CString sBarcodeID, double dOffsetX, double dOffsetY, double dOffsetT)
{
	CString sDBQry = "";
	if( bADOConnect == false){
		if( !func_AA_DBConnect() ) return false;
	}

	CString sEmpty = "";
	if( sBarcodeID == sEmpty || sBarcodeID == "EMPTY" )
	{//바코드 정보가 없으면 저장 안하고 넘어감.
		//func_AA_DBDisConnect();
		return true;
	}

	sDBQry.Format("UPDATE AABonding "
		"SET [AlignOffsetX] = %f,  [AlignOffsetY] = %f, [AlignOffsetT] = %f "
		"WHERE [_BARCODE_ID] = '%s'",
		dOffsetX, dOffsetY, dOffsetT, 
		sBarcodeID );

	m_csAdoProcPtr.Lock();
	
	if( ExecuteQryRs(sDBQry) == FALSE)
	{
		//func_AA_DBDisConnect();
		m_csAdoProcPtr.Unlock();
		return false;
	}
	//func_AA_DBDisConnect();
	m_csAdoProcPtr.Unlock();
	return true;
}


bool CADOClass::func_Set_DeleteRecord(int nDeleteDay)
{
	CString sDBQry = "";
	//## 현재날짜 얻기
	CString strCTime = _T("");
	CTime timeValue;	//현재 시간을 받을 변수
	timeValue = CTime::GetTickCount();
	CTimeSpan timeMinus(nDeleteDay, 0, 0, 0);			//삭제 주기.
	timeValue = timeValue - timeMinus;

	if( bADOConnect == false){
		if( !func_AA_DBConnect() ) return false;
	}

	strCTime.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"), 
		timeValue.GetYear(), timeValue.GetMonth(), timeValue.GetDay(),
		timeValue.GetHour(), timeValue.GetMinute(), timeValue.GetSecond());

	sDBQry.Format(_T("DELETE FROM AABonding WHERE ([_TIME] <= #%s#)"), strCTime);

	m_csAdoProcPtr.Lock();
	
	if( ExecuteQryRs(sDBQry) == FALSE)
	{
		//func_AA_DBDisConnect();
		m_csAdoProcPtr.Unlock();
		return false;
	}

	//func_AA_DBDisConnect();
	m_csAdoProcPtr.Unlock();
	return true;
}


/* AABondingRecord.mdb 파일 Search
// 바코드 ID(키)로 관련 Data Reading
// => Find 후 생산 이력 있을 경우 True, 없으면 False
// => 내역은 CTask로 Data Push
*/
bool CADOClass::func_Get_RecordData(CString sBarcodeID)
{
	CString sDBQry = "";
	//CTime		timeVal;
	//GetRsDataTime(_T("[_TIME]"), timeVal);

	if( bADOConnect == false){
		if( !func_AA_DBConnect() ) return false;
	}

	//쿼리 생성
	sDBQry.Format(_T("SELECT * FROM AABonding WHERE ([_BARCODE_ID] = '%s')"),	sBarcodeID);
	//sDBQry.Format(_T("SELECT * FROM AABonding WHERE ([_BARCODE_ID] LIKE '%%%s%%')"),	sBarcodeID);
	
	m_csAdoProcPtr.Lock();

	ExecuteQryRs(sDBQry);

	if( IsEOF() ){
		//func_AA_DBDisConnect();
		m_csAdoProcPtr.Unlock();
		return false;		//내역 없음
	}


	GetRsDataDouble("LaserTiltTX",  adoRegist.dOffset_TiltTx);
	GetRsDataDouble("LaserTiltTY",  adoRegist.dOffset_TiltTy);
	GetRsDataDouble("LaserIn1",		adoRegist.dLaserIn[0]);
	GetRsDataDouble("LaserIn2",		adoRegist.dLaserIn[1]);
	GetRsDataDouble("LaserIn3",		adoRegist.dLaserIn[2]);
	GetRsDataDouble("LaserIn4",		adoRegist.dLaserIn[3]);
	GetRsDataDouble("LaserOut1",	adoRegist.dLaserOut[0]);
	GetRsDataDouble("LaserOut2",	adoRegist.dLaserOut[1]);
	GetRsDataDouble("LaserOut3",	adoRegist.dLaserOut[2]);
	GetRsDataDouble("LaserOut4",	adoRegist.dLaserOut[3]);

	GetRsDataDouble("AlignOffsetX",  adoRegist.dOffset_Align[0]);
	GetRsDataDouble("AlignOffsetY",  adoRegist.dOffset_Align[1]);
	GetRsDataDouble("AlignOffsetT",  adoRegist.dOffset_Align[2]);
	GetRsDataDouble("PCBX",			 adoRegist.dPCBMotor[0]);
	GetRsDataDouble("PCBY",			 adoRegist.dPCBMotor[1]);
	GetRsDataDouble("PCBTH",		 adoRegist.dPCBMotor[2]);
	GetRsDataDouble("PCBTX",		 adoRegist.dPCBMotor[3]);
	GetRsDataDouble("PCBTY",		 adoRegist.dPCBMotor[4]);
	GetRsDataDouble("PCBZ",			 adoRegist.dPCBMotor[5]);
	//GetRsDataDouble("AlingLensX",  adoRegist.dLans_Align[0]);
	//GetRsDataDouble("AlingLensY",  adoRegist.dLans_Align[1]);
	//GetRsDataDouble("AlingLensT",  adoRegist.dLans_Align[2]);
	//GetRsDataDouble("AlingHolderX",  adoRegist.dPCBHolder_Align[0]);
	//GetRsDataDouble("AlingHolderY",  adoRegist.dPCBHolder_Align[1]);
	//GetRsDataDouble("AlingHolderT",  adoRegist.dPCBHolder_Align[2]);


	//func_AA_DBDisConnect();
	m_csAdoProcPtr.Unlock();
	return true;
}

//*******************************************************************
//              
//  FUNCTION:   - CADOClass::Connect
//              
//  RETURNS:    - bool (실행여부)
//              
//  PARAMETERS: - LPCSTR lpszProvider(연결할 서버 정보), ExecuteOptionEnum emOption(옵션)
//              
//  COMMENTS:   - 데이터 베이스를 열어준다.
//              
//              
//*******************************************************************

bool CADOClass::Connect(LPCSTR lpszProvider, ExecuteOptionEnum emOption)
{

//	TRACE0( "ADOClass::Connect() entered\n" );

	if(m_pConnection != NULL && m_pConnection->GetState() == adStateOpen)
		return FALSE;

	try
	{
		HRESULT hr = m_pConnection.CreateInstance(__uuidof(Connection));
		m_pConnection->ConnectionTimeout = 5;
		_bstr_t btProvider=(_bstr_t)lpszProvider;
		_bstr_t btEmpty=(_bstr_t)"";
		
		m_pConnection->Open(btProvider,btEmpty,btEmpty,emOption);
		
	}
	catch( _com_error &e)
	{
		DumpError(e);
		return FALSE;
	}
	
	return TRUE;
}




//*******************************************************************
//              
//  FUNCTION:   - CADOClass::ExecuteQryCmd
//              
//  RETURNS:    - bool(실행여부)
//              
//  PARAMETERS: - LPCSTR lpszQry(쿼리문), lop(Option) 
//              
//  COMMENTS:   - Command 객체를 이용하여 Select문에 대한 레코드셋을 뽑아낸다. 단지 RS만 만들어 놓는다.
//				  GetRsDataChar or GetRsDataLong를 써서 RS 데이터를 뽑아 쓰세용~~
//              
//              
//*******************************************************************

bool CADOClass::ExecuteQryCmd(LPCSTR lpszQry, long lop)
{

////	TRACE0( "ADOClass::ExecuteQryCmd entered\n" );
	
	if( m_pConnection == NULL || m_pConnection->GetState()!=adStateOpen)
		return FALSE;

	if( m_pRs != NULL && m_pRs->GetState()!=adStateClosed)
	{
		m_pRs->Close();
		m_pRs.Release();
		m_pRs = NULL;
	}

	try
	{
		m_pCommand.CreateInstance(__uuidof( Command )); 
		m_pCommand->ActiveConnection = m_pConnection; 
		m_pCommand->CommandType = adCmdStoredProc; 

		m_pCommand->CommandText = _bstr_t(lpszQry); 

		_variant_t vNull; 
		vNull.vt = VT_ERROR; 
		vNull.scode = DISP_E_PARAMNOTFOUND; 
		
		m_pRs = m_pCommand->Execute(&vNull, &vNull, lop); 

	}
	catch(_com_error &e)
	{

		DumpError(e);
		return FALSE;
	}

	return TRUE;


}


//*******************************************************************
//              
//  FUNCTION:   - CADOClass::ExecuteQryRs
//              
//  RETURNS:    - bool(실행여부)
//              
//  PARAMETERS: - LPCSTR lpszQry(쿼리문),emCurType(CursorType), emLockType(LockType), lop(Option) 
//              
//  COMMENTS:   - RecordSet 객체를 이용하여 Select문에 대한 레코드셋을 뽑아낸다. 단지 RS만 만들어 놓는다.
//				  GetRsDataChar or GetRsDataLong를 써서 RS 데이터를 뽑아 쓰세용~~
//              
//*******************************************************************

bool CADOClass::ExecuteQryRs(CString lpszQry, CursorTypeEnum emCurType, LockTypeEnum emLockType, long lop)
{

//	TRACE0( "ADOClass::ExecuteQry entered\n" );
	
	if( m_pConnection == NULL || m_pConnection->GetState()!=adStateOpen)
		return FALSE;

	
	// 레코드셋이 이미 열려 있다면 초기화 시켜준다.
	if( m_pRs != NULL && m_pRs->GetState()!=adStateClosed)
	{
		m_pRs->Close();
		m_pRs.Release();
		m_pRs = NULL;
	}

	m_pRs.CreateInstance(__uuidof(Recordset));
	//커서를 adUseClient로 해줘야 lastRS를 사용 가능함
	m_pRs->CursorLocation = adUseClient;

	try
	{
		_bstr_t btQry=(_bstr_t)lpszQry;
        m_pRs->Open(btQry, _variant_t((IDispatch *) m_pConnection), emCurType, emLockType, lop);

	}
	catch(_com_error &e)
	{

		DumpError(e);
		return FALSE;

	}

	return TRUE;

}






//*******************************************************************
//              
//  FUNCTION:   - CADOClass::InUpDelQryCmd
//              
//  RETURNS:    - bool(실행여부)
//              
//  PARAMETERS: - LPCSTR lpszQry(쿼리문)
//              
//  COMMENTS:   - Command 객체를 이용하여 Insert, Update, Delete문에 대한 쿼리를 실행한다.
//              
//              
//*******************************************************************


bool CADOClass::InUpDelQryCmd(LPCSTR lpszQry)
{
//	TRACE0( "ADOClass::InUpDelQryCmd entered\n" );
	
	if( m_pConnection == NULL || m_pConnection->GetState()!=adStateOpen)
		return FALSE;


	try
	{
		m_pCommand.CreateInstance(__uuidof( Command )); 
		m_pCommand->ActiveConnection = m_pConnection; 
		m_pCommand->CommandType = adCmdStoredProc; 

		m_pCommand->CommandText = _bstr_t(lpszQry); 

		_variant_t vNull; 
		vNull.vt = VT_ERROR; 
		vNull.scode = DISP_E_PARAMNOTFOUND; 
		
		m_pCommand->Execute(&vNull, &vNull, adCmdUnknown); 

	}
	catch(_com_error &e)
	{

		DumpError(e);
		return FALSE;

	}

	return TRUE;

}


//*******************************************************************
//              
//  FUNCTION:   - CADOClass::InUpDelQryConn
//              
//  RETURNS:    - bool(실행여부)
//              
//  PARAMETERS: - LPCSTR lpszQry(쿼리문)
//              
//  COMMENTS:   - RecordSet 객체를 이용하여 Insert, Update, Delete문에 대한 쿼리를 실행한다.
//              
//              
//*******************************************************************


bool CADOClass::InUpDelQryConn(LPCSTR lpszQry)
{
//	TRACE0( "ADOClass::InUpDelQry entered\n" );
	
	if(m_pConnection == NULL || m_pConnection->GetState()!=adStateOpen )
		return FALSE;


	try 
	{
		_bstr_t btQry=(_bstr_t)lpszQry;
		m_pConnection->Execute(btQry,NULL,adOptionUnspecified);
	}
	catch(_com_error &e)
	{
		DumpError(e);
		return FALSE;
	}
		
	return TRUE;
}






//*******************************************************************
//              
//  FUNCTION:   - CADOClass::DisConnect
//              
//  RETURNS:    - bool (실행여부)
//              
//  PARAMETERS: - 없음
//              
//  COMMENTS:   - m_pConnection과 m_pCommand를 닫아준다.
//              
//              
//*******************************************************************

bool CADOClass::DisConnect()
{
//	TRACE0( "ADOClass::DisConnect entered\n" );

	try{

		//연결을 닫을 때는 m_pConnection보다 m_pRs를 항상 먼저 닫아준다...... 그래야 에러 안뜬다.
		if(m_pRs != NULL && m_pRs->GetState()!=adStateClosed)
		{
			m_pRs->Close();
			m_pRs.Release();
			m_pRs = NULL;
		}		
		
		
		if(m_pConnection != NULL && m_pConnection->GetState()!=adStateClosed )
		{
			m_pConnection->Close();
			m_pConnection.Release();
			m_pConnection = NULL;
		}


	}
	catch(_com_error &e)
	{
		DumpError(e);
		return FALSE;
	}

	bADOConnect = false;
	return TRUE;

}







//*******************************************************************
//              
//  FUNCTION:   - CADOClass::DumpError
//              
//  RETURNS:    - void
//              
//  PARAMETERS: - const _com_error &e
//              
//  COMMENTS:   - ADO 클래스 안에서 catch문에 빠졌을 경우 보고한다. (나중에는 파일로 쓰자)
//              
//              
//*******************************************************************

void CADOClass::DumpError(const _com_error &e) const
{
	_bstr_t btSource(e.Source());
	_bstr_t btDescription(e.Description());
	CString strMsg;
	strMsg.Format(_T("DATE= %s\n %08lx= %s\n Source= %s\n Description= %s")
				,CTime::GetCurrentTime().Format("%Y-%m-%d %H:%M:%S")
				,e.Error(),e.ErrorMessage()
				,(LPCSTR)btSource
				,(LPCSTR)btDescription);


#ifdef _DEBUG
	// 로그에 띄워주기 위해...
	//AfxMessageBox(strMsg);
#endif
	CStdioFile sdFile;
	if( !sdFile.Open(_T("C:\\EZnetManagerDump.txt"), CFile::shareDenyNone | CFile::modeWrite | CFile::typeText) )
	{
		if( !sdFile.Open(_T("C:\\EZnetManagerDump.txt"), CFile::shareDenyNone | CFile::modeCreate | CFile::modeWrite | CFile::typeText) )
		{
//			TRACE("C:\\EZnetManagerDump.txt Create Fail\n");
			return;
		}
	}

	sdFile.SeekToEnd();
	sdFile.WriteString(strMsg);
	sdFile.WriteString(_T("\n\n"));
	sdFile.Close();


}


// =================================================
// RecordSet 마지막인지 여부 확인
// =================================================
BOOL CADOClass::IsEOF()
{
	if (NULL == m_pRs)
	{
		return TRUE;
	}
	return (m_pRs->adoEOF);
}



// =================================================
// Clsoe Recordset
// =================================================
BOOL CADOClass::CloseRS()
{

	try
	{
		if(m_pRs != NULL && m_pRs->GetState()!=adStateClosed)
		{
			m_pRs->Close();
			m_pRs.Release();
			m_pRs = NULL;
		}						
	}
	catch(_com_error &e)
	{
		DumpError(e);
		return FALSE;
	}


	return TRUE;
}

// =================================================
// Recordset First로 이동
// =================================================
void CADOClass::FirstRS()
{

	if( m_pRs != NULL )
	{
		m_pRs->MoveFirst();
	}

}

// =================================================
// Recordset Next로 이동
// =================================================
void CADOClass::NextRS()
{
	if( m_pRs != NULL )
	{
		m_pRs->MoveNext();
	}

}

// =================================================
// Recordset Prev로 이동
// =================================================
void CADOClass::PrevRS()
{
	if( m_pRs != NULL )
	{
		m_pRs->MovePrevious();
	}
}


// =================================================
// Recordset Last로 이동
// =================================================
void CADOClass::LastRS()
{
	if( m_pRs != NULL )
	{
		m_pRs->MoveLast();
	}

}


// =================================================
// LONG형 데이터 반환(RS)
// =================================================
BOOL CADOClass::GetRsDataLong( LPCTSTR lpszColumn, LONG& lValue )
{
	_variant_t var;

	try
	{
		if( m_pRs != NULL)
		{
			var = m_pRs->GetFields()->GetItem(lpszColumn)->GetValue();

			if( var.vt == VT_NULL )
				lValue = 0L;
			else
				lValue = var.ulVal;
		}

	}
	catch(_com_error &e)
	{
		DumpError(e);
		return FALSE;
	}

	return TRUE;

}


// =================================================
// BOOL형 데이터 반환(RS)
// =================================================
BOOL CADOClass::GetRsDataBool(LPCTSTR lpszColumn, BOOL &bValue)
{
	_variant_t var;

	try
	{
		if( m_pRs != NULL)
		{
			var = m_pRs->GetFields()->GetItem(lpszColumn)->GetValue();

			if( var.vt == VT_NULL )
				bValue = -1;
			else if (var.boolVal == -1)
			{
				bValue = TRUE;
			}
			else
			{
				bValue = FALSE;
			}
		}

	}
	catch(_com_error &e)
	{
		DumpError(e);
		return FALSE;
	}

	return TRUE;
}
// =================================================
// INT형 데이터 반환(RS)
// =================================================
BOOL CADOClass::GetRsDataInt(LPCTSTR lpszColumn, INT &nValue)
{
	_variant_t var;

	try
	{
		if( m_pRs != NULL)
		{
			var = m_pRs->GetFields()->GetItem(lpszColumn)->GetValue();

			if( var.vt == VT_NULL )
				nValue = 0;
			else
				nValue = var.intVal;
		}

	}
	catch(_com_error &e)
	{
		DumpError(e);
		return FALSE;
	}

	return TRUE;
}

// =================================================
// 실수형 데이터 반환(RS) - Double
// =================================================
BOOL CADOClass::GetRsDataDouble(LPCTSTR lpszColumn, double& dValue)
{
	_variant_t var;

	try
	{
		if( m_pRs != NULL)
		{

			var = m_pRs->GetFields()->GetItem(lpszColumn)->GetValue();
			if( var.vt == VT_NULL )
			{
				dValue = 0;
			}
			else
			{
				dValue = var.dblVal;
			}

		}
	}
	catch(_com_error &e)
	{
		DumpError(e);
		return FALSE;
	}

	return TRUE;
}

// =================================================
// 실수형 데이터 반환(RS) - float
// =================================================
BOOL CADOClass::GetRsDataFloat(LPCTSTR lpszColumn, float& fValue)
{
	_variant_t var;

	try
	{
		if( m_pRs != NULL)
		{

			var = m_pRs->GetFields()->GetItem(lpszColumn)->GetValue();
			if( var.vt == VT_NULL )
			{
				fValue = 0;
			}
			else
			{
				fValue = var.fltVal;
			}

		}
	}
	catch(_com_error &e)
	{
		DumpError(e);
		return FALSE;
	}

	return TRUE;
}
// =================================================
// 문자열 데이터 반환(RS) - CString
// =================================================
BOOL CADOClass::GetRsDataChar(LPCTSTR lpszColumn, CString& csValue)
{

	_variant_t var;

	try
	{
		if( m_pRs != NULL)
		{

			var = m_pRs->GetFields()->GetItem(lpszColumn)->GetValue();
			if( var.vt == VT_NULL )
			{
				csValue = "";
			}
			else
			{
				csValue = var.bstrVal;
			}

		}
	}
	catch(_com_error &e)
	{
		DumpError(e);
		return FALSE;
	}

	return TRUE;

}

BOOL CADOClass::GetRsDataTime(LPCTSTR lpszColumn, CTime &cTime)
{

	_variant_t var;

	SYSTEMTIME	SystemTime ;
	DATE		date;


	try
	{
		if( m_pRs != NULL)
		{
			var = m_pRs->GetFields()->GetItem(lpszColumn)->GetValue();
			if( var.vt == VT_NULL )
			{
				cTime = 0;
			}
			else
			{
				date = var.date;				
				if(VariantTimeToSystemTime(date, &SystemTime) == TRUE)
				{
					//CTime이 표현할수 있는 범위를 넘어서면
					if ((1970 > SystemTime.wYear) | (3000 < SystemTime.wYear))
					{
						cTime = 0;
					}
					else
					{
						CTime cDTime(SystemTime.wYear, SystemTime.wMonth, SystemTime.wDay,
							SystemTime.wHour, SystemTime.wMinute, SystemTime.wSecond );

						cTime = (CTime)cDTime;
					}
				}
			}
		}

	}
	catch(_com_error &e)
	{
		DumpError(e) ;
		return FALSE;
	}

	return TRUE;
}




// =================================================
// 문자열 데이터 반환(RS) - char*
// =================================================
BOOL CADOClass::GetRsDataChar(LPCTSTR lpszColumn, char *pszValue)
{
	_variant_t var;

	USES_CONVERSION;	// BSTR -> char을 위한 매크로를 쓰기 위해서 선언.


	try
	{
		if( m_pRs != NULL)
		{

			var = m_pRs->GetFields()->GetItem(lpszColumn)->GetValue();
			if( var.vt == VT_NULL )
			{
				strcpy_s( pszValue, 1, (LPCSTR)("") );
			}
			else
			{				
				int nLen = ::WideCharToMultiByte( CP_ACP, 0, var.bstrVal, -1, NULL, 0, NULL, NULL ); // get size.
				::WideCharToMultiByte( CP_ACP, 0, var.bstrVal, -1, pszValue, nLen, NULL, NULL );			
			}
		}
	}

	catch(_com_error &e)
	{
		DumpError(e);
		return FALSE;
	}
	
	return TRUE;
}

// 다음 레코드 목록을 불러오는 함수
int CADOClass::NextRecord(void)
{
	DWORD_PTR lngRec = 0;
	m_pRs = m_pRs->NextRecordset((VARIANT *)lngRec);
	return 0;
}

// 해당 칼럼으로 필터링하는 함수
int CADOClass::setFilter(_bstr_t strField, _bstr_t strFilter)
{
	m_pRs->Filter  = strField + " = '" + strFilter + "'";
	
	if (m_pRs->GetRecordCount() == 0)
		return 1;

	return 0;
}

// 레코드수를 리턴하는 함수
long CADOClass::GetRecordCount(void)
{
	return m_pRs->RecordCount;
}



bool CADOClass::func_AATaskToAAPcbMoter(CString sBarcodeID, double dPCBX, double dPCBY, double dPCBTh, double dPCBTx, double dPCBTy, double dPCBZ)
{
	CString sDBQry = "";
	if( bADOConnect == false){
		if( !func_AA_DBConnect() ) return false;
	}

	CString sEmpty = "";
	if( sBarcodeID == sEmpty || sBarcodeID == "EMPTY" )
	{//바코드 정보가 없으면 저장 안하고 넘어감.
		//func_AA_DBDisConnect();
		return true;
	}
	sDBQry.Format("UPDATE AABonding "
		"SET [PCBX] = %f,  [PCBY] = %f, [PCBTH] = %f, [PCBTX] = %f, [PCBTY] = %f, [PCBZ] = %f WHERE [_BARCODE_ID] = '%s'",
		dPCBX, dPCBY, dPCBTh, dPCBTx, dPCBTy, dPCBZ,
		sBarcodeID );


	m_csAdoProcPtr.Lock();
	
	if( ExecuteQryRs(sDBQry) == FALSE)
	{
		//func_AA_DBDisConnect();
		m_csAdoProcPtr.Unlock();
		return false;
	}
	//func_AA_DBDisConnect();
	m_csAdoProcPtr.Unlock();
	return true;
}