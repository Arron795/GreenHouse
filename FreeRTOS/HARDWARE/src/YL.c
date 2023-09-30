#include "stm32f4xx.h"
#include "YL.h"
#include "stdio.h"
#include "main.h"

#define ADC_RESOLUTION 4095.0f // 12-bit ADC
#define VREF 3.3f // 3.3V�ο���ѹ
#define SOIL_HUMIDITY_RANGE 100.0f // ����ʪ�ȷ�Χ
float adc_value = 0.0f; // ADC��ȡֵ
float soil_humidity = 0.0f; // ����ʪ��
float voltage = 0.0f; // ʵ�ʵ�ѹֵ
void YL_ADC2_Init(void)
{
    // ʹ��GPIOAʱ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    // ʹ��ADC2ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
    // ����GPIOAΪģ������ģʽ
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    // ����ADC2��ͨ��
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
    // ����ADC2ת��
    ADC_Cmd(ADC2, ENABLE);
}
float ConvertToSoilHumidity(float adc_value)
{
    //����ʵ�������������Ĺ�ʽ
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

        //��ʼת��
        ADC_SoftwareStartConv(ADC2);
        uint32_t timeout = xTaskGetTickCount() + pdMS_TO_TICKS(500); // 50ms��ʱʱ��
        //�ȴ�ת�����
        while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC))
        {

            
			 if (xTaskGetTickCount() >= timeout)
				{
				// ��ʱ�˳�	
					return 1;
				}
			
        }
        //��ȡADCֵ
        adc_value = ADC_GetConversionValue(ADC2);
        //ת��Ϊʵ�ʵ�ѹֵ
        voltage = ConvertToVoltage(adc_value);
        //ת��Ϊ����ʪ��
        soil_humidity = ConvertToSoilHumidity(adc_value);
        //��ӡʵ�ʵ�ѹֵ������ʪ��
        //printf("��ѹΪ: %.2fV, ����ʪ��Ϊ: %.2f%%\r\n", voltage, soil_humidity);
        //��ʱһ��ʱ��
		return (u8)soil_humidity;
}



