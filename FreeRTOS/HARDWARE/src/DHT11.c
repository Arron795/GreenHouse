#include "DHT11.h"
#include "semphr.h"
//��©ģʽ��������ֿ�����
//��©ģʽ�����ߵ�ƽ �Զ��������ģʽ
//�˿� PC8 5v 
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
	
	//data��Ϊ���ģʽ
	
	//Խ��1�벻�ȶ�ʱ��
	delay_ms(1000);

	//������
	GPIO_SetBits(GPIOC, GPIO_Pin_8);
	
}
/*
�������ƣ�DHT11_start
��������: void
��������ֵ: void
��������: //�����ź�
*/
void DHT11_start(void)
{
	
	//������ʼ�ź�
	GPIO_ResetBits(GPIOC, GPIO_Pin_8);
	//����20�����ʾ��ʼ�ź�
	  vTaskDelay(20);
	
	//����Ϊ���룬��©ģʽ�����ߵ�ƽ �Զ��������ģʽ
	GPIO_SetBits(GPIOC, GPIO_Pin_8);	
	//DHT11_READ;
	
}

/*
�������ƣ�DHT11_recask
��������: void
��������ֵ: u8  ����1ʧ�ܣ�0��ʾ�ɹ�
��������: //���Ӧ��
*/

u8 DHT11_recask(void)
{
	u8 cnt = 0;
	//�ȴ��ߵ�ƽ��͵�ƽ��������Ӧ�ź�
	uint32_t timeout = xTaskGetTickCount() + pdMS_TO_TICKS(500); // 50ms��ʱʱ��
	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)==1)
	{
		 if (xTaskGetTickCount() >= timeout)
		{
        // ��ʱ�˳�
			
        return 1;
		}		
	}
	timeout = xTaskGetTickCount() + pdMS_TO_TICKS(800); // 80ms��ʱʱ��
	//�ȴ��͵�ƽ��ߵ�ƽ��83us�׶�
	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)==0)
	{
	
		 if (xTaskGetTickCount() >= timeout)
        {
            // ��ʱ�˳�
          return 1;
        }
	}
	 timeout = xTaskGetTickCount() + pdMS_TO_TICKS(600); // 60us��ʱʱ��
	//�ȴ��ߵ�ƽ��͵�ƽ ,87us
	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)==1)
	{
		  if (xTaskGetTickCount() >= timeout)
        {
            // ��ʱ�˳�
          return 1;
        }
	}
	
	return 0; //��Ӧ�ɹ�
	
		
	
}


/*
�������ƣ�DHT11_recdata
��������: void
��������ֵ: u8  ��������
��������: //��������
*/


u8 DHT11_recdata(void)
{
	u8 i = 0;
	u8 data  = 0;
	for(i=0 ; i < 8;i++)
	{	
		//�ȴ��͵�ƽ��ߵ�ƽ��Խ��54us
	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)==0);
		delay_us(45);
		data = data <<1;//�ճ����λ
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)==1){
			data  |= 0x01;
		}	
	//�ȴ��ߵ�ƽ��͵�ƽ
	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)==1);
	}

	return data;
	
}

/*
�������ƣ�DHT11_data
��������:  float *shidu  , float *wendu
��������ֵ: u8 data ����
��������: //��������
*/


u8 DHT11_data(float* shidu  , float* wendu)
{
	u8 buf[100] = {0};
	u8 byte[5] = {0};
	//��ʼ�ź�
	DHT11_start();
	//�ж�Ӧ��
	if(DHT11_recask()==1)
	{
		//printf("��Ӧʧ��");
		return 1;
	}
//	printf("Ӧ��ɹ�");
	
	byte[0] = DHT11_recdata();//0ʪ����������
	byte[1] = DHT11_recdata();//ʪ��С������ 
	byte[2] = DHT11_recdata();//�¶���������
	byte[3] = DHT11_recdata();//�¶�С������
	byte[4] = DHT11_recdata();//У��
	if(byte[4] == ((byte[0] + byte[1] + byte[2] + byte[3]) & 0xff))	//ȡ�Ͱ�λ
	{
		//printf("������ȷ");
		
		*shidu = (byte[0]/1.0+(byte[1]/10.0)) ;
		
		*wendu = (byte[2]/1.0+(byte[3]/10.0)) ;
		
	//printf("ʪ��Ϊ��%.2f\r\n",*shidu);	
	//printf("�¶�Ϊ��%.2f\r\n",*wendu);
	//���͸�wifi
//	sprintf((char* )buf,"�¶�:  %.2f\r\n",*wendu);
//	UART3_Send_Str(buf);
//	memset(buf,'\0',sizeof(buf));
//	sprintf((char* )buf,"ʪ��:  %.2f\r\n",*shidu);
	sprintf((char *)buf,"Params(temp:%.2f;humi:%.2f;})\r\n",*wendu,*shidu);
	UART3_Send_Str(buf);
	memset(buf,'\0',sizeof(buf));
		
	}else
	{
		//printf("���ݴ���");
		return 1;
	}
	return 0;
	
}


u8 DHT11_OPEN(void)
{
	TickType_t xLastWakeTime;
	 const TickType_t xFrequency = 1000; // 1s��ȡһ��
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






