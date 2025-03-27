// EpoxyDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "EpoxyDlg.h"
// CEpoxyDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CEpoxyDlg, CDialogEx)

CEpoxyDlg::CEpoxyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEpoxyDlg::IDD, pParent)
{

}

CEpoxyDlg::~CEpoxyDlg()
{
}

void CEpoxyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEpoxyDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_POS_SAVE, &CEpoxyDlg::OnBnClickedButtonMotorPosSave)
	ON_BN_CLICKED(IDOK, &CEpoxyDlg::OnBnClickedOk)

	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_EPOXY_BASIC, &CEpoxyDlg::OnDBClickedGridEpoxySet)
	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_EPOXY_LENGTH_GRID, &CEpoxyDlg::OnDBClickedGridEpoxyLength)
	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_EPOXY_CIRCLESET_GRID, &CEpoxyDlg::OnDBClickedGridEpoxyCircleSet)
	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_EPOXY_CIRCLE_INSP_GRID, &CEpoxyDlg::OnDBClickedGridEpoxyCircleInsp)
	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_EPOXY_RECT_INSP_GRID, &CEpoxyDlg::OnDBClickedGridEpoxyRectInsp)
	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_EPOXY_OFFSET_GRID, &CEpoxyDlg::OnDBClickedGridEpoxyOffset)
	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_RADIUS_OFFSET_GRID, &CEpoxyDlg::OnDBClickedGridCircleRadiusOffset)
	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_RADIUS_CIRCLE_INSP_GRID, &CEpoxyDlg::OnDBClickedGridCircleInspSet)

	
END_MESSAGE_MAP()

BOOL CEpoxyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	sysData.Load();

	InitGridCtrl_EpoxyCircleSet();
	InitGridCtrl_EpoxyLength();
	InitGridCtrl_EpoxyCircleInsp();
	InitGridCtrl_EpoxyRectInsp();
	InitGridCtrl_EpoxyOffset();
	InitGridCtrl_EpoxyBasicSet();
	InitGridCtrl_EpoxyCircleInspArea();
	//
	InitGridCtrl_CircleRadiusOffset();
	//GetDlgItem(IDC_STATIC_RADIUS_OFFSET_GRID)->ShowWindow(SW_HIDE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CEpoxyDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}
void CEpoxyDlg::InitGridCtrl_EpoxyBasicSet()
{
	int DLG = IDC_STATIC_EPOXY_BASIC;
	CRect rect;
	CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
	EpoxySetRow = 7;//2;//아래
	EpoxySetCol = 2;//5;//옆
	int margin = 4;
	int gridHeight = 32;
	int gridWidth1 = 125;
	int gridWidth2 = 70;
	int totalWidth = gridWidth1 + (gridWidth2*(EpoxySetCol - 1));
	//
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = totalWidth + margin;
	rect.bottom = (gridHeight*EpoxySetRow) + margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.

	GetDlgItem(DLG)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGridEpoxyBasic.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

	m_clGridEpoxyBasic.SetTextBkColor(GRID_COLOR_WHITE);
	m_clGridEpoxyBasic.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridEpoxyBasic.SetFixedTextColor(GRID_COLOR_WHITE);
	m_clGridEpoxyBasic.SetReference_Setting();
	m_clGridEpoxyBasic.EnableSelection(FALSE);
	m_clGridEpoxyBasic.SetRowCount(EpoxySetRow);
	m_clGridEpoxyBasic.SetColumnCount(EpoxySetCol);
	m_clGridEpoxyBasic.SetFixedRowCount(1);
	m_clGridEpoxyBasic.SetFixedColumnCount(1);

	CString tmpStr = "";
	m_clGridEpoxyBasic.SetItemText(0, 0, "직선도포설정");
	m_clGridEpoxyBasic.SetItemText(0, 1, "value");
	m_clGridEpoxyBasic.SetItemText(1, 0, "Speed(mm/s)");
	m_clGridEpoxyBasic.SetItemText(2, 0, "가감속(mm/s)");
	m_clGridEpoxyBasic.SetItemText(3, 0, "ON Delay Time");
	m_clGridEpoxyBasic.SetItemText(4, 0, "OFF Time(s)");
	m_clGridEpoxyBasic.SetItemText(5, 0, "S_Speed(s)");
	m_clGridEpoxyBasic.SetItemText(6, 0, "Point_OFF Time(s)");
	//
	int i = 0, j = 0;
	for (i = 0; i < EpoxySetRow; i++)
	{
		m_clGridEpoxyBasic.SetRowHeight(i, gridHeight);

		for (j = 0; j < EpoxySetCol; j++)
		{
			m_clGridEpoxyBasic.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridEpoxyBasic.SetColumnWidth(j, gridWidth1);
				}
				else {
					m_clGridEpoxyBasic.SetColumnWidth(j, gridWidth2);
				}
			}
		}
	}
	m_clGridEpoxyBasic.Invalidate();
}
// CEpoxyDlg 메시지 처리기입니다.
void CEpoxyDlg::InitGridCtrl_EpoxyOffset()
{
	//CGridCtrl m_clGridEpoxySet;
	//EpoxySetRow
	//EpoxySetCol
	CRect rect;
	CWnd *pWnd= (CWnd*)GetDlgItem(IDC_STATIC_EPOXY_OFFSET_GRID); 
	EpoxyOffsetRow = 3;//2;//아래
	EpoxyOffsetCol = 2;//5;//옆
	int margin = 4;
	int gridHeight = 32;
	int gridWidth1 = 100;
	int gridWidth2 = 70;
	int totalWidth = gridWidth1+(gridWidth2*(EpoxyOffsetCol-1));
	//
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = totalWidth +margin;
	rect.bottom = (gridHeight*EpoxyOffsetRow) +margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.

	GetDlgItem(IDC_STATIC_EPOXY_OFFSET_GRID)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGridEpoxyOffset.Create(rect, this, IDC_STATIC_EPOXY_OFFSET_GRID, WS_TABSTOP | WS_VISIBLE);

	m_clGridEpoxyOffset.SetTextBkColor(GRID_COLOR_WHITE);
	m_clGridEpoxyOffset.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridEpoxyOffset.SetFixedTextColor(GRID_COLOR_WHITE);
	m_clGridEpoxyOffset.SetReference_Setting();
	m_clGridEpoxyOffset.EnableSelection(FALSE);
	m_clGridEpoxyOffset.SetRowCount(EpoxyOffsetRow);
	m_clGridEpoxyOffset.SetColumnCount(EpoxyOffsetCol);
	m_clGridEpoxyOffset.SetFixedRowCount(1);
	m_clGridEpoxyOffset.SetFixedColumnCount(1);

	CString tmpStr="";
	m_clGridEpoxyOffset.SetItemText(0, 0, "도포영역 Offset");
	m_clGridEpoxyOffset.SetItemText(0, 1, "수치");
	m_clGridEpoxyOffset.SetItemText(1, 0,  "Offset_X");
	m_clGridEpoxyOffset.SetItemText(2, 0,  "Offset_Y");

	//
	int i=0, j=0;
	for (i = 0; i < EpoxyOffsetRow; i++)
	{
		m_clGridEpoxyOffset.SetRowHeight(i, gridHeight);
		
		for (j = 0; j < EpoxyOffsetCol; j++)
		{
			m_clGridEpoxyOffset.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridEpoxyOffset.SetColumnWidth(j, gridWidth1);
				}else{
					m_clGridEpoxyOffset.SetColumnWidth(j, gridWidth2);
				}
			}			
		}
	}
	m_clGridEpoxyOffset.Invalidate();
}
void CEpoxyDlg::InitGridCtrl_EpoxyCircleSet()
{
	int DLG = IDC_STATIC_EPOXY_CIRCLESET_GRID;
	CRect rect;
	CWnd *pWnd= (CWnd*)GetDlgItem(DLG);
	EpoxySetCircleRow = 8;//2;//아래
	EpoxySetCircleCol = 2;//5;//옆
	int margin = 4;
	int gridHeight = 32;
	int gridWidth1 = 140;
	int gridWidth2 = 80;
	int totalWidth = gridWidth1+(gridWidth2*(EpoxySetCircleCol-1));
	//
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = totalWidth +margin;
	rect.bottom = (gridHeight*EpoxySetCircleRow) +margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.

	GetDlgItem(DLG)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGridEpoxyCircleSet.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

	m_clGridEpoxyCircleSet.SetTextBkColor(GRID_COLOR_WHITE);
	m_clGridEpoxyCircleSet.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridEpoxyCircleSet.SetFixedTextColor(GRID_COLOR_WHITE);
	m_clGridEpoxyCircleSet.SetReference_Setting();
	m_clGridEpoxyCircleSet.EnableSelection(FALSE);
	m_clGridEpoxyCircleSet.SetRowCount(EpoxySetCircleRow);
	m_clGridEpoxyCircleSet.SetColumnCount(EpoxySetCircleCol);
	m_clGridEpoxyCircleSet.SetFixedRowCount(1);
	m_clGridEpoxyCircleSet.SetFixedColumnCount(1);

	CString tmpStr="";
	m_clGridEpoxyCircleSet.SetItemText(0, 0, "원형도포");
	m_clGridEpoxyCircleSet.SetItemText(0,1, "도포길이");
	m_clGridEpoxyCircleSet.SetItemText(1, 0, "Radius(mm/s)");
	m_clGridEpoxyCircleSet.SetItemText(2, 0, "Angle(mm/s)");
	m_clGridEpoxyCircleSet.SetItemText(3, 0, "Speed(mm/s)");
	m_clGridEpoxyCircleSet.SetItemText(4, 0, "S_Radius(mm/s)");
	m_clGridEpoxyCircleSet.SetItemText(5, 0, "S_Angle(mm/s)");
	m_clGridEpoxyCircleSet.SetItemText(6, 0, "S_Speed(mm/s)");
	m_clGridEpoxyCircleSet.SetItemText(7, 0, "T_Speed(mm/s)");


	//EPOXY_DATA		23.300000   400.000000   12.000000   0.100000   0.000000   0.100000
	int i=0, j=0;
	for (i = 0; i < EpoxySetCircleRow; i++)
	{
		m_clGridEpoxyCircleSet.SetRowHeight(i, gridHeight);
		
		for (j = 0; j < EpoxySetCircleCol; j++)
		{
			m_clGridEpoxyCircleSet.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridEpoxyCircleSet.SetColumnWidth(j, gridWidth1);
				}else{
					m_clGridEpoxyCircleSet.SetColumnWidth(j, gridWidth2);
				}
			}			
		}
	}
	m_clGridEpoxyCircleSet.Invalidate();
}
void CEpoxyDlg::InitGridCtrl_CircleRadiusOffset()
{
	CRect rect;
	CWnd *pWnd = (CWnd*)GetDlgItem(IDC_STATIC_RADIUS_OFFSET_GRID);
	EpoxyLengthRow = 5;//2;//아래
	EpoxyLengthCol = 5;// 3;//5;//옆
	int margin = 4;
	int gridHeight = 32;
	int gridWidth1 = 90;
	int gridWidth2 = 60;
	int totalWidth = gridWidth1 + (gridWidth2*(EpoxyLengthCol - 1));
	//
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = totalWidth + margin;
	rect.bottom = (gridHeight*EpoxyLengthRow) + margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.

	GetDlgItem(IDC_STATIC_RADIUS_OFFSET_GRID)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGridCircleRadiusOffset.Create(rect, this, IDC_STATIC_RADIUS_OFFSET_GRID, WS_TABSTOP | WS_VISIBLE);

	m_clGridCircleRadiusOffset.SetTextBkColor(GRID_COLOR_WHITE);
	m_clGridCircleRadiusOffset.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridCircleRadiusOffset.SetFixedTextColor(GRID_COLOR_WHITE);
	m_clGridCircleRadiusOffset.SetReference_Setting();
	m_clGridCircleRadiusOffset.EnableSelection(FALSE);
	m_clGridCircleRadiusOffset.SetRowCount(EpoxyLengthRow);
	m_clGridCircleRadiusOffset.SetColumnCount(EpoxyLengthCol);
	m_clGridCircleRadiusOffset.SetFixedRowCount(1);
	m_clGridCircleRadiusOffset.SetFixedColumnCount(1);

	CString tmpStr = "";
	m_clGridCircleRadiusOffset.SetItemText(0, 0, "Radius Offset");
	m_clGridCircleRadiusOffset.SetItemText(0, 1, "CenterX");
	m_clGridCircleRadiusOffset.SetItemText(0, 2, "CenterY");
	m_clGridCircleRadiusOffset.SetItemText(0, 3, "EndX");
	m_clGridCircleRadiusOffset.SetItemText(0, 4, "EndY");
	m_clGridCircleRadiusOffset.SetItemText(1, 0, "Point1");
	m_clGridCircleRadiusOffset.SetItemText(2, 0, "Point2");
	m_clGridCircleRadiusOffset.SetItemText(3, 0, "Point3");
	m_clGridCircleRadiusOffset.SetItemText(4, 0, "Point4");

	//
	int i = 0, j = 0;
	for (i = 0; i < EpoxyLengthRow; i++)
	{
		m_clGridCircleRadiusOffset.SetRowHeight(i, gridHeight);

		for (j = 0; j < EpoxyLengthCol; j++)
		{
			m_clGridCircleRadiusOffset.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridCircleRadiusOffset.SetColumnWidth(j, gridWidth1);
				}
				else {
					m_clGridCircleRadiusOffset.SetColumnWidth(j, gridWidth2);
				}
			}
		}
	}
	m_clGridCircleRadiusOffset.Invalidate();
}
void CEpoxyDlg::InitGridCtrl_EpoxyLength()
{
	//CGridCtrl m_clGridEpoxyLength;
	//EpoxyLengthRow
	//EpoxyLengthCol

	CRect rect;
	CWnd *pWnd= (CWnd*)GetDlgItem(IDC_STATIC_EPOXY_LENGTH_GRID); 
	EpoxyLengthRow = 5 + 4;//2;//아래
	EpoxyLengthCol = 2;//5;//옆
	int margin = 4;
	int gridHeight = 30;
	int gridWidth1 = 70;
	int gridWidth2 = 80;
	int totalWidth = gridWidth1+(gridWidth2*(EpoxyLengthCol-1));
	//
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = totalWidth +margin;
	rect.bottom = (gridHeight*EpoxyLengthRow) +margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.

	GetDlgItem(IDC_STATIC_EPOXY_LENGTH_GRID)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGridEpoxyLength.Create(rect, this, IDC_STATIC_EPOXY_LENGTH_GRID, WS_TABSTOP | WS_VISIBLE);

	m_clGridEpoxyLength.SetTextBkColor(GRID_COLOR_WHITE);
	m_clGridEpoxyLength.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridEpoxyLength.SetFixedTextColor(GRID_COLOR_WHITE);
	m_clGridEpoxyLength.SetReference_Setting();
	m_clGridEpoxyLength.EnableSelection(FALSE);
	m_clGridEpoxyLength.SetRowCount(EpoxyLengthRow);
	m_clGridEpoxyLength.SetColumnCount(EpoxyLengthCol);
	m_clGridEpoxyLength.SetFixedRowCount(1);
	m_clGridEpoxyLength.SetFixedColumnCount(1);

	CString tmpStr="";
	m_clGridEpoxyLength.SetItemText(0, 0, "사각도포");
	m_clGridEpoxyLength.SetItemText(0, 1, "도포길이");
	m_clGridEpoxyLength.SetItemText(1, 0,  "Length1");
	m_clGridEpoxyLength.SetItemText(2, 0,  "Length2");
	m_clGridEpoxyLength.SetItemText(3, 0,  "Length3");
	m_clGridEpoxyLength.SetItemText(4, 0, "Length4");
	m_clGridEpoxyLength.SetItemText(5, 0, "Length5");
	m_clGridEpoxyLength.SetItemText(6, 0, "Length6");
	m_clGridEpoxyLength.SetItemText(7, 0, "Length7");
	m_clGridEpoxyLength.SetItemText(8, 0, "Length8");

	//
	int i=0, j=0;
	for (i = 0; i < EpoxyLengthRow; i++)
	{
		m_clGridEpoxyLength.SetRowHeight(i, gridHeight);
		
		for (j = 0; j < EpoxyLengthCol; j++)
		{
			m_clGridEpoxyLength.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridEpoxyLength.SetColumnWidth(j, gridWidth1);
				}else{
					m_clGridEpoxyLength.SetColumnWidth(j, gridWidth2);
				}
			}			
		}
	}
	m_clGridEpoxyLength.Invalidate();
}
void CEpoxyDlg::InitGridCtrl_EpoxyCircleInsp()
{
	//CGridCtrl m_clGridEpoxyCircleInsp;
	//EpoxyInspRow
	//EpoxyInspCol
	CRect rect;
	CWnd *pWnd= (CWnd*)GetDlgItem(IDC_STATIC_EPOXY_CIRCLE_INSP_GRID); 
	EpoxyCircleInspRow = 7;//아래
	EpoxyCircleInspCol = 3;//옆
	int margin = 4;
	int gridHeight = 32;
	int gridWidth1 = 180;
	int gridWidth2 = 80;
	int totalWidth = gridWidth1+(gridWidth2*(EpoxyCircleInspCol-1));
	//
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = totalWidth +margin;
	rect.bottom = (gridHeight*EpoxyCircleInspRow) +margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.

	GetDlgItem(IDC_STATIC_EPOXY_CIRCLE_INSP_GRID)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGridEpoxyCircleInsp.Create(rect, this, IDC_STATIC_EPOXY_CIRCLE_INSP_GRID, WS_TABSTOP | WS_VISIBLE);

	m_clGridEpoxyCircleInsp.SetTextBkColor(GRID_COLOR_WHITE);
	m_clGridEpoxyCircleInsp.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridEpoxyCircleInsp.SetFixedTextColor(GRID_COLOR_WHITE);
	m_clGridEpoxyCircleInsp.SetReference_Setting();
	m_clGridEpoxyCircleInsp.EnableSelection(FALSE);
	m_clGridEpoxyCircleInsp.SetRowCount(EpoxyCircleInspRow);
	m_clGridEpoxyCircleInsp.SetColumnCount(EpoxyCircleInspCol);
	m_clGridEpoxyCircleInsp.SetFixedRowCount(1);
	m_clGridEpoxyCircleInsp.SetFixedColumnCount(1);

	CString tmpStr="";

	m_clGridEpoxyCircleInsp.SetItemText(1, 0, "Epoxy 도포 크기 (mm)");					
	m_clGridEpoxyCircleInsp.SetItemText(2, 0, "검사 영역 안쪽 Offset(mm)");				
	m_clGridEpoxyCircleInsp.SetItemText(3, 0, "검사 영역 바깥 Offset (mm)");				
	m_clGridEpoxyCircleInsp.SetItemText(4, 0, "도포 검사 OK Limit (%)");					
	m_clGridEpoxyCircleInsp.SetItemText(5, 0, "Square 검사 Spec (%)");			
	m_clGridEpoxyCircleInsp.SetItemText(6, 0, "Square 연속 끊어진 구간 (mm)");
	m_clGridEpoxyCircleInsp.SetItemText(0, 0, "원형도포 검사설정");
	m_clGridEpoxyCircleInsp.SetItemText(0, 1, "X");									
	m_clGridEpoxyCircleInsp.SetItemText(0, 2, "Y");				

	//
	int i=0, j=0;
	for (i = 0; i < EpoxyCircleInspRow; i++)
	{
		m_clGridEpoxyCircleInsp.SetRowHeight(i, gridHeight);
		
		for (j = 0; j < EpoxyCircleInspCol; j++)
		{
			m_clGridEpoxyCircleInsp.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridEpoxyCircleInsp.SetColumnWidth(j, gridWidth1);
				}else{
					m_clGridEpoxyCircleInsp.SetColumnWidth(j, gridWidth2);
				}
			}			
		}
	}
	m_clGridEpoxyCircleInsp.Invalidate();
}
void CEpoxyDlg::InitGridCtrl_EpoxyCircleInspArea()
{
	CRect rect;
	int DLG = IDC_STATIC_RADIUS_CIRCLE_INSP_GRID;
	CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
	//;//
	EpoxyCircleAreaRow = 5;//아래
	EpoxyCircleAreaCol = 5;//옆
	int margin = 4;
	int gridHeight = 32;
	int gridWidth1 = 100;
	int gridWidth2 = 55;
	int totalWidth = gridWidth1 + (gridWidth2*(EpoxyCircleAreaCol - 1));
	//
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = totalWidth + margin;
	rect.bottom = (gridHeight*EpoxyCircleAreaRow) + margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.

	GetDlgItem(DLG)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGridEpoxyCircleInspArea.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

	m_clGridEpoxyCircleInspArea.SetTextBkColor(GRID_COLOR_WHITE);
	m_clGridEpoxyCircleInspArea.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridEpoxyCircleInspArea.SetFixedTextColor(GRID_COLOR_WHITE);
	m_clGridEpoxyCircleInspArea.SetReference_Setting();
	m_clGridEpoxyCircleInspArea.EnableSelection(FALSE);
	m_clGridEpoxyCircleInspArea.SetRowCount(EpoxyCircleAreaRow);
	m_clGridEpoxyCircleInspArea.SetColumnCount(EpoxyCircleAreaCol);
	m_clGridEpoxyCircleInspArea.SetFixedRowCount(1);
	m_clGridEpoxyCircleInspArea.SetFixedColumnCount(1);

	CString tmpStr = "";
	m_clGridEpoxyCircleInspArea.SetItemText(0, 0, "원형 검사 영역");
	m_clGridEpoxyCircleInspArea.SetItemText(1, 0, " LT");
	m_clGridEpoxyCircleInspArea.SetItemText(2, 0, " RT");
	m_clGridEpoxyCircleInspArea.SetItemText(4, 0, " RB");
	m_clGridEpoxyCircleInspArea.SetItemText(3, 0, " LB");
	//
	m_clGridEpoxyCircleInspArea.SetItemText(0, 1, "X");
	m_clGridEpoxyCircleInspArea.SetItemText(0, 2, "Y");
	m_clGridEpoxyCircleInspArea.SetItemText(0, 3, "Width");
	m_clGridEpoxyCircleInspArea.SetItemText(0, 4, "height");

	//
	int i = 0, j = 0;
	for (i = 0; i < EpoxyCircleAreaRow; i++)
	{
		m_clGridEpoxyCircleInspArea.SetRowHeight(i, gridHeight);

		for (j = 0; j < EpoxyCircleAreaCol; j++)
		{
			m_clGridEpoxyCircleInspArea.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridEpoxyCircleInspArea.SetColumnWidth(j, gridWidth1);
				}
				else {
					m_clGridEpoxyCircleInspArea.SetColumnWidth(j, gridWidth2);
				}
			}
		}
	}
	m_clGridEpoxyCircleInspArea.Invalidate();
}
void CEpoxyDlg::InitGridCtrl_EpoxyRectInsp()
{
	CRect rect;
	CWnd *pWnd= (CWnd*)GetDlgItem(IDC_STATIC_EPOXY_RECT_INSP_GRID); 
	EpoxyRectInspRow = 5;//아래
	EpoxyRectInspCol = 5;//옆
	int margin = 4;
	int gridHeight = 32;
	int gridWidth1 = 130;
	int gridWidth2 = 55;
	int totalWidth = gridWidth1+(gridWidth2*(EpoxyRectInspCol-1));
	//
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = totalWidth +margin;
	rect.bottom = (gridHeight*EpoxyRectInspRow) +margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.

	GetDlgItem(IDC_STATIC_EPOXY_RECT_INSP_GRID)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGridEpoxyRectInsp.Create(rect, this, IDC_STATIC_EPOXY_RECT_INSP_GRID, WS_TABSTOP | WS_VISIBLE);

	m_clGridEpoxyRectInsp.SetTextBkColor(GRID_COLOR_WHITE);
	m_clGridEpoxyRectInsp.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridEpoxyRectInsp.SetFixedTextColor(GRID_COLOR_WHITE);
	m_clGridEpoxyRectInsp.SetReference_Setting();
	m_clGridEpoxyRectInsp.EnableSelection(FALSE);
	m_clGridEpoxyRectInsp.SetRowCount(EpoxyRectInspRow);
	m_clGridEpoxyRectInsp.SetColumnCount(EpoxyRectInspCol);
	m_clGridEpoxyRectInsp.SetFixedRowCount(1);
	m_clGridEpoxyRectInsp.SetFixedColumnCount(1);

	CString tmpStr="";
	m_clGridEpoxyRectInsp.SetItemText(0, 0, "사각도포 검사 영역");
	m_clGridEpoxyRectInsp.SetItemText(1, 0, " Left");					
	m_clGridEpoxyRectInsp.SetItemText(2, 0, " Right");				
	m_clGridEpoxyRectInsp.SetItemText(3, 0, " Top");				
	m_clGridEpoxyRectInsp.SetItemText(4, 0, " Bottom");					
																						//
	
	
	m_clGridEpoxyRectInsp.SetItemText(0, 1, "X");									
	m_clGridEpoxyRectInsp.SetItemText(0, 2, "Y");	
	m_clGridEpoxyRectInsp.SetItemText(0, 3, "Width");	
	m_clGridEpoxyRectInsp.SetItemText(0, 4, "Height");	

	//
	int i=0, j=0;
	for (i = 0; i < EpoxyRectInspRow; i++)
	{
		m_clGridEpoxyRectInsp.SetRowHeight(i, gridHeight);
		
		for (j = 0; j < EpoxyRectInspCol; j++)
		{
			m_clGridEpoxyRectInsp.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridEpoxyRectInsp.SetColumnWidth(j, gridWidth1);
				}else{
					m_clGridEpoxyRectInsp.SetColumnWidth(j, gridWidth2);
				}
			}			
		}
	}
	m_clGridEpoxyRectInsp.Invalidate();
}
void CEpoxyDlg::ShowGridCtrl_Epoxy()
{

	CString posStr="";

	//도포 속도 , on,off시간 설정
	posStr.Format("%.03lf", model.dEpoxySpeed);
	m_clGridEpoxyBasic.SetItemText(1, 1, posStr);
	posStr.Format("%.03lf", model.dAcc);
	m_clGridEpoxyBasic.SetItemText(2, 1, posStr);
	posStr.Format("%.02lf", model.dOnTime);
	m_clGridEpoxyBasic.SetItemText(3, 1, posStr);
	posStr.Format("%.02lf", model.dOffTime);
	m_clGridEpoxyBasic.SetItemText(4, 1, posStr);
	posStr.Format("%.02lf", model.dSmallSpeed);
	m_clGridEpoxyBasic.SetItemText(5, 1, posStr);
	posStr.Format("%.02lf", model.dSmallOffTime);
	m_clGridEpoxyBasic.SetItemText(6, 1, posStr);

	//
	m_clGridEpoxyBasic.Invalidate();
	//============================================================
	//사각 Epoxy Line
	for (int i = 0; i < 8; i++)
	{
		posStr.Format("%.01lf", model.dDisLength[i]);
		m_clGridEpoxyLength.SetItemText(i + 1, 1, posStr);
	}
	/*posStr.Format("%.01lf", model.dDisLength[0]);
	m_clGridEpoxyLength.SetItemText(1, 1, posStr);
	posStr.Format("%.01lf", model.dDisLength[1]);
	m_clGridEpoxyLength.SetItemText( 2, 1,posStr);
	posStr.Format("%.01lf", model.dDisLength[2]);
	m_clGridEpoxyLength.SetItemText( 3, 1,posStr);
	posStr.Format("%.01lf", model.dDisLength[3]);
	m_clGridEpoxyLength.SetItemText( 4, 1,posStr);*/
	//============================================================
	//Epoxy Insp 사각도포
	posStr.Format("%d", model.m_ResingRectStart[0].x);
	m_clGridEpoxyRectInsp.SetItemText(1, 1, posStr);
	posStr.Format("%d", model.m_ResingRectStart[1].x);
	m_clGridEpoxyRectInsp.SetItemText(2, 1, posStr);
	posStr.Format("%d", model.m_ResingRectStart[2].x);
	m_clGridEpoxyRectInsp.SetItemText(3, 1, posStr);
	posStr.Format("%d", model.m_ResingRectStart[3].x);
	m_clGridEpoxyRectInsp.SetItemText(4, 1, posStr);

	posStr.Format("%d", model.m_ResingRectStart[0].y);
	m_clGridEpoxyRectInsp.SetItemText(1, 2, posStr);
	posStr.Format("%d", model.m_ResingRectStart[1].y);
	m_clGridEpoxyRectInsp.SetItemText(2, 2, posStr);
	posStr.Format("%d", model.m_ResingRectStart[2].y);
	m_clGridEpoxyRectInsp.SetItemText(3, 2, posStr);
	posStr.Format("%d", model.m_ResingRectStart[3].y);
	m_clGridEpoxyRectInsp.SetItemText(4, 2, posStr);

	posStr.Format("%d", model.m_ResingRectSize[0].x);
	m_clGridEpoxyRectInsp.SetItemText(1, 3, posStr);
	posStr.Format("%d", model.m_ResingRectSize[1].x);
	m_clGridEpoxyRectInsp.SetItemText(2, 3, posStr);
	posStr.Format("%d", model.m_ResingRectSize[2].x);
	m_clGridEpoxyRectInsp.SetItemText(3, 3, posStr);
	posStr.Format("%d", model.m_ResingRectSize[3].x);
	m_clGridEpoxyRectInsp.SetItemText(4, 3, posStr);

	posStr.Format("%d", model.m_ResingRectSize[0].y);
	m_clGridEpoxyRectInsp.SetItemText(1, 4, posStr);
	posStr.Format("%d", model.m_ResingRectSize[1].y);
	m_clGridEpoxyRectInsp.SetItemText(2, 4, posStr);
	posStr.Format("%d", model.m_ResingRectSize[2].y);
	m_clGridEpoxyRectInsp.SetItemText(3, 4, posStr);
	posStr.Format("%d", model.m_ResingRectSize[3].y);
	m_clGridEpoxyRectInsp.SetItemText(4, 4, posStr);

	//============================================================
	//원형 Epoxy Speed
	posStr.Format("%.03lf", model.dRadiusLength);
	m_clGridEpoxyCircleSet.SetItemText(1, 1, posStr);
	posStr.Format("%.03lf", model.dAngle);
	m_clGridEpoxyCircleSet.SetItemText(2, 1, posStr);
	posStr.Format("%.03lf", model.dCircleSpeed);
	m_clGridEpoxyCircleSet.SetItemText(3, 1, posStr);

	posStr.Format("%.03lf", model.dConti_RadiusLength);
	m_clGridEpoxyCircleSet.SetItemText(4, 1, posStr);
	posStr.Format("%.03lf", model.dConti_Angle);
	m_clGridEpoxyCircleSet.SetItemText(5, 1, posStr);
	posStr.Format("%.03lf", model.dConti_Speed);
	m_clGridEpoxyCircleSet.SetItemText(6, 1, posStr);
	posStr.Format("%.03lf", model.dTwister_Speed);
	m_clGridEpoxyCircleSet.SetItemText(7, 1, posStr);

	
	//Epoxy Insp 원형도포
	posStr.Format("%.03f", model.m_ResinDrawSize.x);
	m_clGridEpoxyCircleInsp.SetItemText(1, 1, posStr);
	posStr.Format("%.03f", model.m_ResinDrawSize.y);
	m_clGridEpoxyCircleInsp.SetItemText(1, 2, posStr);

	posStr.Format("%.03f", model.m_dResinInspOffset[0].x);
	m_clGridEpoxyCircleInsp.SetItemText(2, 1, posStr);
	posStr.Format("%.03f", model.m_dResinInspOffset[0].y);
	m_clGridEpoxyCircleInsp.SetItemText(2, 2, posStr);

	posStr.Format("%.03f", model.m_dResinInspOffset[1].x);
	m_clGridEpoxyCircleInsp.SetItemText(3, 1, posStr);
	posStr.Format("%.03f", model.m_dResinInspOffset[1].y);
	m_clGridEpoxyCircleInsp.SetItemText(3, 2, posStr);

	posStr.Format("%d", model.m_iResinInspLimit);
	m_clGridEpoxyCircleInsp.SetItemText(4, 1, posStr);
	posStr.Format("--");
	m_clGridEpoxyCircleInsp.SetItemText(4, 2, posStr);

	posStr.Format("%.03f", model.m_iResinInspRectSpec);
	m_clGridEpoxyCircleInsp.SetItemText(5, 1, posStr);
	posStr.Format("--");
	m_clGridEpoxyCircleInsp.SetItemText(5, 2, posStr);

	posStr.Format("%.03f", model.m_dResinInspGapLength);
	m_clGridEpoxyCircleInsp.SetItemText(6, 1, posStr);
	posStr.Format("--");
	m_clGridEpoxyCircleInsp.SetItemText(6, 2, posStr);

	//============================================================
	//도포검사 영역 Offset
	posStr.Format("%.03lf", model.dEpoxyOffset_X);
	m_clGridEpoxyOffset.SetItemText(1, 1, posStr);
	posStr.Format("%.03lf", model.dEpoxyOffset_Y);
	m_clGridEpoxyOffset.SetItemText(2, 1,posStr);
	//============================================================
	
	//다각형 도포 반원의 반지름 길이 Offset
#if 1

	//center
	//x
	posStr.Format("%.02lf", model.dCircleRadiusCenterOffsetX[0]);
	m_clGridCircleRadiusOffset.SetItemText(1, 1, posStr);
	posStr.Format("%.02lf", model.dCircleRadiusCenterOffsetX[1]);
	m_clGridCircleRadiusOffset.SetItemText(2, 1, posStr);
	posStr.Format("%.02lf", model.dCircleRadiusCenterOffsetX[2]);
	m_clGridCircleRadiusOffset.SetItemText(3, 1, posStr);
	posStr.Format("%.02lf", model.dCircleRadiusCenterOffsetX[3]);
	m_clGridCircleRadiusOffset.SetItemText(4, 1, posStr);
	//y
	posStr.Format("%.02lf", model.dCircleRadiusCenterOffsetY[0]);
	m_clGridCircleRadiusOffset.SetItemText(1, 2, posStr);
	posStr.Format("%.02lf", model.dCircleRadiusCenterOffsetY[1]);
	m_clGridCircleRadiusOffset.SetItemText(2, 2, posStr);
	posStr.Format("%.02lf", model.dCircleRadiusCenterOffsetY[2]);
	m_clGridCircleRadiusOffset.SetItemText(3, 2, posStr);
	posStr.Format("%.02lf", model.dCircleRadiusCenterOffsetY[3]);
	m_clGridCircleRadiusOffset.SetItemText(4, 2, posStr);

	//End
	//x
	posStr.Format("%.02lf", model.dCircleRadiusEndOffsetX[0]);
	m_clGridCircleRadiusOffset.SetItemText(1, 3, posStr);
	posStr.Format("%.02lf", model.dCircleRadiusEndOffsetX[1]);
	m_clGridCircleRadiusOffset.SetItemText(2, 3, posStr);
	posStr.Format("%.02lf", model.dCircleRadiusEndOffsetX[2]);
	m_clGridCircleRadiusOffset.SetItemText(3, 3, posStr);
	posStr.Format("%.02lf", model.dCircleRadiusEndOffsetX[3]);
	m_clGridCircleRadiusOffset.SetItemText(4, 3, posStr);
	//y
	posStr.Format("%.02lf", model.dCircleRadiusEndOffsetY[0]);
	m_clGridCircleRadiusOffset.SetItemText(1, 4, posStr);
	posStr.Format("%.02lf", model.dCircleRadiusEndOffsetY[1]);
	m_clGridCircleRadiusOffset.SetItemText(2, 4, posStr);
	posStr.Format("%.02lf", model.dCircleRadiusEndOffsetY[2]);
	m_clGridCircleRadiusOffset.SetItemText(3, 4, posStr);
	posStr.Format("%.02lf", model.dCircleRadiusEndOffsetY[3]);
	m_clGridCircleRadiusOffset.SetItemText(4, 4, posStr);

	m_clGridCircleRadiusOffset.Invalidate();
#endif
	//============================================================

	//============================================================
	//다각형 원형 도포 영역
	//model.m_CircleDrawCenter[iCirCnt].x;
	posStr.Format("%.1lf", model.m_CircleDrawCenter[0].x);
	m_clGridEpoxyCircleInspArea.SetItemText(1, 1, posStr);
	posStr.Format("%.1lf", model.m_CircleDrawCenter[1].x);
	m_clGridEpoxyCircleInspArea.SetItemText(2, 1, posStr);
	posStr.Format("%.1lf", model.m_CircleDrawCenter[2].x);
	m_clGridEpoxyCircleInspArea.SetItemText(3, 1, posStr);
	posStr.Format("%.1lf", model.m_CircleDrawCenter[3].x);
	m_clGridEpoxyCircleInspArea.SetItemText(4, 1, posStr);

	posStr.Format("%.1lf", model.m_CircleDrawCenter[0].y);
	m_clGridEpoxyCircleInspArea.SetItemText(1, 2, posStr);
	posStr.Format("%.1lf", model.m_CircleDrawCenter[1].y);
	m_clGridEpoxyCircleInspArea.SetItemText(2, 2, posStr);
	posStr.Format("%.1lf", model.m_CircleDrawCenter[2].y);
	m_clGridEpoxyCircleInspArea.SetItemText(3, 2, posStr);
	posStr.Format("%.1lf", model.m_CircleDrawCenter[3].y);
	m_clGridEpoxyCircleInspArea.SetItemText(4, 2, posStr);

	posStr.Format("%.1lf", model.m_CircleDrawSize[0].x);
	m_clGridEpoxyCircleInspArea.SetItemText(1, 3, posStr);
	posStr.Format("%.1lf", model.m_CircleDrawSize[1].x);
	m_clGridEpoxyCircleInspArea.SetItemText(2, 3, posStr);
	posStr.Format("%.1lf", model.m_CircleDrawSize[2].x);
	m_clGridEpoxyCircleInspArea.SetItemText(3, 3, posStr);
	posStr.Format("%.1lf", model.m_CircleDrawSize[3].x);
	m_clGridEpoxyCircleInspArea.SetItemText(4, 3, posStr);

	posStr.Format("%.1lf", model.m_CircleDrawSize[0].y);
	m_clGridEpoxyCircleInspArea.SetItemText(1, 4, posStr);
	posStr.Format("%.1lf", model.m_CircleDrawSize[1].y);
	m_clGridEpoxyCircleInspArea.SetItemText(2, 4, posStr);
	posStr.Format("%.1lf", model.m_CircleDrawSize[2].y);
	m_clGridEpoxyCircleInspArea.SetItemText(3, 4, posStr);
	posStr.Format("%.1lf", model.m_CircleDrawSize[3].y);
	m_clGridEpoxyCircleInspArea.SetItemText(4, 4, posStr);

	//-----
	m_clGridEpoxyCircleInspArea.Invalidate();
	m_clGridEpoxyLength.Invalidate();
	m_clGridEpoxyRectInsp.Invalidate();
	m_clGridEpoxyCircleSet.Invalidate();
	m_clGridEpoxyCircleInsp.Invalidate();
	m_clGridEpoxyOffset.Invalidate();
	
}
void CEpoxyDlg::OnDBClickedGridEpoxySet(NMHDR* pNMHDR, LRESULT* pResult)
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;

	int row = pNMGridView->iRow;
	int col = pNMGridView->iColumn;


	if ( row <= 0 || col <= 0 )	return;

	CString sCellData = m_clGridEpoxyBasic.GetItemText(row, col);

	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)sCellData);

	if ( dlg.DoModal() == IDOK )
	{
		m_clGridEpoxyBasic.SetItemText(row, col, dlg.GetstrNum());
		m_clGridEpoxyBasic.Invalidate();
	}
}
void CEpoxyDlg::OnDBClickedGridEpoxyCircleSet(NMHDR* pNMHDR, LRESULT* pResult)
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;

	int row = pNMGridView->iRow;
	int col = pNMGridView->iColumn;


	if ( row <= 0 || col <= 0 )	return;

	CString sCellData = m_clGridEpoxyCircleSet.GetItemText(row, col);

	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)sCellData);

	if ( dlg.DoModal() == IDOK )
	{
		m_clGridEpoxyCircleSet.SetItemText(row, col, dlg.GetstrNum());
		m_clGridEpoxyCircleSet.Invalidate();
	}
}
void CEpoxyDlg::OnDBClickedGridCircleInspSet(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;

	int row = pNMGridView->iRow;
	int col = pNMGridView->iColumn;

	if (row <= 0 || col <= 0)	return;

	CString sCellData = m_clGridEpoxyCircleInspArea.GetItemText(row, col);

	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)sCellData);

	if (dlg.DoModal() == IDOK)
	{
		m_clGridEpoxyCircleInspArea.SetItemText(row, col, dlg.GetstrNum());
		m_clGridEpoxyCircleInspArea.Invalidate();
	}
}

void CEpoxyDlg::OnDBClickedGridCircleRadiusOffset(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;

	int row = pNMGridView->iRow;
	int col = pNMGridView->iColumn;

	if (row <= 0 || col <= 0)	return;

	CString sCellData = m_clGridCircleRadiusOffset.GetItemText(row, col);

	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)sCellData);

	if (dlg.DoModal() == IDOK)
	{
		m_clGridCircleRadiusOffset.SetItemText(row, col, dlg.GetstrNum());
		m_clGridCircleRadiusOffset.Invalidate();
	}
}
void CEpoxyDlg::OnDBClickedGridEpoxyLength(NMHDR* pNMHDR, LRESULT* pResult)
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;

	int row = pNMGridView->iRow;
	int col = pNMGridView->iColumn;

	if ( row <= 0 || col <= 0 )	return;

	CString sCellData = m_clGridEpoxyLength.GetItemText(row, col);

	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)sCellData);

	if ( dlg.DoModal() == IDOK )
	{
		m_clGridEpoxyLength.SetItemText(row, col, dlg.GetstrNum());
		m_clGridEpoxyLength.Invalidate();
	}
}
void CEpoxyDlg::OnDBClickedGridEpoxyCircleInsp(NMHDR* pNMHDR, LRESULT* pResult)
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;

	int row = pNMGridView->iRow;
	int col = pNMGridView->iColumn;

	if ( row <= 0 || col <= 0 )	return;

	CString sCellData = m_clGridEpoxyCircleInsp.GetItemText(row, col);

	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)sCellData);

	if ( dlg.DoModal() == IDOK )
	{
		m_clGridEpoxyCircleInsp.SetItemText(row, col, dlg.GetstrNum());
		m_clGridEpoxyCircleInsp.Invalidate();
	}
	
}
void CEpoxyDlg::OnDBClickedGridEpoxyOffset(NMHDR* pNMHDR, LRESULT* pResult)
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;

	int row = pNMGridView->iRow;
	int col = pNMGridView->iColumn;

	if ( row <= 0 || col <= 0 )	return;

	CString sCellData = m_clGridEpoxyOffset.GetItemText(row, col);

	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)sCellData);

	if ( dlg.DoModal() == IDOK )
	{
		m_clGridEpoxyOffset.SetItemText(row, col, dlg.GetstrNum());
		m_clGridEpoxyOffset.Invalidate();
	}

}
void CEpoxyDlg::OnDBClickedGridEpoxyRectInsp(NMHDR* pNMHDR, LRESULT* pResult)
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;

	int row = pNMGridView->iRow;
	int col = pNMGridView->iColumn;

	if ( row <= 0 || col <= 0 )	return;

	CString sCellData = m_clGridEpoxyRectInsp.GetItemText(row, col);

	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)sCellData);

	if ( dlg.DoModal() == IDOK )
	{
		m_clGridEpoxyRectInsp.SetItemText(row, col, dlg.GetstrNum());
		m_clGridEpoxyRectInsp.Invalidate();
	}

}


void CEpoxyDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if(bShow)
	{
		GetDlgItem(IDC_STATIC_EPOXY_CIRCLE_INSP_GRID)->ShowWindow(true);
		m_clGridEpoxyCircleInsp.ShowWindow(SW_SHOW);
		ShowGridCtrl_Epoxy();
		UpdateData(false);
	}
	else
	{
		CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
		KillTimer(MOTOR_TIMER);
	}
}

BEGIN_EVENTSINK_MAP(CEpoxyDlg, CDialogEx)

END_EVENTSINK_MAP()



void CEpoxyDlg::OnBnClickedButtonMotorPosSave()
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
	
	//====================================//도포 속도 , on,off시간 설정
	cellStr = m_clGridEpoxyBasic.GetItemText(1, 1);
	model.dEpoxySpeed = atof(cellStr);
	cellStr = m_clGridEpoxyBasic.GetItemText(2, 1);
	model.dAcc = atof(cellStr);
	cellStr = m_clGridEpoxyBasic.GetItemText(3, 1);
	model.dOnTime = atof(cellStr);
	cellStr = m_clGridEpoxyBasic.GetItemText(4, 1);
	model.dOffTime = atof(cellStr);
	cellStr = m_clGridEpoxyBasic.GetItemText(5, 1);
	model.dSmallSpeed = atof(cellStr);
	cellStr = m_clGridEpoxyBasic.GetItemText(6, 1);
	model.dSmallOffTime = atof(cellStr);


	//
	//====================================Epoxy Line
	for (int i = 0; i < 8; i++)
	{
		cellStr = m_clGridEpoxyLength.GetItemText(1 + i, 1);
		model.dDisLength[i] = atof(cellStr);
	}
	/*cellStr = m_clGridEpoxyLength.GetItemText(1, 1);
	model.dDisLength[0] = atof(cellStr);
	cellStr = m_clGridEpoxyLength.GetItemText(2, 1);
	model.dDisLength[1] = atof(cellStr);
	cellStr = m_clGridEpoxyLength.GetItemText(3, 1);
	model.dDisLength[2] = atof(cellStr);
	cellStr = m_clGridEpoxyLength.GetItemText(4, 1);
	model.dDisLength[3] = atof(cellStr);*/

	//----------------------------------------------------------------------------
	//====================================Epoxy Insp 사각도포 저장
	cellStr = m_clGridEpoxyRectInsp.GetItemText(1, 1);
	model.m_ResingRectStart[0].x = atoi(cellStr);
	cellStr = m_clGridEpoxyRectInsp.GetItemText(2, 1);
	model.m_ResingRectStart[1].x = atoi(cellStr);
	cellStr = m_clGridEpoxyRectInsp.GetItemText(3, 1);
	model.m_ResingRectStart[2].x = atoi(cellStr);
	cellStr = m_clGridEpoxyRectInsp.GetItemText(4, 1);
	model.m_ResingRectStart[3].x = atoi(cellStr);
	//
	cellStr = m_clGridEpoxyRectInsp.GetItemText(1, 2);
	model.m_ResingRectStart[0].y = atoi(cellStr);
	cellStr = m_clGridEpoxyRectInsp.GetItemText(2, 2);
	model.m_ResingRectStart[1].y = atoi(cellStr);
	cellStr = m_clGridEpoxyRectInsp.GetItemText(3, 2);
	model.m_ResingRectStart[2].y = atoi(cellStr);
	cellStr = m_clGridEpoxyRectInsp.GetItemText(4, 2);
	model.m_ResingRectStart[3].y = atoi(cellStr);
	//
	cellStr = m_clGridEpoxyRectInsp.GetItemText(1, 3);
	model.m_ResingRectSize[0].x = atoi(cellStr);
	cellStr = m_clGridEpoxyRectInsp.GetItemText(2, 3);
	model.m_ResingRectSize[1].x = atoi(cellStr);
	cellStr = m_clGridEpoxyRectInsp.GetItemText(3, 3);
	model.m_ResingRectSize[2].x = atoi(cellStr);
	cellStr = m_clGridEpoxyRectInsp.GetItemText(4, 3);
	model.m_ResingRectSize[3].x = atoi(cellStr);
	//
	cellStr = m_clGridEpoxyRectInsp.GetItemText(1, 4);
	model.m_ResingRectSize[0].y = atoi(cellStr);
	cellStr = m_clGridEpoxyRectInsp.GetItemText(2, 4);
	model.m_ResingRectSize[1].y = atoi(cellStr);
	cellStr = m_clGridEpoxyRectInsp.GetItemText(3, 4);
	model.m_ResingRectSize[2].y = atoi(cellStr);
	cellStr = m_clGridEpoxyRectInsp.GetItemText(4, 4);
	model.m_ResingRectSize[3].y = atoi(cellStr);
		
	//----------------------------------------------------------------------------

	//====================================원형 Epoxy
	cellStr = m_clGridEpoxyCircleSet.GetItemText(1, 1);
	model.dRadiusLength = atof(cellStr);
	cellStr = m_clGridEpoxyCircleSet.GetItemText(2, 1);
	model.dAngle = atof(cellStr);
	cellStr = m_clGridEpoxyCircleSet.GetItemText(3, 1);
	model.dCircleSpeed = atof(cellStr);

	cellStr = m_clGridEpoxyCircleSet.GetItemText(4, 1);
	model.dConti_RadiusLength = atof(cellStr);
	cellStr = m_clGridEpoxyCircleSet.GetItemText(5, 1);
	model.dConti_Angle = atof(cellStr);
	cellStr = m_clGridEpoxyCircleSet.GetItemText(6, 1);
	model.dConti_Speed = atof(cellStr);
	cellStr = m_clGridEpoxyCircleSet.GetItemText(7, 1);
	model.dTwister_Speed = atof(cellStr);
	
	

	//====================================Epoxy Insp 원형도포 저장
	cellStr = m_clGridEpoxyCircleInsp.GetItemText(1, 1);
	model.m_ResinDrawSize.x = (float)atof(cellStr);
	cellStr = m_clGridEpoxyCircleInsp.GetItemText(1, 2);
	model.m_ResinDrawSize.y = (float)atof(cellStr);
	cellStr = m_clGridEpoxyCircleInsp.GetItemText(2, 1);
	model.m_dResinInspOffset[0].x = (float)atof(cellStr);
	cellStr = m_clGridEpoxyCircleInsp.GetItemText(2, 2);
	model.m_dResinInspOffset[0].y = (float)atof(cellStr);
	cellStr = m_clGridEpoxyCircleInsp.GetItemText(3, 1);
	model.m_dResinInspOffset[1].x = (float)atof(cellStr);
	cellStr = m_clGridEpoxyCircleInsp.GetItemText(3, 2);
	model.m_dResinInspOffset[1].y = (float)atof(cellStr);

	cellStr = m_clGridEpoxyCircleInsp.GetItemText(4, 1);
	model.m_iResinInspLimit = atoi(cellStr);
	cellStr = m_clGridEpoxyCircleInsp.GetItemText(5, 1);
	model.m_iResinInspRectSpec = atoi(cellStr);
	cellStr = m_clGridEpoxyCircleInsp.GetItemText(6, 1);
	model.m_dResinInspGapLength = (float)atof(cellStr);
	//-------------------------------------------------------------

	//도포검사 영역 Offset
	cellStr = m_clGridEpoxyOffset.GetItemText(1, 1);
	model.dEpoxyOffset_X = (float)atof(cellStr);
	cellStr = m_clGridEpoxyOffset.GetItemText(2, 1);
	model.dEpoxyOffset_Y = (float)atof(cellStr);

	
	//============================================================
	//다각형 반원
#if  1
	//Center
	cellStr = m_clGridCircleRadiusOffset.GetItemText(1, 1);
	model.dCircleRadiusCenterOffsetX[0] = atof(cellStr);
	cellStr = m_clGridCircleRadiusOffset.GetItemText(2, 1);
	model.dCircleRadiusCenterOffsetX[1] = atof(cellStr);
	cellStr = m_clGridCircleRadiusOffset.GetItemText(3, 1);
	model.dCircleRadiusCenterOffsetX[2] = atof(cellStr);
	cellStr = m_clGridCircleRadiusOffset.GetItemText(4, 1);
	model.dCircleRadiusCenterOffsetX[3] = atof(cellStr);
	//y
	cellStr = m_clGridCircleRadiusOffset.GetItemText(1, 2);
	model.dCircleRadiusCenterOffsetY[0] = atof(cellStr);
	cellStr = m_clGridCircleRadiusOffset.GetItemText(2, 2);
	model.dCircleRadiusCenterOffsetY[1] = atof(cellStr);
	cellStr = m_clGridCircleRadiusOffset.GetItemText(3, 2);
	model.dCircleRadiusCenterOffsetY[2] = atof(cellStr);
	cellStr = m_clGridCircleRadiusOffset.GetItemText(4, 2);
	model.dCircleRadiusCenterOffsetY[3] = atof(cellStr);

	//End
	cellStr = m_clGridCircleRadiusOffset.GetItemText(1, 3);
	model.dCircleRadiusEndOffsetX[0] = atof(cellStr);
	cellStr = m_clGridCircleRadiusOffset.GetItemText(2, 3);
	model.dCircleRadiusEndOffsetX[1] = atof(cellStr);
	cellStr = m_clGridCircleRadiusOffset.GetItemText(3, 3);
	model.dCircleRadiusEndOffsetX[2] = atof(cellStr);
	cellStr = m_clGridCircleRadiusOffset.GetItemText(4, 3);
	model.dCircleRadiusEndOffsetX[3] = atof(cellStr);
	//y
	cellStr = m_clGridCircleRadiusOffset.GetItemText(1, 4);
	model.dCircleRadiusEndOffsetY[0] = atof(cellStr);
	cellStr = m_clGridCircleRadiusOffset.GetItemText(2, 4);
	model.dCircleRadiusEndOffsetY[1] = atof(cellStr);
	cellStr = m_clGridCircleRadiusOffset.GetItemText(3, 4);
	model.dCircleRadiusEndOffsetY[2] = atof(cellStr);
	cellStr = m_clGridCircleRadiusOffset.GetItemText(4, 4);
	model.dCircleRadiusEndOffsetY[3] = atof(cellStr);
#endif
	/*
	posStr.Format("%.01lf", model.dCircleRadiusLength[0]);
	m_clGridCircleRadiusOffset.SetItemText(1, 1, posStr);
	*/
	//====================================Epoxy Insp 사각도포 저장
	cellStr = m_clGridEpoxyCircleInspArea.GetItemText(1, 1);
	model.m_CircleDrawCenter[0].x = atof(cellStr);
	cellStr = m_clGridEpoxyCircleInspArea.GetItemText(2, 1);
	model.m_CircleDrawCenter[1].x = atof(cellStr);
	cellStr = m_clGridEpoxyCircleInspArea.GetItemText(3, 1);
	model.m_CircleDrawCenter[2].x = atof(cellStr);
	cellStr = m_clGridEpoxyCircleInspArea.GetItemText(4, 1);
	model.m_CircleDrawCenter[3].x = atof(cellStr);
	//
	cellStr = m_clGridEpoxyCircleInspArea.GetItemText(1, 2);
	model.m_CircleDrawCenter[0].y = atof(cellStr);
	cellStr = m_clGridEpoxyCircleInspArea.GetItemText(2, 2);
	model.m_CircleDrawCenter[1].y = atof(cellStr);
	cellStr = m_clGridEpoxyCircleInspArea.GetItemText(3, 2);
	model.m_CircleDrawCenter[2].y = atof(cellStr);
	cellStr = m_clGridEpoxyCircleInspArea.GetItemText(4, 2);
	model.m_CircleDrawCenter[3].y = atof(cellStr);
	//
	cellStr = m_clGridEpoxyCircleInspArea.GetItemText(1, 3);
	model.m_CircleDrawSize[0].x = atof(cellStr);
	cellStr = m_clGridEpoxyCircleInspArea.GetItemText(2, 3);
	model.m_CircleDrawSize[1].x = atof(cellStr);
	cellStr = m_clGridEpoxyCircleInspArea.GetItemText(3, 3);
	model.m_CircleDrawSize[2].x = atof(cellStr);
	cellStr = m_clGridEpoxyCircleInspArea.GetItemText(4, 3);
	model.m_CircleDrawSize[3].x = atof(cellStr);
	//
	cellStr = m_clGridEpoxyCircleInspArea.GetItemText(1, 4);
	model.m_CircleDrawSize[0].y = atof(cellStr);
	cellStr = m_clGridEpoxyCircleInspArea.GetItemText(2, 4);
	model.m_CircleDrawSize[1].y = atof(cellStr);
	cellStr = m_clGridEpoxyCircleInspArea.GetItemText(3, 4);
	model.m_CircleDrawSize[2].y = atof(cellStr);
	cellStr = m_clGridEpoxyCircleInspArea.GetItemText(4, 4);
	model.m_CircleDrawSize[3].y = atof(cellStr);

	//============================================================
	model.Save();
	sLangChange.LoadStringA(IDS_STRING1434);
	LogSave(sLangChange);
}

