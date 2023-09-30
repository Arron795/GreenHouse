#ifndef _WIFI2_H

#define _WIFI2_H

#include "stm32f4xx.h"


void esp32_init(u32 baud);
u8 ESP8266_Send_ATcmd(u8 *cmd, u8 *respond);
u8 ESP8266_Connect_WIFI(u8 *ssid, u8 *pwd);
u8 ESP8266_Connect_Server(u8 *tppe, u8 *ip, u32 port);
void Exit_Pass_Through_Mode(void);
u8 ESP8266_Restore(void);
u8 ESP8266_HTTP_Init(u8 *ssid, u8 *pwd, u8 *tppe, u8 *ip, u32 port);
void UART3_Send_Str(u8 *str);

u8 Connect_Wifi_TCP(u8 *ssid, u8 *pwd, u8 *tppe, u8 *ip, u32 port);
	



#endif  /*WIFI2_H*/



