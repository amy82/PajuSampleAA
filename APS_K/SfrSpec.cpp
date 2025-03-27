// SfrSpec.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SfrSpec.h"

// CSfrSpec 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSfrSpec, CDialogEx)

CSfrSpec::CSfrSpec(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSfrSpec::IDD, pParent)
	, m_iSpecDisp(1)
{

}

CSfrSpec::~CSfrSpec()
{
}

void CSfrSpec::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_STATIC_TITLE, m_LabelTitle);
	//DDX_Control(pDX, IDC_MSFLEXGRID_SFR_SPEC, m_gridSfrSpec);
	//DDX_Control(pDX, IDC_MSFLEXGRID_SFR_SPEC2, m_gridSfrSpec2);

	DDX_Control(pDX, IDC_LIMIT_04F_BALANCE,		m_Limit_04F_Balance);
	DDX_Control(pDX, IDC_LIMIT_07F_BALANCE,		m_Limit_07F_Balance);
	DDX_Control(pDX, IDC_LIMIT_OC_ALIGN,		m_Limit_OC);
	DDX_Control(pDX, IDC_LIMIT_OC_ALIGN_TH,		m_Limit_OC_TH);
	DDX_Control(pDX, IDC_LIMIT_MAX_LIMIT,		m_Limit_Max_Limit);
	
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSfrSpec, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CSfrSpec::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_SAVE, &CSfrSpec::OnBnClickedButtonMotorSave)
	ON_STN_CLICKED(IDC_LIMIT_OC_ALIGN, &CSfrSpec::OnStnClickedLimitOcAlign)
	ON_STN_CLICKED(IDC_LIMIT_OC_ALIGN_TH, &CSfrSpec::OnStnClickedLimitOcAlignTh)
	ON_STN_CLICKED(IDC_LIMIT_04F_BALANCE, &CSfrSpec::OnStnClickedLimit04fBalance)
	ON_STN_CLICKED(IDC_LIMIT_07F_BALANCE, &CSfrSpec::OnStnClickedLimit07fBalance)

	ON_NOTIFY(NM_CLICK, IDC_STATIC_SFRSPEC_GRID, &CSfrSpec::OnClickedGridSfr)
	ON_NOTIFY(NM_CLICK, IDC_STATIC_OCSPEC_GRID, &CSfrSpec::OnClickedGridOc)
	
	ON_STN_CLICKED(IDC_LIMIT_MAX_LIMIT, &CSfrSpec::OnStnClickedLimitMaxLimit)
END_MESSAGE_MAP()


// CSfrSpec 메시지 처리기입니다.


void CSfrSpec::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
	if (bShow)
	{
		sysData.Load();
		MandoSfrSpec.NewSfrLoad();// load();
		ShowGridCtrl_Sfr();
	}
}


BOOL CSfrSpec::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	setInterface();
	InitGridCtrl_Oc();
	InitGridCtrl_Sfr();
	return TRUE;
}
void CSfrSpec::OnClickedGridOc(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
	CString szData = _T("");
	CString celData="";
	int nRow, nCol;

	nRow = pNMGridView->iRow;
	nCol = pNMGridView->iColumn;

	if ((nRow >= 1 && nRow < ocRow) && nCol >= 1)
	{
		CString celData;
		celData = m_clGridOcSpec.GetItemText(nRow, nCol); 


		CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
		if(dlg.DoModal() == IDOK)
		{
			CString curStr = dlg.GetstrNum();
			double iVal = atof(curStr);
			//if(iVal<0)		iVal = 0;
			//if(iVal>60)			iVal = 60;

			if (nRow == 10)		//deltaAlgorithm
			{
				if (iVal<0)		iVal = 0;
				if (iVal>1)			iVal = 1;
			}
			if (nRow == 13)		//sfrAlgorithm
			{
				if (iVal<0)		iVal = 0;
				if (iVal>5)			iVal = 5;
			}
			if (nRow == 14)		//sfrAlgorithmMethod
			{
				if (iVal<0)		iVal = 0;
				if (iVal>1)			iVal = 1;
			}
			if (nRow == 15)		//Frequency
			{
				if (iVal<0)		iVal = 0;
				if (iVal>2)			iVal = 2;
			}
			celData.Format("%.03f", iVal);
			m_clGridOcSpec.SetItemText(nRow, nCol, celData);
			m_clGridOcSpec.Invalidate();
		}
	}
}
void CSfrSpec::OnClickedGridSfr(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
	CString szData = _T("");
	CString celData="";
	int nRow, nCol;

	nRow = pNMGridView->iRow;
	nCol = pNMGridView->iColumn;
	if (nRow > model.mGlobalSmallChartCount)//model.mGlobalChartCount)
	{
		return;
	}
	if ((nRow >= 1 && nRow < sfrSpecRow) && nCol >= 1)
	{
		CString celData;
		celData = m_clGridSfrSpec.GetItemText(nRow, nCol); 


		CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
		if(dlg.DoModal() == IDOK)
		{
			CString curStr = dlg.GetstrNum();
			double iVal = atof(curStr);
			//if(iVal<0)		iVal = 0;
			//if(iVal>60)			iVal = 60;
			celData.Format("%.03f", iVal);
			m_clGridSfrSpec.SetItemText(nRow, nCol, celData);
			m_clGridSfrSpec.Invalidate();
		}
	}
}

void CSfrSpec::ShowGridCtrl_Sfr()
{
	CString tmpStr="";
	
	//설정 패턴 개수만큼만 보여줘라
	for (int iNo = 0; iNo < model.mGlobalSmallChartCount; iNo++)	//for( int iNo = 0; iNo < MTF_INSP_CNT; iNo++ )
	{
		tmpStr.Format("%.3f", MandoSfrSpec.dAASFR_Spec[iNo][0]);//uv전
		m_clGridSfrSpec.SetItemText(iNo+1, 1, tmpStr);
		tmpStr.Format("%.3f", MandoSfrSpec.dAASFR_Spec[iNo][1]);//uv후
		m_clGridSfrSpec.SetItemText(iNo+1, 2, tmpStr);
		tmpStr.Format("%.3f", MandoSfrSpec.dAASFR_Spec[iNo][2]);//완제품
		m_clGridSfrSpec.SetItemText(iNo + 1, 3, tmpStr);
	}

	tmpStr.Format("%.03f",  MandoSfrSpec.INSP_AAmode_OC_Max_Spec);
	m_clGridOcSpec.SetItemText(1, 1, tmpStr);
	tmpStr.Format("%.03f", MandoSfrSpec.INSP_AAmode_OC_Min_Spec);
	m_clGridOcSpec.SetItemText(2, 1, tmpStr);
	tmpStr.Format("%.03f", MandoSfrSpec.INSP_Procmode_OC_Max_Spec);
	m_clGridOcSpec.SetItemText(3, 1, tmpStr);
	tmpStr.Format("%.03f", MandoSfrSpec.INSP_Procmode_OC_Min_Spec);
	m_clGridOcSpec.SetItemText(4, 1, tmpStr);
	//tmpStr.Format("%.03f", MandoSfrSpec.Rotation_Spec);
	//m_clGridOcSpec.SetItemText(5, 1, tmpStr);

	tmpStr.Format("%.03f", MandoSfrSpec.INSP_Diff_Spec[0]);
	m_clGridOcSpec.SetItemText(5, 1, tmpStr);

	tmpStr.Format("%.03f", MandoSfrSpec.INSP_Diff_Spec[1]);
	m_clGridOcSpec.SetItemText(6, 1, tmpStr);

	tmpStr.Format("%.03f", MandoSfrSpec.INSP_RIDiff_Spec);
	m_clGridOcSpec.SetItemText(7, 1, tmpStr);

	tmpStr.Format("%.03f", MandoSfrSpec.INSP_Current_Spec);
	m_clGridOcSpec.SetItemText(8, 1, tmpStr);
	tmpStr.Format("%.03f", MandoSfrSpec.INSP_Voltage_Spec);
	m_clGridOcSpec.SetItemText(9, 1, tmpStr);

	tmpStr.Format("%d", MandoSfrSpec.INSP_SfrDeltaAlgorithmType);
	m_clGridOcSpec.SetItemText(10, 1, tmpStr);
	tmpStr.Format("%.03f", MandoSfrSpec.INSP_SfrGamma);
	m_clGridOcSpec.SetItemText(11, 1, tmpStr);
	tmpStr.Format("%.03f", MandoSfrSpec.INSP_SfrMaxEdgeAngle);
	m_clGridOcSpec.SetItemText(12, 1, tmpStr);
	tmpStr.Format("%d", MandoSfrSpec.INSP_SfrAlgorithmType);
	m_clGridOcSpec.SetItemText(13, 1, tmpStr);
	tmpStr.Format("%d", MandoSfrSpec.INSP_SfrAlgorithmMethod);
	m_clGridOcSpec.SetItemText(14, 1, tmpStr);
	tmpStr.Format("%d", MandoSfrSpec.INSP_SfrFrequencyUnit);
	m_clGridOcSpec.SetItemText(15, 1, tmpStr);

	for (int i = 0; i < 4; i++)	//for( int iNo = 0; iNo < MTF_INSP_CNT; iNo++ )
	{
		tmpStr.Format("%.03f", MandoSfrSpec.INSP_SfrInspOffset[i]);
		m_clGridOcSpec.SetItemText(16 + i, 1, tmpStr);
	}

	tmpStr.Format("%.03f", MandoSfrSpec.INSP_OCCenterSpecX);
	m_clGridOcSpec.SetItemText(20, 1, tmpStr);
	tmpStr.Format("%.03f", MandoSfrSpec.INSP_OCCenterSpecY);
	m_clGridOcSpec.SetItemText(21, 1, tmpStr);
	tmpStr.Format("%.03f", MandoSfrSpec.INSP_OCThresholdRatio);
	m_clGridOcSpec.SetItemText(22, 1, tmpStr);
	tmpStr.Format("%d", MandoSfrSpec.INSP_OCRoiCount);
	m_clGridOcSpec.SetItemText(23, 1, tmpStr);
	tmpStr.Format("%d", MandoSfrSpec.INSP_OCEdgeTopMargin);
	m_clGridOcSpec.SetItemText(24, 1, tmpStr);
	tmpStr.Format("%d", MandoSfrSpec.INSP_OCBlockSize);
	m_clGridOcSpec.SetItemText(25, 1, tmpStr);

	for (int i = 0; i < 4; i++)	//for( int iNo = 0; iNo < MTF_INSP_CNT; iNo++ )
	{
		tmpStr.Format("%.03f", MandoSfrSpec.INSP_OCInspOffset[i]);
		m_clGridOcSpec.SetItemText(26 + i, 1, tmpStr);
	}

	tmpStr.Format("%.04f", sysData.m_dOcSpec.x);
	SetDlgItemText(IDC_LIMIT_OC_ALIGN, tmpStr);

	tmpStr.Format("%.04f", sysData.dSpec_OC_Theta);
	SetDlgItemText(IDC_LIMIT_OC_ALIGN_TH, tmpStr);

	tmpStr.Format("%.01f", sysData.dMax_Sfr_Limit);
	SetDlgItemText(IDC_LIMIT_MAX_LIMIT, tmpStr);

	m_clGridSfrSpec.Invalidate();
	m_clGridOcSpec.Invalidate();
	tmpStr.Empty();
}
void CSfrSpec::InitGridCtrl_Sfr()
{
	CRect rect;
	CWnd *pWnd= (CWnd*)GetDlgItem(IDC_STATIC_SFRSPEC_GRID); 
	sfrSpecRow = COMMON_MTF_INSP_CNT + 1;// MTF_INSP_CNT + 1;
	sfrSpecCol = 4;

	int sfrFixRow = 21;
	int marginx = 21;// 4;
	int marginy = 4;
	int gridHeight = 25;
	int gridWidth1 = 100;
	int gridWidth2 = 60;
	int gridWidth3 = 60;
	int gridWidth4 = 60;
	int i = 0;
	int j = 0;
	//
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = gridWidth1+gridWidth2+gridWidth3+gridWidth4  + marginx;
	rect.bottom = (gridHeight*sfrFixRow) + marginy;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.

	GetDlgItem(IDC_STATIC_SFRSPEC_GRID)->GetWindowRect(rect);
	ScreenToClient(rect);//ScreenToClient(rect);
	m_clGridSfrSpec.Create(rect, this, IDC_STATIC_SFRSPEC_GRID, WS_TABSTOP | WS_VISIBLE);

	m_clGridSfrSpec.SetTextBkColor(GRID_COLOR_WHITE);
	m_clGridSfrSpec.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridSfrSpec.SetFixedTextColor(GRID_COLOR_WHITE);
	m_clGridSfrSpec.SetReference_Setting();
	m_clGridSfrSpec.EnableSelection(FALSE);
	m_clGridSfrSpec.SetRowCount(sfrSpecRow);
	m_clGridSfrSpec.SetColumnCount(sfrSpecCol);
	m_clGridSfrSpec.SetFixedRowCount(1);
	m_clGridSfrSpec.SetFixedColumnCount(1);

	m_clGridSfrSpec.SetItemText(0, 0, "Field");
	m_clGridSfrSpec.SetItemText(0, 1, "UV 전");
	m_clGridSfrSpec.SetItemText(0, 2, "UV 후");
	m_clGridSfrSpec.SetItemText(0, 3, "완제품");


	CString specStr;
	for (i = 0; i < COMMON_MTF_INSP_CNT; i++)//for (i = 0; i < MTF_INSP_CNT; i++)
	{
		specStr.Format(_T("[%d] ROI"), i);
		m_clGridSfrSpec.SetItemText(1 + i, 0, specStr);
	}
	specStr.Empty();

	for (i = 0; i < sfrSpecRow; i++)
	{
		m_clGridSfrSpec.SetRowHeight(i, gridHeight);
		
		for (j = 0; j < sfrSpecCol; j++)
		{
			m_clGridSfrSpec.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridSfrSpec.SetColumnWidth(j, gridWidth1);
				}else{
					m_clGridSfrSpec.SetColumnWidth(j, gridWidth2);
				}
			}			
		}
	}
	
	m_clGridSfrSpec.Invalidate();


}
void CSfrSpec::InitGridCtrl_Oc()
{
	//CStatic *staticSize = (CStatic *)GetDlgItem(IDC_STATIC_OCSPEC_GRID);//staticSize->GetClientRect(sRect);
	//Picture Ctr 사이즈 구하기
	CRect rect;
	CWnd *pWnd= (CWnd*)GetDlgItem(IDC_STATIC_OCSPEC_GRID); 
	ocRow = 30;// 8;// 7;// 5;
	ocCol = 2;
	int margin = 4;
	int gridHeight = 28;
	int gridWidth1 = 150;
	int gridWidth2 = 90;
	//
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);
	pWnd->MoveWindow(rect.left, rect.top, (gridWidth1+gridWidth2+margin), (gridHeight*ocRow+margin) );//다이얼로그의 크기와 위치값 조정을 위한 함수.
	
	//=======================================================================
	TCHAR* pszCol[] = {_T("Field"), _T("Spec")};
	int i=0, j=0;

	GetDlgItem(IDC_STATIC_OCSPEC_GRID)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGridOcSpec.Create(rect, this, IDC_STATIC_OCSPEC_GRID, WS_TABSTOP | WS_VISIBLE);

	m_clGridOcSpec.SetTextBkColor(GRID_COLOR_WHITE);
	m_clGridOcSpec.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridOcSpec.SetFixedTextColor(GRID_COLOR_WHITE);
	m_clGridOcSpec.SetReference_Setting();
	m_clGridOcSpec.EnableSelection(FALSE);

	m_clGridOcSpec.SetRowCount(ocRow);
	m_clGridOcSpec.SetColumnCount(ocCol);
	m_clGridOcSpec.SetFixedRowCount(1);
	m_clGridOcSpec.SetFixedColumnCount(1);

	m_clGridOcSpec.SetItemText(0, 0, "Field");
	m_clGridOcSpec.SetItemText(0, 1, "Spec");
	//
	m_clGridOcSpec.SetItemText(1, 0, "AA Mode OC Spec Max");
	m_clGridOcSpec.SetItemText(2, 0, "AA Mode OC Spec Min");
	m_clGridOcSpec.SetItemText(3, 0, "Proc Mode OC Spec Max");
	m_clGridOcSpec.SetItemText(4, 0, "Proc Mode OC Spec Min");
	//
	m_clGridOcSpec.SetItemText(5, 0, "Diff 4F Spec Max");
	m_clGridOcSpec.SetItemText(6, 0, "Diff 7F Spec Max");

	m_clGridOcSpec.SetItemText(7, 0, "RI Spec Max");
	m_clGridOcSpec.SetItemText(8, 0, "Current Spec Max");
	m_clGridOcSpec.SetItemText(9, 0, "Voltage Spec");

	m_clGridOcSpec.SetItemText(10, 0, "Sfr DeltaAlgorithm type");
	m_clGridOcSpec.SetItemText(11, 0, "Sfr Gamma");
	m_clGridOcSpec.SetItemText(12, 0, "Sfr Edge Angle");
	m_clGridOcSpec.SetItemText(13, 0, "Sfr Algorithm type");
	m_clGridOcSpec.SetItemText(14, 0, "Sfr Algorithm Method");
	m_clGridOcSpec.SetItemText(15, 0, "Sfr Frequency Unit");
	m_clGridOcSpec.SetItemText(16, 0, "Sfr Insp.Offset Left");
	m_clGridOcSpec.SetItemText(17, 0, "Sfr Insp.Offset Top");
	m_clGridOcSpec.SetItemText(18, 0, "Sfr Insp.Offset Right");
	m_clGridOcSpec.SetItemText(19, 0, "Sfr Insp.Offset Bottom");

	m_clGridOcSpec.SetItemText(20, 0, "OC Center spec X");
	m_clGridOcSpec.SetItemText(21, 0, "OC Center spec Y");
	m_clGridOcSpec.SetItemText(22, 0, "OC Threshold Ration");
	m_clGridOcSpec.SetItemText(23, 0, "OC ROI Count");
	m_clGridOcSpec.SetItemText(24, 0, "OC Edge Top Margin");
	m_clGridOcSpec.SetItemText(25, 0, "OC Block Size");

	m_clGridOcSpec.SetItemText(26, 0, "OC Insp.Offset Left");
	m_clGridOcSpec.SetItemText(27, 0, "OC Insp.Offset Top");
	m_clGridOcSpec.SetItemText(28, 0, "OC Insp.Offset Right");
	m_clGridOcSpec.SetItemText(29, 0, "OC Insp.Offset Bottom");


	for (i = 0; i < ocRow; i++)
	{
		m_clGridOcSpec.SetRowHeight(i, gridHeight);
		
		for (j = 0; j < ocCol; j++)
		{
			m_clGridOcSpec.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridOcSpec.SetColumnWidth(j, gridWidth1);
				}else{
					m_clGridOcSpec.SetColumnWidth(j, gridWidth2);
				}
			}			
		}
	}
	
	m_clGridOcSpec.Invalidate();
	
}
void CSfrSpec::setInterface()
{
	sLangChange.LoadStringA(IDS_STRING381);
	m_LabelTitle
		.SetBkColor(GRID_COLOR_GREEN)
		.SetTextColor(M_COLOR_BLACK)
		.SetFontBold(TRUE)
		.SetFontSize(21)
		.SetText(sLangChange);	//"Active Align Spec"

	m_Limit_04F_Balance.SetBkColor(M_COLOR_WHITE);
	m_Limit_04F_Balance.SetFontSize(13);
	m_Limit_07F_Balance.SetBkColor(M_COLOR_WHITE);
	m_Limit_07F_Balance.SetFontSize(13);
	m_Limit_OC.SetBkColor(M_COLOR_WHITE);

	m_Limit_Max_Limit.SetBkColor(M_COLOR_WHITE);
	m_Limit_Max_Limit.SetFontSize(13);
	m_Limit_OC.SetFontSize(13);
	m_Limit_OC_TH.SetBkColor(M_COLOR_WHITE);
	m_Limit_OC_TH.SetFontSize(13);
}


void CSfrSpec::OnOK()	{ }

void CSfrSpec::OnCancel()	{ }


void CSfrSpec::OnBnClickedButtonClose()
{
	this->ShowWindow(SW_HIDE);
}


void CSfrSpec::OnBnClickedButtonMotorSave()
{
	bool passFlag = password.m_bFlag;

	if(passFlag == false)
	{
		CString strTemp="";
		CKeyPadDlg keyDlg;

		keyDlg.m_strKeyPad.Format("Password를 입력하세요.");	//"Password를 입력하세요."

		if (keyDlg.DoModal()==IDOK)
		{
			strTemp = keyDlg.GetstrKeypad();

			passFlag = strTemp.CompareNoCase(password.m_szPassword) ? false : true; 
			if(passFlag)
			{
				password.m_bFlag = true;
			}
			else
			{
				sLangChange.LoadStringA(IDS_STRING891);
				errMsg2(Task.AutoFlag, sLangChange);//"Password를 잘 못 입력했습니다."
				return;
			}
		}
		else
		{
			return;
		}
	}


	


	getData();

	sysData.Save();
	sysData.Load();

	MandoSfrSpec.NewSfrSave();// save();
	MandoSfrSpec.NewSfrLoad();//	load();

	ShowGridCtrl_Sfr();//dispData();
}


void CSfrSpec::getData()
{
	//
	CString tmpStr="";
	for (int iNo = 0; iNo < COMMON_MTF_INSP_CNT; iNo++)//for( int iNo = 0; iNo < MTF_INSP_CNT; iNo++ )
	{
		tmpStr = m_clGridSfrSpec.GetItemText(iNo+1, 1);
		MandoSfrSpec.dAASFR_Spec[iNo][0] = atof(tmpStr);

		tmpStr = m_clGridSfrSpec.GetItemText(iNo+1, 2);
		MandoSfrSpec.dAASFR_Spec[iNo][1] = atof(tmpStr);		

		tmpStr = m_clGridSfrSpec.GetItemText(iNo+1, 3);
		MandoSfrSpec.dAASFR_Spec[iNo][2] = atof(tmpStr);		
	}

	tmpStr = m_clGridOcSpec.GetItemText(1,1);				
	MandoSfrSpec.INSP_AAmode_OC_Max_Spec = (float)atof(tmpStr);	

	tmpStr = m_clGridOcSpec.GetItemText(2,1);
	MandoSfrSpec.INSP_AAmode_OC_Min_Spec = (float)atof(tmpStr);

	tmpStr = m_clGridOcSpec.GetItemText(3,1);				
	MandoSfrSpec.INSP_Procmode_OC_Max_Spec = (float)atof(tmpStr);

	tmpStr = m_clGridOcSpec.GetItemText(4,1);				
	MandoSfrSpec.INSP_Procmode_OC_Min_Spec = (float)atof(tmpStr);	

	//tmpStr = m_clGridOcSpec.GetItemText(5, 1);
	//MandoSfrSpec.Rotation_Spec = (float)atof(tmpStr);

	tmpStr = m_clGridOcSpec.GetItemText(5, 1);
	MandoSfrSpec.INSP_Diff_Spec[0] = (float)atof(tmpStr);

	tmpStr = m_clGridOcSpec.GetItemText(6, 1);
	MandoSfrSpec.INSP_Diff_Spec[1] = (float)atof(tmpStr);

	tmpStr = m_clGridOcSpec.GetItemText(7, 1);
	MandoSfrSpec.INSP_RIDiff_Spec = (float)atof(tmpStr);

	tmpStr = m_clGridOcSpec.GetItemText(8, 1);
	MandoSfrSpec.INSP_Current_Spec = (float)atof(tmpStr);

	tmpStr = m_clGridOcSpec.GetItemText(9, 1);
	MandoSfrSpec.INSP_Voltage_Spec = (float)atof(tmpStr);
	
	tmpStr = m_clGridOcSpec.GetItemText(10, 1);
	MandoSfrSpec.INSP_SfrDeltaAlgorithmType = (int)atof(tmpStr);

	tmpStr = m_clGridOcSpec.GetItemText(11, 1);
	MandoSfrSpec.INSP_SfrGamma = (float)atof(tmpStr);

	tmpStr = m_clGridOcSpec.GetItemText(12, 1);
	MandoSfrSpec.INSP_SfrMaxEdgeAngle = (float)atof(tmpStr);

	tmpStr = m_clGridOcSpec.GetItemText(13, 1);
	MandoSfrSpec.INSP_SfrAlgorithmType = (int)atof(tmpStr);

	tmpStr = m_clGridOcSpec.GetItemText(14, 1);
	MandoSfrSpec.INSP_SfrAlgorithmMethod = (int)atof(tmpStr);

	tmpStr = m_clGridOcSpec.GetItemText(15, 1);
	MandoSfrSpec.INSP_SfrFrequencyUnit = (int)atof(tmpStr);

	for (int i = 0; i < 4; i++)
	{
		tmpStr = m_clGridOcSpec.GetItemText(16 + i, 1);
		MandoSfrSpec.INSP_SfrInspOffset[i] = atof(tmpStr);
	}


	tmpStr = m_clGridOcSpec.GetItemText(20, 1);
	MandoSfrSpec.INSP_OCCenterSpecX = (float)atof(tmpStr);

	tmpStr = m_clGridOcSpec.GetItemText(21, 1);
	MandoSfrSpec.INSP_OCCenterSpecY = (float)atof(tmpStr);

	tmpStr = m_clGridOcSpec.GetItemText(22, 1);
	MandoSfrSpec.INSP_OCThresholdRatio = (float)atof(tmpStr);

	tmpStr = m_clGridOcSpec.GetItemText(23, 1);
	MandoSfrSpec.INSP_OCRoiCount = (int)atof(tmpStr);

	tmpStr = m_clGridOcSpec.GetItemText(24, 1);
	MandoSfrSpec.INSP_OCEdgeTopMargin = (int)atof(tmpStr);

	tmpStr = m_clGridOcSpec.GetItemText(25, 1);
	MandoSfrSpec.INSP_OCBlockSize = (int)atof(tmpStr);

	for (int i = 0; i < 4; i++)
	{
		tmpStr = m_clGridOcSpec.GetItemText(26 + i, 1);
		MandoSfrSpec.INSP_OCInspOffset[i] = atof(tmpStr);
	}


	GetDlgItemText(IDC_LIMIT_OC_ALIGN, tmpStr);
	sysData.m_dOcSpec.x = sysData.m_dOcSpec.y = atof(tmpStr);

	GetDlgItemText(IDC_LIMIT_OC_ALIGN_TH, tmpStr);
	sysData.dSpec_OC_Theta = atof(tmpStr);

	GetDlgItemText(IDC_LIMIT_MAX_LIMIT, tmpStr);
	sysData.dMax_Sfr_Limit = atof(tmpStr);
	
	MandoSfrSpec.Insp60Lp = FALSE;
	MandoSfrSpec.Insp67Lp = TRUE;
	MandoSfrSpec.InspCp = FALSE;
}

void CSfrSpec::dispData()
{

}

BEGIN_EVENTSINK_MAP(CSfrSpec, CDialogEx)
	//ON_EVENT(CSfrSpec, IDC_MSFLEXGRID_SFR_SPEC, DISPID_DBLCLICK, CSfrSpec::DblClickMsflexgridSfrSpec, VTS_NONE)
	//ON_EVENT(CSfrSpec, IDC_MSFLEXGRID_SFR_SPEC2, DISPID_DBLCLICK, CSfrSpec::DblClickMsflexgridSfrSpec2, VTS_NONE)
END_EVENTSINK_MAP()


void CSfrSpec::DblClickMsflexgridSfrSpec()
{
	
}

void CSfrSpec::OnStnClickedLimitOcAlign()
{
	CString celData;
	m_Limit_OC.GetWindowText(celData);
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if(f_num < 0.001)		f_num =	0.001f;
		if(f_num > 0.5)			f_num = 0.5f;

		// LHC - 자리수 4자리로 변경.
		celData.Format("%.04f", (f_num));
		m_Limit_OC.SetText(celData);
	}
}


void CSfrSpec::OnStnClickedLimitOcAlignTh()
{
	CString celData;
	m_Limit_OC_TH.GetWindowText(celData);
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if(f_num < 0.001)		f_num =	0.001f;
		if(f_num > 0.5)			f_num = 0.5f;

		celData.Format("%.04f", (f_num));
		m_Limit_OC_TH.SetText(celData);
	}
}



void CSfrSpec::DblClickMsflexgridSfrSpec2()
{
	
}

void CSfrSpec::OnStnClickedLimit04fBalance()
{
	CString celData;
	m_Limit_04F_Balance.GetWindowText(celData);
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());
		celData.Format("%.03f", (f_num));
		m_Limit_04F_Balance.SetText(celData);
	}
}


void CSfrSpec::OnStnClickedLimit07fBalance()
{
	CString celData;
	m_Limit_07F_Balance.GetWindowText(celData);
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());
		celData.Format("%.03f", (f_num));
		m_Limit_07F_Balance.SetText(celData);
	}
}


void CSfrSpec::OnStnClickedLimitMaxLimit()
{
	CString celData;
	m_Limit_Max_Limit.GetWindowText(celData);
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if (dlg.DoModal() == IDOK)
	{
		float f_num = (float)atof(dlg.GetstrNum());

		if (f_num < 0.01)		f_num = 0.01f;
		if (f_num > 0.99)			f_num = 0.99f;

		celData.Format("%.01f", (f_num));
		m_Limit_Max_Limit.SetText(celData);
	}
}
