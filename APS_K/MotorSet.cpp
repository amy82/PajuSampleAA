#include "StdAfx.h"
#include "MotorSet.h"
#include "AA Bonder.h"
#include "AA BonderDlg.h"

#include "DataHandler.h"
#include "DioControl.h"

#include "Driver.h"

#include "MIU/Miu.h"

extern		MIU_DEVICE			gMIUDevice;
extern		CMIU				MIU;




extern CSystemData	sysData;
extern CModelData	model;
extern CTask		Task;
extern CDioControl	Dio;
extern CWork		work;

/* 모터 배열
 현재 모터 
	8축										4축
	0	 Lens X  ->Motor_Lens_X				8	 PCB X	 ->Motor_PCB_X
	1	 Lens Y  ->Motor_Lens_Y				9	 PCB Y	 ->Motor_PCB_Y
	2	 Lens Z  ->Motor_Lens_Z				10	 PCB Θ  ->Motor_PCB_TH
	3	 Lens Θ->Motor_Lens_TH				11	 Syringe ->Motor_Syringe		
	4	 Lens Tx ->Motor_Lens_Xt	
	5	 Lens Ty ->Motor_Lens_Xy
	6	 MTF	 ->Motor_MTF			
	7	 Spare   ->Motor_Spare			
*/


CMotorSet::CMotorSet()
{
}
CMotorSet::~CMotorSet()
{
}

bool CMotorSet::MMC_Init(char *msg)
{
	msg[0] = 0;
	for(int i=0; i<MAX_MOTOR_NO; i++)		m_bOrgFlag[i] = false;	

	short err = 0;
	long addr = 0xD8000000;

#ifdef	ON_LINE_MOTOR
	#ifdef		ON_LINE_MOTOR_TEST
		err = mmc_initx(1, &addr);								// 모션 보드 초기화..
	//	err = get_dpram_addr(0, &addr);						// 해당 모터의 Address 설정이 맞지 않은 경우 강제 설정..

		short ver;
		version_chk(0, &ver);
	#else
		err = mmc_initx(2, &addr);								// 모션 보드 초기화.. 
	#endif
#endif

	if(err==MMC_TIMEOUT_ERR)
		err = set_dpram_addr(0, addr);					// 해당 모터의 Address 설정이 맞지 않은 경우 강제 설정..

	if(err)
	{
		error_message(err, msg);

		char logStr[1000];
		sprintf_s(logStr, "모터 초기화에 실패 하였습니다. 2[%s]", msg, 999);
		errLogSave(logStr);
		return false;
	}

	AmpDisableAll();
	MMC_Axisconfig();

	SetOutputIO(0);

	return true;
}
void CMotorSet::MMC_Axisconfig() 
{
	short tmp = 0;
#ifdef	ON_LINE_MOTOR_TEST
	int motorCnt = mmc_all_axes();
	io_interrupt_enable(0, FALSE);								// Test 장비는 인터럽트 신호 연결 안 됨..
#else
	io_interrupt_enable(0, FALSE);								// 모션 보드의 0번 Bit를 ON 시켜야 보드 동작.. 
	io_interrupt_enable(1, FALSE);								// 비상 스위치 연결 후 True로 해서 동작 확인 할 것
#endif

// 0번 축
	for(int i=0;i<MAX_MOTOR_NO; i++)
	{
		fset_micro_stepper(i);									// 모터 축을 Servo를 제어하는 축으로 지정..
		fset_closed_loop(i, FALSE);								// 해당 축을 closed_loop [1], open_loop [0]로 설정한다.
		fset_step_mode(i, TRUE);								// 해당 축을 tow-pulse [0]로 할 것인지, sign+pulse로 할 것인지 지정..	

		fset_positive_level(i, HIGH);							// 센서가 감지 되었을 때 발생될 Event를 지정..
		fset_negative_level(i, HIGH);							// [HIGH] : Stop, [LOW] : No-Event..
		fset_inposition_required(i, TRUE);


		if(/*(i == Motor_Lens_TH) || */(i == Motor_Lens_Yt) )
			fset_inposition_level(i, HIGH);
		else
			fset_inposition_level(i, LOW);

		fset_positive_limit(i, STOP_EVENT);
		fset_negative_limit(i, STOP_EVENT);
		fset_home(i, NO_EVENT);
		fset_electric_gear(i, 1.0);								// 감속기의 비율.. default는 1.0..

		fset_e_stop_rate(i, (short)(sysData.iMotorAccTime[i]));
		fset_stop_rate(i, (short)(sysData.iMotorAccTime[i]));

		fset_in_position(i, 5);
		fio_interrupt_on_stop(i, TRUE);
		fset_amp_fault(i, ABORT_EVENT);							// Amp Dault가 뜨면 드라이브가 Disable 상태가 되므로, abort 로 명령만 취소..
		fset_home_level(i, LOW);

		if(Motor_Lens_X == i)
		{
			fset_coordinate_direction(i, CORD_CW);					// 모터의 회전 방향을 설정.. 시계 방향이 (+).. CW 모드로..
			fset_encoder_direction(i, CORD_CCW);
		}
		else if(Motor_Lens_Y == i)
		{
			fset_coordinate_direction(i, CORD_CCW);					// 모터의 회전 방향을 설정.. 시계 방향이 (+).. CW 모드로..
			fset_encoder_direction(i, CORD_CCW);
		}
		else if(Motor_Lens_Z == i)
		{
			fset_coordinate_direction(i, CORD_CW);					// 모터의 회전 방향을 설정.. 시계 방향이 (+).. CW 모드로..
			fset_encoder_direction(i, CORD_CW);
		}
		else if(Motor_PCB_TH == i)
		{
			fset_coordinate_direction(i, CORD_CW);					// 모터의 회전 방향을 설정.. 시계 방향이 (+).. CW 모드로..
			fset_encoder_direction(i, CORD_CCW);
		}
		else if(Motor_Lens_Xt == i)
		{
			fset_coordinate_direction(i, CORD_CCW);					// 모터의 회전 방향을 설정.. 시계 방향이 (+).. CW 모드로..
			fset_encoder_direction(i, CORD_CCW);
		}
		else if(Motor_Lens_Yt == i)
		{
			fset_coordinate_direction(i, CORD_CCW);					// 모터의 회전 방향을 설정.. 시계 방향이 (+).. CW 모드로..
			fset_encoder_direction(i, CORD_CCW);
		}
		else if(Motor_PCB_X == i)
		{
			fset_coordinate_direction(i, CORD_CCW);					// 모터의 회전 방향을 설정.. 시계 방향이 (+).. CW 모드로..
			fset_encoder_direction(i, CORD_CCW);
		}
		else if(Motor_PCB_Y == i)
		{
			fset_coordinate_direction(i, CORD_CCW);					// 모터의 회전 방향을 설정.. 시계 방향이 (+).. CW 모드로..
			fset_encoder_direction(i, CORD_CCW);
		}
		else if(Motor_PCB_TH == i)
		{
			fset_coordinate_direction(i, CORD_CW);					// 모터의 회전 방향을 설정.. 시계 방향이 (+).. CW 모드로..
			fset_encoder_direction(i, CORD_CCW);
		}
		else
		{
			fset_coordinate_direction(i, CORD_CW);					// 모터의 회전 방향을 설정.. 시계 방향이 (+).. CW 모드로..
			fset_encoder_direction(i, CORD_CCW);
		}
	}
}
void CMotorSet::MMC_Close()
{
#ifdef ON_LINE_MOTOR

	int i=0;

	for(i=0; i<MAX_MOTOR_NO; i++)
	{
		set_stop(i);
		clear_status(i);
	}
	SetOutputIO(0);

#endif
}


bool CMotorSet::AmpDisable(int axis)
{
	m_bOrgFlag[axis] = false;

#ifdef ON_LINE_MOTOR
	int m_MMC_Err = set_amp_enable(axis, FALSE);

	if (m_MMC_Err != MMC_OK)
		return FALSE;
#endif

	return TRUE;
}
bool CMotorSet::AmpDisableAll()
{
	bool rtnVal = true;

	for(int i=0; i<MAX_MOTOR_NO; i++)
	{
		m_bOrgFlag[i] = false;

#ifdef ON_LINE_MOTOR
		int m_MMC_Err = set_amp_enable(i, FALSE);

		if (m_MMC_Err != MMC_OK)
			rtnVal = FALSE;
#endif
	}

		if(!rtnVal)
	{
		char dispStr[100];
		sprintf_s(dispStr, "AmpDisableAll 실패.");
		errLogSave(dispStr);
	}

	return rtnVal;
}
bool CMotorSet::AmpEnable(int axis)
{
	bool rtnVal = true;

	m_bOrgFlag[axis] = false;

#ifdef ON_LINE_MOTOR
	clear_status(axis);
	int m_MMC_Err; 
	short flag =0;
	m_MMC_Err = get_amp_enable(axis,&flag);	

	if (m_MMC_Err != MMC_OK)
		rtnVal = FALSE;
	if(flag)
		return true;

	Sleep(500);

	m_MMC_Err = set_amp_enable(axis, TRUE);

	Sleep(10);
	if (m_MMC_Err != MMC_OK)
		rtnVal = FALSE;
#endif

	return rtnVal;
}
bool CMotorSet::AmpEnableAll()
{
	int m_MMC_Err = MMC_OK;
	bool rtnVal = true;
	for(int i=0; i<MAX_MOTOR_NO; i++)
	{
		clear_status(i);

		m_bOrgFlag[i] = false;

#ifdef ON_LINE_MOTOR
		m_MMC_Err = set_amp_enable(i, FALSE);
#endif

		if (m_MMC_Err != MMC_OK)
			rtnVal = false;
	}

	Sleep(100);

	for(int i=0; i<MAX_MOTOR_NO; i++)
	{
#ifdef ON_LINE_MOTOR
		m_MMC_Err = set_amp_enable(i, TRUE);
#endif

		if (m_MMC_Err != MMC_OK)
			rtnVal = false;
	}


	if(!rtnVal)
	{
		char dispStr[100];
		sprintf_s(dispStr, "AmpEnableAll 실패.");
		errLogSave(dispStr);
	}

	return rtnVal;
}


bool CMotorSet::AmpFaultReset(int axis)
{
	clear_status(axis);

	if(amp_fault_switch(axis))
	{
		m_bOrgFlag[axis] = false;

		amp_fault_reset(axis);								// AMP Fault를 clear..
		Sleep(500);
		amp_fault_set(axis);								// AMP Port Enable..
	}

	return true;
}

bool CMotorSet::AmpFaultResetAll()
{
	bool rtnFlag = true;

	for(int i=0; i<MAX_MOTOR_NO; i++)
	{
		clear_status(i);

		if(amp_fault_switch(i))
		{
			m_bOrgFlag[i] = false;

			amp_fault_reset(i);								// AMP Fault를 clear..
		}
	}

	Sleep(1000);

	for(int i=0; i<MAX_MOTOR_NO; i++)
	{
		amp_fault_set(i);								// AMP Port Enable..
	}

	Sleep(100);

	for(int i=0; i<MAX_MOTOR_NO; i++)
	{
// 		if(i == Motor_Spare) 
// 			continue;

		if(amp_fault_switch(i))
		{
			rtnFlag = false;
			break;
		}
	}

	if(!rtnFlag)
	{
		char dispStr[100];
		sprintf_s(dispStr, "AmpFaultResetAll 실패.");
		errLogSave(dispStr);
	}


	return rtnFlag;
}

int	CMotorSet::AmpFaultCheck()
{
	int iAmpFaultFlag = 0;
	for(int i=0; i<MAX_MOTOR_NO; i++)
	{
// 		if(i==Motor_Spare || i==Motor_MTF)
// 			continue;
		if(amp_fault_switch(i))
		{
			iAmpFaultFlag += 0x01<<i;
			m_bOrgFlag[i] = false;
		}
	}

	Task.iAmpFaultFlag = iAmpFaultFlag;
	return iAmpFaultFlag;
}

int CMotorSet::GetAxisStatus(int axis)
{
	int ret = 0;
#ifdef ON_LINE_MOTOR
	ret = axis_source(axis);
#endif

	return ret;
}
bool CMotorSet::GetInposition(int axis)
{
#ifdef ON_LINE_MOTOR
	int ret = axis_done(axis);								// 이동이 끝나고, In-position 상태이면 true..
	if(!ret)
	{
		error_message(ret, motorMSG);
		return false;
	}
#endif
	return true;
}
bool CMotorSet::GetHomeSensor(int axis)
{
#ifdef ON_LINE_MOTOR
	int ret = home_switch(axis);
	return ret ? true : false;
#endif
	return true;
}
bool CMotorSet::GetPosiSensor(int axis)
{
#ifdef ON_LINE_MOTOR
	int ret = pos_switch(axis);
	return ret ? true : false;
#endif

	return false;
}
bool CMotorSet::GetNegaSensor(int axis)
{
#ifdef ON_LINE_MOTOR
	int ret = neg_switch(axis);
	return ret ? true : false;
#endif

	return false;
}
bool CMotorSet::GetAmpFault(int axis)
{
	int tmp = amp_fault_switch(axis);
	if(tmp)
	{
		m_bOrgFlag[axis] = false;
		return false;
	}

	return true;
}


int CMotorSet::GetInputIO(int no)
{
	long val = 0x00;

#ifdef ON_LINE_MOTOR
	set_io(0, val);
#endif

	val = val & 0xffff;

	return val;
}
bool CMotorSet::SetOutputIO(int no)
{
	int ret = 0;
#ifdef ON_LINE_MOTOR
	ret = set_io(0, (~no)&0xFFFFFFFF);
#endif

	if(ret)
		return false;

	return true;
}
bool CMotorSet::GetOutputIO(long& val)
{
	val = 0;
#ifdef ON_LINE_MOTOR
	get_out_io(0, &val);
#endif

	val = val & 0xffff;

	return true;
}
bool CMotorSet::SetOutputBit(int no)
{
	int ret = 0;
#ifdef ON_LINE_MOTOR
	ret = set_bit(no);
#endif

	if(ret)	return false;

	return true;
}


bool CMotorSet::ResetOutputBit(int no)
{
	int ret = 0;
#ifdef ON_LINE_MOTOR
	ret = reset_bit(no);
#endif

	if(ret)	return false;

	return true;
}


double CMotorSet::GetCurrentPos(int axis)
{
	double pos = 0;

#ifdef ON_LINE_MOTOR
	get_command(axis, &pos);
//	get_position(axis, &pos);
#endif

	pos /= sysData.fMotorResol[axis];

	return (float)pos;
}

bool CMotorSet::StopAxis(int axis)
{
#ifdef ON_LINE_MOTOR
	frames_clear(axis);
	v_move_stop(axis);
	set_stop(axis);

// 	clock_t start_t = clock();
// 	clock_t end_t;

	int ep = myTimer(true);
	
	while(!axis_done(axis))
	{
		DoEvents();

//		end_t = clock();
//		double t_duration = (double)(end_t - start_t) *1000 / (CLOCKS_PER_SEC);

//		if(t_duration>1000)
		if(myTimer(true)-ep>1000)
		{
			clear_status(axis);

			char temp[200];
			wsprintf(temp,"[%s] 모터 정지 시간 초과.", MotorName[axis]);
			errLogSave(temp);

			return false;
		}
		Sleep(10);
	}

	clear_status(axis);

#endif

	return true;
}
bool CMotorSet::StopAxisAll()
{
	int i;
	bool runFlag[MAX_MOTOR_NO] = {1, };

// 	clock_t start_t = clock();
// 	clock_t end_t;
	int ep = myTimer(true);

#ifdef ON_LINE_MOTOR
	for(i=0; i<MAX_MOTOR_NO; i++)
	{
		frames_clear(i);
		v_move_stop(i);
		set_stop(i);
	}

#endif

	while(1)
	{
// 		end_t = clock();
// 		double t_duration = (double)(end_t - start_t) *MOTOR_STOP_TIME / (CLOCKS_PER_SEC);

//		if(t_duration>1000)
		if(myTimer(true)-ep>1000)
		{
			errLogSave("전체 모터 정지 시간 초과. [1 sec]");
			return false;
		}


//		wait_for_all(MAX_MOTOR_NO, axis);

		for(i=0; i<MAX_MOTOR_NO; i++)
		{
			if (runFlag[i])
			{

#ifdef ON_LINE_MOTOR
				if(!axis_done(i))
#endif
				{
					runFlag[i] = 0;
					break;
				}
			}
		}

		if(i==MAX_MOTOR_NO)
			break;

		DoEvents();

		Sleep(10);
	}

#ifdef ON_LINE_MOTOR
	for(i=0; i<MAX_MOTOR_NO; i++)
		clear_status(i);

#endif

	return true;
}


//////////////////////////////////////////////////////////////////////////
//		homming 방향이 축 마다 다 틀려서 선택해서 사용 하도록 설정
//			축번호					(+)방향					(-)방향							
//		0번 Lens X(-) 											o						  
//		1번 Lens Y(+) 				    o			
//		2번 Lens Z(+)				    o
//		3번 Lens th(-)											o
//		4번 Lens xt(-)											o
//		5번 Lens yt(-)											o
//		6번 MTF(+)						o
//		7번 spare				///////////////////////////////////
//		8번 PCB X(+)						o
//		9번 PCB Y(-)												o
//		10번 PCB Th(-)											o
//		11번 syringe	(+)					o
//
///////////////////////////////////////////////////////////////////////////

bool CMotorSet::CheckHomedirection(int axis)	// HomeDir  false -> -방향으로 홈밍  true -> +방향으로 홈밍
{
	if(axis == Motor_Lens_X)
		return false;
	else if(axis == Motor_Lens_Y)
		return true;
	else if(axis == Motor_Lens_Z)
		return true;
// 	else if(axis == Motor_Lens_TH)
// 		return false;
	else if(axis == Motor_Lens_Xt)
		return false;
	else if(axis == Motor_Lens_Yt)
		return true;
	else if(axis == Motor_PCB_X)
		return true;
	else if(axis == Motor_PCB_Y)
		return false;
	else if(axis == Motor_PCB_TH)
		return false;
	else
		return false;			 // 기본 -방향
}

bool CMotorSet::HomeProcess(int axis, bool HomeDir)	// HomeDir  false -> -방향으로 홈밍  true -> +방향으로 홈밍
{
// 	if(axis == Motor_Spare )
// 		return false;

	double dPOS_Low = 1.5;		// homming 사용시 천천히 이동시 사용 위치  
	double dVel_Low = 1;		// homming 사용시 천천히 이동시 사용 속도
	int iAcc_Low = 10;			// homming 사용시 천천히 이동시 사용 가속시간

	int MotorAccTime;
	int MotorSpeed;		

	if(/*axis == Motor_Lens_TH || */axis == Motor_PCB_TH) 
		MotorSpeed = (int)(4 * sysData.fMotorResol[axis]);
	else if(axis == Motor_PCB_Y) 
		MotorSpeed = (int)(40 * sysData.fMotorResol[axis]);
	else
		MotorAccTime = sysData.iMotorAccTime[axis];
		MotorSpeed = (int)(10 * sysData.fMotorResol[axis]);	// home 속도는 고정으로 가지고 감...

	m_bOrgFlag[axis] = false;
	int step = 0;
	double eTime = 0;
	char temp[200];
	int	status;

	//	wsprintf(temp,"[%s] 모터 원점 복귀 중.", MotorName[axis]);
	//	delayMsg(temp,100000, M_COLOR_BLUE);

	int ep = myTimer(true);

	if(amp_fault_switch(axis))
	{
		errMsg("모터 알람 상태입니다. Reset 후 동작 하세요.");
		return false;
	}

//	AmpFaultReset(axis);
	AmpEnable(axis);

	frames_clear(axis);
	clear_status(axis);

	set_negative_limit(axis, STOP_EVENT);
	set_positive_limit(axis, STOP_EVENT);
	set_home(axis, NO_EVENT);
	Sleep(500);

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif

	bool iHomeErrorFlag;
	if(axis == Motor_PCB_TH)
	{
		iHomeErrorFlag = HomeProcessPCBTH(axis);
		if(!iHomeErrorFlag)
			return false;
	}
	else if(HomeDir)			//방향 +이동 해서 homming
	{
		while(1)
		{
			if(amp_fault_switch(axis))
			{
				StopAxis(axis);
				break;
			}


			status = GetAxisStatus(axis);
			switch(step)
			{
			case 0:
				v_move(axis, MotorSpeed, (short)(MotorAccTime));							
				if((axis_done(axis)) && (status & ST_POS_LIMIT))
				{
					Sleep(500);
					step = 100;
				}

				break;

			case 100:
				set_home(axis, STOP_EVENT);
				v_move(axis, -MotorSpeed/4, (short)(MotorAccTime));
				if(status & ST_HOME_SWITCH)
				{
					Sleep(500);
					set_home(axis, NO_EVENT);
					MoveAxis(axis, 0, dPOS_Low, dVel_Low, iAcc_Low);
					Sleep(500);
					step = 200;
				}
				break;

			case 200:
				if(axis_done(axis))
				{
					step = 300;
					set_home(axis, STOP_EVENT);
				}
				break;
			case 300:
				v_move(axis, (int)(-dVel_Low * sysData.fMotorResol[axis]), (short)(MotorAccTime));

				if(status & ST_HOME_SWITCH)
				{
					Sleep(500);
					set_home(axis, NO_EVENT);
					set_position(axis, 0);
					step = 400;
				}
				break;

			case 400:
				step =1000;
				break;

			default:
				break;
			}

			if(step==1000)
				break;

			eTime = myTimer(true);
			if(eTime-ep>MOTOR_ORIGIN_TIME)
			{
				StopAxis(axis);
				AmpDisable(axis);
				delayMsg(false);
				clear_status(axis);

				char temp[200];
				wsprintf(temp,"[%s] 모터 원점 복귀 시간 초과.", MotorName[axis]);
				errLogSave(temp);

				return false;
			}

			DoEvents();
			Sleep(10);

		}
	}
	else			// -방향으로 이동하면 homming 
	{
		while(1)
		{
			status = GetAxisStatus(axis);
			switch(step)
			{
			case 0:
				v_move(axis, -MotorSpeed, (short)(MotorAccTime));							
				if((axis_done(axis)) && (status & ST_NEG_LIMIT))
				{
					Sleep(500);
					step = 100;
				}

				break;

			case 100:
				set_home(axis, STOP_EVENT);
				v_move(axis, MotorSpeed/4, (short)(MotorAccTime));
				if(status & ST_HOME_SWITCH)
				{
					Sleep(500);
					set_home(axis, NO_EVENT);
					MoveAxis(axis, 0, -dPOS_Low, dVel_Low, iAcc_Low);
					Sleep(500);
					step = 200;
				}
				break;

			case 200:
				if(axis_done(axis))
				{
					set_home(axis, STOP_EVENT);
					step = 300;
				}
				break;
			case 300:
				v_move(axis, (int)(dVel_Low * sysData.fMotorResol[axis]), (short)(MotorAccTime));
				if(status & ST_HOME_SWITCH)
				{
					Sleep(500);
					set_home(axis, NO_EVENT);
					set_position(axis, 0);
					step = 400;
				}
				break;

			case 400:
				step =1000;
				break;

			default:
				break;
			}

			if(step==1000)
				break;

			eTime = myTimer(true);
			if(eTime>MOTOR_ORIGIN_TIME)
			{
				StopAxis(axis);
				AmpDisable(axis);
				delayMsg(false);
				clear_status(axis);

				char temp[200];
				wsprintf(temp,"[%s] 모터 원점 복귀 시간 초과.", MotorName[axis]);
				errLogSave(temp);

				return false;
			}

			DoEvents();
			Sleep(5);

		}
	}

	if(clear_status(axis))
	{
		delayMsg(false);

		clear_status(axis);

		char temp[200];
		wsprintf(temp,"[%s] 모터 초기화 실패.", MotorName[axis]);
		errLogSave(temp);

		return 0;
	}

	frames_clear(axis);

	// MTF, Lens z축, PCB th만 대기 위치로 이동...
	if( axis == Motor_Lens_Z  || axis == Motor_PCB_TH)
	{
		double vel[2], pos[2];
		short acc[2], axis2[2];
		axis2[0]  = short(axis);
		vel[0] = sysData.fMotorSpeed[axis] * sysData.fMotorResol[axis];
		acc[0] = (short)(sysData.iMotorAccTime[axis]);
		pos[0] = model.axis[axis].pos[Wait_Pos] * sysData.fMotorResol[axis];

		start_move_all(1, axis2, pos, vel, acc);
	}

	m_bOrgFlag[axis] = true;

	wsprintf(temp,"[%s] 모터 원점 복귀 완료", MotorName[axis]);
	delayMsg(temp, 500, M_COLOR_GREEN);

	return true;
}

bool CMotorSet::HomeProcessPCBTH(int axis)	
{
	int MotorAccTime = sysData.iMotorAccTime[axis];
	int MotorSpeed = (int)(5 * sysData.fMotorResol[axis]);	// home 속도는 고정으로 가지고 감...

	int cnt = 0;
	int step = 0;
	double eTime = 0;
	double dPOS_Low = 1.5;		// homming 사용시 천천히 이동시 사용 위치  
	double dVel_Low = 1.0;		// homming 사용시 천천히 이동시 사용 속도
	int iAcc_Low = 10;			// homming 사용시 천천히 이동시 사용 가속시간
	int	status;

	int ep = myTimer(true);

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif
	while(1)
	{
		if(amp_fault_switch(axis))
		{
			StopAxis(axis);
			break;
		}


		status = GetAxisStatus(axis);
		switch(step)
		{
		case 0:
			if(!(Dio.PCBCoverOnCheck(false,false)))
			{
				Dio.PCBCoverOn(false,false);
				cnt =0;
			}
			step = 100;
			break;

// 		case 20:
// 			if(cnt>50)
// 				step =30;
// 			else
// 				cnt++;
// 			break;
// 
// 		case 30:
// 			if((Dio.PCBCoverOnCheck(false,false)))
// 			{
// 				step = 50;
// 			}
// 			break;
// 
// 		case 50:
// 			if(!(Dio.PCBPushCheck(false,false)))
// 			{
// 				Dio.PCBPush(false,false);
// 				cnt =0;
// 			}
// 			step = 70;
// 			break;
// 
// 		case 70:
// 			if(cnt>50)
// 				step =80;
// 			else
// 				cnt++;
// 			break;
// 
// 		case 80:
// 			if(Dio.PCBPushCheck(false,false))
// 			{
// 				step = 100;
// 			}
// 			break;

		case 100:
			v_move(Motor_PCB_TH, -MotorSpeed, (short)(MotorAccTime));							
			if((axis_done(Motor_PCB_TH)) && (status & ST_NEG_LIMIT))
			{
				step = 150;
			}
			break;

		case 150:
			if(cnt> 50)	// sleep(10) *50 =500ms
			{
				cnt =0;
				step =200;
			}
			else
				cnt++;
			break;

		case 200:
			MoveAxis(Motor_PCB_TH, REL, dPOS_Low, dVel_Low, iAcc_Low);
			step = 300;
			break;

		case 300:
			if(axis_done(Motor_PCB_TH))
			{
				step = 350;
			}
			break;

		case 350:
			if(cnt> 50)	// sleep(10) *50 =500ms
			{
				cnt =0;
				step =400;
			}
			else
				cnt++;
			break;

		case 400:
			v_move(Motor_PCB_TH, (int)(-dPOS_Low * sysData.fMotorResol[Motor_PCB_TH]), (short)(iAcc_Low));
			if(status & ST_NEG_LIMIT)
			{
				set_position(Motor_PCB_TH, 0);
				step = 500;
			}
			break;

		case 500:
			step =1000;
			m_bOrgFlag[Motor_PCB_TH] =true;
			break;

		default:
			break;
		}


		if(step==1000)
			break;

		eTime = myTimer(true);
		if(eTime-ep>MOTOR_ORIGIN_TIME)
		{
			StopAxis(axis);
			AmpDisable(axis);
			delayMsg(false);
			clear_status(axis);

			char temp[200];
			wsprintf(temp,"[%s] 모터 원점 복귀 시간 초과.", MotorName[axis]);
			errLogSave(temp);

			return false;
		}

		DoEvents();
		Sleep(10);

	}
	return true;
}

bool CMotorSet::HomeProcessMTF(int axis)	
{
	int MotorAccTime = sysData.iMotorAccTime[axis];
	int MotorSpeed = (int)(5 * sysData.fMotorResol[axis]);	// home 속도는 고정으로 가지고 감...

	int cnt = 0;
	int step = 0;
	double eTime = 0;
	double dPOS_Low = 1.5;		// homming 사용시 천천히 이동시 사용 위치  
	double dVel_Low = 1.0;		// homming 사용시 천천히 이동시 사용 속도
	int iAcc_Low = 10;			// homming 사용시 천천히 이동시 사용 가속시간
	int	status;

	int ep = myTimer(true);

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif
	while(1)
	{
		if(amp_fault_switch(axis))
		{
			StopAxis(axis);
			break;
		}


		status = GetAxisStatus(axis);
		switch(step)
		{
		case 0:
			v_move(axis, MotorSpeed, (short)(MotorAccTime));							
			if((axis_done(axis)) && (status & ST_POS_LIMIT))
			{
				Sleep(500);
				step = 100;
			}

			break;

		case 100:
			set_home(axis, STOP_EVENT);
			v_move(axis, -MotorSpeed/4, (short)(MotorAccTime));
			if(status & ST_HOME_SWITCH)
			{
				Sleep(500);
				set_home(axis, NO_EVENT);
				Sleep(500);
				step = 150;
			}
			break;

		case 150:
// 			if(axis_done(Motor_MTF))
// 			{
 				step = 400;
// 			}
			break;

		case 400:
			step =1000;
			break;

		default:
			break;
		}


		if(step==1000)
			break;

		eTime = myTimer(true);
		if(eTime-ep>MOTOR_ORIGIN_TIME)
		{
			StopAxis(axis);
			AmpDisable(axis);
			delayMsg(false);
			clear_status(axis);

			char temp[200];
			wsprintf(temp,"[%s] 모터 원점 복귀 시간 초과.", MotorName[axis]);
			errLogSave(temp);

			return false;
		}

		DoEvents();
		Sleep(10);

	}
	return true;
}

bool CMotorSet::HomeProcessAll()
{
	char temp[200];
	int	status[MAX_MOTOR_NO];
	int MotorAccTime[MAX_MOTOR_NO];
	int MotorSpeed[MAX_MOTOR_NO];
	int step[MAX_MOTOR_NO];	
	int cnt[MAX_MOTOR_NO];

	double eTime = 0;
	double dPOS_Low = 1.5;		// homming 사용시 천천히 이동시 사용 위치  
	double dVel_Low = 1.0;		// homming 사용시 천천히 이동시 사용 속도
	int iAcc_Low = 10;			// homming 사용시 천천히 이동시 사용 가속시간

	bool Zaxis_flag[2];			// Motor_Lens_Z, Motor_Syringe 2개만 + 이동 하면 PCB_Z축 -센서 까지 이동.
	for(int i=0;i<2;i++)
		Zaxis_flag[i] = false;
	bool PCBYaxis_flag = false;			// Y축 -센서 이동 하면 (PCB th , PCB X ) 공압 및 홈밍 함


	// 원점 복귀 전 항상 close 동작

	MIU.Close();
	Dio.setAlarm(YELLOW_LAMP);

	for(int i=0;i<MAX_MOTOR_NO;i++)
	{
// 		if(i==Motor_Spare)
// 			continue;

		m_bOrgFlag[i] = FALSE;
		step[i] = 0;
		cnt[i] = 0;

		if(amp_fault_switch(i))
		{
			errMsg("모터 알람 상태입니다. Reset 후 동작 하세요.");
			return false;
		}

		AmpEnable(i);

		frames_clear(i);
		clear_status(i);

		set_negative_limit(i, STOP_EVENT);
		set_positive_limit(i, STOP_EVENT);
		set_home(i, NO_EVENT);



		MotorAccTime[i] = sysData.iMotorAccTime[i];
		if(/*i == Motor_Lens_TH || i == Motor_Lens_TH || i == Motor_Lens_TH || */i == Motor_Lens_Yt ) 
			MotorSpeed[i] = (int)(4 * sysData.fMotorResol[i]);
		else if(i == Motor_PCB_Y) 
			MotorSpeed[i] = (int)(40 * sysData.fMotorResol[i]);
		else
			MotorSpeed[i] = (int)(10 * sysData.fMotorResol[i]);	// home 속도는 고정으로 가지고 감...
	}

#ifndef	ON_LINE_MOTOR
	for(int i=0; i<MAX_MOTOR_NO;i++)
		step[i] = 1000;
#endif


	if(!Dio.BackLightOn(false,true))		// 백라이트 후진 확인 후 원점 복귀 시작.
	{
		char temp[200];
		wsprintf(temp,"Back Light 후진 실패. 확인 필요");
		errLogSave(temp);
		errMsg2(Task.AutoFlag, "Back Light 후진 실패. 확인 필요");
//		errMsg(temp);
		return false;
	}

	while(1)
	{
		for(int i=0;i<MAX_MOTOR_NO;i++)
			status[i] = GetAxisStatus(i);

		//Motor_Lens_Z(+)
		switch(step[Motor_Lens_Z])
		{
		case 0:
			v_move(Motor_Lens_Z, MotorSpeed[Motor_Lens_Z], (short)(MotorAccTime[Motor_Lens_Z]));							
			if((axis_done(Motor_Lens_Z)) && (status[Motor_Lens_Z] & ST_POS_LIMIT))
			{
				set_home(Motor_Lens_Z, STOP_EVENT);
				////////////////////////////////////////////////////////////////////////////////// 
				// LENS X 이동후 PCB X 이동후.... flag 살리고 homming 함
				v_move(Motor_Lens_X, -MotorSpeed[Motor_Lens_X], (short)(MotorAccTime[Motor_Lens_X]));	// Lens X축 모터 -이동후  PCB X축 이동
				step[Motor_Lens_Z] = 20;
			}
			break;

		case  20:
			if(cnt[Motor_Lens_Z] > 100)	// sleep(10) *50 =500ms
			{
				cnt[Motor_Lens_Z] =0;
				step[Motor_Lens_Z] =30;
			}
			else
				cnt[Motor_Lens_Z]++;
			break;

		case  30:
			if(axis_done(Motor_Lens_X) && (status[Motor_Lens_X] & ST_NEG_LIMIT))					// Lens X축 모터 이동.
			{
				v_move(Motor_PCB_X, -MotorSpeed[Motor_PCB_X], (short)(MotorAccTime[Motor_PCB_X]));	// PCB X축 모터 -이동후 Flag 살림
				step[Motor_Lens_Z] = 50;
			}
			break;

		case  50:
			if(cnt[Motor_Lens_Z]> 50)	// sleep(10) *50 =500ms
			{
				cnt[Motor_Lens_Z] =0;
				step[Motor_Lens_Z] =70;
			}
			else
				cnt[Motor_Lens_Z]++;
			break;


		case  70:
			if(axis_done(Motor_PCB_X) && (status[Motor_PCB_X] & ST_NEG_LIMIT))					// PCB X축 모터 이동 완료후 flag 살림.
			{
				Zaxis_flag[0] = true; 
				step[Motor_Lens_Z] = 80;
			}
			break;

		case  80:
			if(cnt[Motor_Lens_Z]> 50)	// sleep(10) *50 =500ms
			{
				cnt[Motor_Lens_Z] =0;
				step[Motor_Lens_Z] =100;
				Zaxis_flag[0] = true; 
			}
			else
				cnt[Motor_Lens_Z]++;
			break;

			//////////////////////////////////////////////////////////////////////////////////

		case 100:
			v_move(Motor_Lens_Z, -MotorSpeed[Motor_Lens_Z]/4, (short)(MotorAccTime[Motor_Lens_Z]));
			if(status[Motor_Lens_Z] & ST_HOME_SWITCH)
			{
				set_home(Motor_Lens_Z, NO_EVENT);
				step[Motor_Lens_Z] = 150;
			}
			break;

		case 150:
			if(cnt[Motor_Lens_Z]> 50)	// sleep(10) *50 =500ms
			{
				cnt[Motor_Lens_Z] =0;
				step[Motor_Lens_Z] =200;
			}
			else
				cnt[Motor_Lens_Z]++;
			break;

		case 200:
			if(axis_done(Motor_Lens_Z))
			{
				MoveAxis(Motor_Lens_Z, REL, dPOS_Low, dVel_Low, iAcc_Low);
				set_home(Motor_Lens_Z, STOP_EVENT);
				step[Motor_Lens_Z] = 250;
			}
			break;

		case 250:
			if(cnt[Motor_Lens_Z]> 50)	// sleep(10) *50 =500ms
			{
				cnt[Motor_Lens_Z] =0;
				step[Motor_Lens_Z] =300;
			}
			else
				cnt[Motor_Lens_Z]++;
			break;

		case 300:
			v_move(Motor_Lens_Z, (int)(-dVel_Low * sysData.fMotorResol[Motor_Lens_Z]), (short)(MotorAccTime[Motor_Lens_Z]));
			if(status[Motor_Lens_Z] & ST_HOME_SWITCH)
			{
				set_home(Motor_Lens_Z, NO_EVENT);
				set_position(Motor_Lens_Z, 0);
				step[Motor_Lens_Z] = 350;
			}
			break;

		case 350:
			if(cnt[Motor_Lens_Z]> 50)	// sleep(10) *50 =500ms
			{
				cnt[Motor_Lens_Z] =0;
				step[Motor_Lens_Z] =500;
			}
			else
				cnt[Motor_Lens_Z]++;
			break;

		case 500:
			m_bOrgFlag[Motor_Lens_Z] = true; 
			break;

		default:
			break;
		}


		//Motor_Syringe(+)
//		switch(step[Motor_Syringe])
// 		{
// 		case 0:
// 			v_move(Motor_Syringe, MotorSpeed[Motor_Syringe], (short)(MotorAccTime[Motor_Syringe]));							
// 			if((axis_done(Motor_Syringe)) && (status[Motor_Syringe] & ST_POS_LIMIT))
// 			{
// 				set_home(Motor_Syringe, STOP_EVENT);
// 				step[Motor_Syringe] = 50;
// 				Zaxis_flag[1] = true; 
// 			}
// 			break;
// 
// 		case  50:
// 			if(cnt[Motor_Syringe]> 50)	// sleep(10) *50 =500ms
// 			{
// 				cnt[Motor_Syringe] =0;
// 				step[Motor_Syringe] =100;
// 			}
// 			else
// 				cnt[Motor_Syringe]++;
// 			break;
// 
// 		case 100:
// 			v_move(Motor_Syringe, -MotorSpeed[Motor_Syringe]/4, (short)(MotorAccTime[Motor_Syringe]));
// 			if(status[Motor_Syringe] & ST_HOME_SWITCH)
// 			{
// 				set_home(Motor_Syringe, NO_EVENT);
// 				step[Motor_Syringe] = 150;
// 			}
// 			break;
// 
// 		case 150:
// 			if(cnt[Motor_Syringe]> 50)	// sleep(10) *50 =500ms
// 			{
// 				cnt[Motor_Syringe] =0;
// 				step[Motor_Syringe] =200;
// 			}
// 			else
// 				cnt[Motor_Syringe]++;
// 			break;
// 
// 		case 200:
// 			if(axis_done(Motor_Syringe))
// 			{
// 				MoveAxis(Motor_Syringe, REL, dPOS_Low, dVel_Low, iAcc_Low);
// 				set_home(Motor_Syringe, STOP_EVENT);
// 				step[Motor_Syringe] = 250;
// 			}
// 			break;
// 
// 		case 250:
// 			if(cnt[Motor_Syringe]> 50)	// sleep(10) *50 =500ms
// 			{
// 				cnt[Motor_Syringe] =0;
// 				step[Motor_Syringe] =300;
// 			}
// 			else
// 				cnt[Motor_Syringe]++;
// 			break;
// 
// 		case 300:
// 			v_move(Motor_Syringe, (int)(-dVel_Low * sysData.fMotorResol[Motor_Syringe]), (short)(MotorAccTime[Motor_Syringe]));
// 			if(status[Motor_Syringe] & ST_HOME_SWITCH)
// 			{
// 				set_home(Motor_Syringe, NO_EVENT);
// 				set_position(Motor_Syringe, 0);
// 				step[Motor_Syringe] = 350;
// 			}
// 			break;
// 
// 		case 350:
// 			if(cnt[Motor_Syringe]> 50)	// sleep(10) *50 =500ms
// 			{
// 				cnt[Motor_Syringe] =0;
// 				step[Motor_Syringe] =400;
// 			}
// 			else
// 				cnt[Motor_Syringe]++;
// 			break;
// 
// 		case 400:
// 			m_bOrgFlag[Motor_Syringe] = true; 
// 			break;
// 
// 		default:
// 			break;
// 		}

		if(Zaxis_flag[0] && Zaxis_flag[1])	// z축 위로 이동 완료되면 전체 모터 이동 시작 
		{
			//Motor_MTF(+)
//			switch(step[Motor_MTF])
// 			{
// 			case 0:
// 				v_move(Motor_MTF, MotorSpeed[Motor_MTF], (short)(MotorAccTime[Motor_MTF]));							
// 				if((axis_done(Motor_MTF)) && (status[Motor_MTF] & ST_POS_LIMIT))
// 				{
// 					set_home(Motor_MTF, STOP_EVENT);
// 					step[Motor_MTF] = 50;
// 				}
// 				break;
// 
// 			case  50:
// 				if(cnt[Motor_MTF]> 50)	// sleep(10) *50 =500ms
// 				{
// 					cnt[Motor_MTF] =0;
// 					step[Motor_MTF] =100;
// 				}
// 				else
// 					cnt[Motor_MTF]++;
// 				break;
// 
// 			case 100:
// 				v_move(Motor_MTF, -MotorSpeed[Motor_MTF]/4, (short)(MotorAccTime[Motor_MTF]));
// 				if(status[Motor_MTF] & ST_HOME_SWITCH)
// 				{
// 					step[Motor_MTF] = 150;
// 				}
// 				break;
// 
// 			case 150:
// 				if(cnt[Motor_MTF]> 50)	// sleep(10) *50 =500ms
// 				{
// 					cnt[Motor_MTF] =0;
// 					step[Motor_MTF] =200;
// 					set_home(Motor_MTF, NO_EVENT);
// 					set_position(Motor_MTF, 0);
// 				}
// 				else
// 					cnt[Motor_MTF]++;
// 				break;
// 
// 			case 200:
// 				if(axis_done(Motor_MTF))
// 				{
// 					step[Motor_MTF] = 500;
// 				}
// 				break;
// 
// 			case 500:
// 				m_bOrgFlag[Motor_MTF] = true; 
// 				break;
// 
// 			default:
// 				break;
// 			}

			//Motor_Lens_X(-방향)
			switch(step[Motor_Lens_X])
			{
			case 0:
				v_move(Motor_Lens_X, -MotorSpeed[Motor_Lens_X], (short)(MotorAccTime[Motor_Lens_X]));							
				if((axis_done(Motor_Lens_X)) && (status[Motor_Lens_X] & ST_NEG_LIMIT))
				{
					set_home(Motor_Lens_X, STOP_EVENT);
					step[Motor_Lens_X] = 50;
				}
				break;

			case  50:
				if(cnt[Motor_Lens_X]> 50)	// sleep(10) *50 =500ms
				{
					cnt[Motor_Lens_X] =0;
					step[Motor_Lens_X] =100;
				}
				else
					cnt[Motor_Lens_X]++;
				break;

			case 100:
				v_move(Motor_Lens_X, MotorSpeed[Motor_Lens_X]/4, (short)(MotorAccTime[Motor_Lens_X]));
				if(status[Motor_Lens_X] & ST_HOME_SWITCH)
				{
					set_home(Motor_Lens_X, NO_EVENT);
					step[Motor_Lens_X] = 150;
				}
				break;

			case 150:
				if(cnt[Motor_Lens_X]> 50)	// sleep(10) *50 =500ms
				{
					cnt[Motor_Lens_X] =0;
					step[Motor_Lens_X] =200;
				}
				else
					cnt[Motor_Lens_X]++;
				break;

			case 200:
				if(axis_done(Motor_Lens_X))
				{
					MoveAxis(Motor_Lens_X, REL, -dPOS_Low, dVel_Low, iAcc_Low);
					set_home(Motor_Lens_X, STOP_EVENT);
					step[Motor_Lens_X] = 250;
				}
				break;

			case 250:
				if(cnt[Motor_Lens_X]> 50)	// sleep(10) *50 =500ms
				{
					cnt[Motor_Lens_X] =0;
					step[Motor_Lens_X] =300;
				}
				else
					cnt[Motor_Lens_X]++;
				break;

			case 300:
				v_move(Motor_Lens_X, (int)(dVel_Low * sysData.fMotorResol[Motor_Lens_X]), (short)(MotorAccTime[Motor_Lens_X]));
				if(status[Motor_Lens_X] & ST_HOME_SWITCH)
				{
					set_home(Motor_Lens_X, NO_EVENT);
					set_position(Motor_Lens_X, 0);
					step[Motor_Lens_X] = 350;
				}
				break;

			case 350:
				if(cnt[Motor_Lens_X]> 50)	// sleep(10) *50 =500ms
				{
					cnt[Motor_Lens_X] =0;
					step[Motor_Lens_X] =400;
				}
				else
					cnt[Motor_Lens_X]++;
				break;

			case 400:
				m_bOrgFlag[Motor_Lens_X] = true; 
				break;

			default:
				break;
			}


			//Motor_Lens_Y(+방향)
			switch(step[Motor_Lens_Y])
			{
			case 0:
				v_move(Motor_Lens_Y, MotorSpeed[Motor_Lens_Y], (short)(MotorAccTime[Motor_Lens_Y]));							
				if((axis_done(Motor_Lens_Y)) && (status[Motor_Lens_Y] & ST_POS_LIMIT))
				{
					set_home(Motor_Lens_Y, STOP_EVENT);
					step[Motor_Lens_Y] = 50;
				}
				break;

			case  50:
				if(cnt[Motor_Lens_Y]> 50)	// sleep(10) *50 =500ms
				{
					cnt[Motor_Lens_Y] =0;
					step[Motor_Lens_Y] =100;
				}
				else
					cnt[Motor_Lens_Y]++;
				break;

			case 100:
				v_move(Motor_Lens_Y, -MotorSpeed[Motor_Lens_Y]/4, (short)(MotorAccTime[Motor_Lens_Y]));
				if(status[Motor_Lens_Y] & ST_HOME_SWITCH)
				{
					set_home(Motor_Lens_Y, NO_EVENT);
					step[Motor_Lens_Y] = 150;
				}
				break;

			case 150:
				if(cnt[Motor_Lens_Y]> 50)	// sleep(10) *50 =500ms
				{
					cnt[Motor_Lens_Y] =0;
					step[Motor_Lens_Y] =200;
				}
				else
					cnt[Motor_Lens_Y]++;
				break;

			case 200:
				if(axis_done(Motor_Lens_Y))
				{
					MoveAxis(Motor_Lens_Y, REL, dPOS_Low, dVel_Low, iAcc_Low);
					set_home(Motor_Lens_Y, STOP_EVENT);
					step[Motor_Lens_Y] = 250;
				}
				break;

			case 250:
				if(cnt[Motor_Lens_Y]> 50)	// sleep(10) *50 =500ms
				{
					cnt[Motor_Lens_Y] =0;
					step[Motor_Lens_Y] =300;
				}
				else
					cnt[Motor_Lens_Y]++;
				break;

			case 300:
				v_move(Motor_Lens_Y, (int)(-dVel_Low * sysData.fMotorResol[Motor_Lens_Y]), (short)(MotorAccTime[Motor_Lens_Y]));
				if(status[Motor_Lens_Y] & ST_HOME_SWITCH)
				{
					set_home(Motor_Lens_Y, NO_EVENT);
					set_position(Motor_Lens_Y, 0);
					step[Motor_Lens_Y] = 350;
				}
				break;

			case 350:
				if(cnt[Motor_Lens_Y]> 50)	// sleep(10) *50 =500ms
				{
					cnt[Motor_Lens_Y] =0;
					step[Motor_Lens_Y] =400;
				}
				else
					cnt[Motor_Lens_Y]++;
				break;

			case 400:
				m_bOrgFlag[Motor_Lens_Y] = true; 
				break;

			default:
				break;
			}

			//Motor_Lens_TH(-방향)
//			switch(step[Motor_Lens_TH])
// 			{
// 			case 0:
// 				v_move(Motor_Lens_TH, -MotorSpeed[Motor_Lens_TH], (short)(MotorAccTime[Motor_Lens_TH]));							
// 				if((axis_done(Motor_Lens_TH)) && (status[Motor_Lens_TH] & ST_NEG_LIMIT))
// 				{
// 					set_home(Motor_Lens_TH, STOP_EVENT);
// 					step[Motor_Lens_TH] = 50;
// 				}
// 				break;
// 
// 			case  50:
// 				if(cnt[Motor_Lens_TH]> 50)	// sleep(10) *50 =500ms
// 				{
// 					cnt[Motor_Lens_TH] =0;
// 					step[Motor_Lens_TH] =100;
// 				}
// 				else
// 					cnt[Motor_Lens_TH]++;
// 				break;
// 
// 			case 100:
// 				v_move(Motor_Lens_TH, MotorSpeed[Motor_Lens_TH]/4, (short)(MotorAccTime[Motor_Lens_TH]));
// 				if(status[Motor_Lens_TH] & ST_HOME_SWITCH)
// 				{
// 					set_home(Motor_Lens_TH, NO_EVENT);
// 					step[Motor_Lens_TH] = 150;
// 				}
// 				break;
// 
// 			case 150:
// 				if(cnt[Motor_Lens_TH]> 50)	// sleep(10) *50 =500ms
// 				{
// 					cnt[Motor_Lens_TH] =0;
// 					step[Motor_Lens_TH] =200;
// 				}
// 				else
// 					cnt[Motor_Lens_TH]++;
// 				break;
// 
// 			case 200:
// 				if(axis_done(Motor_Lens_TH))
// 				{
// 					MoveAxis(Motor_Lens_TH, REL, -dPOS_Low, dVel_Low, iAcc_Low);
// 					set_home(Motor_Lens_TH, STOP_EVENT);
// 					step[Motor_Lens_TH] = 250;
// 				}
// 				break;
// 
// 			case 250:
// 				if(cnt[Motor_Lens_TH]> 50)	// sleep(10) *50 =500ms
// 				{
// 					cnt[Motor_Lens_TH] =0;
// 					step[Motor_Lens_TH] =300;
// 				}
// 				else
// 					cnt[Motor_Lens_TH]++;
// 				break;
// 
// 			case 300:
// 				v_move(Motor_Lens_TH, (int)(dVel_Low * sysData.fMotorResol[Motor_Lens_TH]), (short)(MotorAccTime[Motor_Lens_TH]));
// 				if(status[Motor_Lens_TH] & ST_HOME_SWITCH)
// 				{
// 					set_home(Motor_Lens_TH, NO_EVENT);
// 					set_position(Motor_Lens_TH, 0);
// 					step[Motor_Lens_TH] = 350;
// 				}
// 				break;
// 
// 			case 350:
// 				if(cnt[Motor_Lens_TH]> 50)	// sleep(10) *50 =500ms
// 				{
// 					cnt[Motor_Lens_TH] =0;
// 					step[Motor_Lens_TH] =400;
// 				}
// 				else
// 					cnt[Motor_Lens_TH]++;
// 				break;
// 
// 			case 400:
// 				m_bOrgFlag[Motor_Lens_TH] = true; 
// 				break;
// 
// 			default:
// 				break;
// 			}

			//Motor_Lens_xt(-)
			switch(step[Motor_Lens_Xt])
			{
			case 0:
				v_move(Motor_Lens_Xt, -MotorSpeed[Motor_Lens_Xt], (short)(MotorAccTime[Motor_Lens_Xt]));							
				if((axis_done(Motor_Lens_Xt)) && (status[Motor_Lens_Xt] & ST_NEG_LIMIT))
				{
					set_home(Motor_Lens_Xt, STOP_EVENT);
					step[Motor_Lens_Xt] = 50;
				}
				break;

			case  50:
				if(cnt[Motor_Lens_Xt]> 50)	// sleep(10) *50 =500ms
				{
					cnt[Motor_Lens_Xt] =0;
					step[Motor_Lens_Xt] =100;
				}
				else
					cnt[Motor_Lens_Xt]++;
				break;

			case 100:
				v_move(Motor_Lens_Xt, MotorSpeed[Motor_Lens_Xt]/4, (short)(MotorAccTime[Motor_Lens_Xt]));
				if(status[Motor_Lens_Xt] & ST_HOME_SWITCH)
				{
					set_home(Motor_Lens_Xt, NO_EVENT);
					step[Motor_Lens_Xt] = 150;
				}
				break;

			case 150:
				if(cnt[Motor_Lens_Xt]> 50)	// sleep(10) *50 =500ms
				{
					cnt[Motor_Lens_Xt] =0;
					step[Motor_Lens_Xt] =200;
				}
				else
					cnt[Motor_Lens_Xt]++;
				break;

			case 200:
				if(axis_done(Motor_Lens_Xt))
				{
					MoveAxis(Motor_Lens_Xt, REL, -dPOS_Low, dVel_Low, iAcc_Low);
					set_home(Motor_Lens_Xt, STOP_EVENT);
					step[Motor_Lens_Xt] = 250;
				}
				break;

			case 250:
				if(cnt[Motor_Lens_Xt]> 50)	// sleep(10) *50 =500ms
				{
					cnt[Motor_Lens_Xt] =0;
					step[Motor_Lens_Xt] =300;
				}
				else
					cnt[Motor_Lens_Xt]++;
				break;

			case 300:
				v_move(Motor_Lens_Xt, (int)(dVel_Low * sysData.fMotorResol[Motor_Lens_Xt]), (short)(MotorAccTime[Motor_Lens_Xt]));
				if(status[Motor_Lens_Xt] & ST_HOME_SWITCH)
				{
					set_home(Motor_Lens_Xt, NO_EVENT);
					set_position(Motor_Lens_Xt, 0);
					step[Motor_Lens_Xt] = 350;
				}
				break;

			case 350:
				if(cnt[Motor_Lens_Xt]> 50)	// sleep(10) *50 =500ms
				{
					cnt[Motor_Lens_Xt] =0;
					step[Motor_Lens_Xt] =400;
				}
				else
					cnt[Motor_Lens_Xt]++;
				break;

			case 400:
				m_bOrgFlag[Motor_Lens_Xt] = true; 
				break;

			default:
				break;
			}

			//Motor_Lens_yt(+)
			switch(step[Motor_Lens_Yt])
			{
			case 0:
				v_move(Motor_Lens_Yt, MotorSpeed[Motor_Lens_Yt], (short)(MotorAccTime[Motor_Lens_Yt]));							
				if((axis_done(Motor_Lens_Yt)) && (status[Motor_Lens_Yt] & ST_POS_LIMIT))
				{
					set_home(Motor_Lens_Yt, STOP_EVENT);
					step[Motor_Lens_Yt] = 50;
				}
				break;

			case  50:
				if(cnt[Motor_Lens_Yt]> 50)	// sleep(10) *50 =500ms
				{
					cnt[Motor_Lens_Yt] =0;
					step[Motor_Lens_Yt] =100;
				}
				else
					cnt[Motor_Lens_Yt]++;
				break;

			case 100:
				v_move(Motor_Lens_Yt, -MotorSpeed[Motor_Lens_Yt]/4, (short)(MotorAccTime[Motor_Lens_Yt]));
				if(status[Motor_Lens_Yt] & ST_HOME_SWITCH)
				{
					set_home(Motor_Lens_Yt, NO_EVENT);
					step[Motor_Lens_Yt] = 150;
				}
				break;

			case 150:
				if(cnt[Motor_Lens_Yt]> 50)	// sleep(10) *50 =500ms
				{
					cnt[Motor_Lens_Yt] =0;
					step[Motor_Lens_Yt] =200;
				}
				else
					cnt[Motor_Lens_Yt]++;
				break;

			case 200:
				if(axis_done(Motor_Lens_Yt))
				{
					MoveAxis(Motor_Lens_Yt, REL, dPOS_Low, dVel_Low, iAcc_Low);
					set_home(Motor_Lens_Yt, STOP_EVENT);
					step[Motor_Lens_Yt] = 250;
				}
				break;

			case 250:
				if(cnt[Motor_Lens_Yt]> 50)	// sleep(10) *50 =500ms
				{
					cnt[Motor_Lens_Yt] =0;
					step[Motor_Lens_Yt] =300;
				}
				else
					cnt[Motor_Lens_Yt]++;
				break;

			case 300:
				v_move(Motor_Lens_Yt, (int)(-dVel_Low * sysData.fMotorResol[Motor_Lens_Yt]), (short)(MotorAccTime[Motor_Lens_Yt]));
				if(status[Motor_Lens_Yt] & ST_HOME_SWITCH)
				{
					set_home(Motor_Lens_Yt, NO_EVENT);
					set_position(Motor_Lens_Yt, 0);
					step[Motor_Lens_Yt] = 350;
				}
				break;

			case 350:
				if(cnt[Motor_Lens_Yt]> 50)	// sleep(10) *50 =500ms
				{
					cnt[Motor_Lens_Yt] =0;
					step[Motor_Lens_Yt] =400;
				}
				else
					cnt[Motor_Lens_Yt]++;
				break;

			case 400:
				m_bOrgFlag[Motor_Lens_Yt] = true; 
				break;

			default:
				break;
			}

			//Motor_PCB_Y(-)
			switch(step[Motor_PCB_Y])
			{
			case 0:
				v_move(Motor_PCB_Y, -MotorSpeed[Motor_PCB_Y], (short)(MotorAccTime[Motor_PCB_Y]));							
				if((axis_done(Motor_PCB_Y)) && (status[Motor_PCB_Y] & ST_NEG_LIMIT))
				{
					set_home(Motor_PCB_Y, STOP_EVENT);
					step[Motor_PCB_Y] = 50;
					PCBYaxis_flag = true; 
				}
				break;

			case  50:
				if(cnt[Motor_PCB_Y]> 50)	// sleep(10) *50 =500ms
				{
					cnt[Motor_PCB_Y] =0;
					step[Motor_PCB_Y] =100;
				}
				else
					cnt[Motor_PCB_Y]++;
				break;

			case 100:
				v_move(Motor_PCB_Y, MotorSpeed[Motor_PCB_Y]/4, (short)(MotorAccTime[Motor_PCB_Y]));
				if(status[Motor_PCB_Y] & ST_HOME_SWITCH)
				{
					set_home(Motor_PCB_Y, NO_EVENT);
					step[Motor_PCB_Y] = 150;
				}
				break;

			case 150:
				if(cnt[Motor_PCB_Y]> 50)	// sleep(10) *50 =500ms
				{
					cnt[Motor_PCB_Y] =0;
					step[Motor_PCB_Y] =200;
				}
				else
					cnt[Motor_PCB_Y]++;
				break;

			case 200:
				if(axis_done(Motor_PCB_Y))
				{
					MoveAxis(Motor_PCB_Y, REL, -dPOS_Low, dVel_Low, iAcc_Low);
					set_home(Motor_PCB_Y, STOP_EVENT);
					step[Motor_PCB_Y] = 250;
				}
				break;

			case 250:
				if(cnt[Motor_PCB_Y]> 50)	// sleep(10) *50 =500ms
				{
					cnt[Motor_PCB_Y] =0;
					step[Motor_PCB_Y] =300;
				}
				else
					cnt[Motor_PCB_Y]++;
				break;

			case 300:
				v_move(Motor_PCB_Y, (int)(dVel_Low * sysData.fMotorResol[Motor_PCB_Y]), (short)(MotorAccTime[Motor_PCB_Y]));
				if(status[Motor_PCB_Y] & ST_HOME_SWITCH)
				{
					set_home(Motor_PCB_Y, NO_EVENT);
					set_position(Motor_PCB_Y, 0);
					step[Motor_PCB_Y] = 350;
				}
				break;

			case 350:
				if(cnt[Motor_PCB_Y]> 50)	// sleep(10) *50 =500ms
				{
					cnt[Motor_PCB_Y] =0;
					step[Motor_PCB_Y] =400;
				}
				else
					cnt[Motor_PCB_Y]++;
				break;

			case 400:
				m_bOrgFlag[Motor_PCB_Y] = true; 
				break;

			default:
				break;
			}

			if(PCBYaxis_flag)
			{
				//Motor_PCB_X(+)
				switch(step[Motor_PCB_X])
				{
				case 0:
					v_move(Motor_PCB_X, MotorSpeed[Motor_PCB_X], (short)(MotorAccTime[Motor_PCB_X]));							
					if((axis_done(Motor_PCB_X)) && (status[Motor_PCB_X] & ST_POS_LIMIT))
					{
						set_home(Motor_PCB_X, STOP_EVENT);
						step[Motor_PCB_X] = 50;
					}
					break;

				case  50:
					if(cnt[Motor_PCB_X]> 50)	// sleep(10) *50 =500ms
					{
						cnt[Motor_PCB_X] =0;
						step[Motor_PCB_X] =100;
					}
					else
						cnt[Motor_PCB_X]++;
					break;

				case 100:
					v_move(Motor_PCB_X, -MotorSpeed[Motor_PCB_X]/4, (short)(MotorAccTime[Motor_PCB_X]));
					if(status[Motor_PCB_X] & ST_HOME_SWITCH)
					{
						set_home(Motor_PCB_X, NO_EVENT);
						step[Motor_PCB_X] = 150;
					}
					break;

				case 150:
					if(cnt[Motor_PCB_X]> 50)	// sleep(10) *50 =500ms
					{
						cnt[Motor_PCB_X] =0;
						step[Motor_PCB_X] =200;
					}
					else
						cnt[Motor_PCB_X]++;
					break;

				case 200:
					if(axis_done(Motor_PCB_X))
					{
						MoveAxis(Motor_PCB_X, REL, dPOS_Low, dVel_Low, iAcc_Low);
						set_home(Motor_PCB_X, STOP_EVENT);
						step[Motor_PCB_X] = 250;
					}
					break;

				case 250:
					if(cnt[Motor_PCB_X]> 50)	// sleep(10) *50 =500ms
					{
						cnt[Motor_PCB_X] =0;
						step[Motor_PCB_X] =300;
					}
					else
						cnt[Motor_PCB_X]++;
					break;

				case 300:
					v_move(Motor_PCB_X, (int)(-dVel_Low * sysData.fMotorResol[Motor_PCB_X]), (short)(MotorAccTime[Motor_PCB_X]));
					if(status[Motor_PCB_X] & ST_HOME_SWITCH)
					{
						set_home(Motor_PCB_X, NO_EVENT);
						set_position(Motor_PCB_X, 0);
						step[Motor_PCB_X] = 350;
					}
					break;

				case 350:
					if(cnt[Motor_PCB_X]> 50)	// sleep(10) *50 =500ms
					{
						cnt[Motor_PCB_X] =0;
						step[Motor_PCB_X] =400;
					}
					else
						cnt[Motor_PCB_X]++;
					break;

				case 400:
					m_bOrgFlag[Motor_PCB_X] = true; 
					break;

				default:
					break;

				}

				//Motor_PCB_TH(-)
				switch(step[Motor_PCB_TH])
				{
				case 0:
					if(!(Dio.PCBCoverOnCheck(false,false)))
					{
						Dio.PCBCoverOn(false,false);
						cnt[Motor_PCB_TH] =0;
					}
//					step[Motor_PCB_TH] = 20;
					step[Motor_PCB_TH] = 100;
					break;

// 				case 20:
// 					if(cnt[Motor_PCB_TH]>50)
// 						step[Motor_PCB_TH] =30;
// 					else
// 						cnt[Motor_PCB_TH]++;
// 					break;
// 
// 				case 30:
// 					if((Dio.PCBCoverOnCheck(false,false)))
// 					{
// 						step[Motor_PCB_TH] = 50;
// 					}
// 					break;
// 
// 				case 50:
// 					if(!(Dio.PCBPushCheck(false,false)))
// 					{
// 						Dio.PCBPush(false,false);
// 						cnt[Motor_PCB_TH] =0;
// 					}
// 					step[Motor_PCB_TH] = 70;
// 					break;
// 
// 				case 70:
// 					if(cnt[Motor_PCB_TH]>50)
// 						step[Motor_PCB_TH] =80;
// 					else
// 						cnt[Motor_PCB_TH]++;
// 					break;
// 
// 				case 80:
// 					if(Dio.PCBPushCheck(false,false))
// 					{
// 						step[Motor_PCB_TH] = 100;
// 					}
// 					break;

				case 100:
					v_move(Motor_PCB_TH, -MotorSpeed[Motor_PCB_TH], (short)(MotorAccTime[Motor_PCB_TH]));							
					if((axis_done(Motor_PCB_TH)) && (status[Motor_PCB_TH] & ST_NEG_LIMIT))
					{
						step[Motor_PCB_TH] = 150;
					}
					break;

				case 150:
					if(cnt[Motor_PCB_TH]> 50)	// sleep(10) *50 =500ms
					{
						cnt[Motor_PCB_TH] =0;
						step[Motor_PCB_TH] =200;
					}
					else
						cnt[Motor_PCB_TH]++;
					break;

				case 200:
					MoveAxis(Motor_PCB_TH, REL, dPOS_Low, dVel_Low, iAcc_Low);
					step[Motor_PCB_TH] = 300;
					break;

				case 300:
					if(axis_done(Motor_PCB_TH))
					{
						step[Motor_PCB_TH] = 350;
					}
					break;

				case 350:
					if(cnt[Motor_PCB_TH]> 50)	// sleep(10) *50 =500ms
					{
						cnt[Motor_PCB_TH] =0;
						step[Motor_PCB_TH] =400;
					}
					else
						cnt[Motor_PCB_TH]++;
					break;

				case 400:
					v_move(Motor_PCB_TH, (int)(-dPOS_Low * sysData.fMotorResol[Motor_PCB_TH]), (short)(MotorAccTime[Motor_PCB_TH]));
					if(status[Motor_PCB_TH] & ST_NEG_LIMIT)
					{
						set_position(Motor_PCB_TH, 0);
						step[Motor_PCB_TH] = 600;
					}
					break;

				case 600:
					m_bOrgFlag[Motor_PCB_TH] =true;
					break;

				default:
					break;
				}
			}

			if(m_bOrgFlag[Motor_Lens_X] && m_bOrgFlag[Motor_Lens_Y] /*&& m_bOrgFlag[Motor_Lens_TH] */&& m_bOrgFlag[Motor_Lens_Yt] && 
				m_bOrgFlag[Motor_PCB_X] && m_bOrgFlag[Motor_PCB_Y] && m_bOrgFlag[Motor_PCB_TH])//&& m_bOrgFlag[Motor_Lens_Z]  && m_bOrgFlag[Motor_Lens_Xt]
				break;


			eTime = myTimer(true);
			if(eTime>MOTOR_ORIGIN_TIME)
			{
				StopAxisAll();
				AmpDisableAll();

				Dio.BuzzerOn(true);
				Dio.LampRedOn(true);

				delayMsg(false);
				for(int i=0;i<MAX_MOTOR_NO;i++)	
				{
//					if(i == Motor_Spare) continue;

					if(!m_bOrgFlag[i])
					{
						clear_status(i);
						char temp[200];
						wsprintf(temp,"[%s] 전체 모터 원점 복귀 시간 초과.", MotorName[i]);
						errLogSave(temp);
					}
				}
				return false;
			}
		}


		bool b_amp_fault_flag = false;

		for(int i=0;i<MAX_MOTOR_NO;i++)	
		{
//			if(i==Motor_Spare)
//				continue;

			if(amp_fault_switch(i))
			{
				b_amp_fault_flag = true;
				break;
			}
		}

		if(b_amp_fault_flag)
		{
			CString logStr;
			StopAxisAll();
			AmpDisableAll();
			Dio.BuzzerOn(true);
			Dio.LampRedOn(true);
			logStr.Format("전체 모터 원점 동작 중 알람 발생");

			if(status[Motor_Lens_X] & ST_AMP_FAULT)						logStr = logStr + " [0]";
			if(status[Motor_Lens_Y] & ST_AMP_FAULT)						logStr = logStr + " [1]";
			if(status[Motor_Lens_Z] & ST_AMP_FAULT)						logStr = logStr + " [2]";
//			if(status[Motor_Lens_TH] & ST_AMP_FAULT)					logStr = logStr + " [3]";
			if(status[Motor_Lens_Xt] & ST_AMP_FAULT)					logStr = logStr + " [4]";
			if(status[Motor_Lens_Yt] & ST_AMP_FAULT)					logStr = logStr + " [5]";
			if(status[Motor_PCB_X] & ST_AMP_FAULT)						logStr = logStr + " [8]";
			if(status[Motor_PCB_Y] & ST_AMP_FAULT)						logStr = logStr + " [9]";
			if(status[Motor_PCB_TH] & ST_AMP_FAULT) 					logStr = logStr + " [10]";

			errMsg2(Task.AutoFlag, logStr);
//			errMsg(logStr.GetBuffer(999));
			errLogSave(temp);
			for(int i=0;i<MAX_MOTOR_NO;i++)
				clear_status(i);
			return false;
		}

		DoEvents();
//		checkMessage();
		Sleep(10);
	}


	for(int i=0; i<MAX_MOTOR_NO; i++)
	{
#ifdef	ON_LINE_MOTOR
		if(clear_status(i))
		{
			delayMsg(false);

			clear_status(i);

			char temp[200];
			wsprintf(temp,"[%s] 전체 모터 원점 복귀 중 모터 초기화 실패.", MotorName[i]);
			errLogSave(temp);

			return false;
		}
#endif
		m_bOrgFlag[i] = true;
		frames_clear(i);
	}

	// MTF, Lens z축, PCB th만 대기 위치로 이동...
	double vel[3] = {0,};
	double pos[3] = {0,};
	short acc[3] = {0,};
	short axis2[3] = {0,};

// 	axis2[0]  = short(Motor_MTF);
// 	vel[0] = sysData.fMotorSpeed[Motor_MTF] * sysData.fMotorResol[Motor_MTF];
// 	acc[0] = (short)(sysData.iMotorAccTime[Motor_MTF]);
// 	pos[0] = model.axis[Motor_MTF].pos[Wait_Pos] * sysData.fMotorResol[Motor_MTF];

	axis2[1]  = short(Motor_Lens_Z);
	vel[1] = sysData.fMotorSpeed[Motor_Lens_Z] * sysData.fMotorResol[Motor_Lens_Z];
	acc[1] = (short)(sysData.iMotorAccTime[Motor_Lens_Z]);
	pos[1] = model.axis[Motor_Lens_Z].pos[Wait_Pos] * sysData.fMotorResol[Motor_Lens_Z];

	axis2[2]  = short(Motor_PCB_TH);
	vel[2] = sysData.fMotorSpeed[Motor_PCB_TH] * sysData.fMotorResol[Motor_PCB_TH];
	acc[2] = (short)(sysData.iMotorAccTime[Motor_PCB_TH]);
	pos[2] = model.axis[Motor_PCB_TH].pos[Wait_Pos] * sysData.fMotorResol[Motor_PCB_TH];

	start_move_all(3, axis2, pos, vel, acc);

	Dio.setAlarm(YELLOW_LAMP);
	wsprintf(temp,"전체 모터 원점 복귀 완료");
	delayMsg(temp, 20000, M_COLOR_GREEN);

	return true;
}

int CMotorSet::HomeCheck()
{
	int iHomeCheckFlag = 0;

	for(int i=0; i<MAX_MOTOR_NO; i++)
	{
		if(m_bOrgFlag[i]==false)
			iHomeCheckFlag += 0x01 << i;
	}

	Task.iHomeErrorFlag = iHomeCheckFlag;

	return iHomeCheckFlag;
}


BOOL CMotorSet::JogMove(int axis, double dVel)
{// 나중에 축 별로 나누어서 사용.
	if(!GetAmpFault(axis))
		return FALSE;

	double dAcc = (short)(sysData.iMotorAccTime[axis]);

	frames_clear(axis);

	int ret;
	ret = v_move((int)axis, dVel, (int)dAcc);

	return ret;
}

BOOL CMotorSet::JogStop(int axis)
{
	frames_clear(axis);

	int ret = v_move_stop((int)axis);

	int ep = myTimer(true);
#ifdef	ON_LINE_MOTOR
	int eTime;
	while(!axis_done(axis))
	{
		DoEvents();

		eTime = myTimer(true);
		if(eTime-ep>1000)
		{
			errLogSave("JOG 이동 정지 시간 초과. [1 sec]");
			return false;
		}
	}
#endif

	clear_status(axis);

	return ret;
}

bool CMotorSet::goMotorPos(int no, short axis[MAX_MOTOR_NO], double pos[MAX_MOTOR_NO])
{
	short axis2[MAX_MOTOR_NO] = {0, };
	double pos2[MAX_MOTOR_NO] = {0, };
	double vel[MAX_MOTOR_NO] = {0, };
	short acc[MAX_MOTOR_NO] = {0, };
	int cnt =0;
	double curPos;

	for(int i=0; i<no; i++)
	{
		if(!m_bOrgFlag[axis[i]])		return false;

		curPos = GetCurrentPos(axis[i]);
		ClearAxis(axis[i]);

		axis2[cnt] = axis[i];
		pos2[cnt] = pos[i] * sysData.fMotorResol[axis[i]];
		vel[cnt] = sysData.fMotorSpeed[axis[i]] * sysData.fMotorResol[axis[i]];
		acc[cnt] = (short)(sysData.iMotorAccTime[axis[i]]);

		if( fabs(pos[i]-curPos)<0.01) 			// 이동할 위치에서 10um 이상 차이가 없을때는 움직이지 않음.
			continue;
		else
			cnt++;
	}

	start_move_all(cnt, axis2, pos2, vel, acc);

	return true;
}

bool CMotorSet::MoveAxis(int axis, bool AbSFlag, double dPos, double dVel, int iAcc)
{	// abs 1:absolute, 0:increment
	if(axis == 7)
		return false;

	clear_status(axis);

	if(amp_fault_switch(axis))
	{
		m_bOrgFlag[axis] = false;

		errLogSave("AMP Alram 발생. MoveAxis 동작 실패.");

		amp_fault_reset(axis);								// AMP Fault를 clear..
		Sleep(100);
		amp_fault_set(axis);								// AMP Fault를 clear..
		return false;
	}

//	if(!GetInposition(axis))
//	{
//		wsprintf(motorMSG, "☞ [Inposition Error]가 발생하였습니다. [%d 축]",axis+1);
//		return false;
//	}

	if(AbSFlag == ABS)
	{
		double curPos = GetCurrentPos(axis);
		if(curPos == dPos)	
		{
			return false;
		}

		if(m_bOrgFlag[axis]==false)
		{
			wsprintf(motorMSG, "☞ 모터 원점 복귀를 먼저 실행 하십시요. [%d 축]",axis+1);
			return false;
		}
	}
	else if(AbSFlag==REL)
	{
		if(dPos == 0)	
			return false;

		dPos += GetCurrentPos(axis);
	}

	dPos *= sysData.fMotorResol[axis];
	
	if(dPos>0)					dPos = (int)(dPos+0.5);

#ifdef ON_LINE_MOTOR
	//	start_move(axis, dPos, dVel, dAcc);

	short axisAll[MAX_MOTOR_NO] = {0, };
	double posAll[MAX_MOTOR_NO] = {0, };
	double velAll[MAX_MOTOR_NO] = {0, };
	short accAll[MAX_MOTOR_NO] = {0, };
//	pos[i] = pos[i] * sysData.fMotorResol[axis[i]];
	axisAll[0] = axis;
	posAll[0] = dPos;
	velAll[0] = dVel * sysData.fMotorResol[axis];
	accAll[0] = (short)(iAcc);

// 	axisAll[1] = 3;
// 	posAll[1] = dPos;
// 	velAll[1] = dVel * sysData.fMotorResol[axis];
// 	accAll[1] = (short)(iAcc);

	start_move_all(1, axisAll, posAll, velAll, accAll);
//	start_move_all(2, axisAll, posAll, velAll, accAll);

#endif
	return true;
}

bool CMotorSet::ClearAxis(int axis)
{
#ifdef ON_LINE_MOTOR
	set_stop(axis);
	clear_status(axis);
	frames_clear(axis);
#endif
	return true;
}

bool CMotorSet::Lens_Motor_Align_Move(double offsetX, double offsetY, double offsetTh)
{
	double eTime;
	short axis[4];	/* axis[0] : X , axis[1] : Y , axis[2] : Z , axis[3] : Theta */
	double pos[4];	/* axis[0] : X , axis[1] : Y , axis[2] : Z , axis[3] : Theta */

	char logMsg[1000];

	double d_dist_X		= model.axis[Motor_Lens_X].pos[Align_Pos] + offsetX ;	
	double d_dist_Y		= model.axis[Motor_Lens_Y].pos[Align_Pos] + offsetY;	
//	double d_dist_Th	= model.axis[Motor_Lens_TH].pos[Align_Pos] + offsetTh;	

	for (int i=Motor_Lens_X; i<=Motor_Lens_Y/*Motor_Lens_TH*/; i++)
	{
		if(i==Motor_Lens_Z)
			continue;


		clear_status(i);

		if(!m_bOrgFlag[i])
		{
			sprintf_s(logMsg, "%s Lens 부 모터가 원점 복귀를 하지 않았습니다.", MotorName[i]);
			errMsg2(Task.AutoFlag, logMsg);
//			errMsg(logMsg);
			return false;
		}

		axis[i-Motor_Lens_X]	= i;
				
		if(i==Motor_Lens_X)				pos[i-Motor_Lens_X]	= model.axis[i].pos[Align_Pos] + offsetX;		/* Align 위치부터 이동 */
		else if(i==Motor_Lens_Y)		pos[i-Motor_Lens_X]	= model.axis[i].pos[Align_Pos] + offsetY;		/* Align 위치부터 이동 */
//		else if(i==Motor_Lens_TH)		pos[i-Motor_Lens_X]	= model.axis[i].pos[Align_Pos] + offsetTh;		/* Align 위치부터 이동 */
	}

	sprintf_s(logMsg, "Lens 부 %s로 이동 합니다.", MotorPosName[Align_Pos]);
	//	delayMsg(logMsg, 10000, M_COLOR_BLUE);

	double MotorPos[2];
	MotorPos[0] = GetCurrentPos(Motor_Lens_X) - model.axis[Motor_Lens_X].pos[Align_Pos];
	MotorPos[1] = GetCurrentPos(Motor_Lens_Y) - model.axis[Motor_Lens_Y].pos[Align_Pos];

	if(fabs(MotorPos[0]) >model.axis[Motor_Lens_X].m_dLimit_Err || fabs(MotorPos[1]) >model.axis[Motor_Lens_Y].m_dLimit_Err)
	{
		sprintf_s(logMsg, "Lens 부 Align Pos 위치를 벗어 났습니다.");
		errMsg2(Task.AutoFlag, logMsg);
//		errMsg(logMsg);
		return false;
	}

	int ep = myTimer(true);

	int step=0;

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif

	while(1)
	{
		switch(step)
		{
		case 0:
			goMotorPos(1, axis+3, pos+3);		// Theta..
			goMotorPos(2, axis, pos);			// X, Y
			step = 10;
			break;

		case 10:
//			goMotorPos(1, axis+3, pos+3);		// Theta..
			step = 100;
			break;

		case 100:								// 이동 완료 확인..
			if(axis_done(Motor_Lens_X))		step = 101;
			break;

		case 101:
			if(axis_done(Motor_Lens_Y))		step = 103;
			break;

		case 103:
//			if(axis_done(Motor_Lens_TH))		step = 1000;
			step = 1000;
			break;
			
		default:
			break;
		}

		if(step==1000)
			break;


		eTime = myTimer(true);
		if(eTime-ep>MOTOR_MOVE_TIME)
		{
			if(step>100)
			{
				int motorNo = step - 100;
				sprintf_s(logMsg, "Lens 부 [%s 모터] 이동 시간 초과", MotorName[motorNo]);
			}
			else
			{
				sprintf_s(logMsg, "Lens 부 이동 비정상");
			}
			errLogSave(logMsg);
			errMsg2(Task.AutoFlag, logMsg);
//			errMsg(logMsg);

			return false;
		}

		Sleep(10);
		checkMessage();
	}

	return true;
}


bool CMotorSet::Lens_Motor_Move(int index, double offsetX, double offsetY, double offsetTh)
{
	double eTime;
	short axis[6];
	double pos[6];

	char logMsg[1000];

	if(index<Wait_Pos || index>Bonding_Pos)
	{
		sprintf_s(logMsg, "Lens 부 모터 이동 위치가 비정상입니다. [index : %d]", index);
		errLogSave(logMsg);
		errMsg2(Task.AutoFlag, logMsg);
//		errMsg(logMsg);

		return false;
	}

	if(index==Bonding_Pos)
	{
		double dMotor = model.axis[Motor_PCB_Y].pos[index] - GetCurrentPos(Motor_PCB_Y);
		if(fabs(dMotor) < model.axis[Motor_PCB_Y].m_dLimit_Err)
		{
			bool b_pcb_push_state = Dio.PCBCoverOnCheck(true, false);
			if (b_pcb_push_state == false)
			{
				sprintf_s(logMsg, "PCB 부 Push Cover가 상승해 있습니다.");
				errMsg2(Task.AutoFlag, logMsg);
				//			errMsg(logMsg);
				return false;
			}
		}
	}

	int step=0;


	bool b_Z_Move_Flag = false;
	double d_dist_X = model.axis[Motor_Lens_X].pos[index] - GetCurrentPos(Motor_Lens_X);
	double d_dist_Y = model.axis[Motor_Lens_Y].pos[index] - GetCurrentPos(Motor_Lens_Y);

	if (fabs(d_dist_X)>model.axis[Motor_Lens_X].m_dLimit_Err || fabs(d_dist_Y)>model.axis[Motor_Lens_Y].m_dLimit_Err)
	{
		axis[0] = Motor_Lens_Z;												// Z, Tilx X, Tilt Y 축 대기 위치 이동 후 X, Y, Θ, Tx, Ty 동작, 동작 완료 후 Z 동작..
		axis[1] = Motor_Lens_Xt;						
		axis[2] = Motor_Lens_Yt;						

		pos[0] = model.axis[Motor_Lens_Z].pos[Wait_Pos];
		pos[1] = model.axis[Motor_Lens_Xt].pos[Wait_Pos];
		pos[2] = model.axis[Motor_Lens_Yt].pos[Wait_Pos];

		step = 0;
		int ep;
		while(1)
		{
			switch(step)
			{
			case 0:									// 6축 모터 대기 위치로 이동 명령..
				ep = myTimer(true);
				goMotorPos(3, axis, pos);			// Z, Xt, Yt

				step = 100;
				break;

			case 100:								// 이동 완료 확인..
				if(axis_done(Motor_Lens_Z))		step = 101;
				break;

			case 101:
				if(axis_done(Motor_Lens_Xt))		step = 102;
				break;

			case 102:
				if(axis_done(Motor_Lens_Yt))		step = 1000;
				break;
				
			default:
				break;
			}

			if(step==1000)
				break;


			eTime = myTimer(true);
			if(eTime-ep>MOTOR_MOVE_TIME)
			{
				if(step>100)
				{
					int motorNo = step - 100;
					sprintf_s(logMsg, "Lens 부 [%s 모터] %s 이동 시간 초과", MotorName[motorNo], MotorPosName[index]);
				}
				else
				{
					sprintf_s(logMsg, "Lens 부 %s 이동 비정상", MotorPosName[index]);
				}
				errLogSave(logMsg);
				errMsg2(Task.AutoFlag, logMsg);
//				errMsg(logMsg);

				return false;
			}

			Sleep(10);
			checkMessage();
		}
	}

	for (int i=Motor_Lens_X; i<=Motor_Lens_Yt; i++)
	{
		clear_status(i);

		if(!m_bOrgFlag[i])
		{
			sprintf_s(logMsg, "%s Lens 부 모터가 원점 복귀를 하지 않았습니다.", MotorName[i]);
			errMsg2(Task.AutoFlag,logMsg);
//			errMsg(logMsg);
			return false;
		}

		axis[i-Motor_Lens_X]	= i;

		if(index == Bonding_Pos)								// Bonding_Pos 이동 시 Align 위치에서 인식한 x, y, Theta 보정값 적용..
		{
			if (fabs(offsetX)>ERROR_LIMIT_X || fabs(offsetY)>ERROR_LIMIT_Y || fabs(offsetTh)>ERROR_LIMIT_TH)
			{
				sprintf_s(logMsg, "Lens 부 보정값이 비정상입니다. [X:%.03f, Y:%.03f, Θ:.%.03f", offsetX, offsetY, offsetTh);
				errMsg2(Task.AutoFlag, logMsg);
//				errMsg(logMsg);
				return false;
			}

			if(i==Motor_Lens_X)				pos[i-Motor_Lens_X]	= model.axis[i].pos[index] + offsetX;
			else if(i==Motor_Lens_Y)		pos[i-Motor_Lens_X]	= model.axis[i].pos[index] + offsetY;
//			else if(i==Motor_Lens_TH)		pos[i-Motor_Lens_X]	= model.axis[i].pos[index] + offsetTh;
			else if(i==Motor_Lens_Z)		pos[i-Motor_Lens_X] = model.axis[i].pos[index];
			else							pos[i-Motor_Lens_X]	= model.axis[i].pos[index];
		}
		else
			pos[i-Motor_Lens_X]	= model.axis[i-Motor_Lens_X].pos[index];
	}

	sprintf_s(logMsg, "Lens 부 %s로 이동 합니다.", MotorPosName[index]);
//	delayMsg(logMsg, 10000, M_COLOR_BLUE);


	int ep = myTimer(true);



	step=0;

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif
	
	while(1)
	{
		switch(step)
		{
		case 0:									// 6축 모터 대기 위치로 이동 명령..
			goMotorPos(2, axis, pos);			// X, Y
 			goMotorPos(1, axis+3, pos+3);		// Theta
// 			goMotorPos(1, axis+4, pos+4);		// Tx
// 			goMotorPos(1, axis+5, pos+5);		// Ty
			step = 100;
			break;

		case 100:								// 이동 완료 확인..
			if(axis_done(Motor_Lens_X))		step = 101;
			break;

		case 101:
			if(axis_done(Motor_Lens_Y))		step = 103;
			break;

// 		case 102:
// 			if(axis_done(Motor_Lens_Z))		step = 103;
// 			break;
// 
		case 103:
//			if(axis_done(Motor_Lens_TH))		step = 1000;
			step = 1000;
			break;

// 		case 104:
// 			if(axis_done(Motor_Lens_Xt))		step = 105;
// 			break;
// 			
// 		case 105:
// 			if(axis_done(Motor_Lens_Yt))		step = 1000;
// 			break;

		default:
			break;
		}

		if(step==1000)
			break;


		eTime = myTimer(true);
		if(eTime-ep>MOTOR_MOVE_TIME)
		{
			if(step>100)
			{
				int motorNo = step - 100;
				sprintf_s(logMsg, "Lens 부 [%s 모터] %s 이동 시간 초과", MotorName[motorNo], MotorPosName[index]);
			}
			else
			{
				sprintf_s(logMsg, "Lens 부 %s 이동 비정상", MotorPosName[index]);
			}
			errLogSave(logMsg);
			errMsg2(Task.AutoFlag, logMsg);
//			errMsg(logMsg);

			return false;
		}

		Sleep(10);
		checkMessage();
	}



// Z 축은 대기로 이동 한 후 나머지 모터 동작하고, 다른 모터 동작 완료 되면 Z 축 이동..
//	if(index!=Loading_Pos)
	{
		step=0;

#ifndef	ON_LINE_MOTOR
		step = 1000;
#endif
		axis[0]	= Motor_Lens_Xt;
		axis[1]	= Motor_Lens_Yt;
		axis[2]	= Motor_Lens_Z;

		pos[0] = model.axis[Motor_Lens_Xt].pos[index];
		pos[1] = model.axis[Motor_Lens_Yt].pos[index];
		pos[2] = model.axis[Motor_Lens_Z].pos[index];

		while(1)
		{
			switch(step)
			{
			case 0:									// 모든 모터 위치 이동 완료 후 Z축 1mm  원래 위치로 이동
				if(index==Loading_Pos || index==Bonding_Pos)
				{
					goMotorPos(2, axis, pos);
				}
				else
				{
					goMotorPos(3, axis, pos);
				}
				step = 102;
				break;

			case 102:								// 이동 완료 확인..
				if(axis_done(Motor_Lens_Xt))		
				{
					step = 103;
				}
				break;

			case 103:								// 이동 완료 확인..
				if(axis_done(Motor_Lens_Yt))		
					step = 104;
				break;

			case 104:								// 이동 완료 확인..
				if(axis_done(Motor_Lens_Z))		
					step = 1000;
				break;

			default:
				break;
			}
			if(step==1000)
				break;

			eTime = myTimer(true);
			if(eTime>MOTOR_MOVE_TIME)
			{
				if(step>100)
				{
					int motorNo = step - 100;
					sprintf_s(logMsg, "Lens 부 [%s 모터] %s 이동 시간 초과", MotorName[motorNo], MotorPosName[index]);
				}
				else
				{
					sprintf_s(logMsg, "Lens 부 %s 이동 비정상", MotorPosName[index]);
				}

				errLogSave(logMsg);
				errMsg2(Task.AutoFlag,logMsg);
//				errMsg(logMsg);

				return false;
			}

			Sleep(5);
			checkMessage();
		}
	}


	return true;
}

bool CMotorSet::Pcb_Motor_Align_Move(double offsetX, double offsetY, double offsetTh)
{
	char logMsg[1000];
	double eTime;
	short axis[3];
	double pos[3];
	int axis_cnt =0;
	double dOffsetLimit = 1.0;


	// 실린지 높이 확인..
	double zPos = 0;

//	zPos = GetCurrentPos(Motor_Syringe);

// 	if(fabs(zPos-model.axis[Motor_Syringe].pos[Align_Pos]) >0.1)
// 	{
// 		sprintf_s(logMsg, "Syringe Z 축을 Align 위치로 이동 후 동작하세요.");
// 		errLogSave(logMsg);
// 		errMsg2(Task.AutoFlag, logMsg);
// //		errMsg(logMsg);
// 
// 		return false;
// 	}

	for (int i=Motor_PCB_X; i<=Motor_PCB_TH; i++)
	{
		if(!m_bOrgFlag[i])
		{
			sprintf_s(logMsg, "%s PCB 부 모터가 원점 복귀를 하지 않았습니다.", MotorName[i]);
			errMsg2(Task.AutoFlag, logMsg);
//			errMsg(logMsg);
			return false;
		}

		axis[i-Motor_PCB_X]		= i;
	
		if(i==Motor_PCB_X)				pos[i-Motor_PCB_X]	= model.axis[i].pos[Align_Pos] + offsetX;
		else if(i==Motor_PCB_Y)			pos[i-Motor_PCB_X]	= model.axis[i].pos[Align_Pos] + offsetY;
		else if(i==Motor_PCB_TH)		pos[i-Motor_PCB_X]	= model.axis[i].pos[Align_Pos] + offsetTh;
	}

	double MotorPos[2];
	MotorPos[0] = GetCurrentPos(Motor_PCB_X) - model.axis[Motor_PCB_X].pos[Align_Pos];
	MotorPos[1] = GetCurrentPos(Motor_PCB_Y) - model.axis[Motor_PCB_Y].pos[Align_Pos];

	if(fabs(MotorPos[0]) >model.axis[Motor_PCB_X].m_dLimit_Err || fabs(MotorPos[1]) >model.axis[Motor_PCB_Y].m_dLimit_Err)
	{
		sprintf_s(logMsg, "PCB 부 Align Pos 위치를 벗어 났습니다.");
		errMsg2(Task.AutoFlag,logMsg);
//		errMsg(logMsg);
		return false;
	}

	int step=0;

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif
	int ep;
	while(1)
	{
		switch(step)
		{
		case 0:									// 3축 모터 대기 위치로 이동 명령..
			ep = myTimer(true);
			goMotorPos(3, axis, pos);
			step = 100;
			break;

		case 100:								// 이동 완료 확인..
			if(axis_done(Motor_PCB_X))		step = 101;
			break;

		case 101:
			if(axis_done(Motor_PCB_Y))		step = 102;
			break;

		case 102:
			if(axis_done(Motor_PCB_TH))		step = 1000;
			break;

		default:
			break;
		}

		if(step==1000)
			break;


		eTime = myTimer(true);
		if(eTime-ep>MOTOR_MOVE_TIME)
		{
			StopAxis(Motor_PCB_X);
			StopAxis(Motor_PCB_Y);
			StopAxis(Motor_PCB_TH);

			if(step>100)
			{
				int motorNo = step - 100;
				sprintf_s(logMsg, "PCB 부 [%s 모터] 이동 시간 초과", MotorName[motorNo]);
			}
			else
			{
				sprintf_s(logMsg, "PCB 부 Align 보정 이동 비정상");
			}

			errLogSave(logMsg);
			errMsg2(Task.AutoFlag,logMsg);
//			errMsg(logMsg);

			return false;
		}

		Sleep(20);
		checkMessage();
	}


#ifdef ON_LINE_MOTOR
	for (int i=Motor_PCB_X; i<=Motor_PCB_TH; i++)
	{
		double curPos;
		curPos = GetCurrentPos(axis[i-Motor_PCB_X]);
		//		get_command(axis[i-Motor_PCB_X], &curPos);
		double errVal = fabs(pos[i-Motor_PCB_X] - curPos);

		if (errVal>IN_POSITION_VAL)
		{
			sprintf_s(logMsg, "PCB 부 %s Align 보정 이동 비정상", MotorPosName[i]);

			errLogSave(logMsg);
			errMsg2(Task.AutoFlag, logMsg);
//			errMsg(logMsg);

			return false;
		}		
	}
#endif


	return true;
}


bool CMotorSet::Pcb_Motor_Move(int index, double offsetX, double offsetY, double offsetTh)
{
	char logMsg[1000];
	double eTime;
	short axis[3];
	double pos[3];
	int axis_cnt =0;

	if(!m_bOrgFlag[Motor_PCB_X] || !m_bOrgFlag[Motor_PCB_Y] || !m_bOrgFlag[Motor_PCB_TH])
	{
		sprintf_s(logMsg, "PCB 부 모터가 원점 복귀를 하지 않았습니다.");
		errMsg2(Task.AutoFlag,logMsg);
//		errMsg(logMsg);
		return false;
	}

	/* 이전 Dio.setAlarm(YELLOW_LAMP);
	double d_Z_motor_pos = GetCurrentPos(Motor_Lens_Z);
	if(index==Bonding_Pos)
	{
		if(fabs(d_Z_motor_pos - model.axis[Motor_Lens_Z].pos[Wait_Pos]) > 0.1)
		{
			sprintf_s(logMsg, "Lens 부 Z 모터가 대기 위치를 벗어났습니다.");
			errMsg(logMsg);

			return false;
		}

		bool  b_PCB_cover_push_down = Dio.PCBCoverOnCheck(true, false);
		if(!b_PCB_cover_push_down)
		{
			sprintf_s(logMsg, "PCB Push를 하강 후 동작하세요.");
			errMsg(logMsg);

			return false;
		}
	}

	double MotorPos;
	MotorPos = fabs(GetCurrentPos(Motor_PCB_Y) - model.axis[Motor_PCB_Y].pos[Bonding_Pos]);
	if(fabs(d_Z_motor_pos - model.axis[Motor_Lens_Z].pos[Wait_Pos]) > 0.1 && (MotorPos < model.axis[Motor_PCB_Y].m_dLimit_Err))		// PCB가 본딩 위치에서 이동 할때 Lens Z축 대기 위치 확인
	{
		sprintf_s(logMsg, "Lens 부 Z 모터가 대기 위치를 벗어났습니다.");
		errMsg(logMsg);
		return false;
	}
*/

	if(index ==Bonding_Pos)
	{
		bool  b_PCB_cover_push_down = Dio.PCBCoverOnCheck(true, false);
		if(!b_PCB_cover_push_down)
		{
			sprintf_s(logMsg, "PCB Push를 하강 후 동작하세요.");
			errMsg2(Task.AutoFlag,logMsg);
			//		errMsg(logMsg);

			return false;
		}
	}

	// 모든 위치에서 Lens X,Y,Z 모두 본딩 위치에 있으면.....Err
	double MotorPos[3];
	MotorPos[0] = fabs(GetCurrentPos(Motor_Lens_X) - model.axis[Motor_Lens_X].pos[Bonding_Pos]);
	MotorPos[1] = fabs(GetCurrentPos(Motor_Lens_Y) - model.axis[Motor_Lens_Y].pos[Bonding_Pos]);
	MotorPos[2] = fabs(GetCurrentPos(Motor_Lens_Z) - model.axis[Motor_Lens_Z].pos[Wait_Pos]);

	// Lens가 X,Y 본딩 위치일 경우 , Lens Z 축 확인 
	if(MotorPos[0] < model.axis[Motor_Lens_X].m_dLimit_Err && MotorPos[1] < model.axis[Motor_Lens_Y].m_dLimit_Err)
	{
		if(MotorPos[2] > 1)		// PCB가 본딩 위치로 이동 할때 Lens Z축 대기 위치 확인
		{
			sprintf_s(logMsg, "Lens 부 X,Y,Z 모터가 본딩 위치에 있습니다.");
			errMsg2(Task.AutoFlag,logMsg);
//			errMsg(logMsg);
			return false;
		}
	}



	// 실린지 높이 확인..
	double zPos = 0;

	if(index==Align_Pos )
		Syringe_Motor_Move(Align_Pos);
	else
		Syringe_Motor_Move(Wait_Pos);

	if(index<Wait_Pos /*|| index>Epoxy_Cal_Insp_Pos*/)
	{
		sprintf_s(logMsg, "PCB 부 모터 이동 위치가 비정상입니다. [index : %d]", index);
		errLogSave(logMsg);
		errMsg2(Task.AutoFlag, logMsg);
//		errMsg(logMsg);

		return false;
	}


	// 본딩위치로 들어 가거나, 나올 때는 X 축 먼저 이동 후 Y 모터 이동 목적..
	int b_bonding_move_flag = 0;

	if (index == Bonding_Pos)
	{
		b_bonding_move_flag = 1;
	}
	else
	{
		double d_x_pos = GetCurrentPos(Motor_PCB_X);
		double d_y_pos = GetCurrentPos(Motor_PCB_Y);

		// 본딩 위치에서 x, y 모터 10mm 근처 있으면..
		if( (abs(d_x_pos - model.axis[Motor_PCB_X].pos[Bonding_Pos])<model.axis[Motor_PCB_X].m_dLimit_Err) && (abs(d_y_pos-model.axis[Motor_PCB_Y].pos[Bonding_Pos])<model.axis[Motor_PCB_Y].m_dLimit_Err) )
			b_bonding_move_flag = 2;
	}

	if(fabs(offsetX)>model.axis[Motor_PCB_X].m_dLimit_Err)
	{
		sprintf_s(logMsg, "PCB 부 X 축 보정값 허용 범위[± %.01f]를 초과 하였습니다. 보정값 :%.03f", model.axis[Motor_PCB_X].m_dLimit_Err, offsetX);
		errLogSave(logMsg);
		errMsg2(Task.AutoFlag,logMsg);
//		errMsg(logMsg);

		return false;
	}

	if(fabs(offsetY)>model.axis[Motor_PCB_Y].m_dLimit_Err)
	{
		sprintf_s(logMsg, "PCB 부 Y 축 보정값 허용 범위[± %.01f]를 초과 하였습니다. 보정값 :%.03f", model.axis[Motor_PCB_Y].m_dLimit_Err, offsetY);
		errLogSave(logMsg);
		errMsg2(Task.AutoFlag, logMsg);
//		errMsg(logMsg);

		return false;
	}

	if(fabs(offsetTh)>model.axis[Motor_PCB_TH].m_dLimit_Err)
	{
		sprintf_s(logMsg, "PCB 부 Θ축 보정값 허용 범위[± %.01f]를 초과 하였습니다. 보정값 :%.03f", model.axis[Motor_PCB_TH].m_dLimit_Err, offsetTh);
		errLogSave(logMsg);
		errMsg2(Task.AutoFlag, logMsg);
//		errMsg(logMsg);

		return false;
	}


	axis[0] = Motor_PCB_X;
	axis[1] = Motor_PCB_Y;
	axis[2] = Motor_PCB_TH;

// 	if (index == Clean_Pos)
// 	{
// 		int CleanPosX, CleanPosY; 
// 		work.SerchCleanPos(CleanPosX, CleanPosY);
// 
// 		pos[0]	= model.axis[Motor_PCB_X].pos[index] + CleanPosX;
// 		pos[1]	= model.axis[Motor_PCB_Y].pos[index] + CleanPosY;
// 		pos[2]	= model.axis[Motor_PCB_TH].pos[index];
// 	}
// 	else
// 	{
		pos[0]	= model.axis[Motor_PCB_X].pos[index] + offsetX;
		pos[1]	= model.axis[Motor_PCB_Y].pos[index] + offsetY;
		pos[2]	= model.axis[Motor_PCB_TH].pos[index] + offsetTh;
//	}

	sprintf_s(logMsg, "PCB 부 %s로 이동 합니다.", MotorPosName[index]);
	//	delayMsg(logMsg, 10000, M_COLOR_BLUE);


	int step=0;

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif


	frames_clear(Motor_PCB_X);
	frames_clear(Motor_PCB_Y);
	frames_clear(Motor_PCB_TH);

	int ep;
	while(1)
	{
		switch(step)
		{
		case 0:									// 3축 모터 대기 위치로 이동 명령..
			ep = myTimer(true);

			// 1: 본딩위치 들어갈때, 2: 본딩 위치에서 나올 떄, 0:xyΘ 같이 움직일 때.
			if(b_bonding_move_flag==1)
			{
				goMotorPos(1, axis, pos);				// x 모터
				goMotorPos(1, axis+2, pos+2);			// Th 모터
			}
			else if(b_bonding_move_flag==2)
				goMotorPos(1, axis+1, pos+1);			// Y 모터
			else
				goMotorPos(3, axis, pos);

			step = 100;
			break;

		case 100:								// 이동 완료 확인..
			if(axis_done(Motor_PCB_X) && axis_done(Motor_PCB_Y) && axis_done(Motor_PCB_TH))
			{
				if(b_bonding_move_flag==1)
					goMotorPos(1, axis+1, pos+1);		// Y 이동..
				else if(b_bonding_move_flag==2)
				{
					goMotorPos(1, axis, pos);			// X 이동..
					goMotorPos(1, axis+2, pos+2);		// Th 이동..
				}
				step = 101;
			}

			break;

		case 101:
			if(axis_done(Motor_PCB_X) && axis_done(Motor_PCB_Y))
				step = 102;
			break;

		case 102:
			if(axis_done(Motor_PCB_TH))
				step = 1000;
			break;

		default:
			break;
		}

		if(step==1000)
			break;


		eTime = myTimer(true);
		if(eTime-ep>MOTOR_MOVE_TIME)
		{
			StopAxis(Motor_PCB_X);
			StopAxis(Motor_PCB_Y);
			StopAxis(Motor_PCB_TH);

			if(step>100)
			{
				int motorNo = step - 100;
				sprintf_s(logMsg, "PCB 부 [%s 모터] %s 이동 시간 초과", MotorName[motorNo], MotorPosName[index]);
			}
			else
			{
				sprintf_s(logMsg, "PCB 부 %s 이동 비정상", MotorPosName[index]);
			}

			errLogSave(logMsg);
			errMsg2(Task.AutoFlag,logMsg);
//			errMsg(logMsg);

			return false;
		}

		Sleep(5);
		checkMessage();
	}
	
// 	if(index==Epoxy_Pos)
// 		Syringe_Motor_Move(Epoxy_Pos);

	return true;
}


bool CMotorSet::LENS_Z_Motor_Move(int index)
{
	double eTime;
	short axis[1];
	double pos[1];

	char logMsg[1000];


	if(index == Loading_Pos)
	{
		bool b_lens_grip_closed = Dio.LensGripCheck(false, false);

		if(b_lens_grip_closed==false)
		{
			if(!askMsg("Grip Close 상태입니다. 하강 하겠습니까?" ))
				return false;
		}
	}

// 	if(flag==Bonding_Pos)
// 	{
// 		bool b_pcb_push_state = Dio.PCBPushCheck(true);
// 		if (b_pcb_push_state == false)
// 		{
// 			sprintf_s(logMsg, "PCB 부 Push Cover가 상승해 있습니다.");
// 			errMsg(logMsg, );
// 			return false;
// 		}
// 	}

	if(!m_bOrgFlag[Motor_Lens_Z])
	{
		sprintf_s(logMsg, "Lens 부 Z 모터가 원점 복귀를 하지 않았습니다.");
		errMsg2(Task.AutoFlag,logMsg);
//		errMsg(logMsg);
		return false;
	}

	if(index == Bonding_Pos)
	{
		if(!Dio.PCBCoverOnCheck(true, false))
		{
			sprintf_s(logMsg, "PCB 부 Lens Cover 열려 있습니다.");
			errMsg2(Task.AutoFlag, logMsg);
//			errMsg(logMsg);
			return false;
		}
	}


	if(index == Loading_Pos)
	{
		for(int i=Motor_Lens_X; i<=Motor_Lens_Yt; i++)
		{
			if(i==Motor_Lens_Z)
				continue;

			double dCheckPos = GetCurrentPos(i);


			if(fabs(dCheckPos-model.axis[i].pos[Loading_Pos])>1)
			{
				sprintf_s(logMsg, "Lens 부 모터가 Loading 위치를 벗어나 있습니다.");
				errMsg2(Task.AutoFlag, logMsg);
//				errMsg(logMsg);
				return false;
			}
		}

		pos[0]	= model.axis[Motor_Lens_Z].pos[Loading_Pos];
	}
	else if(index == Bonding_Pos)
	{
		for(int i=Motor_Lens_X; i<=Motor_Lens_Yt; i++)
		{
//			if(i==Motor_Lens_Z)
//				continue;

			double dCheckPos = GetCurrentPos(i);
			
			if(i == Motor_Lens_Z)		// z축 본딩 위치에 있을 경우 다시 본딩 위치로 이동 하라 했을 경우 errMsg 발생.
			{
				if(fabs(dCheckPos-model.axis[i].pos[Bonding_Pos])< model.axis[i].m_dLimit_Err)
				{
					sprintf_s(logMsg, "Lens 부 Z축 모터가 Bonding 위치에 있습니다.");
					errMsg2(Task.AutoFlag,logMsg);
//					errMsg(logMsg);
					return false;
				}
			}
			else	// 6축 다른 모터..
			{
				if(fabs(dCheckPos-model.axis[i].pos[Bonding_Pos])>model.axis[i].m_dLimit_Err)
				{
					sprintf_s(logMsg, "Lens 부 모터가 Bonding 위치를 벗어나 있습니다.");
					errMsg2(Task.AutoFlag, logMsg);
//					errMsg(logMsg);
					return false;
				}
			}
		}

		pos[0]	= model.axis[Motor_Lens_Z].pos[Bonding_Pos];
	}
	else
		pos[0]	= model.axis[Motor_Lens_Z].pos[Wait_Pos];

	axis[0] = Motor_Lens_Z;


	sprintf_s(logMsg, "Lens 부 %s 모터 이동 합니다.", MotorPosName[Motor_Lens_Z]);
	//	delayMsg(logMsg, 10000, M_COLOR_BLUE);


	int step=0;

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif
	int ep;
	while(1)
	{
		switch(step)
		{
		case 0:
			ep = myTimer(true);
			goMotorPos(1, axis, pos);
			step = 100;
			break;

		case 100:								// 이동 완료 확인..
			if(axis_done(Motor_Lens_Z))
				step = 1000;
			break;

		default:
			break;
		}

		if(step==1000)
			break;


		eTime = myTimer(true);
		if(eTime-ep>MOTOR_MOVE_TIME)
		{
			if(step>100)
			{
				sprintf_s(logMsg, "Lens 부 [%s 모터] 이동 시간 초과", MotorPosName[Motor_Lens_Z]);
			}
			else
			{
				sprintf_s(logMsg, "Lens 부 %s 이동 비정상", MotorPosName[Motor_Lens_Z]);
			}

			errLogSave(logMsg);
			errMsg2(Task.AutoFlag, logMsg);
//			errMsg(logMsg);

			return false;
		}

		Sleep(10);
		checkMessage();
	}

	return true;
}



bool CMotorSet::Syringe_Motor_Move(int index)
{
	return false;
}


bool CMotorSet::MTF_Motor_Move(int index)
{
	double eTime;
	short axis[1];
	double pos[1];

	char logMsg[1000];

	if(index !=Loading_Pos && index !=Wait_Pos)
	{
		sprintf_s(logMsg, "MTF부 모터 이동 위치가 비정상입니다. [index : %d]", index);
		errLogSave(logMsg);
		errMsg2(Task.AutoFlag,logMsg);
//		errMsg(logMsg);

		return false;
	}

// 	if(!m_bOrgFlag[Motor_MTF])
// 	{
// 		sprintf_s(logMsg, "MTF부 모터가 원점 복귀를 하지 않았습니다.");
// 		errMsg2(Task.AutoFlag,logMsg);
// //		errMsg(logMsg);
// 		return false;
// 	}

// 	axis[0] = Motor_MTF;
// 	pos[0]	= model.axis[Motor_MTF].pos[index];

//	sprintf_s(logMsg, "MTF부 %s로 이동 합니다.", MotorPosName[index]);
//	delayMsg(logMsg, 10000, M_COLOR_BLUE);


	int step=0;

#ifndef	ON_LINE_MOTOR
	step = 1000;
#endif

	while(1)
	{
		switch(step)
		{
		case 0:									
			goMotorPos(1, axis, pos);
			step = 106;
			break;

		case 106:								// 이동 완료 확인..
// 			if(axis_done(Motor_MTF))		step = 1000;
// 			break;
			step = 1000;
		default:
			break;
		}

		if(step==1000)
			break;


		eTime = myTimer(true);
		if(eTime>MOTOR_MOVE_TIME)
		{
			if(step>100)
			{
				int motorNo = step - 100;
				sprintf_s(logMsg, "MTF 부 [%s 모터] %s 이동 시간 초과", MotorName[motorNo], MotorPosName[index]);
			}
			else
			{
				sprintf_s(logMsg, "MTF부 %s 이동 비정상", MotorPosName[index]);
			}

			errLogSave(logMsg);
			errMsg2(Task.AutoFlag,logMsg);
//			errMsg(logMsg);

			return false;
		}

		Sleep(10);
		checkMessage();
	}
	

	return true;
}
