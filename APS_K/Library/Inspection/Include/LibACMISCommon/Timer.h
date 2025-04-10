#pragma once

#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>

class Timer
{
private:
	std::chrono::system_clock::time_point& m_startTime;
	std::chrono::system_clock::time_point& m_endTime;
	long long& m_elapsedTime;
	std::string& m_strTimeData;

	std::ostringstream m_oss;

public:
	Timer(std::chrono::system_clock::time_point& outStartTime, 
		  std::chrono::system_clock::time_point& outEndTime, 
		  long long& outElapsedTime, std::string& outStrTimeData)
		: m_startTime(outStartTime), m_endTime(outEndTime)
		, m_elapsedTime(outElapsedTime), m_strTimeData(outStrTimeData)
	{
		m_startTime = std::chrono::system_clock::now();
		m_oss << ConvertTimepointToString(m_startTime) << ',';
	}
	~Timer()
	{
		m_endTime = std::chrono::system_clock::now();
		m_elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(m_endTime - m_startTime).count();
		m_oss << ConvertTimepointToString(m_endTime) << ',' << m_elapsedTime;
		m_strTimeData = m_oss.str();
	}

	inline static std::string GetTimeDataHeader()
	{
		return "StartTime,EndTime,ElapsedTime,";
	}

	inline static std::string ConvertTimepointToString(const std::chrono::system_clock::time_point& time)
	{
		auto time_t = std::chrono::system_clock::to_time_t(time);
		auto duration = time.time_since_epoch();
		auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() % 1000;

		std::ostringstream oss;
		struct tm time_tm;
		localtime_s(&time_tm, &time_t);
		oss << std::put_time(&time_tm, "%Y-%m-%d %H:%M:%S") << '.' << millis;

		return oss.str();
	}
};

class CStopWatch
{
private:
	LARGE_INTEGER freq, start, end;

public:
	CStopWatch()
	{
		QueryPerformanceFrequency(&freq);
		start.QuadPart = 0;
		end.QuadPart = 0;
		StartTime();
	};

	inline void StartTime()
	{
		QueryPerformanceCounter(&start);
	};

	inline double CheckTime()
	{
		QueryPerformanceCounter(&end);

		return (double)(end.QuadPart - start.QuadPart) / (freq.QuadPart * 1000); // ms
		//TRACE("%.2f msec\n", elapsed);
	};
};