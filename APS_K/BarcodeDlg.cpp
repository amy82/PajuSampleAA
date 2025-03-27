// BarcodeDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BarcodeDlg.h"


// CBarcodeDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CBarcodeDlg, CDialogEx)

CBarcodeDlg::CBarcodeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBarcodeDlg::IDD, pParent)
	, m_Edit_strBarcode(_T(""))
{

}

CBarcodeDlg::~CBarcodeDlg()
{
}

void CBarcodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Edit_strBarcode);
}


BEGIN_MESSAGE_MAP(CBarcodeDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_BARCODE_PORT_OPEN, &CBarcodeDlg::OnBnClickedBtnBarcodePortOpen)
	ON_BN_CLICKED(IDC_BTN_BARCODE_PORT_ClOSE, &CBarcodeDlg::OnBnClickedBtnBarcodePortClose)
	ON_BN_CLICKED(IDC_BTN_BARCODE_READE, &CBarcodeDlg::OnBnClickedBtnBarcodeReade)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_BARCODE_READE_STOP, &CBarcodeDlg::OnBnClickedBtnBarcodeReadeStop)
	ON_BN_CLICKED(IDC_BTN_BARCODE_PORT_OPEN, &CBarcodeDlg::OnBnClickedBtnBarcodePortOpen)
END_MESSAGE_MAP()


// CBarcodeDlg 메시지 처리기입니다.


void CBarcodeDlg::OnBnClickedBtnBarcodePortOpen()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	CString sMsg;
	if( !barcode.func_Comm_Open(sysData.iCommPort[COMM_BARCODE], sysData.iBaudRate[COMM_BARCODE]) )
	{
		sLangChange.LoadStringA(IDS_STRING263);	//"[바코드 리더기] 통신 연결 실패"
		sMsg.Format(sLangChange);

		delayMsg(sMsg.GetBuffer(99), 50000, M_COLOR_RED);
		pFrame->putListLog(sMsg);
		Task.bConnectBarcode = false;
		return;
	}


	sLangChange.LoadStringA(IDS_STRING262);
	sMsg.Format(sLangChange);
	Task.bConnectBarcode = true;
	pFrame->putListLog(sMsg);
}


void CBarcodeDlg::OnBnClickedBtnBarcodePortClose()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	CString sMsg;

	barcode.func_Comm_Close();
	sLangChange.LoadStringA(IDS_STRING263);
	sMsg.Format(sLangChange);
	Task.bConnectBarcode = false;
	delayMsg(sMsg.GetBuffer(99), 50000, M_COLOR_RED);
	pFrame->putListLog(sMsg);
}


void CBarcodeDlg::OnBnClickedBtnBarcodeReade()
{
	m_Edit_strBarcode = "";
	SetTimer(999,100,NULL);
}


void CBarcodeDlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == 999)
	{
		CString BarcodeId;

		if( barcode.func_Barcode_Read(BarcodeId) )
		{
			memset(Task.ChipID, 0x00, 256);
 			m_Edit_strBarcode = BarcodeId;
			KillTimer(999);
		}

		UpdateData(FALSE);
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CBarcodeDlg::OnBnClickedBtnBarcodeReadeStop()
{
	KillTimer(999);
}