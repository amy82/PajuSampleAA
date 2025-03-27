//! 2D 직교좌표 그래프 컨트롤의 그래프 데이터 클래스
//! Maked by LHW (2008/3/14 ~ )
//! 최종 작업일 [2009/6/4]

#pragma once

#include <vector>
#include <algorithm>	//! Added by LHW [2008/4/10]

//! Added by LHW [2008/4/10]
struct strDataForSort
{
	int iDataIndex;	//! m_vPoint2D에서의 데이터 index
	double dbData;	//! 정렬의 비교 대상이 되는 값

	strDataForSort()
	{
		InitInfo();
	}

	void InitInfo()
	{
		iDataIndex = -1;
		dbData = 0.;
	}

	strDataForSort& operator=(const strDataForSort &info)  //! = 연산자 재정의
	{
		iDataIndex = info.iDataIndex;
		dbData = info.dbData;

		return *this;
	}	
};

class CGraph2D_Data
{
	//! Modify by LHW [2008/5/23] : iCustomData, crPoint 추가
	struct strPoint2D
	{
		double dbX;	//! X 데이터
		double dbY;	//! Y 데이터

		int iCustomData;
		CRect crPoint;
	};

public:
	CGraph2D_Data(void);
	~CGraph2D_Data(void);

	int m_iElementIndex;	//! 데이터 저장소의 index, Modify by LHW [2008/4/11]

	//! 데이터 입력 함수
	bool SetPoint2D(double *pdbInputY, int iInputSize);
	bool SetPoint2D(double dbStartX, double dbIncrementX, double *pdbInputY, int iInputSize);
	bool SetPoint2D(double *pdbInputX, double *pdbInputY, int iInputSize);
	bool AddPoint2D(double dbInputX, double dbInputY);

	//! Added by LHW [2008/5/23] : 데이터 입력 함수, Custom 데이터 입력 기능 추가
	bool SetPoint2D(double *pdbInputY, int *piCustomData, int iInputSize);
	bool SetPoint2D(double dbStartX, double dbIncrementX, double *pdbInputY, int *piCustomData, int iInputSize);
	bool SetPoint2D(double *pdbInputX, double *pdbInputY, int *piCustomData, int iInputSize);
	bool AddPoint2D(double dbInputX, double dbInputY, int iCustomData);

	bool ClearBuffer2D();	//! 데이터 모두 삭제
	bool DecideMinMax();	//! 입력된 데이터에서 m_dbMinX, m_dbMaxX, m_dbMinY, m_dbMaxY을 찾아냄

	int m_iMaxIndex;	//! m_dbMaxY값에 해당하는 X값의 index, Added by LHW [2008/4/15]

	double m_dbMinX;	//! 입력된 데이터의 X 최소값
	double m_dbMaxX;	//! 입력된 데이터의 X 최대값
	double m_dbMinY;	//! 입력된 데이터의 Y 최소값
	double m_dbMaxY;	//! 입력된 데이터의 Y 최대값

	int m_iVisualDataSize;		//! 현재 Range 설정에서 눈에 보이는 데이터의 개수, X축 Range만 고려, Modify by LHW [2009/6/4]
	int m_iVisualDataStartIndex;//! 현재 Range 설정에서 눈에 보이는 데이터의 시작 index (여유값 포함)
	int m_iVisualDataEndIndex;	//! 현재 Range 설정에서 눈에 보이는 데이터의 마침 index (여유값 포함)
	int	m_iVisualMaxIndex;		//! 현재 Range 설정에서 눈에 보이는 데이터 최대값의 index

	int m_iVisualRealDataStartIndex;//! 현재 Range 설정에서 눈에 보이는 데이터의 시작 index, Added by LHW [2008/11/18]
	int m_iVisualRealDataEndIndex;	//! 현재 Range 설정에서 눈에 보이는 데이터의 마침 index, Added by LHW [2008/11/18]

	int GetPointSize() const;				//! 데이터 개수 반환
	double GetXPoint2D(int iIndex) const;	//! 주어진 데이터 index의 X 데이터 반환
	double GetYPoint2D(int iIndex) const;	//! 주어진 데이터 index의 Y 데이터 반환

	//! Added by LHW [2008/5/23] : 그래프의 점의 사각 영역을 설정하거나 반환
	bool SetDataPointRect(int iIndex, CRect crPoint);
	CRect GetDataPointRect(int iIndex);
	int GetCustomData(int iIndex);

	bool ClearBufferSort();						//! 정렬용 버퍼의 데이터 모두 삭제
	bool SetDataSort(strDataForSort *pstrInputData, int iInputSize);	//! 정렬하기 위한 데이터 입력
	bool AddDataSort(strDataForSort strInputData);						//! 정렬하기 위한 데이터 추가
	bool SortProc(bool bAscend = true);			//! 입력된 데이터를 정렬, bAscend가 true이면 오름차순 정렬
	int GetSortDataSize() const;				//! 정렬된 데이터 버퍼의 크기 반환
	bool SortXDirection(bool bAscend = true);	//! X 데이터로 정렬, bAscend가 true이면 오름차순 정렬, SetDataSort나 AddDataSort 호출하지 않아도 됨
	bool SortYDirection(bool bAscend = true);	//! Y 데이터로 정렬, bAscend가 true이면 오름차순 정렬, SetDataSort나 AddDataSort 호출하지 않아도 됨
	int GetIndexPoint2D_Sort(int iIndex) const;	//! 정렬된 결과에서 주어진 index의 데이터 index를 반환

private:
	std::vector<strPoint2D> m_vPoint2D;		//! 그래프를 그리는 데이터를 저장하는 버퍼
	std::vector<strDataForSort> m_vSortRes;	//! 정렬 결과를 저장하는 버퍼	
};
