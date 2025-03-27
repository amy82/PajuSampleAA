#pragma once


// CContinuousButton

class CContinuousButton : public CButton
{
	DECLARE_DYNAMIC(CContinuousButton)

public:
	CContinuousButton();
	virtual ~CContinuousButton();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


