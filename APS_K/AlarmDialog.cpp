// AlarmDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AlarmDialog.h"
#include "ModelDlg.h"

// CAlarmDialog 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAlarmDialog, CDialogEx)

	CAlarmDialog::CAlarmDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAlarmDialog::IDD, pParent)
{
	m_iAlarmKind = e_AlarmHistory;
}

CAlarmDialog::~CAlarmDialog()
{
}

void CAlarmDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_MSFLEXGRID_ALARM, m_gridAlarm[e_AlarmHistory]);
	//DDX_Control(pDX, IDC_MSFLEXGRID_ALARM_MONITER, m_gridAlarm[e_AlarmMoniter]);
	//DDX_Control(pDX, IDC_MSFLEXGRID_NG_LIST, m_gridAlarm[e_NgList]);

	DDX_Control(pDX, IDC_BUTTON_ALARM_HISTORY,	m_btnAlarmHistory);
	DDX_Control(pDX, IDC_BUTTON_ALARM_MONITOR,	m_btnAlarmMonitor);
	DDX_Control(pDX, IDC_BUTTON_NG_LIST,		m_btnNgList);
}


BEGIN_MESSAGE_MAP(CAlarmDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &CAlarmDialog::OnBnClickedButtonBack)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CAlarmDialog::OnBnClickedButtonNext)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CAlarmDialog::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_BUZZER_OFF, &CAlarmDialog::OnBnClickedButtonBuzzerOff)
	ON_BN_CLICKED(IDC_BUTTON_NG_LIST, &CAlarmDialog::OnBnClickedButtonNgList)
	ON_BN_CLICKED(IDC_BUTTON_ALARM_MONITOR, &CAlarmDialog::OnBnClickedButtonAlarmMonitor)
	ON_BN_CLICKED(IDC_BUTTON_ALARM_HISTORY, &CAlarmDialog::OnBnClickedButtonAlarmHistory)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CAlarmDialog::OnBnClickedButtonReset)
END_MESSAGE_MAP()
// CAlarmDialog 메시지 처리기입니다.


BOOL CAlarmDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	setinterface();

	for(int i = 0; i < 3; i++){
		m_iAlarmCnt[i]	= 0;
		m_iAlarmPage[i]	= 0;
		m_icurPage[i]	= 0;
		m_sAlarmList[i] = new CString[MAX_ALARM_LIST_IN_PAGE * MAX_ALARM_PAGE_CNT +1];
	}

	//initGrid();
	InitGridCtrl_Alarm();
	LoadAlarm();
	SelectAlarm();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CAlarmDialog::DestroyWindow()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	for(int i = 0; i < 3; i++)
		delete [] m_sAlarmList[i];

	return CDialogEx::DestroyWindow();
}

void CAlarmDialog::InitGridCtrl_Alarm()
{
	CRect rect;
	CWnd *pWnd= (CWnd*)GetDlgItem(IDC_STATIC_ALARM_GRID); 
	AlarmRow = MAX_ALARM_LIST_IN_PAGE+1;//아래
	AlarmCol = 2;//옆
	int margin = 4;
	int gridHeight = 30;
	int gridWidth1 = 130;
	int gridWidth2 = 395;
	int totalWidth = gridWidth1+(gridWidth2*(AlarmCol-1));
	//
	pWnd->GetWindowRect(rect);//pWnd->GetClientRect(rect);
	ScreenToClient(rect);//ClientToScreen(rect);

	rect.right = totalWidth +margin;
	rect.bottom = (gridHeight*AlarmRow) +margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.

	GetDlgItem(IDC_STATIC_ALARM_GRID)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGridAlarm.Create(rect, this, IDC_STATIC_ALARM_GRID, WS_TABSTOP | WS_VISIBLE);

	m_clGridAlarm.SetTextBkColor(GRID_COLOR_WHITE);
	m_clGridAlarm.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridAlarm.SetFixedTextColor(GRID_COLOR_WHITE);
	m_clGridAlarm.SetReference_Setting();
	m_clGridAlarm.EnableSelection(FALSE);
	m_clGridAlarm.SetRowCount(AlarmRow);
	m_clGridAlarm.SetColumnCount(AlarmCol);
	m_clGridAlarm.SetFixedRowCount(1);
	m_clGridAlarm.SetFixedColumnCount(1);

	CString tmpStr="";

	m_clGridAlarm.SetItemText(0, 0, "날짜/시간");
	m_clGridAlarm.SetItemText(0, 1, "알람 내역");
	////
	int i=0, j=0;
	for (i = 0; i < AlarmRow; i++)
	{
		m_clGridAlarm.SetRowHeight(i, gridHeight);
		
		for (j = 0; j < AlarmCol; j++)
		{
			m_clGridAlarm.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridAlarm.SetColumnWidth(j, gridWidth1);
				}else{
					m_clGridAlarm.SetColumnWidth(j, gridWidth2);
				}
			}			
		}
	}
	m_clGridAlarm.Invalidate();
}
void CAlarmDialog::ShowGridCtrl_Alarm()
{

}
void CAlarmDialog::setinterface()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	WINDOWPLACEMENT wndpl;
	this->GetWindowPlacement(&wndpl);

	//wndpl.rcNormalPosition.left = pFrame->m_rectCamDispPos2.left;//pFrame->m_rectCamDispPos1.left;
	//wndpl.rcNormalPosition.right = MAIN_DLG_SIZE_X;//pFrame->m_rectCamDispPos2.right;
	//wndpl.rcNormalPosition.top = pFrame->m_rectCamDispPos1.top - SUB_DLG_OFFSET_Y + 10;
	//wndpl.rcNormalPosition.bottom = MAIN_DLG_SIZE_Y - 85;
	//
	wndpl.rcNormalPosition.left = pFrame->m_rectCamDispPos2.left;//pFrame->m_rectCamDispPos1.left;
	wndpl.rcNormalPosition.right = MAIN_DLG_SIZE_X;//pFrame->m_rectCamDispPos2.right;
	wndpl.rcNormalPosition.top = pFrame->m_rectCamDispPos1.top - SUB_DLG_OFFSET_Y + 10;
	wndpl.rcNormalPosition.bottom = MAIN_DLG_SIZE_Y - 85;
	this->MoveWindow(&wndpl.rcNormalPosition);

	wndpl.rcNormalPosition.left = 30;
	wndpl.rcNormalPosition.top = 20;
	wndpl.rcNormalPosition.right = 6000;//wndpl.rcNormalPosition.left + 800 - 31;
	wndpl.rcNormalPosition.bottom = wndpl.rcNormalPosition.top + 800 - 44;
	for(int i = 0; i < 3; i++)
		//m_gridAlarm[i].MoveWindow(&wndpl.rcNormalPosition);

	GetDlgItem(IDC_STATIC_PAGE)->GetWindowPlacement(&wndpl);
	GetDlgItem(IDC_STATIC_PAGE_MONITER)->MoveWindow(&wndpl.rcNormalPosition);
	GetDlgItem(IDC_STATIC_PAGE_NG_LIST)->MoveWindow(&wndpl.rcNormalPosition);
}

void CAlarmDialog::initGrid()
{
	//m_gridAlarm[0].SetRows(MAX_ALARM_LIST_IN_PAGE+1);
	//m_gridAlarm[0].SetColAlignment(0, 4);
	//m_gridAlarm[0].SetColAlignment(1, 4);
	//m_gridAlarm[0].SetColWidth(0, 1500);
	//m_gridAlarm[0].SetColWidth(1, 6000);//9450
	//sLangChange.LoadStringA(IDS_STRING1175);	//날짜/시간
	//m_gridAlarm[0].SetTextMatrix(0, 0, sLangChange);
	//sLangChange.LoadStringA(IDS_STRING1298);	//알람 내역
	//m_gridAlarm[0].SetTextMatrix(0, 1, sLangChange);

	//m_gridAlarm[1].SetRows(MAX_ALARM_LIST_IN_PAGE+1);
	//m_gridAlarm[1].SetColAlignment(0, 4);
	//m_gridAlarm[1].SetColAlignment(1, 4);
	//m_gridAlarm[1].SetColWidth(0, 1500);
	//m_gridAlarm[1].SetColWidth(1, 6000);
	//sLangChange.LoadStringA(IDS_STRING1175);	//날짜/시간
	//m_gridAlarm[0].SetTextMatrix(0, 0, sLangChange);
	//sLangChange.LoadStringA(IDS_STRING1298);	//알람 내역
	//m_gridAlarm[0].SetTextMatrix(0, 1, sLangChange);

	//m_gridAlarm[2].SetRows(MAX_ALARM_LIST_IN_PAGE+1);
	//m_gridAlarm[2].SetCols(6);
	//m_gridAlarm[2].SetColAlignment(0, 4);
	//m_gridAlarm[2].SetColAlignment(1, 4);
	//m_gridAlarm[2].SetColAlignment(2, 4);
	//m_gridAlarm[2].SetColAlignment(3, 4);
	//m_gridAlarm[2].SetColAlignment(4, 4);
	//m_gridAlarm[2].SetColAlignment(5, 4);
	//m_gridAlarm[2].SetColWidth(0, 2000);
	//m_gridAlarm[2].SetColWidth(1, 1000);
	//m_gridAlarm[2].SetColWidth(2, 1000);
	//m_gridAlarm[2].SetColWidth(3, 1000);
	//m_gridAlarm[2].SetColWidth(4, 2000);
	//m_gridAlarm[2].SetColWidth(5, 4450);
	//sLangChange.LoadStringA(IDS_STRING1175);	//날짜/시간
	//m_gridAlarm[2].SetTextMatrix(0, 0, sLangChange);
	//sLangChange.LoadStringA(IDS_STRING756);	//"Lot 명"
	//m_gridAlarm[2].SetTextMatrix(0, 1, sLangChange);
	//sLangChange.LoadStringA(IDS_STRING1267);	//생산 수
	//m_gridAlarm[2].SetTextMatrix(0, 2, sLangChange);
	//sLangChange.LoadStringA(IDS_STRING847);	//불량 수
	//m_gridAlarm[2].SetTextMatrix(0, 3, sLangChange);
	//m_gridAlarm[2].SetTextMatrix(0, 4, _T("Chip ID"));
	//sLangChange.LoadStringA(IDS_STRING1493);	//불량 내용
	//m_gridAlarm[2].SetTextMatrix(0, 5, sLangChange);
}

void CAlarmDialog::SaveAlarm()
{
	SYSTEMTIME time;
	::GetLocalTime(&time);

	FILE *out; 

	CFileFind finder;
	BOOL IsFind;
	CString FolderName;

	FolderName.Format("%s\\%04d%02d", ALARM_DIR, time.wYear, time.wMonth);
	IsFind = finder.FindFile(FolderName);

	if(!IsFind)
	{
		FolderName.Format("%s", BASE_DIR);
		IsFind = finder.FindFile(FolderName);
		if(!IsFind)
		{
			CreateDirectory(FolderName,NULL); 
		}

		FolderName.Format("%s", ALARM_DIR);
		IsFind = finder.FindFile(FolderName);
		if(!IsFind)
		{
			CreateDirectory(FolderName,NULL); 
		}

		FolderName.Format("%s\\%04d%02d", ALARM_DIR, time.wYear, time.wMonth);
		CreateDirectory(FolderName,NULL);
	}
	finder.Close();


	int index = MAX_ALARM_LIST_IN_PAGE * m_iAlarmPage[e_AlarmHistory] + m_iAlarmCnt[e_AlarmHistory] - 1;
	if(index<0)
		return;

	char fileName[1000] = {NULL,};
	wsprintf(fileName, "%s\\AlarmData_%04d%02d%02d.csv", FolderName, time.wYear, time.wMonth, time.wDay);

	if(!fopen_s(&out, fileName,"a"))
	{
		fprintf_s(out, "%s\n", (LPTSTR)(LPCTSTR)m_sAlarmList[e_AlarmHistory][ index ]);
		if(out)		fclose(out);
	}
}


void CAlarmDialog::OnBnClickedButtonBack()
{
	if (m_icurPage[m_iAlarmKind] ==0) 	
		return;	

	else
	{
		m_icurPage[m_iAlarmKind] --;
		DrawGrid(1);		
	}	
}


void CAlarmDialog::OnBnClickedButtonNext()
{
	if ( (m_icurPage[m_iAlarmKind] ==(MAX_ALARM_PAGE_CNT-1)) || (m_icurPage[m_iAlarmKind] == m_iAlarmPage[m_iAlarmKind]) )
		return;	

	else
	{
		m_icurPage[m_iAlarmKind] ++;

		DrawGrid(1);
	}
}

void CAlarmDialog::PushAlarm()
{
	//한 페이지식 이동, 마지막페이지 클리어
	for (int i=0; i<MAX_ALARM_PAGE_CNT; i++)
	{
		for (int j=0; j<MAX_ALARM_LIST_IN_PAGE; j++)
		{
			if (i == (MAX_ALARM_PAGE_CNT-1))
				m_sAlarmList[m_iAlarmKind][ (MAX_ALARM_LIST_IN_PAGE * i) + j ].Empty();
			else
				m_sAlarmList[m_iAlarmKind][ (MAX_ALARM_LIST_IN_PAGE * i) + j ] = m_sAlarmList[m_iAlarmKind][ (MAX_ALARM_LIST_IN_PAGE * (i+1)) + j ];
		}
	}
}

void CAlarmDialog::DrawGrid(int flag)
{ // 0은 모두 지움, 1은 현재 페이지를 그려줌, 2는 가장 최근 페이지를 그려줌
	int i=0, index = 0;
	CString day="";
	CString str="";
	CString temp="";


	// 기존 것들을 지워준다.
	for (i=1; i<=MAX_ALARM_LIST_IN_PAGE; i++)
	{
		m_clGridAlarm.SetItemText(i, 0, "");
		m_clGridAlarm.SetItemText(i, 1, "");

		if(m_iAlarmKind == 2)
		{
			m_clGridAlarm.SetItemText(i, 2, "");
			m_clGridAlarm.SetItemText(i, 3, "");
			m_clGridAlarm.SetItemText(i, 4, "");
			m_clGridAlarm.SetItemText(i, 5, "");
		}
	}

	int cnt = MAX_ALARM_LIST_IN_PAGE;
	if(flag ==1)
	{
		temp.Format("%02d / %02d", m_icurPage[m_iAlarmKind]+1, m_iAlarmPage[m_iAlarmKind]+1);
		GetDlgItem(IDC_STATIC_PAGE)->SetWindowText(temp);
	}
	else if(flag ==2)
	{
		cnt = m_iAlarmCnt[m_iAlarmKind];
		m_icurPage[m_iAlarmKind] = m_iAlarmPage[m_iAlarmKind];
		temp.Format("%02d / %02d", m_iAlarmPage[m_iAlarmKind]+1, m_iAlarmPage[m_iAlarmKind]+1);
	}
	else
		return;

	if(m_iAlarmKind == e_AlarmHistory)
		GetDlgItem(IDC_STATIC_PAGE)->SetWindowText(temp);
	else if(m_iAlarmKind == e_AlarmMoniter)
		GetDlgItem(IDC_STATIC_PAGE_MONITER)->SetWindowText(temp);
	else if(m_iAlarmKind == e_NgList)
		GetDlgItem(IDC_STATIC_PAGE_NG_LIST)->SetWindowText(temp);


	for (i = 0; i < cnt; i++)
	{
		if(flag ==1)
			temp = m_sAlarmList[m_iAlarmKind][ MAX_ALARM_LIST_IN_PAGE * m_icurPage[m_iAlarmKind] + i];
		else
			temp = m_sAlarmList[m_iAlarmKind][ MAX_ALARM_LIST_IN_PAGE * m_iAlarmPage[m_iAlarmKind] + i];

		if(m_iAlarmKind==2)
		{
			CString tmpStr;

			index = temp.Find(',');
			if(index>=0)
			{
				day = temp.Mid(0, index);
				str = temp.Mid(index+1);
				m_clGridAlarm.SetItemText( i+1, 0, day);
			}
			else
				continue;

			index =str.Find(',');
			if(index>=0)
			{
				tmpStr = str.Mid(0, index);
				str = str.Mid(index+1);
				m_clGridAlarm.SetItemText( i+1, 1, tmpStr);
			}
			else
				continue;

			index =str.Find(',');
			if(index>=0)
			{
				tmpStr = str.Mid(0, index);
				str = str.Mid(index+1);
				m_clGridAlarm.SetItemText( i+1, 2, tmpStr);
			}
			else
				continue;

			index =str.Find(',');
			if(index>=0)
			{
				tmpStr = str.Mid(0, index);
				str = str.Mid(index+1);
			}
			else
				continue;

			index =str.Find(',');
			if(index>=0)
			{
				tmpStr = str.Mid(0, index);
				str = str.Mid(index+1);
			}
			else
				continue;

			index =str.Find(',');
			if(index>=0)
			{
				tmpStr = str.Mid(0, index);
				str = str.Mid(index+1);
				m_clGridAlarm.SetItemText( i+1, 3, tmpStr);
			}
			else
				continue;

			index =str.Find(',');
			if(index>=0)
			{
				tmpStr = str.Mid(0, index);
				str = str.Mid(index+1);
				m_clGridAlarm.SetItemText( i+1, 4, tmpStr);
			}
			else
				continue;


			tmpStr = str.Mid(1);
			m_clGridAlarm.SetItemText( i+1, 5, tmpStr);
		}
		else
		{
			CString tmpStr;

			index =temp.Find(',');
			if(index>=0)
			{
				day = temp.Mid(0, index);
				str = temp.Mid(index+1);
				m_clGridAlarm.SetItemText( i+1, 0, day);
				m_clGridAlarm.SetItemText( i+1, 1, str);
			}
			else
			{
				m_clGridAlarm.SetItemText( i+1, 1, temp);
			}
		}
	}

	//// 기존 것들을 지워준다.
	//for (i=1; i<=MAX_ALARM_LIST_IN_PAGE; i++)
	//{
	//	m_gridAlarm[m_iAlarmKind].SetTextMatrix(i, 0, "");
	//	m_gridAlarm[m_iAlarmKind].SetTextMatrix(i, 1, "");

	//	if(m_iAlarmKind == 2)
	//	{
	//		m_gridAlarm[m_iAlarmKind].SetTextMatrix(i, 2, "");
	//		m_gridAlarm[m_iAlarmKind].SetTextMatrix(i, 3, "");
	//		m_gridAlarm[m_iAlarmKind].SetTextMatrix(i, 4, "");
	//		m_gridAlarm[m_iAlarmKind].SetTextMatrix(i, 5, "");
	//	}
	//}

	//int cnt = MAX_ALARM_LIST_IN_PAGE;
	//if(flag ==1)
	//{
	//	temp.Format("%02d / %02d", m_icurPage[m_iAlarmKind]+1, m_iAlarmPage[m_iAlarmKind]+1);
	//	GetDlgItem(IDC_STATIC_PAGE)->SetWindowText(temp);
	//}
	//else if(flag ==2)
	//{
	//	cnt = m_iAlarmCnt[m_iAlarmKind];
	//	m_icurPage[m_iAlarmKind] = m_iAlarmPage[m_iAlarmKind];
	//	temp.Format("%02d / %02d", m_iAlarmPage[m_iAlarmKind]+1, m_iAlarmPage[m_iAlarmKind]+1);
	//}
	//else
	//	return;

	//if(m_iAlarmKind == e_AlarmHistory)
	//	GetDlgItem(IDC_STATIC_PAGE)->SetWindowText(temp);
	//else if(m_iAlarmKind == e_AlarmMoniter)
	//	GetDlgItem(IDC_STATIC_PAGE_MONITER)->SetWindowText(temp);
	//else if(m_iAlarmKind == e_NgList)
	//	GetDlgItem(IDC_STATIC_PAGE_NG_LIST)->SetWindowText(temp);


	//for (i = 0; i < cnt; i++)
	//{
	//	if(flag ==1)
	//		temp = m_sAlarmList[m_iAlarmKind][ MAX_ALARM_LIST_IN_PAGE * m_icurPage[m_iAlarmKind] + i];
	//	else
	//		temp = m_sAlarmList[m_iAlarmKind][ MAX_ALARM_LIST_IN_PAGE * m_iAlarmPage[m_iAlarmKind] + i];

	//	if(m_iAlarmKind==2)
	//	{
	//		CString tmpStr;

	//		index = temp.Find(',');
	//		if(index>=0)
	//		{
	//			day = temp.Mid(0, index);
	//			str = temp.Mid(index+1);
	//			m_gridAlarm[m_iAlarmKind].SetTextMatrix( i+1, 0, day);
	//		}
	//		else
	//			continue;

	//		index =str.Find(',');
	//		if(index>=0)
	//		{
	//			tmpStr = str.Mid(0, index);
	//			str = str.Mid(index+1);
	//			m_gridAlarm[m_iAlarmKind].SetTextMatrix( i+1, 1, tmpStr);
	//		}
	//		else
	//			continue;

	//		index =str.Find(',');
	//		if(index>=0)
	//		{
	//			tmpStr = str.Mid(0, index);
	//			str = str.Mid(index+1);
	//			m_gridAlarm[m_iAlarmKind].SetTextMatrix( i+1, 2, tmpStr);
	//		}
	//		else
	//			continue;

	//		index =str.Find(',');
	//		if(index>=0)
	//		{
	//			tmpStr = str.Mid(0, index);
	//			str = str.Mid(index+1);
	//		}
	//		else
	//			continue;

	//		index =str.Find(',');
	//		if(index>=0)
	//		{
	//			tmpStr = str.Mid(0, index);
	//			str = str.Mid(index+1);
	//		}
	//		else
	//			continue;

	//		index =str.Find(',');
	//		if(index>=0)
	//		{
	//			tmpStr = str.Mid(0, index);
	//			str = str.Mid(index+1);
	//			m_gridAlarm[m_iAlarmKind].SetTextMatrix( i+1, 3, tmpStr);
	//		}
	//		else
	//			continue;

	//		index =str.Find(',');
	//		if(index>=0)
	//		{
	//			tmpStr = str.Mid(0, index);
	//			str = str.Mid(index+1);
	//			m_gridAlarm[m_iAlarmKind].SetTextMatrix( i+1, 4, tmpStr);
	//		}
	//		else
	//			continue;


	//		tmpStr = str.Mid(1);
	//		m_gridAlarm[m_iAlarmKind].SetTextMatrix( i+1, 5, tmpStr);
	//	}
	//	else
	//	{
	//		CString tmpStr;

	//		index =temp.Find(',');
	//		if(index>=0)
	//		{
	//			day = temp.Mid(0, index);
	//			str = temp.Mid(index+1);
	//			m_gridAlarm[m_iAlarmKind].SetTextMatrix( i+1, 0, day);
	//			m_gridAlarm[m_iAlarmKind].SetTextMatrix( i+1, 1, str);
	//		}
	//		else
	//		{
	//			m_gridAlarm[m_iAlarmKind].SetTextMatrix( i+1, 1, temp);
	//		}
	//	}
	//}
}


void CAlarmDialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if(bShow)
	{
		SelectAlarm();
		DrawGrid(2);
	}
}


void CAlarmDialog::LoadAlarm()
{
	LoadAlarm_History();
	LoadAlarm_NgList();
}


void CAlarmDialog::LoadAlarm_History()
{
	SYSTEMTIME time;
	::GetLocalTime(&time);

	FILE *in; 

	char fileName[1000];
	wsprintf(fileName, "%s\\%04d%02d\\AlarmData_%04d%02d%02d.csv", ALARM_DIR, time.wYear, time.wMonth, time.wYear, time.wMonth, time.wDay);
	//wsprintf(fileName, "%s\\AlarmData_%04d%02d%02d.csv", FolderName, time.wYear, time.wMonth, time.wDay);
	int alarmCnt = 0;
	int skipCnt = 0;

	if(!fopen_s(&in, fileName,"r"))
	{
		char	Line[500];
		char	Title[500];
		int		nRtn;

		CString tmp;

		while (1)
		{
			fgets(Line, 499, in);
			nRtn = sscanf_s(Line, "%s", &Title, 499);

			if (nRtn==EOF)	
				break;

			alarmCnt++;
			Line[0] = 0;
		}

		if(in)	fclose(in);
	}


	skipCnt = alarmCnt - (MAX_ALARM_LIST_IN_PAGE) * MAX_ALARM_PAGE_CNT;
	alarmCnt = 0;
	int addCnt = 0;


	if(!fopen_s(&in, fileName,"r"))
	{
		char	Line[500];
		char	Title[500];
		int		nRtn;

		CString tmp;

		while (1)
		{
			fgets(Line, 499, in);
			nRtn = sscanf_s(Line, "%s", &Title, 499);

			if (nRtn==EOF)	
				break;

			if (alarmCnt >= skipCnt)
			{
				m_sAlarmList[e_AlarmHistory][addCnt] = Line;
				addCnt++;
			}
			alarmCnt++;

			Line[0] = 0x00;
		}

		if(in)	fclose(in);
	}

	m_iAlarmPage[e_AlarmHistory] = (addCnt-1) / MAX_ALARM_LIST_IN_PAGE;
	m_iAlarmCnt[e_AlarmHistory] = ((addCnt-1) % MAX_ALARM_LIST_IN_PAGE + 1);
}


void CAlarmDialog::LoadAlarm_NgList()
{
	SYSTEMTIME time;
	::GetLocalTime(&time);

	FILE *in; 

	char fileName[1000];
	wsprintf(fileName, "%s\\%04d%02d\\AlarmData_%04d%02d%02d.csv", ALARM_DIR, time.wYear, time.wMonth, time.wYear, time.wMonth, time.wDay);
	//wsprintf(fileName, "%s\\AlarmData_%04d%02d%02d.csv", FolderName, time.wYear, time.wMonth, time.wDay);
	int alarmCnt = 0;
	int skipCnt = 0;

	if(!fopen_s(&in, fileName,"r"))
	{
		char	Line[500] = {NULL,};
		char	Title[500] = {NULL,};
		int		nRtn = 0;

		CString tmp;

		fgets(Line, 499, in);

		while (1)
		{
			fgets(Line, 499, in);
			nRtn = sscanf_s(Line, "%s", &Title, 499);

			if (nRtn==EOF)	
				break;

			alarmCnt++;
			Line[0] = 0;
		}

		if(in)	fclose(in);
	}


	skipCnt = alarmCnt - (MAX_ALARM_LIST_IN_PAGE) * MAX_ALARM_PAGE_CNT;
	alarmCnt = 0;
	int addCnt = 0;


	if(!fopen_s(&in, fileName,"r"))
	{
		char	Line[500];
		char	Title[500];
		int		nRtn;

		CString tmp;

		fgets(Line, 499, in);

		while (1)
		{
			fgets(Line, 499, in);
			nRtn = sscanf_s(Line, "%s", &Title, 499);

			if (nRtn==EOF)	
				break;

			if (alarmCnt >= skipCnt)
			{
				m_sAlarmList[e_NgList][addCnt] = Line;
				addCnt++;
			}
			alarmCnt++;

			Line[0] = 0x00;
		}

		if(in)	fclose(in);
	}

	m_iAlarmPage[e_NgList] = (addCnt-1) / MAX_ALARM_LIST_IN_PAGE;
	m_iAlarmCnt[e_NgList] = ((addCnt-1) % MAX_ALARM_LIST_IN_PAGE + 1);
}


void CAlarmDialog::OnBnClickedButtonClear()
{
	CString tmpStr;
	CString sTemp;
	sLangChange.LoadStringA(IDS_STRING386);
	sTemp.LoadString(IDS_STRING845);
	if (m_iAlarmKind==0)			tmpStr.Format(sLangChange);	//"Alarm History를 Clear 하시겠습니까?"
	else if (m_iAlarmKind==2)		tmpStr.Format(sTemp);

	if(m_iAlarmKind != 1)
	{
		if(askMsg(tmpStr) == false)
			return;
	}

	m_iAlarmPage[m_iAlarmKind] = 0;
	m_iAlarmCnt[m_iAlarmKind] = 0;

	initGrid();

	if (m_iAlarmKind==1)
	{
		g_AlarmCnt = 0;
		g_AlarmFlag = checkAlarm();
	}

	DrawGrid(2);
}


void CAlarmDialog::OnBnClickedButtonBuzzerOff()
{
	Dio.setAlarm(ALARM_OFF);
}


void CAlarmDialog::SelectAlarm()
{
	DrawGrid(2);

	/*for(int i = 0; i < 3; i++)
		m_gridAlarm[i].ShowWindow(SW_HIDE);
*/
	//m_gridAlarm[m_iAlarmKind].ShowWindow(SW_SHOW);


	if(m_iAlarmKind == e_AlarmHistory)
	{
		m_btnAlarmHistory.m_iStateBtn = 1;
		m_btnAlarmMonitor.m_iStateBtn = 0;
		m_btnNgList.m_iStateBtn = 0;

		GetDlgItem(IDC_STATIC_PAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PAGE_MONITER)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PAGE_NG_LIST)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_BUTTON_CLEAR)->SetWindowText("Alarm History Clear");	//Alarm History Clear
// 		GetDlgItem(IDC_BUTTON_RESET)->ShowWindow(false);
	}
	else if(m_iAlarmKind == e_AlarmMoniter)
	{
		m_btnAlarmHistory.m_iStateBtn = 0;
		m_btnAlarmMonitor.m_iStateBtn = 1;
		m_btnNgList.m_iStateBtn = 0;

		GetDlgItem(IDC_STATIC_PAGE_MONITER)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PAGE_NG_LIST)->ShowWindow(SW_HIDE);
		sLangChange.LoadStringA(IDS_STRING388);
		GetDlgItem(IDC_BUTTON_CLEAR)->SetWindowText(sLangChange);	//Alarm Reset
//		GetDlgItem(IDC_BUTTON_RESET)->ShowWindow(true);
	}
	else		// NG List
	{
		m_btnAlarmHistory.m_iStateBtn = 0;
		m_btnAlarmMonitor.m_iStateBtn = 0;
		m_btnNgList.m_iStateBtn = 1;

		GetDlgItem(IDC_STATIC_PAGE_NG_LIST)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PAGE_MONITER)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_BUTTON_CLEAR)->SetWindowText("NG List Clear");
//		GetDlgItem(IDC_BUTTON_RESET)->ShowWindow(false);
	}

	m_btnAlarmHistory.Invalidate();
	m_btnAlarmMonitor.Invalidate();
	m_btnNgList.Invalidate();
}

void CAlarmDialog::OnBnClickedButtonNgList()
{
	m_iAlarmKind = e_NgList;
	SelectAlarm();
}


void CAlarmDialog::OnBnClickedButtonAlarmMonitor()
{
	m_iAlarmKind = e_AlarmMoniter;
	SelectAlarm();
}


void CAlarmDialog::OnBnClickedButtonAlarmHistory()
{
	m_iAlarmKind = e_AlarmHistory;
	SelectAlarm();
}


void CAlarmDialog::AlarmAdd(CString msg, int iAlarmKind)
{
	SYSTEMTIME time;
	::GetLocalTime(&time);
	CString temp, day, str;
	int index;

	m_iAlarmCnt[iAlarmKind]++;

	// 1~24까지 유효영역
	if (m_iAlarmCnt[iAlarmKind] ==  (MAX_ALARM_LIST_IN_PAGE+1))
	{
		m_iAlarmCnt[iAlarmKind] = 1;
		m_iAlarmPage[iAlarmKind]++;

		if (m_iAlarmPage[iAlarmKind] == MAX_ALARM_PAGE_CNT)
		{
			m_iAlarmPage[iAlarmKind] = MAX_ALARM_PAGE_CNT-1;
			PushAlarm();
		}
	}


	temp.Format("%02d월 %02d일. %02d:%02d:%02d, %s", time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, msg);

	index = MAX_ALARM_LIST_IN_PAGE * m_iAlarmPage[iAlarmKind] + m_iAlarmCnt[iAlarmKind] - 1;

	if(index<0)
		index = 0;

	m_sAlarmList[iAlarmKind][ index ] = temp;
	m_icurPage[iAlarmKind] = m_iAlarmPage[iAlarmKind];


	if(iAlarmKind == e_AlarmHistory)
	{
		SaveAlarm();

		m_iAlarmCnt[1]		= 1;
		m_icurPage[1]		= 0;
		m_sAlarmList[1][0]	= temp;

		checkAlarm();
	}

	DrawGrid(2);

	m_iAlarmKind = iAlarmKind;
}

bool CAlarmDialog::checkAlarm()				// 알람 발생 상태이면 false..
{
	bool rtnFlag = true;

	SYSTEMTIME time;
	::GetLocalTime(&time);


	bool errFlag, negSensorFlag, posSensorFlag;

	CString temp;
	temp.Format("%02d월 %02d일. %02d:%02d:%02d,", time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);


	for (int i=0; i<MAX_MOTOR_NO; i++)
	{
		errFlag = motor.GetAmpFault(i);
		negSensorFlag = motor.GetNegaSensor(i);
		posSensorFlag = motor.GetPosiSensor(i);

		if (errFlag)
		{
			m_sAlarmList[1][ m_iAlarmCnt[1] ].Format("%s [%s] Serve Alarm Occurrence.", temp, MotorName[i]);
			m_iAlarmCnt[1]++;
			rtnFlag = false;
		}

		if (m_iAlarmCnt[1]>=MAX_ALARM_LIST_IN_PAGE)
			break;

		if (negSensorFlag)
		{
			m_sAlarmList[1][ m_iAlarmCnt[1] ].Format("%s [%s] (-) Limit Sensor Detect.", temp, MotorName[i]);
			m_iAlarmCnt[1]++;
			rtnFlag = false;
		}

		if (m_iAlarmCnt[1]>=MAX_ALARM_LIST_IN_PAGE)
			break;

		if (posSensorFlag)
		{
			m_sAlarmList[1][ m_iAlarmCnt[1] ].Format("%s [%s] (+) Limit Sensor Detect.", temp, MotorName[i]);
			m_iAlarmCnt[1]++;
			rtnFlag = false;
		}

		if (m_iAlarmCnt[1]>=MAX_ALARM_LIST_IN_PAGE)
			break;
	}


	if (m_iAlarmCnt[1]>=MAX_ALARM_LIST_IN_PAGE)
		return rtnFlag;



	///////////////////////////////////////////////////////////////////
	// PCB 흡착 확인

	int moduleNo = 0;
	int channelNo = 1;

	bool bOutVaccumFlag, bOutBlowFlag, bInVaccumOnFlag;			// 둘 다 OFF 시 흡착, Vaccum만 살면 탈착


	bInVaccumOnFlag = Dio.PCBvaccumOnCheck(true, false);

//	bOutVaccumFlag = (curOutDioByte[moduleNo][channelNo] & DIO_OUT_PCB_VACUUM) ? true : false;
	//bOutBlowFlag = (curOutDioByte[moduleNo][channelNo] & DIO_OUT_PCB_VACUUM_OFF) ? true : false;

	/*if(!bOutVaccumFlag && !bOutBlowFlag)
	{
		if(!bInVaccumOnFlag)
		{
			m_sAlarmList[1][ m_iAlarmCnt[1] ].Format("%s PCB 흡착 센서 감지 실패.", temp);
			m_iAlarmCnt[1]++;
			rtnFlag = false;
		}
	}
	else if (bInVaccumOnFlag)
	{
		m_sAlarmList[1][ m_iAlarmCnt[1] ].Format("%s PCB 흡착 OFF 감지 실패.", temp);
		m_iAlarmCnt[1]++;
		rtnFlag = false;
	}*/

	if (m_iAlarmCnt[1]>=MAX_ALARM_LIST_IN_PAGE)
		return rtnFlag;



	///////////////////////////////////////////////////////////////////
	// PCB Push 전후진 확인.
	moduleNo = 0;
	channelNo = 0;

	//bool bOutPushForFlag	= (curOutDioByte[moduleNo][channelNo] & DIO_OUT_PCB_PUSH_FOR) ? true : false;
	//bool bOutPushBackFlag	= (curOutDioByte[moduleNo][channelNo] & DIO_OUT_PCB_PUSH_BACK) ? true : false;

	//bool bInPushForFlag		= (curInDio[0] & DIO_IN_PCB_PUSH_FOR) ? true : false;
	//bool bInPushBackFlag	= (curInDio[0] & DIO_IN_PCB_PUSH_BACK) ? true : false;


	//if(bOutPushForFlag && !bOutPushBackFlag)			// 전진..
	//{
	//	if(!bInPushForFlag || bInPushBackFlag)
	//	{
	//		m_sAlarmList[1][ m_iAlarmCnt[1] ].Format("%s PCB Cover 전진 실패.", temp);
	//		m_iAlarmCnt[1]++;
	//		rtnFlag = false;
	//	}
	//}
	//else if(!bOutPushForFlag && bOutPushBackFlag)		// 후진..
	//{
	//	if(bInPushForFlag || !bInPushBackFlag)
	//	{
	//		m_sAlarmList[1][ m_iAlarmCnt[1] ].Format("%s PCB Cover 후진 실패.", temp);
	//		m_iAlarmCnt[1]++;
	//		rtnFlag = false;
	//	}
	//}

	if (m_iAlarmCnt[1]>=MAX_ALARM_LIST_IN_PAGE)
		return rtnFlag;

	///////////////////////////////////////////////////////////////////
	// Lens Grip 전후진 확인.
	moduleNo = 0;
	channelNo = 1;

	bool bOutGripForFlag	= (curOutDioByte[moduleNo][channelNo] & DIO_OUT_LENS_GRIP_FOR) ? true : false;
	bool bOutGripBackFlag	= (curOutDioByte[moduleNo][channelNo] & DIO_OUT_LENS_GRIP_BACK) ? true : false;


	if (m_iAlarmCnt[1]>=MAX_ALARM_LIST_IN_PAGE)
		return rtnFlag;

	return TRUE;
}


void CAlarmDialog::OnBnClickedButtonReset()
{
	m_iAlarmPage[1] = 0;
	m_iAlarmCnt[1] = 0;

	int curIndex = m_iAlarmKind;
	m_iAlarmKind = 1;

	initGrid();

	g_AlarmCnt = 0;
	g_AlarmFlag = checkAlarm();
	DrawGrid(2);

	m_iAlarmKind = curIndex;
}
