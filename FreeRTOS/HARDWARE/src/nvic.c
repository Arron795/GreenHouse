#include "main.h"                  // Device header

u8 uart1_rxbuff[1024] = {0};
/***********************************************
*函数名    :USART1_IRQHandler
*函数功能  :串口1中断服务函数
*函数参数  :无
*函数返回值:无
*函数描述  :
						字库烧录地址：2号块的0号扇区的0号页的0号字节开始：0x020000
						
************************************************/
u8 rx_flag = 0;
//u8 uart2_revbuf[1024]={0};
//u8 uart2_flag = 0;

void USART1_IRQHandler(void)
{

	static u16 len = 0;
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE))
	{
		//读寄存器清中断标志
		uart1_rxbuff[len++] = USART_ReceiveData(USART1);
		//	printf("3中断响应");
	}

	if(USART_GetITStatus(USART1, USART_IT_IDLE))
	{
		//清除中断标志位
		USART1->SR;
		USART1->DR;
		UART3_Send_Str(uart1_rxbuff);
		uart1_rxbuff[len] = '\0';
		printf("%s",uart1_rxbuff);
		
		rx_flag = 1;
		len = 0;
	}


}


//void USART3_IRQHandler(void)
//{
//	static u16 len = 0;
//	
//	if(USART_GetITStatus(USART3, USART_IT_RXNE))
//	{
//		//读寄存器清中断标志
//		uart2_revbuf[len++] = USART3->DR;
//		//	printf("3中断响应");
//	}

//	if(USART_GetITStatus(USART3, USART_IT_IDLE))
//	{
//		//清除中断标志位
//		USART3->SR;
//		USART3->DR;
//		
//		uart2_revbuf[len] = '\0';
//		printf("%s",uart2_revbuf);
//		
//		uart2_flag = 1;
//		len = 0;
//	}
//}









