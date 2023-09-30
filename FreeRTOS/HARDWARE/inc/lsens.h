#ifndef __LSENS_H
#define __LSENS_H	
#include "sys.h" 
#include "usart.h"
#include "stdio.h"
#include "string.h"
#include "main.h"	  

  
#define LSENS_READ_TIMES	10		//定义光敏传感器读取次数,读这么多次,然后取平均值
 
void Lsens_Init(void); 				//初始化光敏传感器
void Lsens_OPEN(void);			//读取光敏传感器的值
void Adc3_Init(void); 				//ADC通道初始化
u16  Get_Adc3(u8 ch); 				//获得某个通道值 
u16 Get_Adc_Average(u8 ch,u8 times);//得到某个通道给定次数采样的平均值  
#endif 





















