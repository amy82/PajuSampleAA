#ifndef __INSPECTION_ERROR_CODE_H__
#define __INSPECTION_ERROR_CODE_H__

//////////////////////////////////////////////////////////////////////////
//응답 코드(A): 코드 P의 응답 코드(A)
#define A_READY				00	//정상 (준비완료)
#define A_ERROR				01	//장비 에러
#define A_NOT_HOME			02  //home 상태가 필요한 경우
#define A_WORKING			03  //작업중
#define A_SEARCH_HOME		04  //home 동작중

//////////////////////////////////////////////////////////////////////////
//명령 코드(T): Handler -> Tester
#define T_STANDBY			00
#define T_START_01			01
#define T_START_02			02
#define T_STOP				20
#define T_SKIP				21
#define T_HOME				22
#define T_EMERGENCY			23


//응답 코드 (R): 명령코드 T의 응답 코드(R), Tester->Hander

// manage code

#define R_RESULT_SOCKET_OPENED			(-2)

#define R_RESULT_NONE					(-1)

// result code
#define R_RESULT_STOP					0	//사용자에 의한 stop
#define R_RESULT_PASS					1	//양품
#define R_RESULT_FAIL					2	//불량
#define R_COMMAND_COMPLETE				3	//명령에 대한 완료(home, stop, emergency등)
#define R_ERROR_BOARD					4
#define R_ERROR_MACHINE_SETUP			5
#define R_ERROR_CHECK_SPEC				6
#define R_ERROR_NOT_CONNECT				7	// 연결안됨(TCP)
#define R_ERROR_EJECT_MODULE			8	// 모듈제거
#define R_ERROR_NONETARGET				9	// 자재없음.
#define R_ERROR_VISION					10  // Vision fail
#define R_ERROR_TIME_OUT				11
#define R_ERROR_NOT_HOME				12	//

#define R_ERROR_CANNOTDO				14  // 어떤 원인으로 인해 test진행 할 수 없는 경우
#define R_ERROR_LASER					15	// Laser error
#define R_RESULT_NO_OPERATOR_NAME		16
#define R_RESULT_LOTNAME_ISNOT_FULL		17

#define R_ERROR_VISION_EPOXY			18  // Epoxy Dispensing error from VISION
#define R_ERROR_TCP						19  // TCP error
#define R_FAIL_I2C						20	//device setting error
#define R_FAIL_CAPTURE					21	//image capture error
#define R_FAIL_NOISE					22
#define R_FAIL_BLIGHTNESS				23
#define R_FAIL_COLOR_PATTERN			24
#define R_FAIL_BARCODE					25
#define R_ERROR_PROCESS_SKIP			26
#define R_FAIL_COLOR_REPRODUCTION		27
#define R_FAIL_LENS_SHADING				28


//////////////////////////////////////////////////////////////////////////
// Please add your inspection error code under 30.
// inspection error code range is from 30 to 99

#define R_FAIL_VCM_I2C					40
#define R_FAIL_AF_RESOLUTION			41
#define R_FAIL_AF_RESOLUTION_MACRO		42
#define R_FAIL_AF_TILT					43
#define R_FAIL_AF_ROTATION				44
#define R_FAIL_AF_DFOV					45
#define R_FAIL_NOT_MOVING_VCM			46
#define R_FAIL_AF_WRONG_CHART			47
#define R_FAIL_AF_SFR_DELTA				48
#define R_FAIL_GAGE_SFR					49

#define R_FAIL_FOCUSING					50
#define R_FAIL_FOCUSING_TIMEOUT			51

// for Auto Focusing
#define R_FAIL_DFOV_FAIL				53	//
#define R_FAIL_SAFETY_DETECTION			56

#define R_FAIL_SNR						58
#define R_FAIL_PATTERN_NOISE			59

#define R_FAIL_BLACK_SPOT				60
#define R_FAIL_STAIN					61


#define R_FAIL_COLORCAL					63
#define R_FAIL_COLOR_SENSITIVITY        64
#define R_FAIL_COLOR_SHADING			65
#define R_FAIL_VIGNETTING_YMEAN			66
#define R_FAIL_VIGNETTING_DSTRIPE		67
#define R_FAIL_COLOR_UNIFORMITY			68
#define R_FAIL_GOLDEN_SHADING_DEV		69


#define R_FAIL_OIS						70
#define R_FAIL_GRAVITY_CAL				71
#define R_FAIL_VCM						72
#define R_FAIL_OIS_HYSTERESIS			73

#define R_FAIL_VCM_SENSITIVITY			75
#define R_FAIL_VCM_LINEARITY			76
#define R_FAIL_VCM_HYSTERESIS			77
#define R_FAIL_VCM_MAXSTROKE			78
#define R_FAIL_VCM_STARTCURRENT			79

#define R_FAIL_DARK_TEST				80
#define R_FAIL_DECENTER					81

#define R_FAIL_SPC_CALCULATION			82	// Shield Pixel Correction
#define R_FAIL_SPC_VERIFICATION			83	// Shield Pixel Correction
#define R_FAIL_DCC_CALCULATION			84	// Defocus Conversion Coefficient
#define R_FAIL_DCC_VERIFICATION			85	// Defocus Conversion Coefficient
#define R_FAIL_SPC_LOADING				86

#define R_FAIL_GET_TEMPERATURE			87

#define R_FAIL_LIGHT_CAL_TIME		    91
#define R_FAIL_LIGHT_CAL_FACTOR         92
#define R_FAIL_WRONG_GOLDEN_MODUE       93
#define R_FAIL_INIT_LIGHT_CAL           94
#define R_FAIL_SHADING_DEV_EEPROM		95
#define R_FAIL_RELATIVEILLUMINATION		96
#define R_FAIL_HALL_CALIBRATION			97
#define R_RESULT_SENSORID_FOUND			98
#define R_FAIL_CHECK_SENSORID			99

//////////////////////////////////////////////////////////////////////////
// DO NOT USE over 100 code
// THIS CODE are for EEPROM
#define R_FAIL_EEPROM_READ				100
#define R_FAIL_EEPROM_WRITE				101
#define R_FAIL_EEPROM_CHECKSUM			102
#define R_FAIL_EEPROM_VERIFY			103
#define R_FAIL_EEPROM_SPEC_OUT			104
#define R_FAIL_EEPROM_UPDATE			105
#define R_FAIL_EEPROM_NOT_EMPTY			106


// THIS CODE are for Certification
#define R_FAIL_CERTIFICATION			300


#define R_FAIL_OTP_READ					1001
#define R_FAIL_OTP_WRITE				1002
#define R_FAIL_OTP_VERIFY				1003
#define R_FAIL_OTP_UPDATE				1004
#define R_FAIL_OTP_NOT_EMPTY			1005
#define R_FAIL_OTP_NO_EMPTY_BANK		1006
#define R_FAIL_OTP_SPEC_OUT				1007

#endif /* __INSPECTION_ERROR_CODE_H__ */