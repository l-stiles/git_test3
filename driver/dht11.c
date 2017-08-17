/*******************************************************************************
****����Ƕ��ʽϵͳ STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****�汾:V1.0
****����:14-2-2014
****˵��:��оƬSTM8S105C4T6
********************************************************************************/
#include "include.h"



/*******************************************************************************
****��������:
****��������:ms��ʱ����
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��
****���ڲ���:��
****˵��:
********************************************************************************/
void delay_ms(int value){
  int i,j;
  if(value<1)
    value = 1;
  for(i=0;i!=value;i++)
    for(j=0;j!=5000;++j);
} 
/*******************************************************************************
****��������:
****��������:us��ʱ����
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��
****���ڲ���:��
****˵��:
********************************************************************************/
void Delay_us(u32 nCount)  
{
  for(char i=0;i<5;i++) 
  {
    while (nCount != 0) 
    {
      nCount--; 
    } 
  } 
}  
/*******************************************************************************
****��������:
****��������:��ʼ��UART
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��
****���ڲ���:��
****˵��:
********************************************************************************/
void DHT11_Init(void) 
{ 
    GPIO_DeInit(GPIOA);  
    
} 
/*******************************************************************************
****��������:
****��������:���Ϳ�ʼ�źź���
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��
****���ڲ���:��
****˵��:
********************************************************************************/
unsigned int DHT11_Start(void)
{ 
  DHT11_OUT;      //���ö˿ڷ���
  DHT11_CLR;      //���Ͷ˿�
  delay_ms(18);   //�������18ms
  DHT11_SET;      //�ͷ�����
  //�����������������ߣ�������ʱ30uS;
  Delay_us(30);
  
  DHT11_IN;      //���ö˿ڷ���
  
  while(!GPIO_ReadInputPin(DHT11_PORT,DHT11_PIN));//DHT11   �ȴ�80us�͵�ƽ��Ӧ�źŽ���
  while(GPIO_ReadInputPin(DHT11_PORT,DHT11_PIN));//DHT11   ����������80us
  
  return 1;
}
/*******************************************************************************
****��������:
****��������:��ȡDHT11����
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��
****���ڲ���:��
****˵��:
********************************************************************************/
unsigned char DHT11_ReadValue(void)
{ 
  unsigned char i,sbuf=0;

  for(i=8;i>0;i--)
  {
    sbuf<<=1; 
    while((!GPIO_ReadInputPin(DHT11_PORT,DHT11_PIN)));//50us�Ŀ�ʼ�͵�ƽ
    Delay_us(30);// ��ʱ 30us �����������Ƿ��Ǹߵ�ƽ 
    if(GPIO_ReadInputPin(DHT11_PORT,DHT11_PIN))
    {
      sbuf|=1;  
    }
    else
    {
      sbuf|=0;
    }
    while(GPIO_ReadInputPin(DHT11_PORT,DHT11_PIN));
  }
  return sbuf;   
}
/*******************************************************************************
****��������:
****��������:��ȡ���������ݺ���
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��
****���ڲ���:��
****˵��:
********************************************************************************/
unsigned char Get_data(unsigned char *buf)
{
  u8 check;

    buf[0]=DHT11_ReadValue();
      
    buf[1]=DHT11_ReadValue();
   
    buf[2]=DHT11_ReadValue();
    
    buf[3]=DHT11_ReadValue();
    
    check =DHT11_ReadValue();

    if(check == buf[0]+buf[1]+buf[2]+buf[3])
        return 1;
    else
        return 0;
} 
