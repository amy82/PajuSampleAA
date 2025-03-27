  // ADOClass.h: interface for the CADOClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADOCLASS_H__3672C5FF_18F6_487D_B1D3_CBE7C810D401__INCLUDED_)
#define AFX_ADOCLASS_H__3672C5FF_18F6_487D_B1D3_CBE7C810D401__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CADOClass  
{
public:
	
	CADOClass();
	virtual ~CADOClass();

	strdefADO	adoRegist;

	CCriticalSection	m_csAdoProcPtr;	  //! DataBase 감시

	bool	bADOConnect;
	BOOL func_AA_DBConnect();			//DB 연결
	void func_AA_DBDisConnect();		//DB 연결 해제

	bool func_AATaskToRecordID(CString sUseModel, CString sBarcodeID);		//레코드 추가
	bool func_AATaskToRecordLaser(CString sBarcodeID, double dOffsetX, double dOffsetY, double dValue[8]);						//레코드 갱신 - Laser 변위 측정	
	bool func_AATaskToRecordAlign(CString sBarcodeID,  double dOffsetX, double dOffsetY, double dOffsetT);						//레코드 갱신 - Align (Lans, Holder간 Align 편차값)
	bool func_AATaskToAAPcbMoter(CString sBarcodeID, double dPCBX, double dPCBY, double dPCBTh, double dPCBTx, double dPCBTy, double dPCBZ);

	bool func_Get_RecordData(CString sBarcodeID);							//레코드 읽기 -> 바코드명으로.

	bool func_Set_DeleteRecord(int nDeleteDay);								//레코드 삭제 -> 일자.

	// -------------------------------------------------------------
	// RS에서 필요한 데이터 타입은 VARIANTARG를 참조하여 추가하세요
	// -------------------------------------------------------------

	// Record Getdata(int)
	BOOL GetRsDataInt(LPCTSTR lpszColumn, INT& nValue);

	// Record Getdata(CString)
	BOOL GetRsDataChar(LPCTSTR lpszColumn, CString& csValue);

	// Record Getdata(char*)
	BOOL GetRsDataChar(LPCTSTR lpszColumn, char* pszValue);

	// Record Getdata(long)
	BOOL GetRsDataLong(LPCTSTR lpszColumn, LONG& lValue);

	// Record GetdateTime(CTime)
	BOOL GetRsDataTime(LPCTSTR lpszColumn, CTime &cTime);

	// Record GetdateTime(BOOL)
	BOOL GetRsDataBool(LPCTSTR lpszColumn, BOOL &bValue);

	// Record Getdata(float)
	BOOL GetRsDataFloat(LPCTSTR lpszColumn, float& fValue);

	// Record Getdata(double)
	BOOL GetRsDataDouble(LPCTSTR lpszColumn, double& dValue);

	// -------------------------------------------------------------


	// RS EOF인지 여부
	BOOL IsEOF();
	
	// RS(Recordset) 마지막으로 이동
	void LastRS();

	// RS 이전으로 이동
	void PrevRS();

	// RS 다음으로 이동
	void NextRS();

	// RS 처음으로 이동
	void FirstRS();

	// Close 레코드 셋
	BOOL CloseRS();

	// 쿼리를 실행하여 레코드셋을 뽑아낸다.(Command 객체 이용) - 속도 빠름, 중복 쿼리 처리 안됨
	bool ExecuteQryCmd(LPCSTR lpszQry, long lop=adCmdUnknown);

	// 쿼리를 실행하여 레코드셋을 뽑아낸다.(RecordSet 객체 이용) - 속도 느림, 중복 쿼리 처리 가능
	bool ExecuteQryRs(CString lpszQry, CursorTypeEnum emCurType=adOpenStatic, LockTypeEnum emLockType=adLockReadOnly, long lop=adCmdUnknown);

	// 쿼리를 실행한다.(Insert, Update, Delete문 : Command객체 이용)
	bool InUpDelQryCmd(LPCSTR lpszQry);

	// 쿼리를 실행한다.(Insert, Update, Delete문 : Connection 객체 이용)
	bool InUpDelQryConn(LPCSTR lpszQry);

	// DB를 연결한다.(Open포함)
	bool Connect(LPCSTR lpszProvider, ExecuteOptionEnum emOption = adOptionUnspecified);

	// DB를 닫아준다(m_pConnection, m_pCommand)
	bool DisConnect();

	// 트랜잭션 처리
	LONG BeginTrans() const { return m_pConnection->BeginTrans();}
	HRESULT RollbackTrans() const { return m_pConnection->RollbackTrans();}
	HRESULT CommitTrans() const { return m_pConnection->CommitTrans();}

	// 다음 레코드 목록을 불러오는 함수
	int NextRecord(void);

	// 해당 칼럼으로 필터링하는 함수
	int setFilter(_bstr_t strField, _bstr_t strFilter);

	// 레코드수를 리턴하는 함수
	long GetRecordCount(void);

private:
	_RecordsetPtr m_pRs;
	_CommandPtr m_pCommand;
	_ConnectionPtr m_pConnection;

	// 에러 보고 함수(예외처리시)
	void DumpError(const _com_error &e) const;




};

#endif // !defined(AFX_ADOCLASS_H__3672C5FF_18F6_487D_B1D3_CBE7C810D401__INCLUDED_)
