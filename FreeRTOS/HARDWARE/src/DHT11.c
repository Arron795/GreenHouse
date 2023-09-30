#include "DHT11.h"
#include "semphr.h"
//开漏模式即可输出又可输入
//开漏模式，拉高电平 自动变成输入模式
//端口 PC8 5v 
void DTH11_PIN_Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 ;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	//zGPIO_SetBits(GPIOC, GPIO_Pin_8);
	
	//data线为输出模式
	
	//越过1秒不稳定时间
	delay_ms(1000);

	//先拉高
	GPIO_SetBits(GPIOC, GPIO_Pin_8);
	
}
/*
函数名称：DHT11_start
函数参数: void
函数返回值: void
函数描述: //启动信号
*/
void DHT11_start(void)
{
	
	//发送起始信号
	GPIO_ResetBits(GPIOC, GPIO_Pin_8);
	//拉低20毫秒表示开始信号
	  vTaskDelay(20);
	
	//设置为输入，开漏模式，拉高电平 自动变成输入模式
	GPIO_SetBits(GPIOC, GPIO_Pin_8);	
	//DHT11_READ;
	
}

/*
函数名称：DHT11_recask
函数参数: void
函数返回值: u8  返回1失败，0表示成功
函数描述: //检测应答
*/

u8 DHT11_recask(void)
{
	u8 cnt = 0;
	//等待高电平变低电平，产生响应信号
	uint32_t timeout = xTaskGetTickCount() + pdMS_TO_TICKS(500); // 50ms超时时间
	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)==1)
	{
		 if (xTaskGetTickCount() >= timeout)
		{
        // 超时退出
			
        return 1;
		}		
	}
	timeout = xTaskGetTickCount() + pdMS_TO_TICKS(800); // 80ms超时时间
	//等待低电平变高电平，83us阶段
	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)==0)
	{
	
		 if (xTaskGetTickCount() >= timeout)
        {
            // 超时退出
          return 1;
        }
	}
	 timeout = xTaskGetTickCount() + pdMS_TO_TICKS(600); // 60us超时时间
	//等待高电平变低电平 ,87us
	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)==1)
	{
		  if (xTaskGetTickCount() >= timeout)
        {
            // 超时退出
          return 1;
        }
	}
	
	return 0; //相应成功
	
		
	
}


/*
函数名称：DHT11_recdata
函数参数: void
函数返回值: u8  返回数据
函数描述: //接收数据
*/


u8 DHT11_recdata(void)
{
	u8 i = 0;
	u8 data  = 0;
	for(i=0 ; i < 8;i++)
	{	
		//等待低电平变高电平，越过54us
	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)==0);
		delay_us(45);
		data = data <<1;//空出最低位
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)==1){
			data  |= 0x01;
		}	
	//等待高电平变低电平
	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)==1);
	}

	return data;
	
}

/*
函数名称：DHT11_data
函数参数:  float *shidu  , float *wendu
函数返回值: u8 data 数据
函数描述: //整合数据
*/


u8 DHT11_data(float* shidu  , float* wendu)
{
	u8 buf[100] = {0};
	u8 byte[5] = {0};
	//开始信号
	DHT11_start();
	//判断应答
	if(DHT11_recask()==1)
	{
		//printf("响应失败");
		return 1;
	}
//	printf("应答成功");
	
	byte[0] = DHT11_recdata();//0湿度整数部分
	byte[1] = DHT11_recdata();//湿度小数部分 
	byte[2] = DHT11_recdata();//温度整数部分
	byte[3] = DHT11_recdata();//温度小数部分
	byte[4] = DHT11_recdata();//校验
	if(byte[4] == ((byte[0] + byte[1] + byte[2] + byte[3]) & 0xff))	//取低八位
	{
		//printf("数据正确");
		
		*shidu = (byte[0]/1.0+(byte[1]/10.0)) ;
		
		*wendu = (byte[2]/1.0+(byte[3]/10.0)) ;
		
	//printf("湿度为：%.2f\r\n",*shidu);	
	//printf("温度为：%.2f\r\n",*wendu);
	//发送给wifi
//	sprintf((char* )buf,"温度:  %.2f\r\n",*wendu);
//	UART3_Send_Str(buf);
//	memset(buf,'\0',sizeof(buf));
//	sprintf((char* )buf,"湿度:  %.2f\r\n",*shidu);
	sprintf((char *)buf,"Params(temp:%.2f;humi:%.2f;})\r\n",*wendu,*shidu);
	UART3_Send_Str(buf);
	memset(buf,'\0',sizeof(buf));
		
	}else
	{
		//printf("数据错误");
		return 1;
	}
	return 0;
	
}


u8 DHT11_OPEN(void)
{
	TickType_t xLastWakeTime;
	 const TickType_t xFrequency = 1000; // 1s读取一次
	xLastWakeTime = xTaskGetTickCount();
	float shidu;
	float wendu;
	u8 res = DHT11_data(&shidu,&wendu);		
	if(1 == res)
	{
		return 0;
	}
	else
	{
		return 1;
	}
	vTaskDelayUntil(&xLastWakeTime, xFrequency);	
}






