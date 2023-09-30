#include "HC-SR04.h"

/*输入方波后，模块会自动发射8个40KHz的声波，与此同时回波引脚（echo）端的电平会由0变为1；
		（此时应该启动定时器计时）；当超声波返回被模块接收到时，回波引 脚端的电平会由1变为0；
		（此时应该停止定时器计数），定时器记下的这个时间即为
			超声波由发射到返回的总时长；*/
			
u8 overcount=0; //记录定时器溢出次数

void TIM3_HCSR04_Init()
{
		GPIO_InitTypeDef GPIO_InitStruct;
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
		 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
		/*PA6为输出端 PA5为输入端*****************/
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;//设置为推挽输出
		GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6;
		GPIO_InitStruct.GPIO_OType= GPIO_OType_PP;
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStruct);
		GPIO_ResetBits(GPIOA,GPIO_Pin_6);//默认为低
	

		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
		GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
		GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5;
		GPIO_Init(GPIOA,&GPIO_InitStruct);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);//默认为低
	
		//定时器3初始化
		TIM_TimeBaseStructure.TIM_Period = 1000-1; //设置自动重转载值为999
		TIM_TimeBaseStructure.TIM_Prescaler =84-1; //设置预分频系数83  1us 计数一次
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
		
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update); //清除更新中断，免得一打开中断立即产生中断
		TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE );//使能制定TIM3中断，允许更新中断
		//中断设置
		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		TIM_Cmd(TIM3, DISABLE);
}
//下面写测距函数
float HCSR04_OPEN(void) //单精度数据类型
{
		TIM3_HCSR04_Init();
		float length=0,sum=0;
		u16 tim;
		unsigned int i=0;//次数
		//测五次数据计算一次平均值
		while(i!=5)
		{
			
			GPIO_SetBits(GPIOA,GPIO_Pin_6); //拉高信号，作为触发信号
			delay_us(20); //高电平信号超过10us
			GPIO_ResetBits(GPIOA,GPIO_Pin_6); //等待回响信号
			uint32_t timeout = xTaskGetTickCount() + pdMS_TO_TICKS(500); // 50ms超时时间
			while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==RESET)
			{
			 if (xTaskGetTickCount() >= timeout)
				{
				// 超时退出
				
					return 1;
				}
			}
			//回响信号到来，开启定时器计数
			TIM_SetCounter(TIM3,0); //清楚定时器的计数器
			TIM_Cmd(TIM3,ENABLE);
			i+=1; //每收到一次回响信号+1,收到5次就计算均值
			timeout = xTaskGetTickCount() + pdMS_TO_TICKS(500); // 50ms超时时间
			while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==SET)//回响信号消失
			{
				
				if (xTaskGetTickCount() >= timeout)
				{
				// 超时退出
				
					return 1;
				}
				
			}
			TIM_Cmd(TIM3,DISABLE);//关闭定时器
			tim=TIM_GetCounter(TIM3); //获取TIM3计数寄存器中的计数值
			
			length=(tim+overcount*1000)/58.0; //通过回响信号计算距离  *0.017 =  1/58
			sum=length+sum;
			TIM3->CNT=0; //将TIM3计数寄存器的计数值清零
			overcount=0; //中断溢出次数清零
			delay_ms(100);
		}
		length=sum/5;
		//printf("超声波测距为：:%fcm \r\n",length);

		return length;

}

void TIM3_IRQHandler(void)
{
		if (TIM_GetITStatus(TIM3,TIM_IT_Update)!= RESET) //检查是否发生TIM3中断
		{
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update ); //清楚中断更新标志
			overcount++;
		}
}
