#pragma once

//! Maked by LHW, 2013/3/4

//! 경과 시간 측정용 클래스

const int iBufSize_Time_Check_Point = 100;

class CTimeChecker
{
public:
	CTimeChecker(void);
	~CTimeChecker(void);

private:
	bool				m_bFlag_Valid_Freq;
	LARGE_INTEGER		m_liFreq;
	LARGE_INTEGER		m_liStartCounter;
	LARGE_INTEGER		m_aliCounter[iBufSize_Time_Check_Point];

public:
	double				m_adTime[iBufSize_Time_Check_Point];

	inline bool IsSuccess_Start_Time() { return m_bFlag_Valid_Freq; }

	void   Init_Time();
	bool   Start_Time();
	double Measure_Time(int iIndex_Time);
};

