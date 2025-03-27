
#pragma once


#include	"stdAfx.h"
#include "Library\Utility\TimeChecker.h"
#define		MAX_CCD_STEP_NO		150
#define		MAX_SFR_DATA_CNT	4000
#define		MAX_DEFECT_CNT		10


typedef struct strdefADO
{
public:
	double dOffset_TiltTx;
	double dOffset_TiltTy;
	double dLaserIn[4];
	double dLaserOut[4];
	double dPCBMotor[6];

	double dOffset_Align[3];	//[X/Y/T]
	double dLans_Align[3];
	double dPCBHolder_Align[3];
} strdefADO, *pstrdefADO;

class COffset
{
public:
	// Epoxy 도포부..
	float	f_epoxy_x_dispense_offset[4];
	float	f_epoxy_y_dispense_offset[4];
	float	f_epoxy_z_dispense_offset[4];
	
	COffset();
};

class CPasswordData
{
public:
	bool	m_bFlag;
	char	m_szPassword[100];

	CPasswordData();
	void Load();
};


typedef struct strOsCheck
{
	bool	m_bOS_Check_Result;
	int		m_iIndex_Result[OS_PIN_COUNT];
	float	m_fReadUpper[OS_PIN_COUNT];
	float	m_fReadLower[OS_PIN_COUNT];
} STR_OS_CHECK, *PSTR_OS_CHECK;

typedef struct strSFRInspect
{
	int		iDataCnt[COMMON_MTF_INSP_CNT];// MTF_INSP_CNT];
	float	fMotorPos[MAX_CCD_STEP_NO][6];
	float	fImageAlign[MAX_CCD_STEP_NO][4];					// SFR 마크 중심 위치를 인식한 후 CCM의 TiltX, TiltX, 


	CRect	rcROI[4];						// 원형 마크 검색 영역..
    CRect	rcFovROI[4];
    CRect	rcSnrROI[4];
    


	CRect	rect[COMMON_LAST_MARK_CNT];// LAST_MARK_CNT];			// 챠트에 보이는 19개 사각형 인식 좌표..
	CRect	_64_Sfr_Rect[COMMON_MTF_INSP_CNT];// MTF_INSP_CNT];		// 챠트에 보이는 64개 SFR 검사 영역..
	mCDPoint	Sfr_pos[MAX_CCD_STEP_NO][5];	// AA Tile 계산 용 코너 부 마크 좌표
	//double *res;
	float	fSfrN4[MAX_CCD_STEP_NO][5];
	float	_64_fSfrN4[COMMON_MTF_INSP_CNT];// MTF_INSP_CNT];
	double	fSFR_DataX[COMMON_MTF_INSP_CNT][MAX_SFR_DATA_CNT];
	double	fSFR_DataY[COMMON_MTF_INSP_CNT][MAX_SFR_DATA_CNT];

	int		iMaxIndex[5];

	double	dMaxPos[COMMON_MTF_INSP_CNT];// MTF_INSP_CNT];			// 필드별 SFR최대값인 Z위치값
	double	dMaxPos_Insp[COMMON_MTF_INSP_CNT];//MTF_INSP_CNT];		// ROI별 SFR최대값인 Z위치값
	double	dMaxSfr_Insp[COMMON_MTF_INSP_CNT];//MTF_INSP_CNT];		// ROI별 SFR최대값

	double	dMaxSfr_StepLog[COMMON_MTF_INSP_CNT];//MTF_INSP_CNT];		// ROI별 SFR최대값
	double	dMaxSfr_Frist_StepLog[COMMON_MTF_INSP_CNT];//MTF_INSP_CNT];		// ROI별 SFR최대값
	double	dMaxSfr_Second_StepLog[COMMON_MTF_INSP_CNT];//MTF_INSP_CNT];		// ROI별 SFR최대값

	int     nTiltCalIndex[COMMON_MTF_INSP_CNT];
	double	dTilt_X;
	double	dTilt_Y;
	
	

} STR_SFR_INSPECT, *PSTR_SFR_INSPECT;



typedef struct strDefectInspect
{
	int		iCnt[4];			// 0:Small, 1:Middle, 2:Large
	RECT	rect[MAX_DEFECT_CNT];

} STR_DEFECT_INSPECT, *PSTR_DEFECT_INSPECT;


class CInfoDlg; //! Added by LHW (2013/5/9)


class CTask
{
private:
	//! Auto White Balance에서 임시 저장소로 사용한다. 
	double  m_dGainRed, m_dGainGreen, m_dGainBlue;
	double  m_dAvgRed, m_dAvgGreen, m_dAvgBlue;
	double  m_dGain_Real;

	int     m_iFlag_Max_Color;	//! 0 : Red, 1 : Green, 2 : Blue

public:
	char    LotNo[256];
	char    ChipID[256];
	char    sNum[256];
	char    Pn[256];
	unsigned long long  FuseID;
	int		nCountChipID;

	bool	bConnectBarcode;
	int		AutoFlag;			// 0:정지 1:자동 2: 일시정지 20130405
	int		AutoReday;			// 0:운전준비 안된 상태 1: 운전 준비 상태
	bool	bMotorRunStop;
	int		LensTask, PCBTask;
	int		ReadyTask;
	int		PauseLensStep, PausePCBStep; 

	int     m_iPcbPickupNo, m_iLensPickupNoCentering, m_iLensPickupNoGrip;

	int		interlockLens;			//lens가 laser 끝나고 본딩위치 가기전까지 interlock
	int		interlockPcb;			//pcb가 본딩위치(xy)이동후 본딩 z이동전 대기
	int		MainLensAutoFlag;	// 0:정지, 1:자동, 2:일시정지
	int		MainPcbAutoFlag;	// 0:정지, 1:자동, 2:일시정지

	double	dSocketRecvTime;
	int		iSocketRecvNo;
	int		iRecvLenCnt[5];		//응답 완료 처리[0=Tx, 1=Ty, 2=AlignX, 3=AlignY, 4=AlignT) => -1=대기중, 1=응답 완료
	int		iRecvLenACK[2];		//0=일치모델 없음, 1=일치모델 존재, -1:초기값

	int		MainPCErrFlag, MainAirFlag, iEMSwitchFlag, iDoorFlag, iDoorFlag2, iAmpFaultFlag, iHomeErrorFlag, iUsbModuleFlag, iLimitErrorFlag;

	bool	b_mark_result[MARK_CNT];				// 0:PCB_Sensor	1:PCB_상단, 2:Lens 상단
	double	d_mark_pos_x[MARK_CNT][2], d_mark_pos_y[MARK_CNT][2], d_mark_theta[MARK_CNT][2], d_mark_rate[MARK_CNT][2];
	double	d_Align_offset_x[MARK_CNT], d_Align_offset_y[MARK_CNT], d_Align_offset_th[MARK_CNT];
	double  d_Holder_Th;
	double	d_Align_offset_xt[3], d_Align_offset_yt[3];

	bool    bFlag_Auto_Exposure_Time;	//! Auto Exposure Time Thread가 동작 중이면 true 설정

	bool    bFlag_Auto_White_Balance;	//! Auto White Balance Thread가 동작 중이면 true 설정
	

    std::vector<int> m_vDirection;
    std::vector<double> m_vFrquency;
    std::vector<double> m_vOffset;
    std::vector<double> m_vSFR;
    std::vector<double> m_vThreshold;
    std::vector<TROIPoint> m_vROI;

	STR_OS_CHECK		osCheck;
	STR_DEFECT_INSPECT	defect;
	STR_SFR_INSPECT		SFR;
	bool sfrResult;
	int		m_iHour;
	int		m_iMin;
	int		m_iSec;	
	double oldLaserTx;
	double oldLaserTy;
	int		m_iCnt_Step_AA_Total;
	int		m_iCnt_1Step_End;
	int     m_iCnt_Best_Step;
	int codeResult;		// 50㎛ code 계산 결과값
	double dFov[5];		// code별 화각..

	int		m_iCnt_RepeatAA;	  //반복성 AA 현재 횟수
	bool	b_FlagAARepeat;		//반복성 AA 플래그

	int m_iCnt_Step_AA;
	int m_iCnt_Second_AA_Start;

	double	dOpticalShiftX;
	double	dOpticalShiftY;
	CRect	rOpticalROI;
	int		iOpticalThVal;
	double  dOpticalPosX;
	double  dOpticalPosY;
	double  dPcbAlignTh;
	double  dEPL;
	double  dLensRotation;
	int		iCnt_Total_Defect;
	int		m_bOkFlag;
	int		m_bOkDispense;			//자동운전중 1회성 도포 완료 여부
	int		m_bOKLensPass;			//자동 운전 중 PCB Unit에서 Lens Unit으로 Lens 이송 완료 되었는지 여부
	int		m_bPBStart;				//Start버튼 눌려지면 0, Door Open해서 제품 흘릴 경우 1(바코드 정상 Reading)

	bool	bFirstAA;				/* Active Alignment 2번째 수행 분류를 위해 */
	int		iMTFCnt;				// Active Alignment시, MTF 확인 -> 이동 횟수
	bool	m_bFlag_Fine_Move;		/* MTF 값이 리미트 이상이면 fine pitch 이동 */


	int		m_iStart_Step_LENS;
	int		m_iEnd_Step_LENS;

	int		m_iStart_Step_PCB;
	int		m_iEnd_Step_PCB;

	int		m_iRetry_Opt;
	int		m_iRetry_Opt_Lens;

	int		m_i_Shade_Avg;

	CRect m_FindCircleRect[4];
	CPoint m_CircleP[4];
	double m_CirclePos_x[4];
	double m_CirclePos_y[4];

	int  sMiniOcTemp;							//보정 20
    CPoint m_clPtFov[MAX_FOV_COUNT];
	CRect m_FindFovRect[MAX_FOV_COUNT];
    double m_FovPos_x[4];
    double m_FovPos_y[4];


    CPoint m_clPtSnr[MAX_FOV_COUNT];

	double	m_dShift_IMG_X;
	double	m_dShift_IMG_Y;
	double	m_dShift_IMG_TH;

	/* NG 배출 */
	bool m_bNgUnload;
	bool m_bOkUnload;
	bool m_bUvPassUnload;

	/* Time Check Index 0    : Total Time		*/
	/* Time Check Index 1~2  : Epoxy Time		*/
	/* Time Check Index 3~4  : Through Time		*/
	/* Time Check Index 5~6  : Fine Time		*/
	/* Time Check Index 7~8  : Opt & Def Time	*/
	/* Time Check Index 9~10 : UV Time			*/
	/* Time Check Index 11   : 시작부터 클린위치 이동 전 까지 (Epoxy 제외) */ 
	CTimeChecker	m_timeChecker;
	double      dUvOffset_Aver;
	double		m_dTime_Total;
	double		m_dTime_TotalAA;
	double		m_dTime_Epoxy;
	double		m_dTime_FineAA;
	double		m_dTime_UV;
	double		m_dTime_LaserDpm;

	double		dMTF_SFR[COMMON_MTF_INSP_CNT];// MTF_INSP_CNT];	// MTF측증치
	double		dMTF_0F_Avg;			// 0필드 MTF 평균값
	double		dMTF_4F_Avg;			// 0.4필드 MTF 평균값
	double		dMTF_5F_Avg;			// 0.5필드 MTF 평균값
	double		dMTF_7F_Avg;			// 0.7필드 MTF 평균값
	double		dMTF_8F_Avg;			// 0.8필드 MTF 평균값

	bool bBcrAutoCount;
	bool bSfrLogView;
	bool bTrinityDoubleDispense;
	int			m_iDrawBarStep;
	bool		m_bFlag_Decrease_SFR;		/* 시작 데이터가 연속 감소가 있을 경우 true */
	
	double		LensTaskTime, PCBTaskTime;
	int			LensOnStage;	//Lens	1:공급 요청 반복. 2: 공급 동작 시작, 100:공급 완료.;
	int			PcbOnStage;		//PCB	1:공급 요청 반복. 2: 공급 동작 시작, 100:공급 완료    200:검사 완료   0:없음 1:PCB 있음 2: PCB 검사 완료;
	bool		MUICheckflag;
	int			m_iFineThCnt;

	bool		m_LinePulse_Mode_Change;
	bool		m_b_AA_Retry_Flag;

	double m_PcbLaserAfterTx;
	double m_PcbLaserAfterTy;




	double		m_Laser_Point[8];

	double dFinalResult[COMMON_MTF_INSP_CNT][1];//MTF_INSP_CNT][1] ;

		// 0 : Laser 편차값, 1 : PCB 편차값-1차 Align 시
	double		m_dataOffset_x[MARK_CNT];
	double		m_dataOffset_y[MARK_CNT];
	double		m_dataOffset_th[MARK_CNT];

	//-- Manual 수동 틸팅 편차값 
	int			m_iRtnTiltingDlg;
	double		dTiltingManual[2];
	double		dAlignManual[3];
	double		dAAPcbMotor[6];

	//-- 도포검사 
	int		m_iStatus_Unit_Epoxy;
	bool	m_bResign_Result[4];
	float	m_f_line_rate[4];
	int		m_line_cnt[4];
	int		m_line_pos[4];
	float	m_f_Hole_rate;

	double 			dTemperature;								// 이미지 센서의 온도	 - 작업시작 시 eeprom에서 읽어옴
	int				iRevision;									// 이미지 센서의 리비젼 번호  -  작업시작 시 eeprom에서 읽어옴

	bool	bManual_FindEpoxy;

	bool	bInsCenter;

	CPoint	cpMEpoxyPos;

	CString	sSaveImageName;

	double	m_Distortion;								// Distortion 계산
	CPoint	m_FoV;										// 화각 계산용 마크위치

	bool ocCheckIng;
	CTask();

	void Init();
	void initSFRElem();
	void	func_TactTimeInit();

	void	getROI();
	bool	getPatchCenterAndSFR(int iInspPos);
	bool	getROI_SFR(int mode);

    bool	_findCirclePos(unsigned char* ucImage, int pitch, int sizeX, int sizeY, CRect* rcRoi);
	bool	_OpencvFindCirclePos(BYTE* ChartRawImage, CRect* clRectRoi, bool bAutoMode);		//int nPitch, int nSizeX, int nSizeY,
	bool	_Trinity_findCirclePos(unsigned char* ucImage, int pitch, int sizeX, int sizeY, CRect* rcRoi);		//강상준 선임 240611 원형마크 없어서
																												//차트로 원형마트 대신


    bool	_findFovPos(unsigned char* ucImage, int pitch, int sizeX, int sizeY, CRect* rcRoi);
    bool	_findSnrPos(unsigned char* ucImage, int pitch, int sizeX, int sizeY, CRect* rcRoi);


	bool	_findCirclePosBin(unsigned char* ucImage, int pitch, int sizeX, int sizeY, CRect* rcRoi);			// 이진화 원찾기 알고리즘
	bool	_findRectPos(unsigned char* ucImage, int pitch, int sizeX, int sizeY, int index, CRect& rcRoi);		// 기존 사각형 위치 인식..
	bool	_findSfrRectPos(unsigned char* ucImage, int pitch, int sizeX, int sizeY, int index, CRect rcRoi, int iCircleCenter_X,int iCircleCenter_Y);

	bool	_findRectPos3(unsigned char* ucImage, int pitch, int sizeX, int sizeY, int index, CRect& rcRoi);	// 정재호 추가 함수.. (사각형 인식)
	bool	_searchEdgePos(unsigned char* ucImage, int pitch, int sizeX, int sizeY, int dir, CRect rcRoi, int &linePos, int &edgeVal);			// 정재호 추가 함수.. (사각형의 라인 인식)

	bool	_findRectPosPattern(unsigned char* ucImage, int pitch, int sizeX, int sizeY, int index, CRect& rcRoi);		// 기존 사각형 위치 인식..
	bool	g_FindRectPos(unsigned char* pImage, int nPitch, int nSizeX, int nSizeY, int nIndex, CRect& clRect);
	bool	g_FindSfrRectPos(unsigned char* pImage, int nPitch, int nSizeX, int nSizeY, int nIndex, CRect clRectRoi, int mode);
	CPoint CTask::getCircle(unsigned char* ucImage, int iX, int iY, int iWidth, int iHeight,  int sizeX, int sizeY, int pitch);

	void	getImageAlignment();
	double	getImageDisplayFOV();
	double	getImageTiltX();
	double	getImageTiltY();
	double	getImageRotation();

};

class COS_Check
{
public:
	int		m_iFlag_UsePin[OS_PIN_COUNT];
	float	m_fUpperLimit[OS_PIN_COUNT];
	float	m_fLowerLimit[OS_PIN_COUNT];

	COS_Check();
	 
	void	init();

	bool	checkOS();
};


class CSfrElem
{
public:
	RECT	m_CircleRoi[4];
	CPoint	m_CircleP[4];

	//
	//FOV
    CRect    m_clRectFov[MAX_FOV_COUNT];
    CPoint m_clPtFov[MAX_FOV_COUNT];

	//SNR
	CRect m_clRectSnr[MAX_SNR_COUNT];
    CPoint m_clPtSnr[MAX_SNR_COUNT];
	//


	int		m_iOffsetX[COMMON_LAST_MARK_CNT];
	int		m_iOffsetY[COMMON_LAST_MARK_CNT];
	int		m_iSizeX[COMMON_LAST_MARK_CNT];
	int		m_iSizeY[COMMON_LAST_MARK_CNT];

	int m_SfrTestUse[COMMON_LAST_MARK_CNT][4];	//0 = T , B, L , R

	//calculation
	int m_AATiltRoiIndex[5];	//[Center,TL, TR, BL, BR]		패턴 순서
	int m_AATiltCalRoi[COMMON_LAST_MARK_CNT][4];	//[Center,TL, TR, BL, BR][T,B,L,R]
	CSfrElem()
	{
		int i = 0;
		for (i = 0; i < COMMON_LAST_MARK_CNT; i++)
		{
			m_iSizeX[i] = 50;
			m_iSizeY[i] = 70;

			m_SfrTestUse[i][0] = 1;
			m_SfrTestUse[i][1] = 1;
			m_SfrTestUse[i][2] = 1;
			m_SfrTestUse[i][3] = 1;

			m_AATiltCalRoi[i][0] = 1;
			m_AATiltCalRoi[i][1] = 1;
			m_AATiltCalRoi[i][2] = 1;
			m_AATiltCalRoi[i][3] = 1;
		}
		for (i = 0; i < 5; i++)
		{
			m_AATiltRoiIndex[i] = i;	//0, 1, 2, 3, 4
			
		}

		int width = 1280;//4208;
		int Height = 1080;//3120;
		
		m_iOffsetX[0] = (int)(width / 2.17);
		m_iOffsetY[0] = (int)(Height/ 2.41);

		m_iOffsetX[1] = (int)(width / 3.05);
		m_iOffsetY[1] = (int)(Height/ 3.22);

		m_iOffsetX[2] = (int)(width / 2.18);
		m_iOffsetY[2] = (int)(Height/ 4.78);

		m_iOffsetX[3] = (int)(width / 1.69);
		m_iOffsetY[3] = (int)(Height/ 3.22);

		m_iOffsetX[4] = (int)(width / 1.69);
		m_iOffsetY[4] = (int)(Height/ 1.93);

		m_iOffsetX[5] = (int)(width / 2.18);
		m_iOffsetY[5] = (int)(Height/ 1.61);

		m_iOffsetX[6] = (int)(width / 3.06);
		m_iOffsetY[6] = (int)(Height/ 1.94);


		m_iOffsetX[7] = (int)(width / 5.54);
		m_iOffsetY[7] = (int)(Height/ 6.19);

		m_iOffsetX[8] = (int)(width / 2.17);
		m_iOffsetY[8] = (int)(Height/ 72.6);

		
		m_CircleRoi[0].left		= (int)(width*0.25);
		m_CircleRoi[0].top		= (int)(Height*0.03);
		m_CircleRoi[0].right	= (int)(width*0.41);
		m_CircleRoi[0].bottom	= (int)(Height*0.28);

		m_CircleRoi[1].left		= (int)(width*0.59);
		m_CircleRoi[1].top		= (int)(Height*0.03);
		m_CircleRoi[1].right	= (int)(width*0.73);
		m_CircleRoi[1].bottom	= (int)(Height*0.28);

		m_CircleRoi[2].left		= (int)(width*0.25);
		m_CircleRoi[2].top		= (int)(Height*0.72);
		m_CircleRoi[2].right	= (int)(width*0.41);
		m_CircleRoi[2].bottom	= (int)(Height*0.97);

		m_CircleRoi[3].left		= (int)(width*0.59);
		m_CircleRoi[3].top		= (int)(Height*0.72);
		m_CircleRoi[3].right	= (int)(width*0.73);
		m_CircleRoi[3].bottom	= (int)(Height*0.97);
		
		for (int i=0 ; i<4 ; i++)
		{
			m_CircleP[i].x = m_CircleP[i].y = 0;
		}
	}
};


class CDefect		//JJH.. 변수명, Load, Save 수정..
{
public:
	int		m_iNgAlarm;
	int		m_iNgUnloading;

	int		m_MaxDefectsCount;

	int		m_i_Insp_Flag[5];			// 검사 사용 / 미사용.

	int		m_i_Cnt_Limit[5];			// NG 판정 Spec..
	int		m_i_Filter_Size_Small[5];	// Small Filter Size..
	int		m_i_Filter_Size_Large[5];	// Large Filter Size..
	int		m_i_Defect_Size_Min[5];		// 결함의 최소 크기..
	int		m_i_Defect_Size_Max[5];		// 결함의 최대 크기..
	int		m_i_Skip_Boundary[5];		// ??..
//	int		m_i_Skip_Edge[5];			// ??..

	float	m_f_Threshold[5];			// ThresHold 값..
	float	m_f_Gray_diff[5];			// 밝기 변화 값..


	int		m_iSmallScale;
	int		m_iMiddleScale;
	int		m_iLargeScale;
	int     m_iEdgeScale;

	CDefect()
	{
		init();
	}

	void	init()
	{

		m_iNgAlarm = 1;
		m_iNgUnloading = 1;
		
		m_MaxDefectsCount	= 50;
		
		m_i_Insp_Flag[0] = m_i_Insp_Flag[1] = m_i_Insp_Flag[2] = m_i_Insp_Flag[3] = m_i_Insp_Flag[4] = 1;
		m_i_Cnt_Limit[0] = m_i_Cnt_Limit[1] = m_i_Cnt_Limit[2] = m_i_Cnt_Limit[3] = m_i_Cnt_Limit[4] = 1;

		m_i_Filter_Size_Small[0] = 1;
		m_i_Filter_Size_Small[1] = 1;
		m_i_Filter_Size_Small[2] = 3;
		m_i_Filter_Size_Small[3] = 1;
		m_i_Filter_Size_Small[4] = 3;

		m_i_Filter_Size_Large[0] = 19;
		m_i_Filter_Size_Large[1] = 21;
		m_i_Filter_Size_Large[2] = 13;
		m_i_Filter_Size_Large[3] = 3;
		m_i_Filter_Size_Large[4] = 11;

				
		m_f_Threshold[0]	= 1.0f;
		m_f_Threshold[1]	= 1.0f;
		m_f_Threshold[2]	= 0.8f;
		m_f_Threshold[3]	= 60.0f;
		m_f_Threshold[4]    = 20.0f;

		m_i_Defect_Size_Min[0]	= 2;
		m_i_Defect_Size_Min[1]	= 50;
		m_i_Defect_Size_Min[2]	= 500;
		m_i_Defect_Size_Min[3]	= 1;
		m_i_Defect_Size_Min[4]	= 100;

		m_i_Defect_Size_Max[0]	= 100;
		m_i_Defect_Size_Max[1]	= 10000;
		m_i_Defect_Size_Max[2]	= 100000;
		m_i_Defect_Size_Max[3]	= 100;
		m_i_Defect_Size_Max[4]	= 100000;


		m_iSmallScale		= 40;
		m_iMiddleScale		= 20;
		m_iLargeScale		= 3;
		m_iEdgeScale        = 10;

		m_f_Gray_diff[0]	= 2.0f;
		m_f_Gray_diff[1]	= 1.0f;
		m_f_Gray_diff[2]	= 0.8f;
		m_f_Gray_diff[3]	= 50.0f;
		m_f_Gray_diff[4]	= 2.0f;

		m_i_Skip_Boundary[0]	= 10;
		m_i_Skip_Boundary[1]	= 50;
		m_i_Skip_Boundary[2]	= 50;
		m_i_Skip_Boundary[3]	= 10;
		m_i_Skip_Boundary[4]	= 100;
	}
};

class CNgList_Data
{
public:
	int m_NgCount;
	int m_NgIndex;
	char sz_NgList[MAX_NG_LIST][256];
	CString tmpNgStr;

	void Save();
	void Load();

	CNgList_Data();
};

class CSystemData
{
public:
	TCHAR m_szBarcodeIp[SIZE_OF_100BYTE];					// 바코드 IP
	int m_nBarcodePort;										// 바코드 PORT

	int iCommPort[MAX_RS232_NO];
	int iBaudRate[MAX_RS232_NO];
	int nEpoxyIndex;
	int nUvIndex;
	int m_iSystemNo;
	int m_iUnitNo;
	//--

	int m_iVacReverse;
	int m_iStaintInspPass;
    int m_iDefectInspPass;
	int m_iLaserInspPass;
	int m_iAlignCamInspPass;
	int m_iSfrMaxValueInsp;
	int m_iEpoxyLaserInspPass;
	int m_i1stAaEbable;
	int m_iDispensePass;
	int m_iMTFUvInsp;
	int m_iUVPass;
	int m_iDispenseInspPass;
	int m_iLine;
	int m_iProductComp;			//완성품 검사 Check
	int m_iProductHolderBoning;	//FF HOLDER BONDING 모드
	int m_iFront;			//전면감지센서
	int m_iDicChange;
	int m_iIrChartUse;
	int m_iSminiOQMOde;			//Smini OQ모드
	
	int		m_FreeRun;
	int		m_iAlignMode;

	int		m_iSmoothness[2];
	int		m_SFR_Type[COMMON_LAST_MARK_CNT];// LAST_MARK_CNT];



	bool m_testRunMode;
	double	fMotorSpeed[MAX_MOTOR_NO];
	float	fMotorAccTime[MAX_MOTOR_NO];
	float	fMotorResol[MAX_MOTOR_NO];
	mCDPoint	dCamResol[3];
	mCDPoint dCamAngle[3];

	mCDPoint	m_dOcSpec;
	double	dSpec_OC_Theta;
	double	dMax_Sfr_Limit;

	double	dLimit_SFR_Balance;
	double	dLimit_SFR_04F_Balance;
	double	dLimit_SFR_07F_Balance;
	double	dLimit_SFR[15];

	double	m_dOffset_Conti_Down_Z;

	double	m_dOffset_Prev_UV_X;
	double	m_dOffset_Prev_UV_Y;
	double	m_dOffset_Prev_UV_Z;
	double	m_dOffset_Prev_UV_Tx;
	double	m_dOffset_Prev_UV_Ty;
	double	m_dOffset_Prev_UV_Th;

	double	m_dMove_MaxPos_Fine;

	double dDataset[MAX_MOTOR_NO];
	double Password; 
	
	int		m_iExposureTime;

	int		iDoorInterlock;
	
	int     m_Epoxy_Change_Count;	// 20141119 LHC - Epoxy 교체 시간 설정.
	int     m_Log_Retention_Period;		// 로그 보관기간 설정

	CString	m_Last_Log_Delete_Date;		// 최종 로그 삭제 일자

	CString	 m_Factory_Code;
	int		 m_Mes_Port_Number;
	CString	 m_Comp_Factory_Code;
	int		 m_Mes_Comp_Port_Number;
	CString	 m_Mes_Ip_Number;

	int     m_iAASel;
	int			m_Epoxy_Shot;
	int			m_Epoxy_Alarm;
	int			m_Epoxy_Start_Time;
	int			m_Epoxy_Last_Time;

	int			m_Socket_Count;
	int			m_Socket_Alarm;

	CSystemData();

	void Load();
	void Save();
};

class CWork
{
public:
	int m_iCnt_Output;
	int m_iCnt_NG_Output;
	int m_iCoverUpDownCnt;	// 동영상 실패 후 Cover Up/Down 횟수 표시

	//double Cleanpad[2];
	//int Cleancnt;

	//----- 만도 차량용 Camera 검사 Count
	int iInspCnt_Output;			//총 검사 완료 수량
	int iInspCnt_NG_Output;			//검사 NG 수량

	int iInspCnt_NG_MTF;			//MTF NG 수량
	int iInspCnt_NG_OC;				//OC NG 수량
	int iInspCnt_NG_Distortion;		//Distortion NG 수량
	int iInspCnt_NG_Current;		//전류측정 NG
	int iInspCnt_NG_TestPattern;	//Test Pattern NG
	int iInspCnt_NG_Defect;			//Defect NG 수량
	int iInspCnt_NG_Stain;			//Stain
	int iInspCnt_NG_Dark;			//Dark 검사 
	int iInspCnt_NG_Uniformity;		//Uniformity 검사

	int m_Epoxy_Time_Check_Year;
	int m_Epoxy_Time_Check_Hour;   // 20141125 LHC - 시간체크 시작시  현재시간 저장
	int m_Epoxy_Time_Check_Min;
	int m_Epoxy_Time_Check_Month;
	int m_Epoxy_Time_Check_Day;
	int m_Epoxy_Time_Flag;
	
	CWork();

	void Load();
	void Save();
	void SaveCntLog();
	void InspCountReset();
};


class CModelList
{
public:
	int TotalCount;// cnt;
	int CurrentModelIndex;
	char ModelName[MAX_MODEL_CNT][SIZE_OF_100BYTE];
	char curModelName[SIZE_OF_100BYTE];

	CModelList();

	void ModelSave();
	void ModelLoad();

	bool NewLoad();
	bool NewSave();
};



typedef struct _SENSOR_INFO
{
	char			m_szRes[256];		//  Resolution 
	int				m_iWidth;           //  Image size Width
	int				m_iHeight;          //  Image size Height
	unsigned int	m_iImageFormat;           //  Pixel Format
}SENSOR_INFO;




class CMotor
{
public:
	double		pos[MAX_POS_NO];		// Wait_Pos,	Loading_Pos,	Holder_Pos,	 Dispense_Pos,	Lens_Pos,	Align_Pos,	  Bonding_Pos,	  DataSet_Pos,	  MAX_POS_NO

	double		m_dLimit_OK;
	double		m_dLimit_Err;

	CMotor()
	{
		for (int i=0; i<MAX_POS_NO; i++)
			pos[i] = 0.00f;

		m_dLimit_OK = 0.01;
		m_dLimit_Err = 3.0;
	};
};

typedef struct _AA_INFO
{
	int				m_iDelayTime;				/* 단위 : msec */
	int				m_iStepCnt;					
	double			m_dMoveDistance;			/* 단위 : mm */
	double			m_dMoveVel;

	float			m_fLimit_MTF;				/* Rough 이동 Limit MTF 값 */
}_AA_INFO;


typedef struct _CAM_GRAB_INFO
{
	int				m_iDelayTime;				/* 단위 : msec */	//0=Laser 측정전 Delay, 1=Align 관련 , 2=CCD Cam
	int				m_iRetryCnt;    
}_CAM_GRAB_INFO;

//! LPMC-500 Frame Grabber에서의 영상 취득 관련 Model 정보
//! Added by LHW, 2013/3/5
typedef struct _CCM_GRAB_INFO
{
	//! Auto Run 상태에서 연속 영상 취득이 아니라, 
	//! 필요할 때에만 일정 회수 만큼 영상을 취득하여 Averaging 처리를 할 때, 
	//! 영상 취득하는 회수, '0'이면 연속 영상 취득
	int m_iCnt_Average_Thru_Focus;
	int m_iCnt_Average_Tilting;
	int m_iCnt_Average_Fine_Focus;
	int m_iCnt_Average_Defect;
	int m_iCnt_Average_Opt_Centering;
}_CCM_GRAB_INFO;

class CModelData
{
public:
	CString mCurModelName;
	//TCHAR mCurModelName[SIZE_OF_100BYTE];
	//char mCurModelName[SIZE_OF_100BYTE];
	int mGlobalChartCount;
	int mGlobalChartType; //0 = x자형 타입 , 1 = +타입 차트
	int mGlobalChartFind; //0 == 패턴 , 1 = 자동
	int mGlobalSmallChartCount;
	int code1, code2;
	int m_dDemosaic;
	double dFov;


	CMotor		axis[MAX_MOTOR_NO];
	COffset		offset;	//도포 Offset

	/* LED Value */
	int			m_iLedValue[MAX_LIGHT_DATA];		//CHART_LIGHT=0, OC_LIGHT=1, UP_LIGHT=3, DOWN_LIGHT = 2, UP_LENS_LIGHT=4, INSP_RESIN=5 RESIN_CALC=6
	int			m_iBright[3];		//PCB_Chip_MARK=0, PCB_Holder_MARK=1, LENS_Align_MARK=2
	int			m_iContrast[3];		//PCB_Chip_MARK=0, PCB_Holder_MARK=1, LENS_Align_MARK=2

	//-------------------------------------------------------------------------
    // xpeng 화상 검사 로그 data
	int  m_LogDefectBrightVery;
	int  m_LogDefectDarkVery;
	int  m_LogDefectHotVery;

    int  m_LogDefectBright;
	int  m_LogDefectDark;
	int  m_LogDefectHot;

	int  m_LogDefectBrightCluster;
	int  m_LogDefectDarkCluster;
	int  m_LogDefectHotCluster;

	int  m_LogDefectDarkHorLine;
	int  m_LogDefectDarkVerLine;
	int  m_LogDefectBrightHorLine;
	int  m_LogDefectBrightVerLine;
	double  m_LogDefectColumnFPN[4];//Red Cr Cb Blue 1 0 3 2			//나중에 나머지 3개도 추가
    //
    double		m_dMTF[24];		//MTF 검사 항목
                                //
    double		m_LogOC_X;          //890
    double		m_LogOC_Y;          //930
    double		m_LogOC_DelatX;     //-20
    double		m_LogOC_DelatY;     //20
                                    //
    double      m_LogDistortion;
    //
	double   m_LogSfr[COMMON_MTF_INSP_CNT];//MTF_INSP_CNT];
	double dGen2Current;
	double   m_LogSaturation[COMMON_MTF_INSP_CNT];//MTF_INSP_CNT];
	double   m_LogSnr;
    //
    double  m_LogBlemishBlackSpot;
    double  m_LogBlemishLcb;
    double  m_LogBlemishRU_Ymean;
    //
    double m_Log_CS_RC_6500K;
    double m_Log_CS_BC_6500K;
    double m_Log_CS_CrCb_6500K;
    double m_Log_CS_RC_2800K;
    double m_Log_CS_BC_2800K;
    double m_Log_CS_CrCb_2800K;

    //
    //
    double m_Log_RI_RED[100];
    double m_Log_RI_CLEARR[100];
    double m_Log_RI_CLEARB[100];
    double m_Log_RI_BLUE[100];
	//
	double m_Log_RI_CornerVar_R;
	double m_Log_RI_CornerVar_Cr;
	double m_Log_RI_CornerVar_Cb;
	double m_Log_RI_CornerVar_B;
    //
    double m_Log_RI_Center_R;
    double m_Log_RI_Center_Cr;
    double m_Log_RI_Center_Cb;
    double m_Log_RI_Center_B;
    //
    double m_Log_RI_LT_Ratio_R;
    double m_Log_RI_LT_Ratio_Cr;
    double m_Log_RI_LT_Ratio_Cb;
    double m_Log_RI_LT_Ratio_B;
    //
    double m_Log_RI_RT_Ratio_R;
    double m_Log_RI_RT_Ratio_Cr;
    double m_Log_RI_RT_Ratio_Cb;
    double m_Log_RI_RT_Ratio_B;
    //
    double m_Log_RI_LB_Ratio_R;
    double m_Log_RI_LB_Ratio_Cr;
    double m_Log_RI_LB_Ratio_Cb;
    double m_Log_RI_LB_Ratio_B;
    //
    double m_Log_RI_RB_Ratio_R;
    double m_Log_RI_RB_Ratio_Cr;
    double m_Log_RI_RB_Ratio_Cb;
    double m_Log_RI_RB_Ratio_B;

    //
    double m_Log_SNR_SNR;
    double m_Log_SNR_DR;
    //
    double  m_Log_CU_LT_Delta_RG;
    double  m_Log_CU_LT_Delta_RB;
    double  m_Log_CU_LT_Delta_BG;

    double  m_Log_CU_RT_Delta_RG;
    double  m_Log_CU_RT_Delta_RB;
    double  m_Log_CU_RT_Delta_BG;

    double  m_Log_CU_LB_Delta_RG;
    double  m_Log_CU_LB_Delta_RB;
    double  m_Log_CU_LB_Delta_BG;

    double  m_Log_CU_RB_Delta_RG;
    double  m_Log_CU_RB_Delta_RB;
    double  m_Log_CU_RB_Delta_BG;
    //
    double  m_Log_FOV_H_FOV;
    double  m_Log_FOV_V_FOV;
    double  m_Log_FOV_D_FOV;
    double  m_Log_Rotate;

    //
	//-------------------------------------------------------------------------
	//
	//★ACMIS 검사 Spec Data
	//-------------------------------------------------------------------------
	//Defect
	double m_DefectSpec[26];//TAllDefectPixel_ONSEMI_RCCB m_DefectSpec;
	int n_DefectCountLimit;
	int n_ClusterCountLimit;
	//Stain

	//fov , distortion 
	double m_FovSpec[9];//

						//oc , rotate
	double m_OcSpec[2];//

					   //Color Sensitivity
	double m_ColorSensitivitySpec[8];//

									 //SNR
	double m_SnrSpec[3];//

						//Uniform 
	double m_UniformSpec[7];//

							//Relative Illumination  
	double m_RIlluminationSpec[5];//

	//Blemish Stain  
	double m_LcbSpec[LcbMaxCount];
	double m_YmeanSpec[YmeanMaxCount];
	double m_FDFSpec[FdfMaxCount];

	//Chart  
	double m_ChartSpec[5];

	//RI  
	//double m_RISpec[11][9];

	//SATURATION
	double m_SaturationMin[36];
	double m_SaturationMax[36];
	double m_SaturationThreshold[36];
    //RI  
    double m_RISpec[8];
    double m_RirOI[100][10];
	//-------------------------------------------------------------------------
	//
	double m_dChartHfovMin;
	double m_dChartHfovMax;

	double m_dChartVfovMin;
	double m_dChartVfovMax;

	double m_dChartDistortionMin;
	double m_dChartDistortionMax;
	//
	//-------------------------------------------------------------------------
	double m_dStaturationMin;
	double m_dStaturationMax;


	double m_dStainLsbCenter;
	double m_dStainLsbCorner;
	double m_dStainLsbEdge;
	double m_dStainYMeanCenter;
	double m_dStainYMeanCorner;
	double m_dStainYMeanEdge;
	//-------------------------------------------------------------------------
	//
	//
	//-------------------------------------------------------------------------
	double		m_InspPcbTilt[2];
	int			d_SIDE_MODEL_CH;	//0 = FRONT , 1 = BACK

	double		m_InPos_X[3];
	double		m_InPos_Y[3];
	double		m_OutPos_X[3];
	double		m_OutPos_Y[3];
	//
	double		m_PcbLaserPos_X[3];
	double		m_PcbLaserPos_Y[3];
	int			holderx;
	int			holdery;
	/* Mark Data */
	CPoint		m_MarkSize[3][2];
	mCDPoint		m_MarkCenter[3][2];
	mCDPoint		m_MarkOrigin[3][2];
	int			m_iLimitRate[3][2];	
	int			m_MarkMatchingRate[4];//0 = Sensor /1 = Holder /2 = Lens /3 = 완제품
	CRect  m_FieldBox[COMMON_LAST_MARK_CNT];// LAST_MARK_CNT];


	COS_Check	osChk;
	CSfrElem	sfrElem;
	CDefect		defect;

	int			UV_Time;		//! UV Lamp의 지속 시간 (단위 msec)
	int			UV_Power;
	double      UV_Weight;

	int			AARepeatCount;
	double		Tilt_Weight_Pre;
	double		Tilt_Weight_Post;

	int		Tilt_Diretion[5];//0 = x , 1 = y , 2 = tx , 3 = ty , 4 = th
	/* SFR ROI 영역 크기 */
	int		m_iSize_ROI_X;
	int		m_iSize_ROI_Y;

	int     m_width;
	int		m_height;
	double     m_oc_x;
	double		m_oc_y;

	_AA_INFO	strInfo_AF1;			/* AutoFocus Rough */
	_AA_INFO	strInfo_AF2;			/* AutoFocus Fine */
	_AA_INFO	strInfo_Tilt;			/* Tilt */

	_CAM_GRAB_INFO	strInfo_Cam[4];

	_CCM_GRAB_INFO  strInfo_CCM;	//! LPMC-500 Frame Grabber의 영상 취득 관련 정보, Added by LHW, 2013/3/5

	int m_iSensorID;
	int	m_iSensorType;

	double	m_dSize_CCD_Cell;		//! CCD Sensor의 물리적인 크기, 단위 um


	//! White Balance 관련
	int     m_iSkip_X_gain, m_iSkip_Y_gain;
	double  m_dBorder_X_gain, m_dBorder_Y_gain;	//! 테두리 영상 제외할 크기, 단위 %
	
	//! LPMC-500 Frame Grabber에서 영상을 취득하는 방법
	E_GRAB_METHOD m_eGrabMethod;	//! Added by LHW (2013/3/13)

	int		m_iCnt_Check_SFR;
	double	m_dMove_Offset_Z;

	//! Dispenser 원호 보간 관련 Data
	
	double dSpeed;			//속도
	double dSmallSpeed;			//conti 작은원 속도
	double dSmallOffTime;			//sMini Holder Point 도포 Delay 시간
	double dAcc;			//가감속 속도
	double dOnTime;			//토출 On후 일정 Delay 시간
	double dOffTime;		//이동중 일정 시간 전에 토출 OFF

	//conti 원형도포
	double dConti_RadiusLength;		//작은원반지름
	double dConti_Angle;			//작은원각도	
	double dConti_Speed;
	double dTwister_Speed;
	//원형도포
	double dRadiusLength;	//반지름
	double dAngle;				//각도	
	double dCircleSpeed;		//속도
	double dCircleAcc;			//가감속 속도
	double dCircleOnTime;	//토출 On후 일정 Delay 시간
	double dCircleOffTime;			//원 이동중 일정 시간 전에 토출 OFF

	//도포검사 영역 Offset
	double dEpoxyOffset_X;	
	double dEpoxyOffset_Y;	
	//&, &, &, &);
	//! Dispenser 직선 Data
	double dDisLength[8];		//각각의 단변 길이
	double dCircleRadiusCenterOffsetX[4];		//다각형 반원 중심점 offset x
	double dCircleRadiusCenterOffsetY[4];		//다각형 반원 중심점 offset y
	double dCircleRadiusEndOffsetX[4];		//다각형 반원 끝점 offset x
	double dCircleRadiusEndOffsetY[4];		//다각형 반원 끝점 offset y

	CPoint		m_EpoxyBaseP;
	double		m_dEpoxyOffsetX;
	double		m_dEpoxyOffsetY;

	double      m_ContiDownOffset;

	CPoint		m_Epoxy2BaseP;
	double		m_dEpoxy2OffsetX;
	double		m_dEpoxy2OffsetY;
	
	float		m_ResingStartAngle[4];				// 도포검사(원형) 시작 각도
	float		m_ResingFinishAngle[4];				// 도포검사(원형) 종료 각도
	int			m_ResingInspLevel;					// 도포검사 판단 칼라 레벨

	mCDPoint		m_ResinDrawSize;
	mCDPoint		m_CircleDrawSize[4];
	mCDPoint		m_CircleDrawCenter[4];				// 원호 중심점
	mCDPoint		m_dResinInspOffset[2];				// 0:안쪽 Offset, 1:바깥 Offset
	int			m_iResinInspLimit;					// 도포 검사 OK / NG 판정 Limit
	double		m_dResinInspHoleSpec;				//KKYH 20150622 HOLE 검사 Spec 추가(%)
	double		m_dResinInspGapLength;				//KKYH 20150622 HOLE 연속 끊어진 구간 Spec(mm)

	CPoint		m_ResingRectStart[4];				//KKYH 20150622 날개부분 검사 영역 시작지점.(mm)
	CPoint		m_ResingRectSize[4];				//KKYH 20150622 날개부분 검사 영역 크기(mm)

	double		m_iResinInspRectSpec;				//KKYH 20150622 날개부분 검사 Spec 추가(%)

	double		dEpoxySize;							// 직선 도포 길이
	double		dEpoxySpeed;						// 직선 도포 속도
	int			iEpoxyDelay;						// 직선 도포 지연시간

	int			ImageCenter;						// ROI 구할때 사용할 화면 중심의 기준

	double		INSP_MTF_0_0F;
	double		INSP_MTF_0_4F;
	double		INSP_MTF_0_5F;
	double		INSP_MTF_0_6F;
	double		INSP_MTF_0_7F;
	double		INSP_MTF_0_8F;
	double		INSP_MTF_Blance_0_4F;
	double		INSP_MTF_Blance_0_5F;
	double		INSP_MTF_Blance_0_6F;
	double		INSP_MTF_Blance_0_7F;
	double		INSP_MTF_Blance_0_8F;
	double		INSP_Blemish;
	double		INSP_Noise;
	int				INSP_Stain;
	double		INSP_BlackSpot;
	double		INSP_DefectPixel_DefectPixelTotal_Hot;
	double		INSP_DefectPixel_DefectPixelTotal_Bright;
	double		INSP_DefectPixel_DefectPixelTotal_Dark;
	double		INSP_DefectPixel_DefectPixelTotal;
	double		INSP_DefectPixel_Dark_Couplet;
	double		INSP_DefectPixel_Dark_Cluster;
	double		INSP_DefectPixel_Light_Couplet;
	double		INSP_DefectPixel_Light_Cluster;
	double		INSP_DefectPixel_Row_Dark;
	double		INSP_DefectPixel_Row_Midlevel;
	double		INSP_DefectPixel_Column_Dark;
	double		INSP_DefectPixel_Column_Midlevel;
	double		INSP_DefectPixel_ColumnFPN;
	double		INSP_DistortionCentering;
	double		INSP_DefectPixel_DefectPixelTotal_Hot_Ratio;		// Single defect 판정을 위한 픽셀과 평균 블록 간의 차이 값 Threshold
	double		INSP_DefectPixel_DefectPixelTotal_Dark_Ratio;		// Single defect 판정을 위한 픽셀과 평균 블록 간의 차이 값 Threshold
	double		INSP_DefectPixel_DefectPixelTotal_Bright_Ratio;		// Single defect 판정을 위한 픽셀과 평균 블록 간의 차이 값 Threshold
	double		INSP_DarkRowSpec;
	double		INSP_DarkColumnSpec;
	double		INSP_MidlevelRowSpec;
	double		INSP_MidlevelColumnSpec;

	double Cleanpad[2];
	int Cleancnt;


	int			STAIN_SPEC_EdgeSize;
	float		STAIN_SPEC_CenterThreshold;
	float		STAIN_SPEC_EdgeThreshold;
	int			STAIN_SPEC_DefectBlockSize;
	int			STAIN_SPEC_LscBlockSize;
	
	CPoint		m_FieldPattern_Pos[COMMON_LAST_MARK_CNT];				// 필드 패턴의 시작위치
	CPoint		m_FieldPattern_Size[COMMON_LAST_MARK_CNT];				// 필드 패턴의 크기
	mCDPoint		m_FieldPatternCenter[COMMON_LAST_MARK_CNT];
	mCDPoint		m_FieldPatternOrigin[COMMON_LAST_MARK_CNT];

	CPoint		m_MTF_ROI_Pos[COMMON_MTF_INSP_CNT];					// SFR 측정 위치
	CPoint		m_MTF_Pos[COMMON_MTF_INSP_CNT];						// MTF DLL 호출 위치
	int			m_MTF_Direction[COMMON_MTF_INSP_CNT];					// SFR ROI 방향


	CPoint		m_DistortionMark_ROI[6];							// Distortion 계산용 마크위치
	CPoint		m_FieldOfView_ROI[2];								// 화각 계산용 마크위치

	float		m_Line_Pulse;										// Line Pulse 값m
	float		m_Gen2_Line_Pulse;				//Gen2 모델만사용


	int			m_Tilt_Ty_Only_LR_RL;							// 0.7F Ty 틸트 계산에 LR,RL ROI만 사용할 지 여부 (1:사용, 0:미사용)
	int			m_IsUseLaserTilt;								// Laser Tilt 사용 유무
	int			m_IsUseDefectPixel_Dark;
	int			m_IsUseDefectPixel_Brite;

	int			m_ccdArray;
	int			m_IsUseDarkDefectTest;							// Defect Picxel 암막 검사 유무
	int			m_IsUseBrightDefectTest;						// Defect Picxel 광원 검사 유무
	int			m_IsUseStainTest;								// 이물 검사 유무

	int			m_IsDoorOpenRunning;							// 전면Door 열린체 진행
	int			m_AUTO_Z_SEARCH;								// Auto Z 사용 여부
	int			m_AUTO_Z_SEARCH_CNT;							// Auto Z Fiducial Mark 확인 횟수
	float		m_AUTO_Z_SEARCH_VAL;							// Auto Z 상수값
	CPoint		m_Fiducial_Mark[4];								// Auto Z Search 계산용 기준 점

	int			m_Uart_Range1;		//스타트값
	int			m_Uart_Range2;		//종료값
	CModelData();

	void AcmisDataLoad();
	void AcmisDataSave();

	void Save();
	void Load();
	void ChartSave();
	void ChartLoad();

    void RoiSave();
    void RoiLoad();
	void PatternSave();
	void PatternLoad();

	void saveMark(int iCamNo, int iMarkType, int iMarkNo);
	void loadMark(int iCamNo, int iMarkType, int iMarkNo);
};

class CMandoInspLog
{
public:
	SYSTEMTIME Insptime;	//검사 시작 시간 저장
	
	CString sBarcodeID;		//바코드명
	double dTilteOffset[2];	//PCB<->Lens 변위 측정 편차[TX, TY]
	double dPCBOffset[3];	//PCB<->Lens Offset 편차[X/Y/T]
	double dLensOffset[3];	//Lens Offset 편차[X/Y/T]
	bool	bInspRes;		//결과
	CString sNGList;

	double dCurrent;		//전류 측정값
	double dVoltage;		//voltage
	CString s12C;			//TestPattern 검사 틀린 갯수

	double dMTF_PreUV[COMMON_MTF_INSP_CNT];//MTF_INSP_CNT];		//UV전 MTF 검사 항목
	double dMTF_PostUV[COMMON_MTF_INSP_CNT];//MTF_INSP_CNT];		//UV후 MTF 검사 항목
	double dLaserTestPoint[4];
	double dLaserTestComPoint[4];
	double dLaserTestTilt[2];
	double dOpticalOc[2];

	double dMtfDiff4F;
	double dMtfDiff7F;
	double dRiDiff;
	double dRicorner[4];

	double dColorReproduction[4];

	double dMTF_TotalAverage;
	double dMTF_LinePulse2_PostUV[COMMON_MTF_INSP_CNT];//MTF_INSP_CNT];		//UV후 MTF 검사 항목
	double dOCResult[2];		//OC 결과.[X/Y]	
	double dDistortion;										// Distortion 측정
	double dFoV;											// FoV 측정
	double dColorBalance;

	double dDefect[2];			//Defect검사[White/Black]
	double dStain[3];
	double dShading65FC[2];
	double dShading85FC[2];
		
	

	bool   m_bInspRes;			//결과

	double d60lpmm[24];			//60lp/mm (17Point)
	double d67lpmm[24];			//67lp/mm (17Point)

	double d04FBalance; 
	double d05FBalance; 
	double d06FBalance; 
	double d07FBalance; 
	double d08FBalance; 

	double	dMTF_PreUV_0_0F;
	double	dMTF_PreUV_0_6F_TL;
	double	dMTF_PreUV_0_6F_TR;
	double	dMTF_PreUV_0_6F_BL;
	double	dMTF_PreUV_0_6F_BR;

	double	dMTF_PreUV_0_4F;
	double	dMTF_PreUV_0_5F;
	double	dMTF_PreUV_0_6F;
	double	dMTF_PreUV_0_7F;
	double	dMTF_PreUV_0_8F;
	double	dMTF_Blance_PreUV_0_4F;
	double	dMTF_Blance_PreUV_0_5F;
	double	dMTF_Blance_PreUV_0_6F;
	double	dMTF_Blance_PreUV_0_7F;
	double	dMTF_Blance_PreUV_0_8F;


	double	dMTF_PostUV_0_0F;
	double	dMTF_PostUV_0_4F;
	double	dMTF_PostUV_0_5F;
	double	dMTF_PostUV_0_6F;
	double	dMTF_PostUV_0_7F;
	double	dMTF_PostUV_0_8F;
	double	dMTF_Blance_PostUV_0_4F;
	double	dMTF_Blance_PostUV_0_5F;
	double	dMTF_Blance_PostUV_0_6F;
	double	dMTF_Blance_PostUV_0_7F;
	double	dMTF_Blance_PostUV_0_8F;

	double	dBlackSpot;
	double	dBlemish;
	double	dNoise;
	double	dDefectPixel_DefectPixelTotal;
	double	dDefectPixel_DefectPixelTotal_Hot;
	double	dDefectPixel_DefectPixelTotal_Bright;
	double	dDefectPixel_DefectPixelTotal_Dark;
	double	dDefectPixel_Dark_Couplet;
	double	dDefectPixel_Light_Couplet;
	double	dDefectPixel_Dark_Cluster;
	double	dDefectPixel_Light_Cluster;
	double	dDefectPixel_Row_Dark;
	double	dDefectPixel_Row_Midlevel;
	double	dDefectPixel_Column_Dark;
	double	dDefectPixel_Column_Midlevel;
	double	dDefectPixel_ColumnFPN;
	double	dDistortionCentering;
	double	dDefectPixel_DefectPixelTotal_Dark_Ratio;		// Single defect 판정을 위한 픽셀과 평균 블록 간의 차이 값 Threshold
	double	dDefectPixel_DefectPixelTotal_Bright_Ratio;		// Single defect 판정을 위한 픽셀과 평균 블록 간의 차이 값 Threshold

	double	dTemperature;									// 센서의 온도값
	//! Main화면 NG List Overlay 관련 변수
	int iNGCnt;
	CString sDispNG[200];
	double getMaxMin(int pos , int type);
	CMandoInspLog();

	void func_InitData();
	void func_LogSave_Shm_vertex();	// 김성봉책임 차크 꼭짓점 좌표 출력
	void func_LogSave_UVBefore();	// UV전 Log Data 저장
	void func_LogSave_UVAfter(int index = 0);	// UV후 Log Data 저장
	void func_LogSave_AAAfter();	//AA후(UV전) Log Data
	void func_LogSave_UVAfter_Min();

	void func_DrawNG_Overlay(int iCh);	//NG항목 Overlay Draw

	void func_LogSave_Stain(CString name , CString title , CString data);
};

enum AA_SFR_SPEC	{AA_CL_00F_V=0,  AA_CR_OOF_V, AA_CT_00F_H, AA_CB_00F_H, AA_LT_04F_V, 
					AA_LT_04F_H, AA_RT_04F_V, AA_RT_04F_H, AA_RB_04F_V, AA_RB_04F_H,
					AA_LB_04F_V, AA_LB_04F_H, AA_L_04F_V, AA_L_04F_H, AA_R_04F_V,
					AA_R_04F_H, AA_LT_07F_V, AA_LT_07F_H, AA_RT_07F_V, AA_RT_07F_H,
					AA_RB_07F_V, AA_RB_07F_H, AA_LB_07F_V, AA_LB_07F_H, AA_MAX_SFR_INSP_CNT };

enum AA_INSP_SPEC	{CL_00F_V=0,  CR_OOF_V, CT_00F_H, CB_00F_H, 
                    LT_04F_V, LT_04F_H, RT_04F_V, RT_04F_H, 
                    RB_04F_V, RB_04F_H, LB_04F_V, LB_04F_H, 
                    LT_07F_V, LT_07F_H, RT_07F_V, RT_07F_H,
					RB_07F_V, RB_07F_H, LB_07F_V, LB_07F_H, MAX_SFR_INSP_CNT };

class CMandoSfrSpec
{ 
public:
	//신규 개조 -> 60LP, C/P은 제거, Only 67LP만.
	//기존 60LP, C/P 추가한 부분이 많고, C/P은 재사용할수 도 있으니
	//배열 3개는 그래도 가고, [0]배열, [2]배열은 사용 하지 않는다.
	// AA장비 변수
	double dAASFR_Spec[COMMON_MTF_INSP_CNT][4];//MTF_INSP_CNT][4];		// [0] : UV전,[1] : UV후, [2] : 완제품, 

	// 화상검사기 변수
	double dINSPSFR_Spec[COMMON_MTF_INSP_CNT][3];//MTF_INSP_CNT][3];

	double		INSP_AAmode_OC_Min_Spec;
	double		INSP_AAmode_OC_Max_Spec;
	double		INSP_Procmode_OC_Min_Spec;
	double		INSP_Procmode_OC_Max_Spec;

	int INSP_SfrDeltaAlgorithmType;
	double INSP_SfrGamma;
	double INSP_SfrMaxEdgeAngle;
	int INSP_SfrAlgorithmType;
	int INSP_SfrAlgorithmMethod;
	int INSP_SfrFrequencyUnit;
	double INSP_SfrInspOffset[4];   //0 = left 1 = top 2 = right 3 = bottom
	
	double INSP_OCCenterSpecX;
	double INSP_OCCenterSpecY;
	double INSP_OCThresholdRatio;
	int INSP_OCRoiCount;
	int INSP_OCEdgeTopMargin;
	int INSP_OCBlockSize;
	double INSP_OCInspOffset[4];   //0 = left 1 = top 2 = right 3 = bottom


	double		Rotation_Spec;

	double INSP_Diff_Spec[2];

	double INSP_RIDiff_Spec;

	double INSP_Current_Spec;
	double INSP_Voltage_Spec;
	bool Insp60Lp;
	bool Insp67Lp;
	bool InspCp;

	CMandoSfrSpec();
	void NewSfrSave();
	void NewSfrLoad();
	void save();
	void load();
};

class CMESCommunication
{
public:

	CString sMES_LotId;			// 바코드명
	int		iMES_Cnt;			// 차수
	int		iMES_FinalResult;	// 합부

	double	dMES_Current;		// 전류측정
	CString sMES_I2C;			// I2C


	CString partNumber;
	CString fwVersion;
	CString sensorId;
	CString OTPWriteFail;
	CString OTPVerifyFail;
								//----------------------------------------------------------------------------------------------------------------------
								//----------------------------------------------------------------------------------------------------------------------
								//new Mes 190921
	double	m_dMesMTF[COMMON_MTF_INSP_CNT];//MTF_INSP_CNT];				//MTF 검사 항목
	double  m_dMesMTFUVAfter[COMMON_MTF_INSP_CNT];//MTF_INSP_CNT];

	int		m_nMesMTFResult[COMMON_MTF_INSP_CNT];//MTF_INSP_CNT];
	int		m_nMesMTFResultUVAfter[COMMON_MTF_INSP_CNT];//MTF_INSP_CNT];

	double		m_nMesDefect[14];

	double  m_dMesOC[2];
	double  m_dMesDeltaOC[2];

	double	m_nMesBlemish[3];			//0 = LCB , 1 = RU_Ymean , 2 = FDF
	double  m_nMesColorSensitivity[6];
	double	m_nMesRI[20];
	double  m_nMesRICorner[4];
	double	m_nMesColorUniformity[12];
	double	m_dMesDistortion;
	double	m_dMesSnr;
	double	m_dMesDr;
	double	m_dMesFov[3];	//0 = HFov , 1 = VFov , 2 = DFov
	double	m_dMesRotate;


	double	m_nMesBlemishMaxDefect[9];
	//---------------------------------------------------------------
	//---------------------------------------------------------------
	//result
	int		m_nMesDistortionResult;
	int		m_nMesDefectResult[14];
	int		m_dMesOCResult[2];
	int		m_dMesDeltaOCResult[2];
	int		m_nMesColorSensitivityResult[6];
	int		m_nMesRIResult[20];
	int		m_nMesRIRICornerResult[4];
	int		m_nMesColorUniformityResult[12];
	int		m_nMesBlemishResult[3];
	int		m_dMesDistortionResult;
	int		m_dMesSnrResult;
	int		m_dMesDrResult;
	int		m_dMesFovResult[3];
	int		m_dMesRotateResult;

	//---------------------------------------------------------------
	//---------------------------------------------------------------


	//20150718 CYJ 검사항목 변경으로 인한 24 -> 12
	double	dMES_MTF[COMMON_MTF_INSP_CNT];//MTF_INSP_CNT];		//MTF 검사 항목
	double  dMES_MTF_UVAfter[COMMON_MTF_INSP_CNT];//MTF_INSP_CNT];

	double	dMES_MTF_67lp[COMMON_MTF_INSP_CNT];//MTF_INSP_CNT];		//MTF 검사 항목
	double  dMES_MTF_67lp_UVAfter[COMMON_MTF_INSP_CNT];//MTF_INSP_CNT];

	double	dMES_MTF_avg[COMMON_LAST_MARK_CNT];// LAST_MARK_CNT];;		//MTF 검사 항목
	double  dMES_MTF_UVAfter_avg[COMMON_LAST_MARK_CNT];// LAST_MARK_CNT];//[5];

	double	dMES_UVBefore_OC[2];	//OC 결과.[X/Y]  UV 전
	double	dMES_UVAfter_OC[2];	//OC 결과.[X/Y]  UV 후
	double	dMES_Distortion;
	int		iMES_Defect[2];		//Defect검사[White/Black]
	double	dMES_DefectPixel_Dark_Couplet;
	double	dMES_DefectPixel_Dark_Cluster;
	double	dMES_DefectPixel_DefectPixelTotal_Hot;
	double	dMES_DefectPixel_DefectPixelTotal_Bright;
	double	dMES_DefectPixel_DefectPixelTotal_Dark;
	double	dMES_DefectPixel_DefectPixelTotal;
	double	dMES_DefectPixel_Row_Dark;
	double	dMES_DefectPixel_Column_Dark;
	double	dMES_DefectPixel_ColumnFPN;
	double	dMES_DefectPixel_Light_Couplet;
	double	dMES_DefectPixel_Light_Cluster;
	double	dMES_DefectPixel_Row_Midlevel;
	double	dMES_DefectPixel_Column_Midlevel;
	CString	sMES_DefectPixel_Dark;
	CString	sMES_DefectPixel_Light;
	double	dMES_Stain;
	double  dMES_Lens_Rotation;
	double	dMES_DistortionCentering;

	double dMES_Shading65FC[2];
	double dMES_Shading85FC[2];

	int		iMES_Current_Result;
	int		iMES_I2C_Result;

	int		iMES_MTF_Result[COMMON_MTF_INSP_CNT];//MTF_INSP_CNT];
	int		iMES_MTF_Result_UVAfter[COMMON_MTF_INSP_CNT];//MTF_INSP_CNT];

	int		iMES_MTF_67lp_Result[COMMON_LAST_MARK_CNT];
	int		iMES_MTF_67lp_Result_UVAfter[COMMON_LAST_MARK_CNT];

	int		iMES_UVBefore_OC_Result[2];
	int		iMES_UVAfter_OC_Result[2];
	int		iMES_Distortion_Result;
	int		iMES_Defect_Result[2];
	int		iMES_DefectPixel_Dark_Result;
	int		iMES_DefectPixel_Light_Result;
	int		iMES_DefectPixel_Dark_Couplet_Result;
	int		iMES_DefectPixel_Dark_Cluster_Result;
	int		iMES_DefectPixel_DefectPixelTotal_Hot_Result;
	int		iMES_DefectPixel_DefectPixelTotal_Bright_Result;
	int		iMES_DefectPixel_DefectPixelTotal_Dark_Result;
	int		iMES_DefectPixel_DefectPixelTotal_Result;
	int		iMES_DefectPixel_Row_Dark_Result;
	int		iMES_DefectPixel_Column_Dark_Result;
	int		iMES_DefectPixel_ColumnFPN_Result;
	int		iMES_DefectPixel_Light_Couplet_Result;
	int		iMES_DefectPixel_Light_Cluster_Result;
	int		iMES_DefectPixel_Row_Midlevel_Result;
	int		iMES_DefectPixel_Column_Midlevel_Result;
	int		iMES_Stain_Result;
	int		iMES_DistortionCentering_Result;
	int     iMES_Lens_Rotation_Result;
	SYSTEMTIME mesTime;
	float eepdc_x, eepdc_y;						// EEPROM Writing 용 D.C. 좌표 값
	int iMES_Shading65FC_Result[2];
	int iMES_Shading85FC_Result[2];

	CMESCommunication();
	void Messave();
};