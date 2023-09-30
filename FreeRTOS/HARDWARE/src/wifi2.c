#include "wifi2.h"
#include "main.h"

//�����ַ���
void UART3_Send_Str(u8 *str)
{
	while(*str != '\0')
	{
		while(!USART_GetFlagStatus(USART3, USART_FLAG_TXE));
		USART_SendData(USART3,*str);
		str++;
		
	}
}



/************************************ESP8266**************************************/
//�������ܣ�����ָ��ATָ���ESP8266
u8 ESP8266_Send_ATcmd(u8 *cmd, u8 *respond)
{
	
	u16 time = 0;
	
	UART3_Send_Str(cmd);
	delay_ms(50);
	
	while(1)
	{

		while(!uart2_flag)//�ȴ��������
		{
			
			delay_ms(5);
			if(++time>=500) return 1;//��ʱ
		}
		uart2_flag = 0;//�����־
		if(NULL!=strstr((const char*)uart2_revbuf,(const char*)respond))return 0;//ָ��ͳɹ�
	}
}

//ESP8266��������
u8 ESP8266_Connect_WIFI(u8 *ssid, u8 *pwd)
{
	u16 time = 0;
	u8 buf[100] = {0};
	
	//MCU����AT+CWQAP ESP8266����OK
	ESP8266_Send_ATcmd((u8 *)"AT+CWQAP\r\n",(u8 *)"OK");
	//AT+CWJAP_DEF="�ȵ���","����"
	strcpy((char *)buf,"AT+CWJAP=");
	strcat((char *)buf,"\"");
	strcat((char *)buf,(const char *)ssid);
	strcat((char *)buf,"\",\"");
	strcat((char *)buf,(const char *)pwd);
	strcat((char *)buf,"\"\r\n");
	
	UART3_Send_Str(buf);
printf("�ȵ�������...");
	
	while(1)
	{
		while(!uart2_flag)//�ȴ�������ɱ�־
		{
			
			delay_ms(50);
			if(++time>=500) return 1;//��ʱ
			
		}
		uart2_flag = 0;
		if(NULL!=strstr((const char *)uart2_revbuf,(const char *)"OK"))
		{
			printf("WIFI���ӳɹ�");
			return 0;
		}
	}
}

//�������ܣ�ESP8266���ӷ�����
u8 ESP8266_Connect_Server(u8 *tppe, u8 *ip, u32 port)
{
	u16 time = 0;
	//AT+CIPSTART="TCP","192.168.xx.xx",xx
	u8 buf[100];
	sprintf((char* )buf,"AT+CIPSTART=\"%s\",\"%s\",%d\r\n",tppe,ip,port);
	
	UART3_Send_Str(buf);
printf("������������...");
	
	while(1)
	{
		while(!uart2_flag)//�ȴ�������ɱ�־
		{
			
			delay_ms(50);
			if(++time>=500) return 1;//��ʱ
			
		}
		uart2_flag = 0;
		if(NULL!=strstr((const char *)uart2_revbuf,(const char *)"OK"))
		{
			printf("���������ӳɹ�");
			return 0;
		}
	}
}

//�˳�͸��
void Exit_Pass_Through_Mode(void)
{
	//+++
	UART3_Send_Str((u8 *)"+++");

	printf("�ر���TCP�������ķ���...");
	
}

//�������ܣ��ָ��������ã��������б�����flash�Ĳ������ָ�Ĭ�ϲ������豸����
//����˵����
//����ֵ��
//ע�����
//ʱ�䣺2023/03/15
//���ߣ�CAI
u8 ESP8266_Restore(void)
{
	u16 time = 0;
	//AT+RESTORE
	UART3_Send_Str((u8 *)"AT+RESTORE\r\n");
	printf("�ָ���������...");	
	while(1)
	{
		while(!uart2_flag)//�ȴ�������ɱ�־
		{
			
			delay_ms(50);
			if(++time>=500) return 1;//��ʱ
			
		}
		uart2_flag = 0;
		if(NULL != strstr((const char *)uart2_revbuf,(const char *)"ready"))
		{
			printf("�ָ��������ɹ�");	
			return 0;
		}
	}
	
}

//�������ܣ�ESP8266��ʼ��
//����˵������
//����ֵ����
//ע�������
//ʱ�䣺2023/03/15
//���ߣ�CAI
u8 ESP8266_HTTP_Init(u8 *ssid, u8 *pwd, u8 *tppe, u8 *ip, u32 port)
{
	u8 ret;

	//�˳�͸��
	if(ESP8266_Send_ATcmd((u8 *)"AT\r\n",(u8*)"OK")!=0)
	{
		Exit_Pass_Through_Mode( );//�˳�͸��
	}
	delay_ms(1000);
	
	ESP8266_Send_ATcmd((u8 *)"AT+RST\r\n",(u8*)"OK");
	delay_ms(1000);
	
	
	//MCU����AT+CWMODE_DEF=1 ESP8266����OK
	ret = ESP8266_Send_ATcmd((u8 *)"AT+CWMODE=3\r\n",(u8 *)"OK");//����WiFiģ�鹤��ģʽΪ��STAģʽ���������ñ�����flash
	if(ret)
	{
		printf("CWMODE error\r\n");
		return 3;
	}
	printf("���ÿͻ���ģʽ�ɹ�\r\n");
	delay_ms(500);
	

		//����WIFI
	Connect_Wifi_TCP((u8 *)ssid,(u8 *) pwd,(u8 *) tppe, (u8 *)ip,port);
	printf("ESP8266 HTTP Set Success\r\n");
	
		//AT+CIPMODE=1 ����OK
		ret = ESP8266_Send_ATcmd((u8 *)"AT+CIPSEND\r\n",(u8 *)"OK");//����͸��
	if(ret)
	{
		printf("AT+CIPSEND error\r\n");
		return 4;
	}
	
			printf("��������ָ��ִ�гɹ�\r\n");
	
	return 0;
	
	
	
	
	
	
	
	
	
	
	
	
	
}

//void esp32_test(void)
//{
//	//�˳�͸��ģʽ
//	Exit_Pass_Through_Mode();
//	
//	//����ATָ��
//	UART2_Send_Str((u8 *)"AT");
//	ESP8266_Send_ATcmd((u8 *)"AT+CWLAP",(u8*)"OK");
//	LCD_dis(0,120,RED,(u8*)uart2_revbuf,24,0,WHITE);
//	//���ÿͻ���ģʽ
//	UART2_Send_Str((u8 *)"AT+CWMODE=1");
//	
//	//�Ͽ���AP������
//	UART2_Send_Str((u8 *)"AT+CWQAP");
//	
//	//�Ͽ���TCP������������
//	UART2_Send_Str((u8 *)"AT+AIPCLOSE");
//	
//	//��������
//	ESP8266_Connect_WIFI((u8 *)"6S Pro",(u8 *)"123456789");
//	
//	//���ӷ�����
//	ESP8266_Connect_Server((u8 *)"TCP",(u8*)"192.168.75.58",(u8*)"(u8*)8888");
//	
//	//����͸��
//	UART2_Send_Str((u8*)"AT+CIPMODE=1");
//	
//	//��͸��
//	UART2_Send_Str((u8*)"AT+CIPSEND");
//	
//}


//����WIFI��TCP
u8 Connect_Wifi_TCP(u8 *ssid, u8 *pwd, u8 *tppe, u8 *ip, u32 port)
{

	//����AP
	ESP8266_Connect_WIFI((u8 *)ssid,(u8 *)pwd);
	
	delay_ms(500);
	
	//����TCP������
	if(!ESP8266_Connect_Server((u8 *)tppe,(u8*)ip,port))
	{
		printf("����TCP�ɹ�\r\n");
		delay_ms(2000);
		if(!ESP8266_Send_ATcmd((u8 *)"AT+CIPMODE=1\r\n",(u8 *)"OK"))
		{
				printf("����͸��ģʽ�ɹ�\r\n");
	
			return 0;
		}
		else 
		{
			printf("����͸��ģʽʧ��\r\n");
			//printf("��������ָ��ִ��ʧ��\r\n");
			delay_ms(500);
			return 2;
		}
		
	}
	
	return 3;
}

u8 ESP32_Query_Version(void)
{
	int ret;
	u8 temp[100] = {0};
	//MCU����AT+GMR WIFI����OK

	ret = ESP8266_Send_ATcmd((u8 *)"AT+GMR\r\n",(u8 *)"OK");//��ѯ�汾��Ϣ
	if(ret)
	{
		printf("AT+GMR error\r\n");
		return ret;
	}
	sprintf((char*)temp, "�汾��Ϣ:%s", uart2_revbuf);
	memset(uart2_revbuf, 0, sizeof(uart2_revbuf));
	delay_ms(20000);
	return ret;
}





