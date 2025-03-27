// CcdSfrSpecDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CcdSnrColorSensSpecDlg.h"
// CCcdSnrColorSensSpecDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCcdSnrColorSensSpecDlg, CDialogEx)

CCcdSnrColorSensSpecDlg::CCcdSnrColorSensSpecDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCcdSnrColorSensSpecDlg::IDD, pParent)
{
}

CCcdSnrColorSensSpecDlg::~CCcdSnrColorSensSpecDlg()
{
}

void CCcdSnrColorSensSpecDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_TOP_BAR, m_clColorStaticTopBar);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_CENTER_SFR_LIMIT, m_clColorStaticCenterSfrLimit);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_CENTER_SFR_LIMIT_VAL, m_clColorStaticCenterSfrLimitVal);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_LIMIT, m_clColorStaticCornerSfrLimit);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_LIMIT_VAL, m_clColorStaticCornerSfrLimitVal);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_DEVIATION_LIMIT, m_clColorStaticCornerSfrDeviationLimit);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_DEVIATION_LIMIT_VAL, m_clColorStaticCornerSfrDeviationLimitVal);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_OC_XY, m_clColorStaticOCXY);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_OC_XY_VAL, m_clColorStaticOCXYVal);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_OC_TH, m_clColorStaticOCTh);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_OC_TH_VAL, m_clColorStaticOCThVal);
	DDX_Control(pDX, IDC_BUTTON_CCD_SFR_SPEC_SAVE, m_clColorButtonSave);
	DDX_Control(pDX, IDC_BUTTON_CCD_SFR_SPEC_CLOSE, m_clColorButtonClose);
}


BEGIN_MESSAGE_MAP(CCcdSnrColorSensSpecDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_CCD_SNR_SPEC_GRID_SPEC, &CCcdSnrColorSensSpecDlg::OnNMDblClickedSnrSpec)
	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_CCD_COLORSENS_SPEC_GRID_SPEC, &CCcdSnrColorSensSpecDlg::OnNMDblClickedColorSensitivitySpec)
	ON_BN_CLICKED(IDC_BUTTON_CCD_SFR_SPEC_SAVE, &CCcdSnrColorSensSpecDlg::OnBnClickedButtonCcdSfrSpecSave)
	ON_BN_CLICKED(IDC_BUTTON_CCD_SFR_SPEC_CLOSE, &CCcdSnrColorSensSpecDlg::OnBnClickedButtonCcdSfrSpecClose)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_CENTER_SFR_LIMIT_VAL, &CCcdSnrColorSensSpecDlg::OnStnClickedStaticCcdSfrSpecCenterSfrLimitVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_LIMIT_VAL, &CCcdSnrColorSensSpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrLimitVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_DEVIATION_LIMIT_VAL, &CCcdSnrColorSensSpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrDeviationLimitVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_OC_XY_VAL, &CCcdSnrColorSensSpecDlg::OnStnClickedStaticCcdSfrSpecOcXyVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_OC_TH_VAL, &CCcdSnrColorSensSpecDlg::OnStnClickedStaticCcdSfrSpecOcThVal)
END_MESSAGE_MAP()


// CCcdSnrColorSensSpecDlg 메시지 처리기입니다.

//-----------------------------------------------------------------------------
//
//	OnPaint
//
//-----------------------------------------------------------------------------
void CCcdSnrColorSensSpecDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	
}

//-----------------------------------------------------------------------------
//
//	다이얼로그 초기화
//
//-----------------------------------------------------------------------------
BOOL CCcdSnrColorSensSpecDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// 컨트롤 초기화
	this->InitCtrl();

	// 그리드 초기화
	this->InitSnrGridCtrl();
	//this->InitColorSensitivityGridCtrl();
	this->CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//-----------------------------------------------------------------------------
//
//	컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CCcdSnrColorSensSpecDlg::InitCtrl()
{
	// 폰트 생성
	m_clFontSmall.CreateFont(16, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontMid.CreateFont(23, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontBig.CreateFont(32, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));

	//m_clColorStaticTopBar.SetBkColor(RGB_COLOR_BLACK);
	//m_clColorStaticTopBar.SetTextColor(RGB_COLOR_WHITE);
	
	m_clColorStaticCenterSfrLimit.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCenterSfrLimit.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCenterSfrLimit.SetFont(&m_clFontSmall);

	m_clColorStaticCenterSfrLimitVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticCenterSfrLimitVal.SetFont(&m_clFontMid);

	m_clColorStaticCornerSfrLimit.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCornerSfrLimit.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCornerSfrLimit.SetFont(&m_clFontSmall);

	m_clColorStaticCornerSfrLimitVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticCornerSfrLimitVal.SetFont(&m_clFontMid);

	m_clColorStaticCornerSfrDeviationLimit.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCornerSfrDeviationLimit.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCornerSfrDeviationLimit.SetFont(&m_clFontSmall);

	m_clColorStaticCornerSfrDeviationLimitVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticCornerSfrDeviationLimitVal.SetFont(&m_clFontMid);

	m_clColorStaticOCXY.SetBkColor(RGB_DLG_BG);
	m_clColorStaticOCXY.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticOCXY.SetFont(&m_clFontSmall);

	m_clColorStaticOCXYVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticOCXYVal.SetFont(&m_clFontMid);

	m_clColorStaticOCTh.SetBkColor(RGB_DLG_BG);
	m_clColorStaticOCTh.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticOCTh.SetFont(&m_clFontSmall);

	m_clColorStaticOCThVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticOCThVal.SetFont(&m_clFontMid);

}

//-----------------------------------------------------------------------------
//
//	그리드 컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CCcdSnrColorSensSpecDlg::InitSnrGridCtrl()
{
	TCHAR* pszRow[] = { _T("") ,
		_T("dSNRThreshold") , _T("MIN SPEC") , _T("MAX SPEC")// _T("dSNRThreshold"), _T("dDRThreshold")
	};

	TCHAR* pszCol[] = { _T("SNR"), _T("Spec") };

	CRect rect;
	int i, j;
	int DLG = IDC_STATIC_CCD_SNR_SPEC_GRID_SPEC;

	CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
	int SpecRow = SnrMaxCount;//아래
	int SpecCol = 2;//옆
	int margin = 4;
	int gridHeight = 25;
	int gridWidth1 = 140;
	int gridWidth2 = 90;
	int totalWidth = gridWidth1 + (gridWidth2*(SpecCol - 1));
	//
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = totalWidth + margin;
	rect.bottom = (gridHeight*SpecRow) + margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.


	GetDlgItem(DLG)->GetWindowRect(rect);
	ScreenToClient(rect);
    m_clGridSnrSpec.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

	m_clGridSnrSpec.SetTextBkColor(RGB_COLOR_WHITE);
	m_clGridSnrSpec.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridSnrSpec.SetFixedTextColor(RGB_COLOR_WHITE);
	m_clGridSnrSpec.SetReference_Setting();
	m_clGridSnrSpec.EnableSelection(FALSE);
	m_clGridSnrSpec.SetRowCount(SpecRow);
	m_clGridSnrSpec.SetColumnCount(SpecCol);
	m_clGridSnrSpec.SetFixedRowCount(1);
	m_clGridSnrSpec.SetFixedColumnCount(1);

	for (i = 0; i < SpecRow; i++)
	{
        m_clGridSnrSpec.SetRowHeight(i, gridHeight);
        m_clGridSnrSpec.SetItemText(i, 0, pszRow[i]);

		for (j = 0; j < SpecCol; j++)
		{
			if (i == 0)
			{
				if (j == 0)
				{
                    m_clGridSnrSpec.SetColumnWidth(j, gridWidth1);
				}
				else
				{
                    m_clGridSnrSpec.SetColumnWidth(j, gridWidth2);
				}

                m_clGridSnrSpec.SetItemText(i, j, pszCol[j]);
			}

            m_clGridSnrSpec.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}
}

void CCcdSnrColorSensSpecDlg::InitColorSensitivityGridCtrl()
{
	TCHAR* pszRow[] = { _T("") 
        ,_T("dSpecDevMaxRG"), _T("dSpecDevMinRG"),_T("dSpecDevMaxBG"), 
        _T("dSpecDevMinBG"), _T("dSpecDevMaxGrGb"),_T("dSpecDevMinGrGb")
        , _T("nAdjustType"),_T("nTypicalValueType")
	};

	TCHAR* pszCol[] = { _T("Color Sensitivity"), _T("Spec") };

	CRect rect;
	int i, j;
	int DLG = IDC_STATIC_CCD_COLORSENS_SPEC_GRID_SPEC;

	CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
	int SpecRow = ColorSensitivityMaxCount;//아래
	int SpecCol = 2;//옆
	int margin = 4;
	int gridHeight = 25;
	int gridWidth1 = 140;
	int gridWidth2 = 90;
	int totalWidth = gridWidth1 + (gridWidth2*(SpecCol - 1));
	//
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = totalWidth + margin;
	rect.bottom = (gridHeight*SpecRow) + margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.


	GetDlgItem(DLG)->GetWindowRect(rect);
	ScreenToClient(rect);
    m_clGridColorSensitivitySpec.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

	m_clGridColorSensitivitySpec.SetTextBkColor(RGB_COLOR_WHITE);
	m_clGridColorSensitivitySpec.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridColorSensitivitySpec.SetFixedTextColor(RGB_COLOR_WHITE);
	m_clGridColorSensitivitySpec.SetReference_Setting();
	m_clGridColorSensitivitySpec.EnableSelection(FALSE);
	m_clGridColorSensitivitySpec.SetRowCount(SpecRow);
	m_clGridColorSensitivitySpec.SetColumnCount(SpecCol);
	m_clGridColorSensitivitySpec.SetFixedRowCount(1);
	m_clGridColorSensitivitySpec.SetFixedColumnCount(1);

	for (i = 0; i < SpecRow; i++)
	{
        m_clGridColorSensitivitySpec.SetRowHeight(i, gridHeight);
        m_clGridColorSensitivitySpec.SetItemText(i, 0, pszRow[i]);

		for (j = 0; j < SpecCol; j++)
		{
			if (i == 0)
			{
				if (j == 0)
				{
                    m_clGridColorSensitivitySpec.SetColumnWidth(j, gridWidth1);
				}
				else
				{
                    m_clGridColorSensitivitySpec.SetColumnWidth(j, gridWidth2);
				}

                m_clGridColorSensitivitySpec.SetItemText(i, j, pszCol[j]);
			}

            m_clGridColorSensitivitySpec.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}
}
//-----------------------------------------------------------------------------
//
//	유닛 설정
//
//-----------------------------------------------------------------------------
void CCcdSnrColorSensSpecDlg::SetUnit(int nUnit)
{
	m_nUnit = nUnit;
}

//-----------------------------------------------------------------------------
//
//	OnShowWindow
//
//-----------------------------------------------------------------------------
void CCcdSnrColorSensSpecDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (bShow == TRUE)
	{
		this->ShowSnrSpec();
		//this->ShowColorSensitivitySpec();
	}
}

//-----------------------------------------------------------------------------
//
//	SFR SPEC 데이터 표시
//
//-----------------------------------------------------------------------------
void CCcdSnrColorSensSpecDlg::ShowSnrSpec()
{
	TCHAR szData[SIZE_OF_100BYTE];
	int i;

	/*_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), model.m_dLimitSFRCent);
	m_clColorStaticCenterSfrLimitVal.SetWindowText(szData);

	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), model.m_dLimitSFRSide);
	m_clColorStaticCornerSfrLimitVal.SetWindowText(szData);

	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clSysData.m_dLimitSFRBalance[m_nUnit]);
	m_clColorStaticCornerSfrDeviationLimitVal.SetWindowText(szData);

	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clSysData.m_clOCSpec[m_nUnit].x);
	m_clColorStaticOCXYVal.SetWindowText(szData);

	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clSysData.m_dOCSpecTh[m_nUnit]);
	m_clColorStaticOCThVal.SetWindowText(szData);*/

	for (i = 0; i < SnrMaxCount-1; i++)
	{
        m_clGridSnrSpec.SetItemText(i + 1, 1, (int)model.m_SnrSpec[i], 3);
	}
    m_clGridSnrSpec.Invalidate();
}
//-----------------------------------------------------------------------------
//
//	UNIFORMITY SPEC 데이터 표시
//
//-----------------------------------------------------------------------------
void CCcdSnrColorSensSpecDlg::ShowColorSensitivitySpec()
{
	TCHAR szData[SIZE_OF_100BYTE];
	int i;

	for (i = 0; i < ColorSensitivityMaxCount-1; i++)
	{
        m_clGridColorSensitivitySpec.SetItemText(i + 1, 1, (int)model.m_ColorSensitivitySpec[i], 3);
	}
    m_clGridColorSensitivitySpec.Invalidate();
}

//-----------------------------------------------------------------------------
//
//	CENTER SFR LIMIT
//
//-----------------------------------------------------------------------------
void CCcdSnrColorSensSpecDlg::OnStnClickedStaticCcdSfrSpecCenterSfrLimitVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPos = _T("");

	m_clColorStaticCenterSfrLimitVal.GetWindowText(sPos);
	CKeyPadDlg keyDlg;
	if (keyDlg.DoModal() == IDOK)
	{
		sPos.Format(_T("%s"), keyDlg.GetstrKeypad());
		m_clColorStaticCenterSfrLimitVal.SetWindowText(sPos);
	}


}

//-----------------------------------------------------------------------------
//
//	CORNER SFR LIMIT
//
//-----------------------------------------------------------------------------
void CCcdSnrColorSensSpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrLimitVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPos = _T("");

	m_clColorStaticCornerSfrLimitVal.GetWindowText(sPos);
	CKeyPadDlg keyDlg;
	if (keyDlg.DoModal() == IDOK)
	{
		sPos.Format(_T("%s"), keyDlg.GetstrKeypad());
		m_clColorStaticCornerSfrLimitVal.SetWindowText(sPos);
	}
}

//-----------------------------------------------------------------------------
//
//	코너부 SFR 편차 LIMIT
//
//-----------------------------------------------------------------------------
void CCcdSnrColorSensSpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrDeviationLimitVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPos = _T("");

	m_clColorStaticCornerSfrDeviationLimitVal.GetWindowText(sPos);
	CKeyPadDlg keyDlg;
	if (keyDlg.DoModal() == IDOK)
	{
		sPos.Format(_T("%s"), keyDlg.GetstrKeypad());
		m_clColorStaticCornerSfrDeviationLimitVal.SetWindowText(sPos);
	}


}

//-----------------------------------------------------------------------------
//
//	광축검사 XY
//
//-----------------------------------------------------------------------------
void CCcdSnrColorSensSpecDlg::OnStnClickedStaticCcdSfrSpecOcXyVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPos = _T("");

	m_clColorStaticOCXYVal.GetWindowText(sPos);
	CKeyPadDlg keyDlg;
	if (keyDlg.DoModal() == IDOK)
	{
		sPos.Format(_T("%s"), keyDlg.GetstrKeypad());
		m_clColorStaticOCXYVal.SetWindowText(sPos);
	}

	
}

//-----------------------------------------------------------------------------
//
//	광축검사 TH
//
//-----------------------------------------------------------------------------
void CCcdSnrColorSensSpecDlg::OnStnClickedStaticCcdSfrSpecOcThVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPos = _T("");

	m_clColorStaticOCThVal.GetWindowText(sPos);
	CKeyPadDlg keyDlg;
	if (keyDlg.DoModal() == IDOK)
	{
		sPos.Format(_T("%s"), keyDlg.GetstrKeypad());
		m_clColorStaticOCThVal.SetWindowText(sPos);
	}


}

//-----------------------------------------------------------------------------
//
//	버튼 : SAVE
//
//-----------------------------------------------------------------------------
void CCcdSnrColorSensSpecDlg::OnBnClickedButtonCcdSfrSpecSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	if (Task.AutoFlag == 2)
	{
		sLangChange.LoadStringA(IDS_STRING1468);
		delayMsg(sLangChange, 2000, M_COLOR_RED);// 일시 정지 중 사용 불가
		return;
	}
	CString sTemp;
	sTemp.Format("SNR SPEC 데이터를 저장하시겠습니까?");
	if (!askMsg(sTemp))return;


	//if (g_ShowMsgModal(_T("확인"), _T("DEFECT/UNIFORM SPEC 데이터를 저장하시겠습니까?"), RGB_COLOR_BLUE) == false)
	//	return;

	this->GetSnrSpec();
    //.this->GetColorSensitivitySpec();
	//g_clSysData.Save();
	//g_clMandoSfrSpec[m_nUnit].Save();
	model.AcmisDataSave();
	theApp.MainDlg->putListLog(_T("[INFO] SNR/COLOR SENSITIVITY SPEC 저장"));//, 0, m_nUnit);
}

//-----------------------------------------------------------------------------
//
//	SFR 데이터 -> 메모리에 저장
//
//-----------------------------------------------------------------------------
void CCcdSnrColorSensSpecDlg::GetSnrSpec()
{
	CString sData = _T("");
	int i;

	for (i = 0; i < SnrMaxCount-1; i++)
	{
		sData = m_clGridSnrSpec.GetItemText(i + 1, 1);
		model.m_SnrSpec[i] = _ttof((TCHAR*)(LPCTSTR)sData);
	}

	/*GetDlgItem(IDC_STATIC_CCD_SFR_SPEC_CENTER_SFR_LIMIT_VAL)->GetWindowText(sData);
	model.m_dLimitSFRCent = _ttof((TCHAR*)(LPCTSTR)sData);

	GetDlgItem(IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_LIMIT_VAL)->GetWindowText(sData);
	model.m_dLimitSFRSide = _ttof((TCHAR*)(LPCTSTR)sData);

	GetDlgItem(IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_DEVIATION_LIMIT_VAL)->GetWindowText(sData);
	g_clSysData.m_dLimitSFRBalance[m_nUnit] = _ttof((TCHAR*)(LPCTSTR)sData);

	GetDlgItem(IDC_STATIC_CCD_SFR_SPEC_OC_XY_VAL)->GetWindowText(sData);
	g_clSysData.m_clOCSpec[m_nUnit].x = _ttof((TCHAR*)(LPCTSTR)sData);
	g_clSysData.m_clOCSpec[m_nUnit].y = _ttof((TCHAR*)(LPCTSTR)sData);

	GetDlgItem(IDC_STATIC_CCD_SFR_SPEC_OC_TH_VAL)->GetWindowText(sData);
	g_clSysData.m_dOCSpecTh[m_nUnit] = _ttof((TCHAR*)(LPCTSTR)sData);*/

	//g_clSysData.Save();
}
//-----------------------------------------------------------------------------
//
//	UNIFORMITY 데이터 -> 메모리에 저장
//
//-----------------------------------------------------------------------------
void CCcdSnrColorSensSpecDlg::GetColorSensitivitySpec()
{
	CString sData = _T("");
	int i;

	for (i = 0; i < ColorSensitivityMaxCount-1; i++)
	{
		sData = m_clGridColorSensitivitySpec.GetItemText(i + 1, 1);
		model.m_ColorSensitivitySpec[i] = _ttof((TCHAR*)(LPCTSTR)sData);
	}
	//g_clSysData.Save();
}

//-----------------------------------------------------------------------------
//
//	버튼 : CLOSE
//
//-----------------------------------------------------------------------------
void CCcdSnrColorSensSpecDlg::OnBnClickedButtonCcdSfrSpecClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ShowWindow(SW_HIDE);
}

//-----------------------------------------------------------------------------
//
//	그리드 컨트롤 더블 클릭
//
//-----------------------------------------------------------------------------
void CCcdSnrColorSensSpecDlg::OnNMDblClickedSnrSpec(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
	CString sData = _T("");
	int nRow, nCol;

	nRow = pNMGridView->iRow;
	nCol = pNMGridView->iColumn;

	if (nRow >= 1 && nCol >= 1)
	{
		sData = m_clGridSnrSpec.GetItemText(nRow, nCol);
		//CKeyPadDlg keyDlg;
		//if (keyDlg.DoModal() == IDOK)
		CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)sData);

		if (dlg.DoModal() == IDOK)
		{
			sData.Format(_T("%.2lf"), atof(dlg.GetstrNum())); //keyDlg.GetstrKeypad());
            m_clGridSnrSpec.SetItemText(nRow, nCol, sData);

            m_clGridSnrSpec.Invalidate();
		}

	}
}

//-----------------------------------------------------------------------------
//
//	그리드 컨트롤 더블 클릭
//
//-----------------------------------------------------------------------------
void CCcdSnrColorSensSpecDlg::OnNMDblClickedColorSensitivitySpec(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
	CString sData = _T("");
	int nRow, nCol;

	nRow = pNMGridView->iRow;
	nCol = pNMGridView->iColumn;

	if (nRow >= 1 && nCol >= 1)
	{
		sData = m_clGridColorSensitivitySpec.GetItemText(nRow, nCol);
		CKeyPadDlg keyDlg;
		if (keyDlg.DoModal() == IDOK)
		{
			sData.Format(_T("%s"), keyDlg.GetstrKeypad());
            m_clGridColorSensitivitySpec.SetItemText(nRow, nCol, sData);

            m_clGridColorSensitivitySpec.Invalidate();
			}

	}
}

//-----------------------------------------------------------------------------
//
//	OnLButtonDown
//
//-----------------------------------------------------------------------------
void CCcdSnrColorSensSpecDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);

	CDialogEx::OnLButtonDown(nFlags, point);
}

//-----------------------------------------------------------------------------
//
//	PreTranslateMessage
//
//-----------------------------------------------------------------------------
BOOL CCcdSnrColorSensSpecDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_LBUTTONDOWN)
	{
	}
	else if (pMsg->message == WM_LBUTTONUP)
	{
		
	}

	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
			return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}