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

#include "gait.h"
uint8_t pdoindex = 0;
uint8_t Index = 0;
void _post_TPDO(CO_Data* d){

	/*UNS32 code, ByteSize, angle;
	UNS32 retcode;(void)retcode;

	ByteSize = 4;
	angle = test_angle[Index];
	//angle = 0xFFFFB1E0;

	 * ���Ϳ��ƼĴ���0x0F��0x7F, ����λ��ģʽ�ĸı�
	 1
	if(pdoindex % 2 == 0){
		code = 0x4F;
		ByteSize = 2;
		retcode = setODentry( d, 0x6040, 0, &code, &ByteSize, 1 );
		retcode = setODentry( d, 0x607A, 0, &angle, &ByteSize, 1 );
	}
	else{
		code = 0x7F;
		ByteSize = 2;
		retcode = setODentry( d, 0x6040, 0, &code, &ByteSize, 1 );
		retcode = setODentry( d, 0x607A, 0, &angle, &ByteSize, 1 );
		Index++;
	}
	pdoindex++;

	if(Index == 10) Index = 0;*/

/*	UNS32 re;
	UNS32 angle = angle_2[Index]-11740;
	re = Edit_Dict(d , Pos_SET_VALUE, 0, &angle);

	if(re == OD_SUCCESSFUL)
		MSG("-TPDO_update-\r\n");
	else
		MSG("-TPDO update error- 0x%lx\r\n",re);
	if(++Index == 323) Index = 0;*/

	UNS32 re;
	UNS32 angle = test_angle[Index];
	re = Edit_Dict(d , Pos_SET_VALUE, 0, &angle);

	if(re == OD_SUCCESSFUL)
		MSG("-TPDO_update- index %d\r\n",Index);
	else
		MSG("-TPDO update error- 0x%lx\r\n",re);
	if(++Index == 120) Index = 0;
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
	MSG("-post_sync-\r\n");
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
