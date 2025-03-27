#ifndef _DIGITST_H
#define _DIGITST_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// DigitST.h : header file
//

// Min number of digits we can display
#define ST_MIN_PRECISION	1
// Max number of digits we can display (it can be increased)
#define ST_MAX_PRECISION	10
// Space left around the bitmap for border
#define BORDER_SPACE		3


class CDigitST : public CStatic
{
public:
	CDigitST();
	virtual ~CDigitST();
    enum {	ST_LEFT			= 0x01, 
			ST_TOP			= 0x02,
			ST_RIGHT		= 0x04,
			ST_BOTTOM		= 0x08};

public:

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDigitST)
	//}}AFX_VIRTUAL

public:
	BOOL SetStyle(UINT nBitmapId, int nPrecision);

	void SetValue(float nValue, BOOL bRepaint = TRUE);
	float GetValue();

	void SetPrecision(int nPrecision, BOOL bResize = TRUE);
	int GetPrecision();

	void SetResize(DWORD dwResize, BOOL bResize = TRUE);
	DWORD GetResize();

	void SetZeroPadding(BOOL bPad = FALSE, BOOL bRepaint = TRUE);
	BOOL GetZeroPadding();

	void Inc(BOOL bRepaint = TRUE);
	void Dec(BOOL bRepaint = TRUE);

	static const char* GetVersionC();
	static const short GetVersionI();

protected:
	//{{AFX_MSG(CDigitST)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	void Resize();
	void PrepareString(char* szDest);
	void DrawDigits(CDC* pDC);

	CBitmap m_bmDigit;
	int m_nWidth;
	int m_nHeight;

	int m_nPrecision;
	float m_nValue;

	BOOL m_bZeroPadding;
	DWORD m_dwResize;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif
