//! 2D 직교좌표 그래프 컨트롤의 색상, 선 두께, Range, Y축 특정값 표시선, 확대 Record 등의 각종 설정 정보를 저장하는 클래스
//! Maked by LHW (2008/3/14 ~ )
//! 최종 작업일 [2009/6/4]
//! Modify by LHW [2008/6/12] : operator 연산자 재정의 부분의 오류 일괄 수정

#pragma once

#include <afxtempl.h>			//! CArray, CTypedPtrArray 사용
#include ".\\Graph2D_Struct.h"

struct strZoomRecord
{
	bool bAutoRange;
	double dbMin;
	double dbMax;
	
	void InitInfo()
	{
		bAutoRange = true;
		dbMin = 0.;
		dbMax = 0.;		
	}

	strZoomRecord& operator=(const strZoomRecord &info)  //! = 연산자 재정의
	{
		bAutoRange = info.bAutoRange;
		dbMin = info.dbMin;
		dbMax = info.dbMax;		

		return *this;
	}
};

//! Modify by LHW [2008/5/14] : m_penCursorLineSelected 추가
//! Modify by LHW [2008/6/30] : m_eGridTextType, m_eCursorTextType, m_iGridTextPrecision, m_iCursorTextPrecision 추가
//! Modify by LHW [2008/7/02] : m_dbAutoRangeMin, m_dbAutoRangeMax 추가
//! Modify by LHW [2009/5/30] : X축 최소, 최대값의 Step 범위값 추가
class CGraph2D_Resource
{
public:
	CGraph2D_Resource(void);
	~CGraph2D_Resource(void);

	strGraph2DResourceInfo m_strResourceInfo;

	E_GRAPH2D_GRID_TEXT_TYPE m_eGridTextType;	//! Grid 표시 글자의 표기 종류(정수형, 실수형, 지수형)
	E_GRAPH2D_GRID_TEXT_TYPE m_eCursorTextType;	//! 커서 표시 글자의 표기 종류(정수형, 실수형, 지수형)
	int m_iGridTextPrecision;					//! Grid의 소수점 자리수
	int m_iCursorTextPrecision;					//! 커서값의 소수점 자리수
	double m_dbAutoRangeMin;					//! Auto Range일 때의 최소값
	double m_dbAutoRangeMax;					//! Auto Range일 때의 최대값

	CBrush		m_brEntireBackGround;
	CBrush		m_brGraphBackGround;
	CBrush		m_brCursorPoint;
	CBrush		m_brCursorTextBack;
	CBrush		m_brZoomArea;

	CPen		m_penAxis;
	CPen		m_penGrid;	
	CPen		m_penCursorLine;
	CPen		m_penCursorLineSelected;
	CPen		m_penCursorTextBorder;

	CFont		m_ftGridText;
	CFont		m_ftCursorText;
	CFont		m_ftLegend;
	CFont		m_ftMainTitle;
	CFont		m_ftSubTitle;

	CArray<strZoomRecord, strZoomRecord&> m_arrZoomRecord;		//! 확대 기능을 사용할 때마다 확대 관련 정보를 저장

	double m_dbPanOffset;	//! Pan 기능에서 X축 방향으로의 Offset값

	CArray<double, double> m_arrMinBound;	//! X축 최소값의 Step 범위값
	CArray<double, double> m_arrMaxBound;	//! X축 최대값의 Step 범위값
	
	void SetResource();
	void ReleaseResource();
	void AddZoomRecord();
};

//! Modify by LHW [2008/4/10] : m_brData 추가
//! Modify by LHW [2008/4/11] : m_iElementIndex 추가
//! Modify by LHW [2008/5/23] : m_penEvent 추가
//! Modify by LHW [2008/6/30] : m_eGridTextType, m_eCursorTextType, m_iGridTextPrecision, m_iCursorTextPrecision 추가
//! Modify by LHW [2008/7/02] : m_dbAutoRangeMin, m_dbAutoRangeMax 추가
//! Modify by LHW [2008/10/25] : m_iLeftXPtofYAxis, m_iRightXPtofYAxis 추가
//! Modify by LHW [2009/2/3] : m_brData를 m_brSymbol로 수정, m_penSymbol, m_brEvent 추가
//! Modify by LHW [2009/2/14] : m_dbTempRangeMax, m_dbTempRangeMin 추가
//! Modify by LHW [2009/5/30] : Y축 최소, 최대값의 Step 범위값 추가
class CGraph2D_ResourceY
{
public:
	CGraph2D_ResourceY(void);
	~CGraph2D_ResourceY(void);

	int m_iElementIndex;	//! Y축 리소스 저장소의 내부 index

	strGraph2D_Y_Axis_Info m_strResourceYinfo;

	E_GRAPH2D_GRID_TEXT_TYPE m_eGridTextType;	//! Grid 표시 글자의 표기 종류(정수형, 실수형, 지수형)
	E_GRAPH2D_GRID_TEXT_TYPE m_eCursorTextType;	//! 커서 표시 글자의 표기 종류(정수형, 실수형, 지수형)
	int m_iGridTextPrecision;					//! Grid의 소수점 자리수
	int m_iCursorTextPrecision;					//! 커서값의 소수점 자리수
	double m_dbAutoRangeMin;					//! Auto Range일 때의 최소값
	double m_dbAutoRangeMax;					//! Auto Range일 때의 최대값
	int m_iLeftXPtofYAxis;						//! 왼쪽에 Y축을 보여줄 X 좌표
	int m_iRightXPtofYAxis;						//! 오른쪽에 Y축을 보여줄 X 좌표

	double m_dbTempRangeMax;					//! Range 최대값을 임시 저장
	double m_dbTempRangeMin;					//! Range 최소값을 임시 저장

	CPen		m_penYAxis;	//! Y축선을 그리는 펜, Multi-Axis일 때 필요
	CPen		m_penData;	//! 실제 그래프를 그리는 펜
	CPen		m_penSymbol;//! 실제 그래프 데이터 점을 그리는 펜
	CPen		m_penEvent;	//! Data-Point Event 영역을 그릴 때 사용하는 펜
	CBrush		m_brSymbol;	//! 실제 그래프 데이터 점을 그리는 브러시
	CBrush		m_brEvent;	//! Data-Point Event 영역을 그릴 때 사용하는 브러시
	int			m_iDrawXPt;	//! Y축선을 그릴 X 좌표

	CArray<strZoomRecord, strZoomRecord&> m_arrZoomRecord;		//! 확대 기능을 사용할 때마다 확대 관련 정보를 저장

	double		m_dbPanOffset;	//! Pan 기능에서 Y축 방향으로의 Offset값

	CArray<double, double> m_arrMinBound;	//! Y축 최소값의 Step 범위값
	CArray<double, double> m_arrMaxBound;	//! Y축 최대값의 Step 범위값
	
	void SetResource();
	void ReleaseResource();
	void AddZoomRecord();
};

//! X축 특정 값 표시선의 클래스, Added by LHW [2008/4/19]
class CGraph2D_ValueLineX
{
public:
	CGraph2D_ValueLineX(void);
	~CGraph2D_ValueLineX(void);

	int m_iElementIndex;	//! X축 특정 값 표시선의 내부 index

	strValueLineXInfo m_strXLineInfo;	//! X축 특정 값 표시선의 설정 정보

	CPen		m_penXLine;
	CRect		m_crSelect;	//! 마우스 이벤트 영역

	int			m_iFontHeight;
	CFont		m_ftValueLineX;
    
	void SetResource();
	void ReleaseResource();
};

//! Y축 특정 값 표시선의 클래스, Added by LHW [2008/3/29]
//! Modify by LHW [2008/4/11] : m_iElementIndex 추가
//! Modify by LHW [2009/2/3] : m_iFontHeight, m_ftValueLineY 추가
class CGraph2D_ValueLineY
{
public:
	CGraph2D_ValueLineY(void);
	~CGraph2D_ValueLineY(void);

	int m_iElementIndex;	//! Y축 특정 값 표시선의 내부 index

	strValueLineYInfo m_strYLineInfo;	//! Y축 특정 값 표시선의 설정 정보

	CPen		m_penYLine;

	int			m_iFontHeight;
	CFont		m_ftValueLineY;

	void SetResource();
	void ReleaseResource();
};

//! Added by LHW [2008/4/11] : 보조 커서 구조체에서 사용자가 직접 입력하면 안되는 부분을 분리
//! Modify by LHW [2008/5/31] : iRealDataIndex, dbXData, dbYData 추가
//! Modify by LHW [2008/8/04] : crSelectX, crSelectY 추가
struct strGraph2D_Aux_Cursor_Extend
{
	int iElementIndex;	//! 보조 커서 구조체의 내부 index
	bool bValid;		//! true이면 보조 커서의 정보가 유효

	int iRealDataIndex;	//! 실제 데이터 index, 아니면 가장 가까운 데이터의 index
	double dbXData;		//! X 값
	double dbYData;		//! Y 값

	int iXPos;			//! X 위치
	int iYPos;			//! Y 위치

	strGraph2D_Aux_Cursor strAuxCursorUser;	//! 사용자가 입력할 수 있는 보조 커서 구조체

	CRect crSelectX;	//! 커서 선택 영역
	CRect crSelectY;	//! 커서 선택 영역

	void InitInfo()
	{
		iElementIndex = -1;
		bValid = true;
		iXPos = 0;
		iYPos = 0;
		iRealDataIndex = -1;
		dbXData = 0.;
		dbYData = 0.;
		strAuxCursorUser.InitInfo();
		crSelectX.SetRectEmpty();
		crSelectY.SetRectEmpty();
	}

	strGraph2D_Aux_Cursor_Extend& operator=(const strGraph2D_Aux_Cursor_Extend &input)
	{
		iElementIndex = input.iElementIndex;
		bValid = input.bValid;
		iXPos = input.iXPos;
		iYPos = input.iYPos;
		iRealDataIndex = input.iRealDataIndex;
		dbXData = input.dbXData;
		dbYData = input.dbYData;
		strAuxCursorUser = input.strAuxCursorUser;
		crSelectX = input.crSelectX;
		crSelectY = input.crSelectY;

		return *this;
	}
};

//! 보조 커서 그룹의 클래스, Added by LHW [2008/3/31]
//! Modify by LHW [2008/4/11] : strGraph2D_Aux_Cursor_Extend로 m_arrCursorInfo을 생성하도록 수정
//! Modify by LHW [2008/4/11] : m_iElementIndex, m_iAuxCursorElementCnt, IsExistAuxCursorElementIndex, GetAuxCursorIndexFromElementIndex 추가
//! Modify by LHW [2008/4/19] : SetResource에서 m_penAuxCursor 생성 부분 수정
//! Modify by LHW [2008/8/04] : 보조 커서의 Pen 부분을 수정
class CGraph2D_Aux_CursorGroup
{
public:
	CGraph2D_Aux_CursorGroup(void);
	~CGraph2D_Aux_CursorGroup(void);

	int m_iElementIndex;		//! 보조 커서 그룹의 내부 index
	int m_iAuxCursorElementCnt;	//! 보조 내부 커서 index를 정하기 위한 변수

	CArray<strGraph2D_Aux_Cursor_Extend, strGraph2D_Aux_Cursor_Extend&> m_arrCursorInfo;	//! 그룹에 속한 보조 커서의 설정 정보

	strGraph2D_Aux_CursorGroup	m_strGroupInfo;	//! 보조 커서의 색상, 선 두께 등의 설정

	CPen						m_penAuxCursorSolid;
	CPen						m_penAuxCursorDot;
	CPen						m_penAuxCursorDash;
	//CPen						m_penAuxCursor;
	CFont						m_ftAuxCursorText;

	void SetResource();
	void ReleaseResource();
	int GetCursorInfoSize();					//! m_arrCursorInfo의 개수를 반환

	int GetAuxCursorPossibleElementIndex();					//! 사용 가능한 내부 index 반환, 오류가 있으면 -1을 반환
	bool IsExistAuxCursorElementIndex(int iElementIndex);	//! 입력된 iElementIndex를 가진 strGraph2D_Aux_Cursor_Extend가 있으면 true를 반환	
	bool GetAuxCursorIndexFromElementIndex(int iElementIndex, int &iIndex);	//! 입력된 내부 index, iElementIndex에 대한 실제 index를 반환
	bool GetAuxCursorElementIndexFromIndex(int iIndex, int &iElementIndex);	//! 실제 index에 대해 내부 index, iElementIndex를 반환
};

//! 자식 커서의 클래스, Added by LHW [2008/6/12]
//! Modify by LHW [2008/6/13] : m_dbDeltaX, m_dbDeltaY, m_iDataIndex 추가
//! Modify by LHW [2008/6/14] : m_bDataValid 추가
//! Modify by LHW [2008/6/15] : m_iCursorDataIndex, m_bCursorMoved 추가
//! Modify by LHW [2008/6/16] : m_penSelectCursorLine 추가
class CGraph2D_Child_Cursor
{
public:
	CGraph2D_Child_Cursor(void);
	~CGraph2D_Child_Cursor(void);

	int m_iElementIndex;	//! 자식 커서 그룹의 내부 index
	int m_iDataIndex;		//! 자식 커서의 데이터 index
	int m_iCursorDataIndex;	//! 부모 커서의 데이터 index

	bool m_bCursorMoved;	//! 부모 커서가 움직이면 true
	bool m_bDataValid;		//! 데이터의 유효성 여부

	double m_dbXData;		//! 자식 커서의 X 데이터
	double m_dbYData;		//! 자식 커서의 Y 데이터

	double m_dbDeltaX;		//! 자식 커서와 커서의 X 데이터 차이값
	double m_dbDeltaY;		//! 자식 커서와 커서의 Y 데이터 차이값

	int m_iXPos;			//! 자식 커서의 X 위치
	int m_iYPos;			//! 자식 커서의 Y 위치

	CRect m_crSelectX;		//! 자식 커서 선택 영역
	CRect m_crSelectY;		//! 자식 커서 선택 영역
	CRect m_crInfo;			//! 자식 커서의 정보창 출력 영역
	CRect m_crData;			//! m_crInfo의 Y 좌표를 결정할 때의 m_DataRect 값 저장, 인쇄 기능때문에 필요

	strGraph2D_Child_Cursor m_strCursorInfo;	//! 자식 커서의 색상, 선 두께 등의 설정

	CBrush		m_brCursorPoint;
	CBrush		m_brCursorTextBack;

	CPen		m_penCursorLine;
	CPen		m_penSelectCursorLine;
	CPen		m_penCursorTextBorder;

	CFont		m_ftCursorText;

	void SetResource();
	void ReleaseResource();
};

#define REGION_CURSOR_SELECT_SIZE	4	//! 영역 표시 커서 선의 개수
#define REGION_CURSOR_LEFT_VERT		0	//! 영역 표시 커서 선에서 왼쪽 수직 선
#define REGION_CURSOR_UP_HORZ		1	//! 영역 표시 커서 선에서 위쪽 수평 선
#define REGION_CURSOR_DOWN_HORZ		2	//! 영역 표시 커서 선에서 아래쪽 수평 선
#define REGION_CURSOR_RIGHT_VERT	3	//! 영역 표시 커서 선에서 오른쪽 수직 선
#define REGION_CURSOR_CENTER		4	//! 영역 표시 커서 선으로 둘러싸인 사각 영역, Added by LHW [2008/12/1]

//! 영역 표시 커서, Added by LHW [2008/11/28]
//! Modify by LHW [2008/11/30] : IsPtInSelect 수정
//! Modify by LHW [2008/12/1] : m_crSelectRegion, m_ptMouseSave 추가
class CGraph2D_Region_Cursor
{
public:
	CGraph2D_Region_Cursor(void);
	~CGraph2D_Region_Cursor(void);

	int m_iElementIndex;	//! 영역 표시 커서의 내부 index

	strGraph2D_Region_Cursor m_strCursorInfo;

	CPen		m_penCursorLine;
	CPen		m_penSelectCursorLine;

	CFont		m_ftCursorText;

	double		m_dbMinDataX;	//! 커서의 X 최소 데이터
	double		m_dbMaxDataX;	//! 커서의 X 최대 데이터
	double		m_dbMinDataY;	//! 커서의 Y 최소 데이터
	double		m_dbMaxDataY;	//! 커서의 Y 최대 데이터

	int			m_iMinPosX;		//! 커서의 X 최소 위치
	int			m_iMaxPosX;		//! 커서의 X 최대 위치
	int			m_iMinPosY;		//! 커서의 Y 최소 위치
	int			m_iMaxPosY;		//! 커서의 Y 최대 위치

	CRect		m_crSelectRegion;	//! 커서 선으로 둘러싸인 영역
	CPoint		m_ptMouseSave;		//! 마우스 이벤트가 발생한 좌표 저장, m_crSelectRegion관련하여 필요
	
	CRect		m_crSelectLine[REGION_CURSOR_SELECT_SIZE];		//! 커서 선 선택 영역
	bool IsPtInSelect(CPoint ptInput, int &iCursorLineIndex);	//! 커서 선 선택 영역안에 있으면 true를 반환
																//! true로 반환될 경우 선택된 커서 선의 index를 반환
	
	void SetResource();
	void ReleaseResource();
};

//! 함수식으로 그려지는 그래프의 클래스, Added by LHW [2008/8/22]
//! Modify by LHW [2008/8/25] : Y축 최소, 최대값 추가
class CGraph2D_Equation
{
public:
	CGraph2D_Equation(void);
	~CGraph2D_Equation(void);

	int m_iElementIndex;	//! 함수식으로 그려지는 그래프의 내부 index

	strGraph2DEquationInfo m_strEquationInfo;

	double m_dbDataMinY;	//! Y축 최소값
	double m_dbDataMaxY;	//! Y축 최대값

	CPen m_penLine;

	void SetResource();
	void ReleaseResource();
	void ReleaseStructureBuf();
};

//! Modify by LHW [2008/4/4] : iSearchMargin 추가
//! Modify by LHW [2008/4/11] : iElementIndex 추가
//! Modify by LHW [2008/4/18] : bShowPoint 추가
//! Modify by LHW [2008/4/19] : bShowGraphChk 추가
//! Modify by LHW [2008/6/12] : iAuxCursorIndex -> iAuxCursorGroupElementIndex
//! Modify by LHW [2008/7/01] : szXData, szYData 추가
//! Modify by LHW [2008/8/01] : bShowStringX, bShowStringY 추가
//! Modify by LHW [2009/6/4] : 마우스를 움직일 때의 커서 동작의 오차를 줄이기 위해 iSearchMargin의 초기값을 100으로 설정
struct strGraph2DCursorInfo
{
	int iElementIndex;		//! 커서의 내부 index

	int iDataIndex;			//! 커서가 위치하는 데이터의 Index
	int iSelectOverlapIndex;//! 커서가 위치하는 그래프의 index

	double dbXData;		//! 커서의 X 데이터
	double dbYData;		//! 커서의 Y 데이터

	CString szXData;	//! 커서의 X 데이터 문자열
	CString szYData;	//! 커서의 Y 데이터 문자열

	int iXPos;			//! 커서의 X 위치
	int iYPos;			//! 커서의 Y 위치

	CRect crSelectX;	//! 커서 선택 영역
	CRect crSelectY;	//! 커서 선택 영역
	CRect crInfo;		//! 커서의 정보창 출력 영역
	CRect crData;		//! crInfo의 Y 좌표를 결정할 때의 m_DataRect 값 저장, 인쇄 기능때문에 필요

	bool bShowGraphChk;	//! true이면 아래 iSelectOverlapIndex의 그래프가 눈에 보이지 않으면 같이 보이지 않고, 
						//! 그래프가 눈에 보이면 같이 보임
	bool bShowInfo;		//! 커서의 정보창 출력 여부
	bool bShowValueX;	//! 커서의 X값 출력 여부
	bool bShowValueY;	//! 커서의 Y값 출력 여부
	bool bShowPoint;	//! 커서에 표시 사각형 출력 여부
	bool bShowStringX;	//! 커서값에 'X : ' 문자열 표시
	bool bShowStringY;	//! 커서값에 'Y : ' 문자열 표시

	E_GRAPH2D_CURSOR_LINE_MODE eLineMode;	//! 커서 선 표시 방식
	bool bMaxHold;							//! true이면 반드시 현재 눈에 보이는 그래프의 최대값에 커서가 위치시킴
	int iSearchMargin;						//! 커서값 찾는 방식이 X축 방향으로 일정한 구간을 정하여 그 안에서 커서값을 찾을 경우 구간의 여유 값
											//! 이 값이 클수록 더 많은 데이터를 검색

	int iAuxCursorGroupElementIndex;		//! 연동하는 보조 커서 그룹의 내부 index

	strGraph2DCursorInfo()
	{
		InitInfo();
	}

	void InitInfo()
	{
		iElementIndex = -1;
		iDataIndex = -1;
		iSelectOverlapIndex = -1;
		dbXData = 0.;
		dbYData = 0.;
		szXData = _T("");
		szYData = _T("");
		iXPos = -1;
		iYPos = -1;		
		crSelectX.SetRectEmpty();
		crSelectY.SetRectEmpty();
		crInfo.SetRectEmpty();
		crData.SetRectEmpty();
		bShowGraphChk = true;
		bShowInfo = true;
		bShowValueX = true;
		bShowValueY = true;
		bShowPoint = true;
		bShowStringX = false;
		bShowStringY = false;
		eLineMode = E_GRAPH2D_CURSOR_LINE_XY;
		bMaxHold = false;
		iSearchMargin = 100;
		iAuxCursorGroupElementIndex = -1;	//! -1은 보조 커서가 없다는 의미로 사용되므로 초기값을 바꾸면 안됨
	}

	strGraph2DCursorInfo& operator=(const strGraph2DCursorInfo &info)  //! = 연산자 재정의
	{
		iElementIndex = info.iElementIndex;
		iDataIndex = info.iDataIndex;
		iSelectOverlapIndex = info.iSelectOverlapIndex;
		dbXData = info.dbXData;
		dbYData = info.dbYData;
		szXData = info.szXData;
		szYData = info.szYData;
		iXPos = info.iXPos;
		iYPos = info.iYPos;		
		crSelectX = info.crSelectX;
		crSelectY = info.crSelectY;
		crInfo = info.crInfo;
		crData = info.crData;
		bShowGraphChk = info.bShowGraphChk;
		bShowInfo = info.bShowInfo;
		bShowValueX = info.bShowValueX;
		bShowValueY = info.bShowValueY;
		bShowPoint = info.bShowPoint;
		bShowStringX = info.bShowStringX;
		bShowStringY = info.bShowStringY;
		eLineMode = info.eLineMode;
		bMaxHold = info.bMaxHold;
		iSearchMargin = info.iSearchMargin;
		iAuxCursorGroupElementIndex = info.iAuxCursorGroupElementIndex;
		
		return *this;
	}
};
