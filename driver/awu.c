/*******************************************************************************
****蓝旗嵌入式系统 STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****版本:V1.0
****日期:14-2-2014
****说明:主芯片STM8S105C4T6
********************************************************************************/
#include "include.h"

void AWU_Ini(void)
{
 // AWU_DeInit();
  AWU_LSICalibrationConfig(128000);//校准LSI
  AWU_Init(AWU_TIMEBASE_1S);//1秒唤醒时间
  AWU_Cmd(ENABLE);
}

/******************* (C) COPYRIGHT 2014 LENCHIMCU.TAOBAO.COM ******************/