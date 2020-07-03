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

	if(retcode != OD_SUCCESSFUL){
		ERROR(0,"-Edit Dict Error- 0x%x",retcode);
		return 0;
	}
	
	return 1;
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
	//sin_cos_test(d);
}



#include "gait.h"


#define ARRAY_K   knee_flexion
#define ARRAY_H   hip_flexion

int PERIOD = 0;							// 设定运行次数
int period = 0;						// 实际运行次数
uint16_t endP = 0;
uint8_t Index = 0;
int x=0, temp_x;						//extern int x=0;语法错误

extern INTEGER32 Pos_Actual_Val, Pos_Actual_Val_node3, Pos_Actual_Val_node4, Pos_Actual_Val_node5;
extern INTEGER16 Current_Actual_Val_node2;
extern INTEGER32 Pos_SET_VALUE_node3;

Uint32 Position[6];
float Position_float[6];
int Position_int[6];

int epos_state = 50;

#include "func_CanOpen.h"
#define QC_TO_Degree_EC90 1//1820.44
#define QC_TO_Degree_RE40 1//2222.22
void assive (CO_Data* d)
{
	if(PERIOD != 0){
		
		endP = sizeof(ARRAY_H)/sizeof(*ARRAY_H);				// period size
		
		//Position_float[0] = (ARRAY_H[x]*QC_TO_Degree_EC90);
		Position_int[0] = (ARRAY_H[x]*QC_TO_Degree_EC90);		// postive means go forward
		Position[0] = (Uint32)Position_int[0];					//for node2
		
		//Position_float[1] = (ARRAY_K[x]*QC_TO_Degree_EC90);
		Position_int[1] = (ARRAY_K[x]*QC_TO_Degree_EC90);
		Position[1] = (Uint32)Position_int[1];					//for node3 counterclkwise
		
		temp_x = x + endP/2;									//start form half period. another side
		if(temp_x >= endP){
			temp_x = temp_x - endP;
		}
		
		//Position_float[2] = (ARRAY_H[temp_x]*QC_TO_Degree_EC90);
		Position_int[2] = (ARRAY_H[temp_x]*-QC_TO_Degree_EC90);
		Position[2] = (Uint32)Position_int[2];					//for node4
		
		//Position_float[3] = (ARRAY_K[temp_x]*QC_TO_Degree_RE40);
		Position_int[3] = (knee_flexion_RE40[temp_x]*QC_TO_Degree_RE40);
		Position[3] = (Uint32)Position_int[3];					//for node5  clkwise

		x++;
		if( x == endP){
			x = 0;
			period++;
			MYMSG("#%d\t%d\r\n",period,PERIOD);
		}
		
		Edit_Dict(d , 0x20620020, 0x00, &Position[0]);//Pos_SET_VALUE node_1
		Edit_Dict(d , 0x20630020, 0x00, &Position[1]);
		Edit_Dict(d , 0x20640020, 0x00, &Position[2]);
		Edit_Dict(d , 0x20650020, 0x00, &Position[3]);
		
		for(uint8_t i = 0;i<4;i++){
			ROW_MSG("%d\t", Position_int[i]);
		}
		ROW_MSG("%d\t%d\t%d\t%d\r\n",Pos_Actual_Val,Pos_Actual_Val_node3,Pos_Actual_Val_node4, Pos_Actual_Val_node5);
	}
	
	if(period >= PERIOD){
		HAL_TIM_Base_Stop_IT(CANOPEN_TIMx_handle);	//关闭定时器
		period = 5;
		setState(&TestMaster_Data, Pre_operational);		//停止
		epos_state = 0;
	}
}

Uint32 pos;
int subI = 0;
void sin_cos_test (CO_Data* d)
{
	
	pos = (int)(10000*sin(2.0f*3.14f*0.005f*subI));
	
	Edit_Dict(d , 0x20620020, 0x00, &pos);
	Edit_Dict(d , 0x20630020, 0x00, &pos);
	Edit_Dict(d , 0x20640020, 0x00, &pos);
	Edit_Dict(d , 0x20650020, 0x00, &pos);
	
	subI++;
	ROW_MSG("%d\t%d\t%d\t%d\t%d\r\n",Pos_Actual_Val,Pos_Actual_Val_node3,Pos_Actual_Val_node4, Pos_Actual_Val_node5,pos);
}

void Test_curve (CO_Data* d)
{
	UNS32 re;
	endP = sizeof(test_angle)/sizeof(*test_angle);
		pos = test_angle[x++];
		if( x==endP){
			x = 0;
		}
	
	re = Edit_Dict(d , 0x20620020, 0x00, &pos);
	re = Edit_Dict(d , 0x20630020, 0x00, &pos);
	re = Edit_Dict(d , 0x20640020, 0x00, &pos);
	re = Edit_Dict(d , 0x20650020, 0x00, &pos);
	
	if(re != OD_SUCCESSFUL){
		ERROR(0,"-TPDO update error- 0x%x",re);
	}
	
	ROW_MSG("%d\t%d\t%d\t%d\t%d\r\n",Pos_Actual_Val,Pos_Actual_Val_node3,Pos_Actual_Val_node4, Pos_Actual_Val_node5,pos);
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
