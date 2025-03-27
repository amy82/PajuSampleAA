// InformDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "InformDlg.h"

// CInformDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CInformDlg, CDialogEx)

	CInformDlg::CInformDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInformDlg::IDD, pParent)
{
}


CInformDlg::~CInformDlg()
{
}

void CInformDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LABEL_MESSAGE, m_labelInformMsg);
}


BEGIN_MESSAGE_MAP(CInformDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CInformDlg::OnBnClickedButtonClose)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CInformDlg 메시지 처리기입니다.



BOOL CInformDlg::OnInitDialog()
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


	titleStr	= "Inform Message Box";
	color		= M_COLOR_RED;
	bkColor		= M_COLOR_BLACK;

	m_labelInformMsg
		.SetBkColor(color)
		.SetTextColor(bkColor)
		.SetFontBold(TRUE)
		.SetText(m_sMsg)
		.SetFontSize(22);


	this->SetWindowText(titleStr);
	this->Invalidate();

	return TRUE;
}


void CInformDlg::OnBnClickedButtonClose()
{
	Dio.setAlarm(ALARM_OFF);

	CDialog::OnOK();
}