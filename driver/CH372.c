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
****��������:��ʱ����
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��Ҫ��ʱ����Ŀ
****���ڲ���:��
****˵��:
********************************************************************************/
void Delay(uint16_t nCount)
{
  while (nCount != 0)
  {   
    nCount--;
  }
}
/*******************************************************************************
****��������:
****��������:��ʼ��ch372��ض˿�
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��
****���ڲ���:��
****˵��:
********************************************************************************/
void CH372_Init(void)
{
   GPIO_Init(CH372_CS_PORT, CH372_CS_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);//CS
   GPIO_Init(CH372_AO_PORT, CH372_AO_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);//AO
   GPIO_Init(CH372_WR_PORT, CH372_WR_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);//WR
   GPIO_Init(CH372_RD_PORT, CH372_RD_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);//RD
   GPIO_ExternalPullUpConfig(CH372_CS_PORT, CH372_CS_PIN, ENABLE);
   GPIO_ExternalPullUpConfig(CH372_AO_PORT, CH372_AO_PIN, ENABLE);
   GPIO_ExternalPullUpConfig(CH372_WR_PORT, CH372_WR_PIN, ENABLE);
   GPIO_ExternalPullUpConfig(CH372_RD_PORT, CH372_RD_PIN, ENABLE);
  //ע��PD7�ж�λ��߼��ж�
   EXTI_DeInit();
   GPIO_Init(CH372_INT_PORT, CH372_INT_PIN, GPIO_MODE_IN_PU_IT);//INT
   EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD, EXTI_SENSITIVITY_FALL_ONLY);
   enableInterrupts();//ʹ�������ж�
}
/*******************************************************************************
****��������:
****��������:��CH372д����
****�汾:V1.0
****����:14-2-2014
****��ڲ���:Cmd-Ҫд�������
****���ڲ���:��
****˵��:
********************************************************************************/
void CH372_WR_CMD(s8 Cmd)
{
   Delay(0xff); 
   
   
   GPIO_Init(CH372_DATA_PORT, GPIO_PIN_ALL, GPIO_MODE_OUT_PP_HIGH_SLOW);
   GPIO_ExternalPullUpConfig(GPIOB, GPIO_PIN_ALL, ENABLE);
   GPIO_Write(CH372_DATA_PORT, Cmd);
   
   GPIO_WriteHigh(CH372_AO_PORT, CH372_AO_PIN);
   GPIO_WriteHigh(CH372_RD_PORT, CH372_RD_PIN);
   
   GPIO_WriteLow(CH372_CS_PORT, CH372_CS_PIN);
   GPIO_WriteLow(CH372_WR_PORT, CH372_WR_PIN);
     
   Delay(0xff); 
   GPIO_WriteHigh(CH372_WR_PORT, CH372_WR_PIN);
   GPIO_WriteHigh(CH372_CS_PORT, CH372_CS_PIN);
   
   
   GPIO_WriteLow(CH372_AO_PORT, CH372_AO_PIN);
 
   Delay(0xff); 
}
/*******************************************************************************
****��������:
****��������:��CH372д����
****�汾:V1.0
****����:14-2-2014
****��ڲ���:Dat-Ҫд�������
****���ڲ���:��
****˵��:
********************************************************************************/
void CH372_WR_DAT(s8 Dat)
{
   
   GPIO_Init(CH372_DATA_PORT, GPIO_PIN_ALL, GPIO_MODE_OUT_PP_HIGH_SLOW);
   GPIO_ExternalPullUpConfig(GPIOB, GPIO_PIN_ALL, ENABLE);
   GPIO_Write(CH372_DATA_PORT, Dat);

   GPIO_WriteLow(CH372_AO_PORT, CH372_AO_PIN);
   GPIO_WriteLow(CH372_CS_PORT, CH372_CS_PIN);
   GPIO_WriteLow(CH372_WR_PORT, CH372_WR_PIN);
   GPIO_WriteLow(CH372_CS_PORT, CH372_CS_PIN);
   
   GPIO_WriteHigh(CH372_WR_PORT, CH372_WR_PIN);
   GPIO_WriteHigh(CH372_CS_PORT, CH372_CS_PIN);
 
   Delay(0xff); 
}
/*******************************************************************************
****��������:
****��������:��CH372������
****�汾:V1.0
****����:14-2-2014
****��ڲ���:wu
****���ڲ���:Dat-��CH372��ȡ������
****˵��:
********************************************************************************/
s8 CH372_RD_DAT(void)
{
   s8 Dat;
   GPIO_Init(CH372_DATA_PORT, GPIO_PIN_ALL, GPIO_MODE_IN_PU_NO_IT);
   
   Delay(0xff); 
   GPIO_WriteLow(CH372_AO_PORT, CH372_AO_PIN);
   GPIO_WriteLow(CH372_CS_PORT, CH372_CS_PIN);
   GPIO_WriteLow(CH372_RD_PORT, CH372_RD_PIN);
   //GPIO_WriteLow(CH372_CS_PORT, CH372_CS_PIN);
   
   Dat= GPIO_ReadInputData(CH372_DATA_PORT);
   
   GPIO_WriteHigh(CH372_RD_PORT, CH372_RD_PIN);
   GPIO_WriteHigh(CH372_CS_PORT, CH372_CS_PIN);
   
   return Dat;
}