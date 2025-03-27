#include "StdAfx.h"
#include "PcbProcess1.h"

CWinThread* pThread_TaskCCD1 = NULL;
bool bThreadCCDRun1 = false;
typedef struct THREADV
{
	int t_Unit;
}_threadV;
//
UINT Thread_TaskCCD1(LPVOID parm)
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	CString logStr = "";


	bThreadCCDRun1 = true;
	if (!pFrame->MIUCheck_process())// || gMIUDevice.CurrentState != 4)
	{
		logStr.Format("CCD ¸ðµâ ¿µ»ó ÃÊ±âÈ­ ½ÇÆÐ.\n Á¦Ç° ¾ÈÂø »óÅÂ ¹× Á¦Ç° ºÒ·® È®ÀÎ ÇÏ¼¼¿ä.");
		errMsg2(Task.AutoFlag, logStr);
		bThreadCCDRun1 = false;
		return false;
	}
	Sleep(300);
	bThreadCCDRun1 = false;


	return true;
}

void CPcbProcess1::putListLog(CString strLog)
{
	theApp.MainDlg->putListLog(strLog);
}


CPcbProcess1::CPcbProcess1(void)
{


}


CPcbProcess1::~CPcbProcess1(void)
{
}

int CPcbProcess1::Ready_process(int iStep)
{
	CString sLog = "";
	int iRtnFunction = iStep;

	switch (iStep)
	{
	case 10000:
		Task.PCBTaskTime = myTimer(true);
		vision.clearOverlay(CCD);

		sLog.Format("		Ready Step [%d]", iRtnFunction);
		putListLog(sLog);



		if (LGIT_MODEL_INDEX == M1_HEATING_GEN2)
		{
			Dio.LensTailGrip(false, false);
		}
		iRtnFunction = 10150;
		break;


	case  10150:
		if (Dio.LensMotorGripCheck(true, false))
		{
			if (Task.m_bOKLensPass == 1)   //Lens ³Ñ±è ¿Ï·á»óÅÂ
			{
				iRtnFunction = 10160;
				sLog.Format("		Ready Step [%d]", iRtnFunction);
				putListLog(sLog);
			}
			else
			{
				sLog.Format("[¿îÀü ÁØºñ] Lens Grip ÀüÁø »óÅÂ ÀÔ´Ï´Ù[%d]\n·»Áî³Ñ±è»óÅÂ È®ÀÎ¹Ù¶ø´Ï´Ù", iStep);
				errMsg2(Task.AutoFlag, sLog);
				iRtnFunction = -10150;
				break;
			}
		}
		else
		{
			if (!Dio.LensMotorGripCheck(false, false))
			{
				sLog.Format("[¿îÀü ÁØºñ]Lens Grip ÀüÁø È®ÀÎ ½ÇÆÐ [%d]", iStep);
				errMsg2(Task.AutoFlag, sLog);
				iRtnFunction = -10150;
			}
			else
			{
				if (Task.m_bOKLensPass == 1)   //Lens ³Ñ±è ¿Ï·á»óÅÂ
				{
					sLog.Format("[¿îÀü ÁØºñ]Lens Grip ÈÄÁø »óÅÂ [%d]]\n·»Áî³Ñ±è»óÅÂ È®ÀÎ¹Ù¶ø´Ï´Ù", iStep);
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

		//Laser ½Ç¸°´õ ÃÊ±âÈ­
	case 10160:
		if (Dio.LaserCylinderUPDOWN(true, false))
		{
			sLog.Format("LASER ½Ç¸°´õ »ó½Â ¿Ï·á[%d]", iRtnFunction);
			theApp.MainDlg->putListLog(sLog);
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 10170;
		}
		else
		{
			sLog.Format("LASER ½Ç¸°´õ »ó½Â ½ÇÆÐ [%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -10160;
		}
		break;

	case 10170:
		if (Dio.LaserCylinderCheck(true, false))
		{
			sLog.Format("LASER ½Ç¸°´õ »ó½Â È®ÀÎ ¿Ï·á[%d]", iRtnFunction);
			theApp.MainDlg->putListLog(sLog);
			iRtnFunction = 10200;

			Sleep(300);
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > IO_DELAY_TIME)
		{
			sLog.Format("LASER ½Ç¸°´õ »ó½Â ½Ã°£ ÃÊ°ú..[%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -10170;
		}
		break;
		//Laser ½Ç¸°´õ ÃÊ±âÈ­ END

	case 10200:
		if (motor.PCB_Z_Motor_Move(Wait_Pos))		//PCB ZÃà ´ë±â À§Ä¡ ÀÌµ¿
		{
			iRtnFunction = 10300;
			sLog.Format("		Ready Step [%d]", iRtnFunction);
			putListLog(sLog);
		}
		else
		{
			sLangChange.LoadStringA(IDS_STRING305);
			sLog.Format(sLangChange, iStep);	//"[¿îÀü ÁØºñ] PCB ZÃà ´ë±âÀ§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]"
			putListLog(sLog);
			iRtnFunction = -10200;
		}

		break;

	case 10300:
		if (motor.LENS_Z_Motor_Move(Wait_Pos))		//Lens ZÃà ´ë±â À§Ä¡
		{
			iRtnFunction = 10400;
			sLog.Format("		Ready Step [%d]", iRtnFunction);
			putListLog(sLog);
		}
		else
		{
			sLangChange.LoadStringA(IDS_STRING303);
			sLog.Format(sLangChange, iStep);	//"[¿îÀü ÁØºñ] Lens ZÃà ´ë±âÀ§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]"
			putListLog(sLog);
			iRtnFunction = -10300;
		}
		break;
	case 10400:

		iRtnFunction = 10600;
		sLog.Format("		Ready Step [%d]", iRtnFunction);
		putListLog(sLog);
		break;

	case 10600:
		if (motor.Pcb_Motor_Move(Wait_Pos))			//PCBºÎ ¸ðÅÍ ´ë±âÀ§Ä¡ ÀÌµ¿
		{
			iRtnFunction = 10700;
			sLog.Format("		Ready Step [%d]", iRtnFunction);
			putListLog(sLog);
		}
		else
		{
			sLangChange.LoadStringA(IDS_STRING306);
			sLog.Format(sLangChange, iStep);	//"[¿îÀü ÁØºñ] PCB ´ë±âÀ§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]"
			putListLog(sLog);
			iRtnFunction = -10600;
		}
		break;
	case 10700:
		if (motor.Lens_Motor_MoveXY(0, Wait_Pos))			//LensºÎ ¸ðÅÍ ´ë±â À§Ä¡ ÀÌµ¿(Lens X/Y/ZÃà)
		{
			iRtnFunction = 10750;
			sLog.Format("		Ready Step [%d]", iRtnFunction);
			putListLog(sLog);
		}
		else
		{
			sLangChange.LoadStringA(IDS_STRING304);
			sLog.Format(sLangChange, iStep);	//"[¿îÀü ÁØºñ] Lens ´ë±âÀ§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]"
			putListLog(sLog);
			iRtnFunction = -10700;
		}
		break;
	case 10750:
		if (motor.Pcb_Tilt_Motor_Move(Wait_Pos))
		{
			iRtnFunction = 10800;
			sLog.Format("		Ready Step [%d]", iRtnFunction);
			putListLog(sLog);
		}
		else
		{
			sLangChange.LoadStringA(IDS_STRING1017);	//PCBºÎ Tx, TyÃà ´ë±â À§Ä¡ ÀÌµ¿ ½ÇÆÐ
			sLog.Format(sLangChange);
			putListLog(sLog);
			iRtnFunction = -10750;
		}
		break;
	case 10800:
		if (motor.Lens_Tilt_Motor_Move(Wait_Pos))
		{
			iRtnFunction = 10900;
			sLog.Format("		Ready Step [%d]", iRtnFunction);
			putListLog(sLog);
		}
		else
		{
			sLangChange.LoadStringA(IDS_STRING745);	//LENSºÎ Tx, TyÃà ´ë±â À§Ä¡ ÀÌµ¿ ½ÇÆÐ
			sLog.Format(sLangChange);
			putListLog(sLog);
			iRtnFunction = -10800;
		}
		break;

	case  10900:
		///////////////////////
		//if( !Dio.LensGrip(true, true) )
		//{		//-- Lens °¨Áö »óÅÂ¿¡¼­ Grip ÀüÁø ¾ÈµÉ °æ¿ì NG
		//	sLangChange.LoadStringA(IDS_STRING300);
		//	sLog.Format(sLangChange, iStep);	//"[¿îÀü ÁØºñ] Lens Grip ÀüÁø ½ÇÆÐ [%d]"
		//	putListLog(sLog);
		//	iRtnFunction = -10900;
		//	break;
		//}			
		//else if( Dio.LensGripCheck(false, false) )			//Lens °¨Áö°¡ ¾ÈµÇ¾úÀ» °æ¿ì  
		//{//-- Lens Grip ÈÄÁø µ¿ÀÛ
		//if(! Dio.HolderGrip(false,false) )    //-- Lens °¨Áö ¾ÈµÇ°í/ Grip ÈÄÁø ¾ÈµÉ °æ¿ì NG
		//{  
		//	sLangChange.LoadStringA(IDS_STRING301);
		//	sLog.Format(sLangChange, iStep);	//"[¿îÀü ÁØºñ] Lens Grip ÈÄÁø ½ÇÆÐ [%d]"
		//	putListLog(sLog);
		//	iRtnFunction = -10900;
		//	break;
		//}
		iRtnFunction = 10950;
		sLog.Format("		Ready Step [%d]", iRtnFunction);
		putListLog(sLog);
		break;
	case 10950:
		iRtnFunction = 10970;
		sLog.Format("		Ready Step [%d]", iRtnFunction);
		putListLog(sLog);
		break;
	case 10970:
		if (!MIU.Stop())					// 95 ~ 100 msec
		{
			sLog.Format(_T("CCD CLOSE FAIL [%d]"), iStep);
			putListLog(sLog);
			iRtnFunction = -10970;
			break;
		}
		iRtnFunction = 15000;	//While¹® Á¾·á
		sLog.Format("		Ready Step [%d]", iRtnFunction);
		putListLog(sLog);
		break;
	case 15000:
		UVCommand.UV_Shutter_PowerSet(model.UV_Power);// 95);//
		sLog.Format("	#1 UV POWER SET: %d", model.UV_Power);
		putListLog(sLog);
		Sleep(500);
		UVCommand2.UV_Shutter_PowerSet(model.UV_Power);// 95);//
		sLog.Format("	#2 UV POWER SET: %d", model.UV_Power);
		putListLog(sLog);
		iRtnFunction = 19000;
		break;
	case 19000:
		Task.AutoReday = 1;
		//		AutoRunView(3);
		iRtnFunction = 19900;
		sLog.Format("		Ready Step [%d]", iRtnFunction);
		putListLog(sLog);
		break;
	}
	return iRtnFunction;
}
int CPcbProcess1::RunProc_ProductLoading(int iUseStep)
{//! ÀÛ¾÷ÀÚ Á¦Ç° ÅõÀÔ ÀÚµ¿ Step		(10000 ~ 10999)
	int iRtnFunction = iUseStep;
	CString logStr = "", sBarCode = "";
	bool bChk = true;

	switch (iUseStep)
	{
	case 10000://! DoorÄ¿Æ° Lift Open.
		Task.interlockLens  = 0;
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
		//LightControl.ctrlLedVolume(LIGHT_OC_6500K, 0);		// Align¸¸ Á¶¸í ON
		Dio.LaserCylinderUPDOWN(true, false);

		logStr.Format("LASER ½Ç¸°´õ »ó½Â ¿Ï·á[%d]", iRtnFunction);
		theApp.MainDlg->putListLog(logStr);
		Task.PCBTaskTime = myTimer(true);

		iRtnFunction = 10060;
		break;

	case 10060:
		if (Dio.LaserCylinderCheck(true, false))
		{
			logStr.Format("LASER ½Ç¸°´õ »ó½Â È®ÀÎ ¿Ï·á[%d]", iRtnFunction);
			theApp.MainDlg->putListLog(logStr);
			iRtnFunction = 10100;

			Sleep(300);
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > IO_DELAY_TIME)
		{
			logStr.Format("LASER ½Ç¸°´õ »ó½Â ½Ã°£ ÃÊ°ú..[%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -10060;
		}
		break;

	case 10100://! Chip Á¤º¸ Draw
		theApp.MainDlg->func_ChipID_Draw();

		iRtnFunction = 10110;

		logStr.Format("		Start ¹öÆ°À» ´­·¯ÁÖ¼¼¿ä[%d]", iRtnFunction);
		putListLog(logStr);
		theApp.MainDlg->m_btnStart.m_iStateBtn = 4;
		theApp.MainDlg->m_btnStart.Invalidate();
		break;

	case 10110://! Start P/B Button Push ´ë±â. 

		if (Dio.StartPBOnCheck(true, false))// || Start_Btn_On)	//ÇÁ·Î±×·¥¿¡ start ¹öÆ° Ãß°¡
		{
			iRtnFunction = 10165;
			MbufClear(vision.MilOptImage, 0);
			theApp.MainDlg->m_btnStart.m_iStateBtn = 0;
			theApp.MainDlg->m_btnStart.Invalidate();
			theApp.MainDlg->Start_Btn_On = false;
			if (Task.m_bOKLensPass == 1)   //Lens ³Ñ±è ¿Ï·á»óÅÂ
			{
				if (!askMsg("·»Áî ³Ñ±è»óÅÂÀÔ´Ï´Ù. \n°è¼Ó ÁøÇàÇÏ½Ã°Ú½À´Ï±î?") == IDOK)
				{
					iRtnFunction = 10000;
					logStr.Format("		loading Step [%d]", iRtnFunction);
					putListLog(logStr);
					break;
				}
			}
			logStr.Format("		loading Step [%d]", iRtnFunction);
			putListLog(logStr);
		}
		break;
	case 10165://! Start P/B Button Push ´ë±â. 
			   //Dio.StartPBLampOn(false);
		sBarCode.Format("%s", Task.ChipID);
		if (sysData.m_iProductComp == 1)
		{
			logStr.Format("====%s ¿ÏÁ¦Ç° °Ë»ç start====", Task.ChipID);
		}
		else
		{
			logStr.Format("====%s AA start====", Task.ChipID);
		}
		vision.clearOverlay(CCD);
		vision.drawOverlay(CCD);
		putListLog("	");
		putListLog(logStr);
		putListLog("	");
		iRtnFunction = 10170;
		logStr.Format("		loading Step [%d]", iRtnFunction);
		putListLog(logStr);
		break;
	case 10170://! Start P/B Button Push ´ë±â.
	{
		bool bflag = true;

		Task.d_Align_offset_x[LENS_Align_MARK] = 0;
		Task.d_Align_offset_y[LENS_Align_MARK] = 0;
		Task.d_Align_offset_th[LENS_Align_MARK] = 0;

		/*bflag = EpoxyTimeCheck(bEpoxyTimeChk);
		if(!bflag)
		{
		iRtnFunction = -10170;
		break;
		}*/
		MandoInspLog.func_InitData();
		Task.func_TactTimeInit();
		theApp.MainDlg->dispGrid();
		Task.m_timeChecker.Measure_Time(1);	//Start ¹öÆ° Å¬¸¯ ½Ã°£
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
		logStr.Format("		loading Step [%d]", iRtnFunction);
		putListLog(logStr);
	}
	break;
	case 10180:
		if (motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("PCB Z Wait À§Ä¡ ÀÌµ¿ ¿Ï·á [%d]", iRtnFunction);
			putListLog(logStr);
			iRtnFunction = 10200;
			logStr.Format("		loading Step [%d]", iRtnFunction);
			putListLog(logStr);
		}
		else
		{
			logStr.Format("PCB Z Wait À§Ä¡ ÀÌµ¿ ¿Ï·á ½ÇÆÐ [%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -10180;
		}
		break;
	case 10200:
		if (motor.Lens_Tilt_Motor_Move(Wait_Pos))
		{
			iRtnFunction = 10202;
			logStr.Format("		Ready Step [%d]", iRtnFunction);
			putListLog(logStr);
		}
		else
		{
			sLangChange.LoadStringA(IDS_STRING745);	//LENSºÎ Tx, TyÃà ´ë±â À§Ä¡ ÀÌµ¿ ½ÇÆÐ
			logStr.Format(sLangChange);
			putListLog(logStr);
			iRtnFunction = -10200;
		}
		break;

	case 10202:
		if (Dio.LaserCylinderCheck(true, false) == false)
		{
			logStr.Format("LASER ½Ç¸°´õ »ó½Â È®ÀÎ ½ÇÆÐ[%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			theApp.MainDlg->putListLog(logStr);
			iRtnFunction = -10202;
			break;
		}
		iRtnFunction = 10205;
		logStr.Format("		loading Step [%d]", iRtnFunction);
		putListLog(logStr);
		break;

	case 10205:
		if (sysData.m_iProductComp == 1)
		{
			iRtnFunction = 10250;
			logStr.Format("		loading Step [%d]", iRtnFunction);
			putListLog(logStr);
		}
		else
		{
			iRtnFunction = 10210;
			logStr.Format("		loading Step [%d]", iRtnFunction);
			putListLog(logStr);
		}
		break;

	case 10210:
		if (Task.m_bOKLensPass == 1)   //Lens ³Ñ±è ¿Ï·á»óÅÂ
		{
			iRtnFunction = 10250;
			break;
		}

		iRtnFunction = 10250;
		logStr.Format("		loading Step [%d]", iRtnFunction);
		putListLog(logStr);
		break;

	case 10250:
		iRtnFunction = 10400;
		logStr.Format("		loading Step [%d]", iRtnFunction);
		putListLog(logStr);
		break;
	case 10400:	//! ¹ÙÄÚµå Á¤º¸ Check

				////////////////////////////////
		MandoInspLog.func_InitData();	//-- Log ÃÊ±âÈ­
		sBarCode.Format("%s", Task.ChipID);

		if (sBarCode == "EMPTY")//¹ÙÄÚµåÁ¤º¸°¡ ¾øÀ» °æ¿ì È®ÀÎ Message
		{
			logStr.Format("¹ÙÄÚµå Á¤º¸°¡ ¾ø½À´Ï´Ù. \n [ %s ]¸íÀ¸·Î ÁøÇà ÇÏ½Ã°Ú½À´Ï±î?", Task.ChipID);
			if (askMsg(logStr) == IDOK)
			{
				sBarCode.Format("%s", Task.ChipID);
			}
			else
			{
				iRtnFunction = 10100;
				logStr.Format("		loading Step [%d]", iRtnFunction);
				putListLog(logStr);
				break;
			}
		}
		else
		{
			if (!g_ADOData.func_AATaskToRecordID(modelList.curModelName, Task.ChipID))
			{
				logStr.Format("		loading Step [%d]", iRtnFunction);
				putListLog(logStr);
#if (____AA_WAY == PCB_TILT_AA)
				/*if(sysData.m_iProductComp==1)
				{
				logStr.Format("ÀÏÄ¡ÇÏ´Â ¾ÆÀÌµð°¡ ¾ø½À´Ï´Ù.[%d]", iUseStep);
				}else
				{
				logStr.Format("DataBase »ý¼º ½ÇÆÐ.[%d]\n MS Office¸¦ ´Ý¾ÆÁÖ¼¼¿ä.", iUseStep);
				}
				errMsg2(Task.AutoFlag,logStr);
				iRtnFunction = -10400;
				break;*/
#endif		

			}
		}


		iRtnFunction = 10440;

		break;
	case 10440:
		if (sysData.m_FreeRun == 0 && sysData.m_iProductComp != 1)
		{
			pThread_TaskCCD1 = ::AfxBeginThread(Thread_TaskCCD1, this);

		}
		iRtnFunction = 10500;
		logStr.Format("		loading Step [%d]", iRtnFunction);
		putListLog(logStr);
		break;
	case 10500:
		iRtnFunction = 10900;
		break;

		break;
	//case 10550:
	//	//±×¸³È®ÀÎ
	//	if (Dio.PcbGripCheck(true, false) == true)
	//	{
	//		logStr.Format(_T("PCB GRIP È®ÀÎ ¿Ï·á [%d]"), iRtnFunction);
	//		iRtnFunction = 10600;
	//	}
	//	else if ((myTimer(true) - Task.PCBTaskTime) > IO_DELAY_TIME)
	//	{
	//		logStr.Format(_T("PCB GRIP ½ÇÆÐ [%d]"), iRtnFunction);
	//		iRtnFunction = -10550;
	//		errMsg2(Task.AutoFlag, logStr);
	//	}
	//	break;
	//case 10600:
	//	//ÅÏ
	//	Sleep(1000);
	//	if (Dio.PcbTurn(false, false) == true)
	//	{
	//		logStr.Format(_T("PCB RETURN ¿Ï·á [%d]"), iRtnFunction);
	//		iRtnFunction = 10650;
	//	}
	//	else
	//	{
	//		logStr.Format(_T("PCB RETURN ½ÇÆÐ [%d]"), iRtnFunction);
	//		iRtnFunction = -10600;
	//		errMsg2(Task.AutoFlag, logStr);
	//	}
	//	putListLog(logStr);
	//	Task.PCBTaskTime = myTimer(true);

	//	break;
	//case 10650:
	//	//ÅÏÈ®ÀÎ
	//	if (Dio.PcbTurnCheck(false, false) == true)
	//	{
	//		logStr.Format(_T("PCB RETURN È®ÀÎ ¿Ï·á [%d]"), iRtnFunction);
	//		iRtnFunction = 10700;
	//	}
	//	else if ((myTimer(true) - Task.PCBTaskTime) > IO_DELAY_TIME)
	//	{
	//		logStr.Format(_T("PCB RETURN È®ÀÎ ½ÇÆÐ [%d]"), iRtnFunction);
	//		iRtnFunction = -10650;
	//		errMsg2(Task.AutoFlag, logStr);
	//	}

	//	break;
	//case 10700:
	//	//PCB ·Îµù ÈÄ È®ÀÎ ´­·¯ÁÖ¼¼¿ä
	//	if (askMsg("PCB ·Îµù ÈÄ È®ÀÎ ´­·¯ÁÖ¼¼¿ä") == IDOK)
	//	{
	//		iRtnFunction = 10900;
	//	}

	//	break;
	case 10900:
		Task.PcbOnStage = 100;
		Task.m_b_AA_Retry_Flag = false;

		logStr.Format("%d", Task.m_iPcbPickupNo);
		theApp.MainDlg->m_labelPickupNoPcb.SetText(logStr);
		theApp.MainDlg->m_labelPickupNoPcb.Invalidate();

		MandoInspLog.sBarcodeID.Format("%s", Task.ChipID);	//¸¸µµ Â÷·®¿ëCamera °Ë»ç Log ÀúÀå
		iLaser_Pos = 0;


		if (sysData.m_iIrChartUse == 1)
		{
			IrvAlignLed.Irv_Light_SetValue(model.m_iLedValue[LEDDATA_TOP1_CHART], IR_CHART);
		}
		else
		{
			LightControl.ctrlLedVolume(LIGHT_TOP_CHART1, model.m_iLedValue[LEDDATA_TOP1_CHART]);
			LightControl.ctrlLedVolume(LIGHT_TOP_CHART2, model.m_iLedValue[LEDDATA_TOP2_CHART]);
			LightControl.ctrlLedVolume(LIGHT_TOP_CHART3, model.m_iLedValue[LEDDATA_TOP3_CHART]);
			LightControl.ctrlLedVolume(LIGHT_TOP_CHART4, model.m_iLedValue[LEDDATA_TOP4_CHART]);
			LightControl.ctrlLedVolume(LIGHT_LEFT_CHART, model.m_iLedValue[LEDDATA_CHART_L]);
			LightControl.ctrlLedVolume(LIGHT_RIGHT_CHART, model.m_iLedValue[LEDDATA_CHART_R]);
		}




#if (____AA_WAY == PCB_TILT_AA)
		if (Task.m_bOKLensPass == 1)   //Lens ³Ñ±è ¿Ï·á»óÅÂ
		{
			logStr.Format("		Lens ±×¸³ ÁøÇà [%d]", iRtnFunction);
			putListLog(logStr);
			iRtnFunction = 15500;// 10250;
			break;
		}
#endif
		iRtnFunction = 11000;
		logStr.Format("		loading Step [%d]", iRtnFunction);
		putListLog(logStr);
		break;

	default:
		sLangChange.LoadStringA(IDS_STRING1007);	//PCB Á¦Ç° ÅõÀÔ Thread Step ¹øÈ£ ºñÁ¤»ó . 
		logStr.Format("PCB Á¦Ç° ÅõÀÔ Thread Step ¹øÈ£ ºñÁ¤»ó [%d]", iUseStep);
		errMsg2(Task.AutoFlag, logStr);
		iRtnFunction = -1;
		break;
	}

	return iRtnFunction;
}

int CPcbProcess1::RunProc_PCBOutsideAlign(int iUseStep)
{
	//! PCB ¿ÜºÎ Align Step(11000 ~ 14999)					//!! MIU_Initialize -> PCB Holder Align À§Ä¡
	int iRtnFunction = iUseStep;
	int iCamDelay = model.strInfo_Cam[1].m_iDelayTime;		//PCB ¿µ»ó È¹µæ Delay
	int iAlignRetry = model.strInfo_Cam[1].m_iRetryCnt;
	int iRtn = 0;
	CString logStr = "";
	bool bChk = true;
	double offsetX = 0.0, offsetY = 0.0, offsetTh = 0.0;

	//ctrlSubDlg(MAIN_DLG);		//20161212  ccd start ¼öÁ¤
	theApp.MainDlg->m_iCurCamNo = 0;
	theApp.MainDlg->setCamDisplay(1, 0);
	theApp.MainDlg->changeMainBtnColor(MAIN_DLG);

	switch (iUseStep)
	{
	case 11000:
		/////////////////////////
		Task.PCBTaskTime = myTimer(true);
		iRtnFunction = 11500;
		break;

	case 11500:
		iRtnFunction = 12000;
		break;
	case 12000://! ¹ÙÄÚµå DB Data ÀúÀå
			   /*if( !g_ADOData.func_AATaskToRecordID(modelList.curModelName, Task.ChipID) )
			   {
			   logStr.Format("DataBase »ý¼º ½ÇÆÐ.[%d]\n MS Office¸¦ ´Ý¾ÆÁÖ¼¼¿ä.", iUseStep);
			   errMsg2(Task.AutoFlag,logStr);
			   iRtnFunction = -12000;
			   break;
			   }*/
		iRtnFunction = 13000;
		break;

	case 13000:
		if (Task.m_bOKLensPass == 1)   //Lens ³Ñ±è ¿Ï·á»óÅÂ
		{
			iRtnFunction = 14100;
			break;
		}

		Task.m_iRetry_Opt = 0;
		LightControlthird.ctrlLedVolume(LIGHT_PCB, model.m_iLedValue[LEDDATA_HOLDER]);		// Align¸¸ Á¶¸í ON
		Task.d_Align_offset_x[PCB_Holder_MARK] = 0;
		Task.d_Align_offset_y[PCB_Holder_MARK] = 0;
		Task.d_Align_offset_th[PCB_Holder_MARK] = 0;
		if (motor.Pcb_Motor_Move(Holder_Pos))
		{
			Task.PCBTaskTime = myTimer(true);
			logStr.Format("Pcb Holder À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = 13300;
		}
		else
		{
			logStr.Format("Pcb Holder À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -13000;
		}
		break;

	case 13300:
		if (motor.PCB_Z_Motor_Move(Holder_Pos))
		{
			Task.PCBTaskTime = myTimer(true);
			logStr.Format("Pcb Holder ZÀ§Ä¡ ÀÌµ¿ ¿Ï·á[%d]", iUseStep);
			putListLog(logStr);
			//151109 ¿µÁø ÀÓ½Ã µô·¹ÀÌ
			Sleep(1000);
			iRtnFunction = 13500;
		}
		else
		{
			logStr.Format("Pcb Holder ZÀ§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -13300;
		}
		break;
	case 13500:
		if ((myTimer(true) - Task.PCBTaskTime) > iCamDelay && (motor.IsStopAxis(Motor_PCB_X) && motor.IsStopAxis(Motor_PCB_Y)))
		{
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 13700;
		}
		break;
	case 13700: // lens Align

		if (Task.m_iRetry_Opt > iAlignRetry)
		{
			logStr.Format("PCB Holder Àç°Ë»ç %d È¸ ½ÇÆÐ[%d]\n º¸Á¤ ¹ÌÀû¿ëÀ¸·Î ÁøÇàÇÏ½Ã°Ú½À´Ï±î?", Task.m_iRetry_Opt, iUseStep);
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
				logStr.Format("PCB Holder Àç°Ë»ç ½ÃÀÛ[%d]", iUseStep);
				putListLog(logStr);
				//logStr.Format("PCB Holder Àç°Ë»ç %d È¸ ½ÇÆÐ[%d]", Task.m_iRetry_Opt, iUseStep);
				//errMsg2(Task.AutoFlag,logStr);
			}

			break;
		}

		offsetX = offsetY = offsetTh = 0.0;
		iRtn = theApp.MainDlg->procCamAlign(CAM2 - 1, PCB_Holder_MARK, false, offsetX, offsetY, offsetTh);
		offsetTh = 0.0;
		saveInspImage(PCB_IMAGE_SAVE, Task.m_iRetry_Opt);

		Task.m_iRetry_Opt++;
		offsetTh = 0;//holder x,yÃà¸¸
		if (iRtn == 0)
		{
			Task.d_Align_offset_x[PCB_Holder_MARK] -= offsetX;
			Task.d_Align_offset_y[PCB_Holder_MARK] -= offsetY;
			Task.d_Align_offset_th[PCB_Holder_MARK] += offsetTh;

			logStr.Format("Pcb Holder : %.3lf %.3lf %.3lf", Task.d_Align_offset_x[PCB_Holder_MARK], Task.d_Align_offset_y[PCB_Holder_MARK], Task.d_Align_offset_th[PCB_Holder_MARK]);//0.000
																																													 //			Sleep(500);
																																													 //pcbDlg->m_labelAlignResult.SetText(logStr);
																																													 //pcbDlg->m_labelAlignResult.Invalidate();

			putListLog(logStr);

			int iRtnVal = theApp.MainDlg->AlignLimitCheck(CAM2 - 1, offsetX, offsetY, offsetTh);
			if (iRtnVal == 1)
			{
				iRtnFunction = 14000;				// º¸Á¤ ÀÌµ¿
			}
			else if (iRtnVal == 2)
			{
				sLangChange.LoadStringA(IDS_STRING654);	//Lens Align [%d] ¿Ï·á [%d]
				logStr.Format("		Pcb Holder [%d] ¿Ï·á [%d]", Task.m_iRetry_Opt, iUseStep);
				putListLog(logStr);

				theApp.MainDlg->InstantMarkDelete(PCB_Holder_MARK);			//ÀÓ½Ã µî·Ï ¸¶Å© »èÁ¦

				logStr.Format("		Pcb Holder Complete : %d, %.03f, %.03f, %.03f", Task.m_iPcbPickupNo, Task.d_Align_offset_x[PCB_Holder_MARK], Task.d_Align_offset_y[PCB_Holder_MARK], Task.d_Align_offset_th[PCB_Holder_MARK]);//0.000);
				AlignResultSave(logStr);
				Task.m_iRetry_Opt = 0;
				iRtnFunction = 14100;				// ¿Ï·á
			}
			else
			{
				logStr.Format("Pcb Holder [%d] º¸Á¤ ¹üÀ§ ÃÊ°ú[%d]", Task.m_iRetry_Opt, iUseStep);
				errMsg2(Task.AutoFlag, logStr);
				AlignLogSave(logStr);
				theApp.MainDlg->InstantMarkDelete(PCB_Holder_MARK);
				iRtnFunction = -13700;				// NG
			}
		}
		else
		{
			logStr.Format("Pcb Holder [%d] ¸¶Å© ÀÎ½Ä ½ÇÆÐ[%d]", Task.m_iRetry_Opt, iUseStep);
			putListLog(logStr);
			Sleep(300);
			iRtnFunction = 13700;					//  Àç°Ë»ç 
		}
		break;

	case 14000://!! º¸Á¤·® ÀÌµ¿.- Retry
		if (motor.Pcb_Holder_Align_Move(Holder_Pos, Task.d_Align_offset_x[PCB_Holder_MARK], Task.d_Align_offset_y[PCB_Holder_MARK], Task.d_Align_offset_th[PCB_Holder_MARK]))
		{
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 13500;
		}
		else
		{
			logStr.Format("Pcb Holder º¸Á¤ À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -14000;
		}
		break;
	case 14100:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format(" PCB ZÃà ´ë±âÀ§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iUseStep);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -14100;
			break;
		}
#if (____AA_WAY == PCB_TILT_AA)
		iRtnFunction = 15000;
#elif (____AA_WAY == LENS_TILT_AA)
		iRtnFunction = 26000;

#endif

		break;
	default:
		logStr.Format("PCB Á¦Ç° ÅõÀÔ Thread Step ¹øÈ£ ºñÁ¤»ó . [%d]", iUseStep);
		errMsg2(Task.AutoFlag, logStr);
		iRtnFunction = -1;
		break;
	}
	return iRtnFunction;
}

int	CPcbProcess1::RunProc_SensorAlign(int iUseStep)
{
	int iRtnFunction = iUseStep;
	int iRtn = 0;
	CString logStr = _T("");
	bool bChk = true;
	double offsetX = 0.0, offsetY = 0.0, offsetTh = 0.0;
	int iCamDelay = model.strInfo_Cam[1].m_iDelayTime;	//PCB ¿µ»ó È¹µæ Delay
	int iAlignRetry = model.strInfo_Cam[1].m_iRetryCnt;
	int iLaserDelay = model.strInfo_Cam[0].m_iDelayTime;	//Laser ÃøÁ¤Àü Delay
	switch (iUseStep)
	{
	case 26000:
		offsetX = offsetY = offsetTh = 0.0;
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("		PCB ZÃà ´ë±âÀ§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iUseStep);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -26000;
			break;
		}
		iRtnFunction = 26050;
		break;
	case 26050:
		Task.m_iRetry_Opt = 0;
		iRtnFunction = 26600;
		break;

	case 26600:
		//Task.LensTaskTime = myTimer(true);
		iRtnFunction = 26610;
		break;

	case 26610:
		//ctrlSubDlg(MAIN_DLG);
		theApp.MainDlg->m_iCurCamNo = 0;
		//SetDigReference(PCB_Chip_MARK);
		LightControlthird.ctrlLedVolume(LIGHT_PCB, model.m_iLedValue[LEDDATA_SENSOR]);		// Align¸¸ Á¶¸í ON

		if (motor.Pcb_Motor_Move(Align_Pos))
		{
			if (motor.PCB_Z_Motor_Move(Align_Pos))
			{
				logStr.Format("PCB Sensor Align À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]", iUseStep);
				putListLog(logStr);
				Task.PCBTaskTime = myTimer(true);
				Task.d_Align_offset_x[PCB_Chip_MARK] = 0;
				Task.d_Align_offset_y[PCB_Chip_MARK] = 0;
				Task.d_Align_offset_th[PCB_Chip_MARK] = 0;
				iRtnFunction = 26615;
			}
		}
		else
		{
			logStr.Format("PCB Sensor Align À§Ä¡ ÀÌµ¿ ½ÇÆÐ [%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -26610;
		}
		break;
	case 26615:
		if ((myTimer(true) - Task.PCBTaskTime) > iCamDelay && (motor.IsStopAxis(Motor_PCB_X) && motor.IsStopAxis(Motor_PCB_Y)))
		{
			iRtnFunction = 26620;
		}
		break;
	case 26620:
		if (Task.m_iRetry_Opt>iAlignRetry)
		{
			logStr.Format("PCB Align(*SensorAlign*) Àç°Ë»ç %d È¸ ½ÇÆÐ[%d]\n º¸Á¤ ¹ÌÀû¿ëÀ¸·Î ÁøÇàÇÏ½Ã°Ú½À´Ï±î?", Task.m_iRetry_Opt, iUseStep);
			Task.d_Align_offset_x[PCB_Chip_MARK] = 0.0;
			Task.d_Align_offset_y[PCB_Chip_MARK] = 0.0;
			Task.d_Align_offset_th[PCB_Chip_MARK] = 0.0;
			Task.m_iRetry_Opt = 0;
			if (askMsg(logStr) == IDOK)
			{
				iRtnFunction = 26629;
			}
			else
			{
				iRtnFunction = 26620;
				logStr.Format("PCB Align Àç°Ë»ç ½ÃÀÛ[%d]", iUseStep);
				putListLog(logStr);
			}
			break;

			break;
		}

		offsetX = offsetY = offsetTh = 0.0;

		iRtn = theApp.MainDlg->procCamAlign(CAM2 - 1, PCB_Chip_MARK, false, offsetX, offsetY, offsetTh);
		saveInspImage(CHIP_IMAGE_SAVE, Task.m_iRetry_Opt);
		Task.m_iRetry_Opt++;

		//offsetTh=0;
		if (iRtn == 0)
		{
			Task.d_Align_offset_x[PCB_Chip_MARK] -= offsetX;
			Task.d_Align_offset_y[PCB_Chip_MARK] -= offsetY;
			Task.d_Align_offset_th[PCB_Chip_MARK] -= offsetTh;


			Task.dPcbAlignTh = Task.d_Align_offset_th[PCB_Chip_MARK];

			logStr.Format("PCB Sensor Align : %.3lf %.3lf %.3lf", Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]);
			//pcbDlg->m_labelAlignResult.SetText(logStr);
			//pcbDlg->m_labelAlignResult.Invalidate();

			putListLog(logStr);

			int iRtnVal = theApp.MainDlg->AlignLimitCheck(CAM2 - 1, offsetX, offsetY, offsetTh);

			if (iRtnVal == 1)
			{
				iRtnFunction = 26625;				// º¸Á¤ ÀÌµ¿
			}
			else if (iRtnVal == 2)
			{
				logStr.Format("		PCB Sensor Align [%d] ¿Ï·á [%d]", Task.m_iRetry_Opt, iUseStep);
				putListLog(logStr);
				//InstantMarkDelete(PCB_Chip_MARK);			//ÀÓ½Ã µî·Ï ¸¶Å© »èÁ¦

				logStr.Format("		PCB Sensor Align Complete : %d, %.03f, %.03f, %.03f", Task.m_iPcbPickupNo, Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]);
				AlignResultSave(logStr);
				Task.m_iRetry_Opt = 0;

				Task.m_timeChecker.Measure_Time(4);	//Laser º¯À§ ÃøÁ¤ ½ÃÀÛ ½Ã°£

				iRtnFunction = 26629;		// ¿Ï·á//iRtnFunction = 16630;				// ¿Ï·á
				LightControlthird.ctrlLedVolume(LIGHT_PCB, 0);		// Align¸¸ Á¶¸í ON
			}
			else
			{
				logStr.Format("PCB Sensor Align [%d] º¸Á¤ ¹üÀ§ ÃÊ°ú", Task.m_iRetry_Opt, iUseStep);
				errMsg2(Task.AutoFlag, logStr);
				AlignLogSave(logStr);
				//InstantMarkDelete(PCB_Chip_MARK);
				iRtnFunction = -26620;				// NG
			}
		}
		else
		{
			logStr.Format("PCB Sensor Align [%d] ¸¶Å© ÀÎ½Ä ½ÇÆÐ[%d]", Task.m_iRetry_Opt, iUseStep);
			putListLog(logStr);
			Sleep(300);
			iRtnFunction = 26620;				//  Àç°Ë»ç 
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
			logStr.Format("PCB Sensor Align º¸Á¤ À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -26625;
		}
		break;
	case 26629:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			sLangChange.LoadStringA(IDS_STRING305);	//PCBºÎ zÃà ¸ðÅÍ À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]
			logStr.Format(sLangChange, iUseStep);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -26629;
			break;
		}
		iRtnFunction = 26990;
		break;
	case 26990://! Lens-ZÃà ´ë±â À§Ä¡ ÀÌµ¿
#if (____AA_WAY == PCB_TILT_AA)
		if (sysData.m_iEpoxyLaserInspPass == 1)
		{
			iRtnFunction = 30000;	//µµÆ÷ÀÌµ¿
		}
		else
		{
			iRtnFunction = 27000;	//LaserÃøÁ¤ ->Align -> µµÆ÷
		}
#elif (____AA_WAY == LENS_TILT_AA)
		if (sysData.m_iEpoxyLaserInspPass == 1)
		{
			iRtnFunction = 30000;//Laser ÃøÁ¤ Pass
		}
		else
		{
			iRtnFunction = 27000;
		}
#endif
		break;
	default:
		logStr.Format("Lens ¿ÜºÎ Align Thread Step ¹øÈ£ ºñÁ¤»ó [%d]", iUseStep);
		errMsg2(Task.AutoFlag, logStr);
		iRtnFunction = -1;
		break;
	}
	logStr.Empty();
	return iRtnFunction;
}

int	CPcbProcess1::RunProc_LaserMeasure(int iUseStep)
{
	int iRtnFunction = iUseStep;
	int iRtn = 0;
	CString logStr = "";
	bool bChk = true;
	double offsetX = 0.0, offsetY = 0.0, offsetTh = 0.0;
	int iCamDelay = model.strInfo_Cam[1].m_iDelayTime;	//PCB ¿µ»ó È¹µæ Delay
	int iAlignRetry = model.strInfo_Cam[1].m_iRetryCnt;
	int iLaserDelay = model.strInfo_Cam[0].m_iDelayTime;	//Laser ÃøÁ¤Àü Delay
	switch (iUseStep)
	{
	case 27000:
		Task.oldLaserTx = 0.1;
		Task.oldLaserTy = 0.1;
		iLaser_Pos = 0;// 4;//4¹øºÎÅÍ°¡ laser out point
		LightControlthird.ctrlLedVolume(LIGHT_PCB, 0);		// Align¸¸ Á¶¸í ON
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("[¿îÀü ÁØºñ] PCB ZÃà ´ë±âÀ§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iUseStep);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -27000;
			break;
		}

		//if ((sysData.m_iDispensePass == 1) || (Task.m_bOkDispense == 1))
		//{
		//	iRtnFunction = 30000;	//-- µµÆ÷ Pass Mode ÀÌ°Å³ª, µµÆ÷ ¿Ï·á ÀÏ °æ¿ì
		//	break;
		//}

		iRtnFunction = 27100;// 27350;//<-ÀÓ½Ã ÆÐ½º   Original-> 27100; 
		break;

	case 27100:
		if (motor.Pcb_Motor_Move_Laser(iLaser_Pos, Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]))
		{
			Task.PCBTaskTime = myTimer(true);
			logStr.Format("Laser º¯À§ ÃøÁ¤ ¿ÜºÎ À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = 27150;
		}
		else
		{
			logStr.Format("Laser º¯À§ ÃøÁ¤ ¿ÜºÎ À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -27100;
		}
		break;

	case 27150:
		if (iLaser_Pos == 0)
		{
			if (!motor.PCB_Z_Motor_Move(Laser_Pcb_Pos))
			{
				logStr.Format("PCB Laser_Pcb_Pos Z ÀÌµ¿ ½ÇÆÐ[%d]", iUseStep);
				putListLog(logStr);
				errMsg2(Task.AutoFlag, logStr);
				iRtnFunction = -27150;
				break;
			}
			else
			{
				logStr.Format("PCB Laser_Pcb_Pos Z ÀÌµ¿ ¿Ï·á[%d]", iUseStep);
				putListLog(logStr);
			}
		}

		if (iLaser_Pos == 0) { iRtnFunction = 27160; }//Ã³À½¿¡¸¸ ½Ç¸°´õ ÇÏ°­
		else { iRtnFunction = 27200; }//Ã³À½¾Æ´Ï¸é ¹Ù·Î °Ë»ç·Î.
		Task.PCBTaskTime = myTimer(true);
		break;
		//laser ½Ç¸°´õ ÇÏ°­
	case 27160:
		if (Dio.LaserCylinderUPDOWN(false, false))
		{
			logStr.Format("LASER ½Ç¸°´õ ÇÏ°­ ¿Ï·á[%d]", iRtnFunction);
			theApp.MainDlg->putListLog(logStr);
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 27170;
		}
		else
		{
			logStr.Format("LASER ½Ç¸°´õ ÇÏ°­ ½ÇÆÐ [%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -27160;
		}
		break;

	case 27170:
		if (Dio.LaserCylinderCheck(false, false))
		{
			logStr.Format("LASER ½Ç¸°´õ ÇÏ°­ È®ÀÎ ¿Ï·á[%d]", iRtnFunction);
			theApp.MainDlg->putListLog(logStr);
			iRtnFunction = 27200;

			Sleep(300);
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > IO_DELAY_TIME)
		{
			logStr.Format("LASER ½Ç¸°´õ ÇÏ°­ ½Ã°£ ÃÊ°ú..[%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -27170;
		}
		break;
		//laser½Ç¸°´õ ÇÏ°­ END
	case 27200:
		if ((myTimer(true) - Task.PCBTaskTime) > iLaserDelay && (motor.IsStopAxis(Motor_PCB_X) && motor.IsStopAxis(Motor_PCB_Y)))
		{
			Sleep(200);
			iRtnFunction = 27250;
		}
		break;
	case 27250:

		Keyence.func_CL3000_Scan(Task.m_Laser_Point[iLaser_Pos]);
		Sleep(100);
		logStr.Format("º¯ À§¼¾¼­ %lf - %d À§Ä¡[%d]", Task.m_Laser_Point[iLaser_Pos], iLaser_Pos + 1, iUseStep);
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
					logStr.Format("Laser ÃøÁ¤°ªÀÌ»ó: %.04lf, %.04lf, %.04lf, %.04lf [%d]", LaserValue[0], LaserValue[1], LaserValue[2], LaserValue[3], iUseStep);
					errMsg2(Task.AutoFlag, logStr);
					iRtnFunction = -27250;
					break;
				}

				if (theApp.MainDlg->_calcLaserTilt(LaserPos, LaserValue, Task.d_Align_offset_xt[PCB_Chip_MARK], Task.d_Align_offset_yt[PCB_Chip_MARK]))
				{
					Task.m_dataOffset_x[0] = Task.d_Align_offset_xt[PCB_Chip_MARK];
					Task.m_dataOffset_y[0] = Task.d_Align_offset_yt[PCB_Chip_MARK];
					logStr.Format("	º¸Á¤·® Tx: %.04lf, Ty: %.04lf", Task.d_Align_offset_xt[PCB_Chip_MARK], Task.d_Align_offset_yt[PCB_Chip_MARK]);
					putListLog(logStr);

					int Rnd = theApp.MainDlg->TiltAlignLimitCheck(Task.d_Align_offset_xt[PCB_Chip_MARK], Task.d_Align_offset_yt[PCB_Chip_MARK]);
					if (Rnd == 2)
					{
						if (Task.m_dataOffset_x[0] == 0 || Task.m_dataOffset_y[0] == 0)
						{
							logStr.Format("Laser º¯À§ Â÷ °ª ÀÌ»ó ¹ß»ý..Xt : %lf, Yt : %lf", Task.m_dataOffset_x[0], Task.m_dataOffset_y[0]);
							//errMsg2(Task.AutoFlag, logStr);
							//iRtnFunction = -27250;
							//break;
						}
						if (!g_ADOData.func_AATaskToRecordLaser(Task.ChipID, Task.m_dataOffset_x[0], Task.m_dataOffset_y[0], Task.m_Laser_Point))
						{
							logStr.Format("DataBase Laser º¯À§ ÃøÁ¤ Data ±â·Ï ½ÇÆÐ.[%d]\n MS Office¸¦ ´Ý¾ÆÁÖ¼¼¿ä.", iUseStep);
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
						iRtnFunction = 27310;//->Laser½Ç¸°´õ»ó½Â, 27350;->PCB WaitPos
						iLaser_Pos++;
					}
					else if (Rnd == 1)
					{
						iRtnFunction = 27300;
					}
					else
					{
						logStr.Format("Laser Tilt  º¸Á¤°ª Limit¸¦ ÃÊ°ú ÇÏ¿´½À´Ï´Ù.[%d]", iUseStep);
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
		if (motor.Pcb_Move_Tilt(Task.d_Align_offset_xt[PCB_Chip_MARK], Task.d_Align_offset_yt[PCB_Chip_MARK]))
		{
			iRtnFunction = 27100;
			logStr.Format("PCB Xt : %lf, Yt : %lf [%d]", Task.d_Align_offset_xt[PCB_Chip_MARK], Task.d_Align_offset_yt[PCB_Chip_MARK], iUseStep);
			putListLog(logStr);
			iLaser_Pos = 0;
		}
		else
		{
			logStr.Format("PCB tx,tyÃà  À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -27300;
		}
		break;

		//laser ½Ç¸°´õ »ó½Â
	case 27310:
		if (Dio.LaserCylinderUPDOWN(true, false))
		{
			logStr.Format("LASER ½Ç¸°´õ »ó½Â ¿Ï·á[%d]", iRtnFunction);
			theApp.MainDlg->putListLog(logStr);
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 27320;
		}
		else
		{
			logStr.Format("LASER ½Ç¸°´õ »ó½Â ½ÇÆÐ [%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -27310;
		}
		break;
	case 27320:
		if (Dio.LaserCylinderCheck(true, false))
		{
			logStr.Format("LASER ½Ç¸°´õ »ó½Â È®ÀÎ ¿Ï·á[%d]", iRtnFunction);
			theApp.MainDlg->putListLog(logStr);
			iRtnFunction = 27350;
			Sleep(300);
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > IO_DELAY_TIME)
		{
			logStr.Format("LASER ½Ç¸°´õ »ó½Â ½Ã°£ ÃÊ°ú..[%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -27320;
		}
		break;
		//laser½Ç¸°´õ »ó½Â END

	case 27350:
		if (motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("PCB ZÃà ´ë±â À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = 27600;
		}
		else
		{
			logStr.Format("PCB ZÃà ´ë±â À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -27350;
		}

		break;
	case 27600:

		iRtnFunction = 27650;
		break;
	case 27650:
		//Sensor Align Ãß°¡
		//
		offsetX = offsetY = offsetTh = 0.0;
		iRtnFunction = 27750;
		break;
	case 27750:
		Task.m_iRetry_Opt = 0;
		iRtnFunction = 27800;
		break;
	case 27800:
		theApp.MainDlg->ctrlSubDlg(MAIN_DLG);
		theApp.MainDlg->m_iCurCamNo = 0;
		LightControlthird.ctrlLedVolume(LIGHT_PCB, model.m_iLedValue[LEDDATA_SENSOR]);		// Align¸¸ Á¶¸í ON

		if (motor.Pcb_Motor_Move(Align_Pos))
		{
			if (motor.PCB_Z_Motor_Move(Align_Pos))
			{
				logStr.Format("PCB Sensor Align À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]", iUseStep);
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
			logStr.Format("PCB Sensor Align À§Ä¡ ÀÌµ¿ ½ÇÆÐ [%d]", iUseStep);
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
			logStr.Format("PCB Align(*Laser*) Àç°Ë»ç %d È¸ ½ÇÆÐ[%d]\n º¸Á¤ ¹ÌÀû¿ëÀ¸·Î ÁøÇàÇÏ½Ã°Ú½À´Ï±î?", Task.m_iRetry_Opt, iUseStep);
			Task.m_iRetry_Opt = 0;
			Task.d_Align_offset_x[PCB_Chip_MARK] = 0.0;
			Task.d_Align_offset_y[PCB_Chip_MARK] = 0.0;
			Task.d_Align_offset_th[PCB_Chip_MARK] = 0.0;
			if (askMsg(logStr) == IDOK)
			{
				iRtnFunction = 27960;
				logStr.Format("PCB Align ¹Ìº¸Á¤ ÁøÇà[%d]", iUseStep);
				putListLog(logStr);
			}
			else
			{
				iRtnFunction = 27900;
				logStr.Format("PCB Align Àç°Ë»ç ½ÃÀÛ[%d]", iUseStep);
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
			Task.d_Align_offset_x[PCB_Chip_MARK] -= offsetX;
			Task.d_Align_offset_y[PCB_Chip_MARK] -= offsetY;
			Task.d_Align_offset_th[PCB_Chip_MARK] -= offsetTh;

			Task.dPcbAlignTh = Task.d_Align_offset_th[PCB_Chip_MARK];
			logStr.Format("PCB Sensor Align : %.3lf %.3lf %.3lf", Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]);
			putListLog(logStr);

			int iRtnVal = theApp.MainDlg->AlignLimitCheck(CAM2 - 1, offsetX, offsetY, offsetTh);

			if (iRtnVal == 1)
			{
				iRtnFunction = 27950;				// º¸Á¤ ÀÌµ¿
			}
			else if (iRtnVal == 2)
			{
				logStr.Format("		PCB Sensor Align [%d] ¿Ï·á [%d]", Task.m_iRetry_Opt, iUseStep);
				putListLog(logStr);
				logStr.Format("		PCB Sensor Align Complete : %d, %.03f, %.03f, %.03f", Task.m_iPcbPickupNo, Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]);
				AlignResultSave(logStr);
				Task.m_iRetry_Opt = 0;

				Task.m_timeChecker.Measure_Time(4);	//Laser º¯À§ ÃøÁ¤ ½ÃÀÛ ½Ã°£


				iRtnFunction = 27960;		// ¿Ï·á
				LightControlthird.ctrlLedVolume(LIGHT_PCB, 0);		// Align¸¸ Á¶¸í ON 
				LightControlthird.ctrlLedVolume(LIGHT_OC_6500K, 0);		// Align¸¸ Á¶¸í ON
			}
			else
			{
				logStr.Format("PCB Sensor Align [%d] º¸Á¤ ¹üÀ§ ÃÊ°ú", Task.m_iRetry_Opt, iUseStep);
				errMsg2(Task.AutoFlag, logStr);
				AlignLogSave(logStr);
				iRtnFunction = -27900;				// NG
			}
		}
		else
		{
			logStr.Format("PCB Sensor Align(*Laser*) [%d] ¸¶Å© ÀÎ½Ä ½ÇÆÐ[%d]", Task.m_iRetry_Opt, iUseStep);
			putListLog(logStr);
			Sleep(500);
			iRtnFunction = 27900;				//  Àç°Ë»ç 
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
			logStr.Format("PCB Sensor Align º¸Á¤ À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -27950;
		}
		break;
	case 27960:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("PCBºÎ ZÃà ´ë±â À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -27960;
			break;
		}
		else
		{
			logStr.Format("PCBºÎ ZÃà ´ë±â À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = 27970;
		}

		break;
	case 27970:
		iRtnFunction = 27990;
	case 27990:
		iRtnFunction = 30000;
		break;
	default:
		logStr.Format("Pcb Thread Step ¹øÈ£ ºñÁ¤»ó .[%d]", iUseStep);
		errMsg2(Task.AutoFlag, logStr);
		iRtnFunction = -1;
		break;
	}
	return iRtnFunction;
}

int CPcbProcess1::RunProc_EpoxyNewResing(int iUseStep)
{//! Epoxy µ¿ÀÛ ¹× µµÆ÷ °Ë»ç Step(17000 ~ 17999)
	int iRtnFunction = iUseStep;
	int iCamDelay = model.strInfo_Cam[1].m_iDelayTime;		//PCB ¿µ»ó È¹µæ Delay
	int iRtn = 0;
	CString logStr = "";
	bool bChk = true;
	double offsetX = 0.0, offsetY = 0.0, offsetTh = 0.0;
	int iLaserDelay = model.strInfo_Cam[0].m_iDelayTime;	//Laser ÃøÁ¤Àü Delay
	int iAlignRetry = model.strInfo_Cam[1].m_iRetryCnt;

	switch (iUseStep)
	{
	case 30000:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			sLangChange.LoadStringA(IDS_STRING1012);	//PCB_ZÃà ´ë±âÀ§Ä¡ ÀÌµ¿ ½ÇÆÐ.
			logStr.Format(sLangChange, iUseStep);
			putListLog(logStr);
			iRtnFunction = -30000;
			break;
		}

		if ((sysData.m_iDispensePass == 1) || (Task.m_bOkDispense == 1))
		{
			iRtnFunction = 34000;// 31000;	//-- µµÆ÷ Pass Mode ÀÌ°Å³ª, µµÆ÷ ¿Ï·á ÀÏ °æ¿ì
		}
		else
		{
			iRtnFunction = 30020;
		}
		break;
	case 30020: //Dispenser -ZÃà ÇÏ°­
		if (motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			iRtnFunction = 30030;
		}
		else
		{
			logStr.Format("PCB Z Wait À§Ä¡ ÀÌµ¿ ¿Ï·á ½ÇÆÐ [%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -30020;
		}
		break;
	case 30030:  //µµÆ÷ À§Ä¡ ÀÌµ¿
		LightControlthird.ctrlLedVolume(LIGHT_PCB, 0);		// Align Á¶¸í OFF
		if (motor.Pcb_Motor_Move(Dispense_Pos, Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]))
		{
			sLangChange.LoadStringA(IDS_STRING935);	//PCB Dispense º¸Á¤ À§Ä¡ ÀÌµ¿ ¿Ï·á-º¸Á¤·® X:%.03lf,Y:%.03lf,T:%.03lf
			logStr.Format(sLangChange, Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]);
			putListLog(logStr);
			iRtnFunction = 30040;
		}
		else
		{
			sLangChange.LoadStringA(IDS_STRING938);	//PCB Dispense À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%
			logStr.Format(sLangChange + _T("d]"), iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -30030;
		}
		break;
	case 30040: //Dispenser-z Ãà »ó½Â
		if (motor.PCB_Z_Motor_Move(Dispense_Pos))
		{
			iRtnFunction = 30050;
		}
		else
		{
			sLangChange.LoadStringA(IDS_STRING977);	//PCB Z Dispense À§Ä¡ ÀÌµ¿ ½ÇÆÐ
			logStr.Format(sLangChange + _T("[%d]"), iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -30040;
		}
		break;

	case 30050: // µð½ºÆæ½º µ¿ÀÛ

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
			//point Çü
		}

		if (bChk)
		{
			Task.m_bOkDispense = 1;

			logStr.Format("PCB Dispense ¿Ï·á[%d]", iUseStep);
			putListLog(logStr);

			iRtnFunction = 30070;
		}
		else
		{
			logStr.Format("PCB Dispense ½ÇÆÐ [%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -30050;
		}
		break;
	case 30070:
		if (motor.IsStopAxis(Motor_PCB_X) && motor.IsStopAxis(Motor_PCB_Y))
		{
			LightControlthird.ctrlLedVolume(LIGHT_PCB, model.m_iLedValue[LEDDATA_SENSOR]);//µµÆ÷ °Ë»çÀü ¾ó¶óÀÎ¸¶Å©¿ë ¶óÀÌÆ®
			iRtnFunction = 30100;
		}
		break;
	case 30100:
		iRtnFunction = 31000;
		break;
	case 31000:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			sLangChange.LoadStringA(IDS_STRING305);	//PCBºÎ zÃà ¸ðÅÍ À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]
			logStr.Format(sLangChange, iUseStep);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -31000;
			break;
		}
		else
		{
			logStr.Format("PCB Z ´ë±â À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]", iUseStep);
			putListLog(logStr);
		}
		iRtnFunction = 34000;
		/*if( sysData.m_iDispenseInspPass == 0 )
		{
		iRtnFunction = 32000;

		}else
		{
		iRtnFunction = 34000;
		}*/
		break;

	case 32000: // µµÆ÷°Ë»ç ÀÌµ¿
		LightControlthird.ctrlLedVolume(LIGHT_PCB, model.m_iLedValue[LEDDATA_HOLDER]);		// Align¸¸ Á¶¸í ON
		if (motor.Pcb_Motor_Move(Holder_Pos))
		{
			iRtnFunction = 32500;
		}
		else
		{
			sLangChange.LoadStringA(IDS_STRING989);	//PCB µµÆ÷°Ë»ç À§Ä¡ ÀÌµ¿ ½ÇÆÐ
			logStr.Format(sLangChange + _T("[%d]"), iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -32000;
		}
		break;

	case 32500:// ÀÌµ¿ÈÄ, ÀÏÁ¤ ½Ã°£ Áö¿¬ ¹× ¸¶Å© È®ÀÎ
		if (motor.PCB_Z_Motor_Move(Holder_Pos))

		{
			Task.PCBTaskTime = myTimer(true);
			sLangChange.LoadStringA(IDS_STRING990);	//PCB µµÆ÷°Ë»ç À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]
			logStr.Format(sLangChange, iUseStep);
			putListLog(logStr);
			iRtnFunction = 33000;
		}
		else
		{
			sLangChange.LoadStringA(IDS_STRING989);	//PCB µµÆ÷°Ë»ç À§Ä¡ ÀÌµ¿ ½ÇÆÐ
			logStr.Format(sLangChange + _T("[%d]"), iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -32500;
		}
		break;
	case 33000: //µµÆ÷°Ë»ç zÃà ÀÌµ¿
		if ((myTimer(true) - Task.PCBTaskTime) > iCamDelay && (motor.IsStopAxis(Motor_PCB_X) && motor.IsStopAxis(Motor_PCB_Y)))
		{
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
		}
		LightControlthird.ctrlLedVolume(LIGHT_PCB, model.m_iLedValue[LEDDATA_EPOXY_INSP]);
		break;
	case 33500: //µµÆ÷°Ë»ç                                Ãß°¡ÇØ¾ßÇÔ
		Sleep(100);
		vision.clearOverlay(CAM1);
		bChk = theApp.MainDlg->_EpoxyFinddispense(CAM1);
		vision.drawOverlay(CAM1);
		if (!bChk)
		{
			putListLog("Epoxy µµÆ÷ °Ë»ç ½ÇÆÐ");
			//logStr.Format("Epoxy Table ÁÂÇ¥ (X:%.03f, Y:%.03f, ¥È:%.03f)", motor.GetEncoderPos(Motor_PCB_X), motor.GetEncoderPos(Motor_PCB_Y), motor.GetEncoderPos(Motor_PCB_TH));
			//putListLog(logStr);
			logStr.Format("Epoxy µµÆ÷ °Ë»ç ½ÇÆÐ. \nÀÚµ¿ ¿îÀü ÁøÇà ÇÏ½Ã°Ú½À´Ï±î?");
			//_stprintf_s(motor.m_szLogMsg, "Epoxy µµÆ÷ °Ë»ç ½ÇÆÐ. \nÀÚµ¿ ¿îÀü ÁøÇà ÇÏ½Ã°Ú½À´Ï±î?");

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
				logStr.Format("Epoxy µµÆ÷ °Ë»ç ½ÇÆÐ[%d]", iUseStep);
				iRtnFunction = -33500;
				break;
			}
		}
		Task.m_timeChecker.Measure_Time(3);	//µµÆ÷ ¿Ï·á ½Ã°£
		Task.m_dTime_Epoxy = Task.m_timeChecker.m_adTime[3] - Task.m_timeChecker.m_adTime[2];
		theApp.MainDlg->dispGrid();

		logStr.Format("PCB µµÆ÷°Ë»ç ¿Ï·á[%d]", iUseStep);
		putListLog(logStr);
		iRtnFunction = 34000;
		break;
	case 34000:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			sLangChange.LoadStringA(IDS_STRING1012);	//PCB_ZÃà ´ë±âÀ§Ä¡ ÀÌµ¿ ½ÇÆÐ.
			logStr.Format(sLangChange, iUseStep);
			putListLog(logStr);
			iRtnFunction = -34000;
			break;
		}
#if (____AA_WAY == PCB_TILT_AA)
		iRtnFunction = 39000;
#elif (____AA_WAY == LENS_TILT_AA)
		iRtnFunction = 35000;
#endif
		break;
	default:
		sLangChange.LoadStringA(IDS_STRING939);	//PCB Dispenser Thread Step ¹øÈ£ ºñÁ¤»ó .
		logStr.Format(sLangChange + _T(" [%d]"), iUseStep);
		errMsg2(Task.AutoFlag, logStr);
		iRtnFunction = -1;
		break;
	}

	return iRtnFunction;
}

int CPcbProcess1::RunProc_InspAAPos(int iUseStep)
{
	//! Lens Pickup¿¡ Á¦Ç° ³Ñ±è Step	(18000 ~ 19999)

	int iRtnFunction = iUseStep;
	int iRtn = 0;
	CString logStr = "";
	double	dFinalDelay = (double)(model.strInfo_Cam[3].m_iDelayTime);
	bool bChk = true;
	double offsetX = 0.0, offsetY = 0.0, offsetTh = 0.0;

	switch (iUseStep)
	{
	case 39000:
#if (____AA_WAY == PCB_TILT_AA)
		iRtnFunction = 41000;
#elif (____AA_WAY == LENS_TILT_AA)
		iRtnFunction = 40000;
#endif		
		break;
		vision.clearOverlay(CAM1);
		vision.drawOverlay(CAM1);
		//if (sysData.m_iDefectInspPass == 1)	// DEFECT °Ë»ç PASS
		//{
		//    iRtnFunction = 39999;
		//}
		//else
		//{
		//    iRtnFunction = 39100;
		//}
		//if(model.m_IsUseBrightDefectTest == 1)	// ±¤¿ø Defect Picxel °Ë»ç À¯¹«

		iRtnFunction = 39700;//aa¶§ defect Pass
		break;
	case 39100:
		LightControlthird.ctrlLedVolume(LIGHT_OC_6500K, model.m_iLedValue[LEDDATA_6500K]);
		if (!motor.Pcb_Motor_Move(OC_6500K_Pos, Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]))
		{
			logStr.Format("PCBºÎ ¸ðÅÍ 0C 6500K °Ë»ç À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = -39100;
		}
		else
		{
			iRtnFunction = 39300;
		}
		break;
	case 39300:
		if (!motor.PCB_Z_Motor_Move(OC_6500K_Pos))
		{
			logStr.Format(_T("PCB Z axis 0C 6500K Pos Move Failed [%d]"), iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -39300;
			break;
		}
		else
		{
			logStr.Format(_T("PCB Z axis 0C 6500K Pos Move Complete [%d]"), iUseStep);
			//errMsg2(Task.AutoFlag,logStr);
			iRtnFunction = 39350;
			break;
		}


	case 39350: //UVÀü OC Defect °Ë»ç 
		Sleep(100);
		MIU.func_Set_InspImageCopy(MID_6500K_RAW, MIU.m_pFrameRawBuffer);
		logStr.Format("MID_6500K_RAW SAVE OK [%d]", iUseStep);
		putListLog(logStr);
		Sleep(500);

		LightControlthird.ctrlLedVolume(LIGHT_OC_6500K, 0);
		iRtnFunction = 39400;
		break;

	case 39400:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format(_T("PCB Z axis Defect Pos Move Failed [%d]"), iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -39400;
			break;
		}
		else
		{
			logStr.Format(_T("PCB Z axis Defect Pos Move Complete [%d]"), iUseStep);
			//errMsg2(Task.AutoFlag,logStr);
			iRtnFunction = 39450;
			break;
		}

	case 39450:	//Dark °Ë»ç À§Ä¡ ÀÌµ¿
		iRtnFunction = 39500;
		//if(model.m_IsUseDarkDefectTest == 1)	// ¾Ï¸· Defect Picxel °Ë»ç À¯¹«
		//{
		//	iRtnFunction = 18102;				//¾Ï¸· °Ë»ç À§Ä¡ ÀÌµ¿
		//}
		//else
		//{
		//	iRtnFunction = 18115;				
		//}
		break;

	case 39500:	//Dark °Ë»ç À§Ä¡ ÀÌµ¿
		if (!motor.Pcb_Motor_Move(Dark_Pos, Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]))
		{
			sLangChange.LoadStringA(IDS_STRING1022);	//PCBºÎ ¸ðÅÍ Dark °Ë»ç À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]
			logStr.Format(sLangChange, iUseStep);
			putListLog(logStr);
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = -39500;
		}
		else
		{
			LightControlthird.ctrlLedVolume(LIGHT_OC_6500K, 0);
			LightControlthird.ctrlLedVolume(LIGHT_PCB, 0);
			iRtnFunction = 39600;
		}
		break;

	case 39600:
		if (!motor.PCB_Z_Motor_Move(Dark_Pos))
		{
			logStr.Format(_T("PCB Z axis Dark Pos Move Failed [%d]"), iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -39600;
		}
		else
		{
			logStr.Format(_T("PCB Z axis Dark Pos Move Complete [%d]"), iUseStep);
			//errMsg2(Task.AutoFlag,logStr);
			iRtnFunction = 39620;
		}
		break;

	case 39620:
		Sleep(500);
		MIU.func_Set_InspImageCopy(LOW_LEVEL_RAW, MIU.m_pFrameRawBuffer);
		logStr.Format("LOW_LEVEL_RAW SAVE OK [%d]", iUseStep);
		putListLog(logStr);
		iRtnFunction = 39650;
		break;
	case 39650:
		if (g_clApsInsp.func_Insp_Defect(MIU.vDefectMidBuffer_6500K, MIU.vDefectLowBuffer, false) == false)
		{
			logStr.Format("[AUTO] Defect °Ë»ç ½ÇÆÐ [%d]", iUseStep);
			MandoInspLog.bInspRes = false;
		}

		logStr.Format("[AUTO] Defect °Ë»ç ¿Ï·á [%d]", iUseStep);
		putListLog(logStr);
		iRtnFunction = 39700;
		break;

	case 39700:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format(_T("PCB Z axis Wait Pos Move Failed [%d]"), iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -39700;
		}
		else
		{
			iRtnFunction = 39850;
		}
		break;
	case 39850:
		iRtnFunction = 39900;
		Task.PCBTaskTime = myTimer(true);
		break;
	case 39900: // º»µù À§Ä¡ ÀÌµ¿
		iRtnFunction = 39999;
		break;
	case 39999:			//¿©±â±îÁö¿È 180706_1
						//if( func_MIU_ConnectLiveCheck() == false)		//MIU ¿µ»ó Check
						//{
						//	iRtnFunction = -39999;
						//	break;
						//}
#if (____AA_WAY == PCB_TILT_AA)
		iRtnFunction = 41000;
#elif (____AA_WAY == LENS_TILT_AA)
		iRtnFunction = 40000;
#endif		
		break;
	default:
		logStr.Format("Pcb Align µ¿ÀÛ Thread Step ¹øÈ£ ºñÁ¤»ó . [%d]", iUseStep);
		errMsg2(Task.AutoFlag, logStr);
		iRtnFunction = -1;
		break;
	}
	logStr.Empty();
	return iRtnFunction;
}

int CPcbProcess1::RunProc_Bonding_Pos_GO(int iUseStep)
{
	int iRtnFunction = iUseStep;
	int iRtn = 0;
	CString logStr = "";
	double	dFinalDelay = (double)(model.strInfo_Cam[3].m_iDelayTime);
	bool bChk = true;
	double offsetX = 0.0, offsetY = 0.0, offsetTh = 0.0;

	switch (iUseStep)
	{
	case 41000:
		if (sysData.m_iIrChartUse == 1)
		{
			IrvAlignLed.Irv_Light_SetValue(model.m_iLedValue[LEDDATA_TOP1_CHART], IR_CHART);
		}
		else
		{

		}
		

		iRtnFunction = 41050;
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
		
		iRtnFunction = 41150;
		break;
	case 41150: // º»µù À§Ä¡ ÀÌµ¿
		Task.PCBTaskTime = myTimer(true);
		iRtnFunction = 41200;
		break;
	case 41200:
		if (motor.Lens_Motor_MoveXY(0, Bonding_Pos))
		{
#if (____AA_WAY == LENS_TILT_AA)
			if (!motor.Lens_Tilt_Motor_Move(Bonding_Pos))
			{
				logStr.Format("Lens %s Tx,TyÀÌµ¿ ½ÇÆÐ", MotorPosName[Bonding_Pos]);
				delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
				iRtnFunction = -41200;
				break;
			}

#endif
			logStr.Format("Lens Bonding À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]", iRtnFunction);
			putListLog(logStr);
			Task.interlockPcb = 1;
			iRtnFunction = 41250;
		}
		else
		{
			logStr.Format("Lens Bonding À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -41200;
			break;
		}
		break;
	case 41250:
#if (____AA_WAY == PCB_TILT_AA)
		if (motor.Pcb_Motor_Move(Bonding_Pos, Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]))
		{
			sLangChange.LoadStringA(IDS_STRING913);	//"PCB Bonding À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]"
			logStr.Format(sLangChange, iUseStep);
			putListLog(logStr);
			iRtnFunction = 41300;
			if (!motor.Pcb_Tilt_Motor_Move(Bonding_Pos))
			{
				logStr.Format("PCB tx,ty Bonding_Pos ÀÌµ¿ ½ÇÆÐ");
				delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
				iRtnFunction = -41250;
				break;
			}
			break;
		}
		else
		{
			sLangChange.LoadStringA(IDS_STRING912);	//PCB Bonding À§Ä¡ ÀÌµ¿ ½ÇÆÐ
			logStr.Format(sLangChange + _T("[%d]"), iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -41250;
			break;
		}
#elif	(____AA_WAY == LENS_TILT_AA)

		
		if (LGIT_MODEL_INDEX == M1_HEATING_GEN2)
		{
			iRtnFunction = 41300;
			break;
		}
		else
		{
			if (motor.Pcb_Motor_Move(Bonding_Pos, Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]))
			{
				sLangChange.LoadStringA(IDS_STRING913);	//"PCB Bonding À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]"
				logStr.Format(sLangChange, iUseStep);
				putListLog(logStr);
				iRtnFunction = 41300;	//jump
				break;
			}
			else
			{
				sLangChange.LoadStringA(IDS_STRING912);	//PCB Bonding À§Ä¡ ÀÌµ¿ ½ÇÆÐ
				logStr.Format(sLangChange + _T("[%d]"), iUseStep);
				errMsg2(Task.AutoFlag, logStr);
				iRtnFunction = -41250;
				break;
			}
		}
		
#endif
		break;
	case 41300:
		if (sysData.m_iEpoxyLaserInspPass == 1)
		{
			//Laser ÃøÁ¤ Pass
			logStr.Format("Laser º¸Á¤ pass[%d]", iRtnFunction);
			putListLog(logStr);
			if (!motor.Pcb_Tilt_Motor_Move(Bonding_Pos))
			{
				logStr.Format("PCB %s ÀÌµ¿ ½ÇÆÐ", MotorPosName[Bonding_Pos]);
				delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
				iRtnFunction = -41300;
				break;
			}
			iRtnFunction = 41310;
			break;
		}
		else
		{
			if (motor.Pcb_Tilt_Trinity_Move(Task.m_PcbLaserAfterTx, Task.m_PcbLaserAfterTy))	//Laser º¸Á¤ÇÑ °ª
			{
				iRtnFunction = 41310;
			}
			else
			{
				sLangChange.LoadStringA(IDS_STRING912);	//PCB Bonding À§Ä¡ ÀÌµ¿ ½ÇÆÐ
				logStr.Format(sLangChange + _T("[%d]"), iUseStep);
				errMsg2(Task.AutoFlag, logStr);
				iRtnFunction = -41250;
			}
		}
		


		break;
	case 41310:
		if (Task.interlockPcb == 1)		//pcbÆ¿Æ®ÀÏ °æ¿ì  ·»Áî ·¹ÀÌÀú,¾ó¶óÀÎ ÀÛ¾÷ ³¡³­ÈÄ º»µùÀ§Ä¡ ¿Ã¶§±îÁö ±â´Ù·Á¾ßµÅ¼­
		{
			iRtnFunction = 41350;
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > 50000)
		{
			logStr.Format("Lens Bonding À§Ä¡ ÀÌµ¿ ½Ã°£ ÃÊ°ú[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -41310;
		}
		break;
	case 41350:
		theApp.MainDlg->setCamDisplay(3, 1);
		iRtnFunction = 41400;

		break;
	case 41400:
		if (LGIT_MODEL_INDEX != M1_HEATING_GEN2)
		{
			iRtnFunction = 48000;
			break;
		}
		if (motor.Pcb_Motor_Move(Dark_Pos, Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]))
		{
			logStr.Format("PCB Tail X,Y À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = 41500;
		}
		else
		{
			sLangChange.LoadStringA(IDS_STRING912);	//PCB Bonding À§Ä¡ ÀÌµ¿ ½ÇÆÐ
			logStr.Format(sLangChange + _T("[%d]"), iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -41400;
		}

		break;
	case 41500:
		if (!askMsg("ÁøÇà #1?"))
		{
			errMsg2(Task.AutoFlag, "ÀÏ½ÃÁ¤Áö");
			iRtnFunction = -41500;
			break;
		}
		iRtnFunction = 41600;
		break;
	case 41600:
		if (!motor.PCB_Z_Motor_Move(Dark_Pos))
		{
			logStr.Format("PCB ZÃà Tail À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -41600;
			break;
		}
		else
		{
			logStr.Format("PCB ZÃà Tail À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]", iRtnFunction);
			putListLog(logStr);
			iRtnFunction = 41700;
		}

		break;
	case 41700:
		Dio.LensTailGrip(false, false);

		Task.PCBTaskTime = myTimer(true);
		iRtnFunction = 41800;
		break;
	case 41800:
		if (Dio.LensTailGripCheck(false, false) == true)
		{
			logStr.Format("Lens Tail UnGrip È®ÀÎ ¿Ï·á");
			putListLog(logStr);
			iRtnFunction = 41900;
			break;
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > IO_DELAY_TIME)
		{
			logStr.Format("Lens Tail UnGrip È®ÀÎ ½Ã°£ ÃÊ°ú");
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -41700;
			break;
		}

		break;
	case 41900:
		if (!askMsg("ÁøÇà #2?"))
		{
			errMsg2(Task.AutoFlag, "ÀÏ½ÃÁ¤Áö");
			iRtnFunction = -41500;
			break;
		}
		iRtnFunction = 42000;
		break;
	case 42000:
		if (motor.Pcb_Motor_Move(Bonding_Pos, Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]))
		{
			sLangChange.LoadStringA(IDS_STRING913);	//"PCB Bonding À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]"
			logStr.Format(sLangChange, iUseStep);
			putListLog(logStr);
			iRtnFunction = 42100;
		}
		else
		{
			sLangChange.LoadStringA(IDS_STRING912);	//PCB Bonding À§Ä¡ ÀÌµ¿ ½ÇÆÐ
			logStr.Format(sLangChange + _T("[%d]"), iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -42000;
		}

		break;
	case 42100:
		if (!askMsg("ÁøÇà #3?"))
		{
			errMsg2(Task.AutoFlag, "ÀÏ½ÃÁ¤Áö");
			iRtnFunction = -41500;
			break;
		}
		iRtnFunction = 48000;
		break;
	case 48000:
		LightControlthird.ctrlLedVolume(LIGHT_PCB, 0);		// Align¸¸ Á¶¸í ON

		logStr.Format("Loading End[%d]", iUseStep);
		putListLog(logStr);
		iRtnFunction = 49000;
		break;
		//
	default:
		logStr.Format("Pcb Align µ¿ÀÛ Thread Step ¹øÈ£ ºñÁ¤»ó . [%d]", iUseStep);
		errMsg2(Task.AutoFlag, logStr);
		iRtnFunction = -1;
		break;
	}
	logStr.Empty();
	return iRtnFunction;
}

int	CPcbProcess1::procAutoFocus(int iStep)
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
		if (gMIUDevice.bMIUOpen == 0 || gMIUDevice.CurrentState != 4)
		{
			logStr.Format("CCD µ¿¿µ»ó Á¤Áö »óÅÂÀÔ´Ï´Ù.");
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
	
		MbufClear(vision.MilOptImage, 0x00);
		MbufClear(vision.MilDefectImage, 0x00);

		Task.initSFRElem();

		Task.PCBTaskTime = myTimer(true);

		theApp.MainDlg->autodispDlg->dispCurTaskOnLabel(1, "-");

		theApp.MainDlg->autodispDlg->DrawGraph(0);
		theApp.MainDlg->autodispDlg->DrawGraph(1);
		MandoInspLog.bInspRes = true;	//60000 ÃÊ±âÈ­
		Task.m_timeChecker.Measure_Time(6);	//AA ½ÃÀÛ ½Ã°£
		iRtnFunction = 60010;
		break;
	case  60010:
		if (bThreadCCDRun1 == false)		//	CCD ¿µ»ó ¾²·¹µå ¸ØÃß¸é ÁøÇà... step = 12000 Âü°í
		{
			iRtnFunction = 60015;
		}
		else
		{
			logStr.Format("CCD ¿µ»ó Open ÁøÇàÁßÀÔ´Ï´Ù[%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -60010;
		}
		break;
	case  60015:
		if (motor.LENS_Z_Motor_Move(Bonding_Pos))
		{
			logStr.Format("Lens Z Bonding À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]", iStep);
			putListLog(logStr);
			iRtnFunction = 60020;

		}
		else
		{
			logStr.Format("Lens Z Bonding À§Ä¡ ÀÌµ¿ ½ÇÆÐ [%d]", iStep);
			putListLog(logStr);
			iRtnFunction = -60015;
		}
		break;
	case 60020:
		if (!motor.PCB_Z_Motor_Move(Bonding_Pos))
		{
			logStr.Format("PCB ZÃà Bonding À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -60020;
			break;
		}
		else
		{
			iRtnFunction = 60030;
			logStr.Format("PCB ZÃà Bonding À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]", iRtnFunction);
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
			logStr.Format("PCBºÎ x,y º»µù À§Ä¡¿¡ µµ´Þ ¿Ï·á[%d]", iStep);
			putListLog(logStr);
			iRtnFunction = 60040;
			logStr.Format("	AA Step [%d]", iRtnFunction);
			putListLog(logStr);
			break;
		}
		else
		{
			logStr.Format("Bonding À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -60030;
			break;
		}
	}
	break;
	case 60040:		/* PCB Z¸ðÅÍ º»µùÀ§Ä¡ ÀÌµ¿ */
	{
		iRtn = theApp.MainDlg->_checkPcbMotor();
		if (iRtn > 0)
		{
			logStr.Format("Z ¸ðÅÍ º»µù À§Ä¡ ÀÌµ¿");
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
					if (motor.IsStopAxis(Motor_Lens_Z))// && motor.GetInposition(Motor_Lens_Z) )
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
					putListLog("Auto Focusing ñé LENS Z Motor ÀÌµ¿ ½Ã°£ ÃÊ°ú.");
					iRtnFunction = -60040;
					break;
				}
			}
		}
		else
		{
			putListLog("PCB °¡ º»µùÀ§Ä¡¿¡ µµ´ÞÇÏÁö ¸øÇß½À´Ï´Ù.");
			iRtnFunction = -60040;
		}
	}
	break;
	case 60070:		/* SFR °ªÀÌ ¿¬¼ÓÀ¸·Î ÇÏ¶ôÇÒ ¶§, Z¸ðÅÍ ÀÌµ¿ */
	{
		double dCurPos = 0.0;
		double dMovePos = model.axis[theApp.MainDlg->TITLE_MOTOR_Z].pos[Bonding_Pos] + model.m_dMove_Offset_Z;
		//¿¬¼ÓÀ¸·Î ÇÏ¶ô½Ã model.m_dMove_Offset_Z¸¸Å­ zÃàÀ» ¿òÁ÷ÀÎ´Ù 
		if (fabs(model.m_dMove_Offset_Z) > 0.2)
		{
			logStr.Format("zÃà ÀÌµ¿Ä¡ Limit ÃÊ°ú : Z : %.3lf", dMovePos);
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
				putListLog("Auto Focusing ñé Z Motor ÀÌµ¿ ½Ã°£ ÃÊ°ú.");
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

		iRtn = theApp.MainDlg->_moveZMotor(dMoveDist, model.strInfo_AF1.m_dMoveVel);		/* Z¸ðÅÍ Rough ÀÌµ¿ */
		if (iRtn > 0) 
		{
			iRtnFunction = 61000;
			logStr.Format("	AA Step [%d]", iRtnFunction);
			putListLog(logStr);
		}
		else {
			iRtnFunction = -60100;
		}
		Task.PCBTaskTime = myTimer(true);
	}
	break;
	case 60200:
	{
		if (Task.bFirstAA)
		{
			if (sysData.m_i1stAaEbable)	//1Â÷ AAÈÄ Á¾·á½Ã
			{
				iRtn = theApp.MainDlg->_getMTF(SFR_FINAL);

				if (iRtn > 0)
				{
					Task.m_iCnt_Second_AA_Start = Task.m_iCnt_Step_AA_Total;
					Task.m_iDrawBarStep = Task.m_iCnt_Step_AA_Total;
					Task.m_iCnt_Step_AA = 0;

					theApp.MainDlg->autodispDlg->DrawBarGraph();
					//MIU.func_Set_InspImageCopy(CHART_RAW);			//1Â÷ AAÈÄ 
					Task.sfrResult = theApp.MainDlg->func_MTF(MIU.vChartBuffet);		//1Â÷ AAÈÄ Á¾·á
					if (Task.sfrResult)
					{
						logStr.Format("1Â÷ AA °á°ú Spec OK.");
						putListLog(logStr);
						iRtnFunction = 69999;
						logStr.Format("	AA Step [%d]", iRtnFunction);
						putListLog(logStr);
						break;
						////int boxIndex[5] = {SFR_CENTER_UP, MTF_INSP_CNT-8, MTF_INSP_CNT-6, MTF_INSP_CNT-4, MTF_INSP_CNT-2};

						//double maxCornor = Task.SFR._64_fSfrN4[boxIndex[1]];//SFR_LEFT_UP_INDEX
						//double minCornor = Task.SFR._64_fSfrN4[boxIndex[1]];//SFR_LEFT_UP_INDEX

						//for (int i=2; i<5; i++)
						//{
						//	if (maxCornor < Task.SFR._64_fSfrN4[boxIndex[i]])
						//		maxCornor = Task.SFR._64_fSfrN4[boxIndex[i]];
						//	if (minCornor > Task.SFR._64_fSfrN4[boxIndex[i]])
						//		minCornor = Task.SFR._64_fSfrN4[boxIndex[i]];
						//}

						//if( maxCornor-minCornor < sysData.dLimit_SFR_Balance)
						//{
						//	//saveSfrSumLog();//ÃÖÁ¾ Data log ÀúÀå
						//	logStr.Format("1Â÷ AA °á°ú Spec OK.");
						//	putListLog(logStr);
						//	iRtnFunction = 69999;
						//	logStr.Format("	AA Step [%d]" , iRtnFunction);
						//	putListLog(logStr);
						//	break;
						//}
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

		iRtn = theApp.MainDlg->_moveZMotor(dMovePos, model.strInfo_AF1.m_dMoveVel);		/* Z¸ðÅÍ Rough ÀÌµ¿ */

		if (iRtn > 0)
		{
			iRtnFunction = 60900;
			Task.PCBTaskTime = myTimer(true);
		}
		else
		{
			iRtnFunction = -60200;
		}
	}

	break;

	case 60900:			/* ZÃà º»µù À§Ä¡ µµÂø ÈÄ */
	{
		if ((myTimer(true) - Task.PCBTaskTime) > model.strInfo_Cam[CCD].m_iDelayTime)
		{
			iRtnFunction = 60910;
		}
		else
		{
			iRtnFunction = 60900;
		}
	}
	break;

	case 60910:	// AAÀü Lens X/Y, PCB Theta º¸Á¤

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
				if (fabs(Task.m_dShift_IMG_X) <= sysData.m_dOcSpec.x &&fabs(Task.m_dShift_IMG_Y) <= sysData.m_dOcSpec.y)
				{
					logStr.Format("		 ¿µ»ó Shift. Spec(%.03lf, %.03lf) In : X %.3lf, Y %.3lf",
						sysData.m_dOcSpec.x, sysData.m_dOcSpec.y,
						Task.m_dShift_IMG_X, Task.m_dShift_IMG_Y);
					putListLog(logStr);
					iRtnFunction = 62000;
					//Task.ocCheckIng = false; 
					break;
				}
				else
				{
					logStr.Format("		 ¿µ»ó Shift.  X %.3lf, Y %.3lf ,Spec(%.03lf, %.03lf)", Task.m_dShift_IMG_X, Task.m_dShift_IMG_Y, sysData.m_dOcSpec.x, sysData.m_dOcSpec.y);
					putListLog(logStr);
					iRtnFunction = 60920;
					//Task.ocCheckIng = true;
				}
			}
		}
		else
		{
			logStr.Format("SFR ¿µ»ó È¹µæ ½ÇÆÐ.");	//SFR ¿µ»ó È¹µæ ½ÇÆÐ.
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
	{
		if ((myTimer(true) - Task.PCBTaskTime) > iDelayTime)
		{
			iRtnFunction = 62000;
			logStr.Format("	AA Step [%d]", iRtnFunction);
			putListLog(logStr);
		}
	}

	break;

	case 62000:
	{
		iRtn = theApp.MainDlg->_getMTF((Task.bFirstAA == true) ? SFR_FINAL : SFR_FIRST);
		logStr.Format("Step :[%d] SFR [%.03f] [Z %.03f]", Task.m_iCnt_Step_AA, Task.SFR.fSfrN4[Task.m_iCnt_Step_AA][0], motor.GetEncoderPos((theApp.MainDlg->TITLE_MOTOR_Z)));
		putListLog(logStr);
		if (iRtn>0)
		{
			Task.m_iCnt_Step_AA++;		/* Auto Focus rough ÃøÁ¤ È½¼ö Áõ°¡ */

			if (Task.bFirstAA)
			{
				theApp.MainDlg->autodispDlg->DrawGraph(1);		/* Z ¸ðÅÍ À§Ä¡º° SFR µ¥ÀÌÅÍ ±×·¡ÇÁ ±×¸®±â */
			}
			else
			{
				theApp.MainDlg->autodispDlg->DrawGraph(0);		/* Z ¸ðÅÍ À§Ä¡º° SFR µ¥ÀÌÅÍ ±×·¡ÇÁ ±×¸®±â */
			}

			if (!Task.bFirstAA == true)
			{
				if (Task.m_iCnt_Step_AA == model.m_iCnt_Check_SFR)
				{
					iRtnFunction = 63000;
					logStr.Format("	AA Step [%d]", iRtnFunction);
					putListLog(logStr);
				}
				else if (Task.m_bFlag_Decrease_SFR == true && Task.m_iCnt_Step_AA == model.m_iCnt_Check_SFR * 2)
				{
					iRtnFunction = 63000;
					logStr.Format("	AA Step [%d]", iRtnFunction);
					putListLog(logStr);
				}
				else {
					iRtnFunction = 64000;
					logStr.Format("	AA Step [%d]", iRtnFunction);
					putListLog(logStr);
				}
			}
			else {
				iRtnFunction = 64000;
				logStr.Format("	AA Step [%d]", iRtnFunction);
				putListLog(logStr);
			}
			//////////////////////////////////////////////////////////////////////////
		}
		else {
			iRtnFunction = -63000;
		}
	}

	break;

	case 63000:		/* ÃÊ±â 3°³ µ¥ÀÌÅÍ È®ÀÎ ÈÄ °¨¼Ò ÁßÀÌ¸é ZÃà ¸ðÅÍ ÀÌµ¿ */
	{
		iRtn = theApp.MainDlg->_checkDecreaseSFR();
		if (iRtn > 0) {
			iRtnFunction = 64000;
			logStr.Format("	AA Step [%d]", iRtnFunction);
			putListLog(logStr);
		}
		else
		{
			Task.m_bFlag_Decrease_SFR = true;
			theApp.MainDlg->autodispDlg->m_iCur_Index_Through = Task.m_iCnt_Step_AA_Total;

			//autodispDlg->DrawGraph(0);			//------>20180607_1
			//autodispDlg->DrawGraph(1);
			iRtnFunction = 60070;
			logStr.Format("	AA Step [%d]", iRtnFunction);
			putListLog(logStr);
		}
	}
	break;

	case 64000:
	{
		iRtn = 1;
		int iRtn2 = 1;

		iRtn = theApp.MainDlg->_checkMaxSfrPos(0);		/* MAX °ª Ã£±â */

		theApp.MainDlg->ccdDlg->SetAlignData_Tilt(Task.SFR.dTilt_X, Task.SFR.dTilt_Y);

		if (iRtn>0)			// && iRtn2>0)
		{
			//if (!Task.bFirstAA)
			//{  
			//	Task.SFR.dTilt_Y = _calcTiltX();//*model.Tilt_Weight_Pre;//*modelSign;//modelWeight_Pre;
			//	Task.SFR.dTilt_X = _calcTiltY();//*model.Tilt_Weight_Pre;//*modelSign;//modelWeight_Pre;
			//}else
			//{
			//	Task.SFR.dTilt_Y = _calcTiltX();//*model.Tilt_Weight_Post;//*modelSign;//modelWeight_Post;
			//	Task.SFR.dTilt_X = _calcTiltY();//*model.Tilt_Weight_Post;//*modelSign;//modelWeight_Post;
			//} 
			//
#if 0
			if (Task.bFirstAA == false)
			{
				double dCurPos = motor.GetCommandPos(TITLE_MOTOR_Z);
				double setZ = sysData.m_dOffset_Conti_Down_Z;
				if (true)//setZ < 0)
				{
					double dMovePos = setZ + dCurPos;
					logStr.Format("Z CurPos : (%.3f) , Z down : (%.3f)", dMovePos, setZ);
					putListLog(logStr);
					////
					if (fabs(setZ) > 0.5)
					{
						logStr.Format("Z Down Limit :%.3f [0.5]", fabs(setZ));
						putListLog(logStr);
						errMsg2(Task.AutoFlag, logStr);
						iRtnFunction = -64000;
						break;
					}
					motor.MoveAxis(TITLE_MOTOR_Z, ABS, dMovePos, sysData.fMotorSpeed[TITLE_MOTOR_Z], sysData.fMotorAccTime[TITLE_MOTOR_Z]);
					double ep = myTimer(true);
					while (1)
					{
						if (myTimer(true) - ep < 5000)
						{
							if (motor.IsStopAxis(TITLE_MOTOR_Z))// && motor.GetInposition(TITLE_MOTOR_Z))
							{
								dCurPos = motor.GetEncoderPos(TITLE_MOTOR_Z);
								if (fabs(dCurPos - dMovePos) <= 0.003)
								{
									Task.PCBTaskTime = myTimer(true);
									logStr.Format("Z Down À§Ä¡ ÀÌµ¿ ¿Ï·á");
									putListLog(logStr);
									break;
								}
							}
						}
						else
						{
							logStr.Format("Z Down À§Ä¡ ÀÌµ¿ ½Ã°£ ÃÊ°ú");
							putListLog(logStr);
							iRtnFunction = -64000;
							break;
						}
					}
					Sleep(600);
					//------------------------------------------------------------------------
					dCurPos = motor.GetCommandPos(TITLE_MOTOR_Z);
					setZ = sysData.m_dOffset_Conti_Down_Z * -1;
					dMovePos = setZ + dCurPos;
					logStr.Format("Z CurPos 2: (%.3f) , Z down : (%.3f)", dMovePos, setZ);
					putListLog(logStr);
					//end 1
					motor.MoveAxis(TITLE_MOTOR_Z, ABS, dMovePos, sysData.fMotorSpeed[TITLE_MOTOR_Z], sysData.fMotorAccTime[TITLE_MOTOR_Z]);
					ep = myTimer(true);
					while (1)
					{
						if (myTimer(true) - ep < 5000)
						{
							if (motor.IsStopAxis(TITLE_MOTOR_Z))// && motor.GetInposition(TITLE_MOTOR_Z))
							{
								dCurPos = motor.GetEncoderPos(TITLE_MOTOR_Z);
								if (fabs(dCurPos - dMovePos) <= 0.003)
								{
									Task.PCBTaskTime = myTimer(true);
									logStr.Format("Z Down Á¤À§Ä¡ ÀÌµ¿ ¿Ï·á");
									putListLog(logStr);
									break;
								}
							}
						}
						else
						{
							logStr.Format("Z Down Á¤À§Ä¡ ÀÌµ¿ ½Ã°£ ÃÊ°ú");
							putListLog(logStr);
							iRtnFunction = -64000;
							break;
						}
					}
					//end 2
				}
			}
#endif

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

			if (sysData.m_iDicChange == 0)
			{
				Task.SFR.dTilt_X = theApp.MainDlg->_calcTiltX() *  mDixTx;
				Task.SFR.dTilt_Y = theApp.MainDlg->_calcTiltY() *  mDixTy;
			}
			else
			{
				Task.SFR.dTilt_X = theApp.MainDlg->_calcTiltY() *  mDixTy;
				Task.SFR.dTilt_Y = theApp.MainDlg->_calcTiltX() *  mDixTx;
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
				logStr.Format("Tilt º¸Á¤°ª Limit ÃÊ°ú : Tx : %.4f Ty : %.4f", Task.SFR.dTilt_X, Task.SFR.dTilt_Y);
				errMsg2(Task.AutoFlag, logStr);
				iRtnFunction = -64000;
			}
			else
			{
				if (Task.bFirstAA == true)
				{
					//2Â÷
					logStr.Format("	AA Step 2Â÷[%d]", iRtnFunction);
					putListLog(logStr);
				}
				else
				{
					//1Â÷
					logStr.Format("	AA Step 1Â÷[%d]", iRtnFunction);
					putListLog(logStr);
				}
				iRtnFunction = 64200;		/* Focusing ¿Ï·á */
				logStr.Format("	AA Step [%d]", iRtnFunction);
				putListLog(logStr);
			}
		}
		else {
			iRtnFunction = 60100;		/* ´Ù½Ã ÃøÁ¤ */
			logStr.Format("	AA Step [%d]", iRtnFunction);
			putListLog(logStr);
		}

		if (Task.m_iCnt_Step_AA>model.strInfo_AF1.m_iStepCnt + 5)
		{
			logStr.Format("SFR ÃøÁ¤ ÃÖ´ë È½¼ö ÃÊ°ú.");
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -64000;	/* Ä«¿îÆ® ÃÊ°ú½Ã ¿¡·¯ */
		}

		double z_move_dist = fabs(model.axis[theApp.MainDlg->TITLE_MOTOR_Z].pos[Bonding_Pos] - motor.GetCommandPos(theApp.MainDlg->TITLE_MOTOR_Z));

		if (z_move_dist > 1.0)//0.5
		{
			logStr.Format("[SFR ÃøÁ¤] Z ¸ðÅÍ ÇÏ°­ °Å¸® ÃÊ°ú (1.0mm ÀÌ»ó ³»¸± ¼ö ¾ø½À´Ï´Ù.)");
			errMsg2(Task.AutoFlag, logStr);

			iRtnFunction = -64000;
		}
	}
	break;

	case 64200:		/* Trough Focus ÈÄ Center SFR °ª MAX À§Ä¡·Î Z¸ðÅÍ ÀÌµ¿ */
	{
		double dCurPos = 0.0;
		double dMovePos = Task.SFR.dMaxPos[0];//-3.970

											  //////////////////////////////////////////////////////////////////////////////////////////
											  //////////////////////////////////////////////////////////////////////////////////////////

		double z_move_dist = 0.0;
		//PCB Z­sÀÌ ¿ò©ÀÌ¹Ç·Î Tiltº¸Á¤½Ã PCB-Z­sÀÌ ÇÏ±ø Á…¾ßÇÔ.
		//
		//2Â÷ ³Ñ¾î°¡¸é¼­ ZÃà ¶ç¿ì´Â ºÎºÐ
		//Lens´Â ZÃà »ó½Â
		//Pcb´Â ZÃà ÇÏ°­
#if (____AA_WAY == PCB_TILT_AA)
		z_move_dist = fabs(model.axis[theApp.MainDlg->TITLE_MOTOR_Z].pos[Bonding_Pos] - dMovePos) * -1;	//1Â÷ ->2 Â÷ÀÌµ¿
#elif (____AA_WAY == LENS_TILT_AA)
		z_move_dist = fabs(model.axis[theApp.MainDlg->TITLE_MOTOR_Z].pos[Bonding_Pos] - dMovePos) * 1;	//1Â÷ ->2 Â÷ÀÌµ¿
#endif
		if (z_move_dist > 1.0)
		{
			logStr.Format("[SFR ÃøÁ¤] Z ¸ðÅÍ ÇÏ°­ °Å¸® ÃÊ°ú (1.0mm ÀÌ»ó ³»¸± ¼ö ¾ø½À´Ï´Ù.)");
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
						logStr.Format("	AA Step [%d]", iRtnFunction);
						putListLog(logStr);
						Task.PCBTaskTime = myTimer(true);

						break;
					}
				}
			}
			else
			{
				putListLog("Auto Focusing ñé LENS Z Motor ÀÌµ¿ ½Ã°£ ÃÊ°ú.");
				errMsg2(Task.AutoFlag, sLangChange);
				iRtnFunction = -64200;
				break;
			}
		}
	}

	break;


	case 64400:
	{
		iRtn = theApp.MainDlg->_procTiltX();

		if (iRtn>0) {
			iRtnFunction = 64600;
			logStr.Format("	AA Step [%d]", iRtnFunction);
			putListLog(logStr);
		}
		else {
			iRtnFunction = -64400;
		}
	}

	break;

	case 64600:
	{
		iRtn = theApp.MainDlg->_procTiltY();

		if (iRtn>0) {
			iRtnFunction = 64700;
		}
		else {
			iRtnFunction = -64600;
		}
	}

	break;

	case 64700:			/* Tilt º¸Á¤ ÈÄ Delay */
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

	case 65000:			/* Tilt ÈÄ MTF ÃøÁ¤ */
	{
		//Task.bFirstAA=true;
		if (Task.bFirstAA == true)//! Active Alignment 2¹øÂ° ¼öÇà 
		{
			Sleep(200);
			iRtn = theApp.MainDlg->_getMTF(SFR_FINAL);

			Task.m_iDrawBarStep = Task.m_iCnt_Step_AA_Total;
			theApp.MainDlg->autodispDlg->DrawBarGraph();

			if (iRtn > 0)
			{
				if (!theApp.MainDlg->_calcImageAlignment())
				{//-- Align º¸Á¤ Limit(ÀÓÀÇÀÇ °ª »ç¿ëÇÔ...1.0)
					sLangChange.LoadStringA(IDS_STRING605);	//ImageCenter NG.  X : %.3lf Y : %.3lf
					logStr.Format(sLangChange, Task.m_dShift_IMG_X, Task.m_dShift_IMG_Y);
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
							logStr.Format("ImageCenter ¿µ»ó Shift.  X %.3lf, Y %.3lf", Task.m_dShift_IMG_X, Task.m_dShift_IMG_Y);
							putListLog(logStr);
							Sleep(200);
							iRtnFunction = 65500;
							logStr.Format("	AA Step [%d]", iRtnFunction);
							putListLog(logStr);
							break;
						}
						else
						{
							logStr.Format("ImageCenter ¿µ»ó Shift. Spec(%.03lf, %.03lf) In : X %.3lf, Y %.3lf", sysData.m_dOcSpec.x, sysData.m_dOcSpec.y, Task.m_dShift_IMG_X, Task.m_dShift_IMG_Y);
							putListLog(logStr);
						}
					}
				}

				bool bMtfCheck2 = true;
				vision.MilBufferUpdate();
				Sleep(500);
				MIU.func_Set_InspImageCopy(UV_BEFORE_CHART, MIU.m_pFrameRawBuffer);			//AA UV BEFORE
				Task.sfrResult = theApp.MainDlg->func_MTF(MIU.vChartBuffet);				// [AA UV BEFORE] #1 MIU.m_pFrameRawBuffer);// 

				MandoInspLog.func_LogSave_UVBefore();	// UVÀü Log Data ÀúÀå

				theApp.MainDlg->autodispDlg->DrawBarGraph();
				if (!Task.sfrResult)// && bMtfCheck2)
				{
					saveInspImage(AA_NG_IMAGE_SAVE, Task.m_iCnt_Step_AA_Total);
					logStr.Format("UVÀü SFR °Ë»ç NG.  \nAA RETRY ÇÏ½Ã°Ú½À´Ï±î?");//logStr.Format("SFR ÃÖÁ¾ °Ë»ç NG.  \nAA RETRY ÇÏ½Ã°Ú½À´Ï±î?");
					if (askMsg(logStr))
					{
						iRtnFunction = 60000;
						logStr.Format("	AA Step [%d]", iRtnFunction);
						putListLog(logStr);
						break;
					}
				}

				//saveSfrSumLog();//ÃÖÁ¾ Data log ÀúÀå

				double dCurPosX, dCurPosY, dCurPosTH, dCurPosTX, dCurPosTY, dCurPosZ;
				dCurPosX = motor.GetEncoderPos(Motor_PCB_X);
				dCurPosY = motor.GetEncoderPos(Motor_PCB_Y);
				dCurPosTH = motor.GetCommandPos(Motor_PCB_TH);
				dCurPosTX = motor.GetCommandPos(Motor_PCB_Xt);
				dCurPosTY = motor.GetCommandPos(Motor_PCB_Yt);
				dCurPosZ = motor.GetCommandPos(Motor_PCB_Z);
				if (!g_ADOData.func_AATaskToAAPcbMoter(Task.ChipID, dCurPosX, dCurPosY, dCurPosTH, dCurPosTX, dCurPosTY, dCurPosZ))
				{
					logStr.Format("DataBase »ý¼º ½ÇÆÐ.[%d]\n MS Office¸¦ ´Ý¾ÆÁÖ¼¼¿ä.", iStep);
					errMsg2(Task.AutoFlag, logStr);
					iRtnFunction = -69999;
					break;
				}
				iRtnFunction = 69999;
				logStr.Format("	AA Step [%d]", iRtnFunction);
				putListLog(logStr);
			}
			else
			{
				logStr.Format("SFR ÃÖÁ¾ °Ë»ç ½ÇÆÐ.");
				errMsg2(Task.AutoFlag, logStr);
				iRtnFunction = -65000;
			}
		}
		else
		{//! Active Alignment 1¹øÂ° ¼öÇà
			iRtn = theApp.MainDlg->_getMTF(SFR_FINAL);
			if (iRtn > 0)
			{
				if (!theApp.MainDlg->_calcImageAlignment())	//¿©±â´Ù //¼öµ¿AA
				{//-- Align º¸Á¤ Limit(ÀÓÀÇÀÇ °ª »ç¿ëÇÔ...1.0)
					sLangChange.LoadStringA(IDS_STRING848);	//NG.  X : %.3lf Y : %.3lf
					logStr.Format(sLangChange, Task.m_dShift_IMG_X, Task.m_dShift_IMG_Y);
					putListLog(logStr);

					iRtnFunction = -65000;

					break;
				}
				else
				{
					if (fabs(Task.m_dShift_IMG_X) <= sysData.m_dOcSpec.x &&
						fabs(Task.m_dShift_IMG_Y) <= sysData.m_dOcSpec.y)
					{//X/Y º¸Á¤°ªÀÌ Spec InÀÏ °æ¿ì ´ÙÀ½ Step
						sLangChange.LoadStringA(IDS_STRING1302);	//¿µ»ó Shift. Spec(%.03lf, %.03lf) In : X %.3lf, Y %.3lf
						logStr.Format(_T("		 ") + sLangChange, sysData.m_dOcSpec.x, sysData.m_dOcSpec.y, Task.m_dShift_IMG_X, Task.m_dShift_IMG_Y);
						putListLog(logStr);
						iRtnFunction = 69999;
						logStr.Format("	AA Step [%d]", iRtnFunction);
						putListLog(logStr);
						break;
					}
					else
					{
						sLangChange.LoadStringA(IDS_STRING1301);	//¿µ»ó Shift.  X %.3lf, Y %.3lf
						logStr.Format(_T("		 ") + sLangChange, Task.m_dShift_IMG_X, Task.m_dShift_IMG_Y);
						putListLog(logStr);
						iRtnFunction = 65500;
						logStr.Format("	AA Step [%d]", iRtnFunction);
						putListLog(logStr);
					}
				}
			}
			else
			{
				sLangChange.LoadStringA(IDS_STRING1074);	//SFR ¿µ»ó È¹µæ ½ÇÆÐ.
				errMsg2(Task.AutoFlag, sLangChange);
				iRtnFunction = -65000;
			}
		}
	}

	//iRtnFunction = -65000;
	break;

	case 65500:
		if (!theApp.MainDlg->_MotorMove_IMG_Align()) {
			iRtnFunction = -65500;
		}
		else
		{
			if (Task.iMTFCnt >= 5)
			{
				if (Task.bFirstAA == true) {
					iRtnFunction = 65520;// 65000;
					logStr.Format("	AA Step [%d]", iRtnFunction);
					putListLog(logStr);
					Task.PCBTaskTime = myTimer(true);
				}
				else
				{
					iRtnFunction = 69999;
					logStr.Format("	AA Step [%d]", iRtnFunction);
					putListLog(logStr);
				}
			}
			else
			{
				Task.iMTFCnt++;
				iRtnFunction = 65520;// 65000;
				logStr.Format("	AA Step [%d]", iRtnFunction);
				putListLog(logStr);
				Task.PCBTaskTime = myTimer(true);
			}
		}
		break;

	case 65520:
		if ((myTimer(true) - Task.PCBTaskTime) > iDelayTime)
		{
			iRtnFunction = 65000;
			logStr.Format("	AA Step [%d]", iRtnFunction);
			putListLog(logStr);
		}

		break;

	case 69000:								// ÃÖÁ¾ SFR °Ë»ç °á°ú ÀúÀå..
	{									// SFR °Ë»ç NG ¹ß»ý ½Ã 1È¸ Àç°Ë»ç ÈÄ ¾çºÒ ÆÇÁ¤.
		if (myTimer(true) - Task.PCBTaskTime > model.strInfo_Cam[CCD].m_iDelayTime * 2 || (myTimer(true)<Task.PCBTaskTime))
		{
			iRtn = theApp.MainDlg->_getMTF(SFR_FINAL);		/* MTF°ª È¹µæ */

			Task.m_iDrawBarStep = Task.m_iCnt_Step_AA_Total;
			theApp.MainDlg->autodispDlg->DrawBarGraph();

			if (iRtn>0)
			{
				if (Task.m_b_AA_Retry_Flag == false)
				{
					Task.m_b_AA_Retry_Flag = true;		// TRUEÀÎ °æ¿ì ´ÙÀ½¹ø¿¡´Â °Ë»ç °á°ú NG ½Ã ¾Ë¶÷ ¹ß»ý..
					iRtnFunction = 60000;				// 60000¿¡¼­ 1, 2Â÷ AA °Ë»ç °á°ú ÃÊ±âÈ­..
					logStr.Format("	AA Step [%d]", iRtnFunction);
					putListLog(logStr);
				}
				else
				{
					saveInspImage(AA_NG_IMAGE_SAVE, Task.m_iCnt_Step_AA_Total);
					Dio.setAlarm(ALARM_ON);

					logStr.Format("SFR ÃÖÁ¾ °Ë»ç NG. ÀÚµ¿ ÁøÇà ÇÏ½Ã°Ú½À´Ï±î?");
					if (askMsg(sLangChange))
					{
						Dio.setAlarm(ALARM_OFF);
						logStr.Format("NG ¹èÃâ ÇÏ½Ã°Ú½À´Ï±î. (¿¹:NG, ¾Æ´Ï¿À:OK)");
						if (askMsg(logStr)) {
							Task.m_bOkFlag = 0;
						}
						else {
							Task.m_bOkFlag = 1;
						}
						iRtnFunction = 69999;
						logStr.Format("	AA Step [%d]", iRtnFunction);
						putListLog(logStr);
					}
					else
					{
						Dio.setAlarm(ALARM_OFF);

						//Task.PauseLensStep = abs(Task.LensTask);
						Task.PausePCBStep = abs(Task.PCBTask);
						Task.AutoFlag = 2;		// ÀÏ½ÃÁ¤Áö
						theApp.MainDlg->AutoRunView(Task.AutoFlag);
						iRtnFunction = -65000;
					}
				}
			}
			else
			{
				logStr.Format("SFR ÃÖÁ¾ °Ë»ç (2Â÷) ½ÇÆÐ.");
				errMsg2(Task.AutoFlag, sLangChange);
				iRtnFunction = -65000;
			}
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
			logStr.Format("DataBase »ý¼º ½ÇÆÐ.[%d]\n MS Office¸¦ ´Ý¾ÆÁÖ¼¼¿ä.", iStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -69999;
			break;
		}
		if (Task.bFirstAA == true)
		{
			Task.m_timeChecker.Measure_Time(7);	//AA ¿Ï·á ½Ã°£
			Task.m_dTime_FineAA = Task.m_timeChecker.m_adTime[5] - Task.m_timeChecker.m_adTime[4];
			theApp.MainDlg->dispGrid();

			iRtnFunction = 110000;
			logStr.Format("	AA Step [%d]", iRtnFunction);
			putListLog(logStr);
		}
		else
		{
			//procOptical AlingÀ¸·Î...
			//Task.m_timeChecker.Measure_Time(4);
			//Task.m_dTime_ThroughAA = Task.m_timeChecker.m_adTime[4] - Task.m_timeChecker.m_adTime[3];

			iRtnFunction = 80000;
			logStr.Format("	AA Step [%d]", iRtnFunction);
			putListLog(logStr);
		}
	}

	break;
	}
	logStr.Empty();
	return iRtnFunction;
}

int CPcbProcess1::UV_process(int iStep)
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

		iRtnFunction = 110500;
		break;

	case 110500:
		if (theApp.MainDlg->Bonding_Pos_Ckeck())
		{
			sLog.Format("AA after PCB Z : %f , set Offset Z : %f", motor.GetCommandPos(theApp.MainDlg->TITLE_MOTOR_Z), sysData.m_dOffset_Prev_UV_Z);	//AAÈÄ Lens Z : %f , ¼³Á¤ Offset Z : %f
			putListLog(sLog);

			theApp.MainDlg->MoveOffset_Prev_UV();	/* PCB X, Y, Z, Tx, Ty, PCB Th UV Àü offset ÀÌµ¿ */

			Sleep(200);
			if (motor.IsStopAxis(theApp.MainDlg->TITLE_MOTOR_Z))// && motor.GetInposition(TITLE_MOTOR_Z))
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

	case 110600:									// 20140612 À©ÅØ Ãß°¡.. UV °æÈ­ Àü SFR ÃøÁ¤.
	{

		//	sLangChange.LoadStringA(IDS_STRING864);	//Offset Z Àû¿ë ÈÄ Lens Z : %f
		//sLog.Format(sLangChange, motor.GetEncoderPos(Motor_Lens_Z));
		//putListLog(sLog);
		Sleep(200);
		saveSfrLog(SFR_OFFSET_DATA);
		theApp.MainDlg->_getMTF(SFR_AFTER_OFFSET_MOVE);
		//saveSfrLog(SFR_OFFSET_DATA);
		iRtnFunction = 110650;
		Task.PCBTaskTime = myTimer(true);
	}
	break;

	case 110650:					//UVÀü MTF °Ë»ç ÁøÇà
	{
		Task.bInsCenter = true;

		theApp.MainDlg->_calcImageAlignment();
		Task.bInsCenter = false;

		iRtnFunction = 110700;

	}
	break;


	case 110700:	// Lens Z  UV Àü offset ÀÌµ¿ 
					// 20150730 HJH Offset Áßº¹ Àû¿ëÀ¸·Î Á¦°Å
					//		MoveOffset_Z();	/* Lens Z  UV Àü offset ÀÌµ¿ */

		iRtnFunction = 111000;
		Task.PCBTaskTime = myTimer(true);
		break;

	case 111000:	// UV °æÈ­
	{
		sLangChange.LoadStringA(IDS_STRING1122);
		theApp.MainDlg->autodispDlg->dispCurTaskOnLabel(1, sLangChange);

		Task.PCBTaskTime = myTimer(true);
		//Task.m_timeChecker.Measure_Time(9);

		if (sysData.m_iUVPass == 1)
		{
			sLog.Format("====UV Pass [%d]====", iStep);
			putListLog(sLog);
			iRtnFunction = 113500;
			break;
		}
		UVCommand.UV_Shutter_Open();
		if (sysData.nUvIndex == 1)
		{
			Sleep(100);
			UVCommand2.UV_Shutter_Open();
		}
		Sleep(10);

		sLog.Format("===> UV ON");
		putListLog(sLog);
		Sleep(model.UV_Time);

		UVCommand.UV_Shutter_Close();
		if (sysData.nUvIndex == 1)
		{
			Sleep(100);
			UVCommand2.UV_Shutter_Close();
		}
		sLog.Format("===> UV OFF [%d]", iStep);

		putListLog(sLog);
		iRtnFunction = 113500;
	}
	break;

	case 113500:
		sLangChange.LoadStringA(IDS_STRING1124);
		theApp.MainDlg->autodispDlg->dispCurTaskOnLabel(1, sLangChange);//"UV °æÈ­ ¿Ï·á"

		Task.m_timeChecker.Measure_Time(8);	//UV ¿Ï·á ½Ã°£
		Task.m_dTime_UV = Task.m_timeChecker.m_adTime[8] - Task.m_timeChecker.m_adTime[7];


		if (myTimer(true) - Task.PCBTaskTime> 100)  // Delay Ã¼Å©
		{
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 115000;
		}
		break;

	case 115000:
		curMotorDist[0] = fabs(motor.GetEncoderPos(Motor_Lens_X) - model.axis[Motor_Lens_X].pos[Bonding_Pos]);
		curMotorDist[1] = fabs(motor.GetEncoderPos(Motor_Lens_Y) - model.axis[Motor_Lens_Y].pos[Bonding_Pos]);
		curMotorDist[2] = fabs(motor.GetCommandPos(Motor_Lens_Z) - model.axis[Motor_Lens_Z].pos[Bonding_Pos]);

		if ((curMotorDist[0]<model.axis[Motor_Lens_X].m_dLimit_Err && curMotorDist[1]<model.axis[Motor_Lens_Y].m_dLimit_Err && curMotorDist[2]<model.axis[Motor_Lens_Z].m_dLimit_Err))
		{
			Task.PcbOnStage = 200;			// °Ë»ç ¿Ï·á.

			iRtnFunction = 115300;

			//if(!Dio.HolderGrip(false, true))				//Lens Gripper open
			//{
			//	sLog.Format("Lens Grip Open ½ÇÆÐ [%d]", iStep);
			//	errMsg2(Task.AutoFlag, sLog);
			//	iRtnFunction = -115000;
			//}
			//else
			//{
			//	Task.m_bOKLensPass = -1;//¸ÞÀÎ ³Ñ±è ¿Ï·á Lamp Ãë¼Ò
			//	Task.PCBTaskTime = myTimer(true);
			//	iRtnFunction = 115300;
			//}

		}

		break;

	case 115300:
		if (!Dio.LensMotorGrip(false, true))
		{

			sLog.Format("Lens Unit Gripper ÇØÁ¦ ½ÇÆÐ[%d]", iStep);
			putListLog(sLog);
			iRtnFunction = -115300;
			break;
		}
		Task.m_bOKLensPass = -1;//¸ÞÀÎ ³Ñ±è ¿Ï·á Lamp Ãë¼Ò
		Task.m_iFineThCnt = 0;
#if (____AA_WAY == PCB_TILT_AA)
		iRtnFunction = 115400;
#elif (____AA_WAY == LENS_TILT_AA)
		iRtnFunction = 115500;
#endif
		break;
	case 115400:
		iRtnFunction = 115450;
		/*if(Dio.CamLaserSlinderMove(false, true))
		{
		iRtnFunction = 115450;
		}
		else
		{
		sLog.Format("Laser/Cam ½Ç¸°´õ ÈÄÁø ½ÇÆÐ[%d]", iStep);
		errMsg2(Task.AutoFlag,sLog);
		iRtnFunction = -115400;
		}*/
		break;
	case 115450:
		iRtnFunction = 115500;
		//if(Dio.CamLaserSlinderCheck(false, false))
		//{
		//	sLog.Format("Laser/Cam ½Ç¸°´õ ÈÄÁø ¿Ï·á[%d]", iStep);
		//	putListLog(sLog);
		//	iRtnFunction = 115500;
		//}
		//else if((myTimer(true) - Task.PCBTaskTime) > 10000)//IO_DELAY_TIME)
		//{
		//	sLog.Format("Laser/Cam ½Ç¸°´õ ÀüÁø ½Ã°£ ÃÊ°ú[%d]", iStep);
		//	errMsg2(Task.AutoFlag,sLog);
		//	iRtnFunction = -115450;
		//}
		break;
	case 115500: //UV¿Ï·áÈÄ ÃÖÁ¾°Ë»ç
		Task.m_bOkFlag = 0;
		work.m_iCnt_Output++;
		work.Save();
		iRtnFunction = 120000;
		theApp.MainDlg->_getMTF(SFR_AFTER_UV);
		break;


	default:
		sLangChange.LoadStringA(IDS_STRING1120);	//UV Process Step ¹øÈ£°¡ ºñÁ¤»óÀÔ´Ï´Ù.
		sLog.Format(sLangChange + _T(" [%d]"), iStep);
		errMsg2(Task.AutoFlag, sLog);
		break;
	}
	sLog.Empty();
	sImgPath.Empty();
	return iRtnFunction;
}

int	CPcbProcess1::func_MandoFinalSFR(int iStep)
{
	CString sLog = _T("");

	double	dFinalDelay = (double)(model.strInfo_Cam[3].m_iDelayTime);
	double offsetX = 0.0;
	double offsetY = 0.0;
	double offsetTh = 0.0;
	int iRtn = 0;
	int iRtnFunction = iStep;
	bool bUseDispense = true;	//µµÆ÷ Pass ¿©ºÎ

	if ((sysData.m_iDispensePass == 1))
	{
		bUseDispense = false;//µµÆ÷ Pass Mode ÀÌ°Å³ª, µµÆ÷ ¿Ï·á ÀÏ °æ¿ì
	}
	else
	{
		bUseDispense = true;
	}

	switch (iStep)
	{
	case 120000:

		iRtnFunction = 121000;
		break;

	case 121000:

		iRtnFunction = 122000;
		break;
	case 122000:	//¿ÏÁ¦Ç° °Ë»ç¸¸ ÇØ´ç (Final °Ë»çÀü X/Y/T º¸Á¤)
		Sleep(dFinalDelay);
		iRtn = theApp.MainDlg->_getMTF(SFR_FINAL);
		if (iRtn > 0)
		{
			if (!theApp.MainDlg->_calcImageAlignment())	//-- Align º¸Á¤ Limit(ÀÓÀÇÀÇ °ª »ç¿ëÇÔ...1.0)
			{
				sLog.Format("NG.  X : %.3lf Y : %.3lf", Task.m_dShift_IMG_X, Task.m_dShift_IMG_Y);
				putListLog(sLog);
				iRtnFunction = -122000;
				break;
			}
			else
			{
				//Æ¿ÆÃ°ª ¾È¸ÂÀ» °æ¿ì °ªÀÌ µ¿ÀÏÇÏ°Ô ¹Ýº¹µÊ.. 3È¸ Á¤µµ¸¸ ÇÏ°í ¾È¸ÂÀ¸¸é Spec IN ½ÃÅ°±â..,
				if (Task.m_iFineThCnt > 5)	Task.m_dShift_IMG_TH = 0.0;
				if (fabs(Task.m_dShift_IMG_TH) <= sysData.dSpec_OC_Theta)//X/Y º¸Á¤°ªÀÌ Spec InÀÏ °æ¿ì ´ÙÀ½ Step
				{
					sLog.Format("	¿µ»ó Shift. Spec In(%.03lf) In : T: %.3lf", sysData.dSpec_OC_Theta, Task.m_dShift_IMG_TH);
					putListLog(sLog);
					iRtnFunction = 122500;
				}
				else
				{
					sLog.Format("	¿µ»ó Shift(Spec : %.03lf).  T: %.3lf", sysData.dSpec_OC_Theta, Task.m_dShift_IMG_TH);
					putListLog(sLog);
					if (bUseDispense == false) //AAB, µµÆ÷ ¹Ì»ç¿ëÀÏ °æ¿ì->¿µ»ó Shift¾ÈÇÏ°í ÁøÇà
					{
						iRtnFunction = 122500;
					}
					else//¿µ»ó Shift ÁøÇà
					{
						Task.m_iFineThCnt++;
						iRtnFunction = 122100;
					}
				}
			}
		}
		else
		{
			if (askMsg("ÁøÇà?") == IDOK)
			{
				iRtnFunction = 122500;
				break;
			}
			else
			{
				errMsg2(Task.AutoFlag, "MTF ÃøÁ¤ Àü SFR ¿µ»ó È¹µæ ½ÇÆÐ..");
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
	case 122500:	//Final Àç °Ë»ç - È®ÀÎ¿ë
		theApp.MainDlg->setCamDisplay(3, 1);

		Sleep(dFinalDelay);
		MIU.func_Set_InspImageCopy(UV_AFTER_CHART, MIU.m_pFrameRawBuffer);		//AA UV AFTER
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
			putListLog("[°Ë»ç] MTF °Ë»ç ¼º°ø.");// Optic_Axis,
		}
		else
		{
			putListLog("[°Ë»ç] MTF °Ë»ç ½ÇÆÐ.");// Optic_Axis,
		}
		Task.m_iDrawBarStep = Task.m_iCnt_Step_AA_Total;
		theApp.MainDlg->autodispDlg->DrawBarGraph();
		iRtnFunction = 122550;

		break;
	case 122550:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			sLangChange.LoadStringA(IDS_STRING305);	//PCBºÎ zÃà ¸ðÅÍ À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]
			sLog.Format(sLangChange, iStep);
			putListLog(sLog);
			iRtnFunction = -122550;
			break;
		}

		if (!motor.LENS_Z_Motor_Move(Wait_Pos))
		{
			sLangChange.LoadStringA(IDS_STRING747);	//LensºÎ zÃà ¸ðÅÍ À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]
			sLog.Format(sLangChange, iStep);
			putListLog(sLog);
			iRtnFunction = -122550;
		}



		iRtnFunction = 122700;
		break;
	case 122700:
		Task.LensTaskTime = myTimer(true);
		Task.m_iRetry_Opt = 0;
		iRtnFunction = 122800;
		break;
	case 122800:
		if (sysData.m_iDefectInspPass == 1)	// ÀÌ¹°°Ë»ç À¯¹«
		{
			sLog.Format(_T("[PASS] Defect Insp"), iStep);
			putListLog(sLog);
			iRtnFunction = 123000;
		}
		else
		{
			//iRtnFunction = 122850;
		}
		break;
	case 122850:
		/*if (!motor.Pcb_Motor_Move(Dark_Pos))
		{
			sLog.Format("PCBºÎ Dark À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iStep);
			putListLog(sLog);
			iRtnFunction = -122850;
		}
		else
		{
			sLog.Format("PCBºÎ Dark À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]", iStep);
			putListLog(sLog);
			iRtnFunction = 122900;
		}*/

		break;
	case 122900:
		/*if (!motor.PCB_Z_Motor_Move(Dark_Pos))
		{
			sLog.Format("PCBºÎ Dark Z À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iStep);
			putListLog(sLog);
			iRtnFunction = -122900;
			break;
		}*/
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
		Sleep(100);
		if (motor.IsStopAxis(Motor_PCB_Z))
		{
			MIU.func_Set_InspImageCopy(LOW_LEVEL_RAW, MIU.m_pFrameRawBuffer);
			iRtnFunction = 122970;
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > 10000)
		{
			sLog.Format("PCB Z DAR Á¤ÁöÈ®ÀÎ ½Ã°£ ÃÊ°ú[%d]", iStep);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -122900;
		}

		break;
	case 122970:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			sLangChange.LoadStringA(IDS_STRING305);	//PCBºÎ zÃà ¸ðÅÍ À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]
			sLog.Format(sLangChange, iStep);
			putListLog(sLog);
			iRtnFunction = -122970;
			break;
		}
		iRtnFunction = 123000;
		break;
	case 123000:
		if (sysData.m_iDefectInspPass == 1 && sysData.m_iStaintInspPass == 1)
		{
			iRtnFunction = 124500;
			break;
		}
		if (sysData.m_iIrChartUse == 1)
		{
			IrvAlignLed.Irv_Light_SetValue(model.m_iLedValue[LEDDATA_6500K], IR_OC);
		}
		else
		{
#ifdef FURONTEER_OC
			OCControl.SendLightLxStep(model.m_iLedValue[LEDDATA_6500K]);
#else
			LightControlthird.ctrlLedVolume(LIGHT_OC_6500K, model.m_iLedValue[LEDDATA_6500K]);
#endif

		}
		iRtnFunction = 123050;

		break;
	case 123050:
		if (!motor.Pcb_Motor_Move(OC_6500K_Pos, Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]))
		{
			sLangChange.LoadStringA(IDS_STRING1023);	//PCBºÎ ¸ðÅÍ Defect °Ë»ç À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]
			sLog.Format(sLangChange, iStep);
			putListLog(sLog);
			iRtnFunction = -123050;
		}
		else
		{
			iRtnFunction = 123100;
		}
		break;
	case 123100:
		if (motor.PCB_Z_Motor_Move(OC_6500K_Pos))
		{
			sLog.Format("PCB Z Axis OC 6500K Pos Move Complete[%d]", iStep);
			putListLog(sLog);
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 123200;
		}
		else
		{
			sLog.Format("PCB Z Axis OC 6500K Pos Move Fail[%d]", iStep);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -123100;
		}
		break;
	case 123200:
		if ((myTimer(true) - Task.PCBTaskTime) > 500)
		{
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 123400;
		}
		break;
	case 123400:
		if (motor.IsStopAxis(Motor_PCB_Z))
		{
			Sleep(100);
			MIU.func_Set_InspImageCopy(MID_6500K_RAW, MIU.m_pFrameRawBuffer);
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 124000;
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > 10000)
		{
			sLog.Format("PCB Z 6500K Á¤ÁöÈ®ÀÎ ½Ã°£ ÃÊ°ú[%d]", iStep);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -123100;
		}
		break;
	case 124000:
		Sleep(dFinalDelay);
		if (sysData.m_iDefectInspPass == 1)	// ÀÌ¹°°Ë»ç À¯¹«
		{
			sLog.Format(_T("[PASS] Defect Insp"), iStep);
			putListLog(sLog);
		}
		else
		{
			if (g_clApsInsp.func_Insp_Defect(MIU.vDefectMidBuffer_6500K, MIU.vDefectLowBuffer, true) == true)	//AA
			{
				putListLog("[°Ë»ç] Defect °Ë»ç ¼º°ø.");
			}
			else
			{
				sLog.Format("[°Ë»ç] Defect °Ë»ç  Error[%d]", iStep);
				putListLog(sLog);
				MandoInspLog.bInspRes = false;
			}
		}
		if (sysData.m_iStaintInspPass == 1)	// ÀÌ¹°°Ë»ç À¯¹«
		{
			sLog.Format(_T("[PASS] Stain Insp"), iStep);
			putListLog(sLog);

		}
		else
		{
			if (g_clApsInsp.func_Insp_Stain(MIU.vDefectMidBuffer_6500K) == true)
			{
				putListLog("[°Ë»ç] Stain °Ë»ç ¼º°ø.");
			}
			else
			{
				sLog.Format("[°Ë»ç] Stain °Ë»ç  Error[%d]", iStep);
				putListLog(sLog);
				MandoInspLog.bInspRes = false;
			}
		}

		iRtnFunction = 124500;
		break;
	case 124500:

		if (MIU.Close())//if(MIU.Stop())
		{
			iRtnFunction = 125000;
		}
		else
		{
			iRtnFunction = 124500;

			if (Task.m_iRetry_Opt>3)
			{
				sLog.Format("CCD ¿µ»ó Close ½ÇÆÐ [%d]", iStep);	//CCD ¿µ»ó Close ½ÇÆÐ[%d]
				errMsg2(Task.AutoFlag, sLog);
				iRtnFunction = -124500;
			}
			else {
				Task.m_iRetry_Opt++;
			}
		}
		break;
	case 125000:
		if (motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			sLog.Format("PCB ZÃà ´ë±â À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]", iStep);
			putListLog(sLog);
			iRtnFunction = 127000;
		}
		else
		{
			sLog.Format("PCB ZÃà ´ë±â À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iStep);
			sLog.Format(sLangChange, iStep);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -125000;
		}
		break;
	case 127000:
		//MIU.m_acsInspImage.Unlock();
		Task.m_iRetry_Opt = 0;
		MandoInspLog.func_LogSave_UVAfter();	//¸¸µµ Â÷·®¿ëCamera °Ë»ç Log ÀúÀå(°Ë»ç/º¸Á¤·® ÀúÀå -> ÃÖÁ¾Log)
												/*inspMES();
												MESCommunication.Messave();*/
												//! °Ë»ç Count Ã³¸®
		work.iInspCnt_Output++;
		if (MandoInspLog.bInspRes == false)	work.iInspCnt_NG_Output++;
		theApp.MainDlg->dispInspResGrid();
		work.Save();
		work.Load();

		Task.m_timeChecker.Measure_Time(13);	//Final °Ë»ç ¿Ï·á ½Ã°£
		Task.m_dTime_TotalAA = Task.m_timeChecker.m_adTime[13] - Task.m_timeChecker.m_adTime[12];
		theApp.MainDlg->dispGrid();

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
			MandoInspLog.func_DrawNG_Overlay(CCD);	//È­¸é Overlay¿¡ NG List Draw
			work.m_iCnt_NG_Output++;
		}
		vision.drawOverlay(CCD, true);

		//ccd¿µ»ó ÀüÈ¯

		theApp.MainDlg->ctrlSubDlg(MAIN_DLG);
		theApp.MainDlg->setCamDisplay(3, 1);
		theApp.MainDlg->changeMainBtnColor(MAIN_DLG);
		iRtnFunction = 127400;
		break;

	case 127400:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			sLog.Format("PCB ZÃà ´ë±â À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iStep);
			putListLog(sLog);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -127400;
			break;
		}
		iRtnFunction = 127500;
		break;
	case 127500:
		if (motor.Pcb_Motor_Move(Wait_Pos))
		{
			sLangChange.LoadStringA(IDS_STRING987);	//PCB ´ë±â À§Ä¡ ÀÌµ¿ ¿Ï·á [%d]
			sLog.Format(sLangChange, iStep);
			putListLog(sLog);
			iRtnFunction = 127900;
		}
		else
		{
			sLangChange.LoadStringA(IDS_STRING986);	//PCB ´ë±â À§Ä¡ ÀÌµ¿ ½ÇÆÐ [%d]
			sLog.Format(sLangChange, iStep);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -127500;
		}
		break;
	case 127900:

		//////Dio.PcbGrip(false, false);   //¾ðÁ¦»ç¿ë?

		iRtnFunction = 128000;
		break;
	case 128000:
		if (!motor.Lens_Motor_MoveXY(0, Wait_Pos))
		{
			sLangChange.LoadStringA(IDS_STRING748);	//LensºÎ ¸ðÅÍ ´ë±â À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]
			sLog.Format(sLangChange, iStep);
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
		if (motor.Lens_Tilt_Motor_Move(Wait_Pos))
		{
			iRtnFunction = 128500;
		}
		else
		{
			sLangChange.LoadStringA(IDS_STRING745);	//LENSºÎ Tx, TyÃà ´ë±â À§Ä¡ ÀÌµ¿ ½ÇÆÐ
			sLog.Format(sLangChange);
			putListLog(sLog);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -128200;
		}
		break;
	case 128500:
		if (motor.Pcb_Tilt_Motor_Move(Wait_Pos))
		{
			sLog.Format("PCB TX,TY ´ë±â À§Ä¡ ÀÌµ¿ ¿Ï·á [%d]", iStep);
			putListLog(sLog);
			iRtnFunction = 129000;
		}
		else
		{
			sLog.Format("PCB TX,TY ´ë±âÀ§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iStep);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -128500;
		}
		break;
	case 129000:
		iRtnFunction = 129500;
		break;
	case 129500:
		Task.m_bOkDispense = -1;	//¸ÞÀÎ µµÆ÷ ¿Ï·á Lamp Ãë¼Ò
		putListLog("		");
		putListLog("		");
		sLog.Format("			END =======%s", Task.ChipID);
		putListLog(sLog);
		putListLog("		");
		putListLog("		");
		putListLog("		");
		putListLog("		");
		Task.m_bPBStart = 0;	//¹ÙÄÚµå Á¤º¸ ÃÊ±âÈ­
		if (true)
		{
			memset(Task.ChipID, 0x00, 256);
			sprintf_s(Task.ChipID, "EMPTY");
			theApp.MainDlg->func_ChipID_Draw();
		}

		Task.m_timeChecker.Measure_Time(14);	//¿ÏÁ¦Ç° ¹èÃâ ½Ã°£
		Task.m_dTime_Total = Task.m_timeChecker.m_adTime[14] - Task.m_timeChecker.m_adTime[1];

		theApp.MainDlg->dispGrid();
		theApp.MainDlg->EpoxyTimeCheck(theApp.MainDlg->bEpoxyTimeChk);

		//Dio.PCBvaccumOn(VACCUM_OFF, false);


		//////////////////////////////////////////////////////////////////////////////////////////////////////
		Task.PCBTask = 10000;
		Task.LensTask = 10000;
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

int CPcbProcess1::RunProc_LensNewPassPickup(int iUseStep)
{//! Lens Pickup¿¡ Á¦Ç° ³Ñ±è Step	(15000 ~ 16600)
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
			logStr.Format("Lens_ZÃà ´ëÀ§Ä¡ ÀÌµ¿ ½ÇÆÐ");
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -15000;
			break;
		}

		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("PCB ZÃà ´ë±âÀ§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iUseStep);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -15000;
			break;
		}

		if (Task.m_bOKLensPass != 1)//! Lens ³Ñ±è ¹Ì¿Ï·á ÀÏ °æ¿ì	 
		{
			if (!motor.Pcb_Motor_Move(Loading_Pos, Task.d_Align_offset_x[PCB_Holder_MARK], Task.d_Align_offset_y[PCB_Holder_MARK], 0))
			{
				logStr.Format("PCB %s ÀÌµ¿ ½ÇÆÐ", MotorPosName[Loading_Pos]);
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
			logStr.Format("Lens Unit Gripper ÇØÁ¦ ½ÇÆÐ[%d]", iUseStep);
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

	case 15200: // °ø±Þ
		if (!motor.Lens_Tilt_Motor_Move(Loading_Pos))
		{
			logStr.Format("Lens %s Tx,TyÀÌµ¿ ½ÇÆÐ", MotorPosName[Loading_Pos]);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -15200;
			break;
		}
		if (!motor.Lens_Motor_MoveXY(0, Loading_Pos))
		{
			logStr.Format("Lens %s X,Y ÀÌµ¿ ½ÇÆÐ", MotorPosName[Loading_Pos]);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -15200;
			break;
		}
		logStr.Format("Lens °ø±Þ À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]", iUseStep);
		putListLog(logStr);
		iRtnFunction = 15250;
		break;

	case 15250:
		if (!motor.PCB_Z_Motor_Move(Loading_Pos))
		{
			logStr.Format("PCB loading Z ÀÌµ¿ ½ÇÆÐ");
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
			logStr.Format("Lens Z À§Ä¡ ÀÌµ¿ ½ÇÆÐ [%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -15252;
		}
		break;

	case 15255:
		iRtnFunction = 15300;
		break;
	case 15300: // ¸ðÅÍ ±×¸³
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
			logStr.Format("Lens ±×¸³ ½ÇÆÐ [%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -15300;
		}
		break;

	case 15350://¸ðÅÍ ±×¸³ È®ÀÎ
		if (Dio.LensMotorGripCheck(true, false))
		{
			logStr.Format("Lens ±×¸³ ¿Ï·á[%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = 15400;

			Sleep(800);
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > IO_DELAY_TIME)
		{
			logStr.Format("Lens Gripper ÀüÁø ¼¾¼­ ½Ã°£ ÃÊ°ú..[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -15350;
		}
		break;
	case 15400:
		iRtnFunction = 15450;
		//Sleep(400);	//½Ç¸°´õ »ç¿ëÀ¸·Î PCB Stage UnGrip½Ã ¼¾¼­ °¨Áö ÈÄ, Delay
		/*if(Dio.HolderGrip(false,false))
		{
		Task.PCBTaskTime = myTimer(true);
		iRtnFunction = 15450;
		}
		else
		{
		logStr.Format("Lens Gripper ÇØÁ¦ ½ÇÆÐ..[%d]", iUseStep);
		errMsg2(Task.AutoFlag,logStr);

		iRtnFunction = -15400;
		}*/
		break;

	case 15450:
		iRtnFunction = 15452;
		/*if(Dio.HolderGripCheck(false, false) )
		{
		iRtnFunction = 15452;
		}
		else if((myTimer(true) - Task.PCBTaskTime) > IO_DELAY_TIME)
		{
		logStr.Format("PCB Stage Lens Gripper ÇØÁ¦ ½ÇÆÐ..[%d]", iUseStep);
		errMsg2(Task.AutoFlag,logStr);

		iRtnFunction = -15450;
		}*/
		//Sleep(600);
		break;
	case 15452:

		iRtnFunction = 15455;
		break;

	case 15455:

		iRtnFunction = 15500;
		break;
	case 15500: // ´ë±â À§Ä¡ ÀÌµ¿		//·»Áî ±×¸³»óÅÂ¿¡¼­ ½ÃÀÛÇÏ¸é ÀÌ¸® ¿Â´Ù ¼öÁ¤ÇÏÁö¸¶

		if (!motor.LENS_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("Lens Z ´ë±â À§Ä¡ ÀÌµ¿ ½ÇÆÐ [%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -15500;
		}
		//
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("PCB waiting Z ÀÌµ¿ ½ÇÆÐ");
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -15500;
		}
		iRtnFunction = 15550;
		break;
	case 15550:
		if (motor.Pcb_Motor_Move(Wait_Pos))			//PCBºÎ ¸ðÅÍ ´ë±âÀ§Ä¡ ÀÌµ¿
		{
			iRtnFunction = 15800;
			logStr.Format("Pcb x,y ´ë±â À§Ä¡ ÀÌµ¿ ¿Ï·á [%d]", iUseStep);
			putListLog(logStr);
		}
		else
		{
			logStr.Format("Pcb x,y ´ë±â À§Ä¡ ÀÌµ¿ ½ÇÆÐ [%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = -15550;
		}
		break;
	case 15800:

		Task.LensTask = 30000;	//pcb AAÀÏ¶§ lens ´Â Align ÀÌµ¿ÈÄ laser
		iRtnFunction = 15900;
		logStr.Format("PCB Epoxy Waiting[%d]", iUseStep);
		putListLog(logStr);
		break;
	case 15900:
		//pcb ´Â 
		//lens°¡ Align , laser¸¶Ä¡°í 
		//º»µùÀ§Ä¡·Î ºüÁö±â Àü±îÁö ´ë±â À§Ä¡·Î°¡¼­ ´ë±âÇØ¾ßµÈ´Ù.

		if (Task.interlockLens == 1)
		{
			Task.interlockLens = 0;
			iRtnFunction = 26000;
		}
		break;
	default:
		logStr.Format("Lens °ø±Þ µ¿ÀÛ Thread Step ¹øÈ£ ºñÁ¤»ó . [%d]", iUseStep);
		errMsg2(Task.AutoFlag, logStr);
		iRtnFunction = -1;
		break;
	}

	return iRtnFunction;
}

int	CPcbProcess1::RunProc_LensAlign(int iUseStep)			//(35000 ~ 39000)
{
	int iRtnFunction = iUseStep;
	int iRtn = 0;
	CString logStr = "";
	bool bChk = true;
	double offsetX = 0.0, offsetY = 0.0, offsetTh = 0.0;
	int iCamDelay = model.strInfo_Cam[1].m_iDelayTime;	//PCB ¿µ»ó È¹µæ Delay
	int iAlignRetry = model.strInfo_Cam[1].m_iRetryCnt;
	int iLaserDelay = model.strInfo_Cam[0].m_iDelayTime;	//Laser ÃøÁ¤Àü Delay
	switch (iUseStep)
	{
	case 35000:
		checkMessage();
		offsetX = offsetY = offsetTh = 0.0;
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("		PCB ZÃà ´ë±âÀ§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iUseStep);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -35000;
			break;
		}
		iRtnFunction = 35050;
		break;
	case 35050:
		Task.m_iRetry_Opt = 0;
		iRtnFunction = 35100;
		break;

	case 35100:
		Task.m_bOKLensPass = -1;//PCB¾ð·Îµå °úÁ¤¿¡¼­ ³Ñ±è»óÅÂ·Î ¸¸µé¾î³õÀ¸¹Ç·Î ÃÊ±âÈ­.
		Task.d_Align_offset_x[LENS_Align_MARK] = 0;
		Task.d_Align_offset_y[LENS_Align_MARK] = 0;
		Task.d_Align_offset_th[LENS_Align_MARK] = 0;


		if (Task.m_bOKLensPass != 1)//! Lens ³Ñ±è ¹Ì¿Ï·á ÀÏ °æ¿ì	 
		{
			iRtnFunction = 35150;
		}
		else
		{
			logStr.Format("Lens ³Ñ±è ¿Ï·á·Î Lens Align Pass![%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = 35400;
		}
		break;

	case 35150:
		theApp.MainDlg->ctrlSubDlg(MAIN_DLG);
		theApp.MainDlg->m_iCurCamNo = 0;
		//SetDigReference(LENS_Align_MARK);
		LightControlthird.ctrlLedVolume(LIGHT_PCB, model.m_iLedValue[LEDDATA_LENS]);		// Align¸¸ Á¶¸í ON
		if (motor.Pcb_Motor_Move(Lens_Pos))
		{
			if (motor.PCB_Z_Motor_Move(Lens_Pos))
			{
				logStr.Format("PCB Lens_Pos Align À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]", iUseStep);
				putListLog(logStr);
				Task.PCBTaskTime = myTimer(true);

				iRtnFunction = 35200;
			}
		}
		else
		{
			logStr.Format("PCB Sensor Align À§Ä¡ ÀÌµ¿ ½ÇÆÐ [%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -35150;
		}
		break;
	case 35200:
		checkMessage();
		if ((myTimer(true) - Task.PCBTaskTime) > iCamDelay && (motor.IsStopAxis(Motor_PCB_X) && motor.IsStopAxis(Motor_PCB_Y)))
		{
			iRtnFunction = 35250;
		}
		break;

	case 35250:

		if (Task.m_iRetry_Opt>iAlignRetry)
		{
			logStr.Format("PCB Align Àç°Ë»ç %d È¸ ½ÇÆÐ[%d]\n º¸Á¤ ¹ÌÀû¿ëÀ¸·Î ÁøÇàÇÏ½Ã°Ú½À´Ï±î?", Task.m_iRetry_Opt, iUseStep);
			if (askMsg(logStr) == IDOK)
			{
				Task.d_Align_offset_x[LENS_Align_MARK] = 0;
				Task.d_Align_offset_y[LENS_Align_MARK] = 0;
				Task.d_Align_offset_th[LENS_Align_MARK] = 0;
				iRtnFunction = 35400;
			}
			else
			{
				Task.m_iRetry_Opt = 0;
				iRtnFunction = 35250;
				logStr.Format("PCB Lens Align Àç°Ë»ç ½ÃÀÛ[%d]", iUseStep);
				putListLog(logStr);

				//iRtnFunction = -35250;
				//logStr.Format("PCB Align Àç°Ë»ç %d È¸ ½ÇÆÐ[%d]", Task.m_iRetry_Opt, iUseStep);
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
			Task.d_Align_offset_th[LENS_Align_MARK] = 0.0;//offsetTh;

			Task.dPcbAlignTh = Task.d_Align_offset_th[LENS_Align_MARK];

			logStr.Format("PCB Lens Align : %.3lf %.3lf %.3lf", Task.d_Align_offset_x[LENS_Align_MARK], Task.d_Align_offset_y[LENS_Align_MARK], Task.d_Align_offset_th[LENS_Align_MARK]);
			//pcbDlg->m_labelAlignResult.SetText(logStr);
			//pcbDlg->m_labelAlignResult.Invalidate();

			putListLog(logStr);

			int iRtnVal = theApp.MainDlg->AlignLimitCheck(CAM1, offsetX, offsetY, offsetTh);

			if (iRtnVal == 1)
			{
				iRtnFunction = 35300;				// º¸Á¤ ÀÌµ¿
			}
			else if (iRtnVal == 2)
			{
				logStr.Format("		PCB Lens Align [%d] ¿Ï·á [%d]", Task.m_iRetry_Opt, iUseStep);
				putListLog(logStr);
				//InstantMarkDelete(PCB_Chip_MARK);			//ÀÓ½Ã µî·Ï ¸¶Å© »èÁ¦

				logStr.Format("		PCB Lens Align Complete : %d, %.03f, %.03f, %.03f", Task.m_iPcbPickupNo, Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]);
				AlignResultSave(logStr);
				Task.m_iRetry_Opt = 0;

				Task.m_timeChecker.Measure_Time(4);	//Laser º¯À§ ÃøÁ¤ ½ÃÀÛ ½Ã°£

				iRtnFunction = 35400;		// ¿Ï·á
			}
			else
			{
				logStr.Format("PCB Lens Align [%d] º¸Á¤ ¹üÀ§ ÃÊ°ú", Task.m_iRetry_Opt, iUseStep);
				errMsg2(Task.AutoFlag, logStr);
				AlignLogSave(logStr);
				//InstantMarkDelete(PCB_Chip_MARK);
				iRtnFunction = -35250;				// NG
			}
		}
		else
		{
			logStr.Format("PCB Lens Align [%d] ¸¶Å© ÀÎ½Ä ½ÇÆÐ[%d]", Task.m_iRetry_Opt, iUseStep);
			putListLog(logStr);

			iRtnFunction = 35200;				//  Àç°Ë»ç 
			Sleep(300);
		}
		break;

	case 35300://- Sensor Align Retry
		if (motor.Pcb_Holder_Align_Move(Lens_Pos, Task.d_Align_offset_x[LENS_Align_MARK], Task.d_Align_offset_y[LENS_Align_MARK], Task.d_Align_offset_th[LENS_Align_MARK]))
		{
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 35200;
		}
		else
		{
			logStr.Format("PCB Sensor Align º¸Á¤ À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -35300;
		}
		break;
	case 35400:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			sLangChange.LoadStringA(IDS_STRING305);	//PCBºÎ zÃà ¸ðÅÍ À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]
			logStr.Format(sLangChange, iUseStep);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -35400;
			break;
		}
		iRtnFunction = 35500;
		break;
	case 35500://! Lens-ZÃà ´ë±â À§Ä¡ ÀÌµ¿
		iRtnFunction = 39000;
		break;
	default:
		logStr.Format("Lens ¿ÜºÎ Align Thread Step ¹øÈ£ ºñÁ¤»ó [%d]", iUseStep);
		errMsg2(Task.AutoFlag, logStr);
		iRtnFunction = -1;
		break;
	}
	logStr.Empty();
	return iRtnFunction;
}

int CPcbProcess1::RunProc_LensLoading(int iUseStep)
{//! Lens Pickup¿¡ Á¦Ç° ³Ñ±è Step	(15000 ~ 16600)
	int iRtnFunction = iUseStep;
	int iRtn = 0;
	CString logStr = "";
	double	dFinalDelay = (double)(model.strInfo_Cam[3].m_iDelayTime);
	bool bChk = true;
	double offsetX = 0.0, offsetY = 0.0, offsetTh = 0.0;
	//Task.m_bOKLensPass = -1;//PCB¾ð·Îµå °úÁ¤¿¡¼­ ³Ñ±è»óÅÂ·Î ¸¸µé¾î³õÀ¸¹Ç·Î ÃÊ±âÈ­.

	switch (iUseStep)
	{
	case 40000:
		if (!motor.LENS_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("Lens_ZÃà ´ëÀ§Ä¡ ÀÌµ¿ ½ÇÆÐ");
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -40000;
			break;
		}

		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("PCB ZÃà ´ë±âÀ§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iUseStep);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -40000;
			break;
		}

		if (Task.m_bOKLensPass != 1)//! Lens ³Ñ±è ¹Ì¿Ï·á ÀÏ °æ¿ì	 
		{

			Task.d_Align_offset_x[LENS_Align_MARK] = 0.0;
			Task.d_Align_offset_y[LENS_Align_MARK] = 0.0;
			if (!motor.Pcb_Motor_Move(Loading_Pos, Task.d_Align_offset_x[LENS_Align_MARK], Task.d_Align_offset_y[LENS_Align_MARK], 0))
			{
				logStr.Format("PCB %s ÀÌµ¿ ½ÇÆÐ", MotorPosName[Loading_Pos]);
				delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
				iRtnFunction = -40000;
				break;
			}
			//M_TRINITY ¸ðµ¨Àº ·¹ÀÌÀúÈÄ Æ¿Æ® ½ÉÇØ¼­ º»µùÀ§Ä¡°¥¶§ ´Ù½Ã ·¹ÀÌÀú Æ¿Æ®µÈ tx,ty °ªÀ¸·Î ÀÌµ¿ 
			if (!motor.Pcb_Tilt_Motor_Move(Loading_Pos))
			{
				logStr.Format("PCB %s ÀÌµ¿ ½ÇÆÐ", MotorPosName[Loading_Pos]);
				delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
				iRtnFunction = -40000;
				break;
			}
			iRtnFunction = 40100;
		}
		else
		{
			iRtnFunction = 40500;
		}
		break;
	case 40100:
		if (!Dio.LensMotorGrip(false, false))
		{
			logStr.Format("Lens Unit Gripper ÇØÁ¦ ½ÇÆÐ[%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = -40100;
			break;
		}
		if (LGIT_MODEL_INDEX == M1_HEATING_GEN2)
		{
			Dio.LensTailGrip(false, false);
		}
		Task.PCBTaskTime = myTimer(true);
		iRtnFunction = 40150;
		break;

	case 40150:
		if (Dio.LensMotorGripCheck(false, false)) 
		{
			iRtnFunction = 40170;
			Task.PCBTaskTime = myTimer(true);
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > IO_DELAY_TIME)
		{
			logStr.Format("Lens UnGrip È®ÀÎ ½Ã°£ ÃÊ°ú");
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -40150;
			break;
		}
		break;
	case 40170:
		if (LGIT_MODEL_INDEX == M1_HEATING_GEN2)
		{
			if (Dio.LensTailGripCheck(false, false))
			{
				iRtnFunction = 40200;
				Task.PCBTaskTime = myTimer(true);
			}
			else if ((myTimer(true) - Task.PCBTaskTime) > IO_DELAY_TIME)
			{
				logStr.Format("Lens Tail UnGrip È®ÀÎ ½Ã°£ ÃÊ°ú");
				errMsg2(Task.AutoFlag, logStr);
				iRtnFunction = -40170;
				break;
			}
		}

		else
		{
			iRtnFunction = 40200;
		}
		
		break;

	case 40200: // °ø±Þ 
		if (!motor.Lens_Tilt_Motor_Move(Loading_Pos))
		{
			logStr.Format("Lens %s Tx,TyÀÌµ¿ ½ÇÆÐ", MotorPosName[Loading_Pos]);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -40200;
			break;
		}
		if (!motor.Lens_Motor_MoveXY(0, Loading_Pos))
		{
			logStr.Format("Lens %s X,Y ÀÌµ¿ ½ÇÆÐ", MotorPosName[Loading_Pos]);
			delayMsg(logStr.GetBuffer(99), 3000, M_COLOR_RED);
			iRtnFunction = -40200;
			break;
		}

		logStr.Format("Lens °ø±Þ À§Ä¡ X,Y ÀÌµ¿ ¿Ï·á[%d]", iUseStep);
		putListLog(logStr);
		iRtnFunction = 40250;
		break;

	case 40250:
		if (!motor.PCB_Z_Motor_Move(Loading_Pos))
		{
			logStr.Format("PCB loading Z ÀÌµ¿ ½ÇÆÐ");
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -40250;
			break;
		}
		if (!motor.LENS_Z_Motor_Move(Loading_Pos))
		{
			logStr.Format("Lens Z À§Ä¡ ÀÌµ¿ ½ÇÆÐ [%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -40250;
			break;
		}
		iRtnFunction = 40252;
		break;
	case 40252:
		Dio.LensMotorGrip(true, false);
		Sleep(500);
		iRtnFunction = 40255;
		break;

	case 40255:
		Dio.LensMotorGrip(false, false);
		Sleep(300);
		iRtnFunction = 40300;
		break;
	case 40300: // ¸ðÅÍ ±×¸³
		if (Dio.LensMotorGrip(true, false))
		{
			Task.m_bOKLensPass = 1;
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 40350;
		}
		else
		{
			Task.m_bOKLensPass = -1;
			logStr.Format("Lens ±×¸³ ½ÇÆÐ [%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -40300;
		}
		break;

	case 40350://¸ðÅÍ ±×¸³ È®ÀÎ
		if (Dio.LensMotorGripCheck(true, false))
		{
			logStr.Format("Lens ±×¸³ ¿Ï·á[%d]", iUseStep);
			putListLog(logStr);
			iRtnFunction = 40400;
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > IO_DELAY_TIME)
		{
			logStr.Format("Lens Gripper ÀüÁø ¼¾¼­ ½Ã°£ ÃÊ°ú..[%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -40350;
		}
		break;

	case 40400:
		Sleep(500);	//½Ç¸°´õ »ç¿ëÀ¸·Î PCB Stage UnGrip½Ã ¼¾¼­ °¨Áö ÈÄ, Delay 0.2s
		iRtnFunction = 40455;
		break;

	case 40455:
		iRtnFunction = 40500;
		break;
	case 40500: // ´ë±â À§Ä¡ ÀÌµ¿
		if (!motor.LENS_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("Lens Z ´ë±â À§Ä¡ ÀÌµ¿ ½ÇÆÐ [%d]", iUseStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -40500;
			break;
		}
		//
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("PCB waiting Z ÀÌµ¿ ½ÇÆÐ");
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -40500;
			break;
		}
		iRtnFunction = 40550;
		break;
	case 40550:

		iRtnFunction = 40600;
		break;
	case 40600:
		if (LGIT_MODEL_INDEX == M1_HEATING_GEN2)
		{
			Dio.LensTailGrip(true, false);
		}
		Task.PCBTaskTime = myTimer(true);
		iRtnFunction = 40650;
		break;
	case 40650:
		if (LGIT_MODEL_INDEX == M1_HEATING_GEN2)
		{
			if (Dio.LensTailGripCheck(true, false))
			{
				iRtnFunction = 40700;

			}
			else if ((myTimer(true) - Task.PCBTaskTime) > IO_DELAY_TIME)
			{
				logStr.Format("Lens Tail Grip È®ÀÎ ½Ã°£ ÃÊ°ú");
				errMsg2(Task.AutoFlag, logStr);
				iRtnFunction = -40650;
				break;
			}

		}
		else
		{
			iRtnFunction = 40700;
		}
		break;
	case 40700:

		iRtnFunction = 40750;
		break;
	case 40750:

		iRtnFunction = 40900;
		break;
	case 40900:
		iRtnFunction = 41000;
		break;
	default:
		logStr.Format("Lens °ø±Þ µ¿ÀÛ Thread Step ¹øÈ£ ºñÁ¤»ó . [%d]", iUseStep);
		errMsg2(Task.AutoFlag, logStr);
		iRtnFunction = -1;
		break;
	}

	return iRtnFunction;
}

int CPcbProcess1::procProductComplete(int iStep)
{
	CString logStr = "";
	CString sSocketMsg = "";
	CString sBarCode = "";
	//
	int iRtnFunction = iStep;
	int iCamDelay = model.strInfo_Cam[1].m_iDelayTime;	//PCB ¿µ»ó È¹µæ Delay
	int iLaserDelay = model.strInfo_Cam[0].m_iDelayTime;	//Laser ÃøÁ¤Àü Delay
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
	case 11000:	// PCB MIU ¿¬°á	
		Sleep(1000);
		Task.oldLaserTx = 0.1;
		Task.oldLaserTy = 0.1;
		Task.PCBTaskTime = myTimer(true);
		
		bThreadCCDRun1 = true;
		if (!theApp.MainDlg->MIUCheck_process() || gMIUDevice.CurrentState != 4)
		{
			sLangChange.LoadStringA(IDS_STRING452);	//CCD ¸ðµâ ¿µ»ó ÃÊ±âÈ­ ½ÇÆÐ.[%d]\n Á¦Ç° ¾ÈÂø »óÅÂ ¹× Á¦Ç° ºÒ·® È®ÀÎ ÇÏ¼¼¿ä.
			logStr.Format(sLangChange, iStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -11000;
			break;
		}
		bThreadCCDRun1 = false;

		iRtnFunction = 12000;
		break;
	case 12000:
		//È®ÀÎÇÊ¿ä norinda
		Task.m_bPBStart = 1;
		//if( Task.m_bPBStart ==  1 )
		//{
		//	func_Socket_Barcode();
		//}
		//else
		//{
		//	//! ¹ÙÄÚµå°¡ ¾ø±â ¶§¹®¿¡ Åë½Å »ç¿ë ¾ÈÇÔ.
		//	Task.iRecvLenACK[0] = Task.iRecvLenACK[1] = 0;
		//	Task.dTiltingManual[0] = Task.dTiltingManual[1] = 0.0;
		//	Task.dAlignManual[0] = Task.dAlignManual[0] = Task.dAlignManual[0] = 0.0;
		//}
		Task.d_Align_offset_x[PCB_Chip_MARK] = 0;
		Task.d_Align_offset_y[PCB_Chip_MARK] = 0;
		Task.d_Align_offset_th[PCB_Chip_MARK] = 0;

		if (sysData.m_iAlignCamInspPass == 1)		//procProductComplete
		{
			logStr.Format("¿ÏÁ¦Ç° Align Pass[%d]", iStep);
			putListLog(logStr);
			iRtnFunction = 12800;
			break;
		}
		iRtnFunction = 12100;
		break;

	case 12100:

		Task.m_iRetry_Opt = 0;
		//SetDigReference(PCB_Holder_MARK);
		LightControlthird.ctrlLedVolume(LIGHT_PCB, model.m_iLedValue[LEDDATA_HOLDER]);		// Align¸¸ Á¶¸í ON
		
		if (motor.Pcb_Motor_Move(CompleteAlign_Pos))
		{
			Task.PCBTaskTime = myTimer(true);
			logStr.Format("Pcb ¿ÏÁ¦Ç° Align À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]", iStep);
			putListLog(logStr);
			iRtnFunction = 12200;
		}
		else
		{
			logStr.Format("Pcb ¿ÏÁ¦Ç° Align À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -12100;
		}
		break;
	case 12200:
		if (motor.PCB_Z_Motor_Move(CompleteAlign_Pos))
		{
			Task.PCBTaskTime = myTimer(true);
			logStr.Format("Pcb ¿ÏÁ¦Ç° Align ZÀ§Ä¡ ÀÌµ¿ ¿Ï·á[%d]", iStep);
			putListLog(logStr);
			iRtnFunction = 12400;
		}
		else
		{
			logStr.Format("Pcb ¿ÏÁ¦Ç° Align ZÀ§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iStep);
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
			logStr.Format("PCB ¿ÏÁ¦Ç° Align Àç°Ë»ç %d È¸ ½ÇÆÐ[%d]\n º¸Á¤ ¹ÌÀû¿ëÀ¸·Î ÁøÇàÇÏ½Ã°Ú½À´Ï±î?", Task.m_iRetry_Opt, iStep);
			if (askMsg(logStr) == IDOK)
			{
				Task.d_Align_offset_x[PCB_Chip_MARK] -= 0;
				Task.d_Align_offset_y[PCB_Chip_MARK] -= 0;
				Task.d_Align_offset_th[PCB_Chip_MARK] += 0;
				iRtnFunction = 12800;
			}
			else
			{
				iRtnFunction = -12500;
				logStr.Format("PCB Align Àç°Ë»ç %d È¸ ½ÇÆÐ[%d]", Task.m_iRetry_Opt, iStep);
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

			logStr.Format("PCB ¿ÏÁ¦Ç° Align : %.3lf %.3lf %.3lf", Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]);
			//pcbDlg->m_labelAlignResult.SetText(logStr);
			//pcbDlg->m_labelAlignResult.Invalidate();
			putListLog(logStr);

			int iRtnVal = theApp.MainDlg->AlignLimitCheck(CAM1, offsetX, offsetY, offsetTh); // PCBÀÌÀç±â ¿òÁ÷ÀÌ´Â ºÎºÐÀÌ¶û Limit Check ÇÒ¶§ CAM1ÀÓ

			if (iRtnVal == 1)
			{
				iRtnFunction = 12700;				// º¸Á¤ ÀÌµ¿
			}
			else if (iRtnVal == 2)
			{
				iLaser_Pos = 0;
				logStr.Format("		PCB ¿ÏÁ¦Ç° Align [%d] ¿Ï·á [%d]", Task.m_iRetry_Opt, iStep);
				putListLog(logStr);
				//InstantMarkDelete(PCB_Chip_MARK);
				logStr.Format("		PCB ¿ÏÁ¦Ç° Align Complete :  %d, %.03f, %.03f, %.03f", Task.m_iPcbPickupNo, Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]);
				AlignResultSave(logStr);
				Task.m_iRetry_Opt = 0;
				Task.dSocketRecvTime = myTimer(true);
				iRtnFunction = 12800;

			}
			else
			{
				logStr.Format("PCB ¿ÏÁ¦Ç° Align [%d] º¸Á¤ ¹üÀ§ ÃÊ°ú[%d]", Task.m_iRetry_Opt, iStep);
				errMsg2(Task.AutoFlag, logStr);
				AlignLogSave(logStr);
				//InstantMarkDelete(PCB_Chip_MARK);
				iRtnFunction = -12500;
			}
		}
		else
		{
			logStr.Format("PCB ¿ÏÁ¦Ç° Align [%d] ¸¶Å© ÀÎ½Ä ½ÇÆÐ[%d]", Task.m_iRetry_Opt, iStep);
			putListLog(logStr);
			iRtnFunction = 12500;				//  Àç°Ë»ç 
		}
		break;

	case 12700://!! º¸Á¤·® ÀÌµ¿.- Retry
		if (motor.Pcb_Holder_Align_Move(CompleteAlign_Pos, Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]))
		{
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 12200;
		}
		else
		{
			logStr.Format("Pcb ¿ÏÁ¦Ç° Align º¸Á¤ À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -12700;
		}
		break;
	case 12800:
		//LightControlthird.ctrlLedVolume(LIGHT_PCB, 0);		//·¹ÀÌÀú °Ë»çÀü off
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			sLangChange.LoadStringA(IDS_STRING305);	//PCBºÎ zÃà ¸ðÅÍ À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]
			logStr.Format(sLangChange, iStep);
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
		//¿ÜºÎ º¯À§ÃøÁ¤°ª Read
#if (____AA_WAY == LENS_TILT_AA) 
		if (g_ADOData.func_Get_RecordData(Task.ChipID))//DB¿¡ Data°¡ ÀÖÀ» °æ¿ì
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
																		  //
			logStr.Format("PCB È­»ó°Ë»ç Chart Pos X(%.3lf), Y(%.3lf)", Task.dAAPcbMotor[0], Task.dAAPcbMotor[1]);
			putListLog(logStr);
			//
			logStr.Format("PCB È­»ó°Ë»ç TX(%.3lf), TY(%.3lf)", Task.dAAPcbMotor[3], Task.dAAPcbMotor[4]);
			putListLog(logStr);

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


			if (fabs(Task.dAAPcbMotor[0] - model.axis[Motor_PCB_X].pos[Bonding_Pos]) > 5.0)
			{
				logStr.Format("Pcb È­»ó°Ë»ç X spec Over[%d]", iStep);
				errMsg2(Task.AutoFlag, logStr);
				iRtnFunction = -12850;
				break;
			}
			if (fabs(Task.dAAPcbMotor[1] - model.axis[Motor_PCB_Y].pos[Bonding_Pos]) > 5.0)
			{
				logStr.Format("Pcb È­»ó°Ë»ç Y spec Over[%d]", iStep);
				errMsg2(Task.AutoFlag, logStr);
				iRtnFunction = -12850;
				break;
			}

			iRtnFunction = 12900;

			//iRtnFunction = 12900;
			//logStr.Format("ÀÏÄ¡ ¸ðµ¨ ¾ø½À´Ï´Ù.\ bonding À§Ä¡·Î ÁøÇà ÇÏ½Ã°Ú½À´Ï±î?");	//ÀüÃ¼ ¿øÁ¡ º¹±Í¸¦ ½ÇÇà ÇÏ½Ã°Ú½À´Ï±î?
			//if (askMsg(logStr))
			//{

			//	
			//	break;
			//}
			/*logStr.Format("ÀÏÄ¡ ¸ðµ¨ ¾ø½À´Ï´Ù.[%d]", iStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -12850;*/
			//ÀÏÄ¡ ¸ðµ¨ ¾øÀ» °æ¿ì ¼öµ¿ Æ¼Äª°ª Ã¢À¸·Î.
			/*Task.m_iRtnTiltingDlg = 2;
			TiltingManualdlg->ShowWindow(SW_SHOW);
			iRtnFunction = 12870;*/
		}


#else
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
			logStr.Format("º¯À§ÃøÁ¤ Data ÀÔ·Â Áß ÀÚµ¿¸ðµå Á¤Áö ¼±ÅÃ[%d]", iStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -12870;
			break;
		}
		else if (Task.m_iRtnTiltingDlg == 1)
		{
			logStr.Format("¿ÜºÎ º¯À§ Tilting ¿Ï·á À§Ä¡ : Tx=%.03lf, Ty=%.03lf", Task.dTiltingManual[0], Task.dTiltingManual[1]);
			putListLog(logStr);

			Task.m_timeChecker.Measure_Time(4);	//Laser º¯À§ ÃøÁ¤ ½ÃÀÛ ½Ã°£
												//iRtnFunction = 12900;//pcb aa¶Ç ·¹ÀÌÀú ÇÏµµ·Ï 200708

			iRtnFunction = 12900;

		}
		break;
	case 12900:
		if (sysData.m_iLaserInspPass == 1)		//¿ÏÁ¦Ç°
		{
			iRtnFunction = 13300;		//¿ÏÁ¦Ç°½Ã ·¹ÀÌÀú ÆÐ½º
			break;
		}


		if (motor.Pcb_Motor_Move_Laser(iLaser_Pos, Task.d_Align_offset_x[PCB_Holder_MARK], Task.d_Align_offset_y[PCB_Holder_MARK], Task.d_Align_offset_th[PCB_Holder_MARK]))
		{
			Task.PCBTaskTime = myTimer(true);
			if (motor.PCB_Z_Motor_Move(Com_Laser_Pos))//Laser_Lens_Pos))
			{
				Task.PCBTaskTime = myTimer(true);
				logStr.Format("Laser º¯À§ ÃøÁ¤ ¿ÜºÎ À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]", iStep);
				putListLog(logStr);
				iRtnFunction = 12910;// 12950;
			}
			else {
				logStr.Format("PCB Com_Laser_Pos Z ÀÌµ¿ ½ÇÆÐ[%d]", iStep);
				putListLog(logStr);
				errMsg2(Task.AutoFlag, logStr);
				iRtnFunction = -12900;
				break;
			}
		}
		else
		{
			logStr.Format("Laser º¯À§ ÃøÁ¤ ¿ÜºÎ À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -12900;
		}

		break;
	case 12910:
		if (iLaser_Pos > 0)
		{
			iRtnFunction = 12950;
			break;
		}
		if (Dio.LaserCylinderUPDOWN(false, false))
		{
			logStr.Format("LASER ½Ç¸°´õ ÇÏ°­ ¿Ï·á[%d]", iRtnFunction);
			theApp.MainDlg->putListLog(logStr);
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 12920;
		}
		else
		{
			logStr.Format("LASER ½Ç¸°´õ ÇÏ°­ ½ÇÆÐ [%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -12910;
		}
		break;

	case 12920:
		if (Dio.LaserCylinderCheck(false, false))
		{
			logStr.Format("LASER ½Ç¸°´õ ÇÏ°­ È®ÀÎ ¿Ï·á[%d]", iRtnFunction);
			theApp.MainDlg->putListLog(logStr);
			iRtnFunction = 12950;

			Sleep(300);
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > IO_DELAY_TIME)
		{
			logStr.Format("LASER ½Ç¸°´õ ÇÏ°­ ½Ã°£ ÃÊ°ú..[%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -12920;
		}
		break;
		//laser½Ç¸°´õ ÇÏ°­ END
	case 12950:
		checkMessage();
		if ((myTimer(true) - Task.PCBTaskTime) > iLaserDelay && (motor.IsStopAxis(Motor_PCB_X) && motor.IsStopAxis(Motor_PCB_Y)))
		{
			iRtnFunction = 13100;
		}
		break;
	case 13100:
		Keyence.func_CL3000_Scan(Task.m_Laser_Point[iLaser_Pos]);
		Sleep(100);
		logStr.Format("º¯À§ ¼¾¼­ %lf[%d] - ¿ÜºÎ - %d À§Ä¡", Task.m_Laser_Point[iLaser_Pos], iStep, iLaser_Pos + 1);
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
					logStr.Format("Laser ÃøÁ¤°ª ÀÌ»ó..¿ÜºÎ º¯À§ ÃøÁ¤°ªÀÌ ÀÌ»ó..[%d]\n ÃøÁ¤°ª:%.04lf, %.04lf, %.04lf, %.04lf ", iStep, LaserValue[0], LaserValue[1], LaserValue[2], LaserValue[3]);
					errMsg2(Task.AutoFlag, logStr);
					iRtnFunction = -13100;
					break;
				}

				if (theApp.MainDlg->_calcLaserTilt(LaserPos, LaserValue, Task.d_Align_offset_xt[0], Task.d_Align_offset_yt[0]))
				{
					/*	logStr.Format("		º¸Á¤·® Tx: %.04lf, Ty: %.04lf", Task.d_Align_offset_xt[0], Task.d_Align_offset_yt[0] );
					putListLog(logStr);
					logStr.Format("		³»ºÎ º¸Á¤·® ÆíÂ÷ Tx: %.04lf, Ty: %.04lf", Task.dTiltingManual[0], Task.dTiltingManual[1] );
					putListLog(logStr);
					int Rnd = TiltAlignLimitCheck(Task.d_Align_offset_xt[0] + Task.dTiltingManual[0], Task.d_Align_offset_yt[0] + Task.dTiltingManual[1] );
					*/


					//Task.m_dataOffset_x[0] =  Task.d_Align_offset_xt[PCB_Holder_MARK];
					//Task.m_dataOffset_y[0] =  Task.d_Align_offset_yt[PCB_Holder_MARK];
					logStr.Format("		º¸Á¤·® Tx: %.04lf, Ty: %.04lf", Task.d_Align_offset_xt[0], Task.d_Align_offset_yt[0]);
					putListLog(logStr);
					logStr.Format("		¿ÜºÎ º¸Á¤·® ÆíÂ÷ Tx: %.04lf, Ty: %.04lf", Task.dTiltingManual[0], Task.dTiltingManual[1]);
					putListLog(logStr);
					//int Rnd = TiltAlignLimitCheck(Task.d_Align_offset_xt[PCB_Holder_MARK],Task.d_Align_offset_yt[PCB_Holder_MARK]);
					//int Rnd = TiltAlignLimitCheck(Task.d_Align_offset_xt[0] + Task.dTiltingManual[0], Task.d_Align_offset_yt[0] + Task.dTiltingManual[1] );
					int Rnd = theApp.MainDlg->TiltAlignLimitCheck(Task.d_Align_offset_xt[0], Task.d_Align_offset_yt[0]);
					if (Rnd == 2)
					{
						Task.m_timeChecker.Measure_Time(5);	//Laser º¯À§ ÃøÁ¤ ¿Ï·á ½Ã°£
						Task.m_dTime_LaserDpm = Task.m_timeChecker.m_adTime[5] - Task.m_timeChecker.m_adTime[4];
						//dispGrid();
						iRtnFunction = 13300;

					}
					else if (Rnd == 1)
					{
						iRtnFunction = 13200;	//º¸Á¤·® ÀÌµ¿		
					}
					else
					{
						logStr.Format("Laser Tilt  º¸Á¤°ª Limit¸¦ ÃÊ°ú ÇÏ¿´½À´Ï´Ù.[%d]", iStep);
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
		if (Dio.LaserCylinderUPDOWN(true, false))
		{
			logStr.Format("LASER ½Ç¸°´õ »ó½Â ¿Ï·á[%d]", iRtnFunction);
			theApp.MainDlg->putListLog(logStr);
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 13310;
		}
		else
		{
			logStr.Format("LASER ½Ç¸°´õ »ó½Â ½ÇÆÐ [%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -13300;
		}
		break;
	case 13310:
		if (Dio.LaserCylinderCheck(true, false))
		{
			logStr.Format("LASER ½Ç¸°´õ »ó½Â È®ÀÎ ¿Ï·á[%d]", iRtnFunction);
			theApp.MainDlg->putListLog(logStr);
			iRtnFunction = 13350;
			Sleep(300);
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > IO_DELAY_TIME)
		{
			logStr.Format("LASER ½Ç¸°´õ »ó½Â ½Ã°£ ÃÊ°ú..[%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -13310;
		}
		break;
		//laser½Ç¸°´õ »ó½Â END
	case 13350:
		if (motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("PCB Z ´ë±â À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]", iRtnFunction);
			putListLog(logStr);
			iRtnFunction = 14000;
		}
		else
		{
			logStr.Format("PCB Z ´ë±â À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iRtnFunction);
			putListLog(logStr);
			iRtnFunction = -13350;
		}
		break;
	case 14000:

		iRtnFunction = 14100;
		break;
	case 14100:

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

		iRtnFunction = 14400;				// ¿Ï·á
		break;
	case 14400:
		iRtnFunction = 14500;
		break;
	case 14500:
		if (motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			logStr.Format("PCB Z ´ë±â À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]", iStep);
			putListLog(logStr);
			iRtnFunction = 15200;
		}
		else
		{
			logStr.Format("PCB Z ´ë±â À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iStep);
			putListLog(logStr);
			iRtnFunction = -14500;
		}
		break;
	case 15200:
		iRtnFunction = 19600;
		break;

	case 19600: // º»µù À§Ä¡ ÀÌµ¿ 
				//if(motor.Pcb_Motor_Move(Bonding_Pos, Task.d_Align_offset_x[PCB_Holder_MARK] + Task.dAlignManual[0], Task.d_Align_offset_y[PCB_Holder_MARK] + Task.dAlignManual[1], Task.d_Align_offset_th[PCB_Holder_MARK] + Task.dAlignManual[2]) )
		if (motor.Pcb_Motor_Move(Bonding_Pos, Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]))
		{
			Task.PCBTaskTime = myTimer(true);
			logStr.Format("PCB Bonding º¸Á¤ À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]", iStep);
			putListLog(logStr);
			iRtnFunction = 19700;
		}
		else
		{
			logStr.Format("PCB Bonding À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -19600;
		}
		break;
	case 19700:
#if (____AA_WAY == LENS_TILT_AA)
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
#else
		iRtnFunction = 19800;
#endif
		break;
	case 19800: //zÃà º»µù À§Ä¡ ÀÌµ¿
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
			if (sysData.m_iIrChartUse == 1)
			{
				IrvAlignLed.Irv_Light_SetValue(model.m_iLedValue[LEDDATA_TOP1_CHART], IR_CHART);
			}
			else
			{
				LightControl.ctrlLedVolume(LIGHT_TOP_CHART1, model.m_iLedValue[LEDDATA_TOP1_CHART]);
				LightControl.ctrlLedVolume(LIGHT_TOP_CHART2, model.m_iLedValue[LEDDATA_TOP2_CHART]);
				LightControl.ctrlLedVolume(LIGHT_TOP_CHART3, model.m_iLedValue[LEDDATA_TOP3_CHART]);
				LightControl.ctrlLedVolume(LIGHT_TOP_CHART4, model.m_iLedValue[LEDDATA_TOP4_CHART]);
			}


			LightControl.ctrlLedVolume(LIGHT_TOP_CHART1, model.m_iLedValue[LEDDATA_TOP1_CHART]);
			LightControl.ctrlLedVolume(LIGHT_TOP_CHART2, model.m_iLedValue[LEDDATA_TOP2_CHART]);
			LightControl.ctrlLedVolume(LIGHT_TOP_CHART3, model.m_iLedValue[LEDDATA_TOP3_CHART]);
			LightControl.ctrlLedVolume(LIGHT_TOP_CHART4, model.m_iLedValue[LEDDATA_TOP4_CHART]);
			LightControl.ctrlLedVolume(LIGHT_LEFT_CHART, model.m_iLedValue[LEDDATA_CHART_L]);
			LightControl.ctrlLedVolume(LIGHT_RIGHT_CHART, model.m_iLedValue[LEDDATA_CHART_R]);



			//if( func_MIU_ConnectLiveCheck() == false)		//MIU ¿µ»ó Check
			//{
			//	iRtnFunction = -19900;
			//	break;
			//}
			theApp.MainDlg->setCamDisplay(3, 1);

			iRtnFunction = 120000;//¿ÏÁ¦Ç° °Ë»ç
		}
		break;

	default:
		sLangChange.LoadStringA(IDS_STRING1004);	//PCB ¿ÏÁ¦Ç° °Ë»ç Thread Step ¹øÈ£ ºñÁ¤»ó . [%d]
		logStr.Format(sLangChange, iStep);
		errMsg2(Task.AutoFlag, logStr);
		iRtnFunction = -20000;
		break;
	}

	logStr.Empty();
	sSocketMsg.Empty();
	sBarCode.Empty();
	return iRtnFunction;
}

int	CPcbProcess1::Complete_FinalInsp(int iStep)
{
	CString sLog = _T("");
	//CString sTemp = _T("");
	//CString sNgMsg = _T("");
	//CString sImgPath = _T("");
	//CString logStr = _T("");
	double	dFinalDelay = (double)(model.strInfo_Cam[3].m_iDelayTime);
	double offsetX = 0.0, offsetY = 0.0, offsetTh = 0.0;
	int iRtn = 0;
	int iRtnFunction = iStep;
	bool bMtfCheck4 = true;
	switch (iStep)
	{
	case 120000:
		theApp.MainDlg->setCamDisplay(3, 1);
		Sleep(dFinalDelay);

		/*sLog.Format("Gen2 Current:%.03lf", model.dGen2Current);
		putListLog(sLog);
		g_clApsInsp.func_insp_CDP800_Current();*/

		iRtnFunction = 121000;
		break;
	case 121000:

		iRtnFunction = 122000;
		break;

	case 122000:	//¿ÏÁ¦Ç° °Ë»ç¸¸ ÇØ´ç (Final °Ë»çÀü X/Y/T º¸Á¤)
		Sleep(dFinalDelay);
		iRtn = theApp.MainDlg->_getMTF(SFR_FINAL);
		Sleep(500);
		if (iRtn > 0)
		{
			if (!theApp.MainDlg->_calcImageAlignment())	//-- Align º¸Á¤ Limit(ÀÓÀÇÀÇ °ª »ç¿ëÇÔ...1.0)
			{
				sLog.Format("NG.  X : %.3lf Y : %.3lf", Task.m_dShift_IMG_X, Task.m_dShift_IMG_Y);
				putListLog(sLog);
				iRtnFunction = -122000;
				break;
			}
			else
			{

				//Æ¿ÆÃ°ª ¾È¸ÂÀ» °æ¿ì °ªÀÌ µ¿ÀÏÇÏ°Ô ¹Ýº¹µÊ.. 3È¸ Á¤µµ¸¸ ÇÏ°í ¾È¸ÂÀ¸¸é Spec IN ½ÃÅ°±â.., 
				if (Task.m_iFineThCnt > 3)	Task.m_dShift_IMG_TH = 0.0;
				if (fabs(Task.m_dShift_IMG_TH) <= sysData.dSpec_OC_Theta)//X/Y º¸Á¤°ªÀÌ Spec InÀÏ °æ¿ì ´ÙÀ½ Step
				{
					sLog.Format("	¿µ»ó Shift. Spec In(%.03lf) In : T: %.3lf", sysData.dSpec_OC_Theta, Task.m_dShift_IMG_TH);
					putListLog(sLog);
					iRtnFunction = 122500;
				}
				else
				{
					sLog.Format("	¿µ»ó Shift(Spec : %.03lf).  T: %.3lf", sysData.dSpec_OC_Theta, Task.m_dShift_IMG_TH);
					putListLog(sLog);
					Task.m_iFineThCnt++;
					iRtnFunction = 122100;
				}
			}
		}
		else
		{
			errMsg2(Task.AutoFlag, "MTF ÃøÁ¤ Àü SFR ¿µ»ó È¹µæ ½ÇÆÐ..");
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
	case 122500:	//Final Àç °Ë»ç - È®ÀÎ¿ë
		theApp.MainDlg->setCamDisplay(3, 1);
		Sleep(dFinalDelay);
		MIU.func_Set_InspImageCopy(EOL_CHART, MIU.m_pFrameRawBuffer);	//¿ÏÁ¦Ç° ¸ðµå
		Sleep(300);
		iRtnFunction = 122520;
		break;
	case 122520:
		Task.bInsCenter = true;

		theApp.MainDlg->_calcImageAlignment();

		Task.bInsCenter = false;

		Task.sfrResult = theApp.MainDlg->func_MTF(MIU.vChartBuffet);//EOL È­»ó #1

		if (Task.sfrResult == true)
		{
			sLangChange.LoadStringA(IDS_STRING229);
			putListLog("[°Ë»ç] MTF °Ë»ç ¼º°ø.");// Optic_Axis,
		}
		else
		{
			sLangChange.LoadStringA(IDS_STRING228);
			sLog.Format(sLangChange, iStep);
			putListLog(sLog);
		}
		Task.m_iDrawBarStep = Task.m_iCnt_Step_AA_Total;
		theApp.MainDlg->autodispDlg->DrawBarGraph();
		iRtnFunction = 122550;
		break;
	case 122550:
		vision.clearOverlay(CCD);
		vision.drawOverlay(CCD, true);

		iRtnFunction = 122600;
		break;
	case 122600:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			sLangChange.LoadStringA(IDS_STRING305);	//PCBºÎ zÃà ¸ðÅÍ À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]
			sLog.Format(sLangChange, iStep);
			putListLog(sLog);
			iRtnFunction = -122600;
			break;
		}
		iRtnFunction = 122700;
		break;
	case 122700:
		if (!motor.LENS_Z_Motor_Move(Wait_Pos))
		{
			sLangChange.LoadStringA(IDS_STRING747);	//LensºÎ zÃà ¸ðÅÍ À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]
			sLog.Format(sLangChange, iStep);
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
		if (sysData.m_iDefectInspPass == 1)	// ÀÌ¹°°Ë»ç À¯¹«
		{
			sLog.Format(_T("[PASS] Defect Insp"), iStep);
			putListLog(sLog);
			iRtnFunction = 123400;
		}
		else
		{
			//iRtnFunction = 123100;
		}
		break;
	case 123100:
		/*if (!motor.Pcb_Motor_Move(Dark_Pos))
		{
			sLog.Format("PCBºÎ Dark À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iStep);
			putListLog(sLog);
			iRtnFunction = -123100;
		}
		else
		{
			sLog.Format("PCBºÎ Dark À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]", iStep);
			putListLog(sLog);
			iRtnFunction = 123200;
		}*/
		break;
	case 123200:
		/*if (!motor.PCB_Z_Motor_Move(Dark_Pos))
		{
			sLog.Format("PCBºÎ Dark Z À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iStep);
			putListLog(sLog);
			iRtnFunction = -123200;
			break;
		}*/
		Task.PCBTaskTime = myTimer(true);
		iRtnFunction = 123300;
		break;
	case 123300:
		Sleep(100);
		if (motor.IsStopAxis(Motor_PCB_Z))
		{
			Sleep(100);
			MIU.func_Set_InspImageCopy(LOW_LEVEL_RAW, MIU.m_pFrameRawBuffer);
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 123400;
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > 10000)
		{
			sLog.Format("PCB Z DAR Á¤ÁöÈ®ÀÎ ½Ã°£ ÃÊ°ú[%d]", iStep);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -123200;
		}
		break;
	case 123400:
		if (!motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			sLangChange.LoadStringA(IDS_STRING305);	//PCBºÎ zÃà ¸ðÅÍ À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]
			sLog.Format(sLangChange, iStep);
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
		if (sysData.m_iIrChartUse == 1)
		{
			IrvAlignLed.Irv_Light_SetValue(model.m_iLedValue[LEDDATA_6500K], IR_OC);
		}
		else
		{
#ifdef FURONTEER_OC
			OCControl.SendLightLxStep(model.m_iLedValue[LEDDATA_6500K]);
#else
			LightControlthird.ctrlLedVolume(LIGHT_OC_6500K, model.m_iLedValue[LEDDATA_6500K]);
#endif
			//LightControlthird.ctrlLedVolume(LIGHT_OC_6500K, model.m_iLedValue[LEDDATA_6500K]);
		}

		iRtnFunction = 123600;
		break;
	case 123600:

		if (!motor.Pcb_Motor_Move(OC_6500K_Pos, Task.d_Align_offset_x[PCB_Chip_MARK], Task.d_Align_offset_y[PCB_Chip_MARK], Task.d_Align_offset_th[PCB_Chip_MARK]))
		{
			sLangChange.LoadStringA(IDS_STRING1023);	//PCBºÎ ¸ðÅÍ Defect °Ë»ç À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]
			sLog.Format(sLangChange, iStep);
			putListLog(sLog);
			iRtnFunction = -123600;
		}
		else
		{
			iRtnFunction = 123700;
		}
		break;
	case 123700:
		if (motor.PCB_Z_Motor_Move(OC_6500K_Pos))
		{
			sLog.Format("PCB Z Axis OC 6500K Pos Move Complete[%d]", iStep);
			putListLog(sLog);
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 123800;
		}
		else
		{
			sLog.Format("PCB Z Axis OC 6500K Pos Move Fail[%d]", iStep);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -123700;
		}
		break;
	case 123800:
		if ((myTimer(true) - Task.PCBTaskTime) > 500)
		{
			iRtnFunction = 123850;
		}
		break;
	case 123850:
		if (motor.IsStopAxis(Motor_PCB_Z))
		{
			Task.PCBTaskTime = myTimer(true);

			//6500k ÀÌ¹ÌÁö ÀúÀå
			Sleep(300);
			MIU.func_Set_InspImageCopy(MID_6500K_RAW, MIU.m_pFrameRawBuffer);
			//ccdDlg->m_pSFRDlg->Raw_ImageSave(MIU.m_pFrameRawBuffer, MID_6500K_RAW);
			//MID_6500K_RAW ÀÌ¹ÌÁö ÀúÀå

			iRtnFunction = 123900;
		}
		else
		{
			sLog.Format("PCB Z Axis OC 6500K Pos Move Check Fail[%d]", iStep);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -123700;
		}
		break;
	case 123900:
		Sleep(dFinalDelay);
		if (sysData.m_iDefectInspPass == 1)	// ÀÌ¹°°Ë»ç À¯¹«
		{
			sLog.Format(_T("[PASS] Defect Insp"), iStep);
			putListLog(sLog);
		}
		else
		{
			if (g_clApsInsp.func_Insp_Defect(MIU.vDefectMidBuffer_6500K, MIU.vDefectLowBuffer, true) == true)	//EOL
			{
				putListLog("[°Ë»ç] Defect °Ë»ç ¼º°ø.");
			}
			else
			{
				sLog.Format("[°Ë»ç] Defect °Ë»ç  Error[%d]", iStep);
				putListLog(sLog);
				MandoInspLog.bInspRes = false;
			}
		}
		if (sysData.m_iStaintInspPass == 1)	// ÀÌ¹°°Ë»ç À¯¹«
		{
			sLog.Format(_T("[PASS] Stain Insp"), iStep);
			putListLog(sLog);

		}
		else
		{
			if (g_clApsInsp.func_Insp_Stain(MIU.vDefectMidBuffer_6500K) == true)
			{
				putListLog("[°Ë»ç] Stain °Ë»ç ¼º°ø.");
			}
			else
			{
				sLog.Format("[°Ë»ç] Stain °Ë»ç  Error[%d]", iStep);
				putListLog(sLog);
				MandoInspLog.bInspRes = false;
			}
		}
		iRtnFunction = 127000;
		break;
	case 127000:
		if (motor.PCB_Z_Motor_Move(Wait_Pos))
		{
			sLog.Format("PCB ZÃà ´ë±â À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]", iStep);
			putListLog(sLog);
			iRtnFunction = 127600;
		}
		else
		{
			sLog.Format("PCB ZÃà ´ë±â À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iStep);
			sLog.Format(sLangChange, iStep);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -127000;
		}
		break;

	case 127600:
		Task.m_iRetry_Opt = 0;
		iRtnFunction = 127700;
		break;
	case 127700:
		//
		if (MIU.Close())
		{
			iRtnFunction = 127800;
		}
		else
		{
			iRtnFunction = 127700;

			if (Task.m_iRetry_Opt>3)
			{
				sLog.Format("CCD ¿µ»ó Close ½ÇÆÐ [%d]", iStep);	//CCD ¿µ»ó Close ½ÇÆÐ[%d]
				errMsg2(Task.AutoFlag, sLog);
				iRtnFunction = -127700;
			}
			else {
				Task.m_iRetry_Opt++;
			}
		}
		break;
	case 127800:

		iRtnFunction = 127900;
		break;
	case 127900:
		//MIU.m_acsInspImage.Unlock();
		Task.m_iRetry_Opt = 0;
		MandoInspLog.func_LogSave_UVAfter();	//¸¸µµ Â÷·®¿ëCamera °Ë»ç Log ÀúÀå(°Ë»ç/º¸Á¤·® ÀúÀå -> ÃÖÁ¾Log)
												//! °Ë»ç Count Ã³¸®
		g_FinalInspLog();
		//inspMES();
		//MESCommunication.Messave();
		work.iInspCnt_Output++;
		if (MandoInspLog.bInspRes == false)	work.iInspCnt_NG_Output++;
		theApp.MainDlg->dispInspResGrid();
		work.Save();
		work.Load();

		Task.m_timeChecker.Measure_Time(13);	//Final °Ë»ç ¿Ï·á ½Ã°£
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
			MandoInspLog.func_DrawNG_Overlay(CCD);	//È­¸é Overlay¿¡ NG List Draw
			work.m_iCnt_NG_Output++;
		}
		vision.drawOverlay(CCD, true);

		//ccd¿µ»ó ÀüÈ¯

		theApp.MainDlg->ctrlSubDlg(MAIN_DLG);
		theApp.MainDlg->setCamDisplay(3, 1);
		theApp.MainDlg->changeMainBtnColor(MAIN_DLG);
		iRtnFunction = 128100;
		break;

	case 128100:
		iRtnFunction = 129200;

		break;
	case 129200:
		if (!motor.Lens_Motor_MoveXY(0, Wait_Pos))
		{
			sLangChange.LoadStringA(IDS_STRING748);	//LensºÎ ¸ðÅÍ ´ë±â À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]
			sLog.Format(sLangChange, iStep);
			putListLog(sLog);
			iRtnFunction = -129200;
		}
		else
		{
			iRtnFunction = 129220;
		}
		break;

	case 129220:

		iRtnFunction = 129300;
		break;
	case 129300:
		if (motor.Pcb_Motor_Move(Wait_Pos))
		{
			sLangChange.LoadStringA(IDS_STRING987);	//PCB ´ë±â À§Ä¡ ÀÌµ¿ ¿Ï·á [%d]
			sLog.Format(sLangChange, iStep);
			putListLog(sLog);
			iRtnFunction = 129350;
		}
		else
		{
			sLangChange.LoadStringA(IDS_STRING986);	//PCB ´ë±â À§Ä¡ ÀÌµ¿ ½ÇÆÐ [%d]
			sLog.Format(sLangChange, iStep);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -129300;
		}

		break;
	case 129350:
		iRtnFunction = 129400;
		break;
	case 129400:
		if (motor.Pcb_Tilt_Motor_Move(Wait_Pos))
		{
			sLog.Format("PCB TX,TY ´ë±â À§Ä¡ ÀÌµ¿ ¿Ï·á [%d]", iStep);
			putListLog(sLog);
			iRtnFunction = 129500;
		}
		else
		{
			sLog.Format("PCB TX,TY ´ë±âÀ§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iStep);
			errMsg2(Task.AutoFlag, sLog);
			iRtnFunction = -129400;
		}
		break;

	case 129500:
		Task.m_bOkDispense = -1;	//¸ÞÀÎ µµÆ÷ ¿Ï·á Lamp Ãë¼Ò
		putListLog("		");
		putListLog("		");
		sLog.Format("			END =======%s", Task.ChipID);
		putListLog(sLog);
		putListLog("		");
		putListLog("		");
		Task.m_bPBStart = 0;	//¹ÙÄÚµå Á¤º¸ ÃÊ±âÈ­
		if (true)
		{
			memset(Task.ChipID, 0x00, 256);
			sprintf_s(Task.ChipID, "EMPTY");
			theApp.MainDlg->func_ChipID_Draw();
		}

		Task.m_timeChecker.Measure_Time(14);	//¿ÏÁ¦Ç° ¹èÃâ ½Ã°£
		Task.m_dTime_Total = Task.m_timeChecker.m_adTime[14] - Task.m_timeChecker.m_adTime[1];

		theApp.MainDlg->dispGrid();
		theApp.MainDlg->EpoxyTimeCheck(theApp.MainDlg->bEpoxyTimeChk);
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		Task.PCBTask = 10000;
		Task.LensTask = 10000;
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


int CPcbProcess1::RunProc_LENS_AlignLaserMeasure(int iLensStep)
{
	int iRtnFunction = iLensStep;
	int iCamDelay = model.strInfo_Cam[1].m_iDelayTime;		//PCB ¿µ»ó È¹µæ Delay
	int iAlignRetry = model.strInfo_Cam[1].m_iRetryCnt;
	int iRtn = 0;
	CString logStr = "";
	bool bChk = true;
	double offsetX = 0.0, offsetY = 0.0, offsetTh = 0.0;

	int iLaserDelay = model.strInfo_Cam[0].m_iDelayTime;	//Laser ÃøÁ¤Àü Delay

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
			iRtnFunction = 30100;
		}
		else
		{
			logStr.Format("Lens_ZÃà ´ë±âÀ§Ä¡ ÀÌµ¿ ½ÇÆÐ.[%d]", iLensStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -30000;
		}

		break;
	case 30100:
#if (____AA_WAY == PCB_TILT_AA)
		iRtnFunction = 30500;
#elif (____AA_WAY == LENS_TILT_AA)
		if (motor.Lens_Motor_MoveXY(0, Wait_Pos))
		{
			iRtnFunction = 43000;//41900;		//·»ÁîÂÊ Ä«¸Þ¶ó ¾øÀ½
		}
		else
		{
			logStr.Format("Lens ´ë±âÀ§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iLensStep);
			putListLog(logStr);
			iRtnFunction = -30050;
		}
		break;

#endif

		break;
	case 30500:
		iRtnFunction = 30600;

		break;
	case 30600:
		iRtnFunction = 30900;

		break;
	case 30900:
#if (____AA_WAY == PCB_TILT_AA)
		if (sysData.m_iLaserInspPass == 1)	//·»Áî
		{
			iRtnFunction = 41100;			//Laser ÃøÁ¤ Pass
		}
		else
		{
			iRtnFunction = 31000;		// 31300;//¾ó¶óÀÎ ÀÓ½Ã ÆÐ½º
		}

#elif (____AA_WAY == LENS_TILT_AA)
		iRtnFunction = 43000;//41900;		//·»ÁîÂÊ Ä«¸Þ¶ó ¾øÀ½
#endif

		break;
	case 31000:
		if (motor.LENS_Z_Motor_Move(Wait_Pos))
		{
			Task.LensTaskTime = myTimer(true);
			iRtnFunction = 31050;
		}
		else
		{
			logStr.Format("Lens_ZÃà ´ë±âÀ§Ä¡ ÀÌµ¿ ½ÇÆÐ.[%d]", iLensStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -31000;
		}



		break;

	case 31050:
		LightControlthird.ctrlLedVolume(LIGHT_PCB, model.m_iLedValue[LEDDATA_LENS]);
		if (motor.Lens_Motor_MoveXY(0, Lens_Pos))
		{
			Task.LensTaskTime = myTimer(true);
			logStr.Format("Lens Align À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]", iLensStep);
			putListLog(logStr);
			iRtnFunction = 31060;
		}
		else
		{
			logStr.Format("Lens Align À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iLensStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -31050;
		}
		break;
	case 31060:
		if (motor.LENS_Z_Motor_Move(Lens_Pos))
		{
			Task.LensTaskTime = myTimer(true);
			logStr.Format("Lens Align Z À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]", iLensStep);
			putListLog(logStr);
			iRtnFunction = 31080;
		}
		else
		{
			logStr.Format("Lens Align Z À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]", iLensStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -31060;
		}
		break;

	case 31080:
		checkMessage();
		if ((myTimer(true) - Task.PCBTaskTime) > iCamDelay && (motor.IsStopAxis(Motor_Lens_X) && motor.IsStopAxis(Motor_Lens_Y)))
		{
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 31100;
		}
		break;

	case 31100: // lens Align
		if (Task.m_iRetry_Opt > iAlignRetry)
		{
			logStr.Format("Lens Align Àç°Ë»ç %d È¸ ½ÇÆÐ[%d]\n º¸Á¤ ¹ÌÀû¿ëÀ¸·Î ÁøÇàÇÏ½Ã°Ú½À´Ï±î?", Task.m_iRetry_Opt, iLensStep);
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
				logStr.Format("Lens Align Àç°Ë»ç %d È¸ ½ÇÆÐ[%d]", Task.m_iRetry_Opt, iLensStep);
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
			Task.d_Align_offset_th[LENS_Align_MARK] = 0;//+= offsetTh;	//Lens´Â º¸Á¤·® Theta°¡ ¾øÀ½

			logStr.Format("Lens Align : %.3lf %.3lf %.3lf", Task.d_Align_offset_x[LENS_Align_MARK], Task.d_Align_offset_y[LENS_Align_MARK], Task.d_Align_offset_th[LENS_Align_MARK]);
			//pcbDlg->m_labelAlignResult.SetText(logStr);
			//pcbDlg->m_labelAlignResult.Invalidate();

			putListLog(logStr);

			int iRtnVal = theApp.MainDlg->AlignLimitCheck(CAM2, offsetX, offsetY, 0);
			if (iRtnVal == 1)
			{
				iRtnFunction = 31200;				// º¸Á¤ ÀÌµ¿
			}
			else if (iRtnVal == 2)
			{
				logStr.Format("		Lens Align [%d] ¿Ï·á [%d]", Task.m_iRetry_Opt, iLensStep);
				putListLog(logStr);
				theApp.MainDlg->InstantMarkDelete(LENS_Align_MARK);			//ÀÓ½Ã µî·Ï ¸¶Å© »èÁ¦

				logStr.Format("		Lens Align Complete : %d, %.03f, %.03f, %.03f", Task.m_iLensPickupNoCentering, Task.d_Align_offset_x[LENS_Align_MARK], Task.d_Align_offset_y[LENS_Align_MARK], Task.d_Align_offset_th[LENS_Align_MARK]);
				AlignResultSave(logStr);
				Task.m_iRetry_Opt = 0;
				iRtnFunction = 31250;// 31300;				// ¿Ï·á
			}
			else
			{
				logStr.Format("Lens Align [%d] º¸Á¤ ¹üÀ§ ÃÊ°ú[%d]", Task.m_iRetry_Opt, iLensStep);
				errMsg2(Task.AutoFlag, logStr);
				AlignLogSave(logStr);
				theApp.MainDlg->InstantMarkDelete(LENS_Align_MARK);
				iRtnFunction = -31100;				// NG
			}
		}
		else
		{
			logStr.Format("Lens Align [%d] ¸¶Å© ÀÎ½Ä ½ÇÆÐ[%d]", Task.m_iRetry_Opt, iLensStep);
			putListLog(logStr);
			iRtnFunction = 31100;					//  Àç°Ë»ç 
		}
		break;

	case 31200://!! º¸Á¤·® ÀÌµ¿.- Retry
		if (motor.Lens_Motor_Align_Move(Task.d_Align_offset_x[LENS_Align_MARK], Task.d_Align_offset_y[LENS_Align_MARK], Task.d_Align_offset_th[LENS_Align_MARK]))
		{
			Task.LensTaskTime = myTimer(true);
			iRtnFunction = 31080;
		}
		else
		{
			sLangChange.LoadStringA(IDS_STRING657);	//Lens Align º¸Á¤ À§Ä¡ ÀÌµ¿ ½ÇÆÐ
			logStr.Format(sLangChange + _T("[%d]"), iLensStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -31200;
		}
		break;
	case 31250:
		LightControlthird.ctrlLedVolume(LIGHT_PCB, 0);
		if (motor.LENS_Z_Motor_Move(Wait_Pos))
		{
			Task.LensTaskTime = myTimer(true);
			iRtnFunction = 31300;
		}
		else
		{
			logStr.Format("Lens_ZÃà ´ë±âÀ§Ä¡ ÀÌµ¿ ½ÇÆÐ.[%d]", iLensStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -31250;
		}
		break;
	case 31300://! Lens-ZÃà ´ë±â À§Ä¡ ÀÌµ¿
		iLaser_Pos = 0;
		if (motor.Lens_Motor_Move_Laser(iLaser_Pos, Task.d_Align_offset_x[LENS_Align_MARK], Task.d_Align_offset_y[LENS_Align_MARK], Task.d_Align_offset_th[LENS_Align_MARK]))
		{
			Task.LensTaskTime = myTimer(true);
			logStr.Format("Laser º¯À§ ÃøÁ¤ ¿ÜºÎ À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]", iLensStep);	//Laser º¯À§ ÃøÁ¤ ¿ÜºÎ À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]
			putListLog(logStr);
			iRtnFunction = 40000;
		}
		else
		{
			logStr.Format("Laser º¯À§ ÃøÁ¤ ¿ÜºÎ À§Ä¡ ÀÌµ¿ ½ÇÆÐ [%d]", iLensStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -31300;
		}
		break;
	case 40000://! Laser-ZÃà ¿ÜºÎ ÃøÁ¤À§Ä¡ ÀÌµ¿
		if (motor.LENS_Z_Motor_Move(Laser_Lens_Pos))
		{
			Task.LensTaskTime = myTimer(true);
			iRtnFunction = 40100;
		}
		else
		{
			logStr.Format("Laser-ZÃà º¯À§ ÃøÁ¤ ¿ÜºÎ À§Ä¡ ÀÌµ¿ ½ÇÆÐ [%d]", iLensStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -40000;
		}
		break;

	case 40100:
		iRtnFunction = 40200;
		break;

	case 40200://! Lens Stage ¿ÜºÎ Laser ÃøÁ¤À§Ä¡ ÀÌµ¿ 
		if (motor.Lens_Motor_Move_Laser(iLaser_Pos, Task.d_Align_offset_x[LENS_Align_MARK], Task.d_Align_offset_y[LENS_Align_MARK], Task.d_Align_offset_th[LENS_Align_MARK]))
		{
			Task.LensTaskTime = myTimer(true);
			logStr.Format("Laser º¯À§ ÃøÁ¤ ¿ÜºÎ À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]", iLensStep);	//Laser º¯À§ ÃøÁ¤ ¿ÜºÎ À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]
			putListLog(logStr);
			if (iLaser_Pos == 0) { iRtnFunction = 40210; }//Ã³À½¸¸ ÇÏ°­¸í·É.
			else { iRtnFunction = 40300; }
		}
		else
		{
			logStr.Format("Laser º¯À§ ÃøÁ¤ ¿ÜºÎ À§Ä¡ ÀÌµ¿ ½ÇÆÐ [%d]", iLensStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -40200;
		}
		break;

		//Laser ½Ç¸°´õ ÇÏ°­
	case 40210:
		if (Dio.LaserCylinderUPDOWN(false, false))
		{
			logStr.Format("LASER ½Ç¸°´õ ÇÏ°­ ¿Ï·á[%d]", iRtnFunction);
			theApp.MainDlg->putListLog(logStr);
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 40220;
		}
		else
		{
			logStr.Format("LASER ½Ç¸°´õ ÇÏ°­ ½ÇÆÐ [%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -40210;
		}
		break;

	case 40220:
		if (Dio.LaserCylinderCheck(false, false))
		{
			logStr.Format("LASER ½Ç¸°´õ ÇÏ°­ È®ÀÎ ¿Ï·á[%d]", iRtnFunction);
			theApp.MainDlg->putListLog(logStr);
			iRtnFunction = 40300;

			Sleep(300);
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > IO_DELAY_TIME)
		{
			logStr.Format("LASER ½Ç¸°´õ ÇÏ°­ ½Ã°£ ÃÊ°ú..[%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -40220;
		}
		break;
	case 40300://! ÃøÁ¤ Àü Delay
		checkMessage();
		if ((myTimer(true) - Task.LensTaskTime) > iLaserDelay && (motor.IsStopAxis(Motor_Lens_X) && motor.IsStopAxis(Motor_Lens_Y)))	//ÃÖÁÖÀÓ´Ô, Delay È®ÀÎ
		{
			iRtnFunction = 41000;
		}
		break;
		//Laser ½Ç¸°´õ ÇÏ°­ END

	case 41000: //¿ÜºÎ º¯À§ °¨Áö (ÀúÀå µû·Î ÇÏ°í Align ÀÌµ¿)
				//Keyence.func_LT9030_Scan(Task.m_Laser_Point[iLaser_Pos]);
		Keyence.func_CL3000_Scan(Task.m_Laser_Point[iLaser_Pos]);
		logStr.Format("º¯À§ ¼¾¼­ %lf[%d] - ¿ÜºÎ - %d À§Ä¡", Task.m_Laser_Point[iLaser_Pos], iLensStep, iLaser_Pos + 1);
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
					sLangChange.LoadStringA(IDS_STRING639);	//Laser ÃøÁ¤°ª ÀÌ»ó..¿ÜºÎ º¯À§ ÃøÁ¤°ªÀÌ ÀÌ»ó..[%d]\n ÃøÁ¤°ª:%.04lf, %.04lf, %.04lf, %.04lf
					logStr.Format(sLangChange, iLensStep, LaserValue[0], LaserValue[1], LaserValue[2], LaserValue[3]);
					errMsg2(Task.AutoFlag, logStr);
					iRtnFunction = -41000;
					break;
				}

				if (theApp.MainDlg->_calcLaserTilt(LaserPos, LaserValue, Task.d_Align_offset_xt[LENS_Align_MARK], Task.d_Align_offset_yt[LENS_Align_MARK]))
				{
					Task.m_dataOffset_x[LENS_Align_MARK] = Task.d_Align_offset_xt[LENS_Align_MARK];
					Task.m_dataOffset_y[LENS_Align_MARK] = Task.d_Align_offset_yt[LENS_Align_MARK];


					sLangChange.LoadStringA(IDS_STRING1264);		//º¸Á¤·® Tx: %.04lf, Ty: %.04lf
					logStr.Format(_T("		") + sLangChange, Task.d_Align_offset_xt[LENS_Align_MARK], Task.d_Align_offset_yt[LENS_Align_MARK]);
					putListLog(logStr);

					int Rnd = theApp.MainDlg->TiltAlignLimitCheck(Task.m_dataOffset_x[LENS_Align_MARK], Task.m_dataOffset_y[LENS_Align_MARK]);
					//20160117 ÀÌÇü¼® ¼öÁ¤

					if (Rnd == 2)
					{

						Task.m_timeChecker.Measure_Time(5);	//Laser º¯À§ ÃøÁ¤ ¿Ï·á ½Ã°£
						Task.m_dTime_LaserDpm = Task.m_timeChecker.m_adTime[5] - Task.m_timeChecker.m_adTime[4];
						//dispGrid();
						MandoInspLog.dTilteOffset[0] = Task.m_dataOffset_x[LENS_Align_MARK];	//¸¸µµ Â÷·®¿ëCamera °Ë»ç Log ÀúÀå
						MandoInspLog.dTilteOffset[1] = Task.m_dataOffset_y[LENS_Align_MARK];


						//20141217 LHC - DataBase¿¡ 0°ªÀÌ ÀúÀåµÇ´Â °æ¿ì°¡ »ý°Ü 0°ªÀÌ µé¾î°¥ °æ¿ì ÀúÀåÇÏÁö¾Ê°í ¾Ë¶÷Ä¡µµ·Ï.
						//±è¿µÈ£ 20150602 FraneeGrabber  °ü·Ã ÀÓ½Ã Pass
						if (Task.m_dataOffset_x[LENS_Align_MARK] == 0 || Task.m_dataOffset_y[LENS_Align_MARK] == 0)
						{
							sLangChange.LoadStringA(IDS_STRING627);	//Laser º¯À§ Â÷ °ª ÀÌ»ó ¹ß»ý..
							logStr.Format(sLangChange + _T("Xt : %lf, Yt : %lf"), Task.m_dataOffset_x[LENS_Align_MARK], Task.m_dataOffset_y[LENS_Align_MARK]);
							errMsg2(Task.AutoFlag, logStr);
							iRtnFunction = -41000;
							break;
						}
						if (!g_ADOData.func_AATaskToRecordLaser(Task.ChipID, Task.m_dataOffset_x[LENS_Align_MARK], Task.m_dataOffset_y[LENS_Align_MARK], Task.m_Laser_Point))
						{
							sLangChange.LoadStringA(IDS_STRING489);	//DataBase Laser º¯À§ ÃøÁ¤ Data ±â·Ï ½ÇÆÐ.[%d]\n MS Office¸¦ ´Ý¾ÆÁÖ¼¼¿ä.
							logStr.Format(sLangChange, iLensStep);
							errMsg2(Task.AutoFlag, logStr);
							iRtnFunction = -41000;
							break;
						}

						LightControlthird.ctrlLedVolume(LIGHT_PCB, model.m_iLedValue[LEDDATA_LENS]);		// Align¸¸ Á¶¸í ON
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
						logStr.Format("Laser Tilt  º¸Á¤°ª Limit¸¦ ÃÊ°ú ÇÏ¿´½À´Ï´Ù.[%d]", iLensStep);
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

	case 41050: // ÀÌµ¿  º¯À§°ªÀÌ 0À¸·Î ¸¸µé±â À§ÇØ ÀÌµ¿
		if (motor.Lens_Move_Tilt(Task.d_Align_offset_xt[LENS_Align_MARK], Task.d_Align_offset_yt[LENS_Align_MARK]))
		{
			iRtnFunction = 40200;
			iLaser_Pos = 0;//4;

		}
		break;

	case 41100:
		iRtnFunction = 41110;
		break;

		//laser½Ç¸°´õ »ó½Â
	case 41110:
		if (Dio.LaserCylinderUPDOWN(true, false))
		{
			logStr.Format("LASER ½Ç¸°´õ »ó½Â ¿Ï·á[%d]", iRtnFunction);
			theApp.MainDlg->putListLog(logStr);
			Task.PCBTaskTime = myTimer(true);
			iRtnFunction = 41120;
		}
		else
		{
			logStr.Format("LASER ½Ç¸°´õ »ó½Â ½ÇÆÐ [%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -41110;
		}
		break;

	case 41120:
		if (Dio.LaserCylinderCheck(true, false))
		{
			logStr.Format("LASER ½Ç¸°´õ »ó½Â È®ÀÎ ¿Ï·á[%d]", iRtnFunction);
			theApp.MainDlg->putListLog(logStr);
			iRtnFunction = 41200;

			Sleep(300);
		}
		else if ((myTimer(true) - Task.PCBTaskTime) > IO_DELAY_TIME)
		{
			logStr.Format("LASER ½Ç¸°´õ »ó½Â ½Ã°£ ÃÊ°ú..[%d]", iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -41120;
		}
		break;
		//laser½Ç¸°´õ »ó½ÂEND

	case 41200://! Lens-ZÃà ´ë±â À§Ä¡ ÀÌµ¿
		if (motor.LENS_Z_Motor_Move(Wait_Pos))
		{
			Task.LensTaskTime = myTimer(true);
			iRtnFunction = 41850;;//// 41300; //41850;//ÀÓ½Ã ·»Áî align pass
								  //iRtnFunction = 41300;
		}
		else
		{
			sLangChange.LoadStringA(IDS_STRING739);	//Lens_ZÃà ´ë±âÀ§Ä¡ ÀÌµ¿ ½ÇÆÐ
			logStr.Format(sLangChange + _T("[%d]"), iLensStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -41200;
		}
		break;

	case 41300:
		if (motor.Lens_Motor_MoveXY(0, Lens_Pos))
		{
			Task.LensTaskTime = myTimer(true);
			sLangChange.LoadStringA(IDS_STRING659);	//Lens Align ÀÌµ¿ [%d]
			logStr.Format(sLangChange, iLensStep);
			putListLog(logStr);
			iRtnFunction = 41400;
		}
		else
		{
			sLangChange.LoadStringA(IDS_STRING660);	//Lens Align ÀÌµ¿ ½ÇÆÐ[%d]
			logStr.Format(sLangChange, iLensStep);
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
			sLangChange.LoadStringA(IDS_STRING661);	//Lens Align À§Ä¡ ÀÌµ¿ ¿Ï·á[%d]
			logStr.Format(sLangChange, iLensStep);
			putListLog(logStr);
			iRtnFunction = 41500;
		}
		else
		{
			sLangChange.LoadStringA(IDS_STRING660);	//Lens Align À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]
			logStr.Format(sLangChange, iLensStep);
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

	case 41600://! LENS Align(º¯À§ÃøÁ¤ º¸Á¤ÈÄ, Shift °è»ê ¿ëµµ)
		if (sysData.m_FreeRun == 1)
		{
			for (int i = 0; i<100; i++)
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
			logStr.Format("Lens Align Àç°Ë»ç %d È¸ ½ÇÆÐ[%d]\n º¸Á¤ ¹ÌÀû¿ëÀ¸·Î ÁøÇàÇÏ½Ã°Ú½À´Ï±î?", Task.m_iRetry_Opt, iLensStep);
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
				logStr.Format("Lens Align Àç°Ë»ç %d È¸ ½ÇÆÐ[%d]", Task.m_iRetry_Opt, iLensStep);
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
			Task.d_Align_offset_th[LENS_Align_MARK] = 0;//+= offsetTh;	//Lens´Â º¸Á¤·® Theta°¡ ¾øÀ½

			sLangChange.LoadStringA(IDS_STRING651);	//Lens Align : %.3lf %.3lf %.3lf
			logStr.Format("Lens Align : %.3lf %.3lf %.3lf", Task.d_Align_offset_x[LENS_Align_MARK], Task.d_Align_offset_y[LENS_Align_MARK], Task.d_Align_offset_th[LENS_Align_MARK]);
			//			Sleep(500);
			//pcbDlg->m_labelAlignResult.SetText(logStr);
			//pcbDlg->m_labelAlignResult.Invalidate();

			putListLog(logStr);

			int iRtnVal = theApp.MainDlg->AlignLimitCheck(CAM2, offsetX, offsetY, 0);
			if (iRtnVal == 1)
			{
				iRtnFunction = 41700;				// º¸Á¤ ÀÌµ¿
			}
			else if (iRtnVal == 2)
			{
				sLangChange.LoadStringA(IDS_STRING654);	//Lens Align [%d] ¿Ï·á [%d]
				logStr.Format(_T("		") + sLangChange, Task.m_iRetry_Opt, iLensStep);
				putListLog(logStr);

				theApp.MainDlg->InstantMarkDelete(LENS_Align_MARK);			//ÀÓ½Ã µî·Ï ¸¶Å© »èÁ¦

				sLangChange.LoadStringA(IDS_STRING655);	//Lens Align Complete : %d, %.03f, %.03f, %.03f
				logStr.Format(_T("		") + sLangChange, Task.m_iLensPickupNoCentering, Task.d_Align_offset_x[LENS_Align_MARK], Task.d_Align_offset_y[LENS_Align_MARK], Task.d_Align_offset_th[LENS_Align_MARK]);
				AlignResultSave(logStr);
				Task.m_iRetry_Opt = 0;
				iRtnFunction = 41800;				// ¿Ï·á
			}
			else
			{
				sLangChange.LoadStringA(IDS_STRING653);	//Lens Align [%d] º¸Á¤ ¹üÀ§ ÃÊ°ú
				logStr.Format(sLangChange + _T("[%d]"), Task.m_iRetry_Opt, iLensStep);
				errMsg2(Task.AutoFlag, logStr);
				AlignLogSave(logStr);
				theApp.MainDlg->InstantMarkDelete(LENS_Align_MARK);
				iRtnFunction = -41600;				// NG
			}
		}
		else
		{
			sLangChange.LoadStringA(IDS_STRING652);	//Lens Align [%d] ¸¶Å© ÀÎ½Ä ½ÇÆÐ[%d]
			logStr.Format(sLangChange, Task.m_iRetry_Opt, iLensStep);
			putListLog(logStr);

			iRtnFunction = 41600;					//  Àç°Ë»ç 
		}
		break;

	case 41700://!! º¸Á¤·® ÀÌµ¿.- Retry
		if (motor.Lens_Motor_Align_Move(Task.d_Align_offset_x[LENS_Align_MARK], Task.d_Align_offset_y[LENS_Align_MARK], Task.d_Align_offset_th[LENS_Align_MARK]))
		{
			Task.LensTaskTime = myTimer(true);
			iRtnFunction = 41500;
		}
		else
		{
			sLangChange.LoadStringA(IDS_STRING657);	//Lens Align º¸Á¤ À§Ä¡ ÀÌµ¿ ½ÇÆÐ
			logStr.Format(sLangChange + _T("[%d]"), iLensStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -41700;
		}
	case 41800: // °ª ÀúÀå2

				//!!!!! 1Â÷ Align º¸Á¤·® ÆíÂ÷ ÀúÀå °ø½Ä(PCB<-> Lens Sensor°£)
		Task.m_dataOffset_x[1] = Task.d_Align_offset_x[LENS_Align_MARK];
		Task.m_dataOffset_y[1] = Task.d_Align_offset_y[LENS_Align_MARK];
		//		Task.m_dataOffset_th[1] = Task.d_Align_offset_th[LENS_Align_MARK] - Task.d_Align_offset_th[PCB_Chip_MARK];

		//sLangChange.LoadStringA(IDS_STRING962);	//PCB Sensor_Holder°£ Align ÆíÂ÷°ª : X:%.03f, Y:%.03f, ¥È:%.04f [%d]
		//logStr.Format(_T("		") + sLangChange, Task.m_dataOffset_x[1], Task.m_dataOffset_y[1],Task.m_dataOffset_th[1], iLensStep);
		//putListLog(logStr);

		//¸¸µµ Â÷·®¿ëCamera °Ë»ç Log ÀúÀå
		MandoInspLog.dLensOffset[0] = Task.m_dataOffset_x[1];
		MandoInspLog.dLensOffset[1] = Task.m_dataOffset_y[1];
		MandoInspLog.dLensOffset[2] = Task.m_dataOffset_th[1];


		iRtnFunction = 41850;
		//if (Dio.CamLaserSlinderMove(false, true))
		//{
		//	logStr.Format("Laser/Cam ½Ç¸°´õ ÈÄÁø ¿Ï·á[%d]", iLensStep);
		//	//putListLog(logStr);
		//	Task.LensTaskTime = myTimer(true);
		//	iRtnFunction = 41850;
		//}
		//else
		//{
		//	logStr.Format("Laser/Cam ½Ç¸°´õ ÈÄÁø ½ÇÆÐ[%d]", iLensStep);
		//	errMsg2(Task.AutoFlag, logStr);
		//	iRtnFunction = -41800;
		//}

		// 20141217 LHC - sensor_holder°£ align ÆíÂ÷ °ª¿¡ 0°¡ µé¾î°¡¸é Á¤ÁöÇÏ°Ô²û
		//±è¿µÈ£ 20150602 FraneeGrabber  °ü·Ã ÀÓ½Ã Pass
		//if(Task.m_dataOffset_x[1] == 0 || Task.m_dataOffset_y[1] == 0 || Task.m_dataOffset_th[1] == 0)
		//{
		//	sLangChange.LoadStringA(IDS_STRING963);	//PCB Sensor_Holder°£ Align ÆíÂ÷°ª ÀÌ»ó ¹ß»ý : X:%.03f, Y:%.03f, ¥È:%.04f [%d]
		//	logStr.Format(_T("		") + sLangChange, Task.m_dataOffset_x[1], Task.m_dataOffset_y[1],Task.m_dataOffset_th[1], iLensStep);
		//	putListLog(logStr);
		//	errMsg2(Task.AutoFlag,logStr);
		//	iRtnFunction = -41800;
		//	break;
		//}

		//-- ADO DB ÀúÀå
		//g_ADOData.func_AATaskToRecordAlign(Task.ChipID, MandoInspLog.dLensOffset[0], MandoInspLog.dLensOffset[1], MandoInspLog.dLensOffset[2]);

		break;
	case 41850:
		iRtnFunction = 41870;
		//if (Dio.CamLaserSlinderMove(false, true))
		//{
		//	logStr.Format("Laser/Cam ½Ç¸°´õ ÈÄÁø ¿Ï·á[%d]", iLensStep);
		//	//putListLog(logStr);
		//	Task.LensTaskTime = myTimer(true);
		//	iRtnFunction = 41870;
		//}
		//else
		//{
		//	logStr.Format("Laser/Cam ½Ç¸°´õ ÈÄÁø ½ÇÆÐ[%d]", iLensStep);
		//	errMsg2(Task.AutoFlag, logStr);
		//	iRtnFunction = -41850;
		//}
		break;
	case 41870:
		iRtnFunction = 41900;
		//if (Dio.CamLaserSlinderCheck(false, false))
		//{
		//	logStr.Format("Laser/Cam ½Ç¸°´õ ÈÄÁø È®ÀÎ ¿Ï·á[%d]", iLensStep);
		//	putListLog(logStr);
		//	iRtnFunction = 41900;
		//}
		//else if ((myTimer(true) - Task.LensTaskTime) > 10000)//IO_DELAY_TIME)
		//{
		//	logStr.Format("Laser/Cam ½Ç¸°´õ ÈÄÁø ½Ã°£ ÃÊ°ú[%d]", iLensStep);
		//	errMsg2(Task.AutoFlag, logStr);
		//	iRtnFunction = -41870;
		//}
		break;
	case 41900://! Lens-ZÃà ´ë±â À§Ä¡ ÀÌµ¿
		if (motor.LENS_Z_Motor_Move(Wait_Pos))
		{
			Task.LensTaskTime = myTimer(true);
			iRtnFunction = 41950;
		}
		else
		{
			sLangChange.LoadStringA(IDS_STRING739);	//Lens_ZÃà ´ë±âÀ§Ä¡ ÀÌµ¿ ½ÇÆÐ
			logStr.Format(sLangChange + _T("[%d]"), iLensStep);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -41900;
		}
		break;
	case 41950:
		iRtnFunction = 42000;


		break;
	case 42000: // º»µù À§Ä¡ ÀÌµ¿
		if (motor.Lens_Motor_MoveXY(0, Bonding_Pos, Task.d_Align_offset_x[LENS_Align_MARK], Task.d_Align_offset_y[LENS_Align_MARK]))
		{
			sLangChange.LoadStringA(IDS_STRING659);	//Lens Align ÀÌµ¿ [%d]
			logStr.Format(sLangChange, iRtnFunction);
			putListLog(logStr);
			iRtnFunction = 42200;
		}
		else
		{
			sLangChange.LoadStringA(IDS_STRING664);	//Lens Bonding À§Ä¡ ÀÌµ¿ ½ÇÆÐ[%d]
			logStr.Format(sLangChange, iRtnFunction);
			errMsg2(Task.AutoFlag, logStr);
			iRtnFunction = -42000;
		}
		break;
	case 42200:
		//Á×½º ¸ðµ¨  , lens º»µùÀ§Ä¡¿¡¼­ zÃà ´ë±âÀ§Ä¡¿¡¼­ pcb º»µùÀ§Ä¡·Î ¸øµé¾î¿Í¼­ zÃà Á» µé¾î¿Ã·Á³ö¾ßµÊ
		iRtnFunction = 43000;
		break;
	case 42400:
		if ((myTimer(true) - Task.LensTaskTime) > iCamDelay && (motor.IsStopAxis(Motor_Lens_Z)))
		{
			iRtnFunction = 43000;
		}
		break;
	case 43000:
		Task.interlockPcb = 1;
		Task.interlockLens = 1;
		iRtnFunction = 50000;
		break;
	default:
		sLangChange.LoadStringA(IDS_STRING628);	//Laser º¯À§ ÃøÁ¤ Thread Step ¹øÈ£ ºñÁ¤»ó .
		logStr.Format(sLangChange + _T("[%d]"), iLensStep);
		errMsg2(Task.AutoFlag, logStr);
		iRtnFunction = -1;
		break;
	}

	return iRtnFunction;
}




