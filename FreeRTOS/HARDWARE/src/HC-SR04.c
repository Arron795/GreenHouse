#include "HC-SR04.h"

/*���뷽����ģ����Զ�����8��40KHz�����������ͬʱ�ز����ţ�echo���˵ĵ�ƽ����0��Ϊ1��
		����ʱӦ��������ʱ����ʱ���������������ر�ģ����յ�ʱ���ز��� �Ŷ˵ĵ�ƽ����1��Ϊ0��
		����ʱӦ��ֹͣ��ʱ������������ʱ�����µ����ʱ�伴Ϊ
			�������ɷ��䵽���ص���ʱ����*/
			
u8 overcount=0; //��¼��ʱ���������

void TIM3_HCSR04_Init()
{
		GPIO_InitTypeDef GPIO_InitStruct;
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
		 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
		/*PA6Ϊ����� PA5Ϊ�����*****************/
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;//����Ϊ�������
		GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6;
		GPIO_InitStruct.GPIO_OType= GPIO_OType_PP;
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStruct);
		GPIO_ResetBits(GPIOA,GPIO_Pin_6);//Ĭ��Ϊ��
	

		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
		GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
		GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5;
		GPIO_Init(GPIOA,&GPIO_InitStruct);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);//Ĭ��Ϊ��
	
		//��ʱ��3��ʼ��
		TIM_TimeBaseStructure.TIM_Period = 1000-1; //�����Զ���ת��ֵΪ999
		TIM_TimeBaseStructure.TIM_Prescaler =84-1; //����Ԥ��Ƶϵ��83  1us ����һ��
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���ģʽ
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
		
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update); //��������жϣ����һ���ж����������ж�
		TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE );//ʹ���ƶ�TIM3�жϣ���������ж�
		//�ж�����
		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		TIM_Cmd(TIM3, DISABLE);
}
//����д��ຯ��
float HCSR04_OPEN(void) //��������������
{
		TIM3_HCSR04_Init();
		float length=0,sum=0;
		u16 tim;
		unsigned int i=0;//����
		//��������ݼ���һ��ƽ��ֵ
		while(i!=5)
		{
			
			GPIO_SetBits(GPIOA,GPIO_Pin_6); //�����źţ���Ϊ�����ź�
			delay_us(20); //�ߵ�ƽ�źų���10us
			GPIO_ResetBits(GPIOA,GPIO_Pin_6); //�ȴ������ź�
			uint32_t timeout = xTaskGetTickCount() + pdMS_TO_TICKS(500); // 50ms��ʱʱ��
			while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==RESET)
			{
			 if (xTaskGetTickCount() >= timeout)
				{
				// ��ʱ�˳�
				
					return 1;
				}
			}
			//�����źŵ�����������ʱ������
			TIM_SetCounter(TIM3,0); //�����ʱ���ļ�����
			TIM_Cmd(TIM3,ENABLE);
			i+=1; //ÿ�յ�һ�λ����ź�+1,�յ�5�ξͼ����ֵ
			timeout = xTaskGetTickCount() + pdMS_TO_TICKS(500); // 50ms��ʱʱ��
			while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==SET)//�����ź���ʧ
			{
				
				if (xTaskGetTickCount() >= timeout)
				{
				// ��ʱ�˳�
				
					return 1;
				}
				
			}
			TIM_Cmd(TIM3,DISABLE);//�رն�ʱ��
			tim=TIM_GetCounter(TIM3); //��ȡTIM3�����Ĵ����еļ���ֵ
			
			length=(tim+overcount*1000)/58.0; //ͨ�������źż������  *0.017 =  1/58
			sum=length+sum;
			TIM3->CNT=0; //��TIM3�����Ĵ����ļ���ֵ����
			overcount=0; //�ж������������
			delay_ms(100);
		}
		length=sum/5;
		//printf("���������Ϊ��:%fcm \r\n",length);

		return length;

}

void TIM3_IRQHandler(void)
{
		if (TIM_GetITStatus(TIM3,TIM_IT_Update)!= RESET) //����Ƿ���TIM3�ж�
		{
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update ); //����жϸ��±�־
			overcount++;
		}
}
