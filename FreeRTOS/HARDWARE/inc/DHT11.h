#ifndef _DHT11_H
#define _DHT11_H
#include "sys.h"
#include "stm32f4xx.h" 
#include "usart.h"
#include "delay.h"
#include "main.h"



void DTH11_PIN_Init(void);
void DHT11_start(void);
u8 DHT11_recask(void);
u8 DHT11_recdata(void);
u8 DHT11_data(float* shidu  , float* wendu);

u8 DHT11_OPEN(void);

#endif /*_DHT11_H*/
