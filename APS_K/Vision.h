#pragma once


#include "stdafx.h"
#ifdef  _M_X64
	LONG64 MFTYPE ProcessingFunction(LONG64 HookType, MIL_ID HookId, void MPTYPE *HookDataPtr);
#else 
	long MFTYPE ProcessingFunction(long HookType, MIL_ID HookId, void MPTYPE *HookDataPtr);
#endif


typedef struct
{
	int		liveMode;
	MIL_ID  MilGrabImage;
	MIL_ID  MilSmallImage;
} HookDataStruct;


#define		MAX_BUFFER_SIZE			10		// MdigProcess 에서 사용 할 영상 버퍼 개수..


#define MAX_PIXEL_CNT	50000
#define MAX_CROSS_CNT	10000	
#define MAX_BOX_CNT		20000
#define MAX_LINE_CNT	10000
#define MAX_TEXT_CNT	10000

//! MbufBayer 함수에서 사용할 입력 데이터 버퍼의 개수
//! Added by LHW (2013/3/13)
const int iBufSize_Bayer = 3;

class CElemPixel
{
public:
	int iCnt;
	CPoint p[MAX_PIXEL_CNT];
	COLORREF c[MAX_PIXEL_CNT];


	CElemPixel(){iCnt=0;}
	~CElemPixel(){}

	void addList(int iPosX, int iPosY, COLORREF color);
	void addList(CPoint Pos, COLORREF color);
	void draw(HDC OverlayDC, double dZoomFactorX, double dZoomFactorY);
};

class CElemCross
{
public:
	int iCnt;
	int iSize[MAX_CROSS_CNT];
	CPoint p[MAX_CROSS_CNT];
	COLORREF c[MAX_CROSS_CNT];


	CElemCross(){iCnt=0;}
	~CElemCross(){}

	void addList(int iPosX, int iPosY, int w, COLORREF color);
	void addList(CPoint Pos, int w, COLORREF color);
	void draw(HDC OverlayDC, double dZoomFactorX, double dZoomFactorY);
};

class CElemBox
{
public:
	int iCnt;
	int iStyle[MAX_BOX_CNT];
	CRect r[MAX_BOX_CNT];
	COLORREF c[MAX_BOX_CNT];

	CElemBox(){iCnt=0;}
	~CElemBox(){}

	void addList(int iLeft, int iTop, int iRight, int iBottom, int iLineStyle, COLORREF color);
	void addList(CRect rBox, int iLineStyle, COLORREF c);	
	void draw(HDC OverlayDC, double dZoomFactorX, double dZoomFactorY, bool largeFlag);
};
class CElemEllipse
{
public:
	int iCnt;
	int iStyle[MAX_BOX_CNT];
	CPoint cp1[MAX_BOX_CNT];
	CPoint cp2[MAX_BOX_CNT];
	COLORREF c[MAX_BOX_CNT];

	CElemEllipse(){iCnt=0;}
	~CElemEllipse(){}

	void addList(CPoint pos1,CPoint pos2, int iLineStyle, COLORREF c);	
	void draw(HDC OverlayDC, double dZoomFactorX, double dZoomFactorY);
};
class CElemLine
{
public:
	int iCnt;
	int iStyle[MAX_LINE_CNT];
	CPoint sp[MAX_LINE_CNT];
	CPoint ep[MAX_LINE_CNT];
	COLORREF c[MAX_LINE_CNT];

	CElemLine(){iCnt=0;}
	~CElemLine(){}

	void addList(int iSx, int iSy, int iEx, int iEy, int iLineStyle, COLORREF color);
	void draw(HDC OverlayDC, double dZoomFactorX, double dZoomFactorY);
};

class CElemText
{
public:
	int iCnt;
	CPoint p[MAX_TEXT_CNT];
	CPoint s[MAX_TEXT_CNT];
	CString str[MAX_TEXT_CNT];
	CString FontName[MAX_TEXT_CNT];
	COLORREF c[MAX_TEXT_CNT];

	CElemText(){iCnt=0;}
	~CElemText(){}

	void addList(int iPosX, int iPosY, CString Str, COLORREF color, int iSizeX, int iSizeY, CString FontStr);
	void draw(HDC OverlayDC, double dZoomFactorX, double dZoomFactorY);
};

class CVision
{
public:
	int m_iDispMode;									/* 0:원본 영상, 1:광축 검사 이진화 영상, 2:LensShade 보정..*/
	int m_iThValue;

	MIL_ID		MilApplication;							/* MilApplition id*/
	MIL_ID		MilSystem;								/* MilSystem id */
	MIL_ID		MilDigitizer;							/* MilDigitizer id */

	CCriticalSection m_csGrab;
	CCriticalSection m_acsGrabLock[2];					//! MilGrabImage 보호용, Added by LHW (2013/2/26)
	CCriticalSection m_acsAlignGrabLock;				//! MilGrabImage 보호용, Added by LHW (2013/2/26)

	MIL_ID			 MilGrabImage[2];					/* 획득 영상 Copy 용 */	
	MIL_ID			 MilGrabImageChild[Cam_Cnt*2];
	MIL_ID			 MilGrabBufferList[MAX_BUFFER_SIZE];	/* 영상 획득 용 버퍼 */
	HookDataStruct	 UserHookData;
	SYSTEMTIME		 m_aTimeGrab[2];					//! 영상 취득했을 때의 시각, Added by LHW (2013/2/26)


	MIL_ID		MilProcImage[2];						/* 영상 처리용 버퍼 */
	MIL_ID		MilProcImageChild[Cam_Cnt*2];			/* 영상 처리용 버퍼 차일드 */
	SYSTEMTIME	m_aTimeGrab_Proc[2];					//! 영상 취득했을 때의 시각, Added by LHW (2013/2/26)

	CCriticalSection m_csProcImageCV;					//! Process용 Open CV 이미지 버퍼 보호용
	SYSTEMTIME		 m_TimeProcImageCV;					//! Process용 Open CV 이미지 버퍼 취득 시각

	//! Added by LHW (2013/3/12)
	SYSTEMTIME  m_aTimeBayer [iBufSize_Bayer];			//! 영상 취득했을 때의 시각
	MIL_ID      MilBayerImage[iBufSize_Bayer];			//! CCD Sensor에서 취득한 Bayer 영상 이미지 버퍼, Added by LHW (2013/3/12)
	MIL_ID		MilWBCoefficients;						//! Array for the white balance coefficients, Added by LHW (2013/3/12)
	int			m_iIndex_Cvt_Clr_Working;				//! Color 변환 중인 버퍼의 index, 0 based
	int			m_iIndex_Cvt_Clr_Ready;					//! Color 변환 준비 완료된 버퍼의 index, 0 based
	int			m_iIndex_Cvt_Clr_Used;					//! Color 변환 완료된 버퍼의 index, 0 based
	bool		m_bFlag_Use_WB_Coeff;					//! true이면, MilWBCoefficients 사용한다. 


	MIL_ID		MilOptImage;							/* AutoRun 중 광축 영상 Display용 */
	MIL_ID		MilOptDisplayImage;
	MIL_ID		MilOptOverlayImage;
#ifdef  _M_X64
	LONG64		TransparentColor_Opt;
#else 
	long		TransparentColor_Opt;
#endif
	
	MIL_ID		MilSfrTargetImage;
	MIL_ID		MilDefectImage;							/* AutoRun 중 이물 검사 Display용 */
	MIL_ID		MilDefectDisplayImage;
	MIL_ID		MilDefectOverlayImage;
#ifdef  _M_X64
	LONG64		TransparentColor_Defect;
#else 
	long		TransparentColor_Defect;
#endif
	
	MIL_ID      MilSaveDisplayDefectImage;				//! 이물 검사 결과 이미지 (화면에 Display 되는 작은 이미지 크기로 저장), Added by LHW (2013/4/1)

	//! 이물 검사에서 사용 Added by LHW (2013/3/6)

	MIL_ID		MilSmallImage[2];						/* 디스플레이용 버퍼 */
	MIL_ID		MilSmallImageChild[Cam_Cnt*2];			/* 디스플레이용 버퍼 차일드 */

	MIL_ID		MilDisplay[MAX_CAM_NO];					/* Mildisplay id */

	MIL_ID		MilOverlayImage[MAX_CAM_NO];			/* MilOverlayImage id */
#ifdef  _M_X64
	LONG64		TransparentColor[MAX_CAM_NO];			/* Transparentcolor id */
#else 
	long		TransparentColor[MAX_CAM_NO];			/* Transparentcolor id */
#endif
	

	//unsigned char* Image[Cam_Cnt*2];
	unsigned char* MilImageBuffer[Cam_Cnt * 2];



	MIL_ID			MilSmallShadeImage;					/* Lens Shade 보정 용 */	
	MIL_ID			MilShadeImage;						/* Lens Shade 보정 용 */	
	unsigned char*	ImageShade;



	MIL_ID		MilMarkImage[3][2];
	MIL_ID		MilMarkSmallImage[3][2];
	MIL_ID		MilMarkDisplay[3][2];

	MIL_ID		MilTempImage;

	MIL_ID		PatModel[3][2];						/* 패턴매칭 마크 모델 */
	MIL_ID		PatResult[3][2];					/* 패턴매칭 결과 */
	MIL_ID		ModModel[3][2];						/* 지오매트릭 마크 모델 */
	MIL_ID		ModResult[3][2];					/* 지오매트릭 결과 */
	MIL_ID		ChartCenterPatternImage;			/* 중심점 확인용 패턴매칭 마크 모델 */
	MIL_ID		ChartCenterPatternResult;			/* 중심점 확인용 패턴매칭 결과 */

	MIL_ID		FieldPatternImage[COMMON_LAST_MARK_CNT];// LAST_MARK_CNT];			/* 필드 ROI용 패턴매칭 마크 모델 */
	MIL_ID		FieldPatternResult[COMMON_LAST_MARK_CNT];// LAST_MARK_CNT];			/* 필드 ROI용 패턴매칭 결과 */

	MIL_ID		MilMask;
	HANDLE		hMaskBuf;
	unsigned char* ucMaskBuf;

	MIL_ID		MilMarkSetImage;
	MIL_ID		MilMarkSetDisplay;
	MIL_ID		MilMarkSetOverlayImage;
#ifdef  _M_X64
	LONG64		MarkSetTransparentColor;
#else 
	long		MarkSetTransparentColor;
#endif
	/*MIL_ID	MilBinaryImage;
	MIL_ID	MilBlobFeatureList;
	MIL_ID	MilBlobResult;
*/
	CElemPixel  pixellist[MAX_CAM_NO];
	CElemCross	crosslist[MAX_CAM_NO];
	CElemBox	boxlist[MAX_CAM_NO];
	CElemLine	linelist[MAX_CAM_NO];
	CElemText	textlist[MAX_CAM_NO];
	CElemEllipse ellipselist[MAX_CAM_NO];

	double		m_dReduceFactorX, m_dReduceFactorY;		// 카메라 모듈의 해상도가 모델 마다 틀리므로, 계산값을 변수로 가지고 있음..
	

	bool initVB();										/* Vision Alloc		  */
	void closeVB();										/* Vision Close		  */
	bool initDisplay();									/* Display Alloc	  */
	void initMarkDisplay(int iSizeX, int iSizeY);		/* Mark Display Alloc */
	void InitMarkSetDisplay(int iSizeX, int iSizeY);	/* MarkSet Alloc	  */
	void enableOverlay();								/* 오버레이 설정		  */
	void enableMarkSetOverlay();						/* MarkSet Overlay    */

	void InitBuffer_AutoDisplay(int iSizeX, int iSizeY);		/* AutoRun Display용 */
	void enableOverlay_AutoDisp();								/* AutoRun Display용 */
	void DeleteBuffer_AutoDisp();								/* AutoRun Display용 */
	void GetBuffer_AutoDisp(int iMode, 
							double dFactorX, 
							double dFactorY);					/* AutoRun 중 이미지 얻기 */

	void StartGrab();
	void StopGrab();
	
	void CloseMarkSetDisplay();

	void clearOverlay(int iCamNo=999);		/* 오버레이 클리어 */
 	void drawOverlay(int iCamNo=999, bool largeFlag=false, bool BaseFlag=true);		/* 오버레이 그리기 */
 	void drawBase(int iCamNo=999);			/* 베이스 그리기 */
	void drawResult(int iCamNo, int iMarkNo, CDPoint Center, double dRate, double dAngle, int iResult);
	void drawResolResult(int iCamNo, int iSizeX, int iSizeY, CDPoint Center, int iResult);
	//! <---------------------------------------
	//! Added by LHW (2013/2/5)
	bool ChangeColor_Box(int iCamNo, COLORREF c);
	void ChangeColor_Box_All(COLORREF c);
	//! <---------------------------------------

	int	 findMark(int iCamNo, int iMarkType, bool flag = false);
	int	 findComAlignMark(int iCamNo, int iMarkType, bool flag = false);
	//완제품모드 Align
	
	int	 patternMatching(int iSearchMode, int iCh, int iMarkType, int iMarkNo, CDPoint& Center, double& dRate, double& dAngle);			/* 패턴 매칭 */
	int	 geometricModelFinder(int iSearchMode, int iCh, int iMarkType, int iMarkNo, CDPoint& Center, double& dRate, double& dAngle);	/* 지오매트릭 */
	bool markRegist(int iCamNo, int iMarkType, int iMarkNo, CRect rBox);																/* 마크 등록 */
	void geometricMarkPreProc(int iCamNo, int iMarkType, int iMarkNo);

    CRect m_clRectFov[MAX_FOV_COUNT];
    CRect m_clRectSnr[MAX_SNR_COUNT];

	bool FnShmEdgeFind(BYTE* ChartRawImage, bool mAutoMode = true);		//김성봉 책임 SHM 모델 차트 모서리 좌표 찾기 231121 CDPoint& clDLCenter, CDPoint& clDRCenter, 
	void loadImage(int iCamNo, CString DirStr);				/* 파일이미지 로드 */
	void saveImage(int iCamNo, CString DirStr);				/* 이미지 파일로 저장 */
	void loadImageonExplorer(int iCamNo);					/* 탐색기 상에서 이미지 로드 */
	void saveImageonExplorer(int iCamNo);					/* 탐색기 상에서 이미지 저장 */
	void saveRealImage(int iCamNo, bool bResult=false);		/* 실제 영상 저장 */
	void saveCaptureImage(bool bResult=false);				/* 캡처 이미지 저장*/
	void bmpImageSaveFn(int iCamNo, int index = 0);
	void setLiveMode(int flag);
	int  getLiveMode();

	void getSnapImage(int camNo);

	void MiuBufferFree();
	void MiuCCdBufferReset();
	bool MiuBufferAlloc(int fi_Width, int fi_Height);
	void MiuBufferUpdate();		//! Added by LHW (2013/2/26)
	void MiuBufferIndexReady();	//! Added by LHW (2013/3/13)

	void MilBufferUpdate();		//! MilGrab -->MilProcImage

	CRect rcFindROI[MAX_CAM_NO][MAX_MARK];


    bool m_FovSetMode;          //Fov 영역 보이게
    bool m_SnrSetMode;          //Snr 영역 보이게

	CVision()
	{
        m_FovSetMode = false;          //Fov 영역 보이게
        m_SnrSetMode = false;          //Snr 영역 보이게


		m_iDispMode = 0;
		m_iThValue = 150;

		int i = 0;

		for(i=0; i<MAX_CAM_NO; i++)
		{
			pixellist[i].iCnt = crosslist[i].iCnt = boxlist[i].iCnt = linelist[i].iCnt = textlist[i].iCnt = 0;

			MilDisplay[i] = M_NULL;
			MilOverlayImage[i] = M_NULL;
		}

		MilApplication = M_NULL;
		MilSystem = M_NULL;
		MilDigitizer = M_NULL;

		for ( i = 0; i < iBufSize_Bayer; i++ )
		{
			MilBayerImage[i] = M_NULL;
		}		

		m_bFlag_Use_WB_Coeff = false;


		for ( i = 0; i < 2; i++ )
		{
			MilGrabImage[i] = M_NULL;
			MilProcImage[i] = M_NULL;
			MilSmallImage[i] = M_NULL;
		}

		for ( i = 0; i < (Cam_Cnt*2); i++ )
		{
			MilGrabImageChild[i] = M_NULL;
			MilProcImageChild[i] = M_NULL;
			MilSmallImageChild[i] = M_NULL;
		}

		for ( i = 0; i < MAX_BUFFER_SIZE; i++ )
		{
			MilGrabBufferList[i] = M_NULL;
		}

		MilTempImage = M_NULL;

		MilOptImage = M_NULL;
		MilOptDisplayImage = M_NULL;
		MilOptOverlayImage = M_NULL;

		MilDefectImage = M_NULL;
		MilDefectDisplayImage = M_NULL;
		MilDefectOverlayImage = M_NULL;
		MilSaveDisplayDefectImage = M_NULL;

		MiuBufferIndexReady();
	}
};