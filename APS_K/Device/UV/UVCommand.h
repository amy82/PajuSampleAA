#pragma once

//! 일본 HAMAMATSU 사의 UV Spot Light Source 장비인 LIGHTNINGCURE LC8 (L9566/L9588)장비의 RS-232C 통신 제어용 클래스
//!  (1.LC8 Instruction Manual_7.pdf 문서의 32, 33 페이지, 4.LC8_cnt Instruction Manual(English)_1.pdf 문서 참조)
//!  (매뉴얼의 내용에 따라 Command 문자열 생성/해석 작업도 맡는다.)
//! Made by LHW (2013/4/29)
//! 마지막 작업 날짜 : 2013/5/7

//! [주의 사항]
//!   UV Lamp는 RS-232C Command가 적절치 못할 경우, 'ERR' 문자열을 PC로 보낸다.

//! RS-232C 통신 클래스를 가져온다. (부모 클래스)
//! 부모 클래스의 함수, public 멤버 변수를 바로 사용 가능
#include "../../Library/RS232C/Handler_RS232C.h"

//! 장비에서의 STX, ETX 값이다. (매뉴얼의 'Delimiter' 문자를 이용한다.)
#define UV_STX	0x0D
#define UV_ETX	0x0D

const int iBufSize_Cure_Program = 9;
const int iBufSize_Step_In_Cure = 7;

//! Memory Cure Program 설정 정보 구조체
struct sreSetupInfo_UV_Program
{
	//int iNo_Program;			//! Program number (1 ~ 9)
	int iModel_Shutter;			//! Shutter mode (1 : mode 1, 2 : mode 2)

	int iUnit_Output_Intensity; //! Intensity Mode (Unit) (1 : %, 2 : W)
								
	double adIntensity[iBufSize_Step_In_Cure];		//! Output Intensity
	double adTime     [iBufSize_Step_In_Cure];		//! Shutter Time, 단위 sec

	sreSetupInfo_UV_Program()
	{
		InitInfo();
	}

	void InitInfo()
	{
		//iNo_Program = 0;
		iModel_Shutter = 1;
		iUnit_Output_Intensity = 1;

		int i = 0;
		for ( i = 0; i < iBufSize_Step_In_Cure; i++ )
		{
			adIntensity[i] = 0.;
			adTime[i] = 0.;
		}
	}

	//! 이상이 있으면 음수를 반환, 이상이 없으면 '1'을 반환
	int IsValid()
	{
		if ( (iModel_Shutter != 1) && (iModel_Shutter != 2) )
		{
			return -1;
		}
		if ( (iUnit_Output_Intensity != 1) && (iUnit_Output_Intensity != 2) )
		{
			return -2;
		}

		int iFailed = -1;
		int i = 0;
		for ( i = 0; i < iBufSize_Step_In_Cure; i++ )
		{
			if ( adIntensity[i] < 0. )
			{
				iFailed = i;
			}
			if ( adTime[i] < 0. )
			{
				iFailed = i;
			}
		}
		if ( iFailed >= 0 )
		{
			return (-100 - iFailed);
		}

		return 1;
	}
	
	sreSetupInfo_UV_Program& operator=(const sreSetupInfo_UV_Program &input)	//! 연산자 재정의
	{
		//iNo_Program            = input.iNo_Program;
		iModel_Shutter         = input.iModel_Shutter;
		iUnit_Output_Intensity = input.iUnit_Output_Intensity;

		int i = 0;
		for ( i = 0; i < iBufSize_Step_In_Cure; i++ )
		{
			adIntensity[i] = input.adIntensity[i];
			adTime[i]      = input.adTime[i];
		}

		return *this;
	}
};

const int iBufSize_INP_Bit = 16;

class CUVCommand : public CHandler_RS232C
{
public:
	CUVCommand(void);
	~CUVCommand(void);

	void ReadyDevice();

private:
	int m_iNo_Machine;	//! UV Lamp 장치의 구분 번호, 0 based

	bool m_bFlag_Ready;	//! UV Lamp가 기본적인 사용 준비를 마쳤으면 true로 설정
	bool m_bFlag_Stable;//! UV Lamp가 안정화되면 true로 설정
	
	TCHAR m_acRecvStorage[16384];
	int m_iRecvSize;
	void OutputRecvData(void *pProcPtr, TCHAR *pcBuff, int iDataSize, int iCnt_Recv);

	int SendData_UV_Controller(BYTE *pbySend, int iSendSize);	

	
	int	Check_Ready_UV();

protected:
	//! 부모 클래스의 가상 함수들을 구체적인 기능을 구현한다. 

	//! RS-232C 통신이 연결된 후에 맨 처음 1번 만 실행해야 할 기능을 구현하다. 
	//! 수신 처리 본체 함수
	virtual void ProcessReceiveData(void *pProcPtr, BYTE *pbyBuff, int iSize, bool bFlag_Active, int iCnt_Recv);
	//! 수신 처리 후 후처리 함수
	virtual void PostProcRecvData();

public:
	int m_iMode_Control;	//! UV Lamp 장치의 현재 제어 방식
							//! 0 : Front Panel 방식, 1 : PC에서의 RS-232C 통신 제어

	int m_iMode_Program;	//! UV Lamp 장치의 현재 Program Mode
							//! 1 : 1 Step. 7 : 7 Step

	double m_dOutputIntensity;		//! UV Lamp 장치의 Output Intensity

	int m_iUnit_Output_Intensity;	//! UV Lamp 장치의 Output Intensity의 단위
									//! 1 : %, 2 : W

	//! 현재 UV Lamp 장치에 설정된 Cure Program 설정 정보 구조체
	sreSetupInfo_UV_Program m_astrCureInfo[iBufSize_Cure_Program];

	//! UV Lamp 장치에 설정할 Cure Program 설정 정보 구조체
	sreSetupInfo_UV_Program m_astrTemp_CureInfo[iBufSize_Cure_Program];

	//! "INP" Command에 대한 응답에서 각 Bit별 처리 관련 Flag 버퍼
	//! "INP" Command가 수신될 때마다 같은 작업이 반복되는 것을 막기 위해 추가하다.
	int m_aiBuf_INP_Bit[iBufSize_INP_Bit];

public:
	bool Altis_UV_Connect(int data);
	bool Altis_UC_Controller_OnOff(int channel, int onoff, int data);
	//! UV 장치에 연결
	//! [주의 사항] 반드시, SetReceiveProcPtr 함수로 수신 처리를 할 Dialog나 GUI 클래스를 설정하고, 이 함수를 호출한다. 
	bool Connect_Device(int sPort);
	//! 연결 해제
	void Close_Device();

	//! 문자열 직접 전송
	int SendData_UV_Controller(CString sSend);

	//! UV Lamp가 기본적인 동작 준비를 마치면 true를 반환
	bool IsReady();
	//! UV Lamp가 안정화되면 true를 반환
	bool IsStable_UV_Lamp();

	//! 아래 함수들을 이해하지 위해서, '4.LC8_cnt Instruction Manual(English)_1.pdf' 문서를 참조 바람

	void Set_Flag_UV_Lamp_Stable();		//! UV Lamp가 안정화되었을 때만 호출한다. 
										//! [주의 사항] 이 함수를 직접 호출하면 안된다. 수신 문자열 처리에서만 호출한다. 

	//! 아래의 함수에서 'Ask~' 함수는 UV 장치에 현재 설정 정보를 요청하는 함수임
	//! 'CAABonderDlg::Parse_From_UV_Lamp' 함수에서 수신 문자열 처리를 한다. 	

	//! 'CNT' 관련
	int Set_Control_Mode_Front_Panel();	//! Front Panel 제어로 설정
	int Set_Control_Mode_RS232C();		//! RS-232C 통신 제어로 설정
	int Ask_Control_Mode();				//! 현재 제어 방식을 묻는다. 

	//! 'PROG' 관련
	int Set_Program_Mode_1_Step();		//! AT~, INT~ 설정 이용
	int Set_Program_Mode_7_Steps();		//! Memory cure program 사용 모드
	int Ask_Program_Mode();				//! 현재 설정값을 묻는다. (PROG? Command)

	//! Shutter와 Diapgragm은 비슷한 역할을 한다. 하지만, Shutter는 크게 움직이는 용도이고, Diapgragm은 미세 조정용이다.
	int UV_Shutter_PowerSet(int value);
	//! 수동 조작
	int UV_Lamp_On();
	int UV_Lamp_Off();
	int UV_Shutter_Open();
	int UV_Shutter_Close();

	//! AT~' 관련 (1) (1 Step에서만 사용 가능)
	int Set_Shutter_AutoTime_1_Step(double fi_dTime);
	int Ask_Shutter_AutoTime_1_Step(double *fo_pdTime);

	//! AT~' 관련 (2) (1 Step에서만 사용 가능)
	int Start_Shutter_Auto_Operation_1_Step();
	int Ask_RemainTime_Shutter_Auto_Operation_1_Step(double *fo_pdTime);

	//! 'INT' 관련 (1) (1 Step, 7 Step 모두 사용 가능)
	int Set_Diaphragm_Stop();
	int Set_Diaphragm_Up();
	int Set_Diaphragm_Down();
	int Set_Diaphragm_Up_1_Point();
	int Set_Diaphragm_Down_1_Point();

	//! 'INT' 관련 (2) (1 Step에서만 사용 가능)
	int Set_Output_Intensity_1_Step(double fi_dInput);

	//! 'INT' 관련 (3) (1 Step, 7 Step 모두 사용 가능)
	bool m_bFlag_Request_INP;	//! 중복 처리 방지용 멤버 변수, 수신 처리 후에 Ask_Output_Intensity 함수 호출 
	int Ask_Output_Intensity();

	//! 'LIF, LAMP~' 관련
	int Reset_UV_Lamp_Operation_Time();
	int Ask_UV_Lamp_Operation_time();

	//! 'CURE~' 관련 (7 Step에서만 사용 가능)
	//! Memory cure program 제어용 함수
	//! '4.LC8_cnt Instruction Manual(English)_1.pdf' 문서의 'Main Window' 화면 설명을 읽어보면,
	//! 아래 함수의 용도를 쉽게 알 수 있다.
	int Set_Cure_Program_Info_7_Steps(int fi_iNoProgram, sreSetupInfo_UV_Program *fi_pstrInput);
	int Ask_Cure_Program_Info_7_Steps(int fi_iNoProgram);
	int Start_Cure_Program_7_Steps(int fi_iNoProgram);
	int Stop_Cure_Program_7_Steps();
	int Ask_Cure_Program_Progress_7_Steps();
	
	//! 'INP' 관련 Flag 버퍼 초기화
	void Init_Buffer_Input_Pin();
	//! 'INP' Command를 UV 장치에 보내어 현재의 다양한 설정 정보를 알아낸다. 
	int  Ask_Input_Pin();

	CString GetExplanationNG(CString sNumberNG);
};

