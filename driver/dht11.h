/*****************************************************************************/ /*****************************************************************************/
#ifndef _dht11_h_
#define _dht11_h_
/*******************************************************************************
****蓝旗嵌入式系统 STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****版本:V1.0
****日期:14-2-2014
****说明:主芯片STM8S105C4T6
********************************************************************************/
#define DHT11_PORT  (GPIOA)
#define DHT11_PIN   (GPIO_PIN_5)


#define DHT11_CLR  GPIO_WriteLow(DHT11_PORT,DHT11_PIN);
#define DHT11_SET  GPIO_WriteHigh(DHT11_PORT,DHT11_PIN);
#define DHT11_IN   GPIO_Init(DHT11_PORT,DHT11_PIN, GPIO_MODE_IN_PU_NO_IT);
#define DHT11_OUT  GPIO_Init(DHT11_PORT,DHT11_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);

extern void DHT11_Init(void);
extern unsigned int DHT11_Start(void);
extern unsigned char DHT11_ReadValue(void);
extern unsigned char Get_data(unsigned char *buf);

#endif
/*****************************************************************************/ /*****************************************************************************/ 