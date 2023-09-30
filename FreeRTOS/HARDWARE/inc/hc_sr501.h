#ifndef _HC_SR501_H
#define _HC_SR501_H

#include "stm32f4xx.h"
#include "stdio.h"
#include "stdlib.h"
#include "delay.h"
#include "wifi2.h"
#include "string.h"

#define HC_SR501_PORT			GPIOC
#define HC_SR501_PIN			GPIO_Pin_2

#define HC_SR501_H				GPIO_SetBits(HC_SR501_PORT,HC_SR501_PIN)
#define HC_SR501_L				GPIO_ResetBits(HC_SR501_PORT,HC_SR501_PIN)

#define HC_SR501_READ			GPIO_ReadInputDataBit(HC_SR501_PORT,HC_SR501_PIN)

void HC_SR501_Init(void);
void HC_SR501_OPEN(void);

#endif







