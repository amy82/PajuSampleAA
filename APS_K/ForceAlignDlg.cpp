// ForceAlignDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ForceAlignDlg.h"

#define MARK_SIZE	600

// CForceAlignDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CForceAlignDlg, CDialogEx)

CForceAlignDlg::CForceAlignDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CForceAlignDlg::IDD, pParent)
{
	m_iCamNo = 0;
	m_iMarkType = 0;
	m_iMoveSpeed = 10;
	SetMarkPosition(512, 384);
}

CForceAlignDlg::~CForceAlignDlg()
{
}

void CForceAlignDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LABEL_TITLE, m_labelTitle);
	DDX_Control(pDX, IDC_BUTTON_BOX_LEFT, m_btn_BoxLeft);
	DDX_Control(pDX, IDC_BUTTON_BOX_UP, m_btn_BoxUP);
	DDX_Control(pDX, IDC_BUTTON_BOX_RIGHT, m_btn_BoxRight);
	DDX_Control(pDX, IDC_BUTTON_BOX_DOWN, m_btn_BoxDown);
}


BEGIN_MESSAGE_MAP(CForceAlignDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_BOX_UP, &CForceAlignDlg::OnBnClickedButtonBoxUp)
	ON_BN_CLICKED(IDC_BUTTON_BOX_LEFT, &CForceAlignDlg::OnClickedButtonBoxLeft)
	ON_BN_CLICKED(IDC_BUTTON_BOX_RIGHT, &CForceAlignDlg::OnClickedButtonBoxRight)
	ON_BN_CLICKED(IDC_BUTTON_BOX_DOWN, &CForceAlignDlg::OnBnClickedButtonBoxDown)
	ON_BN_CLICKED(IDC_BUTTON_BOX_SPEED, &CForceAlignDlg::OnBnClickedButtonBoxSpeed)
	ON_BN_CLICKED(IDC_BUTTON_FORCR_ALIGN, &CForceAlignDlg::OnBnClickedButtonForcrAlign)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CForceAlignDlg 메시지 처리기입니다.


BOOL CForceAlignDlg::OnInitDialog()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	WINDOWPLACEMENT wndpl;
	wndpl.rcNormalPosition = pFrame->m_rectCamDispPos2;
	wndpl.rcNormalPosition.top += (SMALL_CAM_SIZE_Y + 10);
	wndpl.rcNormalPosition.bottom += (SMALL_CAM_SIZE_Y + 50);

	this->MoveWindow(&wndpl.rcNormalPosition);

	m_labelTitle
		.SetBkColor(M_COLOR_WHITE)
		.SetTextColor(M_COLOR_BLUE)
		.SetFontBold(TRUE)
		.SetFontSize(24);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CForceAlignDlg::OnBnClickedButtonBoxUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_rcMark.top -= m_iMoveSpeed;
	m_rcMark.bottom -= m_iMoveSpeed;
	if(m_rcMark.top < 1){
		m_rcMark.top = 1;
		m_rcMark.bottom = m_rcMark.top + MARK_SIZE;
	}

	DrawMark();
}


void CForceAlignDlg::OnClickedButtonBoxLeft()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_rcMark.left -= m_iMoveSpeed;
	m_rcMark.right -= m_iMoveSpeed;
	if(m_rcMark.left < 1){
		m_rcMark.left = 1;
		m_rcMark.right = m_rcMark.left + MARK_SIZE;
	}

	DrawMark();
}


void CForceAlignDlg::OnClickedButtonBoxRight()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_rcMark.left += m_iMoveSpeed;
	m_rcMark.right += m_iMoveSpeed;
	if(m_rcMark.right > CAM_SIZE_X-1){
		m_rcMark.right = CAM_SIZE_X-1;
		m_rcMark.left = m_rcMark.right - MARK_SIZE;
	}

	m_poCenter.x += m_iMoveSpeed;
	if(m_poCenter.x > CAM_SIZE_X-1)
		m_poCenter.x = CAM_SIZE_X-1;

	DrawMark();
}


void CForceAlignDlg::OnBnClickedButtonBoxDown()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_rcMark.top += m_iMoveSpeed;
	m_rcMark.bottom += m_iMoveSpeed;
	if(m_rcMark.bottom > CAM_SIZE_Y-1){
		m_rcMark.bottom = CAM_SIZE_Y-1;
		m_rcMark.top = m_rcMark.bottom - MARK_SIZE;
	}

	DrawMark();
}


void CForceAlignDlg::OnBnClickedButtonBoxSpeed()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTemp;
	GetDlgItem(IDC_BUTTON_BOX_SPEED)->GetWindowText(strTemp);

	if (strTemp=="10")
	{
		m_iMoveSpeed = 1;
		GetDlgItem(IDC_BUTTON_BOX_SPEED)->SetWindowText("1");
	}
	else
	{
		m_iMoveSpeed = 10;
		GetDlgItem(IDC_BUTTON_BOX_SPEED)->SetWindowText("10");
	}
}


void CForceAlignDlg::SetCamNo(int iCamNo, int iMarkType)
{
	m_iCamNo = iCamNo;
	m_iMarkType = iMarkType;
}


void CForceAlignDlg::SetMarkPosition(int x, int y)
{
	m_poCenter = CPoint(x, y);
	m_rcMark = CRect((m_poCenter.x - (MARK_SIZE>>1)), (m_poCenter.y - (MARK_SIZE>>1)), (m_poCenter.x + (MARK_SIZE>>1)), (m_poCenter.y + (MARK_SIZE>>1)));
}


void CForceAlignDlg::SetMarkPosition(CPoint p)
{
	m_poCenter = p;
	m_rcMark = CRect((m_poCenter.x - (MARK_SIZE>>1)), (m_poCenter.y - (MARK_SIZE>>1)), (m_poCenter.x + (MARK_SIZE>>1)), (m_poCenter.y + (MARK_SIZE>>1)));
}


void CForceAlignDlg::DrawMark(bool bDrawComplete)
{
	if((0 > m_iCamNo) || (m_iCamNo > CAM2)){
		AfxMessageBox("CForceAlignDlg::DrawMark CamNo Error, Call Programer");
		return;
	}
	if( (m_iMarkType < 0)  || (m_iMarkType > LENS_Align_MARK) )
	{
		sLangChange.LoadStringA(IDS_STRING462);	//CForceAlignDlg::DrawMark Mark Type 이상, 셋업자 호출
		AfxMessageBox(sLangChange);
		return;
	}
	
	COLORREF colorOverlay;

	if( bDrawComplete == false )	colorOverlay = 	M_COLOR_RED;
	else							colorOverlay = 	M_COLOR_GREEN;

	vision.clearOverlay(m_iCamNo);
	vision.crosslist[m_iCamNo].addList(m_rcMark.CenterPoint(), (MARK_SIZE>>1)-20, colorOverlay);
	vision.boxlist[m_iCamNo].addList(m_rcMark, PS_DOT, colorOverlay);
	vision.drawOverlay(m_iCamNo, false, false);
}

void CForceAlignDlg::OnBnClickedButtonForcrAlign()
{
	if((0 > m_iCamNo) || (m_iCamNo > CAM2))
	{
		sLangChange.LoadStringA(IDS_STRING1442);	//프로그램 카메라 번호 이상. (개발자에게 문의하세요.)
		errMsg2(Task.AutoFlag, sLangChange);
		return;
	}
	if( (m_iMarkType < 0)  || (m_iMarkType > LENS_Align_MARK) )
	{
		AfxMessageBox("CForceAlignDlg::DrawMark Mark Type Error, Call Programer");
		return;
	}

	if (vision.getLiveMode())
		vision.getSnapImage(m_iCamNo);

	bool bRtn = vision.markRegist(m_iCamNo, m_iMarkType, 1, m_rcMark);

	if (!bRtn)
	{
		sLangChange.LoadStringA(IDS_STRING1213);	//마크 등록 실패.
		::errMsg2(Task.AutoFlag, sLangChange);
		return;
	}

	model.m_MarkSize[m_iMarkType][1].x = m_rcMark.Width();
	model.m_MarkSize[m_iMarkType][1].y = m_rcMark.Height();

	double dZoomX = (double)MARK_SIZE_X/(double)m_rcMark.Width();
	double dZoomY = (double)MARK_SIZE_Y/(double)m_rcMark.Height();

	MmodDraw(M_DEFAULT, vision.ModModel[m_iMarkType][1], vision.MilMarkImage[m_iMarkType][1], M_DRAW_IMAGE, M_DEFAULT, M_DEFAULT);
	MimResize(vision.MilMarkImage[m_iMarkType][1], vision.MilMarkSmallImage[m_iMarkType][1], dZoomX, dZoomY, M_DEFAULT);
	
	vision.geometricMarkPreProc(m_iCamNo, m_iMarkType, 1);

	model.Save();

	DrawMark(true);
	m_labelTitle.SetBkColor(M_COLOR_GREEN);
	
}


void CForceAlignDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(bShow == false)
		return;
	
	DrawMark();
}
