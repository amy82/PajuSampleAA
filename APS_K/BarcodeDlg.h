#pragma once


// CBarcodeDlg 대화 상자입니다.

class CBarcodeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBarcodeDlg)

public:
	CBarcodeDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CBarcodeDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_BARCODE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedBtnBarcodePortOpen();
	afx_msg void OnBnClickedBtnBarcodePortClose();
	afx_msg void OnBnClickedBtnBarcodeReade();
	CString m_Edit_strBarcode;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnBarcodeReadeStop();
};
