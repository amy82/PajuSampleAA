#include "StdAfx.h"
#include "TimeChecker.h"


CTimeChecker::CTimeChecker(void)
{
	Init_Time();
}


CTimeChecker::~CTimeChecker(void)
{
}


void CTimeChecker::Init_Time()
{
	int i = 0;
	for ( i = 0; i < iBufSize_Time_Check_Point; i++ )
	{
		m_adTime[i] = 0.;
	}
	m_bFlag_Valid_Freq = false;
}


bool CTimeChecker::Start_Time()
{
	if ( QueryPerformanceFrequency(&m_liFreq) == TRUE )
	{
		m_bFlag_Valid_Freq = true;
	}
	else
	{
		m_bFlag_Valid_Freq = false;		
	}

    if ( QueryPerformanceCounter(&m_liStartCounter) == FALSE )
	{
		m_bFlag_Valid_Freq = false;
	}

	return m_bFlag_Valid_Freq;
}


double CTimeChecker::Measure_Time(int iIndex_Time)
{
	double dRet = -1.;

	if ( m_bFlag_Valid_Freq == false )
	{
		return dRet;
	}
	if ( iIndex_Time < 0 || iIndex_Time >= iBufSize_Time_Check_Point )
	{
		return dRet;
	}

	if ( QueryPerformanceCounter( &(m_aliCounter[iIndex_Time]) ) == TRUE )
	{
		dRet = ((double)(m_aliCounter[iIndex_Time].QuadPart - m_liStartCounter.QuadPart)) / ((double)m_liFreq.QuadPart);
		dRet *= 1000.;
	}
	
	m_adTime[iIndex_Time] = dRet;

	return dRet;
}
