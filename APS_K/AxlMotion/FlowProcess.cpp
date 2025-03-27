#include "stdafx.h"
#include "FlowProcess.h"

#include "../AA Bonder.h"
#include "../AA BonderDlg.h"
#include "../DataHandler.h"
#include "../DioControl.h"
#include "../vision.h"
#include "../MIU/Miu.h"
#include "../ForceAlignDlg.h"

#include "../PcbDlg.h"

extern	CDioControl		Dio;
extern	CMIU			MIU;
extern	MIU_DEVICE		gMIUDevice;
extern	CForceAlignDlg* g_pFoceDlg;

extern	CPcbDlg*		pcbDlg;

extern	CVision			vision;
extern  MandoInspLog	MandoInspLog;

extern	CTask			Task;
extern	CSystemData		sysData;
extern	CModelList		modelList;
extern	CModelData		model;
extern	CWork			work;

extern	bool			bThreadCcmGrab;
extern	bool			bThreadCcmGrabRun;		// CCM 영상 획득 Thread 동작시 True

extern double			g_dFindCenterX[3];
extern double			g_dFindCenterY[3];
extern double			g_dFindAngle[3];


// CFlowProcess
IMPLEMENT_DYNAMIC(CFlowProcess, CWnd)

#define TIME_MOTOR_MOVE			20000	//모터 이동 알람 시간
#define TIME_DIO_SENSOR			5000	//DI/O 센서 확인 시간
#define TIME_DIO_VACCUM			3000	//진공 확인 시간
#define ENCORDER_GAP			0.006	//모터 이동 확인시 Encorder 허용 오차(±)

CFlowProcess::CFlowProcess()
{
	dProcessTime = 0.0;
}

CFlowProcess::~CFlowProcess()
{
}


BEGIN_MESSAGE_MAP(CFlowProcess, CWnd)
END_MESSAGE_MAP()

//
//int CFlowProcess::RunProc_ProductLoading(int iUseStep)
//{//! 작업자 제품 투입 자동 Step( 10000 ~ 11000 )
//	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
//
//	int iRtnFunction = iUseStep;
//	CString logStr = "", sBarCode="";
//	bool bChk = true;
//
//	switch( iUseStep )
//	{
//	case 10000://! Door커튼 Lift Open.
//		if( Dio.DoorLift(true, true) )	iRtnFunction = 10050;
//		else 
//		{
//			logStr.Format("Door Open 실패[%d]", iUseStep);
//			errMsg2(Task.AutoFlag, logStr);
//			iRtnFunction = -10000;
//		}
//		break;
//
//	case 10050://! Lens부 Lift 실린더 Check
//		if( Dio.LensLiftCheck(true))	iRtnFunction = 10080;
//		else
//		{
//			logStr.Format("Door Open Sensor 감지 실패[%d]", iUseStep);
//			errMsg2(Task.AutoFlag, logStr);
//			iRtnFunction = -10000;
//		}
//		break;
//
//	case 10080://! Dark 검사 실린더 하강일 경우 상승
//		if( !Dio.PCBDarkCheck(true, false) )
//		{
//			if( !Dio.PCBDark(true, true) )
//			{
//				logStr.Format("Dark검사 실린더 상승 실패.[%d]", iUseStep);
//				errMsg2(Task.AutoFlag, logStr);
//				iRtnFunction = -10080;
//				break;
//			}
//		}
//		iRtnFunction = 10100;
//		break;
//
//	case 10100://! Chip 정보 Draw
//		pFrame->func_ChipID_Draw();
//		iRtnFunction = 10150;
//		break;
//
//	case 10150://! Start P/B Button Push 대기.
//		if( Dio.StartPBOnCheck(true, false) )	
//		{
//			bool bflag = true;
//
//			bflag = pFrame->EpoxyTimeCheck(pFrame->bEpoxyTimeChk);
//			if(!bflag)
//			{
//				iRtnFunction = -10150;
//				break;
//			}
//
//			Task.func_TactTimeInit();
//			pFrame->dispGrid();
//			Task.m_timeChecker.Measure_Time(1);	//Start 버튼 클릭 시간
//
//			pFrame->func_ChipID_Draw();
//			iRtnFunction = 10200;
//		}
//		break;
//
//	case 10200://! PCB 소켓 닫힘 확인
//		if(Dio.PCBPushSocketCheck(true, false) == false)
//		{
//			logStr.Format("PCB부 커버 소켓 Open 상태 Start 버튼 누름 Error [%d]", iUseStep);
//			errMsg2(Task.AutoFlag, logStr);
//			iRtnFunction = -10200;
//			break;
//		}
//		iRtnFunction = 10300;
//		break;
//
//	case 10300://! Lens Grip 전진
//		Task.PcbOnStage = 100;
//		if( Dio.LensGrip(true,false) )
//		{
//			Task.PCBTaskTime = myTimer(true);
//			iRtnFunction = 10310;
//		}
//		else
//		{
//			logStr.Format("Lens Grip 전진 명령 실패[%d]", iUseStep);
//			errMsg2(Task.AutoFlag, logStr);
//			iRtnFunction = -10300;
//		}		
//		break;
//
//	case 10310://! Lens Grip 전진 확인
//		if(Dio.LensGripCheck(true))		iRtnFunction = 10400;
//		else if((myTimer(true) - Task.PCBTaskTime) > IO_DELAY_TIME)
//		{
//			logStr.Format("Lens Grip 전진 센서 신호 확인 시간 초과[%d]", iUseStep);
//			errMsg2(Task.AutoFlag, logStr);
//			iRtnFunction = -10300;
//		}
//		break;
//
//	case 10400:	//! 바코드 정보 Check
//		MandoInspLog.func_InitData();	//-- Log 초기화
//		sBarCode.Format("%s", Task.ChipID);
//
//		if( sBarCode == "EMPTY" )	//-> 초기에 무조건 EMPTY로 바꿔 놓음.
//		{//바코드정보가 없을 경우 확인 Message
//			logStr.Format("바코드 정보가 없습니다. \n [ %s ]명으로 진행 하시겠습니까?", Task.ChipID);
//			if ( askMsg(logStr) == IDOK)
//			{
//				sBarCode.Format("%s", Task.ChipID);
//			}
//			else
//			{
//				iRtnFunction = -10400;
//				break;
//			}
//		}
//		
//		vision.clearOverlay(CCD);
//		//vision.drawOverlay(CCD);
//		iRtnFunction = 10450;
//		break;
//
//	case 10450:	//! Area 센서 감지 Check
//		if( Dio.LightCurtainOnCheck(false, false) )
//		{
//			if( Dio.DoorLift(false, false) )
//			{
//				Sleep(100);
//				iRtnFunction = 10460;
//			} 
//			else
//			{
//				logStr.Format("Door Close 실패[%d]", iUseStep);
//				errMsg2(Task.AutoFlag, logStr);
//				iRtnFunction = -10450;
//			}
//		}
//		break;
//
//	case 10460:	//Light 커튼 감지 센서 감지 확인
//		if( Dio.DoorLiftOnCheck(false, false) )
//		{//Door Lift가 Close되면 다음 Step
//
//			sysData.Load();
//
//			Task.PcbOnStage = 100;
//			Task.m_b_AA_Retry_Flag = false;
//
//			logStr.Format("%d", Task.m_iPcbPickupNo);
//			pFrame->m_labelPickupNoPcb.SetText(logStr);
//			pFrame->m_labelPickupNoPcb.Invalidate();
//	 
//			MandoInspLog.sBarcodeID.Format("%s", Task.ChipID);	//만도 차량용Camera 검사 Log 저장
//
//			iRtnFunction = 11000;
//		}
//		if( Dio.LightCurtainOnCheck(true, false) )
//		{//Lift Close도중 감시 센서 감지 될 경우 Open
//			if( Dio.DoorLift(true, false) )
//			{
//				iRtnFunction = 10450;
//			}
//			else
//			{
//				logStr.Format("Door Open 실패[%d]", iUseStep);
//				errMsg2(Task.AutoFlag, logStr);
//				iRtnFunction = -10460;
//			}
//		}
//		break;
//
//
//	default:
//		logStr.Format("PCB 제품 투입 Thread Step 번호 비정상 . [%d]", iUseStep);
//		errMsg2(Task.AutoFlag, logStr);
//		iRtnFunction = -1;
//		break;
//	}
//
//	return iRtnFunction;
//}

//int CFlowProcess::RunProc_PCBOutsideAlign(int iUseStep)
//{//! PCB 외부 Align Step(11000 ~ 14999)					//!! MIU_Initialize -> PCB Holder Align 위치
//	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
//
//	int iRtnFunction = iUseStep;
//	int iCamDelay = model.strInfo_Cam[1].m_iDelayTime;		//PCB 영상 획득 Delay
//	int iAlignRetry = model.strInfo_Cam[1].m_iRetryCnt;
//	int iRtn = 0;
//	CString logStr = "";
//	bool bChk = true;
//	double offsetX=0.0, offsetY=0.0, offsetTh=0.0;
//
//	switch( iUseStep )
//	{
//	case 11000://! MIU 영상 Initialize
//		Task.PCBTaskTime = myTimer(true);
//		if (sysData.m_FreeRun == 0)
//		{
//			pFrame->m_csLock_Miu.Lock();
//			MIU.Close();
//	
//			if( !pFrame->MIUCheck_process() || gMIUDevice.CurrentState != 4)
//			{
//				logStr.Format("CCD 모듈 영상 초기화 실패.[%d]\n 제품 안착 상태 및 제품 불량 확인 하세요.", iUseStep);
//				errMsg2(Task.AutoFlag, logStr);
//				iRtnFunction = -11000;
//				break;
//			}
//			pFrame->m_csLock_Miu.Unlock();	
//		}
//
//		iRtnFunction = 12000;
//		break;
//
//	case 12000://! 바코드 DB Data 저장
//		if( !g_ADOData.func_AATaskToRecordID(modelList.curModelName, Task.ChipID) )
//		{
//			logStr.Format("DataBase 생성 실패.[%d]\n MS Office를 닫아주세요.", iUseStep);
//			errMsg2(Task.AutoFlag,logStr);
//			iRtnFunction = -12000;
//			break;
//		}
//		
//		if((sysData.m_iDispensePass == 1) || (Task.m_bOkDispense == 1) )	iRtnFunction = 16350;	//-- 도포 Pass Mode 이거나, 도포 완료 일 경우	//Holder Align -> Clean
//		else																iRtnFunction = 13000;
//		break;
//
//	case 13000: //PCB Holder Align 위치
//		Task.m_timeChecker.Measure_Time(2);	//도포 시작 T/T Check
//		pFrame->SetDigReference(PCB_Holder_MARK);
//		LightControl.ctrlLedVolume(LIGHT_OUTSIDE, model.m_iLedValue[LEDDATA_OUTSIDE]);		// Align만 조명 ON
//
//		Task.m_iRetry_Opt = 0;
//		Dio.BackLightOn(false, false);
//
//		pFrame->m_iCurCamNo = 0;
//		pFrame->setCamDisplay(0, 1);
//
//		if (motor.Pcb_Motor_Move(Holder_Pos))
//		{
//			logStr.Format("PCB Holder Align 이동 [%d]", iUseStep);
//			pFrame->putListLog(logStr);
//			iRtnFunction = 13500;
//		} else {
//			logStr.Format("PCB Align 이동 실패[%d]", iUseStep);
//			pFrame->putListLog(logStr);
//			errMsg2(Task.AutoFlag, logStr);
//			iRtnFunction = -13000;
//		}
//
//		Task.PCBTaskTime = myTimer(true);
//		Task.d_Align_offset_x[PCB_Holder_MARK] = 0;
//		Task.d_Align_offset_y[PCB_Holder_MARK] = 0;
//		Task.d_Align_offset_th[PCB_Holder_MARK] = 0;
//		break;
//
//	case 13500:
//		checkMessage();
//		if((myTimer(true) - Task.PCBTaskTime) > iCamDelay && (motor.IsStopAxis(Motor_PCB_X) && motor.IsStopAxis(Motor_PCB_Y)))
//		{
//			if(gMIUDevice.CurrentState != 4 || bThreadCcmGrab == false ||
//				 !PRIInspection.func_Insp_CurrentMeasure(false) )
//			{
//				logStr.Format("CCD 실시간 영상 획득 실패.[%d]\n 제품 안착 상태 및 제품 불량 확인 하세요.", iUseStep);
//				errMsg2(Task.AutoFlag, logStr);
//				iRtnFunction = -13500;
//				break;
//			}
//
//			iRtnFunction = 14000;
//		}
//		break;
//
//	case 14000:	// 14000 : 영상 획득 및 보정값 계산
//		if(sysData.m_FreeRun == 1)
//		{
//			for(int i=0; i<100; i++)
//			{
//				Sleep(10);
//				checkMessage();
//			}
//
//			iRtnFunction = 16000;
//			Task.d_Align_offset_x[PCB_Holder_MARK] = 0;
//			Task.d_Align_offset_y[PCB_Holder_MARK] = 0;
//			Task.d_Align_offset_th[PCB_Holder_MARK] = 0;
//			break;
//		}
//
//		if (Task.m_iRetry_Opt>iAlignRetry)
//		{
//			pFrame->alignImageBackup(CAM2);
//
//			logStr.Format("PCB Align 재검사 %d 회 실패[%d]", Task.m_iRetry_Opt, iUseStep);
//			errMsg2(Task.AutoFlag,logStr);
//
//			Task.m_iRetry_Opt =0;
//			iRtnFunction = -14000;
//
//			//임시 마크 등록창
//			pFrame->setCamDisplay(0, 1);
//			pFrame->ctrlSubDlg(MAIN_DLG);
//			pFrame->changeMainBtnColor(MAIN_DLG);
//
//			g_pFoceDlg->SetCamNo(CAM2, PCB_Holder_MARK);
//			g_pFoceDlg->SetMarkPosition( (int)g_dFindCenterX[PCB_Holder_MARK], (int)g_dFindCenterY[PCB_Holder_MARK]);
//			g_pFoceDlg->ShowWindow(SW_SHOW);
//			break;
//		}
//
//		offsetX = offsetY = offsetTh = 0.0;	
//		iRtn = pFrame->procCamAlign(CAM2, PCB_Holder_MARK, false, offsetX, offsetY, offsetTh);
//		saveInspImage(PCB_IMAGE_SAVE, Task.m_iRetry_Opt);
//
//		Task.m_iRetry_Opt++;
//
//		if (iRtn == 0)
//		{
//			Task.d_Align_offset_x[PCB_Holder_MARK] -= offsetX;
//			Task.d_Align_offset_y[PCB_Holder_MARK] -= offsetY;
//			Task.d_Align_offset_th[PCB_Holder_MARK] += offsetTh;
//
//			logStr.Format("		PCB Holder Align : %.3lf %.3lf %.3lf", Task.d_Align_offset_x[PCB_Holder_MARK], Task.d_Align_offset_y[PCB_Holder_MARK], Task.d_Align_offset_th[PCB_Holder_MARK]);
//			pcbDlg->m_labelAlignResult.SetText(logStr);
//			pcbDlg->m_labelAlignResult.Invalidate();
//
//			pFrame->putListLog(logStr);
//
//			int iRtnVal = pFrame->AlignLimitCheck(CAM1, offsetX, offsetY, offsetTh); // PCB이재기 움직이는 부분이랑 Limit Check 할때 CAM1임
//
//			if(iRtnVal==1)
//			{
//				iRtnFunction = 14100;				// 보정 이동
//			}
//			else if(iRtnVal==2)
//			{
//				logStr.Format("		PCB Align [%d] 완료 [%d]", Task.m_iRetry_Opt, iUseStep);
//				pFrame->putListLog(logStr);
//
//				pFrame->InstantMarkDelete(PCB_Holder_MARK);			//임시 등록 마크 삭제
//
//				logStr.Format("		PCB Holder Align Complete :  %d, %.03f, %.03f, %.03f", Task.m_iPcbPickupNo, Task.d_Align_offset_x[PCB_Holder_MARK], Task.d_Align_offset_y[PCB_Holder_MARK], Task.d_Align_offset_th[PCB_Holder_MARK]);
//				AlignResultSave(logStr);	
//				Task.m_iRetry_Opt = 0;
//				iRtnFunction = 14200;				// 완료
//			}
//			else
//			{
//				logStr.Format("PCB Align [%d] 보정 범위 초과[%d]", Task.m_iRetry_Opt, iUseStep);
//				errMsg2(Task.AutoFlag,logStr);
//				AlignLogSave(logStr);
//				pFrame->InstantMarkDelete(PCB_Holder_MARK);
//				iRtnFunction = -14000;				// NG
//			}
//		}
//		else
//		{
//			logStr.Format("PCB Align [%d] 마크 인식 실패[%d]", Task.m_iRetry_Opt, iUseStep);
//			pFrame->putListLog(logStr);
//
//			iRtnFunction = 14000;				//  재검사 
//		}
//		break;
//	
//	case 14100://!! 얼라인 이동- Retry
//		if(motor.Pcb_Holder_Align_Move(Holder_Pos, Task.d_Align_offset_x[PCB_Holder_MARK], Task.d_Align_offset_y[PCB_Holder_MARK], Task.d_Align_offset_th[PCB_Holder_MARK]))
//		{
//			Task.PCBTaskTime = myTimer(true);
//			iRtnFunction = 13500;
//		}
//		else
//		{
//			logStr.Format("PCB Align 보정 위치 이동 완료 실패[%d]", iUseStep);
//			errMsg2(Task.AutoFlag,logStr);
//			iRtnFunction = -14100;
//		}	
//		break;
//
//	case 14200:	//TestPattern Check
//		iRtn = PRIInspection.func_Insp_TestPattern(true);
//
//		logStr.Format("[검사] TestPattern 검사 : %d(EA)..[%d]", iRtn, iUseStep);
//		pFrame->putListLog(logStr);
//
//		iRtnFunction = 15000;
//		break;
//
//
//	default:
//		logStr.Format("PCB 제품 투입 Thread Step 번호 비정상 . [%d]", iUseStep);
//		errMsg2(Task.AutoFlag, logStr);
//		iRtnFunction = -1;
//		break;
//	}
//
//	return iRtnFunction;
//}

//
//
//int CFlowProcess::RunProc_EpoxyResing(int iUseStep)
//{//! Epoxy 동작 및 도포 검사 Step(15000 ~
//	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
//
//	int iRtnFunction = iUseStep;
//	int iCamDelay = model.strInfo_Cam[1].m_iDelayTime;		//PCB 영상 획득 Delay
//	int iRtn = 0;
//	CString logStr = "";
//	bool bChk = true;
//	double offsetX=0.0, offsetY=0.0, offsetTh=0.0;
//
//	switch( iUseStep )
//	{
//	case 15000:
//		if( motor.moveEpoxyCleanPos(work.Cleancnt, true) )
//		{
//			logStr.Format("PCB Clean 위치 이동 완료[%d]", iUseStep);
//  			pFrame->putListLog(logStr);
//  			iRtnFunction = 15100;
//			work.Cleancnt++;
//			work.Save();
//		}
//		else
//		{
//			logStr.Format("PCB Clean 위치 이동 동작 실패[%d]", iUseStep);
//			errMsg2(Task.AutoFlag,logStr);
//			iRtnFunction = -15000;
//		}
//		break;
//
//	case 15100: // 디스펜스전 Clean Z축 하강.
//		if(motor.PCB_Z_Motor_Move(Clean_Pos))	iRtnFunction = 15700;
//		else
//		{
//			logStr.Format("PCB Z Clean 위치 이동 완료 실패[%d]", iUseStep);
//			errMsg2(Task.AutoFlag,logStr);
//			iRtnFunction = -15600;
//		}
//		break;
//
//	case 15700: //Dispenser -Z축 상승
//		if(motor.PCB_Z_Motor_Move(Wait_Pos))
//		{
//			if( pFrame->func_MIU_ConnectLiveCheck() == false)		//MIU 영상 Check
//			{
//				iRtnFunction = -15700;
//				break;
//			}
//  			iRtnFunction = 16000;
//		}
//		else
//		{
//			logStr.Format("PCB Z Wait 위치 이동 완료 실패[%d]", iUseStep);
//			errMsg2(Task.AutoFlag,logStr);
//			iRtnFunction = -15700;
//		}
//		break;
//
//	case 16000:  //도포 위치 이동
//		LightControl.ctrlLedVolume(LIGHT_OUTSIDE, 0);		// Align 조명 OFF
//
//		if(motor.Pcb_Motor_Move(Dispense_Pos, Task.d_Align_offset_x[PCB_Holder_MARK], Task.d_Align_offset_y[PCB_Holder_MARK], Task.d_Align_offset_th[PCB_Holder_MARK]))
//		{
//			logStr.Format("PCB Dispense 보정 위치 이동 완료-보정량 X:%.03lf,Y:%.03lf,T:%.03lf", Task.d_Align_offset_x[PCB_Holder_MARK], Task.d_Align_offset_y[PCB_Holder_MARK], Task.d_Align_offset_th[PCB_Holder_MARK]);
//  			pFrame->putListLog(logStr);
//  			iRtnFunction = 16100;
//		}
//		else
//  		{
//  			logStr.Format("PCB Dispense 위치 이동 실패[%d]", iUseStep);
//			errMsg2(Task.AutoFlag,logStr);
// 			iRtnFunction = -16000;
//  		}
//		break;
//
//	case 16100: //Dispenser-z 축 하강
//		if(motor.PCB_Z_Motor_Move(Dispense_Pos))		iRtnFunction = 16200;
//		else
//		{
//			logStr.Format("PCB Z Dispense 위치 이동 실패[%d]", iUseStep);
//			errMsg2(Task.AutoFlag,logStr);
// 			iRtnFunction = -16100;
//		}
//		break;
//
//	case 16200: // 디스펜스 동작
//		if(motor.func_Epoxy_CircleDraw())
//		{
//			Task.m_bOkDispense = 1;
//			logStr.Format("PCB Dispense 완료[%d]", iUseStep);
//  			pFrame->putListLog(logStr);
//  			iRtnFunction = 16300;
//		}
//		else
//		{
//			logStr.Format("PCB Dispense 실패[%d]", iUseStep);
//			errMsg2(Task.AutoFlag,logStr);
// 			iRtnFunction = -16200;
//		}
//		break;
//
//	case 16300:
//		if(motor.IsStopAxis(Motor_PCB_X) && motor.IsStopAxis(Motor_PCB_Y))
//		{
//			if(motor.PCB_Z_Motor_Move(Wait_Pos))
//			{
//  				iRtnFunction = 16400;
//			}
//			else
//			{
//				logStr.Format("PCB Z 대기 위치 이동 실패[%d]", iUseStep);
//  				pFrame->putListLog(logStr);
//  				iRtnFunction = -16300;
//			}
//		}
//		break;
//
//	case 16400://! 도포 검사 사용 여부 판단
//		if( sysData.m_iDispenseInspPass == 0 )	iRtnFunction = 16410;
//		else									iRtnFunction = 17000;
//		break;
//
//	case 16410: // 도포검사 이동
//		// LHC - 도포검사 위치가 있는데 holder Align 위치로 가는 이유가 무엇인가요..? 보정된위치에서 검사를 해야되니까..그런건가요?
//		//if(motor.Pcb_Motor_Move(Insp_Pos,Task.d_Align_offset_x[PCB_Holder_MARK], Task.d_Align_offset_y[PCB_Holder_MARK], Task.d_Align_offset_th[PCB_Holder_MARK]))
//		LightControl.ctrlLedVolume(LIGHT_OUTSIDE, model.m_iLedValue[LEDDATA_EPOXY_INSP]); // LHC - 도포검사때 사용할 조명값 불러오기
//
//		if(motor.Pcb_Motor_Move(Holder_Pos,
//			Task.d_Align_offset_x[PCB_Holder_MARK], Task.d_Align_offset_y[PCB_Holder_MARK], Task.d_Align_offset_th[PCB_Holder_MARK]))
//		{
//			Task.PCBTaskTime = myTimer(true);
//			logStr.Format("PCB 도포검사 위치 이동 완료[%d]", iUseStep);
//  			pFrame->putListLog(logStr);
//  			iRtnFunction = 16450;
//		}
//		else
//		{
//			logStr.Format("PCB 도포검사 위치 이동 실패[%d]", iUseStep);
//			errMsg2(Task.AutoFlag,logStr);
// 			iRtnFunction = -16400;
//		}
//		break;
//
//	case 16450:// 이동후, 일정 시간 지연
//		if( (myTimer(true) - Task.PCBTaskTime) > iCamDelay && (motor.IsStopAxis(Motor_PCB_X) && motor.IsStopAxis(Motor_PCB_Y)) )
//		{
//			iRtnFunction = 16500;
//		}
//		break;
//
//	case 16500: //도포검사                                추가해야함
//		bChk = pFrame->_EpoxyFinddispense(0);
//		if(!bChk)
//		{
//			pFrame->setCamDisplay(0, 1);  //LHC - 도포검사 실패 시 다른화면이 보여지고 있을 수 있기 때문에 도포확인하기위한 화면전환.
//			pFrame->putListLog("Epoxy 도포 검사 실패");
//			CString putLog;
//			putLog.Format("Epoxy Table 좌표 (X:%.03f, Y:%.03f, Θ:%.03f)", motor.GetEncoderPos(Motor_PCB_X), motor.GetEncoderPos(Motor_PCB_Y), motor.GetEncoderPos(Motor_PCB_TH));
//			pFrame->putListLog(putLog);
//
//			sprintf_s(motor.m_szLogMsg, "Epoxy 도포 검사 실패. \n자동 운전 진행 하시겠습니까?");
//
//			Dio.setAlarm(ALARM_ON);
//			if (askMsg(motor.m_szLogMsg))
//			{
//				Task.PCBTaskTime = myTimer(true);
//
//				Dio.setAlarm(ALARM_OFF);
//			}
//			else
//			{
//				Dio.setAlarm(ALARM_OFF);
//
//				logStr.Format("Epoxy 도포 검사 완료 실패[%d]", iUseStep);
//				iRtnFunction = -16500;
//				break;
//			}
//		}
//		else
//		{
//			Task.m_timeChecker.Measure_Time(3);	//도포 완료 시간
//			Task.m_dTime_Epoxy = Task.m_timeChecker.m_adTime[3] - Task.m_timeChecker.m_adTime[2];
//			pFrame->dispGrid();
//
//			logStr.Format("PCB 도포검사 완료[%d]", iUseStep);
//  			pFrame->putListLog(logStr);
//		}
//
//		Task.d_Align_offset_x[LENS_Align_MARK] = 0;
//		Task.d_Align_offset_y[LENS_Align_MARK] = 0;
//		Task.d_Align_offset_th[LENS_Align_MARK] = 0;
//
//		iRtnFunction = 16600;
//		break;
//
//		default:
//		logStr.Format("PCB Dispenser Thread Step 번호 비정상 . [%d]", iUseStep);
//		errMsg2(Task.AutoFlag, logStr);
//		iRtnFunction = -1;
//		break;
//	}
//
//	return iRtnFunction;
//}

//
//int	CFlowProcess::RunProc_LensOutSideAlign(int iUseStep)
//{//! Lens 외부 Align Step	( 16600 ~ 
//	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
//
//	int iRtnFunction = iUseStep;
//	int iRtn = 0;
//	CString logStr = "";
//	bool bChk = true;
//	double offsetX=0.0, offsetY=0.0, offsetTh=0.0;
//
//	switch( iUseStep )
//	{
//	case 16600:
//		if( Task.m_bOKLensPass == 1 )
//		{//LENS 넘김 완료 일 경우
//			iRtnFunction = 16800;	
//			break;
//		}
//
//		Task.m_iRetry_Opt = 0;
//		pFrame->SetDigReference(LENS_Align_MARK);
//		LightControl.ctrlLedVolume(LIGHT_OUTSIDE, model.m_iLedValue[LEDDATA_OUTSIDE]);		// Align만 조명 ON
//
//		if(motor.Pcb_Motor_Move(Lens_Pos))
//		{
//			Task.PCBTaskTime = myTimer(true);
//			logStr.Format("Lens Align 위치 이동 완료[%d]", iUseStep);
//  			pFrame->putListLog(logStr);
//  			iRtnFunction = 16650;
//		}
//		else
//		{
//			logStr.Format("Lens Align 위치 이동 실패[%d]", iUseStep);
//			errMsg2(Task.AutoFlag,logStr);
// 			iRtnFunction = -16600;
//		}
//		break;
//
//	case 16650:
//		checkMessage();
//		if((myTimer(true) - Task.PCBTaskTime) > iCamDelay && (motor.IsStopAxis(Motor_PCB_X) && motor.IsStopAxis(Motor_PCB_Y)))
//		{//!! Lens UnGrip Check
//			if( Dio.LensMotorGripCheck(true, false) )
//			{
//				logStr.Format("Lens Gripper Grip 상태..충돌 위험 발생..\n Lens부 Grip 해제 후 진행하세요.", iStep);
//				iRtnFunction = -16650;
//				break;
//			}
//
//			Task.PCBTaskTime = myTimer(true);
//			iRtnFunction = 16700;
//		}
//		break;
//
//	case 16700: // lens Align
//		if (Task.m_iRetry_Opt>iAlignRetry)
//		{
//			alignImageBackup(CAM2);
//
//			logStr.Format("Lens Align 재검사 %d 회 실패[%d]", Task.m_iRetry_Opt, iStep);
//			errMsg2(Task.AutoFlag,logStr);
//
//			Task.m_iRetry_Opt =0;
//			iRtnFunction = -16700;
//
//			//임시 마크 등록창
//			setCamDisplay(0, 1);
//			ctrlSubDlg(MAIN_DLG);
//			changeMainBtnColor(MAIN_DLG);
//
//			g_pFoceDlg->SetCamNo(CAM2, LENS_Align_MARK);
//			g_pFoceDlg->SetMarkPosition((int)g_dFindCenterX[LENS_Align_MARK], (int)g_dFindCenterY[LENS_Align_MARK]);
//			g_pFoceDlg->ShowWindow(SW_SHOW);
//			break;
//		}
//			
//		offsetX = offsetY = offsetTh = 0.0;
//		LightControl.ctrlLedVolume(UP_LIGHT, model.m_iLedValue[UP_LENS_LIGHT]);		// Align만 조명 ON
//		
//		iRtn = procCamAlign(CAM2, LENS_Align_MARK, false, offsetX, offsetY, offsetTh);
//
//		saveInspImage(LENS_IMAGE_SAVE, Task.m_iRetry_Opt);
//
//		Task.m_iRetry_Opt++;
//
//		if (iRtn == 0)
//		{
//			Task.d_Align_offset_x[LENS_Align_MARK] -= offsetX;
//			Task.d_Align_offset_y[LENS_Align_MARK] -= offsetY;
//			Task.d_Align_offset_th[LENS_Align_MARK] = 0;//+= offsetTh;	//Lens는 보정량 Theta가 없음
//
//			logStr.Format("		Lens Align : %.3lf %.3lf %.3lf", Task.d_Align_offset_x[LENS_Align_MARK], Task.d_Align_offset_y[LENS_Align_MARK], Task.d_Align_offset_th[LENS_Align_MARK]);
//			pcbDlg->m_labelAlignResult.SetText(logStr);
//			pcbDlg->m_labelAlignResult.Invalidate();
//
//			putListLog(logStr);
//
//			int iRtnVal = AlignLimitCheck(CAM1, offsetX, offsetY, 0);
//
//			if(iRtnVal==1)
//			{
//				iRtnFunction = 16750;				// 보정 이동
//			}
//			else if(iRtnVal==2 )
//			{
//				logStr.Format("		Lens Align [%d] 완료 [%d]", Task.m_iRetry_Opt, iStep);
//				putListLog(logStr);
//
//				InstantMarkDelete(LENS_Align_MARK);			//임시 등록 마크 삭제
//
//				logStr.Format("		Lens Align Complete : %d, %.03f, %.03f, %.03f", Task.m_iPcbPickupNo, Task.d_Align_offset_x[LENS_Align_MARK], Task.d_Align_offset_y[LENS_Align_MARK], Task.d_Align_offset_th[LENS_Align_MARK]);
//				AlignResultSave(logStr);	
//				Task.m_iRetry_Opt = 0;
//				iRtnFunction = 16800;				// 완료
//			}
//			else
//			{
//				logStr.Format("Lens Align [%d] 보정 범위 초과[%d]", Task.m_iRetry_Opt, iStep);
//				errMsg2(Task.AutoFlag,logStr);
//				AlignLogSave(logStr);
//				InstantMarkDelete(LENS_Align_MARK);
//				iRtnFunction = -16700;				// NG
//			}
//		}
//		else
//		{
//			logStr.Format("Lens Align [%d] 마크 인식 실패[%d]", Task.m_iRetry_Opt, iStep);
//			putListLog(logStr);
//
//			iRtnFunction = 16700;					//  재검사 
//		}
//		break;
//
//
//
//
//	default:
//		logStr.Format("Lens 외부 Align Thread Step 번호 비정상 . [%d]", iUseStep);
//		errMsg2(Task.AutoFlag, logStr);
//		iRtnFunction = -1;
//		break;
//	}
//
//	return iRtnFunction;
//}