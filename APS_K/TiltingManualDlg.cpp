// TiltingManualDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TiltingManualDlg.h"
#include "afxdialogex.h"
// CTiltingManualDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTiltingManualDlg, CDialogEx)

CTiltingManualDlg::CTiltingManualDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTiltingManualDlg::IDD, pParent)
{

}

CTiltingManualDlg::~CTiltingManualDlg()
{
}

void CTiltingManualDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_OK, m_btnOk);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_btnStop);
	DDX_Control(pDX, IDC_EDIT_TILTING_X, edit_TiltingTX);
	DDX_Control(pDX, IDC_EDIT_TILTING_Y, edit_TiltingTY);
}


BEGIN_MESSAGE_MAP(CTiltingManualDlg, CDialogEx)
	ON_STN_CLICKED(IDC_EDIT_TILTING_X, &CTiltingManualDlg::OnStnClickedEditTiltingX)
	ON_STN_CLICKED(IDC_EDIT_TILTING_Y, &CTiltingManualDlg::OnStnClickedEditTiltingY)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CTiltingManualDlg::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CTiltingManualDlg::OnBnClickedButtonStop)
END_MESSAGE_MAP()


// CTiltingManualDlg 메시지 처리기입니다.


BOOL CTiltingManualDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	Task.dTiltingManual[0] = Task.dTiltingManual[1] = 0.0;

	edit_TiltingTX.SetBkColor(M_COLOR_WHITE);
	edit_TiltingTY.SetBkColor(M_COLOR_WHITE);
	
	SetDlgItemText(IDC_EDIT_TILTING_X, "0.000");
	SetDlgItemText(IDC_EDIT_TILTING_Y, "0.000");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CTiltingManualDlg::OnStnClickedEditTiltingX()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		edit_TiltingTX.SetText(dlg.GetstrNum());
	}
}


void CTiltingManualDlg::OnStnClickedEditTiltingY()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		edit_TiltingTY.SetText(dlg.GetstrNum());
	}
}


void CTiltingManualDlg::OnBnClickedButtonOk()
{
	UpdateData(true);
	CString sEditData;

	GetDlgItemText(IDC_EDIT_TILTING_X, sEditData);
	Task.dTiltingManual[0] = atof(sEditData);
	GetDlgItemText(IDC_EDIT_TILTING_Y, sEditData);
	Task.dTiltingManual[1] = atof(sEditData);
	
	Task.m_iRtnTiltingDlg = 1;
	CDialog::OnOK();
}


void CTiltingManualDlg::OnBnClickedButtonStop()
{
	Task.m_iRtnTiltingDlg = 0;
	CDialog::OnCancel();
}
