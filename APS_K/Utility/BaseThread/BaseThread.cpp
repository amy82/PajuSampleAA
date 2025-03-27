// BaseThread.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BaseThread.h"


// CBaseThread

IMPLEMENT_DYNCREATE(CBaseThread, CWinThread)

CBaseThread::CBaseThread()
{
	m_bWorking = false;
	m_bPause = false;
	m_hThread = NULL;
	m_nThreadID = 0;
}

CBaseThread::~CBaseThread()
{
}

BOOL CBaseThread::InitInstance()
{
	// TODO:  여기에서 각 스레드에 대한 초기화를 수행합니다.
	return TRUE;
}

int CBaseThread::ExitInstance()
{
	// TODO:  여기에서 각 스레드에 대한 정리를 수행합니다.
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CBaseThread, CWinThread)
END_MESSAGE_MAP()


// CBaseThread 메시지 처리기입니다.

//-----------------------------------------------------------------------------
//
//	 스레드 시작
//
//-----------------------------------------------------------------------------
bool CBaseThread::StartThread()
{
	// 스레드가 동작중이면
	if (m_bWorking == true)
	{
		return false;
	}

	m_bWorking = true;
	
	if (::AfxBeginThread(ThreadFunc, (LPVOID)this) == NULL)
	{
		m_bWorking = false;
		return false;
	}
	
	return true;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
UINT CBaseThread::ThreadFunc(void* pParam)
{
	MSG stMessage;
	CBaseThread* pThread = (CBaseThread*)pParam;

	pThread->m_hThread = AfxGetThread()->m_hThread;
	pThread->m_nThreadID = AfxGetThread()->m_nThreadID;

	pThread->ThreadConstructor();

	while (pThread->m_bWorking == true)
	{
		if (PeekMessage(&stMessage, NULL, 0, 0, PM_NOREMOVE) != 0)
		{
			if (GetMessage(&stMessage, NULL, 0, 0) == -1)
			{
				break;
			}
			else
			{
				TranslateMessage(&stMessage);
				DispatchMessage(&stMessage);

				// TO DO : 메시지 처리
			}
		}

		if (pThread->m_bPause == false)
		{
			pThread->ThreadCallBack();
		}
		
		Sleep(MAX_THREAD_SLEEP_INTERVAL);
	}

	pThread->ThreadDestructor();

	pThread->m_hThread = NULL;
	pThread->m_bWorking = false;

	::AfxEndThread(0, TRUE);

	return TRUE;
}

//-----------------------------------------------------------------------------
//
//	스레드 종료
//
//-----------------------------------------------------------------------------
void CBaseThread::EndThread()
{
	if (m_bWorking == false)
	{
		return;
	}

	m_bWorking = false;
	m_bPause = false;

	if (::WaitForSingleObject(m_hThread, 300) == WAIT_TIMEOUT)
	{
		return;
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CBaseThread::PumpPendingMessage()
{
	if (m_bWorking == false)
	{
		return;
	}

	if (::PostThreadMessage(m_nThreadID, WM_PAINT, NULL, NULL) == FALSE)
	{
		TRACE("PostThreadMessage() Fail\n");
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------