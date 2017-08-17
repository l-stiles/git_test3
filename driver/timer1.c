/*******************************************************************************
****����Ƕ��ʽϵͳ STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****�汾:V1.0
****����:14-2-2014
****˵��:��оƬSTM8S105C4T6
********************************************************************************/
#include "include.h"


static void Sort(u16 array[],u8 n);
/*******************************************************************************
****��������:
****��������:��ʱ��1���벶���ʼ������
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��
****���ڲ���:��
****˵��:
********************************************************************************/
void Time1_InputCap()
{
    TIM1_ICInit(TIM1_CHANNEL_3, TIM1_ICPOLARITY_RISING, TIM1_ICSELECTION_DIRECTTI, TIM1_ICPSC_DIV8, 0x00);
    TIM1_ClearFlag(TIM1_FLAG_CC4);
    TIM1_CCxCmd(TIM1_CHANNEL_3, ENABLE);
    TIM1_Cmd(ENABLE);
}
/*******************************************************************************
****��������:
****��������:��ȡ��ʱ��1���벶��Ƶ��
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��
****���ڲ���:Ƶ��
****˵��:
********************************************************************************/
u16 Timer1_InputCapCFre(void)
{
	u16 Period;
	u16 ICValue1,ICValue2;
	FlagStatus fs;
        
	TIM1->CCR4H=0;
	TIM1->CCR4L=0;	/* ������벶׽ֵ */
        //Send_Str("test2");
	//while(!TIM1_GetFlagStatus(TIM1_FLAG_CC4));
        fs = TIM1_GetFlagStatus(TIM1_FLAG_CC3);
       // Send_Str("test3");
	ICValue1=TIM1_GetCapture3();	/* �õ���һ�β�׽����ֵ */
	//Send_Str("test4");
	TIM1_ClearFlag(TIM1_FLAG_CC3);	/* ��ձ�־λ */
	
	//while(!TIM1_GetFlagStatus(TIM1_FLAG_CC4));
         fs = TIM1_GetFlagStatus(TIM1_FLAG_CC3);
	ICValue2=TIM1_GetCapture3();	/* �õ��ڶ��β�׽����ֵ */
	TIM1_ClearFlag(TIM1_FLAG_CC3);	/* ��ձ�־λ */
	
	if(ICValue2 > ICValue1)
	  	Period = ICValue2-ICValue1;
	else if(ICValue2<ICValue1)
	  	Period = 0xffff + ICValue2-ICValue1;
	
	return Period;
}
/*******************************************************************************
****��������:
****��������:��ʱ��1Ƶ�ʻ�ȡ
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��
****���ڲ���:��
****˵��:
********************************************************************************/
void Get_FrequencyArray(u16 FrequencyArray[], u8 times)
{
    u8 i;
    for(i = 0; i < times; i++)
	FrequencyArray[i]=Timer1_InputCapCFre();
}
/*******************************************************************************
****��������:
****��������:����ֵ��������
****�汾:V1.0
****����:14-2-2014
****��ڲ���:array[]-Ҫ��������� n-����
****���ڲ���:��
****˵��:
********************************************************************************/
static void Sort(u16 array[],u8 n)
{
	u8 i,j,k;
	u16 t;
	for(i=0;i<n-1;i++)
	{
		k=i;
		for(j=i+1;j<n;j++)
			if(array[j]<array[k])
				k=j;
		
		t=array[k];
		array[k]=array[i];
		array[i]=t;
	}
}
/*******************************************************************************
****��������:
****��������:����ֵ�����˲�
****�汾:V1.0
****����:14-2-2014
****��ڲ���:GetFrequency[]-Ҫ�˲������� n-����
****���ڲ���:��
****˵��:
********************************************************************************/
u16 Get_AverageFrequency(u16 GetFrequency[],u8 n)
{
	u8 i;
	u16 temp=0;
	
	Sort(GetFrequency,n);
	
	for(i=5;i<n-5;i++)
		temp+=GetFrequency[i];
	
	temp/=(n-10);
	
	return temp;
}
/*******************************************************************************
****��������:
****��������:��ʱ��1����Ƚ�
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��
****���ڲ���:��
****˵��:
********************************************************************************/
void Timer1_OutCompare(void)
{
        TIM1_DeInit();
	/*
	TIM1_Period = 50000
	TIM1_Prescaler = 0
	TIM1_CounterMode = TIM1_COUNTERMODE_UP
	TIM1_RepetitionCounter = 0
	*/
	TIM1_TimeBaseInit(23, TIM1_COUNTERMODE_UP, 49999, 0);	
	
	/*
	TIM1_OCMode = TIM1_OCMODE_TOGGLE
	TIM1_OutputState = TIM1_OUTPUTSTATE_ENABLE
	TIM1_OutputNState = TIM1_OUTPUTNSTATE_DISABLE
	TIM1_Pulse = 5000	
	TIM1_OCPolarity = TIM1_OCPOLARITY_LOW
	TIM1_OCNPolarity = TIM1_OCNPOLARITY_HIGH
	TIM1_OCIdleState = TIM1_OCIDLESTATE_SET
	TIM1_OCNIdleState = TIM1_OCIDLESTATE_RESET
	*/
	TIM1_OC3Init(TIM1_OCMODE_TOGGLE, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_DISABLE,
			   4999, TIM1_OCPOLARITY_LOW, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_SET,
			   TIM1_OCNIDLESTATE_RESET);
 	
	/* TIM1 counter ʹ�� */
	TIM1_Cmd(ENABLE);
	TIM1_CtrlPWMOutputs(ENABLE);	/* ʹ��TIM1��� */
}
/******************* (C) COPYRIGHT 2014 LENCHIMCU.TAOBAO.COM ******************/