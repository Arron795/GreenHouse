#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "semphr.h"

/*
	PA9  PA10 	作为串口1 的接收发送引脚
	PB10  PB11 	作为串口3 的接收发送引脚
	PC8  		作为温湿度DHT11 的输入输出端    电压 5v
	PA4         作为土壤湿度传感器 YL 的模拟输入  电压 3.3v
	PA5 PA6     作为超声波HC-SR04 的输入输出端    电压5v
	PA7			 作为电机的pwm输出口				电压 3.3v
	PA0			 作为烟雾传感器mq2的模拟输入口   电压5v
	
	
*/

//任务优先级
#define START_TASK_PRIO		1
//任务堆栈大小	
#define START_STK_SIZE 		128  
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void start_task(void *pvParameters);

//温湿度
//任务优先级
#define DHT11_TASK_PRIO		7
//任务堆栈大小	
#define DHT11_STK_SIZE 		256 
//任务句柄
TaskHandle_t DHT11_Task_Handler;
//任务函数
void DHT11_task(void *pvParameters);

//土壤湿度
//任务优先级
#define YL_TASK_PRIO		6 //3
//任务堆栈大小	
#define YL_STK_SIZE 		128 
//任务句柄
TaskHandle_t YL_Task_Handler;
//任务函数
void YL_task(void *pvParameters);



//超声波
//任务优先级
#define HCSR04_TASK_PRIO		6
//任务堆栈大小	
#define HCSR04_STK_SIZE 		128
//任务句柄
TaskHandle_t HCSR04_Task_Handler;
//任务函数
void HCSR04_task(void *pvParameters);


//光照
//任务优先级
#define LSENS_TASK_PRIO		6
//任务堆栈大小	
#define LSENS_STK_SIZE 		128
//任务句柄
TaskHandle_t LSENS_Task_Handler;
//任务函数
void LSENS_task(void *pvParameters);

//人体红外
//任务优先级
#define HCSR501_TASK_PRIO		6 //5
//任务堆栈大小	
#define HCSR501_STK_SIZE 		128 
//任务句柄
TaskHandle_t HCSR501_Task_Handler;
//任务函数
void HCSR501_task(void *pvParameters);

//关闭任务
//任务优先级
#define CLOSE_TASK_PRIO		 8
//任务堆栈大小	
#define CLOSE_STK_SIZE 		128 
//任务句柄
TaskHandle_t CLOSE_Task_Handler;
//任务函数
void CLOSE_task(void *pvParameters);


//二值信号量句柄
// SemaphoreHandle_t BinarySemaphore;	//二值信号量句柄
SemaphoreHandle_t MutexSemaphore01;	//互斥信号量
SemaphoreHandle_t MutexSemaphore02;	//互斥信号量
SemaphoreHandle_t MutexSemaphore03;	//互斥信号量
SemaphoreHandle_t MutexSemaphore04;	//互斥信号量
SemaphoreHandle_t MutexSemaphore05;	//互斥信号量
u8 i =1;
int main(void)
{ 
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4
	delay_init(168);					//初始化延时函数
	uart_init(115200);     				//初始化串口
	usart3_init(115200); 	//串口3初始化
	LED_Init();		        			//初始化LED端口
	//电机模块初始化
	TIM14_PWM_Init(1000-1, 84000-1);
	TIM_SetCompare1(TIM14,0);	//修改比较值，修改占空比
	//RGB模块初始化
	GPIO_Configuration();
	TIM4_Configuration();
	PWM_Configuration();

	//WIFI模块初始化
	i=ESP8266_HTTP_Init((u8 *)"ARrons",(u8 *) "76543201",(u8 *) "TCP", (u8 *)"192.168.137.134",8888);
	//i=ESP8266_HTTP_Init((u8 *)"ARrons",(u8 *) "76543201",(u8 *) "TCP", (u8 *)"192.168.137.1",8888);
	//i=ESP8266_HTTP_Init((u8 *)"60",(u8 *) "12345678910",(u8 *) "TCP", (u8 *)"192.168.119.170",8888);
	//创建开始任务
    xTaskCreate((TaskFunction_t )start_task,            //任务函数
                (const char*    )"start_task",          //任务名称
                (uint16_t       )START_STK_SIZE,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )START_TASK_PRIO,       //任务优先级
                (TaskHandle_t*  )&StartTask_Handler);   //任务句柄              
    vTaskStartScheduler();          //开启任务调度
}

//开始任务任务函数
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区
	//BinarySemaphore=xSemaphoreCreateBinary();	
	//创建互斥信号量
	MutexSemaphore01=xSemaphoreCreateMutex();
	MutexSemaphore02=xSemaphoreCreateMutex();
	MutexSemaphore03=xSemaphoreCreateMutex();
	MutexSemaphore04=xSemaphoreCreateMutex();
	MutexSemaphore05=xSemaphoreCreateMutex();
    //创建温湿度AHT11任务
    xTaskCreate((TaskFunction_t )DHT11_task,             
                (const char*    )"DHT11_task",           
                (uint16_t       )DHT11_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )DHT11_TASK_PRIO,        
                (TaskHandle_t*  )&DHT11_Task_Handler);   
    //创建土壤湿度YL任务
    xTaskCreate((TaskFunction_t )YL_task,     
                (const char*    )"YL_task",   
                (uint16_t       )YL_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )YL_TASK_PRIO,
                (TaskHandle_t*  )&YL_Task_Handler); 
	 //创建超声波HC-SR04任务
    xTaskCreate((TaskFunction_t )HCSR04_task,     
                (const char*    )"HCSR04_task",   
                (uint16_t       )HCSR04_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )HCSR04_TASK_PRIO,
                (TaskHandle_t*  )&HCSR04_Task_Handler); 

				
	 //创建光照强度任务
    xTaskCreate((TaskFunction_t )LSENS_task,     
                (const char*    )"LSENS_task",   
                (uint16_t       )LSENS_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )LSENS_TASK_PRIO,
                (TaskHandle_t*  )&LSENS_Task_Handler); 
	
	 //创建人体红外任务
    xTaskCreate((TaskFunction_t )HCSR501_task,     
                (const char*    )"HCSR501_task",   
                (uint16_t       )HCSR501_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )HCSR501_TASK_PRIO,
                (TaskHandle_t*  )&HCSR501_Task_Handler); 
				
	 //创建人体红外任务
    xTaskCreate((TaskFunction_t )CLOSE_task,     
                (const char*    )"CLOSE_task",   
                (uint16_t       )CLOSE_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )CLOSE_TASK_PRIO,
                (TaskHandle_t*  )&CLOSE_Task_Handler); 

				
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}

//温湿度任务函数
void DHT11_task(void *pvParameters)
{	
	DTH11_PIN_Init();
	while(1)
	{

		//printf("DHT11_task\r\n");
		uint32_t timeout = xTaskGetTickCount() + pdMS_TO_TICKS(500); // 50ms超时时间
		xSemaphoreTake(MutexSemaphore01,portMAX_DELAY);
		// while(xSemaphoreTake(MutexSemaphore01,portMAX_DELAY)==pdFALSE)//获取互斥信号量
		// {
		// 	if (xTaskGetTickCount() >= timeout)
		// 	{
       	// 	 // 超时退出			
        		
		// 	}
			
		// }
		DHT11_OPEN();
		//printf("	DHT11_task_return\r\n");
		//timeout = xTaskGetTickCount() + pdMS_TO_TICKS(500);
		xSemaphoreGive(MutexSemaphore01);
		// while(xSemaphoreGive(MutexSemaphore01)==pdFALSE)//释放互斥信号量
		// {
		// 	if (xTaskGetTickCount() >= timeout)
		// 	{
       	// 	 // 超时退出			
      
		// 	}
		 //}
       vTaskDelay(500);                         
	}
}


//超声波任务函数
void HCSR04_task(void *pvParameters)
{
	float length;
	while(1)
	{
		
		xSemaphoreTake(MutexSemaphore02,portMAX_DELAY);	//获取互斥信号量
		length = HCSR04_OPEN();	
		//wifi发送	
		u8 buf[100] = {0};
		//sprintf((char* )buf,"HCSR04:  %fcm\r\n",length);
		sprintf((char *)buf,"HCSR04(hcsr04:%fcm;})\r\n",length);
		//delay_ms(50);
		UART3_Send_Str(buf);
		memset(buf,'\0',sizeof(buf));
		xSemaphoreGive(MutexSemaphore02);					//释放互斥信号量		
		vTaskDelay(1000);           
	}
}


//土壤湿度任务函数
void YL_task(void *pvParameters)
{
	while(1)
	{
//		xSemaphoreTake(MutexSemaphore03,portMAX_DELAY);	//获取互斥信号量
		u8 soil_humidity = 0;
		soil_humidity = YL_OPEN();
		u8 buf[100] = {0};
		sprintf((char* )buf,"土壤湿度为:  %.2f%%\r\n",(float)soil_humidity);
		sprintf((char *)buf,"HUMSOIL(humSoil:%.2f%%;})\r\n",(float)soil_humidity);
		UART3_Send_Str(buf);
		memset(buf,'\0',sizeof(buf));
//		xSemaphoreGive(MutexSemaphore03);					//释放互斥信号量		
       vTaskDelay(1000);           
	}
}


//光照强度任务函数
void LSENS_task(void *pvParameters)
{
	while(1)
	{
//		xSemaphoreTake(MutexSemaphore04,portMAX_DELAY);	//获取互斥信号量
		Lsens_OPEN();						
		vTaskDelay(1000);    
//		xSemaphoreGive(MutexSemaphore04);					//释放互斥信号量		
	}
}

//人体红外任务函数
void HCSR501_task(void *pvParameters)
{
	while(1)
	{		
//		xSemaphoreTake(MutexSemaphore05,portMAX_DELAY);	//获取互斥信号量
		HC_SR501_OPEN();	
//		xSemaphoreGive(MutexSemaphore05);					//释放互斥信号量			
		vTaskDelay(1000);           
	}
}


//关闭任务函数
void CLOSE_task(void *pvParameters)
{
	while(1)
	{
		vTaskSuspend(DHT11_Task_Handler);
		vTaskSuspend(YL_Task_Handler);
		vTaskSuspend(HCSR04_Task_Handler);
		vTaskSuspend(LSENS_Task_Handler);
		vTaskSuspend(HCSR501_Task_Handler);	
		vTaskDelete(CLOSE_Task_Handler); //删除开始任务				
	}
}





u8 uart2_revbuf[200]={0};
u8 uart2_flag = 0;

void USART3_IRQHandler(void)
{
	static u16 len = 0;
	
	if(USART_GetITStatus(USART3, USART_IT_RXNE))
	{
		//读寄存器清中断标志
		uart2_revbuf[len++] = USART3->DR;
	}
	if(i==0){
	if(NULL!=strstr((const char *)uart2_revbuf,(const char *)"c"))
	{
		Set_Motor(0);
	}
	else if(NULL!=strstr((const char *)uart2_revbuf,(const char *)"o"))
	{
		Set_Motor(200);
	}
	else if(NULL!=strstr((const char *)uart2_revbuf,(const char *)"1"))
	{
		Set_Motor(200);
	}
	else if(NULL!=strstr((const char *)uart2_revbuf,(const char *)"2"))
	{
		Set_Motor(600);
	}
	else if(NULL!=strstr((const char *)uart2_revbuf,(const char *)"3"))
	{
		Set_Motor(998);
	}
	else if(NULL!=strstr((const char *)uart2_revbuf,(const char *)"9"))//关闭超声波
	{
		vTaskSuspend(HCSR04_Task_Handler);
		//printf("接收成功");

	}
	else	if(NULL!=strstr((const char *)uart2_revbuf,(const char *)"0"))//打开超声波
	{
		
		//printf("接收成功");
		vTaskResume(HCSR04_Task_Handler);
	}
	else if(NULL!=strstr((const char *)uart2_revbuf,(const char *)"d")) //关闭温湿度
	{
		vTaskSuspend(DHT11_Task_Handler);
		//printf("接收成功");

	}
	else	if(NULL!=strstr((const char *)uart2_revbuf,(const char *)"f"))//打开温湿度
	{
		
		//printf("接收成功");
		vTaskResume(DHT11_Task_Handler);
	}
	else if(NULL!=strstr((const char *)uart2_revbuf,(const char *)"y"))//关闭土壤湿度
	{
		vTaskSuspend(YL_Task_Handler);
		//printf("接收成功");

	}
	else if(NULL!=strstr((const char *)uart2_revbuf,(const char *)"u"))//打开土壤湿度
	{
		
		//printf("接收成功");
		vTaskResume(YL_Task_Handler);
	}
	else if(NULL!=strstr((const char *)uart2_revbuf,(const char *)"l")) //关闭光照
	{
		vTaskSuspend(LSENS_Task_Handler);
		//printf("接收成功");

	}
	else if(NULL!=strstr((const char *)uart2_revbuf,(const char *)"k"))//打开光照
	{
		
		//printf("接收成功");
		vTaskResume(LSENS_Task_Handler);
	}
	else if(NULL!=strstr((const char *)uart2_revbuf,(const char *)"h"))//关闭人体红外
	{
		vTaskSuspend(HCSR501_Task_Handler);
		//printf("接收成功");

	}
	else if(NULL!=strstr((const char *)uart2_revbuf,(const char *)"j"))//打开人体红外
	{
		
		//printf("接收成功");
		vTaskResume(HCSR501_Task_Handler);
	}
	else if(NULL!=strstr((const char *)uart2_revbuf,(const char *)"z"))
	{
		Set_Motor(0);
		vTaskSuspend(DHT11_Task_Handler);
		vTaskSuspend(YL_Task_Handler);
		vTaskSuspend(HCSR04_Task_Handler);
		vTaskSuspend(LSENS_Task_Handler);
		vTaskSuspend(HCSR501_Task_Handler);
		//vTaskSuspendAll();
		
		//printf("接收成功");

	}
	else if(NULL!=strstr((const char *)uart2_revbuf,(const char *)"o"))
	{
		Set_Motor(400);
		vTaskResume(DHT11_Task_Handler);
		vTaskResume(YL_Task_Handler);
		vTaskResume(HCSR04_Task_Handler);
		vTaskResume(LSENS_Task_Handler);
		vTaskResume(HCSR501_Task_Handler);
		//xTaskResumeAll();
		//printf("接收成功");

	}
	}
	
	
	if(USART_GetITStatus(USART3, USART_IT_IDLE))
	{
		//清除中断标志位
		USART3->SR;
		USART3->DR;
		
		uart2_revbuf[len] = '\0';
		printf("%s",uart2_revbuf);
		
		uart2_flag = 1;
		len = 0;
	}
}



