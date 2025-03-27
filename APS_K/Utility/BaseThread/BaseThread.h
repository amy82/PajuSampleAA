#pragma once



// CBaseThread

#define MAX_THREAD_SLEEP_INTERVAL		10

class CBaseThread : public CWinThread
{
	DECLARE_DYNCREATE(CBaseThread)

protected:
	CBaseThread();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CBaseThread();

	virtual void ThreadConstructor(){ return; };
	virtual void ThreadDestructor(){ return; };
	virtual void ThreadCallBack(){ return; };

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	bool StartThread();
	void EndThread();
	void PumpPendingMessage();
	bool GetThreadRunning(){ return m_bWorking; };
	void SetThreadPause(bool bPause){ if(m_bWorking == true) m_bPause = bPause; };
	bool GetThreadPause(){ return m_bPause; };
private:
	static UINT ThreadFunc(void* pParam);

private:
	bool m_bWorking;	
	bool m_bPause;
	HANDLE m_hThread;
	DWORD m_nThreadID;

protected:
	DECLARE_MESSAGE_MAP()
};


