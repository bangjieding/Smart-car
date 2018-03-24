
/*
		����IO����ʼ��ʱ��


 */ 
#include "stm32f10x.h"
 
#ifndef __MAIN_H
#define __MAIN_H

void RCC_Configuration(void);
void NVIC_Configuration(void);
void GPIO_Configuration(void);
void IWDG_Init(void);


void Delay_ms(unsigned int ii32)
{   
	u32 i,j;
	for(j=0;j<ii32;j++)
	{
    for(i=0;i<6500;i++);
 	}
}

void Delay_nms(unsigned int ii32)
{   
	u32 i,j;
	for(j=0;j<ii32;j++)
	{
    for(i=0;i<4900;i++);
 	}
}


void RCC_Configuration(void)
{
		//#if !defined STM32F10X_LD_VL && !defined STM32F10X_MD_VL && !defined STM32F10X_HD_VL
		//����ʱ��Ϊ72MHZ������Ϊ8MHZ
		/* SYSCLK, HCLK, PCLK2 and PCLK1 configuration -----------------------------*/   
		/* RCC system reset(for debug purpose) */
		ErrorStatus HSEStartUpStatus;

		RCC_DeInit();	  /* RCC system reset(for debug purpose) */
		RCC_HSEConfig(RCC_HSE_ON);  /* Enable HSE */	//ʹ���ⲿ����
		HSEStartUpStatus = RCC_WaitForHSEStartUp();/* Wait till HSE is ready */   //�ȴ��ⲿʱ���ȶ�

		if (HSEStartUpStatus == SUCCESS)
		{/* Enable Prefetch Buffer����FLASHԤȡָ���� */	 
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		 //FLASHʱ����� �Ƽ�ֵ:
		 // SYSCLK = 0~24MHz   Latency=0
		 // SYSCLK = 24~48MHz  Latency=1
		 // SYSCLK = 48~72MHz  Latency=2
		FLASH_SetLatency(FLASH_Latency_2);/* Flash 2 wait state */  

		RCC_HCLKConfig(RCC_SYSCLK_Div1);  /* HCLK(AHB??) = SYSCLK */	 
		RCC_PCLK2Config(RCC_HCLK_Div1);   /* PCLK2(APB2) = HCLK */
		RCC_PCLK1Config(RCC_HCLK_Div2);	  /* PCLK1(APB1) = HCLK/2 */ 	 //���36M

		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);//72MHZ

		RCC_PLLCmd(ENABLE);	/* Enable PLL */ 
		while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)	  /* Wait till PLL is ready */
		{
		}
		/* Select PLL as system clock source */
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		/* Wait till PLL is used as system clock source */
		while(RCC_GetSYSCLKSource() != 0x08)
		{}

}
//#endif /* STM32F10X_LD_VL && STM32F10X_MD_VL */
	//�����Ǹ���ģ�鿪��ʱ��
	//����GPIO
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB,ENABLE);


	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

}  

void NVIC_Configuration(void)
{   
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

		/* enabling interrupt */
		//Step2.�ж�NVIC���ã������жϣ��������ȼ�
		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;      //�����¼�
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�0
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;         //��Ӧ���ȼ�1
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //�����ж�
		NVIC_Init(&NVIC_InitStructure);   

		NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;      //�����¼�
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�0
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;         //��Ӧ���ȼ�1
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //�����ж�
		NVIC_Init(&NVIC_InitStructure);  

		/* Enable the USARTy Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);	


		/* Enable the USARTy Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		/* Enable the USARTy Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		/* Enable the UARTy Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);	

		/* Enable the UARTy Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);	
}	 

//��ʱ30S,����GPRS���Ͷ�ʱ�ȳ�ʱ��Ķ�ʱ��
void TIM5_Configuration(void)
{	 
		TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;
		//TIM1 ʹ���ڲ�ʱ��  //TIM_InternalClockConfig(TIM1);
		//TIM1�������� //����Ԥ��Ƶ����Ƶϵ��71����APB2=72M, TIM1_CLK=72/72=1MHz
		//TIM_Period��TIM1_ARR��=1000�����������ϼ�����1000����������¼�������ֵ����
		//���ϼ���ģʽ //TIM_RepetitionCounter(TIM1_RCR)=0��ÿ��������������������¼�
		TIM_DeInit(TIM5);
		TIM_BaseInitStructure.TIM_Prescaler = 36000-1;//36000��Ƶ;	2K��Ƶ��	 1/2K	 *60000 =30S
		TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_BaseInitStructure.TIM_Period =60000;// 
		TIM_BaseInitStructure.TIM_ClockDivision = 0; //����ʡ��
		TIM_TimeBaseInit(TIM5, &TIM_BaseInitStructure);

		TIM_ClearFlag(TIM5, TIM_FLAG_Update);  //���жϣ�����һ�����жϺ����������ж�
		TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);	//ʹ��TIM1�ж�Դ
		TIM_UpdateDisableConfig(TIM5,DISABLE);//Enables or Disables the TIMx Update event.      
		TIM_Cmd(TIM5, ENABLE);	  //TIM1�ܿ��أ�����

}

//��ʱ20MS
void TIM4_Configuration(void)
{	 
		TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;

		TIM_DeInit(TIM4);
		TIM_BaseInitStructure.TIM_Prescaler = 719;//720��Ƶ;	0.1M������	 1/0.1M	 *1000 =1ms
		TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_BaseInitStructure.TIM_Period =100;// 
		TIM_BaseInitStructure.TIM_ClockDivision = 0; //����ʡ��
		TIM_TimeBaseInit(TIM4, &TIM_BaseInitStructure);

		TIM_ClearFlag(TIM4, TIM_FLAG_Update);  //���жϣ�����һ�����жϺ����������ж�
		TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);	//ʹ��TIM1�ж�Դ
		TIM_UpdateDisableConfig(TIM4,DISABLE);//Enables or Disables the TIMx Update event.      
		// NVIC->ISER[0] |= (1 << (TIM2_IRQChannel & 0x1F));     // enable interrupt
		TIM_Cmd(TIM4, ENABLE);	  //TIM1�ܿ��أ�����

}

/********************************************************************
				GPIO��ʼ������
********************************************************************/
void GPIO_Configuration(void)
{  
  	GPIO_InitTypeDef  GPIO_InitStructure; 

	  /* ����LED��ʹ�õ�GPIO�ܽ�ģʽ�����ģʽ�����������*/
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7; //ʹ��PC0~PC7
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				//GPIO���������ģʽ
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  	GPIO_Init(GPIOC, &GPIO_InitStructure);  						//��ص�GPIO�ڳ�ʼ��
	
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;    //����PIN
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU; //��������
		GPIO_Init(GPIOB,&GPIO_InitStructure); //��ʼ�� IO
  	GPIO_SetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);//�ر����е�LEDָʾ��
}	 

void IWDG_Init(void)
{
		IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
		/* IWDG counter clock: 40KHz(LSI) / 128 = 312.5 Hz  3.2msһ����*/ 
		IWDG_SetPrescaler(IWDG_Prescaler_128);
		/* Set counter reload value to 349 */
		IWDG_SetReload(500);  //Լ1.4S
		/* Reload IWDG counter */
		IWDG_ReloadCounter();
		/* Enable IWDG (the LSI oscillator will be enabled by hardware) */
		IWDG_Enable();
}
#endif 

