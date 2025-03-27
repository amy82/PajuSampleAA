// DisplacementDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DisplacementDlg.h"
// CDisplacementDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDisplacementDlg, CDialogEx)

CDisplacementDlg::CDisplacementDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDisplacementDlg::IDD, pParent)
	, m_Edit_ResultVal(0)
{

}

CDisplacementDlg::~CDisplacementDlg()
{
}

void CDisplacementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Edit_ResultVal);
}


BEGIN_MESSAGE_MAP(CDisplacementDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_COMM_OPEN, &CDisplacementDlg::OnBnClickedBtnCommOpen)
	ON_BN_CLICKED(IDC_BTN_COMM_CLOSE, &CDisplacementDlg::OnBnClickedBtnCommClose)
	ON_BN_CLICKED(IDC_BTN_SCAN, &CDisplacementDlg::OnBnClickedBtnScan)
	ON_BN_CLICKED(IDC_BTN_DLG_CLOSE, &CDisplacementDlg::OnBnClickedBtnDlgClose)
	ON_BN_CLICKED(IDC_BTN_ZERO_ON, &CDisplacementDlg::OnBnClickedBtnZeroOn)
	ON_BN_CLICKED(IDC_BTN_ZERO_OFF, &CDisplacementDlg::OnBnClickedBtnZeroOff)
	ON_BN_CLICKED(IDC_BTN_KEY_LOCK, &CDisplacementDlg::OnBnClickedBtnKeyLock)
	ON_BN_CLICKED(IDC_BTN_KEY_UNLOCK, &CDisplacementDlg::OnBnClickedBtnKeyUnlock)
END_MESSAGE_MAP()


// CDisplacementDlg 메시지 처리기입니다.

BOOL CDisplacementDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	//SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	//SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CDisplacementDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		//CAboutDlg dlgAbout;
		//dlgAbout.DoModal();
	}
	else
	{
		//CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.


// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.

void CDisplacementDlg::OnBnClickedBtnCommOpen()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	CString sMsg;
	if( !Keyence.func_RS232_CommOpen(sysData.iCommPort[COMM_LASER], sysData.iBaudRate[COMM_LASER]) )
	{
		sLangChange.LoadStringA(IDS_STRING275);
		sMsg.Format(sLangChange);

		delayMsg(sMsg.GetBuffer(99), 50000, M_COLOR_RED);
		pFrame->putListLog(sMsg);
		return;

	}
	sLangChange.LoadStringA(IDS_STRING274);
	sMsg.Format(sLangChange);
	pFrame->putListLog(sMsg);

}


void CDisplacementDlg::OnBnClickedBtnCommClose()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	CString sMsg;
	Keyence.func_RS232_CommClose();
	sLangChange.LoadStringA(IDS_STRING277);
	sMsg.Format(sLangChange);
	delayMsg(sMsg.GetBuffer(99), 50000, M_COLOR_RED);
	pFrame->putListLog(sMsg);
}


void CDisplacementDlg::OnBnClickedBtnScan()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	CString sMsg, sRecv;
	CString sMsgBuff = "";
	CString sResult = "";
	CString Err = "";
	double	dLaserVal;

	if( !Keyence.func_LT9030_Scan(dLaserVal) )
	{
		sLangChange.LoadStringA(IDS_STRING273);
		sMsg.Format(sLangChange);
		delayMsg(sMsg.GetBuffer(99), 50000, M_COLOR_RED);
		pFrame->putListLog(sMsg);
		return ;
	}

	m_Edit_ResultVal = dLaserVal;
	UpdateData(FALSE);
}


void CDisplacementDlg::OnBnClickedBtnDlgClose()
{
	CDialog::OnOK();
}


void CDisplacementDlg::OnBnClickedBtnZeroOn()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	CString sMsg;
	if( !Keyence.func_LT9030_AutoZeroSet(0, true) )
	{
		sLangChange.LoadStringA(IDS_STRING272);
		sMsg.Format(sLangChange);
		delayMsg(sMsg.GetBuffer(99), 50000, M_COLOR_RED);
		pFrame->putListLog(sMsg);
	}

		sLangChange.LoadStringA(IDS_STRING270);
		sMsg.Format(sLangChange);
		delayMsg(sMsg.GetBuffer(99), 50000, M_COLOR_RED);
		pFrame->putListLog(sMsg);
}


void CDisplacementDlg::OnBnClickedBtnZeroOff()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	CString sMsg;
	if( !Keyence.func_LT9030_AutoZeroSet(0, false) )
	{
		sLangChange.LoadStringA(IDS_STRING271);
		sMsg.Format(sLangChange);
		delayMsg(sMsg.GetBuffer(99), 50000, M_COLOR_RED);
		pFrame->putListLog(sMsg);
	}
		sLangChange.LoadStringA(IDS_STRING269);
		sMsg.Format(sLangChange);
		delayMsg(sMsg.GetBuffer(99), 50000, M_COLOR_RED);
		pFrame->putListLog(sMsg);
}


void CDisplacementDlg::OnBnClickedBtnKeyLock()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	CString sMsg;
	if( !Keyence.func_LT9030_KeyLock(true) )
	{
		sLangChange.LoadStringA(IDS_STRING268);
		sMsg.Format(sLangChange);
		delayMsg(sMsg.GetBuffer(99), 50000, M_COLOR_RED);
		pFrame->putListLog(sMsg);

		return;
	}
		sLangChange.LoadStringA(IDS_STRING266);
		sMsg.Format(sLangChange);
		delayMsg(sMsg.GetBuffer(99), 50000, M_COLOR_RED);
		pFrame->putListLog(sMsg);
}


void CDisplacementDlg::OnBnClickedBtnKeyUnlock()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	CString sMsg;
	if( !Keyence.func_LT9030_KeyLock(false) )
	{
		sLangChange.LoadStringA(IDS_STRING267);
		sMsg.Format(sLangChange);

		delayMsg(sMsg.GetBuffer(99), 50000, M_COLOR_RED);
		pFrame->putListLog(sMsg);
	}

		sLangChange.LoadStringA(IDS_STRING265);
		sMsg.Format(sLangChange);
		delayMsg(sMsg.GetBuffer(99), 50000, M_COLOR_RED);
		pFrame->putListLog(sMsg);
}

