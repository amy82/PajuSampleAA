#pragma once
class CPcbProcess1
{
public:
	CPcbProcess1(void);
	~CPcbProcess1(void);

public:
	void putListLog(CString strLog);

public:
	int Ready_process(int iStep);
	//Common AA
	//
	//
	int RunProc_ProductLoading(int iUseStep);		//! 작업자 제품 투입 자동 Step		(10000 ~ 10999)
	int RunProc_PCBOutsideAlign(int iUseStep);		//! PCB 외부 Align Step				(11000 ~ 14999)		//!! MIU_Initialize -> PCB Holder Align 위치
	int RunProc_SensorAlign(int iUseStep);		//! Sensor Align	(16600 ~ 16999)
	int RunProc_LaserMeasure(int iUseStep);			//! 내부/외부 Laser 측정 Step		(17000 ~ 17999)		//내부 변위 측정 -> 외부 변위측정 -> Sensor Align -> Hold Align
	int RunProc_EpoxyNewResing(int iUseStep);			//! Epoxy 동작 및 도포 검사 Step	(17000 ~ 17999)		//!! Hole 도포,
	int RunProc_InspAAPos(int iUseStep);  //! Defect 검사후 본딩위치 Step	(18000 ~ 19999)
	int RunProc_Bonding_Pos_GO(int iUseStep);
	int	procAutoFocus(int iStep);					/* AutoFocus */
	int	UV_process(int iStep);						/* UV 경화 */
	int	func_MandoFinalSFR(int iStep);				/* 최종 검사 */ //=> 처리 후,10000번지 처음 부터 재 동작
	//---------------------------------------------------------------------------------------------------------------------
	//
	//pcb AA
	//
	int RunProc_LensNewPassPickup(int iUseStep);		//! Lens Pickup에 제품 넘김 Step	(15000 ~ 16599)
	//
	//---------------------------------------------------------------------------------------------------------------------
	//
	//Lens AA
	//
	int RunProc_LensAlign(int iUseStep);			//! Pcb Lens Align	(16600 ~ 16999)
	int RunProc_LensLoading(int iUseStep);
	//
	//
	//
	//---------------------------------------------------------------------------------------------------------------------
	//
	// 완제품 검사 모드
	//
	//
	int	procProductComplete(int iStep);				//! 완제품 검사 모드
	int	Complete_FinalInsp(int iStep);
	//
	//---------------------------------------------------------------------------------------------------------------------
	//
	//
	//Lens Thread
	//
	int RunProc_LENS_AlignLaserMeasure(int iLensStep); //! Lens Thread Control (30000 ~ 39999)


};

