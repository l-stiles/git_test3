/*******************************************************************************
****����Ƕ��ʽϵͳ STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****�汾:V1.0
****����:14-2-2014
****˵��:��оƬSTM8S105C4T6
********************************************************************************/
#include "include.h"

unsigned char  TxAddr[]={0x34,0x43,0x10,0x10,0x01};//���͵�ַ
extern void Delay(uint16_t nCount);
/*******************************************************************************
****��������:
****��������:��ʼ��NRF24L01�ӿ�
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��
****���ڲ���:��
****˵��:
********************************************************************************/
void NRF24L01_Init(void)
{
  // ��ʼ��SPI--��λ��ǰ��, ��ģʽ��SCK����Ϊ�͵�ƽ����һ�����زɼ����� 
	SPI_Init(SPI_FIRSTBIT_MSB, SPI_BAUDRATEPRESCALER_4, SPI_MODE_MASTER,\
		 SPI_CLOCKPOLARITY_LOW, SPI_CLOCKPHASE_1EDGE, \
		 SPI_DATADIRECTION_2LINES_FULLDUPLEX, SPI_NSS_SOFT, 0x07);
	
	SPI_Cmd(ENABLE);	/* ʹ��SPI */
	
	GPIO_Init(NRF24L01_CSN_PORT, NRF24L01_CSN_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);	//CSN���ų�ʼ��Ϊ��� 
	GPIO_Init(NRF24L01_CE_PORT, NRF24L01_CE_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);	// CE���ų�ʼ��Ϊ��� 
}
/*******************************************************************************
****��������:
****��������:��дһ���ֽ�����
****�汾:V1.0
****����:14-2-2014
****��ڲ���:dataҪд������
****���ڲ���:��ȡ������
****˵��:
********************************************************************************/
unsigned char NRF24L01_RW(unsigned char data)
{
	//�ȴ�DR�Ĵ����ǿ� 
	while (SPI_GetFlagStatus( SPI_FLAG_TXE) == RESET);
	
	//ͨ��SPI����һ���ֽ� 
	SPI_SendData(data);
	
	//�ȴ�����һ���ֽ� 
	while (SPI_GetFlagStatus(SPI_FLAG_RXNE) == RESET);
	
	//����SPI�����ϵ��ֽ� 
	return SPI_ReceiveData();  
}
/*******************************************************************************
****��������:
****��������:���Ĵ���
****�汾:V1.0
****����:14-2-2014
****��ڲ���:RegAddr�Ĵ�����ַ
****���ڲ���:��ȡ������
****˵��:
********************************************************************************/
unsigned char NRF24L01_Read_Reg(unsigned char RegAddr)
{
   u8 BackData;
   
   ClrCSN;				// ����ʱ�� 
   NRF24L01_RW(RegAddr);		// д�Ĵ�����ַ 
   BackData = NRF24L01_RW(0x00);	// д����Ĵ���ָ�� 
   SetCSN;
   
   return(BackData); 			// ����״ֵ̬ 
}
/*******************************************************************************
****��������:
****��������:д�Ĵ���
****�汾:V1.0
****����:14-2-2014
****��ڲ���:RegAddr�Ĵ�����ַ dataҪд�������
****���ڲ���:���ص�����
****˵��:
********************************************************************************/
unsigned char NRF24L01_Write_Reg(unsigned char RegAddr,unsigned char data)
{
   u8 BackData;
   
   ClrCSN;				//����ʱ�� 
   BackData = NRF24L01_RW(RegAddr);	// д���ַ 
   NRF24L01_RW(data);			// д��ֵ 
   SetCSN;
   
   return(BackData);
}
/*******************************************************************************
****��������:
****��������:��ȡRX FIFO���������
****�汾:V1.0
****����:14-2-2014
****��ڲ���:RegAddr�Ĵ�����ַ *RxData���ݻ����� DataLen���ݳ���
****���ڲ���:���ص�����
****˵��:����ģʽ��ʹ��
********************************************************************************/
unsigned char NRF24L01_Read_RxData(unsigned char RegAddr, unsigned char *RxData, unsigned char DataLen)
{ 
	u8 BackData,i;
	
	ClrCSN;					//����ʱ�� 
	BackData = NRF24L01_RW(RegAddr);	//д��Ҫ��ȡ�ļĴ�����ַ 
	for(i = 0; i < DataLen; i++) 		// ��ȡ���� 
	{
		RxData[i] = NRF24L01_RW(0);
	} 
	
	SetCSN;
	
	return(BackData); 
}
/*******************************************************************************
****��������:
****��������:д���ݵ�TX FIFO����
****�汾:V1.0
****����:14-2-2014
****��ڲ���:RegAddr�Ĵ�����ַ *RxData���ݻ����� DataLen���ݳ���
****���ڲ���:���ص�����
****˵��:
********************************************************************************/
unsigned char NRF24L01_Write_TxData(unsigned char RegAddr,unsigned char *TxData,unsigned char DataLen)
{ 
	u8 BackData,i;
	
	ClrCSN;
	BackData = NRF24L01_RW(RegAddr);	// д��Ҫд��Ĵ����ĵ�ַ 
	for(i = 0; i < DataLen; i++)		// д������ 
	{
	    NRF24L01_RW(*TxData++);
	}   
	
	SetCSN;
	return(BackData);
}
/*******************************************************************************
****��������:
****��������:����Ϊ����ģʽ
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��
****���ڲ���:��
****˵��:
********************************************************************************/
void NRF24L01_Set_TxMode()
{
        ClrCE; 
	//���÷��͵�ַ�͵�ַ���� 
   	NRF24L01_Write_TxData(W_REGISTER+TX_ADDR,TxAddr,TX_ADDR_WITDH);	
	// Ϊ��Ӧ������豸������ͨ��0��ַ�ͷ��͵�ַ��ͬ 
	NRF24L01_Write_TxData(W_REGISTER+RX_ADDR_P0,TxAddr,TX_ADDR_WITDH);	

	/******�����йؼĴ�������**************/
  	NRF24L01_Write_Reg(W_REGISTER+EN_AA,0x01);       /* ʹ�ܽ���ͨ��0�Զ�Ӧ�� */
  	NRF24L01_Write_Reg(W_REGISTER+EN_RXADDR,0x01);   /* ʹ�ܽ���ͨ��0 */
   	NRF24L01_Write_Reg(W_REGISTER+SETUP_RETR,0x0a);  /* �Զ��ط���ʱ�ȴ�250us+86us���Զ��ط�10�� */
  	NRF24L01_Write_Reg(W_REGISTER+RF_CH,0x40);       /* ѡ����Ƶͨ��0x40 */
  	NRF24L01_Write_Reg(W_REGISTER+RF_SETUP,0x07);    /* ���ݴ�����1Mbps�����书��0dBm���������Ŵ������� */
	NRF24L01_Write_Reg(W_REGISTER+CONFIG,0x0e);      /* CRCʹ�ܣ�16λCRCУ�飬�ϵ� */ 
	SetCE;
	Delay(5);	// ����оƬ�ֲ�Ҫ�� ����10us������ 
}
/*******************************************************************************
****��������:
****��������:����Ϊ����ģʽ
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��
****���ڲ���:��
****˵��:
********************************************************************************/
void NRF24L01_Set_RxMode()
{
	ClrCE; 
	// �����豸����ͨ��0ʹ�úͷ����豸��ͬ�ķ��͵�ַ 
  	NRF24L01_Write_TxData(W_REGISTER+RX_ADDR_P0, TxAddr, TX_ADDR_WITDH);  
	
	/******�����йؼĴ�������**************/
  	NRF24L01_Write_Reg(W_REGISTER+EN_AA,0x01);       /* ʹ�ܽ���ͨ��0�Զ�Ӧ�� */
  	NRF24L01_Write_Reg(W_REGISTER+EN_RXADDR,0x01);   /* ʹ�ܽ���ͨ��0 */
  	NRF24L01_Write_Reg(W_REGISTER+RF_CH,0x40);       /* ѡ����Ƶͨ��0x40 */
	NRF24L01_Write_Reg(W_REGISTER+RX_PW_P0,TX_DATA_WITDH);  /* ����ͨ��0ѡ��ͷ���ͨ����ͬ��Ч���ݿ�� */
  	NRF24L01_Write_Reg(W_REGISTER+RF_SETUP,0x07);    /* ���ݴ�����1Mbps�����书��0dBm���������Ŵ������� */
	NRF24L01_Write_Reg(W_REGISTER+CONFIG,0x0f);      /* CRCʹ�ܣ�16λCRCУ�飬�ϵ� */ 
	SetCE;
	Delay(5);	// ����оƬ�ֲ�Ҫ�� ����10us������ 
  
}
/*******************************************************************************
****��������:
****��������:��������
****�汾:V1.0
****����:14-2-2014
****��ڲ���:*data���ݻ�����
****���ڲ���:��
****˵��:
********************************************************************************/
void NRF24L01_SendData(unsigned char *data)
{
	ClrCE;
	NRF24L01_Write_TxData(W_TX_PAYLOAD, data, TX_DATA_WITDH);	//д��Ҫ���͵����� 
	SetCE;
	
	Delay(5);
}
/*******************************************************************************
****��������:
****��������:��������
****�汾:V1.0
****����:14-2-2014
****��ڲ���:*RevData���ݻ�����
****���ڲ���:0-���ճɹ� 1-����ʧ��
****˵��:
********************************************************************************/
unsigned char NRF24L01_RevData(unsigned char *RevData)
{
	u8 RevFlags = 1;
	u8 sta;
	
	sta = NRF24L01_Read_Reg(R_REGISTER+STATUS);	/* ��ȡ״̬�Ĵ�����ֵ */
	if(sta & 0x40)				/* �ж��Ƿ���յ����� */
	{
		ClrCE; 			
		NRF24L01_Read_RxData(R_RX_PAYLOAD,RevData,RX_DATA_WITDH);	/* ��RXFIFO��ȡ4λ���� */
		
		/* ���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�־ */
		NRF24L01_Write_Reg(W_REGISTER+STATUS,0xff); 
		
		ClrCSN;
	   	NRF24L01_RW(FLUSH_RX);	/* �������FIFO */
	   	SetCSN;	
		
		RevFlags = 0;	   
	}
	
	return(RevFlags);
}
/*******************************************************************************
****��������:
****��������:�Ƿ��ͳɹ�
****�汾:V1.0
****����:14-2-2014
****��ڲ���:*data���ݻ�����
****���ڲ���:0-���ͳɹ� 1-����ʧ��
****˵��:
********************************************************************************/
unsigned char NRRF24L01_CheckACK()
{  
  	u8 sta;
	
	sta=NRF24L01_Read_Reg(R_REGISTER+STATUS);  	/* ���ͺ��ȡ״̬�Ĵ�����ֵ */
	//UART1_SendByte(sta);
	if((sta&0x20)||(sta&0x10)) /* �Ƿ������������жϺ��ظ������ж� */
	{
	   NRF24L01_Write_Reg(W_REGISTER+STATUS,0xff);  /* ���TX_DS��MAX_RT�жϱ�־ */
	   ClrCSN;
	   NRF24L01_RW(FLUSH_TX);	/* �������FIFO */   
           SetCSN; 
	   return 0;
	}
	else
	   return 1;
}
/******************* (C) COPYRIGHT 2014 LENCHIMCU.TAOBAO.COM ******************/