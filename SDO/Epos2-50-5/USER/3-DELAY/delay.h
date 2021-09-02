
#ifndef __delay_H
#define	__delay_H

#include "stm32f10x.h"

/*****************  macro�� ***************************************************/
/* ��������ȡ��ע�� */

//#define US_DELAY	USE
#define MS_DELAY	USE

/*****************  global variable ȫ�ֱ���***************************************************/
extern volatile u32 TimingDelay;                                    //ȫ�ֱ�����ʹ���жϺ����ܹ�����TimingDelay. �ױ�

/*****************  function declaration ��������********************************************/

void Delay(__IO u32 nCount);                                        //����ȷ���ӳ�

	#if defined MS_DELAY	
        void SysTick_ms_Init(void);
        void Delay_ms(__IO u32 nTime);

	#elif defined US_DELAY	
        void SysTick_us_Init(void);
        void Delay_us(__IO u32 nTime);
	#endif
	
	#if (defined MS_DELAY) || (defined US_DELAY)
        void TimingDelay_decrement(void);							//�����ⲿ����
        void SysTick_Init(void);

	#endif

#endif /* __DELAY_H */
