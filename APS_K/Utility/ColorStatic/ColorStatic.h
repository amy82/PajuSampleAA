#pragma once


// CColorStatic

class CColorStatic : public CStatic
{
	DECLARE_DYNAMIC(CColorStatic)

public:
	CColorStatic();
	virtual ~CColorStatic();

	void SetBkColor(COLORREF crBkColor = 0xffffffff);
	void SetTextColor(COLORREF crTextColor = 0xffffffff);

private:
	COLORREF m_crTextColor;
	COLORREF m_crBkColor;

	CBrush m_brBkgnd;
	CWnd* m_pParent;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnDestroy();
};