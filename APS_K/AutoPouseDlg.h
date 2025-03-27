#pragma once


// CAutoPouseDlg 대화 상자입니다.

class CAutoPouseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAutoPouseDlg)

public:
	CAutoPouseDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAutoPouseDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_AUTORUN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
