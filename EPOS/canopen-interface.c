/*
 * canopen-interface.c
 *
 *  Created on: Mar 5, 2020
 *      Author: test
 */

#include "canopen_interface.h"


UNS32 Edit_Dict(CO_Data* d, Uint32 Index_Type,Uint8 SubIndex, void* pdata)
{
	UNS32 retcode;
	UNS16 Index = Index_Type>>16;
	UNS32 ByteSize = (Index_Type&(UNS32)0xFF)>>3;

	retcode = setODentry( d, Index, SubIndex, pdata, &ByteSize, 1 );

	return retcode;
}

/*
 * author lhx
 *
 * @brief : statement in state.c.  callback when Already into preOperational state.
 * Window > Preferences > C/C++ > Editor > Templates.
 */

void _preOperational(CO_Data* d){

//	uint32_t data;
	MSG("complete preOperational\r\n");

}

void _initialisation(CO_Data* d)
{
	(void)d;
	MSG("complete initialization\r\n");

}
void _operational(CO_Data* d)
{
	(void)d;
	MSG("complete operational\r\n");
}
void _stopped(CO_Data* d)
{
	(void)d;
	MSG("complete stop\r\n");
}


/*
 * author lhx
 *
 * @brief : after sendPDOevent, so at beginning ,the first PDO's value is configured in the dict.
 * Window > Preferences > C/C++ > Editor > Templates.
 */


void assive (CO_Data* d);
void Test_curve(CO_Data* d);

void sin_cos_test (CO_Data* d);
void _post_TPDO(CO_Data* d)
	{
	assive(d);
}



#include "gait.h"

#define PERIOD 5		//运行次数
uint8_t period = 0;


//node2
uint8_t start = 0;
uint16_t endP = 0;
uint8_t Index = 0;
extern Uint32 pos;										//֧ܺλ׃
extern int x;												//extern int x=0;语法错误
extern INTEGER32 Pos_Actual_Val;
extern INTEGER16 Current_Actual_Val_node2;

#define ARRAY   hip_0_10m
#define ARRAY_1 hip_1_10m

//node3
extern INTEGER32 Pos_Actual_Val_node3;
extern INTEGER32 Pos_SET_VALUE_node3;
int x3;
Uint32 pos3;
uint8_t start3 = 0;
uint16_t endP3 = 0;
#define ARRAY_H   knee_0_10m
#define ARRAY_H_1 knee_1_10m


int epos_state = 50;
#include "func_CanOpen.h"
void assive (CO_Data* d)
{
	
	UNS32 re;
	if(PERIOD != 0){
		if(start == 0){
			endP = sizeof(ARRAY)/sizeof(*ARRAY);
			pos = ARRAY[x++];
			if( x==endP){
				endP = sizeof(ARRAY_1)/sizeof(*ARRAY_1);
				start = 1;
				x = 0;
			}
		}
		else{
			pos = ARRAY_1[x++];
			if( x==endP){
				x = 0;
			}
		}
		
		if(start3 == 0){
			endP3 = sizeof(ARRAY_H)/sizeof(*ARRAY_H);
			pos3 = ARRAY_H[x3++];
			if( x3==endP3){
				endP3 = sizeof(ARRAY_H_1)/sizeof(*ARRAY_H_1);
				start3 = 1;
				x3 = 0;
			}
		}
		else{
			pos3 = ARRAY_H_1[x3++];
			if( x3==endP3){
				x3 = 0;
				period++;
			}
		}
		
		re = Edit_Dict(d , Pos_SET_VALUE, 0x00, &pos);
		if(re != OD_SUCCESSFUL){
			ERROR(0,"-TPDO update error- 0x%x",re);
		}
		
		re = Edit_Dict(d , 0x20630020, 0x00, &pos3);
		if(re != OD_SUCCESSFUL){
			ERROR(0,"-TPDO update error- 0x%x",re);
		}
		
		
		ROW_MSG("%d\t%d\t%d\t%d\t%d\r\n",Pos_Actual_Val,pos,Pos_Actual_Val_node3, pos3,Current_Actual_Val_node2);
	}
	
	if(period == PERIOD){
		//HAL_TIM_Base_Stop_IT(CANOPEN_TIMx_handle);	//关闭定时器
		period = 5;
		setState(&TestMaster_Data, Pre_operational);		//停止
		epos_state = 0;
	}
}

int subI = 0;
void sin_cos_test (CO_Data* d)
{
	UNS32 re;
	
	pos = (int)(10000*sin(2.0f*3.14f*0.005f*subI));
	pos3 = pos;
	
	re = Edit_Dict(d , Pos_SET_VALUE, 0x00, &pos);
	if(re != OD_SUCCESSFUL){
		ERROR(0,"-TPDO update error- 0x%x",re);
	}
	
	re = Edit_Dict(d , 0x20630020, 0x00, &pos3);
	if(re != OD_SUCCESSFUL){
		ERROR(0,"-TPDO update error- 0x%x",re);
	}
	
	subI++;
	ROW_MSG("%d\t%d\t%d\t%d\r\n",Pos_Actual_Val,pos,Pos_Actual_Val_node3, pos3);
}

void Test_curve (CO_Data* d)
{
	UNS32 re;
	endP = sizeof(test_angle)/sizeof(*test_angle);
		pos = test_angle[x++];
		if( x==endP){
			x = 0;
		}
	
	re = Edit_Dict(d , Pos_SET_VALUE, 0x00, &pos);
	re = Edit_Dict(d , 0x20630020, 0x00, &pos);
	
	if(re != OD_SUCCESSFUL){
		ERROR(0,"-TPDO update error- 0x%x",re);
	}
	
	ROW_MSG("%d\t%d\t%d\r\n",Pos_Actual_Val,pos,Pos_Actual_Val_node3);
}


/*
 * author lhx
 *
 * @brief : in SYNC
 * Window > Preferences > C/C++ > Editor > Templates.
 */

void _post_sync(CO_Data* d)
{
	(void)d;
	SYNC_MSG("-post_sync-\r\n");
}



/*
 * author lhx
 *
 * @brief : life guard
 * Window > Preferences > C/C++ > Editor > Templates.
 */

void _heartbeatError(CO_Data* d, UNS8 heartbeatID)
{
	(void)d;
	(void)heartbeatID;
	MSG_WAR(0x44, "heart beat error", heartbeatID);
	EposMaster_Stop();
}
void _post_SlaveBootup(CO_Data* d, UNS8 SlaveID){(void)d;(void)SlaveID;}
void _post_SlaveStateChange(CO_Data* d, UNS8 nodeId, e_nodeState newNodeState){(void)d;(void)nodeId;(void)newNodeState;}
void _nodeguardError(CO_Data* d, UNS8 id){(void)d;(void)id;}


/*
 * author lhx
 *
 * @brief : receive a emcy
 * Window > Preferences > C/C++ > Editor > Templates.
 */
void _post_emcy(CO_Data* d, UNS8 nodeID, UNS16 errCode, UNS8 errReg, const UNS8 errSpec[5])
{
	(void)d;
	(void)nodeID;
	(void)errCode;
	(void)errReg;
	(void)errSpec;
}
