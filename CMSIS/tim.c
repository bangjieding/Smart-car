/****************************************************************
			��ʱ���жϼ���غ���

****************************************************************/ 

#include <tim.h>




//��ʱ�� 4 �жϷ������ 
void TIM4_IRQHandler(void) //TIM4 �ж�  
{  
	//unsigned char i;
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //��� TIM4 �����жϷ������  
	{  
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update ); //��� TIM4 �����жϱ�־    

		
	}  
} 





