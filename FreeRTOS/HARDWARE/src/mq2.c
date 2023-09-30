
//引脚 PA0 5V
#include "mq2.h"

void ADC_Pin_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_InitTypeDef ADC_InitStruct;
	
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;//多次次转换
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;//数据对齐
	//ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;//独立模式
	ADC_InitStruct.ADC_NbrOfConversion = 1;//转换总数
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;//单通道扫描
	ADC_Init(ADC1,&ADC_InitStruct);
	
	//转换通道 第几次转换 采样时间
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_84Cycles);	
	ADC_ITConfig(ADC1,ADC_IT_EOC,ENABLE);	
	ADC_Cmd(ADC1,ENABLE);

}

void ADC_MQ2_Trans(void)
{	
	u16 adc_value = 0;
	u8 i = 0;	
	for(i = 0; i < 50; i++)
	{ 
		//开始转换
		ADC_SoftwareStartConv(ADC1);	
		//转换是否结束
		while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) != SET);
		adc_value = adc_value + ADC_GetConversionValue(ADC1);//读ADC中的值
	}
	
	//(adc_value / 50);//取样50次的平均值	
	printf("烟雾电压为：%f\r\n",5.0/4096*(adc_value / 50));	//实际电压值	
	printf("烟雾百分比：%.2f\r\n",(adc_value / 50) * 99 / 4096.0);//把AD值转换成百分比0~99
}

void MQ2_OPEN(void)
{

	//u8 buf[20];
	ADC_MQ2_Trans();
	
	//wifi发送
//	sprintf((char* )buf,"%.2f\r\n",ad * 99 / 4096.0);
//	delay_ms(1000);
//	UART3_Send_Str(buf);
//	memset(buf,'\0',sizeof(buf));
	
}






