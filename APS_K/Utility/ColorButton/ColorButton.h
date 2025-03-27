#pragma once


// CColorButton

class CColorButton : public CButton
{
	DECLARE_DYNAMIC(CColorButton)

public:
	CColorButton();
	virtual ~CColorButton();

	void SetCtrlFont(int nHeight, int nWidth, CString szFontName);
	void SetSelected(bool bSelect);
	void ChangeColor(int nState);
	int GetCurrentState() { return m_nStateBtn; }

	int GetBlinkCtrl();
	void SetBlink(bool bBlink);
	void SetBlinkTime(DWORD dwInterval);

private:
	COLORREF m_clrBtnBack;
	COLORREF m_clrBtnBack_Selected;

	COLORREF m_clrBtnNormal;
	COLORREF m_clrBtnOn;
	COLORREF m_clrBtnOn2;
	COLORREF m_clrBtnERR;
	COLORREF m_clrBtnRUN;
	COLORREF m_clrBtnDISABLE;

	COLORREF m_clrBtnText;
	COLORREF m_clrBtnText_Selected;

	bool	m_bSelected;
	int		m_nStateBtn;

	bool	m_bBlink;
	int		m_nUseBlink;
	DWORD	m_dwTimeOver;
	DWORD	m_dwBlinkTime;

	CFont			m_clFont;
	
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};


