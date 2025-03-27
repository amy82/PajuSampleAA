#pragma once


// CSliderCtrlEx

class CSliderCtrlEx : public CSliderCtrl
{
	DECLARE_DYNAMIC(CSliderCtrlEx)

public:
	CSliderCtrlEx();
	virtual ~CSliderCtrlEx();

protected:
	DECLARE_MESSAGE_MAP()

public:
	CDC			m_dcBk;
	CBitmap		m_bmpBk;
	CBitmap     *m_bmpBkOld;
	//CBitmap*	m_pbmpOldBk;
	CPen m_penThumb;
	CPen m_penThumbLight;
	CPen m_penThumbLighter;
	CPen m_penThumbDark;
	CPen m_penThumbDarker;
	COLORREF m_crThumb;
	COLORREF m_crThumbLight;
	COLORREF m_crThumbLighter;
	COLORREF m_crThumbDark;
	COLORREF m_crThumbDarker;

protected:
	afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


