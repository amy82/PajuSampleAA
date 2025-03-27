#include "StdAfx.h"
#include "LogThread.h"
#include "AA BonderDlg.h"
#include "GlobalDeclare.h"

CLogThread::CLogThread(void)
{
	nCount = 0;
	nUnit = 0;
}


CLogThread::~CLogThread(void)
{
}


//-----------------------------------------------------------------------------
//
//	스레드 생성자
//
//-----------------------------------------------------------------------------
void CLogThread::ThreadConstructor()
{

}

//-----------------------------------------------------------------------------
//
//	스레드 소멸자
//
//-----------------------------------------------------------------------------
void CLogThread::ThreadDestructor()
{
	//g_clLogQueue.RemoveAll();
}

//-----------------------------------------------------------------------------
//
//	스레드 콜백
//
//-----------------------------------------------------------------------------
void CLogThread::ThreadCallBack()
{
	// 로그 처리
	this->ProcessLog();
}


//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CLogThread::CreateLogFolder(CString strLog)
{
	/*TCHAR szPath[SIZE_OF_1K];
	SYSTEMTIME stSysTime;
	CFileFind clFinder;
	int i;

	GetLocalTime(&stSysTime);

	if (clFinder.FindFile(BASE_LOG_PATH) == FALSE)
		CreateDirectory(BASE_LOG_PATH, NULL);

	for(i = 0; i < MAX_UNIT_COUNT; i++)
	{
		_stprintf_s(szPath, SIZE_OF_1K, _T("%s"), BASE_LOG_PATH);
		if (clFinder.FindFile(szPath) == FALSE)
			CreateDirectory(szPath, NULL);

		_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Step"), BASE_LOG_PATH);
		if (clFinder.FindFile(szPath) == FALSE)
			CreateDirectory(szPath, NULL);

		_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Step\\%04d%02d"), BASE_LOG_PATH,  stSysTime.wYear, stSysTime.wMonth);
		if (clFinder.FindFile(szPath) == FALSE)
			CreateDirectory(szPath, NULL);		
	}*/
	SYSTEMTIME time;
	::GetLocalTime(&time);

	FILE *out;

	CFileFind finder;
	BOOL IsFind;
	CString FolderName;

	FolderName.Format("%s\\%s\\%04d%02d\\%02d", BASE_LOG_DIR, model.mCurModelName, time.wYear, time.wMonth, time.wDay);
	IsFind = finder.FindFile(FolderName);
	if (!IsFind)
	{
		FolderName.Format("%s", BASE_DIR);
		IsFind = finder.FindFile(FolderName);
		if (!IsFind)
		{
			CreateDirectory(FolderName, NULL);
		}

		FolderName.Format("%s", BASE_LOG_DIR);
		IsFind = finder.FindFile(FolderName);
		if (!IsFind)
		{
			CreateDirectory(FolderName, NULL);
		}

		FolderName.Format("%s\\%s", BASE_LOG_DIR, model.mCurModelName);
		IsFind = finder.FindFile(FolderName);
		if (!IsFind)
		{
			CreateDirectory(FolderName, NULL);
		}

		FolderName.Format("%s\\%s\\%04d%02d", BASE_LOG_DIR, model.mCurModelName, time.wYear, time.wMonth);
		IsFind = finder.FindFile(FolderName);
		if (!IsFind)
		{
			CreateDirectory(FolderName, NULL);
		}

		FolderName.Format("%s\\%s\\%04d%02d\\%02d", BASE_LOG_DIR, model.mCurModelName, time.wYear, time.wMonth, time.wDay);
		IsFind = finder.FindFile(FolderName);
		if (!IsFind)
		{
			CreateDirectory(FolderName, NULL);
		}
	}
	finder.Close();

	/*char fileName[1000];
	wsprintf(fileName, "%s\\%04d%02d%02d_LogDataAA.txt", FolderName, time.wYear, time.wMonth, time.wDay);

	if (!fopen_s(&out, fileName, "a"))
	{
		fprintf_s(out, "%s\n", (LPTSTR)(LPCTSTR)strLog);
		fclose(out);
	}*/

	TCHAR m_szModel[SIZE_OF_100BYTE];
#if (____MACHINE_NAME == MODEL_OHC100)
	_stprintf_s(m_szModel, SIZE_OF_100BYTE, _T("100"));
#else
	_stprintf_s(m_szModel, SIZE_OF_100BYTE, _T("150"));
#endif

	TCHAR szFilePath[SIZE_OF_1K];

	//_stprintf_s(szFilePath, SIZE_OF_1K, _T("%s\\%04d%02d%02d%02d_LogData_%s.txt"), szPath, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, stSysTime.wHour, m_szModel);
	_stprintf_s(szFilePath, SIZE_OF_1K, _T("%s\\%04d%02d%02d_LogData_%s.txt"), FolderName, time.wYear, time.wMonth, time.wDay, model.mCurModelName);
	logFile.open(szFilePath, std::ios::out | std::ios::app);
	if (!logFile.is_open())
	{
		throw std::runtime_error("Failed to open log file");
	}
	else
	{
		logFile << strLog << std::endl;
	}
	logFile.close();
}

void CLogThread::Log(const std::string& message)
{
	{
		std::lock_guard<std::mutex> lock(queueMutex);
		logQueue.push(message);
	}
	logCondition.notify_one();
}

void CLogThread::StopLogging()
{
	std::lock_guard<std::mutex> lock(queueMutex);
	isLogging = false;

	logCondition.notify_all();
	//if (logThread.joinable())
	//{
		//logThread.join();
	//}
}
//-----------------------------------------------------------------------------
//
//	로그 처리
//
//-----------------------------------------------------------------------------
void CLogThread::ProcessLog()
{	
	int i, j;
	std::unique_lock<std::mutex> lock(queueMutex);
	logCondition.wait(lock, [this] 
	{ 
		return !logQueue.empty() || !isLogging;
	});

	if (!isLogging && logQueue.empty())
	{
		return;
	}

	while (!logQueue.empty())
	{
		std::string logMessage = logQueue.front();
		logQueue.pop();
		lock.unlock();

		// 로그 출력 (콘솔에 출력, 파일에 기록 등)
		//std::cout << logMessage << std::endl;

		nCount = theApp.MainDlg->m_listLog.GetCount();
		if (nCount > 500)
		{
			theApp.MainDlg->m_listLog.DeleteString(0);
			//theApp.MainDlg->m_listLog.ResetContent();
		}
		nCount = theApp.MainDlg->m_listLog.AddString(logMessage.c_str());
		theApp.MainDlg->m_listLog.SetCurSel(nCount);

		CreateLogFolder(logMessage.c_str());
		lock.lock();
	}
	return;
	
}
