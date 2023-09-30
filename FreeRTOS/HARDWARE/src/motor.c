#include "motor.h"


void TIM14_PWM_Init(u32 arr , u32 psc)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIO时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);//使能定时器时钟
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7,GPIO_AF_TIM14);//将AA7 复用成定时器14
	
	//配置GPIO参数
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7 ;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;	
	GPIO_Init(GPIOA,  &GPIO_InitStruct);//初始化GPIO
	
	//配置定时器参数
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc; //分频
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up ; //向上计数
	TIM_TimeBaseInitStruct.TIM_Period = arr;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM14, &TIM_TimeBaseInitStruct);//初始化定时器
	
	//配置定时器通道参数
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1; //小于计数值为有效
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_Low; //低电平有效
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC1Init(TIM14,  &TIM_OCInitStruct);//通道一初始化
	
	TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable);//使能通道一预装载
	
	TIM_ARRPreloadConfig(TIM14, ENABLE);//使能ARR预装载
	
	TIM_Cmd(TIM14, ENABLE);//使能定时器14
	
	
}

void Set_Motor(u16  pwmval )
{
	
	TIM_SetCompare1(TIM14,pwmval);	//修改比较值，修改占空比
}


