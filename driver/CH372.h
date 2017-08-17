#ifndef _ch372_h_
#define _ch372_h_
/*******************************************************************************
****蓝旗嵌入式系统 STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****版本:V1.0
****日期:14-2-2014
****说明:主芯片STM8S105C4T6
********************************************************************************/

#define CH372_CS_PORT (GPIOE)
#define CH372_CS_PIN  (GPIO_PIN_6)

#define CH372_AO_PORT (GPIOE)
#define CH372_AO_PIN  (GPIO_PIN_3)

#define CH372_WR_PORT (GPIOD)
#define CH372_WR_PIN  (GPIO_PIN_0)

#define CH372_RD_PORT (GPIOD)
#define CH372_RD_PIN  (GPIO_PIN_2)

#define CH372_INT_PORT (GPIOD)
#define CH372_INT_PIN  (GPIO_PIN_7)

#define CH372_DATA_PORT (GPIOB)

extern void CH372_Init(void);
extern void CH372_WR_CMD(s8 Cmd);
extern void CH372_WR_CMD(s8 Cmd);
extern s8 CH372_RD_DAT(void);
extern void Delay(uint16_t nCount);
extern void CH372_WR_DAT(s8 Dat);
#endif