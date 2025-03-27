// IoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "IoDlg.h"
#include "afxdialogex.h"

// CIoDlg 대화 상자입니다.
IMPLEMENT_DYNAMIC(CIoDlg, CDialogEx)

	CIoDlg::CIoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CIoDlg::IDD, pParent)
{

}

CIoDlg::~CIoDlg()
{
}

void CIoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CIoDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CIoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CIoDlg::OnBnClickedCancel)
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_WM_MOUSEWHEEL()

	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_IO_OUT_GRID, &CIoDlg::OnDBClickedGridOut)
END_MESSAGE_MAP()


// CIoDlg 메시지 처리기입니다.
BOOL CIoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	setInterface();
	InitGridCtrl_In();
	InitGridCtrl_Out();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CIoDlg::OnBnClickedOk(){}
void CIoDlg::OnBnClickedCancel(){}


void CIoDlg::setInterface()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	WINDOWPLACEMENT wndpl;
	this->GetWindowPlacement(&wndpl);

	wndpl.rcNormalPosition = pFrame->m_rectCamDispPos2;
	wndpl.rcNormalPosition.right = pFrame->m_rectCamDispPos2.right + 100;
	wndpl.rcNormalPosition.left = pFrame->m_rectCamDispPos2.left - 0;
	wndpl.rcNormalPosition.top -= SUB_DLG_OFFSET_Y - 10;
	wndpl.rcNormalPosition.bottom = MAIN_DLG_SIZE_Y - 5 - 90;

	this->MoveWindow(&wndpl.rcNormalPosition);
}

void CIoDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	m_bShowFlag = bShow ? true : false;

	if(bShow)
	{
		for (int i=0; i<5; i++)
		{
			oldInVal[i] = (~curInDio[i]) & 0xFF;
		}
		dispOutputData();

		timerRunFlag = false;
		SetTimer(IO_TIMER, 200, NULL);
	}
	else
	{
		KillTimer(IO_TIMER);
	}
}


void CIoDlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent==IO_TIMER)
	{
		if (!timerRunFlag)
		{
			timerRunFlag = true;

			dispInputData();

			timerRunFlag = false;
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CIoDlg::OnDBClickedGridOut(NMHDR* pNMHDR, LRESULT* pResult)
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;

	int curRow = pNMGridView->iRow; 
	int col = pNMGridView->iColumn;

	if (curRow>=0 && curRow<32)
	{
		int channelNo	= (curRow-1) / 8;
		int bitNo		= (curRow - 1) % 8;

		int flag = (curOutDioByte[0][channelNo] & (0x01<<bitNo));

		if (flag)
		{
			int mask = 0xFF - (0x01<<bitNo);
			motor.OutDIO(0, channelNo, (curOutDioByte[0][channelNo] & mask));

			m_clGrid_IO_Out.SetItemBkColor((curRow) , 2, GRID_COLOR_WHITE);
		}
		else
		{
			motor.OutDIO(0, channelNo, (curOutDioByte[0][channelNo] | (0x01<<bitNo)));

			m_clGrid_IO_Out.SetItemBkColor((curRow) , 2, GRID_COLOR_DIO_OUT);

		}
	}
	else
	{
		int channelNo	= ((curRow - 1) - 32) / 8;
		int bitNo		= ((curRow - 1) - 32) % 8;

		int flag = (curOutDioByte[2][channelNo] & (0x01<<bitNo));


		if (flag) 
		{
			int mask = 0xFF - (0x01<<bitNo);
			motor.OutDIO(2, channelNo, (curOutDioByte[2][channelNo] & mask));
			m_clGrid_IO_Out.SetItemBkColor((curRow) , 2, GRID_COLOR_WHITE);
			
		}
		else
		{
			motor.OutDIO(2, channelNo, (curOutDioByte[2][channelNo] | (0x01<<bitNo)));
			m_clGrid_IO_Out.SetItemBkColor((curRow) , 2, GRID_COLOR_DIO_OUT);
		}
	}
	m_clGrid_IO_Out.Invalidate(); 
}
void CIoDlg::InitGridCtrl_In()
{
	CRect rect;
	CWnd *pWnd= (CWnd*)GetDlgItem(IDC_STATIC_IO_IN_GRID); 
	inRow = 65;//아래
	inCol = 3;//옆
	int margin = 20;
	int gridHeight = 35;
	int gridWidth1 = 40;
	int gridWidth2 = 140;
	int gridWidth3 = 40;
	int totalWidth = gridWidth1+gridWidth2+gridWidth3;
	//
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = totalWidth +margin;
	rect.bottom = (gridHeight*25)+4;//rect.bottom = (gridHeight*inRow) +margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.

	GetDlgItem(IDC_STATIC_IO_IN_GRID)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGrid_IO_In.Create(rect, this, IDC_STATIC_IO_IN_GRID, WS_TABSTOP | WS_VISIBLE);

	m_clGrid_IO_In.SetTextBkColor(GRID_COLOR_WHITE);
	m_clGrid_IO_In.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGrid_IO_In.SetFixedTextColor(GRID_COLOR_WHITE);
	m_clGrid_IO_In.SetReference_Setting();
	m_clGrid_IO_In.EnableSelection(FALSE);
	m_clGrid_IO_In.SetRowCount(inRow);
	m_clGrid_IO_In.SetColumnCount(inCol);
	m_clGrid_IO_In.SetFixedRowCount(1);
	m_clGrid_IO_In.SetFixedColumnCount(1);
	CString tmpStr="";


	m_clGrid_IO_In.SetItemText(0, 0, _T("No"));
	m_clGrid_IO_In.SetItemText(0, 1, "입력 Comment");
	m_clGrid_IO_In.SetItemText(0, 2, "입력");	
	//
	for(int i=0; i<inRow-1; i++)
	{
		tmpStr.Format("%d", i+1);
		m_clGrid_IO_In.SetItemText(i+1, 0, tmpStr);
	}
	//
	m_clGrid_IO_In.SetItemText(1, 1, "EMERGENCY S/W #1");					
	m_clGrid_IO_In.SetItemText(2, 1, "START PB");
	/*m_clGrid_IO_In.SetItemText(6, 1, "PCB GRIP 후진");
	m_clGrid_IO_In.SetItemText(7, 1, "PCB GRIP 전진");*/

	m_clGrid_IO_In.SetItemText(9, 1, "LENS GRIP 후진");
	m_clGrid_IO_In.SetItemText(10, 1, "LENS GRIP 전진");
	
	m_clGrid_IO_In.SetItemText(11, 1, "PCB TURN");
	//m_clGrid_IO_In.SetItemText(10, 1, "PCB RETURN");

	/*m_clGrid_IO_In.SetItemText(17, 1, "DOOR SENSOR #1");
	m_clGrid_IO_In.SetItemText(18, 1, "DOOR SENSOR #2");
	m_clGrid_IO_In.SetItemText(19, 1, "DOOR SENSOR #3");
	m_clGrid_IO_In.SetItemText(20, 1, "DOOR SENSOR #4");
	m_clGrid_IO_In.SetItemText(21, 1, "DOOR SENSOR #5");
	m_clGrid_IO_In.SetItemText(22, 1, "DOOR SENSOR #6");
	m_clGrid_IO_In.SetItemText(23, 1, "DOOR SENSOR #7");
	m_clGrid_IO_In.SetItemText(24, 1, "DOOR SENSOR #8");

	m_clGrid_IO_In.SetItemText(26, 1, "Laser Cylinder 하강");
	m_clGrid_IO_In.SetItemText(27, 1, "Laser Cylinder 상승");

	m_clGrid_IO_In.SetItemText(28, 1, "PCB 상승");
	m_clGrid_IO_In.SetItemText(29, 1, "PCB 하강");

	m_clGrid_IO_In.SetItemText(31, 1, "Uv Cylinder 하강");
	m_clGrid_IO_In.SetItemText(32, 1, "Uv Cylinder 상승");*/

	//
	int i=0, j=0;
	for (i = 0; i < inRow; i++)
	{
		m_clGrid_IO_In.SetRowHeight(i, gridHeight);
		
		for (j = 0; j < inCol; j++)
		{
			m_clGrid_IO_In.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			if (i == 0)
			{
				if (j == 0)
				{
					m_clGrid_IO_In.SetColumnWidth(j, gridWidth1);
				}else if (j == 1){
					m_clGrid_IO_In.SetColumnWidth(j, gridWidth2);
				}else{
					m_clGrid_IO_In.SetColumnWidth(j, gridWidth3);
				}
			}			
		}
	}
	m_clGrid_IO_In.Invalidate();
}
void CIoDlg::InitGridCtrl_Out()
{
	CRect rect;
	CWnd *pWnd= (CWnd*)GetDlgItem(IDC_STATIC_IO_OUT_GRID); 
	outRow = 65;//아래
	outCol = 3;//옆
	int margin = 20;
	int gridHeight = 35;
	int gridWidth1 = 40;
	int gridWidth2 = 140;
	int gridWidth3 = 40;
	int totalWidth = gridWidth1+gridWidth2 + gridWidth3;
	//
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = totalWidth +margin;
	rect.bottom = (gridHeight*25) + 4;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.

	GetDlgItem(IDC_STATIC_IO_OUT_GRID)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGrid_IO_Out.Create(rect, this, IDC_STATIC_IO_OUT_GRID, WS_TABSTOP | WS_VISIBLE);

	m_clGrid_IO_Out.SetTextBkColor(GRID_COLOR_WHITE);
	m_clGrid_IO_Out.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGrid_IO_Out.SetFixedTextColor(GRID_COLOR_WHITE);
	m_clGrid_IO_Out.SetReference_Setting();
	m_clGrid_IO_Out.EnableSelection(FALSE);
	m_clGrid_IO_Out.SetRowCount(outRow);
	m_clGrid_IO_Out.SetColumnCount(outCol);
	m_clGrid_IO_Out.SetFixedRowCount(1);
	m_clGrid_IO_Out.SetFixedColumnCount(1);

	CString tmpStr="";


	m_clGrid_IO_Out.SetItemText(0, 0, _T("No"));
	m_clGrid_IO_Out.SetItemText(0, 1, "출력 Comment");
	m_clGrid_IO_Out.SetItemText(0, 2, "출력");	
	
	//
	for(int i=0; i<outRow-1; i++)
	{
		tmpStr.Format("%d", i+1);
		m_clGrid_IO_Out.SetItemText(i+1, 0, tmpStr);
	}
	//
	//m_clGrid_IO_Out.SetItemText(1, 1, "TOWER LAMP - Y");	
	//m_clGrid_IO_Out.SetItemText(2, 1, "TOWER LAMP - G");	
	//m_clGrid_IO_Out.SetItemText(3, 1, "TOWER LAMP - R");	
	//
	//m_clGrid_IO_Out.SetItemText(5, 1, "BUZZER1");
	//m_clGrid_IO_Out.SetItemText(6, 1, "BUZZER2");	
	//m_clGrid_IO_Out.SetItemText(7, 1, "BUZZER3");	
	//m_clGrid_IO_Out.SetItemText(8, 1, "BUZZER4");		
	//
	//m_clGrid_IO_Out.SetItemText(10, 1, "CONTACT 하강");
	//m_clGrid_IO_Out.SetItemText(11, 1, "CONTACT 상승");

	m_clGrid_IO_Out.SetItemText(9, 1, "LENS GRIP 후진");
	m_clGrid_IO_Out.SetItemText(10, 1, "LENS GRIP 전진");
	//
	//m_clGrid_IO_Out.SetItemText(14, 1, "PCB GRIP 후진");
	//m_clGrid_IO_Out.SetItemText(15, 1, "PCB GRIP 전진");
	//
	m_clGrid_IO_Out.SetItemText(15, 1, "EPOXY 토출 ON");

	m_clGrid_IO_Out.SetItemText(2, 1, "START PB");
	//m_clGrid_IO_Out.SetItemText(21, 1, "DOOR PB");
	////
	//m_clGrid_IO_Out.SetItemText(23, 1, "PCB TURN");
	//m_clGrid_IO_Out.SetItemText(24, 1, "PCB RETURN");
	////
	//m_clGrid_IO_Out.SetItemText(26, 1, "Uv Cylinder 하강");
	//m_clGrid_IO_Out.SetItemText(27, 1, "Uv Cylinder 상승");

	//m_clGrid_IO_Out.SetItemText(28, 1, "Laser Cylinder 하강");
	//m_clGrid_IO_Out.SetItemText(29, 1, "Laser Cylinder 상승");


	//												//
	//m_clGrid_IO_Out.SetItemText(18, 1, "UV - ON");				
	//m_clGrid_IO_Out.SetItemText(19, 1, "UV - EMG");			
	//
			
	//m_clGrid_IO_Out.SetItemText(32, 1, "HOLDER GRIP 후진");
	//m_clGrid_IO_Out.SetItemText(33, 1, "HOLDER GRIP 전진");
	


	//m_clGrid_IO_Out.SetItemText(40, 1, "검사 FEED 후진");
	//m_clGrid_IO_Out.SetItemText(41, 1, "검사 FEED 전진");	
	

	
	/*m_clGrid_IO_Out.SetItemText(44, 1, "LASER/CAM 전진");
	m_clGrid_IO_Out.SetItemText(45, 1, "LASER/CAM 후진");
	m_clGrid_IO_Out.SetItemText(48, 1, "DOOR CLOSE");
	m_clGrid_IO_Out.SetItemText(46, 1, "DOOR OPEN");*/
	//
	int i=0, j=0;
	for (i = 0; i < outRow; i++)
	{
		m_clGrid_IO_Out.SetRowHeight(i, gridHeight);
		
		for (j = 0; j < outCol; j++)
		{
			m_clGrid_IO_Out.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			if (i == 0)
			{
				if (j == 0)
				{
					m_clGrid_IO_Out.SetColumnWidth(j, gridWidth1);
				}else if (j == 1){
					m_clGrid_IO_Out.SetColumnWidth(j, gridWidth2);
				}else{
					m_clGrid_IO_Out.SetColumnWidth(j, gridWidth3);
				}
			}			
		}
	}
	m_clGrid_IO_Out.Invalidate();
}

void CIoDlg::initIoGrid()
{
}

BEGIN_EVENTSINK_MAP(CIoDlg, CDialogEx)
END_EVENTSINK_MAP()


void CIoDlg::dispInputData()
{
	int flag = 0;
	int rowNo = 0;
	int oldFlag = 0;

	for(int j=0; j<32; j++)
	{
		rowNo = j + 1;

		flag	= curInDio[0] & (0x01<<j);
		oldFlag	= oldInVal[0] & (0x01<<j);

		//if(flag != oldFlag)
		{
			if(flag)
			{
				//m_clGrid_IO_In.SetRow(rowNo);
				//m_clGrid_IO_In.SetCellBackColor(GRID_COLOR_DIO_IN);
				m_clGrid_IO_In.SetItemBkColor((rowNo) , 2, GRID_COLOR_DIO_IN);
			}
			else
			{
				//m_clGrid_IO_In.SetRow(rowNo);
				//m_clGrid_IO_In.SetCellBackColor(0);
				m_clGrid_IO_In.SetItemBkColor((rowNo) , 2, GRID_COLOR_WHITE);
			}
		}
	}


	for(int i = 32;i<64;i++)
	{
		rowNo = i + 1;

		flag	= curInDio[1] & (0x01<<(i - 32) );
		oldFlag	= oldInVal[1] & (0x01<<(i - 32) );

		if(flag)
		{
			//m_clGrid_IO_In.SetRow(rowNo);
			//m_clGrid_IO_In.SetCellBackColor(GRID_COLOR_DIO_IN);
			m_clGrid_IO_In.SetItemBkColor((rowNo) , 2, GRID_COLOR_DIO_IN);
		}
		else
		{
			//m_clGrid_IO_In.SetRow(rowNo);
			//m_clGrid_IO_In.SetCellBackColor(0);
			m_clGrid_IO_In.SetItemBkColor((rowNo) , 2, GRID_COLOR_WHITE);
		}
	}

	oldInVal[0] = curInDio[0];
	oldInVal[1] = curInDio[1];
	m_clGrid_IO_In.Invalidate();
}

void CIoDlg::dispOutputData()
{
	int flag = 0;
	int rowNo = 0;
	for(int j=0; j<32; j++)
	{
		rowNo = j + 1;

		flag	= curOutDioByte[0][j/8] & (0x01<<j%8);
		if(flag)
		{
			m_clGrid_IO_Out.SetItemBkColor((rowNo) , 2, GRID_COLOR_DIO_OUT);
		}
		else
		{
			m_clGrid_IO_Out.SetItemBkColor((rowNo) , 2, GRID_COLOR_WHITE);
		}
	}
	for(int j=32; j<64; j++)
	{
		rowNo = j + 1;

		flag	= curOutDioByte[2][(j-32)/8] & (0x01<<(j-32)%8);
		if(flag)
		{
			m_clGrid_IO_Out.SetItemBkColor((rowNo) , 2, GRID_COLOR_DIO_OUT);
		}
		else
		{
			m_clGrid_IO_Out.SetItemBkColor((rowNo) , 2, GRID_COLOR_WHITE);
		}
	}
	m_clGrid_IO_Out.Invalidate();
}

BOOL CIoDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if ( m_bShowFlag == true )
	{
		m_clGrid_IO_In.GetWindowRect(&m_rcGridDioIn);

		if ( m_rcGridDioIn.PtInRect(pt) == TRUE )
		{
			if ( zDelta <= 0 )   //! (-) 아래쪽
			{
				DWORD dwTemp = SB_LINEDOWN;
				m_clGrid_IO_In.SendMessage(WM_VSCROLL, dwTemp, NULL);
			}
			else			     //! (+) 윗쪽
			{
				DWORD dwTemp = SB_LINEUP;
				m_clGrid_IO_In.SendMessage(WM_VSCROLL, dwTemp, NULL);
			}
		}


		m_clGrid_IO_Out.GetWindowRect(&m_rcGridDioOut);

		if ( m_rcGridDioOut.PtInRect(pt) == TRUE )
		{
			if ( zDelta <= 0 )   //! (-) 아래쪽
			{
				DWORD dwTemp = SB_LINEDOWN;
				m_clGrid_IO_Out.SendMessage(WM_VSCROLL, dwTemp, NULL);
			}
			else			     //! (+) 윗쪽
			{
				DWORD dwTemp = SB_LINEUP;
				m_clGrid_IO_Out.SendMessage(WM_VSCROLL, dwTemp, NULL);
			}
		}
	}

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}

