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
****��������:��ʱ��2PWM��ʼ��
****�汾:V1.0
****����:14-2-2014
****��ڲ���:timebase-ʱ�����������PWMƵ���й�
              t-�ߵ�ƽʱ�䣬��ռ�ձ��й�
****���ڲ���:��
****˵��:
********************************************************************************/
void TIMER2_PWMInit(unsigned short timebase,unsigned short t)
{
    TIM2_DeInit();  
    /*
     * TIM2 Frequency = TIM2 counter clock/(ARR + 1) 
     * ��������TIM2�ļ���Ƶ��Ϊ 16M/8/(timebase+1)=1K
     */
    TIM2_TimeBaseInit(TIM2_PRESCALER_8, timebase);	
    
    /* 
     * PWM1 Mode configuration: Channel1
     * TIM2 Channel1 duty cycle = [TIM2_CCR1/(TIM2_ARR + 1)] * 100 = 50%
     * TIM2 Channel2 duty cycle = [TIM2_CCR2/(TIM2_ARR + 1)] * 100 = 50%
     */ 
    
    /* ����ͨ��1 */
    TIM2_OC3Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE, t, TIM2_OCPOLARITY_HIGH);
    TIM2_OC3PreloadConfig(ENABLE);
    TIM2_Cmd(ENABLE);
}