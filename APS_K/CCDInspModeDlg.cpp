// CCDInspModeDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CCDInspModeDlg.h"
#include "./Library/Inspection/Include/LibACMISSoftISP/SoftISP.h"
//
#include "CcdSfrSpecDlg.h"
#include "CcdDefectSpecDlg.h"
#include "CcdRiOcSpecDlg.h"
#include "CcdBlemishSpecDlg.h"
#include "CcdChartSpecDlg.h"
#include "CcdRISpecDlg.h"
#include "CcdSnrColorSensSpecDlg.h"
//
//#include "AutoDispDlg.h"
//extern CAutoDispDlg* autodispDlg;
// CCCDInspModeDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCCDInspModeDlg, CDialogEx)

CCCDInspModeDlg::CCCDInspModeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCCDInspModeDlg::IDD, pParent)
{

}

CCCDInspModeDlg::~CCCDInspModeDlg()
{
}

void CCCDInspModeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCCDInspModeDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_INSP_PIXEL_DEFECT, &CCCDInspModeDlg::OnBnClickedBtnInspPixelDefect)
	ON_BN_CLICKED(IDC_BTN_INSP_STAIN, &CCCDInspModeDlg::OnBnClickedBtnInspStain)
	ON_BN_CLICKED(IDC_BTN_INSP_UNIFORMITY, &CCCDInspModeDlg::OnBnClickedBtnInspUniformity)
	ON_BN_CLICKED(IDC_BTN_INSP_CURRENT, &CCCDInspModeDlg::OnBnClickedBtnInspCurrent)
	ON_BN_CLICKED(IDC_BTN_INSP_TEST_PATTERN, &CCCDInspModeDlg::OnBnClickedBtnInspTestPattern)
	ON_BN_CLICKED(IDC_BTN_INSP_MTF, &CCCDInspModeDlg::OnBnClickedBtnInspMtf)
    ON_BN_CLICKED(IDC_BTN_SPEC_DEFECT, &CCCDInspModeDlg::OnBnClickedBtnSpecDefect)
    ON_BN_CLICKED(IDC_BTN_SPEC_OC, &CCCDInspModeDlg::OnBnClickedBtnSpecOc)
    ON_BN_CLICKED(IDC_BTN_SPEC_BLEMISH, &CCCDInspModeDlg::OnBnClickedBtnSpecBlemish)
    ON_BN_CLICKED(IDC_BTN_SPEC_FOV, &CCCDInspModeDlg::OnBnClickedBtnSpecFov)
    ON_BN_CLICKED(IDC_BUTTON_CCD_RELATIVEI_SPEC, &CCCDInspModeDlg::OnBnClickedButtonCcdRelativeiSpec)
    ON_BN_CLICKED(IDC_BTN_SPEC_SNR, &CCCDInspModeDlg::OnBnClickedBtnSpecSnr)
	ON_BN_CLICKED(IDC_BTN_INSP_COLOR_UNIFORMITY, &CCCDInspModeDlg::OnBnClickedBtnInspColorUniformity)
	ON_BN_CLICKED(IDC_BTN_INSP_RI, &CCCDInspModeDlg::OnBnClickedBtnInspRi)
	ON_BN_CLICKED(IDC_BTN_INSP_SNR, &CCCDInspModeDlg::OnBnClickedBtnInspSnr)
	ON_BN_CLICKED(IDC_BTN_INSP_COLOR_SENSITIVITY, &CCCDInspModeDlg::OnBnClickedBtnInspColorSensitivity)
	ON_BN_CLICKED(IDC_BTN_INSP_FOV_DISTORTION, &CCCDInspModeDlg::OnBnClickedBtnInspFovDistortion)
	ON_BN_CLICKED(IDC_BTN_SPEC_MTF, &CCCDInspModeDlg::OnBnClickedBtnSpecMtf)
    ON_BN_CLICKED(IDC_BTN_INSP_DISTORTION, &CCCDInspModeDlg::OnBnClickedBtnInspDistortion)
	ON_BN_CLICKED(IDC_BTN_INSP_SATURATION, &CCCDInspModeDlg::OnBnClickedBtnInspSaturation)
	ON_BN_CLICKED(IDC_BTN_SPEC_COLOR_SENSITIVITY, &CCCDInspModeDlg::OnBnClickedBtnSpecColorSensitivity)
	ON_BN_CLICKED(IDC_BTN_INSP_VOLTAGE, &CCCDInspModeDlg::OnBnClickedBtnInspVoltage)
	ON_BN_CLICKED(IDC_BTN_INSP_COLOR, &CCCDInspModeDlg::OnBnClickedBtnInspColor)
	ON_BN_CLICKED(IDC_BTN_INSP_OTP, &CCCDInspModeDlg::OnBnClickedBtnInspOtp)
	ON_BN_CLICKED(IDC_BTN_INSP_SENSOR_ID, &CCCDInspModeDlg::OnBnClickedBtnInspSensorId)
	ON_BN_CLICKED(IDC_BTN_INSP_FW_VERSION, &CCCDInspModeDlg::OnBnClickedBtnInspFwVersion)
	ON_BN_CLICKED(IDC_BTN_INSP_OTP_VERIFY, &CCCDInspModeDlg::OnBnClickedBtnInspOtpVerify)
END_MESSAGE_MAP()


// CCCDInspModeDlg 메시지 처리기입니다.

bool CCCDInspModeDlg::func_Check_MIU_Mode()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
#ifdef NORINDA_MODE
	return true;
#endif
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING295);
		pFrame->putListLog(sLangChange);
		return false;
	}
	if(Task.AutoFlag == 2)
	{
		sLangChange.LoadStringA(IDS_STRING294);
		pFrame->putListLog(sLangChange);
		return false;
	}

	if ( gMIUDevice.bMIUOpen != 1 )
	{
		sLangChange.LoadStringA(IDS_STRING293);
		pFrame->putListLog(sLangChange);
		return false;
	}

	/*if( gMIUDevice.bMIUInit != 1 )
	{
		sLangChange.LoadStringA(IDS_STRING292);
		pFrame->putListLog(sLangChange);
		return false;
	}*/

	if( gMIUDevice.CurrentState != 4)
	{
		sLangChange.LoadStringA(IDS_STRING290);
		pFrame->putListLog(sLangChange);
		return false;
	}

	return true;
}

void CCCDInspModeDlg::OnBnClickedBtnInspPixelDefect()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	if( !func_Check_MIU_Mode() )	return;

}
//-----------------------------------------------------------------------------
//
//	버튼 : STAIN 검사
//
//-----------------------------------------------------------------------------

void CCCDInspModeDlg::OnBnClickedBtnInspStain()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	//if( !func_Check_MIU_Mode() )	return;
	
	if (Task.AutoFlag == MODE_AUTO)
	{
		pFrame->putListLog(_T("[수동검사] 자동 운전 중 사용 불가"));
		return;
	}

	if (Task.AutoFlag == MODE_PAUSE)
	{
		pFrame->putListLog(_T("[수동검사] 일시 정지 중 사용 불가"));
		return;
	}

	MandoInspLog.func_InitData();	//-- Log 초기화

	vision.clearOverlay(CCD);
	vision.drawOverlay(CCD);
	pFrame->putListLog("=====================================stain 수동검사 시작");

	
	if (g_clApsInsp.func_Insp_Stain(MIU.m_pFrameRawBuffer) == false)
	{
		pFrame->putListLog(_T("[수동검사] STAIN 검사 실패"));
		return;
	}
	vision.drawOverlay(CCD);
	pFrame->putListLog(_T("[수동검사] STAIN 검사 완료"));
	
}


void CCCDInspModeDlg::OnBnClickedBtnInspUniformity()
{

}
//-----------------------------------------------------------------------------
//
//	버튼 : Current
//
//-----------------------------------------------------------------------------
void CCCDInspModeDlg::OnBnClickedBtnInspCurrent()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	//if( !func_Check_MIU_Mode() )	return;

	if (Task.AutoFlag == MODE_AUTO)
	{
		pFrame->putListLog(_T("[수동검사] 자동 운전 중 사용 불가"));
		return;
	}

	if (Task.AutoFlag == MODE_PAUSE)
	{
		pFrame->putListLog(_T("[수동검사] 일시 정지 중 사용 불가"));
		return;
	}
	g_clApsInsp.func_Insp_CurrentMeasure(true);
	//g_clApsInsp.func_insp_CDP800_Current();
	//if( !pFrame->func_Insp_CurrentMeasure(true, false) )
	//{
	//	sLangChange.LoadStringA(IDS_STRING296);
	//	pFrame->putListLog(sLangChange);
	//	return;
	//}
 //   MandoInspLog.func_InitData();	//-- Log 초기화
	//vision.clearOverlay(CCD);

	//if (g_clApsInsp.func_Insp_CurrentMeasure(true, false) == false)
	//{
	//	pFrame->putListLog(_T("[수동검사] Current 측정 실패"));
	//	return;
	//}
	//vision.drawOverlay(CCD);
	pFrame->putListLog(_T("[수동검사] Current 측정 완료"));

}

//-----------------------------------------------------------------------------
//
//	버튼 : PIXEL DEFECT
//
//-----------------------------------------------------------------------------
void CCCDInspModeDlg::OnBnClickedBtnInspTestPattern()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	//bool bDefect=pFrame->BrightDefect_Insp(false);// (10이하)

	if (Task.AutoFlag == MODE_AUTO)
	{
		pFrame->putListLog(_T("[수동검사] 자동 운전 중 사용 불가"));
		return;
	}

	if (Task.AutoFlag == MODE_PAUSE)
	{
		pFrame->putListLog(_T("[수동검사] 일시 정지 중 사용 불가"));
		return;
	}

	MandoInspLog.func_InitData();	//-- Log 초기화
	vision.clearOverlay(CCD);

	 
	
	if (g_clApsInsp.func_Insp_Defect(MIU.vDefectMidBuffer_6500K, MIU.vDefectLowBuffer, false) == false)
	{
		pFrame->putListLog(_T("[수동검사] Defect 검사 실패"));
	    return;
    }
	vision.drawOverlay(CCD);
	pFrame->putListLog(_T("[수동검사] Defect 검사 완료"));
}
//-----------------------------------------------------------------------------
//
//	버튼 : MTF 검사
//
//-----------------------------------------------------------------------------

void CCCDInspModeDlg::OnBnClickedBtnInspMtf()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	//if( !func_Check_MIU_Mode() )	return;

	if (Task.AutoFlag == MODE_AUTO)
	{
		pFrame->putListLog(_T("[수동검사] 자동 운전 중 사용 불가"));
		return;
	}

	if (Task.AutoFlag == MODE_PAUSE)
	{
		pFrame->putListLog(_T("[수동검사] 일시 정지 중 사용 불가"));
		return;
	}

	pFrame->func_MTF(MIU.m_pFrameRawBuffer ,false);//수동검사

	
	/*int count1 = model.mCurModelName.Find(_T("SHM"));
	int count2 = model.mCurModelName.ReverseFind('SHM');
	if (count2 - count1 > 0 && count1 >= 0)
	{
		vision.FnShmEdgeFind(MIU.m_pFrameRawBuffer, false);
		MandoInspLog.func_LogSave_Shm_vertex();

	}
	pFrame->putListLog("[수동검사] MTF 측정 완료");*/
	//MandoInspLog.func_LogSave_UVAfter(1);


}



BOOL CCCDInspModeDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  여기에 추가 초기화 작업을 추가합니다.


	m_clSfrSpecDlg.Create(IDD_DIALOG_CCD_SFR_SPEC, this);
	m_clSfrSpecDlg.ShowWindow(SW_HIDE);

    m_clDefectSpecDlg.Create(IDD_DIALOG_CCD_DEFECT_SPEC, this);
    m_clDefectSpecDlg.ShowWindow(SW_HIDE);

    m_clRiOcSpecDlg.Create(IDD_DIALOG_CCD_RI_OC_SPEC, this);
    m_clRiOcSpecDlg.ShowWindow(SW_HIDE);

    m_clBlemishSpecDlg.Create(IDD_DIALOG_CCD_BLEMISH_SPEC, this);
    m_clBlemishSpecDlg.ShowWindow(SW_HIDE);

    m_clChartSpecDlg.Create(IDD_DIALOG_CCD_CHART_SPEC, this);
    m_clChartSpecDlg.ShowWindow(SW_HIDE);

    m_clRiSpecDlg.Create(IDD_DIALOG_CCD_RI_SPEC, this);
    m_clRiSpecDlg.ShowWindow(SW_HIDE);

    m_clSnrColorSensSpecDlg.Create(IDD_DIALOG_CCD_SNR_COLORSENS_SPEC, this);
    m_clSnrColorSensSpecDlg.ShowWindow(SW_HIDE);
    return TRUE;  // return TRUE unless you set the focus to a control
                  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//-----------------------------------------------------------------------------
//
//	버튼 : DEFECT/UNIFORM
//
//-----------------------------------------------------------------------------
void CCCDInspModeDlg::OnBnClickedBtnSpecDefect()
{
	//m_clDefectSpecDlg.SetUnit(m_nUnit);
    m_clDefectSpecDlg.ShowWindow(SW_SHOW);
}
//-----------------------------------------------------------------------------
//
//	버튼 : OC
//
//-----------------------------------------------------------------------------

void CCCDInspModeDlg::OnBnClickedBtnSpecOc()
{
	//m_clRiOcSpecDlg.SetUnit(m_nUnit);
    m_clRiOcSpecDlg.ShowWindow(SW_SHOW);
}

//-----------------------------------------------------------------------------
//
//	버튼 : BLEMISH
//
//-----------------------------------------------------------------------------
void CCCDInspModeDlg::OnBnClickedBtnSpecBlemish()
{
	//m_clBlemishSpecDlg.SetUnit(m_nUnit);
    m_clBlemishSpecDlg.ShowWindow(SW_SHOW);
}
//-----------------------------------------------------------------------------
//
//	버튼 : FOR/DISTORTION
//
//-----------------------------------------------------------------------------

void CCCDInspModeDlg::OnBnClickedBtnSpecFov()
{
	//m_clChartSpecDlg.SetUnit(m_nUnit);
    m_clChartSpecDlg.ShowWindow(SW_SHOW);
}
//-----------------------------------------------------------------------------
//
//	버튼 : RI
//
//-----------------------------------------------------------------------------

void CCCDInspModeDlg::OnBnClickedButtonCcdRelativeiSpec()
{
	//m_clRiSpecDlg.SetUnit(m_nUnit);
	m_clRiSpecDlg.ShowWindow(SW_SHOW);
}
//-----------------------------------------------------------------------------
//
//	버튼 : SNR/COLOR SENS
//
//-----------------------------------------------------------------------------

void CCCDInspModeDlg::OnBnClickedBtnSpecSnr()
{
	//m_clSnrColorSensSpecDlg.SetUnit(m_nUnit);
	m_clSnrColorSensSpecDlg.ShowWindow(SW_SHOW);
}
//-----------------------------------------------------------------------------
//
//	버튼 : UNIFORMITY
//
//-----------------------------------------------------------------------------

void CCCDInspModeDlg::OnBnClickedBtnInspColorUniformity()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	if (!func_Check_MIU_Mode())	return;

	if (Task.AutoFlag == MODE_AUTO)
	{
		pFrame->putListLog(_T("[수동검사] 자동 운전 중 사용 불가"));
		return;
	}

	if (Task.AutoFlag == MODE_PAUSE)
	{
		pFrame->putListLog(_T("[수동검사] 일시 정지 중 사용 불가"));
		return;
	}

	MandoInspLog.func_InitData();	//-- Log 초기화

	vision.clearOverlay(CCD);

}
//-----------------------------------------------------------------------------
//
//	버튼 : RI
//
//-----------------------------------------------------------------------------

void CCCDInspModeDlg::OnBnClickedBtnInspRi()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	//if (!func_Check_MIU_Mode())	return;

	if (Task.AutoFlag == MODE_AUTO)
	{
		pFrame->putListLog(_T("[수동검사] 자동 운전 중 사용 불가"));
		return;
	}

	if (Task.AutoFlag == MODE_PAUSE)
	{
		pFrame->putListLog(_T("[수동검사] 일시 정지 중 사용 불가"));
		return;
	}

	//MandoInspLog.func_InitData();	//-- Log 초기화

	vision.clearOverlay(CCD);
	//g_clApsInsp.func_Insp_Shm_Illumination(MIU.vTempBuffer);
	//if (g_clApsInsp.func_Insp_Illumination(MIU.m_pFrameRawBuffer, false) == false)
	if (g_clApsInsp.func_Insp_Shm_Illumination(MIU.m_pFrameRawBuffer, false) == false)
	{
		pFrame->putListLog(_T("[수동검사] Relative Illumination 검사 실패"));
		return;
	}
	
	vision.drawOverlay(CCD);
	pFrame->putListLog(_T("[수동검사] Relative Illumination 검사 완료"));
} 

//-----------------------------------------------------------------------------
//
//	버튼 : SMR
//
//-----------------------------------------------------------------------------
void CCCDInspModeDlg::OnBnClickedBtnInspSnr()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	//if (!func_Check_MIU_Mode())	return;

	if (Task.AutoFlag == MODE_AUTO)
	{
		pFrame->putListLog(_T("[수동검사] 자동 운전 중 사용 불가"));
		return;
	}

	if (Task.AutoFlag == MODE_PAUSE)
	{
		pFrame->putListLog(_T("[수동검사] 일시 정지 중 사용 불가"));
		return;
	}

	//MandoInspLog.func_InitData();	//-- Log 초기화

	vision.clearOverlay(CCD);
	g_clApsInsp.g_GetIllumination(MIU.m_pFrameRawBuffer);

	vision.drawOverlay(CCD);
	pFrame->putListLog(_T("[수동검사] OC 검사 완료"));
}

//-----------------------------------------------------------------------------
//
//	버튼 : COLOR SENSITIVITY
//
//-----------------------------------------------------------------------------
void CCCDInspModeDlg::OnBnClickedBtnInspColorSensitivity()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	if (!func_Check_MIU_Mode())	return;

	if (Task.AutoFlag == MODE_AUTO)
	{
		pFrame->putListLog(_T("[수동검사] 자동 운전 중 사용 불가"));
		return;
	}

	if (Task.AutoFlag == MODE_PAUSE)
	{
		pFrame->putListLog(_T("[수동검사] 일시 정지 중 사용 불가"));
		return;
	}

	MandoInspLog.func_InitData();	//-- Log 초기화

	vision.clearOverlay(CCD);
    pFrame->putListLog(_T("[수동검사] Color Sensitivity MID_6500K_RAW TEST..."));
    if (g_clApsInsp.func_Insp_ColorSensitivity(MIU.vDefectMidBuffer_6500K, MID_6500K_RAW, false) == false)
    {
        pFrame->putListLog(_T("[수동검사] Color Sensitivity MID_6500K_RAW 검사 실패"));
    }
    pFrame->putListLog(_T("[수동검사] Color Sensitivity MID_2800K_RAW TEST..."));
    if (g_clApsInsp.func_Insp_ColorSensitivity(MIU.vDefectMidBuffer_2800K, MID_2800K_RAW, false) == false)
    {
        pFrame->putListLog(_T("[수동검사] Color Sensitivity MID_2800K_RAW 검사 실패"));
    }
	vision.drawOverlay(CCD);
	pFrame->putListLog(_T("[수동검사] Color Sensitivity 검사 완료"));
}
//-----------------------------------------------------------------------------
//
//	버튼 : FOV / DISTORTION
//
//-----------------------------------------------------------------------------

void CCCDInspModeDlg::OnBnClickedBtnInspFovDistortion()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	if (!func_Check_MIU_Mode())	return;

	if (Task.AutoFlag == MODE_AUTO)
	{
		pFrame->putListLog(_T("[수동검사] 자동 운전 중 사용 불가"));
		return;
	}

	if (Task.AutoFlag == MODE_PAUSE)
	{
		pFrame->putListLog(_T("[수동검사] 일시 정지 중 사용 불가"));
		return;
	}

	MandoInspLog.func_InitData();	//-- Log 초기화

	vision.clearOverlay(CCD);

	
	pFrame->putListLog(_T("[수동검사] Fov 검사 완료"));
}

//-----------------------------------------------------------------------------
//
//	버튼 : MTP SPEC
//
//-----------------------------------------------------------------------------
void CCCDInspModeDlg::OnBnClickedBtnSpecMtf()
{
	//m_clSfrSpecDlg.SetUnit(m_nUnit);
	m_clSfrSpecDlg.ShowWindow(SW_SHOW);
}


void CCCDInspModeDlg::OnBnClickedBtnInspDistortion()
{
    CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

    if (!func_Check_MIU_Mode())	return;

    if (Task.AutoFlag == MODE_AUTO)
    {
        pFrame->putListLog(_T("[수동검사] 자동 운전 중 사용 불가"));
        return;
    }

    if (Task.AutoFlag == MODE_PAUSE)
    {
        pFrame->putListLog(_T("[수동검사] 일시 정지 중 사용 불가"));
        return;
    }

    MandoInspLog.func_InitData();	//-- Log 초기화

}


void CCCDInspModeDlg::OnBnClickedBtnInspSaturation()
{
	// TODO: Add your control notification handler code here
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	//bool bDefect=pFrame->BrightDefect_Insp(false);// (10이하)

	if (Task.AutoFlag == MODE_AUTO)
	{
		pFrame->putListLog(_T("[수동검사] 자동 운전 중 사용 불가"));
		return;
	}

	if (Task.AutoFlag == MODE_PAUSE)
	{
		pFrame->putListLog(_T("[수동검사] 일시 정지 중 사용 불가"));
		return;
	}

	if (g_clApsInsp.func_Insp_Saturation(MIU.m_pFrameRawBuffer, false) == false)
	{
		pFrame->putListLog(_T("[수동검사] Saturation 검사 실패"));
		return;
	}
	vision.drawOverlay(CCD);
	pFrame->putListLog(_T("[수동검사] Saturation 검사 완료"));
}


void CCCDInspModeDlg::OnBnClickedBtnSpecColorSensitivity()
{
	// TODO: Add your control notification handler code here
}


void CCCDInspModeDlg::OnBnClickedBtnInspVoltage()
{
	// TODO: Add your control notification handler code here
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	//if( !func_Check_MIU_Mode() )	return;

	if (Task.AutoFlag == MODE_AUTO)
	{
		pFrame->putListLog(_T("[수동검사] 자동 운전 중 사용 불가"));
		return;
	}

	if (Task.AutoFlag == MODE_PAUSE)
	{
		pFrame->putListLog(_T("[수동검사] 일시 정지 중 사용 불가"));
		return;
	}
	g_clApsInsp.func_insp_Voltage();

	pFrame->putListLog(_T("[수동검사] Voltage 측정 완료"));
}


void CCCDInspModeDlg::OnBnClickedBtnInspColor()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	//if (!func_Check_MIU_Mode())	return;

	if (Task.AutoFlag == MODE_AUTO)
	{
		pFrame->putListLog(_T("[수동검사] 자동 운전 중 사용 불가"));
		return;
	}

	if (Task.AutoFlag == MODE_PAUSE)
	{
		pFrame->putListLog(_T("[수동검사] 일시 정지 중 사용 불가"));
		return;
	}
	
	vision.clearOverlay(CCD);
	if (g_clApsInsp.func_Insp_Color_reproduction(MIU.m_pFrameRawBuffer, false) == false)
	{
		pFrame->putListLog(_T("[수동검사] Color Reproduction 검사 실패"));
		return;
	}

	vision.drawOverlay(CCD);
	pFrame->putListLog(_T("[수동검사] Color Reproduction 검사 완료"));
}


void CCCDInspModeDlg::OnBnClickedBtnInspOtp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	//if (!func_Check_MIU_Mode())	return;

	if (Task.AutoFlag == MODE_AUTO)
	{
		pFrame->putListLog(_T("[수동검사] 자동 운전 중 사용 불가"));
		return;
	}

	if (Task.AutoFlag == MODE_PAUSE)
	{
		pFrame->putListLog(_T("[수동검사] 일시 정지 중 사용 불가"));
		return;
	}

	MIU.OtpRead_Head_Fn();
}


void CCCDInspModeDlg::OnBnClickedBtnInspSensorId()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	//if (!func_Check_MIU_Mode())	return;

	if (Task.AutoFlag == MODE_AUTO)
	{
		pFrame->putListLog(_T("[수동검사] 자동 운전 중 사용 불가"));
		return;
	}

	if (Task.AutoFlag == MODE_PAUSE)
	{
		pFrame->putListLog(_T("[수동검사] 일시 정지 중 사용 불가"));
		return;
	}

	MIU.SensorIdRead_Head_Fn();
}


void CCCDInspModeDlg::OnBnClickedBtnInspFwVersion()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	//if (!func_Check_MIU_Mode())	return;

	if (Task.AutoFlag == MODE_AUTO)
	{
		pFrame->putListLog(_T("[수동검사] 자동 운전 중 사용 불가"));
		return;
	}

	if (Task.AutoFlag == MODE_PAUSE)
	{
		pFrame->putListLog(_T("[수동검사] 일시 정지 중 사용 불가"));
		return;
	}

	MIU.FwVersionRead_Head_Fn();
}


void CCCDInspModeDlg::OnBnClickedBtnInspOtpVerify()
{
	// TODO: Add your control notification handler code here
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	//if (!func_Check_MIU_Mode())	return;

	if (Task.AutoFlag == MODE_AUTO)
	{
		pFrame->putListLog(_T("[수동검사] 자동 운전 중 사용 불가"));
		return;
	}

	if (Task.AutoFlag == MODE_PAUSE)
	{
		pFrame->putListLog(_T("[수동검사] 일시 정지 중 사용 불가"));
		return;
	}

	MIU.partNumberVerifyFn();
}
