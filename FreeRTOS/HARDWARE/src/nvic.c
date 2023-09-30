#include "main.h"                  // Device header

u8 uart1_rxbuff[1024] = {0};
/***********************************************
*������    :USART1_IRQHandler
*��������  :����1�жϷ�����
*��������  :��
*��������ֵ:��
*��������  :
						�ֿ���¼��ַ��2�ſ��0��������0��ҳ��0���ֽڿ�ʼ��0x020000
						
************************************************/
u8 rx_flag = 0;
//u8 uart2_revbuf[1024]={0};
//u8 uart2_flag = 0;

void USART1_IRQHandler(void)
{

	static u16 len = 0;
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE))
	{
		//���Ĵ������жϱ�־
		uart1_rxbuff[len++] = USART_ReceiveData(USART1);
		//	printf("3�ж���Ӧ");
	}

	if(USART_GetITStatus(USART1, USART_IT_IDLE))
	{
		//����жϱ�־λ
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
//		//���Ĵ������жϱ�־
//		uart2_revbuf[len++] = USART3->DR;
//		//	printf("3�ж���Ӧ");
//	}

//	if(USART_GetITStatus(USART3, USART_IT_IDLE))
//	{
//		//����жϱ�־λ
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









