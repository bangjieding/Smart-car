#include "delay.h"
#include "stm32f10x.h"
#include "pwm.h"

 int main(void)
 {    
    delay_init(72);  //��ʱ������ʼ��         
          
    TIM1_PWM_Init(199,7199);//(7200*200)/72000000=0.02=20ms
    while(1)
    {   
    TIM_SetCompare1(TIM1,190); //45��,1ms
     delay_ms(1000); 
    TIM_SetCompare1(TIM1,185); //90��,1.5ms
     delay_ms(0100);        
    } 
	}

		