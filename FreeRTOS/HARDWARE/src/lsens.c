#include "lsens.h"
#include "delay.h"

//?????ADC
//????????????????????														   
void  Adc3_Init(void)
{    
 
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE); //???ADC3???

  
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3,ENABLE);	  //ADC3??��
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3,DISABLE);	//??��????	 
 
 
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//??????
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//??????????????????5?????
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMA???
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//????4?????ADCCLK=PCLK2/4=84/4=21Mhz,ADC?????��??????36Mhz 
  ADC_CommonInit(&ADC_CommonInitStructure);//?????
	
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12��??
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;//???????	
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//??????????
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//?????????????????????
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//?????	
  ADC_InitStructure.ADC_NbrOfConversion = 1;//1???????????????? ?????????????????1 
  ADC_Init(ADC3, &ADC_InitStructure);//ADC?????
	
 
	ADC_Cmd(ADC3, ENABLE);//????AD?????	 
}				  
//???ADC?
//ch:???? 0~16 ADC_Channel_0~ADC_Channel_16
//?????:??????
u16 Get_Adc3(u8 ch)   
{
	  	//???????ADC??????????????????��????????
	ADC_RegularChannelConfig(ADC3, ch, 1, ADC_SampleTime_480Cycles );	//ADC3,ADC???,480??????,???????????????????			    
  
	ADC_SoftwareStartConv(ADC3);		//????????ADC3?????????????????	
	 
	while(!ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC ));//??????????

	return ADC_GetConversionValue(ADC3);	//??????????ADC3?????????????
}
 

//???????????????
void Lsens_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//???GPIOF???
	
  //??????ADC3???7IO??
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//PF7 ???5
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//???????
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//??????????
  GPIO_Init(GPIOF, &GPIO_InitStructure);//?????  
 
	Adc3_Init();//?????ADC3
}
//???Light Sens???
//0~100:0,??;100,???? 
void Lsens_OPEN(void)
{
	Lsens_Init(); 			//???????????????
	u32 temp_val=0;
	u8 t;
	u8 light;
	for(t=0;t<LSENS_READ_TIMES;t++)
	{
		temp_val+=Get_Adc3(ADC_Channel_5);	//???ADC?,???5
		delay_ms(5);
	}
	temp_val/=LSENS_READ_TIMES;//??????? 
	if(temp_val>4000)temp_val=4000;
	light =  (u16)(100-(temp_val/40));
	//printf("light:%d\r\n",light);
	u8 buf[100];
	//sprintf((char* )buf,"��ǿ: %d\r\n",light);
	sprintf((char *)buf,"LIGHT(light:%d;})\r\n",light);
	//delay_ms(50);
	UART3_Send_Str(buf);
	memset(buf,'\0',sizeof(buf));
}











