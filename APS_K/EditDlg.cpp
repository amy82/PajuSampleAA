// EditDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AA Bonder.h"
#include "EditDlg.h"
#include "afxdialogex.h"


// CEditDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CEditDlg, CDialogEx)

CEditDlg::CEditDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEditDlg::IDD, pParent)
{

}

CEditDlg::~CEditDlg()
{
}

void CEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEditDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CEditDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CEditDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CEditDlg 메시지 처리기입니다.


void CEditDlg::OnBnClickedOk()
{
	GetDlgItem(IDC_EDIT_TEXT)->GetWindowText(m_strText);

	CDialogEx::OnOK();
}


void CEditDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}


CString CEditDlg::getTextOnEdit()
{
	return m_strText;
}