#pragma once
#include <afxmt.h>


class CFlowProcess : public CWnd
{
	DECLARE_DYNAMIC(CFlowProcess)

public:
	CFlowProcess();
	virtual ~CFlowProcess();

protected:
	DECLARE_MESSAGE_MAP()

public:
	double	dProcessTime;

	int RunProc_ProductLoading(int iUseStep);		//! 작업자 제품 투입 자동 Step(10000 ~ )
	int RunProc_PCBOutsideAlign(int iUseStep);		//! PCB 외부 Align Step
	int RunProc_EpoxyResing(int iUseStep);			//! Epoxy 동작 및 도포 검사 Step
	int	RunProc_LensOutSideAlign(int iUseStep);		//! Lens 외부 Align Step
	int RunProc_LaserMeasure(int iUseStep);			//! 내부/외부 Laser 측정 Step

	int RunProc_OisAf(int iUseStep);				//! OIS (50000 ~
	int RunProc_AutoFocus(int iUseStep);			//! Active Align 동작(60000 ~
	int RunProc_UV_Process(int iUseStep);

	int RunProc_FinalInsp(int iUseStep);			//! 검사 관련(이물, 광원)
	int RunPorc_emission(int iUseStep);				//! 완제품 배출 Step
};
