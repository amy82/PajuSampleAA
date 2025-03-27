

//PSH150112

#ifdef  _M_X64
	#include "C:/Program Files (x86)/EzSoftware UC/AXL(Library)/C, C++/AXL.h"
	#include "C:/Program Files (x86)/EzSoftware UC/AXL(Library)/C, C++/AXM.h"
	#include "C:/Program Files (x86)/EzSoftware UC/AXL(Library)/C, C++/AXDev.h"
	#include "C:/Program Files (x86)/EzSoftware UC/AXL(Library)/C, C++/AXHS.h"
	#include "C:/Program Files (x86)/EzSoftware UC/AXL(Library)/C, C++/AXD.h"
	#pragma comment(lib, "C:/Program Files (x86)/EzSoftware UC/AXL(Library)/Library/64Bit/AxL.lib")

#else
	#include "C:\\Program Files\\EzSoftware UC\\AXL(Library)\\C, C++\\AXL.h"
	#include "C:\\Program Files\\EzSoftware UC\\AXL(Library)\\C, C++\\AXM.h"
	#include "C:\\Program Files\\EzSoftware UC\\AXL(Library)\\C, C++\\AXDev.h"
	#include "C:\\Program Files\\EzSoftware UC\\AXL(Library)\\C, C++\\AXHS.h"
	#include "C:\\Program Files\\EzSoftware UC\\AXL(Library)\\C, C++\\AXD.h"
	//#pragma comment(lib, "C:/Program Files/EzSoftware UC/AXL(Library)/Library/32Bit/AxL.lib")
	#pragma comment(lib, "C:\\Program Files\\EzSoftware UC\\AXL(Library)\\Library\\32Bit\\AxL.lib")
	//#pragma comment(lib, "C:/Program Files (x86)/EzSoftware RM/AXL(Library)/Library/32Bit/AxL.lib")
#endif


#define BOARD_CNT	1

#define ABS			1	
#define REL			0	

#define SERVO		0		
#define STEPING		1


//#define ORG_INITIAL_SETTING		//! 초기 모터 Setting 모터 원점 속도 하향.
#define USE_LED_CTRL_BACKDU		//! 백두옵티칼 조명 사용일 경우.(기존 만도향은 대겸컨트롤러 사용)

#define MOTOR_ACC_TYPE_SEC	
#ifdef	MOTOR_ACC_TYPE_SEC	
	#define ACC_CAL		1.0
#else
	#define ACC_CAL		9.8 * 1000
#endif

#if 1

enum	MOTOR_NUM {
	Motor_PCB_X, Motor_PCB_Y, Motor_PCB_TH, Motor_PCB_Xt, Motor_PCB_Yt, Motor_PCB_Z,
	Motor_Lens_X, Motor_Lens_Y, Motor_Lens_Z, Motor_Lens_Yt, Motor_Lens_Xt, MAX_MOTOR_NO
};

static int  MOTOR_SPEED_MAX[MAX_MOTOR_NO] = { 500,		1000,		500,		500,		500,	700,
500,		1000,		700,		500,		500 };

static int  MOTOR_TYPE[MAX_MOTOR_NO] = { SERVO,			SERVO,			SERVO,			STEPING,			STEPING,
SERVO,			SERVO,			SERVO,			SERVO,
SERVO,			STEPING };
//DIR_CW = +
static long	MOTOR_HOME_DIR[MAX_MOTOR_NO] = { DIR_CCW,		DIR_CCW,		DIR_CCW,			DIR_CW,			DIR_CW,			DIR_CCW,
DIR_CW,			DIR_CW,			DIR_CW,				DIR_CW,			DIR_CW };

static long MOTOR_HOME_SIG[MAX_MOTOR_NO] = { HomeSensor,		HomeSensor,			HomeSensor,			HomeSensor,			HomeSensor,			HomeSensor,
HomeSensor,			HomeSensor,			HomeSensor,			HomeSensor,			HomeSensor };

static char MotorName[MAX_MOTOR_NO][50] = { "PCB X",		"PCB Y",		"PCB Θ",		"PCB Tx",		"PCB Ty", 		"PCB Z","Lens X",		"Lens Y",		"Lens Z",		"Lens Ty"	,	"Lens Tx" };


#else

enum	MOTOR_NUM							{
											Motor_PCB_X,		Motor_PCB_Y,		Motor_PCB_Z,		Motor_PCB_TH,		Motor_PCB_Xt,		 Motor_PCB_Yt,
											Motor_Lens_X,		Motor_Lens_Y,		Motor_Lens_Xt,		Motor_Lens_Yt,		Motor_Lens_Z,		 Motor_Lens_TH,
											Motor_Insp_X,	
											Motor_LensAlign_X,	Motor_LensAlign_Y,	Motor_LensAlign_Z,	Motor_LensAlign_TH,	Motor_LensAlign_Yt,	Motor_LensAlign_Xt,
											Motor_LensLaser_Yt,	Motor_LensLaser_Xt,
											MAX_MOTOR_NO
											};

static int  MOTOR_SPEED_MAX[MAX_MOTOR_NO] = { 
											500,				1000,				500,			1000,				500,			500,				
											500,				1000,				500,			500,				500,			500,
											500,
											100,				100,				50,			50,				50,			50,
											50,				50
											};

static int  MOTOR_TYPE[MAX_MOTOR_NO] = {
										SERVO,				SERVO,				SERVO,				STEPING,			STEPING,		STEPING,
										SERVO,				SERVO,				STEPING,			STEPING,			SERVO,			STEPING,
										SERVO,
										SERVO,				SERVO,				SERVO,				STEPING,			STEPING,		STEPING,
										STEPING,			STEPING
										};

static long	MOTOR_HOME_DIR[MAX_MOTOR_NO] = { 
											DIR_CCW,		DIR_CCW,			DIR_CCW,			DIR_CCW,			DIR_CW,			DIR_CW,
											DIR_CW,			DIR_CW,				DIR_CW,				DIR_CW,				DIR_CW,			DIR_CW,
											DIR_CCW,
											DIR_CCW,		DIR_CW,				DIR_CCW,			DIR_CCW,			DIR_CW,		DIR_CCW,
											DIR_CCW,		DIR_CW
											};

static long MOTOR_HOME_SIG[MAX_MOTOR_NO] = { 
											HomeSensor,			HomeSensor,			HomeSensor,			HomeSensor,			HomeSensor,			HomeSensor,
											HomeSensor,			HomeSensor,			HomeSensor,			HomeSensor,			HomeSensor,			HomeSensor,
											HomeSensor,																								
											HomeSensor,			HomeSensor,			HomeSensor,			HomeSensor,			HomeSensor,			HomeSensor,
											HomeSensor,			HomeSensor
											};
static char MotorName[MAX_MOTOR_NO][50] = {
											"PCB X[0]",				"PCB Y[1]",			"PCB Z[2]",			"PCB Θ[3]",	"PCB Tx[4]",    "PCB Ty[5]",
											"Lens X[6]",			"Lens Y[7]",		"Lens Tx[8]",	"Lens Ty[9]",	"Lens Z[10]",	"Lens Θ[11]",
											"Insp X[12]",
											"Align X",		"Align Y",		"Align Z",		"Align Θ",		"Align Ty",		"Align Tx",
											"Laser Ty",		"Laser Tx"
											};

#endif




//! DIO Module의 개수, Added by LHW (2013/4/23)
#define MAX_MODULE_CNT 2 
enum	DIO_REF		{ DIO_OFF = 0,		DIO_ON};
enum	GRIP_IO		{ GRIP_DOWN = 0,	GRIP_UP};					//! Tray GRIP 하강(0), 상승(1)
enum	SENSOR_IO	{ SENSOR_OFF = 0,	SENSOR_ON};					//! 신호 OFF(0), ON(1)
enum	CYLINDER_IO	{ BACKWARD = 0,		FORWARD};					//! 실린더 후진(0), 전진(1)
enum	UPDOWN_IO	{ PICK_DOWN = 0,	PICK_UP};					//! 실린더 하강(0), 상승(1)
enum	VACUM_MODE  { VACCUM_OFF=0, VACCUM_ON, VACCUM_BLOW, VACCUM_BLOW_ON };
enum	TURN_IN		{ TURN_0 = 0,		TURN_90, TURN_180};			//회전 0도(0), 90도(1), 180도(2)
enum	SWITCH_TYPE	{ IN_SWITCH = 0,	OUT_SWITCH};				//스위치 투입완료(0), 배출완료(1)
enum	BUZZER		{ BUZ_ALLOFF=0, BUZ_1, BUZ_2, BUZ_3, BUZ_4};	//부저 알람(명칭 바꿀것)
enum	TOWER_LAMP	{ LAMP_ALL_OFF=0, LAMP_R, LAMP_Y, LAMP_G};		//Tower Lamp 선언
enum	MODE_SWITCH	{ SWITCH_ALL_OFF=0, SWITCH_START, SWITCH_STOP, SWITCH_ALARM};	// Main Mode Switch 

#define		MOTOR_JOG_LOW			0.1				//JOG_SPEED_LOW
#define		MOTOR_JOG_MID			0.5				//JOG_SPEED_MID
#define		MOTOR_JOG_HIGH			1.0				//JOG_SPEED_HIGH

#define SleepTimeDelay 5
#define ORG_PROC_TIME	40000


