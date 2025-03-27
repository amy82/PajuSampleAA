#pragma once

//! 대겸에서 제작한 조명 컨트롤러의 원격 제어용 클래스

//! RS-232C 통신 클래스를 가져온다. (부모 클래스)
//! 부모 클래스의 함수, public 멤버 변수를 바로 사용 가능
#include "../../Library/RS232C/Handler_RS232C.h"

class CUVControl : public CHandler_RS232C
{
public:
	CUVControl(void);
	~CUVControl(void);

private:
	int m_iNo_Machine;	//! 조명 컨트롤러 장치의 구분 번호, 0 based
	
	TCHAR m_acRecvStorage[16384];
	int m_iRecvSize;
	void OutputRecvData(void *pProcPtr, TCHAR *pcBuff, int iDataSize, int iCnt_Recv);

	int SendData_Light_Controller(BYTE *pbySend, int iSendSize);

	//! Channel On/Off
	//! [주의 사항] 'iNoChannel' 값은 조명 컨트롤러의 실제 채널 입력값이다. 
	int SetChannel_OnOff(int iNoChannel, bool bSwitch_On);

	//! 각 Channel의 밝기값(PWM값) 조절
	//! [주의 사항] 'iNoChannel' 값은 조명 컨트롤러의 실제 채널 입력값이다. 
	int SetChannel_Value(int iNoChannel, int iValue);

	int DPS_SetChannel_Value(int iNoChannel, int iValue);

	bool DPS_Light_OnOffLevel(int channel, int onoff, int data);

	int DPS_SetChannel_Value2(int iNoChannel, int iValue);

	bool DPS_Light_OnOffLevel2(int channel, int onoff, int data);

protected:
	//! 부모 클래스의 가상 함수들을 구체적인 기능을 구현한다. 

	//! RS-232C 통신이 연결된 후에 맨 처음 1번 만 실행해야 할 기능을 구현하다. 
	virtual void ReadyDevice();
	//! 수신 처리 본체 함수
	virtual void ProcessReceiveData(void *pProcPtr, BYTE *pbyBuff, int iSize, bool bFlag_Active, int iCnt_Recv);
	//! 수신 처리 후 후처리 함수
	virtual void PostProcRecvData();

public:
	//! 조명 컨트롤러에 연결
	//! [주의 사항] 수신 데이터가 있을 경우에는, 반드시, SetReceiveProcPtr 함수로 수신 처리를 할 Dialog나 GUI 클래스를 설정하고, 이 함수를 호출한다. 
	bool Connect_Device(CString sPort, int iNoMachine = 0);
	//! 연결 해제
	void Close_Device();

	//! 문자열 직접 전송
	int SendData_Light_Controller(CString sSend);	

	//! 각 위치에서의 조명값 개별 설정
	//! 0 : Lens, 1 : PCB, 2 : Resin, 3 : 광축, 4 : MTF, 5 : 이물검사
	//! 역할 별로 조명값 구분, Demo 버전에서의 Model 정보와의 호환을 위해 추가
	//! [주의 사항] 'iChannel'값은 실제 조명 컨트롤러의 채널이 아니다. 
	void ctrlLedVolume(int iChannel, int iValue);
	void SideChartctrlLedVolume(int iChannel, int iValue);
	bool allControl(int iChannel , bool onOff);


	bool Altis_UV_Connect(int data);
	bool Altis_UC_Controller_OnOff(int channel, int onoff);
public:
};

