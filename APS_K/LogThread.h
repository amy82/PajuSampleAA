#pragma once

#include "utility\basethread\basethread.h"

#include <queue>
#include <mutex>
#include <condition_variable>
class CLogThread :
	public CBaseThread
{
public:
	CLogThread(void);
	~CLogThread(void);
public:
    void CreateLogFolder(CString strLog);
protected:
	virtual void ThreadConstructor();
	virtual void ThreadDestructor();
	virtual void ThreadCallBack();

private:
	//void CreateLogFolder();
	void ProcessLog();
	//void WriteLogFile(STRUC_LOG_NODE* pNode);

	
	std::queue<std::string> logQueue;
	std::mutex queueMutex;
	std::condition_variable logCondition;
	bool isLogging;

	std::ofstream logFile;

	int nCount;
	int nUnit;
public:
	void Log(const std::string& message);
	void StopLogging();
};

