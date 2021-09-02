/*******************************************************************************
 * �ļ���  ��can.c
 * ����    ����printf�����ض���USART1�������Ϳ�����printf��������Ƭ��������
 *           ��ӡ��PC�ϵĳ����ն˻򴮿ڵ������֡�         
 * ʵ��ƽ̨��Ұ��STM32������
 * Ӳ�����ӣ�------------------------
 *          | 		PB8-CAN-RX   	 |
 *          | 		PB9-CAN-TX   	 |
 *           ------------------------
 * ��汾  ��ST3.5.0
 * ����    ������
 * ��̳    ��http://www.amobbs.com/forum-1008-1.html
 * �Ա�    ��http://firestm32.taobao.com
**********************************************************************************/

#include "can.h" 
#include "epos.h"

extern   CanTxMsg TxMessage;

/*
 * ��������CAN_GPIO_Config
 * ����  ��CAN��GPIO ����,PB8�������룬PB9�������
 * ����  ���ڲ�����
 */
static void CAN_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*����ʱ������*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

	GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);							 // ��ӳ��IO����Ϊcan

	/* Configure CAN pin: RX */									               	 // PB8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	             // ��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	/* Configure CAN pin: TX */									               // PB9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		         // �����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
}


static void CAN_GPIOA_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*΢ʨʱדʨ׃*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);


	/* Configure CAN pin: RX */									               	 // PB8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	             // ʏ-ˤɫ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/* Configure CAN pin: TX */									               // PB9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		         // شԃΆάˤԶ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}

/*
 * ��������CAN_NVIC_Config
 * ����  ��CAN��NVIC ����,��1���ȼ��飬0��0���ȼ�
		 * ���ͱ����ж�
		 * ����FIFO�����жϣ�USB_LP_CAN1_RX0_IRQn
		 * �����ж�
 */
static void CAN_NVIC_Config(void)
{
	/*NVIC_InitTypeDef NVIC_InitStructure;
	// Configure one bit for preemption priority 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	//�ж�����
	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;	   	//CAN1 RX0�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		   	//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			   			//�����ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);*/
}


/*
 * ��������CAN_Mode_Config
 * ����  ��CAN��ģʽ ����
 * ����  ���ڲ�����
 */
static void CAN_Mode_Config(void)
{
	CAN_InitTypeDef        CAN_InitStructure;
	/************************CANͨ�Ų�������**********************************/
	/*CAN�Ĵ�����ʼ��*/
	CAN_DeInit(CAN1);
	CAN_StructInit(&CAN_InitStructure);
	/*CAN��Ԫ��ʼ��*/
	CAN_InitStructure.CAN_TTCM=DISABLE;			   		//MCR-TTCM  �ر�ʱ�䴥��ͨ��ģʽʹ��
	CAN_InitStructure.CAN_ABOM=ENABLE;			   		//MCR-ABOM  �Զ����߹��� 
	CAN_InitStructure.CAN_AWUM=ENABLE;			   		//MCR-AWUM  ʹ���Զ�����ģʽ
	CAN_InitStructure.CAN_NART=DISABLE;			   		//MCR-NART  ��ֹ�����Զ��ش�	  DISABLE-�Զ��ش�
	CAN_InitStructure.CAN_RFLM=DISABLE;			   		//MCR-RFLM  ����FIFO ����ģʽ  DISABLE-���ʱ�±��ĻḲ��ԭ�б���  
	CAN_InitStructure.CAN_TXFP=DISABLE;			   		//MCR-TXFP  ����FIFO���ȼ� DISABLE-���ȼ�ȡ���ڱ��ı�ʾ�� 
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal; //��������ģʽ
	CAN_InitStructure.CAN_SJW=CAN_SJW_2tq;		   	//BTR-SJW ����ͬ����Ծ��� 2��ʱ�䵥Ԫ
	CAN_InitStructure.CAN_BS1=CAN_BS1_5tq;		   	//BTR-TS1 ʱ���1 ռ����6��ʱ�䵥Ԫ
	CAN_InitStructure.CAN_BS2=CAN_BS2_3tq;		   	//BTR-TS1 ʱ���2 ռ����3��ʱ�䵥Ԫ
	CAN_InitStructure.CAN_Prescaler =4;		   			//BTR-BRP �����ʷ�Ƶ��  ������ʱ�䵥Ԫ��ʱ�䳤�� 36/(1+5+3)/4= 1Mbps EPOS������Ĭ��Ϊ1Mbps
	CAN_Init(CAN1, &CAN_InitStructure);
}


/*
 * ��������CAN_Filter_Config
 * ����  ��CAN�Ĺ����� ����
 * ����  ���ڲ�����
 */
static void CAN_Filter_Config(void)
{
  CAN_FilterInitTypeDef  CAN_FilterInitStructure;

	//CAN��������ʼ��
	CAN_FilterInitStructure.CAN_FilterNumber=0;											//��������0
	CAN_FilterInitStructure.CAN_FilterMode =CAN_FilterMode_IdList;	//�����ڱ�ʶ���б�ģʽ
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_16bit;	//������λ��Ϊ����32λ��
	// ʹ�ܱ��ı�ʾ�����������ձ�ʾ�������ݽ��бȶԹ��ˣ���չID�������µľ����������ǵĻ��������FIFO0�� 

	CAN_FilterInitStructure.CAN_FilterIdHigh= (u16)0x581<<5;				//Ҫ���˵�ID RTR=0,IDE=0  ��������� 2
	CAN_FilterInitStructure.CAN_FilterIdLow = (u16)0x582<<5;				//��������� 0
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh= 0x0000;			
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;			//��������16λÿλ����ƥ��
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0 ;				//��������������FIFO��filter0
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;			//ʹ�ܹ�����
	CAN_FilterInit(&CAN_FilterInitStructure);
	
	//CANͨ���ж�ʹ��
	//CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);*/
}


/*
 * ��������CAN_Config
 * ����  ����������CAN�Ĺ���
 * ����  ����
 * ���  : ��
 * ����  ���ⲿ����
 */
void CAN_Config(void)
{
  //CAN_GPIO_Config();
	CAN_GPIOA_Config();
  CAN_NVIC_Config();
  CAN_Mode_Config();
  CAN_Filter_Config();   
}

/*
 * ��������CAN_SetMsg
 * ����  ��CANͨ�ű�����������
 * ����  ����
 * ���  : ��
 * ����  ���ⲿ����
 */	 
/*
void CAN_SetMsg(uint32_t StdId, uint8_t IDE, uint32_t *p)
{	  
  int i;
	
	TxMessage.StdId = StdId;						 
  //TxMessage.ExtId=0x1314;					 													//ʹ�õ���չID
	
  TxMessage.IDE = (IDE==0)? CAN_ID_STD:CAN_ID_EXT;					//��չģʽ
  TxMessage.RTR=CAN_RTR_DATA;				 													//���͵�������
  TxMessage.DLC=8;							 															//���ݳ���Ϊ2�ֽ�
  
	for(i = 0;i<TxMessage.DLC;i++){
		TxMessage.Data[i]=p[i];
	}
}*/

//TxMessage.Data[0]Ϊ�͵�ַ
void CAN_SetMsg(uint32_t ID, uint32_t low, uint32_t high){
	
	
	uint32_t tmp;
	uint8_t mail;
	int i;
	
	//low = 0x0EFEFABCD;
	//high = 0x0ABCDEFAD;
	
	TxMessage.StdId = ID;						 
	
  TxMessage.IDE = CAN_ID_STD;					//��չģʽ
  TxMessage.RTR = CAN_RTR_DATA;				//���͵�������
  TxMessage.DLC = 8;							 		//���ݳ���Ϊ8�ֽ�

	tmp = low;													//0-cs��1,2-Index  ,3-Sub
	for(i=0;i<4;i++){
		TxMessage.Data[i] = low;
		low = low>>8;
	}
	
	tmp = high;
	
	for(i=4;i<8;i++){
		TxMessage.Data[i] = tmp;
		tmp = tmp>>8;
	}
	mail = CAN_Transmit(CAN1, &TxMessage);
	
	i= 50;
	while(CAN_TransmitStatus(CAN1, mail) != CANTXOK && --i>0){};	//���Ͳ��ɹ��Ļ����ȴ�
	
	//CAN_Transmit(CAN1, &TxMessage);
}

