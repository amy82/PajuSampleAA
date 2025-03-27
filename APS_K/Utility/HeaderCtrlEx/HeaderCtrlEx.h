/**************************************************************************************
  작 성 자 : 안 창근(Prodori)
  작성일자 : 2004-11-12
  수정일자 : 
  Comments : 
		m_list.SubclassDlgItem(IDC_LIST1, this);
		m_list.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		//리스트컨트롤의 헤더컨트롤 연결
		m_header.SubclassWindow(m_list.GetHeaderCtrl()->m_hWnd);
		CFont font;
		font.CreateFont(12, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, "굴림체");
		m_header.SetFont(&font);
		m_header.SetHeight(36); //헤더 영역의 크기 설정
		font.Detach();
		m_header.SetBkColor(RGB(0,255,128));
		m_header.SetTextColor(RGB(128, 0, 255));

		{
			CString sTitle[][2] = {
				{ "이름", ""},
				{ "규격", ""},
				{ "수량", ""},
				{ "단위", ""},
				{ "단가", "합  계"},
				{ "금액", "합  계"},
				{ "단가", "재료비"},
				{ "금액", "재료비"},
				{ "단가", "노무비"},
				{ "금액", "노무비"},
				{ "단가", "경비"},
				{ "금액", "경비"},
				{ "", ""}
			};
			for (int i=0; !sTitle[i][0].IsEmpty(); i++)
			{
				m_list.InsertColumn(i, sTitle[i][0], LVCFMT_CENTER, 100);
				m_header.SetTitle(i, sTitle[i][1]);
			}
		}
 **************************************************************************************/
#if !defined(AFX_HEADERCTRLEX_H__9D44BD11_596F_4973_A464_1CAD0CD8D548__INCLUDED_)
#define AFX_HEADERCTRLEX_H__9D44BD11_596F_4973_A464_1CAD0CD8D548__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HeaderCtrlEx.h : header file
//
#include <afxtempl.h>
/////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlEx window

class CHeaderCtrlEx : public CHeaderCtrl
{
// Construction
public:
	CHeaderCtrlEx();

// Attributes
public:

// Operations
public:

	virtual void SetFont( CFont* pFont, BOOL bRedraw = TRUE );
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHeaderCtrlEx)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetHeight(int nHeight);
	void SetTitle(int nIndex, CString sTitle);
	void SetTextColor(COLORREF color) { m_clrText = color; }
	void SetBkColor(COLORREF color) { m_clrBack = color; }
	virtual ~CHeaderCtrlEx();

	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

private:
	CStringArray	m_sTitle;
	CFont			m_font;
	COLORREF		m_clrText;
	COLORREF		m_clrBack;
	// Generated message map functions
protected:
	void Draw(CDC *pDC);
	//{{AFX_MSG(CHeaderCtrlEx)
	afx_msg void OnPaint();
	//}}AFX_MSG
	afx_msg LRESULT OnDeleteItem(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnInsertItem(WPARAM wparam, LPARAM lparam);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEADERCTRLEX_H__9D44BD11_596F_4973_A464_1CAD0CD8D548__INCLUDED_)
