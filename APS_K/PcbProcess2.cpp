#include "StdAfx.h"
#include "PcbProcess2.h"

CWinThread* pThread_TaskCCD = NULL;
bool bThreadCCDRun = false;
typedef struct THREADV
{
	int t_Unit;
}_threadV;
//
UINT Thread_TaskCCD(LPVOID parm)
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	CString logStr = "";


	bThreadCCDRun = true;			//DRY_RUN
	if (!pFrame->MIUCheck_process())		// || gMIUDevice.CurrentState != 4)
	{
		logStr.Format("CCD 모듈 영상 초기화 실패.\n 제품 안착 상태 및 제품 불량 확인 하세요.");
		errMsg2(Task.AutoFlag, logStr);
		bThreadCCDRun = false;
		return false;
	}
	Sleep(300);
	bThreadCCDRun = false;


	return true;
}
CPcbProcess2::CPcbProcess2(void)
{
	dwTickStartRun = false;

}


CPcbProcess2::~CPcbProcess2(void)
{
}

void CPcbProcess2::putListLog(CString strLog)
{
	theApp.MainDlg->putListLog(strLog);
}

int CPcbProcess2::Ready_process(int iStep)
{
	CString sLog = "";
	int iRtnFunction = iStep;

	switch (iStep)
	{
	case 10000:
		Task.PCBTaskTime = myTimer(true);
		vision.clearOverlay(CCD);

		if (sysData.m_iIrChartUse == 1)
		{
			LightControl.ctrlLedVolume(LIGHT_TOP_CHART1, 0);
			Sleep(100);
			LightControl.ctrlLedVolume(LIGHT_TOP_CHART1, model.m_iLedValue[LEDDATA_TOP2_CHART]);
		}
		else
		{
			LightControl.ctrlLedVolume(LIGHT_TOP_CHART1, 0);
			Sleep(100);
			LightControl.ctrlLedVolume(LIGHT_TOP_CHART1, model.m_iLedValue[LEDDATA_TOP1_CHART]);
		}
		iRtnFunction = 10150;
		break;


	case  10150:
		if (Dio.LensMotorGripCheck(true, false))
		{
			if (Task.m_bOKLensPass == 1)   //Lens 넘김 완료상태
			{
				iRtnFunction = 10160;
				sLog.Format("		Ready Step [%d]", iRtnFunction);
				putListLog(sLog);
			}
			else
			{
				sLog.Format("[운전 준비] Lens Grip 전진 상태 입니다[%d]\n렌즈넘김상태 확인바랍니다", iStep);
				errMsg2(Task.AutoFlag, sLog);
				iRtnFunction = -10150;
				break;
			}
		}
		else
		{
			if (!Dio.LensMotorGripCheck(false, false))
			{
				sLog.Format("[운전 준비]Lens Grip 전진 확인 실패 [%d]", iStep);
				errMsg2(Task.AutoFlag, sLog);
				iRtnFunction = -10150;
			}
			else
			{
				if (Task.m_bOKLensPass == 1)   //Lens 넘김 완료상태
				{
					sLog.Format("[운전 준비]Lens Grip 후진 상태 [%d]]\n렌즈넘김상태 확인바랍니다", iStep);
					errMsg2(Task.AutoFlag, sLog);
					iRtnFunction = -10150;
				}
				else
				{
					iRtnFunction = 10160;
					sLog.Format("		Ready Step [%d]", iRtnFunction);
					putListLog(sLog);
				}

			}
		}
		break;

	case 10160:

		iRtnFunction = 10170;
		break;

	case 10170:
		iRtnFunction = 10200;
		break;

	case 10200:
		if (motor.PCB_Z_Motor_Move(Wait_Pos))		//PCB Z축 대기 위치 이동
		{
			iRtnFunction = 10300;
		}
		else
		{
			sLog.Format("[운전 준비] PCB Z축 대기위치 이동 실패[%d]", iStep);	//"[운전 준비] PCB Z축 대기위치 이동 실패[%d]"
			putListLog(sLog);
			iRtnFunction = -10200;
		}

		break;

	case 10300:
		if (motor.LENS_Z_Motor_Move(Wait_Pos))		//Lens Z축 대기 위치
		{
			iRtnFunction = 10400;
		}
		else
		{
			sLog.Format("Lens Z축 대기위치 이동 실패[%d]", iStep);	//"[운전 준비] Lens Z축 대기위치 이동 실패[%d]"
			putListLog(sLog);
			iRtnFunction = -10300;
		}
		break;
	case 10400:
		iRtnFunction = 10600;
		break;
	case 10600:
		if (motor.Lens_Motor_MoveX(Wait_Pos))		//Lens X 축 대기 위치
		{
			iRtnFunction = 10601;
		}
		else
		{
			sLog.Format("LensLaserAlign Z축 대기위치 이동 실패[%d]", iStep);	//"[운전 준비] Lens Z축 대기위치 이동 실패[%d]"
			putListLog(sLog);
			iRtnFunction = -10600;
		}
		break;
	case 10601:
		iRtnFunction = 10602;
		break;
	case 10602:
		if (motor.Pcb_Motor_Move(Wait_Pos))			//PCB부 모터 대기위치 이동
		{
			iRtnFunction = 10700;
		}
		else
		{
			sLog.Format("PCB 대기위치 이동 실패[%d]", iStep);
			putListLog(sLog);
			iRtnFunction = -10602;
		}
		break;
	case 10700:
		iRtnFunction = 10701;
		break;
	case 10701:
		if (motor.Lens_Motor_MoveXY(Wait_Pos))			//Lens부 모터 대기 위치 이동(Lens X/Y/Z축)
		{
			iRtnFunction = 10750;
		}
		else
		{
			sLog.Format(" Lens 대기위치 이동 실패[%d]", iStep);	//"[운전 준비] Lens 대기위치 이동 실패[%d]"
			putListLog(sLog);
			iRtnFunction = -10701;
		}
		break;
	case 10750:
		if (motor.Pcb_Tilt_Motor_Move(Wait_Pos))
		{
			iRtnFunction = 10800;
		}
		else
		{
			sLog.Format("PCB부 Tx, Ty축 대기 위치 이동 실패");
			putListLog(sLog);
			iRtnFunction = -10750;
		}
		break;
	case 10800:
		if (motor.Lens_Tilt_Motor_Move(Wait_Pos))
		{
			iRtnFunction = 10900;
		}
		else
		{
			sLog.Format("LENS부 Tx, Ty축 대기 위치 이동 실패");
			putListLog(sLog);
			iRtnFunction = -10800;
		}
		break;
	case  10900:
		//Dio.LensVacuumOn(false);
		iRtnFunction = 10901;
		break;
	case  10901:
		iRtnFunction = 10950;
		break;
	case 10950:
		Dio.HolderGrip(false, false);
		sLog.Format("Holder UnGrip 동작 [%d]", iRtnFunction);
		theApp.MainDlg->putListLog(sLog);

		iRtnFunction = 10970;
		break;
	case 10970:
		MIU.Close();
		iRtnFunction = 15000;	//While문 종료
		break;
	case 15000:
		//UVCommand.UV_Shutter_PowerSet(model.UV_Power);

		//sLog.Format("	#1 UV POWER SET: %d", model.UV_Power);
		//putListLog(sLog);
		Sleep(500);
		//UVCommand2.UV_Shutter_PowerSet(model.UV_Power);
		UVCommand.UV_Shutter_PowerSet(model.UV_Power);
		Dio.DoorLift(true, false);
		//UVCommand.UV_Shutter_Open();  //TRI UV
		//sLog.Format("	#2 UV POWER SET: %d", model.UV_Power);
		//putListLog(sLog);
		iRtnFunction = 19000;
		break;

	case 19000:
		Task.AutoReday = 1;
		iRtnFunction = 19900;
		sLog.Format("		Ready Step [%d]", iRtnFunction);
		putListLog(sLog);
		break;
	}
	return iRtnFunction;
}

int CPcbProcess2::RunProc_ProductLoading(int iUseStep)
{//! 작업자 제품 투입 자동 Step		(10000 ~ 10999)
	int iRtnFunction = iUseStep;
	CString logStr = "", sBarCode = "";
	bool bChk = true;
	bool bRetVal = false;
	switch (iUseStep)
	{
	case 10000:
		Task.interlockLens = 0;
		Task.interlockPcb = 0;
		iRtnFunction = 10010;
		break;
	case 10010:
		iRtnFunction = 10030;
		break;
	case 10030:
		iRtnFunction = 10050;
		break;
	case 10050:
		//LightControl.ctrlLedVolume(LIGHT_OC_6500K, 0);		// Align만 조명 ON
		Task.PCBTaskTime = myTimer(true);

		iRtnFunction = 10060;
		break;

	case 10060:
		if (motor.IsStopAxis(Motor_Lens_X) && motor.IsStopAxis(Motor_Lens_Y) && motor.checkLensMotorPos(Wait_Pos))
		{
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 10070;
			break;
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > 10000)
		{
			logStr.Format(_T("Lens x,y axis 정지 확인 실패[%d]"), iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -10060;
			break;
		}
		break;
	case 10070:
		iRtnFunction = 10100;
		break;
	case 10100://! Chip 정보 Draw
		//theApp.MainDlg->func_ChipID_Draw();
		iRtnFunction = 10101;

		logStr.Format("		Start 버튼을 눌러주세요[%d]", iRtnFunction);
		theApp.MainDlg->putListLog(logStr);
		theApp.MainDlg->m_btnStart.m_iStateBtn = 4;
		theApp.MainDlg->m_btnStart.Invalidate();
		break;
	case 10101://! Start P/B Button Push 대기. 
		if (Dio.StartPBOnCheck(true, false))//
		{
			Dio.PCBvaccumOn(VACCUM_ON, false);      //흡착
			iRtnFunction = 10102;
			break;
		}
		break;
	case 10102:
		if (Dio.PCBvaccumOnCheck(true, false) == false)		//DRY_RUN
		{
			logStr.Format("PCB 흡착 감지 실패 [%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -10102;
			break;
		}
		logStr.Format("PCB 흡착 감지 확인 완료 [%d]", iRtnFunction);
		theApp.MainDlg->putListLog(logStr);
		iRtnFunction = 10110;
		break;
	case 10110://! Start P/B Button Push 대기. 
		if (Dio.StartPBOnCheck(true, false))// || Start_Btn_On)	//프로그램에 start 버튼 추가
		{

			iRtnFunction = 10165;
			MbufClear(vision.MilOptImage, 0);

			theApp.MainDlg->m_btnStart.m_iStateBtn = 0;
			theApp.MainDlg->m_btnStart.Invalidate();
			theApp.MainDlg->Start_Btn_On = false;

			if (Task.m_bOKLensPass == 1)   //Lens 넘김 완료상태
			{
				if (!askMsg("렌즈 넘김상태입니다. \n계속 진행하시겠습니까?") == IDOK)
				{
					iRtnFunction = 10000;
					break;
				}
			}
			logStr.Format("START BUTTON PRESS [%d]", iRtnFunction);
			theApp.MainDlg->putListLog(logStr);
		}
		break;
	case 10165://! Start P/B Button Push 대기. 
		Dio.StartPBLampOn(false);
		Dio.DoorLift(false, false);
		Dio.PCBvaccumOn(VACCUM_ON, false);      //흡착
		sBarCode.Format("%s", Task.ChipID);
		if (sysData.m_iProductComp == 1)
		{
			logStr.Format("====%s 완제품 검사 start====", Task.ChipID);
		}
		else
		{
			logStr.Format("====%s AA start====", Task.ChipID);
		}
		vision.clearOverlay(CCD);
		vision.drawOverlay(CCD);
		theApp.MainDlg->putListLog(logStr);
		iRtnFunction = 10170;
		break;
	case 10170:
		if ((myTimer(true) - Task.PCBTaskTime) > 300)
		{
			iRtnFunction = 10171;
			break;
		}
		break;
	case 10171:
		iRtnFunction = 10178;
		break;
	case 10178:
	{
		bool bflag = true;

		Task.d_Align_offset_x[LENS_Align_MARK] = 0;
		Task.d_Align_offset_y[LENS_Align_MARK] = 0;
		Task.d_Align_offset_th[LENS_Align_MARK] = 0;

		MandoInspLog.func_InitData();

		Task.func_TactTimeInit();


		theApp.MainDlg->dispGrid();

		Task.m_timeChecker.Measure_Time(1);	//Start 버튼 클릭 시간
		theApp.MainDlg->func_ChipID_Draw();
		MandoInspLog.bInspRes = true;
		vision.clearOverlay(CCD);
		int iSocketCount = 0;

		//logStr.Format("%d", sysData.m_Socket_Count);
		iSocketCount = atoi(logStr);
		iSocketCount++;
		sysData.m_Socket_Count = iSocketCount;
		sysData.Save();

		iRtnFunction = 10180;
	}
	break;
	case 10180:
		if (motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("PCB Z Wait 위치 이동 완료 [%d]", iRtnFunction);
			theApp.MainDlg->putListLog(logStr);
			iRtnFunction = 10200;
			break;
		}
		else
		{
			logStr.Format("PCB Z Wait 위치 이동 완료 실패 [%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -10180;
			break;
		}
		break;
	case 10200:
		if (motor.Lens_Tilt_Motor_Move(Wait_Pos))
		{
			iRtnFunction = 10202;
			break;
		}
		else
		{
			logStr.Format("LENS부 Tx, Ty축 대기 위치 이동 실패");
			theApp.MainDlg->putListLog(logStr);
			iRtnFunction = -10200;
			break;
		}
		break;

	case 10202:

		iRtnFunction = 10205;
		break;

	case 10205:
		if (sysData.m_iProductComp == 1)
		{
			iRtnFunction = 10250;
			break;
		}
		else
		{
			iRtnFunction = 10210;
			break;
		}
		break;

	case 10210:
		if (Dio.HolderGrip(true, false))
		{
			logStr.Format("Holder Grip 동작 [%d]", iRtnFunction);
			theApp.MainDlg->putListLog(logStr);
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 10250;
			break;
		}
		else
		{
			logStr.Format("Holder Grip 실패[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -10210;
			break;
		}
		
		break;

	case 10250:
		if (!Dio.HolderGripCheck(true, false))
		{
			logStr.Format("Holder Grip 확인 [%d]", iRtnFunction);
			theApp.MainDlg->putListLog(logStr);
			iRtnFunction = 10400;
			break;
			
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > 3000)
		{
			if (askMsg("Holder Grip Fail \n계속 진행하시겠습니까?") == IDOK)
			{
				iRtnFunction = 10400;
				break;
			}
			logStr.Format("HoldertLens Grip Fail[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -10210;
			break;
			
		}
		break;
	case 10400:	
		//! X Y 바코드 POS 이동
		if (motor.Pcb_Motor_Move(Dark_Pos))	//BarcodePos
		{
			logStr.Format("PCB XY BarcodePos 위치 이동 완료 [%d]", iRtnFunction);
			theApp.MainDlg->putListLog(logStr);
			iRtnFunction = 10401;
			break;
		}
		else
		{
			logStr.Format("PCB XY BarcodePos 위치 이동 완료 실패 [%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -10180;
			break;
		}
		break;
	case 10401:
		// Z 바코드 POS 이동
		if (motor.PCB_Z_Motor_Move(Dark_Pos))  //BarcodePos
		{
			logStr.Format("PCB Z BarcodePos 위치 이동 완료 [%d]", iRtnFunction);
			theApp.MainDlg->putListLog(logStr);
			iRtnFunction = 10402;
		}
		else
		{
			logStr.Format("PCB Z BarcodePos 위치 이동 완료 실패 [%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -10180;
		}
		break;
		iRtnFunction = 10402;
		break;
	case 10402:
		//바코드 리딩
		bRetVal = theApp.MainDlg->SendPacketToBarcode(true);
		sBarCode.Format("%s", Task.ChipID);
		//g_ADOData.func_AATaskToRecordID(modelList.curModelName, Task.ChipID);
		if (bRetVal == false)
		{
			logStr.Format("[LAN]Barcode BCR Read 전송 실패 [%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -10402;
			break;
		}
		logStr.Format("[LAN]Barcode BCR Read 전송 성공 [%d]", iRtnFunction);
		theApp.MainDlg->putListLog(logStr);
		iRtnFunction = 10440;
		break;

	case 10440:
		if (sysData.m_testRunMode == false)			//DRY_RUN
		{
			pThread_TaskCCD = ::AfxBeginThread(Thread_TaskCCD, this);

		}
		iRtnFunction = 10500;
		break;
	case 10500:
		if (sysData.m_iFront == 1)
		{
			iRtnFunction = 10900;
			logStr.Format("Door Open Mode [%d]", iRtnFunction);
			putListLog(logStr);
		}
		else
		{
			iRtnFunction = 10550;
		}
		break;

	case 10550:	//! Area 센서 감지 Check 10450
		if (Dio.LightCurtainOnCheck(false, false))
		{
			if (Dio.DoorLift(false, false))
			{
				Sleep(100);
				iRtnFunction = 10600;
			}
			else
			{
				logStr.Format("Door Close 실패 [%d]", iUseStep);	//Door Close 실패
				errMsg2(Task.AutoFlag, logStr);
				iRtnFunction = -10550;
			}
		}
		else
		{
			logStr.Format(("LightCurtain 감지[%d]"), iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -10550;
		}
		break;

	case 10600:	//Light 커튼 감지 센서 감지 확인 10460
		if (Dio.DoorLiftOnCheck(false, false))
		{
			iRtnFunction = 10900;
			break;
		}

		if (Dio.LightCurtainOnCheck(true, false))//Lift Close도중 감시 센서 감지 될 경우 Open
		{
			if (Dio.DoorLift(true, false))
			{
				iRtnFunction = 10550;
				putListLog(logStr);			
			}
			else
			{
				logStr.Format("Door Close 실패 [%d]", iUseStep);
				errMsg2(Task.AutoFlag, logStr);
				iRtnFunction = -10600;
			}
		}
		break;
	case 10900:
		Task.PcbOnStage = 100;
		Task.m_b_AA_Retry_Flag = false;

		logStr.Format("%d", Task.m_iPcbPickupNo);
		theApp.MainDlg->m_labelPickupNoPcb.SetText(logStr);
		theApp.MainDlg->m_labelPickupNoPcb.Invalidate();

		MandoInspLog.sBarcodeID.Format("%s", Task.ChipID);	//만도 차량용Camera 검사 Log 저장
		iLaser_Pos = 0;


		LightControl.ChartAllControl(true);		//chart Led All On


#if (____AA_WAY == PCB_TILT_AA)
		if (Task.m_bOKLensPass == 1)   //Lens 넘김 완료상태
		{
			logStr.Format("		Lens 그립 진행 [%d]", iRtnFunction);
			theApp.MainDlg->putListLog(logStr);
			iRtnFunction = 15500;// 10250;
			break;
		}
#else
		if (sysData.m_iProductComp == 0)		//lens Thread 동작 부분
		{
			if (Task.m_bOKLensPass != 1)
			{
				Task.LensTask = 30000;	//Lens AA,, 렌즈 로드 동시 동작, 간섭 확인후 사용하시오 240115
			}
			else
			{
				Task.interlockLens = 1;		//Lens AA 사용
				logStr.Format("Lens 넘김 완료  [%d]", iRtnFunction);
				theApp.MainDlg->putListLog(logStr);
			}
		}
#endif
		iRtnFunction = 11000;
		break;

	default:
		logStr.Format("PCB 제품 투입 Thread Step 번호 비정상 [%d]", iUseStep);
		errMsg2(Task.AutoFlag, logStr);
		iRtnFunction = -1;
		break;
	}

	return iRtnFunction;
}

int CPcbProcess2::RunProc_PCBOutsideAlign(int iUseStep)
{
	//! PCB 외부 Align Step(11000 ~ 14999)					//!! MIU_Initialize -> PCB Holder Align 위치
	int iRtnFunction = iUseStep;
	int iCamDelay = model.strInfo_Cam[1].m_iDelayTime;		//PCB 영상 획득 Delay
	int iAlignRetry = model.strInfo_Cam[1].m_iRetryCnt;
	int iRtn = 0;
	CString logStr = "";
	bool bChk = true;
	double offsetX = 0.0, offsetY = 0.0, offsetTh = 0.0;

	//ctrlSubDlg(MAIN_DLG);		//20161212  ccd start 수정
	theApp.MainDlg->m_iCurCamNo = 0;
	theApp.MainDlg->setCamDisplay(1, 0);
	theApp.MainDlg->changeMainBtnColor(MAIN_DLG);
	//	Dio.PCBvaccumOn(VACCUM_OFF, false); 

	switch (iUseStep)
	{
		//흡착
		//흡착 확인
		//
	case 11000:
		/////////////////////////
		Task.PCBTaskTime = myTimer(true);
		iRtnFunction = 11500;
		break;

	case 11500:

		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format(" PCB Z축 대기위치 이동 실패[%d]", iUseStep);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -11500;
			break;

		}

		Task.d_Align_offset_x[PCB_Holder_MARK] = 0;
		Task.d_Align_offset_y[PCB_Holder_MARK] = 0;
		Task.d_Align_offset_th[PCB_Holder_MARK] = 0;
		iRtnFunction = 12000;
		break;
	case 12000:

		if (Task.m_bOKLensPass == 1 || sysData.m_iAlignCamInspPass == 1)   //Lens 넘김 완료상태 RunProc_PCBOutsideAlign
		{
			iRtnFunction = 14100;
			break;
		}

		iRtnFunction = 13000;
		break;
	case 13000:
		Task.m_iRetry_Opt = 0;
		LightControl.ctrlLedVolume(LIGHT_PCB, model.m_iLedValue[LEDDATA_HOLDER]);		// Align만 조명 ON
		
		if (motor.Pcb_Motor_Move(Holder_Pos))
		{
			Task.PCBTaskTime = myTimer(true);
			logStr.Format("Pcb Holder 위치 이동 완료[%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = 13300;
		}
		else
		{
			logStr.Format("Pcb Holder 위치 이동 실패[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -13000;
		}
		break;

	case 13300:
		if (motor.PCB_Z_Motor_Move(Holder_Pos))
		{
			Task.PCBTaskTime = myTimer(true);
			logStr.Format("Pcb Holder Z위치 이동 완료[%d]", iUseStep);
			putListLog(logStr);
			//151109 영진 임시 딜레이
			Sleep(300);
			iRtnFunction = 13500;
		}
		else
		{
			logStr.Format("Pcb Holder Z위치 이동 실패[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -13300;
		}
		break;
	case 13500:
		iRtnFunction = 13600;
		break;
	case 13600:
		if ((myTimer(true) - Task.PCBTaskTime) > iCamDelay && (motor.IsStopAxis(Motor_PCB_X) && motor.IsStopAxis(Motor_PCB_Y)))
		{
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 13700;
		}
		break;
	case 13700: // lens Align

		if (Task.m_iRetry_Opt > iAlignRetry)
		{
			logStr.Format("PCB Holder 재검사 %d 회 실패[%d]\n 보정 미적용으로 진행하시겠습니까?", Task.m_iRetry_Opt, iUseStep);
			if (askMsg(logStr) == IDOK)
			{
				Task.d_Align_offset_x[PCB_Holder_MARK] = 0;
				Task.d_Align_offset_y[PCB_Holder_MARK] = 0;
				Task.d_Align_offset_th[PCB_Holder_MARK] = 0;
				iRtnFunction = 14100;
			}
			else
			{
				Task.m_iRetry_Opt = 0;
				iRtnFunction = 13700;
				logStr.Format("PCB Holder 재검사 시작[%d]", iUseStep);
				putListLog(logStr);
			}

			break;
		}

		offsetX = offsetY = offsetTh = 0.0;
		iRtn = theApp.MainDlg->procCamAlign(CAM1, PCB_Holder_MARK, false, offsetX, offsetY, offsetTh);
		offsetTh = 0.0;
		saveInspImage(PCB_IMAGE_SAVE, Task.m_iRetry_Opt);

		Task.m_iRetry_Opt++;
		offsetTh = 0;//holder x,y축만
		if (iRtn == 0)
		{
			Task.d_Align_offset_x[PCB_Holder_MARK] -= offsetX;
			Task.d_Align_offset_y[PCB_Holder_MARK] -= offsetY;
			Task.d_Align_offset_th[PCB_Holder_MARK] += offsetTh;

			logStr.Format("Pcb Holder : %.3lf %.3lf %.3lf", Task.d_Align_offset_x[PCB_Holder_MARK], Task.d_Align_offset_y[PCB_Holder_MARK], Task.d_Align_offset_th[PCB_Holder_MARK]);
			putListLog(logStr);

			int iRtnVal = theApp.MainDlg->AlignLimitCheck(CAM1, offsetX, offsetY, offsetTh);
			if (iRtnVal == 1)
			{
				iRtnFunction = 14000;				// 보정 이동
			}
			else if (iRtnVal == 2)
			{
				logStr.Format("		Pcb Holder [%d] 완료 [%d]", Task.m_iRetry_Opt, iUseStep);
				putListLog(logStr);

				logStr.Format("		Pcb Holder Complete : %d, %.03f, %.03f, %.03f", Task.m_iPcbPickupNo, Task.d_Align_offset_x[PCB_Holder_MARK], Task.d_Align_offset_y[PCB_Holder_MARK], Task.d_Align_offset_th[PCB_Holder_MARK]);//0.000);
				AlignResultSave(logStr);
				Task.m_iRetry_Opt = 0;
				iRtnFunction = 14100;				// 완료
				break;
			}
			else
			{
				logStr.Format("Pcb Holder [%d] 보정 범위 초과[%d]", Task.m_iRetry_Opt, iUseStep);
				errMsg2(Task.AutoFlag, logStr);
				AlignLogSave(logStr);
				theApp.MainDlg->InstantMarkDelete(PCB_Holder_MARK);
				iRtnFunction = -13700;				// NG
				break;
			}
		}
		else
		{
			logStr.Format("Pcb Holder [%d] 마크 인식 실패[%d]", Task.m_iRetry_Opt, iUseStep);
			putListLog(logStr);
			Sleep(300);
			iRtnFunction = 13700;					//  재검사 
		}
		break;

	case 14000://!! 보정량 이동.- Retry
		if (motor.Pcb_Holder_Align_Move(Holder_Pos, Task.d_Align_offset_x[PCB_Holder_MARK], Task.d_Align_offset_y[PCB_Holder_MARK], Task.d_Align_offset_th[PCB_Holder_MARK]))
		{
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 13500;
		}
		else
		{
			logStr.Format("Pcb Holder 보정 위치 이동 실패[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -14000;
		}
		break;
	case 14100:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format(" PCB Z축 대기위치 이동 실패[%d]", iUseStep);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -14100;
			break;

		}
		iRtnFunction = 14200;
		break;
	case 14200:

#if (____AA_WAY == PCB_TILT_AA)
		iRtnFunction = 15000;
#elif (____AA_WAY == LENS_TILT_AA)
		iRtnFunction = 26000;

#endif
		break;
	default:
		logStr.Format("PCB 제품 투입 Thread Step 번호 비정상 . [%d]", iUseStep);
		errMsg2(Task.AutoFlag, logStr);
		iRtnFunction = -1;
		break;
	}
	return iRtnFunction;
}

int	CPcbProcess2::RunProc_SensorAlign(int iUseStep)
{
	int iRtnFunction = iUseStep;
	int iRtn = 0;
	CString logStr = _T("");
	bool bChk = true;
	double offsetX = 0.0, offsetY = 0.0, offsetTh = 0.0;
	int iCamDelay = model.strInfo_Cam[1].m_iDelayTime;	//PCB 영상 획득 Delay
	int iAlignRetry = model.strInfo_Cam[1].m_iRetryCnt;
	int iLaserDelay = model.strInfo_Cam[0].m_iDelayTime;	//Laser 측정전 Delay
	switch (iUseStep)
	{
	case 26000:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("		PCB Z축 대기위치 이동 실패[%d]", iUseStep);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -26000;
			break;
		}

		Task.d_Align_offset_x[PCB_Chip_MARK] = 0;
		Task.d_Align_offset_y[PCB_Chip_MARK] = 0;
		Task.d_Align_offset_th[PCB_Chip_MARK] = 0;

		iRtnFunction = 26050;
		break;
	case 26050:
		if (sysData.m_iAlignCamInspPass == 1)	//RunProc_SensorAlign
		{

			logStr.Format("PCB Sensor Align Pass[%d]", iUseStep);
			putListLog(logStr);


			Task.m_iRetry_Opt = 0;
			iRtnFunction = 26629;
			break;
		}
		Task.m_iRetry_Opt = 0;
		iRtnFunction = 26600;
		break;

	case 26600:
		iRtnFunction = 26610;
		break;

	case 26610:
		//ctrlSubDlg(MAIN_DLG);
		theApp.MainDlg->m_iCurCamNo = 0;
		//SetDigReference(PCB_Chip_MARK);

		LightControl.ctrlLedVolume(LIGHT_PCB, model.m_iLedValue[LEDDATA_SENSOR]);		// Align만 조명 ON

		if (motor.Pcb_Motor_Move(Align_Pos))
		{
			if (motor.PCB_Z_Motor_Move(Align_Pos))
			{
				logStr.Format("PCB Sensor Align 위치 이동 완료[%d]", iUseStep);
				putListLog(logStr);
				
				Task.d_Align_offset_x[PCB_Chip_MARK] = 0;
				Task.d_Align_offset_y[PCB_Chip_MARK] = 0;
				Task.d_Align_offset_th[PCB_Chip_MARK] = 0;
				iRtnFunction = 26615;
				break;
			}
			else
			{
				logStr.Format("PCB Sensor Align Z 위치 이동 실패 [%d]", iUseStep);
				errMsg2(Task.AutoFlag, logStr);
				iRtnFunction = -26610;
				break;
			}
		}
		else
		{
			logStr.Format("PCB Sensor Align X,Y위치 이동 실패 [%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -26610;
		}
		break;
	case 26615:	
		Task.PCBTaskTime = myTimer(true);
		iRtnFunction = 26616;
		break;
	case 26616:
		if ((myTimer(true) - Task.PCBTaskTime) > iCamDelay && (motor.IsStopAxis(Motor_PCB_X) && motor.IsStopAxis(Motor_PCB_Y)))
		{
			iRtnFunction = 26620;
		}
		break;
	case 26620:
		if (Task.m_iRetry_Opt>iAlignRetry)
		{
			logStr.Format("PCB Align(*SensorAlign*) 재검사 %d 회 실패[%d]\n 보정 미적용으로 진행하시겠습니까?", Task.m_iRetry_Opt, iUseStep);
			Task.d_Align_offset_x[PCB_Chip_MARK] = 0.0;
			Task.d_Align_offset_y[PCB_Chip_MARK] = 0.0;
			Task.d_Align_offset_th[PCB_Chip_MARK] = 0.0;
			Task.m_iRetry_Opt = 0;


			if (askMsg(logStr) == IDOK)
			{
				iRtnFunction = 26629;
				break;
			}
			else
			{
				logStr.Format("PCB Sensor Align 실패 [%d]", iUseStep);
				errMsg2(Task.AutoFlag, logStr);
				iRtnFunction = -26620;
			}
			break;
		}

		offsetX = offsetY = offsetTh = 0.0;

		iRtn = theApp.MainDlg->procCamAlign(CAM1, PCB_Chip_MARK, false, offsetX, offsetY, offsetTh);
		saveInspImage(CHIP_IMAGE_SAVE, Task.m_iRetry_Opt);
		Task.m_iRetry_Opt++;

		//offsetTh=0;
		if (iRtn == 0)
		{
			Task.d_Align_offset_x[PCB_Chip_MARK] -= offsetX; 
			Task.d_Align_offset_y[PCB_Chip_MARK] -= offsetY;
			Task.d_Align_offset_th[PCB_Chip_MARK] += offsetTh;

			Task.dPcbAlignTh = Task.d_Align_offset_th[PCB_Chip_MARK];

			logStr.Format("PCB Sensor Align : %.3lf %.3lf %.3lf", Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]);
			//pcbDlg->m_labelAlignResult.SetText(logStr);
			//pcbDlg->m_labelAlignResult.Invalidate();

			putListLog(logStr);

			int iRtnVal = theApp.MainDlg->AlignLimitCheck(CAM1, offsetX, offsetY, offsetTh);

			if (iRtnVal == 1)
			{
				iRtnFunction = 26625;				// 보정 이동
			}
			else if (iRtnVal == 2)
			{
				logStr.Format("		PCB Sensor Align [%d] 완료 [%d]", Task.m_iRetry_Opt, iUseStep);
				putListLog(logStr);
				//InstantMarkDelete(PCB_Chip_MARK);			//임시 등록 마크 삭제

				logStr.Format("		PCB Sensor Align Complete : %d, %.03f, %.03f, %.03f", Task.m_iPcbPickupNo, Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]);
				AlignResultSave(logStr);
				Task.m_iRetry_Opt = 0;

				Task.m_timeChecker.Measure_Time(4);

				iRtnFunction = 26629;		// 완료
				LightControl.ctrlLedVolume(LIGHT_PCB, 0);
				break;
			}
			else
			{
				logStr.Format("PCB Sensor Align [%d] 보정 범위 초과", Task.m_iRetry_Opt);
				putListLog(logStr);
				errMsg2(Task.AutoFlag, logStr);
				//InstantMarkDelete(PCB_Chip_MARK);
				iRtnFunction = -26620;				// NG
				break;
			}
		}
		else
		{
			logStr.Format("PCB Sensor Align [%d] 마크 인식 실패[%d]", Task.m_iRetry_Opt, iUseStep);
			putListLog(logStr);
			Sleep(300);
			iRtnFunction = 26620;				//  재검사 
		}
		break;
	case 26625://- Sensor Align Retry
		if (motor.Pcb_Holder_Align_Move(Align_Pos, Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]))
		{
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 26615;
		}
		else
		{
			logStr.Format("PCB Sensor Align 보정 위치 이동 실패[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -26625;
		}
		break;
	case 26629:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("PCB Z축 대기위치 이동 실패[%d]", iUseStep);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -26629;
			break;
		}
		iRtnFunction = 26990;
		break;
	case 26990:				

		iRtnFunction = 26991;
		break;
	case 26991://! Lens-Z축 대기 위치 이동
#if (____AA_WAY == PCB_TILT_AA)
		if (sysData.m_iEpoxyLaserInspPass == 1)
		{
			iRtnFunction = 30000;	//도포이동
		}
		else
		{
			iRtnFunction = 27000;	//Laser측정 ->Align -> 도포
		}
#elif (____AA_WAY == LENS_TILT_AA)
		if (sysData.m_iEpoxyLaserInspPass == 1)
		{
			iRtnFunction = 30000;//Laser 측정 Pass
		}
		else
		{
			iRtnFunction = 27000;
		}
#endif
		break;
	default:
		logStr.Format("Lens 외부 Align Thread Step 번호 비정상 [%d]", iUseStep);
		errMsg2(Task.AutoFlag, logStr);
		iRtnFunction = -1;
		break;
	}
	logStr.Empty();
	return iRtnFunction;
}

int	CPcbProcess2::RunProc_LaserMeasure(int iUseStep)
{
	int iRtnFunction = iUseStep;
	int iRtn = 0;
	CString logStr = "";
	bool bChk = true;
	double offsetX = 0.0, offsetY = 0.0, offsetTh = 0.0;
	int iCamDelay = model.strInfo_Cam[1].m_iDelayTime;	//PCB 영상 획득 Delay
	int iAlignRetry = model.strInfo_Cam[1].m_iRetryCnt;
	int iLaserDelay = model.strInfo_Cam[0].m_iDelayTime;	//Laser 측정전 Delay
	switch (iUseStep)
	{
	case 27000:
		Task.oldLaserTx = 0.1;
		Task.oldLaserTy = 0.1;
		iLaser_Pos = 0;// 4;//4번부터가 laser out point


		LightControl.ctrlLedVolume(LIGHT_PCB, 0);		// Align만 조명 ON


		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("[운전 준비] PCB Z축 대기위치 이동 실패[%d]", iUseStep);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -27000;
			break;
		}
		LightControl.ctrlLedVolume(LIGHT_OC, 0);



		MandoInspLog.dLaserTestTilt[0] = 0.0;
		MandoInspLog.dLaserTestTilt[1] = 0.0;
		iRtnFunction = 27100;// 27350;//<-임시 패스   Original-> 27100; 
		break;

	case 27100:
		if (motor.Pcb_Motor_Move_Laser(iLaser_Pos, Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]))
		{
			Task.PCBTaskTime = myTimer(true);
			logStr.Format("Laser 변위 측정 외부 위치 이동 완료[%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = 27150;
		}
		else
		{
			logStr.Format("Laser 변위 측정 외부 위치 이동 실패[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -27100;
		}
		break;
	case 27150:
		iRtnFunction = 27151;
		break;
	case 27151:
		if (iLaser_Pos == 0)
		{
			if (!motor.PCB_Z_Motor_Move(Laser_Pcb_Pos))
			{
				logStr.Format("PCB Laser_Pcb_Pos Z 이동 실패[%d]", iUseStep);
				putListLog(logStr);
				errMsg2(Task.AutoFlag, logStr);
				iRtnFunction = -27151;
				break;
			}
			else
			{
				logStr.Format("PCB Laser_Pcb_Pos Z 이동 완료[%d]", iUseStep);
				putListLog(logStr);
			}
		}
		iRtnFunction = 27200;
		Task.PCBTaskTime = myTimer(true);
		break;
	case 27200:
		if ((myTimer(true) - Task.PCBTaskTime) > iLaserDelay && (motor.IsStopAxis(Motor_PCB_X) && motor.IsStopAxis(Motor_PCB_Y)))
		{
			Sleep(200);
			iRtnFunction = 27250;
		}
		break;
	case 27250:
		//Keyence.func_CL3000_Scan(Task.m_Laser_Point[iLaser_Pos]);
		Keyence.func_LT9030_Scan(Task.m_Laser_Point[iLaser_Pos]);  //func_LT9030_Scan

		Sleep(100);

		logStr.Format("변위센서 %lf - %d 위치[%d]", Task.m_Laser_Point[iLaser_Pos], iLaser_Pos + 1, iUseStep);
		putListLog(logStr);

		LaserPos[iLaser_Pos].x = motor.GetEncoderPos(Motor_PCB_X);
		LaserPos[iLaser_Pos].y = motor.GetEncoderPos(Motor_PCB_Y);
		LaserValue[iLaser_Pos] = Task.m_Laser_Point[iLaser_Pos];

		MandoInspLog.dLaserTestPoint[iLaser_Pos] = Task.m_Laser_Point[iLaser_Pos];
		
		if (Task.m_Laser_Point[iLaser_Pos] != 0)
		{
			if (iLaser_Pos == 3)
			{
				if (theApp.MainDlg->func_Check_LaserValueErr(LaserValue) == false)
				{
					logStr.Format("Laser 측정값이상: %.04lf, %.04lf, %.04lf, %.04lf [%d]", LaserValue[0], LaserValue[1], LaserValue[2], LaserValue[3], iUseStep);
					errMsg2(Task.AutoFlag, logStr);
					iRtnFunction = -27250;
					break;
				}

				if (theApp.MainDlg->_calcLaserTilt(LaserPos, LaserValue, Task.d_Align_offset_xt[PCB_Chip_MARK], Task.d_Align_offset_yt[PCB_Chip_MARK]))
				{
					Task.m_dataOffset_x[0] = Task.d_Align_offset_xt[PCB_Chip_MARK];
					Task.m_dataOffset_y[0] = Task.d_Align_offset_yt[PCB_Chip_MARK];
					logStr.Format("	보정량 Tx: %.04lf, Ty: %.04lf", Task.d_Align_offset_xt[PCB_Chip_MARK], Task.d_Align_offset_yt[PCB_Chip_MARK]);
					putListLog(logStr);

					int Rnd = theApp.MainDlg->TiltAlignLimitCheck(Task.d_Align_offset_xt[PCB_Chip_MARK], Task.d_Align_offset_yt[PCB_Chip_MARK]);
					if (Rnd == 2)
					{
						if (Task.m_dataOffset_x[0] == 0.0 || Task.m_dataOffset_y[0] == 0.0)
						{
							logStr.Format("Laser 변위 차 값 이상 발생..Xt : %lf, Yt : %lf", Task.m_dataOffset_x[0], Task.m_dataOffset_y[0]);
							//errMsg2(Task.AutoFlag, logStr);
							//iRtnFunction = -27250;
							//break;
						}
						if (!g_ADOData.func_AATaskToRecordLaser(Task.ChipID, Task.m_dataOffset_x[0], Task.m_dataOffset_y[0], Task.m_Laser_Point))
						{
							logStr.Format("DataBase Laser 변위 측정 Data 기록 실패.[%d]\n MS Office를 닫아주세요.", iUseStep);
							errMsg2(Task.AutoFlag, logStr);
							iRtnFunction = -27250;
							break;
						}
						Task.m_PcbLaserAfterTx = motor.GetCommandPos(Motor_PCB_Xt);
						Task.m_PcbLaserAfterTy = motor.GetCommandPos(Motor_PCB_Yt);

						logStr.Format("	PCB Laser tx:%lf , ty:%lf [%d]", model.axis[Motor_PCB_Xt].pos[Laser_Pcb_Pos], model.axis[Motor_PCB_Yt].pos[Laser_Pcb_Pos], iUseStep);
						putListLog(logStr);
						logStr.Format("	PCB Laser After tx:%lf , ty:%lf [%d]", Task.m_PcbLaserAfterTx, Task.m_PcbLaserAfterTy, iUseStep);
						putListLog(logStr);

						iRtnFunction = 27310;	//->Laser실린더상승, 27350;->PCB WaitPos
						iLaser_Pos++;
					}
					else if (Rnd == 1)
					{
						iRtnFunction = 27300;
					}
					else
					{
						logStr.Format("Laser Tilt  보정값 Limit를 초과 하였습니다.[%d]", iUseStep);
						errMsg2(Task.AutoFlag, logStr);
						iRtnFunction = -27250;
					}
				}
			}
			else
			{
				iRtnFunction = 27100;
				iLaser_Pos++;
			}
		}
		else
		{
			iRtnFunction = 27250;
		}
		break;
	case 27300:
		MandoInspLog.dLaserTestTilt[0] += Task.d_Align_offset_xt[PCB_Chip_MARK];
		MandoInspLog.dLaserTestTilt[1] += Task.d_Align_offset_yt[PCB_Chip_MARK];

		if (motor.Pcb_Move_Tilt(Task.d_Align_offset_xt[PCB_Chip_MARK], Task.d_Align_offset_yt[PCB_Chip_MARK]))
		{
			iRtnFunction = 27100;
			logStr.Format("PCB Xt : %lf, Yt : %lf [%d]", Task.d_Align_offset_xt[PCB_Chip_MARK], Task.d_Align_offset_yt[PCB_Chip_MARK], iUseStep);
			putListLog(logStr);
			iLaser_Pos = 0;
		}
		else
		{
			logStr.Format("PCB tx,ty축  위치 이동 실패[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -27300;
		}
		break;

	case 27310:
		logStr.Format("PCB Laser End Xt : %lf, Yt : %lf [%d]", MandoInspLog.dLaserTestTilt[0], MandoInspLog.dLaserTestTilt[1], iUseStep);
		putListLog(logStr); 

		iLaser_Pos = 0;
		if (LGIT_MODEL_INDEX == M2_FF_MODULE)	//외부 레이저 포인트 측정만
		{
			iRtnFunction = 27315;
		}
		else
		{
			iRtnFunction = 27350;		//jump step
		}
		Task.PCBTaskTime = myTimer(true);
		break;
	case 27315:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("[운전 준비] PCB Z축 대기위치 이동 실패[%d]", iUseStep);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -27315;
			break;
		}
		if (LGIT_MODEL_INDEX == M2_FF_MODULE)
		{
			iRtnFunction = 27320;		//한번더 다른 위치 레이저 포인트 측정만
		}
		else
		{
			iRtnFunction = 27340;
		}
		break;
	case 27320:
		if (motor.Pcb_Motor_Move_ComLaser(iLaser_Pos, Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]))
		{
			logStr.Format("Com Laser 변위 측정 외부 위치 이동 완료[%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = 27325;

			Task.PCBTaskTime = myTimer(true);
		}
		else
		{
			logStr.Format("Com Laser 변위 측정 외부 위치 이동 실패[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -27320;
		}
		
		
		break;
	case 27325:
		if (iLaser_Pos == 0)
		{
			if (!motor.PCB_Z_Motor_Move(Com_Laser_Pos))
			{
				logStr.Format("PCB Com Laser_Pcb_Pos Z 이동 실패[%d]", iUseStep);
				putListLog(logStr);
				errMsg2(Task.AutoFlag, logStr);
				iRtnFunction = -27325;
				break;
			}
			else
			{
				logStr.Format("PCB Laser_Pcb_Pos Z 이동 완료[%d]", iUseStep);
				putListLog(logStr);
			}
		}
		iRtnFunction = 27330;
		Task.PCBTaskTime = myTimer(true);
		break;
	case 27330:
		if ((myTimer(true) - Task.PCBTaskTime) > iLaserDelay && (motor.IsStopAxis(Motor_PCB_X) && motor.IsStopAxis(Motor_PCB_Y)))
		{
			Sleep(200);
			iRtnFunction = 27332;
		}
		
		break;
	case 27332:
		Keyence.func_LT9030_Scan(Task.m_Laser_Point[iLaser_Pos]);  //func_LT9030_Scan
		//Keyence.func_CL3000_Scan(Task.m_Laser_Point[iLaser_Pos]);
		Sleep(100);
		logStr.Format("Side 변위센서 %lf - %d 위치[%d]", Task.m_Laser_Point[iLaser_Pos], iLaser_Pos + 1, iUseStep);
		putListLog(logStr);

		MandoInspLog.dLaserTestComPoint[iLaser_Pos] = Task.m_Laser_Point[iLaser_Pos];
		
		if (Task.m_Laser_Point[iLaser_Pos] != 0)
		{
			if (iLaser_Pos == 3)
			{
				iRtnFunction = 27340;
				break;
			}
			else
			{
				iRtnFunction = 27320;
				iLaser_Pos++;
				break;
			}
		}
		else
		{
			iRtnFunction = 27332;
		}
		break;
	case 27340:
		iRtnFunction = 27350;
		break;
	case 27350:
		if (motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("PCB Z축 대기 위치 이동 완료[%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = 27351;
		}
		else
		{
			logStr.Format("PCB Z축 대기 위치 이동 실패[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -27350;
		}

		break;
	case 27351:
		//if ((sysData.m_iDispensePass == 1) || (Task.m_bOkDispense == 1))
		//{
		//	iRtnFunction = 31000;	//-- 도포 Pass Mode 이거나, 도포 완료 일 경우
		//}
		//else
		//{
		//	iRtnFunction = 30020;
		//}
		iRtnFunction = 27600;
		break;
	case 27600:

		iRtnFunction = 27650;
		break;
	case 27650:
		offsetX = offsetY = offsetTh = 0.0;
		iRtnFunction = 27750;
		break;
	case 27750:
		iRtnFunction = 27960;		// 완료 임시
									//
									//
									//
		break;


#if 0


		Task.m_iRetry_Opt = 0;
		iRtnFunction = 27800;
		break;
	case 27800:
		theApp.MainDlg->ctrlSubDlg(MAIN_DLG);
		theApp.MainDlg->m_iCurCamNo = 0;
		LightControl.ctrlLedVolume(LIGHT_PCB, model.m_iLedValue[LEDDATA_SENSOR]);		// Align만 조명 ON

		if (motor.Pcb_Motor_Move(Align_Pos))
		{
			if (motor.PCB_Z_Motor_Move(Align_Pos))
			{
				logStr.Format("PCB Sensor Align 위치 이동 완료[%d]", iUseStep);
				putListLog(logStr);
				Task.d_Align_offset_x[PCB_Chip_MARK] = 0;
				Task.d_Align_offset_y[PCB_Chip_MARK] = 0;
				Task.d_Align_offset_th[PCB_Chip_MARK] = 0;
				iRtnFunction = 27850;
				Task.PCBTaskTime = myTimer(true);
			}
		}
		else
		{
			logStr.Format("PCB Sensor Align 위치 이동 실패 [%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -27960;
		}
		break;
	case 27850:
		if ((myTimer(true) - Task.PCBTaskTime) > iCamDelay && (motor.IsStopAxis(Motor_PCB_X) && motor.IsStopAxis(Motor_PCB_Y)))
		{
			iRtnFunction = 27900;
		}
		break;
	case 27900:
		if (Task.m_iRetry_Opt>iAlignRetry)
		{
			logStr.Format("PCB Align(*Laser*) 재검사 %d 회 실패[%d]\n 보정 미적용으로 진행하시겠습니까?", Task.m_iRetry_Opt, iUseStep);
			Task.m_iRetry_Opt = 0;
			Task.d_Align_offset_x[PCB_Chip_MARK] = 0.0;
			Task.d_Align_offset_y[PCB_Chip_MARK] = 0.0;
			Task.d_Align_offset_th[PCB_Chip_MARK] = 0.0;
			if (askMsg(logStr) == IDOK)
			{
				iRtnFunction = 27960;
				logStr.Format("PCB Align 미보정 진행[%d]", iUseStep);
				putListLog(logStr);
			}
			else
			{
				iRtnFunction = 27900;
				logStr.Format("PCB Align 재검사 시작[%d]", iUseStep);
				putListLog(logStr);
				Sleep(500);
			}
			break;
		}

		offsetX = offsetY = offsetTh = 0.0;

		iRtn = theApp.MainDlg->procCamAlign(CAM2 - 1, PCB_Chip_MARK, false, offsetX, offsetY, offsetTh);

		saveInspImage(CHIP_IMAGE_SAVE, Task.m_iRetry_Opt);
		Task.m_iRetry_Opt++;
		//offsetTh=0;
		if (iRtn == 0)
		{
			/*Task.d_Align_offset_x[PCB_Chip_MARK] -= offsetX;
			Task.d_Align_offset_y[PCB_Chip_MARK] -= offsetY;
			Task.d_Align_offset_th[PCB_Chip_MARK] -= offsetTh;*/

			Task.d_Align_offset_x[PCB_Holder_MARK] -= offsetX;
			Task.d_Align_offset_y[PCB_Holder_MARK] -= offsetY;
			Task.d_Align_offset_th[PCB_Holder_MARK] += offsetTh;			//lim

			Task.dPcbAlignTh = Task.d_Align_offset_th[PCB_Chip_MARK];
			logStr.Format("PCB Sensor Align : %.3lf %.3lf %.3lf", Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]);
			putListLog(logStr);

			int iRtnVal = theApp.MainDlg->AlignLimitCheck(CAM2 - 1, offsetX, offsetY, offsetTh);

			if (iRtnVal == 1)
			{
				iRtnFunction = 27950;				// 보정 이동
			}
			else if (iRtnVal == 2)
			{
				logStr.Format("		PCB Sensor Align [%d] 완료 [%d]", Task.m_iRetry_Opt, iUseStep);
				putListLog(logStr);
				logStr.Format("		PCB Sensor Align Complete : %d, %.03f, %.03f, %.03f", Task.m_iPcbPickupNo, Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]);
				AlignResultSave(logStr);
				Task.m_iRetry_Opt = 0;

				Task.m_timeChecker.Measure_Time(4);	//Laser 변위 측정 시작 시간


				iRtnFunction = 27960;		// 완료
				LightControl.ctrlLedVolume(LIGHT_PCB, 0);		// Align만 조명 ON 
				LightControl.ctrlLedVolume(LIGHT_OC, 0);		// Align만 조명 ON
			}
			else
			{
				logStr.Format("PCB Sensor Align [%d] 보정 범위 초과 [%d]", Task.m_iRetry_Opt, iUseStep);
				errMsg2(Task.AutoFlag, logStr);
				AlignLogSave(logStr);
				iRtnFunction = -27900;				// NG
			}
		}
		else
		{
			logStr.Format("PCB Sensor Align(*Laser*) [%d] 마크 인식 실패[%d]", Task.m_iRetry_Opt, iUseStep);
			putListLog(logStr);
			Sleep(500);
			iRtnFunction = 27900;				//  재검사 
		}
		break;
	case 27950:
		if (motor.Pcb_Holder_Align_Move(Align_Pos, Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]))
		{
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 27850;
		}
		else
		{
			logStr.Format("PCB Sensor Align 보정 위치 이동 실패[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -27950;
		}
		break;

#endif

	case 27960:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("PCB부 Z축 대기 위치 이동 실패[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -27960;
			break;
		}
		else
		{
			logStr.Format("PCB부 Z축 대기 위치 이동 완료[%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = 27970;
		}

		break;
	case 27970:
		iRtnFunction = 27990;
		break;
	case 27990:
		iRtnFunction = 30000;
		break;
	default:
		logStr.Format("Pcb Thread Step 번호 비정상 .[%d]", iUseStep);
		errMsg2(Task.AutoFlag, logStr);
		iRtnFunction = -1;
		break;
	}
	return iRtnFunction;
}

int CPcbProcess2::RunProc_EpoxyNewResing(int iUseStep)
{//! Epoxy 동작 및 도포 검사 Step(17000 ~ 17999)
	int iRtnFunction = iUseStep;
	int iCamDelay = model.strInfo_Cam[1].m_iDelayTime;		//PCB 영상 획득 Delay
	int iRtn = 0;
	CString logStr = "";
	bool bChk = true;
	double offsetX = 0.0, offsetY = 0.0, offsetTh = 0.0;
	int iLaserDelay = model.strInfo_Cam[0].m_iDelayTime;	//Laser 측정전 Delay
	int iAlignRetry = model.strInfo_Cam[1].m_iRetryCnt;

	switch (iUseStep)
	{
	case 30000:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("PCB_Z축 대기위치 이동 실패[%d].", iUseStep);
			putListLog(logStr);
			iRtnFunction = -30000;
			break;
		}
		logStr.Format("PCB Z Wait 위치 이동 완료 [%d]", iUseStep);
		putListLog(logStr);

		if ((sysData.m_iDispensePass == 1) || (Task.m_bOkDispense == 1))
		{
			iRtnFunction = 34100;// 31000;	//-- 도포 Pass Mode 이거나, 도포 완료 일 경우
			break;
		}
		else
		{
			iRtnFunction = 30020;
			break;
		}
		break;
	case 30020:
		iRtnFunction = 30030;
		break;
	case 30030:  //도포 위치 이동
		LightControl.ctrlLedVolume(LIGHT_PCB, 0);		// Align 조명 OFF
		if (motor.Pcb_Motor_Move(Dispense_Pos, Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]))
		{
			logStr.Format("PCB Dispense 보정 위치 이동 완료-보정량 X:%.03lf,Y:%.03lf,T:%.03lf", Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]);
			putListLog(logStr);
			iRtnFunction = 30040;
		}
		else
		{
			logStr.Format("PCB Dispense 위치 이동 실패 [%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -30030;
		}
		break;
	case 30040:

		iRtnFunction = 30045;
		break;

	case 30045: //Dispenser-z 축 상승
		if (motor.PCB_Z_Motor_Move(Dispense_Pos))
		{
			iRtnFunction = 30050;
		}
		else
		{
			logStr.Format("PCB Z Dispense 위치 이동 실패[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -30045;
		}
		break;
	case 30050: // 디스펜스 동작

		if (sysData.nEpoxyIndex == CRICLE_EPOXY)
		{
			bChk = motor.func_Epoxy_CircleDraw();
		}
		else if (sysData.nEpoxyIndex == RECT_EPOXY)
		{
			bChk = motor.func_Epoxy_Draw();
		}
		else if (sysData.nEpoxyIndex == POLYGON_EPOXY)
		{
			motor.func_Epoxy_Rect_Circle_Draw();
		}
		else if (sysData.nEpoxyIndex == POINT_EPOXY)
		{
			//point 형
			logStr.Format("PCB 설정 미지정 실패 [%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -30050;
			break;
		}

		if (bChk)
		{
			Task.m_bOkDispense = 1;

			logStr.Format("PCB Dispense 완료[%d]", iUseStep);
			putListLog(logStr);

			iRtnFunction = 30070;
		}
		else
		{
			logStr.Format("PCB Dispense 실패 [%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -30050;
		}
		break;
	case 30070:
		if (motor.IsStopAxis(Motor_PCB_X) && motor.IsStopAxis(Motor_PCB_Y))
		{
			iRtnFunction = 30100;
		}
		break;
	case 30100:
		iRtnFunction = 31000;
		break;
	case 31000:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format(" PCB Z축 대기위치 이동 실패[%d]", iUseStep);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -31000;
			break;
		}
		else
		{
			logStr.Format("PCB Z 대기 위치 이동 완료[%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = 32000;
			break;
		}
		break;
	case 32000:
		iRtnFunction = 32100;
		break;

	case 32100: // 도포검사 이동

		if (motor.Pcb_Motor_Move(Holder_Pos))
		{
			LightControl.ctrlLedVolume(LIGHT_PCB, model.m_iLedValue[LEDDATA_HOLDER]);		//홀더 조명 변경
			iRtnFunction = 32500;
		}
		else
		{
			logStr.Format("PCB 도포검사 위치 이동 실패[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -32100;
		}
		break;

	case 32500:// 이동후, 일정 시간 지연 및 마크 확인
		if (motor.PCB_Z_Motor_Move(Holder_Pos))

		{
			Task.PCBTaskTime = myTimer(true);
			logStr.Format("PCB 도포검사 위치 이동 완료 [%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = 33000;
		}
		else
		{
			logStr.Format("PCB 도포검사 위치 이동 실패 [%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -32500;
		}
		break;
	case 33000: //도포검사 z축 이동

		if ((myTimer(true) - Task.PCBTaskTime) > 1000 && (motor.IsStopAxis(Motor_PCB_X) && motor.IsStopAxis(Motor_PCB_Y)))
		{
#if 1
			vision.bmpImageSaveFn(CAM1, 0);
			iRtnFunction = 33500;

			Task.PCBTaskTime = myTimer(true);
			break;
#else
			Sleep(300);
			int iMarkNo = 0;
			CString sTemp = "";

			vision.clearOverlay(CAM1);

			if (vision.getLiveMode())
			{
				vision.getSnapImage(CAM1);
				vision.setLiveMode(true);
			}

			double ep1 = 0.0;
			MappTimer(M_TIMER_RESET, &ep1);
			iMarkNo = vision.findMark(CAM1, PCB_Holder_MARK);

			double ep2 = 0.0;
			MappTimer(M_TIMER_READ, &ep2);
			sTemp.Format(" %.3lf sec", ep2 - ep1);
			vision.textlist[CAM1].addList((CAM_SIZE_X - 140), (CAM_SIZE_Y - 60), sTemp, M_COLOR_GREEN, 24, 10, "Arial");

			vision.drawOverlay(CAM1);

			if (iMarkNo != -1)
			{
#ifdef USE_GEOMETRIC
				MgraColor(M_DEFAULT, M_COLOR_GREEN);
				MmodDraw(M_DEFAULT, vision.ModResult[PCB_Holder_MARK][iMarkNo], vision.MilOverlayImage[CAM1], M_DRAW_BOX + M_DRAW_POSITION + M_DRAW_EDGES + M_DRAW_AXIS, M_DEFAULT, M_DEFAULT);

#endif
			}
			CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
			pFrame->m_rBox.left = 0;
			pFrame->m_rBox.top = 0;
			pFrame->m_rBox.right = 0;
			pFrame->m_rBox.bottom = 0;
			iRtnFunction = 33500;
#endif
			
		}
		break;
	case 33500: // 
		if ((myTimer(true) - Task.PCBTaskTime) > 300)
		{
			iRtnFunction = 33600;
		}
		break;

	case 33600:
		offsetX = offsetY = offsetTh = 0.0;
		iRtn = theApp.MainDlg->procCamAlign(CAM1, PCB_Holder_MARK, false, offsetX, offsetY, offsetTh);
		if (iRtn == 0)
		{
			LightControl.ctrlLedVolume(LIGHT_PCB, model.m_iLedValue[LEDDATA_EPOXY_INSP]);		//도포 검사 조명 변경
			iRtnFunction = 33620;
			Task.PCBTaskTime = myTimer(true);
			break;
		}
		else
		{
			logStr.Format("PCB Holder 검사 실패\n 보정 미적용으로 진행하시겠습니까?");
			putListLog(logStr);
			if (askMsg(logStr) == IDOK)
			{
				Task.d_mark_pos_x[PCB_Holder_MARK][0] = 0.0;
				Task.d_mark_pos_y[PCB_Holder_MARK][0] = 0.0;
				iRtnFunction = 33620;
				break;
			}

			logStr.Format("Pcb Holder 마크 인식 실패[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -33600;				// NG
			break;
		}
		break;
	case 33620:
		if ((myTimer(true) - Task.PCBTaskTime) > 500)
		{
			iRtnFunction = 33700;
		}
		
		break;

	case 33700:
		iRtnFunction = 33800;
		break;
	case 33800:
		iRtnFunction = 33900;
		break;

	case 33900: //도포검사 
		

		vision.clearOverlay(CAM1);

		bChk = theApp.MainDlg->_EpoxyFinddispense(CAM1);		//auto

		vision.drawOverlay(CAM1);
		if (!bChk)
		{
			putListLog("Epoxy 도포 검사 실패");

			logStr.Format("Epoxy 도포 검사 실패. \n자동 운전 진행 하시겠습니까?");

			Dio.setAlarm(ALARM_ON);
			if (askMsg(logStr))
			{
				Task.PCBTaskTime = myTimer(true);
				Dio.setAlarm(ALARM_OFF);
				Dio.setAlarm(AUTO_RUN);
			}
			else
			{
				Dio.setAlarm(AUTO_STOP);
				logStr.Format("Epoxy 도포 검사 실패[%d]", iUseStep);
				iRtnFunction = -33900;
				break;
			}
		}
		Task.m_timeChecker.Measure_Time(3);	//도포 완료 시간
		Task.m_dTime_Epoxy = Task.m_timeChecker.m_adTime[3] - Task.m_timeChecker.m_adTime[2];
		theApp.MainDlg->dispGrid();

		logStr.Format("PCB 도포검사 완료[%d]", iUseStep);
		putListLog(logStr);

		iRtnFunction = 34000;
		break;
	case 34000:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("PCB_Z축 대기위치 이동 실패 [%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = -34000;
			break;
		}

		iRtnFunction = 34100;
		break;
	case 34100:

#if (____AA_WAY == PCB_TILT_AA)
		iRtnFunction = 39000;
#elif (____AA_WAY == LENS_TILT_AA)
		iRtnFunction = 35000;
#endif
		break;
	default:
		logStr.Format("PCB Dispenser Thread Step 번호 비정상 [%d]", iUseStep);
		errMsg2(Task.AutoFlag, logStr);
		iRtnFunction = -1;
		break;
	}

	return iRtnFunction;
}

int CPcbProcess2::RunProc_InspAAPos(int iUseStep)
{
	//! Lens Pickup에 제품 넘김 Step	(18000 ~ 19999)

	int iRtnFunction = iUseStep;
	int iRtn = 0;
	CString logStr = "";
	double	dFinalDelay = (double)(model.strInfo_Cam[3].m_iDelayTime);
	bool bChk = true;
	double offsetX = 0.0, offsetY = 0.0, offsetTh = 0.0;

	switch (iUseStep)
	{
	case 40000:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format(_T("PCB Z axis Wait Pos Move Failed [%d]"), iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -40000;
			break;
		}

		iRtnFunction = 40050;
		break;
	case 40050:
		//240108 동시 이동 pcb 본딩위치
		logStr.Format("PCB %s 이동 명령[%d] ", MotorPosName[Bonding_Pos], iUseStep);
		putListLog(logStr);

		if (!motor.Pcb_Motor_Move(Bonding_Pos, Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK], false))	//if (!motor.Pcb_Motor_MoveY(Bonding_Pos))
		{
			logStr.Format("PCB %s 이동 명령 실패 ", MotorPosName[Bonding_Pos]);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -40050;
			break;
		}
		Task.PCBTaskTime = myTimer(true);
		iRtnFunction = 40060;

	case 40060:


#if (____AA_WAY == PCB_TILT_AA)
		iRtnFunction = 41000;

#elif (____AA_WAY == LENS_TILT_AA)
		iRtnFunction = 41000;


		//if (Task.interlockLens == 1 && Task.m_bOKLensPass == 1)
		//{
		//	iRtnFunction = 40000;/// 41000;		//2호기 렌즈는 Lens Thread에서 로드
		//	break;
		//}
		//if ((myTimer(true) - Task.PCBTaskTime) > 10000)	//10초 대기
		//{
		//	logStr.Format(_T("Lens Load 확인 실패[%d]"), iUseStep);
		//	errMsg2(Task.AutoFlag, logStr);
		//	iRtnFunction = -39999;
		//	break;
		//}

#endif		
		break;
	default:
		logStr.Format("Pcb Align 동작 Thread Step 번호 비정상 . [%d]", iUseStep);
		errMsg2(Task.AutoFlag, logStr);
		iRtnFunction = -1;
		break;
	}
	logStr.Empty();
	return iRtnFunction;
}

int CPcbProcess2::RunProc_Bonding_Pos_GO(int iUseStep)
{//! Lens Pickup에 제품 넘김 Step	(18000 ~ 19999)
	int iRtnFunction = iUseStep;
	int iRtn = 0;
	CString logStr = "";
	double	dFinalDelay = (double)(model.strInfo_Cam[3].m_iDelayTime);
	bool bChk = true;
	double offsetX = 0.0, offsetY = 0.0, offsetTh = 0.0;

	switch (iUseStep)
	{
	case 41000:
		/*if (sysData.m_iIrChartUse == 1)
		{
			LightControl.ctrlLedVolume(0,0);
			Sleep(100);
			LightControl.ctrlLedVolume(0, model.m_iLedValue[LEDDATA_TOP2_CHART]);
		}*/

		LightControl.ChartAllControl(true);

		iRtnFunction = 41020;
		Task.PCBTaskTime = myTimer(true);
		break;
	case 41020:
		iRtnFunction = 41030;
		break;
	case 41030:
		if ((motor.IsStopAxis(Motor_PCB_X) && motor.IsStopAxis(Motor_PCB_Y) && motor.IsStopAxis(Motor_PCB_TH)))
		{
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 41050;
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > 3000)
		{
			logStr.Format(_T("PCB x,y,th axis 정지 확인 실패[%d]"), iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -41030;
		}
		break;
	case 41050:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format(_T("PCB Z axis Wait Pos Move Failed [%d]"), iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -41050;
		}
		else
		{
			iRtnFunction = 41100;
		}
		break;
	case 41100:
		if (sysData.m_iEpoxyLaserInspPass == 1)
		{
			//LASER PASS
			if (motor.Pcb_Tilt_Motor_Move(Bonding_Pos))
			{
				logStr.Format("PCB TX,TY Bonding_Pos 이동 완료 [%d]", iUseStep);
				putListLog(logStr);
				Task.PCBTaskTime = myTimer(true);
				iRtnFunction = 41150;
			}
			else
			{
				logStr.Format(_T("PCB Tilt Bonding Pos Move Fail[%d]"), iUseStep);
				errMsg2(Task.AutoFlag, logStr);
				iRtnFunction = -41100;
				break;
			}
		}
		else
		{
			//레이저 보정을 한경우 보정한 PCB TX,TY 값으로 다시 이동
			if (motor.Pcb_Tilt_Trinity_Move(Task.m_PcbLaserAfterTx, Task.m_PcbLaserAfterTy))
			{
				Task.PCBTaskTime = myTimer(true);
				iRtnFunction = 41150;
			}
			else
			{
				logStr.Format(_T("PCB Tilt Bonding Pos Move Fail[%d]"), iUseStep);
				errMsg2(Task.AutoFlag, logStr);
				iRtnFunction = -41100;
				break;
			}
		}
		
		break;
	case 41150:
		iRtnFunction = 41200;

		break;
	case 41200:
		iRtnFunction = 41220;

		break;
	case 41220:
#if (____AA_WAY == PCB_TILT_AA)
		if (motor.Pcb_Motor_Move(Bonding_Pos, Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]))
		{
			sLangChange.LoadStringA(IDS_STRING913);	//"PCB Bonding 위치 이동 완료[%d]"
			logStr.Format(sLangChange, iUseStep);
			putListLog(logStr);
			iRtnFunction = 41250;
			if (!motor.Pcb_Tilt_Motor_Move(Bonding_Pos))
			{
				logStr.Format("PCB tx,ty Bonding_Pos 이동 실패");
				delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
				iRtnFunction = -41200;
				break;
			}
			break;
		}
		else
		{
			sLangChange.LoadStringA(IDS_STRING912);	//PCB Bonding 위치 이동 실패
			logStr.Format(sLangChange + _T("[%d]"), iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -41200;
			break;
		}
#elif	(____AA_WAY == LENS_TILT_AA)
		if (motor.Pcb_Motor_Move(Bonding_Pos, Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]))
		{
			logStr.Format("PCB Bonding 위치 이동 완료[%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = 41250;
			Task.PCBTaskTime = myTimer(true);
		}
		else
		{
			logStr.Format("PCB Bonding 위치 이동 실패 [%d]", iUseStep);
			putListLog(logStr);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -41200;
		}
#endif
		break;
	case 41250:
		iRtnFunction = 41270;
		break;
	case 41270:

		if (motor.Lens_Motor_MoveXY(Bonding_Pos))
		{
#if (____AA_WAY == LENS_TILT_AA)
			if (!motor.Lens_Tilt_Motor_Move(Bonding_Pos))
			{
				logStr.Format("Lens %s Tx,Ty이동 실패", MotorPosName[Bonding_Pos]);
				delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
				iRtnFunction = -41200;
				break;
			}
			else
			{
				Task.interlockPcb = 1;

				logStr.Format("Lens TX,TY Bonding_Pos 이동 완료 [%d]", iUseStep);
				putListLog(logStr);
			}

#endif
			logStr.Format("Lens X,Y Bonding 위치 이동 완료[%d]", iRtnFunction);
			putListLog(logStr);
			
			iRtnFunction = 41300;
			break;
		}
		else
		{
			logStr.Format("Lens Bonding 위치 이동 실패[%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -41250;
			break;
		}
		break;
	case 41300:
		iRtnFunction = 41310;

		break;
	case 41310:
		if (Task.interlockPcb == 1)		//pcb틸트일 경우  렌즈 레이저,얼라인 작업 끝난후 본딩위치 올때까지 기다려야돼서
		{
			iRtnFunction = 41350;
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > 50000)
		{
			logStr.Format("Lens Bonding 위치 이동 시간 초과[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -41310;
		}
		break;
	case 41350:
		iRtnFunction = 41400;

		break;
	case 41400:
		//if( func_MIU_ConnectLiveCheck() == false)		//MIU 영상 Check				
		//{
		//	iRtnFunction = -41400;
		//	break;
		//}

		theApp.MainDlg->setCamDisplay(3, 1);
		iRtnFunction = 48000;

		break;
	case 48000:

		logStr.Format("Loading End[%d]", iUseStep);
		putListLog(logStr);
		iRtnFunction = 49000;
		break;
		//
	default:
		logStr.Format("Pcb Align 동작 Thread Step 번호 비정상 . [%d]", iUseStep);
		errMsg2(Task.AutoFlag, logStr);
		iRtnFunction = -1;
		break;
	}
	logStr.Empty();
	return iRtnFunction;
}

int	CPcbProcess2::procAutoFocus(int iStep)
{
	int iRtn = 0;
	int iRtnFunction = 0;
	CString logStr = _T("");
	int iDelayTime = 0;

	bool limitCheckFlag = false;

	double dMovePos = 0.0;

	double dAutoZ = 0.0;

	if (iStep >= 60300 && iStep != 69999)
	{
		if (gMIUDevice.bMIUOpen == 0 || gMIUDevice.CurrentState != 4)				//DRY_RUN
		{
			logStr.Format("CCD 동영상 정지 상태입니다.");
			errMsg2(Task.AutoFlag, logStr);
			return iStep;
		}
	}

	if (Task.m_bFlag_Fine_Move == false)
	{
		iDelayTime = model.strInfo_AF1.m_iDelayTime;
	}
	else
	{
		iDelayTime = model.strInfo_AF2.m_iDelayTime;
	}

	iRtnFunction = iStep;

	switch (iStep)
	{
	case 60000:
	{
		MbufClear(vision.MilOptImage, 0x00);
		MbufClear(vision.MilDefectImage, 0x00);

		Task.initSFRElem();
		theApp.MainDlg->autodispDlg->dispCurTaskOnLabel(1, "-");
		theApp.MainDlg->autodispDlg->DrawGraph(0);
		theApp.MainDlg->autodispDlg->DrawGraph(1);


		MandoInspLog.bInspRes = true;	//60000 초기화
		Task.m_timeChecker.Measure_Time(6);	//AA 시작 시간
		iRtnFunction = 60010;
		Task.PCBTaskTime = myTimer(true);
	}
	break;
	case  60010:
		if (bThreadCCDRun == false)		//	CCD 영상 쓰레드 멈추면 진행... step = 12000 참고
		{
			iRtnFunction = 60015;
		}
		else
		{
			logStr.Format("CCD 영상 Open 진행중입니다[%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -60010;
		}
		break;
	case  60015:
		if (motor.LENS_Z_Motor_Move(Bonding_Pos))
		{
			logStr.Format("Lens Z Bonding 위치 이동 완료[%d]", iStep);
			putListLog(logStr);
			iRtnFunction = 60020;

		}
		else
		{
			logStr.Format("Lens Z Bonding 위치 이동 실패 [%d]", iStep);
			putListLog(logStr);
			iRtnFunction = -60015;
		}
		break;
	case 60020:
		if (!motor.PCB_Z_Motor_Move(Bonding_Pos))
		{
			logStr.Format("PCB Z축 Bonding 위치 이동 실패[%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -60020;
			break;
		}
		else
		{
			iRtnFunction = 60030;
			logStr.Format("PCB Z축 Bonding 위치 이동 완료[%d]", iRtnFunction);
			putListLog(logStr);
		}

		break;
	case 60030:
	{
		double MotorPos[2];

		MotorPos[0] = fabs(motor.GetEncoderPos(theApp.MainDlg->TITLE_MOTOR_X) - model.axis[theApp.MainDlg->TITLE_MOTOR_X].pos[Bonding_Pos]);
		MotorPos[1] = fabs(motor.GetEncoderPos(theApp.MainDlg->TITLE_MOTOR_Y) - model.axis[theApp.MainDlg->TITLE_MOTOR_Y].pos[Bonding_Pos]);

		if ((MotorPos[0] < model.axis[theApp.MainDlg->TITLE_MOTOR_X].m_dLimit_Err && MotorPos[1] < model.axis[theApp.MainDlg->TITLE_MOTOR_Y].m_dLimit_Err))
		{
			logStr.Format("PCB부 x,y 본딩 위치에 도달 완료[%d]", iStep);
			putListLog(logStr);
			iRtnFunction = 60040;
			logStr.Format("	AA Step [%d]", iRtnFunction);
			putListLog(logStr);
			break;
		}
		else
		{
			logStr.Format("Bonding 위치 이동 실패[%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -60030;
			break;
		}
	}
	break;

	case 60040:		/* PCB Z모터 본딩위치 이동 */
	{
		iRtn = theApp.MainDlg->_checkPcbMotor();
		if (iRtn > 0)
		{
			logStr.Format("Z 모터 본딩 위치 이동");
			theApp.MainDlg->autodispDlg->dispCurTaskOnLabel(1, logStr);

			theApp.MainDlg->setCamDisplay(3, 1);
			double dCurPos = 0.0;
			double dMovePos = model.axis[Motor_Lens_Z].pos[Bonding_Pos];
			motor.MoveAxis(Motor_Lens_Z, ABS, dMovePos, sysData.fMotorSpeed[Motor_Lens_Z], sysData.fMotorAccTime[Motor_Lens_Z]);
			double ep = myTimer(true);

			while (1)
			{
				if (myTimer(true) - ep < 5000)
				{
					if (motor.IsStopAxis(Motor_Lens_Z))	// && motor.GetInposition(Motor_Lens_Z) )
					{
						dCurPos = motor.GetCommandPos(Motor_Lens_Z);

						if (fabs(dCurPos - dMovePos) <= 0.003)
						{
							Task.PCBTaskTime = myTimer(true);

							logStr.Format("Auto Z Pass");
							putListLog(logStr);
							iRtnFunction = 60900;
							logStr.Format("	AA Step [%d]", iRtnFunction);
							putListLog(logStr);
							break;
						}
					}
				}
				else
				{
					putListLog("Auto Focusing 中 LENS Z Motor 이동 시간 초과.");
					iRtnFunction = -60040;
					break;
				}
			}
		}
		else
		{
			putListLog("PCB 가 본딩위치에 도달하지 못했습니다.");
			iRtnFunction = -60040;
			break;
		}
	}
	break;
	case 60070:		/* SFR 값이 연속으로 하락할 때, Z모터 이동 */
	{
		double dCurPos = 0.0;
		double dMovePos = model.axis[theApp.MainDlg->TITLE_MOTOR_Z].pos[Bonding_Pos] + model.m_dMove_Offset_Z;
		//연속으로 하락시 model.m_dMove_Offset_Z만큼 z축을 움직인다 
		if (fabs(model.m_dMove_Offset_Z) > 0.2)
		{
			logStr.Format("z축 이동치 Limit 초과 : Z : %.3lf", dMovePos);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -60070;
			break;
		}
		motor.MoveAxis(theApp.MainDlg->TITLE_MOTOR_Z, ABS, dMovePos, sysData.fMotorSpeed[theApp.MainDlg->TITLE_MOTOR_Z], sysData.fMotorAccTime[theApp.MainDlg->TITLE_MOTOR_Z]);
		double ep = myTimer(true);
		Task.m_bFlag_Fine_Move = false;
		while (1)
		{
			if (myTimer(true) - ep< 5000)
			{
				if (motor.IsStopAxis(theApp.MainDlg->TITLE_MOTOR_Z))// && motor.GetInposition(TITLE_MOTOR_Z))
				{
					dCurPos = motor.GetCommandPos(theApp.MainDlg->TITLE_MOTOR_Z);
					if (fabs(dCurPos - dMovePos) <= 0.003)
					{
						//240117 초기화 코드 추가
						Task.initSFRElem();
						theApp.MainDlg->autodispDlg->dispCurTaskOnLabel(1, "-");
						theApp.MainDlg->autodispDlg->DrawGraph(0);
						theApp.MainDlg->autodispDlg->DrawGraph(1);


						Task.PCBTaskTime = myTimer(true);
						iRtnFunction = 60900;
						logStr.Format("	AA Step [%d]", iRtnFunction);
						putListLog(logStr);
						break;
					}
				}
			}
			else
			{
				putListLog("Auto Focusing 中 Z Motor 이동 시간 초과.");
				iRtnFunction = -60070;
				break;
			}
		}
	}
	break;

	case 60100:
	{
		double dMoveDist = 0.0;
		if (!Task.m_bFlag_Fine_Move)
		{
			dMoveDist = model.strInfo_AF1.m_dMoveDistance;
			logStr.Format("Through Focusing");
			theApp.MainDlg->autodispDlg->dispCurTaskOnLabel(1, logStr);
		}
		else
		{
			dMoveDist = model.strInfo_AF2.m_dMoveDistance;
			logStr.Format("Fine Focusing");
			theApp.MainDlg->autodispDlg->dispCurTaskOnLabel(1, logStr);
		}

		iRtn = theApp.MainDlg->_moveZMotor(dMoveDist, model.strInfo_AF1.m_dMoveVel);		/* Z모터 Rough 이동 */
		if (iRtn > 0)
		{
			iRtnFunction = 61000;
			Task.PCBTaskTime = myTimer(true);
		}
		else
		{
			iRtnFunction = -60100;
			logStr.Format("	Z Motor 이동 시간 초과 [%d]", iRtnFunction);
			putListLog(logStr);
			errMsg2(Task.AutoFlag, logStr);
			break;
		}

	}
	break;
	case 60200:
	{
		if (Task.bFirstAA)
		{
			if (sysData.m_i1stAaEbable)	//1차 AA후 종료시
			{
				iRtn = theApp.MainDlg->_getMTF(SFR_FINAL);

				if (iRtn > 0)
				{
					Task.m_iCnt_Second_AA_Start = Task.m_iCnt_Step_AA_Total;
					Task.m_iDrawBarStep = Task.m_iCnt_Step_AA_Total;
					Task.m_iCnt_Step_AA = 0;

					theApp.MainDlg->autodispDlg->DrawBarGraph();		// 60200  procAutoFocus
					MIU.func_Set_InspImageCopy(CHART_RAW, MIU.m_pFrameRawBuffer);			//1차 AA후 
					Task.sfrResult = theApp.MainDlg->func_MTF(MIU.vChartBuffet);		//1차 AA후 종료
					if (Task.sfrResult)
					{
						logStr.Format("1차 AA 결과 Spec OK.");
						putListLog(logStr);
						iRtnFunction = 69999;
						break;
					}
				}
			}
			else
			{
				Task.m_iCnt_Second_AA_Start = Task.m_iCnt_Step_AA_Total;
				Task.m_iCnt_Step_AA = 0;
			}
		}
		double dMovePos = 0.0;
#if (____AA_WAY == PCB_TILT_AA)
		dMovePos = 1 * sysData.m_dMove_MaxPos_Fine;
#elif (____AA_WAY == LENS_TILT_AA)
		dMovePos = -1 * sysData.m_dMove_MaxPos_Fine;
#endif	


		iRtn = theApp.MainDlg->_moveZMotor(dMovePos, model.strInfo_AF1.m_dMoveVel);		/* Z모터 Rough 이동 */

		if (iRtn > 0)
		{
			iRtnFunction = 60900;
			logStr.Format("	AA Step [%d]", iRtnFunction);
			putListLog(logStr);
			Task.PCBTaskTime = myTimer(true);
		}
		else
			iRtnFunction = -60200;
	}

	break;

	case 60900:			/* Z축 본딩 위치 도착 후 */

		if ((myTimer(true) - Task.PCBTaskTime) > model.strInfo_Cam[CCD].m_iDelayTime)
		{
			iRtnFunction = 60910;
		}
		else
		{
			iRtnFunction = 60900;
		}

		break;

	case 60910:	// AA전 Lens X/Y, PCB Theta 보정

		iRtn = theApp.MainDlg->_getMTF(SFR_FIRST/*SFR_FINAL*/);
		if (iRtn > 0)
		{
			if (!theApp.MainDlg->_calcImageAlignment())
			{
				logStr.Format("NG.  X : %.3lf Y : %.3lf", Task.m_dShift_IMG_X, Task.m_dShift_IMG_Y);
				putListLog(logStr);
				iRtnFunction = -60910;
			}
			else
			{
				if (fabs(Task.m_dShift_IMG_X) <= sysData.m_dOcSpec.x * 2 && fabs(Task.m_dShift_IMG_Y) <= sysData.m_dOcSpec.y * 2 &&fabs(Task.m_dShift_IMG_TH) < 0.03)
				{
					logStr.Format("		 영상 Shift. Spec(%.03lf, %.03lf) In : X %.3lf, Y %.3lf",
						sysData.m_dOcSpec.x, sysData.m_dOcSpec.y,
						Task.m_dShift_IMG_X, Task.m_dShift_IMG_Y);
					putListLog(logStr);
					iRtnFunction = 62000;
					break;
				}
				else
				{
					logStr.Format("		 영상 Shift.  X %.3lf, Y %.3lf ,Spec(%.03lf, %.03lf)", Task.m_dShift_IMG_X, Task.m_dShift_IMG_Y, sysData.m_dOcSpec.x, sysData.m_dOcSpec.y);
					putListLog(logStr);
					iRtnFunction = 60920;
				}
			}
		}
		else
		{
			logStr.Format("SFR 영상 획득 실패.");	//SFR 영상 획득 실패.
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -60910;
		}
		break;

	case 60920:
		if (!theApp.MainDlg->_MotorMove_IMG_Align())
		{
			iRtnFunction = -60920;
		}
		else
		{
			iRtnFunction = 60930;
		}
		break;

	case 60930:
		if (!theApp.MainDlg->_MotorMove_IMG_AlignTheta())
		{
			iRtnFunction = -60930;
		}
		else
		{
			Sleep(200);
			iRtnFunction = 60900;
		}
		break;

	case 61000:

		if ((myTimer(true) - Task.PCBTaskTime) > iDelayTime)
		{
			iRtnFunction = 62000;
		}

		break;

	case 62000:
	{
		iRtn = theApp.MainDlg->_getMTF((Task.bFirstAA == true) ? SFR_FINAL : SFR_FIRST);		//속도때문에 sfr 로그 숨기기
		logStr.Format("Step :[%d] SFR [%.03f] [Z %.03f]", Task.m_iCnt_Step_AA, Task.SFR.fSfrN4[Task.m_iCnt_Step_AA][0], motor.GetEncoderPos((theApp.MainDlg->TITLE_MOTOR_Z)));
		putListLog(logStr);
		if (iRtn>0)
		{
			Task.m_iCnt_Step_AA++;		/* Auto Focus rough 측정 횟수 증가 */

			if (Task.bFirstAA)
			{
				theApp.MainDlg->autodispDlg->DrawGraph(1);		/* Z 모터 위치별 SFR 데이터 그래프 그리기 */
			}
			else
			{
				theApp.MainDlg->autodispDlg->DrawGraph(0);		/* Z 모터 위치별 SFR 데이터 그래프 그리기 */
			}

			if (!Task.bFirstAA == true)
			{
				if (Task.m_iCnt_Step_AA == model.m_iCnt_Check_SFR)
				{
					iRtnFunction = 63000;
				}
				else if (Task.m_bFlag_Decrease_SFR == true && Task.m_iCnt_Step_AA == model.m_iCnt_Check_SFR * 2)
				{
					iRtnFunction = 63000;
				}
				else
				{
					iRtnFunction = 64000;
				}
			}
			else
			{
				iRtnFunction = 64000;
			}
			//////////////////////////////////////////////////////////////////////////
		}
		else
		{
			iRtnFunction = -63000;
		}
	}

	break;

	case 63000:		/* 초기 3개 데이터 확인 후 감소 중이면 Z축 모터 이동 */
	{
		iRtn = theApp.MainDlg->_checkDecreaseSFR();
		if (iRtn > 0)
		{
			iRtnFunction = 64000;
		}
		else
		{
			Task.m_bFlag_Decrease_SFR = true;
			theApp.MainDlg->autodispDlg->m_iCur_Index_Through = Task.m_iCnt_Step_AA_Total;

			//autodispDlg->DrawGraph(0);			//------>20180607_1
			//autodispDlg->DrawGraph(1);
			iRtnFunction = 60070;
		}
	}
	break;

	case 64000:
	{
		iRtn = 1;
		int iRtn2 = 1;

		iRtn = theApp.MainDlg->_checkMaxSfrPos(0);		/* MAX 값 찾기 */

		theApp.MainDlg->ccdDlg->SetAlignData_Tilt(Task.SFR.dTilt_X, Task.SFR.dTilt_Y);

		if (iRtn>0)			// && iRtn2>0)
		{

			int mDixTx = 1;
			int mDixTy = 1;
			if (model.Tilt_Diretion[2] < 0)
			{
				mDixTx = -1;
			}
			if (model.Tilt_Diretion[3] < 0)
			{
				mDixTy = -1;
			}

			if (sysData.m_iDicChange == 0)										//IM
			{
				Task.SFR.dTilt_X = theApp.MainDlg->_calcTiltX() *  mDixTx;
				Task.SFR.dTilt_Y = theApp.MainDlg->_calcTiltY() *  mDixTy;
			}
			else
			{
				Task.SFR.dTilt_X = theApp.MainDlg->_calcTiltY() *  mDixTx; ;// mDixTy;
				Task.SFR.dTilt_Y = theApp.MainDlg->_calcTiltX() *  mDixTy; ;// mDixTx;
			}

			logStr.Format("TiltX : %.4f TiltY : %.4f", Task.SFR.dTilt_X, Task.SFR.dTilt_Y);
			putListLog(logStr);

			if (saveSfrLog(SFR_SECOND) == false)
			{
				iRtnFunction = -64000;
			}
			else if (fabs(Task.SFR.dTilt_X) > model.axis[theApp.MainDlg->TITLE_MOTOR_TX].m_dLimit_Err ||
				fabs(Task.SFR.dTilt_Y) > model.axis[theApp.MainDlg->TITLE_MOTOR_TY].m_dLimit_Err)
			{
				logStr.Format("Tilt 보정값 Limit 초과 : Tx : %.4f Ty : %.4f", Task.SFR.dTilt_X, Task.SFR.dTilt_Y);
				errMsg2(Task.AutoFlag, logStr);
				iRtnFunction = -64000;
			}
			else
			{
				if (Task.bFirstAA == true)
				{
					//2차
					logStr.Format("	AA Step 2차[%d]", iRtnFunction);
					putListLog(logStr);
				}
				else
				{
					//1차
					logStr.Format("	AA Step 1차[%d]", iRtnFunction);
					putListLog(logStr);
				}
				iRtnFunction = 64200;		/* Focusing 완료 */
			}
		}
		else
		{
			iRtnFunction = 60100;		/* 다시 측정 */
		}

		if (Task.m_iCnt_Step_AA>model.strInfo_AF1.m_iStepCnt + 5)
		{
			logStr.Format("SFR 측정 최대 횟수 초과.");
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -64000;	/* 카운트 초과시 에러 */
		}

		double z_move_dist = fabs(model.axis[theApp.MainDlg->TITLE_MOTOR_Z].pos[Bonding_Pos] - motor.GetCommandPos(theApp.MainDlg->TITLE_MOTOR_Z));

		if (z_move_dist > 1.0)//0.5
		{
			logStr.Format("[SFR 측정] Z 모터 하강 거리 초과 (1.0mm 이상 내릴 수 없습니다.)");
			errMsg2(Task.AutoFlag, logStr);

			iRtnFunction = -64000;
		}
	}
	break;

	case 64200:		/* Trough Focus 후 Center SFR 값 MAX 위치로 Z모터 이동 */
	{
		//theApp.MainDlg->_getMTF(SFR_STEP);			//250116 IM
		//saveSfrLog(SFR_STEP);
		double dCurPos = 0.0;
		double dMovePos = Task.SFR.dMaxPos[0];//-3.970

											  //////////////////////////////////////////////////////////////////////////////////////////
											  //////////////////////////////////////////////////////////////////////////////////////////

		double z_move_dist = 0.0;
		//PCB Z춖이 움찎이므로 Tilt보정시 PCB-Z춖이 하깡 햬야함.
		//
		//2차 넘어가면서 Z축 띄우는 부분
		//Lens는 Z축 상승
		//Pcb는 Z축 하강
#if (____AA_WAY == PCB_TILT_AA)
		z_move_dist = fabs(model.axis[TITLE_MOTOR_Z].pos[Bonding_Pos] - dMovePos) * -1;	//1차 ->2 차이동
#elif (____AA_WAY == LENS_TILT_AA)
		z_move_dist = fabs(model.axis[theApp.MainDlg->TITLE_MOTOR_Z].pos[Bonding_Pos] - dMovePos) * 1;	//1차 ->2 차이동
#endif
		if (z_move_dist > 1.0)
		{
			logStr.Format("[SFR 측정] Z 모터 하강 거리 초과 (1.0mm 이상 내릴 수 없습니다.)");
			errMsg2(Task.AutoFlag, logStr);

			iRtnFunction = -64200;
			break;
		}

		motor.MoveAxis(theApp.MainDlg->TITLE_MOTOR_Z, ABS, dMovePos, /*model.strInfo_AF1.m_dMoveVel*/10.000, sysData.fMotorAccTime[theApp.MainDlg->TITLE_MOTOR_Z]);

		double ep = myTimer(true);

		while (1)
		{
			if (myTimer(true) - ep < 5000)
			{
				if (motor.IsStopAxis(theApp.MainDlg->TITLE_MOTOR_Z))// && motor.GetInposition(TITLE_MOTOR_Z) )
				{
					dCurPos = motor.GetCommandPos(theApp.MainDlg->TITLE_MOTOR_Z);

					if (fabs(dCurPos - dMovePos) <= 0.003)
					{
						iRtnFunction = 64400;
						Task.PCBTaskTime = myTimer(true);

						break;
					}
				}
			}
			else
			{
				putListLog("Auto Focusing 中 LENS Z Motor 이동 시간 초과.");
				errMsg2(Task.AutoFlag, sLangChange);
				iRtnFunction = -64200;
				break;
			}
		}
	}

	break;


	case 64400:

		iRtn = theApp.MainDlg->_procTiltX();

		if (iRtn>0)
		{
			iRtnFunction = 64600;
		}
		else {
			iRtnFunction = -64400;
		}


		break;

	case 64600:

		iRtn = theApp.MainDlg->_procTiltY();

		if (iRtn>0)
		{
			iRtnFunction = 64700;
		}
		else {
			iRtnFunction = -64600;
		}


		break;

	case 64700:			/* Tilt 보정 후 Delay */
		if (Task.bFirstAA == true)
		{
			if ((myTimer(true) - Task.PCBTaskTime) > model.strInfo_Cam[CCD].m_iDelayTime)
			{
				iRtnFunction = 65000;
			}
			else
			{
				iRtnFunction = 64700;
			}
		}
		else
		{
			iRtnFunction = 65000;
		}
		break;

	case 65000:			/* Tilt 후 MTF 측정 */
	{
		//Task.bFirstAA=true;
		if (Task.bFirstAA == true)//! Active Alignment 2번째 수행 
		{
			Sleep(200);
			iRtn = theApp.MainDlg->_getMTF(SFR_FINAL);

			Task.m_iDrawBarStep = Task.m_iCnt_Step_AA_Total;
			theApp.MainDlg->autodispDlg->DrawBarGraph();	//65000

			if (iRtn > 0)
			{
				if (!theApp.MainDlg->_calcImageAlignment())
				{//-- Align 보정 Limit(임의의 값 사용함...1.0)
					logStr.Format("ImageCenter NG.  X : %.3lf Y : %.3lf", Task.m_dShift_IMG_X, Task.m_dShift_IMG_Y);
					putListLog(logStr);
					iRtnFunction = -65000;
					break;
				}
				else
				{
					if (Task.iMTFCnt < 6)
					{
						if (fabs(Task.m_dShift_IMG_X) > sysData.m_dOcSpec.x &&
							fabs(Task.m_dShift_IMG_Y) > sysData.m_dOcSpec.y)
						{
							logStr.Format("ImageCenter 영상 Shift.  X %.3lf, Y %.3lf", Task.m_dShift_IMG_X, Task.m_dShift_IMG_Y);
							putListLog(logStr);
							Sleep(200);
							iRtnFunction = 65500;
							break;
						}
						else
						{
							logStr.Format("ImageCenter 영상 Shift. Spec(%.03lf, %.03lf) In : X %.3lf, Y %.3lf", sysData.m_dOcSpec.x, sysData.m_dOcSpec.y, Task.m_dShift_IMG_X, Task.m_dShift_IMG_Y);
							putListLog(logStr);
						}
					}
				}

				bool bMtfCheck2 = true;
				MIU.func_Set_InspImageCopy(UV_BEFORE_CHART, MIU.m_pFrameRawBuffer);			//========  AA UV BEFORE===
				Task.sfrResult = theApp.MainDlg->func_MTF(MIU.vChartBuffet);				// [AA UV BEFORE] #1
				MandoInspLog.func_LogSave_UVBefore();	// UV전 Log Data 저장

				theApp.MainDlg->autodispDlg->DrawBarGraph();	//65000
				if (!Task.sfrResult && bMtfCheck2)
				{ 
					saveInspImage(AA_NG_IMAGE_SAVE, Task.m_iCnt_Step_AA_Total);
					logStr.Format("UV전 SFR 검사 NG.  \nAA RETRY 하시겠습니까?");//logStr.Format("SFR 최종 검사 NG.  \nAA RETRY 하시겠습니까?");
					if (askMsg(logStr))
					{
						iRtnFunction = 60000;
						break;
					}
				}

				//saveSfrSumLog();//최종 Data log 저장

				double dCurPosX, dCurPosY, dCurPosTH, dCurPosTX, dCurPosTY, dCurPosZ;
				dCurPosX = motor.GetEncoderPos(Motor_PCB_X);
				dCurPosY = motor.GetEncoderPos(Motor_PCB_Y);
				dCurPosTH = motor.GetCommandPos(Motor_PCB_TH);
				dCurPosTX = motor.GetCommandPos(Motor_PCB_Xt);
				dCurPosTY = motor.GetCommandPos(Motor_PCB_Yt);
				dCurPosZ = motor.GetCommandPos(Motor_PCB_Z);
				if (!g_ADOData.func_AATaskToAAPcbMoter(Task.ChipID, dCurPosX, dCurPosY, dCurPosTH, dCurPosTX, dCurPosTY, dCurPosZ))
				{
					logStr.Format("DataBase 생성 실패.[%d]\n MS Office를 닫아주세요.", iStep);
					errMsg2(Task.AutoFlag, logStr);
					iRtnFunction = -69999;
					break;
				}
				iRtnFunction = 69999;
			}
			else
			{
				logStr.Format("SFR 최종 검사 실패.");
				errMsg2(Task.AutoFlag, logStr);
				iRtnFunction = -65000;
			}
			break;
		}
		else
		{//! Active Alignment 1번째 수행
			iRtn = theApp.MainDlg->_getMTF(SFR_FINAL);
			if (iRtn > 0)
			{
				if (!theApp.MainDlg->_calcImageAlignment())	//여기다 //수동AA
				{
					//-- Align 보정 Limit(임의의 값 사용함...1.0)
					logStr.Format("NG.  X : %.3lf Y : %.3lf", Task.m_dShift_IMG_X, Task.m_dShift_IMG_Y);
					putListLog(logStr);

					iRtnFunction = -65000;

					break;
				}
				else
				{
					if (fabs(Task.m_dShift_IMG_X) <= sysData.m_dOcSpec.x &&
						fabs(Task.m_dShift_IMG_Y) <= sysData.m_dOcSpec.y)
					{//X/Y 보정값이 Spec In일 경우 다음 Step
						logStr.Format("영상 Shift. Spec(%.03lf, %.03lf) In : X %.3lf, Y %.3lf", sysData.m_dOcSpec.x, sysData.m_dOcSpec.y, Task.m_dShift_IMG_X, Task.m_dShift_IMG_Y);
						putListLog(logStr);
						iRtnFunction = 69999;
						logStr.Format("	AA Step [%d]", iRtnFunction);
						putListLog(logStr);
						break;
					}
					else
					{
						logStr.Format("영상 Shift.  X %.3lf, Y %.3lf", Task.m_dShift_IMG_X, Task.m_dShift_IMG_Y);
						putListLog(logStr);
						iRtnFunction = 65500;
						logStr.Format("	AA Step [%d]", iRtnFunction);
						putListLog(logStr);
					}
				}
			}
			else
			{
				errMsg2(Task.AutoFlag, "SFR 영상 획득 실패.");
				iRtnFunction = -65000;
			}
		}
	}

	break;

	case 65500:
		if (!theApp.MainDlg->_MotorMove_IMG_Align())
		{
			iRtnFunction = -65500;
		}
		else
		{
			if (Task.iMTFCnt >= 5)
			{
				if (Task.bFirstAA == true) {
					iRtnFunction = 65520;// 65000;
					Task.PCBTaskTime = myTimer(true);
				}
				else
				{
					iRtnFunction = 69999;
				}
			}
			else
			{
				Task.iMTFCnt++;
				iRtnFunction = 65520;// 65000;
				Task.PCBTaskTime = myTimer(true);
			}
		}
		break;

	case 65520:
		if ((myTimer(true) - Task.PCBTaskTime) > iDelayTime)
		{
			iRtnFunction = 65000;
		}

		break;

	case 69000:								// 최종 SFR 검사 결과 저장..
	// SFR 검사 NG 발생 시 1회 재검사 후 양불 판정.
	if (myTimer(true) - Task.PCBTaskTime > 600)	//(model.strInfo_Cam[CCD].m_iDelayTime  *  2) || (myTimer(true)<Task.PCBTaskTime))
	{
		iRtn = theApp.MainDlg->_getMTF(SFR_FINAL);		/* MTF값 획득 */

		Task.m_iDrawBarStep = Task.m_iCnt_Step_AA_Total;
		theApp.MainDlg->autodispDlg->DrawBarGraph();	//69000

		if (iRtn>0)
		{
			if (Task.m_b_AA_Retry_Flag == false)
			{
				Task.m_b_AA_Retry_Flag = true;		// TRUE인 경우 다음번에는 검사 결과 NG 시 알람 발생..
				iRtnFunction = 60000;				// 60000에서 1, 2차 AA 검사 결과 초기화..
			}
			else
			{
				saveInspImage(AA_NG_IMAGE_SAVE, Task.m_iCnt_Step_AA_Total);
				Dio.setAlarm(ALARM_ON);

				logStr.Format("SFR 최종 검사 NG. 자동 진행 하시겠습니까?");
				if (askMsg(sLangChange))
				{
					Dio.setAlarm(ALARM_OFF);
					logStr.Format("NG 배출 하시겠습니까. (예:NG, 아니오:OK)");
					if (askMsg(logStr)) {
						Task.m_bOkFlag = 0;
					}
					else {
						Task.m_bOkFlag = 1;
					}
					iRtnFunction = 69999;
				}
				else
				{
					Dio.setAlarm(ALARM_OFF);

					//Task.PauseLensStep = abs(Task.LensTask);
					Task.PausePCBStep = abs(Task.PCBTask);
					Task.AutoFlag = 2;		// 일시정지
					theApp.MainDlg->AutoRunView(Task.AutoFlag);
					iRtnFunction = -65000;
				}
			}
		}
		else
		{
			logStr.Format("SFR 최종 검사 (2차) 실패.");
			errMsg2(Task.AutoFlag, sLangChange);
			iRtnFunction = -65000;
		}
	}
	break;
	case 69999:
	{
		double dCurPosX, dCurPosY, dCurPosTH, dCurPosTX, dCurPosTY, dCurPosZ;
		dCurPosX = motor.GetEncoderPos(Motor_PCB_X);
		dCurPosY = motor.GetEncoderPos(Motor_PCB_Y);
		dCurPosTH = motor.GetCommandPos(Motor_PCB_TH);
		dCurPosTX = motor.GetCommandPos(Motor_PCB_Xt);
		dCurPosTY = motor.GetCommandPos(Motor_PCB_Yt);
		dCurPosZ = motor.GetCommandPos(Motor_PCB_Z);
		//
		theApp.MainDlg->putListLog("	");
		logStr.Format("database teaching data save [%s]", Task.ChipID);
		theApp.MainDlg->putListLog("dbData/teachingData");
		theApp.MainDlg->putListLog(logStr);
		logStr.Format("AA x: %lf/%lf", dCurPosX, model.axis[Motor_PCB_X].pos[Bonding_Pos]);
		theApp.MainDlg->putListLog(logStr);
		logStr.Format("AA y: %lf/%lf", dCurPosX, model.axis[Motor_PCB_Y].pos[Bonding_Pos]);
		theApp.MainDlg->putListLog(logStr);
		logStr.Format("AA th: %lf/%lf", dCurPosX, model.axis[Motor_PCB_TH].pos[Bonding_Pos]);
		theApp.MainDlg->putListLog(logStr);
		logStr.Format("AA tx: %lf/%lf", dCurPosX, model.axis[Motor_PCB_Xt].pos[Bonding_Pos]);
		theApp.MainDlg->putListLog(logStr);
		logStr.Format("AA ty: %lf/%lf", dCurPosX, model.axis[Motor_PCB_Yt].pos[Bonding_Pos]);
		theApp.MainDlg->putListLog(logStr);
		logStr.Format("AA z: %lf/%lf", dCurPosX, model.axis[Motor_PCB_Z].pos[Bonding_Pos]);
		theApp.MainDlg->putListLog(logStr);
		//
		if (!g_ADOData.func_AATaskToAAPcbMoter(Task.ChipID, dCurPosX, dCurPosY, dCurPosTH, dCurPosTX, dCurPosTY, dCurPosZ))
		{
			logStr.Format("DataBase 생성 실패.[%d]\n MS Office를 닫아주세요.", iStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -69999;
			break;
		}
		if (Task.bFirstAA == true)
		{
			Task.m_timeChecker.Measure_Time(7);	//AA 완료 시간
			Task.m_dTime_FineAA = Task.m_timeChecker.m_adTime[5] - Task.m_timeChecker.m_adTime[4];
			theApp.MainDlg->dispGrid();

			iRtnFunction = 110000;
		}
		else
		{
			iRtnFunction = 80000;
		}
	}

	break;
	}
	logStr.Empty();
	return iRtnFunction;
}

int CPcbProcess2::UV_process(int iStep)
{
	CString sLog = _T("");
	CString sImgPath = _T("");
	//	int iRtn;
	int reCnt = 0;
	int iRtnFunction = iStep;
	double curMotorDist[3];

	switch (iStep)
	{
	case 110000:
		//if (sysData.m_testRunMode == true)
		//{
		//	iRtnFunction = 120000;

		//	break;
		//}
		iRtnFunction = 110500;
		break;

	case 110500:
		if (theApp.MainDlg->Bonding_Pos_Ckeck())
		{
			sLog.Format("AA after PCB Z : %f , set Offset Z : %f", motor.GetCommandPos(theApp.MainDlg->TITLE_MOTOR_Z), sysData.m_dOffset_Prev_UV_Z);	//AA후 Lens Z : %f , 설정 Offset Z : %f
			putListLog(sLog);

			theApp.MainDlg->MoveOffset_Prev_UV();	/* PCB X, Y, Z, Tx, Ty, PCB Th UV 전 offset 이동 */

			Sleep(200);
			//if (motor.IsStopAxis(theApp.MainDlg->TITLE_MOTOR_Z))// && motor.GetInposition(TITLE_MOTOR_Z))
			if (motor.IsStopAxis(theApp.MainDlg->TITLE_MOTOR_Z) && motor.GetInposition(theApp.MainDlg->TITLE_MOTOR_Z))
			{
				iRtnFunction = 110600;
				Task.PCBTaskTime = myTimer(true);
			}
			else
			{
				iRtnFunction = -110500;
			}
		}
		break;

	case 110600:
		Sleep(200);
		saveSfrLog(SFR_OFFSET_DATA);
		theApp.MainDlg->_getMTF(SFR_AFTER_OFFSET_MOVE);

		iRtnFunction = 110650;
		Task.PCBTaskTime = myTimer(true);
		break;

	case 110650:					//UV전 MTF 검사 진행

		Task.bInsCenter = true;

		theApp.MainDlg->_calcImageAlignment();
		Task.bInsCenter = false;

		iRtnFunction = 110700;


		break;


	case 110700:
		iRtnFunction = 111000;
		Task.PCBTaskTime = myTimer(true);
		break;
	case 111000:	// UV 경화
	{
		theApp.MainDlg->autodispDlg->dispCurTaskOnLabel(1, "UV 경화");

		Task.PCBTaskTime = myTimer(true);

		if (sysData.m_iUVPass == 1)
		{
			sLog.Format("====UV Pass [%d]====", iStep);
			putListLog(sLog);
			iRtnFunction = 113500;
			break;
		}
#if 1
		sLog.Format("===> UV ON");
		putListLog(sLog);

		//Dio.UVTrigger(true, false);
		UVCommand.UV_Shutter_Open();
		Sleep(model.UV_Time);

		//Dio.UVTrigger(false, false);
		UVCommand.UV_Shutter_Close();
		sLog.Format("===> UV OFF [%d]", iStep);
		putListLog(sLog);
#else
		UVControl.Altis_UC_Controller_OnOff(1, 1);
		Sleep(100);
		UVControl.Altis_UC_Controller_OnOff(2, 1);
		Sleep(100);
		UVControl.Altis_UC_Controller_OnOff(3, 1);
		Sleep(100);
		UVControl.Altis_UC_Controller_OnOff(4, 1);
		Sleep(10);

		sLog.Format("===> UV ON");
		putListLog(sLog);
		Sleep(model.UV_Time);

		UVControl.Altis_UC_Controller_OnOff(1, 0);
		Sleep(100);
		UVControl.Altis_UC_Controller_OnOff(2, 0);
		Sleep(100);
		UVControl.Altis_UC_Controller_OnOff(3, 0);
		Sleep(100);
		UVControl.Altis_UC_Controller_OnOff(4, 0);
		Sleep(10);

		sLog.Format("===> UV OFF [%d]", iStep);

		putListLog(sLog);

#endif
		iRtnFunction = 113500;
	}
	break;

	case 113500:
		theApp.MainDlg->autodispDlg->dispCurTaskOnLabel(1, "UV 경화 완료");//"UV 경화 완료"

		Task.m_timeChecker.Measure_Time(8);	//UV 완료 시간
		Task.m_dTime_UV = Task.m_timeChecker.m_adTime[8] - Task.m_timeChecker.m_adTime[7];


		if (myTimer(true) - Task.PCBTaskTime> 100)  // Delay 체크
		{
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 115000;
		}
		break;

	case 115000:
		curMotorDist[0] = fabs(motor.GetEncoderPos(Motor_Lens_X) - model.axis[Motor_Lens_X].pos[Bonding_Pos]);
		curMotorDist[1] = fabs(motor.GetEncoderPos(Motor_Lens_Y) - model.axis[Motor_Lens_Y].pos[Bonding_Pos]);
		curMotorDist[2] = fabs(motor.GetEncoderPos(Motor_Lens_Z) - model.axis[Motor_Lens_Z].pos[Bonding_Pos]);

		if ((curMotorDist[0] < model.axis[Motor_Lens_X].m_dLimit_Err && curMotorDist[1] < model.axis[Motor_Lens_Y].m_dLimit_Err && curMotorDist[2] < model.axis[Motor_Lens_Z].m_dLimit_Err))
		{
			Task.PcbOnStage = 200;			// 검사 완료.
			
			if (!Dio.HolderGrip(false, true))				//Lens Gripper open
			{
				sLog.Format("Lens Grip Open 실패 [%d]", iStep);
				errMsg2(Task.AutoFlag, sLog);
				iRtnFunction = -115000;
				break;
			}
			else
			{
				Task.m_bOKLensPass = -1;//메인 넘김 완료 Lamp 취소
				Task.PCBTaskTime = myTimer(true);
				iRtnFunction = 115300;
				break;
			}
			

		}

		break;
	case 115300:
		iRtnFunction = 115310;
		break;
	case 115310:	//jump Step	
		if (!Dio.LensMotorGrip(false, true))
		{

			sLog.Format("Lens Unit Gripper 해제 실패[%d]", iStep);
			putListLog(sLog);
			iRtnFunction = -115310;
			break;
		}
		Task.m_bOKLensPass = -1;//메인 넘김 완료 Lamp 취소


		Task.m_iFineThCnt = 0;
		iRtnFunction = 115400;
		break;
	case 115400:
		if (Dio.CamLaserSlinderMove(false, true))
		{
			iRtnFunction = 115450;
			break;
		}
		else
		{
			sLog.Format("Laser/Cam 실린더 후진 실패[%d]", iStep);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -115400;
			break;
		}
		break;
	case 115450:
		if (Dio.CamLaserSlinderCheck(false, false))
		{
			sLog.Format("Laser/Cam 실린더 후진 완료[%d]", iStep);
			putListLog(sLog);
			iRtnFunction = 115500;
			break;
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > 10000)//IO_DELAY_TIME)
		{
			sLog.Format("Laser/Cam 실린더 전진 시간 초과[%d]", iStep);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -115450;
			break;
		}
		break;
	case 115500: //UV완료후 최종검사
		Task.m_bOkFlag = 0;
		work.m_iCnt_Output++;
		work.Save();

		iRtnFunction = 120000;
		theApp.MainDlg->_getMTF(SFR_AFTER_UV);
		break;


	default:
		sLog.Format("UV Process Step 번호가 비정상입니다. [%d]", iStep);
		errMsg2(Task.AutoFlag, sLog);
		break;
	}
	sLog.Empty();
	sImgPath.Empty();
	return iRtnFunction;
}

int	CPcbProcess2::Complete_FinalInsp(int iStep)
{
	CString sLog = _T("");
	double	dFinalDelay = (double)(model.strInfo_Cam[3].m_iDelayTime);
	double offsetX = 0.0, offsetY = 0.0, offsetTh = 0.0;
	int iRtn = 0;
	int iRtnFunction = iStep;
	bool bMtfCheck4 = true;
	bool beolRtn = false;
	switch (iStep)
	{
	case 120000:	//완제품
		Task.m_iFineThCnt = 0;
		theApp.MainDlg->setCamDisplay(3, 1);
		Sleep(dFinalDelay);

		//g_clApsInsp.func_insp_Voltage();

		iRtnFunction = 121000;
		break;
	case 121000:
		//g_clApsInsp.func_Insp_CurrentMeasure();
		iRtnFunction = 122000;
		break;

	case 122000:	//완제품 검사만 해당 (Final 검사전 X/Y/T 보정)
		Sleep(dFinalDelay);
		iRtn = theApp.MainDlg->_getMTF(SFR_FINAL);
		Sleep(300);
		if (iRtn > 0)
		{
			//if (Task.m_iFineThCnt == 0)
			//{
			//	theApp.MainDlg->g_CalcImageAlign(true);	//완제품 rotation 검사 240131
			//}


			if (!theApp.MainDlg->_calcImageAlignment())	//-- Align 보정 Limit(임의의 값 사용함...1.0)
			{
				sLog.Format("NG.  X : %.3lf Y : %.3lf", Task.m_dShift_IMG_X, Task.m_dShift_IMG_Y);
				putListLog(sLog);
				iRtnFunction = -122000;
				break;
			}
			else
			{

				//틸팅값 안맞을 경우 값이 동일하게 반복됨.. 3회 정도만 하고 안맞으면 Spec IN 시키기.., 
				if (Task.m_iFineThCnt > 3)	Task.m_dShift_IMG_TH = 0.0;
				if (fabs(Task.m_dShift_IMG_TH) <= sysData.dSpec_OC_Theta)//X/Y 보정값이 Spec In일 경우 다음 Step
				{
					sLog.Format("	영상 Shift. Spec In(%.03lf) In : T: %.3lf", sysData.dSpec_OC_Theta, Task.m_dShift_IMG_TH);
					putListLog(sLog);
					iRtnFunction = 122500;
				}
				else
				{
					sLog.Format("	영상 Shift(Spec : %.03lf).  T: %.3lf", sysData.dSpec_OC_Theta, Task.m_dShift_IMG_TH);
					putListLog(sLog);
					Task.m_iFineThCnt++;
					iRtnFunction = 122100;
				}
			}
		}
		else
		{
			errMsg2(Task.AutoFlag, "MTF 측정 전 SFR 영상 획득 실패..");
			iRtnFunction = -122000;
		}
		break;

	case 122100:
		if (!theApp.MainDlg->_MotorMove_IMG_AlignTheta())
		{
			iRtnFunction = -122100;
		}
		else
		{
			Sleep(100);
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 122200;	//Retry
		}
		break;
	case 122200:
		if ((myTimer(true) - Task.PCBTaskTime) > 300)
		{
			iRtnFunction = 122000;
			sLog.Format("	AA Step [%d]", iRtnFunction);
			putListLog(sLog);
		}
		break;
	case 122500:	//Final 재 검사 - 확인용
		theApp.MainDlg->setCamDisplay(3, 1);
		Sleep(dFinalDelay);

		MIU.func_Set_InspImageCopy(EOL_CHART, MIU.m_pFrameRawBuffer);	//================  완제품 모드 chart
		Sleep(100);
		iRtnFunction = 122520;
		break;
	case 122520:
		Task.bInsCenter = true;

		theApp.MainDlg->_calcImageAlignment();

		Task.bInsCenter = false;

		Task.sfrResult = theApp.MainDlg->func_MTF(MIU.vChartBuffet);//EOL 화상 #1

		if (Task.sfrResult == true)
		{
			putListLog("[검사] MTF 검사 성공.");// Optic_Axis,
		}
		else
		{
			sLog.Format("[검사] MTF 검사 Fail.[%d]", iStep);
			putListLog(sLog);
		}
		Task.m_iDrawBarStep = Task.m_iCnt_Step_AA_Total;
		theApp.MainDlg->autodispDlg->DrawBarGraph();	//122520	Complete_FinalInsp
		vision.clearOverlay(CCD);
		vision.drawOverlay(CCD, true);

		iRtnFunction = 122550;   //122600; <- 이미지 save 한장만 할때
		break;

	case 122550:
		
		iRtnFunction = 122560;
		break;
	case 122560:
		iRtnFunction = 122565;
		break;
	case 122565:
		//Sleep(500);
		iRtnFunction = 122570;
		break;
	case 122570:
		iRtnFunction = 122575;
		break;
	case 122575:
		iRtnFunction = 122580;
		break;
	case 122580:
		//mtf 측정
		Task.bInsCenter = true;

		theApp.MainDlg->_calcImageAlignment();

		Task.bInsCenter = false;

		//Task.sfrResult = theApp.MainDlg->func_MTF(MIU.vChartBuffet);//EOL 화상 #1


		//Task.m_iDrawBarStep = Task.m_iCnt_Step_AA_Total;
		//theApp.MainDlg->autodispDlg->DrawBarGraph();		//122580   Complete_FinalInsp
		//vision.FnShmEdgeFind(MIU.m_pFrameRawBuffer);
		/////MandoInspLog.func_LogSave_UVAfter(1);	//eol _RAW.csv  이물검사후 같이 남김

		//MandoInspLog.func_LogSave_Shm_vertex();


		vision.clearOverlay(CCD);
		vision.drawOverlay(CCD, true);
		iRtnFunction = 122590;  // 122590; Chart YUV - RAW 6500 RAW			IMHS	JUMP
		break;
	case 122590:
		iRtnFunction = 122600;
		break;
	case 122600:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			sLog.Format("PCB Z축 대기위치 이동 실패[%d]", iStep);
			putListLog(sLog);
			iRtnFunction = -122600;
			break;
		}
		iRtnFunction = 122650;
		break;
	case 122650:
		iRtnFunction = 122700;
		break;
	case 122700:
		if (!motor.LENS_Z_Motor_Move(Wait_Pos))
		{
			sLog.Format("Lens부 z축 모터 위치 이동 실패[%d]", iStep);
			putListLog(sLog);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -122700;
			break;
		}

		Task.LensTaskTime = myTimer(true);
		//Task.m_iRetry_Opt = 0;
		iRtnFunction = 123000;
		break;
	case 123000:
		if (sysData.m_iDefectInspPass == 1)	// 이물검사 유무
		{
			sLog.Format(_T("[PASS] Defect Insp[%d]"), iStep);
			putListLog(sLog);
			iRtnFunction = 123400;
			break;
		}
		else
		{
			//iRtnFunction = 123100;
			break;
		}
		break;
	case 123100:
		if (!motor.Pcb_Motor_Move(Dark_Pos))
		{
			sLog.Format("PCB부 Dark 위치 이동 실패[%d]", iStep);
			putListLog(sLog);
			iRtnFunction = -123100;
			break;
		}
		else
		{
			sLog.Format("PCB부 Dark 위치 이동 완료[%d]", iStep);
			putListLog(sLog);
			iRtnFunction = 123200;
			break;
		}
		break;
	case 123200:
		if (!motor.PCB_Z_Motor_Move(Dark_Pos))
		{
			sLog.Format("PCB부 Dark Z 위치 이동 실패[%d]", iStep);
			putListLog(sLog);
			iRtnFunction = -123200;
			break;
		}
		Task.PCBTaskTime = myTimer(true);
		iRtnFunction = 123300;
		break;
	case 123300:
		Sleep(100);
		if (motor.IsStopAxis(Motor_PCB_Z))
		{
			Sleep(100);
			MIU.func_Set_InspImageCopy(LOW_LEVEL_RAW, MIU.m_pFrameRawBuffer);		//완제품 dark
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 123400;
			break;
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > 10000)
		{
			sLog.Format("PCB Z DAR 정지확인 시간 초과[%d]", iStep);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -123200;
			break;
		}
		break;
	case 123400:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			sLog.Format("PCB Z축 대기위치 이동 실패[%d]", iStep);
			putListLog(sLog);
			iRtnFunction = -123400;
			break;
		}
		iRtnFunction = 123500;
		break;
	case 123500:
		if (sysData.m_iStaintInspPass == 1 && sysData.m_iDefectInspPass == 1)
		{
			iRtnFunction = 127000;
			break;
		}
		LightControl.ctrlLedVolume(LIGHT_OC, model.m_iLedValue[LEDDATA_STAIN]);

		iRtnFunction = 123600;
		break;
	case 123600:
		if (!motor.Pcb_Motor_Move(OC_6500K_Pos, Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]))
		{
			sLog.Format("PCB부 모터 Defect 검사 위치 이동 실패[%d]", iStep);
			putListLog(sLog);
			iRtnFunction = -123600;
			break;
		}
		else
		{
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 123650;
			break;
		}
		break;

	case 123650:
		//검사 축 대기위치 확인
		iRtnFunction = 123670;
		break;
	case 123670:
		if (!motor.Pcb_Tilt_Motor_Move(OC_6500K_Pos))
		{
			sLog.Format("PCB Tx Ty 축 이물검사 위치 이동 실패[%d]", iStep);	//김세영 선임 요청 
			putListLog(sLog);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -123670;
			break;
		}
		else
		{
			sLog.Format("PCB Tx Ty 축 이물검사 위치 이동 성공[%d]", iStep);	//김세영 선임 요청 
			putListLog(sLog);
			iRtnFunction = 123700;
			break;
		}
		break;
	case 123700:
		if (motor.PCB_Z_Motor_Move(OC_6500K_Pos))
		{
			sLog.Format("PCB Z Axis OC 6500K Pos Move Complete[%d]", iStep);
			putListLog(sLog);
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 123800;
			break;
		}
		else
		{
			sLog.Format("PCB Z Axis OC 6500K Pos Move Fail[%d]", iStep);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -123700;
			break;
		}
		break;
	case 123800:
		if ((myTimer(true) - Task.PCBTaskTime) > 500)
		{
			iRtnFunction = 123850;
			break;
		}
		break;
	case 123850:
		if (motor.IsStopAxis(Motor_PCB_Z))
		{
			Task.PCBTaskTime = myTimer(true);

			//6500k 이미지 저장
			Sleep(300);
			MIU.func_Set_InspImageCopy(MID_6500K_RAW, MIU.m_pFrameRawBuffer);			//oc
			//ccdDlg->m_pSFRDlg->Raw_ImageSave(MIU.m_pFrameRawBuffer, MID_6500K_RAW);
			//MID_6500K_RAW 이미지 저장

			iRtnFunction = 123900;
			break;
		}
		else
		{
			sLog.Format("PCB Z Axis OC 6500K Pos Move Check Fail[%d]", iStep);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -123700;
			break;
		}
		break;
	case 123900:
		Sleep(dFinalDelay);
		if (sysData.m_iDefectInspPass == 1)	// 이물검사 유무
		{
			sLog.Format(_T("[PASS] Defect Insp[%d]"), iStep);
			putListLog(sLog);
		}
		else
		{
			if (g_clApsInsp.func_Insp_Defect(MIU.vDefectMidBuffer_6500K, MIU.vDefectLowBuffer, true) == true)	//EOL
			{
				putListLog("[검사] Defect 검사 성공.");
			}
			else
			{
				sLog.Format("[검사] Defect 검사  Error[%d]", iStep);
				putListLog(sLog);
				MandoInspLog.bInspRes = false;
			}
		}
		if (sysData.m_iStaintInspPass == 1)	// 이물검사 유무
		{
			sLog.Format(_T("[PASS] Stain Insp[%d]"), iStep);
			putListLog(sLog);

		}
		else
		{
			if (LGIT_MODEL_INDEX == M2_FF_MODULE)		//g_GetIllumination 완제품
			{
				//이물광원에서 oc 측정 요청240725
				g_clApsInsp.g_GetIllumination(MIU.vDefectMidBuffer_6500K);
				Sleep(100);
			}


			if (g_clApsInsp.func_Insp_Stain(MIU.vDefectMidBuffer_6500K) == true)
			{
				putListLog("[검사] Stain 검사 성공.");
			}
			else
			{
				sLog.Format("[검사] Stain 검사  Error[%d]", iStep);
				putListLog(sLog);
				MandoInspLog.bInspRes = false;
			}

		}
		

		iRtnFunction = 127000;	/// 127150;// 127000;			IMHS	JUMP
		break;
	case 127000:
		iRtnFunction = 127500;
		break;
	case 127500:
		if (motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			sLog.Format("PCB Z축 대기 위치 이동 완료[%d]", iStep);
			putListLog(sLog);
			iRtnFunction = 127600;
		}
		else
		{
			sLog.Format("PCB Z축 대기 위치 이동 실패[%d]", iStep);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -127500;
		}
		break;

	case 127600:
		Task.m_iRetry_Opt = 0;
		iRtnFunction = 127700;
		break;
	case 127700:
		//Head Model
		MIU.OtpRead_Head_Fn();
		MIU.partNumberVerifyFn();
		MIU.FwVersionRead_Head_Fn();
		MIU.SensorIdRead_Head_Fn();
		iRtnFunction = 127710;
		break;
	case 127710:
		MandoInspLog.func_LogSave_UVAfter(0);	//eol _RAW.csv
		MIU.Close();
		iRtnFunction = 127800;
		break;
	case 127800:
		MESCommunication.OTPVerifyFail.Empty();
		MESCommunication.sensorId.Empty();
		MESCommunication.partNumber.Empty();
		MESCommunication.fwVersion.Empty();
		iRtnFunction = 127900;
		break;
	case 127900:
		Task.m_iRetry_Opt = 0;

		//g_FinalInspLog();

		work.iInspCnt_Output++;
		if (MandoInspLog.bInspRes == false)	work.iInspCnt_NG_Output++;
		theApp.MainDlg->dispInspResGrid();
		work.Save();
		work.Load();

		Task.m_timeChecker.Measure_Time(13);	//Final 검사 완료 시간
		Task.m_dTime_TotalAA = Task.m_timeChecker.m_adTime[13] - Task.m_timeChecker.m_adTime[12];
		theApp.MainDlg->dispGrid();

		iRtnFunction = 128000;
		break;
	case 128000:
		Sleep(100);
		vision.clearOverlay(CCD);
		if (MandoInspLog.bInspRes == true)
		{
			vision.textlist[CCD].addList(50, 100, "PASS", M_COLOR_GREEN, 65, 85, "Arial");
		}
		else
		{
			vision.textlist[CCD].addList(50, 100, "FAIL", M_COLOR_RED, 80, 100, "Arial");
			MandoInspLog.func_DrawNG_Overlay(CCD);	//화면 Overlay에 NG List Draw
			work.m_iCnt_NG_Output++;
		}
		vision.drawOverlay(CCD, true);

		//ccd영상 전환

		theApp.MainDlg->ctrlSubDlg(MAIN_DLG);
		theApp.MainDlg->setCamDisplay(3, 1);
		theApp.MainDlg->changeMainBtnColor(MAIN_DLG);
		iRtnFunction = 128100;
		break;

	case 128100:
		iRtnFunction = 129200;
		break;
	case 129200:
		if (!motor.Lens_Motor_MoveXY(Wait_Pos))
		{
			sLog.Format("Lens부 모터 대기 위치 이동 실패[%d]", iStep);
			putListLog(sLog);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -129200;
			break;
		}
		else
		{
			iRtnFunction = 129220;
		}
		break;

	case 129220:
		iRtnFunction = 129300;
		break;

		break;
	case 129300:
		if (motor.Pcb_Motor_Move(Wait_Pos))
		{
			sLog.Format("PCB 대기 위치 이동 완료 [%d]", iStep);
			putListLog(sLog);
			iRtnFunction = 129350;
		}
		else
		{
			sLog.Format("PCB 대기 위치 이동 실패 [%d]", iStep);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -129300;
		}

		break;
	case 129350:
		//Dio.PcbGrip(false, false);
		iRtnFunction = 129400;
		break;
	case 129400:
		if (motor.Pcb_Tilt_Motor_Move(Wait_Pos))
		{
			sLog.Format("PCB TX,TY 대기 위치 이동 완료 [%d]", iStep);
			putListLog(sLog);
			iRtnFunction = 129410;
		}
		else
		{
			sLog.Format("PCB TX,TY 대기위치 이동 실패[%d]", iStep);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -129400;
		}
		break;
	case 129410:
		if (Dio.DoorLift(true, false))
		{
			sLog.Format("Door Open [%d]", iStep);
			putListLog(sLog);
			iRtnFunction = 129500;
			break;
		}
		else
		{
			sLog.Format("Door Close 실패 [%d]", iStep);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -129410;
			break;
		}
		break;
	case 129500:
		Task.m_bOkDispense = -1;	//메인 도포 완료 Lamp 취소
		putListLog("		");
		putListLog("		");
		sLog.Format("			END =======%s", Task.ChipID);
		putListLog(sLog);
		putListLog("		");
		putListLog("		");
		Task.m_bPBStart = 0;	//바코드 정보 초기화


		memset(Task.ChipID, 0x00, 256);
		//sprintf_s(Task.ChipID, _T("EMPTY"));

		_stprintf_s(Task.ChipID, sizeof(Task.ChipID), _T("EMPTY"));
		theApp.MainDlg->func_ChipID_Draw();

		Task.m_timeChecker.Measure_Time(14);	//완제품 배출 시간
		Task.m_dTime_Total = Task.m_timeChecker.m_adTime[14] - Task.m_timeChecker.m_adTime[1];

		theApp.MainDlg->dispGrid();
		theApp.MainDlg->EpoxyTimeCheck(theApp.MainDlg->bEpoxyTimeChk);
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		Task.PCBTask = 10000;
		iRtnFunction = 10000;
		break;
	default:
		sLog.Format("Mando Test Process Step Number Error. [%d]", iStep);
		errMsg2(Task.AutoFlag, sLog);
		iRtnFunction = -iStep;
		break;
	}
	return iRtnFunction;
}

int	CPcbProcess2::func_MandoFinalSFR(int iStep)
{
	CString sLog = _T("");
	double	dFinalDelay = (double)(model.strInfo_Cam[3].m_iDelayTime);
	double offsetX = 0.0;
	double offsetY = 0.0;
	double offsetTh = 0.0;
	int iRtn = 0;
	int iRtnFunction = iStep;
	bool bUseDispense = true;	//도포 Pass 여부

	if ((sysData.m_iDispensePass == 1))
	{
		bUseDispense = false;//도포 Pass Mode 이거나, 도포 완료 일 경우
	}
	else
	{
		bUseDispense = true;
	}

	switch (iStep)
	{
	case 120000:
		//if (sysData.m_testRunMode == true)
		//{
		//	iRtnFunction = 122550;///// 125000;

		//	break;
		//}
		//g_clApsInsp.func_insp_Voltage();
		iRtnFunction = 121000;
		break;

	case 121000:
		//g_clApsInsp.func_Insp_CurrentMeasure();
		iRtnFunction = 122000;
		break;
	case 122000:	//완제품 검사만 해당 (Final 검사전 X/Y/T 보정)
		Sleep(dFinalDelay);
		iRtn = theApp.MainDlg->_getMTF(SFR_FINAL);
		if (iRtn > 0)
		{
			if (!theApp.MainDlg->_calcImageAlignment())	//-- Align 보정 Limit(임의의 값 사용함...1.0)
			{
				sLog.Format("NG.  X : %.3lf Y : %.3lf", Task.m_dShift_IMG_X, Task.m_dShift_IMG_Y);
				putListLog(sLog);
				iRtnFunction = -122000;
				break;
			}
			else
			{
				//틸팅값 안맞을 경우 값이 동일하게 반복됨.. 3회 정도만 하고 안맞으면 Spec IN 시키기..,
				if (Task.m_iFineThCnt > 5)	Task.m_dShift_IMG_TH = 0.0;
				if (fabs(Task.m_dShift_IMG_TH) <= sysData.dSpec_OC_Theta)//X/Y 보정값이 Spec In일 경우 다음 Step
				{
					sLog.Format("	영상 Shift. Spec In(%.03lf) In : T: %.3lf", sysData.dSpec_OC_Theta, Task.m_dShift_IMG_TH);
					putListLog(sLog);
					iRtnFunction = 122500;
				}
				else
				{
					sLog.Format("	영상 Shift(Spec : %.03lf).  T: %.3lf", sysData.dSpec_OC_Theta, Task.m_dShift_IMG_TH);
					putListLog(sLog);
					if (bUseDispense == false) //AAB, 도포 미사용일 경우->영상 Shift안하고 진행
					{
						iRtnFunction = 122500;
					}
					else//영상 Shift 진행
					{
						Task.m_iFineThCnt++;
						iRtnFunction = 122100;
					}
				}
			}
		}
		else
		{
			if (askMsg("진행?") == IDOK)
			{
				iRtnFunction = 122500;
				break;
			}
			else
			{
				errMsg2(Task.AutoFlag, "MTF 측정 전 SFR 영상 획득 실패..");
				iRtnFunction = -122000;
			}
		}
		break;

	case 122100:
		if (!theApp.MainDlg->_MotorMove_IMG_AlignTheta())
		{
			iRtnFunction = -122100;
		}
		else
		{
			Sleep(100);
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 122200;	//Retry
		}
		break;
	case 122200:
		if ((myTimer(true) - Task.PCBTaskTime) > 300)
		{
			iRtnFunction = 122000;
			sLog.Format("	AA Step [%d]", iRtnFunction);
			putListLog(sLog);
		}
		break;
	case 122500:	//Final 재 검사 - 확인용
		theApp.MainDlg->setCamDisplay(3, 1);

		Sleep(dFinalDelay);
		MIU.func_Set_InspImageCopy(UV_AFTER_CHART, MIU.m_pFrameRawBuffer);		//========AA UV AFTER===
		Sleep(300);
		iRtnFunction = 122520;
		break;
	case 122520:

		Task.bInsCenter = true;

		theApp.MainDlg->_calcImageAlignment();

		Task.bInsCenter = false;

		Task.sfrResult = theApp.MainDlg->func_MTF(MIU.vChartBuffet);			// [AA UV AFTER] #1

		if (Task.sfrResult == true)
		{
			putListLog("[검사] MTF 검사 성공.");// Optic_Axis,
		}
		else
		{
			putListLog("[검사] MTF 검사 실패.");// Optic_Axis,
		}
		Task.m_iDrawBarStep = Task.m_iCnt_Step_AA_Total;
		theApp.MainDlg->autodispDlg->DrawBarGraph();
		iRtnFunction = 122550;

		break;
	case 122550:			//jump step 수정 nono
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			sLog.Format("PCB부 z축 모터 위치 이동 실패[%d]", iStep);
			putListLog(sLog);
			iRtnFunction = -122550;
			break;
		}

		if (!motor.LENS_Z_Motor_Move(Wait_Pos))
		{
			sLog.Format("Lens부 z축 모터 위치 이동 실패[%d]", iStep);
			putListLog(sLog);
			iRtnFunction = -122550;
			break;
		}



		iRtnFunction = 122700;
		break;
	case 122700:

		sLog.Format("Lens Y 대기 위치 이동 명령[%d]", iStep);
		putListLog(sLog);

		motor.Lens_Motor_MoveY(Wait_Pos, 0.0, false);		//Lens x 동시 이동 240108

		Task.m_iRetry_Opt = 0;
		iRtnFunction = 122800;
		break;
	case 122800:
		iRtnFunction = 123000;

		//if (sysData.m_iDefectInspPass == 1)	// 이물검사 유무
		//{
		//	sLog.Format(_T("[PASS] Defect Insp[%d]"), iStep);
		//	putListLog(sLog);
		//	iRtnFunction = 123000;
		//}
		//else
		//{
		//	iRtnFunction = 122850;
		//}
		break;
#if 0
	case 122850:

		if (motor.Pcb_Motor_MoveY(Wait_Pos))
		{
			iRtnFunction = 122860;
			sLog.Format("Pcb y 대기 위치 이동 완료 [%d]", iStep);
			putListLog(sLog);
		}
		else
		{
			sLog.Format("Pcb y 대기 위치 이동 실패 [%d]", iStep);
			putListLog(sLog);
			iRtnFunction = -122850;
		}
		break;
	case 122860:
		if (!motor.Pcb_Motor_Move(Dark_Pos))
		{
			sLog.Format("PCB부 Dark 위치 이동 실패[%d]", iStep);
			putListLog(sLog);
			iRtnFunction = -122860;
		}
		else
		{
			sLog.Format("PCB부 Dark 위치 이동 완료[%d]", iStep);
			putListLog(sLog);
			iRtnFunction = 122900;
		}

		break;
	case 122900:
		if (!motor.PCB_Z_Motor_Move(Dark_Pos))
		{
			sLog.Format("PCB부 Dark Z 위치 이동 실패[%d]", iStep);
			putListLog(sLog);
			iRtnFunction = -122900;
			break;
		}
		Task.PCBTaskTime = myTimer(true);
		iRtnFunction = 122950;
		break;
	case 122950:
		if ((myTimer(true) - Task.PCBTaskTime) > 500)
		{
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 122960;
		}
		break;
	case 122960:
		if (motor.IsStopAxis(Motor_PCB_Z))
		{
			MIU.func_Set_InspImageCopy(LOW_LEVEL_RAW, MIU.m_pFrameRawBuffer);			//aa Dark
			iRtnFunction = 122970;
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > 10000)
		{
			sLog.Format("PCB Z DAR 정지확인 시간 초과[%d]", iStep);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -122900;
		}

		break;

	case 122970:

		iRtnFunction = 123000;
		break;
#endif
	case 123000:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			sLog.Format("PCB Z축 대기위치 이동 실패[%d]", iStep);
			putListLog(sLog);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -123000;
			break;
		}
		sLog.Format("Pcb Z축 대기위치 이동 완료 [%d]", iStep);
		putListLog(sLog);
		iRtnFunction = 123050;
		break;
	case 123050:
		/*Sleep(5000);
		if (motor.Pcb_Motor_MoveY(OC_6500K_Pos))
		{
			sLog.Format("Pcb Y 이물검사 위치 이동 완료 [%d]", iStep);
			putListLog(sLog);
			iRtnFunction = 123051;
			break;
		}
		else
		{
			sLog.Format("Pcb Y 이물검사 위치 이동 실패 [%d]", iStep);
			putListLog(sLog);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -123050;
			break;
		}
		break;*/
		iRtnFunction = 123051;
		break;
	case 123051:
		if (sysData.m_iStaintInspPass == 1)
		{
			sLog.Format("Pcb Y 이물검사 PASS [%d]", iStep);
			putListLog(sLog);
			iRtnFunction = 124500;
			break;
		}
		LightControl.ctrlLedVolume(LIGHT_OC, model.m_iLedValue[LEDDATA_STAIN]);

		iRtnFunction = 123055;

		break;
	case 123055:
		if (!motor.Pcb_Motor_Move(OC_6500K_Pos))
		{
			sLog.Format("PCB축 이물검사 위치 이동 실패[%d]", iStep);	//PCB부 모터 Defect 검사 위치 이동 실패[%d]
			putListLog(sLog);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -123055;
			break;
		}
		else
		{
			iRtnFunction = 123056;
			break;
		}
		break;
	case 123056:
		if (!motor.Pcb_Tilt_Motor_Move(OC_6500K_Pos))
		{
			sLog.Format("PCB Tx Ty 축 이물검사 위치 이동 실패[%d]", iStep);	//김세영 선임 요청 
			putListLog(sLog);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -123056;
			break;
		}
		else
		{
			sLog.Format("PCB Tx Ty 축 이물검사 위치 이동 성공[%d]", iStep);	//김세영 선임 요청 
			putListLog(sLog);
			iRtnFunction = 123058;
			break;
		}
		break;
	case 123058:
		Task.PCBTaskTime = myTimer(true);
		iRtnFunction = 123100;
		break;
	case 123100:
		if (motor.PCB_Z_Motor_Move(OC_6500K_Pos))
		{
			sLog.Format("PCB Z Axis OC 6500K Pos Move Complete[%d]", iStep);
			putListLog(sLog);
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 123400;
			break;
		}
		else
		{
			sLog.Format("PCB Z Axis OC 6500K Pos Move Fail[%d]", iStep);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -123100;
			break;
		}
		break;
	case 123400:
		if (motor.IsStopAxis(Motor_PCB_Z))
		{
			Sleep(100);
			MIU.func_Set_InspImageCopy(MID_6500K_RAW, MIU.m_pFrameRawBuffer);		//aa oc
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 124000;
			break;
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > 10000)
		{
			sLog.Format("PCB Z 6500K 정지확인 시간 초과[%d]", iStep);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -123100;
			break;
		}
		break;
	case 124000:
		//if (sysData.m_iDefectInspPass == 1)	// 이물검사 유무
		//{
		//	sLog.Format(_T("[PASS] Defect Insp [%d]"), iStep);
		//	putListLog(sLog);
		//}
		//else
		//{
		//	if (g_clApsInsp.func_Insp_Defect(MIU.vDefectMidBuffer_6500K, MIU.vDefectLowBuffer, true) == true)	//AA
		//	{
		//		putListLog("[검사] Defect 검사 성공.");
		//	}
		//	else
		//	{
		//		sLog.Format("[검사] Defect 검사  Error[%d]", iStep);
		//		putListLog(sLog);
		//		MandoInspLog.bInspRes = false;
		//	}
		//}
		if (sysData.m_iStaintInspPass == 1)	// 이물검사 유무
		{
			sLog.Format(_T("[PASS] Stain Insp [%d]"), iStep);
			putListLog(sLog);

		}
		else
		{

			if (LGIT_MODEL_INDEX == M2_FF_MODULE)		//g_GetIllumination AA
			{
				//이물광원에서 oc 측정 요청240725
				g_clApsInsp.g_GetIllumination(MIU.vDefectMidBuffer_6500K);
				Sleep(100);
			}


			if (g_clApsInsp.func_Insp_Stain(MIU.vDefectMidBuffer_6500K) == true)
			{
				putListLog("[검사] Stain 검사 성공.");
			}
			else
			{
				sLog.Format("[검사] Stain 검사  Error[%d]", iStep);
				putListLog(sLog);
				MandoInspLog.bInspRes = false;
			}
		}

		iRtnFunction = 124500;
		break;
	case 124500:
		iRtnFunction = 124501;
		break;
	case 124501:
		iRtnFunction = 124502;
		break;
	case 124502:
		//Head Model
		//otp Write
		if (!MIU.OtpWrite_Head_Fn())
		{
			sLog.Format("OTP Write Fail [%d]", iStep);
			errMsg2(Task.AutoFlag, sLog);
			putListLog(sLog);
			MESCommunication.OTPWriteFail.Format(_T("NG"));
			MandoInspLog.bInspRes = false;
			iRtnFunction = -124502;
			break;
		}
		sLog.Format("OTP Write...Sucsess [%d]", iStep);
		MESCommunication.OTPWriteFail.Format(_T("PASS"));
		putListLog(sLog);
		iRtnFunction = 124503;
		break;
	case 124503:
		//OTP
		//ccd close  MIU.Close

		if (!MIU.Close())
		{
			sLog.Format("MIU Close 실패 [%d]", iStep);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -124503;
			break;
		}
		sLog.Format("MIU Close... [%d]", iStep);
		putListLog(sLog);
		iRtnFunction = 124504;
		break;
	case 124504:
		//ccd open  MIU.Open

		if (!theApp.MainDlg->MIUCheck_process())
		{
			sLog.Format("CCD 모듈 영상 초기화 실패.\n 제품 안착 상태 및 제품 불량 확인 하세요.");
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -124504;
			break;
		}
		sLog.Format("CCD Start 성공[%d]", iStep);
		putListLog(sLog);
		iRtnFunction = 124505;
		break;
	case 124505:
		// otp Fw ver
		MIU.FwVersionRead_Head_Fn();
		iRtnFunction = 124506;
		break;
	case 124506:
		//Otp OtpRead_Head_Fn

		MIU.OtpRead_Head_Fn();
		sLog.Format("OTP Read [%d]", iStep);
		putListLog(sLog);
		iRtnFunction = 124507;
		break;
	case 124507:
		//Sensor ID Read
		MIU.SensorIdRead_Head_Fn();
		sLog.Format("Sensor ID Read [%d]", iStep);
		putListLog(sLog);
		iRtnFunction = 124508;
		break;
	case 124508:
		//Otp Verify
		if (!MIU.partNumberVerifyFn())
		{
			sLog.Format("OTP Verify Fail [%d]", iStep);
			errMsg2(Task.AutoFlag, sLog);
			MandoInspLog.bInspRes = false;
			putListLog(sLog);
			iRtnFunction = -124508;
			break;
		}
		sLog.Format("OTP Verify...Sucsess [%d]", iStep);
		iRtnFunction = 124510;
		break;
	case 124510:
		MIU.Close();
		iRtnFunction = 125000;
		break;
	case 125000: 	//jump step 변경 nono
		if (motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			sLog.Format("PCB Z축 대기 위치 이동 완료[%d]", iStep);
			putListLog(sLog);
			iRtnFunction = 125500;
			Task.PCBTaskTime = myTimer(true);
		}
		else
		{
			sLog.Format("PCB Z축 대기 위치 이동 실패[%d]", iStep);
			sLog.Format(sLangChange, iStep);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -125000;
		}
		break;
	case 125500:
		iRtnFunction = 126000;
		break;
	case 126000:
		iRtnFunction = 127000;
		break;
	case 127000:
		iRtnFunction = 127100;
		break;
	case 127100:
		Task.m_iRetry_Opt = 0;
		MandoInspLog.func_LogSave_UVAfter(0);	//만도 차량용Camera 검사 Log 저장(검사/보정량 저장 -> 최종Log)


		/*inspMES();
		MESCommunication.Messave();*/
		//! 검사 Count 처리
		/*work.iInspCnt_Output++;
		if(MandoInspLog.bInspRes == false)	work.iInspCnt_NG_Output++;
		dispInspResGrid();
		work.Save();
		work.Load();*/

		Task.m_timeChecker.Measure_Time(13);	//Final 검사 완료 시간
		Task.m_dTime_TotalAA = Task.m_timeChecker.m_adTime[13] - Task.m_timeChecker.m_adTime[12];
		///dispGrid();

		iRtnFunction = 127300;
		break;

	case 127300:
		Sleep(100);
		vision.clearOverlay(CCD);
		if (MandoInspLog.bInspRes == true)
		{
			vision.textlist[CCD].addList(50, 100, "PASS", M_COLOR_GREEN, 65, 85, "Arial");
		}
		else
		{
			vision.textlist[CCD].addList(50, 100, "FAIL", M_COLOR_RED, 80, 100, "Arial");
			MandoInspLog.func_DrawNG_Overlay(CCD);	//화면 Overlay에 NG List Draw
			work.m_iCnt_NG_Output++;
		}
		vision.drawOverlay(CCD, true);

		//ccd영상 전환

		theApp.MainDlg->ctrlSubDlg(MAIN_DLG);
		theApp.MainDlg->setCamDisplay(3, 1);
		theApp.MainDlg->changeMainBtnColor(MAIN_DLG);
		iRtnFunction = 127400;
		break;

	case 127400:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			sLog.Format("PCB Z축 대기 위치 이동 실패[%d]", iStep);
			putListLog(sLog);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -127400;
			break;
		}
		Task.PCBTaskTime = myTimer(true);
		iRtnFunction = 127500;
		break;
	case 127500:
		//OTP
		MESCommunication.OTPWriteFail.Empty();      
		MESCommunication.OTPVerifyFail.Empty();
		MESCommunication.sensorId.Empty();
		MESCommunication.partNumber.Empty();
		iRtnFunction = 127510;
		break;
	case 127510:
		iRtnFunction = 127520;
		break;
	case 127520:
		if (motor.Pcb_Motor_Move(Wait_Pos))
		{
			sLog.Format("PCB 대기 위치 이동 완료 [%d]", iStep);
			putListLog(sLog);
			iRtnFunction = 127900;

		}
		else
		{
			sLog.Format("PCB 대기 위치 이동 실패 [%d]", iStep);
			putListLog(sLog);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -127520;
		}
		break;
	case 127900:
		if (motor.Pcb_Tilt_Motor_Move(Wait_Pos))
		{
			sLog.Format("PCB TX,TY 대기 위치 이동 완료 [%d]", iStep);
			putListLog(sLog);
			iRtnFunction = 127950;
			Task.PCBTaskTime = myTimer(true);
		}
		else
		{
			sLog.Format("PCB TX,TY 대기위치 이동 실패[%d]", iStep);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -127900;
		}
		break;
	case 127950:

		if (motor.IsStopAxis(Motor_Lens_Y) && motor.checkLensMotorPos(Wait_Pos, 0))
		{
			iRtnFunction = 128000;
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > 10000)
		{
			sLog.Format(_T("Lens y axis 대기 위치 확인 실패[%d]"), iStep);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -127900;
		}

		break;
	case 128000:
		if (!motor.Lens_Motor_MoveXY(Wait_Pos))
		{
			sLog.Format("Lens부 모터 대기 위치 이동 실패[%d]", iStep);
			putListLog(sLog);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -128000;
		}
		else
		{
			iRtnFunction = 128200;
		}
		break;
	case 128200:
		if (Dio.DoorLift(true, false))
		{
			sLog.Format("Door Open [%d]", iStep);
			putListLog(sLog);
			iRtnFunction = 128500;
			break;
		}
		else
		{
			sLog.Format("Door Close 실패 [%d]", iStep);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -128200;
			break;
		}
		break;
	case 128500:
		if (motor.Lens_Tilt_Motor_Move(Wait_Pos))
		{
			iRtnFunction = 129000;
			break;
		}
		else
		{
			sLog.Format("LENS부 Tx, Ty축 대기 위치 이동 실패");
			putListLog(sLog);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -128500;
			break;
		}
		break;

	case 129000:
		iRtnFunction = 129500;
		break;
	case 129500:
		Task.m_bOkDispense = -1;	//메인 도포 완료 Lamp 취소
		putListLog("		");
		putListLog("		");
		sLog.Format("			END =======%s", Task.ChipID);
		putListLog(sLog);
		putListLog("		");
		putListLog("		");
		putListLog("		");
		putListLog("		");
		Task.m_bPBStart = 0;	//바코드 정보 초기화
	
		memset(Task.ChipID, 0x00, 256);
		_stprintf_s(Task.ChipID, sizeof(Task.ChipID), _T("EMPTY"));
		theApp.MainDlg->func_ChipID_Draw();

		Task.m_timeChecker.Measure_Time(14);	//완제품 배출 시간
		Task.m_dTime_Total = Task.m_timeChecker.m_adTime[14] - Task.m_timeChecker.m_adTime[1];

		theApp.MainDlg->dispGrid();
		theApp.MainDlg->EpoxyTimeCheck(theApp.MainDlg->bEpoxyTimeChk);

		Dio.PCBvaccumOn(VACCUM_OFF, false);

		//////////////////////////////////////////////////////////////////////////////////////////////////////
		
		Task.PCBTask = 10000;
		iRtnFunction = 10000;
		break;

	default:
		sLog.Format("Mando Test Process Step Number Error. [%d]", iStep);
		errMsg2(Task.AutoFlag, sLog);
		iRtnFunction = -iStep;
		break;
	}
	sLog.Empty();
	return iRtnFunction;
}


int CPcbProcess2::RunProc_LensNewPassPickup(int iUseStep)
{
	//! Lens Pickup에 제품 넘김 Step	(15000 ~ 16600)
	int iRtnFunction = iUseStep;
	int iRtn = 0;
	CString logStr = "";
	double	dFinalDelay = (double)(model.strInfo_Cam[3].m_iDelayTime);
	bool bChk = true;
	double offsetX = 0.0, offsetY = 0.0, offsetTh = 0.0;

	switch (iUseStep)
	{
	case 15000:
		if (!motor.LENS_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("Lens_Z축 대위치 이동 실패");
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -15000;
			break;
		}

		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("PCB Z축 대기위치 이동 실패[%d]", iUseStep);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -15000;
			break;
		}

		if (Task.m_bOKLensPass != 1)//! Lens 넘김 미완료 일 경우	 
		{
			if (!motor.Pcb_Motor_Move(Loading_Pos, Task.d_Align_offset_x[PCB_Holder_MARK], Task.d_Align_offset_y[PCB_Holder_MARK], 0))
			{
				logStr.Format("PCB %s 이동 실패", MotorPosName[Loading_Pos]);
				delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
				iRtnFunction = -15000;
				break;
			}
			iRtnFunction = 15100;
		}
		else
		{
			iRtnFunction = 15500;
		}
		break;
	case 15100:
		if (!Dio.LensMotorGrip(false, false))
		{
			logStr.Format("Lens Unit Gripper 해제 실패[%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = -15100;
			break;
		}
		Task.PCBTaskTime = myTimer(true);
		iRtnFunction = 15150;
		break;

	case 15150:
		if (Dio.LensMotorGripCheck(false, false))
		{
			iRtnFunction = 15200;
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > IO_DELAY_TIME)
		{
			iRtnFunction = -15150;
		}
		break;

	case 15200: // 공급
		if (!motor.Lens_Tilt_Motor_Move(Loading_Pos))
		{
			logStr.Format("Lens %s Tx,Ty이동 실패", MotorPosName[Loading_Pos]);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -15200;
			break;
		}
		if (!motor.Lens_Motor_MoveXY(Loading_Pos))
		{
			logStr.Format("Lens %s X,Y 이동 실패", MotorPosName[Loading_Pos]);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -15200;
			break;
		}
		logStr.Format("Lens 공급 위치 이동 완료[%d]", iUseStep);
		putListLog(logStr);
		iRtnFunction = 15250;
		break;

	case 15250:
		if (!motor.PCB_Z_Motor_Move(Loading_Pos))
		{
			logStr.Format("PCB loading Z 이동 실패");
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -15250;
		}
		else
		{
			iRtnFunction = 15252;
		}
		break;
	case 15252:
		if (motor.LENS_Z_Motor_Move(Loading_Pos))
		{
			iRtnFunction = 15255;
		}
		else
		{
			logStr.Format("Lens Z 위치 이동 실패 [%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -15252;
		}
		break;

	case 15255:
		iRtnFunction = 15300;
		break;


	case 15300: // 모터 그립
		if (Dio.LensMotorGrip(true, false))
		{
			Task.m_bOKLensPass = 1;
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 15350;
			Sleep(500);
			Dio.LensMotorGrip(false, false);
			Sleep(500);
			Dio.LensMotorGrip(true, false);
		}
		else
		{
			Task.m_bOKLensPass = -1;
			logStr.Format("Lens 그립 실패 [%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -15300;
		}
		break;

	case 15350://모터 그립 확인
		if (Dio.LensMotorGripCheck(true, false))
		{
			logStr.Format("Lens 그립 완료[%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = 15400;

			Sleep(800);
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > IO_DELAY_TIME)
		{
			logStr.Format("Lens Gripper 전진 센서 시간 초과..[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -15350;
		}
		break;
	case 15400:
		Sleep(400);	//실린더 사용으로 PCB Stage UnGrip시 센서 감지 후, Delay
		if (Dio.HolderGrip(false, false))
		{
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 15450;
		}
		else
		{
			logStr.Format("Lens Gripper 해제 실패..[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);

			iRtnFunction = -15400;
		}
		break;

	case 15450:
		if (Dio.HolderGripCheck(false, false))
		{
			iRtnFunction = 15452;
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > IO_DELAY_TIME)
		{
			if (askMsg("Holder UnGrip Fail \n계속 진행하시겠습니까?") == IDOK)
			{
				iRtnFunction = 15452;
				break;
			}
			logStr.Format("PCB Stage Lens Gripper 해제 실패..[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);

			iRtnFunction = -15450;
		}
		Sleep(600);
		break;
	case 15452:

		iRtnFunction = 15455;
		break;

	case 15455:

		iRtnFunction = 15500;
		break;
	case 15500: // 대기 위치 이동		//렌즈 그립상태에서 시작하면 이리 온다 수정하지마

		if (!motor.LENS_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("Lens Z 대기 위치 이동 실패 [%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -15500;
			break;
		}
		//
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("PCB waiting Z 이동 실패");
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -15500;
			break;
		}
		iRtnFunction = 15550;
		break;
	case 15550:
		//if (motor.Pcb_Motor_Move(Wait_Pos))			//PCB부 모터 대기위치 이동


		if (motor.Pcb_Motor_MoveY(Wait_Pos))
		{
			iRtnFunction = 15800;
			logStr.Format("Pcb y 대기 위치 이동 완료 [%d]", iUseStep);
			putListLog(logStr);
		}
		else
		{
			logStr.Format("Pcb y 대기 위치 이동 실패 [%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = -15550;
		}
		break;
	case 15800:

		Task.LensTask = 30000;	//pcb AA일때 lens 는 Align 이동후 laser
		iRtnFunction = 15900;

		break;
	case 15900:

		iRtnFunction = 26000;

		//pcb 는 
		//lens가 Align , laser마치고 
		//본딩위치로 빠지기 전까지 대기 위치로가서 대기해야된다.

		//if (Task.interlockLens == 1)	//PCB AA 사용
		//{
		//	Task.interlockLens = 0;	//PCB AA 사용
		//	iRtnFunction = 26000;
		//}
		break;
	default:
		logStr.Format("Lens 공급 동작 Thread Step 번호 비정상 . [%d]", iUseStep);
		errMsg2(Task.AutoFlag, logStr);
		iRtnFunction = -1;
		break;
	}

	return iRtnFunction;
}

int	CPcbProcess2::RunProc_LensAlign(int iUseStep)			//(35000 ~ 39000)
{
	int iRtnFunction = iUseStep;
	int iRtn = 0;
	CString logStr = "";
	bool bChk = true;
	double offsetX = 0.0, offsetY = 0.0, offsetTh = 0.0;
	int iCamDelay = model.strInfo_Cam[1].m_iDelayTime;	//PCB 영상 획득 Delay
	int iAlignRetry = model.strInfo_Cam[1].m_iRetryCnt;
	int iLaserDelay = model.strInfo_Cam[0].m_iDelayTime;	//Laser 측정전 Delay
	switch (iUseStep)
	{
	case 35000:
		checkMessage();
		offsetX = offsetY = offsetTh = 0.0;
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("		PCB Z축 대기위치 이동 실패[%d]", iUseStep);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -35000;
			break;
		}
		Task.d_Align_offset_x[LENS_Align_MARK] = 0;
		Task.d_Align_offset_y[LENS_Align_MARK] = 0;
		Task.d_Align_offset_th[LENS_Align_MARK] = 0;

		iRtnFunction = 35050;	//2호기 lens align pass 240723
		break;

#if 1
	case 35050:
		if (sysData.m_iAlignCamInspPass == 1)		//xxxxx
		{
			Task.m_iRetry_Opt = 0;
			iRtnFunction = 35400;
			break;
		}
		Task.m_iRetry_Opt = 0;
		iRtnFunction = 35100;
		break;

	case 35100:
		Task.m_bOKLensPass = -1;//PCB언로드 과정에서 넘김상태로 만들어놓으므로 초기화.
		Task.d_Align_offset_x[LENS_Align_MARK] = 0;
		Task.d_Align_offset_y[LENS_Align_MARK] = 0;
		Task.d_Align_offset_th[LENS_Align_MARK] = 0;


		if (Task.m_bOKLensPass != 1)//! Lens 넘김 미완료 일 경우	 
		{
			iRtnFunction = 35150;
			break;
		}
		else
		{
			logStr.Format("Lens 넘김 완료로 Lens Align Pass![%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = 35400;
			break;
		}
		break;
	case 35150:					//IM
		if (motor.Pcb_Motor_Move(Lens_Pos))
		{
			sLangChange.LoadStringA(IDS_STRING1498);
			logStr.Format(sLangChange + _T("[%d]"), MotorPosName[Lens_Pos], iUseStep);
			iRtnFunction = 35151;
			break;
		}
		else
		{
			sLangChange.LoadStringA(IDS_STRING1499);
			logStr.Format(sLangChange + _T("[%d]"), MotorPosName[Lens_Pos], iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -35150;
			break;
		}
		break;
	case 35151:
		theApp.MainDlg->ctrlSubDlg(MAIN_DLG);
		theApp.MainDlg->m_iCurCamNo = 0;
		//SetDigReference(LENS_Align_MARK);
		LightControl.ctrlLedVolume(LIGHT_PCB, model.m_iLedValue[LEDDATA_LENS]);		// Align만 조명 ON
		if (motor.Pcb_Motor_Move(Lens_Pos))
		{
			if (motor.PCB_Z_Motor_Move(Lens_Pos))
			{
				logStr.Format("PCB Lens_Pos Align 위치 이동 완료[%d]", iUseStep);
				putListLog(logStr);
				Task.PCBTaskTime = myTimer(true);
				iRtnFunction = 35152;
				break;
			}
		}
		else
		{
			logStr.Format("PCB Lens Align 위치 이동 실패 [%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -35150;
			break;
		}
		break;

	case 35152:
		//LensHoleFind
		iRtn = theApp.MainDlg->procCamComAlign(CAM1, LENS_Align_MARK, false, offsetX, offsetY, offsetTh);
		if (iRtn == 1)
		{
			logStr.Format("[자동 Lens Hole Find] 마크 인식 성공");
			putListLog(logStr);
			iRtnFunction = 35200;
			break;
		}
		else
		{
			logStr.Format("[자동 Lens Hole Find] 마크 인식 실패");
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -35152;
			break;
		}
		break;
	case 35200:
		if ((myTimer(true) - Task.PCBTaskTime) > iCamDelay && (motor.IsStopAxis(Motor_PCB_X) && motor.IsStopAxis(Motor_PCB_Y)))
		{
			iRtnFunction = 35250;
			break;
		}
		break;

	case 35250:

		if (Task.m_iRetry_Opt>iAlignRetry)
		{
			logStr.Format("PCB Lens Align 재검사 %d 회 실패[%d]\n 보정 미적용으로 진행하시겠습니까?", Task.m_iRetry_Opt, iUseStep);
			if (askMsg(logStr) == IDOK)
			{
				Task.d_Align_offset_x[LENS_Align_MARK] = 0;
				Task.d_Align_offset_y[LENS_Align_MARK] = 0;
				Task.d_Align_offset_th[LENS_Align_MARK] = 0;
				iRtnFunction = 35400;
				break;
			}
			else
			{
				Task.m_iRetry_Opt = 0;
				logStr.Format("PCB Lens Align 재검사 시작[%d]", iUseStep);
				putListLog(logStr);
				iRtnFunction = 35250;
				break;

				//iRtnFunction = -35250;
				//logStr.Format("PCB Align 재검사 %d 회 실패[%d]", Task.m_iRetry_Opt, iUseStep);
				//errMsg2(Task.AutoFlag,logStr);
			}
			break;
		}

		offsetX = offsetY = offsetTh = 0.0;

		iRtn = theApp.MainDlg->procCamAlign(CAM1, LENS_Align_MARK, false, offsetX, offsetY, offsetTh);
		saveInspImage(LENS_IMAGE_SAVE, Task.m_iRetry_Opt);
		Task.m_iRetry_Opt++;
		offsetTh = 0;
		if (iRtn == 0)
		{
			Task.d_Align_offset_x[LENS_Align_MARK] -= offsetX;
			Task.d_Align_offset_y[LENS_Align_MARK] -= offsetY;
			Task.d_Align_offset_th[LENS_Align_MARK] += 0.0;//offsetTh;

			Task.dPcbAlignTh = Task.d_Align_offset_th[LENS_Align_MARK];

			logStr.Format("PCB Lens Align : %.3lf %.3lf %.3lf", Task.d_Align_offset_x[LENS_Align_MARK], Task.d_Align_offset_y[LENS_Align_MARK], Task.d_Align_offset_th[LENS_Align_MARK]);
			//pcbDlg->m_labelAlignResult.SetText(logStr);
			//pcbDlg->m_labelAlignResult.Invalidate();

			putListLog(logStr);

			int iRtnVal = theApp.MainDlg->AlignLimitCheck(CAM1, offsetX, offsetY, offsetTh);

			if (iRtnVal == 1)
			{
				iRtnFunction = 35300;				// 보정 이동
				break;
			}
			else if (iRtnVal == 2)
			{
				logStr.Format("		PCB Lens Align [%d] 완료 [%d]", Task.m_iRetry_Opt, iUseStep);
				putListLog(logStr);
				//InstantMarkDelete(PCB_Chip_MARK);			//임시 등록 마크 삭제

				logStr.Format("		PCB Lens Align Complete : %d, %.03f, %.03f, %.03f", Task.m_iPcbPickupNo, Task.d_Align_offset_x[LENS_Align_MARK], Task.d_Align_offset_y[LENS_Align_MARK], Task.d_Align_offset_th[LENS_Align_MARK]);
				AlignResultSave(logStr);
				Task.m_iRetry_Opt = 0;

				Task.m_timeChecker.Measure_Time(4);	//Laser 변위 측정 시작 시간

				iRtnFunction = 35450;  //35400;		// 완료
				break;
			}
			else
			{
				logStr.Format("PCB Lens Align [%d] 보정 범위 초과", Task.m_iRetry_Opt, iUseStep);
				errMsg2(Task.AutoFlag, logStr);
				AlignLogSave(logStr);
				//InstantMarkDelete(PCB_Chip_MARK);
				iRtnFunction = -35250;				// NG
				break;
			}
		}
		else
		{
			logStr.Format("PCB Lens Align [%d] 마크 인식 실패[%d]", Task.m_iRetry_Opt, iUseStep);
			putListLog(logStr);

			iRtnFunction = 35200;				//  재검사 
			break;
			Sleep(300);
		}
		break;

	case 35300://- Sensor Align Retry
		if (motor.Pcb_Holder_Align_Move(Lens_Pos, Task.d_Align_offset_x[LENS_Align_MARK], Task.d_Align_offset_y[LENS_Align_MARK], Task.d_Align_offset_th[LENS_Align_MARK]))
		{
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 35450;
			break;
		}
		else
		{
			logStr.Format("PCB Lens Align 보정 위치 이동 실패[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -35300;
			break;
		}
		break;
	case 35400:
		if (motor.Pcb_Motor_Move(Wait_Pos))
		{
			sLangChange.LoadStringA(IDS_STRING1498);
			logStr.Format(sLangChange + _T("[%d]"), MotorPosName[Wait_Pos], iUseStep);
			iRtnFunction = 35450;
			break;
		}
		else
		{
			sLangChange.LoadStringA(IDS_STRING1499);	//PCB부 z축 모터 위치 이동 실패[%d]
			logStr.Format(sLangChange + _T("[%d]"), MotorPosName[Wait_Pos], iUseStep);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -35400;
			break;
		}
		break;
#endif
	case 35450:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("PCB Z축 대기위치 이동 실패[%d]", iUseStep);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -35450;
			break;
		}
		iRtnFunction = 35500;
		break;
	case 35500:
		//LensHoleFind XY 축 이동
		iRtnFunction = 35510;
		break;
	case 35510:
		//LensHoleFind Z 축 이동
		iRtnFunction = 35520;
		break;
	case 35520:
		
	case 35530:
		//LensHoleFind
		iRtnFunction = 39000;
		break;
	default:
		logStr.Format("Lens 외부 Align Thread Step 번호 비정상 [%d]", iUseStep);
		errMsg2(Task.AutoFlag, logStr);
		iRtnFunction = -1;
		break;
	}
	logStr.Empty();
	return iRtnFunction;
}

int CPcbProcess2::RunProc_LensLoading(int iUseStep)
{//! Lens Pickup에 제품 넘김 Step	(15000 ~ 16600)
	int iRtnFunction = iUseStep;
	int iRtn = 0;
	CString logStr = "";
	double	dFinalDelay = (double)(model.strInfo_Cam[3].m_iDelayTime);
	bool bChk = true;
	double offsetX = 0.0, offsetY = 0.0, offsetTh = 0.0;
	//Task.m_bOKLensPass = -1;//PCB언로드 과정에서 넘김상태로 만들어놓으므로 초기화.

	switch (iUseStep)
	{
	case 39000:

		if (!motor.LENS_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("Lens_Z축 대위치 이동 실패[%d]", iUseStep);
			putListLog(logStr);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -39000;
			break;
		}
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("PCB Z축 대기위치 이동 실패[%d]", iUseStep);
			putListLog(logStr);
			delayMsg(logStr, 3000, M_COLOR_RED);
			iRtnFunction = -39000;
			break;
		}
		if (Task.m_bOKLensPass != 1)//! Lens 넘김 미완료 일 경우	 
		{
			//레이저후 틸트 심해서 본딩위치갈때 다시 레이저 틸트된 tx,ty 값으로 이동 

			if (!motor.Pcb_Tilt_Motor_Move(Loading_Pos))
			{
				logStr.Format("PCB %s 이동 실패", MotorPosName[Loading_Pos]);
				putListLog(logStr);
				delayMsg(logStr, 3000, M_COLOR_RED);
				iRtnFunction = -39000;
				break;
			}
			if (!motor.Pcb_Motor_Move(Loading_Pos, Task.d_Align_offset_x[LENS_Align_MARK], Task.d_Align_offset_y[LENS_Align_MARK], Task.d_Align_offset_th[LENS_Align_MARK]))
			{
				logStr.Format("PCB %s 이동 실패", MotorPosName[Loading_Pos]);
				putListLog(logStr);
				delayMsg(logStr, 3000, M_COLOR_RED);
				iRtnFunction = -39000;
				break;
			}
			iRtnFunction = 39100;
			break;
		}
		else
		{
			iRtnFunction = 39500;	//렌즈 로드 완료 Jump
		}
		break;

	case 39100:
		if (!Dio.LensMotorGrip(false, false))
		{
			logStr.Format("Lens Unit Gripper 해제 실패[%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = -39100;
			break;
		}
		Task.PCBTaskTime = myTimer(true);
		iRtnFunction = 39150;
		break;

	case 39150:
		if (Dio.LensMotorGripCheck(false, false))
		{
			iRtnFunction = 39170;
			Task.PCBTaskTime = myTimer(true);
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > IO_DELAY_TIME)
		{
			iRtnFunction = -39150;
		}
		break;
	case 39170:
		iRtnFunction = 39200;
		break;

	case 39200: // 공급 
		if (!motor.Lens_Tilt_Motor_Move(Loading_Pos))
		{
			logStr.Format("Lens %s Tx,Ty이동 실패", MotorPosName[Loading_Pos]);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -39200;
			break;
		}
		if (!motor.Lens_Motor_MoveXY(Loading_Pos))
		{
			logStr.Format("Lens %s X,Y 이동 실패", MotorPosName[Loading_Pos]);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -39200;
			break;
		}

		logStr.Format("Lens 공급 위치 이동 완료[%d]", iUseStep);
		putListLog(logStr);
		iRtnFunction = 39210;
		break;
	case 39210:
		iRtnFunction = 39250;
		break;
	case 39250:
		if (!motor.PCB_Z_Motor_Move(Loading_Pos))
		{
			logStr.Format("PCB loading Z 이동 실패");
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -39250;
			break;
		}
		iRtnFunction = 39251;
		break;
	case 39251:
		if (!motor.LENS_Z_Motor_Move(Loading_Pos))
		{
			logStr.Format("Lens Z 위치 이동 실패 [%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -39251;
			break;
		}
		iRtnFunction = 39252;
		break;
	case 39252:
		Dio.LensMotorGrip(true, false);
		Sleep(500);
		iRtnFunction = 39255;
		break;

	case 39255:
		Dio.LensMotorGrip(false, false);
		Sleep(300);
		iRtnFunction = 39300;
		break;
	case 39300: // 모터 그립
		if (Dio.LensMotorGrip(true, false))
		{
			Task.m_bOKLensPass = 1;
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 39350;
		}
		else
		{
			Task.m_bOKLensPass = -1;
			logStr.Format("Lens 그립 실패 [%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -39300;
		}
		break;

	case 39350://모터 그립 확인
		if (Dio.LensMotorGripCheck(true, false))
		{
			logStr.Format("Lens 그립 완료[%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = 39400;
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > IO_DELAY_TIME)
		{
			logStr.Format("Lens Gripper 전진 센서 시간 초과..[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -39350;
		}
		break;

	case 39400:
		Sleep(500);
		if (Dio.HolderGrip(false, false))
		{
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 39455;
		}
		else
		{
			logStr.Format("Lens Gripper 해제 실패..[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);

			iRtnFunction = -39400;
		}
		
		break;

	case 39455:
		if (Dio.HolderGripCheck(false, false))
		{
			iRtnFunction = 39500;
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > IO_DELAY_TIME)
		{
			if (askMsg("Holder UnGrip Fail \n계속 진행하시겠습니까?") == IDOK)
			{
				iRtnFunction = 39500;
				break;
			}
			logStr.Format("PCB Stage Lens Gripper 해제 실패..[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);

			iRtnFunction = -39400;
		}
		Sleep(300);
		
		break;
	case 39500: // 대기 위치 이동
		if (!motor.LENS_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("Lens Z 대기 위치 이동 실패 [%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -39500;
			break;
		}
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("PCB waiting Z 이동 실패");
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -39500;
			break;
		}
		iRtnFunction = 39550;
		break;
	case 39550:
		iRtnFunction = 39900;
		break;
	case 39900:
		iRtnFunction = 39920;
		break;

	case 39920:	//jump step
		iRtnFunction = 40000;
		break;
	default:
		logStr.Format("Lens 공급 동작 Thread Step 번호 비정상 . [%d]", iUseStep);
		errMsg2(Task.AutoFlag, logStr);
		iRtnFunction = -1;
		break;
	}

	return iRtnFunction;
}

int CPcbProcess2::procProductComplete(int iStep)
{
	CString logStr = "";
	CString sSocketMsg = "";
	CString sBarCode = "";
	//
	int iRtnFunction = iStep;
	int iCamDelay = model.strInfo_Cam[1].m_iDelayTime;	//PCB 영상 획득 Delay
	int iLaserDelay = model.strInfo_Cam[0].m_iDelayTime;	//Laser 측정전 Delay
	int iAlignRetry = model.strInfo_Cam[1].m_iRetryCnt;
	double offsetX = 0.0;
	double offsetY = 0.0;
	double offsetTh = 0.0;
	int iTestPatCnt = 0;
	int iRtn = 0;
	//
	vision.clearOverlay(CCD);
	vision.drawOverlay(CCD);
	theApp.MainDlg->ctrlSubDlg(MAIN_DLG);
	theApp.MainDlg->m_iCurCamNo = 0;
	theApp.MainDlg->changeMainBtnColor(MAIN_DLG);
	//
	switch (iStep)
	{
	case 11000:	// PCB MIU 연결	
		iLaser_Pos = 0;
		Task.oldLaserTx = 0.1;
		Task.oldLaserTy = 0.1;
		Task.d_Align_offset_x[PCB_Chip_MARK] = 0;
		Task.d_Align_offset_y[PCB_Chip_MARK] = 0;
		Task.d_Align_offset_th[PCB_Chip_MARK] = 0;
		Task.PCBTaskTime = myTimer(true);
		//if (sysData.m_FreeRun == 0)		
		//{
		//	bThread_MIUCheckRun = true;
		//	if (!MIUCheck_process() || gMIUDevice.CurrentState != 4)
		//	{
		//		sLangChange.LoadStringA(IDS_STRING452);	//CCD 모듈 영상 초기화 실패.[%d]\n 제품 안착 상태 및 제품 불량 확인 하세요.
		//		logStr.Format(sLangChange, iStep);
		//		errMsg2(Task.AutoFlag, logStr);
		//		iRtnFunction = -11000;
		//		break;
		//	}
		//	bThread_MIUCheckRun = false;
		//}
		iRtnFunction = 12000;
		break;
	case 12000:
		//확인필요 norinda
		Task.m_bPBStart = 1;
		//if( Task.m_bPBStart ==  1 )
		//{
		//	func_Socket_Barcode();
		//}
		//else
		//{
		//	//! 바코드가 없기 때문에 통신 사용 안함.
		//	Task.iRecvLenACK[0] = Task.iRecvLenACK[1] = 0;
		//	Task.dTiltingManual[0] = Task.dTiltingManual[1] = 0.0;
		//	Task.dAlignManual[0] = Task.dAlignManual[0] = Task.dAlignManual[0] = 0.0;
		//}
		//iRtnFunction = 12900;			//laser 변위로 점프
		//break;
		
		
		if (sysData.m_iAlignCamInspPass == 1)		//procProductComplete
		{
			logStr.Format("완제품 Align Pass[%d]", iStep);
			putListLog(logStr);
			iRtnFunction = 12800;
			break;
		}

		iRtnFunction = 12100;			//laser 변위로 점프
		break;
		
		
		break;
	case 12100:
		
		Task.PCBTaskTime = myTimer(true);
		iRtnFunction = 12110;
		break;
	case 12110:

		Task.m_iRetry_Opt = 0;
		//SetDigReference(PCB_Holder_MARK);
		LightControl.ctrlLedVolume(LIGHT_PCB, model.m_iLedValue[LEDDATA_HOLDER]);		// Align만 조명 ON

		Task.d_Align_offset_x[PCB_Chip_MARK] = 0;
		Task.d_Align_offset_y[PCB_Chip_MARK] = 0;
		Task.d_Align_offset_th[PCB_Chip_MARK] = 0;

		if (motor.Pcb_Motor_Move(CompleteAlign_Pos))
		{
			Task.PCBTaskTime = myTimer(true);
			logStr.Format("Pcb 완제품 Align 위치 이동 완료[%d]", iStep);
			putListLog(logStr);
			iRtnFunction = 12200;
		}
		else
		{
			logStr.Format("Pcb 완제품 Align 위치 이동 실패[%d]", iStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -12100;
		}
		break;
	case 12200:
		if (motor.PCB_Z_Motor_Move(CompleteAlign_Pos))
		{
			Task.PCBTaskTime = myTimer(true);
			logStr.Format("Pcb 완제품 Align Z위치 이동 완료[%d]", iStep);
			putListLog(logStr);
			iRtnFunction = 12400;
		}
		else
		{
			logStr.Format("Pcb 완제품 Align Z위치 이동 실패[%d]", iStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -12200;
		}
		break;

	case 12400:
		checkMessage();
		if ((myTimer(true) - Task.PCBTaskTime) > iCamDelay && (motor.IsStopAxis(Motor_PCB_X) && motor.IsStopAxis(Motor_PCB_Y)))
		{
			iRtnFunction = 12500;
		}
		break;
	case 12500:

		if (Task.m_iRetry_Opt>iAlignRetry)
		{
			logStr.Format("PCB 완제품 Align 재검사 %d 회 실패[%d]\n 보정 미적용으로 진행하시겠습니까?", Task.m_iRetry_Opt, iStep);
			if (askMsg(logStr) == IDOK)
			{
				Task.d_Align_offset_x[PCB_Chip_MARK] = 0;
				Task.d_Align_offset_y[PCB_Chip_MARK] = 0;
				Task.d_Align_offset_th[PCB_Chip_MARK] = 0;
				iRtnFunction = 12800;
			}
			else
			{
				iRtnFunction = -12500;
				logStr.Format("PCB Align 재검사 %d 회 실패[%d]", Task.m_iRetry_Opt, iStep);
				errMsg2(Task.AutoFlag, logStr);
			}
			break;

		}
		//-----------------------------------
		offsetX = offsetY = offsetTh = 0.0;
		iRtn = theApp.MainDlg->procCamComAlign(CAM1, PCB_Chip_MARK, false, offsetX, offsetY, offsetTh);

		offsetTh = 0.0;
		saveInspImage(PCB_IMAGE_SAVE, Task.m_iRetry_Opt);
		Task.m_iRetry_Opt++;
		if (iRtn == 1)
		{
			Task.d_Align_offset_x[PCB_Chip_MARK] -= offsetX;
			Task.d_Align_offset_y[PCB_Chip_MARK] -= offsetY;
			Task.d_Align_offset_th[PCB_Chip_MARK] += offsetTh;

			logStr.Format("PCB 완제품 Align : %.3lf %.3lf %.3lf", Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]);
			//pcbDlg->m_labelAlignResult.SetText(logStr);
			//pcbDlg->m_labelAlignResult.Invalidate();
			putListLog(logStr);

			int iRtnVal = theApp.MainDlg->AlignLimitCheck(CAM1, offsetX, offsetY, offsetTh); // PCB이재기 움직이는 부분이랑 Limit Check 할때 CAM1임

			if (iRtnVal == 1)
			{
				iRtnFunction = 12700;				// 보정 이동
			}
			else if (iRtnVal == 2)
			{
				iLaser_Pos = 0;
				logStr.Format("		PCB 완제품 Align [%d] 완료 [%d]", Task.m_iRetry_Opt, iStep);
				putListLog(logStr);
				//InstantMarkDelete(PCB_Chip_MARK);
				logStr.Format("		PCB 완제품 Align Complete :  %d, %.03f, %.03f, %.03f", Task.m_iPcbPickupNo, Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]);
				AlignResultSave(logStr);
				Task.m_iRetry_Opt = 0;
				Task.dSocketRecvTime = myTimer(true);
				iRtnFunction = 12800;

			}
			else
			{
				logStr.Format("PCB 완제품 Align [%d] 보정 범위 초과[%d]", Task.m_iRetry_Opt, iStep);
				errMsg2(Task.AutoFlag, logStr);
				AlignLogSave(logStr);
				//InstantMarkDelete(PCB_Chip_MARK);
				iRtnFunction = -12500;
			}
		}
		else
		{
			logStr.Format("PCB 완제품 Align [%d] 마크 인식 실패[%d]", Task.m_iRetry_Opt, iStep);
			putListLog(logStr);
			iRtnFunction = 12500;				//  재검사 
		}
		break;

	case 12700://!! 보정량 이동.- Retry
		if (motor.Pcb_Holder_Align_Move(CompleteAlign_Pos, Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]))
		{
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 12200;
		}
		else
		{
			logStr.Format("Pcb 완제품 Align 보정 위치 이동 실패[%d]", iStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -12700;
		}
		break;
	case 12800:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("PCB Z축 대기위치 이동 실패[%d]", iStep);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -12800;
			break;
		}

		iRtnFunction = 12850;


		break;
	case 12850:
		iLaser_Pos = 0;
		vision.clearOverlay(CAM1);
		//vision.drawOverlay(CAM1);
		//외부 변위측정값 Read
#if (____AA_WAY == LENS_TILT_AA)//PCB_TILT_AA) 
		if (g_ADOData.func_Get_RecordData(Task.ChipID))//DB에 Data가 있을 경우
		{

			Task.dAAPcbMotor[0] = g_ADOData.adoRegist.dPCBMotor[0];   //PCB X
			Task.dAAPcbMotor[1] = g_ADOData.adoRegist.dPCBMotor[1];   //PCB Y
			Task.dAAPcbMotor[2] = g_ADOData.adoRegist.dPCBMotor[2];   //PCB TH
																	  //TX[3] , TY[4]
			Task.dAAPcbMotor[3] = g_ADOData.adoRegist.dPCBMotor[3];   //PCB TX 
			Task.dAAPcbMotor[4] = g_ADOData.adoRegist.dPCBMotor[4];   //PCB TY 
																	  //
			Task.dAAPcbMotor[5] = g_ADOData.adoRegist.dPCBMotor[5];   //PCB Z
			Task.dAlignManual[0] = g_ADOData.adoRegist.dOffset_Align[0];  //AlignOffsetX
			Task.dAlignManual[1] = g_ADOData.adoRegist.dOffset_Align[1];  //AlignOffsetY
			Task.dAlignManual[2] = g_ADOData.adoRegist.dOffset_Align[2];  //AlignOffsetT
											
			logStr.Format("PCB 화상검사 Chart Pos X(%.3lf), Y(%.3lf)", Task.dAAPcbMotor[0], Task.dAAPcbMotor[1]);
			putListLog(logStr);
			//
			logStr.Format("PCB 화상검사 TX(%.3lf), TY(%.3lf)", Task.dAAPcbMotor[3], Task.dAAPcbMotor[4]);
			putListLog(logStr);

			if (fabs(Task.dAAPcbMotor[0] - model.axis[Motor_PCB_X].pos[Bonding_Pos]) > 5.0)
			{
				logStr.Format("Pcb 화상검사 X spec Over[%d]", iStep);
				errMsg2(Task.AutoFlag, logStr);
				iRtnFunction = -12850;
				break;
			}
			if (fabs(Task.dAAPcbMotor[1] - model.axis[Motor_PCB_Y].pos[Bonding_Pos]) > 5.0)
			{
				logStr.Format("Pcb 화상검사 Y spec Over[%d]", iStep);
				errMsg2(Task.AutoFlag, logStr);
				iRtnFunction = -12850;
				break;
			}
			iRtnFunction = 12900;
			break;
		}
		else
		{
			Task.dAAPcbMotor[0] = model.axis[Motor_PCB_X].pos[Bonding_Pos];   //PCB X
			Task.dAAPcbMotor[1] = model.axis[Motor_PCB_Y].pos[Bonding_Pos];   //PCB Y
			Task.dAAPcbMotor[2] = model.axis[Motor_PCB_TH].pos[Bonding_Pos];   //PCB TH
																			   //TX[3] , TY[4]
			Task.dAAPcbMotor[3] = model.axis[Motor_PCB_Xt].pos[Bonding_Pos];   //PCB TX 	model.m_InspPcbTilt[0];//
			Task.dAAPcbMotor[4] = model.axis[Motor_PCB_Yt].pos[Bonding_Pos];   //PCB TY 	model.m_InspPcbTilt[1];//

																			   //
			Task.dAAPcbMotor[5] = model.axis[Motor_PCB_Z].pos[Bonding_Pos];   //PCB Z

			iRtnFunction = 12900;

			//iRtnFunction = 12900;
			//logStr.Format("일치 모델 없습니다.\ bonding 위치로 진행 하시겠습니까?");	//전체 원점 복귀를 실행 하시겠습니까?
			//if (askMsg(logStr))
			//{

			//	
			//	break;
			//}
			/*logStr.Format("일치 모델 없습니다.[%d]", iStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -12850;*/
			//일치 모델 없을 경우 수동 티칭값 창으로.
			/*Task.m_iRtnTiltingDlg = 2;
			TiltingManualdlg->ShowWindow(SW_SHOW);
			iRtnFunction = 12870;*/
		}


#else //#elif (____AA_WAY == LENS_TILT_AA)
		Task.dTiltingManual[0] = 0.0;
		Task.dTiltingManual[1] = 0.0;
		iRtnFunction = 12900;
		/*
		Task.dTiltingManual[0] = g_ADOData.adoRegist.dOffset_TiltTx;
		Task.dTiltingManual[1] = g_ADOData.adoRegist.dOffset_TiltTy;

		Task.dAlignManual[0] = g_ADOData.adoRegist.dOffset_Align[0];
		Task.dAlignManual[1] = g_ADOData.adoRegist.dOffset_Align[1];
		Task.dAlignManual[2] = g_ADOData.adoRegist.dOffset_Align[2];
		*/

		break;
#endif
		break;
	case 12870:
		if (Task.m_iRtnTiltingDlg == 0)
		{
			logStr.Format("변위측정 Data 입력 중 자동모드 정지 선택[%d]", iStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -12870;
			break;
		}
		else if (Task.m_iRtnTiltingDlg == 1)
		{
			logStr.Format("외부 변위 Tilting 완료 위치 : Tx=%.03lf, Ty=%.03lf", Task.dTiltingManual[0], Task.dTiltingManual[1]);
			putListLog(logStr);

			Task.m_timeChecker.Measure_Time(4);	//Laser 변위 측정 시작 시간
												//iRtnFunction = 12900;//pcb aa또 레이저 하도록 200708

			iRtnFunction = 12900;

		}
		break;
	case 12900:
		if (sysData.m_iLaserInspPass == 1)		//완제품
		{
			logStr.Format("완제품 Laser pass");
			putListLog(logStr);
			iRtnFunction = 13300;		//완제품시 레이저 패스
			break;
		}

		if (!motor.Pcb_Tilt_Motor_Move(Com_Laser_Pos))
		{
			logStr.Format("PCB tx,ty Com_Laser_Pos 이동 실패");
			errMsg2(Task.AutoFlag, logStr);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -12900;
			break;
		}
		Task.PCBTaskTime = myTimer(true);
		iRtnFunction = 12901;
		break;

	case 12901:
			////if(motor.Pcb_Motor_Move_Laser(iLaser_Pos, Task.d_Align_offset_x[PCB_Holder_MARK], Task.d_Align_offset_y[PCB_Holder_MARK], Task.d_Align_offset_th[PCB_Holder_MARK]))

		if (motor.Pcb_Motor_Move_ComLaser(iLaser_Pos, Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]))
		{
			if (motor.PCB_Z_Motor_Move(Com_Laser_Pos))
			{
				Task.PCBTaskTime = myTimer(true);
				logStr.Format("Laser 변위 측정 외부 위치 이동 완료[%d]", iStep);
				putListLog(logStr);
				iRtnFunction = 12910;// 12950;
			}
			else
			{
				logStr.Format("PCB Com_Laser_Pos Z 이동 실패[%d]", iStep);
				putListLog(logStr);
				errMsg2(Task.AutoFlag, logStr);
				iRtnFunction = -12900;
				break;
			}
		}
		else
		{
			logStr.Format("Laser 변위 측정 외부 위치 이동 실패[%d]", iStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -12900;
		}

		break;
	case 12910:

		iRtnFunction = 12920;
		break;

	case 12920:
		iRtnFunction = 12950;
		break;
		//laser실린더 하강 END
	case 12950:
		if ((myTimer(true) - Task.PCBTaskTime) > iLaserDelay && (motor.IsStopAxis(Motor_PCB_X) && motor.IsStopAxis(Motor_PCB_Y)))
		{
			iRtnFunction = 13100;
		}
		break;
	case 13100:
		Keyence.func_LT9030_Scan(Task.m_Laser_Point[iLaser_Pos]);  //func_LT9030_Scan

		MandoInspLog.dLaserTestComPoint[iLaser_Pos] = Task.m_Laser_Point[iLaser_Pos];

		//Keyence.func_CL3000_Scan(Task.m_Laser_Point[iLaser_Pos]);
		Sleep(100);
		logStr.Format("변위 센서 %lf[%d] - 외부 - %d 위치", Task.m_Laser_Point[iLaser_Pos], iStep, iLaser_Pos + 1);
		putListLog(logStr);
		LaserPos[iLaser_Pos].x = motor.GetEncoderPos(Motor_PCB_X);
		LaserPos[iLaser_Pos].y = motor.GetEncoderPos(Motor_PCB_Y);
		LaserValue[iLaser_Pos] = Task.m_Laser_Point[iLaser_Pos];

		if (Task.m_Laser_Point[iLaser_Pos] != 0)
		{
			if (iLaser_Pos == 3)
			{
				if (theApp.MainDlg->func_Check_LaserValueErr(LaserValue) == false)
				{
					logStr.Format("Laser 측정값 이상..외부 변위 측정값이 이상..[%d]\n 측정값:%.04lf, %.04lf, %.04lf, %.04lf ", iStep, LaserValue[0], LaserValue[1], LaserValue[2], LaserValue[3]);
					errMsg2(Task.AutoFlag, logStr);
					iRtnFunction = -13100;
					break;
				}

				if (theApp.MainDlg->_calcLaserTilt(LaserPos, LaserValue, Task.d_Align_offset_xt[0], Task.d_Align_offset_yt[0]))
				{
					/*	logStr.Format("		보정량 Tx: %.04lf, Ty: %.04lf", Task.d_Align_offset_xt[0], Task.d_Align_offset_yt[0] );
					putListLog(logStr);
					logStr.Format("		내부 보정량 편차 Tx: %.04lf, Ty: %.04lf", Task.dTiltingManual[0], Task.dTiltingManual[1] );
					putListLog(logStr);
					int Rnd = TiltAlignLimitCheck(Task.d_Align_offset_xt[0] + Task.dTiltingManual[0], Task.d_Align_offset_yt[0] + Task.dTiltingManual[1] );
					*/


					//Task.m_dataOffset_x[0] =  Task.d_Align_offset_xt[PCB_Holder_MARK];
					//Task.m_dataOffset_y[0] =  Task.d_Align_offset_yt[PCB_Holder_MARK];
					logStr.Format("		보정량 Tx: %.04lf, Ty: %.04lf", Task.d_Align_offset_xt[0], Task.d_Align_offset_yt[0]);
					putListLog(logStr);
					logStr.Format("		외부 보정량 편차 Tx: %.04lf, Ty: %.04lf", Task.dTiltingManual[0], Task.dTiltingManual[1]);
					putListLog(logStr);


					//int Rnd = TiltAlignLimitCheck(Task.d_Align_offset_xt[PCB_Holder_MARK],Task.d_Align_offset_yt[PCB_Holder_MARK]);
					//int Rnd = TiltAlignLimitCheck(Task.d_Align_offset_xt[0] + Task.dTiltingManual[0], Task.d_Align_offset_yt[0] + Task.dTiltingManual[1] );


					int Rnd = 2; //theApp.MainDlg->TiltAlignLimitCheck(Task.d_Align_offset_xt[0], Task.d_Align_offset_yt[0]); //250207LIM
					if (Rnd == 2)
					{
						Task.m_timeChecker.Measure_Time(5);	//Laser 변위 측정 완료 시간
						Task.m_dTime_LaserDpm = Task.m_timeChecker.m_adTime[5] - Task.m_timeChecker.m_adTime[4];
						//dispGrid();
						iRtnFunction = 13300;

					}
					else if (Rnd == 1)
					{
						iRtnFunction = 13200;	//보정량 이동		
					}
					else
					{
						logStr.Format("Laser Tilt  보정값 Limit를 초과 하였습니다.[%d]", iStep);
						errMsg2(Task.AutoFlag, logStr);
						iRtnFunction = -13100;
					}
				}
			}
			else
			{
				iRtnFunction = 12900;
				iLaser_Pos++;
			}
		}
		else
		{
			iRtnFunction = 13100;
		}
		break;
	case 13200:
		//if(motor.Pcb_Move_Tilt(Task.d_Align_offset_xt[0] + Task.dTiltingManual[0],Task.d_Align_offset_yt[0] + Task.dTiltingManual[1] ))


		if (motor.Pcb_Move_Tilt(Task.d_Align_offset_xt[0], Task.d_Align_offset_yt[0]))
		{
			iLaser_Pos = 0;
			iRtnFunction = 12900;
		}
		break;

	case 13300:
		iRtnFunction = 13310;
		break;
	case 13310:
		iRtnFunction = 13350;
		break;
	case 13350:
		if (motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("PCB Z 대기 위치 이동 완료[%d]", iRtnFunction);
			putListLog(logStr);
			iRtnFunction = 14000;
		}
		else
		{
			logStr.Format("PCB Z 대기 위치 이동 실패[%d]", iRtnFunction);
			putListLog(logStr);
			iRtnFunction = -13350;
		}
		break;
	case 14000:

		iRtnFunction = 14100;
		break;
	case 14100:
		Task.PCBTaskTime = myTimer(true);
		iRtnFunction = 14200;
		break;

	case 14200:
		if ((myTimer(true) - Task.PCBTaskTime) > iCamDelay && (motor.IsStopAxis(Motor_PCB_X) && motor.IsStopAxis(Motor_PCB_Y)))
		{
			iRtnFunction = 14300;
			Task.m_iRetry_Opt = 0;
		}
		break;
	case 14300:

		iRtnFunction = 14400;				// 완료
		break;
	case 14400:
		iRtnFunction = 14500;
		break;
	case 14500:
		if (motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("PCB Z 대기 위치 이동 완료[%d]", iStep);
			putListLog(logStr);
			iRtnFunction = 15200;
		}
		else
		{
			logStr.Format("PCB Z 대기 위치 이동 실패[%d]", iStep);
			putListLog(logStr);
			iRtnFunction = -14500;
		}
		break;
	case 15200:
		LightControl.ChartAllControl(true);
		iRtnFunction = 19600;
		break;

	case 19600: // 본딩 위치 이동 
		

		if (motor.Pcb_Motor_Move(Bonding_Pos, Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]))
		{
			Task.PCBTaskTime = myTimer(true);
			logStr.Format("PCB Bonding 보정 위치 이동 완료[%d]", iStep);
			putListLog(logStr);
			iRtnFunction = 19700;
		}
		else
		{
			logStr.Format("PCB Bonding 위치 이동 실패[%d]", iStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -19600;
		}
		break;
	case 19700:
#if (____AA_WAY == PCB_TILT_AA)
		iRtnFunction = 19800;
#elif (____AA_WAY == LENS_TILT_AA)
		if (motor.Pcb_Move_Tilt(Task.dAAPcbMotor[3], Task.dAAPcbMotor[4]))
		{
			
			iRtnFunction = 19800;
		}
		else
		{
			logStr.Format(_T("PCB Tilt Bonding Pos Move Fail[%d]"), iStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -19700;
		}
		
#endif
		break;
	case 19800: //z축 본딩 위치 이동
		if (!motor.PCB_Z_Motor_Move(Bonding_Pos))
		{
			logStr.Format(_T("PCB Z Bonding Pos Move Fail[%d]"), iStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -19800;
			break;
		}
		Task.PCBTaskTime = myTimer(true);

		iRtnFunction = 19900;
		break;
	case 19900:
		if ((myTimer(true) - Task.PCBTaskTime) > iCamDelay && (motor.IsStopAxis(Motor_PCB_X) && motor.IsStopAxis(Motor_PCB_Y)))
		{
			

			//if( func_MIU_ConnectLiveCheck() == false)		//MIU 영상 Check
			//{
			//	iRtnFunction = -19900;
			//	break;
			//}
			theApp.MainDlg->setCamDisplay(3, 1);

			iRtnFunction = 120000;//완제품 검사
		}
		break;

	default:
		logStr.Format("PCB 완제품 검사 Step 이상 [%d]", iStep);
		errMsg2(Task.AutoFlag, logStr);
		iRtnFunction = -20000;
		break;
	}
	return iRtnFunction;
}
int CPcbProcess2::RunProc_LENS_AlignLaserMeasure(int iLensStep)
{
	int iRtnFunction = iLensStep;
	int iCamDelay = model.strInfo_Cam[1].m_iDelayTime;		//PCB 영상 획득 Delay
	int iAlignRetry = model.strInfo_Cam[1].m_iRetryCnt;
	int iRtn = 0;
	CString logStr = "";
	bool bChk = true;
	double offsetX = 0.0, offsetY = 0.0, offsetTh = 0.0;

	int iLaserDelay = model.strInfo_Cam[0].m_iDelayTime;	//Laser 측정전 Delay

	switch (iLensStep)
	{
	case 30000:
		Task.oldLaserTx = 0.1;
		Task.oldLaserTy = 0.1;
		Task.d_Align_offset_x[LENS_Align_MARK] = 0;
		Task.d_Align_offset_y[LENS_Align_MARK] = 0;
		Task.d_Align_offset_th[LENS_Align_MARK] = 0;
		//
		Task.m_iRetry_Opt = 0;

		if (motor.LENS_Z_Motor_Move(Wait_Pos))
		{
			Task.LensTaskTime = myTimer(true);
			iRtnFunction = 30050;
		}
		else
		{
			logStr.Format("Lens_Z축 대기위치 이동 실패.[%d]", iLensStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -30000;
		}

		break;

	case 30050:
		if (motor.Lens_Motor_MoveY(Wait_Pos))
		{
			logStr.Format("Lens Y 대기위치 이동 명령[%d]", iLensStep);
			putListLog(logStr);
			iRtnFunction = 30100;		//렌즈쪽 카메라 없음
		}
		else
		{
			logStr.Format("Lens Y 대기위치 이동 실패[%d]", iLensStep);
			putListLog(logStr);
			iRtnFunction = -30050;
		}
		break;
	case 30100:
		if (motor.Lens_Motor_MoveXY(Wait_Pos))
		{
#if (____AA_WAY == PCB_TILT_AA)
			//iRtnFunction = 30500;
			iRtnFunction = 43000;
			LightControl.ctrlLedVolume(LIGHT_PCB, model.m_iLedValue[LEDDATA_LENS]);

#elif (____AA_WAY == LENS_TILT_AA)

			iRtnFunction = 43000;		//렌즈쪽 카메라 없음
			break;

#endif
		}
		else
		{
			logStr.Format("Lens 대기위치 이동 실패[%d]", iLensStep);
			putListLog(logStr);
			iRtnFunction = -30050;
		}
		break;

	case 30500:
		if (Dio.CamLaserSlinderMove(true, true))
		{
			logStr.Format("Laser/Cam 실린더 전진 완료[%d]", iLensStep);
			putListLog(logStr);
			Sleep(500);
			Task.LensTaskTime = myTimer(true);
			iRtnFunction = 30600;

		}
		else
		{
			logStr.Format("Laser/Cam 실린더 전진 실패[%d]", iLensStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -30500;
		}

		break;
	case 30600:
		if (Dio.CamLaserSlinderCheck(true, false))
		{
			logStr.Format("Laser/Cam 실린더 전진 확인 완료[%d]", iLensStep);
			putListLog(logStr);
			iRtnFunction = 30900;
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > 13000)
		{
			logStr.Format("Laser/Cam 실린더 전진 시간 초과[%d]", iLensStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -30600;
		}
		break;
	case 30900:
		if (sysData.m_iLaserInspPass == 1)
		{
			iRtnFunction = 41100;//Laser 측정 Pass
		}
		else
		{
			iRtnFunction = 31250;/////// 31000;
		}

		break;
#if 0 //카메라 없음
	case 31000:
		if (motor.Lens_Motor_MoveXY(Lens_Pos))
		{
			Task.LensTaskTime = myTimer(true);
			logStr.Format("Lens Align 위치 이동 완료[%d]", iLensStep);
			putListLog(logStr);
			iRtnFunction = 31050;
		}
		else
		{
			logStr.Format("Lens Align 위치 이동 실패[%d]", iLensStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -31000;
		}
		break;

	case 31050:
		//tx,ty도 이동되게 수정 221006
		if (!motor.Lens_Tilt_Motor_Move(Lens_Pos))
		{
			logStr.Format("LensAlign_Pos Tx,Ty이동 실패");
			putListLog(logStr);
			delayMsg(logStr, 3000, M_COLOR_RED);
			iRtnFunction = -31050;
			break;
		}
		else
		{
			logStr.Format("LensAlign_Pos Tx,Ty 위치 이동 완료[%d]", iLensStep);
			putListLog(logStr);
			iRtnFunction = 31060;
		}
		
		break;
	case 31060:
		if (motor.LENS_Z_Motor_Move(Lens_Pos))
		{
			Task.LensTaskTime = myTimer(true);
			logStr.Format("Lens Align Z 위치 이동 완료[%d]", iLensStep);
			putListLog(logStr);
			iRtnFunction = 31080;
		}
		else
		{
			logStr.Format("Lens Align Z 위치 이동 실패[%d]", iLensStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -31060;
		}
		break;

	case 31080:
		if ((myTimer(true) - Task.PCBTaskTime) > iCamDelay && (motor.IsStopAxis(Motor_Lens_X) && motor.IsStopAxis(Motor_Lens_Y)))
		{
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 31100;
		}
		break;

	case 31100: // lens Align
		if (Task.m_iRetry_Opt > iAlignRetry)
		{
			logStr.Format("Lens Align 재검사 %d 회 실패[%d]\n 보정 미적용으로 진행하시겠습니까?", Task.m_iRetry_Opt, iLensStep);
			if (askMsg(logStr) == IDOK)
			{
				Task.d_Align_offset_x[LENS_Align_MARK] = 0;
				Task.d_Align_offset_y[LENS_Align_MARK] = 0;
				Task.d_Align_offset_th[LENS_Align_MARK] = 0;
				iRtnFunction = 31300;
			}
			else
			{
				iRtnFunction = -31100;
				logStr.Format("Lens Align 재검사 %d 회 실패[%d]", Task.m_iRetry_Opt, iLensStep);
				errMsg2(Task.AutoFlag, logStr);
			}
			break;
		}

		offsetX = offsetY = offsetTh = 0.0;
		Sleep(200);
		iRtn = theApp.MainDlg->procCamAlign(CAM2 - 1, LENS_Align_MARK, false, offsetX, offsetY, offsetTh);
		saveInspImage(LENS_IMAGE_SAVE, Task.m_iRetry_Opt);

		Task.m_iRetry_Opt++;
		offsetY = 0;
		if (iRtn == 0)
		{
			Task.d_Align_offset_x[LENS_Align_MARK] -= offsetX;
			Task.d_Align_offset_y[LENS_Align_MARK] += offsetY;
			Task.d_Align_offset_th[LENS_Align_MARK] = 0;//+= offsetTh;	//Lens는 보정량 Theta가 없음

			logStr.Format("Lens Align : %.3lf %.3lf %.3lf", Task.d_Align_offset_x[LENS_Align_MARK], Task.d_Align_offset_y[LENS_Align_MARK], Task.d_Align_offset_th[LENS_Align_MARK]);
			//pcbDlg->m_labelAlignResult.SetText(logStr);
			//pcbDlg->m_labelAlignResult.Invalidate();

			putListLog(logStr);

			int iRtnVal = theApp.MainDlg->AlignLimitCheck(CAM2, offsetX, offsetY, 0);
			if (iRtnVal == 1)
			{
				iRtnFunction = 31200;				// 보정 이동
			}
			else if (iRtnVal == 2)
			{
				logStr.Format("		Lens Align [%d] 완료 [%d]", Task.m_iRetry_Opt, iLensStep);
				putListLog(logStr);
				theApp.MainDlg->InstantMarkDelete(LENS_Align_MARK);			//임시 등록 마크 삭제

				logStr.Format("		Lens Align Complete : %d, %.03f, %.03f, %.03f", Task.m_iLensPickupNoCentering, Task.d_Align_offset_x[LENS_Align_MARK], Task.d_Align_offset_y[LENS_Align_MARK], Task.d_Align_offset_th[LENS_Align_MARK]);
				AlignResultSave(logStr);
				Task.m_iRetry_Opt = 0;
				iRtnFunction = 31250;// 31300;				// 완료
			}
			else
			{
				logStr.Format("Lens Align [%d] 보정 범위 초과[%d]", Task.m_iRetry_Opt, iLensStep);
				errMsg2(Task.AutoFlag, logStr);
				AlignLogSave(logStr);
				theApp.MainDlg->InstantMarkDelete(LENS_Align_MARK);
				iRtnFunction = -31100;				// NG
			}
		}
		else
		{
			logStr.Format("Lens Align [%d] 마크 인식 실패[%d]", Task.m_iRetry_Opt, iLensStep);
			putListLog(logStr);
			iRtnFunction = 31100;					//  재검사 
		}
		break;

	case 31200://!! 보정량 이동.- Retry
		if (motor.Lens_Motor_Align_Move(Task.d_Align_offset_x[LENS_Align_MARK], Task.d_Align_offset_y[LENS_Align_MARK], Task.d_Align_offset_th[LENS_Align_MARK]))
		{
			Task.LensTaskTime = myTimer(true);
			iRtnFunction = 31080;
		}
		else
		{
			sLangChange.LoadStringA(IDS_STRING657);	//Lens Align 보정 위치 이동 실패
			logStr.Format(sLangChange + _T("[%d]"), iLensStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -31200;
		}
		break;

#endif
	case 31250:
		if (motor.LENS_Z_Motor_Move(Wait_Pos))
		{
			Task.LensTaskTime = myTimer(true);
			iRtnFunction = 31300;
		}
		else
		{
			logStr.Format("Lens_Z축 대기위치 이동 실패.[%d]", iLensStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -31250;
		}
		break;
	case 31300://! Lens-Z축 대기 위치 이동
		iLaser_Pos = 0;
		//iRtnFunction = 39000; //렌즈 카메라 있을때
		iRtnFunction = 43000; //렌즈 카메라 없을때
		break;
	case 39000:
		if (!motor.Lens_Tilt_Motor_Move(Laser_Lens_Pos))
		{
			logStr.Format("Laser_Lens_Pos Tx,Ty이동 실패");
			putListLog(logStr);
			delayMsg(logStr, 3000, M_COLOR_RED);
			iRtnFunction = -39000;
			break;
		}
		else
		{
			logStr.Format("Laser_Lens_Pos Tx,Ty 위치 이동 완료[%d]", iLensStep);
			putListLog(logStr);
			iRtnFunction = 40000;
		}
		break;
	case 40000://! Laser-Z축 외부 측정위치 이동
		if (motor.LENS_Z_Motor_Move(Laser_Lens_Pos))
		{
			Task.LensTaskTime = myTimer(true);
			iRtnFunction = 40100;
		}
		else
		{
			logStr.Format("Laser-Z축 변위 측정 외부 위치 이동 실패 [%d]", iLensStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -40000;
		}
		break;

	case 40100:
		iRtnFunction = 40200;
		break;

	case 40200://! Lens Stage 외부 Laser 측정위치 이동 
		if (motor.Lens_Motor_Move_Laser(iLaser_Pos, Task.d_Align_offset_x[LENS_Align_MARK], Task.d_Align_offset_y[LENS_Align_MARK], Task.d_Align_offset_th[LENS_Align_MARK]))
		{
			
			logStr.Format("Laser 변위 측정 외부 위치 이동 완료[%d]", iLensStep);	//Laser 변위 측정 외부 위치 이동 완료[%d]
			putListLog(logStr);
			iRtnFunction = 40210;
		}
		else
		{
			logStr.Format("Laser 변위 측정 외부 위치 이동 실패 [%d]", iLensStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -40200;
		}
		break;

	case 40210:
		iRtnFunction = 40220;
		break;

	case 40220:
		Task.LensTaskTime = myTimer(true);
		iRtnFunction = 40300;
		break;

	case 40300://! 측정 전 Delay
		if ((myTimer(true) - Task.LensTaskTime) > iLaserDelay && (motor.IsStopAxis(Motor_Lens_X) && motor.IsStopAxis(Motor_Lens_Y)))	//최주임님, Delay 확인
		{
			iRtnFunction = 41000;
		}
		break;
		//Laser 실린더 하강 END

	case 41000: //외부 변위 감지 (저장 따로 하고 Align 이동)
		Keyence.func_LT9030_Scan(Task.m_Laser_Point[iLaser_Pos]);
		//Keyence.func_CL3000_Scan(Task.m_Laser_Point[iLaser_Pos]);
		logStr.Format("변위 센서 %lf[%d] - 외부 - %d 위치", Task.m_Laser_Point[iLaser_Pos], iLensStep, iLaser_Pos + 1);
		putListLog(logStr);
		LaserPos[iLaser_Pos].x = motor.GetEncoderPos(Motor_Lens_X) - sysData.dDataset[Motor_Lens_X];
		LaserPos[iLaser_Pos].y = motor.GetEncoderPos(Motor_Lens_Y) - sysData.dDataset[Motor_Lens_Y];
		LaserValue[iLaser_Pos] = Task.m_Laser_Point[iLaser_Pos];
		if (Task.m_Laser_Point[iLaser_Pos] != 0)
		{
			if (iLaser_Pos == 3)
			{
				if (theApp.MainDlg->func_Check_LaserValueErr(LaserValue) == false)
				{
					logStr.Format("Laser 측정값 이상..외부 변위 측정값이 이상..[%d]\n 측정값:%.04lf, %.04lf, %.04lf, %.04lf", iLensStep, LaserValue[0], LaserValue[1], LaserValue[2], LaserValue[3]);
					errMsg2(Task.AutoFlag, logStr);
					iRtnFunction = -41000;
					break;
				}

				if (theApp.MainDlg->_calcLaserTilt(LaserPos, LaserValue, Task.d_Align_offset_xt[LENS_Align_MARK], Task.d_Align_offset_yt[LENS_Align_MARK]))
				{
					Task.m_dataOffset_x[LENS_Align_MARK] = Task.d_Align_offset_xt[LENS_Align_MARK];
					Task.m_dataOffset_y[LENS_Align_MARK] = Task.d_Align_offset_yt[LENS_Align_MARK];


					logStr.Format("보정량 Tx: %.04lf, Ty: %.04lf", Task.d_Align_offset_xt[LENS_Align_MARK], Task.d_Align_offset_yt[LENS_Align_MARK]);
					putListLog(logStr);

					int Rnd = theApp.MainDlg->TiltAlignLimitCheck(Task.m_dataOffset_x[LENS_Align_MARK], Task.m_dataOffset_y[LENS_Align_MARK]);
					//20160117 이형석 수정

					if (Rnd == 2)
					{

						Task.m_timeChecker.Measure_Time(5);	//Laser 변위 측정 완료 시간
						Task.m_dTime_LaserDpm = Task.m_timeChecker.m_adTime[5] - Task.m_timeChecker.m_adTime[4];
						//dispGrid();
						MandoInspLog.dTilteOffset[0] = Task.m_dataOffset_x[LENS_Align_MARK];	//만도 차량용Camera 검사 Log 저장
						MandoInspLog.dTilteOffset[1] = Task.m_dataOffset_y[LENS_Align_MARK];


						//20141217 LHC - DataBase에 0값이 저장되는 경우가 생겨 0값이 들어갈 경우 저장하지않고 알람치도록.
						//김영호 20150602 FraneeGrabber  관련 임시 Pass
						if (Task.m_dataOffset_x[LENS_Align_MARK] == 0 || Task.m_dataOffset_y[LENS_Align_MARK] == 0)
						{
							logStr.Format("Laser 변위 차 값 이상 발생..Xt : %lf, Yt : %lf", Task.m_dataOffset_x[LENS_Align_MARK], Task.m_dataOffset_y[LENS_Align_MARK]);
							errMsg2(Task.AutoFlag, logStr);
							iRtnFunction = -41000;
							break;
						}
						if (!g_ADOData.func_AATaskToRecordLaser(Task.ChipID, Task.m_dataOffset_x[LENS_Align_MARK], Task.m_dataOffset_y[LENS_Align_MARK], Task.m_Laser_Point))
						{
							logStr.Format("DataBase Laser 변위 측정 Data 기록 실패.[%d]\n MS Office를 닫아주세요.", iLensStep);
							errMsg2(Task.AutoFlag, logStr);
							iRtnFunction = -41000;
							break;
						}

						LightControl.ctrlLedVolume(LIGHT_PCB, model.m_iLedValue[LEDDATA_LENS]);		// Align만 조명 ON
						Task.LensTaskTime = myTimer(true);
						iRtnFunction = 41100;
						iLaser_Pos++;

					}
					else if (Rnd == 1)
					{
						iRtnFunction = 41050;
					}
					else
					{
						logStr.Format("Laser Tilt  보정값 Limit를 초과 하였습니다.[%d]", iLensStep);
						errMsg2(Task.AutoFlag, logStr);
						iRtnFunction = -41000;
					}
				}
			}
			else
			{
				iRtnFunction = 40200;
				iLaser_Pos++;
			}
		}
		else
		{
			iRtnFunction = 41000;
		}
		break;

	case 41050: // 이동  변위값이 0으로 만들기 위해 이동
		if (motor.Lens_Move_Tilt(Task.d_Align_offset_xt[LENS_Align_MARK], Task.d_Align_offset_yt[LENS_Align_MARK]))
		{
			iRtnFunction = 40200;
			iLaser_Pos = 0;//4;

		}
		break;

	case 41100:
		iRtnFunction = 41110;
		break;

		//laser실린더 상승
	case 41110:
		iRtnFunction = 41120;
		break;

	case 41120:
		iRtnFunction = 41200;
		break;

	case 41200://! Lens-Z축 대기 위치 이동
		if (motor.LENS_Z_Motor_Move(Wait_Pos))
		{
			Task.LensTaskTime = myTimer(true);
			iRtnFunction = 41850;
		}
		else
		{
			logStr.Format("Lens_Z축 대기위치 이동 실패.[%d]", iLensStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -41200;
		}
		break;

	case 41300:
		if (motor.Lens_Motor_MoveXY(Lens_Pos))
		{
			Task.LensTaskTime = myTimer(true);
			logStr.Format("Lens Align 이동 [%d]", iLensStep);
			putListLog(logStr);
			iRtnFunction = 41400;
		}
		else
		{
			logStr.Format("Lens Align 이동 실패[%d]", iLensStep);
			putListLog(logStr);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -41300;
		}

		break;
	case 41400:

		if (motor.LENS_Z_Motor_Move(Lens_Pos))
		{
			Task.d_Align_offset_x[LENS_Align_MARK] = 0;
			Task.d_Align_offset_y[LENS_Align_MARK] = 0;
			Task.d_Align_offset_th[LENS_Align_MARK] = 0;
			Task.LensTaskTime = myTimer(true);
			logStr.Format("Lens Align 위치 이동 완료[%d]", iLensStep);
			putListLog(logStr);
			iRtnFunction = 41500;
		}
		else
		{
			logStr.Format("Lens Align 위치 이동 실패[%d]", iLensStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -41400;
		}
		break;

	case 41500:
		checkMessage();
		if ((myTimer(true) - Task.LensTaskTime) > iCamDelay && (motor.IsStopAxis(Motor_Lens_X) && motor.IsStopAxis(Motor_Lens_Y)))
		{
			iRtnFunction = 41600;
			Task.m_iRetry_Opt = 0;
		}
		break;

	case 41600://! LENS Align(변위측정 보정후, Shift 계산 용도)
		if (sysData.m_FreeRun == 1)
		{
			for (int i = 0; i < 100; i++)
			{
				Sleep(10);
				checkMessage();
			}

			iRtnFunction = 41700;
			Task.d_Align_offset_x[LENS_Align_MARK] = 0;
			Task.d_Align_offset_y[LENS_Align_MARK] = 0;
			Task.d_Align_offset_th[LENS_Align_MARK] = 0;
			break;
		}
		if (Task.m_iRetry_Opt > iAlignRetry)
		{
			logStr.Format("Lens Align 재검사 %d 회 실패[%d]\n 보정 미적용으로 진행하시겠습니까?", Task.m_iRetry_Opt, iLensStep);
			if (askMsg(logStr) == IDOK)
			{
				Task.d_Align_offset_x[LENS_Align_MARK] = 0;
				Task.d_Align_offset_y[LENS_Align_MARK] = 0;
				Task.d_Align_offset_th[LENS_Align_MARK] = 0;
				iRtnFunction = 41800;
			}
			else
			{
				iRtnFunction = -41600;
				logStr.Format("Lens Align 재검사 %d 회 실패[%d]", Task.m_iRetry_Opt, iLensStep);
				errMsg2(Task.AutoFlag, logStr);
			}

			break;
		}
		offsetX = offsetY = offsetTh = 0.0;
		Sleep(200);
		iRtn = theApp.MainDlg->procCamAlign(CAM2 - 1, LENS_Align_MARK, false, offsetX, offsetY, offsetTh);

		saveInspImage(LENS_IMAGE_SAVE, Task.m_iRetry_Opt);

		Task.m_iRetry_Opt++;

		if (iRtn == 0)
		{
			Task.d_Align_offset_x[LENS_Align_MARK] -= offsetX;
			Task.d_Align_offset_y[LENS_Align_MARK] += offsetY;
			Task.d_Align_offset_th[LENS_Align_MARK] = 0;//+= offsetTh;	//Lens는 보정량 Theta가 없음

			logStr.Format("Lens Align : %.3lf %.3lf %.3lf", Task.d_Align_offset_x[LENS_Align_MARK], Task.d_Align_offset_y[LENS_Align_MARK], Task.d_Align_offset_th[LENS_Align_MARK]);
			//			Sleep(500);
			//pcbDlg->m_labelAlignResult.SetText(logStr);
			//pcbDlg->m_labelAlignResult.Invalidate();

			putListLog(logStr);

			int iRtnVal = theApp.MainDlg->AlignLimitCheck(CAM2, offsetX, offsetY, 0);
			if (iRtnVal == 1)
			{
				iRtnFunction = 41700;				// 보정 이동
			}
			else if (iRtnVal == 2)
			{
				logStr.Format("Lens Align [%d] 완료 [%d]", Task.m_iRetry_Opt, iLensStep);
				putListLog(logStr);

				theApp.MainDlg->InstantMarkDelete(LENS_Align_MARK);			//임시 등록 마크 삭제

				logStr.Format("Lens Align Complete : %d, %.03f, %.03f, %.03f", Task.m_iLensPickupNoCentering, Task.d_Align_offset_x[LENS_Align_MARK], Task.d_Align_offset_y[LENS_Align_MARK], Task.d_Align_offset_th[LENS_Align_MARK]);
				AlignResultSave(logStr);
				Task.m_iRetry_Opt = 0;
				iRtnFunction = 41800;				// 완료
			}
			else
			{
				logStr.Format("Lens Align [%d] 보정 범위 초과 [%d]", Task.m_iRetry_Opt, iLensStep);
				errMsg2(Task.AutoFlag, logStr);
				AlignLogSave(logStr);
				theApp.MainDlg->InstantMarkDelete(LENS_Align_MARK);
				iRtnFunction = -41600;				// NG
			}
		}
		else
		{
			logStr.Format("Lens Align [%d] 마크 인식 실패[%d]", Task.m_iRetry_Opt, iLensStep);
			putListLog(logStr);

			iRtnFunction = 41600;					//  재검사 
		}
		break;

	case 41700://!! 보정량 이동.- Retry
		if (motor.Lens_Motor_Align_Move(Task.d_Align_offset_x[LENS_Align_MARK], Task.d_Align_offset_y[LENS_Align_MARK], Task.d_Align_offset_th[LENS_Align_MARK]))
		{
			Task.LensTaskTime = myTimer(true);
			iRtnFunction = 41500;
		}
		else
		{
			logStr.Format("Lens Align 보정 위치 이동 실패[%d]", iLensStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -41700;
		}
	case 41800: // 값 저장2

				//!!!!! 1차 Align 보정량 편차 저장 공식(PCB<-> Lens Sensor간)
		Task.m_dataOffset_x[1] = Task.d_Align_offset_x[LENS_Align_MARK];
		Task.m_dataOffset_y[1] = Task.d_Align_offset_y[LENS_Align_MARK];
		//		Task.m_dataOffset_th[1] = Task.d_Align_offset_th[LENS_Align_MARK] - Task.d_Align_offset_th[PCB_Chip_MARK];

		//sLangChange.LoadStringA(IDS_STRING962);	//PCB Sensor_Holder간 Align 편차값 : X:%.03f, Y:%.03f, Θ:%.04f [%d]
		//logStr.Format(_T("		") + sLangChange, Task.m_dataOffset_x[1], Task.m_dataOffset_y[1],Task.m_dataOffset_th[1], iLensStep);
		//putListLog(logStr);

		//만도 차량용Camera 검사 Log 저장
		MandoInspLog.dLensOffset[0] = Task.m_dataOffset_x[1];
		MandoInspLog.dLensOffset[1] = Task.m_dataOffset_y[1];
		MandoInspLog.dLensOffset[2] = Task.m_dataOffset_th[1];


		if (Dio.CamLaserSlinderMove(false, true))
		{
			logStr.Format("Laser/Cam 실린더 후진 완료[%d]", iLensStep);
			//putListLog(logStr);
			Task.LensTaskTime = myTimer(true);
			iRtnFunction = 41850;
		}
		else
		{
			logStr.Format("Laser/Cam 실린더 후진 실패[%d]", iLensStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -41800;
		}

		break;
	case 41850:
		if (Dio.CamLaserSlinderCheck(false, false))
		{
			logStr.Format("Laser/Cam 실린더 후진 확인 완료[%d]", iLensStep);
			putListLog(logStr);
			iRtnFunction = 41900;
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > 10000)//IO_DELAY_TIME)
		{
			logStr.Format("Laser/Cam 실린더 후진 시간 초과[%d]", iLensStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -41850;
		}
		break;
	case 41900://! Lens-Z축 대기 위치 이동
		if (motor.LENS_Z_Motor_Move(Wait_Pos))
		{
			
			iRtnFunction = 41950;
		}
		else
		{
			logStr.Format("Lens_Z축 대기위치 이동 실패.[%d]", iLensStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -41900;
		}
		break;
	case 41950:
		iRtnFunction = 42000;


		break;
	case 42000: // 본딩 위치 이동
		if (motor.Lens_Motor_MoveXY(Bonding_Pos, Task.d_Align_offset_x[LENS_Align_MARK], Task.d_Align_offset_y[LENS_Align_MARK]))
		{
			logStr.Format("Lens Bonding_Pos 이동 [%d]", iRtnFunction);
			putListLog(logStr);
			iRtnFunction = 42200;

			Task.LensTaskTime = myTimer(true);
		}
		else
		{
			logStr.Format("Lens Bonding_Pos 이동 실패 [%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -42000;
		}
		break;
	case 42200:
		iRtnFunction = 43000;
		break;

	case 43000:
		Task.interlockPcb = 1;			//end RunProc_LENS_AlignLaserMeasure
		Task.interlockLens = 1;		//end RunProc_LENS_AlignLaserMeasure
		iRtnFunction = 50000;
		break;
	default:
		logStr.Format("Laser 변위 측정 Thread Step 번호 비정상 .[%d]", iLensStep);
		errMsg2(Task.AutoFlag, logStr);
		iRtnFunction = -1;
		break;
}

	return iRtnFunction;
}
int CPcbProcess2::RunProc_LENS_LensLoad(int iLensStep)
{
	int iRtnFunction = iLensStep;
	int iCamDelay = model.strInfo_Cam[1].m_iDelayTime;		//PCB 영상 획득 Delay
	int iAlignRetry = model.strInfo_Cam[1].m_iRetryCnt;
	int iRtn = 0;
	CString logStr = "";
	bool bChk = true;
	double offsetX = 0.0, offsetY = 0.0, offsetTh = 0.0;

	int iLaserDelay = model.strInfo_Cam[0].m_iDelayTime;	//Laser 측정전 Delay

	switch (iLensStep)
	{
	case 30000:
#if (____AA_WAY == PCB_TILT_AA)
		iRtnFunction = 50000;
		break;
#endif
		Task.interlockLens = 0;			//Lens AA 사용
		if (Task.m_bOKLensPass == 1)//! Lens 넘김 미완료 일 경우	 
		{
			logStr.Format("Lens 넘김 완료 상태 [%d]", iRtnFunction);
			putListLog(logStr);
			iRtnFunction = 39500;
			break;
		}
		iRtnFunction = 30500;
		break;
	case 30500:
		if (motor.LENS_Z_Motor_Move(Wait_Pos))
		{
			Task.LensTaskTime = myTimer(true);
			iRtnFunction = 30700;
		}
		else
		{
			logStr.Format("Lens_Z축 대기위치 이동 실패.[%d]", iLensStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -30500;
		}

		break;
	case 30700:

		iRtnFunction = 30800;
		break;
	case 30800:

		iRtnFunction = 31000;
		break;
	case 31000:
		if (motor.Lens_Motor_MoveXY(Wait_Pos))
		{
			iRtnFunction = 31500;		//렌즈쪽 카메라 없음
		}
		else
		{
			logStr.Format("Lens 대기위치 이동 실패[%d]", iLensStep);
			putListLog(logStr);
			iRtnFunction = -31000;
		}
		break;
	case 31500:
		if (motor.Lens_Motor_MoveY(Loading_Pos))
		{
			iRtnFunction = 32000;		//렌즈쪽 카메라 없음
		}
		else
		{
			logStr.Format("Lens LensLoad 이동 실패[%d]", iLensStep);
			putListLog(logStr);
			iRtnFunction = -31500;
		}
		break;
	case 32000:
		if (!motor.Lens_Tilt_Motor_Move(Loading_Pos))
		{
			logStr.Format("Lens %s Tx,Ty이동 실패", MotorPosName[Loading_Pos]);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -32000;
			break;
		}
		if (!motor.Lens_Motor_MoveXY(Loading_Pos))
		{
			logStr.Format("Lens %s X,Y 이동 실패", MotorPosName[Loading_Pos]);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -32000;
			break;
		}

		logStr.Format("Lens 공급 위치 이동 완료[%d]", iLensStep);
		putListLog(logStr);
		iRtnFunction = 32500;
		break;
	case 32500:
		if (!Dio.LensMotorGrip(false, false))
		{
			logStr.Format("Lens Unit Gripper 해제 실패[%d]", iLensStep);
			putListLog(logStr);
			iRtnFunction = -32500;
			break;
		}
		Task.LensTaskTime = myTimer(true);
		iRtnFunction = 33000;
		break;
	case 33000:
		if (Dio.LensMotorGripCheck(false, false))
		{
			iRtnFunction = 33500;
			Task.LensTaskTime = myTimer(true);
		}
		else if ((myTimer(true) - Task.LensTaskTime) > IO_DELAY_TIME)
		{
			iRtnFunction = -32500;
		}
		break;
	case 33500:
		iRtnFunction = 34000;
		break;
	case 34000:
		if (!motor.LENS_Z_Motor_Move(Loading_Pos))
		{
			logStr.Format("Lens Z 위치 이동 실패 [%d]", iLensStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -34000;
			break;
		}
		Sleep(300);
		iRtnFunction = 34500;
		break;
	case 34500:
		Dio.LensMotorGrip(true, false);
		Sleep(500);
		iRtnFunction = 35000;
		break;
	case 35000:
		Dio.LensMotorGrip(false, false);
		Sleep(300);
		iRtnFunction = 35500;
		break;
	case 35500:
		if (Dio.LensMotorGrip(true, false))
		{
			Task.m_bOKLensPass = 1;
			Task.LensTaskTime = myTimer(true);
			iRtnFunction = 36000;
		}
		else
		{
			Task.m_bOKLensPass = -1;
			logStr.Format("Lens 그립 실패 [%d]", iLensStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -35500;
		}
		break;
	case 36000:
		if (Dio.LensMotorGripCheck(true, false))
		{
			logStr.Format("Lens 그립 완료[%d]", iLensStep);
			putListLog(logStr);
			iRtnFunction = 36200;
		}
		else if ((myTimer(true) - Task.LensTaskTime) > IO_DELAY_TIME)
		{
			logStr.Format("Lens Gripper 전진 센서 시간 초과..[%d]", iLensStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -35500;
		}
		break;
	case 36200:

		iRtnFunction = 36300;
		break;
	case 36300:
		
		iRtnFunction = 36400;
		break;
	case 36400:
		if (!motor.LENS_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("Lens Z 대기 위치 이동 실패 [%d]", iLensStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -36400;
			break;
		}
		iRtnFunction = 36600;
		break;
	case 36600:
		iRtnFunction = 36800;
		break;
	case 36800:
		if (!motor.Lens_Motor_MoveX(Wait_Pos))
		{
			logStr.Format("Lens X 대기위치 이동 실패");
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -36800;
			break;
		}
		iRtnFunction = 37000;
		break;
	case 37000:
		iRtnFunction = 37200;
		break;
	case 37200:
		iRtnFunction = 37400;
		break;
	case 37400:
		iRtnFunction = 39500;
		break;
	case 39500:
		Task.interlockLens = 1;		//Lens AA 사용 2호기, Lens Thread , 렌즈 로드 완료 부분
		iRtnFunction = 50000;
		break;
	default:
		logStr.Format("Lens Load Thread Step 번호 비정상 [%d]", iLensStep);
		errMsg2(Task.AutoFlag, logStr);
		iRtnFunction = -1;
		break;
	}

	return iRtnFunction;
}


int	CPcbProcess2::HolderRun_Loading(int iUseStep)			//제품 투입		10000 ~ 19000
{
	int iRtnFunction = iUseStep;
	CString logStr = "";

	switch (iUseStep)
	{
	case 10000:
		iRtnFunction = 10100;
		break;

	case 10100:
		logStr.Format("		Start 버튼을 눌러주세요[%d]", iRtnFunction);
		theApp.MainDlg->putListLog(logStr);
		theApp.MainDlg->m_btnStart.m_iStateBtn = 4;
		theApp.MainDlg->m_btnStart.Invalidate();

		iRtnFunction = 10110;
		break;
	case 10110://! Start P/B Button Push 대기. 
		if (Dio.StartPBOnCheck(true, false))// || Start_Btn_On)	//프로그램에 start 버튼 추가
		{

			
			MbufClear(vision.MilOptImage, 0);

			theApp.MainDlg->m_btnStart.m_iStateBtn = 0;
			theApp.MainDlg->m_btnStart.Invalidate();
			theApp.MainDlg->Start_Btn_On = false;

			if (Task.m_bOKLensPass == 1)   //Lens 넘김 완료상태
			{
				if (!askMsg("렌즈 넘김상태입니다. \n계속 진행하시겠습니까?") == IDOK)
				{
					iRtnFunction = 10000;
					break;
				}
			}
			logStr.Format("START BUTTON PRESS [%d]", iRtnFunction);
			theApp.MainDlg->putListLog(logStr);

			iRtnFunction = 10165;
			break;
		}
		break;
	case 10165://! Start P/B Button Push 대기. 
		Dio.StartPBLampOn(false);
		Dio.PCBvaccumOn(VACCUM_ON, false);      //흡착

		logStr.Format("==== Holder Run start====");
		theApp.MainDlg->putListLog(logStr);


		vision.clearOverlay(CCD);
		vision.drawOverlay(CCD);
		iRtnFunction = 10170;
		break;


	case 10170:
		if ((myTimer(true) - Task.PCBTaskTime) > 300)
		{
			iRtnFunction = 10171;
			break;
		}
		break;
	case 10171:
		if (Dio.PCBvaccumOnCheck(true, false) == false)		//DRY_RUN
		{
			logStr.Format("PCB 흡착 감지 실패 [%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -10171;
			break;
		}
		logStr.Format("PCB 흡착 감지 확인 완료 [%d]", iRtnFunction);
		theApp.MainDlg->putListLog(logStr);
		iRtnFunction = 10172;
		break;
	case 10172://! Start P/B Button Push 대기.

		Task.d_Align_offset_x[LENS_Align_MARK] = 0;
		Task.d_Align_offset_y[LENS_Align_MARK] = 0;
		Task.d_Align_offset_th[LENS_Align_MARK] = 0;

		MandoInspLog.func_InitData();

		Task.func_TactTimeInit();


		theApp.MainDlg->dispGrid();

		Task.m_timeChecker.Measure_Time(1);	//Start 버튼 클릭 시간
		MandoInspLog.bInspRes = true;

		vision.clearOverlay(CCD);

		iRtnFunction = 10180;
	
		break;
	case 10180:
		if (motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("PCB Z Wait 위치 이동 완료 [%d]", iRtnFunction);
			theApp.MainDlg->putListLog(logStr);
			iRtnFunction = 10200;
			break;
		}
		else
		{
			logStr.Format("PCB Z Wait 위치 이동 완료 실패 [%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -10180;
			break;
		}
		break;
	case 10200:
		if (motor.LENS_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("Lens Z Wait 위치 이동 완료[%d]", iRtnFunction);
			putListLog(logStr);
			iRtnFunction = 10202;
			break;
		}
		else
		{
			logStr.Format("Lens Z Wait 위치 이동 실패 [%d]", iRtnFunction);
			putListLog(logStr);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -10200;
			break;
		}
		break;

	case 10202:
		if (motor.Lens_Tilt_Motor_Move(Wait_Pos))
		{
			logStr.Format("LENS부 Tx, Ty축 대기 위치 이동 완료");
			theApp.MainDlg->putListLog(logStr);
			iRtnFunction = 10205;
			break;
		}
		else
		{
			logStr.Format("LENS부 Tx, Ty축 대기 위치 이동 실패");
			theApp.MainDlg->putListLog(logStr);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -10200;
			break;
		}
		break;
	case 10205:
		if (motor.Pcb_Tilt_Motor_Move(Wait_Pos))
		{
			logStr.Format("PCB TX,TY Wait_Pos 이동 완료 [%d]", iUseStep);
			putListLog(logStr);
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 10500;
			break;
		}
		else
		{
			logStr.Format(_T("PCB TX,TY Wait_Pos Move Fail[%d]"), iUseStep);
			putListLog(logStr);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -10205;
			break;
		}
		break;
	case 10500:
		if (sysData.m_iFront == 1)
		{
			logStr.Format("Door Open Mode [%d]", iRtnFunction);
			putListLog(logStr);
			iRtnFunction = 10900;
			break;
		}
		else
		{
			iRtnFunction = 10550;
			break;
		}
		break;

	case 10550:	//! Area 센서 감지 Check 10450
		if (Dio.LightCurtainOnCheck(false, false))
		{
			if (Dio.DoorLift(false, false))
			{
				Sleep(100);
				iRtnFunction = 10600;
				break;
			}
			else
			{
				logStr.Format("Door Close 실패 [%d]", iUseStep);	//Door Close 실패
				errMsg2(Task.AutoFlag, logStr);
				iRtnFunction = -10550;
				break;
			}
		}
		else
		{
			logStr.Format(("LightCurtain 감지[%d]"), iUseStep);
			putListLog(logStr);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -10550;
			break;
		}
		break;

	case 10600:	//Light 커튼 감지 센서 감지 확인 10460
		if (Dio.DoorLiftOnCheck(false, false))
		{
			iRtnFunction = 10900;
			break;
		}

		if (Dio.LightCurtainOnCheck(true, false))//Lift Close도중 감시 센서 감지 될 경우 Open
		{
			if (Dio.DoorLift(true, false))
			{
				iRtnFunction = 10550;
				putListLog(logStr);
				break;
			}
			else
			{
				logStr.Format("Door Close 실패 [%d]", iUseStep);
				putListLog(logStr);
				errMsg2(Task.AutoFlag, logStr);
				iRtnFunction = -10600;
				break;
			}
		}
		break;
	case 10900:
		iRtnFunction = 19000;
		break;
	case 19000:
		iRtnFunction = 20000;
		break;
	default:
		logStr.Format("HolderRun_Loading Thread Step 번호 비정상 [%d]", iUseStep);
		errMsg2(Task.AutoFlag, logStr);
		iRtnFunction = -1;
		break;
	}

	return iRtnFunction;
}

int	CPcbProcess2::HolderRun_Dispensing(int iUseStep)		//도포			20000 ~ 29000
{
	int iRtnFunction = iUseStep;
	CString logStr = "";
	bool bChk = false;
	switch (iUseStep)
	{
	case 20000:

		iRtnFunction = 20200;
		break;
	case 20200:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("PCB_Z축 대기위치 이동 실패[%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = -20200;
			break;
		}

		if ((sysData.m_iDispensePass == 1) || (Task.m_bOkDispense == 1))
		{
			iRtnFunction = 29000;
			break;
		}
		else
		{
			iRtnFunction = 20400;
			break;
		}
		break;
	case 20400:
		if (motor.Pcb_Motor_Move(Dispense_Pos))
		{
			logStr.Format("PCB Dispense 위치 이동 완료[%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = 20600;
		}
		else
		{
			logStr.Format("PCB Dispense 위치 이동 실패[%d]", iUseStep);
			putListLog(logStr);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -20400;
		}
		
		break;
	case 20600:
		if (motor.PCB_Z_Motor_Move(Dispense_Pos))
		{
			iRtnFunction = 20800;
		}
		else
		{
			logStr.Format("PCB Z Dispense 위치 이동 실패 [%d]", iUseStep);
			putListLog(logStr);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -20600;
		}
		
		break;
	case 20800:
		if (sysData.nEpoxyIndex == CRICLE_EPOXY)
		{
			bChk = motor.func_Epoxy_CircleDraw();
		}
		else if (sysData.nEpoxyIndex == RECT_EPOXY)
		{
			bChk = motor.func_Epoxy_Draw();
		}
		else if (sysData.nEpoxyIndex == POLYGON_EPOXY)
		{
			motor.func_Epoxy_Rect_Circle_Draw();
		}
		else if (sysData.nEpoxyIndex == POINT_EPOXY)
		{
			//point 형
			logStr.Format("PCB 설정 미지정 실패 [%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -20800;
			break;
		}

		if (bChk)
		{
			Task.m_bOkDispense = 1;

			logStr.Format("PCB Dispense 완료[%d]", iUseStep);
			putListLog(logStr);
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 21000;
		}
		else
		{
			logStr.Format("PCB Dispense 실패 [%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -20800;
		}
		
		break;
	case 21000:
		if (motor.IsStopAxis(Motor_PCB_X) && motor.IsStopAxis(Motor_PCB_Y))
		{
			iRtnFunction = 29000;
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > 60000)
		{
			logStr.Format(_T("Dispense Fail[%d]"), iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -21000;
		}
		break;

	case 29000:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format(" PCB Z축 대기위치 이동 실패[%d]", iUseStep);
			putListLog(logStr);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -29000;
			break;
		}
		else
		{
			logStr.Format("PCB Z 대기 위치 이동 완료[%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = 30000;
			break;
		}
		break;
	default:
		logStr.Format("HolderRun_Dispensing Thread Step 번호 비정상 [%d]", iUseStep);
		errMsg2(Task.AutoFlag, logStr);
		iRtnFunction = -1;
		break;
	}

	return iRtnFunction;
}
int	CPcbProcess2::HolderRun_LensLoading(int iUseStep)		//렌즈 로드		30000 ~ 39000
{
	int iRtnFunction = iUseStep;
	CString logStr = "";

	switch (iUseStep)
	{
	case 30000:
		iRtnFunction = 30200;
		break;

	case 30200:
		if (motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("PCB Z Wait 위치 이동 완료 [%d]", iRtnFunction);
			theApp.MainDlg->putListLog(logStr);
			iRtnFunction = 30400;
		}
		else
		{
			logStr.Format("PCB Z Wait 위치 이동 완료 실패 [%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -30200;
		}
		break;
	case 30400:
		if (motor.LENS_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("Lens Z Wait 위치 이동 완료[%d]", iRtnFunction);
			putListLog(logStr);
			iRtnFunction = 30600;
		}
		else
		{
			logStr.Format("Lens Z Wait 위치 이동 실패 [%d]", iRtnFunction);
			putListLog(logStr);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -30400;
		}
		break;
	case 30600:

		if (Task.m_bOKLensPass != 1)//! Lens 넘김 미완료 일 경우	 
		{
			//레이저후 틸트 심해서 본딩위치갈때 다시 레이저 틸트된 tx,ty 값으로 이동 

			if (!motor.Pcb_Tilt_Motor_Move(Loading_Pos))
			{
				logStr.Format("PCB %s 이동 실패", MotorPosName[Loading_Pos]);
				putListLog(logStr);
				delayMsg(logStr, 3000, M_COLOR_RED);
				iRtnFunction = -30600;
				break;
			}

			if (!motor.Pcb_Motor_Move(Loading_Pos))
			{
				logStr.Format("PCB %s 이동 실패", MotorPosName[Loading_Pos]);
				putListLog(logStr);
				delayMsg(logStr, 3000, M_COLOR_RED);
				iRtnFunction = -30600;
				break;
			}
			iRtnFunction = 30800;
			break;
		}
		else
		{
			iRtnFunction = 39000;	//렌즈 로드 완료 Jump
		}
		break;
	case 30800:
		if (!Dio.LensMotorGrip(false, false))
		{
			logStr.Format("Lens Unit Gripper 해제 실패[%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = -30800;
			break;
		}
		Task.PCBTaskTime = myTimer(true);
		iRtnFunction = 31000;
		break;

	case 31000:
		if (Dio.LensMotorGripCheck(false, false))
		{
			iRtnFunction = 31200;
			Task.PCBTaskTime = myTimer(true);
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > IO_DELAY_TIME)
		{
			logStr.Format("Lens Unit Gripper 해제 확인 실패[%d]", iUseStep);
			putListLog(logStr);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -31000;
		}
		break;

	case 31200:
		if (!motor.Lens_Tilt_Motor_Move(Loading_Pos))
		{
			logStr.Format("Lens %s Tx,Ty이동 실패", MotorPosName[Loading_Pos]);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -31200;
			break;
		}
		if (!motor.Lens_Motor_MoveXY(Loading_Pos))
		{
			logStr.Format("Lens %s X,Y 이동 실패", MotorPosName[Loading_Pos]);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -31200;
			break;
		}

		logStr.Format("Lens 공급 위치 이동 완료[%d]", iUseStep);
		putListLog(logStr);
		iRtnFunction = 31400;
		break;

	case 31400:
		if (!motor.PCB_Z_Motor_Move(Loading_Pos))
		{
			logStr.Format("PCB loading Z 이동 실패");
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -31400;
			break;
		}
		iRtnFunction = 31600;
		break;

	case 31600:
		if (!motor.LENS_Z_Motor_Move(Loading_Pos))
		{
			logStr.Format("Lens Z 위치 이동 실패 [%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -31600;
			break;
		}
		iRtnFunction = 31800;
		break;
	case 31800:
		iRtnFunction = 32000;
		break;
	case 32000:
		Dio.LensMotorGrip(true, false);
		Sleep(500);
		iRtnFunction = 32200;
		break;
	case 32200:
		Dio.LensMotorGrip(false, false);
		Sleep(300);
		iRtnFunction = 32400;
		break;

	case 32400:
		if (Dio.LensMotorGrip(true, false))
		{
			Task.m_bOKLensPass = 1;
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 32600;
		}
		else
		{
			Task.m_bOKLensPass = -1;
			logStr.Format("Lens 그립 실패 [%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -32400;
		}
		break;
	case 32600:
		if (Dio.LensMotorGripCheck(true, false))
		{
			Sleep(500);
			logStr.Format("Lens 그립 완료[%d]", iUseStep);
			putListLog(logStr);

			iRtnFunction = 32800;
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > IO_DELAY_TIME)
		{
			logStr.Format("Lens Gripper 전진 센서 시간 초과..[%d]", iUseStep);
			putListLog(logStr);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -32400;
		}
		break;
	case 32800:
		iRtnFunction = 39000;
		break;

	case 39000:
		if (!motor.LENS_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("Lens Z 대기 위치 이동 실패 [%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -39000;
			break;
		}

		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("PCB waiting Z 이동 실패");
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -39000;
			break;
		}

		iRtnFunction = 40000;		//next 본딩 + UV
		break;
	default:
		logStr.Format("HolderRun_LensLoading Thread Step 번호 비정상 [%d]", iUseStep);
		errMsg2(Task.AutoFlag, logStr);
		iRtnFunction = -1;
		break;
	}

	return iRtnFunction;
}
int	CPcbProcess2::HolderRun_BondingUv(int iUseStep)			//본딩 Uv		40000 ~ 49000
{
	int iRtnFunction = iUseStep;
	CString logStr = "";

	switch (iUseStep)
	{
	case 40000:

		iRtnFunction = 40200;
		break;
	case 40200:
		if (!motor.LENS_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("Lens Z 대기 위치 이동 실패 [%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -40200;
			break;
		}

		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("PCB waiting Z 이동 실패");
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -40200;
			break;
		}
		iRtnFunction = 40400;
		break;
	case 40400:
		if (motor.Pcb_Motor_Move(Bonding_Pos))
		{
			logStr.Format("PCB Bonding 위치 이동 완료[%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = 40600;
			Task.PCBTaskTime = myTimer(true);
		}
		else
		{
			logStr.Format("PCB Bonding 위치 이동 실패 [%d]", iUseStep);
			putListLog(logStr);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -40400;
		}
		break;
	case 40600:
		if (motor.Pcb_Tilt_Motor_Move(Bonding_Pos))
		{
			logStr.Format("PCB TX,TY Bonding_Pos 이동 완료 [%d]", iUseStep);
			putListLog(logStr);
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 40800;
		}
		else
		{
			logStr.Format(_T("PCB Tilt Bonding Pos Move Fail[%d]"), iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -40600;
			break;
		}
		
		break;
	case 40800:
		if (motor.Lens_Motor_MoveXY(Bonding_Pos))
		{
			logStr.Format("Lens X,Y Bonding 위치 이동 완료[%d]", iRtnFunction);
			putListLog(logStr);


			if (!motor.Lens_Tilt_Motor_Move(Bonding_Pos))
			{
				logStr.Format("Lens %s Tx,Ty이동 실패", MotorPosName[Bonding_Pos]);
				delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
				iRtnFunction = -40800;
				break;
			}
			else
			{
				logStr.Format("Lens TX,TY Bonding_Pos 이동 완료 [%d]", iUseStep);
				putListLog(logStr);
				iRtnFunction = 41000;
				break;
			}
		}
		else
		{
			logStr.Format("Lens Bonding 위치 이동 실패[%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -40800;
			break;
		}
		
		break;
	case 41000:

		iRtnFunction = 41200;
		break;
	case 41200:
		if (motor.LENS_Z_Motor_Move(Bonding_Pos))
		{
			logStr.Format("Lens Z Bonding 위치 이동 완료[%d]", iRtnFunction);
			putListLog(logStr);
			iRtnFunction = 41400;

		}
		else
		{
			logStr.Format("Lens Z Bonding 위치 이동 실패 [%d]", iRtnFunction);
			putListLog(logStr);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -41200;
		}
		
		break;
	case 41400:
		if (!motor.PCB_Z_Motor_Move(Bonding_Pos))
		{
			logStr.Format("PCB Z축 Bonding 위치 이동 실패[%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -41400;
			break;
		}
		else
		{
			logStr.Format("PCB Z축 Bonding 위치 이동 완료[%d]", iRtnFunction);
			putListLog(logStr);
			iRtnFunction = 41600;
		}

		break;
	case 41600:
		//Lens 나 Pcb Z축 Offset 줘야 될 수도 있을 듯
		iRtnFunction = 41800;
		break;
	case 41800:
		iRtnFunction = 42000;
		break;
	case 42000:
		iRtnFunction = 42200;
		break;
	case 42200:
		logStr.Format("===> Holder UV ON");
		putListLog(logStr);

		//Dio.UVTrigger(true, false);
		UVCommand.UV_Shutter_Open();
		iRtnFunction = 42400;
		Task.PCBTaskTime = myTimer(true);
		break;
	case 42400:

		if (myTimer(true) - Task.PCBTaskTime > model.UV_Time)  // Delay 체크
		{
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 42600;
		}

		break;
	case 42600:
		logStr.Format("===> Holder UV OFF [%d]", iRtnFunction);
		putListLog(logStr);

		//Dio.UVTrigger(false, false);
		UVCommand.UV_Shutter_Close();
		iRtnFunction = 42800;
		break;

	case 42800:
		Sleep(600);
		iRtnFunction = 43200;
		break;

	case 43200:
		if (!Dio.LensMotorGrip(false, false))
		{
			logStr.Format("Lens Unit Gripper 해제 실패[%d]", iRtnFunction);
			putListLog(logStr);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -43200;
			break;
		}

		Task.PCBTaskTime = myTimer(true);
		Task.m_bOKLensPass = -1;//메인 넘김 완료 Lamp 취소


		iRtnFunction = 43400;
		break;

	case 43400:
		if (Dio.LensMotorGripCheck(false, false))
		{
			Sleep(300);
			logStr.Format("Lens UnGrip 확인 완료 [%d]", iRtnFunction);
			putListLog(logStr);
			iRtnFunction = 43600;
			break;
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > IO_DELAY_TIME)
		{
			logStr.Format("Lens UnGrip 확인 완료 시간 초과[%d]", iRtnFunction);
			putListLog(logStr);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -43200;
		}
		break;


	case 43600:
		iRtnFunction = 43800;
		break;
	case 43800:
		if (!motor.LENS_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("Lens Z 대기 위치 이동 실패 [%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -43800;
			break;
		}
		else
		{
			logStr.Format("Lens Z 대기 위치 이동 완료 [%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = 44000;
		}
		break;
	case 44000:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("PCB Z 대기 위치 이동 실패[%d]", iUseStep);
			putListLog(logStr);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -44000;
			break;
		}
		else
		{
			logStr.Format("PCB Z 대기 위치 이동 완료 [%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = 44200;
		}
		
		break;
	case 44200:
		iRtnFunction = 44400;
		break;
	case 44400:
		iRtnFunction = 49000;
		break;

	case 49000:
		iRtnFunction = 50000;
		break;
	default:
		logStr.Format("HolderRun_BondingUv Thread Step 번호 비정상 [%d]", iUseStep);
		errMsg2(Task.AutoFlag, logStr);
		iRtnFunction = -1;
		break;
	}

	return iRtnFunction;
}
int	CPcbProcess2::HolderRun_FinalOut(int iUseStep)			//배출			50000 ~ 59000
{
	int iRtnFunction = iUseStep;
	CString logStr = "";

	switch (iUseStep)
	{
	case 50000:

		iRtnFunction = 50200;
		break;
	case 50200:
		if (!motor.LENS_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("Lens부 z축 대기 위치 이동 실패[%d]", iUseStep);
			putListLog(logStr);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -50200;
			break;
		}
		else
		{
			logStr.Format("Lens부 z축 대기 위치 이동 완료[%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = 50400;
		}
		break;
	case 50400:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("Pcb부 z축 대기 위치 이동 실패[%d]", iUseStep);
			putListLog(logStr);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -50400;
			break;
		}
		else
		{
			logStr.Format("Pcb부 z축 대기 위치 이동 완료[%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = 50600;
		}
		break;
	case 50600:
		if (motor.Pcb_Motor_MoveY(Wait_Pos))
		{
			logStr.Format("Pcb y 대기 위치 이동 완료 [%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = 50800;
		}
		else
		{
			logStr.Format("Pcb y 대기 위치 이동 실패 [%d]", iUseStep);
			putListLog(logStr);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -50600;
			break;
		}
		
		break;
	case 50800:
		if (motor.Lens_Motor_MoveY(Wait_Pos))
		{
			logStr.Format("Lens Y 대기위치 이동 명령[%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = 51000;
		}
		else
		{
			logStr.Format("Lens Y 대기위치 이동 실패[%d]", iUseStep);
			putListLog(logStr);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -50800;
			break;
		}
		
		break;
	case 51000:

		iRtnFunction = 51200;
		break;
	case 51200:
		if (motor.Pcb_Motor_Move(Wait_Pos))
		{
			logStr.Format("PCB 대기 위치 이동 완료 [%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = 51400;

		}
		else
		{
			logStr.Format("PCB 대기 위치 이동 실패 [%d]", iUseStep);
			putListLog(logStr);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -51200;
		}
		break;

	case 51400:
		if (!motor.Lens_Motor_MoveXY(Wait_Pos))
		{
			logStr.Format("Lens 모터 대기 위치 이동 실패[%d]", iUseStep);
			putListLog(logStr);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -51400;
			break;
		}
		else
		{
			logStr.Format("Lens 대기 위치 이동 완료 [%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = 51600;
		}
		break;
	case 51600:
		if (motor.Pcb_Tilt_Motor_Move(Wait_Pos))
		{
			logStr.Format("PCB TX,TY 대기 위치 이동 완료 [%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = 51800;
		}
		else
		{
			logStr.Format("PCB TX,TY 대기위치 이동 실패[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -51600;
		}
		break;

	case 51800:
		if (motor.Lens_Tilt_Motor_Move(Wait_Pos))
		{
			logStr.Format("LENS부 Tx, Ty축 대기 위치 이동 완료[%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = 52000;
		}
		else
		{
			logStr.Format("LENS부 Tx, Ty축 대기 위치 이동 실패[%d]", iUseStep);
			putListLog(logStr);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -51800;
		}
		break;
	case 52000:
		iRtnFunction = 59000;
		break;
	case 59000:
		iRtnFunction = 10000;
		break;
	default:
		logStr.Format("HolderRun_FinalOut Thread Step 번호 비정상 [%d]", iUseStep);
		errMsg2(Task.AutoFlag, logStr);
		iRtnFunction = -1;
		break;
	}

	return iRtnFunction;
}