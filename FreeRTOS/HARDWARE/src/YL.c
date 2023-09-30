#include "stm32f4xx.h"
#include "YL.h"
#include "stdio.h"
#include "main.h"

#define ADC_RESOLUTION 4095.0f // 12-bit ADC
#define VREF 3.3f // 3.3V参考电压
#define SOIL_HUMIDITY_RANGE 100.0f // 土壤湿度范围
float adc_value = 0.0f; // ADC读取值
float soil_humidity = 0.0f; // 土壤湿度
float voltage = 0.0f; // 实际电压值
void YL_ADC2_Init(void)
{
    // 使能GPIOA时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    // 使能ADC2时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
    // 配置GPIOA为模拟输入模式
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    // 配置ADC2的通道
    ADC_CommonInitTypeDef ADC_CommonInitStructure;
    ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
    ADC_CommonInit(&ADC_CommonInitStructure);
    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfConversion = 1;
    ADC_Init(ADC2, &ADC_InitStructure);
    ADC_RegularChannelConfig(ADC2, ADC_Channel_4, 1, ADC_SampleTime_144Cycles);
    // 启动ADC2转换
    ADC_Cmd(ADC2, ENABLE);
}
float ConvertToSoilHumidity(float adc_value)
{
    //根据实际情况调整下面的公式
    float soil_humidity = SOIL_HUMIDITY_RANGE * (1.0f - (adc_value / ADC_RESOLUTION));
    return soil_humidity;
}
float ConvertToVoltage(float adc_value)
{
    float voltage = (adc_value / ADC_RESOLUTION) * VREF;
    return voltage;
}
u8 YL_OPEN(void)
{
		YL_ADC2_Init();

        //开始转换
        ADC_SoftwareStartConv(ADC2);
        uint32_t timeout = xTaskGetTickCount() + pdMS_TO_TICKS(500); // 50ms超时时间
        //等待转换完成
        while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC))
        {

            
			 if (xTaskGetTickCount() >= timeout)
				{
				// 超时退出	
					return 1;
				}
			
        }
        //读取ADC值
        adc_value = ADC_GetConversionValue(ADC2);
        //转换为实际电压值
        voltage = ConvertToVoltage(adc_value);
        //转换为土壤湿度
        soil_humidity = ConvertToSoilHumidity(adc_value);
        //打印实际电压值和土壤湿度
        //printf("电压为: %.2fV, 土壤湿度为: %.2f%%\r\n", voltage, soil_humidity);
        //延时一段时间
		return (u8)soil_humidity;
}



