#include "stdafx.h"
#include "vision.h"

CEvent				g_GrabEvent;


bool CVision::initVB()
{
	int i, index;
	int pitch, Hight;
#ifdef  _M_X64
	LONG64 lBufferAttributes[2];
	LONG64 lNumberOfDigitizer;
#else 
	long lBufferAttributes[2];
	long lNumberOfDigitizer;
#endif
	

	/* MilApplication Alloc */
	MappAlloc(M_DEFAULT, &MilApplication);

//#ifndef _DEBUG
	/* 디버깅 모드 시 에러메세지 보기 */
	MappControl(M_ERROR,M_PRINT_DISABLE);
//#endif // _DEBUG
#ifdef NORINDA_MODE
	//MsysAlloc(M_SYSTEM_VGA, M_DEV0, M_COMPLETE, &MilSystem);

	MsysAlloc(M_SYSTEM_GIGE_VISION, M_DEV0, M_COMPLETE, &MilSystem);//
#else
	#ifdef ON_LINE_VISION
		//MsysAlloc(M_SYSTEM_METEOR_II, M_DEV0, M_COMPLETE, &MilSystem);
		MsysAlloc(M_SYSTEM_GIGE_VISION, M_DEV0, M_COMPLETE, &MilSystem);//
	//MsysAlloc(M_SYSTEM_VGA, M_DEV0, M_COMPLETE, &MilSystem);
	#else
		MsysAlloc(M_SYSTEM_VGA, M_DEV0, M_COMPLETE, &MilSystem);
	#endif
#endif


	MsysInquire(MilSystem,M_DIGITIZER_NUM,&lNumberOfDigitizer);

	if (lNumberOfDigitizer>0)
	{
		MdigAlloc(MilSystem,M_DEFAULT,"CAM_241125.dcf",M_DEFAULT,&MilDigitizer);
		MdigControl(MilDigitizer, M_GRAB_MODE, M_ASYNCHRONOUS);
		MdigControl(MilDigitizer, M_GRAB_TIMEOUT, 100);//100);

		lBufferAttributes[0] = M_IMAGE + M_GRAB + M_PROC;
		lBufferAttributes[1] = M_IMAGE + M_PROC + M_DISP;
	}
	else
	{
		lBufferAttributes[0] = M_IMAGE + M_PROC;
		lBufferAttributes[1] = M_IMAGE + M_PROC + M_DISP;
	}


	MbufAlloc2d(MilSystem, CAM_SIZE_X, CAM_SIZE_Y, M_DEF_IMAGE_TYPE, lBufferAttributes[0], &MilGrabImage[0]);

	if (MilGrabImage[0])
	{
		MbufClear(MilGrabImage[0], 0);
		for (i = 0; i<Cam_Cnt; i++)
		{
			MbufChild2d(MilGrabImage[0], 0, 0, CAM_SIZE_X, CAM_SIZE_Y, &MilGrabImageChild[i]);
			if (MilGrabImageChild[i])
				MbufClear(MilGrabImageChild[i], 0);
			else
			{
				errMsg2(Task.AutoFlag, "MilGrabImageChild Alloc 실패");
				return false;
			}
		}
	}
	
	MbufAlloc2d(MilSystem, CAM_SIZE_X, CAM_SIZE_Y, M_DEF_IMAGE_TYPE, lBufferAttributes[1], &MilProcImage[0]);
	if (MilProcImage[0])
	{
		MbufClear(MilProcImage[0], 0);
		for (i = 0; i<Cam_Cnt; i++)
		{
			MbufChild2d(MilProcImage[0], 0, 0, CAM_SIZE_X, CAM_SIZE_Y, &MilProcImageChild[i]);
			pitch = MbufInquire(MilProcImageChild[i], M_PITCH, M_NULL);
			Hight = MbufInquire(MilProcImageChild[i], M_SIZE_Y, M_NULL);

			MilImageBuffer[i] = (unsigned char*)GlobalAlloc(GMEM_ZEROINIT, pitch * Hight);

			MbufInquire(MilProcImageChild[i], M_HOST_ADDRESS, &MilImageBuffer[i]);

			if (MilProcImageChild[i])
				MbufClear(MilProcImageChild[i], 0);
			else
			{
				errMsg2(Task.AutoFlag, "MilProcImageChild Alloc 실패");

				return false;
			}
		}
	}
	for(int ccd=0; ccd<2; ccd++)
	{
		/* 디스플레이용 버퍼 Alloc */
		//MbufAlloc2d(MilSystem, SMALL_CCD_SIZE_X, SMALL_CCD_SIZE_Y, M_DEF_IMAGE_TYPE, lBufferAttributes[1], &MilSmallImage[ccd]);
		MbufAllocColor(MilSystem, 3, SMALL_CCD_SIZE_X, SMALL_CCD_SIZE_Y, M_DEF_IMAGE_TYPE, lBufferAttributes[1], &MilSmallImage[ccd]);
		if (MilSmallImage[ccd])
		{
			MbufClear(MilSmallImage[ccd], 0);
			for (i=0 ; i<Cam_Cnt ; i++)
			{
				if ( ccd == 0 && i == 2 )	continue;

				MbufChildColor(MilSmallImage[ccd], M_RED, &MilSmallImageChild[ccd*Cam_Cnt+i]);
				//MbufChild2d(MilSmallImage[ccd], 0, 0, SMALL_CCD_SIZE_X, SMALL_CCD_SIZE_Y, &MilSmallImageChild[ccd*Cam_Cnt + i]);
				if (MilSmallImageChild[ccd*Cam_Cnt+i])	MbufClear(MilSmallImageChild[ccd*Cam_Cnt+i], 0);
				else { ::errMsg2(Task.AutoFlag, "MilSmallImageChild Alloc 실패"); return false; }
			}
		}
		else
		{
			errMsg2(Task.AutoFlag, "MilSmallImage Alloc 실패");
			return false;
		}
	}


	for(index=0; index<MAX_BUFFER_SIZE; index++)
	{
		MbufAlloc2d(MilSystem, CAM_SIZE_X, CAM_SIZE_Y, M_DEF_IMAGE_TYPE, lBufferAttributes[0], &MilGrabBufferList[index]);
		if (MilGrabBufferList[index])
			MbufClear(MilGrabBufferList[index], 0);
		else
		{
			errMsg2(Task.AutoFlag, "MilGrabBufferList Allocation 실패.");
			return false;
		}
	}


	MbufAlloc2d(MilSystem, SMALL_CAM_SIZE_X, SMALL_CAM_SIZE_Y, M_DEF_IMAGE_TYPE, lBufferAttributes[0], &MilSmallShadeImage);
	if (MilSmallShadeImage)
		MbufClear(MilSmallShadeImage, 0);
	else
	{
		errMsg2(Task.AutoFlag, "MilSmallShadeImage Allocation 실패.");
		return false;
	}


	for (i=0 ; i<MARK_CNT; i++)
	{
		for (int j=0 ; j<2; j++)
		{
			MbufAlloc2d(MilSystem, CAM_SIZE_X, CAM_SIZE_Y, M_DEF_IMAGE_TYPE, lBufferAttributes[1], &MilMarkImage[i][j]);

			if (MilMarkImage[i][j])	MbufClear(MilMarkImage[i][j], 0);
			MpatAllocResult(MilSystem, 1L, &PatResult[i][j]);
			MmodAllocResult(MilSystem, M_DEFAULT, &ModResult[i][j]);
		}
	}

	//! Added by LHW (2013/2/26)
	for ( i = 0; i < 2; i++ )
	{
		::GetLocalTime( &(m_aTimeGrab[i]) );
		::GetLocalTime( &(m_aTimeGrab_Proc[i]) );
	}

	//! Added by LHW (2013/3/11)
	::GetLocalTime(&m_TimeProcImageCV);

	//! Added by LHW (2013/3/12)
	for ( i = 0; i < iBufSize_Bayer; i++ )
	{
		::GetLocalTime(&(m_aTimeBayer[i]));
	}

	return true;
}


void CVision::StopGrab()
{
#ifdef ON_LINE_VISION
	MdigProcess(MilDigitizer, MilGrabBufferList, MAX_BUFFER_SIZE-1, M_STOP, M_DEFAULT, ProcessingFunction, &UserHookData);
#endif
}


void CVision::StartGrab()
{
	UserHookData.liveMode = 1;
	UserHookData.MilGrabImage = MilGrabImage[0];
	UserHookData.MilSmallImage = MilSmallImage[0];

#ifdef ON_LINE_VISION
	MdigProcess(MilDigitizer, MilGrabBufferList, MAX_BUFFER_SIZE-1, M_START, M_DEFAULT, ProcessingFunction, &UserHookData);
#endif
}

void CVision::setLiveMode(int flag)
{
	if(flag)
		UserHookData.liveMode = 1;
	else
		UserHookData.liveMode = 0;
}


int CVision::getLiveMode()
{
	return	UserHookData.liveMode;
}


void CVision::closeVB()
{
	int i, j;


// #ifdef ON_LINE_VISION
// 	MdigProcess(MilDigitizer, MilGrabBufferList, MAX_BUFFER_SIZE-1, M_STOP, M_DEFAULT, ProcessingFunction, &UserHookData);
// #endif

	MdigHalt(MilDigitizer);
	MdispSelect(MilDisplay[0], M_NULL);
	MdispSelect(MilDisplay[1], M_NULL);
	MdispSelect(MilDisplay[2], M_NULL);
	MdispSelect(MilDisplay[3], M_NULL);

	if (MilTempImage)
	{
		MbufFree(MilTempImage);
		MilTempImage = M_NULL;
	}

	if(ChartCenterPatternImage)
	{
		MbufFree(ChartCenterPatternImage);
		ChartCenterPatternImage = M_NULL;
	}

	if(ChartCenterPatternResult)
	{
		MbufFree(ChartCenterPatternResult);
		ChartCenterPatternResult = M_NULL;
	}
	
	for (int i = 0; i<COMMON_LAST_MARK_CNT; i++)//for(int i=0;i<LAST_MARK_CNT;i++)
	{
		MbufFree(FieldPatternImage[i]);
		FieldPatternImage[i] = M_NULL;

		MbufFree(FieldPatternResult[i]);
		FieldPatternResult[i] = M_NULL;

	}

	for (i=2 ; i>=0 ; i--)
	{
		for (j=1; j>=0 ; j--)
		{
			if (ModResult[i][j])
			{
				MmodFree(ModResult[i][j]);
				ModResult[i][j] = M_NULL;
			}

			if (ModModel[i][j])
			{
				MmodFree(ModModel[i][j]);
				ModModel[i][j] = M_NULL;
			}

			if (PatResult[i][j])
			{
				MpatFree(PatResult[i][j]);
 				PatResult[i][j] = M_NULL;
			}

			if (PatModel[i][j])
			{
				MpatFree(PatModel[i][j]);
				PatModel[i][j] = M_NULL;
			}
		}
	}

	for (i=2; i>=0 ; i--)
	{
		for (j=1; j>=0 ; j--)
		{
			if (MilMarkDisplay[i][j])
			{
				MdispFree(MilMarkDisplay[i][j]);
				MilMarkDisplay[i][j] = M_NULL;
			}

			if (MilMarkSmallImage[i][j])
			{
				MbufFree(MilMarkSmallImage[i][j]);
				MilMarkSmallImage[i][j] = M_NULL;
			}

			if (MilMarkImage[i][j])
			{
				MbufFree(MilMarkImage[i][j]);
				MilMarkImage[i][j] = M_NULL;
			}
		}
	}

	for (i=0; i<MAX_CAM_NO; i++)
	{
		if (MilDisplay[i])
		{
			MdispFree(MilDisplay[i]);
			MilDisplay[i] = M_NULL;
		}

		if (MilOverlayImage[i])
		{
			MilOverlayImage[i] = M_NULL;
		}
	}

	//MiuBufferFree();	//! Added by LHW (2013/3/12)


	for (i = 0; i < iBufSize_Bayer; i++)
	{
		if (MilBayerImage[i] != M_NULL)
		{
			MbufFree(MilBayerImage[i]);
			MilBayerImage[i] = M_NULL;
		}
	}

	//
	//
	//
	int index = 0;
	for (i=0; i<2; i++)
	{
		for (j=0; j<Cam_Cnt; j++)
		{
			index = i*Cam_Cnt + j;

			if (MilImageBuffer[index]) 
			{
				GlobalUnlock(MilImageBuffer[index]);
			}

			if (MilSmallImageChild[index])
			{
				MbufFree(MilSmallImageChild[index]);
				MilSmallImageChild[index] = M_NULL;
			}

			if (MilGrabImageChild[index])
			{
				MbufFree(MilGrabImageChild[index]);
				MilGrabImageChild[index] = M_NULL;
			}

			if (MilProcImageChild[index])
			{
				MbufFree(MilProcImageChild[index]);
				MilProcImageChild[index] = M_NULL;
			}
		}

		if (MilSmallImage[i])
		{
			MbufFree(MilSmallImage[i]);
			MilSmallImage[i] = M_NULL;
		}

		if (MilGrabImage[i])
		{
			MbufFree(MilGrabImage[i]);
			MilGrabImage[i] = M_NULL;
		}

		if (MilProcImage[i])
		{
			MbufFree(MilProcImage[i]);
			MilProcImage[i] = M_NULL;
		}
	}

	for (int inxdex=0; inxdex < MAX_BUFFER_SIZE; inxdex++)
	{
		if (MilGrabBufferList[inxdex])
		{
			MbufFree(MilGrabBufferList[inxdex]);
			MilGrabBufferList[inxdex] = M_NULL;
		}
	}

	if (MilDigitizer)
	{
		MdigFree(MilDigitizer);
		MilDigitizer = M_NULL;
	}

	MappControl(M_ERROR,M_PRINT_DISABLE);

	if (MilSystem)
	{
		MsysFree(MilSystem);
		MilSystem = M_NULL;
	}

	if (MilApplication)
	{
		MappFree(MilApplication);
		MilApplication = M_NULL;
	}
}

bool CVision::initDisplay()
{
	for (int i=0 ; i<Cam_Cnt; i++)
	{
		if (MilSmallImageChild[i])
		{
			//MdispAlloc(MilSystem, M_DEV0, M_DISPLAY_SETUP, M_DEFAULT, &MilDisplay[i]);
			MdispAlloc(MilSystem, M_DEV0, MIL_TEXT("M_DEFAULT"), M_DEFAULT, &MilDisplay[i]);
			//MdispAlloc(m_MilSystem[nSysIndex], M_DEV0, MIL_TEXT("M_DEFAULT"), M_DEFAULT, &m_MilCamDisplay[nCamIndex][i]);


			MIL_INT DisplayType = MdispInquire(MilDisplay[i], M_DISPLAY_TYPE, M_NULL);
			//if(MdispInquire(MilDisplay[i], M_DISPLAY_MODE, M_NULL)!=M_WINDOWED)
			if (DisplayType != M_WINDOWED)
			{
				sLangChange.LoadStringA(IDS_STRING776);	//MilDisplay Alloc 실패
				::errMsg2(Task.AutoFlag, sLangChange);
				MdispFree(MilDisplay[i]);
				MilDisplay[i] = (MIL_ID) NULL;
				return false;
			}
		}
	}

	if (MilSmallImage[1])
	{
		MdispAlloc(MilSystem, M_DEV0, MIL_TEXT("M_DEFAULT"), M_DEFAULT, &MilDisplay[Cam_Cnt]);


		MIL_INT DisplayType = MdispInquire(MilDisplay[Cam_Cnt], M_DISPLAY_TYPE, M_NULL);
		//if(MdispInquire(MilDisplay[Cam_Cnt], M_DISPLAY_MODE, M_NULL)!=M_WINDOWED)
		if (DisplayType != M_WINDOWED)
		{
			sLangChange.LoadStringA(IDS_STRING776);	//MilDisplay Alloc 실패
			::errMsg2(Task.AutoFlag, sLangChange);
			MdispFree(MilDisplay[Cam_Cnt]);
			MilDisplay[Cam_Cnt] = (MIL_ID) NULL;
			return false;
		}
	}

	return true;
}


void CVision::initMarkDisplay(int iSizeX, int iSizeY)
{
	if (iSizeX<=0 || iSizeY<=0)
	{
		sLangChange.LoadStringA(IDS_STRING765);
		errMsg2(Task.AutoFlag, sLangChange);
		return;
	}

	long BufferAttributes = M_IMAGE + M_DISP + M_PROC;

	for (int i=0 ; i<MARK_CNT ; i++)
	{
		for (int j=0 ; j<2 ; j++)
		{
			MilMarkDisplay[i][j] = M_NULL;

			MbufAllocColor(MilSystem, 1L, CAM_SIZE_X, CAM_SIZE_Y, M_DEF_IMAGE_TYPE, BufferAttributes, &MilMarkImage[i][j]);
			MbufAllocColor(MilSystem, 1L, iSizeX, iSizeY, M_DEF_IMAGE_TYPE, BufferAttributes, &MilMarkSmallImage[i][j]);

			if (MilMarkImage[i][j])	MbufClear(MilMarkImage[i][j], 0);

			if (MilMarkSmallImage[i][j])
			{
				MbufClear(MilMarkSmallImage[i][j], 0);

				//MilMarkDisplay[i][j] = MdispAlloc(MilSystem, M_DEV0, M_DISPLAY_SETUP, M_DEFAULT, M_NULL);
				MilMarkDisplay[i][j] = MdispAlloc(MilSystem, M_DEV0, MIL_TEXT("M_DEFAULT"), M_DEFAULT, M_NULL);

				//if(MdispInquire(MilMarkDisplay[i][j], M_DISPLAY_MODE, M_NULL)!=M_WINDOWED)             
				MIL_INT DisplayType = MdispInquire(MilMarkDisplay[i][j], M_DISPLAY_TYPE, M_NULL);
				if (DisplayType != M_WINDOWED)
				{	
					sLangChange.LoadStringA(IDS_STRING1093);	//This example does not run in dual screen mode.
					errMsg2(Task.AutoFlag, sLangChange);

					MdispFree(MilMarkDisplay[i][j]);
					MilMarkDisplay[i][j] = (MIL_ID) NULL;
				}
			}
		}	
	}

	MbufAllocColor(MilSystem, 1L, CAM_SIZE_X, CAM_SIZE_Y, M_DEF_IMAGE_TYPE, BufferAttributes, &MilTempImage);
	if (MilTempImage)	MbufClear(MilTempImage, 0);
}


void CVision::InitMarkSetDisplay(int iSizeX, int iSizeY)
{
	if (iSizeX<=0 || iSizeY<=0)
	{
		sLangChange.LoadStringA(IDS_STRING766);
		errMsg2(Task.AutoFlag, sLangChange);
		return;
	}

	long BufferAttributes = M_IMAGE+M_DISP+M_PROC;

	MbufAlloc2d(MilSystem, iSizeX, iSizeY, M_DEF_IMAGE_TYPE, BufferAttributes, &MilMarkSetImage);

	if (MilMarkSetImage)
	{
		MbufClear(MilMarkSetImage, 0);

		MilMarkSetDisplay = M_NULL;
		MilMarkSetOverlayImage = M_NULL;

		MilMarkSetDisplay = MdispAlloc(MilSystem, M_DEFAULT, M_DISPLAY_SETUP, M_DEFAULT, M_NULL);
	}
}

void CVision::InitBuffer_AutoDisplay(int iSizeX, int iSizeY)
{
	long BufferAttributes = M_IMAGE+M_DISP+M_PROC;

	/* 광축 */
	MbufAllocColor(MilSystem, 3L, iSizeX, iSizeY, M_DEF_IMAGE_TYPE, BufferAttributes, &MilOptImage);
	if (MilOptImage)
	{
		MbufClear(MilOptImage, 0);

		MilOptDisplayImage = M_NULL;
		MilOptOverlayImage = M_NULL;

		MilOptDisplayImage = MdispAlloc(MilSystem, M_DEFAULT, M_DISPLAY_SETUP, M_DEFAULT, M_NULL);
	}

	/* 이물 */
	MbufAllocColor(MilSystem, 3L, iSizeX, iSizeY, M_DEF_IMAGE_TYPE, BufferAttributes, &MilDefectImage);
	if (MilDefectImage)
	{
		MbufClear(MilDefectImage, 0);

		MilDefectDisplayImage = M_NULL;
		MilDefectOverlayImage = M_NULL;

		MilDefectDisplayImage = MdispAlloc(MilSystem, M_DEFAULT, M_DISPLAY_SETUP, M_DEFAULT, M_NULL);
	}
	MbufAllocColor(MilSystem, 3L, iSizeX, iSizeY, M_DEF_IMAGE_TYPE, BufferAttributes, &MilSaveDisplayDefectImage);
	if (MilSaveDisplayDefectImage)
	{
		MbufClear(MilSaveDisplayDefectImage, 0);
	}
}


void CVision::enableMarkSetOverlay()
{
	if(MilMarkSetDisplay)
	{
		MIL_INT DisplayType = MdispInquire(MilMarkSetDisplay, M_DISPLAY_TYPE, NULL);
		//if(MdispInquire(MilMarkSetDisplay, M_DISPLAY_MODE, M_NULL) == M_WINDOWED )
		if (DisplayType == (M_WINDOWED | M_USER_WINDOW))
		{
			MdispControl(MilMarkSetDisplay, M_OVERLAY, M_ENABLE);
			MdispInquire(MilMarkSetDisplay, M_OVERLAY_ID, &MilMarkSetOverlayImage);
			MdispControl(MilMarkSetDisplay, M_WINDOW_OVR_SHOW, M_ENABLE);
			MdispInquire(MilMarkSetDisplay, M_TRANSPARENT_COLOR, &MarkSetTransparentColor);
			MbufClear(MilMarkSetOverlayImage, MarkSetTransparentColor);
			MdispControl(MilMarkSetDisplay, M_OVERLAY_CLEAR, M_DEFAULT);
			MgraControl(M_DEFAULT, M_BACKGROUND_MODE, M_TRANSPARENT);
		}
	}
}


void CVision::enableOverlay_AutoDisp()
{
	if(MilOptDisplayImage)
	{
		MIL_INT DisplayType = MdispInquire(MilOptDisplayImage, M_DISPLAY_TYPE, NULL);
		//if(MdispInquire(MilOptDisplayImage, M_DISPLAY_MODE, M_NULL) == M_WINDOWED )
		if (DisplayType == (M_WINDOWED | M_USER_WINDOW))
		{
			MdispControl(MilOptDisplayImage, M_OVERLAY, M_ENABLE);
			MdispInquire(MilOptDisplayImage, M_OVERLAY_ID, &MilOptOverlayImage);
			MdispControl(MilOptDisplayImage, M_WINDOW_OVR_SHOW, M_ENABLE);
			MdispInquire(MilOptDisplayImage, M_TRANSPARENT_COLOR, &TransparentColor_Opt);
			MbufClear(MilOptOverlayImage, TransparentColor_Opt);
			MdispControl(MilOptDisplayImage, M_OVERLAY_CLEAR, M_DEFAULT);
			MgraControl(M_DEFAULT, M_BACKGROUND_MODE, M_TRANSPARENT);
		}
	}

	if(MilDefectDisplayImage)
	{
		MIL_INT DisplayType = MdispInquire(MilDefectDisplayImage, M_DISPLAY_TYPE, NULL);
		//if(MdispInquire(MilDefectDisplayImage, M_DISPLAY_MODE, M_NULL) == M_WINDOWED )
		if (DisplayType == (M_WINDOWED | M_USER_WINDOW))
		{
			MdispControl(MilDefectDisplayImage, M_OVERLAY, M_ENABLE);
			MdispInquire(MilDefectDisplayImage, M_OVERLAY_ID, &MilDefectOverlayImage);
			MdispControl(MilDefectDisplayImage, M_WINDOW_OVR_SHOW, M_ENABLE);
			MdispInquire(MilDefectDisplayImage, M_TRANSPARENT_COLOR, &TransparentColor_Defect);
			MbufClear(MilDefectOverlayImage, TransparentColor_Defect);
			MdispControl(MilDefectDisplayImage, M_OVERLAY_CLEAR, M_DEFAULT);
			MgraControl(M_DEFAULT, M_BACKGROUND_MODE, M_TRANSPARENT);
		}
	}
}

void CVision::DeleteBuffer_AutoDisp()
{
	if ( MilDefectOverlayImage )
		MilDefectOverlayImage = M_NULL;
	if ( MilOptOverlayImage )
		MilOptOverlayImage = M_NULL;

	if ( MilDefectDisplayImage )
	{
		MdispFree(MilDefectDisplayImage);
		MilDefectDisplayImage = M_NULL;
	}

	if ( MilOptDisplayImage )
	{
		MdispFree(MilOptDisplayImage);
		MilOptDisplayImage = M_NULL;
	}

	if ( MilDefectImage )
	{
		MbufFree(MilDefectImage);
		MilDefectImage = M_NULL;
	}
	if ( MilSaveDisplayDefectImage )
	{
		MbufFree(MilSaveDisplayDefectImage);
		MilSaveDisplayDefectImage = M_NULL;
	}

	if ( MilOptImage )
	{
		MbufFree(MilOptImage);
		MilOptImage = M_NULL;
	}
}

void CVision::CloseMarkSetDisplay()
{
	if (MilMarkSetOverlayImage)
		MilMarkSetOverlayImage = M_NULL;

	if (MilMarkSetDisplay)
	{
		MdispFree(MilMarkSetDisplay);
		MilMarkSetDisplay = M_NULL;
	}
	if (MilMarkSetImage)
	{
		MbufFree(MilMarkSetImage);
		MilMarkSetImage = M_NULL;
	}
}

void CVision::enableOverlay()
{
#ifdef ON_LINE_VISION
	for(int i=0; i<MAX_CAM_NO; i++)
	{
		if(MilDisplay[i])
		{
			MIL_INT DisplayType = MdispInquire(MilDisplay[i], M_DISPLAY_TYPE, NULL);
			//if(MdispInquire(MilDisplay[i], M_DISPLAY_MODE, M_NULL) == M_WINDOWED)
			if (DisplayType == (M_WINDOWED | M_USER_WINDOW))
			{
				MdispControl(MilDisplay[i], M_OVERLAY, M_ENABLE);
				MdispInquire(MilDisplay[i], M_OVERLAY_ID, &MilOverlayImage[i]);
				MdispControl(MilDisplay[i], M_WINDOW_OVR_SHOW, M_ENABLE);
				MdispInquire(MilDisplay[i], M_TRANSPARENT_COLOR, &TransparentColor[i]);
				MbufClear(MilOverlayImage[i], TransparentColor[i]);
				MdispControl(MilDisplay[i], M_OVERLAY_CLEAR, M_DEFAULT);
				MgraControl(M_DEFAULT, M_BACKGROUND_MODE, M_TRANSPARENT);
			}
		}
	}
#endif
}

void CVision::clearOverlay(int iCamNo/* =999 */)
{
	if (iCamNo==999)
	{
		pixellist[CAM1].iCnt = crosslist[CAM1].iCnt = boxlist[CAM1].iCnt = ellipselist[CAM1].iCnt= linelist[CAM1].iCnt = textlist[CAM1].iCnt = 0;
		pixellist[CAM2].iCnt = crosslist[CAM2].iCnt = boxlist[CAM2].iCnt = ellipselist[CAM2].iCnt= linelist[CAM2].iCnt = textlist[CAM2].iCnt = 0;
//		pixellist[CAM3].iCnt = crosslist[CAM3].iCnt = boxlist[CAM3].iCnt = linelist[CAM3].iCnt = textlist[CAM3].iCnt = 0;
		pixellist[Cam_Cnt].iCnt = crosslist[Cam_Cnt].iCnt = boxlist[Cam_Cnt].iCnt = ellipselist[Cam_Cnt].iCnt= linelist[Cam_Cnt].iCnt = textlist[Cam_Cnt].iCnt = 0;
	}
	else if (iCamNo==CAM1)
		pixellist[CAM1].iCnt = crosslist[CAM1].iCnt = boxlist[CAM1].iCnt = ellipselist[CAM1].iCnt = linelist[CAM1].iCnt = textlist[CAM1].iCnt = 0;
	else if (iCamNo==CAM2)
		pixellist[CAM2].iCnt = crosslist[CAM2].iCnt = boxlist[CAM2].iCnt = ellipselist[CAM2].iCnt = linelist[CAM2].iCnt = textlist[CAM2].iCnt = 0;
// 	else if (iCamNo==CAM3)
// 		pixellist[CAM3].iCnt = crosslist[CAM3].iCnt = boxlist[CAM3].iCnt = linelist[CAM3].iCnt = textlist[CAM3].iCnt = 0;
	else if (iCamNo==Cam_Cnt)
		pixellist[Cam_Cnt].iCnt = crosslist[Cam_Cnt].iCnt = boxlist[Cam_Cnt].iCnt = ellipselist[Cam_Cnt].iCnt =linelist[Cam_Cnt].iCnt = textlist[Cam_Cnt].iCnt = 0;
}

void CVision::drawOverlay(int iCamNo/* =999 */, bool largeFlag, bool BaseFlag)
{
	int iFirstCam=0;
	int iLastCam = 0;

	double dReduceFactorX = 0.0;
	double dReauceFactorY = 0.0;

	CString str="";
	if (iCamNo==999)
	{
		iFirstCam = CAM1;//CAM1+1;
		iLastCam = Cam_Cnt;
	}
	else
	{
		iFirstCam = iCamNo;
		iLastCam = iCamNo;
	}

	for (int i=iFirstCam; i<=iLastCam; i++)
	{
		if (i<3)
		{
			dReduceFactorX = CAM_REDUCE_FACTOR_X;
			dReauceFactorY = CAM_REDUCE_FACTOR_Y;
		}
		else
		{
			dReduceFactorX = m_dReduceFactorX;
			dReauceFactorY = m_dReduceFactorY;
		}
#ifdef ON_LINE_VISION
		MbufClear(MilOverlayImage[i], TransparentColor[i]);

		MbufControl(MilOverlayImage[i], M_DC_ALLOC, M_DEFAULT);

		HDC	OverlayDC = (HDC)MbufInquire(MilOverlayImage[i], M_DC_HANDLE, M_NULL);

		if(BaseFlag == true){
			if(i<2){//if(i<Cam_Cnt){
				str.Format("CAM%d" , (i+1));
				crosslist[i].addList(CAM_SIZE_X/2, CAM_SIZE_Y/2, 300, M_COLOR_GREEN);
				textlist[i].addList(CAM_SIZE_X-200, 10, str, M_COLOR_WHITE, 20, 10, "Arial");

			}else if ( i==CCD )
			{
				crosslist[i].addList(gMIUDevice.nWidth/2, gMIUDevice.nHeight/2, 700, M_COLOR_DARK_MAGENTA);
			}
		}

		pixellist[i].draw(OverlayDC, dReduceFactorX, dReauceFactorY); 
		crosslist[i].draw(OverlayDC, dReduceFactorX, dReauceFactorY);
		boxlist[i].draw(OverlayDC, dReduceFactorX, dReauceFactorY, largeFlag);
		linelist[i].draw(OverlayDC, dReduceFactorX, dReauceFactorY);
		textlist[i].draw(OverlayDC, dReduceFactorX, dReauceFactorY);
		ellipselist[i].draw(OverlayDC, dReduceFactorX, dReauceFactorY);

		MbufControl(MilOverlayImage[i], M_DC_FREE, M_DEFAULT);
 		MbufControl(MilOverlayImage[i], M_MODIFIED, M_DEFAULT);

		::ReleaseDC(NULL, OverlayDC);
#endif
	}
}

//! <------------------------------------------------
//! Added by LHW (2013/2/5)

//! 특정 화면의 사각 영역 색상을 변경
bool CVision::ChangeColor_Box(int iCamNo, COLORREF c)
{
	if ( iCamNo < 0 || iCamNo >= MAX_CAM_NO )
	{
		return false;
	}

	int i = 0;

	for ( i = 0; i < MAX_BOX_CNT; i++ )
	{
		boxlist[iCamNo].c[i] = c;
	}

	return true;
}

//! 모든 화면의 사각 영역 색상을 변경
void CVision::ChangeColor_Box_All(COLORREF c)
{
	int i = 0;

	for ( i = 0; i < MAX_CAM_NO; i++ )
	{
		ChangeColor_Box(i, c);
	}
}

//! <------------------------------------------------

void CVision::drawBase(int iCamNo/* =999 */)
{
	CString Str;
	for (int i=0 ; i<MAX_CAM_NO ; i++)
	{
		if (iCamNo!=999 && i!=iCamNo)
			continue;
		
		if (i==CAM1)
		{
			Str = "TEST";

			textlist[i].addList(16, 10, Str, M_COLOR_WHITE, 20, 13, "Arial");
		}

		linelist[i].addList(0, CAM_SIZE_Y/2, CAM_SIZE_X, CAM_SIZE_Y/2, PS_DOT, M_COLOR_YELLOW);
		linelist[i].addList(CAM_SIZE_X/2, 0, CAM_SIZE_X/2, CAM_SIZE_Y, PS_DOT, M_COLOR_YELLOW);

		Str.Format("CAM %d", i+1);
		textlist[i].addList(CAM_SIZE_X/2-60, 10, Str, M_COLOR_WHITE, 20, 13, "Arial");
	}
}


void CElemPixel::draw(HDC OverlayDC, double dZoomFactorX, double dZoomFactorY)
{
	int i;
	POINT Pixel;

	if(OverlayDC != M_NULL)
	{
		CDC NewDC;

		NewDC.Attach(OverlayDC);
		NewDC.SetBkMode(TRANSPARENT);
		NewDC.SelectStockObject(NULL_BRUSH);

		CPen     m_pen;
		CPen*	 m_penOld;

		for(i=0; i<iCnt; i++)
		{	
			m_pen.CreatePen(PS_SOLID, 1, c[i]); 
			m_penOld = NewDC.SelectObject(&m_pen);

			Pixel.x = (long)(p[i].x * dZoomFactorX + 0.5);
			Pixel.y = (long)(p[i].y * dZoomFactorY + 0.5);

			NewDC.SetPixel(Pixel, c[i]);

			NewDC.SelectObject(m_penOld);
			m_pen.DeleteObject();
		}

		NewDC.Detach();
	}
}

void CElemPixel::addList(int iPosX, int iPosY, COLORREF color)
{
	if (iCnt<MAX_PIXEL_CNT)
	{
		p[iCnt].x = iPosX;
		p[iCnt].y = iPosY;
		c[iCnt] = color;
		iCnt++;
	}
}

void CElemPixel::addList(CPoint Pos, COLORREF color)
{
	if (iCnt<MAX_PIXEL_CNT)
	{
		p[iCnt].x = Pos.x;
		p[iCnt].y = Pos.y;
		c[iCnt] = color;
		iCnt++;
	}
}

void CElemCross::draw(HDC OverlayDC, double dZoomFactorX, double dZoomFactorY)
{
	int i;
	int x, y, w1, w2;

	if(OverlayDC != M_NULL)
	{
		CDC NewDC;

		NewDC.Attach(OverlayDC);
		NewDC.SetBkMode(TRANSPARENT);
		NewDC.SelectStockObject(NULL_BRUSH);

		CPen     m_pen;
		CPen*	 m_penOld;
		
		for(i=0; i<iCnt; i++)
		{	
			m_pen.CreatePen(PS_SOLID, 1, c[i]);
			m_penOld = NewDC.SelectObject(&m_pen);

			w1 = (long)(iSize[i] * dZoomFactorX + 0.5);
			w2 = (long)(iSize[i] * dZoomFactorY + 0.5);
			x = (long)(p[i].x * dZoomFactorX + 0.5);
			y = (long)(p[i].y * dZoomFactorY + 0.5);

			NewDC.MoveTo(x-w1, y);
			NewDC.LineTo(x+w1, y);
			NewDC.MoveTo(x, y-w2);
			NewDC.LineTo(x, y+w2);

			NewDC.SelectObject(m_penOld);
			m_pen.DeleteObject();
		}

		NewDC.Detach();
	}
}

void CElemCross::addList(int iPosX, int iPosY, int w, COLORREF color)
{
	if (iCnt<MAX_CROSS_CNT)
	{
		p[iCnt].x = iPosX;
		p[iCnt].y = iPosY;
		iSize[iCnt] = w;
		c[iCnt] = color;
		iCnt++;
	}
}

void CElemCross::addList(CPoint Pos, int w, COLORREF color)
{
	if (iCnt<MAX_CROSS_CNT)
	{
		p[iCnt].x = Pos.x;
		p[iCnt].y = Pos.y;
		iSize[iCnt] = w;
		c[iCnt] = color;
		iCnt++;
	}
}

void CElemBox::draw(HDC OverlayDC,double dZoomFactorX, double dZoomFactorY, bool largeFlag)
{
	int i;
	int x1, x2, y1, y2;

	if(OverlayDC != M_NULL)
	{
		CDC NewDC;

		NewDC.Attach(OverlayDC);
		NewDC.SetBkMode(TRANSPARENT);
		NewDC.SelectStockObject(NULL_BRUSH);

		CPen     m_pen;
		CPen*	 m_penOld;

		for(i=0; i<iCnt; i++)
		{
			m_pen.CreatePen(iStyle[i], 1, c[i]);
			m_penOld = NewDC.SelectObject(&m_pen);

			if(largeFlag)
			{
				x1 = (long)(r[i].left * dZoomFactorX + 0.5) - 1;
				x2 = (long)(r[i].right * dZoomFactorX + 0.5) + 1;
				y1 = (long)(r[i].top * dZoomFactorY + 0.5) - 1;
				y2 = (long)(r[i].bottom * dZoomFactorY + 0.5) + 1;	
			}
			else
			{
				x1 = (long)(r[i].left * dZoomFactorX + 0.5);
				x2 = (long)(r[i].right * dZoomFactorX + 0.5);
				y1 = (long)(r[i].top * dZoomFactorY + 0.5);
				y2 = (long)(r[i].bottom * dZoomFactorY + 0.5);	
			}
			NewDC.Rectangle(x1, y1, x2, y2);
			NewDC.SelectObject(m_penOld);
			m_pen.DeleteObject();
		}

		NewDC.Detach();
	}
}

void CElemBox::addList(int iLeft,int iTop,int iRight,int iBottom, int iLineStyle, COLORREF color)
{
	if (iCnt<MAX_BOX_CNT)
	{
		r[iCnt].left = iLeft;
		r[iCnt].top = iTop;
		r[iCnt].right = iRight;
		r[iCnt].bottom = iBottom;
		iStyle[iCnt] = iLineStyle;
		c[iCnt] = color;
		iCnt++;
	}
}

void CElemBox::addList(CRect rBox, int iLineStyle, COLORREF color)
{
	if (iCnt<MAX_BOX_CNT)
	{
		r[iCnt] = rBox;
		c[iCnt] = color;
		iStyle[iCnt] = iLineStyle;
		iCnt++;
	}
}

void CElemEllipse::draw(HDC OverlayDC,double dZoomFactorX, double dZoomFactorY)
{
	int i;
	int x1, x2, y1, y2;

	if(OverlayDC != M_NULL)
	{
		CDC NewDC;

		NewDC.Attach(OverlayDC);
		NewDC.SetBkMode(TRANSPARENT);
		NewDC.SelectStockObject(NULL_BRUSH);

		CPen     m_pen;
		CPen*	 m_penOld;

		for(i=0; i<iCnt; i++)
		{
			m_pen.CreatePen(iStyle[i], 1, c[i]);
			m_penOld = NewDC.SelectObject(&m_pen);

			x1 = (long)(cp1[i].x * dZoomFactorX + 0.5);
			x2 = (long)(cp2[i].x * dZoomFactorX + 0.5);
			y1 = (long)(cp1[i].y * dZoomFactorY + 0.5);
			y2 = (long)(cp2[i].y * dZoomFactorY + 0.5);	


			NewDC.Ellipse(x1, y1, x2, y2);
			NewDC.SelectObject(m_penOld);
			m_pen.DeleteObject();
		}

		NewDC.Detach();
	}
}

void CElemEllipse::addList(CPoint pos1,CPoint pos2, int iLineStyle, COLORREF color)
{
	if (iCnt<MAX_BOX_CNT)
	{
		cp1[iCnt].x = pos1.x;
		cp1[iCnt].y = pos1.y;
		cp2[iCnt].x = pos2.x;
		cp2[iCnt].y = pos2.y;

		iStyle[iCnt] = iLineStyle;
		c[iCnt] = color;
		iCnt++;
	}
}

void CElemLine::draw(HDC OverlayDC, double dZoomFactorX, double dZoomFactorY)
{
	int i;
	int x1, x2, y1, y2;

	if(OverlayDC != M_NULL)
	{
		CDC NewDC;

		NewDC.Attach(OverlayDC);
		NewDC.SetBkMode(TRANSPARENT);
		NewDC.SelectStockObject(NULL_BRUSH);

		CPen     m_pen;
		CPen*	 m_penOld;

		for(i=0; i<iCnt; i++)
		{	
			m_pen.CreatePen(iStyle[i], 1, c[i]); 
			m_penOld = NewDC.SelectObject(&m_pen);

			x1 = (long)(sp[i].x * dZoomFactorX + 0.5);
			y1 = (long)(sp[i].y * dZoomFactorY + 0.5);
			x2 = (long)(ep[i].x * dZoomFactorX + 0.5);
			y2 = (long)(ep[i].y * dZoomFactorY + 0.5);	

			NewDC.MoveTo(x1, y1);
			NewDC.LineTo(x2, y2);

			NewDC.SelectObject(m_penOld);
			m_pen.DeleteObject();
		}

		NewDC.Detach();
	}
}

void CElemLine::addList(int iSx,int iSy,int iEx,int iEy,int iLineStyle, COLORREF color)
{
	if (iCnt<MAX_LINE_CNT)
	{
		sp[iCnt].x = iSx;
		sp[iCnt].y = iSy;
		ep[iCnt].x = iEx;
		ep[iCnt].y = iEy;
		iStyle[iCnt] = iLineStyle;
		c[iCnt] = color;
		iCnt++;
	}
}

void CElemText::draw(HDC OverlayDC, double dZoomFactorX, double dZoomFactorY)
{
	int i;
	int x, y;

	char tmpChar[256];

	if(OverlayDC != M_NULL)
	{
		CDC NewDC;

		NewDC.Attach(OverlayDC);
		NewDC.SetBkMode(TRANSPARENT);
		NewDC.SelectStockObject(NULL_BRUSH);

		CFont font, *oldfont;

		for(i=0; i<iCnt; i++)
		{
			font.CreateFont(s[i].x, s[i].y, 0, 0,
				FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
				CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, FontName[i]);

			oldfont = NewDC.SelectObject(&font);

			NewDC.SetTextColor(c[i]);

			x  = (long)(p[i].x * dZoomFactorX + 0.5);
			y  = (long)(p[i].y * dZoomFactorY + 0.5);

			sprintf_s(tmpChar, str[i], 256);	

			NewDC.TextOut(x, y, tmpChar, MOs_strlen(tmpChar));

			NewDC.SelectObject(oldfont);
			font.DeleteObject();
		}

		NewDC.Detach();
	}
}

void CElemText::addList(int iPosX, int iPosY, CString Str, COLORREF color, int iSizeX, int iSizeY, CString FontStr)
{
	if (iCnt<MAX_TEXT_CNT)
	{
		p[iCnt].x = iPosX;
		p[iCnt].y = iPosY;
		str[iCnt] = Str;
		c[iCnt] = color;
		s[iCnt].x = iSizeX;
		s[iCnt].y = iSizeY;
		FontName[iCnt] = FontStr;
		iCnt++;
	}
}

void CVision::geometricMarkPreProc(int iCamNo, int iMarkType, int iMarkNo)
{
	MmodControl(ModModel[iMarkType][iMarkNo], M_CONTEXT, M_SEARCH_POSITION_RANGE, M_ENABLE);
	MmodControl(ModModel[iMarkType][iMarkNo], M_CONTEXT, M_SEARCH_ANGLE_RANGE, M_ENABLE);
	MmodControl(ModModel[iMarkType][iMarkNo], M_CONTEXT, M_SEARCH_SCALE_RANGE, M_ENABLE);

	MmodControl(ModModel[iMarkType][iMarkNo], M_CONTEXT, M_NUMBER, 1);
	MmodControl(ModModel[iMarkType][iMarkNo], M_CONTEXT, M_SPEED, M_MEDIUM);
	MmodControl(ModModel[iMarkType][iMarkNo], M_CONTEXT, M_ACCURACY, M_MEDIUM);

	MmodControl(ModModel[iMarkType][iMarkNo], M_CONTEXT, M_SHARED_EDGES, M_DISABLE);
	MmodControl(ModModel[iMarkType][iMarkNo], M_CONTEXT, M_ASPECT_RATIO, 1.0);
	MmodControl(ModModel[iMarkType][iMarkNo], M_CONTEXT, M_SAVE_TARGET_EDGES, M_DISABLE);
	MmodControl(ModModel[iMarkType][iMarkNo], M_CONTEXT, M_TARGET_CACHING, M_DISABLE);

	if(iCamNo==0)		sysData.m_iSmoothness[0] = 80;
	else				sysData.m_iSmoothness[1] = 80;


 	MmodControl(ModModel[iMarkType][iMarkNo], M_CONTEXT, M_SMOOTHNESS, sysData.m_iSmoothness[iCamNo]);
	MmodControl(ModModel[iMarkType][iMarkNo], M_CONTEXT, M_DETAIL_LEVEL, M_MEDIUM);
	MmodControl(ModModel[iMarkType][iMarkNo], M_CONTEXT, M_FILTER_MODE, M_RECURSIVE);

	MmodControl(ModModel[iMarkType][iMarkNo], M_DEFAULT, M_ANGLE, 0);
	MmodControl(ModModel[iMarkType][iMarkNo], M_DEFAULT, M_ANGLE_DELTA_NEG, 5);
	MmodControl(ModModel[iMarkType][iMarkNo], M_DEFAULT, M_ANGLE_DELTA_POS, 5);


	MmodControl(ModModel[iMarkType][iMarkNo], M_DEFAULT, M_SCALE, 1.0);
	MmodControl(ModModel[iMarkType][iMarkNo], M_DEFAULT, M_SCALE_MIN_FACTOR, 0.99);
	MmodControl(ModModel[iMarkType][iMarkNo], M_DEFAULT, M_SCALE_MAX_FACTOR, 1.01);


	MmodControl(ModModel[iMarkType][iMarkNo], M_DEFAULT, M_NUMBER, 1);
	MmodControl(ModModel[iMarkType][iMarkNo], M_DEFAULT, M_ACCEPTANCE, 75);
	MmodControl(ModModel[iMarkType][iMarkNo], M_DEFAULT, M_ACCEPTANCE_TARGET, 0);
	MmodControl(ModModel[iMarkType][iMarkNo], M_DEFAULT, M_CERTAINTY, 40);
	MmodControl(ModModel[iMarkType][iMarkNo], M_DEFAULT, M_CERTAINTY_TARGET, 0);

	MmodControl(ModResult[iMarkType][iMarkNo], M_DEFAULT, M_DRAW_SCALE_X, CAM_REDUCE_FACTOR_X);
	MmodControl(ModResult[iMarkType][iMarkNo], M_DEFAULT, M_DRAW_SCALE_Y, CAM_REDUCE_FACTOR_Y);

 	MmodPreprocess(ModModel[iMarkType][iMarkNo], M_DEFAULT);
}


bool CVision::markRegist(int iCamNo, int iMarkType, int iMarkNo, CRect rBox)
{
	if (iCamNo>CAM2)
	{
		sLangChange.LoadStringA(IDS_STRING1378);
		::errMsg2(Task.AutoFlag, sLangChange);
		return false;
	}

	int iSizeX = rBox.right - rBox.left;
	int iSizeY = rBox.bottom - rBox.top;

	if (iSizeX<=0 || iSizeY<=0 || iSizeX>=CAM_SIZE_X || iSizeY>=CAM_SIZE_Y)
	{
		sLangChange.LoadStringA(IDS_STRING1377);
		errMsg2(Task.AutoFlag, sLangChange);	//"잘못된 영역입니다."
		return false;
	}

	if(iSizeX < 30 || iSizeY < 30)
	{
		sLangChange.LoadStringA(IDS_STRING1205);
		errMsg2(Task.AutoFlag, sLangChange);	//"등록 박스 사이즈가 너무 작습니다."
		return false;
	}
	MbufClear(MilTempImage, 0);

#ifdef USE_GEOMETRIC
	if (ModModel[iMarkType][iMarkNo])
	{
		MmodFree(ModModel[iMarkType][iMarkNo]);
		ModModel[iMarkType][iMarkNo] = M_NULL;
	}

	MmodAlloc(MilSystem, M_GEOMETRIC, M_DEFAULT, &ModModel[iMarkType][iMarkNo]);
	//MmodDefine(ModModel[iMarkType][iMarkNo], M_IMAGE, MilProcImageChild[iCamNo], rBox.left, rBox.top, iSizeX, iSizeY);


	MmodDefine(ModModel[iMarkType][iMarkNo], M_IMAGE, MilProcImageChild[iCamNo], rBox.left, rBox.top, iSizeX, iSizeY);

	MmodDraw(M_DEFAULT, ModModel[iMarkType][iMarkNo], MilTempImage, M_DRAW_IMAGE, M_DEFAULT, M_DEFAULT);

	MmodControl(ModModel[iMarkType][iMarkNo], M_DEFAULT, M_REFERENCE_X, iSizeX/2);
	MmodControl(ModModel[iMarkType][iMarkNo], M_DEFAULT, M_REFERENCE_Y, iSizeY/2);
#else
	if (PatModel[iMarkType][iMarkNo])
	{
		MpatFree(PatModel[iMarkType][iMarkNo]);
		PatModel[iMarkType][iMarkNo] = M_NULL;
	}

	MpatAllocModel(MilSystem, MilGrabImageChild[iCamNo], rBox.left, rBox.top, iSizeX, iSizeY, M_NORMALIZED, &PatModel[iMarkType][iMarkNo]);
//	MpatAllocModel(MilSystem, MilGrabImageChild[iCamNo], rBox.left, rBox.top, iSizeX, iSizeY, M_NORMALIZED+M_CIRCULAR_OVERSCAN, &PatModel[iMarkType][iMarkNo]);
//	MpatSetAngle(PatModel[iMarkType][iMarkNo], M_SEARCH_ANGLE, M_DEFAULT);
	MpatDraw(M_DEFAULT, PatModel[iMarkType][iMarkNo], MilTempImage, M_DRAW_IMAGE, M_DEFAULT, M_DEFAULT);
#endif

	return true;
}

void CVision::loadImage(int iCamNo, CString DirStr)
{
	if (iCamNo==CCD)
	{
		CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
		if ( pFrame == NULL )
		{
			return;
		}

		MbufClear(MilProcImage[1], 0x00);
		MbufImport(DirStr.GetBuffer(999), M_DEFAULT, M_LOAD, MilSystem, &MilProcImage[1]);
		MbufCopy(MilProcImage[1], MilGrabImage[1]);

		m_dReduceFactorX = (double)SMALL_CCD_SIZE_X / gMIUDevice.nWidth;
		m_dReduceFactorY = (double)SMALL_CCD_SIZE_Y / gMIUDevice.nHeight;
		
		//! 이물 검사 화면에서의 확대/Pan 기능 초기화
		pFrame->m_bBox_Acting_CCD_Zoom = false;
		pFrame->m_bActing_CCD_Zoom = false;
		pFrame->m_bPan_CCD_Zoom = false;
		pFrame->m_bActing_Pan_CCD_Zoom = false;
		pFrame->m_bState_CCD_Zoom = false;
		pFrame->m_rect_CCD_Zoom.SetRectEmpty();
		
		g_iCCDCamView = 5;	//! Added by LHW (2013/3/27)
		MimResize(MilProcImage[1], MilSmallImage[1], m_dReduceFactorX, m_dReduceFactorY, M_DEFAULT);
	}
	else
	{
		m_csGrab.Lock();

		MbufImport(DirStr.GetBuffer(999), M_DEFAULT, M_LOAD, MilSystem, &MilProcImageChild[iCamNo]);
		MbufCopy(MilProcImageChild[iCamNo], MilGrabImageChild[iCamNo]);
		MimResize(MilProcImageChild[iCamNo], MilSmallImageChild[iCamNo], CAM_REDUCE_FACTOR_X, CAM_REDUCE_FACTOR_Y, M_DEFAULT);

		m_csGrab.Unlock();
	}
}
void CVision::bmpImageSaveFn(int iCamNo, int index)
{
	CFileFind finder;
	BOOL IsFind;
	CString FolderName;
	SYSTEMTIME time;
	::GetLocalTime(&time);
	FolderName.Format("%s\\%s\\%04d%02d\\Epoxy", IMAGE_BASE_DIR, model.mCurModelName, time.wYear, time.wMonth);

	IsFind = finder.FindFile(FolderName);
	if (!IsFind)
	{
		FolderName.Format("%s", BASE_DIR);
		IsFind = finder.FindFile(FolderName);
		if (!IsFind)
		{
			CreateDirectory(FolderName, NULL);
		}

		FolderName.Format("%s", BASE_LOG_DIR);
		IsFind = finder.FindFile(FolderName);
		if (!IsFind)
		{
			CreateDirectory(FolderName, NULL);
		}

		FolderName.Format("%s", IMAGE_BASE_DIR);
		IsFind = finder.FindFile(FolderName);
		if (!IsFind)
		{
			CreateDirectory(FolderName, NULL);
		}

		FolderName.Format("%s\\%s", IMAGE_BASE_DIR, model.mCurModelName);
		IsFind = finder.FindFile(FolderName);
		if (!IsFind)
		{
			CreateDirectory(FolderName, NULL);
		}
		FolderName.Format("%s\\%s\\%04d%02d", IMAGE_BASE_DIR, model.mCurModelName, time.wYear, time.wMonth);
		IsFind = finder.FindFile(FolderName);
		if (!IsFind)
		{
			CreateDirectory(FolderName, NULL);
		}

		FolderName.Format("%s\\%s\\%04d%02d\\Epoxy", IMAGE_BASE_DIR, model.mCurModelName, time.wYear, time.wMonth);
		CreateDirectory(FolderName, NULL);
	}




	CString FilePath;
	// _stprintf_s(szFilePath, SIZE_OF_1K, _T("%s\\%s_%s_%d_%02d%02d%02d%03d.raw"), szPath, Task.ChipID, (LPTSTR)(LPCTSTR)nType, gMIUDevice.dTDATASPEC_n.eDemosaicMethod, stSysTime.wHour, stSysTime.wMinute, stSysTime.wSecond, stSysTime.wMilliseconds);

	FilePath.Format(_T("%s\\%s_%02d%02d%02d.bmp"), FolderName, Task.ChipID, time.wHour, time.wMinute, time.wSecond);
	MbufExport(FilePath, M_BMP, MilGrabImageChild[iCamNo]);
}

void CVision::saveImage(int iCamNo, CString DirStr)
{
	if(iCamNo<CCD)
	{
		MbufExport(DirStr.GetBuffer(999), M_BMP, MilGrabImageChild[iCamNo]);
	}else
	{
		vision.MilBufferUpdate();
		MbufExport(DirStr.GetBuffer(999), M_BMP, MilGrabImage[1]);
	}
}

void CVision::loadImageonExplorer(int iCamNo)
{
	char tmpStr[1000];
	CString FileName;

	//sprintf_s(buf, sizeof(buf), "문자 = %0.3f\n", num);
	sprintf_s(tmpStr, sizeof(tmpStr) , "*.*");//sprintf_s(tmpStr,"", 999);//
	CFileDialog* fileOpenDialog= NULL;
	fileOpenDialog = new CFileDialog(TRUE, "jpg", _T(tmpStr), OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, "Image Files (*.jpg)|*.jpg|");

	if(fileOpenDialog)
	{
		if(fileOpenDialog->DoModal() == IDOK)
		{
			FileName = fileOpenDialog->GetPathName();

			setLiveMode(0);

			if (iCamNo == 3)
			{
				if(gMIUDevice.CurrentState > 2)
				{
					gMIUDevice.CurrentState = 2;		// 영상 획득 정지
				}
			}

			loadImage(iCamNo, FileName);
		}

		delete fileOpenDialog;
	}	
}

void CVision::saveImageonExplorer(int iCamNo)
{
	char tmpStr[1000];
	CString FileName;

	if(iCamNo==3)
	{
		if ( gMIUDevice.CurrentState > 3 )
			gMIUDevice.CurrentState = 3;
	}
	else
	{
		setLiveMode(0);
	}

	sprintf_s(tmpStr,"");
	CFileDialog* fileSaveDialog= NULL;
	fileSaveDialog = new CFileDialog(FALSE, "*.bmp" , _T(tmpStr), /*OFN_OVERWRITEPROMPT | */OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,"Image Files(*.bmp)|*.bmp|");

	if(fileSaveDialog)
	{
		if(fileSaveDialog->DoModal() == IDOK)
		{
			FileName = fileSaveDialog->GetPathName();
			saveImage(iCamNo, FileName);
		}

		delete fileSaveDialog;
	}
}


int CVision::patternMatching(int iSearchMode, int iCh, int iMarkType, int iMarkNo, CDPoint& Center, double& dRate, double& dAngle)
{
	CRect rcArea;

	if (PatModel[iMarkType][iMarkNo]==M_NULL)
	{
		Center.x = CAM_SIZE_X>>1;
		Center.y = CAM_SIZE_Y>>1;
		dRate = 0.0;

		return FIND_ERR;
	}

	if (iSearchMode==0)
	{
		rcArea.left		=	0;
		rcArea.top		=	0;
		if (iCh < Cam_Cnt)
		{
			rcArea.right	=	CAM_SIZE_X-1;
			rcArea.bottom	=	CAM_SIZE_Y-1;
		}
	}
	else if (iSearchMode==1)
	{
		rcArea.left		=	(int)(CAM_SIZE_X*0.35 + 0.5);
		rcArea.top		=	5;
		rcArea.right	=	(int)(CAM_SIZE_X*0.65 + 0.5);
		rcArea.bottom	=	(int)(CAM_SIZE_Y*0.35 + 0.5);
	}
	else if (iSearchMode==2)
	{
		rcArea.left		=	(int)(CAM_SIZE_X*0.35 + 0.5);
		rcArea.top		=	(int)(CAM_SIZE_Y*0.65 + 0.5);
		rcArea.right	=	(int)(CAM_SIZE_X*0.65 + 0.5);
		rcArea.bottom	=	CAM_SIZE_Y - 5;
	}
	else if (iSearchMode==3)
	{
		rcArea.left		=	5;
		rcArea.top		=	(int)(CAM_SIZE_Y*0.35 + 0.5);
		rcArea.right	=	(int)(CAM_SIZE_X*0.3 + 0.5);
		rcArea.bottom	=	(int)(CAM_SIZE_Y*0.65 + 0.5);
	}
	else if (iSearchMode==4)
	{
		rcArea.left		=	(int)(CAM_SIZE_X*0.7 + 0.5);
		rcArea.top		=	(int)(CAM_SIZE_Y*0.35 + 0.5);
		rcArea.right	=	CAM_SIZE_X-5;
		rcArea.bottom	=	(int)(CAM_SIZE_Y*0.65 + 0.5);
	}

	MpatSetPosition(PatModel[iMarkType][0], rcArea.left, rcArea.top, (rcArea.right-rcArea.left), (rcArea.bottom-rcArea.top));
	MpatSetAcceptance(PatModel[iMarkType][iMarkNo], 30);
	MpatSetAccuracy(PatModel[iMarkType][iMarkNo], M_HIGH);
	MpatSetCertainty(PatModel[iMarkType][iMarkNo], 80);
	MpatSetNumber(PatModel[iMarkType][iMarkNo], 1L);
	MpatSetSpeed(PatModel[iMarkType][iMarkNo], M_HIGH);
	MpatSetSearchParameter(PatModel[iMarkType][iMarkNo], M_FAST_FIND, M_DISABLE);

	MpatPreprocModel(MilProcImageChild[iCh], PatModel[iMarkType][iMarkNo], M_DEFAULT);
	MpatFindModel(MilProcImageChild[iCh], PatModel[iMarkType][iMarkNo], PatResult[iMarkType][iMarkNo]);

	long lObjNum = MpatGetNumber(PatResult[iMarkType][iMarkNo], M_NULL);

	if(lObjNum > 0)
	{
		MpatGetResult(PatResult[iMarkType][iMarkNo], M_POSITION_X, &Center.x);
		MpatGetResult(PatResult[iMarkType][iMarkNo], M_POSITION_Y, &Center.y);
		MpatGetResult(PatResult[iMarkType][iMarkNo], M_ANGLE, &dAngle);
		MpatGetResult(PatResult[iMarkType][iMarkNo], M_SCORE, &dRate);
	}
	else
	{
		Center.x = CAM_SIZE_X>>1;
		Center.y = CAM_SIZE_Y>>1;
		dRate = 0.0;

		return FIND_ERR;
	}

	if (dRate<50)	return RATE_ERR;

	return FIND_OK;
}

int CVision::geometricModelFinder(int iSearchMode, int iCh, int iMarkType, int iMarkNo, CDPoint& Center, double& dRate, double& dAngle)
{
	CString logStr;
	int iRealCamNo = iCh;
	CRect rcArea;

	if (ModModel[iMarkType][iMarkNo]==M_NULL)
	{
		Center.x = CAM_SIZE_X>>1;
		Center.y = CAM_SIZE_Y>>1;
		dRate = 0.0;

		return FIND_ERR;
	}


	if (iSearchMode==0)
	{//전체 화면
		rcArea.left		=	0;//vision.rcFindROI[iCh][iMarkType].left;//
		rcArea.top		=	0; //vision.rcFindROI[iCh][iMarkType].top;//
		if (iCh < Cam_Cnt)
		{
			rcArea.right	=	CAM_SIZE_X-1;//vision.rcFindROI[iCh][iMarkType].right-1;//
			rcArea.bottom	=	CAM_SIZE_Y-1;//vision.rcFindROI[iCh][iMarkType].bottom-1;//
		}
	}
	else if (iSearchMode==1)
	{
		rcArea.left		=	(int)(CAM_SIZE_X*0.35 + 0.5);
		rcArea.top		=	5;
		rcArea.right	=	(int)(CAM_SIZE_X*0.65 + 0.5);
		rcArea.bottom	=	(int)(CAM_SIZE_Y*0.35 + 0.5);
	}
	else if (iSearchMode==2)
	{
		rcArea.left		=	(int)(CAM_SIZE_X*0.35 + 0.5);
		rcArea.top		=	(int)(CAM_SIZE_Y*0.65 + 0.5);
		rcArea.right	=	(int)(CAM_SIZE_X*0.65 + 0.5);
		rcArea.bottom	=	CAM_SIZE_Y - 5;
	}
	else if (iSearchMode==3)
	{
		rcArea.left		=	5;
		rcArea.top		=	(int)(CAM_SIZE_Y*0.35 + 0.5);
		rcArea.right	=	(int)(CAM_SIZE_X*0.3 + 0.5);
		rcArea.bottom	=	(int)(CAM_SIZE_Y*0.65 + 0.5);
	}
	else if (iSearchMode==4)
	{
		rcArea.left		=	(int)(CAM_SIZE_X*0.7 + 0.5);
		rcArea.top		=	(int)(CAM_SIZE_Y*0.35 + 0.5);
		rcArea.right	=	CAM_SIZE_X-5;
		rcArea.bottom	=	(int)(CAM_SIZE_Y*0.65 + 0.5);
	}

//	geometricMarkPreProc(iCh , iCamNo);

	MmodControl(ModModel[iMarkType][iMarkNo], M_DEFAULT, M_SEARCH_OFFSET_X,	rcArea.left);
	MmodControl(ModModel[iMarkType][iMarkNo], M_DEFAULT, M_SEARCH_OFFSET_Y,	rcArea.top);
	MmodControl(ModModel[iMarkType][iMarkNo], M_DEFAULT, M_SEARCH_SIZE_X,	rcArea.right - rcArea.left);
	MmodControl(ModModel[iMarkType][iMarkNo], M_DEFAULT, M_SEARCH_SIZE_Y,	rcArea.bottom - rcArea.top);

	MmodFind(ModModel[iMarkType][iMarkNo], MilProcImageChild[iCh], ModResult[iMarkType][iMarkNo]);
 
	long lObjNum;
	MmodGetResult(ModResult[iMarkType][iMarkNo], M_DEFAULT, M_NUMBER+M_TYPE_LONG, &lObjNum);

	if(lObjNum > 0)
	{
		MmodGetResult(ModResult[iMarkType][iMarkNo], M_DEFAULT, M_POSITION_X, &Center.x);
		MmodGetResult(ModResult[iMarkType][iMarkNo], M_DEFAULT, M_POSITION_Y, &Center.y);
		MmodGetResult(ModResult[iMarkType][iMarkNo], M_DEFAULT, M_ANGLE, &dAngle);
		MmodGetResult(ModResult[iMarkType][iMarkNo], M_DEFAULT, M_SCORE, &dRate);

		g_dFindCenterX[iMarkType]	= Center.x;
		g_dFindCenterY[iMarkType]	= Center.y;
		g_dFindAngle[iMarkType]	= dAngle;
		
		if (g_dFindAngle[iMarkType]>180.0)	g_dFindAngle[iMarkType] -= 360.0;
	}
	else
	{
		Center.x = CAM_SIZE_X>>1;
		Center.y = CAM_SIZE_Y>>1;
		dRate = 0.0;

		if(iMarkType==1)
		{
			sLangChange.LoadStringA(IDS_STRING1215);
			logStr.Format("   iMarkNo %d, 마크 인식 실패.", iMarkNo);
			AlignLogSave(logStr);
		}

		return FIND_ERR;
	}
	//model.m_MarkMatchingRate
	int markType = iMarkType;
	if(sysData.m_iProductComp == 1)
	{
		markType = 3;
	}
	if (dRate<model.m_MarkMatchingRate[markType])//if (dRate<model.m_iLimitRate[iMarkType][iMarkNo])
	{
		if(iMarkType==1)
		{
			sTempLang.Format( "iMarkNo %d, 마크 인식 매칭율 NG %lf.", iMarkNo, dRate);
			logStr.Format(_T("---------->> ")	+ sTempLang);
			AlignLogSave(logStr);
		}
		return RATE_ERR;
	}
	Task.d_Holder_Th = g_dFindAngle[iMarkType];
	return FIND_OK;
}

void CVision::drawResolResult(int iCamNo, int iSizeX, int iSizeY, CDPoint Center, int iResult)
{
	int iRealCamNo;

	COLORREF colorResult;

	if (iResult==FIND_OK)	colorResult = M_COLOR_GREEN;
	else					colorResult = M_COLOR_RED;

	CRect rTemp1, rTemp2;

	iRealCamNo = iCamNo;

// 	if (iCamNo==CAM3)
// 		iCamNo = CAM2;

	int iMarkSizeX = iSizeX;
	int iMarkSizeY = iSizeY;
	int iMarkCenterX = (int)(Center.x + 0.5);
	int iMarkCenterY = (int)(Center.y + 0.5);

	int iFindCenterX = (int)(Center.x+0.5);
	int iFindCenterY = (int)(Center.y+0.5);

	rTemp1.left = iFindCenterX - iMarkSizeX/2;
	rTemp1.top = iFindCenterY - iMarkSizeY/2;
	rTemp1.right = rTemp1.left + iMarkSizeX;
	rTemp1.bottom = rTemp1.top + iMarkSizeY;

	if (iResult!=NOMARK)
	{
		boxlist[iRealCamNo].addList(rTemp1, PS_SOLID, colorResult);
		crosslist[iRealCamNo].addList(iFindCenterX, iFindCenterY, 40, colorResult);
	}

	CString strResult;

	sTempLang.LoadStringA(IDS_STRING763);
	sLangChange.Format(sTempLang, Center.x, Center.y);
	strResult.Format(sLangChange);
	textlist[iRealCamNo].addList(15, 20, strResult, M_COLOR_YELLOW, 17, 10, _T("arialuni"));

	CAABonderDlg* pFrmae = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	pFrmae->putListLog(strResult);
}


void CVision::drawResult(int iCamNo, int iMarkNo, CDPoint Center, double dRate, double dAngle, int iResult)
{
	COLORREF colorResult;

	if (iResult==FIND_OK)	colorResult = M_COLOR_GREEN;
	else					colorResult = M_COLOR_RED;

	CRect rTemp1, rTemp2;
	int iMarkSizeX = model.m_MarkSize[iCamNo][iMarkNo].x;
	int iMarkSizeY = model.m_MarkSize[iCamNo][iMarkNo].y;
	int iMarkCenterX = (int)(model.m_MarkCenter[iCamNo][iMarkNo].x+0.5);
	int iMarkCenterY = (int)(model.m_MarkCenter[iCamNo][iMarkNo].y+0.5);

// 	int iMarkOriginX	=	(int)(model.m_MarkOrigin[iCamNo][iMarkNo].x + 0.5);
// 	int iMarkOriginY	=	(int)(model.m_MarkOrigin[iCamNo][iMarkNo].y + 0.5);

	int iFindCenterX = (int)(Center.x+0.5);
	int iFindCenterY = (int)(Center.y+0.5);

	rTemp1.left = iFindCenterX - iMarkCenterX;
	rTemp1.top = iFindCenterY - iMarkCenterY;
	rTemp1.right = rTemp1.left + iMarkSizeX;
	rTemp1.bottom = rTemp1.top + iMarkSizeY;

// 	rTemp2.left = iMarkOriginX - iMarkCenterX;
// 	rTemp2.top = iMarkOriginY - iMarkCenterY;
// 	rTemp2.right = rTemp2.left + iMarkSizeX;
// 	rTemp2.bottom = rTemp2.top + iMarkSizeY;

	if (iResult!=NOMARK)
	{
#ifndef USE_GEOMETRIC
		boxlist[iCamNo].addList(rTemp1, PS_SOLID, colorResult);
		crosslist[iCamNo].addList(iFindCenterX, iFindCenterY, 40, colorResult);
#endif

// 		boxlist[iCamNo].addList(rTemp2, PS_SOLID, M_COLOR_BLUE);
// 		crosslist[iCamNo].addList(iMarkOriginX, iMarkOriginY, 40, M_COLOR_BLUE);
	}

	CString strResult;

	strResult.Format("Mark #%d [ %.2f %.2f ]", iMarkNo+1, Center.x, Center.y);
//	if (iMarkNo==0)
		textlist[iCamNo].addList(15, 20, strResult, M_COLOR_GREEN, 17, 7, "Arial");
// 	else if (iMarkNo==1)
// 		textlist[iCamNo].addList((CAM_SIZE_X-150), 20, strResult, M_COLOR_YELLOW, 17, 7, "Arial");

	strResult.Format("%.1f", dRate);
//	if (iMarkNo==0)
		textlist[iCamNo].addList(10, 40, strResult, M_COLOR_GREEN, 27, 12, "Arial Black");
// 	else if (iMarkNo==1)
// 		textlist[iCamNo].addList((CAM_SIZE_X-100), 40, strResult, M_COLOR_WHITE, 27, 12, "Arial Black");

	if(dAngle>180)		dAngle -= 360.0;

	if (fabs(dAngle)>360)
	{
		sLangChange.LoadStringA(IDS_STRING1458);
		strResult.Format(sLangChange);
	}
	else
	{
		sTempLang.LoadStringA(IDS_STRING1459);
		sLangChange.Format(sTempLang, dAngle);
		strResult.Format(sLangChange);
	}

	textlist[iCamNo].addList(15, 80, strResult, M_COLOR_GREEN, 17, 7, "Arial");
}

int CVision::findComAlignMark(int iCamNo, int iMarkType, bool flag)
{
	CString markStr;
	
//	int i;
//	int iIndex;
	int iRtn;

	CDPoint Center;
	double dRate = 0.0;
	double dAngle = 0.0;
	int markNum = 1;

	if (model.m_MarkSize[iMarkType][markNum].x<=0 ||model.m_MarkSize[iMarkType][markNum].y<=0){
		iRtn = NOMARK;
	}else
	{
		iRtn = geometricModelFinder(0, iCamNo, iMarkType, markNum, Center, dRate, dAngle);
	}

	drawResult(iCamNo, markNum, Center, dRate, dAngle, iRtn);

	if (iRtn==FIND_OK){
		return 1;
	}else
	{
		sLangChange.LoadStringA(IDS_STRING1454);
		textlist[iCamNo].addList(200, CAM_SIZE_Y-100, sLangChange, M_COLOR_RED, 24, 12, _T("arialuni"));
		return -1;
	}
}

int CVision::findMark(int iCamNo, int iMarkType, bool flag)
{
	CString strResult;

	int i;
	int iIndex;
	int iRtn[2];

	CDPoint Center[2];
	double dRate[2];
	double dAngle[2];
	int markIndex = 2;
	if(iMarkType == PCB_Chip_MARK)
	{
		markIndex =1;
	}
	for (i=0 ; i<markIndex ; i++)
	{
		if (model.m_MarkSize[iMarkType][i].x<=0 ||model.m_MarkSize[iMarkType][i].y<=0)
			iRtn[i] = NOMARK;
		else
		{
			#ifdef USE_GEOMETRIC
						iRtn[i] = geometricModelFinder(0, iCamNo, iMarkType, i, Center[i], dRate[i], dAngle[i]);
			#else
						iRtn[i] = patternMatching(0, iCamNo, iMarkType, i, Center[i], dRate[i], dAngle[i]);
			#endif
		}

		if (iRtn[i]==FIND_OK)
		{
			iIndex = i;
			Task.d_mark_pos_x[iMarkType][i]	= Center[i].x;
			Task.d_mark_pos_y[iMarkType][i]	= Center[i].y;
			break;
		}
	}

	if (i < markIndex)
		drawResult(iCamNo, iIndex, Center[iIndex], dRate[iIndex], dAngle[iIndex], iRtn[iIndex]);

	if(flag)
	{
		Task.b_mark_result[iMarkType] = false;

		if (iRtn[0]==FIND_OK || iRtn[1]==FIND_OK)
			Task.b_mark_result[iMarkType] = true;

		for(int i=0; i<markIndex; i++)
		{
			Task.d_mark_pos_x[iMarkType][i]	= Center[i].x;
			Task.d_mark_pos_y[iMarkType][i]	= Center[i].y;
			Task.d_mark_theta[iMarkType][i]	= dAngle[i];
			Task.d_mark_rate[iMarkType][i]	= dRate[i];
		}
	}

	if (iRtn[0]==FIND_OK || iRtn[1]==FIND_OK)
		return iIndex;
	else
	{
		sLangChange.LoadStringA(IDS_STRING1454);
		textlist[iCamNo].addList(200, CAM_SIZE_Y-100, sLangChange, M_COLOR_RED, 24, 12, _T("arialuni"));
		return -1;
	}
}

#ifdef  _M_X64
	LONG64 MFTYPE ProcessingFunction(LONG64 HookType, MIL_ID HookId, void MPTYPE *HookDataPtr)
#else 
	long MFTYPE ProcessingFunction(long HookType, MIL_ID HookId, void MPTYPE *HookDataPtr)
#endif

{
	HookDataStruct *UserHookDataPtr = (HookDataStruct *)HookDataPtr;
	MIL_ID ModifiedBufferId;

	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	g_GrabEvent.SetEvent();
	MdigGetHookInfo(HookId, M_MODIFIED_BUFFER+M_BUFFER_ID, &ModifiedBufferId);

	if(UserHookDataPtr->liveMode)
	{
		vision.m_acsAlignGrabLock.Lock();

		MbufCopy(ModifiedBufferId, vision.MilGrabImage[0]);
		//MimFlip(vision.MilGrabImageChild[1], vision.MilGrabImageChild[1], M_HORIZONTAL, M_DEFAULT);
		MimResize(vision.MilGrabImage[0], UserHookDataPtr->MilSmallImage, CAM_REDUCE_FACTOR_X, CAM_REDUCE_FACTOR_Y, M_DEFAULT);

		vision.m_acsAlignGrabLock.Unlock();
	}

	return 0;
}


void CVision::getSnapImage(int camNo)
{
	setLiveMode(true);
 //#ifdef		ON_LINE_VISION
 //	g_GrabEvent.Lock();		// Snap 명령 시 기존 찍고 있던 영상은 버리고 새로 영상 획득..
 //	g_GrabEvent.Lock();
 //	g_GrabEvent.Lock();
 //#endif
//	m_acsAlignGrabLock.Lock();
	m_csGrab.Lock();
	if(camNo<3) 
	{
		MbufCopy(MilGrabImageChild[camNo], MilProcImageChild[camNo]);
	}
	else
		MbufCopy(MilGrabImage[0], MilProcImage[0]);				// 1,2,3 카메라 전부 영상 복사

	m_csGrab.Unlock();
//	m_acsAlignGrabLock.Unlock();
}



void CVision::MiuBufferFree()
{
	int i, index;

	for (i=0; i < 3; i++)
	{	
		index = Cam_Cnt + i;

		if (MilImageBuffer[index])
		{
			GlobalUnlock(MilImageBuffer[index]);
			
		}

		if (MilGrabImageChild[index])
		{
			MbufFree(MilGrabImageChild[index]);
			MilGrabImageChild[index] = M_NULL;
		}

		if (MilProcImageChild[index])
		{
			MbufFree(MilProcImageChild[index]);
			MilProcImageChild[index] = M_NULL;
		}
	}

	
	
	if (MilGrabImage[1])
	{
		MbufFree(MilGrabImage[1]);
		MilGrabImage[1] = M_NULL;
	}

	if (MilProcImage[1])
	{
		MbufFree(MilProcImage[1]);
		MilProcImage[1] = M_NULL;
	}


	for ( i = 0; i < iBufSize_Bayer; i++ )
	{
		if ( MilBayerImage[i] != M_NULL )
		{
			MbufFree(MilBayerImage[i]);
			MilBayerImage[i] = M_NULL;
		}
	}



}
void CVision::MiuCCdBufferReset()
{
	int i = 0;
	if (MilGrabImage[1])
	{
		MbufFree(MilGrabImage[1]);
		MilGrabImage[1] = M_NULL;
	}
	for (i = 0; i < Cam_Cnt; i++)
	{
		if (MilGrabImageChild[Cam_Cnt + i])
		{
			MbufFree(MilGrabImageChild[Cam_Cnt + i]);
			MilGrabImageChild[Cam_Cnt + i] = M_NULL;

		}
	}
	if (MilProcImage[1])
	{
		MbufFree(MilProcImage[1]);
		MilProcImage[1] = M_NULL;
	}
	for (i = 0; i < Cam_Cnt; i++)
	{
		if (MilImageBuffer[3 + i])
		{
			GlobalUnlock(MilImageBuffer[3 + i]);
		}
	}
	for (i = 0; i < Cam_Cnt; i++)
	{
		if (MilProcImageChild[Cam_Cnt + i])
		{
			MbufFree(MilProcImageChild[Cam_Cnt + i]);
			MilProcImageChild[Cam_Cnt + i] = M_NULL;
			//
			
		}
		
	}
	
	for (i = 0; i < iBufSize_Bayer; i++)
	{
		if (MilBayerImage[i])
		{
			MbufFree(MilBayerImage[i]);
			MilBayerImage[i] = M_NULL;
		}
	}
	
}
bool CVision::MiuBufferAlloc(int fi_Width, int fi_Height)
{
	if ( fi_Width <= 0 || fi_Height <= 0 )
	{
		return false;
	}
	MiuCCdBufferReset();

	int i = 0;
	int pitch, Hight;

	long lColorBand;
	long lBufferAttributes = M_IMAGE + M_PROC + M_DISP;


	m_dReduceFactorX = (double)SMALL_CCD_SIZE_X / fi_Width;
	m_dReduceFactorY = (double)SMALL_CCD_SIZE_Y / fi_Height;


	MbufAllocColor(MilSystem, 3, fi_Width, fi_Height, M_DEF_IMAGE_TYPE, lBufferAttributes, &MilGrabImage[1]);
	if (MilGrabImage[1])
	{
		MbufClear(MilGrabImage[1], 0);

		for (i=0 ; i<Cam_Cnt ; i++)
		{
			if (i==CAM1)		lColorBand = M_RED;
			else if (i==CAM2)	lColorBand = M_GREEN;
			else if (i==2)		lColorBand = M_BLUE;

			MbufChildColor(MilGrabImage[1], lColorBand, &MilGrabImageChild[Cam_Cnt+i]);
			if (MilGrabImageChild[Cam_Cnt+i])
				MbufClear(MilGrabImageChild[Cam_Cnt+i], 0);
			else
			{
				sLangChange.LoadStringA(IDS_STRING779);
				::errMsg2(Task.AutoFlag, sLangChange);// MilGrabImageChild Alloc 실패
				return false;
			}
		}
	}
	else
	{
		sLangChange.LoadStringA(IDS_STRING778);
		errMsg2(Task.AutoFlag, sLangChange);	//MilGrabImage Allocation 실패.
		return false;
	}


	MbufAllocColor(MilSystem, 3, fi_Width, fi_Height, M_DEF_IMAGE_TYPE, lBufferAttributes, &MilProcImage[1]);
	if (MilProcImage[1])
	{
		MbufClear(MilProcImage[1], 0);

		long lColorBand;

		for (i=0 ; i<Cam_Cnt ; i++)
		{
			if (i==CAM1)		lColorBand = M_RED;
			else if (i==CAM2)	lColorBand = M_GREEN;
			else if (i==2)		lColorBand = M_BLUE;

			MbufChildColor(MilProcImage[1], lColorBand, &MilProcImageChild[Cam_Cnt+i]);

			if (MilProcImageChild[Cam_Cnt + i])
			{
				MbufClear(MilProcImageChild[Cam_Cnt + i], 0);
			}
			else 
			{
				::errMsg2(Task.AutoFlag, "MilProcImageChild Alloc 실패");	//"MilProcImageChild Alloc 실패")
				return false;
			}

			pitch = MbufInquire(MilProcImageChild[Cam_Cnt+i], M_PITCH, M_NULL);
			Hight = MbufInquire(MilProcImageChild[Cam_Cnt+i], M_SIZE_Y, M_NULL);

			MilImageBuffer[3+i] = (unsigned char*)GlobalAlloc(GMEM_ZEROINIT, pitch * Hight);

			MbufInquire(MilProcImageChild[Cam_Cnt+i], M_HOST_ADDRESS, &MilImageBuffer[Cam_Cnt+i]);
		}
	}
	else 
	{
		sLangChange.LoadStringA(IDS_STRING1455);
		::errMsg2(Task.AutoFlag, sLangChange);	//"MilProcImage Alloc 실패"
		return false;
	}

	if ( model.m_eGrabMethod == MIL_BAYER_CVT_COLOR )
	{
		for ( i = 0; i < iBufSize_Bayer; i++ )
		{
			MbufAlloc2d(MilSystem, fi_Width, fi_Height, 8 + M_UNSIGNED, M_IMAGE + M_PROC, &MilBayerImage[i]);
			if ( MilBayerImage == M_NULL )
			{
				sLangChange.LoadStringA(IDS_STRING775);
				::errMsg2(Task.AutoFlag, sLangChange);	//"MilBayerImage Alloc 실패"
				return false;
			}
		}
	}


	//MbufAllocColor(MilSystem, 1, fi_Width, fi_Height, M_DEF_IMAGE_TYPE, lBufferAttributes, &MilShadeImage);
	//if (MilShadeImage)
	//{
	//	MbufClear(MilShadeImage, 0);
	//	ImageShade = (unsigned char*)GlobalAlloc(GMEM_ZEROINIT, pitch * Hight);
	//	MbufInquire(MilShadeImage, M_HOST_ADDRESS, &ImageShade);
	//}
	//else 
	//{
	//	sLangChange.LoadStringA(IDS_STRING781);
	//	::errMsg2(Task.AutoFlag, sLangChange);	//"MilShadeImage Alloc 실패"
	//	return false;
	//}


	//CString sFileName;
	//sFileName.Format("%s\\Shade Image.bmp", DATA_DIR);
	//MbufImport(sFileName.GetBuffer(99), M_DEFAULT, M_LOAD, MilSystem, &MilSmallShadeImage);
	//MimResize(MilSmallShadeImage, MilShadeImage, 1/m_dReduceFactorX, 1/m_dReduceFactorY, M_DEFAULT);


	//pitch	= MbufInquire(MilShadeImage, M_PITCH, NULL);
	//int height	= MbufInquire(MilShadeImage, M_SIZE_Y, NULL);
	//int width	= MbufInquire(MilShadeImage, M_SIZE_X, NULL);

	/*int pos = 0;
	float avg=0;

	for (int y=0; y<height; y++)
	{
		pos = y*pitch;
		for (int x=0; x<width; x++)
		{
			avg += ImageShade[pos++];
		}
	}

*/

	return true;
}


//! MilGrabImage를 MilProcImage에 복사..
//! [주의 사항] 영상 취득 시각을 함께 갱신한다. 이를 지령 시각과 비교하여 영상의 유효성을 확인한다. 
void CVision::MilBufferUpdate()
{
	if(gMIUDevice.CurrentState>3)
	{
		double ep = myTimer(true);

		while (1)
		{
			if(CompareSystemTime(m_aTimeGrab[1], m_aTimeGrab_Proc[1]) )
			{
				break;
			}

			if( myTimer(true)-ep>2000)
				break;

			Sleep(5);
			checkMessage();
		}
	}

	m_acsGrabLock[1].Lock();

	CopySystemTime(m_aTimeGrab[1], m_aTimeGrab_Proc[1]);		//! 영상 취득 시각 갱신
	CopySystemTime(m_aTimeGrab[1], gMIUDevice.TimeGrab);

	MbufCopy(MilGrabImage[1], MilProcImage[1]);					//! 영상 데이터 갱신

	m_acsGrabLock[1].Unlock();
}

//! Added by LHW (2013/2/26)
//! CCM관련 Process용 버퍼를 갱신한다. 
//! [주의 사항] 영상 취득 시각을 함께 갱신한다. 이를 지령 시각과 비교하여 영상의 유효성을 확인한다. 
void CVision::MiuBufferUpdate()
{
	if ( model.m_eGrabMethod == MIL_BAYER_CVT_COLOR )
	{
		m_acsGrabLock[1].Lock();
		CopySystemTime(m_aTimeGrab[1], m_aTimeGrab_Proc[1]);		//! 영상 취득 시각 갱신
		CopySystemTime(m_aTimeGrab[1], gMIUDevice.TimeGrab);
		MIU.MilCopyToCv(MilGrabImageChild+3);						//! 영상 데이터 갱신
		MbufCopy(MilGrabImage[1], MilProcImage[1]);					//! 영상 데이터 갱신
		m_acsGrabLock[1].Unlock();
	} 
	else
	{
		int iIndex_MIU_Buffer = 0;

		m_csProcImageCV.Lock();
		iIndex_MIU_Buffer = MIU.m_iIndex_Cvt_Clr_Working;
		if ( iIndex_MIU_Buffer >= 0 && iIndex_MIU_Buffer < iBufSize_CCM_Temp )
		{
			CopySystemTime(MIU.m_aTemp[iIndex_MIU_Buffer].TimeGrab, m_TimeProcImageCV);	//! 영상 취득 시각 갱신
			CopySystemTime(m_TimeProcImageCV, gMIUDevice.TimeGrab);
			//cvCopyImage(MIU.m_aTemp[iIndex_MIU_Buffer].imageItp, gMIUDevice.imageItp);	//! 영상 데이터 갱신
			cvCopy(MIU.m_aTemp[iIndex_MIU_Buffer].imageItp, gMIUDevice.imageItp);	//! 영상 데이터 갱신
		}	
		m_csProcImageCV.Unlock();
	}
}


void CVision::GetBuffer_AutoDisp(int iMode, double dFactorX, double dFactorY)
{
	if ( iMode == 0 )	
	{
		MbufClear(MilOptImage, 0);
	}
	else				
	{
		MbufClear(MilDefectImage, 0);
		MbufClear(MilSaveDisplayDefectImage, 0);
	}

	if ( getLiveMode() )
	{
		if ( iMode == 0 )
			MimResize(MilGrabImage[1], MilOptImage, dFactorX, dFactorY, M_DEFAULT);
		else
			MimResize(MilGrabImage[1], MilDefectImage, dFactorX, dFactorY, M_DEFAULT);
	}
	else
	{
		if ( iMode == 0 )	MimResize(MilProcImage[1], MilOptImage, dFactorX, dFactorY, M_DEFAULT);
		else				MimResize(MilProcImage[1], MilDefectImage, dFactorX, dFactorY, M_DEFAULT);
	}
}


//! Added by LHW (2013/3/12)
//! MbufBayer 함수를 사용할 때에만 유효하다.
//! [주의 사항] 반드시, 'MIU.Start()' 함수 호출 전에 호출되어야 한다. 
void CVision::MiuBufferIndexReady()
{
	m_iIndex_Cvt_Clr_Working = 0;
	m_iIndex_Cvt_Clr_Ready = -1;
	m_iIndex_Cvt_Clr_Used = -1;
}
