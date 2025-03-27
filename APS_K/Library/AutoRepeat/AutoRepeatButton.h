#if !defined(AFX_AUTOREPEATBUTTON_H__3F2FF2BD_C05C_11D5_A04D_006067718D04__INCLUDED_)
#define AFX_AUTOREPEATBUTTON_H__3F2FF2BD_C05C_11D5_A04D_006067718D04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AutoRepeatButton.h : header file
//

#include "BtnST.h"

class CAutoRepeatButton : public CButtonST
{
// Construction
public:
	CAutoRepeatButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoRepeatButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAutoRepeatButton();

	// Generated message map functions
protected:
    UINT sent;
	//{{AFX_MSG(CAutoRepeatButton)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOREPEATBUTTON_H__3F2FF2BD_C05C_11D5_A04D_006067718D04__INCLUDED_)
