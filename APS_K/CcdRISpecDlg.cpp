// CcdSfrSpecDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CcdRISpecDlg.h"
// CCcdRISpecDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCcdRISpecDlg, CDialogEx)

CCcdRISpecDlg::CCcdRISpecDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCcdRISpecDlg::IDD, pParent)
{
}

CCcdRISpecDlg::~CCcdRISpecDlg()
{
}

void CCcdRISpecDlg::DoDataExchange(CDataExchange* pDX)
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


BEGIN_MESSAGE_MAP(CCcdRISpecDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_CCD_RI1_SPEC_GRID_SPEC, &CCcdRISpecDlg::OnNMDblClickedRi1Spec)
	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_CCD_RI2_SPEC_GRID_SPEC, &CCcdRISpecDlg::OnNMDblClickedRi2Spec)
    ON_NOTIFY(NM_DBLCLK, IDC_STATIC_CCD_RI3_SPEC_GRID_SPEC, &CCcdRISpecDlg::OnNMDblClickedRi3Spec)
    ON_NOTIFY(NM_DBLCLK, IDC_STATIC_CCD_RI5_SPEC_GRID_SPEC, &CCcdRISpecDlg::OnNMDblClickedRi5Spec)
    ON_NOTIFY(NM_DBLCLK, IDC_STATIC_CCD_RI6_SPEC_GRID_SPEC, &CCcdRISpecDlg::OnNMDblClickedRi6Spec)

    //base
	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_CCD_RI4_SPEC_GRID_SPEC, &CCcdRISpecDlg::OnNMDblClickedRi4Spec)

	ON_BN_CLICKED(IDC_BUTTON_CCD_SFR_SPEC_SAVE, &CCcdRISpecDlg::OnBnClickedButtonCcdSfrSpecSave)
	ON_BN_CLICKED(IDC_BUTTON_CCD_SFR_SPEC_CLOSE, &CCcdRISpecDlg::OnBnClickedButtonCcdSfrSpecClose)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_CENTER_SFR_LIMIT_VAL, &CCcdRISpecDlg::OnStnClickedStaticCcdSfrSpecCenterSfrLimitVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_LIMIT_VAL, &CCcdRISpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrLimitVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_DEVIATION_LIMIT_VAL, &CCcdRISpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrDeviationLimitVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_OC_XY_VAL, &CCcdRISpecDlg::OnStnClickedStaticCcdSfrSpecOcXyVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_OC_TH_VAL, &CCcdRISpecDlg::OnStnClickedStaticCcdSfrSpecOcThVal)
END_MESSAGE_MAP()


// CCcdRISpecDlg 메시지 처리기입니다.

//-----------------------------------------------------------------------------
//
//	OnPaint
//
//-----------------------------------------------------------------------------
void CCcdRISpecDlg::OnPaint()
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
BOOL CCcdRISpecDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// 컨트롤 초기화
	this->InitCtrl();

	// 그리드 초기화
    
	this->InitRIGridCtrl();
    //
    this->InitRiThresholdGridCtrl1();
    this->InitRiThresholdGridCtrl2();
    this->InitRiThresholdGridCtrl3();
    this->InitRiThresholdGridCtrl4();
    this->InitRiThresholdGridCtrl5();
	this->CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//-----------------------------------------------------------------------------
//
//	컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CCcdRISpecDlg::InitCtrl()
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
void CCcdRISpecDlg::InitRiThresholdGridCtrl1()
{

    TCHAR* pszCol[] = { _T("RI"), _T("Threshold_Ch1"), _T("Threshold_Ch2"), _T("Threshold_Ch3"), _T("Threshold_Ch4") };
    CString sData;
    CRect rect;
    int i, j;
    int DLG = IDC_STATIC_CCD_RI1_SPEC_GRID_SPEC;

    CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
    int SpecRow = 5;//아래
    int SpecCol = RIThresholdMaxCount;//옆
    int margin = 4;
    int gridHeight = 25;
    int gridWidth1 = 100;
    int gridWidth2 = 50;
    int totalWidth = gridWidth1 + (gridWidth2*(SpecCol - 1));
    //
    pWnd->GetWindowRect(rect);
    ScreenToClient(rect);

    rect.right = totalWidth + margin;
    rect.bottom = (gridHeight*SpecRow) + margin;
    pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.


    GetDlgItem(DLG)->GetWindowRect(rect);
    ScreenToClient(rect);
    m_clGridRIThresholdSpec1.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

    m_clGridRIThresholdSpec1.SetTextBkColor(RGB_COLOR_WHITE);
    m_clGridRIThresholdSpec1.SetFixedBkColor(GRID_COLOR_TITLE);
    m_clGridRIThresholdSpec1.SetFixedTextColor(RGB_COLOR_WHITE);
    m_clGridRIThresholdSpec1.SetReference_Setting();
    m_clGridRIThresholdSpec1.EnableSelection(FALSE);
    m_clGridRIThresholdSpec1.SetRowCount(SpecRow);
    m_clGridRIThresholdSpec1.SetColumnCount(SpecCol);
    m_clGridRIThresholdSpec1.SetFixedRowCount(1);
    m_clGridRIThresholdSpec1.SetFixedColumnCount(1);
    for (i = 0; i < SpecCol; i++)
    {
        sData.Format(_T("ROI%d"), i + 1);
        m_clGridRIThresholdSpec1.SetItemText(0, i + 1, sData);
    }


    for (i = 0; i < SpecRow; i++)
    {
        m_clGridRIThresholdSpec1.SetRowHeight(i, gridHeight);
        m_clGridRIThresholdSpec1.SetItemText(i, 0, pszCol[i]);

        for (j = 0; j < SpecCol; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    m_clGridRIThresholdSpec1.SetColumnWidth(j, gridWidth1);
                }
                else
                {
                    m_clGridRIThresholdSpec1.SetColumnWidth(j, gridWidth2);
                }

                //
            }

            m_clGridRIThresholdSpec1.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }
    }
}

void CCcdRISpecDlg::InitRiThresholdGridCtrl2()
{

    TCHAR* pszCol[] = { _T("RI"), _T("Threshold_Ch1"), _T("Threshold_Ch2"), _T("Threshold_Ch3"), _T("Threshold_Ch4") };
    CString sData;
    CRect rect;
    int i, j;
    int DLG = IDC_STATIC_CCD_RI2_SPEC_GRID_SPEC;

    CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
    int SpecRow = 5;//아래
    int SpecCol = RIThresholdMaxCount;//옆
    int margin = 4;
    int gridHeight = 25;
    int gridWidth1 = 100;
    int gridWidth2 = 50;
    int totalWidth = gridWidth1 + (gridWidth2*(SpecCol - 1));
    //
    pWnd->GetWindowRect(rect);
    ScreenToClient(rect);

    rect.right = totalWidth + margin;
    rect.bottom = (gridHeight*SpecRow) + margin;
    pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.


    GetDlgItem(DLG)->GetWindowRect(rect);
    ScreenToClient(rect);
    m_clGridRIThresholdSpec2.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

    m_clGridRIThresholdSpec2.SetTextBkColor(RGB_COLOR_WHITE);
    m_clGridRIThresholdSpec2.SetFixedBkColor(GRID_COLOR_TITLE);
    m_clGridRIThresholdSpec2.SetFixedTextColor(RGB_COLOR_WHITE);
    m_clGridRIThresholdSpec2.SetReference_Setting();
    m_clGridRIThresholdSpec2.EnableSelection(FALSE);
    m_clGridRIThresholdSpec2.SetRowCount(SpecRow);
    m_clGridRIThresholdSpec2.SetColumnCount(SpecCol);
    m_clGridRIThresholdSpec2.SetFixedRowCount(1);
    m_clGridRIThresholdSpec2.SetFixedColumnCount(1);
    for (i = 0; i < SpecCol; i++)
    {
        sData.Format(_T("ROI%d"), i + 21);
        m_clGridRIThresholdSpec2.SetItemText(0, i + 1, sData);
    }


    for (i = 0; i < SpecRow; i++)
    {
        m_clGridRIThresholdSpec2.SetRowHeight(i, gridHeight);
        m_clGridRIThresholdSpec2.SetItemText(i, 0, pszCol[i]);

        for (j = 0; j < SpecCol; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    m_clGridRIThresholdSpec2.SetColumnWidth(j, gridWidth1);
                }
                else
                {
                    m_clGridRIThresholdSpec2.SetColumnWidth(j, gridWidth2);
                }

                //
            }

            m_clGridRIThresholdSpec2.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }
    }
}
void CCcdRISpecDlg::InitRiThresholdGridCtrl3()
{

    TCHAR* pszCol[] = { _T("RI"), _T("Threshold_Ch1"), _T("Threshold_Ch2"), _T("Threshold_Ch3"), _T("Threshold_Ch4") };
    CString sData;
    CRect rect;
    int i, j;
    int DLG = IDC_STATIC_CCD_RI3_SPEC_GRID_SPEC;

    CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
    int SpecRow = 5;//아래
    int SpecCol = RIThresholdMaxCount;//옆
    int margin = 4;
    int gridHeight = 25;
    int gridWidth1 = 100;
    int gridWidth2 = 50;
    int totalWidth = gridWidth1 + (gridWidth2*(SpecCol - 1));
    //
    pWnd->GetWindowRect(rect);
    ScreenToClient(rect);

    rect.right = totalWidth + margin;
    rect.bottom = (gridHeight*SpecRow) + margin;
    pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.


    GetDlgItem(DLG)->GetWindowRect(rect);
    ScreenToClient(rect);
    m_clGridRIThresholdSpec3.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

    m_clGridRIThresholdSpec3.SetTextBkColor(RGB_COLOR_WHITE);
    m_clGridRIThresholdSpec3.SetFixedBkColor(GRID_COLOR_TITLE);
    m_clGridRIThresholdSpec3.SetFixedTextColor(RGB_COLOR_WHITE);
    m_clGridRIThresholdSpec3.SetReference_Setting();
    m_clGridRIThresholdSpec3.EnableSelection(FALSE);
    m_clGridRIThresholdSpec3.SetRowCount(SpecRow);
    m_clGridRIThresholdSpec3.SetColumnCount(SpecCol);
    m_clGridRIThresholdSpec3.SetFixedRowCount(1);
    m_clGridRIThresholdSpec3.SetFixedColumnCount(1);
    for (i = 0; i < SpecCol; i++)
    {
        sData.Format(_T("ROI%d"), i + 41);
        m_clGridRIThresholdSpec3.SetItemText(0, i + 1, sData);
    }


    for (i = 0; i < SpecRow; i++)
    {
        m_clGridRIThresholdSpec3.SetRowHeight(i, gridHeight);
        m_clGridRIThresholdSpec3.SetItemText(i, 0, pszCol[i]);

        for (j = 0; j < SpecCol; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    m_clGridRIThresholdSpec3.SetColumnWidth(j, gridWidth1);
                }
                else
                {
                    m_clGridRIThresholdSpec3.SetColumnWidth(j, gridWidth2);
                }

                //
            }

            m_clGridRIThresholdSpec3.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }
    }
}
void CCcdRISpecDlg::InitRiThresholdGridCtrl4()
{

    TCHAR* pszCol[] = { _T("RI"), _T("Threshold_Ch1"), _T("Threshold_Ch2"), _T("Threshold_Ch3"), _T("Threshold_Ch4") };
    CString sData;
    CRect rect;
    int i, j;
    int DLG = IDC_STATIC_CCD_RI5_SPEC_GRID_SPEC;

    CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
    int SpecRow = 5;//아래
    int SpecCol = RIThresholdMaxCount;//옆
    int margin = 4;
    int gridHeight = 25;
    int gridWidth1 = 100;
    int gridWidth2 = 50;
    int totalWidth = gridWidth1 + (gridWidth2*(SpecCol - 1));
    //
    pWnd->GetWindowRect(rect);
    ScreenToClient(rect);

    rect.right = totalWidth + margin;
    rect.bottom = (gridHeight*SpecRow) + margin;
    pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.


    GetDlgItem(DLG)->GetWindowRect(rect);
    ScreenToClient(rect);
    m_clGridRIThresholdSpec4.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

    m_clGridRIThresholdSpec4.SetTextBkColor(RGB_COLOR_WHITE);
    m_clGridRIThresholdSpec4.SetFixedBkColor(GRID_COLOR_TITLE);
    m_clGridRIThresholdSpec4.SetFixedTextColor(RGB_COLOR_WHITE);
    m_clGridRIThresholdSpec4.SetReference_Setting();
    m_clGridRIThresholdSpec4.EnableSelection(FALSE);
    m_clGridRIThresholdSpec4.SetRowCount(SpecRow);
    m_clGridRIThresholdSpec4.SetColumnCount(SpecCol);
    m_clGridRIThresholdSpec4.SetFixedRowCount(1);
    m_clGridRIThresholdSpec4.SetFixedColumnCount(1);
    for (i = 0; i < SpecCol; i++)
    {
        sData.Format(_T("ROI%d"), i + 61);
        m_clGridRIThresholdSpec4.SetItemText(0, i + 1, sData);
    }


    for (i = 0; i < SpecRow; i++)
    {
        m_clGridRIThresholdSpec4.SetRowHeight(i, gridHeight);
        m_clGridRIThresholdSpec4.SetItemText(i, 0, pszCol[i]);

        for (j = 0; j < SpecCol; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    m_clGridRIThresholdSpec4.SetColumnWidth(j, gridWidth1);
                }
                else
                {
                    m_clGridRIThresholdSpec4.SetColumnWidth(j, gridWidth2);
                }

                //
            }

            m_clGridRIThresholdSpec4.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }
    }
}
void CCcdRISpecDlg::InitRiThresholdGridCtrl5()
{

    TCHAR* pszCol[] = { _T("RI"), _T("Threshold_Ch1"), _T("Threshold_Ch2"), _T("Threshold_Ch3"), _T("Threshold_Ch4") };
    CString sData;
    CRect rect;
    int i, j;
    int DLG = IDC_STATIC_CCD_RI6_SPEC_GRID_SPEC;

    CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
    int SpecRow = 5;//아래
    int SpecCol = RIThresholdMaxCount;//옆
    int margin = 4;
    int gridHeight = 25;
    int gridWidth1 = 100;
    int gridWidth2 = 50;
    int totalWidth = gridWidth1 + (gridWidth2*(SpecCol - 1));
    //
    pWnd->GetWindowRect(rect);
    ScreenToClient(rect);

    rect.right = totalWidth + margin;
    rect.bottom = (gridHeight*SpecRow) + margin;
    pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.


    GetDlgItem(DLG)->GetWindowRect(rect);
    ScreenToClient(rect);
    m_clGridRIThresholdSpec5.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

    m_clGridRIThresholdSpec5.SetTextBkColor(RGB_COLOR_WHITE);
    m_clGridRIThresholdSpec5.SetFixedBkColor(GRID_COLOR_TITLE);
    m_clGridRIThresholdSpec5.SetFixedTextColor(RGB_COLOR_WHITE);
    m_clGridRIThresholdSpec5.SetReference_Setting();
    m_clGridRIThresholdSpec5.EnableSelection(FALSE);
    m_clGridRIThresholdSpec5.SetRowCount(SpecRow);
    m_clGridRIThresholdSpec5.SetColumnCount(SpecCol);
    m_clGridRIThresholdSpec5.SetFixedRowCount(1);
    m_clGridRIThresholdSpec5.SetFixedColumnCount(1);
    for (i = 0; i < SpecCol; i++)
    {
        sData.Format(_T("ROI%d"), i + 81);
        m_clGridRIThresholdSpec5.SetItemText(0, i + 1, sData);
    }


    for (i = 0; i < SpecRow; i++)
    {
        m_clGridRIThresholdSpec5.SetRowHeight(i, gridHeight);
        m_clGridRIThresholdSpec5.SetItemText(i, 0, pszCol[i]);

        for (j = 0; j < SpecCol; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    m_clGridRIThresholdSpec5.SetColumnWidth(j, gridWidth1);
                }
                else
                {
                    m_clGridRIThresholdSpec5.SetColumnWidth(j, gridWidth2);
                }

                //
            }

            m_clGridRIThresholdSpec5.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }
    }
}
//-----------------------------------------------------------------------------

void CCcdRISpecDlg::InitRIGridCtrl()
{
	TCHAR* pszRow[] = { _T("") , _T("AnSpecPixelCntInBlock"), _T("AnEnableChannel")
        ,_T("AdSpecCenterIntensity1"), _T("AdSpecCenterIntensity2"),_T("AdSpecCenterIntensity3"), _T("AdSpecCenterIntensity4")
		,_T("CornerVariationMin"), _T("CornerVariationMax")
	};

	TCHAR* pszCol[] = { _T("Uniformity"), _T("Spec") };

	CRect rect;
	int i, j;
	int DLG = IDC_STATIC_CCD_RI4_SPEC_GRID_SPEC;

	CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
	int SpecRow = RISpecCount;//아래
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
	m_clGridRI4Spec.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

	m_clGridRI4Spec.SetTextBkColor(RGB_COLOR_WHITE);
	m_clGridRI4Spec.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridRI4Spec.SetFixedTextColor(RGB_COLOR_WHITE);
	m_clGridRI4Spec.SetReference_Setting();
	m_clGridRI4Spec.EnableSelection(FALSE);
	m_clGridRI4Spec.SetRowCount(SpecRow);
	m_clGridRI4Spec.SetColumnCount(SpecCol);
	m_clGridRI4Spec.SetFixedRowCount(1);
	m_clGridRI4Spec.SetFixedColumnCount(1);

	for (i = 0; i < SpecRow; i++)
	{
		m_clGridRI4Spec.SetRowHeight(i, gridHeight);
		m_clGridRI4Spec.SetItemText(i, 0, pszRow[i]);

		for (j = 0; j < SpecCol; j++)
		{
			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridRI4Spec.SetColumnWidth(j, gridWidth1);
				}
				else
				{
					m_clGridRI4Spec.SetColumnWidth(j, gridWidth2);
				}

				m_clGridRI4Spec.SetItemText(i, j, pszCol[j]);
			}

			m_clGridRI4Spec.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}
}
//-----------------------------------------------------------------------------
//
//	유닛 설정
//
//-----------------------------------------------------------------------------
void CCcdRISpecDlg::SetUnit(int nUnit)
{
	m_nUnit = nUnit;
}

//-----------------------------------------------------------------------------
//
//	OnShowWindow
//
//-----------------------------------------------------------------------------
void CCcdRISpecDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (bShow == TRUE)
	{
		this->ShowRISpec();
        this->ShowRIThresholdSpec();
	}
}

//-----------------------------------------------------------------------------
//
//	SFR SPEC 데이터 표시
//
//-----------------------------------------------------------------------------
void CCcdRISpecDlg::ShowRIThresholdSpec()
{
    TCHAR szData[SIZE_OF_100BYTE];
    int i = 0;
    int j = 0;

    int _x = 0;
    int _y = 0;
    RiThresholdGridCount = 0;
    for (i = 0; i < RIThresholdMaxCount - 1; i++)
    {
        m_clGridRIThresholdSpec1.SetItemText(1, i + 1, model.m_RirOI[RiThresholdGridCount][4], 3);
        m_clGridRIThresholdSpec1.SetItemText(2, i + 1, model.m_RirOI[RiThresholdGridCount][5], 3);
        m_clGridRIThresholdSpec1.SetItemText(3, i + 1, model.m_RirOI[RiThresholdGridCount][6], 3);
        m_clGridRIThresholdSpec1.SetItemText(4, i + 1, model.m_RirOI[RiThresholdGridCount][7], 3);
        RiThresholdGridCount++;
    }
    for (i = 0; i < RIThresholdMaxCount - 1; i++)
    {
        m_clGridRIThresholdSpec2.SetItemText(1, i + 1, model.m_RirOI[RiThresholdGridCount][4], 3);
        m_clGridRIThresholdSpec2.SetItemText(2, i + 1, model.m_RirOI[RiThresholdGridCount][5], 3);
        m_clGridRIThresholdSpec2.SetItemText(3, i + 1, model.m_RirOI[RiThresholdGridCount][6], 3);
        m_clGridRIThresholdSpec2.SetItemText(4, i + 1, model.m_RirOI[RiThresholdGridCount][7], 3);
        RiThresholdGridCount++;
    }
    for (i = 0; i < RIThresholdMaxCount - 1; i++)
    {
        m_clGridRIThresholdSpec3.SetItemText(1, i + 1, model.m_RirOI[RiThresholdGridCount][4], 3);
        m_clGridRIThresholdSpec3.SetItemText(2, i + 1, model.m_RirOI[RiThresholdGridCount][5], 3);
        m_clGridRIThresholdSpec3.SetItemText(3, i + 1, model.m_RirOI[RiThresholdGridCount][6], 3);
        m_clGridRIThresholdSpec3.SetItemText(4, i + 1, model.m_RirOI[RiThresholdGridCount][7], 3);
        RiThresholdGridCount++;
    }
    for (i = 0; i < RIThresholdMaxCount - 1; i++)
    {
        m_clGridRIThresholdSpec4.SetItemText(1, i + 1, model.m_RirOI[RiThresholdGridCount][4], 3);
        m_clGridRIThresholdSpec4.SetItemText(2, i + 1, model.m_RirOI[RiThresholdGridCount][5], 3);
        m_clGridRIThresholdSpec4.SetItemText(3, i + 1, model.m_RirOI[RiThresholdGridCount][6], 3);
        m_clGridRIThresholdSpec4.SetItemText(4, i + 1, model.m_RirOI[RiThresholdGridCount][7], 3);
        RiThresholdGridCount++;
    }
    for (i = 0; i < RIThresholdMaxCount - 1; i++)
    {
        m_clGridRIThresholdSpec5.SetItemText(1, i + 1, model.m_RirOI[RiThresholdGridCount][4], 3);
        m_clGridRIThresholdSpec5.SetItemText(2, i + 1, model.m_RirOI[RiThresholdGridCount][5], 3);
        m_clGridRIThresholdSpec5.SetItemText(3, i + 1, model.m_RirOI[RiThresholdGridCount][6], 3);
        m_clGridRIThresholdSpec5.SetItemText(4, i + 1, model.m_RirOI[RiThresholdGridCount][7], 3);
        RiThresholdGridCount++;
    }




    m_clGridRIThresholdSpec1.Invalidate();
    m_clGridRIThresholdSpec2.Invalidate();
    m_clGridRIThresholdSpec3.Invalidate();
    m_clGridRIThresholdSpec4.Invalidate();
    m_clGridRIThresholdSpec5.Invalidate();
}

//-----------------------------------------------------------------------------
//
//	SFR 데이터 -> 메모리에 저장
//
//-----------------------------------------------------------------------------
void CCcdRISpecDlg::GetRIThresholdSpec()
{
    CString sData = _T("");
    int i;
    RiThresholdGridCount = 0;
    //g_clModelData[m_nUnit].m_RISpec[_x][_y] = _ttof((TCHAR*)(LPCTSTR)sData);
    for (i = 0; i < RIThresholdMaxCount - 1; i++)
    {
        sData = m_clGridRIThresholdSpec1.GetItemText(1, i + 1);
        model.m_RirOI[RiThresholdGridCount][4] = _ttof((TCHAR*)(LPCTSTR)sData);
        sData = m_clGridRIThresholdSpec1.GetItemText(2, i + 1);
        model.m_RirOI[RiThresholdGridCount][5] = _ttof((TCHAR*)(LPCTSTR)sData);
        sData = m_clGridRIThresholdSpec1.GetItemText(3, i + 1);
        model.m_RirOI[RiThresholdGridCount][6] = _ttof((TCHAR*)(LPCTSTR)sData);
        sData = m_clGridRIThresholdSpec1.GetItemText(4, i + 1);
        model.m_RirOI[RiThresholdGridCount][7] = _ttof((TCHAR*)(LPCTSTR)sData);
        RiThresholdGridCount++;
    }
    for (i = 0; i < RIThresholdMaxCount - 1; i++)
    {
        sData = m_clGridRIThresholdSpec2.GetItemText(1, i + 1);
        model.m_RirOI[RiThresholdGridCount][4] = _ttof((TCHAR*)(LPCTSTR)sData);
        sData = m_clGridRIThresholdSpec2.GetItemText(2, i + 1);
        model.m_RirOI[RiThresholdGridCount][5] = _ttof((TCHAR*)(LPCTSTR)sData);
        sData = m_clGridRIThresholdSpec2.GetItemText(3, i + 1);
        model.m_RirOI[RiThresholdGridCount][6] = _ttof((TCHAR*)(LPCTSTR)sData);
        sData = m_clGridRIThresholdSpec2.GetItemText(4, i + 1);
        model.m_RirOI[RiThresholdGridCount][7] = _ttof((TCHAR*)(LPCTSTR)sData);
        RiThresholdGridCount++;
    }
    for (i = 0; i < RIThresholdMaxCount - 1; i++)
    {
        sData = m_clGridRIThresholdSpec3.GetItemText(1, i + 1);
        model.m_RirOI[RiThresholdGridCount][4] = _ttof((TCHAR*)(LPCTSTR)sData);
        sData = m_clGridRIThresholdSpec3.GetItemText(2, i + 1);
        model.m_RirOI[RiThresholdGridCount][5] = _ttof((TCHAR*)(LPCTSTR)sData);
        sData = m_clGridRIThresholdSpec3.GetItemText(3, i + 1);
        model.m_RirOI[RiThresholdGridCount][6] = _ttof((TCHAR*)(LPCTSTR)sData);
        sData = m_clGridRIThresholdSpec3.GetItemText(4, i + 1);
        model.m_RirOI[RiThresholdGridCount][7] = _ttof((TCHAR*)(LPCTSTR)sData);
        RiThresholdGridCount++;
    }
    for (i = 0; i < RIThresholdMaxCount - 1; i++)
    {
        sData = m_clGridRIThresholdSpec4.GetItemText(1, i + 1);
        model.m_RirOI[RiThresholdGridCount][4] = _ttof((TCHAR*)(LPCTSTR)sData);
        sData = m_clGridRIThresholdSpec4.GetItemText(2, i + 1);
        model.m_RirOI[RiThresholdGridCount][5] = _ttof((TCHAR*)(LPCTSTR)sData);
        sData = m_clGridRIThresholdSpec4.GetItemText(3, i + 1);
        model.m_RirOI[RiThresholdGridCount][6] = _ttof((TCHAR*)(LPCTSTR)sData);
        sData = m_clGridRIThresholdSpec4.GetItemText(4, i + 1);
        model.m_RirOI[RiThresholdGridCount][7] = _ttof((TCHAR*)(LPCTSTR)sData);
        RiThresholdGridCount++;
    }
    for (i = 0; i < RIThresholdMaxCount - 1; i++)
    {
        sData = m_clGridRIThresholdSpec5.GetItemText(1, i + 1);
        model.m_RirOI[RiThresholdGridCount][4] = _ttof((TCHAR*)(LPCTSTR)sData);
        sData = m_clGridRIThresholdSpec5.GetItemText(2, i + 1);
        model.m_RirOI[RiThresholdGridCount][5] = _ttof((TCHAR*)(LPCTSTR)sData);
        sData = m_clGridRIThresholdSpec5.GetItemText(3, i + 1);
        model.m_RirOI[RiThresholdGridCount][6] = _ttof((TCHAR*)(LPCTSTR)sData);
        sData = m_clGridRIThresholdSpec5.GetItemText(4, i + 1);
        model.m_RirOI[RiThresholdGridCount][7] = _ttof((TCHAR*)(LPCTSTR)sData);
        RiThresholdGridCount++;
    }
    //g_clSysData.Save();
}

//-----------------------------------------------------------------------------
//
//	SFR SPEC 데이터 표시
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//
//	UNIFORMITY SPEC 데이터 표시
//
//-----------------------------------------------------------------------------
void CCcdRISpecDlg::ShowRISpec()
{
	TCHAR szData[SIZE_OF_100BYTE];
	int i;

	for (i = 0; i < RISpecCount -1; i++)
	{

		m_clGridRI4Spec.SetItemText(i + 1, 1, model.m_RISpec[i], 3);
	}
	m_clGridRI4Spec.Invalidate();
}
//-----------------------------------------------------------------------------
//
//	SFR 데이터 -> 메모리에 저장
//
//-----------------------------------------------------------------------------

void CCcdRISpecDlg::GetRISpec()
{
	CString sData = _T("");
	int i;

	for (i = 0; i < RISpecCount - 1; i++)
	{
		sData = m_clGridRI4Spec.GetItemText(i + 1, 1);
		model.m_RISpec[i] = _ttof((TCHAR*)(LPCTSTR)sData);
	}
	//g_clSysData.Save();
}
//-----------------------------------------------------------------------------
//
//	CENTER SFR LIMIT
//
//-----------------------------------------------------------------------------
void CCcdRISpecDlg::OnStnClickedStaticCcdSfrSpecCenterSfrLimitVal()
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
void CCcdRISpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrLimitVal()
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
void CCcdRISpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrDeviationLimitVal()
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
void CCcdRISpecDlg::OnStnClickedStaticCcdSfrSpecOcXyVal()
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
void CCcdRISpecDlg::OnStnClickedStaticCcdSfrSpecOcThVal()
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
void CCcdRISpecDlg::OnBnClickedButtonCcdSfrSpecSave()
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
	sTemp.Format("RI SPEC 데이터를 저장하시겠습니까?");
	if (!askMsg(sTemp))return;

	//if (g_ShowMsgModal(_T("확인"), _T("DEFECT/UNIFORM SPEC 데이터를 저장하시겠습니까?"), RGB_COLOR_BLUE) == false)
		//return;


	this->GetRISpec();

    this->GetRIThresholdSpec();

	//g_clSysData.Save();
	//g_clMandoSfrSpec[m_nUnit].Save();
	model.AcmisDataSave();
	theApp.MainDlg->putListLog(_T("[INFO] DEFECT/UNIFORM SPEC 저장"));// , 0, m_nUnit);
}

//-----------------------------------------------------------------------------
//
//	버튼 : CLOSE
//
//-----------------------------------------------------------------------------
void CCcdRISpecDlg::OnBnClickedButtonCcdSfrSpecClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ShowWindow(SW_HIDE);
}

//-----------------------------------------------------------------------------
//
//	그리드 컨트롤 더블 클릭
//
//-----------------------------------------------------------------------------
void CCcdRISpecDlg::OnNMDblClickedRi1Spec(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
	CString sData = _T("");
	int nRow, nCol;

	nRow = pNMGridView->iRow;
	nCol = pNMGridView->iColumn;

	if (nRow >= 1 && nCol >= 1)
	{
		sData = m_clGridRIThresholdSpec1.GetItemText(nRow, nCol);
		CKeyPadDlg keyDlg;
		if (keyDlg.DoModal() == IDOK)
		{
			sData.Format(_T("%s"), keyDlg.GetstrKeypad());
            m_clGridRIThresholdSpec1.SetItemText(nRow, nCol, sData);

            m_clGridRIThresholdSpec1.Invalidate();
		}

	}
}

void CCcdRISpecDlg::OnNMDblClickedRi2Spec(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
	CString sData = _T("");
	int nRow, nCol;

	nRow = pNMGridView->iRow;
	nCol = pNMGridView->iColumn;

	if (nRow >= 1 && nCol >= 1)
	{
		sData = m_clGridRIThresholdSpec2.GetItemText(nRow, nCol);
		CKeyPadDlg keyDlg;
		if (keyDlg.DoModal() == IDOK)
		{
			sData.Format(_T("%s"), keyDlg.GetstrKeypad());
            m_clGridRIThresholdSpec2.SetItemText(nRow, nCol, sData);

            m_clGridRIThresholdSpec2.Invalidate();
		}

	}
}

void CCcdRISpecDlg::OnNMDblClickedRi3Spec(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
	CString sData = _T("");
	int nRow, nCol;

	nRow = pNMGridView->iRow;
	nCol = pNMGridView->iColumn;

	if (nRow >= 1 && nCol >= 1)
	{
		sData = m_clGridRIThresholdSpec3.GetItemText(nRow, nCol);
		CKeyPadDlg keyDlg;
		if (keyDlg.DoModal() == IDOK)
		{
			sData.Format(_T("%s"), keyDlg.GetstrKeypad());
            m_clGridRIThresholdSpec3.SetItemText(nRow, nCol, sData);

            m_clGridRIThresholdSpec3.Invalidate();
		}


	}
}

void CCcdRISpecDlg::OnNMDblClickedRi4Spec(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
	CString sData = _T("");
	int nRow, nCol;

	nRow = pNMGridView->iRow;
	nCol = pNMGridView->iColumn;

	if (nRow >= 1 && nCol >= 1)
	{
		sData = m_clGridRI4Spec.GetItemText(nRow, nCol);
		CKeyPadDlg keyDlg;
		if (keyDlg.DoModal() == IDOK)
		{
			sData.Format(_T("%s"), keyDlg.GetstrKeypad());
			m_clGridRI4Spec.SetItemText(nRow, nCol, sData);

			m_clGridRI4Spec.Invalidate();
		}
	}
}


void CCcdRISpecDlg::OnNMDblClickedRi5Spec(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
    CString sData = _T("");
    int nRow, nCol;

    nRow = pNMGridView->iRow;
    nCol = pNMGridView->iColumn;

    if (nRow >= 1 && nCol >= 1)
    {
        sData = m_clGridRIThresholdSpec4.GetItemText(nRow, nCol);
        CKeyPadDlg keyDlg;
        if (keyDlg.DoModal() == IDOK)
        {
            sData.Format(_T("%s"), keyDlg.GetstrKeypad());
            m_clGridRIThresholdSpec4.SetItemText(nRow, nCol, sData);

            m_clGridRIThresholdSpec4.Invalidate();
        }
    }
}

void CCcdRISpecDlg::OnNMDblClickedRi6Spec(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
    CString sData = _T("");
    int nRow, nCol;

    nRow = pNMGridView->iRow;
    nCol = pNMGridView->iColumn;

    if (nRow >= 1 && nCol >= 1)
    {
        sData = m_clGridRIThresholdSpec5.GetItemText(nRow, nCol);
        CKeyPadDlg keyDlg;
        if (keyDlg.DoModal() == IDOK)
        {
            sData.Format(_T("%s"), keyDlg.GetstrKeypad());
            m_clGridRIThresholdSpec5.SetItemText(nRow, nCol, sData);

            m_clGridRIThresholdSpec5.Invalidate();
        }


    }
}
//-----------------------------------------------------------------------------
//
//	OnLButtonDown
//
//-----------------------------------------------------------------------------
void CCcdRISpecDlg::OnLButtonDown(UINT nFlags, CPoint point)
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
BOOL CCcdRISpecDlg::PreTranslateMessage(MSG* pMsg)
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