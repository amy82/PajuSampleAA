
#pragma once
#include "StdAfx.h"

#include "MMCWHP201.h"

#define	ABS	1
#define REL	0


#define IN_POSITION_VAL		100

class CMotorSet
{
public:
	CMotorSet();
	~CMotorSet();	
	// Construction
	char	motorMSG[256];


	bool m_bOrgFlag[MAX_MOTOR_NO];


	bool MMC_Init(char *msg);
	void MMC_Axisconfig();
	void MMC_Close();

	bool AmpEnable(int axis);
	bool AmpDisable(int axis);
	bool AmpEnableAll();
	bool AmpDisableAll();

	bool AmpFaultReset(int axis);
	bool AmpFaultResetAll();

	int	AmpFaultCheck();


	bool GetAmpFault(int axis);
	bool GetInposition(int axis);
	bool GetHomeSensor(int axis);
	bool GetNegaSensor(int axis);
	bool GetPosiSensor(int axis);
	int	 GetAxisStatus(int axis);

	int	 GetInputIO(int no);
	bool SetOutputIO(int no);
	bool GetOutputIO(long& no);
	bool SetOutputBit(int no);
	bool ResetOutputBit(int no);

	double GetCurrentPos(int axis);

	bool StopAxis(int axis);
	bool StopAxisAll();


	BOOL JogMove(int axis, double dVel);
	BOOL JogStop(int axis);	bool MoveAxis(int axis, bool AbSFlag, double dPos, double dVel, int iAcc);

	bool CheckHomedirection(int axis);	// HomeDir  false -> -방향으로 홈밍  true -> +방향으로 홈밍
	bool HomeProcess(int axis, bool HomeDir);
	bool HomeProcessPCBTH(int axis);	
	bool HomeProcessMTF(int axis);	
	bool HomeProcessAll();
	int HomeCheck();

	bool goMotorPos (int no, short axis[MAX_MOTOR_NO], double pos[MAX_MOTOR_NO]);

	bool ClearAxis(int axis);


	bool Lens_Motor_Move(int index, double offsetX=0, double offsetY=0, double offsetTh=0);
	bool Lens_Motor_Align_Move(double offsetX=0, double offsetY=0, double offsetTh=0);			/* Align Retry를 위해 추가 */

	bool Pcb_Motor_Move(int index, double offsetX=0, double offsetY=0, double offsetTh=0);
	bool Pcb_Motor_Align_Move(double offsetX=0, double offsetY=0, double offsetTh=0);			/* Align Retry를 위해 추가 */

	bool LENS_Z_Motor_Move(int index);

	bool Syringe_Motor_Move(int index);
	bool MTF_Motor_Move(int index);
};