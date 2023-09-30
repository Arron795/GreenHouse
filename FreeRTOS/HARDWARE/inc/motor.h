#ifndef _PWM_H
#define _PWM_H

#include "sys.h"
#include "stm32f4xx.h"

void TIM14_PWM_Init(u32 arr , u32 psc);
void Set_Motor(u16  pwmval );
#endif /* _PWM_H */


