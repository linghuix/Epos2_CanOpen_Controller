/**
  ******************************************************************************
  * @file    delay.c
  * @author  Linghui Xu
  * @version V1.0
  * @date    2019.4.27
  * @brief   用3.5.0版本库建的工程模板
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "timer.h"


extern Epos Controller2;
extern Epos Controller1;




extern __IO uint32_t flag;	

/**
  * @brief  TIM中断优先级配置
  * @param  None
  * @retval None
  */
void TIME_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                         /*设置NVIC中断分组2:2位抢占优先级，2位响应优先级*/

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;                         /*TIM2中断*/ 

    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;               /*先占优先级1级*/

    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;                      /*从优先级2级*/ 
        
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                         /*IRQ通道被使能*/ 

    NVIC_Init(&NVIC_InitStructure);                                         /*根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器*/
}


/**
  * @brief  TIM3 Base 单元配置，中断使能
  * @param  None
  * @retval None
  */
void TIME3_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);                                              /*定时器TIM3时钟使能*/

    TIM_TimeBaseStructure.TIM_Period = 1000;                                                         /*设置在下一个更新事件装入活动的自动重装载寄存器周期的值,计数到5000为500ms*/

    TIM_TimeBaseStructure.TIM_Prescaler =(7200-1);                                                    /*设置用来作为TIMx时钟频率除数的预分频值72MHz / (7200) = 10000Hz*/

    TIM_TimeBaseStructure.TIM_ClockDivision = 0;                                                      /*设置时钟分割:TDTS = Tck_tim*/ 

    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                                       /*TIM向上计数模式*/

    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);                                                   /*根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位*/

    //TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_Trigger,ENABLE);  主程序中控制                           /*使能或者失能指定的TIM中断*/

    TIM_Cmd(TIM3, ENABLE);                                                                            //使能TIMx外设
}



/**
  * @brief  TIME2 Base 单元配置，中断使能
  * @param  None
  * @retval None
  */
void TIME2_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);                    /*定时器TIM2时钟使能*/
    
    TIM_TimeBaseStructure.TIM_Period = 5000;                              /*设置在下一个更新事件装入活动的自动重装载寄存器周期的值,计数到10000为10ms*/
    
    TIM_TimeBaseStructure.TIM_Prescaler =(72-1);                            /*设置用来作为TIMx时钟频率除数的预分频值 72MHz/72 = 1MHz */
    
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;                            /*设置时钟分割:TDTS = Tck_tim*/   
    
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;             /*TIM向上计数模式*/ 
    
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);                         /*根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位*/ 
    
    //TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_Trigger,ENABLE);               /*主程序中控制,使能或者失能指定的TIM中断*/
    
    TIM_Cmd(TIM2, ENABLE);                                                  //使能TIMx外设
}


extern int angle_1[102], angle_0[57];
extern int knee_1[102], knee_0[29];
extern int test_angle[71];
extern Uint32 pos;										//电机位置
extern int x;												//角度自变量 extern int x=0;是错的，不能再一次初始化
extern int angle_sensor;

extern int hip_0_5m[114], hip_1_5m[204], hip_0_10m[57], hip_1_10m[102], hip_0_15m[38],hip_1_15m[68];
extern int knee_0_5m[58], knee_1_5m[204], knee_0_10m[29], knee_1_10m[102], knee_0_15m[19],knee_1_15m[68];


//node2
uint8_t start = 0;
uint16_t endP = 0;
uint8_t Index = 0;
extern Uint32 pos;										//支芎位變
extern int x;												//extern int x=0;璇硶閿欒
#define ARRAY   knee_0_10m
#define ARRAY_1 knee_1_10m

//node3
int x3;
Uint32 pos3;
uint8_t start3 = 0;
uint16_t endP3 = 0;
#define ARRAY_H   hip_0_10m
#define ARRAY_H_1 hip_1_10m
void TIM2_interrupt(void){
	//printf("%d\r\n", TIM_GetITStatus(TIM2, TIM_IT_Update));
	
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	
	angle_sensor = SDO_Read(&Controller2,0x6062,0x00);
	printf("%d\t%d\t%d\r\n",x,pos,angle_sensor);
	
	
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
	
	
	PM_SetAngle(&Controller2, pos);
	PM_SetAngle(&Controller1, pos3);
	
	//printf("%d\r\n\r\n", TIM_GetITStatus(TIM2, TIM_IT_Update));
}
