#ifndef _timer1_h_
#define _timer1_h_
/*******************************************************************************
****����Ƕ��ʽϵͳ STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****�汾:V1.0
****����:14-2-2014
****˵��:��оƬSTM8S105C4T6
********************************************************************************/
extern void Time1_InputCap();
extern u16 Timer1_InputCapCFre(void);
extern void Get_FrequencyArray(u16 FrequencyArray[], u8 times);
extern u16 Get_AverageFrequency(u16 GetFrequency[],u8 n);
extern void Timer1_OutCompare(void);

#endif
/******************* (C) COPYRIGHT 2014 LENCHIMCU.TAOBAO.COM ******************/