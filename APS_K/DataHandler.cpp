#include "stdAfx.h"

COffset::COffset()
{
	for(int iNo = 0; iNo < 4; iNo++)
	{
		f_epoxy_x_dispense_offset[iNo] = 0;
		f_epoxy_y_dispense_offset[iNo] = 0;
		f_epoxy_z_dispense_offset[iNo] = 0;
	}
}


CPasswordData::CPasswordData()
{
	sprintf_s(m_szPassword, "1");//3421
	m_bFlag = false;
}


void CPasswordData::Load()
{
	FILE* in;

	char	fileName[1000];
	wsprintf(fileName, "%s\\%s\\Data\\Password.txt", AA_MODEL_LOAD_DIR, model.mCurModelName);

	bool readFlag = false;

	if(!fopen_s(&in, fileName,"r"))
	{
		char	Line[500];
		char	Title[500];
		int		nRtn;

		while (1)
		{
			Line[0] = 0x00;
			fgets(Line, 499, in);
			nRtn = sscanf_s(Line, "%s", &Title, 499);

			if (nRtn==EOF)	
				break;

			else if( strcmp(Title, "PASSWORD")==0 )
			{
				readFlag = true;
				sscanf_s(Line, "%s %s",					Title, 499, m_szPassword, 99);
			}
			Line[0] = 0x00;
		}

		if(in)	fclose(in);
	}

	if(readFlag == false)
	{
		sprintf_s(m_szPassword, "1");//3421

		if(!fopen_s(&in, fileName,"w"))
		{
			fprintf_s(in, "PASSWORD %s",		m_szPassword);
			if(in)	fclose(in);
		}
	}
}

CTask::CTask()
{
	Init();
}

void CTask::Init()
{
	int i = 0;
	m_PcbLaserAfterTx = 0.0;
	m_PcbLaserAfterTy = 0.0;
	bSfrLogView = true;
	m_iPcbPickupNo = 0;
	m_iLensPickupNoCentering = m_iLensPickupNoGrip =  0;
	iMTFCnt = 0;
	m_bOkFlag = 0;
	m_bOkDispense = -1;
	m_bOKLensPass = -1;
	bConnectBarcode = true;
	memset(LotNo, 0x00, 256);
	memset(ChipID, 0x00, 256);
	memset(sNum, 0x00, 256);
	
	memset(Pn, 0x00, 256);

	AutoFlag = 0;
	AutoReday = 0;
	LensTask = PCBTask = 0;
	bMotorRunStop = false;

	PausePCBStep = 10000;
	PauseLensStep = 0;
	interlockLens = interlockPcb = 0;

	
	m_iStatus_Unit_Epoxy = 0;

	MainPCErrFlag = MainAirFlag = iEMSwitchFlag = iDoorFlag = iDoorFlag2 = iAmpFaultFlag = iHomeErrorFlag = iUsbModuleFlag = iLimitErrorFlag = -1;

	b_mark_result[0] = b_mark_result[1] = false;

	MainLensAutoFlag = 1;
	MainPcbAutoFlag = 1;

	for(i=0; i<3; i++)
	{
		d_mark_pos_x[i][0]	= d_mark_pos_y[i][0]	= d_mark_theta[i][0]	= d_mark_rate[i][0]	= 0;
		d_mark_pos_x[i][1]	= d_mark_pos_y[i][1]	= d_mark_theta[i][1]	= d_mark_rate[i][1]	= 0;
		d_Align_offset_x[i]	= d_Align_offset_y[i]	= d_Align_offset_th[i]	= 0;
	}

	bFlag_Auto_Exposure_Time = false;
	bFlag_Auto_White_Balance = false;

	m_dGainRed   = 1.;
	m_dGainGreen = 1.;
	m_dGainBlue  = 1.;

	m_dAvgRed   = 0.;
	m_dAvgGreen = 0.;
	m_dAvgBlue  = 0.;

	m_dGain_Real = 1.;

	m_iFlag_Max_Color = 1;

	m_iCnt_Step_AA_Total = 0;
	m_iCnt_1Step_End = 0;
	m_iCnt_Best_Step = 0;

	oldLaserTx = 0.1;
	oldLaserTy = 0.1;

	osCheck.m_bOS_Check_Result = 0;


	m_iCnt_Step_AA = 0;
	m_iCnt_Second_AA_Start = 0;

	m_iCnt_RepeatAA = 0;

	dOpticalShiftX = 0.0f;
	dOpticalShiftY = 0.0f;
	dOpticalPosX = 0.0f;
	dOpticalPosY = 0.0f;
	dLensRotation = 0.0f;
	rOpticalROI.left	= (int)(gMIUDevice.nWidth * 0.1 + 0.5);
	rOpticalROI.top		= (int)(gMIUDevice.nHeight * 0.1 + 0.5);
	rOpticalROI.right	= (int)(gMIUDevice.nWidth * 0.9 + 0.5);
	rOpticalROI.bottom	= (int)(gMIUDevice.nHeight * 0.9 + 0.5);
	iOpticalThVal = 0;
	dPcbAlignTh = 0.0f;
	dEPL = 0.0f;
	m_iStart_Step_LENS = m_iEnd_Step_LENS = 0;
	m_iStart_Step_PCB = m_iEnd_Step_PCB = 0;

	iCnt_Total_Defect = 0;

	m_dTime_Total				= 0;
	m_dTime_TotalAA				= 0;
	m_dTime_Epoxy				= 0;
	m_dTime_FineAA				= 0;
	m_dTime_UV					= 0;
	m_dTime_LaserDpm			= 0;

	dUvOffset_Aver = 0.0;
	m_dShift_IMG_X = m_dShift_IMG_Y = m_dShift_IMG_TH = 0.0;

	m_dataOffset_x[0] = m_dataOffset_x[1] = m_dataOffset_y[0] = m_dataOffset_y[1] = m_dataOffset_th[0] = m_dataOffset_th[1] = 0;
    m_CirclePos_x[0] = m_CirclePos_x[1] = m_CirclePos_x[2] = m_CirclePos_x[3] = 0.0;
    m_CirclePos_y[0] = m_CirclePos_y[1] = m_CirclePos_y[2] = m_CirclePos_y[3] = 0.0;
    //
    m_FovPos_x[0] = m_FovPos_x[1] = m_FovPos_x[2] = m_FovPos_x[3] = 0.0;
    m_FovPos_y[0] = m_FovPos_y[1] = m_FovPos_y[2] = m_FovPos_y[3] = 0.0;

	bTrinityDoubleDispense = false;
    
	dAAPcbMotor[0] = dAAPcbMotor[1] = dAAPcbMotor[2] = dAAPcbMotor[3] = dAAPcbMotor[4] = dAAPcbMotor[5] = 0.0;
	m_iDrawBarStep = 0;

	m_bFlag_Decrease_SFR = false;

	m_b_AA_Retry_Flag = false;


	m_LinePulse_Mode_Change = false;
	//initSFRElem();

	LensTaskTime = PCBTaskTime = 0;
	LensOnStage = PcbOnStage = 0;

	m_bNgUnload = false;
	m_bOkUnload = false;
	m_bUvPassUnload = false;
	bManual_FindEpoxy = false;
	ocCheckIng = false;

	m_vDirection.resize(COMMON_MTF_INSP_CNT);//MTF_INSP_CNT);
    m_vFrquency.resize(COMMON_MTF_INSP_CNT);//MTF_INSP_CNT);
    m_vOffset.resize(COMMON_MTF_INSP_CNT);//MTF_INSP_CNT);
    m_vSFR.resize(COMMON_MTF_INSP_CNT);//MTF_INSP_CNT);
    m_vThreshold.resize(COMMON_MTF_INSP_CNT);//MTF_INSP_CNT);
    m_vROI.resize(COMMON_MTF_INSP_CNT);//MTF_INSP_CNT);


	sMiniOcTemp = 0;

	for (i = 0; i < COMMON_MTF_INSP_CNT; i++)
	{
		SFR.nTiltCalIndex[i] = 0;
	}
	
}

void CTask::initSFRElem()
{
#ifdef ON_LINE_VISION
	MbufClear(vision.MilDefectImage, 0);//이물 화면 초기화
#endif
	sfrResult = false;
	m_iCnt_Step_AA_Total		= 0;
	m_iCnt_1Step_End = 0;
	m_iCnt_Step_AA = 0;
	m_iCnt_Second_AA_Start = 0;
	codeResult = 0;	
	dFov[0]	= dFov[1]	= dFov[2]	= dFov[3]	= dFov[4]	= 0;


	memset(SFR.iDataCnt, 0x00, sizeof(int)*COMMON_MTF_INSP_CNT);// MTF_INSP_CNT);

	memset(SFR.fMotorPos,		0x00, sizeof(float)*MAX_CCD_STEP_NO*6);
	memset(SFR.fImageAlign,		0x00, sizeof(float)*MAX_CCD_STEP_NO*4);

	memset(SFR.fSfrN4,			0x00, sizeof(float)*MAX_CCD_STEP_NO*MAX_MTF_NO);

	memset(SFR.fSFR_DataX,		0x00, sizeof(double)*MAX_MTF_NO*MAX_SFR_DATA_CNT);
	memset(SFR.fSFR_DataY,		0x00, sizeof(double)*MAX_MTF_NO*MAX_SFR_DATA_CNT);

	memset(SFR.	dMaxPos,		0x00, sizeof(double)*MAX_MTF_NO);


	memset(SFR._64_fSfrN4, 0x00, sizeof(float)*COMMON_MTF_INSP_CNT);// MTF_INSP_CNT);

	SFR.dTilt_X = 0.0;
	SFR.dTilt_Y = 0.0;

	bFirstAA = false;

	m_iRetry_Opt =  m_iRetry_Opt_Lens = 0;

	m_bFlag_Fine_Move = false;

	m_bFlag_Decrease_SFR = false;
	ocCheckIng = false;
}																					

void CTask::func_TactTimeInit()
{
	m_dTime_Total				= 0;
	m_dTime_TotalAA				= 0;
	m_dTime_Epoxy				= 0;
	m_dTime_FineAA				= 0;
	m_dTime_UV					= 0;
	m_dTime_LaserDpm			= 0;

	m_dShift_IMG_X = m_dShift_IMG_Y = m_dShift_IMG_TH = 0.0;

	m_dataOffset_x[0] = m_dataOffset_x[1] = m_dataOffset_y[0] = m_dataOffset_y[1] = m_dataOffset_th[0] = m_dataOffset_th[1] = 0.0;
}

void CTask::getROI()
{

	int sizeX = MbufInquire(vision.MilProcImageChild[4], M_SIZE_X, NULL);
	int sizeY = MbufInquire(vision.MilProcImageChild[4], M_SIZE_Y, NULL);
	int pitch = MbufInquire(vision.MilProcImageChild[4], M_PITCH, NULL);

	if (sizeX<=0 || sizeY<=0)
	{
		LogSave("MilProcImageChild Size Error.");
		return;
	}
	for(int i=0; i<4; i++)
	{
		SFR.rcROI[i] = model.sfrElem.m_CircleRoi[i];
		vision.boxlist[CCD].addList(SFR.rcROI[i], PS_DOT, M_COLOR_GREEN);
	}
}


bool CTask::_findFovPos(unsigned char* ucImage, int pitch, int sizeX, int sizeY, CRect* rcRoi)
{
	int maxSize = 100;// 200;

    CString sLog;

    if (ucImage == NULL)
    {
        sLangChange.LoadStringA(IDS_STRING1303);
        sLog.Format(sLangChange);		//"영상 버퍼가 잘못되었습니다."
        errMsg2(Task.AutoFlag, sLog);
        return false;
    }

    if (sizeX <= 0 || sizeY <= 0)
    {
        sLangChange.LoadStringA(IDS_STRING1304);
        sLog.Format(sLangChange + _T("( X : %d Y : %d )"), sizeX, sizeY);		//영상 사이즈가 잘못되었습니다.
        errMsg2(Task.AutoFlag, sLog);
        return false;
    }

    int aiHistX[5000];
    int aiHistY[5000];

	int offsetX = model.m_oc_x*-1;
	int offsetY = model.m_oc_y*-1;

    CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

    int _CIRCLE_MARK_GAP = 1000;

    for (int i = 0; i<MAX_FOV_COUNT; i++)
    { 
        if (i > 2 && i < 6)continue;

		rcRoi[i].left += offsetX;
		rcRoi[i].top += offsetY;
		rcRoi[i].right += offsetX;
		rcRoi[i].bottom += offsetY;
		vision.boxlist[CCD].addList(rcRoi[i], PS_DASHDOTDOT, M_COLOR_BLUE);
        if (rcRoi[i].left < 0 || rcRoi[i].top < 0 || rcRoi[i].right > sizeX || rcRoi[i].bottom > sizeY)
        {
            sTempLang.LoadStringA(IDS_STRING257);
            sLangChange.Format(sTempLang, i + 1, rcRoi[i].left, rcRoi[i].top, rcRoi[i].right, rcRoi[i].bottom);		//[마크 #%d] 원형 마크 검색 영역이 잘못되었습니다.
            sLog.Format(sLangChange);
            pFrame->putListLog(sLog);
            return false;
        }

        int iSx, iSy, iEx, iEy;
        int x, y, iPos;
        int iMaxX = -1, iMinX = 9999;
        int iMaxY = -1, iMinY = 9999;
        int iMax_Left = -1, iMax_Right = -1, iMax_Up = -1, iMax_Down = -1;

        int iMaxX2 = -1, iMinX2 = 9999;
        int iMaxY2 = -1, iMinY2 = 9999;
        int iMax_Left2 = -1, iMax_Right2 = -1, iMax_Up2 = -1, iMax_Down2 = -1;

        int iSum;
        int iGap;

        int iSum_Left, iSum_Right;
        int iSum_Top, iSum_Bottom;

        iSx = rcRoi[i].left;
        iEx = rcRoi[i].right;
        //
        iSy = rcRoi[i].top;
        iEy = rcRoi[i].bottom;

        ::memset(aiHistY, 0, sizeof(int)*(5000));
        ::memset(aiHistX, 0, sizeof(int)*(5000));


        /* X방향 히스토그램 */
        for (x = iSx; x<iEx; x++)
        {
            iPos = iSy * pitch + x;
            iSum = 0;

            for (y = iSy; y<iEy; y++)
            {
                //				iSum += (ucImage[iPos]*ucImage[iPos]);
                iSum += (ucImage[iPos]);
                iPos += pitch;
            }

            aiHistX[x - iSx] = iSum;
        }


        /* X방향부터 엣지 찾기 */
        for (x = iSx + 5; x<iEx - 5; x++)
        {
            iSum_Left = aiHistX[x - iSx - 4] + aiHistX[x - iSx - 3] + aiHistX[x - iSx - 2] + aiHistX[x - iSx - 1];
            iSum_Right = aiHistX[x - iSx + 4] + aiHistX[x - iSx + 3] + aiHistX[x - iSx + 2] + aiHistX[x - iSx + 1];

            iGap = iSum_Left - iSum_Right;

            if (iGap>400 && iGap > iMax_Left)
            {
                iMax_Left = iGap;
                iMinX = x;
            }

            iGap = iSum_Right - iSum_Left;

            if (iGap>400 && iGap > iMax_Right)
            {
                iMax_Right = iGap;
                iMaxX = x;
            }
        }


        iMax_Left = 0;
        iMinX2 = 0;
        int tmpSx = iMaxX - 400;
        int tmpEx = iMinX - 30;
        if (tmpSx < (iSx + 5))
            tmpSx = (iSx + 5);
        if (tmpEx >(iEx - 5))
            tmpEx = (iSx - 5);


        for (x = tmpSx; x<iMaxX; x++)
        {
            iSum_Left = aiHistX[x - iSx - 4] + aiHistX[x - iSx - 3] + aiHistX[x - iSx - 2] + aiHistX[x - iSx - 1];
            iSum_Right = aiHistX[x - iSx + 4] + aiHistX[x - iSx + 3] + aiHistX[x - iSx + 2] + aiHistX[x - iSx + 1];

            iGap = iSum_Left - iSum_Right;

            if (iGap>600 && iGap > iMax_Left)
            {
                iMax_Left = iGap;
                iMinX2 = x;
            }
        }


        iMax_Right = 0;
        iMaxX2 = 0;

        tmpSx = iMinX + 30;
        tmpEx = iMinX + 400;
        if (tmpSx < (iSx + 5))
            tmpSx = (iSx + 5);
        if (tmpEx >(iEx - 5))
            tmpEx = (iEx - 5);



        for (x = tmpSx; x<tmpEx; x++)
        {
            iSum_Left = aiHistX[x - iSx - 4] + aiHistX[x - iSx - 3] + aiHistX[x - iSx - 2] + aiHistX[x - iSx - 1];
            iSum_Right = aiHistX[x - iSx + 4] + aiHistX[x - iSx + 3] + aiHistX[x - iSx + 2] + aiHistX[x - iSx + 1];

            iGap = iSum_Right - iSum_Left;

            if (iGap>800 && iGap > iMax_Right)//600에서 800으로 수정해서 원형 넓게 잡히는거 수정
            {
                iMax_Right = iGap;
                iMaxX2 = x;
            }
        }


        if (iMaxX - iMinX>30 && iMaxX - iMinX<maxSize && iMinX>0)
        {
            iMinX = iMinX;
            iMaxX = iMaxX;
        }
        else if (iMaxX2 - iMinX>30 && iMaxX2 - iMinX<maxSize && iMinX>0)
        {
            iMinX = iMinX;
            iMaxX = iMaxX2;
        }
        else if (iMaxX - iMinX2>30 && iMaxX - iMinX2<maxSize && iMinX2>0)
        {
            iMinX = iMinX2;
            iMaxX = iMaxX;
        }

        /* Y 방향 히스토그램 */
        for (y = iSy; y<iEy; y++)
        {
            iPos = y * pitch + iMinX;
            iSum = 0;

            for (x = iMinX; x<iMaxX; x++)
            {
                iSum += ucImage[iPos++];
            }

            aiHistY[y - iSy] = iSum;
        }

        for (y = iSy + 5; y<iEy - 5; y++)
        {
            iSum_Top = aiHistY[y - iSy - 4] + aiHistY[y - iSy - 3] + aiHistY[y - iSy - 2] + aiHistY[y - iSy - 1];
            iSum_Bottom = aiHistY[y - iSy + 4] + aiHistY[y - iSy + 3] + aiHistY[y - iSy + 2] + aiHistY[y - iSy + 1];

            iGap = iSum_Top - iSum_Bottom;

            if (iGap > iMax_Up)
            {
                iMax_Up = iGap;
                iMinY = y;
            }

            iGap = iSum_Bottom - iSum_Top;

            if (iGap > iMax_Down)
            {
                iMax_Down = iGap;
                iMaxY = y;
            }
        }


        if (iMinY >= iMaxY)
        {
            int iMinY2 = -9999;
            int iMaxY2 = -9999;
            int iMax_Up2 = 0;
            int iMax_Down2 = 0;

            int tmpSy = iMinY + 5;
            int tmpEy = iEy - 5;

            for (y = tmpSy; y<tmpEy; y++)
            {
                iSum_Top = aiHistY[y - iSy - 4] + aiHistY[y - iSy - 3] + aiHistY[y - iSy - 2] + aiHistY[y - iSy - 1];
                iSum_Bottom = aiHistY[y - iSy + 4] + aiHistY[y - iSy + 3] + aiHistY[y - iSy + 2] + aiHistY[y - iSy + 1];

                iGap = iSum_Bottom - iSum_Top;

                if (iGap > iMax_Down2 && (iGap>_CIRCLE_MARK_GAP))
                {
                    iMax_Down2 = iGap;
                    iMaxY2 = y;
                }
            }


            tmpSy = iSy + 5;
            tmpEy = iMaxY - 5;

            for (y = tmpSy; y<tmpEy; y++)
            {
                iSum_Top = aiHistY[y - iSy - 4] + aiHistY[y - iSy - 3] + aiHistY[y - iSy - 2] + aiHistY[y - iSy - 1];
                iSum_Bottom = aiHistY[y - iSy + 4] + aiHistY[y - iSy + 3] + aiHistY[y - iSy + 2] + aiHistY[y - iSy + 1];

                iGap = iSum_Top - iSum_Bottom;

                if (iGap > iMax_Up2 && (iGap>_CIRCLE_MARK_GAP))
                {
                    iMax_Up2 = iGap;
                    iMinY2 = y;
                }
            }

            if ((iMaxY - iMinY2)>50 && (iMaxY - iMinY2)<250)
            {
                iMinY = iMinY2;
            }
            else if ((iMaxY2 - iMinY)>50 && (iMaxY2 - iMinY)<250)
            {
                iMaxY = iMaxY2;
            }
        }
        else if ((iMaxY - iMinY) > 400)
        {
            int iMaxY2 = -9999;
            int iMinY2 = -9999;
            int iMax_Up2 = 0;
            int iMax_Down2 = 0;

            int tmpSy = iMinY + 5;
            int tmpEy = iMaxY - 5;

            for (y = tmpSy; y<tmpEy; y++)
            {
                iSum_Top = aiHistY[y - iSy - 4] + aiHistY[y - iSy - 3] + aiHistY[y - iSy - 2] + aiHistY[y - iSy - 1];
                iSum_Bottom = aiHistY[y - iSy + 4] + aiHistY[y - iSy + 3] + aiHistY[y - iSy + 2] + aiHistY[y - iSy + 1];

                iGap = iSum_Top - iSum_Bottom;

                if (iGap > iMax_Up2 && (iGap>_CIRCLE_MARK_GAP))
                {
                    iMax_Up2 = iGap;
                    iMinY2 = y;
                }

                iGap = iSum_Bottom - iSum_Top;

                if (iGap > iMax_Down2 && (iGap>_CIRCLE_MARK_GAP))
                {
                    iMax_Down2 = iGap;
                    iMaxY2 = y;
                }
            }

            if ((iMinY2>0) && ((iMaxY - iMinY2)>50 && (iMaxY - iMinY2)<250))
            {
                iMinY = iMinY2;
            }
            else if ((iMaxY2>0) && ((iMaxY2 - iMinY)>50 && (iMaxY2 - iMinY)<250))
            {
                iMaxY = iMaxY2;
            }
        }


        if (iMinX>iMaxX || (iMaxX - iMinX>maxSize))
        {
            sLog.Format("Fov Index %d Fail" , i);
            pFrame->putListLog(sLog);
            vision.boxlist[CCD].addList(iMinX, iMinY, iMaxX, iMaxY, PS_SOLID, M_COLOR_RED);
            sTempLang.LoadStringA(IDS_STRING259);
            sLangChange.Format(sTempLang, i + 1, iMinX, iMaxX);	//[마크 #%d] 좌우 인식 위치가 비정상 입니다.
            sLog.Format(sLangChange);
            pFrame->putListLog(sLog);
            return false;
        }


        if (iMinY>iMaxY || (iMaxY - iMinY>maxSize))
        {
            vision.boxlist[CCD].addList(iMinX, iMinY, iMaxX, iMaxY, PS_SOLID, M_COLOR_RED);
            sTempLang.LoadStringA(IDS_STRING255);
            sLangChange.Format(sTempLang, i + 1, iMinY, iMaxY);
            sLog.Format(sLangChange);	//[마크 #%d] 상하 인식 위치가 비정상 입니다. (상 %d, 하 %d)
            pFrame->putListLog(sLog);
            return false;
        }


        if (iMaxX < 0 || iMaxY < 0 || iMaxX > sizeX || iMaxY > sizeY ||
            iMinX < 0 || iMinY < 0 || iMinX > sizeX || iMinY > sizeY)
        {
            sTempLang.LoadStringA(IDS_STRING252);
            sLangChange.Format(sTempLang, i + 1);
            sLog.Format(sLangChange);	//"[마크 #%d] Max, Min 위치를 찾지 못했습니다."
            pFrame->putListLog(sLog);
            return false;
        }
		
		
        //vision.boxlist[CCD].addList(iMinX, iMinY, iMaxX, iMaxY, PS_DOT, M_COLOR_BLUE);

        m_clPtFov[i].x = (iMaxX + iMinX) / 2;
        m_clPtFov[i].y = (iMaxY + iMinY) / 2;

		m_FindFovRect[i].left = iMinX;
		m_FindFovRect[i].right = iMaxX;
		m_FindFovRect[i].top = iMinY;
		m_FindFovRect[i].bottom = iMaxY;

       // m_FovPos_x[i] = (iMaxX + iMinX) / 2;
       // m_FovPos_y[i] = (iMaxY + iMinY) / 2;
		vision.boxlist[CCD].addList(m_FindFovRect[i], PS_DOT, M_COLOR_YELLOW);
        vision.crosslist[CCD].addList(m_clPtFov[i], 150, M_COLOR_GREEN);
    }
	
    return true;
}

bool CTask::_Trinity_findCirclePos(unsigned char* ucImage, int pitch, int sizeX, int sizeY, CRect* rcRoi)
{
	double dCenterPosX = 0.0;
	double dCenterPosY = 0.0;
	double dAngle = 0.0;
	double dRate = 0.0;
	int index = 0;

	bool brtn = true;
	//for (int i = 0; i < model.mGlobalChartCount; i++)
	//{
	//	if (i == 0)
	//	{
	//		continue;//center은 제외
	//	}
	//	if (FieldPatternMatching(i, dCenterPosX, dCenterPosY, dAngle, dRate))
	//	{
	//		/*rcRoi.left = dCenterPosX - model.m_FieldPattern_Size[i].x / 2;
	//		rcRoi.right = dCenterPosX + model.m_FieldPattern_Size[i].x / 2;
	//		rcRoi.top = dCenterPosY - model.m_FieldPattern_Size[i].y / 2;
	//		rcRoi.bottom = dCenterPosY + model.m_FieldPattern_Size[i].y / 2;*/
	//		m_CircleP[i - 1].x = dCenterPosX;
	//		m_CircleP[i - 1].y = dCenterPosY;
	//		m_CirclePos_x[i - 1] = dCenterPosX;
	//		m_CirclePos_y[i - 1] = dCenterPosY;
	//	}
	//	else
	//	{
	//		brtn = false;
	//	}
	//}
	if (ChartCenterPatternMatching())
	{
		m_CircleP[0].x = (gMIUDevice.nWidth / 2) - 500;
		m_CircleP[0].y = (gMIUDevice.nHeight / 2) - 500;
		m_CircleP[1].x = (gMIUDevice.nWidth / 2) + 500;
		m_CircleP[1].y = (gMIUDevice.nHeight / 2) - 500;

		m_CircleP[2].x = (gMIUDevice.nWidth / 2) - 500;
		m_CircleP[2].y = (gMIUDevice.nHeight / 2) + 500;
		m_CircleP[3].x = (gMIUDevice.nWidth / 2) + 500;
		m_CircleP[3].y = (gMIUDevice.nHeight / 2) + 500;
		m_CirclePos_x[0] = m_CircleP[0].x;
		m_CirclePos_y[0] = m_CircleP[0].y;
		m_CirclePos_x[1] = m_CircleP[1].x;
		m_CirclePos_y[1] = m_CircleP[1].y;
		m_CirclePos_x[2] = m_CircleP[2].x; 
		m_CirclePos_y[2] = m_CircleP[2].y;
		m_CirclePos_x[3] = m_CircleP[3].x;
		m_CirclePos_y[3] = m_CircleP[3].y;
		//Task.m_dShift_IMG_X = theApp.MainDlg->ChartCenterOffsetX*(model.m_dSize_CCD_Cell / 1000.0f)*1.0f;
		//Task.m_dShift_IMG_Y = theApp.MainDlg->ChartCenterOffsetY*(model.m_dSize_CCD_Cell / 1000.0f)*1.0f;
	}
	else
	{
		return false;
	}
	
	return brtn;
	//m_CircleP[i].x = (iMaxX + iMinX) / 2;
	//m_CircleP[i].y = (iMaxY + iMinY) / 2;
}
bool CTask::_OpencvFindCirclePos(BYTE* ChartRawImage, CRect* clRectRoi, bool bAutoMode)		//int nPitch, int nSizeX, int nSizeY,
{

	TCHAR szLog[SIZE_OF_1K];
	TCHAR szFilePath[SIZE_OF_1K];
	//opencv 로 원형마크 찾기

	BYTE* m_pBMPTempBuffer;
	m_pBMPTempBuffer = new BYTE[MIU.m_pBoard->GetFrameBMPSize()];
	memset(m_pBMPTempBuffer, 0, MIU.m_pBoard->GetFrameBMPSize());

	ACMISSoftISP::xMakeBMP(ChartRawImage, (byte*)m_pBMPTempBuffer, gMIUDevice.nWidth, gMIUDevice.nHeight, gMIUDevice.dTDATASPEC_n);

	Mat OrgImage(Size(gMIUDevice.nWidth, gMIUDevice.nHeight), CV_8UC3);
	std::memcpy(OrgImage.data, (char*)m_pBMPTempBuffer, gMIUDevice.nWidth * gMIUDevice.nHeight * 3);


	TCHAR* pszCirRow[] = {
		_T("[0] Circle LT"), _T("[1] Circle RT"), _T("[2] Circle BL"), _T("[3] Circle BR")
	};
	int mdp = 1;						//dp=1이면 입력 이미지와 동일한 해상도를 사용
	int mMinDist = 0;		// / 8;//검출된 원의 중심들 사이의 최소 거리입니다
	int mParam1 = 220;// 200;			//캐니 에지 탐지기에 전달되는 상위 임계값입니다. 
	int mParam2 = 10;// 10;					//중심 검출을 위한 누산기의 임계값입니다. 이 값이 작을수록 더 많은 원이 검출되며, 노이즈나 잘못된 원도 포함될 수 있습니다.
	int mMinRadius = 4;// 11;					//검출할 원의 최소 반지름입니다.  
	int mMaxRadius = 12;// 75;					//검출할 원의 최대 반지름입니다. 
	 
	int arrParam1[] = { 150,170,200, 80, 100, 120 }; 
	bool bCircleRtn = false;
	for (int i = 0; i < 4; i++)
	{
		if (clRectRoi[i].left < 0 || clRectRoi[i].top < 0 || clRectRoi[i].right > gMIUDevice.nWidth || clRectRoi[i].bottom > gMIUDevice.nHeight)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[마크 #%d] 원형 마크 검색 영역이 잘못되었습니다. ( L:%d, T:%d, R:%d, B:%d )"), i + 1, clRectRoi[i].left, clRectRoi[i].top, clRectRoi[i].right, clRectRoi[i].bottom);
			//AddLog(szLog, 0, m_nUnit);
			theApp.MainDlg->putListLog(szLog);
			return false;
		}
		Mat roiimg = OrgImage(cvRect(clRectRoi[i].left, clRectRoi[i].top, clRectRoi[i].Width(), clRectRoi[i].Height()));
		Mat grayImg;
		cv::cvtColor(roiimg, grayImg, cv::COLOR_BGR2GRAY);

		//
		//
		

		mMinDist = grayImg.rows / 2;		// / 8;//검출된 원의 중심들 사이의 최소 거리입니다
		std::vector<cv::Vec3f> circles;
		// 가우시안 블러 적용 (노이즈 제거)
		//cv::GaussianBlur(grayImg, grayImg, cv::Size(9, 9), 2, 2);
		for (int k = 0; k < 6; k++)
		{

			mParam1 = arrParam1[k];
			cv::HoughCircles(grayImg, circles, cv::HOUGH_GRADIENT, mdp, mMinDist, mParam1, mParam2, mMinRadius, mMaxRadius);
			if (circles.empty() == false)
			{ 
				bCircleRtn = true;
				break;
			}
		}

		if (bCircleRtn == false)
		{
			return false;
		}
		/*cv::HoughCircles(grayImg, circles, cv::HOUGH_GRADIENT, mdp, mMinDist, mParam1, mParam2, mMinRadius, mMaxRadius);
		if (circles.empty())
		{
			return false;
		}*/
		if (circles.empty())
		{
			return false;
		}
		cv::Point center(cvRound(circles[0][0]), cvRound(circles[0][1]));
		int radius = cvRound(circles[0][2]);

		m_CircleP[i].x = circles[0][0] + clRectRoi[i].left;
 		m_CircleP[i].y = circles[0][1] + clRectRoi[i].top;

		m_FindCircleRect[i].left = m_CircleP[i].x - radius;
		m_FindCircleRect[i].right = m_CircleP[i].x + radius;
		m_FindCircleRect[i].top = m_CircleP[i].y - radius;
		m_FindCircleRect[i].bottom = m_CircleP[i].y + radius;


		m_CirclePos_x[i] = circles[0][0] + clRectRoi[i].left;
		m_CirclePos_y[i] = circles[0][1] + clRectRoi[i].top;
		//g_clVision.DrawMOverlayBox(m_nUnit, m_nUnit, g_clTaskWork[m_nUnit].m_FindCircleRect[i].left, g_clTaskWork[m_nUnit].m_FindCircleRect[i].top, g_clTaskWork[m_nUnit].m_FindCircleRect[i].right, g_clTaskWork[m_nUnit].m_FindCircleRect[i].bottom, M_COLOR_GRAY, 1, FALSE, PS_SOLID);
		
		
		vision.boxlist[CCD].addList(m_FindCircleRect[i].left, m_FindCircleRect[i].top, m_FindCircleRect[i].right, m_FindCircleRect[i].bottom, PS_SOLID, M_COLOR_GRAY);

		if (bAutoMode == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("%s x:%d , y:%d"), pszCirRow[i], m_CircleP[i].x, m_CircleP[i].y);
			theApp.MainDlg->putListLog(szLog);
		}
		//g_clVision.DrawMOverlayCross(m_nUnit, m_nUnit, g_clTaskWork[m_nUnit].m_clPtCircle[i], 200, M_COLOR_GRAY, 1, FALSE);// TRUE);
		vision.crosslist[CCD].addList(m_CircleP[i], 100, M_COLOR_RED);

#ifdef _DEBUG
		if (false)//bAutoMode == false)
		{
			Mat img_corners;		//코너 찾기
			cvtColor(grayImg, img_corners, COLOR_GRAY2BGR);

			cv::Rect rect(circles[0][0] - radius, circles[0][1] - radius, radius * 2, radius * 2); // (x, y, width, height)
			circle(img_corners, center, 3, Scalar(0, 255, 0), -1, 8, 0);
			rectangle(img_corners, rect, Scalar(0, 255, 0), 1);

			_stprintf_s(szFilePath, SIZE_OF_1K, _T("%s\\circle_%d.jpg"), BASE_LOG_DIR, i + 1);
			imwrite(szFilePath, img_corners);

			namedWindow("Circle Center", WINDOW_NORMAL);// WINDOW_AUTOSIZE);
			imshow("Circle Center", img_corners);

			waitKey(0);
		}

		//circles.clear();
#endif
	}

	if (m_pBMPTempBuffer)
	{
		delete m_pBMPTempBuffer;
	}
	m_pBMPTempBuffer = NULL;

	return true;
}

bool CTask::_findCirclePos(unsigned char* ucImage, int pitch, int sizeX, int sizeY, CRect* rcRoi)
{
	int maxSize = 800;
	
	CString sLog;

	if ( ucImage == NULL )
	{
		sLangChange.LoadStringA(IDS_STRING1303);
		sLog.Format(sLangChange);		//"영상 버퍼가 잘못되었습니다."
		errMsg2(Task.AutoFlag,sLog);
		return false;
	}

	if ( sizeX <= 0 || sizeY <= 0)
	{
		sLangChange.LoadStringA(IDS_STRING1304);
		sLog.Format(sLangChange + _T("( X : %d Y : %d )"), sizeX, sizeY);		//영상 사이즈가 잘못되었습니다.
		errMsg2(Task.AutoFlag, sLog);
		return false;
	}

	int aiHistX[5000];
	int aiHistY[5000];

	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	int _MinGap = 20;
	int _CIRCLE_MARK_GAP=800;	// 800

	for (int i=0 ; i<4 ; i++)
	{
		if ( rcRoi[i].left < 0 || rcRoi[i].top < 0 || rcRoi[i].right > sizeX || rcRoi[i].bottom > sizeY )
		{
			sTempLang.LoadStringA(IDS_STRING257);
			sLangChange.Format(sTempLang, i+1, rcRoi[i].left, rcRoi[i].top, rcRoi[i].right, rcRoi[i].bottom);		//[마크 #%d] 원형 마크 검색 영역이 잘못되었습니다.
			sLog.Format(sLangChange);
			pFrame->putListLog(sLog);
			return false;
		}

		int iSx, iSy, iEx, iEy;
		int x, y, iPos;
		int iMaxX = -1, iMinX = 9999;
		int iMaxY = -1, iMinY = 9999;
		int iMax_Left = -1 , iMax_Right = -1, iMax_Up = -1, iMax_Down = -1;

		int iMaxX2 = -1, iMinX2 = 9999;
		int iMaxY2 = -1, iMinY2 = 9999;
		int iMax_Left2 = -1 , iMax_Right2 = -1, iMax_Up2 = -1, iMax_Down2 = -1;

		int iSum;		
		int iGap;

		int iSum_Left, iSum_Right;
		int iSum_Top, iSum_Bottom;

		iSx = rcRoi[i].left;
		iEx = rcRoi[i].right;
		//
		iSy = rcRoi[i].top;
		iEy = rcRoi[i].bottom;

		::memset(aiHistY, 0, sizeof(int)*(5000));
		::memset(aiHistX, 0, sizeof(int)*(5000));


		/* X방향 히스토그램 */
		for (x=iSx ; x<iEx ; x++)
		{
			iPos = iSy * pitch + x;
			iSum = 0;

			for (y=iSy ; y<iEy ; y++)
			{
//				iSum += (ucImage[iPos]*ucImage[iPos]);
				iSum += (ucImage[iPos]);
				iPos += pitch;
			}

			aiHistX[x-iSx] = iSum;
		}

		///* X방향부터 엣지 찾기 */
		//for (x=iSx+5 ; x<iEx-5 ; x++)
		//{
		//	iSum_Left  = aiHistX[x-iSx-4] + aiHistX[x-iSx-3] + aiHistX[x-iSx-2] + aiHistX[x-iSx-1];
		//	iSum_Right = aiHistX[x-iSx+4] + aiHistX[x-iSx+3] + aiHistX[x-iSx+2] + aiHistX[x-iSx+1];

		//	iGap = iSum_Left - iSum_Right;

		//	if (iGap>300 &&  iGap > iMax_Left)
		//	{
		//		iMax_Left = iGap;
		//		iMinX = x;
		//	}

		//	iGap = iSum_Right - iSum_Left;

		//	if (iGap>300 &&  iGap > iMax_Right)
		//	{
		//		iMax_Right = iGap;
		//		iMaxX = x;
		//	}
		//}
		/* X방향부터 엣지 찾기 */
		for (x=iSx+5 ; x<iEx-5 ; x++)
		{
			iSum_Left  = aiHistX[x-iSx-4] + aiHistX[x-iSx-3] + aiHistX[x-iSx-2] + aiHistX[x-iSx-1];
			iSum_Right = aiHistX[x-iSx+4] + aiHistX[x-iSx+3] + aiHistX[x-iSx+2] + aiHistX[x-iSx+1];

			iGap = iSum_Left - iSum_Right;

			if (iGap>1000 &&  iGap > iMax_Left)
			{
				iMax_Left = iGap;
				iMinX = x;
			}

			iGap = iSum_Right - iSum_Left;

			if (iGap>1000 &&  iGap > iMax_Right)
			{
				iMax_Right = iGap;
				iMaxX = x;
			}
		}


		iMax_Left = 0;
		iMinX2 = 0;
		int tmpSx = iMaxX- 1000;
		int tmpEx = iMinX - _MinGap;
		if(tmpSx < (iSx+5))
			tmpSx = (iSx+5);
		if(tmpEx > (iEx-5))
			tmpEx = (iSx-5);

		//for (x=tmpSx ; x<iMaxX; x++)
		//{
		//	iSum_Left  = aiHistX[x-iSx-4] + aiHistX[x-iSx-3] + aiHistX[x-iSx-2] + aiHistX[x-iSx-1];
		//	iSum_Right = aiHistX[x-iSx+4] + aiHistX[x-iSx+3] + aiHistX[x-iSx+2] + aiHistX[x-iSx+1];

		//	iGap = iSum_Left - iSum_Right;

		//	if (iGap>400 &&  iGap > iMax_Left)
		//	{
		//		iMax_Left = iGap;
		//		iMinX2 = x;
		//	}
		//}
		for (x=tmpSx ; x<iMaxX; x++)
		{
			iSum_Left  = aiHistX[x-iSx-4] + aiHistX[x-iSx-3] + aiHistX[x-iSx-2] + aiHistX[x-iSx-1];
			iSum_Right = aiHistX[x-iSx+4] + aiHistX[x-iSx+3] + aiHistX[x-iSx+2] + aiHistX[x-iSx+1];

			iGap = iSum_Left - iSum_Right;

			if (iGap>1000 &&  iGap > iMax_Left)
			{
				iMax_Left = iGap;
				iMinX2 = x;
			}
		}


		iMax_Right = 0;
		iMaxX2 = 0;

		tmpSx = iMinX + _MinGap;
		tmpEx = iMinX + 1000;
		if(tmpSx < (iSx+5))
			tmpSx = (iSx+5); 
		if(tmpEx > (iEx-5))
			tmpEx = (iEx-5);


		//for (x=tmpSx ; x<tmpEx; x++)
		//{
		//	iSum_Left  = aiHistX[x-iSx-4] + aiHistX[x-iSx-3] + aiHistX[x-iSx-2] + aiHistX[x-iSx-1];
		//	iSum_Right = aiHistX[x-iSx+4] + aiHistX[x-iSx+3] + aiHistX[x-iSx+2] + aiHistX[x-iSx+1];

		//	iGap = iSum_Right - iSum_Left;

		//	if (iGap>400 && iGap > iMax_Right)
		//	{
		//		iMax_Right = iGap;
		//		iMaxX2 = x;
		//	}
		//}
		for (x=tmpSx ; x<tmpEx; x++)
		{
			iSum_Left  = aiHistX[x-iSx-4] + aiHistX[x-iSx-3] + aiHistX[x-iSx-2] + aiHistX[x-iSx-1];
			iSum_Right = aiHistX[x-iSx+4] + aiHistX[x-iSx+3] + aiHistX[x-iSx+2] + aiHistX[x-iSx+1];

			iGap = iSum_Right - iSum_Left;

			if (iGap>1000 && iGap > iMax_Right)
			{
				iMax_Right = iGap;
				iMaxX2 = x;
			}
		}


		if( iMaxX-iMinX>_MinGap && iMaxX-iMinX<maxSize && iMinX>0)
		{
			iMinX = iMinX;
			iMaxX = iMaxX;
		}
		else if( iMaxX2-iMinX>_MinGap && iMaxX2-iMinX<maxSize && iMinX>0 )
		{
			iMinX = iMinX;
			iMaxX = iMaxX2;
		}
		else if( iMaxX-iMinX2>_MinGap && iMaxX-iMinX2<maxSize && iMinX2>0 )
		{
			iMinX = iMinX2;
			iMaxX = iMaxX;
		}

		/* Y 방향 히스토그램 */
		for (y=iSy ; y<iEy ; y++)
		{
			iPos = y * pitch + iMinX;
			iSum = 0;

			for (x=iMinX ; x<iMaxX; x++)
			{
				iSum += ucImage[iPos++];
			}

			aiHistY[y-iSy] = iSum;
		}

		for (y=iSy+5 ; y<iEy-5 ; y++)
		{
			iSum_Top	= aiHistY[y-iSy-4] + aiHistY[y-iSy-3] + aiHistY[y-iSy-2] + aiHistY[y-iSy-1];
			iSum_Bottom = aiHistY[y-iSy+4] + aiHistY[y-iSy+3] + aiHistY[y-iSy+2] + aiHistY[y-iSy+1];

			iGap = iSum_Top - iSum_Bottom;

			if ( iGap > iMax_Up )
			{
				iMax_Up = iGap;
				iMinY = y;
			}

			iGap = iSum_Bottom - iSum_Top;

			if ( iGap > iMax_Down )
			{
				iMax_Down = iGap;
				iMaxY = y;
			}
		}
		 

		if ( iMinY >= iMaxY )
		{
			int iMinY2		= -9999;
			int iMaxY2		= -9999;
			int iMax_Up2	= 0;
			int iMax_Down2	= 0;

			int tmpSy = iMinY + 5;
			int tmpEy = iEy-5;

			for (y=tmpSy ; y<tmpEy ; y++)
			{
				iSum_Top	= aiHistY[y-iSy-4] + aiHistY[y-iSy-3] + aiHistY[y-iSy-2] + aiHistY[y-iSy-1];
				iSum_Bottom = aiHistY[y-iSy+4] + aiHistY[y-iSy+3] + aiHistY[y-iSy+2] + aiHistY[y-iSy+1];

				iGap = iSum_Bottom - iSum_Top;

				if ( iGap > iMax_Down2 && (iGap>_CIRCLE_MARK_GAP) )
				{
					iMax_Down2 = iGap;
					iMaxY2 = y;
				}
			}


			tmpSy = iSy+5;
			tmpEy = iMaxY - 5;

			for (y=tmpSy ; y<tmpEy ; y++)
			{
				iSum_Top	= aiHistY[y-iSy-4] + aiHistY[y-iSy-3] + aiHistY[y-iSy-2] + aiHistY[y-iSy-1];
				iSum_Bottom = aiHistY[y-iSy+4] + aiHistY[y-iSy+3] + aiHistY[y-iSy+2] + aiHistY[y-iSy+1];

				iGap = iSum_Top - iSum_Bottom;

				if ( iGap > iMax_Up2 && (iGap>_CIRCLE_MARK_GAP) )
				{
					iMax_Up2 = iGap;
					iMinY2 = y;
				}
			}

			if( (iMaxY-iMinY2)>50 && (iMaxY-iMinY2)<250)
			{
				iMinY = iMinY2;
			}
			else if( (iMaxY2-iMinY)>50 && (iMaxY2-iMinY)<250)
			{
				iMaxY = iMaxY2;
			}
		}
		else if( (iMaxY-iMinY) > 400 )
		{
			int iMaxY2		= -9999;
			int iMinY2		= -9999;
			int iMax_Up2	= 0;
			int iMax_Down2	= 0;

			int tmpSy = iMinY + 5;
			int tmpEy = iMaxY - 5;

			for (y=tmpSy ; y<tmpEy ; y++)
			{
				iSum_Top	= aiHistY[y-iSy-4] + aiHistY[y-iSy-3] + aiHistY[y-iSy-2] + aiHistY[y-iSy-1];
				iSum_Bottom = aiHistY[y-iSy+4] + aiHistY[y-iSy+3] + aiHistY[y-iSy+2] + aiHistY[y-iSy+1];

				iGap = iSum_Top - iSum_Bottom;

				if ( iGap > iMax_Up2 && (iGap>_CIRCLE_MARK_GAP) )
				{
					iMax_Up2 = iGap;
					iMinY2 = y;
				}

				iGap = iSum_Bottom - iSum_Top;

				if ( iGap > iMax_Down2 && (iGap>_CIRCLE_MARK_GAP) )
				{
					iMax_Down2 = iGap;
					iMaxY2 = y;
				}
			}

			if( (iMinY2>0) && ((iMaxY-iMinY2)>50 && (iMaxY-iMinY2)<250) )
			{
				iMinY = iMinY2;
			}
			else if ( (iMaxY2>0) && ((iMaxY2-iMinY)>50 && (iMaxY2-iMinY)<250) )
			{
				iMaxY = iMaxY2;
			}
		}


		if(iMinX>iMaxX || (iMaxX-iMinX>maxSize) )
		{
			vision.boxlist[CCD].addList(iMinX, iMinY, iMaxX, iMaxY, PS_SOLID, M_COLOR_RED);
			sTempLang.LoadStringA(IDS_STRING259);
			sLangChange.Format(sTempLang, i+1, iMinX, iMaxX);	//[마크 #%d] 좌우 인식 위치가 비정상 입니다.
			sLog.Format(sLangChange);
			pFrame->putListLog(sLog);
			return false;
		}


		if(iMinY>iMaxY || (iMaxY-iMinY>maxSize) )
		{
			vision.boxlist[CCD].addList(iMinX, iMinY, iMaxX, iMaxY, PS_SOLID, M_COLOR_RED);
			sTempLang.LoadStringA(IDS_STRING255);
			sLangChange.Format(sTempLang, i+1, iMinY, iMaxY);
			sLog.Format(sLangChange);	//[마크 #%d] 상하 인식 위치가 비정상 입니다. (상 %d, 하 %d)
			pFrame->putListLog(sLog); 
			return false;
		}


		if ( iMaxX < 0 || iMaxY < 0 || iMaxX > sizeX || iMaxY > sizeY	||
			iMinX < 0 || iMinY < 0 || iMinX > sizeX || iMinY > sizeY )
		{
			sTempLang.LoadStringA(IDS_STRING252);
			sLangChange.Format(sTempLang, i+1);
			sLog.Format(sLangChange);	//"[마크 #%d] Max, Min 위치를 찾지 못했습니다."
			pFrame->putListLog(sLog);
			return false;
		}
		
		vision.boxlist[CCD].addList(iMinX, iMinY, iMaxX, iMaxY, PS_DOT, M_COLOR_BLUE);
		
		m_CircleP[i].x = (iMaxX+iMinX)/2;
		m_CircleP[i].y = (iMaxY+iMinY)/2;

		m_FindCircleRect[i].left = iMinX;
		m_FindCircleRect[i].right = iMaxX;
		m_FindCircleRect[i].top = iMinY;
		m_FindCircleRect[i].bottom = iMaxY;

		m_CirclePos_x[i] = (iMaxX+iMinX)/2;
		m_CirclePos_y[i]  = (iMaxY+iMinY)/2;
		vision.crosslist[CCD].addList(m_CircleP[i], 100, M_COLOR_RED); 
	}
		
	return true;
}

CPoint CTask::getCircle(unsigned char* ucImage, int iX, int iY, int iWidth, int iHeight,  int sizeX, int sizeY, int pitch)
{
	int maxSize = 200;

	CString sLog;

	if ( ucImage == NULL )
	{
		sLangChange.LoadStringA(IDS_STRING1303);
		sLog.Format(sLangChange);		//"영상 버퍼가 잘못되었습니다."
		errMsg2(Task.AutoFlag,sLog);
		return false;
	}

	if ( sizeX <= 0 || sizeY <= 0)
	{
		sLangChange.LoadStringA(IDS_STRING1304);
		sLog.Format(sLangChange + _T("( X : %d Y : %d )"), sizeX, sizeY);		//영상 사이즈가 잘못되었습니다.
		errMsg2(Task.AutoFlag, sLog);
		return false;
	}

	int aiHistX[5000];
	int aiHistY[5000];

	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	int _CIRCLE_MARK_GAP=200;	// 800

		int iSx, iSy, iEx, iEy;
		int x, y, iPos;
		int iMaxX = -1, iMinX = 9999;
		int iMaxY = -1, iMinY = 9999;
		int iMax_Left = -1 , iMax_Right = -1, iMax_Up = -1, iMax_Down = -1;

		int iMaxX2 = -1, iMinX2 = 9999;
		int iMaxY2 = -1, iMinY2 = 9999;
		int iMax_Left2 = -1 , iMax_Right2 = -1, iMax_Up2 = -1, iMax_Down2 = -1;

		int iSum;		
		int iGap;

		int iSum_Left, iSum_Right;
		int iSum_Top, iSum_Bottom;

		iSx = iX;
		iSy = iY;
		iEx = iX+iWidth;
		iEy = iY+iHeight;

		::memset(aiHistY, 0, sizeof(int)*(5000));
		::memset(aiHistX, 0, sizeof(int)*(5000));


		/* X방향 히스토그램 */
		for (x=iSx ; x<iEx ; x++)
		{
			iPos = iSy * pitch + x;
			iSum = 0;

			for (y=iSy ; y<iEy ; y++)
			{
//				iSum += (ucImage[iPos]*ucImage[iPos]);
				iSum += (ucImage[iPos]);
				iPos += pitch;
			}

			aiHistX[x-iSx] = iSum;
		}

		///* X방향부터 엣지 찾기 */
		//for (x=iSx+5 ; x<iEx-5 ; x++)
		//{
		//	iSum_Left  = aiHistX[x-iSx-4] + aiHistX[x-iSx-3] + aiHistX[x-iSx-2] + aiHistX[x-iSx-1];
		//	iSum_Right = aiHistX[x-iSx+4] + aiHistX[x-iSx+3] + aiHistX[x-iSx+2] + aiHistX[x-iSx+1];

		//	iGap = iSum_Left - iSum_Right;

		//	if (iGap>300 &&  iGap > iMax_Left)
		//	{
		//		iMax_Left = iGap;
		//		iMinX = x;
		//	}

		//	iGap = iSum_Right - iSum_Left;

		//	if (iGap>300 &&  iGap > iMax_Right)
		//	{
		//		iMax_Right = iGap;
		//		iMaxX = x;
		//	}
		//}
		/* X방향부터 엣지 찾기 */
		for (x=iSx+5 ; x<iEx-5 ; x++)
		{
			iSum_Left  = aiHistX[x-iSx-4] + aiHistX[x-iSx-3] + aiHistX[x-iSx-2] + aiHistX[x-iSx-1];
			iSum_Right = aiHistX[x-iSx+4] + aiHistX[x-iSx+3] + aiHistX[x-iSx+2] + aiHistX[x-iSx+1];

			iGap = iSum_Left - iSum_Right;

			if (iGap>400 &&  iGap > iMax_Left)
			{
				iMax_Left = iGap;
				iMinX = x;
			}

			iGap = iSum_Right - iSum_Left;

			if (iGap>400 &&  iGap > iMax_Right)
			{
				iMax_Right = iGap;
				iMaxX = x;
			}
		}


		iMax_Left = 0;
		iMinX2 = 0;
		int tmpSx = iMaxX-400;
		int tmpEx = iMinX - 30;
		if(tmpSx < (iSx+5))
			tmpSx = (iSx+5);
		if(tmpEx > (iEx-5))
			tmpEx = (iSx-5);

		//for (x=tmpSx ; x<iMaxX; x++)
		//{
		//	iSum_Left  = aiHistX[x-iSx-4] + aiHistX[x-iSx-3] + aiHistX[x-iSx-2] + aiHistX[x-iSx-1];
		//	iSum_Right = aiHistX[x-iSx+4] + aiHistX[x-iSx+3] + aiHistX[x-iSx+2] + aiHistX[x-iSx+1];

		//	iGap = iSum_Left - iSum_Right;

		//	if (iGap>400 &&  iGap > iMax_Left)
		//	{
		//		iMax_Left = iGap;
		//		iMinX2 = x;
		//	}
		//}
		for (x=tmpSx ; x<iMaxX; x++)
		{
			iSum_Left  = aiHistX[x-iSx-4] + aiHistX[x-iSx-3] + aiHistX[x-iSx-2] + aiHistX[x-iSx-1];
			iSum_Right = aiHistX[x-iSx+4] + aiHistX[x-iSx+3] + aiHistX[x-iSx+2] + aiHistX[x-iSx+1];

			iGap = iSum_Left - iSum_Right;

			if (iGap>600 &&  iGap > iMax_Left)
			{
				iMax_Left = iGap;
				iMinX2 = x;
			}
		}


		iMax_Right = 0;
		iMaxX2 = 0;

		tmpSx = iMinX + 30;
		tmpEx = iMinX + 400;
		if(tmpSx < (iSx+5))
			tmpSx = (iSx+5);
		if(tmpEx > (iEx-5))
			tmpEx = (iEx-5);


		//for (x=tmpSx ; x<tmpEx; x++)
		//{
		//	iSum_Left  = aiHistX[x-iSx-4] + aiHistX[x-iSx-3] + aiHistX[x-iSx-2] + aiHistX[x-iSx-1];
		//	iSum_Right = aiHistX[x-iSx+4] + aiHistX[x-iSx+3] + aiHistX[x-iSx+2] + aiHistX[x-iSx+1];

		//	iGap = iSum_Right - iSum_Left;

		//	if (iGap>400 && iGap > iMax_Right)
		//	{
		//		iMax_Right = iGap;
		//		iMaxX2 = x;
		//	}
		//}
		for (x=tmpSx ; x<tmpEx; x++)
		{
			iSum_Left  = aiHistX[x-iSx-4] + aiHistX[x-iSx-3] + aiHistX[x-iSx-2] + aiHistX[x-iSx-1];
			iSum_Right = aiHistX[x-iSx+4] + aiHistX[x-iSx+3] + aiHistX[x-iSx+2] + aiHistX[x-iSx+1];

			iGap = iSum_Right - iSum_Left;

			if (iGap>600 && iGap > iMax_Right)
			{
				iMax_Right = iGap;
				iMaxX2 = x;
			}
		}


		if( iMaxX-iMinX>30 && iMaxX-iMinX<maxSize && iMinX>0)
		{
			iMinX = iMinX;
			iMaxX = iMaxX;
		}
		else if( iMaxX2-iMinX>30 && iMaxX2-iMinX<maxSize && iMinX>0 )
		{
			iMinX = iMinX;
			iMaxX = iMaxX2;
		}
		else if( iMaxX-iMinX2>30 && iMaxX-iMinX2<maxSize && iMinX2>0 )
		{
			iMinX = iMinX2;
			iMaxX = iMaxX;
		}

		/* Y 방향 히스토그램 */
		for (y=iSy ; y<iEy ; y++)
		{
			iPos = y * pitch + iMinX;
			iSum = 0;

			for (x=iMinX ; x<iMaxX; x++)
			{
				iSum += ucImage[iPos++];
			}

			aiHistY[y-iSy] = iSum;
		}

		for (y=iSy+5 ; y<iEy-5 ; y++)
		{
			iSum_Top	= aiHistY[y-iSy-4] + aiHistY[y-iSy-3] + aiHistY[y-iSy-2] + aiHistY[y-iSy-1];
			iSum_Bottom = aiHistY[y-iSy+4] + aiHistY[y-iSy+3] + aiHistY[y-iSy+2] + aiHistY[y-iSy+1];

			iGap = iSum_Top - iSum_Bottom;

			if ( iGap > iMax_Up )
			{
				iMax_Up = iGap;
				iMinY = y;
			}

			iGap = iSum_Bottom - iSum_Top;

			if ( iGap > iMax_Down )
			{
				iMax_Down = iGap;
				iMaxY = y;
			}
		}


		if ( iMinY >= iMaxY )
		{
			int iMinY2		= -9999;
			int iMaxY2		= -9999;
			int iMax_Up2	= 0;
			int iMax_Down2	= 0;

			int tmpSy = iMinY + 5;
			int tmpEy = iEy-5;

			for (y=tmpSy ; y<tmpEy ; y++)
			{
				iSum_Top	= aiHistY[y-iSy-4] + aiHistY[y-iSy-3] + aiHistY[y-iSy-2] + aiHistY[y-iSy-1];
				iSum_Bottom = aiHistY[y-iSy+4] + aiHistY[y-iSy+3] + aiHistY[y-iSy+2] + aiHistY[y-iSy+1];

				iGap = iSum_Bottom - iSum_Top;

				if ( iGap > iMax_Down2 && (iGap>_CIRCLE_MARK_GAP) )
				{
					iMax_Down2 = iGap;
					iMaxY2 = y;
				}
			}


			tmpSy = iSy+5;
			tmpEy = iMaxY - 5;

			for (y=tmpSy ; y<tmpEy ; y++)
			{
				iSum_Top	= aiHistY[y-iSy-4] + aiHistY[y-iSy-3] + aiHistY[y-iSy-2] + aiHistY[y-iSy-1];
				iSum_Bottom = aiHistY[y-iSy+4] + aiHistY[y-iSy+3] + aiHistY[y-iSy+2] + aiHistY[y-iSy+1];

				iGap = iSum_Top - iSum_Bottom;

				if ( iGap > iMax_Up2 && (iGap>_CIRCLE_MARK_GAP) )
				{
					iMax_Up2 = iGap;
					iMinY2 = y;
				}
			}

			if( (iMaxY-iMinY2)>50 && (iMaxY-iMinY2)<250)
			{
				iMinY = iMinY2;
			}
			else if( (iMaxY2-iMinY)>50 && (iMaxY2-iMinY)<250)
			{
				iMaxY = iMaxY2;
			}
		}
		else if( (iMaxY-iMinY) > 400 )
		{
			int iMaxY2		= -9999;
			int iMinY2		= -9999;
			int iMax_Up2	= 0;
			int iMax_Down2	= 0;

			int tmpSy = iMinY + 5;
			int tmpEy = iMaxY - 5;

			for (y=tmpSy ; y<tmpEy ; y++)
			{
				iSum_Top	= aiHistY[y-iSy-4] + aiHistY[y-iSy-3] + aiHistY[y-iSy-2] + aiHistY[y-iSy-1];
				iSum_Bottom = aiHistY[y-iSy+4] + aiHistY[y-iSy+3] + aiHistY[y-iSy+2] + aiHistY[y-iSy+1];

				iGap = iSum_Top - iSum_Bottom;

				if ( iGap > iMax_Up2 && (iGap>_CIRCLE_MARK_GAP) )
				{
					iMax_Up2 = iGap;
					iMinY2 = y;
				}

				iGap = iSum_Bottom - iSum_Top;

				if ( iGap > iMax_Down2 && (iGap>_CIRCLE_MARK_GAP) )
				{
					iMax_Down2 = iGap;
					iMaxY2 = y;
				}
			}

			if( (iMinY2>0) && ((iMaxY-iMinY2)>50 && (iMaxY-iMinY2)<250) )
			{
				iMinY = iMinY2;
			}
			else if ( (iMaxY2>0) && ((iMaxY2-iMinY)>50 && (iMaxY2-iMinY)<250) )
			{
				iMaxY = iMaxY2;
			}
		}


		if(iMinX>iMaxX || (iMaxX-iMinX>maxSize) )
		{
			vision.boxlist[CCD].addList(iMinX, iMinY, iMaxX, iMaxY, PS_SOLID, M_COLOR_RED);
			sTempLang.LoadStringA(IDS_STRING259);
			sLangChange.Format("좌우 인식 위치가 비정상 입니다.");
			sLog.Format(sLangChange);
			pFrame->putListLog(sLog);
			return false;
		}


		if(iMinY>iMaxY || (iMaxY-iMinY>maxSize) )
		{
			vision.boxlist[CCD].addList(iMinX, iMinY, iMaxX, iMaxY, PS_SOLID, M_COLOR_RED);
			sTempLang.LoadStringA(IDS_STRING255);
			sLog.Format("상하 인식 위치가 비정상 입니다.");
			pFrame->putListLog(sLog);
			return false;
		}


		if ( iMaxX < 0 || iMaxY < 0 || iMaxX > sizeX || iMaxY > sizeY	||
			iMinX < 0 || iMinY < 0 || iMinX > sizeX || iMinY > sizeY )
		{
			sTempLang.LoadStringA(IDS_STRING252);
			sLog.Format("[마크 #%d] Max, Min 위치를 찾지 못했습니다.");
			pFrame->putListLog(sLog);
			return false;
		}

		vision.boxlist[CCD].addList(iMinX, iMinY, iMaxX, iMaxY, PS_DOT, M_COLOR_RED);

	return CPoint((iMaxX+iMinX)/2,(iMaxY+iMinY)/2);
}


bool CTask::_findCirclePosBin(unsigned char* ucImage, int pitch, int sizeX, int sizeY, CRect* rcRoi)
{
	int maxSize = 200;

	CString sLog;

	if ( ucImage == NULL )
	{
		sLangChange.LoadStringA(IDS_STRING1303);
		sLog.Format(sLangChange);		//영상 버퍼가 잘못되었습니다.
		errMsg2(Task.AutoFlag,sLog);
		return false;
	}

	if ( sizeX <= 0 || sizeY <= 0)
	{
		sLangChange.LoadStringA(IDS_STRING1304);
		sLog.Format(sLangChange + _T(" ( X : %d Y : %d )"), sizeX, sizeY);		//영상 사이즈가 잘못되었습니다.
		errMsg2(Task.AutoFlag, sLog);
		return false;
	}

	int aiHistX[5000];
	int aiHistY[5000];

	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;


	for (int i=0 ; i<4 ; i++)
	{
		if ( rcRoi[i].left < 0 || rcRoi[i].top < 0 || rcRoi[i].right > sizeX || rcRoi[i].bottom > sizeY )
		{
			sTempLang.LoadStringA(IDS_STRING257);
			sLangChange.Format(sTempLang, i+1, rcRoi[i].left, rcRoi[i].top, rcRoi[i].right, rcRoi[i].bottom);		//[마크 #%d] 원형 마크 검색 영역이 잘못되었습니다.
			sLog.Format(sLangChange);
			pFrame->putListLog(sLog);
			return false;
		}

		int iSx, iSy, iEx, iEy;
		int x, y, iPos;
		int iMaxX = -1, iMinX = 9999;
		int iMaxY = -1, iMinY = 9999;
		int iMax_Left = -1 , iMax_Right = -1, iMax_Up = -1, iMax_Down = -1;

		int iMaxX2 = -1, iMinX2 = 9999;
		int iMaxY2 = -1, iMinY2 = 9999;
		int iMax_Left2 = -1 , iMax_Right2 = -1, iMax_Up2 = -1, iMax_Down2 = -1;

		int iSum;		
		int iGap;

		int iSum_Left, iSum_Right;
		int iSum_Top, iSum_Bottom;

		iSx = rcRoi[i].left;
		iSy = rcRoi[i].top;
		iEx = rcRoi[i].right;
		iEy = rcRoi[i].bottom;

		::memset(aiHistY, 0, sizeof(int)*(5000));
		::memset(aiHistX, 0, sizeof(int)*(5000));


		/* X방향 히스토그램 */
		for (x=iSx ; x<iEx ; x++)
		{
			iPos = iSy * pitch + x;
			iSum = 0;

			for (y=iSy ; y<iEy ; y++)
			{
//				iSum += (ucImage[iPos]*ucImage[iPos]);
				iSum += (ucImage[iPos] > 30)?1:0;
				iPos += pitch;
			}

			aiHistX[x-iSx] = iSum;
		}

		/* X방향부터 엣지 찾기 */
		for (x=iSx+5 ; x<iEx-5 ; x++)
		{
			iSum_Left  = aiHistX[x-iSx-4] + aiHistX[x-iSx-3] + aiHistX[x-iSx-2] + aiHistX[x-iSx-1];
			iSum_Right = aiHistX[x-iSx+4] + aiHistX[x-iSx+3] + aiHistX[x-iSx+2] + aiHistX[x-iSx+1];

			iGap = iSum_Left - iSum_Right;

			if (iGap>300 &&  iGap > iMax_Left)
			{
				iMax_Left = iGap;
				iMinX = x;
			}

			iGap = iSum_Right - iSum_Left;

			if (iGap>300 &&  iGap > iMax_Right)
			{
				iMax_Right = iGap;
				iMaxX = x;
			}
		}


		iMax_Left = 0;
		iMinX2 = 0;
		int tmpSx = iMaxX-400;
		int tmpEx = iMinX - 30;
		if(tmpSx < (iSx+5))
			tmpSx = (iSx+5);
		if(tmpEx > (iEx-5))
			tmpEx = (iSx-5);

		for (x=tmpSx ; x<iMaxX; x++)
		{
			iSum_Left  = aiHistX[x-iSx-4] + aiHistX[x-iSx-3] + aiHistX[x-iSx-2] + aiHistX[x-iSx-1];
			iSum_Right = aiHistX[x-iSx+4] + aiHistX[x-iSx+3] + aiHistX[x-iSx+2] + aiHistX[x-iSx+1];

			iGap = iSum_Left - iSum_Right;

			if (iGap>400 &&  iGap > iMax_Left)
			{
				iMax_Left = iGap;
				iMinX2 = x;
			}
		}


		iMax_Right = 0;
		iMaxX2 = 0;

		tmpSx = iMinX + 30;
		tmpEx = iMinX + 400;
		if(tmpSx < (iSx+5))
			tmpSx = (iSx+5);
		if(tmpEx > (iEx-5))
			tmpEx = (iEx-5);


		for (x=tmpSx ; x<tmpEx; x++)
		{
			iSum_Left  = aiHistX[x-iSx-4] + aiHistX[x-iSx-3] + aiHistX[x-iSx-2] + aiHistX[x-iSx-1];
			iSum_Right = aiHistX[x-iSx+4] + aiHistX[x-iSx+3] + aiHistX[x-iSx+2] + aiHistX[x-iSx+1];

			iGap = iSum_Right - iSum_Left;

			if (iGap>400 && iGap > iMax_Right)
			{
				iMax_Right = iGap;
				iMaxX2 = x;
			}
		}


		if( iMaxX-iMinX>30 && iMaxX-iMinX<maxSize && iMinX>0)
		{
			iMinX = iMinX;
			iMaxX = iMaxX;
		}
		else if( iMaxX2-iMinX>30 && iMaxX2-iMinX<maxSize && iMinX>0 )
		{
			iMinX = iMinX;
			iMaxX = iMaxX2;
		}
		else if( iMaxX-iMinX2>30 && iMaxX-iMinX2<maxSize && iMinX2>0 )
		{
			iMinX = iMinX2;
			iMaxX = iMaxX;
		}

		/* Y 방향 히스토그램 */
		for (y=iSy ; y<iEy ; y++)
		{
			iPos = y * pitch + iMinX;
			iSum = 0;

			for (x=iMinX ; x<iMaxX; x++)
			{
				iSum += (ucImage[iPos++]>30)?1:0;
			}

			aiHistY[y-iSy] = iSum;
		}

		for (y=iSy+5 ; y<iEy-5 ; y++)
		{
			iSum_Top	= aiHistY[y-iSy-4] + aiHistY[y-iSy-3] + aiHistY[y-iSy-2] + aiHistY[y-iSy-1];
			iSum_Bottom = aiHistY[y-iSy+4] + aiHistY[y-iSy+3] + aiHistY[y-iSy+2] + aiHistY[y-iSy+1];

			iGap = iSum_Top - iSum_Bottom;

			if ( iGap > iMax_Up )
			{
				iMax_Up = iGap;
				iMinY = y;
			}

			iGap = iSum_Bottom - iSum_Top;

			if ( iGap > iMax_Down )
			{
				iMax_Down = iGap;
				iMaxY = y;
			}
		}


		if ( iMinY >= iMaxY )
		{
			int iMinY2		= -9999;
			int iMaxY2		= -9999;
			int iMax_Up2	= 0;
			int iMax_Down2	= 0;

			int tmpSy = iMinY + 5;
			int tmpEy = iEy-5;

			for (y=tmpSy ; y<tmpEy ; y++)
			{
				iSum_Top	= aiHistY[y-iSy-4] + aiHistY[y-iSy-3] + aiHistY[y-iSy-2] + aiHistY[y-iSy-1];
				iSum_Bottom = aiHistY[y-iSy+4] + aiHistY[y-iSy+3] + aiHistY[y-iSy+2] + aiHistY[y-iSy+1];

				iGap = iSum_Bottom - iSum_Top;

				if ( iGap > iMax_Down2 && (iGap>1000) )
				{
					iMax_Down2 = iGap;
					iMaxY2 = y;
				}
			}


			tmpSy = iSy+5;
			tmpEy = iMaxY - 5;

			for (y=tmpSy ; y<tmpEy ; y++)
			{
				iSum_Top	= aiHistY[y-iSy-4] + aiHistY[y-iSy-3] + aiHistY[y-iSy-2] + aiHistY[y-iSy-1];
				iSum_Bottom = aiHistY[y-iSy+4] + aiHistY[y-iSy+3] + aiHistY[y-iSy+2] + aiHistY[y-iSy+1];

				iGap = iSum_Top - iSum_Bottom;

				if ( iGap > iMax_Up2 && (iGap>1000) )
				{
					iMax_Up2 = iGap;
					iMinY2 = y;
				}
			}

			if( (iMaxY-iMinY2)>50 && (iMaxY-iMinY2)<250)
			{
				iMinY = iMinY2;
			}
			else if( (iMaxY2-iMinY)>50 && (iMaxY2-iMinY)<250)
			{
				iMaxY = iMaxY2;
			}
		}
		else if( (iMaxY-iMinY) > 400 )
		{
			int iMaxY2		= -9999;
			int iMinY2		= -9999;
			int iMax_Up2	= 0;
			int iMax_Down2	= 0;

			int tmpSy = iMinY + 5;
			int tmpEy = iMaxY - 5;

			for (y=tmpSy ; y<tmpEy ; y++)
			{
				iSum_Top	= aiHistY[y-iSy-4] + aiHistY[y-iSy-3] + aiHistY[y-iSy-2] + aiHistY[y-iSy-1];
				iSum_Bottom = aiHistY[y-iSy+4] + aiHistY[y-iSy+3] + aiHistY[y-iSy+2] + aiHistY[y-iSy+1];

				iGap = iSum_Top - iSum_Bottom;

				if ( iGap > iMax_Up2 && (iGap>1000) )
				{
					iMax_Up2 = iGap;
					iMinY2 = y;
				}

				iGap = iSum_Bottom - iSum_Top;

				if ( iGap > iMax_Down2 && (iGap>1000) )
				{
					iMax_Down2 = iGap;
					iMaxY2 = y;
				}
			}

			if( (iMinY2>0) && ((iMaxY-iMinY2)>50 && (iMaxY-iMinY2)<250) )
			{
				iMinY = iMinY2;
			}
			else if ( (iMaxY2>0) && ((iMaxY2-iMinY)>50 && (iMaxY2-iMinY)<250) )
			{
				iMaxY = iMaxY2;
			}
		}


		if(iMinX>iMaxX || (iMaxX-iMinX>maxSize) )
		{
			vision.boxlist[CCD].addList(iMinX, iMinY, iMaxX, iMaxY, PS_SOLID, M_COLOR_RED);
			sTempLang.LoadStringA(IDS_STRING259);
			sLangChange.Format(sTempLang, i+1, iMinX, iMaxX);	//[마크 #%d] 좌우 인식 위치가 비정상 입니다.
			sLog.Format(sLangChange);pFrame->putListLog(sLog);
			return false;
		}


		if(iMinY>iMaxY || (iMaxY-iMinY>maxSize) )
		{
			vision.boxlist[CCD].addList(iMinX, iMinY, iMaxX, iMaxY, PS_SOLID, M_COLOR_RED);
			sTempLang.LoadStringA(IDS_STRING255);
			sLangChange.Format(sTempLang, i+1, iMinY, iMaxY);
			sLog.Format(sLangChange);	//[마크 #%d] 상하 인식 위치가 비정상 입니다. (상 %d, 하 %d)
			pFrame->putListLog(sLog);
			return false;
		}


		if ( iMaxX < 0 || iMaxY < 0 || iMaxX > sizeX || iMaxY > sizeY	||
			iMinX < 0 || iMinY < 0 || iMinX > sizeX || iMinY > sizeY )
		{
			sTempLang.LoadStringA(IDS_STRING252);
			sLangChange.Format(sTempLang, i+1);
			sLog.Format(sLangChange);	//"[마크 #%d] Max, Min 위치를 찾지 못했습니다."
			pFrame->putListLog(sLog);
			return false;
		}

		vision.boxlist[CCD].addList(iMinX, iMinY, iMaxX, iMaxY, PS_DOT, M_COLOR_RED);

		m_CircleP[i].x = (iMaxX+iMinX)/2;
		m_CircleP[i].y = (iMaxY+iMinY)/2;

		vision.crosslist[CCD].addList(m_CircleP[i], 200, M_COLOR_RED);
	}

	return true;
}


bool CTask::_findRectPos(unsigned char* ucImage, int pitch, int sizeX, int sizeY, int index, CRect& rcRoi)
{
	CString sLog;
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	int offsetX = (rcRoi.right-rcRoi.left) / 4;
	int offsetY = (rcRoi.bottom-rcRoi.top) / 2;

	if(index == 8 || index == 12)
		offsetY = 0;
	 
	int min_max_Gap = 1000;

	if ( ucImage == NULL )
	{
		sLangChange.LoadStringA(IDS_STRING1303);
		sLog.Format(sLangChange);		//영상 버퍼가 잘못되었습니다.
		errMsg2(Task.AutoFlag,sLog);
		return false;
	}

	if ( sizeX <= 0 || sizeY <= 0)
	{
		sLangChange.LoadStringA(IDS_STRING1304);
		sLog.Format(sLangChange + _T(" ( X : %d Y : %d )"), sizeX, sizeY);		//영상 사이즈가 잘못되었습니다.
		errMsg2(Task.AutoFlag, sLog);
		return false;
	}


	int aiHistX[5000];
	int aiHistY[5000];

	if ( rcRoi.left < 0 || rcRoi.top < 0 || rcRoi.right > sizeX || rcRoi.bottom > sizeY )
	{
		sLangChange.LoadStringA(IDS_STRING1335);	//원형 마크 검색 영역이 잘못되었습니다.
		sLog.Format(sLangChange + _T(" ( L : %d T : %d R : %d B : %d )"), rcRoi.left, rcRoi.top, rcRoi.right, rcRoi.bottom);
		errMsg2(Task.AutoFlag, sLog);
		return false;
	}

	//vision.boxlist[CCD].addList(rcRoi, PS_DOT, M_COLOR_BLUE);

	int iSx, iSy, iEx, iEy, iCx, iCy;
	int x, y, iPos, iSum, iGap;

	::memset(aiHistY, 0, sizeof(int)*(5000));
	::memset(aiHistX, 0, sizeof(int)*(5000));


	iSx = rcRoi.left	+ offsetX;
	iEx = rcRoi.right	- offsetX;
	iSy = rcRoi.top		- offsetY;
	iEy = rcRoi.bottom	+ offsetY;
	iCy = (iSy+iEy) / 2;


	if(iSx<0)				iSx = 0;
	if(iSy<0)				iSy = 0;
	if(iEx>=sizeX)			iEx = sizeX - 1;
	if(iEy>=sizeY)			iEy = sizeY - 1;

	
	for (y=iSy ; y<iEy ; y++)
	{
		iSum = 0;
		iPos = y*pitch + iSx;

		for (x=iSx ; x<iEx ; x++)
		{
			iSum += ucImage[iPos];
			iPos++;
		}

		aiHistY[y] = iSum;
	}


	int iMaxX = -1, iMinX = 9999;
	int iMaxY = -1, iMinY = 9999;
	int iMax_Left = -1 , iMax_Right = -1, iMax_Top = -1, iMax_Bottom = -1;

	int iSum_Top,	iSum_Bottom;

	for (y=iSy+8 ; y<iCy ; y++)
	{
		iSum_Top	= aiHistY[y-7] + aiHistY[y-5] + aiHistY[y-3] + aiHistY[y-1];
		iSum_Bottom = aiHistY[y+7] + aiHistY[y+5] + aiHistY[y+3] + aiHistY[y+1];

		iGap = iSum_Top - iSum_Bottom;

		if ( iGap > iMax_Top)
		{
			iMax_Top = iGap;
			iMinY = y;
		}
	}

// 	vision.boxlist[CCD].addList(iSx, iSy, iEx, iCy, PS_SOLID, M_COLOR_BLUE);
// 	vision.linelist[CCD].addList(rcRoi.left, iMinY, rcRoi.right, iMinY, PS_SOLID, M_COLOR_BLUE);


	for (y=iCy ; y<iEy-8 ; y++)
	{
		iSum_Top	= aiHistY[y-7] + aiHistY[y-5] + aiHistY[y-3] + aiHistY[y-1];
		iSum_Bottom = aiHistY[y+7] + aiHistY[y+5] + aiHistY[y+3] + aiHistY[y+1];

		iGap = iSum_Bottom - iSum_Top;

		if ( iGap > iMax_Bottom)
		{
			iMax_Bottom = iGap;
			iMaxY = y;
		}
	}

//  	vision.boxlist[CCD].addList(iSx, iCy, iEx, iEy, PS_SOLID, M_COLOR_GREEN);
//  	vision.linelist[CCD].addList(rcRoi.left, iMaxY, rcRoi.right, iMaxY, PS_SOLID, M_COLOR_GREEN);

	if ( iMax_Top < min_max_Gap )
	{
		vision.boxlist[CCD].addList(rcRoi, PS_SOLID, M_COLOR_RED);
		sLangChange.LoadStringA(IDS_STRING253);
		sLog.Format(sLangChange +_T(" (%d)"), index, iMax_Top);	//[마크 #%d] 상부 경계선이 불분명합니다
		pFrame->putListLog(sLog);
		return false;
	}

	if ( iMax_Bottom < min_max_Gap )
	{
		vision.boxlist[CCD].addList(rcRoi, PS_SOLID, M_COLOR_RED);
		sLangChange.LoadStringA(IDS_STRING261);	//[마크 #%d] 하부 경계선이 불분명합니다.
		sLog.Format(sLangChange + _T(" (%d)"), index, iMax_Bottom);
		pFrame->putListLog(sLog);
		return false;
	}

	if ( iMinY >= iMaxY || iMinY<1)
	{
		vision.boxlist[CCD].addList(rcRoi, PS_SOLID, M_COLOR_RED);
		sLangChange.LoadStringA(IDS_STRING254);
		sLog.Format(sLangChange, index, iMinY, iMaxY);	//"[마크 #%d] 상하 경계선 인식 결과가 비정상 입니다. [상:%d, 하:%d]"
		pFrame->putListLog(sLog);
		return false;
	}


	offsetX = (rcRoi.right-rcRoi.left) / 2;
	offsetY = (rcRoi.bottom-rcRoi.top) / 4;

	if(index == 8 || index==12)
		offsetY = 10;

	iSx = rcRoi.left	- offsetX;
	iEx = rcRoi.right	+ offsetX;
	iSy = iMinY			+ offsetY;
	iEy = iMaxY			- offsetY;
	iCx = (iSx+iEx) / 2;

	if(iSx<0)			iSx = 0;
	if(iSy<0)			iSy = 0;
	if(iEx>=sizeX)		iEx = sizeX - 1;
	if(iEy>=sizeY)		iEy = sizeY - 1;


	/* X방향 히스토그램 */
	for (x=iSx; x<iEx; x++)
	{
		iSum = 0;
		iPos = iSy*pitch + x;

		for (y=iSy ; y<iEy ; y++)
		{
			iSum += ucImage[iPos];
			iPos += pitch;
		}

		aiHistX[x] = iSum;
	}


	int iSum_Left,	iSum_Right;

	for (x=iSx+5; x<iCx; x++)
	{
		iSum_Left	= aiHistX[x-4] + aiHistX[x-3] + aiHistX[x-2] + aiHistX[x-1];
		iSum_Right	= aiHistX[x+4] + aiHistX[x+3] + aiHistX[x+2] + aiHistX[x+1];

		iGap = iSum_Left - iSum_Right;

		if ( iGap > iMax_Left )
		{
			iMax_Left = iGap;
			iMinX = x;
		}
	}

// 	vision.boxlist[CCD].addList(iSx, iSy, iCx, iEy, PS_SOLID, M_COLOR_BLUE);
// 	vision.linelist[CCD].addList(iMinX, rcRoi.top, iMinX, rcRoi.bottom, PS_SOLID, M_COLOR_RED);

	for (x=iCx; x<iEx-8; x++)
	{
		iSum_Left	= aiHistX[x-4] + aiHistX[x-3] + aiHistX[x-2] + aiHistX[x-1];
		iSum_Right	= aiHistX[x+4] + aiHistX[x+3] + aiHistX[x+2] + aiHistX[x+1];

		iGap = iSum_Right - iSum_Left;

		if ( iGap > iMax_Right )
		{
			iMax_Right = iGap;
			iMaxX = x;
		} 
	}

//	vision.boxlist[CCD].addList(iCx, iSy, iEx, iEy, PS_SOLID, M_COLOR_GREEN);
//	vision.linelist[CCD].addList(iMaxX, rcRoi.top, iMaxX, rcRoi.bottom, PS_SOLID, M_COLOR_GREEN);


	if ( iMax_Left < min_max_Gap )
	{
	//	vision.boxlist[CCD].addList(rcRoi, PS_SOLID, M_COLOR_RED);

		sLangChange.LoadStringA(IDS_STRING260);	//[마크 #%d] 좌측 경계선이 불분명합니다.
		sLog.Format(sLangChange + _T(" (%d)"), index, iMax_Left);
		pFrame->putListLog(sLog);

		vision.boxlist[CCD].addList(iSx, iSy, iCx, iEy, PS_SOLID, M_COLOR_BLUE);
		vision.linelist[CCD].addList(iMinX, rcRoi.top, iMinX, rcRoi.bottom, PS_SOLID, M_COLOR_RED);

		return false;
	}

	if ( iMax_Right < min_max_Gap )
	{
		vision.boxlist[CCD].addList(rcRoi, PS_SOLID, M_COLOR_RED);
		sLangChange.LoadStringA(IDS_STRING256);	//[마크 #%d] 우측 경계선이 불분명합니다.
		sLog.Format(sLangChange + _T(" (%d)"), index, iMax_Right);
		pFrame->putListLog(sLog);

		vision.boxlist[CCD].addList(iCx, iSy, iEx, iEy, PS_SOLID, M_COLOR_RED);
		vision.linelist[CCD].addList(iMaxX, rcRoi.top, iMaxX, rcRoi.bottom, PS_SOLID, M_COLOR_RED);

		return false;
	}


	if(iMinX<5)
	{
		if (index==15 || index==18)
			iMinX = 5;
	}

	if(iMinX>iMaxX || iMinX<1)
	{
		vision.boxlist[CCD].addList(rcRoi, PS_SOLID, M_COLOR_RED);
		sLangChange.LoadStringA(IDS_STRING256);	//[마크 #%d] 좌우 경계선 인식 결과가 비정상 입니다.
		sLog.Format(sLangChange, index, iMinX, iMaxX);
		pFrame->putListLog(sLog);
		return false;
	}

	
	rcRoi.left		= iMinX;
	rcRoi.right		= iMaxX;
	rcRoi.top		= iMinY;
	rcRoi.bottom	= iMaxY;

	return true;
}

bool CTask::g_FindRectPos(unsigned char* pImage, int nPitch, int nSizeX, int nSizeY, int nIndex, CRect& clRect)
{
	TCHAR szLog[SIZE_OF_1K];
	
	int nOffsetX = (int)((clRect.right - clRect.left) / 3);
	int nOffsetY = (int)((clRect.bottom - clRect.top) / 2);


	//	if(index == 8 || index == 12) 구자현 수정
	//		offsetY = 0;

	int min_max_Gap = 1000;

	if (pImage == NULL)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("영상 버퍼가 잘못되었습니다."));
		theApp.MainDlg->putListLog(szLog);
		return false;
	}

	if (nSizeX <= 0 || nSizeY <= 0)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("영상 사이즈가 잘못되었습니다. ( X : %d Y : %d )"), nSizeX, nSizeY);
		theApp.MainDlg->putListLog(szLog);
		return false;
	}


	int aiHistX[5000];
	int aiHistY[5000];

	if (clRect.left < 0 || clRect.top < 0 || clRect.right > nSizeX || clRect.bottom > nSizeY)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("원형 마크 검색 영역이 잘못 되었습니다. ( L : %d T : %d R : %d B : %d )"), clRect.left, clRect.top, clRect.right, clRect.bottom);
		theApp.MainDlg->putListLog(szLog);
		return false;
	}

	//	vision.boxlist[CCD].addList(rcRoi, PS_DOT, M_COLOR_BLUE);

	int iSx, iSy, iEx, iEy, iCx, iCy;
	int x, y, iPos, iSum, avgX, avgY;

	::memset(aiHistY, 0, sizeof(int)*(5000));
	::memset(aiHistX, 0, sizeof(int)*(5000));


	iSx = clRect.left + nOffsetX;
	iEx = clRect.right - nOffsetX;
	iSy = clRect.top - nOffsetY;
	iEy = clRect.bottom + nOffsetY;
	//iSy = rcRoi.top		- offsetY;
	//iEy = rcRoi.bottom	+ offsetY;
	iCy = (iSy + iEy) / 2;


	if (iSx<0)				iSx = 0;
	if (iSy<0)				iSy = 0;
	if (iEx >= nSizeX)			iEx = nSizeX - 1;
	if (iEy >= nSizeY)			iEy = nSizeY - 1;

	avgY = 0;
	for (y = iSy; y < iEy; y++)
	{
		iSum = 0;
		iPos = y * nPitch + iSx;

		for (x = iSx; x < iEx; x++)
		{
			iSum += pImage[iPos];
			iPos++;
		}

		aiHistY[y] = iSum;
		avgY += iSum;
	}

	avgY = (int)(avgY / (iEy - iSy) * 0.9);


	int iMaxX = -1, iMinX = 9999;
	int iMaxY = -1, iMinY = 9999;
	int iMax_Left = -1, iMax_Right = -1, iMax_Top = -1, iMax_Bottom = -1;

	int iSum_Top, iSum_Bottom;

	for (y = iCy; y > iSy + 8; y--)
	{
		if (aiHistY[y - 1] > avgY && aiHistY[y - 3] > avgY && aiHistY[y - 5] > avgY && aiHistY[y - 7] > avgY)
		{
			iSum_Top = aiHistY[y - 7] + aiHistY[y - 5] + aiHistY[y - 3] + aiHistY[y - 1];
			iSum_Bottom = aiHistY[y + 7] + aiHistY[y + 5] + aiHistY[y + 3] + aiHistY[y + 1];

			iMax_Top = iSum_Top - iSum_Bottom;
			iMinY = y;

			break;
		}
	}

	if (y == iSy + 8)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("SFR 사각형[#%d] 상부 인식 실패."), nIndex);
		theApp.MainDlg->putListLog(szLog);
		return false;
	}

	// 	vision.boxlist[CCD].addList(iSx, iSy, iEx, iCy, PS_SOLID, M_COLOR_BLUE);
	// 	vision.linelist[CCD].addList(rcRoi.left, iMinY, rcRoi.right, iMinY, PS_SOLID, M_COLOR_BLUE);


	for (y = iCy; y < iEy - 8; y++)
	{
		if (aiHistY[y + 1] > avgY && aiHistY[y + 3] > avgY && aiHistY[y + 5] > avgY && aiHistY[y + 7] > avgY)
		{
			iSum_Top = aiHistY[y - 7] + aiHistY[y - 5] + aiHistY[y - 3] + aiHistY[y - 1];
			iSum_Bottom = aiHistY[y + 7] + aiHistY[y + 5] + aiHistY[y + 3] + aiHistY[y + 1];

			iMax_Bottom = iSum_Bottom - iSum_Top;
			iMaxY = y;

			break;
		}
	}

	if (y == iEy - 8)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("SFR 사각형[#%d] 하부 인식 실패."), nIndex);
		theApp.MainDlg->putListLog(szLog);
		return false;
	}

	if (iMax_Top < min_max_Gap)
	{
		//g_clVision.DrawMOverlayBox(nUnit, nUnit, clRect, M_COLOR_RED, 1, FALSE, PS_SOLID);

		_stprintf_s(szLog, SIZE_OF_1K, _T("[마크 #%d] 상부 경계선이 불분명합니다. (%d)"), nIndex, iMax_Top);
		theApp.MainDlg->putListLog(szLog);
		return false;
	}

	if (iMax_Bottom < min_max_Gap)
	{
		//g_clVision.DrawMOverlayBox(nUnit, nUnit, clRect, M_COLOR_RED, 1, FALSE, PS_SOLID);

		_stprintf_s(szLog, SIZE_OF_1K, _T("[마크 #%d] 하부 경계선이 불분명합니다. (%d)"), nIndex, iMax_Bottom);
		theApp.MainDlg->putListLog(szLog);
		return false;
	}

	if (iMinY >= iMaxY || iMinY<1)
	{
		//g_clVision.DrawMOverlayBox(nUnit, nUnit, clRect, M_COLOR_RED, 1, FALSE, PS_SOLID);

		_stprintf_s(szLog, SIZE_OF_1K, _T("[마크 #%d] 상하 경계선 인식 결과가 비정상 입니다. [상:%d, 하:%d]"), nIndex, iMinY, iMaxY);
		theApp.MainDlg->putListLog(szLog);
		return false;
	}


	nOffsetX = (clRect.right - clRect.left) / 2;
	nOffsetY = (int)((clRect.bottom - clRect.top) / 3);

	//	if(index == 8 || index==12)
	//		offsetY = 10;

	iSx = clRect.left - nOffsetX;
	iEx = clRect.right + nOffsetX;
	iSy = iMinY + nOffsetY;
	iEy = iMaxY - nOffsetY;
	iCx = (iSx + iEx) / 2;

	if (iSx < 0)			iSx = 0;
	if (iSy < 0)			iSy = 0;
	if (iEx >= nSizeX)		iEx = nSizeX - 1;
	if (iEy >= nSizeY)		iEy = nSizeY - 1;


	/* X방향 히스토그램 */
	avgX = 0;
	for (x = iSx; x < iEx; x++)
	{
		iSum = 0;
		iPos = iSy * nPitch + x;

		for (y = iSy; y < iEy; y++)
		{
			iSum += pImage[iPos];
			iPos += nPitch;
		}

		aiHistX[x] = iSum;
		avgX += iSum;
	}

	avgX = (int)(avgX / ((iEx - iSx) * 0.9));


	int iSum_Left, iSum_Right;

	for (x = iCx; x > iSx + 5; x--)
	{
		if (aiHistX[x - 4] > avgX && aiHistX[x - 3] > avgX && aiHistX[x - 2] > avgX && aiHistX[x - 1] > avgX)
		{
			iSum_Left = aiHistX[x - 4] + aiHistX[x - 3] + aiHistX[x - 2] + aiHistX[x - 1];
			iSum_Right = aiHistX[x + 4] + aiHistX[x + 3] + aiHistX[x + 2] + aiHistX[x + 1];

			iMax_Left = iSum_Left - iSum_Right;
			iMinX = x;

			break;
		}
	}

	if ((x == iSx + 5) && (nIndex != 15) && (nIndex != 18))
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("SFR 사각형[#%d] 좌측 인식 실패."), nIndex);
		theApp.MainDlg->putListLog(szLog);
		return false;
	}

	// 	vision.boxlist[CCD].addList(iSx, iSy, iCx, iEy, PS_SOLID, M_COLOR_BLUE);
	// 	vision.linelist[CCD].addList(iMinX, rcRoi.top, iMinX, rcRoi.bottom, PS_SOLID, M_COLOR_RED);

	for (x = iCx; x < iEx - 5; x++)
	{
		if (aiHistX[x + 1] > avgX && aiHistX[x + 2] > avgX && aiHistX[x + 3] > avgX && aiHistX[x + 4] > avgX)
		{
			iSum_Left = aiHistX[x - 4] + aiHistX[x - 3] + aiHistX[x - 2] + aiHistX[x - 1];
			iSum_Right = aiHistX[x + 4] + aiHistX[x + 3] + aiHistX[x + 2] + aiHistX[x + 1];

			iMax_Right = iSum_Right - iSum_Left;
			iMaxX = x;

			break;
		}
	}

	if ((x == iEx - 5) && (nIndex != 16) && (nIndex != 17))
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("SFR 사각형[#%d] 우측 인식 실패."), nIndex);
		theApp.MainDlg->putListLog(szLog);
		return false;
	}

	// 	vision.boxlist[CCD].addList(iCx, iSy, iEx, iEy, PS_SOLID, M_COLOR_GREEN);
	// 	vision.linelist[CCD].addList(iMaxX, rcRoi.top, iMaxX, rcRoi.bottom, PS_SOLID, M_COLOR_GREEN);


	if (nIndex == 15 || nIndex == 18)
	{
		if (iMax_Right > min_max_Gap)
			iMinX = iMaxX - model.sfrElem.m_iSizeX[nIndex];// g_clModelData[nUnit].m_clSfrInfo.m_nSizeX;
		else
			iMinX = clRect.left;
	}
	else if (iMax_Left < min_max_Gap)
	{
		//g_clVision.DrawMOverlayBox(nUnit, nUnit, clRect, M_COLOR_RED, 1, FALSE, PS_SOLID);

		_stprintf_s(szLog, SIZE_OF_1K, _T("[마크 #%d] 좌측 경계선이 불분명합니다. (%d)"), nIndex, iMax_Left);
		theApp.MainDlg->putListLog(szLog);

		//g_clVision.DrawMOverlayBox(nUnit, nUnit, iSx, iSy, iCx, iEy, M_COLOR_BLUE, 1, FALSE, PS_SOLID);
		//g_clVision.DrawMOverlayLine(nUnit, iMinX, clRect.top, iMinX, clRect.bottom, M_COLOR_RED, 1, FALSE, PS_SOLID);
		return false;
	}

	if (nIndex == 16 || nIndex == 17)
	{
		if (iMax_Left > min_max_Gap)
			iMaxX = iMinX + model.sfrElem.m_iSizeX[nIndex];// g_clModelData[nUnit].m_clSfrInfo.m_nSizeX;
		else
			iMaxX = clRect.right;
	}
	else if (iMax_Right < min_max_Gap)
	{
		//g_clVision.DrawMOverlayBox(nUnit, nUnit, clRect, M_COLOR_RED, 1, FALSE, PS_SOLID);

		_stprintf_s(szLog, SIZE_OF_1K, _T("[마크 #%d] 우측 경계선이 불분명합니다. (%d)"), nIndex, iMax_Right);
		theApp.MainDlg->putListLog(szLog);

		//g_clVision.DrawMOverlayBox(nUnit, nUnit, iCx, iSy, iEx, iEy, M_COLOR_BLUE, 1, FALSE, PS_SOLID);
		//g_clVision.DrawMOverlayLine(nUnit, iMaxX, clRect.top, iMaxX, clRect.bottom, M_COLOR_RED, 1, FALSE, PS_SOLID);

		return false;
	}


	if (iMinX<5)
	{
		if (nIndex == 15 || nIndex == 18)
			iMinX = 5;
	}

	if (iMinX>iMaxX || iMinX<1)
	{
		//g_clVision.DrawMOverlayBox(nUnit, nUnit, clRect, M_COLOR_RED, 1, FALSE, PS_SOLID);

		_stprintf_s(szLog, SIZE_OF_1K, _T("[마크 #%d] 좌우 경계선 인식 결과가 비정상 입니다. (좌:%d 우:%d)"), nIndex, iMinX, iMaxX);
		theApp.MainDlg->putListLog(szLog);

		return false;
	}
	///////////////////////////////////////////////////////////////////////하이데이타

	CRect HiRect;
	CPoint point;

	HiRect.left = iMaxX - 20;
	HiRect.right = iMaxX + 20;
	HiRect.top = (iMinY + iMaxY) / 2 - 20;
	HiRect.bottom = (iMinY + iMaxY) / 2 + 20;

	point.x = iMaxX;
	point.y = (iMinY + iMaxY) / 2;

	////////////////////////////////////////////////////////////////////////


	clRect.left = iMinX;
	clRect.right = iMaxX;
	clRect.top = iMinY;
	clRect.bottom = iMaxY;


	return true;
}


bool CTask::g_FindSfrRectPos(unsigned char* pImage, int nPitch, int nSizeX, int nSizeY, int nIndex, CRect clRectRoi, int mode)
{
	TCHAR szLog[SIZE_OF_1K];
	int nOffsetX = 0;
	int nOffsetY = 0;
	int nIndexLeft, nIndexRight, nIndexTop, nIndexBottom;
	int iWidth = 0;
	int iHeight = 0;
	int mSizeOffsetX = 0;
	int mSizeOffsetY = 0;
	int mTempIndex = 0;
	
	mSizeOffsetX = model.m_iSize_ROI_X;// / 2;
	mSizeOffsetY = model.m_iSize_ROI_Y;// / 2;
	
	COLORREF cAARoiColor = M_COLOR_GRAY;
	if (pImage == NULL)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("SFR  검사 영상 버퍼가 잘못되었습니다."));
		theApp.MainDlg->putListLog(szLog);

		return false;
	}

	if ((nSizeX <= 0) || (nSizeY <= 0))
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("SFR 검사 영상 사이즈가 잘못되었습니다. ( X : %d Y : %d )"), nSizeX, nSizeY);
		theApp.MainDlg->putListLog(szLog);

		return false;
	}
	bool mTargetCheck = false;
	static int mTargetAACount;
	static int nTempIndex;
	if (nIndex == 0)
	{
		nTempIndex = -1;
		mTargetAACount = 0;
	}

	if (mTargetAACount < 5)
	{
		if (model.sfrElem.m_AATiltRoiIndex[mTargetAACount] == nIndex)
		{
			mTargetCheck = true;
			mTargetAACount++;
		}
	}
	
	nIndexTop = -1;		//-1고정
	nIndexBottom = -1;
	nIndexLeft = -1;
	nIndexRight = -1;

	if (model.sfrElem.m_SfrTestUse[nIndex][0] == 1)
	{
		nTempIndex++;
		nIndexTop = nTempIndex;
	}
	if (model.sfrElem.m_SfrTestUse[nIndex][1] == 1)
	{
		nTempIndex++;
		nIndexBottom = nTempIndex;
	}
	if (model.sfrElem.m_SfrTestUse[nIndex][2] == 1)
	{
		nTempIndex++;
		nIndexLeft = nTempIndex;
	}
	if (model.sfrElem.m_SfrTestUse[nIndex][3] == 1)
	{
		nTempIndex++;
		nIndexRight = nTempIndex;
	}
	//////////////////////////////////////////////////////////////////////////////////////////
	

	if ((clRectRoi.right > nSizeX - 5) && (nIndex == 8 || nIndex == 9))
	{
		clRectRoi.right = nSizeX - 5;
	}

	if ((clRectRoi.left < 5) && (nIndex == 7 || nIndex == 10))
	{
		clRectRoi.left = 5;
	}

	if ((clRectRoi.left < 0) || (clRectRoi.top < 0) || (clRectRoi.right > nSizeX) || (clRectRoi.bottom > nSizeY))
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("SFR 마크 인식 위치가 비정상 입니다. ( L %d, T %d, R %d, B %d )"), clRectRoi.left, clRectRoi.top, clRectRoi.right, clRectRoi.bottom);
		theApp.MainDlg->putListLog(szLog);

		return false;
	}
	int RoiHalfWidth = (clRectRoi.right - clRectRoi.left) / 2;
	int RoiHalfHeight = (clRectRoi.bottom - clRectRoi.top) / 2;

	int nCx = (clRectRoi.left + clRectRoi.right) / 2;
	int nCy = (clRectRoi.top + clRectRoi.bottom) / 2;

	int nHist[1000];

	int nSx, nSy, nEx, nEy;
	int x, y, nPos, nSum, nMaxPos, nMaxVal, nTmpVal;
	int nPosTop, nPosBottom, nPosLeft, nPosRight;

	vision.crosslist[CCD].addList(nCx, nCy, RoiHalfWidth / 4, M_COLOR_MAGENTA);

	if (nIndexTop >= 0)
	{
		if (mTargetCheck)
		{
			mTempIndex = model.sfrElem.m_AATiltCalRoi[nIndex][0];
			if (mTempIndex == 1)
			{
				cAARoiColor = M_COLOR_CYAN;
			}
			else
			{
				cAARoiColor = M_COLOR_GRAY;
			}
		}
		if (model.m_MTF_Direction[nIndexTop] == SFR_ROI_VERTICAL)
		{
			iWidth = mSizeOffsetX;
			iHeight = mSizeOffsetY;
		}
		else
		{
			iWidth = mSizeOffsetY;
			iHeight = mSizeOffsetX;
		}

		nOffsetX =  model.m_MTF_ROI_Pos[nIndexTop].x;// RoiHalfWidth / 8;//센터라도 패턴 틀어진 각도때문에 정 센터로 안가서 offset 적용
		nOffsetY =  model.m_MTF_ROI_Pos[nIndexTop].y;// -RoiHalfHeight / 2;

		SFR._64_Sfr_Rect[nIndexTop].left = -1;
		SFR._64_Sfr_Rect[nIndexTop].right = -1;
		SFR._64_Sfr_Rect[nIndexTop].top = -1;
		SFR._64_Sfr_Rect[nIndexTop].bottom = -1;

		nSx = nCx - (iWidth / 2);
		nEx = nCx + (iWidth / 2);
		nSy = clRectRoi.top - (iHeight / 2);
		nEy = clRectRoi.top + (iHeight / 2);
#ifdef _DEBUG
		//g_clVision.DrawMOverlayBox(nUnit, nUnit, nSx, nSy, nEx, nEy, M_COLOR_DARK_GREEN, 1, 1, PS_SOLID);
#endif
		if (nSx < 0)				nSx = 0;
		if (nSy < 0)				nSy = 0;
		if (nEx >= nSizeX)			nEx = nSizeX - 1;
		if (nEy >= nSizeY)			nEy = nSizeY - 1;


		memset(nHist, 0, sizeof(int)*(1000));

		for (y = nSy; y < nEy; y++)
		{
			nSum = 0;
			nPos = y * nPitch + nSx;

			for (x = nSx; x < nEx; x++)
			{
				nSum += pImage[nPos];
				nPos++;
			}

			nHist[y - nSy] = nSum;
		}

		nMaxPos = -1;
		nMaxVal = 0;

		for (y = nSy + 5; y < nEy - 5; y++)
		{
			nTmpVal = (nHist[y - nSy] + nHist[y - nSy - 1] + nHist[y - nSy - 2] + nHist[y - nSy - 3]) - (nHist[y - nSy + 1] + nHist[y - nSy + 2] + nHist[y - nSy + 3] + nHist[y - nSy + 4]);

			if (nTmpVal > nMaxVal)
			{
				nMaxVal = nTmpVal;
				nMaxPos = y;
			}
		}

		nPosTop = nMaxPos;



		//vision.crosslist[CCD].addList(cx, cy, 10, M_COLOR_MAGENTA);
		//g_clVision.DrawMOverlayCross(nUnit, nUnit, nCx, nCy, 10, M_COLOR_MAGENTA, 1, FALSE, PS_SOLID);	//패턴 센터 십자가
		

		/*nSx = nCx - g_clModelData[nUnit].m_nRoiSizeY + nOffsetX;
		nEx = nCx + g_clModelData[nUnit].m_nRoiSizeY + nOffsetX; 
		nSy = nMaxPos - g_clModelData[nUnit].m_nRoiSizeX + nOffsetX;
		nEy = nMaxPos + g_clModelData[nUnit].m_nRoiSizeX + nOffsetX;
		*/
		nSx = nCx - (iWidth / 2) + nOffsetX;		//Top
		nEx = nCx + (iWidth / 2) + nOffsetX;
		nSy = nMaxPos - (iHeight / 2) + nOffsetY;//nOffsetY; 
		nEy = nMaxPos + (iHeight / 2) + nOffsetY;//nOffsetY;

		if (nSx < 5)			nSx = 5;
		if (nSy < 5)			nSy = 5;
		if (nEx > nSizeX - 5)	nEx = nSizeX - 5;
		if (nEy > nSizeY - 5)	nEy = nSizeY - 5;

		SFR._64_Sfr_Rect[nIndexTop].left = nSx;
		SFR._64_Sfr_Rect[nIndexTop].right = nEx;
		SFR._64_Sfr_Rect[nIndexTop].top = nSy;
		SFR._64_Sfr_Rect[nIndexTop].bottom = nEy;

		//g_clVision.DrawMOverlayCross(CAM_CCD, (nSx + nEx) / 2, nMaxPos, 30, M_COLOR_RED, 3, FALSE, PS_SOLID);
		//g_clVision.DrawMOverlayBox(nUnit, nUnit, nSx, nSy, nEx, nEy, M_COLOR_CYAN, 1, FALSE, PS_SOLID);
		_stprintf_s(szLog, SIZE_OF_100BYTE, _T("%d"), nIndexTop);
		//g_clVision.DrawMOverlayText(nUnit, nSx, nSy, szLog, M_COLOR_CYAN, _T("Arial"), 10, 0);

		vision.textlist[CCD].addList(SFR._64_Sfr_Rect[nIndexTop].left, SFR._64_Sfr_Rect[nIndexTop].top, szLog, M_COLOR_YELLOW, 17, 7, "Arial");
		vision.boxlist[CCD].addList(SFR._64_Sfr_Rect[nIndexTop].left, SFR._64_Sfr_Rect[nIndexTop].top, SFR._64_Sfr_Rect[nIndexTop].right, SFR._64_Sfr_Rect[nIndexTop].bottom, PS_SOLID, cAARoiColor);

		if (Task.AutoFlag == 0)
		{
			MIU.SaveSfrImage(pImage, nPitch, iWidth, iHeight, nIndexTop, SFR._64_Sfr_Rect[nIndexTop]);
		}


	}

	if (nIndexBottom >= 0)
	{
		if (mTargetCheck)
		{
			mTempIndex = model.sfrElem.m_AATiltCalRoi[nIndex][1];
			if (mTempIndex == 1)
			{
				cAARoiColor = M_COLOR_CYAN;
			}
			else
			{
				cAARoiColor = M_COLOR_GRAY;
			}
		}
		if (model.m_MTF_Direction[nIndexBottom] == SFR_ROI_VERTICAL)
		{
			iWidth = mSizeOffsetX;
			iHeight = mSizeOffsetY;
		}
		else
		{
			iWidth = mSizeOffsetY;
			iHeight = mSizeOffsetX;
		}

		nOffsetX =  model.m_MTF_ROI_Pos[nIndexBottom].x;// -RoiHalfWidth / 8;//센터라도 패턴 틀어진 각도때문에 정 센터로 안가서 offset 적용
		nOffsetY =  model.m_MTF_ROI_Pos[nIndexBottom].y;// -RoiHalfHeight / 8;

		SFR._64_Sfr_Rect[nIndexBottom].left = -1;
		SFR._64_Sfr_Rect[nIndexBottom].right = -1;
		SFR._64_Sfr_Rect[nIndexBottom].top = -1;
		SFR._64_Sfr_Rect[nIndexBottom].bottom = -1;

		nSx = nCx - (iWidth / 2);
		nEx = nCx + (iWidth / 2);
		nSy = clRectRoi.bottom - (iHeight / 2);
		nEy = clRectRoi.bottom + (iHeight / 2);
#ifdef _DEBUG
		//g_clVision.DrawMOverlayBox(nUnit, nUnit, nSx, nSy, nEx, nEy, M_COLOR_DARK_GREEN, 1, 1, PS_SOLID);
#endif
		
		if (nSx < 0)				nSx = 0;
		if (nSy < 0)				nSy = 0;
		if (nEx >= nSizeX)			nEx = nSizeX - 1;
		if (nEy >= nSizeY)			nEy = nSizeY - 1;

		memset(nHist, 0, sizeof(int)*(1000));

		for (y = nSy; y < nEy; y++)
		{
			nSum = 0;
			nPos = y * nPitch + nSx;

			for (x = nSx; x < nEx; x++)
			{
				nSum += pImage[nPos];
				nPos++;
			}
			nHist[y - nSy] = nSum;
		}

		nMaxPos = -1;
		nMaxVal = 0;

		for (y = nSy + 5; y < nEy - 5; y++)
		{
			nTmpVal = (nHist[y - nSy] + nHist[y - nSy + 1] + nHist[y - nSy + 2] + nHist[y - nSy + 3]) - (nHist[y - nSy - 1] + nHist[y - nSy - 2] + nHist[y - nSy - 3] + nHist[y - nSy - 4]);

			if (nTmpVal > nMaxVal)
			{
				nMaxVal = nTmpVal;
				nMaxPos = y;
			}
		}

		nPosBottom = nMaxPos;



		//vision.crosslist[CCD].addList(cx, cy, 10, M_COLOR_MAGENTA);
		//g_clVision.DrawMOverlayCross(nUnit, nUnit, nCx, nCy, 10, M_COLOR_MAGENTA, 1, FALSE, PS_SOLID);


		nSx = nCx - (iWidth / 2) + nOffsetX;
		nEx = nCx + (iWidth / 2) + nOffsetX;
		nSy = nMaxPos - (iHeight / 2) + nOffsetY;
		nEy = nMaxPos + (iHeight / 2) + nOffsetY;

		if (nSx < 5)				nSx = 5;
		if (nSy < 5)				nSy = 5;
		if (nEx > nSizeX - 5)		nEx = nSizeX - 5;
		if (nEy > nSizeY - 5)		nEy = nSizeY - 5;

		SFR._64_Sfr_Rect[nIndexBottom].left = nSx;
		SFR._64_Sfr_Rect[nIndexBottom].right = nEx;
		SFR._64_Sfr_Rect[nIndexBottom].top = nSy;
		SFR._64_Sfr_Rect[nIndexBottom].bottom = nEy;

		//g_clVision.DrawMOverlayCross(CAM_CCD, (nSx + nEx) / 2, nMaxPos, 30, M_COLOR_MAGENTA, 3, FALSE, PS_SOLID);
		//g_clVision.DrawMOverlayBox(nUnit, nUnit, nSx, nSy, nEx, nEy, M_COLOR_CYAN, 1, FALSE, PS_SOLID);
		_stprintf_s(szLog, SIZE_OF_100BYTE, _T("%d"), nIndexBottom);
		//g_clVision.DrawMOverlayText(nUnit, nSx, nSy, szLog, M_COLOR_CYAN, _T("Arial"), 10, 0);

		vision.textlist[CCD].addList(SFR._64_Sfr_Rect[nIndexBottom].left, SFR._64_Sfr_Rect[nIndexBottom].top, szLog, M_COLOR_YELLOW, 17, 7, "Arial");
		vision.boxlist[CCD].addList(SFR._64_Sfr_Rect[nIndexBottom].left, SFR._64_Sfr_Rect[nIndexBottom].top, SFR._64_Sfr_Rect[nIndexBottom].right, SFR._64_Sfr_Rect[nIndexBottom].bottom, PS_SOLID, cAARoiColor);

		if (Task.AutoFlag == 0)
		{
			MIU.SaveSfrImage(pImage, nPitch, iWidth, iHeight, nIndexBottom, SFR._64_Sfr_Rect[nIndexBottom]);
		}
	}

	if (nIndexLeft >= 0)
	{
		if (mTargetCheck)
		{
			mTempIndex = model.sfrElem.m_AATiltCalRoi[nIndex][2];
			if (mTempIndex == 1)
			{
				cAARoiColor = M_COLOR_CYAN;
			}
			else
			{
				cAARoiColor = M_COLOR_GRAY;
			}
		}
		if (model.m_MTF_Direction[nIndexLeft] == SFR_ROI_VERTICAL)
		{
			iWidth = mSizeOffsetX;
			iHeight = mSizeOffsetY;
		}
		else
		{
			iWidth = mSizeOffsetY;
			iHeight = mSizeOffsetX;
		}

		nOffsetX =  model.m_MTF_ROI_Pos[nIndexLeft].x;//센터라도 패턴 틀어진 각도때문에 정 센터로 안가서 offset 적용
		nOffsetY =  model.m_MTF_ROI_Pos[nIndexLeft].y;// -RoiHalfHeight / 8;

		SFR._64_Sfr_Rect[nIndexLeft].left = -1;
		SFR._64_Sfr_Rect[nIndexLeft].right = -1;
		SFR._64_Sfr_Rect[nIndexLeft].top = -1;
		SFR._64_Sfr_Rect[nIndexLeft].bottom = -1;

		nSx = clRectRoi.left - (iWidth / 2);
		nEx = clRectRoi.left + (iWidth / 2);
		nSy = nCy - (iHeight / 2);
		nEy = nCy + (iHeight / 2);
#ifdef _DEBUG
		//g_clVision.DrawMOverlayBox(nUnit, nUnit, nSx, nSy, nEx, nEy, M_COLOR_DARK_GREEN, 1, 1, PS_SOLID);
#endif
		
		if (nSx < 0)				nSx = 0;
		if (nSy < 0)				nSy = 0;
		if (nEx >= nSizeX)			nEx = nSizeX - 1;
		if (nEy >= nSizeY)			nEy = nSizeY - 1;

		memset(nHist, 0, sizeof(int)*(1000));

		for (x = nSx; x < nEx; x++)
		{
			nSum = 0;
			nPos = nSy * nPitch + x;

			for (y = nSy; y < nEy; y++)
			{
				nSum += pImage[nPos];
				nPos += nPitch;
			}

			nHist[x - nSx] = nSum;
		}

		nMaxPos = -1;
		nMaxVal = 0;

		for (x = nSx + 5; x < nEx - 5; x++)
		{
			nTmpVal = (nHist[x - nSx] + nHist[x - nSx - 1] + nHist[x - nSx - 2] + nHist[x - nSx - 3]) - (nHist[x - nSx + 1] + nHist[x - nSx + 2] + nHist[x - nSx + 3] + nHist[x - nSx + 4]);

			if (nTmpVal > nMaxVal)
			{
				nMaxVal = nTmpVal;
				nMaxPos = x;
			}
		}


		nPosLeft = nMaxPos;

		nSx = nMaxPos - (iWidth / 2) + nOffsetX;	//Left
		nEx = nMaxPos + (iWidth / 2) + nOffsetX;
		nSy = nCy - (iHeight / 2) + nOffsetY;
		nEy = nCy + (iHeight / 2) + nOffsetY;

		if (nSx < 5)				nSx = 5;
		if (nSy < 5)				nSy = 5;
		if (nEx > nSizeX - 5)		nEx = nSizeX - 5;
		if (nEy > nSizeY - 5)		nEy = nSizeY - 5;

		SFR._64_Sfr_Rect[nIndexLeft].left = nSx;
		SFR._64_Sfr_Rect[nIndexLeft].right = nEx;
		SFR._64_Sfr_Rect[nIndexLeft].top = nSy;
		SFR._64_Sfr_Rect[nIndexLeft].bottom = nEy;

		//g_clVision.DrawMOverlayCross(CAM_CCD, nMaxPos, (nSy + nEy) / 2, 30, M_COLOR_MAGENTA, 3, FALSE, PS_SOLID);

		//g_clVision.DrawMOverlayBox(nUnit, nUnit, nSx, nSy, nEx, nEy, M_COLOR_CYAN, 1, FALSE, PS_SOLID);
		_stprintf_s(szLog, SIZE_OF_100BYTE, _T("%d"), nIndexLeft);
		//g_clVision.DrawMOverlayText(nUnit, nSx, nSy, szLog, M_COLOR_CYAN, _T("Arial"), 10, 0);

		vision.textlist[CCD].addList(SFR._64_Sfr_Rect[nIndexLeft].left, SFR._64_Sfr_Rect[nIndexLeft].top, szLog, M_COLOR_YELLOW, 17, 7, "Arial");
		vision.boxlist[CCD].addList(SFR._64_Sfr_Rect[nIndexLeft].left, SFR._64_Sfr_Rect[nIndexLeft].top, SFR._64_Sfr_Rect[nIndexLeft].right, SFR._64_Sfr_Rect[nIndexLeft].bottom, PS_SOLID, cAARoiColor);

		if (Task.AutoFlag == 0)
		{
			MIU.SaveSfrImage(pImage, nPitch, iWidth, iHeight, nIndexLeft, SFR._64_Sfr_Rect[nIndexLeft]);
		}
	}


	if (nIndexRight >= 0)
	{
		if (mTargetCheck)
		{
			mTempIndex = model.sfrElem.m_AATiltCalRoi[nIndex][3];
			if (mTempIndex == 1)
			{
				cAARoiColor = M_COLOR_CYAN;
			}
			else
			{
				cAARoiColor = M_COLOR_GRAY;
			}
		}
		if (model.m_MTF_Direction[nIndexRight] == SFR_ROI_VERTICAL)
		{
			iWidth = mSizeOffsetX;
			iHeight = mSizeOffsetY;
		}
		else
		{
			iWidth = mSizeOffsetY;
			iHeight = mSizeOffsetX;
		}
		nOffsetX = model.m_MTF_ROI_Pos[nIndexRight].x;//센터라도 패턴 틀어진 각도때문에 정 센터로 안가서 offset 적용
		nOffsetY = model.m_MTF_ROI_Pos[nIndexRight].y;// RoiHalfHeight / 8;

		SFR._64_Sfr_Rect[nIndexRight].left = -1;
		SFR._64_Sfr_Rect[nIndexRight].right = -1;
		SFR._64_Sfr_Rect[nIndexRight].top = -1;
		SFR._64_Sfr_Rect[nIndexRight].bottom = -1;

		nSx = clRectRoi.right - (iWidth / 2);
		nEx = clRectRoi.right + (iWidth / 2);
		nSy = nCy - (iHeight / 2);
		nEy = nCy + (iHeight / 2);
#ifdef _DEBUG
		//g_clVision.DrawMOverlayBox(nUnit, nUnit, nSx, nSy, nEx, nEy, M_COLOR_DARK_GREEN, 1, 1, PS_SOLID);
#endif
		
		if (nSx < 0)				nSx = 0;
		if (nSy < 0)				nSy = 0;
		if (nEx >= nSizeX)			nEx = nSizeX - 1;
		if (nEy >= nSizeY)			nEy = nSizeY - 1;

		memset(nHist, 0, sizeof(int)*(1000));

		for (x = nSx; x < nEx; x++)
		{
			nSum = 0;
			nPos = nSy * nPitch + x;

			for (y = nSy; y < nEy; y++)
			{
				nSum += pImage[nPos];
				nPos += nPitch;
			}
			nHist[x - nSx] = nSum;
		}

		nMaxPos = -1;
		nMaxVal = 0;

		for (x = nSx + 5; x < nEx - 5; x++)
		{
			nTmpVal = (nHist[x - nSx] + nHist[x - nSx + 1] + nHist[x - nSx + 2] + nHist[x - nSx + 3]) - (nHist[x - nSx - 1] + nHist[x - nSx - 2] + nHist[x - nSx - 3] + nHist[x - nSx - 4]);

			if (nTmpVal > nMaxVal)
			{
				nMaxVal = nTmpVal;
				nMaxPos = x;
			}
		}

		nPosRight = nMaxPos;

		nSx = nMaxPos - (iWidth / 2) + nOffsetX;
		nEx = nMaxPos + (iWidth / 2) + nOffsetX;
		nSy = nCy - (iHeight / 2) + nOffsetY;
		nEy = nCy + (iHeight / 2) + nOffsetY;

		if (nSx < 5)				nSx = 5;
		if (nSy < 5)				nSy = 5;
		if (nEx > nSizeX - 5)		nEx = nSizeX - 5;
		if (nEy > nSizeY - 5)		nEy = nSizeY - 5;

		SFR._64_Sfr_Rect[nIndexRight].left = nSx;
		SFR._64_Sfr_Rect[nIndexRight].right = nEx;
		SFR._64_Sfr_Rect[nIndexRight].top = nSy;
		SFR._64_Sfr_Rect[nIndexRight].bottom = nEy;

		
		//g_clVision.DrawMOverlayCross(CAM_CCD, nMaxPos, (nSy + nEy) / 2, 30, M_COLOR_MAGENTA, 3, FALSE, PS_SOLID);
		//g_clVision.DrawMOverlayBox(nUnit, nUnit, nSx, nSy, nEx, nEy, M_COLOR_CYAN, 1, FALSE, PS_SOLID);
		_stprintf_s(szLog, SIZE_OF_100BYTE, _T("%d"), nIndexRight);
		//g_clVision.DrawMOverlayText(nUnit, nSx, nSy, szLog, M_COLOR_CYAN, _T("Arial"), 10, 0);

		vision.textlist[CCD].addList(SFR._64_Sfr_Rect[nIndexRight].left, SFR._64_Sfr_Rect[nIndexRight].top, szLog, M_COLOR_YELLOW, 17, 7, "Arial");
		vision.boxlist[CCD].addList(SFR._64_Sfr_Rect[nIndexRight].left, SFR._64_Sfr_Rect[nIndexRight].top, SFR._64_Sfr_Rect[nIndexRight].right, SFR._64_Sfr_Rect[nIndexRight].bottom, PS_SOLID, cAARoiColor);

		if (Task.AutoFlag == 0)
		{
			MIU.SaveSfrImage(pImage, nPitch, iWidth, iHeight, nIndexRight, SFR._64_Sfr_Rect[nIndexRight]);
		}
	}

	return true;
}

bool CTask::_findRectPosPattern(unsigned char* ucImage, int pitch, int sizeX, int sizeY, int index, CRect& rcRoi)
{
	CString sLog="";

	int offsetX = (int)((rcRoi.right-rcRoi.left) / 3);
	int offsetY = (rcRoi.bottom-rcRoi.top) / 2;

	if ( ucImage == NULL )
	{
		sLangChange.LoadStringA(IDS_STRING1303);	//영상 버퍼가 잘못되었습니다.
		sLog.Format(sLangChange);
		errMsg2(Task.AutoFlag,sLog);
		return false;
	}

	if ( sizeX <= 0 || sizeY <= 0)
	{
		sLangChange.LoadStringA(IDS_STRING1304);		//영상 사이즈가 잘못되었습니다. 
		sLog.Format(sLangChange + _T(" ( X : %d Y : %d )"), sizeX, sizeY);
		errMsg2(Task.AutoFlag, sLog);
		return false;
	}

	if ( rcRoi.left < 0 || rcRoi.top < 0 || rcRoi.right > sizeX || rcRoi.bottom > sizeY )
	{
		sLangChange.LoadStringA(IDS_STRING1304);	//ROI 검색 영역이 잘못 되었습니다.
		sLog.Format(sLangChange, rcRoi.left, rcRoi.top, rcRoi.right, rcRoi.bottom);
		errMsg2(Task.AutoFlag, sLog);
		return false;
	}
	sLog.Empty();

	double dCenterPosX = 0.0;
	double dCenterPosY = 0.0;
	double dAngle = 0.0;
	double dRate = 0.0;


	if(FieldPatternMatching(index,  dCenterPosX,  dCenterPosY,  dAngle,  dRate))
	{
		rcRoi.left		= dCenterPosX-model.m_FieldPattern_Size[index].x/2;
		rcRoi.right		= dCenterPosX+model.m_FieldPattern_Size[index].x/2;
		rcRoi.top		= dCenterPosY-model.m_FieldPattern_Size[index].y/2;
		rcRoi.bottom	= dCenterPosY+model.m_FieldPattern_Size[index].y/2;
	}
	return true;
}

// 정재호. 20140905 _findRectPos3 함수 전체 복사.
bool CTask::_findRectPos3(unsigned char* ucImage, int pitch, int sizeX, int sizeY, int index, CRect& rcRoi)			// 정재호 추가 함수.. (사각형 인식)
{


	// 20140905 먼저 보내준 영상과 Setting 후 보내 준 영상이 챠트가 서로 뒤집혀 있어서 mode 추가 했습니다..
	// 둘 중 하나 맞는 걸로 고정해서 쓰시면 됩니다.
	// 0 : LEFT_BLACK
	// 1 : RIGHT_BLACK

	int mode = RIGHT_BLACK;



	CString sLog;
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	if ( ucImage == NULL )
	{
		sLangChange.LoadStringA(IDS_STRING1303);	//영상 버퍼가 잘못되었습니다.
		sLog.Format(sLangChange);
		errMsg2(Task.AutoFlag,sLog);
		return false;
	}

	if ( sizeX <= 0 || sizeY <= 0)
	{
		sLangChange.LoadStringA(IDS_STRING1304);		//영상 사이즈가 잘못되었습니다. 
		sLog.Format(sLangChange + _T(" ( X : %d Y : %d )"), sizeX, sizeY);
		errMsg2(Task.AutoFlag, sLog);
		return false;
	}

	RECT	rectResult;

	rectResult = rcRoi;

	int cx = (rcRoi.left + rcRoi.right) / 2;
	int cy = (rcRoi.top + rcRoi.bottom) / 2;

	int roiWidth	= rcRoi.right - rcRoi.left;
	int roiHeight	= rcRoi.bottom - rcRoi.top;





	RECT	leftRect, rightRect, topRect, bottomRect;
	int		leftLine, leftVal, rightLine, rightVal, topLine, topVal, bottomLine, bottomVal;
	bool	searchFlagLeft, searchFlagRight, searchFlagTop, searchFlagBottom;


	////////////////// 좌측 ///////////////////////
	leftRect.left		= cx - roiWidth;
	leftRect.right		= cx;
	leftRect.top		= rcRoi.top;
	leftRect.bottom		= rcRoi.bottom;


	if(mode==LEFT_BLACK)
		searchFlagLeft = _searchEdgePos(ucImage, pitch, sizeX, sizeY, LEFT_DIR, leftRect, leftLine, leftVal);
	else
		searchFlagLeft = _searchEdgePos(ucImage, pitch, sizeX, sizeY, RIGHT_DIR, leftRect, leftLine, leftVal);

	if(searchFlagLeft)
		rectResult.left = leftLine;


	////////////////// 우측 ///////////////////////

	rightRect.left		= cx;
	rightRect.right		= cx + roiWidth;
	rightRect.top		= rcRoi.top;
	rightRect.bottom	= rcRoi.bottom;

//	searchFlagRight = _searchEdgePos(ucImage, pitch, sizeX, sizeY, RIGHT_DIR, rightRect, rightLine, rightVal);
	if(mode==LEFT_BLACK)
		searchFlagRight = _searchEdgePos(ucImage, pitch, sizeX, sizeY, LEFT_DIR, rightRect, rightLine, rightVal);		// RIGHT_DIR 에서 LEFT_DIR로 방향 바꿈. Box 우측 Line의 좌측 검색. 
	else
		searchFlagRight = _searchEdgePos(ucImage, pitch, sizeX, sizeY, RIGHT_DIR, rightRect, rightLine, rightVal);		// RIGHT_DIR 에서 LEFT_DIR로 방향 바꿈. Box 우측 Line의 좌측 검색. 

	if(searchFlagRight)
		rectResult.right = rightLine;


	////////////////// 상부 ///////////////////////

	topRect.left		= rectResult.left;
	topRect.right		= rectResult.right;
	topRect.top			= cy - roiHeight;
	topRect.bottom		= cy - roiHeight / 5;

	searchFlagTop = _searchEdgePos(ucImage, pitch, sizeX, sizeY, TOP_DIR, topRect, topLine, topVal);

	if(searchFlagTop)
		rectResult.top = topLine;


	////////////////// 하부 ///////////////////////
	bottomRect.left		= rectResult.left;
	bottomRect.right	= rectResult.right;
	bottomRect.top		= cy + roiHeight / 5;
	bottomRect.bottom	= cy + roiHeight;

	searchFlagBottom = _searchEdgePos(ucImage, pitch, sizeX, sizeY, BOTTOM_DIR, bottomRect, bottomLine, bottomVal);

	if(searchFlagBottom)
		rectResult.bottom = bottomLine;


	if(searchFlagBottom && searchFlagBottom && searchFlagBottom && searchFlagBottom)
	{
		rcRoi = rectResult;
		return true;
	}

	return false;
}


// 정재호. 20140905 _searchEdgePos 함수 전체 복사.
bool CTask::_searchEdgePos(unsigned char* ucImage, int pitch, int sizeX, int sizeY, int dir, CRect rcRoi, int &linePos, int &edgeVal)			// 정재호 추가 함수.. (사각형의 라인 인식)
{
	if(rcRoi.left <= 0)
		rcRoi.left = 5;

	if(rcRoi.top <= 0)
		rcRoi.top = 5;

	if(rcRoi.right >= sizeX)
		rcRoi.right = sizeX - 5;

	if(rcRoi.bottom >= sizeY)
		rcRoi.bottom = sizeY - 5;



//	vision.boxlist[CCD].addList(rcRoi, PS_SOLID, M_COLOR_RED);

	edgeVal = -1;

	CString sLog;

	if ( ucImage == NULL )
	{
		
		sLangChange.LoadStringA(IDS_STRING1303);	//영상 버퍼가 잘못되었습니다.
		sLog.Format(sLangChange);
		errMsg2(Task.AutoFlag,sLog);
		return false;
	}

	if ( sizeX <= 0 || sizeY <= 0)
	{
		sLangChange.LoadStringA(IDS_STRING1304);		//영상 사이즈가 잘못되었습니다. 
		sLog.Format(sLangChange + _T(" ( X : %d Y : %d )"), sizeX, sizeY);
		errMsg2(Task.AutoFlag, sLog);
		return false;
	}

	if( (rcRoi.right-rcRoi.left > 1000) || (rcRoi.bottom-rcRoi.top > 1000) )
	{
		sLangChange.LoadStringA(IDS_STRING1212);	//마크 검색 영역 크기가 비정상 입니다.
		sLog.Format(sLangChange + _T(" (%d, %d) (>1000) )"), rcRoi.right-rcRoi.left, rcRoi.bottom-rcRoi.top);
		errMsg2(Task.AutoFlag, sLog);
		return false;
	}

	int anEdgeVal[1000];
	int x, y, pos, tmpVal, sumVal;
	int maxPos=-1, maxVal;

	if(dir == LEFT_DIR || dir == RIGHT_DIR)
	{
		for(x=rcRoi.left; x<rcRoi.right; x++)
		{
			sumVal = 0;
			pos = rcRoi.top * pitch + x;

			for(y=rcRoi.top; y<rcRoi.bottom; y++)
			{
				if(dir == LEFT_DIR)
					tmpVal = ucImage[pos-1] - ucImage[pos];
				else
					tmpVal = ucImage[pos+1] - ucImage[pos];
				
				if(tmpVal<0)		tmpVal = 0;

				sumVal += tmpVal;
				pos += pitch;
			}

			anEdgeVal[x-rcRoi.left] = sumVal;
		}

		maxVal = 0;

		for(x=rcRoi.left; x<rcRoi.right; x++)
		{
			if(anEdgeVal[x-rcRoi.left] > maxVal)
			{
				maxVal = anEdgeVal[x-rcRoi.left];
				maxPos = x;
			}
		}
	}
	else
	{
		for(y=rcRoi.top; y<rcRoi.bottom; y++)
		{
			sumVal = 0;
			pos = y * pitch + rcRoi.left;

			for(x=rcRoi.left; x<rcRoi.right; x++)
			{
				if(dir == TOP_DIR)
					tmpVal = ucImage[pos-pitch] - ucImage[pos];
				else
					tmpVal = ucImage[pos+pitch] - ucImage[pos];

				if(tmpVal<0)		tmpVal = 0;

				sumVal += tmpVal;
				pos++;
			}

			anEdgeVal[y-rcRoi.top] = sumVal;
		}

		maxVal = 0;

		for(y=rcRoi.top; y<rcRoi.bottom; y++)
		{
			if(anEdgeVal[y-rcRoi.top] > maxVal)
			{
				maxVal = anEdgeVal[y-rcRoi.top];
				maxPos = y;
			}
		}
	}

	if(maxPos == -1)
		return false;

	linePos = maxPos;
	edgeVal = maxVal;

	return true;
}

bool CTask::_findSfrRectPos(unsigned char* ucImage, int pitch, int sizeX, int sizeY, int index, CRect rcRoi, int iCircleCenter_X,int iCircleCenter_Y)
{ 
	char szTmp[256];
	int i = 0;
	int iSfrIndex = 0;
	int iWidth=0;
	int iHeight=0;
	int initNum=0;

	int		mRoiTempDic[COMMON_MTF_INSP_CNT] = { 0, };
	int		mAATempNum[COMMON_MTF_INSP_CNT] = { 0, };
	//initNum = 0,0,0,0		4,4,6,6,8,8,10,10
	//
	//5,7,9,11,13,15,17,19
	//0 , < 5
	//5 , < 7
	static int nPatternIndex;
	if (index == 0)
	{
		nPatternIndex = 0;
	}
	int oldIndex = nPatternIndex;
	for (i = 0; i < 4; i++)
	{
		//model.sfrElem.m_AATiltCalRoi[nIndex][0];
		if (model.sfrElem.m_AATiltRoiIndex[0] == index || model.sfrElem.m_AATiltRoiIndex[1] == index ||
			model.sfrElem.m_AATiltRoiIndex[2] == index || model.sfrElem.m_AATiltRoiIndex[3] == index || model.sfrElem.m_AATiltRoiIndex[4] == index)
		{
			if (model.sfrElem.m_AATiltCalRoi[index][i] == 1)	////0 = T , B, L , R
			{
				mAATempNum[nPatternIndex] = 1;
			}
		}
		if (model.sfrElem.m_SfrTestUse[index][i] == 1)	////0 = T , B, L , R
		{
			
			mRoiTempDic[nPatternIndex] = i;
			nPatternIndex++;
		}
		

		
	}
	COLORREF cAARoiColor = M_COLOR_GRAY; 

	int nTop = 0;
	int nLeft = 0;
	int mTempIndex = 0;
	//for(iSfrIndex = initNum; iSfrIndex <= boxIndex[index]; iSfrIndex++)  
	for (iSfrIndex = oldIndex; iSfrIndex < nPatternIndex; iSfrIndex++)
	{
		if (model.m_MTF_Direction[iSfrIndex] == SFR_ROI_VERTICAL)//SFR_ROI_VERTICAL)
		{
			iHeight = model.m_iSize_ROI_Y;
			iWidth = model.m_iSize_ROI_X;
		}
		else
		{
			iHeight = model.m_iSize_ROI_X;
			iWidth = model.m_iSize_ROI_Y;
		}

		if (mAATempNum[iSfrIndex] == 1)
		{
			cAARoiColor = M_COLOR_CYAN;
		}
		else
		{
			cAARoiColor = M_COLOR_GRAY;
		}
		//iSfrIndex = 0 ~ 11

		//nTop = (rcRoi.top + rcRoi.Height() / 2 - (iHeight / 2));
		//nLeft = (rcRoi.left + rcRoi.Width() / 2 - (iWidth / 2));

		if (mRoiTempDic[iSfrIndex] == 0)
		{ 
			//Top
			nTop = (rcRoi.top - (iHeight / 2));
			nLeft = (rcRoi.left + rcRoi.Width() / 2 - (iWidth / 2));
		}
		else if (mRoiTempDic[iSfrIndex] == 1)
		{
			//Bottom
			nTop = (rcRoi.bottom - (iHeight / 2));
			nLeft = (rcRoi.left + rcRoi.Width() / 2 - (iWidth / 2));
		}
		else if (mRoiTempDic[iSfrIndex] == 2)
		{
			//Left
			nTop = (rcRoi.top + rcRoi.Height() / 2 - (iHeight / 2));
			nLeft = (rcRoi.left - (iWidth / 2));
		}
		else
		{
			//Right
			nTop = (rcRoi.top + rcRoi.Height() / 2 - (iHeight / 2));
			nLeft = (rcRoi.right - (iWidth / 2));
		}


		SFR._64_Sfr_Rect[iSfrIndex].left = nLeft + model.m_MTF_ROI_Pos[iSfrIndex].x;
		SFR._64_Sfr_Rect[iSfrIndex].top = nTop + model.m_MTF_ROI_Pos[iSfrIndex].y;

		SFR._64_Sfr_Rect[iSfrIndex].right = SFR._64_Sfr_Rect[iSfrIndex].left + iWidth;
		SFR._64_Sfr_Rect[iSfrIndex].bottom = SFR._64_Sfr_Rect[iSfrIndex].top + iHeight;

		sprintf_s(szTmp, "%d", iSfrIndex);
		vision.textlist[CCD].addList(SFR._64_Sfr_Rect[iSfrIndex].left, SFR._64_Sfr_Rect[iSfrIndex].top, szTmp, M_COLOR_DARK_GREEN, 20, 10, "Arial");

		

		vision.boxlist[CCD].addList(SFR._64_Sfr_Rect[iSfrIndex].left, SFR._64_Sfr_Rect[iSfrIndex].top, SFR._64_Sfr_Rect[iSfrIndex].right, SFR._64_Sfr_Rect[iSfrIndex].bottom, PS_SOLID, cAARoiColor);
		if (Task.AutoFlag == 0)
		{
			MIU.SaveSfrImage(ucImage, pitch, iWidth, iHeight, iSfrIndex, SFR._64_Sfr_Rect[iSfrIndex]); 
		}
	}
	return true;
}



//! 원형 Mark를 찾아낸 결과를 바탕으로 하여 SFR의 사각 영역을 정한다. 
bool CTask::getROI_SFR(int mode)
{
	int i_roi_size_x = model.m_iSize_ROI_X;
	int i_roi_size_y = model.m_iSize_ROI_Y;

	CString sLog="";

	int pitch	= MbufInquire(vision.MilProcImageChild[4], M_PITCH, NULL);
	int width	= MbufInquire(vision.MilProcImageChild[4], M_SIZE_X, NULL);
	int Height	= MbufInquire(vision.MilProcImageChild[4], M_SIZE_Y, NULL);

	vision.drawOverlay(CCD);
	//! 원형 Mark를 찾는다.
	vision.clearOverlay(CCD);
	bool bRtn = false;




	bRtn = _findCirclePos(vision.MilImageBuffer[4], pitch, width, Height, SFR.rcROI);
	//bRtn = _OpencvFindCirclePos(MIU.m_pFrameRawBuffer, SFR.rcROI, true);

	
	//
	double shiftLimit = 2.0; 
	if (!bRtn )
	{
		if(Task.PCBTask != 115500 && ChartCenterPatternMatching() &&mode!=MTF_INSP)	// 중앙의 사각박스2개 이미지를 패턴 매칭 
		{ 
			Task.m_dShift_IMG_X = theApp.MainDlg->ChartCenterOffsetX*(model.m_dSize_CCD_Cell / 1000.0f)*1.0f;
			Task.m_dShift_IMG_Y = theApp.MainDlg->ChartCenterOffsetY*(model.m_dSize_CCD_Cell / 1000.0f)*1.0f;
			if( fabs(Task.m_dShift_IMG_X) < shiftLimit &&fabs(Task.m_dShift_IMG_Y) < shiftLimit )
			{
				theApp.MainDlg->_MotorMove_IMG_Align();
			}
			Sleep(1500);

			vision.clearOverlay(CCD);	
			vision.MilBufferUpdate();	
			Task.getROI();
			Sleep(100);
			bRtn = _findCirclePos(vision.MilImageBuffer[4], pitch, width, Height, SFR.rcROI);
			//bRtn = _OpencvFindCirclePos(MIU.m_pFrameRawBuffer, SFR.rcROI, true);
			if ( !bRtn )
			{
				return false;
			}
		}
		else
		{
			return false;
		}
		
	}

	double dRadian_X, dRadian_Y, dModelRadian_X, dModelRadian_Y;
	double dDeg_X, dDeg_Y, dModelDeg_X, dModelDeg_Y;

	int iHeight_X	= ((m_CircleP[0].y-m_CircleP[1].y) + (m_CircleP[2].y-m_CircleP[3].y)) / 2;
	int iWidth_X	= ((m_CircleP[1].x-m_CircleP[0].x) + (m_CircleP[3].x-m_CircleP[2].x)) / 2;
	int iHeight_Y	= ((m_CircleP[2].x-m_CircleP[0].x) + (m_CircleP[3].x-m_CircleP[1].x)) / 2;
	int iWidth_Y	= ((m_CircleP[2].y-m_CircleP[0].y) + (m_CircleP[3].y-m_CircleP[1].y)) / 2;

	if ( iWidth_X == 0 )
	{
		dRadian_X = 0.;
	}
	else
	{
		dRadian_X = atan((double)(iHeight_X)/(double)(iWidth_X));
	}
	if ( iWidth_Y == 0 )
	{
		dRadian_Y = 0.;
	}
	else
	{
		dRadian_Y = atan((double)(iHeight_Y)/(double)(iWidth_Y));
	}

	dDeg_X = dRadian_X * 180.0 / M_PI;
	dDeg_Y = dRadian_Y * 180.0 / M_PI;

	int iModelHeight_X	= ((model.sfrElem.m_CircleP[0].y-model.sfrElem.m_CircleP[1].y) + (model.sfrElem.m_CircleP[2].y-model.sfrElem.m_CircleP[3].y)) / 2;
	int iModelWidth_X	= ((model.sfrElem.m_CircleP[1].x-model.sfrElem.m_CircleP[0].x) + (model.sfrElem.m_CircleP[3].x-model.sfrElem.m_CircleP[2].x)) / 2;
	int iModelHeight_Y	= ((model.sfrElem.m_CircleP[2].x-model.sfrElem.m_CircleP[0].x) + (model.sfrElem.m_CircleP[3].x-model.sfrElem.m_CircleP[1].x)) / 2;
	int iModelWidth_Y	= ((model.sfrElem.m_CircleP[2].y-model.sfrElem.m_CircleP[0].y) + (model.sfrElem.m_CircleP[3].y-model.sfrElem.m_CircleP[1].y)) / 2;

	if ( iModelWidth_X == 0 )	dModelRadian_X = 0.;
	else						dModelRadian_X = atan((double)(iModelHeight_X)/(double)(iWidth_X));
	
	if ( iModelWidth_Y == 0 )	dModelRadian_Y = 0.;
	else						dModelRadian_Y = atan((double)(iModelHeight_Y)/(double)(iModelWidth_Y));

	dModelDeg_X = dModelRadian_X * 180.0 / M_PI;
	dModelDeg_Y = dModelRadian_Y * 180.0 / M_PI;


	double dRad_Avr = (dRadian_X + dRadian_Y - (dModelRadian_X+dModelRadian_Y)) / 2.0;

	int iCenterX = (model.sfrElem.m_CircleP[0].x+model.sfrElem.m_CircleP[1].x+model.sfrElem.m_CircleP[2].x+model.sfrElem.m_CircleP[3].x)/4;		// 4개의 원마크의 가로축 중심 
	int iCenterY = (model.sfrElem.m_CircleP[0].y+model.sfrElem.m_CircleP[1].y+model.sfrElem.m_CircleP[2].y+model.sfrElem.m_CircleP[3].y)/4;		// 4개의 원마크의 세로축 중심


	int iShift_X	= iCenterX - (m_CircleP[0].x+m_CircleP[1].x+m_CircleP[2].x+m_CircleP[3].x) / 4;
	int iShift_Y	= iCenterY - (m_CircleP[0].y+m_CircleP[1].y+m_CircleP[2].y+m_CircleP[3].y) / 4;


	double dExpand_X = 0.;

	int iExpand_X_Upper = ((m_CircleP[1].x - m_CircleP[0].x) + (m_CircleP[3].x - m_CircleP[2].x)) / 2;
	int iExpand_X_Lower = ((model.sfrElem.m_CircleP[1].x - model.sfrElem.m_CircleP[0].x) + (model.sfrElem.m_CircleP[3].x - model.sfrElem.m_CircleP[2].x)) / 2;

	if ( iExpand_X_Lower == 0 )
		dExpand_X = 0.;
	else
		dExpand_X = (double)(iExpand_X_Upper) / (double)(iExpand_X_Lower);

	double dExpand_Y = 0.;

	int iExpand_Y_Upper = ((m_CircleP[2].y - m_CircleP[0].y) + (m_CircleP[3].y - m_CircleP[1].y)) / 2;
	int iExpand_Y_Lower = ((model.sfrElem.m_CircleP[2].y - model.sfrElem.m_CircleP[0].y) + (model.sfrElem.m_CircleP[3].y - model.sfrElem.m_CircleP[1].y)) / 2;

	if ( iExpand_Y_Lower == 0 )
		dExpand_Y = 0.;
	else
		dExpand_Y = (double)(iExpand_Y_Upper) / (double)(iExpand_Y_Lower);

	int iSx, iSy, iEx, iEy;
	int iUpper_X =0,			iUpper_y =0;
	int iLower_X =0,			iLower_y =0;
	int iMax_Threshold = -1,	iMax_Threshold2 = -1;


	double dCosVal = cos(dRad_Avr);
	double dSinVal = sin(dRad_Avr);

	bool rtn = true;
	char	szDispData[256];
	for (int i = 0 ; i < 4 ; i++)
	{
		sprintf_s(szDispData, "%d", i);
		vision.textlist[CCD].addList(model.sfrElem.m_CircleRoi[i].left+ 10, model.sfrElem.m_CircleRoi[i].top + 10, szDispData, M_COLOR_YELLOW, 17, 7, "Arial");
		vision.boxlist[CCD].addList(model.sfrElem.m_CircleRoi[i], PS_DOT, M_COLOR_GREEN);
	}

	for (int i = 0; i<model.mGlobalChartCount; i++)//for (int i=0 ; i<LAST_MARK_CNT; i++)
	{
		iSx = (int)(iCenterX - (iCenterX-model.sfrElem.m_iOffsetX[i]) * dExpand_X - iShift_X + 0.5);
		iSy = (int)(iCenterY - (iCenterY-model.sfrElem.m_iOffsetY[i]) * dExpand_Y - iShift_Y + 0.5);

		double	dCen_X = (m_CircleP[0].x + m_CircleP[1].x + m_CircleP[2].x + m_CircleP[3].x) / 4;	
		double	dCen_Y = (m_CircleP[0].y + m_CircleP[1].y + m_CircleP[2].y + m_CircleP[3].y) / 4;

		double	dCenter_X = (m_CirclePos_x[0] + m_CirclePos_x[1] + m_CirclePos_x[2] + m_CirclePos_x[3]) / 4;	
		double	dCenter_Y = (m_CirclePos_y[0] + m_CirclePos_y[1] + m_CirclePos_y[2] + m_CirclePos_y[3]) / 4;
		double	dTemp_X = iSx - dCen_X;
		double	dTemp_Y = dCen_Y - iSy;

		double	dRot_X = (dCosVal * dTemp_X) - (dSinVal * dTemp_Y);
		double	dRot_Y = (dSinVal * dTemp_X) + (dCosVal * dTemp_Y);

		double	dReal_X = dRot_X + dCen_X;
		double	dReal_Y = dCen_Y - dRot_Y;
		double dCenterX = width / 2;
		double dCenterY = Height / 2;
		int nShiftX = dCenterX - (m_CircleP[0].x + m_CircleP[1].x + m_CircleP[2].x + m_CircleP[3].x) / 4;
		int nShiftY = dCenterY - (m_CircleP[0].y + m_CircleP[1].y + m_CircleP[2].y + m_CircleP[3].y) / 4;
		iSy = model.sfrElem.m_iOffsetY[i] + nShiftY*-1; //nShiftX;
		iSx = model.sfrElem.m_iOffsetX[i] + nShiftX*-1; //nShiftY;
		iEx = (int)(iSx + model.sfrElem.m_iSizeX[i] + 0.5);
		iEy = (int)(iSy + model.sfrElem.m_iSizeY[i] + 0.5);

		if (iSx < 0)	iSx = 0;
		if (iSy < 0)	iSy = 0;
		if (iEx > width)	iEx = width - 1;
		if (iEy > Height)	iEy = Height - 1;

		SFR.rect[i].left = iSx;
		SFR.rect[i].top = iSy;
		SFR.rect[i].right = iEx;
		SFR.rect[i].bottom = iEy;

		if (model.mGlobalChartFind == 0)
		{
			//패턴 찾기
			rtn = _findRectPosPattern(vision.MilImageBuffer[4], pitch, width, Height, i, SFR.rect[i]);
			if (rtn)
			{
				vision.boxlist[CCD].addList(SFR.rect[i], PS_SOLID, M_COLOR_MAGENTA);
			}
			else
			{
				vision.boxlist[CCD].addList(SFR.rect[i], PS_DOT, M_COLOR_RED);
				continue;
			}
			rtn = _findSfrRectPos(vision.MilImageBuffer[4], pitch, width, Height, i, SFR.rect[i], iCenterX, iCenterY);
		}
		else
		{
			//자동 찾기
			rtn = g_FindRectPos(vision.MilImageBuffer[4], pitch, width, Height, i, SFR.rect[i]);
			if (rtn)
			{
				vision.boxlist[CCD].addList(SFR.rect[i], PS_SOLID, M_COLOR_MAGENTA);
			}
			else
			{
				vision.boxlist[CCD].addList(SFR.rect[i], PS_DOT, M_COLOR_RED);
				continue;
			}
			rtn = g_FindSfrRectPos(vision.MilImageBuffer[4], pitch, width, Height, i, SFR.rect[i], mode);
		}
		if(!rtn)
		{
			vision.boxlist[CCD].addList(SFR.rect[i], PS_DOT, M_COLOR_RED);
			continue;
		}
	}

#if (____AA_WAY == PCB_TILT_AA)
	sLog.Format("PCB Z:%f",motor.GetCommandPos(theApp.MainDlg->TITLE_MOTOR_Z));
#elif (____AA_WAY == LENS_TILT_AA)
	sLog.Format("LENS Z:%f",motor.GetCommandPos(theApp.MainDlg->TITLE_MOTOR_Z));
#endif
	theApp.MainDlg->putListLog(sLog);

	sLog.Format("Ccd Cell Size:%lf",model.m_dSize_CCD_Cell);
	theApp.MainDlg->putListLog(sLog);
	sLog.Empty();

	return true;
}


void CTask::getImageAlignment()
{
	SFR.fImageAlign[m_iCnt_Step_AA_Total][0]	= (float)getImageDisplayFOV();
	SFR.fImageAlign[m_iCnt_Step_AA_Total][1]	= (float)getImageTiltX();
	SFR.fImageAlign[m_iCnt_Step_AA_Total][2]	= (float)getImageTiltY();
	SFR.fImageAlign[m_iCnt_Step_AA_Total][3]	= (float)getImageRotation();
}


double CTask::getImageTiltX()
{

	mCDPoint p[4];
	for (int i=0 ; i<4 ; i++)
	{
		p[i].x	= m_CircleP[i].x;
		p[i].y	= m_CircleP[i].y;
	}

	double dAvr_Left	= (m_CircleP[0].x+m_CircleP[2].x) / 2;
	double dAvr_Right	= (m_CircleP[1].x+m_CircleP[3].x) / 2;

	double dCen_Image	= (m_CircleP[0].x + m_CircleP[1].x + m_CircleP[2].x + m_CircleP[3].x)/4;
	double dCen_Ori		= gMIUDevice.nWidth/2;

	double dWidth_Circle_X =	387.7;//240.0;		// 마크 거리
	double dGap_LensToChart = 246.7; //410.0;	//제품 부터 Chart 까지의 높이

	double dWidth_X = fabs(dAvr_Left-dAvr_Right);
	double dResolX = dWidth_Circle_X/dWidth_X;
	double dHeight		= (dCen_Ori - dCen_Image) * dResolX;
	double dRad_TiltX	= atan(dHeight/dGap_LensToChart);
	double dAng_TiltX	= dRad_TiltX * 180.0 / M_PI;

	return dAng_TiltX;
}

double CTask::getImageTiltY()
{
	mCDPoint p[4];
	for (int i=0 ; i<4 ; i++)
	{
		p[i].x	= m_CircleP[i].x;
		p[i].y	= m_CircleP[i].y;
	}

	// 	double dAvr_Top		= (p[1].y+p[2].y)/2;
	// 	double dAvr_Bottom	= (p[3].y+p[4].y)/2;

	double dAvr_Top		= (m_CircleP[0].y+m_CircleP[1].y) / 2;
	double dAvr_Bottom	= (m_CircleP[2].y+m_CircleP[3].y) / 2;

	//	double dCen_Image	= p[0].y;
	double dCen_Image	= (m_CircleP[0].y + m_CircleP[1].y + m_CircleP[2].y + m_CircleP[3].y)/4;
	double dCen_Ori		= gMIUDevice.nHeight/2;

	double dWidth_Circle_Y = 290.8;//200.0;
	double dGap_LensToChart = 246.7;//410.0;

	double dWidth_Y = fabs(dAvr_Top-dAvr_Bottom);
	double dResolY = dWidth_Circle_Y/dWidth_Y;
	double dHeight		= (dCen_Ori - dCen_Image) * dResolY;
	double dRad_TiltY	= atan(dHeight/dGap_LensToChart);
	double dAng_TiltY	= dRad_TiltY * 180.0 / M_PI;

	return dAng_TiltY;
}

double CTask::getImageRotation()
{
	mCDPoint p[5];
	for (int i=0 ; i<5 ; i++)
	{
		p[i].x	= SFR._64_Sfr_Rect[m_iCnt_Step_AA_Total][i].left;
		p[i].y	= SFR._64_Sfr_Rect[m_iCnt_Step_AA_Total][i].top;
	}

	double dRadian;
	double dAngle_Top;
	double dAngle_Bottom;
	double dPitch;
	double dHeight;

	dPitch	= fabs(p[1].x-p[2].x);
	dHeight	= p[1].y-p[2].y;
	dRadian = atan(dHeight/dPitch);

	dAngle_Top = dRadian * 180.0 / M_PI;

	dPitch	= fabs(p[3].x-p[4].x);
	dHeight = p[3].y-p[4].y;
	dRadian = atan(dHeight/dPitch);

	dAngle_Bottom = dRadian * 180.0 / M_PI;


	return (dAngle_Top+dAngle_Bottom)/2;
}

double CTask::getImageDisplayFOV()
{
	mCDPoint p[5];
	for (int i=0 ; i<5 ; i++)
	{
		p[i].x	= m_CircleP[i].x;
		p[i].y	= m_CircleP[i].y;
	}

	double dRadian;
	double dAngle_DFOV;

	double dWidth_X = fabs(p[0].x-p[3].x);
	double dWidth_Y = fabs(p[0].y-p[3].y);
	double dResolX = 153/dWidth_X;
	double dResolY = 278/dWidth_Y;
	double dWidth = sqrt(pow(gMIUDevice.nWidth * dResolX,2) + pow(gMIUDevice.nHeight * dResolY,2)) ;

	dRadian = atan((dWidth/2)/470.0);

	dAngle_DFOV = (dRadian * 180.0 / M_PI) * 2;

	return dAngle_DFOV;
}

double CMandoInspLog::getMaxMin(int pos , int type)
{
	int i , end;
	double temp;
	switch(pos)
	{
	case 0://0필드
		i = 0;
		end = 4;
		break;
	case 1://0.3필드
		i = 4;
		end = 12;
		break;
	case 2://0.6필드
		i = 12;
		end = 20;
		break;
	case 3://0.8필드
		i = 20;
		end = 28;
		break;
	}
	temp = dMTF_PostUV[i];
	for(i; i<end; i++)
	{
		if(type==0)//Max Return
		{
			if(dMTF_PostUV[i] > temp)
			{
				temp = dMTF_PostUV[i];
			}
		}else//Min Return
		{
			if(dMTF_PostUV[i] < temp)
			{
				temp = dMTF_PostUV[i];
			}
		}
	}
	return temp;
}

CNgList_Data::CNgList_Data()
{
	m_NgCount = 0;
	m_NgIndex = 0;
}

void CNgList_Data::Save()
{
	//FILE *out;

	//CFileFind finder;
	//BOOL IsFind;
	//CString FolderName;

	//SYSTEMTIME SysTime;
	//::GetLocalTime(&SysTime);



	//FolderName.Format("%s", DATA_DIR);

	//IsFind = finder.FindFile(FolderName);
	//if(!IsFind)
	//{
	//	FolderName.Format("%s", BASE_DIR);
	//	CreateDirectory(FolderName,NULL); 

	//	FolderName.Format("%s", DATA_DIR);
	//	CreateDirectory(FolderName,NULL); 
	//}	

	//finder.Close();

	//char	fileName[1000];

	//wsprintf(fileName, "%s\\NgList.txt", FolderName);

	//
	//if(fopen_s(&out, fileName,"w"))
	//{
	//	sLangChange.LoadStringA(IDS_STRING849);	//"NGList 저장 실패..."
	//	errMsg2(Task.AutoFlag, sLangChange);
	//}
	//else
	//{
	//	if (m_NgCount > MAX_NG_LIST)
	//		m_NgCount = MAX_NG_LIST;

	//	for (int i=0; i<m_NgCount; i++)
	//	{
	//		fprintf_s(out, "%s",		sz_NgList[i]);
	//	}
	//			
	//	
	//	if(out)	fclose(out);
	//}
}

void CNgList_Data::Load()
{
	/*FILE* in;

	char	Line[500];
	char	Title[500];	
	int		nRtn, index=0;
	char	fileName[1000];
	
	wsprintf(fileName, "%s\\NgList.txt", DATA_DIR);

	if(!fopen_s(&in, fileName,"r"))
	{
		while (1)
		{
			fgets(Line, 499, in);
			nRtn = sscanf_s(Line, "%s", &Title, 499);

			if (nRtn==EOF)	
				break;

			Line[255] = 0;
			sprintf_s(sz_NgList[index], "%s", Line);
	
			int leng = strlen(sz_NgList[index]);
			
			if(sz_NgList[index][leng-1] == 10)
				sz_NgList[index][leng-1] = 0;

			index++;


			if(index>= MAX_NG_LIST)
				break;
			Line[0] = 0x00;
		}

		if(in)	fclose(in);
	}
	else
		Save();*/
}

CSystemData::CSystemData()
{
	// 20141110 LHC - Port[3], baudrate[3] 추가.(UV Controller)
	int i = 0;
	for(i=0; i<MAX_RS232_NO; i++)
	{
		iCommPort[i] = 1;
		iBaudRate[i] = 9600;
	}
	nEpoxyIndex = 0;
	nUvIndex = 0;
	m_iSystemNo = 0;
	m_iUnitNo = 0;
	m_iVacReverse = 0;

	memset(m_szBarcodeIp, 0x00, sizeof(m_szBarcodeIp));

	_stprintf_s(m_szBarcodeIp, SIZE_OF_100BYTE, _T("169.254.0.1"));
	m_nBarcodePort = 0;

	m_iAlignMode = 0;

	//Load();
	m_testRunMode = false;

	m_iSmoothness[0] = m_iSmoothness[1] = 50;
	m_iDicChange = 0;
	m_iIrChartUse = 0;
	m_iLaserInspPass = 0;
	m_iAlignCamInspPass = 0;
	m_iSfrMaxValueInsp = 0;
	m_iEpoxyLaserInspPass = 0;
	m_iStaintInspPass = 0;
	m_iDefectInspPass = 0;
	m_i1stAaEbable = 0;
	m_iUVPass = 0;
	m_iMTFUvInsp = 0;
	m_iDispensePass = 0;
	m_iDispenseInspPass = 0;
	m_iLine = 0;
	m_iProductComp = 0;
	m_iProductHolderBoning = 0;
	m_dOcSpec.x = 0.02;
	m_dOcSpec.y = 0.02;
	//--- 차트에서 마크 회전 방향 (시계방향=1, 반시계=0)
	m_SFR_Type[0]	= 1;
	m_SFR_Type[1]	= 1;
	m_SFR_Type[2]	= 0;
	m_SFR_Type[3]	= 1;
	m_SFR_Type[4]	= 0;
	/*m_SFR_Type[5]	= 1;
	m_SFR_Type[6]	= 0;
	
	m_SFR_Type[7]	= 1;
	m_SFR_Type[8]	= 0;
	m_SFR_Type[9]	= 1;
	m_SFR_Type[10]	= 0;
	m_SFR_Type[11]	= 1;
	m_SFR_Type[12]	= 1;
	m_SFR_Type[13]	= 0;
	m_SFR_Type[14]	= 0;
	m_SFR_Type[15]	= 1;
	m_SFR_Type[16]	= 0;
	m_SFR_Type[17]	= 1;
	m_SFR_Type[18]	= 0;
*/

	
	m_FreeRun = 0;

	for(i=0; i<MAX_MOTOR_NO; i++)
	{
		fMotorSpeed[i] = 10.0f;
		fMotorResol[i] = 1000.0f;
		fMotorAccTime[i] = 0.1f;
		dDataset[i] = 0.0;
	}

	dCamResol[0].x = dCamResol[0].y = 15.0f;
	dCamResol[1].x = dCamResol[1].y = 15.0f;
	dCamResol[2].x = dCamResol[2].y = 2.0f;

	dCamAngle[0].x = dCamAngle[0].y = 0.0;
	dCamAngle[1].x = dCamAngle[1].y = 0.0;
	dCamAngle[2].x = dCamAngle[2].y = 0.0;

	m_dOffset_Conti_Down_Z = 0.0;

	m_dOffset_Prev_UV_X = 0.0;
	m_dOffset_Prev_UV_Y = 0.0;
	m_dOffset_Prev_UV_Z = 0.0;
	m_dOffset_Prev_UV_Tx = 0.0;
	m_dOffset_Prev_UV_Ty = 0.0;
	m_dOffset_Prev_UV_Th = 0.0;

	dLimit_SFR_Balance = 0.01;
	dLimit_SFR_04F_Balance = 0.01;
	dLimit_SFR_07F_Balance = 0.01;

	dLimit_SFR[0]	= 0.56;
	dLimit_SFR[1]	= 0.40;
	dLimit_SFR[2]	= 0.40;
	dLimit_SFR[3]	= 0.40;
	dLimit_SFR[4]	= 0.38;
	dLimit_SFR[5]	= 0.38;
	dLimit_SFR[6]	= 0.33;
	dLimit_SFR[7]	= 0.33;
	dLimit_SFR[8]	= 0.33;
	dLimit_SFR[9]	= 0.30;
	dLimit_SFR[10]	= 0.30;
	dLimit_SFR[11]	= 0.3;
	dLimit_SFR[12]	= 0.3;
	dLimit_SFR[13]	= 0.3;
	dLimit_SFR[14]	= 0.3;

	Password =1234;	

	m_iExposureTime = 5000;

	iDoorInterlock = 1;

	m_Epoxy_Change_Count = 0;
	m_Log_Retention_Period = 0;
	
	m_Epoxy_Shot = 0;
	m_Epoxy_Alarm = 0;
	m_Epoxy_Start_Time = 0;
	m_Epoxy_Last_Time = 0;

	m_Socket_Count = 0;
	m_Socket_Alarm = 0;

	m_Factory_Code = "KA05FOC01";
	m_Mes_Port_Number = 8613;
	m_Comp_Factory_Code = "KA05FFT01";//KA05FOC01
	m_Mes_Comp_Port_Number = 8613;
	m_Mes_Ip_Number = "192.168.60.62";
}


void CSystemData::Save()
{
	FILE *out;
	TCHAR szIniBuff[SIZE_OF_1K];
	TCHAR szPath[SIZE_OF_1K];


	CFileFind finder;
	BOOL IsFind;
	CString FolderName, FolderName_D, backupFolderName_C, backupFolderName_D;
	SYSTEMTIME SysTime;
	::GetLocalTime(&SysTime);

	if(iCommPort[0]==0)
	{
		return;
	}

	FolderName.Format("%s\\%s\\Data", AA_MODEL_LOAD_DIR, model.mCurModelName);
	IsFind = finder.FindFile(FolderName);
	if(!IsFind)
	{
		FolderName.Format("%s", BASE_AA_MODEL_LOAD_DIR);
		CreateDirectory(FolderName,NULL); 

		FolderName.Format("%s", AA_MODEL_LOAD_DIR);
		CreateDirectory(FolderName, NULL);

		FolderName.Format("%s\\%s", AA_MODEL_LOAD_DIR, model.mCurModelName);
		CreateDirectory(FolderName, NULL);

		FolderName.Format("%s\\%s\\Data", AA_MODEL_LOAD_DIR, model.mCurModelName);
		CreateDirectory(FolderName, NULL);
	}

	backupFolderName_C.Format("%s\\%s\\%04d%02d", AA_BACKUP_LOAD_DIR, model.mCurModelName, SysTime.wYear, SysTime.wMonth);
	IsFind = finder.FindFile(backupFolderName_C);
	if (!IsFind)
	{
		backupFolderName_C.Format("%s", BASE_AA_MODEL_LOAD_DIR);
		IsFind = finder.FindFile(backupFolderName_C);
		if (!IsFind)
		{
			CreateDirectory(backupFolderName_C, NULL);
		}
		backupFolderName_C.Format("%s", BASE_AA_BACKUP_DIR);
		IsFind = finder.FindFile(backupFolderName_C);
		if (!IsFind)
		{
			CreateDirectory(backupFolderName_C, NULL);
		}

		backupFolderName_C.Format("%s", AA_BACKUP_LOAD_DIR);
		IsFind = finder.FindFile(backupFolderName_C);
		if (!IsFind)
		{
			CreateDirectory(backupFolderName_C, NULL);
		}
		backupFolderName_C.Format("%s\\%s", AA_BACKUP_LOAD_DIR, model.mCurModelName);
		IsFind = finder.FindFile(backupFolderName_C);
		if (!IsFind)
		{
			CreateDirectory(backupFolderName_C, NULL);
		}

		backupFolderName_C.Format("%s\\%s\\%04d%02d", AA_BACKUP_LOAD_DIR, model.mCurModelName, SysTime.wYear, SysTime.wMonth);
		CreateDirectory(backupFolderName_C, NULL);

	}


	finder.Close();




	char	fileName[1000];
	wsprintf(fileName, "%s\\SystemData.txt", FolderName);

	if(fopen_s(&out, fileName,"w"))
	{
		errMsg2(Task.AutoFlag, "SystemData Save Fail...");
	}
	else
	{
		fprintf_s(out,"CAM_RESOL %lf %lf %lf %lf %lf %lf\n",		 dCamResol[0].x, dCamResol[0].y, dCamResol[1].x, dCamResol[1].y, dCamResol[2].x, dCamResol[2].y);
		fprintf_s(out,"CAM_ANGLE %lf %lf %lf %lf %lf %lf\n",		 dCamAngle[0].x, dCamAngle[0].y, dCamAngle[1].x, dCamAngle[1].y, dCamAngle[2].x, dCamAngle[2].y);
			
		for(int i=0; i<MAX_MOTOR_NO; i++)
		{
			fprintf_s(out, "MOTOR_PARA %d %lf %f %f\n",	i, fMotorSpeed[i], fMotorAccTime[i], fMotorResol[i]);
		}

		fprintf_s(out, "OC_ALIGN_MODE	%d\n", m_iAlignMode);

		fprintf_s(out, "SFR_LIMIT		%lf\n",dLimit_SFR_Balance);
		fprintf_s(out, "MTF_BLANCE_0_4F		%lf\n", dLimit_SFR_04F_Balance);
		fprintf_s(out, "MTF_BLANCE_0_7F		%lf\n", dLimit_SFR_07F_Balance);
		fprintf_s(out, "SFR_SPEC		%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n"
			, dLimit_SFR[0], dLimit_SFR[1], dLimit_SFR[2], dLimit_SFR[3], dLimit_SFR[4]
			, dLimit_SFR[5], dLimit_SFR[6], dLimit_SFR[7], dLimit_SFR[8], dLimit_SFR[9]
			, dLimit_SFR[10], dLimit_SFR[11], dLimit_SFR[12], dLimit_SFR[13], dLimit_SFR[14]);
		fprintf_s(out, "UV_OFFSET		%lf %lf %lf %lf %lf %lf\n"
			, m_dOffset_Prev_UV_X, m_dOffset_Prev_UV_Y, m_dOffset_Prev_UV_Z
			, m_dOffset_Prev_UV_Tx, m_dOffset_Prev_UV_Ty, m_dOffset_Prev_UV_Th);
		fprintf_s(out, "DATA_SET		%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n", dDataset[0], dDataset[1], dDataset[2], dDataset[3], dDataset[4], dDataset[5], dDataset[6], dDataset[7], dDataset[8], dDataset[9], dDataset[10]);
		fprintf_s(out, "PASSWORD		%lf\n", Password);
		fprintf_s(out, "MODEL_FINDER	%d %d\n", m_iSmoothness[0], m_iSmoothness[1]);
		fprintf_s(out, "CCD_STAIN_INSP_PASS	%d\n", m_iStaintInspPass);
        fprintf_s(out, "CCD_DEFECT_INSP_PASS	%d\n", m_iDefectInspPass);

		fprintf_s(out, "LASER_INSP	%d\n", m_iLaserInspPass);
		fprintf_s(out, "EPOXY_LASER_INSP	%d\n", m_iEpoxyLaserInspPass);
		fprintf_s(out, "ALIGN_CAM_INSP	%d\n", m_iAlignCamInspPass);
		
		fprintf_s(out, "CONTI_ASK_PASS	%d\n", m_iDicChange);
		fprintf_s(out, "IR_CHART_USE	%d\n", m_iIrChartUse);
		
		fprintf_s(out, "SFR_MAX_VALUE_INSP	%d\n", m_iSfrMaxValueInsp);

		
		fprintf_s(out, "FIRST_AA_FINISH_ENABLE	%d\n", m_i1stAaEbable);
		fprintf_s(out, "OC_INSP_SPEC	%lf %lf %lf\n", m_dOcSpec.x, m_dOcSpec.y, dSpec_OC_Theta);
		fprintf_s(out, "MAX_SFR_LIMIT	%lf\n", dMax_Sfr_Limit);
		//
		fprintf_s(out, "MOVE_FINE_MAXPOS	%lf\n", m_dMove_MaxPos_Fine);

		fprintf_s(out, "EXPOSURE_TIME	%d\n", m_iExposureTime);
		fprintf_s(out, "EPOXY_INDEX	%d\n", nEpoxyIndex);
		fprintf_s(out, "UV_INDEX	%d\n", nUvIndex);
		fprintf_s(out, "RS_COMM_PORT	%d %d %d %d %d %d %d %d %d %d %d \n", iCommPort[0], iCommPort[1], iCommPort[2], iCommPort[3], iCommPort[4], iCommPort[5], iCommPort[6], iCommPort[7], iCommPort[8], iCommPort[9], iCommPort[10]);
		fprintf_s(out, "RS_COMM_BAUD	%d %d %d %d %d %d %d %d %d %d %d \n", iBaudRate[0], iBaudRate[1], iBaudRate[2], iBaudRate[3], iBaudRate[4], iBaudRate[5], iBaudRate[6], iBaudRate[7], iBaudRate[8], iBaudRate[9], iBaudRate[10]);
	
		_stprintf_s(szIniBuff, SIZE_OF_1K, _T("%s"), m_szBarcodeIp);
		fprintf_s(out, "BARCODE_IP	%s\n", szIniBuff);
		fprintf_s(out, "BARCODE_PORT	%d\n", m_nBarcodePort);

		fprintf_s(out, "UV_ENABLE	%d\n", m_iUVPass);
		fprintf_s(out, "MTF_UV_INSP	%d\n", m_iMTFUvInsp);
		// 
		fprintf_s(out, "DISPENSE_ENABLE	%d %d %d\n", m_iDispensePass, m_iDispenseInspPass, m_iLine);
		fprintf_s(out, "INSPECTION_MODE %d\n", m_iProductComp);
		fprintf_s(out, "HOLDERBONDING_MODE %d\n", m_iProductHolderBoning);
		fprintf_s(out, "DOOR_INTERLOCK	%d\n", iDoorInterlock);
		fprintf_s(out, "FRONT_CURTAIN	%d\n", m_iFront);
		fprintf_s(out, "EPOXY_CHANGE_COUNT	%d\n", m_Epoxy_Change_Count);
		fprintf_s(out, "LOG_RETENTION_PERIOD	%d\n", m_Log_Retention_Period);
		fprintf_s(out, "LAST_LOG_DELETE_DATE	%s\n", (LPTSTR)(LPCTSTR)m_Last_Log_Delete_Date);
		fprintf_s(out, "FACTORY_CODE	%s\n", (LPTSTR)(LPCTSTR)m_Factory_Code);
		fprintf_s(out, "MES_PORT_NO		%d\n",m_Mes_Port_Number);
		fprintf_s(out, "MES_IP_NO		%s\n", (LPTSTR)(LPCTSTR)m_Mes_Ip_Number);
		fprintf_s(out, "COMP_FACTORY_CODE	%s\n", (LPTSTR)(LPCTSTR)m_Comp_Factory_Code);
		fprintf_s(out, "MES_COMP_PORT_NO		%d\n",m_Mes_Comp_Port_Number);
		fprintf_s(out, _T("AAROI	%d\n"), m_iAASel);
		fprintf_s(out, "EPOXY_CHANGE		%d %d\n", m_Epoxy_Shot, m_Epoxy_Alarm);
		fprintf_s(out, "EPOXY_CHANGE_STIME	%d\n", m_Epoxy_Start_Time);
		fprintf_s(out, "EPOXY_CHANGE_LTIME	%d\n", m_Epoxy_Last_Time);
		fprintf_s(out, "SOCKET_COUNT		%d %d \n", m_Socket_Count, m_Socket_Alarm);
		fprintf_s(out, "CONTI_OFFSET_Z		%lf \n", m_dOffset_Conti_Down_Z);
		if(out)	fclose(out);
	}

#ifdef		ON_LINE_MODE
	char	backupName_C[1000];
	wsprintf(backupName_C, "%s\\SystemData_%04d%02d%02d_%02d%02d.txt", backupFolderName_C, SysTime.wYear, SysTime.wMonth, SysTime.wDay, SysTime.wHour, SysTime.wMinute);
	::CopyFile(fileName, backupName_C, FALSE);

#endif
}


void CSystemData::Load()
{
	TCHAR szPath[SIZE_OF_1K];
	FILE* in;

	CString cMsg;
	char	temp[500];

	char	Line[500];
	char	Title[500];	
	int		nRtn, index;

	char	fileName[1000];		


	wsprintf(fileName, "%s\\%s\\Data\\SystemData.txt", AA_MODEL_LOAD_DIR, model.mCurModelName);

	if(!fopen_s(&in, fileName,"r"))
	{
		while (1)
		{
			fgets(Line, 499, in);
			nRtn = sscanf_s(Line, "%s", &Title, 499);

			if (nRtn==EOF)	
				break;

			else if( strcmp(Title, "CAM_RESOL")==0 )
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf",		Title, 499, &dCamResol[0].x, &dCamResol[0].y, &dCamResol[1].x, &dCamResol[1].y, &dCamResol[2].x, &dCamResol[2].y);
			}
			else if( strcmp(Title, "CAM_ANGLE")==0 )
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf",		Title, 499, &dCamAngle[0].x, &dCamAngle[0].y, &dCamAngle[1].x, &dCamAngle[1].y, &dCamAngle[2].x, &dCamAngle[2].y);
			}
			else if (strcmp(Title, "MOTOR_PARA")==0)
			{
				sscanf_s(Line, "%s %d",								Title, 499, &index);
				sscanf_s(Line, "%s %d %lf %f %f",					Title, 499, &index, &fMotorSpeed[index], &fMotorAccTime[index], &fMotorResol[index]);
			}
			else if(strcmp(Title, "SFR_LIMIT")==0)
			{
				sscanf_s(Line, "%s %lf",					Title, 499,&dLimit_SFR_Balance);
			}
			else if(strcmp(Title, "MTF_BLANCE_0_4F")==0)
			{
				sscanf_s(Line, "%s %lf",					Title, 499, &dLimit_SFR_04F_Balance);
			}
			else if(strcmp(Title, "MTF_BLANCE_0_7F")==0)
			{
				sscanf_s(Line, "%s %lf",					Title, 499, &dLimit_SFR_07F_Balance);
			}
			else if(strcmp(Title, "OC_ALIGN_MODE")==0)
			{
				sscanf_s(Line, "%s %d",								Title, 499, &m_iAlignMode);
			}
			else if(strcmp(Title, "SFR_SPEC")==0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",	Title, 499
					, &dLimit_SFR[0],  &dLimit_SFR[1],  &dLimit_SFR[2],  &dLimit_SFR[3],  &dLimit_SFR[4]
					, &dLimit_SFR[5],  &dLimit_SFR[6],  &dLimit_SFR[7],  &dLimit_SFR[8],  &dLimit_SFR[9]
					, &dLimit_SFR[10], &dLimit_SFR[11], &dLimit_SFR[12], &dLimit_SFR[13], &dLimit_SFR[14]);
			}
			else if(strcmp(Title, "UV_OFFSET")==0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf",						Title, 499
					, &m_dOffset_Prev_UV_X, &m_dOffset_Prev_UV_Y, &m_dOffset_Prev_UV_Z
					, &m_dOffset_Prev_UV_Tx, &m_dOffset_Prev_UV_Ty, &m_dOffset_Prev_UV_Th);
			}
			else if(strcmp(Title, "DATA_SET")==0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", Title, 499, &dDataset[0], &dDataset[1], &dDataset[2], &dDataset[3], &dDataset[4], &dDataset[5], &dDataset[6], &dDataset[7], &dDataset[8], &dDataset[9], &dDataset[10]);

			}
			else if(strcmp(Title, "PASSWORD")==0)
			{
				sscanf_s(Line, "%s %lf",						Title, 499, &Password);
			}
            else if (strcmp(Title, "CCD_STAIN_INSP_PASS") == 0)
            {
                sscanf_s(Line, "%s %d", Title, 499, &m_iStaintInspPass);
            }
            else if (strcmp(Title, "CCD_DEFECT_INSP_PASS") == 0)
            {
                sscanf_s(Line, "%s %d", Title, 499, &m_iDefectInspPass);
            }
			else if (strcmp(Title, "LASER_INSP") == 0)
			{
				sscanf_s(Line, "%s %d", Title, 499, &m_iLaserInspPass);
			}
			else if (strcmp(Title, "ALIGN_CAM_INSP") == 0)
			{
				sscanf_s(Line, "%s %d", Title, 499, &m_iAlignCamInspPass);
			}
			else if (strcmp(Title, "EPOXY_LASER_INSP") == 0)
			{
				sscanf_s(Line, "%s %d", Title, 499, &m_iEpoxyLaserInspPass);
			}
			else if (strcmp(Title, "CONTI_ASK_PASS") == 0)
			{
				sscanf_s(Line, "%s %d", Title, 499, &m_iDicChange);
			}
			else if (strcmp(Title, "IR_CHART_USE") == 0)
			{
				sscanf_s(Line, "%s %d", Title, 499, &m_iIrChartUse);
			}
			else if (strcmp(Title, "SFR_MAX_VALUE_INSP") == 0) 
			{
				sscanf_s(Line, "%s %d", Title, 499, &m_iSfrMaxValueInsp);
			}
			else if(strcmp(Title, "FIRST_AA_FINISH_ENABLE")==0)
			{
				sscanf_s(Line, "%s %d",							Title, 499, &m_i1stAaEbable);
			}
			else if (strcmp(Title, "OC_INSP_SPEC") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf", Title, 499, &m_dOcSpec.x, &m_dOcSpec.y, &dSpec_OC_Theta);
			}
			else if (strcmp(Title, "MAX_SFR_LIMIT") == 0)
			{
				sscanf_s(Line, "%s %lf", Title, 499, &dMax_Sfr_Limit);
			}
			else if(strcmp(Title, "MODEL_FINDER")==0)
			{
				sscanf_s(Line, "%s %d %d",						Title, 499, &m_iSmoothness[0], &m_iSmoothness[1]);
			}
			else if(strcmp(Title, "MOVE_FINE_MAXPOS")==0)
			{
				sscanf_s(Line, "%s %lf",						Title, 499, &m_dMove_MaxPos_Fine);
			}
			else if(strcmp(Title, "EXPOSURE_TIME")==0)
			{
				sscanf_s(Line, "%s %d",						Title, 499, &m_iExposureTime);
			}
			else if (strcmp(Title, "EPOXY_INDEX") == 0)
			{
				sscanf_s(Line, "%s %d", Title, 499, &nEpoxyIndex);
			}
			else if (strcmp(Title, "UV_INDEX") == 0)
			{
				sscanf_s(Line, "%s %d", Title, 499, &nUvIndex);
			}
			else if (strcmp(Title, "BARCODE_IP") == 0)
			{
				sscanf_s(Line, "%s %s", szPath, (unsigned int)sizeof(szPath), m_szBarcodeIp, (unsigned int)sizeof(m_szBarcodeIp));
			}
			else if (strcmp(Title, "BARCODE_PORT") == 0)
			{
				sscanf_s(Line, "%s %d", Title, 499, &m_nBarcodePort);
			}
			else if( strcmp(Title, "RS_COMM_PORT") == 0 )
			{
				sscanf_s(Line, "%s %d %d %d %d %d %d %d %d %d %d %d", Title, 499, &iCommPort[0], &iCommPort[1], &iCommPort[2], &iCommPort[3], &iCommPort[4], &iCommPort[5], &iCommPort[6], &iCommPort[7], &iCommPort[8], &iCommPort[9], &iCommPort[10]);
			}
			else if( strcmp(Title, "RS_COMM_BAUD") == 0 )
			{
				sscanf_s(Line, "%s %d %d %d %d %d %d %d %d %d %d %d", Title, 499, &iBaudRate[0], &iBaudRate[1], &iBaudRate[2], &iBaudRate[3], &iBaudRate[4], &iBaudRate[5], &iBaudRate[6], &iBaudRate[7], &iBaudRate[8], &iBaudRate[9], &iBaudRate[10]);
			}
			else if(strcmp(Title, "UV_ENABLE") == 0)
			{
				sscanf_s(Line, "%s %d",							Title, 499, &m_iUVPass);
			}
			else if(strcmp(Title, "MTF_UV_INSP") == 0)
			{
				sscanf_s(Line, "%s %d",							Title, 499, &m_iMTFUvInsp);
			}
			else if(strcmp(Title, "DISPENSE_ENABLE") == 0)
			{
				sscanf_s(Line, "%s %d %d %d",							Title, 499, &m_iDispensePass, &m_iDispenseInspPass, &m_iLine);
			}
			else if(strcmp(Title, "INSPECTION_MODE") == 0)
			{
				sscanf_s(Line, "%s %d",								Title, 499, &m_iProductComp);
			}
			else if (strcmp(Title, "HOLDERBONDING_MODE") == 0)
			{
				sscanf_s(Line, "%s %d", Title, 499, &m_iProductHolderBoning);
			}
			else if(strcmp(Title, "DOOR_INTERLOCK") == 0)
			{
				sscanf_s(Line, "%s	%d",							Title, 499, &iDoorInterlock);
			}
			else if(strcmp(Title, "FRONT_CURTAIN") == 0)
			{
				sscanf_s(Line, "%s	%d",							Title, 499, &m_iFront);
			}
			else if(strcmp(Title, "EPOXY_CHANGE_COUNT") == 0)
			{
				sscanf_s(Line, "%s	%d",							Title, 499, &m_Epoxy_Change_Count);
			}			
			else if(strcmp(Title, "LOG_RETENTION_PERIOD") == 0)
			{
				sscanf_s(Line, "%s	%d",							Title, 499, &m_Log_Retention_Period);
			}
			else if(strcmp(Title, "LAST_LOG_DELETE_DATE") == 0)
			{
				sscanf_s(Line, "%s	%s",							Title, 499, (LPTSTR)(LPCTSTR)m_Last_Log_Delete_Date, 499);
			}
			else if(strcmp(Title, "FACTORY_CODE") == 0)
			{
				sscanf_s(Line, "%s	%s",							Title, 499, temp, 499);
				m_Factory_Code.Format("%s",temp);
			}
			else if(strcmp(Title, "MES_PORT_NO") == 0)
			{
				sscanf_s(Line, "%s	%d",							Title, 499, &m_Mes_Port_Number);
			}
			else if(strcmp(Title, "MES_IP_NO") == 0)
			{
				sscanf_s(Line, "%s	%s",							Title, 499, temp, 499);
				m_Mes_Ip_Number.Format("%s",temp);
			}
			else if(strcmp(Title, "COMP_FACTORY_CODE") == 0)
			{
				sscanf_s(Line, "%s	%s",							Title, 499, temp, 499);
				m_Comp_Factory_Code.Format("%s",temp);
			}
			else if(strcmp(Title, "MES_COMP_PORT_NO") == 0)
			{
				sscanf_s(Line, "%s	%d",							Title, 499, &m_Mes_Comp_Port_Number);
			}
			else if(strcmp(Title, "AAROI")==0)
			{
				sscanf_s(Line, "%s	%d",							Title, 499, &m_iAASel);
			}
			else if( strcmp(Title, "EPOXY_CHANGE") == 0 )
			{
				sscanf_s(Line, "%s %d %d", Title, 499, &m_Epoxy_Shot, &m_Epoxy_Alarm);
			}
			else if( strcmp(Title, "EPOXY_CHANGE_STIME") == 0 )
			{
				sscanf_s(Line, "%s %d", Title, 499, &m_Epoxy_Start_Time);
			}
			else if( strcmp(Title, "EPOXY_CHANGE_LTIME") == 0 )
			{
				sscanf_s(Line, "%s %d", Title, 499, &m_Epoxy_Last_Time);
			}
			else if (strcmp(Title, "SOCKET_COUNT") == 0)
			{
				sscanf_s(Line, "%s %d %d", Title, 499, &m_Socket_Count, &m_Socket_Alarm);
			}
			else if (strcmp(Title, "CONTI_OFFSET_Z") == 0)
			{ 
				sscanf_s(Line, "%s %lf", Title, 499, &m_dOffset_Conti_Down_Z);
			}

			Line[0] = 0x00;
		}
		if(in)	fclose(in);

	}
	else
		Save();
}

CWork::CWork()
{
	m_iCnt_Output =0;
	m_iCnt_NG_Output =0;
	m_iCoverUpDownCnt = 0;
	iInspCnt_Output	= 0;
	iInspCnt_NG_Output	= 0;
	iInspCnt_NG_MTF	= 0;
	iInspCnt_NG_OC	= 0;
	iInspCnt_NG_Distortion	= 0;
	iInspCnt_NG_Current	= 0;
	iInspCnt_NG_TestPattern	= 0;
	iInspCnt_NG_Defect	= 0;
	iInspCnt_NG_Stain	= 0;
	iInspCnt_NG_Dark	= 0;
	iInspCnt_NG_Uniformity	= 0;

	m_Epoxy_Time_Check_Hour = 0;   // 20141125 LHC - 시간체크 시작시  현재시간 저장
	m_Epoxy_Time_Check_Min = 0;
	m_Epoxy_Time_Check_Month = 0;
	m_Epoxy_Time_Check_Day = 0;
	m_Epoxy_Time_Flag = 0;
}

void CWork::Save()
{
	FILE *out;

	CFileFind finder;
	BOOL IsFind;
	CString FolderName;
	//wsprintf(fileName, "%s\\%s\\Data\\WorkData.txt", AA_MODEL_LOAD_DIR, modelList.curModelName);

	FolderName.Format("%s", AA_MODEL_LOAD_DIR);

	IsFind = finder.FindFile(FolderName);
	if(!IsFind)
	{
		FolderName.Format("%s", BASE_AA_MODEL_LOAD_DIR);

		IsFind = finder.FindFile(FolderName);
		if(!IsFind)
		{
			CreateDirectory(FolderName,NULL); 
		}

		FolderName.Format("%s", AA_MODEL_LOAD_DIR);

		CreateDirectory(FolderName,NULL); 
	}

	finder.Close();

	char tmpStr[1000];
	wsprintf(tmpStr, "%s\\%s\\Data\\WorkData.txt", FolderName, modelList.curModelName);
	if(fopen_s(&out, tmpStr,"w"))
	{
		errMsg2(Task.AutoFlag, "WorkData 저장 실패...");
	}
	else
	{
		fprintf_s(out,"INSP_CNT %d %d %d\n",		 m_iCnt_Output, m_iCnt_NG_Output, m_iCoverUpDownCnt);

		//fprintf_s(out, "Clean	%d %lf %lf\n", Cleancnt, Cleanpad[0], Cleanpad[1]);

		fprintf_s(out, "MANDO_INSP_CNT %d %d %d %d %d %d %d %d %d %d %d\n",
			iInspCnt_Output,
			iInspCnt_NG_Output,
			iInspCnt_NG_MTF,
			iInspCnt_NG_OC,
			iInspCnt_NG_Distortion,
			iInspCnt_NG_Current,
			iInspCnt_NG_TestPattern,
			iInspCnt_NG_Defect,
			iInspCnt_NG_Stain,
			iInspCnt_NG_Dark,
			iInspCnt_NG_Uniformity);

		fprintf_s(out, "EPOXY_TIME_CHECK	%d %04d %02d %02d %02d %02d\n", m_Epoxy_Time_Flag, m_Epoxy_Time_Check_Year, 
			m_Epoxy_Time_Check_Month,m_Epoxy_Time_Check_Day,
			m_Epoxy_Time_Check_Hour,m_Epoxy_Time_Check_Min);

		if(out)		fclose(out);
	}
}


void CWork::SaveCntLog()
{
	FILE *out;

	CFileFind finder;
	BOOL IsFind;
	CString FolderName;

	SYSTEMTIME time;
	::GetLocalTime(&time);

	FolderName.Format("%s\\%04d%02d", ALARM_DIR, time.wYear, time.wMonth);
	IsFind = finder.FindFile(FolderName);

	if(!IsFind)
	{
		FolderName.Format("%s", BASE_DIR);
		IsFind = finder.FindFile(FolderName);
		if(!IsFind)
			CreateDirectory(FolderName,NULL); 

		FolderName.Format("%s", ALARM_DIR);
		IsFind = finder.FindFile(FolderName);
		if(!IsFind)
			CreateDirectory(FolderName,NULL); 

		FolderName.Format("%s\\%04d%02d", ALARM_DIR, time.wYear, time.wMonth);
		CreateDirectory(FolderName,NULL);
	}

	finder.Close();

	char tmpStr[1000];
	wsprintf(tmpStr, "%s\\ProductCnt_%04d%02d%02d.txt", FolderName, time.wYear, time.wMonth, time.wDay);

	if(!fopen_s(&out, tmpStr,"a"))
	{
		fprintf_s(out,"%02d:%02d:%02d, %d, %d, %d %s\n",		time.wHour, time.wMinute, time.wSecond, m_iCnt_Output, m_iCnt_NG_Output, sysData.m_Socket_Count,/*m_iCoverUpDownCnt,*/ Task.LotNo);

		if(out)	fclose(out);
	}

}


void CWork::Load()
{
	FILE* in;

	CString tmpStr;
	char	fileName[1000];
	//wsprintf(fileName, "%s\\WorkData.txt", DATA_DIR);
	wsprintf(fileName, "%s\\%s\\Data\\WorkData.txt", AA_MODEL_LOAD_DIR, modelList.curModelName);

	if(!fopen_s(&in, fileName,"r"))
	{
		char	Line[500];
		char	Title[500];
		int		nRtn;

		while (1)
		{
			fgets(Line, 499, in);
			nRtn = sscanf_s(Line, "%s", &Title, 499);

			if (nRtn==EOF)	
				break;

			else if( strcmp(Title, "INSP_CNT")==0 )
			{
				sscanf_s(Line, "%s %d %d %d",		Title, 499, &m_iCnt_Output, &m_iCnt_NG_Output, &m_iCoverUpDownCnt);
			}
			//else if(strcmp(Title, "Clean")==0)
			//{
			//	sscanf_s(Line, "%s %d %lf %lf",						Title, 499, &Cleancnt, &Cleanpad[0], &Cleanpad[1]);
			//}
			else if( strcmp(Title, "MANDO_INSP_CNT") == 0 )
			{
				sscanf_s(Line, "%s  %d %d %d %d %d %d %d %d %d %d %d", Title, 499, 
					&iInspCnt_Output,
					&iInspCnt_NG_Output,
					&iInspCnt_NG_MTF,
					&iInspCnt_NG_OC,
					&iInspCnt_NG_Distortion,
					&iInspCnt_NG_Current,
					&iInspCnt_NG_TestPattern,
					&iInspCnt_NG_Defect,
					&iInspCnt_NG_Stain,
					&iInspCnt_NG_Dark,
					&iInspCnt_NG_Uniformity);
			}
			else if(strcmp(Title, "EPOXY_TIME_CHECK") == 0)
			{
				sscanf_s(Line, "%s	%d %d %d %d %d %d",				Title, 499, &m_Epoxy_Time_Flag, 
					&m_Epoxy_Time_Check_Year, &m_Epoxy_Time_Check_Month,
					&m_Epoxy_Time_Check_Day,&m_Epoxy_Time_Check_Hour,&m_Epoxy_Time_Check_Min);
			}
			Line[0] = 0x00;
		}

		if(in)	fclose(in);
	}
	else
		Save();
}


void CWork::InspCountReset()
{
	iInspCnt_Output	= 0;
	iInspCnt_NG_Output	= 0;
	iInspCnt_NG_MTF	= 0;
	iInspCnt_NG_OC	= 0;
	iInspCnt_NG_Distortion	= 0;
	iInspCnt_NG_Current	= 0;
	iInspCnt_NG_TestPattern	= 0;
	iInspCnt_NG_Defect	= 0;
	iInspCnt_NG_Stain	= 0;
	iInspCnt_NG_Dark	= 0;
	iInspCnt_NG_Uniformity	= 0;
	Save();
}

CModelList::CModelList()
{
	TotalCount = 1;

	memset(ModelName, 0x00, sizeof(ModelName));// MAX_MODEL_CNT * 50);
	//sprintf_s(curModelName, "TEST", 50);
	//sprintf_s(name[0], "TEST", 50);
}


bool CModelList::NewSave()
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szIniIndex[SIZE_OF_100BYTE];
	TCHAR szIniBuff[SIZE_OF_1K];
	CFileFind clFinder;
	TCHAR szData[SIZE_OF_1K];
	TCHAR szLog[SIZE_OF_1K];
	int i = 0;
#if (____AA_WAY == PCB_TILT_AA)
	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\PCB_AA_ModelList.ini"), BASE_AA_MODEL_LOAD_DIR);
#else
	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\LENS_AA_ModelList.ini"), BASE_AA_MODEL_LOAD_DIR);
#endif
	
	if (clFinder.FindFile(szPath) == FALSE)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[Info] %s 파일 없습니다."), szPath);
		theApp.MainDlg->putListLog(szLog);
		return false;
	}


	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), TotalCount);
	WritePrivateProfileString(_T("MODEL"), _T("COUNT"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), CurrentModelIndex);
	WritePrivateProfileString(_T("MODEL"), _T("CURRENT"), szData, szPath);

	TCHAR* pszCol[] = { _T("PCB_AA"), _T("LENS_AA") };
	int ModelCount = TotalCount;


	for (i = 0; i < TotalCount; i++)
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("Model%d"), i + 1);
		_stprintf_s(szData, SIZE_OF_1K, _T("%s"), ModelName[i]);
		WritePrivateProfileString(_T("MODEL_LIST"), szIniIndex, szData, szPath);
	}
	return true;
}

bool CModelList::NewLoad()
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szIniIndex[SIZE_OF_100BYTE];
	TCHAR szIniBuff[SIZE_OF_1K];
	//CModelInfo cLensLotFixId;
	CFileFind clFinder;

	TCHAR szLog[SIZE_OF_1K];
	int i = 0;

#if (____AA_WAY == PCB_TILT_AA)
	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\PCB_AA_ModelList.ini"), BASE_AA_MODEL_LOAD_DIR);
#else
	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\LENS_AA_ModelList.ini"), BASE_AA_MODEL_LOAD_DIR);
#endif

	//_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\PCB_AA_ModelList.ini"), BASE_AA_MODEL_LOAD_DIR);
	//_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\LENS_AA_ModelList.ini"), AA_MODEL_LOAD_DIR);

	if (clFinder.FindFile(szPath) == FALSE)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[Info] %s 파일 없습니다."), szPath);
		theApp.MainDlg->putListLog(szLog);
		return false;
	}
	// 모델 총 개수
	TotalCount = GetPrivateProfileInt(_T("MODEL"), _T("COUNT"), 0, szPath);
	// 현재 모델 순번
	CurrentModelIndex = GetPrivateProfileInt(_T("MODEL"), _T("CURRENT"), 0, szPath);
	if (TotalCount < 1)
	{
		return false;
	}


	TCHAR* pszCol[] = { _T("PCB_AA"), _T("LENS_AA") };
	int ModelCount = modelList.TotalCount;

	char tmpName[SIZE_OF_100BYTE];
	int LoadDataTotalCount = 0;		//총개수와 name이 다를 수 있어서
	for (i = 0; i < ModelCount; i++)		//총 10개까지 로드
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("Model%d"), i + 1);
		GetPrivateProfileString(_T("MODEL_LIST"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);

		if (_tcslen(szIniBuff) > 0)
		{

			_tcscpy_s(tmpName, SIZE_OF_100BYTE, szIniBuff);
			wsprintf(ModelName[LoadDataTotalCount], "%s", tmpName);
			_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] MODEL%d =%s"), pszCol[0], i + 1, ModelName[LoadDataTotalCount]);
			theApp.MainDlg->putListLog(szLog);
			LoadDataTotalCount++;
		}
	}

	_tcscpy_s(curModelName, SIZE_OF_100BYTE, ModelName[CurrentModelIndex]);
	//sprintf_s(model.mCurModelName, sizeof(model.mCurModelName), "%s", curModelName);
	//_stprintf_s(model.mCurModelName, SIZE_OF_100BYTE, _T("%s"), curModelName);
	model.mCurModelName.Format(_T("%s"), curModelName);
	_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] CURRENT MODEL =(%s)"), pszCol[0], curModelName);
	theApp.MainDlg->putListLog(szLog);

	_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] TOTAL LOAD COUNT = %d[%d]"), pszCol[0], LoadDataTotalCount, modelList.TotalCount);
	theApp.MainDlg->putListLog(szLog);

	return true;

}



CModelData::CModelData()
{
	//sprintf_s(mCurModelName, sizeof(mCurModelName) , "TEST");
	//_stprintf_s(mCurModelName, SIZE_OF_100BYTE, _T("TEST"));
	model.mCurModelName.Format(_T("TEST"));
	int i = 0;
	mGlobalChartCount = 5;
	mGlobalChartType = 0;
	mGlobalChartFind = 0;
	m_dDemosaic = 0;
	//-------------------------------------------------------------------------
	//
	//★ACMIS 검사 Spec Data
	//-------------------------------------------------------------------------
	for (i = 0; i < 26; i++)
	{
		m_DefectSpec[i] = 0.0;
	}
	for (i = 0; i < 9; i++)
	{
		m_FovSpec[i] = 0.0;
	}
	m_OcSpec[0] = 0.0;
	m_OcSpec[1] = 0.0;

	m_ColorSensitivitySpec[0] = 0.0;
	for (i = 0; i < 7; i++)
	{
		m_UniformSpec[i] = 0.0;
	}
	for (i = 0; i < 5; i++)
	{
		m_RIlluminationSpec[i] = 0.0;
	}

	n_DefectCountLimit = 0;
	n_ClusterCountLimit = 0;

	m_dStainLsbCenter = 0.0;
	m_dStainLsbCorner = 0.0;
	m_dStainLsbEdge = 0.0;
	m_dStainYMeanCenter = 0.0;
	m_dStainYMeanCorner = 0.0;
	m_dStainYMeanEdge = 0.0;

	m_dStaturationMin = 0.0;
	m_dStaturationMax = 0.0;

	m_dChartHfovMin = 0.0;
	m_dChartHfovMax = 0.0;

	m_dChartVfovMin = 0.0;
	m_dChartVfovMax = 0.0;

	m_dChartDistortionMin = 0.0;
	m_dChartDistortionMax = 0.0;
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	m_InspPcbTilt[0] = 0.0;
	m_InspPcbTilt[1] = 0.0;

	d_SIDE_MODEL_CH = 0;
	code1 = 341;
	code2 = 511;
	dFov = 0.1;

	for (int i=0 ; i<3 ; i++)
	{
		for (int j=0 ; j<2 ; j++)
		{
			m_MarkSize[i][j].x = m_MarkSize[i][j].y = 0;
			m_MarkCenter[i][j].x = m_MarkCenter[i][j].y = 0.0;
			m_MarkOrigin[i][j].x = m_MarkOrigin[i][j].y = 0.0;
			m_iLimitRate[i][j] = 70;
		}
	}
	for (int i=0 ; i<MAX_LIGHT_DATA ; i++)
	{
		m_iLedValue[i] = 40;
	}
	for (int i=0 ; i<4 ; i++)
	{
		m_MarkMatchingRate[i] = 50;
	}

	for (i = 0; i < 36; i++)//for (i = 0; i < MTF_INSP_CNT; i++)
	{
		m_SaturationMin[i] = 0.0;
		m_SaturationMax[i] = 0.0;
		m_SaturationThreshold[i] = 0.0;
	}

	//-------------------------------------------------------------------------------------------
    for (i = 0; i < COMMON_MTF_INSP_CNT; i++)
    {
        m_LogSfr[i] = 0.0;
		m_LogSaturation[i] = 0.0;
    }

	dGen2Current = 0.0;
	m_LogDefectBrightVery = 0;
	m_LogDefectDarkVery = 0;
	m_LogDefectHotVery = 0;

    m_LogDefectBright = 0;
    m_LogDefectDark = 0;
    m_LogDefectHot = 0;
    m_LogDefectBrightCluster = 0;
    m_LogDefectDarkCluster = 0;
    m_LogDefectHotCluster = 0;
    m_LogDefectDarkHorLine = 0;
    m_LogDefectDarkVerLine = 0;
    m_LogDefectBrightHorLine = 0;
    m_LogDefectBrightVerLine = 0;
	for (i = 0; i<4; i++)
	{
		m_LogDefectColumnFPN[i] = 0;
	}
    
    //
    m_LogOC_X = 0.0;          //890 
    m_LogOC_Y = 0.0;          //930
    m_LogOC_DelatX = 0.0;     //-20
    m_LogOC_DelatY = 0.0;     //20
                              //
    m_LogDistortion = 0.0;
    //
    m_LogBlemishBlackSpot = 0.0;
    m_LogBlemishLcb = 0.0;
    m_LogBlemishRU_Ymean = 0.0;
    //
    m_Log_CS_RC_6500K = 0.0;
    m_Log_CS_BC_6500K = 0.0;
    m_Log_CS_CrCb_6500K = 0.0;
    m_Log_CS_RC_2800K = 0.0;
    m_Log_CS_BC_2800K = 0.0;
    m_Log_CS_CrCb_2800K = 0.0;

    for (i = 0; i < 100; i++)
    {
        m_Log_RI_RED[i] = 0.0;
        m_Log_RI_CLEARR[i] = 0.0;
        m_Log_RI_CLEARB[i] = 0.0;
        m_Log_RI_BLUE[i] = 0.0;
    }


    //
	//
	m_Log_RI_CornerVar_R = 0.0;
	m_Log_RI_CornerVar_Cr = 0.0;
	m_Log_RI_CornerVar_Cb = 0.0;
	m_Log_RI_CornerVar_B = 0.0;
	//
    m_Log_RI_Center_R = 0.0;
    m_Log_RI_Center_Cr = 0.0;
    m_Log_RI_Center_Cb = 0.0;
    m_Log_RI_Center_B = 0.0;
    m_Log_RI_LT_Ratio_R = 0.0;
    m_Log_RI_LT_Ratio_Cr = 0.0;
    m_Log_RI_LT_Ratio_Cb = 0.0;
    m_Log_RI_LT_Ratio_B = 0.0;
    m_Log_RI_RT_Ratio_R = 0.0;
    m_Log_RI_RT_Ratio_Cr = 0.0;
    m_Log_RI_RT_Ratio_Cb = 0.0;
    m_Log_RI_RT_Ratio_B = 0.0;
    m_Log_RI_LB_Ratio_R = 0.0;
    m_Log_RI_LB_Ratio_Cr = 0.0;
    m_Log_RI_LB_Ratio_Cb = 0.0;
    m_Log_RI_LB_Ratio_B = 0.0;
    m_Log_RI_RB_Ratio_R = 0.0;
    m_Log_RI_RB_Ratio_Cr = 0.0;
    m_Log_RI_RB_Ratio_Cb = 0.0;
    m_Log_RI_RB_Ratio_B = 0.0;

    //
    m_Log_SNR_SNR = 0.0;
    m_Log_SNR_DR = 0.0;
    //
    m_Log_CU_LT_Delta_RG = 0.0;
    m_Log_CU_LT_Delta_RB = 0.0;
    m_Log_CU_LT_Delta_BG = 0.0;
    m_Log_CU_RT_Delta_RG = 0.0;
    m_Log_CU_RT_Delta_RB = 0.0;
    m_Log_CU_RT_Delta_BG = 0.0;
    m_Log_CU_LB_Delta_RG = 0.0;
    m_Log_CU_LB_Delta_RB = 0.0;
    m_Log_CU_LB_Delta_BG = 0.0;
    m_Log_CU_RB_Delta_RG = 0.0;
    m_Log_CU_RB_Delta_RB = 0.0;
    m_Log_CU_RB_Delta_BG = 0.0;
    //
    m_Log_FOV_H_FOV = 0.0;
    m_Log_FOV_V_FOV = 0.0;
    m_Log_FOV_D_FOV = 0.0;
    m_Log_Rotate = 0.0;
    //------------------------------------------------------------------------------------------------
	m_iBright[0] = m_iBright[1] = m_iBright[2] = m_iContrast[0] = m_iContrast[1] = m_iContrast[2] = 0;

	UV_Time = 5000;
	UV_Weight = 0.3;
	UV_Power = 95;
	AARepeatCount = 0;
	Tilt_Weight_Pre = 0.0;
	Tilt_Weight_Post = 0.0;

	Tilt_Diretion[0] = 1;
	Tilt_Diretion[1] = 1;
	Tilt_Diretion[2] = 1;
	Tilt_Diretion[3] = 1;
	Tilt_Diretion[4] = 1;
	for (int i=0 ; i<MAX_MOTOR_NO ; i++)
	{
		axis[i].m_dLimit_OK = 0;
		axis[i].m_dLimit_Err = 0;

		for (int j=0 ; i<MAX_POS_NO ; i++)
			axis[i].pos[j] = 0.0;
	}

	strInfo_AF1.m_iDelayTime	= 5;
	strInfo_AF1.m_iStepCnt		= 10;
	strInfo_AF1.m_dMoveDistance	= 1;
	strInfo_AF1.m_dMoveVel		= 1;
	strInfo_AF1.m_fLimit_MTF	= 0.6f;

	strInfo_AF2.m_iDelayTime	= 5;
	strInfo_AF2.m_iStepCnt		= 10;
	strInfo_AF2.m_dMoveDistance	= 1;
	strInfo_AF2.m_dMoveVel		= 1;
	strInfo_AF2.m_fLimit_MTF	= 0.6f;

	strInfo_Tilt.m_iDelayTime	 = 5;
	strInfo_Tilt.m_iStepCnt		 = 10;
	strInfo_Tilt.m_dMoveDistance = 1;
	strInfo_Tilt.m_dMoveVel		 = 1;
	strInfo_Tilt.m_fLimit_MTF	= 0.6f;

	for (int i=0 ; i<4 ; i++)
	{
		strInfo_Cam[i].m_iDelayTime	= 5;
		strInfo_Cam[i].m_iRetryCnt		= 3;
	}

	strInfo_CCM.m_iCnt_Average_Thru_Focus    = 2;
	strInfo_CCM.m_iCnt_Average_Tilting       = 2;
	strInfo_CCM.m_iCnt_Average_Fine_Focus    = 2;
	strInfo_CCM.m_iCnt_Average_Defect        = 2;
	strInfo_CCM.m_iCnt_Average_Opt_Centering = 2;

	m_iSensorID = m_iSensorType = 0;

	m_dSize_CCD_Cell	= 0.0;

	//! White Balance 관련

	m_iSkip_X_gain = 1;
	m_iSkip_Y_gain = 1;
	m_dBorder_X_gain = 0.;
	m_dBorder_Y_gain = 0.;

	//! LPMC-500 Frame Grabber에서 영상을 취득하는 방법
	m_eGrabMethod =LAON_CVT_COLOR;// MIL_BAYER_CVT_COLOR;//norinda

	m_iCnt_Check_SFR = 3;
	m_dMove_Offset_Z = 0.2;
	
	m_iSize_ROI_X = 50;
	m_iSize_ROI_Y = 70;

	m_width = 0;
	m_height = 0;
	m_oc_x = 0;
	m_oc_y = 0;

	m_Tilt_Ty_Only_LR_RL = 0;
	dConti_RadiusLength = 1.0;
	dConti_Angle = 360.0;
	dConti_Speed = 3.0;
	dTwister_Speed = 2.0;
	//
	dRadiusLength = 1.0;	
	dAngle = 360.0;			
	dSpeed = 10.0;
	dSmallSpeed = 5.0;
	dSmallOffTime = 0.0;
	dOnTime = 0.0;			
	dOffTime = 0.0;		
	dAcc = 0.2;
	//
	dCircleSpeed = 0.0;
	dCircleAcc = 0.0;
	dCircleOnTime = 0.0;
	dCircleOffTime = 0.0;

	m_EpoxyBaseP.x = m_EpoxyBaseP.y = 0;
	m_Epoxy2BaseP.x = m_Epoxy2BaseP.y = 0;
	m_dEpoxyOffsetX = m_dEpoxyOffsetY = 0.0;
	m_ContiDownOffset = 1.0;
	m_ResinDrawSize.x = 7.8;
	m_ResinDrawSize.y = 8.5;

	m_CircleDrawCenter[0].x = 10.0;
	m_CircleDrawCenter[0].y = 10.0;
	m_CircleDrawCenter[1].x = 10.0;
	m_CircleDrawCenter[1].y = 10.0;
	m_CircleDrawCenter[2].x = 10.0;
	m_CircleDrawCenter[2].y = 10.0;
	m_CircleDrawCenter[3].x = 10.0;
	m_CircleDrawCenter[3].y = 10.0;
	m_dResinInspOffset[0].x = m_dResinInspOffset[0].y = m_dResinInspOffset[1].x = m_dResinInspOffset[1].y = 0.4;

	m_iResinInspLimit = 20;
	m_dResinInspHoleSpec = 20;		//HOLE 검사 Spec 추가(%)
	m_dResinInspGapLength = 0.06;	//HOLE 연속 끊어진 구간 Spec(mm)

	//KKYH 20150622 날개부분 검사 영역 추가
	m_ResingRectStart[0].x = 0;
	m_ResingRectStart[0].y = 0;
	m_ResingRectSize[0].x =  0;
	m_ResingRectSize[0].y =	 0;
	m_ResingRectStart[1].x = 0;
	m_ResingRectStart[1].y = 0;
	m_ResingRectSize[1].x =  0;
	m_ResingRectSize[1].y =  0;
	m_ResingRectStart[2].x = 0;
	m_ResingRectStart[2].y = 0;
	m_ResingRectSize[2].x =  0;
	m_ResingRectSize[2].y =  0;
	m_ResingRectStart[3].x = 0;
	m_ResingRectStart[3].y = 0;
	m_ResingRectSize[3].x =  0;
	m_ResingRectSize[3].y =  0;
	m_iResinInspRectSpec = 40;
	//--------------------------

	dEpoxyOffset_X = 0.0;
	dEpoxyOffset_Y = 0.0;

	dDisLength[0] = 0.0;
	dDisLength[1] = 0.0;
	dDisLength[2] = 0.0;
	dDisLength[3] = 0.0;
	dDisLength[4] = 0.0;
	dDisLength[5] = 0.0;
	dDisLength[6] = 0.0;
	dDisLength[7] = 0.0;

	dCircleRadiusCenterOffsetX[0] = 0.0;
	dCircleRadiusCenterOffsetX[1] = 0.0;
	dCircleRadiusCenterOffsetX[2] = 0.0;
	dCircleRadiusCenterOffsetX[3] = 0.0;
	dCircleRadiusCenterOffsetY[0] = 0.0;
	dCircleRadiusCenterOffsetY[1] = 0.0;
	dCircleRadiusCenterOffsetY[2] = 0.0;
	dCircleRadiusCenterOffsetY[3] = 0.0;

	dCircleRadiusEndOffsetX[0] = 0.0;
	dCircleRadiusEndOffsetX[1] = 0.0;
	dCircleRadiusEndOffsetX[2] = 0.0;
	dCircleRadiusEndOffsetX[3] = 0.0;
	dCircleRadiusEndOffsetY[0] = 0.0;
	dCircleRadiusEndOffsetY[1] = 0.0;
	dCircleRadiusEndOffsetY[2] = 0.0;
	dCircleRadiusEndOffsetY[3] = 0.0;


	
	/*m_Epoxy_Shot = 0;
	m_Epoxy_Alarm = 0;
	m_Epoxy_Start_Time = 0;
	m_Epoxy_Last_Time = 0;

	m_Socket_Count = 0;
	m_Socket_Alarm = 0;*/

	dEpoxySize = 4.5;
	dEpoxySpeed = 5.0;
	iEpoxyDelay = 500;

	m_ccdArray = 4;
	holderx = 60;//pcb 세타 모터 중심에서 holder중심까지의 거리
	holdery = 6;


	m_Uart_Range1 = 0;
	m_Uart_Range2 = 0;
}

//-----------------------------------------------------------------------------
//
//	ACMIS Dll Spec 로드,저장
//
//-----------------------------------------------------------------------------
void CModelData::AcmisDataLoad()
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szIniIndex[SIZE_OF_100BYTE];
	TCHAR szIniBuff[SIZE_OF_1K];
	CString sToken = _T("");
	int i, j;
	//_ttoi
	//_ttof
	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\%s\\Data\\ACMIS.ini"), AA_MODEL_LOAD_DIR, model.mCurModelName);
	//_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Model\\%s\\ACMIS.ini"), DATA_DIR, modelList.curModelName);

	//-------------------------------------------------------------------------------------------------------------------------------------
	// DefectSpec, stSpecAllOnsemiRCCBSpec
	int DefectMax = sizeof(DEFECT_SPEC_NAME) / sizeof(DEFECT_SPEC_NAME[0]);//20;// 19;int DefectMax = 19;
	for (i = 0; i < DefectMax; i++)
	{
		GetPrivateProfileString(_T("ACMIS_DEFECT"), DEFECT_SPEC_NAME[i], _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		m_DefectSpec[i] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
	}
	GetPrivateProfileString(_T("ACMIS_DEFECT_LIMIT"), _T("defectCount"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	n_DefectCountLimit = _ttoi((TCHAR*)(LPCTSTR)szIniBuff);

	GetPrivateProfileString(_T("ACMIS_DEFECT_LIMIT"), _T("clusterCount"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	n_ClusterCountLimit = _ttoi((TCHAR*)(LPCTSTR)szIniBuff);
	//-------------------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------
	//STAIN

	
	for (i = 0; i < LcbMaxCount; i++)
	{
		GetPrivateProfileString(_T("ACMIS_LCB"), STAIN_LCB_SPEC_NAME[i], _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		m_LcbSpec[i] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
	}
	for (i = 0; i < YmeanMaxCount; i++)
	{
		GetPrivateProfileString(_T("ACMIS_YMEAN"), STAIN_YMEAN_SPEC_NAME[i], _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		m_YmeanSpec[i] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
	}
	for (i = 0; i < FdfMaxCount; i++)
	{
		GetPrivateProfileString(_T("ACMIS_FDF"), STAIN_FDF_SPEC_NAME[i], _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		m_FDFSpec[i] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
	}
	//-------------------------------------------------------------------------------------------------------------------------------------
	//rotate, oc
	//
	int OcMax = 2;
	for (i = 0; i < OcMax; i++)
	{
		GetPrivateProfileString(_T("ACMIS_OC"), OC_SPEC_NAME[i], _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		m_OcSpec[i] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
	}
	//-------------------------------------------------------------------------------------------------------------------------------------
	//Saturation

	int SaturationMax = 36;
	for (i = 0; i < SaturationMax; i++)
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("ROI%d_MIN"), i + 1);
		GetPrivateProfileString(_T("ACMIS_SATURATION"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		m_SaturationMin[i] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
		//
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("ROI%d_MAX"), i + 1);
		GetPrivateProfileString(_T("ACMIS_SATURATION"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		m_SaturationMax[i] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
		//
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("ROI%d_THRESHOLD"), i + 1);
		GetPrivateProfileString(_T("ACMIS_SATURATION"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		m_SaturationThreshold[i] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
	}

	//-------------------------------------------------------------------------------------------------------------------------------------
	//Color Sensitivity
	int ColorMax = 8;
	for (i = 0; i < ColorMax; i++)
	{
		GetPrivateProfileString(_T("ACMIS_COLOR_SENS"), COLOR_SENS_SPEC_NAME[i], _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		m_ColorSensitivitySpec[i] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
	}
	//-------------------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------
	//SNR
	int SnrMax = 3;
	for (i = 0; i < SnrMax; i++)
	{
		GetPrivateProfileString(_T("ACMIS_SNR"), SNR_SPEC_NAME[i], _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		m_SnrSpec[i] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
	}
	//-------------------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------
	//Color Uniform
	int UniformMax = 7;
	for (i = 0; i < UniformMax; i++)
	{
		GetPrivateProfileString(_T("ACMIS_UNIFORMITY"), UNIFORMITY_SPEC_NAME[i], _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		m_UniformSpec[i] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
	}
	
	
	//-------------------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------
	//CHART
	for (i = 0; i < 5; i++)
	{
		GetPrivateProfileString(_T("ACMIS_CHART"), CHART_SPEC_NAME[i], _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		m_ChartSpec[i] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
	}
    //-------------------------------------------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------------------------------------------
    //Relative Illumination 
    int IlluminationMax = 5;
    for (i = 0; i < IlluminationMax; i++)
    {
        GetPrivateProfileString(_T("ACMIS_R_ILLUMINATION"), R_ILLUMINATION_SPEC_NAME[i], _T(""), szIniBuff, sizeof(szIniBuff), szPath);
        m_RIlluminationSpec[i] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
    }
    
    //-------------------------------------------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------
	//RelativeIllumination
	//[ACMIS_RI]

    for (i = 0; i < 8; i++)
    {
        GetPrivateProfileString(_T("ACMIS_RI"), RI_SPEC_NAME[i], _T(""), szIniBuff, sizeof(szIniBuff), szPath);
        m_RISpec[i] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
    }
    //-------------------------------------------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------------------------------------------
    //RelativeIllumination
    //[ACMIS_RI_ROI]  ROI LOAD 1000개  THRESHOLD 400만 UI로 빼면된다.
    //
    int _x = 0;
    int _y = 0;
    //X(Left)	Y(Top)	Width(Right)	Heigh(Bottom)	Threshold_Ch0	Threshold_Ch1	Threshold_Ch2	Threshold_Ch3	Offset	Type
    for (_y = 0; _y < 100; _y++)    //총 100개 항목
    {
        _stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("ROI%d"), _y + 1);
        GetPrivateProfileString(_T("ACMIS_RI_ROI"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
        for (_x = 0; _x < 10; _x++)
        {
            AfxExtractSubString(sToken, szIniBuff, _x, _T('/'));
            m_RirOI[_y][_x] = _ttof((TCHAR*)(LPCTSTR)sToken);
        }
    }
    //-------------------------------------------------------------------------------------------------------------------------------------
	/*GetPrivateProfileString(_T("ACMIS_SATURATION"), SATURATION_SPEC_NAME[0], _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	m_dStaturationMin = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
	GetPrivateProfileString(_T("ACMIS_SATURATION"), SATURATION_SPEC_NAME[1], _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	m_dStaturationMax = _ttof((TCHAR*)(LPCTSTR)szIniBuff);*/

    //-------------------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------
	return;
}
void CModelData::AcmisDataSave()
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szData[SIZE_OF_1K];
	TCHAR szIniBuff[SIZE_OF_1K];
    TCHAR szIniIndex[SIZE_OF_100BYTE];
	int nPosi = 0;
	int i = 0, j = 0;

	//this->CopyBackup(szModelName);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\%s\\Data\\ACMIS.ini"), AA_MODEL_LOAD_DIR, model.mCurModelName);
	//_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Model\\%s\\ACMIS.ini"), DATA_DIR, modelList.curModelName);

	//-------------------------------------------------------------------------------------------------------------------------------------
	// DefectSpec, stSpecAllOnsemiRCCBSpec
	int DefectMax = sizeof(DEFECT_SPEC_NAME) / sizeof(DEFECT_SPEC_NAME[0]);//20;// 19;int DefectMax = 19;
	for (i = 0; i < DefectMax; i++)
	{
		_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_DefectSpec[i]);
		WritePrivateProfileString(_T("ACMIS_DEFECT"), DEFECT_SPEC_NAME[i], szData, szPath);
	}
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), n_DefectCountLimit);
	WritePrivateProfileString(_T("ACMIS_DEFECT_LIMIT"), _T("defectCount"), szData, szPath);
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), n_ClusterCountLimit);
	WritePrivateProfileString(_T("ACMIS_DEFECT_LIMIT"), _T("clusterCount"), szData, szPath);

	//-------------------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------
	//stain
	
	//
	for (i = 0; i < LcbMaxCount; i++)
	{
		_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_LcbSpec[i]);
		WritePrivateProfileString(_T("ACMIS_LCB"), STAIN_LCB_SPEC_NAME[i], szData, szPath);
	}
	//
	for (i = 0; i < YmeanMaxCount; i++)
	{
		_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_YmeanSpec[i]);
		WritePrivateProfileString(_T("ACMIS_YMEAN"), STAIN_YMEAN_SPEC_NAME[i], szData, szPath);
	}
	for (i = 0; i < FdfMaxCount; i++)
	{
		_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_FDFSpec[i]);
		WritePrivateProfileString(_T("ACMIS_FDF"), STAIN_FDF_SPEC_NAME[i], szData, szPath);
	}
	//-------------------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------
	//fov, distortion, rotate
	//m_FovSpec
	int OCMax = 2;
	for (i = 0; i < OCMax; i++)
	{
		_stprintf_s(szData, SIZE_OF_1K, _T("%.01lf"), m_OcSpec[i]);
		WritePrivateProfileString(_T("ACMIS_OC"), OC_SPEC_NAME[i], szData, szPath);
	}
	//-------------------------------------------------------------------------------------------------------------------------------------
	//Saturation
	int SaturationMax = 36;
	for (i = 0; i < SaturationMax; i++)
	{

		_stprintf_s(szData, SIZE_OF_1K, _T("%.01lf"), m_SaturationMin[i]);
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("ROI%d_MIN"), i + 1);
		WritePrivateProfileString(_T("ACMIS_SATURATION"), szIniIndex, szData, szPath);

		_stprintf_s(szData, SIZE_OF_1K, _T("%.01lf"), m_SaturationMax[i]);
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("ROI%d_MAX"), i + 1);
		WritePrivateProfileString(_T("ACMIS_SATURATION"), szIniIndex, szData, szPath);

		_stprintf_s(szData, SIZE_OF_1K, _T("%.01lf"), m_SaturationThreshold[i]);
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("ROI%d_THRESHOLD"), i + 1);
		WritePrivateProfileString(_T("ACMIS_SATURATION"), szIniIndex, szData, szPath);
	}
	/*
	

	int SaturationMax = 36;
	for (i = 0; i < SaturationMax; i++)
	{
	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("ROI%d_MIN"), i + 1);
	GetPrivateProfileString(_T("ACMIS_SATURATION"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	m_SaturationMin[i] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
	//
	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("ROI%d_MAX"), i + 1);
	GetPrivateProfileString(_T("ACMIS_SATURATION"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	m_SaturationMax[i] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
	//
	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("ROI%d_THRESHOLD"), i + 1);
	GetPrivateProfileString(_T("ACMIS_SATURATION"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	m_SaturationThreshold[i] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
	}*/
	//-------------------------------------------------------------------------------------------------------------------------------------
	// Color Sensitivity
	int ColorMax = 8;
	for (i = 0; i < ColorMax; i++)
	{
		_stprintf_s(szData, SIZE_OF_1K, _T("%.01lf"), m_ColorSensitivitySpec[i]);
		WritePrivateProfileString(_T("ACMIS_COLOR_SENS"), COLOR_SENS_SPEC_NAME[i], szData, szPath);
	}
	//-------------------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------
	// SNR
	int SnrMax = 3;
	for (i = 0; i < SnrMax; i++)
	{
		_stprintf_s(szData, SIZE_OF_1K, _T("%.01lf"), m_SnrSpec[i]);
		WritePrivateProfileString(_T("ACMIS_SNR"), SNR_SPEC_NAME[i], szData, szPath);
	}


	//-------------------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------
	//Uniform
	int UniformMax = 7;
	for (i = 0; i < UniformMax; i++)
	{
		_stprintf_s(szData, SIZE_OF_1K, _T("%.01lf"), m_UniformSpec[i]);
		WritePrivateProfileString(_T("ACMIS_UNIFORMITY"), UNIFORMITY_SPEC_NAME[i], szData, szPath);
	}
	//-------------------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------
	//Relative Illumination 
	int IlluminationMax = 5;
	for (i = 0; i < IlluminationMax; i++)
	{
		_stprintf_s(szData, SIZE_OF_1K, _T("%.01lf"), m_RIlluminationSpec[i]);
		WritePrivateProfileString(_T("ACMIS_R_ILLUMINATION"), R_ILLUMINATION_SPEC_NAME[i], szData, szPath);
	}

	
	//-------------------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------
	//Chart
	for (i = 0; i < 5; i++)
	{
		_stprintf_s(szData, SIZE_OF_1K, _T("%.01lf"), m_ChartSpec[i]);
		WritePrivateProfileString(_T("ACMIS_CHART"), CHART_SPEC_NAME[i], szData, szPath);
	}
	//-------------------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------
	//RelativeIllumination
	//[ACMIS_RI]
	
    /*for (i = 0; i < 6; i++)
    {
        GetPrivateProfileString(_T("ACMIS_RI"), RI_SPEC_NAME[i], _T(""), szIniBuff, sizeof(szIniBuff), szPath);
        m_RISpec[i] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
    }*/
    for (i = 0; i < 8; i++)
    {
        _stprintf_s(szData, SIZE_OF_1K, _T("%.01lf"), m_RISpec[i]);
        WritePrivateProfileString(_T("ACMIS_RI"), RI_SPEC_NAME[i], szData, szPath);
    }
    //-------------------------------------------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------------------------------------------
    //RI THRESHOLD SPEC
    int _y = 0;
    int _x = 0;
    for (_y = 0; _y < 100; _y++)    //총 100개 항목
    {
        nPosi = 0;
        for (_x = 0; _x < 10; _x++)
        {
            _stprintf_s(&szIniBuff[nPosi], (SIZE_OF_1K - nPosi), _T("%.03lf / "), m_RirOI[_y][_x]);
            nPosi = (int)(_tcslen(szIniBuff));
        }
        _stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("ROI%d"), _y + 1);
        WritePrivateProfileString(_T("ACMIS_RI_ROI"), szIniIndex, szIniBuff, szPath);
    }
    //-------------------------------------------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------------------------------------------
	
	/*_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_dStaturationMin);
	WritePrivateProfileString(_T("ACMIS_SATURATION"), SATURATION_SPEC_NAME[0], szData, szPath);
	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_dStaturationMax);
	WritePrivateProfileString(_T("ACMIS_SATURATION"), SATURATION_SPEC_NAME[1], szData, szPath);*/
	//---------

}
void CModelData::ChartSave()
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szData[SIZE_OF_1K];
	TCHAR szIniIndex[SIZE_OF_100BYTE];
	TCHAR szIniBuff[SIZE_OF_1K];
	CString sToken = _T("");
	int i, j;
	int nPosi = 0;
	CFileFind clFinder;
	if (clFinder.FindFile(AA_MODEL_LOAD_DIR) == FALSE)
	{
		CreateDirectory(AA_MODEL_LOAD_DIR, NULL);
	}

	
	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\%s\\Data\\ChartData.ini"), AA_MODEL_LOAD_DIR, model.mCurModelName);


	if (mGlobalChartCount < 5)
	{
		mGlobalChartCount = 5;
	}
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), mGlobalChartCount);
	WritePrivateProfileString(_T("CHART"), _T("COUNT"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), mGlobalChartType);
	WritePrivateProfileString(_T("CHART"), _T("TYPE"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), mGlobalChartFind);
	WritePrivateProfileString(_T("CHART"), _T("FIND"), szData, szPath);
	
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_dDemosaic);
	WritePrivateProfileString(_T("CHART"), _T("DEMOSAIC"), szData, szPath);
	
	
	//
	
	nPosi = 0;
	for (i = 0; i < 5; i++)
	{
		_stprintf_s(&szData[nPosi], (SIZE_OF_1K - nPosi), _T("%d /"), sfrElem.m_AATiltRoiIndex[i]);
		nPosi = (int)_tcslen(szData);
	}
	szData[nPosi - 1] = NULL;// 마지막 /는 뺀다.
	WritePrivateProfileString(_T("TILT_CAL"), _T("ROIBOX"), szData, szPath);

	for (i = 0; i < COMMON_LAST_MARK_CNT; i++)
	{
		_stprintf_s(szData, SIZE_OF_1K, _T("%d / %d / %d / %d"), sfrElem.m_SfrTestUse[i][0], sfrElem.m_SfrTestUse[i][1], sfrElem.m_SfrTestUse[i][2], sfrElem.m_SfrTestUse[i][3]);
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("ROI%d"), i);
		WritePrivateProfileString(_T("ROIUSE"), szIniIndex, szData, szPath);
	}
	for (i = 0; i < COMMON_LAST_MARK_CNT; i++)
	{
		_stprintf_s(szData, SIZE_OF_1K, _T("%d / %d / %d / %d"), sfrElem.m_AATiltCalRoi[i][0], sfrElem.m_AATiltCalRoi[i][1], sfrElem.m_AATiltCalRoi[i][2], sfrElem.m_AATiltCalRoi[i][3]);
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("ROI%d"), i);
		WritePrivateProfileString(_T("TILT_CAL"), szIniIndex, szData, szPath);
	}
	

	nPosi = 0;
	for (i = 0; i < COMMON_LAST_MARK_CNT; i++)
	{
		_stprintf_s(&szData[nPosi], (SIZE_OF_1K - nPosi), _T("%d /"), sfrElem.m_iOffsetX[i]);
		nPosi = (int)_tcslen(szData);
	}
	szData[nPosi - 1] = NULL;// 마지막 /는 뺀다.
	WritePrivateProfileString(_T("SFR"), _T("SFR_OFFSET_X"), szData, szPath);

	nPosi = 0;
	for (i = 0; i < COMMON_LAST_MARK_CNT; i++)
	{
		_stprintf_s(&szData[nPosi], (SIZE_OF_1K - nPosi), _T("%d /"), sfrElem.m_iOffsetY[i]);
		nPosi = (int)_tcslen(szData);
	}
	szData[nPosi - 1] = NULL;// 마지막 /는 뺀다.
	WritePrivateProfileString(_T("SFR"), _T("SFR_OFFSET_Y"), szData, szPath);

	nPosi = 0;
	for (i = 0; i < COMMON_LAST_MARK_CNT; i++)
	{
		_stprintf_s(&szData[nPosi], (SIZE_OF_1K - nPosi), _T("%d /"), abs(sfrElem.m_iSizeX[i]));
		nPosi = (int)_tcslen(szData);
	}
	szData[nPosi - 1] = NULL;// 마지막 /는 뺀다.
	WritePrivateProfileString(_T("SFR"), _T("SFR_SIZE_X"), szData, szPath);
	nPosi = 0;
	for (i = 0; i < COMMON_LAST_MARK_CNT; i++)
	{
		_stprintf_s(&szData[nPosi], (SIZE_OF_1K - nPosi), _T("%d /"), abs(sfrElem.m_iSizeY[i]));
		nPosi = (int)_tcslen(szData);
	}
	szData[nPosi - 1] = NULL;// 마지막 /는 뺀다.
	WritePrivateProfileString(_T("SFR"), _T("SFR_SIZE_Y"), szData, szPath);




	nPosi = 0;
	for (i = 0; i < COMMON_LAST_MARK_CNT; i++)
	{
		_stprintf_s(&szData[nPosi], (SIZE_OF_1K - nPosi), _T("%d /"), model.m_FieldPattern_Pos[i].x);
		nPosi = (int)_tcslen(szData);
	}
	szData[nPosi - 1] = NULL;// 마지막 /는 뺀다.
	WritePrivateProfileString(_T("SFR"), _T("FIELD_PATTERN_POS_X"), szData, szPath);
	nPosi = 0;
	for (i = 0; i < COMMON_LAST_MARK_CNT; i++)
	{
		_stprintf_s(&szData[nPosi], (SIZE_OF_1K - nPosi), _T("%d /"), model.m_FieldPattern_Pos[i].y);
		nPosi = (int)_tcslen(szData);
	}
	szData[nPosi - 1] = NULL;// 마지막 /는 뺀다.
	WritePrivateProfileString(_T("SFR"), _T("FIELD_PATTERN_POS_Y"), szData, szPath);
	nPosi = 0;
	for (i = 0; i < COMMON_LAST_MARK_CNT; i++)
	{
		_stprintf_s(&szData[nPosi], (SIZE_OF_1K - nPosi), _T("%d /"), model.m_FieldPattern_Size[i].x);
		nPosi = (int)_tcslen(szData);
	}
	szData[nPosi - 1] = NULL;// 마지막 /는 뺀다.
	WritePrivateProfileString(_T("SFR"), _T("FIELD_PATTERN_SIZE_X"), szData, szPath);
	nPosi = 0;
	for (i = 0; i < COMMON_LAST_MARK_CNT; i++)
	{
		_stprintf_s(&szData[nPosi], (SIZE_OF_1K - nPosi), _T("%d /"), model.m_FieldPattern_Size[i].y);
		nPosi = (int)_tcslen(szData);
	}
	szData[nPosi - 1] = NULL;// 마지막 /는 뺀다.
	WritePrivateProfileString(_T("SFR"), _T("FIELD_PATTERN_SIZE_Y"), szData, szPath);



	nPosi = 0;
	for (i = 0; i < COMMON_MTF_INSP_CNT; i++)
	{
		_stprintf_s(&szData[nPosi], (SIZE_OF_1K - nPosi), _T("%d /"), model.m_MTF_ROI_Pos[i].x);
		nPosi = (int)_tcslen(szData);
	}
	szData[nPosi - 1] = NULL;// 마지막 /는 뺀다.
	WritePrivateProfileString(_T("SFR"), _T("MTF_ROI_POS_X"), szData, szPath);
	//
	nPosi = 0;
	for (i = 0; i < COMMON_MTF_INSP_CNT; i++)
	{
		_stprintf_s(&szData[nPosi], (SIZE_OF_1K - nPosi), _T("%d /"), model.m_MTF_ROI_Pos[i].y);
		nPosi = (int)_tcslen(szData);
	}
	szData[nPosi - 1] = NULL;// 마지막 /는 뺀다.
	WritePrivateProfileString(_T("SFR"), _T("MTF_ROI_POS_Y"), szData, szPath);


	nPosi = 0;
	for (i = 0; i < COMMON_MTF_INSP_CNT; i++)
	{
		_stprintf_s(&szData[nPosi], (SIZE_OF_1K - nPosi), _T("%d /"), model.m_MTF_Direction[i]); 
		nPosi = (int)_tcslen(szData);
	}
	szData[nPosi - 1] = NULL;// 마지막 /는 뺀다.
	WritePrivateProfileString(_T("SFR"), _T("MTF_DIRECTION"), szData, szPath);
	

	//원형마크
	nPosi = 0;
	for (i = 0; i < 4; i++)
	{
		_stprintf_s(&szData[nPosi], (SIZE_OF_1K - nPosi), _T("%d /"), sfrElem.m_CircleP[i].x);
		nPosi = (int)_tcslen(szData);
	}
	szData[nPosi - 1] = NULL;// 마지막 /는 뺀다.
	WritePrivateProfileString(_T("CIRCLE"), _T("CIRCLE_POS_X"), szData, szPath);
	//
	nPosi = 0;
	for (i = 0; i < 4; i++)
	{
		_stprintf_s(&szData[nPosi], (SIZE_OF_1K - nPosi), _T("%d /"), sfrElem.m_CircleP[i].y);
		nPosi = (int)_tcslen(szData);
	}
	szData[nPosi - 1] = NULL;// 마지막 /는 뺀다.
	WritePrivateProfileString(_T("CIRCLE"), _T("CIRCLE_POS_Y"), szData, szPath);

	//
	//
	nPosi = 0;
	for (i = 0; i < 4; i++)
	{
		_stprintf_s(&szData[nPosi], (SIZE_OF_1K - nPosi), _T("%d /"), sfrElem.m_CircleRoi[i].left);
		nPosi = (int)_tcslen(szData);
	}
	szData[nPosi - 1] = NULL;// 마지막 /는 뺀다.
	WritePrivateProfileString(_T("CIRCLE"), _T("CIRCLE_ROI_LEFT"), szData, szPath);
	//
	nPosi = 0;
	for (i = 0; i < 4; i++)
	{
		_stprintf_s(&szData[nPosi], (SIZE_OF_1K - nPosi), _T("%d /"), sfrElem.m_CircleRoi[i].top);
		nPosi = (int)_tcslen(szData);
	}
	szData[nPosi - 1] = NULL;// 마지막 /는 뺀다.
	WritePrivateProfileString(_T("CIRCLE"), _T("CIRCLE_ROI_TOP"), szData, szPath);
	//
	nPosi = 0;
	for (i = 0; i < 4; i++)
	{
		_stprintf_s(&szData[nPosi], (SIZE_OF_1K - nPosi), _T("%d /"), sfrElem.m_CircleRoi[i].right);
		nPosi = (int)_tcslen(szData);
	}
	szData[nPosi - 1] = NULL;// 마지막 /는 뺀다.
	WritePrivateProfileString(_T("CIRCLE"), _T("CIRCLE_ROI_RIGHT"), szData, szPath);
	//
	nPosi = 0;
	for (i = 0; i < 4; i++)
	{
		_stprintf_s(&szData[nPosi], (SIZE_OF_1K - nPosi), _T("%d /"), sfrElem.m_CircleRoi[i].bottom);
		nPosi = (int)_tcslen(szData);
	} 
	szData[nPosi - 1] = NULL;// 마지막 /는 뺀다.
	WritePrivateProfileString(_T("CIRCLE"), _T("CIRCLE_ROI_BOTTOM"), szData, szPath);

	//패턴 개수 * 4 ( T = 0 , B = 1 , L = 2 , R = 3) 순서
	
	
	
	sToken.Empty();
}
void CModelData::ChartLoad()
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szIniIndex[SIZE_OF_100BYTE];
	TCHAR szIniBuff[SIZE_OF_1K];
	CString sToken = _T("");
	int i, j, k;

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\%s\\Data\\ChartData.ini"), AA_MODEL_LOAD_DIR, mCurModelName);




	mGlobalChartCount = GetPrivateProfileInt(_T("CHART"), _T("COUNT"), 0, szPath);
	if (mGlobalChartCount < 5)
	{
		mGlobalChartCount = 5;
	}
	mGlobalChartType = GetPrivateProfileInt(_T("CHART"), _T("TYPE"), 0, szPath);
	mGlobalChartFind = GetPrivateProfileInt(_T("CHART"), _T("FIND"), 0, szPath);
	m_dDemosaic = GetPrivateProfileInt(_T("CHART"), _T("DEMOSAIC"), 0, szPath);

	switch (m_dDemosaic)
	{
	case 0:
		gMIUDevice.dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_NONE; break;
	case 1:
		gMIUDevice.dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_GRADIENT; break;
	case 2:
		gMIUDevice.dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_BL33; break;
	case 3:
		gMIUDevice.dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_OPENCV_VNG; break;
	case 4:
		gMIUDevice.dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_VNG; break;
	case 5:
		gMIUDevice.dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_GR_ONLY; break;
	case 6:
		gMIUDevice.dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_GB_ONLY; break;
	case 7:
		gMIUDevice.dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_GBTF; break;
	case 8:
		gMIUDevice.dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_BLLC; break;
	case 9:
		gMIUDevice.dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_RESIDUAL; break;
	case 10:
		gMIUDevice.dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_BAYER_Y; break;
	case 11:
		gMIUDevice.dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_GRADIENT_RESIDUAL; break;
	case 12:
		gMIUDevice.dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_GBTF_RESIDUAL; break;
	case 13:
		gMIUDevice.dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_RESIDUAL_RESIDUAL; break;
	case 14:
		gMIUDevice.dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_BL33_RESIDUAL; break;
	case 15:
		gMIUDevice.dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_IR_ONLY; break;
	case 16:
		gMIUDevice.dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_GRADIENT_G_ONLY; break;
	case 17:
		gMIUDevice.dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_GBTF_G_ONLY; break;
	case 18:
		gMIUDevice.dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_RESIDUAL_G_ONLY; break;
	case 19:
		gMIUDevice.dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_BL33_G_ONLY; break;
	case 20:
		gMIUDevice.dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_GRADIENT_IR_ONLY; break;
	case 21:
		gMIUDevice.dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_GBTF_IR_ONLY; break;
	case 22:
		gMIUDevice.dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_RESIDUAL_IR_ONLY; break;
	case 23:
		gMIUDevice.dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_BL33_IR_ONLY; break;
	default:
		gMIUDevice.dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_NONE; break;
		break;
	}

	mGlobalSmallChartCount = 0; 
		for (i = 0; i < mGlobalChartCount; i++)//for (i = 0; i < COMMON_LAST_MARK_CNT; i++)
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("ROI%d"), i);
		GetPrivateProfileString(_T("ROIUSE"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		for (j = 0; j < 4; j++)
		{
			AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
			switch (j)
			{
			case 0:		sfrElem.m_SfrTestUse[i][0] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
			case 1:		sfrElem.m_SfrTestUse[i][1] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
			case 2:		sfrElem.m_SfrTestUse[i][2] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
			case 3:		sfrElem.m_SfrTestUse[i][3] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
			}

			if (sfrElem.m_SfrTestUse[i][j] == 1)
			{
				mGlobalSmallChartCount++;
			}
		}
	}
	GetPrivateProfileString(_T("TILT_CAL"), _T("ROIBOX"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (i = 0; i < 5; i++)
	{
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		sfrElem.m_AATiltRoiIndex[i] = _ttoi((TCHAR*)(LPCTSTR)sToken);
	}
	for (i = 0; i < COMMON_LAST_MARK_CNT; i++)
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("ROI%d"), i);
		GetPrivateProfileString(_T("TILT_CAL"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		for (j = 0; j < 4; j++)
		{
			AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
			switch (j)
			{
			case 0:		sfrElem.m_AATiltCalRoi[i][0] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
			case 1:		sfrElem.m_AATiltCalRoi[i][1] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
			case 2:		sfrElem.m_AATiltCalRoi[i][2] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
			case 3:		sfrElem.m_AATiltCalRoi[i][3] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
			}
		}
	}
	

	GetPrivateProfileString(_T("SFR"), _T("SFR_OFFSET_X"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (i = 0; i < COMMON_LAST_MARK_CNT; i++)
	{
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		sfrElem.m_iOffsetX[i] = _ttoi((TCHAR*)(LPCTSTR)sToken);
	}
	GetPrivateProfileString(_T("SFR"), _T("SFR_OFFSET_Y"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (i = 0; i < COMMON_LAST_MARK_CNT; i++)
	{
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		sfrElem.m_iOffsetY[i] = _ttoi((TCHAR*)(LPCTSTR)sToken);
	}

	GetPrivateProfileString(_T("SFR"), _T("SFR_SIZE_X"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (i = 0; i < COMMON_LAST_MARK_CNT; i++)
	{
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		sfrElem.m_iSizeX[i] = _ttoi((TCHAR*)(LPCTSTR)sToken);
	}
	GetPrivateProfileString(_T("SFR"), _T("SFR_SIZE_Y"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (i = 0; i < COMMON_LAST_MARK_CNT; i++)
	{
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		sfrElem.m_iSizeY[i] = _ttoi((TCHAR*)(LPCTSTR)sToken);
	}




	GetPrivateProfileString(_T("SFR"), _T("FIELD_PATTERN_POS_X"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (i = 0; i < COMMON_LAST_MARK_CNT; i++)
	{
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		model.m_FieldPattern_Pos[i].x = _ttoi((TCHAR*)(LPCTSTR)sToken);
	}
	GetPrivateProfileString(_T("SFR"), _T("FIELD_PATTERN_POS_Y"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (i = 0; i < COMMON_LAST_MARK_CNT; i++)
	{
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		model.m_FieldPattern_Pos[i].y = _ttoi((TCHAR*)(LPCTSTR)sToken);
	}
	GetPrivateProfileString(_T("SFR"), _T("FIELD_PATTERN_SIZE_X"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (i = 0; i < COMMON_LAST_MARK_CNT; i++)
	{
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		model.m_FieldPattern_Size[i].x = _ttoi((TCHAR*)(LPCTSTR)sToken);
	}
	GetPrivateProfileString(_T("SFR"), _T("FIELD_PATTERN_SIZE_Y"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (i = 0; i < COMMON_LAST_MARK_CNT; i++)
	{
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		model.m_FieldPattern_Size[i].y = _ttoi((TCHAR*)(LPCTSTR)sToken);
	}
	




	GetPrivateProfileString(_T("SFR"), _T("MTF_ROI_POS_X"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (i = 0; i < COMMON_MTF_INSP_CNT; i++)
	{
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		model.m_MTF_ROI_Pos[i].x = _ttoi((TCHAR*)(LPCTSTR)sToken);
	}
	GetPrivateProfileString(_T("SFR"), _T("MTF_ROI_POS_Y"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (i = 0; i < COMMON_MTF_INSP_CNT; i++)
	{
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		model.m_MTF_ROI_Pos[i].y = _ttoi((TCHAR*)(LPCTSTR)sToken);
	}


	GetPrivateProfileString(_T("SFR"), _T("MTF_DIRECTION"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (i = 0; i < COMMON_MTF_INSP_CNT; i++)
	{
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		model.m_MTF_Direction[i] = _ttoi((TCHAR*)(LPCTSTR)sToken);
	}
	
	//CIRCLE_POS_X
	GetPrivateProfileString(_T("CIRCLE"), _T("CIRCLE_POS_X"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (i = 0; i < 4; i++)
	{
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		sfrElem.m_CircleP[i].x = _ttoi((TCHAR*)(LPCTSTR)sToken);
	}
	GetPrivateProfileString(_T("CIRCLE"), _T("CIRCLE_POS_Y"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (i = 0; i < 4; i++)
	{
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		sfrElem.m_CircleP[i].y = _ttoi((TCHAR*)(LPCTSTR)sToken);
	}
	//
	GetPrivateProfileString(_T("CIRCLE"), _T("CIRCLE_ROI_LEFT"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (i = 0; i < 4; i++)
	{
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		sfrElem.m_CircleRoi[i].left = _ttoi((TCHAR*)(LPCTSTR)sToken);
	}
	GetPrivateProfileString(_T("CIRCLE"), _T("CIRCLE_ROI_TOP"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (i = 0; i < 4; i++)
	{
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		sfrElem.m_CircleRoi[i].top = _ttoi((TCHAR*)(LPCTSTR)sToken);
	}
	GetPrivateProfileString(_T("CIRCLE"), _T("CIRCLE_ROI_RIGHT"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (i = 0; i < 4; i++)
	{
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		sfrElem.m_CircleRoi[i].right = _ttoi((TCHAR*)(LPCTSTR)sToken);
	}
	GetPrivateProfileString(_T("CIRCLE"), _T("CIRCLE_ROI_BOTTOM"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (i = 0; i < 4; i++)
	{
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		sfrElem.m_CircleRoi[i].bottom = _ttoi((TCHAR*)(LPCTSTR)sToken);
	}
	//
	//
	//
	//
	//
	sToken.Empty();

	for (int i = 0; i<model.mGlobalChartCount; i++)//for (int i = 0; i<LAST_MARK_CNT; i++)
	{
		model.m_FieldBox[i].left = sfrElem.m_iOffsetX[i];
		model.m_FieldBox[i].top = sfrElem.m_iOffsetY[i];
		model.m_FieldBox[i].right = model.m_FieldBox[i].left + sfrElem.m_iSizeX[i];
		model.m_FieldBox[i].bottom = model.m_FieldBox[i].top + sfrElem.m_iSizeY[i];
	}
}
///////////////////////////////////////////////////////////////////////////////
void CModelData::Save()
{
	ChartSave();
	FILE *out;

	CFileFind finder;
	BOOL IsFind;
	CString FolderName, FolderName_D, backupFolderName_C, backupFolderName_D;
	//CString	backupFolderName; //0114 hyo

	SYSTEMTIME SysTime;
	::GetLocalTime(&SysTime);


	FolderName.Format("%s\\%s\\Data", AA_MODEL_LOAD_DIR, mCurModelName);
	IsFind = finder.FindFile(FolderName);
	if(!IsFind)
	{
		FolderName.Format("%s", BASE_DIR);
		IsFind = finder.FindFile(FolderName);
		if(!IsFind)
			CreateDirectory(FolderName,NULL); 

		FolderName.Format("%s", BASE_AA_MODEL_LOAD_DIR);
		IsFind = finder.FindFile(FolderName);
		if (!IsFind)
			CreateDirectory(FolderName, NULL);

		FolderName.Format("%s", AA_MODEL_LOAD_DIR);
		IsFind = finder.FindFile(FolderName);
		if (!IsFind)
			CreateDirectory(FolderName, NULL);

		FolderName.Format("%s\\%s", AA_MODEL_LOAD_DIR, mCurModelName);
		IsFind = finder.FindFile(FolderName);
		if(!IsFind)
			CreateDirectory(FolderName,NULL); 

		FolderName.Format("%s\\%s\\Data", AA_MODEL_LOAD_DIR, mCurModelName);
		CreateDirectory(FolderName,NULL); 
	}


	backupFolderName_C.Format("%s\\%s\\%04d%02d", AA_BACKUP_LOAD_DIR, mCurModelName, SysTime.wYear, SysTime.wMonth);
	IsFind = finder.FindFile(backupFolderName_C);
	if(!IsFind)
	{
		backupFolderName_C.Format("%s", BASE_AA_MODEL_LOAD_DIR);
		IsFind = finder.FindFile(backupFolderName_C);
		if (!IsFind)
		{
			CreateDirectory(backupFolderName_C, NULL);
		}
		backupFolderName_C.Format("%s", BASE_AA_BACKUP_DIR);
		IsFind = finder.FindFile(backupFolderName_C);
		if (!IsFind)
		{
			CreateDirectory(backupFolderName_C, NULL);
		}

		backupFolderName_C.Format("%s", AA_BACKUP_LOAD_DIR);
		IsFind = finder.FindFile(backupFolderName_C);
		if (!IsFind)
		{
			CreateDirectory(backupFolderName_C, NULL);
		}
		backupFolderName_C.Format("%s\\%s", AA_BACKUP_LOAD_DIR, mCurModelName);
		IsFind = finder.FindFile(backupFolderName_C);
		if (!IsFind)
		{
			CreateDirectory(backupFolderName_C, NULL);
		}

		backupFolderName_C.Format("%s\\%s\\%04d%02d", AA_BACKUP_LOAD_DIR, mCurModelName, SysTime.wYear, SysTime.wMonth);
		CreateDirectory(backupFolderName_C,NULL); 

	}

	finder.Close();

	char	fileName[1000];
	//wsprintf(fileName, "%s\\Model\\%s\\%s.txt", DATA_DIR, modelList.curModelName, modelList.curModelName);
	wsprintf(fileName, "%s\\%s\\Data\\%s.txt", AA_MODEL_LOAD_DIR, mCurModelName, mCurModelName);
	//tmpStr.Format("%s\\%s\\Data", AA_MODEL_LOAD_DIR, modelList.curModelName);
	//wsprintf(fileName, "%s\\Data.txt", tmpStr);
	
	if(fopen_s(&out, fileName,"w"))
	{
		sLangChange.LoadStringA(IDS_STRING789);	//Model Data 저장 실패...
		errMsg2(Task.AutoFlag, sLangChange);
	}
	else
	{
		//fprintf_s(out, "CURRENT_MODEL %s\n",	modelList.curModelName);


		CString TitleStr="";
		
		for(int iNo = 0; iNo  < MAX_POS_NO; iNo++ ) 
		{
			if(iNo==0)			TitleStr = "MOTOR_WAIT_POSITION";
			else if (iNo==1)	TitleStr = "MOTOR_LOADING_POSITION";			// 공급 / 배출 같은 위치에서..
			else if (iNo==2)	TitleStr = "MOTOR_HOLDER_POSITION";
			else if (iNo==3)	TitleStr = "MOTOR_DISPENSE_POSITION";
			else if (iNo==4)	TitleStr = "MOTOR_LENS_POSITION";			
			else if (iNo==5)	TitleStr = "MOTOR_LASER_PCB_POSITION";
			else if (iNo==6)	TitleStr = "MOTOR_LASER_LENS_POSITION";
			else if (iNo==7)	TitleStr = "MOTOR_ALIGN_POSITION";
            else if (iNo == 8)	TitleStr = "MOTOR_BONDING_POSITION";
            else if (iNo == 9)	TitleStr = "MOTOR_DARK_POSITION"; 
            else if (iNo == 10)	TitleStr = "MOTOR_2800K_POSITION";
			else if (iNo == 11)	TitleStr = "MOTOR_6500K_POSITION";
			else if (iNo == 12)	TitleStr = "MOTOR_DEFECT_POSITION";
			else if (iNo == 13)	TitleStr = "MOTOR_PCB_LOADING_POSITION";
			else if (iNo == 14)	TitleStr = "MOTOR_COVER_LOADING_POSITION";
			else if (iNo == 15)	TitleStr = "MOTOR_COVER_UNLOADING_POSITION";
			else if (iNo == 16)	TitleStr = "MOTOR_POINT_DISPENSE_POSITION";
			else if (iNo == 17)	TitleStr = "MOTOR_CONNECT_POSITION";
			else if (iNo == 18)	TitleStr = "MOTOR_CALC_POSITION";
			else if (iNo == 19)	TitleStr = "MOTOR_CLEAN_POSITION";
			else if (iNo == 20)	TitleStr = "MOTOR_INSP_POSITION";
			else if (iNo == 21)	TitleStr = "MOTOR_HOLDER_UV_POSITION";
			else if (iNo == 22)	TitleStr = "MOTOR_CONTI_TAIL_DELAY_POSITION";
			else if (iNo == 23)	TitleStr = "MOTOR_COM_LASER_POSITION";
            else if (iNo == 24)	TitleStr = "MOTOR_CALC2_POSITION";
			else if (iNo == 25)	TitleStr = "MOTOR_COMALIGN_POSITION";
			else if (iNo == 26)	TitleStr = "MOTOR_DISPENSE_POS1";
			else if (iNo == 27)	TitleStr = "MOTOR_DISPENSE_POS2";
			else if (iNo == 28)	TitleStr = "MOTOR_DISPENSE_POS3";
			

			fprintf_s(out, "%s       %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n", TitleStr.GetBuffer(999),
				axis[0].pos[iNo],
				axis[1].pos[iNo], axis[2].pos[iNo], axis[3].pos[iNo], axis[4].pos[iNo], axis[5].pos[iNo],
				axis[6].pos[iNo], axis[7].pos[iNo], axis[8].pos[iNo], axis[9].pos[iNo], axis[10].pos[iNo]

		
			
			);
		}
		TitleStr.Empty();

		fprintf_s(out, "LENS_OK_LIMIT		%lf %lf %lf %lf %lf\n"
			, axis[Motor_Lens_X].m_dLimit_OK, axis[Motor_Lens_Y].m_dLimit_OK, axis[Motor_Lens_Z].m_dLimit_OK
			, axis[Motor_Lens_Xt].m_dLimit_OK, axis[Motor_Lens_Yt].m_dLimit_OK);
		fprintf_s(out, "LENS_ERR_LIMIT		%lf %lf %lf %lf %lf\n"
			, axis[Motor_Lens_X].m_dLimit_Err, axis[Motor_Lens_Y].m_dLimit_Err, axis[Motor_Lens_Z].m_dLimit_Err
			, axis[Motor_Lens_Xt].m_dLimit_Err, axis[Motor_Lens_Yt].m_dLimit_Err);

		fprintf_s(out, "PCB_OK_LIMIT		%lf %lf %lf %lf %lf %lf\n"
			, axis[Motor_PCB_X].m_dLimit_OK, axis[Motor_PCB_Y].m_dLimit_OK, axis[Motor_PCB_TH].m_dLimit_OK, 
			axis[Motor_PCB_Xt].m_dLimit_OK, axis[Motor_PCB_Yt].m_dLimit_OK, axis[Motor_PCB_Z].m_dLimit_OK);
		fprintf_s(out, "PCB_ERR_LIMIT		%lf %lf %lf %lf %lf %lf\n"
			, axis[Motor_PCB_X].m_dLimit_Err, axis[Motor_PCB_Y].m_dLimit_Err, axis[Motor_PCB_TH].m_dLimit_Err
			, axis[Motor_PCB_Xt].m_dLimit_Err, axis[Motor_PCB_Yt].m_dLimit_Err, axis[Motor_PCB_Z].m_dLimit_Err);


		fprintf_s(out, "LENS_MARK_1		%lf %lf %lf %lf %d %d %d\n"
			, m_MarkCenter[0][0].x, m_MarkCenter[0][0].y, m_MarkOrigin[0][0].x, m_MarkOrigin[0][0].y, m_MarkSize[0][0].x, m_MarkSize[0][0].y, m_iLimitRate[0][0]);
		fprintf_s(out, "LENS_MARK_2		%lf %lf %lf %lf %d %d %d\n"
			, m_MarkCenter[0][1].x, m_MarkCenter[0][1].y, m_MarkOrigin[0][1].x, m_MarkOrigin[0][1].y, m_MarkSize[0][1].x, m_MarkSize[0][1].y, m_iLimitRate[0][1]);

		fprintf_s(out, "PCB_MARK_1		%lf %lf %lf %lf %d %d %d\n"
			, m_MarkCenter[1][0].x, m_MarkCenter[1][0].y, m_MarkOrigin[1][0].x, m_MarkOrigin[1][0].y, m_MarkSize[1][0].x, m_MarkSize[1][0].y, m_iLimitRate[1][0]);
		fprintf_s(out, "PCB_MARK_2		%lf %lf %lf %lf %d %d %d\n"
			, m_MarkCenter[1][1].x, m_MarkCenter[1][1].y, m_MarkOrigin[1][1].x, m_MarkOrigin[1][1].y, m_MarkSize[1][1].x, m_MarkSize[1][1].y, m_iLimitRate[1][1]);

		fprintf_s(out, "LENS_DEAD_END_MARK_1		%lf %lf %lf %lf %d %d %d\n"
			, m_MarkCenter[2][0].x, m_MarkCenter[2][0].y, m_MarkOrigin[2][0].x, m_MarkOrigin[2][0].y, m_MarkSize[2][0].x, m_MarkSize[2][0].y, m_iLimitRate[2][0]);
		fprintf_s(out, "LENS_DEAD_END_MARK_2		%lf %lf %lf %lf %d %d %d\n"
			, m_MarkCenter[2][1].x, m_MarkCenter[2][1].y, m_MarkOrigin[2][1].x, m_MarkOrigin[2][1].y, m_MarkSize[2][1].x, m_MarkSize[2][1].y, m_iLimitRate[2][1]);
		fprintf_s(out, "MARK_MATCHING		%d %d %d %d\n"
			, m_MarkMatchingRate[0], m_MarkMatchingRate[1], m_MarkMatchingRate[2], m_MarkMatchingRate[3]);

		fprintf_s(out, "LED		%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", m_iLedValue[0], m_iLedValue[1], m_iLedValue[2], m_iLedValue[3], m_iLedValue[4], m_iLedValue[5], m_iLedValue[6], m_iLedValue[7], m_iLedValue[8], m_iLedValue[9], m_iLedValue[10], m_iLedValue[11], m_iLedValue[12], m_iLedValue[13], m_iLedValue[14], m_iLedValue[15], m_iLedValue[16], m_iLedValue[17], m_iLedValue[18]);
		fprintf_s(out, "OIS_AF		%d %d %lf\n", code1, code2, dFov);
		fprintf_s(out, "UV_Time		 %d\n",  UV_Time);
		fprintf_s(out, "UV_Weight    %lf\n", UV_Weight);
		fprintf_s(out, "UV_Power		 %d\n", UV_Power);
		fprintf_s(out, "AA_Repeat_Count		 %d\n", AARepeatCount);		//AARepeatCount

		fprintf_s(out, "TILT_Weight_Pre    %lf\n", Tilt_Weight_Pre);
		fprintf_s(out, "TILT_Weight_Post    %lf\n", Tilt_Weight_Post);
		
		fprintf_s(out, "TILT_DIRETION_V    %d %d %d %d %d\n", Tilt_Diretion[0], Tilt_Diretion[1], Tilt_Diretion[2], Tilt_Diretion[3], Tilt_Diretion[4]);
		
		
		


		//! ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		fprintf_s(out, "USE_DEFECT_INSP		    %d %d\n",			defect.m_iNgAlarm, defect.m_iNgUnloading);
		fprintf_s(out, "USE_SIZE		        %d %d %d %d %d\n",	defect.m_i_Insp_Flag[0],	defect.m_i_Insp_Flag[1],	defect.m_i_Insp_Flag[2],	defect.m_i_Insp_Flag[3],	defect.m_i_Insp_Flag[4]);
		fprintf_s(out, "SMALL_FILTER_SIZE	    %d %d %d %d %d\n",	defect.m_i_Filter_Size_Small[0],  defect.m_i_Filter_Size_Small[1], defect.m_i_Filter_Size_Small[2], defect.m_i_Filter_Size_Small[3], defect.m_i_Filter_Size_Small[4]);
		fprintf_s(out, "LARGE_FILTER_SIZE	    %d %d %d %d %d\n",	defect.m_i_Filter_Size_Large[0],  defect.m_i_Filter_Size_Large[1], defect.m_i_Filter_Size_Large[2], defect.m_i_Filter_Size_Large[3], defect.m_i_Filter_Size_Large[4]);
		fprintf_s(out, "THRESHOLD		        %f %f %f %f %f\n",	defect.m_f_Threshold[0],     defect.m_f_Threshold[1],    defect.m_f_Threshold[2], defect.m_f_Threshold[3], defect.m_f_Threshold[4]);
		fprintf_s(out, "MIN_SIZE		        %d %d %d %d %d\n",	defect.m_i_Defect_Size_Min[0],       defect.m_i_Defect_Size_Min[1],      defect.m_i_Defect_Size_Min[2], defect.m_i_Defect_Size_Min[3], defect.m_i_Defect_Size_Min[4]);
		fprintf_s(out, "MAX_SIZE		        %d %d %d %d %d\n",	defect.m_i_Defect_Size_Max[0],       defect.m_i_Defect_Size_Max[1],      defect.m_i_Defect_Size_Max[2], defect.m_i_Defect_Size_Max[3], defect.m_i_Defect_Size_Max[4]);
		fprintf_s(out, "GRAY_DIFF		        %f %f %f %f %f\n",	defect.m_f_Gray_diff[0],      defect.m_f_Gray_diff[1],     defect.m_f_Gray_diff[2], defect.m_f_Gray_diff[3], defect.m_f_Gray_diff[4]);
		fprintf_s(out, "BOUNDARY_SKIP		    %d %d %d %d %d\n",	defect.m_i_Skip_Boundary[0],  defect.m_i_Skip_Boundary[1], defect.m_i_Skip_Boundary[2], defect.m_i_Skip_Boundary[3], defect.m_i_Skip_Boundary[4]);
//		fprintf_s(out, "EDGE_SKIP		        %d %d %d %d %d\n",	defect.m_i_Skip_Edge[0],      defect.m_i_Skip_Edge[1],   defect.m_i_Skip_Edge[2],     defect.m_i_Skip_Edge[3], defect.m_i_Skip_Edge[4]);
		fprintf_s(out, "MAX_LIMIT_CNT		    %d %d %d %d %d\n",	defect.m_i_Cnt_Limit[0],   defect.m_i_Cnt_Limit[1],  defect.m_i_Cnt_Limit[2], defect.m_i_Cnt_Limit[3], defect.m_i_Cnt_Limit[4]);
		fprintf_s(out, "SCALE		            %d %d %d %d\n",		defect.m_iSmallScale,         defect.m_iMiddleScale,        defect.m_iLargeScale, defect.m_iEdgeScale);
		//! ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

		fprintf_s(out, "INFO_AF1		%d %d %lf %lf %f\n", strInfo_AF1.m_iDelayTime, strInfo_AF1.m_iStepCnt, strInfo_AF1.m_dMoveDistance, strInfo_AF1.m_dMoveVel, strInfo_AF1.m_fLimit_MTF);
		fprintf_s(out, "INFO_AF2		%d %d %lf %lf\n", strInfo_AF2.m_iDelayTime, strInfo_AF2.m_iStepCnt, strInfo_AF2.m_dMoveDistance, strInfo_AF2.m_dMoveVel);
		fprintf_s(out, "INFO_TILT		%d %d %lf %lf\n", strInfo_Tilt.m_iDelayTime, strInfo_Tilt.m_iStepCnt, strInfo_Tilt.m_dMoveDistance, strInfo_Tilt.m_dMoveVel);

		fprintf_s(out, "INFO_CAM1		%d %d\n", strInfo_Cam[0].m_iDelayTime, strInfo_Cam[0].m_iRetryCnt);
		fprintf_s(out, "INFO_CAM2		%d %d\n", strInfo_Cam[1].m_iDelayTime, strInfo_Cam[1].m_iRetryCnt);
		fprintf_s(out, "INFO_CAM3		%d %d\n", strInfo_Cam[2].m_iDelayTime, strInfo_Cam[2].m_iRetryCnt);
		fprintf_s(out, "INFO_CAM4		%d %d\n", strInfo_Cam[3].m_iDelayTime, strInfo_Cam[3].m_iRetryCnt);

		//! Added by LHW (2013/3/5)
		fprintf_s(out, "CCM_AVERAGE_COUNT		%d %d %d %d %d\n", strInfo_CCM.m_iCnt_Average_Thru_Focus, 
																	strInfo_CCM.m_iCnt_Average_Tilting, 
																	strInfo_CCM.m_iCnt_Average_Fine_Focus, 
																	strInfo_CCM.m_iCnt_Average_Defect, 
																	strInfo_CCM.m_iCnt_Average_Opt_Centering);

		fprintf_s(out, "SENSOR_INFO		%d %d\n", m_iSensorID, m_iSensorType);
		fprintf_s(out, "CCD_CELL_SIZE	%lf\n", m_dSize_CCD_Cell);  
		fprintf_s(out, "CCD_GAIN_SKIP_SIZE	%d %d\n", m_iSkip_X_gain, m_iSkip_Y_gain);
		fprintf_s(out, "CCD_GAIN_BORDER_SIZE	%lf %lf\n", m_dBorder_X_gain, m_dBorder_Y_gain);  
		
		fprintf_s(out, "CCD_GRAB_METHOD		%d\n", m_eGrabMethod);

		fprintf_s(out, "SFR_CHECK_CNT		%d\n", m_iCnt_Check_SFR);
		fprintf_s(out, "MOVE_OFFSET_Z		%lf\n", m_dMove_Offset_Z);

		fprintf_s(out, "SFR_ROI_SIZE		%d %d\n", m_iSize_ROI_X, m_iSize_ROI_Y);
	
		fprintf_s(out, "PCB_Bright_Contrast		%d %d\n", m_iBright[PCB_Holder_MARK], m_iContrast[PCB_Holder_MARK]);
		fprintf_s(out, "LENS_Bright_Contrast	%d %d\n", m_iBright[LENS_Align_MARK], m_iContrast[LENS_Align_MARK]);
		fprintf_s(out, "Chip_Bright_Contrast	%d %d\n", m_iBright[PCB_Chip_MARK], m_iContrast[PCB_Chip_MARK]);
		

		fprintf_s(out, "SIDE_MODEL_CHECK	%d\n", d_SIDE_MODEL_CH);

		fprintf_s(out, "INSP_PCB_TILT		%.02lf %.02lf\n", m_InspPcbTilt[0], m_InspPcbTilt[1]);
		//
		fprintf_s(out, "INPOS_X		%.02lf %.02lf %.02lf\n", m_InPos_X[0],m_InPos_X[1],m_InPos_X[2]);

		fprintf_s(out, "INPOS_Y		%.02lf %.02lf %.02lf\n", m_InPos_Y[0],m_InPos_Y[1],m_InPos_Y[2]);

		fprintf_s(out, "OUTPOS_X		%.02lf %.02lf %.02lf\n", m_OutPos_X[0], m_OutPos_X[1], m_OutPos_X[2]);
		fprintf_s(out, "OUTPOS_Y		%.02lf %.02lf %.02lf\n", m_OutPos_Y[0], m_OutPos_Y[1], m_OutPos_Y[2]);

		fprintf_s(out, "PCB_LASERPOS_X		%.02lf %.02lf %.02lf\n", m_PcbLaserPos_X[0], m_PcbLaserPos_X[1], m_PcbLaserPos_X[2]);
		fprintf_s(out, "PCB_LASERPOS_Y		%.02lf %.02lf %.02lf\n", m_PcbLaserPos_Y[0], m_PcbLaserPos_Y[1], m_PcbLaserPos_Y[2]);

		fprintf_s(out, "DISPENSE_LENGTH		%lf %lf %lf %lf %lf %lf %lf %lf\n", dDisLength[0], dDisLength[1], dDisLength[2], dDisLength[3], dDisLength[4], dDisLength[5], dDisLength[6], dDisLength[7]);
		fprintf_s(out, "CIRCLE_RADIUS_OFFSETX		%lf %lf %lf %lf\n", dCircleRadiusCenterOffsetX[0], dCircleRadiusCenterOffsetX[1], dCircleRadiusCenterOffsetX[2], dCircleRadiusCenterOffsetX[3]);
		fprintf_s(out, "CIRCLE_RADIUS_OFFSETY		%lf %lf %lf %lf\n", dCircleRadiusCenterOffsetY[0], dCircleRadiusCenterOffsetY[1], dCircleRadiusCenterOffsetY[2], dCircleRadiusCenterOffsetY[3]);

		fprintf_s(out, "CIRCLE_END_OFFSETX		%lf %lf %lf %lf\n", dCircleRadiusEndOffsetX[0], dCircleRadiusEndOffsetX[1], dCircleRadiusEndOffsetX[2], dCircleRadiusEndOffsetX[3]);
		fprintf_s(out, "CIRCLE_END_OFFSETY		%lf %lf %lf %lf\n", dCircleRadiusEndOffsetY[0], dCircleRadiusEndOffsetY[1], dCircleRadiusEndOffsetY[2], dCircleRadiusEndOffsetY[3]);

		fprintf_s(out, "EPOXY_DATA		%lf %lf %lf %lf %lf %lf\n",   dSpeed, dAcc, dOnTime, dOffTime, dSmallSpeed, dSmallOffTime);
		fprintf_s(out, "EPOXY_CIRCLE_DATA		%lf %lf %lf %lf %lf %lf %lf %lf\n", dRadiusLength, dAngle, dCircleSpeed, dCircleAcc, dConti_RadiusLength, dConti_Angle, dConti_Speed, dTwister_Speed);

		fprintf_s(out, "EPOXY_LINE		%lf %lf %d\n", dEpoxySize, dEpoxySpeed, iEpoxyDelay);

		fprintf_s(out, "EPOXYINSP_OFFSET		%lf %lf\n",   dEpoxyOffset_X, dEpoxyOffset_Y);
		fprintf_s(out, "EPOXY_BASE_POS		%d %d\n", m_EpoxyBaseP.x, m_EpoxyBaseP.y);
		fprintf_s(out, "EPOXY2_BASE_POS		%d %d\n", m_Epoxy2BaseP.x, m_Epoxy2BaseP.y);
		fprintf_s(out, "EPOXY_OFFSET_POS		%lf %lf\n", m_dEpoxyOffsetX, m_dEpoxyOffsetY);
		fprintf_s(out, "EPOXY2_OFFSET_POS		%lf %lf\n", m_dEpoxy2OffsetX, m_dEpoxy2OffsetY);

		fprintf_s(out, "EPOXY_TABLE_OFFSET_X		%f %f %f %f\n",	model.offset.f_epoxy_x_dispense_offset[0], model.offset.f_epoxy_x_dispense_offset[1],	model.offset.f_epoxy_x_dispense_offset[2], model.offset.f_epoxy_x_dispense_offset[3]);
		fprintf_s(out, "EPOXY_TABLE_OFFSET_Y		%f %f %f %f\n",	model.offset.f_epoxy_y_dispense_offset[0], model.offset.f_epoxy_y_dispense_offset[1],	model.offset.f_epoxy_y_dispense_offset[2], model.offset.f_epoxy_y_dispense_offset[3]);
		fprintf_s(out, "EPOXY_TABLE_OFFSET_Z		%f %f %f %f\n",	model.offset.f_epoxy_z_dispense_offset[0], model.offset.f_epoxy_z_dispense_offset[1],	model.offset.f_epoxy_z_dispense_offset[2], model.offset.f_epoxy_z_dispense_offset[3]);

		fprintf_s(out, "RESIN_DRAW_SIZE   %f %f\n",			m_ResinDrawSize.x, m_ResinDrawSize.y);

		fprintf_s(out, "CIRCLE_DRAW_SIZE_LT	%lf %lf\n", m_CircleDrawSize[0].x, m_CircleDrawSize[0].y);
		fprintf_s(out, "CIRCLE_DRAW_SIZE_RT	%lf %lf\n", m_CircleDrawSize[1].x, m_CircleDrawSize[1].y);
		fprintf_s(out, "CIRCLE_DRAW_SIZE_LB	%lf %lf\n", m_CircleDrawSize[2].x, m_CircleDrawSize[2].y);
		fprintf_s(out, "CIRCLE_DRAW_SIZE_RB	%lf %lf\n", m_CircleDrawSize[3].x, m_CircleDrawSize[3].y);

		fprintf_s(out, "RESIN_DRAW_CENTER	%f %f %f %f %f %f %f %f\n",		m_CircleDrawCenter[0].x, m_CircleDrawCenter[0].y, m_CircleDrawCenter[1].x, m_CircleDrawCenter[1].y, m_CircleDrawCenter[2].x, m_CircleDrawCenter[2].y, m_CircleDrawCenter[3].x, m_CircleDrawCenter[3].y);
		fprintf_s(out, "RESIN_INSP_OFFSET	%f %f %f %f\n",		m_dResinInspOffset[0].x, m_dResinInspOffset[0].y, m_dResinInspOffset[1].x, m_dResinInspOffset[1].y);
		fprintf_s(out, "RESIN_INSP_LIMIT	%d\n", 				m_iResinInspLimit);
		fprintf_s(out, "RESIN_INSP_SPEC	%f %f %f\n", 		m_dResinInspHoleSpec, m_dResinInspGapLength, m_iResinInspRectSpec);	//KKYH 20150622 HOLE 검사 Spec 추가
		fprintf_s(out, "EPOXY_INSP_RECT_LEFT	%d %d %d %d\n",	m_ResingRectStart[0].x, m_ResingRectStart[0].y,	m_ResingRectSize[0].x, m_ResingRectSize[0].y);
		fprintf_s(out, "EPOXY_INSP_RECT_RIGHT	%d %d %d %d\n",	m_ResingRectStart[1].x, m_ResingRectStart[1].y,	m_ResingRectSize[1].x, m_ResingRectSize[1].y);
		fprintf_s(out, "EPOXY_INSP_RECT_TOP		%d %d %d %d\n",	m_ResingRectStart[2].x, m_ResingRectStart[2].y,	m_ResingRectSize[2].x, m_ResingRectSize[2].y);
		fprintf_s(out, "EPOXY_INSP_RECT_BOTTOM	%d %d %d %d\n",	m_ResingRectStart[3].x, m_ResingRectStart[3].y,	m_ResingRectSize[3].x, m_ResingRectSize[3].y);

		fprintf_s(out, "EPOXY_INSP_ANGLE	%f %f %f %f %f %f %f %f\n",	m_ResingStartAngle[0], m_ResingFinishAngle[0],	m_ResingStartAngle[1], m_ResingFinishAngle[1],	m_ResingStartAngle[2], m_ResingFinishAngle[2],	m_ResingStartAngle[3], m_ResingFinishAngle[3]);
		fprintf_s(out, "EPOXY_INSP_COLOR_LEVEL	%d\n",	m_ResingInspLevel);

		fprintf_s(out, "CLEANPAD	%d %lf %lf\n", Cleancnt, Cleanpad[0], Cleanpad[1]);


		
		fprintf_s(out, "DISTORTION_MARK	%d %d %d %d %d %d\n", model.m_DistortionMark_ROI[0].x,model.m_DistortionMark_ROI[0].y, model.m_DistortionMark_ROI[1].x,model.m_DistortionMark_ROI[1].y, model.m_DistortionMark_ROI[2].x,model.m_DistortionMark_ROI[2].y);
		fprintf_s(out, "FIELD_VIEW_MARK	%d %d %d %d\n", model.m_FieldOfView_ROI[0].x,model.m_FieldOfView_ROI[0].y, model.m_FieldOfView_ROI[1].x,model.m_FieldOfView_ROI[1].y);


		fprintf_s(out, "LINE_PULSE	%f %f\n", model.m_Line_Pulse, model.m_Gen2_Line_Pulse);	// Frequency(Line Pulse)
		fprintf_s(out, "TILT_TY_ONLY_LR_RL		%d\n", m_Tilt_Ty_Only_LR_RL);
		fprintf_s(out, "IS_USE_LASER_TILT	%d\n",	model.m_IsUseLaserTilt);	// Laser Tilt 사용 유무

		fprintf_s(out, "IS_USE_DARK_DEFECT_TEST	%d\n",	model.m_IsUseDarkDefectTest);		//
		fprintf_s(out, "IS_USE_BRIGHT_DEFECT_TEST	%d\n",	model.m_IsUseBrightDefectTest);	//
		fprintf_s(out, "IS_USE_STAIN_TEST	%d\n",	model.m_IsUseStainTest);				//
		fprintf_s(out, "IS_DOOR_OPEN_RUNNING	%d\n",	model.m_IsDoorOpenRunning);				//
		fprintf_s(out, "IS_AUTO_Z_SEARCH	%d\n",	model.m_AUTO_Z_SEARCH);				//
		fprintf_s(out, "AUTO_Z_SEARCH_CNT	%d\n",	model.m_AUTO_Z_SEARCH_CNT);				//
		fprintf_s(out, "AUTO_Z_SEARCH_VAL	%f\n",	model.m_AUTO_Z_SEARCH_VAL);				//

		fprintf_s(out, "UART_VALUE		%d %d\n", m_Uart_Range1, m_Uart_Range2);
		fprintf_s(out, "CONTI_DOWN_OFFSET	%lf\n", model.m_ContiDownOffset);
		if(out)	fclose(out);
	}

	for (int i=0 ; i<MARK_CNT ; i++)
	{
		int iCh = 1;
		if(i == PCB_Chip_MARK)	iCh = 0;

		for (int j=0 ; j<2; j++)
		{
			saveMark(iCh, i, j);
		}
	}

	
#ifdef		ON_LINE_MODE
	char	backupName_C[1000];

	wsprintf(backupName_C, "%s\\%s_%04d%02d%02d_%02d%02d.txt", backupFolderName_C, mCurModelName, SysTime.wYear, SysTime.wMonth, SysTime.wDay, SysTime.wHour, SysTime.wMinute);
	::CopyFile(fileName, backupName_C, FALSE);
#endif

}
void CModelData::PatternSave()
{

	
}
void CModelData::PatternLoad()
{
	#ifdef ON_LINE_VISION
	for (int i = 0; i < MARK_CNT; i++)
	{
		int iCh = 1;
		if(i == PCB_Chip_MARK)	iCh = 0;

		for (int j = 0 ; j < 2; j++)
		{
			loadMark(iCh, i, j);
		}
	}

	
	CString strPatDir;

	for (int i = 0; i < model.mGlobalChartCount; i++)//for(int i = 0;i < LAST_MARK_CNT;i++)
	{
		//strPatDir.Format("%s\\Model\\%s\\CHART_Mark_%d-Mask.pat", DATA_DIR, model.mCurModelName, i);
		strPatDir.Format("%s\\%s\\Data\\Mark\\CHART_Mark_%d-Mask.pat", AA_MODEL_LOAD_DIR, model.mCurModelName, i);
		MpatRestore(vision.MilSystem, strPatDir.GetBuffer(999), &vision.FieldPatternImage[i]);
		if (i == 0)
		{
			MpatRestore(vision.MilSystem, strPatDir.GetBuffer(999), &vision.ChartCenterPatternImage);		//loadMark
		}
	}
	strPatDir.Empty();


	#endif
}

void CModelData::RoiSave()
{

    TCHAR szPath[SIZE_OF_1K];
    TCHAR szIniIndex[SIZE_OF_100BYTE];
    TCHAR szData[SIZE_OF_1K];
    int i;

    _stprintf_s(szPath, SIZE_OF_1K, _T("%s\\%s\\Data\\RoiData.ini"), AA_MODEL_LOAD_DIR, model.mCurModelName);


    //------------------------------------------------------------------------------
    //fov
    //------------------------------------------------------------------------------
    for (i = 0; i < MAX_FOV_COUNT; i++)
    {
        // FOV 마크 위치
        _stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("POS%02d"), i + 1);
        _stprintf_s(szData, SIZE_OF_1K, _T("%d / %d"), sfrElem.m_clPtFov[i].x, sfrElem.m_clPtFov[i].y);
        WritePrivateProfileString(_T("FovMark"), szIniIndex, szData, szPath);

        // FOV 마크 영역
        _stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("ROI%02d"), i + 1);
        _stprintf_s(szData, SIZE_OF_1K, _T("%d / %d / %d / %d"), sfrElem.m_clRectFov[i].left,
            sfrElem.m_clRectFov[i].top, sfrElem.m_clRectFov[i].right, sfrElem.m_clRectFov[i].bottom);
        WritePrivateProfileString(_T("FovMark"), szIniIndex, szData, szPath);
    }
    //------------------------------------------------------------------------------
    //snr
    //------------------------------------------------------------------------------
    for (i = 0; i < MAX_SNR_COUNT; i++)
    {
        // SNR 마크 위치
        _stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("POS%02d"), i + 1);
        _stprintf_s(szData, SIZE_OF_1K, _T("%d / %d"), sfrElem.m_clPtSnr[i].x, sfrElem.m_clPtSnr[i].y);
        WritePrivateProfileString(_T("SnrMark"), szIniIndex, szData, szPath);
    }
    for (i = 0; i < 4; i++)
    {
        // SNR 마크 영역
        _stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("ROI%02d"), i + 1);
        _stprintf_s(szData, SIZE_OF_1K, _T("%d / %d / %d / %d"), sfrElem.m_clRectSnr[i].left,
            sfrElem.m_clRectSnr[i].top, sfrElem.m_clRectSnr[i].right, sfrElem.m_clRectSnr[i].bottom);
        WritePrivateProfileString(_T("SnrMark"), szIniIndex, szData, szPath);
    }

}

void CModelData::RoiLoad()
{
    TCHAR szPath[SIZE_OF_1K];
    TCHAR szIniIndex[SIZE_OF_100BYTE];
    TCHAR szIniBuff[SIZE_OF_1K];
    CString sToken = _T("");
    int i, j;



	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\%s\\Data\\RoiData.ini"), AA_MODEL_LOAD_DIR, modelList.curModelName);
    //_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\RoiData.ini"), DATA_DIR);
    //------------------------------------------------------------------------------
    //fov
    //------------------------------------------------------------------------------
    for (i = 0; i < MAX_FOV_COUNT; i++)
    {
        // fov 마크 위치
        _stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("POS%02d"), i + 1);
        GetPrivateProfileString(_T("FovMark"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
        for (j = 0; j < 2; j++)
        {
            AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
            switch (j)
            {
            case 0:		sfrElem.m_clPtFov[i].x = _ttoi((TCHAR*)(LPCTSTR)sToken);		break;
            case 1:		sfrElem.m_clPtFov[i].y = _ttoi((TCHAR*)(LPCTSTR)sToken);		break;
            }
        }


        // fov 마크 영역
        _stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("ROI%02d"), i + 1);
        GetPrivateProfileString(_T("FovMark"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
        for (j = 0; j < 4; j++)
        {
            AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
            switch (j)
            {
            case 0:		sfrElem.m_clRectFov[i].left = _ttoi((TCHAR*)(LPCTSTR)sToken);	break;
            case 1:		sfrElem.m_clRectFov[i].top = _ttoi((TCHAR*)(LPCTSTR)sToken);	break;
            case 2:		sfrElem.m_clRectFov[i].right = _ttoi((TCHAR*)(LPCTSTR)sToken);	break;
            case 3:		sfrElem.m_clRectFov[i].bottom = _ttoi((TCHAR*)(LPCTSTR)sToken);	break;
            }
        }
    }
    //------------------------------------------------------------------------------
    //snr
    //------------------------------------------------------------------------------
    for (i = 0; i < MAX_SNR_COUNT; i++)
    {
        // snr 마크 위치
        _stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("POS%02d"), i + 1);
        GetPrivateProfileString(_T("SnrMark"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
        for (j = 0; j < 2; j++)
        {
            AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
            switch (j)
            {
            case 0:		sfrElem.m_clPtSnr[i].x = _ttoi((TCHAR*)(LPCTSTR)sToken);		break;
            case 1:		sfrElem.m_clPtSnr[i].y = _ttoi((TCHAR*)(LPCTSTR)sToken);		break;
            }
        }


        // snr 마크 영역
        _stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("ROI%02d"), i + 1);
        GetPrivateProfileString(_T("SnrMark"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
        for (j = 0; j < 4; j++)
        {
            AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
            switch (j)
            {
            case 0:		sfrElem.m_clRectSnr[i].left = _ttoi((TCHAR*)(LPCTSTR)sToken);	break;
            case 1:		sfrElem.m_clRectSnr[i].top = _ttoi((TCHAR*)(LPCTSTR)sToken);	break;
            case 2:		sfrElem.m_clRectSnr[i].right = _ttoi((TCHAR*)(LPCTSTR)sToken);	break;
            case 3:		sfrElem.m_clRectSnr[i].bottom = _ttoi((TCHAR*)(LPCTSTR)sToken);	break;
            }
        }
    }
    //------------------------------------------------------------------------------
    //
    //------------------------------------------------------------------------------
}
void CModelData::Load()
{
	ChartLoad();
	FILE* in;

	CString tmpStr;
	char	fileName[1000];
	char	temp[500];
	//tmpStr.Format("%s\\Model\\%s", DATA_DIR, modelList.curModelName);
	tmpStr.Format("%s\\%s\\Data", AA_MODEL_LOAD_DIR, modelList.curModelName);
	wsprintf(fileName, "%s\\%s.txt", tmpStr, modelList.curModelName);

	if(!fopen_s(&in, fileName,"r"))
	{
		char	Line[500];
		char	Title[500];
		int		nRtn;
		int iArrNo = 0;	//KYH 임시 변수

		while (1)
		{
			fgets(Line, 499, in);
			nRtn = sscanf_s(Line, "%s", &Title, 499);

			if (nRtn==EOF)	
				break;
			else if (strcmp(Title, "MOTOR_WAIT_POSITION") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", Title, 499,
					&axis[0].pos[Wait_Pos], &axis[1].pos[Wait_Pos], &axis[2].pos[Wait_Pos], &axis[3].pos[Wait_Pos], &axis[4].pos[Wait_Pos], &axis[5].pos[Wait_Pos],
					&axis[6].pos[Wait_Pos], &axis[7].pos[Wait_Pos], &axis[8].pos[Wait_Pos], &axis[9].pos[Wait_Pos], &axis[10].pos[Wait_Pos]);//, &axis[11].pos[Wait_Pos]);
			}
			else if (strcmp(Title, "MOTOR_LOADING_POSITION") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", Title, 499,
					&axis[0].pos[Loading_Pos], &axis[1].pos[Loading_Pos], &axis[2].pos[Loading_Pos], &axis[3].pos[Loading_Pos], &axis[4].pos[Loading_Pos], &axis[5].pos[Loading_Pos],
					&axis[6].pos[Loading_Pos], &axis[7].pos[Loading_Pos], &axis[8].pos[Loading_Pos], &axis[9].pos[Loading_Pos], &axis[10].pos[Loading_Pos]);//, &axis[11].pos[Loading_Pos]);
			}
			else if (strcmp(Title, "MOTOR_HOLDER_POSITION") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", Title, 499,
					&axis[0].pos[Holder_Pos], &axis[1].pos[Holder_Pos], &axis[2].pos[Holder_Pos], &axis[3].pos[Holder_Pos], &axis[4].pos[Holder_Pos], &axis[5].pos[Holder_Pos],
					&axis[6].pos[Holder_Pos], &axis[7].pos[Holder_Pos], &axis[8].pos[Holder_Pos], &axis[9].pos[Holder_Pos], &axis[10].pos[Holder_Pos]);//, &axis[11].pos[Holder_Pos]);
			}
			else if (strcmp(Title, "MOTOR_DISPENSE_POSITION") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", Title, 499,
					&axis[0].pos[Dispense_Pos], &axis[1].pos[Dispense_Pos], &axis[2].pos[Dispense_Pos], &axis[3].pos[Dispense_Pos], &axis[4].pos[Dispense_Pos], &axis[5].pos[Dispense_Pos],
					&axis[6].pos[Dispense_Pos], &axis[7].pos[Dispense_Pos], &axis[8].pos[Dispense_Pos], &axis[9].pos[Dispense_Pos], &axis[10].pos[Dispense_Pos]);//, &axis[11].pos[Dispense_Pos]);
			}
			else if (strcmp(Title, "MOTOR_LENS_POSITION") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", Title, 499,
					&axis[0].pos[Lens_Pos], &axis[1].pos[Lens_Pos], &axis[2].pos[Lens_Pos], &axis[3].pos[Lens_Pos], &axis[4].pos[Lens_Pos], &axis[5].pos[Lens_Pos],
					&axis[6].pos[Lens_Pos], &axis[7].pos[Lens_Pos], &axis[8].pos[Lens_Pos], &axis[9].pos[Lens_Pos], &axis[10].pos[Lens_Pos]);//, &axis[11].pos[Lens_Pos]);
			}
			else if (strcmp(Title, "MOTOR_LASER_PCB_POSITION") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", Title, 499,
					&axis[0].pos[Laser_Pcb_Pos], &axis[1].pos[Laser_Pcb_Pos], &axis[2].pos[Laser_Pcb_Pos], &axis[3].pos[Laser_Pcb_Pos], &axis[4].pos[Laser_Pcb_Pos], &axis[5].pos[Laser_Pcb_Pos],
					&axis[6].pos[Laser_Pcb_Pos], &axis[7].pos[Laser_Pcb_Pos], &axis[8].pos[Laser_Pcb_Pos], &axis[9].pos[Laser_Pcb_Pos], &axis[10].pos[Laser_Pcb_Pos]);//, &axis[11].pos[Laser_Pcb_Pos]);
			}
			else if (strcmp(Title, "MOTOR_LASER_LENS_POSITION") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", Title, 499,
					&axis[0].pos[Laser_Lens_Pos], &axis[1].pos[Laser_Lens_Pos], &axis[2].pos[Laser_Lens_Pos], &axis[3].pos[Laser_Lens_Pos], &axis[4].pos[Laser_Lens_Pos], &axis[5].pos[Laser_Lens_Pos],
					&axis[6].pos[Laser_Lens_Pos], &axis[7].pos[Laser_Lens_Pos], &axis[8].pos[Laser_Lens_Pos], &axis[9].pos[Laser_Lens_Pos], &axis[10].pos[Laser_Lens_Pos]);//, &axis[11].pos[Laser_Lens_Pos]);
			}
			else if (strcmp(Title, "MOTOR_ALIGN_POSITION") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", Title, 499,
					&axis[0].pos[Align_Pos], &axis[1].pos[Align_Pos], &axis[2].pos[Align_Pos], &axis[3].pos[Align_Pos], &axis[4].pos[Align_Pos], &axis[5].pos[Align_Pos],
					&axis[6].pos[Align_Pos], &axis[7].pos[Align_Pos], &axis[8].pos[Align_Pos], &axis[9].pos[Align_Pos], &axis[10].pos[Align_Pos]);//, &axis[11].pos[Align_Pos]);
			}
			else if (strcmp(Title, "MOTOR_BONDING_POSITION") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", Title, 499,
					&axis[0].pos[Bonding_Pos], &axis[1].pos[Bonding_Pos], &axis[2].pos[Bonding_Pos], &axis[3].pos[Bonding_Pos], &axis[4].pos[Bonding_Pos], &axis[5].pos[Bonding_Pos],
					&axis[6].pos[Bonding_Pos], &axis[7].pos[Bonding_Pos], &axis[8].pos[Bonding_Pos], &axis[9].pos[Bonding_Pos], &axis[10].pos[Bonding_Pos]);//, &axis[11].pos[Bonding_Pos]);
			}
			else if (strcmp(Title, "MOTOR_DARK_POSITION") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", Title, 499,
					&axis[0].pos[Dark_Pos], &axis[1].pos[Dark_Pos], &axis[2].pos[Dark_Pos], &axis[3].pos[Dark_Pos], &axis[4].pos[Dark_Pos], &axis[5].pos[Dark_Pos],
					&axis[6].pos[Dark_Pos], &axis[7].pos[Dark_Pos], &axis[8].pos[Dark_Pos], &axis[9].pos[Dark_Pos], &axis[10].pos[Dark_Pos]);//, &axis[11].pos[Dark_Pos]);
			}
			else if (strcmp(Title, "MOTOR_6500K_POSITION") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", Title, 499,
					&axis[0].pos[OC_6500K_Pos], &axis[1].pos[OC_6500K_Pos], &axis[2].pos[OC_6500K_Pos], &axis[3].pos[OC_6500K_Pos], &axis[4].pos[OC_6500K_Pos], &axis[5].pos[OC_6500K_Pos],
					&axis[6].pos[OC_6500K_Pos], &axis[7].pos[OC_6500K_Pos], &axis[8].pos[OC_6500K_Pos], &axis[9].pos[OC_6500K_Pos], &axis[10].pos[OC_6500K_Pos]);//, &axis[11].pos[OC_6500K_Pos]);
			}
			else if (strcmp(Title, "MOTOR_2800K_POSITION") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", Title, 499,
					&axis[0].pos[OC_2800K_Pos], &axis[1].pos[OC_2800K_Pos], &axis[2].pos[OC_2800K_Pos], &axis[3].pos[OC_2800K_Pos], &axis[4].pos[OC_2800K_Pos], &axis[5].pos[OC_2800K_Pos],
					&axis[6].pos[OC_2800K_Pos], &axis[7].pos[OC_2800K_Pos], &axis[8].pos[OC_2800K_Pos], &axis[9].pos[OC_2800K_Pos], &axis[10].pos[OC_2800K_Pos]);//, &axis[11].pos[OC_2800K_Pos]);
			}
			else if (strcmp(Title, "MOTOR_DEFECT_POSITION") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", Title, 499,
					&axis[0].pos[Defect_Pos], &axis[1].pos[Defect_Pos], &axis[2].pos[Defect_Pos], &axis[3].pos[Defect_Pos], &axis[4].pos[Defect_Pos], &axis[5].pos[Defect_Pos],
					&axis[6].pos[Defect_Pos], &axis[7].pos[Defect_Pos], &axis[8].pos[Defect_Pos], &axis[9].pos[Defect_Pos], &axis[10].pos[Defect_Pos]);//, &axis[11].pos[Defect_Pos]);
			}
			else if (strcmp(Title, "MOTOR_PCB_LOADING_POSITION") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", Title, 499,
					&axis[0].pos[Pcb_Loading_Pos], &axis[1].pos[Pcb_Loading_Pos], &axis[2].pos[Pcb_Loading_Pos], &axis[3].pos[Pcb_Loading_Pos], &axis[4].pos[Pcb_Loading_Pos], &axis[5].pos[Pcb_Loading_Pos],
					&axis[6].pos[Pcb_Loading_Pos], &axis[7].pos[Pcb_Loading_Pos], &axis[8].pos[Pcb_Loading_Pos], &axis[9].pos[Pcb_Loading_Pos], &axis[10].pos[Pcb_Loading_Pos]);//, &axis[11].pos[Defect_Pos]);
			}
			else if (strcmp(Title, "MOTOR_COVER_LOADING_POSITION") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", Title, 499,
					&axis[0].pos[Cover_Loading_Pos], &axis[1].pos[Cover_Loading_Pos], &axis[2].pos[Cover_Loading_Pos], &axis[3].pos[Cover_Loading_Pos], &axis[4].pos[Cover_Loading_Pos], &axis[5].pos[Cover_Loading_Pos],
					&axis[6].pos[Cover_Loading_Pos], &axis[7].pos[Cover_Loading_Pos], &axis[8].pos[Cover_Loading_Pos], &axis[9].pos[Cover_Loading_Pos], &axis[10].pos[Cover_Loading_Pos]);//, &axis[11].pos[Defect_Pos]);
			}
			else if (strcmp(Title, "MOTOR_COVER_UNLOADING_POSITION") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", Title, 499,
					&axis[0].pos[Cover_UnLoading_Pos], &axis[1].pos[Cover_UnLoading_Pos], &axis[2].pos[Cover_UnLoading_Pos], &axis[3].pos[Cover_UnLoading_Pos], &axis[4].pos[Cover_UnLoading_Pos], &axis[5].pos[Cover_UnLoading_Pos],
					&axis[6].pos[Cover_UnLoading_Pos], &axis[7].pos[Cover_UnLoading_Pos], &axis[8].pos[Cover_UnLoading_Pos], &axis[9].pos[Cover_UnLoading_Pos], &axis[10].pos[Cover_UnLoading_Pos]);//, &axis[11].pos[Defect_Pos]);
			}
			//
			//
			else if (strcmp(Title, "MOTOR_POINT_DISPENSE_POSITION") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", Title, 499,
					&axis[0].pos[PDispense_Pos], &axis[1].pos[PDispense_Pos], &axis[2].pos[PDispense_Pos], &axis[3].pos[PDispense_Pos], &axis[4].pos[PDispense_Pos], &axis[5].pos[PDispense_Pos],
					&axis[6].pos[PDispense_Pos], &axis[7].pos[PDispense_Pos], &axis[8].pos[PDispense_Pos], &axis[9].pos[PDispense_Pos], &axis[10].pos[PDispense_Pos]);//, &axis[11].pos[Defect_Pos]);
			}
			else if (strcmp(Title, "MOTOR_CONNECT_POSITION") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", Title, 499,
					&axis[0].pos[Contact_Pos], &axis[1].pos[Contact_Pos], &axis[2].pos[Contact_Pos], &axis[3].pos[Contact_Pos], &axis[4].pos[Contact_Pos], &axis[5].pos[Contact_Pos],
					&axis[6].pos[Contact_Pos], &axis[7].pos[Contact_Pos], &axis[8].pos[Contact_Pos], &axis[9].pos[Contact_Pos], &axis[10].pos[Contact_Pos]);//, &axis[11].pos[Contact_Pos]);
			}
			else if (strcmp(Title, "MOTOR_CALC_POSITION") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", Title, 499,
					&axis[0].pos[Calc_Pos], &axis[1].pos[Calc_Pos], &axis[2].pos[Calc_Pos], &axis[3].pos[Calc_Pos], &axis[4].pos[Calc_Pos], &axis[5].pos[Calc_Pos],
					&axis[6].pos[Calc_Pos], &axis[7].pos[Calc_Pos], &axis[8].pos[Calc_Pos], &axis[9].pos[Calc_Pos], &axis[10].pos[Calc_Pos]);//, &axis[11].pos[Calc_Pos]);
			}
			else if (strcmp(Title, "MOTOR_CLEAN_POSITION") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", Title, 499,
					&axis[0].pos[Clean_Pos], &axis[1].pos[Clean_Pos], &axis[2].pos[Clean_Pos], &axis[3].pos[Clean_Pos], &axis[4].pos[Clean_Pos], &axis[5].pos[Clean_Pos],
					&axis[6].pos[Clean_Pos], &axis[7].pos[Clean_Pos], &axis[8].pos[Clean_Pos], &axis[9].pos[Clean_Pos], &axis[10].pos[Clean_Pos]);//, &axis[11].pos[Clean_Pos]);
			}
			else if (strcmp(Title, "MOTOR_INSP_POSITION") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", Title, 499,
					&axis[0].pos[Insp_Pos], &axis[1].pos[Insp_Pos], &axis[2].pos[Insp_Pos], &axis[3].pos[Insp_Pos], &axis[4].pos[Insp_Pos], &axis[5].pos[Insp_Pos],
					&axis[6].pos[Insp_Pos], &axis[7].pos[Insp_Pos], &axis[8].pos[Insp_Pos], &axis[9].pos[Insp_Pos], &axis[10].pos[Insp_Pos]);//, &axis[11].pos[Insp_Pos]);
			}
			else if (strcmp(Title, "MOTOR_HOLDER_UV_POSITION") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", Title, 499,
					&axis[0].pos[Holder_Uv_Pos], &axis[1].pos[Holder_Uv_Pos], &axis[2].pos[Holder_Uv_Pos], &axis[3].pos[Holder_Uv_Pos], &axis[4].pos[Holder_Uv_Pos], &axis[5].pos[Holder_Uv_Pos],
					&axis[6].pos[Holder_Uv_Pos], &axis[7].pos[Holder_Uv_Pos], &axis[8].pos[Holder_Uv_Pos], &axis[9].pos[Holder_Uv_Pos], &axis[10].pos[Holder_Uv_Pos]);//, &axis[11].pos[Holder_Uv_Pos]);
			}
			else if (strcmp(Title, "MOTOR_CONTI_TAIL_DELAY_POSITION") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", Title, 499,
					&axis[0].pos[ContiTailDelay_Pos], &axis[1].pos[ContiTailDelay_Pos], &axis[2].pos[ContiTailDelay_Pos], &axis[3].pos[ContiTailDelay_Pos], &axis[4].pos[ContiTailDelay_Pos], &axis[5].pos[ContiTailDelay_Pos],
					&axis[6].pos[ContiTailDelay_Pos], &axis[7].pos[ContiTailDelay_Pos], &axis[8].pos[ContiTailDelay_Pos], &axis[9].pos[ContiTailDelay_Pos], &axis[10].pos[ContiTailDelay_Pos]);//, &axis[11].pos[ContiTailDelay_Pos]);
			}
			else if (strcmp(Title, "MOTOR_COM_LASER_POSITION") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", Title, 499,
					&axis[0].pos[Com_Laser_Pos], &axis[1].pos[Com_Laser_Pos], &axis[2].pos[Com_Laser_Pos], &axis[3].pos[Com_Laser_Pos], &axis[4].pos[Com_Laser_Pos], &axis[5].pos[Com_Laser_Pos],
					&axis[6].pos[Com_Laser_Pos], &axis[7].pos[Com_Laser_Pos], &axis[8].pos[Com_Laser_Pos], &axis[9].pos[Com_Laser_Pos], &axis[10].pos[Com_Laser_Pos]);//, &axis[11].pos[Contact2_Pos]);
			}
			else if (strcmp(Title, "MOTOR_CALC2_POSITION") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", Title, 499,
					&axis[0].pos[Calc2_Pos], &axis[1].pos[Calc2_Pos], &axis[2].pos[Calc2_Pos], &axis[3].pos[Calc2_Pos], &axis[4].pos[Calc2_Pos], &axis[5].pos[Calc2_Pos],
					&axis[6].pos[Calc2_Pos], &axis[7].pos[Calc2_Pos], &axis[8].pos[Calc2_Pos], &axis[9].pos[Calc2_Pos], &axis[10].pos[Calc2_Pos]);//, &axis[11].pos[Calc2_Pos]);
			}
			else if (strcmp(Title, "MOTOR_COMALIGN_POSITION") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", Title, 499,
					&axis[0].pos[CompleteAlign_Pos], &axis[1].pos[CompleteAlign_Pos], &axis[2].pos[CompleteAlign_Pos], &axis[3].pos[CompleteAlign_Pos], &axis[4].pos[CompleteAlign_Pos], &axis[5].pos[CompleteAlign_Pos],
					&axis[6].pos[CompleteAlign_Pos], &axis[7].pos[CompleteAlign_Pos], &axis[8].pos[CompleteAlign_Pos], &axis[9].pos[CompleteAlign_Pos], &axis[10].pos[CompleteAlign_Pos]);//, &axis[11].pos[CompleteAlign_Pos]);
			}
			else if (strcmp(Title, "MOTOR_DISPENSE_POS1") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", Title, 499,
					&axis[0].pos[Dispense_Pos1], &axis[1].pos[Dispense_Pos1], &axis[2].pos[Dispense_Pos1], &axis[3].pos[Dispense_Pos1], &axis[4].pos[Dispense_Pos1], &axis[5].pos[Dispense_Pos1],
					&axis[6].pos[Dispense_Pos1], &axis[7].pos[Dispense_Pos1], &axis[8].pos[Dispense_Pos1], &axis[9].pos[Dispense_Pos1], &axis[10].pos[Dispense_Pos1]);
			}

			else if (strcmp(Title, "MOTOR_DISPENSE_POS2") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", Title, 499,
					&axis[0].pos[Dispense_Pos2], &axis[1].pos[Dispense_Pos2], &axis[2].pos[Dispense_Pos2], &axis[3].pos[Dispense_Pos2], &axis[4].pos[Dispense_Pos2], &axis[5].pos[Dispense_Pos2],
					&axis[6].pos[Dispense_Pos2], &axis[7].pos[Dispense_Pos2], &axis[8].pos[Dispense_Pos2], &axis[9].pos[Dispense_Pos2], &axis[10].pos[Dispense_Pos2]);
			}

			else if (strcmp(Title, "MOTOR_DISPENSE_POS3") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", Title, 499,
					&axis[0].pos[Dispense_Pos3], &axis[1].pos[Dispense_Pos3], &axis[2].pos[Dispense_Pos3], &axis[3].pos[Dispense_Pos3], &axis[4].pos[Dispense_Pos3], &axis[5].pos[Dispense_Pos3],
					&axis[6].pos[Dispense_Pos3], &axis[7].pos[Dispense_Pos3], &axis[8].pos[Dispense_Pos3], &axis[9].pos[Dispense_Pos3], &axis[10].pos[Dispense_Pos3]);
			}
			else if (strcmp(Title, "LENS_OK_LIMIT") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf"
					, Title, 499, &axis[Motor_Lens_X].m_dLimit_OK, &axis[Motor_Lens_Y].m_dLimit_OK, &axis[Motor_Lens_Z].m_dLimit_OK
					, &axis[Motor_Lens_Xt].m_dLimit_OK, &axis[Motor_Lens_Yt].m_dLimit_OK);
			}
			else if (strcmp(Title, "LENS_ERR_LIMIT") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf"
					, Title, 499, &axis[Motor_Lens_X].m_dLimit_Err, &axis[Motor_Lens_Y].m_dLimit_Err, &axis[Motor_Lens_Z].m_dLimit_Err
					, &axis[Motor_Lens_Xt].m_dLimit_Err, &axis[Motor_Lens_Yt].m_dLimit_Err);
			}
			else if (strcmp(Title, "PCB_OK_LIMIT") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf"
					, Title, 499, &axis[Motor_PCB_X].m_dLimit_OK, &axis[Motor_PCB_Y].m_dLimit_OK, &axis[Motor_PCB_TH].m_dLimit_OK
					, &axis[Motor_PCB_Xt].m_dLimit_OK, &axis[Motor_PCB_Yt].m_dLimit_OK, &axis[Motor_PCB_Z].m_dLimit_OK);
			}
			else if (strcmp(Title, "PCB_ERR_LIMIT") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf"
					, Title, 499, &axis[Motor_PCB_X].m_dLimit_Err, &axis[Motor_PCB_Y].m_dLimit_Err,	&axis[Motor_PCB_TH].m_dLimit_Err
					, &axis[Motor_PCB_Xt].m_dLimit_Err, &axis[Motor_PCB_Yt].m_dLimit_Err, &axis[Motor_PCB_Z].m_dLimit_Err);
			}

			
			else if (strcmp(Title, "LENS_MARK_1")==0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %d %d %d"
					,	Title, 499, &m_MarkCenter[0][0].x, &m_MarkCenter[0][0].y, &m_MarkOrigin[0][0].x, &m_MarkOrigin[0][0].y, &m_MarkSize[0][0].x, &m_MarkSize[0][0].y, &m_iLimitRate[0][0]);
			}
			else if (strcmp(Title, "LENS_MARK_2")==0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %d %d %d"
					,	Title, 499, &m_MarkCenter[0][1].x, &m_MarkCenter[0][1].y, &m_MarkOrigin[0][1].x, &m_MarkOrigin[0][1].y, &m_MarkSize[0][1].x, &m_MarkSize[0][1].y, &m_iLimitRate[0][1]);
			}
			else if (strcmp(Title, "PCB_MARK_1")==0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %d %d %d"
					,	Title, 499, &m_MarkCenter[1][0].x, &m_MarkCenter[1][0].y, &m_MarkOrigin[1][0].x, &m_MarkOrigin[1][0].y, &m_MarkSize[1][0].x, &m_MarkSize[1][0].y, &m_iLimitRate[1][0]);
			}
			else if (strcmp(Title, "PCB_MARK_2")==0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %d %d %d"
					,	Title, 499, &m_MarkCenter[1][1].x, &m_MarkCenter[1][1].y, &m_MarkOrigin[1][1].x, &m_MarkOrigin[1][1].y, &m_MarkSize[1][1].x, &m_MarkSize[1][1].y, &m_iLimitRate[1][1]);
			}
			else if (strcmp(Title, "LENS_DEAD_END_MARK_1")==0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %d %d %d"
					,	Title, 499, &m_MarkCenter[2][0].x, &m_MarkCenter[2][0].y, &m_MarkOrigin[2][0].x, &m_MarkOrigin[2][0].y, &m_MarkSize[2][0].x, &m_MarkSize[2][0].y, &m_iLimitRate[2][0]);
			}
			else if (strcmp(Title, "LENS_DEAD_END_MARK_2")==0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %d %d %d"
					,	Title, 499, &m_MarkCenter[2][1].x, &m_MarkCenter[2][1].y, &m_MarkOrigin[2][1].x, &m_MarkOrigin[2][1].y, &m_MarkSize[2][1].x, &m_MarkSize[2][1].y, &m_iLimitRate[2][1]);
			}

			else if (strcmp(Title, "MARK_MATCHING")==0)
			{
				sscanf_s(Line, "%s %d %d %d %d"
					,Title, 499, &m_MarkMatchingRate[0], &m_MarkMatchingRate[1], &m_MarkMatchingRate[2], &m_MarkMatchingRate[3]);
			}
			else if (strcmp(Title, "LED")==0)
			{
				sscanf_s(Line, "%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",	Title, 499, &m_iLedValue[0], &m_iLedValue[1], &m_iLedValue[2], &m_iLedValue[3], &m_iLedValue[4], &m_iLedValue[5], &m_iLedValue[6], &m_iLedValue[7], &m_iLedValue[8], &m_iLedValue[9], &m_iLedValue[10], &m_iLedValue[11], &m_iLedValue[12], &m_iLedValue[13], &m_iLedValue[14], &m_iLedValue[15], &m_iLedValue[16], &m_iLedValue[17], &m_iLedValue[18]);
			}
			else if (strcmp(Title, "OIS_AF")==0)
			{
				sscanf_s(Line, "%s %d %d %lf",	Title, 499, &code1, &code2, &dFov);
			}
			else if (strcmp(Title, "UV_Time")==0)
			{
				sscanf_s(Line, "%s %d",	Title, 499, &UV_Time);
			}
			else if (strcmp(Title, "UV_Power") == 0)
			{
				sscanf_s(Line, "%s %d", Title, 499, &UV_Power);
			}
			else if (strcmp(Title, "UV_Weight")==0)
			{
				sscanf_s(Line, "%s %lf", Title, 499, &UV_Weight);
			}
			else if (strcmp(Title, "AA_Repeat_Count") == 0)
			{
				sscanf_s(Line, "%s %d", Title, 499, &AARepeatCount);
			}
			else if (strcmp(Title, "SENSOR_INFO")==0)
			{
				sscanf_s(Line, "%s %d %d",	Title, 499, &m_iSensorID, &m_iSensorType);
			}
			else if ( strcmp(Title, "INFO_AF1")==0 )
			{
				sscanf_s(Line, "%s %d %d %lf %lf %f", Title, 499, &strInfo_AF1.m_iDelayTime, &strInfo_AF1.m_iStepCnt, &strInfo_AF1.m_dMoveDistance, &strInfo_AF1.m_dMoveVel, &strInfo_AF1.m_fLimit_MTF);
			}
			else if ( strcmp(Title, "INFO_AF2")==0 )
			{
				sscanf_s(Line, "%s %d %d %lf %lf", Title, 499, &strInfo_AF2.m_iDelayTime, &strInfo_AF2.m_iStepCnt, &strInfo_AF2.m_dMoveDistance, &strInfo_AF2.m_dMoveVel);
			}
			else if ( strcmp(Title, "INFO_TILT")==0 )
			{
				sscanf_s(Line, "%s %d %d %lf %lf", Title, 499, &strInfo_Tilt.m_iDelayTime, &strInfo_Tilt.m_iStepCnt, &strInfo_Tilt.m_dMoveDistance, &strInfo_Tilt.m_dMoveVel);
			}
			else if ( strcmp(Title, "INFO_CAM1")==0 )
			{
				sscanf_s(Line, "%s %d %d", Title, 499, &strInfo_Cam[0].m_iDelayTime, &strInfo_Cam[0].m_iRetryCnt);
			}
			else if ( strcmp(Title, "INFO_CAM2")==0 )
			{
				sscanf_s(Line, "%s %d %d", Title, 499, &strInfo_Cam[1].m_iDelayTime, &strInfo_Cam[1].m_iRetryCnt);
			}
			else if ( strcmp(Title, "INFO_CAM3")==0 )
			{
				sscanf_s(Line, "%s %d %d", Title, 499, &strInfo_Cam[2].m_iDelayTime, &strInfo_Cam[2].m_iRetryCnt);
			}
			else if ( strcmp(Title, "INFO_CAM4")==0 )
			{
				sscanf_s(Line, "%s %d %d", Title, 499, &strInfo_Cam[3].m_iDelayTime, &strInfo_Cam[3].m_iRetryCnt);
			}
			else if ( strcmp(Title, "CCM_AVERAGE_COUNT")==0 )
			{
				sscanf_s(Line, "%s %d %d %d %d %d", Title, 499, &strInfo_CCM.m_iCnt_Average_Thru_Focus, 
					                                            &strInfo_CCM.m_iCnt_Average_Tilting, 
					                                            &strInfo_CCM.m_iCnt_Average_Fine_Focus, 
																&strInfo_CCM.m_iCnt_Average_Defect, 
																&strInfo_CCM.m_iCnt_Average_Opt_Centering);
			}
			else if ( strcmp(Title, "CCD_CELL_SIZE")==0 )
			{
				sscanf_s(Line, "%s %lf", Title, 499, &m_dSize_CCD_Cell);
			}
			else if ( strcmp(Title, "CCD_GAIN_SKIP_SIZE")==0 )
			{
				sscanf_s(Line, "%s %d %d", Title, 499, &m_iSkip_X_gain, &m_iSkip_Y_gain);
			}
			else if ( strcmp(Title, "CCD_GAIN_BORDER_SIZE")==0 )
			{
				sscanf_s(Line, "%s %lf %lf", Title, 499, &m_dBorder_X_gain, &m_dBorder_Y_gain);
			}
			else if ( strcmp(Title, "CCD_GRAB_METHOD")==0 )
			{
				sscanf_s(Line, "%s %d", Title, 499, &m_eGrabMethod);
			}
			else if ( strcmp(Title, "CIRCLE_POS1")==0 )
			{
				sscanf_s(Line, "%s %d %d", Title, 499, &sfrElem.m_CircleP[0].x, &sfrElem.m_CircleP[0].y);
			}
			else if ( strcmp(Title, "CIRCLE_POS2")==0 )
			{
				sscanf_s(Line, "%s %d %d", Title, 499, &sfrElem.m_CircleP[1].x, &sfrElem.m_CircleP[1].y);
			}
			else if ( strcmp(Title, "CIRCLE_POS3")==0 )
			{
				sscanf_s(Line, "%s %d %d", Title, 499, &sfrElem.m_CircleP[2].x, &sfrElem.m_CircleP[2].y);
			}
			else if ( strcmp(Title, "CIRCLE_POS4")==0 )
			{
				sscanf_s(Line, "%s %d %d", Title, 499, &sfrElem.m_CircleP[3].x, &sfrElem.m_CircleP[3].y);
			}
			else if ( strcmp(Title, "CIRCLE_ROI1")==0 )
			{
				sscanf_s(Line, "%s %d %d %d %d", Title, 499, &sfrElem.m_CircleRoi[0].left, &sfrElem.m_CircleRoi[0].top, &sfrElem.m_CircleRoi[0].right, &sfrElem.m_CircleRoi[0].bottom);
			}
			else if ( strcmp(Title, "CIRCLE_ROI2")==0 )
			{
				sscanf_s(Line, "%s %d %d %d %d", Title, 499, &sfrElem.m_CircleRoi[1].left, &sfrElem.m_CircleRoi[1].top, &sfrElem.m_CircleRoi[1].right, &sfrElem.m_CircleRoi[1].bottom);
			}
			else if ( strcmp(Title, "CIRCLE_ROI3")==0 )
			{
				sscanf_s(Line, "%s %d %d %d %d", Title, 499, &sfrElem.m_CircleRoi[2].left, &sfrElem.m_CircleRoi[2].top, &sfrElem.m_CircleRoi[2].right, &sfrElem.m_CircleRoi[2].bottom);
			}
			else if ( strcmp(Title, "CIRCLE_ROI4")==0 )
			{
				sscanf_s(Line, "%s %d %d %d %d", Title, 499, &sfrElem.m_CircleRoi[3].left, &sfrElem.m_CircleRoi[3].top, &sfrElem.m_CircleRoi[3].right, &sfrElem.m_CircleRoi[3].bottom);
			}
            //
           
			if ( strcmp(Title, "SFR_CHECK_CNT")==0 )
			{
				sscanf_s(Line, "%s %d", Title, 499, &m_iCnt_Check_SFR);
			}
			else if ( strcmp(Title, "MOVE_OFFSET_Z")==0 )
			{
				sscanf_s(Line, "%s %lf", Title, 499, &m_dMove_Offset_Z);
			}
			else if ( strcmp(Title, "SFR_ROI_SIZE")==0 )
			{
				sscanf_s(Line, "%s %d %d", Title, 499, &m_iSize_ROI_X, &m_iSize_ROI_Y);
			}
			else if (strcmp(Title, "PCB_Bright_Contrast")==0)
			{
				sscanf_s(Line, "%s %d %d",	Title, 499, &m_iBright[PCB_Holder_MARK], &m_iContrast[PCB_Holder_MARK]);
			}
			else if (strcmp(Title, "LENS_Bright_Contrast")==0)
			{
				sscanf_s(Line, "%s %d %d",	Title, 499, &m_iBright[LENS_Align_MARK], &m_iContrast[LENS_Align_MARK]);
			}
			else if (strcmp(Title, "Chip_Bright_Contrast")==0)
			{
				sscanf_s(Line, "%s %d %d",	Title, 499, &m_iBright[PCB_Chip_MARK], &m_iContrast[PCB_Chip_MARK]);
			}
			else if (strcmp(Title, "USE_DEFECT_INSP")==0)
			{
				sscanf_s(Line, "%s %d %d",	Title, 499, &defect.m_iNgAlarm, &defect.m_iNgUnloading);
			}
			else if (strcmp(Title, "USE_SIZE")==0)
			{
				sscanf_s(Line, "%s %d %d %d %d %d",	Title, 499, &defect.m_i_Insp_Flag[0],	&defect.m_i_Insp_Flag[1],	&defect.m_i_Insp_Flag[2],	&defect.m_i_Insp_Flag[3],	&defect.m_i_Insp_Flag[4]);
			}
			else if (strcmp(Title, "SMALL_FILTER_SIZE")==0)
			{
				sscanf_s(Line, "%s %d %d %d %d %d",	Title, 499, &defect.m_i_Filter_Size_Small[0],	&defect.m_i_Filter_Size_Small[1],	&defect.m_i_Filter_Size_Small[2],	&defect.m_i_Filter_Size_Small[3],	&defect.m_i_Filter_Size_Small[4]);
			}
			else if (strcmp(Title, "LARGE_FILTER_SIZE")==0)
			{
				sscanf_s(Line, "%s %d %d %d %d %d",	Title, 499, &defect.m_i_Filter_Size_Large[0],	&defect.m_i_Filter_Size_Large[1],	&defect.m_i_Filter_Size_Large[2],	&defect.m_i_Filter_Size_Large[3],	&defect.m_i_Filter_Size_Large[4]);
			}
			else if (strcmp(Title, "THRESHOLD")==0)
			{
				sscanf_s(Line, "%s %f %f %f %f %f",	Title, 499, &defect.m_f_Threshold[0],	&defect.m_f_Threshold[1],	&defect.m_f_Threshold[2],	&defect.m_f_Threshold[3], &defect.m_f_Threshold[4]);
			}
			else if (strcmp(Title, "MIN_SIZE")==0)
			{
				sscanf_s(Line, "%s %d %d %d %d %d",	Title, 499, &defect.m_i_Defect_Size_Min[0], &defect.m_i_Defect_Size_Min[1], &defect.m_i_Defect_Size_Min[2], &defect.m_i_Defect_Size_Min[3], &defect.m_i_Defect_Size_Min[4]);
			}
			else if (strcmp(Title, "MAX_SIZE")==0)
			{
				sscanf_s(Line, "%s %d %d %d %d %d",	Title, 499, &defect.m_i_Defect_Size_Max[0], &defect.m_i_Defect_Size_Max[1], &defect.m_i_Defect_Size_Max[2], &defect.m_i_Defect_Size_Max[3], &defect.m_i_Defect_Size_Max[4]);
			}
			else if (strcmp(Title, "GRAY_DIFF")==0)
			{
				sscanf_s(Line, "%s %f %f %f %f %f",	Title, 499, &defect.m_f_Gray_diff[0], &defect.m_f_Gray_diff[1], &defect.m_f_Gray_diff[2], &defect.m_f_Gray_diff[3], &defect.m_f_Gray_diff[4]);
			}
			else if (strcmp(Title, "BOUNDARY_SKIP")==0)
			{
				sscanf_s(Line, "%s %d %d %d %d %d",	Title, 499, &defect.m_i_Skip_Boundary[0],  &defect.m_i_Skip_Boundary[1], &defect.m_i_Skip_Boundary[2], &defect.m_i_Skip_Boundary[3], &defect.m_i_Skip_Boundary[4]);
			}
			else if (strcmp(Title, "MAX_LIMIT_CNT")==0)
			{
				sscanf_s(Line, "%s %d %d %d %d %d",	Title, 499, &defect.m_i_Cnt_Limit[0],   &defect.m_i_Cnt_Limit[1],  &defect.m_i_Cnt_Limit[2], &defect.m_i_Cnt_Limit[3], &defect.m_i_Cnt_Limit[4]);
			}
			else if (strcmp(Title, "SCALE") == 0)
			{
				sscanf_s(Line, "%s %d %d %d %d", Title, 499, &defect.m_iSmallScale, &defect.m_iMiddleScale, &defect.m_iLargeScale, &defect.m_iEdgeScale);
			}
			else if (strcmp(Title, "SIDE_MODEL_CHECK") == 0)
			{
				sscanf_s(Line, "%s %d", Title, 499, &d_SIDE_MODEL_CH);
			}
			else if (strcmp(Title, "INSP_PCB_TILT") == 0)
			{
				sscanf_s(Line, "%s %lf %lf", Title, 499, &m_InspPcbTilt[0], &m_InspPcbTilt[1]);
			}
			else if	(strcmp(Title, "INPOS_X")==0)
			{
				sscanf_s(Line, "%s %lf %lf %lf",	Title, 499, &m_InPos_X[0], &m_InPos_X[1], &m_InPos_X[2]);
			}
			else if	(strcmp(Title, "INPOS_Y")==0)
			{
				sscanf_s(Line, "%s %lf %lf %lf",	Title, 499, &m_InPos_Y[0], &m_InPos_Y[1], &m_InPos_Y[2]);
			}
			else if (strcmp(Title, "OUTPOS_X") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf", Title, 499, &m_OutPos_X[0], &m_OutPos_X[1], &m_OutPos_X[2]);
			}
			else if (strcmp(Title, "OUTPOS_Y") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf", Title, 499, &m_OutPos_Y[0], &m_OutPos_Y[1], &m_OutPos_Y[2]);
			}
			else if (strcmp(Title, "PCB_LASERPOS_X") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf", Title, 499, &m_PcbLaserPos_X[0], &m_PcbLaserPos_X[1], &m_PcbLaserPos_X[2]);
			}
			else if (strcmp(Title, "PCB_LASERPOS_Y") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf", Title, 499, &m_PcbLaserPos_Y[0], &m_PcbLaserPos_Y[1], &m_PcbLaserPos_Y[2]);
			}

			
			else if( strcmp(Title, "EPOXY_DATA") == 0 )
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf",	Title, 499, &dSpeed, &dAcc, &dOnTime, &dOffTime, &dSmallSpeed, &dSmallOffTime);
			}
			else if( strcmp(Title, "EPOXY_CIRCLE_DATA") == 0 )
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf",	Title, 499, &dRadiusLength,  &dAngle,  &dCircleSpeed, &dCircleAcc, &dConti_RadiusLength, &dConti_Angle, &dConti_Speed, &dTwister_Speed);
			}
			else if( strcmp(Title, "EPOXY_LINE") == 0 )
			{
				sscanf_s(Line, "%s %lf %lf %d",	Title, 499, &dEpoxySize, &dEpoxySpeed, &iEpoxyDelay);
			}
			else if ( strcmp(Title, "EPOXY_TABLE_OFFSET_X")==0 )
			{
				sscanf_s(Line, "%s %f %f %f %f", Title, 499, &offset.f_epoxy_x_dispense_offset[0], &offset.f_epoxy_x_dispense_offset[1], &offset.f_epoxy_x_dispense_offset[2], &offset.f_epoxy_x_dispense_offset[3]);
			}
			else if( strcmp(Title, "EPOXYINSP_OFFSET") == 0 )
			{
				sscanf_s(Line, "%s %lf %lf",	Title, 499, &dEpoxyOffset_X, &dEpoxyOffset_Y);
			}
			else if ( strcmp(Title, "EPOXY_BASE_POS")==0 )
			{
				sscanf_s(Line, "%s %d %d", Title, 499, &m_EpoxyBaseP.x, &m_EpoxyBaseP.y);
			}
			else if ( strcmp(Title, "EPOXY2_BASE_POS")==0 )
			{
				sscanf_s(Line, "%s %d %d", Title, 499, &m_Epoxy2BaseP.x, &m_Epoxy2BaseP.y);
			}
			else if ( strcmp(Title, "EPOXY_OFFSET_POS")==0 )
			{
				sscanf_s(Line, "%s %lf %lf", Title, 499, &m_dEpoxyOffsetX, &m_dEpoxyOffsetY);
			}
			else if ( strcmp(Title, "EPOXY2_OFFSET_POS")==0 )
			{
				sscanf_s(Line, "%s %lf %lf", Title, 499, &m_dEpoxy2OffsetX, &m_dEpoxy2OffsetY);
			}
			else if ( strcmp(Title, "EPOXY_TABLE_OFFSET_Y")==0 )
			{
				sscanf_s(Line, "%s %f %f %f %f", Title, 499, &offset.f_epoxy_y_dispense_offset[0], &offset.f_epoxy_y_dispense_offset[1], &offset.f_epoxy_y_dispense_offset[2], &offset.f_epoxy_y_dispense_offset[3]);
			}
			else if ( strcmp(Title, "EPOXY_TABLE_OFFSET_Z")==0 )
			{
				sscanf_s(Line, "%s %f %f %f %f", Title, 499, &offset.f_epoxy_z_dispense_offset[0], &offset.f_epoxy_z_dispense_offset[1], &offset.f_epoxy_z_dispense_offset[2], &offset.f_epoxy_z_dispense_offset[3]);
			}
			else if (strcmp(Title, "RESIN_DRAW_SIZE")==0)
			{
				sscanf_s(Line, "%s %lf %lf",	Title, 499, &m_ResinDrawSize.x, &m_ResinDrawSize.y);
			}
			else if (strcmp(Title, "CIRCLE_DRAW_SIZE_LT") == 0)
			{
				sscanf_s(Line, "%s	%lf %lf", Title, 499, &m_CircleDrawSize[0].x, &m_CircleDrawSize[0].y);
			}
			else if (strcmp(Title, "CIRCLE_DRAW_SIZE_RT") == 0)
			{
				sscanf_s(Line, "%s	%lf %lf", Title, 499, &m_CircleDrawSize[1].x, &m_CircleDrawSize[1].y);
			}
			else if (strcmp(Title, "CIRCLE_DRAW_SIZE_LB") == 0)
			{
				sscanf_s(Line, "%s	%lf %lf", Title, 499, &m_CircleDrawSize[2].x, &m_CircleDrawSize[2].y);
			}
			else if (strcmp(Title, "CIRCLE_DRAW_SIZE_RB") == 0)
			{
				sscanf_s(Line, "%s	%lf %lf", Title, 499, &m_CircleDrawSize[3].x, &m_CircleDrawSize[3].y);
			}
			else if ( strcmp(Title, "RESIN_DRAW_CENTER")==0 )
			{
				sscanf_s(Line, "%s	%lf %lf %lf %lf %lf %lf %lf %lf", Title, 499, &m_CircleDrawCenter[0].x, &m_CircleDrawCenter[0].y, &m_CircleDrawCenter[1].x, &m_CircleDrawCenter[1].y, &m_CircleDrawCenter[2].x, &m_CircleDrawCenter[2].y, &m_CircleDrawCenter[3].x, &m_CircleDrawCenter[3].y);
			}
			else if ( strcmp(Title, "RESIN_INSP_OFFSET")==0 )
			{
				sscanf_s(Line, "%s	%lf %lf %lf %lf", Title, 499, &m_dResinInspOffset[0].x, &m_dResinInspOffset[0].y, &m_dResinInspOffset[1].x, &m_dResinInspOffset[1].y);
			}
			else if ( strcmp(Title, "RESIN_INSP_LIMIT")==0 )
			{
				sscanf_s(Line, "%s %d", Title, 499, &m_iResinInspLimit);
			}
			else if ( strcmp(Title, "RESIN_INSP_SPEC")==0 )
			{//KKYH 20150622 HOLE 검사 Spec 추가
				sscanf_s(Line, "%s %lf %lf %lf", Title, 499, &m_dResinInspHoleSpec, &m_dResinInspGapLength, &m_iResinInspRectSpec);
			}
//
//			}
			else if( strcmp(Title, "DISTORTION_MARK") == 0 )
			{
				sscanf_s(Line, "%s %d %d %d %d %d %d %d %d %d %d %d %d", Title, 499, &m_DistortionMark_ROI[0].x,&m_DistortionMark_ROI[0].y, &m_DistortionMark_ROI[1].x,&m_DistortionMark_ROI[1].y, &m_DistortionMark_ROI[2].x,&m_DistortionMark_ROI[2].y, &m_DistortionMark_ROI[3].x,&m_DistortionMark_ROI[3].y, &m_DistortionMark_ROI[4].x,&m_DistortionMark_ROI[4].y, &m_DistortionMark_ROI[5].x,&m_DistortionMark_ROI[5].y);
			}
			else if( strcmp(Title, "FIELD_VIEW_MARK") == 0 )
			{
				sscanf_s(Line, "%s %d %d %d %d", Title, 499, &m_FieldOfView_ROI[0].x,&m_FieldOfView_ROI[0].y, &m_FieldOfView_ROI[1].x,&m_FieldOfView_ROI[1].y);
			}
			else if( strcmp(Title, "FIELD_PATTERN_CENTER") == 0 )
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", Title, 499, &m_FieldPatternCenter[0].x,&m_FieldPatternCenter[0].y, &m_FieldPatternCenter[1].x,&m_FieldPatternCenter[1].y, &m_FieldPatternCenter[2].x,&m_FieldPatternCenter[2].y, &m_FieldPatternCenter[3].x,&m_FieldPatternCenter[3].y, &m_FieldPatternCenter[4].x,&m_FieldPatternCenter[4].y);
			}
			else if( strcmp(Title, "FIELD_PATTERN_ORIGIN") == 0 )
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", Title, 499, &m_FieldPatternOrigin[0].x,&m_FieldPatternOrigin[0].y, &m_FieldPatternOrigin[1].x,&m_FieldPatternOrigin[1].y, &m_FieldPatternOrigin[2].x,&m_FieldPatternOrigin[2].y, &m_FieldPatternOrigin[3].x,&m_FieldPatternOrigin[3].y, &m_FieldPatternOrigin[4].x,&m_FieldPatternOrigin[4].y);
			}
			else if ( strcmp(Title, "LINE_PULSE")==0 )		// Frequency(Line Pulse)
			{
				sscanf_s(Line, "%s	%f %f", Title, 499, &m_Line_Pulse, &model.m_Gen2_Line_Pulse);
			}
			if ( strcmp(Title, "IS_USE_LASER_TILT")==0 )		// Laser Tilt 사용 유무
			{
				sscanf_s(Line, "%s	%d", Title, 499, &m_IsUseLaserTilt);
			}		
			else if ( strcmp(Title, "CLEANPAD")==0 )
			{
				sscanf_s(Line, "%s %d %lf %lf",						Title, 499, &Cleancnt, &Cleanpad[0], &Cleanpad[1]);
			}
			else if ( strcmp(Title, "TILT_TY_ONLY_LR_RL")==0 )
			{
				sscanf_s(Line, "%s %d",						Title, 499, &m_Tilt_Ty_Only_LR_RL);
			}else if ( strcmp(Title, "CCD_ARRAY")==0 )
			{
				sscanf_s(Line, "%s	%d", Title, 499, &m_ccdArray);
			}

			//-- 조건문이 블록이 너무 많이 중첩되었다고 안된다고 하네요.... 어쩔수 없이 if문으로 다시.
			if (strcmp(Title, "DISPENSE_LENGTH") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf %lf %lf %lf %lf", Title, 499, &dDisLength[0], &dDisLength[1], &dDisLength[2], &dDisLength[3], &dDisLength[4], &dDisLength[5], &dDisLength[6], &dDisLength[7]);
			}
			if (strcmp(Title, "CIRCLE_RADIUS_OFFSETX") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dCircleRadiusCenterOffsetX[0], &dCircleRadiusCenterOffsetX[1], &dCircleRadiusCenterOffsetX[2], &dCircleRadiusCenterOffsetX[3]);
			}
			if (strcmp(Title, "CIRCLE_RADIUS_OFFSETY") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dCircleRadiusCenterOffsetY[0], &dCircleRadiusCenterOffsetY[1], &dCircleRadiusCenterOffsetY[2], &dCircleRadiusCenterOffsetY[3]);
			}
			if (strcmp(Title, "CIRCLE_END_OFFSETX") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dCircleRadiusEndOffsetX[0], &dCircleRadiusEndOffsetX[1], &dCircleRadiusEndOffsetX[2], &dCircleRadiusEndOffsetX[3]);
			}
			if (strcmp(Title, "CIRCLE_END_OFFSETY") == 0)
			{
				sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dCircleRadiusEndOffsetY[0], &dCircleRadiusEndOffsetY[1], &dCircleRadiusEndOffsetY[2], &dCircleRadiusEndOffsetY[3]);
			}
			else if ( strcmp(Title, "EPOXY_INSP_RECT_LEFT")==0 )
			{
				sscanf_s(Line, "%s	%d %d %d %d", Title, 499, &m_ResingRectStart[0].x, &m_ResingRectStart[0].y,	&m_ResingRectSize[0].x, &m_ResingRectSize[0].y);
			}
			else if ( strcmp(Title, "EPOXY_INSP_RECT_RIGHT")==0 )
			{
				sscanf_s(Line, "%s	%d %d %d %d", Title, 499, &m_ResingRectStart[1].x, &m_ResingRectStart[1].y,	&m_ResingRectSize[1].x, &m_ResingRectSize[1].y);
			}
			else if ( strcmp(Title, "EPOXY_INSP_RECT_TOP")==0 )
			{
				sscanf_s(Line, "%s	%d %d %d %d", Title, 499, &m_ResingRectStart[2].x, &m_ResingRectStart[2].y,	&m_ResingRectSize[2].x, &m_ResingRectSize[2].y);
			}
			else if ( strcmp(Title, "EPOXY_INSP_RECT_BOTTOM")==0 )
			{
				sscanf_s(Line, "%s	%d %d %d %d", Title, 499, &m_ResingRectStart[3].x, &m_ResingRectStart[3].y,	&m_ResingRectSize[3].x, &m_ResingRectSize[3].y);
			}
			else if ( strcmp(Title, "EPOXY_INSP_ANGLE")==0 )
			{
				sscanf_s(Line, "%s	%f %f %f %f %f %f %f %f", Title, 499, &m_ResingStartAngle[0], &m_ResingFinishAngle[0], &m_ResingStartAngle[1], &m_ResingFinishAngle[1], &m_ResingStartAngle[2], &m_ResingFinishAngle[2], &m_ResingStartAngle[3], &m_ResingFinishAngle[3]);
			}
			else if ( strcmp(Title, "EPOXY_INSP_COLOR_LEVEL")==0 )
			{
				sscanf_s(Line, "%s	%d", Title, 499, &m_ResingInspLevel);
			}
			else if ( strcmp(Title, "IS_USE_DARK_DEFECT_TEST")==0 )
			{
				sscanf_s(Line, "%s %d",						Title, 499, &m_IsUseDarkDefectTest);
			}

			else if ( strcmp(Title, "IS_USE_BRIGHT_DEFECT_TEST")==0 )
			{
				sscanf_s(Line, "%s %d",						Title, 499, &m_IsUseBrightDefectTest);
			}
			else if ( strcmp(Title, "IS_USE_STAIN_TEST")==0 )
			{
				sscanf_s(Line, "%s %d",						Title, 499, &m_IsUseStainTest);
			}
			else if ( strcmp(Title, "IS_DOOR_OPEN_RUNNING")==0 )
			{
				sscanf_s(Line, "%s %d",						Title, 499, &m_IsDoorOpenRunning);
			}
			else if ( strcmp(Title, "IS_AUTO_Z_SEARCH")==0 )
			{
				sscanf_s(Line, "%s %d",						Title, 499, &m_AUTO_Z_SEARCH);
			}
			else if ( strcmp(Title, "AUTO_Z_SEARCH_CNT")==0 )
			{
				sscanf_s(Line, "%s %d",						Title, 499, &m_AUTO_Z_SEARCH_CNT);
			}
			else if ( strcmp(Title, "AUTO_Z_SEARCH_VAL")==0 )
			{
				sscanf_s(Line, "%s %f",						Title, 499, &m_AUTO_Z_SEARCH_VAL);
			}
			else if (strcmp(Title, "TILT_Weight_Pre")==0)
			{
				sscanf_s(Line, "%s %lf", Title, 499, &Tilt_Weight_Pre);
			}
			else if (strcmp(Title, "TILT_Weight_Post")==0)
			{
				sscanf_s(Line, "%s %lf", Title, 499, &Tilt_Weight_Post);
			}
			else if (strcmp(Title, "TILT_DIRETION_V") == 0)
			{
				sscanf_s(Line, "%s %d %d %d %d %d", Title, 499, &Tilt_Diretion[0], &Tilt_Diretion[1], &Tilt_Diretion[2], &Tilt_Diretion[3], &Tilt_Diretion[4]);
			}
			else if (strcmp(Title, "UART_VALUE") == 0)
			{
				sscanf_s(Line, "%s %d %d", Title, 499, &m_Uart_Range1, &m_Uart_Range2);
			}
			else if (strcmp(Title, "CONTI_DOWN_OFFSET") == 0)
			{
				sscanf_s(Line, "%s %lf", Title, 499, &m_ContiDownOffset);
			}
			Line[0] = 0x00;
		}

		if(in)	fclose(in);

	}
	else 
	{
		Save();
	}

}

void CModelData::saveMark(int iCamNo, int iMarkType, int iMarkNo)
{
	CString FolderName;

	FolderName.Format("%s", AA_MODEL_LOAD_DIR);

	CString strType;
	if (iMarkType == PCB_Chip_MARK)			strType = "LENS";
	else if (iMarkType == PCB_Holder_MARK)	strType = "PCB";
	else									strType = "LENS_Edge";

	CString strPatDir;
#ifdef USE_GEOMETRIC
	strPatDir.Format("%s\\%s\\Data\\Mark\\%s_Mark_%d.mod", FolderName, mCurModelName, strType, iMarkNo);
	//strPatDir.Format("%s\\Model\\%s\\%s_Mark_%d.mod", FolderName, mCurModelName, strType, iMarkNo);
#else
	strPatDir.Format("%s\\%s\\Data\\Mark\\%s_Mark_%d.Pat", FolderName, mCurModelName, strType, iMarkNo);
	//strPatDir.Format("%s\\Model\\%s\\%s_Mark_%d.Pat", FolderName, mCurModelName, strType, iMarkNo);
#endif

#ifdef USE_GEOMETRIC
	if (vision.ModModel[iMarkType][iMarkNo] == M_NULL) 
	{
		return;
	}
	//MmodSave(strPatDir.GetBuffer(999), vision.ModModel[iMarkType][iMarkNo], M_DEFAULT);
	MmodSave(strPatDir, vision.ModModel[iMarkType][iMarkNo], M_DEFAULT);
#else
	if (vision.PatModel[iMarkType][iMarkNo]==M_NULL)
		return;

	MpatSave(strPatDir.GetBuffer(999), vision.PatModel[iMarkType][iMarkNo]);
#endif
}


void CModelData::loadMark(int iCamNo, int iMarkType, int iMarkNo)
{
	CString strType;
	if (iMarkType == PCB_Chip_MARK)			strType = "LENS";
	else if (iMarkType == PCB_Holder_MARK)	strType = "PCB";
	else									strType = "LENS_Edge";

	CString strPatDir;
#ifdef USE_GEOMETRIC
	//strPatDir.Format("%s\\Model\\%s\\%s_Mark_%d.mod", DATA_DIR, mCurModelName, strType, iMarkNo);
	strPatDir.Format("%s\\%s\\Data\\Mark\\%s_Mark_%d.mod", AA_MODEL_LOAD_DIR, mCurModelName, strType, iMarkNo);
#else
	strPatDir.Format("%s\\Model\\%s\\%s_Mark_%d.pat", DATA_DIR, mCurModelName, strType, iMarkNo);
#endif

	if (::_access(strPatDir, 0x00)==-1)
	{
#ifdef USE_GEOMETRIC
		vision.ModModel[iMarkType][iMarkNo] = M_NULL;
#else
		vision.PatModel[iMarkType][iMarkNo] = M_NULL;
#endif
		return;
	}
#ifdef USE_GEOMETRIC
	if (vision.ModModel[iMarkType][iMarkNo])
	{
 		MmodFree(vision.ModModel[iMarkType][iMarkNo]);
		vision.ModModel[iMarkType][iMarkNo] = M_NULL;
	}
#else
	if (vision.PatModel[iMarkType][iMarkNo])
	{
		MpatFree(vision.PatModel[iMarkType][iMarkNo]);
		vision.PatModel[iMarkType][iMarkNo] = M_NULL;
	}
#endif

#ifdef USE_GEOMETRIC
	MmodRestore(strPatDir.GetBuffer(999), vision.MilSystem, M_DEFAULT, &vision.ModModel[iMarkType][iMarkNo]);
	
#else
	MpatRestore(vision.MilSystem, strPatDir.GetBuffer(999), &vision.PatModel[iMarkType][iMarkNo]);
//	MpatDraw(M_DEFAULT, vision.PatModel[iMarkType][iMarkNo], vision.MilMarkSmallImage[iMarkType][iMarkNo], M_DRAW_IMAGE, M_DEFAULT, M_DEFAULT);
	MpatPreprocModel(vision.MilProcImageChild[iCamNo], vision.PatModel[iMarkType][iMarkNo], M_DEFAULT);
#endif
	

	/*
	//221107 여기왜있지?
	//for(int i=0;i<LAST_MARK_CNT;i++)
	//{
		//strPatDir.Format("%s\\Model\\%s\\%s_Mark_%d-Mask.pat", DATA_DIR, model.mCurModelName, strType, i);
		//MpatRestore(vision.MilSystem, strPatDir.GetBuffer(999), &vision.FieldPatternImage[i]);
	//}*/


	strType.Empty();
}

COS_Check::COS_Check()
{
	init();
}

void COS_Check::init()
{
	for (int i=0 ; i<OS_PIN_COUNT ; i++)
	{
		m_iFlag_UsePin[i]	= 1;	/* 기본적으로 모두 사용 */
		m_fUpperLimit[i]	= 0.0;
		m_fLowerLimit[i]	= 0.0;
	}
}


//=================================================================\
//만도 차량용 검사기 Log 저장
CMandoInspLog::CMandoInspLog()
{
	sBarcodeID = "EMPTY";	
	func_InitData();
}

void CMandoInspLog::func_InitData()
{
	int i = 0;
	int iNo = 0;
	::GetLocalTime(&Insptime);	//작업 시작 시간 
	m_bInspRes = false;
	bInspRes = true;
	sNGList = "";
	
	dTilteOffset[0] = dTilteOffset[1] = 0.0;
	dPCBOffset[0] = dPCBOffset[1] = dPCBOffset[2] = 0.0;
	model.m_Log_FOV_H_FOV = 0.0;
	model.m_Log_FOV_V_FOV = 0.0;
	model.m_Log_FOV_D_FOV = 0.0;
	model.m_Log_Rotate = 0.0;
	model.m_Log_SNR_DR = 0.0;
	model.m_Log_SNR_SNR = 0.0;
	dCurrent = 0.0;
	dVoltage = 0.0;
	s12C = "";
	dMTF_TotalAverage = 0.0;

	for(iNo = 0; iNo < COMMON_MTF_INSP_CNT; iNo++)
	{
		dMTF_PreUV[iNo] = 0.0;
		dMTF_PostUV[iNo] = 0.0;
	}

	for (i = 0; i < 9; i++)
	{
		MESCommunication.m_nMesBlemishMaxDefect[i] = 0.0;
	}
	for (i = 0; i < 4; i++)
	{
		dLaserTestPoint[i] = 0.0;
		dLaserTestComPoint[i] = 0.0;
	}

	dLaserTestTilt[0] = 0.0;
	dLaserTestTilt[1] = 0.0;
	
	dOpticalOc[0] = 0.0;
	dOpticalOc[1] = 0.0;


	dMtfDiff4F = 0.0;
	dMtfDiff7F = 0.0;
	dRiDiff = 0.0;
	dOCResult[0] = dOCResult[1] = 0.0;		
	dDistortion = 0.0;

	dDefect[0] = dDefect[1] = 0.0;			
	dStain[0] = dStain[1] = dStain[2] = 0.0;
	dShading65FC[0] = dShading65FC[1] = 0.0;
	dShading85FC[0] = dShading85FC[1] = 0.0;
	model.m_oc_x = 0.0;
	model.m_oc_y = 0.0;
	//! Main화면 NG List Overlay 관련 변수
	iNGCnt = 0;
	for(int iNo = 0; iNo < 100; iNo++)
	{
		sDispNG[iNo] = "";
	}
}




void CMandoInspLog::func_LogSave_UVBefore()		//UVBefore_AA시 로그  로그대대적수정(2/5)
{//UV Before Log Data 저장
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	FILE *out; 
	int i = 0;
	CFileFind finder;
	BOOL IsFind;
	CString FolderName;

	FolderName.Format("%s\\%s\\%04d%02d\\%02d", BASE_LOG_DIR, model.mCurModelName, Insptime.wYear, Insptime.wMonth, Insptime.wDay);

	IsFind = finder.FindFile(FolderName);
	if(!IsFind)
	{
		FolderName.Format("%s", BASE_DIR);
		IsFind = finder.FindFile(FolderName);
		if(!IsFind)
		{
			CreateDirectory(FolderName,NULL); 
		}

		FolderName.Format("%s", BASE_LOG_DIR);
		IsFind = finder.FindFile(FolderName);
		if(!IsFind)
		{
			CreateDirectory(FolderName,NULL); 
		}

		FolderName.Format("%s\\%s", BASE_LOG_DIR, model.mCurModelName);
		IsFind = finder.FindFile(FolderName);
		if (!IsFind)
		{
			CreateDirectory(FolderName, NULL);
		}

		FolderName.Format("%s\\%s\\%04d%02d", BASE_LOG_DIR, model.mCurModelName, Insptime.wYear, Insptime.wMonth);
		IsFind = finder.FindFile(FolderName);
		if (!IsFind)
		{
			CreateDirectory(FolderName, NULL);
		}

		FolderName.Format("%s\\%s\\%04d%02d\\%02d", BASE_LOG_DIR, model.mCurModelName, Insptime.wYear, Insptime.wMonth, Insptime.wDay);
		IsFind = finder.FindFile(FolderName);
		if (!IsFind)
		{
			CreateDirectory(FolderName, NULL);
		}

	}

	int iStepNo = Task.m_iCnt_Step_AA_Total;
	char fileName[1000];
	wsprintf(fileName, "%s\\%04d%02d%02d_AALog_UVBefore.csv", FolderName, Insptime.wYear, Insptime.wMonth, Insptime.wDay, sysData.m_iSystemNo, sysData.m_iUnitNo);

	CFile file;
	if ( finder.FindFile(fileName) == TRUE )
	{
		BOOL bFlag_File_Open = file.Open(fileName, CFile::modeRead);
		if ( bFlag_File_Open == FALSE )
		{
			sLangChange.LoadStringA(IDS_STRING1437);	//"파일이 사용 중 입니다."
			errMsg2(Task.AutoFlag, sLangChange);
			finder.Close();

			return;
		}
		else
			file.Close();
	}
	finder.Close();

	if (fopen_s(&out, fileName, "r") != NULL)
	{
		if (fopen_s(&out, fileName, "w") == NULL)
		{
			fprintf_s(out, ",,,,,Resolution,,each,,,,,,,,,,,,,,");
			fprintf_s(out, "\n");
			//
			fprintf_s(out,  "Date,Time ");
			fprintf_s(out,  ",SW Version,Model");
			fprintf_s(out,  ",BarcodeID");
			fprintf_s(out, ",X,Y");
			fprintf_s(out,  ",Width,Height");

			for (i = 0; i < model.mGlobalSmallChartCount; i++)//for (i = 0; i < MTF_INSP_CNT; i++)
			{
				_ftprintf_s(out, _T(",[SFR] Roi-%d"), i);
			}
			fprintf_s(out, "\n");
		}

		if(out)	fclose(out);
	}
	else
	{
		if(out)		fclose(out);
	}

	CString sModelName;

	if(!fopen_s(&out, fileName, "a" ))
	{
		fprintf_s(out, "%04d-%02d-%02d,",Insptime.wYear,Insptime.wMonth,Insptime.wDay);
		fprintf_s(out, "%02d:%02d:%02d,",Insptime.wHour,Insptime.wMinute,Insptime.wSecond);
		//
		fprintf_s(out, "VER.%s,%s,",VER_STR,model.mCurModelName);
		fprintf_s(out, "%s,", (LPTSTR)(LPCTSTR)sBarcodeID);
		fprintf_s(out, ",%.02lf,%.02lf", MESCommunication.m_dMesDeltaOC[0], MESCommunication.m_dMesDeltaOC[1]);//model.m_oc_x, model.m_oc_y);
		fprintf_s(out, "%d,%d",gMIUDevice.nWidth,gMIUDevice.nHeight);

		for (int i = 0; i<model.mGlobalSmallChartCount; i++)//for (int i = 0; i<MTF_INSP_CNT; i++)
		{
			fprintf_s(out, ",%.06lf", dMTF_PreUV[i]);
		}

		fprintf_s(out, "\n");

		if(out)	fclose(out);
	}

}


void CMandoInspLog::func_LogSave_UVAfter(int index)		//Final_완제품(화상검사) 로그(1/5) , AA시 로그(3/5)  : 로그대대적수정										
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	FILE *out; 
	CFileFind finder;
	BOOL IsFind;
	CString FolderName;
	char fileName[1000];
	int iStepNo = Task.m_iCnt_Step_AA_Total;
	int i = 0;
	

	FolderName.Format("%s\\%s\\%04d%02d\\%02d", BASE_LOG_DIR, model.mCurModelName, Insptime.wYear, Insptime.wMonth, Insptime.wDay);

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

		FolderName.Format("%s\\%s", BASE_LOG_DIR, model.mCurModelName);
		IsFind = finder.FindFile(FolderName);
		if (!IsFind)
		{
			CreateDirectory(FolderName, NULL);
		}

		FolderName.Format("%s\\%s\\%04d%02d", BASE_LOG_DIR, model.mCurModelName, Insptime.wYear, Insptime.wMonth);
		IsFind = finder.FindFile(FolderName);
		if (!IsFind)
		{
			CreateDirectory(FolderName, NULL);
		}
		FolderName.Format("%s\\%s\\%04d%02d\\%02d", BASE_LOG_DIR, model.mCurModelName, Insptime.wYear, Insptime.wMonth, Insptime.wDay);
		IsFind = finder.FindFile(FolderName);
		if (!IsFind)
		{
			CreateDirectory(FolderName, NULL);
		}
	}
	if (sysData.m_iProductComp == 1)//완제품일때
	{
		wsprintf(fileName, "%s\\%04d%02d%02d_EolLog_UvAfter.csv", FolderName, Insptime.wYear, Insptime.wMonth, Insptime.wDay);
	}
	else
	{
		wsprintf(fileName, "%s\\%04d%02d%02d_AALog_UvAfter.csv", FolderName, Insptime.wYear, Insptime.wMonth, Insptime.wDay);
	}
	

	CFile file;
	if (finder.FindFile(fileName) == TRUE)
	{
		BOOL bFlag_File_Open = file.Open(fileName, CFile::modeRead);
		if (bFlag_File_Open == FALSE)
		{
			sLangChange.LoadStringA(IDS_STRING1437);	//"파일이 사용 중 입니다."
			errMsg2(Task.AutoFlag, sLangChange);
			finder.Close();

			return;
		}
		else
			file.Close();
	}
	finder.Close();



	if (fopen_s(&out, fileName, "r") != NULL)
	{
		if (fopen_s(&out, fileName, "w") == NULL)
		{
			fprintf_s(out, ",,,,,,,OC,,,Resolution,,each");
			//
			fprintf_s(out, "\n");
			//
			fprintf_s(out,  "Date,Time");
			fprintf_s(out,  ",SW Version,Model");

			fprintf_s(out,  ",BarcodeID"); 

			fprintf_s(out,	",OTP PartNumber");
			fprintf_s(out,	",SensorID");
			fprintf_s(out,	",FW Version");
			fprintf_s(out,	",OTP Write");
			fprintf_s(out,	",OTP Verify");
			
			fprintf_s(out,  ",Judge,NGList");
			fprintf_s(out,  ",CHART OC X, CHART OC Y");
			fprintf_s(out,  ",Rotation,Width,Height");

			
			for (i = 0; i < model.mGlobalSmallChartCount; i++)//for (i = 0; i < MTF_INSP_CNT; i++)
			{
				_ftprintf_s(out, _T(",[SFR] Roi-%d"), i);
			}

			fprintf_s(out, ",[Laser] Point1 LT,[Laser] Point2 RT,[Laser] Point3 RB,[Laser] Point4 LB");
			fprintf_s(out, ",[Laser] Side Point1 LT,[Laser] Side Point2 RT,[Laser] Side Point3 RB,[Laser] Side Point4 LB");
			fprintf_s(out, ",[Laser] Tilt Tx,[Laser] Tilt Ty");
			fprintf_s(out, ",[OC] X,[OC] Y");
			//_T("TOP_CHART_L"), _T("TOP_CHART_T"), _T("TOP_CHART_R"), 	_T("LEFT_SIDE_CHART_4F_T") ,
			//_T("LEFT_SIDE_CHART_7F_T"),
			//	_T("LEFT_SIDE_CHART_7F_M")
			//_ftprintf_s(out, _T(",[Blemish] LCB,[Blemish] RU_Ymean,[Blemish] FDF"));

			//_ftprintf_s(out, _T(",[Blemish] LCB ,[Blemish] Ymean ,[Blemish] FPF"));
			//_ftprintf_s(out, _T(",[Blemish] FDF Max Value(Center) ,[Blemish] FDF Max Value(Edge) ,[Blemish] FDF Max Value(Corner)"));
			//_ftprintf_s(out, _T(",[Blemish] LCB Max Value(Center) ,[Blemish] LCB Max Value(Edge) ,[Blemish] LCB Max Value(Corner)"));
			//_ftprintf_s(out, _T(",[Blemish] Ymean Max Value(Center) ,[Blemish] Ymean Max Value(Edge) ,[Blemish] Ymean Max Value(Corner)"));
			////

			//fprintf_s(out, ",Diff4F,Diff7F,RIDiff");
			//fprintf_s(out, ",RIconer0,RIconer1,RIconer2,RIconer3");
			//fprintf_s(out, ",Voltage,Current");
			//fprintf_s(out, ",ColorReproduction ROI 1,ColorReproduction ROI 2,ColorReproduction ROI 3,ColorReproduction ROI 4");

			fprintf_s(out, "\n");
		}

		if(out)	fclose(out);
	}
	else
	{
		if(out)		fclose(out);
	}
	CString sModelName;
	if(!fopen_s(&out, fileName, "a" ))
	{
		fprintf_s(out, "%04d-%02d-%02d,",Insptime.wYear,Insptime.wMonth,Insptime.wDay);
		fprintf_s(out, "%02d:%02d:%02d,",Insptime.wHour,Insptime.wMinute,Insptime.wSecond);
		//
		fprintf_s(out, "VER.%s,%s,",VER_STR,model.mCurModelName);
		fprintf_s(out, "%s,", (LPTSTR)(LPCTSTR)sBarcodeID);  
		fprintf_s(out, "%s,", (LPTSTR)(LPCTSTR)MESCommunication.partNumber);
		fprintf_s(out, "%s,", (LPTSTR)(LPCTSTR)MESCommunication.sensorId);
		fprintf_s(out, "%s,", (LPTSTR)(LPCTSTR)MESCommunication.fwVersion);
		fprintf_s(out, "%s,", (LPTSTR)(LPCTSTR)MESCommunication.OTPWriteFail);
		fprintf_s(out, "%s,", (LPTSTR)(LPCTSTR)MESCommunication.OTPVerifyFail);

		if( bInspRes == true )		fprintf_s(out, "OK, %s", (LPTSTR)(LPCTSTR)sNGList);
		else						fprintf_s(out, "NG, %s", (LPTSTR)(LPCTSTR)sNGList);
		
		fprintf_s(out, ",%.02lf,%.02lf", MESCommunication.m_dMesDeltaOC[0], MESCommunication.m_dMesDeltaOC[1]);//model.m_oc_x, model.m_oc_y);
		fprintf_s(out, ",%.03lf,%d,%d",Task.dLensRotation, gMIUDevice.nWidth, gMIUDevice.nHeight);//0.00 = Rotation
		
		for (i = 0; i<model.mGlobalSmallChartCount ; i++)//for(int i=0; i<MTF_INSP_CNT; i++)
		{
			fprintf_s(out, ",%.06lf",dMTF_PostUV[i]);//완제품일때 12포인트 MTF
		}
		for (i = 0; i < 4; i++)
		{
			fprintf_s(out, ",%.06lf", dLaserTestPoint[i]);
		}
		for (i = 0; i < 4; i++)
		{
			fprintf_s(out, ",%.06lf", dLaserTestComPoint[i]);
		}
		
		fprintf_s(out, ",%.06lf", dLaserTestTilt[0]);
		fprintf_s(out, ",%.06lf", dLaserTestTilt[1]);

		fprintf_s(out, ",%.06lf,%.06lf", MandoInspLog.dOpticalOc[0], MandoInspLog.dOpticalOc[1]);
		
		/*fprintf_s(out, ",%d,%d,%d", MESCommunication.m_nMesBlemish[0], MESCommunication.m_nMesBlemish[1], MESCommunication.m_nMesBlemish[2]);
		for (int i = 0; i < 9; i++)
		{
			fprintf_s(out, ",%.06lf", MESCommunication.m_nMesBlemishMaxDefect[i]);
		}*/

		//fprintf_s(out, ",%.06lf,%.06lf,%.06lf", dMtfDiff4F, dMtfDiff7F, dRiDiff);
		//fprintf_s(out, ",%.06lf,%.06lf,%.06lf,%.06lf", dRicorner[0], dRicorner[1], dRicorner[2], dRicorner[3]);
		//fprintf_s(out, ",%.06lf,%.06lf", dVoltage, dCurrent);
		//fprintf_s(out, ",%.06lf,%.06lf,%.06lf,%.06lf", dColorReproduction[0], dColorReproduction[1], dColorReproduction[2], dColorReproduction[3]);

		fprintf_s(out, "\n");
		
		if(out)	fclose(out);
	}

}

void CMandoInspLog::func_DrawNG_Overlay(int iCh)
{
	CString sLog;
	int iGapY = 60;//120;
	int iSX = 10;
	int iSY= 400;//700;//400;

	int iCurX, iCurY;
	iCurX = iSX;

	int iListNo = 0;

	for(int iNo = 0; iNo < iNGCnt; iNo++)
	{
		iCurY = iSY + (iGapY*iListNo);
		
		if(iCurY > (int) CAM_SIZE_Y + 2000)
		{
			iListNo = 0;
			iCurY = iSY + (iGapY*iListNo);
			iCurX += CAM_SIZE_X/2;	//내용이 많을 경우 2줄로 표시 하기 위해
		}
		// 20141110 LHC - NG 목록 Display 시 글자크기 크게 변경.
		//vision.textlist[iCh].addList(iCurX, iCurY, sDispNG[iNo], M_COLOR_RED, 12, 8, "Arial");
		vision.textlist[iCh].addList(iCurX, iCurY, sDispNG[iNo], M_COLOR_RED, 18, 10, "Arial");
		iListNo++;
	}
}
CMandoSfrSpec::CMandoSfrSpec()
{
	for(int j = 0; j<24; j++)
	{
		for(int i = 0; i < 3; i++)
		{
			dAASFR_Spec[j][i] = 0.227;
				
		}
	}
	for( int i = 0; i< 24; i++ )
	{
		for(int k = 0; k < 3; k++)
		{
			dINSPSFR_Spec[i][k] = 0.11;
		}
	}

	Insp60Lp = 0;
	Insp67Lp = 0;
	InspCp = 1;

	INSP_AAmode_OC_Min_Spec = -15.0;
	INSP_AAmode_OC_Max_Spec = 15.0;
	INSP_Procmode_OC_Min_Spec = -15.0;
	INSP_Procmode_OC_Max_Spec = 15.0;

	INSP_Diff_Spec[0] = 0.25;
	INSP_Diff_Spec[1] = 0.30;

	INSP_RIDiff_Spec = 70.0;

	INSP_Voltage_Spec = 0.0;
	INSP_Current_Spec = 0.0;

	INSP_SfrDeltaAlgorithmType = 0;
	INSP_SfrGamma = 0.0;
	INSP_SfrMaxEdgeAngle = 0.0;
	INSP_SfrAlgorithmType = 0;
	INSP_SfrAlgorithmMethod = 0;
	INSP_SfrFrequencyUnit = 0;
	for (int i = 0; i > 4; i++)
	{
		INSP_SfrInspOffset[i] = 0.0;
	}

	INSP_OCCenterSpecX = 0.0;
	INSP_OCCenterSpecY = 0.0;
	INSP_OCThresholdRatio = 0.0;
	INSP_OCRoiCount = 0;
	INSP_OCEdgeTopMargin = 0;
	INSP_OCBlockSize = 0;
	for (int i = 0; i > 4; i++)
	{
		INSP_OCInspOffset[i] = 0.0;
	}
	
}
void CMandoSfrSpec::NewSfrSave()
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szData[SIZE_OF_1K];
	TCHAR szIniIndex[SIZE_OF_100BYTE];
	TCHAR szIniBuff[SIZE_OF_1K];
	CString sToken = _T("");
	int i, j;
	int nPosi = 0;
	CFileFind clFinder;
	if (clFinder.FindFile(AA_MODEL_LOAD_DIR) == FALSE)
	{
		CreateDirectory(AA_MODEL_LOAD_DIR, NULL);
	}


	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\%s\\Data\\SfrSpec.ini"), AA_MODEL_LOAD_DIR, model.mCurModelName);

	for (i = 0; i < COMMON_MTF_INSP_CNT; i++)
	{
		_stprintf_s(szData, SIZE_OF_1K, _T("%lf / %lf / %lf"), dAASFR_Spec[i][0], dAASFR_Spec[i][1], dAASFR_Spec[i][2]);
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("ROI%d"), i);
		WritePrivateProfileString(_T("SFR_SPEC"), szIniIndex, szData, szPath);
	}


	_stprintf_s(szData, SIZE_OF_1K, _T("%lf"), INSP_AAmode_OC_Max_Spec);
	WritePrivateProfileString(_T("OC"), _T("AA_MAX"), szData, szPath);
	_stprintf_s(szData, SIZE_OF_1K, _T("%lf"), INSP_AAmode_OC_Min_Spec);
	WritePrivateProfileString(_T("OC"), _T("AA_MIN"), szData, szPath);
	_stprintf_s(szData, SIZE_OF_1K, _T("%lf"), INSP_Procmode_OC_Max_Spec);
	WritePrivateProfileString(_T("OC"), _T("COMP_MAX"), szData, szPath);
	_stprintf_s(szData, SIZE_OF_1K, _T("%lf"), INSP_Procmode_OC_Min_Spec);
	WritePrivateProfileString(_T("OC"), _T("COMP_MIN"), szData, szPath);


	_stprintf_s(szData, SIZE_OF_1K, _T("%lf"), Rotation_Spec);
	WritePrivateProfileString(_T("ROTATION"), _T("MAX"), szData, szPath);


	_stprintf_s(szData, SIZE_OF_1K, _T("%lf"), INSP_Diff_Spec[0]);
	WritePrivateProfileString(_T("DIFF4F"), _T("MAX"), szData, szPath);
	_stprintf_s(szData, SIZE_OF_1K, _T("%lf"), INSP_Diff_Spec[1]);
	WritePrivateProfileString(_T("DIFF7F"), _T("MAX"), szData, szPath);


	_stprintf_s(szData, SIZE_OF_1K, _T("%lf"), INSP_RIDiff_Spec);
	WritePrivateProfileString(_T("RIDIFF"), _T("MAX"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%lf"), INSP_Current_Spec);
	WritePrivateProfileString(_T("CURRENT"), _T("MAX"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%lf"), INSP_Voltage_Spec);
	WritePrivateProfileString(_T("VOLTAGE"), _T("MAX"), szData, szPath);
	
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), INSP_SfrDeltaAlgorithmType);
	WritePrivateProfileString(_T("SFR"), _T("DELTA_ALGORITHM"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%lf"), INSP_SfrGamma);
	WritePrivateProfileString(_T("SFR"), _T("GAMMA"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%lf"), INSP_SfrMaxEdgeAngle);
	WritePrivateProfileString(_T("SFR"), _T("MAX_EDGEANGLE"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), INSP_SfrAlgorithmType);
	WritePrivateProfileString(_T("SFR"), _T("ALGORITHM"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), INSP_SfrAlgorithmMethod);
	WritePrivateProfileString(_T("SFR"), _T("ALGORITHM_METHOD"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), INSP_SfrFrequencyUnit);
	WritePrivateProfileString(_T("SFR"), _T("FREQUENCY_UNIT"), szData, szPath);

	for (i = 0; i < 4; i++)
	{
		_stprintf_s(szData, SIZE_OF_1K, _T("%lf"), INSP_SfrInspOffset[i]);
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("OFFSET %d"), i);
		WritePrivateProfileString(_T("SFR_INSP_OFFSET"), szIniIndex, szData, szPath);
	}

	_stprintf_s(szData, SIZE_OF_1K, _T("%lf"), INSP_OCCenterSpecX);
	WritePrivateProfileString(_T("OC"), _T("CENTER_SPEC_X"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%lf"), INSP_OCCenterSpecY);
	WritePrivateProfileString(_T("OC"), _T("CENTER_SPEC_Y"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%lf"), INSP_OCThresholdRatio);
	WritePrivateProfileString(_T("OC"), _T("THRESHOLD_RATIO"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), INSP_OCRoiCount);
	WritePrivateProfileString(_T("OC"), _T("ROI_COUNT"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), INSP_OCEdgeTopMargin);
	WritePrivateProfileString(_T("OC"), _T("EDGE_TOP_MARGIN"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), INSP_OCBlockSize);
	WritePrivateProfileString(_T("OC"), _T("BLOCK_SIZE"), szData, szPath);

	for (i = 0; i < 4; i++)
	{
		_stprintf_s(szData, SIZE_OF_1K, _T("%lf"), INSP_OCInspOffset[i]);
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("OFFSET %d"), i);
		WritePrivateProfileString(_T("OC_INSP_OFFSET"), szIniIndex, szData, szPath);
	}
}
void CMandoSfrSpec::NewSfrLoad()
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szIniIndex[SIZE_OF_100BYTE];
	TCHAR szIniBuff[SIZE_OF_1K];
	CString sToken = _T("");
	int i, j, k;

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\%s\\Data\\SfrSpec.ini"), AA_MODEL_LOAD_DIR, model.mCurModelName);

	for (i = 0; i < COMMON_MTF_INSP_CNT; i++)
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("ROI%d"), i);
		GetPrivateProfileString(_T("SFR_SPEC"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		for (j = 0; j < 4; j++)
		{
			AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
			switch (j)
			{
				case 0:		dAASFR_Spec[i][0] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
				case 1:		dAASFR_Spec[i][1] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
				case 2:		dAASFR_Spec[i][2] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
			}
		}
	}

	GetPrivateProfileString(_T("OC"), _T("AA_MAX"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	INSP_AAmode_OC_Max_Spec = _ttof(szIniBuff);

	GetPrivateProfileString(_T("OC"), _T("AA_MIN"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	INSP_AAmode_OC_Min_Spec = _ttof(szIniBuff);

	GetPrivateProfileString(_T("OC"), _T("COMP_MAX"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	INSP_Procmode_OC_Max_Spec = _ttof(szIniBuff);

	GetPrivateProfileString(_T("OC"), _T("COMP_MIN"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	INSP_Procmode_OC_Min_Spec = _ttof(szIniBuff);

	GetPrivateProfileString(_T("ROTATION"), _T("MAX"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	Rotation_Spec = _ttof(szIniBuff);

	GetPrivateProfileString(_T("DIFF4F"), _T("MAX"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	INSP_Diff_Spec[0] = _ttof(szIniBuff);

	GetPrivateProfileString(_T("DIFF7F"), _T("MAX"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	INSP_Diff_Spec[1] = _ttof(szIniBuff);

	GetPrivateProfileString(_T("RIDIFF"), _T("MAX"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	INSP_RIDiff_Spec = _ttof(szIniBuff);
	
	GetPrivateProfileString(_T("CURRENT"), _T("MAX"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	INSP_Current_Spec = _ttof(szIniBuff);
	GetPrivateProfileString(_T("VOLTAGE"), _T("MAX"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	INSP_Voltage_Spec = _ttof(szIniBuff);

	GetPrivateProfileString(_T("SFR"), _T("DELTA_ALGORITHM"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	INSP_SfrDeltaAlgorithmType = _ttof(szIniBuff);

	GetPrivateProfileString(_T("SFR"), _T("GAMMA"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	INSP_SfrGamma = _ttof(szIniBuff);

	GetPrivateProfileString(_T("SFR"), _T("MAX_EDGEANGLE"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	INSP_SfrMaxEdgeAngle = _ttof(szIniBuff);

	GetPrivateProfileString(_T("SFR"), _T("ALGORITHM"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	INSP_SfrAlgorithmType = _ttof(szIniBuff);

	GetPrivateProfileString(_T("SFR"), _T("ALGORITHM_METHOD"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	INSP_SfrAlgorithmMethod = _ttof(szIniBuff);

	GetPrivateProfileString(_T("SFR"), _T("FREQUENCY_UNIT"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	INSP_SfrFrequencyUnit = _ttof(szIniBuff);

	for (i = 0; i < 4; i++)
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("OFFSET %d"), i);
		GetPrivateProfileString(_T("SFR_INSP_OFFSET"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		INSP_SfrInspOffset[i] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
	}

	GetPrivateProfileString(_T("OC"), _T("CENTER_SPEC_X"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	INSP_OCCenterSpecX = _ttof(szIniBuff);

	GetPrivateProfileString(_T("OC"), _T("CENTER_SPEC_Y"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	INSP_OCCenterSpecY = _ttof(szIniBuff);

	GetPrivateProfileString(_T("OC"), _T("THRESHOLD_RATIO"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	INSP_OCThresholdRatio = _ttof(szIniBuff);

	GetPrivateProfileString(_T("OC"), _T("ROI_COUNT"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	INSP_OCRoiCount = _ttof(szIniBuff);

	GetPrivateProfileString(_T("OC"), _T("EDGE_TOP_MARGIN"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	INSP_OCEdgeTopMargin = _ttof(szIniBuff);

	GetPrivateProfileString(_T("OC"), _T("BLOCK_SIZE"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	INSP_OCBlockSize = _ttof(szIniBuff);

	for (i = 0; i < 4; i++)
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("OFFSET %d"), i);
		GetPrivateProfileString(_T("OC_INSP_OFFSET"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		INSP_OCInspOffset[i] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
	}

}

void CMandoSfrSpec::save()
{
	FILE *out;

	CFileFind finder;
	BOOL IsFind;
	CString FolderName, FolderName_D, backupFolderName_C, backupFolderName_D;
	//CString backupFolderName;	//0114 hyo

	SYSTEMTIME SysTime;
	::GetLocalTime(&SysTime);

	FolderName.Format("%s\\%s\\Data", AA_MODEL_LOAD_DIR, model.mCurModelName);
	IsFind = finder.FindFile(FolderName);
	if(!IsFind)
	{
		FolderName.Format("%s", BASE_DIR);
		CreateDirectory(FolderName,NULL); 

		FolderName.Format("%s", AA_MODEL_LOAD_DIR);
		CreateDirectory(FolderName, NULL);

		FolderName.Format("%s\\%s", AA_MODEL_LOAD_DIR, model.mCurModelName);
		CreateDirectory(FolderName, NULL);

		FolderName.Format("%s\\%s\\Data", AA_MODEL_LOAD_DIR, model.mCurModelName);
		CreateDirectory(FolderName, NULL);
	}

	finder.Close();

	char	fileName[1000];
	wsprintf(fileName, "%s\\SfrSpec.txt", FolderName);

	if(fopen_s(&out, fileName,"w"))
	{
		sLangChange.LoadStringA(IDS_STRING1083);
		errMsg2(Task.AutoFlag, _T("SfrSpec Save Fail..."));
	}
	else
	{
		fprintf_s(out,"0.0F_TV   %lf %lf %lf %lf\n",  dAASFR_Spec[0][0], dAASFR_Spec[0][1], dAASFR_Spec[0][2], dAASFR_Spec[0][3]);
		fprintf_s(out, "0.0F_BV   %lf %lf %lf %lf\n", dAASFR_Spec[1][0], dAASFR_Spec[1][1], dAASFR_Spec[1][2], dAASFR_Spec[1][3]);
		fprintf_s(out, "0.0F_LH   %lf %lf %lf %lf\n", dAASFR_Spec[2][0], dAASFR_Spec[2][1], dAASFR_Spec[2][2], dAASFR_Spec[2][3]);
		fprintf_s(out, "0.0F_RH   %lf %lf %lf %lf\n", dAASFR_Spec[3][0], dAASFR_Spec[3][1], dAASFR_Spec[3][2], dAASFR_Spec[3][3]);
		fprintf_s(out, "0.5F_UL_H %lf %lf %lf %lf\n", dAASFR_Spec[4][0], dAASFR_Spec[4][1], dAASFR_Spec[4][2], dAASFR_Spec[4][3]);
		fprintf_s(out, "0.5F_UL_V %lf %lf %lf %lf\n", dAASFR_Spec[5][0], dAASFR_Spec[5][1], dAASFR_Spec[5][2], dAASFR_Spec[5][3]);
		fprintf_s(out, "0.5F_UR_H %lf %lf %lf %lf\n", dAASFR_Spec[6][0], dAASFR_Spec[6][1], dAASFR_Spec[6][2], dAASFR_Spec[6][3]);
		fprintf_s(out, "0.5F_UR_V %lf %lf %lf %lf\n", dAASFR_Spec[7][0], dAASFR_Spec[7][1], dAASFR_Spec[7][2], dAASFR_Spec[7][3]);
		fprintf_s(out, "0.5F_LL_H %lf %lf %lf %lf\n", dAASFR_Spec[8][0], dAASFR_Spec[8][1], dAASFR_Spec[8][2], dAASFR_Spec[8][3]);
		fprintf_s(out, "0.5F_LL_V %lf %lf %lf %lf\n", dAASFR_Spec[9][0], dAASFR_Spec[9][1], dAASFR_Spec[9][2], dAASFR_Spec[9][3]);
		fprintf_s(out, "0.5F_LR_H %lf %lf %lf %lf\n", dAASFR_Spec[10][0], dAASFR_Spec[10][1], dAASFR_Spec[10][2], dAASFR_Spec[10][3]);
		fprintf_s(out, "0.5F_LR_V %lf %lf %lf %lf\n", dAASFR_Spec[11][0], dAASFR_Spec[11][1], dAASFR_Spec[11][2], dAASFR_Spec[11][3]);
		fprintf_s(out, "0.7F_UL_H %lf %lf %lf %lf\n", dAASFR_Spec[12][0], dAASFR_Spec[12][1], dAASFR_Spec[12][2], dAASFR_Spec[12][3]);
		fprintf_s(out, "0.7F_UL_V %lf %lf %lf %lf\n", dAASFR_Spec[13][0], dAASFR_Spec[13][1], dAASFR_Spec[13][2], dAASFR_Spec[13][3]);
		fprintf_s(out, "0.7F_UR_H %lf %lf %lf %lf\n", dAASFR_Spec[14][0], dAASFR_Spec[14][1], dAASFR_Spec[14][2], dAASFR_Spec[14][3]);
		fprintf_s(out, "0.7F_UR_V %lf %lf %lf %lf\n", dAASFR_Spec[15][0], dAASFR_Spec[15][1], dAASFR_Spec[15][2], dAASFR_Spec[15][3]);
		fprintf_s(out, "0.7F_LL_H %lf %lf %lf %lf\n", dAASFR_Spec[16][0], dAASFR_Spec[16][1], dAASFR_Spec[16][2], dAASFR_Spec[16][3]);
		fprintf_s(out, "0.7F_LL_V %lf %lf %lf %lf\n", dAASFR_Spec[17][0], dAASFR_Spec[17][1], dAASFR_Spec[17][2], dAASFR_Spec[17][3]);
		fprintf_s(out, "0.7F_LR_H %lf %lf %lf %lf\n", dAASFR_Spec[18][0], dAASFR_Spec[18][1], dAASFR_Spec[18][2], dAASFR_Spec[18][3]);
		fprintf_s(out, "0.7F_LR_V %lf %lf %lf %lf\n", dAASFR_Spec[19][0], dAASFR_Spec[19][1], dAASFR_Spec[19][2], dAASFR_Spec[19][3]);
		fprintf_s(out, "0.8F_UL_H %lf %lf %lf %lf\n", dAASFR_Spec[20][0], dAASFR_Spec[20][1], dAASFR_Spec[20][2], dAASFR_Spec[20][3]);
		fprintf_s(out, "0.8F_UL_V %lf %lf %lf %lf\n", dAASFR_Spec[21][0], dAASFR_Spec[21][1], dAASFR_Spec[21][2], dAASFR_Spec[21][3]);
		fprintf_s(out, "0.8F_UR_H %lf %lf %lf %lf\n", dAASFR_Spec[22][0], dAASFR_Spec[22][1], dAASFR_Spec[22][2], dAASFR_Spec[22][3]);
		fprintf_s(out, "0.8F_UR_V %lf %lf %lf %lf\n", dAASFR_Spec[23][0], dAASFR_Spec[23][1], dAASFR_Spec[23][2], dAASFR_Spec[23][3]);
		fprintf_s(out, "0.8F_LL_H %lf %lf %lf %lf\n", dAASFR_Spec[24][0], dAASFR_Spec[24][1], dAASFR_Spec[24][2], dAASFR_Spec[24][3]);
		fprintf_s(out, "0.8F_LL_V %lf %lf %lf %lf\n", dAASFR_Spec[25][0], dAASFR_Spec[25][1], dAASFR_Spec[25][2], dAASFR_Spec[25][3]);
		fprintf_s(out, "0.8F_LR_H %lf %lf %lf %lf\n", dAASFR_Spec[26][0], dAASFR_Spec[26][1], dAASFR_Spec[26][2], dAASFR_Spec[26][3]);
		fprintf_s(out, "0.8F_LR_V %lf %lf %lf %lf\n", dAASFR_Spec[27][0], dAASFR_Spec[27][1], dAASFR_Spec[27][2], dAASFR_Spec[27][3]);
		fprintf_s(out, "0.9F_UL_H %lf %lf %lf %lf\n", dAASFR_Spec[28][0], dAASFR_Spec[28][1], dAASFR_Spec[28][2], dAASFR_Spec[28][3]);
		fprintf_s(out, "0.9F_UL_V %lf %lf %lf %lf\n", dAASFR_Spec[29][0], dAASFR_Spec[29][1], dAASFR_Spec[29][2], dAASFR_Spec[29][3]);
		fprintf_s(out, "0.9F_UR_H %lf %lf %lf %lf\n", dAASFR_Spec[30][0], dAASFR_Spec[30][1], dAASFR_Spec[30][2], dAASFR_Spec[30][3]);
		fprintf_s(out, "0.9F_UR_V %lf %lf %lf %lf\n", dAASFR_Spec[31][0], dAASFR_Spec[31][1], dAASFR_Spec[31][2], dAASFR_Spec[31][3]);
		fprintf_s(out, "0.9F_LL_H %lf %lf %lf %lf\n", dAASFR_Spec[32][0], dAASFR_Spec[32][1], dAASFR_Spec[32][2], dAASFR_Spec[32][3]);
		fprintf_s(out, "0.9F_LL_V %lf %lf %lf %lf\n", dAASFR_Spec[33][0], dAASFR_Spec[33][1], dAASFR_Spec[33][2], dAASFR_Spec[33][3]);
		fprintf_s(out, "0.9F_LR_H %lf %lf %lf %lf\n", dAASFR_Spec[34][0], dAASFR_Spec[34][1], dAASFR_Spec[34][2], dAASFR_Spec[34][3]);
		fprintf_s(out, "0.9F_LR_V %lf %lf %lf %lf\n", dAASFR_Spec[35][0], dAASFR_Spec[35][1], dAASFR_Spec[35][2], dAASFR_Spec[35][3]);

	
		

		fprintf_s(out,"OC_SPEC_AA_MAX   %lf\n",					INSP_AAmode_OC_Max_Spec);
		fprintf_s(out,"OC_SPEC_AA_MIN	%lf\n",					INSP_AAmode_OC_Min_Spec);
		fprintf_s(out,"OC_SPEC_PROC_MAX	%lf\n",					INSP_Procmode_OC_Max_Spec);
		fprintf_s(out,"OC_SPEC_PROC_MIN	%lf\n",					INSP_Procmode_OC_Min_Spec);
		fprintf_s(out,"INSP_ROTATION_SPEC	%lf\n",				Rotation_Spec);
		if(out)	fclose(out);
	}
}

void CMandoSfrSpec::load()
{
	FILE* in;

	char	Line[500];
	char	Title[500];	
	int		nRtn;

	char	fileName[1000];	

	wsprintf(fileName, "%s\\%s\\Data\\SfrSpec.txt", AA_MODEL_LOAD_DIR, model.mCurModelName);

	if(!fopen_s(&in, fileName,"r"))
	{
		while (1)
		{
			fgets(Line, 499, in);
			nRtn = sscanf_s(Line, "%s", &Title, 499);

			if (nRtn==EOF)	
				break;

			if     ( strcmp(Title, "0.0F_TV") == 0)		sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[0][0], &dAASFR_Spec[0][1], &dAASFR_Spec[0][2], &dAASFR_Spec[0][3]);
			else if (strcmp(Title, "0.0F_BV") == 0)		sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[1][0], &dAASFR_Spec[1][1], &dAASFR_Spec[1][2], &dAASFR_Spec[1][3]);
			else if (strcmp(Title, "0.0F_LH") == 0)		sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[2][0], &dAASFR_Spec[2][1], &dAASFR_Spec[2][2], &dAASFR_Spec[2][3]);
			else if (strcmp(Title, "0.0F_RH") == 0)		sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[3][0], &dAASFR_Spec[3][1], &dAASFR_Spec[3][2], &dAASFR_Spec[3][3]);
			else if (strcmp(Title, "0.5F_UL_H") == 0)	sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[4][0], &dAASFR_Spec[4][1], &dAASFR_Spec[4][2], &dAASFR_Spec[4][3]);
			else if (strcmp(Title, "0.5F_UL_V") == 0)	sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[5][0], &dAASFR_Spec[5][1], &dAASFR_Spec[5][2], &dAASFR_Spec[5][3]);
			else if (strcmp(Title, "0.5F_UR_H") == 0)	sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[6][0], &dAASFR_Spec[6][1], &dAASFR_Spec[6][2], &dAASFR_Spec[6][3]);
			else if (strcmp(Title, "0.5F_UR_V") == 0)	sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[7][0], &dAASFR_Spec[7][1], &dAASFR_Spec[7][2], &dAASFR_Spec[7][3]);
			else if (strcmp(Title, "0.5F_LL_H") == 0)	sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[8][0], &dAASFR_Spec[8][1], &dAASFR_Spec[8][2], &dAASFR_Spec[8][3]);
			else if (strcmp(Title, "0.5F_LL_V") == 0)	sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[9][0], &dAASFR_Spec[9][1], &dAASFR_Spec[9][2], &dAASFR_Spec[9][3]);
			else if (strcmp(Title, "0.5F_LR_H") == 0)	sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[10][0], &dAASFR_Spec[10][1], &dAASFR_Spec[10][2], &dAASFR_Spec[10][3]);
			else if (strcmp(Title, "0.5F_LR_V") == 0)	sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[11][0], &dAASFR_Spec[11][1], &dAASFR_Spec[11][2], &dAASFR_Spec[11][3]);
			else if (strcmp(Title, "0.7F_UL_H") == 0)	sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[12][0], &dAASFR_Spec[12][1], &dAASFR_Spec[12][2], &dAASFR_Spec[12][3]);
			else if (strcmp(Title, "0.7F_UL_V") == 0)	sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[13][0], &dAASFR_Spec[13][1], &dAASFR_Spec[13][2], &dAASFR_Spec[13][3]);
			else if (strcmp(Title, "0.7F_UR_H") == 0)	sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[14][0], &dAASFR_Spec[14][1], &dAASFR_Spec[14][2], &dAASFR_Spec[14][3]);
			else if (strcmp(Title, "0.7F_UR_V") == 0)	sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[15][0], &dAASFR_Spec[15][1], &dAASFR_Spec[15][2], &dAASFR_Spec[15][3]);
			else if (strcmp(Title, "0.7F_LL_H") == 0)	sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[16][0], &dAASFR_Spec[16][1], &dAASFR_Spec[16][2], &dAASFR_Spec[16][3]);
			else if (strcmp(Title, "0.7F_LL_V") == 0)	sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[17][0], &dAASFR_Spec[17][1], &dAASFR_Spec[17][2], &dAASFR_Spec[17][3]);
			else if (strcmp(Title, "0.7F_LR_H") == 0)	sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[18][0], &dAASFR_Spec[18][1], &dAASFR_Spec[18][2], &dAASFR_Spec[18][3]);
			else if (strcmp(Title, "0.7F_LR_V") == 0)	sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[19][0], &dAASFR_Spec[19][1], &dAASFR_Spec[19][2], &dAASFR_Spec[19][3]);
			else if (strcmp(Title, "0.8F_UL_H") == 0)	sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[20][0], &dAASFR_Spec[20][1], &dAASFR_Spec[20][2], &dAASFR_Spec[20][3]);
			else if (strcmp(Title, "0.8F_UL_V") == 0)	sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[21][0], &dAASFR_Spec[21][1], &dAASFR_Spec[21][2], &dAASFR_Spec[21][3]);
			else if (strcmp(Title, "0.8F_UR_H") == 0)	sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[22][0], &dAASFR_Spec[22][1], &dAASFR_Spec[22][2], &dAASFR_Spec[22][3]);
			else if (strcmp(Title, "0.8F_UR_V") == 0)	sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[23][0], &dAASFR_Spec[23][1], &dAASFR_Spec[23][2], &dAASFR_Spec[23][3]);
			else if (strcmp(Title, "0.8F_LL_H") == 0)	sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[24][0], &dAASFR_Spec[24][1], &dAASFR_Spec[24][2], &dAASFR_Spec[24][3]);
			else if (strcmp(Title, "0.8F_LL_V") == 0)	sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[25][0], &dAASFR_Spec[25][1], &dAASFR_Spec[25][2], &dAASFR_Spec[25][3]);
			else if (strcmp(Title, "0.8F_LR_H") == 0)	sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[26][0], &dAASFR_Spec[26][1], &dAASFR_Spec[26][2], &dAASFR_Spec[26][3]);
			else if (strcmp(Title, "0.8F_LR_V") == 0)	sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[27][0], &dAASFR_Spec[27][1], &dAASFR_Spec[27][2], &dAASFR_Spec[27][3]);
			else if (strcmp(Title, "0.9F_UL_H") == 0)	sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[28][0], &dAASFR_Spec[28][1], &dAASFR_Spec[28][2], &dAASFR_Spec[28][3]);
			else if (strcmp(Title, "0.9F_UL_V") == 0)	sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[29][0], &dAASFR_Spec[29][1], &dAASFR_Spec[29][2], &dAASFR_Spec[29][3]);
			else if (strcmp(Title, "0.9F_UR_H") == 0)	sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[30][0], &dAASFR_Spec[30][1], &dAASFR_Spec[30][2], &dAASFR_Spec[30][3]);
			else if (strcmp(Title, "0.9F_UR_V") == 0)	sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[31][0], &dAASFR_Spec[31][1], &dAASFR_Spec[31][2], &dAASFR_Spec[31][3]);
			else if (strcmp(Title, "0.9F_LL_H") == 0)	sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[32][0], &dAASFR_Spec[32][1], &dAASFR_Spec[32][2], &dAASFR_Spec[32][3]);
			else if (strcmp(Title, "0.9F_LL_V") == 0)	sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[33][0], &dAASFR_Spec[33][1], &dAASFR_Spec[33][2], &dAASFR_Spec[33][3]);
			else if (strcmp(Title, "0.9F_LR_H") == 0)	sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[34][0], &dAASFR_Spec[34][1], &dAASFR_Spec[34][2], &dAASFR_Spec[34][3]);
			else if (strcmp(Title, "0.9F_LR_V") == 0)	sscanf_s(Line, "%s %lf %lf %lf %lf", Title, 499, &dAASFR_Spec[35][0], &dAASFR_Spec[35][1], &dAASFR_Spec[35][2], &dAASFR_Spec[35][3]);

			

			else if ( strcmp(Title, "OC_SPEC_AA_MAX")==0 )sscanf_s(Line, "%s %lf", Title, 499,								&INSP_AAmode_OC_Max_Spec);
			else if ( strcmp(Title, "OC_SPEC_AA_MIN")==0 )sscanf_s(Line, "%s %lf", Title, 499,								&INSP_AAmode_OC_Min_Spec);
			else if ( strcmp(Title, "OC_SPEC_PROC_MAX")==0 )sscanf_s(Line, "%s %lf", Title, 499,							&INSP_Procmode_OC_Max_Spec);
			else if ( strcmp(Title, "OC_SPEC_PROC_MIN")==0 )sscanf_s(Line, "%s %lf", Title, 499,							&INSP_Procmode_OC_Min_Spec);
			else if ( strcmp(Title, "INSP_ROTATION_SPEC")==0 )sscanf_s(Line, "%s %lf", Title, 499,							&Rotation_Spec);

			Line[0] = 0x00;
		}

		if(in)	fclose(in);
	}
	else
		save();
}
void CMESCommunication::Messave()
{
	FILE *out;

	CFileFind finder;
	BOOL IsFind;
	CString FolderName, FolderName_D, backupFolderName_C, backupFolderName_D;

	
	CTime koreaTime = CTime::GetTickCount();
	FolderName.Format("C:\\BMS_MES");
	IsFind = finder.FindFile(FolderName);
	if(!IsFind)
	{
		FolderName.Format("C:\\BMS_MES");
		CreateDirectory(FolderName,NULL); 
	}
	finder.Close();
	char	fileName[1000];
	int i = 0;
	if(sysData.m_iProductComp == 1)
	{
		wsprintf(fileName, "%s\\%s_%d_%04d%02d%02d%02d%02d%02d.txt", FolderName, sysData.m_Comp_Factory_Code, iMES_Cnt , koreaTime.GetYear(), koreaTime.GetMonth(), koreaTime.GetDay(), koreaTime.GetHour(), koreaTime.GetMinute(), koreaTime.GetSecond());
	}
	else
	{
		wsprintf(fileName, "%s\\%s_%d_%04d%02d%02d%02d%02d%02d.txt", FolderName, sysData.m_Factory_Code, iMES_Cnt , koreaTime.GetYear(), koreaTime.GetMonth(), koreaTime.GetDay(), koreaTime.GetHour(), koreaTime.GetMinute(), koreaTime.GetSecond());
	}
	//
	if(fopen_s(&out, fileName,"w"))
	{
		sLangChange.LoadStringA(IDS_STRING769);	//MES Data 저장 실패...
		errMsg2(Task.AutoFlag, sLangChange);
	}
	else
	{
		fprintf_s(out,"%s,", (LPTSTR)(LPCTSTR)sMES_LotId);   // 바코드명
		fprintf_s(out,"%d,", iMES_Cnt);     // 차수
		fprintf_s(out,"%d,", iMES_FinalResult);  // 최종합부
		fprintf_s(out, "%.03lf:%d,", dMES_Current, 1);// iMES_Current_Result);  // 전류측정
		fprintf_s(out, "%s:%d,", (LPTSTR)(LPCTSTR)sMES_I2C, 1);// iMES_I2C_Result); //
		if (sysData.m_iProductComp == 1)
		{
			for (i = 0; i < 14; i++) {
				_ftprintf_s(out, _T("%.1lf:%d,"), m_nMesDefect[i], m_nMesDefectResult[i]);  // Defect 검사
			}
		}
		for (i = 0; i < model.mGlobalChartCount; i++)//for (i = 0; i < LAST_MARK_CNT; i++)
		{
			if (sysData.m_iProductComp == 0)
			{
				_ftprintf_s(out, _T("%.03lf:%d,"), dMES_MTF_avg[i], iMES_MTF_67lp_Result[i]);  // MTF 검사
			}
			else
			{
				//완제품
				_ftprintf_s(out, _T("%.03lf:%d,"), dMES_MTF_UVAfter_avg[i], iMES_MTF_67lp_Result_UVAfter[i]);  // MTF 검사
			}
		}
		
		for (i = 0; i < 2; i++)
		{
			_ftprintf_s(out, _T("%.03lf:%d,"), m_dMesOC[i], m_dMesOCResult[i]);  // OC 검사
			if (i == 1)
			{
				_ftprintf_s(out, _T("%.03lf:%d\r\n"), m_dMesDeltaOC[i], m_dMesDeltaOCResult[i]);  // OC 검사
			}
			else
			{
				_ftprintf_s(out, _T("%.03lf:%d,"), m_dMesDeltaOC[i], m_dMesDeltaOCResult[i]);  // OC 검사
			}
			
		}

		if (sysData.m_iProductComp == 1)
		{
			_ftprintf_s(out, _T("%.03lf:%d,"), m_dMesDistortion, m_nMesDistortionResult); // Distortion 검사

			for (i = 0; i < 3; i++)
				_ftprintf_s(out, _T("%.03lf:%d,"), m_nMesBlemish[i], m_nMesBlemishResult[i]);  // Blemish 검사

			for (i = 0; i < 6; i++)
				_ftprintf_s(out, _T("%.03lf:%d,"), m_nMesColorSensitivity[i], m_nMesColorSensitivityResult[i]);  // ColorSensitivity 검사

			for (i = 0; i < 20; i++)
				_ftprintf_s(out, _T("%.03lf:%d,"), m_nMesRI[i], m_nMesRIResult[i]);  // RI 검사

			for (i = 0; i < 4; i++)
				_ftprintf_s(out, _T("%.03lf:%d,"), m_nMesRICorner[i], m_nMesRIRICornerResult[i]);  // RI Corner검사

			_ftprintf_s(out, _T("%.03lf:%d,"), m_dMesSnr, m_dMesSnrResult);			// SNR 검사
			_ftprintf_s(out, _T("%.03lf:%d,"), m_dMesDr, m_dMesDrResult);			// DR 검사

			for (i = 0; i < 12; i++)
				_ftprintf_s(out, _T("%.03lf:%d,"), m_nMesColorUniformity[i], m_nMesColorUniformityResult[i]);  // ColorUniformity 검사

			for (i = 0; i < 3; i++)
			{
				if (i == 3 - 1)
				{
					_ftprintf_s(out, _T("%.03lf:%d\r\n"), m_dMesFov[i], m_dMesFovResult[i]);  // FOV 검사
				}
				else
				{
					_ftprintf_s(out, _T("%.03lf:%d,"), m_dMesFov[i], m_dMesFovResult[i]);  // FOV 검사
				}
			}
		}
		 
		if(out)			fclose(out);
	}	
}

CMESCommunication::CMESCommunication()
{
		sMES_LotId.Format("EMPTY");
		sMES_I2C.Format("PASS");
			//= _T("EMPTY");	// 바코드 아이디
		iMES_Cnt = 0;			// 차수
		iMES_FinalResult = 0;	// 합부
		
		for (int i = 0; i < COMMON_MTF_INSP_CNT; i++)
		{
			dMES_MTF[i] = 0.0;			//MTF 검사 항목
			dMES_MTF_UVAfter[i] = 0.0;
			dMES_MTF_67lp[i] = 0.0;			//MTF 검사 항목
			dMES_MTF_67lp_UVAfter[i] = 0.0;
			
		}


		for (int i = 0; i < COMMON_LAST_MARK_CNT; i++)
		{
			dMES_MTF_avg[i] = 0.0;			//MTF 검사 항목
			dMES_MTF_UVAfter_avg[i] = 0.0;
		}
			
	

		dMES_DefectPixel_Dark_Couplet = 0;
		dMES_DefectPixel_Dark_Cluster = 0;
		dMES_DefectPixel_DefectPixelTotal_Hot = 0; // DefectPixel_DefectPixelTotal_Hot 검사
		dMES_DefectPixel_DefectPixelTotal_Bright = 0; // DefectPixel_DefectPixelTotal_Bright 검사
		dMES_DefectPixel_DefectPixelTotal_Dark = 0; // DefectPixel_DefectPixelTotal_Dark 검사
		dMES_DefectPixel_DefectPixelTotal = 0; // DefectPixel_DefectPixelTotal 검사
		dMES_DefectPixel_Row_Dark = 0; // DefectPixel_Row_Dark 검사
		dMES_DefectPixel_Column_Dark = 0; // DefectPixel_Column_Dark 검사
		dMES_DefectPixel_ColumnFPN = 0; // DefectPixel_ColumnFPN 검사
		dMES_DefectPixel_Light_Couplet = 0; // DefectPixel_Light_Couplet 검사
		dMES_DefectPixel_Light_Cluster = 0; // DefectPixel_Light_Cluster 검사
		dMES_DefectPixel_Row_Midlevel = 0; // DefectPixel_Row_Midlevel 검사
		dMES_DefectPixel_Column_Midlevel = 0; // DefectPixel_Column_Midlevel 검사
		dMES_Stain = 0; // stain 검사
		//dMES_DistortionCentering = 0;
		dMES_UVBefore_OC[0] = dMES_UVBefore_OC[1] = 0.0;	//OC 결과.[X/Y]  UV 전
		dMES_UVAfter_OC[0] = dMES_UVAfter_OC[1] = 0.0;		//OC 결과.[X/Y]  UV 후
		dMES_Distortion = 0.0;
		iMES_Defect[0] = iMES_Defect[1] = 0;			//Defect검사[White/Black]
		dMES_Current = 0.0;

		dMES_Shading65FC[0] = dMES_Shading65FC[1] = dMES_Shading85FC[0] = dMES_Shading85FC[1] = 0.0;

		for (int i = 0; i < COMMON_MTF_INSP_CNT; i++)
		{
			iMES_MTF_Result[i] = 0;
			iMES_MTF_Result_UVAfter[i] = 0;
		}
		for (int i = 0; i < COMMON_LAST_MARK_CNT; i++)
		{
			iMES_MTF_67lp_Result[i] = 0;
			iMES_MTF_67lp_Result_UVAfter[i] = 0;
		}
			

//		iMES_DefectPixel_Dark_Couplet_Result = 0;
		iMES_DefectPixel_Dark_Cluster_Result = 0;
		iMES_DefectPixel_DefectPixelTotal_Hot_Result = 0; // DefectPixel_DefectPixelTotal_Hot 검사
		iMES_DefectPixel_DefectPixelTotal_Bright_Result = 0; // DefectPixel_DefectPixelTotal_Bright 검사
		iMES_DefectPixel_DefectPixelTotal_Dark_Result = 0; // DefectPixel_DefectPixelTotal_Dark 검사
		iMES_DefectPixel_DefectPixelTotal_Result = 0; // DefectPixel_DefectPixelTotal 검사
//		iMES_DefectPixel_Row_Dark_Result = 0; // DefectPixel_Row_Dark 검사
//		iMES_DefectPixel_Column_Dark_Result = 0; // DefectPixel_Column_Dark 검사
//		iMES_DefectPixel_Row_Count_Dark_Result = 0; // DefectPixel_Row_Count_Dark 검사
//		iMES_DefectPixel_Column_Count_Dark_Result = 0; // DefectPixel_Column_Count_Dark 검사
//		iMES_DefectPixel_ColumnFPN_Result = 0; // DefectPixel_ColumnFPN 검사
//		iMES_DefectPixel_Light_Couplet_Result = 0; // DefectPixel_Light_Couplet 검사
		iMES_DefectPixel_Light_Cluster_Result = 0; // DefectPixel_Light_Cluster 검사
//		iMES_DefectPixel_Row_Count_Light_Result = 0; // DefectPixel_Row_Count_Light 검사
//		iMES_DefectPixel_Column_Count_Light_Result = 0; // DefectPixel_Column_Count_Light 검사
//		iMES_DefectPixel_Row_Midlevel_Result = 0; // DefectPixel_Row_Midlevel 검사
//		iMES_DefectPixel_Column_Midlevel_Result = 0; // DefectPixel_Column_Midlevel 검사
		iMES_DistortionCentering_Result = 0;
		iMES_UVBefore_OC_Result[0]= iMES_UVBefore_OC_Result[1] = iMES_UVAfter_OC_Result[0]= iMES_UVAfter_OC_Result[1] = 0;
		iMES_Distortion_Result = 0;
		iMES_Defect_Result[0] = iMES_Defect_Result[1] = 0;
		iMES_Stain_Result = 0;
		iMES_Shading65FC_Result[0] = iMES_Shading65FC_Result[1] = iMES_Shading85FC_Result[0] = iMES_Shading85FC_Result[1] = 0;
		iMES_Current_Result = 0;
		iMES_Lens_Rotation_Result = 0;


		//======================================================================================
		//======================================================================================
		//======================================================================================
		//new Mes 190921

		//
		int i = 0;
		for (i = 0; i < COMMON_MTF_INSP_CNT; i++)
		{
			m_dMesMTF[i] = 0.0;			//MTF 검사 항목
			m_nMesMTFResult[i] = 0;
		}

		m_dMesDistortion = 0.0;
		m_dMesSnr = 0.0;
		m_dMesDr = 0.0;
		m_dMesRotate = 0.0;


		m_dMesRotateResult = 1;
		m_dMesSnrResult = 1;
		m_dMesDrResult = 1;
		m_nMesDistortionResult = 1;

		for (i = 0; i < 2; i++)
		{
			m_dMesOC[i] = 0.0;
			m_dMesDeltaOC[i] = 0.0;
			m_dMesOCResult[i] = 0;
			m_dMesDeltaOCResult[i] = 0;
		}

		for (i = 0; i < 3; i++)
		{
			m_dMesFov[i] = 0.0;
			m_dMesFovResult[i] = 1;
		}
		for (i = 0; i < 14; i++)
		{
			m_nMesDefect[i] = 0.0;
			m_nMesDefectResult[i] = 0;
		}
		for (i = 0; i < 6; i++)
		{
			m_nMesColorSensitivity[i] = 0.0;
			m_nMesColorSensitivityResult[i] = 1;
		}

		for (i = 0; i < 20; i++)
		{
			m_nMesRI[i] = 0.0;
			m_nMesRIResult[i] = 1;
		}
		for (i = 0; i < 4; i++)
		{
			m_nMesRICorner[i] = 0.0;
			m_nMesRIRICornerResult[i] = 1;
		}


		for (i = 0; i < 12; i++)
		{
			m_nMesColorUniformity[i] = 0.0;
			m_nMesColorUniformityResult[i] = 1;
		}
		
}
