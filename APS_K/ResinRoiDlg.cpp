// ResinRoiDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AA Bonder.h"
#include "ResinRoiDlg.h"
#include "afxdialogex.h"
#include "AA BonderDlg.h"
#include "DataHandler.h"
#include "GetNumDlg.h"
#include "KeyPadDlg.h"


extern	CModelData		model;

extern CSystemData sysData;

extern	CPasswordData	password;

extern  CTask			Task;

// ResinRoiDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CResinRoiDlg, CDialog)

CResinRoiDlg::CResinRoiDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CResinRoiDlg::IDD, pParent)
{

}

CResinRoiDlg::~CResinRoiDlg()
{
}

void CResinRoiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSFLEXGRID_ARC_ROI, m_gridArcRoi);
	DDX_Control(pDX, IDC_MSFLEXGRID_LINE_ROI, m_gridLineRoi);
}


BEGIN_MESSAGE_MAP(CResinRoiDlg, CDialog)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_RESIN_ROI_SAVE, &CResinRoiDlg::OnBnClickedButtonResinRoiSave)
	ON_BN_CLICKED(IDOK, &CResinRoiDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CResinRoiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	sysData.Load();
	func_GridInit_ArcRoi();
	func_GridInit_LineRoi();


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CResinRoiDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}

// CResinRoiDlg 메시지 처리기입니다.


void CResinRoiDlg::OnBnClickedButtonResinRoiSave()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	bool passFlag = password.m_bFlag;

	if(passFlag == false)
	{
		CString strTemp;
		CKeyPadDlg keyDlg;

		sLangChange.LoadStringA(IDS_STRING891);
		keyDlg.m_strKeyPad = sLangChange;	//"Password를 입력하세요."

		if (keyDlg.DoModal()==IDOK)
		{
			strTemp = keyDlg.GetstrKeypad();
			
			passFlag = strTemp.CompareNoCase(password.m_szPassword) ? false : true;
		}
		else
		{
			return;
		}
	}

	if(passFlag)
	{
		password.m_bFlag = true;
	}
	else
	{
		sLangChange.LoadStringA(IDS_STRING892);
		errMsg2(Task.AutoFlag, sLangChange);	//"Password를 잘 못 입력했습니다."
		return;
	}
	

	CString cellStr;
	sLangChange.LoadStringA(IDS_STRING1435);	//파라미터를 저장 하시겠습니까?
	cellStr.Format(sLangChange);

	if( !askMsg(cellStr.GetBuffer(99)) )
	{
		return;
	}

	

	getData_ResinRoi();
	model.Save();
	model.Load();

	displayData_ResinRoi();
	sLangChange.LoadStringA(IDS_STRING1434);
	LogSave(sLangChange);
}


void CResinRoiDlg::func_GridInit_ArcRoi()
{
	m_gridArcRoi.SetColAlignment(0, 4);
	m_gridArcRoi.SetColAlignment(1, 4);
	m_gridArcRoi.SetColAlignment(2, 4);


	m_gridArcRoi.SetColWidth(0, 1800);
	m_gridArcRoi.SetColWidth(1, 1300);
	m_gridArcRoi.SetColWidth(2, 1300);

	sLangChange.LoadStringA(IDS_STRING545);
	m_gridArcRoi.SetTextMatrix(1, 0, _T("왼쪽 위 Center"));					
	sLangChange.LoadStringA(IDS_STRING1152);
	m_gridArcRoi.SetTextMatrix(2, 0, _T("오른쪽 위 Center"));				
	sLangChange.LoadStringA(IDS_STRING1151);
	m_gridArcRoi.SetTextMatrix(3, 0, _T("왼쪽 아래 Center"));				
	sLangChange.LoadStringA(IDS_STRING1195);
	m_gridArcRoi.SetTextMatrix(4, 0, _T("오른쪽 아래 Center"));				

	
	m_gridArcRoi.SetTextMatrix(0, 1, _T("X"));										//X"));
	
	m_gridArcRoi.SetTextMatrix(0, 2, _T("Y"));			

	m_gridArcRoi.SetRedraw(TRUE);
	m_gridArcRoi.Refresh();
}

void CResinRoiDlg::func_GridInit_LineRoi()
{
	
m_gridLineRoi.SetColAlignment(0, 4);
	m_gridLineRoi.SetColAlignment(1, 4);
	m_gridLineRoi.SetColAlignment(2, 4);


	m_gridLineRoi.SetColWidth(0, 2500);
	m_gridLineRoi.SetColWidth(1, 1300);
	m_gridLineRoi.SetColWidth(2, 1300);

	sLangChange.LoadStringA(IDS_STRING545);
	m_gridLineRoi.SetTextMatrix(1, 0, _T("직선검사 왼쪽 Start"));	
	sLangChange.LoadStringA(IDS_STRING1152);
	m_gridLineRoi.SetTextMatrix(2, 0, _T("직선검사 오른쪽 Start"));	
	sLangChange.LoadStringA(IDS_STRING1151);
	m_gridLineRoi.SetTextMatrix(3, 0, _T("직선검사 위쪽 Start"));	
	sLangChange.LoadStringA(IDS_STRING1195);
	m_gridLineRoi.SetTextMatrix(4, 0, _T("직선검사 아래쪽 Start"));	
	sLangChange.LoadStringA(IDS_STRING598);
	m_gridLineRoi.SetTextMatrix(5, 0, _T("직선검사 왼쪽 SIZE"));	
	sLangChange.LoadStringA(IDS_STRING599);
	m_gridLineRoi.SetTextMatrix(6, 0, _T("직선검사 오른쪽 SIZE"));	
																	
		
	m_gridLineRoi.SetTextMatrix(7, 0, _T("직선검사 위쪽 SIZE"));	
		
	m_gridLineRoi.SetTextMatrix(8, 0, _T("직선검사 아래쪽 SIZE"));	
		
																			//
	
	m_gridLineRoi.SetTextMatrix(0, 1, _T("X"));										//X"));
	
	m_gridLineRoi.SetTextMatrix(0, 2, _T("Y"));			

	m_gridLineRoi.SetRedraw(TRUE);
	m_gridLineRoi.Refresh();							//Y"));
}

void CResinRoiDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if(bShow)
	{
		displayData_ResinRoi();
		UpdateData(false);
	}
	else
	{
		CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
		KillTimer(MOTOR_TIMER);
	}
}

BEGIN_EVENTSINK_MAP(CResinRoiDlg, CDialogEx)
	ON_EVENT(CResinRoiDlg, IDC_MSFLEXGRID_LINE_ROI, DISPID_DBLCLICK, CResinRoiDlg::DblClickMsflexgridLineRoi, VTS_NONE)
	ON_EVENT(CResinRoiDlg, IDC_MSFLEXGRID_ARC_ROI, DISPID_DBLCLICK, CResinRoiDlg::DblClickMsflexgridArcRoi, VTS_NONE)
END_EVENTSINK_MAP()


void CResinRoiDlg::DblClickMsflexgridArcRoi()
{
	int iRow = m_gridArcRoi.GetMouseRow();
	int iCol = m_gridArcRoi.GetMouseCol();

	if ( iRow <= 0 || iCol <= 0 )	return;

	CString sCellData = m_gridArcRoi.GetTextMatrix(iRow, iCol);

	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)sCellData);

	if ( dlg.DoModal() == IDOK )
	{
		m_gridArcRoi.SetTextMatrix(iRow, iCol, dlg.GetstrNum());
	}
}

void CResinRoiDlg::DblClickMsflexgridLineRoi()
{
	int iRow = m_gridLineRoi.GetMouseRow();
	int iCol = m_gridLineRoi.GetMouseCol();

	if ( iRow <= 0 || iCol <= 0 )	return;

	CString sCellData = m_gridLineRoi.GetTextMatrix(iRow, iCol);

	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)sCellData);

	if ( dlg.DoModal() == IDOK )
	{
		m_gridLineRoi.SetTextMatrix(iRow, iCol, dlg.GetstrNum());
	}
}

void CResinRoiDlg::displayData_ResinRoi()
{
	CString tmpStr;

	tmpStr.Format("%.03f", model.m_ResinDrawCenter[0].x);
	m_gridArcRoi.SetTextMatrix(1, 1, tmpStr);
	tmpStr.Format("%.03f", model.m_ResinDrawCenter[0].y);
	m_gridArcRoi.SetTextMatrix(1, 2, tmpStr);

	tmpStr.Format("%.03f", model.m_ResinDrawCenter[1].x);
	m_gridArcRoi.SetTextMatrix(2, 1, tmpStr);
	tmpStr.Format("%.03f", model.m_ResinDrawCenter[1].y);
	m_gridArcRoi.SetTextMatrix(2, 2, tmpStr);

	tmpStr.Format("%.03f", model.m_ResinDrawCenter[2].x);
	m_gridArcRoi.SetTextMatrix(3, 1, tmpStr);
	tmpStr.Format("%.03f", model.m_ResinDrawCenter[2].y);
	m_gridArcRoi.SetTextMatrix(3, 2, tmpStr);

	tmpStr.Format("%.03f", model.m_ResinDrawCenter[3].x);
	m_gridArcRoi.SetTextMatrix(4, 1, tmpStr);
	tmpStr.Format("%.03f", model.m_ResinDrawCenter[3].y);
	m_gridArcRoi.SetTextMatrix(4, 2, tmpStr);





	tmpStr.Format("%.03f", model.m_ResingRectStart[0].x);
	m_gridLineRoi.SetTextMatrix(1, 1, tmpStr);
	tmpStr.Format("%.03f", model.m_ResingRectStart[0].y);
	m_gridLineRoi.SetTextMatrix(1, 2, tmpStr);

	tmpStr.Format("%.03f", model.m_ResingRectStart[1].x);
	m_gridLineRoi.SetTextMatrix(2, 1, tmpStr);
	tmpStr.Format("%.03f", model.m_ResingRectStart[1].y);
	m_gridLineRoi.SetTextMatrix(2, 2, tmpStr);

	tmpStr.Format("%.03f", model.m_ResingRectStart[2].x);
	m_gridLineRoi.SetTextMatrix(3, 1, tmpStr);
	tmpStr.Format("%.03f", model.m_ResingRectStart[2].y);
	m_gridLineRoi.SetTextMatrix(3, 2, tmpStr);

	tmpStr.Format("%.03f", model.m_ResingRectStart[3].x);
	m_gridLineRoi.SetTextMatrix(4, 1, tmpStr);
	tmpStr.Format("%.03f", model.m_ResingRectStart[3].y);
	m_gridLineRoi.SetTextMatrix(4, 2, tmpStr);

	tmpStr.Format("%.03f", model.m_ResingRectSize[0].x);
	m_gridLineRoi.SetTextMatrix(5, 1, tmpStr);
	tmpStr.Format("%.03f", model.m_ResingRectSize[0].y);
	m_gridLineRoi.SetTextMatrix(5, 2, tmpStr);

	tmpStr.Format("%.03f", model.m_ResingRectSize[1].x);
	m_gridLineRoi.SetTextMatrix(6, 1, tmpStr);
	tmpStr.Format("%.03f", model.m_ResingRectSize[1].y);
	m_gridLineRoi.SetTextMatrix(6, 2, tmpStr);

	tmpStr.Format("%.03f", model.m_ResingRectSize[2].x);
	m_gridLineRoi.SetTextMatrix(7, 1, tmpStr);
	tmpStr.Format("%.03f", model.m_ResingRectSize[2].y);
	m_gridLineRoi.SetTextMatrix(7, 2, tmpStr);

	tmpStr.Format("%.03f", model.m_ResingRectSize[3].x);
	m_gridLineRoi.SetTextMatrix(8, 1, tmpStr);
	tmpStr.Format("%.03f", model.m_ResingRectSize[3].y);
	m_gridLineRoi.SetTextMatrix(8, 2, tmpStr);

	UpdateData(false);
}


void CResinRoiDlg::getData_ResinRoi()
{
	UpdateData(true);
	CString tmpStr;

	tmpStr = m_gridArcRoi.GetTextMatrix(1, 1);
	model.m_ResinDrawCenter[0].x = (float)atof(tmpStr);
	tmpStr = m_gridArcRoi.GetTextMatrix(1, 2);
	model.m_ResinDrawCenter[0].y = (float)atof(tmpStr);

	tmpStr = m_gridArcRoi.GetTextMatrix(2, 1);
	model.m_ResinDrawCenter[1].x = (float)atof(tmpStr);
	tmpStr = m_gridArcRoi.GetTextMatrix(2, 2);
	model.m_ResinDrawCenter[1].y = (float)atof(tmpStr);

	tmpStr = m_gridArcRoi.GetTextMatrix(3, 1);
	model.m_ResinDrawCenter[2].x = (float)atof(tmpStr);
	tmpStr = m_gridArcRoi.GetTextMatrix(3, 2);
	model.m_ResinDrawCenter[2].y = (float)atof(tmpStr);

	tmpStr = m_gridArcRoi.GetTextMatrix(4, 1);
	model.m_ResinDrawCenter[3].x = (float)atof(tmpStr);

	tmpStr = m_gridArcRoi.GetTextMatrix(4, 2);
	model.m_ResinDrawCenter[3].y = (float)atof(tmpStr);



	tmpStr = m_gridLineRoi.GetTextMatrix(1, 1);
	model.m_ResingRectStart[0].x = (float)atof(tmpStr);
	tmpStr = m_gridLineRoi.GetTextMatrix(1, 2);
	model.m_ResingRectStart[0].y = (float)atof(tmpStr);

	tmpStr = m_gridLineRoi.GetTextMatrix(2, 1);
	model.m_ResingRectStart[1].x = (float)atof(tmpStr);
	tmpStr = m_gridLineRoi.GetTextMatrix(2, 2);
	model.m_ResingRectStart[1].y = (float)atof(tmpStr);

	tmpStr = m_gridLineRoi.GetTextMatrix(3, 1);
	model.m_ResingRectStart[2].x = (float)atof(tmpStr);
	tmpStr = m_gridLineRoi.GetTextMatrix(3, 2);
	model.m_ResingRectStart[2].y = (float)atof(tmpStr);

	tmpStr = m_gridLineRoi.GetTextMatrix(4, 1);
	model.m_ResingRectStart[3].x = (float)atof(tmpStr);
	tmpStr = m_gridLineRoi.GetTextMatrix(4, 2);
	model.m_ResingRectStart[3].y = (float)atof(tmpStr);

	tmpStr = m_gridLineRoi.GetTextMatrix(5, 1);
	model.m_ResingRectSize[0].x = (float)atof(tmpStr);
	tmpStr = m_gridLineRoi.GetTextMatrix(5, 2);
	model.m_ResingRectSize[0].y = (float)atof(tmpStr);

	tmpStr = m_gridLineRoi.GetTextMatrix(6, 1);
	model.m_ResingRectSize[1].x = (float)atof(tmpStr);
	tmpStr = m_gridLineRoi.GetTextMatrix(6, 2);
	model.m_ResingRectSize[1].y = (float)atof(tmpStr);

	tmpStr = m_gridLineRoi.GetTextMatrix(7, 1);
	model.m_ResingRectSize[2].x = (float)atof(tmpStr);
	tmpStr = m_gridLineRoi.GetTextMatrix(7, 2);
	model.m_ResingRectSize[2].y = (float)atof(tmpStr);

	tmpStr = m_gridLineRoi.GetTextMatrix(8, 1);
	model.m_ResingRectSize[3].x = (float)atof(tmpStr);
	tmpStr = m_gridLineRoi.GetTextMatrix(8, 2);
	model.m_ResingRectSize[3].y = (float)atof(tmpStr);
	
}