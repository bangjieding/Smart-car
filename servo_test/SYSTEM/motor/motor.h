#ifndef _motor_H
#define _motor_H
#include "stm32f10x.h"
#define MOTOR GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15
 
void motor_init(void);
void move_forward(void);
void stop(void);

#endif 
