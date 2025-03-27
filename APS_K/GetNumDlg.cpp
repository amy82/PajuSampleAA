// GetNumDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AA Bonder.h"
#include "GetNumDlg.h"
#include "afxdialogex.h"


// CGetNumDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CGetNumDlg, CDialogEx)

CGetNumDlg::CGetNumDlg(int maxchar, char* getnum, CWnd* pParent)
	: CDialogEx(CGetNumDlg::IDD, pParent)
{
	m_FirstFlag = TRUE;
	m_intMaxChar =  maxchar;


	m_strGetNum = getnum;
	
	if( m_strGetNum.Find('.') == -1 )
		m_nPointNum = 0;
	else
		m_nPointNum = 6;
}

CGetNumDlg::~CGetNumDlg()
{
}

void CGetNumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LABEL_MODIFY_DATA, m_labelModifyData);
}


BEGIN_MESSAGE_MAP(CGetNumDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_1, &CGetNumDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_2, &CGetNumDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_3, &CGetNumDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_4, &CGetNumDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON_, &CGetNumDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON_6, &CGetNumDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON_7, &CGetNumDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON_8, &CGetNumDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON_9, &CGetNumDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON_0, &CGetNumDlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON_DOT, &CGetNumDlg::OnBnClickedButtonDot)
	ON_BN_CLICKED(IDC_BUTTON_SIGN, &CGetNumDlg::OnBnClickedButtonSign)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &CGetNumDlg::OnBnClickedButtonBack)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CGetNumDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CGetNumDlg::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_ESC, &CGetNumDlg::OnBnClickedButtonEsc)
END_MESSAGE_MAP()


// CGetNumDlg 메시지 처리기입니다.


void CGetNumDlg::OnBnClickedButton1()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strGetNum = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strGetNum += "1";
	UpdateDisplay();
}


void CGetNumDlg::OnBnClickedButton2()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strGetNum = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strGetNum += "2";
	UpdateDisplay();
}


void CGetNumDlg::OnBnClickedButton3()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strGetNum = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strGetNum += "3";
	UpdateDisplay();
}


void CGetNumDlg::OnBnClickedButton4()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strGetNum = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strGetNum += "4";
	UpdateDisplay();
}


void CGetNumDlg::OnBnClickedButton5()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strGetNum = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strGetNum += "5";
	UpdateDisplay();
}


void CGetNumDlg::OnBnClickedButton6()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strGetNum = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strGetNum += "6";
	UpdateDisplay();
}


void CGetNumDlg::OnBnClickedButton7()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strGetNum = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strGetNum += "7";
	UpdateDisplay();
}


void CGetNumDlg::OnBnClickedButton8()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strGetNum = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strGetNum += "8";
	UpdateDisplay();
}


void CGetNumDlg::OnBnClickedButton9()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strGetNum = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strGetNum += "9";
	UpdateDisplay();
}


void CGetNumDlg::OnBnClickedButton0()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strGetNum = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strGetNum += "0";
	UpdateDisplay();
}


void CGetNumDlg::OnBnClickedButtonDot()
{
	if( !VerifyMaxChar() ) return;

	m_strGetNum += ".";	
	UpdateDisplay();
}


void CGetNumDlg::OnBnClickedButtonSign()
{
	if( !m_strGetNum.GetLength() ) return;

	if(m_strGetNum.GetAt(0) == '-')
	{
		m_strGetNum.Remove('-');
	}
	else
	{
		m_strGetNum.Insert(0,'-');
	}

	UpdateDisplay();
}


void CGetNumDlg::OnBnClickedButtonBack()
{
	m_FirstFlag = FALSE;

	int len = m_strGetNum.GetLength();
	if(len)
	{
		m_strGetNum.SetAt(len-1,' ');
		m_strGetNum.TrimRight();
		UpdateDisplay();
	}
}


void CGetNumDlg::OnBnClickedButtonClear()
{
	m_strGetNum = "";	
	UpdateDisplay();
}


void CGetNumDlg::OnBnClickedButtonOk()
{
	if(m_strGetNum == "")
		CDialog::OnCancel();
	else
		CDialog::OnOK();
}


void CGetNumDlg::OnBnClickedButtonEsc()
{
	CDialog::OnCancel();
}


BOOL CGetNumDlg::VerifyMaxChar()
{
	if( m_strGetNum.GetLength() >= m_intMaxChar ) return FALSE;
	else return TRUE;
}


void CGetNumDlg::UpdateDisplay()
{
	m_labelModifyData.SetWindowText(m_strGetNum);
}


CString CGetNumDlg::GetstrNum()
{
	return m_strGetNum;	
}


BOOL CGetNumDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if(m_strTitle.GetLength()>3)
		this->SetWindowText(m_strTitle);

	m_labelModifyData
		.SetBkColor(RGB(166,202,240))
		.SetTextColor(M_COLOR_BLACK)
		.SetFontBold(TRUE)
		.SetText(m_strGetNum)
		.SetFontSize(13);

	return TRUE;
}


BOOL CGetNumDlg::PreTranslateMessage(MSG* pMsg)
{
	if ( pMsg->message == WM_KEYDOWN )
	{
		if ( pMsg->wParam == '0' || pMsg->wParam == 96 )
		{
			OnBnClickedButton0();
		}
		else if ( pMsg->wParam == '1' || pMsg->wParam == 97 )
		{
			OnBnClickedButton1();
		}
		else if ( pMsg->wParam == '2' || pMsg->wParam == 98 )
		{
			OnBnClickedButton2();
		}
		else if ( pMsg->wParam == '3' || pMsg->wParam == 99 )
		{
			OnBnClickedButton3();
		}
		else if ( pMsg->wParam == '4' || pMsg->wParam == 100 )
		{
			OnBnClickedButton4();
		}
		else if ( pMsg->wParam == '5' || pMsg->wParam == 101 )
		{
			OnBnClickedButton5();
		}
		else if ( pMsg->wParam == '6' || pMsg->wParam == 102 )
		{
			OnBnClickedButton6();
		}
		else if ( pMsg->wParam == '7' || pMsg->wParam == 103 )
		{
			OnBnClickedButton7();
		}
		else if ( pMsg->wParam == '8' || pMsg->wParam == 104 )
		{
			OnBnClickedButton8();
		}
		else if ( pMsg->wParam == '9' || pMsg->wParam == 105 )
		{
			OnBnClickedButton9();
		}
		else if ( pMsg->wParam == VK_BACK )
		{
			OnBnClickedButtonBack();
		}
		else if ( pMsg->wParam == VK_OEM_PERIOD || pMsg->wParam == 110 )
		{
			OnBnClickedButtonDot();
		}
		else if ( pMsg->wParam == VK_RETURN )
		{
			OnBnClickedButtonOk();
		}
		else if ( pMsg->wParam == VK_ESCAPE )
		{
			OnBnClickedButtonEsc();
		}
		else if ( pMsg->wParam == VK_OEM_MINUS )
		{
			OnBnClickedButtonSign();
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}