#ifndef _beep_h_
#define _beep_h_
/*******************************************************************************
****����Ƕ��ʽϵͳ STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****�汾:V1.0
****����:14-2-2014
****˵��:��оƬSTM8S105C4T6
********************************************************************************/
//���������Ƶ��
#define beep_1k (BEEP_FREQUENCY_1KHZ)
#define beep_2k (BEEP_FREQUENCY_2KHZ)
#define beep_4k (BEEP_FREQUENCY_4KHZ)

extern void Beep_Init(BEEP_Frequency_TypeDef beep_fre);
#endif
/******************* (C) COPYRIGHT 2014 LENCHIMCU.TAOBAO.COM ******************/