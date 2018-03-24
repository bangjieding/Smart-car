
/*
		定义IO，初始化时钟


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
		//设置时钟为72MHZ，晶振为8MHZ
		/* SYSCLK, HCLK, PCLK2 and PCLK1 configuration -----------------------------*/   
		/* RCC system reset(for debug purpose) */
		ErrorStatus HSEStartUpStatus;

		RCC_DeInit();	  /* RCC system reset(for debug purpose) */
		RCC_HSEConfig(RCC_HSE_ON);  /* Enable HSE */	//使能外部晶振
		HSEStartUpStatus = RCC_WaitForHSEStartUp();/* Wait till HSE is ready */   //等待外部时钟稳定

		if (HSEStartUpStatus == SUCCESS)
		{/* Enable Prefetch Buffer开启FLASH预取指功能 */	 
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		 //FLASH时序控制 推荐值:
		 // SYSCLK = 0~24MHz   Latency=0
		 // SYSCLK = 24~48MHz  Latency=1
		 // SYSCLK = 48~72MHz  Latency=2
		FLASH_SetLatency(FLASH_Latency_2);/* Flash 2 wait state */  

		RCC_HCLKConfig(RCC_SYSCLK_Div1);  /* HCLK(AHB??) = SYSCLK */	 
		RCC_PCLK2Config(RCC_HCLK_Div1);   /* PCLK2(APB2) = HCLK */
		RCC_PCLK1Config(RCC_HCLK_Div2);	  /* PCLK1(APB1) = HCLK/2 */ 	 //最大36M

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
	//下面是给个模块开启时钟
	//启动GPIO
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB,ENABLE);


	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

}  

void NVIC_Configuration(void)
{   
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

		/* enabling interrupt */
		//Step2.中断NVIC设置：允许中断，设置优先级
		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;      //更新事件
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //抢占优先级0
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;         //响应优先级1
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //允许中断
		NVIC_Init(&NVIC_InitStructure);   

		NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;      //更新事件
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //抢占优先级0
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;         //响应优先级1
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //允许中断
		NVIC_Init(&NVIC_InitStructure);  

		/* Enable the USARTy Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //抢占优先级0
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);	


		/* Enable the USARTy Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //抢占优先级0
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		/* Enable the USARTy Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //抢占优先级0
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		/* Enable the UARTy Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //抢占优先级0
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);	

		/* Enable the UARTy Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //抢占优先级0
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);	
}	 

//定时30S,用于GPRS发送定时等长时间的定时，
void TIM5_Configuration(void)
{	 
		TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;
		//TIM1 使用内部时钟  //TIM_InternalClockConfig(TIM1);
		//TIM1基本设置 //设置预分频器分频系数71，即APB2=72M, TIM1_CLK=72/72=1MHz
		//TIM_Period（TIM1_ARR）=1000，计数器向上计数到1000后产生更新事件，计数值归零
		//向上计数模式 //TIM_RepetitionCounter(TIM1_RCR)=0，每次向上溢出都产生更新事件
		TIM_DeInit(TIM5);
		TIM_BaseInitStructure.TIM_Prescaler = 36000-1;//36000分频;	2K的频率	 1/2K	 *60000 =30S
		TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_BaseInitStructure.TIM_Period =60000;// 
		TIM_BaseInitStructure.TIM_ClockDivision = 0; //不能省掉
		TIM_TimeBaseInit(TIM5, &TIM_BaseInitStructure);

		TIM_ClearFlag(TIM5, TIM_FLAG_Update);  //清中断，以免一启用中断后立即产生中断
		TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);	//使能TIM1中断源
		TIM_UpdateDisableConfig(TIM5,DISABLE);//Enables or Disables the TIMx Update event.      
		TIM_Cmd(TIM5, ENABLE);	  //TIM1总开关：开启

}

//定时20MS
void TIM4_Configuration(void)
{	 
		TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;

		TIM_DeInit(TIM4);
		TIM_BaseInitStructure.TIM_Prescaler = 719;//720分频;	0.1M的速率	 1/0.1M	 *1000 =1ms
		TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_BaseInitStructure.TIM_Period =100;// 
		TIM_BaseInitStructure.TIM_ClockDivision = 0; //不能省掉
		TIM_TimeBaseInit(TIM4, &TIM_BaseInitStructure);

		TIM_ClearFlag(TIM4, TIM_FLAG_Update);  //清中断，以免一启用中断后立即产生中断
		TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);	//使能TIM1中断源
		TIM_UpdateDisableConfig(TIM4,DISABLE);//Enables or Disables the TIMx Update event.      
		// NVIC->ISER[0] |= (1 << (TIM2_IRQChannel & 0x1F));     // enable interrupt
		TIM_Cmd(TIM4, ENABLE);	  //TIM1总开关：开启

}

/********************************************************************
				GPIO初始化函数
********************************************************************/
void GPIO_Configuration(void)
{  
  	GPIO_InitTypeDef  GPIO_InitStructure; 

	  /* 配置LED灯使用的GPIO管脚模式，输出模式，灌电流驱动*/
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7; //使用PC0~PC7
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				//GPIO工作在输出模式
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  	GPIO_Init(GPIOC, &GPIO_InitStructure);  						//相关的GPIO口初始化
	
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;    //设置PIN
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU; //上拉输入
		GPIO_Init(GPIOB,&GPIO_InitStructure); //初始化 IO
  	GPIO_SetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);//关闭所有的LED指示灯
}	 

void IWDG_Init(void)
{
		IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
		/* IWDG counter clock: 40KHz(LSI) / 128 = 312.5 Hz  3.2ms一个数*/ 
		IWDG_SetPrescaler(IWDG_Prescaler_128);
		/* Set counter reload value to 349 */
		IWDG_SetReload(500);  //约1.4S
		/* Reload IWDG counter */
		IWDG_ReloadCounter();
		/* Enable IWDG (the LSI oscillator will be enabled by hardware) */
		IWDG_Enable();
}
#endif 

