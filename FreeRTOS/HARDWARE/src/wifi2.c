#include "wifi2.h"
#include "main.h"

//发送字符串
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
//函数功能：发送指定AT指令给ESP8266
u8 ESP8266_Send_ATcmd(u8 *cmd, u8 *respond)
{
	
	u16 time = 0;
	
	UART3_Send_Str(cmd);
	delay_ms(50);
	
	while(1)
	{

		while(!uart2_flag)//等待传输完成
		{
			
			delay_ms(5);
			if(++time>=500) return 1;//超时
		}
		uart2_flag = 0;//清除标志
		if(NULL!=strstr((const char*)uart2_revbuf,(const char*)respond))return 0;//指令发送成功
	}
}

//ESP8266连接网络
u8 ESP8266_Connect_WIFI(u8 *ssid, u8 *pwd)
{
	u16 time = 0;
	u8 buf[100] = {0};
	
	//MCU发送AT+CWQAP ESP8266返回OK
	ESP8266_Send_ATcmd((u8 *)"AT+CWQAP\r\n",(u8 *)"OK");
	//AT+CWJAP_DEF="热点名","密码"
	strcpy((char *)buf,"AT+CWJAP=");
	strcat((char *)buf,"\"");
	strcat((char *)buf,(const char *)ssid);
	strcat((char *)buf,"\",\"");
	strcat((char *)buf,(const char *)pwd);
	strcat((char *)buf,"\"\r\n");
	
	UART3_Send_Str(buf);
printf("热点连接中...");
	
	while(1)
	{
		while(!uart2_flag)//等待传输完成标志
		{
			
			delay_ms(50);
			if(++time>=500) return 1;//超时
			
		}
		uart2_flag = 0;
		if(NULL!=strstr((const char *)uart2_revbuf,(const char *)"OK"))
		{
			printf("WIFI连接成功");
			return 0;
		}
	}
}

//函数功能：ESP8266连接服务器
u8 ESP8266_Connect_Server(u8 *tppe, u8 *ip, u32 port)
{
	u16 time = 0;
	//AT+CIPSTART="TCP","192.168.xx.xx",xx
	u8 buf[100];
	sprintf((char* )buf,"AT+CIPSTART=\"%s\",\"%s\",%d\r\n",tppe,ip,port);
	
	UART3_Send_Str(buf);
printf("服务器连接中...");
	
	while(1)
	{
		while(!uart2_flag)//等待传输完成标志
		{
			
			delay_ms(50);
			if(++time>=500) return 1;//超时
			
		}
		uart2_flag = 0;
		if(NULL!=strstr((const char *)uart2_revbuf,(const char *)"OK"))
		{
			printf("服务器连接成功");
			return 0;
		}
	}
}

//退出透传
void Exit_Pass_Through_Mode(void)
{
	//+++
	UART3_Send_Str((u8 *)"+++");

	printf("关闭在TCP服务器的发言...");
	
}

//函数功能：恢复出厂设置，擦除所有保存在flash的参数，恢复默认参数，设备重启
//参数说明：
//返回值：
//注意事项：
//时间：2023/03/15
//作者：CAI
u8 ESP8266_Restore(void)
{
	u16 time = 0;
	//AT+RESTORE
	UART3_Send_Str((u8 *)"AT+RESTORE\r\n");
	printf("恢复出厂设置...");	
	while(1)
	{
		while(!uart2_flag)//等待传输完成标志
		{
			
			delay_ms(50);
			if(++time>=500) return 1;//超时
			
		}
		uart2_flag = 0;
		if(NULL != strstr((const char *)uart2_revbuf,(const char *)"ready"))
		{
			printf("恢复出厂化成功");	
			return 0;
		}
	}
	
}

//函数功能：ESP8266初始化
//参数说明：无
//返回值：无
//注意事项：无
//时间：2023/03/15
//作者：CAI
u8 ESP8266_HTTP_Init(u8 *ssid, u8 *pwd, u8 *tppe, u8 *ip, u32 port)
{
	u8 ret;

	//退出透传
	if(ESP8266_Send_ATcmd((u8 *)"AT\r\n",(u8*)"OK")!=0)
	{
		Exit_Pass_Through_Mode( );//退出透传
	}
	delay_ms(1000);
	
	ESP8266_Send_ATcmd((u8 *)"AT+RST\r\n",(u8*)"OK");
	delay_ms(1000);
	
	
	//MCU发送AT+CWMODE_DEF=1 ESP8266返回OK
	ret = ESP8266_Send_ATcmd((u8 *)"AT+CWMODE=3\r\n",(u8 *)"OK");//配置WiFi模组工作模式为单STA模式，并把配置保存在flash
	if(ret)
	{
		printf("CWMODE error\r\n");
		return 3;
	}
	printf("设置客户端模式成功\r\n");
	delay_ms(500);
	

		//连接WIFI
	Connect_Wifi_TCP((u8 *)ssid,(u8 *) pwd,(u8 *) tppe, (u8 *)ip,port);
	printf("ESP8266 HTTP Set Success\r\n");
	
		//AT+CIPMODE=1 返回OK
		ret = ESP8266_Send_ATcmd((u8 *)"AT+CIPSEND\r\n",(u8 *)"OK");//设置透传
	if(ret)
	{
		printf("AT+CIPSEND error\r\n");
		return 4;
	}
	
			printf("发送数据指令执行成功\r\n");
	
	return 0;
	
	
	
	
	
	
	
	
	
	
	
	
	
}

//void esp32_test(void)
//{
//	//退出透传模式
//	Exit_Pass_Through_Mode();
//	
//	//测试AT指令
//	UART2_Send_Str((u8 *)"AT");
//	ESP8266_Send_ATcmd((u8 *)"AT+CWLAP",(u8*)"OK");
//	LCD_dis(0,120,RED,(u8*)uart2_revbuf,24,0,WHITE);
//	//设置客户端模式
//	UART2_Send_Str((u8 *)"AT+CWMODE=1");
//	
//	//断开与AP的连接
//	UART2_Send_Str((u8 *)"AT+CWQAP");
//	
//	//断开与TCP服务器的连接
//	UART2_Send_Str((u8 *)"AT+AIPCLOSE");
//	
//	//连接网络
//	ESP8266_Connect_WIFI((u8 *)"6S Pro",(u8 *)"123456789");
//	
//	//连接服务器
//	ESP8266_Connect_Server((u8 *)"TCP",(u8*)"192.168.75.58",(u8*)"(u8*)8888");
//	
//	//设置透传
//	UART2_Send_Str((u8*)"AT+CIPMODE=1");
//	
//	//打开透传
//	UART2_Send_Str((u8*)"AT+CIPSEND");
//	
//}


//连接WIFI和TCP
u8 Connect_Wifi_TCP(u8 *ssid, u8 *pwd, u8 *tppe, u8 *ip, u32 port)
{

	//连接AP
	ESP8266_Connect_WIFI((u8 *)ssid,(u8 *)pwd);
	
	delay_ms(500);
	
	//连接TCP服务器
	if(!ESP8266_Connect_Server((u8 *)tppe,(u8*)ip,port))
	{
		printf("连接TCP成功\r\n");
		delay_ms(2000);
		if(!ESP8266_Send_ATcmd((u8 *)"AT+CIPMODE=1\r\n",(u8 *)"OK"))
		{
				printf("设置透传模式成功\r\n");
	
			return 0;
		}
		else 
		{
			printf("设置透传模式失败\r\n");
			//printf("发送数据指令执行失败\r\n");
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
	//MCU发送AT+GMR WIFI返回OK

	ret = ESP8266_Send_ATcmd((u8 *)"AT+GMR\r\n",(u8 *)"OK");//查询版本信息
	if(ret)
	{
		printf("AT+GMR error\r\n");
		return ret;
	}
	sprintf((char*)temp, "版本信息:%s", uart2_revbuf);
	memset(uart2_revbuf, 0, sizeof(uart2_revbuf));
	delay_ms(20000);
	return ret;
}





