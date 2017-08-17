#ifndef _gpio_h_
#define _gpio_h_
/*******************************************************************************
****����Ƕ��ʽϵͳ STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****�汾:V1.0
****����:14-2-2014
****˵��:��оƬSTM8S105C4T6
********************************************************************************/

//  ����LED����
#define  LED1       0x01
#define  LED2       0x02
#define  LED3       0x04
//����LED�ӿ�
#define LED1_GPIO_PORT  (GPIOC)
#define LED1_GPIO_PINS  (GPIO_PIN_3)

#define LED2_GPIO_PORT  (GPIOC)
#define LED2_GPIO_PINS  (GPIO_PIN_4)

#define LED3_GPIO_PORT  (GPIOD)
#define LED3_GPIO_PINS  (GPIO_PIN_2)
//�������ܺ���
extern void LED_Init(u8 LedNum);
extern void LED_On(u8 LedNum);
extern void LED_Off(u8 LedNum);
extern void LED_Toggle(u8 LedNum);
#endif
/******************* (C) COPYRIGHT 2014 LENCHIMCU.TAOBAO.COM ******************/