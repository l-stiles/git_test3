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
****��������:��ʼ���ⲿ�ж�
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��
****���ڲ���:��
****˵��:����������PA4/5/6�������������˿�λ�ⲿ�жϣ��½��ش���
********************************************************************************/
void  EXTI_Init(void)
{
   EXTI_DeInit();//�ָ��ⲿ�ж���ؼĴ���ΪĬ��ֵ
   GPIO_Init(GPIOB, GPIO_PIN_3, GPIO_MODE_IN_PU_IT);//�����������ж�
   EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOB, EXTI_SENSITIVITY_FALL_ONLY);//�½��ش���
   
   GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_IN_PU_IT);//�����������ж�
   EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD, EXTI_SENSITIVITY_FALL_ONLY);//�½��ش���
   
   GPIO_Init(GPIOD, GPIO_PIN_7, GPIO_MODE_IN_PU_IT);//�����������ж�
   EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOA, EXTI_SENSITIVITY_FALL_ONLY);//�½��ش���
   
   
   enableInterrupts();//ʹ�������ж�
}
/******************* (C) COPYRIGHT 2014 LENCHIMCU.TAOBAO.COM ******************/