// MarkSetDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MarkSetDlg.h"

// CMarkSetDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMarkSetDlg, CDialogEx)

CMarkSetDlg::CMarkSetDlg(int iCamNo, int iMarkType, int iMarkNo, int iSizeX, int iSizeY, bool bFirst, CWnd* pParent /*=NULL*/)
	: CDialogEx(CMarkSetDlg::IDD, pParent)
{
	m_iCamNo = iCamNo;
	m_iMarkType = iMarkType;
	m_iMarkNo = iMarkNo;
	m_iSizeX = iSizeX;
	m_iSizeY = iSizeY;

	m_iSelMoveType = 0;
	m_iSelDrawType = 0;
	bFirstMark = bFirst;
}

CMarkSetDlg::~CMarkSetDlg()
{
}

void CMarkSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_MOVETYPE1, m_iSelMoveType);
	DDX_Control(pDX, IDC_LABEL_SIZE_PEN, m_labelPenSize);
	DDX_Radio(pDX, IDC_RADIO_CENTER, m_iSelDrawType);
}


BEGIN_MESSAGE_MAP(CMarkSetDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMarkSetDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMarkSetDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_RADIO_MOVETYPE1, &CMarkSetDlg::OnBnClickedRadioMovetype1)
	ON_BN_CLICKED(IDC_RADIO_MOVETYPE2, &CMarkSetDlg::OnBnClickedRadioMovetype2)
	ON_BN_CLICKED(IDC_BUTTON_BOX_UP, &CMarkSetDlg::OnBnClickedButtonBoxUp)
	ON_BN_CLICKED(IDC_BUTTON_BOX_DOWN, &CMarkSetDlg::OnBnClickedButtonBoxDown)
	ON_BN_CLICKED(IDC_BUTTON_BOX_LEFT, &CMarkSetDlg::OnBnClickedButtonBoxLeft)
	ON_BN_CLICKED(IDC_BUTTON_BOX_RIGHT, &CMarkSetDlg::OnBnClickedButtonBoxRight)
	ON_BN_CLICKED(IDC_BUTTON_BOX_SPEED, &CMarkSetDlg::OnBnClickedButtonBoxSpeed)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
//	ON_WM_MBUTTONDOWN()
ON_WM_MOUSEMOVE()
ON_BN_CLICKED(IDC_RADIO_CENTER, &CMarkSetDlg::OnBnClickedRadioCenter)
ON_BN_CLICKED(IDC_RADIO_MASK, &CMarkSetDlg::OnBnClickedRadioMask)
ON_BN_CLICKED(IDC_BUTTON_CLEAR_MASK, &CMarkSetDlg::OnBnClickedButtonClearMask)
ON_BN_CLICKED(IDC_BUTTON_CLEAR_MASK2, &CMarkSetDlg::OnBnClickedButtonClearMask2)
ON_STN_CLICKED(IDC_LABEL_SIZE_PEN, &CMarkSetDlg::OnStnClickedLabelSizePen)
END_MESSAGE_MAP()


// CMarkSetDlg 메시지 처리기입니다.
BOOL CMarkSetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	WINDOWPLACEMENT wndpl;

	GetDlgItem(IDC_DISP_MARKSET)->GetWindowPlacement(&wndpl);
	m_iMarkSetSizeX = wndpl.rcNormalPosition.right - wndpl.rcNormalPosition.left;
	m_iMarkSetSizeY = wndpl.rcNormalPosition.bottom - wndpl.rcNormalPosition.top;

	m_rcDispWin = wndpl.rcNormalPosition;

	vision.InitMarkSetDisplay(m_iMarkSetSizeX, m_iMarkSetSizeY);

	CWnd* pWnd;
	pWnd = (CWnd*)GetDlgItem(IDC_DISP_MARKSET);
	MdispSelectWindow(vision.MilMarkSetDisplay, vision.MilMarkSetImage, pWnd->m_hWnd);

	vision.enableMarkSetOverlay();

	m_dZoomX = (double)m_iMarkSetSizeX/(double)m_iSizeX;
	m_dZoomY = (double)m_iMarkSetSizeY/(double)m_iSizeY;

	if(m_iCamNo != CCD)	// CCD일 경우 패턴 매칭용으로 생각하고 마스크 관련 아이템들 숨김
	{

		MmodControl(vision.ModModel[m_iMarkType][m_iMarkNo], M_DEFAULT, M_DRAW_SCALE_X, m_dZoomX);
		MmodControl(vision.ModModel[m_iMarkType][m_iMarkNo], M_DEFAULT, M_DRAW_SCALE_Y, m_dZoomY);

		MgraColor(M_DEFAULT, M_COLOR_GREEN);
		//MmodDraw(M_DEFAULT, vision.ModModel[m_iMarkType][m_iMarkNo], vision.MilMarkSetImage, M_DRAW_IMAGE+M_DRAW_EDGES, M_DEFAULT, M_DEFAULT);
		MmodDraw(M_DEFAULT, vision.ModModel[m_iMarkType][m_iMarkNo], vision.MilMarkSetImage, M_DRAW_IMAGE, M_DEFAULT, M_DEFAULT);

		//MgraColor(M_DEFAULT, M_COLOR_GREEN);
	//	MimResize(vision.MilTempImage, vision.MilMarkSetImage, m_dZoomX, m_dZoomY, M_DEFAULT);

	#ifdef USE_GEOMETRIC
		MmodInquire(vision.ModModel[m_iMarkType][m_iMarkNo], M_DEFAULT, M_REFERENCE_X+M_TYPE_DOUBLE, &m_Center.x);
		MmodInquire(vision.ModModel[m_iMarkType][m_iMarkNo], M_DEFAULT, M_REFERENCE_Y+M_TYPE_DOUBLE, &m_Center.y);
	#else
		MpatInquire(vision.PatModel[m_iMarkType][m_iMarkNo], M_CENTER_X, &m_Center.x);
		MpatInquire(vision.PatModel[m_iMarkType][m_iMarkNo], M_CENTER_Y, &m_Center.y);
	#endif

		//MbufAllocColor(vision.MilSystem, 1, m_iSizeX, m_iSizeY, M_DEF_IMAGE_TYPE, M_IMAGE+M_DISP,&vision.MilMask);
		MbufAllocColor(vision.MilSystem, 1, m_iSizeX, m_iSizeY, M_DEF_IMAGE_TYPE, M_IMAGE + M_DISP + M_PROC, &vision.MilMask);
		vision.hMaskBuf = GlobalAlloc( GMEM_FIXED | GMEM_ZEROINIT, m_iSizeX*m_iSizeY);
		if (vision.hMaskBuf)
		{
			vision.ucMaskBuf = (unsigned char *)GlobalLock(vision.hMaskBuf);
			::memset(vision.ucMaskBuf,0x00,(m_iSizeX*m_iSizeY));
		}
		else 
		{
			AfxMessageBox("Memory Allocation Error...[Mask Buffer Error]");	
		}

		drawLine(m_Center);


		m_bDrawMask = false;
		m_iSize_MaskPen = 10;

		m_labelPenSize
			.SetBkColor(M_COLOR_WHITE)
			.SetText("10")
			.SetFontBold(TRUE)
			.SetFontSize(17)
			.SetTextColor(M_COLOR_BLACK);

		m_iMoveSpeed = 10;

		MgraColor(M_DEFAULT, M_COLOR_YELLOW); 
		MmodDraw(M_DEFAULT, vision.ModModel[m_iMarkType][m_iMarkNo], vision.MilMarkSetOverlayImage, M_DRAW_EDGES, M_DEFAULT, M_DEFAULT);//마크이미지 표시 변경

		MmodDraw(M_DEFAULT, vision.ModModel[m_iMarkType][m_iMarkNo], vision.MilMarkSetOverlayImage, M_DRAW_DONT_CARES, M_DEFAULT, M_DEFAULT);
	}
	else if(m_iCamNo == CCD)	// CCD일 경우 패턴 매칭용으로 생각하고 마스크 관련 아이템들 숨김
	{
		
	}

	LoadMarkImg();

	if(bFirstMark == true)	OnBnClickedButtonClearMask();	//마크 초기 등록일 경우 Overlay 초기화

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CMarkSetDlg::OnBnClickedOk()
{
	if(m_iCamNo != CCD)
	{
	#ifdef USE_GEOMETRIC
		MmodControl(vision.ModModel[m_iMarkType][m_iMarkNo], M_DEFAULT, M_REFERENCE_X, m_Center.x);
		MmodControl(vision.ModModel[m_iMarkType][m_iMarkNo], M_DEFAULT, M_REFERENCE_Y, m_Center.y);

		MmodControl(vision.ModModel[m_iMarkType][m_iMarkNo], M_DEFAULT, M_DRAW_SCALE_X, 1.0);
		MmodControl(vision.ModModel[m_iMarkType][m_iMarkNo], M_DEFAULT, M_DRAW_SCALE_Y, 1.0);
	#else
		MpatSetCenter(vision.PatModel[m_iMarkType][m_iMarkNo], m_Center.x, m_Center.y);
	#endif

		MbufClear(vision.MilMask, 0x00);
		MbufPut(vision.MilMask, vision.ucMaskBuf);
		SaveMarkImg();

		MmodMask(vision.ModModel[m_iMarkType][m_iMarkNo], M_DEFAULT, vision.MilMask, M_DONT_CARES, M_DEFAULT);
		MmodPreprocess(vision.ModModel[m_iMarkType][m_iMarkNo], M_DEFAULT);
	}
	else
	{
		MpatSetCenter(vision.FieldPatternImage[m_iMarkType], m_Center.x, m_Center.y);
	}
	vision.CloseMarkSetDisplay();

	MbufFree(vision.MilMask);
	vision.MilMask = M_NULL;
	GlobalFree(vision.hMaskBuf);
	vision.hMaskBuf = NULL;

	CDialogEx::OnOK();
}


void CMarkSetDlg::OnBnClickedCancel()
{
	vision.CloseMarkSetDisplay();
	model.loadMark(m_iCamNo, m_iMarkType, m_iMarkNo);

	MmodControl(vision.ModModel[m_iMarkType][m_iMarkNo], M_DEFAULT, M_DRAW_SCALE_X, 1.0);
	MmodControl(vision.ModModel[m_iMarkType][m_iMarkNo], M_DEFAULT, M_DRAW_SCALE_Y, 1.0);

	MbufFree(vision.MilMask);
	vision.MilMask = M_NULL;
	GlobalFree(vision.hMaskBuf);
	vision.hMaskBuf = NULL;

	CDialogEx::OnCancel();
}


void CMarkSetDlg::drawLine(CDPoint p)
{
	MbufClear(vision.MilMarkSetOverlayImage, vision.MarkSetTransparentColor);

	MgraColor(M_DEFAULT, M_COLOR_RED);
	MgraLine(M_DEFAULT, vision.MilMarkSetOverlayImage, (int)(p.x*m_dZoomX+0.5), 0, (int)(p.x*m_dZoomX+0.5), m_iMarkSetSizeY);
	MgraLine(M_DEFAULT, vision.MilMarkSetOverlayImage, 0, (int)(p.y*m_dZoomY+0.5), m_iMarkSetSizeX, (int)(p.y*m_dZoomY+0.5));

	m_iSelDrawType = 0;

	UpdateData(false);
}

void CMarkSetDlg::OnBnClickedRadioMovetype1()
{
	UpdateData(true);

	m_iSelDrawType = 0;

	UpdateData(false);
}


void CMarkSetDlg::OnBnClickedRadioMovetype2()
{
	UpdateData(true);

	m_iSelDrawType = 0;

	UpdateData(false);
}


void CMarkSetDlg::OnBnClickedButtonBoxUp()
{
	m_Center.y -= m_iMoveSpeed;

	drawLine(m_Center);
}


void CMarkSetDlg::OnBnClickedButtonBoxDown()
{
	m_Center.y += m_iMoveSpeed;

	drawLine(m_Center);
}


void CMarkSetDlg::OnBnClickedButtonBoxLeft()
{
	m_Center.x -= m_iMoveSpeed;

	drawLine(m_Center);
}


void CMarkSetDlg::OnBnClickedButtonBoxRight()
{
	m_Center.x += m_iMoveSpeed;

	drawLine(m_Center);
}


void CMarkSetDlg::OnBnClickedButtonBoxSpeed()
{
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


void CMarkSetDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if ( point.x > m_rcDispWin.left		&&
		 point.x < m_rcDispWin.right	&&
		 point.y > m_rcDispWin.top		&&
		 point.y < m_rcDispWin.bottom )
	{
		m_ClickP = point;

		if ( m_iSelDrawType == 1 )
		{
			m_bDrawMask = true;

			drawMaskPen(m_ClickP);
		}
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMarkSetDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bDrawMask = false;

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMarkSetDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if(!(nFlags & 0x01))
	{
		m_bDrawMask = false;
	}

	if ( point.x > m_rcDispWin.left		&&
		 point.x < m_rcDispWin.right	&&
		 point.y > m_rcDispWin.top		&&
		 point.y < m_rcDispWin.bottom )
	{
		if ( m_bDrawMask == true )
		{
 			m_MoveP.x = m_ClickP.x - point.x;
 			m_MoveP.y = m_ClickP.y - point.y;

			drawMaskPen(point);
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CMarkSetDlg::drawMaskPen(CPoint p)
{
	updateMaskPenSize();

	m_rcMask.left		= (int)(p.x - m_iSize_MaskPen - m_rcDispWin.left);
	m_rcMask.top		= (int)(p.y - m_iSize_MaskPen - m_rcDispWin.top) ;
	m_rcMask.right		= (int)(p.x + m_iSize_MaskPen - m_rcDispWin.left);
	m_rcMask.bottom		= (int)(p.y + m_iSize_MaskPen - m_rcDispWin.top) ;

	if ( m_rcMask.left < 0 )	m_rcMask.left = 0;
	if ( m_rcMask.top < 0 )		m_rcMask.top = 0;

	if ( m_rcMask.right > m_iMarkSetSizeX )	m_rcMask.right = m_iMarkSetSizeX - 1;
	if ( m_rcMask.bottom > m_iMarkSetSizeY )	m_rcMask.bottom  = m_iMarkSetSizeY - 1;

	MgraColor(M_DEFAULT, M_COLOR_BLUE);
	MgraRectFill(M_DEFAULT, vision.MilMarkSetOverlayImage, m_rcMask.left, m_rcMask.top, m_rcMask.right, m_rcMask.bottom);

	getAreaMask();
}

void CMarkSetDlg::getAreaMask()
{
	int iSx = (int)(m_rcMask.left	/ m_dZoomX + 0.5);
	int iSy = (int)(m_rcMask.top	/ m_dZoomY + 0.5);
	int iEx = (int)(m_rcMask.right  / m_dZoomX + 0.5);
	int iEy = (int)(m_rcMask.bottom / m_dZoomY + 0.5);
	int iPos;

	for (int y=iSy ; y<iEy ; y++)
	{
		iPos = y * m_iSizeX + iSx;

		for (int x=iSx ; x<iEx ; x++)
		{
			vision.ucMaskBuf[iPos++] = 0xff;
		}
	}
}

void CMarkSetDlg::updateMaskPenSize()
{
	m_iSize_MaskPen = GetDlgItemInt(IDC_LABEL_SIZE_PEN);
}

void CMarkSetDlg::OnBnClickedRadioCenter()
{
	UpdateData(true);
}


void CMarkSetDlg::OnBnClickedRadioMask()
{
	UpdateData(true);
}


void CMarkSetDlg::OnBnClickedButtonClearMask()
{
	MbufClear(vision.MilMarkSetOverlayImage, vision.MarkSetTransparentColor);

	MgraColor(M_DEFAULT, M_COLOR_RED);
	MgraLine(M_DEFAULT, vision.MilMarkSetOverlayImage, (int)(m_Center.x*m_dZoomX+0.5), 0, (int)(m_Center.x*m_dZoomX+0.5), m_iMarkSetSizeY);
	MgraLine(M_DEFAULT, vision.MilMarkSetOverlayImage, 0, (int)(m_Center.y*m_dZoomY+0.5), m_iMarkSetSizeX, (int)(m_Center.y*m_dZoomY+0.5));

	::memset(vision.ucMaskBuf, 0x00, m_iSizeX*m_iSizeY);
	MbufClear(vision.MilMask, 0x00);
}


void CMarkSetDlg::OnBnClickedButtonClearMask2()
{
	MbufClear(vision.MilMask, 0x00);
	MbufPut(vision.MilMask, vision.ucMaskBuf);

	MmodMask(vision.ModModel[m_iMarkType][m_iMarkNo], M_DEFAULT, vision.MilMask, M_DONT_CARES, M_DEFAULT);
	MmodPreprocess(vision.ModModel[m_iMarkType][m_iMarkNo], M_DEFAULT);
}


void CMarkSetDlg::OnStnClickedLabelSizePen()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		m_labelPenSize.SetText(dlg.GetstrNum());
	}
}



void CMarkSetDlg::SaveMarkImg()
{
	CString FolderName;
	FolderName.Format("%s", AA_MODEL_LOAD_DIR);

	CString strType;
	if (m_iMarkType==PCB_Chip_MARK)			strType = "LENS";
	else if (m_iMarkType==PCB_Holder_MARK)		strType = "PCB";
	else										strType = "LENS_Edge";

	CString strPatDir;
	strPatDir.Format("%s\\%s\\Data\\Mark\\%s_Mark_%d-Mask.bmp", FolderName, model.mCurModelName, strType, m_iMarkNo);

	if (vision.MilMask==M_NULL)
		return;

	MbufExport(strPatDir.GetBuffer(999), M_BMP, vision.MilMask);
}



void CMarkSetDlg::LoadMarkImg()
{

	CString FolderName="";
	FolderName.Format("%s", AA_MODEL_LOAD_DIR);

	CString strType="";
	CString strPatDir="";

	if(m_iCamNo != CCD)
	{
		if (m_iMarkType==PCB_Chip_MARK)					strType = "LENS";
		else if (m_iMarkType==PCB_Holder_MARK)		strType = "PCB";
		else																	strType = "LENS_Edge";
	}
	else
	{
		strType = "CHART";
	}

	strPatDir.Format("%s\\%s\\Data\\Mark\\%s_Mark_%d-Mask.bmp", FolderName, model.mCurModelName, strType, m_iMarkNo);
	if( m_iCamNo == CCD)
	{
		MbufClear(vision.MilProcImage[1], 0x00);
		MbufImport(strPatDir.GetBuffer(999), M_DEFAULT, M_LOAD, vision.MilSystem, &vision.MilProcImage[1]);
		MbufCopy(vision.MilProcImage[1], vision.MilMarkSetDisplay);
	}
	else
	{
		MbufImport(strPatDir.GetBuffer(999), M_DEFAULT, M_LOAD, vision.MilSystem, &vision.MilMask);
		MbufGet(vision.MilMask, vision.ucMaskBuf);
	}
}