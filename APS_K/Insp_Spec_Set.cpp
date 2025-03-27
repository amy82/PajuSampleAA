// Insp_Spec_Set.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Insp_Spec_Set.h"


// CInsp_Spec_Set 대화 상자입니다.

IMPLEMENT_DYNAMIC(CInsp_Spec_Set, CDialogEx)

CInsp_Spec_Set::CInsp_Spec_Set(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInsp_Spec_Set::IDD, pParent)
{
}

CInsp_Spec_Set::~CInsp_Spec_Set()
{
}

void CInsp_Spec_Set::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CInsp_Spec_Set::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow)
	{
		putData();
		UpdateData(false);
	}
}

BOOL CInsp_Spec_Set::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//CInsp_Spec_Set::OnInitDialog();

	return TRUE;
}

BEGIN_MESSAGE_MAP(CInsp_Spec_Set, CDialogEx)
	ON_BN_CLICKED(IDSAVE, &CInsp_Spec_Set::OnBnClickedSave)
	ON_WM_SHOWWINDOW()
	ON_EN_CHANGE(IDC_DEFECTPIXEL_DEFECTPIXELTOTAL_BRIGHT, &CInsp_Spec_Set::OnEnChangeDefectpixelDefectpixeltotalBright)
	ON_EN_CHANGE(IDC_DEFECTPIXEL_DEFECTPIXELTOTAL_DARK, &CInsp_Spec_Set::OnEnChangeDefectpixelDefectpixeltotalDark)
	ON_EN_CHANGE(IDC_DEFECTPIXEL_DEFECTPIXELTOTAL_HOT, &CInsp_Spec_Set::OnEnChangeDefectpixelDefectpixeltotalHot)
	ON_BN_CLICKED(IDOK, &CInsp_Spec_Set::OnBnClickedOk)
END_MESSAGE_MAP()


// CInsp_Spec_Set 메시지 처리기입니다.


void CInsp_Spec_Set::OnBnClickedSave()
{
	bool passFlag = password.m_bFlag;

	if(passFlag == false)
	{
		CString strTemp;
		CKeyPadDlg keyDlg;

		sLangChange.LoadStringA(IDS_STRING891);
		keyDlg.m_strKeyPad = sLangChange;	//"Password를 입력하세요."

		if (keyDlg.DoModal()==IDOK)
		{
			strTemp = keyDlg.GetstrKeypad();

			passFlag = strTemp.CompareNoCase(password.m_szPassword) ? false : true;
		}
		else
		{
			return;
		}
	}


	if(passFlag)
	{
		password.m_bFlag = true;
	}
	else
	{
		sLangChange.LoadStringA(IDS_STRING892);
		errMsg2(Task.AutoFlag, sLangChange);	//"Password를 잘 못 입력했습니다."
		return;
	}



	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	sLangChange.LoadStringA(IDS_STRING1156);	//"검사 파라미터를 저장 하시겠습니까?"
	if(askMsg(sLangChange))
	{
		getData();

		model.Save();
		model.Load();

		putData();
	}
}

void CInsp_Spec_Set::getData()
{
	CString sEditData;

	UpdateData(true);

	GetDlgItemText(IDC_MTF_0_0F, sEditData);
	model.INSP_MTF_0_0F = atof(sEditData);

	GetDlgItemText(IDC_MTF_0_5F, sEditData);
	model.INSP_MTF_0_5F	= atof(sEditData);

	GetDlgItemText(IDC_MTF_0_7F, sEditData);
	model.INSP_MTF_0_7F	= atof(sEditData);

	GetDlgItemText(IDC_MTF_BLANCE_0_5F, sEditData);
	model.INSP_MTF_Blance_0_5F	= atof(sEditData);
	GetDlgItemText(IDC_MTF_BLANCE_0_7F, sEditData);
	model.INSP_MTF_Blance_0_7F	= atof(sEditData);

	GetDlgItemText(IDC_BLEMISH, sEditData);
	model.INSP_Blemish	= atof(sEditData);
	GetDlgItemText(IDC_NOISE, sEditData);
	model.INSP_Noise	= atof(sEditData);
	GetDlgItemText(IDC_STAIN, sEditData);
	model.INSP_Stain	= atof(sEditData);

	GetDlgItemText(IDC_DEFECTPIXEL_DEFECTPIXELTOTAL_HOT, sEditData);
	model.INSP_DefectPixel_DefectPixelTotal_Hot	= atof(sEditData);

	GetDlgItemText(IDC_DEFECTPIXEL_DEFECTPIXELTOTAL_BRIGHT, sEditData);
	model.INSP_DefectPixel_DefectPixelTotal_Bright	= atof(sEditData);
	GetDlgItemText(IDC_DEFECTPIXEL_DEFECTPIXELTOTAL_BRIGHT_RATIO, sEditData);
	model.INSP_DefectPixel_DefectPixelTotal_Bright_Ratio	= atof(sEditData);
	GetDlgItemText(IDC_DEFECTPIXEL_DEFECTPIXELTOTAL_DARK, sEditData);
	model.INSP_DefectPixel_DefectPixelTotal_Dark	= atof(sEditData);
	GetDlgItemText(IDC_DEFECTPIXEL_DEFECTPIXELTOTAL_DARK_RATIO, sEditData);
	model.INSP_DefectPixel_DefectPixelTotal_Dark_Ratio	= atof(sEditData);
	GetDlgItemText(IDC_DEFECTPIXEL_COUPLET, sEditData);
	model.INSP_DefectPixel_Dark_Couplet	= atof(sEditData);
	GetDlgItemText(IDC_DEFECTPIXEL_CLUSTER, sEditData);
	model.INSP_DefectPixel_Dark_Cluster = atof(sEditData);
	GetDlgItemText(IDC_DEFECTPIXEL_ROW_DARK, sEditData);
	model.INSP_DefectPixel_Row_Dark	= atof(sEditData);
	GetDlgItemText(IDC_DEFECTPIXEL_ROW_MIDLEVEL, sEditData);
	model.INSP_DefectPixel_Row_Midlevel	= atof(sEditData);

	GetDlgItemText(IDC_DEFECTPIXEL_COLUMN_DARK, sEditData);
	model.INSP_DefectPixel_Column_Dark	= atof(sEditData);
	GetDlgItemText(IDC_DEFECTPIXEL_COLUMN_MIDLEVEL, sEditData);
	model.INSP_DefectPixel_Column_Midlevel	= atof(sEditData);
	GetDlgItemText(IDC_DEFECTPIXEL_COLUMNFPN, sEditData);
	model.INSP_DefectPixel_ColumnFPN = atof(sEditData);

	GetDlgItemText(IDC_DISTORTIONCENTERING, sEditData);
	model.INSP_DistortionCentering = atoi(sEditData);
}


void CInsp_Spec_Set::putData()
{
	CString sEditData;

	sEditData.Format("%.02lf", model.INSP_MTF_0_0F);
	SetDlgItemText(IDC_MTF_0_0F, sEditData);
	sEditData.Format("%.02lf", model.INSP_MTF_0_5F);
	SetDlgItemText(IDC_MTF_0_5F, sEditData);
	sEditData.Format("%.02lf", model.INSP_MTF_0_7F);
	SetDlgItemText(IDC_MTF_0_7F, sEditData);
	sEditData.Format("%.02lf", model.INSP_MTF_Blance_0_5F);
	SetDlgItemText(IDC_MTF_BLANCE_0_5F, sEditData);
	sEditData.Format("%.02lf", model.INSP_MTF_Blance_0_7F);
	SetDlgItemText(IDC_MTF_BLANCE_0_7F, sEditData);

	SetDlgItemInt(IDC_BLEMISH, model.INSP_Blemish);
	SetDlgItemInt(IDC_NOISE, model.INSP_Noise);
	SetDlgItemInt(IDC_STAIN, model.INSP_Stain);
	SetDlgItemInt(IDC_DEFECTPIXEL_DEFECTPIXELTOTAL_HOT, model.INSP_DefectPixel_DefectPixelTotal_Hot);
	SetDlgItemInt(IDC_DEFECTPIXEL_DEFECTPIXELTOTAL_BRIGHT, model.INSP_DefectPixel_DefectPixelTotal_Bright);
	SetDlgItemInt(IDC_DEFECTPIXEL_DEFECTPIXELTOTAL_BRIGHT_RATIO, model.INSP_DefectPixel_DefectPixelTotal_Bright_Ratio);
	SetDlgItemInt(IDC_DEFECTPIXEL_DEFECTPIXELTOTAL_DARK, model.INSP_DefectPixel_DefectPixelTotal_Dark);
	SetDlgItemInt(IDC_DEFECTPIXEL_DEFECTPIXELTOTAL_DARK_RATIO, model.INSP_DefectPixel_DefectPixelTotal_Dark_Ratio);
	SetDlgItemInt(IDC_DEFECTPIXEL_COUPLET, model.INSP_DefectPixel_Dark_Couplet);
	SetDlgItemInt(IDC_DEFECTPIXEL_CLUSTER, model.INSP_DefectPixel_Dark_Cluster);
	SetDlgItemInt(IDC_DEFECTPIXEL_ROW_DARK, model.INSP_DefectPixel_Row_Dark);
	SetDlgItemInt(IDC_DEFECTPIXEL_ROW_MIDLEVEL, model.INSP_DefectPixel_Row_Midlevel);
	SetDlgItemInt(IDC_DEFECTPIXEL_COLUMN_DARK, model.INSP_DefectPixel_Column_Dark);
	SetDlgItemInt(IDC_DEFECTPIXEL_COLUMN_MIDLEVEL, model.INSP_DefectPixel_Column_Midlevel);
	SetDlgItemInt(IDC_DEFECTPIXEL_COLUMNFPN, model.INSP_DefectPixel_ColumnFPN);
	SetDlgItemInt(IDC_DISTORTIONCENTERING, model.INSP_DistortionCentering);

	UpdateData(false);
}




void CInsp_Spec_Set::OnEnChangeDefectpixelDefectpixeltotalBright()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CInsp_Spec_Set::OnEnChangeDefectpixelDefectpixeltotalDark()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CInsp_Spec_Set::OnEnChangeDefectpixelDefectpixeltotalHot()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CInsp_Spec_Set::OnBnClickedOk()
{
	this->ShowWindow(SW_HIDE);
}
