#ifndef _wwdg_h_
#define _wwdg_h_
/*******************************************************************************
****����Ƕ��ʽϵͳ STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****�汾:V1.0
****����:14-2-2014
****˵��:��оƬSTM8S105C4T6
********************************************************************************/
#define COUNTERINIT 0x7f	/* ������ʼֵ */
#define WINDOW      0x77	/* ��������ֵ */
extern void WWDG_Ini(u8 Count,u8 WinCount);
extern void WWDG_RstStatus(void);
extern void WWDG_ReloadCount(void);
#endif
/******************* (C) COPYRIGHT 2014 LENCHIMCU.TAOBAO.COM ******************/