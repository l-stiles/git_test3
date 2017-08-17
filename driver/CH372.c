/*******************************************************************************
****蓝旗嵌入式系统 STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****版本:V1.0
****日期:14-2-2014
****说明:主芯片STM8S105C4T6
********************************************************************************/
#include "include.h"
/*******************************************************************************
****函数名称:
****函数功能:延时函数
****版本:V1.0
****日期:14-2-2014
****入口参数:需要延时的数目
****出口参数:无
****说明:
********************************************************************************/
void Delay(uint16_t nCount)
{
  while (nCount != 0)
  {   
    nCount--;
  }
}
/*******************************************************************************
****函数名称:
****函数功能:初始化ch372相关端口
****版本:V1.0
****日期:14-2-2014
****入口参数:无
****出口参数:无
****说明:
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
  //注意PD7中断位最高级中断
   EXTI_DeInit();
   GPIO_Init(CH372_INT_PORT, CH372_INT_PIN, GPIO_MODE_IN_PU_IT);//INT
   EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD, EXTI_SENSITIVITY_FALL_ONLY);
   enableInterrupts();//使能所有中断
}
/*******************************************************************************
****函数名称:
****函数功能:向CH372写命令
****版本:V1.0
****日期:14-2-2014
****入口参数:Cmd-要写入的命令
****出口参数:无
****说明:
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
****函数名称:
****函数功能:向CH372写数据
****版本:V1.0
****日期:14-2-2014
****入口参数:Dat-要写入的数据
****出口参数:无
****说明:
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
****函数名称:
****函数功能:从CH372读数据
****版本:V1.0
****日期:14-2-2014
****入口参数:wu
****出口参数:Dat-从CH372读取的数据
****说明:
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