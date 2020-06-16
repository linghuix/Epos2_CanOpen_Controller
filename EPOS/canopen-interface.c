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
void _post_TPDO(CO_Data* d)
	{
	assive(d);
}



#include "gait.h"

//node2
uint8_t start = 0;
uint16_t endP = 0;
uint8_t Index = 0;
extern Uint32 pos;										//֧ܺλ׃
extern int x;												//extern int x=0;语法错误
extern INTEGER32 Pos_Actual_Val;
#define ARRAY   hip_0_5m
#define ARRAY_1 hip_1_5m

//node3
extern INTEGER32 Pos_Actual_Val_node3;
extern INTEGER32 Pos_SET_VALUE_node3;
int x3;
Uint32 pos3;
uint8_t start3 = 0;
uint16_t endP3 = 0;
#define ARRAY_H   knee_0_5m
#define ARRAY_H_1 knee_1_5m

void assive (CO_Data* d)
{
	UNS32 re;
	
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
		if( x==endP)
			x = 0;
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
		if( x3==endP3)
			x3 = 0;
	}
	
	re = Edit_Dict(d , Pos_SET_VALUE, 0x00, &pos);
	re = Edit_Dict(d , 0x20630020, 0x00, &pos3);
	
	if(re == OD_SUCCESSFUL)
		TPDO_MSG("-TPDO_update- index %d\r\n",Index);
	else
		TPDO_MSG("-TPDO update error- 0x%x\r\n",re);
	
	
	ROW_MSG("%d\t%d\t%d\t%d\r\n",Pos_Actual_Val,pos,Pos_Actual_Val_node3, pos3);
}



void Test_curve (CO_Data* d)
{
	UNS32 re;
	endP = sizeof(test_angle)/sizeof(*test_angle);
		pos = test_angle[x++]/2;
		if( x==endP)
			x = 0;
	
	re = Edit_Dict(d , Pos_SET_VALUE, 0x00, &pos);
	
	
	if(re == OD_SUCCESSFUL)
		TPDO_MSG("-TPDO_update- index %d\r\n",Index);
	else
		TPDO_MSG("-TPDO update error- 0x%x\r\n",re);
	ROW_MSG("%d\t%d\r\n",Pos_Actual_Val,pos);
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
