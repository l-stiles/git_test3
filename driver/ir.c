/*******************************************************************************
****����Ƕ��ʽϵͳ STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****�汾:V1.0
****����:14-2-2014
****˵��:��оƬSTM8S105C4T6
********************************************************************************/
#include "include.h"

extern unsigned short LowTime;//�͵�ƽʱ��
extern unsigned short HighTime;//�ߵ�ƽʱ��
unsigned char a[4];    //�����û��롢�û�������������롢�����ݷ���
/*******************************************************************************
****��������:
****��������:��ʼ�����⴫�����ӿ�
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��
****���ڲ���:��
****˵��:һ�廯�������ͷ��PA4����������˿�λ�ⲿ�жϣ��½��ش���
********************************************************************************/
void  IR_Init(void)
{
   EXTI_DeInit();//��ʼ����ؼĴ���λĬ��ֵ
   GPIO_Init(GPIOA, GPIO_PIN_4, GPIO_MODE_IN_PU_IT);//����������ж�
   EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOA, EXTI_SENSITIVITY_FALL_ONLY);//�½��ش���
   enableInterrupts();//ʹ�������ж�
}

/*******************************************************************************
****��������:
****��������:������뺯��
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��
****���ڲ���:1-������ȷ 0-�������
****˵��:��
********************************************************************************/
unsigned char DeCode(void)
{
    unsigned char  i,j;
    unsigned char temp;    //��������������
    for(i=0;i<4;i++)
    {
      for(j=0;j<8;j++)
      {
         temp=temp>>1;  //temp�еĸ�����λ����һλ����Ϊ�ȶ������Ǹ�λ����	
         TIM2_SetCounter(0x0000);
         TIM2_Cmd(ENABLE);
         while(!GPIO_ReadInputPin(GPIOA, GPIO_PIN_4));
         TIM2_Cmd(DISABLE);
         LowTime=TIM2_GetCounter();
  
         TIM2_SetCounter(0x0000);
         TIM2_Cmd(ENABLE);
         while(GPIO_ReadInputPin(GPIOA, GPIO_PIN_4));
         TIM2_Cmd(DISABLE);
         HighTime=TIM2_GetCounter();
         
         if((LowTime<900)||(LowTime>1300))
         {
            return 0;
         }
         if((HighTime>1000)&&(HighTime<1200))
         {
           temp=temp&0x7f;
         }
         if((HighTime>3000)&&(HighTime<3500))
         {
           temp=temp|0x80;
         }
      }
      a[i]=temp;
      
    }
    if(a[2]=~a[3])//У��
      return 1;
    else
      return 0;
}

/******************* (C) COPYRIGHT 2014 LENCHIMCU.TAOBAO.COM ******************/