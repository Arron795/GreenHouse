#ifndef __LSENS_H
#define __LSENS_H	
#include "sys.h" 
#include "usart.h"
#include "stdio.h"
#include "string.h"
#include "main.h"	  

  
#define LSENS_READ_TIMES	10		//���������������ȡ����,����ô���,Ȼ��ȡƽ��ֵ
 
void Lsens_Init(void); 				//��ʼ������������
void Lsens_OPEN(void);			//��ȡ������������ֵ
void Adc3_Init(void); 				//ADCͨ����ʼ��
u16  Get_Adc3(u8 ch); 				//���ĳ��ͨ��ֵ 
u16 Get_Adc_Average(u8 ch,u8 times);//�õ�ĳ��ͨ����������������ƽ��ֵ  
#endif 





















