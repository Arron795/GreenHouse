#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "semphr.h"

/*
	PA9  PA10 	��Ϊ����1 �Ľ��շ�������
	PB10  PB11 	��Ϊ����3 �Ľ��շ�������
	PC8  		��Ϊ��ʪ��DHT11 �����������    ��ѹ 5v
	PA4         ��Ϊ����ʪ�ȴ����� YL ��ģ������  ��ѹ 3.3v
	PA5 PA6     ��Ϊ������HC-SR04 �����������    ��ѹ5v
	PA7			 ��Ϊ�����pwm�����				��ѹ 3.3v
	PA0			 ��Ϊ��������mq2��ģ�������   ��ѹ5v
	
	
*/

//�������ȼ�
#define START_TASK_PRIO		1
//�����ջ��С	
#define START_STK_SIZE 		128  
//������
TaskHandle_t StartTask_Handler;
//������
void start_task(void *pvParameters);

//��ʪ��
//�������ȼ�
#define DHT11_TASK_PRIO		7
//�����ջ��С	
#define DHT11_STK_SIZE 		256 
//������
TaskHandle_t DHT11_Task_Handler;
//������
void DHT11_task(void *pvParameters);

//����ʪ��
//�������ȼ�
#define YL_TASK_PRIO		6 //3
//�����ջ��С	
#define YL_STK_SIZE 		128 
//������
TaskHandle_t YL_Task_Handler;
//������
void YL_task(void *pvParameters);



//������
//�������ȼ�
#define HCSR04_TASK_PRIO		6
//�����ջ��С	
#define HCSR04_STK_SIZE 		128
//������
TaskHandle_t HCSR04_Task_Handler;
//������
void HCSR04_task(void *pvParameters);


//����
//�������ȼ�
#define LSENS_TASK_PRIO		6
//�����ջ��С	
#define LSENS_STK_SIZE 		128
//������
TaskHandle_t LSENS_Task_Handler;
//������
void LSENS_task(void *pvParameters);

//�������
//�������ȼ�
#define HCSR501_TASK_PRIO		6 //5
//�����ջ��С	
#define HCSR501_STK_SIZE 		128 
//������
TaskHandle_t HCSR501_Task_Handler;
//������
void HCSR501_task(void *pvParameters);

//�ر�����
//�������ȼ�
#define CLOSE_TASK_PRIO		 8
//�����ջ��С	
#define CLOSE_STK_SIZE 		128 
//������
TaskHandle_t CLOSE_Task_Handler;
//������
void CLOSE_task(void *pvParameters);


//��ֵ�ź������
// SemaphoreHandle_t BinarySemaphore;	//��ֵ�ź������
SemaphoreHandle_t MutexSemaphore01;	//�����ź���
SemaphoreHandle_t MutexSemaphore02;	//�����ź���
SemaphoreHandle_t MutexSemaphore03;	//�����ź���
SemaphoreHandle_t MutexSemaphore04;	//�����ź���
SemaphoreHandle_t MutexSemaphore05;	//�����ź���
u8 i =1;
int main(void)
{ 
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4
	delay_init(168);					//��ʼ����ʱ����
	uart_init(115200);     				//��ʼ������
	usart3_init(115200); 	//����3��ʼ��
	LED_Init();		        			//��ʼ��LED�˿�
	//���ģ���ʼ��
	TIM14_PWM_Init(1000-1, 84000-1);
	TIM_SetCompare1(TIM14,0);	//�޸ıȽ�ֵ���޸�ռ�ձ�
	//RGBģ���ʼ��
	GPIO_Configuration();
	TIM4_Configuration();
	PWM_Configuration();

	//WIFIģ���ʼ��
	i=ESP8266_HTTP_Init((u8 *)"ARrons",(u8 *) "76543201",(u8 *) "TCP", (u8 *)"192.168.137.134",8888);
	//i=ESP8266_HTTP_Init((u8 *)"ARrons",(u8 *) "76543201",(u8 *) "TCP", (u8 *)"192.168.137.1",8888);
	//i=ESP8266_HTTP_Init((u8 *)"60",(u8 *) "12345678910",(u8 *) "TCP", (u8 *)"192.168.119.170",8888);
	//������ʼ����
    xTaskCreate((TaskFunction_t )start_task,            //������
                (const char*    )"start_task",          //��������
                (uint16_t       )START_STK_SIZE,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
                (TaskHandle_t*  )&StartTask_Handler);   //������              
    vTaskStartScheduler();          //�����������
}

//��ʼ����������
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ���
	//BinarySemaphore=xSemaphoreCreateBinary();	
	//���������ź���
	MutexSemaphore01=xSemaphoreCreateMutex();
	MutexSemaphore02=xSemaphoreCreateMutex();
	MutexSemaphore03=xSemaphoreCreateMutex();
	MutexSemaphore04=xSemaphoreCreateMutex();
	MutexSemaphore05=xSemaphoreCreateMutex();
    //������ʪ��AHT11����
    xTaskCreate((TaskFunction_t )DHT11_task,             
                (const char*    )"DHT11_task",           
                (uint16_t       )DHT11_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )DHT11_TASK_PRIO,        
                (TaskHandle_t*  )&DHT11_Task_Handler);   
    //��������ʪ��YL����
    xTaskCreate((TaskFunction_t )YL_task,     
                (const char*    )"YL_task",   
                (uint16_t       )YL_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )YL_TASK_PRIO,
                (TaskHandle_t*  )&YL_Task_Handler); 
	 //����������HC-SR04����
    xTaskCreate((TaskFunction_t )HCSR04_task,     
                (const char*    )"HCSR04_task",   
                (uint16_t       )HCSR04_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )HCSR04_TASK_PRIO,
                (TaskHandle_t*  )&HCSR04_Task_Handler); 

				
	 //��������ǿ������
    xTaskCreate((TaskFunction_t )LSENS_task,     
                (const char*    )"LSENS_task",   
                (uint16_t       )LSENS_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )LSENS_TASK_PRIO,
                (TaskHandle_t*  )&LSENS_Task_Handler); 
	
	 //���������������
    xTaskCreate((TaskFunction_t )HCSR501_task,     
                (const char*    )"HCSR501_task",   
                (uint16_t       )HCSR501_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )HCSR501_TASK_PRIO,
                (TaskHandle_t*  )&HCSR501_Task_Handler); 
				
	 //���������������
    xTaskCreate((TaskFunction_t )CLOSE_task,     
                (const char*    )"CLOSE_task",   
                (uint16_t       )CLOSE_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )CLOSE_TASK_PRIO,
                (TaskHandle_t*  )&CLOSE_Task_Handler); 

				
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}

//��ʪ��������
void DHT11_task(void *pvParameters)
{	
	DTH11_PIN_Init();
	while(1)
	{

		//printf("DHT11_task\r\n");
		uint32_t timeout = xTaskGetTickCount() + pdMS_TO_TICKS(500); // 50ms��ʱʱ��
		xSemaphoreTake(MutexSemaphore01,portMAX_DELAY);
		// while(xSemaphoreTake(MutexSemaphore01,portMAX_DELAY)==pdFALSE)//��ȡ�����ź���
		// {
		// 	if (xTaskGetTickCount() >= timeout)
		// 	{
       	// 	 // ��ʱ�˳�			
        		
		// 	}
			
		// }
		DHT11_OPEN();
		//printf("	DHT11_task_return\r\n");
		//timeout = xTaskGetTickCount() + pdMS_TO_TICKS(500);
		xSemaphoreGive(MutexSemaphore01);
		// while(xSemaphoreGive(MutexSemaphore01)==pdFALSE)//�ͷŻ����ź���
		// {
		// 	if (xTaskGetTickCount() >= timeout)
		// 	{
       	// 	 // ��ʱ�˳�			
      
		// 	}
		 //}
       vTaskDelay(500);                         
	}
}


//������������
void HCSR04_task(void *pvParameters)
{
	float length;
	while(1)
	{
		
		xSemaphoreTake(MutexSemaphore02,portMAX_DELAY);	//��ȡ�����ź���
		length = HCSR04_OPEN();	
		//wifi����	
		u8 buf[100] = {0};
		//sprintf((char* )buf,"HCSR04:  %fcm\r\n",length);
		sprintf((char *)buf,"HCSR04(hcsr04:%fcm;})\r\n",length);
		//delay_ms(50);
		UART3_Send_Str(buf);
		memset(buf,'\0',sizeof(buf));
		xSemaphoreGive(MutexSemaphore02);					//�ͷŻ����ź���		
		vTaskDelay(1000);           
	}
}


//����ʪ��������
void YL_task(void *pvParameters)
{
	while(1)
	{
//		xSemaphoreTake(MutexSemaphore03,portMAX_DELAY);	//��ȡ�����ź���
		u8 soil_humidity = 0;
		soil_humidity = YL_OPEN();
		u8 buf[100] = {0};
		sprintf((char* )buf,"����ʪ��Ϊ:  %.2f%%\r\n",(float)soil_humidity);
		sprintf((char *)buf,"HUMSOIL(humSoil:%.2f%%;})\r\n",(float)soil_humidity);
		UART3_Send_Str(buf);
		memset(buf,'\0',sizeof(buf));
//		xSemaphoreGive(MutexSemaphore03);					//�ͷŻ����ź���		
       vTaskDelay(1000);           
	}
}


//����ǿ��������
void LSENS_task(void *pvParameters)
{
	while(1)
	{
//		xSemaphoreTake(MutexSemaphore04,portMAX_DELAY);	//��ȡ�����ź���
		Lsens_OPEN();						
		vTaskDelay(1000);    
//		xSemaphoreGive(MutexSemaphore04);					//�ͷŻ����ź���		
	}
}

//�������������
void HCSR501_task(void *pvParameters)
{
	while(1)
	{		
//		xSemaphoreTake(MutexSemaphore05,portMAX_DELAY);	//��ȡ�����ź���
		HC_SR501_OPEN();	
//		xSemaphoreGive(MutexSemaphore05);					//�ͷŻ����ź���			
		vTaskDelay(1000);           
	}
}


//�ر�������
void CLOSE_task(void *pvParameters)
{
	while(1)
	{
		vTaskSuspend(DHT11_Task_Handler);
		vTaskSuspend(YL_Task_Handler);
		vTaskSuspend(HCSR04_Task_Handler);
		vTaskSuspend(LSENS_Task_Handler);
		vTaskSuspend(HCSR501_Task_Handler);	
		vTaskDelete(CLOSE_Task_Handler); //ɾ����ʼ����				
	}
}





u8 uart2_revbuf[200]={0};
u8 uart2_flag = 0;

void USART3_IRQHandler(void)
{
	static u16 len = 0;
	
	if(USART_GetITStatus(USART3, USART_IT_RXNE))
	{
		//���Ĵ������жϱ�־
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
	else if(NULL!=strstr((const char *)uart2_revbuf,(const char *)"9"))//�رճ�����
	{
		vTaskSuspend(HCSR04_Task_Handler);
		//printf("���ճɹ�");

	}
	else	if(NULL!=strstr((const char *)uart2_revbuf,(const char *)"0"))//�򿪳�����
	{
		
		//printf("���ճɹ�");
		vTaskResume(HCSR04_Task_Handler);
	}
	else if(NULL!=strstr((const char *)uart2_revbuf,(const char *)"d")) //�ر���ʪ��
	{
		vTaskSuspend(DHT11_Task_Handler);
		//printf("���ճɹ�");

	}
	else	if(NULL!=strstr((const char *)uart2_revbuf,(const char *)"f"))//����ʪ��
	{
		
		//printf("���ճɹ�");
		vTaskResume(DHT11_Task_Handler);
	}
	else if(NULL!=strstr((const char *)uart2_revbuf,(const char *)"y"))//�ر�����ʪ��
	{
		vTaskSuspend(YL_Task_Handler);
		//printf("���ճɹ�");

	}
	else if(NULL!=strstr((const char *)uart2_revbuf,(const char *)"u"))//������ʪ��
	{
		
		//printf("���ճɹ�");
		vTaskResume(YL_Task_Handler);
	}
	else if(NULL!=strstr((const char *)uart2_revbuf,(const char *)"l")) //�رչ���
	{
		vTaskSuspend(LSENS_Task_Handler);
		//printf("���ճɹ�");

	}
	else if(NULL!=strstr((const char *)uart2_revbuf,(const char *)"k"))//�򿪹���
	{
		
		//printf("���ճɹ�");
		vTaskResume(LSENS_Task_Handler);
	}
	else if(NULL!=strstr((const char *)uart2_revbuf,(const char *)"h"))//�ر��������
	{
		vTaskSuspend(HCSR501_Task_Handler);
		//printf("���ճɹ�");

	}
	else if(NULL!=strstr((const char *)uart2_revbuf,(const char *)"j"))//���������
	{
		
		//printf("���ճɹ�");
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
		
		//printf("���ճɹ�");

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
		//printf("���ճɹ�");

	}
	}
	
	
	if(USART_GetITStatus(USART3, USART_IT_IDLE))
	{
		//����жϱ�־λ
		USART3->SR;
		USART3->DR;
		
		uart2_revbuf[len] = '\0';
		printf("%s",uart2_revbuf);
		
		uart2_flag = 1;
		len = 0;
	}
}



