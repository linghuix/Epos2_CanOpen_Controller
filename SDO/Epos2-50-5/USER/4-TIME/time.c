/**
  ******************************************************************************
  * @file    delay.c
  * @author  Linghui Xu
  * @version V1.0
  * @date    2019.4.27
  * @brief   ��3.5.0�汾�⽨�Ĺ���ģ��
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
  * @brief  TIM�ж����ȼ�����
  * @param  None
  * @retval None
  */
void TIME_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                         /*����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�*/

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;                         /*TIM2�ж�*/ 

    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;               /*��ռ���ȼ�1��*/

    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;                      /*�����ȼ�2��*/ 
        
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                         /*IRQͨ����ʹ��*/ 

    NVIC_Init(&NVIC_InitStructure);                                         /*����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���*/
}


/**
  * @brief  TIM3 Base ��Ԫ���ã��ж�ʹ��
  * @param  None
  * @retval None
  */
void TIME3_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);                                              /*��ʱ��TIM3ʱ��ʹ��*/

    TIM_TimeBaseStructure.TIM_Period = 1000;                                                         /*��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ,������5000Ϊ500ms*/

    TIM_TimeBaseStructure.TIM_Prescaler =(7200-1);                                                    /*����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ72MHz / (7200) = 10000Hz*/

    TIM_TimeBaseStructure.TIM_ClockDivision = 0;                                                      /*����ʱ�ӷָ�:TDTS = Tck_tim*/ 

    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                                       /*TIM���ϼ���ģʽ*/

    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);                                                   /*����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ*/

    //TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_Trigger,ENABLE);  �������п���                           /*ʹ�ܻ���ʧ��ָ����TIM�ж�*/

    TIM_Cmd(TIM3, ENABLE);                                                                            //ʹ��TIMx����
}



/**
  * @brief  TIME2 Base ��Ԫ���ã��ж�ʹ��
  * @param  None
  * @retval None
  */
void TIME2_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);                    /*��ʱ��TIM2ʱ��ʹ��*/
    
    TIM_TimeBaseStructure.TIM_Period = 5000;                              /*��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ,������10000Ϊ10ms*/
    
    TIM_TimeBaseStructure.TIM_Prescaler =(72-1);                            /*����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 72MHz/72 = 1MHz */
    
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;                            /*����ʱ�ӷָ�:TDTS = Tck_tim*/   
    
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;             /*TIM���ϼ���ģʽ*/ 
    
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);                         /*����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ*/ 
    
    //TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_Trigger,ENABLE);               /*�������п���,ʹ�ܻ���ʧ��ָ����TIM�ж�*/
    
    TIM_Cmd(TIM2, ENABLE);                                                  //ʹ��TIMx����
}


extern int angle_1[102], angle_0[57];
extern int knee_1[102], knee_0[29];
extern int test_angle[71];
extern Uint32 pos;										//���λ��
extern int x;												//�Ƕ��Ա��� extern int x=0;�Ǵ�ģ�������һ�γ�ʼ��
extern int angle_sensor;

extern int hip_0_5m[114], hip_1_5m[204], hip_0_10m[57], hip_1_10m[102], hip_0_15m[38],hip_1_15m[68];
extern int knee_0_5m[58], knee_1_5m[204], knee_0_10m[29], knee_1_10m[102], knee_0_15m[19],knee_1_15m[68];


//node2
uint8_t start = 0;
uint16_t endP = 0;
uint8_t Index = 0;
extern Uint32 pos;										//֧ܺλ׃
extern int x;												//extern int x=0;语法错误
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
