/****************************************************************
			定时器中断及相关函数

****************************************************************/ 

#include <tim.h>




//定时器 4 中断服务程序 
void TIM4_IRQHandler(void) //TIM4 中断  
{  
	//unsigned char i;
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //检查 TIM4 更新中断发生与否  
	{  
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update ); //清除 TIM4 更新中断标志    

		
	}  
} 





