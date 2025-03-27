#pragma once


// CButtonEx

#define DEFAULT_MARGIN	20

class CRGBImageList
{
public:
	CRGBImageList()
	{
		m_dcMem.CreateCompatibleDC(NULL);
		m_old = NULL;
	}
	virtual ~CRGBImageList()
	{
		if (m_hImage)
		{
			m_dcMem.SelectObject(m_old);
			m_old = NULL;
			m_bmp.Detach();
			::DeleteObject(m_hImage);
		}
		m_dcMem.DeleteDC();
	}

	BOOL Create(UINT idBitmap, UINT nWidth)
	{
		BITMAP bmpInfo;
		m_bmp.LoadBitmap(idBitmap);

		//m_hImage = (HBITMAP)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(idBitmap), IMAGE_BITMAP, 0, 0, NULL);//LR_LOADTRANSPARENT | LR_LOADMAP3DCOLORS);
		
		//if (!m_hImage) return FALSE;

		if (m_old != NULL){
			m_dcMem.SelectObject(&m_old);
			m_bmp.Detach();
		}

		//m_bmp.Attach(m_hImage);
		m_width = nWidth;

		//m_bmp.GetObject(sizeof(BITMAP), &m_bmpInfo);
		m_bmp.GetBitmap(&bmpInfo);
		m_height = bmpInfo.bmHeight;

		m_old = m_dcMem.SelectObject(&m_bmp);
		return TRUE;
	}

	BOOL Draw(CDC* pDC, int nImage, POINT pt)
	{
		return  pDC->BitBlt(pt.x, pt.y, m_width, m_height, &m_dcMem, nImage*m_width, 0, SRCCOPY);
	}

	CSize GetImageDimension() { CSize s(m_width, m_height); return s; }

protected:
	CDC  m_dcMem;
	HBITMAP m_hImage;
	CBitmap m_bmp;
	UINT m_width, m_height;
	CGdiObject *m_old;
	BITMAP m_bmpInfo;
};


class CButtonEx : public CButton
{
	DECLARE_DYNAMIC(CButtonEx)

public:
	CButtonEx(BOOL bReadOnly = TRUE, BOOL bDepressed = FALSE, BOOL bCenterAlign = TRUE);
	virtual ~CButtonEx();

	void SetCtrlFont(int nHeight, int nWidth, CString szFontName);
	void SetImage(UINT nID, UINT nImgWidth);
	void SetPress(int nDraw); //Set button state (TRUE=pushed, FALSE=depressed)
	int GetBlinkCtrl(int nFirst, int nSecond);		//±Ù∫˝¿” µø¿€ ¡§∫∏ ∞ËªÍ

	void SetSelected(bool bClick);
	void SetMoveCtrl(bool bMove);
	void SetBlink(bool bBlink);
	void SetBlinkTime(DWORD dwInterval);
	int	 GetDrawIndex();

private:
	bool	m_bSelected;
	bool	m_bMove;
	bool	m_bBlink;
	int		m_nUseBlink;
	DWORD	m_dwTimeOver;
	DWORD	m_dwBlinkTime;

protected:
	int	m_nMargin;
	int	m_nRadius;
	CPoint m_ptCenter;
	CRect m_textRect;
	BOOL m_bCenterAlign;
	BOOL m_bReadOnly;
	int	m_nDrawImg;
	CFont m_clFont;
	
	CRGBImageList m_imgList;
	CSize m_rcImage;

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();

public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};


