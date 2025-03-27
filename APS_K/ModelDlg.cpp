// ModelDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ModelDlg.h"
#include "afxdialogex.h"
#include "EditDlg.h"
#include "DataSet.h"
#include "PassWordDlg.h"
//#include "SfrSpec.h"
#include "BarcodeDlg.h"
#include "Insp_Spec_Set.h"
#include "ImageInsp/Inspection_Alg.h"
#include "InfoDlg.h"
//extern		CSfrSpec*			sfrSpecDlg;
extern		CInsp_Spec_Set*		InspSpecSet;


extern		CDataSet*		DataSet;





// CModelDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CModelDlg, CDialogEx)

	CModelDlg::CModelDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CModelDlg::IDD, pParent)
{

}

CModelDlg::~CModelDlg()
{
}

void CModelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_MSFLEXGRID_MODEL, m_gridModel);
	DDX_Control(pDX, IDC_BUTTON_FREE_RUN, m_btnFreeRun);
	DDX_Control(pDX, IDC_EDIT_EPOXY_SHOT, m_Epoxy_Shot);
	DDX_Control(pDX, IDC_EDIT_EPOXY_ALARM, m_Epoxy_Alarm);
	DDX_Control(pDX, IDC_EDIT_EPOXY_START_TIME, m_Epoxy_Start_Time);
	DDX_Control(pDX, IDC_EDIT_EPOXY_LAST_TIME, m_Epoxy_Last_Time);
	DDX_Control(pDX, IDC_EDIT_SOCKET_COUNT, m_Socket_Count);
	DDX_Control(pDX, IDC_EDIT_SOCKET_ALARM, m_Socket_Alarm);
	DDX_Control(pDX, IDC_BUTTON_SOCKET_RESET, m_Socket_Reset);
}


BEGIN_MESSAGE_MAP(CModelDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CModelDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CModelDlg::OnBnClickedCancel)
	ON_WM_SHOWWINDOW()
	//	ON_STN_CLICKED(IDC_LABEL, &CModelDlg::OnStnClickedLabel)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_CREATE, &CModelDlg::OnBnClickedButtonCreate)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CModelDlg::OnBnClickedButtonDelete)
	ON_WM_MOUSEHWHEEL()
	ON_WM_MOUSEWHEEL()
	ON_BN_CLICKED(IDC_BUTTON_PARAMETERSETTING, &CModelDlg::OnBnClickedButtonParametersetting)
	ON_BN_CLICKED(IDC_BUTTON_DATASET, &CModelDlg::OnBnClickedButtonDataset)
	ON_BN_CLICKED(IDC_BUTTON_FREE_RUN, &CModelDlg::OnBnClickedButtonFreeRun)
	ON_BN_CLICKED(IDC_BUTTON_SFR_SPEC, &CModelDlg::OnBnClickedButtonSfrSpec)
	ON_BN_CLICKED(IDC_BTN_BARCODE, &CModelDlg::OnBnClickedBtnBarcode)
	ON_STN_CLICKED(IDC_EDIT_EPOXY_SHOT, &CModelDlg::OnStnClickedEditEpoxyShot)
	ON_STN_CLICKED(IDC_EDIT_EPOXY_ALARM, &CModelDlg::OnStnClickedEditEpoxyAlarm)
	ON_STN_CLICKED(IDC_EDIT_EPOXY_START_TIME, &CModelDlg::OnStnClickedEditEpoxyStartTime)
	ON_STN_CLICKED(IDC_EDIT_EPOXY_LAST_TIME, &CModelDlg::OnStnClickedEditEpoxyLastTime)
	ON_BN_CLICKED(IDC_BUTTON_EPOXY_RESET, &CModelDlg::OnBnClickedButtonEpoxyReset)
	ON_STN_CLICKED(IDC_EDIT_SOCKET_COUNT, &CModelDlg::OnStnClickedEditSocketCount)
	ON_STN_CLICKED(IDC_EDIT_SOCKET_ALARM, &CModelDlg::OnStnClickedEditSocketAlarm)
	ON_BN_CLICKED(IDC_BUTTON_SOCKET_RESET, &CModelDlg::OnBnClickedButtonSocketReset)

	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_MODEL_GRID, &CModelDlg::OnDBClickedGridModelb)
    ON_NOTIFY(NM_CLICK, IDC_STATIC_MODEL_GRID, &CModelDlg::OnGridClick)
	ON_BN_CLICKED(IDC_BTN_EEPROM_DLG, &CModelDlg::OnBnClickedBtnEepromDlg)
	ON_BN_CLICKED(IDC_BUTTON_MODEL_LOAD, &CModelDlg::OnBnClickedButtonModelLoad)
	ON_BN_CLICKED(IDC_BUTTON_COPY, &CModelDlg::OnBnClickedButtonCopy)
END_MESSAGE_MAP()


// CModelDlg 메시지 처리기입니다.
BOOL CModelDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	ModelCurCol = modelList.TotalCount;
	InitGridCtrl_Model();
	setInterface();

	ShowGridCtrl_Model();
	
	return TRUE;
}

void CModelDlg::OnBnClickedOk(){}
void CModelDlg::OnBnClickedCancel(){}

void CModelDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	m_bShowFlag = bShow ? true : false;

	if (bShow)
	{
		putData();
		ShowGridCtrl_Model();		//OnShowWindow

		//sensor.getSensorListFromINI();
		initListBox();
		dispCurSensor();

		if (sysData.m_FreeRun == 1)
		{
			m_btnFreeRun.m_iStateBtn	= 1;
		}
		else
		{
			m_btnFreeRun.m_iStateBtn	= 0;
		}

		m_btnFreeRun.Invalidate();

		//m_gridModel.GetWindowRect(&m_rcGridModel);
	}
	else
	{

	}
}
void CModelDlg::GrabImgLoad()
{
	//CString FileName = "";
	//FileName.Format("%s\\%s.jpg",DLL_DIR, model.name);
	////
	//CRect rect;
	//m_stDisplay.GetClientRect(&rect);
	//long	BufferAttributes;
	//MIL_ID  MIL_TeachImage;
	//MIL_ID  MilResizeImage;	
	//MIL_ID  MIL_Display;
	//MIL_Display = M_NULL;
	//MilResizeImage = M_NULL;
	////
	//int wid = 1024;
	//int hei = 768;
	////MsysAlloc(M_SYSTEM_VGA, M_DEV0, M_COMPLETE, &vision.MilSystem);
	////MsysInquire(vision.MilSystem, M_DIGITIZER_NUM, &NumberOfDigitizer);
	//BufferAttributes =  M_IMAGE + M_PROC + M_DISP;;
	//MbufAllocColor(vision.MilSystem, 3, wid, hei, M_DEF_IMAGE_TYPE, BufferAttributes, &MIL_TeachImage);
	//MbufAllocColor(vision.MilSystem, 3,  wid, hei, M_DEF_IMAGE_TYPE, BufferAttributes, &MilResizeImage);
	//MbufClear(MIL_TeachImage,M_COLOR_BLACK);
	//MbufClear(MilResizeImage, M_COLOR_BLACK);
	//MbufLoad((char*)(const char*)FileName, MIL_TeachImage);
	//MdispAlloc(vision.MilSystem, M_DEFAULT, "M_DEFAULT", M_DEFAULT, &MIL_Display);

	////MdispInquire(MIL_Display, M_DISPLAY_MODE, M_NULL);
	//CWnd* pWnd = (CWnd*) GetDlgItem(IDC_STATIC_GRAB_IMAGE);
	//
	//double dFactorX	= (double)(rect.right)/(double)(wid);
	//double dFactorY	= (double)(rect.bottom)/(double)(hei);
	//MimResize(MIL_TeachImage, MilResizeImage, dFactorX,dFactorY, M_DEFAULT);
	//MdispSelectWindow(MIL_Display, MilResizeImage, pWnd->m_hWnd);
}
void CModelDlg::InitGridCtrl_Model()
{
	CRect rect;
	CWnd *pWnd= (CWnd*)GetDlgItem(IDC_STATIC_MODEL_GRID); 

	//
	//모델 그리드 10개로 고정시켜놓고 추가될때마다 추가해야된다.
	//
	ModelRow =  modelList.TotalCount + 1;// MAX_MODEL_CNT + 1;//아래
	ModelCol = 2;//옆
	int marginx = 20;
	int marginy = 4;
	int gridHeight = 40;
	int gridWidth1 = 55;
	int gridWidth2 = 250;
	int totalWidth = gridWidth1+(gridWidth2*(ModelCol-1));

	int GridCount = ModelRow;
	//
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	fixRow = 15 + 1;		//1은 title

	if (GridCount < fixRow)
	{
		GridCount = fixRow;	//칸 채우기위해
		marginx = 4;
	}
	rect.right = totalWidth + marginx;
	rect.bottom = (gridHeight * fixRow) + marginy;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.

	GetDlgItem(IDC_STATIC_MODEL_GRID)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGridModel.Create(rect, this, IDC_STATIC_MODEL_GRID, WS_TABSTOP | WS_VISIBLE);

	m_clGridModel.SetTextBkColor(GRID_COLOR_WHITE);
	m_clGridModel.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridModel.SetFixedTextColor(GRID_COLOR_WHITE);
	m_clGridModel.SetReference_Setting();
	m_clGridModel.EnableSelection(FALSE);
	m_clGridModel.SetRowCount(GridCount);
	m_clGridModel.SetColumnCount(ModelCol);
	m_clGridModel.SetFixedRowCount(1);
	m_clGridModel.SetFixedColumnCount(1);
	m_clGridModel.AutoSize();

	CString tmpStr="";
	m_clGridModel.SetItemText(0, 0, "NO");
	m_clGridModel.SetItemText(0, 1, "NAME");
	
	int i = 0, j = 0;
	for (i = 0; i < GridCount; i++)
	{
		m_clGridModel.SetRowHeight(i, gridHeight);
		tmpStr.Format("%d", i + 1);
		m_clGridModel.SetItemText(i + 1, 0, tmpStr);//No
		for (j = 0; j < ModelCol; j++)
		{
			m_clGridModel.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridModel.SetColumnWidth(j, gridWidth1);
				}else
				{
					m_clGridModel.SetColumnWidth(j, gridWidth2);
				}
			}			
		}
	}
	m_clGridModel.Invalidate();
}


void CModelDlg::ShowGridCtrl_Model(int nMode)	//0 = show , 1 = 생성 , 2 = 삭제
{
	int i;
	int j;
	CString tmpStr="";
	int marginy = 4;
	int marginx = 20;
	int gridHeight = 40;
	int gridWidth1 = 55;
	int gridWidth2 = 250;
	int GridCount = modelList.TotalCount + 1;
	int totalWidth = gridWidth1 + (gridWidth2*(ModelCol - 1));

	if (GridCount <= fixRow)
	{
		GridCount = fixRow;	//칸 채우기위해
		marginx = 4;
	}

	if (nMode == 1) 
	{
		//모델 추가
		m_clGridModel.SetRowCount(GridCount);// modelList.TotalCount + 1);
		m_clGridModel.SetRowHeight(modelList.TotalCount, gridHeight);
		for (j = 0; j < ModelCol; j++)
		{
			m_clGridModel.SetItemFormat(modelList.TotalCount, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		
	}
	CRect rect;
	CWnd *pWnd = (CWnd*)GetDlgItem(IDC_STATIC_MODEL_GRID);
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);
	

	/*rect.right = totalWidth + marginx;
	rect.bottom = (gridHeight * GridCount) + marginy;*/
	GetDlgItem(IDC_STATIC_MODEL_GRID)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGridModel.MoveWindow(rect);
	//m_clGridModel.setwid
	//그리스 사이즈를 바꿔야된다.

	//rect.right = totalWidth + marginx;
	//rect.bottom = (gridHeight * fixRow) + marginy;
	//pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.


	for (int i = 0; i < modelList.TotalCount; i++)//for (int i=0 ; i<MAX_MODEL_CNT ; i++)
	{
		tmpStr.Format("%d", i + 1);
		m_clGridModel.SetItemText(i+1, 0, tmpStr);//No
		tmpStr.Format("%s", modelList.ModelName[i]);
		m_clGridModel.SetItemText(i+1, 1, tmpStr);//Model
	}






	tmpStr.Format("%s", modelList.curModelName);

	for (i = 0; i<modelList.TotalCount + 1; i++)//for (i=0 ; i<MAX_MODEL_CNT+1 ; i++)
	{
		if (strcmp(tmpStr, modelList.ModelName[i]) == 0)
		{
			changeModelNo(i + 1);
			break;
		}
	}
	tmpStr.Empty();
	m_clGridModel.Invalidate();
}
void CModelDlg::setInterface()
{
	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;

	WINDOWPLACEMENT wndpl;
	this->GetWindowPlacement(&wndpl);

	
	wndpl.rcNormalPosition = pFrame->m_rectCamDispPos2;
	wndpl.rcNormalPosition.right = MAIN_DLG_SIZE_X;
	wndpl.rcNormalPosition.left = pFrame->m_rectCamDispPos2.left;
	wndpl.rcNormalPosition.top -= SUB_DLG_OFFSET_Y - 10;
	wndpl.rcNormalPosition.bottom = MAIN_DLG_SIZE_Y - 5 - 90;

	this->MoveWindow(&wndpl.rcNormalPosition);

}

void CModelDlg::initModelGrid()
{
	
}

int CModelDlg::getCurRowOnGrid()
{
	return 1;
}

void CModelDlg::putData()
{
	CString sEditData;
	CString sTimeData;
	int len = 1;
	sEditData.Format(_T("%d"), sysData.m_Epoxy_Shot);
	SetDlgItemText(IDC_EDIT_EPOXY_SHOT, sEditData);
	sEditData.Format(_T("%d"), sysData.m_Epoxy_Alarm);
	SetDlgItemText(IDC_EDIT_EPOXY_ALARM, sEditData);
	sTimeData.Format(_T("%d"), sysData.m_Epoxy_Start_Time);
	len = sTimeData.GetLength();
	if(len != 6)
	{	
		sEditData.Format(_T("0%sD %s:%s"), sTimeData.Left(1), sTimeData.Mid(1, 2), sTimeData.Right(2));
	}
	else 
	{
		sEditData.Format(_T("%sD %s:%s"), sTimeData.Left(2), sTimeData.Mid(2, 2), sTimeData.Right(2));
	}
	SetDlgItemText(IDC_EDIT_EPOXY_START_TIME, sEditData);
	sTimeData.Format(_T("%d"), sysData.m_Epoxy_Last_Time);
	len = sTimeData.GetLength();
	if(len != 6)
	{	
		sEditData.Format(_T("0%sD %s:%s"), sTimeData.Left(1), sTimeData.Mid(1, 2), sTimeData.Right(2));
	}
	else 
	{
		sEditData.Format(_T("%sD %s:%s"), sTimeData.Left(2), sTimeData.Mid(2, 2), sTimeData.Right(2));
	}
	SetDlgItemText(IDC_EDIT_EPOXY_LAST_TIME, sEditData);
	sEditData.Format(_T("%d"), sysData.m_Socket_Count);
	SetDlgItemText(IDC_EDIT_SOCKET_COUNT, sEditData);
	sEditData.Format(_T("%d"), sysData.m_Socket_Alarm);
	SetDlgItemText(IDC_EDIT_SOCKET_ALARM, sEditData);
	
	
	UpdateData(false);
}

void CModelDlg::OnBnClickedButtonCreate()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}
	CString strTemp="";
	if(modelList.TotalCount >= MAX_MODEL_CNT)
	{
		int _cnt = MAX_MODEL_CNT;
		strTemp.Format("모델 추가 개수 초과 [%d]" , _cnt);	//
		errMsg2(Task.AutoFlag, strTemp);
		return;
	}
	
	CKeyPadDlg keyDlg;

	keyDlg.m_strKeyPad = "Input Model Name";

	if (keyDlg.DoModal()==IDOK)
	{
		strTemp = keyDlg.GetstrKeypad();

		int strLength = strTemp.GetLength();
		if(strLength<1)
		{
			sLangChange.LoadStringA(IDS_STRING1219);	//모델명 입력이 비정상입니다.
			errMsg2(Task.AutoFlag, sLangChange);
			return;
		}
		if (ModelCheck(strTemp) == true)
		{
			//같은 모델이름 있으면 리턴

			errMsg2(Task.AutoFlag, _T("동일 모델 존재합니다."));
			return;
		}
	}
	else
	{
		return;
	}

	

	sprintf_s(modelList.ModelName[modelList.TotalCount++], sizeof(modelList.ModelName[modelList.TotalCount++]) , "%s", (LPTSTR)(LPCTSTR)strTemp);
	sprintf_s(modelList.curModelName, sizeof(modelList.curModelName),"%s", (LPTSTR)(LPCTSTR)strTemp);

	modelList.NewSave();
	modelList.NewLoad();

	//initModelGrid();
	ShowGridCtrl_Model(1);	//Create
	//sprintf_s(model.mCurModelName, sizeof(model.mCurModelName) , "%s", modelList.curModelName);

	model.Save();
	model.Load();

	work.Save();
	work.Load();

	MandoSfrSpec.save();
	MandoSfrSpec.load();

	model.AcmisDataSave();
	model.AcmisDataLoad();

	model.RoiSave();
	model.RoiLoad();

	for(int i = 0; i < MARK_CNT; i++)
	{
		int iCh = 1;
		if(i == PCB_Chip_MARK)	iCh = 0;

		for(int j = 0; j < 2; j++)
		{
			vision.geometricMarkPreProc(iCh, i, j);
		}
	}
	
	//CString folderPath;
	////ini폴더 복사
	//folderPath.Format("%s\\Model\\%s\\Initialize", DATA_DIR, strTemp);// modelList.curModelName);
	//if (GetFileAttributes(folderPath) == -1)
	//{
	//	CreateDirectoryA(folderPath, NULL);
	//}
	//! 검사 Spec 파일 Copy
	//CString strOldFile = _T("");
	//CString strNewFile = _T("");
	/*strOldFile.Format("%s\\Model\\SPEC_BASE.INI", DATA_DIR);
	strNewFile.Format("%s\\Model\\%s\\SPEC.INI", DATA_DIR, model.name);
	CopyFile(strOldFile, strNewFile, TRUE);

	strOldFile.Format("%s\\Model\\TestPattern_raw3.dat", DATA_DIR);
	strNewFile.Format("%s\\Model\\%s\\TestPattern_BASE.dat", DATA_DIR, model.name);
	CopyFile(strOldFile, strNewFile, TRUE);*/


	initListBox();
	dispCurSensor();

	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	pFrame->DispCurModelName(model.mCurModelName);


	strTemp.Empty();
}


void CModelDlg::dispCurModel()
{
	int i;
	CString strCurName;

	strCurName.Format("%s", modelList.curModelName);
	//modelList.TotalCount
	for (i = 0; i<modelList.TotalCount + 1; i++)//for (i=0 ; i<MAX_MODEL_CNT+1 ; i++)
	{
		if (strcmp(strCurName, modelList.ModelName[i])==0)
			break;
	}
	m_clGridModel.Invalidate();
	//m_gridModel.SetRow(i+1);
	//m_clGridModel.SetRowCount(i+1);
}


void CModelDlg::copyModel(int iScrNo, int iDesNo)
{
	CString strScr="";
	CString strDes="";

	strScr = m_clGridModel.GetItemText(iScrNo, 1);
	strDes = m_clGridModel.GetItemText(iDesNo, 1);

	//sprintf_s(model.mCurModelName, sizeof(model.mCurModelName), "%s", (LPTSTR)(LPCTSTR)strScr);
	//_stprintf_s(model.mCurModelName, SIZE_OF_100BYTE, _T("%s"), strScr);
	model.mCurModelName.Format(_T("%s"), strScr);
	model.Load();
	//sprintf_s(model.mCurModelName, sizeof(model.mCurModelName) , "%s", (LPTSTR)(LPCTSTR)strDes);
	//_stprintf_s(model.mCurModelName, SIZE_OF_100BYTE, _T("%s"), strDes);
	model.mCurModelName.Format(_T("%s"), strDes);
	model.Save();

	sprintf_s(modelList.curModelName, sizeof(modelList.curModelName) ,  "%s", model.mCurModelName);
	
	modelList.NewSave();
	model.Load();

	for(int i = 0; i < MARK_CNT; i++)
	{
		int iCh = 1;
		if(i == PCB_Chip_MARK)	iCh = 0;
		for(int j = 0; j < 2; j++){
			vision.geometricMarkPreProc(iCh, i, j);
		}
	}
}


void CModelDlg::OnBnClickedButtonDelete()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	if (modelList.TotalCount ==1)
	{
		sLangChange.LoadStringA(IDS_STRING1206);	//등록된 모델이 1개입니다.
		errMsg2(Task.AutoFlag, sLangChange);
		return;
	}
	CString strTemp = "";
	int iCurRow = ModelCurCol;//getCurRowOnGrid()-1;

	if(iCurRow > modelList.TotalCount)
	{
		strTemp.Format("등록된 모델이 없습니다.");
		errMsg2(Task.AutoFlag, strTemp);
		return;
	}
	//==========================================================
	CKeyPadDlg keyDlg;
	strTemp.Format("Password를 입력하세요.");
	keyDlg.m_strKeyPad = strTemp;
	bool rtn = false;
	if (keyDlg.DoModal()==IDOK)
	{
		strTemp = keyDlg.GetstrKeypad();

		rtn = !strTemp.CompareNoCase(password.m_szPassword);
		if(!rtn)
		{
			strTemp.Format("Password를 잘 못 입력했습니다.");
			errMsg2(Task.AutoFlag, strTemp);	
			return;
		}
	}
	else
	{
		return;
	}
	//==========================================================
	int CurrentNum = iCurRow - 1;		//Grid라서 -1함
	if (iCurRow >= modelList.TotalCount)
	{
		sprintf_s(modelList.ModelName[CurrentNum], sizeof(modelList.ModelName[CurrentNum]), "");
	}
	else
	{
		for (int i = CurrentNum; i < modelList.TotalCount; i++)
		{
			sprintf_s(modelList.ModelName[i], sizeof(modelList.ModelName[i]), "");
			sprintf_s(modelList.ModelName[i], sizeof(modelList.ModelName[i]), "%s", modelList.ModelName[i + 1]);
		}
	}
	if (CurrentNum == modelList.CurrentModelIndex)
	{
		int curIndex = CurrentNum - 1;// iCurRow - 2;
		if (curIndex < 0)		curIndex = 0;

		sprintf_s(modelList.curModelName, sizeof(modelList.curModelName), "%s", modelList.ModelName[curIndex]);
		modelList.CurrentModelIndex = curIndex;
		modelList.TotalCount--;
		modelList.NewSave();
		modelList.NewLoad();
		//sprintf_s(model.mCurModelName, sizeof(model.mCurModelName), "%s", modelList.curModelName);
		MandoSfrSpec.load();

		model.Load();

		work.Load();
		model.PatternLoad();
		work.SaveCntLog();
		model.AcmisDataLoad();
		model.RoiLoad();

		theApp.MainDlg->DispCurModelName(model.mCurModelName);
		vision.UserHookData.liveMode = 1;

		changeModelNo(ModelCurCol);
	}
	
	

	//initModelGrid();
	ShowGridCtrl_Model();	//delete
}


BOOL CModelDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	//if ( m_bShowFlag == true )
	//{
	//	m_gridModel.GetWindowRect(&m_rcGridModel);

	//	if ( m_rcGridModel.PtInRect(pt) == TRUE )
	//	{
	//		if ( zDelta <= 0 )   //! (-) 아래쪽
	//		{
	//			DWORD dwTemp = SB_LINEDOWN;
	//			m_gridModel.SendMessage(WM_VSCROLL, dwTemp, NULL);
	//		}
	//		else			     //! (+) 윗쪽
	//		{
	//			DWORD dwTemp = SB_LINEUP;
	//			m_gridModel.SendMessage(WM_VSCROLL, dwTemp, NULL);
	//		}
	//	}
	//}
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}

//! Modified by LHW (2013/4/24)
void CModelDlg::initListBox()
{
	if ( MIU.m_iSensorListCnt <= 0 )
	{
		return;
	}
}

//! Modified by LHW (2013/4/24)
void CModelDlg::initListBox2(int iIndex)
{
}



void CModelDlg::dispCurSensor()
{
	CString sTemp = _T("");

	if ( MIU.m_iSensorListCnt > 0 && MIU.m_pSID != NULL )
	{
		int iIndex_Sensor_ID   = model.m_iSensorID;

		if ( iIndex_Sensor_ID >= 0 && iIndex_Sensor_ID < MIU.m_iSensorListCnt )
		{
			if ( MIU.m_pSID[iIndex_Sensor_ID].nInfoCount > 0 && MIU.m_pSID[iIndex_Sensor_ID].pInfo != NULL )
				sTemp.Format(_T("%s_%s"), MIU.m_pSID[iIndex_Sensor_ID].szSensorName, MIU.m_pSID[iIndex_Sensor_ID].pInfo[0].szResolution);
		}
	}

	int length = sTemp.GetLength();
}


BEGIN_EVENTSINK_MAP(CModelDlg, CDialogEx)
	//ON_EVENT(CModelDlg, IDC_MSFLEXGRID_MODEL, DISPID_DBLCLICK, CModelDlg::DblClickMsflexgridModel, VTS_NONE)
	//ON_EVENT(CModelDlg, IDC_MSFLEXGRID_EPOXY_INSP_PARA, DISPID_CLICK, CModelDlg::ClickMsflexgridEpoxyInspPara, VTS_NONE)
END_EVENTSINK_MAP()

void CModelDlg::OnGridClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
	ModelCurCol = pItem->iRow; 

	if (ModelCurCol > modelList.TotalCount)
	{
		ModelCurCol = modelList.TotalCount;
	}
	

   // Trace(_T("Clicked on row %d, col %d\n"), pItem->iRow, pItem->iColumn);
}
void CModelDlg::changeModelNo(int IndexNo)
{
	//
	for (int i = 0; i < modelList.TotalCount; i++)//for (int i = 0; i < MAX_MODEL_CNT; i++)
	{
		m_clGridModel.SetItemBkColor(i + 1, 1, GRID_COLOR_WHITE);
	}

	m_clGridModel.SetItemBkColor(IndexNo, 1, GRID_COLOR_SELECT);
	m_clGridModel.Invalidate();
}
void CModelDlg::OnDBClickedGridModelb(NMHDR* pNMHDR, LRESULT* pResult)
{
	return;


	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
	
	int col = pNMGridView->iColumn;
	int row = pNMGridView->iRow;
	if(col<1 || row<1)										//JJH.	수정
		return;

	if(row > modelList.TotalCount)
	{
		return;
	}

	vision.UserHookData.liveMode = 0;
	Sleep(100);

	return;

	sprintf_s(modelList.curModelName,sizeof(modelList.curModelName) ,  "%s", modelList.ModelName[row-1]);


	
	modelList.NewSave();
	modelList.NewLoad();	//ModelLoad();

	MandoSfrSpec.NewSfrLoad();// load();

	model.Load();

	work.Load();
	model.PatternLoad();
	work.SaveCntLog();
	model.AcmisDataLoad();
	model.RoiLoad();

	initModelGrid();


	//initListBox();
	//dispCurSensor();

	theApp.MainDlg->DispCurModelName(model.mCurModelName);
	vision.UserHookData.liveMode = 1;
}
//! Modified by LHW (2013/4/24)
void CModelDlg::DblClickMsflexgridModel()
{
	//int col = m_gridModel.GetMouseCol();
	//int row = m_gridModel.GetMouseRow();

	/*if(row<1 || row > modelList.cnt)
	{
		dispCurModel();
		return;
	}

	vision.UserHookData.liveMode = 0;
	Sleep(100);

	sprintf_s(modelList.curModelName, "%s", modelList.name[row-1], 49);

	modelList.Save();
	modelList.Load();
	model.Load();

	initModelGrid();
	dispCurModel();

	initListBox();
	dispCurSensor();

	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	pFrame->DispCurModelName(model.name);

	vision.UserHookData.liveMode = 1;*/
}

void CModelDlg::OnBnClickedButtonParametersetting()
{
	CInfoDlg infoDlg;
	infoDlg.DoModal();
}

void CModelDlg::OnBnClickedButtonDataset()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	if(Task.AutoFlag == 2)
	{
		sLangChange.LoadStringA(IDS_STRING1468);
		delayMsg(sLangChange, 2000, M_COLOR_RED);// 일시 정지 중 사용 불가
		return;
	}


	bool passFlag = false;

	if(passFlag == false)
	{
		CString strTemp="";
		CKeyPadDlg keyDlg;

		strTemp.Format("Password를 입력하세요.");
		keyDlg.m_strKeyPad = strTemp;

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


	CDataSet DataSet;
	DataSet.DoModal();
}


void CModelDlg::OnBnClickedButtonFreeRun()
{
	if(Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}

	if(Task.AutoFlag == 2)
	{
		sLangChange.LoadStringA(IDS_STRING1468);
		delayMsg(sLangChange, 2000, M_COLOR_RED);// 일시 정지 중 사용 불가
		return;
	}


	CAABonderDlg* pFrame = (CAABonderDlg*)AfxGetApp()->m_pMainWnd;
	int iRtn = pFrame->freeRun();

	if(iRtn==0)
	{
		m_btnFreeRun.m_iStateBtn	= 0;
		m_btnFreeRun.Invalidate();
	}
	else if(iRtn == 1)
	{
		m_btnFreeRun.m_iStateBtn	= 1;
		m_btnFreeRun.Invalidate();
	}
}


void CModelDlg::OnBnClickedButtonSfrSpec()
{
	theApp.MainDlg->sfrSpecDlg->ShowWindow(SW_SHOW);
	
}


void CModelDlg::OnBnClickedBtnBarcode()
{
	
	CBarcodeDlg dlg;
	dlg.DoModal();
}




void CModelDlg::ClickMsflexgridEpoxyInspPara()
{
	
}


void CModelDlg::OnStnClickedEditEpoxyShot()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CModelDlg::OnStnClickedEditEpoxyAlarm()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);

	if(dlg.DoModal() == IDOK)
	{
		m_Epoxy_Alarm.SetText(dlg.GetstrNum());
	}
	UpdateData(FALSE);
	CString sEditData;
	GetDlgItemText(IDC_EDIT_EPOXY_ALARM, sEditData);
	sysData.m_Epoxy_Alarm = atoi(sEditData);
	sysData.Save();
}


void CModelDlg::OnStnClickedEditEpoxyStartTime()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CModelDlg::OnStnClickedEditEpoxyLastTime()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CModelDlg::OnBnClickedButtonEpoxyReset()
{
	SYSTEMTIME SysTime;
	::GetLocalTime(&SysTime);
	CString timeData="";
	CString dispData="";
	timeData.Format("%02d%02d%02d", SysTime.wDay, SysTime.wHour, SysTime.wMinute);
	dispData.Format("%sD %s:%s", timeData.Left(2), timeData.Mid(2, 2), timeData.Right(2));
	m_Epoxy_Shot.SetText("0");
	m_Epoxy_Start_Time.SetText(dispData);
	m_Epoxy_Last_Time.SetText(dispData);
	sysData.m_Epoxy_Shot = atoi("0");
	sysData.m_Epoxy_Start_Time = atoi(timeData);
	sysData.m_Epoxy_Last_Time = atoi(timeData);

	sysData.Save();
}


void CModelDlg::OnStnClickedEditSocketCount()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CModelDlg::OnStnClickedEditSocketAlarm()
{
	CString celData;
	CGetNumDlg dlg(10, (LPTSTR)(LPCTSTR)celData);
	if(dlg.DoModal() == IDOK)
	{
		m_Socket_Alarm.SetText(dlg.GetstrNum());
	}
	UpdateData(FALSE);
	CString sEditData;
	GetDlgItemText(IDC_EDIT_SOCKET_ALARM, sEditData);
	sysData.m_Socket_Alarm = atoi(sEditData);
	sysData.Save();
}


void CModelDlg::OnBnClickedButtonSocketReset()
{
	m_Socket_Count.SetText("0");
	sysData.m_Socket_Count = atoi("0");

	sysData.Save();
}

void CModelDlg::OnBnClickedBtnEepromDlg()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CModelDlg::OnBnClickedButtonModelLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}
	if (ModelCurCol < 1)
	{
		delayMsg(_T("모델 선택 확인바랍니다"), 2000, M_COLOR_RED);
		return;
	}
	if (ModelCurCol > modelList.TotalCount)
	{
		delayMsg(_T("모델 선택 확인바랍니다"), 2000, M_COLOR_RED);
		return;
	}
	CString strLog = _T("");
	int loadIndex = ModelCurCol - 1;
	strLog.Format(_T("%s 모델 로드 하시겠습니까?"), modelList.ModelName[loadIndex]);
	if (askMsg(strLog) == false)
	{
		return;
	}
	vision.UserHookData.liveMode = 0;
	Sleep(100);
	modelList.CurrentModelIndex = loadIndex;
	sprintf_s(modelList.curModelName, sizeof(modelList.curModelName), "%s", modelList.ModelName[loadIndex]);


	modelList.NewSave();
	modelList.NewLoad();
	sysData.Load();
	MIU.ImageBufferSet();
	MandoSfrSpec.NewSfrLoad();
	
	model.Load();

	work.Load();
	model.PatternLoad();
	work.SaveCntLog();
	model.AcmisDataLoad();
	model.RoiLoad();

	vision.MiuBufferAlloc(gMIUDevice.nWidth, gMIUDevice.nHeight);

	theApp.MainDlg->DispCurModelName(model.mCurModelName);
	vision.UserHookData.liveMode = 1;

	changeModelNo(ModelCurCol);

	
	strLog.Format(_T("[MODEL] %s/%d - Load 완료") , modelList.curModelName , ModelCurCol);
	delayMsg(strLog, 2500, M_COLOR_CYAN);
}
bool CModelDlg::FnAllFolderCopy(CString Src, CString Dest)//LPCTSTR Src, LPCTSTR Dest)
{
	HANDLE hSrch;
	WIN32_FIND_DATA wfd;
	BOOL bResult = TRUE;
	TCHAR WildCard[MAX_PATH];
	TCHAR SrcFile[MAX_PATH];
	TCHAR DestFile[MAX_PATH];

	wsprintf(WildCard, "%s\\*.*", Src);
	CreateDirectory(Dest, NULL);
	hSrch = FindFirstFile(WildCard, &wfd);
	if (hSrch == INVALID_HANDLE_VALUE) 
	{
		return false;
	}
	while (bResult) 
	{
		wsprintf(SrcFile, "%s\\%s", Src, wfd.cFileName);
		wsprintf(DestFile, "%s\\%s", Dest, wfd.cFileName);
		// 서브 디렉토리가 발견되면 서브 디렉토리를 복사한다.
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			if (lstrcmp(wfd.cFileName, ".") && lstrcmp(wfd.cFileName, "..")) 
			{
				FnAllFolderCopy(SrcFile, DestFile);
			}
		}
		else {
			CopyFile(SrcFile, DestFile, FALSE);
		}
		bResult = FindNextFile(hSrch, &wfd);
	}
	FindClose(hSrch);
	return true;
}
bool CModelDlg::ModelCheck(CString newModel)
{
	int i = 0;
	for (i = 0; i < modelList.TotalCount; i++)
	{
		if (modelList.ModelName[i] == newModel)
		{
			return true;
		}
	}

	return false;
}
void CModelDlg::OnBnClickedButtonCopy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (Task.AutoFlag == 1)
	{
		sLangChange.LoadStringA(IDS_STRING1463);
		delayMsg(sLangChange, 1000, M_COLOR_RED);
		return;
	}
	CString strTemp = "";
	if (modelList.TotalCount >= MAX_MODEL_CNT)
	{
		int _cnt = MAX_MODEL_CNT;
		strTemp.Format("모델 추가 개수 초과 [%d]", _cnt);	//
		errMsg2(Task.AutoFlag, strTemp);
		return;
	}

	CKeyPadDlg keyDlg;

	keyDlg.m_strKeyPad = "Input Model Name";

	if (keyDlg.DoModal() == IDOK)
	{
		strTemp = keyDlg.GetstrKeypad();

		int strLength = strTemp.GetLength();
		if (strLength<1)
		{
			sLangChange.LoadStringA(IDS_STRING1219);	//모델명 입력이 비정상입니다.
			errMsg2(Task.AutoFlag, sLangChange);
			return;
		}
		if (ModelCheck(strTemp) == true)
		{
			//같은 모델이름 있으면 리턴
			
			errMsg2(Task.AutoFlag, _T("동일 모델 존재합니다."));
			return;
		}
	}
	else
	{
		return; 
	}
	CString SrcFolder;
	SrcFolder.Format(_T("%s\\%s"), AA_MODEL_LOAD_DIR, modelList.curModelName);
	
	sprintf_s(modelList.ModelName[modelList.TotalCount++], sizeof(modelList.ModelName[modelList.TotalCount++]), "%s", (LPTSTR)(LPCTSTR)strTemp);
	//복사만해서 모델 체인지 없음
	modelList.NewSave();
	modelList.NewLoad();

	ShowGridCtrl_Model(1);	//Create

	CString DestFolder;
	DestFolder.Format(_T("%s\\%s"), AA_MODEL_LOAD_DIR, strTemp);
	FnAllFolderCopy(SrcFolder, DestFolder);

	SrcFolder.Empty();
	DestFolder.Empty();
}
