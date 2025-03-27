//! 2D 직교좌표 그래프 컨트롤을 외부에서 조작하는 데 필요한 열거자, 구조체, 메시지 정의
//! Maked by LHW (2008/3/14 ~ )
//! 최종 작업일 [2013/3/26]

//! Modify by LHW [2008/6/12] : operator 연산자 재정의 부분의 오류 일괄 수정

#pragma once

#define WM_GRAPH2D_DRAW_COMPLETE	WM_USER + 1232	//! 모니터 화면에 그래프 그리는 작업을 완료하면 메시지 발생
													//! WPARAM : NULL, LPARAM : NULL

#define WM_GRAPH2D_AXIS_Y_EVENT		WM_USER + 1238	//! Y축 부분에서 더블 클릭을 하면 발생하는 메시지, Added by LHW [2008/7/31]
													//! WPARAM : NULL, LPARAM : NULL

#define WM_GRAPH2D_PAN_XY_EVENT		WM_USER + 1242	//! XY 축 방향의 Pan 기능을 수행하고 마우스를 놓을 때 발생하는 메시지, Added by LHW [2009/3/1]
													//! WPARAM : NULL, LPARAM : NULL

#define WM_GRAPH2D_PAN_X_EVENT		WM_USER + 1243	//! X 축 방향의 Pan 기능을 수행하고 마우스를 놓을 때 발생하는 메시지, Added by LHW [2009/3/1]
													//! WPARAM : NULL, LPARAM : NULL

#define WM_GRAPH2D_PAN_Y_EVENT		WM_USER + 1244	//! Y 축 방향의 Pan 기능을 수행하고 마우스를 놓을 때 발생하는 메시지, Added by LHW [2009/3/1]
													//! WPARAM : NULL, LPARAM : NULL

#define WM_GRAPH2D_LMOUSE_DOWN		WM_USER + 1233	//! 마우스 왼쪽 클릭을 하면 메시지 발생
													//! WPARAM : NULL
													//! LPARAM : 구조체 strGraph2D_MouseDown_Info, 마우스 클릭위치 전달
#define WM_GRAPH2D_RMOUSE_DOWN		WM_USER + 1234	//! 마우스 오른쪽 클릭을 하면 메시지 발생
													//! WPARAM : NULL
													//! LPARAM : 구조체 strGraph2D_MouseDown_Info, 마우스 클릭위치 전달

//! Modify by LHW [2008/4/19] : X축 특정값 표시선 관련 추가
//! Modify by LHW [2008/6/13] : 자식 커서 관련 추가
//! Modify by LHW [2008/8/5] : bAuxCursorEvent 추가
//! Modify by LHW [2008/11/28] : bRegionCursorEvent 추가
struct strGraph2D_MouseDown_Info	//! 메시지로 전달되는 구조체
{
	int iPlotIndex;		//! 설정된 Plot index
	int iMouseDownX;	//! 마우스 클릭위치 X 좌표
	int iMouseDownY;	//! 마우스 클릭위치 Y 좌표

	bool bXValueLineEvent;	//! X축 특정값 표시선에서 마우스 이벤트가 발생하면 true
	int iXValueLineIndex;	//! X축 특정값 표시선의 index

	bool bChildCursorEvent;	//! 자식 커서에서 마우스 이벤트가 발생하면 true
	bool bAuxCursorEvent;	//! 보조 커서에서 마우스 이벤트가 발생하면 true
	bool bRegionCursorEvent;//! 영역 표시 커서에서 마우스 이벤트가 발생하면 true

	void InitInfo()
	{
		iPlotIndex = -1;
		iMouseDownX = 0;
		iMouseDownY = 0;

		bXValueLineEvent = false;
		iXValueLineIndex = -1;

		bChildCursorEvent = false;
		bAuxCursorEvent = false;
		bRegionCursorEvent = false;
	}

	strGraph2D_MouseDown_Info& operator=(const strGraph2D_MouseDown_Info &input)
	{
		iPlotIndex = input.iPlotIndex;
		iMouseDownX = input.iMouseDownX;
		iMouseDownY = input.iMouseDownY;
		bXValueLineEvent = input.bXValueLineEvent;
		iXValueLineIndex = input.iXValueLineIndex;
		bChildCursorEvent = input.bChildCursorEvent;
		bAuxCursorEvent = input.bAuxCursorEvent;
		bRegionCursorEvent = input.bRegionCursorEvent;

		return *this;
	}
};

//! Added by LHW [2008/6/16] : 마우스, 키보드로 움직일 수 있는 커서 종류
typedef enum _E_GRAPH2D_MOVE_CURSOR_TYPE
{
	E_GRAPH2D_MOVE_MAIN_CURSOR_TYPE = 0, 
	E_GRAPH2D_MOVE_CHILD_CURSOR_TYPE = 1, 
}E_GRAPH2D_MOVE_CURSOR_TYPE;

#define WM_GRAPH2D_CURSOR_EVENT WM_USER + 1235	//! 커서 관련 이벤트가 발생할 때마다 메시지 발생
												//! WPARAM : NULL
												//! LPARAM : 구조체 strGraph2D_Cursor_Event

//! Modify by LHW [2008/8/20] : E_GRAPH2D_CURSOR_SEARCH_X_VISUAL 추가
typedef enum _E_GRAPH2D_CURSOR_SEARCH_MODE	//! 커서값 찾는 방식
{
	E_GRAPH2D_CURSOR_SEARCH_X_RANGE = 0,	//! X축 방향으로 일정한 구간을 정하여 그 안에서 커서값을 찾음. X축 등간격, X-Y 데이터가 1:1 혹은 1:0 대응 그래프에 적합
	E_GRAPH2D_CURSOR_SEARCH_X_VISUAL = 1,	//! X축 방향으로 눈에 보이는 구간에서 커서값을 찾음. X축 등간격 아님, X-Y 데이터가 1:1 혹은 1:0 대응 그래프에 적합
	E_GRAPH2D_CURSOR_SEARCH_ALL = 2,		//! 모든 데이터를 검색하여 커서값을 찾음. X축 등간격 아님, X-Y 데이터가 1:다 대응 그래프에 적합
}E_GRAPH2D_CURSOR_SEARCH_MODE;

typedef enum _E_GRAPH2D_CURSOR_ALL_SEARCH_MODE	//! Overlap된 그래프에서 커서를 찾는 방식, Added by LHW [2008/7/24]
{
	E_GRAPH2D_CURSOR_ALL_SEARCH_SELECT = 0,		//! 마우스로 커서 중심점을 클릭을 했을 때만 모든 그래프에서 커서값을 찾음
	E_GRAPH2D_CURSOR_ALL_SEARCH_NONE = 1,		//! 현재 그래프에서만 커서값을 찾음
	E_GRAPH2D_CURSOR_ALL_SEARCH_ALWAYS = 2,		//! 무조건 모든 그래프에서 커서값을 찾음
}E_GRAPH2D_CURSOR_ALL_SEARCH_MODE;

typedef enum _E_GRAPH2D_CURSOR_OPERATION_MODE	//! 커서 동작 종류
{
	E_GRAPH2D_CURSOR_ADD = 0,				//! 커서 추가
	E_GRAPH2D_CURSOR_MOVE = 1,				//! 커서 이동
	E_GRAPH2D_CURSOR_SHOW_INFO = 2,			//! 커서 정보창 보여주기/숨기기
	E_GRAPH2D_CURSOR_LINE = 3,				//! 커서 선 표시 방식 변경
	E_GRAPH2D_CURSOR_MAX_HOLD = 4,			//! 커서에 Max-Hold 설정 변경
	E_GRAPH2D_CURSOR_SERACH_MARGIN = 5,		//! 커서의 X축 방향 검색 시 여유 값 설정, Modify by LHW [2008/4/4]
	E_GRAPH2D_CURSOR_VALUE_VISIBLE = 6,		//! 커서의 X,Y 값 표시 여부 변경 설정, Modify by LHW [2008/4/4]
	E_GRAPH2D_CURSOR_POINT_VISIBLE = 7,		//! 커서의 정확한 위치를 사각형등으로 표시하는지의 여부 변경 설정, Modify by LHW [2008/4/18]
	E_GRAPH2D_CURSOR_XY_STRING_VISIBLE = 8, //! 커서의 'X : ', 'Y : ' 문자열 표시 여부 설정, Modify by LHW [2008/8/01]
	E_GRAPH2D_CURSOR_DELETE = 9,			//! 커서 삭제
	E_GRAPH2D_CURSOR_DELETE_ALL = 10,		//! 커서 모두 삭제
}E_GRAPH2D_CURSOR_OPERATION_MODE;

typedef enum _E_GRAPH2D_CURSOR_LINE_MODE	//! 커서 선 표시 방식
{
	E_GRAPH2D_CURSOR_LINE_XY = 0,			//! 커서 선을 X-Y방향으로 모두 표시
	E_GRAPH2D_CUROSR_LINE_X = 1,			//! 커서 선을 X방향으로만 모두 표시
}E_GRAPH2D_CURSOR_LINE_MODE;

struct strGraph2D_Cursor_Event	//! 커서의 현재 동작 상태 구조체
{
	int iPlotIndex;			//! 설정된 Plot index
	bool bMouseOperation;	//! Mouse 동작으로 발생한 커서 이벤트이면 true로 설정

	E_GRAPH2D_CURSOR_OPERATION_MODE eOperationMode;	//! 커서 동작 종류
	E_GRAPH2D_CURSOR_LINE_MODE		eLineMode;		//! 커서 선 표시 방식

	int iCursorIndex;		//! 커서의 index, 0 based, eOperationMode가 E_GRAPH2D_CURSOR_DELETE_ALL일 때는 -1
	int iOverlapIndex;		//! 커서가 가르키는 Overlap되는 그래프의 index, 0 based
	int iDataIndex;			//! 커서의 데이터 index, 0 based

	double dbXData;			//! 커서의 X값
	double dbYData;			//! 커서의 Y값
	int iXPos;				//! 커서의 X 위치
	int iYPos;				//! 커서의 Y 위치

	bool bMaxHold;			//! true이면 커서가 반드시 최대값에 위치
	int iSearchMargin;		//! 커서의 X축 방향 검색 시 여유 값, Modify by LHW [2008/4/4]

	strGraph2D_Cursor_Event()
	{
		InitInfo();
	}

	void InitInfo()
	{
		iPlotIndex = -1;
		bMouseOperation = true;
		eOperationMode = E_GRAPH2D_CURSOR_MOVE;
		eLineMode = E_GRAPH2D_CURSOR_LINE_XY;
		iCursorIndex = -1;
		iOverlapIndex = -1;
		iDataIndex = -1;
		dbXData = 0.;
		dbYData = 0.;
		iXPos = 0;
		iYPos = 0;
		bMaxHold = false;
		iSearchMargin = 0;
	}

	strGraph2D_Cursor_Event& operator=(const strGraph2D_Cursor_Event &input)
	{
		iPlotIndex = input.iPlotIndex;
		bMouseOperation = input.bMouseOperation;
		eOperationMode = input.eOperationMode;
		eLineMode = input.eLineMode;
		iCursorIndex = input.iCursorIndex;
		iOverlapIndex = input.iOverlapIndex;
		iDataIndex = input.iDataIndex;
		dbXData = input.dbXData;
		dbYData = input.dbYData;
		iXPos = input.iXPos;
		iYPos = input.iYPos;
		bMaxHold = input.bMaxHold;
		iSearchMargin = input.iSearchMargin;

		return *this;
	}
};

#define WM_GRAPH2D_REGION_CURSOR_EVENT	WM_USER + 1241	//! 영역 표시 커서 관련 이벤트가 발생할 때마다 메시지 발생, Added by LHW [2008/11/28]
														//! WPARAM : NULL
														//! LPARAM : 구조체 strGraph2D_Region_Cursor_Event

struct strGraph2D_Region_Cursor_Event	//! 영역 표시 커서의 현재 동작 상태 구조체, Added by LHW [2008/11/28]
{
	int iPlotIndex;		//! 설정된 Plot index
	int iCursorIndex;	//! 커서의 index

	double dbMinDataX;	//! 커서의 X 최소값
	double dbMaxDataX;	//! 커서의 X 최대값
	double dbMinDataY;	//! 커서의 Y 최소값
	double dbMaxDataY;	//! 커서의 Y 최대값

	int iMinPosX;		//! 커서의 X 최소 위치
	int iMaxPosX;		//! 커서의 X 최대 위치	
	int iMinPosY;		//! 커서의 Y 최소 위치
	int iMaxPosY;		//! 커서의 Y 최대 위치

	strGraph2D_Region_Cursor_Event()
	{
		InitInfo();
	}

	void InitInfo()
	{
		iPlotIndex = -1;
		iCursorIndex = -1;
		dbMinDataX = 0.;
		dbMaxDataX = 0.;
		dbMinDataY = 0.;
		dbMaxDataY = 0.;
		iMinPosX = 0;
		iMaxPosX = 0;
		iMinPosY = 0;
		iMaxPosY = 0;
	}

	strGraph2D_Region_Cursor_Event& operator=(const strGraph2D_Region_Cursor_Event &input)
	{
		iPlotIndex = input.iPlotIndex;
		iCursorIndex = input.iCursorIndex;
		dbMinDataX = input.dbMinDataX;
		dbMaxDataX = input.dbMaxDataX;
		dbMinDataY = input.dbMinDataY;
		dbMaxDataY = input.dbMaxDataY;
		iMinPosX = input.iMinPosX;
		iMaxPosX = input.iMaxPosX;
		iMinPosY = input.iMinPosY;
		iMaxPosY = input.iMaxPosY;

		return *this;
	}
};

//! Added by LHW [2008/11/28] : 영역 표시 커서 추가, 그래프와는 독립적으로 동작하는 커서
//! Modify by LHW [2008/11/30] : iOverlapIndex, bShowGraphChk 추가
struct strGraph2D_Region_Cursor
{
	bool bShow;			//! true이면 커서가 보이게 함
	bool bShowText;		//! true이면 커서 표시 문자열이 보이게 함
	bool bShowGraphChk;	//! true이면 아래 iOverlapIndex의 그래프가 눈에 보이지 않으면 같이 보이지 않고, 그래프가 눈에 보이면 같이 보임

	int iOverlapIndex;			//! 영역 표시 커서가 가르키는 Overlap되는 그래프의 index, 0 based

	bool bCursorFontHeight;		//! true이면 커서 표시 문자열 글자 크기를 자동 설정
	int	iCursorFontHeight;		//! 커서 표시 문자열 글자 크기, 음수값으로 설정
	CString	szCursorFontName;	//! 커서 표시 문자열의 폰트 종류

	COLORREF clrCursorLine;			//! 커서 선의 색상
	COLORREF clrSelectCursorLine;	//! 선택된 커서 선의 색상
	COLORREF clrCursorText;			//! 커서 표시 문자열의 색상

	CString szCursorText;		//! 커서 표시 문자열

	int iCursorLineThickness;	//! 커서 선의 두께

	strGraph2D_Region_Cursor()
	{
		InitInfo();
	}

	void InitInfo()
	{
		bShow = true;
		bShowText = true;
		bShowGraphChk = true;
		iOverlapIndex = -1;
		bCursorFontHeight = true;
		iCursorFontHeight = -10;
		szCursorFontName = _T("MS Sans Serif");
		clrCursorLine = RGB(255, 128, 0);
		clrSelectCursorLine = RGB(255, 0, 0);
		clrCursorText = RGB(0, 0, 0);
		szCursorText = _T("");
		iCursorLineThickness = 1;
	}

	strGraph2D_Region_Cursor& operator=(const strGraph2D_Region_Cursor &input)
	{
		bShow = input.bShow;
		bShowText = input.bShowText;
		bShowGraphChk = input.bShowGraphChk;
		iOverlapIndex = input.iOverlapIndex;
		bCursorFontHeight = input.bCursorFontHeight;
		iCursorFontHeight = input.iCursorFontHeight;
		szCursorFontName = input.szCursorFontName;
		clrCursorLine = input.clrCursorLine;
		clrSelectCursorLine = input.clrSelectCursorLine;
		clrCursorText = input.clrCursorText;
		szCursorText = input.szCursorText;
		iCursorLineThickness = input.iCursorLineThickness;
		
		return *this;
	}
};

//! Added by LHW [2008/6/12] : 자식 커서값 찾는 방식
//! Modify by LHW [2008/8/20] : E_GRAPH2D_CHILD_CURSOR_SEARCH_X_VISUAL 추가
typedef enum _E_GRAPH2D_CHILD_CURSOR_SEARCH_MODE
{
	E_GRAPH2D_CHILD_CURSOR_SEARCH_X_RANGE = 0,	//! X축 방향으로 일정한 구간을 정하여 그 안에서 자식 커서값을 찾음. X축 등간격, X-Y 데이터가 1:1 혹은 1:0 대응 그래프에 적합
	E_GRAPH2D_CHILD_CURSOR_SEARCH_X_VISUAL = 1,	//! X축 방향으로 눈에 보이는 구간에서 자식 커서값을 찾음. X축 등간격 아님, X-Y 데이터가 1:1 혹은 1:0 대응 그래프에 적합
	E_GRAPH2D_CHILD_CURSOR_SEARCH_ALL = 2,		//! 모든 데이터를 검색하여 자식 커서값을 찾음. X축 등간격 아님, X-Y 데이터가 1:다 대응 그래프에 적합
}E_GRAPH2D_CHILD_CURSOR_SEARCH_MODE;

typedef enum _E_GRAPH2D_CHILD_CURSOR_LINE_MODE	//! 자식 커서 선 표시 방식, Added by LHW [2008/6/12]
{
	E_GRAPH2D_CHILD_CURSOR_LINE_XY = 0,			//! 자식 커서 선을 X-Y방향으로 모두 표시
	E_GRAPH2D_CHILD_CUROSR_LINE_X = 1,			//! 자식 커서 선을 X방향으로만 모두 표시
}E_GRAPH2D_CHILD_CURSOR_LINE_MODE;

//! Added by LHW [2008/6/12] : 커서에 종속되어 동작하는 자식 커서 추가, 보조 커서와는 달리 마우스 이벤트를 받아 동작 가능
//! Modify by LHW [2008/6/14] : bCursorOverlapAllSearch 추가
//! Modify by LHW [2008/6/15] : bFollowCursor 추가
//! Modify by LHW [2008/6/16] : clrSelectCursorLine 추가
//! Modify by LHW [2008/8/11] : bShowStringX, bShowStringY 추가
//! Modify by LHW [2009/6/4] : 마우스를 움직일 때의 커서 동작의 오차를 줄이기 위해 iSearchMargin의 초기값을 100으로 설정
struct strGraph2D_Child_Cursor
{
	E_GRAPH2D_CHILD_CURSOR_SEARCH_MODE	eSearchMode;	//! 자식 커서값 찾는 방식 설정
	E_GRAPH2D_CHILD_CURSOR_LINE_MODE	eLineMode;		//! 자식 커서 선 표시 방식

	int iOverlapIndex;			//! 자식 커서가 가르키는 Overlap되는 그래프의 index, 0 based
	int iCursorElementIndex;	//! 부모 커서의 내부 index, 자식 커서 index가 아님, 0 based

	bool bShow;						//! true이면 자식 커서가 보이게 함
	bool bCursorOverlapAllSearch;	//! true이면 자식 커서의 값을 구하기 위해 무조건 Overlap된 모든 그래프에서 작업 진행
	bool bFollowCursor;				//! true이면 부모 커서가 움직일 경우 같이 움직임

	int iSearchMargin;			//! 자식 커서값 찾는 방식이 X축 방향으로 일정한 구간을 정하여 그 안에서 자식 커서값을 찾을 경우 구간의 여유 값
								//! 이 값이 클수록 더 많은 데이터를 검색
	
	int	iCursorLineThickness;		//! 자식 커서 선의 두께
	int	iCursorTextBorderThickness;	//! 자식 커서 정보창의 테두리 선의 두께

	bool bCursorFontHeight;		//! true이면 자식 커서 표시 문자 글자 크기를 자동 설정
	int	iCursorFontHeight;		//! 자식 커서 표시 문자 글자 크기, 음수값으로 설정
	CString	szCursorFontName;	//! 자식 커서 표시 문자의 폰트 종류

	COLORREF clrCursorLine;			//! 자식 커서 선의 색상
	COLORREF clrSelectCursorLine;	//! 선택된 자식 커서 선의 색상
	COLORREF clrCursorPoint;		//! 자식 커서 점의 색상
	COLORREF clrCursorText;			//! 자식 커서값 글자의 색상
	COLORREF clrCursorTextBorder;	//! 자식 커서 정보창의 테두리 선의 색상
	COLORREF clrCursorTextBack;		//! 자식 커서 정보창의 바탕색

	bool bShowGraphChk;				//! true이면 아래 iOverlapIndex의 그래프가 눈에 보이지 않으면 같이 보이지 않고, 그래프가 눈에 보이면 같이 보임
	bool bShowInfo;					//! 자식 커서의 정보창 출력 여부
	bool bShowValueX;				//! 자식 커서의 X값 출력 여부
	bool bShowValueY;				//! 자식 커서의 Y값 출력 여부
	bool bShowValueDeltaX;			//! 자식 커서와 부모 커서 사이의 X 차이값 출력 여부
	bool bShowValueDeltaY;			//! 자식 커서와 부모 커서 사이의 Y 차이값 출력 여부
	bool bShowPoint;				//! 자식 커서에 표시 사각형 출력 여부
	bool bShowStringX;				//! 커서값에 'X : ' 문자열 표시
	bool bShowStringY;				//! 커서값에 'Y : ' 문자열 표시

	strGraph2D_Child_Cursor()
	{
		InitInfo();
	}

	void InitInfo()
	{
		eSearchMode = E_GRAPH2D_CHILD_CURSOR_SEARCH_X_RANGE;
		eLineMode = E_GRAPH2D_CHILD_CURSOR_LINE_XY;
		iOverlapIndex = -1;
		iCursorElementIndex = -1;
		bShow = true;
		bCursorOverlapAllSearch = false;
		bFollowCursor = true;
		iSearchMargin = 100;
		iCursorLineThickness = 1;
		iCursorTextBorderThickness = 1;
		bCursorFontHeight = true;
		iCursorFontHeight = -10;
		szCursorFontName = _T("MS Sans Serif");
		clrCursorLine = RGB(0, 255, 0);
		clrSelectCursorLine = RGB(0, 128, 0);
		clrCursorPoint = RGB(255, 0, 0);
		clrCursorText = RGB(0, 0, 0);
		clrCursorTextBorder = RGB(0, 0, 0);
		clrCursorTextBack = RGB(255, 255, 128);
		bShowGraphChk = true;
		bShowInfo = true;
		bShowValueX = true;
		bShowValueY = true;
		bShowValueDeltaX = true;
		bShowValueDeltaY = true;
		bShowPoint = true;
		bShowStringX = false;
		bShowStringY = false;
	}

	strGraph2D_Child_Cursor& operator=(const strGraph2D_Child_Cursor &input)
	{
		eSearchMode = input.eSearchMode;
		eLineMode = input.eLineMode;
		iOverlapIndex = input.iOverlapIndex;
		iCursorElementIndex = input.iCursorElementIndex;
		bShow = input.bShow;
		bCursorOverlapAllSearch = input.bCursorOverlapAllSearch;
		bFollowCursor = input.bFollowCursor;
		iSearchMargin = input.iSearchMargin;
		iCursorLineThickness = input.iCursorLineThickness;
		iCursorTextBorderThickness = input.iCursorTextBorderThickness;
		bCursorFontHeight = input.bCursorFontHeight;
		iCursorFontHeight = input.iCursorFontHeight;
		szCursorFontName = input.szCursorFontName;
		clrCursorLine = input.clrCursorLine;
		clrSelectCursorLine = input.clrSelectCursorLine;
		clrCursorPoint = input.clrCursorPoint;
		clrCursorText = input.clrCursorText;
		clrCursorTextBorder = input.clrCursorTextBorder;
		clrCursorTextBack = input.clrCursorTextBack;
		bShowGraphChk = input.bShowGraphChk;
		bShowInfo = input.bShowInfo;
		bShowValueX = input.bShowValueX;
		bShowValueY = input.bShowValueY;
		bShowValueDeltaX = input.bShowValueDeltaX;
		bShowValueDeltaY = input.bShowValueDeltaY;
		bShowPoint = input.bShowPoint;
		bShowStringX = input.bShowStringX;
		bShowStringY = input.bShowStringY;

		return *this;
	}
};

//! Added by LHW [2008/4/19]
#define WM_GRAPH2D_ZOOM_EVENT WM_USER + 1236	//! 커서 관련 이벤트가 발생할 때마다 메시지 발생
												//! WPARAM : NULL
												//! LPARAM : 구조체 strGraph2D_Zoom_Event

//! Added by LHW [2008/4/19]
typedef enum _E_GRAPH2D_ZOOM_OPERATION_MODE	//! Zoom 동작 종류
{
	E_GRAPH2D_ZOOM_IN = 0,		//! 확대
	E_GRAPH2D_ZOOM_OUT = 1,		//! 예전 상태로 돌아가기
	E_GRAPH2D_ZOOM_FIT = 2,		//! 원래대로
}E_GRAPH2D_ZOOM_OPERATION_MODE;

//! Added by LHW [2008/4/19]
struct strGraph2D_Zoom_Event	//! 확대/축소 현재 동작 상태 구조체
{
	int iPlotIndex;				//! 설정된 Plot index
	E_GRAPH2D_ZOOM_OPERATION_MODE eZoomMode;	//! Zoom 동작 종류

	strGraph2D_Zoom_Event()
	{
		InitInfo();
	}

	void InitInfo()
	{
		iPlotIndex = -1;
		eZoomMode = E_GRAPH2D_ZOOM_IN;
	}

	strGraph2D_Zoom_Event& operator=(const strGraph2D_Zoom_Event &input)
	{
		iPlotIndex = input.iPlotIndex;
		eZoomMode = input.eZoomMode;

		return *this;
	}
};

//! Added by LHW [2008/5/23]
#define WM_GRAPH2D_DATA_POINT_EVENT	WM_USER + 1237 //! 그래프의 데이터 점에서 이벤트가 발생했을 때의 메시지
												   //! WPARAM : NULL
  												   //! LPARAM : 구조체 strGraph2D_DataPoint_Event

//! Added by LHW [2008/5/23]
struct strGraph2D_DataPoint_Event	//! 그래프의 데이터 점에서 보내지는 정보 구조체
{
	int iOverlapIndex;	//! 그래프 index, 0 based
	int iDataIndex;		//! 데이터 index, 0 based
	double dbXData;		//! X값
	double dbYData;		//! Y값
	int iCustomData;	//! 사용자가 추가 입력한 데이터, 초기값 -1

	strGraph2D_DataPoint_Event()
	{
		InitInfo();
	}

	void InitInfo()
	{
		iOverlapIndex = -1;
		iDataIndex = -1;
		dbXData = 0.;
		dbYData = 0.;
		iCustomData = -1;
	}

	strGraph2D_DataPoint_Event& operator=(const strGraph2D_DataPoint_Event &input)
	{
		iOverlapIndex = input.iOverlapIndex;
		iDataIndex = input.iDataIndex;
		dbXData = input.dbXData;
		dbYData = input.dbYData;
		iCustomData = input.iCustomData;

		return *this;
	}
};

typedef enum _E_GRAPH2D_KEY_TYPE	//! 키보드에서 눌려진 키의 종류, Added by LHW [2008/4/15]
{
	E_GRAPH2D_KEY_UP_ARROW = 0,		//! 위쪽 화살표
	E_GRAPH2D_KEY_DOWN_ARROW = 1,	//! 아래쪽 화살표
	E_GRAPH2D_KEY_LEFT_ARROW = 2,	//! 왼쪽 화살표
	E_GRAPH2D_KEY_RIGHT_ARROW = 3,	//! 오른쪽 화살표
	E_GRAPH2D_KEY_PAGE_UP = 4,		//! 'Page UP' 키
	E_GRAPH2D_KEY_PAGE_DOWN = 5,	//! 'Page Down' 키
}E_GRAPH2D_KEY_TYPE;

//! Added by LHW [2008/3/31]
//! Modify by LHW [2008/4/1] : E_GRAPH2D_AUX_CURSOR_FIXED_INDEX 추가
typedef enum _E_GRAPH2D_AUX_CURSOR_TYPE	//! 보조 커서 기능의 종류
{
	E_GRAPH2D_AUX_CURSOR_FIXED = 0,			//! 특정 X값에 대해 고정
	E_GRAPH2D_AUX_CURSOR_VARIABLE = 1,		//! 커서가 움직임에 따라 커서를 중심으로 변화되는 X값에 대해 표시
	E_GRAPH2D_AUX_CURSOR_FIXED_INDEX = 2,	//! 특정 데이터 index에 대해 고정
}E_GRAPH2D_AUX_CURSOR_TYPE;

//! Added by LHW [2008/4/1] : 보조 커서값 찾는 방식
//! Modify by LHW [2008/8/20] : E_GRAPH2D_AUX_CURSOR_SEARCH_X_VISUAL 추가
typedef enum _E_GRAPH2D_AUX_CURSOR_SEARCH_MODE
{
	E_GRAPH2D_AUX_CURSOR_SEARCH_X_RANGE = 0,	//! X축 방향으로 일정한 구간을 정하여 그 안에서 보조 커서값을 찾음. X축 등간격, X-Y 데이터가 1:1 혹은 1:0 대응 그래프에 적합
	E_GRAPH2D_AUX_CURSOR_SEARCH_X_VISUAL = 1,	//! X축 방향으로 눈에 보이는 구간에서만 보조 커서값을 찾음
												//! 보조 커서가 키보드, 마우스로 움직일 경우. X축 등간격 아님, X-Y 데이터가 1:1 혹은 1:0 대응 그래프에 적합												
	E_GRAPH2D_AUX_CURSOR_SEARCH_ALL = 2,		//! 모든 데이터를 검색하여 보조 커서값을 찾음. X축 등간격 아님, X-Y 데이터가 1:다 대응 그래프에 적합
}E_GRAPH2D_AUX_CURSOR_SEARCH_MODE;

//! Added by LHW [2008/4/19]
//! Modify by LHW [2008/4/21] : E_GRAPH2D_AUX_CURSOR_DASH_LINE 추가
//! Modify by LHW [2008/8/04] : E_GRAPH2D_AUX_CURSOR_SOLID_LINE 추가
typedef enum _E_GRAPH2D_AUX_CURSOR_DRAW_MODE	//! 보조 커서 그리는 방식
{
	E_GRAPH2D_AUX_CURSOR_CIRCLE = 0,			//! 원으로 보조 커서 표시
	E_GRAPH2D_AUX_CURSOR_SOLID_LINE = 1,		//! 실선으로 보조 커서 표시
	E_GRAPH2D_AUX_CURSOR_DOT_LINE = 2,			//! 간격이 작은 점선으로 보조 커서 표시
	E_GRAPH2D_AUX_CURSOR_DASH_LINE = 3,			//! 간격이 긴 점선으로 보조 커서 표시
}E_GRAPH2D_AUX_CURSOR_DRAW_MODE;

typedef enum _E_GRAPH2D_AUX_CURSOR_BOUNDARY_MODE	//! 보조 커서 경계 조건, Added by LHW [2008/8/19]
{
	E_GRAPH2D_AUX_CURSOR_BOUNDARY_NONE = 0,			//! 경계 조건 없음
	E_GRAPH2D_AUX_CURSOR_BOUNDARY_CURSOR_LEFT = 1,	//! Main 커서의 왼쪽에만 위치
	E_GRAPH2D_AUX_CURSOR_BOUNDARY_CURSOR_RIGHT = 2, //! Main 커서의 오른쪽에만 위치
}E_GRAPH2D_AUX_CURSOR_BOUNDARY_MODE;

#define WM_GRAPH2D_AUX_CURSOR_EVENT	WM_USER + 1239	//! 보조 커서를 마우스, 키보드로 조작하면 메시지 발생, Added by LHW [2008/8/5]
													//! 보조 커서의 새로운 위치 설정은 메시지를 받아 직접 해주어야 함

struct strGraph2D_Aux_Cursor_Event	//! 보조 커서 이벤트 구조체, Added by LHW [2008/8/5]
{
	int iPlotIndex;				//! 그래프 index

	int iAuxCursorGroupElementIndex;//! 이벤트가 발생한 보조 커서 그룹 Element index
	int iAuxCursorElementIndex;		//! 이벤트가 발생한 보조 커서 Element index

	int iAuxCursorGroupIndex;	//! 이벤트가 발생한 보조 커서 그룹 index
	int iAuxCursorIndex;		//! 이벤트가 발생한 보조 커서 index

	int iDataIndex;				//! 이벤트가 발생한 보조 커서의 데이터 index
	double dbXData;				//! 이벤트가 발생한 보조 커서의 X값
	double dbYData;				//! 이벤트가 발생한 보조 커서의 Y값

	strGraph2D_Aux_Cursor_Event()
	{
		InitInfo();
	}

	void InitInfo()
	{
		iPlotIndex = -1;
		iAuxCursorGroupElementIndex = -1;
		iAuxCursorElementIndex = -1;
		iAuxCursorGroupIndex = -1;
		iAuxCursorIndex = -1;

		iDataIndex = -1;
		dbXData = 0.;
		dbYData = 0.;
	}

	strGraph2D_Aux_Cursor_Event& operator=(const strGraph2D_Aux_Cursor_Event &input)
	{
		iPlotIndex = input.iPlotIndex;
		iAuxCursorGroupElementIndex = input.iAuxCursorGroupElementIndex;
		iAuxCursorElementIndex = input.iAuxCursorElementIndex;
		iAuxCursorGroupIndex = input.iAuxCursorGroupIndex;
		iAuxCursorIndex = input.iAuxCursorIndex;

		iDataIndex = input.iDataIndex;
		dbXData = input.dbXData;
		dbYData = input.dbYData;
	}
};

//! Added by LHW [2008/3/31]
//! Modify by LHW [2008/4/1] : bValid, iOverlapIndex, eSearchMode, iDataIndex 추가
//! Modify by LHW [2008/4/11] : 보조 커서 구조체에서 사용자가 직접 입력하면 안되는 부분을 분리
//! Modify by LHW [2008/8/4] : eDrawMode, bMouseEvent, iCustomData, dbCustomData 추가
//! Modify by LHW [2008/8/5] : iSearchMargin, bIndependency 추가
//! Modify by LHW [2008/8/19] : eBoundaryMode 추가
//! Modify by LHW [2008/8/20] : bCursorOverlapAllSearch, eMouseSearchMode 추가
//! Modify by LHW [2009/6/4] : 마우스를 움직일 때의 커서 동작의 오차를 줄이기 위해 iSearchMargin의 초기값을 100으로 설정
struct strGraph2D_Aux_Cursor	//! 보조 커서 구조체
{
	E_GRAPH2D_AUX_CURSOR_TYPE			eCursorType;		//! 보조 커서의 기능 종류 설정
	E_GRAPH2D_AUX_CURSOR_SEARCH_MODE	eSearchMode;		//! 보조 커서값 찾는 방식 설정
	E_GRAPH2D_AUX_CURSOR_SEARCH_MODE	eMouseSearchMode;	//! 키보드나 마우스로 보조 커서값 찾는 방식 설정
	E_GRAPH2D_AUX_CURSOR_DRAW_MODE		eDrawMode;			//! 보조 커서 그리는 방식
	E_GRAPH2D_AUX_CURSOR_BOUNDARY_MODE	eBoundaryMode;		//! 보조 커서의 경계 조건

	bool bCursorOverlapAllSearch;	//! true이면 보조 커서의 값을 구하기 위해 무조건 Overlap된 모든 그래프에서 작업 진행

	bool bMouseEvent;			//! true이면 마우스 이벤트를 받아 처리할 수 있음, true이면 보조 커서에서 커서 모양이 변경
	int iSearchMargin;			//! 마우스로 데이터를 찾을 때의 구간 여유 값

	bool bIndependency;			//! 독립 여부, true이면 마우스, 키보드 움직임에 따라 독자적으로 움직임
	
	int iOverlapIndex;			//! 보조 커서가 가르키는 Overlap되는 그래프의 index, 0 based
	int iCursorIndex;			//! 커서 index, 보조 커서 index가 아님, 0 based
								//! eCursorType가 E_GRAPH2D_AUX_CURSOR_VARIABLE일 때 기준이 되는 커서 index
	int iDataIndex;				//! 데이터 index, eCursorType가 E_GRAPH2D_AUX_CURSOR_FIXED_INDEX일 때 사용, 0 based

	double dbXData;				//! X값, eCursorType가 E_GRAPH2D_AUX_CURSOR_FIXED_INDEX일 때를 제외하면 직접 입력해야 함
								//! eCursorType가 E_GRAPH2D_AUX_CURSOR_FIXED일 때는 절대값
								//! eCursorType가 E_GRAPH2D_AUX_CURSOR_VARIABLE일 때는 현재 커서 선에 대한 상대값

	CString szCursorText;		//! 보조 커서 글자, 보조 커서 위에 표시

	int iCustomData;			//! 사용자 데이터
	double dbCustomData;		//! 사용자 데이터

	strGraph2D_Aux_Cursor()
	{
		InitInfo();
	}

	void InitInfo()
	{		
		eCursorType = E_GRAPH2D_AUX_CURSOR_FIXED;
		eSearchMode = E_GRAPH2D_AUX_CURSOR_SEARCH_X_RANGE;
		eMouseSearchMode = E_GRAPH2D_AUX_CURSOR_SEARCH_X_RANGE;
		eDrawMode = E_GRAPH2D_AUX_CURSOR_CIRCLE;
		eBoundaryMode = E_GRAPH2D_AUX_CURSOR_BOUNDARY_NONE;
		bCursorOverlapAllSearch = false;
		bMouseEvent = false;
		iSearchMargin = 100;
		bIndependency = false;
		iOverlapIndex = 0;
		iCursorIndex = 0;
		iDataIndex = 0;
		dbXData = 0.;				
		szCursorText = _T("");
		iCustomData = 0;
		dbCustomData = 0.;
	}

	strGraph2D_Aux_Cursor& operator=(const strGraph2D_Aux_Cursor &input)
	{		
		eCursorType = input.eCursorType;
		eSearchMode = input.eSearchMode;
		eMouseSearchMode = input.eMouseSearchMode;
		eDrawMode = input.eDrawMode;
		eBoundaryMode = input.eBoundaryMode;
		bCursorOverlapAllSearch = input.bCursorOverlapAllSearch;
		bMouseEvent = input.bMouseEvent;
		iSearchMargin = input.iSearchMargin;
		bIndependency = input.bIndependency;
		iOverlapIndex = input.iOverlapIndex;
		iCursorIndex = input.iCursorIndex;
		iDataIndex = input.iDataIndex;
		dbXData = input.dbXData;				
		szCursorText = input.szCursorText;
		iCustomData = input.iCustomData;
		dbCustomData = input.dbCustomData;

		return *this;
	}
};

//! Added by LHW [2008/3/31]
//! Modify by LHW [2008/4/1] : bShow 추가
//! Modify by LHW [2008/4/10] : bFontVertical 추가
//! Modify by LHW [2008/4/19] : eDrawMode 추가
//! Modify by LHW [2008/5/9] : bFontBold 추가
//! Modify by LHW [2008/8/4] : eDrawMode 삭제, iPenThickness를 iSolidPenThickness로 명칭 변경, iCustomData, dbCustomData 추가
struct strGraph2D_Aux_CursorGroup	//! 보조 커서 그룹의 공통 정보의 설정 구조체
{
	bool		bShow;				//! true이면 보조 커서들이 보이게 함
	
	bool		bFontHeight;		//! true이면 문자 글자 크기를 자동 설정
	int			iFontHeight;		//! 문자 글자 크기, 음수값으로 설정
	bool		bFontVertical;		//! true이면 문자를 수직으로 위치시킴
	bool		bFontBold;			//! true이면 문자를 굵게 표시
	CString		szFontName;			//! 문자의 폰트 종류

	bool		bRadius;			//! true이면 보조 커서의 반경을 자동 설정
	int			iRadius;			//! 보조 커서의 반경 (보조 커서는 원형으로 표시)

	int			iSolidPenThickness;	//! 보조 커서 실선의 두께

	COLORREF	clrAuxCursor;		//! 보조 커서의 색상
	COLORREF	clrAuxCursorText;	//! 보조 커서 글자의 색상

	int iCustomData;			//! 사용자 데이터
	double dbCustomData;		//! 사용자 데이터

	strGraph2D_Aux_CursorGroup()
	{
		InitInfo();
	}

	void InitInfo()
	{
		bShow = true;		
		bFontHeight = true;
		iFontHeight = 10;
		bFontVertical = false;
		bFontBold = false;
		szFontName = _T("MS Sans Serif");
		bRadius = true;
		iRadius = 4;
		iSolidPenThickness = 1;
		clrAuxCursor = RGB(0, 0, 0);
		clrAuxCursorText = RGB(0, 0, 0);
		iCustomData = 0;
		dbCustomData = 0.;
	}

	strGraph2D_Aux_CursorGroup& operator=(const strGraph2D_Aux_CursorGroup &input)
	{
		bShow = input.bShow;		
		bFontHeight = input.bFontHeight;
		iFontHeight = input.iFontHeight;
		bFontVertical = input.bFontVertical;
		bFontBold = input.bFontBold;
		szFontName = input.szFontName;
		bRadius = input.bRadius;
		iRadius = input.iRadius;
		iSolidPenThickness = input.iSolidPenThickness;
		clrAuxCursor = input.clrAuxCursor;
		clrAuxCursorText = input.clrAuxCursorText;
		iCustomData = input.iCustomData;
		dbCustomData = input.dbCustomData;
		
		return *this;
	}
};

typedef enum _E_GRAPH2D_ZOOM_DIRECTION	//! 확대되는 방향
{
	E_GRAPH2D_ZOOM_DIRECTION_XY = 0,	//! X-Y축 모두 확대
	E_GRAPH2D_ZOOM_DIRECTION_X = 1,		//! X축만 확대
	E_GRAPH2D_ZOOM_DIRECTION_Y = 2,		//! Y축만 확대
}E_GRAPH2D_ZOOM_DIRECTION;

//! Modify by LHW [2008/10/25] : E_GRAPH2D_ZOOM_Y 추가
//! Modify by LHW [2009/2/2] : E_GRAPH2D_PAN_X, E_GRAPH2D_PAN_Y 추가
typedef enum _E_GRAPH2D_MOUSE_OPERATION	//! Mouse를 이용한 동작의 종류
{
	E_GRAPH2D_CURSOR_XY = 0,	//! X-Y축 방향으로 동작하는 커서
	E_GRAPH2D_ZOOM_XY = 1,		//! X-Y축 방향으로 확대할 영역 선택
	E_GRAPH2D_ZOOM_X = 2,		//! X축 방향으로 확대할 영역 선택
	E_GRAPH2D_ZOOM_Y = 3,		//! Y축 방향으로 확대할 영역 선택
	E_GRAPH2D_PAN_XY = 4,		//! X-Y축 방향으로 동작하는 그래프의 평행 이동
	E_GRAPH2D_PAN_X = 5,		//! X축 방향으로 동작하는 그래프의 평행 이동
	E_GRAPH2D_PAN_Y = 6,		//! Y축 방향으로 동작하는 그래프의 평행 이동
}E_GRAPH2D_MOUSE_OPERATION;

typedef enum _E_GRAPH2D_GRID_TEXT_TYPE	//! Grid 값 표시 방식
{
	E_GRAPH2D_GRID_INTEGER = 0,	//! 정수형 표기
	E_GRAPH2D_GRID_DOUBLE = 1,	//! 실수형 표기
	E_GRAPH2D_GRID_EXP = 2,		//! 지수형 표기
}E_GRAPH2D_GRID_TEXT_TYPE;

//! Added by LHW [2008/4/2]
//! Modify by LHW [2008/4/9] : E_GRAPH2D_DATA_VISUAL_MILLI_SECOND 추가
typedef enum _E_GRAPH2D_DATA_VISUAL_TYPE	//! 입력된 데이터의 종류와 처리 방식에 따라 데이터를 표시하는 방법의 종류
{
	E_GRAPH2D_DATA_VISUAL_LINEAR = 0,		//! 입력된 데이터를 그대로 이용
	E_GRAPH2D_DATA_VISUAL_CALCULATION = 1,	//! 입력된 데이터에 1차 함수 식을 적용하여 변형된 데이터를 사용할 때
	E_GRAPH2D_DATA_VISUAL_TIME = 2,			//! 입력된 데이터가 Time 데이터일 때
	E_GRAPH2D_DATA_VISUAL_SECOND = 3,		//! 입력된 데이터가 초 단위의 정수일 때
	E_GRAPH2D_DATA_VISUAL_MILLI_SECOND = 4,	//! 입력된 데이터가 Milli 초 단위의 정수일 때	
}E_GRAPH2D_DATA_VISUAL_TYPE;

//! Added by LHW [2008/4/3]
typedef enum _E_GRAPH2D_DATA_CALC_TYPE		//! 입력된 데이터에 1차 함수 식을 적용할 때의 종류
{
	//! y : 연산 결과 값, x : 원래 데이터, a : 계수, b : Offset 값
	E_GRAPH2D_DATA_CALC_MULTIPLY = 0,		//! y = a * x + b
	E_GRAPH2D_DATA_CALC_DIVIDE = 1,			//! y = x / a + b
}E_GRAPH2D_DATA_CALC_TYPE;

//! Modify by LHW [2008/6/30] : E_GRAPH2D_RANGE_MARGIN_MAX_PERCENT 추가
typedef enum _E_GRAPH2D_RANGE_MARGIN_TYPE	//! Auto Range일 때의 여유 값 설정 종류, 최소값 아래, 최대값 위로 여유 값을 사용
{
	E_GRAPH2D_RANGE_MARGIN_NONE = 0,		//! 여유 값을 사용하지 않음
	E_GRAPH2D_RANGE_MARGIN_PERCENT = 1,		//! strGraph2D_Axis_Info의 (dbManualMax - dbManualMin)의 %값으로 설정
	E_GRAPH2D_RANGE_MARGIN_MAX_PERCENT = 2,	//! strGraph2D_Axis_Info의 dbManualMax, dbManualMin 중 절대값으로 비교하여 최대값을 구한 후, 이 값에 %값을 더함
	E_GRAPH2D_RANGE_MARGIN_VALUE = 3,		//! 여유 값을 고정 값으로 설정	
}E_GRAPH2D_GRID_MARGIN_TYPE;

//! Added by LHW [2008/4/17] : Auto Range에서 예약된 값을 적용하는 방법
//! Modify by LHW [2009/5/30] : E_GRAPH2D_AUTO_RANGE_RESERVED_STEP 추가
typedef enum _E_GRAPH2D_AUTO_RANGE_RESERVED_TYPE
{
	E_GRAPH2D_AUTO_RANGE_RESERVED_NONE = 0,		//! 예약 설정 없음
	E_GRAPH2D_AUTO_RANGE_RESERVED_FORCED = 1,	//! 무조건 예약값으로 설정
	E_GRAPH2D_AUTO_RANGE_RESERVED_CONSIDER = 2,	//! 원래값보다 작거나 클 경우에만 적용
	E_GRAPH2D_AUTO_RANGE_RESERVED_STEP = 3,		//! 설정된 Step값들 사이의 값을 적용, 최소값일 경우에는 Step값 중 작은 쪽, 최대값일 경우에는 Step값 중 큰 쪽을 적용
}E_GRAPH2D_AUTO_RANGE_RESERVED_TYPE;

//! Modify by LHW [2008/4/2] : GetManualMinTime, SetManualMinTime, GetManualMaxTime, SetManualMaxTime, eGridType 추가
//! Modify by LHW [2008/4/4] : bAutoRangeReservedMin, dbAutoRangeReservedMin, bAutoRangeReservedMax, dbAutoRangeReservedMax 추가
//! Modify by LHW [2008/4/16] : bKilo 추가
//! Modify by LHW [2008/4/17] : bAutoRangeReservedMin를 eAutoRangeReservedMin로, bAutoRangeReservedMax를 eAutoRangeReservedMax로 변경
//! Modify by LHW [2008/6/30] : bAutoGridTextPrecision, bAutoCursorTextPrecision 추가
//! Modify by LHW [2008/7/1] : bSymmetry 추가
//! Modify by LHW [2008/7/24] : szCaption을 삭제하고, szCaption1, szCaption2 추가
//! Modify by LHW [2009/2/4] : bMaxOperation, bAutoRangeGridSize, iAutoRangeGridSize 추가
//! Modify by LHW [2009/3/1] : bGridCalc, bCursorCalc 추가
//! Modify by LHW [2009/5/30] : bMarginIncludeMin, bMarginIncludeMax 추가
//! Modify by LHW [2013/3/26] : bDirection_Plus 추가
struct strGraph2D_Axis_Info	//! 축, Grid, 커서 관련 설정 구조체
{
	bool bAutoRange;		//! true이면 Auto Range
	double dbManualMin;		//! 눈에 보이는 최소값
	double dbManualMax;		//! 눈에 보이는 최대값

	bool bMaxOperation;		//! true이면 bAutoRange가 true일 때, 최대값이 ... 0.01, 0.25, 0.5, 1, 2.5, 5, 10, 25, 50, 100, 250, 500, ... 의 값 중 하나를 가지도록 함
	bool bMinOperation;		//! true이면 bAutoRange가 true일 때, 최대값이 ... -0.01, -0.25, -0.5, -1, -2.5, -5, -10, -25, -50, -100, -250, -500, ... 의 값 중 하나를 가지도록 함

	bool bDirection_Plus;	//! true이면 최소값에서 최대값으로 증가하는 방향으로 그래프가 그려진다.
							//!   - X축에서 true이면, 왼쪽에서 오른쪽으로 증가하는 방향으로 그래프를 그린다. 
							//!   - Y축에서 true이면, 아래쪽에서 위쪽으로 증가하는 방향으로 그래프를 그린다. 

	bool bSymmetry;			//! true이면 bAutoRange가 true일 때, 최대, 최소값 중 절대값이 큰 쪽으로 대칭되게 적용
	E_GRAPH2D_AUTO_RANGE_RESERVED_TYPE eAutoRangeReservedMin;
	double dbAutoRangeReservedMin;	//! 예약 최소값, dbManualMin값에 대응
	E_GRAPH2D_AUTO_RANGE_RESERVED_TYPE eAutoRangeReservedMax;
	double dbAutoRangeReservedMax;	//! 예약 최대값, dbManualMax값에 대응

	E_GRAPH2D_GRID_MARGIN_TYPE eMarginType;	//! 최소값 아래, 최대값 위로 여유 값을 사용하는 방법 설정
											//! bAutoRange가 true이고,
											//! eAutoRangeReservedMin, eAutoRangeReservedMax가 각각 E_GRAPH2D_AUTO_RANGE_RESERVED_NONE 일 때만 사용
	double dbMargin;		//! eMarginType가 E_GRAPH2D_RANGE_MARGIN_PERCENT이면 '(dbManualMax - dbManualMin)'의 %값
							//! eMarginType가 E_GRAPH2D_RANGE_MARGIN_MAX_PERCENT이면 'max(fabs(dbManualMax), fabs(dbManualMin))'의 %값
							//! eMarginType가 E_GRAPH2D_RANGE_MARGIN_VALUE이면 고정 값

	bool bMarginZero;		//! true이면 (dbManualMax - dbManualMin)가 0일 경우, 여유 값을 사용
	double dbMarginZero;	//! 여유 값, %값이 아닌 절대값

	bool bMarginIncludeMin;	//! eAutoRangeReservedMin이 E_GRAPH2D_AUTO_RANGE_RESERVED_STEP일 때, true이면 Margin을 고려
	bool bMarginIncludeMax;	//! eAutoRangeReservedMax이 E_GRAPH2D_AUTO_RANGE_RESERVED_STEP일 때, true이면 Margin을 고려

	bool bShowGrid;				//! false이면 축 눈금이 보이지 않게 됨
	bool bShowMin;				//! false이면 축 최소값이 보이지 않게 됨
	bool bShowMax;				//! false이면 축 최대값이 보이지 않게 됨
	bool bIncrementGrid;		//! true이면 축 최소값부터 dbIncrementGrid만큼 증가시키며 Grid 생성
	double dbIncrementGrid;		//! 축 Grid 증가값
	int iGridSize;				//! bIncrementGrid가 false이면 설정된 개수만큼 최대한 등간격으로 Grid 생성
	bool bAutoRangeGridSize;	//! true이면 bAutoRange가 true일 때, iAutoRangeGridSize를 iGridSize에 설정
	int iAutoRangeGridSize;		//! bAutoRange가 true이면 사용하는 축 Grid의 개수
	bool bAutoGridTextPrecision;//! true이면 Grid에서 표시 글자가 실수형 표기(E_GRAPH2D_GRID_DOUBLE)일 때의 소수점 자리수 자동 설정
	int iGridTextPrecision;		//! Grid에서 표시 글자가 실수형 표기일 때의 소수점 자리수 (0 이상의 정수값)
								//! Grid에서 표시 글자가 지수형 표기일 때의 가수부분의 소수점 자리수 (0 이상의 정수값)
	E_GRAPH2D_GRID_TEXT_TYPE eGridTextType;		//! Grid 표시 글자의 표기 종류(정수형, 실수형, 지수형)
	E_GRAPH2D_DATA_VISUAL_TYPE eGridVisualType;	//! Grid의 종류(숫자, Time 등)
	bool bKilo;				//! true이면 입력된 데이터가 1000보다 크면 1000으로 나누어 주고 'k'를 붙임
							//! eGridVisualType이 E_GRAPH2D_DATA_VISUAL_LINEAR, E_GRAPH2D_DATA_VISUAL_CALCULATION일때만 사용

	E_GRAPH2D_DATA_CALC_TYPE eDataCalcType;		//! 데이터에 1차 함수 식을 적용할 때 어떤 연산을 할 것인지 결정
												//! eGridVisualType이 E_GRAPH2D_DATA_VISUAL_CALCULATION 일 때만 사용
	double dbCoeff;								//! 1차 함수에서 계수 값
	double dbYOffset;							//! 1차 함수에서 Y Offset 값
	bool bGridCalc;								//! true이면 Grid 연산 적용
												//! eGridVisualType이 E_GRAPH2D_DATA_VISUAL_CALCULATION 일 때만 사용
	bool bCursorCalc;							//! true이면 Cursor 연산 적용
												//! eGridVisualType이 E_GRAPH2D_DATA_VISUAL_CALCULATION 일 때만 사용

	bool bTimeGrid_CoupleRow;					//! Grid 문자열이 2줄 일 때 true
												//! eGridVisualType이 E_GRAPH2D_DATA_VISUAL_TIME 일 때만 사용
												//! false이면 szGridTimeFormat1 만 사용
	CString szGridTimeFormat1;					//! Grid 시간 서식 문자열, 예) %Y/%m/%d %H:%M:%S
	CString szGridTimeformat2;					//! Grid 시간 서식 문자열, 예) %Y/%m/%d %H:%M:%S
    
	bool bAutoCursorTextPrecision;				//! true이면 커서 정보창에서 표시 글자가 실수형 표기(E_GRAPH2D_GRID_DOUBLE)일 때의 소수점 자리수 자동 설정
	int iCursorTextPrecision;					//! 커서 정보창에 표시되는 글자의 소수점 자리수 (0 이상의 정수값)
												//! 커서 정보창의 글자는 소수점 자리수를 제외하면, 
												//! eGridTextType, eGridVisualType 등의 Grid 표시 설정과 동일 적용
	CString szCursorTimeFormat;					//! 커서 시간 서식 문자열, 예) %Y/%m/%d %H:%M:%S

	CString szCaption1;			//! 축 이름 (그래프 오른쪽 윗 부분에 표시되는 문자열 [X : ~ , Y : ~])
								//!			E_GRAPH2D_XY_CAPTION_POS_UNITE, E_GRAPH2D_XY_CAPTION_POS_SEPARATE (X, Y의 아래 부분)에서 사용
	CString szCaption2;			//! 축 이름 (그래프 오른쪽 윗 부분에 표시되는 문자열 [X : ~ , Y : ~])
								//!			E_GRAPH2D_XY_CAPTION_POS_SEPARATE에서만 사용(Y의 윗 부분)
	CString szCursorUnit;		//! 커서 정보창에 표시될 단위

	strGraph2D_Axis_Info()
	{
		InitInfo();
	}

	void InitInfo()
	{
		bAutoRange = true;
		dbManualMin = 0.;
		dbManualMax = 0.;

		bMaxOperation = false;
		bMinOperation = false;

		bDirection_Plus = true;

		bSymmetry = false;
		eAutoRangeReservedMin = E_GRAPH2D_AUTO_RANGE_RESERVED_NONE;
		dbAutoRangeReservedMin = 0.;
		eAutoRangeReservedMax = E_GRAPH2D_AUTO_RANGE_RESERVED_NONE;
		dbAutoRangeReservedMax = 0.;

		eMarginType = E_GRAPH2D_RANGE_MARGIN_NONE;
		dbMargin = 0.;

		bMarginZero = true;
		dbMarginZero = 1.;

		bMarginIncludeMin = true;
		bMarginIncludeMax = true;

		bShowGrid = true;
		bShowMin = true;
		bShowMax = true;
		bIncrementGrid = false;
		dbIncrementGrid = 10.;
		iGridSize = 4;
		bAutoRangeGridSize = false;
		iAutoRangeGridSize = 5;
		bAutoGridTextPrecision = true;
		iGridTextPrecision = 1;
		eGridTextType = E_GRAPH2D_GRID_DOUBLE;
		eGridVisualType = E_GRAPH2D_DATA_VISUAL_LINEAR;
		bKilo = false;

		eDataCalcType = E_GRAPH2D_DATA_CALC_MULTIPLY;
		dbCoeff = 1.;
		dbYOffset = 0.;
		bGridCalc = true;
		bCursorCalc = true;

		bTimeGrid_CoupleRow = false;
		szGridTimeFormat1 = _T("%Y/%m/%d %H:%M:%S");
		szGridTimeformat2 = _T("%Y/%m/%d %H:%M:%S");

		bAutoCursorTextPrecision = true;
		iCursorTextPrecision = 1;
		szCursorTimeFormat = _T("%Y/%m/%d %H:%M:%S");

		szCaption1 = _T("");
		szCaption2 = _T("");
		szCursorUnit = _T("");
	}

	COleDateTime GetManualMinTime()	//! X축이 Time일 때는 이 함수를 사용하여 최소값을 반환
	{
		COleDateTime timeMin;
		timeMin.m_dt = dbManualMin;
		return timeMin;
	}

	void SetManualMinTime(COleDateTime timeMin)	//! X축이 Time일 때는 이 함수를 사용하여 최소값을 설정
	{
		dbManualMin = (double)(timeMin.m_dt);
	}

	COleDateTime GetManualMaxTime()	//! X축이 Time일 때는 이 함수를 사용하여 최대값을 반환
	{
		COleDateTime timeMax;
		timeMax.m_dt = dbManualMax;
		return timeMax;
	}

	void SetManualMaxTime(COleDateTime timeMax)	//! X축이 Time일 때는 이 함수를 사용하여 최대값을 설정
	{
		dbManualMax = (double)(timeMax.m_dt);
	}

	strGraph2D_Axis_Info& operator=(const strGraph2D_Axis_Info &input)
	{
		bAutoRange = input.bAutoRange;		
		dbManualMin = input.dbManualMin;
		dbManualMax = input.dbManualMax;

		bMaxOperation = input.bMaxOperation;
		bMinOperation = input.bMinOperation;

		bDirection_Plus = input.bDirection_Plus;

		bSymmetry = input.bSymmetry;
		eAutoRangeReservedMin = input.eAutoRangeReservedMin;
		dbAutoRangeReservedMin = input.dbAutoRangeReservedMin;
		eAutoRangeReservedMax = input.eAutoRangeReservedMax;
		dbAutoRangeReservedMax = input.dbAutoRangeReservedMax;

		eMarginType = input.eMarginType;
		dbMargin = input.dbMargin;

		bMarginZero = input.bMarginZero;
		dbMarginZero = input.dbMarginZero;

		bMarginIncludeMin = input.bMarginIncludeMin;
		bMarginIncludeMax = input.bMarginIncludeMax;
		
		bShowGrid = input.bShowGrid;
		bShowMin = input.bShowMin;
		bShowMax = input.bShowMax;
		bIncrementGrid = input.bIncrementGrid;
		dbIncrementGrid = input.dbIncrementGrid;
		iGridSize = input.iGridSize;
		bAutoRangeGridSize = input.bAutoRangeGridSize;
		iAutoRangeGridSize = input.iAutoRangeGridSize;
		bAutoGridTextPrecision = input.bAutoGridTextPrecision;
		iGridTextPrecision = input.iGridTextPrecision;
		eGridTextType = input.eGridTextType;
		eGridVisualType = input.eGridVisualType;
		bKilo = input.bKilo;

		eDataCalcType = input.eDataCalcType;
		dbCoeff = input.dbCoeff;
		dbYOffset = input.dbYOffset;
		bGridCalc = input.bGridCalc;
		bCursorCalc = input.bCursorCalc;

		bTimeGrid_CoupleRow = input.bTimeGrid_CoupleRow;
		szGridTimeFormat1 = input.szGridTimeFormat1;
		szGridTimeformat2 = input.szGridTimeformat2;

		bAutoCursorTextPrecision = input.bAutoCursorTextPrecision;
		iCursorTextPrecision = input.iCursorTextPrecision;
		szCursorTimeFormat = input.szCursorTimeFormat;

		szCaption1 = input.szCaption1;
		szCaption2 = input.szCaption2;
		szCursorUnit = input.szCursorUnit;

		return *this;
	}
};

//! Modify by LHW [2008/5/23] : E_GRAPH2D_DATA_DRAW_TYPE 과의 구분을 위해 명칭 변경
typedef enum _E_GRAPH2D_DRAW_RANGE_MODE	//! 그래프 선을 그리는 방식의 종류
{
	E_GRAPH2D_VISIBLE_RANGE_DRAW = 0,	//! 눈에 보이는 부분의 그래프만 그림
										//! X축 방향으로 증가함에 따라 Y 데이터가 존재하는 경우에만 유효한 결과를 보여줌
										//! 1) X-Y 그래프를 그릴 때, 2) 그래프가 Overlap된 경우에서 확대할 때 등에는 문제의 여지가 있음
	E_GRAPH2D_ALL_DRAW = 1,				//! 모든 데이터를 그림
}E_GRAPH2D_DRAW_RANGE_MODE;

//! Added by LHW [2008/5/23]
//! Modify by LHW [2009/2/3] : E_GRAPH2D_DATA_DRAW_RECTANGLE를 E_GRAPH2D_DATA_DRAW_SYMBOL로 변경, E_GRAPH2D_DATA_DRAW_LINE_SYMBOL 추가
typedef enum _E_GRAPH2D_DATA_DRAW_TYPE	//! 그래프 표현 방식의 종류
{
	E_GRAPH2D_DATA_DRAW_LINE = 0,		//! 선
	E_GRAPH2D_DATA_DRAW_SYMBOL = 1,		//! 심볼
	E_GRAPH2D_DATA_DRAW_LINE_SYMBOL = 2,//! 선 + 심볼
}E_GRAPH2D_DATA_DRAW_TYPE;

//! Added by LHW [2009/2/3]
//! Modify by LHW [2009/2/16] : 순서 변경
//! Modify by LHW [2009/3/6] : E_GRAPH2D_DRAW_CROSS, E_GRAPH2D_DRAW_DIAMOND, E_GRAPH2D_DRAW_REVERSE_TRIANGLE 추가
typedef enum _E_GRAPH2D_DRAW_SYMBOL_TYPE	//! 그래프의 데이터를 표시하는 심볼의 종류
{
	E_GRAPH2D_DRAW_RECTANGLE = 0,
	E_GRAPH2D_DRAW_CIRCLE = 1, 
	E_GRAPH2D_DRAW_TRIANGLE = 2, 	
	E_GRAPH2D_DRAW_CROSS = 3, 
	E_GRAPH2D_DRAW_DIAMOND = 4, 
	E_GRAPH2D_DRAW_REVERSE_TRIANGLE = 5, 
	E_GRAPH2D_DRAW_FILL_RECT = 6, 
}E_GRAPH2D_DRAW_SYMBOL_TYPE;

//! Added by LHW [2008/7/24]
typedef enum _E_GRAPH2D_LINE_TYPE		//! 그래프 선의 종류
{
	E_GRAPH2D_LINE_TYPE_SOLID = 0,		//! 실선
	E_GRAPH2D_LINE_TYPE_DOT = 1,		//! 간격이 촘촘한 점선
	E_GRAPH2D_LINE_TYPE_DASH = 2,		//! 간격이 듬성한 점선
	E_GRAPH2D_LINE_TYPE_DASH_DOT = 3,	//! 1점쇄선
	E_GRAPH2D_LINE_TYPE_DASH_DOTDOT = 4,//! 2점쇄선
}E_GRAPH2D_LINE_TYPE;

//! Modify by LHW [2008/5/23] : eDrawRangeMode 수정, eDataDrawType, bShowEventRect, iEventRectSize 추가
//! Modify by LHW [2008/5/28] : iEventLineWidth 추가
//! Modify by LHW [2008/7/24] : eLineType 추가
//! Modify by LHW [2009/2/3] : iSymbolLineWidth, iSymbolSize, eSymbolType, eEventSymbolType 추가
//! Modify by LHW [2009/2/4] : 심볼의 크기 관련 초기값 변경
struct strGraph2D_Y_Axis_Info			//! Y축의 설정 구조체
{
	strGraph2D_Axis_Info strAxisInfo;	//! Grid 등의 설정

	bool		bShowGraph;				//! false이면 Grid, Min, Max, 그래프 모두 보이지 않게 됨
	bool		bAxisLeft;				//! true이면 Y축을 왼쪽에 그리고 false이면 오른쪽에 그림	
	COLORREF	clrData;				//! 그래프 선의 색상
	int			iLineWidth;				//! 그래프 선의 두께
	
	COLORREF	clrSymbol;				//! 그래프의 각 데이터를 표시하는 심볼의 색상
	int			iSymbolLineWidth;		//! 그래프의 각 데이터를 표시하는 심볼 선의 두께
	int			iSymbolSize;			//! 그래프의 각 데이터를 표시하는 심볼의 크기
										//! 사각형일 때는 한 변의 길이가 (2 * iLineWidth) + 1 픽셀이 됨, 0 이면 1 픽셀로 표시
	
	E_GRAPH2D_DRAW_RANGE_MODE eDrawRangeMode;	//! 그래프 선을 그리는 방식의 종류를 설정
	E_GRAPH2D_DATA_DRAW_TYPE eDataDrawType;		//! 그래프의 표현 방식의 종류
	E_GRAPH2D_LINE_TYPE eLineType;				//! 그래프 선의 종류, eDataDrawType이 E_GRAPH2D_DATA_DRAW_LINE, E_GRAPH2D_DATA_DRAW_LINE_SYMBOL일 때만 유효
	E_GRAPH2D_DRAW_SYMBOL_TYPE eSymbolType;		//! 그래프의 각 데이터를 표시하는 심볼의 종류

	//! CGraph2DWnd의 m_bDataPointEventMsg가 true일 때만 사용
	bool		bShowEventRect;					//! true이면 Data-Point Event 영역을 눈에 보이게 함, 내부가 투명한 사각형으로 표시
	int			iEventLineWidth;				//! Data-Point Event 영역 선의 두께
	int			iEventRectSize;					//! Data-Point Event 영역의 크기, 한 변의 길이가 (2 * iEventRectSize) + 1 픽셀인 사각형으로 설정
	COLORREF	clrEventRect;					//! Data-Point Event 심볼의 색상
	E_GRAPH2D_DRAW_SYMBOL_TYPE eEventSymbolType;//! Data-Point 영역을 나타내는 심볼의 종류, 크기는 iEventRectSize가 사용

	strGraph2D_Y_Axis_Info()
	{
		InitInfo();
	}

	void InitInfo()
	{
		strAxisInfo.InitInfo();
		strAxisInfo.iGridTextPrecision = 3;
		strAxisInfo.iCursorTextPrecision = 3;
		bShowGraph = true;
		bAxisLeft = true;		
		clrData = RGB(0, 64, 0);
		iLineWidth = 1;
		clrSymbol = RGB(0, 0, 64);
		iSymbolLineWidth = 1;
		iSymbolSize = 3;
		eDrawRangeMode = E_GRAPH2D_VISIBLE_RANGE_DRAW;
		eDataDrawType = E_GRAPH2D_DATA_DRAW_LINE;
		eLineType = E_GRAPH2D_LINE_TYPE_SOLID;
		eSymbolType = E_GRAPH2D_DRAW_RECTANGLE;
		bShowEventRect = false;
		iEventLineWidth = 1;
		iEventRectSize = 3;
		clrEventRect = RGB(0, 0, 64);
		eEventSymbolType = E_GRAPH2D_DRAW_RECTANGLE;
	}

	strGraph2D_Y_Axis_Info& operator=(const strGraph2D_Y_Axis_Info &input)
	{
		strAxisInfo = input.strAxisInfo;
		bShowGraph = input.bShowGraph;
		bAxisLeft = input.bAxisLeft;	
		clrData = input.clrData;
		iLineWidth = input.iLineWidth;
		clrSymbol = input.clrSymbol;
		iSymbolLineWidth = input.iSymbolLineWidth;
		iSymbolSize = input.iSymbolSize;
		eDrawRangeMode = input.eDrawRangeMode;
		eDataDrawType = input.eDataDrawType;
		eLineType = input.eLineType;
		eSymbolType = input.eSymbolType;
		bShowEventRect = input.bShowEventRect;
		iEventLineWidth = input.iEventLineWidth;
		iEventRectSize = input.iEventRectSize;
		clrEventRect = input.clrEventRect;
		eEventSymbolType = input.eEventSymbolType;

		return *this;
	}
};

//! Modify by LHW [2008/8/21] : bShowChk 추가
//! Modify by LHW [2009/2/3] : bShowText, szText, bTextPosExt 추가
struct strValueLineYInfo		//! Y축 특정값 설정 구조체
{
	bool		bShow;			//! 눈에 보이면 true
	bool		bGraphShowChk;	//! true이면 아래 iOverlapIndex의 그래프가 눈에 보이지 않으면 같이 보이지 않고, 
								//! 그래프가 눈에 보이면 같이 보임
	bool		bShowChk;		//! true이면 bShow가 false일 경우, Y축 Auto Range에 Y축 특정값이 반영되지 않음
	int			iOverlapIndex;	//! 그래프 index, 어떤 그래프에서 사용할 것이지 결정, 0 based
								//! 여러 개의 그래프가 있고, 단일 축일때도 해당 그래프 index 설정
								//! 초기값은 0
	double		dbValue;		//! Y축 특정값
	COLORREF	clrValue;		//! 선 색상
	int			iLineWidth;		//! 선 두께
	bool		bShowText;		//! true이면 szText를 보이게 함, 단 Y축 선이 눈에 보여야지만 문자열도 보여짐
	CString		szText;			//! 표시 문자열
	bool		bTextPosExt;	//! true이면 그래프 오른쪽 바깥 부분에 문자열을 위치시키고, false이면 그래프 내부의 오른쪽 부분에 위치

	strValueLineYInfo()
	{
		InitInfo();
	}

	void InitInfo()
	{
		bShow = true;
		bGraphShowChk = true;
		bShowChk = true;
		iOverlapIndex = 0;
		dbValue = 0.;
		clrValue = RGB(0, 0, 0);
		iLineWidth = 1;
		bShowText = false;
		szText = _T("");
		bTextPosExt = false;
	}

	strValueLineYInfo& operator=(const strValueLineYInfo &input)
	{
		bShow = input.bShow;
		bGraphShowChk = input.bGraphShowChk;
		bShowChk = input.bShowChk;
		iOverlapIndex = input.iOverlapIndex;
		dbValue = input.dbValue;
		clrValue = input.clrValue;
		iLineWidth = input.iLineWidth;
		bShowText = input.bShowText;
		szText = input.szText;
		bTextPosExt = input.bTextPosExt;
		
		return *this;
	}
};

struct strValueLineXInfo		//! X축 특정값 설정 구조체
{
	bool		bShow;			//! 눈에 보이면 true

	double		dbValue;		//! X축 특정값
	COLORREF	clrValue;		//! 선 색상
	int			iLineWidth;		//! 선 두께

	CString		szText;			//! 표시 문자열

	strValueLineXInfo()
	{
		InitInfo();
	}

	void InitInfo()
	{
		bShow = true;

		dbValue = 0.;
		clrValue = RGB(0, 0, 0);
		iLineWidth = 1;
		szText = _T("");
	}

	strValueLineXInfo& operator=(const strValueLineXInfo &input)
	{
		bShow = input.bShow;
		dbValue = input.dbValue;
		clrValue = input.clrValue;
		iLineWidth = input.iLineWidth;
		szText = input.szText;

		return *this;
	}
};

#define WM_GRAPH2D_DECIDE_TIME_X_AXIS WM_USER + 1240	//! X축이 시각을 표시할 때, 눈에 보이는 X축의 최소, 최대값을 결정한 후 발생하는 메시지, Added by LHW [2008/8/18]
														//! WPARAM : NULL, LPARAM : NULL

typedef enum _E_GRAPH2D_TITLE_ALIGN		//! 제목 정렬 종류
{
	E_GRAPH2D_TITLE_ALIGN_LEFT = 0,		//! 왼쪽 정렬
	E_GRAPH2D_TITLE_ALIGN_CENTER = 1,	//! 중앙 정렬
	E_GRAPH2D_TITLE_ALIGN_RIGHT = 2,	//! 오른쪽 정렬
}E_GRAPH2D_TITLE_ALIGN;

//! Modify by LHW [2009/2/26] : 폰트 종류, 문자 크기 추가
struct strGraph2DTitleInfo					//! 제목 설정 구조체
{
	bool					bShow;				//! true이면 제목이 보이고, false이면 보이지 않음
	bool					bBold;				//! true이면 글자를 굵게 처리
	E_GRAPH2D_TITLE_ALIGN	eAlign;				//! 제목 정렬 종류
	double					dbLeftMargin;		//! 왼쪽 가장자리와의 거리, 단위 : 컨트롤 전체 폭에 대한 %
												//! E_GRAPH2D_TITLE_ALIGN_LEFT, E_GRAPH2D_TITLE_ALIGN_CENTER에서만 사용
	double					dbRightMargin;		//! 오른쪽 가장자리와의 거리, 단위 : 컨트롤 전체 폭에 대한 %
												//! E_GRAPH2D_TITLE_ALIGN_RIGHT에서만 사용
	COLORREF				clrTitle;			//! 제목 색상
	CString					szTitle;			//! 제목 문자열
	bool					bTitleFontHeight;	//! 제목 표시 문자 글자 크기를 자동 설정
	int						iTitleFontHeight;	//! 제목 표시 문자 글자 크기, 음수값으로 설정
	CString					szTitleFontName;	//! 제목 표시 문자의 폰트 종류

	strGraph2DTitleInfo()
	{
		InitInfo();
	}

	void InitInfo()
	{
		bShow = false;
		bBold = false;
		eAlign = E_GRAPH2D_TITLE_ALIGN_CENTER;
		dbLeftMargin = 0.;
		dbRightMargin = 0.;
		clrTitle = RGB(0, 0, 0);
		szTitle = _T("");
		bTitleFontHeight = true;
		iTitleFontHeight = -10;
		szTitleFontName = _T("MS Sans Serif");
	}

	strGraph2DTitleInfo& operator=(const strGraph2DTitleInfo &input)
	{
		bShow = input.bShow;
		bBold = input.bBold;
		eAlign = input.eAlign;
		dbLeftMargin = input.dbLeftMargin;
		dbRightMargin = input.dbRightMargin;
		clrTitle = input.clrTitle;
		szTitle = input.szTitle;
		bTitleFontHeight = input.bTitleFontHeight;
		iTitleFontHeight = input.iTitleFontHeight;
		szTitleFontName = input.szTitleFontName;

		return *this;
	}
};

//! Added by LHW [2008/7/24] : X-Y 표시 문자열의 표시 방법, strGraph2D_Axis_Info의 szCaption1을 표시
//! Modify by LHW [2008/8/1] : E_GRAPH2D_XY_CAPTION_POS_UNITE_Y 추가
//! Modify by LHW [2008/10/24] : E_GRAPH2D_XY_CAPTION_POS_ONLY_XY 추가
//! 2012/12/20 : E_GRAPH2D_XY_CAPTION_POS_ONLY_XY 추가
typedef enum _E_GRAPH2D_XY_CAPTION_POSITION
{
	E_GRAPH2D_XY_CAPTION_POS_NONE = 0,		//! 표시하지 않음
	E_GRAPH2D_XY_CAPTION_POS_ONLY_XY = 1,	//! X축 오른쪽에 'X'문자 표시, Y축 위쪽에 'Y'문자 표시만 표시
	E_GRAPH2D_XY_CAPTION_POS_UNITE = 2,		//! 한 줄로 통합하여 축 바로위 왼쪽 혹은 오른쪽에 위치, X축 오른쪽에 'X'문자 표시, Y축 위쪽에 'Y'문자 표시
	E_GRAPH2D_XY_CAPTION_POS_SEPARATE = 3,	//! 각 축의 위, 아래에 표시
	E_GRAPH2D_XY_CAPTION_POS_UNITE_Y = 4,	//! X축은 E_GRAPH2D_XY_CAPTION_POS_SEPARATE와 동일하게 표시, Y축은 E_GRAPH2D_XY_CAPTION_POS_UNITE와 동일하게 표시
	E_GRAPH2D_XY_CAPTION_POS_ONE_Y = 5,		//! X축은 E_GRAPH2D_XY_CAPTION_POS_SEPARATE와 동일하게 표시, Y축은 strGraph2DResourceInfo의 szCaptionY 표시
	E_GRAPH2D_XY_CAPTION_POS_ONLY_X = 6,	//! X축은 E_GRAPH2D_XY_CAPTION_POS_SEPARATE와 동일하게 표시, Y축은 표시하지 않음
}E_GRAPH2D_XY_CAPTION_POSITION;

//! Added by LHW [2008/5/14] : clrCursorSelectedLine 추가
//! Modify by LHW [2008/7/24] : eXYCaptionPosition 추가
//! Modify by LHW [2008/8/01] : bYCaptionLeftPos 추가
//! Modify by LHW [2008/12/27] : szCaptionY 추가
//! Modify by LHW [2009/2/26] : 제목의 폰트 종류, 문자 크기 삭제
struct strGraph2DResourceInfo				//! 색상, X축 설정 구조체
{
	COLORREF	clrEntireBackGround;		//! 그래프 컨트롤 전체 바탕색
	COLORREF	clrGraphBackGround;			//! 실제 그래프 부분 바탕색
	COLORREF	clrAxis;					//! 축선의 색상
	COLORREF	clrGrid;					//! Grid 점선의 색상
	COLORREF	clrGridText;				//! Grid 눈금 글자의 색상
	COLORREF	clrCursorLine;				//! 커서 선의 색상
	COLORREF	clrCursorSelectedLine;		//! 선택된 커서 선의 색상
	COLORREF	clrCursorText;				//! 커서값 글자의 색상
	COLORREF	clrCursorTextBorder;		//! 커서 정보창의 테두리 선의 색상
	COLORREF	clrCursorPoint;				//! 커서 점의 색상
	COLORREF	clrCursorTextBack;			//! 커서 정보창의 바탕색
	COLORREF	clrLegend;					//! X,Y 축 정보 글자의 색상
	COLORREF	clrZoomArea;				//! 확대 영역 색상

	bool		bGridFontHeight;			//! true이면 Grid 표시 문자 글자 크기를 자동 설정
	bool		bCursorFontHeight;			//! true이면 Cursor 표시 문자 글자 크기를 자동 설정
	bool		bLegendFontHeight;			//! true이면 X-Y 정보 문자열 표시 문자 글자 크기를 자동 설정
	
	int			iGridFontHeight;			//! Grid 표시 문자 글자 크기, 음수값으로 설정
	int			iCursorFontHeight;			//! Cursor 표시 문자 글자 크기, 음수값으로 설정
	int			iLegendFontHeight;			//! X-Y 정보 문자열 표시 문자 글자 크기, 음수값으로 설정
	
	CString		szGridFontName;				//! Grid 표시 문자의 폰트 종류
	CString		szCursorFontName;			//! Cursor 표시 문자의 폰트 종류
	CString		szLegendFontName;			//! X-Y 정보 문자열 표시 문자의 폰트 종류
	
	int			iAxisThickness;				//! 축 선의 두께
	int			iGridThickness;				//! Grid 선의 두께
	int			iCursorLineThickness;		//! 커서 선의 두께
	int			iCursorTextBorderThickness;	//! 커서 정보창의 테두리 선의 두께

	strGraph2D_Axis_Info strAxisInfoX;		//! X축 설정
	CString		szCaptionY;					//! Y축 이름, E_GRAPH2D_XY_CAPTION_POS_ONE_Y에서만 사용

	bool		bAutoDivisionLength;		//! true이면 iDivisionLength값을 자동 설정
	int			iDivisionLength;			//! Grid에서 값을 표시하는 부분의 눈금 길이

	strGraph2DTitleInfo strMainTitleInfo;	//! 주 제목 설정
	strGraph2DTitleInfo strSubTitleInfo;	//! 보조 제목 설정
	
	E_GRAPH2D_XY_CAPTION_POSITION eXYCaptionPosition;//! X-Y 표시 문자열 표시 방법
	bool		bYCaptionLeftPos;			//! eXYCaptionPosition이 E_GRAPH2D_XY_CAPTION_POS_UNITE, E_GRAPH2D_XY_CAPTION_POS_UNITE_Y일 때,
											//! true이면 Y축 문자열이 왼쪽에 위치

	strGraph2DResourceInfo()
	{
		InitInfo();
	}

	void InitInfo()
	{
		clrEntireBackGround = RGB(231, 231, 231);
		clrGraphBackGround = RGB(255, 255, 255);
		clrAxis = RGB(0, 0, 0);
		clrGrid = RGB(0, 0, 0);		
		clrGridText = RGB(0, 0, 0);
		clrCursorLine = RGB(255, 0, 255);
		clrCursorSelectedLine = RGB(255, 0, 0);
		clrCursorPoint = RGB(255, 0, 0);
		clrCursorText = RGB(0, 0, 0);
		clrCursorTextBorder = RGB(0, 0, 0);
		clrCursorTextBack = RGB(255, 255, 128);
		clrLegend = RGB(0, 0, 0);
		clrZoomArea = RGB(255, 128, 128);

		bGridFontHeight = true;
		bCursorFontHeight = true;
		bLegendFontHeight = true;
		
		iGridFontHeight = -10;
		iCursorFontHeight = -10;
		iLegendFontHeight = -10;
		
		szGridFontName = _T("MS Sans Serif");
		szCursorFontName = _T("MS Sans Serif");
		szLegendFontName = _T("MS Sans Serif");
		
		iAxisThickness = 1;
		iGridThickness = 1;
		iCursorLineThickness = 1;
		iCursorTextBorderThickness = 1;

		strAxisInfoX.InitInfo();
		strAxisInfoX.iGridTextPrecision = 1;
		strAxisInfoX.iCursorTextPrecision = 1;

		szCaptionY = _T("");

		bAutoDivisionLength = true;
		iDivisionLength = 4;

		strMainTitleInfo.InitInfo();
		strSubTitleInfo.InitInfo();
		
		eXYCaptionPosition = E_GRAPH2D_XY_CAPTION_POS_NONE;
		bYCaptionLeftPos = true;
	}

	strGraph2DResourceInfo& operator=(const strGraph2DResourceInfo &input)
	{
		clrEntireBackGround = input.clrEntireBackGround;
		clrGraphBackGround = input.clrGraphBackGround;
		clrAxis = input.clrAxis;
		clrGrid = input.clrGrid;		
		clrGridText = input.clrGridText;
		clrCursorLine = input.clrCursorLine;
		clrCursorSelectedLine = input.clrCursorSelectedLine;
		clrCursorPoint = input.clrCursorPoint;
		clrCursorText = input.clrCursorText;
		clrCursorTextBorder = input.clrCursorTextBorder;
		clrCursorTextBack = input.clrCursorTextBack;
		clrLegend = input.clrLegend;
		clrZoomArea = input.clrZoomArea;

		bGridFontHeight = input.bGridFontHeight;
		bCursorFontHeight = input.bCursorFontHeight;
		bLegendFontHeight = input.bLegendFontHeight;
		
		iGridFontHeight = input.iGridFontHeight;
		iCursorFontHeight = input.iCursorFontHeight;
		iLegendFontHeight = input.iLegendFontHeight;
		
		szGridFontName = input.szGridFontName;
		szCursorFontName = input.szCursorFontName;
		szLegendFontName = input.szLegendFontName;
		
		iAxisThickness = input.iAxisThickness;
		iGridThickness = input.iGridThickness;
		iCursorLineThickness = input.iCursorLineThickness;
		iCursorTextBorderThickness = input.iCursorTextBorderThickness;

		strAxisInfoX = input.strAxisInfoX;

		szCaptionY = input.szCaptionY;

		bAutoDivisionLength = input.bAutoDivisionLength;
		iDivisionLength = input.iDivisionLength;

		strMainTitleInfo = input.strMainTitleInfo;
		strSubTitleInfo = input.strSubTitleInfo;
			
		eXYCaptionPosition = input.eXYCaptionPosition;
		bYCaptionLeftPos = input.bYCaptionLeftPos;

		return *this;
	}
};

//! Added by LHW [2008/8/22] : 함수식으로 그래프를 그릴 경우 필요한 데이터 구조체 추가
//! Modify by LHW [2008/8/23] : bShowGraphChk, iOverlapIndex 추가
//! Modify by LHW [2008/8/26] : 복사 생성자, bShowChk 추가
//! Modify by LHW [2008/9/1] : dbInputOffsetX, dbOutputOffsetY, bUseExp 추가
struct strGraph2DEquationInfo
{
	//! iCoeffSize가 1이면 Y축 방향의 직선 (y = a),
	//! iCoeffSize가 2이면 1차 그래프 (y = ax + b), 
	//! iCoeffSize가 3이면 2차 그래프 (y = ax^2 + bx + c) 등으로 그래프가 그려짐
	//! a, b, c 등은 모두 함수식 계수값
	
	int iCoeffSize;			//! 함수식 계수의 개수
	double *pdbCoeff;		//! 함수식 계수

	double dbStartRangeX;	//! 함수식으로 그리는 그래프의 X축 시작 지점
	double dbEndRangeX;		//! 함수식으로 그리는 그래프의 X축 마침 지점

	double dbInputOffsetX;	//! X 데이터의 Offset 값
	double dbOutputOffsetY;	//! Y 결과값의 Offset 값

	int iOverlapIndex;		//! 이 그래프와 연결된 Main 그래프의 index
	int iCustomData;		//! 사용자 데이터
	double dbCustomData;	//! 사용자 데이터

	bool bUseExp;			//! 지수 함수(함수식 고정) 사용, 함수식 계수의 개수가 반드시 2개이어야 함

	E_GRAPH2D_LINE_TYPE eLineType;	//! 그래프 선 종류
	COLORREF clrLine;				//! 그래프 선 색상
	int iLineWidth;					//! 그래프 선의 굵기, 실선일 경우에만 2이상의 값이 적용 가능
	bool bShow;						//! true이면 그래프가 보이게 됨
	bool bShowChk;					//! true이면 bShow가 false이면 Auto Range 등의 설정에서 제외시킴
	bool bShowGraphChk;				//! true이면 bShow가 true이더라도, 짝이 되는 그래프가 보이지 않으면 보이지 않게 함

	strGraph2DEquationInfo()
	{
		InitInfo();
	}

	~strGraph2DEquationInfo()
	{
		ReleaseCoeffBuf();
	}

	void InitInfo()
	{
		iCoeffSize = 0;
		pdbCoeff = NULL;
		dbStartRangeX = 0.;
		dbEndRangeX = 0.;
		dbInputOffsetX = 0.;
		dbOutputOffsetY = 0.;
		iOverlapIndex = -1;
		iCustomData = 0;
		dbCustomData = 0.;
		bUseExp = false;
		eLineType = E_GRAPH2D_LINE_TYPE_SOLID;
		clrLine = RGB(0, 0, 255);
		iLineWidth = 1;
		bShow = true;
		bShowChk = true;
		bShowGraphChk = true;
	}

	bool MakeCoeffBuf(int iNewSize)
	{
		if ( iNewSize <= 0 )
		{
			return false;
		}

		ReleaseCoeffBuf();

		pdbCoeff = new double[iNewSize + 1];
		if ( pdbCoeff == NULL )
		{
			return false;
		}

		for ( int i = 0; i < (iNewSize + 1); i++ )
		{
			pdbCoeff[i] = 0.;
		}

		iCoeffSize = iNewSize;

		return true;
	}

	void ReleaseCoeffBuf()
	{
		if ( pdbCoeff != NULL )
		{
			delete [] pdbCoeff;
			pdbCoeff = NULL;
		}
		iCoeffSize = 0;
	}

	strGraph2DEquationInfo(const strGraph2DEquationInfo &input)	//! 복사 생성자
	{
		InitInfo();

		if ( input.iCoeffSize > 0 && input.pdbCoeff != NULL )
		{
			MakeCoeffBuf(input.iCoeffSize);
		}

		if ( iCoeffSize > 0 && pdbCoeff != NULL )
		{
			for ( int i = 0; i < iCoeffSize; i++ )
			{
				pdbCoeff[i] = input.pdbCoeff[i];
			}
		}

		dbStartRangeX = input.dbStartRangeX;
		dbEndRangeX = input.dbEndRangeX;
		dbInputOffsetX = input.dbInputOffsetX;
		dbOutputOffsetY = input.dbOutputOffsetY;

		iOverlapIndex = input.iOverlapIndex;
		iCustomData = input.iCustomData;
		dbCustomData = input.dbCustomData;

		bUseExp = input.bUseExp;

		eLineType = input.eLineType;
		clrLine = input.clrLine;
		iLineWidth = input.iLineWidth;
		bShow = input.bShow;
		bShowChk = input.bShowChk;
		bShowGraphChk = input.bShowGraphChk;
	}

	strGraph2DEquationInfo& operator=(const strGraph2DEquationInfo &input)
	{
		if ( (iCoeffSize != input.iCoeffSize) || pdbCoeff == NULL )
		{
			if ( input.iCoeffSize > 0 )
			{
				if ( MakeCoeffBuf(input.iCoeffSize) == false )
				{
					return *this;
				}				
			}
			else
			{
				ReleaseCoeffBuf();
			}
		}

		if ( iCoeffSize > 0 && pdbCoeff != NULL )
		{
			for ( int i = 0; i < iCoeffSize; i++ )
			{
				pdbCoeff[i] = input.pdbCoeff[i];
			}
		}

		dbStartRangeX = input.dbStartRangeX;
		dbEndRangeX = input.dbEndRangeX;
		dbInputOffsetX = input.dbInputOffsetX;
		dbOutputOffsetY = input.dbOutputOffsetY;

		iOverlapIndex = input.iOverlapIndex;
		iCustomData = input.iCustomData;
		dbCustomData = input.dbCustomData;

		bUseExp = input.bUseExp;

		eLineType = input.eLineType;
		clrLine = input.clrLine;
		iLineWidth = input.iLineWidth;
		bShow = input.bShow;
		bShowChk = input.bShowChk;
		bShowGraphChk = input.bShowGraphChk;

		return *this;
	}
};
