#ifndef _24l01_h_
#define _24l01_h_
/*******************************************************************************
****����Ƕ��ʽϵͳ STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****�汾:V1.0
****����:14-2-2014
****˵��:��оƬSTM8S105C4T6
********************************************************************************/
//nRF24L01�������ź궨��
#define NRF24L01_CE_PORT  GPIOC
#define NRF24L01_IRQ_PORT GPIOC
#define NRF24L01_CSN_PORT GPIOC

#define NRF24L01_CE_PIN  GPIO_PIN_3
#define NRF24L01_IRQ_PIN GPIO_PIN_2
#define NRF24L01_CSN_PIN GPIO_PIN_1
 
#define SetCE	GPIO_WriteHigh(NRF24L01_CE_PORT, NRF24L01_CE_PIN)
#define ClrCE	GPIO_WriteLow(NRF24L01_CE_PORT, NRF24L01_CE_PIN)

#define SetCSN	GPIO_WriteHigh(NRF24L01_CSN_PORT, NRF24L01_CSN_PIN)
#define ClrCSN	GPIO_WriteLow(NRF24L01_CSN_PORT, NRF24L01_CSN_PIN)

#define TX_ADDR_WITDH 	5		/* ���͵�ַ�������Ϊ5���ֽ� */
#define RX_ADDR_WITDH 	5		/* ���յ�ַ�������Ϊ5���ֽ� */
#define TX_DATA_WITDH 	32		/* �������ݿ��4���ֽ� */
#define RX_DATA_WITDH 	32		/* �������ݿ��4���ֽ� */



//����Ĵ���
#define  R_REGISTER      0x00//��ȡ���üĴ���
#define  W_REGISTER      0x20//д���üĴ���
#define  R_RX_PAYLOAD 	 0x61//��ȡRX��Ч����
#define  W_TX_PAYLOAD	 0xa0//дTX��Ч����
#define  FLUSH_TX		 0xe1//���TXFIFO�Ĵ���
#define  FLUSH_RX		 0xe2//���RXFIFO�Ĵ���
#define  REUSE_TX_PL     0xe3//����ʹ����һ����Ч����
#define  NOP             0xff//�ղ���

//�Ĵ�����ַ
#define  CONFIG          0x00//���üĴ���
#define  EN_AA			 0x01//ʹ���Զ�Ӧ��
#define  EN_RXADDR       0x02//����ͨ��ʹ��0-5��ͨ��
#define  SETUP_AW        0x03//��������ͨ����ַ���3-5
#define  SETUP_RETR      0x04//�����Զ��ط�
#define  RF_CH           0x05//��Ƶͨ������
#define  RF_SETUP        0x06//��Ƶ�Ĵ���
#define  STATUS          0x07//״̬�Ĵ���
#define  OBSERVE_TX      0x08//���ͼ��Ĵ���
#define  CD              0x09//�ز�
#define  RX_ADDR_P0      0x0a//����ͨ��0���յ�ַ
#define  RX_ADDR_P1      0x0b//����ͨ��1���յ�ַ
#define  RX_ADDR_P2      0x0c//����ͨ��2���յ�ַ
#define  RX_ADDR_P3      0x0d//����ͨ��3���յ�ַ
#define  RX_ADDR_P4      0x0e//����ͨ��4���յ�ַ
#define  RX_ADDR_P5      0x0f//����ͨ��5���յ�ַ
#define  TX_ADDR         0x10//���͵�ַ
#define  RX_PW_P0        0x11//P0ͨ�����ݿ������
#define  RX_PW_P1        0x12//P1ͨ�����ݿ������
#define  RX_PW_P2        0x13//P2ͨ�����ݿ������
#define  RX_PW_P3        0x14//P3ͨ�����ݿ������
#define  RX_PW_P4        0x15//P4ͨ�����ݿ������
#define  RX_PW_P5        0x16//P5ͨ�����ݿ������
#define  FIFO_STATUS     0x17//FIFO״̬�Ĵ���

extern void NRF24L01_Init(void);
extern unsigned char NRF24L01_RW(unsigned char data);
extern unsigned char NRF24L01_Read_Reg(unsigned char RegAddr);
extern unsigned char NRF24L01_Write_Reg(unsigned char RegAddr,unsigned char data);
extern unsigned char NRF24L01_Read_RxData(unsigned char RegAddr, unsigned char *RxData, unsigned char DataLen);
extern unsigned char NRF24L01_Write_TxData(unsigned char RegAddr,unsigned char *TxData,unsigned char DataLen);
extern void NRF24L01_Set_TxMode();
extern void NRF24L01_Set_RxMode();
extern void NRF24L01_SendData(unsigned char *data);
extern unsigned char NRF24L01_RevData(unsigned char *RevData);
extern unsigned char NRRF24L01_CheckACK();
#endif
/******************* (C) COPYRIGHT 2014 LENCHIMCU.TAOBAO.COM ******************/