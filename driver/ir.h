#ifndef _ir_h_
#define _ir_h_
/*******************************************************************************
****����Ƕ��ʽϵͳ STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****�汾:V1.0
****����:14-2-2014
****˵��:��оƬSTM8S105C4T6
********************************************************************************/
//����������ͷ�ӿ�
#define IR_PORT GPIOA
#define IR_PINS GPIO_PIN_4
//������ع��ܺ���
extern unsigned char a[4];
extern void  IR_Init(void);
extern unsigned char DeCode(void);
#endif

/******************* (C) COPYRIGHT 2014 LENCHIMCU.TAOBAO.COM ******************/