// CcdSfrSpecDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CcdBlemishSpecDlg.h"
// CCcdBlemishSpecDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCcdBlemishSpecDlg, CDialogEx)

CCcdBlemishSpecDlg::CCcdBlemishSpecDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCcdBlemishSpecDlg::IDD, pParent)
{
}

CCcdBlemishSpecDlg::~CCcdBlemishSpecDlg()
{
}

void CCcdBlemishSpecDlg::DoDataExchange(CDataExchange* pDX)
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


BEGIN_MESSAGE_MAP(CCcdBlemishSpecDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
    ON_NOTIFY(NM_DBLCLK, IDC_STATIC_CCD_BLEMISH_SPEC_GRID_SPEC, &CCcdBlemishSpecDlg::OnNMDblClickedSfrBlockspot)
    ON_NOTIFY(NM_DBLCLK, IDC_STATIC_CCD_LCB_SPEC_GRID_SPEC, &CCcdBlemishSpecDlg::OnNMDblClickedSfrLcb)
    ON_NOTIFY(NM_DBLCLK, IDC_STATIC_CCD_YMEAN_SPEC_GRID_SPEC, &CCcdBlemishSpecDlg::OnNMDblClickedSfrYmean)
	ON_BN_CLICKED(IDC_BUTTON_CCD_SFR_SPEC_SAVE, &CCcdBlemishSpecDlg::OnBnClickedButtonCcdSfrSpecSave)
	ON_BN_CLICKED(IDC_BUTTON_CCD_SFR_SPEC_CLOSE, &CCcdBlemishSpecDlg::OnBnClickedButtonCcdSfrSpecClose)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_CENTER_SFR_LIMIT_VAL, &CCcdBlemishSpecDlg::OnStnClickedStaticCcdSfrSpecCenterSfrLimitVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_LIMIT_VAL, &CCcdBlemishSpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrLimitVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_DEVIATION_LIMIT_VAL, &CCcdBlemishSpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrDeviationLimitVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_OC_XY_VAL, &CCcdBlemishSpecDlg::OnStnClickedStaticCcdSfrSpecOcXyVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_OC_TH_VAL, &CCcdBlemishSpecDlg::OnStnClickedStaticCcdSfrSpecOcThVal)
END_MESSAGE_MAP()


// CCcdBlemishSpecDlg 메시지 처리기입니다.

//-----------------------------------------------------------------------------
//
//	OnPaint
//
//-----------------------------------------------------------------------------
void CCcdBlemishSpecDlg::OnPaint()
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
BOOL CCcdBlemishSpecDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// 컨트롤 초기화
	this->InitCtrl();

	// 그리드 초기화
    this->InitLcbGridCtrl();
    this->InitYmeanGridCtrl();
    this->InitFdfGridCtrl();

    
	this->CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//-----------------------------------------------------------------------------
//
//	컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CCcdBlemishSpecDlg::InitCtrl()
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
void CCcdBlemishSpecDlg::InitFdfGridCtrl()
{
    TCHAR* pszCol[] = { _T("FDF"), _T("Spec") };

    CRect rect;
    int i, j;
    int DLG = IDC_STATIC_CCD_BLEMISH_SPEC_GRID_SPEC;

    CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
    int SpecRow = FdfMaxCount + 1;//아래
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
	m_clGridFDFSpec.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

    m_clGridFDFSpec.SetTextBkColor(RGB_COLOR_WHITE);
    m_clGridFDFSpec.SetFixedBkColor(GRID_COLOR_TITLE);
    m_clGridFDFSpec.SetFixedTextColor(RGB_COLOR_WHITE);
    m_clGridFDFSpec.SetReference_Setting();
    m_clGridFDFSpec.EnableSelection(FALSE);
    m_clGridFDFSpec.SetRowCount(SpecRow);
    m_clGridFDFSpec.SetColumnCount(SpecCol);
    m_clGridFDFSpec.SetFixedRowCount(1);
    m_clGridFDFSpec.SetFixedColumnCount(1);

    for (i = 0; i < SpecRow; i++)
    {
		m_clGridFDFSpec.SetRowHeight(i, gridHeight);
		m_clGridFDFSpec.SetItemText(i + 1, 0, STAIN_FDF_SPEC_NAME[i]);

        for (j = 0; j < SpecCol; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
					m_clGridFDFSpec.SetColumnWidth(j, gridWidth1);
                }
                else
                {
					m_clGridFDFSpec.SetColumnWidth(j, gridWidth2);
                }

				m_clGridFDFSpec.SetItemText(i, j, pszCol[j]);
            }

			m_clGridFDFSpec.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }
    }
}
void CCcdBlemishSpecDlg::InitLcbGridCtrl()
{
    TCHAR* pszCol[] = { _T("Lcb"), _T("Spec") };

    CRect rect;
    int i, j;
    int DLG = IDC_STATIC_CCD_LCB_SPEC_GRID_SPEC;

    CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
    int SpecRow = LcbMaxCount + 1;//아래
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
    m_clGridLcbSpec.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

    m_clGridLcbSpec.SetTextBkColor(RGB_COLOR_WHITE);
    m_clGridLcbSpec.SetFixedBkColor(GRID_COLOR_TITLE);
    m_clGridLcbSpec.SetFixedTextColor(RGB_COLOR_WHITE);
    m_clGridLcbSpec.SetReference_Setting();
    m_clGridLcbSpec.EnableSelection(FALSE);
    m_clGridLcbSpec.SetRowCount(SpecRow);
    m_clGridLcbSpec.SetColumnCount(SpecCol);
    m_clGridLcbSpec.SetFixedRowCount(1);
    m_clGridLcbSpec.SetFixedColumnCount(1);

    for (i = 0; i < SpecRow; i++)
    {
        m_clGridLcbSpec.SetRowHeight(i, gridHeight);
        m_clGridLcbSpec.SetItemText(i + 1, 0, STAIN_LCB_SPEC_NAME[i]);

        for (j = 0; j < SpecCol; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    m_clGridLcbSpec.SetColumnWidth(j, gridWidth1);
                }
                else
                {
                    m_clGridLcbSpec.SetColumnWidth(j, gridWidth2);
                }

                m_clGridLcbSpec.SetItemText(i, j, pszCol[j]);
            }

            m_clGridLcbSpec.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }
    }
}
void CCcdBlemishSpecDlg::InitYmeanGridCtrl()
{

    TCHAR* pszCol[] = { _T("Ymean"), _T("Spec") };

    CRect rect;
    int i, j;
    int DLG = IDC_STATIC_CCD_YMEAN_SPEC_GRID_SPEC;

    CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
    int SpecRow = YmeanMaxCount + 1;//아래
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
    m_clGridYmenaSpec.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

    m_clGridYmenaSpec.SetTextBkColor(RGB_COLOR_WHITE);
    m_clGridYmenaSpec.SetFixedBkColor(GRID_COLOR_TITLE);
    m_clGridYmenaSpec.SetFixedTextColor(RGB_COLOR_WHITE);
    m_clGridYmenaSpec.SetReference_Setting();
    m_clGridYmenaSpec.EnableSelection(FALSE);
    m_clGridYmenaSpec.SetRowCount(SpecRow);
    m_clGridYmenaSpec.SetColumnCount(SpecCol);
    m_clGridYmenaSpec.SetFixedRowCount(1);
    m_clGridYmenaSpec.SetFixedColumnCount(1);

    for (i = 0; i < SpecRow; i++)
    {
        m_clGridYmenaSpec.SetRowHeight(i, gridHeight);
        m_clGridYmenaSpec.SetItemText(i + 1, 0, STAIN_YMEAN_SPEC_NAME[i]);

        for (j = 0; j < SpecCol; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    m_clGridYmenaSpec.SetColumnWidth(j, gridWidth1);
                }
                else
                {
                    m_clGridYmenaSpec.SetColumnWidth(j, gridWidth2);
                }

                m_clGridYmenaSpec.SetItemText(i, j, pszCol[j]);
            }

            m_clGridYmenaSpec.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }
    }
}
//-----------------------------------------------------------------------------
//
//	유닛 설정
//
//-----------------------------------------------------------------------------
void CCcdBlemishSpecDlg::SetUnit(int nUnit)
{
	m_nUnit = nUnit;
}

//-----------------------------------------------------------------------------
//
//	OnShowWindow
//
//-----------------------------------------------------------------------------
void CCcdBlemishSpecDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (bShow == TRUE)
	{
        this->ShowBlemishSpec();
        this->ShowLcbSpec();
        this->ShowYmeanSpec();
	}
}

//-----------------------------------------------------------------------------
//
//	SFR SPEC 데이터 표시
//
//-----------------------------------------------------------------------------
void CCcdBlemishSpecDlg::ShowBlemishSpec()
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

	for (i = 0; i < FdfMaxCount; i++)
	{
		m_clGridFDFSpec.SetItemText(i + 1, 1, model.m_FDFSpec[i],3);
		//m_clGridBlemishSpec.SetItemText(i + 1, 2, model.m_LcbSpec[i],3);
		//m_clGridBlemishSpec.SetItemText(i + 1, 3, model.m_YmeanSpec[i],3);
	}

	m_clGridFDFSpec.Invalidate();
}
void CCcdBlemishSpecDlg::ShowLcbSpec()
{
    TCHAR szData[SIZE_OF_100BYTE];
    int i;

    for (i = 0; i < LcbMaxCount; i++)
    {
        m_clGridLcbSpec.SetItemText(i + 1, 1, model.m_LcbSpec[i], 3);
    }

    m_clGridLcbSpec.Invalidate();
}
void CCcdBlemishSpecDlg::ShowYmeanSpec()
{
    TCHAR szData[SIZE_OF_100BYTE];
    int i;

    for (i = 0; i < YmeanMaxCount; i++)
    {
        m_clGridYmenaSpec.SetItemText(i + 1, 1, model.m_YmeanSpec[i], 3);
    }

    m_clGridYmenaSpec.Invalidate();
}


//-----------------------------------------------------------------------------
//
//	SFR 데이터 -> 메모리에 저장
//
//-----------------------------------------------------------------------------
void CCcdBlemishSpecDlg::GetBlemishSpec()
{
    CString sData = _T("");
    int i;

    for (i = 0; i < FdfMaxCount; i++)
    {
        sData = m_clGridFDFSpec.GetItemText(i + 1, 1);
        model.m_FDFSpec[i] = _ttof((TCHAR*)(LPCTSTR)sData);

    }
}
void CCcdBlemishSpecDlg::GetLcbSpec()
{
    CString sData = _T("");
    int i;

    for (i = 0; i < LcbMaxCount; i++)
    {
        sData = m_clGridLcbSpec.GetItemText(i + 1, 1);
        model.m_LcbSpec[i] = _ttof((TCHAR*)(LPCTSTR)sData);
    }
    //g_clSysData.Save();
}
void CCcdBlemishSpecDlg::GetYmeanSpec()
{
    CString sData = _T("");
    int i;

    for (i = 0; i < YmeanMaxCount; i++)
    {
        sData = m_clGridYmenaSpec.GetItemText(i + 1, 1);
        model.m_YmeanSpec[i] = _ttof((TCHAR*)(LPCTSTR)sData);
    }
    //g_clSysData.Save();
}
//---------------------------------------------------------------------------
//
//	CENTER SFR LIMIT
//
//-----------------------------------------------------------------------------
void CCcdBlemishSpecDlg::OnStnClickedStaticCcdSfrSpecCenterSfrLimitVal()
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
void CCcdBlemishSpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrLimitVal()
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
void CCcdBlemishSpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrDeviationLimitVal()
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
void CCcdBlemishSpecDlg::OnStnClickedStaticCcdSfrSpecOcXyVal()
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
void CCcdBlemishSpecDlg::OnStnClickedStaticCcdSfrSpecOcThVal()
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
void CCcdBlemishSpecDlg::OnBnClickedButtonCcdSfrSpecSave()
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
	sTemp.Format("BLEMISH SPEC 데이터를 저장하시겠습니까?");
	if (!askMsg(sTemp))return;
	//if (g_ShowMsgModal(_T("확인"), _T("DEFECT/UNIFORM SPEC 데이터를 저장하시겠습니까?"), RGB_COLOR_BLUE) == false)
		//return;

    this->GetBlemishSpec();
    this->GetLcbSpec();
    this->GetYmeanSpec();

	//g_clSysData.Save();
	//g_clMandoSfrSpec[m_nUnit].Save();
	model.AcmisDataSave();
	theApp.MainDlg->putListLog(_T("[INFO] BLEMISH SPEC 저장"));// , 0, m_nUnit);
}

//-----------------------------------------------------------------------------
//
//	버튼 : CLOSE
//
//-----------------------------------------------------------------------------
void CCcdBlemishSpecDlg::OnBnClickedButtonCcdSfrSpecClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ShowWindow(SW_HIDE);
}

//-----------------------------------------------------------------------------
//
//	그리드 컨트롤 더블 클릭
//
//-----------------------------------------------------------------------------
void CCcdBlemishSpecDlg::OnNMDblClickedSfrBlockspot(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
    CString sData = _T("");
    int nRow, nCol;

    nRow = pNMGridView->iRow;
    nCol = pNMGridView->iColumn;

    if (nRow >= 1 && nCol >= 1)
    {
        sData = m_clGridFDFSpec.GetItemText(nRow, nCol);
		/*CKeyPadDlg keyDlg;
		if (keyDlg.DoModal() == IDOK)
		{
			sData.Format(_T("%s"), keyDlg.GetstrKeypad());*/
		CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)sData);
		if (dlg.DoModal() == IDOK)
		{
			float f_num = (float)atof(dlg.GetstrNum());
			sData.Format(_T("%.3f"), f_num);
			m_clGridFDFSpec.SetItemText(nRow, nCol, sData);

			m_clGridFDFSpec.Invalidate();
        }


    }
}

void CCcdBlemishSpecDlg::OnNMDblClickedSfrLcb(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
    CString sData = _T("");
    int nRow, nCol;

    nRow = pNMGridView->iRow;
    nCol = pNMGridView->iColumn;

    if (nRow >= 1 && nCol >= 1)
    {
        sData = m_clGridLcbSpec.GetItemText(nRow, nCol);
		/*CKeyPadDlg keyDlg;
		if (keyDlg.DoModal() == IDOK)
		{
			sData.Format(_T("%s"), keyDlg.GetstrKeypad());*/
		CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)sData);
		if (dlg.DoModal() == IDOK)
		{
			float f_num = (float)atof(dlg.GetstrNum());
			sData.Format(_T("%.3f"), f_num);
            m_clGridLcbSpec.SetItemText(nRow, nCol, sData);

            m_clGridLcbSpec.Invalidate();
        }

     
    }
}

void CCcdBlemishSpecDlg::OnNMDblClickedSfrYmean(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
    CString sData = _T("");
    int nRow, nCol;

    nRow = pNMGridView->iRow;
    nCol = pNMGridView->iColumn;

    if (nRow >= 1 && nCol >= 1)
    {
        sData = m_clGridYmenaSpec.GetItemText(nRow, nCol);
		/*CKeyPadDlg keyDlg;
		if (keyDlg.DoModal() == IDOK)
		{
			sData.Format(_T("%s"), keyDlg.GetstrKeypad());*/
		CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)sData);
		if (dlg.DoModal() == IDOK)
		{
			float f_num = (float)atof(dlg.GetstrNum());
			sData.Format(_T("%.3f"), f_num);
            m_clGridYmenaSpec.SetItemText(nRow, nCol, sData);

            m_clGridYmenaSpec.Invalidate();
        }

    }
}

//-----------------------------------------------------------------------------
//
//	그리드 컨트롤 더블 클릭
//
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//
//	OnLButtonDown
//
//-----------------------------------------------------------------------------
void CCcdBlemishSpecDlg::OnLButtonDown(UINT nFlags, CPoint point)
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
BOOL CCcdBlemishSpecDlg::PreTranslateMessage(MSG* pMsg)
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