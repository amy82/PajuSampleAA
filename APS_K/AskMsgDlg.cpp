// AskMsgDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AA BonderDlg.h"
#include "AskMsgDlg.h"
#include "afxdialogex.h"


// CAskMsgDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAskMsgDlg, CDialogEx)

	CAskMsgDlg::CAskMsgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAskMsgDlg::IDD, pParent)
{
}

CAskMsgDlg::~CAskMsgDlg()
{
}

void CAskMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LABEL_MESSAGE, m_labelMsg);
}


BEGIN_MESSAGE_MAP(CAskMsgDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_YES, &CAskMsgDlg::OnBnClickedButtonYes)
	ON_BN_CLICKED(IDC_BUTTON_NO, &CAskMsgDlg::OnBnClickedButtonNo)
END_MESSAGE_MAP()


// CAskMsgDlg 메시지 처리기입니다.


BOOL CAskMsgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_labelMsg
		.SetBkColor(M_COLOR_LIGHT_BLUE)
		.SetText(m_sMsg)
		.SetFontBold(TRUE)
		.SetFontSize(20);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CAskMsgDlg::OnBnClickedButtonYes()
{
	CDialogEx::OnOK();
}


void CAskMsgDlg::OnBnClickedButtonNo()
{
	CDialogEx::OnCancel();
}
