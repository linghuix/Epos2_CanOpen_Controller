
#include "HW_epos.h"

/*
 * 函数名：接收传感器数
 * 描述 
 * 调用  
 */
uint8_t NODE_ID[] = {2,3,4,5,6,7};                          																//EPOS ID
Epos Controller1, Controller2, Controller3, Controller4, Controller5, Controller6;        //控制器对
Epos *Controller[] = {&Controller1, &Controller2, &Controller3, &Controller4, &Controller5, &Controller6};
uint8_t NumControllers = 2;

/*
 * author lhx
 *
 * @brief : Enable Epos in can network
 * Window > Preferences > C/C++ > Editor > Templates.
 */

void Epos_NodeEnable(void)
{	
	uint8_t i;		//index
	for(i=0;i<NumControllers;i++){
		Node_StructInit(Controller[i], NOT_USED, NODE_ID[i]);	//初始化最大加速度，速度，跟踪误差，波特1M/s
	}

	///通过canopen设定EPOS控制器参
	printf("-----------------------------------------------\r\n");
	printf("-----------------Epos_Init---------------------\r\n");
	printf("-----------------------------------------------\r\n");

	for(i=0;i<NumControllers;i++){
		Node_ParamConfig(Controller[i]);
	}

	printf("-----------------------------------------------\r\n");
	printf("-------------Initial_EPOS_Done!----------------\r\n");
	printf("-----------------------------------------------\r\n");
	//OSTimeDlyHMSM(0, 0,0,500);


	//******** 控制模式设置 *******
	for(i=0;i<NumControllers;i++){
		Node_setMode(Controller[i], Position_Mode);
	}
	printf("-----------------------------------------------\r\n");
	printf("-----------------Mode_set----------------------\r\n");
	printf("-----------------------------------------------\r\n");
	//OSTimeDlyHMSM(0, 0,0,500);

	
	//******** 使能EPOS *******
	for(i=0;i<NumControllers;i++){
		Node_OperEn(Controller[i]);                                               //Switch On Disable to Operation Enable
	}
	printf("-----------------------------------------------\r\n");
	printf("-----------------Enable_EPOS-------------------\r\n");
	printf("-----------------------------------------------\r\n");
		
}

void EPOS_Reset(void)
{
	for(int i=0;i<NumControllers;i++){
		masterNMT(&TestMaster_Data, Controller[i], NMT_Reset_Node);	//to Pre-Operation
	}
}

void EPOS_Start(void)
{
	printf("-----------------------------------------------\r\n");
	printf("---------NMT -enter into operation-------------\r\n");
	printf("-----------------------------------------------\r\n");
	for(int i=0;i<NumControllers;i++){
		masterNMT(&TestMaster_Data, Controller[i], NMT_Start_Node);	//to operation
	}
}


/** 速度模式的速度设置 */
void Epos_SpeedSet(Uint32 speed){
	
		 SDO_Write(Controller[1],Target_Velocity,0x00,speed);
		 SDO_Write(Controller[1],OD_CTRL_WORD ,0x00,0x0F);	
}


/**************Position Mode*********************************/
void PM_SetAngle(Epos* epos, Uint32 angle){
    
    #if defined SDO
    SDO_Write(epos, Target_pos, 0x00, angle);
        #endif 
}


/** Position Set */
void Epos_PosSet(Epos* epos, Uint32 pos)
	{
	
		 SDO_Write(epos,OD_CTRL_WORD ,0x00,0x0F);	
		 PM_SetAngle(epos,pos);
		 SDO_Write(epos,OD_CTRL_WORD ,0x00,0x7F);	
}


/**控制器启
void Epos_Start(void)
{
	
    ******** EPOS basic COMMANDING PARAMETERS *******
		SDO_Write(Controller[1], Profile_Acceleration,0x00,4000);
		SDO_Write(Controller[1], Profile_Deceleration,0x00,4000);	
		SDO_Write(Controller[1], Motion_Profile_Type,0x00,0);
		
		SDO_Write(Controller[1], OD_P_VELOCITY ,0x00, 50);
	
		OSTimeDlyHMSM(0, 0,0,2000);
		printf("\r\n EPOS control beginning!\r\n\r\n");

}
*/

/*
 * 函数名：实时控制任务
 * 描述  
 * 调用  
 */
/**实现速度摇摆控制 */
void speed_Task(void){
	
	Uint32 speed = 50;
	
	Epos_SpeedSet(speed);
	Epos_Delay(1000); 
	
	Epos_SpeedSet(-speed);
	Epos_Delay(1000); 
	
	Epos_SpeedSet(speed*5);
	Epos_Delay(1000); 

	Epos_SpeedSet(-speed*5);
	Epos_Delay(1000); 
}


/** position task 摇摆*/
void pos_Task(void){
	
	Uint32 pos = 20000,i;
	
	for(i=0;i<5;i++){
		Epos_PosSet(Controller[1] ,pos*i);
		Epos_Delay(50); 
	}
	
	for(i=0;i<5;i++){
		Epos_PosSet(Controller[1],-pos*i);
		Epos_Delay(50); 
	}
}


void Epos_ControlTask(void){
	
	pos_Task();
}


/*
 * 函数名：接收传感器数
 * 描述  
 * 调用  
 */
Uint32 status;
Uint32 velocity, speed;
void Epos_ReceiveDate(){
	
		status = SDO_Read(Controller[1], 0x6041,0x00);
		Epos_Delay(2); 
		speed = SDO_Read(Controller[1], Velocity_Demand_Value,0x00);		
		Epos_Delay(2); 
		printf("status:0x%X\t%d\r\n",status,speed);
		speed = SDO_Read(Controller[1], OP_MODE_Read,0x00);	
		velocity = SDO_Read(Controller[1], Target_Velocity,0x00);	
		Epos_Delay(2); 
		printf("mode:%d\t%d\r\n",speed, velocity);
		Epos_Delay(10); 
}


//状态的控制
void State(void){

    //NMT_Pre(Controller[1], ALL);                        
    SDO_Read(Controller[1],Statusword,0x00);

    Node_PDOConfig(Controller[1]);
    SDO_Read(Controller[1],0x1400,0x01);
    SDO_Read(Controller[1],0x1600,0x00);
    SDO_Read(Controller[1],0x1600,0x01);

    //NMT_Start(Controller[1], ALL);
}


/*
 * 函数名：接收传感器数
 * 描述  
 * 调用  
 */

#define PI 3.1415
#include "gait.h"

uint32_t flag = 0xff;          //用于标志是否接收到数据，在中断函数中赋
int pos=0;                       //电机位置
int x=0;                            //角度自变
int angle_sensor;
	
/*void Epos_Conroller_TIMBack(){

//		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);		//清除中断标志


		//if(flag==0xff) flag = 0;

		pos = (x>=323) ? angle_2[x-323]:angle_1[x];

		//angle_sensor = SDO_Read(Controller,Pos_Actual_Value,0x00);

		PM_SetAngle(Controller[1], pos);
		PM_SetAngle(Controller[1],pos);

		if( ++x==727 ) x = 0;

}

*/
void Node_Initial_Postion(void)
{
//	SDO_Read(Epos* epos,Uint32 Index_Type,Uint8 SubIndex);
}
