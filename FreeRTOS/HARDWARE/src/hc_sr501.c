#include "hc_sr501.h"

void HC_SR501_Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = HC_SR501_PIN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;
	
	GPIO_Init(HC_SR501_PORT,&GPIO_InitStruct);
	
}

void HC_SR501_OPEN(void)
{
	HC_SR501_Init();
	
	if(HC_SR501_READ == 0)
	{
		//printf("无人体红外	\r\n");
		u8 buf[100] = {0};
		//sprintf((char* )buf,"humenRay:%s\r\n","yes");
		sprintf((char *)buf,"HUMENRAY(humenRay:%s;})\r\n","no!");
		//delay_ms(50);
		UART3_Send_Str(buf);
		memset(buf,'\0',sizeof(buf));		

	}
	else if(HC_SR501_READ == 1)
	{
		//printf("		有人体红外\r\n");
		u8 buf[100];
		//sprintf((char* )buf,"humenRay:  %s\r\n","no");
		sprintf((char *)buf,"HUMENRAY(humenRay:%s;})\r\n","yes");
		//delay_ms(50);
		UART3_Send_Str(buf);
		memset(buf,'\0',sizeof(buf));		

	}
}

