// CCDCtrlDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AA Bonder.h"
#include "AA BonderDlg.h"
#include "CCDCtrlDlg.h"
#include "afxdialogex.h"


#include "DataHandler.h"
extern CModelData  model;
extern CSystemData sysData;
extern CTask	   Task;

#include "MIU/Miu.h"
extern MIU_DEVICE					gMIUDevice;
extern char							gDeviceCount;
extern char							gDeviceIndex;

extern		CMIU				MIU;

#include "DioControl.h"
extern CDioControl	Dio;

#include "Vision.h"
extern CVision vision;

extern		int			g_iCCDCamView;
extern		bool		bThreadCcmGrabRun;		// CCM 영상 획득 Thread 동작시 True


// CCCDCtrlDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCCDCtrlDlg, CDialogEx)

	CCCDCtrlDlg::CCCDCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCCDCtrlDlg::IDD, pParent)
{
}

CCCDCtrlDlg::~CCCDCtrlDlg()
{
}

void CCCDCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_GPIO27, m_cGpio27Status);
	DDX_Control(pDX, IDC_CHECK_GPIO13, m_cGpio13Status);
	DDX_Control(pDX, IDC_CHECK_GPIO15, m_cGpio15Status);
	DDX_Control(pDX, IDC_CHECK_GPIO19, m_cGpio19Status);
	DDX_Control(pDX, IDC_CHECK_GPIO21, m_cGpio21Status);
	DDX_Control(pDX, IDC_CHECK_GPIO25, m_cGpio25Status);
}


BEGIN_MESSAGE_MAP(CCCDCtrlDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CCCDCtrlDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CCCDCtrlDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE2, &CCCDCtrlDlg::OnBnClickedButtonClose2)
	ON_BN_CLICKED(IDC_BUTTON_INIT, &CCCDCtrlDlg::OnBnClickedButtonInit)
	ON_BN_CLICKED(IDC_BUTTON_LIVE, &CCCDCtrlDlg::OnBnClickedButtonLive)
	ON_BN_CLICKED(IDC_BUTTON_SNAP, &CCCDCtrlDlg::OnBnClickedButtonSnap)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_MIU, &CCCDCtrlDlg::OnBnClickedButtonOpenMiu)
	ON_BN_CLICKED(IDC_BUTTON_INIT_MIU, &CCCDCtrlDlg::OnBnClickedButtonInitMiu)
	ON_BN_CLICKED(IDC_BUTTON_VCM_READY, &CCCDCtrlDlg::OnBnClickedButtonVcmReady)
	ON_BN_CLICKED(IDC_BUTTON_CODE_WRITE, &CCCDCtrlDlg::OnBnClickedButtonCodeWrite)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_CUR_MEASURE, &CCCDCtrlDlg::OnBnClickedCurMeasure)
	ON_BN_CLICKED(IDC_STOP_LIVE, &CCCDCtrlDlg::OnBnClickedStopLive)
	ON_BN_CLICKED(IDC_SENSOR_WRITE, &CCCDCtrlDlg::OnBnClickedSensorWrite)
	ON_BN_CLICKED(IDC_SENSOR_READ, &CCCDCtrlDlg::OnBnClickedSensorRead)
	ON_BN_CLICKED(IDC_BTN_TEST, &CCCDCtrlDlg::OnBnClickedBtnTest)
	ON_BN_CLICKED(IDC_CHECK_GPIO15, &CCCDCtrlDlg::OnBnClickedCheckGpio15)
	ON_BN_CLICKED(IDC_CHECK_GPIO13, &CCCDCtrlDlg::OnBnClickedCheckGpio13)
	ON_BN_CLICKED(IDC_CHECK_GPIO19, &CCCDCtrlDlg::OnBnClickedCheckGpio19)
	ON_BN_CLICKED(IDC_CHECK_GPIO21, &CCCDCtrlDlg::OnBnClickedCheckGpio21)
	ON_BN_CLICKED(IDC_CHECK_GPIO25, &CCCDCtrlDlg::OnBnClickedCheckGpio25)
	ON_BN_CLICKED(IDC_CHECK_GPIO27, &CCCDCtrlDlg::OnBnClickedCheckGpio27)
	ON_BN_CLICKED(IDC_BUTTON_GET_GPIO31, &CCCDCtrlDlg::OnBnClickedButtonGetGpio31)
	ON_BN_CLICKED(IDC_BUTTON_GET_GPIO33, &CCCDCtrlDlg::OnBnClickedButtonGetGpio33)
	ON_BN_CLICKED(IDC_BUTTON_UART_SEND, &CCCDCtrlDlg::OnBnClickedButtonUartSend)
	ON_BN_CLICKED(IDC_BUTTON_UART_RX_GET, &CCCDCtrlDlg::OnBnClickedButtonUartRxGet)
END_MESSAGE_MAP()


// CCCDCtrlDlg 메시지 처리기입니다.
BOOL CCCDCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect rcClient;
	GetWindowRect(rcClient);
	int iSizeX	= rcClient.right - rcClient.left;
	int iSizeY	= rcClient.bottom - rcClient.top;

	CRect rcTemp;
	rcTemp.left		= MAIN_DLG_SIZE_X/2 - iSizeX/2;
	rcTemp.top		= MAIN_DLG_SIZE_Y/2 - iSizeY/2;
	rcTemp.right	= MAIN_DLG_SIZE_X/2 + iSizeX/2;
	rcTemp.bottom	= MAIN_DLG_SIZE_Y/2 + iSizeY/2;
	this->MoveWindow(rcTemp.left, rcTemp.top, (rcTemp.right-rcTemp.left), (rcTemp.bottom-rcTemp.top));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CCCDCtrlDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow)
	{

	}
}


void CCCDCtrlDlg::OnBnClickedCancel()
{
	g_iCCDCamView =5;
	CDialogEx::OnCancel();
}

//! Modified by LHW (2013/3/13)
void CCCDCtrlDlg::OnBnClickedButtonOpen()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	if(pFrame->m_bMiuRun)
	{
		CString logStr;
		sLangChange.LoadStringA(IDS_STRING131);
		logStr.Format(sLangChange);
		delayMsg(logStr.GetBuffer(100), 3000, M_COLOR_RED);
		return ;
	}
	else
	{
		pFrame->m_bMiuRun = true;
	}


	//////MIU.SensorListInitialize();

	MIU.Close();					// 95 ~ 100 msec

	Sleep(500);
	sLangChange.LoadStringA(IDS_STRING1420);	//카메라 모듈 정보 Loading.
	pFrame->putListLog(sLangChange);

	if(!MIU.Open())
	{
		pFrame->putListLog(MIU.sLogMessage);
		delayMsg(MIU.sLogMessage.GetBuffer(999));

		pFrame->m_bMiuRun = false;
		return;
	}
	else
	{
		sLangChange.LoadStringA(IDS_STRING1427);	//카메라 모듈 통신 Open.
		pFrame->putListLog(sLangChange);
	}

	Sleep(500);
	if(!MIU.CcmInit())
	{
		pFrame->putListLog(MIU.sLogMessage);
		delayMsg(MIU.sLogMessage.GetBuffer(999), 500000, M_COLOR_RED);
		pFrame->m_bMiuRun = false;
		pFrame->m_csLock_Miu.Unlock();
		return;
	}
	else
	{
		sLangChange.LoadStringA(IDS_STRING1423);	//카메라 모듈 초기화 완료.
		pFrame->putListLog(sLangChange);
	}

	//! CCD Sensor의 Registry 설정 정보를 알아낸다.
	MIU.GetCurrentInfo_Exposure_From_CCD_IMX135();

	Sleep(500);

	if(!MIU.Start())
	{
		pFrame->putListLog(MIU.sLogMessage);
		delayMsg(MIU.sLogMessage.GetBuffer(999));
	}
	else
	{
		if (!bThreadCcmGrabRun)
		{
			CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
			pFrame->CcmThreadStart();
		}
	}

	pFrame->m_bMiuRun = false;
	pFrame->m_csLock_Miu.Unlock();
}


void CCCDCtrlDlg::OnBnClickedButtonClose2()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	if(pFrame->m_bMiuRun)
	{
		CString logStr;
		sLangChange.LoadStringA(IDS_STRING131);
		logStr.Format(sLangChange);
		delayMsg(logStr.GetBuffer(100), 3000, M_COLOR_RED);
		return ;
	}
	else
	{
		pFrame->m_bMiuRun = true;
	}


	if(!MIU.Close())
	{
		pFrame->putListLog(MIU.sLogMessage);
		delayMsg(MIU.sLogMessage.GetBuffer(999));
	}
	else
	{
		sLangChange.LoadStringA(IDS_STRING1424);	//카메라 모듈 통신 Close.
					pFrame->putListLog(sLangChange);
	}

	pFrame->m_bMiuRun = false;
}


void CCCDCtrlDlg::OnBnClickedButtonInit()
{
	if(Dio.PCBPushSocketCheck(true, false) == false)
	{
		CString logMsg;
		sLangChange.LoadStringA(IDS_STRING1026);	//PCB부 커버 소켓이 열려 있습니다.
		logMsg.Format(sLangChange);
		errMsg2(Task.AutoFlag,logMsg);
		return;
	}

	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	if(pFrame->m_bMiuRun)
	{
		CString logStr;
		sLangChange.LoadStringA(IDS_STRING131);
		logStr.Format(sLangChange);
		delayMsg(logStr.GetBuffer(100), 3000, M_COLOR_RED);
		return ;
	}
	else
	{
		pFrame->m_bMiuRun = true;
	}

	pFrame->m_csLock_Miu.Lock();


	if(!MIU.CcmInit())
	{
		pFrame->putListLog(MIU.sLogMessage);
		delayMsg(MIU.sLogMessage.GetBuffer(999));
	}
	else
	{
		sLangChange.LoadStringA(IDS_STRING1423);	//카메라 모듈 초기화 완료.
		pFrame->putListLog(sLangChange);
	}

	pFrame->m_bMiuRun = false;
	pFrame->m_csLock_Miu.Unlock();
}

//! Modified by LHW (2013/3/13)
void CCCDCtrlDlg::OnBnClickedButtonLive()
{
	gMIUDevice.CurrentState = 4;

	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	sLangChange.LoadStringA(IDS_STRING1419);	//카메라 모듈 동영상.
	pFrame->putListLog(sLangChange);
}


void CCCDCtrlDlg::OnBnClickedButtonSnap()
{
	gMIUDevice.CurrentState = 3;

	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	sLangChange.LoadStringA(IDS_STRING1421);	//카메라 모듈 정지 영상.
	pFrame->putListLog(sLangChange);
}


void CCCDCtrlDlg::OnBnClickedButtonOpenMiu()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	if(pFrame->m_bMiuRun)
	{
		CString logStr;
		sLangChange.LoadStringA(IDS_STRING131);
		logStr.Format(sLangChange);
		delayMsg(logStr.GetBuffer(100), 3000, M_COLOR_RED);
		return ;
	}
	else
	{
		pFrame->m_bMiuRun = true;
	}

	pFrame->m_csLock_Miu.Lock();

	//////MIU.SensorListInitialize();
	//////pFrame->putListLog("카메라 모듈 정보 Loading.");

	if(!MIU.Open())
	{
		pFrame->putListLog(MIU.sLogMessage);
		delayMsg(MIU.sLogMessage.GetBuffer(999));
		return;
	}
	else
	{
		sLangChange.LoadStringA(IDS_STRING1427);	//카메라 모듈 통신 Open.
		pFrame->putListLog(sLangChange);
	}


	if(!MIU.CcmInit())
	{
		pFrame->putListLog(MIU.sLogMessage);
		delayMsg(MIU.sLogMessage.GetBuffer(999), 500000, M_COLOR_RED);
		return;
	}
	else
	{
		sLangChange.LoadStringA(IDS_STRING1423);	//카메라 모듈 초기화 완료.
		pFrame->putListLog(sLangChange);
	}

	pFrame->m_bMiuRun = false;
	pFrame->m_csLock_Miu.Unlock();

	sLangChange.LoadStringA(IDS_STRING573);	//Frame Grabber 초기화
	pFrame->putListLog(sLangChange);
}


void CCCDCtrlDlg::OnBnClickedButtonInitMiu()
{
}


void CCCDCtrlDlg::OnBnClickedButtonVcmReady()
{
	MIU.MoveVCM_Code(0);
}


void CCCDCtrlDlg::OnBnClickedButtonCodeWrite()
{
	int code;
	code = GetDlgItemInt(IDC_EDIT1);
	MIU.MoveVCM_Code(code);
}

void CCCDCtrlDlg::OnBnClickedCurMeasure()
{
	float	cur ;
	char	writeData[256] ;

//	MIU.GetCurrent ( &cur );  //m_cPcie.CM_GetDynamicCurrent(&cur1, &cur2, &cur3, &cur4) ;
	sprintf_s(writeData, 256, "%f", cur) ;
	GetDlgItem(IDC_CUR_EDIT)->SetWindowText(writeData);
	
}


void CCCDCtrlDlg::OnBnClickedStopLive()
{
	MIU.StopLive();
	
}


void CCCDCtrlDlg::OnBnClickedSensorWrite()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

		bool  b_PCB_cover_push_down = Dio.PCBPushSocketCheck(true, false);
		if(b_PCB_cover_push_down==true)
		{
			sLangChange=_T("Cover Close");
			pFrame->putListLog(sLangChange);
		}
		else
		{
			sLangChange=_T("Cover Open");
			pFrame->putListLog(sLangChange);
		}

	CString sValue;
//	sValue=pFrame->getSensorID();


return;

	//MIUWriteRegister(gDeviceIndex, (MIU_REG_TYPE)REG_IIC1, 0x0A02, 0x1F);
	//MIUWriteRegister(gDeviceIndex, (MIU_REG_TYPE)REG_IIC1, 0x0A00, 0x01);

	//MIUReadRegister(gDeviceIndex, (MIU_REG_TYPE)REG_IIC1, (unsigned short)0x0A22, (unsigned short*)&nData);


return;
}


void CCCDCtrlDlg::OnBnClickedSensorRead()
{
	//int addr;
	int data[4]={0,0,0,0};
	CString sData;

//	sData = MIU.SensorRegRead(0x50,0x0000,13);
//	sData = MIU.SensorRegRead(0x50,0x0010,12);
//	sData = MIU.SensorRegRead(0x50,0x0030,7);
	//CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	//data =pFrame->GetRevisionNumber();
}


void CCCDCtrlDlg::OnBnClickedBtnTest()
{
	//MbufPut(vision.MilGrabImageChild[3], MIU.m_acvChildImage[1]->imageData);
	//MbufPut(vision.MilGrabImageChild[4], MIU.m_acvChildImage[1]->imageData);
	//MbufPut(vision.MilGrabImageChild[5], MIU.m_acvChildImage[1]->imageData);

	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	pFrame->Update_CCD_Display();
}



void CCCDCtrlDlg::OnBnClickedCheckGpio15()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
//	int		gpioVal ;
	
}


void CCCDCtrlDlg::OnBnClickedCheckGpio13()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
//	int		gpioVal ;
	

}


void CCCDCtrlDlg::OnBnClickedCheckGpio19()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
//	int		gpioVal ;
	

}


void CCCDCtrlDlg::OnBnClickedCheckGpio21()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
//	int		gpioVal ;
	

}


void CCCDCtrlDlg::OnBnClickedCheckGpio25()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
//	int		gpioVal ;
	

}


void CCCDCtrlDlg::OnBnClickedCheckGpio27()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	//int		gpioVal ;
	

}


void CCCDCtrlDlg::OnBnClickedButtonGetGpio31()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	//int		gpioVal ;


}


void CCCDCtrlDlg::OnBnClickedButtonGetGpio33()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	//int		gpioVal ;


}


void CCCDCtrlDlg::OnBnClickedButtonUartSend()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	CString		str ;	
//	int			data ;
//	__int64		wdData ;
//	int			ret ;


	
	return ;
}


void CCCDCtrlDlg::OnBnClickedButtonUartRxGet()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	//int	data;
	//int ret;
	//CString		str ;

}
