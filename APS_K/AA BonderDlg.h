
// AA BonderDlg.h : 헤더 파일
//

#pragma once


#include "afxdialogex.h"
#include "Label/Label.h"
#include "ExButton/exbutton.h"
#include "afxwin.h"
#include "Socket/ConnectSocket.h"
#include "Socket/ClientSocket.h"
#include "Socket/ListenSocket.h"
#include "Utility\GridCtrl\GridCtrl.h"
#include "PRI_INSP/MandoFinalSFR.h"
#include "Utility\Serial\Serial.h"
//
#include "LensDlg.h"
#include "LensEdgeDlg.h"
#include "PcbDlg.h"
#include "CcdDlg.h"
#include "CCDSFRDlg.h"
#include "IoDlg.h"
#include "ModelDlg.h"
#include "SfrSpec.h"
#include "AutoDispDlg.h"
#include "AlarmDialog.h"
#include "LightDlg.h"
#include "LensTeaching.h"
#include "PcbTeaching.h"
#include "PcbTeachingDis.h"
#include "CCDInspModeDlg.h"
#include "ChartSetDlg.h"
#include "Insp_Spec_Set.h"
#include "LogThread.h"
#include "MesConnSocket.h"

#include "PcbProcess1.h"
#include "PcbProcess2.h"


//class CLightDlg;

#include <queue>
#include <mutex>
#include <condition_variable>
// CAABonderDlg 대화 상자
class CAABonderDlg : public CDialogEx
{
// 생성입니다.
public:
	CAABonderDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_AABONDER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.

protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CPcbProcess2 pcbProcess;
	
	
	

	CSfrSpec*					sfrSpecDlg;// = NULL;
	CChartSetDlg*				chartSetDlg;// = NULL;
	CLensDlg*					lensDlg;// = NULL;
	CLensEdgeDlg*			lensEdgeDlg;// = NULL;
	CPcbDlg*					pcbDlg;// = NULL;
	CCcdDlg*					ccdDlg;// = NULL;
	CMotorDlg*				motorDlg;// = NULL;
	CMotorDlg2*				motorDlg2;// = NULL;
	CMotorDlg3*				motorDlg3;// = NULL;
	CIoDlg*						ioDlg;// = NULL;
	CModelDlg*				modelDlg;// = NULL;
	CAutoDispDlg*			autodispDlg;// = NULL;
	CInsp_Spec_Set*		InspSpecSet;// = NULL;

	CMesConnSocket m_clBarcodeConnSocket;

//	int		_checkMaxSfrPos_B(int iMode);			// 정재호 주석 처리.
	bool	MoveOffset_Z();
	void	ctrlSubDlg(int iDlgNo);
	void	setCamDisplay(int camNo, int mode);	
	void	dispStepOnButton(int iCtrlNo, int iState);
	void	putListLog(CString strLog);
	void	loadStandardCursor();
	void	destoryStandardCursor();
	void	changeCursor(CPoint p, CRect rcTemp);
	int		checkMousePos(CPoint p, CRect rcTemp);
	int		AlignLimitCheck(int Insptype, double dOffsetX, double dOffsetY, double dOffsetTh);										// [Insptype] 0:Lens PreAlign 1:PCB PreAlign
	int		TiltAlignLimitCheck(double dOffsetX, double dOffsetY);
	double  HolderThetaCalc(double _theta , int index);
	void	dispLotName();
	void	SetDigReference(int iMark);
	void threadExit();
	int WaitThreadEndH(HANDLE _hThread, int _nWaitMilSec, LPCTSTR _sMsg, bool _bClose);
	void MainEpoxyRun();
	
	int ccdPosLeft;
	int ccdPosRight;
	//! Added by LHW (2013/3/27)
	int     Update_CCD_Display();


	int		procCamAlign(int iCamNo, int iMarkType, bool liveMode, double &dOffsetX, double &dOffsetY, double &dOffsetTh);
	int		procCamComAlign(int camNo, int iMarkType, bool liveMode, double &dOffsetX, double &dOffsetY, double &dOffsetTh);
	
	int		_checkPcbMotor();							/* PCB 모터 위치 확인 */
	int		_getMTF(int iMode, bool LogView = true);				/* MTF값 획득 */	//int iMode =SFR_FIRST
	int		_moveZMotor(double dDist, double dVel);		/* Z 모터 이동 */
	int		_checkMaxSfrPos(int iMode);	
	
	double GetFoV(LPBYTE Rgb,int Width, int Height,CPoint Center);
	double GetDistortion(LPBYTE Rgb,int m_Width, int m_Height,CPoint Center);
	CPoint GetCrossPos(int x,int y,int size,LPBYTE Rgb,int Width, int Height,CPoint cpCenter);
	CPoint GetCrossPos2(int x,int y,int size,LPBYTE Rgb,int Width, int Height,CPoint cpCenter);
	bool findFiducialMark(LPBYTE Rgb, int sizeX, int sizeY, CPoint* cpFiducialPos);
	CPoint GetCirclePos(LPBYTE Rgb, int sizeX, int sizeY, CRect crFiducialRoi);
	CPoint GetCirclePos(LPBYTE Rgb, int sizeX, int sizeY, CRect crFiducialRoi,bool bOver);
	void Mark_Area(int x1, int y1, int x2, int y2, COLORREF color, int Width, int Height, LPBYTE Rgb);
	void Mark_Cross(int x1, int y1, int x2, int y2, COLORREF color, int Width, int Height, LPBYTE Rgb);

	BYTE m_BtblITU[256][256];
	BYTE m_RtblITU[256][256];
	BYTE bmph[100];
	CxImage* m_pImage;
	int m_FileType;
	CStatic m_ImageView;
	CxImage* m_img;
	int m_Height;
	int m_Width;
	HGLOBAL m_Rgb_Handle;
	LPSTR m_pRgb;
	unsigned char*	m_InImg;
	BYTE*			m_SrcData;
	BYTE*			m_SrcData2;
	BITMAPINFO* m_BmInfo;
	
	int	caclCodeVal(double dFov[5]);


	std::ofstream logFile;

	int		_procTiltX();							//  X 계산 후 이동
	int		_procTiltY();							// Y 계산 후 이동

	bool	_calcLaserTilt(CDPoint dMotorPos[4], double dLaser[4], double &TX, double &TY);
	double	_calcTiltX();							/* Tilt X 계산 */
	double	_calcTiltY();							/* Tilt Y 계산 */

	bool	_calcImageAlignment();
	bool	_MotorMove_IMG_Align();
	bool	_MotorMove_IMG_AlignTheta();
	bool	_MotorMove_IMG_AlignXYT();

	
	int TITLE_MOTOR_Z;
	int TITLE_MOTOR_TX;
	int TITLE_MOTOR_TY;
	int TITLE_MOTOR_X;
	int TITLE_MOTOR_Y;
	int		_findOpticalCenter();					/* 광축 찾기 */
	int		_moveXYMotor();							/* 광축 보정값 X, Y 이동 */
	bool	_GetOpticAxis(int fi_scale, int fi_thVal, double &fo_dOffsetX, double &fo_dOffsetY);
	
	//int		emission_process(int iStep);
	CLogThread m_clLogThread;

	bool	func_MIU_ConnectLiveCheck();
	bool	Bonding_Pos_Ckeck();

	double  calcColorBalance(cv::Mat src, int nColorOrder);
	double	calcMeanRoI(cv::Mat src, int nRoIsize);

	int		NG_process(int iStep);
	int		Test(int iStep);
	void	SocketTableCheck(int Mode);


	void	Delete_Child_Dialog();
	void	Make_Child_Dialog();

	void	DispCurModelName(CString sName);

	void	initGrid();
	void	dispGrid();
    bool    g_CalcImageAlign(bool bRotationUse = true);

	//bool    
	void	initInspResGrid();
	void	dispInspResGrid();

	int		_checkDecreaseSFR();
	void	drawLine_MeasureDist(int iMode);			/* 거리측정용 라인 그리기 iMode 0 : 기본 위치 1: 이동 위치 */
	int		changeCursor_MeasureMode(CPoint p);			/* 거리측정 중일 때 마우스 커서 변환 */

	void	DisableButton(bool AutorunFlag);

	bool	ReadSensorID(int readMode, CString strID);
	void	AutoRunView(int curstate);



	// 검사 DLL 사용
	bool	checkDarkDefect_PreUV();				// UV전 Dark Defect 검사 결과 확인용.
	bool	checkLightDefect_PreUV();				// UV전 Light Defect 검사 결과 확인용.

	bool	func_MTF(BYTE* ChartRawImage, bool bAutoMode = true, int dindex = 0);


	int   totalStainNum;


	bool	MoveOffset_Prev_UV();

	bool	m_bMiuRun;  
	CCriticalSection m_csLock_Miu; //! m_rect_CCD_Zoom 보호용
	CCriticalSection m_csLock_Socket; //! 이더넷 통신 알람 방지용

	bool MIUCheck_process();

	void DeleteOldData(int year, int month, int day);

	BOOL m_bMeasureDist;		/* 직선 간의 거리 측정 */
	BOOL m_bLogView;
	BOOL m_bBcrAutoCount;

	bool m_bDrawMeasureLine;
	int		m_iType_MeasureLine;
	bool m_bProComp;
	bool m_bQmode;
	int		m_iLine_Left;
	int		m_iLine_Top;
	int		m_iLine_Right;
	int		m_iLine_Bottom;

	CListBox	m_listLog;
	CFont		font;

	CLabel	m_labelMenu;
	CLabel	m_labelTitle;
	CLabel	m_labelHom;
	CLabel	m_labelServo;
	CLabel  m_labelMes;
	CLabel	m_labelUsbModule;
	CLabel	m_labelUsbLive;
	CLabel	m_labelTime;

	CLabel	m_labelPickupNoPcb;
	CLabel	m_labelPickupNoLensCentering;
	CLabel	m_labelPickupNoLensGrip;


	CLabel m_labelThread1;
	CLabel m_labelThread2;

	CLabel m_labelCurModelName;
	CLabel m_labelCCD_ID;
	CLabel	m_labelLotName;
	CLabel	m_labelCcdRetryCnt;

	CRect	m_rectCcdDispPos;
	CRect	m_rectCamDispPos1, m_rectCamDispPos2,m_rectCamDispPos3;
	CRect	m_rBox;
	CRect	m_rcFixedBox;

	bool	m_bDrawFlag;
	bool	m_bBoxMoveFlag;
	bool	m_bBoxMoveFlag_CCD;
	bool	m_bisAlignBtn;
	bool	m_bisMotorBtn;
	bool	m_bisLightBtn;

	//! <-----------------------------------------------------------------------------------------
	//! Added by LHW (2013/3/27)
	CPoint  m_ViewPos;					//! CCD 화면에서 영상의 왼쪽 위 부분의 위치
	bool    m_bState_CCD_Zoom;			//! true이면 CCD 화면에서 확대된 상태
	bool    m_bBox_CCD_Zoom;			//! true이면 CCD 화면에서 Zoom Area 조작 가능
	bool    m_bBox_Acting_CCD_Zoom;		//! true이면 CCD 화면에서 Zoom Area 조작 중
	bool    m_bActing_CCD_Zoom;			//! true이면 CCD 화면에서 Zoom된 상태
	bool    m_bPan_CCD_Zoom;			//! true이면 CCD 화면에서 Mouse로 화면 이동 가능
	bool    m_bActing_Pan_CCD_Zoom;		//! true이면 CCD 화면에서 Mouse로 화면 이동 중
	CRect            m_rect_CCD_Zoom;	//! CCD 화면이 확대되어 눈에 보이는 부분의 사각 영역
	CCriticalSection m_csLock_CCD_Zoom; //! m_rect_CCD_Zoom 보호용
	CPoint           m_PanMoveP;
	//! <-----------------------------------------------------------------------------------------

	CPoint	m_ClickP;
	CPoint	m_MoveP;

	int m_iOldDlgNo;
	int m_iCurCamNo;
	int m_iMoveType;
	int m_iNo_SFR;

	//! <---------------------------------------------------------------------------
	//! Added by LHW (2013/2/5)
	int      m_iMode_Mouse_Box;	//! Mouse로 사각 영역 설정하는 작업의 종류 값, 0 based
	void     Change_Mode_Mouse_Box(int iMode_Mouse_Box);
	COLORREF GetColor_Mouse_Box(int iMode_Mouse_Box);
	//! <---------------------------------------------------------------------------

	HCURSOR m_hCursor_Standard;
	HCURSOR	m_hCursor_Width;
	HCURSOR m_hCursor_Height;
	HCURSOR m_hCursor_Move;
	HCURSOR m_hCursor_NWSE;
	HCURSOR m_hCursor_NESW;

	

	int freeRun();


	double ChartCenterOffsetX, ChartCenterOffsetY;



	//void AdjustDisplaySize(unsigned char* pFrameBuffer, unsigned char* p2byteBuffer, RawImgInfo* pRawImgInfo);
	int LoadImageData(unsigned char* pDataBuffer, const char * _Filename);

private:
	int     area       [_DEF_MAX_BLOBS*4];
	float   gd         [_DEF_MAX_BLOBS*4];
	CvPoint	TopLeft    [_DEF_MAX_BLOBS*4];
	CvPoint	BottomRight[_DEF_MAX_BLOBS*4];
	CSerial m_clSerialBcr;

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonMain();
	afx_msg void OnBnClickedButtonLens();
	afx_msg void OnBnClickedButtonCcd();
	afx_msg void OnBnClickedButtonMotor();
	afx_msg void OnBnClickedButtonIo();
	afx_msg void OnBnClickedButtonModel();
	
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	
	CExButton m_btnOrigin;
	CExButton m_btnReady;
	CExButton m_btnAutorun;
	CExButton m_btnPause;
	CExButton m_btnStop;
	CExButton m_btnNgOut;
	CExButton m_btnPcbFinish;
	CExButton m_btnStart;

	afx_msg void OnBnClickedButtonLensSupply();
	afx_msg void OnBnClickedButtonPcbOsCheck();
	afx_msg void OnBnClickedButtonPcbSupply();
	afx_msg void OnBnClickedButtonCcdAlign();
	afx_msg void OnBnClickedButtonCcdInsp();
	afx_msg void OnBnClickedButtonOrigin();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	void CcmThreadStart();
	void CCMThreadStart_Auto_Exposure_Time();
	void CCMThreadStart_Auto_WhiteBalance();

	void calcCamRotatePos(int iCamNo, double dFindX, double dFindY, double dBaseX, double dBaseY, double& dCx, double& dCy);
	bool calcAlignData(int camNo, int iMarkType, double &dOffsetX, double &dOffsetY, double &dOffsetTh);


	char	sz_PCB_Error_Msg[256];
	char	sz_LENS_Error_Msg[256];
	int checkAutoRunLensAlarm(int fi_step);
	int checkAutoRunPcbAlarm(int fi_step);

	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonLight();
	afx_msg void OnBnClickedButtonPause();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonAutorun();
	afx_msg void OnBnClickedButtonReady();

	CLabel m_LabelDoor;

	void ChipIDCountPlus();
	void	  func_ChipID_Draw();
	void	  changeMainBtnColor(int dlg);
	int		  m_oldDlg;

	int	m_bIsLensMode;	// 0=Lens Chip, 1= PCB 상단, 2=Lens상단
	int m_bIsMotorMode;	// 0=

	DECLARE_EVENTSINK_MAP()
	int m_iCcd;
	afx_msg void OnBnClickedRadioAlign();
	afx_msg void OnBnClickedRadioCcd2();
	afx_msg void OnStnClickedLabelStatusUsbLive();
	afx_msg void OnBnClickedCheckDist();
	afx_msg void OnBnClickedButtonAlarm();
	void WriteRohm12Cbulk(int wRegAddr,unsigned char *wRegData,int len);
	virtual BOOL DestroyWindow();
	CExButton m_bMainBtn_Main;
	CExButton m_bMainBtn_Model;
	CExButton m_bMainBtn_Align;
	CExButton m_bMainBtn_Motor;
	CExButton m_bMainBtn_CCD;
	CExButton m_bMainBtn_IO;
	CExButton m_bMainBtn_Light;
	CExButton m_bMainBtn_Alarm;	
	afx_msg void OnStnClickedLabelStatusServo();
	afx_msg void OnBnClickedButtonNgOut();
	CExButton m_bPcbFinish;
	CExButton m_bDispenseFinish;
	CExButton m_bLensPassFinish;
	CExButton m_EpoxyTimeCheck;
	CExButton m_bProCompCheck;

	CExButton m_bSminiOQCheck;
	CExButton m_bSetDlg;
	afx_msg void OnBnClickedButtonPcbResult();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClickedLabelTitle();

protected:
	void	SetInterface();
	void	SetInterface_Button();
	void	SetInterface_Label();
	void	SetInterface_CreateDlg();

	
public:
	bool m_bBarcodeConnect;
	bool ConnectBarcode();
	void DisConnectBarcode();
	bool SendPacketToBarcode(bool bUse);

	void RecvBcrSerial();
	void ParseBcrSerial(unsigned char* pRecvBuff, int nRecvLen);
	void ParseHandBcrSerial(unsigned char* pRecvBuff, int nRecvHandLen);

	unsigned char m_sPacketBuff[SIZE_OF_1K];
	int m_nPacketBuffPosi;
	int m_nTotalPacketSize;
	bool m_bStxState;
	unsigned char m_sHandPacketBuff[SIZE_OF_1K];
	int m_nHandPacketBuffPosi;


	bool dwTickStartRun;
	int CamPosY;
	int baseGap;
	void	InstantMarkDelete(int iMarkType);

	bool	_EpoxyFinddispense(int PcbIndex);
	bool	_inspResign(bool autoMode, int index, int dispMode);
	bool	_inspResignHole(bool autoMode, int index, int dispMode);
	bool	_inspResignRect(bool autoMode, int index, int iDirection, int iRectCnt);		//KKYH 20150622 날개부분 검사 추가(iRectCnt : 0=LEFT, 1=RIGHT)

	bool	_inspResignHole(bool autoMode, int index, int dispMode, int iCirCnt, unsigned char *);
	bool	_inspResignRect(bool autoMode, int index, int iDirection, int iRectCnt, unsigned char *);		//KKYH 20150622 날개부분 검사 추가(iRectCnt : 0=LEFT, 1=RIGHT)

	bool	_inspResignHole(bool autoMode, int index, int dispMode, unsigned char *);
	bool	_inspLine(int sx, int sy, int ex, int ey, unsigned char *m_Imagebuf);
				

	afx_msg void OnStnClickedLabelCcdRetry();

	bool bLightCurtain; //수동에서 Light Curtain 감지 상태
	afx_msg void OnBnClickedButtonDispenseResult();
	afx_msg void OnBnClickedButtonProcomp();
	
	bool	func_Check_LaserValueErr(double dVal[4]);	//Laser 변위 측정값 이상 Check -> 4 Point 측정값이 모두 같다고 하면 Laser 이상한거임.

	CCriticalSection m_csImageGrab;

	/* 소켓 */
	//////////////////////////////////////////////////////////////////////////
	//!!! 서버
	CCriticalSection	m_csRcvMsg;
	CCriticalSection	m_csSendMsg;
	CListenSocket		m_ListenSocket;
	POSITION			m_pos[2];					/* 클라이언트의 링크 위치 */
	CString m_sOldRcvMsg;


	void		CreateServer();		/* 서버 생성 */
	void		CloseServer();		/* 서버 닫기 */
	void		CheckClientPosition(CSocket* pClient, CString sMsg);		/* 클라이언트 링크 위치 찾기 */
	void		ServerCheckMessage(CSocket* pClient, CString sMsg);			/* 클라이언트로부터 받은 메세지 처리 */
	bool		SendMessageToClient(int iCh, CString sMsg);					/* 클라이언트로 메세지 전송 */
	void		func_Control_StateChange(int iCh);


	//!!! 클라이언트
	bool   m_bisConnect;
	CConnectSocket	m_Socket;

	// 20141202 LHC - 클래스변수 하나 더 만들기
	CConnectSocket	m_SocketMes;
	bool	m_bMESConnect;

	void   showLanConnect();

	bool	ConnectToServer();          // 클라이언트가 서버에 접속할 때 사용하는 함수.
	bool	CheckMessage(CString sMsg);
	bool	SendMessageToServer(CString sMsg);

	void  func_SocketControl_ConnectCheck();
	void  MESConnectToServer();			// MES 서버로 접속하는 함수

	bool bEpoxyTimeChk;
	bool EpoxyTimeCheck(bool TimeFlag);
	CTime   today;



	void UnpackRaw10(unsigned char *src, unsigned short *dst, int rows, int cols);
	bool func_Insp_CurrentMeasure(bool bLogDraw=true, bool bAutoMode = false);			//전류 측정 검사


	
//////////////////////////////////////////////////////////////////////////
	CString getSensorID();


	void	func_Socket_Barcode();
	void	func_Set_SFR_N_Type();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonLensPassResult();
	afx_msg void OnBnClickedButtonMinimize();
	afx_msg void OnBnClickedButtonTimeCheck();
	afx_msg void OnStnClickedLabelLotName();
	afx_msg void OnBnClickedServerStart();
	afx_msg void OnBnClickedServerStop();
	afx_msg void OnBnClickedClientConnect();
	afx_msg void OnBnClickedClientDisconnect();
	afx_msg void OnBnClickedClientSend();
public:
	std::vector<BYTE> m_vFrameBuffer;
	std::vector<SHORT> m_12Buffer;

	std::vector<BYTE> vYImgBuffer;
	//std::vector<BYTE> vstainYImgBuffer;
	//std::shared_ptr<CAtomResolutionSFR> m_pChartProc;
	std::shared_ptr<ResolutionImageBufferManager> mgr;
	afx_msg void OnStnClickedLabelId();

	int output_Mode; //0 = hex , 1 = float
	void Rs232Init();
public:
	CLightDlg LightDlg;
	CGridCtrl m_clGridResult;
	void	InitGridCtrl_Result();
	void	ShowGridCtrl_Result();

	int ResultRow;
	int ResultCol;
	
	//
	afx_msg void OnDBClickedGridResult(NMHDR* pNMHDR, LRESULT* pResult);
	
	bool Start_Btn_On;
	afx_msg void OnBnClickedAutorunStart();
	afx_msg void OnBnClickedDoorOpen();
	afx_msg void OnBnClickedDoorClose();

	bool uart_ThreadFn();
	void ChartRoiReset();
	afx_msg void OnStnClickedLabelStatusMes();
	afx_msg void OnStnClickedLabelModelname();
	afx_msg void OnBnClickedButtonSminiOqmode();
	afx_msg void OnBnClickedButtonSetDlg();
	afx_msg void OnBnClickedCheckLogView();
	afx_msg void OnBnClickedCheckBcrCount();
	CExButton m_bProHolderBondingCheck;
	afx_msg void OnBnClickedButtonProcHolder();
};
