#include "motor.h"


void TIM14_PWM_Init(u32 arr , u32 psc)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);//ʹ�ܶ�ʱ��ʱ��
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7,GPIO_AF_TIM14);//��AA7 ���óɶ�ʱ��14
	
	//����GPIO����
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7 ;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;	
	GPIO_Init(GPIOA,  &GPIO_InitStruct);//��ʼ��GPIO
	
	//���ö�ʱ������
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc; //��Ƶ
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up ; //���ϼ���
	TIM_TimeBaseInitStruct.TIM_Period = arr;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM14, &TIM_TimeBaseInitStruct);//��ʼ����ʱ��
	
	//���ö�ʱ��ͨ������
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1; //С�ڼ���ֵΪ��Ч
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_Low; //�͵�ƽ��Ч
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC1Init(TIM14,  &TIM_OCInitStruct);//ͨ��һ��ʼ��
	
	TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable);//ʹ��ͨ��һԤװ��
	
	TIM_ARRPreloadConfig(TIM14, ENABLE);//ʹ��ARRԤװ��
	
	TIM_Cmd(TIM14, ENABLE);//ʹ�ܶ�ʱ��14
	
	
}

void Set_Motor(u16  pwmval )
{
	
	TIM_SetCompare1(TIM14,pwmval);	//�޸ıȽ�ֵ���޸�ռ�ձ�
}


