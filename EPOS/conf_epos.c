
#include <conf_epos.h>
#include "ucos_ii.h"
#include "sdo_control.h"
#include "canopen_interface.h"

extern CanRxMsg RxMessage;
#define MS10 0x2710
#define MS5 0x1388
#define MS15 0x3A98
#define MS50 0xC350
#define MS20 0x4E20
#define S1 0xF4240
/*
 * author lhx
 *
 * @brief : 配置字典结构体中的重要参数
 *  EPOS控制器的初始化
 * Window > Preferences > C/C++ > Editor > Templates.
 */
extern UNS32 TestMaster_obj1006;
void SetMyDict(void)
{
	uint32_t data;
	TestMaster_obj1006 = MS10;		//set sync cycle
	
	data = 0x182;
	Edit_Dict(&TestMaster_Data,0x14000120, 0x01, &data);		//RPDO	node 2
	data = 0x183;
	Edit_Dict(&TestMaster_Data,0x14010120, 0x01, &data);		//RPDO	node 3
	data = 0x184;
	Edit_Dict(&TestMaster_Data,0x14020120, 0x01, &data);		//RPDO	node 2
	data = 0x185;
	Edit_Dict(&TestMaster_Data,0x14030120, 0x01, &data);		//RPDO	node 3
	
	data = 0x202;
	Edit_Dict(&TestMaster_Data,0x18000120, 0x01, &data);		//TPDO	node 2
	data = 0x210;
	Edit_Dict(&TestMaster_Data,0x18010120, 0x01, &data);		//TPDO	node 3
	data = 0x203;
	Edit_Dict(&TestMaster_Data,0x18020120, 0x01, &data);		//TPDO	node 2
	data = 0x204;
	Edit_Dict(&TestMaster_Data,0x18030120, 0x01, &data);		//TPDO	node 3
}


void EposMaster_Init(void)
{
	unsigned char nodeID = 0x01;
	setNodeId(&TestMaster_Data, nodeID);
}

#include "canopen_interface.h"
#include "func_CanOpen.h"
extern uint8_t NumControllers;
void EposMaster_Start(void)
{
	uint32_t data[6];
	SetMyDict();
	
	setState(&TestMaster_Data, Initialisation);

	if (!(*(TestMaster_Data.iam_a_slave)))		//master
	{
		EPOS_Reset();
		Epos_NodeEnable();
		
		for(int i=0;i<NumControllers;i++){
			Node_To_Home_Postion(Controller[i]);
		}
		OSTimeDlyHMSM(0, 0,0,200);
		
		EPOS_Start();
		
	}
	
	/* 验证是否进入位于home */
	for(int i=0;i<NumControllers;i++){
		data[i] = SDO_Read(Controller[i], Pos_Actual_Value, 0X00);
		MSG("pos - %x\r\n",data[i]);
	}
	
	/* 验证是否进入 Operational 模式 */
	for(int i=0;i<NumControllers;i++){
		data[i] = SDO_Read(Controller[i], Statusword, 0X00);
		MSG("state - %x\r\n",data[i]);
	}
	
	//if(((data[0]>>9)&0x01) & ((data[1]>>9)&0x01) & ((data[2]>>9)&0x01) & ((data[3]>>9)&0x01)){
		HAL_TIM_Base_Start_IT(CANOPEN_TIMx_handle);
		MSG("already start MNT\r\n");
		printf("-----------------------------------------------\r\n");
		printf("-----------------PDO_ENABLE -------------------\r\n");
		printf("-----------------------------------------------\r\n");
		//setState(&TestMaster_Data, Pre_operational); //心跳,同步周期协议配置
		setState(&TestMaster_Data, Operational);
	//}
}


void EposMaster_Stop(void)
{
	setState(&TestMaster_Data, Stopped); //心跳,同步周期协议配置
}
/*
 *
 *
 *
 *
 */

void writeNetwork (UNS8 nodeId, UNS16 index,UNS8 subIndex, UNS32 count, UNS8 dataType, UNS32 data)
{
	writeNetworkDict(&TestMaster_Data,nodeId ,index, subIndex, count, dataType, &data ,0);	//向can网络中的节点发送
}


/*
 * author lhx
 *
 * @brief : 配置网络EPOS 节点，并且设置最大的跟踪误差，最大的速度、加速度、负加速度，以及快速停止的负加速度设定
 * Window > Preferences > C/C++ > Editor > Templates.
 */
void Node_ParamConfig(Epos* epos)
{
	MSG("Epos_ParamInit node %d : \r\n", epos->node_ID);
	
    //SDO_Read(epos,OD_STATUS_WORD,0x00);                  //Fault Status=0x0108  红灯闪烁
    SDO_Write(epos, OD_CTRL_WORD, 0x00, 0x00);
	
    SDO_Write(epos, OD_CTRL_WORD, 0x00, Fault_Reset);      //Fault_Reset command 控制字设置为0x80 第7位置1，参考固件手册 Fault reset figure3-3 事件15 驱动初始化完成
    //SDO_Read(epos,OD_STATUS_WORD,0x00);                  //Switch On    Status=0x0540/0140   绿灯闪烁

    SDO_Write(epos, OD_Following_ERR_window, 0x00, MAX_F_ERR); //最大误差设置

	SDO_Write(epos, OD_MOTOR_DATA_MAX_V, 0x04, MAX_P_V);//MAX_P_V);  //最大速度
	//SDO_Write(epos, OD_MOTOR_DATA, 0x04, MAX_P_V);     //最大允许速度

    SDO_Write(epos, OD_MAX_P_VELOCITY, 0x00, MAX_P_V);//MAX_P_V);  //最大速度

    SDO_Write(epos, OD_Max_Acceleration, 0x00, epos->acc);	//max acc set

    SDO_Write(epos, OD_P_ACCELERATION, 0x00, epos->acc); 		//加速度  无效参数

    SDO_Write(epos, OD_P_DECELERATION, 0x00, epos->dec); 		//负加速度

    SDO_Write(epos, OD_QS_DECELERATION, 0x00, QDEC);     		//快速停止负加速度

    SDO_Write(epos,OD_CAN_BITRATE,0x00,0x00);              	//set value = 0. set CAN bitrate 1M/s.

}


/*
 * author lhx
 *
 * @brief : 设定EPOS 结构体，并且设置最大的跟踪误差，最大的速度、加速度、负加速度，以及快速停止的负加速度设定
 * Window > Preferences > C/C++ > Editor > Templates.
 */
void Node_StructInit(Epos* epos1, Uint8 CAN_ID, Uint8 NODE_ID)
{
    // EPOS结构体初始化
    epos1->b_init = 0;
    epos1->CAN_Handles = NULL;
    epos1->node_ID = NODE_ID;               //节点ID设置
    
    epos1->b_init = 1;                      //EPOS 初始化标志
    epos1->cur_mode = MODE_NONE;            //控制模式
    epos1->opt = 0x001f;
    epos1->acc = MAX_ACC;                   //最大加速度
    epos1->dec = MAX_DEC;                   //最大负加速度
    epos1->b_need_shutdown = 0;             //是否需要关闭控制器
}



/*
 * author lhx
 *
 * @brief : 打印CAN帧
 * Window > Preferences > C/C++ > Editor > Templates.
 */
void Print(CanRxMsg RxMessage){
    
    int i;
//    printf("0x%x\t",RxMessage.StdId);
    printf("0x%x\t",RxMessage.head.StdId);

    printf("0x");
    for(i=0;i<8;i++) printf("%02X ",RxMessage.Data[i]);
    printf("\r\n");
}



/***未通过实验**/
void Node_PDOConfig(Epos* A)
{
    /** A 节点控制器是需要发送PDO给 B 的 ***/
    /*  Transmit PDO 1 Parameter.启动PDO + 不允许RTR + 配置对应的CAN-ID 180+ID 
    SDO_Write(A,0x1400,0x01,((Uint32)0x0<<31)+((Uint32)0x0<<30) + 0x201); 
    
    //Transmit PDO 1 Mapping 映射一个对象 + 32位角度设置寄存器
    SDO_Write(A,0x1A00,0x00,0x01); 
    SDO_Write(A,0x1A00,0x01,((Uint32)PM_SET_VALUE<<16)+((Uint32)0x00<<8)+0x20); */
    
    /** B 设置对应的 RXPDO **/
    //Receive PDO 1 Parameter
    SDO_Write(A,0x1400,0x01,(((Uint32)0x0<<31)+((Uint32)0x0<<30)+0x201)); //ID与接收的TxPDO对应，实现两者之间的传输
    
    //Receive PDO 1 Mapping。设置条件：首先PDO必须使能，NMT必须位于Pre-Operation
    SDO_Write(A,0x1400,0x02,1); 
    
    SDO_Write(A,0x1600,0x00,0); 
    SDO_Write(A,0x1600,0x01,(((Uint32)Target_pos<<16)+((Uint32)0x00<<8)+0x20)); //映射的对象可以与TxPDO不同！ 
    SDO_Write(A,0x1600,0x00,1);
}



/*
 * author lhx
 *
 * @brief : 设置 EPOS node 工作模式, 并配置对应的工作模式
 * Window > Preferences > C/C++ > Editor > Templates.
 */
void Node_setMode(Epos* epos, Uint16 mode){

    epos->cur_mode = mode;
    
    SDO_Write(epos,OP_MODE,0x00,mode); 
                
    switch(mode){

	/** EPOS4 **/
        
	case(Velocity_Mode):		//CONFIGURATION PARAMETERS
			//SDO_Write(epos,OP_MODE,0x00,Velocity_Mode);
			SDO_Write(epos,OD_Max_Acceleration,0x00,1000);                                                // set Max Acceleration
			SDO_Write(epos, OD_MAX_P_VELOCITY, 0x00, MAX_P_V);                                            // Maximal Profile Velocity
			break;

	case(Current_Mode):
			SDO_Write(epos,OD_MOTOR_DATA_continue_I,0x01,2000);         // set Continuous Current Limit 连续输出电流最大值 mA
			SDO_Write(epos, OD_MOTOR_DATA_MAX_I, 0x02, 4000);     //输出最大电流，推荐为两倍连续最大电流
			SDO_Write(epos, OD_MOTOR_DATA_MAX_MPP, 0x03, 1);        //Changes only in “Disable” state.Number of magnetic pole pairs 参考电机手册
			SDO_Write(epos, OD_MOTOR_DATA_MAX_V, 0x04, 25000);     //限制电机最大速度 rpm
			SDO_Write(epos, OD_MOTOR_DATA_TH_CONT, 0x05, 1);         // thermal time constant
			break;

	case(Profile_Position_Mode):	//CONFIGURATION PARAMETERS
			SDO_Write(epos, OD_MAX_P_VELOCITY, 0x00, MAX_P_V);              // Maximal Profile Velocity
				SDO_Write(epos, OD_MAX_MOTOR_SPEED, 0x00, 5000);								//参考电机手册
				SDO_Write(epos, Max_gear_input_speed, 0x03,1000);
			SDO_Write(epos, OD_QS_DECELERATION, 0x00, QDEC);                //快速停止负加速度
			SDO_Write(epos,OD_Max_Acceleration,0x00,10000);
			break;

	case(Profile_Velocity_Mode):		//CONFIGURATION PARAMETERS
			SDO_Write(epos, Soft_P_Limit_Min, 0x01, 0x80000000);                //-2147483648
			SDO_Write(epos, Soft_P_Limit_Max, 0x02, 0x7FFFFFFF);                //2147483647

			SDO_Write(epos, OD_MAX_P_VELOCITY, 0x00,3000);                 //最大速度 Maximal Profile Velocity
			SDO_Write(epos, OD_QS_DECELERATION, 0x00, 50000);              //快速停止负加速度
			SDO_Write(epos, OD_MAX_MOTOR_SPEED, 0x00, 5000);              // Maximal Profile Velocity
			SDO_Write(epos, Max_gear_input_speed, 0x03,1000);
			SDO_Write(epos,OD_Max_Acceleration,0x00,10000);

			break;

	case(Homing_Mode):      //可以将该功能配置给某个数字口
			SDO_Write(epos, OD_Motion_Profile_Type, 0x00,1);                 //sin2  ramp
			break;

	case(Interpolated_Position_Mode):
			SDO_Write(epos, OD_Interpolation_Sub_Mode, 0x00,(Uint32)(-1));//always -1 cubic spline interpolation (PVT)
			SDO_Write(epos, Interpolation_Time_Period_1, 0x01,1);//always 1
			SDO_Write(epos, Interpolation_Time_Period_2, 0x02,(Uint32)(-3));//always -3  插值周期 10^-3s
			SDO_Write(epos, Soft_P_Limit_Min, 0x01, 0x80000000);                //-2147483648
			SDO_Write(epos, Soft_P_Limit_Max, 0x02, 0x7FFFFFFF);                //2147483647
			//SDO_Write(epos,OD_Position_Window, 0x00,4294967295);             //关闭 position window
			SDO_Write(epos, Pos_Window_Time, 0x00, 0);
			break;

	default:
			printf("error mode\r\n");
        
    }
}

    
void Node_OperEn(Epos* epos){
	
    SDO_Write(epos,OD_CTRL_WORD,0x00,0x06);                    // Shut down  驱动函数失能
    Epos_Delay(500);

    //SDO_Read(epos,OD_STATUS_WORD,0x00);                      // Ready to Switch On    Status=0x0121   绿灯闪烁
    
    SDO_Write(epos,OD_CTRL_WORD,0x00,0x0F);                    // Switch on AND Enable Operation 驱动参数设定
    Epos_Delay(500);
    
    //SDO_Read(epos,OD_STATUS_WORD,0x00);                      // Operation Enable      Status=0x0137   绿灯常亮
}

void Node_DisEn(Epos* epos){
	
    SDO_Write(epos,OD_CTRL_WORD,0x00,0x06);                    // Disable Operation    Controlword=0xxx 0111
    Epos_Delay(500);
}


void Epos_Delay(Uint32 time){
	OSTimeDly(time);
}
