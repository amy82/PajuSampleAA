// DelayMsgDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DelayMsgDlg.h"

// CDelayMsgDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDelayMsgDlg, CDialogEx)

	CDelayMsgDlg::CDelayMsgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDelayMsgDlg::IDD, pParent)
{

}

CDelayMsgDlg::~CDelayMsgDlg()
{
}

void CDelayMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LABEL_MESSAGE, m_labelDelayMsg);
}


BEGIN_MESSAGE_MAP(CDelayMsgDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CDelayMsgDlg::OnBnClickedButtonClose)
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()





BOOL CDelayMsgDlg::OnInitDialog()
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

	timerRunFlag = false;
	sLangChange.LoadStringA(IDS_STRING493);
	delay		= 3000;
	titleStr	= sLangChange;	//Delay Message Show
	color		= M_COLOR_GREEN;
	bkColor		= M_COLOR_BLACK;

	m_labelDelayMsg
		.SetBkColor(color)
		.SetTextColor(bkColor)
		.SetFontBold(TRUE)
		.SetText(sLangChange)	//Delay Message Show
		.SetFontSize(22);

	return TRUE;
}


void CDelayMsgDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if(bShow)
	{
		showTime = CTime::GetCurrentTime();
	
		m_labelDelayMsg.SetBkColor(color);
		m_labelDelayMsg.SetTextColor(bkColor);
		this->SetWindowText(titleStr);

		timerRunFlag = false;

		SetTimer(MSG_TIMER, 200, NULL);
	}
	else
	{
		KillTimer(MSG_TIMER);
	}
}

void CDelayMsgDlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent==MSG_TIMER)
	{
		if(!timerRunFlag)
		{
			timerRunFlag = true;

			curTime = CTime::GetCurrentTime();
			CTimeSpan tmp = curTime - showTime;

			int sec = (int)tmp.GetTotalSeconds();

			if(sec>=delay / 1000)
			{
				KillTimer(MSG_TIMER);
				this->ShowWindow(false);
			}

			timerRunFlag = false;
		}
		m_labelDelayMsg.Invalidate();
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CDelayMsgDlg::OnBnClickedButtonClose()
{
	Dio.setAlarm(ALARM_OFF);
	this->ShowWindow(false);
}
