/*******************************************************************************
****����Ƕ��ʽϵͳ STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****�汾:V1.0
****����:14-2-2014
****˵��:��оƬSTM8S105C4T6
********************************************************************************/
#include "include.h"



/*******************************************************************************
****��������:
****��������:��ʼ��LED�ӿ�
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��Ҫ��ʼ����LED
ȡֵ����ֵ֮һ��������֮��ġ������㡱�����ʽ
            LED1
            LED2
            LED3
****���ڲ���:��
****˵��:
********************************************************************************/
void LED_Init(u8 LedNum)
{
   if(LedNum&LED1)
   {
      GPIO_Init(LED1_GPIO_PORT, (GPIO_Pin_TypeDef)LED1_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST);
   }
    if(LedNum&LED2)
   {
      GPIO_Init(LED2_GPIO_PORT, (GPIO_Pin_TypeDef)LED2_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST);
   }
    if(LedNum&LED3)
   {
      GPIO_Init(LED3_GPIO_PORT, (GPIO_Pin_TypeDef)LED3_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST);
   }
}
/*******************************************************************************
****��������:
****��������:����LED
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��Ҫ������LED
ȡֵ����ֵ֮һ��������֮��ġ������㡱�����ʽ
            LED1
            LED2
            LED3
****���ڲ���:��
****˵��:
********************************************************************************/
void LED_On(u8 LedNum)
{
   if(LedNum&LED1)
   {
      GPIO_WriteLow(LED1_GPIO_PORT, LED1_GPIO_PINS);
   }
   if(LedNum&LED2)
   {
      GPIO_WriteLow(LED2_GPIO_PORT, LED2_GPIO_PINS);
   }
   if(LedNum&LED3)
   {
      GPIO_WriteLow(LED3_GPIO_PORT, LED3_GPIO_PINS);
   }
}
/*******************************************************************************
****��������:
****��������:Ϩ��LED
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��ҪϨ���LED
ȡֵ����ֵ֮һ��������֮��ġ������㡱�����ʽ
            LED1
            LED2
            LED3
****���ڲ���:��
****˵��:
********************************************************************************/
void LED_Off(u8 LedNum)
{
   if(LedNum&LED1)
   {
      GPIO_WriteHigh(LED1_GPIO_PORT, LED1_GPIO_PINS);
   }
   if(LedNum&LED2)
   {
      GPIO_WriteHigh(LED2_GPIO_PORT, LED2_GPIO_PINS);
   }
   if(LedNum&LED3)
   {
      GPIO_WriteHigh(LED3_GPIO_PORT, LED3_GPIO_PINS);
   }
}
/*******************************************************************************
****��������:
****��������:��תLED
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��Ҫ��ת��LED
ȡֵ����ֵ֮һ��������֮��ġ������㡱�����ʽ
            LED1
            LED2
            LED3
****���ڲ���:��
****˵��:
********************************************************************************/
void LED_Toggle(u8 LedNum)
{
   if(LedNum&LED1)
   {
      GPIO_WriteReverse(LED1_GPIO_PORT, LED1_GPIO_PINS);
   }
   if(LedNum&LED2)
   {
      GPIO_WriteReverse(LED2_GPIO_PORT, LED2_GPIO_PINS);
   }
   if(LedNum&LED3)
   {
      GPIO_WriteReverse(LED3_GPIO_PORT, LED3_GPIO_PINS);
   }
}
/******************* (C) COPYRIGHT 2014 LENCHIMCU.TAOBAO.COM ******************/