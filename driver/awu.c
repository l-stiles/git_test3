/*******************************************************************************
****����Ƕ��ʽϵͳ STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****�汾:V1.0
****����:14-2-2014
****˵��:��оƬSTM8S105C4T6
********************************************************************************/
#include "include.h"

void AWU_Ini(void)
{
 // AWU_DeInit();
  AWU_LSICalibrationConfig(128000);//У׼LSI
  AWU_Init(AWU_TIMEBASE_1S);//1�뻽��ʱ��
  AWU_Cmd(ENABLE);
}

/******************* (C) COPYRIGHT 2014 LENCHIMCU.TAOBAO.COM ******************/