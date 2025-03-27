#pragma once

#include "Label/Label.h"
#include "ContinuousButton.h"

// CForceAlignDlg 대화 상자입니다.

class CForceAlignDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CForceAlignDlg)

public:
	CForceAlignDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CForceAlignDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_FORCE_ALIGN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonBoxUp();
	afx_msg void OnClickedButtonBoxLeft();
	afx_msg void OnClickedButtonBoxRight();
	afx_msg void OnBnClickedButtonBoxDown();
	afx_msg void OnBnClickedButtonBoxSpeed();
	afx_msg void OnBnClickedButtonForcrAlign();

	void SetCamNo(int iCamNo, int iMarkType);
	void SetMarkPosition(CPoint p);
	void SetMarkPosition(int x, int y);

protected:
	CLabel	m_labelTitle;
	CContinuousButton m_btn_BoxLeft;
	CContinuousButton m_btn_BoxUP;
	CContinuousButton m_btn_BoxRight;
	CContinuousButton m_btn_BoxDown;

	int m_iCamNo;
	int m_iMarkType;

	int m_iMoveSpeed;
	CPoint	m_poCenter;
	CRect	m_rcMark;

	void DrawMark(bool bDrawComplete = false);

	
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
