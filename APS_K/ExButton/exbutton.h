#if !defined(AFX_EXBUTTON_H__7613DD85_E2B4_4007_AEB4_C774875722FE__INCLUDED_)
#define AFX_EXBUTTON_H__7613DD85_E2B4_4007_AEB4_C774875722FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExButton window

//! 'Owner draw' 속성이 있는 버튼 컨트롤을 그린다. 

class CExButton : public CButton
{
// Construction
public:
	CExButton();

// Attributes
public:
	COLORREF m_clrBtnBack;
	COLORREF m_clrBtnBack_Selected;

	COLORREF m_clrBtnNormal;
	COLORREF m_clrBtnOn;
	COLORREF m_clrBtnOn2;
	COLORREF m_clrBtnOFF;

	COLORREF m_clrBtnStart;

	COLORREF m_clrBtnText;
	COLORREF m_clrBtnText_Selected;

	bool m_bSelected;

	int m_iStateBtn;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CExButton)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXBUTTON_H__7613DD85_E2B4_4007_AEB4_C774875722FE__INCLUDED_)
