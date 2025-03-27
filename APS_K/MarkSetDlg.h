#pragma once

/* Label Class */
#include "Label/Label.h"

// CMarkSetDlg 대화 상자입니다.

class CMarkSetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMarkSetDlg)

public:
	CMarkSetDlg(int iCamNo, int iMarkType, int iMarkNo, int iSizeX, int iSizeY, bool bFirst, CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMarkSetDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_MARKSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	int m_iCamNo;
	int m_iMarkType;
	int m_iMarkNo;
	int m_iSizeX;
	int m_iSizeY;
	int m_iMarkSetSizeX;
	int m_iMarkSetSizeY;
	int m_iMoveSpeed;
	bool bFirstMark;

	double m_dZoomX;
	double m_dZoomY;

	CDPoint m_Center;

	CLabel m_labelPenSize;

	CRect m_rcDispWin;
	CRect m_rcMask;

	CPoint m_ClickP;
	CPoint m_MoveP;

	bool	m_bDrawMask;

	int		m_iSize_MaskPen;

	void	drawLine(CDPoint p);
	void	drawMaskPen(CPoint p);
	void	getAreaMask();
	void	updateMaskPenSize();

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	int m_iSelMoveType;		/* 0:Position 1:Size */
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioMovetype1();
	afx_msg void OnBnClickedRadioMovetype2();
	afx_msg void OnBnClickedButtonBoxUp();
	afx_msg void OnBnClickedButtonBoxDown();
	afx_msg void OnBnClickedButtonBoxLeft();
	afx_msg void OnBnClickedButtonBoxRight();
	afx_msg void OnBnClickedButtonBoxSpeed();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	int m_iSelDrawType;		/* 0:Center 1:Mask */
	afx_msg void OnBnClickedRadioCenter();
	afx_msg void OnBnClickedRadioMask();
	afx_msg void OnBnClickedButtonClearMask();
	afx_msg void OnBnClickedButtonClearMask2();
	afx_msg void OnStnClickedLabelSizePen();

protected:
	void SaveMarkImg();
	void LoadMarkImg();
};
