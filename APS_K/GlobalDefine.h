#pragma once
#ifndef __GLOBAL_DEFINE
#define __GLOBAL_DEFINE


//#define		NORINDA_MODE

//=======================================================================
#define	PCB_TILT_AA				0
#define LENS_TILT_AA			1

#define ____AA_WAY					LENS_TILT_AA	//PCB_TILT_AA, LENS_TILT_AA




#define	AA_RUN_MODE				2101
#define HOLDER_RUN_MODE			3102

#define HEAD_MODEL

#define	__RUN_MODE			AA_RUN_MODE//AA_RUN_MODE

const int M2_FF_MODULE = 200200;		//240726 박동찬, 김세영 선임, 사각도포 얇은 제품 사격형 도포 차트 9개 LGIT_GRABBER_20240715_01_v2.2.3  epoxy무게 = 0.035

static int LGIT_MODEL_INDEX = M2_FF_MODULE;
//----------------------------------------------------------------------------------------------------------------------------------- 
#define					VER_STR		"250212_2"			//VC.db 이거때문??
//#define					VER_STR		"250212_1"			//git 연결 되긴 됨 근데 vs 에서 push, pull 은 아직 안됨?? 왜?
//#define					VER_STR		"250207_2"			//완제품 레이져 값
//#define					VER_STR		"250207_1"			//김세영 선임 요청
//#define					VER_STR		"250206_1"			//bcr 확인, 버튼 생성 
//#define					VER_STR		"250124_1"			//자동 흡착
//#define					VER_STR		"250123_3"			// 김세영 선임 요청 OC 이물 광원 검사 txty 보정상태 -> 티칭 pos 로 검사, bcr pos = DarkPos
//#define					VER_STR		"250123_2"			// SR-X100 연결, 리딩 확인
//#define					VER_STR		"250122_2"			//Sleep(300);, LENS_DEAD_END_MARK_2 수정 후 BCR IP UI 생성
//#define					VER_STR		"250122_1"			//LensHoleFind 자동운전 Process 추가 LensAlign 전 
//#define					VER_STR		"250121_4"			// ccd cell size 세이브에 추가 기존 하드코팅 3.0 -> 0.0 초기화로 바꿈
//#define					VER_STR		"250121_3"			//
//#define					VER_STR		"250121_2"			// Lens Hole MarkFind = procCamComAlign, Dispense_Pos2 = LensHoleFind, Dark_Pos = BCRread
//#define					VER_STR		"250121_1"			// LogData, Image, ACMIS, Excel 경로 월 -> 일, OC Spec UI 설정 변경
//#define					VER_STR		"250120_2"			// SubCam 화면 다시 원복, 박준택 선임 요첨 알고리즘 타입 UI 설정
//#define					VER_STR		"250120_1"			// 사각도포 //추가 보간 = UI 상 DisLength 5 값으로, SubDlg 버튼, SubCam 화면 수정 
//#define					VER_STR		"250117_1"			//DLL 변경, 이미지저장 파일경로 Month -> Day 
//#define					VER_STR		"250116_2"			//패턴 부호 반대
//#define					VER_STR		"250116_1"			//MandoInspLog.bInspRes = false; otp Write, Verify 제품 양불 판정 적용
//#define					VER_STR		"250115_2"			//
//#define					VER_STR		"250115_1"			//
//#define					VER_STR		"250114_5"			//
//#define					VER_STR		"250114_4"			//조명 Lee
//#define					VER_STR		"250114_3"			//
//#define					VER_STR		"250114_2"			//
//#define					VER_STR		"250114_1"			//
//#define					VER_STR		"250113_1"			//doorlift, bcr func_Barcode_Read 여기를 안탐
//#define					VER_STR		"250110_6"			//BCR
//#define					VER_STR		"250110_5"			//완제품 ALIGN 부호 반대
//#define					VER_STR		"250110_4"			//Sfr 평균값 1,2차 분리 Lee
//#define					VER_STR		"250110_3"			//Sfr 평균값 1,2차 분리
//#define					VER_STR		"250110_2"			//AA반복성 제거
//#define					VER_STR		"250110_1"			//AA반복성
//#define					VER_STR		"250109_3"			//SfrMax값, 반복성 UI 만 수정
//#define					VER_STR		"250109_2"			//모니터 스레드 도어리프트
//#define					VER_STR		"250109_1"			//LENS ALIGN 후 XY 대기위치 안가고 바로 다음 스텝 
//#define					VER_STR		"250108_3"			//LENS ALIGN 후 XY 대기위치 안가고 바로 다음 스텝 
//#define					VER_STR		"250108_2"			//조명컨트롤러 클래스 1개로 
//#define					VER_STR		"250108_1"			//도포량 측정용 UI Z 축만 Dispense_Pos1 로  
//#define					VER_STR		"250107_1"			//도포검사 수정 ,  otp수정 writeData[5] = 0x11;	////0x0F;
//bThreadTaskPcbRun = false;	정지시 추가
//bThreadTaskLensRun = false;
//Task.bMotorRunStop 변수 추가 (정지해도 모터 이동 while 문에서 안빠져나오는 것 같아 추가

//#define					VER_STR		"250103_4"				//LENS ALIGN
//#define					VER_STR		"250103_3"				//
//#define					VER_STR		"250103_2"				//holder bonding mode
//#define					VER_STR		"250103_1"				//자동에 SensorAlign 결과값 부호 변경, UV After에 OC 값 MandoInspLog. 이거 붙여넣어봄 
//#define					VER_STR		"250102_2"				//
//#define					VER_STR		"250102_1"				//
//#define					VER_STR		"241231_2"				//자동 AA 
//#define					VER_STR		"241231_1"				//HOLDER_RUN exe 
//#define					VER_STR		"241230_1"				//LGIT_GRABBER_20241230_01_v2.2.5_TEMP 윤현순 책임 DLL변경
//#define					VER_STR		"241227_3"			//OTP, F/W, Sensor ID AA, EOL 마지막 MIU.Close 전에 
//#define					VER_STR		"241227_2"			//렌즈 로딩, AA Pos 이동 스탭 변경 39000 <-> 40000 
//#define					VER_STR		"241227_1"			//Laser 수동 버튼 LT 로 변경
//#define					VER_STR		"241226_2"			//mark mil10 수정
//#define					VER_STR		"241226_1"				//OTP 검사 수동버튼
//#define					VER_STR		"241224_1"				//DRY_RUN, TRI UV 변경
//#define					VER_STR		"241223_1"				//원점 후 본딩티칭
//#define					VER_STR		"241220_1"				//이 팀장님 OTP 함수 추가 + 시퀀스에 순서만 추가 + 파이널 로그 함수에 SensorID, OTP, FW 저장 추가
//#define					VER_STR		"241219_1"				//보드 컨트롤러 1000OP 변경  BOARD_TYPE_LAON1000OP 검색 드라이버 설치 후 실행
//#define					VER_STR		"241211_1"				//PCBCoverCloseCheck  pcb motor move 함수, pcb motor Y move 함수 내 주석 처리 되어있음, Vaccum On 시퀀스 AA Loading 처음에 추가
// #define					VER_STR		"241127_1"				//HOLDER_RUN_MODE 모드 확인 완료
//#define					VER_STR		"241121_1"				//모터코드 비교,
//#define					VER_STR		"241120_1"				//Uv Altis 추가
//#define					VER_STR		"241119_3"				//io정리 완료
//#define					VER_STR		"241119_2"				//[20241029]Distribute_V2.8.0.1_VS2015 dll변경
//#define					VER_STR		"241119_1"				//파주 샘플 설비로 변경 시작 , mil10으로 교체 완료


//
//#define					VER_STR		"241114_1"
//차트 밝기 green 150정도 노출값으로 조정 , 도포무게 = 0.035 ~ 0.039정도
//0x300B 0x05   //; exposure H
//0x300C 0x78   //; exposure L
//uv전 , uv후 , 완제품 mtf측정시 평균측정 이미지도 남도록 수정
//#define					VER_STR		"241112_1"			//M2_FF_MODULE 모델 김세영 선임 sfr , 여러번 측정 평균낸 값으로 aa 진행 요청, 수정중

//opencv dll 추가
//PATH=$(ProjectDir)\Library\lib64;C:\Opencv346\install\x64\vc14\bin;%PATH%

//io , 조명,레이저 남음

//#define	MACHINE_1ST				110
//#define MACHINE______2ST		304
////
//#define	__MACHINE_MODEL			MACHINE______2ST



//=======================================================================
//=======================================================================
#define		EVMS
#define		ON_LINE_MODE
#ifdef NORINDA_MODE

//#define		ON_LINE_VISION
//#define		ON_LINE_MOTOR
//#define		ON_LINE_DIO
//#define		ON_LINE_MOTOR

#else

#ifdef		ON_LINE_MODE
#define		ON_LINE_MOTOR
////#define		ON_LINE_LAN
#define		ON_LINE_DIO
#define		ON_LINE_VISION
#define		ON_LINE_KEYENCE
#define		ON_LINE_MONITOR
#endif
#endif


//=======================================================================
//=======================================================================
#define  S_ONSEMI					2100		//기존 온세미 센서
#define  S_OMNIVISION				2200		//옴니비전 센서


#define ____SENSOR_TYPE					999999999		//S_OMNIVISION


//=================================================================================================================================================================


static CString sTempLang;
static CString sLangChange;

#define SWAP(a,b)		{int t; t=a; a=b; b=t;}		/* int형 스왑 */
#define SWAP_STR(a,b)	{CString t; t=a; a=b; b=t;}	/* CString형 스왑 */
#define rgb(r,g,b) (r*256*256+g*256+b)


#define PDC_LAVENDER			RGB(230,230,250)
#define PDC_GREEN					RGB(0,128,0)
#define PDC_LIGHTGREEN			RGB(144,238,144)
#define PDC_YELLOW				RGB(255,255,0)
#define PDC_BLACK					RGB(0,0,0)
#define PDC_RED						RGB(255,0,0)
#define PDC_BLUE					RGB(0,0,255)

#define CV_LAVENDER				CV_RGB(230,230,250)
#define CV_GREEN					CV_RGB(0,128,0)
#define CV_LIGHTGREEN			CV_RGB(144,238,144)
#define CV_YELLOW					CV_RGB(255,255,0)
#define CV_BLACK					CV_RGB(0,0,0)
#define CV_RED						CV_RGB(255,0,0)
#define CV_BLUE						CV_RGB(0,0,255)


enum MOTOR_SPEED { SPEED_AUTO_H = 0, SPEED_AUTO_L, SPEED_MANUAL };				//!! 모터 구동 속도
enum MODE_TYPE { MODE_STOP = 0, MODE_READY, MODE_AUTO, MODE_PAUSE, MODE_ERR };	//!! 모드 상태 변수 0=정지상태, 1=운전준비상태, 2=자동운전상태, 3=일시정지상태
enum HOME_READY_TYPE { TYPE_HOME = 0, TYPE_READY, TYPE_HOME_READY };					//!! 원점 상태 변수 

#define		MAX_CAM_NO		4
#define		MAX_MARK		3
enum CAMERA { CAM1 = 0, CAM2, CAM_NULL, Cam_Cnt };

enum MARK { PCB_Chip_MARK = 0, PCB_Holder_MARK, LENS_Align_MARK, MARK_CNT };

enum CHART_FIELD { CHART_CENTER = 0, CHART_TOP, CHART_BOTTOM, CHART_LEFT, CHART_RIGHT, CHART_FIELD_CNT };
enum SFR_ROI { CT = 0, CB, CL, CR, TL, TB, BR, BT, LB, LR, RT, RL, SFR_ROI_CNT };

#define SOCKET_MAIN			"192.168.3.3"
#define SOCKET_AA1			"192.168.3.1"
#define SOCKET_AA2			"192.168.3.2"

#define SFR_COMP_MAX		// SFR계산 시 평균값, 최대치 중 선택.  정의시 최대치 

#define J_RCCC	0
#define J_CRCC	1
#define J_CCRC	2
#define J_CCCR	3

#define R_RESULT_PASS					0	//양품 
#define R_RESULT_FAIL					1	//불량
#define R_FAIL_NOISE					2
#define R_FAIL_BLACK_SPOT				3
#define R_FAIL_STAIN					4

#define IMG_PROC_TYPE	7


#define		USE_GEOMETRIC
#define     USE_MIL_BAYER_CONVERSION

#define _DEF_MAX_BLOBS		200  

#define		CHART_CENTER_MARK	1000



enum LED_LIGHT_CONTROL {
	LIGHT_OC, LIGHT_PCB,
	LIGHT_LEFT_CHART, LIGHT_RIGHT_CHART,
	LIGHT_TOP_CHART1, LIGHT_TOP_CHART2, LIGHT_TOP_CHART3, LIGHT_TOP_CHART4, LIGHT_TOP_CHART5, LIGHT_TOP_CHART6,
	LIGHT_LENS,
	MAX_LIGHT_CONTROL
};


enum LED_LIGHT_DATA {
	LEDDATA_SENSOR, LEDDATA_HOLDER, LEDDATA_CHART_L, LEDDATA_CHART_R, 
	LEDDATA_TOP1_CHART, LEDDATA_TOP2_CHART, LEDDATA_TOP3_CHART, LEDDATA_TOP4_CHART, LEDDATA_TOP5_CHART, LEDDATA_TOP6_CHART,
	LEDDATA_OC, LEDDATA_EPOXY_INSP, LEDDATA_RESIN_CALC, LEDDATA_LENS, LEDDATA_STAIN, LEDDATA_DEFECT, MAX_LIGHT_DATA
};
//LEDDATA_6500K, LEDDATA_2800K
enum	RS_232_COMM { COMM_LASER, COMM_BARCODE, COMM_UV, COMM_LIGHT1, COMM_LIGHT2, COMM_LIGHT3, COMM_UV2, COMM_LIGHT4, COMM_LIGHT5, COMM_LIGHTOC_1ST, COMM_X100_BCR, MAX_RS232_NO };


#define		SIZE_OF_100BYTE					100
#define		SIZE_OF_1K						1024

#define		MAIN_DLG_SIZE_X		1920//1280						// Main Dialog..
#define		MAIN_DLG_SIZE_Y		1080
#define		SUB_DLG_OFFSET_Y	10

#define		MARK_SIZE_X			183							// 패턴 마크 Display 크기..
#define		MARK_SIZE_Y			167

#define		MARKSET_SIZE_X		377							// 패턴 마크 Display 크기..
#define		MARKSET_SIZE_Y		333

#define		CAM_SIZE_X			1280						// CIS 카메라 영상 크기..
#define		CAM_SIZE_Y			1024



#define		SMALL_CAM_SIZE_X	(CAM_SIZE_X/3+100)			// 영상 화면 Display..
#define		SMALL_CAM_SIZE_Y	(CAM_SIZE_Y/3+100)

#define		SMALL_CCD_SIZE_X	(CAM_SIZE_X/3+600)			//386
#define		SMALL_CCD_SIZE_Y	(CAM_SIZE_Y/3+240)			//100





#define		CAM_REDUCE_FACTOR_X		(double)SMALL_CAM_SIZE_X/CAM_SIZE_X
#define		CAM_REDUCE_FACTOR_Y		(double)SMALL_CAM_SIZE_Y/CAM_SIZE_Y
#define		CAM_EXPAND_FACTOR_X		(double)CAM_SIZE_X/SMALL_CAM_SIZE_X
#define		CAM_EXPAND_FACTOR_Y		(double)CAM_SIZE_Y/SMALL_CAM_SIZE_Y


#define		IO_DELAY_TIME			20000

#define		IN_POSITION_VAL			0.2

#define		MAX_DEVICE				2


#define		CCD				Cam_Cnt

#define		OS_PIN_COUNT		55

#define		MAX_ALARM_PAGE_CNT			20			// 알람 히스토리 창의 최대 알람 페이지 수..
#define		MAX_ALARM_LIST_IN_PAGE		24			// 알람 페이지 당 출력되는 알람 수..

#define		MAX_NG_LIST					20			// 불량 배출 시 NG 항목 등록 수..



enum OUTPUT_MODE { ASCII_MODE = 0, ASCII_MODE_2, FLOAT_MODE, DEC_MODE, HEX_MODE, FuSeID_MODE};
enum E_GRAB_METHOD { LAON_CVT_COLOR, MIL_BAYER_CVT_COLOR };
enum IMAGE_SAVE_ID { LENS_IMAGE_SAVE, PCB_IMAGE_SAVE, CHIP_IMAGE_SAVE, AA_FINAL_IMAGE_SAVE, AA_NG_IMAGE_SAVE, AA_CIRCLE_NG_IMAGE_SAVE, OPTIC_IMAGE_SAVE, DEFECT_NG_IMAGE_SAVE, EPOXY_IMAGE_SAVE };
enum AA_MODE { MODE_MARKCENTER = 0, MODE_DISTORTIONCENTER, MODE_OPTICAL };
enum MTF_INSP_MODE { MTF_17P = 0, MTF_24P };

#define		COMMON_LAST_MARK_CNT			20		//버퍼 공간 , 저장 개수로만 사용
#define		COMMON_MTF_INSP_CNT				50		//버퍼 공간 , 저장 개수로만 사용


#define MAX_FOV_COUNT				9       //협각

#define MAX_SNR_COUNT				3       //흰,빨,검순서


#define		SFR_ROI_VERTICAL			0//1
#define		SFR_ROI_HORIZONTAL			1//2

// Cneter SFR 검사 Box 번호..
#define		SFR_CENTER_UP					0	
#define		SFR_CENTER_DOWN					1	
#define		SFR_CENTER_LEFT					2
#define		SFR_CENTER_RIGHT				3
#define		SFR_CENTER_END					3

#define		SFR_05_LEFT_UP_H				4	
#define		SFR_05_LEFT_UP_V				5	

#define		SFR_05_RIGHT_UP_H				6
#define		SFR_05_RIGHT_UP_V				7

#define		SFR_05_LEFT_DOWN_H				8	
#define		SFR_05_LEFT_DOWN_V				9	

#define		SFR_05_RIGHT_DOWN_H				10
#define		SFR_05_RIGHT_DOWN_V				11
//--------------------------------------------------------else
#define		SFR_07_LEFT_UP_H				12	
#define		SFR_07_LEFT_UP_V				13	

#define		SFR_07_RIGHT_UP_H				14
#define		SFR_07_RIGHT_UP_V				15

#define		SFR_07_LEFT_DOWN_H				16	
#define		SFR_07_LEFT_DOWN_V				17	

#define		SFR_07_RIGHT_DOWN_H				18
#define		SFR_07_RIGHT_DOWN_V				19
//--------------------------------------------------------visteon






// 0.5 필드 코너부 SFR 검사 Box 번호..
#define		SFR_50_05						4
#define		SFR_50_06						5
#define		SFR_50_07						6
#define		SFR_50_08						7

// 0.7 필드 코너부 SFR 검사 Box 번호..		
#define		SFR_70_09						8
#define		SFR_70_10						9
#define		SFR_70_11						10
#define		SFR_70_12						11

// 0.7 필드 코너부 SFR 검사 Box 번호..						
#define		SFR_LEFT_UP_INDEX				16		// 황준혁  최종 검사관련된 내용 연계되어 있음
#define		SFR_LEFT_UP_INDEX_2				17

#define		SFR_RIGHT_UP_INDEX				18		// 황준혁  최종 검사관련된 내용 연계되어 있음
#define		SFR_RIGHT_UP_INDEX_2			19

#define		SFR_RIGHT_DOWN_INDEX			20
#define		SFR_RIGHT_DOWN_INDEX_2			21

#define		SFR_LEFT_DOWN_INDEX				22
#define		SFR_LEFT_DOWN_INDEX_2			23



#define		LED_CHART			1
#define		LED_OC				2
#define		LED_LENS			3
#define		LED_PCB				4


#define		SFR_FIRST							0
#define		SFR_SECOND							1
#define		SFR_FINAL							2
#define		OC_INSP								3
#define		SFR_BEFORE_UV						4
#define		SFR_AFTER_UV						5
#define		SFR_OFFSET_DATA						6
#define		SFR_AFTER_OFFSET_MOVE				7
#define		SFR_AFTER_TILT						8
#define		SFR_MANUAL							9
#define		MTF_INSP							10
#define		SFR_STEP							11



#define		UNLOADING_INDEX		0
#define		AA1_INDEX			1
#define		AA2_INDEX			2
#define		OC_INDEX			3
#define		UV_INDEX			4


#define		RECEIVE_DATA		FALSE
#define		SEND_DATA			TRUE

enum SIDE_MODEL { SIDE_FRONT = 0, SIDE_BACK };

enum DIALOG { MAIN_DLG, MODEL_DLG, LENS_DLG, LENS_EDGE_DLG, PCB_DLG, RESIN_DLG, CCD_DLG, MOTOR_DLG, MOTOR_DLG2, MOTOR_DLG3, IO_DLG, ALARM_DLG, MOTOR_INSPDLG, PCB_INSPDLG , MOTOR_DLG4};

enum RAW_CAPTURE_TYPE { MID_6500K_RAW = 0, LOW_LEVEL_RAW, MID_2800K_RAW, UV_BEFORE_CHART, UV_AFTER_CHART, EOL_CHART, CHART_RAW, CHART_SECOND_RAW };
enum JPG_CAPTURE_TYPE { BLACKSPOT_JPG = 0, LCBJPG, YMEAN_JPG, DEFECT_MID_JPG, DEFECT_LOW_JPG, MTF_JPG };
enum FIDUCIAL_MARK_TYPE { DOT_TYPE = 0, GRID_TYPE = 2 };

enum BOX_MOVE_TYPE { MOVE_POS = 0, MOVE_SIZE };
enum SFR_MOVE_TYPE { MOVE_UP = 0, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };

/* 패턴매칭 결과 */
enum PAT_RESULT { FIND_OK, FIND_ERR, NOMARK, RATE_ERR, ROTATE_ERR };
enum MOUSE_CURSOR { MOVE_ALL, MOVE_WIDTH_LEFT, MOVE_WIDTH_RIGHT, MOVE_HEIGHT_TOP, MOVE_HEIGHT_BOTTOM, MOVE_NW, MOVE_NE, MOVE_SW, MOVE_SE };
enum LAMP_NO { ALARM_ON, ALARM_OFF, AUTO_STOP, AUTO_RUN };

enum STEP_ID { STEP_LENS_SUPPLY, STEP_PCB_SUPPLY, STEP_OS_CHECK, STEP_RESIN_SUPPLY, STEP_CCD_ALIGN, STEP_CCD_INSP, STEP_UVLAMP, STEP_EMISSION };
enum STEP_RESULT { STEP_NORMAL, STEP_OK, STEP_NG };


enum TIMER_NUM { MAIN_TIMER = 1, MOTOR_TIMER, JOG_TIMER, IO_TIMER, LENS_TIMER, PCB_TIMER, RESIN_TIMER, MSG_TIMER, HOME_TIMER, CCD_DEFECT_TIMER, KILL_TIMER };


enum EPOXY_MODEL { CRICLE_EPOXY, RECT_EPOXY, POLYGON_EPOXY, POINT_EPOXY};

#define	MAX_MODEL_CNT			1000


enum	MOTOR_POS 
{
	Wait_Pos, Loading_Pos, Holder_Pos, Dispense_Pos, Lens_Pos,
	Laser_Pcb_Pos, Laser_Lens_Pos, Align_Pos, Bonding_Pos, Dark_Pos, Defect_Pos, OC_6500K_Pos, OC_2800K_Pos,
	Pcb_Loading_Pos, Cover_Loading_Pos, Cover_UnLoading_Pos, PDispense_Pos,
	Contact_Pos, Calc_Pos, Clean_Pos, Insp_Pos, Holder_Uv_Pos, ContiTailDelay_Pos,
	Com_Laser_Pos, Calc2_Pos, CompleteAlign_Pos,
	Dispense_Pos1, Dispense_Pos2, Dispense_Pos3,
	MAX_POS_NO

};

static char MotorPosName[MAX_POS_NO][50] = { "Wait Pos",	"Loading Pos",	"Holder Pos",	"Dispense Pos", "Lens Align",
"pcb Laser",		"Lens Laser",	"Sensor Align", "Bonding Pos", "Barcode Pos", "Defect Pos", "OC 6500K Pos" , "OC 2800K Pos",
"Pcb Load Pos" , "Cover Load Pos",	"Cover UnLoad Pos",	"PDispense Pos",
"Contact Pos", "Calc Pos", "Ready Pos", "도포검사 Pos", "OQLaser Pos", "TailDelay_Pos",
"완제품LaserPos", "도포Calc2 위치", "ComAlign Pos","도포무게측정Pos", "Dispense Pos2", "Dispense Pos3" };


enum	MTF_POS { MTF_Center, MTF_left_upper, MTF_right_upper, MTF_left_bottom, MTF_right_bottom, MAX_MTF_NO };




static TCHAR* DEFECT_SPEC_NAME[26] =//[19] =
{ _T("AnBlockSizeHot"),	 _T("AnBlockSizeDark"),			_T("AnBlockSizeBright"),
_T("AnThresholdTypeHot"),		_T("AnThresholdTypeDark"),		_T("AnThresholdTypeBright"),
_T("AdDefectThresholdHot"),	_T("AdDefectThresholdDark"),	_T("AdDefectThresholdBright"),
_T("AnMaxHotDefectNum"),		_T("AnMaxDarkDefectNum"),		_T("AnMaxBrightDefectNum"),
_T("AnMaxHotClusterNum"),		_T("AnMaxDarkClusterNum"),		_T("AnMaxBrightClusterNum"),
_T("AnEnableChannel"),
_T("AnDefectInCluster"),
_T("ADefectInClusterChannel"),	//_T("AspecColumnFPN"),
_T("AEnableCircle"),
_T("APosOffsetX"),		_T("APosOffsetY"),
_T("ARadiusRatioX"),	_T("ARadiusRatioY"),
_T("AThresholdRatio"),	_T("AROIRange"),		_T("AUsediFixedCircle")
};

static TCHAR* pszXtype[5] = { _T("CENTER"), _T("TL"), _T("TR"), _T("BL"), _T("BR") };
static TCHAR* pszPlustype[5] = { _T("CENTER"), _T("T"), _T("B"), _T("L"), _T("R") };
//
static TCHAR* OC_SPEC_NAME[2] =
{
	_T("AnFiducialMarkNum"), _T("AnFiducialMarkType")
};
//
static TCHAR* COLOR_SENS_SPEC_NAME[8] =
{ _T("AdSpecDevMaxRG"),_T("AdSpecDevMinRG"),_T("AdSpecDevMaxBG"),
_T("AdSpecDevMinBG"),_T("AdSpecDevMaxGrGb"),_T("AdSpecDevMinGrGb")
,_T("AnAdjustType"),_T("AnTypicalValueType")
};
//
static TCHAR* SNR_SPEC_NAME[3] =
{ _T("AdSNRThreshold"), _T("AdSNRMIN"), _T("AdSNRMAX")
};
//


static TCHAR* UNIFORMITY_SPEC_NAME[7] =
{ _T("AnGridSizeX"),		_T("AnGridSizeY"),
_T("AnColorSpaceType"),		_T("AnMaxDiffType"),
_T("AspecMaxDiffRG"),		_T("AspecMaxDiffBG"),
_T("AspecMaxDiffRB")
};
//

static TCHAR* R_ILLUMINATION_SPEC_NAME[5] =
{ _T("AdSpecCenterIntensity1"),		_T("AdSpecCenterIntensity2"),		_T("AdSpecCenterIntensity3"),
_T("AdSpecCenterIntensity4"),		_T("AnSpecPixelCntInBlock")
};

static TCHAR* STAIN_BLEMISH_SPEC_NAME[20] =
{
	_T("AnBlockWidth"),			_T("AnBlockHeight"),		_T("AnClusterSize"),
	_T("AnDefectInCluster"),	_T("AdDefectRatio"),
	_T("AbEnableCircle"),		_T("AnPosOffsetX"),			_T("AnPosOffsetY"),
	_T("AdRadiusRatioX"),		_T("AdRadiusRatioY"),		_T("AdThresholdRatio"),
	_T("AdROIRange"),			_T("AnUsedFixedCircle"),	_T("AbEnableMultiCircle"),
	_T("AdZoneSizeRatio1"),		_T("AdZoneSizeRatio2"),		_T("AdZoneSizeRatio3"),
	_T("AdThreshold1"),			_T("AdThreshold2"),			_T("AdThreshold3")
};
const int LcbMaxCount = 35;


static TCHAR* STAIN_LCB_SPEC_NAME[LcbMaxCount] =
{
	_T("AdCenterThreshold"),		_T("AdEdgeThreshold"),		_T("AdCornerThreshold"),
	_T("AnMaxSingleDefectNum"),
	_T("AnMinDefectWidthHeigh"),
	_T("AnCenterMaxR"),				_T("AnCenterMaxGR"),			_T("AnCenterMaxGB"),	_T("AnCenterMaxB"),
	_T("AnEdgeMaxR"),				_T("AnEdgeMaxGR"),				_T("AnEdgeMaxGB"),			_T("AnEdgeMaxB"),
	_T("AnCornerMaxR"),			_T("AnCornerMaxGR"),			_T("AnCornerMaxGB"),		_T("AnCornerMaxB"),
	_T("AbEnableCircle"),		_T("AnPosOffsetX"),				_T("AnPosOffsetY"),
	_T("AdRadiusRatioX"),			_T("AdRadiusRatioY"),		_T("AdThresholdRatio"),			_T("AdROIRange"),
	_T("AnUsedFixedCircle"),		_T("AbEnableMultiCircle"),
	_T("AdZoneSizeRatio1"),		_T("AdZoneSizeRatio2"),		_T("AdZoneSizeRatio3"),
	_T("AdThreshold1"),				_T("AdThreshold2"),			_T("AdThreshold3"),
	_T("AnBlobSize1"),				_T("AnBlobSize2"),			_T("AnBlobSize3")
};
const int YmeanMaxCount = 28;
static TCHAR* STAIN_YMEAN_SPEC_NAME[YmeanMaxCount] =
{
	_T("AdEdgeSize"),				_T("AdCenterThreshold"),		_T("AdEdgeThreshold"),
	_T("AdCornerThreshold"),		_T("AnDefecBlockSize"),			_T("AnLscBlockSize"),
	_T("AnCalcType"),				_T("AnnMaxRecursiveCount"),     _T("AdMaxDefectSize"),
	_T("AdPixelSize"),
	_T("AbEnableCircle"),
	_T("AnPosOffsetX"),				_T("AnPosOffsetY"),
	_T("AdRadiusRatioX"),			_T("AdRadiusRatioY"),
	_T("AdThresholdRatio"),			_T("AdROIRange"),
	_T("AnUsedFixedCircle"),		_T("AbEnableMultiCircle"),
	_T("AdZoneSizeRatio1"),			_T("AdZoneSizeRatio2"),			_T("AdZoneSizeRatio3"),
	_T("AdThreshold1"),				_T("AdThreshold2"),				_T("AdThreshold3"),
	_T("AnBlobSize1"),				_T("AnBlobSize2"),			_T("AnBlobSize3")
};

const int FdfMaxCount = 30;
static TCHAR* STAIN_FDF_SPEC_NAME[FdfMaxCount] =		//30개
{
	_T("AdCenterThreshold"),		_T("AdEdgeThreshold"),		_T("AdCornerThreshold"),
	_T("AnMedianFilterSize"),		_T("AnLscBlockSize"),
	_T("AnWidthScaleRatio"),		_T("AnHeightScaleRatio"),
	_T("AnMinDefectWidthHeight"),	_T("AnWindowSize"),
	_T("AnEdgeSize"),				_T("AbEnableChannel"),
	_T("AnMaxSingleDefectNum"),
	_T("AbEnableCircle"),
	_T("AnPosOffsetX"),				_T("AnPosOffsetY"),
	_T("AdRadiusRatioX"),			_T("AdRadiusRatioY"),
	_T("AdThresholdRatio"),			_T("AdROIRange"),
	_T("AnUsedFixedCircle"),
	_T("AbEnableMultiCircle"),
	_T("AdZoneSizeRatio1"),			_T("AdZoneSizeRatio2"),			_T("AdZoneSizeRatio3"),
	_T("AdThreshold1"),				_T("AdThreshold2"),				_T("AdThreshold3"),
	_T("AnBlobSize1"),				_T("AnBlobSize2"),			_T("AnBlobSize3")
};

static TCHAR* CHART_SPEC_NAME[5] =
{
	_T("AdRealGapX"), _T("AdRealGapY"),
	_T("AnFiducialMarkType"),		_T("AdModuleChartDistance"),
	_T("AnDistortionAlrotithmType")
};
static TCHAR* RI_SPEC_NAME[8] =
{
	_T("AnSpecPixelCntInBlock"),    _T("AnEnableChannel"),
	_T("AdSpecCenterIntensity1"),_T("AdSpecCenterIntensity2"),_T("AdSpecCenterIntensity3"),_T("AdSpecCenterIntensity4")
	,_T("AnCornerVariationMin"),_T("AnCornerVariationMax")
};

static TCHAR* SATURATION_SPEC_NAME[2] =
{
	_T("AnSpecSaturationMin"),    _T("AnSpecSaturationMax")
};



enum	MARK_DIRECTION { LEFT_BLACK = 0, RIGHT_BLACK };			// 정재호 20140905 추가.. 챠트에서 SFR 검사 영역의 BOX가 좌우 중 어느쪽이 검은 쪽인지?
enum	DIRECTION_NO { LEFT_DIR = 0, RIGHT_DIR, TOP_DIR, BOTTOM_DIR };


#define		MOTOR_Lens_Z_OFFSET			1		// 1mm  본딩 위치 이동시 1mm 위로 후 모든 모터 이동 완료후 원래 위치로 이동.

#define		RGB_DLG_BG						RGB(40, 39, 35)
#define		RGB_CTRL_BG						RGB(174,54,27)//RGB(55, 73, 93)


#define		GRID_COLOR_TITLE			RGB(0,155,155)
//
#define		GRID_COLOR_WHITE            RGB(255,255,255)
#define		GRID_COLOR_GREEN			RGB(128, 255, 128)
#define		GRID_COLOR_RED				RGB(255, 94, 164)

#define		GRID_COLOR_SPARE_MOTOR		RGB(128, 128, 128)
#define		GRID_COLOR_SELECT			RGB(244, 216, 234)

#define		GRID_COLOR_DIO_OUT			RGB(128, 255, 128)
#define		GRID_COLOR_DIO_IN			RGB(255, 94, 164)

#define		RGB_COLOR_WHITE					RGB(255, 255, 255)
#define		RGB_COLOR_BLACK					RGB(0, 0, 0)
#define		RGB_COLOR_RED					RGB(255, 0, 0)
#define		RGB_COLOR_GREEN					RGB(0, 255, 0)
#define		RGB_COLOR_BLUE					RGB(0, 0, 255)
#define		RGB_COLOR_GRAY					RGB(100, 100, 100)

#define		A_COLOR_BLACK                                 M_RGB888(0,0,0)
#define		A_COLOR_RED                                   M_RGB888(255,0,0)
#define		A_COLOR_GREEN                                 M_RGB888(0,255,0)
#define		A_COLOR_BLUE                                  M_RGB888(0,0,255)
#define		A_COLOR_YELLOW                                M_RGB888(255,255,0)
#define		A_COLOR_MAGENTA                               M_RGB888(255,0,255)
#define		A_COLOR_CYAN                                  M_RGB888(0,255,255)
#define		A_COLOR_WHITE                                 M_RGB888(255,255,255)
#define		A_COLOR_GRAY                                  M_RGB888(128,128,128)
#define		A_COLOR_BRIGHT_GRAY                           M_RGB888(192,192,192)
#define		A_COLOR_LIGHT_GRAY                            M_RGB888(160,160,164)
#define		A_COLOR_LIGHT_GREEN                           M_RGB888(192,220,192)
#define		A_COLOR_LIGHT_BLUE                            M_RGB888(166,202,240)
#define		A_COLOR_LIGHT_WHITE                           M_RGB888(255,251,240)
#define		A_COLOR_DARK_RED                              M_RGB888(128,0,0)
#define		A_COLOR_DARK_GREEN                            M_RGB888(0,128,0)
#define		A_COLOR_DARK_BLUE                             M_RGB888(0,0,128)
#define		A_COLOR_DARK_YELLOW                           M_RGB888(128,128,0)
#define		A_COLOR_DARK_MAGENTA                          M_RGB888(128,0,128)
#define		A_COLOR_DARK_CYAN                             M_RGB888(0,128,128)

#define CV_LAVENDER					CV_RGB(230,230,250)
#define CV_GREEN					CV_RGB(0,128,0)
#define CV_LIGHTGREEN				CV_RGB(144,238,144)
#define CV_YELLOW					CV_RGB(255,255,0)
#define CV_BLACK					CV_RGB(0,0,0)
#define CV_RED						CV_RGB(255,0,0)
#define CV_BLUE						CV_RGB(0,0,255)

#define		MOTOR_GAP				0.1				// Encoder  오차 허용 범위

#define		MOTOR_ORIGIN_TIME	    320000			// msec..// test중
#define		MOTOR_MOVE_TIME			50000			// msec..//test중
#define		MOTOR_STOP_TIME			1000			// msec..
#define		IO_CHECK_TIME			3000			// msec..

#define		MOTOR_JOG_LOW			0.1				//JOG_SPEED_LOW
#define		MOTOR_JOG_MID			0.5				//JOG_SPEED_MID
#define		MOTOR_JOG_HIGH			1.0				//JOG_SPEED_HIGH

#ifndef M_PI
#define M_PI       	3.14159265358979323846f
#endif

#define M_PI_2     	1.57079632679489661923f
#define M_PI_4     	0.785398163397448309616f
#define M2_PI      	(M_PI+M_PI)
//! <--------------------------------------------------------------------------
//! 아진엑스텍 Motion Controller 전역 객체
#include "AxlMotion/AXTDefine.h"
#include "AxlMotion/AxlMotorSet.h"
#include "AxlMotion/FlowProcess.h"



class mCDPoint
{
public:
	double x, y;
	mCDPoint()
	{
		x = y = 0.0;
	}
};



#endif