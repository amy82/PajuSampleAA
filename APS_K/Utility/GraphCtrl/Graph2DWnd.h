//! 2D 직교좌표 그래프 컨트롤의 본체 클래스
//! Maked by LHW [2008/3/14 ~ ]
//! 최종 작업일 [2013/4/1]

#pragma once

#include "dib256.h"	//! Added by LHW [2009/2/25]

// CGraph2DWnd

//! 1) 화면이 MM_TEXT 매핑 모드로 설정되어 있어야 사용 가능
//! 2) 모든 Remove~(삭제할 index), Delete~(삭제할 index) 함수를 사용한 후에는 삭제할 index 뒤의 요소들이 앞으로 이동하므로, 
//!    삭제한 index 뒤의 index는 모두 1을 빼주어야 함
//! 3) 모든 함수의 index는 0 based
//! 4) 그래프를 그려줄 데이터는 반드시 X축 방향 데이터가 오름차순이 되도록 입력해 주어야 함

#include ".\\Graph2D_Resource.h"//! CGraph2D_Resource, strGraph2DResourceInfo 등 사용

class CGraph2D_Data;
class CGraph2DWnd : public CWnd
{
	struct strYCaption	//! Y축 설명 문자열의 정보(E_GRAPH2D_XY_CAPTION_POS_UNITE에서 사용)
	{
		CString szCaption;
		COLORREF clrCaption;

		void InitInfo()
		{
			szCaption = _T("");
			clrCaption = RGB(0, 0, 0);
		}

		strYCaption& operator=(const strYCaption &info)  //! = 연산자 재정의
		{
			szCaption = info.szCaption;
			clrCaption = info.clrCaption;

			return *this;
		}
	};

	struct strPanPosition	//! Pan 기능에서 마우스로 선택한 시작점과 마침점의 좌표
	{
		int iStartX;
		int iStartY;
		int iEndX;
		int iEndY;

		void InitInfo()
		{
			iStartX = iStartY = 0;
			iEndX = iEndY = 0;
		}

		strPanPosition& operator=(const strPanPosition &info)  //! = 연산자 재정의
		{
			iStartX = info.iStartX;
			iStartY = info.iStartY;
			iEndX = info.iEndX;
			iEndY = info.iEndY;

			return *this;
		}
	};

	struct strYRangeMapper	//! 데이터의 실수형 값을 화면 상의 정수형 값으로 변환해 줌
	{		
		int		m_iYPtMin;		//! MM_TEXT 매핑 모드이므로 m_dbYDataMax와 대응
		int		m_iYPtMax;		//! MM_TEXT 매핑 모드이므로 m_dbYDataMin와 대응
		double	m_dbYDataMin;
		double	m_dbYDataMax;
			
		double  m_dbCoeff;
	
		void CalcCoeff()	//! 변환 계수 계산, CalcYDataToPt, CalcPtToYData함수 전에 반드시 호출되어야 함
		{
			m_dbCoeff = ( (double)(m_iYPtMax - m_iYPtMin) ) / (m_dbYDataMax - m_dbYDataMin);
		}
		
		int	CalcYDataToPt(double dbDrawData)	//! 변환 계산
		{
			int iYPt = (int)( m_dbCoeff * (m_dbYDataMax - dbDrawData) ) + m_iYPtMin;

			return iYPt;
		}

		double CalcPtToYData(int iYPt)
		{
			double dbYData = m_dbYDataMax - (((double)(iYPt - m_iYPtMin)) / m_dbCoeff);

			return dbYData;
		}
	};

	struct strXRangeMapper	//! 데이터의 실수형 값을 화면 상의 정수형 값으로 변환해 줌
	{		
		int		m_iXPtMin;		//! m_dbXDataMin와 대응
		int		m_iXPtMax;		//! m_dbXDataMax와 대응
		double	m_dbXDataMin;
		double	m_dbXDataMax;
			
		double  m_dbCoeff;
	
		void CalcCoeff()	//! 변환 계수 계산, CalcXDataToPt, CalcPtToXData함수 전에 반드시 호출되어야 함
		{
			m_dbCoeff = ( (double)(m_iXPtMax - m_iXPtMin) ) / (m_dbXDataMax - m_dbXDataMin);
		}
		
		int	CalcXDataToPt(double dbDrawData)	//! 변환 계산
		{
			int iXPt = (int)( m_dbCoeff * (dbDrawData - m_dbXDataMin) ) + m_iXPtMin;

			return iXPt;
		}

		double CalcPtToXData(int iXPt)
		{
			double dbXData = (((double)(iXPt - m_iXPtMin)) / m_dbCoeff) + m_dbXDataMin;

			return dbXData;
		}
	};

	DECLARE_DYNAMIC(CGraph2DWnd)

public:
	CGraph2DWnd();
	virtual ~CGraph2DWnd();

	bool m_bChanged;			//! 다음의 경우 true로 설정
								//! 그래프의 크기가 변할 때, strGraph2DResourceInfo 구조체가 변경될 때, 인쇄를 마치고 나서
								//! 그래프 데이터를 입력할 때, 확대/축소를 할 때
	
	bool m_bMultiPlotOneAxis;	//! true이면 여러 개의 Plot이 있더라도 Y축은 한 개만 존재
								//! true이면 Y축의 Grid 설정등은 SetResourceYInfo함수에서 0번의 설정을 따름
								//! 그래프가 보이는지의 여부, 그래프 색상등은 SetResourceYInfo함수에서 각각 설정

	HWND m_hMsgHandle;			//! 그래프 컨트롤에서 보내는 모든 메시지를 받을 핸들값
	bool m_bAutoDrawCompleteMsg;//! true이면 그래프 컨트롤의 크기가 변하거나 중요 설정이 변경되면, 
								//! 모니터 화면에 그래프를 그리는 작업을 완료후에 메시지를 보냄, Added by LHW [2008/7/01]
	bool m_bDrawCompleteMsg;	//! true이면 모니터 화면에 그래프를 그리는 작업을 완료후에 메시지를 보냄, Added by LHW [2008/5/31]
	bool m_bCursorEventMsg;		//! true이면 커서 이벤트 발생 때마다 메시지를 보냄
	bool m_bZoomEventMsg;		//! true이면 Zoom 이벤트 발생 때마다 메시지를 보냄, Added by LHW [2008/4/19]	
	bool m_bAxisYEventMsg;		//! true이면 Y축 부분에서 마우스 더블 클릭을 하면 메시지를 보냄, Added by LHW [2008/7/31]
	bool m_bTimeAxisXEventMsg;	//! true이면 X축이 시각 표시이고, 축의 눈에 보이는 최소, 최대값이 정해진 후 메시지를 보냄, Added by LHW [2008/8/18]
	bool m_bRegionCursorEventMsg;	//! true이면 영역 표시 커서 이벤트 발생 때마다 메시지를 보냄, Added by LHW [2008/11/28]
	bool m_bAxisXZoom;			//! true이면 Alt 키를 누른 상태에서 마우스로 X축 방향 확대, 축소 가능, Added by LHW [2009/2/2]
	bool m_bAxisYzoom;			//! true이면 Alt 키를 누른 상태에서 마우스로 Y축 방향 확대, 축소 가능, Added by LHW [2009/2/2]
	bool m_bAxisXYZoom;			//! true이면 Alt 키를 누른 상태에서 마우스로 X, Y축 방향 확대, 축소 가능, Added by LHW [2009/2/2]
	bool m_bAxisXPan;			//! true이면 Shift 키를 누른 상태에서 마우스로 X축 방향 확대, 축소 가능, Added by LHW [2009/2/2]
	bool m_bAxisYPan;			//! true이면 Shift 키를 누른 상태에서 마우스로 Y축 방향 확대, 축소 가능, Added by LHW [2009/2/2]
	bool m_bAxisXYPan;			//! true이면 Shift 키를 누른 상태에서 마우스로 X, Y축 방향 확대, 축소 가능, Added by LHW [2009/2/2]
	bool m_bSysmbolOnceDraw;	//! true이면 Symbol이 그려진 상태에서는 마우스 이벤트 영역을 그리지 않도록 함, Added by LHW [2009/2/19]
	bool m_bDataPointEventMsg;	//! true이면 왼쪽 Ctrl키를 누른 상태에서 그래프의 점을 클릭할 때마다 메시지를 보냄, Added by LHW [2008/5/23]
	bool m_bDataPointCusor;		//! true이면 왼쪽 Ctrl키를 누른 상태에서 마우스 커서가 변경, Added by LHW [2008/5/28]
	bool m_bXAutoRangeShowGraph;//! true이면 눈에 보이도록 설정된 그래프들만 고려하여 X축의 Min, Max 값을 산출
	bool m_bYAutoRangeShowGraph;//! true이면 눈에 보이도록 설정된 그래프들만 고려하여 Y축의 Min, Max 값을 산출
	bool m_bYAutoRangeValueLine;//! true이면 Y축 특정값 표시선이 모두 보이도록 Y축의 Min, Max 값을 산출
	bool m_bXAutoRangeEquation;	//! true이면 함수식으로 그려지는 그래프를 고려하여 X축의 Min, Max 값을 산출, Added by LHW [2008/8/25]
	bool m_bYAutoRangeEquation;	//! true이면 함수식으로 그려지는 그래프를 고려하여 Y축의 Min, Max 값을 산출, Added by LHW [2008/8/25]
	bool m_bXAutoRangeRegionCursor;	//! true이면 영역 표시 커서를 고려하여 X축의 Min, Max 값을 산출, Added by LHW [2008/12/14]
	bool m_bYAutoRangeRegionCursor;	//! true이면 영역 표시 커서를 고려하여 Y축의 Min, Max 값을 산출, Added by LHW [2008/12/14]
	bool m_bXValueLineRMouseDownChk;	//! Added by LHW [2008/4/19] : true이면 마우스 오른쪽 클릭을 할 때, 
										//! X축 특정 값 표시선 근처인지 확인하여 마우스 오른쪽 클릭 시의 메시지에 이벤트 발생 유무, LineIndex를 추가하여 보냄
	bool m_bChildCursorRMouseDownChk;	//! Added by LHW [2008/6/13] : true이면 마우스 오른쪽 클릭을 할 때, 
										//! 자식 커서 근처인지 확인하여 마우스 오른쪽 클릭 시의 메시지에 이벤트 발생 유무를 보냄
	bool m_bAuxCursorRMouseDownChk;		//! Added by LHW [2008/8/5] : true이면 마우스 오른쪽 클릭을 할 때, 
										//! 보조 커서 근처인지 확인하여 마우스 오른쪽 클릭 시의 메시지에 이벤트 발생 유무를 보냄
	bool m_bRegionCursorRMouseDownChk;	//! Added by LHW [2008/11/28] : true이면 마우스 오른쪽 클릭을 할 때, 
										//! 영역 표시 커서 근처인지 확인하여 마우스 오른쪽 클릭 시의 메시지에 이벤트 발생 유무를 보냄
	bool m_bSelectedCursorLine;			//! true이면 선택된 커서는 색상을 다르게 표시, Added by LHW [2008/5/14]
	bool m_bSelectedChildCursorLine;	//! true이면 선택된 자식 커서는 색상을 다르게 표시, Added by LHW [2008/6/16]
	bool m_bSelectedRegionCursorLine;	//! true이면 선택된 영역 표시 커서는 색상을 다르게 표시, Added by LHW [2008/11/28]
	int m_iTopOverlapIndex;			//! 여러 개의 그래프가 Overlap되어 있을 때, 맨 위에 보이는 그래프의 index, -1이면 순서대로 그려 줌, Added by LHW [2008/7/24]
	int m_iShowGridY_OverlapIndex;	//! 여러 개의 그래프가 Overlap되어 있을 때, 그 중에서 Y축 Grid선을 보여 줄 그래프의 index, -1이면 Grid선을 그리지 않음, Added by LHW [2008/7/30]
									//! 축이 1개만 있을 경우에는 내부에서 0으로 변경
	bool m_bCloseCursorSelect;	//! true이면 마우스 다운을 할 때, 가장 가까운 커서가 선택됨, Added by LHW [2008/7/24]
	E_GRAPH2D_CURSOR_ALL_SEARCH_MODE m_eCursorAllSearchMode;//! Overlap된 그래프에서 커서값 찾는 방법, Added by LHW [2008/7/24]
	bool m_bXScaleLock;	//! true이면 X축 Range 처리를 하지 않음, Added by LHW [2008/12/27]
	bool m_bYScaleLock;	//! true이면 Y축 Range 처리를 하지 않음, Added by LHW [2008/12/27]
	bool m_bAlwaysInitYPos;		//! true이면 항상 내부적으로 Init_XPos_YAxis 함수를 호출하여 Y축의 X좌표를 초기화, Added by LHW [2009/2/27]
	bool m_bCursorUpDownSearchOperation;	//! true이면 키보드 Up, Down 키를 누를 때, m_iCursorUpDownSearchMargin 만큼의 데이터를 체크하여
											//! 가장 가까운 X축 값을 가지는 커서로 이동, Added by LHW [2009/3/1]
	int m_iCursorUpDownSearchMargin;		//! 동일한 X축 값을 가지는 새로운 커서를 찾기 위한 검색 구간, Added by LHW [2009/3/1]
	
	bool m_bDrawBackGroundImage;	//! true이면 배경 이미지를 그림, Added by LHW [2009/2/25]
	CDIBitmap	m_bmpBackground;	//! 배경 이미지, Added by LHW [2009/2/25]
	
	E_GRAPH2D_MOVE_CURSOR_TYPE IsCurrentMoveCursorType();	//! 마지막으로 마우스, 키보드로 움직인 커서의 종류 반환, Added by LHW [2008/6/16]
    
	E_GRAPH2D_MOUSE_OPERATION m_eMouseOperationMode;	//! 현재 마우스가 동작하는 방식을 설정, 기본값으로 커서 동작이 설정되어 있음
	E_GRAPH2D_CURSOR_SEARCH_MODE m_eCursorSearchMode;	//! 마우스로 커서값을 찾는 방식, 기본값으로 E_GRAPH2D_CURSOR_SEARCH_X_RANGE 설정
	E_GRAPH2D_CURSOR_LINE_MODE m_eCursorLineMode;		//! 새로 추가되는 커서의 커서 선 표시 방식

	//! Plot의 각종 설정 함수
	void SetPlotIndex(int iPlotIndex);	//! Plot index 설정, 하나의 화면에 여러 개의 그래프가 있으면 Plot index로 구분 가능
	int GetPlotIndex() const;			//! Plot index 반환

	bool MakePlotBuffer(int iNewSize);	//! Overlap되는 그래프 선의 개수만큼 버퍼 생성, 이 함수를 호출하지 않아도 기본적으로 1개로 버퍼 생성
										//! 이 함수를 호출하면 기존 버퍼는 삭제하고 새로 생성
	bool AddPlotBuffer();				//! 기존 버퍼 뒤에 새로운 버퍼를 추가, Added by LHW [2008/4/11]
	int GetPlotBufferSize() const;		//! Overlap되는 그래프 선을 그리는 버퍼의 개수를 반환
	bool RemoveOnePlotBuffer(int iOverlapIndex);	//! 그래프 하나만 삭제, iOverlapIndex는 Overlap되는 그래프의 index (0 based)
	void RemoveAllPlotBuffer();						//! 그래프 전체 삭제

	bool SetResourcePtr(CGraph2D_Resource *pResource);	//! 외부에서 리소스 객체를 받음 (많은 수의 그래프를 동시에 그릴 때 사용)
														//! OS에서 할당해주는 리소스의 양에는 한계가 있으므로
														//! 이 함수를 사용하면 MakeResourcePtr 함수는 사용하지 않음
	bool MakeResourcePtr();				//! 직접 CGraph2D_Resource 리소스 객체를 생성, 그래프 수가 작거나 설정을 따로 해야 할 경우에 사용
	bool ReleaseResourcePtr();			//! 직접 생성한 CGraph2D_Resource 리소스 객체를 해제, MakeResourcePtr함수와 짝으로 사용

	//! 마우스 커서 설정
	void SetPanCursor(HCURSOR hNewPanCursor1, HCURSOR hNewPanCursor2);	//! Pan 동작에서 사용하는 커서 핸들값을 설정
																		//! hNewPanCursor1 : Pan 동작에서 Mouse Down 상태에서의 마우스 커서
																		//! hNewPanCursor2 : Pan 동작에서 보통 상태에서의 마우스 커서
	void SetDataPointCursor(HCURSOR hNewDataPointCursor);		//! Data-Point Event 동작에서 사용하는 커서 핸들값을 설정, Added by LHW [2008/5/28]
	void SetZoomXYCursor(HCURSOR hNewCursor);					//! Zoom Area 동작에서 사용하는 커서 핸들값을 설정, Added by LHW [2009/2/2]
	void SetZoomXCursor(HCURSOR hNewCursor);					//! Zoom X 동작에서 사용하는 커서 핸들값을 설정, Added by LHW [2009/2/2]
	void SetZoomYCursor(HCURSOR hNewCursor);					//! Zoom Y 동작에서 사용하는 커서 핸들값을 설정, Added by LHW [2009/2/2]
	void SetPanXCursor(HCURSOR hNewCursor);						//! X축 방향 Pan 동작에서 사용하는 커서 핸들값을 설정, Added by LHW [2009/2/2]
	void SetPanYCursor(HCURSOR hNewCursor);						//! Y축 방향 Pan 동작에서 사용하는 커서 핸들값을 설정, Added by LHW [2009/2/2]

	//! 그래프 정보 문자열 설정 함수, MakeResourcePtr 또는 SetResourcePtr 함수 호출후에 사용해야 함
	//! iOverlapIndex는 Overlap되는 그래프의 index (0 based)
	bool SetCaptionX(CString szInput);							//! X축 설명 문자열 입력
	bool SetCaptionY(CString szInput1, CString szInput2, int iOverlapIndex = 0);	//! Y축 설명 문자열 입력, szInput2 추가, Modify by LHW [2008/7/24]
	bool SetCursorUnitX(CString szInput);						//! 커서 정보창에 표시될 X축 단위 문자열 입력
	bool SetCursorUnitY(CString szInput, int iOverlapIndex = 0);//! 커서 정보창에 표시될 Y축 단위 문자열 입력

	//! 색상, Range, 커서의 소수점 자리수 설정 함수, "Graph2D_Struct.h" 파일에 구조체 선언부가 있음
	//! MakeResourcePtr 또는 SetResourcePtr 함수 호출후에 사용해야 함
	bool SetResourceInfo(strGraph2DResourceInfo strInfo);
	bool GetResourceInfo(strGraph2DResourceInfo &strInfo);
	//! Y축 Grid, 커서의 Y 값 표시, 그래프의 선 색상 설정, iOverlapIndex는 Overlap되는 그래프의 index (0 based), MakePlotBuffer 함수 호출 후에 사용
	bool SetResourceYInfo(strGraph2D_Y_Axis_Info strInfo, int iOverlapIndex = 0);
	bool GetResourceYInfo(strGraph2D_Y_Axis_Info &strInfo, int iOverlapIndex = 0);

	//! Y축의 X좌표는 Grid의 문자열의 너비가 커지면 같이 커진 후 그 크기로 고정, 최대치는 현재 화면 너비의 절반, 화면 크기가 바뀌면 Y축의 X좌표를 초기화, Added by LHW [2008/10/25]
	bool Init_XPos_YAxis(int iOverlapIndex);	//! Y축의 X좌표를 초기화
	bool Get_XPos_YAxis(int iOverlapIndex, int &iLeftXPtofYAxis, int &iRightXPtofYAxis);//! Y축의 X좌표를 반환
	bool Set_XPos_YAxis(int iOverlapIndex, int iLeftXPtofYAxis, int iRightXPtofYAxis);	//! Y축의 X좌표를 강제로 설정, 하지만 Grid의 문자열의 너비가 커지면 자동으로 변경

	//! 데이터 입력,조작 함수, Overlap되는 데이터의 index(iOverlapIndex)는 0 based
	//! SetPlotData 함수는 기존의 데이터를 삭제하고 모든 데이터를 추가하는 함수, 내부적으로 ClearPlotData, DecideMinMax 호출됨
	//! AddPlotData 함수는 데이터를 하나씩 입력할 때 사용, 기존의 데이터에 계속 추가할 수도 있음
	//!		단, AddPlotData 함수는 새로 데이터를 입력할 경우, 이 함수를 사용하기 전에 ClearPlotData를 호출해야 함
	//!		    AddPlotData 함수는 데이터를 모두 입력한 후에 반드시 DecideMinMax를 호출해야 함
	bool SetPlotData(double *pdbInY, int iInputSize, int iOverlapIndex = 0);//! 데이터 입력, X축 데이터는 0 based의 index값이 입력됨
	bool SetPlotData(double dbStartX, double dbIncrementX, double *pdbInY, int iInputSize, int iOverlapIndex = 0);	
																		//! 데이터 입력, X축 방향으로는 시작값과 증가값을 입력
	bool SetPlotData(double *pdbInX, double *pdbInY, int iInputSize, int iOverlapIndex = 0);	
																		//! 데이터 입력, X, Y축 방향으로 각각 데이터 입력
	bool SetPlotData(COleDateTime timeStartX, int iIncrementSecondX, double *pdbInY, int iInputSize, int iOverlapIndex = 0);
											//! 데이터 입력, X축 방향으로 시작 시각과 초 단위의 증가값을 입력, Added by LHW [2008/4/2]
	bool AddPlotData(double dbInX, double dbInY, int iOverlapIndex = 0);//! 데이터를 하나씩 입력
	bool AddPlotData(COleDateTime timeInX, double dbInY, int iOverlapIndex = 0);//! 데이터를 하나씩 입력, X 데이터는 Time 데이터, Added by LHW [2008/4/2]
	bool ClearPlotData(int iOverlapIndex = 0);	//! 현재 데이터 제거 함수
	bool DecideMinMax(int iOverlapIndex = 0);	//! 현재 입력된 X, Y 데이터의 최대, 최소값을 찾아내어 해당 변수에 갱신

	//! Added by LHW [2008/5/23] : 데이터 입력,조작 함수, Custom Data 입력 기능 추가, 그 이외에는 위의 데이터 입력,조작 함수들과 동일
	//! Custom Data는 0이상의 정수값이 입력되어 있을 경우에만 이벤트용 사각 영역 생성
	//! Overlap되는 데이터의 index(iOverlapIndex)는 0 based
	//! Custom Data의 개수는 X, Y 입력값의 개수와 동일해야 함, Custom Data 입력 버퍼를 NULL로 하면 -1로 입력
	bool SetPlotData(double *pdbInY, int *piCustomData, int iInputSize, int iOverlapIndex = 0);//! 데이터 입력, X축 데이터는 0 based의 index값이 입력됨
	bool SetPlotData(double dbStartX, double dbIncrementX, double *pdbInY, int *piCustomData, int iInputSize, int iOverlapIndex = 0);	
																		//! 데이터 입력, X축 방향으로는 시작값과 증가값을 입력
	bool SetPlotData(double *pdbInX, double *pdbInY, int *piCustomData, int iInputSize, int iOverlapIndex = 0);	
																		//! 데이터 입력, X, Y축 방향으로 각각 데이터 입력
	bool SetPlotData(COleDateTime timeStartX, int iIncrementSecondX, double *pdbInY, int *piCustomData, int iInputSize, int iOverlapIndex = 0);
											//! 데이터 입력, X축 방향으로 시작 시각과 초 단위의 증가값을 입력
	bool AddPlotData(int iCustomData, double dbInX, double dbInY, int iOverlapIndex = 0);//! 데이터를 하나씩 입력
	bool AddPlotData(int iCustomData, COleDateTime timeInX, double dbInY, int iOverlapIndex = 0);//! 데이터를 하나씩 입력, X 데이터는 Time 데이터

	//! Added by LHW [2013/2/22]
	bool GetPlotDataX(double &dbValueX, int iDataIndex, int iOverlapIndex = 0);
	bool GetPlotDataY(double &dbValueY, int iDataIndex, int iOverlapIndex = 0);

	//! 외부에서 CDC객체와 사각 영역을 주어 Plot을 그려주는 함수, 인쇄 기능에 필요
	//! 인쇄를 할 때, 반드시 MM_TEXT 매핑 모드 상태이어야 함
	bool Display(CDC *pDC, const CRect crDraw, bool bPrintFlag);		//! 실질적으로 그래프를 그리는 함수
																		//! crDraw로 그래프의 시작 위치, 크기를 정해 줌
																		//! 호출하지 않아도 내부적으로 OnPaint()에서 호출됨
																		//! 인쇄할 때는 bPrintFlag를 true로 설정하여 직접 호출해야 함

	//! Added by LHW [2008/4/19]
	//! 일정 구간안의 Peak 값을 찾는 함수, Data index는 모두 0 based, iOverlapIndex는 Overlap되는 그래프의 index (0 based)
	//! iStartDataIndex : 시작 index, iEndDataIndex : 마침 index, iPeakDataIndex는 찾아낸 Peak 값의 데이터 index
	bool GetLocalPeakDataIndex(int iStartDataIndex, int iEndDataIndex, int &iPeakDataIndex, int iOverlapIndex = 0);

	//! 커서 조작 함수, 커서 index, Data index는 모두 0 based, iOverlapIndex는 Overlap되는 그래프의 index (0 based)
	//! bRecvEvent : 커서 이벤트를 받아 처리할 때는 {{반드시}} true로 해야 함, 그 이외에는 false로 설정
	int GetCurrentCursorSize();							//! 커서 개수 반환
	bool IsCurrentCursorSelect(int &iSelectCursorIndex);//! 현재 선택된 커서의 index를 iSelectCursorIndex로 반환
														//! 현재 선택된 커서가 없으면 iSelectCursorIndex로 -1을 반환, 현재 커서가 없으면 false를 반환														
	bool IsCursorSelected(int &iSelectCursorIndex);		//! 현재 선택된 커서의 index를 iSelectCursorIndex로 반환, 현재 커서가 없으면 false를 반환
														//! IsCurrentCursorSelect와는 달리 현재 선택된 커서가 없으면 마지막으로 선택된 커서의 index값을 반환

	bool GetCursorOverlapIndex(int iCursorIndex, int &iOverlapIndex);	//! 주어진 커서 index의 커서의 그래프 index 반환
	bool SetCursorOverlapIndex(int iCursorIndex, int iOverlapIndex);	//! 주어진 커서 index의 커서의 그래프 index 새로 설정, Added by LHW [2008/7/29]
	bool GetCursorDataIndex(int iCursorIndex, int &iDataIndex);			//! 주어진 커서 index의 커서의 Data index 반환

	bool ShowToggleCursorInfoInSelected(bool bRecvEvent);				//! 선택된 커서 정보창을 보이게 하거나 보이지 않게 함
	bool ShowToggleCursorInfo(int iCursorIndex, bool bRecvEvent);		//! 주어진 커서 index의 커서 정보창을 보이게 하거나 보이지 않게 함
	bool ShowCursorInfoInSelected(bool bShow, bool bRecvEvent);			//! 선택된 커서 정보창을 보이게 하거나 보이지 않게 함
	bool ShowCursorInfo(int iCursorIndex, bool bShow, bool bRecvEvent);	//! 주어진 커서 index의 커서 정보창을 보이게 하거나 보이지 않게 함
	bool IsShowCursorInfoInSelected();				//! 현재 선택된 커서 정보창이 보이는 상태이면 true를 반환
	bool IsShowCursorInfo(int iCursorIndex);		//! 주어진 커서 index의 커서 정보창이 보이는 상태이면 true를 반환
	
	//! Modify by LHW [2008/7/24] : AddCursorInMouseClick, AddCursorInPosition에 iOverlapIndex 추가
	//!								iOverlapIndex가 -1이면 모든 그래프에서 커서 검색, 0이상이면 해당 그래프에서만 커서 추가
	bool AddCursorInMouseClick(bool bRecvEvent, int iOverlapIndex = -1);					//! 현재 마우스가 클릭된 지점에 커서를 새로 포함
	bool AddCursorInPosition(int iXPos, int iYPos, bool bRecvEvent, int iOverlapIndex = -1);//! 주어진 좌표의 지점에 커서를 새로 포함
	bool AddCursorInDataIndex(int iDataIndex, bool bRecvEvent, int iOverlapIndex = 0);		//! 특정 Data index에 커서를 새로 포함

	bool DeleteCursorInSelected(bool bRecvEvent);					//! 선택된 커서만 제거
	bool DeleteCursor(int iCursorIndex, bool bRecvEvent);			//! 주어진 커서 index의 커서만 제거, Modify by LHW [2008/4/19]
	bool DeleteAllCursor(bool bRecvEvent);							//! 커서 모두 제거, Modify by LHW [2008/4/19]
	bool DeleteAllCursor(int iOverlapIndex, bool bRecvEvent);		//! iOverlapIndex의 그래프와 연결된 커서 모두 제거, Added by LHW [2008/7/29]
	bool ReAdjustAllCursor(bool bSearchDirectionFlag);				//! 커서에서 범위 밖의 iOverlapIndex를 재조정, Added by LHW [2008/7/29]
																	//! bSearchDirectionFlag가 true이면 새로운 iOverlapIndex를 앞에서 부터 찾아봄
	
	bool MoveCursor(int iCursorIndex, bool bMoveRight, bool bRecvEvent, int iOverlapIndex = 0);	//! 주어진 커서 index의 커서 이동, bMoveRight가 true이면 오른쪽 이동, false이면 왼쪽 이동
	bool MoveCursor(int iCursorIndex, int iDataIndex, bool bRecvEvent, int iOverlapIndex = 0);	//! 주어진 커서 index의 커서를 주어진 Data index로 이동
	
	bool GetCursorLineMode(int iCursorIndex, E_GRAPH2D_CURSOR_LINE_MODE &eLineMode);				//! 주어진 커서 index의 커서 선 표시 방식 반환
	bool SetCursorLineMode(int iCursorIndex, E_GRAPH2D_CURSOR_LINE_MODE eLineMode, bool bRecvEvent);//! 주어진 커서 index의 커서 선 표시 방식 설정

	bool GetCursorMaxHold(int iCursorIndex, bool &bMaxHold);				//! 주어진 커서 index의 커서가 반드시 최대값에 위치하도록 설정되어 있으면 bMaxHold로 true를 반환
	bool SetCursorMaxHold(int iCursorIndex, bool bMaxHold, bool bRecvEvent);//! bMaxHold가 true이면 주어진 커서 index의 커서가 반드시 최대값에 위치하도록 설정

	bool GetCursorValue(int iCursorIndex, int &iDataIndex, double &dbValueX, double &dbValueY);	//! 주어진 커서 index의 커서의 X, Y, 데이터 index 값을 반환

	//! 주어진 데이터 index, X값을 가지고, iOverlapIndex의 그래프의 Y값을 반환
	//! bEqualInterval가 true이면 데이터가 X방향으로 간격이 같음을 의미
	//! iDataIndex가 -1이거나 해당 그래프 데이터의 iDataIndex에 해당하는 X값과 입력된 X값이 다르면,
	//! X값에 해당하는 Y값을 찾아보고, 그래도 없으면 보간법으로 계산하여 반환, Added by LHW [2008/7/24]
	bool GetDataYValue(int iDataIndex, double dbValueX, int iOverlapIndex, bool bEqualInterval, double &dbValueY);																									

	//! Added by LHW [2008/7/01]
	bool GetCursorValueString(int iCursorIndex, CString &szValueX, CString &szValueY);	//! 주어진 커서 index의 커서의 X, Y 데이터 문자열 반환
	bool GetCursorRealPrecision(int iCursorIndex, int &iPrecisionX, int &iPrecisionY);	//! 주어진 커서 index의 커서의 소수점 자리수 반환

	//! Added by LHW [2008/4/4]
	bool GetCursorSearchMargin(int iCursorIndex, int &iMargin);					//! 주어진 커서 index의 커서가 가장 가까운 데이터를 찾을 때, 찾는 구간의 여유 값 반환																						
	bool SetCursorSearchMargin(int iCursorIndex, int iMargin, bool bRecvEvent);	//! 찾는 구간의 여유 값(추가로 검색해야 할 데이터 개수) 설정, 여유 값은 m_eCursorSearchMode가 E_GRAPH2D_CURSOR_SEARCH_X_RANGE 때만 사용
	
	//! Added by LHW [2008/4/4]
	bool GetCursorValueVisible(int iCursorIndex, bool &bVisibleX, bool &bVisibleY);					//! 주어진 커서 index의 커서의 X,Y 문자열이 각각 보이거나 숨겨진 상태를 반환
	bool SetCursorValueVisible(int iCursorIndex, bool bVisibleX, bool bVisibleY, bool bRecvEvent);	//! 주어진 커서 index의 커서의 X,Y 문자열이 각각 보이거나 숨겨진 상태를 설정

	//! Added by LHW [2008/8/01]
	bool GetCursorXYStringVisible(int iCursorIndex, bool &bVisibleX, bool &bVisibleY);					//! 주어진 커서 index의 커서의 'X : ', "Y : ' 문자열이 각각 보이거나 숨겨진 상태를 반환
	bool SetCursorXYStringVisible(int iCursorIndex, bool bVisibleX, bool bVisibleY, bool bRecvEvent);	//! 주어진 커서 index의 커서의 'X : ', "Y : ' 문자열이 각각 보이거나 숨겨진 상태를 설정

	//! Added by LHW [2008/4/18]
	bool GetCursorPointVisible(int iCursorIndex, bool &bVisible);					//! 주어진 커서 index의 커서에 사각형 등의 표시로 커서 위치를 표시하는지의 여부 반환
	bool SetCursorPointVisible(int iCursorIndex, bool bVisible, bool bRecvEvent);	//! 주어진 커서 index의 커서에 사각형 등의 표시로 커서 위치를 표시하는지의 여부 설정

	//! Added by LHW [2008/4/19] : 보조 커서 내부 index를 저장해야 커서가 삭제될 때, 연결된 보조 커서가 같이 삭제됨, 초기값으로 -1이 입력되어 있음
	//! Modify by LHW [2008/6/12] : 함수명 변경
	bool GetCursorAuxCursorGroupIndex(int iCursorIndex, int &iAuxCursorGroupElementIndex);	//! 주어진 커서 index의 커서의 정보 저장소에 보조 커서 그룹의 내부 index를 반환
	bool SetCursorAuxCursorGroupIndex(int iCursorIndex, int iAuxCursorGroupElementIndex);	//! 주어진 커서 index의 커서의 정보 저장소에 보조 커서 그룹의 내부 index를 저장

	//! Added by LHW [2008/4/19] : 그래프가 보이지 않으면 커서도 같이 보이지 않게 설정하려면 true로 설정해야 함
	bool GetCursorGraphVisibleCheck(int iCursorIndex, bool &bVisibleChk);
	bool SetCursorGraphVisibleCheck(int iCursorIndex, bool bVisibleChk);

	//! Added by LHW [2009/5/30]
	bool Add_YMinBound(int iOverlapIndex, double dbInput);	//! Y축 방향 최소값을 결정할 Step 값을 추가
	bool Add_YMaxBound(int iOverlapIndex, double dbInput);	//! Y축 방향 최대값을 결정할 Step 값을 추가
	bool RemoveAll_YMinBound(int iOverlapIndex);			//! Y축 방향 최소값을 결정할 Step 값 모두 삭제
	bool RemoveAll_YMaxBound(int iOverlapIndex);			//! Y축 방향 최대값을 결정할 Step 값 모두 삭제
	bool Add_XMinBound(double dbInput);						//! X축 방향 최소값을 결정할 Step 값을 추가
	bool Add_XMaxBound(double dbInput);						//! X축 방향 최대값을 결정할 Step 값을 추가
	bool RemoveAll_XMinBound();								//! X축 방향 최소값을 결정할 Step 값 모두 삭제
	bool RemoveAll_XMaxBound();								//! X축 방향 최대값을 결정할 Step 값 모두 삭제

	//! Added by LHW [2008/4/15]
	//! 키보드의 키를 누르면 커서 이동 처리, 다른 방법으로 커서를 이동시키기 위해서는 직접 구현해야 함
	//! true가 반환되면 invalidate를 호출해야 함
	//! 왼쪽 화살표 : 커서를 데이터 한 개 뒤로 이동, 오른쪽 화살표 : 커서를 데이터 한 개 앞으로 이동
	//! 위쪽 화살표, 아래쪽 화살표 : Overlap된 그래프 사이의 이동
	//! Page UP 키 : 커서를 iMoveSize만큼 뒤로 이동, Page Down 키 : 커서를 iMoveSize만큼 앞으로 이동
	bool CursorOperationWithKeyBoard(E_GRAPH2D_KEY_TYPE eKeyType, int iMoveSize = 100);

	//! 보조 커서 관련 함수 : Added by LHW [2008/3/31]
	//! Added by LHW [2008/5/31] : GetAuxCursorValue 추가
	//! Modify by LHW [2008/6/3] : GetAuxCursorValue에 bValid 추가
	//! 보조 커서 조작 함수, iAuxCursorGroupIndex, iAuxCursorIndex는 보조 커서를 구분하는 index, 0 based
	//! SetAuxCursorInfo, GetAuxCursorInfo, SetAuxCursorGroupInfo, GetAuxCursorGroupInfo 함수는 AddAuxCursor 함수 호출 후 사용 가능
	int GetCurrentAuxCursorGroupSize();						//! 보조 커서 그룹의 개수 반환
	int GetCurrentAuxCursorSize(int iAuxCursorGroupIndex);	//! iAuxCursorGroupIndex에 해당하는 보조 커서 그룹의 보조 커서 개수 반환	
	int AddAuxCursor(strGraph2D_Aux_Cursor strAuxCursorInfo, int iAuxCursorGroupIndex = -1);//! 새로운 보조 커서 추가하고 보조 커서가 소속된 보조 커서 그룹 index를 반환
																							//! iAuxCursorGroupIndex가 0 이상의 정수이면 해당 index의 보조 커서 그룹에 추가
																							//! iAuxCursorGroupIndex가 -1이면 보조 커서 그룹을 새로 생성하고 보조 커서 추가
	bool SetAuxCursorInfo(int iAuxCursorGroupIndex, int iAuxCursorIndex, strGraph2D_Aux_Cursor strAuxCursorInfo);	//! 보조 커서의 정보 설정
	bool GetAuxCursorInfo(int iAuxCursorGroupIndex, int iAuxCursorIndex, strGraph2D_Aux_Cursor &strAuxCursorInfo);	//! 보조 커서의 정보 반환
	bool SetAuxCursorGroupInfo(int iAuxCursorGroupIndex, strGraph2D_Aux_CursorGroup strAuxCursorGroupInfo);	//! 보조 커서 그룹의 정보 설정
	bool GetAuxCursorGroupInfo(int iAuxCursorGroupIndex, strGraph2D_Aux_CursorGroup &strAuxCursorGroupInfo);//! 보조 커서 그룹의 정보 반환	
	bool ChangeAuxCursorGroupOverlapIndex(int iAuxCursorGroupIndex, int iOverlapIndex);	//! 보조 커서 그룹 전체의 Overlap index 변경, Added by LHW [2008/7/27]
	//! 주어진 보조 커서 index의 커서의 X, Y, 데이터 index 값을 반환
	bool GetAuxCursorValue(int iAuxCursorGroupIndex, int iAuxCursorIndex, bool &bValid, int &iDataIndex, double &dbValueX, double &dbValueY);
	bool MoveAuxCursor(int iAuxCursorGroupIndex, int iAuxCursorIndex, int iDataIndex, int iOverlapIndex = 0);	//! 보조 커서를 새로운 위치에 설정, Added by LHW [2008/8/5]
	bool IsCurrentAuxCursorSelect(int &iSelectAuxCursorGroupIndex, int &iSelectAuxCursorIndex);	//! Added by LHW [2008/8/5], 현재 선택된 보조 커서의 index를 반환
																								//! 현재 선택된 보조 커서가 없으면 인자로 -1을 반환
																								//! 현재 보조 커서가 없으면 false를 반환
	bool IsAuxCursorSelected(int &iSelectAuxCursorGroupIndex, int &iSelectAuxCursorIndex);	//! Added by LHW [2008/8/5], 현재 선택된 커서의 index를 반환
																							//! 현재 보조 커서가 없으면 false를 반환
																							//! IsCurrentAuxCursorSelect와는 달리 현재 선택된 커서가 없으면 마지막으로 선택된 커서의 index값을 반환
	bool RemoveOneAuxCursor(int iAuxCursorGroupIndex, int iAuxCursorIndex);	//! 특정 보조 커서 삭제
	bool RemoveOneAuxCursorGroup(int iAuxCursorGroupIndex);					//! 특정 보조 커서 그룹 삭제
	void RemoveAllAuxCursor();												//! 보조 커서 모두 삭제

	//! 아래의 MakeFrom~ 함수들은 X축 데이터가 등간격이고 , X-Y 데이터가 1:1 대응 인 것을 전제로 함

	//! Added by LHW [2008/4/10]
	//! iOverlapIndex는 Overlap되는 그래프의 index (0 based)
	//! 입력된 Y축 데이터에서 큰 순서대로 iAuxCursorSize 개 만큼 보조 커서를 추가하고, iAuxCursorGroupIndex를 반환
	bool MakeFromMaxValuesToAuxCursor(int iAuxCursorSize, int &iAuxCursorGroupIndex, int iOverlapIndex = 0);
	//! 주어진 Threshold 값보다 큰 Y축 데이터들을 보조 커서로 추가하고, iAuxCursorGroupIndex를 반환
	//! Modify by LHW [2008/9/1] : iMaxAddSize 추가, Threshold 값보다 큰 Y축 데이터의 보조 커서 최대 개수를 설정
	//!												-1이면 Threshold보다 큰 모든 값을 보조 커서로 추가
	bool MakeFromThresholdToAuxCursor(double dbThreshold, int iMaxAddSize, int &iAuxCursorGroupIndex, int iOverlapIndex = 0);

	//! Added by LHW [2008/4/28]
	//! iOverlapIndex는 Overlap되는 그래프의 index (0 based)
	//! 입력된 Y축 데이터의 Peak값에서 큰 순서대로 iAuxCursorSize 개 만큼 보조 커서를 추가하고, iAuxCursorGroupIndex를 반환
	bool MakeFromMaxPeakValuesToAuxCursor(int iAuxCursorSize, int &iAuxCursorGroupIndex, int iOverlapIndex = 0);

	//! 자식 커서 관련, Added by LHW [2008/6/13]
	//! Added by LHW [2008/6/15] : MoveChildCursor 추가
	int GetCurrentChildCursorSize();								//! 자식 커서 개수 반환
	bool IsCurrentChildCursorSelect(int &iSelectChildCursorIndex);	//! 현재 선택된 자식 커서의 index를 iSelectCursorIndex로 반환
																	//! 현재 선택된 자식 커서가 없으면 iSelectCursorIndex로 -1을 반환
																	//! 현재 자식 커서가 없으면 false를 반환
	bool IsChildCursorSelected(int &iSelectChildCursorIndex);		//! 현재 선택된 커서의 index를 iSelectChildCursorIndex로 반환, Added by LHW [2008/6/14]
																	//! 현재 커서가 없으면 false를 반환
																	//! IsCurrentChildCursorSelect와는 달리 현재 선택된 커서가 없으면 마지막으로 선택된 커서의 index값을 반환
	bool IsExistChildCursor(int iElementCursorIndex);				//! 주어진 iElementCursorIndex의 커서와 연결된 자식 커서가 있으면 true를 반환, Added by LHW [2008/6/16]
	int AddChildCursor(strGraph2D_Child_Cursor strChildCursor);	//! 자식 커서 추가
	bool SetChildCursorInfo(int iChildCursorIndex, strGraph2D_Child_Cursor strChildCursor);	//! 자식 커서의 정보 설정
	bool GetChildCursorInfo(int iChildCursorIndex, strGraph2D_Child_Cursor &strChildCursor);//! 자식 커서의 정보 반환
	bool MoveChildCursor(int iChildCursorIndex, int iDataIndex, int iOverlapIndex = 0);	//! 주어진 iChildCursorIndex의 자식 커서를 주어진 Data index로 이동	
	//! 주어진 자식 커서 index의 커서의 X, Y, 데이터 index 값을 반환
	bool GetChildCursorValue(int iChildCursorIndex, bool &bValid, int &iDataIndex, double &dbValueX, double &dbValueY, double &dbDeltaX, double &dbDeltaY);
	bool RemoveOneChildCursor(int iChildCursorIndex);	//! 특정 자식 커서 삭제
	void RemoveChildCursor(int iElementCursorIndex);	//! 주어진 iElementCursorIndex의 커서와 연결된 모든 자식 커서 삭제
	void RemoveAllChildCursor();						//! 자식 커서 모두 삭제

	//! 영역 표시 커서 관련, Added by LHW [2008/11/28]
	int GetCurrentRegionCursorSize();
	bool IsCurrentRegionCursorSelect(int &iSelectRegionCursorIndex);
	bool IsRegionCursorSelected(int &iSelectRegionCursorIndex);
	int AddRegionCursor(strGraph2D_Region_Cursor strRegionCursor, bool bChkOverlapIndex = true);	//! Modify by LHW [2008/12/16] : bChkOverlapIndex 추가
	bool SetRegionCursorInfo(int iRegionCursorIndex, strGraph2D_Region_Cursor strRegionCursor);
	bool GetRegionCursorInfo(int iRegionCursorIndex, strGraph2D_Region_Cursor &strRegionCursor);
	bool MoveRegionCursor(int iRegionCursorIndex, double dbInputMinX, double dbInputMaxX, double dbInputMinY, double dbInputMaxY);
	bool GetRegionCursorValue(int iRegionCursorIndex, double &dbOutputMinX, double &dbOutputMaxX, double &dbOutputMinY, double &dbOutputMaxY);
	bool RemoveOneRegionCursor(int iRegionCursorIndex);
	void RemoveAllRegionCursor();
	
	//! 확대/축소 관련 함수
	//! Modify by LHW [2008/4/19] : bRecvEvent 추가, Zoom 이벤트를 받아 처리할 때는 {{반드시}} true로 해야 함, 그 이외에는 false로 설정
	bool ZoomArea(CRect crZoomArea, bool bRecvEvent, E_GRAPH2D_ZOOM_DIRECTION eMode = E_GRAPH2D_ZOOM_DIRECTION_XY);	//! 주어진 사각 영역만큼 그래프를 확대
	bool ZoomX(double dbMin, double dbMax, bool bRecvEvent);//! Added by LHW [2009/2/14]
	bool ZoomY(bool bRecvEvent);							//! Added by LHW [2009/2/14]
	bool ZoomOut(bool bRecvEvent = false);			//! 전의 확대 상태로 변경
	bool IsZoomIn();								//! 마우스로 선택하여 확대된 상태이면 true를 반환
	//! bDirectionX가 true이면 X축 방향으로 Auto Range 상태, bDirectionY가 true이면 Y축 방향으로 Auto Range 상태
	bool ZoomFirstBack(bool bDirectionX, bool bDirectionY, bool bRecvEvent = false);//! 확대 기능을 하기 전의 맨 처음 상태로 변경, Modify by LHW [2008/4/17]	
	bool ZoomFit(bool bDirectionX, bool bDirectionY, bool bRecvEvent = false);		//! 전체 그래프를 모두 Auto Range로 설정, Modify by LHW [2008/4/17]

	//! Pan 관련 함수	
	bool IsPanOperated();							//! 현재 Pan 기능을 사용하여 그래프를 평행 이동한 상태이면 true를 반환

	//! X축 특정값 표시선 관련 함수, iLineIndex는 선을 구분하는 index, 0 based, Added by LHW [2008/4/19]
	int GetXValueLineSize();												//! X축 특정값 표시선의 개수 반환
	bool SetXValueLineInfo(int iLineIndex, strValueLineXInfo strXLineInfo);	//! X축 특정값 표시선 정보 설정
	bool GetXValueLineInfo(int iLineIndex, strValueLineXInfo &strXLineInfo);//! X축 특정값 표시선 정보 반환
	int AddXValueLine(strValueLineXInfo strXLineInfo);						//! 새로운 X축 특정값 표시선 추가, Line index를 반환
	bool RemoveOneXValueLine(int iLineIndex);								//! 특정 Line index의 X축 특정값 표시선 삭제
	void RemoveAllXValueLine();												//! 모든 X축 특정값 표시선 삭제

	//! Y축 특정값 표시선 관련 함수, iLineIndex는 선을 구분하는 index, 0 based, Added by LHW [2008/3/29]
	int GetYValueLineSize();												//! Y축 특정값 표시선의 개수 반환
	bool SetYValueLineInfo(int iLineIndex, strValueLineYInfo strYLineInfo);	//! Y축 특정값 표시선 정보 설정
	bool GetYValueLineInfo(int iLineIndex, strValueLineYInfo &strYLineInfo);//! Y축 특정값 표시선 정보 반환
	int AddYValueLine(strValueLineYInfo strYLineInfo);						//! 새로운 Y축 특정값 표시선 추가, Line index를 반환
	bool RemoveOneYValueLine(int iLineIndex);								//! 특정 Line index의 Y축 특정값 표시선 삭제
	void RemoveAllYValueLine();												//! 모든 Y축 특정값 표시선 삭제

	//! 함수식으로 그려지는 그래프 관련 함수, Added by LHW [2008/8/23]
	int GetGraphEquationSize();															//! 함수식으로 그려지는 그래프 개수 반환
	bool SetGraphEquationInfo(int iGraphIndex, strGraph2DEquationInfo strEquationInfo);	//! 함수식으로 그려지는 그래프 정보 설정
	bool GetGraphEquationInfo(int iGraphIndex, strGraph2DEquationInfo &strEquationInfo);//! 함수식으로 그려지는 그래프 정보 반환																						
	int AddGraphEquation(strGraph2DEquationInfo strEquationInfo);						//! 함수식으로 그려지는 그래프 추가, Graph index를 반환
	bool RemoveOneGraphEquation(int iGraphIndex);										//! 특정 Graph index의 함수식으로 그려지는 그래프 삭제
	void RemoveAllGraphEquation();														//! 모든 함수식으로 그려지는 그래프 삭제
	
	//! Plot의 현재 상태 정보를 반환하는 함수
	//! iOverlapIndex는 Overlap되는 그래프의 index (0 based)
	//! Modify by LHW [2008/4/2] : bShow가 true이면 눈에 보이도록 설정된 그래프만 고려하여 해당 상태 정보를 반환
	//! Modify by LHW [2008/8/25] : bEquation가 true이면 함수식으로 그려지는 그래프를 고려하여 해당 상태 정보를 반환하도록 수정
	int GetGraphWidth();		//! 그래프의 실제 폭, pixel 단위로 반환
	int GetGraphHeight();		//! 그래프의 실제 높이, pixel 단위로 반환
	int GetRealDataSize(bool bShow = false);		//! 그래프 데이터의 개수 최대값을 반환
	int GetRealDataSize(int iOverlapIndex, bool bShow = false);	//! 해당 그래프의 데이터 개수를 반환, 인자값이 잘못되었으면 음수를 반환, Added by LHW [2008/8/02]
	int GetRealVisualDataSize(bool bShow = false);	//! 눈에 보이는 그래프 데이터의 개수 최대값을 반환
	int GetRealVisualDataSize(int iOverlapIndex, bool bShow = false);	//! 해당 그래프의 눈에 보이는 데이터 개수를 반환, 인자값이 잘못되었으면 음수를 반환, Added by LHW [2008/11/18]
	bool GetVisualDataIndex(int iOverlapIndex, int &iStartDataIndex, int &iEndDataIndex);	//! 해당 그래프의 눈에 보이는 데이터 index를 반환, Added by LHW [2008/11/18]
	//! Modify by LHW [2008/12/14] : 영역 표시 커서 고려하는 기능 추가
	double GetRealMinX(bool bEquation, bool bRegionCursor, bool bShow = false);	//! 그래프 데이터 버퍼 m_arrPlotData에 입력된 데이터들의 X 최소값, 버퍼에 데이터가 없으면 0을 반환
	double GetRealMaxX(bool bEquation, bool bRegionCursor, bool bShow = false);	//! 그래프 데이터 버퍼 m_arrPlotData에 입력된 데이터들의 X 최대값, 버퍼에 데이터가 없으면 0을 반환
	double GetRealMinY(bool bEquation, bool bYValueLine, bool bRegionCursor, bool bShow = false);	//! 그래프 데이터 버퍼 m_arrPlotData에 입력된 데이터들의 Y 최소값, 버퍼에 데이터가 없으면 0을 반환
																				//! bEquation가 true이면 함수식으로 그려지는 그래프가 모두 보이도록 Y축 최소값을 반환
																				//! bYValueLine가 true이면 Y축 특정값 표시선이 모두 보이도록 Y 최소값을 반환
																				//! bRegionCursor가 true이면 영역 표시 커서가 모두 보이도록 Y 최소값을 반환
	double GetRealMaxY(bool bEquation, bool bYValueLine, bool bRegionCursor, bool bShow = false);	//! 그래프 데이터 버퍼 m_arrPlotData에 입력된 데이터들의 Y 최대값, 버퍼에 데이터가 없으면 0을 반환
																				//! bEquation가 true이면 함수식으로 그려지는 그래프가 모두 보이도록 Y축 최대값을 반환
																				//! bYValueLine가 true이면 Y축 특정값 표시선이 모두 보이도록 Y 최대값을 반환
																				//! bRegionCursor가 true이면 영역 표시 커서가 모두 보이도록 Y 최대값을 반환
	double GetRealMinY(int iOverlapIndex);		//! 그래프 데이터 버퍼 m_arrPlotData에 입력된 데이터들의 Y 최소값, Added by LHW [2008/7/28]
	double GetRealMaxY(int iOverlapIndex);		//! 그래프 데이터 버퍼 m_arrPlotData에 입력된 데이터들의 Y 최대값, Added by LHW [2008/7/28]
	double GetVisualMinX();						//! 눈에 보이는 그래프의 X축 최소값, Added by LHW [2008/4/18]
	double GetVisualMaxX();						//! 눈에 보이는 그래프의 X축 최대값, Added by LHW [2008/4/18]
	bool GetVisualMinY(double &dbMinY, int iOverlapIndex = 0);	//! 눈에 보이는 그래프의 Y축 최소값, Added by LHW [2008/4/18]
	bool GetVisualMaxY(double &dbMaxY, int iOverlapIndex = 0);	//! 눈에 보이는 그래프의 Y축 최대값, Added by LHW [2008/4/18]
	bool GetAutoRangeMinX(double &dbMinX);							//! Auto Range일 때의 X축 최소값 반환, Margin등이 고려된 값, Added by LHW [2008/7/02]
	bool GetAutoRangeMaxX(double &dbMaxX);							//! Auto Range일 때의 X축 최대값 반환, Margin등이 고려된 값, Added by LHW [2008/7/02]
	bool GetAutoRangeMinY(double &dbMinY, int iOverlapIndex = 0);	//! Auto Range일 때의 Y축 최소값 반환, Margin등이 고려된 값, Added by LHW [2008/7/02]
	bool GetAutoRangeMaxY(double &dbMaxY, int iOverlapIndex = 0);	//! Auto Range일 때의 Y축 최대값 반환, Margin등이 고려된 값, Added by LHW [2008/7/02]

	//! 아래 사항을 반영하려면 반드시 m_bChanged를 true로 하고 다시 그려주어야 함
	bool m_bAutoRangeY_UsingRangeX;			//! true이면 m_dbMinX_AutoRangeY, m_dbMaxX_AutoRangeY 사이의 X값에 해당하는 Y값을 가지고, Auto Range 설정, Added by LHW [2009/3/5]
	double m_dbMinX_AutoRangeY;				//! Y축 Auto Range에 사용될 X축 최소값, Added by LHW [2009/3/5]
	double m_dbMaxX_AutoRangeY;				//! Y축 Auto Range에 사용될 X축 최대값, Added by LHW [2009/3/5]
	bool GetMinY_UsingRangeX(double &dbMinY, int iOverlapIndex = 0);//! m_dbMinX_AutoRangeY, m_dbMaxX_AutoRangeY 사이의 Y축 최소값 반환, Added by LHW [2009/3/5]
	bool GetMaxY_UsingRangeX(double &dbMaxY, int iOverlapIndex = 0);//! m_dbMinX_AutoRangeY, m_dbMaxX_AutoRangeY 사이의 Y축 최대값 반환, Added by LHW [2009/3/5]

	//! 해당 그래프의 최대값의 index를 반환, 오류가 발생하면 -1을 반환
	int GetDataIndexofMaxValue(int iOverlapIndex);												//! 데이터 전체 구간에서의 최대값, Added by LHW [2008/4/15]
	int GetDataIndexofMaxValue(int iOverlapIndex, int iStartDataIndex, int iEndDataIndex);		//! 주어진 Data Index사이에서의 최대값, Added by LHW [2009/2/27]
	int GetDataIndexofMaxValue(int iOverlapIndex, double dbStartValue, double dbEndValue);		//! 주어진 X축 값 사이의 최대값, Added by LHW [2009/2/27]
	int GetDataIndexofMaxValue(int iOverlapIndex, COleDateTime timeStart, COleDateTime timeEnd);//! 주어진 X축 값 사이의 최대값, Added by LHW [2009/2/27]

	bool IsAutoRange(bool bDirectionX, bool bDirectionY, bool bShow = false);	//! 하나라도 Manual Range로 설정되어 있으면 false를 반환
																				//! bDirectionX가 true이면 X방향으로 확인
																				//! bDirectionY가 true이면 Y방향으로 확인
	bool IsShowGraph();			//! 하나라도 그래프가 보이면 true를 반환
	bool IsScreenDrawing();		//! 현재 WM_PAINT 메시지를 받아 OnPaint()에서 그래프를 그리는 중이면 true로 반환

	//! 내부 index와 index 사이의 변환 관계, 내부 index는 절대 중복되지 않는 고유 index, 구별자로 사용 가능, Added by LHW [2008/4/11]
	//! Added by LHW [2008/6/13] : GetChildCursorIndexFromElementIndex, GetChildCursorElementIndexFromIndex 추가
	//! Added by LHW [2008/8/23] : GetGraphEquationIndexFromElementIndex, GetGraphEquationElementIndexFromIndex 추가
	//! Added by LHW [2008/11/28] : GetRegionCursorIndexFromElementIndex, GetRegionCursorElementIndexFromIndex 추가
	//! 입력된 내부 index, iElementIndex에 대한 실제 index를 반환
	bool GetCursorIndexFromElementIndex(int iElementIndex, int &iIndex);
	bool GetAuxCursorGroupIndexFromElementIndex(int iElementIndex, int &iIndex);
	bool GetChildCursorIndexFromElementIndex(int iElementIndex, int &iIndex);
	bool GetResourceYIndexFromElementIndex(int iElementIndex, int &iIndex);
	bool GetDataBufferIndexFromElementIndex(int iElementIndex, int &iIndex);
	bool GetXValueLineIndexFromElementIndex(int iElementIndex, int &iIndex);
	bool GetYValueLineIndexFromElementIndex(int iElementIndex, int &iIndex);
	bool GetGraphEquationIndexFromElementIndex(int iElementIndex, int &iIndex);
	bool GetRegionCursorIndexFromElementIndex(int iElementIndex, int &iIndex);
	//! 실제 index에 대해 내부 index, iElementIndex를 반환
	bool GetCursorElementIndexFromIndex(int iIndex, int &iElementIndex);
	bool GetAuxCursorGroupElementIndexFromIndex(int iIndex, int &iElementIndex);
	bool GetChildCursorElementIndexFromIndex(int iIndex, int &iElementIndex);
	bool GetResourceYElementIndexFromIndex(int iIndex, int &iElementIndex);
	bool GetDataBufferElementIndexFromIndex(int iIndex, int &iElementIndex);
	bool GetXValueLineElementIndexFromIndex(int iIndex, int &iElementIndex);
	bool GetYValueLineElementIndexFromIndex(int iIndex, int &iElementIndex);
	bool GetGraphEquationElementIndexFromIndex(int iIndex, int &iElementIndex);
	bool GetRegionCursorElementIndexFromIndex(int iIndex, int &iElementIndex);

	//! Added by LHW [2008/4/3]
	//! Modify by LHW [2008/7/02] : protected에서 public으로 변경
	//! 주어진 데이터값을 현재 설정된 포맷에 따라 Grid 눈금의 표시 글자, 커서의 표시 글자로 반환
	//! bDirectionX : X축 값이면 true, bSecondRow : Time이고 2줄로 표시할 때 2번째 줄이면 true, bCursorText : 커서 값이면 true
	//! Overlap되는 데이터의 index(iOverlapIndex)는 0 based이고 Y축 값일 때만 사용
	CString GetVisualDataText(double dbData, bool bDirectionX, bool bSecondRow, bool bCursorText, int iOverlapIndex = 0);

	CString GetDeltaTimeText(double dbDeltaTime);	//! Added by LHW [2008/8/11], 시간 차를 문자열로 반환
	
	
protected:
	int m_iPlotIndex;					//! 그래프 번호

	CGraph2D_Resource *m_pPlotResource;	//! 리소스 객체
	bool m_bSelfCreateResourcePtr;		//! 직접 리소스 객체를 생성하면 true

	strXRangeMapper	m_XMapper;													//! 데이터를 화면 상의 X 좌표로 계산
	CArray<strYRangeMapper, strYRangeMapper&> m_arrYMapper;						//! 데이터를 화면 상의 Y 좌표로 계산
	CTypedPtrArray<CPtrArray, CGraph2D_ResourceY*> m_arrResourceY;				//! Y축 방향의 리소스 데이터 저장소
	CTypedPtrArray<CPtrArray, CGraph2D_Data*> m_arrPlotData;					//! 그래프 데이터 저장소
	CTypedPtrArray<CPtrArray, CGraph2D_ValueLineX*> m_arrValueLineX;			//! X축 특정 값 표시선 정보 저장소, Added by LHW [2008/4/19]
	CTypedPtrArray<CPtrArray, CGraph2D_ValueLineY*> m_arrValueLineY;			//! Y축 특정 값 표시선 정보 저장소, Added by LHW [2008/3/29]
	CArray<strGraph2DCursorInfo, strGraph2DCursorInfo&> m_arrCursor;			//! 커서 정보 구조체
	CTypedPtrArray<CPtrArray, CGraph2D_Aux_CursorGroup*> m_arrAuxCursorGroup;	//! 보조 커서 정보 저장소, Added by LHW [2008/3/31]
	CTypedPtrArray<CPtrArray, CGraph2D_Child_Cursor*> m_arrChildCursor;			//! 자식 커서 정보 저장소, Added by LHW [2008/6/13]
	CTypedPtrArray<CPtrArray, CGraph2D_Equation*> m_arrGraphEquation;			//! 함수식으로 그려지는 그래프의 정보 저장소, Added by LHW [2008/8/22]
	CTypedPtrArray<CPtrArray, CGraph2D_Region_Cursor*> m_arrRegionCursor;		//! 영역 표시 커서 정보 저장소, Added by LHW [2008/11/28]
	
	bool IsValidCursorIndex(int iCursorIndex);						//! iCursorIndex의 커서가 유효하면 true를 반환, Added by LHW [2008/6/15]
	bool IsValidOverlapIndex(int iOverlapIndex);					//! iOverlapIndex의 그래프가 현재 사용 가능하면 true를 반환
	bool IsValidXValueLineIndex(int iLineIndex);					//! iLineIndex의 X축 특정값 표시선이 유효하면 true를 반환
	bool IsValidYValueLineIndex(int iLineIndex);					//! iLineIndex의 Y축 특정값 표시선이 유효하면 true를 반환
	bool IsValidChildCursorIndex(int iChildCursorIndex);			//! iChildCursorIndex가 유효하면 true를 반환, Added by LHW [2008/6/14]
	bool IsValidGraphEquationIndex(int iGraphIndex);				//! iGraphIndex가 유효하면 true를 반환, Added by LHW [2008/8/23]
	bool IsValidRegionCursorIndex(int iRegionCursorIndex);			//! iRegionCursorIndex가 유효하면 true를 반환, Added by LHW [2008/11/28]

	E_GRAPH2D_MOVE_CURSOR_TYPE m_eSelectCursorType;					//! 현재 마우스, 키보드로 마지막으로 움직인 커서의 종류, Added by LHW [2008/6/16]
	
	int m_iSelectCursorIndex;										//! 현재 선택된 커서의 Index
	int m_iSelectedCursorIndex;										//! 마지막으로 선택된 커서의 index

	bool m_bCursorSelected;			//! 커서가 선택되어 움직이는 중이면 true
	bool m_bCursorOverlap;			//! true이면 Overlap된 그래프 모두의 데이터 검색, false이면 현재 선택된 그래프 데이터에서만 검색
									//! 현재, 커서의 데이터 점을 클릭하면 true로 설정되게 되어 있음
	bool m_bCursorInfoSelected;		//! 커서 정보창이 선택되어 움직이는 중이면 true
	CPoint m_ptSave;				//! 마우스가 오른쪽 클릭된 지점을 저장, AddCursorInMouseClick 함수에서 사용
	int m_iCursorMargin;			//! 커서 관련 처리에 필요한 여유 pixel 값

	strGraph2D_MouseDown_Info m_strMouseDownInfo;				//! 마우스 클릭한 지점등을 저장
	strGraph2D_Cursor_Event m_strCursorEventInfo;				//! 커서 관련 이벤트 정보 저장
	strGraph2D_DataPoint_Event m_strDataPointEventInfo;			//! 그래프의 점에서 발생한 이벤트 정보 저장, Added by LHW [2008/5/23]
	strGraph2D_Aux_Cursor_Event m_strAuxCursorEventInfo;		//! 보조 커서 관련 이벤트 정보 저장, Added by LHW [2008/8/5]
	strGraph2D_Region_Cursor_Event m_strRegionCursorEventInfo;	//! 영역 표시 커서 관련 이벤트 정보 저장, Added by LHW [2008/11/28]

	int m_bMouseMoveProcessing;	//! 마우스가 움직여서 커서 관련 작업을 하는 동안 true로 설정, 부하를 줄이기 위해 사용, Added by LHW [2008/7/24]
	
	bool CalcCursorPos(int iXPos, int iYPos, bool bAddCursorFlag, strGraph2DCursorInfo* pstrCursorInfo);	//! 커서 위치 계산
								//! 커서 추가일 때는 bAddCursorFlag는 true이어야 함, Modify by LHW [2008/4/17]
	bool SetCursorInfo(int iCursorDataIndex, strGraph2DCursorInfo* pstrCursorInfo, int iOverlapIndex = 0);	//! 주어진 Data index에 해당하는 정보를 커서 구조체에 설정
	void ReCalcCursorPos();		//! MouseMove 시 커서 위치 다시 계산, 그래프 크기 변화에 따른 커서의 위치 다시 계산
	bool SendCursorEventMsg(int iCursorIndex, bool bMouseOperation, E_GRAPH2D_CURSOR_OPERATION_MODE eOperationMode, strGraph2DCursorInfo* pstrCursorInfo);	//! 커서 이벤트 메시지 발송
								//! iCursorIndex : 커서 index, bMouseOperation : 마우스로 발생한 이벤트이면 true
								//! eOperationMode : 커서의 동작 종류

	//! 자식 커서의 위치, 데이터 관련 처리, Added by LHW [2008/6/13]
	int m_iSelectChildCursorIndex;	//! 현재 선택된 자식 커서의 Index
	int m_iSelectedChildCursorIndex;//! 마지막으로 선택된 자식 커서의 index, Added by LHW [2008/6/14]
	bool m_bChildCursorSelected;	//! 자식 커서가 선택되어 움직이는 중이면 true
	bool m_bChildCursorOverlap;		//! true이면 Overlap된 그래프 모두의 데이터 검색, false이면 현재 선택된 그래프 데이터에서만 검색
									//!  현재, 자식 커서의 데이터 점을 클릭하면 true로 설정되게 되어 있음
	bool m_bChildCursorInfoSelected;//! 자식 커서 정보창이 선택되어 움직이는 중이면 true
	int m_iChildCursorMargin;		//! 자식 커서 관련 처리에 필요한 여유 pixel 값
	bool CalcChildCursorPos(int iXPos, int iYPos, bool bAddCursorFlag, int iChildCursorIndex);	//! 자식 커서 위치 계산
																								//! 커서 추가일 때는 bAddCursorFlag는 true이어야 함
	//! 주어진 Data index에 해당하는 정보를 설정
	//! Modify by LHW [2008/6/16] : bAddFlag 추가, 자식 커서를 새로 추가할 때는 bAddFlag를 true로 설정
	bool SetChildCursorInfo(int iChildCursorDataIndex, int iChildCursorIndex, bool bAddFlag, int iOverlapIndex = 0);
	void ReCalcChildCursorPos();//! MouseMove 시 자식 커서 위치 다시 계산, 그래프 크기 변화에 따른 자식 커서의 위치 다시 계산

	//! 커서와 자식 커서의 연동, Added by LHW [2008/6/15]
	bool SetFlag_If_CursorMoved(int iCursorIndex);	//! iCursorIndex의 커서가 움직였을 경우
	//bool UpdateCursorDataIndex_Childcursor();		//! 커서의 데이터 index를 자식 커서에 반영

	//! 영역 표시 커서의 위치, 데이터 관련 처리, Added by LHW [2008/11/28]
	//! Modify by LHW [2008/11/30] : iRegionCursorLineIndex, m_iSelectRegionCursorLineIndex, m_iRegionCursorMargin 추가
	//! Modify by LHW [2008/12/1] : SendRegionCursorEventMsg 추가
	int m_iSelectRegionCursorIndex;		//! 현재 선택된 영역 표시 커서의 Index
	int m_iSelectedRegionCursorIndex;	//! 마지막으로 선택된 영역 표시 커서의 index
	int m_iSelectRegionCursorLineIndex;	//! 현재 선택된 영역 표시 커서의 커서 선의 Index
	int m_iRegionCursorMargin;			//! 영역 표시 커서 관련 처리에 필요한 여유 pixel 값
	bool m_bRegionCursorSelected;		//! 영역 표시 커서가 선택되어 움직이는 중이면 true
	bool CalcRegionCursorPos(int iXPos, int iYPos, int iRegionCursorIndex, int iRegionCursorLineIndex);
	bool CalcRegionCursor();
	bool SendRegionCursorEventMsg(int iRegionCursorIndex);

	//! 보조 커서의 위치, 데이터 관련 처리
	bool CalcAuxCursorPos(int iXPos, int iYPos, int iAuxCursorGroupIndex, int iAuxCursorIndex);	//! 보조 커서의 위치 계산, Added by LHW [2008/8/5]
	bool CalcAuxCursor();		//! 보조 커서의 X값에 대해 Y값과 X, Y 위치를 계산 설정, Added by LHW [2008/4/1]
	//! Added by LHW [2008/8/4]
    bool m_bAuxCursorSelected;	//! 보조 커서가 선택되어 움직이는 중이면 true
	int m_iSelectAuxCursorGroupIndex;	//! 현재 선택된 보조 커서 그룹의 index
	int m_iSelectedAuxCursorGroupIndex;	//! 마지막으로 선택된 보조 커서 그룹의 index
	int m_iSelectAuxCursorIndex;		//! 현재 선택된 보조 커서의 index
	int m_iSelectedAuxCursorIndex;		//! 마지막으로 선택된 보조 커서의 index

	bool m_bLeftMouseDown;		//! true이면 왼쪽 마우스 다운 상태, Added by LHW [2008/5/28]
	bool m_bRightMouseDown;		//! true이면 오른쪽 마우스 다운 상태, Added by LHW [2009/2/2]
	bool m_bMouseMoved;			//! true이면 OnMouseMove가 호출된 상태, Added by LHW [2009/2/2]

	bool m_bZoomMouseDown;		//! true이면 Zoom을 위한 사각 영역 설정 중
	bool m_bPanMouseDown;		//! true이면 Pan 실제 동작 중
	bool m_bAxisEventFront;		//! true이면 마우스 이벤트가 발생한 위치가 축의 앞쪽임을 의미, Added by LHW [2009/2/2]

	strGraph2D_Zoom_Event m_strZoomEventInfo;	//! Zoom 관련 이벤트 정보 저장
	bool SendZoomEventMsg(E_GRAPH2D_ZOOM_OPERATION_MODE eZoomMode);	//! Zoom 이벤트 메시지 발송, Added by LHW [2008/4/19]

	bool SetDataPointRect();		//! 그래프의 각 점의 이벤트 사각 영역을 설정

	int m_iPanOffsetX;				//! Pan 기능에서 X축 방향으로의 Offset값
	int m_iPanOffsetY;				//! Pan 기능에서 Y축 방향으로의 Offset값
	strPanPosition m_strPanPosition;//! Pan 기능에서 마우스로 선택한 시작점과 마침점의 좌표
	bool ApplyPanPosition();		//! m_strPanPosition의 값으로 Range Offset값들을 수정

	double GetCalcData(double dbData, bool bDirectionX, bool bCursorText, int iOverlapIndex = 0);//! 연산되어 실제 보여지는 데이터를 반환, Added by LHW [2008/8/02]

	double GetFloor(double dbInput, int iResultMode);	//! 소수점 반올림 함수
														//! [iResultMode] 0 이상의 정수 가능 
														//! (예. 1 : 소수점 2째 자리에서 반올림, 2 : 소수점 3째 자리에서 반올림)
	
	//! 점 (iX1, iY1), 점 (iX2, iY2)이 직선으로 연결되어 있을 때, 그 사이의 점 iInputX의 Y좌표를 계산하여 반환, Added by LHW [2008/4/1]
	int CalcLinearInterpolate(int iX1, int iY1, int iX2, int iY2, int iInputX);

	double CalcPolynomialEquation(double *pdbCoeff, int iCoeffSize, double dbInput);	//! 주어진 계수를 가진 다항식의 입력값에 대한 출력값을 반환, Added by LHW [2008/8/23]

	double DecideMinMaxOperation(double dbInput);	//! 입력된 최소, 최대값을 일정한 규칙에 따라 새로운 최소, 최대값을 구하여 반환, Added by LHW [2009/2/4]
													//! 최대값은 입력값이 양수일 때, 최소값은 입력값이 음수일 때만 사용 가능
													//! 그래프의 눈금을 보기 좋게 하기 위해 사용

	//! Added by LHW [2009/3/1]
	//! 주어진 Data Index에 해당하는 X축 데이터와 가장 근접하는 Data Index를 알아냄, iMargin이 0이면 모든 데이터 검색
	bool SearchEqualValueX(int iOverlapIndex1, int iDataIndex1, int iOverlapIndex2, int &iDataIndex2, int iMargin = 0);

	//! Added by LHW [2009/5/30]
	//! X축 방향 Step 값이 없으면 입력값을 그대로 반환
	double GetCompareXMinBound(double dbInput);	//! 주어진 값과 X축 방향 Step 값들을 비교하여 최소값 반환
	double GetCompareXMaxBound(double dbInput);	//! 주어진 값과 X축 방향 Step 값들을 비교하여 최대값 반환

	//! Added by LHW [2009/5/30]
	//! 주어진 iOverlapIndex의 Y축 방향 Step 값이 없으면 입력값을 그대로 반환
	double GetCompareYMinBound(int iOverlapIndex, double dbInput);	//! 주어진 값과 Y축 방향 Step 값들을 비교하여 최소값 반환
	double GetCompareYMaxBound(int iOverlapIndex, double dbInput);	//! 주어진 값과 Y축 방향 Step 값들을 비교하여 최대값 반환

	//! Added by LHW [2008/4/4]
	//! 주어진 iOverlapIndex의 Y축 특정선 표시선이 없으면 입력값을 그대로 반환
	double GetMinCompareYValueLine(int iOverlapIndex, double dbInput);	//! 주어진 값과 Y축 특정선 표시선의 값들을 비교하여 최소값 반환
	double GetMaxCompareYValueLine(int iOverlapIndex, double dbInput);	//! 주어진 값과 Y축 특정선 표시선의 값들을 비교하여 최대값 반환

	//! Added by LHW [2008/8/25]
	//! 주어진 iOverlapIndex와 연결된 함수식으로 그려지는 그래프가 없으면 입력값을 그대로 반환
	double GetMinCompareYEquation(int iOverlapIndex, double dbInput);	//! 주어진 값과 함수식으로 그려지는 그래프의 값들을 비교하여 Y축 최소값 반환
	double GetMaxCompareYEquation(int iOverlapIndex, double dbInput);	//! 주어진 값과 함수식으로 그려지는 그래프의 값들을 비교하여 Y축 최대값 반환

	//! Added by LHW [2008/12/14]
	//! 주어진 iOverlapIndex의 영역 표시 커서가 없으면 입력값을 그대로 반환
	double GetMinCompareYRegionCursor(int iOverlapIndex, double dbInput);	//! 주어진 값과 영역 표시 커서의 값들을 비교하여 최소값 반환
	double GetMaxCompareYRegionCursor(int iOverlapIndex, double dbInput);	//! 주어진 값과 영역 표시 커서의 값들을 비교하여 최대값 반환

	bool SetGraphEquationMinMaxY();	//! 함수식으로 그려지는 그래프의 Y축 최소, 최대값을 찾아내어 설정, Added by LHW [2008/8/25]

	//! 내부 index 조작을 위한 변수, 함수, Added by LHW [2008/4/11]
	//! Added by LHW [2008/4/19] : GetXValueLinePossibleElementIndex, IsExistXValueLineElementIndex 추가
	//! Added by LHW [2008/6/13] : GetChildCursorPossibleElementIndex, IsExistChildCursorElementIndex 추가
	//! Added by LHW [2008/8/23] : GetGraphEquationPossibleElementIndex, IsExistGraphEquationElementIndex 추가
	//! Added by LHW [2008/11/28] : GetRegionCursorPossibleElementIndex, IsExistRegionCursorElementIndex 추가
	//! 사용 가능한 내부 index 반환, 오류가 있으면 -1을 반환
	int GetCursorPossibleElementIndex();		
	int GetAuxCursorGroupPossibleElementIndex();
	int GetChildCursorPossibleElementIndex();	
	int GetResourceYPossibleElementIndex();		
	int GetDataBufferPossibleElementIndex();	
	int GetXValueLinePossibleElementIndex();	
	int GetYValueLinePossibleElementIndex();
	int GetGraphEquationPossibleElementIndex();
	int GetRegionCursorPossibleElementIndex();
	//! 입력된 내부index를 가진 요소가 있으면 true를 반환
	bool IsExistCursorElementIndex(int iElementIndex);			
	bool IsExistAuxCursorGroupElementIndex(int iElementIndex);	
	bool IsExistChildCursorElementIndex(int iElementIndex);
	bool IsExistResourceYElementIndex(int iElementIndex);		
	bool IsExistDataBufferElementIndex(int iElementIndex);		
	bool IsExistXValueLineElementIndex(int iElementIndex);		
	bool IsExistYValueLineElementIndex(int iElementIndex);
	bool IsExistGraphEquationElementIndex(int iElementIndex);
	bool IsExistRegionCursorElementIndex(int iElementIndex);

	//! Added by LHW [2008/5/28]
	bool m_bDataPointSearchProcessing;		//! Data-Point Event 영역에 마우스가 들어가 있는지 확인 작업 중이면 true로 설정, Added by LHW [2008/9/19]
	bool m_bDataPointSearchComplete;		//! Data-Point Event 영역에 마우스가 들어가 있으며 해당 정보를 구조체에 설정했으면 true로 설정
	bool SearchDataPoint(CPoint ptInput);	//! Data-Point Event 영역에 마우스가 들어가 있으면 true를 반환
	
	bool m_bDrawing;		//! 그래프를 그리는 도중이면 true
	bool m_bCalcCursor;		//! 커서 관련 처리 중이면 true
	bool m_bCalcChildCursor;//! 자식 커서 관련 처리 중이면 true, Added by LHW [2008/6/13]
	bool m_bCalcAuxCursor;	//! 보조 커서 관련 처리 중이면 true, Added by LHW [2008/8/4]

	bool m_bTemporaryMouseOperation;	//! true이면 m_eMouseOperationMode가 E_GRAPH2D_CURSOR_XY일 때, 임시로 확대, 축소, Pan 작업을 진행, Added by LHW [2009/2/2]
	
	//! 마우스 커서의 핸들값
	HCURSOR	m_hCursor_Horz;
	HCURSOR	m_hCursor_Vert;
	HCURSOR m_hCursor_Move;
	HCURSOR m_hCursor_Pan_DOWN;
	HCURSOR m_hCursor_Pan_UP;
	HCURSOR m_hCursor_DataPoint_Event;	//! Data-Point Event에서 사용, Added by LHW [2008/5/28]
	HCURSOR m_hCursor_Zoom_X;			//! Added by LHW [2009/2/2]
	HCURSOR m_hCursor_Zoom_Y;			//! Added by LHW [2009/2/2]
	HCURSOR m_hCursor_Zoom_XY;			//! Added by LHW [2009/2/2]
	HCURSOR m_hCursor_Pan_X;			//! Added by LHW [2009/2/2]
	HCURSOR m_hCursor_Pan_Y;			//! Added by LHW [2009/2/2]

	int m_iRealGraphHeight;	//! 실제 그래프가 그려지는 부분의 높이

	int m_iGridMarginX, m_iGridMarginY;	//! Grid의 여유 간격값, Added by LHW [2007/7/24]
	int m_iAxisCaptionMarginX;			//! 축의 문자열 표시를 위한 여유 간격값, Added by LHW [2008/11/28]

	CPoint m_ptMouseDownPos;//! 마우스 왼쪽 클릭 한 지점을 저장, Added by LHW [2009/1/6]

	bool m_bCreateDC;		//! 메모리 DC 초기화하면 true
	CDC  m_DrawDC;			//! 메모리 DC
	CBitmap  m_DrawBitmap;
	CBitmap *m_pOldDrawBitmap;
	CRect m_CurRect;			//! 그래프 컨트롤 전체의 사각 영역
	CRect m_MainTitleRect;		//! 주 제목의 사각 영역
	CRect m_SubTitleRect;		//! 보조 제목의 사각 영역
	CRect m_AxisCaptionRect;	//! 축의 문자열 표시를 위한 사각 영역, Added by LHW [2008/8/01]	
	CRect m_crAxisX_Event;		//! X축 표시 사각 영역, Added by LHW [2009/2/2]
	CRect m_crAxisY_Left_Event;	//! 왼쪽의 Y축 표시 사각 영역, Added by LHW [2008/7/31], 변수 명 변경, Modify by LHW [2009/2/2]
	CRect m_crAxisY_Right_Event;//! 오른쪽의 Y축 표시 사각 영역, Added by LHW [2008/7/31], 변수 명 변경, Modify by LHW [2009/2/2]
	CRect m_DataRect;			//! 실제 그래프를 그리는 영역의 사각 영역 (축을 포함)
	CRect m_graphRect;			//! 실제 그래프를 그리는 영역의 사각 영역 (축을 포함하지 않음)
	CRect m_RealGraphRect;		//! 그래프의 실제 사각 영역
	CRect m_crZoomArea;			//! 확대 영역의 사각 영역
	
	CRgn m_DrawRgn;				//! 실제 그래프를 그리는 영역
	
	//! 백업용 리소스 객체
	CPen* m_penOld;
	CFont* m_pOldFont;
	CBrush* m_pOldBrush;
	COLORREF m_clrBackup;

	bool ReadyDraw(CDC *pDC);		//! 그래프를 그리기 전에 필요한 작업(사각 영역 크기 설정, X,Y축 각각의 Mapping 정보 설정 등)을 수행

	bool GetStringMaxWidth_AxisY(CDC *pDC, int iOverlapIndex, double dbMinValue, double dbMaxValue, int &iMaxWidth);	//! Y축 눈금 문자열의 최대 너비를 반환, Added by LHW [2008/10/25]
	
	bool DrawInit(CDC *pDC);												//! 메모리 DC 초기화
	bool DrawBackground(CDC *pDC);											//! 배경색
	bool DrawAxis(CDC *pDC);												//! X-Y 축, 눈금
	bool DrawAxisY(CDC *pDC, int iOverlapIndex, bool bOnlyAxis, bool bLeft);//! Y축, Modify by LHW [2008/4/4]
																			//! bOnlyAxis가 true이면 Y축이 한개만 있는 경우
																			//! bLeft가 true이면 왼쪽에 축이 그려짐
	bool DrawInfo(CDC *pDC);												//! 그래프 정보값 표시
	bool DrawData(CDC *pDC);												//! 그래프
	bool DrawGraph(CDC *pDC, int iOverlapIndex);							//! 각각의 그래프를 그림, Added by LHW [2008/7/24]
	bool DrawValueLineX(CDC *pDC);											//! X축 특정값 표시 선, Added by LHW [2008/4/19]
	bool DrawValueLineY(CDC *pDC);											//! Y축 특정값 표시 선, Added by LHW [2008/3/29]
	bool DrawEquation(CDC *pDC, int iOverlapIndex);							//! 함수식으로 그려지는 그래프를 그림, Added by LHW [2008/8/23]
																			//! iOverlapIndex가 0이상의 정수, 해당 iOverlapIndex와 연결된 그래프를 그림 																			
	bool DrawAuxCursor(CDC *pDC);											//! 보조 커서, Added by LHW [2008/3/31]
	bool DrawCursor(CDC *pDC);												//! 커서
	bool DrawChildCursor(CDC *pDC);											//! 자식 커서, Added by LHW [2008/6/13]
	bool DrawRegionCursor(CDC *pDC);										//! 영역 표시 커서, Added by LHW [2008/11/28]
	bool DrawZoomArea(CDC *pDC);											//! 선택된 확대 영역을 표시

	//! 각 데이터 위치를 표시하는 심볼을 그리는 함수, Added by LHW [2009/2/3]
	bool DrawSymbol(CDC *pDC, int iXPt, int iYPt, E_GRAPH2D_DRAW_SYMBOL_TYPE eType, int iSymbolSize, CBrush *pBrush = NULL);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};


