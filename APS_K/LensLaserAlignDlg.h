#pragma once

#include "Label/Label.h"
#include "Library/AutoRepeat/AutoRepeatButton.h"
#include "ExButton/exbutton.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "ContinuousButton.h"


class CLensDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLensDlg)

public:
	CLensDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CLensDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_LENS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	int dcode;
	bool	timerRunFlag;

	void	setInterface();
	void	initMarkGrid();
	void	ctrlLiveButton();
	void	getMarkSize();
	void	dispMarkImage();
	void	clickedMarkDisp(int iMarkNo);
	void	dispData();

	void	changeMotorNo(int motorNo);
	void	CheckJogMotorSpeed();

	int		gripErrCnt, centeringErrCnt, vaccumErrCnt;
	void	changeColorPcbCoverSensorBtn();		//Pcb 소켓 커버 Close 감지
	void	changeColorPcbTurnBtn();
	void	changeColorContactUpBtn();
	void	changeColorUvCylinderBtn();

	void	changeColorLensLiftBtn();
	void	changeColorOcLightBtn();
	void	changeColorGripBtn();
	void	changeColorPcbGripBtn();
	void	changeColorLensSensorBtn();			//Lens 감지 센서
	void	changeColorLensSensorLift();
	void	changeColorBackLightBtn();
	void	changeColorMotorPosBtn();				/* 모터위치이동 버튼 색상 바꾸기 */
	bool	checkCurMotorPos(int iPos);				/* 모터의 현재 위치 확인 */
	bool	checkCurMotorZPos(int iPos);			/* Z모터의 현재 위치 확인 */
	bool	checkCurMotorPosZ(int iPos);	/* 모터 위치 확인 */
	bool	checkCurInspXMotorPos(int iPos); /*INSP X 모터 위치 확인*/
	bool	checkMotorPos(int iPos);
	void    DigLedputData();


	int m_iMarkDispSizeX;
	int m_iMarkDispSizeY;
	int m_iMarkSizeX;
	int m_iMarkSizeY;
	int m_iMarkNo;
	int m_iSelMotor;
	int m_iMoveSpeed;
	int m_iCopyMarkNo;

	CRect m_rMarkBox;
	CRect m_rcFixedBox;

	bool m_bCopyFlag;

	CLabel m_labelDisp1;
	CLabel m_labelDisp2;

	CLabel m_labelAlignResult;


	double	m_fMotorJogSpeed;
	bool OLD_JogPlusflag;
	bool OLD_JogMinusflag;


public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	int m_iSelMoveType;
	afx_msg void OnBnClickedButtonBoxSpeed();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonLivemode();
	afx_msg void OnBnClickedButtonRegist();
	afx_msg void OnBnClickedButtonFind();
	afx_msg void OnBnClickedRadioPos();
	afx_msg void OnBnClickedRadioSize();
	afx_msg void OnBnClickedButtonBoxUp();
	afx_msg void OnBnClickedButtonBoxDown();
	afx_msg void OnBnClickedButtonBoxLeft();
	afx_msg void OnBnClickedButtonBoxRight();
	afx_msg void OnBnClickedButtonMotorSupply();
	afx_msg void OnBnClickedButtonMotorAlign();
	afx_msg void OnBnClickedButtonMotorBond();
	afx_msg void OnBnClickedButtonImgLoad();
	afx_msg void OnBnClickedButtonImgSave();
	afx_msg void OnBnClickedButtonMarkset();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonGripOn();
	afx_msg void OnBnClickedButtonGripOff();
	afx_msg void OnBnClickedButtonBacklightIn();
	afx_msg void OnBnClickedButtonBacklightOut();
	DECLARE_EVENTSINK_MAP()
	void DblClickMsflexgridMark();
	void DblClickMsflexgridMotor();
	afx_msg void OnBnClickedButtonMotorWait();
	afx_msg void OnBnClickedButtonAlignTest();
	afx_msg void OnBnClickedButtonMotorBond2();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnMenuCopy();
	afx_msg void OnMenuDelete();
	afx_msg void OnMenuPaste();
	CExButton m_btnGrip_ON;
	CExButton m_btnGrip_OFF;

	CExButton m_btnPcbTurn;
	CExButton m_btnPcbReTurn;
	
	CExButton m_btnContact_UP;
	CExButton m_btnContact_DOWN;
	
	
//	CButton m_btnBond;
//	CButton m_btnBond2;

	CExButton m_btnPcbCloseSonsor;
	CExButton m_btnCenteringOn;
	CExButton m_btnCenteringOff;
	CExButton m_btnLensSonsor;
	CExButton m_btnLensCoverUP;
	CExButton m_btnLensCoverDown;

	CExButton m_btnWaitPos;
	CExButton m_btnZWait;

	CExButton m_btnSupplyPos;
	CExButton m_btnSupplyPosZ;
	CExButton m_btnSupplyPos2;

	CExButton m_btnAlignPos;
	CExButton m_btnAlignPosZ;

	

	CExButton m_btnBondPos;
	CExButton m_btnBondPosZ;
	CExButton m_btnZBonding;
	CExButton m_btnBond2Pos;
	CExButton m_btn_PcbGrip_For;
	CExButton m_btn_PcbGrip_Back;
	CExButton m_btn_OC_For;
	CExButton m_btn_OC_Back;
	CExButton m_btnComAlign;

	CExButton m_btnDarkUp;
	CExButton m_btnDarkDown;

	CExButton m_btnDarkPos;
	CExButton m_btnDarkZPos;
    CExButton m_btnDefectPos;
    CExButton m_btnDefectPosZ;

	CExButton m_btnPcbLoadingPos;
	CExButton m_btnPcbLoadingZPos;
	CExButton m_btnCoverLoadingPos;
	CExButton m_btnCoverLoadingZPos;
	CExButton m_btnCoverUnLoadingPos;
	CExButton m_btnCoverUnLoadingZPos;

	CExButton m_btnHolderUvPos;
	CExButton m_btnHolderUvZPos;
	
	
    CExButton m_btn2800kPos;
    CExButton m_btn2800kPosZ;

	CExButton m_btnComAlignPos;
	CExButton m_btnComAlignPosZ;

	int pushErrCnt;
	void	changeColorOcBtn();			/* PCB Cover 전/후진 버튼 색상 바꾸기 */
	void	changeColorDarkBtn();			/* Dark 실린더 버튼 색상 바꾸기 */

	afx_msg void OnBnClickedButtonGotoPcbalign();
	CExButton m_btnPCB;
	CExButton m_btnLens;
	CExButton m_btnLensEdge;
	CExButton m_btnBackLightOn;
	CExButton m_btnBackLightOff;
	
	CExButton m_btnPcbGrip;
	CExButton m_btnPcbUnGrip;
	
	CExButton m_btnUVCylinder_Up;
	CExButton m_btnUVCylinder_Down;

//	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	bool func_TaskMovingCheck();
	bool func_MovingInterlock();

	CContinuousButton m_btn_BoxLeft;
	CContinuousButton m_btn_BoxUP;
	CContinuousButton m_btn_BoxRight;
	CContinuousButton m_btn_BoxDown;
	afx_msg void OnBnClickedButtonGotoLensalign();
	afx_msg void OnBnClickedButtonGotoLensedgeAlign();
	afx_msg void OnBnClickedButtonEdgePcbCoverUp();
	afx_msg void OnBnClickedButtonEdgePcbCoverDown();
	afx_msg void OnBnClickedButtonPcbCoverFor();
	afx_msg void OnBnClickedButtonPcbCoverBack();
	afx_msg void OnBnClickedButtonPcbDarkUp();
	afx_msg void OnBnClickedButtonMotorDarkInsp();
	afx_msg void OnBnClickedButtonMotorDefectInsp();
	afx_msg void OnBnClickedButtonPcbDarkDown();
	afx_msg void OnBnClickedButtonMotorSupply2();
	afx_msg void OnBnClickedButtonSilDown();
	afx_msg void OnBnClickedButtonEdgePcbGrip();
	afx_msg void OnBnClickedButtonEdgePcbUngrip();
	afx_msg void OnBnClickedButtonMotorZWait();
	afx_msg void OnBnClickedButtonZMotorUpBonding();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonMotorDefectInspZ();
	afx_msg void OnBnClickedButtonMotorAlignZ();
	afx_msg void OnBnClickedButtonMotorSupplyZ();
	afx_msg void OnBnClickedButtonBacklightOutPre();
	afx_msg void OnBnClickedButtonOpticalInsp();
	afx_msg void OnBnClickedButtonPcbGripFor();
	afx_msg void OnBnClickedButtonPcbGripBack();
	afx_msg void OnBnClickedButtonComAlignTest();
	afx_msg void OnBnClickedButtonMotorComAlign();
	afx_msg void OnBnClickedButtonMotorComAlignZ();


    afx_msg void OnBnClickedButtonMotor2800kInsp();
    afx_msg void OnBnClickedButtonMotor2800kInspZ();
	afx_msg void OnBnClickedButtonMotorZDarkInsp();
	afx_msg void OnBnClickedButtonContactUp();
	afx_msg void OnBnClickedButtonMotorPcbLoading();
	afx_msg void OnBnClickedButtonMotorCoverLoading();
	afx_msg void OnBnClickedButtonMotorZPcbLoading();
	afx_msg void OnBnClickedButtonMotorZCoverLoading();
	afx_msg void OnBnClickedButtonContactDown();
	afx_msg void OnBnClickedButtonMotorCoverUnloading();
	afx_msg void OnBnClickedButtonMotorZCoverUnloading();
	afx_msg void OnBnClickedButtonUvCylinderUp();
	afx_msg void OnBnClickedButtonUvCylinderDown();
	CExButton m_btnInspXWaitPos;
	CExButton m_btnInspXAlignPos;
	CExButton m_btnInspXDefectPos;
	CExButton m_btnInspXDarkPos;
	afx_msg void OnBnClickedButtonInspMotorWait();
	afx_msg void OnBnClickedButtonInspMotorAlign();
	afx_msg void OnBnClickedButtonInspMotorDefectInsp();
	afx_msg void OnBnClickedButtonInspMotorDarkInsp();
};
