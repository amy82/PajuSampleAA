// SfrSpec.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ChartSetDlg.h"

// CChartSetDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CChartSetDlg, CDialogEx)

CChartSetDlg::CChartSetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChartSetDlg::IDD, pParent)
	, m_iSpecDisp(1)
{
	mGridFixRow = 21;
	sfrRow = 0;
	sfrCol = 0;
	roiRow = 0;
	roiCol = 0;

}

CChartSetDlg::~CChartSetDlg()
{
}

void CChartSetDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_STATIC_TITLE, m_LabelTitle);
	//DDX_Control(pDX, IDC_LIMIT_04F_BALANCE,		m_Limit_04F_Balance);
	DDX_Control(pDX, IDC_COMBO_CHART_COUNT, m_ComboChartCount);
	DDX_Control(pDX, IDC_COMBO_CHART_TYPE, m_ComboChartType);
	DDX_Control(pDX, IDC_COMBO_CHART_FIND, m_ComboChartFind);
	DDX_Control(pDX, IDC_COMBO_DEMOSAIC, m_ComboDemosaic);
	
	//AA ROI

	
	
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CChartSetDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CChartSetDlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_SAVE, &CChartSetDlg::OnBnClickedButtonMotorSave)
	ON_STN_CLICKED(IDC_LIMIT_04F_BALANCE, &CChartSetDlg::OnStnClickedLimit04fBalance)
	ON_NOTIFY(NM_CLICK, IDC_STATIC_CHART_SET_GRID, &CChartSetDlg::OnClickedGridSfr)
	ON_NOTIFY(NM_CLICK, IDC_STATIC_CHART_AA_ROI_GRID, &CChartSetDlg::OnClickedGridRoi)
	
END_MESSAGE_MAP()


// CChartSetDlg 메시지 처리기입니다.


void CChartSetDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
	if (bShow)
	{
		ShowGridCtrl_ChartSet();
		FnTiltCal();
	}
}


BOOL CChartSetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	this->CenterWindow();
	mLocalChartCount = model.mGlobalChartCount;

	setInterface();
	InitGridCtrl_ChartSet();
	InitGridCtrl_AARoiSet();
	FnTiltCal();
	return TRUE;
}

void CChartSetDlg::FnTiltCal()
{
	TCHAR szLog[SIZE_OF_1K];
	int i = 0;
	int j = 0;
	int count = 0;
	int mArrCount = 0;
	int mRoiIndex = 0;	//틸트 계산에 들어가는 roi 패턴 번호
	_stprintf_s(szLog, SIZE_OF_1K, _T("[ROI]Tilt Cal Start")); 
	theApp.MainDlg->putListLog(szLog);
	for (i = 0; i < model.mGlobalChartCount; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (i == model.sfrElem.m_AATiltRoiIndex[0] || 
				i == model.sfrElem.m_AATiltRoiIndex[1] || i == model.sfrElem.m_AATiltRoiIndex[2] || 
				i == model.sfrElem.m_AATiltRoiIndex[3] || i == model.sfrElem.m_AATiltRoiIndex[4])
			{
				if (model.sfrElem.m_AATiltCalRoi[i][j] == 1)
				{
					Task.SFR.nTiltCalIndex[mArrCount] = count;
#ifdef _DEBUG
					_stprintf_s(szLog, SIZE_OF_1K, _T("[ROI:%d]Tilt Cal Index[%d/%d]") , i, mArrCount, Task.SFR.nTiltCalIndex[mArrCount]);
					theApp.MainDlg->putListLog(szLog);
#endif
					mArrCount++;
				}
				
				
			}
			if (model.sfrElem.m_SfrTestUse[i][j] == 1)
			{
				count++;
			}
			//
		}
	}
}
void CChartSetDlg::RoiGridReset(int nRow , int index)
{
	//좌측 측정에 체크 안돼있으면 AA 선택 안되게 해야된다.
	int i = 0;
	CGridCellCheck* kk;
	BOOL bRtn = FALSE;
	for (i = 0; i < 4; i++)
	{
		m_clGridChartAARoi.SetCellType(nRow, i + 1, RUNTIME_CLASS(CGridCell));
		m_clGridChartAARoi.SetItemState(nRow, i + 1, m_clGridChartAARoi.GetItemState(nRow, i + 1) & GVIS_READONLY);
		m_clGridChartAARoi.Invalidate();
		if (model.sfrElem.m_SfrTestUse[index][i] == 1)
		{
			bRtn = m_clGridChartAARoi.SetCellType(nRow, i + 1, RUNTIME_CLASS(CGridCellCheck));
			if (bRtn)
			{
				kk = (CGridCellCheck*)(m_clGridChartAARoi.GetCell(nRow, i + 1));
				if (model.sfrElem.m_AATiltCalRoi[index][i] == 1)
				{
					kk->SetCheck(TRUE);
					m_clGridChartAARoi.SetItemText(nRow, i + 1, _T("On"));
				}
				else
				{
					kk->SetCheck(FALSE);
					m_clGridChartAARoi.SetItemText(nRow, i + 1, _T(""));//_T("Off"));
				}
				m_clGridChartAARoi.SetItemBkColor(nRow, i + 1, RGB_COLOR_WHITE);
			}
		}
		else
		{
			//클릭안되게 수정
			
			m_clGridChartAARoi.SetItemText(nRow, i + 1, _T("X"));
			m_clGridChartAARoi.SetItemBkColor(nRow, i + 1, RGB_COLOR_BLACK); 
		}
		m_clGridChartAARoi.Invalidate();
	}

}
void CChartSetDlg::OnClickedGridRoi(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
	CString celData = "";
	int nRow = 0;
	int nCol = 0;
	int setIndex = 0;
	nRow = pNMGridView->iRow;
	nCol = pNMGridView->iColumn;
	int mTempRow = 0;
	if (nRow > 0 && nCol == 0)
	{
		mTempRow = atoi(m_clGridChartAARoi.GetItemText(nRow, nCol));
		//nRow = 1, 2, 3, 4
		switch (nRow)
		{
		case 1:
			//Center
			break;
		case 2:	//ROI 1(TL , T)
			//1 or 5
			if (mTempRow == nRow - 1)
			{
				setIndex = 5;
				m_clGridChartAARoi.SetItemText(nRow, nCol, setIndex);
			}
			else
			{
				setIndex = nRow - 1;
				m_clGridChartAARoi.SetItemText(nRow, nCol, setIndex);
			}
			RoiGridReset(nRow, setIndex);
			break;
		case 3://ROI 1(TR , B)
			//2 or 6
			if (mTempRow == nRow - 1)
			{
				setIndex = 6;
				m_clGridChartAARoi.SetItemText(nRow, nCol, setIndex);
			}
			else
			{
				setIndex = nRow - 1;
				m_clGridChartAARoi.SetItemText(nRow, nCol, setIndex);
			}
			RoiGridReset(nRow, setIndex);
			break;
		case 4://ROI 1(BL , L)
			//3 or 7
			if (mTempRow == nRow - 1)
			{
				setIndex = 7;
				m_clGridChartAARoi.SetItemText(nRow, nCol, setIndex);
			}
			else
			{
				setIndex = nRow - 1;
				m_clGridChartAARoi.SetItemText(nRow, nCol, setIndex);
			}
			RoiGridReset(nRow, setIndex);
			break;
		case 5://ROI 1(BR , R)
			//4 or 8
			if (mTempRow == nRow - 1)
			{
				setIndex = 8;
				m_clGridChartAARoi.SetItemText(nRow, nCol, setIndex);
			}
			else
			{
				setIndex = nRow - 1;
				m_clGridChartAARoi.SetItemText(nRow, nCol, setIndex);
			}
			RoiGridReset(nRow, setIndex);
			break;
		}
		m_clGridChartAARoi.Invalidate();
	}else if ((nRow >= 1 && nRow < roiRow) && nCol >= 1)
	{
		mTempRow = atoi(m_clGridChartAARoi.GetItemText(nRow, 0));
		if (model.sfrElem.m_SfrTestUse[mTempRow][nCol - 1] == 1)
		{
			CGridCellCheck* kk;
			kk = (CGridCellCheck*)(m_clGridChartAARoi.GetCell(nRow, nCol));
			kk->SetCheck(!kk->GetCheck());
			if (kk->GetCheck() == TRUE)
			{
				m_clGridChartAARoi.SetItemText(nRow, nCol, _T("On"));
			}
			else
			{
				m_clGridChartAARoi.SetItemText(nRow, nCol, _T(""));//_T("Off"));
			}
			m_clGridChartAARoi.Invalidate();
		}
		
	}
}



void CChartSetDlg::OnClickedGridSfr(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
	CString celData="";
	int nRow = 0;
	int nCol = 0;

	nRow = pNMGridView->iRow;
	nCol = pNMGridView->iColumn;

	if (nRow > mLocalChartCount)
	{
		return;
	}
	if ((nRow >= 1 && nRow < sfrRow) && nCol >= 1)
	{
		//if ((nRow >= 1 && nRow < sfrRow) && nCol >= 1)
		//{
		//	//checkBox
		//	return;
		//}
		CGridCellCheck* kk;
		kk = (CGridCellCheck*)(m_clGridChartSetSpec.GetCell(nRow, nCol));
		kk->SetCheck(!kk->GetCheck());
		if (kk->GetCheck() == TRUE)
		{
			m_clGridChartSetSpec.SetItemText(nRow, nCol, _T("On"));
		}
		else
		{
			m_clGridChartSetSpec.SetItemText(nRow, nCol, _T(""));//_T("Off"));
		}
		m_clGridChartSetSpec.Invalidate();
		/*CString celData;
		celData = m_clGridChartSetSpec.GetItemText(nRow, nCol);


		CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
		if(dlg.DoModal() == IDOK)
		{
			CString curStr = dlg.GetstrNum();

			double iVal = atof(curStr);
			celData.Format("%.03f", iVal);

			m_clGridChartSetSpec.SetItemText(nRow, nCol, celData);
			m_clGridChartSetSpec.Invalidate();
		}*/
	}
}

void CChartSetDlg::GetGridCtrl_ChartSet()
{
	//
	int i = 0;
	int j = 0;
	model.mGlobalSmallChartCount = 0;
	CGridCellCheck* kk;
	//---------------------------------------------------------------------
	//
	//SFR 측정 유무
	//
	//---------------------------------------------------------------------
	for (i = 0; i < mLocalChartCount; i++)
	{
		memset(model.sfrElem.m_AATiltCalRoi[i], 0, sizeof(model.sfrElem.m_AATiltCalRoi[i]));
		for (j = 0; j < 4; j++)
		{
			kk = (CGridCellCheck*)(m_clGridChartSetSpec.GetCell(i + 1, j + 1));
			if (kk->GetCheck() == TRUE)
			{
				model.mGlobalSmallChartCount++;
				model.sfrElem.m_SfrTestUse[i][j] = 1;
			}
			else
			{
				model.sfrElem.m_SfrTestUse[i][j] = 0;
			}
		}
	}
	//---------------------------------------------------------------------
	//
	//AA 틸트 계산 영역
	//
	//---------------------------------------------------------------------
	int roiTemp = 0;
	for (i = 0; i < 5; i++)
	{
		roiTemp = atoi(m_clGridChartAARoi.GetItemText(i + 1, 0));
		model.sfrElem.m_AATiltRoiIndex[i] = roiTemp;

		for (j = 0; j < 4; j++)
		{
			kk = (CGridCellCheck*)(m_clGridChartAARoi.GetCell(i + 1, j + 1));
			if (kk->GetCheck() == TRUE)
			{
				model.sfrElem.m_AATiltCalRoi[roiTemp][j] = 1;
			}
			else
			{
				model.sfrElem.m_AATiltCalRoi[roiTemp][j] = 0;
			}
		}
	}
	//---------------------------------------------------------------------
	//
	//측정 영역 개수 , 틸트 계산 타입설정
	//
	//---------------------------------------------------------------------
	model.mGlobalChartCount = m_ComboChartCount.GetCurSel() + 1 + 4;		//패턴 개수
	model.mGlobalChartType = m_ComboChartType.GetCurSel();					//개별 roi 개수
	model.mGlobalChartFind = m_ComboChartFind.GetCurSel();					//패턴 찾는 방식 0 = 패턴
	
	mLocalChartCount = model.mGlobalChartCount;

	model.m_dDemosaic = m_ComboDemosaic.GetCurSel();
}
void CChartSetDlg::ShowGridCtrl_ChartSet(int nMode)
{
	int i = 0;
	int j = 0;
	CString tmpStr="";
	CGridCellCheck* kk;
	//
	//
	//Grid 사이즈 설정
	CRect rect;
	CWnd *pWnd = (CWnd*)GetDlgItem(IDC_STATIC_CHART_SET_GRID);
	sfrRow = mGridFixRow;// mLocalChartCount + 1;
	sfrCol = 5;	//title , l , r, t , b
	int margin = 4;
	int gridHeight = 25;
	int gridWidth1 = 100;
	int gridWidth2 = 60;
	int gridWidth3 = 60;
	int gridWidth4 = 60;
	int gridWidth5 = 60;
	//if (sfrRow < mGridFixRow)
	//{
	//	sfrRow = mGridFixRow;	//칸 채우기위해
	//							//marginx = 4;
	//}
	//
	model.mGlobalSmallChartCount = 0;
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);


	CString specStr;
	for (i = 0; i < sfrRow; i++)
	{
		m_clGridChartSetSpec.SetRowHeight(i, gridHeight);
		//
		if (i == 0)
		{
			specStr.Format(_T("[%d]%s"), i, pszXtype[0]);
			m_clGridChartSetSpec.SetItemText(1 + i, 0, specStr);
		}
		else
		{
			
			if (model.mGlobalChartType == 0)
			{
				//x자형 차트
				//CENTER , LT , RT , BL , BR
				specStr.Format(_T("[%d]%s"), i, pszXtype[(i - 1) % 4 + 1]);
			}
			else
			{
				//+ 자트 adas wide 광각 차트
				//CENTER, T , B . L, R
				specStr.Format(_T("[%d]%s"), i, pszPlustype[(i - 1) % 4 + 1]);
			}
			m_clGridChartSetSpec.SetItemText(1 + i, 0, specStr);
		}
		
		//modelmGlobalChartType
		//
		for (j = 0; j < 5; j++)
		{
			m_clGridChartSetSpec.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			if (i > 0 &&j > 0)
			{
				if (i <= mLocalChartCount)
				{
					m_clGridChartSetSpec.SetCellType(i, j, RUNTIME_CLASS(CGridCellCheck));
					kk = (CGridCellCheck*)(m_clGridChartSetSpec.GetCell(i, j));
					if (model.sfrElem.m_SfrTestUse[i - 1][j - 1] == 1)
					{
						model.mGlobalSmallChartCount++;
						m_clGridChartSetSpec.SetItemText(i, j, _T("On"));
						kk->SetCheck(TRUE);
					}
					else
					{
						m_clGridChartSetSpec.SetItemText(i, j, _T(""));//_T("Off"));
						kk->SetCheck(FALSE);
					}
				}
				else
				{
					m_clGridChartSetSpec.SetCellType(i, j, RUNTIME_CLASS(CGridCell));
					m_clGridChartSetSpec.SetItemText(i, j, _T(""));
				}
				
				m_clGridChartSetSpec.SetItemState(i, j, m_clGridChartSetSpec.GetItemState(i, j) & GVIS_READONLY);
				
			}
			
		}
	}
	CString sRoi = _T("");
	int roiTemp = 0;
	for (i = 0; i < 5; i++)
	{
		roiTemp = model.sfrElem.m_AATiltRoiIndex[i];
		m_clGridChartAARoi.SetItemText(1 + i, 0, roiTemp);		//AA ROI 영역 설정
		
		for (j = 0; j < 4; j++)
		{
			RoiGridReset(i + 1, roiTemp);						//AA틸트 계산 영역 설정
		}
	}
	m_clGridChartAARoi.Invalidate();


	//
	m_ComboChartCount.SetCurSel(model.mGlobalChartCount - 1 - 4);		//CHART COUNT 패턴 개수
	m_ComboChartType.SetCurSel(model.mGlobalChartType);					//틸트 계산 타입 , X , +
	m_ComboChartFind.SetCurSel(model.mGlobalChartFind);					//차트 찾는 방식 , X , +

	m_ComboDemosaic.SetCurSel(model.m_dDemosaic);
	//model. = .GetCurSel();

	sRoi.Empty();
	tmpStr.Empty();
	specStr.Empty();
	m_clGridChartSetSpec.Invalidate();
}

void CChartSetDlg::InitGridCtrl_ChartSet()
{
	CRect rect;
	CWnd *pWnd= (CWnd*)GetDlgItem(IDC_STATIC_CHART_SET_GRID);
	sfrRow = mLocalChartCount + 1;
	sfrCol = 5;
	int marginX = 20;
	int marginY = 4;
	int gridHeight = 25;
	int gridWidth1 = 90;
	int gridWidth2 = 50;
	int gridWidth3 = 50;
	int gridWidth4 = 50;
	int gridWidth5 = 50;
	int i = 0;
	int j = 0;


	//
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = gridWidth1+gridWidth2+gridWidth3+gridWidth4+ gridWidth5 + marginX;
	//rect.bottom = (gridHeight * mGridFixRow) + marginY;
	rect.bottom = (gridHeight * 15) + marginY;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.

	GetDlgItem(IDC_STATIC_CHART_SET_GRID)->GetWindowRect(rect);
	ScreenToClient(rect);//ScreenToClient(rect);
	m_clGridChartSetSpec.Create(rect, this, IDC_STATIC_CHART_SET_GRID, WS_TABSTOP | WS_VISIBLE);

	m_clGridChartSetSpec.SetTextBkColor(GRID_COLOR_WHITE);
	m_clGridChartSetSpec.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridChartSetSpec.SetFixedTextColor(GRID_COLOR_WHITE);
	m_clGridChartSetSpec.SetReference_Setting();
	m_clGridChartSetSpec.EnableSelection(FALSE);
	m_clGridChartSetSpec.SetRowCount(mGridFixRow);
	m_clGridChartSetSpec.SetColumnCount(sfrCol);
	m_clGridChartSetSpec.SetFixedRowCount(1);
	m_clGridChartSetSpec.SetFixedColumnCount(1);
	m_clGridChartSetSpec.SetEditable(FALSE);
	m_clGridChartSetSpec.SetItemText(0, 0, "ROI");
	m_clGridChartSetSpec.SetItemText(0, 1, "Top");
	m_clGridChartSetSpec.SetItemText(0, 2, "Bottom");
	m_clGridChartSetSpec.SetItemText(0, 3, "Left");
	m_clGridChartSetSpec.SetItemText(0, 4, "Rigth");
	m_clGridChartSetSpec.AutoSize();


	CString specStr;
	 
	for (i = 0; i < mGridFixRow; i++)
	{
		m_clGridChartSetSpec.SetRowHeight(i, gridHeight);
		if (i == 0)
		{
			specStr.Format(_T("[%d]Center"), i);
		}
		else
		{
			specStr.Format(_T("[%d]"), i);
		}
		
		m_clGridChartSetSpec.SetItemText(1 + i, 0, specStr);
		for (j = 0; j < sfrCol; j++)
		{
			m_clGridChartSetSpec.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridChartSetSpec.SetColumnWidth(j, gridWidth1);
					
				}else
				{
					m_clGridChartSetSpec.SetColumnWidth(j, gridWidth2);
				}
			}
			else
			{
				if (j > 0 && i <= mLocalChartCount)
				{
					
					m_clGridChartSetSpec.SetItemText(i, j, _T(""));//_T("Off"));
					m_clGridChartSetSpec.SetCellType(i, j, RUNTIME_CLASS(CGridCellCheck));
					m_clGridChartSetSpec.SetItemState(i, j, m_clGridChartSetSpec.GetItemState(i, j) & GVIS_READONLY);
				}
			}
		}
	}
	specStr.Empty();
	m_clGridChartSetSpec.Invalidate();
}

void CChartSetDlg::setInterface()
{

	m_LabelTitle
		.SetBkColor(GRID_COLOR_GREEN)
		.SetTextColor(M_COLOR_BLACK)
		.SetFontBold(TRUE)
		.SetFontSize(21)
		.SetText("Chart Set");




	//총 24개
	m_ComboDemosaic.ResetContent();
	m_ComboDemosaic.AddString(_T("DEMOSAIC_NONE"));
	m_ComboDemosaic.AddString(_T("GRADIENT"));
	m_ComboDemosaic.AddString(_T("BL33"));
	m_ComboDemosaic.AddString(_T("OPENCV_VNG"));
	m_ComboDemosaic.AddString(_T("VNG"));
	m_ComboDemosaic.AddString(_T("GR_ONLY"));
	m_ComboDemosaic.AddString(_T("GB_ONLY"));
	m_ComboDemosaic.AddString(_T("GBTF"));
	m_ComboDemosaic.AddString(_T("BLLC"));
	m_ComboDemosaic.AddString(_T("RESIDUAL"));
	m_ComboDemosaic.AddString(_T("BAYER_Y"));
	m_ComboDemosaic.AddString(_T("GRADIENT_RESIDUAL"));
	m_ComboDemosaic.AddString(_T("GBTF_RESIDUAL"));
	m_ComboDemosaic.AddString(_T("RESIDUAL_RESIDUAL"));
	m_ComboDemosaic.AddString(_T("BL33_RESIDUAL"));
	m_ComboDemosaic.AddString(_T("IR_ONLY"));
	m_ComboDemosaic.AddString(_T("GRADIENT_G_ONLY"));
	m_ComboDemosaic.AddString(_T("GBTF_G_ONLY"));
	m_ComboDemosaic.AddString(_T("RESIDUAL_G_ONLY"));
	m_ComboDemosaic.AddString(_T("BL33_G_ONLY"));
	m_ComboDemosaic.AddString(_T("GRADIENT_IR_ONLY"));
	m_ComboDemosaic.AddString(_T("GBTF_IR_ONLY"));
	m_ComboDemosaic.AddString(_T("RESIDUAL_IR_ONLY"));
	m_ComboDemosaic.AddString(_T("BL33_IR_ONLY"));

	m_ComboDemosaic.SetCurSel(0);
}


void CChartSetDlg::OnOK()	{ }

void CChartSetDlg::OnCancel()	{ }


void CChartSetDlg::OnBnClickedButtonClose()
{
	this->ShowWindow(SW_HIDE);
}


void CChartSetDlg::OnBnClickedButtonMotorSave()
{
	int i = 0;
	int j = 0;
	bool bRtn = false;
	//AA 영역이 하나도 체크가 안돼있으면 저장 막아야된다.
	int roiTemp = 0;
	CGridCellCheck* kk;
	for (i = 0; i < 5; i++)
	{
		bRtn = false;
		for (j = 0; j < 4; j++)
		{
			kk = (CGridCellCheck*)(m_clGridChartAARoi.GetCell(i + 1, j + 1));
			if (kk->GetCheck() == TRUE)
			{
				bRtn = true;
			}
		}
		if (bRtn == false)
		{
			GetGridCtrl_ChartSet();
			ShowGridCtrl_ChartSet();
			errMsg2(Task.AutoFlag, _T("틸트 계산 영역 1개 이상 선택해주세요"));
			return;
		}
	}
	
	//
	GetGridCtrl_ChartSet();

	model.ChartSave();
	model.ChartLoad();

	ShowGridCtrl_ChartSet();
	FnTiltCal();
	theApp.MainDlg->ChartRoiReset();

	//bool passFlag = password.m_bFlag;

	//if(passFlag == false)
	//{
	//	CString strTemp="";
	//	CKeyPadDlg keyDlg;

	//	keyDlg.m_strKeyPad.Format("Password를 입력하세요.");	//"Password를 입력하세요."

	//	if (keyDlg.DoModal()==IDOK)
	//	{
	//		strTemp = keyDlg.GetstrKeypad();

	//		passFlag = strTemp.CompareNoCase(password.m_szPassword) ? false : true; 
	//		if(passFlag)
	//		{
	//			password.m_bFlag = true;
	//		}
	//		else
	//		{
	//			sLangChange.LoadStringA(IDS_STRING891);
	//			errMsg2(Task.AutoFlag, sLangChange);//"Password를 잘 못 입력했습니다."
	//			return;
	//		}
	//	}
	//	else
	//	{
	//		return;
	//	} 
	//}

	

}

void CChartSetDlg::InitGridCtrl_AARoiSet()
{
	CRect rect;
	CWnd *pWnd = (CWnd*)GetDlgItem(IDC_STATIC_CHART_AA_ROI_GRID);
	roiRow = 6;
	roiCol = 5;
	int margin = 4;
	int gridHeight = 25;
	int gridWidth1 = 70;
	int gridWidth2 = 50;
	int gridWidth3 = 50;
	int gridWidth4 = 50;
	int gridWidth5 = 50;
	int i = 0;
	int j = 0;


	//
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = gridWidth1 + gridWidth2 + gridWidth3 + gridWidth4 + gridWidth5 + margin;
	rect.bottom = (gridHeight*roiRow) + margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.

	GetDlgItem(IDC_STATIC_CHART_AA_ROI_GRID)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGridChartAARoi.Create(rect, this, IDC_STATIC_CHART_AA_ROI_GRID, WS_TABSTOP | WS_VISIBLE);


	m_clGridChartAARoi.SetTextBkColor(GRID_COLOR_WHITE);
	m_clGridChartAARoi.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridChartAARoi.SetFixedTextColor(GRID_COLOR_WHITE);
	m_clGridChartAARoi.SetReference_Setting();
	m_clGridChartAARoi.EnableSelection(FALSE);
	m_clGridChartAARoi.SetRowCount(roiRow);
	m_clGridChartAARoi.SetColumnCount(roiCol);
	m_clGridChartAARoi.SetFixedRowCount(1);
	//m_clGridChartAARoi.SetFixedColumnCount(1);
	m_clGridChartAARoi.SetEditable(FALSE);

	//m_clGridChartAARoi.SetVirtualMode(TRUE);
	m_clGridChartAARoi.SetItemText(0, 0, "AA ROI");
	m_clGridChartAARoi.SetItemText(0, 1, "Top");
	m_clGridChartAARoi.SetItemText(0, 2, "Bottom");
	m_clGridChartAARoi.SetItemText(0, 3, "Left");
	m_clGridChartAARoi.SetItemText(0, 4, "Rigth");
	m_clGridChartAARoi.AutoSize();


	CString specStr;

	for (i = 0; i < roiRow; i++)
	{
		m_clGridChartAARoi.SetRowHeight(i, gridHeight);
		specStr.Format(_T("%d"), model.sfrElem.m_AATiltRoiIndex[i]);

		m_clGridChartAARoi.SetItemText(1 + i, 0, specStr);
		for (j = 0; j < roiCol; j++)
		{
			m_clGridChartAARoi.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridChartAARoi.SetColumnWidth(j, gridWidth1);
				}
				else
				{
					m_clGridChartAARoi.SetColumnWidth(j, gridWidth2);
				}
				
			}
			else
			{
				if (j > 0 && i <= mLocalChartCount)
				{
					m_clGridChartAARoi.SetItemText(i, j, _T(""));//_T("Off"));
					m_clGridChartAARoi.SetCellType(i, j, RUNTIME_CLASS(CGridCellCheck));
					m_clGridChartAARoi.SetItemState(i, j, m_clGridChartAARoi.GetItemState(i, j) & GVIS_READONLY);
				}
			}
		}
	}
	specStr.Empty();
	m_clGridChartAARoi.Invalidate();
}

BEGIN_EVENTSINK_MAP(CChartSetDlg, CDialogEx)

END_EVENTSINK_MAP()

void CChartSetDlg::OnStnClickedLimit04fBalance()
{
	/*CString celData;
	m_Limit_04F_Balance.GetWindowText(celData);
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());
		celData.Format("%.03f", (f_num));
		m_Limit_04F_Balance.SetText(celData);
	}*/
}


