
// DioControl.h : 


#pragma once

#include "stdafx.h"

//DIO INPUT

#define		DIO_IN_EMERGENCY1						0x00000001		//!  1) 
#define		DIO_IN_EMERGENCY2						0x00000002		//!  2) 
#define		DIO_IN_PCB_VACUUM						0x00000004		//!  3) 
#define		DIO_IN______TEMP4						0x00000008		//!  4) 
#define		DIO_IN______TEMP5						0x00000010		//!  5) 
#define		DIO_IN______TEMP6						0x00000020		//!  6) 
#define     DIO_IN_DOORSENSOR1						0x00000040		//!  7) 
#define     DIO_IN_DOORSENSOR2						0x00000080		//!  8) 
#define		DIO_IN_DOORSENSOR3						0x00000100		//!  9) 
#define		DIO_IN_DOORSENSOR4						0x00000200		//! 10) 
#define		DIO_IN_DOORSENSOR5						0x00000400		//! 11) 
#define		DIO_IN_DOORSENSOR6						0x00000800		//! 12)  
#define		DIO_IN_DOORSENSOR7						0x00001000		//! 13)
#define     DIO_IN______TEMP14						0x00002000		//! 14) 
#define     DIO_IN______TEMP15						0x00004000		//! 15) 
#define     DIO_IN______TEMP16						0x00008000		//! 16) 
//-----------------------------------------------------------------------------
#define		DIO_IN______TEMP17						0x00010000		//! 17) 
#define		DIO_IN______TEMP18						0x00020000		//! 18) 
#define     DIO_IN_UV_LAMP_ON						0x00040000		//! 19) 
#define     DIO_IN_UV_LAMP_ALARMUP					0x00080000		//! 20) 
#define     DIO_IN_UV_LAMP_ALARMDOWN				0x00100000		//! 21) 
#define		DIO_IN______TEMP22						0x00200000		//! 22) 
#define		DIO_IN______TEMP23						0x00400000		//! 23) 
#define		DIO_IN______TEMP24						0x00800000		//! 24) 
#define     DIO_IN_EPOXY_ON							0x01000000		//! 25) 
#define		DIO_IN______TEMP26						0x02000000		//! 26)
#define		DIO_IN______TEMP27						0x04000000		//! 27) 
#define		DIO_IN______TEMP28						0x08000000		//! 28) 
#define		DIO_IN______TEMP29						0x10000000		//! 29) 
#define		DIO_IN______TEMP30						0x20000000		//! 30) 
#define     DIO_IN_LIGHT_CURTAIN					0x40000000		//! 31) 
#define		DIO_IN_AA_STAGE1_INTERLOCK				0x80000000		//! 32) 


//1번 DIO
#define		DIO_IN_DIS_SENSOR						0x00000001		//!  1) LENS GRIP 전진
#define		DIO_IN_PCBSTAGE_GRIP_BACK				0x00000002		//!  2) LENS GRIP 후진
#define		DIO_IN_PCBSTAGE_GRIP_FOR				0x00000004		//!  3) Lens Stage Gripper 후진 센서
#define		DIO_IN_DOOR_CLOSE						0x00000008		//!  4) DOOR Close
#define		DIO_IN_DOOR_OPEN						0x00000010		//!  5) DOOR Open
#define		DIO_IN______2TEMP6						0x00000020		//!  6) 비어있음
#define		DIO_IN_START							0x00000040		//!  7) START PB
#define		DIO_IN_DOOR_PB							0x00000080		//!  8) DOOR PB
#define		DIO_IN______2TEMP9						0x00000100		//!  9) 비어있음
#define		DIO_IN______2TEMP10						0x00000200		//! 10) 비어있음
#define		DIO_IN______2TEMP11						0x00000400		//! 11) 비어있음
#define		DIO_IN______2TEMP12						0x00000800		//! 12) 비어있음
#define		DIO_IN______2TEMP13						0x00001000		//! 13) 비어있음
#define		DIO_IN______2TEMP14						0x00002000		//! 14) 비어있음
#define		DIO_IN_OC_FOR							0x00004000		//! 15) OC 조명 전진 === 임시
#define		DIO_IN_OC_BACK							0x00008000		//! 16) OC 조명 후진 === 임시
//------------------------------------------------------------------
#define		DIO_IN______2TEMP17						0x00010000		//! 17) Lens Grip 전진센서
#define		DIO_IN_LENS_GRIP_BACK					0x00020000		//! 18) Lens Grip 후진센서
#define     DIO_IN_LENS_GRIP_FOR					0x00040000		//! 19) LASER  상승센서 DIO_IN_CHART_BACK
#define     DIO_IN_PCB_GRIP_BACK					0x00080000		//! 20) LASER  하강센서 DIO_IN_CHART_FOR
#define     DIO_IN_PCB_GRIP_FOR						0x00100000		//! 21) Dark 검사 상승센서
#define     DIO_IN______2TEMP22						0x00200000		//! 22) Dark 검사 하강센서
#define     DIO_IN______2TEMP23						0x00400000		//! 23) C/R 전진
#define     DIO_IN______2TEMP24						0x00800000		//! 24) C/R 후진
#define		DIO_IN_PCB_SOCKET_CLOSE					0x01000000		//! 25) PCB GRIP 후진	-- 사용안함	
#define     DIO_IN______2TEMP26						0x02000000		//! 26) PCB GRIP 전진	-- 사용안함
#define		DIO_IN______2TEMP27						0x04000000		//! 27) PCB 클립 소켓 닫힘 여부
#define		DIO_IN_OCLIGHT_FOR						0x08000000		//! 28) 검사 FEED 전진
#define		DIO_IN_OCLIGHT_BACK						0x10000000		//! 29) 검사 FEED 후진
#define		DIO_IN_LASER_CAM_DOWN					0x20000000		//! 30) DARK 전진
#define		DIO_IN_LASER_CAM_FOR					0x40000000		//! 31) DARK 후진
#define		DIO_IN______2TEMP32						0x80000000		//! 32) DARK CAP PUSHER 상승



//●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●
//●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●
///////////////// DIO Output DEFINE /////////////////
//0번 모듈

//!---------- Channel 0
	//0번
#define		DIO_OUT_PCB_VACUUM				0x01		//!  1) 비어있음
#define		DIO_OUT_PCB_VACUUM_OFF			0x02		//!  2) 비어있음
#define		DIO_OUT_SPARE3					0x04		//!  3) 비어있음
#define		DIO_OUT_SPARE4					0x08		//!  4) 비어있음
#define     DIO_OUT_SPARE5					0x10		//!  5) 비어있음
#define     DIO_OUT_SPARE6					0x20		//!  6) 비어있음
#define     DIO_OUT_SPARE7					0x40		//!  7) 비어있음
#define     DIO_OUT_SPARE8					0x80		//!  8) 비어있음
	//
#define     DIO_OUT_TOWER_LAMP_R			0x01		//!  9) LAMP R
#define     DIO_OUT_TOWER_LAMP_Y			0x02		//! 10) LAMP Y
#define		DIO_OUT_TOWER_LAMP_G			0x04		//! 11) LAMP G
#define		DIO_OUT_SPARE9					0x08		//! 12) 비어있음
#define		DIO_OUT_BUZZER1					0x10		//! 13) BUZZER1
#define		DIO_OUT_BUZZER2					0x20		//! 14) BUZZER2
#define		DIO_OUT_BUZZER3					0x40		//! 15) BUZZER3
#define		DIO_OUT_BUZZER4					0x80		//! 16) BUZZER4
	//-----------------------------------------------------------------------------
#define		DIO_OUT_SPARE10					0x01		//! 17) 비어있음
#define		DIO_OUT_SPARE11					0x02		//! 18) 비어있음
#define		DIO_OUT_UV_ON					0x04		//! 19) UV ON
#define		DIO_OUT_UV_EMG					0x08		//! 20) UV EMG
#define		DIO_OUT_SPARE12					0x10		//! 21) 비어있음
#define		DIO_OUT_SPARE13					0x20		//! 22) 비어있음
#define		DIO_OUT_SPARE14					0x40		//! 23) 비어있음
#define		DIO_OUT_SPARE15					0x80		//! 24) 비어있음
	//
#define		DIO_OUT_EPOXY_ON				0x01		//! 25) 토출 ON
#define		DIO_OUT_SPARE16					0x02		//! 26) 비어있음
#define		DIO_OUT_SPARE17					0x04		//! 27) 비어있음
#define		DIO_OUT_SPARE18					0x08		//! 28) 비어있음
#define		DIO_OUT_SPARE19					0x10		//! 29) 비어있음
#define		DIO_OUT_SPARE20					0x20		//! 30) 비어있음
#define		DIO_OUT_SPARE21					0x40		//! 31) 비어있음
#define		DIO_OUT_SPARE22					0x80		//! 32) 비어있음



	//1번
#define		DIO_OUT_PCBSTAGE_GRIP_FOR		0x01		//!  1) HOLDER GRIP 전진
#define		DIO_OUT_PCBSTAGE_GRIP_BACK		0x02		//!  2) HOLDER GRIP 후진
#define		DIO_OUT_DOOR_CLOSE				0x04		//!  3) DOOR CLOSE
#define		DIO_OUT_DOOR_OPEN				0x08		//!  4) DOOR OPEN
#define		DIO_OUT_LENS_GRIP_BACK			0x10		//!  5) LENS GRIP 후진
#define		DIO_OUT_LENS_GRIP_FOR			0x20		//!  6) LENS GRIP 전진
#define		DIO_OUT_PCB_GRIP_BACK			0x40		//!  7) LENS ALIGN CHUCK 후진
#define		DIO_OUT_PCB_GRIP_FOR			0x80		//!  8) LENS ALIGN CHUCK 전진
	//------------------------------------------------------------------
#define		DIO_OUT_OCLIGHT_BACK			0x01		//!  9) 검사 FEED 전진
#define		DIO_OUT_OCLIGHT_FOR				0x02		//! 10) 검사 FEED 후진
#define		DIO_OUT_LASER_CAM_BACK			0x04		//! 11) DARK CAP PUSHER 상승
#define		DIO_OUT_LASER_CAM_FOR			0x08		//! 12) DARK CAP PUSHER 하강
#define		DIO_OUT_SPARE23					0x10		//! 13) 비어있음
#define		DIO_OUT_SPARE24					0x20		//! 14) 비어있음
#define		DIO_OUT_SPARE25					0x40		//! 15) 비어있음
#define		DIO_OUT_SPARE26					0x80		//! 16) 비어있음
	//------------------------------------------------------------------
#define		DIO_OUT_START_PB				0x01		//! 17) START PB
#define		DIO_OUT_DOOR_PB					0x02		//! 18) DOOR PB
#define		DIO_OUT_SPARE27					0x04		//! 19) 비어있음
#define		DIO_OUT_SPARE28					0x08		//! 20) 비어있음
#define		DIO_OUT_SPARE29					0x10		//! 21) 비어있음
#define		DIO_OUT_SPARE30					0x20		//! 22) 비어있음
#define		DIO_OUT_SPARE31					0x40		//! 23) 비어있음
#define     DIO_OUT_SPARE32					0x80		//!	24) 비어있음
	//
#define		DIO_OUT_SPARE33					0x01		//!	25) 비어있음
#define		DIO_OUT_SPARE34					0x02		//!	26) 비어있음
#define		DIO_OUT_SPARE35					0x04		//!	27) 비어있음
#define		DIO_OUT_SPARE36					0x08		//!	28) 비어있음
#define		DIO_OUT_SPARE37					0x10		//!	29) 비어있음
#define		DIO_OUT_SPARE38					0x20		//!	30) 비어있음
#define		DIO_OUT_OC_FOR					0x40		//!	31) OC 조명 전진 === 임시
#define		DIO_OUT_OC_BACK					0x80		//!	32) OC 조명 후진 === 임시


//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★


class CDioControl
{
public:
	CDioControl();

	CCriticalSection	g_CriOutDio;
public:
	//241119
	//New
	bool OcSlinderMove(bool flag, bool waitFlag);
	bool OcSlinderCheck(bool flag, bool waitFlag);

	//Cam, Laser 실린더 전,후진
	bool CamLaserSlinderMove(bool flag, bool waitFlag = true);
	//Cam, Laser 실린더 상태 확인
	bool CamLaserSlinderCheck(bool flag, bool waitFlag = true);

	//Conti 렌즈 꼬리 그립
	bool ContiTailGrip(bool flag, bool waitFlag = true);
	//Conti 렌즈 꼬리 그립 상태 확인
	bool ContiTailGripCheck(bool flag, bool waitFlag = true);

	//! UV부 연기 탈취
	bool UVGasClean(bool flag);

	//! Lens Gripper 전진/후진
	bool HolderGrip(bool flag, bool waitFlag = true);
	//! Lens Gripper 전진/후진 센서
	bool HolderGripCheck(bool flag, bool waitFlag = true);

	//! Lens Gripper 전진/후진
	bool LensMotorGrip(bool flag, bool waitFlag = true);
	//! Lens Gripper 전진/후진 센서
	bool LensMotorGripCheck(bool flag, bool waitFlag = true);


	//! pcb Grip 전진/후진
	bool LensLift(bool flag, bool waitFlag = true);
	//! Lens Lift 상승/하강 센서
	bool LensLiftCheck(bool flag, bool waitFlag = true);

	//! PCB 소켓 감지 센서
	bool LensOnCheck(bool flag, bool waitFlag = true);

	//! PCB Cover 전진/후진
	bool PCBPush(bool flag, bool waitFlag = true);		//-- 사용안함(컨셉 변경)
														//! PCB Cover 전진/후진 센서
	bool PCBPushCheck(bool flag, bool waitFlag = true);	//-- 사용안함(컨셉 변경)

	bool PCBCoverCloseCheck(bool flag, bool waitFlag = true);	//PCB 커버 클립형식 감지센서 T=닫힘확인, F=열림확인


	bool PCBDark(bool flag, bool waitFlag = true);					//! PCB Dark 상승/하강
	bool PCBDarkCheck(bool flag, bool waitFlag = true);				//! PCB Dark 상승/하강 센서

																	//! PCB 흡착/탈착
	bool PCBvaccumOn(int flag, bool waitFlag = true);				// 0:OFF, 1:흡착, 2:탈착..
																	//! PCB 흡착 센서
	bool PCBvaccumOnCheck(bool flag, bool waitFlag = true);			// 흡착만 확인 가능..


	bool BackLightOn(bool flag, bool waitFlag = true);				//! 배사 조명 하강/상승
	bool BackLightOnCheck(bool flag, bool waitFlag = true);			//! 배사 조명 하강/상승 센서 확인

																	//! Start P/B 스위치 상태
	bool StartPBOnCheck(bool flag, bool waitFlag = true);
	bool StartPBLampOn(bool flag);

	//! Door Open/Close
	bool DoorPBOnCheck(bool flag, bool waitFlag = true);
	bool DoorPBLampOn(bool flag);
	bool DoorLift(bool flag, bool waitflag = true);
	bool DoorLiftOnCheck(bool flag, bool waitflag = true);

	//! 전면 도어 센서(커튼)
	bool LightCurtainOnCheck(bool flag, bool waitFlag = true);

	//! 도포
	bool EpoxyDischargeOn(bool flag, bool waitFlag = true);			//Dispence 토출 On/Off 
	bool EpoxyDischargeOnCheck(bool flag, bool waitFlag = true);	//Dispence 토출중 Check

																	//! 20150603 도포 I/O 추가
	bool EpoxyDischargeOn2(bool flag, bool waitFlag = true);			//Dispence 토출 On/Off 
	bool EpoxyDischargeOnCheck2(bool flag, bool waitFlag = true);	//Dispence 토출중 Check

	bool UVTrigger(bool flag, bool waitFlag = true);
	bool UVCheck(bool flag, bool waitFlag = true);

	int SensorContactCheck();

	void setAlarm(int AlarmNo);			//0: 알람 + Red Lamp On 1: Yellow Lamp 2: Green Lamp

	void SetLampOn(int iType);			//enum LAMP_NO { ALARM_ON, ALARM_OFF, AUTO_STOP, AUTO_RUN};
	void SetBuzzer(bool flag, int iType);

	bool PcbGrip(bool flag, bool waitFlag = true);			//PCBGRIP
	bool PcbGripCheck(bool flag, bool waitFlag = true);			//PCBUNGRIP

	bool CamLaserClinder(bool flag, bool waitFlag = true);					//! PCB Dark 상승/하강
	bool CamLaserClinderCheck(bool flag, bool waitFlag = true);				//! PCB Dark 상승/하강 센서

	bool VacuumSol(bool flag, bool waitFlag = true); //! Vacuum 파기

	bool Relay(bool flag, bool waitFlag = true); //! 릴레이
	
public:

	bool LensVacuumOn(bool flag);

};
