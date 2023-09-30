#ifndef __MAIN_H
#define __MAIN_H	 
#include "sys.h" 
#include "stm32f4xx.h"
#include "led.h"
#include "FreeRTOS.h"
#include "task.h"
#include "usart.h"
#include "delay.h"
#include "string.h"
#include "stdio.h"
#include "mq2.h"
#include "YL.h"
#include "DHT11.h"
#include "HC-SR04.h"
#include "motor.h"
#include "wifi2.h"
#include "nvic.h"
#include "lsens.h"
#include "hc_sr501.h"
#include "RGB.h"

extern u8 uart1_rxbuff[1024];
extern u8 rx_flag;

extern u8 uart2_revbuf[200];
extern u8 uart2_flag;	

#endif

