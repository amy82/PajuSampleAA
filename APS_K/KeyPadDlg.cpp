// KeyPadDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AA Bonder.h"
#include "KeyPadDlg.h"
#include "afxdialogex.h"


// CKeyPadDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CKeyPadDlg, CDialogEx)

	CKeyPadDlg::CKeyPadDlg(int maxchar, char* getkeypad, CWnd* pParent)
	: CDialogEx(CKeyPadDlg::IDD, pParent)
{
	m_FirstFlag = TRUE;
	m_intMaxChar =  maxchar;

	m_strKeyPad = getkeypad; 
	if( m_strKeyPad.Find('.') == -1 ){
		m_nPointKeyPad = 0;
	}else{
		m_nPointKeyPad = 6;
	}
}

CKeyPadDlg::~CKeyPadDlg()
{

}

void CKeyPadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LABEL_MODIFY_DATA, m_labelModifyData);
}


BEGIN_MESSAGE_MAP(CKeyPadDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_1, &CKeyPadDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_2, &CKeyPadDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_3, &CKeyPadDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_4, &CKeyPadDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON_5, &CKeyPadDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON_6, &CKeyPadDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON_7, &CKeyPadDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON_8, &CKeyPadDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON_9, &CKeyPadDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON_0, &CKeyPadDlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON_A, &CKeyPadDlg::OnBnClickedButtonA)
	ON_BN_CLICKED(IDC_BUTTON_B, &CKeyPadDlg::OnBnClickedButtonB)
	ON_BN_CLICKED(IDC_BUTTON_C, &CKeyPadDlg::OnBnClickedButtonC)
	ON_BN_CLICKED(IDC_BUTTON_D, &CKeyPadDlg::OnBnClickedButtonD)
	ON_BN_CLICKED(IDC_BUTTON_E, &CKeyPadDlg::OnBnClickedButtonE)
	ON_BN_CLICKED(IDC_BUTTON_F, &CKeyPadDlg::OnBnClickedButtonF)
	ON_BN_CLICKED(IDC_BUTTON_G, &CKeyPadDlg::OnBnClickedButtonG)
	ON_BN_CLICKED(IDC_BUTTON_H, &CKeyPadDlg::OnBnClickedButtonH)
	ON_BN_CLICKED(IDC_BUTTON_I, &CKeyPadDlg::OnBnClickedButtonI)
	ON_BN_CLICKED(IDC_BUTTON_J, &CKeyPadDlg::OnBnClickedButtonJ)
	ON_BN_CLICKED(IDC_BUTTON_K, &CKeyPadDlg::OnBnClickedButtonK)
	ON_BN_CLICKED(IDC_BUTTON_L, &CKeyPadDlg::OnBnClickedButtonL)
	ON_BN_CLICKED(IDC_BUTTON_N, &CKeyPadDlg::OnBnClickedButtonN)
	ON_BN_CLICKED(IDC_BUTTON_M, &CKeyPadDlg::OnBnClickedButtonM)
	ON_BN_CLICKED(IDC_BUTTON_O, &CKeyPadDlg::OnBnClickedButtonO)
	ON_BN_CLICKED(IDC_BUTTON_P, &CKeyPadDlg::OnBnClickedButtonP)
	ON_BN_CLICKED(IDC_BUTTON_Q, &CKeyPadDlg::OnBnClickedButtonQ)
	ON_BN_CLICKED(IDC_BUTTON_R, &CKeyPadDlg::OnBnClickedButtonR)
	ON_BN_CLICKED(IDC_BUTTON_S, &CKeyPadDlg::OnBnClickedButtonS)
	ON_BN_CLICKED(IDC_BUTTON_T, &CKeyPadDlg::OnBnClickedButtonT)
	ON_BN_CLICKED(IDC_BUTTON_U, &CKeyPadDlg::OnBnClickedButtonU)
	ON_BN_CLICKED(IDC_BUTTON_V, &CKeyPadDlg::OnBnClickedButtonV)
	ON_BN_CLICKED(IDC_BUTTON_W, &CKeyPadDlg::OnBnClickedButtonW)
	ON_BN_CLICKED(IDC_BUTTON_X, &CKeyPadDlg::OnBnClickedButtonX)
	ON_BN_CLICKED(IDC_BUTTON_Y, &CKeyPadDlg::OnBnClickedButtonY)
	ON_BN_CLICKED(IDC_BUTTON_Z, &CKeyPadDlg::OnBnClickedButtonZ)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &CKeyPadDlg::OnBnClickedButtonBack)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CKeyPadDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CKeyPadDlg::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_ESC, &CKeyPadDlg::OnBnClickedButtonEsc)
	ON_BN_CLICKED(IDC_BUTTON_COMMA, &CKeyPadDlg::OnBnClickedButtonComma)
	ON_BN_CLICKED(IDC_BUTTON_UNDER_BAR, &CKeyPadDlg::OnBnClickedButtonUnderBar)
END_MESSAGE_MAP()


// CKeyPadDlg 메시지 처리기입니다.


void CKeyPadDlg::OnBnClickedButton1()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "1";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButton2()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "2";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButton3()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "3";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButton4()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "4";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButton5()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "5";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButton6()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "6";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButton7()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "7";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButton8()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "8";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButton9()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "9";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButton0()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "0";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButtonA()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "A";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButtonB()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "B";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButtonC()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "C";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButtonD()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "D";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButtonE()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "E";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButtonF()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "F";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButtonG()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "G";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButtonH()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "H";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButtonI()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "I";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButtonJ()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "J";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButtonK()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "K";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButtonL()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "L";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButtonN()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "N";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButtonM()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "M";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButtonO()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "O";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButtonP()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "P";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButtonQ()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "Q";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButtonR()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "R";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButtonS()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "S";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButtonT()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "T";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButtonU()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "U";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButtonV()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "V";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButtonW()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "W";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButtonX()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "X";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButtonY()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "Y";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButtonZ()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += "Z";
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButtonBack()
{
	m_FirstFlag = FALSE;

	int len = m_strKeyPad.GetLength();
	if(len)
	{
		m_strKeyPad.SetAt(len-1,' ');
		m_strKeyPad.TrimRight();
		UpdateDisplay();
	}
}
void CKeyPadDlg::OnBnClickedButtonClear()
{
	m_strKeyPad = "";	
	UpdateDisplay();
}
void CKeyPadDlg::OnBnClickedButtonOk()
{
	if(m_strKeyPad == ""){
		CDialog::OnCancel();
	}else{
		CDialog::OnOK();
	}
}
void CKeyPadDlg::OnBnClickedButtonEsc()
{
	CDialog::OnCancel();
}

BOOL CKeyPadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_labelModifyData
		.SetBkColor(RGB(166,202,240))
		.SetTextColor(M_COLOR_BLACK)
		.SetFontBold(TRUE)
		.SetText(m_strKeyPad)
		.SetFontSize(17);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}



BOOL CKeyPadDlg::VerifyMaxChar()
{
	if( m_strKeyPad.GetLength() >= m_intMaxChar ){
		return FALSE;
	}else{
		return TRUE;
	}
}


void CKeyPadDlg::UpdateDisplay()
{
	m_labelModifyData.SetWindowText(m_strKeyPad);
}


CString CKeyPadDlg::GetstrKeypad()
{
	return m_strKeyPad;	
}


BOOL CKeyPadDlg::PreTranslateMessage(MSG* pMsg)
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
		else if ( pMsg->wParam == 'A' || pMsg->wParam == 'a')
		{
			OnBnClickedButtonA();
		}
		else if ( pMsg->wParam == 'B' || pMsg->wParam == 'b')
		{
			OnBnClickedButtonB();
		}
		else if ( pMsg->wParam == 'C' || pMsg->wParam == 'c')
		{
			OnBnClickedButtonC();
		}
		else if ( pMsg->wParam == 'D' || pMsg->wParam == 'd')
		{
			OnBnClickedButtonD();
		}
		else if ( pMsg->wParam == 'E' || pMsg->wParam == 'e')
		{
			OnBnClickedButtonE();
		}
		else if ( pMsg->wParam == 'F' || pMsg->wParam == 'f')
		{
			OnBnClickedButtonF();
		}
		else if ( pMsg->wParam == 'G' || pMsg->wParam == 'g')
		{
			OnBnClickedButtonG();
		}
		else if ( pMsg->wParam == 'H' || pMsg->wParam == 'h')
		{
			OnBnClickedButtonH();
		}
		else if ( pMsg->wParam == 'I' || pMsg->wParam == 'i')
		{
			OnBnClickedButtonI();
		}
		else if ( pMsg->wParam == 'J' || pMsg->wParam == 'j')
		{
			OnBnClickedButtonJ();
		}
		else if ( pMsg->wParam == 'K' || pMsg->wParam == 'k')
		{
			OnBnClickedButtonK();
		}
		else if ( pMsg->wParam == 'L' || pMsg->wParam == 'l')
		{
			OnBnClickedButtonL();
		}
		else if ( pMsg->wParam == 'N' || pMsg->wParam == 'n')
		{
			OnBnClickedButtonN();
		}
		else if ( pMsg->wParam == 'M' || pMsg->wParam == 'm')
		{
			OnBnClickedButtonM();
		}
		else if ( pMsg->wParam == 'O' || pMsg->wParam == 'o')
		{
			OnBnClickedButtonO();
		}
		else if ( pMsg->wParam == 'P' || pMsg->wParam == 'p')
		{
			OnBnClickedButtonP();
		}
		else if ( pMsg->wParam == 'Q' || pMsg->wParam == 'q')
		{
			OnBnClickedButtonQ();
		}
		else if ( pMsg->wParam == 'R' || pMsg->wParam == 'r')
		{
			OnBnClickedButtonR();
		}
		else if ( pMsg->wParam == 'S' || pMsg->wParam == 's')
		{
			OnBnClickedButtonS();
		}
		else if ( pMsg->wParam == 'T' || pMsg->wParam == 't')
		{
			OnBnClickedButtonT();
		}
		else if ( pMsg->wParam == 'U' || pMsg->wParam == 'u')
		{
			OnBnClickedButtonU();
		}
		else if ( pMsg->wParam == 'V' || pMsg->wParam == 'v')
		{
			OnBnClickedButtonV();
		}
		else if ( pMsg->wParam == 'W' || pMsg->wParam == 'w')
		{
			OnBnClickedButtonW();
		}
		else if ( pMsg->wParam == 'X' || pMsg->wParam == 'x')
		{
			OnBnClickedButtonX();
		}
		else if ( pMsg->wParam == 'Y' || pMsg->wParam == 'y')
		{
			OnBnClickedButtonY();
		}
		else if ( pMsg->wParam == 'Z' || pMsg->wParam == 'z')
		{
			OnBnClickedButtonZ();
		}
		else if ( pMsg->wParam == VK_BACK )
		{
			OnBnClickedButtonBack();
		}
		else if ( pMsg->wParam == VK_RETURN )
		{
			OnBnClickedButtonOk();
			return FALSE;
		}
		else if ( pMsg->wParam == VK_ESCAPE )
		{
			OnBnClickedButtonEsc();
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CKeyPadDlg::OnBnClickedButtonComma()
{
	if( m_FirstFlag )
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if( !VerifyMaxChar() ) return;

	m_strKeyPad += ".";
	UpdateDisplay();
}


void CKeyPadDlg::OnBnClickedButtonUnderBar()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_FirstFlag)
	{
		m_FirstFlag = FALSE;
		m_strKeyPad = "";
	}

	if (!VerifyMaxChar()) return;

	m_strKeyPad += "_";
	UpdateDisplay();
}
