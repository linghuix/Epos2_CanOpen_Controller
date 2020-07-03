#ifndef	_APP_H_
#define	_APP_H_

#include  "BSP.h"			// Board support package header
#include  "ucos_ii.h" 		// uC/OS-II header
#include "debug.h"
#include "HW_epos.h"
#include "gait.h"

/******************任务优先级*******************/
#define STARTUP_TASK_PRIO     		2
#define	TASK_canrcv_PRIO			6
#define	TASK_cansend_PRIO			5
#define	TASK_remote_PRIO			7
#define	TASK_canapp_PRIO			3



/************任务需要的堆栈设置************/
#define STARTUP_TASK_STK_SIZE   	80
#define	TASK_A_STK_SIZE				300
#define	TASK_B_STK_SIZE				400
#define	TASK_remote_STK_SIZE				400
#define	TASK_canapp_STK_SIZE		500
#define CAN_RECEIVE_STK 			700


extern OS_EVENT * CRCV_WAIT_Semp;

/**************** �û��������� *******************/

void Task_Start(void *p_arg);

void Epos_Task(void *p_arg);
void CANRcv_Task(void *p_arg);
void CANSend_Task(void *p_arg);
void RemoteController_Task(void *p_arg);


void TIMx_DispatchFromISR(void);
void CANRcv_DateFromISR(void);

#endif	//_APP_H_
