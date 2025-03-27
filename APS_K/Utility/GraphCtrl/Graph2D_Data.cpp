#include "StdAfx.h"
#include ".\\Graph2D_Data.h"

//! Added by LHW [2008/4/10] : 오름차순 정렬을 위한 비교에 사용될 함수
bool CompareForAscendSort(const strDataForSort&a, const strDataForSort&b)
{
	return a.dbData < b.dbData;
}

//! Added by LHW [2008/4/10] : 내림차순 정렬을 위한 비교에 사용될 함수
bool CompareForDescendSort(const strDataForSort&a, const strDataForSort&b)
{
	return a.dbData > b.dbData;
}

CGraph2D_Data::CGraph2D_Data(void)
{
	m_iElementIndex = -1;	//! Modify by LHW [2008/4/11]

	m_iMaxIndex = 0;

	m_dbMinX = 0.;
	m_dbMaxX = 0.;
	m_dbMinY = 0.;
	m_dbMaxY = 0.;

	m_iVisualDataSize = 0;
	m_iVisualDataStartIndex = 0;
	m_iVisualDataEndIndex = 0;
	m_iVisualMaxIndex = -1;
	m_iVisualRealDataStartIndex = 0;	//! Added by LHW [2008/11/18]
	m_iVisualRealDataEndIndex = 0;		//! Added by LHW [2008/11/18]
}

CGraph2D_Data::~CGraph2D_Data(void)
{
	ClearBuffer2D();
}

//! Modify by LHW [2008/5/23] : iCustomData, crPoint 초기화 추가
bool CGraph2D_Data::SetPoint2D(double *pdbInputY, int iInputSize)
{
	if ( pdbInputY == NULL || iInputSize <= 0 )
	{
		return false;
	}

	ClearBuffer2D();

	strPoint2D strNewData;

	for ( int i = 0; i < iInputSize; i++ )
	{
		strNewData.dbX = (double)i;
		strNewData.dbY = pdbInputY[i];
		strNewData.iCustomData = -1;
		strNewData.crPoint.SetRectEmpty();
		m_vPoint2D.push_back(strNewData);
	}

	return DecideMinMax();
}

//! Modify by LHW [2008/5/23] : iCustomData, crPoint 초기화 추가
bool CGraph2D_Data::SetPoint2D(double dbStartX, double dbIncrementX, double *pdbInputY, int iInputSize)
{
	if ( pdbInputY == NULL || iInputSize <= 0 )
	{
		return false;
	}

	ClearBuffer2D();

	strPoint2D strNewData;

	for ( int i = 0; i < iInputSize; i++ )
	{
		strNewData.dbX = dbStartX;
		strNewData.dbY = pdbInputY[i];
		strNewData.iCustomData = -1;
		strNewData.crPoint.SetRectEmpty();
		m_vPoint2D.push_back(strNewData);
		dbStartX += dbIncrementX;
	}

	return DecideMinMax();
}

//! Modify by LHW [2008/5/23] : iCustomData, crPoint 초기화 추가
bool CGraph2D_Data::SetPoint2D(double *pdbInputX, double *pdbInputY, int iInputSize)
{
	if ( pdbInputX == NULL || pdbInputY == NULL || iInputSize <= 0 )
	{
		return false;
	}

	ClearBuffer2D();

	strPoint2D strNewData;

	for ( int i = 0; i < iInputSize; i++ )
	{
		strNewData.dbX = pdbInputX[i];
		strNewData.dbY = pdbInputY[i];
		strNewData.iCustomData = -1;
		strNewData.crPoint.SetRectEmpty();
		m_vPoint2D.push_back(strNewData);
	}

	return DecideMinMax();
}

//! Modify by LHW [2008/5/23] : iCustomData, crPoint 초기화 추가
bool CGraph2D_Data::AddPoint2D(double dbInputX, double dbInputY)
{
	strPoint2D strNewData;
	strNewData.dbX = dbInputX;
	strNewData.dbY = dbInputY;
	strNewData.iCustomData = -1;
	strNewData.crPoint.SetRectEmpty();
	m_vPoint2D.push_back(strNewData);
	return true;
}

//! Added by LHW [2008/5/23]
bool CGraph2D_Data::SetPoint2D(double *pdbInputY, int *piCustomData, int iInputSize)
{
	if ( pdbInputY == NULL || iInputSize <= 0 )
	{
		return false;
	}

	ClearBuffer2D();

	strPoint2D strNewData;

	for ( int i = 0; i < iInputSize; i++ )
	{
		strNewData.dbX = (double)i;
		strNewData.dbY = pdbInputY[i];
		if ( piCustomData != NULL )
		{
			strNewData.iCustomData = piCustomData[i];
		}
		else
		{
			strNewData.iCustomData = -1;
		}
		strNewData.crPoint.SetRectEmpty();
		m_vPoint2D.push_back(strNewData);
	}

	return DecideMinMax();
}

//! Added by LHW [2008/5/23]
bool CGraph2D_Data::SetPoint2D(double dbStartX, double dbIncrementX, double *pdbInputY, int *piCustomData, int iInputSize)
{
	if ( pdbInputY == NULL || iInputSize <= 0 )
	{
		return false;
	}

	ClearBuffer2D();

	strPoint2D strNewData;

	for ( int i = 0; i < iInputSize; i++ )
	{
		strNewData.dbX = dbStartX;
		strNewData.dbY = pdbInputY[i];
		if ( piCustomData != NULL )
		{
			strNewData.iCustomData = piCustomData[i];
		}
		else
		{
			strNewData.iCustomData = -1;
		}
		strNewData.crPoint.SetRectEmpty();
		m_vPoint2D.push_back(strNewData);
		dbStartX += dbIncrementX;
	}

	return DecideMinMax();
}

//! Added by LHW [2008/5/23]
bool CGraph2D_Data::SetPoint2D(double *pdbInputX, double *pdbInputY, int *piCustomData, int iInputSize)
{
	if ( pdbInputX == NULL || pdbInputY == NULL || iInputSize <= 0 )
	{
		return false;
	}

	ClearBuffer2D();

	strPoint2D strNewData;

	for ( int i = 0; i < iInputSize; i++ )
	{
		strNewData.dbX = pdbInputX[i];
		strNewData.dbY = pdbInputY[i];
		if ( piCustomData != NULL )
		{
			strNewData.iCustomData = piCustomData[i];
		}
		else
		{
			strNewData.iCustomData = -1;
		}
		strNewData.crPoint.SetRectEmpty();
		m_vPoint2D.push_back(strNewData);
	}

	return DecideMinMax();
}

//! Added by LHW [2008/5/23]
bool CGraph2D_Data::AddPoint2D(double dbInputX, double dbInputY, int iCustomData)
{
	strPoint2D strNewData;
	strNewData.dbX = dbInputX;
	strNewData.dbY = dbInputY;
	strNewData.iCustomData = iCustomData;
	strNewData.crPoint.SetRectEmpty();
	m_vPoint2D.push_back(strNewData);
	return true;
}

bool CGraph2D_Data::ClearBuffer2D()
{
	m_vPoint2D.clear();
	m_vSortRes.clear();

	m_dbMinX = 0.;
	m_dbMaxX = 0.;
	m_dbMinY = 0.;
	m_dbMaxY = 0.;

	m_iVisualDataSize = 0;
	m_iVisualDataStartIndex = 0;
	m_iVisualDataEndIndex = 0;
	m_iVisualMaxIndex = -1;
	m_iVisualRealDataStartIndex = 0;	//! Added by LHW [2008/11/18]
	m_iVisualRealDataEndIndex = 0;		//! Added by LHW [2008/11/18]

	return true;
}

bool CGraph2D_Data::DecideMinMax()
{
	int iPointSize = GetPointSize();

	if ( iPointSize <= 0 )
	{
		return false;
	}

	m_dbMinX = m_vPoint2D[0].dbX;
	m_dbMaxX = m_vPoint2D[0].dbX;
	m_dbMinY = m_vPoint2D[0].dbY;
	m_dbMaxY = m_vPoint2D[0].dbY;
	
	for ( int i = 1; i < iPointSize; i++ )
	{
		if (m_vPoint2D[i].dbX < m_dbMinX)
			m_dbMinX = m_vPoint2D[i].dbX;
		if (m_vPoint2D[i].dbX > m_dbMaxX)
			m_dbMaxX = m_vPoint2D[i].dbX;

		if (m_vPoint2D[i].dbY < m_dbMinY)
			m_dbMinY = m_vPoint2D[i].dbY;
		if (m_vPoint2D[i].dbY > m_dbMaxY)
		{
			m_iMaxIndex = i;	//! Modify by LHW [2008/4/15]
			m_dbMaxY = m_vPoint2D[i].dbY;
		}
	}

	return true;
}

int CGraph2D_Data::GetPointSize() const
{
	return (int)(m_vPoint2D.size());
}

double CGraph2D_Data::GetXPoint2D(int iIndex) const
{
	/*if ( iIndex < 0 || iIndex >= GetPointSize() )
	{
		return -1.;
	}*/

	return m_vPoint2D[iIndex].dbX;
}

double CGraph2D_Data::GetYPoint2D(int iIndex) const
{
	/*if ( iIndex < 0 || iIndex >= GetPointSize() )
	{
		return -1.;
	}*/

	return m_vPoint2D[iIndex].dbY;
}

//! Added by LHW [2008/5/23]
bool CGraph2D_Data::SetDataPointRect(int iIndex, CRect crPoint)
{
	m_vPoint2D[iIndex].crPoint = crPoint;
	return true;
}

//! Added by LHW [2008/5/23]
CRect CGraph2D_Data::GetDataPointRect(int iIndex)
{
	return m_vPoint2D[iIndex].crPoint;
}

//! Added by LHW [2008/5/23]
int CGraph2D_Data::GetCustomData(int iIndex)
{
	return m_vPoint2D[iIndex].iCustomData;
}

//! Added by LHW [2008/4/10]
bool CGraph2D_Data::SortXDirection(bool bAscend)
{
	int iPointSize = GetPointSize();

	if ( iPointSize <= 0 )
	{
		return false;
	}

	m_vSortRes.clear();

	strDataForSort strSortData;

	for ( int i = 0; i < iPointSize; i++ )
	{
		strSortData.iDataIndex = i;
		strSortData.dbData = GetXPoint2D(i);
		m_vSortRes.push_back(strSortData);
	}

	if ( bAscend == true )
	{
		//sort(m_vSortRes.begin(), m_vSortRes.end(), CompareForAscendSort);
	}
	else
	{
		//sort(m_vSortRes.begin(), m_vSortRes.end(), CompareForDescendSort);
	}

	return true;
}

//! Added by LHW [2008/4/10]
bool CGraph2D_Data::SortYDirection(bool bAscend)
{
	int iPointSize = GetPointSize();

	if ( iPointSize <= 0 )
	{
		return false;
	}

	m_vSortRes.clear();

	strDataForSort strSortData;

	for ( int i = 0; i < iPointSize; i++ )
	{
		strSortData.iDataIndex = i;
		strSortData.dbData = GetYPoint2D(i);
		m_vSortRes.push_back(strSortData);
	}

	if ( bAscend == true )
	{
		//sort(m_vSortRes.begin(), m_vSortRes.end(), CompareForAscendSort);
	}
	else
	{
		//sort(m_vSortRes.begin(), m_vSortRes.end(), CompareForDescendSort);
	}

	return true;
}

//! Added by LHW [2008/4/10]
int CGraph2D_Data::GetSortDataSize() const
{
	return (int)(m_vSortRes.size());
}

//! Added by LHW [2008/4/10]
int CGraph2D_Data::GetIndexPoint2D_Sort(int iIndex) const
{
	return m_vSortRes[iIndex].iDataIndex;
}

//! Added by LHW [2008/4/28]
bool CGraph2D_Data::ClearBufferSort()
{
	m_vSortRes.clear();

	return true;
}

//! Added by LHW [2008/4/28]
bool CGraph2D_Data::SetDataSort(strDataForSort *pstrInputData, int iInputSize)
{
	if ( pstrInputData == NULL || iInputSize <= 0 )
	{
		return false;
	}

	for ( int i = 0; i < iInputSize; i++ )
	{
		m_vSortRes.push_back(pstrInputData[i]);
	}

	return true;
}

//! Added by LHW [2008/4/28]
bool CGraph2D_Data::AddDataSort(strDataForSort strInputData)
{
	m_vSortRes.push_back(strInputData);

	return true;
}

//! Added by LHW [2008/4/28]
bool CGraph2D_Data::SortProc(bool bAscend)
{
	if ( bAscend == true )
	{
		//sort(m_vSortRes.begin(), m_vSortRes.end(), CompareForAscendSort);
	}
	else
	{
		//sort(m_vSortRes.begin(), m_vSortRes.end(), CompareForDescendSort);
	}

	return true;
}
