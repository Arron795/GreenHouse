#include "RGB.h"


void GPIO_Configuration(void)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOD, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    // ����PD12��PD13��PB7Ϊ���ù���
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // ���ù���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // �������
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; // ���������費ʹ��
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    // ��PD12��PD13��PB7�ĸ��ù��ֱܷ�����ΪTIM4��ͨ��1��2��3
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4);
}
void TIM4_Configuration(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    // ����TIM4��Ԥ��Ƶ�ͼ���ֵ��ʹ�䶨ʱ����Ϊ1ms
    TIM_TimeBaseStructure.TIM_Period = 1000 - 1;
    TIM_TimeBaseStructure.TIM_Prescaler = 84 - 1; // Ԥ��Ƶ��84MHz / 84 = 1MHz
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
    TIM_OCInitTypeDef TIM_OCInitStructure;
    // ����TIM4��ͨ��1��2��3ΪPWM���
    // ʹ��PWMģʽ1��PWM����Ϊ1ms��ռ�ձ�Ϊ0%
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM4, &TIM_OCInitStructure);
    TIM_OC2Init(TIM4, &TIM_OCInitStructure);
    TIM_OC3Init(TIM4, &TIM_OCInitStructure);
    TIM_Cmd(TIM4, ENABLE);
}
void PWM_Configuration(void)
{
    // ����RGB�Ƶĳ�ʼ��ɫΪ��ɫ
    TIM4->CCR1 = 50;   // Rͨ��ռ�ձ�Ϊ0%
    TIM4->CCR2 = 50; // Gͨ��ռ�ձ�Ϊ100%
    TIM4->CCR3 = 100; // Bͨ��ռ�ձ�Ϊ100%
}


