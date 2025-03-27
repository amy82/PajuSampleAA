

#include "stdafx.h"
#include "DioControl.h"

CDioControl::CDioControl()
{	
}

bool CDioControl::OcSlinderMove(bool flag, bool waitFlag)
{
	int moduleNo = 2;
	int channelNo = 1;

	g_CriOutDio.Lock();

	int outVal = curOutDioByte[moduleNo][channelNo];

	if (flag)
	{
		outVal = outVal | DIO_OUT_OCLIGHT_FOR;
		outVal = outVal & ~DIO_OUT_OCLIGHT_BACK;
	}
	else
	{
		outVal = outVal & ~DIO_OUT_OCLIGHT_FOR;
		outVal = outVal | DIO_OUT_OCLIGHT_BACK;
	}
	motor.OutDIO(moduleNo, channelNo, outVal);

	g_CriOutDio.Unlock();


#ifndef		ON_LINE_DIO
	return true;
#endif


	if (waitFlag)
	{
		if (!OcSlinderCheck(flag, waitFlag))
		{
			return false;
		}
	}

	return true;
}
bool CDioControl::OcSlinderCheck(bool flag, bool waitFlag)
{
	if (flag)
	{
		if (curInDio[1] & DIO_IN_OCLIGHT_FOR)
		{
			if (!(curInDio[1] & DIO_IN_OCLIGHT_BACK))
				return true;
		}
	}
	else
	{
		if (curInDio[1] & DIO_IN_OCLIGHT_FOR)
		{
			if (!(curInDio[1] & DIO_IN_OCLIGHT_BACK))
				return true;
		}
	}

#ifndef		ON_LINE_DIO
	return true;
#endif

	if (!waitFlag)
		return false;

	double ep = myTimer(true);

	while (waitFlag)
	{
		if (flag)
		{
			if (curInDio[1] & DIO_IN_OCLIGHT_FOR)
			{
				if (!(curInDio[1] & DIO_IN_OCLIGHT_BACK))
					break;
			}
		}
		else
		{
			if (curInDio[1] & DIO_IN_OCLIGHT_BACK)
			{
				if (!(curInDio[1] & DIO_IN_OCLIGHT_FOR))
					break;
			}
		}

		if (myTimer(true) - ep>IO_DELAY_TIME)
		{
			CString tmpStr;
			CString sTemp;
			sLangChange.LoadStringA(IDS_STRING669);
			sTemp.LoadString(IDS_STRING672);
			if (flag)			tmpStr.Format("OC LIGHT 전진 동작 시간 초과");	//Lens Grip 전진 동작 시간 초과
			else				tmpStr.Format("OC LIGHT 전진 동작 시간 초과");	//Lens Grip 후진 동작 시간 초과

			errMsg2(Task.AutoFlag, tmpStr);

			return false;
		}


		Sleep(1);
	}

	return true;
}
//! UV부 연기 탈취
bool CDioControl::UVGasClean(bool flag)
{
	//int moduleNo = 0;
	//int channelNo = 2;

	//g_CriOutDio.Lock();

	//int outVal = curOutDioByte[moduleNo][channelNo];

	//if (flag)
	//	outVal = outVal | DIO_OUT_SPOT_UV_CLEAN_GAS;
	//else
	//	outVal = outVal & (~DIO_OUT_SPOT_UV_CLEAN_GAS);

	//motor.OutDIO(moduleNo, channelNo, outVal);

	//g_CriOutDio.Unlock();


	return true;
}


//! Lens Stage Gripper 전진/후진
bool CDioControl::HolderGrip(bool flag, bool waitFlag)
{
	int moduleNo = 2;
	int channelNo = 0;

	g_CriOutDio.Lock();

	int outVal = curOutDioByte[moduleNo][channelNo];

	if (flag)
	{
		outVal = outVal | DIO_OUT_PCBSTAGE_GRIP_FOR;
		outVal = outVal & ~DIO_OUT_PCBSTAGE_GRIP_BACK;
	}
	else
	{
		outVal = outVal & ~DIO_OUT_PCBSTAGE_GRIP_FOR;
		outVal = outVal | DIO_OUT_PCBSTAGE_GRIP_BACK;
	}
	motor.OutDIO(moduleNo, channelNo, outVal);

	g_CriOutDio.Unlock();


#ifndef		ON_LINE_DIO
	return true;
#endif


	if (waitFlag)
	{
		if (!HolderGripCheck(flag, waitFlag))
		{
			return false;
		}
	}

	return true;
}

//! Lens Gripper 전진/후진 센서
bool CDioControl::HolderGripCheck(bool flag, bool waitFlag)
{
	if (flag)
	{
		if (curInDio[1] & DIO_IN_PCBSTAGE_GRIP_FOR)
		{
			if (!(curInDio[1] & DIO_IN_PCBSTAGE_GRIP_BACK))
				return true;
		}
	}
	else
	{
		if (curInDio[1] & DIO_IN_PCBSTAGE_GRIP_BACK)
		{
			if (!(curInDio[1] & DIO_IN_PCBSTAGE_GRIP_FOR))
				return true;
		}
	}

#ifndef		ON_LINE_DIO
	return true;
#endif

	if (!waitFlag)
		return false;

	double ep = myTimer(true);

	while (waitFlag)
	{
		if (flag)
		{
			if (curInDio[1] & DIO_IN_PCBSTAGE_GRIP_FOR)
			{
				if (!(curInDio[1] & DIO_IN_PCBSTAGE_GRIP_BACK))
					break;
			}
		}
		else
		{
			if (curInDio[1] & DIO_IN_PCBSTAGE_GRIP_BACK)
			{
				if (!(curInDio[1] & DIO_IN_PCBSTAGE_GRIP_FOR))
					break;
			}
		}

		if (myTimer(true) - ep>IO_DELAY_TIME)
		{
			CString tmpStr;
			CString sTemp;
			sLangChange.LoadStringA(IDS_STRING669);
			sTemp.LoadString(IDS_STRING672);
			if (flag)			tmpStr.Format("Holder Grip 전진 동작 시간 초과");	//Lens Grip 전진 동작 시간 초과
			else				tmpStr.Format("Holder Grip 후진 동작 시간 초과");		//Lens Grip 후진 동작 시간 초과

			errMsg2(Task.AutoFlag, tmpStr);

			return false;
		}



		Sleep(1);

		Sleep(1);
	}

	return true;
}
bool CDioControl::CamLaserSlinderMove(bool flag, bool waitFlag)
{
#if (____AA_WAY == LENS_TILT_AA)
	if (flag)
	{
		return false;
	}

#endif

	int moduleNo = 2;
	int channelNo = 1;

	g_CriOutDio.Lock();

	int outVal = curOutDioByte[moduleNo][channelNo];

	if (flag)
	{
		outVal = outVal | DIO_OUT_LASER_CAM_FOR;
		outVal = outVal & ~DIO_OUT_LASER_CAM_BACK;
	}
	else
	{
		outVal = outVal & ~DIO_OUT_LASER_CAM_FOR;
		outVal = outVal | DIO_OUT_LASER_CAM_BACK;
	}
	motor.OutDIO(moduleNo, channelNo, outVal);

	g_CriOutDio.Unlock();


#ifndef		ON_LINE_DIO
	return true;
#endif


	if (waitFlag)
	{
		if (!CamLaserSlinderCheck(flag, waitFlag))
		{
			return false;
		}
	}

	return true;
}
bool CDioControl::CamLaserSlinderCheck(bool flag, bool waitFlag)
{
	if (flag)
	{
		if (curInDio[1] & DIO_IN_LASER_CAM_FOR)
		{
			if (!(curInDio[1] & DIO_IN_LASER_CAM_DOWN))
				return true;
		}
	}
	else
	{
		if (curInDio[1] & DIO_IN_LASER_CAM_DOWN)
		{
			if (!(curInDio[1] & DIO_IN_LASER_CAM_FOR))
				return true;
		}
	}

#ifndef		ON_LINE_DIO
	return true;
#endif

	if (!waitFlag)
		return false;

	double ep = myTimer(true);

	while (waitFlag)
	{
		if (flag)
		{
			if (curInDio[1] & DIO_IN_LASER_CAM_FOR)
			{
				if (!(curInDio[1] & DIO_IN_LASER_CAM_DOWN))
					break;
			}
		}
		else
		{
			if (curInDio[1] & DIO_IN_LASER_CAM_DOWN)
			{
				if (!(curInDio[1] & DIO_IN_LASER_CAM_FOR))
					break;
			}
		}

		if (myTimer(true) - ep>IO_DELAY_TIME)
		{
			CString tmpStr = "";
			if (flag)			tmpStr.Format("Laser/Cam 전진 동작 시간 초과");	//Lens Grip 전진 동작 시간 초과
			else				tmpStr.Format("Laser/Cam 후진 동작 시간 초과");	//Lens Grip 후진 동작 시간 초과

			errMsg2(Task.AutoFlag, tmpStr);

			return false;
		}


		Sleep(1);
	}

	return true;
}

//! Lens 흡착 센서
// 흡착만 확인 가능..
bool CDioControl::LensOnCheck(bool flag, bool waitFlag/*=true*/)
{//- B접점
//	if (!flag)
//	{
//		if (curInDio[1] & DIO_IN_LENS_SENSOR)
//			return true;
//	}
//	else
//	{
//		if (!(curInDio[1] & DIO_IN_LENS_SENSOR))
//			return true;
//	}
//
//#ifndef		ON_LINE_DIO
//	return true;
//#endif
//
//	if(!waitFlag)
//		return false;
//
//	double ep = myTimer(true);
//
//	while (waitFlag)
//	{
//		if (!flag)
//		{
//			if (curInDio[1] & DIO_IN_LENS_SENSOR)
//			{
//				break;
//			}
//		}
//
//		if(myTimer(true)-ep>IO_DELAY_TIME)
//		{
//			CString tmpStr;
//
//			sLangChange.LoadStringA(IDS_STRING711);
//			if(flag)			tmpStr.Format(sLangChange);	//LENS 감지 시간 초과
//
//			errMsg2(Task.AutoFlag,tmpStr);
//
//			return false;
//		}
//
//		checkMessage();
//		Sleep(1);
//		checkMessage();
//		Sleep(1);
//		checkMessage();
//	}
	return true;
}


//! PCB 흡착/탈착
bool CDioControl::PCBvaccumOn(int flag, bool waitFlag)		// 0:OFF, 1:흡착, 2:탈착
{
	int moduleNo = 0;
	int channelNo = 0;
	int blowTime = 1000;

	g_CriOutDio.Lock();

	int outVal = curOutDioByte[moduleNo][channelNo];

	if (flag == VACCUM_ON)
	{
		outVal = outVal | DIO_OUT_PCB_VACUUM;
		outVal = outVal & ~DIO_OUT_PCB_VACUUM_OFF;
	}
	else if (flag == VACCUM_BLOW || (flag == VACCUM_BLOW_ON))
	{
		outVal = outVal & ~DIO_OUT_PCB_VACUUM;
		outVal = outVal | DIO_OUT_PCB_VACUUM_OFF;
	}
	else if (flag == VACCUM_OFF)
	{
		outVal = outVal | DIO_OUT_PCB_VACUUM_OFF;
		outVal = outVal & ~DIO_OUT_PCB_VACUUM;
	}

	motor.OutDIO(moduleNo, channelNo, outVal);


	if (flag == VACCUM_BLOW)
	{
		Sleep(blowTime);

		outVal = outVal & ~DIO_OUT_PCB_VACUUM;
		outVal = outVal & ~DIO_OUT_PCB_VACUUM_OFF;

		motor.OutDIO(moduleNo, channelNo, outVal);
	}

	g_CriOutDio.Unlock();


#ifndef		ON_LINE_DIO
	return true;
#endif

	if (waitFlag)
	{
		bool checkFlag = false;

		if (flag == VACCUM_ON)
			checkFlag = true;

		if (!PCBvaccumOnCheck(checkFlag, waitFlag))
		{
			return false;
		}
	}

	return true;
}

//! PCB 흡착 센서
// 흡착만 확인 가능..
bool CDioControl::PCBvaccumOnCheck(bool flag, bool waitFlag)
{
	if (!flag)
	{
		if (!(curInDio[0] & DIO_IN_PCB_VACUUM))
			return true;
		
	}
	else
	{
		if (curInDio[0] & DIO_IN_PCB_VACUUM)
			return true;
	}

#ifndef		ON_LINE_DIO
	return true;
#endif

	if (!waitFlag)
		return false;

	double ep = myTimer(true);

	while (waitFlag)
	{
		if (flag)
		{
			if (!(curInDio[0] & DIO_IN_PCB_VACUUM))
				break;
		}
		else
		{
			if (curInDio[0] & DIO_IN_PCB_VACUUM)
				break;
		}

		if (myTimer(true) - ep>IO_DELAY_TIME)
		{
			CString tmpStr;
			CString sTemp;
			sLangChange.LoadStringA(IDS_STRING1011);
			sTemp.LoadString(IDS_STRING1009);
			if (flag)			tmpStr.Format(sLangChange);	//PCB 흡착 동작 시간 초과
			else				tmpStr.Format(sTemp);	//PCB 탈착 동작 시간 초과

			errMsg2(Task.AutoFlag, tmpStr);

			return false;
		}

		checkMessage();
		Sleep(5);
	}
	return true;
}

//! 배사 조명 전진/후진  => 상승, 하강
bool CDioControl::BackLightOn(bool flag, bool waitFlag)
{
	

//	int moduleNo = 2;
//	int channelNo = 2;
//
//
//	//	if(flag == false )	LightControl.ctrlLedVolume(LIGHT_OC, 0);
//	//	else				LightControl.ctrlLedVolume(LIGHT_OC, model.m_iLedValue[LEDDATA_OC]);
//
//
//
//	g_CriOutDio.Lock();
//
//	int outVal = curOutDioByte[moduleNo][channelNo];
//
//	if (flag == false)
//	{
//		outVal = outVal | DIO_OUT_BACK_LIGHT_FOR;
//		outVal = outVal & ~DIO_OUT_BACK_LIGHT_BACK;
//	}
//	else
//	{
//		outVal = outVal & ~DIO_OUT_BACK_LIGHT_FOR;
//		outVal = outVal | DIO_OUT_BACK_LIGHT_BACK;
//	}
//
//	motor.OutDIO(moduleNo, channelNo, outVal);
//
//	g_CriOutDio.Unlock();
//
//
//#ifndef		ON_LINE_DIO
//	return true;
//#endif
//
//	if (waitFlag)
//	{
//		if (!BackLightOnCheck(flag, waitFlag))
//		{
//			return false;
//		}
//	}

	return true;
}

//! 배사 조명 전진/후진 센서  => 상승 하강. 
bool CDioControl::BackLightOnCheck(bool flag, bool waitFlag)
{
//	if (flag == false)
//	{//상승
//		if (curInDio[1] & DIO_IN_BACK_LIGHT_FOR)
//		{
//			if (!(curInDio[1] & DIO_IN_BACK_LIGHT_BACK))
//				return true;
//		}
//	}
//	else
//	{//하강
//		if (curInDio[1] & DIO_IN_BACK_LIGHT_BACK)
//		{
//			if (!(curInDio[1] & DIO_IN_BACK_LIGHT_FOR))
//				return true;
//		}
//	}
//
//#ifndef		ON_LINE_DIO
//	return true;
//#endif
//
//	if (!waitFlag)
//		return false;
//
//	double ep = myTimer(true);
//
//	while (waitFlag)
//	{
//		if (flag == false)
//		{
//			if (curInDio[1] & DIO_IN_BACK_LIGHT_FOR)
//			{
//				if (!(curInDio[1] & DIO_IN_BACK_LIGHT_BACK))
//					break;
//			}
//		}
//		else
//		{
//			if (curInDio[1] & DIO_IN_BACK_LIGHT_BACK)
//			{
//				if (!(curInDio[1] & DIO_IN_BACK_LIGHT_FOR))
//					break;
//			}
//		}
//
//		if (myTimer(true) - ep > IO_DELAY_TIME)
//		{
//			CString tmpStr;
//			CString sTemp;
//			sLangChange.LoadStringA(IDS_STRING407);
//			sTemp.LoadString(IDS_STRING410);
//			if (flag)			tmpStr.Format(sLangChange);	//Back Light 전진 시간 초과
//			else				tmpStr.Format(sTemp);	//Back Light 후진 시간 초과
//
//			errMsg2(Task.AutoFlag, tmpStr);
//
//			return false;
//		}
//
//		checkMessage();
//		Sleep(5);
//	}
	return true;
}

void CDioControl::setAlarm(int AlarmNo)			//0: 알람 + Red Lamp On 1: Yellow Lamp 2: Green Lamp
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	CString sLog = "";

	if (AlarmNo == ALARM_ON)
	{
		SetLampOn(ALARM_ON);
		SetBuzzer(true, AlarmNo);
		pFrame->m_labelTitle.SetBkColor(M_COLOR_RED);
	}
	else if (AlarmNo == ALARM_OFF)
	{
		SetLampOn(ALARM_OFF);
		SetBuzzer(false, AlarmNo);
		pFrame->m_labelTitle.SetBkColor(M_COLOR_BLUE);
	}
	else if (AlarmNo == AUTO_STOP)
	{
		SetLampOn(AUTO_STOP);
		SetBuzzer(false, AlarmNo);
		pFrame->m_labelTitle.SetBkColor(M_COLOR_BLUE);
	}
	else if (AlarmNo == AUTO_RUN)
	{
		SetLampOn(AUTO_RUN);
		//SetBuzzer(false, AlarmNo);
		pFrame->m_labelTitle.SetBkColor(M_COLOR_BLUE);
		//SetBuzzer(true, AlarmNo);
		//pFrame->m_labelTitle.SetBkColor(M_COLOR_BLUE);
		//Sleep(100);
		//SetBuzzer(false, AlarmNo);
	}

	pFrame->m_labelTitle.Invalidate();
}
bool CDioControl::ContiTailGrip(bool flag, bool waitFlag)
{
	int moduleNo = 2;
	int channelNo = 1;

	g_CriOutDio.Lock();

	int outVal = curOutDioByte[moduleNo][channelNo];

	if (flag)
	{
		outVal = outVal | DIO_OUT_LASER_CAM_FOR;
		outVal = outVal & ~DIO_OUT_LASER_CAM_BACK;
	}
	else
	{
		outVal = outVal & ~DIO_OUT_LASER_CAM_FOR;
		outVal = outVal | DIO_OUT_LASER_CAM_BACK;
	}
	motor.OutDIO(moduleNo, channelNo, outVal);

	g_CriOutDio.Unlock();


#ifndef		ON_LINE_DIO
	return true;
#endif


	if (waitFlag)
	{
		if (!ContiTailGripCheck(flag, waitFlag))
		{
			return false;
		}
	}

	return true;
}
bool CDioControl::ContiTailGripCheck(bool flag, bool waitFlag)
{
	if (flag)
	{
		if (curInDio[1] & DIO_IN_LASER_CAM_FOR)
		{
			if (!(curInDio[1] & DIO_IN_LASER_CAM_DOWN))
				return true;
		}
	}
	else
	{
		if (curInDio[1] & DIO_IN_LASER_CAM_DOWN)
		{
			if (!(curInDio[1] & DIO_IN_LASER_CAM_FOR))
				return true;
		}
	}

#ifndef		ON_LINE_DIO
	return true;
#endif

	if (!waitFlag)
		return false;

	double ep = myTimer(true);

	while (waitFlag)
	{
		if (flag)
		{
			if (curInDio[1] & DIO_IN_LASER_CAM_FOR)
			{
				if (!(curInDio[1] & DIO_IN_LASER_CAM_DOWN))
					break;
			}
		}
		else
		{
			if (curInDio[1] & DIO_IN_LASER_CAM_DOWN)
			{
				if (!(curInDio[1] & DIO_IN_LASER_CAM_FOR))
					break;
			}
		}

		if (myTimer(true) - ep>IO_DELAY_TIME)
		{
			CString tmpStr = "";
			if (flag)			tmpStr.Format("Laser/Cam 전진 동작 시간 초과");	//Lens Grip 전진 동작 시간 초과
			else				tmpStr.Format("Laser/Cam 후진 동작 시간 초과");	//Lens Grip 후진 동작 시간 초과

			errMsg2(Task.AutoFlag, tmpStr);

			return false;
		}


		Sleep(1);
	}

	return true;
}

//! Lens Gripper 전진/후진
bool CDioControl::LensMotorGrip(bool flag, bool waitFlag)
{
	int moduleNo = 2;
	int channelNo = 0;

	g_CriOutDio.Lock();

	int outVal = curOutDioByte[moduleNo][channelNo];

	if (flag)
	{
		outVal = outVal | DIO_OUT_LENS_GRIP_FOR;
		outVal = outVal & ~DIO_OUT_LENS_GRIP_BACK;
	}
	else
	{
		outVal = outVal & ~DIO_OUT_LENS_GRIP_FOR;
		outVal = outVal | DIO_OUT_LENS_GRIP_BACK;
	}
	motor.OutDIO(moduleNo, channelNo, outVal);

	g_CriOutDio.Unlock();


#ifndef		ON_LINE_DIO
	return true;
#endif


	if (waitFlag)
	{
		if (!LensMotorGripCheck(flag, waitFlag))
		{
			return false;
		}
	}

	return true;
}

//! Lens Gripper 전진/후진 센서
bool CDioControl::LensMotorGripCheck(bool flag, bool waitFlag)
{
	if (flag)
	{
		if (curInDio[1] & DIO_IN_LENS_GRIP_FOR)
		{
			if (!(curInDio[1] & DIO_IN_LENS_GRIP_BACK))
				return true;
		}
	}
	else
	{
		if (curInDio[1] & DIO_IN_LENS_GRIP_BACK)
		{
			if (!(curInDio[1] & DIO_IN_LENS_GRIP_FOR))
				return true;
		}
	}

#ifndef		ON_LINE_DIO
	return true;
#endif

	if (!waitFlag)
		return false;

	double ep = myTimer(true);

	while (waitFlag)
	{
		if (flag)
		{
			if (curInDio[1] & DIO_IN_LENS_GRIP_FOR)
			{
				if (!(curInDio[1] & DIO_IN_LENS_GRIP_BACK))
					break;
			}
		}
		else
		{
			if (curInDio[1] & DIO_IN_LENS_GRIP_BACK)
			{
				if (!(curInDio[1] & DIO_IN_LENS_GRIP_FOR))
					break;
			}
		}

		if (myTimer(true) - ep>IO_DELAY_TIME)
		{
			CString tmpStr;
			CString sTemp;
			sLangChange.LoadStringA(IDS_STRING669);
			sTemp.LoadString(IDS_STRING672);
			if (flag)			tmpStr.Format(sLangChange);	//Lens Grip 전진 동작 시간 초과
			else				tmpStr.Format(sTemp);	//Lens Grip 후진 동작 시간 초과

			errMsg2(Task.AutoFlag, tmpStr);

			return false;
		}


		checkMessage();
		Sleep(1);
		checkMessage();
		Sleep(1);
		checkMessage();
	}

	return true;
}

bool CDioControl::PCBCoverCloseCheck(bool flag, bool waitFlag)
{
	if (flag)
	{
		if (!(curInDio[1] & DIO_IN_PCB_SOCKET_CLOSE))//닫힘 상태 확인 완료
		{
			return true;
		}
	}
	else
	{
		if (curInDio[1] & DIO_IN_PCB_SOCKET_CLOSE)//열림 상태 확인 완료
		{
			return true;
		}
	}

#ifndef		ON_LINE_DIO
	return true;
#endif

	if (!waitFlag)
		return false;

	double ep = myTimer(true);

	while (waitFlag)
	{
		if (flag)
		{
			if (!(curInDio[1] & DIO_IN_PCB_SOCKET_CLOSE))
			{
				break;
			}
		}
		else
		{
			if (curInDio[1] & DIO_IN_PCB_SOCKET_CLOSE)
			{
				break;
			}
		}

		if (myTimer(true) - ep > IO_DELAY_TIME)
		{
			CString tmpStr;
			CString sTemp;
			sLangChange.LoadStringA(IDS_STRING1452);
			sTemp.LoadString(IDS_STRING916);
			if (flag)			tmpStr.Format(sLangChange);	//PCB Cover 소켓 닫힘 센서 확인 시간 초과
			else				tmpStr.Format(sTemp);	//PCB Cover 소켓 열림 센서 확인 시간 초과
			errMsg2(Task.AutoFlag, tmpStr);

			return false;
		}

		checkMessage();
		Sleep(1);
		checkMessage();
		Sleep(1);
		checkMessage();
	}

	return true;
}
//! PCB Dark 상승/하강
bool CDioControl::PCBDark(bool flag, bool waitFlag)
{
	int moduleNo = 2;
	int channelNo = 1;


	g_CriOutDio.Lock();

	int outVal = curOutDioByte[moduleNo][channelNo];

	if (flag)
	{
		outVal = outVal | DIO_OUT_LASER_CAM_BACK;
		outVal = outVal & ~DIO_OUT_LASER_CAM_BACK;
	}
	else
	{
		outVal = outVal & ~DIO_OUT_LASER_CAM_BACK;
		outVal = outVal | DIO_OUT_LASER_CAM_BACK;
	}
	motor.OutDIO(moduleNo, channelNo, outVal);

	g_CriOutDio.Unlock();

#ifndef		ON_LINE_DIO
	return true;
#endif

	if (waitFlag)
	{
		if (!PCBDarkCheck(flag, waitFlag))
		{
			return false;
		}
	}

	return true;
}

//! PCB Dark 상승/하강 센서
bool CDioControl::PCBDarkCheck(bool flag, bool waitFlag)
{

//	if (flag)
//	{
//		if (curInDio[1] & DIO_IN_DARK_LIFT_UP)
//		{
//			if (!(curInDio[1] & DIO_IN_DARK_LIFT_DOWN))
//				return true;
//		}
//	}
//	else
//	{
//		if (curInDio[1] & DIO_IN_DARK_LIFT_DOWN)
//		{
//			if (!(curInDio[1] & DIO_IN_DARK_LIFT_UP))
//				return true;
//		}
//	}
//
//#ifndef		ON_LINE_DIO
//	return true;
//#endif
//
//	if (!waitFlag)
//		return false;
//
//	double ep = myTimer(true);
//
//	while (waitFlag)
//	{
//		if (flag)
//		{
//			if (curInDio[1] & DIO_IN_DARK_LIFT_UP)
//			{
//				if (!(curInDio[1] & DIO_IN_DARK_LIFT_DOWN))
//					break;
//			}
//		}
//		else
//		{
//			if (curInDio[1] & DIO_IN_DARK_LIFT_DOWN)
//			{
//				if (!(curInDio[1] & DIO_IN_DARK_LIFT_UP))
//					break;
//			}
//		}
//
//		if (myTimer(true) - ep>IO_DELAY_TIME)
//		{
//			CString tmpStr;
//			CString sTemp;
//			sLangChange.LoadStringA(IDS_STRING921);
//			sTemp.LoadString(IDS_STRING929);
//			if (flag)			tmpStr.Format(sLangChange);	//PCB Dark 상승 시간 초과
//			else				tmpStr.Format(sTemp);	//PCB Dark 하강 시간 초과
//			errMsg2(Task.AutoFlag, tmpStr);
//
//			return false;
//		}
//
//		checkMessage();
//		Sleep(1);
//		checkMessage();
//		Sleep(1);
//		checkMessage();
//	}

	return true;
}
//! Lens Stage Gripper 전진/후진
bool CDioControl::LensLift(bool flag, bool waitFlag)
{
	/*int moduleNo = 2;
	int channelNo = 0;

	g_CriOutDio.Lock();

	int outVal = curOutDioByte[moduleNo][channelNo];

	if (flag)
	{
		outVal = outVal | DIO_OUT_LENS_ALIGN_CHUCK_FOR;
		outVal = outVal & ~DIO_OUT_LENS_ALIGN_CHUCK_BACK;
	}
	else
	{
		outVal = outVal & ~DIO_OUT_LENS_ALIGN_CHUCK_FOR;
		outVal = outVal | DIO_OUT_LENS_ALIGN_CHUCK_BACK;
	}
	motor.OutDIO(moduleNo, channelNo, outVal);

	g_CriOutDio.Unlock();


#ifndef		ON_LINE_DIO
	return true;
#endif


	if (waitFlag)
	{
		if (!LensLiftCheck(flag, waitFlag))
		{
			return false;
		}
	}
*/
	return true;
}

//! PCB Cover 전진/후진
bool CDioControl::PCBPush(bool flag, bool waitFlag)
{
//	if (PcbGripCheck(false, false) == true)
//	{
//		CString sTemp;
//		//sLangChange.LoadStringA(IDS_STRING1026);	//PCB부 커버 소켓이 열려 있습니다.
//		sTemp.Format(_T("DO NOT MOVE!! PCB GRIP OUT STATE"));
//		delayMsg(sTemp, 3000, M_COLOR_DARK_GREEN);
//		return false;
//	}
//
//	int moduleNo = 2;
//	int channelNo = 0;
//
//	g_CriOutDio.Lock();
//
//	int outVal = curOutDioByte[moduleNo][channelNo];
//
//	if (flag)
//	{
//		outVal = outVal | DIO_OUT_PCB_PUSH_UP;
//		outVal = outVal & ~DIO_OUT_PCB_PUSH_DOWN;
//	}
//	else
//	{
//		outVal = outVal & ~DIO_OUT_PCB_PUSH_UP;
//		outVal = outVal | DIO_OUT_PCB_PUSH_DOWN;
//	}
//	motor.OutDIO(moduleNo, channelNo, outVal);
//
//	g_CriOutDio.Unlock();
//
//#ifndef		ON_LINE_DIO
//	return true;
//#endif
//
//	if (waitFlag)
//	{
//		if (!PCBPushCheck(flag, waitFlag))
//		{
//			return false;
//		}
//	}
//
	return true;
}

//! PCB Cover 전진/후진 센서
bool CDioControl::PCBPushCheck(bool flag, bool waitFlag)
{
//	if (flag)
//	{
//		if (curInDio[1] & DIO_IN_PCB_PUSH_UP)
//		{
//			if (!(curInDio[1] & DIO_IN_PCB_PUSH_DOWN))
//				return true;
//		}
//	}
//	else
//	{
//		if (curInDio[1] & DIO_IN_PCB_PUSH_DOWN)
//		{
//			if (!(curInDio[1] & DIO_IN_PCB_PUSH_UP))
//				return true;
//		}
//	}
//
//#ifndef		ON_LINE_DIO
//	return true;
//#endif
//
//	if (!waitFlag)
//		return false;
//
//	double ep = myTimer(true);
//
//	while (waitFlag)
//	{
//		if (flag)
//		{
//			if (curInDio[1] & DIO_IN_PCB_PUSH_UP)
//			{
//				if (!(curInDio[1] & DIO_IN_PCB_PUSH_DOWN))
//					break;
//			}
//		}
//		else
//		{
//			if (curInDio[1] & DIO_IN_PCB_PUSH_DOWN)
//			{
//				if (!(curInDio[1] & DIO_IN_PCB_PUSH_UP))
//					break;
//			}
//		}
//
//		if (myTimer(true) - ep>IO_DELAY_TIME)
//		{
//			CString tmpStr;
//			CString sTemp;
//			sLangChange.LoadStringA(IDS_STRING917);
//			sTemp.LoadString(IDS_STRING918);
//			if (flag)			tmpStr.Format(sLangChange);	//PCB Cover 전진 시간 초과
//			else				tmpStr.Format(sTemp);  //PCB Cover 후진 시간 초과
//			errMsg2(Task.AutoFlag, tmpStr);
//
//			return false;
//		}
//
//		checkMessage();
//		Sleep(1);
//		checkMessage();
//		Sleep(1);
//		checkMessage();
//	}

	return true;
}
bool CDioControl::LensLiftCheck(bool flag, bool waitFlag)
{
//	if (flag)
//	{
//		if (curInDio[1] & DIO_IN_LENS_ALIGN_CHUCK_FOR)
//		{
//			if (!(curInDio[1] & DIO_IN_LENS_ALIGN_CHUCK_BACK))
//				return true;
//		}
//	}
//	else
//	{
//		if (curInDio[1] & DIO_IN_LENS_ALIGN_CHUCK_BACK)
//		{
//			if (!(curInDio[1] & DIO_IN_LENS_ALIGN_CHUCK_FOR))
//				return true;
//		}
//	}
//
//#ifndef		ON_LINE_DIO
//	return true;
//#endif
//
//	if (!waitFlag)
//		return false;
//
//	double ep = myTimer(true);
//
//	while (waitFlag)
//	{
//		if (flag)
//		{
//			if (curInDio[1] & DIO_IN_LENS_ALIGN_CHUCK_FOR)
//			{
//				if (!(curInDio[1] & DIO_IN_LENS_ALIGN_CHUCK_BACK))
//					break;
//			}
//		}
//		else
//		{
//			if (curInDio[1] & DIO_IN_LENS_ALIGN_CHUCK_BACK)
//			{
//				if (!(curInDio[1] & DIO_IN_LENS_ALIGN_CHUCK_FOR))
//					break;
//			}
//		}
//
//		if (myTimer(true) - ep>IO_DELAY_TIME)
//		{
//			CString tmpStr;
//			CString sTemp;
//			sLangChange.LoadStringA(IDS_STRING678);
//			sTemp.LoadString(IDS_STRING680);
//			if (flag)			tmpStr.Format(sLangChange);	//Lens Lift 상승 동작 시간 초과
//			else				tmpStr.Format(sTemp);	//Lens Lift 하강 동작 시간 초과
//
//			errMsg2(Task.AutoFlag, tmpStr);
//
//			return false;
//		}
//
//		Sleep(1);
//	}

	return true;
}
//! START P/B 버튼 Check
bool CDioControl::StartPBOnCheck(bool flag, bool waitFlag)
{
	if (flag)
	{
		if (curInDio[1] & DIO_IN_START) {
			StartPBLampOn(true);
			return true;
		}
	}
	else
	{
		if (!(curInDio[1] & DIO_IN_START)) {
			StartPBLampOn(false);
			return true;
		}
	}

	if (!waitFlag)	return false;

	double ep = myTimer(true);
	while (waitFlag)
	{
		if (flag)
		{
			if (curInDio[1] & DIO_IN_START) {
				StartPBLampOn(true);
				break;
			}
		}
		else
		{
			if (!(curInDio[1] & DIO_IN_START)) {
				StartPBLampOn(false);
				break;
			}
		}

		if (myTimer(true) - ep > IO_DELAY_TIME)
		{
			//CString tmpStr;
			//if(flag)			tmpStr.Format("Start 스위치 ON 시간 초과");
			//else				tmpStr.Format("Start 스위치 OFF 시간 초과");
			//errMsg2(Task.AutoFlag,tmpStr);
			return false;
		}

		checkMessage();
		Sleep(5);
		}

	return true;
	}

bool CDioControl::StartPBLampOn(bool flag)
{
	int moduleNo = 2;
	int channelNo = 2;

	g_CriOutDio.Lock();
	int outVal = curOutDioByte[moduleNo][channelNo];

	if (flag == true)	outVal = outVal | DIO_OUT_START_PB;
	else				outVal = outVal & ~DIO_OUT_START_PB;

	motor.OutDIO(moduleNo, channelNo, outVal);
	g_CriOutDio.Unlock();
	return true;
}





//! Door Open/Close
bool CDioControl::DoorPBOnCheck(bool flag, bool waitFlag)
{
	if (flag)
	{
		if (curInDio[1] & DIO_IN_DOOR_PB) {
			DoorPBLampOn(true);
			return true;
		}
	}
	else
	{
		if (!(curInDio[1] & DIO_IN_DOOR_PB)) {
			DoorPBLampOn(false);
			return true;
		}
	}

	if (!waitFlag)	return false;

	double ep = myTimer(true);
	while (waitFlag)
	{
		if (flag)
		{
			if (curInDio[1] & DIO_IN_DOOR_PB) {
				DoorPBLampOn(true);
				break;
			}
		}
		else
		{
			if (!(curInDio[1] & DIO_IN_DOOR_PB)) {
				DoorPBLampOn(false);
				break;
			}
		}

		if (myTimer(true) - ep > IO_DELAY_TIME)
		{
			//CString tmpStr;
			//if(flag)			tmpStr.Format("Start 스위치 ON 시간 초과");
			//else				tmpStr.Format("Start 스위치 OFF 시간 초과");
			//errMsg2(Task.AutoFlag,tmpStr);
			return false;
		}

		checkMessage();
		Sleep(5);
	}

	return true;
}

bool CDioControl::DoorPBLampOn(bool flag)
{
	int moduleNo = 2;
	int channelNo = 2;

	g_CriOutDio.Lock();
	int outVal = curOutDioByte[moduleNo][channelNo];

	if (flag == true)	outVal = outVal | DIO_OUT_DOOR_PB;
	else				outVal = outVal & ~DIO_OUT_DOOR_PB;

	motor.OutDIO(moduleNo, channelNo, outVal);
	g_CriOutDio.Unlock();

	return true;
}
bool CDioControl::DoorLift(bool flag, bool waitflag)
{
	int moduleNo = 2;
	int channelNo = 0;

	g_CriOutDio.Lock();

	int outVal = curOutDioByte[moduleNo][channelNo];

	if (flag)
	{
		outVal = outVal | DIO_OUT_DOOR_OPEN;
		outVal = outVal & ~DIO_OUT_DOOR_CLOSE;
	}
	else
	{
		outVal = outVal & ~DIO_OUT_DOOR_OPEN;
		outVal = outVal | DIO_OUT_DOOR_CLOSE;
	}
	motor.OutDIO(moduleNo, channelNo, outVal);

	g_CriOutDio.Unlock();

	if (!waitflag)	return true;

	if (waitflag)
	{
		if (!DoorLiftOnCheck(flag, waitflag))
		{
			return false;
		}
	}

	return true;
}

bool CDioControl::DoorLiftOnCheck(bool flag, bool waitflag)
{
	if (flag)
	{
		if (curInDio[1] & DIO_IN_DOOR_OPEN)
		{
			if (!(curInDio[1] & DIO_IN_DOOR_CLOSE))
				return true;
		}
	}
	else
	{
		if (curInDio[1] & DIO_IN_DOOR_CLOSE)
		{
			if (!(curInDio[1] & DIO_IN_DOOR_OPEN))
				return true;
		}
	}

	if (!waitflag)	return false;

	double ep = myTimer(true);
	while (waitflag)
	{
		if (Task.AutoFlag == 0)
		{
			break;	//자동운전시작으로 도어오픈도중에 STOP 클릭시 무한루프 방지
		}
		if (flag)
		{
			if (curInDio[1] & DIO_IN_DOOR_OPEN)
			{
				if (!(curInDio[1] & DIO_IN_DOOR_CLOSE))
					break;
			}
		}
		else
		{
			if (curInDio[1] & DIO_IN_DOOR_CLOSE)
			{
				if (!(curInDio[1] & DIO_IN_DOOR_OPEN))
					break;
			}
		}

		if (myTimer(true) - ep > 8000/*IO_DELAY_TIME*2*/)
		{
			CString tmpStr = "";
			if (flag) {
				tmpStr.Format("DoorLift Open 동작 시간 초과");
			}
			else {
				tmpStr.Format("DoorLift Close 동작 시간 초과");
			}
			errMsg2(Task.AutoFlag, tmpStr);

			return false;
		}

		checkMessage();
		Sleep(1);
		checkMessage();
		Sleep(1);
		checkMessage();
	}

	return true;
}

bool CDioControl::LightCurtainOnCheck(bool flag, bool waitFlag)
{// flag = true일 경우 감지 확인, false = 미감지 확인

	if (flag)
	{//감지확인 시 감지 되었을 경우
		if (!(curInDio[0] & DIO_IN_LIGHT_CURTAIN)) {
			return true;
		}
	}
	else
	{//미감지 확인 시  미감지 되었을 경우
		if ((curInDio[0] & DIO_IN_LIGHT_CURTAIN)) {
			return true;
		}
	}

	if (!waitFlag)	return false;

	double ep = myTimer(true);
	while (waitFlag)
	{
		if (flag)
		{
			if (!(curInDio[0] & DIO_IN_LIGHT_CURTAIN)) {
				break;
			}
		}
		else
		{
			if (curInDio[0] & DIO_IN_LIGHT_CURTAIN) {
				break;
			}
		}

		if (myTimer(true) - ep > IO_DELAY_TIME)
		{
			return false;
		}

		checkMessage();
		Sleep(5);
	}
	return true;
}

bool CDioControl::UVCheck(bool flag, bool waitFlag)
{// flag = true일 경우 감지 확인, false = 미감지 확인

	if (flag)
	{//감지확인 시 감지 되었을 경우
		if ((curInDio[0] & DIO_IN_UV_LAMP_ON)) {
			return true;
		}
	}
	else
	{//미감지 확인 시  미감지 되었을 경우
		if (!(curInDio[0] & DIO_IN_UV_LAMP_ON)) {
			return true;
		}
	}

	if (!waitFlag)	return false;

	double ep = myTimer(true);
	while (waitFlag)
	{
		if (flag)
		{
			if ((curInDio[0] & DIO_IN_UV_LAMP_ON)) {
				break;
			}
		}
		else
		{
			if (!curInDio[0] & DIO_IN_UV_LAMP_ON) {
				break;
			}
		}

		if (myTimer(true) - ep > IO_DELAY_TIME)
		{
			return false;
		}

		checkMessage();
		Sleep(5);
	}
	return true;
}


bool CDioControl::UVTrigger(bool flag, bool waitFlag)
{
	int moduleNo = 0;
	int channelNo = 2;

	g_CriOutDio.Lock();

	int outVal = curOutDioByte[moduleNo][channelNo];

	if (flag)
	{
		//outVal = outVal | DIO_OUT_UV_OFF;
		outVal = outVal /*| DIO_OUT_UV_UP*/ | DIO_OUT_UV_ON;
	}
	else
	{
		//outVal = outVal & ~DIO_OUT_UV_OFF;
		outVal = outVal & ~/*DIO_OUT_UV_UP | */DIO_OUT_UV_ON;
	}

	motor.OutDIO(moduleNo, channelNo, outVal);
	g_CriOutDio.Unlock();

	if (!waitFlag)		return true;

	//if ( waitFlag )
	//{
	//	if ( !EpoxyDischargeOnCheck(flag, waitFlag) )
	//	{
	//		return false;
	//	}
	//}

	return true;
}

bool CDioControl::LensVacuumOn(bool flag)
{

	return true;
}


bool CDioControl::EpoxyDischargeOn(bool flag, bool waitFlag)
{//Dispence 토출 On/Off 
	int moduleNo = 0;
	int channelNo = 3;	//

	g_CriOutDio.Lock();

	int outVal = curOutDioByte[moduleNo][channelNo];

	if (flag)
	{
		outVal = outVal | DIO_OUT_EPOXY_ON;
	}
	else
	{
		outVal = outVal & ~DIO_OUT_EPOXY_ON;
	}

	motor.OutDIO(moduleNo, channelNo, outVal);

	g_CriOutDio.Unlock();

	if (!waitFlag)		return true;

	if (waitFlag)
	{
		if (!EpoxyDischargeOnCheck(flag, waitFlag))
		{
			return false;
		}
	}

	return true;
}

bool CDioControl::EpoxyDischargeOnCheck(bool flag, bool waitFlag)
{	//Dispence 토출중 Check
	if (!flag) {
		if (curInDio[0] & DIO_IN_EPOXY_ON)
			return true;
	}
	else
	{
		if (!(curInDio[0] & DIO_IN_EPOXY_ON))
			return true;
	}

	if (!waitFlag)	return false;

	double ep = myTimer(true);

	while (waitFlag)
	{
		if (flag)
		{
			if (curInDio[0] & DIO_IN_EPOXY_ON)
				break;
		}
		else
		{
			if (!(curInDio[0] & DIO_IN_EPOXY_ON))
				break;
		}

		if (myTimer(true) - ep > IO_DELAY_TIME)
		{
			CString tmpStr;
			CString sTemp;
			sLangChange.LoadStringA(IDS_STRING501);
			sTemp.LoadString(IDS_STRING500);
			if (flag)			tmpStr.Format(sLangChange);		//Dispence 토출상태ON 시간 초과
			else				tmpStr.Format(sTemp);			//Dispence 토출상태OFF 시간 초과

			errMsg2(Task.AutoFlag, tmpStr);

			return false;
		}

		checkMessage();
		Sleep(5);
	}

	return true;
}

// 20150603
bool CDioControl::EpoxyDischargeOn2(bool flag, bool waitFlag)
{
	//Dispence 토출 On/Off 
	//int moduleNo = 0;
	//int channelNo = 3;	//

	//g_CriOutDio.Lock();

	//int outVal = curOutDioByte[moduleNo][channelNo];

	//if (flag)
	//{
	//	outVal = outVal | DIO_OUT_EPOXY_ON2;
	//}
	//else
	//{
	//	outVal = outVal & ~DIO_OUT_EPOXY_ON2;
	//}

	//motor.OutDIO(moduleNo, channelNo, outVal);

	//g_CriOutDio.Unlock();

	//if (!waitFlag)		return true;

	//if (waitFlag)
	//{
	//	if (!EpoxyDischargeOnCheck(flag, waitFlag))
	//	{
	//		return false;
	//	}
	//}

	return true;
}

// 20150603
bool CDioControl::EpoxyDischargeOnCheck2(bool flag, bool waitFlag)
{	
	//Dispence 토출중 Check
	//if (!flag) {
	//	if (curInDio[0] & DIO_IN_EPOXY_ON2)
	//		return true;
	//}
	//else
	//{
	//	if (!(curInDio[0] & DIO_IN_EPOXY_ON2))
	//		return true;
	//}

	//if (!waitFlag)	return false;

	//double ep = myTimer(true);

	//while (waitFlag)
	//{
	//	if (flag)
	//	{
	//		if (curInDio[0] & DIO_IN_EPOXY_ON2)
	//			break;
	//	}
	//	else
	//	{
	//		if (!(curInDio[0] & DIO_IN_EPOXY_ON2))
	//			break;
	//	}

	//	if (myTimer(true) - ep > IO_DELAY_TIME)
	//	{
	//		CString tmpStr;
	//		CString sTemp;
	//		sLangChange.LoadStringA(IDS_STRING501);
	//		sTemp.LoadString(IDS_STRING500);
	//		if (flag)			tmpStr.Format(sLangChange);		//Dispence 토출상태ON 시간 초과
	//		else				tmpStr.Format(sTemp);			//Dispence 토출상태OFF 시간 초과

	//		errMsg2(Task.AutoFlag, tmpStr);

	//		return false;
	//	}

	//	checkMessage();
	//	Sleep(5);
	//}

	return true;
}

void CDioControl::SetBuzzer(bool flag, int iType)
{
	int moduleNo = 0;
	int channelNo = 1;	//

	g_CriOutDio.Lock();

	int outVal = curOutDioByte[moduleNo][channelNo];

	//outVal &= ~(DIO_OUT_TOWER_LAMP_BUZZER | DIO_OUT_BUZZER1 | DIO_OUT_BUZZER2 | DIO_OUT_BUZZER3 | DIO_OUT_BUZZER4);
	outVal &= ~(DIO_OUT_BUZZER1 | DIO_OUT_BUZZER2 | DIO_OUT_BUZZER3 | DIO_OUT_BUZZER4);
	switch (iType)
	{
	case ALARM_ON:
		outVal |= DIO_OUT_BUZZER1;
		break;
	case AUTO_RUN:
		outVal |= DIO_OUT_BUZZER4;
		break;
	case AUTO_STOP:
		outVal |= DIO_OUT_BUZZER2;
		break;
	}
	motor.OutDIO(moduleNo, channelNo, outVal);

	if (iType == AUTO_RUN || iType == AUTO_STOP)
	{
		Sleep(500);
		outVal = curOutDioByte[moduleNo][channelNo];

		//outVal &= ~(DIO_OUT_TOWER_LAMP_BUZZER | DIO_OUT_BUZZER1 | DIO_OUT_BUZZER2 | DIO_OUT_BUZZER3 | DIO_OUT_BUZZER4);
		outVal &= ~(DIO_OUT_BUZZER1 | DIO_OUT_BUZZER2 | DIO_OUT_BUZZER3 | DIO_OUT_BUZZER4);
		motor.OutDIO(moduleNo, channelNo, outVal);
	}

	g_CriOutDio.Unlock();
}

int CDioControl::SensorContactCheck()
{
	int moduleNo = 1;
	int SensorData = 0;

	if (curInDio[moduleNo] & DIO_IN_DIS_SENSOR)
		SensorData = 1;
	else
		SensorData = 0;
	return SensorData;
}



void CDioControl::SetLampOn(int iType)
{
	int moduleNo = 0;
	int channelNo = 1;

	g_CriOutDio.Lock();
	int outVal = curOutDioByte[moduleNo][channelNo];

	if (iType == ALARM_ON)//RED LAMP
	{
		outVal |= DIO_OUT_TOWER_LAMP_R;
		outVal &= ~(DIO_OUT_TOWER_LAMP_G | DIO_OUT_TOWER_LAMP_Y);
	}
	else if (iType == AUTO_RUN)//Green LAMP
	{
		outVal |= DIO_OUT_TOWER_LAMP_G;
		outVal &= ~(DIO_OUT_TOWER_LAMP_R | DIO_OUT_TOWER_LAMP_Y);
	}
	else if (iType == AUTO_STOP)//Yellow LAMP
	{
		outVal |= DIO_OUT_TOWER_LAMP_Y;
		outVal &= ~(DIO_OUT_TOWER_LAMP_R | DIO_OUT_TOWER_LAMP_G);
	}
	else if (iType == ALARM_OFF)
	{
		outVal &= ~(DIO_OUT_TOWER_LAMP_R | DIO_OUT_TOWER_LAMP_Y | DIO_OUT_TOWER_LAMP_G);
	}
	motor.OutDIO(moduleNo, channelNo, outVal);
	g_CriOutDio.Unlock();
}


//! Pcb Grip 전진/후진
bool CDioControl::PcbGrip(bool flag, bool waitFlag)
{
	int moduleNo = 2;
	int channelNo = 0;

	g_CriOutDio.Lock();

	int outVal = curOutDioByte[moduleNo][channelNo];

	if (flag)
	{
		outVal = outVal | DIO_OUT_PCB_GRIP_FOR;
		outVal = outVal & ~DIO_OUT_PCB_GRIP_BACK;
	}
	else
	{
		outVal = outVal & ~DIO_OUT_PCB_GRIP_FOR;
		outVal = outVal | DIO_OUT_PCB_GRIP_BACK;
	}
	motor.OutDIO(moduleNo, channelNo, outVal);

	g_CriOutDio.Unlock();


#ifndef		ON_LINE_DIO
	return true;
#endif


	if (waitFlag)
	{
		if (!PcbGripCheck(flag, waitFlag))
		{
			return false;
		}
	}

	return true;
}

//! PCB Grip 전진/후진 센서
bool CDioControl::PcbGripCheck(bool flag, bool waitFlag)
{
	if (flag)
	{
		if (curInDio[1] & DIO_IN_PCB_GRIP_FOR)
		{
			if (!(curInDio[1] & DIO_IN_PCB_GRIP_BACK))
				return true;
		}
	}
	else
	{
		if (curInDio[1] & DIO_IN_PCB_GRIP_BACK)
		{
			if (!(curInDio[1] & DIO_IN_PCB_GRIP_FOR))
				return true;
		}
	}

#ifndef		ON_LINE_DIO
	return true;
#endif

	if (!waitFlag)
		return false;

	double ep = myTimer(true);

	while (waitFlag)
	{
		if (flag)
		{
			if (curInDio[1] & DIO_IN_PCB_GRIP_FOR)
			{
				if (!(curInDio[1] & DIO_IN_PCB_GRIP_BACK))
					break;
			}
		}
		else
		{
			if (curInDio[1] & DIO_IN_PCB_GRIP_BACK)
			{
				if (!(curInDio[1] & DIO_IN_PCB_GRIP_FOR))
					break;
			}
		}

		if (myTimer(true) - ep>IO_DELAY_TIME)
		{
			CString tmpStr;
			CString sTemp;
			//sLangChange.LoadStringA(IDS_STRING669);
			//sTemp.LoadString(IDS_STRING672);
			if (flag)			tmpStr.Format(_T("PCB Grip Advance Operation Timeout"));	//PCB Grip 전진 동작 시간 초과
			else				tmpStr.Format(_T("PCB Grip Backward Operation Timeout"));		//PCB Grip 후진 동작 시간 초과

			errMsg2(Task.AutoFlag, tmpStr);

			return false;
		}


		checkMessage();
		Sleep(1);
		checkMessage();
		Sleep(1);
		checkMessage();
	}

	return true;
}
//! Laser Lift 상승/하강
bool CDioControl::CamLaserClinder(bool flag, bool waitFlag)
{
	/*int moduleNo = 2;
	int channelNo = 2;

	g_CriOutDio.Lock();

	int outVal = curOutDioByte[moduleNo][channelNo];

	if (flag)
	{
		outVal = outVal | DIO_OUT_LASER_LIFT_UP;
		outVal = outVal & ~DIO_OUT_LASER_LIFT_DOWN;
	}
	else
	{
		outVal = outVal & ~DIO_OUT_LASER_LIFT_UP;
		outVal = outVal | DIO_OUT_LASER_LIFT_DOWN;
	}
	motor.OutDIO(moduleNo, channelNo, outVal);

	g_CriOutDio.Unlock();


#ifndef		ON_LINE_DIO
	return true;
#endif


	if (waitFlag)
	{
		if (!CamLaserClinderCheck(flag, waitFlag))
		{
			return false;
		}
	}*/

	return true;
}

bool CDioControl::CamLaserClinderCheck(bool flag, bool waitFlag)
{
//	if (flag)
//	{
//		if (curInDio[1] & DIO_IN_LASER_LIFT_UP)
//		{
//			if (!(curInDio[1] & DIO_IN_LASER_LIFT_DOWN))
//				return true;
//		}
//	}
//	else
//	{
//		if (curInDio[1] & DIO_IN_LASER_LIFT_DOWN)
//		{
//			if (!(curInDio[1] & DIO_IN_LASER_LIFT_UP))
//				return true;
//		}
//	}
//
//#ifndef		ON_LINE_DIO
//	return true;
//#endif
//
//	if (!waitFlag)
//		return false;
//
//	double ep = myTimer(true);
//
//	while (waitFlag)
//	{
//		if (flag)
//		{
//			if (curInDio[1] & DIO_IN_LASER_LIFT_UP)
//			{
//				if (!(curInDio[1] & DIO_IN_LASER_LIFT_DOWN))
//					break;
//			}
//		}
//		else
//		{
//			if (curInDio[1] & DIO_IN_LASER_LIFT_DOWN)
//			{
//				if (!(curInDio[1] & DIO_IN_LASER_LIFT_UP))
//					break;
//			}
//		}
//
//		if (myTimer(true) - ep>10000)//IO_DELAY_TIME)
//		{
//			CString tmpStr;
//			CString sTemp;
//			/*sLangChange.LoadStringA(IDS_STRING678);
//			sTemp.LoadString(IDS_STRING680);*/
//			if (flag)			tmpStr.Format("Laser/Cam 전진 동작 시간 초과");	//Laser Lift 상승 동작 시간 초과
//			else				tmpStr.Format("Laser/Cam 후진 동작 시간 초과");	//Laser Lift 하강 동작 시간 초과
//
//			errMsg2(Task.AutoFlag, tmpStr);
//
//			return false;
//		}
//
//
//		checkMessage();
//		Sleep(1);
//		checkMessage();
//		Sleep(1);
//		checkMessage();
//	}

	return true;
}
bool CDioControl::VacuumSol(bool flag, bool waitFlag)
{
	//int moduleNo = 2;
	//int channelNo = 0;	//

	//g_CriOutDio.Lock();

	//int outVal = curOutDioByte[moduleNo][channelNo];

	//if (flag)
	//{
	//	outVal = outVal | DIO_OUT_VACUUM_SOL;
	//}
	//else
	//{
	//	outVal = outVal & ~DIO_OUT_VACUUM_SOL;
	//}

	//motor.OutDIO(moduleNo, channelNo, outVal);
	//g_CriOutDio.Unlock();

	//if (!waitFlag)		return true;


	return true;
}
bool CDioControl::Relay(bool flag, bool waitFlag)
{
	//int moduleNo = 0;
	//int channelNo = 2;	//

	//g_CriOutDio.Lock();

	//int outVal = curOutDioByte[moduleNo][channelNo];

	//if (flag)
	//{
	//	outVal = outVal | DIO_OUT_RELAY;
	//}
	//else
	//{
	//	outVal = outVal & ~DIO_OUT_RELAY;
	//}

	//motor.OutDIO(moduleNo, channelNo, outVal);
	//g_CriOutDio.Unlock();

	//if (!waitFlag)		return true;


	return true;
}
